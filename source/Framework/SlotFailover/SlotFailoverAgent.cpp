/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/SlotFailover/SlotFailoverAgent.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Core/PrismFrameworkMessages.h"
#include "Framework/SlotFailover/SlotFailoverAgentContext.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"

namespace WaveNs
{

SlotFailoverAgent::SlotFailoverAgent (WaveObjectManager *pWaveObjectManager, UI32 slotNumber) 
    : WaveWorker (pWaveObjectManager),
    m_slotNumber (slotNumber)
{
}

SlotFailoverAgent::~SlotFailoverAgent ()
{
}

ResourceId SlotFailoverAgent::execute ()
{
    WaveNs::PrismSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SlotFailoverAgent::getListOfEnabledServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SlotFailoverAgent::sendSlotFailoverStep),

        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SlotFailoverAgent::prismSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&SlotFailoverAgent::prismSynchronousLinearSequencerFailedStep)
    };

    SlotFailoverAgentContext *pSlotFailoverAgentContext = new SlotFailoverAgentContext (reinterpret_cast<PrismAsynchronousContext *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    ResourceId status = pSlotFailoverAgentContext->execute ();

    return (status);
}

ResourceId SlotFailoverAgent::getListOfEnabledServicesStep (SlotFailoverAgentContext *pSlotFailoverAgentContext)
{
    vector<PrismServiceId> &enabledServices = pSlotFailoverAgentContext->getEnabledServices ();

    WaveObjectManager::getListOfEnabledServices (enabledServices);

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId SlotFailoverAgent::sendSlotFailoverStep (SlotFailoverAgentContext *pSlotFailoverAgentContext)
{
    vector<PrismServiceId> &serviceIdsToSendSlotFailover = pSlotFailoverAgentContext->getEnabledServices ();
    UI32                    i                    = 0;
    UI32                    numberOfServices     = 0;

    numberOfServices = serviceIdsToSendSlotFailover.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (false == (requiresSlotFailoverNotification (serviceIdsToSendSlotFailover[i])))
        {
            continue;
        }

        PrismSlotFailoverObjectManagerMessage *prismSlotFailoverObjectManagerMessage = new PrismSlotFailoverObjectManagerMessage (serviceIdsToSendSlotFailover[i], m_slotNumber);

        ResourceId status = sendSynchronously (prismSlotFailoverObjectManagerMessage);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "PrismSlotFailoverAgent::sendSlotFailoverStep: Could not send SlotFailover to a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToSendSlotFailover[i]));
            return (status);
        }
        else
        {
            status = prismSlotFailoverObjectManagerMessage->getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, "PrismSlotFailoverAgent::sendSlotFailoverStep: Not able to update Instance Id  Completion Status : " + FrameworkToolKit::localize (status));
                prismAssert (false, __FILE__, __LINE__);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "PrismSlotFailoverAgent::sendSlotFailoverStep : Successfully sent SlotFailover " + FrameworkToolKit::getServiceNameById (serviceIdsToSendSlotFailover[i]));
            }
        }

        delete prismSlotFailoverObjectManagerMessage;
    }

    return (WAVE_MESSAGE_SUCCESS);
}

bool SlotFailoverAgent::requiresSlotFailoverNotification(const PrismServiceId &prismServiceId)
{
    if (((PrismFrameworkObjectManager::getPrismServiceId               ()) == prismServiceId) ||
        (true != (FrameworkToolKit::isALocalService (prismServiceId))) ||
        (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (prismServiceId))))
    {
        return (false);
    }
    else
    {
        return (true);
    }
}

}

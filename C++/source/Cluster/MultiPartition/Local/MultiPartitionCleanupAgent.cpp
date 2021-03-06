/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayaraman Iyer                                               *
 ***************************************************************************/

#include "Cluster/MultiPartition/Local/MultiPartitionCleanupAgent.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Core/WaveFrameworkMessages.h"
#include "Cluster/Local/ClusterLocalObjectManager.h"
#include "Cluster/MultiPartition/Local/MultiPartitionLocalObjectManager.h"
#include "Cluster/MultiPartition/Local/MultiPartitionCleanupAgentContext.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"

namespace WaveNs
{

MultiPartitionCleanupAgent::MultiPartitionCleanupAgent (WaveObjectManager *pWaveObjectManager, string &partitionName, UI32 senderServiceId, ObjectId &ownerPartitionManagedObjectId) 
    : WaveWorker (pWaveObjectManager),
      m_partitionName (partitionName),
      m_senderServiceId (senderServiceId),
      m_ownerPartitionManagedObjectId (ownerPartitionManagedObjectId),
      m_isPartialCleanup              (false),
      m_partialCleanupTag             (FRAMEWORK_ERROR)

{
}

MultiPartitionCleanupAgent::~MultiPartitionCleanupAgent ()
{
}

bool MultiPartitionCleanupAgent::getIsPartialCleanup () const
{
    return m_isPartialCleanup;
}

void MultiPartitionCleanupAgent::setPartialCleanupTag (const ResourceId &partialCleanupTag)
{
    m_isPartialCleanup  = true;

    m_partialCleanupTag = partialCleanupTag;
}

ResourceId MultiPartitionCleanupAgent::getPartialCleanupTag ()
{
    waveAssert (true == m_isPartialCleanup, __FILE__, __LINE__);

    return m_partialCleanupTag;
}

ResourceId MultiPartitionCleanupAgent::execute ()
{
    trace (TRACE_LEVEL_INFO, "WaveMultiPartitionCleanupAgent::execute: called.");

    WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&MultiPartitionCleanupAgent::getListOfEnabledServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&MultiPartitionCleanupAgent::sendMultiPartitionCleanupStep),

        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&MultiPartitionCleanupAgent::waveSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&MultiPartitionCleanupAgent::waveSynchronousLinearSequencerFailedStep)
    };

    MultiPartitionCleanupAgentContext *pMultiPartitionCleanupAgentContext = new MultiPartitionCleanupAgentContext (reinterpret_cast<WaveAsynchronousContext *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    ResourceId status = pMultiPartitionCleanupAgentContext->execute ();

    return (status);
}

ResourceId MultiPartitionCleanupAgent::getListOfEnabledServicesStep (MultiPartitionCleanupAgentContext *pMultiPartitionCleanupAgentContext)
{
    trace (TRACE_LEVEL_INFO, "WaveMultiPartitionCleanupAgent::getListOfEnabledServicesStep: called.");
    vector<WaveServiceId> &enabledServices = pMultiPartitionCleanupAgentContext->getEnabledServices ();

    WaveObjectManager::getListOfEnabledServices (enabledServices);

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId MultiPartitionCleanupAgent::sendMultiPartitionCleanupStep (MultiPartitionCleanupAgentContext *pMultiPartitionCleanupAgentContext)
{
    vector<WaveServiceId> &serviceIdsToSendMultiPartitionCleanup = pMultiPartitionCleanupAgentContext->getEnabledServices ();
    UI32       i                    = 0;
    UI32       numberOfServices     = serviceIdsToSendMultiPartitionCleanup.size();

    trace (TRACE_LEVEL_INFO, string ("WaveMultiPartitionCleanupAgent::sendMultiPartitionCleanupStep: called. Total Services = [ ") + (serviceIdsToSendMultiPartitionCleanup.size())+ string("]"));
    for (i = 0; i < numberOfServices; i++)
    {
        trace (TRACE_LEVEL_INFO, "WaveMultiPartitionCleanupAgent::sendMultiPartitionCleanupStep: send PartitionCleanup to service: " + FrameworkToolKit::getServiceNameById (serviceIdsToSendMultiPartitionCleanup[i]));
        if (false == (requiresMultiPartitionCleanupNotification(serviceIdsToSendMultiPartitionCleanup[i])))
        {
            continue;
        }

        if (m_senderServiceId == serviceIdsToSendMultiPartitionCleanup[i])
        {
            // Don't send the cleanup to the caller service. 
            continue;
        }

        ObjectId ownerPartitionManagedObjectId = getOwnerPartitionManagedObjectId ();
        WaveMultiPartitionCleanupObjectManagerMessage *waveMultiPartitionCleanupObjectManagerMessage = new WaveMultiPartitionCleanupObjectManagerMessage (serviceIdsToSendMultiPartitionCleanup[i], m_partitionName, ownerPartitionManagedObjectId );

        if (true == getIsPartialCleanup ())
        {
            ResourceId partialCleanupTag = getPartialCleanupTag ();

            waveMultiPartitionCleanupObjectManagerMessage->setPartialCleanupTag (partialCleanupTag);
        }

        ResourceId status = sendSynchronously (waveMultiPartitionCleanupObjectManagerMessage);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveMultiPartitionCleanupAgent::sendMultiPartitionCleanupStep: Could not send PartitionCleanup to service: " + FrameworkToolKit::getServiceNameById (serviceIdsToSendMultiPartitionCleanup[i]));

            delete waveMultiPartitionCleanupObjectManagerMessage;

            return (status);
        }
        else
        {
            status = waveMultiPartitionCleanupObjectManagerMessage->getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, "WaveMultiPartitionCleanupAgent::sendMultiPartitionCleanupStep: Not able to update Instance Id  Completion Status : " + FrameworkToolKit::localize (status));
                waveAssert (false, __FILE__, __LINE__);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "WaveMultiPartitionCleanupAgent::sendMultiPartitionCleanupStep : Successfully sent MultiPartitionCleanup to Service: " + FrameworkToolKit::getServiceNameById (serviceIdsToSendMultiPartitionCleanup[i]));
            }
        }

        delete waveMultiPartitionCleanupObjectManagerMessage;
    }

    return (WAVE_MESSAGE_SUCCESS);
}

bool MultiPartitionCleanupAgent::requiresMultiPartitionCleanupNotification(const WaveServiceId &waveServiceId)
{
    // 1. Exlude WaveFrameworkObjectManager (in general.)
    // 2. Exclude MultiTenencyLocalObjectManager (It is running this Agent)
    // 3. Exclude Global services
    // 4. Exclude User Specific Local services.

    if (((WaveFrameworkObjectManager::getWaveServiceId()) == waveServiceId) ||
        ((MultiPartitionLocalObjectManager::getWaveServiceId ()) == waveServiceId) ||
        ((ClusterLocalObjectManager::getWaveServiceId ()) == waveServiceId) ||
        (false == (FrameworkToolKit::isALocalService (waveServiceId))) ||
        (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))))
    {
        return (false);
    }
    else
    {
        return (true);
    }
}

ObjectId  MultiPartitionCleanupAgent::getOwnerPartitionManagedObjectId () const
{
    return (m_ownerPartitionManagedObjectId);
}

}

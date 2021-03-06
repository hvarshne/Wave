/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Amit Agrawal                                                 *
 ***************************************************************************/

#include "Framework/Postboot/WavePostbootAgent.h"
#include "Framework/Postboot/WavePostbootAgentContext.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Core/WaveFrameworkMessages.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"
#include "Framework/Core/PostBootStartedEvent.h"
#include "Framework/Core/PostBootCompletedEvent.h"
#include "../postboot/PostBoot.h"

namespace WaveNs
{

// read this from the xml generated file
static map <UI32, vector <postbootPass> > registrations; 

WavePostbootAgent::WavePostbootAgent (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager, false)
{
}

WavePostbootAgent::WavePostbootAgent (WaveObjectManager *pWaveObjectManager, const UI32 &event, const UI32 &parameter, const UI32 &recoveryType)
    : WaveWorker (pWaveObjectManager, false),
     m_eventId    (event),
     m_parameter  (parameter),
     m_recoveryType (recoveryType)
{
}

WavePostbootAgent::~WavePostbootAgent ()
{
}

ResourceId WavePostbootAgent::execute ()
{
    WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WavePostbootAgent::getListOfEnabledServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WavePostbootAgent::mergeStaticRegistrationsStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WavePostbootAgent::notifyPostbootStartedStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WavePostbootAgent::sendPostbootPassStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WavePostbootAgent::notifyPostbootCompletedStep),

        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WavePostbootAgent::waveSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WavePostbootAgent::waveSynchronousLinearSequencerFailedStep)
    };

    WavePostbootAgentContext *pWavePostbootAgentContext = new WavePostbootAgentContext (reinterpret_cast<WaveAsynchronousContext *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    trace(TRACE_LEVEL_DEBUG, string("WavePostbootAgent::execute Triggering execution of sequencerSteps"));
    ResourceId status = pWavePostbootAgentContext->execute ();

    return (status);
}

ResourceId WavePostbootAgent::getListOfEnabledServicesStep (WavePostbootAgentContext *pWavePostbootAgentContext)
{
    unsigned int    i = 0;

    trace(TRACE_LEVEL_INFO, string("WavePostbootAgent::getListOfEnabledServicesStep Entered"));

    vector<WaveServiceId> &enabledServices = pWavePostbootAgentContext->getEnabledServices ();

    WaveObjectManager::getListOfEnabledServices (enabledServices);

    trace(TRACE_LEVEL_DEBUG, string("Enabled services are:"));

    for (i=0; i<enabledServices.size(); i++)
    {
        trace(TRACE_LEVEL_DEBUG, string(" ") + enabledServices[i]);
    }

    return (WAVE_MESSAGE_SUCCESS);
}

void WavePostbootAgent::populateRegistrations (map <UI32, vector <postbootPass> > registrationsTable)
{
    registrations = registrationsTable;
    return;
}

// Merge global postboot pass table with the one maintined by wave
// Wave framework provides APIs also to insert elements in this table. So,
// if any plugin uses those APIs, then also we are safe

ResourceId WavePostbootAgent::mergeStaticRegistrationsStep (WavePostbootAgentContext *pWavePostbootAgentContext)
{
    trace(TRACE_LEVEL_INFO, string("WavePostbootAgent::mergeStaticRegistrationsStep Entered"));

    m_postbootTable = registrations;
    printRegistrationTable();

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WavePostbootAgent::notifyPostbootStartedStep (WavePostbootAgentContext *pWavePostbootAgentContext)
{
    trace(TRACE_LEVEL_DEVEL, string("WavePostbootAgent::notifyPostbootStartedStep : Entered"));

    ResourceId  status  = WAVE_MESSAGE_ERROR;

    PostBootStartedEvent * pPostBootStartedEvent = new PostBootStartedEvent(m_eventId, m_parameter);
    ResourceId postboostStartBrocadcastStatus = broadcast(pPostBootStartedEvent);

    if (WAVE_MESSAGE_SUCCESS == postboostStartBrocadcastStatus)
    {
        status  = WAVE_MESSAGE_SUCCESS;
    }
    else
    {
        status = WAVE_MESSAGE_ERROR;   
    }
    
    return (status);
}

ResourceId WavePostbootAgent::sendPostbootPassStep (WavePostbootAgentContext *pWavePostbootAgentContext)
{
    vector<WaveServiceId> &enabledServices = pWavePostbootAgentContext->getEnabledServices ();
    UI8                     passNum              = 0;
    UI8                     serviceIdIndex       = 0;
    UI8                     checkIdIndex         = 0;
    UI8                     enabledIndex         = 0;
    SI8                     serviceFound         = 0;
    WaveServiceId          serviceId;
    string                  passName;
    UI32                    recoveryTypeForThisService;

    trace(TRACE_LEVEL_INFO, string("WavePostbootAgent::sendPostbootPassStep Entered"));

    if ( m_postbootTable.size() == 0 ) 
    {
        trace(TRACE_LEVEL_INFO, string("WavePostbootAgent::sendPostbootPassStep: Wave pass table is empty. No messages to be sent!"));
        return (WAVE_MESSAGE_SUCCESS);
    }

    // !! hack !! until HA support is ready for L3 config replay for warm recovery
    //string  envVar;
    //envVar = FrameworkToolKit::getProcessInitialWorkingDirectory() + "/triggerPostbootOnWarmRecovery";
    //trace (TRACE_LEVEL_INFO, string("WavePostbootAgent::sendPostbootPassStep: opening file:") + envVar);
    //ifstream tmpPostbootTriggerFile(envVar.c_str());
    
    // For all the pass rows in the table
    for (passNum = 0; passNum < m_postbootTable[m_eventId].size(); passNum++)
    {
        passName = (m_postbootTable[m_eventId])[passNum].passName;
        trace (TRACE_LEVEL_INFO, string("WavePostbootAgent:: postboot table:") + m_eventId + string(" pass:") + passNum + string(" name:") + passName);

        // verify if the #services present in the vector == #entries in recovery vector
        if (((m_postbootTable[m_eventId])[passNum].serviceId).size() != ((m_postbootTable[m_eventId])[passNum].recoveryType).size())
        {
            trace (TRACE_LEVEL_FATAL, string("WavePostbootAgent::sendPostbootPassStep: #entries in serviceId vector != #entries in recoveryType vector!!. Check the postboot cpp generation process"));
            waveAssert(false, __FILE__, __LINE__);
        }

        for (serviceIdIndex = 0; serviceIdIndex < ((m_postbootTable[m_eventId])[passNum].serviceId).size(); serviceIdIndex++)
        {
            serviceId = (m_postbootTable[m_eventId])[passNum].serviceId[serviceIdIndex];

            // skip holes in the pass row
            if (serviceId == 0) // reserved ID & a hole
            {
                trace (TRACE_LEVEL_INFO, string("WavePostbootAgent::sendPostbootPassStep: Index:") + serviceIdIndex + string(" in pass:") + passNum + string(" is empty. Skipping"));
                continue;
            }

            // if the recovery type for this boot is WARM and for this postboot entry is not WARM, skip it
            recoveryTypeForThisService = (m_postbootTable[m_eventId])[passNum].recoveryType[serviceIdIndex];

            if ( WAVE_HA_WARM_RECOVERY == m_recoveryType )
            {
                // note that the same serviceIdIndex is applicable for recoveryType vector as well
                if ( !(recoveryTypeForThisService & WAVE_RECOVERY_TYPE_WARM) )
                {
                    trace (TRACE_LEVEL_INFO, string("WavePostbootAgent::sendPostbootPassStep: boot recovery type is WARM, but for service ") + FrameworkToolKit::getServiceNameById (serviceId) + string(" with passNum:") + passNum + string(" passName:") + passName + string(" recovery type is not warm as per postboot xml. Hence skipping"));
                    continue;
                }

                // !! hack !! demand a file ~/triggerPostbootOnWarmRecovery to be created for postboot support for warm recovery now
                //if (!tmpPostbootTriggerFile)
                //{
                //    trace (TRACE_LEVEL_ERROR, string("WavePostbootAgent::sendPostbootPassStep: boot recovery type is WARM, but file:") + envVar + string(" is not present. Create it if you want WARM recovery support for postboot now"));
                //    continue;
                //}
            }
            else if ( WAVE_HA_COLD_RECOVERY == m_recoveryType )
            {
                if ( !(recoveryTypeForThisService & WAVE_RECOVERY_TYPE_COLD) )
                {
                    trace (TRACE_LEVEL_INFO, string("WavePostbootAgent::sendPostbootPassStep: boot recovery type is COLD, but for service ") + FrameworkToolKit::getServiceNameById (serviceId) + string(" with passNum:") + passNum + string(" passName:") + passName + string(" recovery type is not cold as per postboot xml. Hence skipping"));
                    continue;
                }
            }
            else
            {
                trace (TRACE_LEVEL_FATAL, string("WavePostbootAgent::sendPostbootPassStep: boot recovery type is UNKNOWN!! ") + m_recoveryType +string(" hence skipping") );
                continue;
            }

            // check if this service ID is repeated in the pass row
            for (checkIdIndex = serviceIdIndex+1; checkIdIndex < ((m_postbootTable[m_eventId])[passNum].serviceId).size(); checkIdIndex++)
            {
                if (serviceId == (m_postbootTable[m_eventId])[passNum].serviceId[checkIdIndex])
                {
                    trace (TRACE_LEVEL_FATAL, string("WavePostbootAgent::sendPostbootPassStep: Duplicate serviceID:") + serviceId + string(" not allowed in same pass!"));
                    waveAssert(false, __FILE__, __LINE__);
                }
            }
            
            // first check if the service id in postboot table is actually enabled
            serviceFound = 0;
            for (enabledIndex = 0; enabledIndex < enabledServices.size(); enabledIndex++)
            {
                if (serviceId == enabledServices[enabledIndex])
                {
                    serviceFound = 1;
                    break;
                }
            }
            if (serviceFound == 0)
            {
                trace (TRACE_LEVEL_WARN, string("WavePostbootAgent::sendPostbootPassStep: ServiceId:") + serviceId + string(" is not enabled!"));
                continue;
            }
            
            if (false == requiresPostboot(serviceId))
            {
                trace (TRACE_LEVEL_INFO, string("WavePostbootAgent::sendPostbootPassStep: Postboot required is false for ServiceId:") + serviceId);
                continue;
            }

            // Create a message with the serviceId & the pass number. This message will be sent to the plugins

            trace (TRACE_LEVEL_INFO, string("WavePostbootAgent::sendPostbootPassStep: Sending postboot message to serviceId:") + FrameworkToolKit::getServiceNameById (serviceId) + string(" with passNum:") + passNum + string(" passName:") + passName + string(" parameter:") + m_parameter + string(" recoveryType:") + m_recoveryType);
            WavePostbootObjectManagerMessage wavePostbootObjectManagerMessage (serviceId, passNum, passName, m_parameter, m_recoveryType);

            ResourceId status = sendSynchronously (&wavePostbootObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, "WaveBootAgent::sendPostbootPassStep : Could not Postboot a service : " + FrameworkToolKit::getServiceNameById (serviceId));
                waveAssert (false, __FILE__, __LINE__);
                return (status);
            }
            else
            {
                if (WAVE_MESSAGE_SUCCESS != wavePostbootObjectManagerMessage.getCompletionStatus ())
                {
                    trace (TRACE_LEVEL_FATAL, string("WavePostbootAgent::sendPostbootPassStep: Failed to send message"));
                }
                else
                {
                    trace (TRACE_LEVEL_DEBUG, string("WavePostbootAgent::sendPostbootPassStep: Message sent successfully"));
                }
            }
        }
    }
    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WavePostbootAgent::notifyPostbootCompletedStep (WavePostbootAgentContext *pWavePostbootAgentContext)
{
    trace(TRACE_LEVEL_DEVEL, string("WavePostbootAgent::notifyPostbootCompletedStep :  Entered"));

    ResourceId  status  = WAVE_MESSAGE_ERROR;

    PostBootCompletedEvent * pPostBootCompletedEvent = new PostBootCompletedEvent(m_eventId, m_parameter);
    ResourceId postboostCompleteBrocadcastStatus = broadcast(pPostBootCompletedEvent);

    if (WAVE_MESSAGE_SUCCESS == postboostCompleteBrocadcastStatus)
    {
        status  = WAVE_MESSAGE_SUCCESS;
    }
    else
    {
        status = WAVE_MESSAGE_ERROR;   
    }

    return (status);
}

bool WavePostbootAgent::requiresPostboot (const WaveServiceId &waveServiceId)
{
    if (((WaveFrameworkObjectManager::getWaveServiceId ()) == waveServiceId) ||
        (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))))
    {
        return (false);
    }
    else
    {
        return (true);
    }
}

void WavePostbootAgent::printRegistrationTable (void)
{
    UI8                     tableNum             = 0;
    UI8                     passNum              = 0;
    UI8                     serviceIdIndex       = 0;
    WaveServiceId          serviceId;

    cout << endl;
    cout << "==============================================" << endl;
    cout << "WavePostbootAgent::printRegistrationTable =>" << endl;
    cout << "==============================================";

    map<UI32, vector <postbootPass> >::iterator it;

  // show content:
    for ( it = m_postbootTable.begin() ; it != m_postbootTable.end(); it++ )
    {
        tableNum = (UI8)(it->first);
        cout << endl << "For table" << (int)tableNum << " ";
 
        for (passNum = 0; passNum < m_postbootTable[tableNum].size(); passNum++)
        {
            cout << endl << "For pass:" << (int)passNum << "name:" << (m_postbootTable[tableNum])[passNum].passName;
        cout << "ServiceIDs are: ";

            for (serviceIdIndex = 0; serviceIdIndex < ((m_postbootTable[tableNum])[passNum].serviceId).size(); serviceIdIndex++)
            {
                serviceId = (m_postbootTable[tableNum])[passNum].serviceId[serviceIdIndex];
            cout << serviceId << " ";
            }
        }
    }
    cout << endl;
    cout << "==============================================" << endl;
}

}

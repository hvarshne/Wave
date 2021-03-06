/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "SystemManagement/Migration/WaveSystemManagementGetPossibleCompletionsWorker.h"
#include "SystemManagement/WaveSystemManagementTypes.h"
#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "SystemManagement/WaveSystemManagementObjectManager.h"
#include "Modeling/YANG/ObjectModel/YangElement.h"
#include "Modeling/YANG/ObjectModel/YangUserInterface.h"
#include "SystemManagement/CommandLineInterface/Client/CommandLineInterfaceEntry.h"
#include "SystemManagement/Migration/WaveSystemManagementGetPossibleCompletionsMessage.h"

namespace WaveNs
{

WaveSystemManagementGetPossibleCompletionsWorker::WaveSystemManagementGetPossibleCompletionsWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager), 
    m_pTopLevelCommandLineinterfaceEntry                (NULL),
    m_pCommandLineInterfaceEntryForShowRunningConfig    (NULL),
    m_pCommandLineInterfaceEntryForShow                 (NULL),
    m_pYangUserInterface                                (NULL),
    m_isInitializationDone                              (false)

{
    addOperationMap (WAVE_SYSTEM_MANAGEMENT_GET_POSSIBLE_COMPLETIONS_MESSAGE, reinterpret_cast<WaveMessageHandler> (&WaveSystemManagementGetPossibleCompletionsWorker::getPossibleCompletionsMessageHandler));
}

WaveSystemManagementGetPossibleCompletionsWorker::~WaveSystemManagementGetPossibleCompletionsWorker ()
{
}

WaveMessage *WaveSystemManagementGetPossibleCompletionsWorker::createMessageInstance (const UI32 &operationCode)
{
    WaveMessage *pWaveMessage = NULL;

    switch (operationCode)
    {
        case WAVE_SYSTEM_MANAGEMENT_GET_POSSIBLE_COMPLETIONS_MESSAGE:
            pWaveMessage = new WaveSystemManagementGetPossibleCompletionsMessage ();
            break;

        default :
            trace (TRACE_LEVEL_FATAL, string ("WaveSystemManagementGetPossibleCompletionsMessage::createMessageInstance : Unknown operation code : ") + operationCode);
            waveAssert (false, __FILE__, __LINE__);
            break;
    }

    return (pWaveMessage);
}
                
void WaveSystemManagementGetPossibleCompletionsWorker::getPossibleCompletionsMessageHandler (WaveSystemManagementGetPossibleCompletionsMessage *pWaveSystemManagementGetPossibleCompletionsMessage)
{
    trace (TRACE_LEVEL_DEBUG, "WaveSystemManagementGetPossibleCompletionsWorker::getPossibleCompletionsMessageHandler : Entered ");

    if (false == m_isInitializationDone)
    {
        initializeCommandLineInterfaces ();
    }

    string commandName = pWaveSystemManagementGetPossibleCompletionsMessage->getCommandName ();
    string token = pWaveSystemManagementGetPossibleCompletionsMessage->getToken ();
    vector<string> keyVector;
    
    trace (TRACE_LEVEL_DEBUG, string ("WaveSystemManagementGetPossibleCompletionsWorker::getPossibleCompletionsMessageHandler Command Name is ###########   ") + commandName + string ("   ##################"));

    vector<string>              possibleCompletions;
    CommandLineInterfaceEntry  *pTokenCliEntry;
    vector<YangElement *>       tempYangElements;
    
    if (commandName == "")
    {
        m_pCommandLineInterfaceEntryForShowRunningConfig->getValidCommands (possibleCompletions, keyVector , token) ;
    }
    else
    {
        trace (TRACE_LEVEL_DEBUG, string ("WaveSystemManagementGetPossibleCompletionsWorker::getPossibleCompletionsMessageHandler : command name after  removing  :  ") + commandName);
        pTokenCliEntry = m_pCommandLineInterfaceEntryForShowRunningConfig->getCommandLineInterfaceEntry (commandName , keyVector);
        if (NULL != pTokenCliEntry)
        { 
            pTokenCliEntry->getValidCommands (possibleCompletions, keyVector, token);
        }
    }

    if ("" != commandName)
    {
        commandName += " ";
    }

    for (UI32 i = 0; i < possibleCompletions.size (); i++)
    {
        trace (TRACE_LEVEL_DEBUG, string ("WaveSystemManagementGetPossibleCompletionsWorker::getPossibleCompletionsMessageHandler : Children :  ") + possibleCompletions[i]);

        tempYangElements    = m_pYangUserInterface->getYangElementsByTargetNodeName (commandName + possibleCompletions[i]);

        if (tempYangElements.size () > 0)
        {
            trace (TRACE_LEVEL_DEBUG, string ("WaveSystemManagementGetPossibleCompletionsWorker::getPossibleCompletionsMessageHandler : Child Info : ") + tempYangElements[0]->getInfo ());
            pWaveSystemManagementGetPossibleCompletionsMessage->addCompletionNameAndInfoOneByOne (possibleCompletions[i], tempYangElements[0]->getInfo ());
        }
        else
        {
            pWaveSystemManagementGetPossibleCompletionsMessage->addCompletionNameAndInfoOneByOne (possibleCompletions[i], ""); 
        }

        tempYangElements.clear ();
    }

    pWaveSystemManagementGetPossibleCompletionsMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    reply (pWaveSystemManagementGetPossibleCompletionsMessage);
}
                
void WaveSystemManagementGetPossibleCompletionsWorker::initializeCommandLineInterfaces ()
{
    trace (TRACE_LEVEL_DEBUG, string ("WaveSystemManagementGetPossibleCompletionsWorker::initializeCommandLineInterfaces3 : Entering ... "));

    m_pYangUserInterface  = WaveSystemManagementObjectManager::getYangUserInterface ();    

    vector<string> commandLinesForShowRunningConfig;

    m_pYangUserInterface->getAllCliTargetNodeNamesForData (commandLinesForShowRunningConfig);

    m_pTopLevelCommandLineinterfaceEntry                = new CommandLineInterfaceEntry ();
    m_pCommandLineInterfaceEntryForShow                 = new CommandLineInterfaceEntry ("show");
    m_pCommandLineInterfaceEntryForShowRunningConfig    = new CommandLineInterfaceEntry ("running-config");

    m_pCommandLineInterfaceEntryForShow->addChildEntryIfDoesNotExist    (m_pCommandLineInterfaceEntryForShowRunningConfig);
    m_pTopLevelCommandLineinterfaceEntry->addChildEntryIfDoesNotExist   (m_pCommandLineInterfaceEntryForShow);
   
    m_pCommandLineInterfaceEntryForShow->setCliTargetNodeName              ("");
    m_pCommandLineInterfaceEntryForShowRunningConfig->setCliTargetNodeName ("");


    m_pCommandLineInterfaceEntryForShowRunningConfig->addCommandLines (commandLinesForShowRunningConfig);
    
    m_pTopLevelCommandLineinterfaceEntry->sortValidCommands ();

    m_isInitializationDone = true;
}

}


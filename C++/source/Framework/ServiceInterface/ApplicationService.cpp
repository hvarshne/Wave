/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ServiceInterface/ApplicationService.h"
#include "Framework/ServiceInterface/ApplicationServiceMessages.h"
#include "Framework/ServiceInterface/ApplicationServiceUtils.h"
#include "Framework/Utils/StringUtils.h"

namespace WaveNs
{

ApplicationServiceRepository *ApplicationService::m_pApplicationServiceRepository = NULL;

ApplicationService::ApplicationService (const string &applicationServiceName, const UI32 &applicationServiceId)
    : WaveObjectManager (applicationServiceName),
      m_applicationServiceId (applicationServiceId)
{
    addOperationMap (WAVE_OBJECT_MANAGER_ANY_OPCODE, reinterpret_cast<WaveMessageHandler> (&ApplicationService::applicationServiceMessageHandler));

    map<UI32, ApplicationServiceMessageHandler> *pHandlersMap = ApplicationServiceHelper::getHandlersMapForApplicationService (m_applicationServiceId);

    if (NULL != pHandlersMap)
    {
        map<UI32, ApplicationServiceMessageHandler>::iterator element    = pHandlersMap->begin ();
        map<UI32, ApplicationServiceMessageHandler>::iterator endElement = pHandlersMap->end ();

        while (element != endElement)
        {
            addMessageHandlerToThisApplicationService (element->first, element->second);

            element++;
        }
    }
}

ApplicationService::~ApplicationService ()
{
}

WaveMessage *ApplicationService::createMessageInstance (const UI32 &operationCode)
{
    WaveMessage *pWaveMessage = NULL;

    switch (operationCode)
    {
        case APPLICATION_SERVICE_GENERIC_MESSAGE:
            pWaveMessage = new ApplicationServiceMessage ();
            break;
        default:
            pWaveMessage = NULL;
    }

    return (pWaveMessage);
}

UI32 ApplicationService::registerNewApplicationService (const string &newApplicationServiceName)
{
    UI32 newApplicationServiceId = 0;

    ApplicationServiceHelper::lock ();

    if (NULL == m_pApplicationServiceRepository)
    {
        m_pApplicationServiceRepository = ApplicationServiceRepository::getInstance ();
    }

    newApplicationServiceId = ApplicationServiceHelper::getNextApplicationServiceId ();

    m_pApplicationServiceRepository->addNewApplicationService (newApplicationServiceId, newApplicationServiceName);

    ApplicationServiceHelper::unlock ();

    return (newApplicationServiceId);
}

void ApplicationService::createNewApplicationServices ()
{
    ApplicationServiceHelper::lock ();

    if (NULL != m_pApplicationServiceRepository)
    {
        m_pApplicationServiceRepository->createApplicationServices ();
    }

    ApplicationServiceHelper::unlock ();
}

void ApplicationService::addMessageHandler (const UI32 &applicationServiceId, const UI32 &operationCode, ApplicationServiceMessageHandler handler)
{
    ApplicationServiceHelper::lock ();

    ApplicationServiceHelper::addMessageHandler (applicationServiceId, operationCode, handler);

    ApplicationServiceHelper::unlock ();
}

void ApplicationService::addMessageHandlerToThisApplicationService (const UI32 &operationCode, ApplicationServiceMessageHandler handler)
{
    map<UI32, ApplicationServiceMessageHandler>::iterator element    = m_applicaionServiceMessageHandlersMap.find (operationCode);
    map<UI32, ApplicationServiceMessageHandler>::iterator endElement = m_applicaionServiceMessageHandlersMap.end ();

    if (element != endElement)
    {
        trace (TRACE_LEVEL_FATAL, "ApplicationService::applicationServiceMessageHandler : Handler already registered for operation code : " + operationCode);
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        m_applicaionServiceMessageHandlersMap[operationCode] = handler;
    }
}

void ApplicationService::applicationServiceMessageHandler (ApplicationServiceMessage *pApplicationServiceMessage)
{
    UI32  operationCode = pApplicationServiceMessage->getOperationCode ();
    void *pPayLoad      = NULL;
    UI32  payLoadLength = 0;

    pPayLoad = pApplicationServiceMessage->getInputBuffer1 (payLoadLength);

    ApplicationServiceMessageHandler pMessageHandler = m_applicaionServiceMessageHandlersMap[operationCode];

    if (NULL == pMessageHandler)
    {
        trace (TRACE_LEVEL_FATAL, "ApplicationService::applicationServiceMessageHandler : No Handler registered for operation code : " + operationCode);
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        ApplicationServiceMessageHandlerContext *pApplicationServiceMessageHandlerContext = new  ApplicationServiceMessageHandlerContext (this, pApplicationServiceMessage);

        waveAssert (NULL != pApplicationServiceMessageHandlerContext, __FILE__, __LINE__);

        (*pMessageHandler) (pPayLoad, payLoadLength, pApplicationServiceMessageHandlerContext);
    }
}

void ApplicationService::applicationServiceMessageCallback (FrameworkStatus frameworkStatus, ApplicationServiceMessage *pApplicationServiceMessage, void *pContext)
{
    ApplicationServiceSendContext *pApplicationServiceSendContext = reinterpret_cast<ApplicationServiceSendContext *> (pContext);
    void                          *pOutputPayLoad                 = NULL;
    UI32                           outputPayLoadLength            = 0;
    ResourceId                     messageStatus                  = WAVE_MESSAGE_SUCCESS;

    if (FRAMEWORK_SUCCESS != frameworkStatus)
    {
        trace (TRACE_LEVEL_ERROR, string ("ApplicationService::applicationServiceMessageCallback : Application Message failed, Framework Status : ") + frameworkStatus);
    }

    if (NULL != pApplicationServiceMessage)
    {
        pOutputPayLoad = pApplicationServiceMessage->transferBufferToUser (APPLICATION_SERVICE_GENERIC_MESSAGE_OUTPUT_BUFFER1, outputPayLoadLength);
        messageStatus  = pApplicationServiceMessage->getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != messageStatus)
        {
            trace (TRACE_LEVEL_ERROR, string ("ApplicationService::applicationServiceMessageCallback : Message sent to Application Service returned error : ") + messageStatus);
        }

        delete pApplicationServiceMessage;
    }

    waveAssert (NULL != pApplicationServiceSendContext, __FILE__, __LINE__);

    ApplicationServiceCallback  pApplicationServiceCallback = pApplicationServiceSendContext->getPApplicationServiceCallback ();
    void                       *pApplicationServiceContext  = pApplicationServiceSendContext->getPApplicationServiceContext ();

    delete pApplicationServiceSendContext;

    if (NULL != pApplicationServiceCallback)
    {
        (*pApplicationServiceCallback) (pOutputPayLoad, outputPayLoadLength, pApplicationServiceContext);
    }
}

}

/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveMessagingBrokerClient/Test/WaveMessagingBrokerClientTestObjectManager.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveMessagingBrokerClient/Test/WaveBrokerPublishTest1Message.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveBrokerPublishMessageFactory.h"
#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveBrokerPublishMessage.h"

namespace WaveNs
{

WaveMessagingBrokerClientTestObjectManager::WaveMessagingBrokerClientTestObjectManager ()
    : WaveTestObjectManager (getServiceName ())
{
    WaveBrokerPublishMessageFactory::registerWaveBrokerPublishMessageInstantiator ("WaveBrokerPublishTest1Message", &WaveBrokerPublishTest1Message::createMessageInstance);
}

WaveMessagingBrokerClientTestObjectManager::~WaveMessagingBrokerClientTestObjectManager ()
{
}

string WaveMessagingBrokerClientTestObjectManager::getServiceName ()
{
    return ("Wave Messaging Broker Client Test");
}

WaveMessagingBrokerClientTestObjectManager *WaveMessagingBrokerClientTestObjectManager::getInstance ()
{
    static WaveMessagingBrokerClientTestObjectManager *pWaveMessagingBrokerClientTestObjectManager = new WaveMessagingBrokerClientTestObjectManager ();

    WaveNs::waveAssert (NULL != pWaveMessagingBrokerClientTestObjectManager, __FILE__, __LINE__);

    return (pWaveMessagingBrokerClientTestObjectManager);
}

WaveServiceId WaveMessagingBrokerClientTestObjectManager::getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

void WaveMessagingBrokerClientTestObjectManager::testRequestHandler (RegressionTestMessage *pRegressionTestMessage)
{
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveMessagingBrokerClientTestObjectManager::simpleWaveBrokerConnectTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveMessagingBrokerClientTestObjectManager::simpleWaveBrokerSubscribeMessageTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveMessagingBrokerClientTestObjectManager::simpleWaveBrokerPublishMessageTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveMessagingBrokerClientTestObjectManager::waveLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveMessagingBrokerClientTestObjectManager::waveLinearSequencerFailedStep),
    };

    WaveLinearSequencerContext *pWaveLinearSequencerContext = new WaveLinearSequencerContext (pRegressionTestMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pWaveLinearSequencerContext->start ();
}

void WaveMessagingBrokerClientTestObjectManager::simpleWaveBrokerConnectTestStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    string brokerName         = "broker1";
    bool   runConnectingTests = false;
    string tempString;
    string brokerIpAddress;
    SI32   brokerPort;

    brokerName      = getTestParameterValue ("broker");
    brokerIpAddress = getTestParameterValue ("brokerip");
    tempString      = getTestParameterValue ("brokerport");
    brokerPort      = atoi (tempString.c_str ());
    tempString      = getTestParameterValue ("connect");

    if ("true" == tempString)
    {
        runConnectingTests = true;
    }

    if (true == runConnectingTests)
    {
        trace (TRACE_LEVEL_INFO, "WaveMessagingBrokerClientTestObjectManager::simpleWaveBrokerConnectTestStep : Running Connecting Tests ...");

        WaveMessageBrokerStatus status = connectToMessageBroker (brokerName, brokerIpAddress, brokerPort);

        if (WAVE_MESSAGE_BROKER_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, "WaveMessagingBrokerClientTestObjectManager::simpleWaveBrokerConnectTestStep : Failed to connect to Broker.  Broker Name : " + brokerName);
        }
    }

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveMessagingBrokerClientTestObjectManager::simpleWaveBrokerPublishMessageTestStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    string brokerName                = "broker1";
    bool   runPublishingTests        = false;
    string tempString;
    UI32   numberOfMessagesToPublish = 1000;

    brokerName = getTestParameterValue ("broker");
    tempString = getTestParameterValue ("publish");

    if ("true" == tempString)
    {
        runPublishingTests = true;
    }

    tempString = getTestParameterValue ("nmsgs");

    if ("" != tempString)
    {
        numberOfMessagesToPublish = atoi (tempString.c_str ());
    }

    if (true == runPublishingTests)
    {
        trace (TRACE_LEVEL_INFO, "WaveMessagingBrokerClientTestObjectManager::simpleWaveBrokerPublishMessageTestStep : Running Publish Tests ...");

        WaveBrokerPublishTest1Message *pWaveBrokerPublishTest1Message = new WaveBrokerPublishTest1Message ();

        waveAssert (NULL != pWaveBrokerPublishTest1Message, __FILE__, __LINE__);

        UI32 i = 0;

        for (i = 0; i < numberOfMessagesToPublish; i++)
        {
            pWaveBrokerPublishTest1Message->setMessageToBePublished (string ("Published Message - ") + (i + 1));

            WaveMessageBrokerStatus status = publishToMessageBroker (brokerName, pWaveBrokerPublishTest1Message);

            if (WAVE_MESSAGE_BROKER_SUCCESS != status)
            {
                trace (TRACE_LEVEL_ERROR, "WaveMessagingBrokerClientTestObjectManager::simpleWaveBrokerPublishMessageTestStep : Failed to publish message : Status : " + FrameworkToolKit::localize (status));
            }

            if (0 == ((i + 1) % 10000))
            {
                trace (TRACE_LEVEL_INFO, string ("    Published Message Count : ") + (i + 1));
            }
        }

        delete pWaveBrokerPublishTest1Message;
    }

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveMessagingBrokerClientTestObjectManager::simpleWaveBrokerSubscribeMessageTestStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    string brokerName        = "broker1";
    bool   runSubscribeTests = false;
    string tempString;

    brokerName = getTestParameterValue ("broker");
    tempString = getTestParameterValue ("subscribe");

    if ("true" == tempString)
    {
        runSubscribeTests = true;
    }

    if (true == runSubscribeTests)
    {
        trace (TRACE_LEVEL_INFO, "WaveMessagingBrokerClientTestObjectManager::simpleWaveBrokerSubscribeMessageTestStep : Running Subscribe Tests ...");

        string topicToSubscribe = "WaveBrokerPublishTest1Message";

        WaveMessageBrokerStatus status = subscribeToMessageBroker (brokerName, topicToSubscribe, reinterpret_cast<WaveBrokerPublishMessageHandler>(&WaveMessagingBrokerClientTestObjectManager::simpleSubscriptionCallback));

        if (WAVE_MESSAGE_BROKER_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, "WaveMessagingBrokerClientTestObjectManager::simpleWaveBrokerSubscribeMessageTestStep : Failed to publish message : Status : " + FrameworkToolKit::localize (status));
        }
    }

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveMessagingBrokerClientTestObjectManager::simpleSubscriptionCallback (const WaveBrokerPublishMessage * const pWaveBrokerPublishMessage)
{
    static UI64 totalNumberOfPublishedMessagesReceived  = 0;

    waveAssert (NULL != pWaveBrokerPublishMessage, __FILE__, __LINE__);

    const WaveBrokerPublishTest1Message * const pWaveBrokerPublishTest1Message = dynamic_cast<const WaveBrokerPublishTest1Message * const> (pWaveBrokerPublishMessage);

    waveAssert (NULL != pWaveBrokerPublishTest1Message, __FILE__, __LINE__);

    totalNumberOfPublishedMessagesReceived++;

    if (0 == (totalNumberOfPublishedMessagesReceived % 10000))
    {
        trace (TRACE_LEVEL_INFO, "WaveMessagingBrokerClientTestObjectManager::simpleSubscriptionCallback : " + pWaveBrokerPublishTest1Message->getMessageToBePublished () + string (" : Sequence No. : " ) + pWaveBrokerPublishTest1Message->getSequenceNumber ());
    }

    pWaveBrokerPublishTest1Message->garbageCollect ();
}

}

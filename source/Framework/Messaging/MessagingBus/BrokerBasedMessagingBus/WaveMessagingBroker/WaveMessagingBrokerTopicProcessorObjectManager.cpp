/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveMessagingBroker/WaveMessagingBrokerTopicProcessorObjectManager.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveMessagingBroker/WaveMessagingBrokerTopicProcessorPublishWorker.h"

namespace WaveNs
{

map<string, PrismServiceId> WaveMessagingBrokerTopicProcessorObjectManager::m_topicNameToPrismServiceIdMap;
PrismMutex                  WaveMessagingBrokerTopicProcessorObjectManager::m_topicNameToPrismServiceIdMapMutex;

WaveMessagingBrokerTopicProcessorObjectManager::WaveMessagingBrokerTopicProcessorObjectManager (const string &topicName)
    : WaveLocalObjectManager                            ((getServiceNamePrefix ()) + topicName),
      m_topicName                                       (topicName),
      m_pWaveMessagingBrokerTopicProcessorPublishWorker (NULL)
{
    m_topicNameToPrismServiceIdMapMutex.lock ();

    map<string, PrismServiceId>::const_iterator element    = m_topicNameToPrismServiceIdMap.find (topicName);
    map<string, PrismServiceId>::const_iterator endElement = m_topicNameToPrismServiceIdMap.end  ();

    if (endElement == element)
    {
        m_topicNameToPrismServiceIdMap[topicName] = getServiceId ();
    }
    else
    {
        prismAssert (false, __FILE__, __LINE__);
    }

    m_topicNameToPrismServiceIdMapMutex.unlock ();

    m_pWaveMessagingBrokerTopicProcessorPublishWorker = new WaveMessagingBrokerTopicProcessorPublishWorker (this);

    bootStrapSelf ();
}

WaveMessagingBrokerTopicProcessorObjectManager::~WaveMessagingBrokerTopicProcessorObjectManager ()
{
    m_topicNameToPrismServiceIdMapMutex.lock ();

    map<string, PrismServiceId>::iterator element    = m_topicNameToPrismServiceIdMap.find (m_topicName);
    map<string, PrismServiceId>::iterator endElement = m_topicNameToPrismServiceIdMap.end  ();

    if (endElement != element)
    {
        m_topicNameToPrismServiceIdMap.erase (element);
    }
    else
    {
        prismAssert (false, __FILE__, __LINE__);
    }

    m_topicNameToPrismServiceIdMapMutex.unlock ();
}

WaveMessagingBrokerTopicProcessorObjectManager *WaveMessagingBrokerTopicProcessorObjectManager::createInstance (const string &topicName)
{
    WaveMessagingBrokerTopicProcessorObjectManager *pWaveMessagingBrokerTopicProcessorObjectManager = new WaveMessagingBrokerTopicProcessorObjectManager (topicName);

    WaveNs::prismAssert (NULL != pWaveMessagingBrokerTopicProcessorObjectManager, __FILE__, __LINE__);

    return (pWaveMessagingBrokerTopicProcessorObjectManager);
}

string WaveMessagingBrokerTopicProcessorObjectManager::getServiceNamePrefix ()
{
    return ("Wave Messaging Broker Topic Processor - ");
}

string WaveMessagingBrokerTopicProcessorObjectManager::getTopicName () const
{
    return (m_topicName);
}

PrismServiceId WaveMessagingBrokerTopicProcessorObjectManager::getPrismServiceIdByTopicName (const string &topicName)
{
    PrismServiceId prismServiceId = 0;

    m_topicNameToPrismServiceIdMapMutex.lock ();

    map<string, PrismServiceId>::const_iterator element    = m_topicNameToPrismServiceIdMap.find (topicName);
    map<string, PrismServiceId>::const_iterator endElement = m_topicNameToPrismServiceIdMap.end  ();

    if (endElement != element)
    {
        prismServiceId = element->second;
    }

    m_topicNameToPrismServiceIdMapMutex.unlock ();

    return (prismServiceId);
}

}

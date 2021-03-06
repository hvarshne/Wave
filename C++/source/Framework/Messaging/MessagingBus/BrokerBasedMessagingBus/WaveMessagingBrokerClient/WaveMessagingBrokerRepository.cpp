/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveMessagingBrokerClient/WaveMessagingBrokerRepository.h"
#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveMessagingBrokerClient/WaveMessagingBroker.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveBrokerSubscribeMessage.h"
#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveBrokerPublishMessage.h"

namespace WaveNs
{

WaveMessagingBrokerRepository::WaveMessagingBrokerRepository ()
{
}

WaveMessagingBrokerRepository::~WaveMessagingBrokerRepository ()
{
}

string WaveMessagingBrokerRepository::getWaveMessagingBrokerUniqueString (const string &ipAddress, const SI32 &port)
{
    return (ipAddress + string (":") + port);
}

WaveMessagingBrokerRepository *WaveMessagingBrokerRepository::getInstance ()
{
    static WaveMutex                           waveMessagingBrokerRepositoryMutex;
    static WaveMessagingBrokerRepository *pWaveMessagingBrokerClientRepository = NULL;

    waveMessagingBrokerRepositoryMutex.lock ();

    if (NULL == pWaveMessagingBrokerClientRepository)
    {
        pWaveMessagingBrokerClientRepository = new WaveMessagingBrokerRepository ();

        waveAssert (NULL != pWaveMessagingBrokerClientRepository, __FILE__, __LINE__);
    }

    waveMessagingBrokerRepositoryMutex.unlock ();

    return (pWaveMessagingBrokerClientRepository);
}

bool WaveMessagingBrokerRepository::isAKnownBrokerByName (const string &name)
{
    bool isKnown = false;

    m_waveMessagingBrokersMutex.lock ();

    map<string, WaveMessagingBroker *>::const_iterator element    = m_waveMessagingBrokersMapByName.find (name);
    map<string, WaveMessagingBroker *>::const_iterator endElement = m_waveMessagingBrokersMapByName.end  ();

    if (endElement != element)
    {
        isKnown = true;
    }
    else
    {
        isKnown = false;
    }

    m_waveMessagingBrokersMutex.unlock();

    return (isKnown);
}

bool WaveMessagingBrokerRepository::isAKnownBrokerByUniqueString (const string &uniqueString)
{
    bool isKnown = false;

    m_waveMessagingBrokersMutex.lock ();

    map<string, WaveMessagingBroker *>::const_iterator element    = m_waveMessagingBrokersMapByUniqueString.find (uniqueString);
    map<string, WaveMessagingBroker *>::const_iterator endElement = m_waveMessagingBrokersMapByUniqueString.end  ();

    if (endElement != element)
    {
        isKnown = true;
    }
    else
    {
        isKnown = false;
    }

    m_waveMessagingBrokersMutex.unlock();

    return (isKnown);
}

bool WaveMessagingBrokerRepository::isAKnownBroker (const string &ipAddress, const SI32 &port)
{
    bool   isKnown      = false;
    string uniqueString = getWaveMessagingBrokerUniqueString (ipAddress, port);

    m_waveMessagingBrokersMutex.lock ();

    map<string, WaveMessagingBroker *>::const_iterator element    = m_waveMessagingBrokersMapByUniqueString.find (uniqueString);
    map<string, WaveMessagingBroker *>::const_iterator endElement = m_waveMessagingBrokersMapByUniqueString.end  ();

    if (endElement != element)
    {
        isKnown = true;
    }
    else
    {
        isKnown = false;
    }

    m_waveMessagingBrokersMutex.unlock();

    return (isKnown);
}

bool WaveMessagingBrokerRepository::isAKnownBroker (const string& name, const string &ipAddress, const SI32 &port)
{
    bool   isKnownByName                   = false;
    bool   isKnownByUniqueString           = false;
    string waveMessagingBrokerUniqueString = getWaveMessagingBrokerUniqueString (ipAddress, port);

    m_waveMessagingBrokersMutex.lock ();

    map<string, WaveMessagingBroker *>::const_iterator element    = m_waveMessagingBrokersMapByName.find (name);
    map<string, WaveMessagingBroker *>::const_iterator endElement = m_waveMessagingBrokersMapByName.end  ();

    if (endElement != element)
    {
        isKnownByName = true;
    }
    else
    {
        isKnownByName = false;
    }

    map<string, WaveMessagingBroker *>::const_iterator element1    = m_waveMessagingBrokersMapByUniqueString.find (waveMessagingBrokerUniqueString);
    map<string, WaveMessagingBroker *>::const_iterator endElement1 = m_waveMessagingBrokersMapByUniqueString.end  ();

    if (endElement1 != element1)
    {
        isKnownByUniqueString = true;
    }
    else
    {
        isKnownByUniqueString = false;
    }

    m_waveMessagingBrokersMutex.unlock();

    waveAssert (isKnownByName == isKnownByUniqueString, __FILE__, __LINE__);

    return (isKnownByName);
}

bool WaveMessagingBrokerRepository::addBrokerIfNotAlreadyKnown (const string& name, const string &ipAddress, const SI32 &port)
{
    bool   isKnownByName                   = false;
    bool   isKnownByUniqueString           = false;
    string waveMessagingBrokerUniqueString = getWaveMessagingBrokerUniqueString (ipAddress, port);
    bool   isNewBrokerNeeded               = false;

    m_waveMessagingBrokersMutex.lock ();

    map<string, WaveMessagingBroker *>::const_iterator element    = m_waveMessagingBrokersMapByName.find (name);
    map<string, WaveMessagingBroker *>::const_iterator endElement = m_waveMessagingBrokersMapByName.end  ();

    if (endElement != element)
    {
        isKnownByName = true;
    }
    else
    {
        isKnownByName = false;
    }

    map<string, WaveMessagingBroker *>::const_iterator element1    = m_waveMessagingBrokersMapByUniqueString.find (waveMessagingBrokerUniqueString);
    map<string, WaveMessagingBroker *>::const_iterator endElement1 = m_waveMessagingBrokersMapByUniqueString.end  ();

    if (endElement1 != element1)
    {
        isKnownByUniqueString = true;
    }
    else
    {
        isKnownByUniqueString = false;
    }


    if ((false == isKnownByName) && (false == isKnownByUniqueString))
    {
        isNewBrokerNeeded = true;

        WaveMessagingBroker *pWaveMessagingBroker = new WaveMessagingBroker (name, ipAddress, port);

        waveAssert (NULL != pWaveMessagingBroker, __FILE__, __LINE__);

        m_waveMessagingBrokersMapByName[name]                                    = pWaveMessagingBroker;
        m_waveMessagingBrokersMapByUniqueString[waveMessagingBrokerUniqueString] = pWaveMessagingBroker;
    }

    m_waveMessagingBrokersMutex.unlock();

    return (isNewBrokerNeeded);
}

void WaveMessagingBrokerRepository::addBroker (const string& name, const string &ipAddress, const SI32 &port)
{
    bool   isKnownByName                   = false;
    bool   isKnownByUniqueString           = false;
    string waveMessagingBrokerUniqueString = getWaveMessagingBrokerUniqueString (ipAddress, port);

    m_waveMessagingBrokersMutex.lock ();

    map<string, WaveMessagingBroker *>::const_iterator element    = m_waveMessagingBrokersMapByName.find (name);
    map<string, WaveMessagingBroker *>::const_iterator endElement = m_waveMessagingBrokersMapByName.end  ();

    if (endElement != element)
    {
        isKnownByName = true;
    }
    else
    {
        isKnownByName = false;
    }

    map<string, WaveMessagingBroker *>::const_iterator element1    = m_waveMessagingBrokersMapByUniqueString.find (waveMessagingBrokerUniqueString);
    map<string, WaveMessagingBroker *>::const_iterator endElement1 = m_waveMessagingBrokersMapByUniqueString.end  ();

    if (endElement1 != element1)
    {
        isKnownByUniqueString = true;
    }
    else
    {
        isKnownByUniqueString = false;
    }

    waveAssert (isKnownByName == isKnownByUniqueString, __FILE__, __LINE__);

    if (false == isKnownByName)
    {
        WaveMessagingBroker *pWaveMessagingBroker = new WaveMessagingBroker (name, ipAddress, port);

        waveAssert (NULL != pWaveMessagingBroker, __FILE__, __LINE__);

        m_waveMessagingBrokersMapByName[name]                                    = pWaveMessagingBroker;
        m_waveMessagingBrokersMapByUniqueString[waveMessagingBrokerUniqueString] = pWaveMessagingBroker;
    }
    else
    {
        waveAssert (false, __FILE__, __LINE__);
    }

    m_waveMessagingBrokersMutex.unlock();
}

void WaveMessagingBrokerRepository::removeBroker (const string& name)
{
    bool                 isKnownByName                    = false;
    bool                 isKnownByUniqueString            = false;
    string               waveMessagingBrokerUniqueString;
    WaveMessagingBroker *pWaveMessagingBroker             = NULL;

    m_waveMessagingBrokersMutex.lock ();

    map<string, WaveMessagingBroker *>::iterator element    = m_waveMessagingBrokersMapByName.find (name);
    map<string, WaveMessagingBroker *>::iterator endElement = m_waveMessagingBrokersMapByName.end  ();

    if (endElement != element)
    {
        isKnownByName = true;

        pWaveMessagingBroker = element->second;

        waveAssert (NULL != pWaveMessagingBroker, __FILE__, __LINE__);

        waveMessagingBrokerUniqueString = pWaveMessagingBroker->getUniqueString ();
    }
    else
    {
        isKnownByName = false;
    }

    map<string, WaveMessagingBroker *>::iterator element1    = m_waveMessagingBrokersMapByUniqueString.find (waveMessagingBrokerUniqueString);
    map<string, WaveMessagingBroker *>::iterator endElement1 = m_waveMessagingBrokersMapByUniqueString.end  ();

    if (endElement1 != element1)
    {
        isKnownByUniqueString = true;
    }
    else
    {
        isKnownByUniqueString = false;
    }

    waveAssert (isKnownByName == isKnownByUniqueString, __FILE__, __LINE__);

    if (true == isKnownByName)
    {
        m_waveMessagingBrokersMapByName.erase (element);
        m_waveMessagingBrokersMapByUniqueString.erase (element1);
    }
    else
    {
        waveAssert (false, __FILE__, __LINE__);
    }

    m_waveMessagingBrokersMutex.unlock();
}

WaveMessagingBroker *WaveMessagingBrokerRepository::checkoutBroker (const string &brokerName)
{
    bool                 isKnownByName                    = false;
    bool                 isKnownByUniqueString            = false;
    string               waveMessagingBrokerUniqueString;
    WaveMessagingBroker *pWaveMessagingBroker             = NULL;

    m_waveMessagingBrokersMutex.lock ();

    map<string, WaveMessagingBroker *>::iterator element    = m_waveMessagingBrokersMapByName.find (brokerName);
    map<string, WaveMessagingBroker *>::iterator endElement = m_waveMessagingBrokersMapByName.end  ();

    if (endElement != element)
    {
        isKnownByName = true;

        pWaveMessagingBroker = element->second;

        waveAssert (NULL != pWaveMessagingBroker, __FILE__, __LINE__);

        waveMessagingBrokerUniqueString = pWaveMessagingBroker->getUniqueString ();
    }
    else
    {
        isKnownByName = false;
    }

    map<string, WaveMessagingBroker *>::iterator element1    = m_waveMessagingBrokersMapByUniqueString.find (waveMessagingBrokerUniqueString);
    map<string, WaveMessagingBroker *>::iterator endElement1 = m_waveMessagingBrokersMapByUniqueString.end  ();

    if (endElement1 != element1)
    {
        isKnownByUniqueString = true;
    }
    else
    {
        isKnownByUniqueString = false;
    }

    waveAssert (isKnownByName == isKnownByUniqueString, __FILE__, __LINE__);

    if (true == isKnownByName)
    {
        pWaveMessagingBroker->checkout ();
    }

    m_waveMessagingBrokersMutex.unlock();

    return (pWaveMessagingBroker);
}

WaveMessagingBroker *WaveMessagingBrokerRepository::checkoutBroker (const string &ipAddress, const SI32 &port)
{
    bool                 isKnownByName                    = false;
    bool                 isKnownByUniqueString            = false;
    string               waveMessagingBrokerUniqueString  = getWaveMessagingBrokerUniqueString (ipAddress, port);
    string               brokerName;
    WaveMessagingBroker *pWaveMessagingBroker             = NULL;

    m_waveMessagingBrokersMutex.lock ();

    map<string, WaveMessagingBroker *>::iterator element1    = m_waveMessagingBrokersMapByUniqueString.find (waveMessagingBrokerUniqueString);
    map<string, WaveMessagingBroker *>::iterator endElement1 = m_waveMessagingBrokersMapByUniqueString.end  ();

    if (endElement1 != element1)
    {
        isKnownByUniqueString = true;

        pWaveMessagingBroker = element1->second;

        waveAssert (NULL != pWaveMessagingBroker, __FILE__, __LINE__);

        brokerName = pWaveMessagingBroker->getName ();
    }
    else
    {
        isKnownByUniqueString = false;
    }

    map<string, WaveMessagingBroker *>::iterator element    = m_waveMessagingBrokersMapByName.find (brokerName);
    map<string, WaveMessagingBroker *>::iterator endElement = m_waveMessagingBrokersMapByName.end  ();

    if (endElement != element)
    {
        isKnownByName = true;
    }
    else
    {
        isKnownByName = false;
    }

    waveAssert (isKnownByName == isKnownByUniqueString, __FILE__, __LINE__);

    if (true == isKnownByName)
    {
        pWaveMessagingBroker->checkout ();
    }
    else
    {
        waveAssert (false, __FILE__, __LINE__);
    }

    m_waveMessagingBrokersMutex.unlock();

    return (pWaveMessagingBroker);
}

void WaveMessagingBrokerRepository::checkinBroker (WaveMessagingBroker *pWaveMessagingBroker)
{
    waveAssert (NULL != pWaveMessagingBroker, __FILE__, __LINE__);

    string               brokerName                       = pWaveMessagingBroker->getName ();
    bool                 isKnownByName                    = false;
    bool                 isKnownByUniqueString            = false;
    string               waveMessagingBrokerUniqueString;
    WaveMessagingBroker *pWaveMessagingBroker1            = NULL;

    m_waveMessagingBrokersMutex.lock ();

    map<string, WaveMessagingBroker *>::iterator element    = m_waveMessagingBrokersMapByName.find (brokerName);
    map<string, WaveMessagingBroker *>::iterator endElement = m_waveMessagingBrokersMapByName.end  ();

    if (endElement != element)
    {
        isKnownByName = true;

        pWaveMessagingBroker1 = element->second;

        waveAssert (NULL != pWaveMessagingBroker1, __FILE__, __LINE__);

        waveMessagingBrokerUniqueString = pWaveMessagingBroker1->getUniqueString ();
    }
    else
    {
        isKnownByName = false;
    }

    map<string, WaveMessagingBroker *>::iterator element1    = m_waveMessagingBrokersMapByUniqueString.find (waveMessagingBrokerUniqueString);
    map<string, WaveMessagingBroker *>::iterator endElement1 = m_waveMessagingBrokersMapByUniqueString.end  ();

    if (endElement1 != element1)
    {
        isKnownByUniqueString = true;
    }
    else
    {
        isKnownByUniqueString = false;
    }

    waveAssert (isKnownByName == isKnownByUniqueString, __FILE__, __LINE__);

    if (true == isKnownByName)
    {
        pWaveMessagingBroker1->checkin ();
    }
    else
    {
        waveAssert (false, __FILE__, __LINE__);
    }

    m_waveMessagingBrokersMutex.unlock();
}

WaveMessageBrokerStatus WaveMessagingBrokerRepository::subscribeToMessageBroker (const string &brokerName, const vector<string> &topicNames)
{
    WaveMessagingBrokerRepository *pWaveMessagingBrokerRepository = getInstance ();

    waveAssert (NULL != pWaveMessagingBrokerRepository, __FILE__, __LINE__);

    WaveMessagingBroker *pWaveMessagingBroker = pWaveMessagingBrokerRepository->checkoutBroker (brokerName);

    if (NULL == pWaveMessagingBroker)
    {
        return (WAVE_MESSAGE_BROKER_ERROR_UNKNOWN);
    }

    WaveBrokerSubscribeMessage *pWaveBrokerSubscribeMessage = new WaveBrokerSubscribeMessage (topicNames);

    waveAssert (NULL != pWaveBrokerSubscribeMessage, __FILE__, __LINE__);

    bool status = (*pWaveMessagingBroker) << pWaveBrokerSubscribeMessage;

    if (true == status)
    {
        return (WAVE_MESSAGE_BROKER_SUCCESS);
    }
    else
    {
        return (WAVE_MESSAGE_BROKER_ERROR_REQUEST_CACHED);
    }
}

WaveMessageBrokerStatus WaveMessagingBrokerRepository::subscribeToMessageBroker (const string &brokerName, const string &topicName)
{
    vector<string> topicNames;

    topicNames.push_back (topicName);

    return (subscribeToMessageBroker (brokerName, topicNames));
}

WaveMessageBrokerStatus WaveMessagingBrokerRepository::publishToMessageBroker (const string &brokerName, WaveBrokerPublishMessage *pWaveBrokerPublishMessage)
{
    WaveMessagingBrokerRepository *pWaveMessagingBrokerRepository = getInstance ();

    waveAssert (NULL != pWaveMessagingBrokerRepository, __FILE__, __LINE__);

    WaveMessagingBroker *pWaveMessagingBroker = pWaveMessagingBrokerRepository->checkoutBroker (brokerName);

    if (NULL == pWaveMessagingBroker)
    {
        return (WAVE_MESSAGE_BROKER_ERROR_UNKNOWN);
    }

    bool status = (*pWaveMessagingBroker) << pWaveBrokerPublishMessage;

    if (true == status)
    {
        return (WAVE_MESSAGE_BROKER_SUCCESS);
    }
    else
    {
        return (WAVE_MESSAGE_BROKER_ERROR_PUBLISHING_MESSAGE);
    }
}

string WaveMessagingBrokerRepository::getBrokerName (const string &ipAddress, const SI32 &port)
{
    string brokerName;
    string uniqueString = getWaveMessagingBrokerUniqueString (ipAddress, port);

    m_waveMessagingBrokersMutex.lock ();

    map<string, WaveMessagingBroker *>::const_iterator element    = m_waveMessagingBrokersMapByUniqueString.find (uniqueString);
    map<string, WaveMessagingBroker *>::const_iterator endElement = m_waveMessagingBrokersMapByUniqueString.end  ();

    if (endElement != element)
    {
        WaveMessagingBroker *pWaveMessagingBroker = element->second;

        waveAssert (NULL != pWaveMessagingBroker, __FILE__, __LINE__);

        brokerName = pWaveMessagingBroker->getName ();
    }

    m_waveMessagingBrokersMutex.unlock();

    return (brokerName);
}


}

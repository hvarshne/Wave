/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveBrokerBasedMessage.h"
#include "Framework/Attributes/AttributeResourceId.h"

#include <string.h>

namespace WaveNs
{

WaveBrokerBasedMessage::WaveBrokerBasedMessageBuffer::WaveBrokerBasedMessageBuffer (UI32 size, const void *pBuffer, bool ownedByMessage)
    : m_size (size),
      m_pBuffer ((void *) pBuffer)
{
    if (false == ownedByMessage)
    {
        m_pBuffer = new UI8[size];
        memcpy (m_pBuffer, pBuffer, size);
    }
}

WaveBrokerBasedMessage::WaveBrokerBasedMessageBuffer::WaveBrokerBasedMessageBuffer (const WaveBrokerBasedMessage::WaveBrokerBasedMessageBuffer &waveMessagebuffer)
{
    m_size    = waveMessagebuffer.m_size;

    m_pBuffer = new UI8[m_size];
    memcpy (m_pBuffer, waveMessagebuffer.m_pBuffer, m_size);
}

WaveBrokerBasedMessage::WaveBrokerBasedMessageBuffer::~WaveBrokerBasedMessageBuffer ()
{
    destroy ();
}

WaveBrokerBasedMessage::WaveBrokerBasedMessageBuffer &WaveBrokerBasedMessage::WaveBrokerBasedMessageBuffer::operator = (const WaveBrokerBasedMessage::WaveBrokerBasedMessageBuffer &waveMessagebuffer)
{
    destroy ();

    m_size    = waveMessagebuffer.m_size;

    m_pBuffer = new UI8[m_size];
    memcpy (m_pBuffer, waveMessagebuffer.m_pBuffer, m_size);

    return (*this);
}

void WaveBrokerBasedMessage::WaveBrokerBasedMessageBuffer::destroy ()
{
    m_size = 0;

    if (NULL != m_pBuffer)
    {
        delete[] (reinterpret_cast<UI8 *> (m_pBuffer));
        m_pBuffer = NULL;
    }
}

void WaveBrokerBasedMessage::WaveBrokerBasedMessageBuffer::invalidateBuffer ()
{
    m_size    = 0;
    m_pBuffer = NULL;
}

UI32 WaveBrokerBasedMessage::WaveBrokerBasedMessageBuffer::getSize () const
{
    return (m_size);
}

void *WaveBrokerBasedMessage::WaveBrokerBasedMessageBuffer::getPBuffer () const
{
    return (m_pBuffer);
}

void WaveBrokerBasedMessage::WaveBrokerBasedMessageBuffer::setPBuffer (void *pBuffer)
{
    m_pBuffer = pBuffer;
}

WaveBrokerBasedMessage::WaveBrokerBasedMessage ()
    : SerializableObject (),
      m_waveBrokerBasedMessageType (WAVE_BROKER_BASED_MESSAGING_BUS_MESSAGE_TYPE_UNKNOWN)
{
}

WaveBrokerBasedMessage::WaveBrokerBasedMessage (const WaveBrokerBasedMessageType &waveBrokerBasedMessageType)
    : SerializableObject (),
      m_waveBrokerBasedMessageType (waveBrokerBasedMessageType)
{
}

WaveBrokerBasedMessage::~WaveBrokerBasedMessage ()
{
}

WaveBrokerBasedMessageType WaveBrokerBasedMessage::getWaveBrokerBasedMessageType () const
{
    return (m_waveBrokerBasedMessageType);
}

void WaveBrokerBasedMessage::setWaveBrokerBasedMessageType (const WaveBrokerBasedMessageType &waveBrokerBasedMessageType)
{
    m_waveBrokerBasedMessageType = waveBrokerBasedMessageType;
}

void WaveBrokerBasedMessage::setupAttributesForSerialization ()
{
    SerializableObject::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeResourceId ((UI32 *) &m_waveBrokerBasedMessageType, "waveBrokerBasedMessageType"));
}

UI32 WaveBrokerBasedMessage::getNumberOfBuffers () const
{
    return (m_buffers.size ());
}

void WaveBrokerBasedMessage::getBufferTags (vector<UI32> &bufferTagsVector) const
{
    map<UI32, WaveBrokerBasedMessageBuffer *>::const_iterator limitingElement = m_buffers.end ();
    map<UI32, WaveBrokerBasedMessageBuffer *>::const_iterator element         = m_buffers.begin ();

    while (element != limitingElement)
    {
        bufferTagsVector.push_back (element->first);

        element++;
    }
}

void WaveBrokerBasedMessage::removeAllBuffers ()
{
    map<UI32, WaveBrokerBasedMessageBuffer *>::iterator  element                       = m_buffers.begin () ;
    map<UI32, WaveBrokerBasedMessageBuffer *>::iterator  limitingElement               = m_buffers.end   ();
    WaveBrokerBasedMessageBuffer                        *pWaveBrokerBasedMessageBuffer = NULL;

    while (element != limitingElement)
    {
        pWaveBrokerBasedMessageBuffer = element->second;
        delete pWaveBrokerBasedMessageBuffer;

        element++;
    }

    m_buffers.clear ();
}

void WaveBrokerBasedMessage::transferAllBuffers (WaveBrokerBasedMessage *pWaveBrokerBasedMessage)
{
    if (this == pWaveBrokerBasedMessage)
    {
        waveAssert (false, __FILE__, __LINE__);
        return;
    }

    map<UI32, WaveBrokerBasedMessageBuffer *>::iterator  element                       = m_buffers.begin () ;
    map<UI32, WaveBrokerBasedMessageBuffer *>::iterator  limitingElement               = m_buffers.end   ();
    UI32                                                 bufferTag;
    WaveBrokerBasedMessageBuffer                        *pWaveBrokerBasedMessageBuffer = NULL;

    while (element != limitingElement)
    {
        bufferTag                     = element->first;
        pWaveBrokerBasedMessageBuffer = element->second;

        pWaveBrokerBasedMessage->addBuffer (bufferTag, pWaveBrokerBasedMessageBuffer->getSize (), pWaveBrokerBasedMessageBuffer->getPBuffer (), true);

        pWaveBrokerBasedMessageBuffer->setPBuffer (NULL);
        delete pWaveBrokerBasedMessageBuffer;

        element++;
    }

    m_buffers.clear ();
}

WaveMessageStatus WaveBrokerBasedMessage::addBuffer (UI32 tag, UI32 size, const void *pBuffer, bool bufferWillBeOwnedByMessage)
{
    UI32  tempSize;
    void *pTempBuffer = NULL;

    if (NULL == pBuffer)
    {
        cout << "WaveMessage::addBuffer : Cannot add NULL buffer to a WaveMessage." << endl;
        waveAssert (false, __FILE__, __LINE__);

        return (WAVE_MESSAGE_ERROR_ADDING_NULL_BUFFER);
    }

    pTempBuffer = findBuffer (tag, tempSize);

    if (NULL != pTempBuffer)
    {
        cout << "WaveMessage::addBuffer : A buffer already exists with the tag (" << tag << ")." << endl;
        waveAssert (false, __FILE__, __LINE__);

        return (WAVE_MESSAGE_ERROR_BUFFER_WITH_TAG_EXISTS);
    }
    else
    {
        WaveBrokerBasedMessageBuffer *pWaveBrokerBasedMessageBuffer = new WaveBrokerBasedMessageBuffer (size, pBuffer, bufferWillBeOwnedByMessage);

        m_buffers[tag] = pWaveBrokerBasedMessageBuffer;

        return (WAVE_MESSAGE_SUCCESS);
    }
}

void *WaveBrokerBasedMessage::findBuffer (UI32 tag, UI32 &size) const
{
    map<UI32, WaveBrokerBasedMessageBuffer *>::const_iterator limitingElement = m_buffers.end ();
    map<UI32, WaveBrokerBasedMessageBuffer *>::const_iterator element         = m_buffers.find (tag);

    if (limitingElement != element)
    {
        WaveBrokerBasedMessageBuffer *pWaveBrokerBasedMessageBuffer = element->second;

        size = pWaveBrokerBasedMessageBuffer->getSize ();

        return (pWaveBrokerBasedMessageBuffer->getPBuffer ());
    }
    else
    {
        size = 0;

        return (NULL);
    }
}

void *WaveBrokerBasedMessage::transferBufferToUser (UI32 tag, UI32 &size)
{
    map<UI32, WaveBrokerBasedMessageBuffer *>::iterator limitingElement = m_buffers.end ();
    map<UI32, WaveBrokerBasedMessageBuffer *>::iterator element         = m_buffers.find (tag);

    if (limitingElement != element)
    {
        WaveBrokerBasedMessageBuffer *pWaveBrokerBasedMessageBuffer = element->second;
        void                         *pTempBuffer                   = pWaveBrokerBasedMessageBuffer->getPBuffer ();

        m_buffers.erase (element);
        size = pWaveBrokerBasedMessageBuffer->getSize ();
        pWaveBrokerBasedMessageBuffer->invalidateBuffer ();
        delete pWaveBrokerBasedMessageBuffer;

        return (pTempBuffer);
    }
    else
    {
        size = 0;

        return (NULL);
    }
}

WaveMessageStatus WaveBrokerBasedMessage::removeBuffer (UI32 tag)
{
    UI32  tempSize;
    void *pTempBuffer = NULL;

    pTempBuffer = findBuffer (tag, tempSize);

    if (NULL == pTempBuffer)
    {
        cout << "WaveMessage::addBuffer : A buffer does not exist with the tag (" << tag << ")." << endl;
        waveAssert (false, __FILE__, __LINE__);

        return (WAVE_MESSAGE_ERROR_BUFFER_WITH_TAG_DOES_NOT_EXIST);
    }
    else
    {
        map<UI32, WaveBrokerBasedMessageBuffer *>::iterator element = m_buffers.find (tag);

        WaveBrokerBasedMessageBuffer *pWaveBrokerBasedMessageBuffer = element->second;
        m_buffers.erase (element);
        delete pWaveBrokerBasedMessageBuffer;

        return (WAVE_MESSAGE_SUCCESS);
    }
}

WaveBrokerBasedMessageType WaveBrokerBasedMessage::getWaveBrokerBasedMessageType (const char *pSerializedData)
{
    static const char *pAttributeStringAtBegining = "<AwaveBrokerBasedMessageType>";
    static const char *pAttributeStringAtEnding   = "</AwaveBrokerBasedMessageType>";
    static       char  sotString[256];

    const char *pBegin = strstr (pSerializedData, pAttributeStringAtBegining);
    const char *pValue = pBegin + strlen (pAttributeStringAtBegining);
    const char *pEnd   = strstr (pValue, pAttributeStringAtEnding);

    static WaveBrokerBasedMessageType waveBrokerBasedMessageType = WAVE_BROKER_BASED_MESSAGING_BUS_MESSAGE_TYPE_UNKNOWN;
    static AttributeResourceId        attributeResourceId          (waveBrokerBasedMessageType);

    UI32 valueSize = pEnd - pValue;

    strncpy (sotString, pValue, valueSize);

    sotString[valueSize] = '\0';

    attributeResourceId.fromString (sotString);

    WaveBrokerBasedMessageType *pWaveBrokerBasedMessageType = (WaveBrokerBasedMessageType *) attributeResourceId.getPData ();

    return (*pWaveBrokerBasedMessageType);
}

#if 0
WaveBrokerBasedMessageType WaveBrokerBasedMessage::getWaveBrokerBasedMessageType (const string &serializedData)
{
        SI32   index1                = 0;
        SI32   index2                = 0;
    static string attributeTag          = "waveBrokerBasedMessageType";
    static string attributeTagBeginning = "<A"  + attributeTag + ">";
    static string attributeTagEnding    = "</A" + attributeTag + ">";

    static UI32   startIndexOffset      = attributeTagBeginning.size ();

    index1    = serializedData.find (attributeTagBeginning);
    index2    = serializedData.find (attributeTagEnding);

    string sotString = serializedData.substr (index1 + startIndexOffset, index2 - index1 - startIndexOffset);

    static WaveBrokerBasedMessageType waveBrokerBasedMessageType = WAVE_BROKER_BASED_MESSAGING_BUS_MESSAGE_TYPE_UNKNOWN;
    static AttributeResourceId        attributeResourceId          (waveBrokerBasedMessageType);

    attributeResourceId.fromString (sotString);

    WaveBrokerBasedMessageType *pWaveBrokerBasedMessageType = (WaveBrokerBasedMessageType *) attributeResourceId.getPData ();

    return (*pWaveBrokerBasedMessageType);
}
#endif

string WaveBrokerBasedMessage::getTopicName (const char *pSerializedData)
{
    static const char *pAttributeStringAtBegining = "<AtopicName>";
    static const char *pAttributeStringAtEnding   = "</AtopicName>";
    static       char  sotString[256];

    const char *pBegin = strstr (pSerializedData, pAttributeStringAtBegining);
    const char *pValue = pBegin + strlen (pAttributeStringAtBegining);
    const char *pEnd   = strstr (pValue, pAttributeStringAtEnding);

    UI32 valueSize = pEnd - pValue;

    strncpy (sotString, pValue, valueSize);

    sotString[valueSize] = '\0';

    return (sotString);
}

#if 0
string WaveBrokerBasedMessage::getTopicName (const string &serializedData)
{
           SI32   index1                = 0;
           SI32   index2                = 0;
    static string attributeTag          = "topicName";
    static string attributeTagBeginning = "<A"  + attributeTag + ">";
    static string attributeTagEnding    = "</A" + attributeTag + ">";

    static UI32   startIndexOffset      = attributeTagBeginning.size ();

    index1    = serializedData.find (attributeTagBeginning);
    index2    = serializedData.find (attributeTagEnding);

    string sotString = serializedData.substr (index1 + startIndexOffset, index2 - index1 - startIndexOffset);

    static AttributeString attributeString ("");

    attributeString.fromString (sotString);

    string *pString = (string *) attributeString.getPData ();

    return (*pString);
}
#endif

}

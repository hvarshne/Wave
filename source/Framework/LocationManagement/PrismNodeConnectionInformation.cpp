/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/LocationManagement/PrismNodeConnectionInformation.h"

namespace WaveNs
{

PrismNodeConnectionInformation::PrismNodeConnectionInformation ()
    : SerializableObject (),
      m_thisLocationServerIpAddress (""),
      m_thisLocationServerPort (0),
      m_expectedLocationId (256),
      m_messageVersion ("")
{
}

PrismNodeConnectionInformation::PrismNodeConnectionInformation (const string &thisLocationServerIpAddress, const UI32 &thisLocationServerPort, const LocationId &expectedLocationId, const string &messageVersion)
    : SerializableObject (),
      m_thisLocationServerIpAddress (thisLocationServerIpAddress),
      m_thisLocationServerPort (thisLocationServerPort),
      m_expectedLocationId (expectedLocationId),
      m_messageVersion     (messageVersion)
{
}

PrismNodeConnectionInformation::~PrismNodeConnectionInformation ()
{
}

void PrismNodeConnectionInformation::setupAttributesForSerialization ()
{
    SerializableObject::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeString (&m_thisLocationServerIpAddress,  "thisLocationServerIpAddress"));
    addSerializableAttribute (new AttributeUI32   (&m_thisLocationServerPort,       "thisLocationServerPort"));
    addSerializableAttribute (new AttributeLocationId   (&m_expectedLocationId,     "expectedLocationId"));
    addSerializableAttribute (new AttributeString       (&m_messageVersion,         "messageVersion"));
}
 
string PrismNodeConnectionInformation::getThisLocationServerIpAddress () const
{
    return (m_thisLocationServerIpAddress);
}

void PrismNodeConnectionInformation::setThisLocationServerIpAddress (const string &thisLocationServerIpAddress)
{
    m_thisLocationServerIpAddress = thisLocationServerIpAddress;
}

UI32 PrismNodeConnectionInformation::getThisLocationServerPort () const
{
    return (m_thisLocationServerPort);
}

void PrismNodeConnectionInformation::setThisLocationServerPort (const UI32 &thisLocationServerPort)
{
    m_thisLocationServerPort = thisLocationServerPort;
}

LocationId PrismNodeConnectionInformation::getExpectedLocationId () const
{
    return (m_expectedLocationId);
}

void PrismNodeConnectionInformation::setExpectedLocationId (const LocationId &expectedLocationId)
{
    m_expectedLocationId = expectedLocationId;
}

string PrismNodeConnectionInformation::getMessageVersion () const
{
    return (m_messageVersion); 
}

void PrismNodeConnectionInformation::setMessageVersion (const string &messageVersion) 
{
    m_messageVersion = messageVersion;
}

PrismHaNodeConnectionInformation::PrismHaNodeConnectionInformation ()
    : SerializableObject (),
      m_thisLocationServerIpAddress (""),
      m_thisLocationServerPort (0),
      m_expectedLocationId (256),
      m_messageVersion ("")
{
}

PrismHaNodeConnectionInformation::PrismHaNodeConnectionInformation (const string &thisLocationServerIpAddress, const UI32 &thisLocationServerPort, const LocationId &expectedLocationId, const string &messageVersion)
    : SerializableObject (),
      m_thisLocationServerIpAddress (thisLocationServerIpAddress),
      m_thisLocationServerPort (thisLocationServerPort),
      m_expectedLocationId (expectedLocationId),
      m_messageVersion (messageVersion)
{
}

PrismHaNodeConnectionInformation::~PrismHaNodeConnectionInformation ()
{
}

void PrismHaNodeConnectionInformation::setupAttributesForSerialization ()
{
    SerializableObject::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeString (&m_thisLocationServerIpAddress,  "thisLocationServerIpAddress"));
    addSerializableAttribute (new AttributeUI32   (&m_thisLocationServerPort,       "thisLocationServerPort"));
    addSerializableAttribute (new AttributeLocationId   (&m_expectedLocationId,     "expectedLocationId"));
    addSerializableAttribute (new AttributeString (&m_messageVersion,               "messageVersion"));
}

void PrismHaNodeConnectionInformation::setupAttributesForSerializationInAttributeOrderFormat ()
{
    SerializableObject::setupAttributesForSerializationInAttributeOrderFormat ();
    
    addAttributeNameForOrderToNameMapping ("thisLocationServerIpAddress");
    addAttributeNameForOrderToNameMapping ("thisLocationServerPort");
    addAttributeNameForOrderToNameMapping ("expectedLocationId");
    addAttributeNameForOrderToNameMapping ("messageVersion");
}

string PrismHaNodeConnectionInformation::getThisLocationServerIpAddress () const
{
    return (m_thisLocationServerIpAddress);
}

void PrismHaNodeConnectionInformation::setThisLocationServerIpAddress (const string &thisLocationServerIpAddress)
{
    m_thisLocationServerIpAddress = thisLocationServerIpAddress;
}

UI32 PrismHaNodeConnectionInformation::getThisLocationServerPort () const
{
    return (m_thisLocationServerPort);
}

void PrismHaNodeConnectionInformation::setThisLocationServerPort (const UI32 &thisLocationServerPort)
{
    m_thisLocationServerPort = thisLocationServerPort;
}

LocationId PrismHaNodeConnectionInformation::getExpectedLocationId () const
{
    return (m_expectedLocationId);
}

void PrismHaNodeConnectionInformation::setExpectedLocationId (const LocationId &expectedLocationId)
{
    m_expectedLocationId = expectedLocationId;
}

string PrismHaNodeConnectionInformation::getMessageVersion () const
{
    return (m_messageVersion);
}

void PrismHaNodeConnectionInformation::setMessageVersion (const string &messageVersion)
{
    m_messageVersion = messageVersion;
}

}

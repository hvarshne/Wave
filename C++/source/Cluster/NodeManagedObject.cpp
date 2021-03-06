/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Amr Sabaa                                                    *
 ***************************************************************************/

#include "Framework/Core/WaveFrameworkMessages.h"
#include "Cluster/NodeManagedObject.h"


namespace WaveNs
{

NodeManagedObject::NodeManagedObject (WaveObjectManager *pWaveObjectManager)
    : WaveElement (pWaveObjectManager),
      WavePersistableObject (NodeManagedObject::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject (pWaveObjectManager)
{
    setGenericStatus (WAVE_MANAGED_OBJECT_GENERIC_STATUS_GOOD);

    m_locationId                 = 0;
    m_nodeName                   = string("NO NAME");
    m_nodePort                   = 0;
}
/*
NodeManagedObject::NodeManagedObject (WaveObjectManager *pWaveObjectManager, string nodeName)
    : WaveElement (pWaveObjectManager),
      WaveManagedObject (pWaveObjectManager),
      m_nodeName (nodeName)
{
    m_genericStatus             = NODE_CREATED;

}
*/
NodeManagedObject::NodeManagedObject (WaveObjectManager *pWaveObjectManager, LocationId locationId, string nodeName, UI32 nodePort)
    : WaveElement (pWaveObjectManager),
      WavePersistableObject (NodeManagedObject::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject (pWaveObjectManager),
      m_locationId (locationId),
      m_nodeName (nodeName),
      m_nodePort (nodePort)
{
    setGenericStatus (WAVE_MANAGED_OBJECT_GENERIC_STATUS_GOOD);
}

NodeManagedObject::NodeManagedObject (const NodeManagedObject &rhs)
    : WaveElement (rhs.m_pWaveObjectManager),
      WavePersistableObject (NodeManagedObject::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject (rhs.m_pWaveObjectManager)
{
    setGenericStatus (rhs.getGenericStatus ());

    m_locationId    = rhs.m_locationId;
    m_nodeName      = rhs.m_nodeName;
    m_nodePort      = rhs.m_nodePort;
}

void NodeManagedObject::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeLocationId (&m_locationId, "locationId"));
    addPersistableAttribute (new AttributeString     (&m_nodeName,   "nodeName"));
    addPersistableAttribute (new AttributeUI32       (&m_nodePort,   "nodePort"));
}

void NodeManagedObject::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeLocationId (&m_locationId, "locationId"));
    addPersistableAttributeForCreate (new AttributeString     (&m_nodeName,   "nodeName"));
    addPersistableAttributeForCreate (new AttributeUI32       (&m_nodePort,   "nodePort"));
}

NodeManagedObject::~NodeManagedObject ()
{
}

string NodeManagedObject::getClassName ()
{
    return ("NodeManagedObject");
}

ResourceId NodeManagedObject::getNodeGenericStatus ()
{
    return (getGenericStatus ());
}
void NodeManagedObject::setNodeGenericStatus (ResourceId status)
{
    setGenericStatus (status);
}

LocationId NodeManagedObject::getLocationId () const
{
    return (m_locationId);
}

void NodeManagedObject::setLocationId (const LocationId &locationId)
{
    m_locationId = locationId;
}

string NodeManagedObject::getNodeName ()
{
    return (m_nodeName);
}

void NodeManagedObject::setNodeName (string nodeName)
{
    m_nodeName = nodeName;
}

UI32 NodeManagedObject::getNodePort ()
{
    return (m_nodePort);
}

void NodeManagedObject::setNodePort (UI32 nodePort)
{
    m_nodePort  =   nodePort;
}

NodeManagedObject &NodeManagedObject::operator = (const NodeManagedObject &rhs)
{
    m_locationId  = rhs.m_locationId;
    m_nodeName    = rhs.m_nodeName;
    m_nodePort    = rhs.m_nodePort;

    return (*this);
}

bool NodeManagedObject::operator == (const NodeManagedObject &rhs)
{
    if ((m_locationId == rhs.m_locationId) && (m_nodeName == rhs.m_nodeName) && (m_nodePort == rhs.m_nodePort))
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

bool NodeManagedObject::operator != (const NodeManagedObject &rhs)
{
    if ((m_locationId == rhs.m_locationId) && (m_nodeName == rhs.m_nodeName) && (m_nodePort == rhs.m_nodePort))
    {
        return (false);
    }
    else
    {
        return (true);
    }
}



Node::Node ()
{
    m_nodeName          = string("NO NAME");
    m_nodePort          = 1234;
}

Node::Node (string nodeName, UI32 nodePort)
{
    m_nodeName          = nodeName;
    m_nodePort          = nodePort;
}

Node::~Node ()
{
}


string Node::getNodeName ()
{
    return (m_nodeName);
}

void Node::setNodeName (string nodeName)
{
    m_nodeName = nodeName;
}

UI32 Node::getNodePort ()
{
    return (m_nodePort);
}

void Node::setNodePort (UI32 nodePort)
{
    m_nodePort  =   nodePort;
}


Node &Node::operator = (const Node &rhs)
{
    m_nodeName    = rhs.m_nodeName;
    m_nodePort    = rhs.m_nodePort;

    return (*this);
}

bool Node::operator == (const Node &rhs)
{
    if ((m_nodeName == rhs.m_nodeName) && (m_nodePort == rhs.m_nodePort))
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

bool Node::operator != (const Node &rhs)
{
    if ((m_nodeName == rhs.m_nodeName) && (m_nodePort == rhs.m_nodePort))
    {
        return (false);
    }
    else
    {
        return (true);
    }
}

}

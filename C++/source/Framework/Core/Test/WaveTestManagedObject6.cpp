/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/Test/WaveTestManagedObject6.h"
#include "Framework/Attributes/AttributeManagedObjectComposition.cpp"

namespace WaveNs
{

WaveTestManagedObject6::WaveTestManagedObject6 (WaveObjectManager *pWaveObjectManager)
    : WaveElement (pWaveObjectManager),
      WavePersistableObject (WaveTestManagedObject6::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject (pWaveObjectManager),
      m_integer6        (0)
{
}

WaveTestManagedObject6::~WaveTestManagedObject6 ()
{
}

string WaveTestManagedObject6::getClassName ()
{
    return ("WaveTestManagedObject6");
}

void WaveTestManagedObject6::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeUI32                                              (&m_integer6,     "integer6"));
    addPersistableAttribute (new AttributeString                                            (&m_message6,     "message6"));
    addPersistableAttribute (new AttributeObjectId                                          (&m_objectId6,    "objectId6"));
    addPersistableAttribute (new AttributeManagedObjectComposition<WaveTestManagedObject1> (&m_composition6, "composition6", WaveTestManagedObject1::getClassName ()));
}

void WaveTestManagedObject6::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeUI32                                              (&m_integer6,     "integer6"));
    addPersistableAttributeForCreate (new AttributeString                                            (&m_message6,     "message6"));
    addPersistableAttributeForCreate (new AttributeObjectId                                          (&m_objectId6,    "objectId6"));
    addPersistableAttributeForCreate (new AttributeManagedObjectComposition<WaveTestManagedObject1> (&m_composition6, "composition6", WaveTestManagedObject1::getClassName ()));
}

void WaveTestManagedObject6::setInteger6 (const UI32 &integer6)
{
    m_integer6 = integer6;
}

void WaveTestManagedObject6::setMessage6 (const string &message6)
{
    m_message6 = message6;
}

void WaveTestManagedObject6::setObjectId6 (const ObjectId &objectId6)
{
    m_objectId6 = objectId6;
}

void WaveTestManagedObject6::setComposition6 (const WaveManagedObjectPointer<WaveTestManagedObject1> &composition6)
{
    m_composition6 = composition6;
}

UI32 WaveTestManagedObject6::getInteger6 () const
{
    return (m_integer6);
}

string WaveTestManagedObject6::getMessage6 () const
{
    return (m_message6);
}

ObjectId WaveTestManagedObject6::getObjectId6 () const
{
    return (m_objectId6);
}

WaveManagedObjectPointer<WaveTestManagedObject1> WaveTestManagedObject6::getComposition6 () const
{
    return (m_composition6);
}

bool WaveTestManagedObject6::operator == (const WaveTestManagedObject6 &rhs) const
{
    if ((rhs.getObjectId ()) != ((getObjectId ())))
    {
        return (false);
    }

    if (rhs.m_integer6 != m_integer6)
    {
        return (false);
    }

    if (rhs.m_message6 != m_message6)
    {
        return (false);
    }

    if (rhs.m_objectId6 != m_objectId6)
    {
        return (false);
    }

    if (m_composition6 != rhs.m_composition6)
    {
        return (false);
    }

    return (true);
}

bool WaveTestManagedObject6::operator != (const WaveTestManagedObject6 &rhs) const
{
    return (!(operator == (rhs)));
}

}

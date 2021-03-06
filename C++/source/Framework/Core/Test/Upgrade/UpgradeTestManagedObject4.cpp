/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/Test/Upgrade/UpgradeTestManagedObject4.h"

namespace WaveNs
{

UpgradeTestManagedObject4::UpgradeTestManagedObject4 (WaveObjectManager *pWaveObjectManager)
        : WaveElement (pWaveObjectManager),
        WavePersistableObject (UpgradeTestManagedObject4::getClassName (), UpgradeTestManagedObject1::getClassName ()),
        UpgradeTestManagedObject1 (pWaveObjectManager),
        m_integer4              (0)
{
}

UpgradeTestManagedObject4::~UpgradeTestManagedObject4 ()
{
}

string UpgradeTestManagedObject4::getClassName ()
{
    return ("UpgradeTestManagedObject4");
}

void UpgradeTestManagedObject4::setupAttributesForPersistence ()
{
    UpgradeTestManagedObject1::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeUI32                      (&m_integer4,           "integer4"));
    addPersistableAttribute (new AttributeString                    (&m_message4,           "message4"));
    addPersistableAttribute (new AttributeObjectId                  (&m_objectId4,          "objectId4"));
    addPersistableAttribute (new AttributeObjectIdAssociation       (&m_association4,       "association4", UpgradeTestManagedObject1::getClassName ()));
    addPersistableAttribute (new AttributeObjectIdVector            (&m_objectIdVector4,    "objectIdVector4"));
    addPersistableAttribute (new AttributeObjectIdVectorAssociation (&m_associationVector4, "associationVector4", getClassName (), getObjectId (), UpgradeTestManagedObject1::getClassName ()));
}

void UpgradeTestManagedObject4::setupAttributesForCreate ()
{
    addPersistableAttributeForCreate (new AttributeUI32                      (&m_integer4,           "integer4"));
    addPersistableAttributeForCreate (new AttributeString                    (&m_message4,           "message4"));
    addPersistableAttributeForCreate (new AttributeObjectId                  (&m_objectId4,          "objectId4"));
    addPersistableAttributeForCreate (new AttributeObjectIdAssociation       (&m_association4,       "association4", UpgradeTestManagedObject1::getClassName ()));
    addPersistableAttributeForCreate (new AttributeObjectIdVector            (&m_objectIdVector4,    "objectIdVector4"));
    addPersistableAttributeForCreate (new AttributeObjectIdVectorAssociation (&m_associationVector4, "associationVector4", getClassName (), getObjectId (), UpgradeTestManagedObject1::getClassName ()));
}

void UpgradeTestManagedObject4::setInteger4 (const UI32 &integer4)
{
    m_integer4 = integer4;
}

void UpgradeTestManagedObject4::setMessage4 (const string &message4)
{
    m_message4 = message4;
}

void UpgradeTestManagedObject4::setObjectId4 (const ObjectId &objectId4)
{
    m_objectId4 = objectId4;
}

void UpgradeTestManagedObject4::setAssociation4 (const ObjectId &association4)
{
    m_association4 = association4;
}

void UpgradeTestManagedObject4::setObjectIdVector4 (const vector<ObjectId> &objectVector4)
{
    m_objectIdVector4 = objectVector4;
}

void UpgradeTestManagedObject4::setAssociationVector4 (const vector<ObjectId> &objectVector4)
{
    m_associationVector4 = objectVector4;
}

UI32 UpgradeTestManagedObject4::getInteger4 () const
{
    return (m_integer4);
}

string UpgradeTestManagedObject4::getMessage4 () const
{
    return (m_message4);
}

ObjectId UpgradeTestManagedObject4::getObjectId4 () const
{
    return (m_objectId4);
}

ObjectId UpgradeTestManagedObject4::getAssociation4 () const
{
    return (m_association4);
}

vector<ObjectId> UpgradeTestManagedObject4::getObjectIdVector4 () const
{
    return (m_objectIdVector4);
}

vector<ObjectId> UpgradeTestManagedObject4::getAssociationVector4 () const
{
    return (m_associationVector4);
}

bool UpgradeTestManagedObject4::operator == (const UpgradeTestManagedObject4 &rhs) const
{
    bool isEqual = UpgradeTestManagedObject1::operator == (rhs);

    if (false == isEqual)
    {
        return (false);
    }

    if (rhs.m_integer4 != m_integer4)
    {
        return (false);
    }

    if (rhs.m_message4 != m_message4)
    {
        return (false);
    }

    if (rhs.m_objectId4 != m_objectId4)
    {
        return (false);
    }

    if (rhs.m_association4 != m_association4)
    {
        return (false);
    }

    if (rhs.m_objectIdVector4 != m_objectIdVector4)
    {
        return (false);
    }

    if (rhs.m_associationVector4 != m_associationVector4)
    {
        return (false);
    }

    return (true);
}

bool UpgradeTestManagedObject4::operator != (const UpgradeTestManagedObject4 &rhs) const
{
    return (!(operator == (rhs)));
}

}

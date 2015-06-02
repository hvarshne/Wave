/***************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                                                *
 *   All rights reserved.                                                                                                   *
 *   Author : Jitendra Singh                                                                                             *
 ***************************************************************************/

#include "Cluster/Local/WaveSlotLocalManagedObject.h"
#include "Framework/ObjectModel/WaveLocalManagedObject.h"
#include "Cluster/Local/ClusterLocalObjectManager.h"

namespace WaveNs
{

// Dummy Constructor: This should not be called
WaveSlotLocalManagedObject::WaveSlotLocalManagedObject ()
    : PrismElement               (*this),
      PrismPersistableObject     (WaveSlotLocalManagedObjectBase::getClassName (), WaveLocalManagedObject::getClassName ()),
      WaveManagedObject          (*this),
      WaveLocalManagedObjectBase (this),
      WaveLocalManagedObject     (*this),
      WaveSlotLocalManagedObjectBase (*this)
{
    setEmptyNeededOnPersistentBoot (true);
    setEmptyNeededOnPersistentBootWithDefault (false);
} 

WaveSlotLocalManagedObject::WaveSlotLocalManagedObject (ClusterLocalObjectManager *pClusterLocalObjectManager)
    : PrismElement               (pClusterLocalObjectManager),
      PrismPersistableObject     (WaveSlotLocalManagedObject::getClassName (), WaveLocalManagedObject::getClassName ()),
      WaveManagedObject          (pClusterLocalObjectManager),
      WaveLocalManagedObjectBase (this),
      WaveLocalManagedObject     (pClusterLocalObjectManager),
      WaveSlotLocalManagedObjectBase (this)
{
    setEmptyNeededOnPersistentBoot (true);
    setEmptyNeededOnPersistentBootWithDefault (false);
}

WaveSlotLocalManagedObject::WaveSlotLocalManagedObject (ClusterLocalObjectManager *pClusterLocalObjectManager, UI32 &slotNumber, UI32 &objectType, UI32 &hwType, UI32 &hwId, UI32 &slotState, UI32 &reason, UI32 &version)
    : PrismElement               (pClusterLocalObjectManager),
      PrismPersistableObject     (WaveSlotLocalManagedObject::getClassName (), WaveLocalManagedObject::getClassName ()),
      WaveManagedObject          (pClusterLocalObjectManager),
      WaveLocalManagedObjectBase (this),
      WaveLocalManagedObject     (pClusterLocalObjectManager),
      WaveSlotLocalManagedObjectBase (this, slotNumber, objectType, hwType, hwId, slotState, reason, version)
{
    setEmptyNeededOnPersistentBoot (true);
    setEmptyNeededOnPersistentBootWithDefault (false);
}

WaveSlotLocalManagedObject::~WaveSlotLocalManagedObject ()
{
}

string WaveSlotLocalManagedObject::getClassName ()
{
    return ("WaveSlotLocalManagedObject");
}

void WaveSlotLocalManagedObject::setupAttributesForPersistence ()
{
    WaveLocalManagedObject::setupAttributesForPersistence ();

    WaveSlotLocalManagedObjectBase::setupAttributesForPersistence ();
}

void WaveSlotLocalManagedObject::setupAttributesForCreate ()
{
    WaveLocalManagedObject::setupAttributesForCreate ();

    WaveSlotLocalManagedObjectBase::setupAttributesForCreate ();
}

}

/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/LoadOperationalDataContext.h"
#include "Framework/ObjectModel/WaveManagedObject.h"

namespace WaveNs
{

LoadOperationalDataContext::LoadOperationalDataContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps),
      m_pWaveManagedObject        (NULL),
      m_pOwnerWaveManagedObject   (NULL)
{
}

LoadOperationalDataContext::LoadOperationalDataContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pWaveAsynchronousContext, pWaveElement, pSteps, numberOfSteps),
      m_pWaveManagedObject        (NULL),
      m_pOwnerWaveManagedObject   (NULL)
{
}

LoadOperationalDataContext::~LoadOperationalDataContext ()
{
    if (NULL != m_pOwnerWaveManagedObject)
    {
        delete m_pOwnerWaveManagedObject;
    }
    else if (NULL != m_pWaveManagedObject)
    {
        delete m_pWaveManagedObject;
    }
}

ObjectId LoadOperationalDataContext::getWaveManagedObjectId () const
{
    return (m_waveManagedObjctId);
}

void LoadOperationalDataContext::setWaveManagedObjectId (const ObjectId &waveManagedObjectId)
{
    m_waveManagedObjctId = waveManagedObjectId;
}

vector<string> LoadOperationalDataContext::getOperationalDataFields () const
{
    return (m_operationalDataFields);
}

void LoadOperationalDataContext::setOperationalDataFields (const vector<string> &operationalDataFields)
{
    m_operationalDataFields = operationalDataFields;
}

WaveManagedObject *LoadOperationalDataContext::getPWaveManagedObject () const
{
    return (m_pWaveManagedObject);
}

void LoadOperationalDataContext::setPWaveManagedObject (WaveManagedObject *pWaveManagedObject)
{
    m_pWaveManagedObject = pWaveManagedObject;
}

WaveManagedObject *LoadOperationalDataContext::getPOwnerWaveManagedObject () const
{
    return (m_pOwnerWaveManagedObject);
}

void LoadOperationalDataContext::setPOwnerWaveManagedObject (WaveManagedObject *pOwnerWaveManagedObject)
{
    m_pOwnerWaveManagedObject = pOwnerWaveManagedObject;
}

}

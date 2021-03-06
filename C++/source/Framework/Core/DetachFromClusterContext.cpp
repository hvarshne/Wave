/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/DetachFromClusterContext.h"

namespace WaveNs
{

DetachFromClusterContext::DetachFromClusterContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext     (pWaveMessage, pWaveElement, pSteps, numberOfSteps),
      m_thisLocationRoleBeforeDetach  (LOCATION_STAND_ALONE),
      m_reasonForDetachingFromCluster (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED)
{
}

DetachFromClusterContext::DetachFromClusterContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pWaveAsynchronousContext, pWaveElement, pSteps, numberOfSteps),
      m_thisLocationRoleBeforeDetach  (LOCATION_STAND_ALONE),
      m_reasonForDetachingFromCluster (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED)
{
}

DetachFromClusterContext::~DetachFromClusterContext ()
{
}

LocationRole DetachFromClusterContext::getThisLocationRoleBeforeDetach () const
{
    return (m_thisLocationRoleBeforeDetach);
}

void DetachFromClusterContext::setThisLocationRoleBeforeDetach (const LocationRole &thisLocationRoleBeforeDetach)
{
    m_thisLocationRoleBeforeDetach = thisLocationRoleBeforeDetach;
}

FrameworkObjectManagerFailoverReason DetachFromClusterContext::getReasonForDetachingFromCluster () const
{
    return (m_reasonForDetachingFromCluster);
}

void DetachFromClusterContext::setReasonForDetachingFromCluster (const FrameworkObjectManagerFailoverReason &reasonForDetachingFromCluster)
{
    m_reasonForDetachingFromCluster = reasonForDetachingFromCluster;
}

}

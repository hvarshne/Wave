/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#include "Cluster/ClusterRejoinContext.h"

namespace WaveNs
{

ClusterRejoinContext::ClusterRejoinContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps),
    m_isReplaceRejoin             (false)
{
}

ClusterRejoinContext::~ClusterRejoinContext ()
{
}

bool ClusterRejoinContext::getIsReplaceRejoin () const
{
    return (m_isReplaceRejoin);
}

void ClusterRejoinContext::setIsReplaceRejoin (const bool &isReplaceRejoin)
{
    m_isReplaceRejoin = isReplaceRejoin;
}

}

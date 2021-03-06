/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anand Kumar Subramanian                                      *
 ***************************************************************************/

#ifndef SECONDARYNODECLUSTERCONTEXT_H
#define SECONDARYNODECLUSTERCONTEXT_H

#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Framework/Utils/WaveAsynchronousContext.h"

namespace WaveNs
{

class SecondaryNodeClusterContext: public WaveLinearSequencerContext
{
    private :
    protected :
    public :
                    SecondaryNodeClusterContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps, bool setSecondaryNodeClusterCreationFlag = true, bool clusterHaSyncInProgressFlag = false);
                    SecondaryNodeClusterContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps, bool setSecondaryNodeClusterCreationFlag = true, bool clusterHaSyncInProgressFlag = false);
        virtual    ~SecondaryNodeClusterContext ();

        bool        getClusterHaSyncInProgress  () const;
        void        setClusterHaSyncInProgress  (bool clusterHaSyncInProgressFlag);

        void        setDBEmptyRequired          (const bool &isDBEmptyRequired);
        bool        getIsDBEmptyRequired        () const;

        string      getClusterPrimaryIpAddress  ();
        SI32        getClusterPrimaryPort       ();
        LocationId  getClusterPrimaryLocationId ();

        void        setClusterPrimaryIpAddress  (const string &ipAddress);
        void        setClusterPrimaryPort       (const SI32 &port);
        void        setClusterPrimaryLocationId (const LocationId &locationId);

    // Now the data members

    private :
        bool        m_setSecondaryNodeClusterCreationFlag;
        bool        m_clusterHaSyncInProgressFlag;
        bool        m_isDBEmptyRequired;
        string      m_clusterPrimaryIpAddress;
        SI32        m_clusterPrimaryPort;
        LocationId  m_clusterPrimaryLocationId;

    protected :
    public :
};

}

#endif // SECONDARYNODECLUSTERCONTEXT_H 



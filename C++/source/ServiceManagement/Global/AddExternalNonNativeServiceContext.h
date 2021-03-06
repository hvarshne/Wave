/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef ADDEXTERNALNONNATIVESERVICECONTEXT_H
#define ADDEXTERNALNONNATIVESERVICECONTEXT_H

#include "Framework/Utils/WaveLinearSequencerContext.h"

namespace WaveNs
{

class AddExternalNonNativeServiceContext : public WaveLinearSequencerContext
{
    private :
    protected :
    public :
                 AddExternalNonNativeServiceContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual ~AddExternalNonNativeServiceContext ();

        const vector<string> &getApplicationNames () const;
              void            setApplicationNames (const vector <string> &applicationNames);

    // Now the Data Members

    private :
        vector<string> m_applicationNames;

    protected :
    public :
};

}

#endif // ADDEXTERNALNONNATIVESERVICECONTEXT_H

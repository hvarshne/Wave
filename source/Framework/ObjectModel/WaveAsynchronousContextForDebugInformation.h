/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#ifndef WAVEASYNCHRONOUSCONTEXTFORDEBUGINFORMATION_H
#define WAVEASYNCHRONOUSCONTEXTFORDEBUGINFORMATION_H

#include "Framework/Types/Types.h"
#include "Framework/Utils/PrismAsynchronousContext.h"

namespace WaveNs
{

class WaveAsynchronousContextForDebugInformation : public PrismAsynchronousContext
{
    private :
    protected :
    public :
                                    WaveAsynchronousContextForDebugInformation  (PrismElement *pCaller, PrismAsynchronousCallback pCallback, void *pCallerContext = NULL);
        virtual                    ~WaveAsynchronousContextForDebugInformation  ();

                void                setDebugInformation                         (const string &debugInformation);
                const   string &    getDebugInformation                         () const;

    // Now the data members

    private :
                        string      m_debugInformation;

    protected :
    public :
};

}

#endif // WAVEASYNCHRONOUSCONTEXTFORDEBUGINFORMATION_H

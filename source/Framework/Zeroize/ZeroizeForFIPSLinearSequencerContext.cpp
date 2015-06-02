/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#include "Framework/Core/PrismFrameworkObjectManager.h"
#include "Framework/Zeroize/ZeroizeForFIPSLinearSequencerContext.h"


namespace WaveNs
{
	
    ZeroizeForFIPSLinearSequencerContext::ZeroizeForFIPSLinearSequencerContext 
    (
        PrismMessage                *pPrismMessage, 
        PrismElement                *pPrismElement, 
        PrismLinearSequencerStep    *pSteps, 
        UI32                        numberOfSteps

    ): PrismLinearSequencerContext (pPrismMessage, pPrismElement, pSteps, numberOfSteps)
    {
    }

    ZeroizeForFIPSLinearSequencerContext::~ZeroizeForFIPSLinearSequencerContext()
    {
    }


}

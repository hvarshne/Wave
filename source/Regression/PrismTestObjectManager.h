/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMTESTOBJECTMANAGER_H
#define PRISMTESTOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManager.h"
#include "Regression/RegressionTestMessage.h"
#include "Regression/RegressionPrepareMessage.h"
#include "Regression/RegressionPrepareMessage2.h"
#include <map>
#include <vector>
#include <string>

namespace WaveNs
{

class PrismTestObjectManager : public WaveLocalObjectManager
{
    private :
        virtual PrismMessage *createMessageInstance (const UI32 &operationCode);

    protected :
                     PrismTestObjectManager              (const string &prismTestObjectManagerName, const UI32 &stackSize = 0, const vector<UI32> *pCpuAffinityVector = NULL);
        virtual void testRequestHandler                  (RegressionTestMessage *pMessage) = 0;
                void prepareForRegressionRequestHandler  (RegressionPrepareMessage *pMessage);
                void prepareForRegressionRequestHandler2 (RegressionPrepareMessage2 *pMessage);
              string getTestParameterValue (const string &inputKeyString);

    public :

    // Now the data members

    private :
    protected :
        map<string, string> m_testParameters;
        vector<string> m_regressionInput;

    public :
};

}

#endif // PRISMTESTOBJECTMANAGER_H

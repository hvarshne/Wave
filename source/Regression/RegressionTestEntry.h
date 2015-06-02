/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef REGRESSIONTESTENTRY_H
#define REGRESSIONTESTENTRY_H

#include "Framework/Types/Types.h"

namespace WaveNs
{

class RegressionTestEntry
{
    private :
    protected :
    public :
                      RegressionTestEntry     ();
                      RegressionTestEntry     (PrismServiceId id, bool enabled);
                     ~RegressionTestEntry     ();
        PrismServiceId  getTestServiceId        () const;
        bool          getIsTestEnabled        () const;
        void          setIsTestEnabled        (bool enabled);


    // Now the data members

     private :
        PrismServiceId m_testServiceId;
        bool         m_isTestEnabled;

     protected :
     public :
};

}

#endif // REGRESSIONTESTENTRY_H

/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGPRESENCE_H
#define YANGPRESENCE_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangPresence : public YangElement
{
    private :
    protected :
    public :
                            YangPresence    ();
        virtual            ~YangPresence    ();

        static  string      getYangName     ();

        static YangElement *createInstance  ();

    // Now the data members
    private :
    protected :
    public :
};

}

#endif // YANGPRESENCE_H

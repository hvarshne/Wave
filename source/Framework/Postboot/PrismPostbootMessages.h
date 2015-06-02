/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Amit Agrawal                                                 *
 ***************************************************************************/

#ifndef PRISMPOSTBOOTMESSAGES_H
#define PRISMPOSTBOOTMESSAGES_H

#include "Framework/ObjectModel/PrismElement.h"
#include "Framework/Messaging/Local/PrismMessage.h"

namespace WaveNs
{

class ExecutePostbootPassTableMessage : public PrismMessage
{
    private :
    protected :
    public :
                               ExecutePostbootPassTableMessage ();
        virtual               ~ExecutePostbootPassTableMessage ();

    // Now the data members
    private :
    protected :
    public :
};

}

#endif // PRISMPOSTBOOTMESSAGES_H

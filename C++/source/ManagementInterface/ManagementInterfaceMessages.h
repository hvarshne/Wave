/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef MANAGEMENTINTERFACEMESSAGES_H
#define MANAGEMENTINTERFACEMESSAGES_H

#include "Framework/Attributes/AttributesMap.h"
#include "Framework/Messaging/Local/WaveMessage.h"

namespace WaveNs
{

class RequestToManagementInterfaceMessage : public WaveMessage
{
    private :
    protected :
    public :
        RequestToManagementInterfaceMessage (WaveServiceId servciceId, UI32 operationId, AttributesMap *pAttributesMap);

     // Now the data members

     private :
        AttributesMap *m_pInputAttributesMap;
     protected :
     public :
};

}

#endif // MANAGEMENTINTERFACEMESSAGES_H

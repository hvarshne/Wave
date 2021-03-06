/***************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMANAGEDOBJECTMESSAGE_H
#define WAVEMANAGEDOBJECTMESSAGE_H

#include "Framework/Messaging/Local/WaveMessage.h"
#include "Framework/ObjectModel/ObjectId.h"

namespace WaveNs
{

class WaveManagedObjectMessage : public WaveMessage
{
    private :
        virtual void setupAttributesForSerialization ();

    protected :
    public :
                          WaveManagedObjectMessage (WaveServiceId serviceCode, UI32 operationCode);
                          WaveManagedObjectMessage (WaveServiceId serviceCode, UI32 operationCode, const ObjectId &waveManagedObjectId);
        virtual          ~WaveManagedObjectMessage ();

                ObjectId  getWaveManagedObjectId   () const;
                void      setWaveManagedObjectId   (const ObjectId &waveManagedObjectId);

    // Now the data members

    private :
        ObjectId m_waveManagedObjectId;

    protected :
    public :
};

}

#endif // WAVEMANAGEDOBJECTMESSAGE_H

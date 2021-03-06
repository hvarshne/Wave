/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVETESTMANAGEDOBJECT2_H
#define WAVETESTMANAGEDOBJECT2_H

#include "Framework/ObjectModel/WaveManagedObject.h"

namespace WaveNs
{

class WaveTestManagedObject2 : public WaveManagedObject
{
    private :
        virtual void setupAttributesForPersistence ();

    protected :
    public :
                         WaveTestManagedObject2  (WaveObjectManager *pWaveObjectManager);
        virtual         ~WaveTestManagedObject2  ();

        static  string   getClassName             ();

        virtual void     setupAttributesForCreate ();

                void     setInteger2              (const UI32 &integer2);
                void     setMessage2              (const string &message2);
                void     setObjectId2             (const ObjectId &objectId2);
                void     setAssociation2          (const ObjectId &association2);

                UI32      getInteger2             () const;
                string    getMessage2             () const;
                ObjectId  getObjectId2            () const;
                ObjectId  getAssociation2         () const;

        virtual bool     operator ==              (const WaveTestManagedObject2 &rhs) const;
        virtual bool     operator !=              (const WaveTestManagedObject2 &rhs) const;

    // Now the data members

    private :
        UI32     m_integer2;
        string   m_message2;
        ObjectId m_objectId2;
        ObjectId m_association2;

    protected :
    public :
};

}

#endif // WAVETESTMANAGEDOBJECT2_H

/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#ifndef WAVECLIREPLYTHREAD
#define WAVECLIREPLYTHREAD

#include "Framework/MultiThreading/WavePosixThread.h"
#include "ManagementInterface/ManagementInterfaceMessage.h"

namespace WaveNs
{

class WaveCliReplyThread : public WavePosixThread
{
    private:
                WaveThreadStatus start ();


    protected:

    public:
                WaveCliReplyThread (ManagementInterfaceMessage *pManagementInterfaceMessage);
    // data members


    private:
                ManagementInterfaceMessage *m_pManagementInterfaceMessage;
    protected:

    public:
};

}

#endif


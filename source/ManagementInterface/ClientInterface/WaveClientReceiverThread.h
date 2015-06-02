/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVECLIENTRECEIVERTHREAD_H
#define WAVECLIENTRECEIVERTHREAD_H

#include "Framework/MultiThreading/PrismPosixThread.h"
#include "Framework/Types/Types.h"
#include "Framework/Utils/PrismMutex.h"
#include <string>

namespace WaveNs
{

class ServerStreamingSocket;

class WaveClientReceiverThread : public PrismPosixThread
{
    private :
        bool authorizeClient ();

    protected :
    public :
                                  WaveClientReceiverThread       (ServerStreamingSocket *pServerStreamingSocket);
                                 ~WaveClientReceiverThread       ();

        virtual WaveThreadStatus  start                          ();
                void              setPeerServerDetails           (const string &peerServerIpAddress, const SI32 &peerServerPort, const string& messageVersion = "");
                void              closePeerServerStreamingSocket (void);

                void              setPeerServerId                (const UI32 &peerServerId);
                string            getPeerServerMessageVersion    () const;
                UI8               getPeerServerSerializationType () const;

    // Now the Data Members

    private :
        ServerStreamingSocket *m_pServerStreamingSocket;
        string                 m_peerServerIpAddress;
        SI32                   m_peerServerPort;
        PrismMutex             m_peerServerMutex;

        UI32                   m_peerServerId;
        string                 m_peerServerMessageVersion;
        UI8                    m_peerServerSerializationType;

    protected :
    public :
};

}

#endif // WAVECLIENTRECEIVERTHREAD_H

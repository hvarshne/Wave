/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorkerProxy.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorkerReadinessMessage.h"
#include "Framework/Utils/SystemErrorUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceMessageBase.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorkerResponseMessage.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceInputConfiguration.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceManagerDelegateMessage.h"

#include <errno.h>

namespace WaveNs
{

MapReduceWorkerProxy::MapReduceWorkerProxy (const SI32 &readSocket, const SI32 &writeSocket)
    : m_readSocket  (readSocket),
      m_writeSocket (writeSocket)
{
}

MapReduceWorkerProxy::~MapReduceWorkerProxy ()
{
    WaveNs::tracePrintf (TRACE_LEVEL_INFO, "MapReduceWorkerProxy::~MapReduceWorkerProxy : RFD : %d, WFD : %d", m_readSocket, m_writeSocket);

    ::close (m_readSocket);
    ::close (m_writeSocket);
}

void MapReduceWorkerProxy::receiveMessageFromWorker (string &messageFromManager)
{
    messageFromManager = "";

    UI32 sizeOfDataToReceive = 0;

    SI32 status = ::read (m_readSocket, &sizeOfDataToReceive, sizeof (sizeOfDataToReceive));

    if (-1 == status)
    {
        WaveNs::tracePrintf (TRACE_LEVEL_INFO, "MapReduceWorkerProxy::receiveMessageFromWorker : Data read failed for fd : %d with status : %d : %s", m_readSocket, errno, (SystemErrorUtils::getErrorStringForErrorNumber(errno)).c_str ());
    }
    else if (0 == status)
    {
        return;
    }
    else
    {
        sizeOfDataToReceive = ntohl (sizeOfDataToReceive);

        const UI32 originalSizeOfDataToReceive = sizeOfDataToReceive;

        WaveNs::tracePrintf (TRACE_LEVEL_INFO, "FD %d, number of bytes to read : %d", m_readSocket, originalSizeOfDataToReceive);

        char *pBuffer     = new char[originalSizeOfDataToReceive + 1];
        char *pTempBuffer = pBuffer;

        waveAssert (NULL != pBuffer,     __FILE__, __LINE__);
        waveAssert (NULL != pTempBuffer, __FILE__, __LINE__);

        while (sizeOfDataToReceive > 0)
        {
            status = ::read (m_readSocket, pTempBuffer, sizeOfDataToReceive);

            if (-1 == status)
            {
                WaveNs::tracePrintf (TRACE_LEVEL_INFO, "MapReduceWorkerProxy::receiveMessageFromWorker : Data read failed for fd : %d during message read with status : %d : %s", m_readSocket, errno, (SystemErrorUtils::getErrorStringForErrorNumber(errno)).c_str ());

                delete pBuffer;

                return;
            }
            else if (0 == status)
            {
                WaveNs::tracePrintf (TRACE_LEVEL_INFO, "FD %d, could not read when number of bytes remaining : %d", m_readSocket, status, sizeOfDataToReceive);

                delete pBuffer;

                return;
            }
            else
            {
                sizeOfDataToReceive -= status;
                pTempBuffer         += status;
            }
        }

        pBuffer[originalSizeOfDataToReceive] = '\0';

        WaveNs::tracePrintf (TRACE_LEVEL_INFO, true, false, "FD : %d, Data Read : %s", m_readSocket, pBuffer);

        messageFromManager = pBuffer;

        return;
    }

    return;
}

MapReduceWorkerReadinessMessage *MapReduceWorkerProxy::receiveWorkerReadynessMessage ()
{
    string messageFromWorker;

    receiveMessageFromWorker (messageFromWorker);

    if ("" != messageFromWorker)
    {
        MapReduceMessageType mapReduceMessageType = MapReduceMessageBase::getType (messageFromWorker);

        if (MAP_REDUCE_MESSAGE_TYPE_READY == mapReduceMessageType)
        {
            MapReduceWorkerReadinessMessage *pMapReduceWorkerReadinessMessage = instantiateWorkerReadynessMessage ();

            waveAssert (NULL != pMapReduceWorkerReadinessMessage, __FILE__, __LINE__);

            pMapReduceWorkerReadinessMessage->loadFromSerializedData2 (messageFromWorker);

            return (pMapReduceWorkerReadinessMessage);
        }
    }

    return (NULL);
}

MapReduceMessageBase *MapReduceWorkerProxy::receiveWorkerMessage ()
{
    string messageFromWorker;

    receiveMessageFromWorker (messageFromWorker);

    if ("" != messageFromWorker)
    {
        MapReduceMessageType mapReduceMessageType = MapReduceMessageBase::getType (messageFromWorker);

        if (MAP_REDUCE_MESSAGE_TYPE_READY == mapReduceMessageType)
        {
            MapReduceWorkerReadinessMessage *pMapReduceWorkerReadinessMessage = instantiateWorkerReadynessMessage ();

            waveAssert (NULL != pMapReduceWorkerReadinessMessage, __FILE__, __LINE__);

            pMapReduceWorkerReadinessMessage->loadFromSerializedData2 (messageFromWorker);

            return (pMapReduceWorkerReadinessMessage);
        }
        else if (MAP_REDUCE_MESSAGE_TYPE_RESPONSE == mapReduceMessageType)
        {
            MapReduceWorkerResponseMessage *pMapReduceWorkerResponseMessage = instantiateWorkerResponseMessage ();

            waveAssert (NULL != pMapReduceWorkerResponseMessage, __FILE__, __LINE__);

            pMapReduceWorkerResponseMessage->loadFromSerializedData2 (messageFromWorker);

            return (pMapReduceWorkerResponseMessage);
        }
    }

    return (NULL);
}

bool MapReduceWorkerProxy::processWorkerReadynessMessageAndDelegate (MapReduceInputConfiguration *pMapReduceInputConfiguration, MapReduceWorkerReadinessMessage *pMapReduceWorkerReadinessMessage)
{
    waveAssert (NULL != pMapReduceInputConfiguration,     __FILE__, __LINE__);
    waveAssert (NULL != pMapReduceWorkerReadinessMessage, __FILE__, __LINE__);

    MapReduceManagerDelegateMessage *pMapReduceManagerDelegateMessage = pMapReduceInputConfiguration->getNextWork (pMapReduceWorkerReadinessMessage);

    if (NULL == pMapReduceManagerDelegateMessage)
    {
        return (false);
    }

    bool sendStatus = sendWorkerReadinessMessage (pMapReduceManagerDelegateMessage);

    return (sendStatus);
}

bool MapReduceWorkerProxy::sendWorkerReadinessMessage (MapReduceManagerDelegateMessage *pMapReduceManagerDelegateMessage)
{
    waveAssert (NULL != pMapReduceManagerDelegateMessage, __FILE__, __LINE__);

    string serializedData;

    pMapReduceManagerDelegateMessage->serialize2 (serializedData);

          UI32  sizeOfSerializedData            = serializedData.length ();
    const char *pBuffer                         = serializedData.c_str ();
          UI32  sizeOfSerializedDataOverNetwork = htonl (sizeOfSerializedData);

    SI32  writeStatus          = 0;

    writeStatus = ::write (m_writeSocket, &sizeOfSerializedDataOverNetwork, sizeof (sizeOfSerializedData));

    if (-1 == writeStatus)
    {
        return (false);
    }

    while (sizeOfSerializedData > 0)
    {
        writeStatus = ::write (m_writeSocket, serializedData.c_str (), sizeOfSerializedData);

        if (-1 == writeStatus)
        {
            return (false);
        }
        else
        {
            sizeOfSerializedData -= writeStatus;

            pBuffer += writeStatus;
        }
    }

    return (true);
}

MapReduceWorkerResponseMessage *MapReduceWorkerProxy::receiveWorkerResponseMessage ()
{
    return (NULL);
}

}

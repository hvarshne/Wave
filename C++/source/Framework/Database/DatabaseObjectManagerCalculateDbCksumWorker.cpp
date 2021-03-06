/**********************************************************************************************
 *  @file : DatabaseObjectManagerCalculateDbCksumWorker.cpp                                   *
 *   Copyright (C) 2010 Vidyasagara Guntaka                                                   *
 *   All rights reserved.                                                                     *
 *   Description : Implements a class DatabaseObjectManagerCalculateDbCksumWorker.            *
 *                  The handler handles a message DatabaseObjectManagerCalculateDbCksumMessage*
 *                  where it calculates the checksum for local database and reply.            *
 *   Author : Pritee Ghosh                                                                    *
 *   Date   : 02/22/2011                                                                      *
 **********************************************************************************************/

#include "Framework/Database/DatabaseObjectManagerCalculateDbCksumWorker.h"
#include "Framework/Database/DatabaseObjectManagerCalculateDbCksumMessage.h"
#include "Framework/Database/DatabaseObjectManagerTypes.h"
#include "Framework/Database/DatabaseConnection.h"
#include "Framework/Database/DatabaseObjectManager.h"
#include "Framework/Utils/StringUtils.h"

namespace WaveNs
{

DatabaseObjectManagerCalculateDbCksumWorker::DatabaseObjectManagerCalculateDbCksumWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager)
{
    addOperationMap (DATABASE_OBJECT_MANAGER_CALCULATE_DB_CKSUM, reinterpret_cast<WaveMessageHandler> (&DatabaseObjectManagerCalculateDbCksumWorker::calculateDBCksumMessageHandler));
}

DatabaseObjectManagerCalculateDbCksumWorker::~DatabaseObjectManagerCalculateDbCksumWorker ()
{
}

WaveMessage *DatabaseObjectManagerCalculateDbCksumWorker::createMessageInstance (const UI32 &operationCode)
{
    WaveMessage *pWaveMessage = NULL;

    switch (operationCode)
    {
        case DATABASE_OBJECT_MANAGER_CALCULATE_DB_CKSUM :
            pWaveMessage = new DatabaseObjectManagerCalculateDbCksumMessage ();
            break;

        default :
            trace (TRACE_LEVEL_FATAL, string ("DatabaseObjectManagerCalculateDbCksumWorker::createMessageInstance : Unknown operation code : ") + operationCode);
            waveAssert (false, __FILE__, __LINE__);
    }

    return (pWaveMessage);
}

void DatabaseObjectManagerCalculateDbCksumWorker::calculateDBCksumMessageHandler (DatabaseObjectManagerCalculateDbCksumMessage *pDatabaseObjectManagerCalculateDbCksumMessage)
{
    char    cksum [100];
    FILE    *pFile;

    trace (TRACE_LEVEL_DEBUG, "DatabaseObjectManagerCalculateDbCksumWorker::calculateDBCksumMessageHandler : Entering...");

    if (false == (DatabaseObjectManager::getIsDatabaseEnabled ()))
    {
        trace (TRACE_LEVEL_DEVEL, "DatabaseObjectManagerCalculateDbCksumWorker::calculateDBCksumMessageHandler: No support for Persistent Store will be provided.");
        pDatabaseObjectManagerCalculateDbCksumMessage->setCompletionStatus (WAVE_MESSAGE_ERROR);
        reply (pDatabaseObjectManagerCalculateDbCksumMessage);
        return;
    }

    trace (TRACE_LEVEL_DEBUG, "DatabaseObjectManagerCalculateDbCksumWorker::calculateDBCksumMessageHandler : Calculating Database checksum...");

    string commandString = string (" pg_dump --schema=WaveCurrent --format=p") + string (" --port=") + DatabaseObjectManager::getDatabasePort () + string (" ") + DatabaseObjectManager::getDatabaseName () + string (" | /bin/sort | /usr/bin/md5sum | /usr/bin/cut -d ' ' -f 1 ");

    tracePrintf (TRACE_LEVEL_INFO, "DatabaseObjectManagerCalculateDbCksumWorker::calculateDBCksumMessageHandler : commandString= %s", commandString.c_str ());
    pFile = popen (commandString.c_str (), "r");

    if (pFile == NULL)
    {
        trace (TRACE_LEVEL_ERROR, string("DatabaseObjectManagerCalculateDbCksumWorker::calculateDBCksumMessageHandler: Failed to calculate the cksum for database") + commandString.c_str ());
        pDatabaseObjectManagerCalculateDbCksumMessage->setCompletionStatus (WAVE_MESSAGE_ERROR);
        reply (pDatabaseObjectManagerCalculateDbCksumMessage);
        return;
    }

    char *pChar = fgets (cksum, 100, pFile);

    if (NULL == pChar)
    {
        // handle the null case.
    }

    fclose (pFile);
    tracePrintf (TRACE_LEVEL_DEBUG, "DatabaseObjectManagerCalculateDbCksumWorker::calculateDBCksumMessageHandler : cksum = %s", cksum); 


    pDatabaseObjectManagerCalculateDbCksumMessage->setDbCksumForNode (cksum);
    pDatabaseObjectManagerCalculateDbCksumMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    reply (pDatabaseObjectManagerCalculateDbCksumMessage);
}

}

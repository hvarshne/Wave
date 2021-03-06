/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : jiyer                                                        *
 **************************************************************************/

#include "File/Local/FilePushFileMessage.h"
#include "File/Local/FileLocalObjectManager.h"
#include "File/Local/FileLocalTypes.h"
#include "Framework/Attributes/AttributeResourceId.h"


namespace WaveNs
{

    FilePushFileMessage::FilePushFileMessage ()
        : WaveMessage (FileLocalObjectManager::getWaveServiceId (), FILESVCPUSHFILE),
         m_sourceLocationId(0),        
         m_fileTransferFlag(0)
    {
    }

    FilePushFileMessage::FilePushFileMessage (const string &SourceFileName,const string &DestinationFileName,const UI32 &SourceLocationId, vector<UI32> &DestinationLocationIdList, UI32 &fileTransferFlag)
        : WaveMessage (FileLocalObjectManager::getWaveServiceId (), FILESVCPUSHFILE),
        m_sourceFileName           (SourceFileName),
        m_destinationFileName      (DestinationFileName),
        m_sourceLocationId         (SourceLocationId),
        m_vecDestinationLocationId (DestinationLocationIdList),
        m_vecLocationToReceiveNextMessage (DestinationLocationIdList),
        m_fileTransferFlag         (fileTransferFlag),
        m_transferHandle           ("")
    {
          InitInternalTables(DestinationLocationIdList);
    }
    
            
    FilePushFileMessage::FilePushFileMessage (const string &SourceFileName,const string &DestinationFileName,const UI32 &SourceLocationId, vector<UI32> &DestinationLocationIdList)
        : WaveMessage (FileLocalObjectManager::getWaveServiceId (), FILESVCPUSHFILE),
        m_sourceFileName           (SourceFileName),
        m_destinationFileName      (DestinationFileName),
        m_sourceLocationId         (SourceLocationId),
        m_vecDestinationLocationId (DestinationLocationIdList),
        m_vecLocationToReceiveNextMessage (DestinationLocationIdList),
        m_fileTransferFlag         (0),
        m_transferHandle           ("")
    {
          InitInternalTables(DestinationLocationIdList);
    }
    
    FilePushFileMessage::~FilePushFileMessage ()
    {
    }

    void  FilePushFileMessage::InitInternalTables(vector<UI32> &DestinationLocationIdList)
    {
          // Set the ResponseStatus and FrameworkStatus Table to Success for all locations.
          vector<UI32>::iterator itr = DestinationLocationIdList.begin();
          for (; DestinationLocationIdList.end() != itr ; itr++)
          {
               m_ResponseCodeList.push_back(WAVE_MESSAGE_SUCCESS);
               m_FrameworkStatusList.push_back(FRAMEWORK_SUCCESS);
          }
    }

    void  FilePushFileMessage::setupAttributesForSerialization()
    {
        WaveMessage::setupAttributesForSerialization ();
        addSerializableAttribute (new AttributeString(&m_sourceFileName,"SourceFileName"));
        addSerializableAttribute (new AttributeString(&m_destinationFileName,"DestinationFileName"));
        addSerializableAttribute (new AttributeUI32(&m_sourceLocationId,"SourceLocationId"));
        addSerializableAttribute (new AttributeUI32(&m_fileTransferFlag,"FileTransferFlag"));
        addSerializableAttribute (new AttributeString(&m_transferHandle,"TransferHandle"));
        addSerializableAttribute (new AttributeLocationIdVector(&m_vecDestinationLocationId, "LocationIdListFromUser"));
        addSerializableAttribute (new AttributeLocationIdVector(&m_vecLocationToReceiveNextMessage, "LocationIdToReceiveNextMessage"));
        addSerializableAttribute (new AttributeResourceIdVector(&m_ResponseCodeList, "ResponseCodeList"));
//      addSerializableAttribute (new AttributeResourceIdVector(&m_FrameworkStatusList, "FrameworkStatusList"));
    }

    void  FilePushFileMessage::setSourceFileName(const string &SourceFileName)
    {
        m_sourceFileName  =  SourceFileName;
    }

    string  FilePushFileMessage::getSourceFileName() const
    {
        return (m_sourceFileName);
    }

    void  FilePushFileMessage::setDestinationFileName(const string &DestinationFileName)
    {
        m_destinationFileName  =  DestinationFileName;
    }

    string  FilePushFileMessage::getDestinationFileName() const
    {
        return (m_destinationFileName);
    }

    void  FilePushFileMessage::setSourceLocationId(const UI32 &SourceLocationId)
    {
        m_sourceLocationId  =  SourceLocationId;
    }

    UI32  FilePushFileMessage::getSourceLocationId() const
    {
        return (m_sourceLocationId);
    }

     void   FilePushFileMessage::setDestinationLocationIdList  (const vector<UI32> &vecLocationIdList)
     {
          m_vecDestinationLocationId = vecLocationIdList;
     }

     vector<UI32>  FilePushFileMessage::getDestinationLocationIdList  ()
     {
          return m_vecDestinationLocationId;
     }

    void  FilePushFileMessage::setFileTransferFlag(const UI32 &fileTransferFlag)
    {
        m_fileTransferFlag  =  fileTransferFlag;
    }

    UI32  FilePushFileMessage::getFileTransferFlag() const
    {
        return (m_fileTransferFlag);
    }

    void   FilePushFileMessage::setTransferHandle(string &TransferHandle)
    {
          m_transferHandle = TransferHandle;
    }

    string  FilePushFileMessage::getTransferHandle()
    {
          return m_transferHandle;
    }

     UI32  FilePushFileMessage::getLocationCountToReceiveNextMessage() const
     {
          return(m_vecLocationToReceiveNextMessage.size());
     }

     vector<UI32>   FilePushFileMessage::getDestinationLocationIdListForNextMessage() 
     {
          return (m_vecLocationToReceiveNextMessage);
     }

     void  FilePushFileMessage::removeLocationForSubsequentSends(const UI32 &nLocationId)
     {
          bool bLocationFound = false;
          vector<UI32>::iterator itr =  m_vecLocationToReceiveNextMessage.begin();
          for(; itr != m_vecLocationToReceiveNextMessage.end(); itr++)
          {
               if ((*itr) == nLocationId)
               {
                    bLocationFound = true;
                    break;
               }
          }
          // Remove from the list.
          if (true == bLocationFound)
          {
               m_vecLocationToReceiveNextMessage.erase(itr);
          }
     }

     vector<ResourceId>     FilePushFileMessage::getResponseCodeList           ()
     {
          return m_ResponseCodeList;     
     }

     void   FilePushFileMessage::setResponseCodeList(vector<ResourceId>  &responseStatus)
     {
          m_ResponseCodeList = responseStatus;
     }
     
     vector<FrameworkStatus> FilePushFileMessage::getFrameworkStatusList       ()
     {
          return m_FrameworkStatusList;     
     }


FilePushFileToHaPeerMessage::FilePushFileToHaPeerMessage ()
    : WaveMessage          (FileLocalObjectManager::getWaveServiceId (), FILESVCFILEPUSHFILETOHAPEER),
      m_fileSize            (0)
{
}

FilePushFileToHaPeerMessage::FilePushFileToHaPeerMessage (const string &sourceFileName, const string &destinationFileName)
    : WaveMessage          (FileLocalObjectManager::getWaveServiceId (), FILESVCFILEPUSHFILETOHAPEER),
      m_sourceFileName      (sourceFileName),
      m_destinationFileName (destinationFileName),
      m_fileSize            (0)
{
}

FilePushFileToHaPeerMessage::~FilePushFileToHaPeerMessage ()
{
}

void FilePushFileToHaPeerMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeString (&m_sourceFileName,       "SourceFileName"));
    addSerializableAttribute (new AttributeString (&m_destinationFileName,  "DestinationFileName"));
    // (Used only inside handler as temporary storage between sequencer steps.)
    // addSerializableAttribute (new AttributeUI32   (&m_fileSize,             "FileSize"));
}

void FilePushFileToHaPeerMessage::setSourceFileName (const string &sourceFileName)
{
    m_sourceFileName = sourceFileName;
}

string FilePushFileToHaPeerMessage::getSourceFileName () const
{
    return m_sourceFileName;
}

void FilePushFileToHaPeerMessage::setDestinationFileName (const string &destinationFileName)
{
    m_destinationFileName = destinationFileName;
}

string FilePushFileToHaPeerMessage::getDestinationFileName () const
{
    return m_destinationFileName;
}

void FilePushFileToHaPeerMessage::setFileSize (const UI32 &fileSize)
{
    m_fileSize = fileSize;
}

UI32 FilePushFileToHaPeerMessage::getFileSize () const
{
    return m_fileSize;
}

}

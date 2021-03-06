/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 ***************************************************************************/

#include "Framework/Core/WaveFrameworkMessages.h"
#include "Framework/Types/Types.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Attributes/AttributeResourceId.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Attributes/AttributeStringVectorVector.h"
#include "Framework/Attributes/AttributeUI32VectorVector.h"
#include "Framework/Messaging/LightHouse/LightPulse.h"
#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveBrokerPublishMessage.h"

namespace WaveNs
{

static const UI32 s_bufferTagForValidationDetails = 0;
static const UI32 s_bufferTagForValidationResults = 1;

static const UI32 s_bufferTagForHaSyncValidationDetails = 0;
static const UI32 s_bufferTagForHaSyncValidationResults = 1;

WaveInitializeObjectManagerMessage::WaveInitializeObjectManagerMessage (WaveServiceId id, const WaveBootReason &reason)
    : WaveMessage (id, WAVE_OBJECT_MANAGER_INITIALIZE),
      m_reason     (reason)
{
}

WaveBootReason WaveInitializeObjectManagerMessage::getReason () const
{
    return (m_reason);
}

WaveInstallObjectManagerMessage::WaveInstallObjectManagerMessage (WaveServiceId id, const WaveBootReason &reason)
    : WaveMessage (id, WAVE_OBJECT_MANAGER_INSTALL),
      m_reason     (reason)
{
}

WaveBootReason WaveInstallObjectManagerMessage::getReason () const
{
    return (m_reason);
}

WaveEnableObjectManagerMessage::WaveEnableObjectManagerMessage (WaveServiceId id, const WaveBootReason &reason)
: WaveMessage (id, WAVE_OBJECT_MANAGER_ENABLE),
      m_reason     (reason)
{
}

WaveBootReason WaveEnableObjectManagerMessage::getReason () const
{
    return (m_reason);
}

WaveUpgradeObjectManagerMessage::WaveUpgradeObjectManagerMessage (WaveServiceId id, const WaveBootReason &reason)
    : WaveMessage (id, WAVE_OBJECT_MANAGER_UPGRADE),
      m_reason     (reason)
{
}

WaveBootReason WaveUpgradeObjectManagerMessage::getReason () const
{
    return (m_reason);
}

WaveBootObjectManagerMessage::WaveBootObjectManagerMessage (WaveServiceId id, const WaveBootReason &reason, const bool &rollBackFlag)
    : WaveMessage (id, WAVE_OBJECT_MANAGER_BOOT),
      m_reason     (reason),
      m_rollBackFlag (rollBackFlag)
{
}

bool WaveBootObjectManagerMessage::getRollBackFlag () const
{
    return (m_rollBackFlag);
}

WavePostbootObjectManagerMessage::WavePostbootObjectManagerMessage (WaveServiceId id, SI8 passNum, string passName, UI32 slotNum, UI32 recoveryType)
    : WaveMessage (id, WAVE_OBJECT_MANAGER_POSTBOOT),
      m_passNum    (passNum),
      m_passName   (passName),
      m_slotNum    (slotNum),
      m_recoveryType (recoveryType)
{
}

WaveHaInstallObjectManagerMessage::WaveHaInstallObjectManagerMessage (WaveServiceId id, const WaveBootReason &reason)
    : WaveMessage (id, WAVE_OBJECT_MANAGER_HAINSTALL),
      m_reason     (reason)
{
}

WaveBootReason WaveHaInstallObjectManagerMessage::getReason () const
{
    return (m_reason);
}

WaveHaBootObjectManagerMessage::WaveHaBootObjectManagerMessage (WaveServiceId id, const WaveBootReason &reason)
    : WaveMessage (id, WAVE_OBJECT_MANAGER_HABOOT),
      m_reason     (reason)
{
}

WaveBootReason WaveHaBootObjectManagerMessage::getReason () const
{
    return (m_reason);
}

void WavePostbootObjectManagerMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeSI8      (&m_passNum,       "passNum"));
     addSerializableAttribute (new AttributeString   (&m_passName,      "passName"));
     addSerializableAttribute (new AttributeUI32     (&m_slotNum,       "slotNum"));
     addSerializableAttribute (new AttributeUI32     (&m_recoveryType,  "recoveryType"));
}

SI8 WavePostbootObjectManagerMessage::getPassNum () const
{
    return (m_passNum);
}

string WavePostbootObjectManagerMessage::getPassName () const
{
    return (m_passName);
}

UI32 WavePostbootObjectManagerMessage::getSlotNum () const
{
    return (m_slotNum);
}

UI32 WavePostbootObjectManagerMessage::getRecoveryType () const
{
    return (m_recoveryType);
}

WaveBootReason WaveBootObjectManagerMessage::getReason () const
{
    return (m_reason);
}

WaveShutdownObjectManagerMessage::WaveShutdownObjectManagerMessage (WaveServiceId id)
    : WaveMessage (id, WAVE_OBJECT_MANAGER_SHUTDOWN)
{
}

WaveDisableObjectManagerMessage::WaveDisableObjectManagerMessage (WaveServiceId id)
    : WaveMessage (id, WAVE_OBJECT_MANAGER_DISABLE)
{
}

WaveUninstallObjectManagerMessage::WaveUninstallObjectManagerMessage (WaveServiceId id)
    : WaveMessage (id, WAVE_OBJECT_MANAGER_UNINSTALL)
{
}

WaveUninitializeObjectManagerMessage::WaveUninitializeObjectManagerMessage (WaveServiceId id)
    : WaveMessage (id, WAVE_OBJECT_MANAGER_UNINITIALIZE)
{
}

WaveDestructObjectManagerMessage::WaveDestructObjectManagerMessage (WaveServiceId id)
    : WaveMessage (id, WAVE_OBJECT_MANAGER_DESTRUCT)
{
}

WavePingObjectManagerMessage::WavePingObjectManagerMessage (WaveServiceId id)
    : WaveMessage (id, WAVE_OBJECT_MANAGER_PING)
{
    setPriority (WAVE_MESSAGE_PRIORITY_HIGH);
}

WaveTimerExpiredObjectManagerMessage::WaveTimerExpiredObjectManagerMessage (WaveServiceId id, TimerHandle timerId, WaveTimerExpirationHandler pWaveTimerExpirationCallback, void *pWaveTimerExpirationContext, WaveElement *pWaveTimerSender)
    : WaveMessage (id, WAVE_OBJECT_MANAGER_TIMER_EXPIRED)
{
    m_timerId                       =   timerId;
    m_pWaveTimerExpirationCallback =   pWaveTimerExpirationCallback;
    m_pWaveTimerExpirationContext  =   pWaveTimerExpirationContext;
    m_pWaveTimerSender             =   pWaveTimerSender;

}

WaveTimerExpiredObjectManagerMessage::WaveTimerExpiredObjectManagerMessage (const WaveTimerExpiredObjectManagerMessage &waveTimerExpiredObjectManagerMessage)
    : WaveMessage (0, WAVE_OBJECT_MANAGER_TIMER_EXPIRED)
{
    trace (TRACE_LEVEL_FATAL, "WaveTimerExpiredObjectManagerMessage::WaveTimerExpiredObjectManagerMessage : Copy constructing WaveTimerExpiredObjectManagerMessage does not make sense and hence not allowed.");
    waveAssert (false, __FILE__, __LINE__);
}

WaveTimerExpiredObjectManagerMessage &WaveTimerExpiredObjectManagerMessage::operator = (const WaveTimerExpiredObjectManagerMessage &waveTimerExpiredObjectManagerMessage)
{
    trace (TRACE_LEVEL_FATAL, "WaveTimerExpiredObjectManagerMessage::operator = : Assigning to a WaveTimerExpiredObjectManagerMessage does not make sense and hence not allowed.");
    waveAssert (false, __FILE__, __LINE__);

    return (*this);
}

WaveTimerExpirationHandler WaveTimerExpiredObjectManagerMessage::getTimerExpirationCallback ()
{
    return  m_pWaveTimerExpirationCallback;
}

void *WaveTimerExpiredObjectManagerMessage::getTimerExpirationContext ()
{
    return  m_pWaveTimerExpirationContext;
}

TimerHandle WaveTimerExpiredObjectManagerMessage::getTimerId ()
{
    return  m_timerId;
}

WaveElement *WaveTimerExpiredObjectManagerMessage::getTimerSender ()
{
    return  m_pWaveTimerSender;
}

WaveObjectManagerDatabaseSanityCheckMessage::WaveObjectManagerDatabaseSanityCheckMessage (WaveServiceId id, const WaveBootReason &bootReason)
    : WaveMessage (id, WAVE_OBJECT_MANAGER_DATABASE_SANITY_CHECK),
    m_bootReason (bootReason)
{
}

WaveBootReason WaveObjectManagerDatabaseSanityCheckMessage::getBootReason () const
{
    return m_bootReason;
}

WaveObjectManagerCollectValidationDataMessage::WaveObjectManagerCollectValidationDataMessage (WaveServiceId id)
    : WaveMessage (id, WAVE_OBJECT_MANAGER_CREATE_CLUSTER_COLLECT_VALIDATION_DATA)
{
}

WaveObjectManagerCollectValidationDataMessage::~WaveObjectManagerCollectValidationDataMessage ()
{
}

void WaveObjectManagerCollectValidationDataMessage::setValidationDetails (void *const pData, const UI32 &size, bool willBeOwnedByMessage)
{
    addBuffer (s_bufferTagForValidationDetails, size, pData, willBeOwnedByMessage);
}

void WaveObjectManagerCollectValidationDataMessage::getValidationDetails (void *&pData, UI32 &size)
{
    pData = transferBufferToUser (s_bufferTagForValidationDetails, size);
}

WaveObjectManagerValidateClusterCreationMessage::WaveObjectManagerValidateClusterCreationMessage (WaveServiceId id)
    : WaveMessage (id, WAVE_OBJECT_MANAGER_CREATE_CLUSTER_VALIDATE)
{
}

WaveObjectManagerValidateClusterCreationMessage::~WaveObjectManagerValidateClusterCreationMessage ()
{
}

void WaveObjectManagerValidateClusterCreationMessage::setValidationDetails (void *const pData, const UI32 &size, bool willBeOwnedByMessage)
{
    addBuffer (s_bufferTagForValidationDetails, size, pData, willBeOwnedByMessage);
}

void WaveObjectManagerValidateClusterCreationMessage::getValidationDetails (void *&pData, UI32 &size)
{
    pData = transferBufferToUser (s_bufferTagForValidationDetails, size);
}

void WaveObjectManagerValidateClusterCreationMessage::setValidationResults (void *const pData, const UI32 &size, bool willBeOwnedByMessage)
{
    addBuffer (s_bufferTagForValidationResults, size, pData, willBeOwnedByMessage);
}

void WaveObjectManagerValidateClusterCreationMessage::getValidationResults (void *&pData, UI32 &size)
{
    pData = transferBufferToUser (s_bufferTagForValidationResults, size);
}

WaveObjectManagerSendValidationResultsMessage::WaveObjectManagerSendValidationResultsMessage (WaveServiceId id)
    : WaveMessage (id, WAVE_OBJECT_MANAGER_CREATE_CLUSTER_SEND_VALIDATION_RESULTS)
{
}

WaveObjectManagerSendValidationResultsMessage::~WaveObjectManagerSendValidationResultsMessage ()
{
}

void WaveObjectManagerSendValidationResultsMessage::addValidationResults (const string &ipAddress, const SI32 &port, void *pValidationResults, const UI32 &validationResultsSize)
{
    m_ipAddressesVector.push_back (ipAddress);
    m_portsVector.push_back (port);

    UI32 resultsBufferTag = m_ipAddressesVector.size () - 1;

    addBuffer (resultsBufferTag, validationResultsSize, pValidationResults, true);
}

void  WaveObjectManagerSendValidationResultsMessage::getValidationResults (const string &ipAddress, const SI32 &port, void *&pValidationResults, UI32 &validationResultsSize)
{
    UI32 numberOfResults = m_ipAddressesVector.size ();
    UI32 i               = 0;

    pValidationResults    = NULL;
    validationResultsSize = 0;

    for (i = 0; i < numberOfResults; i++)
    {
        if ((m_ipAddressesVector[i] == ipAddress) && (m_portsVector[i] == port))
        {
            pValidationResults = transferBufferToUser (i, validationResultsSize);
            return;
        }
    }
}

UI32 WaveObjectManagerSendValidationResultsMessage::getNumberOfLocationsThatSentValidationResults ()
{
    const UI32 numberOfIpAddresses = m_ipAddressesVector.size ();
    const UI32 numberOfPorts       = m_portsVector.size ();

    if (numberOfIpAddresses != numberOfPorts)
    {
        trace (TRACE_LEVEL_FATAL, "WaveObjectManagerSendValidationResultsMessage::getNumberOfLocationsThatSentValidationResults : Corruption detected.  The number of IpAddresses must match with number of ports.");
        waveAssert (false, __FILE__, __LINE__);

        return (0);
    }
    else
    {
        return (numberOfIpAddresses);
    }
}

void WaveObjectManagerSendValidationResultsMessage::getLocationDetailsAtIndex (const UI32 &index, string &ipAddress, SI32 &port)
{
    const UI32 numberOfIpAddresses = m_ipAddressesVector.size ();
    const UI32 numberOfPorts       = m_portsVector.size ();

    if (numberOfIpAddresses != numberOfPorts)
    {
        trace (TRACE_LEVEL_FATAL, "WaveObjectManagerSendValidationResultsMessage::getLocationDetailsAtIndex : Corruption detected.  The number of IpAddresses must match with number of ports.");
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        if (numberOfIpAddresses <= index)
        {
            trace (TRACE_LEVEL_FATAL, string ("WaveObjectManagerSendValidationResultsMessage::getLocationDetailsAtIndex : Index (") + index + ") Out of range. Max Possible : " + (numberOfIpAddresses - 1));
            waveAssert (false, __FILE__, __LINE__);
        }
        else
        {
            ipAddress = m_ipAddressesVector[index];
            port      = m_portsVector[index];
        }
    }
}

WaveObjectManagerHaSyncCollectValidationDataMessage::WaveObjectManagerHaSyncCollectValidationDataMessage (WaveServiceId id)
    : WaveMessage (id, WAVE_OBJECT_MANAGER_HA_SYNC_COLLECT_VALIDATION_DATA)
{
}

WaveObjectManagerHaSyncCollectValidationDataMessage::~WaveObjectManagerHaSyncCollectValidationDataMessage ()
{
}

void WaveObjectManagerHaSyncCollectValidationDataMessage::setValidationDetails (void *const pData, const UI32 &size, bool willBeOwnedByMessage)
{
    addBuffer (s_bufferTagForHaSyncValidationDetails, size, pData, willBeOwnedByMessage);
}

void WaveObjectManagerHaSyncCollectValidationDataMessage::getValidationDetails (void *&pData, UI32 &size)
{
    pData = transferBufferToUser (s_bufferTagForHaSyncValidationDetails, size);
}

WaveObjectManagerHaSyncValidateDataMessage::WaveObjectManagerHaSyncValidateDataMessage (WaveServiceId id)
    : WaveMessage (id, WAVE_OBJECT_MANAGER_HA_SYNC_VALIDATE_DATA)
{
}

WaveObjectManagerHaSyncValidateDataMessage::~WaveObjectManagerHaSyncValidateDataMessage ()
{
}

void WaveObjectManagerHaSyncValidateDataMessage::setValidationDetails (void *const pData, const UI32 &size, bool willBeOwnedByMessage)
{
    addBuffer (s_bufferTagForValidationDetails, size, pData, willBeOwnedByMessage);
}

void WaveObjectManagerHaSyncValidateDataMessage::getValidationDetails (void *&pData, UI32 &size)
{
    pData = transferBufferToUser (s_bufferTagForValidationDetails, size);
}

void WaveObjectManagerHaSyncValidateDataMessage::setValidationResults (void *const pData, const UI32 &size, bool willBeOwnedByMessage)
{
    addBuffer (s_bufferTagForHaSyncValidationResults, size, pData, willBeOwnedByMessage);
}

void WaveObjectManagerHaSyncValidateDataMessage::getValidationResults (void *&pData, UI32 &size)
{
    pData = transferBufferToUser (s_bufferTagForHaSyncValidationResults, size);
}

WaveObjectManagerHaSyncSendValidationResultsMessage::WaveObjectManagerHaSyncSendValidationResultsMessage (WaveServiceId id)
    : WaveMessage (id, WAVE_OBJECT_MANAGER_HA_SYNC_SEND_VALIDATION_RESULTS)
{
}

WaveObjectManagerHaSyncSendValidationResultsMessage::~WaveObjectManagerHaSyncSendValidationResultsMessage ()
{
}

void WaveObjectManagerHaSyncSendValidationResultsMessage::addValidationResults (void *pValidationResults, const UI32 &validationResultsSize)
{
    addBuffer (s_bufferTagForHaSyncValidationResults, validationResultsSize, pValidationResults, true);
}

void WaveObjectManagerHaSyncSendValidationResultsMessage::getValidationResults (void *&pValidationResults, UI32 &validationResultsSize)
{
    pValidationResults    = NULL;
    validationResultsSize = 0;

    pValidationResults = transferBufferToUser (0, validationResultsSize);
    return;
}

WaveObjectManagerRegisterEventListenerMessage::WaveObjectManagerRegisterEventListenerMessage (WaveServiceId id, const UI32 &operationCodeToListenFor, const WaveServiceId &listenerWaveServiceId, const LocationId &listenerLocationId)
    : WaveMessage (id, WAVE_OBJECT_MANAGER_REGISTER_EVENT_LISTENER),
      m_operationCodeToListenFor (operationCodeToListenFor),
      m_listenerWaveServiceId (listenerWaveServiceId),
      m_listenerLocationId (listenerLocationId)
{
}

WaveObjectManagerRegisterEventListenerMessage::~WaveObjectManagerRegisterEventListenerMessage ()
{
}

UI32 WaveObjectManagerRegisterEventListenerMessage::getOperationCodeToListenFor () const
{
    return (m_operationCodeToListenFor);
}

void  WaveObjectManagerRegisterEventListenerMessage::setOperationCodeToListenFor (const UI32 &operationCodeToListenFor)
{
    m_operationCodeToListenFor = operationCodeToListenFor;
}

WaveServiceId WaveObjectManagerRegisterEventListenerMessage::getListenerWaveServiceId () const
{
    return (m_listenerWaveServiceId);
}

void  WaveObjectManagerRegisterEventListenerMessage::setListenerWaveServiceId (const WaveServiceId &listenerWaveServiceId)
{
    m_listenerWaveServiceId = listenerWaveServiceId;
}

LocationId WaveObjectManagerRegisterEventListenerMessage::getListenerLocationId () const
{
    return (m_listenerLocationId);
}

void  WaveObjectManagerRegisterEventListenerMessage::setListenerLocationId (const LocationId &listenerLocationId)
{
    m_listenerLocationId = listenerLocationId;
}

WaveFailoverObjectManagerMessage::WaveFailoverObjectManagerMessage (WaveServiceId id, const FrameworkObjectManagerFailoverReason &failoverReason, const bool isPrincipalChangedWithThisFailover)
    : WaveMessage (id, WAVE_OBJECT_MANAGER_FAILOVER),
      m_failoverReason (failoverReason),
      m_isPrincipalChangedWithThisFailover (isPrincipalChangedWithThisFailover)
{
}

WaveFailoverObjectManagerMessage::~WaveFailoverObjectManagerMessage ()
{
}

FrameworkObjectManagerFailoverReason WaveFailoverObjectManagerMessage::getFailoverReason () const
{
    return (m_failoverReason);
}

vector<LocationId> &WaveFailoverObjectManagerMessage::getFailedLocationIds ()
{
    return (m_failedLocationIds);
}

bool WaveFailoverObjectManagerMessage::getIsPrincipalChangedWithThisFailover () const
{
    return (m_isPrincipalChangedWithThisFailover);
}

WavePauseObjectManagerMessage::WavePauseObjectManagerMessage (WaveServiceId id)
    : WaveMessage (id, WAVE_OBJECT_MANAGER_PAUSE)
{
}

WaveResumeObjectManagerMessage::WaveResumeObjectManagerMessage (WaveServiceId id)
    : WaveMessage (id, WAVE_OBJECT_MANAGER_RESUME)
{
}

WaveSetCpuAffinityObjectManagerMessage::WaveSetCpuAffinityObjectManagerMessage (WaveServiceId id)
    : WaveMessage (id, WAVE_OBJECT_MANAGER_SET_CPU_AFFINITY)
{
}

vector<UI32> WaveSetCpuAffinityObjectManagerMessage::getCpuAffinityVector () const
{
    return (m_cpuAffinityVector);
}

void WaveSetCpuAffinityObjectManagerMessage::setCpuAffinityVector (const vector<UI32> &cpuAffinityVector)
{
    m_cpuAffinityVector = cpuAffinityVector;
}

WaveListenForEventsObjectManagerMessage::WaveListenForEventsObjectManagerMessage (WaveServiceId id)
    : WaveMessage (id, WAVE_OBJECT_MANAGER_LISTEN_FOR_EVENTS)
{
}

WaveLoadOperationalDataForManagedObjectObjectManagerMessage::WaveLoadOperationalDataForManagedObjectObjectManagerMessage ()
    : WaveMessage            (0, WAVE_OBJECT_MANAGER_LOAD_OPERATIONAL_DATA_FOR_MANAGED_OBJECT)
{
    setIsConfigurationChanged (false);
}

WaveLoadOperationalDataForManagedObjectObjectManagerMessage::WaveLoadOperationalDataForManagedObjectObjectManagerMessage (WaveServiceId id, ObjectId objectId, const vector<string> &operationalDataFields)
    : WaveMessage            (id, WAVE_OBJECT_MANAGER_LOAD_OPERATIONAL_DATA_FOR_MANAGED_OBJECT),
      m_objectId              (objectId),
      m_operationalDataFields (operationalDataFields)
{
    setIsConfigurationChanged (false);
}

void WaveLoadOperationalDataForManagedObjectObjectManagerMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeObjectId     (&m_objectId,              "objectId"));
     addSerializableAttribute (new AttributeStringVector (&m_operationalDataFields, "operationalDataFields"));
}

ObjectId WaveLoadOperationalDataForManagedObjectObjectManagerMessage::getObjectId () const
{
    return (m_objectId);
}

vector<string> WaveLoadOperationalDataForManagedObjectObjectManagerMessage::getOperationalDataFields () const
{
    return (m_operationalDataFields);
}

WaveHeartbeatFailureObjectManagerMessage::WaveHeartbeatFailureObjectManagerMessage (WaveServiceId id, IpV4Address ipAddress, UI16 portNumber)
	: WaveMessage            (id, WAVE_OBJECT_MANAGER_HEARTBEAT_FAILURE),
	  m_ipAddress             (ipAddress),
	  m_portNumber            (portNumber)
{
}

void WaveHeartbeatFailureObjectManagerMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

 	addSerializableAttribute (new AttributeIpV4Address  (&m_ipAddress,   "ipAddress"));
     addSerializableAttribute (new AttributeUI16         (&m_portNumber, "portNumber"));
}

IpV4Address WaveHeartbeatFailureObjectManagerMessage::getIpAddress() const
{
    return (m_ipAddress);
}

UI16 WaveHeartbeatFailureObjectManagerMessage::getPortNumber() const
{
    return (m_portNumber);
}

WaveExternalStateSynchronizationObjectManagerMessage::WaveExternalStateSynchronizationObjectManagerMessage (WaveServiceId id, UI32 fssStageNumber, ResourceId serviceType)
	: WaveMessage            (id, WAVE_OBJECT_MANAGER_EXTERNAL_STATE_SYNCHRONIZATION),
	  m_fssStageNumber        (fssStageNumber),
      m_serviceType           (serviceType)
{
}

void WaveExternalStateSynchronizationObjectManagerMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeUI32         (&m_fssStageNumber,    "fssStageNumber"));
     addSerializableAttribute (new AttributeResourceId   (&m_serviceType,       "serviceType"));
}

UI32 WaveExternalStateSynchronizationObjectManagerMessage::getFssStageNumber() const
{
    return (m_fssStageNumber);
}

ResourceId WaveExternalStateSynchronizationObjectManagerMessage::getServiceType() const
{
    return (m_serviceType);
}

WaveConfigReplayEndObjectManagerMessage::WaveConfigReplayEndObjectManagerMessage (WaveServiceId id)
	: WaveMessage            (id, WAVE_OBJECT_MANAGER_CONFIG_REPLAY_END)
{
}

void WaveConfigReplayEndObjectManagerMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();
}

WaveFileReplayEndObjectManagerMessage::WaveFileReplayEndObjectManagerMessage (WaveServiceId id)
	: WaveMessage            (id, WAVE_OBJECT_MANAGER_FILE_REPLAY_END)
{
}

void WaveFileReplayEndObjectManagerMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();
}

WaveSlotFailoverObjectManagerMessage::WaveSlotFailoverObjectManagerMessage (WaveServiceId id, UI32 slotNumber)
	: WaveMessage            (id, WAVE_OBJECT_MANAGER_SLOT_FAILOVER),
    m_slotNumber (slotNumber)
{
}

void WaveSlotFailoverObjectManagerMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeUI32         (&m_slotNumber, "slotNumber"));
}

UI32 WaveSlotFailoverObjectManagerMessage::getSlotNumber() const
{
    return (m_slotNumber);
}

WaveMultiPartitionCleanupObjectManagerMessage::WaveMultiPartitionCleanupObjectManagerMessage (WaveServiceId id, string &partitionName, ObjectId &ownerPartitionManagedObjectId)
    : WaveMessage          (id, WAVE_OBJECT_MANAGER_PARTITION_CLEANUP),
      m_partitionName          (partitionName),
      m_ownerPartitionManagedObjectId (ownerPartitionManagedObjectId),
      m_isPartialCleanup              (false),
      m_partialCleanupTag             (FRAMEWORK_ERROR)
{
}

ObjectId WaveMultiPartitionCleanupObjectManagerMessage::getOwnerPartitionManagedObjectId () const
{
    return (m_ownerPartitionManagedObjectId);
}

void WaveMultiPartitionCleanupObjectManagerMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeString       (&m_partitionName,     "partitionName"));
     addSerializableAttribute (new AttributeBool         (&m_isPartialCleanup,  "isPartialCleanup"));
     addSerializableAttribute (new AttributeResourceId   (&m_partialCleanupTag, "partialCleanupTag"));
}

string WaveMultiPartitionCleanupObjectManagerMessage::getPartitionName () const
{
    return (m_partitionName);
}

bool WaveMultiPartitionCleanupObjectManagerMessage::getIsPartialCleanup () const
{
    return m_isPartialCleanup;
}

void WaveMultiPartitionCleanupObjectManagerMessage::setPartialCleanupTag (const ResourceId &partialCleanupTag)
{
    m_isPartialCleanup  = true;

    m_partialCleanupTag = partialCleanupTag;
}

ResourceId WaveMultiPartitionCleanupObjectManagerMessage::getPartialCleanupTag ()
{
    waveAssert (true == m_isPartialCleanup, __FILE__, __LINE__);

    return m_partialCleanupTag;
}



WaveObjectManagerBackendSyncUpMessage::WaveObjectManagerBackendSyncUpMessage (WaveServiceId id)
    : WaveMessage            (id, WAVE_OBJECT_MANAGER_BACKEND_SYNC_UP)
{
}


WaveObjectManagerMessageHistoryConfigMessage::WaveObjectManagerMessageHistoryConfigMessage (WaveServiceId id)
    : WaveMessage              (id, WAVE_OBJECT_MANAGER_MESSAGE_HISTORY_CONFIG),
    m_messageHistoryState     (false),
    m_messageHistoryMaxSize   (0)
{
}

WaveObjectManagerMessageHistoryConfigMessage::~WaveObjectManagerMessageHistoryConfigMessage ()
{
}

void WaveObjectManagerMessageHistoryConfigMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeBool (&m_messageHistoryState,   "messageHistoryState"));
     addSerializableAttribute (new AttributeUI32 (&m_messageHistoryMaxSize, "messageHistoryMaxSize"));
}

bool WaveObjectManagerMessageHistoryConfigMessage::getMessageHistoryState () const
{
    return m_messageHistoryState;
}

void WaveObjectManagerMessageHistoryConfigMessage::setMessageHistoryState (bool messageHistoryState)
{
    m_messageHistoryState = messageHistoryState;
}

UI32 WaveObjectManagerMessageHistoryConfigMessage::getMessageHistoryMaxSize () const
{
    return m_messageHistoryMaxSize;
}

void WaveObjectManagerMessageHistoryConfigMessage::setMessageHistoryMaxSize (UI32 messageHistoryMaxSize)
{
    m_messageHistoryMaxSize = messageHistoryMaxSize;
}


WaveObjectManagerMessageHistoryDumpMessage::WaveObjectManagerMessageHistoryDumpMessage (WaveServiceId id)
    : WaveMessage              (id, WAVE_OBJECT_MANAGER_MESSAGE_HISTORY_DUMP)
{
}

WaveObjectManagerMessageHistoryDumpMessage::~WaveObjectManagerMessageHistoryDumpMessage ()
{
}

void WaveObjectManagerMessageHistoryDumpMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeStringVector (&m_messageHistoryDumpStringVector, "messageHistoryDumpStringVector"));
}

vector<string> &WaveObjectManagerMessageHistoryDumpMessage::getMessageHistoryDumpStringVector ()
{
    return m_messageHistoryDumpStringVector;
}

void WaveObjectManagerMessageHistoryDumpMessage::setMessageHistoryDumpStringVector (vector<string> &messageHistoryDumpStringVector)
{
    m_messageHistoryDumpStringVector = messageHistoryDumpStringVector;
}

WaveObjectManagerUpdateRelationshipMessage::WaveObjectManagerUpdateRelationshipMessage ()
    : WaveMessage (0, WAVE_OBJECT_MANAGER_UPDATE_RELATIONSHIP)
{
}

WaveObjectManagerUpdateRelationshipMessage::WaveObjectManagerUpdateRelationshipMessage (WaveServiceId id)
    : WaveMessage (id, WAVE_OBJECT_MANAGER_UPDATE_RELATIONSHIP)
{
}

WaveObjectManagerUpdateRelationshipMessage::WaveObjectManagerUpdateRelationshipMessage (WaveServiceId id, UI32 operationCode)
    : WaveMessage (id, operationCode)
{
}

WaveObjectManagerUpdateRelationshipMessage::~WaveObjectManagerUpdateRelationshipMessage ()
{
}

void WaveObjectManagerUpdateRelationshipMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeString       (&m_parentClassName,       "parentClassName"));
     addSerializableAttribute (new AttributeString       (&m_childClassName,        "childClassName"));
     addSerializableAttribute (new AttributeString       (&m_relationshipName,      "relationshipName"));
     addSerializableAttribute (new AttributeObjectId     (&m_parentObjectId,        "parentObjectId"));
     addSerializableAttribute (new AttributeObjectId     (&m_childObjectId,         "childObjectId"));
     addSerializableAttribute (new AttributeBool         (&m_isAddingRelationship,  "isAddingRelationship"));
}

void WaveObjectManagerUpdateRelationshipMessage::setRelationshipVariables (const string &parentClassName, const string &childClassName, const string &relationshipName, const ObjectId &parentObjectId, const ObjectId &childObjectId)
{
    m_parentClassName   = parentClassName;
    m_childClassName    = childClassName;
    m_relationshipName  = relationshipName;
    m_parentObjectId    = parentObjectId;
    m_childObjectId     = childObjectId;
}

void WaveObjectManagerUpdateRelationshipMessage::getRelationshipVariables (string &parentClassName, string &childClassName, string &relationshipName, ObjectId &parentObjectId, ObjectId &childObjectId)
{
    parentClassName     = m_parentClassName;
    childClassName      = m_childClassName;
    relationshipName    = m_relationshipName;
    parentObjectId      = m_parentObjectId;
    childObjectId       = m_childObjectId;
}

void WaveObjectManagerUpdateRelationshipMessage::setIsAddingRelationship (const bool &isAddingRelationship)
{
    m_isAddingRelationship = isAddingRelationship;
}

bool WaveObjectManagerUpdateRelationshipMessage::getIsAddingRelationship () const
{
    return (m_isAddingRelationship);
}

WaveObjectManagerUpdateWaveManagedObjectMessage::WaveObjectManagerUpdateWaveManagedObjectMessage ()
    : WaveMessage (0, WAVE_OBJECT_MANAGER_UPDATE_MANAGED_OBJECT),
      m_childUserTag (0),
      m_warningResourceId (0),
      m_isConfigReplayInProgress (false)
{
}

WaveObjectManagerUpdateWaveManagedObjectMessage::WaveObjectManagerUpdateWaveManagedObjectMessage (WaveServiceId id)
    : WaveMessage (id, WAVE_OBJECT_MANAGER_UPDATE_MANAGED_OBJECT),
      m_childUserTag (0),
      m_warningResourceId (0),
      m_isConfigReplayInProgress (false)
{
}

WaveObjectManagerUpdateWaveManagedObjectMessage::WaveObjectManagerUpdateWaveManagedObjectMessage (WaveServiceId id, UI32 operationCode)
    : WaveMessage (id, operationCode),
      m_childUserTag (0),
      m_warningResourceId (0),
      m_isConfigReplayInProgress (false)
{
}

WaveObjectManagerUpdateWaveManagedObjectMessage::~WaveObjectManagerUpdateWaveManagedObjectMessage ()
{
}

void WaveObjectManagerUpdateWaveManagedObjectMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeObjectId     (&m_inputWaveManagedObjectId,      "inputWaveManagedObjectId"));
     addSerializableAttribute (new AttributeObjectId     (&m_operateOnWaveManagedObjectId,  "operateOnWaveManagedObjectId"));
     addSerializableAttribute (new AttributeUI32Vector   (&m_attributeUserTags,             "attributeUserTags"));
     addSerializableAttribute (new AttributeStringVector (&m_attributeNames,                "attributeNames"));
     addSerializableAttribute (new AttributeStringVector (&m_attributeValues,               "attributeValues"));
     addSerializableAttribute (new AttributeObjectId     (&m_parentObjectId,                "parentObjectId"));
     addSerializableAttribute (new AttributeUI32         (&m_childUserTag,                  "childUserTag"));
     addSerializableAttribute (new AttributeUI32         (&m_choiceUserTag,                 "choiceUserTag"));
     addSerializableAttribute (new AttributeBool         (&m_isErrorCode,                   "isErrorCode"));
     addSerializableAttribute (new AttributeUI32         (&m_choiceUserTagNeedToRemove,     "choiceUserTagNeedToRemove"));
     addSerializableAttribute (new AttributeUI32         (&m_warningResourceId,             "warningResourceId"));
     addSerializableAttribute (new AttributeBool         (&m_isConfigReplayInProgress,      "isConfigReplayInProgress"));
}

ObjectId WaveObjectManagerUpdateWaveManagedObjectMessage::getInputWaveManagedObjectId() const
{
    return (m_inputWaveManagedObjectId);
}

void WaveObjectManagerUpdateWaveManagedObjectMessage::setInputWaveManagedObjectId(const WaveNs::ObjectId& waveManagedObjectId)
{
    m_inputWaveManagedObjectId = waveManagedObjectId;
}

ObjectId WaveObjectManagerUpdateWaveManagedObjectMessage::getOperateOnWaveManagedObjectId() const
{
    return (m_operateOnWaveManagedObjectId);
}

void WaveObjectManagerUpdateWaveManagedObjectMessage::setOperateOnWaveManagedObjectId(const WaveNs::ObjectId& waveManagedObjectId)
{
    m_operateOnWaveManagedObjectId = waveManagedObjectId;
}

vector<UI32> WaveObjectManagerUpdateWaveManagedObjectMessage::getAttributeUserTags () const
{
    return (m_attributeUserTags);
}

void WaveObjectManagerUpdateWaveManagedObjectMessage::setAttributeUserTags(const std::vector< UI32 >& attributeUserTags)
{
    if ((0 != (m_attributeNames.size ())) && (0 != attributeUserTags.size ()))
    {
        waveAssert (false, __FILE__, __LINE__);
    }

    m_attributeUserTags = attributeUserTags;
}

vector<string> WaveObjectManagerUpdateWaveManagedObjectMessage::getAttributeNames () const
{
    return (m_attributeNames);
}

void WaveObjectManagerUpdateWaveManagedObjectMessage::setAttributeNames (const vector<string> &attributeNames)
{
    if ((0 != (m_attributeUserTags.size ())) && (0 != attributeNames.size ()))
    {
        waveAssert (false, __FILE__, __LINE__);
    }

    m_attributeNames = attributeNames;
}

vector<string> WaveObjectManagerUpdateWaveManagedObjectMessage::getAttributeValues () const
{
    return (m_attributeValues);
}

void WaveObjectManagerUpdateWaveManagedObjectMessage::setAttributeValues (const vector< string >& attributeValues)
{
    m_attributeValues = attributeValues;
}

ObjectId WaveObjectManagerUpdateWaveManagedObjectMessage::getParentObjectId () const
{
    return (m_parentObjectId);
}

void WaveObjectManagerUpdateWaveManagedObjectMessage::setParentObjectId (const ObjectId &parentObjectId)
{
    m_parentObjectId = parentObjectId;
}

UI32 WaveObjectManagerUpdateWaveManagedObjectMessage::getChildUserTag () const
{
    return (m_childUserTag);
}

void WaveObjectManagerUpdateWaveManagedObjectMessage::setChildUserTag (const UI32 &childUserTag)
{
    m_childUserTag = childUserTag;
}

UI32 WaveObjectManagerUpdateWaveManagedObjectMessage::getChoiceUserTag () const
{
    return (m_choiceUserTag);
}

void WaveObjectManagerUpdateWaveManagedObjectMessage::setChoiceUserTag (const UI32 &choiceUserTag)
{
    m_choiceUserTag = choiceUserTag;
}

bool WaveObjectManagerUpdateWaveManagedObjectMessage::getIsPropagateErrorCodeNeeded () const
{
    return (m_isErrorCode);
}

void WaveObjectManagerUpdateWaveManagedObjectMessage::setIsPropagateErrorCodeNeeded (const bool isErrorCode)
{
    m_isErrorCode = isErrorCode;
}

void WaveObjectManagerUpdateWaveManagedObjectMessage::setChoiceUserTagNeedToRemove (const UI32 &choiceUserTagNeedToRemove)
{
    m_choiceUserTagNeedToRemove = choiceUserTagNeedToRemove;
}

UI32 WaveObjectManagerUpdateWaveManagedObjectMessage::getChoiceUserTagNeedToRemove () const
{
    return (m_choiceUserTagNeedToRemove);
}

void WaveObjectManagerUpdateWaveManagedObjectMessage::setWarningResourceId (const UI32 warningResourceId)
{
    m_warningResourceId = warningResourceId;
}

UI32 WaveObjectManagerUpdateWaveManagedObjectMessage::getWarningResourceId () const
{
    return (m_warningResourceId);
}

void WaveObjectManagerUpdateWaveManagedObjectMessage::setConfigReplayInProgressFlag (const bool isConfigReplayInProgress)
{
    m_isConfigReplayInProgress = isConfigReplayInProgress;
}

bool WaveObjectManagerUpdateWaveManagedObjectMessage::getConfigReplayInProgressFlag () const
{
    return (m_isConfigReplayInProgress);
}


WaveObjectManagerCreateWaveManagedObjectMessage::WaveObjectManagerCreateWaveManagedObjectMessage ()
    : WaveObjectManagerUpdateWaveManagedObjectMessage (0, WAVE_OBJECT_MANAGER_CREATE_MANAGED_OBJECT)
{
}

WaveObjectManagerCreateWaveManagedObjectMessage::WaveObjectManagerCreateWaveManagedObjectMessage (WaveServiceId id)
    : WaveObjectManagerUpdateWaveManagedObjectMessage (id, WAVE_OBJECT_MANAGER_CREATE_MANAGED_OBJECT)
{
}

WaveObjectManagerCreateWaveManagedObjectMessage::~WaveObjectManagerCreateWaveManagedObjectMessage ()
{
}

void WaveObjectManagerCreateWaveManagedObjectMessage::setupAttributesForSerialization ()
{
    WaveObjectManagerUpdateWaveManagedObjectMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeString     (&m_managedObjectClassName, "managedObjectClassName"));
}

string WaveObjectManagerCreateWaveManagedObjectMessage::getManagedObjectClassNameNeedToBeCreated () const
{
    return (m_managedObjectClassName);
}

void WaveObjectManagerCreateWaveManagedObjectMessage::setManagedObjectClassNameNeedToBeCreated (const string &managedObjectClassName)
{
    m_managedObjectClassName = managedObjectClassName;
}

ObjectId WaveObjectManagerCreateWaveManagedObjectMessage::getObjectId () const
{
    return (m_objectId);
}

void WaveObjectManagerCreateWaveManagedObjectMessage::setObjectId (const WaveNs::ObjectId& objectId)
{
    m_objectId = objectId;
}

WaveZeroizeObjectManagerMessage::WaveZeroizeObjectManagerMessage (WaveServiceId id)
    : WaveMessage (id, WAVE_OBJECT_MANAGER_FIPS_ZEROIZE)
{
}

WaveObjectManagerGetDebugInformationMessage::WaveObjectManagerGetDebugInformationMessage ()
    : ManagementInterfaceMessage ("", WAVE_OBJECT_MANAGER_GET_DEBUG_INFORMATION)
{
    // An empty service string name is equivalent to wave service id 0

    setIsMessageSupportedWhenServiceIsPaused (true);
}

WaveObjectManagerGetDebugInformationMessage::WaveObjectManagerGetDebugInformationMessage (const string &serviceName)
    : ManagementInterfaceMessage (serviceName, WAVE_OBJECT_MANAGER_GET_DEBUG_INFORMATION)
{
    setIsMessageSupportedWhenServiceIsPaused (true);
}

WaveObjectManagerGetDebugInformationMessage::~WaveObjectManagerGetDebugInformationMessage ()
{
}

void WaveObjectManagerGetDebugInformationMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeString   (&m_debugInformation, "debugInformation"));
}

void WaveObjectManagerGetDebugInformationMessage::setDebugInformation (const string &debugInformation)
{
    m_debugInformation = debugInformation;
}

const string & WaveObjectManagerGetDebugInformationMessage::getDebugInformation () const
{
    return (m_debugInformation);
}

WaveObjectManagerResetDebugInformationMessage::WaveObjectManagerResetDebugInformationMessage ()
    : ManagementInterfaceMessage ("", WAVE_OBJECT_MANAGER_RESET_DEBUG_INFORMATION)
{
    // An empty service string name is equivalent to wave service id 0

    setIsMessageSupportedWhenServiceIsPaused (true);
}

WaveObjectManagerResetDebugInformationMessage::WaveObjectManagerResetDebugInformationMessage (const string &serviceName)
    : ManagementInterfaceMessage (serviceName, WAVE_OBJECT_MANAGER_RESET_DEBUG_INFORMATION)
{
    setIsMessageSupportedWhenServiceIsPaused (true);
}

WaveObjectManagerResetDebugInformationMessage::~WaveObjectManagerResetDebugInformationMessage ()
{
}

WaveObjectManagerDeleteWaveManagedObjectMessage::WaveObjectManagerDeleteWaveManagedObjectMessage ()
    :  WaveObjectManagerUpdateWaveManagedObjectMessage (0, WAVE_OBJECT_MANAGER_DELETE_MANAGED_OBJECT)
{
}

WaveObjectManagerDeleteWaveManagedObjectMessage::WaveObjectManagerDeleteWaveManagedObjectMessage (WaveServiceId id)
    : WaveObjectManagerUpdateWaveManagedObjectMessage (id, WAVE_OBJECT_MANAGER_DELETE_MANAGED_OBJECT)
{
}

WaveObjectManagerDeleteWaveManagedObjectMessage::WaveObjectManagerDeleteWaveManagedObjectMessage (WaveServiceId id, UI32 operationCode)
    : WaveObjectManagerUpdateWaveManagedObjectMessage (id, operationCode)
{
}

WaveObjectManagerDeleteWaveManagedObjectMessage::~WaveObjectManagerDeleteWaveManagedObjectMessage ()
{
}

void WaveObjectManagerDeleteWaveManagedObjectMessage::setupAttributesForSerialization ()
{
    WaveObjectManagerUpdateWaveManagedObjectMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeUI32 (&m_isMO, "isMO"));
}

UI32 WaveObjectManagerDeleteWaveManagedObjectMessage::getIsMO () const
{
    return (m_isMO);
}

void WaveObjectManagerDeleteWaveManagedObjectMessage::setIsMO(const UI32 &isMO)
{
    m_isMO = isMO;
}

WaveObjectManagerDeleteWaveManagedObjectsMessage::WaveObjectManagerDeleteWaveManagedObjectsMessage ()
    :   WaveObjectManagerDeleteWaveManagedObjectMessage (0, WAVE_OBJECT_MANAGER_DELETE_MANAGED_OBJECTS)
{
}

WaveObjectManagerDeleteWaveManagedObjectsMessage::WaveObjectManagerDeleteWaveManagedObjectsMessage (WaveServiceId id)
    :   WaveObjectManagerDeleteWaveManagedObjectMessage (id, WAVE_OBJECT_MANAGER_DELETE_MANAGED_OBJECTS)
{
}

WaveObjectManagerDeleteWaveManagedObjectsMessage::~WaveObjectManagerDeleteWaveManagedObjectsMessage ()
{
}

void WaveObjectManagerDeleteWaveManagedObjectsMessage::setupAttributesForSerialization ()
{
    WaveObjectManagerDeleteWaveManagedObjectMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeObjectIdVector     (&m_ManagedObjectIdVector,       "ManagedObjectIdVector"));
     addSerializableAttribute (new AttributeStringVectorVector (&m_AttributeNameVectorVector,   "AttributeNameVectorVector"));
     addSerializableAttribute (new AttributeUI32VectorVector   (&m_AttributeUserTagVectorVector,"AttributeUserTagVectorVector"));
}

vector<ObjectId>  WaveObjectManagerDeleteWaveManagedObjectsMessage::getManagedObjectsIdVector () const
{
    return (m_ManagedObjectIdVector);
}

void WaveObjectManagerDeleteWaveManagedObjectsMessage::setManagedObjectsIdVector (const vector<ObjectId> &ManagedObjectIdVector)
{
     m_ManagedObjectIdVector = ManagedObjectIdVector;
}

vector<vector<string> > WaveObjectManagerDeleteWaveManagedObjectsMessage::getAttributeNameVectorVector () const
{
    return (m_AttributeNameVectorVector);
}

void WaveObjectManagerDeleteWaveManagedObjectsMessage::setAttributeNameVectorVector (const vector<vector<string> > &AttributeNameVectorVector)
{
    m_AttributeNameVectorVector = AttributeNameVectorVector;
}

vector<vector<UI32> > WaveObjectManagerDeleteWaveManagedObjectsMessage::getAttributeUserTagVectorVector () const
{
    return (m_AttributeUserTagVectorVector);
}

void WaveObjectManagerDeleteWaveManagedObjectsMessage::setAttributeUserTagVectorVector (const vector<vector<UI32> > &AttributeUserTagVectorVector)
{
    m_AttributeUserTagVectorVector = AttributeUserTagVectorVector;
}


WaveObjectManagerGetDataFromClientMessage::WaveObjectManagerGetDataFromClientMessage ()
 : WaveMessage ( 0, WAVE_OBJECT_MANAGER_GET_CLIENT_DATA )
{
    m_commandCode = 0;
    m_commandType = 0;
    m_enablePaginate = false;
    m_localPluginServiceCode = 0;
    m_globalPluginServiceCode = 0;
    m_numberOfRecordsRequested = 0;
    m_sendToClusterRequested = false;
    m_numberOfCommandStrings = 0;
}

WaveObjectManagerGetDataFromClientMessage::WaveObjectManagerGetDataFromClientMessage ( WaveServiceId id )
 : WaveMessage ( id, WAVE_OBJECT_MANAGER_GET_CLIENT_DATA )
{
    m_commandCode = 0;
    m_commandType = 0;
    m_enablePaginate = false;
    m_localPluginServiceCode = 0;
    m_globalPluginServiceCode = 0;
    m_numberOfRecordsRequested = 0;
    m_sendToClusterRequested = false;
    m_numberOfCommandStrings = 0;
}

WaveObjectManagerGetDataFromClientMessage::WaveObjectManagerGetDataFromClientMessage ( WaveServiceId id, UI32 commandCode, UI32 commandType, bool sendToClusterRequested )
 : WaveMessage ( id, WAVE_OBJECT_MANAGER_GET_CLIENT_DATA ),
   m_commandCode ( commandCode ),
   m_commandType ( commandType ),
   m_sendToClusterRequested ( sendToClusterRequested )
{
    m_enablePaginate = false;
    m_localPluginServiceCode = 0;
    m_globalPluginServiceCode = 0;
    m_numberOfRecordsRequested = 0;
    m_numberOfCommandStrings = 0;
}

WaveObjectManagerGetDataFromClientMessage::~WaveObjectManagerGetDataFromClientMessage ()
{

}

void WaveObjectManagerGetDataFromClientMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeString (&m_clientName, "clientName"));
    addSerializableAttribute (new AttributeUI32 (&m_commandCode, "commandCode"));
    addSerializableAttribute (new AttributeUI32 (&m_commandType, "commandType"));
    addSerializableAttribute (new AttributeLocationIdVector (&m_selectedNodes, "selectedNodes"));
    addSerializableAttribute (new AttributeBoolVector (&m_moreRecordsVector, "moreRecordsVector"));
    addSerializableAttribute (new AttributeUI32 (&m_localPluginServiceCode, "localPluginServiceCode"));
    addSerializableAttribute (new AttributeUI32 (&m_numberOfRecordsRequested, "numberOfRecordsRequested"));
    addSerializableAttribute (new AttributeBool (&m_sendToClusterRequested, "sendToClusterRequested"));
    addSerializableAttribute (new AttributeSI32 (&m_numberOfCommandStrings, "numberOfCommandStrings"));
    addSerializableAttribute (new AttributeStringVector (&m_commandStrings, "commandStrings"));
}

void WaveObjectManagerGetDataFromClientMessage::setEnablePaginate ( const bool &enablePaginate )
{
    m_enablePaginate = enablePaginate;
}

bool WaveObjectManagerGetDataFromClientMessage::getEnablePaginate ( ) const
{
    bool enablePaginate = m_enablePaginate;
    return (enablePaginate);
}

void WaveObjectManagerGetDataFromClientMessage::setClientName ( const string &clientName )
{
    m_clientName = clientName;
}

void WaveObjectManagerGetDataFromClientMessage::getClientName ( string &clientName ) const
{
    clientName = m_clientName;
}

void WaveObjectManagerGetDataFromClientMessage::setSelectedNodes ( const vector<LocationId> &selectedNodes )
{
    m_selectedNodes = selectedNodes ;
}

void WaveObjectManagerGetDataFromClientMessage::getSelectedNodes ( vector<LocationId> &selectedNodes ) const
{
    selectedNodes = m_selectedNodes;
}

void WaveObjectManagerGetDataFromClientMessage::setGlobalPluginServiceCode ( const UI32 &globalPluginServiceCode )
{
    m_globalPluginServiceCode = globalPluginServiceCode;
}

UI32 WaveObjectManagerGetDataFromClientMessage::getGlobalPluginServiceCode ( ) const
{
    UI32 globalPluginServiceCode = m_globalPluginServiceCode;
    return ( globalPluginServiceCode );
}

void WaveObjectManagerGetDataFromClientMessage::setLocalPluginServiceCode ( const UI32 &localPluginServiceCode )
{
    m_localPluginServiceCode = localPluginServiceCode;
}

UI32 WaveObjectManagerGetDataFromClientMessage::getLocalPluginServiceCode ( ) const
{
    UI32 localPluginServiceCode = m_localPluginServiceCode;
    return (localPluginServiceCode);
}

void WaveObjectManagerGetDataFromClientMessage::setNewServiceCode ( const UI32 &serviceCode )
{
    setServiceCode(serviceCode);
}

void WaveObjectManagerGetDataFromClientMessage::setCommandCode ( const UI32 &commandCode )
{
    m_commandCode = commandCode ;
}

UI32 WaveObjectManagerGetDataFromClientMessage::getCommandCode ( ) const
{
    UI32 commandCode = m_commandCode ;
    return ( commandCode );
}

void WaveObjectManagerGetDataFromClientMessage::setCommandType ( const UI32 &commandType )
{
    m_commandType = commandType ;
}

UI32 WaveObjectManagerGetDataFromClientMessage::getCommandType ( ) const
{
    UI32 commandType = m_commandType ;
    return ( commandType );
}

void WaveObjectManagerGetDataFromClientMessage::setNumberOfRecordsRequested ( const UI32 &numberOfRecordsRequested )
{
    m_numberOfRecordsRequested = numberOfRecordsRequested ;
}

UI32 WaveObjectManagerGetDataFromClientMessage::getNumberOfRecordsRequested ( ) const
{
    UI32 numberOfRecordsRequested = m_numberOfRecordsRequested ;
    return ( numberOfRecordsRequested );
}

void WaveObjectManagerGetDataFromClientMessage::addToMoreRecordsVector ( const bool &moreRecord )
{
    m_moreRecordsVector.push_back( moreRecord );
}

void WaveObjectManagerGetDataFromClientMessage::getMoreRecordsVector ( vector<bool> &moreRecordsVector ) const
{
    moreRecordsVector = m_moreRecordsVector;
}

void WaveObjectManagerGetDataFromClientMessage::setSendToClusterRequested ( const bool &sendToClusterRequested )
{
    m_sendToClusterRequested = sendToClusterRequested;
}

bool WaveObjectManagerGetDataFromClientMessage::getSendToClusterRequested ( ) const
{
    return (m_sendToClusterRequested);
}

void WaveObjectManagerGetDataFromClientMessage::setNumberOfCommandStrings (const SI32 numberOfCommandStrings)
{
    m_numberOfCommandStrings = numberOfCommandStrings;
}

SI32 WaveObjectManagerGetDataFromClientMessage::getNumberOfCommandStrings () const
{
    return (m_numberOfCommandStrings);
}

void WaveObjectManagerGetDataFromClientMessage::setCommandStrings (const vector<string> &commandStrings)
{
    m_commandStrings = commandStrings;
}

vector<string> WaveObjectManagerGetDataFromClientMessage::getCommandStrings () const
{
    return (m_commandStrings);
}

void WaveObjectManagerGetDataFromClientMessage::copyClientDataFromMessage ( WaveMessage *pWaveMessage )
{
    vector<UI32> bufferTags;
    pWaveMessage->getBufferTags(bufferTags);

    // This function is used when data sent from Client is received on the same node. To maintain uniqueness in buffer tag
    // we replace tag with locationId of the receiver. This removes conflict during collation of client data from all nodes
    //Since the tag is replaced with LocationId, only single buffer is supported
    waveAssert ( 1 >= bufferTags.size(), __FILE__, __LINE__);

    trace (TRACE_LEVEL_DEVEL, string("WaveOperationalDataObjectGetWorker::copyClientDataFromMessage : response buffer size is ") +  bufferTags.size());

    for ( UI32 i = 0 ; i < bufferTags.size() ; i++)
    {
        UI32 size = 0;
        void * pBuffer = NULL;
        pBuffer = pWaveMessage->transferBufferToUser(bufferTags[i],size);
        waveAssert ( NULL != pBuffer, __FILE__, __LINE__);
        //Dont free the buffer since it is owned by message
        this->addBuffer( FrameworkToolKit::getThisLocationId(), size, pBuffer, true);
        pBuffer = NULL;
    }

    bufferTags.clear();
}

void WaveObjectManagerGetDataFromClientMessage::copyAllBuffersFromMessage ( const WaveMessage *pWaveMessage )
{
    trace (TRACE_LEVEL_DEVEL, string("WaveObjectManagerGetDataFromClientMessage::copyAllBuffersFromMessage : Buffer size=") + pWaveMessage->getNumberOfBuffers ());
    this->copyBuffersFrom( *pWaveMessage );
}

void WaveObjectManagerGetDataFromClientMessage::getDataSentFromAllClients ( vector<LocationId> &selectedNodes, vector<UI32> &clientStatus, vector<void *> &buffers, vector<bool> &moreRecordsVector )
{
    selectedNodes.clear();
    this->getSelectedNodes(selectedNodes);

    // Make sure this is inorder of selected nodes
    this->getMoreRecordsVector ( moreRecordsVector);
    trace (TRACE_LEVEL_DEVEL, string("WaveObjectManagerGetDataFromClientMessage::getDataSentFromAllClients : Nodes size is ") + selectedNodes.size());


    //TestingBegin
    /*
    vector<UI32> bufferTags;
    getBufferTags(bufferTags);

    for ( UI32 j = 0 ; j < bufferTags.size() ; j++)
        {
            UI32 size = 0;
            void * pBuffer = NULL;
            pBuffer = findBuffer(bufferTags[j],size);
            emp_t *pEmp_t = (emp_t *) pBuffer;
            waveAssert ( NULL != pBuffer, __FILE__, __LINE__);
            //Dont free the buffer since it is owned by message
            trace (TRACE_LEVEL_INFO, string("WaveOperationalDataObjectGetWorker::sendMessageToAllNodesStepCallback : response buffer size is ") + size + (" ,x is -> ") + pEmp_t->x + (" flag is -> ") + pEmp_t->flag + (" tag is ") + bufferTags[j]);
            pBuffer = NULL;
        }

    */
    //Testing End

    for ( UI32 i = 0; i < selectedNodes.size(); i++)
    {
        bool found = false;
        ResourceId status = WAVE_MESSAGE_ERROR;
        UI32 size;
        void * pBuffer = NULL;
        string localizedStatus = "";

        found = this->getStatusPropagationByLocationId(status, localizedStatus, selectedNodes[i]);

        trace (TRACE_LEVEL_DEVEL, string("WaveObjectManagerGetDataFromClientMessage::getDataSentFromAllClients : selected node is  ") + selectedNodes[i]);

        if ( found )
        {
            trace (TRACE_LEVEL_DEVEL, string("WaveObjectManagerGetDataFromClientMessage::getDataSentFromAllClients : client status is ") + FrameworkToolKit::localize( status ));
            clientStatus.push_back(status);
        }
        else
        {
            trace (TRACE_LEVEL_DEVEL, string("WaveObjectManagerGetDataFromClientMessage::getDataSentFromAllClients : client status not found "));
            waveAssert ( false, __FILE__, __LINE__);
        }

        // Buffer tag would be locationId of the selected nodes
        pBuffer = transferBufferToUser(selectedNodes[i],size);

        if (!pBuffer)
        {
            trace (TRACE_LEVEL_INFO, string("WaveObjectManagerGetDataFromClientMessage::getDataSentFromAllClients : BUFFER is NULL") );
        }

        buffers.push_back(pBuffer);
        pBuffer= NULL;
    }

}

WaveDeliverBrokerPublishMessage::WaveDeliverBrokerPublishMessage (WaveServiceId waveServiceId)
    : WaveMessage                (waveServiceId, WAVE_OBJECT_MANAGER_DELIVER_WAVE_BROKER_PUBLISH_MESSAGE),
      m_pWaveBrokerPublishMessage (NULL)
{
}

WaveDeliverBrokerPublishMessage::~WaveDeliverBrokerPublishMessage ()
{
}

WaveBrokerPublishMessage *WaveDeliverBrokerPublishMessage::getPWaveBrokerPublishMessage ()
{
    return (m_pWaveBrokerPublishMessage);
}

void WaveDeliverBrokerPublishMessage::setPWaveBrokerPublishMessage (WaveBrokerPublishMessage *pWaveBrokerPublishMessage)
{
    m_pWaveBrokerPublishMessage = pWaveBrokerPublishMessage;
}

WaveDeliverLightPulseMessage::WaveDeliverLightPulseMessage (WaveServiceId waveServiceId)
    : WaveMessage   (waveServiceId, WAVE_OBJECT_MANAGER_DELIVER_WAVE_LIGHT_PULSE_MESSAGE),
      m_pLightPulse (NULL)
{
}

WaveDeliverLightPulseMessage::~WaveDeliverLightPulseMessage ()
{
}

LightPulse *WaveDeliverLightPulseMessage::getPLightPulse ()
{
    return (m_pLightPulse);
}

void WaveDeliverLightPulseMessage::setPLightPulse (LightPulse *pLightPulse)
{
    m_pLightPulse = pLightPulse;
}

}

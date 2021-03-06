/***************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/Messaging/Local/WaveMessage.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForPostbootPhase.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForShutdownPhases.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForExternalStateSynchronization.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForConfigReplayEnd.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForFileReplayEnd.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForSlotFailover.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForMultiPartitionCleanup.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForUpgradePhase.h"
#include "Framework/Failover/FailoverAsynchronousContext.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForDebugInformation.h"
#include "Framework/ObjectModel/WaveObjectManagerStatisticsTracker.h"
#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContextForDeletion.h"
#include "Framework/ObjectModel/WaveSendMulticastContext.h"
#include "Framework/ObjectModel/WaveObjectManagerCommitTransactionContext.h"
#include "Framework/CliBlockManagement/CliBlockMessage.h"
#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveBrokerPublishMessage.h"

#include <stdarg.h>

using namespace std;

namespace WaveNs
{

WaveWorker::WaveWorker (WaveObjectManager *pWaveObjectManager)
    : WaveElement                      (pWaveObjectManager),
      m_linkWorkerToParentObjectManager (true)
{
    if (true == m_linkWorkerToParentObjectManager)
    {
        m_pWaveObjectManager->addWorker (this);
    }
}

// this form of the constructor is called by dynamic threads, worker is not added to the object manager worker vector, *p is a dummy parameter to overload the constructor
WaveWorker::WaveWorker (WaveObjectManager *pWaveObjectManager, const bool &linkWorkerToParentObjectManager)
    : WaveElement                      (pWaveObjectManager),
      m_linkWorkerToParentObjectManager (linkWorkerToParentObjectManager)
{
    if (true == m_linkWorkerToParentObjectManager)
    {
        m_pWaveObjectManager->addWorker (this);
    }
}

WaveWorker::~WaveWorker ()
{
    // Dynamic worker threads like postBootAgent are not added to the worker list so they can't be removed, other workers should be removed on destruction

    if (true == m_linkWorkerToParentObjectManager)
    {
        m_pWaveObjectManager->removeWorker (this);
    }
}


void WaveWorker::initialize (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    trace (TRACE_LEVEL_DEVEL, "WaveWorker::initialize : Entering ...");

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void WaveWorker::listenForEvents (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    trace (TRACE_LEVEL_DEVEL, "WaveWorker::listenForEvents : Entering ...");

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void WaveWorker::install (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    trace (TRACE_LEVEL_DEVEL, "WaveWorker::install : Entering ...");

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void WaveWorker::enable (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    trace (TRACE_LEVEL_DEVEL, "WaveWorker::enable : Entering ...");

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void WaveWorker::upgrade (WaveAsynchronousContextForUpgradePhase *pWaveAsynchronousContextForUpgradePhase)
{
    trace (TRACE_LEVEL_DEVEL, "WaveWorker::upgrade : Entering ...");

    pWaveAsynchronousContextForUpgradePhase->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForUpgradePhase->callback ();
}

void WaveWorker::boot (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    trace (TRACE_LEVEL_DEVEL, "WaveWorker::boot : Entering ...");

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void WaveWorker::hainstall (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    trace (TRACE_LEVEL_DEVEL, "WaveWorker::hainstall : Entering ...");

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void WaveWorker::haboot (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    trace (TRACE_LEVEL_DEVEL, "WaveWorker::haboot : Entering ...");

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void WaveWorker::postboot (WaveAsynchronousContextForPostbootPhase *pWaveAsynchronousContextForPostbootPhase)
{
    trace (TRACE_LEVEL_DEVEL, string("WaveWorker::postboot : Entering with pass#:") + pWaveAsynchronousContextForPostbootPhase->getPassNum());

    pWaveAsynchronousContextForPostbootPhase->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForPostbootPhase->callback ();
}

void WaveWorker::heartBeatFailure (WaveAsynchronousContext *pWaveAsynchronousContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveWorker::heartBeatFailure : Entering ...");

    pWaveAsynchronousContext->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContext->callback ();
}

void WaveWorker::externalStateSynchronization (WaveAsynchronousContextForExternalStateSynchronization *pWaveAsynchronousContextForExternalStateSynchronization)
{
    trace (TRACE_LEVEL_DEVEL, "WaveWorker::externalStateSynchronization : Entering ...");

    pWaveAsynchronousContextForExternalStateSynchronization->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForExternalStateSynchronization->callback ();
}

void WaveWorker::configReplayEnd (WaveAsynchronousContextForConfigReplayEnd *pWaveAsynchronousContextForConfigReplayEnd)
{
    trace (TRACE_LEVEL_DEVEL, "WaveWorker::configReplayEnd : Entering ...");

    pWaveAsynchronousContextForConfigReplayEnd->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForConfigReplayEnd->callback ();
}

void WaveWorker::fileReplayEnd (WaveAsynchronousContextForFileReplayEnd *pWaveAsynchronousContextForFileReplayEnd)
{
    trace (TRACE_LEVEL_DEVEL, "WaveWorker::fileReplayEnd : Entering ...");

    pWaveAsynchronousContextForFileReplayEnd->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForFileReplayEnd->callback ();
}

void WaveWorker::slotFailover (WaveAsynchronousContextForSlotFailover *pWaveAsynchronousContextForSlotFailover)
{
    trace (TRACE_LEVEL_DEVEL, "WaveWorker::slotFailover : Entering ...");

    pWaveAsynchronousContextForSlotFailover->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForSlotFailover->callback ();
}

void WaveWorker::multiPartitionCleanup (WaveAsynchronousContextForMultiPartitionCleanup *pWaveAsynchronousContextForMultiPartitionCleanup)
{
    trace (TRACE_LEVEL_DEVEL, "WaveWorker::multiPartitionCleanup : Entering ...");

    pWaveAsynchronousContextForMultiPartitionCleanup->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForMultiPartitionCleanup->callback ();
}

void WaveWorker::multiPartitionPartialCleanup (WaveAsynchronousContextForMultiPartitionCleanup *pWaveAsynchronousContextForMultiPartitionCleanup)
{
    trace (TRACE_LEVEL_DEVEL, "WaveWorker::multiPartitionPartialCleanup : Entering ...");

    waveAssert (true == pWaveAsynchronousContextForMultiPartitionCleanup->getIsPartialCleanup (), __FILE__, __LINE__);

    pWaveAsynchronousContextForMultiPartitionCleanup->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForMultiPartitionCleanup->callback ();
}

void WaveWorker::shutdown (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases)
{
    trace (TRACE_LEVEL_DEVEL, "WaveWorker::shutdown : Entering ...");

    pWaveAsynchronousContextForShutDownPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForShutDownPhases->callback ();
}

void WaveWorker::uninstall (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases)
{
    trace (TRACE_LEVEL_DEVEL, "WaveWorker::uninstall : Entering ...");

    pWaveAsynchronousContextForShutDownPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForShutDownPhases->callback ();
}

void WaveWorker::disable (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases)
{
    trace (TRACE_LEVEL_DEVEL, "WaveWorker::disable : Entering ...");

    pWaveAsynchronousContextForShutDownPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForShutDownPhases->callback ();
}

void WaveWorker::unlistenEvents ()
{
    trace (TRACE_LEVEL_DEVEL, "WaveWorker::unlistenEvents : Entering ...");

    m_pWaveObjectManager->unlistenEvents ();
}

void WaveWorker::uninitialize (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases)
{
    trace (TRACE_LEVEL_DEVEL, "WaveWorker::uninitialize : Entering ...");

    pWaveAsynchronousContextForShutDownPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForShutDownPhases->callback ();
}

void WaveWorker::destruct (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases)
{
    trace (TRACE_LEVEL_DEVEL, "WaveWorker::destruct : Entering ...");

    pWaveAsynchronousContextForShutDownPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForShutDownPhases->callback ();
}

void WaveWorker::backendSyncUp (WaveAsynchronousContext *pWaveAsynchronousContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveWorker::backendSyncUp : Entering ...");

    pWaveAsynchronousContext->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContext->callback ();
}

WaveMessageStatus WaveWorker::send  (WaveMessage *pWaveMessage, WaveMessageResponseHandler pWaveMessageCallback, void *pWaveMessageContext, UI32 timeOutInMilliSeconds, LocationId locationId, WaveElement *pWaveMessageSender)
{
    return (m_pWaveObjectManager->send (pWaveMessage, pWaveMessageCallback, pWaveMessageContext, timeOutInMilliSeconds, locationId, pWaveMessageSender != NULL ? pWaveMessageSender : this));
}

WaveMessageStatus WaveWorker::sendOneWay (WaveMessage *pWaveMessage, const LocationId &locationId)
{
    return (m_pWaveObjectManager->sendOneWay (pWaveMessage, locationId));
}

WaveMessageStatus WaveWorker::sendOneWayToFront (WaveMessage *pWaveMessage, const LocationId &locationId)
{
    return (m_pWaveObjectManager->sendOneWayToFront (pWaveMessage, locationId));
}

WaveMessageStatus WaveWorker::sendSynchronously (WaveMessage *pWaveMessage, const LocationId &locationId)
{
    return (m_pWaveObjectManager->sendSynchronously (pWaveMessage, locationId));
}

void WaveWorker::sendToWaveCluster (WaveSendToClusterContext *pWaveSendToClusterContext)
{
    m_pWaveObjectManager->sendToWaveCluster (pWaveSendToClusterContext);
}

void WaveWorker::sendOneWayToWaveCluster (WaveSendToClusterContext *pWaveSendToClusterContext)
{
    m_pWaveObjectManager->sendOneWayToWaveCluster (pWaveSendToClusterContext);
}

bool WaveWorker::isBeingSurrogated ()
{
    return (m_pWaveObjectManager->isBeingSurrogated ());
}

WaveMessageStatus WaveWorker::recall (WaveMessage *pWaveMessage)
{
    return (m_pWaveObjectManager->recall (pWaveMessage));
}

WaveMessageStatus WaveWorker::reply (WaveMessage *pWaveMessage)
{
    return (m_pWaveObjectManager->reply (pWaveMessage));
}

WaveMessageStatus WaveWorker::reply (const WaveEvent *&pWaveEvent)
{
    return (m_pWaveObjectManager->reply (pWaveEvent));
}

WaveMessageStatus WaveWorker::broadcast (WaveEvent *pWaveEvent)
{
    return (m_pWaveObjectManager->broadcast (pWaveEvent));
}

void WaveWorker::trace (TraceLevel traceLevel, const string &stringToTrace)
{
    m_pWaveObjectManager->trace (traceLevel, stringToTrace);
}

void WaveWorker::tracePrintf (TraceLevel traceLevel, const bool &addNewLine, const bool &suppressPrefix, const char * const pFormat, ...)
{
    va_list variableArguments;

    va_start (variableArguments, pFormat);

    m_pWaveObjectManager->tracePrintf (traceLevel, addNewLine, suppressPrefix, pFormat, variableArguments);

    va_end (variableArguments);
}

void WaveWorker::tracePrintf (TraceLevel traceLevel, const char * const pFormat, ...)
{
    va_list variableArguments;

    va_start (variableArguments, pFormat);

    m_pWaveObjectManager->tracePrintf (traceLevel, pFormat, variableArguments);

    va_end (variableArguments);
}

void WaveWorker::waveAssert (bool isAssertNotRequired, const char *pFileName, UI32 lineNumber)
{
    m_pWaveObjectManager->waveAssert (isAssertNotRequired, pFileName, lineNumber);
}

void WaveWorker::addOperationMap (UI32 operationCode, WaveMessageHandler pWaveMessageHandler, WaveElement *pWaveElement)
{
    if (NULL == pWaveElement)
    {
        pWaveElement = this;
    }

    m_pWaveObjectManager->addOperationMap (operationCode, pWaveMessageHandler, pWaveElement);
}

void WaveWorker::addLightPulseType (const string &lightPulseName, WaveElement *pWaveElement)
{
    if (NULL == pWaveElement)
    {
        pWaveElement = this;
    }

    m_pWaveObjectManager->addLightPulseType (lightPulseName, pWaveElement);
}

void WaveWorker::removeOperationMap (const UI32 &operationCode)
{
    m_pWaveObjectManager->removeOperationMap (operationCode);
}

void WaveWorker::addServiceIndependentOperationMap (UI32 operationCode, WaveServiceIndependentMessageHandler pWaveServiceIndependentMessageHandler)
{
    m_pWaveObjectManager->addServiceIndependentOperationMap (operationCode, pWaveServiceIndependentMessageHandler);
}

void WaveWorker::addServiceIndependentOperationMap (UI32 operationCode, ManagementInterfaceServiceIndependentMessageHandler pManagementInterfaceServiceIndependentMessageHandler)
{
    m_pWaveObjectManager->addServiceIndependentOperationMap (operationCode, pManagementInterfaceServiceIndependentMessageHandler);
}

void WaveWorker::removeServiceIndependentOperationMap (UI32 operationCode)
{
    m_pWaveObjectManager->removeServiceIndependentOperationMap (operationCode);
}

ResourceId WaveWorker::startTimer (TimerHandle &timerHandle, timeval &startInterval, timeval &periodicInterval, WaveTimerExpirationHandler pWaveTimerExpirationCallback, void *pWaveTimerExpirationContext, WaveElement *pWaveTimerSender)
{
    return (m_pWaveObjectManager->startTimer (timerHandle, startInterval, periodicInterval, pWaveTimerExpirationCallback, pWaveTimerExpirationContext, pWaveTimerSender != NULL ? pWaveTimerSender : this));
}

ResourceId WaveWorker::startTimer (TimerHandle &timerHandle, UI32 timeInMilliSeconds, WaveTimerExpirationHandler pWaveTimerExpirationCallback, void *pWaveTimerExpirationContext, WaveElement *pWaveTimerSender)
{
    return (m_pWaveObjectManager->startTimer (timerHandle, timeInMilliSeconds, pWaveTimerExpirationCallback, pWaveTimerExpirationContext, pWaveTimerSender != NULL ? pWaveTimerSender : this));
}

ResourceId WaveWorker::deleteTimer (TimerHandle timerHandle)
{
    return (m_pWaveObjectManager->deleteTimer (timerHandle));
}

void WaveWorker::holdMessages ()
{
    m_pWaveObjectManager->holdMessages ();
}

void WaveWorker::holdHighPriorityMessages ()
{
    m_pWaveObjectManager->holdHighPriorityMessages ();
}

void WaveWorker::holdEvents ()
{
    m_pWaveObjectManager->holdEvents ();
}

void WaveWorker::holdAll ()
{
    m_pWaveObjectManager->holdAll ();
}

void WaveWorker::unholdMessages ()
{
    m_pWaveObjectManager->unholdMessages ();
}

void WaveWorker::unholdHighPriorityMessages ()
{
    m_pWaveObjectManager->unholdHighPriorityMessages ();
}

void WaveWorker::unholdEvents ()
{
    m_pWaveObjectManager->unholdEvents ();
}

void WaveWorker::unholdAll ()
{
    m_pWaveObjectManager->unholdAll ();
}

UI32 WaveWorker::getNumberOfPendingTimerExpirationMessages ()
{
    return (m_pWaveObjectManager->getNumberOfPendingTimerExpirationMessages ());
}

UI32 WaveWorker::getNumberOfPendingNormalMessages ()
{
    return (m_pWaveObjectManager->getNumberOfPendingNormalMessages ());
}

UI32 WaveWorker::getNumberOfPendingHighPriorityMessages ()
{
    return (m_pWaveObjectManager->getNumberOfPendingHighPriorityMessages ());
}
/*
void WaveWorker::failover (FrameworkObjectManagerFailoverReason failoverReason, vector<LocationId> failedLocationIds, WaveAsynchronousContext *pWaveAsynchronousContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveWorker::failover : Entering ...");

    pWaveAsynchronousContext->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContext->callback ();
}
*/
void WaveWorker::failover (FailoverAsynchronousContext *pFailoverAsynchronousContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveWorker::failover : Entering ...");

    pFailoverAsynchronousContext->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pFailoverAsynchronousContext->callback ();
}

void WaveWorker::getDebugInformation (WaveAsynchronousContextForDebugInformation *pWaveAsynchronousContextForDebugInformation)
{
    trace (TRACE_LEVEL_DEVEL, "WaveWorker::getDebugInformation : Entering ...");

    pWaveAsynchronousContextForDebugInformation->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForDebugInformation->callback ();
}

void WaveWorker::resetDebugInformation (WaveAsynchronousContextForDebugInformation *pWaveAsynchronousContextForDebugInformation)
{
    trace (TRACE_LEVEL_DEVEL, "WaveWorker::resetDebugInformation : Entering ...");

    pWaveAsynchronousContextForDebugInformation->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForDebugInformation->callback ();
}

void WaveWorker::startTransaction ()
{
    m_pWaveObjectManager->startTransaction ();
}

bool WaveWorker::isTransactionInProgress ()
{
    return (m_pWaveObjectManager->isTransactionInProgress ());
}

ResourceId WaveWorker::commitTransaction (WaveObjectManagerCommitTransactionContext *pWaveObjectManagerCommitTransactionContext)
{
    return (m_pWaveObjectManager->commitTransaction (pWaveObjectManagerCommitTransactionContext));
}

void WaveWorker::rollbackTransaction ()
{
    m_pWaveObjectManager->rollbackTransaction ();
}

void WaveWorker::addManagedClass (const string &managedClassName)
{
    m_pWaveObjectManager->addManagedClass (managedClassName, this);
}

vector<WaveManagedObject *> *WaveWorker::querySynchronouslyLocalManagedObjectsForLocationId (const LocationId &locationId, const string &className)
{
    return (m_pWaveObjectManager->querySynchronouslyLocalManagedObjectsForLocationId (locationId, className));
}

vector<WaveManagedObject *> *WaveWorker::querySynchronouslyLocalManagedObjectsForLocationId (const LocationId &locationId, const string &className, const vector<string> &selectFields)
{
    return (m_pWaveObjectManager->querySynchronouslyLocalManagedObjectsForLocationId (locationId, className, selectFields));
}

vector<WaveManagedObject *> *WaveWorker::querySynchronouslyLocalManagedObjectsForLocationId (const LocationId &locationId, WaveManagedObjectSynchronousQueryContext *pWaveManagedObjectSynchronousQueryContext)
{
    return (m_pWaveObjectManager->querySynchronouslyLocalManagedObjectsForLocationId (locationId, pWaveManagedObjectSynchronousQueryContext));
}

void WaveWorker::query (WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext)
{
    m_pWaveObjectManager->query (pWaveManagedObjectQueryContext);
}

vector<WaveManagedObject *> *WaveWorker::querySynchronously (WaveManagedObjectSynchronousQueryContext *pWaveManagedObjectSynchronousQueryContext)
{
    return (m_pWaveObjectManager->querySynchronously (pWaveManagedObjectSynchronousQueryContext));
}

WaveManagedObject* WaveWorker::createInMemoryManagedObject (const  string &className)
{
    return (m_pWaveObjectManager->createInMemoryManagedObject (className));
}

ResourceId WaveWorker::querySynchronouslyForCount (WaveManagedObjectSynchronousQueryContext *pWaveManagedObjectSynchronousQueryContext, UI32 &count)
{
    return (m_pWaveObjectManager->querySynchronouslyForCount (pWaveManagedObjectSynchronousQueryContext, count));
}

ResourceId WaveWorker::querySynchronouslyForCount (const string &managedClassName, UI32 &count, const string &schema)
{
    return (m_pWaveObjectManager->querySynchronouslyForCount (managedClassName, count, schema));
}

ResourceId WaveWorker::querySynchronouslyForCount (const string &managedClassName, const string &fieldName, const string &range, UI32 &count, const string &schema)
{
    return (m_pWaveObjectManager->querySynchronouslyForCount (managedClassName, fieldName, range, count, schema));
}

ResourceId WaveWorker::querySynchronouslyForCountForManagedObjectByName (const string &managedClassName, const string &nameValue, UI32 &count, const string &schema)
{
    return (m_pWaveObjectManager->querySynchronouslyForCountForManagedObjectByName (managedClassName, nameValue, count, schema));
}

vector<WaveManagedObject *> *WaveWorker::querySynchronously (const string &managedClassName, const string &schema)
{
    return (m_pWaveObjectManager->querySynchronously (managedClassName, schema));
}

vector<WaveManagedObject *> *WaveWorker::querySynchronously (const string &managedClassName, vector<ObjectId> &objectIds, const string &schema)
{
    return (m_pWaveObjectManager->querySynchronously (managedClassName, objectIds, schema));
}

vector<WaveManagedObject *> *WaveWorker::querySynchronouslyByName (const string &managedClassName, const string &managedObjectName, const string &schema)
{
    return (m_pWaveObjectManager->querySynchronouslyByName (managedClassName, managedObjectName, schema));
}

void WaveWorker::addWaveConfigEntry (Attribute *attribute)
{
    m_pWaveObjectManager->addWaveConfigEntry (attribute);
}

void WaveWorker::updateWaveConfigEntry (Attribute *attribute)
{
    m_pWaveObjectManager->updateWaveConfigEntry (attribute);
}

void WaveWorker::getWaveConfigEntry (string &configName, Attribute *attribute, bool &configFound)
{
    m_pWaveObjectManager->getWaveConfigEntry (configName, attribute, configFound);
}

void WaveWorker::updateWaveManagedObject (WaveManagedObject *pWaveManagedObject)
{
    m_pWaveObjectManager->updateWaveManagedObject (pWaveManagedObject);
}

void WaveWorker::updateMultipleWaveManagedObjects (WaveManagedObjectSynchronousQueryContextForUpdate *pWaveManagedObjectSynchronousQueryContextForUpdate)
{
    m_pWaveObjectManager->updateMultipleWaveManagedObjects (pWaveManagedObjectSynchronousQueryContextForUpdate);
}

void WaveWorker::deleteWaveManagedObject (const ObjectId &objectId)
{
    m_pWaveObjectManager->deleteWaveManagedObject (objectId);
}

void WaveWorker::deleteWaveManagedObject (WaveManagedObjectSynchronousQueryContextForDeletion *pWaveManagedObjectSynchronousQueryContextForDeletion)
{
    m_pWaveObjectManager->deleteWaveManagedObject (pWaveManagedObjectSynchronousQueryContextForDeletion);
}

void WaveWorker::deleteMultipleWaveManagedObjects (WaveManagedObjectSynchronousQueryContextForDeletion *pWaveManagedObjectSynchronousQueryContextForDeletion)
{
    m_pWaveObjectManager->deleteMultipleWaveManagedObjects (pWaveManagedObjectSynchronousQueryContextForDeletion);
}

void WaveWorker::deleteManagedObjectCompositions (WaveManagedObjectSynchronousQueryContextForDeletion *pWaveManagedObjectSynchronousQueryContextForDeletion, const set<string> relationsSet)
{
    m_pWaveObjectManager->deleteManagedObjectCompositions (pWaveManagedObjectSynchronousQueryContextForDeletion, relationsSet);
}

void WaveWorker::deleteManagedObjectCompositions (const ObjectId &objectId, const set<string> relationsSet)
{
    m_pWaveObjectManager->deleteManagedObjectCompositions (objectId, relationsSet);
}

void WaveWorker::deletePartialManagedObjectCompositions (const string &parentClassName, const string &compositionName,
        WaveManagedObjectSynchronousQueryContextForDeletion *pQueryContextForDeletionOnChildMO)
{
    m_pWaveObjectManager->deletePartialManagedObjectCompositions (parentClassName, compositionName, pQueryContextForDeletionOnChildMO);
}

bool WaveWorker::isManagedClassSupported (const string &managedClass)
{
    return (m_pWaveObjectManager->isManagedClassSupported (managedClass));
}

void WaveWorker::addRelationship (const string &parentClassName, const string &childClassName, const string &relationshipName, const ObjectId &parentObjectId, const ObjectId &childObjectId)
{
    m_pWaveObjectManager->addRelationship (parentClassName, childClassName, relationshipName, parentObjectId, childObjectId);
}

void WaveWorker::deleteRelationship (const string &parentClassName, const string &childClassName, const string &relationshipName, const ObjectId &parentObjectId, const ObjectId &childObjectId)
{
    m_pWaveObjectManager->deleteRelationship (parentClassName, childClassName, relationshipName, parentObjectId, childObjectId);
}

void WaveWorker::addToComposition (const string &parentClassName, const string &childCalssName, const string &compositionName, const ObjectId &parentObjectId, const ObjectId &childObjectId)
{
    m_pWaveObjectManager->addToComposition (parentClassName, childCalssName, compositionName, parentObjectId, childObjectId);
}

void WaveWorker::deleteFromComposition (const string &parentClassName, const string &childCalssName, const string &compositionName, const ObjectId &parentObjectId, const ObjectId &childObjectId)
{
    m_pWaveObjectManager->deleteFromComposition (parentClassName, childCalssName, compositionName, parentObjectId, childObjectId);
}

void WaveWorker::addToAssociation (const string &parentClassName, const string &childCalssName, const string &associationName, const ObjectId &parentObjectId, const ObjectId &childObjectId)
{
    m_pWaveObjectManager->addToAssociation (parentClassName, childCalssName, associationName, parentObjectId, childObjectId);
}

void WaveWorker::deleteFromAssociation (const string &parentClassName, const string &childCalssName, const string &associationName, const ObjectId &parentObjectId, const ObjectId &childObjectId)
{
    m_pWaveObjectManager->deleteFromAssociation (parentClassName, childCalssName, associationName, parentObjectId, childObjectId);
}

WaveManagedObject *WaveWorker::queryManagedObject (const ObjectId &managedObjectId, const string &schema)
{
    return (m_pWaveObjectManager->queryManagedObject (managedObjectId, schema));
}

ResourceId WaveWorker::querySynchronouslyForObjectIdForManagedObjectByName (const string &managedClassName, const string &nameValue, ObjectId &objectId, const string &schema)
{
    return (m_pWaveObjectManager->querySynchronouslyForObjectIdForManagedObjectByName (managedClassName, nameValue, objectId, schema));
}

vector<WaveManagedObject *> *WaveWorker::queryManagedObjectAssociatedWithSlot (const string &managedClassName, UI32 slotNumber, LocationId locationId, const string &schema)
{
    return (m_pWaveObjectManager->queryManagedObjectAssociatedWithSlot (managedClassName, slotNumber, locationId, schema));
}

TraceClientId WaveWorker::getTraceClientId ()
{
    return (m_pWaveObjectManager->getTraceClientId ());
}

void WaveWorker::addEventType (const UI32 &eventOperationCode)
{
    m_pWaveObjectManager->addEventType (eventOperationCode);
}

void WaveWorker::setCpuAffinity (const vector<UI32> &cpuAffinityVector)
{
    m_pWaveObjectManager->setCpuAffinity (cpuAffinityVector);
}

WaveServiceId WaveWorker::getServiceId ()
{
    return (m_pWaveObjectManager->getServiceId ());
}

void WaveWorker::listenForEvent (WaveServiceId waveServiceCode, UI32 sourceOperationCode, WaveEventHandler pWaveEventHandler, WaveElement *pWaveElement, const LocationId &sourceLocationId)
{
    m_pWaveObjectManager->listenForEvent (waveServiceCode, sourceOperationCode, pWaveEventHandler, pWaveElement != NULL ? pWaveElement : this, sourceLocationId);
}

void WaveWorker::listenForLightPulse (const string &lightPulseName, WaveLightPulseHandler pWaveLightPulseHandler, WaveElement *pWaveElement)
{
    m_pWaveObjectManager->listenForLightPulse (lightPulseName, pWaveLightPulseHandler, pWaveElement != NULL ? pWaveElement : this);
}

ResourceId WaveWorker::sendSynchronouslyToWaveClient (const string &waveClientName, ManagementInterfaceMessage *pManagementInterfaceMessage, const SI32 &Instance)
{
    return (m_pWaveObjectManager->sendSynchronouslyToWaveClient (waveClientName, pManagementInterfaceMessage, Instance));
}

WaveMessageStatus WaveWorker::sendToWaveServer (const UI32 &waveServerId, ManagementInterfaceMessage *pManagementInterfaceMessage, WaveMessageResponseHandler messageCallback, WaveElement *pWaveMessageSender, void *pInputContext, UI32 timeOutInMilliSeconds)
{
    return (m_pWaveObjectManager->sendToWaveServer (waveServerId, pManagementInterfaceMessage, messageCallback, pWaveMessageSender, pInputContext, timeOutInMilliSeconds));
}

ResourceId WaveWorker::sendToWaveClient (const string &waveClientName, ManagementInterfaceMessage *pManagementInterfaceMessage, WaveMessageResponseHandler pWaveMessageCallback, void *pWaveMessageContext, UI32 timeOutInMilliSeconds, const SI32 &Instance)
{
    return (m_pWaveObjectManager->sendToWaveClient (waveClientName, pManagementInterfaceMessage, pWaveMessageCallback, pWaveMessageContext, timeOutInMilliSeconds, Instance));
}

void WaveWorker::sendToWaveClients (WaveSendToClientsContext *pWaveSendToClientsContext)
{
    m_pWaveObjectManager->sendToWaveClients (pWaveSendToClientsContext);
}

ResourceId WaveWorker::sendOneWayToAllWaveClients(ManagementInterfaceMessage *pManagementInterfaceMessage)
{
    return( m_pWaveObjectManager->sendOneWayToAllWaveClients(pManagementInterfaceMessage) );
}

WaveManagedObject *WaveWorker::createManagedObjectInstance (const string &managedClassName)
{
    trace (TRACE_LEVEL_ERROR, "WaveWorker::createManagedObjectInstance : NOT IMPLEMENTED.  RETURNS NULL BY DEFAULT.");
    return (NULL);
}

void WaveWorker::addManagedClass (const string &managedClassName, WaveElement *pOwnerForInstantiation)
{
    if (NULL == pOwnerForInstantiation)
    {
        pOwnerForInstantiation = this;
    }

    m_pWaveObjectManager->addManagedClass (managedClassName, pOwnerForInstantiation);
}

WaveMessage *WaveWorker::createMessageInstance (const UI32 &operationCode)
{
    trace (TRACE_LEVEL_ERROR, "WaveWorker::createMessageInstance : NOT IMPLEMENTED.  RETURNS NULL BY DEFAULT.");
    return (NULL);
}

void WaveWorker::printfToWaveClientSession (const WaveClientSessionContext &waveClientSessionContext, const char * const pFormat, ...)
{
    va_list variableArguments;

    va_start (variableArguments, pFormat);

    m_pWaveObjectManager->printfToWaveClientSession (waveClientSessionContext, pFormat, variableArguments);

    va_end (variableArguments);
}

void WaveWorker::printfToAllWaveClientSessions (const WaveClientSessionContext &waveClientSessionContext, const char * const pFormat, ...)
{
    va_list variableArguments;

    va_start (variableArguments, pFormat);

    m_pWaveObjectManager->printfToAllWaveClientSessions (waveClientSessionContext, pFormat, variableArguments);

    va_end (variableArguments);
}

ResourceId WaveWorker::addLog (ResourceId logType, ResourceId logDescriptionType, const vector<Attribute *> &logDescriptionArguments)
{
    return (m_pWaveObjectManager->addLog(logType, logDescriptionType, logDescriptionArguments));
}

void WaveWorker::registerLock (const string &serviceString)
{
    m_pWaveObjectManager->registerLock (serviceString);
}

ResourceId WaveWorker::updateHardwareSynchronizationState (ResourceId hardwareSynchronizationState, const vector<LocationId> &locationIds)
{
    return (m_pWaveObjectManager->updateHardwareSynchronizationState (hardwareSynchronizationState, locationIds));
}

ResourceId WaveWorker::updateHardwareSynchronizationState (ResourceId hardwareSynchronizationState, LocationId locationId)
{
    return (m_pWaveObjectManager->updateHardwareSynchronizationState (hardwareSynchronizationState, locationId));
}

void WaveWorker::dbBasicSanityCheck (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    trace (TRACE_LEVEL_DEVEL, "WaveWorker::dbBasicSanityCheck : Entering ...");

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void WaveWorker::dbInconsistencyCheck (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    trace (TRACE_LEVEL_DEVEL, "WaveWorker::dbInconsistencyCheck : Entering ...");

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void WaveWorker::zeroize (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases)
{
    trace (TRACE_LEVEL_DEVEL, "WaveWorker::zeroize : Entering ...");

    pWaveAsynchronousContextForShutDownPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForShutDownPhases->callback ();
}

WaveObjectManagerStatisticsTracker *WaveWorker::getPWaveObjectManagerStatisticsTracker () const
{
    return (m_pWaveObjectManager->getPWaveObjectManagerStatisticsTracker ());
}

void WaveWorker::deleteAllManagedObjectInstances (const string &className)
{
    m_pWaveObjectManager->deleteAllManagedObjectInstances (className);
}

void WaveWorker::updateTimeConsumedInThisThread (const UI32 &operationCode, const UI32 &sequencerStepIndex, const UI32 &numberOfSeconds, const SI32 &numberOfNanoSeconds)
{
    m_pWaveObjectManager->updateTimeConsumedInThisThread (operationCode, sequencerStepIndex, numberOfSeconds, numberOfNanoSeconds);
}

void WaveWorker::updateRealTimeConsumedInThisThread (const UI32 &operationCode, const UI32 &sequencerStepIndex, const UI32 &numberOfSeconds, const SI32 &numberOfNanoSeconds)
{
    m_pWaveObjectManager->updateRealTimeConsumedInThisThread (operationCode, sequencerStepIndex, numberOfSeconds, numberOfNanoSeconds);
}

void WaveWorker::sendMulticast (WaveSendMulticastContext *pWaveSendMulticastContext)
{
    m_pWaveObjectManager->sendMulticast (pWaveSendMulticastContext);
}

void WaveWorker::postponeMessageHandling (WaveMessage *pWaveMessage)
{
    m_pWaveObjectManager->postponeMessageHandling (pWaveMessage);
}

void WaveWorker::resumeAllPostponedMessages ()
{
    m_pWaveObjectManager->resumeAllPostponedMessages ();
}

ResourceId WaveWorker::blockCli (const CliBlockContext &cliBlockContext, const bool &clusterWide)
{
    ResourceId status = m_pWaveObjectManager->blockCli (cliBlockContext, clusterWide);
    return status;
}

ResourceId WaveWorker::unblockCli (const CliBlockContext &cliBlockContext, const bool &clusterWide)
{
    ResourceId status = m_pWaveObjectManager->unblockCli (cliBlockContext, clusterWide);
    return status;
}

WaveMessageBrokerStatus WaveWorker::connectToMessageBroker (const string &brokerName, const string &brokerIpAddress, const SI32 &brokerPort)
{
    return (m_pWaveObjectManager->connectToMessageBroker (brokerName, brokerIpAddress, brokerPort));
}

WaveMessageBrokerStatus WaveWorker::subscribeToMessageBroker (const string &brokerName, const vector<string> &topicNames, const vector<WaveBrokerPublishMessageHandler> publishMessageHandlers, WaveElement *pSubscriber)
{
    return (m_pWaveObjectManager->subscribeToMessageBroker (brokerName, topicNames, publishMessageHandlers, pSubscriber != NULL ? pSubscriber : this));
}

WaveMessageBrokerStatus WaveWorker::subscribeToMessageBroker (const string &brokerName, const vector<string> &topicNames, WaveBrokerPublishMessageHandler publishMessageHandler, WaveElement *pSubscriber)
{
    return (m_pWaveObjectManager->subscribeToMessageBroker (brokerName, topicNames, publishMessageHandler, pSubscriber != NULL ? pSubscriber : this));
}

WaveMessageBrokerStatus WaveWorker::subscribeToMessageBroker (const string &brokerName, const string &topicName, WaveBrokerPublishMessageHandler publishMessageHandler, WaveElement *pSubscriber)
{
    return (m_pWaveObjectManager->subscribeToMessageBroker (brokerName, brokerName, publishMessageHandler, pSubscriber != NULL ? pSubscriber : this));
}

WaveMessageBrokerStatus WaveWorker::unsubscribeToMessageBroker (const string &brokerName, const vector<string> &topicNames, WaveElement *pSubscriber)
{
    return (m_pWaveObjectManager->unsubscribeToMessageBroker (brokerName, topicNames, pSubscriber != NULL ? pSubscriber : this));
}

WaveMessageBrokerStatus WaveWorker::unsubscribeToMessageBroker (const string &brokerName, const string &topicName, WaveElement *pSubscriber)
{
    return (m_pWaveObjectManager->unsubscribeToMessageBroker (brokerName, topicName, pSubscriber != NULL ? pSubscriber : this));
}

WaveMessageBrokerStatus WaveWorker::publishToMessageBroker (const string &brokerName, WaveBrokerPublishMessage *pWaveBrokerPublishMessage, WaveElement *pSubscriber)
{
    return (m_pWaveObjectManager->publishToMessageBroker (brokerName, pWaveBrokerPublishMessage));
}

void WaveWorker::deliverWaveBrokerPublishedEvent (const string &brokerName, const string &topicName, WaveBrokerPublishMessage *pWaveBrokerPublishMessage)
{
    m_pWaveObjectManager->deliverWaveBrokerPublishedEvent (brokerName, topicName, pWaveBrokerPublishMessage);
}

WaveMessageStatus WaveWorker::broadcastLightPulse (LightPulse *pLightPulse)
{
    return (m_pWaveObjectManager->broadcastLightPulse (pLightPulse));
}

void WaveWorker::deliverWaveLightPulse (const LightPulse *&pLightPulse)
{
    return (m_pWaveObjectManager->deliverWaveLightPulse (pLightPulse));
}

}

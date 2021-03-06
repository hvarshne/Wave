/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveSendToClusterContext.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"

namespace WaveNs
{

WaveSendToClusterContext::WaveSendToClusterContext (WaveElement *pCaller, WaveAsynchronousCallback pCallback, void *pCallerContext)
    : WaveAsynchronousContext (pCaller, pCallback, pCallerContext),
      m_pWaveMessageForPhase1                  (NULL),
      m_pWaveMessageForPhase2                  (NULL),
      m_timeoutForPhase1                        (0),
      m_timeoutForPhase2                        (0),
      m_numberOfFailuresForPhase1               (0),
      m_numberOfDisconnectedNodesForPhase1      (0),
      m_numberOfFailuresForPhase2               (0),
      m_treatFailureOnFailingOverAsSuccessFlag  (false),
      m_returnSuccessForPartialSuccessFlag      (false),
      m_isPartialSuccessCaseFlag                (false),
      m_isLocationsForPhase1SetByUserFlag       (false),
      m_isSendOneWayToWaveCluster               (false)
{
    /* Defect 359422: show vcs hang issue fix. We will send to nodes that are part of the cluster and not to node that are
     * joining the cluster. More details in the tt. */
    FrameworkToolKit::getFullyConnectedLocations (m_locationsToSendToForPhase1);
    m_locationsToSendToForPhase1.push_back (FrameworkToolKit::getThisLocationId ());
}

WaveSendToClusterContext::~WaveSendToClusterContext ()
{
    map<LocationId, WaveMessage *>::iterator       element    = m_resultingMessageForPhase1.begin ();
    map<LocationId, WaveMessage *>::const_iterator endElement = m_resultingMessageForPhase1.end ();

    while (endElement != element)
    {
        delete (element->second);
        element++;
    }

    map<LocationId, WaveMessage *>::iterator       element2    = m_resultingMessageForPhase2.begin ();
    map<LocationId, WaveMessage *>::const_iterator endElement2 = m_resultingMessageForPhase2.end ();

    while (endElement2 != element2)
    {
        delete (element2->second);
        element2++;
    }
}

WaveMessage *WaveSendToClusterContext::getPWaveMessageForPhase1 () const
{
    return (m_pWaveMessageForPhase1);
}

void WaveSendToClusterContext::setPWaveMessageForPhase1 (WaveMessage *pWaveMessageForPhase1)
{
    m_pWaveMessageForPhase1 = pWaveMessageForPhase1;
}

WaveMessage *WaveSendToClusterContext::getPWaveMessageForPhase2 () const
{
    return (m_pWaveMessageForPhase2);
}

void WaveSendToClusterContext::setPWaveMessageForPhase2 (WaveMessage *pWaveMessageForPhase2)
{
    if (pWaveMessageForPhase2 && m_returnSuccessForPartialSuccessFlag)
    {
        trace (TRACE_LEVEL_ERROR, "WaveSendToClusterContext::setPWaveMessageForPhase2: PartialSuccess flag and rollback message can't be set at a time.");  
        trace (TRACE_LEVEL_ERROR, "WaveSendToClusterContext::setPWaveMessageForPhase2: Be sure about the expected behaviour - If rollback message to be sent on failure or should it be considered as PartialSuccess.");  
        waveAssert (false, __FILE__, __LINE__);
    }

    m_pWaveMessageForPhase2 = pWaveMessageForPhase2;
}

UI32 WaveSendToClusterContext::getTimeoutForPhase1 () const
{
    return (m_timeoutForPhase1);
}

void WaveSendToClusterContext::setTimeoutForPhase1 (const UI32 &timeoutForPhase1)
{
    m_timeoutForPhase1 = timeoutForPhase1;
}

UI32 WaveSendToClusterContext::getTimeoutForPhase2 () const
{
    return (m_timeoutForPhase2);
}

void WaveSendToClusterContext::setTimeoutForPhase2 (const UI32 &timeoutForPhase2)
{
    m_timeoutForPhase2 = timeoutForPhase2;
}

vector<LocationId> WaveSendToClusterContext::getLocationsToSendToForPhase1 () const
{
    return (m_locationsToSendToForPhase1);
}

void WaveSendToClusterContext::setLocationsToSendToForPhase1 (const vector<UI32> &locationToSendToForPhase1)
{
    m_locationsToSendToForPhase1 = locationToSendToForPhase1;
    m_isLocationsForPhase1SetByUserFlag = true;
}

WaveMessageStatus WaveSendToClusterContext::getSendStatusForPhase1 (const LocationId &locationId)
{
    map<LocationId, WaveMessageStatus>::const_iterator element    = m_sendStatusForPhase1.find (locationId);
    map<LocationId, WaveMessageStatus>::const_iterator endElement = m_sendStatusForPhase1.end ();

    waveAssert (endElement != element, __FILE__, __LINE__);

    return (m_sendStatusForPhase1[locationId]);
}

void WaveSendToClusterContext::setSendStatusForPhase1 (const LocationId &locationId, const WaveMessageStatus &sendStatusForPhase1)
{
    map<LocationId, WaveMessageStatus>::const_iterator element    = m_sendStatusForPhase1.find (locationId);
    map<LocationId, WaveMessageStatus>::const_iterator endElement = m_sendStatusForPhase1.end ();

    waveAssert (endElement == element, __FILE__, __LINE__);

    m_sendStatusForPhase1[locationId] = sendStatusForPhase1;
}

FrameworkStatus WaveSendToClusterContext::getFrameworkStatusForPhase1 (const LocationId &locationId)
{
    map<LocationId, FrameworkStatus>::const_iterator element    = m_frameworkStatusForPhase1.find (locationId);
    map<LocationId, FrameworkStatus>::const_iterator endElement = m_frameworkStatusForPhase1.end ();

    waveAssert (endElement != element, __FILE__, __LINE__);

    return (m_frameworkStatusForPhase1[locationId]);
}

void WaveSendToClusterContext::setFrameworkStatusForPhase1 (const LocationId &locationId, const FrameworkStatus frameworkStatusForPhase1)
{
    map<LocationId, FrameworkStatus>::const_iterator element    = m_frameworkStatusForPhase1.find (locationId);
    map<LocationId, FrameworkStatus>::const_iterator endElement = m_frameworkStatusForPhase1.end ();

    waveAssert (endElement == element, __FILE__, __LINE__);

    m_frameworkStatusForPhase1[locationId] = frameworkStatusForPhase1;
}

ResourceId WaveSendToClusterContext::getCompletionStatusForPhase1 (const LocationId &locationId)
{
    map<LocationId, ResourceId>::const_iterator element    = m_completionStatusForPhase1.find (locationId);
    map<LocationId, ResourceId>::const_iterator endElement = m_completionStatusForPhase1.end ();

    waveAssert (endElement != element, __FILE__, __LINE__);

    return (m_completionStatusForPhase1[locationId]);
}

void WaveSendToClusterContext::setCompletionStatusForPhase1 (const LocationId &locationId, const ResourceId &completionStatusForPhase1)
{
    map<LocationId, ResourceId>::const_iterator element    = m_completionStatusForPhase1.find (locationId);
    map<LocationId, ResourceId>::const_iterator endElement = m_completionStatusForPhase1.end ();

    waveAssert (endElement == element, __FILE__, __LINE__);

    m_completionStatusForPhase1[locationId] = completionStatusForPhase1;
}

WaveMessage *WaveSendToClusterContext::getResultingMessageForPhase1 (const LocationId &locationId)
{
    map<LocationId, WaveMessage *>::const_iterator element    = m_resultingMessageForPhase1.find (locationId);
    map<LocationId, WaveMessage *>::const_iterator endElement = m_resultingMessageForPhase1.end ();

    waveAssert (endElement != element, __FILE__, __LINE__);

    return (m_resultingMessageForPhase1[locationId]);
}

void WaveSendToClusterContext::setResultingMessageForPhase1 (const LocationId &locationId, WaveMessage *pWaveMessage)
{
    map<LocationId, WaveMessage *>::const_iterator element    = m_resultingMessageForPhase1.find (locationId);
    map<LocationId, WaveMessage *>::const_iterator endElement = m_resultingMessageForPhase1.end ();

    waveAssert (endElement == element, __FILE__, __LINE__);

    m_resultingMessageForPhase1[locationId] = pWaveMessage;
}

WaveMessage *WaveSendToClusterContext::transferResultingMessageForPhase1 (const LocationId &locationId)
{
    map<LocationId, WaveMessage *>::const_iterator  element       = m_resultingMessageForPhase1.find (locationId);
    map<LocationId, WaveMessage *>::const_iterator  endElement    = m_resultingMessageForPhase1.end ();
    WaveMessage                                    *pWaveMessage = NULL;

    waveAssert (endElement != element, __FILE__, __LINE__);

    pWaveMessage = m_resultingMessageForPhase1[locationId];

   m_resultingMessageForPhase1.erase (locationId);

    return (pWaveMessage);
}

UI32 WaveSendToClusterContext::getNumberOfFailuresForPhase1 () const
{
    return (m_numberOfFailuresForPhase1);
}

void WaveSendToClusterContext::setNumberOfFailuresForPhase1 (const UI32 &numberOfFailuresForPhase1)
{
    m_numberOfFailuresForPhase1 = numberOfFailuresForPhase1;
}

UI32 WaveSendToClusterContext::getNumberOfDisconnectedNodesForPhase1 () const
{
    return (m_numberOfDisconnectedNodesForPhase1);
}

void WaveSendToClusterContext::setNumberOfDisconnectedNodesForPhase1 (const UI32 &numberOfDisconnectsForPhase1)
{
    m_numberOfDisconnectedNodesForPhase1 = numberOfDisconnectsForPhase1;
}

vector<LocationId> WaveSendToClusterContext::getLocationsToSendToForPhase2 () const
{
    return (m_locationsToSendToForPhase2);
}

void WaveSendToClusterContext::setLocationsToSendToForPhase2 (const vector<UI32> &locationToSendToForPhase2)
{
    m_locationsToSendToForPhase2 = locationToSendToForPhase2;
}

WaveMessageStatus WaveSendToClusterContext::getSendStatusForPhase2 (const LocationId &locationId)
{
    map<LocationId, WaveMessageStatus>::const_iterator element    = m_sendStatusForPhase2.find (locationId);
    map<LocationId, WaveMessageStatus>::const_iterator endElement = m_sendStatusForPhase2.end ();

    waveAssert (endElement != element, __FILE__, __LINE__);

    return (m_sendStatusForPhase2[locationId]);
}

void WaveSendToClusterContext::setSendStatusForPhase2 (const LocationId &locationId, const WaveMessageStatus &sendStatusForPhase2)
{
    map<LocationId, WaveMessageStatus>::const_iterator element    = m_sendStatusForPhase2.find (locationId);
    map<LocationId, WaveMessageStatus>::const_iterator endElement = m_sendStatusForPhase2.end ();

    waveAssert (endElement == element, __FILE__, __LINE__);

    m_sendStatusForPhase2[locationId] = sendStatusForPhase2;
}

FrameworkStatus WaveSendToClusterContext::getFrameworkStatusForPhase2 (const LocationId &locationId)
{
    map<LocationId, FrameworkStatus>::const_iterator element    = m_frameworkStatusForPhase2.find (locationId);
    map<LocationId, FrameworkStatus>::const_iterator endElement = m_frameworkStatusForPhase2.end ();

    waveAssert (endElement != element, __FILE__, __LINE__);

    return (m_frameworkStatusForPhase2[locationId]);
}

void WaveSendToClusterContext::setFrameworkStatusForPhase2 (const LocationId &locationId, const FrameworkStatus frameworkStatusForPhase2)
{
    map<LocationId, FrameworkStatus>::const_iterator element    = m_frameworkStatusForPhase2.find (locationId);
    map<LocationId, FrameworkStatus>::const_iterator endElement = m_frameworkStatusForPhase2.end ();

    waveAssert (endElement == element, __FILE__, __LINE__);

    m_frameworkStatusForPhase2[locationId] = frameworkStatusForPhase2;
}

ResourceId WaveSendToClusterContext::getCompletionStatusForPhase2 (const LocationId &locationId)
{
    map<LocationId, ResourceId>::const_iterator element    = m_completionStatusForPhase2.find (locationId);
    map<LocationId, ResourceId>::const_iterator endElement = m_completionStatusForPhase2.end ();

    waveAssert (endElement != element, __FILE__, __LINE__);

    return (m_completionStatusForPhase2[locationId]);
}

void WaveSendToClusterContext::setCompletionStatusForPhase2 (const LocationId &locationId, const ResourceId &completionStatusForPhase2)
{
    map<LocationId, ResourceId>::const_iterator element    = m_completionStatusForPhase2.find (locationId);
    map<LocationId, ResourceId>::const_iterator endElement = m_completionStatusForPhase2.end ();

    waveAssert (endElement == element, __FILE__, __LINE__);

    m_completionStatusForPhase2[locationId] = completionStatusForPhase2;
}

WaveMessage *WaveSendToClusterContext::getResultingMessageForPhase2 (const LocationId &locationId)
{
    map<LocationId, WaveMessage *>::const_iterator element    = m_resultingMessageForPhase2.find (locationId);
    map<LocationId, WaveMessage *>::const_iterator endElement = m_resultingMessageForPhase2.end ();

    waveAssert (endElement != element, __FILE__, __LINE__);

    return (m_resultingMessageForPhase2[locationId]);
}

void WaveSendToClusterContext::setResultingMessageForPhase2 (const LocationId &locationId, WaveMessage *pWaveMessage)
{
    map<LocationId, WaveMessage *>::const_iterator element    = m_resultingMessageForPhase2.find (locationId);
    map<LocationId, WaveMessage *>::const_iterator endElement = m_resultingMessageForPhase2.end ();

    waveAssert (endElement == element, __FILE__, __LINE__);

    m_resultingMessageForPhase2[locationId] = pWaveMessage;
}

WaveMessage *WaveSendToClusterContext::transferResultingMessageForPhase2 (const LocationId &locationId)
{
    map<LocationId, WaveMessage *>::const_iterator  element       = m_resultingMessageForPhase2.find (locationId);
    map<LocationId, WaveMessage *>::const_iterator  endElement    = m_resultingMessageForPhase2.end ();
    WaveMessage                                    *pWaveMessage = NULL;

    waveAssert (endElement != element, __FILE__, __LINE__);

    pWaveMessage = m_resultingMessageForPhase2[locationId];

    m_resultingMessageForPhase2.erase (locationId);

    return (pWaveMessage);
}

UI32 WaveSendToClusterContext::getNumberOfFailuresForPhase2 () const
{
    return (m_numberOfFailuresForPhase2);
}

void WaveSendToClusterContext::setNumberOfFailuresForPhase2 (const UI32 &numberOfFailuresForPhase2)
{
    m_numberOfFailuresForPhase2 = numberOfFailuresForPhase2;
}

bool WaveSendToClusterContext::getTreatFailureOnFailingOverAsSuccessFlag () const
{
    return (m_treatFailureOnFailingOverAsSuccessFlag);
}

void WaveSendToClusterContext::setTreatFailureOnFailingOverAsSuccessFlag (const bool &treatFailureOnFailingOverAsSuccessFlag)
{
    m_treatFailureOnFailingOverAsSuccessFlag = treatFailureOnFailingOverAsSuccessFlag;
}

bool WaveSendToClusterContext::getPartialSuccessFlag () const
{
    return (m_returnSuccessForPartialSuccessFlag);
}

void WaveSendToClusterContext::setPartialSuccessFlag (const bool &partialSuccessFlag)
{
    if (partialSuccessFlag && m_pWaveMessageForPhase2)
    {
        trace (TRACE_LEVEL_ERROR, "WaveSendToClusterContext::setPartialSuccessFlag: PartialSuccess flag and rollback message can't be set at a time.");  
        trace (TRACE_LEVEL_ERROR, "WaveSendToClusterContext::setPartialSuccessFlag: Be sure about the expected behaviour - If rollback message to be sent on failure or should it be considered as PartialSuccess.");  
 
        waveAssert (false, __FILE__, __LINE__);
    }
        
    m_returnSuccessForPartialSuccessFlag = partialSuccessFlag;
}

void WaveSendToClusterContext::setIsPartialSuccessCaseFlag (const bool isPartialSuccessCase)
{
    m_isPartialSuccessCaseFlag = isPartialSuccessCase;
}

bool WaveSendToClusterContext::getIsPartialSuccessCaseFlag () const
{
    if (!m_returnSuccessForPartialSuccessFlag)
    {
        trace (TRACE_LEVEL_ERROR, "WaveSendToClusterContext::getIsPartialSuccessCaseFlag: PartialSuccessFlag is not set. So, m_isPartialSuccessCaseFlag has not updated. Please, set m_returnSuccessForPartialSuccessFlag to true if you need to knwo the Partial Success case.");
        waveAssert (false, __FILE__, __LINE__);
    }

    return m_isPartialSuccessCaseFlag;
}

vector<LocationId> WaveSendToClusterContext::getFailedOverLocations () const 
{
    return (m_failedOverLocations);
}

void WaveSendToClusterContext::setFailedOverLocations (const vector<UI32> &disconnectedLocationsForSurrogate)
{
    m_failedOverLocations = disconnectedLocationsForSurrogate;
}

bool WaveSendToClusterContext::getIsLocationsForPhase1SetByUserFlag () const
{
    return (m_isLocationsForPhase1SetByUserFlag);
}

const bool &WaveSendToClusterContext::getIsSendOneWayToWaveCluster () const
{
    return (m_isSendOneWayToWaveCluster);
}

void WaveSendToClusterContext::setIsSendOneWayToWaveCluster (bool isSendOneWayToWaveCluster)
{
    if (true == isSendOneWayToWaveCluster)
    {
        if (NULL != m_pWaveMessageForPhase2)
        {
            trace (TRACE_LEVEL_FATAL, "WaveSendToClusterContext::setIsSendOneWayToWaveCluster : Send one way to wave cluster and setting a phase2 rollback message are not allowed.");  
            waveAssert (false, __FILE__, __LINE__);
        }

        if (true == m_returnSuccessForPartialSuccessFlag)
        {
            trace (TRACE_LEVEL_FATAL, "WaveSendToClusterContext::setIsSendOneWayToWaveCluster : Send one way to wave cluster and setting partial success are not allowed."); 

            waveAssert (false, __FILE__, __LINE__);
        }
    }

    m_isSendOneWayToWaveCluster = isSendOneWayToWaveCluster;
}

}

/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Cluster/CentralClusterConfigDeleteClusterWorker.h"
#include "Cluster/ClusterTypes.h"
#include "Framework/Core/FrameworkObjectManagerMessages.h"
#include "Cluster/Local/HeartBeat/HeartBeatMessages.h"
#include "Cluster/ClusterDeleteContext.h"
#include "Cluster/ClusterMessages.h"
#include "Cluster/WaveCluster.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Cluster/Local/WaveNode.h"
#include "Framework/ObjectModel/WaveManagedObjectToolKit.h"
#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContext.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"

namespace WaveNs
{

CentralClusterConfigDeleteClusterWorker::CentralClusterConfigDeleteClusterWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager)
{
    addOperationMap (CLUSTER_DELETE_CLUSTER, reinterpret_cast<WaveMessageHandler> (&CentralClusterConfigDeleteClusterWorker::deleteClusterMessageHandler));
}

CentralClusterConfigDeleteClusterWorker::~CentralClusterConfigDeleteClusterWorker ()
{
}

WaveMessage *CentralClusterConfigDeleteClusterWorker::createMessageInstance (const UI32 &operationCode)
{
    WaveMessage *pWaveMessage = NULL;

    switch (operationCode)
    {
        case CLUSTER_DELETE_CLUSTER :
            pWaveMessage = new ClusterObjectManagerDeleteClusterMessage;
            break;

        default :
            pWaveMessage = NULL;
    }

    return (pWaveMessage);
}

void CentralClusterConfigDeleteClusterWorker::deleteClusterMessageHandler (ClusterObjectManagerDeleteClusterMessage *pClusterObjectManagerDeleteClusterMessage)
{
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&CentralClusterConfigDeleteClusterWorker::deleteClusterValidateStep),
        reinterpret_cast<WaveLinearSequencerStep> (&CentralClusterConfigDeleteClusterWorker::deleteClusterStopHeartBeatsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&CentralClusterConfigDeleteClusterWorker::deleteClusterCommitStep),
        reinterpret_cast<WaveLinearSequencerStep> (&CentralClusterConfigDeleteClusterWorker::deleteClusterRequestFrameworkToDeleteClusterStep),
        reinterpret_cast<WaveLinearSequencerStep> (&CentralClusterConfigDeleteClusterWorker::waveLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&CentralClusterConfigDeleteClusterWorker::waveLinearSequencerFailedStep)
    };

    ClusterDeleteContext *pClusterDeleteContext = new ClusterDeleteContext (pClusterObjectManagerDeleteClusterMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pClusterDeleteContext->holdAll ();
    pClusterDeleteContext->start ();
}

void CentralClusterConfigDeleteClusterWorker::deleteClusterValidateStep (ClusterDeleteContext *pClusterDeleteContext)
{
    trace (TRACE_LEVEL_DEVEL, "CentralClusterConfigDeleteClusterWorker::deleteClusterValidateStep : Entering ...");

    // Check if cluster is already created and reject if it is not already created.

    vector<WaveManagedObject *> *pResults = querySynchronously (WaveCluster::getClassName ());

    waveAssert (NULL != pResults, __FILE__, __LINE__);

    if (NULL == pResults)
    {
        pClusterDeleteContext->executeNextStep (WAVE_MESSAGE_ERROR);
        return;
    }

    UI32       numberOfResults = pResults->size ();
    ResourceId status          = WAVE_MESSAGE_SUCCESS;

    if (0 == numberOfResults)
    {
        trace (TRACE_LEVEL_WARN, "CentralClusterConfigDeleteClusterWorker::deleteClusterValidateStep : There is no cluster created.");

        status = WAVE_CLUSTER_DELETE_STATUS_CLUSTER_NOT_FOUND;
    }
    else if (1 < numberOfResults)
    {
        trace (TRACE_LEVEL_FATAL, "CentralClusterConfigDeleteClusterWorker::deleteClusterValidateStep : Multiple cluster objects found.");
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        pClusterDeleteContext->setPWaveCluster (dynamic_cast<WaveCluster *> ((*pResults)[0]));
    }

    pResults->clear ();
    delete pResults;

    pClusterDeleteContext->executeNextStep (status);
}

void CentralClusterConfigDeleteClusterWorker::deleteClusterStopHeartBeatsStep (ClusterDeleteContext *pClusterDeleteContext)
{
    trace (TRACE_LEVEL_DEVEL, "CentralClusterConfigDeleteClusterWorker::deleteClusterStopHeartBeatsStep : Entering ...");

    WaveCluster                                *pWaveCluster          = pClusterDeleteContext->getPWaveCluster ();
    vector<ObjectId>                             secondaryNodes;
    UI32                                         numberOfSecondaryNodes = 0;
    UI32                                         i                      = 0;
    string                                       secondaryNodeName;
    UI32                                         secondaryNodePort;
    WaveNode                                    *pSecondaryNode         = NULL;
    ResourceId                                   status                 = WAVE_MESSAGE_SUCCESS;
    vector<WaveManagedObject *>                 *pSecondaryNodeResults  = NULL;
    UI32                                         numberOfResults        = 0;
    ClusterObjectManagerDeleteClusterMessage    *pMessage               = reinterpret_cast<ClusterObjectManagerDeleteClusterMessage *> (pClusterDeleteContext->getPWaveMessage ());
    WaveNode                                     tempNode               (getPWaveObjectManager (), FrameworkToolKit::getThisLocationId (), FrameworkToolKit::getThisLocationIpAddress (), FrameworkToolKit::getThisLocationPort ());

    waveAssert (NULL != pWaveCluster, __FILE__, __LINE__);

    secondaryNodes         = pWaveCluster->getSecondaryNodes ();
    numberOfSecondaryNodes = secondaryNodes.size ();

    if (numberOfSecondaryNodes)
    {
        pSecondaryNodeResults = querySynchronously (WaveNode::getClassName (), secondaryNodes);
        waveAssert (NULL != pSecondaryNodeResults, __FILE__, __LINE__);

        numberOfResults = pSecondaryNodeResults->size ();
        waveAssert (numberOfSecondaryNodes == numberOfResults, __FILE__, __LINE__);
    }
    else     
    {
        trace (TRACE_LEVEL_INFO, "CentralClusterConfigDeleteClusterWorker::deleteClusterStopHeartBeatsStep: There is no Seoncdary Node Present");     
    }

    pClusterDeleteContext->setPSecondaryNodes (pSecondaryNodeResults);

    // Attempt to stop all heart beats to secondary.  Even if we fail stopping heart beats we will simply proceed.

    for (i = 0; i < numberOfSecondaryNodes; i++)
    {
        pSecondaryNode = dynamic_cast<WaveNode *> ((*pSecondaryNodeResults)[i]);

        waveAssert (NULL != pSecondaryNode, __FILE__, __LINE__);

        if ((*pSecondaryNode) != tempNode)
        {
            secondaryNodeName = pSecondaryNode->getIpAddress ();
            secondaryNodePort = pSecondaryNode->getPort ();

            StopHeartBeatMessage message;

            message.setDstIpAddress (secondaryNodeName);
            message.setDstPortNumber (secondaryNodePort);

            status = sendSynchronously (&message);

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_ERROR, "CentralClusterConfigDeleteClusterWorker::deleteClusterStopHeartBeatsStep : Failed to Stop heart beat to the Secondary Node.  Node Name : " + secondaryNodeName + string (", Port : ") + secondaryNodePort + string (", Status : ") + FrameworkToolKit::localize (status));
            }
            else
            {
                status = message.getCompletionStatus ();

                if (WAVE_MESSAGE_SUCCESS != status)
                {
                    trace (TRACE_LEVEL_ERROR, "CentralClusterConfigDeleteClusterWorker::deleteClusterStopHeartBeatsStep : Failed to Stop heart beat to the Secondary Node.  Node Name : " + secondaryNodeName + string (", Port : ") + secondaryNodePort + string (", Completion Status : ") + FrameworkToolKit::localize (status));
                }
                else
                {
                    trace (TRACE_LEVEL_INFO, "CentralClusterConfigDeleteClusterWorker::deleteClusterStopHeartBeatsStep : Stopped Heart Beat with " + secondaryNodeName + string (":") + secondaryNodePort);
                }
            }

            if (false == pMessage->getIsRebootRequired ())
            {
                (WaveFrameworkObjectManager::getInstance ())->disconnectFromLocation (secondaryNodeName, (SI32) secondaryNodePort);
            }
        }
    }

    pClusterDeleteContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void CentralClusterConfigDeleteClusterWorker::deleteClusterCommitStep (ClusterDeleteContext *pClusterDeleteContext)
{
    trace (TRACE_LEVEL_DEVEL, "CentralClusterConfigDeleteClusterWorker::deleteClusterCommitStep : Entering ...");

    WaveCluster                 *pWaveCluster          = pClusterDeleteContext->getPWaveCluster ();
    ResourceId                    status                 = WAVE_MESSAGE_SUCCESS;

    startTransaction ();

    delete pWaveCluster;
    pClusterDeleteContext->setPWaveCluster (NULL);

    //Also update the status of local wavenode

  //Update local waveNode
    WaveManagedObjectSynchronousQueryContext queryContextForPrimarywaveNode (WaveNode::getClassName ());
    string  primaryIpAddress = FrameworkToolKit::getThisLocationIpAddress ();
    UI32    primaryPort      = FrameworkToolKit::getThisLocationPort ();

    queryContextForPrimarywaveNode.addAndAttribute (new AttributeString (primaryIpAddress,     "ipAddress"));
    queryContextForPrimarywaveNode.addAndAttribute (new AttributeUI32   (primaryPort, "port"));

    vector<WaveManagedObject *>* pResultsForPrimaryWavenode = querySynchronously (&queryContextForPrimarywaveNode);
    waveAssert (NULL != pResultsForPrimaryWavenode, __FILE__, __LINE__);
    waveAssert (1 == pResultsForPrimaryWavenode->size(), __FILE__, __LINE__);

    WaveNode *pPrimaryWaveNode = dynamic_cast<WaveNode *> ((*pResultsForPrimaryWavenode)[0]);
    waveAssert( NULL != pPrimaryWaveNode, __FILE__, __LINE__);

    pPrimaryWaveNode->setGenericStatus(WAVE_MANAGED_OBJECT_GENERIC_STATUS_GOOD);
    pPrimaryWaveNode->setSpecificStatus(WAVE_MANAGED_OBJECT_SPECIFIC_STATUS_STAND_ALONE);
    updateWaveManagedObject(pPrimaryWaveNode);

    status = commitTransaction ();
    if (FRAMEWORK_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "CentralClusterConfigDeleteClusterWorker::deleteClusterCommitStep : Could not commit to repository.  status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }
    
    WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector(pResultsForPrimaryWavenode);
    pClusterDeleteContext->executeNextStep (status);
}

void CentralClusterConfigDeleteClusterWorker::deleteClusterRequestFrameworkToDeleteClusterStep (ClusterDeleteContext *pClusterDeleteContext)
{
    trace (TRACE_LEVEL_DEVEL, "CentralClusterConfigDeleteClusterWorker::deleteClusterRequestFrameworkToDeleteClusterStep : Entering ...");

    ClusterObjectManagerDeleteClusterMessage    *pClusterObjectManagerDeleteClusterMessage    = reinterpret_cast<ClusterObjectManagerDeleteClusterMessage *> (pClusterDeleteContext->getPWaveMessage ());
    WaveServiceId                               serderServiceId                              = pClusterObjectManagerDeleteClusterMessage->getSenderServiceCode ();

    FrameworkObjectManagerDestroyClusterMessage *pFrameworkObjectManagerDestroyClusterMessage = new FrameworkObjectManagerDestroyClusterMessage ();
    ResourceId                                   status                                       = WAVE_MESSAGE_SUCCESS;

    pFrameworkObjectManagerDestroyClusterMessage->setOriginalRequester (serderServiceId);
    pFrameworkObjectManagerDestroyClusterMessage->setIsRebootRequired (pClusterObjectManagerDeleteClusterMessage->getIsRebootRequired ());

    status = sendOneWay (pFrameworkObjectManagerDestroyClusterMessage);
    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR, "CentralClusterConfigDeleteClusterWorker::deleteClusterRequestFrameworkToDeleteClusterStep : Error in requesting framework to delete cluster.  status : " + FrameworkToolKit::localize (status));

        pClusterDeleteContext->executeNextStep (status);
        return;
    }
    pClusterDeleteContext->executeNextStep (status);
}

void CentralClusterConfigDeleteClusterWorker::deleteClusterRequestFrameworkToDeleteClusterCallback (FrameworkStatus frameworkStatus, FrameworkObjectManagerDestroyClusterMessage *pFrameworkObjectManagerDestroyClusterMessage, void *pContext)
{
    trace (TRACE_LEVEL_DEVEL, "CentralClusterConfigDeleteClusterWorker::deleteClusterRequestFrameworkToDeleteClusterCallback : Entering ...");

    ClusterDeleteContext *pClusterDeleteContext = reinterpret_cast<ClusterDeleteContext *> (pContext);
    ResourceId            status                = WAVE_MESSAGE_SUCCESS;

    if (FRAMEWORK_SUCCESS != frameworkStatus)
    {
        status = frameworkStatus;

        trace (TRACE_LEVEL_ERROR, "CentralClusterConfigDeleteClusterWorker::deleteClusterRequestFrameworkToDeleteClusterCallback : Error in requesting framework to delete cluster.  status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = pFrameworkObjectManagerDestroyClusterMessage->getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, "CentralClusterConfigDeleteClusterWorker::deleteClusterRequestFrameworkToDeleteClusterCallback : Error in requesting framework to delete cluster.  Completion Status : " + FrameworkToolKit::localize (status));
        }
    }

    delete pFrameworkObjectManagerDestroyClusterMessage;

    pClusterDeleteContext->executeNextStep (status);
    return;
}

}

/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#include "Cluster/CentralClusterConfigDeleteNodeWorker.h"
#include "Cluster/CentralClusterConfigObjectManager.h"
#include "Cluster/ClusterMessages.h"
#include "Cluster/ClusterTypes.h"
#include "Cluster/Local/WaveNode.h"
#include "Framework/Core/FrameworkObjectManagerMessages.h"
#include "Cluster/WaveCluster.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContext.h"
#include "Framework/Utils/FrameworkToolKit.h"

namespace WaveNs
{

CentralClusterConfigDeleteNodeWorker::CentralClusterConfigDeleteNodeWorker (CentralClusterConfigObjectManager *pCentralClusterConfigObjectManager)
    : WaveWorker (pCentralClusterConfigObjectManager)
{
    addOperationMap (CLUSTER_DELETE_NODE, reinterpret_cast<WaveMessageHandler> (&CentralClusterConfigDeleteNodeWorker::deleteNodeMessageHandler));
}

CentralClusterConfigDeleteNodeWorker::~CentralClusterConfigDeleteNodeWorker ()
{
}

WaveMessage *CentralClusterConfigDeleteNodeWorker::createMessageInstance (const UI32 &operationCode)
{
    WaveMessage *pWaveMessage = NULL;

    switch (operationCode)
    {
        case CLUSTER_DELETE_NODE :
            pWaveMessage = new ClusterObjectManagerDeleteNodeMessage;
            break;

        default :
            pWaveMessage = NULL;
    }

    return (pWaveMessage);
}

void CentralClusterConfigDeleteNodeWorker::deleteNodeMessageHandler (ClusterObjectManagerDeleteNodeMessage *pClusterObjectManagerDeleteNodeMessage)
{
    trace (TRACE_LEVEL_DEVEL, "CentralClusterConfigAddNodeWorker::deleteNodeMessageHandler : Entering ...");

    WaveLinearSequencerContext *pWaveLinearSequencerContext;

    // In case of deletion of a disconnected node, we do not need to explicitly stop HB as it would have been
    // done during HB failure.    
    if (true == pClusterObjectManagerDeleteNodeMessage->getIsDisconnected())
    {
        WaveLinearSequencerStep sequencerForDisconnectedSteps[] =
        {
            reinterpret_cast<WaveLinearSequencerStep> (&CentralClusterConfigDeleteNodeWorker::deleteNodeValidateStep),
            reinterpret_cast<WaveLinearSequencerStep> (&CentralClusterConfigDeleteNodeWorker::deleteNodeRequestFrameworkToDeleteNodeStep),
            reinterpret_cast<WaveLinearSequencerStep> (&CentralClusterConfigDeleteNodeWorker::waveLinearSequencerSucceededStep),
            reinterpret_cast<WaveLinearSequencerStep> (&CentralClusterConfigDeleteNodeWorker::waveLinearSequencerFailedStep)
        };

        pWaveLinearSequencerContext = new WaveLinearSequencerContext (pClusterObjectManagerDeleteNodeMessage, this, sequencerForDisconnectedSteps, sizeof (sequencerForDisconnectedSteps) / sizeof (sequencerForDisconnectedSteps[0]));
    }
    else  
    {
        WaveLinearSequencerStep sequencerSteps[] =
        {
            reinterpret_cast<WaveLinearSequencerStep> (&CentralClusterConfigDeleteNodeWorker::deleteNodeValidateStep),
            reinterpret_cast<WaveLinearSequencerStep> (&CentralClusterConfigDeleteNodeWorker::deleteNodeStopHeartBeatsStep),
            reinterpret_cast<WaveLinearSequencerStep> (&CentralClusterConfigDeleteNodeWorker::deleteNodeRequestFrameworkToDeleteNodeStep),
            reinterpret_cast<WaveLinearSequencerStep> (&CentralClusterConfigDeleteNodeWorker::waveLinearSequencerSucceededStep),
            reinterpret_cast<WaveLinearSequencerStep> (&CentralClusterConfigDeleteNodeWorker::waveLinearSequencerFailedStep)
        };

        pWaveLinearSequencerContext = new WaveLinearSequencerContext (pClusterObjectManagerDeleteNodeMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    }
    //  pWaveLinearSequencerContext->holdAll ();
    pWaveLinearSequencerContext->start ();

}

void CentralClusterConfigDeleteNodeWorker::deleteNodeValidateStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_INFO, "CentralClusterConfigdeleteNodeWorker::deleteNodeValidateStep : starting ...");

    ClusterObjectManagerDeleteNodeMessage *pClusterObjectManagerDeleteNodeMessage = reinterpret_cast<ClusterObjectManagerDeleteNodeMessage *> (pWaveLinearSequencerContext->getPWaveMessage ());

    string                               nodeName;
    SI32                                 nodePort;
    UI32                                 i, j;
    vector<WaveManagedObject *>         *pResults = NULL;
    WaveNode                            *pNode    = NULL;
    UI32                                 noOfSecondaryNodes;
    UI32                                 validSecondaryNode = 0;
    ResourceId                           status   = WAVE_MESSAGE_SUCCESS;
    UI32                                 noOfNode = pClusterObjectManagerDeleteNodeMessage->getNNodesToDelete ();
    vector<string>                       NodeNames;
    vector<UI32>                         NodePorts;
    UI32                                 NodeSize;
    string                               primaryNodeName = FrameworkToolKit::getClusterPrimaryIpAddress ();
    SI32                                 primaryNodePort = FrameworkToolKit::getClusterPrimaryPort ();

    //Check if node is a part of cluster 

    pResults = querySynchronously (WaveNode::getClassName ());

    waveAssert (NULL != pResults, __FILE__, __LINE__);

    noOfSecondaryNodes = pResults->size ();

    for (j = 0; j < noOfNode; j++)
    {
        nodeName = pClusterObjectManagerDeleteNodeMessage->getNodeName (j);
        nodePort = pClusterObjectManagerDeleteNodeMessage->getNodePort (j);

        NodeNames.push_back (nodeName);
        NodePorts.push_back (nodePort);

        for (i = 0; i < noOfSecondaryNodes; i++)
        {
            pNode = dynamic_cast<WaveNode *> ((*pResults)[i]);

            waveAssert (NULL != pNode, __FILE__, __LINE__);
        
            if (((pNode->getIpAddress ()) ==  nodeName) && ((pNode->getPort ()) ==  (UI32) nodePort))
            {
                validSecondaryNode = 1;
                break;
            }
        }
        
        if ((nodeName == primaryNodeName) && (nodePort == primaryNodePort))
        {
            trace (TRACE_LEVEL_ERROR, "CentralClusterConfigAddNodeWorker::deleteNodeValidateStep: Can Node Delete Primary Node");
            validSecondaryNode = 0;
            break;
        }
        //check if deleting any node twice

        NodeSize = NodeNames.size ();

        for (i = 0; i < NodeSize - 1 ; i++)
        {
            if ((nodeName == NodeNames[i]) && ((UI32) nodePort == NodePorts[i]))
            {
                trace (TRACE_LEVEL_ERROR, "CentralClusterConfigAddNodeWorker::deleteNodeValidateStep: please check for Duplicate Node in delete nodes");
                validSecondaryNode = 0;
                break;
            }
    
        }

        // In case of deletion of disconnected node, check for disconnected status.
        if (true == pClusterObjectManagerDeleteNodeMessage->getIsDisconnected())
        {
            if (WAVE_MANAGED_OBJECT_SPECIFIC_STATUS_SECONDARY_NOT_CONNECTED_TO_CLUSTER != pNode->getSpecificStatus())
            {
                trace (TRACE_LEVEL_ERROR, "CentralClusterConfigAddNodeWorker::deleteNodeValidateStep: Not a disconnected node");
                validSecondaryNode = 0;
                break; 
            }   
        }
    }

    if (!validSecondaryNode) 
    {
       trace (TRACE_LEVEL_ERROR, "CentralClusterConfigAddNodeWorker::deleteNodeValidateStep: Invalid Node Name/ port" + nodeName + string(" ")+nodePort);
       status = WAVE_MESSAGE_ERROR;
    }

    for (i = 0; i < noOfSecondaryNodes; i++)
    {
        delete (*pResults)[i];
    }

    pResults->clear ();
    delete pResults;

    pWaveLinearSequencerContext->executeNextStep (status);
}

void CentralClusterConfigDeleteNodeWorker::deleteNodeStopHeartBeatsStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_INFO, "CentralClusterConfigDeleteNodeWorker::deleteNodeStopHeartBeatStep : starting ...");

    ClusterObjectManagerDeleteNodeMessage *pClusterObjectManagerDeleteNodeMessage = reinterpret_cast<ClusterObjectManagerDeleteNodeMessage *> (pWaveLinearSequencerContext->getPWaveMessage ());
    string                               nodeName;
    UI32                                 nodePort;
    ResourceId                           status   = WAVE_MESSAGE_SUCCESS;
    StopHeartBeatMessage                 message;
    UI32                                 noOfNode = pClusterObjectManagerDeleteNodeMessage->getNNodesToDelete ();
    UI32                                 i;

    for (i = 0; i < noOfNode; i++)
    {
        nodeName = pClusterObjectManagerDeleteNodeMessage->getNodeName (i);
        nodePort = pClusterObjectManagerDeleteNodeMessage->getNodePort (i);
    
        message.setDstIpAddress (nodeName);
        message.setDstPortNumber (nodePort);

        status = sendSynchronously (&message);
    
        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, "CentralClusterConfigDeleteNodeWorker::deleteNodeStopHeartBeatsStep : Failed to Stop heart beat to the Secondary Node.  Node Name : " + nodeName + string (", Port : ") + nodePort + string (", Status : ") + FrameworkToolKit::localize (status));
        }
        else
        {
            status = message.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_ERROR, "CentralClusterConfigDeleteNodeWorker::deleteNodeStopHeartBeatsStep : Failed to Stop heart beat to the Secondary Node.  Node Name : " + nodeName + string (", Port : ") + nodePort + string (", Completion Status : ") + FrameworkToolKit::localize (status));
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "CentralClusterConfigDeleteNodeWorker::deleteNodeStopHeartBeatsStep : Stopped Heart Beat with " + nodeName + string (":") + nodePort);
            }
        }
    }

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);

}

void CentralClusterConfigDeleteNodeWorker::deleteNodeRequestFrameworkToDeleteNodeStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_INFO, "CentralClusterConfigDeleteClusterWorker::deleteNodeRequestFrameworkToDeleteNodeStep : Entering ...");

        ClusterObjectManagerDeleteNodeMessage               *pClusterObjectManagerDeleteNodeMessage               = reinterpret_cast<ClusterObjectManagerDeleteNodeMessage *> (pWaveLinearSequencerContext->getPWaveMessage ());
        FrameworkObjectManagerDeleteNodesFromClusterMessage *pFrameworkObjectManagerDeleteNodesFromClusterMessage = new FrameworkObjectManagerDeleteNodesFromClusterMessage ();
        ResourceId                                           status                                               = WAVE_MESSAGE_SUCCESS;
        UI32                                                 i                                                    = 0;
        UI32                                                 noNodes                                              = pClusterObjectManagerDeleteNodeMessage->getNNodesToDelete ();
        string                                               nodeName;
        SI32                                                 nodePort;


        for (i = 0; i < noNodes; i++)
        {
            nodeName = pClusterObjectManagerDeleteNodeMessage->getNodeName (i);
            nodePort = pClusterObjectManagerDeleteNodeMessage->getNodePort (i);

            pFrameworkObjectManagerDeleteNodesFromClusterMessage->addNodeIpAddressAndPort (nodeName, nodePort);

        }

        // Set flag to indicate deletion of a disconnected node.  
        if (true == pClusterObjectManagerDeleteNodeMessage->getIsDisconnected()) 
        {
            pFrameworkObjectManagerDeleteNodesFromClusterMessage->setIsDisconnected(true);
        }

        status = send (pFrameworkObjectManagerDeleteNodesFromClusterMessage, reinterpret_cast<WaveMessageResponseHandler> (&CentralClusterConfigDeleteNodeWorker::deleteNodeRequestFrameworkToDeleteNodeCallback), pWaveLinearSequencerContext);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, "CentralClusterConfigDeleteNodeWorker::deleteNodeRequestFrameworkToDeleteNodeStep : Error in requesting framework to delete cluster.  status : " + FrameworkToolKit::localize (status));

            pWaveLinearSequencerContext->executeNextStep (status);         
        
            return;
        } else {
            trace (TRACE_LEVEL_INFO, "CentralClusterConfigDeleteClusterWorker::deleteNodeRequestFrameworkToDeleteNodeStep : Sent ...");
        }

//    pWaveLinearSequencerContext->executeNextStep (status);  
}

void CentralClusterConfigDeleteNodeWorker::deleteNodeRequestFrameworkToDeleteNodeCallback (FrameworkStatus frameworkStatus, FrameworkObjectManagerDeleteNodesFromClusterMessage *pFrameworkObjectManagerDeleteNodesFromClusterMessage, void *pContext)
{
    trace (TRACE_LEVEL_INFO, "CentralClusterConfigDeleteNodeWorker::deleteNodeRequestFrameworkToDeleteNodeCallback : Entering ...");

    WaveLinearSequencerContext *pWaveLinearSequencerContext  = reinterpret_cast<WaveLinearSequencerContext *> (pContext);
    ClusterObjectManagerDeleteNodeMessage *pClusterObjectManagerDeleteNodeMessage = reinterpret_cast<ClusterObjectManagerDeleteNodeMessage *> (pWaveLinearSequencerContext->getPWaveMessage ());

    ResourceId                                status                                    = WAVE_MESSAGE_SUCCESS;
    string                                               nodeName;
    SI32                                                 nodePort;
    UI32                                                 noNodes = pClusterObjectManagerDeleteNodeMessage->getNNodesToDelete ();
    UI32 i;

    if (FRAMEWORK_SUCCESS != frameworkStatus)
    {
        status = frameworkStatus;

        for (i = 0; i < noNodes; i++)
        {
            nodeName = pClusterObjectManagerDeleteNodeMessage->getNodeName (i);
            nodePort = pClusterObjectManagerDeleteNodeMessage->getNodePort (i);

            pClusterObjectManagerDeleteNodeMessage->setNodeStatus (nodeName, nodePort, status);
        }

        if(WAVE_MESSAGE_ERROR_REMOTE_LOCATION_UNAVAILABLE == status) {
            status = WAVE_MESSAGE_SUCCESS;
        }
    }
    else
    {
        for (i = 0; i < noNodes; i++)
        {
            nodeName = pClusterObjectManagerDeleteNodeMessage->getNodeName (i);
            nodePort = pClusterObjectManagerDeleteNodeMessage->getNodePort (i);

            status = pFrameworkObjectManagerDeleteNodesFromClusterMessage->getNodeStatus (nodeName, nodePort);

            pClusterObjectManagerDeleteNodeMessage->setNodeStatus (nodeName, nodePort, status);
        }
    }

    delete (pFrameworkObjectManagerDeleteNodesFromClusterMessage);

    pWaveLinearSequencerContext->executeNextStep (status);
}

}


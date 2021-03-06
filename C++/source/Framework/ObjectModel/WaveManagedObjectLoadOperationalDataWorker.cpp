/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveManagedObjectLoadOperationalDataWorker.h"
#include "Framework/Types/Types.h"
#include "Framework/Core/WaveFrameworkMessages.h"
#include "Framework/ObjectModel/LoadOperationalDataContext.h"
#include "Framework/ObjectModel/WaveManagedObjectLoadOperationalDataContext.h"
#include "Framework/ObjectModel/WaveManagedObject.h"

namespace WaveNs
{

WaveManagedObjectLoadOperationalDataWorker::WaveManagedObjectLoadOperationalDataWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager)
{
    addOperationMap (WAVE_OBJECT_MANAGER_LOAD_OPERATIONAL_DATA_FOR_MANAGED_OBJECT, reinterpret_cast<WaveMessageHandler> (&WaveManagedObjectLoadOperationalDataWorker::loadOperationalDataHandler));
}

WaveManagedObjectLoadOperationalDataWorker::~WaveManagedObjectLoadOperationalDataWorker ()
{
}

WaveMessage *WaveManagedObjectLoadOperationalDataWorker::createMessageInstance (const UI32 &operationCode)
{
    WaveMessage *pWaveMessage = NULL;

    switch (operationCode)
    {
        case WAVE_OBJECT_MANAGER_LOAD_OPERATIONAL_DATA_FOR_MANAGED_OBJECT :
            pWaveMessage = new WaveLoadOperationalDataForManagedObjectObjectManagerMessage;
            break;

        default :
            pWaveMessage = NULL;
    }

    return (pWaveMessage);
}

void WaveManagedObjectLoadOperationalDataWorker::loadOperationalDataHandler (WaveLoadOperationalDataForManagedObjectObjectManagerMessage *pWaveLoadOperationalDataForManagedObjectObjectManagerMessage)
{
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectLoadOperationalDataWorker::loadOperationalDataQueryManagedObjectStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectLoadOperationalDataWorker::loadOperationalDataLoadStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectLoadOperationalDataWorker::waveLinearSequencerStartTransactionStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectLoadOperationalDataWorker::loadOperationalDataUpdateWaveManagedObjectStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectLoadOperationalDataWorker::waveLinearSequencerCommitTransactionStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectLoadOperationalDataWorker::waveLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectLoadOperationalDataWorker::waveLinearSequencerFailedStep),
    };

    LoadOperationalDataContext *pLoadOperationalDataContext = new LoadOperationalDataContext (pWaveLoadOperationalDataForManagedObjectObjectManagerMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pLoadOperationalDataContext->setWaveManagedObjectId   (pWaveLoadOperationalDataForManagedObjectObjectManagerMessage->getObjectId              ());
    pLoadOperationalDataContext->setOperationalDataFields (pWaveLoadOperationalDataForManagedObjectObjectManagerMessage->getOperationalDataFields ());

    pLoadOperationalDataContext->holdAll ();
    pLoadOperationalDataContext->start ();
}

void WaveManagedObjectLoadOperationalDataWorker::loadOperationalDataQueryManagedObjectStep (LoadOperationalDataContext *pLoadOperationalDataContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectLoadOperationalDataWorker::loadOperationalDataQueryManagedObjectStep : Entering ...");

    ObjectId           waveManagedObjectId = pLoadOperationalDataContext->getWaveManagedObjectId ();
    WaveManagedObject *pWaveManagedObject  = queryManagedObject (waveManagedObjectId);
    ResourceId         status              = WAVE_MESSAGE_SUCCESS;
    WaveManagedObject *pComposedManagedObject = NULL;
    
	if (NULL != pWaveManagedObject)
    {
	    if (ObjectId::NullObjectId != pWaveManagedObject->getOwnerManagedObjectId()) 
	    {
            // This is the case where the current MO is a composed one
            WaveManagedObject *pOwnerWaveManagedObject = queryManagedObject (pWaveManagedObject->getOwnerManagedObjectId());

            delete pWaveManagedObject;

            if (NULL == pOwnerWaveManagedObject)
            {
                status = WAVE_MANAGED_OBJECT_LOAD_OPERATIONAL_DATA_OBJECT_OWNER_NOT_FOUND;
            }
		    else 
		    {
                pComposedManagedObject = pOwnerWaveManagedObject->getComposedManagedObject(waveManagedObjectId);
			    if (NULL == pComposedManagedObject) 
			    {
                    trace (TRACE_LEVEL_ERROR, "WaveManagedObjectLoadOperationalDataWorker::loadOperationalDataQueryManagedObjectStep: The Composed Managed Object of the parent Managed Object does not exist. Please check if the composition relationship has been defined properly. ");
                    status = WAVE_MANAGED_OBJECT_LOAD_OPERATIONAL_DATA_COMPOSED_OBJECT_NOT_FOUND_BY_OWNER;
			    }
			    else
			    {
                    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectLoadOperationalDataWorker::loadOperationalDataQueryManagedObjectStep: The class name of the composed managed object is : " + pComposedManagedObject->getObjectClassName ());
                    pLoadOperationalDataContext->setPWaveManagedObject (pComposedManagedObject);
				    pLoadOperationalDataContext->setPOwnerWaveManagedObject (pOwnerWaveManagedObject);
			    }
		    }
	    }
		else 
		{
            pLoadOperationalDataContext->setPWaveManagedObject (pWaveManagedObject);
		}
    }
    else
    {
        status = WAVE_MANAGED_OBJECT_LOAD_OPERATIONAL_DATA_OBJECT_NOT_FOUND;
    }
                    


    pLoadOperationalDataContext->executeNextStep (status);
}

void WaveManagedObjectLoadOperationalDataWorker::loadOperationalDataLoadStep (LoadOperationalDataContext *pLoadOperationalDataContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectLoadOperationalDataWorker::loadOperationalDataLoadStep : Entering ...");

    WaveManagedObject *pWaveManagedObject = pLoadOperationalDataContext->getPWaveManagedObject ();

    waveAssert (NULL != pWaveManagedObject, __FILE__, __LINE__);
        
    WaveManagedObjectLoadOperationalDataContext *pWaveManagedObjectLoadOperationalDataContext = new WaveManagedObjectLoadOperationalDataContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveManagedObjectLoadOperationalDataWorker::loadOperationalDataLoadCallback), pLoadOperationalDataContext);

    waveAssert (NULL != pWaveManagedObjectLoadOperationalDataContext, __FILE__, __LINE__);

    pWaveManagedObjectLoadOperationalDataContext->setOperationalDataFields (pLoadOperationalDataContext->getOperationalDataFields ());

    if (NULL != pLoadOperationalDataContext->getPOwnerWaveManagedObject ()) 
	{
        pWaveManagedObjectLoadOperationalDataContext->setPOwnerManagedObject   (pLoadOperationalDataContext->getPOwnerWaveManagedObject ());
	}

    pWaveManagedObject->loadOperationalData (pWaveManagedObjectLoadOperationalDataContext);
    
}

void WaveManagedObjectLoadOperationalDataWorker::loadOperationalDataLoadCallback (WaveManagedObjectLoadOperationalDataContext *pWaveManagedObjectLoadOperationalDataContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectLoadOperationalDataWorker::loadOperationalDataLoadCallback : Entering ...");

    LoadOperationalDataContext *pLoadOperationalDataContext = reinterpret_cast<LoadOperationalDataContext *> (pWaveManagedObjectLoadOperationalDataContext->getPCallerContext ());
    ResourceId                  status                      = pWaveManagedObjectLoadOperationalDataContext->getCompletionStatus ();

    waveAssert (NULL != pLoadOperationalDataContext, __FILE__, __LINE__);

    delete pWaveManagedObjectLoadOperationalDataContext;
    
    pLoadOperationalDataContext->executeNextStep (status);
}

void WaveManagedObjectLoadOperationalDataWorker::loadOperationalDataUpdateWaveManagedObjectStep (LoadOperationalDataContext *pLoadOperationalDataContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectLoadOperationalDataWorker::loadOperationalDataUpdateWaveManagedObjectStep : Entering ...");

    WaveManagedObject *pWaveManagedObject = pLoadOperationalDataContext->getPWaveManagedObject ();

    waveAssert (NULL != pWaveManagedObject, __FILE__, __LINE__);

    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectLoadOperationalDataWorker::loadOperationalDataUpdateWaveManagedObjectStep: The class name of the composed managed object is : " + pWaveManagedObject->getObjectClassName ());

    updateWaveManagedObject (pWaveManagedObject);

    pLoadOperationalDataContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

}

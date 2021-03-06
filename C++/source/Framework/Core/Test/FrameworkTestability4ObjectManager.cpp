/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include <time.h>
#include "Framework/Core/Test/FrameworkTestability4ObjectManager.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Utils/WaveAsynchronousContext.h"
#include "Framework/Core/Test/WaveTestManagedObject1.h"
#include "Framework/Core/Test/WaveTestManagedObject2.h"
#include "Framework/Core/Test/WaveTestManagedObject3.h"
#include "Framework/Core/Test/WaveTestManagedObject4.h"
#include "Framework/Core/Test/WaveTestManagedObject5.h"
#include "Framework/Core/Test/WaveTestManagedView1.h"
#include "Framework/Core/Test/WaveTestManagedView2.h"
#include "Framework/Core/Test/WaveTestManagedObject6.h"
#include "Framework/Core/Test/WaveTestManagedObject7.h"
#include "Framework/Core/Test/WaveTestManagedObject8.h"
#include "Framework/Core/Test/WaveTestManagedObject10.h"
#include "Framework/Core/Test/WaveTestManagedObject11.h"
#include "Framework/Core/Test/WaveTestManagedObject12.h"
#include "Framework/Core/Test/FrameworkTestabilityMessages.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Core/Test/FrameworkPersistenceTestContext.h"
#include "Framework/ObjectModel/WaveManagedObjectQueryContext.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"
#include "Framework/Core/Test/FrameworkTestability4ObjectManagerGetManagedObjects.h"
#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContext.h"
#include "Framework/ObjectModel/WaveManagedObjectSynchronousInnerQueryContext.h"
#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContextForDeletion.h"
#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContextForUpdate.h"
#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContextForSetOperation.h"
#include "Framework/ObjectModel/WaveManagedObjectPointer.cpp"
#include "Framework/ObjectModel/WaveManagedObjectToolKit.h"
#include "Framework/ObjectModel/WaveSendToClusterContext.h"
#include "Framework/Attributes/AttributeTypes.h"
#include "Framework/Attributes/AttributeSqlBetween.h"
#include "Framework/Attributes/AttributeSqlIn.h"
#include "Framework/Attributes/AttributeSqlExists.h"


namespace WaveNs
{

FrameworkTestability4ObjectManager::FrameworkTestability4ObjectManager ()
    : WaveLocalObjectManager (getWaveServiceName ())
{
    WaveTestManagedObject1 waveTestManagedObject1 (this);
    WaveTestManagedObject2 waveTestManagedObject2 (this);
    WaveTestManagedObject3 waveTestManagedObject3 (this);
    WaveTestManagedObject4 waveTestManagedObject4 (this);
    WaveTestManagedObject5 waveTestManagedObject5 (this);
    WaveTestManagedObject6  waveTestManagedObject6  (this);
    WaveTestManagedObject7  waveTestManagedObject7  (this);
    WaveTestManagedObject8  waveTestManagedObject8  (this);
    WaveTestManagedObject10 waveTestManagedObject10 (this);
    WaveTestManagedObject11 waveTestManagedObject11 (this);
    WaveTestManagedObject12 waveTestManagedObject12 (this);
    WaveTestManagedView1   waveTestManagedView1   (this);
    WaveTestManagedView2   waveTestManagedView2   (this);

    waveTestManagedObject1.setupOrm ();
    waveTestManagedObject2.setupOrm ();
    waveTestManagedObject3.setupOrm ();
    waveTestManagedObject4.setupOrm ();
    waveTestManagedObject5.setupOrm ();
    waveTestManagedObject6.setupOrm ();
    waveTestManagedObject7.setupOrm ();
    waveTestManagedObject8.setupOrm ();
    waveTestManagedObject10.setupOrm ();
    waveTestManagedObject11.setupOrm ();
    waveTestManagedObject12.setupOrm ();
    waveTestManagedView1.setupOrm   ();
    waveTestManagedView2.setupOrm   ();

    addManagedClass (WaveTestManagedObject1::getClassName ());
    addManagedClass (WaveTestManagedObject2::getClassName ());
    addManagedClass (WaveTestManagedObject3::getClassName ());
    addManagedClass (WaveTestManagedObject4::getClassName ());
    addManagedClass (WaveTestManagedObject5::getClassName ());
    addManagedClass (WaveTestManagedObject6::getClassName ());
    addManagedClass (WaveTestManagedObject10::getClassName ());
    addManagedClass (WaveTestManagedObject11::getClassName ());
    addManagedClass (WaveTestManagedObject12::getClassName ());
    addManagedClass (WaveTestManagedObject7::getClassName ());
    addManagedClass (WaveTestManagedObject8::getClassName ());
    addManagedClass (WaveTestManagedView1::getClassName ());
    addManagedClass (WaveTestManagedView2::getClassName ());

    addOperationMap (FRAMEWORK_TESTABILITY_MESSAGE8,              reinterpret_cast<WaveMessageHandler> (&FrameworkTestability4ObjectManager::frameworkTestabilityMessage8RequestHandler));
    
    addOperationMap (FRAMEWORK_TESTABILITY_MESSAGE9, reinterpret_cast<WaveMessageHandler> (&FrameworkTestability4ObjectManager::frameworkTestability9MessageHandler));

    addOperationMap (FRAMEWORK_TESTABILITY_4_GET_MANAGED_OBJECTS, reinterpret_cast<WaveMessageHandler> (&FrameworkTestability4ObjectManager::getManagedObjectsMessageHandler));
}

FrameworkTestability4ObjectManager::~FrameworkTestability4ObjectManager ()
{
}

FrameworkTestability4ObjectManager *FrameworkTestability4ObjectManager::getInstance ()
{
    static FrameworkTestability4ObjectManager *pFrameworkTestability4ObjectManager = new FrameworkTestability4ObjectManager ();

    WaveNs::waveAssert (NULL != pFrameworkTestability4ObjectManager, __FILE__, __LINE__);

    return (pFrameworkTestability4ObjectManager);
}

WaveServiceId FrameworkTestability4ObjectManager::getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

string FrameworkTestability4ObjectManager::getWaveServiceName ()
{
    return ("Framework Testability 4");
}

void FrameworkTestability4ObjectManager::initialize (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    trace (TRACE_LEVEL_DEVEL, "FrameworkTestability4ObjectManager::initialize : Entering ...");

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

WaveMessage *FrameworkTestability4ObjectManager::createMessageInstance (const UI32 &operationCode)
{
    WaveMessage *pWaveMessage = NULL;

    switch (operationCode)
    {
        case FRAMEWORK_TESTABILITY_4_GET_MANAGED_OBJECTS :
            pWaveMessage = new FrameworkTestability4ObjectManagerGetManagedObjects;
            break;
        
        case FRAMEWORK_TESTABILITY_MESSAGE9 :
            pWaveMessage = new FrameworkTestabilityMessage9;
            break;

        default :
            pWaveMessage = NULL;
    }

    return (pWaveMessage);
}

WaveManagedObject *FrameworkTestability4ObjectManager::createManagedObjectInstance (const string &managedClassName)
{
    WaveManagedObject *pWaveManagedObject = NULL;

    if ((WaveTestManagedObject1::getClassName ()) == managedClassName)
    {
        pWaveManagedObject = new WaveTestManagedObject1 (this);
    }
    else if ((WaveTestManagedObject2::getClassName ()) == managedClassName)
    {
        pWaveManagedObject = new WaveTestManagedObject2 (this);
    }
    else if ((WaveTestManagedObject3::getClassName ()) == managedClassName)
    {
        pWaveManagedObject = new WaveTestManagedObject3 (this);
    }
    else if ((WaveTestManagedObject4::getClassName ()) == managedClassName)
    {
        pWaveManagedObject = new WaveTestManagedObject4 (this);
    }
    else if ((WaveTestManagedObject5::getClassName ()) == managedClassName)
    {
        pWaveManagedObject = new WaveTestManagedObject5 (this);
    }
    else if ((WaveTestManagedObject6::getClassName ()) == managedClassName)
    {
        pWaveManagedObject = new WaveTestManagedObject6 (this);
    }
    else if ((WaveTestManagedObject7::getClassName ()) == managedClassName)
    {
        pWaveManagedObject = new WaveTestManagedObject7 (this);
    }
    else if ((WaveTestManagedObject8::getClassName ()) == managedClassName)
    {
        pWaveManagedObject = new WaveTestManagedObject8 (this);
    }
    else if ((WaveTestManagedObject10::getClassName ()) == managedClassName)
    {
        pWaveManagedObject = new WaveTestManagedObject10 (this);
    }
    else if ((WaveTestManagedObject11::getClassName ()) == managedClassName)
    {
        pWaveManagedObject = new WaveTestManagedObject11 (this);
    }
    else if ((WaveTestManagedObject12::getClassName ()) == managedClassName)
    {
        pWaveManagedObject = new WaveTestManagedObject12 (this);
    }
    else if ((WaveTestManagedView1::getClassName ()) == managedClassName)
    {
        pWaveManagedObject = new WaveTestManagedView1 (this);
    }
    else if ((WaveTestManagedView2::getClassName ()) == managedClassName)
    {
        pWaveManagedObject = new WaveTestManagedView2 (this);
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, "FrameworkTestability4ObjectManager::createManagedObjectInstance : Unknown Managed Class Name : " + managedClassName);
    }

    return (pWaveManagedObject);
}

void FrameworkTestability4ObjectManager::frameworkTestabilityMessage8RequestHandler (FrameworkTestabilityMessage8 *pFrameworkTestabilityMessage8)
{
   UI32 isPagingTestEnabled = pFrameworkTestabilityMessage8->getPageSize();
   if (!isPagingTestEnabled)
   {
 
    WaveLinearSequencerStep sequencerSteps[] =
    {

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleTransactionTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryUsingEqualTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryUsingNotEqualTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryUsingGreaterThanTest1Step),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryUsingGreaterThanTest2Step),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryUsingGreaterThanOrEqualToTest1Step),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryUsingGreaterThanOrEqualToTest2Step),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryUsingLessThanTest1Step),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryUsingLessThanTest2Step),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryUsingLessThanOrEqualToTest1Step),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryUsingLessThanOrEqualToTest2Step),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryUsingLikeTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryUsingNotLikeTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryUsingILikeTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryUsingNotILikeTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryByAttributeTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryByAttributeRangeTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryByAttributeSqlBetweenTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryByAttributeSqlBetweenStringTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryByAttributeSqlInTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryByAttributeSqlInStringTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryWithOneConditionSetTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryWithTwoConditionSets1TestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryWithTwoConditionSets2TestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryWithThreeConditionSetsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleSynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleSynchronousQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleSynchronousQueryByObjectIdTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleSynchronousQueryWithConditionSetsTestStep),


        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleUpdateTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simplePartialUpdateTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simplePartialIncrementalUpdateTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleSynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleSynchronousQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleSynchronousQueryByObjectIdTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::largeUpdateTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleSynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleSynchronousQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleSynchronousQueryByObjectIdTestStep),

        //Testing of updateMultipleWaveManagedObjects using update Context
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::updateAllRowsWithUpdateContextTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::partialUpdateAllRowsWithUpdateContextTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::updateFewRowsWithUpdateContextTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryTestStep),


        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::deleteAllCreatedObjectsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleSynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleSynchronousQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleSynchronousQueryByObjectIdTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::largeTransactionTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleSynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleSynchronousQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleSynchronousQueryByObjectIdTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::deleteAllCreatedObjectsTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleSynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleSynchronousQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleSynchronousQueryByObjectIdTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleTransactionTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::deleteAllUsingDeleteWaveManagedObjectWithObjectIdTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleSynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleSynchronousQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleSynchronousQueryByObjectIdTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleTransactionTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::deleteAllUsingDeleteWaveManagedObjectWithDeletionContextTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleSynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleSynchronousQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleSynchronousQueryByObjectIdTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToAssociationTransactionTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationSynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationSynchronousQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryByAttributeSqlInTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryByAttributeSqlExistsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryByAttributeSqlNotExistsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryByManagedViewTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryByManagedViewWithUnionSqlTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToAssociationUpdateTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationSynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationSynchronousQueryByObjectIdsTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::largeOneToAssociationUpdateTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationSynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationSynchronousQueryByObjectIdsTestStep),

        //Testing of updateMultipleWaveManagedObjects using Update Context
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::updateAssociationWithUpdateContextTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationSynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationSynchronousQueryByObjectIdsTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::deleteAllCreatedObjects2TestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationSynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationSynchronousQueryByObjectIdsTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToAssociationTransactionTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationSynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationSynchronousQueryByObjectIdsTestStep),

        //Delete without loading objects in memory
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::deleteOneToOneAssociationWithDeletionContextTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationSynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationSynchronousQueryByObjectIdsTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToAssociationCanBeEmptyTransactionTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryUsingIsNullTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryUsingIsNotNullTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::deleteOneToOneAssociationWithDeletionContextTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::largeOneToAssociationTransactionTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationSynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationSynchronousQueryByObjectIdsTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::deleteAllCreatedObjects2TestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationSynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationSynchronousQueryByObjectIdsTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleDerivationTransactionTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleDerivationQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleDerivationQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleDerivationSynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleDerivationSynchronousQueryByObjectIdsTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::deleteAllCreatedObjects3TestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleDerivationQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleDerivationQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleDerivationSynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleDerivationSynchronousQueryByObjectIdsTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::largeDerivationTransactionTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleDerivationQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleDerivationQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleDerivationSynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleDerivationSynchronousQueryByObjectIdsTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::deleteAllCreatedObjects3TestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleDerivationQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleDerivationQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleDerivationSynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleDerivationSynchronousQueryByObjectIdsTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyAssociationTransactionTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyAssociationQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyAssociationQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyAssociationSynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationSynchronousQueryByObjectIdsTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyAssociationUpdateTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyAssociationQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyAssociationQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyAssociationSynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationSynchronousQueryByObjectIdsTestStep),

        //Delete without loading objects in memory
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::deleteOneToManyAssociationWithDeletionContextTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyAssociationQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyAssociationQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyAssociationSynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationSynchronousQueryByObjectIdsTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::deleteAllCreatedObjects4TestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyAssociationQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyAssociationQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyAssociationSynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationSynchronousQueryByObjectIdsTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::largeOneToManyAssociationTransactionTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyAssociationQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyAssociationQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyAssociationSynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationSynchronousQueryByObjectIdsTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::deleteAllCreatedObjects4TestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyAssociationQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyAssociationQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyAssociationSynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationSynchronousQueryByObjectIdsTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyMultipleAssociationsInHierarchyTransactionTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyMultipleAssociationsInHierarchyQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyMultipleAssociationsInHierarchyQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyMultipleAssociationsInHierarchySynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyMultipleAssociationsInHierarchySynchronousQueryByObjectIdsTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::deleteAllCreatedObjects5TestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyMultipleAssociationsInHierarchyQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyMultipleAssociationsInHierarchyQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyMultipleAssociationsInHierarchySynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyMultipleAssociationsInHierarchySynchronousQueryByObjectIdsTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::largeOneToManyMultipleAssociationsInHierarchyTransactionTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyMultipleAssociationsInHierarchyQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyMultipleAssociationsInHierarchyQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyMultipleAssociationsInHierarchySynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyMultipleAssociationsInHierarchySynchronousQueryByObjectIdsTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::deleteAllCreatedObjects5TestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyMultipleAssociationsInHierarchyQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyMultipleAssociationsInHierarchyQueryByObjectIdsTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyMultipleAssociationsInHierarchySynchronousQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyMultipleAssociationsInHierarchySynchronousQueryByObjectIdsTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneCompositionTransactionTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneCompositionQueryTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneCompositionUpdateTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneCompositionQueryTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::deleteAllCreatedObjects6TestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneCompositionQueryTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::largeOneToOneCompositionTransactionTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneCompositionQueryTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::deleteAllCreatedObjects6TestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneCompositionQueryTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneCompositionTransactionTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneCompositionQueryTestStep),

        //Delete without loading objects in memory
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::deleteOneToOneCompositionWithDeletionContextTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::deleteAllOneToOneCompositionUsingDeleteWaveManagedObjectWithObjectIdTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneCompositionQueryTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneCompositionTransactionTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneCompositionQueryTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::deleteAllOneToOneCompositionUsingDeleteWaveManagedObjectWithDeletionContextTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneCompositionQueryTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyCompositionTransactionTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyCompositionQueryTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyCompositionUpdateTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyCompositionQueryTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::deleteAllCreatedObjects7TestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyCompositionQueryTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::largeOneToManyCompositionTransactionTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyCompositionQueryTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::deleteAllCreatedObjects7TestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyCompositionQueryTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyCompositionTransactionTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyCompositionQueryTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::deleteAllOneToManyCompositionUsingDeleteWaveManagedObjectWithObjectIdTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyCompositionQueryTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyCompositionTransactionTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyCompositionQueryTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::deleteAllOneToManyCompositionUsingDeleteWaveManagedObjectWithDeletionContextTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyCompositionQueryTestStep),
        
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyCompositionTransactionTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyCompositionQueryTestStep),
        //Delete without loading objects in memory
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::deleteAllOneToManyCompositionUsingDeleteMultipleWaveManagedObjectsWithDeletionContextTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyCompositionQueryTestStep),
        
        //Delete without loading objects in memory
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneToOneCompositionTransactionTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneToOneCompositionQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneCompositionQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::deleteAllOneToOneToOneCompositionUsingDeleteMultipleWaveManagedObjectsWithDeletionContextTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneToOneCompositionQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToOneCompositionQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyToManyCompositionTransactionTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyToManyCompositionQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyCompositionQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleDerivationQueryTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::deleteAllOneToManyToManyCompositionUsingDeleteMultipleWaveManagedObjectsWithDeletionContextTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyToManyCompositionQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyCompositionQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleDerivationQueryTestStep),


        // Test off-memory (without loading into memory) deletion of compositions an MO or MOs, leaving the MO(s) as is.

        // Test setup - Create WaveTestManagedObject7 objects, each object containing
        // pWaveTestManagedObject1 objects as composition.
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleOneToManyCompositionTransactionTestStep),
        // Verify that test objects are properly created.
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryTestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::deleteManagedObjectCompositionsOneToManyTestStep),

        // Verify that test objects are proper.
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleQueryTestStep),
        // Test tear-down - cleanup the created WaveTestManagedObject7 objects.
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::deleteAllCreatedObjects7TestStep),

        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::waveLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::waveLinearSequencerFailedStep)
    };

    FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext = new FrameworkPersistenceTestContext (pFrameworkTestabilityMessage8, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pFrameworkPersistenceTestContext->start ();
   }
   else
   {
 
    WaveLinearSequencerStep sequencerSteps[] =
    {   
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleTransactionTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::simpleSynchronousPageQueryTestStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::deleteAllCreatedObjectsTestStep),
 
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::waveLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&FrameworkTestability4ObjectManager::waveLinearSequencerFailedStep)
    };
    FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext = new FrameworkPersistenceTestContext (pFrameworkTestabilityMessage8, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));
         pFrameworkPersistenceTestContext->start ();
   }
}

void FrameworkTestability4ObjectManager::simpleTransactionTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Transaction Test ...");

    FrameworkTestabilityMessage8             *pFrameworkTestabilityMessage8 = reinterpret_cast<FrameworkTestabilityMessage8 *> (pFrameworkPersistenceTestContext->getPWaveMessage ());
    ResourceId                                status                        = WAVE_MESSAGE_SUCCESS;
    UI32                                      numberOfObjectsToCreate       = pFrameworkTestabilityMessage8->getNumberOfObjectsToBeCreated ();
    UI32                                      i                             = 0;
    vector<WaveTestManagedObject1 *>        &allCreatedObjects             = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjectsMap          = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();

    pFrameworkPersistenceTestContext->setNumberOfObjectsToBeCreated (numberOfObjectsToCreate);

    for (i = 0; i < numberOfObjectsToCreate; i++)
    {
        startTransaction ();

        WaveTestManagedObject1 *pWaveTestManagedObject1 = new WaveTestManagedObject1 (this);

        pWaveTestManagedObject1->setInteger1 (i);
        pWaveTestManagedObject1->setMessage1 (string ("Wave's Test Case") + i);
        pWaveTestManagedObject1->setObjectId1 (ObjectId (i, i));

        allCreatedObjects.push_back (pWaveTestManagedObject1);
        allCreatedObjectsMap[pWaveTestManagedObject1->getObjectId ()] = pWaveTestManagedObject1;

        status = commitTransaction ();

        if (status != FRAMEWORK_SUCCESS)
        {
            trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::simpleTransactionTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
            break;
        }
        else
        {
            status = WAVE_MESSAGE_SUCCESS;
        }
    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleQueryTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Query Test ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject1::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleQueryTestCallback), pFrameworkPersistenceTestContext);

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults ((pFrameworkPersistenceTestContext->getCreatedObjects ()).size ());

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleQueryUsingEqualTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Query Using Equal Test ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject1::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleQueryTestCallback), pFrameworkPersistenceTestContext);

    // The equal condition operator is already used by default when the parameter is not specified
    pWaveManagedObjectQueryContext->addAndAttribute (new AttributeUI32 (1, "integer1"), WAVE_ATTRIBUTE_CONDITION_OPERATOR_EQUAL);

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults (1);

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleQueryUsingNotEqualTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Query Using Not Equal Test ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject1::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleQueryTestCallback), pFrameworkPersistenceTestContext);

    pWaveManagedObjectQueryContext->addOrAttribute  (new AttributeUI32 (1, "integer1"), WAVE_ATTRIBUTE_CONDITION_OPERATOR_NOT_EQUAL);

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults ( (((pFrameworkPersistenceTestContext->getCreatedObjects ()).size ()) - 1) );

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleQueryUsingGreaterThanTest1Step (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Query Using Greater Than Test 1 ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject1::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleQueryTestCallback), pFrameworkPersistenceTestContext);

    UI32 firstIndex  = 0;

    pWaveManagedObjectQueryContext->addAndAttribute (new AttributeUI32 (&firstIndex, "integer1"), WAVE_ATTRIBUTE_CONDITION_OPERATOR_GREATER_THAN);

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults ( (((pFrameworkPersistenceTestContext->getCreatedObjects ()).size ()) - 1) );

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleQueryUsingGreaterThanTest2Step (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Query Using Greater Than Test 2 ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject1::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleQueryTestCallback), pFrameworkPersistenceTestContext);

    UI32 lastIndex  = ((pFrameworkPersistenceTestContext->getCreatedObjects ()).size ()) - 1;

    pWaveManagedObjectQueryContext->addOrAttribute (new AttributeUI32 (&lastIndex, "integer1"), WAVE_ATTRIBUTE_CONDITION_OPERATOR_GREATER_THAN);

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults (0);

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleQueryUsingGreaterThanOrEqualToTest1Step (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Query Using Greater Than Or Equal To Test 1 ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject1::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleQueryTestCallback), pFrameworkPersistenceTestContext);

    UI32 firstIndex = 0;

    pWaveManagedObjectQueryContext->addAndAttribute (new AttributeUI32 (&firstIndex, "integer1"), WAVE_ATTRIBUTE_CONDITION_OPERATOR_GREATER_THAN_OR_EQUAL_TO);

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults ((pFrameworkPersistenceTestContext->getCreatedObjects ()).size ());

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleQueryUsingGreaterThanOrEqualToTest2Step (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Query Using Greater Than Or Equal To Test 2 ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject1::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleQueryTestCallback), pFrameworkPersistenceTestContext);

    UI32 lastIndex  = ((pFrameworkPersistenceTestContext->getCreatedObjects ()).size ()) - 1;

    pWaveManagedObjectQueryContext->addOrAttribute (new AttributeUI32 (&lastIndex, "integer1"), WAVE_ATTRIBUTE_CONDITION_OPERATOR_GREATER_THAN_OR_EQUAL_TO);

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults (1);

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleQueryUsingLessThanTest1Step (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Query Using Less Than Test 1 ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject1::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleQueryTestCallback), pFrameworkPersistenceTestContext);

    UI32 firstIndex = 0;

    pWaveManagedObjectQueryContext->addAndAttribute (new AttributeUI32 (&firstIndex, "integer1"), WAVE_ATTRIBUTE_CONDITION_OPERATOR_LESS_THAN);

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults (0);

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleQueryUsingLessThanTest2Step (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Query Using Less Than Test 2 ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject1::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleQueryTestCallback), pFrameworkPersistenceTestContext);

    UI32 lastIndex  = ((pFrameworkPersistenceTestContext->getCreatedObjects ()).size ()) - 1;

    pWaveManagedObjectQueryContext->addOrAttribute (new AttributeUI32 (&lastIndex, "integer1"), WAVE_ATTRIBUTE_CONDITION_OPERATOR_LESS_THAN);

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults ( ((pFrameworkPersistenceTestContext->getCreatedObjects ()).size () - 1) );

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleQueryUsingLessThanOrEqualToTest1Step (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Query Using Less Than Or Equal To Test 1 ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject1::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleQueryTestCallback), pFrameworkPersistenceTestContext);

    UI32 firstIndex = 0;

    pWaveManagedObjectQueryContext->addAndAttribute (new AttributeUI32 (&firstIndex, "integer1"), WAVE_ATTRIBUTE_CONDITION_OPERATOR_LESS_THAN_OR_EQUAL_TO);

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults (1);

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleQueryUsingLessThanOrEqualToTest2Step (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Query Using Less Than Or Equal To Test 2 ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject1::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleQueryTestCallback), pFrameworkPersistenceTestContext);

    UI32 lastIndex  = ((pFrameworkPersistenceTestContext->getCreatedObjects ()).size ()) - 1;

    pWaveManagedObjectQueryContext->addOrAttribute (new AttributeUI32 (&lastIndex, "integer1"), WAVE_ATTRIBUTE_CONDITION_OPERATOR_LESS_THAN_OR_EQUAL_TO);

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults ((pFrameworkPersistenceTestContext->getCreatedObjects ()).size ());

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleQueryUsingLikeTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Query Using Like Test ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject1::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleQueryTestCallback), pFrameworkPersistenceTestContext);

    // Pattern matching using the LIKE condition
    pWaveManagedObjectQueryContext->addAndAttribute (new AttributeString ("%Wave\'s%", "message1"), WAVE_ATTRIBUTE_CONDITION_OPERATOR_LIKE);

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults ((pFrameworkPersistenceTestContext->getCreatedObjects ()).size ());

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleQueryUsingNotLikeTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Query Using Not Like Test ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject1::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleQueryTestCallback), pFrameworkPersistenceTestContext);

    // Pattern matching using the NOT LIKE condition
    pWaveManagedObjectQueryContext->addOrAttribute (new AttributeString ("%Wave\'s%", "message1"), WAVE_ATTRIBUTE_CONDITION_OPERATOR_NOT_LIKE);

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults (0);

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleQueryUsingILikeTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Query Using ILike Test ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject1::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleQueryTestCallback), pFrameworkPersistenceTestContext);

    // Pattern matching using the case insensitive ILIKE condition
    pWaveManagedObjectQueryContext->addAndAttribute (new AttributeString ("%test case%", "message1"), WAVE_ATTRIBUTE_CONDITION_OPERATOR_ILIKE);

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults ((pFrameworkPersistenceTestContext->getCreatedObjects ()).size ());

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleQueryUsingNotILikeTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Query Using Not ILike Test ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject1::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleQueryTestCallback), pFrameworkPersistenceTestContext);

    // Pattern matching using the case insensitive NOT ILIKE condition
    pWaveManagedObjectQueryContext->addOrAttribute (new AttributeString ("%test case%", "message1"), WAVE_ATTRIBUTE_CONDITION_OPERATOR_NOT_ILIKE);

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults (0);

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleQueryTestCallback (WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext)
{
    FrameworkPersistenceTestContext          *pFrameworkPersistenceTestContext = reinterpret_cast<FrameworkPersistenceTestContext *> (pWaveManagedObjectQueryContext->getPCallerContext ());
    ResourceId                                status                           = pWaveManagedObjectQueryContext->getCompletionStatus ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjectsMap             = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::simpleQueryCallback : Simple Query test failed. Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        vector<WaveManagedObject *> *pResults = pWaveManagedObjectQueryContext->getPResults ();

        waveAssert (NULL != pResults, __FILE__, __LINE__);

        UI32 numberOfExpectedResults = pFrameworkPersistenceTestContext->getNumberOfExpectedResults ();
        UI32 numberOfResults = pResults->size ();
        UI32 i               = 0;

        if (numberOfExpectedResults != numberOfResults)
        {
            trace (TRACE_LEVEL_FATAL, string ("FrameworkTestability4ObjectManager::simpleQueryCallback : We did not get expected number of results.  Expected = ") + numberOfExpectedResults + string (", Obtained =  ") + numberOfResults);
            vector<WaveTestManagedObject1 *>          &allCreatedObjects       = pFrameworkPersistenceTestContext->getCreatedObjects ();
            UI32                                        numberOfObjectsCreated  = allCreatedObjects.size ();

            for (i = 0; i < numberOfObjectsCreated; i++)
            {
                startTransaction ();

                deleteWaveManagedObject (allCreatedObjects[i]->getObjectId ());

                status = commitTransaction ();

                if (status != FRAMEWORK_SUCCESS)
                {
                    trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::simpleQueryCallback : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
                    break;
                }
                else
                {
                    status = WAVE_MESSAGE_SUCCESS;
                }
            }

            allCreatedObjects.clear ();
            allCreatedObjectsMap.clear ();
        }
        else
        {
            trace (TRACE_LEVEL_DEVEL, string ("    Number of Results (asynchronously obtained) = ") + numberOfResults);

            for (i = 0; i < numberOfResults; i++)
            {
                WaveTestManagedObject1 *pWaveTestManagedObject1         = reinterpret_cast<WaveTestManagedObject1 *> ((*pResults)[i]);
                ObjectId                 oid                              = pWaveTestManagedObject1->getObjectId  ();
                UI32                     integer1                         = pWaveTestManagedObject1->getInteger1  ();
                string                   message1                         = pWaveTestManagedObject1->getMessage1  ();
                ObjectId                 objectId1                        = pWaveTestManagedObject1->getObjectId1 ();

                WaveTestManagedObject1 *pWaveTestManagedObject1Expected = allCreatedObjectsMap[oid];
                ObjectId                 oidExpected                      = pWaveTestManagedObject1Expected->getObjectId  ();
                UI32                     integer1Expected                 = pWaveTestManagedObject1Expected->getInteger1  ();
                string                   message1Expected                 = pWaveTestManagedObject1Expected->getMessage1  ();
                ObjectId                 objectId1Expected                = pWaveTestManagedObject1Expected->getObjectId1 ();

                //trace (TRACE_LEVEL_DEVEL, string ("        ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer1 + string (", ") + message1 + string (", ") + objectId1.getClassId () + string (", ") + objectId1.getInstanceId ());

                if ((*pWaveTestManagedObject1Expected) != (*pWaveTestManagedObject1))
                {
                    trace (TRACE_LEVEL_ERROR, string ("Got      : ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer1 + string (", ") + message1 + string (", ") + objectId1.getClassId () + string (", ") + objectId1.getInstanceId ());
                    trace (TRACE_LEVEL_ERROR, string ("Expected : ") + oidExpected.getClassId () + string (", ") + oidExpected.getInstanceId () + string (", ") + integer1Expected + string (", ") + message1Expected + string (", ") + objectId1Expected.getClassId () + string (", ") + objectId1Expected.getInstanceId ());
                    waveAssert (false, __FILE__, __LINE__);

                    status = WAVE_MESSAGE_ERROR;
                    break;
                }
            }

            if (WAVE_MESSAGE_SUCCESS == status)
            {
                trace (TRACE_LEVEL_DEVEL, "    All Queried results were successfully compared against expected values.");
            }
        }
    }

    delete pWaveManagedObjectQueryContext;

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleQueryByObjectIdsTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Query By ObjectIds Test ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject1::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleQueryTestCallback), pFrameworkPersistenceTestContext);

    // Now add the ObjectIds to the context so that the query gets only the requested objects.

    vector<WaveTestManagedObject1 *> &allCreatedObjects         = pFrameworkPersistenceTestContext->getCreatedObjects ();
    UI32                               numberOfObjectsCreated    = allCreatedObjects.size ();
    UI32                               numberOfObjectsToQueryFor = numberOfObjectsCreated > 100 ? 100 : numberOfObjectsCreated;
    UI32                               i                         = 0;

    for (i = 0; i < numberOfObjectsToQueryFor; i++)
    {
        pWaveManagedObjectQueryContext->addObjectId ((allCreatedObjects[i])->getObjectId ());
    }

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults (numberOfObjectsToQueryFor);;

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleQueryByAttributeTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Query By ATtributes Test ...");

    FrameworkTestabilityMessage8   *pFrameworkTestabilityMessage8   = reinterpret_cast<FrameworkTestabilityMessage8 *> (pFrameworkPersistenceTestContext->getPWaveMessage ());
    UI32                            numberOfObjectsToCreate         = pFrameworkTestabilityMessage8->getNumberOfObjectsToBeCreated ();
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject1::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleQueryTestCallback), pFrameworkPersistenceTestContext);

    if (0 < numberOfObjectsToCreate)
    {
        pWaveManagedObjectQueryContext->addAndAttribute (new AttributeUI32 (1, "integer1"));
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, "FrameworkTestability4ObjectManager::simpleQueryByAttributeTestStep : There must be at least one Object created for this test step to run.");
        waveAssert (false, __FILE__, __LINE__);
    }

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults (1);

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleQueryByAttributeRangeTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Query By Range");

    WaveManagedObjectSynchronousQueryContext synchronousQueryContext (WaveTestManagedObject1::getClassName ());

    UI32Range    range32("1,3-11,15,21-50");
    string       fieldNameToQuery  = "integer1";
    vector<UI32> rangeCount;

    range32.getUI32RangeVector (rangeCount);
    

    synchronousQueryContext.setAttributeRangeForQuery (new AttributeUI32Range (range32.toString (), fieldNameToQuery));

    vector<WaveManagedObject *> *pResults = querySynchronously (&synchronousQueryContext);

    UI32 numberOfResults = 0;

    if (NULL != pResults)
    {
        numberOfResults = pResults->size ();

        trace (TRACE_LEVEL_INFO, string ("SimpleQueryByRange: number of Object found : ") + numberOfResults);
    }

    for (UI32 i = 0; i < numberOfResults; i++)
    {
        delete ((*pResults)[i]);
    }

    delete pResults;


    WaveManagedObjectSynchronousQueryContext synchronousQueryContext1 (WaveTestManagedObject1::getClassName ());
    synchronousQueryContext1.setAttributeRangeForQuery (new AttributeUI32Range (range32.toString (), fieldNameToQuery));

    UI32 count = 0;

    // Test 1 Count on correct range integer with Query Context

    ResourceId queryStatus = querySynchronouslyForCount (&synchronousQueryContext1, count);

    if (WAVE_MESSAGE_SUCCESS != queryStatus)
    {
        trace (TRACE_LEVEL_ERROR, "Query Failed Reason : " + FrameworkToolKit::localize (queryStatus));
        pFrameworkPersistenceTestContext->executeNextStep (WAVE_MESSAGE_ERROR);
        return;
    }

    trace (TRACE_LEVEL_INFO, string ("SimpleQueryByRange: querySynchronouslyForCount = ") + count);

    // Test 2 Count on Managed Object

    UI32 countWaveTestManagedObject1 = 0;

    queryStatus = querySynchronouslyForCount (WaveTestManagedObject1::getClassName (), countWaveTestManagedObject1);

    if (WAVE_MESSAGE_SUCCESS != queryStatus)
    {
        trace (TRACE_LEVEL_ERROR, "Query Failed Reason : " + FrameworkToolKit::localize (queryStatus));
        pFrameworkPersistenceTestContext->executeNextStep (WAVE_MESSAGE_ERROR);
        return;
    }

    trace (TRACE_LEVEL_INFO, string ("SimpleQueryByRange: total Managed object created = ") + countWaveTestManagedObject1);

    // Test 3 Trying to get Count on non integer field in Managed Object for Range

    string fieldNameToQuery1 = "message1";
    UI32 countWaveTestManagedObject2 = 0;

    queryStatus = querySynchronouslyForCount (WaveTestManagedObject1::getClassName (), fieldNameToQuery1, range32.toString (), countWaveTestManagedObject2);

    if (WAVE_MESSAGE_ERROR_COUNT_QUERY_NOT_SUPPORTED_ON_NON_INTEGER_RANGE != queryStatus)
    {
        trace (TRACE_LEVEL_ERROR, "Query Failed Reason : " + FrameworkToolKit::localize (queryStatus));
        pFrameworkPersistenceTestContext->executeNextStep (WAVE_MESSAGE_ERROR);
        return;
    }
    
    if ((count != numberOfResults) || (count != rangeCount.size ()) || (countWaveTestManagedObject1 != pFrameworkPersistenceTestContext->getNumberOfObjectsToBeCreated ()))
    {
        trace (TRACE_LEVEL_INFO, string ("Count = ") + pFrameworkPersistenceTestContext->getNumberOfObjectsToBeCreated ());

        trace (TRACE_LEVEL_ERROR, "SimpleQueryByRange: Test Failed");

        pFrameworkPersistenceTestContext->executeNextStep (WAVE_MESSAGE_ERROR);
    }
    else
    {
        pFrameworkPersistenceTestContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
}

void FrameworkTestability4ObjectManager::simpleQueryByAttributeSqlBetweenTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Query using SQL BETWEEN Attribute Test ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject1::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleQueryTestCallback), pFrameworkPersistenceTestContext);

    pWaveManagedObjectQueryContext->addAndAttribute (new AttributeSqlBetween (new AttributeUI32 (1, "integer1"), new AttributeUI32 (10, "integer1")), WAVE_ATTRIBUTE_CONDITION_OPERATOR_BETWEEN);

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults (10);

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleQueryByAttributeSqlBetweenStringTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Query using SQL BETWEEN String Attribute Test ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject1::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleQueryTestCallback), pFrameworkPersistenceTestContext);

    pWaveManagedObjectQueryContext->addAndAttribute (new AttributeSqlBetween (new AttributeString ("Wave's Test Case1", "message1"), new AttributeString ("Wave's Test Case10", "message1")), WAVE_ATTRIBUTE_CONDITION_OPERATOR_BETWEEN);

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults (2);

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleQueryByAttributeSqlInTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Query using SQL IN Attribute Test ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject1::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleQueryTestCallback), pFrameworkPersistenceTestContext);

    vector<Attribute *> attributesForSqlIn;

    attributesForSqlIn.push_back (new AttributeUI32 (1, "integer1"));
    attributesForSqlIn.push_back (new AttributeUI32 (3, "integer1"));
    attributesForSqlIn.push_back (new AttributeUI32 (5, "integer1"));
    attributesForSqlIn.push_back (new AttributeUI32 (7, "integer1"));
    attributesForSqlIn.push_back (new AttributeUI32 (9, "integer1"));
    
    pWaveManagedObjectQueryContext->addOrAttribute (new AttributeSqlIn (attributesForSqlIn), WAVE_ATTRIBUTE_CONDITION_OPERATOR_IN);

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults (5);

    // Do not clean up attributeSqlIn as well as all other attributes added to it as it will be deleted after query is performed in query context's destructor.

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleQueryByAttributeSqlInStringTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Query using SQL IN Attribute String Test ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject1::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleQueryTestCallback), pFrameworkPersistenceTestContext);

    vector<Attribute *> attributesForSqlIn;

    attributesForSqlIn.push_back (new AttributeString ("Wave's Test Case1", "message1"));
    attributesForSqlIn.push_back (new AttributeString ("Wave's Test Case3", "message1"));
    attributesForSqlIn.push_back (new AttributeString ("Wave's Test Case5", "message1"));
    attributesForSqlIn.push_back (new AttributeString ("Wave's Test Case7", "message1"));
    attributesForSqlIn.push_back (new AttributeString ("Wave's Test Case9", "message1"));

    pWaveManagedObjectQueryContext->addOrAttribute (new AttributeSqlIn (attributesForSqlIn), WAVE_ATTRIBUTE_CONDITION_OPERATOR_IN);

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults (5);

    // Do not clean up attributeSqlIn as well as all other attributes added to it as it will be deleted after query is performed in query context's destructor.

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleQueryWithOneConditionSetTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Query With One Condition Set Test ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject1::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleQueryTestCallback), pFrameworkPersistenceTestContext);

    pWaveManagedObjectQueryContext->createConditionSet ("CS_ASYNC_BIST_1");

    pWaveManagedObjectQueryContext->addAttributeToConditionSet ("CS_ASYNC_BIST_1", new AttributeUI32 (1, "integer1"), WAVE_ATTRIBUTE_CONCATENATION_OPERATOR_AND, WAVE_ATTRIBUTE_CONDITION_OPERATOR_NOT_EQUAL);
    pWaveManagedObjectQueryContext->addAttributeToConditionSet ("CS_ASYNC_BIST_1", new AttributeUI32 (2, "integer1"), WAVE_ATTRIBUTE_CONCATENATION_OPERATOR_AND, WAVE_ATTRIBUTE_CONDITION_OPERATOR_GREATER_THAN_OR_EQUAL_TO);
    pWaveManagedObjectQueryContext->addAttributeToConditionSet ("CS_ASYNC_BIST_1", new AttributeUI32 (3, "integer1"), WAVE_ATTRIBUTE_CONCATENATION_OPERATOR_AND, WAVE_ATTRIBUTE_CONDITION_OPERATOR_LESS_THAN_OR_EQUAL_TO);

    pWaveManagedObjectQueryContext->combineConditionSets ("CS_ASYNC_BIST_1");

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults (2);

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleQueryWithTwoConditionSets1TestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Query With Two OR'ed Condition Sets Test ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject1::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleQueryTestCallback), pFrameworkPersistenceTestContext);

    pWaveManagedObjectQueryContext->createConditionSet ("CS_ASYNC_BIST_1");
    pWaveManagedObjectQueryContext->createConditionSet ("CS_ASYNC_BIST_2");

    pWaveManagedObjectQueryContext->addAttributeToConditionSet ("CS_ASYNC_BIST_1", new AttributeUI32 (3, "integer1"), WAVE_ATTRIBUTE_CONCATENATION_OPERATOR_OR, WAVE_ATTRIBUTE_CONDITION_OPERATOR_EQUAL);
    pWaveManagedObjectQueryContext->addAttributeToConditionSet ("CS_ASYNC_BIST_1", new AttributeUI32 (5, "integer1"), WAVE_ATTRIBUTE_CONCATENATION_OPERATOR_OR, WAVE_ATTRIBUTE_CONDITION_OPERATOR_EQUAL);
    pWaveManagedObjectQueryContext->addAttributeToConditionSet ("CS_ASYNC_BIST_1", new AttributeUI32 (7, "integer1"), WAVE_ATTRIBUTE_CONCATENATION_OPERATOR_OR, WAVE_ATTRIBUTE_CONDITION_OPERATOR_EQUAL);

    pWaveManagedObjectQueryContext->addAttributeToConditionSet ("CS_ASYNC_BIST_2", new AttributeUI32 (10, "integer1"), WAVE_ATTRIBUTE_CONCATENATION_OPERATOR_AND, WAVE_ATTRIBUTE_CONDITION_OPERATOR_GREATER_THAN);
    pWaveManagedObjectQueryContext->addAttributeToConditionSet ("CS_ASYNC_BIST_2", new AttributeUI32 (20, "integer1"), WAVE_ATTRIBUTE_CONCATENATION_OPERATOR_AND, WAVE_ATTRIBUTE_CONDITION_OPERATOR_LESS_THAN);

    pWaveManagedObjectQueryContext->combineConditionSets ("CS_ASYNC_BIST_1+CS_ASYNC_BIST_2");

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults (12);

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleQueryWithTwoConditionSets2TestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Query With Two AND'ed Condition Sets Test ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject1::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleQueryTestCallback), pFrameworkPersistenceTestContext);

    pWaveManagedObjectQueryContext->createConditionSet ("CS_ASYNC_BIST_1");
    pWaveManagedObjectQueryContext->createConditionSet ("CS_ASYNC_BIST_2");

    pWaveManagedObjectQueryContext->addAttributeToConditionSet ("CS_ASYNC_BIST_1", new AttributeUI32 (3, "integer1"), WAVE_ATTRIBUTE_CONCATENATION_OPERATOR_AND, WAVE_ATTRIBUTE_CONDITION_OPERATOR_NOT_EQUAL);
    pWaveManagedObjectQueryContext->addAttributeToConditionSet ("CS_ASYNC_BIST_1", new AttributeUI32 (5, "integer1"), WAVE_ATTRIBUTE_CONCATENATION_OPERATOR_AND, WAVE_ATTRIBUTE_CONDITION_OPERATOR_NOT_EQUAL);
    pWaveManagedObjectQueryContext->addAttributeToConditionSet ("CS_ASYNC_BIST_1", new AttributeUI32 (7, "integer1"), WAVE_ATTRIBUTE_CONCATENATION_OPERATOR_AND, WAVE_ATTRIBUTE_CONDITION_OPERATOR_NOT_EQUAL);

    pWaveManagedObjectQueryContext->addAttributeToConditionSet ("CS_ASYNC_BIST_2", new AttributeUI32 (1, "integer1"), WAVE_ATTRIBUTE_CONCATENATION_OPERATOR_AND, WAVE_ATTRIBUTE_CONDITION_OPERATOR_GREATER_THAN_OR_EQUAL_TO);
    pWaveManagedObjectQueryContext->addAttributeToConditionSet ("CS_ASYNC_BIST_2", new AttributeUI32 (10, "integer1"), WAVE_ATTRIBUTE_CONCATENATION_OPERATOR_AND, WAVE_ATTRIBUTE_CONDITION_OPERATOR_LESS_THAN_OR_EQUAL_TO);

    pWaveManagedObjectQueryContext->combineConditionSets ("CS_ASYNC_BIST_1*CS_ASYNC_BIST_2");
    
    pFrameworkPersistenceTestContext->setNumberOfExpectedResults (7);

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleQueryWithThreeConditionSetsTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Query With Three Condition Sets Test ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject1::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleQueryTestCallback), pFrameworkPersistenceTestContext);

    pWaveManagedObjectQueryContext->createConditionSet ("CS_ASYNC_BIST_A");
    pWaveManagedObjectQueryContext->createConditionSet ("CS_ASYNC_BIST_B");
    pWaveManagedObjectQueryContext->createConditionSet ("CS_ASYNC_BIST_C");

    pWaveManagedObjectQueryContext->addAttributeToConditionSet ("CS_ASYNC_BIST_A", new AttributeString  ("%Test%", "message1")  , WAVE_ATTRIBUTE_CONCATENATION_OPERATOR_AND, WAVE_ATTRIBUTE_CONDITION_OPERATOR_LIKE);
    pWaveManagedObjectQueryContext->addAttributeToConditionSet ("CS_ASYNC_BIST_A", new AttributeUI32    (10, "integer1")        , WAVE_ATTRIBUTE_CONCATENATION_OPERATOR_AND, WAVE_ATTRIBUTE_CONDITION_OPERATOR_LESS_THAN_OR_EQUAL_TO);

    pWaveManagedObjectQueryContext->addAttributeToConditionSet ("CS_ASYNC_BIST_B", new AttributeString  ("%CASE%", "message1") , WAVE_ATTRIBUTE_CONCATENATION_OPERATOR_AND, WAVE_ATTRIBUTE_CONDITION_OPERATOR_ILIKE);
    pWaveManagedObjectQueryContext->addAttributeToConditionSet ("CS_ASYNC_BIST_B", new AttributeUI32    (5, "integer1")         , WAVE_ATTRIBUTE_CONCATENATION_OPERATOR_AND, WAVE_ATTRIBUTE_CONDITION_OPERATOR_NOT_EQUAL);

    pWaveManagedObjectQueryContext->addAttributeToConditionSet ("CS_ASYNC_BIST_C", new AttributeString  ("%PatternA%", "message1")  , WAVE_ATTRIBUTE_CONCATENATION_OPERATOR_AND, WAVE_ATTRIBUTE_CONDITION_OPERATOR_NOT_LIKE);
    pWaveManagedObjectQueryContext->addAttributeToConditionSet ("CS_ASYNC_BIST_C", new AttributeString  ("%patternb%", "message1")  , WAVE_ATTRIBUTE_CONCATENATION_OPERATOR_AND, WAVE_ATTRIBUTE_CONDITION_OPERATOR_NOT_ILIKE);
    pWaveManagedObjectQueryContext->addAttributeToConditionSet ("CS_ASYNC_BIST_C", new AttributeUI32    (1, "integer1")             , WAVE_ATTRIBUTE_CONCATENATION_OPERATOR_AND, WAVE_ATTRIBUTE_CONDITION_OPERATOR_EQUAL);

    pWaveManagedObjectQueryContext->combineConditionSets ("CS_ASYNC_BIST_A*(CS_ASYNC_BIST_B+CS_ASYNC_BIST_C)");

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults (10);

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleSynchronousQueryTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Synchronous Query Test ...");
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjectsMap = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    vector<WaveManagedObject *>             *pResults             = querySynchronously (WaveTestManagedObject1::getClassName ());

    waveAssert (NULL != pResults, __FILE__, __LINE__);

    UI32       numberOfExpectedResults = (pFrameworkPersistenceTestContext->getCreatedObjects ()).size ();
    UI32       numberOfResults         = pResults->size ();
    UI32       i                       = 0;
    ResourceId status                  = WAVE_MESSAGE_SUCCESS;

    trace (TRACE_LEVEL_DEVEL, string ("    Number of Results (synchronously obtained) = ") + numberOfResults);

    if (numberOfExpectedResults != numberOfResults)
    {
        trace (TRACE_LEVEL_FATAL, string ("FrameworkTestability4ObjectManager::simpleSynchronousQueryTestStep : We did not get expected number of results.  Expected = ") + numberOfExpectedResults + string (", Obtained =  ") + numberOfResults);
        waveAssert (false, __FILE__, __LINE__);
        status = WAVE_MESSAGE_ERROR;
    }
    else
    {
        for (i = 0; i < numberOfResults; i++)
        {
            WaveTestManagedObject1 *pWaveTestManagedObject1         = dynamic_cast<WaveTestManagedObject1 *> ((*pResults)[i]);
            waveAssert (NULL != pWaveTestManagedObject1, __FILE__, __LINE__);
            ObjectId                 oid                              = pWaveTestManagedObject1->getObjectId  ();
            UI32                     integer1                         = pWaveTestManagedObject1->getInteger1  ();
            string                   message1                         = pWaveTestManagedObject1->getMessage1  ();
            ObjectId                 objectId1                        = pWaveTestManagedObject1->getObjectId1 ();

            WaveTestManagedObject1 *pWaveTestManagedObject1Expected = allCreatedObjectsMap[oid];
            ObjectId                 oidExpected                      = pWaveTestManagedObject1Expected->getObjectId  ();
            UI32                     integer1Expected                 = pWaveTestManagedObject1Expected->getInteger1  ();
            string                   message1Expected                 = pWaveTestManagedObject1Expected->getMessage1  ();
            ObjectId                 objectId1Expected                = pWaveTestManagedObject1Expected->getObjectId1 ();

            //trace (TRACE_LEVEL_DEVEL, string ("        ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer1 + string (", ") + message1 + string (", ") + objectId1.getClassId () + string (", ") + objectId1.getInstanceId ());

            if ((*pWaveTestManagedObject1Expected) != (*pWaveTestManagedObject1))
            {
                trace (TRACE_LEVEL_ERROR, string ("Got      : ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer1 + string (", ") + message1 + string (", ") + objectId1.getClassId () + string (", ") + objectId1.getInstanceId ());
                trace (TRACE_LEVEL_ERROR, string ("Expected : ") + oidExpected.getClassId () + string (", ") + oidExpected.getInstanceId () + string (", ") + integer1Expected + string (", ") + message1Expected + string (", ") + objectId1Expected.getClassId () + string (", ") + objectId1Expected.getInstanceId ());
                waveAssert (false, __FILE__, __LINE__);

                status = WAVE_MESSAGE_ERROR;
                break;
            }
        }

        if (WAVE_MESSAGE_SUCCESS == status)
        {
            trace (TRACE_LEVEL_DEVEL, "    All Queried results were successfully compared against expected values.");
        }
    }

    for (i = 0; i < numberOfResults; i++)
    {
        delete ((*pResults)[i]);
    }

    delete pResults;

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleSynchronousQueryByObjectIdsTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Synchronous Query By ObjectIds Test ...");

    // Now add the ObjectIds to the context so that the query gets only the requested objects.

    vector<WaveTestManagedObject1 *>        &allCreatedObjects        = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjectsMap     = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    UI32                                     numberOfObjectsCreated    = allCreatedObjects.size ();
    UI32                                     numberOfObjectsToQueryFor = numberOfObjectsCreated > 100 ? 100 : numberOfObjectsCreated;
    UI32                                     i                         = 0;
    vector<ObjectId>                         objectIds;

    for (i = 0; i < numberOfObjectsToQueryFor; i++)
    {
        objectIds.push_back ((allCreatedObjects[i])->getObjectId ());
    }

    vector<WaveManagedObject *> *pResults = querySynchronously (WaveTestManagedObject1::getClassName (), objectIds);

    waveAssert (NULL != pResults, __FILE__, __LINE__);

    UI32       numberOfExpectedResults = numberOfObjectsToQueryFor;
    UI32       numberOfResults         = pResults->size ();
    ResourceId status                  = WAVE_MESSAGE_SUCCESS;

    trace (TRACE_LEVEL_DEVEL, string ("    Number of Results (synchronously obtained) = ") + numberOfResults);

    if (numberOfExpectedResults != numberOfResults)
    {
        trace (TRACE_LEVEL_FATAL, string ("FrameworkTestability4ObjectManager::simpleSynchronousQueryByObjectIdsTestStep : We did not get expected number of results.  Expected = ") + numberOfExpectedResults + string (", Obtained =  ") + numberOfResults);
        waveAssert (false, __FILE__, __LINE__);
        status = WAVE_MESSAGE_ERROR;
    }
    else
    {
        for (i = 0; i < numberOfResults; i++)
        {
            WaveTestManagedObject1 *pWaveTestManagedObject1         = dynamic_cast<WaveTestManagedObject1 *> ((*pResults)[i]);
            waveAssert (NULL != pWaveTestManagedObject1, __FILE__, __LINE__);
            ObjectId                 oid                              = pWaveTestManagedObject1->getObjectId  ();
            UI32                     integer1                         = pWaveTestManagedObject1->getInteger1  ();
            string                   message1                         = pWaveTestManagedObject1->getMessage1  ();
            ObjectId                 objectId1                        = pWaveTestManagedObject1->getObjectId1 ();

            WaveTestManagedObject1 *pWaveTestManagedObject1Expected = allCreatedObjectsMap[oid];
            ObjectId                 oidExpected                      = pWaveTestManagedObject1Expected->getObjectId  ();
            UI32                     integer1Expected                 = pWaveTestManagedObject1Expected->getInteger1  ();
            string                   message1Expected                 = pWaveTestManagedObject1Expected->getMessage1  ();
            ObjectId                 objectId1Expected                = pWaveTestManagedObject1Expected->getObjectId1 ();

            //trace (TRACE_LEVEL_DEVEL, string ("        ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer1 + string (", ") + message1 + string (", ") + objectId1.getClassId () + string (", ") + objectId1.getInstanceId ());

            if ((*pWaveTestManagedObject1Expected) != (*pWaveTestManagedObject1))
            {
                trace (TRACE_LEVEL_ERROR, string ("Got      : ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer1 + string (", ") + message1 + string (", ") + objectId1.getClassId () + string (", ") + objectId1.getInstanceId ());
                trace (TRACE_LEVEL_ERROR, string ("Expected : ") + oidExpected.getClassId () + string (", ") + oidExpected.getInstanceId () + string (", ") + integer1Expected + string (", ") + message1Expected + string (", ") + objectId1Expected.getClassId () + string (", ") + objectId1Expected.getInstanceId ());
                waveAssert (false, __FILE__, __LINE__);

                status = WAVE_MESSAGE_ERROR;
                break;
            }
        }

        if (WAVE_MESSAGE_SUCCESS == status)
        {
            trace (TRACE_LEVEL_DEVEL, "    All Queried results were successfully compared against expected values.");
        }
    }

    for (i = 0; i < numberOfResults; i++)
    {
        delete ((*pResults)[i]);
    }

    delete pResults;

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleSynchronousQueryByObjectIdTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Synchronous Query By ObjectId (One At a Time) Test ...");

    // Now add the ObjectIds to the context so that the query gets only the requested objects.

    vector<WaveTestManagedObject1 *>        &allCreatedObjects     = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjectsMap  = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    UI32                                     numberOfObjectsCreated = allCreatedObjects.size ();
    UI32                                     i                      = 0;
    ResourceId                               status                 = WAVE_MESSAGE_SUCCESS;

    for (i = 0; i < numberOfObjectsCreated; i++)
    {
        WaveTestManagedObject1 *pWaveTestManagedObject1         = dynamic_cast<WaveTestManagedObject1 *> (queryManagedObject ((allCreatedObjects[i])->getObjectId ()));

        waveAssert (NULL != pWaveTestManagedObject1, __FILE__, __LINE__);

        ObjectId                 oid                              = pWaveTestManagedObject1->getObjectId  ();
        UI32                     integer1                         = pWaveTestManagedObject1->getInteger1  ();
        string                   message1                         = pWaveTestManagedObject1->getMessage1  ();
        ObjectId                 objectId1                        = pWaveTestManagedObject1->getObjectId1 ();

        WaveTestManagedObject1 *pWaveTestManagedObject1Expected = allCreatedObjectsMap[oid];

        waveAssert (NULL != pWaveTestManagedObject1Expected, __FILE__, __LINE__);

        ObjectId                 oidExpected                      = pWaveTestManagedObject1Expected->getObjectId  ();
        UI32                     integer1Expected                 = pWaveTestManagedObject1Expected->getInteger1  ();
        string                   message1Expected                 = pWaveTestManagedObject1Expected->getMessage1  ();
        ObjectId                 objectId1Expected                = pWaveTestManagedObject1Expected->getObjectId1 ();

        if ((*pWaveTestManagedObject1Expected) != (*pWaveTestManagedObject1))
        {
            trace (TRACE_LEVEL_ERROR, string ("Got      : ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer1 + string (", ") + message1 + string (", ") + objectId1.getClassId () + string (", ") + objectId1.getInstanceId ());
            trace (TRACE_LEVEL_ERROR, string ("Expected : ") + oidExpected.getClassId () + string (", ") + oidExpected.getInstanceId () + string (", ") + integer1Expected + string (", ") + message1Expected + string (", ") + objectId1Expected.getClassId () + string (", ") + objectId1Expected.getInstanceId ());
            waveAssert (false, __FILE__, __LINE__);

            status = WAVE_MESSAGE_ERROR;
            break;
        }

        delete pWaveTestManagedObject1;
    }

    if (WAVE_MESSAGE_SUCCESS == status)
    {
        trace (TRACE_LEVEL_DEVEL, "    All Queried results were successfully compared against expected values.");
    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleSynchronousQueryWithConditionSetsTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Synchronous Query With Condition Sets Test ...");

    map<ObjectId, WaveTestManagedObject1 *>   &allCreatedObjectsMap    = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();

    WaveManagedObjectSynchronousQueryContext synchronousQueryContext (WaveTestManagedObject1::getClassName ());

    synchronousQueryContext.createConditionSet ("CS_BIST_1");
    synchronousQueryContext.createConditionSet ("CS_BIST_2");

    synchronousQueryContext.addAttributeToConditionSet ("CS_BIST_1", new AttributeUI32 (1, "integer1"), WAVE_ATTRIBUTE_CONCATENATION_OPERATOR_OR, WAVE_ATTRIBUTE_CONDITION_OPERATOR_EQUAL);
    synchronousQueryContext.addAttributeToConditionSet ("CS_BIST_1", new AttributeUI32 (2, "integer1"), WAVE_ATTRIBUTE_CONCATENATION_OPERATOR_OR, WAVE_ATTRIBUTE_CONDITION_OPERATOR_EQUAL);
    synchronousQueryContext.addAttributeToConditionSet ("CS_BIST_2", new AttributeUI32 (10, "integer1"), WAVE_ATTRIBUTE_CONCATENATION_OPERATOR_AND, WAVE_ATTRIBUTE_CONDITION_OPERATOR_GREATER_THAN);
    synchronousQueryContext.addAttributeToConditionSet ("CS_BIST_2", new AttributeUI32 (20, "integer1"), WAVE_ATTRIBUTE_CONCATENATION_OPERATOR_AND, WAVE_ATTRIBUTE_CONDITION_OPERATOR_LESS_THAN);

    synchronousQueryContext.combineConditionSets ("CS_BIST_1+CS_BIST_2");

    vector<WaveManagedObject *>                *pResults                = querySynchronously (&synchronousQueryContext);

    waveAssert (NULL != pResults, __FILE__, __LINE__);

    UI32       numberOfExpectedResults = 11;
    UI32       numberOfResults         = pResults->size ();
    UI32       i                       = 0;
    ResourceId status                  = WAVE_MESSAGE_SUCCESS;

    trace (TRACE_LEVEL_DEVEL, string ("    Number of Results (synchronously obtained) = ") + numberOfResults);

    if (numberOfExpectedResults != numberOfResults)
    {
        trace (TRACE_LEVEL_FATAL, string ("FrameworkTestability4ObjectManager::simpleSynchronousQueryTestStep : We did not get expected number of results.  Expected = ") + numberOfExpectedResults + string (", Obtained =  ") + numberOfResults);
        waveAssert (false, __FILE__, __LINE__);
        status = WAVE_MESSAGE_ERROR;
    }
    else
    {
        for (i = 0; i < numberOfResults; i++)
        {
            WaveTestManagedObject1 *pWaveTestManagedObject1         = dynamic_cast<WaveTestManagedObject1 *> ((*pResults)[i]);
            waveAssert (NULL != pWaveTestManagedObject1, __FILE__, __LINE__);
            ObjectId                 oid                              = pWaveTestManagedObject1->getObjectId  ();
            UI32                     integer1                         = pWaveTestManagedObject1->getInteger1  ();
            string                   message1                         = pWaveTestManagedObject1->getMessage1  ();
            ObjectId                 objectId1                        = pWaveTestManagedObject1->getObjectId1 ();

            WaveTestManagedObject1 *pWaveTestManagedObject1Expected = allCreatedObjectsMap[oid];
            ObjectId                 oidExpected                      = pWaveTestManagedObject1Expected->getObjectId  ();
            UI32                     integer1Expected                 = pWaveTestManagedObject1Expected->getInteger1  ();
            string                   message1Expected                 = pWaveTestManagedObject1Expected->getMessage1  ();
            ObjectId                 objectId1Expected                = pWaveTestManagedObject1Expected->getObjectId1 ();

            //trace (TRACE_LEVEL_DEVEL, string ("        ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer1 + string (", ") + message1 + string (", ") + objectId1.getClassId () + string (", ") + objectId1.getInstanceId ());

            if ((*pWaveTestManagedObject1Expected) != (*pWaveTestManagedObject1))
            {
                trace (TRACE_LEVEL_ERROR, string ("Got      : ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer1 + string (", ") + message1 + string (", ") + objectId1.getClassId () + string (", ") + objectId1.getInstanceId ());
                trace (TRACE_LEVEL_ERROR, string ("Expected : ") + oidExpected.getClassId () + string (", ") + oidExpected.getInstanceId () + string (", ") + integer1Expected + string (", ") + message1Expected + string (", ") + objectId1Expected.getClassId () + string (", ") + objectId1Expected.getInstanceId ());
                waveAssert (false, __FILE__, __LINE__);

                status = WAVE_MESSAGE_ERROR;
                break;
            }
        }

        if (WAVE_MESSAGE_SUCCESS == status)
        {
            trace (TRACE_LEVEL_DEVEL, "    All Queried results were successfully compared against expected values.");
        }
    }

    for (i = 0; i < numberOfResults; i++)
    {
        delete ((*pResults)[i]);
    }

    delete pResults;

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleUpdateTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Update Transaction Test ...");

    ResourceId                         status                        = WAVE_MESSAGE_SUCCESS;
    UI32                               i                             = 0;
    vector<WaveTestManagedObject1 *> &allCreatedObjects             = pFrameworkPersistenceTestContext->getCreatedObjects ();
    UI32                               numberOfObjectsCreated        = allCreatedObjects.size ();

    for (i = 0; i < numberOfObjectsCreated; i++)
    {
        startTransaction ();

        updateWaveManagedObject (allCreatedObjects[i]);

        allCreatedObjects[i]->setInteger1 (1000 + i);
        allCreatedObjects[i]->setMessage1 ("Waves's Simple Update's Test Cases");
        allCreatedObjects[i]->setObjectId1 (ObjectId (1000 + i, 1000 + i));

        status = commitTransaction ();

        if (status != FRAMEWORK_SUCCESS)
        {
            trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::simpleUpdateTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
            break;
        }
        else
        {
            status = WAVE_MESSAGE_SUCCESS;
        }
    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simplePartialUpdateTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Partial Update Transaction Test ...");

    ResourceId                         status                        = WAVE_MESSAGE_SUCCESS;
    UI32                               i                             = 0;
    vector<WaveTestManagedObject1 *> &allCreatedObjects             = pFrameworkPersistenceTestContext->getCreatedObjects ();
    UI32                               numberOfObjectsCreated        = allCreatedObjects.size ();
    vector<string>                     attributesToBeUpdated;

    attributesToBeUpdated.push_back ("integer1");
    attributesToBeUpdated.push_back ("message1");
    attributesToBeUpdated.push_back ("objectId1");

    for (i = 0; i < numberOfObjectsCreated; i++)
    {
        startTransaction ();

        updateWaveManagedObject (allCreatedObjects[i]);

        allCreatedObjects[i]->setInteger1 (2000 + i);
        allCreatedObjects[i]->setMessage1 ("Waves's Simple Partial Update's Test Cases");
        allCreatedObjects[i]->setObjectId1 (ObjectId (2000 + i, 2000 + i));

        allCreatedObjects[i]->setAttributesToBeUpdated (attributesToBeUpdated);

        status = commitTransaction ();

        if (status != FRAMEWORK_SUCCESS)
        {
            trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::simplePartialUpdateTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
            break;
        }
        else
        {
            status = WAVE_MESSAGE_SUCCESS;
        }
    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simplePartialIncrementalUpdateTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Partial Incremental Update Transaction Test ...");

    ResourceId                         status                        = WAVE_MESSAGE_SUCCESS;
    UI32                               i                             = 0;
    vector<WaveTestManagedObject1 *> &allCreatedObjects             = pFrameworkPersistenceTestContext->getCreatedObjects ();
    UI32                               numberOfObjectsCreated        = allCreatedObjects.size ();

    for (i = 0; i < numberOfObjectsCreated; i++)
    {
        startTransaction ();

        updateWaveManagedObject (allCreatedObjects[i]);

        allCreatedObjects[i]->setAttributesToBeUpdated (vector<string> ());

        allCreatedObjects[i]->setInteger1 (3000 + i);
        allCreatedObjects[i]->addAttributeToBeUpdated ("integer1");
        allCreatedObjects[i]->setMessage1 ("Waves's Simple Partial Incremental Update's Test Cases");
        allCreatedObjects[i]->addAttributeToBeUpdated ("message1");
        allCreatedObjects[i]->setObjectId1 (ObjectId (3000 + i, 3000 + i));
        allCreatedObjects[i]->addAttributeToBeUpdated ("objectId1");

        status = commitTransaction ();

        if (status != FRAMEWORK_SUCCESS)
        {
            trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::simplePartialIncrementalUpdateTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
            break;
        }
        else
        {
            status = WAVE_MESSAGE_SUCCESS;
        }
    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::largeUpdateTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Large Update Transaction Test ...");

    ResourceId                         status                        = WAVE_MESSAGE_SUCCESS;
    UI32                               i                             = 0;
    vector<WaveTestManagedObject1 *> &allCreatedObjects             = pFrameworkPersistenceTestContext->getCreatedObjects ();
    UI32                               numberOfObjectsCreated        = allCreatedObjects.size ();

    startTransaction ();

    for (i = 0; i < numberOfObjectsCreated; i++)
    {
        updateWaveManagedObject (allCreatedObjects[i]);

        allCreatedObjects[i]->clearAttributesToBeUpdated ();

        allCreatedObjects[i]->setInteger1 (2000 + i);
        allCreatedObjects[i]->setMessage1 ("Test Simple Update");
    }

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::largeUpdateTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

//Testing of updateMultipleWaveManagedObjects using update Context
void FrameworkTestability4ObjectManager::updateAllRowsWithUpdateContextTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Update All Rows With Update Context Transaction Test ...");

    ResourceId                         status                        = WAVE_MESSAGE_SUCCESS;
    UI32                               i                             = 0;
    vector<WaveTestManagedObject1 *> &allCreatedObjects             = pFrameworkPersistenceTestContext->getCreatedObjects ();
    UI32                               numberOfObjectsCreated        = allCreatedObjects.size ();

    for (i = 0; i < numberOfObjectsCreated; i++)
    {
        allCreatedObjects[i]->setInteger1 (1000);
        allCreatedObjects[i]->setMessage1 ("Waves's Update All Rows With Update Context's Test Cases");
        allCreatedObjects[i]->setObjectId1 (ObjectId (1000, 1000));
    }

    startTransaction ();

    WaveManagedObjectSynchronousQueryContextForUpdate *syncQueryCtxt = new WaveManagedObjectSynchronousQueryContextForUpdate (WaveTestManagedObject1::getClassName ());
    WaveManagedObject *waveManagedObject = syncQueryCtxt->getWaveManagedObjectToAddUpdateAttributes ();
    WaveTestManagedObject1 *pWaveTestManagedObject = dynamic_cast<WaveTestManagedObject1 *>  (waveManagedObject);

    pWaveTestManagedObject->setInteger1 (1000);
    pWaveTestManagedObject->setMessage1 ("Waves's Update All Rows With Update Context's Test Cases");
    pWaveTestManagedObject->setObjectId1 (ObjectId (1000, 1000));

    pWaveTestManagedObject->addAttributeToBeUpdated ("integer1");
    pWaveTestManagedObject->addAttributeToBeUpdated ("message1");
    pWaveTestManagedObject->addAttributeToBeUpdated ("objectId1");

    updateMultipleWaveManagedObjects (syncQueryCtxt);

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::updateAllRowsWithUpdateContextTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::partialUpdateAllRowsWithUpdateContextTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Partial Update All Rows With Update Context Transaction Test ...");

    ResourceId                         status                        = WAVE_MESSAGE_SUCCESS;
    UI32                               i                             = 0;
    vector<WaveTestManagedObject1 *> &allCreatedObjects             = pFrameworkPersistenceTestContext->getCreatedObjects ();
    UI32                               numberOfObjectsCreated        = allCreatedObjects.size ();
    vector<string>                     attributesToBeUpdated;

    attributesToBeUpdated.push_back ("integer1");
    attributesToBeUpdated.push_back ("message1");

    for (i = 0; i < numberOfObjectsCreated; i++)
    {
        allCreatedObjects[i]->setInteger1 (2000);
        allCreatedObjects[i]->setMessage1 ("Waves's Partial Update All Rows With Update Context's Test Cases");
    }

    startTransaction ();

    WaveManagedObjectSynchronousQueryContextForUpdate *syncQueryCtxt = new WaveManagedObjectSynchronousQueryContextForUpdate (WaveTestManagedObject1::getClassName ());
    WaveManagedObject *waveManagedObject = syncQueryCtxt->getWaveManagedObjectToAddUpdateAttributes ();
    WaveTestManagedObject1 *pWaveTestManagedObject = dynamic_cast<WaveTestManagedObject1 *> (waveManagedObject);

    pWaveTestManagedObject->setInteger1 (2000);
    pWaveTestManagedObject->setMessage1 ("Waves's Partial Update All Rows With Update Context's Test Cases");

    pWaveTestManagedObject->setAttributesToBeUpdated (attributesToBeUpdated);

    updateMultipleWaveManagedObjects (syncQueryCtxt);

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::partialUpdateAllRowsWithUpdateContextTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::updateFewRowsWithUpdateContextTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Update Few Rows With Update Context Transaction Test ...");

    ResourceId                         status                        = WAVE_MESSAGE_SUCCESS;
    UI32                               i                             = 0;
    vector<WaveTestManagedObject1 *> &allCreatedObjects             = pFrameworkPersistenceTestContext->getCreatedObjects ();
    UI32                               numberOfObjectsCreated        = allCreatedObjects.size ();
    vector<string>                     attributesToBeUpdated;

    startTransaction ();
    // Set Integer to 2000 for all objects except last one
    for (i = 0; i < numberOfObjectsCreated - 1; i++)
    {
        updateWaveManagedObject (allCreatedObjects[i]);

        allCreatedObjects[i]->setInteger1 (2000);
        allCreatedObjects[i]->setMessage1 ("Waves's Update Few Rows With Update Context's Test Cases");
        allCreatedObjects[i]->setObjectId1 (ObjectId (1000, 1000));

    }
    //Set Last rows's Integer to 2001
    updateWaveManagedObject (allCreatedObjects[numberOfObjectsCreated - 1]);
    allCreatedObjects[numberOfObjectsCreated - 1]->setInteger1 (2001);
    allCreatedObjects[numberOfObjectsCreated - 1]->setMessage1 ("Waves's Update Few Rows With Update Context's Test Cases - Last row");

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::updateFewRowsWithUpdateContextTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
        pFrameworkPersistenceTestContext->executeNextStep (status);
        return;
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }

    // Now update using UpdateContext
    for (i = 0; i < numberOfObjectsCreated - 1; i++)
    {
        allCreatedObjects[i]->setMessage1 ("UPDATED:Waves's Update Few Rows With Update Context's Test Cases");
    }

    startTransaction ();
    // Update all rows expect the last one by setting the WHERE condition as below
    WaveManagedObjectSynchronousQueryContextForUpdate *syncQueryCtxt = new WaveManagedObjectSynchronousQueryContextForUpdate (WaveTestManagedObject1::getClassName ());
    WaveManagedObject *waveManagedObject = syncQueryCtxt->getWaveManagedObjectToAddUpdateAttributes ();
    UI32 integer = 2000;
    // Sets WHERE interger1=2000 in the SQL UPDATE query.
    syncQueryCtxt->addAndAttribute (new AttributeUI32 (&integer,"integer1"));

    WaveTestManagedObject1 *pWaveTestManagedObject = dynamic_cast<WaveTestManagedObject1 *> (waveManagedObject);

    pWaveTestManagedObject->setMessage1 ("UPDATED:Waves's Update Few Rows With Update Context's Test Cases");

    pWaveTestManagedObject->addAttributeToBeUpdated ("message1");

    updateMultipleWaveManagedObjects (syncQueryCtxt);

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::updateFewRowsWithUpdateContextTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::deleteAllUsingDeleteWaveManagedObjectWithObjectIdTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Delete All Using Delete Wave Managed Object With Object Id Test ...");

    ResourceId                                  status                  = WAVE_MESSAGE_SUCCESS;
    UI32                                        i                       = 0;
    vector<WaveTestManagedObject1 *>          &allCreatedObjects       = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *>   &allCreatedObjectsMap    = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    UI32                                        numberOfObjectsCreated  = allCreatedObjects.size ();

    for (i = 0; i < numberOfObjectsCreated; i++)
    {
        startTransaction ();

        deleteWaveManagedObject (allCreatedObjects[i]->getObjectId ());

        status = commitTransaction ();

        if (status != FRAMEWORK_SUCCESS)
        {
            trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::deleteAllUsingDeleteWaveManagedObjectWithObjectIdTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
            break;
        }
        else
        {
            status = WAVE_MESSAGE_SUCCESS;
        }
    }

    allCreatedObjects.clear ();
    allCreatedObjectsMap.clear ();

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::deleteAllUsingDeleteWaveManagedObjectWithDeletionContextTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Delete All Using Delete Wave Managed Object With Deletion Context Test ...");

    ResourceId                                  status                  = WAVE_MESSAGE_SUCCESS;
    vector<WaveTestManagedObject1 *>          &allCreatedObjects       = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *>   &allCreatedObjectsMap    = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();

    WaveManagedObjectSynchronousQueryContextForDeletion synchronousQueryContextForDeletion (WaveTestManagedObject1::getClassName ());

    synchronousQueryContextForDeletion.addAndAttribute (new AttributeString ("%Test%", "message1"), "LIKE");

    startTransaction ();

    deleteWaveManagedObject (&synchronousQueryContextForDeletion);

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::deleteAllUsingDeleteWaveManagedObjectWithDeletionContextTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }

    allCreatedObjects.clear ();
    allCreatedObjectsMap.clear ();

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::deleteAllCreatedObjectsTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Delete All Created Objects Transaction Test ...");

    ResourceId                                status                 = WAVE_MESSAGE_SUCCESS;
    UI32                                      i                      = 0;
    vector<WaveTestManagedObject1 *>        &allCreatedObjects      = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjectsMap   = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    UI32                                      numberOfObjectsCreated = allCreatedObjects.size ();

    startTransaction ();

    for (i = 0; i < numberOfObjectsCreated; i++)
    {
        delete allCreatedObjects[i];
    }

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::deleteAllCreatedObjectsTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }

    allCreatedObjects.clear ();
    allCreatedObjectsMap.clear ();

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::largeTransactionTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Large Transaction Test ...");

    FrameworkTestabilityMessage8             *pFrameworkTestabilityMessage8 = reinterpret_cast<FrameworkTestabilityMessage8 *> (pFrameworkPersistenceTestContext->getPWaveMessage ());
    ResourceId                                status                        = WAVE_MESSAGE_SUCCESS;
    UI32                                      numberOfObjectsToCreate       = pFrameworkTestabilityMessage8->getNumberOfObjectsToBeCreated ();
    UI32                                      i                             = 0;
    vector<WaveTestManagedObject1 *>        &allCreatedObjects             = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjectsMap          = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();

    startTransaction ();

    for (i = 0; i < numberOfObjectsToCreate; i++)
    {
        WaveTestManagedObject1 *pWaveTestManagedObject1 = new WaveTestManagedObject1 (this);

        pWaveTestManagedObject1->setInteger1 (i);
        pWaveTestManagedObject1->setMessage1 ("Test");
        pWaveTestManagedObject1->setObjectId1 (ObjectId (i, i));

        allCreatedObjects.push_back (pWaveTestManagedObject1);
        allCreatedObjectsMap[pWaveTestManagedObject1->getObjectId ()] = pWaveTestManagedObject1;
    }

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::largeTransactionTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleOneToAssociationTransactionTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-One Association Transaction Test ...");

    FrameworkTestabilityMessage8             *pFrameworkTestabilityMessage8 = reinterpret_cast<FrameworkTestabilityMessage8 *> (pFrameworkPersistenceTestContext->getPWaveMessage ());
    ResourceId                                status                        = WAVE_MESSAGE_SUCCESS;
    UI32                                      numberOfObjectsToCreate       = pFrameworkTestabilityMessage8->getNumberOfObjectsToBeCreated ();
    UI32                                      i                             = 0;
    vector<WaveTestManagedObject1 *>        &allCreatedObjects             = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjects1Map         = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    vector<WaveTestManagedObject2 *>        &allCreatedObjects2            = pFrameworkPersistenceTestContext->getCreatedObjects2 ();
    map<ObjectId, WaveTestManagedObject2 *> &allCreatedObjects2Map         = pFrameworkPersistenceTestContext->getCreatedObjects2Map ();

    for (i = 0; i < numberOfObjectsToCreate; i++)
    {
        startTransaction ();

        WaveTestManagedObject1 *pWaveTestManagedObject1 = new WaveTestManagedObject1 (this);
        WaveTestManagedObject2 *pWaveTestManagedObject2 = new WaveTestManagedObject2 (this);

        pWaveTestManagedObject1->setInteger1 (i);
        pWaveTestManagedObject1->setMessage1 ("Test");
        pWaveTestManagedObject1->setObjectId1 (ObjectId (i, i));

        pWaveTestManagedObject2->setInteger2 (i);
        pWaveTestManagedObject2->setMessage2 ("Test");
        pWaveTestManagedObject2->setObjectId2 (ObjectId (i, i));
        pWaveTestManagedObject2->setAssociation2 (pWaveTestManagedObject1->getObjectId ());

        allCreatedObjects.push_back (pWaveTestManagedObject1);
        allCreatedObjects1Map[pWaveTestManagedObject1->getObjectId ()] = pWaveTestManagedObject1;
        allCreatedObjects2.push_back (pWaveTestManagedObject2);
        allCreatedObjects2Map[pWaveTestManagedObject2->getObjectId ()] = pWaveTestManagedObject2;

        status = commitTransaction ();

        if (status != FRAMEWORK_SUCCESS)
        {
            trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::simpleOneToAssociationTransactionTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
            break;
        }
        else
        {
            status = WAVE_MESSAGE_SUCCESS;
        }
    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleOneToAssociationCanBeEmptyTransactionTestStep(FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-One Association Can Be Empty Transaction Test ...");

    FrameworkTestabilityMessage8             *pFrameworkTestabilityMessage8 = reinterpret_cast<FrameworkTestabilityMessage8 *> (pFrameworkPersistenceTestContext->getPWaveMessage ());
    ResourceId                                status                        = WAVE_MESSAGE_SUCCESS;
    UI32                                      numberOfObjectsToCreate       = pFrameworkTestabilityMessage8->getNumberOfObjectsToBeCreated ();
    UI32                                      i                             = 0;
    vector<WaveTestManagedObject1 *>        &allCreatedObjects             = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjects1Map         = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    vector<WaveTestManagedObject2 *>        &allCreatedObjects2            = pFrameworkPersistenceTestContext->getCreatedObjects2 ();
    map<ObjectId, WaveTestManagedObject2 *> &allCreatedObjects2Map         = pFrameworkPersistenceTestContext->getCreatedObjects2Map ();

    for (i = 0; i < numberOfObjectsToCreate; i++)
    {
        startTransaction ();

        WaveTestManagedObject1 *pWaveTestManagedObject1;
        if (i != numberOfObjectsToCreate - 1)
        {
            pWaveTestManagedObject1 = new WaveTestManagedObject1 (this);

            pWaveTestManagedObject1->setInteger1 (i);
            pWaveTestManagedObject1->setMessage1 ("Test");
            pWaveTestManagedObject1->setObjectId1 (ObjectId (i, i));
        }

        WaveTestManagedObject2 *pWaveTestManagedObject2 = new WaveTestManagedObject2 (this);

        pWaveTestManagedObject2->setInteger2 (i);
        pWaveTestManagedObject2->setMessage2 ("Test");
        pWaveTestManagedObject2->setObjectId2 (ObjectId (i, i));
        if (i != numberOfObjectsToCreate - 1)
        {
            pWaveTestManagedObject2->setAssociation2 (pWaveTestManagedObject1->getObjectId ());

            allCreatedObjects.push_back (pWaveTestManagedObject1);
            allCreatedObjects1Map[pWaveTestManagedObject1->getObjectId ()] = pWaveTestManagedObject1;
        }
        allCreatedObjects2.push_back (pWaveTestManagedObject2);
        allCreatedObjects2Map[pWaveTestManagedObject2->getObjectId ()] = pWaveTestManagedObject2;

        status = commitTransaction ();

        if (status != FRAMEWORK_SUCCESS)
        {
            trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::simpleOneToAssociationCanBeEmptyTransactionTestStep: Transaction failed.  Status : " + FrameworkToolKit::localize (status));
            break;
        }
        else
        {
            status = WAVE_MESSAGE_SUCCESS;
        }
    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryUsingIsNullTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-One Association Query Test ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject2::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryTestCallback), pFrameworkPersistenceTestContext);

    ObjectId m_association2;
    pWaveManagedObjectQueryContext->addAndAttribute (new AttributeObjectIdAssociation (&m_association2, "association2", WaveTestManagedObject1::getClassName ()), WAVE_ATTRIBUTE_CONDITION_OPERATOR_IS_NULL);
    pFrameworkPersistenceTestContext->setNumberOfExpectedResults (1);

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryUsingIsNotNullTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-One Association Query Test ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject2::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryTestCallback), pFrameworkPersistenceTestContext);

    ObjectId m_association2;
    pWaveManagedObjectQueryContext->addAndAttribute (new AttributeObjectIdAssociation (&m_association2, "association2", WaveTestManagedObject1::getClassName ()), WAVE_ATTRIBUTE_CONDITION_OPERATOR_IS_NOT_NULL);
    pFrameworkPersistenceTestContext->setNumberOfExpectedResults ((pFrameworkPersistenceTestContext->getCreatedObjects2 ()).size () - 1);

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryByManagedViewTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-One Association Query By Managed View...");
    FrameworkTestabilityMessage8             *pFrameworkTestabilityMessage8 = reinterpret_cast<FrameworkTestabilityMessage8 *> (pFrameworkPersistenceTestContext->getPWaveMessage ());
    ResourceId                                status                        = WAVE_MESSAGE_SUCCESS;
    UI32                                      numberOfObjectsToCreate       = pFrameworkTestabilityMessage8->getNumberOfObjectsToBeCreated ();

    WaveManagedObjectSynchronousQueryContext *pWaveManagedObjectSynchronousQueryContext = new WaveManagedObjectSynchronousQueryContext (WaveTestManagedView1::getClassName ());
    vector<WaveManagedObject *> *pResults = querySynchronously (pWaveManagedObjectSynchronousQueryContext);

    delete pWaveManagedObjectSynchronousQueryContext;

    if ( (*(pResults)).size () != numberOfObjectsToCreate)
    {
        status = WAVE_MESSAGE_ERROR;
    }

    UI32 numberOfResults = pResults->size ();
    UI32 i               = 0;
    for (i = 0; i < numberOfResults; i++)
    {
        WaveTestManagedView1 *pWaveTestManagedView1 = dynamic_cast<WaveTestManagedView1 *> ((*pResults)[i]);
        waveAssert (NULL != pWaveTestManagedView1, __FILE__, __LINE__);
        UI32                     integer1                         = pWaveTestManagedView1->getInteger1  ();
        string                   message1                         = pWaveTestManagedView1->getMessage1  ();

        trace (TRACE_LEVEL_DEBUG, string ("Got      : ") + integer1 + string (", ") + message1 );

        delete pWaveTestManagedView1;
    }
    pFrameworkPersistenceTestContext->executeNextStep (status);
    
}

void FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryByManagedViewWithUnionSqlTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-One Association Query By Managed View With Union support Test...");
    FrameworkTestabilityMessage8             *pFrameworkTestabilityMessage8 = reinterpret_cast<FrameworkTestabilityMessage8 *> (pFrameworkPersistenceTestContext->getPWaveMessage ());
    ResourceId                                status                        = WAVE_MESSAGE_SUCCESS;
    UI32                                      numberOfObjectsToCreate       = pFrameworkTestabilityMessage8->getNumberOfObjectsToBeCreated ();


    WaveManagedObjectSynchronousQueryContext *pWaveManagedObjectSynchronousQueryContext = new WaveManagedObjectSynchronousQueryContext (WaveTestManagedView2::getClassName ());
    vector<WaveManagedObject *> *pResults = querySynchronously (pWaveManagedObjectSynchronousQueryContext);

    delete pWaveManagedObjectSynchronousQueryContext;

/*
    if ( (*(pResults)).size () != numberOfObjectsToCreate)
    {
        status = WAVE_MESSAGE_ERROR;
    }
*/

    UI32 numberOfResults = pResults->size ();

    tracePrintf (TRACE_LEVEL_INFO, true, false, "FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryByManagedViewWithUnionSqlTestStep: numberOfObjectsToCreate : %d, numberOfResults = %d", numberOfObjectsToCreate, numberOfResults);

    UI32 i               = 0;
    for (i = 0; i < numberOfResults; i++)
    {
        WaveTestManagedView2 *pWaveTestManagedView2 = dynamic_cast<WaveTestManagedView2 *> ((*pResults)[i]);
        waveAssert (NULL != pWaveTestManagedView2, __FILE__, __LINE__);
        UI32                     integer2                         = pWaveTestManagedView2->getInteger2  ();
        string                   message2                         = pWaveTestManagedView2->getMessage2  ();

        tracePrintf (TRACE_LEVEL_INFO, true, false, "Got      : integer2 - %d,  message2 - %s", integer2, message2.c_str());
        delete pWaveTestManagedView2;
    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
    
}

void FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryByAttributeSqlExistsTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-One Association Query By Attribute Sql EXISTS...");

    ResourceId                                status                           = WAVE_MESSAGE_SUCCESS;

    WaveManagedObjectSynchronousInnerQueryContext *pWaveManagedObjectSynchronousInnerQueryContext = new WaveManagedObjectSynchronousInnerQueryContext (WaveTestManagedObject1::getClassName ());
    pWaveManagedObjectSynchronousInnerQueryContext->addOrAttribute (new AttributeUI32(1, "integer1"));
    pWaveManagedObjectSynchronousInnerQueryContext->addSelectField ("integer1");

    WaveManagedObjectSynchronousQueryContext *pWaveManagedObjectSynchronousQueryContext = new WaveManagedObjectSynchronousQueryContext (WaveTestManagedObject2::getClassName ());
    pWaveManagedObjectSynchronousQueryContext->addAndAttribute (new AttributeSqlExists(pWaveManagedObjectSynchronousInnerQueryContext), WAVE_ATTRIBUTE_CONDITION_OPERATOR_EXISTS);
    pWaveManagedObjectSynchronousQueryContext->addAndAttribute (new AttributeUI32(1, "integer2"), WAVE_ATTRIBUTE_CONDITION_OPERATOR_EQUAL);
    vector<WaveManagedObject *> *pResults = querySynchronously (pWaveManagedObjectSynchronousQueryContext);

    delete pWaveManagedObjectSynchronousQueryContext;
    delete pWaveManagedObjectSynchronousInnerQueryContext;

    if ( (*(pResults)).size () != 1)
    {
        status = WAVE_MESSAGE_ERROR;
    }
    pFrameworkPersistenceTestContext->executeNextStep (status);
    
}

void FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryByAttributeSqlNotExistsTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-One Association Query By Attribute Sql NOT EXISTS...");

    ResourceId                                status                           = WAVE_MESSAGE_SUCCESS;

    WaveManagedObjectSynchronousInnerQueryContext *pWaveManagedObjectSynchronousInnerQueryContext = new WaveManagedObjectSynchronousInnerQueryContext (WaveTestManagedObject1::getClassName ());
    pWaveManagedObjectSynchronousInnerQueryContext->addOrAttribute (new AttributeUI32(1, "integer1"));
    pWaveManagedObjectSynchronousInnerQueryContext->addSelectField ("integer1");

    WaveManagedObjectSynchronousQueryContext *pWaveManagedObjectSynchronousQueryContext = new WaveManagedObjectSynchronousQueryContext (WaveTestManagedObject2::getClassName ());
    pWaveManagedObjectSynchronousQueryContext->addAndAttribute (new AttributeSqlExists(pWaveManagedObjectSynchronousInnerQueryContext), WAVE_ATTRIBUTE_CONDITION_OPERATOR_NOT_EXISTS);
    pWaveManagedObjectSynchronousQueryContext->addAndAttribute (new AttributeUI32(1, "integer2"), WAVE_ATTRIBUTE_CONDITION_OPERATOR_EQUAL);
    vector<WaveManagedObject *> *pResults = querySynchronously (pWaveManagedObjectSynchronousQueryContext);

    delete pWaveManagedObjectSynchronousQueryContext;
    delete pWaveManagedObjectSynchronousInnerQueryContext;

    if ( (*(pResults)).size () != 0)
    {
        status = WAVE_MESSAGE_ERROR;
    }
    pFrameworkPersistenceTestContext->executeNextStep (status);
    
}

void FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryByAttributeSqlInTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-One Association Query By Attribute Sql IN...");

    ResourceId                                status                           = WAVE_MESSAGE_SUCCESS;

    WaveManagedObjectSynchronousInnerQueryContext *pWaveManagedObjectSynchronousInnerQueryContext = new WaveManagedObjectSynchronousInnerQueryContext (WaveTestManagedObject1::getClassName ());
    pWaveManagedObjectSynchronousInnerQueryContext->addOrAttribute (new AttributeUI32(1, "integer1"));
    pWaveManagedObjectSynchronousInnerQueryContext->addOrAttribute (new AttributeUI32(2, "integer1"));
    pWaveManagedObjectSynchronousInnerQueryContext->addSelectField ("integer1");

    WaveManagedObjectSynchronousQueryContext *pWaveManagedObjectSynchronousQueryContext = new WaveManagedObjectSynchronousQueryContext (WaveTestManagedObject2::getClassName ());
    pWaveManagedObjectSynchronousQueryContext->addAndAttribute (new AttributeSqlIn(pWaveManagedObjectSynchronousInnerQueryContext, "integer2"), WAVE_ATTRIBUTE_CONDITION_OPERATOR_IN);
    vector<WaveManagedObject *> *pResults = querySynchronously (pWaveManagedObjectSynchronousQueryContext);

    delete pWaveManagedObjectSynchronousQueryContext;
    delete pWaveManagedObjectSynchronousInnerQueryContext;

    if ( (*(pResults)).size () != 2)
    {
        status = WAVE_MESSAGE_ERROR;
    }
    pFrameworkPersistenceTestContext->executeNextStep (status);
    
}

void FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-One Association Query Test ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject2::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryTestCallback), pFrameworkPersistenceTestContext);

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults ((pFrameworkPersistenceTestContext->getCreatedObjects2 ()).size ());

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryTestCallback (WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext)
{
    FrameworkPersistenceTestContext          *pFrameworkPersistenceTestContext = reinterpret_cast<FrameworkPersistenceTestContext *> (pWaveManagedObjectQueryContext->getPCallerContext ());
    ResourceId                                status                           = pWaveManagedObjectQueryContext->getCompletionStatus ();
    map<ObjectId, WaveTestManagedObject2 *> &allCreatedObjects2Map            = pFrameworkPersistenceTestContext->getCreatedObjects2Map ();

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryTestCallback : Simple One-One Association Query test failed. Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        vector<WaveManagedObject *> *pResults = pWaveManagedObjectQueryContext->getPResults ();

        waveAssert (NULL != pResults, __FILE__, __LINE__);

        UI32 numberOfExpectedResults = pFrameworkPersistenceTestContext->getNumberOfExpectedResults ();
        UI32 numberOfResults = pResults->size ();
        UI32 i               = 0;

        if (numberOfExpectedResults != numberOfResults)
        {
            trace (TRACE_LEVEL_FATAL, string ("FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryTestCallback : We did not get expected number of results.  Expected = ") + numberOfExpectedResults + string (", Obtained =  ") + numberOfResults);
            waveAssert (false, __FILE__, __LINE__);
            status = WAVE_MESSAGE_ERROR;
        }
        else
        {
            trace (TRACE_LEVEL_DEVEL, string ("    Number of Results (asynchronously obtained) = ") + numberOfResults);

            for (i = 0; i < numberOfResults; i++)
            {
                WaveTestManagedObject2 *pWaveTestManagedObject2         = dynamic_cast<WaveTestManagedObject2 *> ((*pResults)[i]);
                waveAssert (NULL != pWaveTestManagedObject2, __FILE__, __LINE__);
                ObjectId                 oid                              = pWaveTestManagedObject2->getObjectId  ();
                UI32                     integer2                         = pWaveTestManagedObject2->getInteger2  ();
                string                   message2                         = pWaveTestManagedObject2->getMessage2  ();
                ObjectId                 objectId2                        = pWaveTestManagedObject2->getObjectId2 ();

                WaveTestManagedObject2 *pWaveTestManagedObject2Expected = allCreatedObjects2Map[oid];
                ObjectId                 oidExpected                      = pWaveTestManagedObject2Expected->getObjectId  ();
                UI32                     integer2Expected                 = pWaveTestManagedObject2Expected->getInteger2  ();
                string                   message2Expected                 = pWaveTestManagedObject2Expected->getMessage2  ();
                ObjectId                 objectId2Expected                = pWaveTestManagedObject2Expected->getObjectId2 ();

                //trace (TRACE_LEVEL_DEVEL, string ("        ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer2 + string (", ") + message2 + string (", ") + objectId2.getClassId () + string (", ") + objectId2.getInstanceId ());

                if ((*pWaveTestManagedObject2Expected) != (*pWaveTestManagedObject2))
                {
                    trace (TRACE_LEVEL_ERROR, string ("Got      : ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer2 + string (", ") + message2 + string (", ") + objectId2.getClassId () + string (", ") + objectId2.getInstanceId ());
                    trace (TRACE_LEVEL_ERROR, string ("Expected : ") + oidExpected.getClassId () + string (", ") + oidExpected.getInstanceId () + string (", ") + integer2Expected + string (", ") + message2Expected + string (", ") + objectId2Expected.getClassId () + string (", ") + objectId2Expected.getInstanceId ());
                    waveAssert (false, __FILE__, __LINE__);

                    status = WAVE_MESSAGE_ERROR;
                    break;
                }
            }

            if (WAVE_MESSAGE_SUCCESS == status)
            {
                trace (TRACE_LEVEL_DEVEL, "    All Queried results were successfully compared against expected values.");
            }
        }
    }

    delete pWaveManagedObjectQueryContext;

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryByObjectIdsTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-One Association Query By ObjectIds Test ...");

    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject2::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleOneToOneAssociationQueryTestCallback), pFrameworkPersistenceTestContext);

    // Now add the ObjectIds to the context so that the query gets only the requested objects.

    vector<WaveTestManagedObject2 *> &allCreatedObjects2        = pFrameworkPersistenceTestContext->getCreatedObjects2 ();
    UI32                               numberOfObjectsCreated2   = allCreatedObjects2.size ();
    UI32                               numberOfObjectsToQueryFor = numberOfObjectsCreated2 > 100 ? 100 : numberOfObjectsCreated2;
    UI32                               i                         = 0;

    for (i = 0; i < numberOfObjectsToQueryFor; i++)
    {
        pWaveManagedObjectQueryContext->addObjectId ((allCreatedObjects2[i])->getObjectId ());
    }

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults (numberOfObjectsToQueryFor);

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleOneToOneAssociationSynchronousQueryTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-One Association Synchronous Query Test ...");

    map<ObjectId, WaveTestManagedObject2 *> &allCreatedObjects2Map = pFrameworkPersistenceTestContext->getCreatedObjects2Map ();
    vector<WaveManagedObject *>             *pResults              = querySynchronously (WaveTestManagedObject2::getClassName ());

    waveAssert (NULL != pResults, __FILE__, __LINE__);

    UI32       numberOfExpectedResults = (pFrameworkPersistenceTestContext->getCreatedObjects2 ()).size ();
    UI32       numberOfResults         = pResults->size ();
    UI32       i                        = 0;
    ResourceId status                   = WAVE_MESSAGE_SUCCESS;

    trace (TRACE_LEVEL_DEVEL, string ("    Number of Results (synchronously obtained) = ") + numberOfResults);

    if (numberOfExpectedResults != numberOfResults)
    {
        trace (TRACE_LEVEL_FATAL, string ("FrameworkTestability4ObjectManager::simpleOneToOneAssociationSynchronousQueryTestStep : We did not get expected number of results.  Expected = ") + numberOfExpectedResults + string (", Obtained =  ") + numberOfResults);
        waveAssert (false, __FILE__, __LINE__);
        status = WAVE_MESSAGE_ERROR;
    }
    else
    {
        for (i = 0; i < numberOfResults; i++)
        {
            WaveTestManagedObject2 *pWaveTestManagedObject2         = dynamic_cast<WaveTestManagedObject2 *> ((*pResults)[i]);
            waveAssert (NULL != pWaveTestManagedObject2, __FILE__, __LINE__);
            ObjectId                 oid                              = pWaveTestManagedObject2->getObjectId  ();
            UI32                     integer2                         = pWaveTestManagedObject2->getInteger2  ();
            string                   message2                         = pWaveTestManagedObject2->getMessage2  ();
            ObjectId                 objectId2                        = pWaveTestManagedObject2->getObjectId2 ();

            WaveTestManagedObject2 *pWaveTestManagedObject2Expected = allCreatedObjects2Map[oid];
            ObjectId                 oidExpected                      = pWaveTestManagedObject2Expected->getObjectId  ();
            UI32                     integer2Expected                 = pWaveTestManagedObject2Expected->getInteger2  ();
            string                   message2Expected                 = pWaveTestManagedObject2Expected->getMessage2  ();
            ObjectId                 objectId2Expected                = pWaveTestManagedObject2Expected->getObjectId2 ();

            //trace (TRACE_LEVEL_DEVEL, string ("        ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer2 + string (", ") + message2 + string (", ") + objectId2.getClassId () + string (", ") + objectId2.getInstanceId ());

            if ((*pWaveTestManagedObject2Expected) != (*pWaveTestManagedObject2))
            {
                trace (TRACE_LEVEL_ERROR, string ("Got      : ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer2 + string (", ") + message2 + string (", ") + objectId2.getClassId () + string (", ") + objectId2.getInstanceId ());
                trace (TRACE_LEVEL_ERROR, string ("Expected : ") + oidExpected.getClassId () + string (", ") + oidExpected.getInstanceId () + string (", ") + integer2Expected + string (", ") + message2Expected + string (", ") + objectId2Expected.getClassId () + string (", ") + objectId2Expected.getInstanceId ());
                waveAssert (false, __FILE__, __LINE__);

                status = WAVE_MESSAGE_ERROR;
                break;
            }
        }

        if (WAVE_MESSAGE_SUCCESS == status)
        {
            trace (TRACE_LEVEL_DEVEL, "    All Queried results were successfully compared against expected values.");
        }
    }

    for (i = 0; i < numberOfResults; i++)
    {
        delete ((*pResults)[i]);
    }

    delete pResults;

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleOneToOneAssociationSynchronousQueryByObjectIdsTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-One Association Synchronous Query By ObjectIds Test ...");

    // Now add the ObjectIds to the context so that the query gets only the requested objects.

    vector<WaveTestManagedObject2 *>        &allCreatedObjects2       = pFrameworkPersistenceTestContext->getCreatedObjects2 ();
    map<ObjectId, WaveTestManagedObject2 *> &allCreatedObjects2Map    = pFrameworkPersistenceTestContext->getCreatedObjects2Map ();
    UI32                                     numberOfObjectsCreated2   = allCreatedObjects2.size ();
    UI32                                     numberOfObjectsToQueryFor = numberOfObjectsCreated2 > 100 ? 100 : numberOfObjectsCreated2;
    UI32                                     i                         = 0;
    vector<ObjectId>                         objectIds;

    for (i = 0; i < numberOfObjectsToQueryFor; i++)
    {
        objectIds.push_back ((allCreatedObjects2[i])->getObjectId ());
    }

    vector<WaveManagedObject *> *pResults = querySynchronously (WaveTestManagedObject2::getClassName (), objectIds);

    waveAssert (NULL != pResults, __FILE__, __LINE__);

    UI32       numberOfExpectedResults = numberOfObjectsToQueryFor;
    UI32       numberOfResults         = pResults->size ();
    ResourceId status                  = WAVE_MESSAGE_SUCCESS;

    trace (TRACE_LEVEL_DEVEL, string ("    Number of Results (synchronously obtained) = ") + numberOfResults);

    if (numberOfExpectedResults != numberOfResults)
    {
        trace (TRACE_LEVEL_FATAL, string ("FrameworkTestability4ObjectManager::simpleOneToOneAssociationSynchronousQueryByObjectIdsTestStep : We did not get expected number of results.  Expected = ") + numberOfExpectedResults + string (", Obtained =  ") + numberOfResults);
        waveAssert (false, __FILE__, __LINE__);
        status = WAVE_MESSAGE_ERROR;
    }
    else
    {
        for (i = 0; i < numberOfResults; i++)
        {
            WaveTestManagedObject2 *pWaveTestManagedObject2         = dynamic_cast<WaveTestManagedObject2 *> ((*pResults)[i]);
            waveAssert (NULL != pWaveTestManagedObject2, __FILE__, __LINE__);
            ObjectId                 oid                              = pWaveTestManagedObject2->getObjectId  ();
            UI32                     integer2                         = pWaveTestManagedObject2->getInteger2  ();
            string                   message2                         = pWaveTestManagedObject2->getMessage2  ();
            ObjectId                 objectId2                        = pWaveTestManagedObject2->getObjectId2 ();

            WaveTestManagedObject2 *pWaveTestManagedObject2Expected = allCreatedObjects2Map[oid];
            ObjectId                 oidExpected                      = pWaveTestManagedObject2Expected->getObjectId  ();
            UI32                     integer2Expected                 = pWaveTestManagedObject2Expected->getInteger2  ();
            string                   message2Expected                 = pWaveTestManagedObject2Expected->getMessage2  ();
            ObjectId                 objectId2Expected                = pWaveTestManagedObject2Expected->getObjectId2 ();

            //trace (TRACE_LEVEL_DEVEL, string ("        ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer2 + string (", ") + message2 + string (", ") + objectId2.getClassId () + string (", ") + objectId2.getInstanceId ());

            if ((*pWaveTestManagedObject2Expected) != (*pWaveTestManagedObject2))
            {
                trace (TRACE_LEVEL_ERROR, string ("Got      : ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer2 + string (", ") + message2 + string (", ") + objectId2.getClassId () + string (", ") + objectId2.getInstanceId ());
                trace (TRACE_LEVEL_ERROR, string ("Expected : ") + oidExpected.getClassId () + string (", ") + oidExpected.getInstanceId () + string (", ") + integer2Expected + string (", ") + message2Expected + string (", ") + objectId2Expected.getClassId () + string (", ") + objectId2Expected.getInstanceId ());
                waveAssert (false, __FILE__, __LINE__);

                status = WAVE_MESSAGE_ERROR;
                break;
            }
        }

        if (WAVE_MESSAGE_SUCCESS == status)
        {
            trace (TRACE_LEVEL_DEVEL, "    All Queried results were successfully compared against expected values.");
        }
    }

    for (i = 0; i < numberOfResults; i++)
    {
        delete ((*pResults)[i]);
    }

    delete pResults;

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::deleteAllCreatedObjects2TestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Delete All Created Objects2 Transaction Test ...");

    ResourceId                                status                  = WAVE_MESSAGE_SUCCESS;
    UI32                                      i                       = 0;
    vector<WaveTestManagedObject1 *>        &allCreatedObjects       = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjectsMap    = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    vector<WaveTestManagedObject2 *>        &allCreatedObjects2      = pFrameworkPersistenceTestContext->getCreatedObjects2 ();
    map<ObjectId, WaveTestManagedObject2 *> &allCreatedObjects2Map   = pFrameworkPersistenceTestContext->getCreatedObjects2Map ();
    UI32                                      numberOfObjectsCreated  = allCreatedObjects.size ();
    UI32                                      numberOfObjectsCreated2 = allCreatedObjects2.size ();

    startTransaction ();

    for (i = 0; i < numberOfObjectsCreated2; i++)
    {
        delete allCreatedObjects2[i];
    }

    for (i = 0; i < numberOfObjectsCreated; i++)
    {
        delete allCreatedObjects[i];
    }

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::deleteAllCreatedObjects2TestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }

    allCreatedObjects2.clear ();
    allCreatedObjects2Map.clear ();
    allCreatedObjects.clear ();
    allCreatedObjectsMap.clear ();

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleOneToAssociationUpdateTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-One Association Update Test ...");

    ResourceId                         status                 = WAVE_MESSAGE_SUCCESS;
    UI32                               i                      = 0;
    vector<WaveTestManagedObject1 *> &allCreatedObjects      = pFrameworkPersistenceTestContext->getCreatedObjects ();
    vector<WaveTestManagedObject2 *> &allCreatedObjects2     = pFrameworkPersistenceTestContext->getCreatedObjects2 ();
    UI32                               numberOfObjectsCreated = allCreatedObjects2.size ();

    for (i = 0; i < numberOfObjectsCreated; i++)
    {
        startTransaction ();

        WaveTestManagedObject1 *pWaveTestManagedObject1 = allCreatedObjects[i];
        WaveTestManagedObject2 *pWaveTestManagedObject2 = allCreatedObjects2[i];

        updateWaveManagedObject (pWaveTestManagedObject1);
        updateWaveManagedObject (pWaveTestManagedObject2);

        pWaveTestManagedObject1->setInteger1 (i + 21);
        pWaveTestManagedObject1->setMessage1 ("Test Update 21");
        pWaveTestManagedObject1->setObjectId1 (ObjectId (i + 100, i + 100));

        pWaveTestManagedObject2->setInteger2 (i + 22);
        pWaveTestManagedObject2->setMessage2 ("Test Update 22");
        pWaveTestManagedObject2->setObjectId2 (ObjectId (i + 1000, i + 100));
        pWaveTestManagedObject2->setAssociation2 (pWaveTestManagedObject1->getObjectId ());

        status = commitTransaction ();

        if (status != FRAMEWORK_SUCCESS)
        {
            trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::simpleOneToAssociationUpdateTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
            break;
        }
        else
        {
            status = WAVE_MESSAGE_SUCCESS;
        }
    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::largeOneToAssociationUpdateTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Large One-One Association Update Test ...");

    ResourceId                         status                 = WAVE_MESSAGE_SUCCESS;
    UI32                               i                      = 0;
    vector<WaveTestManagedObject1 *> &allCreatedObjects      = pFrameworkPersistenceTestContext->getCreatedObjects ();
    vector<WaveTestManagedObject2 *> &allCreatedObjects2     = pFrameworkPersistenceTestContext->getCreatedObjects2 ();
    UI32                               numberOfObjectsCreated = allCreatedObjects2.size ();

    startTransaction ();

    for (i = 0; i < numberOfObjectsCreated; i++)
    {
        WaveTestManagedObject1 *pWaveTestManagedObject1 = allCreatedObjects[i];
        WaveTestManagedObject2 *pWaveTestManagedObject2 = allCreatedObjects2[i];

        updateWaveManagedObject (pWaveTestManagedObject1);
        updateWaveManagedObject (pWaveTestManagedObject2);

        pWaveTestManagedObject1->setInteger1 (i + 210);
        pWaveTestManagedObject1->setMessage1 ("Test Update 210");
        pWaveTestManagedObject1->setObjectId1 (ObjectId (i + 210, i + 210));

        pWaveTestManagedObject2->setInteger2 (i + 220);
        pWaveTestManagedObject2->setMessage2 ("Test Update 220");
        pWaveTestManagedObject2->setObjectId2 (ObjectId (i + 1220, i + 1220));
        pWaveTestManagedObject2->setAssociation2 (pWaveTestManagedObject1->getObjectId ());
    }

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::largeOneToAssociationUpdateTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

//Testing of updateMultipleWaveManagedObjects using update Context
void FrameworkTestability4ObjectManager::updateAssociationWithUpdateContextTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Update Association With Update Context Test ...");

    ResourceId                         status                 = WAVE_MESSAGE_SUCCESS;
    UI32                               i                      = 0;
    vector<WaveTestManagedObject1 *> &allCreatedObjects      = pFrameworkPersistenceTestContext->getCreatedObjects ();
    vector<WaveTestManagedObject2 *> &allCreatedObjects2     = pFrameworkPersistenceTestContext->getCreatedObjects2 ();
    UI32                               numberOfObjectsCreated = allCreatedObjects2.size ();

    for (i = 0; i < numberOfObjectsCreated; i++)
    {

        WaveTestManagedObject1 *pWaveTestManagedObject1 = allCreatedObjects[i];
        WaveTestManagedObject2 *pWaveTestManagedObject2 = allCreatedObjects2[i];

        pWaveTestManagedObject1->setInteger1 (21);
        pWaveTestManagedObject1->setMessage1 ("Test Update 21");
        pWaveTestManagedObject1->setObjectId1 (ObjectId (100, 100));

        pWaveTestManagedObject2->setInteger2 (22);
        pWaveTestManagedObject2->setMessage2 ("Test Update 22");
        pWaveTestManagedObject2->setObjectId2 (ObjectId (1000, 100));
        pWaveTestManagedObject2->setAssociation2 (allCreatedObjects[0]->getObjectId ());
    }

    startTransaction ();

    WaveManagedObjectSynchronousQueryContextForUpdate *syncQueryCtxt1 = new WaveManagedObjectSynchronousQueryContextForUpdate (WaveTestManagedObject1::getClassName ());
    WaveManagedObject *waveManagedObject1 = syncQueryCtxt1->getWaveManagedObjectToAddUpdateAttributes ();
    WaveTestManagedObject1 *pEmptyWaveTestManagedObject1 = dynamic_cast<WaveTestManagedObject1 *> (waveManagedObject1);

    pEmptyWaveTestManagedObject1->setInteger1 (21);
    pEmptyWaveTestManagedObject1->setMessage1 ("Test Update 21");
    pEmptyWaveTestManagedObject1->setObjectId1 (ObjectId (100, 100));

    pEmptyWaveTestManagedObject1->addAttributeToBeUpdated ("integer1");
    pEmptyWaveTestManagedObject1->addAttributeToBeUpdated ("message1");
    pEmptyWaveTestManagedObject1->addAttributeToBeUpdated ("objectId1");

    updateMultipleWaveManagedObjects (syncQueryCtxt1);

    WaveManagedObjectSynchronousQueryContextForUpdate *syncQueryCtxt2 = new WaveManagedObjectSynchronousQueryContextForUpdate (WaveTestManagedObject2::getClassName ());
    WaveManagedObject *waveManagedObject2 = syncQueryCtxt2->getWaveManagedObjectToAddUpdateAttributes ();
    WaveTestManagedObject2 *pEmptyWaveTestManagedObject2 = dynamic_cast<WaveTestManagedObject2 *> (waveManagedObject2);

    pEmptyWaveTestManagedObject2->setInteger2 (22);
    pEmptyWaveTestManagedObject2->setMessage2 ("Test Update 22");
    pEmptyWaveTestManagedObject2->setObjectId2 (ObjectId (1000, 100));
    pEmptyWaveTestManagedObject2->setAssociation2 (allCreatedObjects[0]->getObjectId ());

    pEmptyWaveTestManagedObject2->addAttributeToBeUpdated ("integer2");
    pEmptyWaveTestManagedObject2->addAttributeToBeUpdated ("message2");
    pEmptyWaveTestManagedObject2->addAttributeToBeUpdated ("objectId2");
    pEmptyWaveTestManagedObject2->addAttributeToBeUpdated ("association2");

    updateMultipleWaveManagedObjects (syncQueryCtxt2);

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::updateAssociationWithUpdateContextTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::largeOneToAssociationTransactionTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Large One-One Association Transaction Test ...");

    FrameworkTestabilityMessage8             *pFrameworkTestabilityMessage8 = reinterpret_cast<FrameworkTestabilityMessage8 *> (pFrameworkPersistenceTestContext->getPWaveMessage ());
    ResourceId                                status                        = WAVE_MESSAGE_SUCCESS;
    UI32                                      numberOfObjectsToCreate       = pFrameworkTestabilityMessage8->getNumberOfObjectsToBeCreated ();
    UI32                                      i                             = 0;
    vector<WaveTestManagedObject1 *>        &allCreatedObjects             = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjectsMap          = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    vector<WaveTestManagedObject2 *>        &allCreatedObjects2            = pFrameworkPersistenceTestContext->getCreatedObjects2 ();
    map<ObjectId, WaveTestManagedObject2 *> &allCreatedObjects2Map         = pFrameworkPersistenceTestContext->getCreatedObjects2Map ();

    startTransaction ();

    for (i = 0; i < numberOfObjectsToCreate; i++)
    {
        WaveTestManagedObject1 *pWaveTestManagedObject1 = new WaveTestManagedObject1 (this);
        WaveTestManagedObject2 *pWaveTestManagedObject2 = new WaveTestManagedObject2 (this);

        pWaveTestManagedObject1->setInteger1 (i);
        pWaveTestManagedObject1->setMessage1 ("Test");
        pWaveTestManagedObject1->setObjectId1 (ObjectId (i, i));

        pWaveTestManagedObject2->setInteger2 (i);
        pWaveTestManagedObject2->setMessage2 ("Test");
        pWaveTestManagedObject2->setObjectId2 (ObjectId (i, i));
        pWaveTestManagedObject2->setAssociation2 (pWaveTestManagedObject1->getObjectId ());

        allCreatedObjects.push_back (pWaveTestManagedObject1);
        allCreatedObjectsMap[pWaveTestManagedObject1->getObjectId ()] = pWaveTestManagedObject1;
        allCreatedObjects2.push_back (pWaveTestManagedObject2);
        allCreatedObjects2Map[pWaveTestManagedObject2->getObjectId ()] = pWaveTestManagedObject2;
    }

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::largeOneToAssociationTransactionTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleDerivationTransactionTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Derivation Transaction Test ...");

    FrameworkTestabilityMessage8             *pFrameworkTestabilityMessage8 = reinterpret_cast<FrameworkTestabilityMessage8 *> (pFrameworkPersistenceTestContext->getPWaveMessage ());
    ResourceId                                status                        = WAVE_MESSAGE_SUCCESS;
    UI32                                      numberOfObjectsToCreate       = pFrameworkTestabilityMessage8->getNumberOfObjectsToBeCreated ();
    UI32                                      i                             = 0;
    vector<WaveTestManagedObject1 *>        &allCreatedObjects             = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjects1Map         = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    vector<WaveTestManagedObject3 *>        &allCreatedObjects3            = pFrameworkPersistenceTestContext->getCreatedObjects3 ();
    map<ObjectId, WaveTestManagedObject3 *> &allCreatedObjects3Map         = pFrameworkPersistenceTestContext->getCreatedObjects3Map ();

    for (i = 0; i < numberOfObjectsToCreate; i++)
    {
        startTransaction ();

        WaveTestManagedObject1 *pWaveTestManagedObject1 = new WaveTestManagedObject1 (this);
        WaveTestManagedObject3 *pWaveTestManagedObject3 = new WaveTestManagedObject3 (this);

        pWaveTestManagedObject1->setInteger1 (i);
        pWaveTestManagedObject1->setMessage1 ("Test 1");
        pWaveTestManagedObject1->setObjectId1 (ObjectId (i, i));

        pWaveTestManagedObject3->setInteger1 (i);
        pWaveTestManagedObject3->setMessage1 ("Test 31");
        pWaveTestManagedObject3->setObjectId1 (ObjectId (i, i));
        pWaveTestManagedObject3->setInteger3 (i);
        pWaveTestManagedObject3->setMessage3 ("Test 33");
        pWaveTestManagedObject3->setObjectId3 (ObjectId (i, i));
        pWaveTestManagedObject3->setAssociation3 (pWaveTestManagedObject1->getObjectId ());

        allCreatedObjects.push_back (pWaveTestManagedObject1);
        allCreatedObjects1Map[pWaveTestManagedObject1->getObjectId ()] = pWaveTestManagedObject1;
        allCreatedObjects3.push_back (pWaveTestManagedObject3);
        allCreatedObjects3Map[pWaveTestManagedObject3->getObjectId ()] = pWaveTestManagedObject3;

        status = commitTransaction ();

        if (status != FRAMEWORK_SUCCESS)
        {
            trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::simpleDerivationTransactionTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
            break;
        }
        else
        {
            status = WAVE_MESSAGE_SUCCESS;
        }
    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleDerivationQueryTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Derivation Query Test ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject3::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleDerivationQueryTestCallback), pFrameworkPersistenceTestContext);

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults ((pFrameworkPersistenceTestContext->getCreatedObjects3 ()).size ());

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleDerivationQueryTestCallback (WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext)
{
    FrameworkPersistenceTestContext          *pFrameworkPersistenceTestContext = reinterpret_cast<FrameworkPersistenceTestContext *> (pWaveManagedObjectQueryContext->getPCallerContext ());
    ResourceId                                status                           = pWaveManagedObjectQueryContext->getCompletionStatus ();
    map<ObjectId, WaveTestManagedObject3 *> &allCreatedObjects3Map            = pFrameworkPersistenceTestContext->getCreatedObjects3Map ();

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::simpleDerivationQueryTestCallback : Simple Derivation Query test failed. Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        vector<WaveManagedObject *> *pResults = pWaveManagedObjectQueryContext->getPResults ();

        waveAssert (NULL != pResults, __FILE__, __LINE__);

        UI32 numberOfExpectedResults = pFrameworkPersistenceTestContext->getNumberOfExpectedResults ();
        UI32 numberOfResults = pResults->size ();
        UI32 i               = 0;

        if (numberOfExpectedResults != numberOfResults)
        {
            trace (TRACE_LEVEL_FATAL, string ("FrameworkTestability4ObjectManager::simpleDerivationQueryTestCallback : We did not get expected number of results.  Expected = ") + numberOfExpectedResults + string (", Obtained =  ") + numberOfResults);
            waveAssert (false, __FILE__, __LINE__);
            status = WAVE_MESSAGE_ERROR;
        }
        else
        {
            trace (TRACE_LEVEL_DEVEL, string ("    Number of Results (asynchronously obtained) = ") + numberOfResults);

            for (i = 0; i < numberOfResults; i++)
            {
                WaveTestManagedObject3 *pWaveTestManagedObject3         = dynamic_cast<WaveTestManagedObject3 *> ((*pResults)[i]);
                waveAssert (NULL != pWaveTestManagedObject3, __FILE__, __LINE__);
                ObjectId                 oid                              = pWaveTestManagedObject3->getObjectId  ();
                UI32                     integer1                         = pWaveTestManagedObject3->getInteger1  ();
                string                   message1                         = pWaveTestManagedObject3->getMessage1  ();
                ObjectId                 objectId1                        = pWaveTestManagedObject3->getObjectId1 ();
                UI32                     integer3                         = pWaveTestManagedObject3->getInteger3  ();
                string                   message3                         = pWaveTestManagedObject3->getMessage3  ();
                ObjectId                 objectId3                        = pWaveTestManagedObject3->getObjectId3 ();
                ObjectId                 association3                     = pWaveTestManagedObject3->getAssociation3 ();

                WaveTestManagedObject3 *pWaveTestManagedObject3Expected = allCreatedObjects3Map[oid];
                ObjectId                 oidExpected                      = pWaveTestManagedObject3Expected->getObjectId  ();
                UI32                     integer1Expected                 = pWaveTestManagedObject3Expected->getInteger1  ();
                string                   message1Expected                 = pWaveTestManagedObject3Expected->getMessage1  ();
                ObjectId                 objectId1Expected                = pWaveTestManagedObject3Expected->getObjectId1 ();
                UI32                     integer3Expected                 = pWaveTestManagedObject3Expected->getInteger3  ();
                string                   message3Expected                 = pWaveTestManagedObject3Expected->getMessage3  ();
                ObjectId                 objectId3Expected                = pWaveTestManagedObject3Expected->getObjectId3 ();
                ObjectId                 association3Expected             = pWaveTestManagedObject3Expected->getAssociation3 ();

                if ((*pWaveTestManagedObject3Expected) != (*pWaveTestManagedObject3))
                {
                    trace (TRACE_LEVEL_ERROR, string ("Got      : ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer1 + string (", ") + message1 + string (", ") + objectId1.getClassId () + string (", ") + objectId1.getInstanceId () + string (", ") + integer3 + string (", ") + message3 + string (", ") + objectId3.getClassId () + string (", ") + objectId3.getInstanceId () + string (", ") + association3.getClassId () + string (", ") + association3.getInstanceId ());
                    trace (TRACE_LEVEL_ERROR, string ("Expected : ") + oidExpected.getClassId () + string (", ") + oidExpected.getInstanceId () + string (", ") + integer1Expected + string (", ") + message1Expected + string (", ") + objectId1Expected.getClassId () + string (", ") + objectId1Expected.getInstanceId () + string (", ") + integer3Expected + string (", ") + message3Expected + string (", ") + objectId3Expected.getClassId () + string (", ") + objectId3Expected.getInstanceId () + string (", ") + association3Expected.getClassId () + string (", ") + association3Expected.getInstanceId ());
                    waveAssert (false, __FILE__, __LINE__);

                    status = WAVE_MESSAGE_ERROR;
                    break;
                }
            }

            if (WAVE_MESSAGE_SUCCESS == status)
            {
                trace (TRACE_LEVEL_DEVEL, "    All Queried results were successfully compared against expected values.");
            }
        }
    }

    delete pWaveManagedObjectQueryContext;

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleDerivationQueryByObjectIdsTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Derivation Query By ObjectIds Test ...");

    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject3::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleDerivationQueryTestCallback), pFrameworkPersistenceTestContext);

    // Now add the ObjectIds to the context so that the query gets only the requested objects.

    vector<WaveTestManagedObject3 *> &allCreatedObjects3        = pFrameworkPersistenceTestContext->getCreatedObjects3 ();
    UI32                               numberOfObjectsCreated3   = allCreatedObjects3.size ();
    UI32                               numberOfObjectsToQueryFor = numberOfObjectsCreated3 > 100 ? 100 : numberOfObjectsCreated3;
    UI32                               i                         = 0;

    for (i = 0; i < numberOfObjectsToQueryFor; i++)
    {
        pWaveManagedObjectQueryContext->addObjectId ((allCreatedObjects3[i])->getObjectId ());
    }

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults (numberOfObjectsToQueryFor);

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleDerivationSynchronousQueryTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Derivation Synchronous Query Test ...");

    map<ObjectId, WaveTestManagedObject3 *> &allCreatedObjects3Map = pFrameworkPersistenceTestContext->getCreatedObjects3Map ();
    vector<WaveManagedObject *>             *pResults              = querySynchronously (WaveTestManagedObject3::getClassName ());

    waveAssert (NULL != pResults, __FILE__, __LINE__);

    UI32       numberOfExpectedResults = (pFrameworkPersistenceTestContext->getCreatedObjects3 ()).size ();
    UI32       numberOfResults         = pResults->size ();
    UI32       i                        = 0;
    ResourceId status                   = WAVE_MESSAGE_SUCCESS;

    trace (TRACE_LEVEL_DEVEL, string ("    Number of Results (synchronously obtained) = ") + numberOfResults);

    if (numberOfExpectedResults != numberOfResults)
    {
        trace (TRACE_LEVEL_FATAL, string ("FrameworkTestability4ObjectManager::simpleDerivationSynchronousQueryTestStep : We did not get expected number of results.  Expected = ") + numberOfExpectedResults + string (", Obtained =  ") + numberOfResults);
        waveAssert (false, __FILE__, __LINE__);
        status = WAVE_MESSAGE_ERROR;
    }
    else
    {
        for (i = 0; i < numberOfResults; i++)
        {
            WaveTestManagedObject3 *pWaveTestManagedObject3         = dynamic_cast<WaveTestManagedObject3 *> ((*pResults)[i]);
            waveAssert (NULL != pWaveTestManagedObject3, __FILE__, __LINE__);
            ObjectId                 oid                              = pWaveTestManagedObject3->getObjectId  ();
            UI32                     integer1                         = pWaveTestManagedObject3->getInteger1  ();
            string                   message1                         = pWaveTestManagedObject3->getMessage1  ();
            ObjectId                 objectId1                        = pWaveTestManagedObject3->getObjectId1 ();
            UI32                     integer3                         = pWaveTestManagedObject3->getInteger3  ();
            string                   message3                         = pWaveTestManagedObject3->getMessage3  ();
            ObjectId                 objectId3                        = pWaveTestManagedObject3->getObjectId3 ();
            ObjectId                 association3                     = pWaveTestManagedObject3->getAssociation3 ();

            WaveTestManagedObject3 *pWaveTestManagedObject3Expected = allCreatedObjects3Map[oid];
            ObjectId                 oidExpected                      = pWaveTestManagedObject3Expected->getObjectId  ();
            UI32                     integer1Expected                 = pWaveTestManagedObject3Expected->getInteger1  ();
            string                   message1Expected                 = pWaveTestManagedObject3Expected->getMessage1  ();
            ObjectId                 objectId1Expected                = pWaveTestManagedObject3Expected->getObjectId1 ();
            UI32                     integer3Expected                 = pWaveTestManagedObject3Expected->getInteger3  ();
            string                   message3Expected                 = pWaveTestManagedObject3Expected->getMessage3  ();
            ObjectId                 objectId3Expected                = pWaveTestManagedObject3Expected->getObjectId3 ();
            ObjectId                 association3Expected             = pWaveTestManagedObject3Expected->getAssociation3 ();

            if ((*pWaveTestManagedObject3Expected) != (*pWaveTestManagedObject3))
            {
                trace (TRACE_LEVEL_ERROR, string ("Got      : ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer1 + string (", ") + message1 + string (", ") + objectId1.getClassId () + string (", ") + objectId1.getInstanceId () + string (", ") + integer3 + string (", ") + message3 + string (", ") + objectId3.getClassId () + string (", ") + objectId3.getInstanceId () + string (", ") + association3.getClassId () + string (", ") + association3.getInstanceId ());
                trace (TRACE_LEVEL_ERROR, string ("Expected : ") + oidExpected.getClassId () + string (", ") + oidExpected.getInstanceId () + string (", ") + integer1Expected + string (", ") + message1Expected + string (", ") + objectId1Expected.getClassId () + string (", ") + objectId1Expected.getInstanceId () + string (", ") + integer3Expected + string (", ") + message3Expected + string (", ") + objectId3Expected.getClassId () + string (", ") + objectId3Expected.getInstanceId () + string (", ") + association3Expected.getClassId () + string (", ") + association3Expected.getInstanceId ());
                waveAssert (false, __FILE__, __LINE__);

                status = WAVE_MESSAGE_ERROR;
                break;
            }
        }

        if (WAVE_MESSAGE_SUCCESS == status)
        {
            trace (TRACE_LEVEL_DEVEL, "    All Queried results were successfully compared against expected values.");
        }
    }

    for (i = 0; i < numberOfResults; i++)
    {
        delete ((*pResults)[i]);
    }

    delete pResults;

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleDerivationSynchronousQueryByObjectIdsTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Derivation Synchronous Query By ObjectIds Test ...");

    // Now add the ObjectIds to the context so that the query gets only the requested objects.

    vector<WaveTestManagedObject3 *>        &allCreatedObjects3       = pFrameworkPersistenceTestContext->getCreatedObjects3 ();
    map<ObjectId, WaveTestManagedObject3 *> &allCreatedObjects3Map    = pFrameworkPersistenceTestContext->getCreatedObjects3Map ();
    UI32                                     numberOfObjectsCreated3   = allCreatedObjects3.size ();
    UI32                                     numberOfObjectsToQueryFor = numberOfObjectsCreated3 > 100 ? 100 : numberOfObjectsCreated3;
    UI32                                     i                         = 0;
    vector<ObjectId>                         objectIds;

    for (i = 0; i < numberOfObjectsToQueryFor; i++)
    {
        objectIds.push_back ((allCreatedObjects3[i])->getObjectId ());
    }

    vector<WaveManagedObject *> *pResults = querySynchronously (WaveTestManagedObject3::getClassName (), objectIds);

    waveAssert (NULL != pResults, __FILE__, __LINE__);

    UI32       numberOfExpectedResults = numberOfObjectsToQueryFor;
    UI32       numberOfResults         = pResults->size ();
    ResourceId status                  = WAVE_MESSAGE_SUCCESS;

    trace (TRACE_LEVEL_DEVEL, string ("    Number of Results (synchronously obtained) = ") + numberOfResults);

    if (numberOfExpectedResults != numberOfResults)
    {
        trace (TRACE_LEVEL_FATAL, string ("FrameworkTestability4ObjectManager::simpleDerivationSynchronousQueryByObjectIdsTestStep : We did not get expected number of results.  Expected = ") + numberOfExpectedResults + string (", Obtained =  ") + numberOfResults);
        waveAssert (false, __FILE__, __LINE__);
        status = WAVE_MESSAGE_ERROR;
    }
    else
    {
        for (i = 0; i < numberOfResults; i++)
        {
            WaveTestManagedObject3 *pWaveTestManagedObject3         = dynamic_cast<WaveTestManagedObject3 *> ((*pResults)[i]);
            waveAssert (NULL != pWaveTestManagedObject3, __FILE__, __LINE__);
            ObjectId                 oid                              = pWaveTestManagedObject3->getObjectId  ();
            UI32                     integer1                         = pWaveTestManagedObject3->getInteger1  ();
            string                   message1                         = pWaveTestManagedObject3->getMessage1  ();
            ObjectId                 objectId1                        = pWaveTestManagedObject3->getObjectId1 ();
            UI32                     integer3                         = pWaveTestManagedObject3->getInteger3  ();
            string                   message3                         = pWaveTestManagedObject3->getMessage3  ();
            ObjectId                 objectId3                        = pWaveTestManagedObject3->getObjectId3 ();
            ObjectId                 association3                     = pWaveTestManagedObject3->getAssociation3 ();

            WaveTestManagedObject3 *pWaveTestManagedObject3Expected = allCreatedObjects3Map[oid];
            ObjectId                 oidExpected                      = pWaveTestManagedObject3Expected->getObjectId  ();
            UI32                     integer1Expected                 = pWaveTestManagedObject3Expected->getInteger1  ();
            string                   message1Expected                 = pWaveTestManagedObject3Expected->getMessage1  ();
            ObjectId                 objectId1Expected                = pWaveTestManagedObject3Expected->getObjectId1 ();
            UI32                     integer3Expected                 = pWaveTestManagedObject3Expected->getInteger3  ();
            string                   message3Expected                 = pWaveTestManagedObject3Expected->getMessage3  ();
            ObjectId                 objectId3Expected                = pWaveTestManagedObject3Expected->getObjectId3 ();
            ObjectId                 association3Expected             = pWaveTestManagedObject3Expected->getAssociation3 ();

            if ((*pWaveTestManagedObject3Expected) != (*pWaveTestManagedObject3))
            {
                trace (TRACE_LEVEL_ERROR, string ("Got      : ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer1 + string (", ") + message1 + string (", ") + objectId1.getClassId () + string (", ") + objectId1.getInstanceId () + string (", ") + integer3 + string (", ") + message3 + string (", ") + objectId3.getClassId () + string (", ") + objectId3.getInstanceId () + string (", ") + association3.getClassId () + string (", ") + association3.getInstanceId ());
                trace (TRACE_LEVEL_ERROR, string ("Expected : ") + oidExpected.getClassId () + string (", ") + oidExpected.getInstanceId () + string (", ") + integer1Expected + string (", ") + message1Expected + string (", ") + objectId1Expected.getClassId () + string (", ") + objectId1Expected.getInstanceId () + string (", ") + integer3Expected + string (", ") + message3Expected + string (", ") + objectId3Expected.getClassId () + string (", ") + objectId3Expected.getInstanceId () + string (", ") + association3Expected.getClassId () + string (", ") + association3Expected.getInstanceId ());
                waveAssert (false, __FILE__, __LINE__);

                status = WAVE_MESSAGE_ERROR;
                break;
            }
        }

        if (WAVE_MESSAGE_SUCCESS == status)
        {
            trace (TRACE_LEVEL_DEVEL, "    All Queried results were successfully compared against expected values.");
        }
    }

    for (i = 0; i < numberOfResults; i++)
    {
        delete ((*pResults)[i]);
    }

    delete pResults;

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::deleteAllCreatedObjects3TestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Delete All Created Objects3 Transaction Test ...");

    ResourceId                                status                  = WAVE_MESSAGE_SUCCESS;
    UI32                                      i                       = 0;
    vector<WaveTestManagedObject1 *>        &allCreatedObjects       = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjects1Map   = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    vector<WaveTestManagedObject3 *>        &allCreatedObjects3      = pFrameworkPersistenceTestContext->getCreatedObjects3 ();
    map<ObjectId, WaveTestManagedObject3 *> &allCreatedObjects3Map   = pFrameworkPersistenceTestContext->getCreatedObjects3Map ();
    UI32                                      numberOfObjectsCreated  = allCreatedObjects.size ();
    UI32                                      numberOfObjectsCreated3 = allCreatedObjects3.size ();

    startTransaction ();

    for (i = 0; i < numberOfObjectsCreated3; i++)
    {
        delete allCreatedObjects3[i];
    }

    for (i = 0; i < numberOfObjectsCreated; i++)
    {
        delete allCreatedObjects[i];
    }

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::deleteAllCreatedObjects3TestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }

    allCreatedObjects3.clear ();
    allCreatedObjects3Map.clear ();
    allCreatedObjects.clear ();
    allCreatedObjects1Map.clear ();

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::largeDerivationTransactionTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Large Derivation Transaction Test ...");

    FrameworkTestabilityMessage8      *pFrameworkTestabilityMessage8 = reinterpret_cast<FrameworkTestabilityMessage8 *> (pFrameworkPersistenceTestContext->getPWaveMessage ());
    ResourceId                         status                        = WAVE_MESSAGE_SUCCESS;
    UI32                               numberOfObjectsToCreate       = pFrameworkTestabilityMessage8->getNumberOfObjectsToBeCreated ();
    UI32                               i                             = 0;
    vector<WaveTestManagedObject1 *>        &allCreatedObjects      = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjects1Map  = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    vector<WaveTestManagedObject3 *>        &allCreatedObjects3     = pFrameworkPersistenceTestContext->getCreatedObjects3 ();
    map<ObjectId, WaveTestManagedObject3 *> &allCreatedObjects3Map  = pFrameworkPersistenceTestContext->getCreatedObjects3Map ();

    startTransaction ();

    for (i = 0; i < numberOfObjectsToCreate; i++)
    {
        WaveTestManagedObject1 *pWaveTestManagedObject1 = new WaveTestManagedObject1 (this);
        WaveTestManagedObject3 *pWaveTestManagedObject3 = new WaveTestManagedObject3 (this);

        pWaveTestManagedObject1->setInteger1 (i);
        pWaveTestManagedObject1->setMessage1 ("Test 1");
        pWaveTestManagedObject1->setObjectId1 (ObjectId (i, i));

        pWaveTestManagedObject3->setInteger1 (i);
        pWaveTestManagedObject3->setMessage1 ("Test 31");
        pWaveTestManagedObject3->setObjectId1 (ObjectId (i, i));
        pWaveTestManagedObject3->setInteger3 (i);
        pWaveTestManagedObject3->setMessage3 ("Test 33");
        pWaveTestManagedObject3->setObjectId3 (ObjectId (i, i));
        pWaveTestManagedObject3->setAssociation3 (pWaveTestManagedObject1->getObjectId ());

        allCreatedObjects.push_back (pWaveTestManagedObject1);
        allCreatedObjects1Map[pWaveTestManagedObject1->getObjectId ()] = pWaveTestManagedObject1;
        allCreatedObjects3.push_back (pWaveTestManagedObject3);
        allCreatedObjects3Map[pWaveTestManagedObject3->getObjectId ()] = pWaveTestManagedObject3;
    }

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::largeDerivationTransactionTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleOneToManyAssociationTransactionTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-To-Many Association Transaction Test ...");

        FrameworkTestabilityMessage8         *pFrameworkTestabilityMessage8 = reinterpret_cast<FrameworkTestabilityMessage8 *> (pFrameworkPersistenceTestContext->getPWaveMessage ());
    ResourceId                                status                        = WAVE_MESSAGE_SUCCESS;
    UI32                                      numberOfObjectsToCreate       = pFrameworkTestabilityMessage8->getNumberOfObjectsToBeCreated ();
    UI32                                      i                             = 0;
    vector<WaveTestManagedObject1 *>        &allCreatedObjects             = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjects1Map         = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    vector<WaveTestManagedObject4 *>        &allCreatedObjects4            = pFrameworkPersistenceTestContext->getCreatedObjects4 ();
    map<ObjectId, WaveTestManagedObject4 *> &allCreatedObjects4Map         = pFrameworkPersistenceTestContext->getCreatedObjects4Map ();
    vector<ObjectId>                          tempVector;

    for (i = 0; i < numberOfObjectsToCreate; i++)
    {
        startTransaction ();

        WaveTestManagedObject1 *pWaveTestManagedObject1 = new WaveTestManagedObject1 (this);
        WaveTestManagedObject4 *pWaveTestManagedObject4 = new WaveTestManagedObject4 (this);

        pWaveTestManagedObject1->setInteger1 (i);
        pWaveTestManagedObject1->setMessage1 ("Test 1");
        pWaveTestManagedObject1->setObjectId1 (ObjectId (i, i));

        pWaveTestManagedObject4->setInteger1 (i);
        pWaveTestManagedObject4->setMessage1 ("Test 41");
        pWaveTestManagedObject4->setObjectId1 (ObjectId (i, i));
        pWaveTestManagedObject4->setInteger4 (i);
        pWaveTestManagedObject4->setMessage4 ("Test 44");
        pWaveTestManagedObject4->setObjectId4 (ObjectId (i, i));
        pWaveTestManagedObject4->setAssociation4 (pWaveTestManagedObject1->getObjectId ());

        tempVector.clear ();

        tempVector.push_back (ObjectId (i, i));
        tempVector.push_back (ObjectId (i, i));
        tempVector.push_back (ObjectId (i, i));

        pWaveTestManagedObject4->setObjectIdVector4 (tempVector);

        tempVector.clear ();

        tempVector.push_back (pWaveTestManagedObject1->getObjectId ());
        tempVector.push_back (pWaveTestManagedObject1->getObjectId ());
        tempVector.push_back (pWaveTestManagedObject1->getObjectId ());

        pWaveTestManagedObject4->setAssociationVector4 (tempVector);

        allCreatedObjects.push_back (pWaveTestManagedObject1);
        allCreatedObjects1Map[pWaveTestManagedObject1->getObjectId ()] = pWaveTestManagedObject1;
        allCreatedObjects4.push_back (pWaveTestManagedObject4);
        allCreatedObjects4Map[pWaveTestManagedObject4->getObjectId ()] = pWaveTestManagedObject4;

        status = commitTransaction ();

        if (status != FRAMEWORK_SUCCESS)
        {
            trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::simpleOneToManyAssociationTransactionTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
            break;
        }
        else
        {
            status = WAVE_MESSAGE_SUCCESS;
        }
    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleOneToManyAssociationQueryTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-Many Association Query Test ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject4::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleOneToManyAssociationQueryTestCallback), pFrameworkPersistenceTestContext);

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults ((pFrameworkPersistenceTestContext->getCreatedObjects4 ()).size ());

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleOneToManyAssociationQueryTestCallback (WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext)
{
    FrameworkPersistenceTestContext          *pFrameworkPersistenceTestContext = reinterpret_cast<FrameworkPersistenceTestContext *> (pWaveManagedObjectQueryContext->getPCallerContext ());
    ResourceId                                status                           = pWaveManagedObjectQueryContext->getCompletionStatus ();
    map<ObjectId, WaveTestManagedObject4 *> &allCreatedObjects4Map            = pFrameworkPersistenceTestContext->getCreatedObjects4Map ();

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::simpleOneToManyAssociationQueryTestCallback : Simple One-To-Many Association Query test failed. Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        vector<WaveManagedObject *> *pResults = pWaveManagedObjectQueryContext->getPResults ();

        waveAssert (NULL != pResults, __FILE__, __LINE__);

        UI32 numberOfExpectedResults = pFrameworkPersistenceTestContext->getNumberOfExpectedResults ();
        UI32 numberOfResults = pResults->size ();
        UI32 i               = 0;

        if (numberOfExpectedResults != numberOfResults)
        {
            trace (TRACE_LEVEL_FATAL, string ("FrameworkTestability4ObjectManager::simpleOneToManyAssociationQueryTestCallback : We did not get expected number of results.  Expected = ") + numberOfExpectedResults + string (", Obtained =  ") + numberOfResults);
            waveAssert (false, __FILE__, __LINE__);
            status = WAVE_MESSAGE_ERROR;
        }
        else
        {
            trace (TRACE_LEVEL_DEVEL, string ("    Number of Results (asynchronously obtained) = ") + numberOfResults);

            for (i = 0; i < numberOfResults; i++)
            {
                WaveTestManagedObject4 *pWaveTestManagedObject4         = dynamic_cast<WaveTestManagedObject4 *> ((*pResults)[i]);
                waveAssert (NULL != pWaveTestManagedObject4, __FILE__, __LINE__);
                ObjectId                 oid                              = pWaveTestManagedObject4->getObjectId  ();
                UI32                     integer1                         = pWaveTestManagedObject4->getInteger1  ();
                string                   message1                         = pWaveTestManagedObject4->getMessage1  ();
                ObjectId                 objectId1                        = pWaveTestManagedObject4->getObjectId1 ();
                UI32                     integer4                         = pWaveTestManagedObject4->getInteger4  ();
                string                   message4                         = pWaveTestManagedObject4->getMessage4  ();
                ObjectId                 objectId4                        = pWaveTestManagedObject4->getObjectId4 ();
                ObjectId                 association4                     = pWaveTestManagedObject4->getAssociation4 ();

                WaveTestManagedObject4 *pWaveTestManagedObject4Expected = allCreatedObjects4Map[oid];
                ObjectId                 oidExpected                      = pWaveTestManagedObject4Expected->getObjectId  ();
                UI32                     integer1Expected                 = pWaveTestManagedObject4Expected->getInteger1  ();
                string                   message1Expected                 = pWaveTestManagedObject4Expected->getMessage1  ();
                ObjectId                 objectId1Expected                = pWaveTestManagedObject4Expected->getObjectId1 ();
                UI32                     integer4Expected                 = pWaveTestManagedObject4Expected->getInteger4  ();
                string                   message4Expected                 = pWaveTestManagedObject4Expected->getMessage4  ();
                ObjectId                 objectId4Expected                = pWaveTestManagedObject4Expected->getObjectId4 ();
                ObjectId                 association4Expected             = pWaveTestManagedObject4Expected->getAssociation4 ();

                if ((*pWaveTestManagedObject4Expected) != (*pWaveTestManagedObject4))
                {
                    trace (TRACE_LEVEL_ERROR, string ("Got      : ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer1 + string (", ") + message1 + string (", ") + objectId1.getClassId () + string (", ") + objectId1.getInstanceId () + string (", ") + integer4 + string (", ") + message4 + string (", ") + objectId4.getClassId () + string (", ") + objectId4.getInstanceId () + string (", ") + association4.getClassId () + string (", ") + association4.getInstanceId ());
                    trace (TRACE_LEVEL_ERROR, string ("Expected : ") + oidExpected.getClassId () + string (", ") + oidExpected.getInstanceId () + string (", ") + integer1Expected + string (", ") + message1Expected + string (", ") + objectId1Expected.getClassId () + string (", ") + objectId1Expected.getInstanceId () + string (", ") + integer4Expected + string (", ") + message4Expected + string (", ") + objectId4Expected.getClassId () + string (", ") + objectId4Expected.getInstanceId () + string (", ") + association4Expected.getClassId () + string (", ") + association4Expected.getInstanceId ());
                    waveAssert (false, __FILE__, __LINE__);

                    status = WAVE_MESSAGE_ERROR;
                    break;
                }
            }

            if (WAVE_MESSAGE_SUCCESS == status)
            {
                trace (TRACE_LEVEL_DEVEL, "    All Queried results were successfully compared against expected values.");
            }
        }
    }

    delete pWaveManagedObjectQueryContext;

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleOneToManyAssociationQueryByObjectIdsTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-Many Association Query By ObjectIds Test ...");

    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject4::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleOneToManyAssociationQueryTestCallback), pFrameworkPersistenceTestContext);

    // Now add the ObjectIds to the context so that the query gets only the requested objects.

    vector<WaveTestManagedObject4 *> &allCreatedObjects4        = pFrameworkPersistenceTestContext->getCreatedObjects4 ();
    UI32                               numberOfObjectsCreated4   = allCreatedObjects4.size ();
    UI32                               numberOfObjectsToQueryFor = numberOfObjectsCreated4 > 100 ? 100 : numberOfObjectsCreated4;
    UI32                               i                         = 0;

    for (i = 0; i < numberOfObjectsToQueryFor; i++)
    {
        pWaveManagedObjectQueryContext->addObjectId ((allCreatedObjects4[i])->getObjectId ());
    }

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults (numberOfObjectsToQueryFor);

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleOneToManyAssociationSynchronousQueryTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-Many Association Synchronous Query Test ...");

    map<ObjectId, WaveTestManagedObject4 *> &allCreatedObjects4Map = pFrameworkPersistenceTestContext->getCreatedObjects4Map ();
    vector<WaveManagedObject *>             *pResults              = querySynchronously (WaveTestManagedObject4::getClassName ());

    waveAssert (NULL != pResults, __FILE__, __LINE__);

    UI32       numberOfExpectedResults = (pFrameworkPersistenceTestContext->getCreatedObjects4 ()).size ();
    UI32       numberOfResults         = pResults->size ();
    UI32       i                        = 0;
    ResourceId status                   = WAVE_MESSAGE_SUCCESS;

    trace (TRACE_LEVEL_DEVEL, string ("    Number of Results (synchronously obtained) = ") + numberOfResults);

    if (numberOfExpectedResults != numberOfResults)
    {
        trace (TRACE_LEVEL_FATAL, string ("FrameworkTestability4ObjectManager::simpleOneToManyAssociationSynchronousQueryTestStep : We did not get expected number of results.  Expected = ") + numberOfExpectedResults + string (", Obtained =  ") + numberOfResults);
        waveAssert (false, __FILE__, __LINE__);
        status = WAVE_MESSAGE_ERROR;
    }
    else
    {
        for (i = 0; i < numberOfResults; i++)
        {
            WaveTestManagedObject4 *pWaveTestManagedObject4         = dynamic_cast<WaveTestManagedObject4 *> ((*pResults)[i]);
            waveAssert (NULL != pWaveTestManagedObject4, __FILE__, __LINE__);
            ObjectId                 oid                              = pWaveTestManagedObject4->getObjectId  ();
            UI32                     integer1                         = pWaveTestManagedObject4->getInteger1  ();
            string                   message1                         = pWaveTestManagedObject4->getMessage1  ();
            ObjectId                 objectId1                        = pWaveTestManagedObject4->getObjectId1 ();
            UI32                     integer4                         = pWaveTestManagedObject4->getInteger4  ();
            string                   message4                         = pWaveTestManagedObject4->getMessage4  ();
            ObjectId                 objectId4                        = pWaveTestManagedObject4->getObjectId4 ();
            ObjectId                 association4                     = pWaveTestManagedObject4->getAssociation4 ();

            WaveTestManagedObject4 *pWaveTestManagedObject4Expected = allCreatedObjects4Map[oid];
            ObjectId                 oidExpected                      = pWaveTestManagedObject4Expected->getObjectId  ();
            UI32                     integer1Expected                 = pWaveTestManagedObject4Expected->getInteger1  ();
            string                   message1Expected                 = pWaveTestManagedObject4Expected->getMessage1  ();
            ObjectId                 objectId1Expected                = pWaveTestManagedObject4Expected->getObjectId1 ();
            UI32                     integer4Expected                 = pWaveTestManagedObject4Expected->getInteger4  ();
            string                   message4Expected                 = pWaveTestManagedObject4Expected->getMessage4  ();
            ObjectId                 objectId4Expected                = pWaveTestManagedObject4Expected->getObjectId4 ();
            ObjectId                 association4Expected             = pWaveTestManagedObject4Expected->getAssociation4 ();

            if ((*pWaveTestManagedObject4Expected) != (*pWaveTestManagedObject4))
            {
                trace (TRACE_LEVEL_ERROR, string ("Got      : ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer1 + string (", ") + message1 + string (", ") + objectId1.getClassId () + string (", ") + objectId1.getInstanceId () + string (", ") + integer4 + string (", ") + message4 + string (", ") + objectId4.getClassId () + string (", ") + objectId4.getInstanceId () + string (", ") + association4.getClassId () + string (", ") + association4.getInstanceId ());
                trace (TRACE_LEVEL_ERROR, string ("Expected : ") + oidExpected.getClassId () + string (", ") + oidExpected.getInstanceId () + string (", ") + integer1Expected + string (", ") + message1Expected + string (", ") + objectId1Expected.getClassId () + string (", ") + objectId1Expected.getInstanceId () + string (", ") + integer4Expected + string (", ") + message4Expected + string (", ") + objectId4Expected.getClassId () + string (", ") + objectId4Expected.getInstanceId () + string (", ") + association4Expected.getClassId () + string (", ") + association4Expected.getInstanceId ());
                waveAssert (false, __FILE__, __LINE__);

                status = WAVE_MESSAGE_ERROR;
                break;
            }
        }

        if (WAVE_MESSAGE_SUCCESS == status)
        {
            trace (TRACE_LEVEL_DEVEL, "    All Queried results were successfully compared against expected values.");
        }
    }

    for (i = 0; i < numberOfResults; i++)
    {
        delete ((*pResults)[i]);
    }

    delete pResults;

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleOneToManyAssociationSynchronousQueryByObjectIdsTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-Many Association Synchronous Query By ObjectIds Test ...");

    // Now add the ObjectIds to the context so that the query gets only the requested objects.

    vector<WaveTestManagedObject4 *>        &allCreatedObjects4       = pFrameworkPersistenceTestContext->getCreatedObjects4 ();
    map<ObjectId, WaveTestManagedObject4 *> &allCreatedObjects4Map    = pFrameworkPersistenceTestContext->getCreatedObjects4Map ();
    UI32                                     numberOfObjectsCreated4   = allCreatedObjects4.size ();
    UI32                                     numberOfObjectsToQueryFor = numberOfObjectsCreated4 > 100 ? 100 : numberOfObjectsCreated4;
    UI32                                     i                         = 0;
    vector<ObjectId>                         objectIds;

    for (i = 0; i < numberOfObjectsToQueryFor; i++)
    {
        objectIds.push_back ((allCreatedObjects4[i])->getObjectId ());
    }

    vector<WaveManagedObject *> *pResults = querySynchronously (WaveTestManagedObject4::getClassName (), objectIds);

    waveAssert (NULL != pResults, __FILE__, __LINE__);

    UI32       numberOfExpectedResults = numberOfObjectsToQueryFor;
    UI32       numberOfResults         = pResults->size ();
    ResourceId status                  = WAVE_MESSAGE_SUCCESS;

    trace (TRACE_LEVEL_DEVEL, string ("    Number of Results (synchronously obtained) = ") + numberOfResults);

    if (numberOfExpectedResults != numberOfResults)
    {
        trace (TRACE_LEVEL_FATAL, string ("FrameworkTestability4ObjectManager::simpleOneToManyAssociationSynchronousQueryByObjectIdsTestStep : We did not get expected number of results.  Expected = ") + numberOfExpectedResults + string (", Obtained =  ") + numberOfResults);
        waveAssert (false, __FILE__, __LINE__);
        status = WAVE_MESSAGE_ERROR;
    }
    else
    {
        for (i = 0; i < numberOfResults; i++)
        {
            WaveTestManagedObject4 *pWaveTestManagedObject4         = dynamic_cast<WaveTestManagedObject4 *> ((*pResults)[i]);
            waveAssert (NULL != pWaveTestManagedObject4, __FILE__, __LINE__);
            ObjectId                 oid                              = pWaveTestManagedObject4->getObjectId  ();
            UI32                     integer1                         = pWaveTestManagedObject4->getInteger1  ();
            string                   message1                         = pWaveTestManagedObject4->getMessage1  ();
            ObjectId                 objectId1                        = pWaveTestManagedObject4->getObjectId1 ();
            UI32                     integer4                         = pWaveTestManagedObject4->getInteger4  ();
            string                   message4                         = pWaveTestManagedObject4->getMessage4  ();
            ObjectId                 objectId4                        = pWaveTestManagedObject4->getObjectId4 ();
            ObjectId                 association4                     = pWaveTestManagedObject4->getAssociation4 ();

            WaveTestManagedObject4 *pWaveTestManagedObject4Expected = allCreatedObjects4Map[oid];
            ObjectId                 oidExpected                      = pWaveTestManagedObject4Expected->getObjectId  ();
            UI32                     integer1Expected                 = pWaveTestManagedObject4Expected->getInteger1  ();
            string                   message1Expected                 = pWaveTestManagedObject4Expected->getMessage1  ();
            ObjectId                 objectId1Expected                = pWaveTestManagedObject4Expected->getObjectId1 ();
            UI32                     integer4Expected                 = pWaveTestManagedObject4Expected->getInteger4  ();
            string                   message4Expected                 = pWaveTestManagedObject4Expected->getMessage4  ();
            ObjectId                 objectId4Expected                = pWaveTestManagedObject4Expected->getObjectId4 ();
            ObjectId                 association4Expected             = pWaveTestManagedObject4Expected->getAssociation4 ();

            if ((*pWaveTestManagedObject4Expected) != (*pWaveTestManagedObject4))
            {
                trace (TRACE_LEVEL_ERROR, string ("Got      : ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer1 + string (", ") + message1 + string (", ") + objectId1.getClassId () + string (", ") + objectId1.getInstanceId () + string (", ") + integer4 + string (", ") + message4 + string (", ") + objectId4.getClassId () + string (", ") + objectId4.getInstanceId () + string (", ") + association4.getClassId () + string (", ") + association4.getInstanceId ());
                trace (TRACE_LEVEL_ERROR, string ("Expected : ") + oidExpected.getClassId () + string (", ") + oidExpected.getInstanceId () + string (", ") + integer1Expected + string (", ") + message1Expected + string (", ") + objectId1Expected.getClassId () + string (", ") + objectId1Expected.getInstanceId () + string (", ") + integer4Expected + string (", ") + message4Expected + string (", ") + objectId4Expected.getClassId () + string (", ") + objectId4Expected.getInstanceId () + string (", ") + association4Expected.getClassId () + string (", ") + association4Expected.getInstanceId ());
                waveAssert (false, __FILE__, __LINE__);

                status = WAVE_MESSAGE_ERROR;
                break;
            }
        }

        if (WAVE_MESSAGE_SUCCESS == status)
        {
            trace (TRACE_LEVEL_DEVEL, "    All Queried results were successfully compared against expected values.");
        }
    }

    for (i = 0; i < numberOfResults; i++)
    {
        delete ((*pResults)[i]);
    }

    delete pResults;

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleOneToManyAssociationUpdateTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-To-Many Association Update Test ...");

    ResourceId                         status                  = WAVE_MESSAGE_SUCCESS;
    UI32                               i                       = 0;
    vector<WaveTestManagedObject1 *>  &allCreatedObjects      = pFrameworkPersistenceTestContext->getCreatedObjects ();
    vector<WaveTestManagedObject4 *>  &allCreatedObjects4     = pFrameworkPersistenceTestContext->getCreatedObjects4 ();
    UI32                               numberOfObjectsCreated4 = allCreatedObjects4.size ();
    vector<ObjectId>                   tempVector;

    for (i = 0; i < numberOfObjectsCreated4; i++)
    {
        startTransaction ();

        WaveTestManagedObject1 *pWaveTestManagedObject1 = allCreatedObjects[i];
        WaveTestManagedObject4 *pWaveTestManagedObject4 = allCreatedObjects4[i];

        waveAssert (NULL != pWaveTestManagedObject4, __FILE__, __LINE__);

        updateWaveManagedObject (pWaveTestManagedObject4);

        pWaveTestManagedObject4->setInteger1 (i);
        pWaveTestManagedObject4->setMessage1 ("Test 41 Update");
        pWaveTestManagedObject4->setObjectId1 (ObjectId (i, i));
        pWaveTestManagedObject4->setInteger4 (i);
        pWaveTestManagedObject4->setMessage4 ("Test 44 Update");
        pWaveTestManagedObject4->setObjectId4 (ObjectId (i + 5000, i + 5000));
        pWaveTestManagedObject4->setAssociation4 (pWaveTestManagedObject1->getObjectId ());

        tempVector.clear ();

        tempVector.push_back (ObjectId (i + 100, i + 100));
        tempVector.push_back (ObjectId (i + 100, i + 100));
        tempVector.push_back (ObjectId (i + 100, i + 100));

        pWaveTestManagedObject4->setObjectIdVector4 (tempVector);

        tempVector.clear ();

        tempVector.push_back (pWaveTestManagedObject1->getObjectId ());
        tempVector.push_back (pWaveTestManagedObject1->getObjectId ());
        tempVector.push_back (pWaveTestManagedObject1->getObjectId ());

        pWaveTestManagedObject4->setAssociationVector4 (tempVector);

        status = commitTransaction ();

        if (status != FRAMEWORK_SUCCESS)
        {
            trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::simpleOneToManyAssociationUpdateTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
            break;
        }
        else
        {
            status = WAVE_MESSAGE_SUCCESS;
        }

    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::deleteOneToManyAssociationWithDeletionContextTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Delete One To Many Association With Deletion Context Test ...");

    ResourceId                          status                  = WAVE_MESSAGE_SUCCESS;
    vector<WaveTestManagedObject4 *>   &allCreatedObjects4     = pFrameworkPersistenceTestContext->getCreatedObjects4 ();

    WaveManagedObjectSynchronousQueryContextForDeletion *syncQueryCtxt = new WaveManagedObjectSynchronousQueryContextForDeletion (WaveTestManagedObject4::getClassName ());
    UI32 integer = 0;
    // Sets 'WHERE interger4=0' in the SQL DELETE query.
    syncQueryCtxt->addAndAttribute (new AttributeUI32 (&integer, "integer4"));

    startTransaction ();

    deleteMultipleWaveManagedObjects (syncQueryCtxt);

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::deleteOneToManyAssociationWithDeletionContextTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }
    delete (allCreatedObjects4[0]);
    allCreatedObjects4.erase (allCreatedObjects4.begin () + 0);

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::deleteOneToOneAssociationWithDeletionContextTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Delete One To One Association With Deletion Context Test ...");

    ResourceId                          status                      = WAVE_MESSAGE_SUCCESS;
    vector<WaveTestManagedObject2 *>   &allCreatedObjects2         = pFrameworkPersistenceTestContext->getCreatedObjects2 ();
    map<ObjectId, WaveTestManagedObject2 *> &allCreatedObjects2Map = pFrameworkPersistenceTestContext->getCreatedObjects2Map ();
    UI32                                numberOfObjectsCreated2     = allCreatedObjects2.size ();
    UI32                                i                           = 0;

    WaveManagedObjectSynchronousQueryContextForDeletion *syncQueryCtxt = new WaveManagedObjectSynchronousQueryContextForDeletion (WaveTestManagedObject2::getClassName ());

    // Sets 'WHERE  (message2 LIKE '%Test%')' in the SQL DELETE query.
    syncQueryCtxt->addAndAttribute (new AttributeString ("%Test%", "message2"), "LIKE");

    startTransaction ();

    deleteMultipleWaveManagedObjects (syncQueryCtxt);

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::deleteOneToOneAssociationWithDeletionContextTestStep: Transaction failed.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }

    for (i = 0; i < numberOfObjectsCreated2; i++)
    {
        delete allCreatedObjects2[i];
    }
    allCreatedObjects2.clear ();
    allCreatedObjects2Map.clear ();

    // Cleanup the associated data too
    vector<WaveTestManagedObject1 *>        &allCreatedObjects       = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjectsMap    = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    UI32                                      numberOfObjectsCreated  = allCreatedObjects.size ();

    startTransaction ();

    for (i = 0; i < numberOfObjectsCreated; i++)
    {
        delete allCreatedObjects[i];
    }

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::deleteOneToOneAssociationWithDeletionContextTestStep: Transaction failed.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }

    allCreatedObjects.clear ();
    allCreatedObjectsMap.clear ();

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::deleteAllCreatedObjects4TestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Delete All Created Objects4 Transaction Test ...");

    ResourceId                         status                  = WAVE_MESSAGE_SUCCESS;
    UI32                               i                       = 0;
    vector<WaveTestManagedObject1 *> &allCreatedObjects       = pFrameworkPersistenceTestContext->getCreatedObjects ();
    vector<WaveTestManagedObject4 *> &allCreatedObjects4      = pFrameworkPersistenceTestContext->getCreatedObjects4 ();
    UI32                               numberOfObjectsCreated  = allCreatedObjects.size ();
    UI32                               numberOfObjectsCreated4 = allCreatedObjects4.size ();

    startTransaction ();

    for (i = 0; i < numberOfObjectsCreated4; i++)
    {
        delete allCreatedObjects4[i];
    }

    for (i = 0; i < numberOfObjectsCreated; i++)
    {
        delete allCreatedObjects[i];
    }

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::deleteAllCreatedObjects4TestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }

    allCreatedObjects4.clear ();
    allCreatedObjects.clear ();

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::largeOneToManyAssociationTransactionTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Large One-To-Many Association Transaction Test ...");

    FrameworkTestabilityMessage8             *pFrameworkTestabilityMessage8 = reinterpret_cast<FrameworkTestabilityMessage8 *> (pFrameworkPersistenceTestContext->getPWaveMessage ());
    ResourceId                                status                        = WAVE_MESSAGE_SUCCESS;
    UI32                                      numberOfObjectsToCreate       = pFrameworkTestabilityMessage8->getNumberOfObjectsToBeCreated ();
    UI32                                      i                             = 0;
    vector<WaveTestManagedObject1 *>        &allCreatedObjects             = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjects1Map         = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    vector<WaveTestManagedObject4 *>        &allCreatedObjects4            = pFrameworkPersistenceTestContext->getCreatedObjects4 ();
    map<ObjectId, WaveTestManagedObject4 *> &allCreatedObjects4Map         = pFrameworkPersistenceTestContext->getCreatedObjects4Map ();
    vector<ObjectId>                          tempVector;

    startTransaction ();

    for (i = 0; i < numberOfObjectsToCreate; i++)
    {
        WaveTestManagedObject1 *pWaveTestManagedObject1 = new WaveTestManagedObject1 (this);
        WaveTestManagedObject4 *pWaveTestManagedObject4 = new WaveTestManagedObject4 (this);

        pWaveTestManagedObject1->setInteger1 (i);
        pWaveTestManagedObject1->setMessage1 ("Test 1");
        pWaveTestManagedObject1->setObjectId1 (ObjectId (i, i));

        pWaveTestManagedObject4->setInteger1 (i);
        pWaveTestManagedObject4->setMessage1 ("Test 41");
        pWaveTestManagedObject4->setObjectId1 (ObjectId (i, i));
        pWaveTestManagedObject4->setInteger4 (i);
        pWaveTestManagedObject4->setMessage4 ("Test 44");
        pWaveTestManagedObject4->setObjectId4 (ObjectId (i, i));
        pWaveTestManagedObject4->setAssociation4 (pWaveTestManagedObject1->getObjectId ());

        tempVector.clear ();

        tempVector.push_back (ObjectId (i, i));
        tempVector.push_back (ObjectId (i, i));
        tempVector.push_back (ObjectId (i, i));

        pWaveTestManagedObject4->setObjectIdVector4 (tempVector);

        tempVector.clear ();

        tempVector.push_back (pWaveTestManagedObject1->getObjectId ());
        tempVector.push_back (pWaveTestManagedObject1->getObjectId ());
        tempVector.push_back (pWaveTestManagedObject1->getObjectId ());

        pWaveTestManagedObject4->setAssociationVector4 (tempVector);

        allCreatedObjects.push_back (pWaveTestManagedObject1);
        allCreatedObjects1Map[pWaveTestManagedObject1->getObjectId ()] = pWaveTestManagedObject1;
        allCreatedObjects4.push_back (pWaveTestManagedObject4);
        allCreatedObjects4Map[pWaveTestManagedObject4->getObjectId ()] = pWaveTestManagedObject4;
    }

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::largeOneToManyAssociationTransactionTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleOneToManyMultipleAssociationsInHierarchyTransactionTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-To-Many Muiltiple Associations In Hierarchy Transaction Test ...");

        FrameworkTestabilityMessage8         *pFrameworkTestabilityMessage8 = reinterpret_cast<FrameworkTestabilityMessage8 *> (pFrameworkPersistenceTestContext->getPWaveMessage ());
    ResourceId                                status                        = WAVE_MESSAGE_SUCCESS;
    UI32                                      numberOfObjectsToCreate       = pFrameworkTestabilityMessage8->getNumberOfObjectsToBeCreated ();
    UI32                                      i                             = 0;
    vector<WaveTestManagedObject1 *>        &allCreatedObjects             = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjects1Map         = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    vector<WaveTestManagedObject5 *>        &allCreatedObjects5            = pFrameworkPersistenceTestContext->getCreatedObjects5 ();
    map<ObjectId, WaveTestManagedObject5 *> &allCreatedObjects5Map         = pFrameworkPersistenceTestContext->getCreatedObjects5Map ();
    vector<ObjectId>                          tempVector;

    for (i = 0; i < numberOfObjectsToCreate; i++)
    {
        startTransaction ();

        WaveTestManagedObject1 *pWaveTestManagedObject1 = new WaveTestManagedObject1 (this);
        WaveTestManagedObject5 *pWaveTestManagedObject5 = new WaveTestManagedObject5 (this);

        pWaveTestManagedObject1->setInteger1 (i);
        pWaveTestManagedObject1->setMessage1 ("Test 1");
        pWaveTestManagedObject1->setObjectId1 (ObjectId (i, i));

        pWaveTestManagedObject5->setInteger1 (i);
        pWaveTestManagedObject5->setMessage1 ("Test 41");
        pWaveTestManagedObject5->setObjectId1 (ObjectId (i, i));
        pWaveTestManagedObject5->setInteger4 (i);
        pWaveTestManagedObject5->setMessage4 ("Test 44");
        pWaveTestManagedObject5->setObjectId4 (ObjectId (i, i));
        pWaveTestManagedObject5->setAssociation4 (pWaveTestManagedObject1->getObjectId ());

        tempVector.clear ();

        tempVector.push_back (ObjectId (i, i));
        tempVector.push_back (ObjectId (i, i));
        tempVector.push_back (ObjectId (i, i));

        pWaveTestManagedObject5->setObjectIdVector4 (tempVector);

        tempVector.clear ();

        tempVector.push_back (pWaveTestManagedObject1->getObjectId ());
        tempVector.push_back (pWaveTestManagedObject1->getObjectId ());
        tempVector.push_back (pWaveTestManagedObject1->getObjectId ());

        pWaveTestManagedObject5->setAssociationVector4 (tempVector);

        pWaveTestManagedObject5->setAssociationVector5 (tempVector);

        allCreatedObjects.push_back (pWaveTestManagedObject1);
        allCreatedObjects1Map[pWaveTestManagedObject1->getObjectId ()] = pWaveTestManagedObject1;
        allCreatedObjects5.push_back (pWaveTestManagedObject5);
        allCreatedObjects5Map[pWaveTestManagedObject5->getObjectId ()] = pWaveTestManagedObject5;

        status = commitTransaction ();

        if (status != FRAMEWORK_SUCCESS)
        {
            trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::simpleOneToManyMultipleAssociationsInHierarchyTransactionTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
            break;
        }
        else
        {
            status = WAVE_MESSAGE_SUCCESS;
        }
    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleOneToManyMultipleAssociationsInHierarchyQueryTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-To-Many Muiltiple Associations In Hierarchy Query Test ...");

    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject5::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleOneToManyMultipleAssociationsInHierarchyQueryTestCallback), pFrameworkPersistenceTestContext);

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults ((pFrameworkPersistenceTestContext->getCreatedObjects5 ()).size ());

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleOneToManyMultipleAssociationsInHierarchyQueryTestCallback (WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext)
{
    FrameworkPersistenceTestContext          *pFrameworkPersistenceTestContext = reinterpret_cast<FrameworkPersistenceTestContext *> (pWaveManagedObjectQueryContext->getPCallerContext ());
    ResourceId                                status                           = pWaveManagedObjectQueryContext->getCompletionStatus ();
    map<ObjectId, WaveTestManagedObject5 *> &allCreatedObjects5Map            = pFrameworkPersistenceTestContext->getCreatedObjects5Map ();

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::simpleOneToManyMultipleAssociationsInHierarchyQueryTestCallback : Simple One-To-Many Muiltiple Associations In Hierarchy Query test failed. Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        vector<WaveManagedObject *> *pResults = pWaveManagedObjectQueryContext->getPResults ();

        waveAssert (NULL != pResults, __FILE__, __LINE__);

        UI32 numberOfExpectedResults = pFrameworkPersistenceTestContext->getNumberOfExpectedResults ();
        UI32 numberOfResults = pResults->size ();
        UI32 i               = 0;

        if (numberOfExpectedResults != numberOfResults)
        {
            trace (TRACE_LEVEL_FATAL, string ("FrameworkTestability4ObjectManager::simpleOneToManyMultipleAssociationsInHierarchyQueryTestCallback : We did not get expected number of results.  Expected = ") + numberOfExpectedResults + string (", Obtained =  ") + numberOfResults);
            waveAssert (false, __FILE__, __LINE__);
            status = WAVE_MESSAGE_ERROR;
        }
        else
        {
            trace (TRACE_LEVEL_DEVEL, string ("    Number of Results (asynchronously obtained) = ") + numberOfResults);

            for (i = 0; i < numberOfResults; i++)
            {
                WaveTestManagedObject5 *pWaveTestManagedObject5         = dynamic_cast<WaveTestManagedObject5 *> ((*pResults)[i]);
                waveAssert (NULL != pWaveTestManagedObject5, __FILE__, __LINE__);
                ObjectId                 oid                              = pWaveTestManagedObject5->getObjectId  ();
                UI32                     integer1                         = pWaveTestManagedObject5->getInteger1  ();
                string                   message1                         = pWaveTestManagedObject5->getMessage1  ();
                ObjectId                 objectId1                        = pWaveTestManagedObject5->getObjectId1 ();
                UI32                     integer4                         = pWaveTestManagedObject5->getInteger4  ();
                string                   message4                         = pWaveTestManagedObject5->getMessage4  ();
                ObjectId                 objectId4                        = pWaveTestManagedObject5->getObjectId4 ();
                ObjectId                 association4                     = pWaveTestManagedObject5->getAssociation4 ();

                WaveTestManagedObject5 *pWaveTestManagedObject5Expected = allCreatedObjects5Map[oid];
                ObjectId                 oidExpected                      = pWaveTestManagedObject5Expected->getObjectId  ();
                UI32                     integer1Expected                 = pWaveTestManagedObject5Expected->getInteger1  ();
                string                   message1Expected                 = pWaveTestManagedObject5Expected->getMessage1  ();
                ObjectId                 objectId1Expected                = pWaveTestManagedObject5Expected->getObjectId1 ();
                UI32                     integer4Expected                 = pWaveTestManagedObject5Expected->getInteger4  ();
                string                   message4Expected                 = pWaveTestManagedObject5Expected->getMessage4  ();
                ObjectId                 objectId4Expected                = pWaveTestManagedObject5Expected->getObjectId4 ();
                ObjectId                 association4Expected             = pWaveTestManagedObject5Expected->getAssociation4 ();

                if ((*pWaveTestManagedObject5Expected) != (*pWaveTestManagedObject5))
                {
                    trace (TRACE_LEVEL_ERROR, string ("Got      : ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer1 + string (", ") + message1 + string (", ") + objectId1.getClassId () + string (", ") + objectId1.getInstanceId () + string (", ") + integer4 + string (", ") + message4 + string (", ") + objectId4.getClassId () + string (", ") + objectId4.getInstanceId () + string (", ") + association4.getClassId () + string (", ") + association4.getInstanceId ());
                    trace (TRACE_LEVEL_ERROR, string ("Expected : ") + oidExpected.getClassId () + string (", ") + oidExpected.getInstanceId () + string (", ") + integer1Expected + string (", ") + message1Expected + string (", ") + objectId1Expected.getClassId () + string (", ") + objectId1Expected.getInstanceId () + string (", ") + integer4Expected + string (", ") + message4Expected + string (", ") + objectId4Expected.getClassId () + string (", ") + objectId4Expected.getInstanceId () + string (", ") + association4Expected.getClassId () + string (", ") + association4Expected.getInstanceId ());
                    waveAssert (false, __FILE__, __LINE__);

                    status = WAVE_MESSAGE_ERROR;
                    break;
                }
            }

            if (WAVE_MESSAGE_SUCCESS == status)
            {
                trace (TRACE_LEVEL_DEVEL, "    All Queried results were successfully compared against expected values.");
            }
        }
    }

    delete pWaveManagedObjectQueryContext;

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleOneToManyMultipleAssociationsInHierarchyQueryByObjectIdsTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-To-Many Muiltiple Associations In Hierarchy Query By ObjectIds Test ...");

    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject5::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleOneToManyMultipleAssociationsInHierarchyQueryTestCallback), pFrameworkPersistenceTestContext);

    // Now add the ObjectIds to the context so that the query gets only the requested objects.

    vector<WaveTestManagedObject5 *> &allCreatedObjects5        = pFrameworkPersistenceTestContext->getCreatedObjects5 ();
    UI32                               numberOfObjectsCreated5   = allCreatedObjects5.size ();
    UI32                               numberOfObjectsToQueryFor = numberOfObjectsCreated5 > 100 ? 100 : numberOfObjectsCreated5;
    UI32                               i                         = 0;

    for (i = 0; i < numberOfObjectsToQueryFor; i++)
    {
        pWaveManagedObjectQueryContext->addObjectId ((allCreatedObjects5[i])->getObjectId ());
    }

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults (numberOfObjectsToQueryFor);

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleOneToManyMultipleAssociationsInHierarchySynchronousQueryTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-To-Many Muiltiple Associations In Hierarchy Synchronous Query Test ...");

    map<ObjectId, WaveTestManagedObject5 *> &allCreatedObjects5Map = pFrameworkPersistenceTestContext->getCreatedObjects5Map ();
    vector<WaveManagedObject *>             *pResults              = querySynchronously (WaveTestManagedObject5::getClassName ());

    waveAssert (NULL != pResults, __FILE__, __LINE__);

    UI32       numberOfExpectedResults = (pFrameworkPersistenceTestContext->getCreatedObjects5 ()).size ();
    UI32       numberOfResults         = pResults->size ();
    UI32       i                        = 0;
    ResourceId status                   = WAVE_MESSAGE_SUCCESS;

    trace (TRACE_LEVEL_DEVEL, string ("    Number of Results (synchronously obtained) = ") + numberOfResults);

    if (numberOfExpectedResults != numberOfResults)
    {
        trace (TRACE_LEVEL_FATAL, string ("FrameworkTestability4ObjectManager::simpleOneToManyMultipleAssociationsInHierarchySynchronousQueryTestStep : We did not get expected number of results.  Expected = ") + numberOfExpectedResults + string (", Obtained =  ") + numberOfResults);
        waveAssert (false, __FILE__, __LINE__);
        status = WAVE_MESSAGE_ERROR;
    }
    else
    {
        for (i = 0; i < numberOfResults; i++)
        {
            WaveTestManagedObject5 *pWaveTestManagedObject5         = dynamic_cast<WaveTestManagedObject5 *> ((*pResults)[i]);
            waveAssert (NULL != pWaveTestManagedObject5, __FILE__, __LINE__);
            ObjectId                 oid                              = pWaveTestManagedObject5->getObjectId  ();
            UI32                     integer1                         = pWaveTestManagedObject5->getInteger1  ();
            string                   message1                         = pWaveTestManagedObject5->getMessage1  ();
            ObjectId                 objectId1                        = pWaveTestManagedObject5->getObjectId1 ();
            UI32                     integer4                         = pWaveTestManagedObject5->getInteger4  ();
            string                   message4                         = pWaveTestManagedObject5->getMessage4  ();
            ObjectId                 objectId4                        = pWaveTestManagedObject5->getObjectId4 ();
            ObjectId                 association4                     = pWaveTestManagedObject5->getAssociation4 ();

            WaveTestManagedObject5 *pWaveTestManagedObject5Expected = allCreatedObjects5Map[oid];
            ObjectId                 oidExpected                      = pWaveTestManagedObject5Expected->getObjectId  ();
            UI32                     integer1Expected                 = pWaveTestManagedObject5Expected->getInteger1  ();
            string                   message1Expected                 = pWaveTestManagedObject5Expected->getMessage1  ();
            ObjectId                 objectId1Expected                = pWaveTestManagedObject5Expected->getObjectId1 ();
            UI32                     integer4Expected                 = pWaveTestManagedObject5Expected->getInteger4  ();
            string                   message4Expected                 = pWaveTestManagedObject5Expected->getMessage4  ();
            ObjectId                 objectId4Expected                = pWaveTestManagedObject5Expected->getObjectId4 ();
            ObjectId                 association4Expected             = pWaveTestManagedObject5Expected->getAssociation4 ();

            if ((*pWaveTestManagedObject5Expected) != (*pWaveTestManagedObject5))
            {
                trace (TRACE_LEVEL_ERROR, string ("Got      : ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer1 + string (", ") + message1 + string (", ") + objectId1.getClassId () + string (", ") + objectId1.getInstanceId () + string (", ") + integer4 + string (", ") + message4 + string (", ") + objectId4.getClassId () + string (", ") + objectId4.getInstanceId () + string (", ") + association4.getClassId () + string (", ") + association4.getInstanceId ());
                trace (TRACE_LEVEL_ERROR, string ("Expected : ") + oidExpected.getClassId () + string (", ") + oidExpected.getInstanceId () + string (", ") + integer1Expected + string (", ") + message1Expected + string (", ") + objectId1Expected.getClassId () + string (", ") + objectId1Expected.getInstanceId () + string (", ") + integer4Expected + string (", ") + message4Expected + string (", ") + objectId4Expected.getClassId () + string (", ") + objectId4Expected.getInstanceId () + string (", ") + association4Expected.getClassId () + string (", ") + association4Expected.getInstanceId ());
                waveAssert (false, __FILE__, __LINE__);

                status = WAVE_MESSAGE_ERROR;
                break;
            }
        }

        if (WAVE_MESSAGE_SUCCESS == status)
        {
            trace (TRACE_LEVEL_DEVEL, "    All Queried results were successfully compared against expected values.");
        }
    }

    for (i = 0; i < numberOfResults; i++)
    {
        delete ((*pResults)[i]);
    }

    delete pResults;

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleOneToManyMultipleAssociationsInHierarchySynchronousQueryByObjectIdsTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-To-Many Muiltiple Associations In Hierarchy Synchronous Query By ObjectIds Test ...");

    // Now add the ObjectIds to the context so that the query gets only the requested objects.

    vector<WaveTestManagedObject5 *>        &allCreatedObjects5       = pFrameworkPersistenceTestContext->getCreatedObjects5 ();
    map<ObjectId, WaveTestManagedObject5 *> &allCreatedObjects5Map    = pFrameworkPersistenceTestContext->getCreatedObjects5Map ();
    UI32                                     numberOfObjectsCreated5   = allCreatedObjects5.size ();
    UI32                                     numberOfObjectsToQueryFor = numberOfObjectsCreated5 > 100 ? 100 : numberOfObjectsCreated5;
    UI32                                     i                         = 0;
    vector<ObjectId>                         objectIds;

    for (i = 0; i < numberOfObjectsToQueryFor; i++)
    {
        objectIds.push_back ((allCreatedObjects5[i])->getObjectId ());
    }

    vector<WaveManagedObject *> *pResults = querySynchronously (WaveTestManagedObject5::getClassName (), objectIds);

    waveAssert (NULL != pResults, __FILE__, __LINE__);

    UI32       numberOfExpectedResults = numberOfObjectsToQueryFor;
    UI32       numberOfResults         = pResults->size ();
    ResourceId status                  = WAVE_MESSAGE_SUCCESS;

    trace (TRACE_LEVEL_DEVEL, string ("    Number of Results (synchronously obtained) = ") + numberOfResults);

    if (numberOfExpectedResults != numberOfResults)
    {
        trace (TRACE_LEVEL_FATAL, string ("FrameworkTestability4ObjectManager::simpleOneToManyMultipleAssociationsInHierarchySynchronousQueryByObjectIdsTestStep : We did not get expected number of results.  Expected = ") + numberOfExpectedResults + string (", Obtained =  ") + numberOfResults);
        waveAssert (false, __FILE__, __LINE__);
        status = WAVE_MESSAGE_ERROR;
    }
    else
    {
        for (i = 0; i < numberOfResults; i++)
        {
            WaveTestManagedObject5 *pWaveTestManagedObject5         = dynamic_cast<WaveTestManagedObject5 *> ((*pResults)[i]);
            waveAssert (NULL != pWaveTestManagedObject5, __FILE__, __LINE__);
            ObjectId                 oid                              = pWaveTestManagedObject5->getObjectId  ();
            UI32                     integer1                         = pWaveTestManagedObject5->getInteger1  ();
            string                   message1                         = pWaveTestManagedObject5->getMessage1  ();
            ObjectId                 objectId1                        = pWaveTestManagedObject5->getObjectId1 ();
            UI32                     integer4                         = pWaveTestManagedObject5->getInteger4  ();
            string                   message4                         = pWaveTestManagedObject5->getMessage4  ();
            ObjectId                 objectId4                        = pWaveTestManagedObject5->getObjectId4 ();
            ObjectId                 association4                     = pWaveTestManagedObject5->getAssociation4 ();

            WaveTestManagedObject5 *pWaveTestManagedObject5Expected = allCreatedObjects5Map[oid];
            ObjectId                 oidExpected                      = pWaveTestManagedObject5Expected->getObjectId  ();
            UI32                     integer1Expected                 = pWaveTestManagedObject5Expected->getInteger1  ();
            string                   message1Expected                 = pWaveTestManagedObject5Expected->getMessage1  ();
            ObjectId                 objectId1Expected                = pWaveTestManagedObject5Expected->getObjectId1 ();
            UI32                     integer4Expected                 = pWaveTestManagedObject5Expected->getInteger4  ();
            string                   message4Expected                 = pWaveTestManagedObject5Expected->getMessage4  ();
            ObjectId                 objectId4Expected                = pWaveTestManagedObject5Expected->getObjectId4 ();
            ObjectId                 association4Expected             = pWaveTestManagedObject5Expected->getAssociation4 ();

            if ((*pWaveTestManagedObject5Expected) != (*pWaveTestManagedObject5))
            {
                trace (TRACE_LEVEL_ERROR, string ("Got      : ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer1 + string (", ") + message1 + string (", ") + objectId1.getClassId () + string (", ") + objectId1.getInstanceId () + string (", ") + integer4 + string (", ") + message4 + string (", ") + objectId4.getClassId () + string (", ") + objectId4.getInstanceId () + string (", ") + association4.getClassId () + string (", ") + association4.getInstanceId ());
                trace (TRACE_LEVEL_ERROR, string ("Expected : ") + oidExpected.getClassId () + string (", ") + oidExpected.getInstanceId () + string (", ") + integer1Expected + string (", ") + message1Expected + string (", ") + objectId1Expected.getClassId () + string (", ") + objectId1Expected.getInstanceId () + string (", ") + integer4Expected + string (", ") + message4Expected + string (", ") + objectId4Expected.getClassId () + string (", ") + objectId4Expected.getInstanceId () + string (", ") + association4Expected.getClassId () + string (", ") + association4Expected.getInstanceId ());
                waveAssert (false, __FILE__, __LINE__);

                status = WAVE_MESSAGE_ERROR;
                break;
            }
        }

        if (WAVE_MESSAGE_SUCCESS == status)
        {
            trace (TRACE_LEVEL_DEVEL, "    All Queried results were successfully compared against expected values.");
        }
    }

    for (i = 0; i < numberOfResults; i++)
    {
        delete ((*pResults)[i]);
    }

    delete pResults;

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::deleteAllCreatedObjects5TestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Delete All Created Objects5 Transaction Test ...");

    ResourceId                         status                  = WAVE_MESSAGE_SUCCESS;
    UI32                               i                       = 0;
    vector<WaveTestManagedObject1 *> &allCreatedObjects       = pFrameworkPersistenceTestContext->getCreatedObjects ();
    vector<WaveTestManagedObject5 *> &allCreatedObjects5      = pFrameworkPersistenceTestContext->getCreatedObjects5 ();
    UI32                               numberOfObjectsCreated  = allCreatedObjects.size ();
    UI32                               numberOfObjectsCreated5 = allCreatedObjects5.size ();

    startTransaction ();

    for (i = 0; i < numberOfObjectsCreated5; i++)
    {
        delete allCreatedObjects5[i];
    }

    for (i = 0; i < numberOfObjectsCreated; i++)
    {
        delete allCreatedObjects[i];
    }

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::deleteAllCreatedObjects5TestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }

    allCreatedObjects5.clear ();
    allCreatedObjects.clear ();

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::largeOneToManyMultipleAssociationsInHierarchyTransactionTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Large One-To-Many Muiltiple Associations In Hierarchy Transaction Test ...");

        FrameworkTestabilityMessage8         *pFrameworkTestabilityMessage8 = reinterpret_cast<FrameworkTestabilityMessage8 *> (pFrameworkPersistenceTestContext->getPWaveMessage ());
    ResourceId                                status                        = WAVE_MESSAGE_SUCCESS;
    UI32                                      numberOfObjectsToCreate       = pFrameworkTestabilityMessage8->getNumberOfObjectsToBeCreated ();
    UI32                                      i                             = 0;
    vector<WaveTestManagedObject1 *>        &allCreatedObjects             = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjects1Map         = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    vector<WaveTestManagedObject5 *>        &allCreatedObjects5            = pFrameworkPersistenceTestContext->getCreatedObjects5 ();
    map<ObjectId, WaveTestManagedObject5 *> &allCreatedObjects5Map         = pFrameworkPersistenceTestContext->getCreatedObjects5Map ();
    vector<ObjectId>                          tempVector;

    startTransaction ();

    for (i = 0; i < numberOfObjectsToCreate; i++)
    {
        WaveTestManagedObject1 *pWaveTestManagedObject1 = new WaveTestManagedObject1 (this);
        WaveTestManagedObject5 *pWaveTestManagedObject5 = new WaveTestManagedObject5 (this);

        pWaveTestManagedObject1->setInteger1 (i);
        pWaveTestManagedObject1->setMessage1 ("Test 1");
        pWaveTestManagedObject1->setObjectId1 (ObjectId (i, i));

        pWaveTestManagedObject5->setInteger1 (i);
        pWaveTestManagedObject5->setMessage1 ("Test 41");
        pWaveTestManagedObject5->setObjectId1 (ObjectId (i, i));
        pWaveTestManagedObject5->setInteger4 (i);
        pWaveTestManagedObject5->setMessage4 ("Test 44");
        pWaveTestManagedObject5->setObjectId4 (ObjectId (i, i));
        pWaveTestManagedObject5->setAssociation4 (pWaveTestManagedObject1->getObjectId ());

        tempVector.clear ();

        tempVector.push_back (ObjectId (i, i));
        tempVector.push_back (ObjectId (i, i));
        tempVector.push_back (ObjectId (i, i));

        pWaveTestManagedObject5->setObjectIdVector4 (tempVector);

        tempVector.clear ();

        tempVector.push_back (pWaveTestManagedObject1->getObjectId ());
        tempVector.push_back (pWaveTestManagedObject1->getObjectId ());
        tempVector.push_back (pWaveTestManagedObject1->getObjectId ());

        pWaveTestManagedObject5->setAssociationVector4 (tempVector);

        pWaveTestManagedObject5->setAssociationVector5 (tempVector);

        allCreatedObjects.push_back (pWaveTestManagedObject1);
        allCreatedObjects1Map[pWaveTestManagedObject1->getObjectId ()] = pWaveTestManagedObject1;
        allCreatedObjects5.push_back (pWaveTestManagedObject5);
        allCreatedObjects5Map[pWaveTestManagedObject5->getObjectId ()] = pWaveTestManagedObject5;

    }

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::largeOneToManyMultipleAssociationsInHierarchyTransactionTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleOneToOneCompositionTransactionTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-To-One Composition Transaction Test ...");

    FrameworkTestabilityMessage8             *pFrameworkTestabilityMessage8 = reinterpret_cast<FrameworkTestabilityMessage8 *> (pFrameworkPersistenceTestContext->getPWaveMessage ());
    ResourceId                                status                        = WAVE_MESSAGE_SUCCESS;
    UI32                                      numberOfObjectsToCreate       = pFrameworkTestabilityMessage8->getNumberOfObjectsToBeCreated ();
    UI32                                      i                             = 0;
    vector<WaveTestManagedObject1 *>        &allCreatedObjects             = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjects1Map         = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    vector<WaveTestManagedObject6 *>         &allCreatedObjects6            = pFrameworkPersistenceTestContext->getCreatedObjects6 ();
    map<ObjectId, WaveTestManagedObject6 *>  &allCreatedObjects6Map         = pFrameworkPersistenceTestContext->getCreatedObjects6Map ();

    for (i = 0; i < numberOfObjectsToCreate; i++)
    {
        startTransaction ();

        WaveTestManagedObject1 *pWaveTestManagedObject1 = new WaveTestManagedObject1 (this);
        WaveTestManagedObject6 *pWaveTestManagedObject6 = new WaveTestManagedObject6 (this);

        pWaveTestManagedObject1->setInteger1 (i);
        pWaveTestManagedObject1->setMessage1 ("Test");
        pWaveTestManagedObject1->setObjectId1 (ObjectId (i, i));

        pWaveTestManagedObject6->setInteger6 (i);
        pWaveTestManagedObject6->setMessage6 ("Test");
        pWaveTestManagedObject6->setObjectId6 (ObjectId (i, i));
        pWaveTestManagedObject6->setComposition6 (WaveManagedObjectPointer<WaveTestManagedObject1> (pWaveTestManagedObject1));

        allCreatedObjects.push_back (pWaveTestManagedObject1);
        allCreatedObjects1Map[pWaveTestManagedObject1->getObjectId ()] = pWaveTestManagedObject1;
        allCreatedObjects6.push_back (pWaveTestManagedObject6);
        allCreatedObjects6Map[pWaveTestManagedObject6->getObjectId ()] = pWaveTestManagedObject6;

        status = commitTransaction ();

        if (status != FRAMEWORK_SUCCESS)
        {
            trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::simpleOneToOneCompositionTransactionTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
            break;
        }
        else
        {
            status = WAVE_MESSAGE_SUCCESS;
        }
    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleOneToOneCompositionQueryTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-To-One Composition Query Test ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject6::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleOneToOneCompositionQueryTestCallback), pFrameworkPersistenceTestContext);

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults ((pFrameworkPersistenceTestContext->getCreatedObjects6 ()).size ());

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleOneToOneCompositionQueryTestCallback (WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext)
{
    FrameworkPersistenceTestContext          *pFrameworkPersistenceTestContext = reinterpret_cast<FrameworkPersistenceTestContext *> (pWaveManagedObjectQueryContext->getPCallerContext ());
    ResourceId                                status                           = pWaveManagedObjectQueryContext->getCompletionStatus ();
    map<ObjectId, WaveTestManagedObject6 *>  &allCreatedObjects6Map             = pFrameworkPersistenceTestContext->getCreatedObjects6Map ();

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::simpleOneToOneCompositionQueryTestCallback : Simple One-One Composition Query test failed. Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        vector<WaveManagedObject *> *pResults = pWaveManagedObjectQueryContext->getPResults ();

        waveAssert (NULL != pResults, __FILE__, __LINE__);

        UI32 numberOfExpectedResults = pFrameworkPersistenceTestContext->getNumberOfExpectedResults ();
        UI32 numberOfResults = pResults->size ();
        UI32 i               = 0;

        if (numberOfExpectedResults != numberOfResults)
        {
            trace (TRACE_LEVEL_FATAL, string ("FrameworkTestability4ObjectManager::simpleOneToOneCompositionQueryTestCallback : We did not get expected number of results.  Expected = ") + numberOfExpectedResults + string (", Obtained =  ") + numberOfResults);
            waveAssert (false, __FILE__, __LINE__);
            status = WAVE_MESSAGE_ERROR;
        }
        else
        {
            trace (TRACE_LEVEL_DEVEL, string ("    Number of Results (asynchronously obtained) = ") + numberOfResults);

            for (i = 0; i < numberOfResults; i++)
            {
                WaveTestManagedObject6 *pWaveTestManagedObject6         = dynamic_cast<WaveTestManagedObject6 *> ((*pResults)[i]);
                waveAssert (NULL != pWaveTestManagedObject6, __FILE__, __LINE__);
                ObjectId                oid                             = pWaveTestManagedObject6->getObjectId  ();
                UI32                    integer6                        = pWaveTestManagedObject6->getInteger6  ();
                string                  message6                        = pWaveTestManagedObject6->getMessage6  ();
                ObjectId                objectId6                       = pWaveTestManagedObject6->getObjectId6 ();

                WaveTestManagedObject6 *pWaveTestManagedObject6Expected = allCreatedObjects6Map[oid];
                ObjectId                oidExpected                     = pWaveTestManagedObject6Expected->getObjectId  ();
                UI32                    integer6Expected                = pWaveTestManagedObject6Expected->getInteger6  ();
                string                  message6Expected                = pWaveTestManagedObject6Expected->getMessage6  ();
                ObjectId                objectId6Expected               = pWaveTestManagedObject6Expected->getObjectId6 ();

                //trace (TRACE_LEVEL_DEVEL, string ("        ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer2 + string (", ") + message2 + string (", ") + objectId2.getClassId () + string (", ") + objectId2.getInstanceId ());

                if ((*pWaveTestManagedObject6Expected) != (*pWaveTestManagedObject6))
                {
                    trace (TRACE_LEVEL_ERROR, string ("Got      : ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer6 + string (", ") + message6 + string (", ") + objectId6.getClassId () + string (", ") + objectId6.getInstanceId ());
                    trace (TRACE_LEVEL_ERROR, string ("Expected : ") + oidExpected.getClassId () + string (", ") + oidExpected.getInstanceId () + string (", ") + integer6Expected + string (", ") + message6Expected + string (", ") + objectId6Expected.getClassId () + string (", ") + objectId6Expected.getInstanceId ());
                    waveAssert (false, __FILE__, __LINE__);

                    status = WAVE_MESSAGE_ERROR;
                    break;
                }
            }

            if (WAVE_MESSAGE_SUCCESS == status)
            {
                trace (TRACE_LEVEL_DEVEL, "    All Queried results were successfully compared against expected values.");
            }
        }
    }

    delete pWaveManagedObjectQueryContext;

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleOneToOneCompositionUpdateTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-To-One Composition Update Test ...");

    FrameworkTestabilityMessage8             *pFrameworkTestabilityMessage8 = reinterpret_cast<FrameworkTestabilityMessage8 *> (pFrameworkPersistenceTestContext->getPWaveMessage ());
    ResourceId                                status                        = WAVE_MESSAGE_SUCCESS;
    UI32                                      numberOfObjectsToCreate       = pFrameworkTestabilityMessage8->getNumberOfObjectsToBeCreated ();
    UI32                                      i                             = 0;
    vector<WaveTestManagedObject1 *>        &allCreatedObjects             = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjects1Map         = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    vector<WaveTestManagedObject6 *>         &allCreatedObjects6            = pFrameworkPersistenceTestContext->getCreatedObjects6 ();

    allCreatedObjects.clear     ();
    allCreatedObjects1Map.clear ();

    for (i = 0; i < numberOfObjectsToCreate; i++)
    {
        startTransaction ();

        WaveTestManagedObject1 *pWaveTestManagedObject1 = new WaveTestManagedObject1 (this);
        WaveTestManagedObject6 *pWaveTestManagedObject6   = allCreatedObjects6[i];

        pWaveTestManagedObject1->setInteger1 (i * 2);
        pWaveTestManagedObject1->setMessage1 ("Test Update 1");
        pWaveTestManagedObject1->setObjectId1 (ObjectId (i * 2, i * 2));

        updateWaveManagedObject (pWaveTestManagedObject6);

        pWaveTestManagedObject6->setInteger6 (i);
        pWaveTestManagedObject6->setMessage6 ("Test Update 2");
        pWaveTestManagedObject6->setObjectId6 (ObjectId (i * 3, i * 3));
        pWaveTestManagedObject6->setComposition6 (WaveManagedObjectPointer<WaveTestManagedObject1> (pWaveTestManagedObject1));

        allCreatedObjects.push_back (pWaveTestManagedObject1);
        allCreatedObjects1Map[pWaveTestManagedObject1->getObjectId ()] = pWaveTestManagedObject1;

        status = commitTransaction ();

        if (status != FRAMEWORK_SUCCESS)
        {
            trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::simpleOneToOneCompositionUpdateTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
            break;
        }
        else
        {
            status = WAVE_MESSAGE_SUCCESS;
        }
    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::deleteOneToOneCompositionWithDeletionContextTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Delete One To One Compostion With Deletion Context Test ...");

    ResourceId                          status                  = WAVE_MESSAGE_SUCCESS;
    vector<WaveTestManagedObject6 *>    &allCreatedObjects6     = pFrameworkPersistenceTestContext->getCreatedObjects6 ();

    WaveManagedObjectSynchronousQueryContextForDeletion *syncQueryCtxt = new WaveManagedObjectSynchronousQueryContextForDeletion (WaveTestManagedObject6::getClassName ());
    UI32 integer = 0;
    // Sets 'WHERE interger6=0' in the SQL DELETE query.
    syncQueryCtxt->addAndAttribute (new AttributeUI32 (&integer, "integer6"));

    startTransaction ();

    deleteMultipleWaveManagedObjects (syncQueryCtxt);

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::deleteOneToOneCompositionWithDeletionContextTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }
    delete (allCreatedObjects6[0]);
    allCreatedObjects6.erase (allCreatedObjects6.begin () + 0);

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::deleteAllOneToOneCompositionUsingDeleteWaveManagedObjectWithObjectIdTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Delete All One-To-One Composition Using Delete Wave Managed Object With Object Id Test ...");

    ResourceId                                status                  = WAVE_MESSAGE_SUCCESS;
    UI32                                      i                       = 0;
    vector<WaveTestManagedObject1 *>        &allCreatedObjects       = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjectsMap    = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    vector<WaveTestManagedObject6 *>         &allCreatedObjects6      = pFrameworkPersistenceTestContext->getCreatedObjects6 ();
    map<ObjectId, WaveTestManagedObject6 *>  &allCreatedObjects6Map   = pFrameworkPersistenceTestContext->getCreatedObjects6Map ();
    UI32                                      numberOfObjectsCreated6 = allCreatedObjects6.size ();
    
    for (i = 0; i < numberOfObjectsCreated6; i++)
    {
        startTransaction ();

        deleteWaveManagedObject (allCreatedObjects6[i]->getObjectId ());

        status = commitTransaction ();

        if (status != FRAMEWORK_SUCCESS)
        {
            trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::deleteAllOneToOneCompositionUsingDeleteWaveManagedObjectWithObjectIdTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
            break;
        }
        else
        {
            status = WAVE_MESSAGE_SUCCESS;
        }
    }

    allCreatedObjects6.clear ();
    allCreatedObjects6Map.clear ();
    allCreatedObjects.clear ();
    allCreatedObjectsMap.clear ();

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::deleteAllOneToOneCompositionUsingDeleteWaveManagedObjectWithDeletionContextTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Delete All One-To-One Composition Using Delete Wave Managed Object With Deletion Context Test ...");

    ResourceId                                status                  = WAVE_MESSAGE_SUCCESS;
    vector<WaveTestManagedObject1 *>        &allCreatedObjects       = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjectsMap    = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    vector<WaveTestManagedObject6 *>         &allCreatedObjects6      = pFrameworkPersistenceTestContext->getCreatedObjects6 ();
    map<ObjectId, WaveTestManagedObject6 *>  &allCreatedObjects6Map   = pFrameworkPersistenceTestContext->getCreatedObjects6Map ();

    WaveManagedObjectSynchronousQueryContextForDeletion synchronousQueryContextForDeletion (WaveTestManagedObject6::getClassName ());

    synchronousQueryContextForDeletion.addAndAttribute (new AttributeString ("%Test%", "message6"), "LIKE");

    startTransaction ();

    deleteWaveManagedObject (&synchronousQueryContextForDeletion);

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::deleteAllOneToOneCompositionUsingDeleteWaveManagedObjectWithDeletionContextTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }
    
    allCreatedObjects6.clear ();
    allCreatedObjects6Map.clear ();
    allCreatedObjects.clear ();
    allCreatedObjectsMap.clear ();

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::deleteAllCreatedObjects6TestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Delete All Created Objects6 Transaction Test ...");

    ResourceId                                status                  = WAVE_MESSAGE_SUCCESS;
    UI32                                      i                       = 0;
    vector<WaveTestManagedObject1 *>        &allCreatedObjects       = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjectsMap    = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    vector<WaveTestManagedObject6 *>         &allCreatedObjects6      = pFrameworkPersistenceTestContext->getCreatedObjects6 ();
    map<ObjectId, WaveTestManagedObject6 *>  &allCreatedObjects6Map   = pFrameworkPersistenceTestContext->getCreatedObjects6Map ();
    UI32                                      numberOfObjectsCreated6 = allCreatedObjects6.size ();

    startTransaction ();

    for (i = 0; i < numberOfObjectsCreated6; i++)
    {
        delete allCreatedObjects6[i];
    }

    // NOTICE: We must not delete the WaveTestManagedObject1 here since they are owned by the WaveTestManagedObject6.
    //         They are implicitly deleted when the owning WaveTestManagedObject6 are deleted.
    //         If you explicitly delete WaveTestManagedObject1 objects it will result in SIGSEGV!!!

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::deleteAllCreatedObjects6TestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }

    allCreatedObjects6.clear ();
    allCreatedObjects6Map.clear ();
    allCreatedObjects.clear ();
    allCreatedObjectsMap.clear ();

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::largeOneToOneCompositionTransactionTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Large One-To-One Composition Transaction Test ...");

    FrameworkTestabilityMessage8             *pFrameworkTestabilityMessage8 = reinterpret_cast<FrameworkTestabilityMessage8 *> (pFrameworkPersistenceTestContext->getPWaveMessage ());
    ResourceId                                status                        = WAVE_MESSAGE_SUCCESS;
    UI32                                      numberOfObjectsToCreate       = pFrameworkTestabilityMessage8->getNumberOfObjectsToBeCreated ();
    UI32                                      i                             = 0;
    vector<WaveTestManagedObject1 *>        &allCreatedObjects             = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjects1Map         = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    vector<WaveTestManagedObject6 *>         &allCreatedObjects6            = pFrameworkPersistenceTestContext->getCreatedObjects6 ();
    map<ObjectId, WaveTestManagedObject6 *>  &allCreatedObjects6Map         = pFrameworkPersistenceTestContext->getCreatedObjects6Map ();

    startTransaction ();

    for (i = 0; i < numberOfObjectsToCreate; i++)
    {
        WaveTestManagedObject1 *pWaveTestManagedObject1 = new WaveTestManagedObject1 (this);
        WaveTestManagedObject6 *pWaveTestManagedObject6 = new WaveTestManagedObject6 (this);

        pWaveTestManagedObject1->setInteger1 (i);
        pWaveTestManagedObject1->setMessage1 ("Test");
        pWaveTestManagedObject1->setObjectId1 (ObjectId (i, i));

        pWaveTestManagedObject6->setInteger6 (i);
        pWaveTestManagedObject6->setMessage6 ("Test");
        pWaveTestManagedObject6->setObjectId6 (ObjectId (i, i));
        pWaveTestManagedObject6->setComposition6 (WaveManagedObjectPointer<WaveTestManagedObject1> (pWaveTestManagedObject1));

        allCreatedObjects.push_back (pWaveTestManagedObject1);
        allCreatedObjects1Map[pWaveTestManagedObject1->getObjectId ()] = pWaveTestManagedObject1;
        allCreatedObjects6.push_back (pWaveTestManagedObject6);
        allCreatedObjects6Map[pWaveTestManagedObject6->getObjectId ()] = pWaveTestManagedObject6;
    }

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::largeOneToOneCompositionTransactionTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleOneToManyCompositionTransactionTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-To-Many Composition Transaction Test ...");

    FrameworkTestabilityMessage8             *pFrameworkTestabilityMessage8 = reinterpret_cast<FrameworkTestabilityMessage8 *> (pFrameworkPersistenceTestContext->getPWaveMessage ());
    ResourceId                                status                        = WAVE_MESSAGE_SUCCESS;
    UI32                                      numberOfObjectsToCreate       = pFrameworkTestabilityMessage8->getNumberOfObjectsToBeCreated ();
    UI32                                      i                             = 0;
    UI32                                      j                             = 0;
    vector<WaveTestManagedObject1 *>        &allCreatedObjects             = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjects1Map         = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    vector<WaveTestManagedObject7 *>         &allCreatedObjects7            = pFrameworkPersistenceTestContext->getCreatedObjects7 ();
    map<ObjectId, WaveTestManagedObject7 *>  &allCreatedObjects7Map         = pFrameworkPersistenceTestContext->getCreatedObjects7Map ();

    for (i = 0; i < numberOfObjectsToCreate / 10; i++)
    {
        startTransaction ();

        vector <WaveManagedObjectPointer<WaveTestManagedObject1> > tempVector;

        for (j = 0; j < 32; j++)
        {
            WaveTestManagedObject1 *pWaveTestManagedObject1 = new WaveTestManagedObject1 (this);

            pWaveTestManagedObject1->setInteger1 (i * 32 + j);
            pWaveTestManagedObject1->setMessage1 ("Test");
            pWaveTestManagedObject1->setObjectId1 (ObjectId (i * 32 + j, i * 32 + j));

            tempVector.push_back (WaveManagedObjectPointer<WaveTestManagedObject1> (pWaveTestManagedObject1));

            allCreatedObjects.push_back (pWaveTestManagedObject1);
            allCreatedObjects1Map[pWaveTestManagedObject1->getObjectId ()] = pWaveTestManagedObject1;
        }

        WaveTestManagedObject7 *pWaveTestManagedObject7 = new WaveTestManagedObject7 (this);

        pWaveTestManagedObject7->setInteger7 (i);
        pWaveTestManagedObject7->setMessage7 ("Test");
        pWaveTestManagedObject7->setObjectId7 (ObjectId (i, i));
        pWaveTestManagedObject7->setComposition7 (tempVector);

        allCreatedObjects7.push_back (pWaveTestManagedObject7);
        allCreatedObjects7Map[pWaveTestManagedObject7->getObjectId ()] = pWaveTestManagedObject7;

        status = commitTransaction ();

        if (status != FRAMEWORK_SUCCESS)
        {
            trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::simpleOneToManyCompositionTransactionTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
            break;
        }
        else
        {
            status = WAVE_MESSAGE_SUCCESS;
        }

        if (0 == ((i + 1) % 100))
        {
            trace (TRACE_LEVEL_INFO, string ("    Finished ") + (i + 1) + string (" Simple One-To-Many Composition Transactions"));
        }
    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleOneToManyCompositionQueryTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-To-Many Composition Query Test ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject7::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleOneToManyCompositionQueryTestCallback), pFrameworkPersistenceTestContext);

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults ((pFrameworkPersistenceTestContext->getCreatedObjects7 ()).size ());

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleOneToManyCompositionQueryTestCallback (WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext)
{
    FrameworkPersistenceTestContext          *pFrameworkPersistenceTestContext = reinterpret_cast<FrameworkPersistenceTestContext *> (pWaveManagedObjectQueryContext->getPCallerContext ());
    ResourceId                                status                           = pWaveManagedObjectQueryContext->getCompletionStatus ();
    map<ObjectId, WaveTestManagedObject7 *>  &allCreatedObjects7Map             = pFrameworkPersistenceTestContext->getCreatedObjects7Map ();

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::simpleOneToManyCompositionQueryTestCallback : Simple One-Many Composition Query test failed. Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        vector<WaveManagedObject *> *pResults = pWaveManagedObjectQueryContext->getPResults ();

        waveAssert (NULL != pResults, __FILE__, __LINE__);

        UI32 numberOfExpectedResults = pFrameworkPersistenceTestContext->getNumberOfExpectedResults ();
        UI32 numberOfResults = pResults->size ();
        UI32 i               = 0;

        if (numberOfExpectedResults != numberOfResults)
        {
            trace (TRACE_LEVEL_FATAL, string ("FrameworkTestability4ObjectManager::simpleOneToManyCompositionQueryTestCallback : We did not get expected number of results.  Expected = ") + numberOfExpectedResults + string (", Obtained =  ") + numberOfResults);
            waveAssert (false, __FILE__, __LINE__);
            status = WAVE_MESSAGE_ERROR;
        }
        else
        {
            trace (TRACE_LEVEL_DEVEL, string ("    Number of Results (asynchronously obtained) = ") + numberOfResults);

            for (i = 0; i < numberOfResults; i++)
            {
                WaveTestManagedObject7 *pWaveTestManagedObject7         = dynamic_cast<WaveTestManagedObject7 *> ((*pResults)[i]);
                waveAssert (NULL != pWaveTestManagedObject7, __FILE__, __LINE__);
                ObjectId                oid                             = pWaveTestManagedObject7->getObjectId  ();
                UI32                    integer7                        = pWaveTestManagedObject7->getInteger7  ();
                string                  message7                        = pWaveTestManagedObject7->getMessage7  ();
                ObjectId                objectId7                       = pWaveTestManagedObject7->getObjectId7 ();

                WaveTestManagedObject7 *pWaveTestManagedObject7Expected = allCreatedObjects7Map[oid];
                ObjectId                oidExpected                     = pWaveTestManagedObject7Expected->getObjectId  ();
                UI32                    integer7Expected                = pWaveTestManagedObject7Expected->getInteger7  ();
                string                  message7Expected                = pWaveTestManagedObject7Expected->getMessage7  ();
                ObjectId                objectId7Expected               = pWaveTestManagedObject7Expected->getObjectId7 ();

                //trace (TRACE_LEVEL_DEVEL, string ("        ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer2 + string (", ") + message2 + string (", ") + objectId2.getClassId () + string (", ") + objectId2.getInstanceId ());

                if ((*pWaveTestManagedObject7Expected) != (*pWaveTestManagedObject7))
                {
                    trace (TRACE_LEVEL_ERROR, string ("Got      : ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer7+ string (", ") + message7 + string (", ") + objectId7.getClassId () + string (", ") + objectId7.getInstanceId ());
                    trace (TRACE_LEVEL_ERROR, string ("Expected : ") + oidExpected.getClassId () + string (", ") + oidExpected.getInstanceId () + string (", ") + integer7Expected + string (", ") + message7Expected + string (", ") + objectId7Expected.getClassId () + string (", ") + objectId7Expected.getInstanceId ());
                    waveAssert (false, __FILE__, __LINE__);

                    status = WAVE_MESSAGE_ERROR;
                    break;
                }
            }

            if (WAVE_MESSAGE_SUCCESS == status)
            {
                trace (TRACE_LEVEL_DEVEL, "    All Queried results were successfully compared against expected values.");
            }
        }
    }

    delete pWaveManagedObjectQueryContext;

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleOneToManyCompositionUpdateTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-To-Many Composition Update Test ...");

    FrameworkTestabilityMessage8             *pFrameworkTestabilityMessage8 = reinterpret_cast<FrameworkTestabilityMessage8 *> (pFrameworkPersistenceTestContext->getPWaveMessage ());
    ResourceId                                status                        = WAVE_MESSAGE_SUCCESS;
    UI32                                      numberOfObjectsToCreate       = pFrameworkTestabilityMessage8->getNumberOfObjectsToBeCreated ();
    UI32                                      i                             = 0;
    UI32                                      j                             = 0;
    vector<WaveTestManagedObject1 *>        &allCreatedObjects             = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjects1Map         = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    vector<WaveTestManagedObject7 *>         &allCreatedObjects7            = pFrameworkPersistenceTestContext->getCreatedObjects7 ();

    allCreatedObjects.clear     ();
    allCreatedObjects1Map.clear ();

    for (i = 0; i < numberOfObjectsToCreate / 10; i++)
    {
        startTransaction ();

        vector <WaveManagedObjectPointer<WaveTestManagedObject1> > tempVector;

        for (j = 0; j < 32; j++)
        {
            WaveTestManagedObject1 *pWaveTestManagedObject1 = new WaveTestManagedObject1 (this);

            pWaveTestManagedObject1->setInteger1 ((i * 32 + j) + 100);
            pWaveTestManagedObject1->setMessage1 ("Test Update 1");
            pWaveTestManagedObject1->setObjectId1 (ObjectId ((i * 32 + j) * 2, (i * 32 + j) * 2));

            tempVector.push_back (WaveManagedObjectPointer<WaveTestManagedObject1> (pWaveTestManagedObject1));

            allCreatedObjects.push_back (pWaveTestManagedObject1);
            allCreatedObjects1Map[pWaveTestManagedObject1->getObjectId ()] = pWaveTestManagedObject1;
        }

        WaveTestManagedObject7 *pWaveTestManagedObject7 = allCreatedObjects7[i];

        updateWaveManagedObject (pWaveTestManagedObject7);

        pWaveTestManagedObject7->setInteger7 (i + i);
        pWaveTestManagedObject7->setMessage7 ("Test Update 2");
        pWaveTestManagedObject7->setObjectId7 (ObjectId (i + i, i + i));
        pWaveTestManagedObject7->setComposition7 (tempVector);

        status = commitTransaction ();

        if (status != FRAMEWORK_SUCCESS)
        {
            trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::simpleOneToManyCompositionTransactionTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
            break;
        }
        else
        {
            status = WAVE_MESSAGE_SUCCESS;
        }

        if (0 == ((i + 1) % 100))
        {
            trace (TRACE_LEVEL_INFO, string ("    Finished ") + (i + 1) + string (" Simple One-To-Many Composition Transactions"));
        }
    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::deleteAllOneToManyCompositionUsingDeleteWaveManagedObjectWithObjectIdTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Delete All One-To-Many Composition Using Delete Wave Managed Object With Object Id Test ...");

    ResourceId                                status                  = WAVE_MESSAGE_SUCCESS;
    UI32                                      i                       = 0;
    vector<WaveTestManagedObject1 *>        &allCreatedObjects       = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjectsMap    = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    vector<WaveTestManagedObject7 *>         &allCreatedObjects7      = pFrameworkPersistenceTestContext->getCreatedObjects7 ();
    map<ObjectId, WaveTestManagedObject7 *>  &allCreatedObjects7Map   = pFrameworkPersistenceTestContext->getCreatedObjects7Map ();
    UI32                                      numberOfObjectsCreated7 = allCreatedObjects7.size ();

    for (i = 0; i < numberOfObjectsCreated7; i++)
    {
        startTransaction ();
        
        deleteWaveManagedObject (allCreatedObjects7[i]->getObjectId ());    

        status = commitTransaction ();
        
        if (status != FRAMEWORK_SUCCESS)
        {
            trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::deleteAllOneToManyCompositionUsingDeleteWaveManagedObjectWithObjectIdTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
            break;
        }
        else
        {
            status = WAVE_MESSAGE_SUCCESS;
        }
    }
    
    allCreatedObjects7.clear ();
    allCreatedObjects7Map.clear ();
    allCreatedObjects.clear ();
    allCreatedObjectsMap.clear ();

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::deleteAllOneToManyCompositionUsingDeleteWaveManagedObjectWithDeletionContextTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Delete All One-To-Many Composition Using Delete Wave Managed Object With Deletion Context Test ...");

    vector<WaveTestManagedObject1 *>        &allCreatedObjects       = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjectsMap    = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    vector<WaveTestManagedObject7 *>         &allCreatedObjects7      = pFrameworkPersistenceTestContext->getCreatedObjects7 ();
    map<ObjectId, WaveTestManagedObject7 *>  &allCreatedObjects7Map   = pFrameworkPersistenceTestContext->getCreatedObjects7Map ();
    ResourceId                                status                  = WAVE_MESSAGE_SUCCESS;

    WaveManagedObjectSynchronousQueryContextForDeletion synchronousQueryContextForDeletion (WaveTestManagedObject7::getClassName ());

    synchronousQueryContextForDeletion.addAndAttribute (new AttributeString ("%Test%", "message7"), "LIKE");

    startTransaction ();

    deleteWaveManagedObject (&synchronousQueryContextForDeletion);

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::deleteAllOneToManyCompositionUsingDeleteWaveManagedObjectWithDeletionContextTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }
    
    allCreatedObjects7.clear ();
    allCreatedObjects7Map.clear ();
    allCreatedObjects.clear ();
    allCreatedObjectsMap.clear ();

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::deleteManagedObjectCompositionsOneToManyTestStep (
        FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Delete one-to-many compositions of Managed Objects Test ...");

    ResourceId status = WAVE_MESSAGE_SUCCESS;

    WaveManagedObjectSynchronousQueryContextForDeletion *synchronousQueryContextForDeletion  =
            new WaveManagedObjectSynchronousQueryContextForDeletion(WaveTestManagedObject7::getClassName ());
    synchronousQueryContextForDeletion->addAndAttribute (new AttributeString ("%Test%", "message7"), "LIKE");

    set <string> compositions;
    compositions.insert(string("composition7"));

    startTransaction ();

    deleteManagedObjectCompositions (synchronousQueryContextForDeletion, compositions);

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::deleteCompositionsFromManagedObjectTestStep : Transaction failed.  Status : "
                + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }

    // Remove the objects that are expected to be deleted, from the test context.
    pFrameworkPersistenceTestContext->getCreatedObjects().clear ();
    pFrameworkPersistenceTestContext->getCreatedObjectsMap().clear ();

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleOneToOneToOneCompositionTransactionTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-To-One-To-One Composition Transaction Test ...");

    FrameworkTestabilityMessage8             *pFrameworkTestabilityMessage8 = reinterpret_cast<FrameworkTestabilityMessage8 *> (pFrameworkPersistenceTestContext->getPWaveMessage ());
    ResourceId                                status                        = WAVE_MESSAGE_SUCCESS;
    UI32                                      numberOfObjectsToCreate       = pFrameworkTestabilityMessage8->getNumberOfObjectsToBeCreated ();
    UI32                                      i                             = 0;
    vector<WaveTestManagedObject1 *>        &allCreatedObjects             = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjects1Map         = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    vector<WaveTestManagedObject6 *>         &allCreatedObjects6            = pFrameworkPersistenceTestContext->getCreatedObjects6 ();
    map<ObjectId, WaveTestManagedObject6 *>  &allCreatedObjects6Map         = pFrameworkPersistenceTestContext->getCreatedObjects6Map ();
    vector<WaveTestManagedObject10 *>        &allCreatedObjects10           = pFrameworkPersistenceTestContext->getCreatedObjects10 ();
    map<ObjectId, WaveTestManagedObject10 *> &allCreatedObjects10Map         = pFrameworkPersistenceTestContext->getCreatedObjects10Map ();

    for (i = 0; i < numberOfObjectsToCreate; i++)
    {
        startTransaction ();

        WaveTestManagedObject1 *pWaveTestManagedObject1 = new WaveTestManagedObject1 (this);
        WaveTestManagedObject6  *pWaveTestManagedObject6  = new WaveTestManagedObject6 (this);
        WaveTestManagedObject10 *pWaveTestManagedObject10 = new WaveTestManagedObject10 (this);

        pWaveTestManagedObject1->setInteger1 (i);
        pWaveTestManagedObject1->setMessage1 ("Test");
        pWaveTestManagedObject1->setObjectId1 (ObjectId (i, i));

        pWaveTestManagedObject6->setInteger6 (i);
        pWaveTestManagedObject6->setMessage6 ("Test");
        pWaveTestManagedObject6->setObjectId6 (ObjectId (i, i));
        pWaveTestManagedObject6->setComposition6 (WaveManagedObjectPointer<WaveTestManagedObject1> (pWaveTestManagedObject1));

        pWaveTestManagedObject10->setInteger10 (i);
        pWaveTestManagedObject10->setMessage10 ("Test");
        pWaveTestManagedObject10->setComposition10 (WaveManagedObjectPointer<WaveTestManagedObject6> (pWaveTestManagedObject6));

        allCreatedObjects.push_back (pWaveTestManagedObject1);
        allCreatedObjects1Map[pWaveTestManagedObject1->getObjectId ()] = pWaveTestManagedObject1;
        allCreatedObjects6.push_back (pWaveTestManagedObject6);
        allCreatedObjects6Map[pWaveTestManagedObject6->getObjectId ()] = pWaveTestManagedObject6;
        allCreatedObjects10.push_back (pWaveTestManagedObject10);
        allCreatedObjects10Map[pWaveTestManagedObject10->getObjectId ()] = pWaveTestManagedObject10;

        status = commitTransaction ();

        if (status != FRAMEWORK_SUCCESS)
        {
            trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::simpleOneToOneCompositionTransactionTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
            break;
        }
        else
        {
            status = WAVE_MESSAGE_SUCCESS;
        }
    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleOneToOneToOneCompositionQueryTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-To-One-To-One Composition Query Test ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject10::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleOneToOneToOneCompositionQueryTestCallback), pFrameworkPersistenceTestContext);

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults ((pFrameworkPersistenceTestContext->getCreatedObjects10 ()).size ());

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleOneToOneToOneCompositionQueryTestCallback (WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext)
{
    FrameworkPersistenceTestContext          *pFrameworkPersistenceTestContext = reinterpret_cast<FrameworkPersistenceTestContext *> (pWaveManagedObjectQueryContext->getPCallerContext ());
    ResourceId                                status                           = pWaveManagedObjectQueryContext->getCompletionStatus ();
    map<ObjectId, WaveTestManagedObject10 *>  &allCreatedObjects10Map          = pFrameworkPersistenceTestContext->getCreatedObjects10Map ();

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::simpleOneToOneToOneCompositionQueryTestCallback : Simple One-One-One Composition Query test failed. Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        vector<WaveManagedObject *> *pResults = pWaveManagedObjectQueryContext->getPResults ();

        waveAssert (NULL != pResults, __FILE__, __LINE__);

        UI32 numberOfExpectedResults = pFrameworkPersistenceTestContext->getNumberOfExpectedResults ();
        UI32 numberOfResults = pResults->size ();
        UI32 i               = 0;

        if (numberOfExpectedResults != numberOfResults)
        {
            trace (TRACE_LEVEL_FATAL, string ("FrameworkTestability4ObjectManager::simpleOneToOneToOneCompositionQueryTestCallback : We did not get expected number of results.  Expected = ") + numberOfExpectedResults + string (", Obtained =  ") + numberOfResults);
            waveAssert (false, __FILE__, __LINE__);
            status = WAVE_MESSAGE_ERROR;
        }
        else
        {
            trace (TRACE_LEVEL_DEVEL, string ("    Number of Results (asynchronously obtained) = ") + numberOfResults);

            for (i = 0; i < numberOfResults; i++)
            {
                WaveTestManagedObject10 *pWaveTestManagedObject10         = dynamic_cast<WaveTestManagedObject10 *> ((*pResults)[i]);
                waveAssert (NULL != pWaveTestManagedObject10, __FILE__, __LINE__);
                ObjectId                oid                             = pWaveTestManagedObject10->getObjectId  ();
                UI32                    integer10                        = pWaveTestManagedObject10->getInteger10  ();
                string                  message10                        = pWaveTestManagedObject10->getMessage10  ();

                WaveTestManagedObject10 *pWaveTestManagedObject10Expected = allCreatedObjects10Map[oid];
                ObjectId                oidExpected                     = pWaveTestManagedObject10Expected->getObjectId  ();
                UI32                    integer10Expected               = pWaveTestManagedObject10Expected->getInteger10 ();
                string                  message10Expected               = pWaveTestManagedObject10Expected->getMessage10 ();

                //trace (TRACE_LEVEL_DEVEL, string ("        ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer2 + string (", ") + message2 + string (", ") + objectId2.getClassId () + string (", ") + objectId2.getInstanceId ());

                if ((*pWaveTestManagedObject10Expected) != (*pWaveTestManagedObject10))
                {
                    trace (TRACE_LEVEL_ERROR, string ("Got      : ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer10 + string (", ") + message10);
                    trace (TRACE_LEVEL_ERROR, string ("Expected : ") + oidExpected.getClassId () + string (", ") + oidExpected.getInstanceId () + string (", ") + integer10Expected + string (", ") + message10Expected);
                    waveAssert (false, __FILE__, __LINE__);

                    status = WAVE_MESSAGE_ERROR;
                    break;
                }
            }

            if (WAVE_MESSAGE_SUCCESS == status)
            {
                trace (TRACE_LEVEL_DEVEL, "    All Queried results were successfully compared against expected values.");
            }
        }
    }

    delete pWaveManagedObjectQueryContext;

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::deleteAllOneToOneToOneCompositionUsingDeleteMultipleWaveManagedObjectsWithDeletionContextTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Delete All One-To-One-To-One Composition Using Delete Multiple Wave Managed Objects With Deletion Context Test ...");
    
    vector<WaveTestManagedObject1 *>        &allCreatedObjects       = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjectsMap    = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    vector<WaveTestManagedObject6 *>         &allCreatedObjects6      = pFrameworkPersistenceTestContext->getCreatedObjects6 ();
    map<ObjectId, WaveTestManagedObject6 *>  &allCreatedObjects6Map   = pFrameworkPersistenceTestContext->getCreatedObjects6Map ();
    vector<WaveTestManagedObject10 *>        &allCreatedObjects10     = pFrameworkPersistenceTestContext->getCreatedObjects10 ();
    map<ObjectId, WaveTestManagedObject10 *> &allCreatedObjects10Map  = pFrameworkPersistenceTestContext->getCreatedObjects10Map ();
    ResourceId                               status                   = WAVE_MESSAGE_SUCCESS;

    WaveManagedObjectSynchronousQueryContextForDeletion *synchronousQueryContextForDeletion  = new WaveManagedObjectSynchronousQueryContextForDeletion(WaveTestManagedObject10::getClassName ());

    // Sets 'WHERE  (message10 LIKE '%Test%')' in the SQL DELETE query.
    synchronousQueryContextForDeletion->addAndAttribute (new AttributeString ("%Test%", "message10"), "LIKE");

    startTransaction ();

    deleteMultipleWaveManagedObjects (synchronousQueryContextForDeletion);

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::deleteAllOneToOneToOneCompositionUsingDeleteMultipleWaveManagedObjectsWithDeletionContextTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }

    allCreatedObjects10.clear ();
    allCreatedObjects10Map.clear ();
    allCreatedObjects6.clear ();
    allCreatedObjects6Map.clear ();
    allCreatedObjects.clear ();
    allCreatedObjectsMap.clear ();

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleOneToManyToManyCompositionTransactionTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-To-Many-To-Many Composition Transaction Test ...");

    ResourceId                                status                        = WAVE_MESSAGE_SUCCESS;
    UI32                                      i                             = 0;
    UI32                                      j                             = 0;
    UI32                                      k                             = 0;
    vector<WaveTestManagedObject1 *>        &allCreatedObjects             = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjects1Map         = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    vector<WaveTestManagedObject3 *>        &allCreatedObjects3            = pFrameworkPersistenceTestContext->getCreatedObjects3 ();
    map<ObjectId, WaveTestManagedObject3 *> &allCreatedObjects3Map         = pFrameworkPersistenceTestContext->getCreatedObjects3Map ();
    vector<WaveTestManagedObject7 *>         &allCreatedObjects7            = pFrameworkPersistenceTestContext->getCreatedObjects7 ();
    map<ObjectId, WaveTestManagedObject7 *>  &allCreatedObjects7Map         = pFrameworkPersistenceTestContext->getCreatedObjects7Map ();
    vector<WaveTestManagedObject11 *>        &allCreatedObjects11           = pFrameworkPersistenceTestContext->getCreatedObjects11 ();
    map<ObjectId, WaveTestManagedObject11 *> &allCreatedObjects11Map        = pFrameworkPersistenceTestContext->getCreatedObjects11Map ();

    for (i = 0; i < 2; i++)
    {
        startTransaction ();

        vector <WaveManagedObjectPointer<WaveTestManagedObject7> > tempVector1;
        for (k = 0; k < 2; k++)
        {
            vector <WaveManagedObjectPointer<WaveTestManagedObject1> > tempVector;

            for (j = 0; j < 2; j++)
            {
                WaveTestManagedObject1 *pWaveTestManagedObject1 = new WaveTestManagedObject1 (this);

                pWaveTestManagedObject1->setInteger1 (i * 2 * 2 + k * 2 + j);
                pWaveTestManagedObject1->setMessage1 ("Test");
                pWaveTestManagedObject1->setObjectId1 (ObjectId (i * 2 * 2 + k * 2 +  j, i * 2 * 2 + k * 2 + j));

                tempVector.push_back (WaveManagedObjectPointer<WaveTestManagedObject1> (pWaveTestManagedObject1));

                allCreatedObjects.push_back (pWaveTestManagedObject1);
                allCreatedObjects1Map[pWaveTestManagedObject1->getObjectId ()] = pWaveTestManagedObject1;

                WaveTestManagedObject3 *pWaveTestManagedObject3 = new WaveTestManagedObject3 (this);

                pWaveTestManagedObject3->setInteger3 (i * 2 * 2 + k * 2 + j);
                pWaveTestManagedObject3->setMessage3 ("Test");
                pWaveTestManagedObject3->setObjectId3 (ObjectId (i * 2 * 2 + k * 2 +  j, i * 2 * 2 + k * 2 + j));
                pWaveTestManagedObject3->setAssociation3 (pWaveTestManagedObject1->getObjectId ());

                tempVector.push_back (WaveManagedObjectPointer<WaveTestManagedObject1> (pWaveTestManagedObject3));

                allCreatedObjects3.push_back (pWaveTestManagedObject3);
                allCreatedObjects3Map[pWaveTestManagedObject3->getObjectId ()] = pWaveTestManagedObject3;
            }

            WaveTestManagedObject7 *pWaveTestManagedObject7 = new WaveTestManagedObject7 (this);

            pWaveTestManagedObject7->setInteger7 (i * 2 + k);
            pWaveTestManagedObject7->setMessage7 ("Test");
            pWaveTestManagedObject7->setObjectId7 (ObjectId (i * 2 + k, i * 2 + k));
            pWaveTestManagedObject7->setComposition7 (tempVector);

            tempVector1.push_back (WaveManagedObjectPointer<WaveTestManagedObject7> (pWaveTestManagedObject7));

            allCreatedObjects7.push_back (pWaveTestManagedObject7);
            allCreatedObjects7Map[pWaveTestManagedObject7->getObjectId ()] = pWaveTestManagedObject7;
        }

        WaveTestManagedObject11 *pWaveTestManagedObject11 = new WaveTestManagedObject11 (this);

        pWaveTestManagedObject11->setInteger11 (i);
        pWaveTestManagedObject11->setMessage11 ("Test");
        pWaveTestManagedObject11->setComposition11 (tempVector1);

        allCreatedObjects11.push_back (pWaveTestManagedObject11);
        allCreatedObjects11Map[pWaveTestManagedObject11->getObjectId ()] = pWaveTestManagedObject11;

        status = commitTransaction ();

        if (status != FRAMEWORK_SUCCESS)
        {
            trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::simpleOneToManyToManyCompositionTransactionTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
            break;
        }
        else
        {
            status = WAVE_MESSAGE_SUCCESS;
        }

    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::simpleOneToManyToManyCompositionQueryTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple One-To-Many-To-Many Composition Query Test ...");
    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (WaveTestManagedObject11::getClassName (), this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::simpleOneToManyToManyCompositionQueryTestCallback), pFrameworkPersistenceTestContext);

    pFrameworkPersistenceTestContext->setNumberOfExpectedResults ((pFrameworkPersistenceTestContext->getCreatedObjects11 ()).size ());

    query (pWaveManagedObjectQueryContext);
}

void FrameworkTestability4ObjectManager::simpleOneToManyToManyCompositionQueryTestCallback (WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext)
{
    FrameworkPersistenceTestContext          *pFrameworkPersistenceTestContext = reinterpret_cast<FrameworkPersistenceTestContext *> (pWaveManagedObjectQueryContext->getPCallerContext ());
    ResourceId                                status                           = pWaveManagedObjectQueryContext->getCompletionStatus ();
    map<ObjectId, WaveTestManagedObject11 *>  &allCreatedObjects11Map          = pFrameworkPersistenceTestContext->getCreatedObjects11Map ();

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::simpleOneToManyToManyCompositionQueryTestCallback : Simple One-Many-Many Composition Query test failed. Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        vector<WaveManagedObject *> *pResults = pWaveManagedObjectQueryContext->getPResults ();

        waveAssert (NULL != pResults, __FILE__, __LINE__);

        UI32 numberOfExpectedResults = pFrameworkPersistenceTestContext->getNumberOfExpectedResults ();
        UI32 numberOfResults = pResults->size ();
        UI32 i               = 0;

        if (numberOfExpectedResults != numberOfResults)
        {
            trace (TRACE_LEVEL_FATAL, string ("FrameworkTestability4ObjectManager::simpleOneToManyToManyCompositionQueryTestCallback : We did not get expected number of results.  Expected = ") + numberOfExpectedResults + string (", Obtained =  ") + numberOfResults);
            waveAssert (false, __FILE__, __LINE__);
            status = WAVE_MESSAGE_ERROR;
        }
        else
        {
            trace (TRACE_LEVEL_DEVEL, string ("    Number of Results (asynchronously obtained) = ") + numberOfResults);

            for (i = 0; i < numberOfResults; i++)
            {
                WaveTestManagedObject11 *pWaveTestManagedObject11         = dynamic_cast<WaveTestManagedObject11 *> ((*pResults)[i]);
                waveAssert (NULL != pWaveTestManagedObject11, __FILE__, __LINE__);
                ObjectId                oid                             = pWaveTestManagedObject11->getObjectId  ();
                UI32                    integer11                       = pWaveTestManagedObject11->getInteger11  ();
                string                  message11                       = pWaveTestManagedObject11->getMessage11  ();

                WaveTestManagedObject11 *pWaveTestManagedObject11Expected = allCreatedObjects11Map[oid];
                ObjectId                oidExpected                     = pWaveTestManagedObject11Expected->getObjectId  ();
                UI32                    integer11Expected               = pWaveTestManagedObject11Expected->getInteger11  ();
                string                  message11Expected               = pWaveTestManagedObject11Expected->getMessage11  ();

                //trace (TRACE_LEVEL_DEVEL, string ("        ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer2 + string (", ") + message2 + string (", ") + objectId2.getClassId () + string (", ") + objectId2.getInstanceId ());

                if ((*pWaveTestManagedObject11Expected) != (*pWaveTestManagedObject11))
                {
                    trace (TRACE_LEVEL_ERROR, string ("Got      : ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer11+ string (", ") + message11);
                    trace (TRACE_LEVEL_ERROR, string ("Expected : ") + oidExpected.getClassId () + string (", ") + oidExpected.getInstanceId () + string (", ") + integer11Expected + string (", ") + message11Expected);
                    waveAssert (false, __FILE__, __LINE__);

                    status = WAVE_MESSAGE_ERROR;
                    break;
                }
            }

            if (WAVE_MESSAGE_SUCCESS == status)
            {
                trace (TRACE_LEVEL_DEVEL, "    All Queried results were successfully compared against expected values.");
            }
        }
    }

    delete pWaveManagedObjectQueryContext;

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::deleteAllOneToManyToManyCompositionUsingDeleteMultipleWaveManagedObjectsWithDeletionContextTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Delete All One-To-Many-To-Many Composition Using Delete Multiple Wave Managed Objects With Deletion Context Test ...");
    
    vector<WaveTestManagedObject1 *>        &allCreatedObjects       = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjectsMap    = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    vector<WaveTestManagedObject3 *>        &allCreatedObjects3      = pFrameworkPersistenceTestContext->getCreatedObjects3 ();
    map<ObjectId, WaveTestManagedObject3 *> &allCreatedObjects3Map   = pFrameworkPersistenceTestContext->getCreatedObjects3Map ();
    vector<WaveTestManagedObject7 *>         &allCreatedObjects7      = pFrameworkPersistenceTestContext->getCreatedObjects7 ();
    map<ObjectId, WaveTestManagedObject7 *>  &allCreatedObjects7Map   = pFrameworkPersistenceTestContext->getCreatedObjects7Map ();
    vector<WaveTestManagedObject11 *>        &allCreatedObjects11     = pFrameworkPersistenceTestContext->getCreatedObjects11 ();
    map<ObjectId, WaveTestManagedObject11 *> &allCreatedObjects11Map  = pFrameworkPersistenceTestContext->getCreatedObjects11Map ();
    ResourceId                               status                   = WAVE_MESSAGE_SUCCESS;

    WaveManagedObjectSynchronousQueryContextForDeletion *synchronousQueryContextForDeletion  = new WaveManagedObjectSynchronousQueryContextForDeletion(WaveTestManagedObject11::getClassName ());

    // Sets 'WHERE  (message7 LIKE '%Test%')' in the SQL DELETE query.
    synchronousQueryContextForDeletion->addAndAttribute (new AttributeString ("%Test%", "message11"), "LIKE");

    startTransaction ();

    deleteMultipleWaveManagedObjects (synchronousQueryContextForDeletion);

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::deleteAllOneToManyToManyCompositionUsingDeleteMultipleWaveManagedObjectsWithDeletionContextTestStep: Transaction failed.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }

    allCreatedObjects11.clear ();
    allCreatedObjects11Map.clear ();
    allCreatedObjects7.clear ();
    allCreatedObjects7Map.clear ();
    allCreatedObjects3.clear ();
    allCreatedObjects3Map.clear ();
    allCreatedObjects.clear ();
    allCreatedObjectsMap.clear ();


    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::deleteAllOneToManyCompositionUsingDeleteMultipleWaveManagedObjectsWithDeletionContextTestStep(FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Delete All One-To-Many Composition Using Delete Multiple Wave Managed Objects With Deletion Context Test ...");
    
    vector<WaveTestManagedObject1 *>        &allCreatedObjects       = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjectsMap    = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    vector<WaveTestManagedObject7 *>         &allCreatedObjects7      = pFrameworkPersistenceTestContext->getCreatedObjects7 ();
    map<ObjectId, WaveTestManagedObject7 *>  &allCreatedObjects7Map   = pFrameworkPersistenceTestContext->getCreatedObjects7Map ();
    ResourceId                                status                  = WAVE_MESSAGE_SUCCESS;

    WaveManagedObjectSynchronousQueryContextForDeletion *synchronousQueryContextForDeletion  = new WaveManagedObjectSynchronousQueryContextForDeletion(WaveTestManagedObject7::getClassName ());

    // Sets 'WHERE  (message7 LIKE '%Test%')' in the SQL DELETE query.
    synchronousQueryContextForDeletion->addAndAttribute (new AttributeString ("%Test%", "message7"), "LIKE");

    startTransaction ();

    deleteMultipleWaveManagedObjects (synchronousQueryContextForDeletion);

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::deleteAllOneToManyCompositionUsingDeleteMultipleWaveManagedObjectsWithDeletionContextTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }

    allCreatedObjects7.clear ();
    allCreatedObjects7Map.clear ();
    allCreatedObjects.clear ();
    allCreatedObjectsMap.clear ();

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::deleteAllCreatedObjects7TestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Delete All Created Objects7 Transaction Test ...");

    ResourceId                                status                  = WAVE_MESSAGE_SUCCESS;
    UI32                                      i                       = 0;
    vector<WaveTestManagedObject1 *>        &allCreatedObjects       = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjectsMap    = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    vector<WaveTestManagedObject7 *>         &allCreatedObjects7      = pFrameworkPersistenceTestContext->getCreatedObjects7 ();
    map<ObjectId, WaveTestManagedObject7 *>  &allCreatedObjects7Map   = pFrameworkPersistenceTestContext->getCreatedObjects7Map ();
    UI32                                      numberOfObjectsCreated7 = allCreatedObjects7.size ();

    startTransaction ();

    for (i = 0; i < numberOfObjectsCreated7; i++)
    {
        delete allCreatedObjects7[i];
    }

    // NOTICE: We must not delete the WaveTestManagedObject1 here since they are owned by the WaveTestManagedObject6.
    //         They are implicitly deleted when the owning WaveTestManagedObject6 are deleted.
    //         If you explicitly delete WaveTestManagedObject1 objects it will result in SIGSEGV!!!

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::deleteAllCreatedObjects7TestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }

    allCreatedObjects7.clear ();
    allCreatedObjects7Map.clear ();
    allCreatedObjects.clear ();
    allCreatedObjectsMap.clear ();

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::largeOneToManyCompositionTransactionTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Large One-To-Many Composition Transaction Test ...");

    FrameworkTestabilityMessage8             *pFrameworkTestabilityMessage8 = reinterpret_cast<FrameworkTestabilityMessage8 *> (pFrameworkPersistenceTestContext->getPWaveMessage ());
    ResourceId                                status                        = WAVE_MESSAGE_SUCCESS;
    UI32                                      numberOfObjectsToCreate       = pFrameworkTestabilityMessage8->getNumberOfObjectsToBeCreated ();
    UI32                                      i                             = 0;
    UI32                                      j                             = 0;
    vector<WaveTestManagedObject1 *>        &allCreatedObjects             = pFrameworkPersistenceTestContext->getCreatedObjects ();
    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjects1Map         = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();
    vector<WaveTestManagedObject7 *>         &allCreatedObjects7            = pFrameworkPersistenceTestContext->getCreatedObjects7 ();
    map<ObjectId, WaveTestManagedObject7 *>  &allCreatedObjects7Map         = pFrameworkPersistenceTestContext->getCreatedObjects7Map ();

    startTransaction ();

    for (i = 0; i < numberOfObjectsToCreate / 10; i++)
    {
        vector <WaveManagedObjectPointer<WaveTestManagedObject1> > tempVector;

        for (j = 0; j < 32; j++)
        {
            WaveTestManagedObject1 *pWaveTestManagedObject1 = new WaveTestManagedObject1 (this);

            pWaveTestManagedObject1->setInteger1 (i * 32 + j);
            pWaveTestManagedObject1->setMessage1 ("Test");
            pWaveTestManagedObject1->setObjectId1 (ObjectId (i * 32 + j, i * 32 + j));

            tempVector.push_back (WaveManagedObjectPointer<WaveTestManagedObject1> (pWaveTestManagedObject1));

            allCreatedObjects.push_back (pWaveTestManagedObject1);
            allCreatedObjects1Map[pWaveTestManagedObject1->getObjectId ()] = pWaveTestManagedObject1;
        }

        WaveTestManagedObject7 *pWaveTestManagedObject7 = new WaveTestManagedObject7 (this);

        pWaveTestManagedObject7->setInteger7 (i);
        pWaveTestManagedObject7->setMessage7 ("Test");
        pWaveTestManagedObject7->setObjectId7 (ObjectId (i, i));
        pWaveTestManagedObject7->setComposition7 (tempVector);

        allCreatedObjects7.push_back (pWaveTestManagedObject7);
        allCreatedObjects7Map[pWaveTestManagedObject7->getObjectId ()] = pWaveTestManagedObject7;
    }

    status = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::simpleOneToManyCompositionTransactionTestStep : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::getManagedObjectsMessageHandler (FrameworkTestability4ObjectManagerGetManagedObjects *pFrameworkTestability4ObjectManagerGetManagedObjects)
{
    trace (TRACE_LEVEL_DEVEL, "FrameworkTestability4ObjectManager::getManagedObjectsMessageHandler : Entering ...");

    const string managedObjectClassName = pFrameworkTestability4ObjectManagerGetManagedObjects->getManagedObjectClassName ();
    const string schemaName             = pFrameworkTestability4ObjectManagerGetManagedObjects->getSchemaName             ();

    trace (TRACE_LEVEL_INFO, "FrameworkTestability4ObjectManager::getManagedObjectsMessageHandler : Managed Object Class Name : " + managedObjectClassName);
    trace (TRACE_LEVEL_INFO, "FrameworkTestability4ObjectManager::getManagedObjectsMessageHandler : Schema Name               : " + schemaName);

    WaveManagedObjectSynchronousQueryContext queryContext (managedObjectClassName);

    queryContext.setSchemaToQuery (schemaName);
    queryContext.addOrderField    ("name");

    vector<WaveManagedObject *> *pWaveManagedObjects = querySynchronously (&queryContext);

    waveAssert (NULL != pWaveManagedObjects, __FILE__, __LINE__);

    UI32               numberOfWaveManagedObjects = pWaveManagedObjects->size ();
    UI32               i                          = 0;
    string             showDump;
    vector<string>    &managedObjects             = pFrameworkTestability4ObjectManagerGetManagedObjects->getManagedObjects ();
    WaveManagedObject *pWaveManagedObject         = NULL;
    bool               useRawFromat               = pFrameworkTestability4ObjectManagerGetManagedObjects->getUseRawFormat ();

    for ( i = 0; i < numberOfWaveManagedObjects; i++)
    {
        pWaveManagedObject = (*pWaveManagedObjects)[i];

        waveAssert (NULL != pWaveManagedObject, __FILE__, __LINE__);

        showDump = managedObjectClassName + " " + pWaveManagedObject->getName ();

        if (true == (useRawFromat))
        {
            pWaveManagedObject->getRawShowDump (showDump, WAVE_MANAGED_OBJECT_SHOW_CONFIGURATION);
        }
        else
        {
        pWaveManagedObject->getShowDump (showDump, WAVE_MANAGED_OBJECT_SHOW_CONFIGURATION);
        }

        managedObjects.push_back (showDump);

        delete pWaveManagedObject;
    }

    delete pWaveManagedObjects;

    pFrameworkTestability4ObjectManagerGetManagedObjects->setNumberOfManagedObjects (numberOfWaveManagedObjects);

    pFrameworkTestability4ObjectManagerGetManagedObjects->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    reply (pFrameworkTestability4ObjectManagerGetManagedObjects);
}

void FrameworkTestability4ObjectManager::simpleSynchronousPageQueryTestStep (FrameworkPersistenceTestContext *pFrameworkPersistenceTestContext)
{
    trace (TRACE_LEVEL_INFO, "Simple Synchronous Paged Query Test ...");
    UI32       numberOfExpectedResults = (pFrameworkPersistenceTestContext->getCreatedObjects ()).size ();
    UI32	 resultCount = 0;	

    map<ObjectId, WaveTestManagedObject1 *> &allCreatedObjectsMap = pFrameworkPersistenceTestContext->getCreatedObjectsMap ();

	WaveManagedObjectSynchronousQueryContext *synchronousQueryContext =
		new WaveManagedObjectSynchronousQueryContext(WaveTestManagedObject1::getClassName ());
	synchronousQueryContext->setPageSizeForQueryResults (23); // Make it progtamatic


    ResourceId status                  = WAVE_MESSAGE_SUCCESS;


	while(1)
{
	vector<WaveManagedObject *> 			*pResults			  = querySynchronously (synchronousQueryContext);
	waveAssert (NULL != pResults, __FILE__, __LINE__);

	UI32       numberOfResults         = pResults->size ();
	UI32       i                       = 0;
	status                  = WAVE_MESSAGE_SUCCESS;

	trace (TRACE_LEVEL_DEBUG, string ("    Number of Results (synchronously obtained) = ") + numberOfResults);
	if (numberOfResults <= 0)
	{
	delete pResults;
	trace (TRACE_LEVEL_DEBUG, string ("    Total number of Results (synchronously obtained) = ") + resultCount);
	break;	
	} 
	else
	{

	resultCount +=numberOfResults;
		
	if (23 != numberOfResults)
	{
		trace (TRACE_LEVEL_INFO, string ("FrameworkTestability4ObjectManager::simpleSynchronousQueryTestStep : Expected total= ")
		+ numberOfExpectedResults + string (", Obtained =	") + numberOfResults + string (", Actual total =  ") + resultCount);
	}


	for (i = 0; i < numberOfResults; i++)
	{
		WaveTestManagedObject1 *pWaveTestManagedObject1         = dynamic_cast<WaveTestManagedObject1 *> ((*pResults)[i]);
        waveAssert (NULL != pWaveTestManagedObject1, __FILE__, __LINE__);
		ObjectId                 oid                              = pWaveTestManagedObject1->getObjectId  ();
		UI32                     integer1                         = pWaveTestManagedObject1->getInteger1  ();
		trace (TRACE_LEVEL_DEBUG, string ("   Results  WaveTestManagedObject1->getInteger1  ()= ") + integer1);
		string                   message1                         = pWaveTestManagedObject1->getMessage1  ();
		ObjectId                 objectId1                        = pWaveTestManagedObject1->getObjectId1 ();

		WaveTestManagedObject1 *pWaveTestManagedObject1Expected = allCreatedObjectsMap[oid];
		ObjectId                 oidExpected                      = pWaveTestManagedObject1Expected->getObjectId  ();
		UI32                     integer1Expected                 = pWaveTestManagedObject1Expected->getInteger1  ();
		string                   message1Expected                 = pWaveTestManagedObject1Expected->getMessage1  ();
		ObjectId                 objectId1Expected                = pWaveTestManagedObject1Expected->getObjectId1 ();

		trace (TRACE_LEVEL_DEVEL, string ("        ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer1 + string (", ") + message1 + string (", ") + objectId1.getClassId () + string (", ") + objectId1.getInstanceId ());

		if ((*pWaveTestManagedObject1Expected) != (*pWaveTestManagedObject1))
		{
		    trace (TRACE_LEVEL_ERROR, string ("Got      : ") + oid.getClassId () + string (", ") + oid.getInstanceId () + string (", ") + integer1 + string (", ") + message1 + string (", ") + objectId1.getClassId () + string (", ") + objectId1.getInstanceId ());
		    trace (TRACE_LEVEL_ERROR, string ("Expected : ") + oidExpected.getClassId () + string (", ") + oidExpected.getInstanceId () + string (", ") + integer1Expected + string (", ") + message1Expected + string (", ") + objectId1Expected.getClassId () + string (", ") + objectId1Expected.getInstanceId ());
		    waveAssert (false, __FILE__, __LINE__);

		    status = WAVE_MESSAGE_ERROR;
		    break;
		}
	    }

	    if (WAVE_MESSAGE_SUCCESS == status)
	    {
	        trace (TRACE_LEVEL_DEBUG, "    simpleSynchronousPageQueryTestStep: All Queried results were successfully compared against expected values.");
	    }


	}

	for (i = 0; i < numberOfResults; i++)
	{
	    delete ((*pResults)[i]);
	}

	delete pResults;
 }

   delete synchronousQueryContext;

    pFrameworkPersistenceTestContext->executeNextStep (status);
}

void FrameworkTestability4ObjectManager::frameworkTestability9MessageHandler (FrameworkTestabilityMessage9 *pMessage)
{
    UI32        i       =   0;

    startTransaction ();

    WaveTestManagedObject8 *pWaveTestManagedObject8 = new WaveTestManagedObject8 (this);

    pWaveTestManagedObject8->setInteger8 (i);
    pWaveTestManagedObject8->setMessage8 ("Wave's Test Cases For Nested Transaction");

    FrameworkTestabilityMessage10 *pMessage10 = new FrameworkTestabilityMessage10 ();

    WaveSendToClusterContext     *pWaveSendToClusterContext      = new WaveSendToClusterContext (this, reinterpret_cast<WaveAsynchronousCallback> (&FrameworkTestability4ObjectManager::frameworkTestability10MessageSendToWaveClusterCallback), pMessage);

    pWaveSendToClusterContext->setPWaveMessageForPhase1 (pMessage10);
    pWaveSendToClusterContext->setPWaveMessageForPhase2 (NULL);
    
    sendToWaveCluster (pWaveSendToClusterContext);

}

void FrameworkTestability4ObjectManager::frameworkTestability10MessageSendToWaveClusterCallback (WaveSendToClusterContext *pWaveSendToClusterContext)
{
    FrameworkTestabilityMessage9 *pMessage      = reinterpret_cast<FrameworkTestabilityMessage9 *> (pWaveSendToClusterContext->getPCallerContext ());
    ResourceId  status                          = commitTransaction ();

    if (status != FRAMEWORK_SUCCESS)
    {
        trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::frameworkTestability10MessageSendToWaveClusterCallback : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
        status = WAVE_MESSAGE_ERROR;
    }
    else
    {
        status = WAVE_MESSAGE_SUCCESS;
    }

    delete (pWaveSendToClusterContext->getPWaveMessageForPhase1 ());
    delete pWaveSendToClusterContext;
    
    pMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    reply (pMessage);

}

}

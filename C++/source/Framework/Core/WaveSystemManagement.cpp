/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/WaveSystemManagement.h"
#include "Framework/Core/ApplicationSpecificServices.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Utils/WaveSourceGenerator/WaveSourceGeneratorBase.h"
#include "Framework/Core/FrameworkSequenceGenerator.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/Database/DatabaseObjectManager.h"
#include "Framework/Profiling/WaveProfiler.h"
#include "Framework/Utils/TimeZoneToolKit.h"
#include "SystemManagement/WaveSystemManagementObjectManager.h"
#include "SystemManagement/SystemManagementToolKit.h"
#include "SystemManagement/CommandLineInterface/Server/CommandLineInterfaceReceiverObjectManager.h"
#include "Framework/ObjectModel/WavePersistableObject.h"
#include "Framework/ObjectModel/WaveManagedObject.h"
#include "Framework/ObjectModel/WaveLocalManagedObject.h"
#include "HttpInterface/HttpInterfaceReceiverObjectManager.h"
#include "Framework/Database/MultiDatabaseObjectManager.h"
#include "ManagementInterface/ManagementInterfaceReceiverObjectManager.h"
#include "ManagementInterface/ClientInterface/WaveClientReceiverObjectManager.h"
#include "ManagementInterface/ClientInterface/WaveClientTransportObjectManager.h"
#include "ManagementInterface/ClientInterface/WaveUserInterfaceObjectManager.h"
#include "Framework/Core/WaveFrameworkObjectManagerInitializeWorker.h"
#include "Cluster/MultiPartition/Global/MultiPartitionObjectManager.h"
#include "Cluster/MultiPartition/Local/MultiPartitionLocalObjectManager.h"

#include <time.h>
#include <stdlib.h>
#include <sys/resource.h>

//Commenting it our for now.  We need to find way to enable it on Solaris.
//extern int daemon (int doNotChangeToRootDir, int doNotCloseFileDescriptors);

static string s_waveTraceFileDirectory         ("");
static string s_waveConfigurationFileDirectory ("");
static string s_waveProfileFileDirectory       ("");

namespace WaveNs
{

void WaveSystemManagement::initialize (const WaveMainConfiguration &waveMainConfiguration)
{
    // First change to user specified directory if any

    SI32 rlimitStatus = 0;
    rlimit rlim;

    rlim.rlim_cur = 1048576 * 8;   // 8 MB
    rlim.rlim_max = 1048576 * 8;

    rlimitStatus = setrlimit (RLIMIT_STACK, &rlim);

    if (0 != rlimitStatus)
    {
        trace (TRACE_LEVEL_WARN, "WaveSystemManagement::initialize not able to set rlimit");
    }

    if ("" != (waveMainConfiguration.getChangeDirectoryTo ()))
    {
        SI32 chDirStatus = chdir ((waveMainConfiguration.getChangeDirectoryTo ()).c_str ());

        if (0 != chDirStatus)
        {
            trace (TRACE_LEVEL_ERROR, "WaveSystemManagement::initialize : Could not Change Directory to " + waveMainConfiguration.getChangeDirectoryTo ());
            trace (TRACE_LEVEL_ERROR, "WaveSystemManagement::initialize : Reason listed below :");
            perror ("WAVE System Management");
            waveAssert (false, __FILE__, __LINE__);
        }
    }

    // Initialize Random Generator

    srand (time (NULL));

    // Set the Management Interface Role

    FrameworkToolKit::setManagementInterfaceRole (WAVE_MGMT_INTF_ROLE_SERVER);
    FrameworkToolKit::setDefaultTraceLevel (TRACE_LEVEL_INFO);

    // Set if the database is to be enabled.

    DatabaseObjectManager::setIsDatabaseEnabled (waveMainConfiguration.getIsDatabaseEnabled ());
    DatabaseObjectManager::setDatabasePort (waveMainConfiguration.getDatabasePort ());

    // First record the current working directory as the directory in which the process was started

    FrameworkToolKit::initialize ();

    //Initialize time zone information

    TimeZoneToolKit::initialize ();

    // Setup the System Management;

    SystemManagementToolKit::setYinPaths          (waveMainConfiguration.getYinPaths ());
    SystemManagementToolKit::setWyserTagsFilePath (waveMainConfiguration.getWyserTagsFilePath ());

    // set the Wave Framework configuration file.

    WaveFrameworkObjectManager::setConfigurationFile ((getConfigurationFileDirectory ()) + "/" + waveMainConfiguration.getApplicationCompactName () + ".cfg");
    WaveFrameworkObjectManager::setGlobalConfigurationFile ((getConfigurationFileDirectory ()) + "/" + waveMainConfiguration.getApplicationCompactName () + ".global.cfg");

#ifdef _X86_COMPILE_
    WaveFrameworkObjectManager::setLockFileForConfigurationFile ((getConfigurationFileDirectory ()) + "/" + waveMainConfiguration.getApplicationCompactName () + ".cfg.tmp");
#else
    WaveFrameworkObjectManager::setLockFileForConfigurationFile ("/tmp/" + waveMainConfiguration.getApplicationCompactName () + ".cfg.tmp");
#endif

    // set the Wave Framework configuration file.

    WaveFrameworkObjectManager::setConfigurationFile ((getConfigurationFileDirectory ()) + "/" + waveMainConfiguration.getApplicationCompactName () + ".cfg");

    // Set the trace file name first

    TraceObjectManager::setTraceFileName ((getTraceFileDirectory ()) + "/" + waveMainConfiguration.getApplicationCompactName () + ".trc");

    // Set the profile file namespace

    WaveProfiler::setProfileFileName ((getProfileFileDirectory ()) + "/" + waveMainConfiguration.getApplicationCompactName () + ".wpd");

    // Set if logging to syslog is required

    TraceObjectManager::setIsSysLogRequired (waveMainConfiguration.getIsSysLogRequired ());

    // Set database logging information and if logging is required.

    DatabaseObjectManager::setDatabaseLogFileName (getTraceFileDirectory () + "/" + waveMainConfiguration.getApplicationCompactName () + "." + waveMainConfiguration.getDatabaseLogFileName () + ".log");
    DatabaseObjectManager::setIsDatabaseLogEnabled (waveMainConfiguration.getIsDatabaseLogEnabled ());

    // Set database runtime parameters

    DatabaseObjectManager::setDatabaseSharedBuffers (waveMainConfiguration.getDatabaseSharedBuffers ());

    // Run the process in daemon mode if required.

    if (true == (waveMainConfiguration.getIsADaemon ()))
    {
        int rc = daemon (1, 0);

        if (0 != rc)
        {
            // handle the error.
        }
    }

    // Record if the process is running as a daemon.

    FrameworkToolKit::setIsRunningAsADaemon (waveMainConfiguration.getIsADaemon ());

    // Add ORM Repository Most Base Classes information from Wave.

    OrmRepository::addMostBaseClass (WavePersistableObject::getClassName ());
    OrmRepository::addMostBaseClass (WaveManagedObject::getClassName      ());
    OrmRepository::addMostBaseClass (WaveLocalManagedObject::getClassName ());

    // WaveFrameworkObjectManager must be the first one to be created.

    WaveFrameworkObjectManager::getInstance ();

    if (true == (waveMainConfiguration.getIsADaemon ()))
    {
        FrameworkToolKit::initializeConsolePrintFunction ();
    }

    // ShellObjectManager must be the next one so that all can register their shells and related shell handlers.

    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (ShellObjectManager::getInstance));

    FrameworkToolKit::registerDebugShellEntries ();

    // WARNING! WARNING! WARNING!
    // DO NOT CHANGE ABOVE THIS LINE

    // Below this one the services are registered in reverse order.  The last one will be on top of the list.


    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (ClusterLocalObjectManager::getInstance), true, WAVE_SERVICE_INACTIVE);
    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (MultiPartitionObjectManager::getInstance), true, WAVE_SERVICE_INACTIVE);
    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (MultiPartitionLocalObjectManager::getInstance), true, WAVE_SERVICE_INACTIVE);

    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (HttpInterfaceReceiverObjectManager::getInstance));

    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (CommandLineInterfaceReceiverObjectManager::getInstance));
    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (WaveSystemManagementObjectManager::getInstance));

    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (MultiDatabaseObjectManager::getInstance));

    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (ManagementInterfaceReceiverObjectManager::getInstance));
    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (ManagementInterfaceObjectManager::getInstance));
    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (WaveUserInterfaceObjectManager::getInstance));
    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (WaveClientTransportObjectManager::getInstance));
    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (WaveClientReceiverObjectManager::getInstance));

    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (TimerObjectManager::getInstance), false);
    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (TimerSignalObjectManager::getInstance), false);

    //registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (TraceObjectManager::getInstance));

    // Instantiate Native Wave Services here

    instantiateNativeWaveServices ();
}

string WaveSystemManagement::getTraceFileDirectory ()
{
    static WaveMutex traceFileDirectoryMutex;

    traceFileDirectoryMutex.lock ();

    if ("" != s_waveTraceFileDirectory)
    {
        traceFileDirectoryMutex.unlock ();
        return (s_waveTraceFileDirectory);
    }
    else
    {
        s_waveTraceFileDirectory = FrameworkToolKit::getProcessInitialWorkingDirectory ();

        if ("" == s_waveTraceFileDirectory)
        {
            s_waveTraceFileDirectory = "/tmp";
        }
    }

    traceFileDirectoryMutex.unlock ();

    return (s_waveTraceFileDirectory);
}

string WaveSystemManagement::getConfigurationFileDirectory ()
{
    static WaveMutex configurationFileDirectoryMutex;

    configurationFileDirectoryMutex.lock ();

    if ("" != s_waveConfigurationFileDirectory)
    {
        configurationFileDirectoryMutex.unlock ();
        return (s_waveConfigurationFileDirectory);
    }
    else
    {
        s_waveConfigurationFileDirectory = FrameworkToolKit::getProcessInitialWorkingDirectory ();

        if ("" == s_waveConfigurationFileDirectory)
        {
            s_waveConfigurationFileDirectory = "/tmp";
        }
    }

    configurationFileDirectoryMutex.unlock ();

    return (s_waveConfigurationFileDirectory);
}

string WaveSystemManagement::getProfileFileDirectory ()
{
    static WaveMutex profileFileDirectoryMutex;

    profileFileDirectoryMutex.lock ();

    if ("" != s_waveProfileFileDirectory)
    {
        profileFileDirectoryMutex.unlock ();
        return (s_waveProfileFileDirectory);
    }
    else
    {
        s_waveProfileFileDirectory = FrameworkToolKit::getProcessInitialWorkingDirectory ();

        if ("" == s_waveProfileFileDirectory)
        {
            s_waveProfileFileDirectory = "/tmp";
        }
    }

    profileFileDirectoryMutex.unlock ();

    return (s_waveProfileFileDirectory);
}

void WaveSystemManagement::registerNativeServiceInternal (NativeWaveServiceInstantiator pNativeWaveServiceInstantiator, const bool &isForNormalPhase, const ResourceId &serviceMode)
{
    Wave::registerNativeServiceInternal (pNativeWaveServiceInstantiator, isForNormalPhase, serviceMode);
}

void WaveSystemManagement::instantiateNativeWaveServices ()
{
    Wave::instantiateNativeWaveServices ();
}

}

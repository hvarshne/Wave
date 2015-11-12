/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Configuration;

import java.util.Vector;

import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonSerializable;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.XmlWaveXPath;
import com.CxWave.Wave.Framework.Utils.Configuration.WaveConfiguration;

@XmlWaveXPath (path = "wave")
public class WaveMainConfiguration extends WaveConfiguration
{
    @XmlWaveXPath (path = "application")
    private WaveMainApplication         m_application;

    @XmlWaveXPath (path = "database")
    private WaveMainDatabase            m_database                 = new WaveMainDatabase ();

    @XmlWaveXPath (path = "management-interface")
    private WaveMainManagementInterface m_waveMainManagementInterface;

    @XmlWaveXPath (path = "system-management")
    private WaveMainSystemManagement    m_waveMainSystemManagement = new WaveMainSystemManagement ();

    private boolean                     m_isSysLogRequired;
    private int                         m_port;

    @NonSerializable
    private Vector<String>              m_yinPaths;
    private String                      m_wyserTagsFilePath;
    private String                      m_databaseEmptyType;
    private long                        m_databaseEmptyTypeAutoDetectionThresholdValue;
    private String                      m_configurationFile;
    private String                      m_configurationFileDirectory;
    private String                      m_globalConfigurationFile;
    private String                      m_lockFileForConfigurationFile;
    private String                      m_traceFileDirectory;
    private String                      m_traceFileName;
    private String                      m_profileFileName;

    public WaveMainConfiguration ()
    {
    }

    public WaveMainApplication getApplication ()
    {
        return m_application;
    }

    public void setApplication (final WaveMainApplication application)
    {
        m_application = application;
    }

    public WaveMainDatabase getDatabase ()
    {
        return m_database;
    }

    public void setDatabase (final WaveMainDatabase database)
    {
        m_database = database;
    }

    public WaveMainManagementInterface getWaveMainManagementInterface ()
    {
        return m_waveMainManagementInterface;
    }

    public void setWaveMainManagementInterface (final WaveMainManagementInterface waveMainManagementInterface)
    {
        m_waveMainManagementInterface = waveMainManagementInterface;
    }

    public WaveMainSystemManagement getWaveMainSystemManagement ()
    {
        return m_waveMainSystemManagement;
    }

    public void setWaveMainSystemManagement (final WaveMainSystemManagement waveMainSystemManagement)
    {
        m_waveMainSystemManagement = waveMainSystemManagement;
    }

    public boolean getIsSysLogRequired ()
    {
        return m_isSysLogRequired;
    }

    public void setIsSysLogRequired (final boolean isSysLogRequired)
    {
        m_isSysLogRequired = isSysLogRequired;
    }

    public int getPort ()
    {
        return m_port;
    }

    public void setPort (final int port)
    {
        m_port = port;
    }

    public Vector<String> getYinPaths ()
    {
        return m_yinPaths;
    }

    public void setYinPaths (final Vector<String> yinPaths)
    {
        m_yinPaths = yinPaths;
    }

    public String getWyserTagsFilePath ()
    {
        return m_wyserTagsFilePath;
    }

    public void setWyserTagsFilePath (final String wyserTagsFilePath)
    {
        m_wyserTagsFilePath = wyserTagsFilePath;
    }

    public String getDatabaseEmptyType ()
    {
        return m_databaseEmptyType;
    }

    public void setDatabaseEmptyType (final String databaseEmptyType)
    {
        m_databaseEmptyType = databaseEmptyType;
    }

    public long getDatabaseEmptyTypeAutoDetectionThresholdValue ()
    {
        return m_databaseEmptyTypeAutoDetectionThresholdValue;
    }

    public void setDatabaseEmptyTypeAutoDetectionThresholdValue (final long databaseEmptyTypeAutoDetectionThresholdValue)
    {
        m_databaseEmptyTypeAutoDetectionThresholdValue = databaseEmptyTypeAutoDetectionThresholdValue;
    }

    public String getConfigurationFile ()
    {
        return m_configurationFile;
    }

    public void setConfigurationFile (final String configurationFile)
    {
        m_configurationFile = configurationFile;
    }

    public String getConfigurationFileDirectory ()
    {
        return m_configurationFileDirectory;
    }

    public void setConfigurationFileDirectory (final String configurationFileDirectory)
    {
        m_configurationFileDirectory = configurationFileDirectory;
    }

    public String getApplicationCompactName ()
    {
        if (null != m_application)
        {
            return (m_application.getApplicationCompactName ());
        }
        else
        {
            return ("");
        }
    }

    public String getGlobalConfigurationFile ()
    {
        return m_globalConfigurationFile;
    }

    public void setGlobalConfigurationFile (final String globalConfigurationFile)
    {
        m_globalConfigurationFile = globalConfigurationFile;
    }

    public String getLockFileForConfigurationFile ()
    {
        return m_lockFileForConfigurationFile;
    }

    public void setLockFileForConfigurationFile (final String lockFileForConfigurationFile)
    {
        m_lockFileForConfigurationFile = lockFileForConfigurationFile;
    }

    public String getTraceFileDirectory ()
    {
        return m_traceFileDirectory;
    }

    public void setTraceFileDirectory (final String traceFileDirectory)
    {
        m_traceFileDirectory = traceFileDirectory;
    }

    public String getTraceFileName ()
    {
        return m_traceFileName;
    }

    public void setTraceFileName (final String traceFileName)
    {
        m_traceFileName = traceFileName;
    }

    public String getProfileFileName ()
    {
        return m_profileFileName;
    }

    public void setProfileFileName (final String profileFileName)
    {
        m_profileFileName = profileFileName;
    }
}

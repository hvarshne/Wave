/***************************************************************************
 *   Copyright (C) 2015-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

package com.CxWave.Wave.Framework.Trace;

import com.CxWave.Wave.Framework.Type.TraceClientId;
import com.CxWave.Wave.Framework.Utils.Terminal.WaveTerminalUtils;
import com.CxWave.Wave.Framework.Utils.Time.WaveTimeUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class TraceObjectManager
{
    private static TraceObjectManager s_traceObjectManager = null;

    private static String             s_waveTraceFilePath  = "waveTraceFile.log";
    private static boolean            s_isFirstTime        = true;
    private static WaveTraceFile      s_waveTraceFile      = new WaveTraceFile ();
    private static TraceClientMap     s_traceClientMap     = null;

    private TraceObjectManager ()
    {
        s_traceClientMap = TraceClientMap.getInstance ();
    }

    public static TraceObjectManager getInstance ()
    {
        if (null == s_traceObjectManager)
        {
            s_traceObjectManager = new TraceObjectManager ();
        }

        return (s_traceObjectManager);
    }

    public static void setWaveTraceFilePath (final String waveTraceFilePath)
    {
        s_waveTraceFilePath = waveTraceFilePath;

    }

    public static String getWaveTraceFilePath ()
    {
        return (s_waveTraceFilePath);
    }

    private static String getTraceTagForLevel (final TraceLevel traceLevel)
    {
        String traceTag = null;

        switch (traceLevel)
        {
            case TRACE_LEVEL_UNKNOWN:
                traceTag = "UNKNOWN: ";
                break;

            case TRACE_LEVEL_DEVEL:
                traceTag = "DEVEL  : ";
                break;

            case TRACE_LEVEL_DEBUG:
                traceTag = "DEBUG  : ";
                break;

            case TRACE_LEVEL_INFO:
                traceTag = "INFO   : ";
                break;

            case TRACE_LEVEL_PERF_START:
                traceTag = "PERF_S : ";

                break;

            case TRACE_LEVEL_PERF_END:
                traceTag = "PERF_E : ";
                break;

            case TRACE_LEVEL_SUCCESS:
                traceTag = "SUCCESS: ";
                break;

            case TRACE_LEVEL_WARN:
                traceTag = "WARN   : ";
                break;

            case TRACE_LEVEL_ERROR:
                traceTag = "ERROR  : ";
                break;

            case TRACE_LEVEL_FATAL:
                traceTag = "FATAL  : ";
                break;
        }

        return (traceTag);
    }

    public static void traceDirectly (final TraceClientId traceClientId, final TraceLevel requestedTraceLevel, final String stringToTrace, final boolean addNewLine, final boolean suppressPrefix)
    {
        if (s_isFirstTime)
        {
            s_waveTraceFile.setNewFilePath (s_waveTraceFilePath);

            s_isFirstTime = false;
        }

        TraceLevel currentTraceLevel = s_traceClientMap.getTraceClientLevel (traceClientId);

        if (0 >= (currentTraceLevel.compareTo (requestedTraceLevel)))
        {
            StringBuilder computedTraceString = new StringBuilder ();

            WaveTerminalUtils.waveSetConsoleTextColor (requestedTraceLevel);

            if (! suppressPrefix)
            {
                computedTraceString.append (getTraceTagForLevel (requestedTraceLevel));

                computedTraceString.append (WaveTimeUtils.ctime ());

                computedTraceString.append (" : ");
            }

            String newLineString = "";

            if (addNewLine)
            {
                newLineString = "\n";
            }

            s_waveTraceFile.printf ("%s%s%s", computedTraceString, stringToTrace, newLineString);
            s_waveTraceFile.flush ();

            System.out.printf ("%s%s%s", computedTraceString, stringToTrace, newLineString);

            WaveTerminalUtils.waveResetConsoleTextColor ();
        }
    }
}
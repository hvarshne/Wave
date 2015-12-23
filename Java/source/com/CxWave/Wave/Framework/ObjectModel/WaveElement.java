/***************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public abstract class WaveElement
{
    private WaveObjectManager m_waveObjectManager;

    protected WaveElement ()
    {
    }

    protected WaveElement (final WaveObjectManager waveObjectManager)
    {
        m_waveObjectManager = waveObjectManager;
    }

    protected WaveElement (final WaveElement waveElement)
    {
        m_waveObjectManager = waveElement.m_waveObjectManager;
    }

    protected WaveObjectManager getWaveObjectManager ()
    {
        return (m_waveObjectManager);
    }

    protected void setWaveObjectManager (final WaveObjectManager waveObjectManager)
    {
        m_waveObjectManager = waveObjectManager;
    }

    protected abstract void trace (final TraceLevel requestedTraceLevel, final String stringToTrace, final boolean addNewLine, final boolean suppressPrefix);

    protected void unknownTrace (final String stringToTrace, final boolean addNewLine, final boolean suppressPrefix)
    {
        trace (TraceLevel.TRACE_LEVEL_UNKNOWN, stringToTrace, addNewLine, suppressPrefix);
    }

    protected void develTrace (final String stringToTrace, final boolean addNewLine, final boolean suppressPrefix)
    {
        trace (TraceLevel.TRACE_LEVEL_DEVEL, stringToTrace, addNewLine, suppressPrefix);
    }

    protected void debugTrace (final String stringToTrace, final boolean addNewLine, final boolean suppressPrefix)
    {
        trace (TraceLevel.TRACE_LEVEL_DEBUG, stringToTrace, addNewLine, suppressPrefix);
    }

    protected void infoTrace (final String stringToTrace, final boolean addNewLine, final boolean suppressPrefix)
    {
        trace (TraceLevel.TRACE_LEVEL_INFO, stringToTrace, addNewLine, suppressPrefix);
    }

    protected void successTrace (final String stringToTrace, final boolean addNewLine, final boolean suppressPrefix)
    {
        trace (TraceLevel.TRACE_LEVEL_SUCCESS, stringToTrace, addNewLine, suppressPrefix);
    }

    protected void warnTrace (final String stringToTrace, final boolean addNewLine, final boolean suppressPrefix)
    {
        trace (TraceLevel.TRACE_LEVEL_WARN, stringToTrace, addNewLine, suppressPrefix);
    }

    protected void errorTrace (final String stringToTrace, final boolean addNewLine, final boolean suppressPrefix)
    {
        trace (TraceLevel.TRACE_LEVEL_ERROR, stringToTrace, addNewLine, suppressPrefix);
    }

    protected void fatalTrace (final String stringToTrace, final boolean addNewLine, final boolean suppressPrefix)
    {
        trace (TraceLevel.TRACE_LEVEL_FATAL, stringToTrace, addNewLine, suppressPrefix);
    }

    protected abstract void trace (final TraceLevel requestedTraceLevel, final String stringToTrace);

    protected void unknownTrace (final String stringToTrace)
    {
        trace (TraceLevel.TRACE_LEVEL_UNKNOWN, stringToTrace);
    }

    protected void develTrace (final String stringToTrace)
    {
        trace (TraceLevel.TRACE_LEVEL_DEVEL, stringToTrace);
    }

    protected void debugTrace (final String stringToTrace)
    {
        trace (TraceLevel.TRACE_LEVEL_DEBUG, stringToTrace);
    }

    protected void infoTrace (final String stringToTrace)
    {
        trace (TraceLevel.TRACE_LEVEL_INFO, stringToTrace);
    }

    protected void successTrace (final String stringToTrace)
    {
        trace (TraceLevel.TRACE_LEVEL_SUCCESS, stringToTrace);
    }

    protected void warnTrace (final String stringToTrace)
    {
        trace (TraceLevel.TRACE_LEVEL_WARN, stringToTrace);
    }

    protected void errorTrace (final String stringToTrace)
    {
        trace (TraceLevel.TRACE_LEVEL_ERROR, stringToTrace);
    }

    protected void fatalTrace (final String stringToTrace)
    {
        trace (TraceLevel.TRACE_LEVEL_FATAL, stringToTrace);
    }

    protected abstract void tracePrintf (final TraceLevel requestedTraceLevel, final boolean addNewLine, final boolean suppressPrefix, final String formatString, Object... objects);

    protected void unknownTracePrintf (final boolean addNewLine, final boolean suppressPrefix, final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_UNKNOWN, addNewLine, suppressPrefix, formatString, objects);
    }

    protected void develTracePrintf (final boolean addNewLine, final boolean suppressPrefix, final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_DEVEL, addNewLine, suppressPrefix, formatString, objects);
    }

    protected void debugTracePrintf (final boolean addNewLine, final boolean suppressPrefix, final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_DEBUG, addNewLine, suppressPrefix, formatString, objects);
    }

    protected void infoTracePrintf (final boolean addNewLine, final boolean suppressPrefix, final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_INFO, addNewLine, suppressPrefix, formatString, objects);
    }

    protected void successTracePrintf (final boolean addNewLine, final boolean suppressPrefix, final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_SUCCESS, addNewLine, suppressPrefix, formatString, objects);
    }

    protected void warnTracePrintf (final boolean addNewLine, final boolean suppressPrefix, final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_WARN, addNewLine, suppressPrefix, formatString, objects);
    }

    protected void errorTracePrintf (final boolean addNewLine, final boolean suppressPrefix, final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, addNewLine, suppressPrefix, formatString, objects);
    }

    protected void fatalTracePrintf (final boolean addNewLine, final boolean suppressPrefix, final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, addNewLine, suppressPrefix, formatString, objects);
    }

    protected abstract void tracePrintf (final TraceLevel requestedTraceLevel, final String formatString, Object... objects);

    protected void unknownTracePrintf (final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_UNKNOWN, formatString, objects);
    }

    protected void develTracePrintf (final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_DEVEL, formatString, objects);
    }

    protected void debugTracePrintf (final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_DEBUG, formatString, objects);
    }

    protected void infoTracePrintf (final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_INFO, formatString, objects);
    }

    protected void successTracePrintf (final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_SUCCESS, formatString, objects);
    }

    protected void warnTracePrintf (final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_WARN, formatString, objects);
    }

    protected void errorTracePrintf (final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, formatString, objects);
    }

    protected void fatalTracePrintf (final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, formatString, objects);
    }

    public void holdAll ()
    {
        // TODO Auto-generated method stub

    }

    public void unholdAll ()
    {
        // TODO Auto-generated method stub

    }
}

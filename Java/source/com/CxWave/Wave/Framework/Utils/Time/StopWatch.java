/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.Time;

import java.util.Vector;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;

public class StopWatch
{
    private final Vector<Long> m_lapStarts       = new Vector<Long> ();
    private final Vector<Long> m_lapStops        = new Vector<Long> ();
    private long               m_currentLapStart = 0;

    public StopWatch ()
    {
    }

    public int getNumberOfLaps ()
    {
        WaveAssertUtils.waveAssert ((m_lapStarts.size ()) == (m_lapStops.size ()));

        return (m_lapStarts.size ());
    }

    public int getNumberOfLapsStarted ()
    {
        return ((m_lapStarts.size ()) + (0 < m_currentLapStart ? 1 : 0));
    }

    public int getNumberOfLapsStoped ()
    {
        return (m_lapStops.size ());
    }

    public long getLapDuration (final int lapIndex)
    {
        if ((lapIndex < (getNumberOfLaps ())) && (0 <= lapIndex))
        {
            return ((m_lapStops.get (lapIndex)) - (m_lapStarts.get (lapIndex)));
        }
        else
        {
            WaveTraceUtils.fatalTracePrintf ("StopWatch.getLapDuration : LapIndex %d is out of bounds.  Number of Laps : %d", lapIndex, getNumberOfLaps ());
            WaveAssertUtils.waveAssert ();

            return (-1);
        }
    }

    public long getLastLapDuration ()
    {
        final int numberOfLaps = getNumberOfLaps ();

        if (0 < numberOfLaps)
        {
            return (getLapDuration (numberOfLaps - 1));
        }
        else
        {
            return (0);
        }
    }

    public void start ()
    {
        m_currentLapStart = System.nanoTime ();
    }

    public void stop ()
    {
        // Deliberately using the order below (stop first and then add the start from already recorded variable).

        m_lapStops.add (System.nanoTime ());

        WaveAssertUtils.waveAssert (0 != m_currentLapStart);
        m_lapStarts.add (m_currentLapStart);

        m_currentLapStart = 0;
    }
}

/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Timer;

import com.CxWave.Wave.Framework.ObjectModel.WaveLocalObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.ObjectManagerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.PrePhase;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Resources.ResourceEnums.WaveObjectManagerPriority;

@PrePhase
@ObjectManagerPriority (WaveObjectManagerPriority.WAVE_OBJECT_MANAGER_PRIORITY_TIMER_SIGNAL)
public class TimerSignalObjectManager extends WaveLocalObjectManager
{
    private static TimerSignalObjectManager s_timerSignalObjectManager = null;

    private TimerSignalObjectManager ()
    {
        super (getServiceName ());
    }

    public static String getServiceName ()
    {
        return ("Framework Timer Signal");
    }

    public static TimerSignalObjectManager getInstance ()
    {
        if (null == s_timerSignalObjectManager)
        {
            s_timerSignalObjectManager = new TimerSignalObjectManager ();
        }

        WaveAssertUtils.waveAssert (null != s_timerSignalObjectManager);

        return (s_timerSignalObjectManager);
    }

    public static WaveServiceId getWaveServiceId ()
    {
        return ((getInstance ()).getServiceId ());
    }
}

/***************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***************************************************************************/

package com.CxWave.Wave.Framework.Utils.Assert;

public class WaveAssertUtils
{
    private WaveAssertUtils ()
    {
    }

    public static void waveAssert (boolean isAssertNotRequired)
    {
        if (!isAssertNotRequired)
        {
            Thread.dumpStack ();
            (Runtime.getRuntime ()).halt (-1);
        }
    }

    public static void waveAssert ()
    {
        waveAssert (false);
    }
}

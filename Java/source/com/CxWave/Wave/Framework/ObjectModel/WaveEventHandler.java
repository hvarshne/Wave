/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import com.CxWave.Wave.Framework.Messaging.Local.WaveEvent;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Source.WaveJavaSourceRepository;
import com.CxWave.Wave.Framework.Utils.Stack.WaveStackUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;

public class WaveEventHandler
{
    private final String m_methodName;
    private Method       m_method      = null;
    private WaveElement  m_waveElement = null;

    public WaveEventHandler (final String methodName)
    {
        m_methodName = methodName;
    }

    public String getMethodName ()
    {
        return (m_methodName);
    }

    public void validateAndCompute (final WaveElement waveElement)
    {
        WaveAssertUtils.waveAssert (null != waveElement);

        m_waveElement = waveElement;

        final Class<?> waveElementClass = waveElement.getClass ();

        WaveAssertUtils.waveAssert (null != waveElementClass);

        final Method waveEventHndlerMethod = WaveJavaSourceRepository.getMethodForWaveEventHandlerInWaveJavaClass (waveElementClass.getTypeName (), m_methodName);

        if (null == waveEventHndlerMethod)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveEventHandler.validateAndCompute : Could not compute the wave event handler in class %s formethod name %s.", waveElementClass.getTypeName (), m_methodName);
            WaveAssertUtils.waveAssert ();
        }

        m_method = waveEventHndlerMethod;
    }

    void execute (final WaveEvent waveEvent)
    {
        try
        {
            m_method.invoke (m_waveElement, waveEvent);
        }
        catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException e)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveEventHandler.execute : Failed to invoke method : %s, Details : %s", m_method.getName (), e.toString ());

            final Throwable cause = e.getCause ();

            if (null != cause)
            {
                WaveTraceUtils.fatalTracePrintf ("WaveEventHandler.execute : Cause : %s", cause.toString ());

                WaveTraceUtils.fatalTracePrintf ("%s", WaveStackUtils.getStackString (cause));
            }

            WaveTraceUtils.fatalTracePrintf ("%s", WaveStackUtils.getStackString (e));
        }
    }
}

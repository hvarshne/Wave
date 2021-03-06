/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

import java.lang.reflect.Method;
import java.util.Map;

import com.CxWave.Wave.Framework.Messaging.LightHouse.LightPulse;
import com.CxWave.Wave.Framework.Messaging.Local.WaveEvent;
import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonEventHandler;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonLightPulseHandler;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonMessageHandler;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonWorker;
import com.CxWave.Wave.Framework.ObjectModel.Boot.WaveAsynchronousContextForBootPhases;
import com.CxWave.Wave.Framework.Type.LocationId;
import com.CxWave.Wave.Framework.Type.TimeValue;
import com.CxWave.Wave.Framework.Type.TimerHandle;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Source.WaveJavaSourceRepository;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;
import com.CxWave.Wave.Resources.ResourceEnums.WaveMessageStatus;

@NonWorker
public class WaveWorker extends WaveElement
{
    private final boolean m_linkWorkerToParentObjectManager = true;

    public WaveWorker (final WaveObjectManager waveObjectManager)
    {
        super (waveObjectManager);

        if (m_linkWorkerToParentObjectManager)
        {
            waveObjectManager.addWorker (this);
        }
    }

    @Override
    protected void trace (final TraceLevel requestedTraceLevel, final String stringToTrace, final boolean addNewLine, final boolean suppressPrefix)
    {
        m_waveObjectManager.trace (requestedTraceLevel, stringToTrace, addNewLine, suppressPrefix);
    }

    @Override
    protected void trace (final TraceLevel requestedTraceLevel, final String stringToTrace)
    {
        m_waveObjectManager.trace (requestedTraceLevel, stringToTrace);
    }

    @Override
    protected void tracePrintf (final TraceLevel requestedTraceLevel, final boolean addNewLine, final boolean suppressPrefix, final String formatString, final Object... objects)
    {
        m_waveObjectManager.tracePrintf (requestedTraceLevel, addNewLine, suppressPrefix, formatString, objects);
    }

    @Override
    protected void tracePrintf (final TraceLevel requestedTraceLevel, final String formatString, final Object... objects)
    {
        m_waveObjectManager.tracePrintf (requestedTraceLevel, formatString, objects);
    }

    @Override
    protected void holdMessages ()
    {
        m_waveObjectManager.holdMessages ();
    }

    @Override
    protected void holdHighPriorityMessages ()
    {
        m_waveObjectManager.holdHighPriorityMessages ();
    }

    @Override
    protected void holdEvents ()
    {
        m_waveObjectManager.holdEvents ();
    }

    @Override
    public void holdAll ()
    {
        m_waveObjectManager.holdAll ();
    }

    @Override
    protected void unholdMessages ()
    {
        m_waveObjectManager.unholdMessages ();
    }

    @Override
    protected void unholdHighPriorityMessages ()
    {
        m_waveObjectManager.unholdHighPriorityMessages ();
    }

    @Override
    protected void unholdEvents ()
    {
        m_waveObjectManager.unholdEvents ();
    }

    @Override
    public void unholdAll ()
    {
        m_waveObjectManager.unholdAll ();
    }

    @Override
    public void updateTimeConsumedInThisThread (final UI32 operationCode, final int currentStep, final long lastLapDuration)
    {
        m_waveObjectManager.updateTimeConsumedInThisThread (operationCode, currentStep, lastLapDuration);
    }

    @Override
    public void updateRealTimeConsumedInThisThread (final UI32 operationCode, final int currentStep, final long lastLapDuration)
    {
        m_waveObjectManager.updateRealTimeConsumedInThisThread (operationCode, currentStep, lastLapDuration);
    }

    public void addSupportedOperations ()
    {
        final Map<Class<?>, Method> messageHandlersInInheritanceHierarchyPreferringLatest = WaveJavaSourceRepository.getMessageHandlersInInheritanceHierarchyPreferringLatest ((getClass ()).getName ());

        for (final Map.Entry<Class<?>, Method> entry : messageHandlersInInheritanceHierarchyPreferringLatest.entrySet ())
        {
            infoTracePrintf ("WaveWorker.addSupportedOperations :             Adding worker message handler for  %s : %s", (entry.getKey ()).getName (), (entry.getValue ()).getName ());

            m_waveObjectManager.addOperationMapForMessageClass (entry.getKey (), entry.getValue (), this);
        }
    }

    @Override
    @NonMessageHandler
    protected ResourceId reply (final WaveMessage waveMessage)
    {
        return (m_waveObjectManager.reply (waveMessage));
    }

    @Override
    protected ResourceId commitTransaction ()
    {
        return (m_waveObjectManager.commitTransaction ());
    }

    @Override
    protected void rollbackTransaction ()
    {
        m_waveObjectManager.rollbackTransaction ();
    }

    protected void waveAssert ()
    {
        m_waveObjectManager.waveAssert ();
    }

    protected void waveAssert (final boolean isAssertNotRequired)
    {
        m_waveObjectManager.waveAssert (isAssertNotRequired);
    }

    public void initialize (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        infoTracePrintf ("WaveWorker.initialize : Entering for %s ...", (getClass ()).getName ());

        waveAsynchronousContextForBootPhases.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        waveAsynchronousContextForBootPhases.callback ();
    }

    public void enable (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        infoTracePrintf ("WaveWorker.enable : Entering for %s ...", (getClass ()).getName ());

        waveAsynchronousContextForBootPhases.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        waveAsynchronousContextForBootPhases.callback ();
    }

    public void install (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        infoTracePrintf ("WaveWorker.install : Entering for %s ...", (getClass ()).getName ());

        waveAsynchronousContextForBootPhases.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        waveAsynchronousContextForBootPhases.callback ();
    }

    public void boot (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        infoTracePrintf ("WaveWorker.boot : Entering for %s ...", (getClass ()).getName ());

        waveAsynchronousContextForBootPhases.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        waveAsynchronousContextForBootPhases.callback ();
    }

    public void listenForEvents (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        infoTracePrintf ("WaveWorker.listenForEvents : Entering for %s ...", (getClass ()).getName ());

        waveAsynchronousContextForBootPhases.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        waveAsynchronousContextForBootPhases.callback ();
    }

    @NonMessageHandler
    @Override
    protected WaveMessageStatus sendOneWay (final WaveMessage waveMessage)
    {
        return (m_waveObjectManager.sendOneWay (waveMessage));
    }

    @Override
    protected WaveMessageStatus sendOneWay (final WaveMessage waveMessage, final LocationId locationId)
    {
        return (m_waveObjectManager.sendOneWay (waveMessage, locationId));
    }

    @NonMessageHandler
    @Override
    protected WaveMessageStatus sendSynchronously (final WaveMessage waveMessage)
    {
        return (m_waveObjectManager.sendSynchronously (waveMessage));
    }

    @Override
    protected WaveMessageStatus sendSynchronously (final WaveMessage waveMessage, final LocationId locationId)
    {
        return (m_waveObjectManager.sendSynchronously (waveMessage, locationId));
    }

    public void listenForEventsDefaultImplementation ()
    {
        infoTracePrintf ("WaveWorker.listenForEventsDefaultImplementation : Entering ...");

        final Map<Class<?>, Method> eventHandlersForThisClass = WaveJavaSourceRepository.getEventHandlersInInheritanceHierarchyPreferringLatest ((getClass ()).getTypeName ());

        for (final Map.Entry<Class<?>, Method> entry : eventHandlersForThisClass.entrySet ())
        {
            final Class<?> eventClass = entry.getKey ();
            final Method eventHandlerMethod = entry.getValue ();

            waveAssert (null != eventClass);
            waveAssert (null != eventHandlerMethod);

            infoTracePrintf ("WaveWorker.listenForEventsDefaultImplementation : Adding Event Handler in OM : %s, for Event : %s using %s", m_waveObjectManager.getName (), eventClass.getTypeName (), (getClass ()).getTypeName ());

            addOperationMapForEventClass (eventClass, eventHandlerMethod, this);
        }
    }

    private void addOperationMapForEventClass (final Class<?> eventClass, final Method eventHandlerMethod, final WaveWorker waveWorker)
    {
        m_waveObjectManager.addOperationMapForEventClass (eventClass, eventHandlerMethod, waveWorker);
    }

    @Override
    @NonEventHandler
    protected WaveMessageStatus broadcast (final WaveEvent waveEvent)
    {
        return (m_waveObjectManager.broadcast (waveEvent));
    }

    @Override
    protected ResourceId startTimer (final TimerHandle timerHandle, final TimeValue startInterval, final WaveTimerExpirationHandler waveTimerExpirationCallback, final Object waveTimerExpirationContext, final WaveElement waveTimerSender)
    {
        return (startTimer (timerHandle, startInterval, new TimeValue (0, 0), waveTimerExpirationCallback, waveTimerExpirationContext, waveTimerSender));
    }

    @Override
    protected ResourceId startTimer (final TimerHandle timerHandle, final TimeValue startInterval, final WaveTimerExpirationHandler waveTimerExpirationCallback, final Object waveTimerExpirationContext)
    {
        return (startTimer (timerHandle, startInterval, waveTimerExpirationCallback, waveTimerExpirationContext, this));
    }

    @Override
    protected ResourceId startTimer (final TimerHandle timerHandle, final TimeValue startInterval, final TimeValue periodicInterval, final WaveTimerExpirationHandler waveTimerExpirationCallback, final Object waveTimerExpirationContext, final WaveElement waveTimerSender)
    {
        return (m_waveObjectManager.startTimer (timerHandle, startInterval, periodicInterval, waveTimerExpirationCallback, waveTimerExpirationContext, waveTimerSender));
    }

    @Override
    protected ResourceId startTimer (final TimerHandle timerHandle, final TimeValue startInterval, final TimeValue periodicInterval, final WaveTimerExpirationHandler waveTimerExpirationCallback, final Object waveTimerExpirationContext)
    {
        return (startTimer (timerHandle, startInterval, periodicInterval, waveTimerExpirationCallback, waveTimerExpirationContext, this));
    }

    @Override
    protected ResourceId startTimer (final TimerHandle timerHandle, final long startIntervalMilliSeconds, final long periodicIntervalMilliSeconds, final WaveTimerExpirationHandler waveTimerExpirationCallback, final Object waveTimerExpirationContext, final WaveElement waveTimerSender)
    {
        return (m_waveObjectManager.startTimer (timerHandle, startIntervalMilliSeconds, periodicIntervalMilliSeconds, waveTimerExpirationCallback, waveTimerExpirationContext, waveTimerSender));
    }

    @Override
    protected ResourceId startTimer (final TimerHandle timerHandle, final long startIntervalMilliSeconds, final long periodicIntervalMilliSeconds, final WaveTimerExpirationHandler waveTimerExpirationCallback, final Object waveTimerExpirationContext)
    {
        return (m_waveObjectManager.startTimer (timerHandle, startIntervalMilliSeconds, periodicIntervalMilliSeconds, waveTimerExpirationCallback, waveTimerExpirationContext, this));
    }

    @Override
    protected ResourceId startTimer (final TimerHandle timerHandle, final long startIntervalMilliSeconds, final WaveTimerExpirationHandler waveTimerExpirationCallback, final Object waveTimerExpirationContext, final WaveElement waveTimerSender)
    {
        return (m_waveObjectManager.startTimer (timerHandle, startIntervalMilliSeconds, waveTimerExpirationCallback, waveTimerExpirationContext, waveTimerSender));
    }

    @Override
    protected ResourceId startTimer (final TimerHandle timerHandle, final long startIntervalMilliSeconds, final WaveTimerExpirationHandler waveTimerExpirationCallback, final Object waveTimerExpirationContext)
    {
        return (m_waveObjectManager.startTimer (timerHandle, startIntervalMilliSeconds, waveTimerExpirationCallback, waveTimerExpirationContext, this));
    }

    @Override
    protected ResourceId deleteTimer (final TimerHandle timerHandle)
    {
        return (m_waveObjectManager.deleteTimer (timerHandle));
    }

    public WaveServiceId getServiceId ()
    {
        return (m_waveObjectManager.getServiceId ());
    }

    public boolean getAllowAutomaticallyUnlistenForEvents ()
    {
        return (m_waveObjectManager.getAllowAutomaticallyUnlistenForEvents ());
    }

    protected void setIsEnabled (final boolean isEnabled)
    {
        m_waveObjectManager.setIsEnabled (isEnabled);
    }

    @Override
    protected WaveMessageStatus send (final WaveMessage waveMessage, final WaveMessageResponseHandler waveMessageCallback, final Object waveMessageContext)
    {
        return (send (waveMessage, waveMessageCallback, waveMessageContext, 0, LocationId.NullLocationId, this));
    }

    @Override
    protected WaveMessageStatus send (final WaveMessage waveMessage, final WaveMessageResponseHandler waveMessageCallback, final Object waveMessageContext, final long timeOutInMilliSeconds, final LocationId locationId, final WaveElement waveMessageSender)
    {
        return (m_waveObjectManager.send (waveMessage, waveMessageCallback, waveMessageContext, timeOutInMilliSeconds, locationId, waveMessageSender));
    }

    @Override
    @NonLightPulseHandler
    protected WaveMessageStatus broadcastLightPulse (final LightPulse lightPulse)
    {
        return (m_waveObjectManager.broadcastLightPulse (lightPulse));
    }

    @Override
    protected void addLightPulseType (final String lightPulseName)
    {
        addLightPulseType (lightPulseName, this);
    }

    @Override
    protected void addLightPulseType (final String lightPulseName, final WaveElement waveElement)
    {
        m_waveObjectManager.addLightPulseType (lightPulseName, waveElement);
    }

    public void unlistenEvents ()
    {
        m_waveObjectManager.unlistenEvents ();
    }

    @NonLightPulseHandler
    public void handleLightPulse (final LightPulse lightPulse)
    {
        final WaveObjectManager waveObjectManager = getWaveObjectManager ();

        waveAssert (null != waveObjectManager);

        waveObjectManager.handleWaveLightPulse (lightPulse);
    }
}

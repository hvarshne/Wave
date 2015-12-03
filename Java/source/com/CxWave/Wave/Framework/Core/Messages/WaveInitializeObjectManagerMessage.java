/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Messages;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.ObjectModel.FrameworkOpCodes;
import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.Message;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Resources.ResourceEnums.WaveBootReason;

@Message (om = WaveObjectManager.class)
public class WaveInitializeObjectManagerMessage extends WaveMessage
{
    private final WaveBootReason m_reason;

    public WaveInitializeObjectManagerMessage ()
    {
        super (WaveServiceId.NullServiceId, FrameworkOpCodes.WAVE_OBJECT_MANAGER_INITIALIZE);

        m_reason = WaveBootReason.WAVE_BOOT_FIRST_TIME_BOOT;
    }

    public WaveInitializeObjectManagerMessage (final WaveServiceId id, final WaveBootReason reason)
    {
        super (id, FrameworkOpCodes.WAVE_OBJECT_MANAGER_INITIALIZE);

        m_reason = reason;
    }

    public WaveBootReason getReason ()
    {
        return m_reason;
    }
}

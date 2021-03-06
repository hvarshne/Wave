/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Type.WaveOperationCodeInterface;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;

public enum FrameworkOpCodes implements WaveOperationCodeInterface
{
    // @formatter:off

    // There cannot be more than 1000 entries here

    WAVE_OBJECT_MANAGER_INITIALIZE,
    WAVE_OBJECT_MANAGER_LISTEN_FOR_EVENTS,
    WAVE_OBJECT_MANAGER_ENABLE,
    WAVE_OBJECT_MANAGER_INSTALL,
    WAVE_OBJECT_MANAGER_BOOT,
    WAVE_OBJECT_MANAGER_POSTBOOT,
    WAVE_OBJECT_MANAGER_HEARTBEAT_FAILURE,
    WAVE_OBJECT_MANAGER_CONFIG_REPLAY_END,
    WAVE_OBJECT_MANAGER_SLOT_FAILOVER,
    WAVE_OBJECT_MANAGER_EXTERNAL_STATE_SYNCHRONIZATION,
    WAVE_OBJECT_MANAGER_DISABLE,
    WAVE_OBJECT_MANAGER_SHUTDOWN,
    WAVE_OBJECT_MANAGER_UNINSTALL,
    WAVE_OBJECT_MANAGER_UNINITIALIZE,
    WAVE_OBJECT_MANAGER_DESTRUCT,
    WAVE_OBJECT_MANAGER_PING,
    WAVE_OBJECT_MANAGER_PREPARE_FOR_REGRESSION,
    WAVE_OBJECT_MANAGER_PREPARE_FOR_REGRESSION2,
    WAVE_OBJECT_MANAGER_TEST,
    WAVE_OBJECT_MANAGER_TIMER_EXPIRED,
    WAVE_OBJECT_MANAGER_CREATE_CLUSTER_COLLECT_VALIDATION_DATA,
    WAVE_OBJECT_MANAGER_CREATE_CLUSTER_VALIDATE,
    WAVE_OBJECT_MANAGER_CREATE_CLUSTER_SEND_VALIDATION_RESULTS,
    WAVE_OBJECT_MANAGER_FAILOVER,

    WAVE_OBJECT_MANAGER_REGISTER_EVENT_LISTENER,

    WAVE_OBJECT_MANAGER_PAUSE,
    WAVE_OBJECT_MANAGER_RESUME,

    WAVE_OBJECT_MANAGER_SET_CPU_AFFINITY,

    WAVE_OBJECT_MANAGER_LOAD_OPERATIONAL_DATA_FOR_MANAGED_OBJECT,

    WAVE_OBJECT_MANAGER_BACKEND_SYNC_UP,

    WAVE_OBJECT_MANAGER_MESSAGE_HISTORY_CONFIG,
    WAVE_OBJECT_MANAGER_MESSAGE_HISTORY_DUMP,

    WAVE_OBJECT_MANAGER_UPDATE_MANAGED_OBJECT,
    WAVE_OBJECT_MANAGER_CREATE_MANAGED_OBJECT,

    WAVE_OBJECT_MANAGER_DELETE_MANAGED_OBJECT,
    WAVE_OBJECT_MANAGER_FIPS_ZEROIZE,
    WAVE_OBJECT_MANAGER_UPGRADE,

    WAVE_OBJECT_MANAGER_HA_SYNC_COLLECT_VALIDATION_DATA,
    WAVE_OBJECT_MANAGER_HA_SYNC_VALIDATE_DATA,
    WAVE_OBJECT_MANAGER_HA_SYNC_SEND_VALIDATION_RESULTS,

    WAVE_OBJECT_MANAGER_HAINSTALL,
    WAVE_OBJECT_MANAGER_HABOOT,

    WAVE_OBJECT_MANAGER_GET_DEBUG_INFORMATION,
    WAVE_OBJECT_MANAGER_RESET_DEBUG_INFORMATION,

    WAVE_OBJECT_MANAGER_UPDATE_RELATIONSHIP,

    WAVE_OBJECT_MANAGER_FILE_REPLAY_END,

    // Multi-Partition cleanup.
    WAVE_OBJECT_MANAGER_PARTITION_CLEANUP,

    // Get Data From client
    WAVE_OBJECT_MANAGER_GET_CLIENT_DATA,

    //Bulk delete in Unified
    WAVE_OBJECT_MANAGER_DELETE_MANAGED_OBJECTS,

    WAVE_OBJECT_MANAGER_DATABASE_SANITY_CHECK,

    // Wave Broker Publish Message delivery

    WAVE_OBJECT_MANAGER_DELIVER_WAVE_BROKER_PUBLISH_MESSAGE,

    // Light Pulse delivery

    WAVE_OBJECT_MANAGER_DELIVER_WAVE_LIGHT_PULSE_MESSAGE,

    // The following must be the last two.
    // These opcodes are currently limited to be used by only
    // the remote transport service.

    WAVE_OBJECT_MANAGER_ANY_OPCODE,
    WAVE_OBJECT_MANAGER_ANY_EVENT;


    private static final long s_numberOfValues = (values ()).length;
    public static final long s_maximumNumberOfOpCodes = 1000;

    // @formatter:on

    private FrameworkOpCodes ()
    {
    }

    @Override
    public UI32 getOperationCode ()
    {
        WaveAssertUtils.waveAssert (s_numberOfValues <= s_maximumNumberOfOpCodes);

        if ((ordinal ()) == (s_numberOfValues - 1))
        {
            return (UI32.MAXIMUM);
        }
        else if ((ordinal ()) == (s_numberOfValues - 2))
        {
            return (new UI32 (UI32.MAXIMUM_LONG_VALUE - 1));
        }
        else
        {
            return new UI32 ((UI32.MAXIMUM_LONG_VALUE - s_maximumNumberOfOpCodes) + (ordinal ()));
        }
    }

    @Override
    public int getOperationCodeIntValue ()
    {
        return (((getOperationCode ()).getValue ()).intValue ());

    }
}

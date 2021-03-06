/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel.Annotations;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

import com.CxWave.Wave.Resources.ResourceEnums.WaveObjectManagerPriority;

@Retention (RetentionPolicy.RUNTIME)
@Target (
    { ElementType.TYPE
    })
public @interface ObjectManagerPriority
{
    public WaveObjectManagerPriority value () default WaveObjectManagerPriority.WAVE_OBJECT_MANAGER_PRIORITY_DEFAULT;
}

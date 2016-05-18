/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Attributes;

import java.util.HashSet;
import java.util.Set;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.Type.SI8;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;

public class AttributeSI8 extends Attribute
{
    public AttributeSI8 ()
    {
        super ();
    }

    public AttributeSI8 (final ReflectionAttribute reflectionAttribute)
    {
        super (reflectionAttribute);
    }

    @Override
    public Set<String> getSupportedDataTypes ()
    {
        final Set<String> supportedDataTypes = new HashSet<String> ();

        supportedDataTypes.add (byte.class.getTypeName ());
        supportedDataTypes.add (Byte.class.getTypeName ());

        return (supportedDataTypes);
    }

    @Override
    public void toWaveString (final SerializableObject thisSerializableObject, final StringBuffer value)
    {
        final Object object = getValue (thisSerializableObject);

        if (null == object)
        {
            return;
        }

        final SI8 data = (SI8) object;

        WaveAssertUtils.waveAssert (null != data);

        value.append (data.toString ());
    }

    @Override
    public void fromWaveString (final SerializableObject thisSerializableObject, final String value)
    {
        Object object = getValue (thisSerializableObject);

        if (null == object)
        {
            if (WaveStringUtils.isNotBlank (value))
            {
                object = new SI8 (0);
            }
            else
            {
                return;
            }
        }

        final SI8 data = (SI8) object;

        final String valueString = value;

        data.fromWaveString (valueString);
    }
}

/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Type;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;

public class UI8
{
    private Byte m_value;

    public UI8 (final byte value)
    {
        setValue (value);
    }

    public UI8 (final long value)
    {
        setValue (value);
    }

    public UI8 (final UI8 rhs)
    {
        setValue (rhs);
    }

    @Override
    public boolean equals (final Object object)
    {
        if (!(object instanceof UI8))
        {
            return (false);
        }

        if (object == this)
        {
            return (true);
        }

        final UI8 rhs = (UI8) object;

        if (m_value == (rhs.getValue ()))
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }

    public Byte getValue ()
    {
        return (m_value);
    }

    public void setValue (final byte value)
    {
        m_value = new Byte (value);
    }

    public void setValue (final long value)
    {
        WaveAssertUtils.waveAssert (isValid (value));

        m_value = (byte) (value - (1 << 7));
    }

    public void setValue (final UI8 rhs)
    {
        m_value = new Byte (rhs.getValue ());
    }

    public boolean isValid (final long value)
    {
        if ((0 <= value) && ((1 << 8) > value))
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }

    public void increment ()
    {
        m_value++;
    }

    public void decrement ()
    {
        m_value--;
    }

    public boolean equals (final UI8 rhs)
    {
        return (m_value.equals (rhs.m_value));
    }
}

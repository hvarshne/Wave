/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Type;

public class UI64 implements Comparable<UI64>
{
    private Long m_value;

    public UI64 (final Long value)
    {
        setValue (value);
    }

    public UI64 (final long value)
    {
        setValue (value);
    }

    public UI64 (final UI64 rhs)
    {
        setValue (rhs);
    }

    public UI64 (final String value)
    {
        try
        {
            setValue (Long.valueOf (value));
        }
        catch (final NumberFormatException e)
        {
            setValue (0);
        }
    }

    @Override
    public boolean equals (final Object object)
    {
        if (null == object)
        {
            return (false);
        }

        if (!(object instanceof UI64))
        {
            return (false);
        }

        if (object == this)
        {
            return (true);
        }

        final UI64 rhs = (UI64) object;

        if (m_value == (rhs.getValue ()))
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }

    public Long getValue ()
    {
        return (m_value);
    }

    public void setValue (final long value)
    {
        m_value = new Long (value);
    }

    public void setValue (final Long value)
    {
        m_value = new Long (value);
    }

    public void setValue (final UI64 rhs)
    {
        m_value = new Long (rhs.getValue ());
    }

    public void increment ()
    {
        m_value++;
    }

    public void increment (final long incrementValue)
    {
        m_value += incrementValue;
    }

    public void decrement ()
    {
        m_value--;
    }

    public void decrement (final long decrementValue)
    {
        m_value -= decrementValue;
    }

    public boolean equals (final UI64 rhs)
    {
        return (m_value.equals (rhs.m_value));
    }

    @Override
    public String toString ()
    {
        return (m_value.toString ());
    }

    @Override
    public int hashCode ()
    {
        return (m_value.hashCode ());
    }

    @Override
    public int compareTo (final UI64 rhs)
    {
        return (m_value.compareTo (rhs.m_value));
    }

    public void fromWaveString (final String valueString)
    {
        try
        {
            setValue (Long.valueOf (valueString));
        }
        catch (final NumberFormatException e)
        {
            setValue (0);
        }
    }
}

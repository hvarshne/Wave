/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Shell;

public class ShellBase
{
    final String m_name;

    public ShellBase (final String name)
    {
        m_name = name;
    }

    public String getName ()
    {
        return (m_name);
    }

    public boolean isRootShell ()
    {
        return (false);
    }
}

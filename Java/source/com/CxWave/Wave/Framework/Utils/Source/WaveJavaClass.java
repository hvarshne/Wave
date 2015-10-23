/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.Source;

import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;

public class WaveJavaClass
{
    private final String                          m_name;
    private final Map<String, WaveJavaInterface>  m_superInterfaces;
    private final Map<String, WaveJavaAnnotation> m_annotations;
    private WaveJavaClass                         m_superClass;
    private final Map<String, WaveJavaClass>      m_childClasses;

    public WaveJavaClass (final String name)
    {
        m_name = name;
        m_superInterfaces = new HashMap<String, WaveJavaInterface> ();
        m_annotations = new HashMap<String, WaveJavaAnnotation> ();
        m_childClasses = new HashMap<String, WaveJavaClass> ();
    }

    public String getName ()
    {
        return m_name;
    }

    public void addSuperInterfaces (final Vector<String> superInterfaceNames)
    {
        for (final String superInterfaceName : superInterfaceNames)
        {
            if (WaveStringUtils.isNotBlank (superInterfaceName))
            {
                final WaveJavaInterface waveJavaSuperInterface = WaveJavaSourceRepository.getWaveJavaInterface (superInterfaceName);

                WaveAssertUtils.waveAssert (null != waveJavaSuperInterface);

                m_superInterfaces.put (superInterfaceName, waveJavaSuperInterface);
            }
        }
    }

    public Vector<String> getSuperInterfaceNames ()
    {
        final Vector<String> superInterfaceNames = new Vector<String> ();

        for (final String superInterfaceName : m_superInterfaces.keySet ())
        {
            if (WaveStringUtils.isNotBlank (superInterfaceName))
            {
                superInterfaceNames.add (superInterfaceName);
            }
            else
            {
                WaveAssertUtils.waveAssert ();
            }
        }

        return (superInterfaceNames);
    }

    public void addAnnotations (final Vector<String> annotationNames)
    {
        for (final String annotationName : annotationNames)
        {
            if (WaveStringUtils.isNotBlank (annotationName))
            {
                final WaveJavaAnnotation waveJavaAnnotation = WaveJavaSourceRepository.getWaveJavaAnnotation (annotationName);

                WaveAssertUtils.waveAssert (null != waveJavaAnnotation);

                m_annotations.put (annotationName, waveJavaAnnotation);
            }
        }
    }

    public Vector<String> getAnnotationNames ()
    {
        final Vector<String> annotationNames = new Vector<String> ();

        for (final String annotationName : m_annotations.keySet ())
        {
            if (WaveStringUtils.isNotBlank (annotationName))
            {
                annotationNames.add (annotationName);
            }
        }

        return (annotationNames);
    }

    private void addChildClass (final WaveJavaClass childClass)
    {
        WaveAssertUtils.waveAssert (null != childClass);

        m_childClasses.put (childClass.getName (), childClass);
    }

    public void setSuperClass (final String superClassName)
    {
        if (WaveStringUtils.isNotBlank (superClassName))
        {
            final WaveJavaClass waveJavaClass = WaveJavaSourceRepository.getWaveJavaClass (superClassName);

            WaveAssertUtils.waveAssert (null != waveJavaClass);

            m_superClass = waveJavaClass;

            m_superClass.addChildClass (this);
        }
    }

    public String getSuperClassName ()
    {
        String superClassName = null;

        if (null != m_superClass)
        {
            superClassName = m_superClass.getName ();
        }

        return (superClassName);
    }
}

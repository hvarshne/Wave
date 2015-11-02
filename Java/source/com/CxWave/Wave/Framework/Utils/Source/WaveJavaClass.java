/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.Source;

import java.lang.annotation.Annotation;
import java.lang.reflect.Field;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.Vector;

import com.CxWave.Wave.Framework.Attributes.ReflectionAttributesMap;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class WaveJavaClass extends WaveJavaType
{
    private final String                          m_name;
    private final Map<String, WaveJavaInterface>  m_superInterfaces;
    private final Map<String, WaveJavaAnnotation> m_annotations;
    private WaveJavaClass                         m_superClass;
    private final Map<String, WaveJavaClass>      m_childClasses;
    private final Map<String, WaveJavaClass>      m_anonymousClasses;
    private WaveJavaClass                         m_declaringClass;
    private ReflectionAttributesMap               m_serializationReflectionAttributesMapForDeclaredFields;

    public WaveJavaClass (final String name)
    {
        m_name = name;
        m_superInterfaces = new HashMap<String, WaveJavaInterface> ();
        m_annotations = new HashMap<String, WaveJavaAnnotation> ();
        m_childClasses = new HashMap<String, WaveJavaClass> ();
        m_anonymousClasses = new HashMap<String, WaveJavaClass> ();
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

                waveJavaSuperInterface.addChildClass (this);
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
                if ((annotationName.startsWith ("java.")) || (annotationName.startsWith ("javax.")))
                {
                    continue;
                }

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
        if ((superClassName.startsWith ("java.")) || (superClassName.startsWith ("javax.")))
        {
            return;
        }

        if (WaveStringUtils.isNotBlank (superClassName))
        {
            final WaveJavaClass waveJavaClass = WaveJavaSourceRepository.getWaveJavaClass (superClassName);

            if (null == waveJavaClass)
            {
                WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_WARN, "Could not find super class : " + superClassName, true, false);
            }
            else
            {
                m_superClass = waveJavaClass;

                m_superClass.addChildClass (this);
            }
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

    private void addAnonymousClass (final WaveJavaClass anonymousClass)
    {
        WaveAssertUtils.waveAssert (null != anonymousClass);

        m_anonymousClasses.put (anonymousClass.getName (), anonymousClass);

    }

    public void setDeclaringClass (final String declaringClassName)
    {
        if (WaveStringUtils.isNotBlank (declaringClassName))
        {
            final WaveJavaClass waveJavaClass = WaveJavaSourceRepository.getWaveJavaClass (declaringClassName);

            WaveAssertUtils.waveAssert (null != waveJavaClass);

            m_declaringClass = waveJavaClass;

            m_declaringClass.addAnonymousClass (this);
        }
    }

    @Override
    public void compute ()
    {
        Class<?> reflectionClass = null;

        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_INFO, "Computing for Java Class " + m_name, true, false);

        try
        {
            reflectionClass = Class.forName (m_name);
        }
        catch (final ClassNotFoundException e)
        {
            e.printStackTrace ();
            WaveAssertUtils.waveAssert ();
        }

        final Class<?> reflectionSuperClass = reflectionClass.getSuperclass ();

        setSuperClass (reflectionSuperClass.getName ());

        final Class<?>[] superInterfaces = reflectionClass.getInterfaces ();
        final Vector<String> superInterfaceNames = new Vector<String> ();

        for (final Class<?> superInterface : superInterfaces)
        {
            superInterfaceNames.add (superInterface.getName ());
        }

        addSuperInterfaces (superInterfaceNames);

        final Annotation[] annotations = reflectionClass.getAnnotations ();
        final Vector<String> annotationNames = new Vector<String> ();

        for (final Annotation annotation : annotations)
        {
            annotationNames.add ((annotation.annotationType ()).getName ());
        }

        addAnnotations (annotationNames);

        computeSerializationReflectionAttributesMapForDeclaredFields (reflectionClass);
    }

    private void computeSerializationReflectionAttributesMapForDeclaredFields (final Class<?> reflectionClass)
    {
        final Field[] declaredFields = reflectionClass.getDeclaredFields ();
    }

    public Set<String> getAllDescendants ()
    {
        final Set<String> allDescendantsSet = new HashSet<String> ();

        for (final Map.Entry<String, WaveJavaClass> descendant : m_childClasses.entrySet ())
        {
            allDescendantsSet.add (descendant.getKey ());

            allDescendantsSet.addAll ((descendant.getValue ()).getAllDescendants ());
        }

        return (allDescendantsSet);
    }

    public boolean isAnnotatedWith (final String annotationName)
    {
        return (m_annotations.containsKey (annotationName));
    }

    public ReflectionAttributesMap getSerializationReflectionAttributesMapForDeclaredFields ()
    {
        return (m_serializationReflectionAttributesMapForDeclaredFields);
    }
}

/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangImport.h"
#include "Modeling/YANG/ObjectModel/YangPrefix.h"
#include "Framework/Utils/AssertUtils.h"

namespace WaveNs
{

YangImport::YangImport ()
    : YangElement (getYangName (), "")
{
}

YangImport::~YangImport()
{
}

string YangImport::getYangName ()
{
    return ("import");
}

YangElement *YangImport::createInstance ()
{
    return (new YangImport ());
}

string YangImport::getModule () const
{
    return (m_module);
}

void YangImport::setModule (const string &module)
{
    m_module = module;
}


string YangImport::getPrefix () const
{
    return (m_prefix);
}

void YangImport::setPrefix (const string &prefix)
{
    m_prefix = prefix;
}

void YangImport::processChildElement (YangElement *pYangElement)
{
    YangElement::processChildElement (pYangElement);

    const string yangName = pYangElement->getYangName ();

    if ((YangPrefix::getYangName()) == yangName)
    {
        YangPrefix *pYangPrefix = dynamic_cast<YangPrefix *> (pYangElement);

        waveAssert (NULL != pYangPrefix, __FILE__, __LINE__);

        string prefixValue;

        pYangPrefix->getAttributeValue ("value", prefixValue);

        waveAssert ("" != prefixValue, __FILE__, __LINE__);

        setPrefix (prefixValue);
    }
}
void YangImport::processAttribute (const string &attributeName, const string &attributeValue)
{
    YangElement::processAttribute (attributeName, attributeValue);

    if ("module" == attributeName)
    {
        setModule (attributeValue);
    }
}

}

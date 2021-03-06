/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/WaveSourceGenerator/WaveSourceGeneratorForManagedObject.h"

namespace WaveNs
{

WaveSourceGeneratorForManagedObject::WaveSourceGeneratorForManagedObject (const string &name, const string &nameSpace)
    : WaveSourceGeneratorBase (name, nameSpace)
{
}

WaveSourceGeneratorForManagedObject::~WaveSourceGeneratorForManagedObject ()
{
}

string WaveSourceGeneratorForManagedObject::generateClassName () const
{
    return (m_name);
}

string WaveSourceGeneratorForManagedObject::generateHIncludes () const
{
    string hIncludes = "#include \"Framework/ObjectModel/WaveManagedObject.h\"\n"
                       "\n";

    return (hIncludes);
}

string WaveSourceGeneratorForManagedObject::generateHClassBegin () const
{
    string classBegin = "class " + generateClassName () + " : public WaveManagedObject\n"
                        "{\n";

    return (classBegin);
}

string WaveSourceGeneratorForManagedObject::generateHClassMemberFunctionsPrivate () const
{
    string memberFunctionsPublic = "    private :\n"
                                   "        void setupAttributesForPersistence ();\n"
                                   "        void setupAttributesForCreate      ();\n"
                                   "\n";

    return (memberFunctionsPublic);
}

string WaveSourceGeneratorForManagedObject::generateHClassMemberFunctionsPublic () const
{
    string memberFunctionsPublic = "    public :\n"
                                   "                 " + generateClassName () + " (WaveObjectManager *pWaveObjectManager);\n"
                                   "        virtual        ~" + generateClassName () + " ();\n"
                                   "\n"
                                   "        static  string  getClassName ();\n";

    return (memberFunctionsPublic);
}

string WaveSourceGeneratorForManagedObject::generateCppMemberFunctions () const
{
    string memberFunctions;

    memberFunctions += generateClassName () + "::" + generateClassName () + " (WaveObjectManager *pWaveObjectManager)\n"
                       "    : WaveElement           (pWaveObjectManager),\n"
                       "      WavePersistableObject (" + generateClassName () + "::getClassName (), WaveManagedObject::getClassName ()),\n"
                       "      WaveManagedObject     (pWaveObjectManager)\n"
                       "{\n"
                       "}\n"
                       "\n";

    memberFunctions += generateClassName () + "::~" + generateClassName () + " ()\n"
                       "{\n"
                       "}\n"
                       "\n";

    memberFunctions += "void " + generateClassName () + "::getClassName ()\n"
                       "{\n"
                       "    return (\"" + generateClassName () + "\");\n"
                       "}\n"
                       "\n";

    memberFunctions += "void " + generateClassName () + "::setupAttributesForPersistence ()\n"
                       "{\n"
                       "    WaveManagedObject::setupAttributesForPersistence ();\n"
                       "\n"
                       "    // This class Specific Attributes below\n"
                       "    <AUTOGENERATED : FILLME>\n"
                       "}\n"
                       "\n";

    memberFunctions += "void " + generateClassName () + "::setupAttributesForCreate ()\n"
                       "{\n"
                       "    WaveManagedObject::setupAttributesForCreate ();\n"
                       "\n"
                       "    // This class Specific Attributes below\n"
                       "    <AUTOGENERATED : FILLME>\n"
                       "}\n"
                       "\n";

    return (memberFunctions);
}

}

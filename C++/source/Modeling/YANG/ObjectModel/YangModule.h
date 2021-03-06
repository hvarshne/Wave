/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGMODULE_H
#define YANGMODULE_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangGrouping;
class YangTypedef;

class YangModule : public YangElement
{
    private :
                void          addNamespace                    (const string &namespacePrefix, const string &namespaceString);

    protected :
    public :
                              YangModule                      ();
                              YangModule                      (const string &name);
        virtual              ~YangModule                      ();

        static  string        getYangName                     ();

        static  YangElement  *createInstance                  ();

        virtual void          processAttribute                (const string &attributeName, const string &attributeValue);

        virtual void          processChildElement             (YangElement *pYangElement);

                string        getImportedModuleName           (const string &importedModulePrefix) const;
                void          addImportedModuleDetails        (const string &importedModulePrefix, const string &importedModuleName);
                bool          isAKnownImportedModulePrefix    (const string &importedModulePrefix) const;

                bool          isAKnownGrouping                (const string &groupingName) const;
                void          addGrouping                     (YangGrouping *pYangGrouping);
                YangGrouping *getGrouping                     (const string &groupingName) const;

                void          incrementUsageCountForGrouping  (const string &groupingName);
                void          incrementUsageCountForGroupingForProgrammingLanguages (const YangModuleCollection *pYangModuleCollection, const string &groupingName);

                void          getClonedChildrenForGrouping    (const string &groupingName, vector<YangElement *> &clonedChildrenForGrouping) const;

                void          removeAllUnusedGroupings        ();
                void          removeAllGroupings              ();

        virtual void          computeCliTargetNodeNameForSelf ();

                string        getPrefix                       () const;
                void          setPrefix                       (const string &prefix);

                bool          isAKnownTypedef                 (const string &typedefName) const;
                void          addTypedef                      (YangTypedef *pYangTypedef);
                YangTypedef  *getTypedef                      (const string &typedefName) const;
                void          getClonedChildrenForTypedef     (string &typedefName, vector<YangElement *> &clonedChildrenForTypedef) const;
                void          removeAllTypedefs               ();
                string        getNamespaceStringForPrefix     (const string &namespacePrefix) const;
                string        getNamespaceUri                 () const;

        static  bool          compareYangModulesByNamespaceUri  (YangModule *pYangModule, YangModule *pYangModule2);

        virtual void          generateHFileForCLanguage         (const YangModuleCollection &yangModuleCollection) const;

                string        getFileName                       () const;
                void          setFileName                       (const string &fileName);

                string        getHFileNameForCLanguageWithoutDirectory       () const;

                void          getPreifxAndPostfixStringsForHFileForCLanguage (string &prefix, string &postfix, const YangModuleCollection &yangModuleCollection);

    // Now the data members

    private :
        string                      m_fileName;
        string                      m_prefix;
        map<string, string>         m_importedModulesMap;
        map<string, YangGrouping *> m_groupingsMap;
        map<string, YangTypedef *>  m_typedefsMap;

        map<string, string>         m_namespacePrefixToNamespaceMap;

        static const string         s_xmlnsTokenPrefix;

        string                      m_namespaceUri;

    protected :
    public :
};

}

#endif // YANGMODULE_H

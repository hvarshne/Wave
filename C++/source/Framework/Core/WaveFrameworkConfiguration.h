/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEFRAMEWORKCONFIGURATION_H
#define WAVEFRAMEWORKCONFIGURATION_H

#include "Framework/ObjectModel/SerializableObject.h"
#include "Framework/LocationManagement/LocationBase.h"
#include "Framework/Types/Types.h"
#include <vector>
#include <string>

namespace WaveNs
{

class WaveFrameworkConfiguration : virtual public SerializableObject
{
    private :
    protected :
        virtual void setupAttributesForSerialization                        ();
        virtual void setupAttributesForSerializationInAttributeOrderFormat  ();

    public :
                            WaveFrameworkConfiguration    ();
                           ~WaveFrameworkConfiguration    ();
        ResourceId          initializeConfiguration        ();
        ResourceId          saveConfiguration              (const string &configurationFileName);
        ResourceId          loadConfiguration              (const string &configurationFileName);
        ResourceId          validateConfiguration          ();

        string              getThisLocationIpAddress       () const;
        SI32                getThisLocationPort            () const;
        LocationRole        getThisLocationRole            () const;
        void                setThisLocationRole            (const LocationRole& role); 
        LocationId          getThisLocationLocationId      () const;
        void                setThisLocationLocationId      (const LocationId& locationid);
        string              getClusterPrimaryIpAddress     () const;
        SI32                getClusterPrimaryPort          () const;
        void                setClusterPrimaryPort          (const SI32& port);
        LocationId          getClusterPrimaryLocationId    () const;
        void                setClusterPrimaryLocationId    (const LocationId& locationid);
        vector<string>      getKnownLocationIpAddresses    () const;
        void                setKnownLocationIpAddresses    (const vector<string>& ipAddress);
        vector<SI32>        getKnownLocationPorts          () const;
        void                setKnownLocationPorts          (const vector<SI32>& ports);
        vector<LocationId>  getKnownLocationLocationIds    () const;
        void                setKnownLocationLocationIds    (const vector<LocationId>& loc);
        vector<string>      getKnownSubLocationIpAddress   () const;
        vector<SI32>        getKnownSubLocationPorts       () const;
        vector<LocationId>  getKnownSubLocationLocationIds () const;
        bool                getIsStartupValid              () const;
        void                setIsStartupValid              (const bool isValid);
        string              getStartupFileName             () const;
        void                setStartupFileName             (const string &fileName);
        ResourceId          getStartupFileType             () const;
        void                setStartupFileType             (const ResourceId &fileType);
        LocationId          getLastUsedLocationId          () const;
        void                setLastUsedLocationId          (const LocationId& locationid);
        bool                getDBRestoreIncomplete         () const;
        void                setDBRestoreIncomplete         (const bool dbRestoreIncomplete);

        void                display                        () const;
        void                displayToTerminal              () const;

        size_t              getSchemaChangeInfo            (vector<string> & managedObjectNames, vector<string> & managedObjectFieldNamesStrings,vector<string> & managedObjectFieldTypesStrings,vector<UI32> & classIds, vector<UI32> & parentClassIds, vector<string> & userDefinedKeyCombinationsFieldNamesForSchemaChange, vector<string> & userDefinedKeyCombinationsFieldTypesForSchemaChange, vector<string> &fieldNamesExpandedTypesForSchemaChange) const;

        bool                setSchemaChangeInfo            (vector<string> & managedObjectNames, vector<string> & managedObjectFieldNamesStrings,vector<string> & managedObjectFieldTypesStrings,vector<UI32> & classIds, vector<UI32> & parentClassIds, vector<string> & userDefinedKeyCombinationsFieldNamesForSchemaChange, vector<string> & userDefinedKeyCombinationsFieldTypesForSchemaChange, vector<string> &fieldNamesExpandedTypesForSchemaChange);
        
    // now the data members

    private :
        string             m_thisLocationIpAddress;
        SI32               m_thisLocationPort;
        ResourceId         m_thisLocationRole; // LocationRole - For Serialization, enums are not allowed - must user corresponding ResourceId values.
        LocationId         m_thisLocationLocationId;
        string             m_clusterPrimaryIpAddress;
        SI32               m_clusterPrimaryPort;
        LocationId         m_clusterPrimaryLocationId;
        vector<string>     m_knownLocationIpAddresses;
        vector<SI32>       m_knownLocationPorts;
        vector<LocationId> m_knownLocationLocationIds;
        vector<string>     m_knownSubLocationIpAddresses;
        vector<SI32>       m_knownSubLocationPorts;
        vector<LocationId> m_knownSubLocationLocationIds;
        bool               m_isStartupValid;
        string             m_startupFileName;
        ResourceId         m_startupFileType;
        LocationId         m_lastUsedLocationId;
        bool               m_dbRestoreIncomplete;

        //Data members to be used to populate the .cfg file while generating sql for upgrade
        vector<string>     m_managedObjectNamesForSchemaChange;
        vector<string>     m_fieldNamesStringsForSchemaChange;
        vector<string>     m_fieldNamesTypesForSchemaChange;
        vector<UI32>       m_classIds;
        vector<UI32>       m_parentTableIds;
        vector<string>     m_userDefinedKeyCombinationsFieldNamesForSchemaChange;
        vector<string>     m_userDefinedKeyCombinationsFieldTypesForSchemaChange;
        vector<string>     m_fieldNamesExpandedTypesForSchemaChange;


    protected :
    public :

    friend class PersistentWaveBootAgent;
    friend class PersistentWithDefaultWaveBootAgent;
    friend class PersistentWithDefaultForHABootAgent;
    friend class WaveFrameworkObjectManagerHaSyncWorker;
};

}

#endif // WAVEFRAMEWORKCONFIGURATION_H

/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Cindy Hou                                                    *
 ***************************************************************************/

#ifndef ATTRIBUTES_HOSTUC_H
#define ATTRIBUTES_HOSTUC_H

#include "Framework/Attributes/Attribute.h"
#include "Framework/Attributes/AttributeUC.h"
#include "Framework/Types/HostUC.h"
#include "WaveResourceIdEnums.h"

namespace WaveNs
{

class AttributeHostUC : public Attribute, public AttributeUC
{
    private :
        virtual bool                validate                    () const;

    protected :
    public :
                                    AttributeHostUC             (const HostUC &data, const bool &isNoElement, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                    AttributeHostUC             (const HostUC &data, const bool &isNoElement, const bool &defaultFlag, const HostUC &defaultData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                    AttributeHostUC             (HostUC *pData, const bool &isNoElement, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                    AttributeHostUC             (HostUC *pData, const bool &isNoElement, const bool &defaultFlag, const HostUC &defaultData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                    AttributeHostUC             (const AttributeHostUC &attribute);
        virtual                    ~AttributeHostUC             ();
                AttributeHostUC    &operator =                  (const AttributeHostUC &attribute);
                HostUC              getValue                    () const;
                void                setValue                    (const HostUC &data);

        virtual string              getSqlType                  ();
        virtual void                setupOrm                    (OrmTable *pOrmTable);
        virtual string              getSqlForCreate             ();
        virtual void                getSqlForInsert             (string &sqlForPreValues, string &sqlForInsert, string &sqlForInsert2, bool isFirst = false);
        virtual void                getSqlForUpdate             (string &sqlForUpdate, string &sqlForUpdate2, bool isFirst = false);
        virtual void                getSqlForSelect             (string &sqlForSelect, AttributeConditionOperator attributeConditionOperator = WAVE_ATTRIBUTE_CONDITION_OPERATOR_EQUAL);
        virtual void                toString                    (string &valueString);
        virtual void                fromString                  (const string &valueString);
        virtual void                getPlainString              (string &valueString);
        virtual ResourceId          loadFromPlainString         (const string &valueString);
        virtual void               *getPData                    ();
        virtual void                setValue                    (const void *pData);
        virtual Attribute          *clone                       ();
        static  map<string, string> getSupportedConversions     ();

                bool                isCurrentValueSameAsDefault () const;
                HostUC              getDefaultData              () const;
                bool                getIsDefaultDataValidFlag   (void) const;

                bool                getIsNoElement              () const;
        virtual void                setDefaultValue             () ;
        virtual void                getCValue                   (WaveCValue *pCValue);
        virtual bool                getIsUserConfigured         ();
    // Now the data members

    private :
        HostUC *m_pData;
        HostUC  m_defaultData;
        bool    m_isDefaultDataValid; // if this is true, then default value is valid
        bool    m_isNoElement;

    protected :
    public :
};

}
#endif //ATTRIBUTES_HOSTUC_H

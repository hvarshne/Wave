#ifndef ATTRIBUTEUUID_H
#define ATTRIBUTEUUID_H

#include "Framework/Attributes/Attribute.h"
#include "Framework/Attributes/AttributeVector.h"
#include "Framework/Types/Uuid.h"
#include "WaveResourceIdEnums.h"

namespace WaveNs
{

class AttributeUUID : public Attribute
{
    private :
        virtual bool                    validate                        () const;
        virtual bool                    isConditionOperatorSupported    (AttributeConditionOperator attributeConditionOperator);

    protected :
    public :
                                        AttributeUUID                   (const Uuid &data, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                        AttributeUUID                   (const Uuid &data, const Uuid &defaultData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                        AttributeUUID                   (Uuid *pData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                        AttributeUUID                   (Uuid *pData, const Uuid &defaultData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                        AttributeUUID                   (const AttributeUUID &attribute);
        virtual                        ~AttributeUUID                   ();
                AttributeUUID          &operator =                      (const AttributeUUID &attribute);
                Uuid                    getValue                        () const;
                void                    setValue                        (const Uuid &data);
                Uuid                    getDefaultValue                 () const;
                bool                    getIsDefaultValueValidFlag      () const;
        virtual string                  getSqlType                      ();
        virtual void                    setupOrm                        (OrmTable *pOrmTable);
        virtual string                  getSqlForCreate                 ();
        virtual void                    getSqlForInsert                 (string &sqlForPreValues, string &sqlForInsert, string &sqlForInsert2, bool isFirst = false);
        virtual void                    getSqlForUpdate                 (string &sqlForUpdate, string &sqlForUpdate2, bool isFirst = false);
        virtual void                    getSqlForSelect                 (string &sqlForSelect, AttributeConditionOperator attributeConditionOperator = WAVE_ATTRIBUTE_CONDITION_OPERATOR_EQUAL);
        virtual void                    toString                        (string &valueString);
        virtual void                    fromString                      (const string &valueString);
        virtual void                   *getPData                        ();
        virtual void                    setValue                        (const void *pData);
        virtual Attribute              *clone                           ();
                bool                    isCurrentValueSameAsDefault     () const;
        static  map<string, string>     getSupportedConversions         ();
        virtual void                    setDefaultValue                 ();
        virtual void                    getCValue                       (WaveCValue *pCValue);
    // Now the data members

    private :
        Uuid *m_pData;
        Uuid  m_defaultData;
        bool  m_isDefaultDataValid;

    protected :
    public :
};

}

#endif // ATTRIBUTEUUID_H

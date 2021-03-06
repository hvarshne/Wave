/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef ORMASSOCIATION_H
#define ORMASSOCIATION_H

#include "Framework/ObjectRelationalMapping/OrmRelation.h"

namespace WaveNs
{

class OrmAssociation : public OrmRelation
{
    private :
    protected :
    public :
                                    OrmAssociation         (const string &name, const string &relatedTo, const OrmRelationType &relationType, const bool &canBeEmpty = false);
                                   ~OrmAssociation         ();

        virtual string              getSqlForCreate        (const string &schema) const;
        virtual string              getSqlForCreate2       (const string &parentName, const string &scehma) const;
        virtual string              getAuxilliaryTableName (const string &parentName) const;
        virtual OrmRelationUmlType  getRelationUmlType     () const;
        virtual string              getAlterSqlForOneToOneRelationship              (const string &schema,const string & tableName) const;
        virtual string              getAlterSqlToAddNotNullForOneToOneRelationship  (const string &schema,const string & tableName) const;
        virtual string              getAlterSqlToDropNotNullForOneToOneRelationship (const string &schema,const string & tableName) const;
                string              getOwnerClassFkeyConstraintName                           (const string &parentName) const;
                string              getOwnerInstanceFkeyConstraintName                        (const string &parentName) const;
                string              getRelatedClassFkeyConstraintName                         (const string &parentName) const;
                string              getRelatedInstanceFkeyConstraintName                      (const string &parentName) const;

    // Now the data memebers

    private :
        bool m_canBeEmpty;

    protected :
    public :
};

}

#endif // ORMASSOCIATION_H

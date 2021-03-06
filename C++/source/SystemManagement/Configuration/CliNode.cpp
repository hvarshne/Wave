/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "SystemManagement/Configuration/CliNode.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/StringUtils.h"

namespace WaveNs
{

CliNode::CliNode ()
{
}

CliNode::CliNode (const string &cliNodeName)
    : m_cliNodeName (cliNodeName)
{
}

CliNode::~CliNode ()
{
    destroyAndClearChildren ();
}

void CliNode::destroyAndClearChildren ()
{
    UI32 numberOfChildren = m_children.size ();
    UI32 i                = 0;

    for (i = 0; i < numberOfChildren; i++)
    {
        delete m_children[i];
    }

    m_children.clear    ();
    m_childrenMap.clear ();
}

string CliNode::getCliNodeName () const
{
    return (m_cliNodeName);
}

void CliNode::setCliNodeName (const string &cliNodeName)
{
    m_cliNodeName = cliNodeName;
}

void CliNode::addChild (const string &childCliNodeName)
{
    if (true == (isAKnownChild (childCliNodeName)))
    {
        waveAssert (false, __FILE__, __LINE__);
    }

    waveAssert ("" != childCliNodeName, __FILE__, __LINE__);

    CliNode * const pNewCliNode = new CliNode (childCliNodeName);

    waveAssert (NULL != pNewCliNode, __FILE__, __LINE__);

    addChild (pNewCliNode);
}

void CliNode::addChild (CliNode * const pChildCliNode)
{
    waveAssert (NULL != pChildCliNode, __FILE__, __LINE__);

    string childCliNodeName = pChildCliNode->getCliNodeName ();

    waveAssert ("" != childCliNodeName, __FILE__, __LINE__);

    if (false == (isAKnownChild (childCliNodeName)))
    {
        m_children.push_back (pChildCliNode);
        m_childrenMap[childCliNodeName] = pChildCliNode;
    }
    else
    {
        waveAssert (false, __FILE__, __LINE__);
    }
}

bool CliNode::isAKnownChild (const string &childCliNodeName) const
{
    map<string, CliNode *>::const_iterator element    = m_childrenMap.find (childCliNodeName);
    map<string, CliNode *>::const_iterator endElement = m_childrenMap.end  ();

    if (endElement != element)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

CliNode *CliNode::getChild (const string &childCliNodeName)
{
    if (true == (isAKnownChild (childCliNodeName)))
    {
        return (m_childrenMap[childCliNodeName]);
    }
    else
    {
        return (NULL);
    }
}

void CliNode::addCommandLine (const string &commandLine)
{
    vector<string> commandLineTokens;
    UI32           numberOfCommandLineTokens = 0;
    UI32           i                         = 0;
    CliNode       *pParentForNextLevel       = this;

    StringUtils::tokenize (commandLine, commandLineTokens, ' ');

    numberOfCommandLineTokens = commandLineTokens.size ();

    for (i = 0; i < numberOfCommandLineTokens; i++)
    {
        string commandLineToken = commandLineTokens[i];
        bool   isChildKnown     = pParentForNextLevel->isAKnownChild (commandLineToken);

        if (false == isChildKnown)
        {
            pParentForNextLevel->addChild (commandLineToken);
        }

        pParentForNextLevel = pParentForNextLevel->getChild (commandLineToken);

        waveAssert (NULL != pParentForNextLevel, __FILE__, __LINE__);
    }
}

void CliNode::getChildrenCliNodeNames (vector<string> &childrenCliNodeNames)
{
    UI32 numberOfChildren = m_children.size ();
    UI32 i                = 0;

    for (i = 0; i < numberOfChildren; i++)
    {
        CliNode *pTempCliNode = m_children[i];

        waveAssert (NULL != pTempCliNode, __FILE__, __LINE__);

        childrenCliNodeNames.push_back (pTempCliNode->getCliNodeName ());
    }
}

void CliNode::getChildrenCliNodeNamesForCommandLine (const string &commandLine, vector<string> &childrenCliNodeNames)
{
    vector<string> commandLineTokens;
    UI32           numberOfCommandLineTokens = 0;
    UI32           i                         = 0;
    CliNode       *pParentForNextLevel       = this;

    StringUtils::tokenize (commandLine, commandLineTokens, ' ');

    numberOfCommandLineTokens = commandLineTokens.size ();

    for (i = 0; i < numberOfCommandLineTokens; i++)
    {
        string commandLineToken = commandLineTokens[i];
        bool   isChildKnown     = pParentForNextLevel->isAKnownChild (commandLineToken);

        if (false == isChildKnown)
        {
            return;
        }

        pParentForNextLevel = pParentForNextLevel->getChild (commandLineToken);

        waveAssert (NULL != pParentForNextLevel, __FILE__, __LINE__);
    }

    pParentForNextLevel->getChildrenCliNodeNames (childrenCliNodeNames);
}

}

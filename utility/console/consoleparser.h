/* -*- mode: c++ -*-
   
   this file is part of Soccer Server 3D
   Copyright (C) 2002 Soccer Server Maintainance Group

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
  
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
 
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/
#ifndef UTILITY_CONSOLEPARSER_H
#define UTILITY_CONSOLEPARSER_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "scanner.h"
#include "variables/convar.h"

//! the statement separators

//! separates two statements
static const std::string SP_SEPARATOR = ";";
//! marks the remainder as a comment
static const std::string SP_COMMENT = "#";
//! the beginning of a vector
static const std::string SP_VECTOR_BEGIN = "<";
//! the float separator of a vector
static const std::string SP_VECTOR_SEP = ",";
//! the end of a vector
static const std::string SP_VECTOR_END = ">";

class Console;

/*! \class ConsoleParser
  $Id: consoleparser.h,v 1.3 2002/08/21 14:11:16 fruit Exp $

    ConsoleParser

    The console's parser which transforms a string to execute into a
    statementlist.

    A token is represented as a ConVar*, 
    a statement as a ConVar* container

    EBNF (or something close enough):
    statementlist    ::= statementlist statement ';' statement | statement
    statement        ::= command parameterlist | '#' anything | <EMPTY>
                         # is a comment, so everything after it is
                         simply ignored and may be anything

    parameterlist    ::= parameterlist parameter | parameter
    parameter        ::= int | float | string | vector | command | label
    int              ::= [0..9]+
    float            ::= int [ '.' [int]] | '.' int
    string           ::= '"' a string '"' | ''' a string '''
                         where a string may not contain the closing "
                         resp. ', which have to be escaped as '\"' and
                         '\''.
    vector           ::= '<' float ',' float ',' float '>'
    command          ::= a string
                         A command is a string which has the name of a
                         command known to the ClassServer.
    label            ::= a string    
                         A label is anything which does not fit into
                         the other categories it is interpreted by a
                         command as a variable, a constant, ...

    SEPARATORS: (defined with the constants SP_xxx)

    ';' : separates statements
    '#' : starts a comment. the rest of the input is ignored
    '<' : starts a vector : '<' float ',' float ',' float '>'
    ',' : seperates the parts of a vector
    '>' : terminates a vector

    HISTORY:
    The console subsystem was taken from a student project at the AI
    Research Group, Koblenz University. Original development by Marco
    Koegler <koegler@uni-koblenz.de>, Markus Rollmann
    <rollmark@uni-koblenz.de>, Alexander Fuchs <alexf@uni-koblenz.de>,
    et.al.
*/
class ConsoleParser
{
public:
    /*! a sequence of parsed statements (a statement is stored as
       a list of convars)
     */
    typedef std::list < ConVar::ConVars > StatementList;

    //! initializes the scanner
    ConsoleParser();
    ~ConsoleParser();

    /*! scans a string and converts it into a statement list the
       created statement list has to be destroyed with
       DeleteStatements by the caller on failure the statementlist is
       empty and has not to be deleted per default empty statements -
       statements without a token - are removed
     */
    std::pair < bool, StatementList >
    scan(const std::string& to_scan, bool remove_empty_statements = true) const;
    /*! checks the syntax of the statements,
       assures that every statement does begin with a command,
       removes empty statements
     */
    static bool parse(const StatementList& statements);
    //! deletes a statement list
    static void deleteStatements(const StatementList& statements);
    //! deletes the ConVars of the statement
    static void
    deleteStatement(ConVar::ConVars statement);

protected:
    ConsoleParser(const ConsoleParser &) {}
    ConsoleParser& operator =(const ConsoleParser &) {}

    //! a string list used by some methods
    typedef std::list < std::string > TStrings;

    //! wrapper for a more convenient call of Scan: the alias list is missing
    std::pair < bool, ConVar::ConVars >
    ConsoleParser::doScan(const std::string& input) const;
    /*! Scans the input and converts every token into an appropriate ConVar.
       The alias list is used to prevent a endless loop in expanding aliases,
       e.g. alias a "b"; alias b "a" is catched.
     */
    std::pair < bool, ConVar::ConVars >
    ConsoleParser::scan(const std::string & input, TStrings used_aliases) const;
    /*! These methods reuse the ConVars stored in their parameters,
       therefore the parameter contents may not be deleted. The token
       list is splitted into several statements at SP_SEPARATOR.
     */
    StatementList
    splitStatements(const ConVar::ConVars& tokens) const;
    //! removes the comments from a list of statements
    StatementList
    removeComments(const ConsoleParser::StatementList& statements) const;
    /*! Removes the comments from a statement,
       an empty statement may be the result.
     */
    ConVar::ConVars removeComment(const ConVar::ConVars& statement) const;
    /*! Replaces the tokens representing a vector with a vector token
       from a list of statements
     */
    StatementList
    replaceVectors(const ConsoleParser::StatementList& statements) const;
    /*! Replaces the tokens representing a vector with a vector token
       from a statement.
     */
    ConVar::ConVars replaceVector(const ConVar::ConVars& statement) const;
    /*! Tries to match a token sequence with a vector. If iter points
       to such a sequence, the sequence is deleted and instead a
       vector token is returned. Otherwise the token pointed to by the
       iter is returned unchanged.
     */
    ConVar::ConVars
    ConsoleParser::matchVector(ConVar::ConVars::const_iterator& iter,
                               ConVar::ConVars::const_iterator iter_end) const;
    //! removes all empty statements
    StatementList
    removeEmptyStatements(const ConsoleParser::StatementList& statements) const;
    //! tests if the ConVar* is of type separator and contains the given value
    static bool
    isItThisSeparator(const ConVar* con_var, const std::string& separator);

    //! the used scanner configuration
    Scanner::InitInfo M_scanner_info;
};

#endif                          // UTILITY_CONSOLEPARSER_H

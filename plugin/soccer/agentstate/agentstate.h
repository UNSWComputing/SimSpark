/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: agentstate.h,v 1.1.2.1 2004/01/06 21:47:45 rollmark Exp $

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/
#ifndef AGENTSTATE_H
#define AGENTSTATE_H

#include <oxygen/sceneserver/basenode.h>

class AgentState : public oxygen::BaseNode
{
    //
    // functions
    //
public:
    AgentState();
    virtual ~AgentState();

    /** set the team name */
    virtual void SetTeamName(std::string name);

    /** set the uniform number */
    virtual void SetUniformNumber(int number);

protected:
    /** team name */
    std::string mTeamName;

    /** uniform number */
    int mUniformNumber;
};

DECLARE_CLASS(AgentState);

#endif // AGENTSTATE_H

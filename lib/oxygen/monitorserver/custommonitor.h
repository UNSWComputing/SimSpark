/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: custommonitor.h,v 1.2 2004/12/31 14:10:36 rollmark Exp $

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
#ifndef OXYGEN_CUSTOMMONITOR_H
#define OXYGEN_CUSTOMMONITOR_H

#include <zeitgeist/leaf.h>
#include <oxygen/gamecontrolserver/predicate.h>

namespace oxygen
{

class CustomMonitor : public zeitgeist::Leaf
{
public:
    CustomMonitor();
    virtual ~CustomMonitor();

    /** This function will be called be called periodically from the
        monitor implementation to do any monitor updates. Custom
        predicates that the Monitor client receives are passed as a
        PredicateList
     */
    virtual void ParseCustomPredicates(const oxygen::PredicateList& pList) = 0;
};

} // namespace oxygen

DECLARE_ABSTRACTCLASS(CustomMonitor);

#endif // OXYGEN_CUSTOMMONITOR_H

/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: axis.h,v 1.4 2004/04/10 11:04:58 rollmark Exp $

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
#ifndef KEROSIN_AXIS_H
#define KEROSIN_AXIS_H

#include <oxygen/sceneserver/basenode.h>

namespace kerosin
{

class Axis : public oxygen::BaseNode
{
    //
    // Functions
    //
public:
    Axis();

    /** returns the size of an axis */
    float GetSize();

    /** sets the size of an axis */
    void SetSize(float size);

protected:
    virtual void RenderInternal();

protected:
    // size of an axis
    float mSize;
};

DECLARE_CLASS(Axis);

} //namespace kerosin
#endif //KEROSIN_AXIS_H

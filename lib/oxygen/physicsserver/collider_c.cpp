/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

this file is part of rcssserver3D
Fri May 9 2003
Copyright (C) 2003 Koblenz University
$Id: collider_c.cpp,v 1.7.18.1 2008/02/24 14:31:11 sgvandijk Exp $

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

#include "collider.h"

using namespace oxygen;
using namespace boost;
using namespace salt;
using namespace std;

FUNCTION(Collider,setPosition)
{
    Vector3f inPos;

    if (
        (in.GetSize() == 0) ||
        (! in.GetValue(in.begin(),inPos))
        )
        {
            return false;
        }

    obj->SetPosition(inPos);
    return true;
}

FUNCTION(Collider,setLocalPosition)
{
    Vector3f inPos;

    if (
        (in.GetSize() == 0) ||
        (! in.GetValue(in.begin(),inPos))
        )
        {
            return false;
        }

    obj->SetLocalPosition(inPos);
    return true;
}

FUNCTION(Collider,setRotation)
{
    Matrix inRot;
    if (!in.GetValue(in.begin(),inRot))
    {
        return false;
    }
    
    obj->SetRotation(inRot);
    return true;
}

FUNCTION(Collider,addCollisionHandler)
{
    string inHandlerName;

    if (
        (in.GetSize() != 1) ||
        (! in.GetValue(in.begin(),inHandlerName))
        )
        {
            return false;
        }

    return obj->AddCollisionHandler(inHandlerName);
}

void CLASS(Collider)::DefineClass()
{
    DEFINE_FUNCTION(setPosition);
    DEFINE_FUNCTION(setLocalPosition);
    DEFINE_FUNCTION(setRotation);
    DEFINE_FUNCTION(addCollisionHandler);
    DEFINE_BASECLASS(oxygen/ODEObject);
}

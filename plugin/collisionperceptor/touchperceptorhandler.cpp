/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: touchperceptorhandler.cpp,v 1.1 2007/05/31 14:48:58 hedayat Exp $

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

#include "touchperceptorhandler.h"
#include <oxygen/physicsserver/collider.h>
#include <oxygen/sceneserver/transform.h>
#include <oxygen/physicsserver/world.h>
#include <oxygen/physicsserver/space.h>
#include "extendedtouchperceptor.h"

using namespace oxygen;
using namespace boost;

void TouchPerceptorHandler::HandleCollision
(boost::shared_ptr<Collider> collidee, dContact& contact)
{
    if (
        (mCollider.get() == 0) ||
        (mWorld.get() == 0) ||
        (mSpace.get() == 0)
        )
        {
            return;
        }

    // to create a contact joint it we must have at least one body to
    // attach it to.
    dBodyID myBody = dGeomGetBody(mCollider->GetODEGeom());
    dBodyID collideeBody = dGeomGetBody(collidee->GetODEGeom());

    if (
        (myBody == 0) &&
        (collideeBody == 0)
        )
        {
            return;
        }

    shared_ptr<ContactJointHandler> handler =
        collidee->FindChildSupportingClass<ContactJointHandler>();

    if (handler.get() == 0)
        {
            return;
        }

    CalcSurfaceParam(contact.surface,handler->GetSurfaceParameter());

    dJointID joint = dJointCreateContact
        (mWorld->GetODEWorld(), mSpace->GetODEJointGroup(), &contact);

    dJointAttach (joint, myBody, collideeBody);


    // find the first CollisionPerceptor below our closest Transform node
    shared_ptr<Transform> transformParent = shared_static_cast<Transform>
      (make_shared(GetParentSupportingClass("Transform")));

    if (transformParent.get() == 0)
      {
        return;
      }

    shared_ptr<ExtendedTouchPerceptor> perceptor =
      shared_static_cast<ExtendedTouchPerceptor>
      (transformParent->GetChildSupportingClass("ExtendedTouchPerceptor", true));

    if (perceptor.get() == 0)
      {
          GetLog()->Error() << "TouchPerceptorHandler: no suitable child node found!\n";
        return;
      }

    // Can we avoid dynamic allocation to increase performance?!
    dJointSetFeedback(joint, new dJointFeedback());
    
    perceptor->AddTouchInfo(contact, joint);
}
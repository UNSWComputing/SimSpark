/* -*- mode: c++ -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2003 Koblenz University
   $Id: collider.cpp,v 1.4.8.4 2004/01/25 11:34:29 rollmark Exp $

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
#include "space.h"
#include "body.h"
#include "collisionhandler.h"
#include <oxygen/sceneserver/scene.h>
#include <zeitgeist/logserver/logserver.h>

using namespace boost;
using namespace oxygen;
using namespace std;

Collider::Collider() : ODEObject(), mODEGeom(0)
{
}

Collider::~Collider()
{
  if (mODEGeom)
    {
      dGeomDestroy(mODEGeom);
      mODEGeom = 0;
    }
}

void Collider::OnLink()
{
  ODEObject::OnLink();

  if (mODEGeom == 0)
    {
      return;
    }

  // if there is a Body below our parent, link to it
  shared_ptr<Body> body = shared_static_cast<Body>
    (make_shared(GetParent())->GetChildOfClass("Body"));

  if (body.get() != 0)
    {
      dGeomSetBody (mODEGeom, body->GetODEBody());
    }

  // if we have a space add the geom to it
  shared_ptr<Scene> scene = GetScene();
  if (scene.get() == 0)
    {
      return;
    }

  mSpace = shared_static_cast<Space>(scene->GetChildOfClass("Space"));
  if (mSpace.get() == 0)
    {
      return;
    }

  dSpaceID space = mSpace->GetODESpace();

  if (
      (space) &&
      (! dSpaceQuery(space, mODEGeom))
      )
    {
      dGeomSetData(mODEGeom, this);
      dSpaceAdd(space, mODEGeom);
    }
}

void Collider::OnUnlink()
{
  ODEObject::OnUnlink();

  if (
      (mSpace.get() == 0) ||
      (mODEGeom == 0)
      )
    {
      return;
    }

  // remove collision geometry from space
  dSpaceID space = mSpace->GetODESpace();

  if (
      (space) &&
      (dSpaceQuery(space, mODEGeom))
      )
    {
      dSpaceRemove(space, mODEGeom);
    }

  mSpace.reset();
}

dGeomID Collider::GetODEGeom()
{
  return mODEGeom;
}

bool Collider::AddCollisionHandler(const std::string& handlerName)
{
  GetCore()->New(handlerName);

  shared_ptr<CollisionHandler> handler =
    shared_dynamic_cast<CollisionHandler>(GetCore()->New(handlerName));

  if (handler.get() == 0)
    {
      GetLog()->Error()
        << "ERROR: (Collider) Cannot create CollisionHandler "
        << handlerName << "\n";
      return false;
    }

  return AddChildReference(handler);
}

void Collider::OnCollision(dGeomID collidee, dContact& contact)
{
  // get the collider corresponding to the collidee's dGeomID and
  // retrieve a shared pointer to it
  Collider* colPtr = Collider::GetCollider(collidee);
  if (colPtr == 0)
    {
      GetLog()->Error()
        << "ERROR: (Collider) no Collider found for dGeomID "
        << collidee << "\n";
      return;
    }

  shared_ptr<Collider> colShared = shared_static_cast<Collider>
    (make_shared(colPtr->GetSelf()));

  if (colShared.get() == 0)
    {
      return;
    }

  TLeafList colHandler;
  GetChildrenSupportingClass("CollisionHandler",colHandler);

  if (colHandler.size() == 0)
    {
      // for convenience we add a ContactJointHandler if no other
      // handler is registered. This behaviour covers the majority of
      // all use cases and eases the creation of Colliders.

      AddCollisionHandler("kerosin/ContactJointHandler");
      GetChildrenSupportingClass("CollisionHandler",colHandler);
    }

  for (
       TLeafList::iterator iter = colHandler.begin();
       iter != colHandler.end();
       ++iter
       )
    {
      shared_ptr<CollisionHandler> handler =
        shared_static_cast<CollisionHandler>(*iter);

      handler->HandleCollision(colShared, contact);
    }
}

Collider* Collider::GetCollider(dGeomID id)
{
  return id ?
    static_cast<Collider*>(dGeomGetData(id)) : 0;
}

void Collider::SetPosition(salt::Vector3f pos)
{
  dGeomSetPosition (mODEGeom, pos[0], pos[1], pos[2]);
}

/* -*- mode: c++; c-basic-indent: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: controlaspect.cpp,v 1.5 2007/06/16 15:06:04 jboedeck Exp $

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

#include "controlaspect.h"
#include <zeitgeist/logserver/logserver.h>
#include <oxygen/sceneserver/sceneserver.h>

using namespace std;
using namespace boost;
using namespace oxygen;
using namespace zeitgeist;

shared_ptr<Scene>
ControlAspect::GetActiveScene()
{
    static shared_ptr<SceneServer> sceneServer;

    if (sceneServer.get() == 0)
    {
        sceneServer = shared_dynamic_cast<SceneServer>(GetCore()->Get("/sys/server/scene"));

        if (sceneServer.get() == 0)
        {
            GetLog()->Error() << "(ControlAspect) cannot get SceneServer\n";
            return shared_ptr<Scene>();
        }
    }

    static shared_ptr<Scene> activeScene;

    if (activeScene.get() == 0)
    {
        activeScene = sceneServer->GetActiveScene();

        if (activeScene.get() == 0)
        {
            GetLog()->Error() << "(ControlAspect) SceneServer reported no active scene\n";
            return shared_ptr<Scene>();
        }
    }

    return activeScene;
}

shared_ptr<ControlAspect>
ControlAspect::GetControlAspect(const string& name)
{
    static const string gcsPath = "/sys/server/gamecontrol/";

    shared_ptr<ControlAspect> aspect = shared_dynamic_cast<ControlAspect>
            (GetCore()->Get(gcsPath + name));

    if (aspect.get() == 0)
    {
        GetLog()->Error() << "(ControlAspect) found no " << name << "\n";
    }
    
    return aspect;
}



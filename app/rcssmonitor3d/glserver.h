/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: glserver.h,v 1.3.2.5 2004/01/31 17:29:36 rollmark Exp $

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
#ifndef _GLSERVER_H
#define _GLSERVER_H

#include <GL/glut.h>
#include "camera.h"

class GLserver
{
 public:
  GLserver(){};
  GLserver(int width, int height,
           salt::Vector3f camPos,
           salt::Vector3f lookAtPos,
           salt::Vector3f up, bool wire);
  ~GLserver() {};

  void InitGL();
  void DrawGround(salt::Vector3f gridPos, float szX, float szZ);
  void ApplyCamera();
  void DrawText(const char* text, salt::Vector2f pos);
  void DrawGoal(salt::Vector3f goalPos, salt::Vector3f sz);
  void DrawSphere(salt::Vector3f spherePos, float radius);
  void DrawShadowOfSphere(salt::Vector3f spherePos,float radius);
  void DrawWireBox(salt::Vector3f boxPos, salt::Vector3f sz);
  void Reshape(int width, int height)
    {
        mWidth = width;
        mHeight = height;
    }

  //inline functions
  inline void SetViewByMouse(const Vector2f& mousePos, const Vector2f& refPos)
    {
        mCamera.SetViewByMouse(mousePos, refPos);
    }
  inline salt::Vector3f GetCameraPos()
    {
        return mCamPos;
    }
  inline void SetCameraPos(const salt::Vector3f& newPos)
    {
        mCamPos = newPos;
        mCamera.SetCameraPos(newPos);
    }
  inline void SetLookAtPos(const salt::Vector3f& newPos)
    {
        mLookAt = newPos;
        mCamera.SetLookAtPos(newPos);
    }
  inline void MoveCamForward(float steps)
    {
        mCamera.MoveCamForward(steps);
        mCamPos = mCamera.GetLookAtPos();
        mLookAt = mCamera.GetCameraPos();
    }
  inline void MoveCamStrafe(float steps)
    {
        mCamera.MoveCamStrafe(steps);
        mCamPos = mCamera.GetLookAtPos();
        mLookAt = mCamera.GetCameraPos();
    }

  inline void MoveCamUp(float steps)
    {
        mCamera.MoveCamUp(steps);
        mCamPos = mCamera.GetLookAtPos();
        mLookAt = mCamera.GetCameraPos();
    }

protected:
  salt::Vector3f mCamPos;
  salt::Vector3f mLookAt;
  salt::Vector3f mUp;
  Camera mCamera;
  bool mWireframe;
  int mWidth;
  int mHeight;
};

#endif // _GLSERVER_H



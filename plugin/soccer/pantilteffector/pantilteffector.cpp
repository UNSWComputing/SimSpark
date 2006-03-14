/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Mon May 9 2005
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: pantilteffector.cpp,v 1.1 2006/03/10 13:46:47 fruit Exp $

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
#include "pantiltaction.h"
#include "pantilteffector.h"
#include <salt/gmath.h>
#include <zeitgeist/logserver/logserver.h>
#include <soccer/soccerbase/soccerbase.h>
#include <soccer/restrictedvisionperceptor/restrictedvisionperceptor.h>

using namespace boost;
using namespace oxygen;
using namespace salt;

PanTiltEffector::PanTiltEffector() : oxygen::Effector(),
                                     mMaxPanAngleDelta(90),
                                     mMaxTiltAngleDelta(10)
{
    SetSigma(0.25);
}

PanTiltEffector::~PanTiltEffector()
{
}

bool
PanTiltEffector::Realize(boost::shared_ptr<ActionObject> action)
{
    if (mBody.get() == 0)
    {
        return false;
    }

    shared_ptr<BaseNode> parent =
        shared_dynamic_cast<BaseNode>(make_shared(GetParent()));

    if (parent.get() == 0)
    {
        GetLog()->Error() << "ERROR: (PanTiltEffector) "
                          << "parent node is not derived from BaseNode\n";
        return false;
    }

    shared_ptr<PanTiltAction> panTiltAction =
        shared_dynamic_cast<PanTiltAction>(action);

    if (panTiltAction.get() == 0)
    {
        GetLog()->Error() << "ERROR: (PanTiltEffector) "
                          << "cannot realize an unknown ActionObject\n";
        return false;
    }

    float pan = panTiltAction->GetPanAngle();
    // cut down the pan angle if necessary
    if (gAbs(pan) > mMaxPanAngleDelta)
    {
        pan = gSign(pan) * mMaxPanAngleDelta;
    }

    float tilt = panTiltAction->GetTiltAngle();
    // cut down the tilt angle if necessary
    if (gAbs(tilt) > mMaxTiltAngleDelta)
    {
        tilt = gSign(tilt) * mMaxTiltAngleDelta;
    }

    // apply random error if there is a RNG
    if (mActuatorErrorRNG.get() != 0)
    {
        pan += (*(mActuatorErrorRNG.get()))();
        tilt += (*(mActuatorErrorRNG.get()))();
    }

    // look for vision perceptor and apply change
    shared_ptr<RestrictedVisionPerceptor> rvp =
        parent->FindChildSupportingClass<RestrictedVisionPerceptor>(false);
    if (rvp.get() == 0)
    {
        GetLog()->Error() << "ERROR: (PanTiltEffector) "
                          << "cannot find RestrictedVisionPerceptor instance\n";
        return false;
    }

    rvp->ChangePanTilt(pan,tilt);
    return true;
}

shared_ptr<ActionObject>
PanTiltEffector::GetActionObject(const Predicate& predicate)
{
    if (predicate.name != GetPredicate())
    {
        GetLog()->Error() << "ERROR: (PanTiltEffector) invalid predicate"
                          << predicate.name << "\n";
        return shared_ptr<ActionObject>();
    }

    Predicate::Iterator iter = predicate.begin();

    float pan;
    if (! predicate.AdvanceValue(iter, pan))
    {
        GetLog()->Error() << "ERROR: (PanTiltEffector) 2 float parameters expected\n";
        return shared_ptr<ActionObject>(new ActionObject(GetPredicate()));
    }
    float tilt;
    if (! predicate.AdvanceValue(iter, tilt))
    {
        GetLog()->Error() << "ERROR: (PanTiltEffector) float parameter expected\n";
        return shared_ptr<ActionObject>(new ActionObject(GetPredicate()));
    }
    return shared_ptr<ActionObject>(new PanTiltAction(GetPredicate(),pan,tilt));
}

void
PanTiltEffector::OnLink()
{
    SoccerBase::GetTransformParent(*this,mTransformParent);
    SoccerBase::GetBody(*this,mBody);
    SoccerBase::GetAgentState(*this,mAgentState);
}

void
PanTiltEffector::OnUnlink()
{
    mActuatorErrorRNG.reset();
    mTransformParent.reset();
    mBody.reset();
}

void
PanTiltEffector::SetMaxPanAngleDelta(unsigned char max_pan_angle)
{
    mMaxPanAngleDelta = max_pan_angle;
}

void
PanTiltEffector::SetMaxTiltAngleDelta(unsigned char max_tilt_angle)
{
    mMaxTiltAngleDelta = max_tilt_angle;
}

void
PanTiltEffector::SetSigma(float sigma)
{
    NormalRngPtr rng(new salt::NormalRNG<>(0.0,sigma));
    mActuatorErrorRNG = rng;
}


/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: export.cpp,v 1.1 2004/05/07 12:18:34 rollmark Exp $

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
#include <zeitgeist/zeitgeist.h>
#include "hinge2perceptor.h"
#include "hinge2effector.h"
#include "timeperceptor.h"

ZEITGEIST_EXPORT_BEGIN()
    ZEITGEIST_EXPORT(Hinge2Effector);
    ZEITGEIST_EXPORT(Hinge2Perceptor);
    ZEITGEIST_EXPORT(TimePerceptor);
ZEITGEIST_EXPORT_END()
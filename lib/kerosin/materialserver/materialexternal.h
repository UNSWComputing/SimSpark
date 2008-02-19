/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of simspark
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: materialexternal.h,v 1.1 2008/02/19 22:49:23 hedayat Exp $

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
#ifndef KEROSIN_MATERIALEXTERNAL_H
#define KEROSIN_MATERIALEXTERNAL_H

#include "materialsolid.h"

namespace kerosin
{
class MaterialExternal : public MaterialSolid
{
    // Functions
public:
    MaterialExternal();
    virtual ~MaterialExternal();

    virtual void Bind();

    //! @return the name of the reference
    const std::string& GetReference() const;

    //! Set the name of the reference
    void SetReference(const std::string& name);

protected:
    /** sets up all lighting material properties */
    void SetupMaterial();

    // Members
protected:
    /** the external file reference */
    std::string mName;
};

DECLARE_CLASS(MaterialExternal);
};

#endif // KEROSIN_MATERIALEXTERNAL_H

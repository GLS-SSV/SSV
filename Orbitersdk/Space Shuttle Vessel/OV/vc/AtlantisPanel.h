/****************************************************************************
  This file is part of Space Shuttle Vessel

  Basic panel definitions


  Space Shuttle Vessel is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Vessel is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Vessel; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file SSV-LICENSE.txt for more details.

  **************************************************************************/
/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/01/20   GLS
2021/08/24   GLS
2021/12/26   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Basic panel definitions



  Space Shuttle Ultra is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Ultra is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Ultra; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file Doc\Space Shuttle Ultra\GPL.txt for more details.

  **************************************************************************/
#ifndef _ATLANTIS_PANEL_H_
#define _ATLANTIS_PANEL_H_

#include <OrbiterAPI.h>
#include <string>
#include <BasicPanel.h>
#include "../Atlantis.h"


namespace vc
{

using namespace std;


class AtlantisPanel : public BasicPanel<Atlantis>
{
public:
	AtlantisPanel(Atlantis* _sts, const std::string& _name) : BasicPanel(_sts, _name) {};
	virtual ~AtlantisPanel() {};
	Atlantis* STS() const { return V(); };

	void AddMeshes( const VECTOR3 &ofs ) override
	{
		if (mesh_idx == (UINT)-1)
		{
			VECTOR3 _ofs = ofs + panelofs;
			mesh_idx = STS()->AddMesh( hMesh, &_ofs );
			STS()->SetMeshVisibilityMode( mesh_idx, MESHVIS_VC );
		}
		return;
	}

	void SetMeshVisibility( bool visible )override
	{
		if (mesh_idx != (UINT)-1)
		{
			if (visible) STS()->SetMeshVisibilityMode( mesh_idx, MESHVIS_VC );
			else STS()->SetMeshVisibilityMode( mesh_idx, MESHVIS_NEVER );
		}
		return;
	}

protected:
	void DefineMesh( const char* meshname ) override
	{
		const VECTOR3 panelofs = _V( 0.0, 0.0, 0.0 );
		DefineMesh( meshname, panelofs );
		return;
	}

	void DefineMesh( const char* meshname, const VECTOR3& panelofs ) override
	{
		hMesh = oapiLoadMeshGlobal( meshname );
		mesh_idx = (UINT)-1;
		this->panelofs = panelofs;
		bHasOwnVCMesh = true;
		return;
	}
};

}

#endif// _ATLANTIS_PANEL_H_

/****************************************************************************
  This file is part of Space Shuttle Vessel

  Payload MPM subsystem definition


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
2020/05/06   GLS
2020/05/10   GLS
2020/05/14   GLS
2020/06/20   GLS
2020/10/10   GLS
2021/01/20   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Starboard MPM system



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
#ifndef __PLMPM_H
#define __PLMPM_H


#include "MPM.h"
#include <vector>
#include "Mission\Mission.h"


class Payload_MPM : public MPM
{
public:
	Payload_MPM( AtlantisSubsystemDirector* _director, const mission::PayloadMPM& plmpm, bool portside );
	virtual ~Payload_MPM();

	void Realize() override;
	void OnPreStep(double simt, double simdt, double mjd) override;
	void OnPostStep(double simt, double simdt, double mjd) override;
	void OnSaveState(FILEHANDLE scn) const override;

	void VisualCreated( VISHANDLE vis ) override;

	void CreateAttachment( void ) override;

	void UpdateAttachment( void );
protected:
	void OnMRLLatched() override;
	void OnMRLReleased() override;
private:
	void AttachPL();
	void FindPLAttachments();
	bool CheckRTL() const;
	/**
	 * Returns index (in vpPL and vhPLAttach vectors) of first PL found that can be attached to the MPM.
	 * Returns -1 if no attachment is within range.
	 */
	int FindPL() const;

	void AddMesh( void );
	void DefineAnimations( void );

	mission::PayloadMPM plmpm;

	MESHHANDLE hMesh_Pedestal_Shoulder;
	MESHHANDLE hMesh_Pedestal_Forward;
	MESHHANDLE hMesh_Pedestal_Mid;
	MESHHANDLE hMesh_Pedestal_Aft;
	UINT mesh_index_pedestal_shoulder;
	UINT mesh_index_pedestal_forward;
	UINT mesh_index_pedestal_mid;
	UINT mesh_index_pedestal_aft;

	//NOTE: any item in vhPL MUST have a corresponding entry in vhPLAttach at the same index
	vector<OBJHANDLE> vhPL; // PL vessels in scenario
	vector<ATTACHMENTHANDLE> vhPLAttach; //attchment point on PL(s) that attaches to MPM

	VECTOR3 attach_point[2];
};

#endif// __PLMPM_H

/****************************************************************************
  This file is part of Space Shuttle Vessel

  Airborne Support Structure for the Inertial Upper Stage subsystem definition


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
2020/03/29   GLS
2020/04/01   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/06/01   GLS
2020/06/20   GLS
2020/06/23   GLS
2020/06/28   GLS
2020/08/21   GLS
2020/08/25   GLS
2020/09/12   GLS
2020/10/07   GLS
2021/06/15   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/01/10   GLS
2022/02/16   GLS
2022/04/29   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Airborne Support Structure for the Inertial Upper Stage definition



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
#ifndef __ASE_IUS_H
#define __ASE_IUS_H


#include <discsignals.h>
#include "AtlantisSubsystem.h"
#include "mission/Mission.h"
#include <Orbitersdk.h>


using namespace discsignals;


class ASE_IUS:public AtlantisSubsystem
{
	private:
		bool AftLocation;

		bool PyroBusPri;
		bool PyroBusAlt;
		bool UmbilicalsEnaPri;
		bool UmbilicalsEnaAlt;
		bool IUSDeploymentEnaPri;
		bool IUSDeploymentEnaAlt;
		bool TiltTableActuatorMotionPri1Lower;
		bool TiltTableActuatorMotionPri1Raise;
		bool TiltTableActuatorMotionAlt2Lower;
		bool TiltTableActuatorMotionAlt2Raise;

		UINT mesh_index;
		MESHHANDLE hMesh;
		MESHHANDLE hMesh_Latches[2];// [port, starboard]
		UINT mesh_idx_Latches[2];

		VECTOR3 ASEoffset;
		VECTOR3 IUSattachoffset;

		UINT animTiltTable;
		UINT animUmbilical;
		double posTiltTable;
		double posUmbilical;

		UINT animPRLAHook[2];

		double oldposition;

		ATTACHMENTHANDLE hIUSattach;

		bool umbilicalreleased;

		DiscInPort pTiltTableActuatorDriveEnablePri1Intermediate;
		DiscInPort pTiltTableActuatorDriveEnablePri1Maximum;
		DiscInPort pTiltTableActuatorDriveEnableAlt2Intermediate;
		DiscInPort pTiltTableActuatorDriveEnableAlt2Maximum;

		DiscInPort pTiltTableActuatorMotionPri1Lower;
		DiscInPort pTiltTableActuatorMotionPri1Raise;
		DiscInPort pTiltTableActuatorMotionAlt2Lower;
		DiscInPort pTiltTableActuatorMotionAlt2Raise;

		DiscInPort pPyroBusPriOff;
		DiscInPort pPyroBusPriOn;
		DiscInPort pPyroBusAltOff;
		DiscInPort pPyroBusAltOn;

		DiscInPort pUmbilicalsEnaPriOff;
		DiscInPort pUmbilicalsEnaPriEnable;
		DiscInPort pUmbilicalsEnaAltOff;
		DiscInPort pUmbilicalsEnaAltEnable;
		DiscInPort pUmbilicalsRelPriRelease;
		DiscInPort pUmbilicalsRelAltRelease;

		DiscInPort pIUSDeploymentEnaPriOff;
		DiscInPort pIUSDeploymentEnaPriEnable;
		DiscInPort pIUSDeploymentEnaAltOff;
		DiscInPort pIUSDeploymentEnaAltEnable;

		DiscInPort pIUSDeploymentDpyPriDeploy;
		DiscInPort pIUSDeploymentDpyAltDeploy;

		DiscOutPort pPyroBusPriTB;
		DiscOutPort pPyroBusAltTB;

		DiscOutPort pUmbilicalsEnaPriTB;
		DiscOutPort pUmbilicalsEnaAltTB;
		DiscOutPort pUmbilicalsRelPriTB;
		DiscOutPort pUmbilicalsRelAltTB;

		DiscOutPort pIUSDeploymentEnaPriTB;
		DiscOutPort pIUSDeploymentEnaAltTB;

		DiscOutPort pTiltTableActuatorMotionPri1TB;
		DiscOutPort pTiltTableActuatorMotionAlt2TB;

		DiscOutPort pTiltTableActuatorPositionPri1TB;
		DiscOutPort pTiltTableActuatorPositionAlt2TB;

		struct mission::Latches latches[2];
		double LatchState[2];// 0 = closed; 1 = open
		DiscOutPort LAT_A[2];
		DiscOutPort LAT_B[2];
		DiscOutPort REL_A[2];
		DiscOutPort REL_B[2];
		DiscInPort MOTOR_1_PWR[2];
		DiscInPort MOTOR_2_PWR[2];
		DiscInPort IND_A[2];
		DiscInPort IND_B[2];
		DiscOutPort RDY_A[2];
		DiscOutPort RDY_B[2];

		bool IsIUSAttached( void ) const;
		void CalcUmbilicalAnimation( void );
		void RunAnimation( void );
		void AddMesh( void );
		void DefineAnimations( void );
		void DefineLatchAnimations( void );

	public:
		explicit ASE_IUS( AtlantisSubsystemDirector* _director, bool AftLocation, const struct mission::Latches* latches );
		virtual ~ASE_IUS();

		void Realize( void ) override;
		void OnPreStep( double simt, double simdt, double mjd ) override;
		bool OnParseLine( const char* line ) override;
		void OnSaveState( FILEHANDLE scn ) const override;
		bool SingleParamParseLine() const override {return true;};
		double GetSubsystemMass( void ) const override;

		void CreateAttachment( void );
		void UpdateAttachment( void );

		void GetPLBInfo( unsigned short& PLID_longeron1, unsigned short& PLID_longeron2, unsigned short& PLID_longeron3, unsigned short& PLID_keel, bool& aftlocation, bool& Reversed_longeron1, bool& Reversed_longeron2, bool& Reversed_longeron3 ) const;
};

#endif //__IUS_ASE_H

/****************************************************************************
  This file is part of Space Shuttle Vessel

  Centaur Integrated Support Structure subsystem definition


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
2020/07/25   GLS
2020/08/19   GLS
2020/08/20   GLS
2020/08/21   GLS
2020/08/25   GLS
2020/08/27   GLS
2020/09/12   GLS
2020/10/07   GLS
2021/06/16   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/01/10   GLS
2022/02/16   GLS
2022/04/29   GLS
2022/08/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Centaur Integrated Support Structure definition



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
#ifndef __CISS_H
#define __CISS_H


#include <discsignals.h>
#include "AtlantisSubsystem.h"
#include "Mission\\Mission.h"
#include <Orbitersdk.h>


using namespace discsignals;


class CISS:public AtlantisSubsystem
{
		bool isGPrime;

		MESHHANDLE hMesh;
		UINT mesh_idx;
		MESHHANDLE hMesh_Specific;
		UINT mesh_idx_specific;
		MESHHANDLE hMesh_MK;
		UINT mesh_idx_MK;
		MESHHANDLE hMesh_Latches[3];// [port, starboard, keel]
		UINT mesh_idx_Latches[3];

		GROUPREQUESTSPEC grs[12];
		double posDAold;

		UINT anim_rotate;
		UINT anim_motorcrank;
		UINT anim_link;
		UINT anim_lox_a;
		UINT anim_lox_b;
		UINT anim_gox_a;
		UINT anim_gox_b;
		UINT anim_lh2_a;
		UINT anim_lh2_b;
		UINT anim_gh2_a;
		UINT anim_gh2_b;
		double posDA;
		double posmotorcrank;
		double poslink;
		double poslox_a;
		double poslox_b;
		double posgox_a;
		double posgox_b;
		double poslh2_a;
		double poslh2_b;
		double posgh2_a;
		double posgh2_b;

		UINT animLatches[3];

		double x2;
		double y2;
		double r1;
		double r3;
		double r4;
		double x7;
		double y7;
		double r2_5;
		double r5;
		double r6;
		double x10;
		double y10;
		double r2_8;
		double r8;
		double r9;
		double x13;
		double y13;
		double r2_11;
		double r11;
		double r12;
		double x16;
		double y16;
		double r2_14;
		double r14;
		double r15;
		double theta1o;
		double theta3o;
		double theta4o;
		double theta2_5o;
		double theta5o;
		double theta6o;
		double theta2_8o;
		double theta8o;
		double theta9o;
		double theta2_11o;
		double theta11o;
		double theta12o;
		double theta2_14o;
		double theta14o;
		double theta15o;

		ATTACHMENTHANDLE ahToCentaur;

		bool bMECH_PRI_PWR;
		bool bMECH_BKUP_PWR;
		bool bDA_PRI_UP;
		bool bDA_PRI_DN;
		bool bDA_BKUP_UP;
		bool bDA_BKUP_DN;
		bool bSUPER_ZIP_FIRE;

		DiscInPort pSUPER_ZIP_PRI_FIRE;
		DiscInPort pSUPER_ZIP_PRI_ARM_ARM;
		DiscInPort pDA_PRI_ROT_DN;
		DiscInPort pDA_PRI_ROT_UP;
		DiscInPort pLOGIC_PRI_PWR_ON;
		DiscInPort pSSP_PRI_PWR_ON;
		DiscInPort pMECH_PRI_PWR_OFF;
		DiscInPort pMECH_PRI_PWR_ON;
		DiscOutPort pSUPER_ZIP_PRI_ARM_TB;
		DiscOutPort pPosition_PRI_TB;
		DiscOutPort pMECH_PRI_PWR_TB;

		DiscInPort pSUPER_ZIP_BKUP_FIRE;
		DiscInPort pSUPER_ZIP_BKUP_ARM_ARM;
		DiscInPort pDA_BKUP_ROT_DN;
		DiscInPort pDA_BKUP_ROT_UP;
		DiscInPort pLOGIC_BKUP_PWR_ON;
		DiscInPort pSSP_BKUP_PWR_ON;
		DiscInPort pMECH_BKUP_PWR_OFF;
		DiscInPort pMECH_BKUP_PWR_ON;
		DiscOutPort pSUPER_ZIP_BKUP_ARM_TB;
		DiscOutPort pPosition_BKUP_TB;
		DiscOutPort pMECH_BKUP_PWR_TB;

		struct mission::Latches latches[3];
		double LatchState[3];// 0 = closed; 1 = open
		DiscOutPort LAT_A[3];
		DiscOutPort LAT_B[3];
		DiscOutPort REL_A[3];
		DiscOutPort REL_B[3];
		DiscInPort MOTOR_1_PWR[3];
		DiscInPort MOTOR_2_PWR[3];
		DiscInPort IND_A[3];
		DiscInPort IND_B[3];
		DiscOutPort RDY_A[3];
		DiscOutPort RDY_B[3];

		bool IsCentaurAttached( void ) const;
		void DefineAnimations( void );
		void DefineLatchAnimations( void );
		void RunAnimation( void );
		void CalcAnimation( void );
		void AddMesh( void );

	public:
		explicit CISS( AtlantisSubsystemDirector* _director, bool isGPrime, const struct mission::Latches* latches );
		~CISS( void );

		void Realize( void ) override;
		void OnPreStep( double simt, double simdt, double mjd ) override;
		bool OnParseLine( const char* line ) override;
		void OnSaveState( FILEHANDLE scn ) const override;
		bool SingleParamParseLine() const override {return true;};
		double GetSubsystemMass( void ) const override;
		void Animate( void ) override;

		void CreateAttachment( void );
		void UpdateAttachment( void );

		void GetPLBInfo( unsigned short& PLID_longeron1, unsigned short& PLID_longeron2, unsigned short& PLID_keel, unsigned short& bay, bool& Reversed_longeron1, bool& Reversed_longeron2 ) const;
};

#endif// __CISS_H

/****************************************************************************
  This file is part of Space Shuttle Vessel

  Entry Guidance Targeting Routine definition


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
2020/04/01   GLS
2020/05/08   GLS
2020/06/20   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Entry Guidance Targeting Routine definition



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
#ifndef __EGRT
#define __EGRT


#include "SimpleGPCSoftware.h"


namespace dps
{
	class EGRT:public SimpleGPCSoftware
	{
		// midpoint targeting logic not used
		private:
			// input
			VECTOR3 XYZED;// shuttle velocity vector (greenwich coord.) [fps]
			VECTOR3 XYZE;// shuttle position vector (greenwich coord.) [ft]
			VECTOR3 RLS/*[2]*/;// runway position vectors (greenwich coord.) [ft]
			MATRIX3 REC/*[2]*/;// greenwich to runway transformation matrices [1]
			unsigned short OVHD/*[2]*/;// runway approach mode flags [1]
			//double SRAZ;// secondary runway azimuth [rad]
			//double AZRW;// bearing from true north of runway +x axis (pri?) [rad]
			unsigned short RWID;// selected runway ID (1-pri; 2-sec) [1]
			unsigned short IFP;// first pass flag [1]
			//double VTOGL;// velocity to toggle OVHD/STRT HAC status [fps]
			double M;// vehicle mass [slugs]
			double PSHARS;
			double RF0;
			double R1;
			double R2;
			double WTGS1;
			double XHACL;
			double XHACH;

			// output
			double DELAZ;// azimuth error [rad]
			double TRANG;// range to target [NM]
			//double YSGNT;// R/L HAC indicator [1]
			//double PSHAT;// HAC turn angle [deg]
			//double RTURNT;// HAC radius [ft]
			double RCHMAG;// radius of landing site [ft]

			// internal
			unsigned short RWID0;// old RWID
			unsigned short IRED;// runway redesignation flag
			//unsigned int IMID;// midpoint targeting [1]
			double RAZ;// selected runway azimuth [rad]
			//double VE;// (old |XYZED|?) [fps]
			double YSGN/*[2]*/;// R/L HAC indicator [1]
			double PSHA/*[2]*/;// HAC turn angle [deg]
			double RTURN/*[2]*/;// HAC radius [ft]
			double SIGNY;// sign of vehicle Y position in runway coordinates [1]
			VECTOR3 RC;// center of heading alignment circle in runway coordinates [ft]
			VECTOR3 HACEF;// offset of center of heading alignment circle to runway, in earth-fixed coordinates [ft]
			double RCCEF[3];// position of HAC in earth-fixed coordinates [ft]
			double VNORM[3];
			double RVEHMG;// radius of vehicle position [ft]
			double BARVEH;// bearing of the vehicle [rad]
			double SINB;
			double BARCC;// heading to center of alignment circle [rad]
			double CTHVC;// cosine (angle between vehicle and HAC)
			double SBARCR;
			double A2;// [rad]
			double DVEWP1;// distance from vehicle to WP1 [ft]
			double BARWP1;// heading to tangent point on HAC [rad]
			double DARC;// distance around heading alignment cone [ft]
			double PSI;// heading of vehicle [rad]

			double step;


			void EXEC( void );// targeting executive logic
			void SEQ( void );// sequence controller
			void CHACRC( void );// center of heading alignment cone - runway coordinates
			void CHACEFC( void );// center of heading alignment cone in earth-fixed coordinates
			void BV( void );// bearing of the vehicle
			void BVCHAC( void );// bearing to center of the alignment cone
			void COSTHETA( void );// great circle arc
			void DWP1( void );// distance to WP1
			void DVNEP( void );// range to threshold point
			void DELAZ_( void );// azimuth error (underscore added to name due to collision with variable)

		public:
			explicit EGRT( SimpleGPCSystem* _gpc );
			virtual ~EGRT( void );

			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;

			void ReadILOADs( const std::map<std::string,std::string>& ILOADs ) override;

			void OnPreStep( double simt, double simdt, double mjd ) override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;
	};

}

#endif// __EGRT

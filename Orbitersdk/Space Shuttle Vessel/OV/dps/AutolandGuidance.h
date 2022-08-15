/****************************************************************************
  This file is part of Space Shuttle Vessel

  Autoland Guidance definition


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
2020/04/07   GLS
2020/05/08   GLS
2020/06/20   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Autoland Guidance definition



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
#ifndef __ALGUID
#define __ALGUID


#include "SimpleGPCSoftware.h"


class FILT1;

/*
PMODE values
1 = Trajectory capture
2 = Steep glide slope
3 = Pull up and shallow glide slope
4 = Final flare
*/

/*
FMODE values (PMODE = 3)
1 = Open loop
2 = Circularization
3 = Exponetial capture
*/

/*
SB_MODE values
1 = TAEM-to-A/L transition to 3kft
2 = from 3kft to 500ft
3 = from 500ft to WOWLON
*/

namespace dps
{
	class AutolandGuidance:public SimpleGPCSoftware
	{
		private:
			// input
			double H;// altitude above runway [ft]
			double H_DOT;// altitude rate [fps]
			unsigned short IGS;// glide slope (1-light ;2-heavy)
			unsigned short IGI;// aimpoint (1-nom; 2-close-in)
			double V_T;// true airspeed [fps]
			double VI;// equivalent? velocity [fps]
			double VG;// ground velocity [fps]
			double X;// position X wrt runway [ft]
			double Y;// position Y wrt runway [ft]
			double Y_DOT;// Y rate of change [fps]
			double GAMMA;// topodetic earth relative flight-path angle [deg]
			unsigned short FLATTURN;
			unsigned short WOWLON;
			unsigned short FCS_PITCH;
			unsigned short FCS_ROLL;
			double R;
			double X_K;
			double H_K;
			double X_EXP;
			double H_DECAY;
			double SIGMA;
			double GAMMA_REF_1;
			double GAMMA_REF_2;
			double X_ZERO;
			double X_AIM;
			double H_FLARE;
			double H_CLOOP;
			double WEIGHT;// [lbs]

			// output
			unsigned short PMODE;// autoland phase counter
			unsigned short FMODE;// FSGS phase counter
			double NZ_CMD;// NZ command
			double PHIC_AL;// roll angle command [deg]
			double RC;// yaw rate command post WOWLON
			double DSBC_AL;// speedbrake command [deg]

			// internal
			unsigned short RESET;
			double H_REF;// reference altitude [ft]
			double H_DOTREF;// reference altitude rate [fps]
			double HERR;// altitude error [ft]
			double HDOTER;// altitude rate error [fps]
			double GAMERR;// gamma error [deg]
			double TGMER;// timer for gamma error [s]
			double GAMMA_C3;
			double TTD1I;
			double NZCP;// last NZC [g]
			unsigned short SB_FIRSTPASS;// speedbrake first pass flag
			unsigned short SB_MODE;// speedbrake control phase
			unsigned short SB_SEL;// speedbrake logic selection (1=NOM, 2=SHORT, 3=ELS)
			double V_REF;
			double TDX_1;// touchdown displacement from wind speed [ft]
			double TDX_2;// touchdown displacement from velocity error [ft]
			double TDX_3;// touchdown displacement from density altitude [ft]
			double TDX_4;// touchdown displacement from vehicle weight [ft]
			double TDX_5;// touchdown displacement from close-in aimpoint [ft]
			double TDX_6;// touchdown displacement from SB option [ft]
			double DSBC_SMART;// smart DSBC command [deg]
			unsigned long SB2_COUNT;// counts number of runs in SB_MODE = 2

			FILT1* fltrNZ_C2I_12;
			FILT1* fltrNZ_C2I_3;
			FILT1* fltrNZ_C1I;
			FILT1* fltrGAMMA_C3;
			FILT1* fltrTTD1I;
			FILT1* fltrA3_ALGNCZ;
			FILT1* fltrA13;
			FILT1* fltrA14;
			FILT1* fltrA40;
			FILT1* fltrA14_WINDSPEED;// using same parameters as fltrA14
			FILT1* intWINDSPEED;

			double step;

			void ALGEXEC( double dt );// autoland guidance
			void ALGINIT( void );// init
			void ALGREF( double dt );// reference parameters
			void ALGNCZ( double dt );// NZ command
			void ALGSBC( double dt );// speedbrake command
			void ALGPHIC( void );// bank angle command

			double CalcDensityAltitude( double sigma ) const;

		public:
			explicit AutolandGuidance( SimpleGPCSystem* _gpc );
			virtual ~AutolandGuidance( void );

			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;

			void ReadILOADs( const std::map<std::string,std::string>& ILOADs ) override;

			void OnPreStep( double simt, double simdt, double mjd ) override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;
	};

};

#endif// __ALGUID

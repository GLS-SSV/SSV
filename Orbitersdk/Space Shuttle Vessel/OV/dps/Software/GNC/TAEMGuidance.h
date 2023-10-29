/****************************************************************************
  This file is part of Space Shuttle Vessel

  Terminal Area Energy Management Guidance definition


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
2022/03/24   GLS
2022/04/01   GLS
2022/09/29   GLS
2022/12/23   GLS
2023/10/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Terminal Area Energy Management Guidance definition



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
#ifndef __TAEMGUID
#define __TAEMGUID


#include "../SimpleGPCSoftware.h"


/*
IPHASE values
0 = S-turn
1 = Acquisition
2 = Heading alignment
3 = Prefinal
4 = Alpha transition (GRTLS)
5 = NZ hold (GRTLS)
6 = Alpha hold (GRTLS)
*/

namespace dps
{
	class TAEMGuidance:public SimpleGPCSoftware
	{
		private:
			// input
			double COSPHI;// cosine of body roll euler angle [1]
			double GAMMA;// topodetic earth relative flight-path angle [deg]
			//unsigned short GI_CHANGE;// flag indicating glideslope desired [1]
			double H;// geodetic altitude of vehicle center of mass above rw [ft]
			double HDOT;// negative z component of velocity in topodetic coordinates [fps]
			double MACH;// mach number [1]
			//double ORAHAC[2];// automatic downmode inhibit flag [1]
			double PSD;// course with respect to centerline [deg]
			double QBAR;// dynamic pressure [psf]
			unsigned short RWID;// selected runway ID flag [1]
			double V;// magnitude of earth relative velocity vector [fps]
			double VH;// topodetic horizontal component of earth relative velocity [fps]
			//double VTOGL;// velocity to toggle OVHD/STRT HAC status [fps]
			double WEIGHT;// orbiter mass [slugs]
			double X;// x-component of position in runway coordinates [ft]
			double XDOT;// x-component of velocity in runway coordinates [fps]
			double Y;// y-component of position in runway coordinates [ft]
			double YDOT;// y-component of velocity in runway coordinates [fps]
			double GAMSGS;
			double PHILMC;

			// output
			double DELRNG;// range error from reference altitude profile
			double DPSAC;// heading error to HAC tangency [deg]
			double DSBC_AT;// speedbrake angle command (hinge line) [deg]
			//double EAS_CMD;// equivalent airspeed command [knots]
			double EOW;// energy per unit weight [ft]
			double NZC;// commanded body normal load factor increment from equilibrium [g]
			//unsigned short OHALRT;// TAEM automatic downmode flag [1]
			double PHIC_AT;// roll angle command
			double QBARF;// filtered dynamic pressure [psf]
			double RCIR;// distance from OV to HAC center [ft]
			double EN;// reference energy [ft]
			double ES;// E/W to start S-turn [ft]
			double EMEP;// E/W to downmode to MEP [ft]
			double EMOH;// E/W to downmode to strait-in [ft]

			// internal
			unsigned short IRESET;// [1]
			//double YHAC;// HAC Y position [ft]
			double XCIR;// x distance from OV to HAC center [ft]
			double YCIR;// y distance from OV to HAC center [ft]
			double DRPRED;// range to XALI [ft]
			double RPRED2;// range from WP1 (or current position in the HAC?) to rw
			double RPRED3;// prefinal initiation range [ft]
			double QBREF;// qbar ref [psf]
			double QBERR;// qbar error [psf]
			double XALI;// A/L interface range
			unsigned short IGS;// glide path angle sel [1]
			unsigned short IEL;// index of energy line [1]
			double DNZUL;// NZ command upper limit [g]
			double DNZLL;// NZ command lower limit [g]
			double PHILIM;// roll command limit [deg]
			double PHIC;// unlimited roll command [deg]
			double PHI0;// previous roll command [deg]
			double DHDRRF;// tan of flight path angle ref [1]
			double QBD;
			double DSBC;// unlimited speedbrake command [deg]
			double DSBI;
			double S;// sign of roll command during S-turn [1]
			double ISR;
			unsigned short RWID0;// previous selected runway ID flag [1]

			double step;

			void TGEXEC( double dt );// TAEM guidance
			void TGINIT( void );// TAEM guidance initiation
			void TGXHAC( void );// XHAC
			void GTP( void );// groundtrack predictor
			void TGCOMP( double dt );// TAEM reference, dynamic pressure and spiral adjust
			void TGTRAN( void );// phase transition, MEP, and OHALRT
			void TGNZC( double dt );// normal acceleration command
			void TGSBC( double dt );// speedbrake command
			void TGPHIC( double dt );// roll command

		public:
			explicit TAEMGuidance( SimpleGPCSystem* _gpc );
			virtual ~TAEMGuidance( void );

			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;

			void ReadILOADs( const std::map<std::string,std::string>& ILOADs ) override;

			void OnPreStep( double simt, double simdt, double mjd ) override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;
	};

}

#endif// __TAEMGUID

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
			unsigned short OVHD;// OVHD/STRT approach mode flag [1]
			double PSD;// course with respect to centerline [deg]
			double PSHA;// HAC turn angle [deg]
			double QBAR;// dynamic pressure [psf]
			double RTURN;// HAC spiral turn radius [ft]
			unsigned short RWID;// selected runway ID flag [1]
			double V;// magnitude of earth relative velocity vector [fps]
			double VH;// topodetic horizontal component of earth relative velocity [fps]
			//double VTOGL;// velocity to toggle OVHD/STRT HAC status [fps]
			double WEIGHT;// orbiter mass [slugs]
			double X;// x-component of position in runway coordinates [ft]
			double XDOT;// x-component of velocity in runway coordinates [fps]
			double Y;// y-component of position in runway coordinates [ft]
			double YDOT;// y-component of velocity in runway coordinates [fps]
			double YSGN;// R/L cone indicator [1]
			double WT_GS1;
			double TGGS;
			double XA;
			double HFTC[2];
			double HALI[2];
			double HMEP[2];
			double GAMSGS;
			double PBHC[2];
			double PBGC[2];
			double PBRC[2];
			double CUBIC_C3[2];
			double CUBIC_C4[2];
			double EOW_SPT[2];
			double EN_C1[2][2];
			double EN_C2[2][2];
			double R2MAX;
			double ESHFMX;
			double ES1[2];
			double EDRS[2];
			double EMEP_C1[2][2];
			double EMEP_C2[2][2];
			double EMOHC1[2];
			double EMOHC2[2];
			double YERRLM;
			double GY;
			double GYDOT;
			double DNZLC1;
			double DNZLC2;
			double DNZUC1;
			double DNZUC2;
			double DR3;
			double DR4;
			double RF0;
			double RFMN;
			double RFMX;
			double R1;
			double R2;
			double PSHARS;
			double PSRF;
			double DHOH1;
			double DHOH2;
			double DHOH3;
			double DRFK;
			double PHAVGC;
			double PHAVGLL;
			double PHAVGS;
			double PHAVGUL;
			double PHILM0;
			double PHILM1;
			double PHILM2;
			double PHILM3;
			double PHILMSUP;
			double PHILS;
			double PHIM;
			double PHILMC;
			double PHILM4;
			double QBARDL;
			double CQG;
			double CQDG;
			double CDEQD;
			double DEL_H1;
			double DEL_H2;
			double Y_RANGE1;
			double Y_RANGE2;
			double GAMMA_COEF1;
			double GAMMA_COEF2;
			double QB_ERROR2;
			double H_REF1;
			double H_REF2;
			double HMIN3;
			double P2TRNC1;
			double ENBIAS;
			double RMINST[2];
			double PSSTRN;
			double PSOHAL;
			double RMOH;

			// output
			double DELRNG;// range error from reference altitude profile
			double DPSAC;// heading error to HAC tangency [deg]
			double DSBC_AT;// speedbrake angle command (hinge line) [deg]
			//double EAS_CMD;// equivalent airspeed command [knots]
			double EOW;// energy per unit weight [ft]
			double HERROR;// altitude error from reference profile [ft]
			unsigned short IPHASE;// TAEM phase counter [1]
			unsigned short MEP;// minimum entry point flag [1]
			double NZC;// commanded body normal load factor increment from equilibrium [g]
			//unsigned short OHALRT;// TAEM automatic downmode flag [1]
			double PHIC_AT;// roll angle command
			double QBARF;// filtered dynamic pressure [psf]
			double RPRED;// predicted range to rw [ft]
			unsigned short TG_END;// TAEM end flag [1]
			double RF;// current HAC final size [ft]
			double XHAC;// HAC X position [ft]
			double RCIR;// distance from OV to HAC center [ft]
			double EN;// reference energy [ft]
			double ES;// E/W to start S-turn [ft]
			double EMEP;// E/W to downmode to MEP [ft]
			double EMOH;// E/W to downmode to strait-in [ft]
			double PSC;// heading to HAC center [deg]

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
			unsigned short IGI;// aimpoint sel [1]
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

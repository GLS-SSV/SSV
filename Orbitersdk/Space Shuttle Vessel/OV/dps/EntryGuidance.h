/****************************************************************************
  This file is part of Space Shuttle Vessel

  Entry Guidance definition


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
2020/05/08   GLS
2020/06/20   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/03/29   GLS
2022/04/02   GLS
2022/04/26   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Entry Guidance definition



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
#ifndef __ENTRYGUID
#define __ENTRYGUID


#include "SimpleGPCSoftware.h"


/*
ISLECT values
1 = Preentry
2 = Temperature control
3 = Equilibrium glide
4 = Constant drag
5 = Transition
*/

namespace dps
{
	class EntryGuidance:public SimpleGPCSoftware
	{
		private:
			// input
			unsigned short START;// initialization flag [1]
			double ALPHA;// angle of attack [deg]
			double ROLL;// current bank angle [deg]
			double TRANGE;// current range to runway [NM]
			double VE;// current relative velocity [fps]
			double VI;// current inertial velocity [fps]
			double XLFAC;// current load factor [fps^2]
			double DRAG;// current drag acceleration [fps^2]
			double DELAZ;// current azimuth error [rad]
			double HLS;// altitude above runway [ft]
			double LOD;// current lift/drag ratio [1]
			double RDOT;// current oblate Earth altitude rate [fps]
			double ASTART;
			double CALP0[10];
			double CALP1[10];
			double CALP2[10];
			double VALP[9];
			unsigned short NALP;
			double VNOALP;
			double VALMOD;
			double VC20;
			double DLAPLM;
			double DDMIN;
			double RDMAX;
			double CRDEAF;
			double DLALLM;
			double ACLAM1;
			double ACLAM2;
			double ACLIM1;
			double ACLIM2;
			double ACLIM3;
			double ACLIM4;
			double Y1;
			double Y2;
			double Y3;
			double CY0;
			double CY1;
			double DLRDLM;
			double VHS1;
			double VHS2;
			double HS01;
			double HS02;
			double HS03;
			double HS11;
			double HS13;
			double HSMIN;

			double ALFM;
			double DELV;
			double VTRAN;
			double VQ;
			double ETRAN;
			double EEF4;
			double DF;
			double RPT1;
			double VSAT;
			double VS1;
			double D230;
			double VB1;
			double VA;
			double VA1;
			double VA2;
			double AK;
			double AK1;
			double LODMIN;
			double DT2MIN;
			double E1;
			double GS1;
			double GS2;
			double GS3;
			double GS4;
			double DRDDL;
			double ALIM;
			double CT16[3];
			double VC16;
			double CT16MN;
			double CT16MX;
			double CT17MN;
			double CT17MX;
			double CT17M2;
			double CT17[2];
			double C17MP;
			double C21;
			double C22;
			double C23;
			double C24;
			double C25;
			double C27;
			double CDDOT1;
			double CDDOT2;
			double CDDOT3;
			double CDDOT4;
			double CDDOT5;
			double CDDOT6;
			double CDDOT7;
			double CDDOT8;
			double CDDOT9;
			double VRDT;
			double DDLIM;
			double ZK1;
			double ALMN1;
			double ALMN2;
			double ALMN3;
			double ALMN4;
			double YLMIN;
			double YLMN2;
			double VYLMAX;
			double VELMN;
			double ACN1;
			double VRLMC;
			double RLMC1;
			double RLMC2;
			double RLMC3;
			double RLMC4;
			double RLMC5;
			double RLMC6;
			double VEROLC;
			double V_TAEM;
			double PREBNK;

			// output
			double ALPCMD;// angle-of-attack command [deg]
			double DREFP;// drag reference [fps^2]
			double VCG;// velocity at start of constant drag phase [fps]
			//double VRR;// velocity at first bank reversal [fps]
			double EOWD;// energy overweight [ft]
			//double RC176G;// first roll command after 0.176g [deg]
			unsigned short EG_END;// Entry guidance end flag

			// internal
			unsigned short ISLECT;// entry guidance subphase counter
			double T1;// equilibrium glide vertical lift acceleration [fps^2]
			double T2;// constant drag level to reach target [fps^2]
			double T2DOT;// rate of change of T2 [fps^2/s]
			double T2OLD;// old value of T2 [fps^2]
			double DREFP3;// DREFP test value for transition to phase 3 [fps^2]
			double DREFP4;// DREFP test value for transition to phase 4 [fps^2]
			double DREFP5;// DREFP test value for transition to phase 5 [fps^2]
			//double CZOLD;// DZOLD????
			bool ITRAN;// transition initilization flag [1]
			unsigned short ICT;// alpha modulation flag [1]
			double C20;// dALPHA / dCd gain
			double ACLAM;// maximum allowable alpha [deg]
			double ACLIM;// minimum allowable alpha [deg]
			double DELALF;// delta alpha from schedule [deg]
			double DELALP;// command alpha increment [deg]
			double DLRDOT;// Rdot feedback term [fps]
			unsigned short LMFLG;// saturated roll command flag [1]
			double VTRB;// Rdot feedback velocity lockout
			double DDP;// past value of DD
			double RPT;// desired range at VQ [NM]
			double VSAT2;// VSAT^2
			double D23;// reference drag level at VB1 [fps^2]
			double DX[2];// normalized values for DREFP
			double VX[2];// velocity where dD/dV=0 in Ith temp control D-V quadratic
			double VF[2];// upper velocity bounds for Ith temperature control range segment
			double V0[2];
			double V[3];// velocity sampling points for temp control numerical range prediction
			double Q[3];// DREFP/VE in temp control phase
			double A[2];
			double VB2;// VB^2
			double RCG1;// constant component of RCG
			unsigned short IALP;// ALPCMD segment counter
			double XLOD;// limited lift/drag ratio [1]
			double VE2;// VE^2
			double EEF;// energy/mass
			double CAG;// pseudoenergy/mass used in transition (L/D) reference
			double HS;// height scale [ft]
			double VQ2;// VQ^2
			double C1;// dD/dE in transition
			double RDTREF;// altitude rate reference [fps]
			double LODX;// unlimited vertical L/D command
			double LODV;// vertical L/D command
			double RF[2];// Ith range segment in temp control phase x D23
			double CQ1[2];// constants in Ith temperature control D-V quadratic
			double CQ2[2];// VE coefficients in Ith temperature control D-V quadratic
			double CQ3[2];// VE^2 coefficients in Ith temperature control D-V quadratic
			double RFF1;// temperature control range x D23
			double VSIT2;// VS1^2
			double A2;// temporary valiable used in computing range and updating D23 [NM]
			double REQ1;// equilibrium glide range x D23 [NM]
			double RCG;// constant drag phase range [NM]
			double R231;// phase 2 and 3 range x D23 [NM]
			double D231;// first updated value of D23 [fps^2]
			double DRDD;// derivative of range wrt drag [NM/fps^2]
			unsigned short N;
			double DREF[2];// DREFP for Ith temperature control D-V quadratic
			double HDTRF[2];// intermediate calculation of temperature control R dot ref (HACK docs have HDTRF[1])
			double DRF;// test values for transition to D23-VB1 quadratic reference parameters
			double C2;// component of L/D reference
			double ALDCO;// temporary variable in phase 3 reference parameters
			double DREFP1;// DREFP in equilibrium glide
			double RDTRF1;// RDTREF in phase 3 [fps]
			double DREFPT;// DREFP-DF in transition phase
			double RER1;// transition phase range
			double DLIM;// maximum value of DREFP in transition
			double ALPDOT;// rate of change of ALPCMD [deg/s]
			double ACMD1;// scheduled angle of attack [deg]
			double C16;// d(L/D)/dD
			double C17;// d(L/D)/dH
			double C4;// reference altitude rate term
			double ALDREF;// vertical L/D reference
			double DD;// drag - DREFP [fps^2]
			double DDS;// limited value of DD [fps^2]
			double ZK;// Rdot gain feedback
			double RK2ROL;// bank direction [1]
			double RK2RLP;// previous bank direction [1]
			double YL;// maximum heading error absolute value [rad]
			double LMN;// maximum value of LODV (bank angle limit?)
			double DZOLD;// previous value of DELAZ
			double DZSGN;// change in DELAZ
			double DLZRL;// test variable in bank angle computation
			unsigned short IDBCHG;// deadband change flag [1]
			//unsigned short IVRR;// first roll reversal flag [1]
			double ARG[3];// 1) cosine of commanded bank angle; 2) cosine of unlimited bank command; 3) cosine of bank reference angle
			double ROLLC[3];// 1) roll angle command about body axis [deg]; 2) unlimited roll command [deg]; 3) roll ref [deg]
			//unsigned short ISLECP;// past value of ISLECT

			double step;

			void EGEXEC( double dt );// entry guidance executive
			void EGSCALHT( void );// entry guidance scale height
			void EGINIT( void );// entry guidance initialization
			void EGCOMN( double dt );// entry guidance common computation
			void EGPEP( void );// entry guidance preentry phase
			void EGRP( void );// entry guidance range prediction
			void EGREF( void );// entry guidance reference parameters
			void EGREF4( void );// entry guidance constant drag phase
			void EGTRAN( void );// entry guidance transition phase
			void EGALPCMD( double dt );// entry guidance angle-of-attack function
			void EGGNSLCT( void );// entry guidance gain selection function
			void EGLODVCMD( void );// entry guidance lateral logic and vertical L/D command function
			void EGROLCMD( void );//entry guidance bank command function

		public:
			explicit EntryGuidance( SimpleGPCSystem* _gpc );
			virtual ~EntryGuidance( void );

			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;

			void ReadILOADs( const std::map<std::string,std::string>& ILOADs ) override;

			void OnPreStep( double simt, double simdt, double mjd ) override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;
	};

}

#endif// __ENTRYGUID

/****************************************************************************
  This file is part of Space Shuttle Vessel

  Main Propulsion System subsystem definition


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
2020/05/10   GLS
2020/06/20   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Main Propulsion System definition



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
#ifndef _mps_MPS_H_
#define _mps_MPS_H_


#include "..\AtlantisSubsystem.h"
#include <Sensor.h>


class PressureActuatedValve;
class SolenoidValve;


namespace mps
{
	class HeSysPneu;

	class MPS:public AtlantisSubsystem
	{
		private:
			HeSysPneu* HeSys;

			double LOXManifPress;
			double LH2ManifPress;

			double LOXinitpress;
			double LH2initpress;

			double LOXrepress;

			double GOXmass;// g
			double GH2mass;// g

			// PV
			PressureActuatedValve* ptrPV1;// ME-1 LOX prevalve
			PressureActuatedValve* ptrPV2;// ME-2 LOX prevalve
			PressureActuatedValve* ptrPV3;// ME-3 LOX prevalve
			PressureActuatedValve* ptrPV4;// ME-1 LH2 prevalve
			PressureActuatedValve* ptrPV5;// ME-2 LH2 prevalve
			PressureActuatedValve* ptrPV6;// ME-3 LH2 prevalve
			PressureActuatedValve* ptrPV7;// LOX Fdln Rlf SOV (NO)
			PressureActuatedValve* ptrPV8;// LH2 Fdln Rlf SOV (NO)
			PressureActuatedValve* ptrPV9;// LOX O/B F/D
			PressureActuatedValve* ptrPV10;// LOX I/B F/D
			PressureActuatedValve* ptrPV11;// LH2 O/B F/D
			PressureActuatedValve* ptrPV12;// LH2 I/B F/D
			PressureActuatedValve* ptrPV13;// LH2 topping
			PressureActuatedValve* ptrPV17;// LH2 B/U Inbd DV
			PressureActuatedValve* ptrPV18;// LH2 B/U Otbd DV
			PressureActuatedValve* ptrPV19;// LOX Ovbd B/V (NO)
			PressureActuatedValve* ptrPV20;// LOX POGO Recrc 1 (NO)
			PressureActuatedValve* ptrPV21;// LOX POGO Recrc 2 (NO)
			//ValveTypeBool* ptrPV22;// LH2 Hi Pt Bl (NC)

			// LV
			/*LV1;// E1 He Iso Vlv A OP Pwr
			LV2;// E1 He Iso Vlv B OP Pwr
			LV3;// E2 He Iso Vlv A OP Pwr
			LV4;// E2 He Iso Vlv B OP Pwr
			LV5;// E3 He Iso Vlv A OP Pwr
			LV6;// E3 He Iso Vlv B OP Pwr
			LV7;// Pneu He Iso Vlv 1 OP Pwr
			LV8;// Pneu He Iso Vlv 2 OP Pwr
			LV10;// Reg He Xover Vlv OP Pw*/
			SolenoidValve* ptrLV12;// E1 LO2 Prevlv OP Pwr 1
			SolenoidValve* ptrLV13;// E1 LO2 Prevlv CL Pwr 1
			SolenoidValve* ptrLV14;// E2 LO2 Prevlv OP Pwr 1
			SolenoidValve* ptrLV15;// E2 LO2 Prevlv CL Pwr 1
			SolenoidValve* ptrLV16;// E3 LO2 Prevlv OP Pwr 1
			SolenoidValve* ptrLV17;// E3 LO2 Prevlv CL Pwr 1
			SolenoidValve* ptrLV18;// E1 LH2 Prevlv OP Pwr
			SolenoidValve* ptrLV19;// E1 LH2 Prevlv CL Pwr
			SolenoidValve* ptrLV20;// E2 LH2 Prevlv OP Pwr
			SolenoidValve* ptrLV21;// E2 LH2 Prevlv CL Pwr
			SolenoidValve* ptrLV22;// E3 LH2 Prevlv OP Pwr
			SolenoidValve* ptrLV23;// E3 LH2 Prevlv CL Pwr
			SolenoidValve* ptrLV24;
			SolenoidValve* ptrLV25;
			/*LV26;// He Sply Blwdwn 1 OP Pwr
			LV27;// He Sply Blwdwn 2 OP Pwr*/
			SolenoidValve* ptrLV28;
			SolenoidValve* ptrLV29;
			SolenoidValve* ptrLV30;// LO2 Inbd F/D Vlv OP Pwr
			SolenoidValve* ptrLV31;// LO2 Inbd F/D Vlv CL Pwr
			SolenoidValve* ptrLV32;
			SolenoidValve* ptrLV33;
			SolenoidValve* ptrLV34;// LH2 Inbd F/D Vlv OP Pwr
			SolenoidValve* ptrLV35;// LH2 Inbd F/D Vlv CL Pwr
			SolenoidValve* ptrLV39;// MPS LH2 Topping Vlv OP pwr
			SolenoidValve* ptrLV40;// LO2 Manf Reprss 1 OP Pwr
			SolenoidValve* ptrLV41;// LO2 Manf Reprss 2 OP Pwr
			SolenoidValve* ptrLV42;// LH2 Manf Reprss 1 OP Pwr
			SolenoidValve* ptrLV43;// LH2 Manf Reprss 2 OP Pwr
			SolenoidValve* ptrLV46;// LO2 17in Disc Vlv OP Pwr
			SolenoidValve* ptrLV47;// LO2 17in Disc Vlv CL Pwr
			SolenoidValve* ptrLV48;// LH2 17in Disc Vlv OP Pwr
			SolenoidValve* ptrLV49;// LH2 17in Disc Vlv CL Pwr
			SolenoidValve* ptrLV50;// LH2 4in Disc Vlv Op Pwr
			SolenoidValve* ptrLV51;// LH2 4in Disc Vlv Cl Pwr
			// LV52;// GH2 Pressurization Line Vent Valve
			SolenoidValve* ptrLV53;// GO2 Flow Control Valve 1
			SolenoidValve* ptrLV54;// GO2 Flow Control Valve 2
			SolenoidValve* ptrLV55;// GO2 Flow Control Valve 3
			SolenoidValve* ptrLV56;// GH2 Press FCV 1 CL Pwr
			SolenoidValve* ptrLV57;// GH2 Press FCV 2 CL Pwr
			SolenoidValve* ptrLV58;// GH2 Press FCV 3 CL Pwr
			/*LV59;// E1 He Intcn In OP Pwr
			LV60;// E1 He Intcn Out OP Pwr
			LV61;// E2 He Intcn In OP Pwr
			LV62;// E2 He Intcn Out OP Pwr
			LV63;// E3 He Intcn In OP Pwr
			LV64;// E3 He Intcn Out OP Pwr
			LV65;// LO2 17in Disc Lock Pwr
			LV66;// LO2 17in Disc Unlock Pwr
			LV67;// LH2 17in Disc Lock Pwr
			LV68;// LH2 17in Disc Unlock Pwr*/
			SolenoidValve* ptrLV72;// LH2 B/U Inbd DV OP Pwr
			SolenoidValve* ptrLV73;// LH2 B/U Otbd DV OP Pwr
			/*LV74;// LH2 RTLS Reprss 1 OP Pwr
			LV75;// LH2 RTLS Reprss 2 OP Pwr*/
			SolenoidValve* ptrLV76;// LOX Ovbd B/V CL
			SolenoidValve* ptrLV77;// LO2 Pogo Recrc 1 Cl Pwr
			SolenoidValve* ptrLV78;// LO2 Pogo RECRC 2 Cl PWR
			//LV79;// LH2 Hi Pt Bl OP
			SolenoidValve* ptrLV80;// E1 LO2 Prevlv CL Pwr 2
			SolenoidValve* ptrLV81;// E2 LO2 Prevlv CL Pwr 2
			SolenoidValve* ptrLV82;// E3 LO2 Prevlv CL Pwr 2
			SolenoidValve* ptrLV83;// E1 LO2 Prevlv OP Pwr 2
			SolenoidValve* ptrLV84;// E2 LO2 Prevlv OP Pwr 2
			SolenoidValve* ptrLV85;// E3 LO2 Prevlv OP Pwr 2


			// PD

			PressureActuatedValve* ptrPD1;// LOX 17in Disc
			//PD1L	LOX 17in Disc Latch
			PressureActuatedValve* ptrPD2;// LH2 17in Disc
			//PD2L	LH2 17in Disc Latch
			PressureActuatedValve* ptrPD3;// LH2 4in Disc
			/*ptrPD4;// GO2 Press Disconnect
			ptrPD5;// GH2 Press Disconnect
			PD6
			PD7
			PD8	GHE 1" SUPPLY FILL DISCONNECT
			PD9	GO2 1" REPRESS DISCONNECT
			PD10	GH2 1" REPRESS DISCONNECT
			PD11	FILL/DRAIN LH2 DISCONNECT
			PD12	FILL/DRAIN LO2 DISCONNECT
			PD13	LO2 BLEED DISCONNECT
			PD14
			PD15	GO2 TEST POINT COUPLING
			PD16	GH2 TEST POINT COUPLING
			PD17	LH2 Hi Pt Bl disconnect
			*/

			// RV
			bool RV5;
			bool RV6;

			Sensor ManifPress[2];// 1) LOX, 2) LH2

		public:
			MPS( AtlantisSubsystemDirector* _director, HeSysPneu* HeSys );
			~MPS( void );

			void Realize( void ) override;
			void OnPostStep( double simt, double simdt, double mjd ) override;

			void OnSaveState( FILEHANDLE scn ) const override;
			bool OnParseLine( const char* line ) override;

			double GetLOXManifPress( void ) const;
			double GetLH2ManifPress( void ) const;

			/**
			 * This function is called by the SSMEs to get the position of its LOX prevalve.
			 * This function should only be used for physics purposes.
			 * @param[in]	eng	number of the calling SSME
			 * @return		position of valve (between 0 and 1)
			 */
			double GetLOXPVPos( int eng ) const;

			/**
			 * This function is called by the SSMEs to get the position of its LH2 prevalve.
			 * This function should only be used for physics purposes.
			 * @param[in]	eng	number of the calling SSME
			 * @return		position of valve (between 0 and 1)
			 */
			double GetLH2PVPos( int eng ) const;

			/**
			 * This function is called by the SSMEs to simulate pressurant flow.
			 * It uses the positions of the flow control valves to control the flow.
			 * @param[in]	eng	number of the calling SSME
			 * @param[in]	GOXmass	mass of gaseous oxygen (in kg)
			 * @param[in]	GH2mass	mass of gaseous hydrogen (in kg)
			 */
			void PressurantFlow( int eng, double GOXmass, double GH2mass );
	};
}


#endif// _mps_MPS_H_
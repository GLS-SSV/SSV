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
2022/09/29   GLS
2023/11/08   GLS
2026/09/18   GLS
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


#include "../AtlantisSubsystem.h"
#include <Sensor.h>
#include <discsignals.h>


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
			// PV14;// E-1 LH2 Recirc Pump Vlv
			// PV15;// E-2 LH2 Recirc Pump Vlv
			// PV16;// E-3 LH2 Recirc Pump Vlv
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
			// LV36;// LH2 Recirc Pump Vlv
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


			Sensor ManifPress[2];// 0) LOX, 1) LH2
			// CW and D&C connected directly to sensor output
			discsignals::DiscInPort ManifPress_LOX;
			discsignals::DiscInPort ManifPress_LH2;
			discsignals::DiscOutPort ManifPress_LOX_TM;
			discsignals::DiscOutPort ManifPress_LH2_TM;


			discsignals::DiscInPort dipE1_GPC_CL_INH_A;
			discsignals::DiscInPort dipE1_GPC_CL_INH_B;
			discsignals::DiscInPort dipE1_GPC_CL_INH_C;
			discsignals::DiscInPort dipE2_GPC_CL_INH_A;
			discsignals::DiscInPort dipE2_GPC_CL_INH_B;
			discsignals::DiscInPort dipE2_GPC_CL_INH_C;
			discsignals::DiscInPort dipE3_GPC_CL_INH_A;
			discsignals::DiscInPort dipE3_GPC_CL_INH_B;
			discsignals::DiscInPort dipE3_GPC_CL_INH_C;
			discsignals::DiscInPort dipPV1_GPC_OP_A;
			discsignals::DiscInPort dipPV1_GPC_OP_B;
			discsignals::DiscInPort dipPV1_GPC_OP_C;
			discsignals::DiscInPort dipPV1_GPC_OP_D;
			discsignals::DiscInPort dipPV1_GPC_CL_A;
			discsignals::DiscInPort dipPV1_GPC_CL_B;
			discsignals::DiscInPort dipPV1_GPC_CL_C;
			discsignals::DiscInPort dipPV1_GPC_CL_D;
			discsignals::DiscInPort dipPV1_OP;// TODO make switch
			discsignals::DiscInPort dipPV1_CL;// TODO make switch
			discsignals::DiscInPort dipPV2_GPC_OP_A;
			discsignals::DiscInPort dipPV2_GPC_OP_B;
			discsignals::DiscInPort dipPV2_GPC_OP_C;
			discsignals::DiscInPort dipPV2_GPC_OP_D;
			discsignals::DiscInPort dipPV2_GPC_CL_A;
			discsignals::DiscInPort dipPV2_GPC_CL_B;
			discsignals::DiscInPort dipPV2_GPC_CL_C;
			discsignals::DiscInPort dipPV2_GPC_CL_D;
			discsignals::DiscInPort dipPV2_OP;// TODO make switch
			discsignals::DiscInPort dipPV2_CL;// TODO make switch
			discsignals::DiscInPort dipPV3_GPC_OP_A;
			discsignals::DiscInPort dipPV3_GPC_OP_B;
			discsignals::DiscInPort dipPV3_GPC_OP_C;
			discsignals::DiscInPort dipPV3_GPC_OP_D;
			discsignals::DiscInPort dipPV3_GPC_CL_A;
			discsignals::DiscInPort dipPV3_GPC_CL_B;
			discsignals::DiscInPort dipPV3_GPC_CL_C;
			discsignals::DiscInPort dipPV3_GPC_CL_D;
			discsignals::DiscInPort dipPV3_OP;// TODO make switch
			discsignals::DiscInPort dipPV3_CL;// TODO make switch
			discsignals::DiscInPort dipPV4_GPC_OP_A;
			discsignals::DiscInPort dipPV4_GPC_OP_B;
			discsignals::DiscInPort dipPV4_GPC_OP_C;
			discsignals::DiscInPort dipPV4_GPC_CL_A;
			discsignals::DiscInPort dipPV4_GPC_CL_B;
			discsignals::DiscInPort dipPV4_GPC_CL_C;
			discsignals::DiscInPort dipPV4_OP;// TODO make switch
			discsignals::DiscInPort dipPV4_CL;// TODO make switch
			discsignals::DiscInPort dipPV5_GPC_OP_A;
			discsignals::DiscInPort dipPV5_GPC_OP_B;
			discsignals::DiscInPort dipPV5_GPC_OP_C;
			discsignals::DiscInPort dipPV5_GPC_CL_A;
			discsignals::DiscInPort dipPV5_GPC_CL_B;
			discsignals::DiscInPort dipPV5_GPC_CL_C;
			discsignals::DiscInPort dipPV5_OP;// TODO make switch
			discsignals::DiscInPort dipPV5_CL;// TODO make switch
			discsignals::DiscInPort dipPV6_GPC_OP_A;
			discsignals::DiscInPort dipPV6_GPC_OP_B;
			discsignals::DiscInPort dipPV6_GPC_OP_C;
			discsignals::DiscInPort dipPV6_GPC_CL_A;
			discsignals::DiscInPort dipPV6_GPC_CL_B;
			discsignals::DiscInPort dipPV6_GPC_CL_C;
			discsignals::DiscInPort dipPV6_OP;// TODO make switch
			discsignals::DiscInPort dipPV6_CL;// TODO make switch
			discsignals::DiscInPort dipPV7_GPC_CL_A;
			discsignals::DiscInPort dipPV7_GPC_CL_B;
			discsignals::DiscInPort dipPV7_GPC_CL_C;
			discsignals::DiscInPort dipPV7_OP;// TODO make switch
			discsignals::DiscInPort dipPV7_CL;// TODO make switch
			discsignals::DiscInPort dipPV8_GPC_CL_A;
			discsignals::DiscInPort dipPV8_GPC_CL_B;
			discsignals::DiscInPort dipPV8_GPC_CL_C;
			discsignals::DiscInPort dipPV8_OP;// TODO make switch
			discsignals::DiscInPort dipPV8_CL;// TODO make switch
			discsignals::DiscInPort dipPV9_GPC_OP;
			discsignals::DiscInPort dipPV9_GPC_CL;
			discsignals::DiscInPort dipPV9_OP;// TODO make switch
			discsignals::DiscInPort dipPV9_CL;// TODO make switch
			discsignals::DiscInPort dipPV10_GPC_OP_A;
			discsignals::DiscInPort dipPV10_GPC_OP_B;
			discsignals::DiscInPort dipPV10_GPC_CL;
			discsignals::DiscInPort dipPV10_OP;// TODO make switch
			discsignals::DiscInPort dipPV10_CL;// TODO make switch
			discsignals::DiscInPort dipPV11_GPC_OP;
			discsignals::DiscInPort dipPV11_GPC_CL;
			discsignals::DiscInPort dipPV11_OP;// TODO make switch
			discsignals::DiscInPort dipPV11_CL;// TODO make switch
			discsignals::DiscInPort dipPV12_GPC_OP_A;
			discsignals::DiscInPort dipPV12_GPC_OP_B;
			discsignals::DiscInPort dipPV12_GPC_CL;
			discsignals::DiscInPort dipPV12_OP;// TODO make switch
			discsignals::DiscInPort dipPV12_CL;// TODO make switch
			discsignals::DiscInPort dipPV17_OP_A;
			discsignals::DiscInPort dipPV17_OP_B;
			discsignals::DiscInPort dipPV17_OP_C;
			discsignals::DiscInPort dipPV18_OP_A;
			discsignals::DiscInPort dipPV18_OP_B;
			discsignals::DiscInPort dipPV18_OP_C;
			discsignals::DiscInPort dipPV19_CL_A;
			discsignals::DiscInPort dipPV19_CL_B;
			discsignals::DiscInPort dipPV19_CL_C;
			discsignals::DiscInPort dipPV20_CL_A;
			discsignals::DiscInPort dipPV20_CL_B;
			discsignals::DiscInPort dipPV21_CL_A;
			discsignals::DiscInPort dipPV21_CL_B;
			discsignals::DiscInPort dipLV39_GPC_OP;
			discsignals::DiscInPort dipLV40_GPC_OP;
			discsignals::DiscInPort dipLV40_OP;// TODO make switch
			discsignals::DiscInPort dipLV40_CL;// TODO make switch
			discsignals::DiscInPort dipLV41_GPC_OP;
			discsignals::DiscInPort dipLV41_OP;// TODO make switch
			discsignals::DiscInPort dipLV41_CL;// TODO make switch
			discsignals::DiscInPort dipLV42_GPC_OP;
			discsignals::DiscInPort dipLV42_OP;// TODO make switch
			discsignals::DiscInPort dipLV42_CL;// TODO make switch
			discsignals::DiscInPort dipLV43_GPC_OP;
			discsignals::DiscInPort dipLV43_OP;// TODO make switch
			discsignals::DiscInPort dipLV43_CL;// TODO make switch
			discsignals::DiscOutPort dopLV12;
			discsignals::DiscOutPort dopLV13;
			discsignals::DiscOutPort dopLV14;
			discsignals::DiscOutPort dopLV15;
			discsignals::DiscOutPort dopLV16;
			discsignals::DiscOutPort dopLV17;
			discsignals::DiscOutPort dopLV18;
			discsignals::DiscOutPort dopLV19;
			discsignals::DiscOutPort dopLV20;
			discsignals::DiscOutPort dopLV21;
			discsignals::DiscOutPort dopLV22;
			discsignals::DiscOutPort dopLV23;
			discsignals::DiscOutPort dopLV24;
			discsignals::DiscOutPort dopLV25;
			discsignals::DiscOutPort dopLV28;
			discsignals::DiscOutPort dopLV29;
			discsignals::DiscOutPort dopLV30;
			discsignals::DiscOutPort dopLV31;
			discsignals::DiscOutPort dopLV32;
			discsignals::DiscOutPort dopLV33;
			discsignals::DiscOutPort dopLV34;
			discsignals::DiscOutPort dopLV35;
			discsignals::DiscOutPort dopLV39;
			discsignals::DiscOutPort dopLV40;
			discsignals::DiscOutPort dopLV41;
			discsignals::DiscOutPort dopLV42;
			discsignals::DiscOutPort dopLV43;
			discsignals::DiscOutPort dopLV72;
			discsignals::DiscOutPort dopLV73;
			discsignals::DiscOutPort dopLV76;
			discsignals::DiscOutPort dopLV77;
			discsignals::DiscOutPort dopLV78;
			discsignals::DiscOutPort dopLV80;
			discsignals::DiscOutPort dopLV81;
			discsignals::DiscOutPort dopLV82;
			discsignals::DiscOutPort dopLV83;
			discsignals::DiscOutPort dopLV84;
			discsignals::DiscOutPort dopLV85;

			discsignals::DiscInPort dipLH2UllagePress;

			discsignals::DiscInPort dipLOXUllagePressure[3];
			discsignals::DiscInPort dipLH2UllagePressure[3];
			discsignals::DiscOutPort dopGOX_FCV[3];
			discsignals::DiscOutPort dopGH2_FCV[3];

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

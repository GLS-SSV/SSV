/****************************************************************************
  This file is part of Space Shuttle Vessel

  User Interface Control definition


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
#ifndef _UICONTROL_H_
#define _UICONTROL_H_


#include <string>
#include "SimpleGPCSoftware.h"


namespace dps
{
	/**
	 * System Services \ User Interface
	 */
	class UserInterfaceControl:public SimpleGPCSoftware
	{
		private:
			SimpleGPCSystem* pGPC;

			void SetIllegalEntry( const unsigned short deu );
			unsigned short GetIdx( const unsigned short ops, const unsigned short mode ) const;




			unsigned short DMC_CASE;// MCDS_Function

			void DMC_SUPER( void );// User interface control supervisor (500)
			void DMC_FUNCTIONS( void );// MDCS Functions Processor (505)
			void Keyboard_Input_Initialization( void );// (505.1)
			void MCDS_Function_Clean_Up( void );// (505.1)
			void Application_Interface( void );// (505.3)
			void MF_Change( void );// (505.4)


			unsigned short DMC_SDEU;// Start_DEU
			unsigned short DMC_EDEU;// End_DEU
			unsigned short DMC_K;// K_Index

			void DMC_DISPLAY( void );// MCDS_Display_Coordinator (520)
			void DEU_Find( void );// (520.2)
			void no_name( void );// (520.4)
			void DFB_Search( const unsigned short disp );// (520.5)
			void Display_Processor( void );// (520.6)
			void New_Display_Call( void );// (520.7)


			void DM1_KEYBOARD( void );// Keyboard data processor
			//void DM1_KEYSTROKE_PROC( const SCP_DIT& dit );
			//void DM2_APPLICATION( void );// Application request processor
			//void DM3_DISPLAY( void );// Page locator
			//void DM4_DEU_PROC( void );// DEU background update processor
			//void DM5_NEW_CSEG( void );// Control segment scheduler
			//void DM6_OPS_PROC( void );// OPS request processor
			//void DM7_REQ_MFTERM( void );// Request MF termination processor
			//void DM8_SPEC_PROC( void );// SPEC request processor
			void DM9_ITEM( void );// Item processor
			//void DMN_NEW_LOAD( void );// Buffer addressability processor
			void DMR_RESUME( void );// Resume DEU processor
			//void DMZ_LOG( void );// UI control supervisor log function
			//void DMC_CC_SPEC( void );// Cargo control SPEC processor
			//void DXR_DMM_ROLLIN( void );// MM rollin display processor
			//void DXX_CSEG_TERM( void );// Control segment termination
			void DIR_IORESET( void );// I/O reset processor




			unsigned short DMC_PROCTYPE;// Sequence_Process_Type (0=Illegal Entry; 1=OPS Transition; 2=Mode To Mode Transition; 3=Schedule; 6=Cancel Old SPEC & Start New SPEC; 7=Reconfiguration Required)
			unsigned short DMC_TVAL;// Sequence_Tester
			unsigned short DMC_TVAL1;// Sequence_Test_1
			unsigned short DMC_TVAL_2;// Sequence_Test 2
			unsigned short DMC_TVAL_3;// Sequence_Test 3
			unsigned short DMC_TVAL_4;// Sequence_Test 4
			unsigned short DMC_REC_IN_PROGRESS;// Reconfiguration_In_Progress
			unsigned short DMC_TERMI;// Terminator_Index
			unsigned short DMC_TINDX;// Test_Index
			unsigned short DMC_SZFMACT;// SPEC_Zero_MACT
			unsigned short DMC_REQOSNBR;// Sequence_Request_OPS/SPEC
			short DMC_AMT_I;// Sequence_AMT_Index
			unsigned short DMC_MACT_I;// Sequence_MACT_Index
			unsigned short DMC_CUR_OP;// Sequence_Current_OPS
			unsigned short DMC_SEQVAL;// Sequence_Value
			unsigned short DMC_WTCT;// Sequence_Wait_Count
			unsigned short DMC_SAVE;// Old_OPS
			short DMC_REQMODE;// Sequence_Request_Mode
			//unsigned short DMC_SPIDS[3];// Save_SPEC_Numbers
			unsigned short DMC_SPECID[4];// Save_SPEC_Numbers.Next_SPEC_Number
			//unsigned short DMC_SPEC_T[3];// Next_SPEC_MACT_AMT_Indexes
			unsigned short DMC_MINXTS[4];// Next_SPEC_MACT_AMT_Indexes.Next_SPEC_MACT
			unsigned short DMC_AINXTS[4];// Next_SPEC_MACT_AMT_Indexes.Next_SPEC_AMT
			unsigned short DMC_FOUND;// Found_Value/Display_Found_ID
			unsigned short DMC_GRTIX;// GRT_Index
			unsigned short DMC_UNDX;// Sequence_Update_Index
			unsigned short DMC_GPCZ;// GPC_OPS_Zero_Keystroke
			unsigned short DMC_TYPE;// Action_Type
			unsigned short DMC_MFI;// Sequence_Major_Function
			std::string DMC_PROG_NAME;// Sequence_Program_Name
			unsigned short DMC_INITIAL;// Value Specifying Initial Conditions (0 = Initial Conditions; NE 0 Is Non Initial Condition)
			unsigned short DMC_MACT_INDEX;// MCDS_MACT_Index
			unsigned short DMC_AMTVALID;// AMT_Table_Valid
			//unsigned short DMC_OZPAGE_VAL;// OPS_Zero_Page
			unsigned short DMC_REC_IP2;// Value Specifying Reconfiguration Being Started, 0 = Not Started, NE 0 = Reconfiguration Started

			unsigned short DMCVL_D_LVLN;// Level Number Passed By All Callers Of MCDS_DISPLAY_COORDINATION (520) Specifying Level Of Display Requested, 1 = OPS Level Display Requested, 2 = SPEC Level Display Requested, 3 = DISP Level Display Requested
			unsigned short DMCVL_D_DISP;// The Display Number Requested By All Callers Of MCDS_DISPLAY_COORDINATION (520)

			/*Four Values Corresponding To The 4 Copies Of The MACT Specifying:
			When = 0 That An OPS (Level 1) Display Is Being Used By The MACT Copy Or Not Used And When NE 0 Specifies A SPEC (Level 2) Disp Is Being Used By The MACT Copy
			1 = DEU 1
			2 = DEU 2
			3 = DEU 3
			4 = DEU 4*/
			unsigned short DMCV_DEU_MACT[4];


			void DMC_SEQ_REQ_PROC( unsigned short DMC_TYPE/*Action_Type*/ );// Sequence_Request_Processor (560)
			void Termination_Processor( void );// (560.01)
			void Secondary_Reconfiguration_Processor( void );// (560.02)
			void Reconfiguration_Complete_Processor( void );// (560.03)
			void Keyboard_Processor( void );// (560.04)
			void OPS_Zero_Processor( void );// (560.05)
			void OPS_Non_Zero_Processor( void );// (560.06)
			void SPEC_Validity_Processor( void );// (560.07)
			void SPEC_Search_OPS_Type( void );// (560.08)
			void SPEC_Active_Search( void );// (560.09)
			void SPEC_Processor( void );// (560.10)
			void Control_Segment_Scheduler( void );// (560.11)
			void SPEC_Control_Processor( void );// (560.12)
			void OPS_Control_Processor( void );// (560.13)
			void Control_Segment_Terminator( void );// (560.14)
			void Sequence_Reconfiguration_Pre_Processor( void );// (560.15)
			void Sequence_Reconfiguration_Processor( void );// (560.16)
			void AMT_GRT_Search_Processor( void );// (560.17)
			void IN_Core_Tester( void );// (560.18)
			void Overlay_Allowed_Tester( void );// (560.19)
			void Mode_To_Mode_Processor( void );// (560.20)
			void Buffer_Address_Mover( void );// (560.21)


		public:
			explicit UserInterfaceControl( SimpleGPCSystem* pGPC );
			virtual ~UserInterfaceControl( void );

			bool OnParseLine( const char* keyword, const char* value );
			void OnSaveState( FILEHANDLE scn ) const;

			void OnPreStep( double simt, double simdt, double mjd ) override;
	};
}

#endif// _UICONTROL_H_

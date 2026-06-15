#include "SSP_EXEC.h"
#include "SSD_SP_DATA_ACQ.h"
#include "SSB_PL_BAY_DOORS.h"
#include "SSO_SP_DATA_OUT.h"
#include <cassert>


namespace dps
{
	SSP_EXEC::SSP_EXEC( SimpleGPCSystem* pGPC ):SimpleGPCSoftware( pGPC, "SSP_EXEC" )
	{
		cycle = 0;
		pSSD_SP_DATA_ACQ = dynamic_cast<SSD_SP_DATA_ACQ*>(pGPC->GetCOMSUB( "SSD_SP_DATA_ACQ" ));
		assert( (pSSD_SP_DATA_ACQ != NULL) && "SSP_EXEC::SSP_EXEC.pSSD_SP_DATA_ACQ" );
		pSSB_PL_BAY_DOORS = dynamic_cast<SSB_PL_BAY_DOORS*>(pGPC->GetCOMSUB( "SSB_PL_BAY_DOORS" ));
		assert( (pSSB_PL_BAY_DOORS != NULL) && "SSP_EXEC::SSP_EXEC.pSSB_PL_BAY_DOORS" );
		pSSO_SP_DATA_OUT = dynamic_cast<SSO_SP_DATA_OUT*>(pGPC->GetCOMSUB( "SSO_SP_DATA_OUT" ));
		assert( (pSSO_SP_DATA_OUT != NULL) && "SSP_EXEC::SSP_EXEC.pSSO_SP_DATA_OUT" );
		return;
	}

	SSP_EXEC::~SSP_EXEC( void )
	{
		return;
	}

	void SSP_EXEC::OnPreStep( double simt, double simdt, double mjd )
	{
		oapiWriteLogV( "		%d SSP_EXEC", (cycle % 12) + 1 );
		cycle++;

		// Hybrid Dispatcher
		for (int i = 1; i <= 32;i++)
		{
			SCP_HYB_DISPATCH SHD_HYB_DISPATCH;
			ReadCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, i, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );

			SHD_HYB_DISPATCH.PC = static_cast<short>(SHD_HYB_DISPATCH.PC) - 1;
			if (static_cast<short>(SHD_HYB_DISPATCH.PC) <= 0)
			{
				if (static_cast<short>(SHD_HYB_DISPATCH.FREQ) <= 0)
				{
					if (SHD_HYB_DISPATCH.FREQ == 0)
					{
						SHD_HYB_DISPATCH.PC = 1;
						WriteCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, i, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );
						break;
					}

					SHD_HYB_DISPATCH.PC = SHD_HYB_DISPATCH.FREQ - 0x8000;
				}
				else
				{
					SHD_HYB_DISPATCH.PC = SHD_HYB_DISPATCH.FREQ;

					switch (SHD_HYB_DISPATCH.CASENO)
					{
						case 1:
							//SP_Current_Time = Clocktime;
							pSSD_SP_DATA_ACQ->Call();
							oapiWriteLogV( "SSD_SP_DATA_ACQ" );
							break;
						case 2:
							//SSA_APU_FUEL_QTY();
							oapiWriteLogV( "SSA_APU_FUEL_QTY" );
							break;
						case 3:
							//SSF_FUEL_CELL();
							oapiWriteLogV( "SSF_FUEL_CELL" );
							break;
						case 4:
							//SSC_FUEL_CELL_PURGE();
							oapiWriteLogV( "SSC_FUEL_CELL_PURGE" );
							break;
						case 5:
							//SSN_O2N2_QTY();
							oapiWriteLogV( "SSN_O2N2_QTY" );
							break;
						case 6:
							//SSW_H2O_PUMP_P();
							oapiWriteLogV( "SSW_H2O_PUMP_P" );
							break;
						case 7:
							//SST_HYD_FLD_TEMP();
							oapiWriteLogV( "SST_HYD_FLD_TEMP" );
							break;
						case 8:
							//SSR_REC_TAPE_POS();
							oapiWriteLogV( "SSR_REC_TAPE_POS" );
							break;
						case 9:
							//SSH_HYD_H2O_QTY();
							oapiWriteLogV( "SSH_HYD_H2O_QTY" );
							break;
						case 10:
							pSSB_PL_BAY_DOORS->Call();
							oapiWriteLogV( "SSB_PL_BAY_DOORS" );
							break;
						case 11:
							//SSS_STAND_H2O_COOL();
							oapiWriteLogV( "SSS_STAND_H2O_COOL" );
							break;
						case 12:
							//SSM_ANT_MGMT();
							oapiWriteLogV( "SSM_ANT_MGMT" );
							break;
						case 13:
							pSSO_SP_DATA_OUT->Call();
							oapiWriteLogV( "SSO_SP_DATA_OUT" );
							break;
						case 14:
							// Set Full Execute Flag
							WriteCOMPOOL_IS( SCP_CSBB_FULL_EX_FLAG, 1 );
							oapiWriteLogV( "CSSB_FULL_EX_FLAG" );
							break;
						//////////////////////////////////////////////////////////////
						/*case 1:// Set Full Execute Flag For Payload Bay Doors
							break;
						case 2:// PAYLOAD_BAY_DOORS
							break;
						case 3:// APU_FUEL_QUANTITY
							break;
						case 4:// FUEL_CELL_COMP
							break;
						case 5:// FUEL_CELL_PURGE
							break;
						case 6:// O2_N2_QUANTITY
							break;
						case 7:// HYDRAULIC_FLUID_TEMP_CONTROL
							break;
						case 8:// RECORDER_TAPE_POSITION
							break;
						case 9:// HYDRAULIC_WATER_BOILER_QTY
							break;
						case 10:// STANDBY_WATER_COOLANT
							break;
						case 11:// ANTENNA_MANAGEMENT
							break;
						case 12:// Move ICC Data From Input Buffer To Data Buffer...
							break;
						case 13:// SP_DATA_OUT
							break;
						case 14:// TIME_EXECUTE_COMMAND
							break;
						case 15:// SSUS_SEQUENCE_CONTROL
							// PDS 1.04Hz 0.96s
							break;
						case 16:// IUS_GNC_TRANSFER
							// PDL 0.52Hz 1.92s
							break;
						case 17:// STANDARD_GNC_TRANSFER
							// PMG 0.52Hz 1.92s
							break;
						case 18:// If Special Process In Progress Mask...
							break;
						case 19:// PCS CONTROL (NULL CASE)
							break;
						case 20:// MISSION_UNIQUE_PROCESS_1
							break;
						case 21:// MISSION_UNIQUE_PROCESS_2
							break;
						case 22:// MISSION_UNIQUE_PROCESS_3
							break;
						case 23:// MISSION_UNIQUE_PROCESS_4
							break;
						case 24:// MISSION_UNIQUE_PROCESS_5
							break;
						case 25:// MISSION_UNIQUE_PROCESS_6
							break;
						case 26:// MISSION_UNIQUE_PROCESS_7
							break;
						case 27:// MISSION_UNIQUE_PROCESS_8
							break;
						case 28:// SPACELAB_READ_PROTOCOL
							break;
						case 29:// SPACELAB_WRITE_PROTOCOL
							break;
						case 30:// SPACELAB_GNC_TRANSFER
							break;*/
					}
				}
			}

			WriteCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, i, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );
		}
		return;
	}
}

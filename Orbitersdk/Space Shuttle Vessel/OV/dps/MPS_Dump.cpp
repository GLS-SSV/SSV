/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/04/01   GLS
2020/04/07   GLS
2020/06/20   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/05/29   GLS
2022/08/05   GLS
********************************************/
#include "MPS_Dump.h"
#include "..\Atlantis.h"
#include "SSME_SOP.h"
#include "SSME_Operations.h"
#include "IO_Control.h"
#include "MPS_ATVC_CMD_SOP.h"
#include <cassert>


namespace dps
{
	constexpr double DUMP_START_DELAY = 120;// from MECO confirmed

	constexpr double HE_IC_OP_DELAY = 20;// from MECO confirmed
	constexpr double HE_IC_CL_DELAY = 120;// from dump start

	constexpr double LOX_DUMP_START_DELAY = 0;// from dump start
	constexpr double LOX_DUMP_DURATION = 120;
	constexpr double LOX_DUMP_PRESS_DURATION = 90;

	constexpr double LH2_DUMP_START_DELAY = 0;// from MECO
	constexpr double LH2_DUMP_DURATION = 120;

	constexpr double LH2_DUMP_BU_VLV_START_DELAY = 11.4;// from MECO confirmed
	constexpr double LH2_DUMP_BU_VLV_DURATION = 228.6;

	constexpr double FIRST_AUTOMATED_VACUUM_INERT_START_DELAY = 1020;// from dump start
	constexpr double FIRST_AUTOMATED_VACUUM_INERT_DURATION = 120;

	constexpr double SECOND_AUTOMATED_VACUUM_INERT_START_DELAY = 0;// from MM106
	constexpr double SECOND_AUTOMATED_VACUUM_INERT_DURATION = 180;// approx


	MPS_Dump::MPS_Dump( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "MPS_Dump" )
	{
		active = false;
		dump_started = false;

		MM106_trans = false;

		t_last = 0;
		return;
	}

	MPS_Dump::~MPS_Dump( void )
	{
		return;
	}

	void MPS_Dump::OnPreStep( double simt, double simdt, double mjd )
	{
		if (active == false)
		{
			if (pSSME_Operations->GetMECOConfirmedFlag() == true)
			{
				active = true;
				t_MECO = simt;
			}
		}
		else
		{
			if (GetMajorMode() > 600)// RTLS
			{
				//
			}
			else// NOM
			{
				// LH2 B/U dump switch
				if (ReadCOMPOOL_IS( SCP_MPS_BACKUP_LH2_PRPLT_DUMP_START ) == 1)
				{
					// open
					pIO_Control->SetCommand( LH2_INBD_BU_DV_OP, true );
					pIO_Control->SetCommand( LH2_OTBD_BU_DV_OP, true );
				}
				else
				{
					if (ReadCOMPOOL_IS( SCP_MPS_BACKUP_LH2_PRPLT_DUMP_STOP ) == 1)
					{
						// close
						pIO_Control->SetCommand( LH2_INBD_BU_DV_OP, false );
						pIO_Control->SetCommand( LH2_OTBD_BU_DV_OP, false );
					}
				}

				// LH2 B/U dump start
				if (((t_MECO + LH2_DUMP_BU_VLV_START_DELAY) <= simt) && ((t_MECO + LH2_DUMP_BU_VLV_START_DELAY) > t_last))
				{
					pIO_Control->SetCommand( LH2_INBD_BU_DV_OP, true );
					pIO_Control->SetCommand( LH2_OTBD_BU_DV_OP, true );
					oapiWriteLogV( "LH2 Backup Dump Valves open @ MET %.2f", STS()->GetMET() );
				}

				// LH2 B/U dump end
				if (((t_MECO + LH2_DUMP_BU_VLV_START_DELAY + LH2_DUMP_BU_VLV_DURATION) <= simt) && ((t_MECO + LH2_DUMP_BU_VLV_START_DELAY + LH2_DUMP_BU_VLV_DURATION) > t_last))
				{
					pIO_Control->SetCommand( LH2_INBD_BU_DV_OP, false );
					pIO_Control->SetCommand( LH2_OTBD_BU_DV_OP, false );
					oapiWriteLogV( "LH2 Backup Dump Valves close @ MET %.2f", STS()->GetMET() );
				}

				// He I/Cs
				if (((t_MECO + HE_IC_OP_DELAY) <= simt) && ((t_MECO + HE_IC_OP_DELAY) > t_last))
				{
					pIO_Control->SetCommand( HE_IC_CTR_OUT_OP, true );
					pIO_Control->SetCommand( HE_IC_LEFT_IN_OP, true );
					pIO_Control->SetCommand( HE_IC_RIGHT_OUT_OP, true );
					oapiWriteLogV( "Helium Interconnect valves open @ MET %.2f", STS()->GetMET() );
				}

				if ((dump_started == false) && ((t_MECO + 16) <= simt))
				{
					if (((t_MECO + DUMP_START_DELAY) <= simt) || ReadCOMPOOL_IS( SCP_MPS_PRPLT_DUMP_SEQUENCE_START ) || ((STS()->GetLH2ManifPress() > 60) && (STS()->GetLH2ManifPress() < 90)))// time, sw in start or overpressure
					{
						// start dump
						if (ReadCOMPOOL_IS( SCP_MPS_PRPLT_DUMP_SEQUENCE_STOP ) == 0)// sw not in stop
						{
							dump_started = true;
							t_dump_start = simt;
							oapiWriteLogV( "MPS Dump Sequence start @ MET %.2f", STS()->GetMET() );
						}
					}
				}

				if (dump_started == true)
				{
					// LOX dump start
					if (((t_dump_start + LOX_DUMP_START_DELAY) <= simt) && ((t_dump_start + LOX_DUMP_START_DELAY) > t_last))
					{
						pSSME_SOP->SetOxidizerDumpStartCommandFlag( 1 );
						pSSME_SOP->SetOxidizerDumpStartCommandFlag( 2 );
						pSSME_SOP->SetOxidizerDumpStartCommandFlag( 3 );
						pIO_Control->SetCommand( LOX_REPRESS_1_OP, true );
						pIO_Control->SetCommand( LOX_REPRESS_2_OP, true );
						pIO_Control->SetCommand( ME1_LOX_PVLV_OP_A, true );
						pIO_Control->SetCommand( ME2_LOX_PVLV_OP_A, true );
						pIO_Control->SetCommand( ME3_LOX_PVLV_OP_A, true );
						pIO_Control->SetCommand( ME1_LOX_PVLV_OP_B, true );
						pIO_Control->SetCommand( ME2_LOX_PVLV_OP_B, true );
						pIO_Control->SetCommand( ME3_LOX_PVLV_OP_B, true );
						pIO_Control->SetCommand( ME1_LOX_PVLV_CL_A, false );
						pIO_Control->SetCommand( ME2_LOX_PVLV_CL_A, false );
						pIO_Control->SetCommand( ME3_LOX_PVLV_CL_A, false );
						pIO_Control->SetCommand( ME1_LOX_PVLV_CL_B, false );
						pIO_Control->SetCommand( ME2_LOX_PVLV_CL_B, false );
						pIO_Control->SetCommand( ME3_LOX_PVLV_CL_B, false );
						oapiWriteLogV( "LOX Dump start @ MET %.2f", STS()->GetMET() );
					}

					// LOX dump end
					if (((t_dump_start + LOX_DUMP_START_DELAY + LOX_DUMP_PRESS_DURATION) <= simt) && ((t_dump_start + LOX_DUMP_START_DELAY + LOX_DUMP_PRESS_DURATION) > t_last))
					{
						pIO_Control->SetCommand( LOX_REPRESS_1_OP, false );
						pIO_Control->SetCommand( LOX_REPRESS_2_OP, false );
					}
					if (((t_dump_start + LOX_DUMP_START_DELAY + LOX_DUMP_DURATION) <= simt) && ((t_dump_start + LOX_DUMP_START_DELAY + LOX_DUMP_DURATION) > t_last))
					{
						pSSME_SOP->SetDumpStopCommandFlag( 1 );
						pSSME_SOP->SetDumpStopCommandFlag( 2 );
						pSSME_SOP->SetDumpStopCommandFlag( 3 );
						pIO_Control->SetCommand( ME1_LOX_PVLV_OP_A, false );
						pIO_Control->SetCommand( ME2_LOX_PVLV_OP_A, false );
						pIO_Control->SetCommand( ME3_LOX_PVLV_OP_A, false );
						pIO_Control->SetCommand( ME1_LOX_PVLV_OP_B, false );
						pIO_Control->SetCommand( ME2_LOX_PVLV_OP_B, false );
						pIO_Control->SetCommand( ME3_LOX_PVLV_OP_B, false );
						oapiWriteLogV( "LOX Dump complete @ MET %.2f", STS()->GetMET() );
					}

					// LH2 dump start
					if (((t_dump_start + LH2_DUMP_START_DELAY) <= simt) && ((t_dump_start + LH2_DUMP_START_DELAY) > t_last))
					{
						pIO_Control->SetCommand( LH2_OTBD_FD_VLV_CL, false );
						pIO_Control->SetCommand( LH2_OTBD_FD_VLV_OP, true );
						pIO_Control->SetCommand( LH2_INBD_FD_VLV_CL, false );
						pIO_Control->SetCommand( LH2_INBD_FD_VLV_OP, true );
						pIO_Control->SetCommand( LH2_TOPPING_VLV_OP, true );
						pIO_Control->SetCommand( ME1_LH2_PVLV_OP, true );
						pIO_Control->SetCommand( ME2_LH2_PVLV_OP, true );
						pIO_Control->SetCommand( ME3_LH2_PVLV_OP, true );
						pIO_Control->SetCommand( ME1_LH2_PVLV_CL, false );
						pIO_Control->SetCommand( ME2_LH2_PVLV_CL, false );
						pIO_Control->SetCommand( ME3_LH2_PVLV_CL, false );
						oapiWriteLogV( "LH2 Dump start @ MET %.2f", STS()->GetMET() );
					}

					// LH2 dump end
					if (((t_dump_start + LH2_DUMP_START_DELAY + LH2_DUMP_DURATION) <= simt) && ((t_dump_start + LH2_DUMP_START_DELAY + LH2_DUMP_DURATION) > t_last))
					{
						pIO_Control->SetCommand( LH2_OTBD_FD_VLV_CL, true );
						pIO_Control->SetCommand( LH2_OTBD_FD_VLV_OP, false );
						pIO_Control->SetCommand( LH2_INBD_FD_VLV_OP, false );
						pIO_Control->SetCommand( LH2_TOPPING_VLV_OP, false );
						pIO_Control->SetCommand( ME1_LH2_PVLV_OP, false );
						pIO_Control->SetCommand( ME2_LH2_PVLV_OP, false );
						pIO_Control->SetCommand( ME3_LH2_PVLV_OP, false );
						oapiWriteLogV( "LH2 Dump complete @ MET %.2f", STS()->GetMET() );
					}

					// end of dump
					if (((t_dump_start + HE_IC_CL_DELAY) <= simt) && ((t_dump_start + HE_IC_CL_DELAY) > t_last))
					{
						WriteCOMPOOL_IS( SCP_MPS_LO2_DUMP_STOP, 1 );
						pIO_Control->SetCommand( HE_IC_CTR_OUT_OP, false );
						pIO_Control->SetCommand( HE_IC_LEFT_IN_OP, false );
						pIO_Control->SetCommand( HE_IC_RIGHT_OUT_OP, false );
						pIO_Control->SetCommand( HE_ISOL_A_CTR_OP, false );
						pIO_Control->SetCommand( HE_ISOL_A_LEFT_OP, false );
						pIO_Control->SetCommand( HE_ISOL_A_RIGHT_OP, false );
						pIO_Control->SetCommand( HE_ISOL_B_CTR_OP, false );
						pIO_Control->SetCommand( HE_ISOL_B_LEFT_OP, false );
						pIO_Control->SetCommand( HE_ISOL_B_RIGHT_OP, false );
						// move SSMEs to entry config
						pMPS_ATVC_CMD_SOP->SetSSMEActPos( 0, ENTRYSTOWCONFIG_1P, ENTRYSTOWCONFIG_1Y );
						pMPS_ATVC_CMD_SOP->SetSSMEActPos( 1, ENTRYSTOWCONFIG_2P, ENTRYSTOWCONFIG_2Y );
						pMPS_ATVC_CMD_SOP->SetSSMEActPos( 2, ENTRYSTOWCONFIG_3P, ENTRYSTOWCONFIG_3Y );
						oapiWriteLogV( "MPS Dump Sequence complete @ MET %.2f", STS()->GetMET() );
					}

					// contingency LH2 vac inert
					if (((t_dump_start + HE_IC_CL_DELAY) < simt) && ((t_dump_start + FIRST_AUTOMATED_VACUUM_INERT_START_DELAY) > simt))
					{
						if (((STS()->GetLH2ManifPress() > 60) && (STS()->GetLH2ManifPress() < 90)) && (ReadCOMPOOL_IS( SCP_MPS_BACKUP_LH2_PRPLT_DUMP_START ) == 0))// overpressure and sw not in open
						{
							pIO_Control->SetCommand( LH2_OTBD_FD_VLV_CL, false );
							pIO_Control->SetCommand( LH2_OTBD_FD_VLV_OP, true );
							pIO_Control->SetCommand( LH2_TOPPING_VLV_OP, true );
							oapiWriteLogV( "Contingency LH2 Vacuum Inert start @ MET %.2f", STS()->GetMET() );
						}
					}

					// vac inert 1 start
					if (((t_dump_start + FIRST_AUTOMATED_VACUUM_INERT_START_DELAY) <= simt) && ((t_dump_start + FIRST_AUTOMATED_VACUUM_INERT_START_DELAY) > t_last))
					{
						pIO_Control->SetCommand( LOX_OTBD_FD_VLV_CL, false );
						pIO_Control->SetCommand( LOX_OTBD_FD_VLV_OP, true );
						pIO_Control->SetCommand( LOX_INBD_FD_VLV_CL, false );
						pIO_Control->SetCommand( LOX_INBD_FD_VLV_OP, true );
						pIO_Control->SetCommand( LH2_INBD_BU_DV_OP, true );
						pIO_Control->SetCommand( LH2_OTBD_BU_DV_OP, true );
						oapiWriteLogV( "Automated Vacuum Inert 1 start @ MET %.2f", STS()->GetMET() );
					}

					// vac inert 1 end
					if (((t_dump_start + FIRST_AUTOMATED_VACUUM_INERT_START_DELAY + FIRST_AUTOMATED_VACUUM_INERT_DURATION) <= simt) && ((t_dump_start + FIRST_AUTOMATED_VACUUM_INERT_START_DELAY + FIRST_AUTOMATED_VACUUM_INERT_DURATION) > t_last))
					{
						pIO_Control->SetCommand( LOX_OTBD_FD_VLV_CL, true );
						pIO_Control->SetCommand( LOX_OTBD_FD_VLV_OP, false );
						pIO_Control->SetCommand( LOX_INBD_FD_VLV_OP, false );
						pIO_Control->SetCommand( LH2_INBD_BU_DV_OP, false );
						pIO_Control->SetCommand( LH2_OTBD_BU_DV_OP, false );
						// PV11 and PV13 close now if opened in the contingency LH2 vac inert
						pIO_Control->SetCommand( LH2_OTBD_FD_VLV_CL, true );
						pIO_Control->SetCommand( LH2_OTBD_FD_VLV_OP, false );
						pIO_Control->SetCommand( LH2_TOPPING_VLV_OP, false );
						oapiWriteLogV( "Automated Vacuum Inert 1 complete @ MET %.2f", STS()->GetMET() );
					}

					if (MM106_trans == true)
					{
						// vac inert 2 start
						if (((t_MM106_trans + SECOND_AUTOMATED_VACUUM_INERT_START_DELAY) < simt) && ((t_MM106_trans + SECOND_AUTOMATED_VACUUM_INERT_START_DELAY) >= t_last))
						{
							pIO_Control->SetCommand( LH2_INBD_BU_DV_OP, true );
							pIO_Control->SetCommand( LH2_OTBD_BU_DV_OP, true );
							oapiWriteLogV( "Automated Vacuum Inert 2 start @ MET %.2f", STS()->GetMET() );
						}

						// vac inert 2 end
						if (((t_MM106_trans + SECOND_AUTOMATED_VACUUM_INERT_START_DELAY + SECOND_AUTOMATED_VACUUM_INERT_DURATION) <= simt) && ((t_MM106_trans + SECOND_AUTOMATED_VACUUM_INERT_START_DELAY + SECOND_AUTOMATED_VACUUM_INERT_DURATION) > t_last))
						{
							pIO_Control->SetCommand( LH2_INBD_BU_DV_OP, false );
							pIO_Control->SetCommand( LH2_OTBD_BU_DV_OP, false );
							oapiWriteLogV( "Automated Vacuum Inert 2 complete @ MET %.2f", STS()->GetMET() );
						}
					}
				}
				t_last = simt;
			}
		}
		return;
	}

	void MPS_Dump::Realize( void )
	{
		pSSME_SOP = dynamic_cast<SSME_SOP*> (FindSoftware( "SSME_SOP" ));
		assert( (pSSME_SOP != NULL) && "MPS_Dump::Realize.pSSME_SOP" );
		pSSME_Operations = dynamic_cast<SSME_Operations*> (FindSoftware( "SSME_Operations" ));
		assert( (pSSME_Operations != NULL) && "MPS_Dump::Realize.pSSME_Operations" );
		pIO_Control = dynamic_cast<IO_Control*> (FindSoftware( "IO_Control" ));
		assert( (pIO_Control != NULL) && "MPS_Dump::Realize.pIO_Control" );
		pMPS_ATVC_CMD_SOP = dynamic_cast<MPS_ATVC_CMD_SOP*> (FindSoftware( "MPS_ATVC_CMD_SOP" ));
		assert( (pMPS_ATVC_CMD_SOP != NULL) && "MPS_Dump::Realize.pMPS_ATVC_CMD_SOP" );
		return;
	}

	bool MPS_Dump::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 106:
				if (GetMajorMode() == 105)
				{
					MM106_trans = true;
					t_MM106_trans = t_last;
				}
			case 103:
			case 104:
			case 105:
			case 601:
			case 602:
			case 603:
				return true;
			default:
				return false;
		}
	}
}
/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/04/01   GLS
2020/04/07   GLS
2020/04/28   GLS
2020/06/20   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/01/15   GLS
2022/05/29   GLS
2022/08/05   GLS
2022/08/15   GLS
2022/09/29   GLS
2022/10/03   GLS
2022/12/23   GLS
2026/09/18   GLS
********************************************/
#include "ETSepSequence.h"
#include "../../../Atlantis.h"


namespace dps
{
	// K-Loads (not in correct format)
	constexpr double ET_SEP_ROLL_RATE_LIMIT = 0.7;// deg/sec
	constexpr double ET_SEP_PITCH_RATE_LIMIT = 0.7;// deg/sec
	constexpr double ET_SEP_YAW_RATE_LIMIT = 0.7;// deg/sec


	// HACK little info on the time sequence
	constexpr double ET_SEP_DELAY_MECO = 18;// sec
	constexpr double ET_SEP_CLOSE_PD = 8;// sec
	constexpr double ET_SEP_OPEN_SOV = 8;// sec
	constexpr double ET_SEP_SSME_STOW = 8;// sec
	constexpr double ET_SEP_ARM_SEP_PIC = 9.5;// sec
	constexpr double ET_SEP_DELAY_MINUSZ = 0.16;// sec


	ETSepSequence::ETSepSequence( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "ETSepSequence" )
	{
		active = false;
		autoETSEP = false;

		t_MECO = -1;
		t_last = -1;
		timerSEP = -1;

		{// TODO fix IO
			DiscreteBundle* bundle = BundleManager()->CreateBundle( "MPS_LV_C", 16 );
			PD1_OP.Connect( bundle, 13 );
			PD1_CL.Connect( bundle, 14 );
			PD2_OP.Connect( bundle, 15 );

			bundle = BundleManager()->CreateBundle( "MPS_LV_D", 16 );
			PD2_CL.Connect( bundle, 0 );
			PD3_OP.Connect( bundle, 1 );
			PD3_CL.Connect( bundle, 2 );
			// TODO do unlock valves

			bundle = BundleManager()->CreateBundle( "MPS_CLInd_A", 16 );
			PD1_CL_Ind_A.Connect( bundle, 13 );
			PD1_CL_Ind_B.Connect( bundle, 14 );
			PD2_CL_Ind_A.Connect( bundle, 15 );

			bundle = BundleManager()->CreateBundle( "MPS_CLInd_B", 16 );
			PD2_CL_Ind_B.Connect( bundle, 0 );
			PD3_CL_Ind.Connect( bundle, 7 );
		}
		return;
	}

	ETSepSequence::~ETSepSequence( void )
	{
		return;
	}

	void ETSepSequence::OnPostStep( double simt, double simdt, double mjd )
	{
		if (active == true)
		{
			if (ReadCOMPOOL_IS( SCP_ET_SEPARATION_MANUAL_ENABLE_CMD ) != 0)
			{
				if (ReadCOMPOOL_IS( SCP_ET_SEPARATION_INITIATE_CMD ) != 0)
				{
					if (ReadCOMPOOL_IS( SCP_ET_SEP_CMD ) == 0)
					{
						oapiWriteLog( "MAN ET SEP" );
					}
					WriteCOMPOOL_IS( SCP_ET_SEP_CMD, 1 );
				}
			}
			else
			{
				if (((t_MECO + ET_SEP_DELAY_MECO) <= simt) && ((t_MECO + ET_SEP_DELAY_MECO) > t_last))
				{
					autoETSEP = true;
				}
			}

			if (((t_MECO + ET_SEP_CLOSE_PD) <= simt) && ((t_MECO + ET_SEP_CLOSE_PD) > t_last))
			{
				// close feedline valves
				PD1_OP.ResetLine();
				PD1_CL.SetLine();
				PD2_OP.ResetLine();
				PD2_CL.SetLine();
				PD3_OP.ResetLine();
				PD3_CL.SetLine();
			}

			if (((t_MECO + ET_SEP_OPEN_SOV) <= simt) && ((t_MECO + ET_SEP_OPEN_SOV) > t_last))
			{
				// open feedline relief SOVs
				WriteCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA ) & ~0x0200 );// LO2 CL A
				WriteCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA ) & ~0x0200 );// LO2 CL B
				WriteCOMPOOL_IS( SCP_FA3_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA3_IOM12_CH0_DATA ) & ~0x0008 );// LO2 CL C
				WriteCOMPOOL_IS( SCP_FA3_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA3_IOM15_CH0_DATA ) & ~0x0200 );// LH2 CL A
				WriteCOMPOOL_IS( SCP_FA4_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM15_CH0_DATA ) & ~0x0200 );// LH2 CL B
				WriteCOMPOOL_IS( SCP_FA1_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM12_CH0_DATA ) & ~0x0008 );// LH2 CL C
			}

			if (((t_MECO + ET_SEP_SSME_STOW) <= simt) && ((t_MECO + ET_SEP_SSME_STOW) > t_last))
			{
				// SSME dump repo
				WriteCOMPOOL_IS( SCP_MPS_DUMP_GIMBAL_POS_FLAG, 1 );
			}

			if (((t_MECO + ET_SEP_ARM_SEP_PIC) <= simt) && ((t_MECO + ET_SEP_ARM_SEP_PIC) > t_last))
			{
				// arm sep PICs
				WriteCOMPOOL_IS( SCP_ET_SEP_ARM, 1 );
			}

			// TODO THC move stops auto sep

			if ((autoETSEP == true) && (ReadCOMPOOL_IS( SCP_ET_SEP_CMD ) == 0))
			{
				// TODO check feedline valves retracted
				// TODO check MDMs FA2, FA3, FA4
				VECTOR3 angvel;
				STS()->GetAngularVel( angvel );
				angvel *= DEG;

				if ((fabs( angvel.z ) <= ET_SEP_ROLL_RATE_LIMIT) && // check rates
					(fabs( angvel.x ) <= ET_SEP_PITCH_RATE_LIMIT) &&
					(fabs( angvel.y ) <= ET_SEP_YAW_RATE_LIMIT) &&
					(PD1_CL_Ind_A.IsSet() == true) && // check feedline valves closed
					(PD1_CL_Ind_B.IsSet() == true) &&
					(PD2_CL_Ind_A.IsSet() == true) &&
					(PD2_CL_Ind_B.IsSet() == true) &&
					(PD3_CL_Ind.IsSet() == true))
				{
					WriteCOMPOOL_IS( SCP_ET_SEP_CMD, 1 );

					// remove power from LVs
					PD1_CL.ResetLine();
					PD2_CL.ResetLine();
					PD3_CL.ResetLine();
				}
				else
				{
					WriteCOMPOOL_IS( SCP_ET_AUTO_SEP_INHIBIT_CREW_ALERT, 1 );
				}
			}

			if (ReadCOMPOOL_IS( SCP_ET_SEP_CMD ) == 1)
			{
				if (timerSEP == -1)// first run
				{
					// -Z translation cmd
					WriteCOMPOOL_IS( SCP_SEP_MINUSZ_CMD, 1 );
					timerSEP = simt + ET_SEP_DELAY_MINUSZ;
				}
				else if (((timerSEP + ET_SEP_DELAY_MINUSZ) <= simt) && ((timerSEP + ET_SEP_DELAY_MINUSZ) > t_last))
				//else if (timerSEP <= SimT)
				{
					// sep cmd
					WriteCOMPOOL_IS( SCP_ET_SEP_FIRE1, 1 );
					WriteCOMPOOL_IS( SCP_ET_SEP_FIRE23, 1 );
					WriteCOMPOOL_IS( SCP_ET_AUTO_SEP_INHIBIT_CREW_ALERT, 0 );

					oapiWriteLogV( "ET SEP @ MET %.2f", STS()->GetMET() );
				}
				else if (((timerSEP + 0.5) <= simt) && ((timerSEP + 0.5) > t_last))// HACK using 0.5 but apparently it should be 23 seconds
				{
					WriteCOMPOOL_IS( SCP_M_RSET_USER, 1 );
					CANCEL( this->GetIdentifier() );
				}
			}

			t_last = simt;
		}
		else
		{
			if (ReadCOMPOOL_IS( SCP_MECO_CONFIRMED ) == 1)
			{
				t_MECO = simt;
				active = true;
			}
		}
		return;
	}
}

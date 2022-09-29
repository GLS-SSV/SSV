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
2022/09/29   GLS
********************************************/
#include "ETSepSequence.h"
#include "../Atlantis.h"
#include "SSME_Operations.h"
#include "TransitionDAP.h"
#include "IO_Control.h"
#include "MPS_ATVC_CMD_SOP.h"
#include "MEC_SOP.h"
#include <cassert>


namespace dps
{
	// HACK little info on the time sequence
	constexpr double ET_SEP_DELAY_MECO = 18;// sec
	constexpr double ET_SEP_CLOSE_PD = 8;// sec
	constexpr double ET_SEP_OPEN_SOV = 8;// sec
	constexpr double ET_SEP_SSME_STOW = 8;// sec
	constexpr double ET_SEP_ARM_SEP_PIC = 9.5;// sec
	constexpr double ET_SEP_DELAY_MINUSZ = 0.16;// sec
	constexpr double ET_SEP_ROLL_RATE_LIMIT = 0.7;// deg/sec (I-load)
	constexpr double ET_SEP_PITCH_RATE_LIMIT = 0.7;// deg/sec (I-load)
	constexpr double ET_SEP_YAW_RATE_LIMIT = 0.7;// deg/sec (I-load)


	ETSepSequence::ETSepSequence( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "ETSepSequence" )
	{
		active = false;
		done = false;
		autoETSEP = false;
		ETSEPCommand = false;
		ETSEPINH = false;

		t_MECO = -1;
		t_last = -1;
		timerSEP = -1;
		return;
	}

	ETSepSequence::~ETSepSequence( void )
	{
		return;
	}

	void ETSepSequence::OnPostStep( double simt, double simdt, double mjd )
	{
		if (done == true) return;

		if (active == true)
		{
			if (ReadCOMPOOL_IS( SCP_ET_SEPARATION_MANUAL_ENABLE_CMD ) != 0)
			{
				if (ReadCOMPOOL_IS( SCP_ET_SEPARATION_INITIATE_CMD ) != 0)
				{
					if (ETSEPCommand == false)
					{
						oapiWriteLog( "MAN ET SEP" );
					}
					ETSEPCommand = true;
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
				pIO_Control->SetCommand( LO2_FEEDLINE_RLF_ISOL_CL, false );
				pIO_Control->SetCommand( LH2_FEEDLINE_RLF_ISOL_CL, false );
			}

			if (((t_MECO + ET_SEP_SSME_STOW) <= simt) && ((t_MECO + ET_SEP_SSME_STOW) > t_last))
			{
				// SSME dump repo
				pMPS_ATVC_CMD_SOP->SetSSMEActPos( 0, MPSDUMPCONFIG_1P, MPSDUMPCONFIG_1Y );
				pMPS_ATVC_CMD_SOP->SetSSMEActPos( 1, MPSDUMPCONFIG_2P, MPSDUMPCONFIG_2Y );
				pMPS_ATVC_CMD_SOP->SetSSMEActPos( 2, MPSDUMPCONFIG_3P, MPSDUMPCONFIG_3Y );
			}

			if (((t_MECO + ET_SEP_ARM_SEP_PIC) <= simt) && ((t_MECO + ET_SEP_ARM_SEP_PIC) > t_last))
			{
				// arm sep PICs
				pMEC_SOP->SetETSepSequencerFlag( MECSOP_ETSEP_ETORB_STR_SEPN_PICS_ARM );
			}

			// TODO THC move stops auto sep

			if ((autoETSEP == true) && (ETSEPCommand == false))
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
					ETSEPCommand = true;

					// remove power from LVs
					PD1_CL.ResetLine();
					PD2_CL.ResetLine();
					PD3_CL.ResetLine();
				}
				else
				{
					// TODO C&W msg
					ETSEPINH = true;
					//sprintf_s( oapiDebugString(), 256, "SEP INH" );
				}
			}

			if (ETSEPCommand == true)
			{
				if (timerSEP == -1)// first run
				{
					// -Z translation cmd
					pTransitionDAP->MinusZTranslationCommand();
					timerSEP = simt + ET_SEP_DELAY_MINUSZ;
				}
				else if (((timerSEP + ET_SEP_DELAY_MINUSZ) <= simt) && ((timerSEP + ET_SEP_DELAY_MINUSZ) > t_last))
				//else if (timerSEP <= SimT)
				{
					// sep cmd
					pMEC_SOP->SetETSepSequencerFlag( MECSOP_ETSEP_ETORB_STR_SEPN_FIRE_1 );
					pMEC_SOP->SetETSepSequencerFlag( MECSOP_ETSEP_ETORB_STR_SEPN_FIRE_2 );
					ETSEPINH = false;

					oapiWriteLogV( "ET SEP @ MET %.2f", STS()->GetMET() );
				}
				else if (((timerSEP + 0.5) <= simt) && ((timerSEP + 0.5) > t_last))// HACK using 0.5 but apparently it should be 23 seconds
				{
					pMEC_SOP->SetMECMasterResetFlag();
					done = true;
				}
			}

			t_last = simt;
		}
		else
		{
			if (pSSME_Operations->GetMECOConfirmedFlag() == true)
			{
				t_MECO = simt;
				active = true;
			}
		}
		return;
	}

	void ETSepSequence::Realize( void )
	{
		pSSME_Operations = dynamic_cast<SSME_Operations*> (FindSoftware( "SSME_Operations" ));
		assert( (pSSME_Operations != NULL) && "ETSepSequence::Realize.pSSME_Operations" );
		pTransitionDAP = dynamic_cast<TransitionDAP*> (FindSoftware( "TransitionDAP" ));
		assert( (pTransitionDAP != NULL) && "ETSepSequence::Realize.pTransitionDAP" );
		pIO_Control = dynamic_cast<IO_Control*> (FindSoftware( "IO_Control" ));
		assert( (pIO_Control != NULL) && "ETSepSequence::Realize.pIO_Control" );
		pMPS_ATVC_CMD_SOP = dynamic_cast<MPS_ATVC_CMD_SOP*> (FindSoftware( "MPS_ATVC_CMD_SOP" ));
		assert( (pMPS_ATVC_CMD_SOP != NULL) && "ETSepSequence::Realize.pMPS_ATVC_CMD_SOP" );
		pMEC_SOP = dynamic_cast<MEC_SOP*> (FindSoftware( "MEC_SOP" ));
		assert( (pMEC_SOP != NULL) && "ETSepSequence::Realize.pMEC_SOP" );


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
		return;
	}

	bool ETSepSequence::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			//case 102:
			case 103:
			case 104:
			case 601:
				return true;
			default:
				return false;
		}
	}

	bool ETSepSequence::GetETSEPINHFlag( void ) const
	{
		return ETSEPINH;
	}

	bool ETSepSequence::GetETSEPCommandFlag( void ) const
	{
		return ETSEPCommand;
	}
}
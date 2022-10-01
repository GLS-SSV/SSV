/******* SSV File Modification Notice *******
Date         Developer
2020/04/07   GLS
2020/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/03/29   GLS
2022/03/30   GLS
2022/04/20   GLS
2022/04/26   GLS
2022/05/29   GLS
2022/08/05   GLS
2022/08/15   GLS
********************************************/
#include "SRBSepSequence.h"
#include "..\Atlantis.h"
#include "AscentDAP.h"
#include "MEC_SOP.h"


namespace dps
{
	constexpr double SRB_SEP_SEQUENCE_START_TIME = 100.0;// sec


	SRBSepSequence::SRBSepSequence( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "SRBSepSequence" )
	{
		Active = false;

		SRBSeparationCmd = false;
		LHRHSRBPC50PSI = false;
		SRBSeparationInitiation = false;
		SRBAutoSepInhibitCrewAlert = false;

		firstpass_step2 = true;
		firstpass_step4_A = true;
		firstpass_step4_B = true;

		SRBSepModingTimeDelayTimer = -1.0;
		SRBSepCmdTimeDelayTimer = -1.0;
		SepCmdTimer = -1.0;

		LHPC50time = -1.0;
		RHPC50time = -1.0;
		timeSRBSEPinit = -1;

		// I-LOADs init
		BP_ROLL_RATE_LMT_CONSTANT = 99999;
		BQ_PITCH_RATE_LMT_CONSTANT = 99999;
		BR_YAW_RATE_LMT_CONSTANT = 99999;
		DYNAMIC_PRS_LMT = 99999;
		SRB_SEP_BACKUP_CUE_T = 131.28;
		SRB_SEP_MODING_T_DELAY = 3.2;
		SRB_SEP_COMMAND_T_DELAY = 4.9;
		MAX_SRB_SEP_CUE_DIFRNTL = 5.5;
		return;
	}

	SRBSepSequence::~SRBSepSequence( void )
	{
		return;
	}

	void SRBSepSequence::OnPostStep( double simt, double simdt, double mjd )
	{
		if (!Active) return;
		if (STS()->GetMET() < SRB_SEP_SEQUENCE_START_TIME) return;

		/*
		Steps from JSC-16936.
		Changes from diagram:
			- updated I-LOAD times from JSC-10559
			- added SRB_SEP_SEQUENCE_START_TIME check
			- added MECO Confirmed check to step 4
		*/

	//step1:
		if (SRBSeparationCmd) goto step4;
		else if (SRBSeparationInitiation) goto step2;
		else
		{
			// TODO get middle value of the 3 sensors
			// TODO detect drop below 50
			double LHPC = STS()->GetSRBChamberPressure();// HACK same value for both
			if ((LHPC < 50.0) && (LHPC50time == -1.0)) LHPC50time = simt;

			double RHPC = STS()->GetSRBChamberPressure();// HACK same value for both
			if ((RHPC < 50.0) && (RHPC50time == -1.0)) RHPC50time = simt;

			if ((LHPC50time > 0.0) && (RHPC50time > 0.0))
			{
				double dt = fabs( LHPC50time - RHPC50time );
				if (dt <= MAX_SRB_SEP_CUE_DIFRNTL)
				{
					LHRHSRBPC50PSI = true;
					goto step2;
				}
			}
		}

		if (STS()->GetMET() > SRB_SEP_BACKUP_CUE_T) goto step2;
		return;

	step2:
		// TODO set:
		// srb rss safe flag
		// srb rss pwr off flag
		// et/orb sep cameras on cmd
		SRBSeparationInitiation = true;

		if (firstpass_step2)
		{
			firstpass_step2 = false;
			SRBSepModingTimeDelayTimer = simt + SRB_SEP_MODING_T_DELAY;
			SRBSepCmdTimeDelayTimer = simt + SRB_SEP_COMMAND_T_DELAY;
		}

		if (simt >= SRBSepModingTimeDelayTimer)
		{
			// TODO set srb sep function moding flag
			pAscentDAP->NullSRBNozzles();// is this the moding flag?
			pMEC_SOP->SetSRBSepSequencerFlag( MECSOP_SRBSEP_SRB_SEP_PICS_ARM );

			if (simt >= SRBSepCmdTimeDelayTimer)
			{
				// TODO set:
				// atvc srb 26v deadface flag
				// atvc srb ivd pwr on false
				goto step3;
			}
		}
		return;

	step3:
		SRBAutoSepInhibitCrewAlert = false;

		if (ReadCOMPOOL_IS( SCP_SRB_SEPARATION_MANUAL_AUTO_ENABLE_CMD ) != 0)
		{
			if (ReadCOMPOOL_IS( SCP_SRB_SEPARATION_INITIATE_CMD ) != 0) goto step4;
		}

		VECTOR3 angvel;
		STS()->GetAngularVel( angvel );
		angvel *= DEG;
		if ((fabs( angvel.z ) < BP_ROLL_RATE_LMT_CONSTANT) && // check rates
			(fabs( angvel.x ) < BQ_PITCH_RATE_LMT_CONSTANT) &&
			(fabs( angvel.y ) < BR_YAW_RATE_LMT_CONSTANT) &&
			((STS()->GetDynPressure() * 0.020885434272991) < DYNAMIC_PRS_LMT))// check qbar
			goto step4;

		SRBAutoSepInhibitCrewAlert = true;
		return;

	step4:
		if (ReadCOMPOOL_IS( SCP_MECO_CONFIRMED ) == 0)
		{
			pMEC_SOP->SetSRBSepSequencerFlag( MECSOP_SRBSEP_SRB_SEP_FIRE_1 );
			pMEC_SOP->SetSRBSepSequencerFlag( MECSOP_SRBSEP_SRB_SEP_FIRE_2 );
			SRBSeparationCmd = true;

			if (firstpass_step4_A)
			{
				firstpass_step4_A = false;
				SepCmdTimer = simt;
				SetMajorMode( 103 );// HACK not here but is should be at this time. probably related to SRBSeparationCmd
			}

			if ((simt - SepCmdTimer) >= 4.0)
			{
				// TODO set false:
				// srb sep fire 1 & 2 flags
				// srb pwr on
				// l & r srb pwr bus c rpc's b & c
				// srb rss pwr off flag
				// srb rss safe flag
				// srb sep pics arm flag
				// et/orb sep cam on cmd

				if (firstpass_step4_B)
				{
					firstpass_step4_B = false;
					return;
				}

				pMEC_SOP->SetMECMasterResetFlag();
				Active = false;
				return;
			}
		}
		return;
	}

	void SRBSepSequence::Realize( void )
	{
		pAscentDAP = dynamic_cast<AscentDAP*> (FindSoftware( "AscentDAP" ));
		assert( (pAscentDAP != NULL) && "SRBSepSequence::Realize.pAscentDAP" );
		pMEC_SOP = dynamic_cast<MEC_SOP*> (FindSoftware( "MEC_SOP" ));
		assert( (pMEC_SOP != NULL) && "SRBSepSequence::Realize.pMEC_SOP" );
		return;
	}

	void SRBSepSequence::ReadILOADs( const std::map<std::string,std::string>& ILOADs )
	{
		GetValILOAD( "BP_ROLL_RATE_LMT_CONSTANT", ILOADs, BP_ROLL_RATE_LMT_CONSTANT );
		GetValILOAD( "BQ_PITCH_RATE_LMT_CONSTANT", ILOADs, BQ_PITCH_RATE_LMT_CONSTANT );
		GetValILOAD( "BR_YAW_RATE_LMT_CONSTANT", ILOADs, BR_YAW_RATE_LMT_CONSTANT );
		GetValILOAD( "DYNAMIC_PRS_LMT", ILOADs, DYNAMIC_PRS_LMT );
		GetValILOAD( "SRB_SEP_BACKUP_CUE_T", ILOADs, SRB_SEP_BACKUP_CUE_T );
		GetValILOAD( "SRB_SEP_MODING_T_DELAY", ILOADs, SRB_SEP_MODING_T_DELAY );
		GetValILOAD( "SRB_SEP_COMMAND_T_DELAY", ILOADs, SRB_SEP_COMMAND_T_DELAY );
		GetValILOAD( "MAX_SRB_SEP_CUE_DIFRNTL", ILOADs, MAX_SRB_SEP_CUE_DIFRNTL );
		return;
	}

	bool SRBSepSequence::OnMajorModeChange( unsigned int newMajorMode )
	{
		if (newMajorMode == 102)
		{
			Active = true;
			return true;
		}
		if (newMajorMode == 103) return true;
		else return false;
	}

	bool SRBSepSequence::GetLHRHSRBPC50PSIFlag( void ) const
	{
		return LHRHSRBPC50PSI;
	}

	bool SRBSepSequence::GetSRBAutoSepInhibitCrewAlertFlag( void ) const
	{
		return SRBAutoSepInhibitCrewAlert;
	}
}
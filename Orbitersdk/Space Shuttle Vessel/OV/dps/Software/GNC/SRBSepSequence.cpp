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
2022/09/29   GLS
2022/12/23   GLS
2025/07/20   GLS
2026/09/18   GLS
********************************************/
#include "SRBSepSequence.h"
#include "../../../Atlantis.h"


namespace dps
{
	SRBSepSequence::SRBSepSequence( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "SRBSepSequence" )
	{
		firstpass_step2 = true;
		firstpass_step4_A = true;
		firstpass_step4_B = true;

		SRBSepModingTimeDelayTimer = -1.0;
		SRBSepCmdTimeDelayTimer = -1.0;
		SepCmdTimer = -1.0;

		LHPC50time = -1.0;
		RHPC50time = -1.0;
		timeSRBSEPinit = -1;
		return;
	}

	SRBSepSequence::~SRBSepSequence( void )
	{
		return;
	}

	void SRBSepSequence::OnPostStep( double simt, double simdt, double mjd )
	{
		/*
		Steps from JSC-16936.
		Changes from diagram:
			- updated I-LOAD times from JSC-10559
			- added MECO Confirmed check to step 4
		*/

	//step1:
		if (ReadCOMPOOL_IS( SCP_SRB_SEP_CMD_FLAG ) == 1) goto step4;
		else if (ReadCOMPOOL_IS( SCP_SRB_SEP_INITIATION ) == 1) goto step2;
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
				if (dt <= ReadCOMPOOL_SD( SCP_MAX_SRB_SEP_CUE_DIFRNTL ))
				{
					WriteCOMPOOL_IS( SCP_LH_RH_SRB_PC_50_PSI_FLAG, 1 );
					goto step2;
				}
			}
		}

		if (STS()->GetMET() > ReadCOMPOOL_SD( SCP_SRB_SEP_BACKUP_CUE_T )) goto step2;
		return;

	step2:
		// TODO set:
		// srb rss safe flag
		// srb rss pwr off flag
		// et/orb sep cameras on cmd
		WriteCOMPOOL_IS( SCP_SRB_SEP_INITIATION, 1 );

		if (firstpass_step2)
		{
			firstpass_step2 = false;
			SRBSepModingTimeDelayTimer = simt + ReadCOMPOOL_SD( SCP_SRB_SEP_MODING_T_DELAY );
			SRBSepCmdTimeDelayTimer = simt + ReadCOMPOOL_SD( SCP_SRB_SEP_COMMAND_T_DELAY );
		}

		if (simt >= SRBSepModingTimeDelayTimer)
		{
			WriteCOMPOOL_IS( SCP_SRB_MODING_SEP, 1 );
			WriteCOMPOOL_IS( SCP_SRB_SEP_ARM, 1 );

			if (simt >= SRBSepCmdTimeDelayTimer)
			{
				WriteCOMPOOL_IS( SCP_ATVC_26V_DDFACE, 1 );
				WriteCOMPOOL_IS( SCP_ATVC_IVD_PWR, 0 );
				goto step3;
			}
		}
		return;

	step3:
		WriteCOMPOOL_IS( SCP_SRB_AUTO_SEP_INHIBIT_CREW_ALERT, 0 );

		if (ReadCOMPOOL_IS( SCP_SRB_SEPARATION_MANUAL_AUTO_ENABLE_CMD ) != 0)
		{
			if (ReadCOMPOOL_IS( SCP_SRB_SEPARATION_INITIATE_CMD ) != 0) goto step4;
		}

		VECTOR3 angvel;
		STS()->GetAngularVel( angvel );
		angvel *= DEG;
		if ((fabs( angvel.z ) < ReadCOMPOOL_SS( SCP_BP_ROLL_RATE_LMT_CONSTANT )) && // check rates
			(fabs( angvel.x ) < ReadCOMPOOL_SS( SCP_BQ_PITCH_RATE_LMT_CONSTANT )) &&
			(fabs( angvel.y ) < ReadCOMPOOL_SS( SCP_BR_YAW_RATE_LMT_CONSTANT )) &&
			((STS()->GetDynPressure() * 0.020885434272991) < ReadCOMPOOL_SS( SCP_DYNAMIC_PRS_LMT )))// check qbar
			goto step4;

		WriteCOMPOOL_IS( SCP_SRB_AUTO_SEP_INHIBIT_CREW_ALERT, 1 );
		return;

	step4:
		if (ReadCOMPOOL_IS( SCP_MECO_CONFIRMED ) == 0)
		{
			WriteCOMPOOL_IS( SCP_SRB_SEP_CMD_FLAG, 1 );
			WriteCOMPOOL_IS( SCP_SRB_SEP_FIRE1, 1 );
			WriteCOMPOOL_IS( SCP_SRB_SEP_FIRE23, 1 );

			if (firstpass_step4_A)
			{
				firstpass_step4_A = false;
				SepCmdTimer = simt;
			}

			if ((simt - SepCmdTimer) >= 4.0)
			{
				// TODO set false:
				// srb pwr on
				// l & r srb pwr bus c rpc's b & c
				// et/orb sep cam on cmd
				WriteCOMPOOL_IS( SCP_SRB_SEP_FIRE1, 0 );
				WriteCOMPOOL_IS( SCP_SRB_SEP_FIRE23, 0 );
				WriteCOMPOOL_IS( SCP_SRB_RSS_OFF, 0 );
				WriteCOMPOOL_IS( SCP_SRB_RSS_SAFE, 0 );
				WriteCOMPOOL_IS( SCP_SRB_SEP_ARM, 0 );

				if (firstpass_step4_B)
				{
					firstpass_step4_B = false;
					return;
				}

				WriteCOMPOOL_IS( SCP_SRB_SEP_ARM, 0 );
				WriteCOMPOOL_IS( SCP_M_RSET_USER, 1 );
				CANCEL( this->GetIdentifier() );
				return;
			}
		}
		return;
	}
}

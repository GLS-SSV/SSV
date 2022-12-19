/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/04/07   GLS
2020/06/20   GLS
2020/06/28   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/03/29   GLS
2022/03/31   GLS
2022/04/26   GLS
2022/06/10   GLS
2022/06/23   GLS
2022/08/05   GLS
2022/08/15   GLS
2022/11/15   GLS
********************************************/
#include "SBTC_SOP.h"
#include "SBTC_RM.h"
#include "SSME_SOP.h"
#include <MathSSV.h>
#include <cassert>


namespace dps
{
	SBTC_SOP::SBTC_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "SBTC_SOP" )
	{
		MAN_THROTTLE = false;
		MAN_THROTTLE_ACTIVE = false;
		MAN_THROTTLE_COMMAND = 0.0;

		CDR_TAKEOVER = false;
		PLT_TAKEOVER = false;
		MAN_SPEEDBRAKE_COMMAND = 0.0;
		CDR_DATA = true;
		return;
	}

	SBTC_SOP::~SBTC_SOP( void )
	{
		return;
	}

	void SBTC_SOP::Realize( void )
	{
		pSBTC_RM = dynamic_cast<SBTC_RM*>(FindSoftware( "SBTC_RM" ));
		assert( (pSBTC_RM != NULL) && "SBTC_SOP::Realize.pSBTC_RM" );

		pSSME_SOP = dynamic_cast<SSME_SOP*>(FindSoftware( "SSME_SOP" ));
		assert( (pSSME_SOP != NULL) && "SBTC_SOP::Realize.pSSME_SOP" );
		return;
	}

	void SBTC_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		switch (GetMajorMode())
		{
			case 101:
				WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) | 0x0020 );
				WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) | 0x0020 );
				break;
			case 304:
			case 305:
			case 602:
			case 603:
			case 801:
				ManSpeedbrake();// man speedbrake
				break;
			default:
				if (ReadCOMPOOL_IS( SCP_MECO_CONFIRMED ) == 0) ManThrottle();// man throttle
				break;
		}
		return;
	}

	bool SBTC_SOP::OnParseLine( const char* keyword, const char* value )
	{
		if (!_strnicmp( keyword, "MAN_THROTTLE", 12 ))
		{
			if (!_strnicmp( value, "TRUE", 4 ))
			{
				MAN_THROTTLE = true;
				MAN_THROTTLE_ACTIVE = true;
			}
			else
			{
				MAN_THROTTLE = false;
				MAN_THROTTLE_ACTIVE = false;
			}
			return true;
		}
		else if (!_strnicmp( keyword, "DATA", 4 ))
		{
			if (!_strnicmp( value, "PLT", 3 )) CDR_DATA = false;
			else CDR_DATA = true;
			return true;
		}
		return false;
	}

	void SBTC_SOP::OnSaveState( FILEHANDLE scn ) const
	{
		if (MAN_THROTTLE_ACTIVE == true) oapiWriteScenario_string( scn, "MAN_THROTTLE", "TRUE" );
		if (CDR_DATA == false) oapiWriteScenario_string( scn, "DATA", "PLT" );
		return;
	}

	bool SBTC_SOP::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 101:
			case 102:
			case 103:
			case 304:
			case 305:
			case 601:
			case 602:
			case 603:
			case 801:
				return true;
			default:
				return false;
		}
	}

	void SBTC_SOP::ManSpeedbrake( void )
	{
		double L = 0.0;
		bool DG_L = false;
		bool TO_L = false;
		double R = 0.0;
		bool DG_R = false;
		bool TO_R = false;

		// get data from RM
		pSBTC_RM->GetSBTCData_L( L, DG_L, TO_L );
		pSBTC_RM->GetSBTCData_R( R, DG_R, TO_R );

		// TODO what to do when DG flag is false?

		// convert to degrees
		L = (1.0 - L) * 98.6;
		R = (1.0 - R) * 98.6;

		// AUTO/MAN speedbrake logic
		if (TO_L == true)
		{
			// CDR
			CDR_TAKEOVER = true;
			PLT_TAKEOVER = false;
			CDR_DATA = true;
		}
		else if (TO_R == true)
		{
			// PLT
			CDR_TAKEOVER = false;
			PLT_TAKEOVER = true;
			CDR_DATA = false;
		}
		else
		{
			CDR_TAKEOVER = false;
			PLT_TAKEOVER = false;
		}

		// data switch
		if (CDR_DATA == true) MAN_SPEEDBRAKE_COMMAND = L;
		else MAN_SPEEDBRAKE_COMMAND = R;
		return;
	}

	void SBTC_SOP::ManThrottle( void )
	{
		double R = 0.0;
		bool DG_R = false;
		bool TO_R = false;

		// get data from RM
		pSBTC_RM->GetSBTCData_R( R, DG_R, TO_R );

		// TODO what to do when DG flag is false?

		// convert to throttle percentage
		unsigned short KMIN = ReadCOMPOOL_IS( SCP_KMIN );
		unsigned short KMAX = ReadCOMPOOL_IS( SCP_KMAX );
		R = KMIN + (R * (KMAX - KMIN));

		// AUTO/MAN throttle logic
		if (MAN_THROTTLE == true)
		{
			if (MAN_THROTTLE_ACTIVE == true)
			{
				// full MAN control
				pSSME_SOP->SetThrottlePercent( Round( R ) );

				// check for AUTO
				unsigned short CDR_SPDBK_THROT = ReadCOMPOOL_IS( SCP_LH_SPD_BK_THROT_AUTO_MAN );
				unsigned short PLT_SPDBK_THROT = ReadCOMPOOL_IS( SCP_RH_SPD_BK_THROT_AUTO_MAN );
				if ((CDR_SPDBK_THROT == 1) || (PLT_SPDBK_THROT == 1))
				{
					MAN_THROTTLE = false;
					MAN_THROTTLE_ACTIVE = false;
				}
			}
			else
			{
				if (TO_R == true)
				{
					// check for 4% tolerance
					if (fabs( R - ReadCOMPOOL_IS( SCP_K_CMD ) ) < 4.0)
					{
						MAN_THROTTLE_ACTIVE = true;
						pSSME_SOP->SetThrottlePercent( Round( R ) );
					}
				}
				else
				{
					// back to AUTO
					MAN_THROTTLE = false;
				}
			}
		}
		else
		{
			// check for MAN
			if (TO_R == true)
			{
				MAN_THROTTLE = true;
			}
		}

		// DAP lights
		if (MAN_THROTTLE_ACTIVE)
		{
			// PLT MAN
			WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA ) | 0x0020 );
		}
		else
		{
			if (!MAN_THROTTLE)
			{
				// CDR/PLT AUTO
				WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) | 0x0020 );
				WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) | 0x0020 );
			}
		}
		return;
	}

	bool SBTC_SOP::GetManThrottle( void ) const
	{
		return MAN_THROTTLE;
	}

	double SBTC_SOP::GetManThrottleCommand( void ) const
	{
		return MAN_THROTTLE_COMMAND;
	}

	bool SBTC_SOP::GetCDRTakeover( void ) const
	{
		return CDR_TAKEOVER;
	}

	bool SBTC_SOP::GetPLTTakeover( void ) const
	{
		return PLT_TAKEOVER;
	}

	double SBTC_SOP::GetManSpeedbrakeCommand( void ) const
	{
		return MAN_SPEEDBRAKE_COMMAND;
	}
}
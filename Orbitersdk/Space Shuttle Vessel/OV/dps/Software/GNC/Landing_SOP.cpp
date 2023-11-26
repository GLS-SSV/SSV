/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/05/28   GLS
2020/06/20   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/05/29   GLS
2022/12/01   indy91
2023/09/03   GLS
2023/11/26   GLS
********************************************/
#include "Landing_SOP.h"
#include <cassert>


namespace dps
{
	// time delay between WOW and WONG
	const double T_WOW = 2.08;// [s]

	// theta condition for WONG
	const double ATT_WONG = 0.0;// [deg]


	Landing_SOP::Landing_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "Landing_SOP" )
	{
		WOWLON_timecounter = 0.0;

		WOWINITIATE = false;
		return;
	}

	Landing_SOP::~Landing_SOP( void )
	{
		return;
	}

	void Landing_SOP::OnPreStep( double simt, double simdt, double mjd )
	{
		if (ReadCOMPOOL_IS( SCP_TG_END ) == 0) return;// only run from A/L

		unsigned short FF2_IOM12_CH0 = ReadCOMPOOL_IS( SCP_FF2_IOM12_CH0_DATA );
		unsigned short FF2_IOM12_CH2 = ReadCOMPOOL_IS( SCP_FF2_IOM12_CH2_DATA );
		unsigned short FF3_IOM12_CH0 = ReadCOMPOOL_IS( SCP_FF3_IOM12_CH0_DATA );
		unsigned short FF3_IOM12_CH2 = ReadCOMPOOL_IS( SCP_FF3_IOM12_CH2_DATA );

		unsigned short LMG_NO_WOW = (FF2_IOM12_CH2 & 0x0200) >> 9;
		unsigned short RMG_NO_WOW = (FF3_IOM12_CH2 & 0x0200) >> 9;
		unsigned short NLG_NO_WOW_1 = (FF3_IOM12_CH0 & 0x2000) >> 13;
		unsigned short NLG_NO_WOW_2 = (FF2_IOM12_CH0 & 0x0800) >> 11;

		bool THETA = (ReadCOMPOOL_SS( SCP_THETA ) < ATT_WONG);
		bool WOWDELAY = (WOWLON_timecounter > T_WOW);
		WOWINITIATE = (ReadCOMPOOL_IS( SCP_ET_SEPARATION_INITIATE_CMD ) || ReadCOMPOOL_IS( SCP_SRB_SEPARATION_INITIATE_CMD )) || WOWINITIATE;

		if (ReadCOMPOOL_IS( SCP_WOWLON_IND ) == 0)
		{
			if (((LMG_NO_WOW == 0) && (RMG_NO_WOW == 0)) || WOWINITIATE)
			{
				WriteCOMPOOL_IS( SCP_HUD_WOWLON, 1 );
				WriteCOMPOOL_IS( SCP_FLATTURN_CMD, 1 );
				WriteCOMPOOL_IS( SCP_WOWLON_IND, 1 );
				WOWLON_timecounter = 0.0;
			}
		}
		else WOWLON_timecounter += simdt;

		if (ReadCOMPOOL_IS( SCP_ROLLOUT_IND ) == 0)
		{
			if ((((NLG_NO_WOW_1 == 0) && (NLG_NO_WOW_2 == 0)) || WOWINITIATE) && THETA && WOWDELAY)
			{
				WriteCOMPOOL_IS( SCP_HUD_ROLLOUT, 1 );
				WriteCOMPOOL_IS( SCP_GSENBL, 1 );
				WriteCOMPOOL_IS( SCP_ROLLOUT_IND, 1 );

				// HACK set pitch back to AUTO to signal GSENBL (move to AerojetDAP)
				WriteCOMPOOL_IS( SCP_AUTOP_IND, 1 );
				WriteCOMPOOL_IS( SCP_CSSP_IND, 0 );
			}
		}
		return;
	}

	bool Landing_SOP::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void Landing_SOP::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	bool Landing_SOP::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 305:
			case 603:
				return true;
			default:
				return false;
		}
	}
}
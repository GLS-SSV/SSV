/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/05/28   GLS
2020/06/20   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/05/29   GLS
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

	void Landing_SOP::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "LANDING_GEAR", 16 );
		dipNLG_NO_WOW.Connect( pBundle, 11 );
		dipLMG_NO_WOW.Connect( pBundle, 12 );
		dipRMG_NO_WOW.Connect( pBundle, 13 );
		return;
	}

	void Landing_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		if (ReadCOMPOOL_IS( SCP_TG_END ) == 0) return;// only run from A/L

		bool THETA = (ReadCOMPOOL_SD( SCP_THETA ) < ATT_WONG);
		bool WOWDELAY = (WOWLON_timecounter > T_WOW);
		WOWINITIATE = (ReadCOMPOOL_IS( SCP_ET_SEPARATION_INITIATE_CMD ) || ReadCOMPOOL_IS( SCP_SRB_SEPARATION_INITIATE_CMD )) || WOWINITIATE;

		if (ReadCOMPOOL_IS( SCP_WOWLON ) == 0)
		{
			if ((!dipLMG_NO_WOW.IsSet() && !dipRMG_NO_WOW.IsSet()) || WOWINITIATE)
			{
				WriteCOMPOOL_IS( SCP_HUD_WOWLON, 1 );
				WriteCOMPOOL_IS( SCP_FLATTURN, 1 );
				WriteCOMPOOL_IS( SCP_WOWLON, 1 );
				WOWLON_timecounter = 0.0;
			}
		}
		else WOWLON_timecounter += simdt;

		if (ReadCOMPOOL_IS( SCP_ROLLOUT ) == 0)
		{
			if ((!dipNLG_NO_WOW.IsSet() || WOWINITIATE) && THETA && WOWDELAY)
			{
				WriteCOMPOOL_IS( SCP_HUD_ROLLOUT, 1 );
				WriteCOMPOOL_IS( SCP_GSENBL, 1 );
				WriteCOMPOOL_IS( SCP_ROLLOUT, 1 );

				// set pitch back to AUTO to signal GSENBL
				WriteCOMPOOL_IS( SCP_AEROJET_FCS_PITCH, 1 );
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

	bool Landing_SOP::GetWOWLON( void ) const
	{
		return ReadCOMPOOL_IS( SCP_WOWLON ) == 1;// HACK temp only for IDP
	}
}
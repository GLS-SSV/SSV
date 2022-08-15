/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/06/18   GLS
2021/08/24   GLS
2022/08/05   GLS
********************************************/
#include "7SegDisp_MissionTime.h"
#include "..\dps\MasterTimingUnit.h"
#include "../Atlantis.h"


namespace vc
{
	_7SegDisp_MissionTime::_7SegDisp_MissionTime( Atlantis* _sts, const std::string& _ident ):_7SegDisp( _sts, _ident )
	{
		fwd = true;
	}

	_7SegDisp_MissionTime::~_7SegDisp_MissionTime()
	{
	}

	void _7SegDisp_MissionTime::SetLocation( bool fwd )
	{
		this->fwd = fwd;
		return;
	}

	void _7SegDisp_MissionTime::Realize( void )
	{
		DiscreteBundle* pBundle;
		if (fwd) pBundle = STS()->BundleManager()->CreateBundle( "O3_Timer_OMSRCS", 16 );
		else pBundle = STS()->BundleManager()->CreateBundle( "A4_Timer", 2 );
		pMissionTimerTEST.Connect( pBundle, 0 );
		pMissionTimerGMT.Connect( pBundle, 1 );
		return;
	}

	void _7SegDisp_MissionTime::Controller( void )
	{
		if (pMissionTimerGMT.IsSet())
		{
			short sGMTDays = STS()->MTU()->GetGMTDay( 0 );
			short sGMTHours = STS()->MTU()->GetGMTHour( 0 );
			short sGMTMinutes = STS()->MTU()->GetGMTMin( 0 );
			short sGMTSeconds = STS()->MTU()->GetGMTSec( 0 );

			next_state[8] = sGMTDays / 100;
			next_state[7] = (sGMTDays / 10) % 10;
			next_state[6] = sGMTDays % 10;
			next_state[5] = sGMTHours / 10;
			next_state[4] = sGMTHours % 10;
			next_state[3] = sGMTMinutes / 10;
			next_state[2] = sGMTMinutes % 10;
			next_state[1] = sGMTSeconds / 10;
			next_state[0] = sGMTSeconds % 10;
		}
		else if (pMissionTimerTEST.IsSet())
		{
			next_state[8] = 8;
			next_state[7] = 8;
			next_state[6] = 8;
			next_state[5] = 8;
			next_state[4] = 8;
			next_state[3] = 8;
			next_state[2] = 8;
			next_state[1] = 8;
			next_state[0] = 8;
		}
		else
		{
			short sMETDays = STS()->MTU()->GetMETDay( 0 );
			short sMETHours = STS()->MTU()->GetMETHour( 0 );
			short sMETMinutes = STS()->MTU()->GetMETMin( 0 );
			short sMETSeconds = STS()->MTU()->GetMETSec( 0 );

			next_state[8] = sMETDays / 100;
			next_state[7] = (sMETDays / 10) % 10;
			next_state[6] = sMETDays % 10;
			next_state[5] = sMETHours / 10;
			next_state[4] = sMETHours % 10;
			next_state[3] = sMETMinutes / 10;
			next_state[2] = sMETMinutes % 10;
			next_state[1] = sMETSeconds / 10;
			next_state[0] = sMETSeconds % 10;
		}
		return;
	}
};
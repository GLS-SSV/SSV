/******* SSV File Modification Notice *******
Date         Developer
2020/04/07   GLS
2020/04/08   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/06/06   GLS
2021/08/23   GLS
2021/08/24   GLS
********************************************/
#include "ATVC.h"
#include "..\MPS_TVC.h"
#include <cassert>


namespace gnc
{
	ATVC::ATVC( AtlantisSubsystemDirector* _director, const string& _ident, short nID ):AtlantisSubsystem( _director, _ident )
	{
		ID = nID;
		return;
	}

	ATVC::~ATVC( void )
	{
		return;
	}


	void ATVC::Realize( void )
	{
		DiscreteBundle* bundle = BundleManager()->CreateBundle( "ATVC_POWER", 4 );
		dipPower[0].Connect( bundle, 0 );
		dipPower[1].Connect( bundle, 1 );
		dipPower[2].Connect( bundle, 2 );
		dipPower[3].Connect( bundle, 3 );

		bundle = BundleManager()->CreateBundle( "ATVC", 10 );
		dipPpos[0].Connect( bundle, 0 );
		dipPpos[1].Connect( bundle, 1 );
		dipPpos[2].Connect( bundle, 2 );
		dipYpos[0].Connect( bundle, 3 );
		dipYpos[1].Connect( bundle, 4 );
		dipYpos[2].Connect( bundle, 5 );
		dipRpos[0].Connect( bundle, 6 );
		dipRpos[1].Connect( bundle, 7 );
		dipTpos[0].Connect( bundle, 8 );
		dipTpos[1].Connect( bundle, 9 );

		pMPS_TVC = dynamic_cast<MPS_TVC*>(director->GetSubsystemByName( "MPS_TVC" ));
		assert( (pMPS_TVC != NULL) && "ATVC::Realize.pMPS_TVC" );
		return;
	}

	void ATVC::OnPostStep( double simt, double simdt, double mjd )
	{
		if (!(dipPower[0].IsSet() || dipPower[1].IsSet() || dipPower[2].IsSet() || dipPower[3].IsSet())) return;// HACK at least one box on

		for (int i = 0; i < 3; i++)
		{
			pMPS_TVC->Command( i, dipPpos[i].GetVoltage(), dipYpos[i].GetVoltage() );
		}

		//STS()->SetSRBGimbalAngles( static_cast<SIDE> (0), pitchGimbal+rollGimbal, yawGimbal );
		//STS()->SetSRBGimbalAngles( static_cast<SIDE> (1), pitchGimbal+rollGimbal, yawGimbal );
		return;
	}
}
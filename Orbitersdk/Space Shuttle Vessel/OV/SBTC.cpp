/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/06/04   GLS
2022/08/05   GLS
2023/06/14   GLS
2023/11/11   GLS
********************************************/
#include "SBTC.h"
#include "Atlantis.h"
#include <cassert>


SBTC::SBTC( AtlantisSubsystemDirector* _director, const string& _ident, unsigned short ID ):AtlantisSubsystem( _director, _ident )
{
	assert( ((ID == 1) || (ID == 2)) && "SBTC::SBTC:ID" );
	this->ID = ID;
	return;
}

SBTC::~SBTC( void )
{
}

void SBTC::Realize( void )
{
	DiscreteBundle* pBundle;

	if (ID == 1)
	{
		// left
		pBundle = BundleManager()->CreateBundle( "MDM_FF1_IOM1_PLUS", 16 );
		dopSBTC[0].Connect( pBundle, 4 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF1_IOM6_CH0", 16 );
		dopSBTC[3].Connect( pBundle, 13 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF2_IOM1_PLUS", 16 );
		dopSBTC[1].Connect( pBundle, 4 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF2_IOM6_CH0", 16 );
		dopSBTC[4].Connect( pBundle, 13 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM1_PLUS", 16 );
		dopSBTC[2].Connect( pBundle, 4 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM6_CH0", 16 );
		dopSBTC[5].Connect( pBundle, 13 );
	}
	else
	{
		// right
		pBundle = BundleManager()->CreateBundle( "MDM_FF2_IOM14_PLUS", 16 );
		dopSBTC[0].Connect( pBundle, 4 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF2_IOM15_CH0", 16 );
		dopSBTC[3].Connect( pBundle, 13 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM14_PLUS", 16 );
		dopSBTC[1].Connect( pBundle, 4 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM15_CH0", 16 );
		dopSBTC[4].Connect( pBundle, 13 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF4_IOM14_PLUS", 16 );
		dopSBTC[2].Connect( pBundle, 4 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF4_IOM15_CH0", 16 );
		dopSBTC[5].Connect( pBundle, 13 );
	}

	pBundle = BundleManager()->CreateBundle( "DDU_POWER", 16 );
	dipPower.Connect( pBundle, 3 + (4 * (ID - 1)) );
	return;
}

void SBTC::OnPreStep( double simt, double simdt, double mjd )
{
	if (dipPower.IsSet())
	{
		double pos = 0.0;
		bool takeover = false;

		STS()->GetSBTCPosition( ID, pos, takeover );

		// limit output voltage to match position limit voltage to MDM input voltage
		dopSBTC[0].SetLine( static_cast<float>((1.0 - pos) * 5.11) );
		dopSBTC[1].SetLine( static_cast<float>((1.0 - pos) * 5.11) );
		dopSBTC[2].SetLine( static_cast<float>((1.0 - pos) * 5.11) );

		dopSBTC[3].SetLine( takeover ? 15.0f : 0.0f );
		dopSBTC[4].SetLine( takeover ? 15.0f : 0.0f );
		dopSBTC[5].SetLine( takeover ? 15.0f : 0.0f );
	}
	else for (auto &x : dopSBTC) x.ResetLine();
	return;
}

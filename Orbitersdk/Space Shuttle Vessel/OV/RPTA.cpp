/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2026/09/18   GLS
********************************************/
#include "RPTA.h"
#include "Atlantis.h"
#include <cassert>


RPTA::RPTA( AtlantisSubsystemDirector* _director, const string& _ident, unsigned short ID ):AtlantisSubsystem( _director, _ident )
{
	assert( ((ID == 1) || (ID == 2)) && "RPTA::RPTA:ID" );
	this->ID = ID;
	return;
}

RPTA::~RPTA( void )
{
}

void RPTA::Realize( void )
{
	DiscreteBundle* pBundle;

	if (ID == 1)
	{
		// left
		pBundle = BundleManager()->CreateBundle( "MDM_FF1_IOM1_HI", 16 );
		dopRPTA[0].Connect( pBundle, 3 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF2_IOM1_HI", 16 );
		dopRPTA[1].Connect( pBundle, 3 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM1_HI", 16 );
		dopRPTA[2].Connect( pBundle, 3 );
	}
	else
	{
		// right
		pBundle = BundleManager()->CreateBundle( "MDM_FF2_IOM14_HI", 16 );
		dopRPTA[0].Connect( pBundle, 3 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM14_HI", 16 );
		dopRPTA[1].Connect( pBundle, 3 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF4_IOM14_HI", 16 );
		dopRPTA[2].Connect( pBundle, 3 );
	}

	pBundle = BundleManager()->CreateBundle( "DDU_POWER", 16 );
	dipPower.Connect( pBundle, 3 + (4 * (ID - 1)) );
	return;
}

void RPTA::OnPreStep( double simt, double simdt, double mjd )
{
	if (dipPower.IsSet())
	{
		double pos = 0.0;

		STS()->GetRPTAPosition( pos );

		// limit output voltage to match position limit voltage to MDM input voltage
		dopRPTA[0].SetLine( static_cast<float>(pos * 5.11) );
		dopRPTA[1].SetLine( static_cast<float>(pos * 5.11) );
		dopRPTA[2].SetLine( static_cast<float>(pos * 5.11) );
	}
	else for (auto &x : dopRPTA) x.ResetLine();
	return;
}

/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
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
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "RPTA", 16 );

	if (ID == 1) for (int i = 0; i < 3; i++) dopRPTA[i].Connect( pBundle, i );// left
	else for (int i = 0; i < 3; i++) dopRPTA[i].Connect( pBundle, i + 3 );// right

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

		dopRPTA[0].SetLine( (float)pos );
		dopRPTA[1].SetLine( (float)pos );
		dopRPTA[2].SetLine( (float)pos );
	}
	else for (auto &x : dopRPTA) x.ResetLine();
	return;
}

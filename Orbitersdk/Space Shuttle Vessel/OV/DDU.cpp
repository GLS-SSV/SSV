/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
********************************************/
#include "DDU.h"
#include <cassert>


DDU::DDU( AtlantisSubsystemDirector* _director, const string& _ident, unsigned short ID ):AtlantisSubsystem( _director, _ident )
{
	assert( ((ID == 1) || (ID == 2) || (ID == 3)) && "DDU::DDU:ID" );
	this->ID = ID;
	return;
}

DDU::~DDU( void )
{
}

void DDU::Realize( void )
{
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "DDU_POWER", 16 );

	dipMNxPower[0].Connect( pBundle, 0 + (4 * (ID - 1)) );
	dipMNxPower[1].Connect( pBundle, 1 + (4 * (ID - 1)) );
	dipControllerPowerSwitch.Connect( pBundle, 2 + (4 * (ID - 1)) );
	dopOutputPower.Connect( pBundle, 3 + (4 * (ID - 1)) );
	return;
}

void DDU::OnPreStep( double simt, double simdt, double mjd )
{
	if ((dipMNxPower[0].IsSet() || dipMNxPower[1].IsSet()) && dipControllerPowerSwitch.IsSet()) dopOutputPower.SetLine();
	else dopOutputPower.ResetLine();
	return;
}

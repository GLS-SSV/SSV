#include "MPC3.h"


MPC3::MPC3( AtlantisSubsystemDirector *_director, bool ODSkit ):AtlantisSubsystem( _director, "MPC3" ),
	ODSkit(ODSkit)
{
}

MPC3::~MPC3()
{
}

void MPC3::Realize( void )
{
	if (ODSkit)
	{
		discsignals::DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MPC_ODS_POWER", 16 );
		LogicPwr_C2.Connect( pBundle, 10 );
		LogicPwr_C3.Connect( pBundle, 11 );
	}
	return;
}

void MPC3::OnPreStep( double simt, double simdt, double mjd )
{
	if (ODSkit)
	{
		LogicPwr_C2.SetLine( 28.0f );
		LogicPwr_C3.SetLine( 28.0f );
	}
	return;
}

#include "MPC1.h"


MPC1::MPC1( AtlantisSubsystemDirector *_director, bool ODSkit ):AtlantisSubsystem( _director, "MPC1" ),
	ODSkit(ODSkit), K5(false)
{
}

MPC1::~MPC1()
{
}

void MPC1::Realize( void )
{
	if (ODSkit)
	{
		discsignals::DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MPC_ODS_POWER", 16 );
		K5_on.Connect( pBundle, 0 );
		K5_off.Connect( pBundle, 1 );
		MNA_A7.Connect( pBundle, 4 );
		LogicPwr_A3.Connect( pBundle, 6 );
		LogicPwr_A1.Connect( pBundle, 7 );
		LightDepressVlv_MNA.Connect( pBundle, 12 );
	}
	return;
}

void MPC1::OnPreStep( double simt, double simdt, double mjd )
{
	if (ODSkit)
	{
		K5 = (K5_on && !K5_off) || (K5 && !K5_off) || (K5 && K5_on);

		if (K5)
		{
			MNA_A7.SetLine( 28.0f );
			LogicPwr_A3.SetLine( 28.0f );
			LogicPwr_A1.SetLine( 28.0f );
			LightDepressVlv_MNA.SetLine( 28.0f );
		}
		else
		{
			MNA_A7.ResetLine();
			LogicPwr_A3.ResetLine();
			LogicPwr_A1.ResetLine();
			LightDepressVlv_MNA.ResetLine();
		}
	}
	return;
}

bool MPC1::OnParseLine( const char* line )
{
	if (ODSkit)
	{
		if (!_strnicmp( line, "K5", 2 ))
		{
			int tmp = 0;
			sscanf_s( line + 3, "%d", &tmp );
			K5 = (tmp == 1);
			return true;
		}
	}
	return false;
}

void MPC1::OnSaveState( FILEHANDLE scn ) const
{
	if (ODSkit)
	{
		oapiWriteScenario_int( scn, "K5", K5 ? 1 : 0 );
	}
	return;
}

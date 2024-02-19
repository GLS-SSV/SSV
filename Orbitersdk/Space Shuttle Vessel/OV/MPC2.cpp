#include "MPC2.h"


MPC2::MPC2( AtlantisSubsystemDirector *_director, bool ODSkit ):AtlantisSubsystem( _director, "MPC2" ),
	ODSkit(ODSkit), K5(false)
{
}

MPC2::~MPC2()
{
}

void MPC2::Realize( void )
{
	if (ODSkit)
	{
		discsignals::DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MPC_ODS_POWER", 16 );
		K5_on.Connect( pBundle, 2 );
		K5_off.Connect( pBundle, 3 );
		MNB_A7.Connect( pBundle, 5 );
		LogicPwr_B1.Connect( pBundle, 8 );
		LogicPwr_B2.Connect( pBundle, 9 );
		LightDepressVlv_MNB.Connect( pBundle, 13 );
	}
	return;
}

void MPC2::OnPreStep( double simt, double simdt, double mjd )
{
	if (ODSkit)
	{
		K5 = (K5_on && !K5_off) || (K5 && !K5_off) || (K5 && K5_on);

		if (K5)
		{
			MNB_A7.SetLine( 28.0f );
			LogicPwr_B1.SetLine( 28.0f );
			LogicPwr_B2.SetLine( 28.0f );
			LightDepressVlv_MNB.SetLine( 28.0f );
		}
		else
		{
			MNB_A7.ResetLine();
			LogicPwr_B1.ResetLine();
			LogicPwr_B2.ResetLine();
			LightDepressVlv_MNB.ResetLine();
		}
	}
	return;
}

bool MPC2::OnParseLine( const char* line )
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

void MPC2::OnSaveState( FILEHANDLE scn ) const
{
	if (ODSkit)
	{
		oapiWriteScenario_int( scn, "K5", K5 ? 1 : 0 );
	}
	return;
}

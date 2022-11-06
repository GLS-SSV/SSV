#include "SSB_PL_BAY_DOORS.h"


namespace dps
{
	SSB_PL_BAY_DOORS::SSB_PL_BAY_DOORS( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "SSB_PL_BAY_DOORS" )
	{
		return;
	}

	SSB_PL_BAY_DOORS::~SSB_PL_BAY_DOORS( void )
	{
		return;
	}

	bool SSB_PL_BAY_DOORS::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void SSB_PL_BAY_DOORS::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	void SSB_PL_BAY_DOORS::OnPostStep( double simt, double simdt, double mjd )
	{
		if (ReadCOMPOOL_IS( SCP_CSBB_POWER_ON_OFF_FLAG ) == 1)
		{
			WriteCOMPOOL_IS( SCP_CSBB_POWER_ON_OFF_FLAG, 0 );
			if (ReadCOMPOOL_AIS( SCP_CSBB_POWER_ON_OFF_ITEM, 1, 2 ) == 1)
			{
				// power on
			}
			else
			{
				// power off
			}
		}
		return;
	}

	bool SSB_PL_BAY_DOORS::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 201:
				WriteCOMPOOL_AIS( SCP_CSBB_POWER_ON_OFF_ITEM, 1, 0, 2 );
				WriteCOMPOOL_AIS( SCP_CSBB_POWER_ON_OFF_ITEM, 2, 1, 2 );
				WriteCOMPOOL_IS( SCP_CSBB_SWITCH_BYPASS_ITEM, 0 );
				WriteCOMPOOL_IS( SCP_CSBB_PBD_OPEN_ITEM, 0 );
				WriteCOMPOOL_IS( SCP_CSBB_PBD_STOP_ITEM, 0 );
				WriteCOMPOOL_IS( SCP_CSBB_PBD_CLOSE_ITEM, 0 );
				return true;
			default:
				WriteCOMPOOL_AIS( SCP_CSBB_POWER_ON_OFF_ITEM, 1, 0, 2 );
				WriteCOMPOOL_AIS( SCP_CSBB_POWER_ON_OFF_ITEM, 2, 1, 2 );
				return false;
		}
	}
}

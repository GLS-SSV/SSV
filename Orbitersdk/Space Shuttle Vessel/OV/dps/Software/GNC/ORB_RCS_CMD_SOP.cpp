#include "ORB_RCS_CMD_SOP.h"


namespace dps
{
	ORB_RCS_CMD_SOP::ORB_RCS_CMD_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "ORB_RCS_CMD_SOP" )
	{
		return;
	}

	ORB_RCS_CMD_SOP::~ORB_RCS_CMD_SOP( void )
	{
		return;
	}

	void ORB_RCS_CMD_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		return;
	}

	bool ORB_RCS_CMD_SOP::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void ORB_RCS_CMD_SOP::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	bool ORB_RCS_CMD_SOP::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 201:
			case 202:
			case 801:
				return true;
		}
		return false;
	}
}

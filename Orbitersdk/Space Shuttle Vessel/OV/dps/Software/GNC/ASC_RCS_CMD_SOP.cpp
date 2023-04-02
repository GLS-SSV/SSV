#include "ASC_RCS_CMD_SOP.h"


namespace dps
{
	ASC_RCS_CMD_SOP::ASC_RCS_CMD_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "ASC_RCS_CMD_SOP" )
	{
		return;
	}

	ASC_RCS_CMD_SOP::~ASC_RCS_CMD_SOP( void )
	{
		return;
	}

	void ASC_RCS_CMD_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		return;
	}

	bool ASC_RCS_CMD_SOP::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void ASC_RCS_CMD_SOP::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	bool ASC_RCS_CMD_SOP::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 102:
			case 103:
			case 104:
			case 105:
			case 106:
			case 301:
			case 302:
			case 303:
			case 601:
			case 602:
			case 603:
				return true;
		}
		return false;
	}
}

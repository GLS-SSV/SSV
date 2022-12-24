#include "RCS_RM.h"
#include <MathSSV.h>


namespace dps
{
	RCS_RM::RCS_RM( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "RCS_RM" )
	{
		return;
	}

	RCS_RM::~RCS_RM( void )
	{
		return;
	}

	void RCS_RM::Realize( void )
	{
		return;
	}

	void RCS_RM::OnPostStep( double simt, double simdt, double mjd )
	{
		return;
	}

	bool RCS_RM::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void RCS_RM::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	bool RCS_RM::OnMajorModeChange( unsigned int newMajorMode )
	{
		return true;
	}
}

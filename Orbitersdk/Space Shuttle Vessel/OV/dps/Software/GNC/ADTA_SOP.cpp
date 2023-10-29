#include "ADTA_SOP.h"
#include "../../../Atlantis.h"
#include <EngConst.h>


namespace dps
{
	ADTA_SOP::ADTA_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "ADTA_SOP" )
	{
		return;
	}

	ADTA_SOP::~ADTA_SOP( void )
	{
		return;
	}

	void ADTA_SOP::OnPreStep( double simt, double simdt, double mjd )
	{
		double ALPHA = STS()->GetAOA();
		double QBAR = STS()->GetDynPressure() * PA2PSF;
		double EAS = (sqrt( QBAR ) * 17.18) * (MPS2FPS / MPS2KTS);
		double ALT = STS()->GetAltitude() * MPS2FPS / 1000;// TODO
		double M = STS()->GetMachNumber();
		double HDOT = 0;// TODO
		double TAS = STS()->GetAirspeed() * MPS2FPS;

		WriteCOMPOOL_IS( SCP_ADPVALIDC, 1 );
		WriteCOMPOOL_IS( SCP_ADPVALIDP, 1 );

		WriteCOMPOOL_SS( SCP_ALPHA, static_cast<float>(ALPHA) );
		WriteCOMPOOL_SS( SCP_DDALPHAC, static_cast<float>(ALPHA) );
		WriteCOMPOOL_SS( SCP_DDALPHAP, static_cast<float>(ALPHA) );

		WriteCOMPOOL_SS( SCP_DDALTC, static_cast<float>(ALT) );
		WriteCOMPOOL_SS( SCP_DDALTP, static_cast<float>(ALT) );

		WriteCOMPOOL_SS( SCP_DDEASC, static_cast<float>(EAS) );
		WriteCOMPOOL_SS( SCP_DDEASP, static_cast<float>(EAS) );

		WriteCOMPOOL_SS( SCP_DDHDOTC, static_cast<float>(HDOT) );
		WriteCOMPOOL_SS( SCP_DDHDOTP, static_cast<float>(HDOT) );

		WriteCOMPOOL_SS( SCP_DDMC, static_cast<float>(M) );
		WriteCOMPOOL_SS( SCP_DDMP, static_cast<float>(M) );

		WriteCOMPOOL_SS( SCP_EAS, static_cast<float>(EAS) );

		WriteCOMPOOL_SS( SCP_M, static_cast<float>(M) );

		WriteCOMPOOL_SS( SCP_QBAR, static_cast<float>(QBAR) );

		WriteCOMPOOL_SS( SCP_TAS, static_cast<float>(TAS) );

		return;
	}

	bool ADTA_SOP::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 301:
			case 302:
			case 303:
			case 304:
			case 305:
			case 602:// TODO check this
			case 603:
				return true;
			default:
				return false;
		}
	}

	bool ADTA_SOP::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void ADTA_SOP::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}
}

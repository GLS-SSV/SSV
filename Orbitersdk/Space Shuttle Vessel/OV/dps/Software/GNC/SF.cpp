#include "SF.h"
#include "../../../Atlantis.h"


namespace dps
{
	SF::SF( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "SF" )
	{
		return;
	}

	SF::~SF( void )
	{
		return;
	}

	void SF::OnPreStep( double simt, double simdt, double mjd )
	{
		// HACK NY, NZ
		VECTOR3 gravity;
		STS()->GetWeightVector( gravity );
		VECTOR3 f;
		STS()->GetForceVector( f );
		WriteCOMPOOL_SS( SCP_NY, static_cast<float>((f.x - (STS()->GroundContact() ? 0.0 : gravity.x)) / length( gravity )) );
		WriteCOMPOOL_SS( SCP_NZ, static_cast<float>((f.y - (STS()->GroundContact() ? 0.0 : gravity.y)) / length( gravity )) );

		// HACK rates
		VECTOR3 rates;
		STS()->GetAngularVel( rates );
		WriteCOMPOOL_SS( SCP_Q_ORB, static_cast<float>(rates.x * DEG) );
		WriteCOMPOOL_SS( SCP_P_ORB, static_cast<float>(rates.z * DEG) );
		WriteCOMPOOL_SS( SCP_R_ORB, static_cast<float>(-rates.y * DEG) );
		return;
	}

	bool SF::OnMajorModeChange( unsigned int newMajorMode )
	{
		return true;
	}
}

#include "ASCENT_UPP.h"
#include "../../../Atlantis.h"
#include "../../../Mission/Mission.h"
#include <MathSSV.h>


namespace dps
{
	ASCENT_UPP::ASCENT_UPP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "ASCENT_UPP" )
	{
		return;
	}

	ASCENT_UPP::~ASCENT_UPP( void )
	{
		return;
	}

	void ASCENT_UPP::Realize( void )
	{
		hEarth = STS()->GetGravityRef();
		return;
	}

	void ASCENT_UPP::OnPreStep( double simt, double simdt, double mjd )
	{
		VECTOR3 ECEF_pos = GetPosition_ECEF( STS(), hEarth ) * MPS2FPS;
		VECTOR3 ECEF_vel = GetVelocity_ECEF( STS(), hEarth ) * MPS2FPS;
		VECTOR3 ECI_pos = GetPosition_ECI( STS(), hEarth ) * MPS2FPS;
		VECTOR3 ECI_vel = GetVelocity_ECI( STS(), hEarth ) * MPS2FPS;

		STATE_PROPAGATION( ECEF_vel, ECI_vel );
		ASCENT_RTLS_COMPS( ECEF_vel, ECEF_pos );
		PW_HSI_COMPS( ECEF_vel, ECI_vel, ECEF_pos, ECI_pos );
		return;
	}

	void ASCENT_UPP::STATE_PROPAGATION( const VECTOR3& ECEF_vel, const VECTOR3& ECI_vel )
	{
		WriteCOMPOOL_SS( SCP_REL_VEL_MAG, static_cast<float>(length( ECEF_vel )) );
		WriteCOMPOOL_SS( SCP_V_INERTIAL_MAG, static_cast<float>(length( ECI_vel )) );
		return;
	}

	void ASCENT_UPP::ASCENT_RTLS_COMPS( const VECTOR3& ECEF_vel, const VECTOR3& ECEF_pos )
	{
		WriteCOMPOOL_SS( SCP_ALT, static_cast<float>(length( ECEF_pos ) - 20902263.7794/*Earth eq. radius*/) );

		unsigned short MM = ReadCOMPOOL_IS( SCP_MM );
		if ((MM == 102) || (MM == 103) || (MM == 601))
		{
			WriteCOMPOOL_SS( SCP_EAS, static_cast<float>(sqrt( STS()->GetDynPressure() * PA2PSF ) * 17.18 * (MPS2FPS / MPS2KTS)) );

			VECTOR3 f;
			STS()->GetForceVector( f );
			WriteCOMPOOL_SS( SCP_LOAD_TOTAL, static_cast<float>((f.z / (STS()->GetMass() * G)) + sin( STS()->GetPitch() )) );
		}

		double HDOT = dotp( ECEF_vel, ECEF_pos ) / length( ECEF_pos );
		WriteCOMPOOL_SS( SCP_H_DOT, static_cast<float>(HDOT) );
		return;
	}

	void ASCENT_UPP::PW_HSI_COMPS( const VECTOR3& ECEF_vel, const VECTOR3& ECI_vel, const VECTOR3& ECEF_pos, const VECTOR3& ECI_pos )
	{
		// rotation matrix from EC to "local"
		VECTOR3 zi = unit( ECI_pos );// up
		VECTOR3 yi = unit( crossp( _V( 0.0, 0.0, 1.0 ), zi ) );// east
		VECTOR3 xi = unit( crossp( zi, yi ) );// north
		MATRIX3 roti = _M( xi.x, xi.y, xi.z, yi.x, yi.y, yi.z, zi.x, zi.y, zi.z );

		VECTOR3 zr = unit( ECEF_pos );// up
		VECTOR3 yr = unit( crossp( _V( 0.0, 0.0, 1.0 ), zr ) );// east
		VECTOR3 xr = unit( crossp( zr, yr ) );// north
		MATRIX3 rotr = _M( xr.x, xr.y, xr.z, yr.x, yr.y, yr.z, zr.x, zr.y, zr.z );

		// get "local" velocities
		VECTOR3 vi = mul( roti, ECI_vel );
		VECTOR3 vr = mul( rotr, ECEF_vel );

		// get angle to north
		double vih = SignedAngle( _V( vi.x, vi.y, 0.0 ), _V( 1.0, 0.0, 0.0 ), _V( 0.0, 0.0, -1.0 ) );
		double vrh = SignedAngle( _V( vr.x, vr.y, 0.0 ), _V( 1.0, 0.0, 0.0 ), _V( 0.0, 0.0, -1.0 ) );

		WriteCOMPOOL_SS( SCP_HEADING_V_I, static_cast<float>(vih) );
		if (ReadCOMPOOL_SS( SCP_REL_VEL_MAG ) > 200) WriteCOMPOOL_SS( SCP_HEADING_V_REL, static_cast<float>(vrh) );
		else WriteCOMPOOL_SS( SCP_HEADING_V_REL, 0.0f );

		WriteCOMPOOL_IS( SCP_CDI_SCALE, 50 );
		WriteCOMPOOL_SS( SCP_HEADING_TAL, 0.0f );
		WriteCOMPOOL_SS( SCP_MEDS_D_AZ, 0.0f );

		ELEMENTS el;
		STS()->GetElements( hEarth, el, NULL, 0, FRAME_EQU );
		WriteCOMPOOL_SS( SCP_MEDS_D_INCL, static_cast<float>(STS()->GetMissionData()->GetMECOInc() - el.i) );

		WriteCOMPOOL_SS( SCP_INCL_TARGET, 0.0f );
		WriteCOMPOOL_SS( SCP_PW_RANGE, 0.0f );
		WriteCOMPOOL_SS( SCP_XTRK, 0.0f );
		WriteCOMPOOL_SS( SCP_XTRK_CDI, 0.0f );
		WriteCOMPOOL_SS( SCP_HEADING_ATO, 0.0f );
		WriteCOMPOOL_SS( SCP_HEADING_RW, 0.0f );
		return;
	}

	void ASCENT_UPP::ASCENT_UPP_INIT( void )
	{
		return;
	}

	bool ASCENT_UPP::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 101:
			case 102:
			case 103:
			case 104:
			case 105:
			case 106:
				return true;
			default:
				return false;
		}
	}

	bool ASCENT_UPP::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void ASCENT_UPP::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}
}

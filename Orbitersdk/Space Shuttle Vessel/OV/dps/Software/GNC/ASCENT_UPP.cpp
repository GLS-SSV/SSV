#include "ASCENT_UPP.h"
#include "GNCUtilities.h"
#include "../../../Atlantis.h"
#include <MathSSV.h>


namespace dps
{
	static void GetStateVectors( VESSEL* v, OBJHANDLE hEarth, VECTOR3& pos, VECTOR3& vel )
	{
		v->GetRelativePos(hEarth, pos);
		v->GetRelativeVel(hEarth, vel);

		pos = ConvertBetweenLHAndRHFrames(pos);
		vel = ConvertBetweenLHAndRHFrames(vel);

		pos = mul(M_J2000_to_M50, pos);
		vel = mul(M_J2000_to_M50, vel);
	}


	ASCENT_UPP::ASCENT_UPP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "ASCENT_UPP" ),
		hEarth(0)
	{
		return;
	}

	ASCENT_UPP::~ASCENT_UPP( void )
	{
		return;
	}

	void ASCENT_UPP::OnPreStep( double simt, double simdt, double mjd )
	{
		if (!hEarth) hEarth = STS()->GetGravityRef();

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

		unsigned short MM_CODE_102 = ReadCOMPOOL_IS( SCP_MM_CODE_102 );
		unsigned short MM_CODE_103 = ReadCOMPOOL_IS( SCP_MM_CODE_103 );
		unsigned short MM_CODE_601 = ReadCOMPOOL_IS( SCP_MM_CODE_601 );
		if ((MM_CODE_102 == 1) || (MM_CODE_103 == 1) || (MM_CODE_601 == 1))
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

		VECTOR3 R_AVGG, V_AVGG, IYC, IY_XTRK, IYC_EF, IYT_EF;
		double T_STATE, INCL_TARGET;
		GNCUtilities* pGNCUtilities = dynamic_cast<GNCUtilities*>(GetCOMSUB( "GNCUtilities" ));

		if (ReadCOMPOOL_SS( SCP_REL_VEL_MAG ) > 200) WriteCOMPOOL_SS( SCP_HEADING_V_REL, static_cast<float>(vrh) );
		else WriteCOMPOOL_SS( SCP_HEADING_V_REL, 0.0f );

		WriteCOMPOOL_SS( SCP_HEADING_V_I, static_cast<float>(vih) );

		GetStateVectors( STS(), hEarth, R_AVGG, V_AVGG );
		R_AVGG *= MPS2FPS;
		V_AVGG *= MPS2FPS;
		IY_XTRK = ReadCOMPOOL_VD( SCP_IYD );
		double XTRK = -dotp(R_AVGG, IY_XTRK) * NAUTMI_PER_FT;
		WriteCOMPOOL_SS( SCP_XTRK, static_cast<float>(XTRK) );
		WriteCOMPOOL_SS( SCP_XTRK_CDI, static_cast<float>(XTRK) );

		WriteCOMPOOL_IS( SCP_CDI_SCALE, 50 );
		if (fabs( XTRK ) <= 10) WriteCOMPOOL_IS( SCP_CDI_SCALE, 10 );
		if ((fabs( XTRK ) <= 1) && (STS()->GetMET() >= 390)) WriteCOMPOOL_IS( SCP_CDI_SCALE, 1 );

		T_STATE = ReadClock();
		IYC = unit(crossp(V_AVGG, R_AVGG));
		IYC_EF = tmul(pGNCUtilities->EARTH_FIXED_TO_M50_COORD(T_STATE), IYC);
		IYT_EF = tmul(pGNCUtilities->EARTH_FIXED_TO_M50_COORD(T_STATE), IY_XTRK);
		INCL_TARGET = acos( -IYT_EF.z );
		WriteCOMPOOL_SS( SCP_INCL_TARGET, static_cast<float>(INCL_TARGET) );
		WriteCOMPOOL_SS( SCP_MEDS_D_INCL, static_cast<float>(INCL_TARGET - acos(-IYC_EF.z)) );

		WriteCOMPOOL_SS( SCP_HEADING_TAL, 0.0f );
		WriteCOMPOOL_SS( SCP_MEDS_D_AZ, 0.0f );

		WriteCOMPOOL_SS( SCP_PW_RANGE, 0.0f );

		WriteCOMPOOL_SS( SCP_HEADING_ATO, 0.0f );
		WriteCOMPOOL_SS( SCP_HEADING_RW, 0.0f );
		return;
	}

	void ASCENT_UPP::ASCENT_UPP_INIT( void )
	{
		return;
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

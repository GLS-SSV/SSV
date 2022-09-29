/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2020/08/24   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/12/29   GLS
2022/03/24   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "AL_UPP.h"
#include "../Atlantis.h"
#include <MathSSV.h>


namespace dps
{
	AL_UPP::AL_UPP( SimpleGPCSystem* _gpc ):SimpleGPCSoftware( _gpc, "AL_UPP" )
	{
#if 1// for OSFS2016 only, r87 fixes issue
		firststep = true;
		QBAR_0 = 0.0f;
		XLFAC_0 = 0.0f;
		DRAG_0 = 0.0f;
		LOD_0 = 0.0f;
		ALPHA_0 = 0.0f;
		COSALF_0 = 1.0f;
		SINALF_0 = 0.0f;
		BETA_0 = 0.0f;
		PHI_0 = 0.0f;
		COSPHI_0 = 1.0f;
		SINPHI_0 = 0.0f;
		NY_0 = 0.0f;
		NZ_0 = 1.0f;
#endif
		return;
	}

	AL_UPP::~AL_UPP( void )
	{
		return;
	}

	void AL_UPP::Realize( void )
	{
		hEarth = STS()->GetGravityRef();
		return;
	}

#if 1// for OSFS2016 only, r87 fixes issue
	bool AL_UPP::OnParseLine( const char* keyword, const char* value )
	{
		if (!_strnicmp( keyword, "QBAR", 4 ))
		{
			float tmp = 0.0f;
			sscanf_s( value, "%f", &tmp );
			QBAR_0 = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "XLFAC", 5 ))
		{
			float tmp = 0.0f;
			sscanf_s( value, "%f", &tmp );
			XLFAC_0 = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "DRAG", 4 ))
		{
			float tmp = 0.0f;
			sscanf_s( value, "%f", &tmp );
			DRAG_0 = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "LOD", 3 ))
		{
			float tmp = 0.0f;
			sscanf_s( value, "%f", &tmp );
			LOD_0 = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "ALPHA", 5 ))
		{
			float tmp = 0.0f;
			sscanf_s( value, "%f", &tmp );
			ALPHA_0 = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "COSALF", 6 ))
		{
			float tmp = 0.0f;
			sscanf_s( value, "%f", &tmp );
			COSALF_0 = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "SINALF", 6 ))
		{
			float tmp = 0.0f;
			sscanf_s( value, "%f", &tmp );
			SINALF_0 = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "BETA", 4 ))
		{
			float tmp = 0.0f;
			sscanf_s( value, "%f", &tmp );
			BETA_0 = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "PHI", 3 ))
		{
			float tmp = 0.0f;
			sscanf_s( value, "%f", &tmp );
			PHI_0 = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "COSPHI", 6 ))
		{
			float tmp = 0.0f;
			sscanf_s( value, "%f", &tmp );
			COSPHI_0 = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "SINPHI", 6 ))
		{
			float tmp = 0.0f;
			sscanf_s( value, "%f", &tmp );
			SINPHI_0 = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "NY", 2 ))
		{
			float tmp = 0.0f;
			sscanf_s( value, "%f", &tmp );
			NY_0 = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "NZ", 2 ))
		{
			float tmp = 0.0f;
			sscanf_s( value, "%f", &tmp );
			NZ_0 = tmp;
			return true;
		}
		else return false;
	}

	void AL_UPP::OnSaveState( FILEHANDLE scn ) const
	{
		float QBAR = ReadCOMPOOL_SD( SCP_QBAR );
		float XLFAC = ReadCOMPOOL_SD( SCP_XLFAC );
		float DRAG = ReadCOMPOOL_SD( SCP_DRAG );
		float LOD = ReadCOMPOOL_SD( SCP_LOD );
		float ALPHA = ReadCOMPOOL_SD( SCP_ALPHA );
		float COSALF = ReadCOMPOOL_SD( SCP_COSALF );
		float SINALF = ReadCOMPOOL_SD( SCP_SINALF );
		float BETA = ReadCOMPOOL_SD( SCP_BETA );
		float PHI = ReadCOMPOOL_SD( SCP_PHI );
		float COSPHI = ReadCOMPOOL_SD( SCP_COSPHI );
		float SINPHI = ReadCOMPOOL_SD( SCP_SINPHI );
		float NY = ReadCOMPOOL_SD( SCP_NY );
		float NZ = ReadCOMPOOL_SD( SCP_NZ );

		oapiWriteScenario_float( scn, "QBAR", QBAR );
		oapiWriteScenario_float( scn, "XLFAC", XLFAC );
		oapiWriteScenario_float( scn, "DRAG", DRAG );
		oapiWriteScenario_float( scn, "LOD", LOD );
		oapiWriteScenario_float( scn, "ALPHA", ALPHA );
		oapiWriteScenario_float( scn, "COSALF", COSALF );
		oapiWriteScenario_float( scn, "SINALF", SINALF );
		oapiWriteScenario_float( scn, "BETA", BETA );
		oapiWriteScenario_float( scn, "PHI", PHI );
		oapiWriteScenario_float( scn, "COSPHI", COSPHI );
		oapiWriteScenario_float( scn, "SINPHI", SINPHI );
		oapiWriteScenario_float( scn, "NY", NY );
		oapiWriteScenario_float( scn, "NZ", NZ );
		return;
	}
#endif

	void AL_UPP::OnPreStep( double simt, double simdt, double mjd )
	{
		if (ReadCOMPOOL_IS( SCP_TG_END ) == 0) return;

		VECTOR3 ECEF_pos = GetPosition_ECEF( STS(), hEarth ) * MPS2FPS;
		WriteCOMPOOL_V( SCP_ECEF_POS, ECEF_pos );

		VECTOR3 ECEF_vel = GetVelocity_ECEF( STS(), hEarth ) * MPS2FPS;
		WriteCOMPOOL_V( SCP_ECEF_VEL, ECEF_vel );

		double VE = length( ECEF_vel );
		WriteCOMPOOL_SD( SCP_VE, static_cast<float>(VE) );

		VECTOR3 rwPos;
		if (ReadCOMPOOL_IS( SCP_RWID ) == 1) rwPos = ReadCOMPOOL_V( SCP_PRI_POS );
		else rwPos = ReadCOMPOOL_V( SCP_SEC_POS );
		WriteCOMPOOL_SD( SCP_H, static_cast<float>(length( ECEF_pos ) - length( rwPos ) - 18.5) );// correction for wheels

		double HDOT = dotp( ECEF_vel, ECEF_pos ) / length( ECEF_pos );
		WriteCOMPOOL_SD( SCP_HDOT, static_cast<float>(HDOT) );

		VECTOR3 RRW;
		VECTOR3 VRW;
		if (ReadCOMPOOL_IS( SCP_RWID ) == 1)
		{
			MATRIX3 G2R = ReadCOMPOOL_M( SCP_PRI_G2R );
			RRW = mul( G2R, ECEF_pos - ReadCOMPOOL_V( SCP_PRI_POS ) );
			VRW = mul( G2R, ECEF_vel );
		}
		else
		{
			MATRIX3 G2R = ReadCOMPOOL_M( SCP_SEC_G2R );
			RRW = mul( G2R, ECEF_pos - ReadCOMPOOL_V( SCP_SEC_POS ) );
			VRW = mul( G2R, ECEF_vel );
		}

		WriteCOMPOOL_SD( SCP_V_T, static_cast<float>(STS()->GetAirspeed() * MPS2FPS) );
		double qbar = STS()->GetDynPressure() * PA2PSF;
		double keas = sqrt( qbar ) * 17.18;
		WriteCOMPOOL_SD( SCP_V_I, static_cast<float>((keas / MPS2KTS) * MPS2FPS) );
		WriteCOMPOOL_SD( SCP_KEAS, static_cast<float>(keas) );
		WriteCOMPOOL_SD( SCP_VG, static_cast<float>(length( ECEF_vel - (ECEF_pos * (dotp( ECEF_vel, ECEF_pos ) / dotp( ECEF_pos, ECEF_pos ))) )) );
		WriteCOMPOOL_SD( SCP_X, static_cast<float>(RRW.x) );
		WriteCOMPOOL_SD( SCP_Y, static_cast<float>(RRW.y) );
		WriteCOMPOOL_SD( SCP_Z, static_cast<float>(RRW.z) );
		WriteCOMPOOL_SD( SCP_XDOT, static_cast<float>(VRW.x) );
		WriteCOMPOOL_SD( SCP_YDOT, static_cast<float>(VRW.y) );
		WriteCOMPOOL_SD( SCP_HDG, static_cast<float>(STS()->GetYaw() * DEG) );
		WriteCOMPOOL_SD( SCP_GAMMA, static_cast<float>(asin( HDOT / VE ) * DEG) );

		double PHI = -STS()->GetBank();
		WriteCOMPOOL_SD( SCP_PHI, static_cast<float>(PHI * DEG) );
		WriteCOMPOOL_SD( SCP_COSPHI, static_cast<float>(cos( PHI )) );
		WriteCOMPOOL_SD( SCP_SINPHI, static_cast<float>(sin( PHI )) );
		WriteCOMPOOL_SD( SCP_TANPHI, static_cast<float>(tan( PHI )) );
		double THETA = STS()->GetPitch();
		WriteCOMPOOL_SD( SCP_THETA, static_cast<float>(THETA * DEG) );
		WriteCOMPOOL_SD( SCP_COSTH, static_cast<float>(cos( THETA )) );
		WriteCOMPOOL_SD( SCP_SINTH, static_cast<float>(sin( THETA )) );
		double ALPHA = STS()->GetAOA();
		WriteCOMPOOL_SD( SCP_ALPHA, static_cast<float>(ALPHA * DEG) );
		WriteCOMPOOL_SD( SCP_COSALF, static_cast<float>(cos( ALPHA )) );
		WriteCOMPOOL_SD( SCP_SINALF, static_cast<float>(sin( ALPHA )) );
		WriteCOMPOOL_SD( SCP_BETA, -static_cast<float>(STS()->GetSlipAngle() * DEG) );
		WriteCOMPOOL_SD( SCP_QBAR, static_cast<float>(qbar) );

		double weight = STS()->GetMass();
		VECTOR3 lift, drag, gravity;
		STS()->GetLiftVector( lift );
		STS()->GetDragVector( drag );
		STS()->GetWeightVector( gravity );
		VECTOR3 f;
		STS()->GetForceVector( f );
		WriteCOMPOOL_SD( SCP_NY, static_cast<float>((f.x - (STS()->GroundContact() ? 0.0 : gravity.x)) / length( gravity )) );
		WriteCOMPOOL_SD( SCP_NZ, static_cast<float>((lift.y + drag.y) / length( gravity )) );
		WriteCOMPOOL_SD( SCP_WEIGHT, static_cast<float>(weight * KG2LBM * LBS2SL) );

		VECTOR3 rates;
		STS()->GetAngularVel( rates );
		WriteCOMPOOL_SD( SCP_Q, static_cast<float>(rates.x * DEG) );
		WriteCOMPOOL_SD( SCP_P, static_cast<float>(rates.z * DEG) );
		WriteCOMPOOL_SD( SCP_R, static_cast<float>(-rates.y * DEG) );

#if 1// for OSFS2016 only, r87 fixes issue
		// HACK to avoid wrong data in first timestep, load parameters from scenario (or default values)
		if (firststep)
		{
			firststep = false;
			WriteCOMPOOL_SD( SCP_QBAR, QBAR_0 );
			WriteCOMPOOL_SD( SCP_XLFAC, XLFAC_0 );
			WriteCOMPOOL_SD( SCP_DRAG, DRAG_0 );
			WriteCOMPOOL_SD( SCP_LOD, LOD_0 );
			WriteCOMPOOL_SD( SCP_ALPHA, ALPHA_0 );
			WriteCOMPOOL_SD( SCP_COSALF, COSALF_0 );
			WriteCOMPOOL_SD( SCP_SINALF, SINALF_0 );
			WriteCOMPOOL_SD( SCP_BETA, BETA_0 );
			WriteCOMPOOL_SD( SCP_PHI, PHI_0 );
			WriteCOMPOOL_SD( SCP_COSPHI, COSPHI_0 );
			WriteCOMPOOL_SD( SCP_SINPHI, SINPHI_0 );
			WriteCOMPOOL_SD( SCP_NY, NY_0 );
			WriteCOMPOOL_SD( SCP_NZ, NZ_0 );
		}
#endif
		return;
	}

	bool AL_UPP::OnMajorModeChange( unsigned int newMajorMode )
	{
		if (newMajorMode == 305) return true;
		else return false;
	}
};

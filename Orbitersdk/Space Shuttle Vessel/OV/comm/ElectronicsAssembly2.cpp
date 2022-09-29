/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "ElectronicsAssembly2.h"
#include "../Atlantis.h"
#include "DeployedAssembly.h"
#include <MathSSV.h>


namespace comm
{
	constexpr VECTOR3 ANTENNA_OFFSET = { 3.5, 0.5, 10.5 };// m (approx)
	constexpr double RADAR_MAINLOBE_HALF_CONE = 5;// deg


	ElectronicsAssembly2::ElectronicsAssembly2( AtlantisSubsystemDirector* _director, DeployedAssembly* pDeployedAssembly ):AtlantisSubsystem( _director, "ElectronicsAssembly2" )
	{
		this->pDeployedAssembly = pDeployedAssembly;

		target = NULL;
		rOLD = 0;

		dt_OLD = 0.1;
	}

	ElectronicsAssembly2::~ElectronicsAssembly2()
	{
	}

	void ElectronicsAssembly2::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "A1U_SWITCHES_B", 16 );
		pPower_Off.Connect( pBundle, 5 );
		pPower_On.Connect( pBundle, 6 );

		pBundle = BundleManager()->CreateBundle( "EA1_EA2", 16 );
		KUaz.Connect( pBundle, 0 );
		KUel.Connect( pBundle, 1 );
		RADSTB.Connect( pBundle, 2 );
		RADON.Connect( pBundle, 3 );
		RADARPOWERLOW.Connect( pBundle, 4 );
		RADARPOWERMEDIUM.Connect( pBundle, 5 );
		Range.Connect( pBundle, 6 );
		RangeRate.Connect( pBundle, 7 );
		Detect.Connect( pBundle, 8 );
		TGTaz.Connect( pBundle, 9 );
		TGTel.Connect( pBundle, 10 );
		return;
	}

	void ElectronicsAssembly2::OnPostStep( double simt, double simdt, double mjd )
	{
		if (pPower_Off || RADSTB)
		{
			Detect.ResetLine();
			Range.ResetLine();
			RangeRate.ResetLine();
			TGTaz.ResetLine();
			TGTel.ResetLine();
			return;
		}

		double r = 0;
		double rr = 0;
		double az = 0;
		double el = 0;

		if (target)
		{
			if (!GetTargetInfo( target, r, rr, az, el, dt_OLD ))
			{
				target = NULL;
				Detect.ResetLine();
				Range.ResetLine();
				RangeRate.ResetLine();
				TGTaz.ResetLine();
				TGTel.ResetLine();
			}
			else
			{
				Range.SetLine( (float)(r * MPS2FPS) );
				RangeRate.SetLine( (float)range( -150, rr * MPS2FPS, 75 ) );
				TGTaz.SetLine( (float)az );
				TGTel.SetLine( (float)el );
			}
		}
		else
		{
			if ((target = FindTarget( r, az, el )))
			{
				rOLD = r;
				Detect.SetLine();
			}
		}

		dt_OLD = simdt;
		return;
	}

	OBJHANDLE ElectronicsAssembly2::FindTarget( double &r, double &az, double &el )
	{
		for (int i = oapiGetVesselCount() - 1; i >= 0; i--)
		{
			OBJHANDLE hVessel = oapiGetVesselByIndex( i );
			if (hVessel != STS()->GetHandle())
			{
				if (IsDetected( hVessel, r, az, el )) return hVessel;
			}
		}
		return NULL;
	}

	bool ElectronicsAssembly2::GetTargetInfo( OBJHANDLE hVessel, double &r, double &rr, double &az, double &el, double dt )
	{
		if (IsDetected( hVessel, r, az, el ))
		{
			rr = (r - rOLD) / dt;
			rOLD = r;
			return true;
		}
		return false;
	}

	bool ElectronicsAssembly2::IsDetected( OBJHANDLE hVessel, double &r, double &az, double &el )
	{
		VECTOR3 gpos;
		oapiGetGlobalPos( hVessel, &gpos );

		VECTOR3 lpos;
		STS()->Global2Local( gpos, lpos );
		lpos -= ANTENNA_OFFSET;
		r = length( lpos );
		if ((r < 30.48) || (r > 45720)) return false;// 100ft and 150kft

		double size = oapiGetSize( hVessel );
		double p = GetPower();

		double r0_4 = 863097.48412416;// 30.48^4 Km
		double p0 = 27;// W
		double size0 = 6.5;// m

		double r2 = 1000 * pow( (p * size * r0_4) / (p0 * size0), 0.25 );

		if (r <= r2)
		{
			az = atan2( -lpos.x, lpos.y ) * DEG;
			el = atan2( lpos.z, fabs( lpos.y ) ) * DEG;
			// HACK assume constant power inside main lobe
			if ((acos( sin( az * RAD ) * sin( KUaz.GetVoltage() * RAD ) + cos( az * RAD ) * cos( KUaz.GetVoltage() * RAD ) * cos( (el - KUel.GetVoltage()) * RAD ) ) * DEG) < RADAR_MAINLOBE_HALF_CONE) return true;
		}

		return false;
	}

	double ElectronicsAssembly2::GetPower( void )
	{
		if (RADARPOWERLOW.IsSet()) return 0.09;// low
		else if (RADARPOWERMEDIUM.IsSet()) return 1.4;// med
		else return 22.39;// high
	}
};
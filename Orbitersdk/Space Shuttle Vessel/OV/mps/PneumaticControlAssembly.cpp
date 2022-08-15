/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/01/10   GLS
2022/01/15   GLS
2022/08/05   GLS
********************************************/
#include "PneumaticControlAssembly.h"
#include "SSME.h"
#include "HeliumSystem.h"
#include "SolenoidValve.h"
#include "PressureActuatedValve.h"


namespace mps
{
	constexpr double RATE_FSP_SV = 1000;
	constexpr double RATE_BVC_SV = 1000;
	constexpr double RATE_ES_SV = 1000;
	constexpr double RATE_SP_SV = 1000;
	constexpr double RATE_HPOTPISP_SV = 1000;

	constexpr double RATE_FSP_PAV = 100;
	constexpr double RATE_OBV_PAV = 100;
	constexpr double RATE_ES_PAV = 100;
	constexpr double RATE_FPP_PAV = 100;
	constexpr double RATE_OPP_PAV = 100;
	constexpr double RATE_HPOTPISP_PAV = 100;
	constexpr double RATE_OSP_PAV = 100;
	constexpr double RATE_PSV_PAV = 6;//16.7s


	PneumaticControlAssembly::PneumaticControlAssembly( SSME* eng, HeSysEng* HeSys )
	{
		FuelSystemPurge_SV = new SolenoidValve( 0, RATE_FSP_SV, true, HeSys, nullptr );
		BleedValvesControl_SV = new SolenoidValve( 1, RATE_BVC_SV, true, HeSys, nullptr );
		EmergencyShutdown_SV = new SolenoidValve( 0, RATE_ES_SV, false, HeSys, nullptr );

		PurgeSequenceValve_PAV = new PressureActuatedValve( 1, RATE_PSV_PAV, nullptr, nullptr, EmergencyShutdown_SV, nullptr );

		ShutdownPurge_SV = new SolenoidValve( 0, RATE_SP_SV, true, HeSys, PurgeSequenceValve_PAV );
		HPOTPISPurge_SV = new SolenoidValve( 1, RATE_HPOTPISP_SV, true, HeSys, PurgeSequenceValve_PAV );

		FuelSystemPurge_PAV = new PressureActuatedValve( 0, RATE_FSP_PAV, FuelSystemPurge_SV, nullptr, HeSys, nullptr );
		OxidizerBleedValve_PAV = new PressureActuatedValve( 1, RATE_OBV_PAV, BleedValvesControl_SV, nullptr, HeSys, nullptr );
		EmergencyShutdown_PAV = new PressureActuatedValve( 0, RATE_ES_PAV, EmergencyShutdown_SV, nullptr, HeSys, nullptr );
		OxidizerSystemPurge_PAV = new PressureActuatedValve( 0, RATE_OSP_PAV, EmergencyShutdown_SV, nullptr, HeSys, nullptr );// TODO change EmergencyShutdown_SV and HeSys to GSE N2
		FuelPreburnerPurge_PAV = new PressureActuatedValve( 0, RATE_FPP_PAV, ShutdownPurge_SV, nullptr, HeSys, nullptr );//, OxidizerSystemPurge_PAV );
		OxidizerPreburnerPurge_PAV = new PressureActuatedValve( 0, RATE_OPP_PAV, ShutdownPurge_SV, nullptr, HeSys, nullptr );//, OxidizerSystemPurge_PAV );
		HPOTPISPurge_PAV = new PressureActuatedValve( 1, RATE_HPOTPISP_PAV, HPOTPISPurge_SV, nullptr, HeSys, nullptr );//, OxidizerSystemPurge_PAV );

		pressFuelSystemPurge = 0;
		//pressEmergencyShutdown = 0;
		pressFuelPreburnerPurge = 0;
		pressOxidizerPreburnerPurge = 0;
		pressHPOTPISPurge = 0;

		this->eng = eng;
		this->HeSys = HeSys;
		return;
	}

	PneumaticControlAssembly::~PneumaticControlAssembly( void )
	{
		delete FuelSystemPurge_SV;
		delete BleedValvesControl_SV;
		delete EmergencyShutdown_SV;
		delete ShutdownPurge_SV;
		delete HPOTPISPurge_SV;

		delete FuelSystemPurge_PAV;
		delete OxidizerBleedValve_PAV;
		delete EmergencyShutdown_PAV;
		delete FuelPreburnerPurge_PAV;
		delete OxidizerPreburnerPurge_PAV;
		delete HPOTPISPurge_PAV;
		delete OxidizerSystemPurge_PAV;
		delete PurgeSequenceValve_PAV;
		return;
	}

	void PneumaticControlAssembly::tmestp( double simdt )
	{
		FuelSystemPurge_SV->tmestp( simdt );
		BleedValvesControl_SV->tmestp( simdt );
		EmergencyShutdown_SV->tmestp( simdt );
		ShutdownPurge_SV->tmestp( simdt );
		HPOTPISPurge_SV->tmestp( simdt );

		FuelSystemPurge_PAV->tmestp( simdt );
		OxidizerBleedValve_PAV->tmestp( simdt );
		EmergencyShutdown_PAV->tmestp( simdt );
		OxidizerSystemPurge_PAV->tmestp( simdt );
		PurgeSequenceValve_PAV->tmestp( simdt );
		FuelPreburnerPurge_PAV->tmestp( simdt );
		OxidizerPreburnerPurge_PAV->tmestp( simdt );
		HPOTPISPurge_PAV->tmestp( simdt );

		if (FuelPreburnerPurge_PAV->GetPos() > 0)
		{
			pressFuelPreburnerPurge = 0.3 * FuelPreburnerPurge_PAV->GetPos() * HeSys->Use( 20.0, 0 );// use He
		}
		else
		{
			pressFuelPreburnerPurge = 0;
		}
		if (OxidizerPreburnerPurge_PAV->GetPos() > 0)
		{
			pressOxidizerPreburnerPurge = OxidizerPreburnerPurge_PAV->GetPos() * HeSys->Use( 50.0, 0 );// use He
		}
		else
		{
			pressOxidizerPreburnerPurge = 0;
		}

		//sprintf_s( oapiDebugString(), 256, "IS%.1f|%.1f OBV%.1f|%.1f FSP%.1f OSP%.1f ESD%.1f FPBP%.1f OPBP%.1f PSV%.1f", HPOTPISPurge_PAV->GetPos(), HPOTPISPurge_SV->GetPos(), OxidizerBleedValve_PAV->GetPos(), BleedValvesControl_SV->GetPos(), FuelSystemPurge_PAV->GetPos(), OxidizerSystemPurge_PAV->GetPos(), EmergencyShutdown_PAV->GetPos(), FuelPreburnerPurge_PAV->GetPos(), OxidizerPreburnerPurge_PAV->GetPos(), PurgeSequenceValve_PAV->GetPos() );
		return;
	}

	void PneumaticControlAssembly::Realize( discsignals::DiscreteBundle* bundle )
	{
		FuelSystemPurge_SV->Connect( 0, bundle, 0 );
		FuelSystemPurge_SV->Connect( 1, bundle, 1 );

		BleedValvesControl_SV->Connect( 0, bundle, 2 );
		BleedValvesControl_SV->Connect( 1, bundle, 3 );

		EmergencyShutdown_SV->Connect( 0, bundle, 4 );
		EmergencyShutdown_SV->Connect( 1, bundle, 5 );

		ShutdownPurge_SV->Connect( 0, bundle, 6 );
		ShutdownPurge_SV->Connect( 1, bundle, 7 );

		HPOTPISPurge_SV->Connect( 0, bundle, 8 );
		HPOTPISPurge_SV->Connect( 1, bundle, 9 );
		return;
	}

	double PneumaticControlAssembly::UseHPOTPISPurge( double flow )
	{// TODO get GSE press
		pressHPOTPISPurge = 0.27604167 * HPOTPISPurge_PAV->Use( flow, 0 );// HACK no clue about the "regulator"
		return pressHPOTPISPurge;
	}
	// expected shutdown value of 518 psia for the Phase II SSME,
	// or 576 psia for the BLOCK I SSME, BLOCK IIA SSME, and the BLOCK II SSME

	double PneumaticControlAssembly::UseFuelSystemPurge( double flow )
	{
		pressFuelSystemPurge = 0.3 * FuelSystemPurge_PAV->Use( flow, 0 );// HACK no clue about the "regulator"
		return pressFuelSystemPurge;
	}

	double PneumaticControlAssembly::GetPressFuelSystemPurge() const
	{
		return pressFuelSystemPurge;
	}

	double PneumaticControlAssembly::GetPressEmergencyShutdown() const
	{
		return EmergencyShutdown_PAV->GetPos() * HeSys->Use( 0, 0 );
		//return pressEmergencyShutdown;
	}

	double PneumaticControlAssembly::GetPressFuelPreburnerPurge() const
	{
		return pressFuelPreburnerPurge;
	}

	double PneumaticControlAssembly::GetPressOxidizerPreburnerPurge() const
	{
		return pressOxidizerPreburnerPurge;
	}

	double PneumaticControlAssembly::GetPressHPOTPISPurge() const
	{
		return pressHPOTPISPurge;
	}
}
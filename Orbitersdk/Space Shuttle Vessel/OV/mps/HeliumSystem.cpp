/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/04/07   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/06/06   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/01/10   GLS
2022/01/15   GLS
2022/08/05   GLS
2022/08/07   GLS
********************************************/
#include "HeliumSystem.h"
#include <SolenoidValve.h>
#include <discsignals.h>
#include "MPSdefs.h"


namespace mps
{
	constexpr double R = 8.314;
	constexpr double AR_HE = 4.00260222;
	constexpr double TANK_VOL_ENG = 0.7560598;// m^3
	constexpr double TANK_VOL_PNEU = 0.1330892;// m^3

	constexpr double INITIAL_TANK_TEMP_ENG = 310.0;//303.0;// K
	constexpr double INITIAL_TANK_TEMP_PNEU = 290.0;//303.0;// K
	constexpr double INITIAL_HE_MASS_ENG = 34000.0;//30500.0;// g
	constexpr double INITIAL_HE_MASS_PNEU = 5897.0;// g
	constexpr double MAX_REG_FLOW = 400.0;// g/s
	constexpr double MAX_TANK_FLOW = 600.0;// g/s


	HeSysEng::HeSysEng( AtlantisSubsystemDirector* _director, const string& _ident, int ID ):AtlantisSubsystem( _director, _ident )
	{
#ifdef _MPSDEBUG
		oapiWriteLogV( " HeSysEng::HeSysEng in || ID:%d", ID );
#endif// _MPSDEBUG

		this->ID = ID;
		TankTemp = INITIAL_TANK_TEMP_ENG;
		HeMass = INITIAL_HE_MASS_ENG;// + (INITIAL_HE_MASS_ENG * 0.1 * (oapiRand() - 0.5));// +/-5% variance
		TankPress = (((HeMass / AR_HE) * R * TankTemp) / TANK_VOL_ENG) / 6894.757;
		RegPress = 785.0;
		TotalFlow = 0.0;

		vlvISOL_A = new SolenoidValve( 1.0, 1000.0, true, nullptr, nullptr );
		vlvISOL_B = new SolenoidValve( 1.0, 1000.0, true, nullptr, nullptr );

		vlvInIC = new SolenoidValve( 0.0, 1000.0, true, nullptr, nullptr );
		vlvOutIC = new SolenoidValve( 0.0, 1000.0, true, nullptr, nullptr );

		TankPressure = Sensor( 0.0, 5000.0 );
		RegPressure[0] = Sensor( 0.0, 1000.0 );
		RegPressure[1] = Sensor( 0.0, 1000.0 );

#ifdef _MPSDEBUG
		oapiWriteLog( " HeSysEng::HeSysEng out" );
#endif// _MPSDEBUG
		return;
	}

	HeSysEng::~HeSysEng( void )
	{
		delete vlvISOL_A;
		delete vlvISOL_B;

		delete vlvInIC;
		delete vlvOutIC;
		return;
	}

	void HeSysEng::Realize( void )
	{
		discsignals::DiscreteBundle* bundle;
		switch (ID)
		{
			case 1:
				bundle = BundleManager()->CreateBundle( "MPS_LV_A", 16 );// LV1 - LV16
				vlvISOL_A->Connect( 0, bundle, 0 );
				vlvISOL_B->Connect( 0, bundle, 1 );

				bundle = BundleManager()->CreateBundle( "MPS_LV_D", 16 );// LV49 - LV64
				vlvInIC->Connect( 0, bundle, 10 );
				vlvOutIC->Connect( 0, bundle, 11 );

				bundle = BundleManager()->CreateBundle( "MPS_HE_SENSORS", 12 );
				TankPressure.Connect( bundle, 0 );
				RegPressure[0].Connect( bundle, 1 );
				RegPressure[1].Connect( bundle, 2 );

				sys1 = dynamic_cast<HeSysEng*>(director->GetSubsystemByName( "HeEng_L" ));
				sys2 = dynamic_cast<HeSysEng*>(director->GetSubsystemByName( "HeEng_R" ));
				break;
			case 2:
				bundle = BundleManager()->CreateBundle( "MPS_LV_A", 16 );// LV1 - LV16
				vlvISOL_A->Connect( 0, bundle, 2 );
				vlvISOL_B->Connect( 0, bundle, 3 );

				bundle = BundleManager()->CreateBundle( "MPS_LV_D", 16 );// LV49 - LV64
				vlvInIC->Connect( 0, bundle, 12 );
				vlvOutIC->Connect( 0, bundle, 13 );

				bundle = BundleManager()->CreateBundle( "MPS_HE_SENSORS", 12 );
				TankPressure.Connect( bundle, 3 );
				RegPressure[0].Connect( bundle, 4 );
				RegPressure[1].Connect( bundle, 5 );

				sys1 = dynamic_cast<HeSysEng*>(director->GetSubsystemByName( "HeEng_C" ));
				sys2 = dynamic_cast<HeSysEng*>(director->GetSubsystemByName( "HeEng_R" ));
				break;
			case 3:
				bundle = BundleManager()->CreateBundle( "MPS_LV_A", 16 );// LV1 - LV16
				vlvISOL_A->Connect( 0, bundle, 4 );
				vlvISOL_B->Connect( 0, bundle, 5 );

				bundle = BundleManager()->CreateBundle( "MPS_LV_D", 16 );// LV49 - LV64
				vlvInIC->Connect( 0, bundle, 14 );
				vlvOutIC->Connect( 0, bundle, 15 );

				bundle = BundleManager()->CreateBundle( "MPS_HE_SENSORS", 12 );
				TankPressure.Connect( bundle, 6 );
				RegPressure[0].Connect( bundle, 7 );
				RegPressure[1].Connect( bundle, 8 );

				sys1 = dynamic_cast<HeSysEng*>(director->GetSubsystemByName( "HeEng_C" ));
				sys2 = dynamic_cast<HeSysEng*>(director->GetSubsystemByName( "HeEng_L" ));
				break;
		}

		sysP = dynamic_cast<HeSysPneu*>(director->GetSubsystemByName( "HePneu" ));
		return;
	}

	void HeSysEng::OnSaveState( FILEHANDLE scn ) const
	{
		char cbuf[128];

		sprintf_s( cbuf, 128, "PRESS" );
		oapiWriteScenario_float( scn, cbuf, TankPress );

		sprintf_s( cbuf, 128, "%f %f %f %f", vlvISOL_A->GetPos(), vlvISOL_B->GetPos(), vlvInIC->GetPos(), vlvOutIC->GetPos() );
		oapiWriteScenario_string( scn, "VALVES", cbuf );
		return;
	}

	bool HeSysEng::OnParseLine( const char* line )
	{
		double read_f1 = 0.0;
		double read_f2 = 0.0;
		double read_f3 = 0.0;
		double read_f4 = 0.0;

		if (!_strnicmp( line, "PRESS", 5 ))
		{
			sscanf_s( line + 5, "%lf", &read_f1 );

			if ((read_f1 >= 0.0) && (read_f1 <= 4500.0))
			{
				TankPress = read_f1;
				HeMass = (TankPress * 6894.757 * TANK_VOL_ENG * AR_HE) / ( R * INITIAL_TANK_TEMP_ENG);
			}
#ifdef _MPSDEBUG
			oapiWriteLogV( " HeSysEng::OnParseLine || TankPress:%f HeMass:%f", TankPress, HeMass );
#endif// _MPSDEBUG
			return true;
		}
		else if (!_strnicmp( line, "VALVES", 6 ))
		{
			sscanf_s( line + 6, "%lf %lf %lf %lf", &read_f1, &read_f2, &read_f3, &read_f4 );

			if ((read_f1 >= 0.0) && (read_f1 <= 1.0))
			{
				vlvISOL_A->_backdoor( read_f1 );
			}

			if ((read_f2 >= 0.0) && (read_f2 <= 1.0))
			{
				vlvISOL_B->_backdoor( read_f2 );
			}

			if ((read_f3 >= 0.0) && (read_f3 <= 1.0))
			{
				vlvInIC->_backdoor( read_f3 );
			}

			if ((read_f4 >= 0.0) && (read_f4 <= 1.0))
			{
				vlvOutIC->_backdoor( read_f4 );
			}
#ifdef _MPSDEBUG
			oapiWriteLogV( " HeSysEng::OnParseLine || vlvISOL_A:%f vlvISOL_B:%f vlvInIC:%f vlvOutIC:%f", vlvISOL_A->GetPos(), vlvISOL_B->GetPos(), vlvInIC->GetPos(), vlvOutIC->GetPos() );
#endif// _MPSDEBUG
			return true;
		}
		return false;
	}

	void HeSysEng::OnPostStep( double simt, double simdt, double mjd )
	{
		// update vlvs
		vlvISOL_A->tmestp( simdt );
		vlvISOL_B->tmestp( simdt );

		vlvInIC->tmestp( simdt );
		vlvOutIC->tmestp( simdt );

		if ((ID == 2) && (sysP->vlvLEngXOVR->GetPos() == 1.0))
		{
			double XOVRratio = sysP->GetRegPress() / (RegPress + sysP->GetRegPress());
			sysP->Use( TotalFlow * XOVRratio, 0 );
			TotalFlow = TotalFlow * (1.0 - XOVRratio);
		}

		double maxregflow = (vlvISOL_A->GetPos() + vlvISOL_B->GetPos()) * MAX_REG_FLOW;
		if (maxregflow == 0.0)
		{
			// TODO should opening isol vlvs look like this?
			RegPress -= 400.0 * simdt;// to show a decay upon closing the isol vlvs
			if (RegPress < 0.0) RegPress = 0.0;
			TotalFlow = 0.0;

			TankPressure.SetValue( TankPress );
			RegPressure[0].SetValue( RegPress );
			RegPressure[1].SetValue( RegPress );
			return;
		}

		double regheadpress = 0;

		if (vlvInIC->GetPos() == 1.0)// TODO change to != 0???
		{
			double usedmass = TotalFlow * simdt;
			double totalpress = 0.0;
			double inpress[4] = {0.0, 0.0, 0.0, 0.0};

			if (TankPress > sysP->GetTankPress())
			{
				inpress[0] = TankPress;
			}
			else
			{
				inpress[1] = sysP->GetTankPress();
				if ((sys1->IsOutICOpen() == 1) && (sys1->GetTankPress() > inpress[1])) inpress[2] = sys1->GetTankPress();
				if ((sys2->IsOutICOpen() == 1) && (sys2->GetTankPress() > inpress[1])) inpress[3] = sys2->GetTankPress();
			}

			totalpress = inpress[0] + inpress[1] + inpress[2] + inpress[3];

			inpress[0] = UseTank( (inpress[0] / totalpress) * usedmass );
			regheadpress = inpress[0];

			inpress[1] = sysP->UseTank( (inpress[1] / totalpress) * usedmass );
			if (regheadpress < inpress[1]) regheadpress = inpress[1];

			inpress[2] = sys1->UseTank( (inpress[2] / totalpress) * usedmass );
			if (regheadpress < inpress[2]) regheadpress = inpress[2];

			inpress[3] = sys2->UseTank( (inpress[3] / totalpress) * usedmass );
			if (regheadpress < inpress[3]) regheadpress = inpress[3];
		}
		else
		{
			UseTank( TotalFlow * simdt );
			regheadpress = TankPress;
		}

		RegPress = 730.0 + (((maxregflow - TotalFlow) / maxregflow) * 55.0);
		if (regheadpress < RegPress) RegPress = regheadpress;
		TotalFlow = 0.0;

		TankPressure.SetValue( TankPress );
		RegPressure[0].SetValue( RegPress );
		RegPressure[1].SetValue( RegPress );
		return;
	}

	double HeSysEng::Use( double flow, int source )
	{
		TotalFlow += flow;

		if ((ID == 2) && (sysP->vlvLEngXOVR->GetPos() == 1.0) && (RegPress < sysP->GetRegPress())) return sysP->GetRegPress();
		return RegPress;
	}

	double HeSysEng::UseTank( double mass )
	{
		double P1 = TankPress * 6894.757;
		double m2 = HeMass - mass;
		if (m2 <= 0.0)
		{
			TankPress = 0.0;
			HeMass = 0.0;
			return 0.0;
		}
		double P2 = P1 * pow( HeMass / m2, -1.66 );
		double T2 = TankTemp * pow( P2 / P1, 0.397590 );
		TankPress = P2 / 6894.757;
		TankTemp = T2;
		HeMass = m2;
		return TankPress;
	}

	double HeSysEng::FillTank( double mass )
	{
		double P1 = TankPress * 6894.757;
		double m2 = HeMass + mass;
		double P2 = P1 * pow( HeMass / m2, -1.66 );
		double T2 = TankTemp * pow( P2 / P1, 0.397590 );
		TankPress = P2 / 6894.757;
		TankTemp = T2;
		HeMass = m2;
		return TankPress;
	}

	int HeSysEng::GetTankPress( void ) const
	{
		return (int)TankPress;//((int)(TankPress / 10)) * 10;
	}

	int HeSysEng::GetRegPress( void ) const
	{
		return (int)RegPress;
	}

	double HeSysEng::IsOutICOpen( void ) const
	{
		return vlvOutIC->GetPos();
	}


	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////


	HeSysPneu::HeSysPneu( AtlantisSubsystemDirector* _director, const string& _ident ):AtlantisSubsystem( _director, _ident )
	{
		TankTemp = INITIAL_TANK_TEMP_PNEU;
		HeMass = INITIAL_HE_MASS_PNEU;// + (INITIAL_HE_MASS_PNEU * 0.1 * (oapiRand() - 0.5));// +/-5% variance
		TankPress = (((HeMass / AR_HE) * R * TankTemp) / TANK_VOL_PNEU) / 6894.757;
		RegPress = 770.0;
		TotalFlow = 0.0;

		vlvISOL_A = new SolenoidValve( 1.0, 1000.0, true, nullptr, nullptr );
		vlvISOL_B = new SolenoidValve( 1.0, 1000.0, true, nullptr, nullptr );

		vlvLEngXOVR = new SolenoidValve( 0.0, 1000.0, true, nullptr, nullptr );

		TankPressure = Sensor( 0.0, 5000.0 );
		RegPressure = Sensor( 0.0, 1000.0 );
		return;
	}

	HeSysPneu::~HeSysPneu( void )
	{
		delete vlvISOL_A;
		delete vlvISOL_B;

		delete vlvLEngXOVR;
		return;
	}

	void HeSysPneu::Realize( void )
	{
		discsignals::DiscreteBundle* bundle = BundleManager()->CreateBundle( "MPS_LV_A", 16 );// LV1 - LV16
		vlvISOL_A->Connect( 0, bundle, 6 );
		vlvISOL_B->Connect( 0, bundle, 7 );
		vlvLEngXOVR->Connect( 0, bundle, 9 );

		bundle = BundleManager()->CreateBundle( "MPS_HE_SENSORS", 12 );
		TankPressure.Connect( bundle, 9 );
		RegPressure.Connect( bundle, 10 );

		sys1 = dynamic_cast<HeSysEng*>(director->GetSubsystemByName( "HeEng_C" ));
		sys2 = dynamic_cast<HeSysEng*>(director->GetSubsystemByName( "HeEng_L" ));
		sys3 = dynamic_cast<HeSysEng*>(director->GetSubsystemByName( "HeEng_R" ));
		return;
	}

	void HeSysPneu::OnSaveState( FILEHANDLE scn ) const
	{
		char cbuf[128];

		sprintf_s( cbuf, 128, "PRESS" );
		oapiWriteScenario_float( scn, cbuf, TankPress );

		sprintf_s( cbuf, 128, "%f %f %f", vlvISOL_A->GetPos(), vlvISOL_B->GetPos(), vlvLEngXOVR->GetPos() );
		oapiWriteScenario_string( scn, "VALVES", cbuf );
		return;
	}

	bool HeSysPneu::OnParseLine( const char* line )
	{
		double read_f1 = 0.0;
		double read_f2 = 0.0;
		double read_f3 = 0.0;

		if (!_strnicmp( line, "PRESS", 5 ))
		{
			sscanf_s( line + 5, "%lf", &read_f1 );

			if ((read_f1 >= 0.0) && (read_f1 <= 4500.0))
			{
				TankPress = read_f1;
				HeMass = (TankPress * 6894.757 * TANK_VOL_PNEU * AR_HE) / ( R * INITIAL_TANK_TEMP_PNEU);
			}
#ifdef _MPSDEBUG
			oapiWriteLogV( " HeSysPneu::OnParseLine || TankPress:%f HeMass:%f", TankPress, HeMass );
#endif// _MPSDEBUG
			return true;
		}
		else if (!_strnicmp( line, "VALVES", 6 ))
		{
			sscanf_s( line + 6, "%lf %lf %lf", &read_f1, &read_f2, &read_f3 );

			if ((read_f1 >= 0.0) && (read_f1 <= 1.0))
			{
				vlvISOL_A->_backdoor( read_f1 );
			}

			if ((read_f2 >= 0.0) && (read_f2 <= 1.0))
			{
				vlvISOL_B->_backdoor( read_f2 );
			}

			if ((read_f3 >= 0.0) && (read_f3 <= 1.0))
			{
				vlvLEngXOVR->_backdoor( read_f3 );
			}
#ifdef _MPSDEBUG
			oapiWriteLogV( " HeSysPneu::OnParseLine || vlvISOL_A:%f vlvISOL_B:%f vlvLEngXOVR:%f", vlvISOL_A->GetPos(), vlvISOL_B->GetPos(), vlvLEngXOVR->GetPos() );
#endif// _MPSDEBUG
			return true;
		}
		return false;
	}

	void HeSysPneu::OnPostStep( double simt, double simdt, double mjd )
	{
		// update vlvs
		vlvISOL_A->tmestp( simdt );
		vlvISOL_B->tmestp( simdt );

		vlvLEngXOVR->tmestp( simdt );

		if (vlvLEngXOVR->GetPos() == 1.0)
		{
			double XOVRratio = sys2->GetRegPress() / (RegPress + sys2->GetRegPress());
			sys2->Use( TotalFlow * XOVRratio, 0 );
			TotalFlow = TotalFlow * (1.0 - XOVRratio);
		}

		double maxregflow = (vlvISOL_A->GetPos() + vlvISOL_B->GetPos()) * MAX_REG_FLOW;
		if (maxregflow == 0.0)
		{
			RegPress -= 400.0 * simdt;// to show a decay upon closing the isol vlvs
			if (RegPress < 0.0) RegPress = 0.0;
			TotalFlow = 0.0;
		}

		// I/C
		double inpress[3] = {0.0, 0.0, 0.0};

		if ((sys1->IsOutICOpen() == 1) && (sys1->GetTankPress() > TankPress)) inpress[0] = sys1->GetTankPress();
		if ((sys2->IsOutICOpen() == 1) && (sys2->GetTankPress() > TankPress)) inpress[1] = sys2->GetTankPress();
		if ((sys3->IsOutICOpen() == 1) && (sys3->GetTankPress() > TankPress)) inpress[2] = sys3->GetTankPress();

		double totalpress = inpress[0] + inpress[1] + inpress[2];

		if (totalpress > 0.0)
		{
			// TODO it would be nice to equalize press perfectly, but it's not that bad with current "brute force" approach
			double ICmass = MAX_TANK_FLOW * simdt;

			inpress[0] = sys1->UseTank( (inpress[0] / totalpress) * ICmass );
			inpress[1] = sys2->UseTank( (inpress[1] / totalpress) * ICmass );
			inpress[2] = sys3->UseTank( (inpress[2] / totalpress) * ICmass );

			UseTank( (TotalFlow * simdt) - ICmass );

			//sprintf_s( oapiDebugString(), 256, "%f|%f|%f|%f", totalpress, inpress[0] / totalpress, inpress[1] / totalpress, inpress[2] / totalpress );
		}
		else
		{
			UseTank( TotalFlow * simdt );
		}

		if (maxregflow > 0.0)// to not divide by 0 if ISOLs are closed
		{
			RegPress = 715.0 + (((maxregflow - TotalFlow) / maxregflow) * 55.0);
			if (TankPress < RegPress) RegPress = TankPress;
		}
		TotalFlow = 0.0;

		TankPressure.SetValue( TankPress );
		RegPressure.SetValue( RegPress );
		return;
	}

	double HeSysPneu::Use( double flow, int source )
	{
		TotalFlow += flow;

		if ((vlvLEngXOVR->GetPos() == 1.0) && (RegPress < sys2->GetRegPress())) return sys2->GetRegPress();
		return RegPress;
	}

	double HeSysPneu::UseTank( double mass )
	{
		double P1 = TankPress * 6894.757;
		double m2 = HeMass - mass;
		if (m2 <= 0.0)
		{
			TankPress = 0.0;
			HeMass = 0.0;
			return 0.0;
		}
		double P2 = P1 * pow( HeMass / m2, -1.66 );
		double T2 = TankTemp * pow( P2 / P1, 0.397590 );
		TankPress = P2 / 6894.757;
		TankTemp = T2;
		HeMass = m2;
		return TankPress;
	}

	double HeSysPneu::FillTank( double mass )
	{
		double P1 = TankPress * 6894.757;
		double m2 = HeMass + mass;
		double P2 = P1 * pow( HeMass / m2, -1.66 );
		double T2 = TankTemp * pow( P2 / P1, 0.397590 );
		TankPress = P2 / 6894.757;
		TankTemp = T2;
		HeMass = m2;
		return TankPress;
	}

	int HeSysPneu::GetTankPress( void ) const
	{
		return (int)TankPress;//((int)(TankPress / 10)) * 10;
	}

	int HeSysPneu::GetRegPress( void ) const
	{
		return (int)RegPress;
	}
}

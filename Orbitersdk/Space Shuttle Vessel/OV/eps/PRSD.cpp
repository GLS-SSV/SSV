/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2020/06/28   GLS
2020/08/17   GLS
2020/08/25   GLS
2020/08/29   GLS
2020/09/12   GLS
2020/10/06   GLS
2020/10/07   GLS
2021/01/19   GLS
2021/06/30   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/11/27   GLS
2021/12/05   GLS
2021/12/23   GLS
2021/12/30   GLS
2022/01/10   GLS
2022/01/12   GLS
2022/01/20   GLS
2022/02/16   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "PRSD.h"
#include "../Atlantis.h"
#include "SolenoidValve.h"
#include "../../CommonDefs.h"
#include <EngConst.h>


namespace eps
{
	const static char* MESHNAME_EDOSINGLEPALLET = "SSV\\OV\\EDO_single_pallet";
	const static char* MESHNAME_EDODUALPALLET = "SSV\\OV\\EDO_dual_pallet";

	constexpr double R = 8.314;
	constexpr double AR_O2 = 31.99880;// g/mol
	constexpr double AR_H2 = 2.01588;// g/mol

	constexpr double O2_TANK_DAY_MASS = 97.52236;// Kg
	constexpr double O2_TANK_MASS_CAP = 354255.6;// g
	constexpr double O2_TANK_VOL = 0.3171487;// m^3
	constexpr double O2_TANK_INITIAL_TEMP = 97.0;// K

	constexpr double H2_TANK_DAY_MASS = 102.9655;// Kg
	constexpr double H2_TANK_MASS_CAP = 41730.5;// g
	constexpr double H2_TANK_VOL = 0.6056973;// m^3
	constexpr double H2_TANK_INITIAL_TEMP = 22.0;// K

	constexpr double EDO_KIT_MASS = 123;// Kg (TODO)
	constexpr double EDO_SINGLEPALLET_DRY_MASS = 3500.0 * LBM2KG;// Kg
	constexpr double EDO_DUALPALLET_DRY_MASS = EDO_SINGLEPALLET_DRY_MASS * 1.9;// Kg (HACK)


	PRSD::PRSD( unsigned short internalsets, bool EDOhw, unsigned short pallet, AtlantisSubsystemDirector* _director ):AtlantisSubsystem( _director, "PRSD" )
	{
		if ((internalsets < 2) || (internalsets > 5))
		{
			oapiWriteLog( "(SSV_OV) [ERROR] Illegal value for Internal Tank Sets" );
			internalsets = 5;
		}
		if ((pallet > 2) || (!EDOhw && (pallet != 0)))
		{
			oapiWriteLog( "(SSV_OV) [ERROR] Illegal value for EDO Pallet" );
			pallet = 0;
		}

		this->sets = internalsets + (pallet * 4);
		this->EDOhw = EDOhw;
		this->pallet = pallet;

		hEDOPalletMesh = NULL;
		mesh_EDOPallet = MESH_UNDEFINED;

		for (int i = 0; i < sets; i++)
		{
			O2mass.push_back( O2_TANK_MASS_CAP );
			O2press.push_back( 0 );
			O2temp.push_back( O2_TANK_INITIAL_TEMP );
			H2mass.push_back( H2_TANK_MASS_CAP );
			H2press.push_back( 0 );
			H2temp.push_back( H2_TANK_INITIAL_TEMP );

			O2TKqty.push_back( Sensor( 0, 100 ) );
			O2TKpress.push_back( Sensor( 0, 1200 ) );
			O2TKtemp.push_back( Sensor( -425, 475 ) );
			O2TKhtrcntrpress.push_back( Sensor( 505, 1015 ) );
			O2TKhtrassytemp1.push_back( Sensor( -425, 475 ) );
			O2TKhtrassytemp2.push_back( Sensor( -425, 475 ) );
			H2TKqty.push_back( Sensor( 0, 100 ) );
			H2TKpress.push_back( Sensor( 0, 400 ) );
			H2TKtemp.push_back( Sensor( -425, 475 ) );
			H2TKhtrcntrpress.push_back( Sensor( 145, 305 ) );
			H2TKhtrassytemp.push_back( Sensor( -425, 475 ) );

			O2HeatersA_On.push_back( DiscInPort() );
			O2HeatersA_Auto.push_back( DiscInPort() );
			O2HeatersB_On.push_back( DiscInPort() );
			O2HeatersB_Auto.push_back( DiscInPort() );
			O2Heaters_Test.push_back( DiscInPort() );
			O2Heaters_Reset.push_back( DiscInPort() );
			H2HeatersA_On.push_back( DiscInPort() );
			H2HeatersA_Auto.push_back( DiscInPort() );
			H2HeatersB_On.push_back( DiscInPort() );
			H2HeatersB_Auto.push_back( DiscInPort() );
		}

		O2ManifPress[0] = new Sensor( 0, 1200 );
		O2ManifPress[1] = new Sensor( 0, 1200 );
		H2ManifPress[0] = new Sensor( 0, 400 );
		H2ManifPress[1] = new Sensor( 0, 400 );

		// all valves take less than 0.5s to operate
		vman.AddValve( O2Manif[0] = new SolenoidLatchingValve( "LV011", 1.0, 300, nullptr, nullptr ) );
		vman.AddValve( O2Manif[1] = new SolenoidLatchingValve( "LV021", 1.0, 300, nullptr, nullptr ) );
		vman.AddValve( H2Manif[0] = new SolenoidLatchingValve( "LV031", 1.0, 300, nullptr, nullptr ) );
		vman.AddValve( H2Manif[1] = new SolenoidLatchingValve( "LV041", 1.0, 300, nullptr, nullptr ) );

		vman.AddValve( FCO2Reac[0] = new SolenoidLatchingValve( "LV013", 1.0, 300, nullptr, nullptr ) );
		vman.AddValve( FCO2Reac[1] = new SolenoidLatchingValve( "LV023", 1.0, 300, nullptr, nullptr ) );
		vman.AddValve( FCO2Reac[2] = new SolenoidLatchingValve( "LV024", 1.0, 300, nullptr, nullptr ) );
		vman.AddValve( FCH2Reac[0] = new SolenoidLatchingValve( "LV033", 1.0, 300, nullptr, nullptr ) );
		vman.AddValve( FCH2Reac[1] = new SolenoidLatchingValve( "LV043", 1.0, 300, nullptr, nullptr ) );
		vman.AddValve( FCH2Reac[2] = new SolenoidLatchingValve( "LV044", 1.0, 300, nullptr, nullptr ) );

		vman.AddValve( O2ECLSSSupply[0] = new SolenoidLatchingValve( "LV012", 1.0, 300, nullptr, nullptr ) );
		vman.AddValve( O2ECLSSSupply[1] = new SolenoidLatchingValve( "LV022", 1.0, 300, nullptr, nullptr ) );
	}

	PRSD::~PRSD()
	{
		delete O2ManifPress[0];
		delete O2ManifPress[1];
		delete H2ManifPress[0];
		delete H2ManifPress[1];
	}

	void PRSD::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "PRSD_ValveComands", 16 );
		O2Manif[0]->ConnectInput( 0, false, pBundle, 0 );
		O2Manif[0]->ConnectInput( 0, true, pBundle, 1 );
		O2Manif[1]->ConnectInput( 0, false, pBundle, 2 );
		O2Manif[1]->ConnectInput( 0, true, pBundle, 3 );
		H2Manif[0]->ConnectInput( 0, false, pBundle, 4 );
		H2Manif[0]->ConnectInput( 0, true, pBundle, 5 );
		H2Manif[1]->ConnectInput( 0, false, pBundle, 6 );
		H2Manif[1]->ConnectInput( 0, true, pBundle, 7 );

		FCO2Reac[0]->ConnectInput( 0, false, pBundle, 8 );
		FCO2Reac[0]->ConnectInput( 0, true, pBundle, 9 );
		FCO2Reac[1]->ConnectInput( 0, false, pBundle, 10 );
		FCO2Reac[1]->ConnectInput( 0, true, pBundle, 11 );
		FCO2Reac[2]->ConnectInput( 0, false, pBundle, 12 );
		FCO2Reac[2]->ConnectInput( 0, true, pBundle, 13 );
		FCH2Reac[0]->ConnectInput( 0, false, pBundle, 8 );
		FCH2Reac[0]->ConnectInput( 0, true, pBundle, 9 );
		FCH2Reac[1]->ConnectInput( 0, false, pBundle, 10 );
		FCH2Reac[1]->ConnectInput( 0, true, pBundle, 11 );
		FCH2Reac[2]->ConnectInput( 0, false, pBundle, 12 );
		FCH2Reac[2]->ConnectInput( 0, true, pBundle, 13 );

		pBundle = BundleManager()->CreateBundle( "PRSD_ValvePositions", 16 );
		O2Manif[0]->ConnectPositionSensor( 0, pBundle, 0 );
		O2Manif[1]->ConnectPositionSensor( 0, pBundle, 1 );
		H2Manif[0]->ConnectPositionSensor( 0, pBundle, 2 );
		H2Manif[1]->ConnectPositionSensor( 0, pBundle, 3 );

		FCO2Reac[0]->ConnectPositionSensor( 0, pBundle, 4 );
		FCO2Reac[1]->ConnectPositionSensor( 0, pBundle, 5 );
		FCO2Reac[2]->ConnectPositionSensor( 0, pBundle, 6 );
		FCH2Reac[0]->ConnectPositionSensor( 0, pBundle, 7 );
		FCH2Reac[1]->ConnectPositionSensor( 0, pBundle, 8 );
		FCH2Reac[2]->ConnectPositionSensor( 0, pBundle, 9 );

		pBundle = BundleManager()->CreateBundle( "PRSD_O2HeatersA_On", 16 );
		for (int i = 0; i < sets; i++) O2HeatersA_On[i].Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "PRSD_O2HeatersA_Auto", 16 );
		for (int i = 0; i < sets; i++) O2HeatersA_Auto[i].Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "PRSD_O2HeatersB_On", 16 );
		for (int i = 0; i < sets; i++) O2HeatersB_On[i].Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "PRSD_O2HeatersB_Auto", 16 );
		for (int i = 0; i < sets; i++) O2HeatersB_Auto[i].Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "PRSD_O2Heaters_Test", 16 );
		for (int i = 0; i < sets; i++) O2Heaters_Test[i].Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "PRSD_O2Heaters_Reset", 16 );
		for (int i = 0; i < sets; i++) O2Heaters_Reset[i].Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "PRSD_H2HeatersA_On", 16 );
		for (int i = 0; i < sets; i++) H2HeatersA_On[i].Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "PRSD_H2HeatersA_Auto", 16 );
		for (int i = 0; i < sets; i++) H2HeatersA_Auto[i].Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "PRSD_H2HeatersB_On", 16 );
		for (int i = 0; i < sets; i++) H2HeatersB_On[i].Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "PRSD_H2HeatersB_Auto", 16 );
		for (int i = 0; i < sets; i++) H2HeatersB_Auto[i].Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "PRSD_O2HtrAssyTemp1", 16 );
		for (int i = 0; i < sets; i++) O2TKhtrassytemp1[i].Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "PRSD_O2HtrAssyTemp2", 16 );
		for (int i = 0; i < sets; i++) O2TKhtrassytemp2[i].Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "PRSD_H2HtrAssyTemp", 16 );
		for (int i = 0; i < sets; i++) H2TKhtrassytemp[i].Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "PRSD_O2Qty", 16 );
		for (int i = 0; i < sets; i++) O2TKqty.at( i ).Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "PRSD_H2Qty", 16 );
		for (int i = 0; i < sets; i++) H2TKqty.at( i ).Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "PRSD_O2FluidTemp", 16 );
		for (int i = 0; i < sets; i++) O2TKtemp.at( i ).Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "PRSD_H2FluidTemp", 16 );
		for (int i = 0; i < sets; i++) H2TKtemp.at( i ).Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "PRSD_O2Press", 16 );
		for (int i = 0; i < sets; i++) O2TKpress.at( i ).Connect( pBundle, i );
		O2ManifPress[0]->Connect( pBundle, 14 );
		O2ManifPress[1]->Connect( pBundle, 15 );

		pBundle = BundleManager()->CreateBundle( "PRSD_O2Press2", 16 );
		for (int i = 0; i < sets; i++) O2TKhtrcntrpress.at( i ).Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "PRSD_H2Press", 16 );
		for (int i = 0; i < sets; i++) H2TKpress.at( i ).Connect( pBundle, i );
		H2ManifPress[0]->Connect( pBundle, 14 );
		H2ManifPress[1]->Connect( pBundle, 15 );

		pBundle = BundleManager()->CreateBundle( "PRSD_H2Press2", 16 );
		for (int i = 0; i < sets; i++) H2TKhtrcntrpress.at( i ).Connect( pBundle, i );

		AddMesh();
		return;
	}

	void PRSD::AddMesh( void )
	{
		if (EDOhw)
		{
			if (pallet == 1)
			{
				hEDOPalletMesh = oapiLoadMeshGlobal( MESHNAME_EDOSINGLEPALLET );
				mesh_EDOPallet = STS()->AddMesh( hEDOPalletMesh );
				STS()->SetMeshVisibilityMode( mesh_EDOPallet, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
				oapiWriteLog( "(SSV_OV) [INFO] EDO single pallet mesh added" );
			}
			else if (pallet == 2)
			{
				hEDOPalletMesh = oapiLoadMeshGlobal( MESHNAME_EDODUALPALLET );
				mesh_EDOPallet = STS()->AddMesh( hEDOPalletMesh );
				STS()->SetMeshVisibilityMode( mesh_EDOPallet, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
				oapiWriteLog( "(SSV_OV) [INFO] EDO dual pallet mesh added" );
			}
		}
		return;
	}

	void PRSD::GetPLBInfo( unsigned short& PLID, bool& Reversed, unsigned short& pallet ) const
	{
		if (this->pallet != 0) PLID = 311;
		else PLID = 0;

		Reversed = false;

		pallet = this->pallet;
		return;
	}

	void PRSD::OnPreStep( double simt, double simdt, double mjd )
	{
		vman.OnPostStep( simt, simdt, mjd );

		// O2 1,2 803-854 (811-846)
		// O2 3,4 832-883 (840-870)
		// H2 1,2 200-226
		// H2 3,4 217-243


		// TODO

		// tk 1, 2
		if (sets >= 3)
		{
			// tk 3
			if (sets > 5)
			{
				// pallets (tk 6 - 13)
			}
		}

		if (sets >= 4)
		{
			// tk 4
			if (sets >= 5)
			{
				// tk 5
			}
		}


		// sensor output
		O2ManifPress[0]->SetValue( 0 );
		O2ManifPress[1]->SetValue( 0 );
		H2ManifPress[0]->SetValue( 0 );
		H2ManifPress[1]->SetValue( 0 );

		for (int i = 0; i < sets; i++)
		{
			O2TKqty[i].SetValue( 100 * (O2mass[i] / O2_TANK_MASS_CAP) );
			O2TKpress[i].SetValue( O2press[i] / PSI2PA );
			O2TKtemp[i].SetValue( ((O2temp[i] - 273.15) * 1.8) + 32 );
			//O2TKhtrcntrpress[i].SetValue( O2press[i] / PSI2PA );
			//O2TKhtrassytemp1[i].SetValue( ((O2temp[i] - 273.15) * 1.8) + 32 );
			//O2TKhtrassytemp2[i].SetValue( ((O2temp[i] - 273.15) * 1.8) + 32 );

			H2TKqty[i].SetValue( 100 * (H2mass[i] / H2_TANK_MASS_CAP) );
			H2TKpress[i].SetValue( H2press[i] / PSI2PA );
			H2TKtemp[i].SetValue( ((H2temp[i] - 273.15) * 1.8) + 32 );
			//H2TKhtrcntrpress[i].SetValue( H2press[i] / PSI2PA );
			//H2TKhtrassytemp[i].SetValue( ((H2temp[i] - 273.15) * 1.8) + 32 );
		}
		return;
	}

	bool PRSD::OnParseLine( const char* line )
	{
		return vman.OnParseLine( line );
		/*char cbuf[16];

		if (vman.OnParseLine( line )) return true;
		else
		{
			for (int i = 0; i < sets; i++)
			{
				sprintf_s( cbuf, 16, "O2_TK%d", i + 1 );
				if (!_strnicmp( line, cbuf, strlen( cbuf ) ))
				{
					double m = 0;
					double p = 0;
					double t = 0;
					sscanf_s( line + 7, "%lf %lf %lf", &m, &p, &t );
					O2mass[i] = m;
					O2press[i] = p;
					O2temp[i] = t;
					return true;
				}
				else
				{
					sprintf_s( cbuf, 16, "H2_TK%d", i + 1 );
					if (!_strnicmp( line, cbuf, strlen( cbuf ) ))
					{
						double m = 0;
						double p = 0;
						double t = 0;
						sscanf_s( line + 7, "%lf %lf %lf", &m, &p, &t );
						H2mass[i] = m;
						H2press[i] = p;
						H2temp[i] = t;
						return true;
					}
				}
			}
			return false;
		}*/
	}

	void PRSD::OnSaveState( FILEHANDLE scn ) const
	{
		vman.OnSaveState( scn );

		/*char cbuf[16];
		char cbuf2[64];
		for (int i = 0; i < sets; i++)
		{
			sprintf_s( cbuf, 16, "O2_TK%d", i + 1 );
			sprintf_s( cbuf2, 64, "%.6f %.6f %.6f", O2mass[i], O2press[i], O2temp[i] );
			oapiWriteScenario_string( scn, cbuf, cbuf2 );

			sprintf_s( cbuf, 16, "H2_TK%d", i + 1 );
			sprintf_s( cbuf2, 64, "%.6f %.6f %.6f", H2mass[i], H2press[i], H2temp[i] );
			oapiWriteScenario_string( scn, cbuf, cbuf2 );
		}*/
		return;
	}

	double PRSD::GetSubsystemMass() const
	{
		double mass = (O2_TANK_DAY_MASS + H2_TANK_DAY_MASS) * sets;

		if (EDOhw)
		{
			mass += EDO_KIT_MASS;

			if (pallet == 1) mass += EDO_SINGLEPALLET_DRY_MASS;
			else if (pallet == 2) mass += EDO_DUALPALLET_DRY_MASS;
		}

		for (int i = 0; i < sets; i++) mass += (O2mass[i] + H2mass[i]) * 0.001;

		return mass;
	}

	double PRSD::Use( double flow, int source )
	{
		if (source == 1)
		{
			// O2 FC 1
			//FCO2Reac[0]->GetPos()
			return 0;
		}
		else if (source == 2)
		{
			// O2 FC 2
			//FCO2Reac[1]->GetPos()
			return 0;
		}
		else if (source == 3)
		{
			// O2 FC 3
			//FCO2Reac[2]->GetPos()
			return 0;
		}
		else if (source == 4)
		{
			// H2 FC 1
			//FCH2Reac[0]->GetPos()
			return 0;
		}
		else if (source == 5)
		{
			// H2 FC 2
			//FCH2Reac[1]->GetPos()
			return 0;
		}
		else if (source == 6)
		{
			// H2 FC 3
			//FCH2Reac[2]->GetPos()
			return 0;
		}
		else if (source == 7)
		{
			// O2 ECLSS 1
			//O2ECLSSSupply[0]->GetPos()
			return 0;
		}
		else if (source == 8)
		{
			// O2 ECLSS 2
			//O2ECLSSSupply[1]->GetPos()
			return 0;
		}
		else return 0;
	}
};
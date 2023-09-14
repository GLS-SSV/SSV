/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/03/29   GLS
2020/04/01   GLS
2020/04/07   GLS
2020/06/01   GLS
2020/06/12   GLS
2020/06/20   GLS
2020/06/21   GLS
2020/06/23   GLS
2021/06/28   GLS
2021/08/08   GLS
2021/08/10   GLS
2021/08/24   GLS
2021/12/09   GLS
2021/12/10   GLS
2021/12/30   GLS
2022/01/07   GLS
2022/01/08   GLS
2022/01/09   GLS
2022/03/24   GLS
2022/04/07   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/10/24   GLS
2022/11/16   GLS
2022/11/17   GLS
2023/09/14   GLS
********************************************/
// ==============================================================
//                 ORBITER MODULE: Atlantis
//                  Part of the ORBITER SDK
//          Copyright (C) 2001-2003 Martin Schweiger
//                   All rights reserved
//
// Atlantis_Tank.cpp
// Reference implementation of Atlantis Tank vessel class module
// Note: The propellant tanks associated with the ET are defined
// by the Atlantis class. This module is attached to the orbiter
// during launch and takes control of the tank after separation
// from the orbiter.
// ==============================================================

#define ORBITER_MODULE
#include "ET.h"
#include "meshres_SLWT.h"
#include "../OV/Atlantis.h"
#include "../CommonDefs.h"
#include <math.h>
#include <string>
#include <EngConst.h>


const static char* MESHNAME_SWT = "SSV\\ET\\SWT";
const static char* MESHNAME_LWT = "SSV\\ET\\LWT";
const static char* MESHNAME_SLWT = "SSV\\ET\\SLWT";

const static char* SCORCHED_TEXTURE_SUFFIX = "_SCORCHED";

// HACK assuming constant temperatures during powered flight, using values are at SSME exit minus 100K
constexpr double GOX_TEMPERATURE = 448.7056 - 100;// K
constexpr double GH2_TEMPERATURE = 255.3722 - 100;// K

// constants for van der waals equation
constexpr double O2_VDW_A = 0.1382;// Pa m^3
constexpr double O2_VDW_B = 0.0000319;// m^3/mol
constexpr double H2_VDW_A = 0.02452;// Pa m^3
constexpr double H2_VDW_B = 0.0000265;// m^3/mol

constexpr double LOX_TANK_VOLUME = 553.9625;// m^3
constexpr double LOX_MAX_VOLUME = 548.3434;// m^3
constexpr double LOX_MIN_ULLAGE_VOLUME = LOX_TANK_VOLUME - LOX_MAX_VOLUME;// m^3
constexpr double LH2_TANK_VOLUME = 1515.461;// m^3
constexpr double LH2_MAX_VOLUME = 1475.44;// m^3
constexpr double LH2_MIN_ULLAGE_VOLUME = LH2_TANK_VOLUME - LH2_MAX_VOLUME;// m^3

// empty mass
constexpr double SWT_EMPTY_MASS = 76000.0 * LBM2KG;//STS-1 to STS-5 tank 76000 lbs
constexpr double SWT_FRL_EMPTY_MASS = SWT_EMPTY_MASS + (600.0 * LBM2KG);// same as SWT plus FRL weight (>600 lbs)
constexpr double LWT_EMPTY_MASS = 66000.0 * LBM2KG;//Light weight tank 66000 lbs, STS-6 to STS-90
constexpr double SLWT_EMPTY_MASS = 58500.0 * LBM2KG;//Super light weight tank, 58500lbs, STS-91 on


// ==============================================================
// Specialised vessel class Atlantis_Tank
// ==============================================================

// Constructor
ET::ET( OBJHANDLE hObj ):VESSEL4( hObj ),
type(SLWT),useFRL(false),useBipodRamps(true),usePALRamps(true),
bUseScorchedTexture(false),
hTexture(NULL),hScorchedTexture(NULL),
LOXPct5LevelSensor( 5.0, 4.85, 0.0, 0.0, 28.0 ),
LOXPct98LevelSensor{Sensor( 98.0, 97.85, 0.0, 0.0, 28.0 ),Sensor( 98.0, 97.85, 0.0, 0.0, 28.0 )},
LOXPct100MinusLevelSensor( 99.85, 99.7, 0.0, 0.0, 28.0 ),
LOXPct100LevelSensor{Sensor( 100.0, 99.85, 0.0, 0.0, 28.0 ),Sensor( 100.0, 99.85, 0.0, 0.0, 28.0 )},
LOXPct100PlusLevelSensor( 100.15, 100.0, 0.0, 0.0, 28.0 ),
LOXOverfillLevelSensor( 101.0, 100.85, 0.0, 0.0, 28.0 ),
LH2LowLevelSensor{Sensor( 0.2, 0.05, 0.0, 0.0, 28.0 ),Sensor( 0.2, 0.05, 0.0, 0.0, 28.0 ),Sensor( 0.2, 0.05, 0.0, 0.0, 28.0 ),Sensor( 0.2, 0.05, 0.0, 0.0, 28.0 )},
LH2Pct5LevelSensor( 5.0, 4.85, 0.0, 0.0, 28.0 ),
LH2Pct98LevelSensor{Sensor( 98.0, 97.85, 0.0, 0.0, 28.0 ),Sensor( 98.0, 97.85, 0.0, 0.0, 28.0 )},
LH2Pct100MinusLevelSensor( 99.85, 99.7, 0.0, 0.0, 28.0 ),
LH2Pct100LevelSensor{Sensor( 100.0, 99.85, 0.0, 0.0, 28.0 ),Sensor( 100.0, 99.85, 0.0, 0.0, 28.0 )},
LH2Pct100PlusLevelSensor( 100.15, 100.0, 0.0, 0.0, 28.0 ),
LH2OverfillLevelSensor( 101.0, 100.85, 0.0, 0.0, 28.0 ),
LOXUllagePressureSensor{Sensor( 0.0, 30.0, 0.005, 0.028667 ),Sensor( 0.0, 30.0, 0.005, 0.028667 ),Sensor( 0.0, 30.0, 0.005, 0.028667 ),Sensor( 0.0, 30.0, 0.005, 0.028667 )},// ullage sensor error derived from data in SDH SLWT
LH2UllagePressureSensor{Sensor( 12.0, 52.0, 0.02, 0.025625 ),Sensor( 12.0, 52.0, 0.02, 0.025625 ),Sensor( 12.0, 52.0, 0.02, 0.025625 ),Sensor( 12.0, 52.0, 0.02, 0.025625 )}
{
	// preload mesh
	mesh_idx = MESH_UNDEFINED;

	sensorsconnected = false;
	postsep = false;
	GO2VentReliefValveOpen = false;
	GH2VentReliefValveOpen = false;
}

ET::~ET()
{
	if (hTexture) oapiReleaseTexture( hTexture );
	if (hScorchedTexture) oapiReleaseTexture( hScorchedTexture );
}

void ET::SetTexture( SURFHANDLE tex )
{
	if (!hDevTankMesh) return;// no mesh handle

	if (tex == NULL) throw std::exception( "Could not load ET texture" );

	if (!oapiSetTexture( hDevTankMesh, 1, tex ))
		oapiWriteLog( "(SSV_ET) [ERROR] Could not update texture" );
	return;
}

void ET::LoadTextures( void )
{
	if (hTexture == NULL) hTexture = oapiLoadTexture( strTextureName.c_str() );
	if (hTexture == NULL) throw std::exception( "Could not load ET texture" );

	std::string strScorchedTextureName = strTextureName;
	strScorchedTextureName.insert( strScorchedTextureName.length() - 4, SCORCHED_TEXTURE_SUFFIX );

	if (hScorchedTexture == NULL) hScorchedTexture = oapiLoadTexture( strScorchedTextureName.c_str() );
	if (hScorchedTexture == NULL) oapiWriteLogV( "(SSV_ET) [ERROR] Could not load ET scorched texture: %s", strScorchedTextureName.c_str() );
	return;
}

void ET::PropellantFlow( double& LOXmass, double& LH2mass )
{
	this->LOXmass -= LOXmass;
	if (this->LOXmass < 0)
	{
		LOXmass += this->LOXmass;
		this->LOXmass = 0;
	}

	this->LH2mass -= LH2mass;
	if (this->LH2mass < 0)
	{
		LH2mass += this->LH2mass;
		this->LH2mass = 0;
	}

	SetPropellantMass( phET, this->LOXmass + this->LH2mass );
	return;
}

void ET::PressurantFlow( double GOXmass, double GH2mass )
{
	// HACK take the masses directly from the ET, as it's more simple and the small error this
	// gives only appear when ET is empty (just before MECO on rare occasions)
	PropellantFlow( GOXmass, GH2mass );

	// add masses (put ullage mass as emtpy mass)
	SetEmptyMass( GetEmptyMass() + GOXmass + GH2mass );

	this->GOXmass += GOXmass * 1000;
	this->GH2mass += GH2mass * 1000;
	return;
}

double ET::GetPropellantLevel( void ) const
{
	return 100.0 * (GetPropellantMass( phET ) / TANK_MAX_PROPELLANT_MASS);
}

double ET::GetLOXUllagePressure( void ) const
{
	return LOXullagepress;
}

double ET::GetLH2UllagePressure( void ) const
{
	return LH2ullagepress;
}

// ==============================================================
// Callback functions
// ==============================================================

// Set Tank class specs
void ET::clbkSetClassCaps (FILEHANDLE cfg)
{
	try
	{
		SetEnableFocus (false);
		// Tank cannot receive input focus

		SetSize (24.0);

		phET = CreatePropellantResource( TANK_MAX_PROPELLANT_MASS );

		SetCW (0.2, 0.3, 1.2, 1.2);
		VECTOR3 cs = {412.1,411.8,72.7};
		SetCrossSections (cs);
		VECTOR3 rd = {0.5,0.5,0.1};
		SetRotDrag (rd);
		VECTOR3 pmi = {145.6,145.6,10.5};
		SetPMI (pmi);
		SetPitchMomentScale (1e-4);
		SetYawMomentScale( 1e-4 );
		SetLiftCoeffFunc (0);

		DWORD ntdvtx = 4;
		static TOUCHDOWNVTX tdvtx[4] = {
			{_V( 0.0, 7.5, -20.0 ), 1e5, 1e2, 0.5, 0.005},
			{_V( 7.5, -3.5, -20.0 ), 1e5, 1e2, 0.5, 0.005},
			{_V( -7.5, -3.5, -20.0 ), 1e5, 1e2, 0.5, 0.005},
			{_V( 0.0, 0.0, 35.0 ), 1e5, 1e2, 0.5}
		};
		SetTouchdownPoints( tdvtx, ntdvtx );

		// vents (initially with very high ISP so it uses little prop)
		// LOX
		thGOXventNE = CreateThruster( _V( -0.4956, 0.0939, 29.5129 ), _V( -0.724098, 0.224951, 0.651981 ), 600, phET, 99999999, 99999999 );
		thGOXventSW = CreateThruster( _V( 0.3767, 0.3645, 29.5129 ), _V( 0.494864, -0.574482, 0.651981 ), 600, phET, 99999999, 99999999 );
		PARTICLESTREAMSPEC psGOXvent = {
			0,
			0.1,
			50,
			20,
			0.1,
			0.4,
			6,
			5,
			PARTICLESTREAMSPEC::DIFFUSE,
			PARTICLESTREAMSPEC::LVL_PLIN,
			0, 1,
			PARTICLESTREAMSPEC::ATM_FLAT,
			1, 1,
			0};
		AddExhaustStream( thGOXventNE, &psGOXvent );
		AddExhaustStream( thGOXventSW, &psGOXvent );

		// LH2
		thGH2vent = CreateThruster( _V( -3.6378, -2.1712, 12.1898 ), _V( 0.866025, 0.5, 0.0 ), 600, phET, 99999999, 99999999 );
		PARTICLESTREAMSPEC psGH2vent = {
			0,
			0.1,
			50,
			20,
			0,
			0.5,
			20,
			5,
			PARTICLESTREAMSPEC::DIFFUSE,
			PARTICLESTREAMSPEC::LVL_PLIN,
			0, 1,
			PARTICLESTREAMSPEC::ATM_FLAT,
			1, 1,
			0};
		AddExhaustStream( thGH2vent, &psGH2vent );

		ahToOrbiter = CreateAttachment(true, _V(0, 0.0, 0.0), _V(0, -1, 0), _V(0, 0, 1), "SSV_ET");
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_ET) [FATAL ERROR] Exception in ET::clbkSetClassCaps: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_ET) [FATAL ERROR] Exception in ET::clbkSetClassCaps" );
		abort();
	}
}

// Simulation time step
void ET::clbkPostStep (double simt, double simdt, double mjd)
{
	try
	{
		if (sensorsconnected == false)
		{
			// connect sensors
			OBJHANDLE hOV = GetAttachmentStatus( ahToOrbiter );

			if (hOV != NULL)
			{
				Atlantis* OV = static_cast<Atlantis*> (oapiGetVesselInterface( hOV ));

				DiscreteBundle *pBundle = OV->BundleManager()->CreateBundle( "ET_LOX_SENSORS", 16 );
				LOXPct5LevelSensor.Connect( pBundle, 4 );
				LOXPct98LevelSensor[0].Connect( pBundle, 5 );
				LOXPct98LevelSensor[1].Connect( pBundle, 6 );
				LOXPct100MinusLevelSensor.Connect( pBundle, 7 );
				LOXPct100LevelSensor[0].Connect( pBundle, 8 );
				LOXPct100LevelSensor[1].Connect( pBundle, 9 );
				LOXPct100PlusLevelSensor.Connect( pBundle, 10 );
				LOXOverfillLevelSensor.Connect( pBundle, 11 );
				LOXUllagePressureSensor[0].Connect( pBundle, 12 );
				LOXUllagePressureSensor[1].Connect( pBundle, 13 );
				LOXUllagePressureSensor[2].Connect( pBundle, 14 );
				LOXUllagePressureSensor[3].Connect( pBundle, 15 );

				pBundle = OV->BundleManager()->CreateBundle( "ET_LH2_SENSORS", 16 );
				LH2LowLevelSensor[0].Connect( pBundle, 0 );
				LH2LowLevelSensor[1].Connect( pBundle, 1 );
				LH2LowLevelSensor[2].Connect( pBundle, 2 );
				LH2LowLevelSensor[3].Connect( pBundle, 3 );
				LH2Pct5LevelSensor.Connect( pBundle, 4 );
				LH2Pct98LevelSensor[0].Connect( pBundle, 5 );
				LH2Pct98LevelSensor[1].Connect( pBundle, 6 );
				LH2Pct100MinusLevelSensor.Connect( pBundle, 7 );
				LH2Pct100LevelSensor[0].Connect( pBundle, 8 );
				LH2Pct100LevelSensor[1].Connect( pBundle, 9 );
				LH2Pct100PlusLevelSensor.Connect( pBundle, 10 );
				LH2OverfillLevelSensor.Connect( pBundle, 11 );
				LH2UllagePressureSensor[0].Connect( pBundle, 12 );
				LH2UllagePressureSensor[1].Connect( pBundle, 13 );
				LH2UllagePressureSensor[2].Connect( pBundle, 14 );
				LH2UllagePressureSensor[3].Connect( pBundle, 15 );

				sensorsconnected = true;
			}
		}

		double LOXullagevol = ((1 - (LOXmass / LOX_MAX_PROPELLANT_MASS)) * LOX_MAX_VOLUME) + LOX_MIN_ULLAGE_VOLUME;
		double LH2ullagevol = ((1 - (LH2mass / LH2_MAX_PROPELLANT_MASS)) * LH2_MAX_VOLUME) + LH2_MIN_ULLAGE_VOLUME;

		// using van der waals now as it's easy to solve for pressure
		LOXullagepress = ((GOXmass * 8.314 * GOX_TEMPERATURE) / ((15.999 * LOXullagevol) - (GOXmass * O2_VDW_B))) - ((GOXmass * GOXmass * O2_VDW_A) / (15.999 * 15.999 * LOXullagevol * LOXullagevol));
		LH2ullagepress = ((GH2mass * 8.314 * GH2_TEMPERATURE) / ((1.008 * LH2ullagevol) - (GH2mass * H2_VDW_B))) - ((GH2mass * GH2mass * H2_VDW_A) / (1.008 * 1.008 * LH2ullagevol * LH2ullagevol));

		UpdateSensors();

		// vent/relief valves
		// HACK far from perfect but should only be used post sep, and only few care about the ET by then
		// GOX
		if (GO2VentReliefValveOpen == true)// opens at 31psig, closes at 29psig
		{// HACK using psia for now
			// check if should close
			if ((LOXullagepress / PSI2PA) < 43.7)
			{
				GO2VentReliefValveOpen = false;
				// close
				SetThrusterLevel( thGOXventNE, 0 );
				SetThrusterLevel( thGOXventSW, 0 );
			}
			else
			{
				// keep open
				SetThrusterLevel( thGOXventNE, min( (LOXullagepress / PSI2PA) - 45, 1 ) );
				SetThrusterLevel( thGOXventSW, min( (LOXullagepress / PSI2PA) - 45, 1 ) );
				// decrease mass
				GOXmass -= 6000 * simdt;
			}
		}
		else
		{
			// check if should open
			if ((LOXullagepress / PSI2PA) > 45.7)
			{
				GO2VentReliefValveOpen = true;
				// open
				SetThrusterLevel( thGOXventNE, min( (LOXullagepress / PSI2PA) - 45, 1 ) );
				SetThrusterLevel( thGOXventSW, min( (LOXullagepress / PSI2PA) - 45, 1 ) );
				// decrease mass
				GOXmass -= 6000 * simdt;
			}
			else
			{
				// keep closed
				SetThrusterLevel( thGOXventNE, 0 );
				SetThrusterLevel( thGOXventSW, 0 );
			}
		}

		// GH2
		if (GH2VentReliefValveOpen == true)// opens at 50.7psia, closes at 48.7psia
		{
			// check if should close
			if ((LH2ullagepress / PSI2PA) < 48.7)
			{
				GH2VentReliefValveOpen = false;
				// close
				SetThrusterLevel( thGH2vent, 0 );
			}
			else
			{
				// keep open
				SetThrusterLevel( thGH2vent, min( (LH2ullagepress / PSI2PA) - 48, 1 ) );
				// decrease mass
				GH2mass -= 2000 * simdt;
			}
		}
		else
		{
			// check if should open
			if ((LH2ullagepress / PSI2PA) > 50.7)
			{
				GH2VentReliefValveOpen = true;
				// open
				SetThrusterLevel( thGH2vent, min( (LH2ullagepress / PSI2PA) - 48.7, 1 ) );
				// decrease mass
				GH2mass -= 2000 * simdt;
			}
			else
			{
				// keep closed
				SetThrusterLevel( thGH2vent, 0 );
			}
		}

		// post sep "reconfigure"
		if (!GetAttachmentStatus(ahToOrbiter))
		{
			if (GetAltitude() < 0.0) oapiDeleteVessel (GetHandle());

			if (postsep == false)// runs once after sep
			{
				// add ullage mass back to propellant resource to be used for venting
				SetPropellantMass( phET, GetPropellantMass( phET ) + ((GOXmass + GH2mass) / 1000) );
				SetEmptyMass( GetEmptyMass() - ((GOXmass + GH2mass) / 1000) );

				// change vent isp to sane values
				SetThrusterIsp( thGOXventNE, 100, 100 );
				SetThrusterIsp( thGOXventSW, 100, 100 );
				SetThrusterIsp( thGH2vent, 300, 300 );

				// disconnect sensors
				LOXPct5LevelSensor.Disconnect();
				LOXPct98LevelSensor[0].Disconnect();
				LOXPct98LevelSensor[1].Disconnect();
				LOXPct100MinusLevelSensor.Disconnect();
				LOXPct100LevelSensor[0].Disconnect();
				LOXPct100LevelSensor[1].Disconnect();
				LOXPct100PlusLevelSensor.Disconnect();
				LOXOverfillLevelSensor.Disconnect();
				LOXUllagePressureSensor[0].Disconnect();
				LOXUllagePressureSensor[1].Disconnect();
				LOXUllagePressureSensor[2].Disconnect();
				LOXUllagePressureSensor[3].Disconnect();
				LH2LowLevelSensor[0].Disconnect();
				LH2LowLevelSensor[1].Disconnect();
				LH2LowLevelSensor[2].Disconnect();
				LH2LowLevelSensor[3].Disconnect();
				LH2Pct5LevelSensor.Disconnect();
				LH2Pct98LevelSensor[0].Disconnect();
				LH2Pct98LevelSensor[1].Disconnect();
				LH2Pct100MinusLevelSensor.Disconnect();
				LH2Pct100LevelSensor[0].Disconnect();
				LH2Pct100LevelSensor[1].Disconnect();
				LH2Pct100PlusLevelSensor.Disconnect();
				LH2OverfillLevelSensor.Disconnect();
				LH2UllagePressureSensor[0].Disconnect();
				LH2UllagePressureSensor[1].Disconnect();
				LH2UllagePressureSensor[2].Disconnect();
				LH2UllagePressureSensor[3].Disconnect();

				postsep = true;
			}

			// "vaporize" 0.6Kg/s LOX mass remaining and 0.9Kg/s LH2
			double tmp = 0.6 * oapiRand() * simdt;
			if ((LOXmass - tmp) < 0)
			{
				GOXmass += LOXmass * 1000;
				LOXmass = 0;
			}
			else
			{
				GOXmass += tmp * 1000;
				LOXmass -= tmp;
			}

			tmp = 0.9 * oapiRand() * simdt;
			if ((LH2mass - tmp) < 0)
			{
				GH2mass += LH2mass * 1000;
				LH2mass = 0;
			}
			else
			{
				GH2mass += tmp * 1000;
				LH2mass -= tmp;
			}
		}
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_ET) [FATAL ERROR] Exception in ET::clbkPostStep: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_ET) [FATAL ERROR] Exception in ET::clbkPostStep" );
		abort();
	}
}

void ET::UpdateSensors( void )
{
	// LOX
	double lvl = 100 * LOXmass / LOX_MAX_PROPELLANT_MASS;
	LOXPct5LevelSensor.SetValue( lvl );
	LOXPct98LevelSensor[0].SetValue( lvl );
	LOXPct98LevelSensor[1].SetValue( lvl );
	LOXPct100MinusLevelSensor.SetValue( lvl );
	LOXPct100LevelSensor[0].SetValue( lvl );
	LOXPct100LevelSensor[1].SetValue( lvl );
	LOXPct100PlusLevelSensor.SetValue( lvl );
	LOXOverfillLevelSensor.SetValue( lvl );
	LOXUllagePressureSensor[0].SetValue( (LOXullagepress / PSI2PA) - 14.7 );
	LOXUllagePressureSensor[1].SetValue( (LOXullagepress / PSI2PA) - 14.7 );
	LOXUllagePressureSensor[2].SetValue( (LOXullagepress / PSI2PA) - 14.7 );
	LOXUllagePressureSensor[3].SetValue( (LOXullagepress / PSI2PA) - 14.7 );

	// LH2
	lvl = 100 * LH2mass / LH2_MAX_PROPELLANT_MASS;
	LH2LowLevelSensor[0].SetValue( lvl );
	LH2LowLevelSensor[1].SetValue( lvl );
	LH2LowLevelSensor[2].SetValue( lvl );
	LH2LowLevelSensor[3].SetValue( lvl );
	LH2Pct5LevelSensor.SetValue( lvl );
	LH2Pct98LevelSensor[0].SetValue( lvl );
	LH2Pct98LevelSensor[1].SetValue( lvl );
	LH2Pct100MinusLevelSensor.SetValue( lvl );
	LH2Pct100LevelSensor[0].SetValue( lvl );
	LH2Pct100LevelSensor[1].SetValue( lvl );
	LH2Pct100PlusLevelSensor.SetValue( lvl );
	LH2OverfillLevelSensor.SetValue( lvl );
	LH2UllagePressureSensor[0].SetValue( LH2ullagepress / PSI2PA );
	LH2UllagePressureSensor[1].SetValue( LH2ullagepress / PSI2PA );
	LH2UllagePressureSensor[2].SetValue( LH2ullagepress / PSI2PA );
	LH2UllagePressureSensor[3].SetValue( LH2ullagepress / PSI2PA );
	return;
}

void ET::clbkLoadStateEx( FILEHANDLE scn, void* status )
{
	try
	{
		char* line;

		while (oapiReadScenario_nextline( scn, line ))
		{
			if (!_strnicmp( line, "MISSION", 7 ))
			{
				strMission = line + 8;
				LoadMissionFile();

				SetConfiguration();
			}
			else if (!_strnicmp( line, "SCORCHED", 8 ))
			{
				bUseScorchedTexture = true;
			}
			else ParseScenarioLineEx( line, status );
		}
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_ET) [FATAL ERROR] Exception in ET::clbkLoadStateEx: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_ET) [FATAL ERROR] Exception in ET::clbkLoadStateEx" );
		abort();
	}
}

void ET::clbkSaveState(FILEHANDLE scn)
{
	try
	{
		VESSEL4::clbkSaveState(scn);
		if (strMission.length() > 0) oapiWriteScenario_string( scn, "MISSION", (char*)strMission.c_str() );
		if (bUseScorchedTexture) oapiWriteLine( scn, "  SCORCHED" );
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_ET) [FATAL ERROR] Exception in ET::clbkSaveState: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_ET) [FATAL ERROR] Exception in ET::clbkSaveState" );
		abort();
	}
}

void ET::clbkPostCreation( void )
{
	try
	{
		// use prop level just loaded from the .scn to finish lox/lh2 mass setup
		// HACK always assuming post pre-press conditions
		double lvl = GetPropellantMass( phET ) / TANK_MAX_PROPELLANT_MASS;

		LOXmass = lvl * LOX_MAX_PROPELLANT_MASS;
		LH2mass = lvl * LH2_MAX_PROPELLANT_MASS;

		LOXullagepress = 35.7 * PSI2PA;// Pa pre-press 21+14.7=35.7 psia, in flight 20-25psig (34.7-39.7psia), relief at 31psig (45.7psia)
		LH2ullagepress = 47 * PSI2PA;// Pa pre-press 47 psia, in flight 32.8-33.2psia, relief at 36psig (50.7psia)

		// initially use the pressures above and derive GH2/GOX mass
		// HACK using the ideal gas equation because the van der waals is a little hardcore to solve for mass
		double LOXullagevol = ((1 - lvl) * LOX_MAX_VOLUME) + LOX_MIN_ULLAGE_VOLUME;
		double LH2ullagevol = ((1 - lvl) * LH2_MAX_VOLUME) + LH2_MIN_ULLAGE_VOLUME;

		GOXmass = (LOXullagepress * LOXullagevol * 15.999) / (8.314 * GOX_TEMPERATURE);
		GH2mass = (LH2ullagepress * LH2ullagevol * 1.008) / (8.314 * GH2_TEMPERATURE);

		SetEmptyMass( GetEmptyMass() + ((GOXmass + GH2mass) / 1000) );
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_ET) [FATAL ERROR] Exception in ET::clbkPostCreation: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_ET) [FATAL ERROR] Exception in ET::clbkPostCreation" );
		abort();
	}
}

void ET::clbkVisualCreated(VISHANDLE vis, int refcount)
{
	try
	{
		hVis = vis;

		hDevTankMesh = GetDevMesh(vis, mesh_idx);

		if (!strTextureName.empty()) LoadTextures();

		if (bUseScorchedTexture)
		{
			if (hScorchedTexture) SetTexture( hScorchedTexture );
			else
			{
				oapiWriteLog( "(SSV_ET) INFO: No ET scorched texture available" );
				SetTexture( hTexture );// load default
			}
		}
		else
		{
			SetTexture( hTexture );
		}

		// if SLWT, handle bipod and PAL ramps visibility
		if (type == SLWT)
		{
			GROUPEDITSPEC grpSpec;
			grpSpec.flags = GRPEDIT_SETUSERFLAG;
			grpSpec.UsrFlag = 0x00000003;// hide group and shadow

			if (!useBipodRamps)
			{
				oapiWriteLog( "(SSV_ET) [INFO] Hiding Bipod ramps" );
				oapiEditMeshGroup( hDevTankMesh, GRP_BIPOD_FOAM_RAMPS_SLWT, &grpSpec );
			}
			if (!usePALRamps)
			{
				oapiWriteLog( "(SSV_ET) [INFO] Hiding PAL ramps" );
				oapiEditMeshGroup( hDevTankMesh, GRP_LH2_PAL_RAMP_SLWT, &grpSpec );
				oapiEditMeshGroup( hDevTankMesh, GRP_LOX_PAL_RAMP_SLWT, &grpSpec );
			}
		}
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_ET) [FATAL ERROR] Exception in ET::clbkVisualCreated: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_ET) [FATAL ERROR] Exception in ET::clbkVisualCreated" );
		abort();
	}
}

void ET::clbkVisualDestroyed(VISHANDLE vis, int refcount)
{
	try
	{
		if (vis == hVis)
		{
			hVis = NULL;
			hDevTankMesh = NULL;
		}
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_ET) [FATAL ERROR] Exception in ET::clbkVisualDestroyed: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_ET) [FATAL ERROR] Exception in ET::clbkVisualDestroyed" );
		abort();
	}
}

int ET::clbkGeneric( int msgid, int prm, void* context )
{
	if (msgid == (VMSG_USER + 0x0001))
	{
		bUseScorchedTexture = true;
		if (hScorchedTexture) SetTexture( hScorchedTexture );
		else oapiWriteLog( "(SSV_ET) INFO: No ET scorched texture available" );
	}
	return 0;
}

void ET::LoadMissionFile( void )
{
	std::string filename;
	filename = "Missions\\SSV\\" + strMission + ".json";

	FILE* hF = fopen( filename.c_str(), "r" );
	if (hF == NULL)
	{
		oapiWriteLogV( "(SSV_ET) [ERROR] Can't open mission file %s", strMission.c_str() );
		return;
	}

	oapiWriteLogV( "(SSV_ET) [INFO] Loading mission file %s", strMission.c_str() );

	fseek( hF, 0, SEEK_END );
	long filesize = ftell( hF );
	if (filesize < 0)
	{
		fclose( hF );
		return;
	}

	char* missionfilestr = new char[filesize];
	rewind( hF );
	fread( missionfilestr, sizeof(char), filesize, hF );
	fclose( hF );

	cJSON* root = cJSON_Parse( missionfilestr );
	if (!root)
	{
		oapiWriteLog( "(SSV_ET) [ERROR] Error parsing mission file version" );
		delete[] missionfilestr;
		return;
	}

	cJSON* version = cJSON_GetObjectItemCaseSensitive( root, "Version" );
	switch (version->valueint)
	{
		case 2:// unchanged from V1
			LoadMissionV1( root );
			break;
		default:
			oapiWriteLogV( "(SSV_ET) [ERROR] Unknown mission file version %d", version->valueint );
			break;
	}

	cJSON_Delete( root );
	delete[] missionfilestr;
	return;
}

void ET::LoadMissionV1( cJSON* root )
{
	// read ExternalTank
	cJSON* et = cJSON_GetObjectItemCaseSensitive( root, "External Tank" );

	cJSON* tmp = cJSON_GetObjectItemCaseSensitive( et, "Type" );
	if (!strcmp( "SWT", tmp->valuestring ))
	{
		type = SWT;
	}
	else if (!strcmp( "LWT", tmp->valuestring ))
	{
		type = LWT;
	}
	else //if (!strcmp( "SLWT", tmp->valuestring ))
	{
		type = SLWT;
	}

	tmp = cJSON_GetObjectItemCaseSensitive( et, "Texture" );
	strTextureName = "SSV\\ET\\" + std::string( tmp->valuestring ) + ".dds";

	tmp = cJSON_GetObjectItemCaseSensitive( et, "FRL" );
	useFRL = cJSON_IsTrue( tmp );

	tmp = cJSON_GetObjectItemCaseSensitive( et, "Bipod Ramps" );
	useBipodRamps = cJSON_IsTrue( tmp );

	tmp = cJSON_GetObjectItemCaseSensitive( et, "PAL Ramps" );
	usePALRamps = cJSON_IsTrue( tmp );
	return;
}

void ET::SetConfiguration( void )
{
	if (type == SWT)
	{
		if (useFRL) SetEmptyMass( SWT_FRL_EMPTY_MASS );
		else SetEmptyMass( SWT_EMPTY_MASS );
		hTankMesh = oapiLoadMeshGlobal( MESHNAME_SWT );
	}
	else if (type == LWT)
	{
		SetEmptyMass( LWT_EMPTY_MASS );
		hTankMesh = oapiLoadMeshGlobal( MESHNAME_LWT );
	}
	else// if (type == SLWT)
	{
		// default to SLWT tank
		SetEmptyMass( SLWT_EMPTY_MASS );
		hTankMesh = oapiLoadMeshGlobal( MESHNAME_SLWT );
	}

	mesh_idx = AddMesh( hTankMesh );
	return;
}

// ==============================================================
// API interface
// ==============================================================

// Initialisation
DLLCLBK VESSEL *ovcInit (OBJHANDLE hvessel, int flightmodel)
{
	try
	{
		return new ET( hvessel );
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_ET) [FATAL ERROR] Exception in ovcInit: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_ET) [FATAL ERROR] Exception in ovcInit" );
		abort();
	}
}

// Cleanup
DLLCLBK void ovcExit (VESSEL *vessel)
{
	try
	{
		if (vessel) delete static_cast<ET*>(vessel);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_ET) [FATAL ERROR] Exception in ovcExit: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_ET) [FATAL ERROR] Exception in ovcExit" );
		abort();
	}
}

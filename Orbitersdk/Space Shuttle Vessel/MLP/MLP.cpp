/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/03/29   GLS
2020/04/01   GLS
2020/05/07   GLS
2020/05/08   GLS
2020/06/01   GLS
2020/06/12   GLS
2020/06/20   GLS
2020/06/21   GLS
2020/06/23   GLS
2020/08/04   GLS
2021/06/14   GLS
2021/06/18   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/13   GLS
2021/12/26   GLS
2022/01/07   GLS
2022/01/09   GLS
2022/01/10   GLS
2022/02/20   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "MLP.h"
#include "../CommonDefs.h"
#include "meshres_MLP.h"
#include "../OV/Atlantis.h"
#include "../LC39/LC39.h"
#include "../T0UmbilicalReference.h"
#include "../MLPPadInterface.h"
#include <cstdio>

#define ORBITER_MODULE


const double TSM_UMBILICAL_RETRACT_SPEED = 1.181;// sec

const VECTOR3 HDP_POS = _V( 0.0, 8.06036, -6.649195 );


MLP::MLP(OBJHANDLE hVessel, int iFlightModel)
: VESSEL4(hVessel, iFlightModel)
{
	mshMLP = oapiLoadMeshGlobal("SSV\\MLP\\MLP");

	ahHDP = NULL;
	ahBase = NULL;

	vis=NULL;

	SRBwaterbagsteam_lvl = 0.0;

	pSTS = NULL;
	pPad = NULL;

	HBOIOn = false;
	HBOILevel = 0.0;
	HBOITime = 8.0 + (oapiRand() * 5.0);
}

MLP::~MLP()
{
	delete LeftT0Umb;
	delete RightT0Umb;
	delete LeftT0UmbCover;
	delete RightT0UmbCover;
}

void MLP::clbkSetClassCaps(FILEHANDLE cfg)
{
	try
	{
		SetSize(25.0);
		SetEmptyMass(4.1957075E6);
		msh_idx=AddMesh(mshMLP);

		DefineAnimations();
		DefineHBOIs();
		DefineSRBWaterBagSteam();

		// touchdown points: -30.84 on y for pad, -16.25 for VAB; must set touchdown points to match pad height so shuttle stack has correct touchdown points at liftoff
		DWORD ntdvtx = 4;
		static TOUCHDOWNVTX tdvtx[4] = {
			{_V( 0.0, -30.84, 25.0 ), 1e8, 1e2, 5, 5},
			{_V( -25.0, -30.84, -25.0 ), 1e8, 1e2, 5, 5},
			{_V( 25.0, -30.84, -25.0 ), 1e8, 1e2, 5, 5},
			{_V( 0, 10, 0 ), 1e8, 1e2, 5}
		};
		SetTouchdownPoints( tdvtx, ntdvtx );

		if(!ahHDP)	{
			ahHDP = CreateAttachment(false, HDP_POS, _V(0.0, 1.0, 0.0), _V(0.0, 0.0, -1.0), "XHDP");
		}

		if(!ahBase) {
			ahBase = CreateAttachment(true, _V(0, 0, 0.0), _V(0, 1, 0), _V(0, 0, 1), "XMLP");
		}
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_MLP) [FATAL ERROR] Exception in MLP::clbkSetClassCaps: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_MLP) [FATAL ERROR] Exception in MLP::clbkSetClassCaps" );
		abort();
	}
}

void MLP::clbkPostCreation( void )
{
	try
	{
		// get pointer to T0UmbilicalReference
		OBJHANDLE hSTS = GetAttachmentStatus( ahHDP );
		if (hSTS != NULL)
		{
			VESSEL* pVessel = oapiGetVesselInterface( hSTS );
			if (pVessel != NULL)
			{
				if (!_strnicmp( pVessel->GetClassName(), "SSV_OV", 6 ))
				{
					pSTS = (static_cast<Atlantis*>(pVessel))->T0UmbRef();
					oapiWriteLog( "(SSV_MLP) [INFO] Connected to T0UmbilicalReference" );
				}
			}
		}

		// get pointer to MLPPadInterface
		OBJHANDLE hPad = GetAttachmentStatus( ahBase );
		if (hPad != NULL)
		{
			VESSEL* pVessel = oapiGetVesselInterface( hPad );
			if (pVessel != NULL)
			{
				if (!_strnicmp( pVessel->GetClassName(), "SSV_LC39", 7 ))
				{
					pPad = static_cast<LC39*>(pVessel);
					oapiWriteLog( "(SSV_MLP) [INFO] Connected to MLPPadInterface" );
				}
			}
		}

		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_MLP) [FATAL ERROR] Exception in MLP::clbkPostCreation: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_MLP) [FATAL ERROR] Exception in MLP::clbkPostCreation" );
		abort();
	}
}

void MLP::clbkSaveState( FILEHANDLE scn )
{
	try
	{
		VESSEL4::clbkSaveState( scn );

		if (strMission.length() > 0) oapiWriteScenario_string( scn, "MISSION", (char*)strMission.c_str() );

		if (HBOIOn) oapiWriteScenario_float( scn, "HBOI", HBOITime );

		WriteScenario_state(scn, "T0_UMB", T0Umbilical_State);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_MLP) [FATAL ERROR] Exception in MLP::clbkSaveState: %s", e.what() );
		abort();
	}

	catch (...)
	{
		oapiWriteLog( "(SSV_MLP) [FATAL ERROR] Exception in MLP::clbkSaveState" );
		abort();
	}
}

void MLP::clbkLoadStateEx( FILEHANDLE scn, void* status )
{
	try
	{
		char* line;
		while(oapiReadScenario_nextline(scn, line))
		{
			if (!_strnicmp( line, "MISSION", 7 ))
			{
				strMission = line + 8;
				// TODO load mission file
			}
			else if (!_strnicmp( line, "HBOI", 4 ))
			{
				sscanf_s( line + 4, "%lf", &HBOITime );
				HBOIOn = true;
			}
			else if (!_strnicmp( line, "T0_UMB", 6 ))
			{
				sscan_state( line + 6, T0Umbilical_State );
				SetAnimation( anim_t0umb, T0Umbilical_State.pos );
			}
			else ParseScenarioLineEx(line, status);
		}
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_MLP) [FATAL ERROR] Exception in MLP::clbkLoadStateEx: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_MLP) [FATAL ERROR] Exception in MLP::clbkLoadStateEx" );
		abort();
	}
}

void MLP::clbkPreStep(double simt, double simdt, double mjd)
{
	try
	{
		if (T0Umbilical_State.Moving()) {
			double dp=simdt*TSM_UMBILICAL_RETRACT_SPEED;
			T0Umbilical_State.Move(dp);
			SetAnimation(anim_t0umb, T0Umbilical_State.pos);
		}

		// HBOI operation
		if (HBOIOn)
		{
			HBOITime -= simdt;
			if (HBOITime <= 0.0)
			{
				HBOIOn = false;
				HBOILevel = 0.0;
			}
			else HBOILevel = 1.0;
		}

		if (SRBwaterbagsteam_lvl > 0.0) SRBwaterbagsteam_lvl -= 0.05;
		else SRBwaterbagsteam_lvl = 0.0;

		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_MLP) [FATAL ERROR] Exception in MLP::clbkPreStep: %s", e.what() );
		abort();
	}

	catch (...)
	{
		oapiWriteLog( "(SSV_MLP) [FATAL ERROR] Exception in MLP::clbkPreStep" );
		abort();
	}
}

void MLP::clbkVisualCreated( VISHANDLE vis, int refcount )
{
	try
	{
		this->vis = vis;

		if (T0Umbilical_State.Closed()) HideSRBWaterBags( vis );
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_MLP) [FATAL ERROR] Exception in MLP::clbkVisualCreated: %s", e.what() );
		abort();
	}

	catch (...)
	{
		oapiWriteLog( "(SSV_MLP) [FATAL ERROR] Exception in MLP::clbkVisualCreated" );
		abort();
	}
}

void MLP::clbkVisualDestroyed( VISHANDLE vis, int refcount )
{
	try
	{
		if(this->vis == vis) this->vis = NULL;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_MLP) [FATAL ERROR] Exception in MLP::clbkVisualDestroyed: %s", e.what() );
		abort();
	}

	catch (...)
	{
		oapiWriteLog( "(SSV_MLP) [FATAL ERROR] Exception in MLP::clbkVisualDestroyed" );
		abort();
	}
}

DLLCLBK VESSEL* ovcInit(OBJHANDLE vessel, int flightmodel)
{
	try
	{
		return new MLP(vessel, flightmodel);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_MLP) [FATAL ERROR] Exception in ovcInit: %s", e.what() );
		abort();
	}

	catch (...)
	{
		oapiWriteLog( "(SSV_MLP) [FATAL ERROR] Exception in ovcInit" );
		abort();
	}
}

DLLCLBK void ovcExit(VESSEL* vessel)
{
	try
	{
		if (vessel) delete static_cast<MLP*>(vessel);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_MLP) [FATAL ERROR] Exception in ovcExit: %s", e.what() );
		abort();
	}

	catch (...)
	{
		oapiWriteLog( "(SSV_MLP) [FATAL ERROR] Exception in ovcExit" );
		abort();
	}
}

void MLP::DefineHBOIs( void )
{
	const VECTOR3 FWD_LEFT_HBOI_POS = _V( -4.12067, 10.4461, -16.8715 );
	const VECTOR3 FWD_RIGHT_HBOI_POS = _V( 4.12067, 10.4461, -16.8715 );
	const VECTOR3 AFT_LEFT_HBOI_POS = _V( -4.37152, 10.007, -13.1899 );
	const VECTOR3 AFT_LEFT_HBOI2_POS = _V( -4.37797, 10.0302, -13.3145 );
	const VECTOR3 AFT_RIGHT_HBOI_POS = _V( 4.37152, 10.007, -13.1899 );
	const VECTOR3 AFT_RIGHT_HBOI2_POS = _V( 4.37797, 10.0302, -13.3145 );

	static PARTICLESTREAMSPEC HBOI_Stream = {
		0, 0.1, 300.0, 17.5, 0.2, 0.25, 0, 0.5, PARTICLESTREAMSPEC::EMISSIVE,
		PARTICLESTREAMSPEC::LVL_FLAT, 1, 1,
		PARTICLESTREAMSPEC::ATM_FLAT, 1, 1
	};
	HBOI_Stream.tex = oapiRegisterParticleTexture("contrail3");

	AddParticleStream( &HBOI_Stream, FWD_LEFT_HBOI_POS, _V( 0.985, 0.0, -0.174 ), &HBOILevel );
	AddParticleStream( &HBOI_Stream, FWD_RIGHT_HBOI_POS, _V( -0.985, 0.0, -0.174 ), &HBOILevel );
	AddParticleStream( &HBOI_Stream, AFT_LEFT_HBOI_POS, _V( 1.0, 0.0, 0.0 ), &HBOILevel );
	AddParticleStream( &HBOI_Stream, AFT_LEFT_HBOI2_POS, _V( 0.985, 0.0, -0.174 ), &HBOILevel );
	AddParticleStream( &HBOI_Stream, AFT_RIGHT_HBOI_POS, _V( -1.0, 0.0, 0.0 ), &HBOILevel );
	AddParticleStream( &HBOI_Stream, AFT_RIGHT_HBOI2_POS, _V( -0.985, 0.0, -0.174 ), &HBOILevel );
	return;
}

void MLP::DefineSRBWaterBagSteam( void )
{
	static PARTICLESTREAMSPEC SRBwaterbagsteam = {
		0, 4, 15.0, 0.5, 0.1, 1, 0.3, 1, PARTICLESTREAMSPEC::EMISSIVE,
		PARTICLESTREAMSPEC::LVL_FLAT, 1, 1,
		PARTICLESTREAMSPEC::ATM_FLAT, 1, 1
	};

	AddParticleStream( &SRBwaterbagsteam, _V( -6.25855, 7.11054, 0.238205 ), _V( 0.0, 0.0, 1.0 ), &SRBwaterbagsteam_lvl );// LH
	AddParticleStream( &SRBwaterbagsteam, _V( 6.25855, 7.11054, 0.238205 ), _V( 0.0, 0.0, 1.0 ), &SRBwaterbagsteam_lvl );// RH
	return;
}

void MLP::DefineAnimations()
{
	T0Umbilical_State.Set(AnimState::CLOSED, 0.0);
	anim_t0umb=CreateAnimation(0.0);

	// T0 umbilical animation detais
	// 1.181sec total time
	// 0.147sec delay between PIC fire and plate motion
	// plate stop and door motion at 0.669sec
	static UINT LeftT0UmbGrp[1] = {GRP_LH2_TSM_UMBILICALS_MLP};
	LeftT0Umb = new MGROUP_ROTATE(msh_idx, LeftT0UmbGrp, 1, _V( -5.334, 7.92425, -15.200494 ), _V( 0.0436194, 0.0, -0.999048 ), (float)(26.0*RAD));
	AddAnimationComponent(anim_t0umb, 0.434, 0.876, LeftT0Umb);

	static UINT RightT0UmbGrp[1] = {GRP_LOX_TSM_UMBILICALS_MLP};
	RightT0Umb = new MGROUP_ROTATE(msh_idx, RightT0UmbGrp, 1, _V( 5.334, 7.92425, -15.200494 ), _V( 0.0436194, 0.0, 0.999048 ), (float)(26.0*RAD));
	AddAnimationComponent(anim_t0umb, 0.434, 0.876, RightT0Umb);

	static UINT LeftT0UmbCoverGrp[1] = {GRP_LH2_TSM_BONNET_MLP};
	LeftT0UmbCover = new MGROUP_ROTATE(msh_idx, LeftT0UmbCoverGrp, 1, _V( -5.7912, 14.880541, -13.775 ), _V( -0.0436194, 0.0, 0.999048 ), (float)(90.0*RAD));
	AddAnimationComponent(anim_t0umb, 0.0, 0.434, LeftT0UmbCover);

	static UINT RightT0UmbCoverGrp[1] = {GRP_LOX_TSM_BONNET_MLP};
	RightT0UmbCover = new MGROUP_ROTATE(msh_idx, RightT0UmbCoverGrp, 1, _V( 5.7912, 14.880541, -13.775 ), _V( -0.0436194, 0.0, -0.999048 ), (float)(90.0*RAD));
	AddAnimationComponent(anim_t0umb, 0.0, 0.434, RightT0UmbCover);
}

void MLP::HideSRBWaterBags( VISHANDLE vis )
{
	GROUPEDITSPEC grpSpec;
	grpSpec.flags = GRPEDIT_SETUSERFLAG;
	grpSpec.UsrFlag = 0x00000003;
	DEVMESHHANDLE hDevMLP = GetDevMesh( vis, msh_idx );
	oapiEditMeshGroup( hDevMLP, GRP_LSRB_WATER_BAG_MLP, &grpSpec );
	oapiEditMeshGroup( hDevMLP, GRP_RSRB_WATER_BAG_MLP, &grpSpec);
	oapiEditMeshGroup( hDevMLP, GRP_LSRB_WATER_BAG_WATER_MLP, &grpSpec );
	oapiEditMeshGroup( hDevMLP, GRP_RSRB_WATER_BAG_WATER_MLP, &grpSpec );
	return;
}

void MLP::FireSSMEH2BurnPICs( void )
{
	HBOIOn = true;
	return;
}

void MLP::SetGMTLO( double GMTLO )
{
	if (!IsT0UmbilicalConnected()) return;
	pSTS->SetGMTLO( GMTLO );
	return;
}

void MLP::SetGMTLOSetCommandFlag( bool val )
{
	if (!IsT0UmbilicalConnected()) return;
	pSTS->SetGMTLOSetCommandFlag( val );
	return;
}

void MLP::SetLPSCountdownHoldFlag( bool val )
{
	if (!IsT0UmbilicalConnected()) return;
	pSTS->SetLPSCountdownHoldFlag( val );
	return;
}

void MLP::SetLPSGoForAutoSequenceStartFlag( bool val )
{
	if (!IsT0UmbilicalConnected()) return;
	pSTS->SetLPSGoForAutoSequenceStartFlag( val );
	return;
}

void MLP::SetLPSGoForEngineStartFlag( bool val )
{
	if (!IsT0UmbilicalConnected()) return;
	pSTS->SetLPSGoForEngineStartFlag( val );
	return;
}

void MLP::SetResumeCountCommandFlag( bool val )
{
	if (!IsT0UmbilicalConnected()) return;
	pSTS->SetResumeCountCommandFlag( val );
	return;
}

bool MLP::GetRSCountdownHoldFlag( void )
{
	if (!IsT0UmbilicalConnected()) return false;
	return pSTS->GetRSCountdownHoldFlag();
}

bool MLP::GetLaunchSequenceAbortFlag( void )
{
	if (!IsT0UmbilicalConnected()) return false;
	return pSTS->GetLaunchSequenceAbortFlag();
}

void MLP::PSN4( void )
{
	if (!IsT0UmbilicalConnected()) return;
	pSTS->PSN4();
	return;
}

double MLP::GetHydSysPress( int sys )
{
	if (!IsT0UmbilicalConnected()) return 0.0;
	return pSTS->GetHydSysPress( sys );
}

int MLP::GetHeTankPress( int sys )
{
	if (!IsT0UmbilicalConnected()) return 0;
	return pSTS->GetHeTankPress( sys );
}

int MLP::GetHeRegPress( int sys )
{
	if (!IsT0UmbilicalConnected()) return 0;
	return pSTS->GetHeRegPress( sys );
}

void MLP::HeFillTank( int sys, double mass )
{
	if (!IsT0UmbilicalConnected()) return;
	pSTS->HeFillTank( sys, mass );
	return;
}

void MLP::SetSSMEActPos( int num, double Ppos, double Ypos )
{
	if (!IsT0UmbilicalConnected()) return;
	pSTS->SetSSMEActPos( num, Ppos, Ypos );
	return;
}

unsigned int MLP::GetHoldFlags( void )
{
	if (!IsT0UmbilicalConnected()) return 0;
	return pSTS->GetHoldFlags();
}

void MLP::FireHDPPICs( void )
{
	OBJHANDLE hShuttle = GetAttachmentStatus( ahHDP );
	if (hShuttle)
	{
		VESSELSTATUS2 st;
		st.version = 2;
		st.flag = 0;
		VESSELSTATUS2 st2;
		st2.version = 2;
		st2.flag = 0;
		GetStatusEx( &st2 );

		DetachChild( ahHDP );

		VESSEL* pV = oapiGetVesselInterface( hShuttle );
		pV->GetStatusEx( &st );
		st.rbody = st2.rbody;
		st.rvel = st2.rvel;
		st.status = 0;
		pV->DefSetStateEx( &st );
	}

	pPad->FireETVASPICs();

	// hide water bags
	if (vis) HideSRBWaterBags( vis );

	// vaporize water
	SRBwaterbagsteam_lvl = 1.0;
	return;
}

void MLP::FireT0UmbilicalPICs( void )
{
	T0Umbilical_State.action = AnimState::CLOSING;
	return;
}

bool MLP::IsT0UmbilicalConnected( void ) const
{
	return (T0Umbilical_State.action == AnimState::OPEN);
}

#include "CrewModule.h"
#include "Atlantis.h"
#include "ParameterValues.h"
#include "Atlantis_vc_defs.h"
#include "meshres_vc_middeck.h"
#include "resource.h"
#include <assert.h>


const static char* MESHNAME_SEAT = "SSV\\OV\\SpecialistSeat";
const static char* MESHNAME_COAS = "SSV\\OV\\COAS";
const static char* MESHNAME_POLE = "SSV\\OV\\CrewEscapePole";

const VECTOR3 OFS_POLE_STOWED = _V( -1.423087, 0.932527, 14.030231 ) + VC_OFFSET;
const VECTOR3 OFS_POLE_INSTALLED = _V( -2.0298, 0.326233, 14.068698 ) + VC_OFFSET;


CrewModule::CrewModule( AtlantisSubsystemDirector* _director, unsigned short seats, bool internalAL, bool escape ):AtlantisSubsystem( _director, "CrewModule" ),
cfg(ASCENTENTRY),
COAS_loc(STOWED),
mesh_coasfw(-1),
mesh_coasoh(-1),
mesh_polestowed(-1),
mesh_poleinstalled(-1),
pCOASFWrot(NULL),
pSeat5rot(NULL),
pSeat6rot(NULL),
pSeat7rot(NULL),
pPoleStowedrot(NULL),
pPoleInstalledrot(NULL),
anim_seats(-1),
anim_COASFW(-1),
anim_PoleStowed(-1),
anim_PoleInstalled(-1)
{
	if (seats > 7) seats = 7;
	else if (seats < 3) seats = 3;

	this->seats = seats - 2;

	this->internalAL = internalAL;

	this->escape = escape;

	for (auto &x : mesh_seat) x = -1;

	SEATS_POSITION[0] = OFS_SEAT4;
	SEATS_POSITION[1] = OFS_SEAT3;
	SEATS_POSITION[2] = escape ? OFS_SEAT5A : OFS_SEAT5;
	SEATS_POSITION[3] = escape ? OFS_SEAT6A : OFS_SEAT6;
	SEATS_POSITION[4] = OFS_SEAT7;

	hSeatMesh = oapiLoadMeshGlobal( MESHNAME_SEAT );
	hCOASMesh = oapiLoadMeshGlobal( MESHNAME_COAS );
	if (escape) hPoleMesh = oapiLoadMeshGlobal( MESHNAME_POLE );
	else hPoleMesh = NULL;
	return;
}

CrewModule::~CrewModule( void )
{
	if (pCOASFWrot) delete pCOASFWrot;
	if (pSeat5rot) delete pSeat5rot;
	if (pSeat6rot) delete pSeat6rot;
	if (pSeat7rot) delete pSeat7rot;
	if (pPoleStowedrot) delete pPoleStowedrot;
	if (pPoleInstalledrot) delete pPoleInstalledrot;
}

void CrewModule::Realize( void )
{
	AddMesh();
	return;
}

bool CrewModule::OnParseLine( const char* line )
{
	if (!_strnicmp( line, "CONFIG", 6 ))
	{
		int tmp = 0;
		sscanf_s( line + 6, "%d", &tmp );
		if ((tmp >= ASCENTENTRY) && (tmp <= ORBIT)) cfg = static_cast<CC_CFG>(tmp);
	}
	else if (!_strnicmp( line, "COAS", 4 ))
	{
		int tmp = 0;
		sscanf_s( line + 4, "%d", &tmp );
		if ((tmp >= STOWED) && (tmp <= OH)) COAS_loc = static_cast<COAS_LOC>(tmp);
	}
	else return false;

	return true;
}

void CrewModule::OnSaveState( FILEHANDLE scn ) const
{
	oapiWriteScenario_int( scn, "CONFIG", cfg );
	oapiWriteScenario_int( scn, "COAS", COAS_loc );
	return;
}

void CrewModule::OnPreStep( double simt, double simdt, double mjd )
{
	return;
}

void CrewModule::AddMesh( void )
{
	// seats
	for (int i = 0; i < seats; i++)
		mesh_seat[i] = STS()->AddMesh( hSeatMesh, &SEATS_POSITION[i] );

	// tilt MD seats to match floor
	if (seats > 2)
	{
		anim_seats = STS()->CreateAnimation( 0.0 );

		// seat 5
		static UINT grpSeat5[1] = {0};
		pSeat5rot = new MGROUP_ROTATE( mesh_seat[2], grpSeat5, 1, _V( 0.0, 0.0, 0.0 ), _V( 1.0, 0.0, 0.0 ), static_cast<float>(2.768611 * RAD) );
		STS()->AddAnimationComponent( anim_seats, 0.0, 1.0, pSeat5rot );

		if (seats > 3)
		{
			// seat 6
			static UINT grpSeat6[1] = {0};
			pSeat6rot = new MGROUP_ROTATE( mesh_seat[3], grpSeat6, 1, _V( 0.0, 0.0, 0.0 ), _V( 1.0, 0.0, 0.0 ), static_cast<float>(2.768611 * RAD) );
			STS()->AddAnimationComponent( anim_seats, 0.0, 1.0, pSeat6rot );

			if (seats > 4)
			{
				// seat 7
				static UINT grpSeat7[1] = {0};
				pSeat7rot = new MGROUP_ROTATE( mesh_seat[4], grpSeat7, 1, _V( 0.0, 0.0, 0.0 ), _V( 1.0, 0.0, 0.0 ), static_cast<float>(2.768611 * RAD) );
				STS()->AddAnimationComponent( anim_seats, 0.0, 1.0, pSeat7rot );
			}
		}

		STS()->SetAnimation( anim_seats, 1.0 );
	}

	// COAS OH
	mesh_coasoh = STS()->AddMesh( hCOASMesh, &OFS_COAS_OH );

	// COAS FW
	mesh_coasfw = STS()->AddMesh( hCOASMesh, &OFS_COAS_FW );

	anim_COASFW = STS()->CreateAnimation( 0.0 );
	static UINT grpCOAS[1] = {0};
	pCOASFWrot = new MGROUP_ROTATE( mesh_coasfw, grpCOAS, 1, _V( 0.0, 0.0, 0.0 ), _V( 0.0, 0.7071068, 0.7071068 ), static_cast<float>(180.0 * RAD) );
	STS()->AddAnimationComponent( anim_COASFW, 0.0, 1.0, pCOASFWrot );
	STS()->SetAnimation( anim_COASFW, 1.0 );

	// crew escape pole
	if (escape)
	{
		// stowed
		mesh_polestowed = STS()->AddMesh( hPoleMesh, &OFS_POLE_STOWED );

		anim_PoleStowed = STS()->CreateAnimation( 0.0 );
		static UINT grpPoleStowed[1] = {0};
		pPoleStowedrot = new MGROUP_ROTATE( mesh_polestowed, grpPoleStowed, 1, _V( 0.0, 0.0, 0.0 ), _V( 0.0, 1.0, 0.0 ), static_cast<float>(14.27864983 * RAD) );
		STS()->AddAnimationComponent( anim_PoleStowed, 0.0, 1.0, pPoleStowedrot );
		STS()->SetAnimation( anim_PoleStowed, 1.0 );

		// installed
		mesh_poleinstalled = STS()->AddMesh( hPoleMesh, &OFS_POLE_INSTALLED );

		anim_PoleInstalled = STS()->CreateAnimation( 0.0 );
		static UINT grpPoleInstalled[1] = {0};
		pPoleInstalledrot = new MGROUP_ROTATE( mesh_poleinstalled, grpPoleInstalled, 1, _V( 0.0, 0.0, 0.0 ), _V( -1.0, 0.0, 0.0 ), static_cast<float>(77.98203421 * RAD) );
		STS()->AddAnimationComponent( anim_PoleInstalled, 0.0, 1.0, pPoleInstalledrot );
		STS()->SetAnimation( anim_PoleInstalled, 1.0 );
	}

	UpdateVisual();
	return;
}

void CrewModule::UpdateVisual( void )
{
	if ((STS()->GetVCMode() >= VC_DOCKCAM) && (STS()->GetVCMode() <= VC_RMSCAMWRIST))
		HideMeshes();
	else 
		ShowMeshes();
	return;
}

void CrewModule::HideMeshes( void )
{
	for (int i = 0; i < seats; i++)
		STS()->SetMeshVisibilityMode( mesh_seat[i], MESHVIS_NEVER );

	STS()->SetMeshVisibilityMode( mesh_coasfw, MESHVIS_NEVER );
	STS()->SetMeshVisibilityMode( mesh_coasoh, MESHVIS_NEVER );

	if (escape)
	{
		STS()->SetMeshVisibilityMode( mesh_polestowed, MESHVIS_NEVER );
		STS()->SetMeshVisibilityMode( mesh_poleinstalled, MESHVIS_NEVER );
	}
	return;
}

void CrewModule::ShowMeshes( void )
{
	// seats
	if (cfg == ASCENTENTRY)
	{
		for (int i = 0; i < seats; i++)
			STS()->SetMeshVisibilityMode( mesh_seat[i], MESHVIS_VC );
	}
	else
	{
		for (int i = 0; i < seats; i++)
			STS()->SetMeshVisibilityMode( mesh_seat[i], MESHVIS_NEVER );
	}

	// COAS
	if (COAS_loc == STOWED)
	{
		STS()->SetMeshVisibilityMode( mesh_coasfw, MESHVIS_NEVER );
		STS()->SetMeshVisibilityMode( mesh_coasoh, MESHVIS_NEVER );
	}
	else if (COAS_loc == FW)
	{
		STS()->SetMeshVisibilityMode( mesh_coasfw, MESHVIS_VC );
		STS()->SetMeshVisibilityMode( mesh_coasoh, MESHVIS_NEVER );
	}
	else// if (COAS_loc == OH)
	{
		STS()->SetMeshVisibilityMode( mesh_coasfw, MESHVIS_NEVER );
		STS()->SetMeshVisibilityMode( mesh_coasoh, MESHVIS_VC );
	}

	if (escape)
	{
		if (cfg == ASCENTENTRY)
		{
			STS()->SetMeshVisibilityMode( mesh_polestowed, MESHVIS_NEVER );
			STS()->SetMeshVisibilityMode( mesh_poleinstalled, MESHVIS_VC );
		}
		else
		{
			STS()->SetMeshVisibilityMode( mesh_polestowed, MESHVIS_VC );
			STS()->SetMeshVisibilityMode( mesh_poleinstalled, MESHVIS_NEVER );
		}
	}
	return;
}

void CrewModule::VisualCreated( VISHANDLE vis )
{
	DEVMESHHANDLE hMDDevMesh = STS()->GetDevMesh( vis, STS()->Middeckmesh() );
	GROUPEDITSPEC grpSpec;
	grpSpec.flags = GRPEDIT_SETUSERFLAG;
	grpSpec.UsrFlag = 3;

	if (internalAL)
	{
		oapiEditMeshGroup( hMDDevMesh, GRP_STORAGEBAGS_FLOOR_MD_VC, &grpSpec );
		oapiEditMeshGroup( hMDDevMesh, GRP_STORAGEBAGS_CEILING_MD_VC, &grpSpec );
		oapiEditMeshGroup( hMDDevMesh, GRP_FLOORSTORAGEPANELS_MD_VC, &grpSpec );
	}

	if (!escape)
	{
		oapiEditMeshGroup( hMDDevMesh, GRP_EESS_BOX_MD_VC, &grpSpec );
		oapiEditMeshGroup( hMDDevMesh, GRP_SIDEHATCHTHRUSTERPACKBOXES_MD_VC, &grpSpec );
	}
	return;
}

BOOL CrewModule::CC_DlgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if (uMsg == WM_COMMAND)
	{
		switch (LOWORD(wParam))
		{
			case IDCANCEL:
				oapiCloseDialog( hWnd );
				return TRUE;
			case IDC_CFGAE:
				cfg = ASCENTENTRY;
				COAS_loc = STOWED;
				UpdateVisual();
				UpdateDialog( hWnd );
				return TRUE;
			case IDC_CFGORBIT:
				cfg = ORBIT;
				UpdateVisual();
				UpdateDialog( hWnd );
				return TRUE;
			case IDC_COASSTOWED:
				COAS_loc = STOWED;
				UpdateVisual();
				UpdateDialog( hWnd );
				return TRUE;
			case IDC_COASFW:
				COAS_loc = FW;
				UpdateVisual();
				UpdateDialog( hWnd );
				return TRUE;
			case IDC_COASOH:
				COAS_loc = OH;
				UpdateVisual();
				UpdateDialog( hWnd );
				return TRUE;
		}
	}
	else if (uMsg == WM_SHOWWINDOW)
	{
		UpdateDialog( hWnd );

		// let Orbiter perform default actions
		return oapiDefDialogProc( hWnd, uMsg, wParam, lParam );
	}

	//if message has not been handled in this function, perform default action
	return oapiDefDialogProc( hWnd, uMsg, wParam, lParam );
}

void CrewModule::UpdateDialog( HWND hWnd )
{
	if (cfg == ASCENTENTRY)
	{
		EnableWindow( GetDlgItem( hWnd, IDC_CFGAE ), FALSE );
		EnableWindow( GetDlgItem( hWnd, IDC_CFGORBIT ), TRUE );

		EnableWindow( GetDlgItem( hWnd, IDC_COASSTOWED ), FALSE );
		EnableWindow( GetDlgItem( hWnd, IDC_COASFW ), FALSE );
		EnableWindow( GetDlgItem( hWnd, IDC_COASOH ), FALSE );
	}
	else// if (cfg == ORBIT)
	{
		EnableWindow( GetDlgItem( hWnd, IDC_CFGAE ), TRUE );
		EnableWindow( GetDlgItem( hWnd, IDC_CFGORBIT ), FALSE );

		if (COAS_loc == STOWED)
		{
			EnableWindow( GetDlgItem( hWnd, IDC_COASSTOWED ), FALSE );
			EnableWindow( GetDlgItem( hWnd, IDC_COASFW ), TRUE );
			EnableWindow( GetDlgItem( hWnd, IDC_COASOH ), TRUE );
		}
		else if (COAS_loc == FW)
		{
			EnableWindow( GetDlgItem( hWnd, IDC_COASSTOWED ), TRUE );
			EnableWindow( GetDlgItem( hWnd, IDC_COASFW ), FALSE );
			EnableWindow( GetDlgItem( hWnd, IDC_COASOH ), TRUE );
		}
		else// if (COAS_loc == OH)
		{
			EnableWindow( GetDlgItem( hWnd, IDC_COASSTOWED ), TRUE );
			EnableWindow( GetDlgItem( hWnd, IDC_COASFW ), TRUE );
			EnableWindow( GetDlgItem( hWnd, IDC_COASOH ), FALSE );
		}
	}
	return;
}
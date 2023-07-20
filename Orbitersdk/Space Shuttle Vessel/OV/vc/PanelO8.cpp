/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2020/06/23   GLS
2021/06/02   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/20   GLS
2022/05/29   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "PanelO8.h"
#include "StandardSwitch.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_o8.h"


namespace vc
{
	PanelO8::PanelO8( Atlantis* psts ):AtlantisPanel( psts, "O8" )
	{
		DefineMesh( MESHNAME_PANELO8 );

		Add( pRadarAltimeter[0] = new StdSwitch2( psts, "RADAR ALTIMETER 1" ) );
		pRadarAltimeter[0]->SetLabel( 0, "OFF" );
		pRadarAltimeter[0]->SetLabel( 1, "ON" );

		Add( pRadarAltimeter[1] = new StdSwitch2( psts, "RADAR ALTIMETER 2" ) );
		pRadarAltimeter[1]->SetLabel( 0, "OFF" );
		pRadarAltimeter[1]->SetLabel( 1, "ON" );

		Add( pAnnunciatorLampTest = new StdSwitch3( psts, "ANNUNCIATOR LAMP TEST" ) );
	}

	PanelO8::~PanelO8()
	{
	}

	void PanelO8::DefineVC()
	{
		VECTOR3 switch_rot = _V( 1, 0, 0 );

		AddAIDToMouseEventList( AID_O8 );

		pRadarAltimeter[0]->SetInitialAnimState( 0.5f );
		pRadarAltimeter[0]->DefineGroup( GRP_S4_O8_VC );
		pRadarAltimeter[0]->SetReference( _V( 0.2651, 3.1652, 13.6946 ), switch_rot );
		pRadarAltimeter[0]->SetMouseRegion( AID_O8, 0.089737f, 0.106703f, 0.135184f, 0.140805f );

		pRadarAltimeter[1]->SetInitialAnimState( 0.5f );
		pRadarAltimeter[1]->DefineGroup( GRP_S5_O8_VC );
		pRadarAltimeter[1]->SetReference( _V( 0.2651, 3.1652, 13.6946 ), switch_rot );
		pRadarAltimeter[1]->SetMouseRegion( AID_O8, 0.157729f, 0.106310f, 0.201778f, 0.140387f );

		pAnnunciatorLampTest->SetInitialAnimState( 0.5f );
		pAnnunciatorLampTest->DefineGroup( GRP_S18_O8_VC );
		pAnnunciatorLampTest->SetReference( _V( 0.6000, 3.0978, 13.9709 ), switch_rot );
		pAnnunciatorLampTest->SetMouseRegion( AID_O8, 0.775565f, 0.498687f, 0.814904f, 0.530986f );
		pAnnunciatorLampTest->SetSpringLoaded( true, 0 );
		pAnnunciatorLampTest->SetSpringLoaded( true, 2 );
	}

	void PanelO8::Realize()
	{
		discsignals::DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "RDR_ALT", 16 );
		pRadarAltimeter[0]->ConnectPort( 1, pBundle, 0 );
		pRadarAltimeter[1]->ConnectPort( 1, pBundle, 1 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA", 16 );
		pAnnunciatorLampTest->ConnectPort( 2, pBundle, 8 );
		pAnnunciatorLampTest->ConnectPort( 0, pBundle, 9 );

		AtlantisPanel::Realize();
	}

	void PanelO8::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_O8, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_O8,
			_V( 0.202423, 3.1858, 13.6083 ) + ofs, _V( 0.710853, 3.1858, 13.6083 ) + ofs,
			_V( 0.202423, 3.01485, 14.3133 ) + ofs, _V( 0.710853, 3.01474, 14.3133 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
	}

}

/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/05/10   GLS
2020/05/24   GLS
2020/06/20   GLS
2020/06/23   GLS
2021/06/28   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2022/01/07   GLS
2022/03/22   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/19   GLS
2022/04/20   GLS
2022/05/29   GLS
2022/08/05   GLS
********************************************/
#include "PanelA7A3.h"
#include "StandardSwitch.h"
#include "../Atlantis.h"
#include "..\ParameterValues.h"
#include "vc_defs.h"
#include "DiscreteBundleManager.h"
#include "../meshres_vc_a7a3.h"


namespace vc
{
	using namespace discsignals;

	PanelA7A3::PanelA7A3( Atlantis* _sts, bool defaultposition ):AtlantisPanel( _sts, defaultposition ? "A7L" : "A6L" )
	{
		DefineMesh( MESHNAME_PANELA7A3 );

		Add( pLightsTrussFwd = new StdSwitch2( _sts, "LIGHTS TRUSS FWD" ) );
		pLightsTrussFwd->SetLabel( 0, "OFF" );
		pLightsTrussFwd->SetLabel( 1, "ON" );

		Add( pLightsTrussAft = new StdSwitch2( _sts, "LIGHTS TRUSS AFT" ) );
		pLightsTrussAft->SetLabel( 0, "OFF" );
		pLightsTrussAft->SetLabel( 1, "ON" );

		Add( pLightsVestibulePort = new StdSwitch2( _sts, "LIGHTS VESTIBULE PORT" ) );
		pLightsVestibulePort->SetLabel( 0, "OFF" );
		pLightsVestibulePort->SetLabel( 1, "ON" );

		Add( pLightsVestibuleStbd = new StdSwitch2( _sts, "LIGHTS VESTIBULE STBD" ) );
		pLightsVestibuleStbd->SetLabel( 0, "OFF" );
		pLightsVestibuleStbd->SetLabel( 1, "ON" );
	}

	PanelA7A3::~PanelA7A3()
	{
	}

	void PanelA7A3::Realize()
	{
		oapiWriteLog( "Panel A7A3:\tRealize()" );

		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "ODS_LIGHTS", 16 );
		pLightsTrussFwd->ConnectPort( 1, pBundle, 0 );
		pLightsTrussAft->ConnectPort( 1, pBundle, 1 );
		pLightsVestibulePort->ConnectPort( 1, pBundle, 2 );
		pLightsVestibuleStbd->ConnectPort( 1, pBundle, 3 );

		AtlantisPanel::Realize();

		oapiWriteLog( "Panel A7A3:\tRealize done." );
		return;
	}

	void PanelA7A3::DefineVC()
	{
		VECTOR3 switch_rot = _V( -1.0, 0.0, 0.0 );

		oapiWriteLog( "Panel A7A3:\tDefine VC" );

		AddAIDToMouseEventList( AID_A7A3 );

		pLightsTrussFwd->SetInitialAnimState( 0.5f );
		pLightsTrussFwd->DefineGroup( GRP_S11_A7A3_VC );
		pLightsTrussFwd->SetReference( _V( 0.35099, 2.324645, 12.45905 ), switch_rot );
		pLightsTrussFwd->SetMouseRegion( AID_A7A3, 0.765151f, 0.588041f, 0.804096f, 0.680719f );

		pLightsTrussAft->SetInitialAnimState( 0.5f );
		pLightsTrussAft->DefineGroup( GRP_S12_A7A3_VC );
		pLightsTrussAft->SetReference( _V( 0.35099, 2.324645, 12.45905 ), switch_rot );
		pLightsTrussAft->SetMouseRegion( AID_A7A3, 0.826668f, 0.588041f, 0.864016f, 0.680719f );

		pLightsVestibulePort->SetInitialAnimState( 0.5f );
		pLightsVestibulePort->DefineGroup( GRP_S15_A7A3_VC );
		pLightsVestibulePort->SetReference( _V( 0.354569, 2.263065, 12.47845 ), switch_rot );
		pLightsVestibulePort->SetMouseRegion( AID_A7A3, 0.765151f, 0.811992f, 0.804096f, 0.900690f );

		pLightsVestibuleStbd->SetInitialAnimState( 0.5f );
		pLightsVestibuleStbd->DefineGroup( GRP_S16_A7A3_VC );
		pLightsVestibuleStbd->SetReference( _V( 0.354569, 2.263065, 12.47845 ), switch_rot );
		pLightsVestibuleStbd->SetMouseRegion( AID_A7A3, 0.826668f, 0.811992f, 0.864016f, 0.900690f );
		return;
	}

	void PanelA7A3::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;
		oapiVCRegisterArea( AID_A7A3, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP );
		oapiVCSetAreaClickmode_Quadrilateral( AID_A7A3,
			_V( 0.790742, 2.50659, 12.3989 ) + ofs, _V( 0.263602, 2.50659, 12.3989 ) + ofs,
			_V( 0.790742, 2.21941, 12.4892 ) + ofs, _V( 0.263602, 2.21941, 12.4892 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}
};

/******* SSV File Modification Notice *******
Date         Developer
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
2022/09/18   GLS
********************************************/
#include "PanelA3.h"
#include "StandardSwitch.h"
#include "PushButton.h"
#include "..\Atlantis.h"
#include "..\ParameterValues.h"
#include "vc_defs.h"
#include "..\meshres_vc_a3.h"


namespace vc
{
	PanelA3::PanelA3( Atlantis* _sts ):AtlantisPanel( _sts, "A3" )
	{
		DefineMesh( MESHNAME_PANELA3 );

		Add( pMon1_Power = new StdSwitch2( _sts, "MONITOR 1 POWER" ) );
		pMon1_Power->SetLabel( 0, "OFF" );
		pMon1_Power->SetLabel( 1, "ON" );
		Add( pMon1_Function = new StdSwitch3( _sts, "MONITOR 1 FUNCTION" ) );
		Add( pMon1_Select = new PushButton( _sts, "MONITOR 1 SELECT" ) );

		Add( pMon2_Power = new StdSwitch2( _sts, "MONITOR 2 POWER" ) );
		pMon2_Power->SetLabel( 0, "OFF" );
		pMon2_Power->SetLabel( 1, "ON" );
		Add( pMon2_Function = new StdSwitch3( _sts, "MONITOR 2 FUNCTION" ) );
		Add( pMon2_Select = new PushButton( _sts, "MONITOR 2 SELECT" ) );
	}

	PanelA3::~PanelA3()
	{
	}

	void PanelA3::DefineVC()
	{
		VECTOR3 switch_rotV = _V( -0.71902, 0.0, 0.69499 );///
		VECTOR3 switch_rotH = _V( -0.12679, 0.98254, -0.136193 );///
		VECTOR3 switch_push = _V( -0.6856, -0.186158, -0.70377 );///

		AddAIDToMouseEventList( AID_A3 );

		pMon1_Power->DefineGroup( GRP_MON1_S1_A3_VC );
		pMon1_Power->SetInitialAnimState( 0.5 );
		pMon1_Power->SetReference( _V( -1.03924, 3.09114, 12.4754 ), switch_rotV );
		pMon1_Power->SetMouseRegion( AID_A3, 0.262333f, 0.059299f, 0.416424f, 0.091852f );

		pMon1_Function->DefineGroup( GRP_MON1_S2_A3_VC );
		pMon1_Function->SetInitialAnimState( 0.5 );
		pMon1_Function->SetReference( _V( -1.04045, 3.05204, 12.4869 ), switch_rotH );
		pMon1_Function->SetMouseRegion( AID_A3, 0.373139f, 0.186269f, 0.768961f, 0.207861f );
		pMon1_Function->SetSpringLoaded( true, 0 );
		pMon1_Function->SetSpringLoaded( true, 2 );
		pMon1_Function->SetOrientation( true );

		pMon1_Select->SetMouseRegion( AID_A3, 0.294887f, 0.135948f, 0.466709f, 0.155176f );
		pMon1_Select->SetDirection( switch_push );
		pMon1_Select->DefineGroup( GRP_MON1_S3_A3_VC );

		pMon2_Power->DefineGroup( GRP_MON2_S1_A3_VC );
		pMon2_Power->SetInitialAnimState( 0.5 );
		pMon2_Power->SetReference( _V( -1.0167, 2.91936, 12.4988 ), switch_rotV );
		pMon2_Power->SetMouseRegion( AID_A3, 0.244577f, 0.597140f, 0.427013f, 0.629872f );

		pMon2_Function->DefineGroup( GRP_MON2_S2_A3_VC );
		pMon2_Function->SetInitialAnimState( 0.5 );
		pMon2_Function->SetReference( _V( -1.01776, 2.87915, 12.5104 ), switch_rotH );
		pMon2_Function->SetMouseRegion( AID_A3, 0.363168f, 0.732259f, 0.751540f, 0.753721f );
		pMon2_Function->SetSpringLoaded( true, 0 );
		pMon2_Function->SetSpringLoaded( true, 2 );
		pMon2_Function->SetOrientation( true );

		pMon2_Select->SetMouseRegion( AID_A3, 0.287613f, 0.676727f, 0.478040f, 0.698892f );
		pMon2_Select->SetDirection( switch_push );
		pMon2_Select->DefineGroup( GRP_MON2_S3_A3_VC );
		return;
	}

	void PanelA3::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_A3, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_A3,
			_V( -1.0361, 3.1158, 12.4603 ) + ofs, _V( -1.0764, 3.1123, 12.4814 ) + ofs,
			_V( -0.998, 2.7924, 12.5022 ) + ofs, _V( -1.0268, 2.7936, 12.5297 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelA3::Realize()
	{
		AtlantisPanel::Realize();

		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "A3_Monitors", 16 );
		pMon1_Power->ConnectPort( 1, pBundle, 0 );
		pMon1_Function->ConnectPort( 0, pBundle, 1 );
		pMon1_Function->ConnectPort( 2, pBundle, 2 );
		pMon1_Select->output.Connect( pBundle, 3 );
		pMon2_Power->ConnectPort( 1, pBundle, 4 );
		pMon2_Function->ConnectPort( 0, pBundle, 5 );
		pMon2_Function->ConnectPort( 2, pBundle, 6 );
		pMon2_Select->output.Connect( pBundle, 7 );
		return;
	}
};

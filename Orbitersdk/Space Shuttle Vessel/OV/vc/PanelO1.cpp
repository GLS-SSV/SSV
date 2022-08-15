/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2020/06/23   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/20   GLS
2022/08/05   GLS
********************************************/
#include "PanelO1.h"
#include "StandardLight.h"
#include "../Atlantis.h"
#include "..\ParameterValues.h"
#include "vc_defs.h"
#include "..\meshres_vc_o1.h"


namespace vc
{
	PanelO1::PanelO1( Atlantis *_sts ):AtlantisPanel( _sts, "O1" )
	{
		DefineMesh( MESHNAME_PANELO1 );

		Add( pGPCLight[0] = new StandardSingleLight( _sts, "GPC 1 1" ) );
		Add( pGPCLight[1] = new StandardSingleLight( _sts, "GPC 1 2" ) );
		Add( pGPCLight[2] = new StandardSingleLight( _sts, "GPC 1 3" ) );
		Add( pGPCLight[3] = new StandardSingleLight( _sts, "GPC 1 4" ) );
		Add( pGPCLight[4] = new StandardSingleLight( _sts, "GPC 1 5" ) );

		Add( pGPCLight[5] = new StandardSingleLight( _sts, "GPC 2 1" ) );
		Add( pGPCLight[6] = new StandardSingleLight( _sts, "GPC 2 2" ) );
		Add( pGPCLight[7] = new StandardSingleLight( _sts, "GPC 2 3" ) );
		Add( pGPCLight[8] = new StandardSingleLight( _sts, "GPC 2 4" ) );
		Add( pGPCLight[9] = new StandardSingleLight( _sts, "GPC 2 5" ) );

		Add( pGPCLight[10] = new StandardSingleLight( _sts, "GPC 3 1" ) );
		Add( pGPCLight[11] = new StandardSingleLight( _sts, "GPC 3 2" ) );
		Add( pGPCLight[12] = new StandardSingleLight( _sts, "GPC 3 3" ) );
		Add( pGPCLight[13] = new StandardSingleLight( _sts, "GPC 3 4" ) );
		Add( pGPCLight[14] = new StandardSingleLight( _sts, "GPC 3 5" ) );

		Add( pGPCLight[15] = new StandardSingleLight( _sts, "GPC 4 1" ) );
		Add( pGPCLight[16] = new StandardSingleLight( _sts, "GPC 4 2" ) );
		Add( pGPCLight[17] = new StandardSingleLight( _sts, "GPC 4 3" ) );
		Add( pGPCLight[18] = new StandardSingleLight( _sts, "GPC 4 4" ) );
		Add( pGPCLight[19] = new StandardSingleLight( _sts, "GPC 4 5" ) );

		Add( pGPCLight[20] = new StandardSingleLight( _sts, "GPC 5 1" ) );
		Add( pGPCLight[21] = new StandardSingleLight( _sts, "GPC 5 2" ) );
		Add( pGPCLight[22] = new StandardSingleLight( _sts, "GPC 5 3" ) );
		Add( pGPCLight[23] = new StandardSingleLight( _sts, "GPC 5 4" ) );
		Add( pGPCLight[24] = new StandardSingleLight( _sts, "GPC 5 5" ) );
	}

	PanelO1::~PanelO1()
	{
	}

	void PanelO1::DefineVC( void )
	{
		AddAIDToMouseEventList( AID_O1 );

		pGPCLight[0]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_11_O1_VC );
		pGPCLight[0]->SetStateOffset( 1, 0.0f, -0.050781f );

		pGPCLight[1]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_12_O1_VC );
		pGPCLight[1]->SetStateOffset( 1, 0.0f, -0.050781f );

		pGPCLight[2]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_13_O1_VC );
		pGPCLight[2]->SetStateOffset( 1, 0.0f, -0.050781f );

		pGPCLight[3]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_14_O1_VC );
		pGPCLight[3]->SetStateOffset( 1, 0.0f, -0.050781f );

		pGPCLight[4]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_15_O1_VC );
		pGPCLight[4]->SetStateOffset( 1, 0.0f, -0.050781f );

		pGPCLight[5]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_21_O1_VC );
		pGPCLight[5]->SetStateOffset( 1, 0.0f, -0.050781f );

		pGPCLight[6]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_22_O1_VC );
		pGPCLight[6]->SetStateOffset( 1, 0.0f, -0.050781f );

		pGPCLight[7]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_23_O1_VC );
		pGPCLight[7]->SetStateOffset( 1, 0.0f, -0.050781f );

		pGPCLight[8]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_24_O1_VC );
		pGPCLight[8]->SetStateOffset( 1, 0.0f, -0.050781f );

		pGPCLight[9]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_25_O1_VC );
		pGPCLight[9]->SetStateOffset( 1, 0.0f, -0.050781f );

		pGPCLight[10]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_31_O1_VC );
		pGPCLight[10]->SetStateOffset( 1, 0.0f, -0.050781f );

		pGPCLight[11]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_32_O1_VC );
		pGPCLight[11]->SetStateOffset( 1, 0.0f, -0.050781f );

		pGPCLight[12]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_33_O1_VC );
		pGPCLight[12]->SetStateOffset( 1, 0.0f, -0.050781f );

		pGPCLight[13]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_34_O1_VC );
		pGPCLight[13]->SetStateOffset( 1, 0.0f, -0.050781f );

		pGPCLight[14]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_35_O1_VC );
		pGPCLight[14]->SetStateOffset( 1, 0.0f, -0.050781f );

		pGPCLight[15]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_41_O1_VC );
		pGPCLight[15]->SetStateOffset( 1, 0.0f, -0.050781f );

		pGPCLight[16]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_42_O1_VC );
		pGPCLight[16]->SetStateOffset( 1, 0.0f, -0.050781f );

		pGPCLight[17]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_43_O1_VC );
		pGPCLight[17]->SetStateOffset( 1, 0.0f, -0.050781f );

		pGPCLight[18]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_44_O1_VC );
		pGPCLight[18]->SetStateOffset( 1, 0.0f, -0.050781f );

		pGPCLight[19]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_45_O1_VC );
		pGPCLight[19]->SetStateOffset( 1, 0.0f, -0.050781f );

		pGPCLight[20]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_51_O1_VC );
		pGPCLight[20]->SetStateOffset( 1, 0.0f, -0.050781f );

		pGPCLight[21]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_52_O1_VC );
		pGPCLight[21]->SetStateOffset( 1, 0.0f, -0.050781f );

		pGPCLight[22]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_53_O1_VC );
		pGPCLight[22]->SetStateOffset( 1, 0.0f, -0.050781f );

		pGPCLight[23]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_54_O1_VC );
		pGPCLight[23]->SetStateOffset( 1, 0.0f, -0.050781f );

		pGPCLight[24]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_55_O1_VC );
		pGPCLight[24]->SetStateOffset( 1, 0.0f, -0.050781f );
		return;
	}

	void PanelO1::RegisterVC( void )
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_O1, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_O1,
			_V( -0.7261, 3.0096, 14.3150 ) + ofs, _V( -0.1146, 3.0096, 14.3150 ) + ofs,
			_V( -0.7261, 2.7283, 14.3728 ) + ofs, _V( -0.1146, 2.7283, 14.3728 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelO1::Realize( void )
	{
		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "ADU_A", 16 );
		for (int i = 0; i < 16; i++) lightcmd[i].Connect( pBundle, i );

		pBundle = STS()->BundleManager()->CreateBundle( "ADU_B", 16 );
		for (int i = 16; i < 25; i++) lightcmd[i].Connect( pBundle, i - 16 );

		pBundle = STS()->BundleManager()->CreateBundle( "O1LIGHTS_A", 16 );
		for (int i = 0; i < 16; i++)
		{
			pGPCLight[i]->ConnectLight( 0, pBundle, i );
			lightoutput[i].Connect( pBundle, i );
		}

		pBundle = STS()->BundleManager()->CreateBundle( "O1LIGHTS_B", 16 );
		for (int i = 16; i < 25; i++)
		{
			pGPCLight[i]->ConnectLight( 0, pBundle, i - 16 );
			lightoutput[i].Connect( pBundle, i - 16 );
		}

		pBundle = STS()->BundleManager()->CreateBundle( "ACA", 16 );
		lighttest[0].Connect( pBundle, 6 );
		lighttest[1].Connect( pBundle, 8 );

		AtlantisPanel::Realize();
		return;
	}

	void PanelO1::OnPostStep( double simt, double simdt, double mjd )
	{
		AtlantisPanel::OnPostStep( simt, simdt, mjd );

		if (lighttest[0].IsSet() || lighttest[1].IsSet())
		{
			for (int i = 0; i < 25; i++) lightoutput[i].SetLine();
		}
		else
		{
			for (int i = 0; i < 25; i++) lightoutput[i].SetLine( (int)lightcmd[i].IsSet() * 5.0f );
		}
		return;
	}
}

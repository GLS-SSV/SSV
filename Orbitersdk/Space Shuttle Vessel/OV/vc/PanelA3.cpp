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
2022/09/29   GLS
********************************************/
#include "PanelA3.h"
#include "CTVM.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_a3.h"


namespace vc
{
	PanelA3::PanelA3( Atlantis* _sts ):AtlantisPanel( _sts, "A3" )
	{
		DefineMesh( MESHNAME_PANELA3 );

		Add( pMon1 = new CTVM( 1, _sts, "MONITOR 1" ) );
		Add( pMon2 = new CTVM( 2, _sts, "MONITOR 2" ) );
	}

	PanelA3::~PanelA3()
	{
	}

	void PanelA3::DefineVC()
	{
		VECTOR3 switch_rotV = _V( -0.71902, 0.0, 0.69499 );
		VECTOR3 switch_rotH = _V( -0.12679, 0.98254, -0.136193 );
		VECTOR3 switch_push = _V( -0.6856, -0.186158, -0.70377 );

		AddAIDToMouseEventList( AID_A3 );

		pMon1->SetMouseRegion( AID_A3, 0.0f, 0.002365f, 1.0f, 0.406909f );
		pMon1->SetReferences( _V( -1.03924, 3.09114, 12.4754 ), _V( -1.04045, 3.05204, 12.4869 ) );
		pMon1->SetGroups( GRP_MON1_S1_A3_VC, GRP_MON1_S2_A3_VC, GRP_MON1_S3_A3_VC );
		pMon1->SetDirections( switch_rotV, switch_rotH, switch_push );

		pMon2->SetMouseRegion( AID_A3, 0.0f, 0.534035f, 1.0f, 0.938629f );
		pMon2->SetReferences( _V( -1.0167, 2.91936, 12.4988 ), _V( -1.01776, 2.87915, 12.5104 ) );
		pMon2->SetGroups( GRP_MON2_S1_A3_VC, GRP_MON2_S2_A3_VC, GRP_MON2_S3_A3_VC );
		pMon2->SetDirections( switch_rotV, switch_rotH, switch_push );
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

	void PanelA3::VisualCreated( void )
	{
		if (STS()->D3D9())
		{
			oapiWriteLog( "(SSV_OV) [INFO] Setting CTVM surfaces" );
			DEVMESHHANDLE hDevMesh = STS()->GetDevMesh( STS()->Get_vis(), GetVCMeshIndex() );
			if (hDevMesh != NULL)
			{
				oapiSetTexture( hDevMesh, 2, pMon1->GetMonitorSurf() );
				oapiSetTexture( hDevMesh, 3, pMon2->GetMonitorSurf() );
			}
		}

		AtlantisPanel::VisualCreated();
		return;
	}
}

/******* SSV File Modification Notice *******
Date         Developer
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
2022/09/29   GLS
********************************************/
#include "PanelA12A1.h"
#include "MDU.h"
#include "StandardSwitch.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_a12a1.h"


namespace vc
{
	PanelA12A1::PanelA12A1( Atlantis *_sts, bool defaultposition ) : AtlantisPanel( _sts, defaultposition ? "R12U" : "R11U" )
	{
		DefineMesh( MESHNAME_PANELA12A1 );

		Add(pCRT4 = new MDU(_sts, "CRT4", MDUID_CRT4));
	}

	PanelA12A1::~PanelA12A1()
	{
	}

	void PanelA12A1::DefineVC()
	{
		AddAIDToMouseEventList( AID_A12A1 );

		pCRT4->DefineVCGroup( GRP_CRT4_A12A1_VC );
		pCRT4->DefineMaterial( MAT_MDU_CRT4_A12A1_VC );
		pCRT4->SetMouseRegion( AID_A12A1, 0.036582f, 0.040874f, 0.527693f, 0.963088f );
		return;
	}

	void PanelA12A1::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_A12A1, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_A12A1,
			_V( 1.53941, 2.43208, 13.6093 ) + ofs, _V( 1.53983, 2.43283, 13.0865 ) + ofs,
			_V( 1.3315, 2.29614, 13.6093 ) + ofs, _V( 1.3315, 2.29657, 13.0865 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelA12A1::Realize()
	{
		AtlantisPanel::Realize();
		return;
	}
};

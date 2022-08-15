/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2020/06/23   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/20   GLS
2022/08/05   GLS
********************************************/
#include "PanelR10.h"
#include "..\Atlantis.h"
#include "..\ParameterValues.h"
#include "vc_defs.h"
#include "..\meshres_vc_r10.h"


namespace vc
{
	PanelR10::PanelR10( Atlantis* _sts ):AtlantisPanel( _sts, "R10" )
	{
		DefineMesh( MESHNAME_PANELR10 );
	}

	PanelR10::~PanelR10()
	{
	}

	void PanelR10::DefineVC()
	{
		AddAIDToMouseEventList( AID_R10 );
		return;
	}

	void PanelR10::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_R10, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_R10,
			_V( 1.65494, 2.50958, 12.8038 ) + ofs, _V( 1.69245, 2.53394, 12.2564 ) + ofs,
			_V( 1.53864, 2.43406, 12.8038 ) + ofs, _V( 1.53913, 2.43437, 12.2564 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelR10::Realize()
	{
		AtlantisPanel::Realize();
		return;
	}
};
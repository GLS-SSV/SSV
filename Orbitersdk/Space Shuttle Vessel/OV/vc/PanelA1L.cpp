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
2022/08/05   GLS
********************************************/
#include "PanelA1L.h"
#include "..\Atlantis.h"
#include "..\ParameterValues.h"
#include "vc_defs.h"
#include "..\meshres_vc_a1l.h"


namespace vc
{
	PanelA1L::PanelA1L( Atlantis* _sts ):AtlantisPanel( _sts, "A1L" )
	{
		DefineMesh( MESHNAME_PANELA1L );
	}

	PanelA1L::~PanelA1L()
	{
	}

	void PanelA1L::DefineVC()
	{
		AddAIDToMouseEventList( AID_A1L );
		return;
	}

	void PanelA1L::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_A1L, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_A1L,
			_V( 1.4954, 2.6915, 12.2208 ) + ofs, _V( 1.1639, 2.6915, 12.2209 ) + ofs,
			_V( 1.4954, 2.3069, 12.221 ) + ofs, _V( 1.1639, 2.3069, 12.221 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelA1L::Realize()
	{
		AtlantisPanel::Realize();
		return;
	}
};
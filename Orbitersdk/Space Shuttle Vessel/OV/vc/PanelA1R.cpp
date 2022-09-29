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
2022/03/26   GLS
2022/04/19   GLS
2022/04/20   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "PanelA1R.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_a1r.h"


namespace vc
{
	PanelA1R::PanelA1R( Atlantis* _sts ):AtlantisPanel( _sts, "A1R" )
	{
		DefineMesh( MESHNAME_PANELA1R );
	}

	PanelA1R::~PanelA1R()
	{
	}

	void PanelA1R::DefineVC()
	{
		AddAIDToMouseEventList( AID_A1R );
		return;
	}

	void PanelA1R::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_A1R, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_A1R,
			_V( 1.0902, 2.7055, 12.2209 ) + ofs, _V( 0.8332, 2.7055, 12.221 ) + ofs,
			_V( 1.0902, 2.1313, 12.221 ) + ofs, _V( 0.8332, 2.1313, 12.2211 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelA1R::Realize()
	{
		AtlantisPanel::Realize();
		return;
	}
};
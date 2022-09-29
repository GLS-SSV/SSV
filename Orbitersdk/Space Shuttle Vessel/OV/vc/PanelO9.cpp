/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2020/06/23   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/20   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "PanelO9.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_o9.h"


namespace vc
{
	PanelO9::PanelO9( Atlantis* _sts ):AtlantisPanel( _sts, "O9" )
	{
		DefineMesh( MESHNAME_PANELO9 );
	}

	PanelO9::~PanelO9()
	{
	}

	void PanelO9::DefineVC()
	{
		AddAIDToMouseEventList( AID_O9 );
		return;
	}

	void PanelO9::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_O9, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_O9,
			_V( 0.759093, 2.98093, 14.2904 ) + ofs, _V( 0.84038, 2.98599, 13.912 ) + ofs,
			_V( 0.866101, 2.86819, 14.3114 ) + ofs, _V( 0.946387, 2.87325, 13.933 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelO9::Realize()
	{
		AtlantisPanel::Realize();
		return;
	}
}

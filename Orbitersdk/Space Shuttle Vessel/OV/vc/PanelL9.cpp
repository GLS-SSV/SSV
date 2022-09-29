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
#include "PanelL9.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_l9.h"


namespace vc
{
	PanelL9::PanelL9( Atlantis* _sts ):AtlantisPanel( _sts, "L9" )
	{
		DefineMesh( MESHNAME_PANELL9 );
	}

	PanelL9::~PanelL9()
	{
	}

	void PanelL9::DefineVC()
	{
		AddAIDToMouseEventList( AID_L9 );
		return;
	}

	void PanelL9::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_L9, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_L9,
			_V( -1.6965, 2.53376, 12.2204 ) + ofs, _V( -1.66009, 2.51012, 12.8038 ) + ofs,
			_V( -1.54444, 2.43502, 12.2204 ) + ofs, _V( -1.5438, 2.4346, 12.8038 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelL9::Realize()
	{
		AtlantisPanel::Realize();
		return;
	}
}

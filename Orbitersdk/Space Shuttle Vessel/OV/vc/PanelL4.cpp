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
#include "PanelL4.h"
#include "..\Atlantis.h"
#include "..\ParameterValues.h"
#include "vc_defs.h"
#include "..\meshres_vc_l4.h"


namespace vc
{
	PanelL4::PanelL4( Atlantis* _sts ):AtlantisPanel( _sts, "L4" )
	{
		DefineMesh( MESHNAME_PANELL4 );
	}

	PanelL4::~PanelL4()
	{
	}

	void PanelL4::DefineVC()
	{
		AddAIDToMouseEventList( AID_L4 );
		return;
	}

	void PanelL4::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_L4, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_L4,
			_V( -1.44342, 2.60918, 13.8059 ) + ofs, _V( -1.44342, 1.95123, 13.8059 ) + ofs,
			_V( -1.15403, 2.60918, 13.8059 ) + ofs, _V( -1.15403, 1.95123, 13.8059 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelL4::Realize()
	{
		AtlantisPanel::Realize();
		return;
	}
};
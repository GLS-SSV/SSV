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
#include "PanelR4.h"
#include "..\Atlantis.h"
#include "..\ParameterValues.h"
#include "vc_defs.h"
#include "..\meshres_vc_r4.h"


namespace vc
{
	PanelR4::PanelR4( Atlantis* _sts ):AtlantisPanel( _sts, "R4" )
	{
		DefineMesh( MESHNAME_PANELR4 );
	}

	PanelR4::~PanelR4()
	{
	}

	void PanelR4::DefineVC()
	{
		AddAIDToMouseEventList( AID_R4 );
		return;
	}

	void PanelR4::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_R4, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_R4,
			_V( 1.4982, 1.87836, 13.8054 ) + ofs, _V( 1.4982, 2.22704, 13.8054 ) + ofs,
			_V( 1.14952, 1.87836, 13.8054 ) + ofs, _V( 1.14952, 2.22704, 13.8054 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelR4::Realize()
	{
		AtlantisPanel::Realize();
		return;
	}
};
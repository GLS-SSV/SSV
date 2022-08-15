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
#include "PanelO13.h"
#include "..\Atlantis.h"
#include "..\ParameterValues.h"
#include "vc_defs.h"
#include "..\meshres_vc_o13.h"


namespace vc
{
	PanelO13::PanelO13( Atlantis* _sts ):AtlantisPanel( _sts, "O13" )
	{
		DefineMesh( MESHNAME_PANELO13 );
	}

	PanelO13::~PanelO13()
	{
	}

	void PanelO13::DefineVC()
	{
		AddAIDToMouseEventList( AID_O13 );
		return;
	}

	void PanelO13::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_O13, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_O13,
			_V( -0.9374, 3.023, 13.226 ) + ofs, _V( -0.8098, 3.122, 13.226 ) + ofs,
			_V( -0.9374, 3.023, 13.579 ) + ofs, _V( -0.8098, 3.122, 13.579 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelO13::Realize()
	{
		AtlantisPanel::Realize();
		return;
	}
};
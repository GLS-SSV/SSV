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
#include "PanelO7.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_o7.h"


namespace vc
{
	PanelO7::PanelO7( Atlantis* _sts ):AtlantisPanel( _sts, "O7" )
	{
		DefineMesh( MESHNAME_PANELO7 );
	}

	PanelO7::~PanelO7()
	{
	}

	void PanelO7::DefineVC()
	{
		AddAIDToMouseEventList( AID_O7 );
		return;
	}

	void PanelO7::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_O7, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_O7,
			_V( -0.217782, 3.1858, 13.6081 ) + ofs, _V( 0.202397, 3.1858, 13.6081 ) + ofs,
			_V( -0.217782, 3.01494, 14.3132 ) + ofs, _V( 0.202397, 3.01485, 14.3131 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelO7::Realize()
	{
		AtlantisPanel::Realize();
		return;
	}
}

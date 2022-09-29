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
#include "PanelO5.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_o5.h"


namespace vc
{
	PanelO5::PanelO5( Atlantis* _sts ):AtlantisPanel( _sts, "O5" )
	{
		DefineMesh( MESHNAME_PANELO5 );
	}

	PanelO5::~PanelO5()
	{
	}

	void PanelO5::DefineVC()
	{
		AddAIDToMouseEventList( AID_O5 );
		return;
	}

	void PanelO5::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_O5, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_O5,
			_V( -0.8451, 2.98599, 13.912 ) + ofs, _V( -0.76482, 2.98093, 14.2904 ) + ofs,
			_V( -0.95111, 2.87325, 13.933 ) + ofs, _V( -0.87083, 2.86819, 14.3114 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelO5::Realize()
	{
		AtlantisPanel::Realize();
		return;
	}
};
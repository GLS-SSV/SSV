/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2020/06/23   GLS
2021/06/02   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/20   GLS
2022/08/05   GLS
********************************************/
#include "PanelF9.h"
#include "..\Atlantis.h"
#include "..\ParameterValues.h"
#include "vc_defs.h"
#include "..\meshres_vc_f9.h"


namespace vc
{
	PanelF9::PanelF9( Atlantis* _sts ):AtlantisPanel( _sts, "F9" )
	{
		DefineMesh( MESHNAME_PANELF9 );
	}

	PanelF9::~PanelF9()
	{
	}

	void PanelF9::DefineVC()
	{
		AddAIDToMouseEventList( AID_F9 );
		return;
	}

	void PanelF9::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_F9, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_F9,
			_V( 0.949898, 2.15454, 14.7274 ) + ofs, _V( 1.17864, 2.15454, 14.7274 ) + ofs,
			_V( 0.951728, 1.83612, 14.6439 ) + ofs, _V( 1.12191, 1.88919, 14.6594 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelF9::Realize()
	{
		AtlantisPanel::Realize();
		return;
	}
};
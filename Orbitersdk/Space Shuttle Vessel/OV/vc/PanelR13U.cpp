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
#include "PanelR13U.h"
#include "..\Atlantis.h"
#include "..\ParameterValues.h"
#include "vc_defs.h"
#include "..\meshres_vc_r13u.h"


namespace vc
{
	PanelR13U::PanelR13U( Atlantis* _sts ):AtlantisPanel( _sts, "R13U" )
	{
		DefineMesh( MESHNAME_PANELR13U );
	}

	PanelR13U::~PanelR13U()
	{
	}

	void PanelR13U::DefineVC()
	{
		AddAIDToMouseEventList( AID_R13U );
		return;
	}

	void PanelR13U::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_R13U, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_R13U,
			_V( 1.54125, 2.43524, 12.561 ) + ofs, _V( 1.54125, 2.43524, 12.2564 ) + ofs,
			_V( 1.30501, 2.28002, 12.561 ) + ofs, _V( 1.30501, 2.28002, 12.2564 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelR13U::Realize()
	{
		AtlantisPanel::Realize();
		return;
	}
};
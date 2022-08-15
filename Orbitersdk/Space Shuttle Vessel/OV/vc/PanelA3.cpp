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
2022/03/24   GLS
2022/03/26   GLS
2022/04/19   GLS
2022/04/20   GLS
2022/05/29   GLS
2022/08/05   GLS
********************************************/
#include "PanelA3.h"
#include "..\Atlantis.h"
#include "..\ParameterValues.h"
#include "vc_defs.h"
#include "..\meshres_vc_a3.h"


namespace vc
{
	PanelA3::PanelA3( Atlantis* _sts ):AtlantisPanel( _sts, "A3" )
	{
		DefineMesh( MESHNAME_PANELA3 );
	}

	PanelA3::~PanelA3()
	{
	}

	void PanelA3::DefineVC()
	{
		AddAIDToMouseEventList( AID_A3 );
		return;
	}

	void PanelA3::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_A3, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_A3,
			_V( -1.0361, 3.1158, 12.4603 ) + ofs, _V( -1.0764, 3.1123, 12.4814 ) + ofs,
			_V( -0.998, 2.7924, 12.5022 ) + ofs, _V( -1.0268, 2.7936, 12.5297 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelA3::Realize()
	{
		AtlantisPanel::Realize();
		return;
	}
};
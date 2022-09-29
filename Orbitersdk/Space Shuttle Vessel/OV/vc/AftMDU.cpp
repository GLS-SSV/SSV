/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2020/06/23   GLS
2021/06/28   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2022/02/07   GLS
2022/03/22   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/19   GLS
2022/04/20   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "AftMDU.h"
#include "MDU.h"
#include "../Atlantis.h"
#include "../meshres_vc.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_a134.h"


namespace vc
{
	AftMDU::AftMDU(Atlantis* _sts)
		: AtlantisPanel(_sts, "AftMDU")
	{
		DefineMesh( MESHNAME_PANELA134 );

		Add(pAFD = new MDU(_sts, "AFD1", MDUID_AFD1));
	}

	AftMDU::~AftMDU()
	{
	}

	void AftMDU::DefineVC()
	{
		AddAIDToMouseEventList(AID_AFTMDU);

		pAFD->SetMouseRegion(AID_AFTMDU, 0.0, 0.0, 1.0, 1.0);
		pAFD->DefineVCGroup( GRP_AFD1_A134_VC );
		pAFD->DefineMaterial( MAT_MDU_AFD1_A134_VC );
	}

	void AftMDU::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea(AID_AFTMDU, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED);

		oapiVCSetAreaClickmode_Quadrilateral (AID_AFTMDU,
			_V(0.776, 3.314, 12.458)+ofs, _V(0.543, 3.297, 12.359)+ofs,
			_V(0.793, 3.089, 12.45)+ofs, _V(0.562, 3.072, 12.352) + _V( 0.001, 0.001, 0.001 )+ofs);
	}
};

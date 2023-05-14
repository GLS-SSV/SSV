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
2023/04/26   GLS
2023/05/12   GLS
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
	AftMDU::AftMDU( Atlantis* _sts, BusManager* pBusManager )
		: AtlantisPanel(_sts, "AftMDU")
	{
		DefineMesh( MESHNAME_PANELA134 );

		Add( pAFD = new MDU( _sts, "AFD1", MDUID_AFD1, pBusManager ) );
	}

	AftMDU::~AftMDU()
	{
	}

	void AftMDU::DefineVC()
	{
		VECTOR3 panel_normal = _V( -0.38746, -0.066186, 0.9195 );

		AddAIDToMouseEventList(AID_AFTMDU);

		pAFD->SetMouseRegion(AID_AFTMDU, 0.0, 0.0, 1.0, 1.0);
		pAFD->DefineVCGroup( GRP_AFD1_A134_VC );
		pAFD->DefineMaterial( MAT_MDU_AFD1_A134_VC );
		pAFD->DefinePowerButtonGroup( GRP_AFD1_ONOFF_A134_VC );
		pAFD->SetPowerButtonReference( _V( 0.774363, 3.114757, 12.468427 ), panel_normal );
		return;
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

	void AftMDU::Realize( void )
	{
		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "MDU_ADC_Power", 16 );
		pAFD->ConnectPower( pBundle, 6 );

		AtlantisPanel::Realize();
		return;
	}
}

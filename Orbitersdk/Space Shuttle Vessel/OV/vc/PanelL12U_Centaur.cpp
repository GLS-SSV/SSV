/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2020/06/23   GLS
2021/06/03   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/20   GLS
2022/05/29   GLS
2022/08/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Panel L12U VC implementation



  Space Shuttle Ultra is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Ultra is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Ultra; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file Doc\Space Shuttle Ultra\GPL.txt for more details.

  **************************************************************************/

#include "PanelL12U_Centaur.h"
#include "StandardSwitch.h"
#include "Talkback.h"
#include "../meshres_vc_l12u_centaur.h"
#include "../Atlantis.h"
#include "..\ParameterValues.h"
#include "vc_defs.h"


namespace vc
{
	PanelL12U_Centaur::PanelL12U_Centaur( Atlantis* _sts ):AtlantisPanel( _sts, "L12U_Centaur" )
	{
		DefineMesh( MESHNAME_PANELL12U_CENTAUR );

		Add( pSUPER_ZIP_PRI_FIRE = new StdSwitch2( _sts, "SUPER*ZIP PRI FIRE" ) );
		pSUPER_ZIP_PRI_FIRE->SetLabel( 1, "FIRE" );

		Add( pSUPER_ZIP_PRI_ARM = new StdSwitch2( _sts, "SUPER*ZIP PRI ARM" ) );
		pSUPER_ZIP_PRI_ARM->SetLabel( 0, "SAFE" );
		pSUPER_ZIP_PRI_ARM->SetLabel( 1, "ARM" );

		Add( pDA_PRI_ROT = new StdSwitch3( _sts, "DA PRI ROT" ) );
		pDA_PRI_ROT->SetLabel( 0, "DN" );
		pDA_PRI_ROT->SetLabel( 2, "UP" );

		Add( pLOGIC_PRI_PWR = new StdSwitch2( _sts, "LOGIC PRI PWR" ) );
		pLOGIC_PRI_PWR->SetLabel( 0, "OFF" );
		pLOGIC_PRI_PWR->SetLabel( 1, "ON" );

		Add( pSSP_PRI_PWR = new StdSwitch2( _sts, "SSP PRI PWR" ) );
		pSSP_PRI_PWR->SetLabel( 0, "OFF" );
		pSSP_PRI_PWR->SetLabel( 1, "ON" );

		Add( pMECH_PRI_PWR = new StdSwitch3( _sts, "MECH PRI PWR" ) );
		pMECH_PRI_PWR->SetLabel( 0, "OFF" );
		pMECH_PRI_PWR->SetLabel( 2, "ON" );


		Add( pSUPER_ZIP_BKUP_FIRE = new StdSwitch2( _sts, "SUPER*ZIP BKUP FIRE" ) );
		pSUPER_ZIP_BKUP_FIRE->SetLabel( 1, "FIRE" );

		Add( pSUPER_ZIP_BKUP_ARM = new StdSwitch2( _sts, "SUPER*ZIP BKUP ARM" ) );
		pSUPER_ZIP_BKUP_ARM->SetLabel( 0, "SAFE" );
		pSUPER_ZIP_BKUP_ARM->SetLabel( 1, "ARM" );

		Add( pDA_BKUP_ROT = new StdSwitch3( _sts, "DA BKUP ROT" ) );
		pDA_BKUP_ROT->SetLabel( 0, "DN" );
		pDA_BKUP_ROT->SetLabel( 2, "UP" );

		Add( pLOGIC_BKUP_PWR = new StdSwitch2( _sts, "LOGIC BKUP PWR" ) );
		pLOGIC_BKUP_PWR->SetLabel( 0, "OFF" );
		pLOGIC_BKUP_PWR->SetLabel( 1, "ON" );

		Add( pSSP_BKUP_PWR = new StdSwitch2( _sts, "SSP BKUP PWR" ) );
		pSSP_BKUP_PWR->SetLabel( 0, "OFF" );
		pSSP_BKUP_PWR->SetLabel( 1, "ON" );

		Add( pMECH_BKUP_PWR = new StdSwitch3( _sts, "MECH BKUP PWR" ) );
		pMECH_BKUP_PWR->SetLabel( 0, "OFF" );
		pMECH_BKUP_PWR->SetLabel( 2, "ON" );

		Add( pMECH_PRI_PWR_TB = new StandardTalkback2( _sts, "MECH PRI PWR TB" ) );
		Add( pPosition_PRI_TB = new StandardTalkback2( _sts, "POSITION PRI TB" ) );
		Add( pSUPER_ZIP_PRI_ARM_TB = new StandardTalkback2( _sts, "SUPER*ZIP PRI ARM TB" ) );
		Add( pMECH_BKUP_PWR_TB = new StandardTalkback2( _sts, "MECH BKUP PWR TB" ) );
		Add( pPosition_BKUP_TB = new StandardTalkback2( _sts, "POSITION BKUP TB" ) );
		Add( pSUPER_ZIP_BKUP_ARM_TB = new StandardTalkback2( _sts, "SUPER*ZIP BKUP ARM TB" ) );
		return;
	}

	PanelL12U_Centaur::~PanelL12U_Centaur()
	{
		return;
	}

	void PanelL12U_Centaur::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;
		oapiVCRegisterArea( AID_L12U_CENTAUR, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBPRESSED | PANEL_MOUSE_LBUP );
		oapiVCSetAreaClickmode_Quadrilateral( AID_L12U_CENTAUR,
			_V( -1.5330, 2.4258, 12.2205 ) + ofs, _V( -1.5330, 2.4258, 12.6776 ) + ofs,
			_V( -1.3427, 2.3011, 12.2205 ) + ofs, _V( -1.3427, 2.3011, 12.6776 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		return;
	}

	void PanelL12U_Centaur::DefineVC()
	{
		const VECTOR3 SWITCH_ROT = _V( 0, 0, 1 );

		AddAIDToMouseEventList( AID_L12U_CENTAUR );

		pSUPER_ZIP_PRI_FIRE->SetInitialAnimState( 0.5f );
		pSUPER_ZIP_PRI_FIRE->DefineGroup( GRP_S2_L12U_CENTAUR_VC );
		pSUPER_ZIP_PRI_FIRE->SetReference( _V( -1.4561, 2.3776, 12.3233 ), SWITCH_ROT );
		pSUPER_ZIP_PRI_FIRE->SetMouseRegion( AID_L12U_CENTAUR, 0.116959f, 0.351245f, 0.159764f, 0.441283f );
		pSUPER_ZIP_PRI_FIRE->SetSpringLoaded( true, 1 );

		pSUPER_ZIP_PRI_ARM->SetInitialAnimState( 0.5f );
		pSUPER_ZIP_PRI_ARM->DefineGroup( GRP_S3_L12U_CENTAUR_VC );
		pSUPER_ZIP_PRI_ARM->SetReference( _V( -1.4561, 2.3776, 12.3233 ), SWITCH_ROT );
		pSUPER_ZIP_PRI_ARM->SetMouseRegion( AID_L12U_CENTAUR, 0.191898f, 0.352835f, 0.236525f, 0.441156f );

		pDA_PRI_ROT->SetInitialAnimState( 0.5f );
		pDA_PRI_ROT->DefineGroup( GRP_S5_L12U_CENTAUR_VC );
		pDA_PRI_ROT->SetReference( _V( -1.4561, 2.3776, 12.3233 ), SWITCH_ROT );
		pDA_PRI_ROT->SetMouseRegion( AID_L12U_CENTAUR, 0.317172f, 0.354949f, 0.358382f, 0.442820f );
		pDA_PRI_ROT->SetSpringLoaded( true );

		pLOGIC_PRI_PWR->SetInitialAnimState( 0.5f );
		pLOGIC_PRI_PWR->DefineGroup( GRP_S6_L12U_CENTAUR_VC );
		pLOGIC_PRI_PWR->SetReference( _V( -1.4561, 2.3776, 12.3233 ), SWITCH_ROT );
		pLOGIC_PRI_PWR->SetMouseRegion( AID_L12U_CENTAUR, 0.375559f, 0.353634f, 0.422636f, 0.441116f );

		pSSP_PRI_PWR->SetInitialAnimState( 0.5f );
		pSSP_PRI_PWR->DefineGroup( GRP_S8_L12U_CENTAUR_VC );
		pSSP_PRI_PWR->SetReference( _V( -1.3684, 2.3204, 12.2933 ), SWITCH_ROT );
		pSSP_PRI_PWR->SetMouseRegion( AID_L12U_CENTAUR, 0.123397f, 0.813643f, 0.167096f, 0.903715f );

		pMECH_PRI_PWR->SetInitialAnimState( 0.5f );
		pMECH_PRI_PWR->DefineGroup( GRP_S9_L12U_CENTAUR_VC );
		pMECH_PRI_PWR->SetReference( _V( -1.3684, 2.3204, 12.2933 ), SWITCH_ROT );
		pMECH_PRI_PWR->SetMouseRegion( AID_L12U_CENTAUR, 0.199524f, 0.813388f, 0.244427f, 0.904525f );
		pMECH_PRI_PWR->SetSpringLoaded( true );


		pSUPER_ZIP_BKUP_FIRE->SetInitialAnimState( 0.5f );
		pSUPER_ZIP_BKUP_FIRE->DefineGroup( GRP_S14_L12U_CENTAUR_VC );
		pSUPER_ZIP_BKUP_FIRE->SetReference( _V( -1.4561, 2.3776, 12.3233 ), SWITCH_ROT );
		pSUPER_ZIP_BKUP_FIRE->SetMouseRegion( AID_L12U_CENTAUR, 0.591131f, 0.352536f, 0.636050f, 0.443414f );
		pSUPER_ZIP_BKUP_FIRE->SetSpringLoaded( true, 1 );

		pSUPER_ZIP_BKUP_ARM->SetInitialAnimState( 0.5f );
		pSUPER_ZIP_BKUP_ARM->DefineGroup( GRP_S15_L12U_CENTAUR_VC );
		pSUPER_ZIP_BKUP_ARM->SetReference( _V( -1.4561, 2.3776, 12.3233 ), SWITCH_ROT );
		pSUPER_ZIP_BKUP_ARM->SetMouseRegion( AID_L12U_CENTAUR, 0.670413f, 0.351977f, 0.715270f, 0.443036f );

		pDA_BKUP_ROT->SetInitialAnimState( 0.5f );
		pDA_BKUP_ROT->DefineGroup( GRP_S17_L12U_CENTAUR_VC );
		pDA_BKUP_ROT->SetReference( _V( -1.4561, 2.3776, 12.3233 ), SWITCH_ROT );
		pDA_BKUP_ROT->SetMouseRegion( AID_L12U_CENTAUR, 0.792740f, 0.353993f, 0.837321f, 0.444548f );
		pDA_BKUP_ROT->SetSpringLoaded( true );

		pLOGIC_BKUP_PWR->SetInitialAnimState( 0.5f );
		pLOGIC_BKUP_PWR->DefineGroup( GRP_S18_L12U_CENTAUR_VC );
		pLOGIC_BKUP_PWR->SetReference( _V( -1.4561, 2.3776, 12.3233 ), SWITCH_ROT );
		pLOGIC_BKUP_PWR->SetMouseRegion( AID_L12U_CENTAUR, 0.852032f, 0.356422f, 0.896194f, 0.440456f );

		pSSP_BKUP_PWR->SetInitialAnimState( 0.5f );
		pSSP_BKUP_PWR->DefineGroup( GRP_S20_L12U_CENTAUR_VC );
		pSSP_BKUP_PWR->SetReference( _V( -1.3684, 2.3204, 12.2933 ), SWITCH_ROT );
		pSSP_BKUP_PWR->SetMouseRegion( AID_L12U_CENTAUR, 0.617838f, 0.812859f, 0.660512f, 0.903650f );

		pMECH_BKUP_PWR->SetInitialAnimState( 0.5f );
		pMECH_BKUP_PWR->DefineGroup( GRP_S21_L12U_CENTAUR_VC );
		pMECH_BKUP_PWR->SetReference( _V( -1.3684, 2.3204, 12.2933 ), SWITCH_ROT );
		pMECH_BKUP_PWR->SetMouseRegion( AID_L12U_CENTAUR, 0.692812f, 0.812956f, 0.735333f, 0.902322f );
		pMECH_BKUP_PWR->SetSpringLoaded( true );

		pSUPER_ZIP_PRI_ARM_TB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS3_U_L12U_CENTAUR_VC, GRP_DS3_L_L12U_CENTAUR_VC );
		pPosition_PRI_TB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS5_U_L12U_CENTAUR_VC, GRP_DS5_L_L12U_CENTAUR_VC );
		pMECH_PRI_PWR_TB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS9_U_L12U_CENTAUR_VC, GRP_DS9_L_L12U_CENTAUR_VC );

		pSUPER_ZIP_BKUP_ARM_TB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS15_U_L12U_CENTAUR_VC, GRP_DS15_L_L12U_CENTAUR_VC );
		pPosition_BKUP_TB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS17_U_L12U_CENTAUR_VC, GRP_DS17_L_L12U_CENTAUR_VC );
		pMECH_BKUP_PWR_TB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS21_U_L12U_CENTAUR_VC, GRP_DS21_L_L12U_CENTAUR_VC );
		return;
	}

	void PanelL12U_Centaur::Realize()
	{
		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "L12UtoCISS_PRI", 16 );
		pSUPER_ZIP_PRI_FIRE->ConnectPort( 1, pBundle, 0 );
		pSUPER_ZIP_PRI_ARM->ConnectPort( 1, pBundle, 1 );
		pSUPER_ZIP_PRI_ARM_TB->SetInput( pBundle, 2, TB_GRAY );
		pDA_PRI_ROT->ConnectPort( 0, pBundle, 3 );
		pDA_PRI_ROT->ConnectPort( 2, pBundle, 4 );
		pPosition_PRI_TB->SetInput( pBundle, 5, TB_GRAY );
		pLOGIC_PRI_PWR->ConnectPort( 1, pBundle, 6 );
		pSSP_PRI_PWR->ConnectPort( 1, pBundle, 7 );
		pMECH_PRI_PWR->ConnectPort( 0, pBundle, 8 );
		pMECH_PRI_PWR->ConnectPort( 2, pBundle, 9 );
		pMECH_PRI_PWR_TB->SetInput( pBundle, 10, TB_GRAY );

		pBundle = STS()->BundleManager()->CreateBundle( "L12UtoCISS_BKUP", 16 );
		pSUPER_ZIP_BKUP_FIRE->ConnectPort( 1, pBundle, 0 );
		pSUPER_ZIP_BKUP_ARM->ConnectPort( 1, pBundle, 1 );
		pSUPER_ZIP_BKUP_ARM_TB->SetInput( pBundle, 2, TB_GRAY );
		pDA_BKUP_ROT->ConnectPort( 0, pBundle, 3 );
		pDA_BKUP_ROT->ConnectPort( 2, pBundle, 4 );
		pPosition_BKUP_TB->SetInput( pBundle, 5, TB_GRAY );
		pLOGIC_BKUP_PWR->ConnectPort( 1, pBundle, 6 );
		pSSP_BKUP_PWR->ConnectPort( 1, pBundle, 7 );
		pMECH_BKUP_PWR->ConnectPort( 0, pBundle, 8 );
		pMECH_BKUP_PWR->ConnectPort( 2, pBundle, 9 );
		pMECH_BKUP_PWR_TB->SetInput( pBundle, 10, TB_GRAY );

		AtlantisPanel::Realize();
		return;
	}
};

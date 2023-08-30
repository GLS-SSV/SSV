/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel 36V73A8A2 implementation



  Space Shuttle Vessel is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Vessel is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Vessel; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file SSV-LICENSE.txt for more details.

  **************************************************************************/
/******* SSV File Modification Notice *******
Date         Developer
2020/05/06   GLS
2020/05/10   GLS
2020/06/20   GLS
2020/06/23   GLS
2020/08/24   GLS
2020/09/02   GLS
2020/09/03   GLS
2021/01/19   GLS
2021/06/03   GLS
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
2022/05/15   GLS
2022/05/16   GLS
2022/05/29   GLS
2022/08/05   GLS
2022/09/29   GLS
2023/07/30   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Panel A8 VC implementation



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
#include "PanelA8A2.h"
#include "StandardSwitch.h"
#include "StandardSwitchCover.h"
#include "Talkback.h"
#include "../meshres_vc_a8a2.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../Atlantis.h"


namespace vc
{
	PanelA8A2::PanelA8A2( Atlantis* _sts ):AtlantisPanel( _sts, "A8A2" )
	{
		DefineMesh( MESHNAME_PANELA8A2 );

		Add( pRMSSelect = new StdSwitch3( _sts, "RMS SELECT" ) );
		pRMSSelect->SetLabel( 0, "PORT" );
		pRMSSelect->SetLabel( 1, "OFF" );
		pRMSSelect->SetLabel( 2, "STBD" );

		Add( pStbdRMSCover = new StandardSwitchCover( _sts, "STARBOARD RMS COVER" ) );

		Add( pStbdRMS = new StdSwitch3( _sts, "STARBOARD RMS" ) );
		pStbdRMS->SetLabel( 2, "DEPLOY" );
		pStbdRMS->SetLabel( 1, "OFF" );
		pStbdRMS->SetLabel( 0, "STOW" );

		Add( pStbdMRL = new StdSwitch3( _sts, "STARBOARD RMS RETENTION LATCHES" ) );
		pStbdMRL->SetLabel( 2, "RELEASE" );
		pStbdMRL->SetLabel( 1, "OFF" );
		pStbdMRL->SetLabel( 0, "LATCH" );

		Add( pPortRMSCover = new StandardSwitchCover( _sts, "PORT RMS COVER" ) );

		Add( pPortRMS = new StdSwitch3( _sts, "PORT RMS" ) );
		pPortRMS->SetLabel( 2, "DEPLOY" );
		pPortRMS->SetLabel( 1, "OFF" );
		pPortRMS->SetLabel( 0, "STOW" );

		Add( pPortMRL = new StdSwitch3( _sts, "PORT RMS RETENTION LATCHES" ) );
		pPortMRL->SetLabel( 2, "RELEASE" );
		pPortMRL->SetLabel( 1, "OFF" );
		pPortMRL->SetLabel( 0, "LATCH" );

		Add( pStbdRMSTb = new StandardTalkback3( _sts, "STARBOARD RMS TB" ) );
		Add( pStbdMRLTb = new StandardTalkback3( _sts, "STARBOARD RMS RETENTION LATCHES TB" ) );

		Add( pStbdMRL_RTL[0] = new StandardTalkback2( _sts, "STARBOARD RMS RETENTION LATCHES READY FOR LATCH FWD" ) );
		Add( pStbdMRL_RTL[1] = new StandardTalkback2( _sts, "STARBOARD RMS RETENTION LATCHES READY FOR LATCH MID" ) );
		Add( pStbdMRL_RTL[2] = new StandardTalkback2( _sts, "STARBOARD RMS RETENTION LATCHES READY FOR LATCH AFT" ) );

		Add( pPortRMSTb = new StandardTalkback3( _sts, "PORT RMS TB" ) );
		Add( pPortMRLTb = new StandardTalkback3( _sts, "PORT RMS RETENTION LATCHES TB" ) );

		Add( pPortMRL_RTL[0] = new StandardTalkback2( _sts, "PORT RMS RETENTION LATCHES READY FOR LATCH FWD" ) );
		Add( pPortMRL_RTL[1] = new StandardTalkback2( _sts, "PORT RMS RETENTION LATCHES READY FOR LATCH MID" ) );
		Add( pPortMRL_RTL[2] = new StandardTalkback2( _sts, "PORT RMS RETENTION LATCHES READY FOR LATCH AFT" ) );

	}

	PanelA8A2::~PanelA8A2()
	{
	}

	void PanelA8A2::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;
		oapiVCRegisterArea( AID_A8A2, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBPRESSED | PANEL_MOUSE_LBUP );
		oapiVCSetAreaClickmode_Quadrilateral( AID_A8A2,
			_V( -0.270182, 2.35742, 12.448 ) + ofs, _V( -0.791144, 2.35742, 12.448 ) + ofs,
			_V( -0.270182, 2.12317, 12.5214 ) + ofs, _V( -0.791144, 2.12317, 12.5214 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		return;
	}

	void PanelA8A2::DefineVC()
	{
		const VECTOR3 switch_rot_vert = _V( -1.0, 0.0, 0.0 );
		const VECTOR3 switch_rot_horz = _V( 0.0, 0.9499, -0.3126 );

		AddAIDToMouseEventList( AID_A8A2 );

		pRMSSelect->SetMouseRegion( AID_A8A2, 0.479694f, 0.210500f, 0.518273f, 0.289998f );
		pRMSSelect->SetReference( _V( -0.530412, 2.2947, 12.4675 ), switch_rot_horz );
		pRMSSelect->DefineGroup( GRP_S1_A8A2_VC );
		pRMSSelect->SetInitialAnimState( 0.5f );
		pRMSSelect->SetOrientation( true );

		pStbdRMSCover->SetMouseRegion( AID_A8A2, 0, 0.098150f, 0.448541f, 0.134312f, 0.563395f );
		pStbdRMSCover->SetMouseRegion( AID_A8A2, 1, 0.098150f, 0.373877f, 0.134312f, 0.448541f );
		pStbdRMSCover->SetReference( _V( -0.321147, 2.253903, 12.480497 ), switch_rot_vert );
		pStbdRMSCover->DefineGroup( GRP_COVER2_A8A2_VC );

		pStbdRMS->SetMouseRegion( AID_A8A2, 0.098150f, 0.448541f, 0.134312f, 0.563395f );
		pStbdRMS->SetReference( _V( -0.326004, 2.239835, 12.48465 ), switch_rot_vert );
		pStbdRMS->DefineGroup( GRP_S2_A8A2_VC );
		pStbdRMS->SetInitialAnimState( 0.5f );

		pStbdMRL->SetMouseRegion( AID_A8A2, 0.184482f, 0.481239f, 0.223794f, 0.567873f );
		pStbdMRL->SetReference( _V( -0.370397, 2.235215, 12.48625 ), switch_rot_vert );
		pStbdMRL->DefineGroup( GRP_S3_A8A2_VC );
		pStbdMRL->SetInitialAnimState( 0.5f );

		pPortRMSCover->SetMouseRegion( AID_A8A2, 0, 0.691518f, 0.441630f, 0.727687f, 0.560525f );
		pPortRMSCover->SetMouseRegion( AID_A8A2, 1, 0.691518f, 0.373877f, 0.727687f, 0.441630f );
		pPortRMSCover->SetReference( _V( -0.630142, 2.255419, 12.47999 ), switch_rot_vert );
		pPortRMSCover->DefineGroup( GRP_COVER5_A8A2_VC );

		pPortRMS->SetMouseRegion( AID_A8A2, 0.691518f, 0.441630f, 0.727687f, 0.560525f );
		pPortRMS->SetReference( _V( -0.634946, 2.241515, 12.4843 ), switch_rot_vert );
		pPortRMS->DefineGroup( GRP_S5_A8A2_VC );
		pPortRMS->SetInitialAnimState( 0.5f );

		pPortMRL->SetMouseRegion( AID_A8A2, 0.780079f, 0.477783f, 0.818926f, 0.564324f );
		pPortMRL->SetReference( _V( -0.68129, 2.235295, 12.4862 ), switch_rot_vert );
		pPortMRL->DefineGroup( GRP_S6_A8A2_VC );
		pPortMRL->SetInitialAnimState( 0.5f );

		pStbdRMSTb->DefineMeshGroup( GetVCMeshIndex(), GRP_DS1_A8A2_VC );
		pStbdMRLTb->DefineMeshGroup( GetVCMeshIndex(), GRP_DS2_A8A2_VC );

		pStbdMRL_RTL[0]->DefineMeshGroups( GetVCMeshIndex(), GRP_DS9_U_A8A2_VC, GRP_DS9_L_A8A2_VC );
		pStbdMRL_RTL[1]->DefineMeshGroups( GetVCMeshIndex(), GRP_DS7_U_A8A2_VC, GRP_DS7_L_A8A2_VC );
		pStbdMRL_RTL[2]->DefineMeshGroups( GetVCMeshIndex(), GRP_DS3_U_A8A2_VC, GRP_DS3_L_A8A2_VC );

		pPortRMSTb->DefineMeshGroup( GetVCMeshIndex(), GRP_DS4_A8A2_VC );
		pPortMRLTb->DefineMeshGroup( GetVCMeshIndex(), GRP_DS5_A8A2_VC );

		pPortMRL_RTL[0]->DefineMeshGroups( GetVCMeshIndex(), GRP_DS10_U_A8A2_VC, GRP_DS10_L_A8A2_VC );
		pPortMRL_RTL[1]->DefineMeshGroups( GetVCMeshIndex(), GRP_DS8_U_A8A2_VC, GRP_DS8_L_A8A2_VC );
		pPortMRL_RTL[2]->DefineMeshGroups( GetVCMeshIndex(), GRP_DS6_U_A8A2_VC, GRP_DS6_L_A8A2_VC );
		return;
	}

	void PanelA8A2::Realize()
	{
		DiscreteBundle* pBundle=STS()->BundleManager()->CreateBundle( "RMS", 16 );
		pRMSSelect->ConnectPort( 0, pBundle, 6 );

		pBundle = STS()->BundleManager()->CreateBundle( "MPM_D&C", 16 );
		pPortRMS->ConnectPort( 0, pBundle, 0 );
		pPortRMS->ConnectPort( 2, pBundle, 1 );
		PORT_MPM_SYSTEM_1_STOW.Connect( pBundle, 2 );
		PORT_MPM_SYSTEM_1_DEPLOY.Connect( pBundle, 3 );
		PORT_MPM_SYSTEM_2_STOW.Connect( pBundle, 4 );
		PORT_MPM_SYSTEM_2_DEPLOY.Connect( pBundle, 5 );
		pStbdRMS->ConnectPort( 0, pBundle, 6 );
		pStbdRMS->ConnectPort( 2, pBundle, 7 );
		STBD_MPM_SYSTEM_1_STOW.Connect( pBundle, 8 );
		STBD_MPM_SYSTEM_1_DEPLOY.Connect( pBundle, 9 );
		STBD_MPM_SYSTEM_2_STOW.Connect( pBundle, 10 );
		STBD_MPM_SYSTEM_2_DEPLOY.Connect( pBundle, 11 );

		pBundle = STS()->BundleManager()->CreateBundle( "A8A2_INTERNAL", 16 );
		PORT_MPM_STOW.Connect( pBundle, 0 );
		PORT_MPM_DEPLOY.Connect( pBundle, 1 );
		STBD_MPM_STOW.Connect( pBundle, 2 );
		STBD_MPM_DEPLOY.Connect( pBundle, 3 );
		pPortRMSTb->SetInput( 1, pBundle, 0, TB_STO );
		pPortRMSTb->SetInput( 0, pBundle, 1, TB_DPY );
		pStbdRMSTb->SetInput( 1, pBundle, 2, TB_STO );
		pStbdRMSTb->SetInput( 0, pBundle, 3, TB_DPY );

		pBundle = STS()->BundleManager()->CreateBundle( "MRL_D&C", 16 );
		pPortMRL->ConnectPort( 0, pBundle, 0 );
		pPortMRL->ConnectPort( 2, pBundle, 1 );
		pPortMRLTb->SetInput( 1, pBundle, 2, TB_LAT );
		pPortMRLTb->SetInput( 0, pBundle, 3, TB_REL );
		pStbdMRL->ConnectPort( 0, pBundle, 4 );
		pStbdMRL->ConnectPort( 2, pBundle, 5 );
		pStbdMRLTb->SetInput( 1, pBundle, 6, TB_LAT );
		pStbdMRLTb->SetInput( 0, pBundle, 7, TB_REL );

		pBundle = STS()->BundleManager()->CreateBundle( "PORT_FWD_MRL_CTRL", 16 );
		pPortMRL_RTL[0]->SetInput( pBundle, 7, TB_GRAY );
		pBundle = STS()->BundleManager()->CreateBundle( "PORT_MID_MRL_CTRL", 16 );
		pPortMRL_RTL[1]->SetInput( pBundle, 7, TB_GRAY );
		pBundle = STS()->BundleManager()->CreateBundle( "PORT_AFT_MRL_CTRL", 16 );
		pPortMRL_RTL[2]->SetInput( pBundle, 7, TB_GRAY );

		pBundle = STS()->BundleManager()->CreateBundle( "STBD_FWD_MRL_CTRL", 16 );
		pStbdMRL_RTL[0]->SetInput( pBundle, 7, TB_GRAY );
		pBundle = STS()->BundleManager()->CreateBundle( "STBD_MID_MRL_CTRL", 16 );
		pStbdMRL_RTL[1]->SetInput( pBundle, 7, TB_GRAY );
		pBundle = STS()->BundleManager()->CreateBundle( "STBD_AFT_MRL_CTRL", 16 );
		pStbdMRL_RTL[2]->SetInput( pBundle, 7, TB_GRAY );

		AtlantisPanel::Realize();
		return;
	}

	void PanelA8A2::OnPostStep( double simt, double simdt, double mjd )
	{
		AtlantisPanel::OnPostStep( simt, simdt, mjd );

		if (PORT_MPM_SYSTEM_1_STOW || PORT_MPM_SYSTEM_2_STOW) PORT_MPM_STOW.SetLine();
		else PORT_MPM_STOW.ResetLine();

		if (PORT_MPM_SYSTEM_1_DEPLOY || PORT_MPM_SYSTEM_2_DEPLOY) PORT_MPM_DEPLOY.SetLine();
		else PORT_MPM_DEPLOY.ResetLine();

		if (STBD_MPM_SYSTEM_1_STOW || STBD_MPM_SYSTEM_2_STOW) STBD_MPM_STOW.SetLine();
		else STBD_MPM_STOW.ResetLine();

		if (STBD_MPM_SYSTEM_1_DEPLOY || STBD_MPM_SYSTEM_2_DEPLOY) STBD_MPM_DEPLOY.SetLine();
		else STBD_MPM_DEPLOY.ResetLine();
		return;
	}
}

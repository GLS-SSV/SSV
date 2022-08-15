/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
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

  Panel L10 VC implementation



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

#include "PanelL10_IUS.h"
#include "StandardSwitch.h"
#include "Talkback.h"
#include "../Atlantis.h"
#include "..\ParameterValues.h"
#include "vc_defs.h"
#include "..\meshres_vc_l10_ius.h"


namespace vc
{
	PanelL10_IUS::PanelL10_IUS( Atlantis* _sts ):AtlantisPanel( _sts, "L10_IUS" )
	{
		DefineMesh( MESHNAME_PANELL10_IUS );

		Add( pPanelMode = new LockableLever2( _sts, "PANEL MODE" ) );
		pPanelMode->SetLabel( 0, "ALTERNATE" );
		pPanelMode->SetLabel( 1, "PRIMARY" );
		pPanelMode->SetInitialPosition( 1 );

		Add( pPowerSourceASEBatteriesPri = new StdSwitch3( _sts, "POWER SOURCE ASE BATTERIES PRI" ) );
		pPowerSourceASEBatteriesPri->SetLabel( 0, "OFF" );
		pPowerSourceASEBatteriesPri->SetLabel( 1, "-" );
		pPowerSourceASEBatteriesPri->SetLabel( 2, "ON" );

		Add( pPowerSourceASEBatteriesAlt = new StdSwitch3( _sts, "POWER SOURCE ASE BATTERIES ALT" ) );
		pPowerSourceASEBatteriesAlt->SetLabel( 0, "OFF" );
		pPowerSourceASEBatteriesAlt->SetLabel( 1, "-" );
		pPowerSourceASEBatteriesAlt->SetLabel( 2, "ON" );

		Add( pPowerSourceOrbiterSCConvPwrPri = new StdSwitch3( _sts, "POWER SOURCE ORBITER S/C CONV PWR PRI" ) );
		pPowerSourceOrbiterSCConvPwrPri->SetLabel( 0, "OFF" );
		pPowerSourceOrbiterSCConvPwrPri->SetLabel( 1, "-" );
		pPowerSourceOrbiterSCConvPwrPri->SetLabel( 2, "ON" );

		Add( pPowerSourceOrbiterSCConvPwrAlt = new StdSwitch3( _sts, "POWER SOURCE ORBITER S/C CONV PWR ALT" ) );
		pPowerSourceOrbiterSCConvPwrAlt->SetLabel( 0, "OFF" );
		pPowerSourceOrbiterSCConvPwrAlt->SetLabel( 1, "-" );
		pPowerSourceOrbiterSCConvPwrAlt->SetLabel( 2, "ON" );

		Add( pPowerSourceIUSSCBatteryPri = new StdSwitch3( _sts, "POWER SOURCE IUS S/C BATTERY PRI" ) );
		pPowerSourceIUSSCBatteryPri->SetLabel( 0, "STAGE I & II OFF" );
		pPowerSourceIUSSCBatteryPri->SetLabel( 1, "-" );
		pPowerSourceIUSSCBatteryPri->SetLabel( 2, "STAGE I ON" );

		Add( pPowerSourceIUSSCBatteryAlt = new StdSwitch3( _sts, "POWER SOURCE IUS S/C BATTERY ALT" ) );
		pPowerSourceIUSSCBatteryAlt->SetLabel( 0, "STAGE I & II OFF" );
		pPowerSourceIUSSCBatteryAlt->SetLabel( 1, "-" );
		pPowerSourceIUSSCBatteryAlt->SetLabel( 2, "STAGE I ON" );

		Add( pPowerSourceIUSBusABatteriesPri = new StdSwitch3( _sts, "POWER SOURCE IUS BUS A BATTERIES PRI" ) );
		pPowerSourceIUSBusABatteriesPri->SetLabel( 0, "STAGE I & II OFF" );
		pPowerSourceIUSBusABatteriesPri->SetLabel( 1, "-" );
		pPowerSourceIUSBusABatteriesPri->SetLabel( 2, "STAGE I ON" );

		Add( pPowerSourceIUSBusABatteriesAlt = new StdSwitch3( _sts, "POWER SOURCE IUS BUS A BATTERIES ALT" ) );
		pPowerSourceIUSBusABatteriesAlt->SetLabel( 0, "STAGE I & II OFF" );
		pPowerSourceIUSBusABatteriesAlt->SetLabel( 1, "-" );
		pPowerSourceIUSBusABatteriesAlt->SetLabel( 2, "STAGE I ON" );

		Add( pPowerSourceIUSBusBBatteriesPri = new StdSwitch3( _sts, "POWER SOURCE IUS BUS B BATTERIES PRI" ) );
		pPowerSourceIUSBusBBatteriesPri->SetLabel( 0, "STAGE I & II OFF" );
		pPowerSourceIUSBusBBatteriesPri->SetLabel( 1, "-" );
		pPowerSourceIUSBusBBatteriesPri->SetLabel( 2, "STAGE I ON" );

		Add( pPowerSourceIUSBusBBatteriesAlt = new StdSwitch3( _sts, "POWER SOURCE IUS BUS B BATTERIES ALT" ) );
		pPowerSourceIUSBusBBatteriesAlt->SetLabel( 0, "STAGE I & II OFF" );
		pPowerSourceIUSBusBBatteriesAlt->SetLabel( 1, "-" );
		pPowerSourceIUSBusBBatteriesAlt->SetLabel( 2, "STAGE I ON" );

		Add( pIUSConvPwrPri = new StdSwitch3( _sts, "IUS CONV PWR PRI" ) );
		pIUSConvPwrPri->SetLabel( 0, "OFF" );
		pIUSConvPwrPri->SetLabel( 1, "-" );
		pIUSConvPwrPri->SetLabel( 2, "ON" );

		Add( pIUSConvPwrAlt = new StdSwitch3( _sts, "IUS CONV PWR ALT" ) );
		pIUSConvPwrAlt->SetLabel( 0, "OFF" );
		pIUSConvPwrAlt->SetLabel( 1, "-" );
		pIUSConvPwrAlt->SetLabel( 2, "ON" );

		Add( pSCSupportSCRegPwrPri = new StdSwitch3( _sts, "S/C SUPPORT S/C REG PWR PRI" ) );
		pSCSupportSCRegPwrPri->SetLabel( 0, "OFF" );
		pSCSupportSCRegPwrPri->SetLabel( 1, "-" );
		pSCSupportSCRegPwrPri->SetLabel( 2, "ON" );

		Add( pSCSupportSCRegPwrAlt = new StdSwitch3( _sts, "S/C SUPPORT S/C REG PWR ALT" ) );
		pSCSupportSCRegPwrAlt->SetLabel( 0, "OFF" );
		pSCSupportSCRegPwrAlt->SetLabel( 1, "-" );
		pSCSupportSCRegPwrAlt->SetLabel( 2, "ON" );

		Add( pSCSupportSCPowerPri = new StdSwitch3( _sts, "S/C SUPPORT S/C POWER PRI" ) );
		pSCSupportSCPowerPri->SetLabel( 0, "OFF" );
		pSCSupportSCPowerPri->SetLabel( 1, "-" );
		pSCSupportSCPowerPri->SetLabel( 2, "ON" );

		Add( pSCSupportSCPowerAlt = new StdSwitch3( _sts, "S/C SUPPORT S/C POWER ALT" ) );
		pSCSupportSCPowerAlt->SetLabel( 0, "OFF" );
		pSCSupportSCPowerAlt->SetLabel( 1, "-" );
		pSCSupportSCPowerAlt->SetLabel( 2, "ON" );

		Add( pIUSSupportAFeedPri = new StdSwitch3( _sts, "IUS SUPPORT A FEED PRI" ) );
		pIUSSupportAFeedPri->SetLabel( 0, "OFF" );
		pIUSSupportAFeedPri->SetLabel( 1, "-" );
		pIUSSupportAFeedPri->SetLabel( 2, "ON" );

		Add( pIUSSupportAFeedAlt = new StdSwitch3( _sts, "IUS SUPPORT A FEED ALT" ) );
		pIUSSupportAFeedAlt->SetLabel( 0, "OFF" );
		pIUSSupportAFeedAlt->SetLabel( 1, "-" );
		pIUSSupportAFeedAlt->SetLabel( 2, "ON" );

		Add( pIUSSupportBFeedPri = new StdSwitch3( _sts, "IUS SUPPORT B FEED PRI" ) );
		pIUSSupportBFeedPri->SetLabel( 0, "OFF" );
		pIUSSupportBFeedPri->SetLabel( 1, "-" );
		pIUSSupportBFeedPri->SetLabel( 2, "ON" );

		Add( pIUSSupportBFeedAlt = new StdSwitch3( _sts, "IUS SUPPORT B FEED ALT" ) );
		pIUSSupportBFeedAlt->SetLabel( 0, "OFF" );
		pIUSSupportBFeedAlt->SetLabel( 1, "-" );
		pIUSSupportBFeedAlt->SetLabel( 2, "ON" );

		Add( pTestPri = new StdSwitch3( _sts, "TEST PRI" ) );
		pTestPri->SetLabel( 0, "BARBER POLE" );
		pTestPri->SetLabel( 1, "-" );
		pTestPri->SetLabel( 2, "GRAY" );

		Add( pTestAlt = new StdSwitch3( _sts, "TEST ALT" ) );
		pTestAlt->SetLabel( 0, "BARBER POLE" );
		pTestAlt->SetLabel( 1, "-" );
		pTestAlt->SetLabel( 2, "GRAY" );

		Add( pIUSSupportHeatersBatteryPri = new StdSwitch3( _sts, "IUS SUPPORT HEATERS BATTERY PRI" ) );
		pIUSSupportHeatersBatteryPri->SetLabel( 0, "OFF" );
		pIUSSupportHeatersBatteryPri->SetLabel( 1, "-" );
		pIUSSupportHeatersBatteryPri->SetLabel( 2, "ON" );

		Add( pIUSSupportHeatersBatteryAlt = new StdSwitch3( _sts, "IUS SUPPORT HEATERS BATTERY ALT" ) );
		pIUSSupportHeatersBatteryAlt->SetLabel( 0, "OFF" );
		pIUSSupportHeatersBatteryAlt->SetLabel( 1, "-" );
		pIUSSupportHeatersBatteryAlt->SetLabel( 2, "ON" );

		Add( pIUSSupportHeatersCriticalPri = new StdSwitch3( _sts, "IUS SUPPORT HEATERS CRITICAL PRI" ) );
		pIUSSupportHeatersCriticalPri->SetLabel( 0, "OFF" );
		pIUSSupportHeatersCriticalPri->SetLabel( 1, "-" );
		pIUSSupportHeatersCriticalPri->SetLabel( 2, "ON" );

		Add( pIUSSupportHeatersCriticalAlt = new StdSwitch3( _sts, "IUS SUPPORT HEATERS CRITICAL ALT" ) );
		pIUSSupportHeatersCriticalAlt->SetLabel( 0, "OFF" );
		pIUSSupportHeatersCriticalAlt->SetLabel( 1, "-" );
		pIUSSupportHeatersCriticalAlt->SetLabel( 2, "ON" );

		Add( pIUSSupportWBDIPri = new StdSwitch3( _sts, "IUS SUPPORT WBDI PRI" ) );
		pIUSSupportWBDIPri->SetLabel( 0, "OFF" );
		pIUSSupportWBDIPri->SetLabel( 1, "-" );
		pIUSSupportWBDIPri->SetLabel( 2, "ON" );

		Add( pIUSSupportWBDIAlt = new StdSwitch3( _sts, "IUS SUPPORT WBDI ALT" ) );
		pIUSSupportWBDIAlt->SetLabel( 0, "OFF" );
		pIUSSupportWBDIAlt->SetLabel( 1, "-" );
		pIUSSupportWBDIAlt->SetLabel( 2, "ON" );

		Add( pIUSPowerPri = new StdSwitch3( _sts, "IUS POWER PRI" ) );
		pIUSPowerPri->SetLabel( 0, "OFF" );
		pIUSPowerPri->SetLabel( 1, "-" );
		pIUSPowerPri->SetLabel( 2, "ON" );

		Add( pIUSPowerAlt = new StdSwitch3( _sts, "IUS POWER ALT" ) );
		pIUSPowerAlt->SetLabel( 0, "OFF" );
		pIUSPowerAlt->SetLabel( 1, "-" );
		pIUSPowerAlt->SetLabel( 2, "ON" );

		Add( pNormBusPwrPri = new StdSwitch3( _sts, "NORM BUS PWR PRI" ) );
		pNormBusPwrPri->SetLabel( 0, "OFF" );
		pNormBusPwrPri->SetLabel( 1, "-" );
		pNormBusPwrPri->SetLabel( 2, "ON" );

		Add( pNormBusPwrAlt = new StdSwitch3( _sts, "NORM BUS PWR ALT" ) );
		pNormBusPwrAlt->SetLabel( 0, "OFF" );
		pNormBusPwrAlt->SetLabel( 1, "-" );
		pNormBusPwrAlt->SetLabel( 2, "ON" );

		Add( pIUSSupportAutoShutdownStandbyModePri = new StdSwitch3( _sts, "IUS SUPPORT AUTO SHUTDOWN STANDBY MODE PRI" ) );
		pIUSSupportAutoShutdownStandbyModePri->SetLabel( 0, "OFF" );
		pIUSSupportAutoShutdownStandbyModePri->SetLabel( 1, "-" );
		pIUSSupportAutoShutdownStandbyModePri->SetLabel( 2, "ENABLE" );

		Add( pIUSSupportAutoShutdownStandbyModeAlt = new StdSwitch3( _sts, "IUS SUPPORT AUTO SHUTDOWN STANDBY MODE ALT" ) );
		pIUSSupportAutoShutdownStandbyModeAlt->SetLabel( 0, "OFF" );
		pIUSSupportAutoShutdownStandbyModeAlt->SetLabel( 1, "-" );
		pIUSSupportAutoShutdownStandbyModeAlt->SetLabel( 2, "ENABLE" );

		Add( pTiltTableActuatorDriveEnablePri1 = new StdSwitch3( _sts, "TILT TABLE ACTUATOR DRIVE ENABLE PRI 1" ) );
		pTiltTableActuatorDriveEnablePri1->SetLabel( 0, "INTERMEDIATE" );
		pTiltTableActuatorDriveEnablePri1->SetLabel( 1, "OFF" );
		pTiltTableActuatorDriveEnablePri1->SetLabel( 2, "MAXIMUM" );

		Add( pTiltTableActuatorDriveEnableAlt2 = new StdSwitch3( _sts, "TILT TABLE ACTUATOR DRIVE ENABLE ALT 2" ) );
		pTiltTableActuatorDriveEnableAlt2->SetLabel( 0, "INTERMEDIATE" );
		pTiltTableActuatorDriveEnableAlt2->SetLabel( 1, "OFF" );
		pTiltTableActuatorDriveEnableAlt2->SetLabel( 2, "MAXIMUM" );

		Add( pTiltTableActuatorMotionPri1 = new StdSwitch3( _sts, "TILT TABLE ACTUATOR MOTION PRI 1" ) );
		pTiltTableActuatorMotionPri1->SetLabel( 0, "LOWER" );
		pTiltTableActuatorMotionPri1->SetLabel( 1, "-" );
		pTiltTableActuatorMotionPri1->SetLabel( 2, "RAISE" );

		Add( pTiltTableActuatorMotionAlt2 = new StdSwitch3( _sts, "TILT TABLE ACTUATOR MOTION ALT 2" ) );
		pTiltTableActuatorMotionAlt2->SetLabel( 0, "LOWER" );
		pTiltTableActuatorMotionAlt2->SetLabel( 1, "-" );
		pTiltTableActuatorMotionAlt2->SetLabel( 2, "RAISE" );

		Add( pTiltTableActuatorAltDrAct1 = new LockableLever2( _sts, "TILT TABLE ACTUATOR ALT DR ACT 1" ) );
		pTiltTableActuatorAltDrAct1->SetLabel( 0, "OFF" );
		pTiltTableActuatorAltDrAct1->SetLabel( 1, "DISENGAGE" );

		Add( pCmdPathEnabled = new LockableLever3( _sts, "CMD PATH ENABLED" ) );
		pCmdPathEnabled->SetLabel( 0, "HARDLINE" );
		pCmdPathEnabled->SetLabel( 1, "RF" );
		pCmdPathEnabled->SetLabel( 2, "HARDLINE" );

		Add( pPyroBusPri = new StdSwitch3( _sts, "PYRO BUS PRI" ) );
		pPyroBusPri->SetLabel( 0, "OFF" );
		pPyroBusPri->SetLabel( 1, "-" );
		pPyroBusPri->SetLabel( 2, "ON" );

		Add( pPyroBusAlt = new StdSwitch3( _sts, "PYRO BUS ALT" ) );
		pPyroBusAlt->SetLabel( 0, "OFF" );
		pPyroBusAlt->SetLabel( 1, "-" );
		pPyroBusAlt->SetLabel( 2, "ON" );

		Add( pUmbilicalsEnaPri = new StdSwitch3( _sts, "UMBILICALS ENA PRI" ) );
		pUmbilicalsEnaPri->SetLabel( 0, "OFF" );
		pUmbilicalsEnaPri->SetLabel( 1, "-" );
		pUmbilicalsEnaPri->SetLabel( 2, "ENABLE" );

		Add( pUmbilicalsEnaAlt = new StdSwitch3( _sts, "UMBILICALS ENA ALT" ) );
		pUmbilicalsEnaAlt->SetLabel( 0, "OFF" );
		pUmbilicalsEnaAlt->SetLabel( 1, "-" );
		pUmbilicalsEnaAlt->SetLabel( 2, "ENABLE" );

		Add( pUmbilicalsRelPri = new LockableLever2( _sts, "UMBILICALS REL PRI" ) );
		pUmbilicalsRelPri->SetLabel( 0, "OFF" );
		pUmbilicalsRelPri->SetLabel( 1, "RELEASE" );

		Add( pUmbilicalsRelAlt = new LockableLever2( _sts, "UMBILICALS REL ALT" ) );
		pUmbilicalsRelAlt->SetLabel( 0, "OFF" );
		pUmbilicalsRelAlt->SetLabel( 1, "RELEASE" );

		Add( pIUSDeploymentEnaPri = new StdSwitch3( _sts, "IUS DEPLOYMENT ENA PRI" ) );
		pIUSDeploymentEnaPri->SetLabel( 0, "OFF" );
		pIUSDeploymentEnaPri->SetLabel( 1, "-" );
		pIUSDeploymentEnaPri->SetLabel( 2, "ENABLE" );

		Add( pIUSDeploymentEnaAlt = new StdSwitch3( _sts, "IUS DEPLOYMENT ENA ALT" ) );
		pIUSDeploymentEnaAlt->SetLabel( 0, "OFF" );
		pIUSDeploymentEnaAlt->SetLabel( 1, "-" );
		pIUSDeploymentEnaAlt->SetLabel( 2, "ENABLE" );

		Add( pIUSDeploymentDpyPri = new LockableLever2( _sts, "IUS DEPLOYMENT DPY PRI" ) );
		pIUSDeploymentDpyPri->SetLabel( 0, "OFF" );
		pIUSDeploymentDpyPri->SetLabel( 1, "DEPLOY" );

		Add( pIUSDeploymentDpyAlt = new LockableLever2( _sts, "IUS DEPLOYMENT DPY ALT" ) );
		pIUSDeploymentDpyAlt->SetLabel( 0, "OFF" );
		pIUSDeploymentDpyAlt->SetLabel( 1, "DEPLOY" );

		Add( pPowerKill = new LockableLever2( _sts, "POWER KILL" ) );
		pPowerKill->SetLabel( 0, "OFF" );
		pPowerKill->SetLabel( 1, "KILL" );

		Add( pPowerSourceASEBatteriesPriTB = new StandardTalkback2( _sts, "POWER SOURCE ASE BATTERIES PRI TB" ) );
		Add( pPowerSourceASEBatteriesAltTB = new StandardTalkback2( _sts, "POWER SOURCE ASE BATTERIES ALT TB" ) );
		Add( pPowerSourceOrbiterSCConvPwrPriTB = new StandardTalkback2( _sts, "POWER SOURCE ORBITER S/C CONV PWR PRI TB" ) );
		Add( pPowerSourceOrbiterSCConvPwrAltTB = new StandardTalkback2( _sts, "POWER SOURCE ORBITER S/C CONV PWR ALT TB" ) );
		Add( pPowerSourceIUSSCBatteryPriTB = new StandardTalkback2( _sts, "POWER SOURCE IUS S/C BATTERY PRI TB" ) );
		Add( pPowerSourceIUSSCBatteryAltTB = new StandardTalkback2( _sts, "POWER SOURCE IUS S/C BATTERY ALT TB" ) );
		Add( pPowerSourceIUSBusABatteriesPriTB = new StandardTalkback2( _sts, "POWER SOURCE IUS BUS A BATTERIES PRI TB" ) );
		Add( pPowerSourceIUSBusABatteriesAltTB = new StandardTalkback2( _sts, "POWER SOURCE IUS BUS A BATTERIES ALT TB" ) );
		Add( pPowerSourceIUSBusBBatteriesPriTB = new StandardTalkback2( _sts, "POWER SOURCE IUS BUS B BATTERIES PRI TB" ) );
		Add( pPowerSourceIUSBusBBatteriesAltTB = new StandardTalkback2( _sts, "POWER SOURCE IUS BUS B BATTERIES ALT TB" ) );
		Add( pIUSConvPwrPriTB = new StandardTalkback2( _sts, "IUS CONV PWR PRI TB" ) );
		Add( pIUSConvPwrAltTB = new StandardTalkback2( _sts, "IUS CONV PWR ALT TB" ) );
		Add( pSCSupportSCRegPwrPriTB = new StandardTalkback2( _sts, "S/C SUPPORT S/C REG PWR PRI TB" ) );
		Add( pSCSupportSCRegPwrAltTB = new StandardTalkback2( _sts, "S/C SUPPORT S/C REG PWR ALT TB" ) );
		Add( pSCSupportSCPowerPriTB = new StandardTalkback2( _sts, "S/C SUPPORT S/C POWER PRI TB" ) );
		Add( pSCSupportSCPowerAltTB = new StandardTalkback2( _sts, "S/C SUPPORT S/C POWER ALT TB" ) );
		Add( pIUSSupportAFeedPriTB = new StandardTalkback2( _sts, "IUS SUPPORT A FEED PRI TB" ) );
		Add( pIUSSupportAFeedAltTB = new StandardTalkback2( _sts, "IUS SUPPORT A FEED ALT TB" ) );
		Add( pIUSSupportBFeedPriTB = new StandardTalkback2( _sts, "IUS SUPPORT B FEED PRI TB" ) );
		Add( pIUSSupportBFeedAltTB = new StandardTalkback2( _sts, "IUS SUPPORT B FEED ALT TB" ) );
		Add( pMatrixStatusPriTB = new StandardTalkback2( _sts, "MATRIX STATUS PRI TB" ) );
		Add( pMatrixStatusAltTB = new StandardTalkback2( _sts, "MATRIX STATUS ALT TB" ) );
		Add( pIUSSupportHeatersBatteryPriTB = new StandardTalkback2( _sts, "IUS SUPPORT HEATERS BATTERY PRI TB" ) );
		Add( pIUSSupportHeatersBatteryAltTB = new StandardTalkback2( _sts, "IUS SUPPORT HEATERS BATTERY ALT TB" ) );
		Add( pIUSSupportHeatersCriticalPriTB = new StandardTalkback2( _sts, "IUS SUPPORT HEATERS CRITICAL PRI TB" ) );
		Add( pIUSSupportHeatersCriticalAltTB = new StandardTalkback2( _sts, "IUS SUPPORT HEATERS CRITICAL ALT TB" ) );
		Add( pIUSSupportWBDIPriTB = new StandardTalkback2( _sts, "IUS SUPPORT WBDI PRI TB" ) );
		Add( pIUSSupportWBDIAltTB = new StandardTalkback2( _sts, "IUS SUPPORT WBDI ALT TB" ) );
		Add( pIUSPowerPriTB = new StandardTalkback2( _sts, "IUS POWER PRI TB" ) );
		Add( pIUSPowerAltTB = new StandardTalkback2( _sts, "IUS POWER ALT TB" ) );
		Add( pNormBusPwrPriTB = new StandardTalkback2( _sts, "NORM BUS PWR PRI TB" ) );
		Add( pNormBusPwrAltTB = new StandardTalkback2( _sts, "NORM BUS PWR ALT TB" ) );
		Add( pIUSSupportAutoShutdownStandbyModePriTB = new StandardTalkback2( _sts, "IUS SUPPORT AUTO SHUTDOWN STANDBY MODE PRI TB" ) );
		Add( pIUSSupportAutoShutdownStandbyModeAltTB = new StandardTalkback2( _sts, "IUS SUPPORT AUTO SHUTDOWN STANDBY MODE ALT TB" ) );
		Add( pTiltTableActuatorMotionPri1TB = new StandardTalkback2( _sts, "TILT TABLE ACTUATOR MOTION PRI 1 TB" ) );
		Add( pTiltTableActuatorMotionAlt2TB = new StandardTalkback2( _sts, "TILT TABLE ACTUATOR MOTION ALT 2 TB" ) );
		Add( pTiltTableActuatorPositionPri1TB = new StandardTalkback2( _sts, "TILT TABLE ACTUATOR POSITION PRI 1 TB" ) );
		Add( pTiltTableActuatorPositionAlt2TB = new StandardTalkback2( _sts, "TILT TABLE ACTUATOR POSITION ALT 2 TB" ) );
		Add( pTiltTableActuatorPriDrAct1EngagedTB = new StandardTalkback2( _sts, "TILT TABLE ACTUATOR PRI DR ACT 1 ENGAGED TB" ) );
		Add( pTiltTableActuatorAltDrAct2EngagedTB = new StandardTalkback2( _sts, "TILT TABLE ACTUATOR ALT DR ACT 2 ENGAGED TB" ) );
		Add( pPyroBusPriTB = new StandardTalkback2( _sts, "PYRO BUS PRI TB" ) );
		Add( pPyroBusAltTB = new StandardTalkback2( _sts, "PYRO BUS ALT TB" ) );
		Add( pUmbilicalsEnaPriTB = new StandardTalkback2( _sts, "UMBILICALS ENA PRI TB" ) );
		Add( pUmbilicalsEnaAltTB = new StandardTalkback2( _sts, "UMBILICALS ENA ALT TB" ) );
		Add( pUmbilicalsRelPriTB = new StandardTalkback2( _sts, "UMBILICALS REL PRI TB" ) );
		Add( pUmbilicalsRelAltTB = new StandardTalkback2( _sts, "UMBILICALS REL ALT TB" ) );
		Add( pIUSDeploymentEnaPriTB = new StandardTalkback2( _sts, "IUS DEPLOYMENT ENA PRI TB" ) );
		Add( pIUSDeploymentEnaAltTB = new StandardTalkback2( _sts, "IUS DEPLOYMENT ENA ALT TB" ) );
		return;
	}

	PanelL10_IUS::~PanelL10_IUS()
	{
		return;
	}

	void PanelL10_IUS::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;
		oapiVCRegisterArea( AID_L10_IUS, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBPRESSED | PANEL_MOUSE_LBUP );
		oapiVCSetAreaClickmode_Quadrilateral( AID_L10_IUS,
			_V( -1.5437, 2.4325, 13.0847 ) + ofs, _V( -1.5437, 2.4325, 13.6310 ) + ofs,
			_V( -1.0516, 2.1129, 13.0847 ) + ofs, _V( -1.0516, 2.1129, 13.6310 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelL10_IUS::DefineVC()
	{
		const VECTOR3 SWITCH_ROT = _V( 0, 0, 1 );
		const VECTOR3 SWITCH_PULL = _V( 0.544639, 0.838671, 0 );

		AddAIDToMouseEventList( AID_L10_IUS );

		pPanelMode->SetInitialAnimState( 0.5f );
		pPanelMode->DefineGroup( GRP_S61_L10_IUS_VC );
		pPanelMode->SetReference( _V( -1.4702, 2.3884, 13.5557 ), SWITCH_ROT );
		pPanelMode->SetMouseRegion( AID_L10_IUS, 0.852753f, 0.124612f, 0.882422f, 0.166456f );
		pPanelMode->SetPullDirection( SWITCH_PULL );

		pPowerSourceASEBatteriesPri->SetInitialAnimState( 0.5f );
		pPowerSourceASEBatteriesPri->DefineGroup( GRP_S3_L10_IUS_VC );
		pPowerSourceASEBatteriesPri->SetReference( _V( -1.4441, 2.3686, 13.1502 ), SWITCH_ROT );
		pPowerSourceASEBatteriesPri->SetMouseRegion( AID_L10_IUS, 0.113853f, 0.180123f, 0.147586f, 0.219617f );
		pPowerSourceASEBatteriesPri->SetSpringLoaded( true, 0 );
		pPowerSourceASEBatteriesPri->SetSpringLoaded( true, 2 );

		pPowerSourceASEBatteriesAlt->SetInitialAnimState( 0.5f );
		pPowerSourceASEBatteriesAlt->DefineGroup( GRP_S33_L10_IUS_VC );
		pPowerSourceASEBatteriesAlt->SetReference( _V( -1.4441, 2.3686, 13.1502 ), SWITCH_ROT );
		pPowerSourceASEBatteriesAlt->SetMouseRegion( AID_L10_IUS, 0.167758f, 0.180064f, 0.205525f, 0.220610f );
		pPowerSourceASEBatteriesAlt->SetSpringLoaded( true, 0 );
		pPowerSourceASEBatteriesAlt->SetSpringLoaded( true, 2 );

		pPowerSourceOrbiterSCConvPwrPri->SetInitialAnimState( 0.5f );
		pPowerSourceOrbiterSCConvPwrPri->DefineGroup( GRP_S4_L10_IUS_VC );
		pPowerSourceOrbiterSCConvPwrPri->SetReference( _V( -1.4441, 2.3686, 13.1502 ), SWITCH_ROT );
		pPowerSourceOrbiterSCConvPwrPri->SetMouseRegion( AID_L10_IUS, 0.237598f, 0.178404f, 0.269871f, 0.218495f );
		pPowerSourceOrbiterSCConvPwrPri->SetSpringLoaded( true, 0 );
		pPowerSourceOrbiterSCConvPwrPri->SetSpringLoaded( true, 2 );

		pPowerSourceOrbiterSCConvPwrAlt->SetInitialAnimState( 0.5f );
		pPowerSourceOrbiterSCConvPwrAlt->DefineGroup( GRP_S34_L10_IUS_VC );
		pPowerSourceOrbiterSCConvPwrAlt->SetReference( _V( -1.4441, 2.3686, 13.1502 ), SWITCH_ROT );
		pPowerSourceOrbiterSCConvPwrAlt->SetMouseRegion( AID_L10_IUS, 0.296558f, 0.179452f, 0.328858f, 0.218466f );
		pPowerSourceOrbiterSCConvPwrAlt->SetSpringLoaded( true, 0 );
		pPowerSourceOrbiterSCConvPwrAlt->SetSpringLoaded( true, 2 );

		pPowerSourceIUSSCBatteryPri->SetInitialAnimState( 0.5f );
		pPowerSourceIUSSCBatteryPri->DefineGroup( GRP_S5_L10_IUS_VC );
		pPowerSourceIUSSCBatteryPri->SetReference( _V( -1.4441, 2.3686, 13.1502 ), SWITCH_ROT );
		pPowerSourceIUSSCBatteryPri->SetMouseRegion( AID_L10_IUS, 0.395487f, 0.180426f, 0.429601f, 0.220517f );
		pPowerSourceIUSSCBatteryPri->SetSpringLoaded( true, 0 );
		pPowerSourceIUSSCBatteryPri->SetSpringLoaded( true, 2 );

		pPowerSourceIUSSCBatteryAlt->SetInitialAnimState( 0.5f );
		pPowerSourceIUSSCBatteryAlt->DefineGroup( GRP_S35_L10_IUS_VC );
		pPowerSourceIUSSCBatteryAlt->SetReference( _V( -1.4441, 2.3686, 13.1502 ), SWITCH_ROT );
		pPowerSourceIUSSCBatteryAlt->SetMouseRegion( AID_L10_IUS, 0.456171f, 0.180185f, 0.489332f, 0.219832f );
		pPowerSourceIUSSCBatteryAlt->SetSpringLoaded( true, 0 );
		pPowerSourceIUSSCBatteryAlt->SetSpringLoaded( true, 2 );

		pPowerSourceIUSBusABatteriesPri->SetInitialAnimState( 0.5f );
		pPowerSourceIUSBusABatteriesPri->DefineGroup( GRP_S9_L10_IUS_VC );
		pPowerSourceIUSBusABatteriesPri->SetReference( _V( -1.4441, 2.3686, 13.1502 ), SWITCH_ROT );
		pPowerSourceIUSBusABatteriesPri->SetMouseRegion( AID_L10_IUS, 0.530112f, 0.179549f, 0.562831f, 0.220697f );
		pPowerSourceIUSBusABatteriesPri->SetSpringLoaded( true, 0 );
		pPowerSourceIUSBusABatteriesPri->SetSpringLoaded( true, 2 );

		pPowerSourceIUSBusABatteriesAlt->SetInitialAnimState( 0.5f );
		pPowerSourceIUSBusABatteriesAlt->DefineGroup( GRP_S39_L10_IUS_VC );
		pPowerSourceIUSBusABatteriesAlt->SetReference( _V( -1.4441, 2.3686, 13.1502 ), SWITCH_ROT );
		pPowerSourceIUSBusABatteriesAlt->SetMouseRegion( AID_L10_IUS, 0.591074f, 0.179826f, 0.623668f, 0.220067f );
		pPowerSourceIUSBusABatteriesAlt->SetSpringLoaded( true, 0 );
		pPowerSourceIUSBusABatteriesAlt->SetSpringLoaded( true, 2 );

		pPowerSourceIUSBusBBatteriesPri->SetInitialAnimState( 0.5f );
		pPowerSourceIUSBusBBatteriesPri->DefineGroup( GRP_S11_L10_IUS_VC );
		pPowerSourceIUSBusBBatteriesPri->SetReference( _V( -1.4441, 2.3686, 13.1502 ), SWITCH_ROT );
		pPowerSourceIUSBusBBatteriesPri->SetMouseRegion( AID_L10_IUS, 0.660245f, 0.179550f, 0.690858f, 0.218969f );
		pPowerSourceIUSBusBBatteriesPri->SetSpringLoaded( true, 0 );
		pPowerSourceIUSBusBBatteriesPri->SetSpringLoaded( true, 2 );

		pPowerSourceIUSBusBBatteriesAlt->SetInitialAnimState( 0.5f );
		pPowerSourceIUSBusBBatteriesAlt->DefineGroup( GRP_S41_L10_IUS_VC );
		pPowerSourceIUSBusBBatteriesAlt->SetReference( _V( -1.4441, 2.3686, 13.1502 ), SWITCH_ROT );
		pPowerSourceIUSBusBBatteriesAlt->SetMouseRegion( AID_L10_IUS, 0.720762f, 0.180016f, 0.753149f, 0.219112f );
		pPowerSourceIUSBusBBatteriesAlt->SetSpringLoaded( true, 0 );
		pPowerSourceIUSBusBBatteriesAlt->SetSpringLoaded( true, 2 );

		pIUSConvPwrPri->SetInitialAnimState( 0.5f );
		pIUSConvPwrPri->DefineGroup( GRP_S1_L10_IUS_VC );
		pIUSConvPwrPri->SetReference( _V( -1.3415, 2.3013, 13.1399 ), SWITCH_ROT );
		pIUSConvPwrPri->SetMouseRegion( AID_L10_IUS, 0.094067f, 0.390423f, 0.126817f, 0.430282f );
		pIUSConvPwrPri->SetSpringLoaded( true, 0 );
		pIUSConvPwrPri->SetSpringLoaded( true, 2 );

		pIUSConvPwrAlt->SetInitialAnimState( 0.5f );
		pIUSConvPwrAlt->DefineGroup( GRP_S31_L10_IUS_VC );
		pIUSConvPwrAlt->SetReference( _V( -1.3415, 2.3013, 13.1399 ), SWITCH_ROT );
		pIUSConvPwrAlt->SetMouseRegion( AID_L10_IUS, 0.155074f, 0.390227f, 0.188251f, 0.431424f );
		pIUSConvPwrAlt->SetSpringLoaded( true, 0 );
		pIUSConvPwrAlt->SetSpringLoaded( true, 2 );

		pSCSupportSCRegPwrPri->SetInitialAnimState( 0.5f );
		pSCSupportSCRegPwrPri->DefineGroup( GRP_S2_L10_IUS_VC );
		pSCSupportSCRegPwrPri->SetReference( _V( -1.3572, 2.3106, 13.2181 ), SWITCH_ROT );
		pSCSupportSCRegPwrPri->SetMouseRegion( AID_L10_IUS, 0.2372062f, 0.359336f, 0.271265f, 0.399214f );
		pSCSupportSCRegPwrPri->SetSpringLoaded( true, 0 );
		pSCSupportSCRegPwrPri->SetSpringLoaded( true, 2 );

		pSCSupportSCRegPwrAlt->SetInitialAnimState( 0.5f );
		pSCSupportSCRegPwrAlt->DefineGroup( GRP_S32_L10_IUS_VC );
		pSCSupportSCRegPwrAlt->SetReference( _V( -1.3572, 2.3106, 13.2181 ), SWITCH_ROT );
		pSCSupportSCRegPwrAlt->SetMouseRegion( AID_L10_IUS, 0.297839f, 0.359164f, 0.330424f, 0.399969f );
		pSCSupportSCRegPwrAlt->SetSpringLoaded( true, 0 );
		pSCSupportSCRegPwrAlt->SetSpringLoaded( true, 2 );

		pSCSupportSCPowerPri->SetInitialAnimState( 0.5f );
		pSCSupportSCPowerPri->DefineGroup( GRP_S6_L10_IUS_VC );
		pSCSupportSCPowerPri->SetReference( _V( -1.3572, 2.3106, 13.2181 ), SWITCH_ROT );
		pSCSupportSCPowerPri->SetMouseRegion( AID_L10_IUS, 0.392651f, 0.359357f, 0.426633f, 0.400193f );
		pSCSupportSCPowerPri->SetSpringLoaded( true, 0 );
		pSCSupportSCPowerPri->SetSpringLoaded( true, 2 );

		pSCSupportSCPowerAlt->SetInitialAnimState( 0.5f );
		pSCSupportSCPowerAlt->DefineGroup( GRP_S36_L10_IUS_VC );
		pSCSupportSCPowerAlt->SetReference( _V( -1.3572, 2.3106, 13.2181 ), SWITCH_ROT );
		pSCSupportSCPowerAlt->SetMouseRegion( AID_L10_IUS, 0.453977f, 0.360261f, 0.486132f, 0.400180f );
		pSCSupportSCPowerAlt->SetSpringLoaded( true, 0 );
		pSCSupportSCPowerAlt->SetSpringLoaded( true, 2 );

		pIUSSupportAFeedPri->SetInitialAnimState( 0.5f );
		pIUSSupportAFeedPri->DefineGroup( GRP_S10_L10_IUS_VC );
		pIUSSupportAFeedPri->SetReference( _V( -1.3415, 2.3013, 13.1399 ), SWITCH_ROT );
		pIUSSupportAFeedPri->SetMouseRegion( AID_L10_IUS, 0.533648f, 0.390069f, 0.567750f, 0.430798f );
		pIUSSupportAFeedPri->SetSpringLoaded( true, 0 );
		pIUSSupportAFeedPri->SetSpringLoaded( true, 2 );

		pIUSSupportAFeedAlt->SetInitialAnimState( 0.5f );
		pIUSSupportAFeedAlt->DefineGroup( GRP_S40_L10_IUS_VC );
		pIUSSupportAFeedAlt->SetReference( _V( -1.3415, 2.3013, 13.1399 ), SWITCH_ROT );
		pIUSSupportAFeedAlt->SetMouseRegion( AID_L10_IUS, 0.596000f, 0.389347f, 0.626979f, 0.430596f );
		pIUSSupportAFeedAlt->SetSpringLoaded( true, 0 );
		pIUSSupportAFeedAlt->SetSpringLoaded( true, 2 );

		pIUSSupportBFeedPri->SetInitialAnimState( 0.5f );
		pIUSSupportBFeedPri->DefineGroup( GRP_S12_L10_IUS_VC );
		pIUSSupportBFeedPri->SetReference( _V( -1.3415, 2.3013, 13.1399 ), SWITCH_ROT );
		pIUSSupportBFeedPri->SetMouseRegion( AID_L10_IUS, 0.660756f, 0.388670f, 0.691974f, 0.430090f );
		pIUSSupportBFeedPri->SetSpringLoaded( true, 0 );
		pIUSSupportBFeedPri->SetSpringLoaded( true, 2 );

		pIUSSupportBFeedAlt->SetInitialAnimState( 0.5f );
		pIUSSupportBFeedAlt->DefineGroup( GRP_S42_L10_IUS_VC );
		pIUSSupportBFeedAlt->SetReference( _V( -1.3415, 2.3013, 13.1399 ), SWITCH_ROT );
		pIUSSupportBFeedAlt->SetMouseRegion( AID_L10_IUS, 0.718953f, 0.390628f, 0.751530f, 0.430818f );
		pIUSSupportBFeedAlt->SetSpringLoaded( true, 0 );
		pIUSSupportBFeedAlt->SetSpringLoaded( true, 2 );

		pTestPri->SetInitialAnimState( 0.5f );
		pTestPri->DefineGroup( GRP_S63_L10_IUS_VC );
		pTestPri->SetReference( _V( -1.3415, 2.3013, 13.1399 ), SWITCH_ROT );
		pTestPri->SetMouseRegion( AID_L10_IUS, 0.822632f, 0.390149f, 0.855152f, 0.430973f );
		pTestPri->SetSpringLoaded( true, 0 );
		pTestPri->SetSpringLoaded( true, 2 );

		pTestAlt->SetInitialAnimState( 0.5f );
		pTestAlt->DefineGroup( GRP_S73_L10_IUS_VC );
		pTestAlt->SetReference( _V( -1.3415, 2.3013, 13.1399 ), SWITCH_ROT );
		pTestAlt->SetMouseRegion( AID_L10_IUS, 0.883398f, 0.390262f, 0.914446f, 0.430280f );
		pTestAlt->SetSpringLoaded( true, 0 );
		pTestAlt->SetSpringLoaded( true, 2 );

		pIUSSupportHeatersBatteryPri->SetInitialAnimState( 0.5f );
		pIUSSupportHeatersBatteryPri->DefineGroup( GRP_S21_L10_IUS_VC );
		pIUSSupportHeatersBatteryPri->SetReference( _V( -1.2541, 2.2442, 13.1401 ), SWITCH_ROT );
		pIUSSupportHeatersBatteryPri->SetMouseRegion( AID_L10_IUS, 0.095766f, 0.568545f, 0.126822f, 0.608904f );
		pIUSSupportHeatersBatteryPri->SetSpringLoaded( true, 0 );
		pIUSSupportHeatersBatteryPri->SetSpringLoaded( true, 2 );

		pIUSSupportHeatersBatteryAlt->SetInitialAnimState( 0.5f );
		pIUSSupportHeatersBatteryAlt->DefineGroup( GRP_S51_L10_IUS_VC );
		pIUSSupportHeatersBatteryAlt->SetReference( _V( -1.2541, 2.2442, 13.1401 ), SWITCH_ROT );
		pIUSSupportHeatersBatteryAlt->SetMouseRegion( AID_L10_IUS, 0.154715f, 0.568617f, 0.185813f, 0.608895f );
		pIUSSupportHeatersBatteryAlt->SetSpringLoaded( true, 0 );
		pIUSSupportHeatersBatteryAlt->SetSpringLoaded( true, 2 );

		pIUSSupportHeatersCriticalPri->SetInitialAnimState( 0.5f );
		pIUSSupportHeatersCriticalPri->DefineGroup( GRP_S22_L10_IUS_VC );
		pIUSSupportHeatersCriticalPri->SetReference( _V( -1.2541, 2.2442, 13.1401 ), SWITCH_ROT );
		pIUSSupportHeatersCriticalPri->SetMouseRegion( AID_L10_IUS, 0.218462f, 0.567740f, 0.250986f, 0.608784f );
		pIUSSupportHeatersCriticalPri->SetSpringLoaded( true, 0 );
		pIUSSupportHeatersCriticalPri->SetSpringLoaded( true, 2 );

		pIUSSupportHeatersCriticalAlt->SetInitialAnimState( 0.5f );
		pIUSSupportHeatersCriticalAlt->DefineGroup( GRP_S52_L10_IUS_VC );
		pIUSSupportHeatersCriticalAlt->SetReference( _V( -1.2541, 2.2442, 13.1401 ), SWITCH_ROT );
		pIUSSupportHeatersCriticalAlt->SetMouseRegion( AID_L10_IUS, 0.278251f, 0.566908f, 0.311681f, 0.607395f );
		pIUSSupportHeatersCriticalAlt->SetSpringLoaded( true, 0 );
		pIUSSupportHeatersCriticalAlt->SetSpringLoaded( true, 2 );

		pIUSSupportWBDIPri->SetInitialAnimState( 0.5f );
		pIUSSupportWBDIPri->DefineGroup( GRP_S23_L10_IUS_VC );
		pIUSSupportWBDIPri->SetReference( _V( -1.2541, 2.2442, 13.1401 ), SWITCH_ROT );
		pIUSSupportWBDIPri->SetMouseRegion( AID_L10_IUS, 0.360761f, 0.568326f, 0.394916f, 0.608589f );
		pIUSSupportWBDIPri->SetSpringLoaded( true, 0 );
		pIUSSupportWBDIPri->SetSpringLoaded( true, 2 );

		pIUSSupportWBDIAlt->SetInitialAnimState( 0.5f );
		pIUSSupportWBDIAlt->DefineGroup( GRP_S53_L10_IUS_VC );
		pIUSSupportWBDIAlt->SetReference( _V( -1.2541, 2.2442, 13.1401 ), SWITCH_ROT );
		pIUSSupportWBDIAlt->SetMouseRegion( AID_L10_IUS, 0.422435f, 0.568450f, 0.455397f, 0.608290f );
		pIUSSupportWBDIAlt->SetSpringLoaded( true, 0 );
		pIUSSupportWBDIAlt->SetSpringLoaded( true, 2 );

		pIUSPowerPri->SetInitialAnimState( 0.5f );
		pIUSPowerPri->DefineGroup( GRP_S8_L10_IUS_VC );
		pIUSPowerPri->SetReference( _V( -1.2541, 2.2442, 13.1401 ), SWITCH_ROT );
		pIUSPowerPri->SetMouseRegion( AID_L10_IUS, 0.541147f, 0.568843f, 0.573920f, 0.609133f );
		pIUSPowerPri->SetSpringLoaded( true, 0 );
		pIUSPowerPri->SetSpringLoaded( true, 2 );

		pIUSPowerAlt->SetInitialAnimState( 0.5f );
		pIUSPowerAlt->DefineGroup( GRP_S38_L10_IUS_VC );
		pIUSPowerAlt->SetReference( _V( -1.2541, 2.2442, 13.1401 ), SWITCH_ROT );
		pIUSPowerAlt->SetMouseRegion( AID_L10_IUS, 0.599976f, 0.568463f, 0.631928f, 0.608484f );
		pIUSPowerAlt->SetSpringLoaded( true, 0 );
		pIUSPowerAlt->SetSpringLoaded( true, 2 );

		pNormBusPwrPri->SetInitialAnimState( 0.5f );
		pNormBusPwrPri->DefineGroup( GRP_S7_L10_IUS_VC );
		pNormBusPwrPri->SetReference( _V( -1.2541, 2.2442, 13.1401 ), SWITCH_ROT );
		pNormBusPwrPri->SetMouseRegion( AID_L10_IUS, 0.683755f, 0.569051f, 0.716306f, 0.609468f );
		pNormBusPwrPri->SetSpringLoaded( true, 0 );
		pNormBusPwrPri->SetSpringLoaded( true, 2 );

		pNormBusPwrAlt->SetInitialAnimState( 0.5f );
		pNormBusPwrAlt->DefineGroup( GRP_S37_L10_IUS_VC );
		pNormBusPwrAlt->SetReference( _V( -1.2541, 2.2442, 13.1401 ), SWITCH_ROT );
		pNormBusPwrAlt->SetMouseRegion( AID_L10_IUS, 0.743800f, 0.569090f, 0.776005f, 0.609276f );
		pNormBusPwrAlt->SetSpringLoaded( true, 0 );
		pNormBusPwrAlt->SetSpringLoaded( true, 2 );

		pIUSSupportAutoShutdownStandbyModePri->SetInitialAnimState( 0.5f );
		pIUSSupportAutoShutdownStandbyModePri->DefineGroup( GRP_S20_L10_IUS_VC );
		pIUSSupportAutoShutdownStandbyModePri->SetReference( _V( -1.2541, 2.2442, 13.1401 ), SWITCH_ROT );
		pIUSSupportAutoShutdownStandbyModePri->SetMouseRegion( AID_L10_IUS, 0.823231f, 0.569670f, 0.854505f, 0.609477f );
		pIUSSupportAutoShutdownStandbyModePri->SetSpringLoaded( true, 0 );
		pIUSSupportAutoShutdownStandbyModePri->SetSpringLoaded( true, 2 );

		pIUSSupportAutoShutdownStandbyModeAlt->SetInitialAnimState( 0.5f );
		pIUSSupportAutoShutdownStandbyModeAlt->DefineGroup( GRP_S50_L10_IUS_VC );
		pIUSSupportAutoShutdownStandbyModeAlt->SetReference( _V( -1.2541, 2.2442, 13.1401 ), SWITCH_ROT );
		pIUSSupportAutoShutdownStandbyModeAlt->SetMouseRegion( AID_L10_IUS, 0.882804f, 0.569229f, 0.914825f, 0.608940f );
		pIUSSupportAutoShutdownStandbyModeAlt->SetSpringLoaded( true, 0 );
		pIUSSupportAutoShutdownStandbyModeAlt->SetSpringLoaded( true, 2 );

		pTiltTableActuatorDriveEnablePri1->SetInitialAnimState( 0.5f );
		pTiltTableActuatorDriveEnablePri1->DefineGroup( GRP_S13_L10_IUS_VC );
		pTiltTableActuatorDriveEnablePri1->SetReference( _V( -1.1797, 2.1957, 13.1493 ), SWITCH_ROT );
		pTiltTableActuatorDriveEnablePri1->SetMouseRegion( AID_L10_IUS, 0.111635f, 0.719421f, 0.141082f, 0.759150f );

		pTiltTableActuatorDriveEnableAlt2->SetInitialAnimState( 0.5f );
		pTiltTableActuatorDriveEnableAlt2->DefineGroup( GRP_S43_L10_IUS_VC );
		pTiltTableActuatorDriveEnableAlt2->SetReference( _V( -1.1797, 2.1957, 13.1493 ), SWITCH_ROT );
		pTiltTableActuatorDriveEnableAlt2->SetMouseRegion( AID_L10_IUS, 0.171649f, 0.719137f, 0.201649f, 0.759119f );

		pTiltTableActuatorMotionPri1->SetInitialAnimState( 0.5f );
		pTiltTableActuatorMotionPri1->DefineGroup( GRP_S14_L10_IUS_VC );
		pTiltTableActuatorMotionPri1->SetReference( _V( -1.1797, 2.1957, 13.1493 ), SWITCH_ROT );
		pTiltTableActuatorMotionPri1->SetMouseRegion( AID_L10_IUS, 0.254209f, 0.719156f, 0.285940f, 0.759275f );
		pTiltTableActuatorMotionPri1->SetSpringLoaded( true, 0 );
		pTiltTableActuatorMotionPri1->SetSpringLoaded( true, 2 );

		pTiltTableActuatorMotionAlt2->SetInitialAnimState( 0.5f );
		pTiltTableActuatorMotionAlt2->DefineGroup( GRP_S44_L10_IUS_VC );
		pTiltTableActuatorMotionAlt2->SetReference( _V( -1.1797, 2.1957, 13.1493 ), SWITCH_ROT );
		pTiltTableActuatorMotionAlt2->SetMouseRegion( AID_L10_IUS, 0.314874f, 0.719508f, 0.347282f, 0.759363f );
		pTiltTableActuatorMotionAlt2->SetSpringLoaded( true, 0 );
		pTiltTableActuatorMotionAlt2->SetSpringLoaded( true, 2 );

		pTiltTableActuatorAltDrAct1->SetInitialAnimState( 0.5f );
		pTiltTableActuatorAltDrAct1->DefineGroup( GRP_S57_L10_IUS_VC );
		pTiltTableActuatorAltDrAct1->SetReference( _V( -1.1782, 2.1988, 13.5538 ), SWITCH_ROT );
		pTiltTableActuatorAltDrAct1->SetMouseRegion( AID_L10_IUS, 0.754145f, 0.717768f, 0.787739f, 0.759606f );
		pTiltTableActuatorAltDrAct1->SetPullDirection( SWITCH_PULL );
		pTiltTableActuatorAltDrAct1->SetSpringLoaded( true, 1 );

		pCmdPathEnabled->SetInitialAnimState( 0.5f );
		pCmdPathEnabled->DefineGroup( GRP_S65_L10_IUS_VC );
		pCmdPathEnabled->SetReference( _V( -1.1782, 2.1988, 13.5538 ), SWITCH_ROT );
		pCmdPathEnabled->SetMouseRegion( AID_L10_IUS, 0.838003f, 0.717705f, 0.870962f, 0.759780f );
		pCmdPathEnabled->SetPullDirection( SWITCH_PULL );

		pPyroBusPri->SetInitialAnimState( 0.5f );
		pPyroBusPri->DefineGroup( GRP_S24_L10_IUS_VC );
		pPyroBusPri->SetReference( _V( -1.0958, 2.1410, 13.1492 ), SWITCH_ROT );
		pPyroBusPri->SetMouseRegion( AID_L10_IUS, 0.111920f, 0.890384f, 0.145745f, 0.930124f );
		pPyroBusPri->SetSpringLoaded( true, 0 );
		pPyroBusPri->SetSpringLoaded( true, 2 );

		pPyroBusAlt->SetInitialAnimState( 0.5f );
		pPyroBusAlt->DefineGroup( GRP_S54_L10_IUS_VC );
		pPyroBusAlt->SetReference( _V( -1.0958, 2.1410, 13.1492 ), SWITCH_ROT );
		pPyroBusAlt->SetMouseRegion( AID_L10_IUS, 0.172300f, 0.889325f, 0.203690f, 0.929150f );
		pPyroBusAlt->SetSpringLoaded( true, 0 );
		pPyroBusAlt->SetSpringLoaded( true, 2 );

		pUmbilicalsEnaPri->SetInitialAnimState( 0.5f );
		pUmbilicalsEnaPri->DefineGroup( GRP_S18_L10_IUS_VC );
		pUmbilicalsEnaPri->SetReference( _V( -1.0958, 2.1410, 13.1492 ), SWITCH_ROT );
		pUmbilicalsEnaPri->SetMouseRegion( AID_L10_IUS, 0.255508f, 0.889941f, 0.287612f, 0.930524f );
		pUmbilicalsEnaPri->SetSpringLoaded( true, 0 );
		pUmbilicalsEnaPri->SetSpringLoaded( true, 2 );

		pUmbilicalsEnaAlt->SetInitialAnimState( 0.5f );
		pUmbilicalsEnaAlt->DefineGroup( GRP_S48_L10_IUS_VC );
		pUmbilicalsEnaAlt->SetReference( _V( -1.0958, 2.1410, 13.1492 ), SWITCH_ROT );
		pUmbilicalsEnaAlt->SetMouseRegion( AID_L10_IUS, 0.316503f, 0.890866f, 0.347555f, 0.930231f );
		pUmbilicalsEnaAlt->SetSpringLoaded( true, 0 );
		pUmbilicalsEnaAlt->SetSpringLoaded( true, 2 );

		pUmbilicalsRelPri->SetInitialAnimState( 0.5f );
		pUmbilicalsRelPri->DefineGroup( GRP_S19_L10_IUS_VC );
		pUmbilicalsRelPri->SetReference( _V( -1.0939, 2.1438, 13.3103 ), SWITCH_ROT );
		pUmbilicalsRelPri->SetMouseRegion( AID_L10_IUS, 0.395237f, 0.887448f, 0.424710f, 0.930452f );
		pUmbilicalsRelPri->SetPullDirection( SWITCH_PULL );
		pUmbilicalsRelPri->SetSpringLoaded( true, 1 );

		pUmbilicalsRelAlt->SetInitialAnimState( 0.5f );
		pUmbilicalsRelAlt->DefineGroup( GRP_S49_L10_IUS_VC );
		pUmbilicalsRelAlt->SetReference( _V( -1.0939, 2.1438, 13.3103 ), SWITCH_ROT );
		pUmbilicalsRelAlt->SetMouseRegion( AID_L10_IUS, 0.449887f, 0.889443f, 0.480940f, 0.931571f );
		pUmbilicalsRelAlt->SetPullDirection( SWITCH_PULL );
		pUmbilicalsRelAlt->SetSpringLoaded( true, 1 );

		pIUSDeploymentEnaPri->SetInitialAnimState( 0.5f );
		pIUSDeploymentEnaPri->DefineGroup( GRP_S25_L10_IUS_VC );
		pIUSDeploymentEnaPri->SetReference( _V( -1.0958, 2.1410, 13.1492 ), SWITCH_ROT );
		pIUSDeploymentEnaPri->SetMouseRegion( AID_L10_IUS, 0.534739f, 0.890996f, 0.565632f, 0.929932f );
		pIUSDeploymentEnaPri->SetSpringLoaded( true, 0 );
		pIUSDeploymentEnaPri->SetSpringLoaded( true, 2 );

		pIUSDeploymentEnaAlt->SetInitialAnimState( 0.5f );
		pIUSDeploymentEnaAlt->DefineGroup( GRP_S55_L10_IUS_VC );
		pIUSDeploymentEnaAlt->SetReference( _V( -1.0958, 2.1410, 13.1492 ), SWITCH_ROT );
		pIUSDeploymentEnaAlt->SetMouseRegion( AID_L10_IUS, 0.591902f, 0.889207f, 0.624428f, 0.928453f );
		pIUSDeploymentEnaAlt->SetSpringLoaded( true, 0 );
		pIUSDeploymentEnaAlt->SetSpringLoaded( true, 2 );

		pIUSDeploymentDpyPri->SetInitialAnimState( 0.5f );
		pIUSDeploymentDpyPri->DefineGroup( GRP_S26_L10_IUS_VC );
		pIUSDeploymentDpyPri->SetReference( _V( -1.0939, 2.1438, 13.3103 ), SWITCH_ROT );
		pIUSDeploymentDpyPri->SetMouseRegion( AID_L10_IUS, 0.666605f, 0.889142f, 0.699841f, 0.929472f );
		pIUSDeploymentDpyPri->SetPullDirection( SWITCH_PULL );
		pIUSDeploymentDpyPri->SetSpringLoaded( true, 1 );

		pIUSDeploymentDpyAlt->SetInitialAnimState( 0.5f );
		pIUSDeploymentDpyAlt->DefineGroup( GRP_S56_L10_IUS_VC );
		pIUSDeploymentDpyAlt->SetReference( _V( -1.0939, 2.1438, 13.3103 ), SWITCH_ROT );
		pIUSDeploymentDpyAlt->SetMouseRegion( AID_L10_IUS, 0.726243f, 0.889508f, 0.758000f, 0.929481f );
		pIUSDeploymentDpyAlt->SetPullDirection( SWITCH_PULL );
		pIUSDeploymentDpyAlt->SetSpringLoaded( true, 1 );

		pPowerKill->SetInitialAnimState( 0.5f );
		pPowerKill->DefineGroup( GRP_S62_L10_IUS_VC );
		pPowerKill->SetReference( _V( -1.1141, 2.1573, 13.5453 ), SWITCH_ROT );
		pPowerKill->SetMouseRegion( AID_L10_IUS, 0.834209f, 0.848043f, 0.869189f, 0.889788f );
		pPowerKill->SetPullDirection( SWITCH_PULL );
		pPowerKill->SetSpringLoaded( true, 1 );

		pPowerSourceASEBatteriesPriTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS13_U_L10_IUS_VC, GRP_DS13_L_L10_IUS_VC );
		pPowerSourceASEBatteriesAltTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS133_U_L10_IUS_VC, GRP_DS133_L_L10_IUS_VC );
		pPowerSourceOrbiterSCConvPwrPriTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS14_U_L10_IUS_VC, GRP_DS14_L_L10_IUS_VC );
		pPowerSourceOrbiterSCConvPwrAltTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS134_U_L10_IUS_VC, GRP_DS134_L_L10_IUS_VC );
		pPowerSourceIUSSCBatteryPriTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS15_U_L10_IUS_VC, GRP_DS15_L_L10_IUS_VC );
		pPowerSourceIUSSCBatteryAltTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS135_U_L10_IUS_VC, GRP_DS135_L_L10_IUS_VC );
		pPowerSourceIUSBusABatteriesPriTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS19_U_L10_IUS_VC, GRP_DS19_L_L10_IUS_VC );
		pPowerSourceIUSBusABatteriesAltTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS139_U_L10_IUS_VC, GRP_DS139_L_L10_IUS_VC );
		pPowerSourceIUSBusBBatteriesPriTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS111_U_L10_IUS_VC, GRP_DS111_L_L10_IUS_VC );
		pPowerSourceIUSBusBBatteriesAltTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS141_U_L10_IUS_VC, GRP_DS141_L_L10_IUS_VC );
		pIUSConvPwrPriTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS11_U_L10_IUS_VC, GRP_DS11_L_L10_IUS_VC );
		pIUSConvPwrAltTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS131_U_L10_IUS_VC, GRP_DS131_L_L10_IUS_VC );
		pSCSupportSCRegPwrPriTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS12_U_L10_IUS_VC, GRP_DS12_L_L10_IUS_VC );
		pSCSupportSCRegPwrAltTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS132_U_L10_IUS_VC, GRP_DS132_L_L10_IUS_VC );
		pSCSupportSCPowerPriTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS16_U_L10_IUS_VC, GRP_DS16_L_L10_IUS_VC );
		pSCSupportSCPowerAltTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS136_U_L10_IUS_VC, GRP_DS136_L_L10_IUS_VC );
		pIUSSupportAFeedPriTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS110_U_L10_IUS_VC, GRP_DS110_L_L10_IUS_VC );
		pIUSSupportAFeedAltTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS140_U_L10_IUS_VC, GRP_DS140_L_L10_IUS_VC );
		pIUSSupportBFeedPriTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS112_U_L10_IUS_VC, GRP_DS112_L_L10_IUS_VC );
		pIUSSupportBFeedAltTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS142_U_L10_IUS_VC, GRP_DS142_L_L10_IUS_VC );
		pMatrixStatusPriTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS180_U_L10_IUS_VC, GRP_DS180_L_L10_IUS_VC );
		pMatrixStatusAltTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS181_U_L10_IUS_VC, GRP_DS181_L_L10_IUS_VC );
		pIUSSupportHeatersBatteryPriTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS121_U_L10_IUS_VC, GRP_DS121_L_L10_IUS_VC );
		pIUSSupportHeatersBatteryAltTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS151_U_L10_IUS_VC, GRP_DS151_L_L10_IUS_VC );
		pIUSSupportHeatersCriticalPriTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS122_U_L10_IUS_VC, GRP_DS122_L_L10_IUS_VC );
		pIUSSupportHeatersCriticalAltTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS152_U_L10_IUS_VC, GRP_DS152_L_L10_IUS_VC );
		pIUSSupportWBDIPriTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS123_U_L10_IUS_VC, GRP_DS123_L_L10_IUS_VC );
		pIUSSupportWBDIAltTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS153_U_L10_IUS_VC, GRP_DS153_L_L10_IUS_VC );
		pIUSPowerPriTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS18_U_L10_IUS_VC, GRP_DS18_L_L10_IUS_VC );
		pIUSPowerAltTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS138_U_L10_IUS_VC, GRP_DS138_L_L10_IUS_VC );
		pNormBusPwrPriTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS17_U_L10_IUS_VC, GRP_DS17_L_L10_IUS_VC );
		pNormBusPwrAltTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS137_U_L10_IUS_VC, GRP_DS137_L_L10_IUS_VC );
		pIUSSupportAutoShutdownStandbyModePriTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS120_U_L10_IUS_VC, GRP_DS120_L_L10_IUS_VC );
		pIUSSupportAutoShutdownStandbyModeAltTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS150_U_L10_IUS_VC, GRP_DS150_L_L10_IUS_VC );
		pTiltTableActuatorMotionPri1TB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS114_U_L10_IUS_VC, GRP_DS114_L_L10_IUS_VC );
		pTiltTableActuatorMotionAlt2TB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS144_U_L10_IUS_VC, GRP_DS144_L_L10_IUS_VC );
		pTiltTableActuatorPositionPri1TB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS161_U_L10_IUS_VC, GRP_DS161_L_L10_IUS_VC );
		pTiltTableActuatorPositionAlt2TB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS171_U_L10_IUS_VC, GRP_DS171_L_L10_IUS_VC );
		pTiltTableActuatorPriDrAct1EngagedTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS176_U_L10_IUS_VC, GRP_DS176_L_L10_IUS_VC );
		pTiltTableActuatorAltDrAct2EngagedTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS177_U_L10_IUS_VC, GRP_DS177_L_L10_IUS_VC );
		pPyroBusPriTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS124_U_L10_IUS_VC, GRP_DS124_L_L10_IUS_VC );
		pPyroBusAltTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS143_U_L10_IUS_VC, GRP_DS143_L_L10_IUS_VC );
		pUmbilicalsEnaPriTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS118_U_L10_IUS_VC, GRP_DS118_L_L10_IUS_VC );
		pUmbilicalsEnaAltTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS148_U_L10_IUS_VC, GRP_DS148_L_L10_IUS_VC );
		pUmbilicalsRelPriTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS119_U_L10_IUS_VC, GRP_DS119_L_L10_IUS_VC );
		pUmbilicalsRelAltTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS149_U_L10_IUS_VC, GRP_DS149_L_L10_IUS_VC );
		pIUSDeploymentEnaPriTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS125_U_L10_IUS_VC, GRP_DS125_L_L10_IUS_VC );
		pIUSDeploymentEnaAltTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS155_U_L10_IUS_VC, GRP_DS155_L_L10_IUS_VC );
		return;
	}

	void PanelL10_IUS::Realize()
	{
		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "L10toASE_A", 16 );
		pPanelMode->ConnectPort( 1, pBundle, 0 );
		pPowerSourceASEBatteriesPri->ConnectPort( 0, pBundle, 1 );
		pPowerSourceASEBatteriesPri->ConnectPort( 2, pBundle, 2 );
		pPowerSourceASEBatteriesPriTB->SetInput( pBundle, 3, TB_GRAY );
		pPowerSourceASEBatteriesAlt->ConnectPort( 0, pBundle, 4 );
		pPowerSourceASEBatteriesAlt->ConnectPort( 2, pBundle, 5 );
		pPowerSourceASEBatteriesAltTB->SetInput( pBundle, 6, TB_GRAY );
		pPowerSourceOrbiterSCConvPwrPri->ConnectPort( 0, pBundle, 7 );
		pPowerSourceOrbiterSCConvPwrPri->ConnectPort( 2, pBundle, 8 );
		pPowerSourceOrbiterSCConvPwrPriTB->SetInput( pBundle, 9, TB_GRAY );
		pPowerSourceOrbiterSCConvPwrAlt->ConnectPort( 0, pBundle, 10 );
		pPowerSourceOrbiterSCConvPwrAlt->ConnectPort( 2, pBundle, 11 );
		pPowerSourceOrbiterSCConvPwrAltTB->SetInput( pBundle, 12, TB_GRAY );
		pPowerSourceIUSSCBatteryPri->ConnectPort( 0, pBundle, 13 );
		pPowerSourceIUSSCBatteryPri->ConnectPort( 2, pBundle, 14 );
		pPowerSourceIUSSCBatteryPriTB->SetInput( pBundle, 15, TB_GRAY );

		pBundle = STS()->BundleManager()->CreateBundle( "L10toASE_B", 16 );
		pPowerSourceIUSSCBatteryAlt->ConnectPort( 0, pBundle, 0 );
		pPowerSourceIUSSCBatteryAlt->ConnectPort( 2, pBundle, 1 );
		pPowerSourceIUSSCBatteryAltTB->SetInput( pBundle, 2, TB_GRAY );
		pPowerSourceIUSBusABatteriesPri->ConnectPort( 0, pBundle, 3 );
		pPowerSourceIUSBusABatteriesPri->ConnectPort( 2, pBundle, 4 );
		pPowerSourceIUSBusABatteriesPriTB->SetInput( pBundle, 5, TB_GRAY );
		pPowerSourceIUSBusABatteriesAlt->ConnectPort( 0, pBundle, 6 );
		pPowerSourceIUSBusABatteriesAlt->ConnectPort( 2, pBundle, 7 );
		pPowerSourceIUSBusABatteriesAltTB->SetInput( pBundle, 8, TB_GRAY );
		pPowerSourceIUSBusBBatteriesPri->ConnectPort( 0, pBundle, 9 );
		pPowerSourceIUSBusBBatteriesPri->ConnectPort( 2, pBundle, 10 );
		pPowerSourceIUSBusBBatteriesPriTB->SetInput( pBundle, 11, TB_GRAY );
		pPowerSourceIUSBusBBatteriesAlt->ConnectPort( 0, pBundle, 12 );
		pPowerSourceIUSBusBBatteriesAlt->ConnectPort( 2, pBundle, 13 );
		pPowerSourceIUSBusBBatteriesAltTB->SetInput( pBundle, 14, TB_GRAY );

		pBundle = STS()->BundleManager()->CreateBundle( "L10toASE_C", 16 );
		pIUSConvPwrPri->ConnectPort( 0, pBundle, 0 );
		pIUSConvPwrPri->ConnectPort( 2, pBundle, 1 );
		pIUSConvPwrPriTB->SetInput( pBundle, 2, TB_GRAY );
		pIUSConvPwrAlt->ConnectPort( 0, pBundle, 3 );
		pIUSConvPwrAlt->ConnectPort( 2, pBundle, 4 );
		pIUSConvPwrAltTB->SetInput( pBundle, 5, TB_GRAY );
		pSCSupportSCRegPwrPri->ConnectPort( 0, pBundle, 6 );
		pSCSupportSCRegPwrPri->ConnectPort( 2, pBundle, 7 );
		pSCSupportSCRegPwrPriTB->SetInput( pBundle, 8, TB_GRAY );
		pSCSupportSCRegPwrAlt->ConnectPort( 0, pBundle, 9 );
		pSCSupportSCRegPwrAlt->ConnectPort( 2, pBundle, 10 );
		pSCSupportSCRegPwrAltTB->SetInput( pBundle, 11, TB_GRAY );
		pSCSupportSCPowerPri->ConnectPort( 0, pBundle, 12 );
		pSCSupportSCPowerPri->ConnectPort( 2, pBundle, 13 );
		pSCSupportSCPowerPriTB->SetInput( pBundle, 14, TB_GRAY );

		pBundle = STS()->BundleManager()->CreateBundle( "L10toASE_D", 16 );
		pSCSupportSCPowerAlt->ConnectPort( 0, pBundle, 0 );
		pSCSupportSCPowerAlt->ConnectPort( 2, pBundle, 1 );
		pSCSupportSCPowerAltTB->SetInput( pBundle, 2, TB_GRAY );
		pIUSSupportAFeedPri->ConnectPort( 0, pBundle, 3 );
		pIUSSupportAFeedPri->ConnectPort( 2, pBundle, 4 );
		pIUSSupportAFeedPriTB->SetInput( pBundle, 5, TB_GRAY );
		pIUSSupportAFeedAlt->ConnectPort( 0, pBundle, 6 );
		pIUSSupportAFeedAlt->ConnectPort( 2, pBundle, 7 );
		pIUSSupportAFeedAltTB->SetInput( pBundle, 8, TB_GRAY );
		pIUSSupportBFeedPri->ConnectPort( 0, pBundle, 9 );
		pIUSSupportBFeedPri->ConnectPort( 2, pBundle, 10 );
		pIUSSupportBFeedPriTB->SetInput( pBundle, 11, TB_GRAY );
		pIUSSupportBFeedAlt->ConnectPort( 0, pBundle, 12 );
		pIUSSupportBFeedAlt->ConnectPort( 2, pBundle, 13 );
		pIUSSupportBFeedAltTB->SetInput( pBundle, 14, TB_GRAY );

		pBundle = STS()->BundleManager()->CreateBundle( "L10toASE_E", 16 );
		pTestPri->ConnectPort( 0, pBundle, 0 );
		pTestPri->ConnectPort( 2, pBundle, 1 );
		pMatrixStatusPriTB->SetInput( pBundle, 2, TB_GRAY );
		pTestAlt->ConnectPort( 0, pBundle, 3 );
		pTestAlt->ConnectPort( 2, pBundle, 4 );
		pMatrixStatusAltTB->SetInput( pBundle, 5, TB_GRAY );
		pIUSSupportHeatersBatteryPri->ConnectPort( 0, pBundle, 6 );
		pIUSSupportHeatersBatteryPri->ConnectPort( 2, pBundle, 7 );
		pIUSSupportHeatersBatteryPriTB->SetInput( pBundle, 8, TB_GRAY );
		pIUSSupportHeatersBatteryAlt->ConnectPort( 0, pBundle, 9 );
		pIUSSupportHeatersBatteryAlt->ConnectPort( 2, pBundle, 10 );
		pIUSSupportHeatersBatteryAltTB->SetInput( pBundle, 11, TB_GRAY );
		pIUSSupportHeatersCriticalPri->ConnectPort( 0, pBundle, 12 );
		pIUSSupportHeatersCriticalPri->ConnectPort( 2, pBundle, 13 );
		pIUSSupportHeatersCriticalPriTB->SetInput( pBundle, 14, TB_GRAY );

		pBundle = STS()->BundleManager()->CreateBundle( "L10toASE_F", 16 );
		pIUSSupportHeatersCriticalAlt->ConnectPort( 0, pBundle, 0 );
		pIUSSupportHeatersCriticalAlt->ConnectPort( 2, pBundle, 1 );
		pIUSSupportHeatersCriticalAltTB->SetInput( pBundle, 2, TB_GRAY );
		pIUSSupportWBDIPri->ConnectPort( 0, pBundle, 3 );
		pIUSSupportWBDIPri->ConnectPort( 2, pBundle, 4 );
		pIUSSupportWBDIPriTB->SetInput( pBundle, 5, TB_GRAY );
		pIUSSupportWBDIAlt->ConnectPort( 0, pBundle, 6 );
		pIUSSupportWBDIAlt->ConnectPort( 2, pBundle, 7 );
		pIUSSupportWBDIAltTB->SetInput( pBundle, 8, TB_GRAY );
		pIUSPowerPri->ConnectPort( 0, pBundle, 9 );
		pIUSPowerPri->ConnectPort( 2, pBundle, 10 );
		pIUSPowerPriTB->SetInput( pBundle, 11, TB_GRAY );
		pIUSPowerAlt->ConnectPort( 0, pBundle, 12 );
		pIUSPowerAlt->ConnectPort( 2, pBundle, 13 );
		pIUSPowerAltTB->SetInput( pBundle, 14, TB_GRAY );

		pBundle = STS()->BundleManager()->CreateBundle( "L10toASE_G", 16 );
		pNormBusPwrPri->ConnectPort( 0, pBundle, 0 );
		pNormBusPwrPri->ConnectPort( 2, pBundle, 1 );
		pNormBusPwrPriTB->SetInput( pBundle, 2, TB_GRAY );
		pNormBusPwrAlt->ConnectPort( 0, pBundle, 3 );
		pNormBusPwrAlt->ConnectPort( 2, pBundle, 4 );
		pNormBusPwrAltTB->SetInput( pBundle, 5, TB_GRAY );
		pIUSSupportAutoShutdownStandbyModePri->ConnectPort( 0, pBundle, 6 );
		pIUSSupportAutoShutdownStandbyModePri->ConnectPort( 2, pBundle, 7 );
		pIUSSupportAutoShutdownStandbyModePriTB->SetInput( pBundle, 8, TB_GRAY );
		pIUSSupportAutoShutdownStandbyModeAlt->ConnectPort( 0, pBundle, 9 );
		pIUSSupportAutoShutdownStandbyModeAlt->ConnectPort( 2, pBundle, 10 );
		pIUSSupportAutoShutdownStandbyModeAltTB->SetInput( pBundle, 11, TB_GRAY );
		pTiltTableActuatorDriveEnablePri1->ConnectPort( 0, pBundle, 12 );
		pTiltTableActuatorDriveEnablePri1->ConnectPort( 2, pBundle, 13 );
		pTiltTableActuatorDriveEnableAlt2->ConnectPort( 0, pBundle, 14 );
		pTiltTableActuatorDriveEnableAlt2->ConnectPort( 2, pBundle, 15 );

		pBundle = STS()->BundleManager()->CreateBundle( "L10toASE_H", 16 );
		pTiltTableActuatorMotionPri1->ConnectPort( 0, pBundle, 0 );
		pTiltTableActuatorMotionPri1->ConnectPort( 2, pBundle, 1 );
		pTiltTableActuatorMotionAlt2->ConnectPort( 0, pBundle, 2 );
		pTiltTableActuatorMotionAlt2->ConnectPort( 2, pBundle, 3 );
		pTiltTableActuatorMotionPri1TB->SetInput( pBundle, 4, TB_GRAY );
		pTiltTableActuatorMotionAlt2TB->SetInput( pBundle, 5, TB_GRAY );
		pTiltTableActuatorPositionPri1TB->SetInput( pBundle, 6, TB_GRAY );
		pTiltTableActuatorPositionAlt2TB->SetInput( pBundle, 7, TB_GRAY );
		pTiltTableActuatorPriDrAct1EngagedTB->SetInput( pBundle, 8, TB_GRAY );
		pTiltTableActuatorAltDrAct2EngagedTB->SetInput( pBundle, 9, TB_GRAY );
		pTiltTableActuatorAltDrAct1->ConnectPort( 1, pBundle, 10 );
		pCmdPathEnabled->ConnectPort( 0, pBundle, 11 );
		pCmdPathEnabled->ConnectPort( 2, pBundle, 12 );
		pPyroBusPri->ConnectPort( 0, pBundle, 13 );
		pPyroBusPri->ConnectPort( 2, pBundle, 14 );
		pPyroBusPriTB->SetInput( pBundle, 15, TB_GRAY );

		pBundle = STS()->BundleManager()->CreateBundle( "L10toASE_I", 16 );
		pPyroBusAlt->ConnectPort( 0, pBundle, 0 );
		pPyroBusAlt->ConnectPort( 2, pBundle, 1 );
		pPyroBusAltTB->SetInput( pBundle, 2, TB_GRAY );
		pUmbilicalsEnaPri->ConnectPort( 0, pBundle, 3 );
		pUmbilicalsEnaPri->ConnectPort( 2, pBundle, 4 );
		pUmbilicalsEnaPriTB->SetInput( pBundle, 5, TB_GRAY );
		pUmbilicalsEnaAlt->ConnectPort( 0, pBundle, 6 );
		pUmbilicalsEnaAlt->ConnectPort( 2, pBundle, 7 );
		pUmbilicalsEnaAltTB->SetInput( pBundle, 8, TB_GRAY );
		pUmbilicalsRelPri->ConnectPort( 1, pBundle, 9 );
		pUmbilicalsRelPriTB->SetInput( pBundle, 10, TB_GRAY );
		pUmbilicalsRelAlt->ConnectPort( 1, pBundle, 11 );
		pUmbilicalsRelAltTB->SetInput( pBundle, 12, TB_GRAY );
		pIUSDeploymentEnaPri->ConnectPort( 0, pBundle, 13 );
		pIUSDeploymentEnaPri->ConnectPort( 2, pBundle, 14 );
		pIUSDeploymentEnaPriTB->SetInput( pBundle, 15, TB_GRAY );

		pBundle = STS()->BundleManager()->CreateBundle( "L10toASE_J", 16 );
		pIUSDeploymentEnaAlt->ConnectPort( 0, pBundle, 0 );
		pIUSDeploymentEnaAlt->ConnectPort( 2, pBundle, 1 );
		pIUSDeploymentEnaAltTB->SetInput( pBundle, 2, TB_GRAY );
		pIUSDeploymentDpyPri->ConnectPort( 0, pBundle, 3 );
		pIUSDeploymentDpyAlt->ConnectPort( 1, pBundle, 4 );
		pPowerKill->ConnectPort( 1, pBundle, 5 );

		AtlantisPanel::Realize();
		return;
	}
};

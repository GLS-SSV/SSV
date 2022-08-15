/******* SSV File Modification Notice *******
Date         Developer
2020/06/14   GLS
2020/06/20   GLS
2021/08/24   GLS
2022/08/05   GLS
********************************************/
#include "CrawlerRightPanel.h"
#include "Crawler.h"
#include "Crawler_defs.h"
#include "CrawlerPBI.h"
#include "CrawlerDigitalDisplay.h"
#include "CrawlerBarGauge.h"
#include "CrawlerPushButton.h"
#include "CrawlerPanelLight.h"
#include "meshres_crawler_vc.h"


namespace vc
{

CrawlerRightPanel::CrawlerRightPanel(Crawler* _v, const std::string& _ident, CRAWLER_CAB _cab)
: CrawlerPanel(_v, _ident, _cab)
{
	Add(pIndependent = new CrawlerPBI(_v, "Independent"));
	Add(pCrab = new CrawlerPBI(_v, "Crab"));
	Add(pGreatCircle = new CrawlerPBI(_v, "GreatCircle"));
	Add(pMode = new CrawlerPBI2(_v, "Mode"));

	Add(pDesSteeringAngleValue = new CrawlerDigitalDisplay(_v, "DesiredSteeringAngleValue"));
	Add(pDesSteeringAngleGauge = new CrawlerBarGauge(_v, "DesiredSteeringAngleGauge", false));
	Add(pLeftSteeringAngleValue = new CrawlerDigitalDisplay(_v, "LeftSteeringAngleValue"));
	Add(pLeftSteeringAngleGauge = new CrawlerBarGauge(_v, "LeftSteeringAngleGauge", false));
	Add(pRightSteeringAngleValue = new CrawlerDigitalDisplay(_v, "RightSteeringAngleValue"));
	Add(pRightSteeringAngleGauge = new CrawlerBarGauge(_v, "RightSteeringAngleGauge", false));

	Add(pAverageHeightValue = new CrawlerDigitalDisplay(_v, "RightSteeringAngleValue"));
	Add(pAverageHeightGauge = new CrawlerBarGauge(_v, "AverageHeightGauge", true));

	Add( pCabAck = new CrawlerPushButton( _v, "Cab Ack" ) );

	Add( pCabSelected = new CrawlerPanelLight( _v, "Cab Selected" ) );
	Add( pMotorChgPermissive = new CrawlerPanelLight( _v, "Motor Chg Permissive" ) );
	Add( pMaxAngleWarning = new CrawlerPanelLight( _v, "Max Angle Warning" ) );
	Add( pCabInControl = new CrawlerPanelLight( _v, "Cab In Control" ) );
}

CrawlerRightPanel::~CrawlerRightPanel()
{
}

void CrawlerRightPanel::RegisterVC()
{
	BasicPanel::RegisterVC();

	VECTOR3 ofs;
	int aid_ofs;
	if(cabID==FWD) {
		ofs = CRAWLER_FWD_VC_OFFSET;
		aid_ofs = 0;
	}
	else {
		ofs = CRAWLER_REAR_VC_OFFSET;
		aid_ofs = AID_REAR_OFFSET;
	}

	oapiVCRegisterArea(AID_RIGHT_MIN+aid_ofs, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
	oapiVCSetAreaClickmode_Quadrilateral(AID_RIGHT_MIN+aid_ofs,
		TransformVector(_V(-0.267, 0.18, -0.194))+ofs,
		TransformVector(_V(-0.420, 0.18, -0.026))+ofs,
		TransformVector(_V(-0.267, -0.040, -0.108))+ofs,
		TransformVector(_V(-0.420, -0.040, 0.073))+ofs);

	SURFHANDLE gauges_tex = oapiGetTextureHandle(V()->GetVCMesh(cabID), 2);
	oapiVCRegisterArea(AID_STEERING_DES_VALUE+aid_ofs, _R(48, 304, 198, 346), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, gauges_tex);
	oapiVCRegisterArea(AID_STEEEING_DES_BAR+aid_ofs, _R(47, 366, 528, 394), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, gauges_tex);
	oapiVCRegisterArea(AID_STEERING_L_VALUE+aid_ofs, _R(50, 488, 200, 530), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, gauges_tex);
	oapiVCRegisterArea(AID_STEERING_L_BAR+aid_ofs, _R(49, 550, 530, 578), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, gauges_tex);
	oapiVCRegisterArea(AID_STEERING_R_VALUE+aid_ofs, _R(50, 870, 200, 912), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, gauges_tex);
	oapiVCRegisterArea(AID_STEERING_R_BAR+aid_ofs, _R(49, 932, 530, 960), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, gauges_tex);
	oapiVCRegisterArea(AID_AVG_HEIGHT_VALUE+aid_ofs, _R(767, 822, 917, 864), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, gauges_tex);
	oapiVCRegisterArea(AID_AVG_HEIGHT_BAR+aid_ofs, _R(827, 351, 859, 805), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, gauges_tex);

	oapiWriteLog("CrawlerRightPanel::RegisterVC() called");
}

void CrawlerRightPanel::DefineVC()
{
	VECTOR3 push_dir = _V( -0.7784, -0.4384, -0.44935 );
	if (cabID == FWD) push_dir = _V( 0.7784, -0.4384, 0.44935 );

	int aid_ofs;
	if (cabID == FWD) aid_ofs = 0;
	else aid_ofs = AID_REAR_OFFSET;

	AddAIDToMouseEventList(AID_RIGHT_MIN+aid_ofs);

	pGreatCircle->SetStateOffset( 1, 0.0f, 0.082031f );// go
	pGreatCircle->SetDirection( push_dir );
	pGreatCircle->DefineMeshGroup( V()->GetVCMeshIdx( cabID ), GRP_GCIRC_MODE_PBI_VC );
	pGreatCircle->SetMouseRegion( AID_RIGHT_MIN + aid_ofs, 0.313290f, 0.794157f, 0.348793f, 0.895431f );

	pCrab->SetStateOffset( 1, 0.0f, 0.082031f );// go
	pCrab->SetDirection( push_dir );
	pCrab->DefineMeshGroup( V()->GetVCMeshIdx( cabID ), GRP_CRAB_MODE_PBI_VC );
	pCrab->SetMouseRegion( AID_RIGHT_MIN + aid_ofs, 0.413186f, 0.809932f, 0.451601f, 0.912886f );

	pIndependent->SetStateOffset( 1, 0.0f, 0.082031f );// go
	pIndependent->SetDirection( push_dir );
	pIndependent->DefineMeshGroup( V()->GetVCMeshIdx( cabID ), GRP_INDEP_MODE_PBI_VC );
	pIndependent->SetMouseRegion( AID_RIGHT_MIN + aid_ofs, 0.516589f, 0.824793f, 0.556619f, 0.929386f );

	pMode->SetStateOffset( 1, 0.0f, 0.082031f );// 2deg
	pMode->SetStateOffset( 2, 0.082031f, 0.082031f );// 6deg
	pMode->SetStateOffset( 3, 0.164063f, 0.082031f );// 2deg/6deg
	pMode->SetDirection( push_dir );
	pMode->DefineMeshGroup( V()->GetVCMeshIdx( cabID ), GRP_MODE_PBI_VC );
	pMode->SetMouseRegion( AID_RIGHT_MIN + aid_ofs, 0.0, 0.0, 0.067998f, 0.201554f );

	pDesSteeringAngleValue->AddAIDToRedrawEventList(AID_STEERING_DES_VALUE+aid_ofs);
	DefineSteeringAngleDisplay(pDesSteeringAngleValue);

	pDesSteeringAngleGauge->AddAIDToRedrawEventList(AID_STEEEING_DES_BAR+aid_ofs);
	DefineSteeringAngleGauge(pDesSteeringAngleGauge);

	pLeftSteeringAngleValue->AddAIDToRedrawEventList(AID_STEERING_L_VALUE+aid_ofs);
	DefineSteeringAngleDisplay(pLeftSteeringAngleValue);

	pLeftSteeringAngleGauge->AddAIDToRedrawEventList(AID_STEERING_L_BAR+aid_ofs);
	DefineSteeringAngleGauge(pLeftSteeringAngleGauge);

	pRightSteeringAngleValue->AddAIDToRedrawEventList(AID_STEERING_R_VALUE+aid_ofs);
	DefineSteeringAngleDisplay(pRightSteeringAngleValue);
	pRightSteeringAngleGauge->AddAIDToRedrawEventList(AID_STEERING_R_BAR+aid_ofs);
	DefineSteeringAngleGauge(pRightSteeringAngleGauge);

	pAverageHeightGauge->SetScaleValue(6.0);
	pAverageHeightGauge->SetRange(0.0, 6.0);
	pAverageHeightGauge->SetBaseCoords(0, 0);
	pAverageHeightGauge->SetDimensions(32, 454, 37);
	pAverageHeightGauge->AddAIDToRedrawEventList(AID_AVG_HEIGHT_BAR+aid_ofs);

	pAverageHeightValue->SetScaleValue(6.0);
	pAverageHeightValue->SetBaseCoords(0, 0);
	pAverageHeightValue->SetDimensions(150, 42, 5);
	pAverageHeightValue->AddAIDToRedrawEventList(AID_AVG_HEIGHT_VALUE+aid_ofs);

	pCabAck->SetDirection( push_dir );
	pCabAck->DefineGroup( GRP_CAB_ACK_PBI_VC );
	pCabAck->SetMouseRegion( AID_RIGHT_MIN + aid_ofs, 0.961500f, 0.895574f, 1.000000f, 1.000000f );

	pCabSelected->SetStateOffset( 1, -0.560547f, 0.153320f );
	pCabSelected->DefineMeshGroup( V()->GetVCMeshIdx( cabID ), GRP_CAB_SELECTED_INDICATOR_VC );

	pMotorChgPermissive->SetStateOffset( 1, -0.560547f, 0.153320f );
	pMotorChgPermissive->DefineMeshGroup( V()->GetVCMeshIdx( cabID ), GRP_MOTOR_CHKS_INDICATOR_VC );

	pMaxAngleWarning->SetStateOffset( 1, -0.560547f, 0.153320f );
	pMaxAngleWarning->DefineMeshGroup( V()->GetVCMeshIdx( cabID ), GRP_MAX_ANGLE_WARNING_INDICATOR02_VC );

	pCabInControl->SetStateOffset( 1, -0.560547f, 0.153320f );
	pCabInControl->DefineMeshGroup( V()->GetVCMeshIdx( cabID ), GRP_CAB_IN_CONTROL_INDICATOR_VC );
	return;
}

void CrawlerRightPanel::DefineSteeringAngleGauge(CrawlerBarGauge* pGauge) const
{
	pGauge->SetScaleValue( static_cast<float>(MAX_TURN_ANGLE) );
	pGauge->SetRange(-7.0, 7.0);
	pGauge->SetBaseCoords(0, 0);
	pGauge->SetDimensions(481, 28, 37);
}

void CrawlerRightPanel::DefineSteeringAngleDisplay(CrawlerDigitalDisplay* pDisplay) const
{
	pDisplay->SetScaleValue( static_cast<float>(MAX_TURN_ANGLE) );
	pDisplay->SetBaseCoords(0, 0);
	pDisplay->SetDimensions(150, 42, 5);
}

void CrawlerRightPanel::Realize()
{
	DiscreteBundle* pBundleLampTest = V()->BundleManager()->CreateBundle( "CRAWLER_LAMPTEST", 16 );
	pGreatCircle->ConnectLight( 1, pBundleLampTest, cabID );
	pCrab->ConnectLight( 1, pBundleLampTest, cabID );
	pIndependent->ConnectLight( 1, pBundleLampTest, cabID );
	pMode->ConnectLight( 1, pBundleLampTest, cabID );
	pMode->ConnectLight( 3, pBundleLampTest, cabID );
	pCabSelected->ConnectLight( 1, pBundleLampTest, cabID );
	pMotorChgPermissive->ConnectLight( 1, pBundleLampTest, cabID );
	pMaxAngleWarning->ConnectLight( 1, pBundleLampTest, cabID );
	pCabInControl->ConnectLight( 1, pBundleLampTest, cabID );

	DiscreteBundle* pBundle;
	if (cabID == FWD) pBundle = V()->BundleManager()->CreateBundle( "CRAWLER_STEERING_FWD", 16 );
	else pBundle = V()->BundleManager()->CreateBundle( "CRAWLER_STEERING_AFT", 16 );
	pDesSteeringAngleValue->ConnectPort( pBundle, 0 );
	pDesSteeringAngleGauge->ConnectPort( pBundle, 0 );
	pLeftSteeringAngleValue->ConnectPort( pBundle, 1 );
	pLeftSteeringAngleGauge->ConnectPort( pBundle, 1 );
	pRightSteeringAngleValue->ConnectPort( pBundle, 2 );
	pRightSteeringAngleGauge->ConnectPort( pBundle, 2 );

	pGreatCircle->ConnectPushButton( pBundle, 3 );
	pCrab->ConnectPushButton( pBundle, 4 );
	pIndependent->ConnectPushButton( pBundle, 5 );
	pMode->ConnectPushButton( pBundle, 6 );

	pGreatCircle->ConnectLight( 0, pBundle, 7 );
	pCrab->ConnectLight( 0, pBundle, 8 );
	pIndependent->ConnectLight( 0, pBundle, 9 );
	pMode->ConnectLight( 0, pBundle, 10 );
	pMode->ConnectLight( 2, pBundle, 11 );

	pBundle = V()->BundleManager()->CreateBundle("CRAWLER_JEL", 1);
	pAverageHeightGauge->ConnectPort(pBundle, 0);
	pAverageHeightValue->ConnectPort(pBundle, 0);

	if (cabID == FWD) pBundle = V()->BundleManager()->CreateBundle( "CRAWLER_CONTROL_FWD", 16 );
	else pBundle = V()->BundleManager()->CreateBundle( "CRAWLER_CONTROL_AFT", 16 );
	pCabAck->output.Connect( pBundle, 0 );
	pCabSelected->ConnectLight( 0, pBundle, 1 );
	pCabInControl->ConnectLight( 0, pBundle, 2 );

	CrawlerPanel::Realize();
	return;
}

};
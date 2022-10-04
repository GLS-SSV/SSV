/******* SSV File Modification Notice *******
Date         Developer
2020/06/14   GLS
2020/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "CrawlerLeftPanel.h"
#include "Crawler.h"
#include "Crawler_defs.h"
#include "CrawlerPBI.h"
#include "CrawlerPushButton.h"
#include "CrawlerPanelLight.h"
#include "CrawlerDigitalDisplay.h"
#include "meshres_crawler_vc.h"


namespace vc
{

CrawlerLeftPanel::CrawlerLeftPanel(Crawler *_v, const std::string &_ident, vc::CRAWLER_CAB _cab)
: CrawlerPanel(_v, _ident, _cab), pSpeedKnobAnimation(NULL)
{
	Add(pParkingBrakePBI = new CrawlerPBI2(_v, "BRAKE"));
	Add(pFwdPBI = new CrawlerPBI(_v, "FWD"));
	Add(pRevPBI = new CrawlerPBI(_v, "REV"));
	Add(pNeutPBI = new CrawlerPBI(_v, "NEUT"));
	Add(pParkingBrakeLight = new CrawlerPanelLight(_v, "BrakeLight"));
	Add( pExciterOn = new CrawlerPanelLight( _v, "Exciter On" ) );
	Add( pMotorFieldLoss = new CrawlerPanelLight( _v, "Motor Field Loss" ) );
	Add( pGroundFault = new CrawlerPanelLight( _v, "Ground Fault" ) );
	Add(pCommandVoltage = new CrawlerDigitalDisplay(_v, "CommandVoltage"));
	Add( pLampTest = new CrawlerPushButton( _v, "LampTest" ) );
}

CrawlerLeftPanel::~CrawlerLeftPanel()
{
	delete pSpeedKnobAnimation;
}

void CrawlerLeftPanel::RegisterVC()
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

	oapiVCRegisterArea(AID_LEFT_MIN+aid_ofs, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
	oapiVCSetAreaClickmode_Quadrilateral(AID_LEFT_MIN+aid_ofs,
		TransformVector(_V(0.566, 0.187, 0.214))+ofs,
		TransformVector(_V(0.310, 0.187, -0.236))+ofs,
		TransformVector(_V(0.525, 0.105, 0.220))+ofs,
		TransformVector(_V(0.275, 0.075, -0.214))+ofs);

	SURFHANDLE gauges_tex = oapiGetTextureHandle(V()->GetVCMesh(cabID), 2);
	oapiVCRegisterArea(AID_COMMAND_VOLTAGE+aid_ofs, _R(199, 139, 331, 169), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, gauges_tex);
}

void CrawlerLeftPanel::DefineVC()
{
	VECTOR3 push_dir = _V( 0.7784, -0.4384, -0.44935 );
	if (cabID == FWD) push_dir = _V( -0.7784, -0.4384, 0.44935 );

	int aid_ofs;
	if (cabID == FWD) aid_ofs = 0;
	else aid_ofs = AID_REAR_OFFSET;

	AddAIDToMouseEventList(AID_LEFT_MIN+aid_ofs);

	pParkingBrakePBI->SetStateOffset( 1, 0.0f, 0.082031f );// on
	pParkingBrakePBI->SetStateOffset( 2, 0.082031f, 0.0f );// off
	pParkingBrakePBI->SetStateOffset( 3, 0.082031f, 0.082031f );// on/off
	pParkingBrakePBI->SetDirection( push_dir );
	pParkingBrakePBI->DefineMeshGroup( V()->GetVCMeshIdx( cabID ), GRP_BRAKES_PBI_VC );
	pParkingBrakePBI->SetMouseRegion( AID_LEFT_MIN + aid_ofs, 0.928669f, 0.561843f, 0.957623f, 0.761592f );

	pFwdPBI->SetStateOffset( 1, 0.0f, 0.082031f );// go
	pFwdPBI->SetDirection( push_dir );
	pFwdPBI->DefineMeshGroup( V()->GetVCMeshIdx( cabID ), GRP_FWD_PBI_VC );
	pFwdPBI->SetMouseRegion( AID_LEFT_MIN + aid_ofs, 0.157694f, 0.125969f, 0.188828f, 0.336145f );

	pRevPBI->SetStateOffset( 1, 0.0f, 0.082031f );// go
	pRevPBI->SetDirection( push_dir );
	pRevPBI->DefineMeshGroup( V()->GetVCMeshIdx( cabID ), GRP_REV_PBI_VC );
	pRevPBI->SetMouseRegion( AID_LEFT_MIN + aid_ofs, 0.257694f, 0.129591f, 0.288609f, 0.337227f );

	pNeutPBI->SetStateOffset( 1, 0.0f, 0.082031f );// go
	pNeutPBI->SetDirection( push_dir );
	pNeutPBI->DefineMeshGroup( V()->GetVCMeshIdx( cabID ), GRP_NEUT_PBI_VC );
	pNeutPBI->SetMouseRegion( AID_LEFT_MIN + aid_ofs, 0.208361f, 0.128575f, 0.240231f, 0.335481f );

	pParkingBrakeLight->SetStateOffset( 1, -0.560547f, 0.153320f );
	pParkingBrakeLight->DefineMeshGroup( V()->GetVCMeshIdx( cabID ), GRP_BRAKES_ON_INDICATOR_VC );

	pExciterOn->SetStateOffset( 1, -0.560547f, 0.153320f );
	pExciterOn->DefineMeshGroup( V()->GetVCMeshIdx( cabID ), GRP_EXCITER_ON_INDICATOR_VC );

	pMotorFieldLoss->SetStateOffset( 1, -0.560547f, 0.153320f );
	pMotorFieldLoss->DefineMeshGroup( V()->GetVCMeshIdx( cabID ), GRP_MOTOR_FIELD_LOSS_INDICATOR_VC );

	pGroundFault->SetStateOffset( 1, -0.560547f, 0.153320f );
	pGroundFault->DefineMeshGroup( V()->GetVCMeshIdx( cabID ), GRP_GROUND_FAULT_INDICATOR_VC );

	pCommandVoltage->SetScaleValue(100.0f);
	pCommandVoltage->SetBaseCoords(0, 0);
	pCommandVoltage->SetDimensions(132, 30, 5);
	pCommandVoltage->AddAIDToRedrawEventList(AID_COMMAND_VOLTAGE+aid_ofs);

	pLampTest->SetDirection( push_dir );
	pLampTest->DefineGroup( GRP_LAMP_TEST_PBI_VC );
	pLampTest->SetMouseRegion( AID_LEFT_MIN + aid_ofs, 0.783505f, 0.137807f, 0.813234f, 0.346944f );
	return;
}

void CrawlerLeftPanel::DefineVCAnimations(UINT vcidx)
{
	static UINT SpeedControlKnob[1] = {GRP_SPEED_CONTROL_KNOB_VC};
	pSpeedKnobAnimation = new MGROUP_ROTATE(vcidx, SpeedControlKnob, 1, TransformVector(_V( 0.3884, 0.090291, 0.073452 )),
		TransformVector(_V( -0.7784, 0.4384, 0.44935 )), static_cast<float>((270.0*RAD)));
	anim_SpeedKnob = V()->CreateAnimation(0.0);
	V()->AddAnimationComponent(anim_SpeedKnob, 0.0, 1.0, pSpeedKnobAnimation);

	CrawlerPanel::DefineVCAnimations( vcidx );
	return;
}
void CrawlerLeftPanel::Realize()
{
	DiscreteBundle* pBundleLampTest = V()->BundleManager()->CreateBundle( "CRAWLER_LAMPTEST", 16 );
	pLampTest->output.Connect( pBundleLampTest, cabID );
	pParkingBrakePBI->ConnectLight( 1, pBundleLampTest, cabID );
	pParkingBrakePBI->ConnectLight( 3, pBundleLampTest, cabID );
	pParkingBrakeLight->ConnectLight( 1, pBundleLampTest, cabID );
	pNeutPBI->ConnectLight( 1, pBundleLampTest, cabID );
	pFwdPBI->ConnectLight( 1, pBundleLampTest, cabID );
	pRevPBI->ConnectLight( 1, pBundleLampTest, cabID );
	pExciterOn->ConnectLight( 1, pBundleLampTest, cabID );
	pMotorFieldLoss->ConnectLight( 1, pBundleLampTest, cabID );
	pGroundFault->ConnectLight( 1, pBundleLampTest, cabID );

	DiscreteBundle* pBundle;
	if (cabID == FWD) pBundle = V()->BundleManager()->CreateBundle( "CRAWLER_BRAKE_FWD", 16 );
	else pBundle = V()->BundleManager()->CreateBundle( "CRAWLER_BRAKE_AFT", 16 );
	pParkingBrakePBI->ConnectPushButton( pBundle, 0 );
	pParkingBrakePBI->ConnectLight( 0, pBundle, 2 );// off
	pParkingBrakePBI->ConnectLight( 2, pBundle, 1 );// on
	pParkingBrakeLight->ConnectLight( 0, pBundle, 1 );

	if (cabID == FWD) pBundle = V()->BundleManager()->CreateBundle( "CRAWLER_ENGINE_FWD", 16 );
	else pBundle = V()->BundleManager()->CreateBundle( "CRAWLER_ENGINE_AFT", 16 );
	pCommandVoltage->ConnectPort( pBundle, 0 );
	pNeutPBI->ConnectPushButton( pBundle, 1 );
	pFwdPBI->ConnectPushButton( pBundle, 2 );
	pRevPBI->ConnectPushButton( pBundle, 3 );
	pNeutPBI->ConnectLight( 0, pBundle, 4 );
	pFwdPBI->ConnectLight( 0, pBundle, 5 );
	pRevPBI->ConnectLight( 0, pBundle, 6 );

	if (cabID == FWD) pBundle = V()->BundleManager()->CreateBundle( "CRAWLER_SPEED_FWD", 16 );
	else pBundle = V()->BundleManager()->CreateBundle( "CRAWLER_SPEED_AFT", 16 );
	port_TargetSpeed.Connect(pBundle, 1);

	CrawlerPanel::Realize();
	return;
}

void CrawlerLeftPanel::OnPreStep(double simt, double simdt, double mjd)
{
	CrawlerPanel::OnPreStep(simt, simdt, mjd);

	double speedKnob = port_TargetSpeed.GetVoltage()/MAX_UNLOADED_SPEED;
	V()->SetAnimation(anim_SpeedKnob, speedKnob);
}
}

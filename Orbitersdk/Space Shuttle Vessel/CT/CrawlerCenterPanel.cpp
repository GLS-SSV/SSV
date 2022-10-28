/******* SSV File Modification Notice *******
Date         Developer
2020/06/14   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "CrawlerCenterPanel.h"
#include "Crawler.h"
#include "Crawler_defs.h"
#include "CrawlerDigitalDisplay.h"
#include "CrawlerBarGauge.h"
#include <EngConst.h>
#include "meshres_crawler_vc.h"
#include <MathSSV.h>


namespace vc
{

CrawlerCenterPanel::CrawlerCenterPanel(Crawler* _v, const std::string& _ident, CRAWLER_CAB _cab)
: CrawlerPanel(_v, _ident, _cab)
{
	Add(pSpeedGauge = new CrawlerBarGauge(_v, "SpeedGauge", false));
	Add(pSpeedDisplay = new CrawlerDigitalDisplay(_v, "SpeedDisplay"));
}

CrawlerCenterPanel::~CrawlerCenterPanel()
{
	for(vector<MGROUP_TRANSFORM*>::const_iterator i=vpAnimations.begin(); i!=vpAnimations.end();++i)
		delete (*i);
}

void CrawlerCenterPanel::RegisterVC()
{
	CrawlerPanel::RegisterVC();

	int aid_ofs;
	if(cabID==FWD) aid_ofs = 0;
	else  aid_ofs = AID_REAR_OFFSET;

	SURFHANDLE gauges_tex = oapiGetTextureHandle(V()->GetVCMesh(cabID), 2);
	oapiVCRegisterArea(AID_SPEED_BAR+aid_ofs, _R(50, 769, 532, 797), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, gauges_tex);
	oapiVCRegisterArea(AID_SPEED_VALUE+aid_ofs, _R(52, 707, 200, 749), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, gauges_tex);
}

void CrawlerCenterPanel::DefineVC()
{
	int aid_ofs;
	if(cabID==FWD) aid_ofs = 0;
	else  aid_ofs = AID_REAR_OFFSET;

	pSpeedGauge->AddAIDToRedrawEventList(AID_SPEED_BAR+aid_ofs);
	pSpeedGauge->SetRange(-2.0, 2.0);
	pSpeedGauge->SetBaseCoords(0, 0);
	pSpeedGauge->SetDimensions(482, 28, 37);
	pSpeedGauge->SetScaleValue(static_cast<float>(MPS2MPH));

	pSpeedDisplay->AddAIDToRedrawEventList(AID_SPEED_VALUE+aid_ofs);
	pSpeedDisplay->SetBaseCoords(0, 0);
	pSpeedDisplay->SetDimensions(148, 42, 4);
	pSpeedDisplay->SetScaleValue(static_cast<float>(MPS2MPH));
}

void CrawlerCenterPanel::DefineVCAnimations(UINT vcidx)
{
	static UINT SteeringWheel[2] = {GRP_STEERING_WHEEL_VC, GRP_STEERING_WHEEL_DEGREES_VC};
	MGROUP_ROTATE *pSteeringWheel = new MGROUP_ROTATE(vcidx, SteeringWheel, 2, TransformVector(_V(0.0, 0.099, -0.164)),
		TransformVector(_V(0, 0.50104, 0.86543)), static_cast<float>(180.0*RAD) );
	anim_steering = V()->CreateAnimation(0.5);
	V()->AddAnimationComponent(anim_steering, 0.0, 1.0, pSteeringWheel);
	vpAnimations.push_back(pSteeringWheel);

	CrawlerPanel::DefineVCAnimations( vcidx );
	return;
}

void CrawlerCenterPanel::Realize()
{
	// connect disc ports
	DiscreteBundle* pBundle;
	if (cabID == FWD) pBundle = V()->BundleManager()->CreateBundle( "CRAWLER_STEERING_FWD", 16 );
	else pBundle = V()->BundleManager()->CreateBundle( "CRAWLER_STEERING_AFT", 16 );
	steeringwheel.Connect( pBundle, 15 );

	if (cabID == FWD) pBundle = V()->BundleManager()->CreateBundle( "CRAWLER_SPEED_FWD", 16 );
	else pBundle = V()->BundleManager()->CreateBundle( "CRAWLER_SPEED_AFT", 16 );
	pSpeedGauge->ConnectPort(pBundle, 0);
	pSpeedDisplay->ConnectPort(pBundle, 0);

	CrawlerPanel::Realize();
}

void CrawlerCenterPanel::OnPreStep(double simt, double simdt, double mjd)
{
	CrawlerPanel::OnPreStep(simt, simdt, mjd);

	// get steering input [-1.0; +1.0] and set steering wheel position
	// in real life, steering wheel angle should determine steering command; here it's the other way around
	double steeringAnim = range( 0.0, (steeringwheel.GetVoltage() * 0.5) + 0.5, 1.0 );
	V()->SetAnimation(anim_steering, steeringAnim);
}

}

/****************************************************************************
  This file is part of Space Shuttle Vessel

  CrawlerCenterPanel definition


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
2020/03/29   GLS
2020/04/01   GLS
2020/05/10   GLS
2020/06/14   GLS
2020/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/12/25   GLS
2022/09/29   GLS
********************************************/

#ifndef _CRAWLERCENTERPANEL_H_
#define _CRAWLERCENTERPANEL_H_


#include <Orbitersdk.h>
#include <vector>
#include "Crawler_vc_defs.h"
#include <DiscInPort.h>
#include <DiscreteBundle.h>


namespace vc
{
	
	class CrawlerDigitalDisplay;
	class CrawlerBarGauge;


	using discsignals::DiscInPort;

class CrawlerCenterPanel : public CrawlerPanel
{
public:
	CrawlerCenterPanel(Crawler* _v, const std::string& _ident, CRAWLER_CAB _cab);
	~CrawlerCenterPanel();

	void DefineVCAnimations (UINT vcidx) override;
	void RegisterVC() override;
	void DefineVC() override;

	void OnPreStep(double simt, double simdt, double mjd) override;
	void Realize() override;
private:
	vector<MGROUP_TRANSFORM*> vpAnimations;

	CrawlerBarGauge* pSpeedGauge;
	CrawlerDigitalDisplay* pSpeedDisplay;

	UINT anim_steering;

	DiscInPort steeringwheel;
};

}

#endif// _CRAWLERCENTERPANEL_H_

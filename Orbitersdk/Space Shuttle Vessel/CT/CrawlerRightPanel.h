/****************************************************************************
  This file is part of Space Shuttle Vessel

  CrawlerRightPanel definition


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
2020/05/10   GLS
2020/06/14   GLS
2020/06/20   GLS
2021/08/24   GLS
2021/12/25   GLS
********************************************/

#ifndef CRAWLERRIGHTPANEL_H_B50D0092_63B0_46ed_9BAC_9C3CFC05C2D5
#define CRAWLERRIGHTPANEL_H_B50D0092_63B0_46ed_9BAC_9C3CFC05C2D5
#pragma once


#include "Crawler_vc_defs.h"


namespace vc
{
	class CrawlerPBI;
	class CrawlerPBI2;
	class CrawlerDigitalDisplay;
	class CrawlerBarGauge;
	class CrawlerPushButton;
	class CrawlerPanelLight;


class CrawlerRightPanel : public CrawlerPanel
{
	CrawlerPBI* pGreatCircle;
	CrawlerPBI* pIndependent;
	CrawlerPBI* pCrab;
	CrawlerPBI2* pMode;

	CrawlerDigitalDisplay* pLeftSteeringAngleValue; // shows angle for this cab
	CrawlerDigitalDisplay* pRightSteeringAngleValue; // shows angle for other cab
	CrawlerDigitalDisplay* pDesSteeringAngleValue;

	CrawlerBarGauge* pLeftSteeringAngleGauge; // shows angle for this cab
	CrawlerBarGauge* pRightSteeringAngleGauge; // shows angle for other cab
	CrawlerBarGauge* pDesSteeringAngleGauge;

	CrawlerDigitalDisplay* pAverageHeightValue;
	CrawlerBarGauge* pAverageHeightGauge;

	CrawlerPushButton* pCabAck;

	CrawlerPanelLight* pCabSelected;
	CrawlerPanelLight* pMotorChgPermissive;
	CrawlerPanelLight* pMaxAngleWarning;
	CrawlerPanelLight* pCabInControl;

	void DefineSteeringAngleGauge(CrawlerBarGauge* pGauge) const;
	void DefineSteeringAngleDisplay(CrawlerDigitalDisplay* pDisplay) const;
public:
	CrawlerRightPanel(Crawler* _v, const std::string& _ident, CRAWLER_CAB _cab);
	virtual ~CrawlerRightPanel();

	void RegisterVC() override;
	void DefineVC() override;
	void Realize() override;
};

};

#endif
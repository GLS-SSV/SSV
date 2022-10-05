/****************************************************************************
  This file is part of Space Shuttle Vessel

  CrawlerDigitalDisplay definition


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
2020/04/01   GLS
2020/05/10   GLS
2020/06/14   GLS
2020/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/12/25   GLS
2022/09/29   GLS
********************************************/

#ifndef _CRAWLERDIGITALDISPLAY_H_
#define _CRAWLERDIGITALDISPLAY_H_


#include "Crawler_vc_defs.h"
#include <BasicVCComponent.h>
#include <discsignals.h>

namespace vc
{
	using discsignals::DiscInPort;
	using discsignals::DiscreteBundle;

/**
 * Class for displaying digital value (e.g. Steering angle)
 * Uses IDB_7SEGDIGITS resource for digit bitmaps
 */
class CrawlerDigitalDisplay : public BasicVCComponent<Crawler>
{
	DiscInPort input;
	float fOldValue;
	float fScale;

	POINT redrawBase;
	unsigned short usWidth;
	unsigned short usHeight;
	unsigned short usDigitCount;
	unsigned short usDigitWidth;
public:
	CrawlerDigitalDisplay(Crawler* _v, const std::string& _ident);
	virtual ~CrawlerDigitalDisplay();

	void OnPreStep(double simt, double simdt, double mjd) override;
	bool OnVCRedrawEvent(int id, int _event, SURFHANDLE surf) override;

	void ConnectPort(DiscreteBundle* pBundle, unsigned short usLine);

	void SetScaleValue(float _fScale);
	void SetDimensions(unsigned short _usWidth, unsigned short _usHeight, unsigned short _usDigitCount);
	void SetBaseCoords(unsigned short usX, unsigned short usY);
};

}

#endif// _CRAWLERDIGITALDISPLAY_H_

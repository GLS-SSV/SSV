/****************************************************************************
  This file is part of Space Shuttle Vessel

  LDS definition


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
2020/05/10   GLS
2020/06/14   GLS
2020/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/12/25   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/

#include <Orbitersdk.h>
#include "Crawler_vc_defs.h"
#include <vector>

const int OFF = 0;
const int ON = 1;
const VECTOR3 VAB_HIGHBAY1 = _V(29,7.5,49.25);
const VECTOR3 VAB_HIGHBAY2 = _V(-29,7.5,49.25);

namespace vc
{


	class LDS : public CrawlerPanel
	{
		std::vector<MGROUP_ROTATE*> vpAnimations;
		std::vector<MGROUP_TRANSLATE*> LDSAnimation;

		UINT LDSBarAnim;
		UINT CabSelectionSwitchAnim;
		enum {CAB1, CAB3} CabSelectionSwitchPosition;
	public:
		LDS(Crawler* _v, const std::string& _ident, CRAWLER_CAB _cab);
		virtual ~LDS();

		void RegisterVC() override;
		void DefineVC() override;
		void Realize() override;
		void OnPostStep(double simt, double simdt, double mjd) override;

		void DefineVCAnimations(UINT vcidx) override;
		bool OnVCMouseEvent(int id, int _event, VECTOR3 &p) override;
	private:
		ATTACHMENTHANDLE FindNearestAttachment(VESSEL** pV) const;
		double CalculateDistanceBetweenAttachments();
		void UpdateLDS(double distance);
	};
}

/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel F7 definition



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
2020/05/08   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/12/26   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Panel F7 definition



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
#ifndef _VC_PANELF7_H_
#define _VC_PANELF7_H_


#include "AtlantisPanel.h"
#include <discsignals.h>


namespace vc
{
	class MDU;
	class _7SegDisp_EventTime;
	class StandardSingleLight;
	class StandardDoubleLight;

	using namespace discsignals;


	class PanelF7: public AtlantisPanel
	{
	private:
		MDU* pCRT1;
		MDU* pCRT2;
		MDU* pCRT3;
		MDU* pMFD1;
		MDU* pMFD2;

		_7SegDisp_EventTime* pEventTime;

		StandardSingleLight* pCWLight[38];
		StandardDoubleLight* pMainEngStatus[3];
		StandardSingleLight* pSMAlert;

		DiscInPort lighttestleft[2];
		DiscInPort lighttestright[2];
		DiscInPort lightcmd[38];
		DiscOutPort lightoutput[38];

	public:
		explicit PanelF7(Atlantis* _sts);
		virtual ~PanelF7();

		void DefineVC() override;
		void RegisterVC() override;
		void Realize() override;
		void OnPostStep( double simt, double simdt, double mjd ) override;
	};
}

#endif// _VC_PANELF7_H_

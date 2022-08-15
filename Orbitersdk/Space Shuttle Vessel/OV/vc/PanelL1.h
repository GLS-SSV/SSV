/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel L1 definition



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
2020/05/08   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/06/02   GLS
2021/08/24   GLS
2021/12/26   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Panel L1 definition



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
#ifndef __VC_PANELL1_H
#define __VC_PANELL1_H


#include "AtlantisPanel.h"


namespace vc
{
	class StandardSwitchCover;
	class PushButtonIndicatorSingleLight;
	class StandardSingleLight;


	class PanelL1 : public AtlantisPanel
	{
		private:
			StandardSwitchCover* pFireSuppressionAvBayAgentDischCover[3];
			PushButtonIndicatorSingleLight* pFireSuppressionAvBayAgentDisch[3];

			StandardSingleLight* pSmokeDetectionA_Cabin;
			StandardSingleLight* pSmokeDetectionA_LFltDeck;
			StandardSingleLight* pSmokeDetectionA_AvBay1;
			StandardSingleLight* pSmokeDetectionA_AvBay2;
			StandardSingleLight* pSmokeDetectionA_AvBay3;
			StandardSingleLight* pSmokeDetectionB_Payload;
			StandardSingleLight* pSmokeDetectionB_RFltDeck;
			StandardSingleLight* pSmokeDetectionB_AvBay1;
			StandardSingleLight* pSmokeDetectionB_AvBay2;
			StandardSingleLight* pSmokeDetectionB_AvBay3;

		public:
			explicit PanelL1( Atlantis* _sts );
			virtual ~PanelL1();

			void DefineVC( void ) override;
			void RegisterVC( void ) override;
			void Realize( void ) override;
	};
}

#endif// __VC_PANELL1_H
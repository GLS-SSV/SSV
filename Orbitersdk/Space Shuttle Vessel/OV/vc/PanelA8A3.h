/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel 36V73A8A3 definition



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
2020/03/20   GLS
2020/04/01   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/05/24   GLS
2020/06/20   GLS
2020/07/11   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/12/26   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Panel A7A3 and Panel A8A3 definition



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
#ifndef _VC_PANELA8A3_H_
#define _VC_PANELA8A3_H_


#include "AtlantisPanel.h"
#include <discsignals.h>


namespace vc
{
	class StandardSingleLight;
	class StdSwitch2;
	class StdSwitch3;
	class PushButton;
	class StandardSwitchCover;

	using namespace discsignals;


	class PanelA8A3: public AtlantisPanel
	{
		StandardSingleLight* plADS;
		StandardSingleLight* plBDS;
		StandardSingleLight* plCDS;
		StandardSingleLight* plPowerOn;
		StandardSingleLight* plAPDSProtectCircOff;
		StandardSingleLight* plRingAligned;
		StandardSingleLight* plRingInitialPos;
		StandardSingleLight* plFixersOff;
		StandardSingleLight* plHooks1Open;
		StandardSingleLight* plHooks2Open;
		StandardSingleLight* plLatchesClosed;
		StandardSingleLight* plUndockComplete;
		StandardSingleLight* plInitialContact;
		StandardSingleLight* plCapture;
		StandardSingleLight* plRingForward;
		StandardSingleLight* plReadyToHook;
		StandardSingleLight* plInterfSealed;
		StandardSingleLight* plHooks1Closed;
		StandardSingleLight* plHooks2Closed;
		StandardSingleLight* plLatchesOpen;
		StandardSingleLight* plRingFinal;
		StandardSingleLight* plAp;
		StandardSingleLight* plBp;
		StandardSingleLight* plCp;
		StandardSingleLight* pPyroProtectCircuitOff;

		StdSwitch2* pControlPanelPowerA;
		StdSwitch2* pControlPanelPowerB;
		StdSwitch2* pControlPanelPowerC;

		StdSwitch2* pHeatersDCUPowerH1;
		StdSwitch2* pHeatersDCUPowerH2DCU;
		StdSwitch2* pHeatersDCUPowerH3DCU;

		StdSwitch2* pAPDSPowerA;
		StdSwitch2* pAPDSPowerB;
		StdSwitch2* pAPDSPowerC;

		StdSwitch2* pPyrosAp;
		StdSwitch2* pPyrosBp;
		StdSwitch2* pPyrosCp;

		PushButton* pLampTest;
		PushButton* pPowerOn;
		PushButton* pPowerOff;
		PushButton* pRingOut;
		PushButton* pRingIn;
		PushButton* pAPDSCircProtOff;
		PushButton* pCloseHooks;
		PushButton* pCloseLatches;
		PushButton* pFixerOff;

		PushButton* pPyroCircProtOff;
		PushButton* pPyroCircProtOn;
		PushButton* pActHooksFiring;
		PushButton* pPasHooksFiring;
		PushButton* pOpenHooks;
		PushButton* pOpenLatches;
		PushButton* pUndocking;

		StandardSwitchCover* pPyroCommands;
		StandardSwitchCover* pAPDSControlCommands;

		DiscInPort CNTL_PNL_A;
		DiscInPort CNTL_PNL_V;
		DiscInPort lighttest;
		DiscInPort lightcmd[19];
		DiscOutPort lightoutput[19];

	public:
		explicit PanelA8A3( Atlantis* _sts, bool defaultposition );
		virtual ~PanelA8A3();

		void DefineVC() override;
		void Realize() override;
		void RegisterVC() override;
		void OnPostStep( double simt, double simdt, double mjd ) override;
	};
}

#endif// _VC_PANELA8A3_H_

/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel A15 (EDO) definition



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
#ifndef __VC_PANELA15_EDO_H
#define __VC_PANELA15_EDO_H


#include "AtlantisPanel.h"


namespace vc
{
	class CircuitBreaker;
	class StdSwitch2;
	class StdSwitch3;
	class StandardTalkback2;


	class PanelA15_EDO : public AtlantisPanel
	{
		private:
			StdSwitch3* pCryoTank5HeatersO2A;
			StdSwitch3* pCryoTank5HeatersO2B;
			StdSwitch3* pCryoTank5HeatersO2ResetTest;
			StdSwitch3* pCryoTank5HeatersH2A;
			StdSwitch3* pCryoTank5HeatersH2B;

			StandardTalkback2* pPalletPowerPPCA1;
			StandardTalkback2* pPalletPowerPPCA2;

			StdSwitch3* pPalletPowerMNA;
			StdSwitch3* pPalletPowerMNB;

			CircuitBreaker* pPPCAContPwr1ESS1BC;
			CircuitBreaker* pPPCAContPwr2ESS2CA;

			StdSwitch2* pPalletHeatersA;
			StdSwitch2* pPalletHeatersB;

			StdSwitch3* pPalletCryoTankHeatersO2Tank6A;
			StdSwitch3* pPalletCryoTankHeatersO2Tank6B;
			StdSwitch3* pPalletCryoTankHeatersO2Tank6ResetTest;
			StdSwitch3* pPalletCryoTankHeatersH2Tank6A;
			StdSwitch3* pPalletCryoTankHeatersH2Tank6B;

			StdSwitch3* pPalletCryoTankHeatersO2Tank7A;
			StdSwitch3* pPalletCryoTankHeatersO2Tank7B;
			StdSwitch3* pPalletCryoTankHeatersO2Tank7ResetTest;
			StdSwitch3* pPalletCryoTankHeatersH2Tank7A;
			StdSwitch3* pPalletCryoTankHeatersH2Tank7B;

			StdSwitch3* pPalletCryoTankHeatersO2Tank8A;
			StdSwitch3* pPalletCryoTankHeatersO2Tank8B;
			StdSwitch3* pPalletCryoTankHeatersO2Tank8ResetTest;
			StdSwitch3* pPalletCryoTankHeatersH2Tank8A;
			StdSwitch3* pPalletCryoTankHeatersH2Tank8B;

			StdSwitch3* pPalletCryoTankHeatersO2Tank9A;
			StdSwitch3* pPalletCryoTankHeatersO2Tank9B;
			StdSwitch3* pPalletCryoTankHeatersO2Tank9ResetTest;
			StdSwitch3* pPalletCryoTankHeatersH2Tank9A;
			StdSwitch3* pPalletCryoTankHeatersH2Tank9B;

			CircuitBreaker* pPalletCryoTank6CntrlO2;
			CircuitBreaker* pPalletCryoTank6CntrlH2;
			CircuitBreaker* pPalletCryoTank6QtyO2;
			CircuitBreaker* pPalletCryoTank6QtyH2;
			CircuitBreaker* pPalletCryoTank6O2HtrSnsr1;
			CircuitBreaker* pPalletCryoTank6O2HtrSnsr2;

			CircuitBreaker* pPalletCryoTank7CntrlO2;
			CircuitBreaker* pPalletCryoTank7CntrlH2;
			CircuitBreaker* pPalletCryoTank7QtyO2;
			CircuitBreaker* pPalletCryoTank7QtyH2;
			CircuitBreaker* pPalletCryoTank7O2HtrSnsr1;
			CircuitBreaker* pPalletCryoTank7O2HtrSnsr2;

			CircuitBreaker* pPalletCryoTank8CntrlO2;
			CircuitBreaker* pPalletCryoTank8CntrlH2;
			CircuitBreaker* pPalletCryoTank8QtyO2;
			CircuitBreaker* pPalletCryoTank8QtyH2;
			CircuitBreaker* pPalletCryoTank8O2HtrSnsr1;
			CircuitBreaker* pPalletCryoTank8O2HtrSnsr2;

			CircuitBreaker* pPalletCryoTank9CntrlO2;
			CircuitBreaker* pPalletCryoTank9CntrlH2;
			CircuitBreaker* pPalletCryoTank9QtyO2;
			CircuitBreaker* pPalletCryoTank9QtyH2;
			CircuitBreaker* pPalletCryoTank9O2HtrSnsr1;
			CircuitBreaker* pPalletCryoTank9O2HtrSnsr2;

			StdSwitch2* pPSCommCCUPwr;
			StdSwitch2* pDCUtilityPower;
			StdSwitch2* pACUtilityPower;

			SURFHANDLE hTexture;

			bool ov102;
			bool ov103;
			bool ov104;
			bool ov105;

		public:
			explicit PanelA15_EDO( Atlantis* _sts, const std::string &orbiter );
			virtual ~PanelA15_EDO( void );

			void DefineVC( void ) override;
			void RegisterVC( void ) override;
			void Realize( void ) override;
			void VisualCreated( void ) override;
	};
}

#endif// __VC_PANELA15_EDO_H

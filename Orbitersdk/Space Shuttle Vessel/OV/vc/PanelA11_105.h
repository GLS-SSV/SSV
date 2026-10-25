/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel A11 (OV-105) definition



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
#ifndef __VC_PANELA11_105_H
#define __VC_PANELA11_105_H


#include "AtlantisPanel.h"


namespace vc
{
	class CircuitBreaker;
	class StdSwitch2;
	class StdSwitch3;


	class PanelA11_105 : public AtlantisPanel
	{
		private:
			StdSwitch3* pCryoTank4HeatersO2A;
			StdSwitch3* pCryoTank4HeatersO2B;
			StdSwitch3* pCryoTank4HeatersO2ResetTest;
			StdSwitch3* pCryoTank4HeatersH2A;
			StdSwitch3* pCryoTank4HeatersH2B;

			StdSwitch3* pPalletCryoTankHeatersO2Tank10A;
			StdSwitch3* pPalletCryoTankHeatersO2Tank10B;
			StdSwitch3* pPalletCryoTankHeatersO2Tank10ResetTest;
			StdSwitch3* pPalletCryoTankHeatersH2Tank10A;
			StdSwitch3* pPalletCryoTankHeatersH2Tank10B;

			StdSwitch3* pPalletCryoTankHeatersO2Tank11A;
			StdSwitch3* pPalletCryoTankHeatersO2Tank11B;
			StdSwitch3* pPalletCryoTankHeatersO2Tank11ResetTest;
			StdSwitch3* pPalletCryoTankHeatersH2Tank11A;
			StdSwitch3* pPalletCryoTankHeatersH2Tank11B;

			StdSwitch3* pPalletCryoTankHeatersO2Tank12A;
			StdSwitch3* pPalletCryoTankHeatersO2Tank12B;
			StdSwitch3* pPalletCryoTankHeatersO2Tank12ResetTest;
			StdSwitch3* pPalletCryoTankHeatersH2Tank12A;
			StdSwitch3* pPalletCryoTankHeatersH2Tank12B;

			StdSwitch3* pPalletCryoTankHeatersO2Tank13A;
			StdSwitch3* pPalletCryoTankHeatersO2Tank13B;
			StdSwitch3* pPalletCryoTankHeatersO2Tank13ResetTest;
			StdSwitch3* pPalletCryoTankHeatersH2Tank13A;
			StdSwitch3* pPalletCryoTankHeatersH2Tank13B;

			CircuitBreaker* pPalletCryoTank10CntrlO2;
			CircuitBreaker* pPalletCryoTank10CntrlH2;
			CircuitBreaker* pPalletCryoTank10QtyO2;
			CircuitBreaker* pPalletCryoTank10QtyH2;
			CircuitBreaker* pPalletCryoTank10O2HtrSnsr1;
			CircuitBreaker* pPalletCryoTank10O2HtrSnsr2;

			CircuitBreaker* pPalletCryoTank11CntrlO2;
			CircuitBreaker* pPalletCryoTank11CntrlH2;
			CircuitBreaker* pPalletCryoTank11QtyO2;
			CircuitBreaker* pPalletCryoTank11QtyH2;
			CircuitBreaker* pPalletCryoTank11O2HtrSnsr1;
			CircuitBreaker* pPalletCryoTank11O2HtrSnsr2;

			CircuitBreaker* pPalletCryoTank12CntrlO2;
			CircuitBreaker* pPalletCryoTank12CntrlH2;
			CircuitBreaker* pPalletCryoTank12QtyO2;
			CircuitBreaker* pPalletCryoTank12QtyH2;
			CircuitBreaker* pPalletCryoTank12O2HtrSnsr1;
			CircuitBreaker* pPalletCryoTank12O2HtrSnsr2;

			CircuitBreaker* pPalletCryoTank13CntrlO2;
			CircuitBreaker* pPalletCryoTank13CntrlH2;
			CircuitBreaker* pPalletCryoTank13QtyO2;
			CircuitBreaker* pPalletCryoTank13QtyH2;
			CircuitBreaker* pPalletCryoTank13O2HtrSnsr1;
			CircuitBreaker* pPalletCryoTank13O2HtrSnsr2;

			StdSwitch2* pMSCommCCUPwr;
			StdSwitch2* pDCUtilityPower;

			StdSwitch2* pPalletHeaterC;
			StdSwitch2* pPalletHeaterD;

		public:
			explicit PanelA11_105( Atlantis* _sts );
			virtual ~PanelA11_105( void );

			void DefineVC( void ) override;
			void RegisterVC( void ) override;
			void Realize( void ) override;
	};
}

#endif// __VC_PANELA11_105_H

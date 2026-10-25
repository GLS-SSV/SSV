/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel A11 (OV-104 EDO) definition



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
#ifndef __VC_PANELA11_104_EDO_H
#define __VC_PANELA11_104_EDO_H


#include "AtlantisPanel.h"


namespace vc
{
	class CircuitBreaker;
	class StdSwitch2;
	class StdSwitch3;


	class PanelA11_104_EDO : public AtlantisPanel
	{
		private:
			StdSwitch3* pCryoTank4HeatersO2A;
			StdSwitch3* pCryoTank4HeatersO2B;
			StdSwitch3* pCryoTank4HeatersO2ResetTest;
			StdSwitch3* pCryoTank4HeatersH2A;
			StdSwitch3* pCryoTank4HeatersH2B;

			StdSwitch3* pCryoTankSelect6_10_O2;
			StdSwitch3* pCryoTankSelect6_10_H2;

			StdSwitch3* pCryoTankSelect7_11_O2;
			StdSwitch3* pCryoTankSelect7_11_H2;

			StdSwitch3* pCryoTankSelect8_12_O2;
			StdSwitch3* pCryoTankSelect8_12_H2;

			StdSwitch3* pCryoTankSelect9_13_O2;
			StdSwitch3* pCryoTankSelect9_13_H2;

			CircuitBreaker* pPalletCryoTank10QtyO2;
			CircuitBreaker* pPalletCryoTank10QtyH2;

			CircuitBreaker* pPalletCryoTank11QtyO2;
			CircuitBreaker* pPalletCryoTank11QtyH2;

			CircuitBreaker* pPalletCryoTank12QtyO2;
			CircuitBreaker* pPalletCryoTank12QtyH2;

			CircuitBreaker* pPalletCryoTank13QtyO2;
			CircuitBreaker* pPalletCryoTank13QtyH2;

			StdSwitch2* pMSCommCCUPwr;
			StdSwitch2* pDCUtilityPower;

		public:
			explicit PanelA11_104_EDO( Atlantis* _sts );
			virtual ~PanelA11_104_EDO( void );

			void DefineVC( void ) override;
			void RegisterVC( void ) override;
			void Realize( void ) override;
	};
}

#endif// __VC_PANELA11_104_EDO_H

/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel A11 (OV-102) definition



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
#ifndef __VC_PANELA11_102_H
#define __VC_PANELA11_102_H


#include "AtlantisPanel.h"


namespace vc
{
	class StdSwitch2;
	class StdSwitch3;


	class PanelA11_102 : public AtlantisPanel
	{
		private:
			StdSwitch3* pCryoTank45HeatersO2TK4;
			StdSwitch3* pCryoTank45HeatersO2TK5;
			StdSwitch3* pCryoTank45HeatersO2TK45ResetTest;
			StdSwitch3* pCryoTank45HeatersH2TK45A;
			StdSwitch3* pCryoTank45HeatersH2TK45B;

			StdSwitch2* pMSCommCCUPwr;
			StdSwitch2* pOSCommCCUPwr;
			StdSwitch2* pDCUtilityPower;

		public:
			explicit PanelA11_102( Atlantis* _sts );
			virtual ~PanelA11_102( void );

			void DefineVC( void ) override;
			void RegisterVC( void ) override;
			void Realize( void ) override;
	};
}

#endif// __VC_PANELA11_102_H

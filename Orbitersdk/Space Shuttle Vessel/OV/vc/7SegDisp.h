/****************************************************************************
  This file is part of Space Shuttle Vessel

  7-Segment Display VC Component


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
2020/06/20   GLS
2021/01/20   GLS
2021/06/28   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/23   GLS
2021/12/26   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  7-Segment Display VC Component



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
#ifndef __7SD_H
#define __7SD_H


#include "AtlantisVCComponent.h"
#include <vector>


namespace vc
{
	inline constexpr int _7SD_STATE_NUM0 = 0;
	inline constexpr int _7SD_STATE_NUM1 = 1;
	inline constexpr int _7SD_STATE_NUM2 = 2;
	inline constexpr int _7SD_STATE_NUM3 = 3;
	inline constexpr int _7SD_STATE_NUM4 = 4;
	inline constexpr int _7SD_STATE_NUM5 = 5;
	inline constexpr int _7SD_STATE_NUM6 = 6;
	inline constexpr int _7SD_STATE_NUM7 = 7;
	inline constexpr int _7SD_STATE_NUM8 = 8;
	inline constexpr int _7SD_STATE_NUM9 = 9;
	inline constexpr int _7SD_STATE_NUMOFF = 10;

	inline constexpr int _7SD_STATE_NUM0_DOTON = 11;
	inline constexpr int _7SD_STATE_NUM1_DOTON = 12;
	inline constexpr int _7SD_STATE_NUM2_DOTON = 13;
	inline constexpr int _7SD_STATE_NUM3_DOTON = 14;
	inline constexpr int _7SD_STATE_NUM4_DOTON = 15;
	inline constexpr int _7SD_STATE_NUM5_DOTON = 16;
	inline constexpr int _7SD_STATE_NUM6_DOTON = 17;
	inline constexpr int _7SD_STATE_NUM7_DOTON = 18;
	inline constexpr int _7SD_STATE_NUM8_DOTON = 19;
	inline constexpr int _7SD_STATE_NUM9_DOTON = 20;
	inline constexpr int _7SD_STATE_NUMOFF_DOTON = 21;

	inline constexpr int _7SD_STATE_NUM0_DOTOFF = 22;
	inline constexpr int _7SD_STATE_NUM1_DOTOFF = 23;
	inline constexpr int _7SD_STATE_NUM2_DOTOFF = 24;
	inline constexpr int _7SD_STATE_NUM3_DOTOFF = 25;
	inline constexpr int _7SD_STATE_NUM4_DOTOFF = 26;
	inline constexpr int _7SD_STATE_NUM5_DOTOFF = 27;
	inline constexpr int _7SD_STATE_NUM6_DOTOFF = 28;
	inline constexpr int _7SD_STATE_NUM7_DOTOFF = 29;
	inline constexpr int _7SD_STATE_NUM8_DOTOFF = 30;
	inline constexpr int _7SD_STATE_NUM9_DOTOFF = 31;
	inline constexpr int _7SD_STATE_NUMOFF_DOTOFF = 32;

	inline constexpr int _7SD_STATE_SIGNPLUS = 33;
	inline constexpr int _7SD_STATE_SIGNMINUS = 34;
	inline constexpr int _7SD_STATE_SIGNOFF = 35;

	inline constexpr int _7SD_STATE_SIGN2PLUS = 36;
	inline constexpr int _7SD_STATE_SIGN2MINUS = 37;
	inline constexpr int _7SD_STATE_SIGN2OFF = 38;
	inline constexpr int _7SD_STATE_SIGN2ON = 39;


	class _7SegDisp:public AtlantisVCComponent
	{
		protected:
			std::vector<int> default_state;
			std::vector<int> state;
			std::vector<int> next_state;
			//std::vector<bool> IsDoubleSign;
			//std::vector<bool> HasDecimalPoint;
			//std::vector<bool> IsNumber;
			std::vector<UINT> grpIndex;

			UINT panelmesh;

			void UpdateUV( int component );

		public:
			_7SegDisp( Atlantis* _sts, const std::string& _ident );
			virtual ~_7SegDisp();

			void OnPreStep( double simt, double simdt, double mjd ) override;

			void DefineMesh( UINT _panelmesh );
			void DefineComponent( UINT _grpIndex, bool _IsNumber = true, bool _HasDecimalPoint = false, bool _IsDoubleSign = false, int _default_state = _7SD_STATE_NUM0 );

			virtual void VisualCreated( void ) override;

			virtual void Controller( void ) = 0;
	};
}

#endif// __7SD_H

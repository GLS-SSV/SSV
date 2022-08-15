/****************************************************************************
  This file is part of Space Shuttle Vessel

  Talkback VC Component definition


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
2020/06/20   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Talkback VC Component



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
#ifndef __TALKBACK_H
#define __TALKBACK_H
#pragma once

#include "AtlantisVCComponent.h"
#include <DiscInPort.h>

namespace vc
{
	using namespace discsignals;

	inline constexpr int TB_BARBERPOLE = 0;
	inline constexpr int TB_STO = 1;
	inline constexpr int TB_LAT = 2;
	inline constexpr int TB_CL = 3;
	inline constexpr int TB_OP = 4;
	inline constexpr int TB_ON = 5;
	inline constexpr int TB_OFF = 6;
	inline constexpr int TB_X10 = 7;
	inline constexpr int TB_GRAY = 8;
	inline constexpr int TB_DPY = 9;
	inline constexpr int TB_REL = 10;
	inline constexpr int TB_DN = 11;
	inline constexpr int TB_UP = 12;
	inline constexpr int TB_RUN = 13;
	inline constexpr int TB_IPL = 14;
	inline constexpr int TB_ICH = 15;
	inline constexpr int TB_RAD = 16;
	inline constexpr int TB_PL = 17;
	inline constexpr int TB_BYP = 18;


	class BasicTalkback : public AtlantisVCComponent
	{
		protected:
			UINT panelmesh;
			unsigned short usInactiveFlag;
			unsigned short tkbk_default_state;

			void SoundOff( void ) const;
			void SoundOn( void ) const;

		public:
			BasicTalkback(Atlantis* _sts, const std::string& _ident);
			virtual ~BasicTalkback();

			void SetInactiveSegment( unsigned short _usFlag );
	};

	class StandardTalkback2 : public BasicTalkback
	{
		protected:
			unsigned short tkbk_state_U;
			unsigned short tkbk_state_L;
			unsigned short tkbk_next_state_U;
			unsigned short tkbk_next_state_L;
			unsigned short usCover;
			UINT grpIndex_U;
			UINT grpIndex_L;

			void UpdateUV( void );

		public:
			StandardTalkback2( Atlantis* _sts, const std::string& _ident );
			virtual ~StandardTalkback2();

			void OnPostStep(double simt, double simdt, double mjd) override;

			void DefineMeshGroups( UINT _panelmesh, UINT _grpIndex_U, UINT _grpIndex_L );
			void SetInitialState( unsigned short _usFlag );
			void SetInput( DiscreteBundle* pBundle, unsigned short usLine, unsigned short usFlag );
			void SetCoverSegment( unsigned short _usFlag );
			void VisualCreated( void )override;

			unsigned short flags;
			DiscInPort input;
	};

	class StandardTalkback3 : public BasicTalkback
	{
		protected:
			unsigned short tkbk_state;
			unsigned short tkbk_next_state;
			UINT grpIndex;

			void UpdateUV( void );

		public:
			StandardTalkback3( Atlantis* _sts, const std::string& _ident );
			virtual ~StandardTalkback3();

			void OnPostStep(double simt, double simdt, double mjd) override;

			void DefineMeshGroup( UINT _panelmesh, UINT _grpIndex );
			void SetInitialState( unsigned short _usFlag );
			void SetInput( unsigned short idx, DiscreteBundle* pBundle, unsigned short usLine, unsigned short usFlag );
			void VisualCreated( void ) override;

			unsigned short flags[2];
			DiscInPort input[2];
	};
};

#endif //__TALKBACK_H
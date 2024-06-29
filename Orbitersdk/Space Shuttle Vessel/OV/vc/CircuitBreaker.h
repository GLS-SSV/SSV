/****************************************************************************
  This file is part of Space Shuttle Vessel

  Circuit Breaker VC Component


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
2021/08/24   GLS
2021/12/26   GLS
2022/09/29   GLS
2024/02/11   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Circuit Breaker VC Component



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
#ifndef __CIRCUITBREAKER_H
#define __CIRCUITBREAKER_H


#include "AtlantisVCComponent.h"
#include <discsignals.h>


namespace vc
{
	using namespace discsignals;

	class CircuitBreaker:public AtlantisVCComponent
	{
		private:
			bool CBin;
			bool hasinput;// indicates if input is connected and should be used to source output voltage

			DiscInPort input;
			DiscOutPort output;

			UINT grpIndex;
			MGROUP_TRANSLATE* move;
			UINT anim_move;

			double t0;
			bool counting;

			void OnChange( bool _CBin );
			void SetOutput( void );

		public:
			CircuitBreaker( Atlantis* _sts, const std::string& _ident );
			virtual ~CircuitBreaker();

			bool OnParseLine( const char* line ) override;
			bool GetStateString( unsigned long ulBufferSize, char* pszBuffer ) override;
			void DefineGroup( UINT _grpIndex );
			void Connect( DiscreteBundle* pBundle, unsigned short usLine );
			void ConnectInput( DiscreteBundle* pBundle, unsigned short usLine );
			void DefineVCAnimations( UINT vc_idx ) override;
			bool OnMouseEvent( int _event, float x, float y ) override;
			void SetInitialPosition( bool in );
			void OnPreStep( double simt, double simdt, double mjd ) override;
	};
}

#endif// __CIRCUITBREAKER_H

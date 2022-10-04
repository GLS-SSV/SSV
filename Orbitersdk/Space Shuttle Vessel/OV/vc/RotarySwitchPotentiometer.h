/****************************************************************************
  This file is part of Space Shuttle Vessel

  Rotary Switch Potentiometer VC Component


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
#ifndef __ROTARYSWITCHPOTENTIOMETER_H
#define __ROTARYSWITCHPOTENTIOMETER_H


#include "AtlantisVCComponent.h"
#include <DiscOutPort.h>


namespace vc
{
	using namespace discsignals;

	class RotarySwitchPotentiometer:public AtlantisVCComponent
	{
		private:
			double pos;// [0:1]
			double ang;

			DiscOutPort input;
			DiscOutPort output;

			UINT grpIndex;
			MGROUP_ROTATE* rot;
			UINT anim_rot;

			void OnPositionChange( void );

		public:
			RotarySwitchPotentiometer( Atlantis* _sts, const std::string& _ident );
			virtual ~RotarySwitchPotentiometer();

			bool OnParseLine( const char* line ) override;
			bool GetStateString( unsigned long ulBufferSize, char* pszBuffer ) override;
			void DefineGroup( UINT _grpIndex );
			void Connect( DiscreteBundle* pBundle, unsigned short usLine );
			void DefineVCAnimations( UINT vc_idx ) override;
			bool OnMouseEvent( int _event, float x, float y ) override;
			void SetAngleRange( double ang );
	};
}

#endif// __ROTARYSWITCHPOTENTIOMETER_H

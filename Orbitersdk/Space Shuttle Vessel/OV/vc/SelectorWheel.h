/****************************************************************************
  This file is part of Space Shuttle Vessel

  Selector Wheel VC Component


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
#ifndef __SELECTORWHEEL_H
#define __SELECTORWHEEL_H


#include "AtlantisVCComponent.h"
#include <DiscOutPort.h>


namespace vc
{
	inline constexpr double WHEEL_RATE = 1.0;// [1/s]


	using namespace discsignals;


	class SelectorWheel:public AtlantisVCComponent
	{
		private:
			short dirsign;
			unsigned short posidx;
			unsigned short uboundidx;
			unsigned short lboundidx;
			bool boundset;
			unsigned short outputval[10];

			DiscOutPort output[4];

			UINT grpIndex;
			MGROUP_ROTATE* wheel;
			UINT anim_wheel;

		protected:
			void SetOutput( void );

			/**
			 *
			 * @return	true if motion, false if wheel is at limits
			 */
			bool OnChange( bool up );
			virtual void PlayChangeSound( void );

		public:
			SelectorWheel( Atlantis* _sts, const std::string& _ident );
			virtual ~SelectorWheel();

			bool OnParseLine( const char* line ) override;
			bool GetStateString( unsigned long ulBufferSize, char* pszBuffer ) override;
			void DefineWheelGroup( UINT _grpIndex );
			void Connect( DiscreteBundle* pBundle, unsigned short usLine, unsigned short bcdidx );
			void DefineVCAnimations( UINT vc_idx ) override;
			virtual bool OnMouseEvent( int _event, float x, float y ) override = 0;
			void OnPostStep( double simt, double simdt, double mjd ) override;

			void SetBounds( unsigned short lower, unsigned short upper );
			void DefineOutputs( unsigned short idx, unsigned short val );
	};
}

#endif// __SELECTORWHEEL_H

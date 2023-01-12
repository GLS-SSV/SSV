/****************************************************************************
  This file is part of Space Shuttle Vessel

  Systems Management Displays definition


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
#ifndef _dps_SMDISP_H_
#define _dps_SMDISP_H_


#include "../GeneralDisplays.h"
#include <discsignals.h>


using namespace discsignals; 


namespace dps
{
	class SMDisplays:public GeneralDisplays
	{
		private:
			void OnPaint_SM_SPEC94_PASS( vc::MDU* pMDU ) const;
			void OnPaint_SM_DISP95_PASS( vc::MDU* pMDU ) const;
			void OnPaint_SM_DISP96_PASS( vc::MDU* pMDU ) const;
			void OnPaint_SM_DISP97_PASS( vc::MDU* pMDU ) const;
			void OnPaint_SM_DISP169_PASS( vc::MDU* pMDU ) const;
			void OnPaint_SM_ANTENNA_PASS( vc::MDU* pMDU ) const;
			void OnPaint_SM_PLBAYDOORS_PASS( vc::MDU* pMDU ) const;

			bool ItemInput_SM_SPEC94_PASS( int item, const char* Data );
			bool ItemInput_SM_ANTENNA_PASS( int item, const char* Data );
			bool ItemInput_SM_PLBAYDOORS_PASS( int item, const char* Data );

		public:
			explicit SMDisplays( SimpleGPCSystem* _gpc );
			~SMDisplays( void );

			bool OnMajorModeChange( unsigned int newMajorMode ) override;

			/**
			 * Handles Item entry on shuttle's keyboard.
			 * Returns true if input OK, false for illegal entry.
			 * @param spec spec currently displayed
			 * @param item ITEM number
			 * @param Data string containing data entered
			 */
			bool ItemInput( int spec, int item, const char* Data ) override;

			/**
			 * Draws display on MDU.
			 * Returns true if data was drawn; false otherwise
			 */
			bool OnPaint( int spec, vc::MDU* pMDU ) const override;
	};
}


#endif// _dps_SMDISP_H_

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


namespace dps
{
	class SMDisplays:public GeneralDisplays
	{
		private:
			unsigned short RMS_SEL;

			void OnPaint_SPEC94( CRT_Interface* crt ) const;
			void OnPaint_SPEC95( CRT_Interface* crt ) const;
			void OnPaint_DISP96( CRT_Interface* crt ) const;
			void OnPaint_DISP97( CRT_Interface* crt ) const;
			void OnPaint_DISP169( CRT_Interface* crt ) const;
			void OnPaint_ANTENNA( CRT_Interface* crt ) const;
			void OnPaint_PLBAYDOORS( CRT_Interface* crt ) const;

			void BackgroundData_SPEC94( CRT_Interface* crt ) const;
			void BackgroundData_SPEC95( CRT_Interface* crt ) const;
			void BackgroundData_DISP96( CRT_Interface* crt ) const;
			void BackgroundData_DISP97( CRT_Interface* crt ) const;
			void BackgroundData_DISP169( CRT_Interface* crt ) const;
			void BackgroundData_ANTENNA( CRT_Interface* crt ) const;
			void BackgroundData_PLBAYDOORS( CRT_Interface* crt ) const;

			bool ItemInput_SPEC94( int item, const char* Data );
			bool ItemInput_ANTENNA( int item, const char* Data );
			bool ItemInput_PLBAYDOORS( int item, const char* Data );

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
			 */
			void Paint( CRT_Interface* crt, unsigned short page ) const override;

			/**
			 * Draws display on MDU.
			 */
			void PaintBackground( CRT_Interface* crt, unsigned short page ) const override;
	};
}


#endif// _dps_SMDISP_H_

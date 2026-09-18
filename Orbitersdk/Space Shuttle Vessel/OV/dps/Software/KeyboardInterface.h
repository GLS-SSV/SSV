/****************************************************************************
  This file is part of Space Shuttle Vessel

  Keyboard Interface definition


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
#ifndef _KBIF_H_
#define _KBIF_H_


#include "SimpleGPCSoftware.h"


namespace dps
{
	/**
	 * System Services \ User Interface \ Command Input Process
	 */
	class KeyboardInterface:public SimpleGPCSoftware
	{
		private:
			unsigned short DMIB_ERR_MSG;
			unsigned short DMMV_MF_NEW[4];// Current_MF_Setting
			unsigned short DMMV_BYPASS;// Bypass_Logic
			unsigned short DMMB_MF_TIMING;// MF_Timing_Needed
			unsigned short DMMB_MF_TIMR[4];// MF_3Cycle_Timer
			unsigned short DMMV_NEW_FRZ;// Current_Freeze
			unsigned short DMMV_OLD_FRZ;// Old_Freeze


			void DMI_MCDS_IN( void );// MCDS input processor (400)

			void DMM_MCDS_PROCESS( unsigned char deu );// MCDS message processor (405)
			//void Initialization_Process( void );//(405.1)
			//void Bite_Process( void );//(405.2)
			void MF_Process( unsigned char deu );//(405.3)
			//void Keyboard_Process( void );//(405.4)
			//void Convert_Keys( void );//(405.5)
			//void Freeze_Process( void );//(405.6)

		public:
			explicit KeyboardInterface( SimpleGPCSystem* pGPC );
			virtual ~KeyboardInterface( void );

			void OnPreStep( double simt, double simdt, double mjd );

			bool OnParseLine( const char* keyword, const char* value );
			void OnSaveState( FILEHANDLE scn ) const;
	};
}

#endif// _KBIF_H_

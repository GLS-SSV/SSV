/****************************************************************************
  This file is part of Space Shuttle Vessel

  Orbiter Actuator Slew Check definition


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
#ifndef _dps_ORBACTRSLEW_H_
#define _dps_ORBACTRSLEW_H_


#include "../SimpleGPCSoftware.h"


namespace dps
{
	class ORB_ACTR_SLEW:public SimpleGPCSoftware
	{
		private:
			unsigned short FP;

			unsigned short P;
			unsigned short DELAY;
			unsigned short HOLD;
			unsigned short TRAP_CYC;
			unsigned short SLEW_PROG;
			unsigned short SLEW_FLAG[3];
			unsigned short SLEW_COMPLETE[3];

			unsigned short AERO_I;
			unsigned short MPS_I;

			double cycledt;

			void SLEW_CHK( const unsigned short NULL_CYC, const unsigned short CYC, const unsigned short* SLEW_TIME, const float* POSN, const float DELTA, unsigned short& I, float& CMD, const double dt );

		public:
			explicit ORB_ACTR_SLEW( SimpleGPCSystem* _gpc );
			~ORB_ACTR_SLEW( void );

			void OnPreStep( double simt, double simdt, double mjd ) override;

			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;
	};
}

#endif// _dps_ORBACTRSLEW_H_

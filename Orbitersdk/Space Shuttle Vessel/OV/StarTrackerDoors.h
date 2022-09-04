/****************************************************************************
  This file is part of Space Shuttle Vessel

  Star Tracker Doors subsystem definition



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
#ifndef _ST_DOORS_H_
#define _ST_DOORS_H_


#include "AtlantisSubsystem.h"
#include "discsignals.h"


using namespace discsignals;


class StarTrackerDoors:public AtlantisSubsystem
{
	private:
		double Ypos;// [0:1]
		double Zpos;// [0:1]

		UINT anim_Y;
		UINT anim_Z;

		// -Y SYSTEM 1 MOTOR CONTROL
		DiscOutPort STAR_TRACKER_Y_DOOR_CLS_1;
		DiscOutPort STAR_TRACKER_Y_DOOR_OP_1;
		DiscInPort SYS_1_MOTOR_1_PWR;

		// -Y SYSTEM 2 MOTOR CONTROL
		DiscOutPort STAR_TRACKER_Y_DOOR_CLS_2;
		DiscOutPort STAR_TRACKER_Y_DOOR_OP_2;
		DiscInPort SYS_2_MOTOR_2_PWR;

		// -Z SYSTEM 1 MOTOR CONTROL
		DiscOutPort STAR_TRACKER_Z_DOOR_CLS_2;
		DiscOutPort STAR_TRACKER_Z_DOOR_OP_2;
		DiscInPort SYS_1_MOTOR_2_PWR;

		// -Z SYSTEM 2 MOTOR CONTROL
		DiscOutPort STAR_TRACKER_Z_DOOR_CLS_1;
		DiscOutPort STAR_TRACKER_Z_DOOR_OP_1;
		DiscInPort SYS_2_MOTOR_1_PWR;


		void DefineAnimations( void );
		void SetIndications( void );

	public:
		explicit StarTrackerDoors( AtlantisSubsystemDirector* _director );
		~StarTrackerDoors( void );

		void Realize( void ) override;
		bool OnParseLine( const char* keyword, const char* value ) override;
		void OnSaveState( FILEHANDLE scn ) const override;

		void OnPostStep( double simt, double simdt, double mjd ) override;
};


#endif// _ST_DOORS_H_

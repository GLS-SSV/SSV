/****************************************************************************
  This file is part of Space Shuttle Vessel

  Vent Doors subsystem definition


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
#ifndef _VENTDOORS_H_
#define _VENTDOORS_H_


#include "AtlantisSubsystem.h"
#include <discsignals.h>


using namespace discsignals;


class VentDoors: public AtlantisSubsystem 
{
	private:
		// 0 = closed, 1 = open
		double posLH12;
		double posLH3;
		double posLH47;
		double posLH5;
		double posLH6;
		double posLH89;
		double posRH12;
		double posRH3;
		double posRH47;
		double posRH5;
		double posRH6;
		double posRH89;

		UINT anim_LH1;
		UINT anim_LH2;
		UINT anim_LH3;
		UINT anim_LH4;
		UINT anim_LH5;
		UINT anim_LH6;
		UINT anim_LH7;
		UINT anim_LH8;
		UINT anim_LH9;
		UINT anim_RH1;
		UINT anim_RH2;
		UINT anim_RH3;
		UINT anim_RH4;
		UINT anim_RH5;
		UINT anim_RH6;
		UINT anim_RH7;
		UINT anim_RH8;
		UINT anim_RH9;

		bool hasVentDoor47;

		DiscInPort LH_VENTS_1_AND_2_MOTOR_1_PWR;
		DiscInPort LH_VENTS_1_AND_2_MOTOR_2_PWR;

		DiscInPort LH_VENT_3_MOTOR_1_PWR;
		DiscInPort LH_VENT_3_MOTOR_2_PWR;

		DiscInPort LH_VENTS_4_AND_7_MOTOR_1_PWR;
		DiscInPort LH_VENTS_4_AND_7_MOTOR_2_PWR;

		DiscInPort LH_VENT_5_MOTOR_1_PWR;
		DiscInPort LH_VENT_5_MOTOR_2_PWR;

		DiscInPort LH_VENT_6_MOTOR_1_PWR;
		DiscInPort LH_VENT_6_MOTOR_2_PWR;

		DiscInPort LH_VENTS_8_AND_9_MOTOR_1_PWR;
		DiscInPort LH_VENTS_8_AND_9_MOTOR_2_PWR;

		DiscInPort RH_VENTS_1_AND_2_MOTOR_1_PWR;
		DiscInPort RH_VENTS_1_AND_2_MOTOR_2_PWR;

		DiscInPort RH_VENT_3_MOTOR_1_PWR;
		DiscInPort RH_VENT_3_MOTOR_2_PWR;

		DiscInPort RH_VENTS_4_AND_7_MOTOR_1_PWR;
		DiscInPort RH_VENTS_4_AND_7_MOTOR_2_PWR;

		DiscInPort RH_VENT_5_MOTOR_1_PWR;
		DiscInPort RH_VENT_5_MOTOR_2_PWR;

		DiscInPort RH_VENT_6_MOTOR_1_PWR;
		DiscInPort RH_VENT_6_MOTOR_2_PWR;

		DiscInPort RH_VENTS_8_AND_9_MOTOR_1_PWR;
		DiscInPort RH_VENTS_8_AND_9_MOTOR_2_PWR;


		DiscOutPort L_VENTS_1_AND_2_CLOSE_1;
		DiscOutPort L_VENTS_1_AND_2_CLOSE_1_TM;
		DiscOutPort L_VENTS_1_AND_2_CLOSE_2;
		DiscOutPort L_VENTS_1_AND_2_CLOSE_2_TM;
		DiscOutPort L_VENTS_1_AND_2_OPEN_1;
		DiscOutPort L_VENTS_1_AND_2_OPEN_1_TM;
		DiscOutPort L_VENTS_1_AND_2_OPEN_2;
		DiscOutPort L_VENTS_1_AND_2_OPEN_2_TM;
		DiscOutPort L_VENTS_1_AND_2_PURGE_1_IND_1;
		DiscOutPort L_VENTS_1_AND_2_PURGE_1_IND_1_TM;
		DiscOutPort L_VENTS_1_AND_2_PURGE_1_IND_2;
		DiscOutPort L_VENTS_1_AND_2_PURGE_1_IND_2_TM;

		DiscOutPort LH_VENT_3_CLOSE_1;
		DiscOutPort LH_VENT_3_CLOSE_1_TM;
		DiscOutPort LH_VENT_3_CLOSE_2;
		DiscOutPort LH_VENT_3_CLOSE_2_TM;
		DiscOutPort LH_VENT_3_OPEN_1;
		DiscOutPort LH_VENT_3_OPEN_1_TM;
		DiscOutPort LH_VENT_3_OPEN_2;
		DiscOutPort LH_VENT_3_OPEN_2_TM;

		DiscOutPort LH_VENTS_4_AND_7_CLOSE_1;
		DiscOutPort LH_VENTS_4_AND_7_CLOSE_1_TM;
		DiscOutPort LH_VENTS_4_AND_7_CLOSE_2;
		DiscOutPort LH_VENTS_4_AND_7_CLOSE_2_TM;
		DiscOutPort LH_VENTS_4_AND_7_OPEN_1;
		DiscOutPort LH_VENTS_4_AND_7_OPEN_1_TM;
		DiscOutPort LH_VENTS_4_AND_7_OPEN_2;
		DiscOutPort LH_VENTS_4_AND_7_OPEN_2_TM;

		DiscOutPort LH_VENT_5_CLOSE_1;
		DiscOutPort LH_VENT_5_CLOSE_1_TM;
		DiscOutPort LH_VENT_5_CLOSE_2;
		DiscOutPort LH_VENT_5_CLOSE_2_TM;
		DiscOutPort LH_VENT_5_OPEN_1;
		DiscOutPort LH_VENT_5_OPEN_1_TM;
		DiscOutPort LH_VENT_5_OPEN_2;
		DiscOutPort LH_VENT_5_OPEN_2_TM;

		DiscOutPort LH_VENT_6_CLOSE_1;
		DiscOutPort LH_VENT_6_CLOSE_1_TM;
		DiscOutPort LH_VENT_6_CLOSE_2;
		DiscOutPort LH_VENT_6_CLOSE_2_TM;
		DiscOutPort LH_VENT_6_OPEN_1;
		DiscOutPort LH_VENT_6_OPEN_1_TM;
		DiscOutPort LH_VENT_6_OPEN_2;
		DiscOutPort LH_VENT_6_OPEN_2_TM;

		DiscOutPort LH_VENT_6_PURGE_1_IND_1;
		DiscOutPort LH_VENT_6_PURGE_1_IND_1_TM;
		DiscOutPort LH_VENT_6_PURGE_1_IND_2;
		DiscOutPort LH_VENT_6_PURGE_1_IND_2_TM;
		DiscOutPort LH_VENT_6_PURGE_2_IND_1;
		DiscOutPort LH_VENT_6_PURGE_2_IND_1_TM;
		DiscOutPort LH_VENT_6_PURGE_2_IND_2;
		DiscOutPort LH_VENT_6_PURGE_2_IND_2_TM;

		DiscOutPort LH_VENTS_8_AND_9_CLOSE_1;
		DiscOutPort LH_VENTS_8_AND_9_CLOSE_1_TM;
		DiscOutPort LH_VENTS_8_AND_9_CLOSE_2;
		DiscOutPort LH_VENTS_8_AND_9_CLOSE_2_TM;
		DiscOutPort LH_VENTS_8_AND_9_OPEN_1;
		DiscOutPort LH_VENTS_8_AND_9_OPEN_1_TM;
		DiscOutPort LH_VENTS_8_AND_9_OPEN_2;
		DiscOutPort LH_VENTS_8_AND_9_OPEN_2_TM;
		DiscOutPort LH_VENTS_8_AND_9_PURGE_IND_1;
		DiscOutPort LH_VENTS_8_AND_9_PURGE_IND_1_TM;
		DiscOutPort LH_VENTS_8_AND_9_PURGE_IND_2;
		DiscOutPort LH_VENTS_8_AND_9_PURGE_IND_2_TM;

		DiscOutPort R_VENTS_1_AND_2_CLOSE_1;
		DiscOutPort R_VENTS_1_AND_2_CLOSE_1_TM;
		DiscOutPort R_VENTS_1_AND_2_CLOSE_2;
		DiscOutPort R_VENTS_1_AND_2_CLOSE_2_TM;
		DiscOutPort R_VENTS_1_AND_2_OPEN_1;
		DiscOutPort R_VENTS_1_AND_2_OPEN_1_TM;
		DiscOutPort R_VENTS_1_AND_2_OPEN_2;
		DiscOutPort R_VENTS_1_AND_2_OPEN_2_TM;
		DiscOutPort R_VENTS_1_AND_2_PURGE_1_IND_1;
		DiscOutPort R_VENTS_1_AND_2_PURGE_1_IND_1_TM;
		DiscOutPort R_VENTS_1_AND_2_PURGE_1_IND_2;
		DiscOutPort R_VENTS_1_AND_2_PURGE_1_IND_2_TM;

		DiscOutPort RH_VENT_3_CLOSE_1;
		DiscOutPort RH_VENT_3_CLOSE_1_TM;
		DiscOutPort RH_VENT_3_CLOSE_2;
		DiscOutPort RH_VENT_3_CLOSE_2_TM;
		DiscOutPort RH_VENT_3_OPEN_1;
		DiscOutPort RH_VENT_3_OPEN_1_TM;
		DiscOutPort RH_VENT_3_OPEN_2;
		DiscOutPort RH_VENT_3_OPEN_2_TM;

		DiscOutPort RH_VENTS_4_AND_7_CLOSE_1;
		DiscOutPort RH_VENTS_4_AND_7_CLOSE_1_TM;
		DiscOutPort RH_VENTS_4_AND_7_CLOSE_2;
		DiscOutPort RH_VENTS_4_AND_7_CLOSE_2_TM;
		DiscOutPort RH_VENTS_4_AND_7_OPEN_1;
		DiscOutPort RH_VENTS_4_AND_7_OPEN_1_TM;
		DiscOutPort RH_VENTS_4_AND_7_OPEN_2;
		DiscOutPort RH_VENTS_4_AND_7_OPEN_2_TM;

		DiscOutPort RH_VENT_5_CLOSE_1;
		DiscOutPort RH_VENT_5_CLOSE_1_TM;
		DiscOutPort RH_VENT_5_CLOSE_2;
		DiscOutPort RH_VENT_5_CLOSE_2_TM;
		DiscOutPort RH_VENT_5_OPEN_1;
		DiscOutPort RH_VENT_5_OPEN_1_TM;
		DiscOutPort RH_VENT_5_OPEN_2;
		DiscOutPort RH_VENT_5_OPEN_2_TM;

		DiscOutPort RH_VENT_6_CLOSE_1;
		DiscOutPort RH_VENT_6_CLOSE_1_TM;
		DiscOutPort RH_VENT_6_CLOSE_2;
		DiscOutPort RH_VENT_6_CLOSE_2_TM;
		DiscOutPort RH_VENT_6_OPEN_1;
		DiscOutPort RH_VENT_6_OPEN_1_TM;
		DiscOutPort RH_VENT_6_OPEN_2;
		DiscOutPort RH_VENT_6_OPEN_2_TM;

		DiscOutPort RH_VENT_6_PURGE_1_IND_1;
		DiscOutPort RH_VENT_6_PURGE_1_IND_1_TM;
		DiscOutPort RH_VENT_6_PURGE_1_IND_2;
		DiscOutPort RH_VENT_6_PURGE_1_IND_2_TM;
		DiscOutPort RH_VENT_6_PURGE_2_IND_1;
		DiscOutPort RH_VENT_6_PURGE_2_IND_1_TM;
		DiscOutPort RH_VENT_6_PURGE_2_IND_2;
		DiscOutPort RH_VENT_6_PURGE_2_IND_2_TM;

		DiscOutPort RH_VENTS_8_AND_9_CLOSE_1;
		DiscOutPort RH_VENTS_8_AND_9_CLOSE_1_TM;
		DiscOutPort RH_VENTS_8_AND_9_CLOSE_2;
		DiscOutPort RH_VENTS_8_AND_9_CLOSE_2_TM;
		DiscOutPort RH_VENTS_8_AND_9_OPEN_1;
		DiscOutPort RH_VENTS_8_AND_9_OPEN_1_TM;
		DiscOutPort RH_VENTS_8_AND_9_OPEN_2;
		DiscOutPort RH_VENTS_8_AND_9_OPEN_2_TM;
		DiscOutPort RH_VENTS_8_AND_9_PURGE_IND_1;
		DiscOutPort RH_VENTS_8_AND_9_PURGE_IND_1_TM;
		DiscOutPort RH_VENTS_8_AND_9_PURGE_IND_2;
		DiscOutPort RH_VENTS_8_AND_9_PURGE_IND_2_TM;


		void DefineAnimations( void );
		void SetIndications( void );
		void SetAnimations( void );

	public:
		VentDoors( AtlantisSubsystemDirector* _director, bool hasVentDoor47 );
		virtual ~VentDoors();

		void Realize( void ) override;
		bool SingleParamParseLine( void ) const override {return true;};
		bool OnParseLine( const char* line ) override;
		void OnSaveState( FILEHANDLE scn ) const override;
		void OnPostStep( double simt, double simdt, double mjd ) override;
};

#endif// _VENTDOORS_H_

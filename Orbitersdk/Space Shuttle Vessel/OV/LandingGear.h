/****************************************************************************
  This file is part of Space Shuttle Vessel

  Landing Gear subsystem definition


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
2020/03/29   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/02/16   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Landing Gear System definition



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
#ifndef __LANDINGGEAR_H_
#define __LANDINGGEAR_H_


#include "AtlantisSubsystem.h"
#include <discsignals.h>
#include <Orbitersdk.h>


using namespace discsignals;


/**
* @brief	Implementation of the Landing Gear subsystem, along with Brakes and Nosewheel Steering.
*
* This class handles the Landing Gear, Brakes and Nosewheel Steering physical implementation, responding to command signals and generating sensor data.
*/
class LandingGear:public AtlantisSubsystem
{
	friend class Atlantis;

	private:
		DiscInPort dipArm[2];
		DiscInPort dipDeploy[2];
		DiscInPort dipReset;
		DiscInPort dipBrakesMNA;
		DiscInPort dipBrakesMNB;
		DiscInPort dipBrakesMNC;
		DiscInPort dipAntiSkid;
		DiscInPort dipNWS1_CMPTR_CMD;
		DiscInPort dipNWS2_CMPTR_CMD;
		DiscInPort dipNWS1_ENABLE_A_CMD;
		DiscInPort dipNWS1_ENABLE_B_CMD;
		DiscInPort dipNWS2_ENABLE_A_CMD;
		DiscInPort dipNWS2_ENABLE_B_CMD;
		DiscInPort dipNWSMNA;
		DiscInPort dipNWSMNB;
		DiscInPort dipNWS1;
		DiscInPort dipNWS2;
		DiscInPort dipDDU2PowerSupply;
		DiscInPort dipNW_POSN_ERROR;

		DiscOutPort dopNLG_Door_Up;
		DiscOutPort dopNLG_Down;
		DiscOutPort dopLMG_Door_Up;
		DiscOutPort dopLMG_Down;
		DiscOutPort dopRMG_Door_Up;
		DiscOutPort dopRMG_Down;
		DiscOutPort dopNLG_NO_WOW;
		DiscOutPort dopLMG_NO_WOW;
		DiscOutPort dopRMG_NO_WOW;
		DiscOutPort dopArm[2];// HACK 2 signals due to ACAs
		DiscOutPort dopDown[2];// HACK 2 signals due to ACAs
		DiscOutPort dopAntiSkidFail;
		DiscOutPort dopNWS_POS_A;// -RH, +LH [-5.0v, +5.0v]
		DiscOutPort dopNWS_POS_B;// -RH, +LH [-5.0v, +5.0v]
		DiscOutPort dopNWS_POS_C;// -RH, +LH [-5.0v, +5.0v]
		DiscOutPort dopNWS1_ACT;
		DiscOutPort dopNWS2_ACT;
		DiscOutPort dopNWSFail;

		bool Arm;
		bool Down;

		// physical status
		double NLG;
		double LMG;
		double RMG;

		bool NLG_NoWOW;
		bool LMG_NoWOW;
		bool RMG_NoWOW;

		double NWSpos;// +RH, -LH [deg]

		UINT anim_nosegear;
		UINT anim_leftgear;
		UINT anim_rightgear;

		void AddAnimation( void );

		void Brakes( void );
		void NWS( double dt );
		void SetLandingGearPosition( void );
		void SetDigitals( void );

	public:
		explicit LandingGear( AtlantisSubsystemDirector* _director );
		~LandingGear( void );

		virtual bool SingleParamParseLine() const override {return true;};
		bool OnParseLine( const char* line ) override;
		void OnSaveState( FILEHANDLE scn ) const override;
		void Realize( void ) override;
		void OnPostStep( double simt, double simdt, double mjd ) override;
};


#endif// __LANDINGGEAR_H_s
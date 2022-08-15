/****************************************************************************
  This file is part of Space Shuttle Vessel

  Hydraulic Actuated Valve Definition


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
2020/05/10   GLS
2020/08/24   GLS
2021/08/24   GLS
2022/07/16   GLS
2022/08/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Hydraulic Actuated Valve Definition



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
#ifndef _g_HydraulicActuatedValve_H_
#define _g_HydraulicActuatedValve_H_


#include "PressureSource.h"
#include "DiscInPort.h"


using discsignals::DiscInPort;
using discsignals::DiscreteBundle;


// HACK no clue about right amounts
const double MIN_PRESS_CLOSE_HAV = 150;// psia
const double HE_USE_CLOSE_HAV = 20;// g


/**
 * @brief	Implementation of the HydraulicActuatedValve class.
 *
 * This class simulates a hydraulic actuated valve, that controls flow from
 * a PressureSource instance. Pneumatic closing capability is also provided.
 */
class HydraulicActuatedValve:public PressureSource
{
	private:
		DiscInPort dipServovalve[2];

		DiscInPort dipFailOperationalServoswitch[2];
		DiscInPort dipFailSafeServoswitch[2];

		DiscInPort dipHYD;

		PressureSource* PneumaticClose;

		double pos;
		double rate_hyd;
		double rate_pneu;

		double SequenceValveOpenPos;
	public:
		/**
		 * Returns valve position
		 * @return	valve position (range: 0 - closed, 1 - open)
		 */
		double GetPos( void ) const;

		/**
		 * Updates valve position (call from time step functions).
		 * @param	dt	sim dt
		 */
		void tmestp( double dt );

		/**
		 * Use from .scn loading function to set valve position.
		 * @param[in]	ipos	valve position (range: 0 - closed, 1 - open)
		 */
		void _backdoor( double ipos );

		/**
		 * Create a new valve.
		 * @param[in]	initpos	initial valve position (range: 0 - closed, 1 - open)
		 * @param[in]	rate_hyd	valve motion rate under hydraulic pressure
		 */
		HydraulicActuatedValve( double initpos, double rate_hyd );

		/**
		 * Create a new valve.
		 * @param[in]	initpos	initial valve position
		 * @param[in]	rate_hyd	valve motion rate under hydraulic pressure
		 * @param[in]	rate_pneu	valve motion rate under pneumatic pressure
		 * @param[in]	PneumaticClose	handle to PressureSource for pneumatic actuator close
		 * @param[in]	SequenceValveOpenPos	valve position at which the sequence valve opens
		 */
		HydraulicActuatedValve( double initpos, double rate_hyd, double rate_pneu, PressureSource* PneumaticClose, double SequenceValveOpenPos = 0 );
		~HydraulicActuatedValve( void );

		void Connect( DiscreteBundle* pBundle, DiscreteBundle* pBundleHYD );

		double Use( double flow, int source ) override;// HACK just for sequence valve
};


#endif// _g_HydraulicActuatedValve_H_

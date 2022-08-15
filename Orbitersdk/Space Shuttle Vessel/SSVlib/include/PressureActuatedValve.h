/****************************************************************************
  This file is part of Space Shuttle Vessel

  Pressure Actuated Valve Definition


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
2020/04/01   GLS
2020/04/15   GLS
2020/05/10   GLS
2020/08/24   GLS
2021/08/24   GLS
2022/07/16   GLS
2022/08/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Pressure Actuated Valve Definition



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
#ifndef _g_PressureActuatedValve_H_
#define _g_PressureActuatedValve_H_


#include "PressureSource.h"
#include "DiscOutPort.h"


using discsignals::DiscOutPort;
using discsignals::DiscreteBundle;


// HACK no clue about right amounts
const double MIN_PRESS_OPEN_PAV = 85;// psia
const double HE_USE_OPEN_PAV = 20;// g


/**
 * @brief	Implementation of the PressureActuatedValve class.
 *
 * This class simulates a pressure actuated valve, that controls flow from
 * a PressureSource instance. It can be one of 3 types: normally-closed,
 * normally-open and bistable.
 */
class PressureActuatedValve:public PressureSource
{
	private:
		DiscOutPort dopCLInd[2];
		DiscOutPort dopOPInd[2];

		PressureSource* OP;
		PressureSource* CL;
		PressureSource* psource;
		PressureSource* psourceinvent;

		double pos;
		double rate;
	public:
		/**
		 * Returns valve position.
		 * @return	valve position (range: 0 - closed, 1 - open)
		 */
		double GetPos( void ) const;

		/**
		 * Updates valve position. Must be called at every time step.
		 * @param[in]	dt	sim dt
		 */
		void tmestp( double dt );

		/**
		 * Use from .scn loading function to set valve position.
		 * @param[in]	ipos	valve position (range: 0 - closed, 1 - open).
		 */
		void _backdoor( double ipos );

		/**
		 * Class constructor. PressureSource parameters control valve type.
		 * @param[in]	initpos	initial valve position (range: 0 - closed, 1 - open)
		 * @param[in]	imaxrate	maximum valve motion rate
		 * @param[in]	OP	pressure source to open the valve (nullptr if valve is normally-open)
		 * @param[in]	CL	pressure source to close the valve (nullptr if valve is normally-closed)
		 * @param[in]	psource	pressure source to be controlled by the valve
		 * @param[in]	psourceinvent	pressure source "in the vent", used to open the valve (nullptr is not applicable)
		 */
		PressureActuatedValve( double initpos, double rate, PressureSource* OP, PressureSource* CL, PressureSource* psource, PressureSource* psourceinvent );
		~PressureActuatedValve( void );

		/**
		 * Used to connect valve position indicators.
		 * @param[in]	openind	chooses between open position or closed position indicator.
		 * @param[in]	output	chooses which of the 2 position indicator to connect
		 * @param[in]	pBundle	handle to discrete bundle
		 * @param[in]	iLine	line number in discrete bundle
		 */
		void ConnectIndication( bool openind, unsigned short output, DiscreteBundle* pBundle, unsigned short iLine );

		/**
		 * Used to set pressure sources when they are unavailable for the constructor.
		 * @param[in]	OP	pressure source to open the valve (nullptr if valve is normally-open)
		 * @param[in]	CL	pressure source to close the valve (nullptr if valve is normally-closed)
		 * @param[in]	psource	pressure source to be controlled by the valve
		 * @param[in]	psourceinvent	pressure source "in the vent", used to open the valve (nullptr is not applicable)
		 */
		void SetPressureSources( PressureSource* OP, PressureSource* CL, PressureSource* psource, PressureSource* psourceinvent );

		double Use( double flow, int source ) override;
};


#endif// _g_PressureActuatedValve_H_

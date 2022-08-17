/****************************************************************************
  This file is part of Space Shuttle Vessel

  Motor Valve Definition


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
#ifndef _g_MotorValve_H_
#define _g_MotorValve_H_


#include "BasicValve.h"
#include "PressureSource.h"
#include "DiscInPort.h"
#include "DiscOutPort.h"


using namespace discsignals;


class MotorValve:public BasicValve, public PressureSource
{
	private:
		DiscInPort dipInput;
		DiscOutPort dopPosOP[2];
		DiscOutPort dopPosCL[2];
		PressureSource* psource;
		PressureSource* psourceinvent;

	public:
		void OnPostStep( double fSimT, double fDeltaT, double fMJD );

		/**
		 * Creates a new valve.
		 * @param[in]	initpos	initial valve position (range: 0 - closed, 1 - open)
		 * @param[in]	imaxrate	maximum valve motion rate [%/sec]
		 * @param[in]	psource	pressure source to be controlled by the valve
		 * @param[in]	psourceinvent	pressure source "in the vent", used to open the valve (nullptr is not applicable)
		 */
		MotorValve( const string& name, double initpos, double rate, PressureSource* psource, PressureSource* psourceinvent );
		~MotorValve( void );

		/**
		 * Connects the valve to the specified discrete bundle at the specified line.
		 * @param[in]	pBundle	handle to discrete bundle
		 * @param[in]	iLine	line number in discrete bundle
		 */
		void ConnectInput( DiscreteBundle* pBundle, int iLine );

		/**
		 * Connects on of the valve position sensors to the specified discrete bundle at the specified line.
		 * @param[in]	output	chooses which of the 2 valve position sensors to connect
		 * @param[in]	open	chooses if the output to connect refers to open or close
		 * @param[in]	pBundle	handle to discrete bundle
		 * @param[in]	iLine	line number in discrete bundle
		 */
		void ConnectPositionSensor( unsigned int output, bool open, DiscreteBundle* pBundle, int iLine );

		double Use( double flow, int source ) override;
};


#endif// _g_MotorValve_H_

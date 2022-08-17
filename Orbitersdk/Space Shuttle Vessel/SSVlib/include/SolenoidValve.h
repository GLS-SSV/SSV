/****************************************************************************
  This file is part of Space Shuttle Vessel

  Solenoid Valve Definition


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
2020/04/15   GLS
2020/05/10   GLS
2020/08/24   GLS
2021/08/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/07/16   GLS
2022/08/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Solenoid Valve Definition



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
#ifndef _g_SolenoidValve_H_
#define _g_SolenoidValve_H_


#include "BasicValve.h"
#include "PressureSource.h"
#include "DiscInPort.h"
#include "DiscOutPort.h"


using namespace discsignals;


/**
 * @brief	Implementation of the SolenoidValve class.
 *
 * This class simulates a solenoid valve, that controls flow from a
 * PressureSource instance. It can be one of 2 types: normally-closed
 * or normally-open. The valve is controlled via discrete line.
 */
class SolenoidValve:public PressureSource
{
	private:
		DiscInPort dipInput[2];
		PressureSource* psource;
		PressureSource* psourceinvent;

		bool NormallyClosed;

		double pos;
		double rate;
	public:
		/**
		 * Returns valve position.
		 * @return	valve	position (range: 0 - closed, 1 - open)
		 */
		double GetPos( void ) const;

		/**
		 * Updates valve position. Must be called at every time step.
		 * @param[in]	dt	sim dt
		 */
		void tmestp( double dt );

		/**
		 * Use from .scn loading function to set valve position.
		 * @param[in]	ipos	valve position (range: 0 - closed, 1 - open)
		 */
		void _backdoor( double ipos );

		/**
		 * Creates a new valve.
		 * @param[in]	initpos	initial valve position (range: 0 - closed, 1 - open)
		 * @param[in]	imaxrate	maximum valve motion rate [%/sec]
		 * @param[in]	NormallyClosed	indicates if valve is normally-closed
		 * @param[in]	psource	pressure source to be controlled by the valve
		 * @param[in]	psourceinvent	pressure source "in the vent", used to open the valve (nullptr is not applicable)
		 */
		SolenoidValve( double initpos, double rate, bool NormallyClosed, PressureSource* psource, PressureSource* psourceinvent );
		~SolenoidValve( void );

		/**
		 * Connects the valve to the specified discrete bundle at the specified line.
		 * @param[in]	input	chooses which of the 2 valve inputs to connect
		 * @param[in]	pBundle	handle to discrete bundle
		 * @param[in]	iLine	line number in discrete bundle
		 */
		void Connect( unsigned short input, DiscreteBundle* pBundle, unsigned short iLine );

		double Use( double flow, int source ) override;
};


class SolenoidValve_2:public BasicValve, public PressureSource
{
	private:
		DiscInPort dipInput[2];
		DiscOutPort dopPosOP[2];
		DiscOutPort dopPosCL[2];
		PressureSource* psource;
		PressureSource* psourceinvent;

		bool NormallyClosed;

	public:
		void OnPostStep( double simt, double simdt, double mjd ) override;

		/**
		 * Creates a new valve.
		 * @param[in]	initpos	initial valve position (range: 0 - closed, 1 - open)
		 * @param[in]	imaxrate	maximum valve motion rate [%/sec]
		 * @param[in]	NormallyClosed	indicates if valve is normally-closed
		 * @param[in]	psource	pressure source to be controlled by the valve
		 * @param[in]	psourceinvent	pressure source "in the vent", used to open the valve (nullptr is not applicable)
		 */
		SolenoidValve_2( const string& name, double initpos, double rate, bool NormallyClosed, PressureSource* psource, PressureSource* psourceinvent );
		~SolenoidValve_2( void );

		/**
		 * Connects the valve to the specified discrete bundle at the specified line.
		 * @param[in]	input	chooses which of the 2 valve inputs to connect
		 * @param[in]	pBundle	handle to discrete bundle
		 * @param[in]	iLine	line number in discrete bundle
		 */
		void ConnectInput( unsigned short input, DiscreteBundle* pBundle, unsigned short iLine );

		/**
		 * Connects on of the valve position sensors to the specified discrete bundle at the specified line.
		 * @param[in]	output	chooses which of the 2 valve position sensors to connect
		 * @param[in]	open	chooses if the output to connect refers to open or close
		 * @param[in]	pBundle	handle to discrete bundle
		 * @param[in]	iLine	line number in discrete bundle
		 */
		void ConnectPositionSensor( unsigned short output, bool open, DiscreteBundle* pBundle, unsigned short iLine );

		double Use( double flow, int source ) override;
};


class SolenoidLatchingValve:public BasicValve, public PressureSource
{
	private:
		DiscInPort dipInputOP[2];
		DiscInPort dipInputCL[2];
		DiscOutPort dopPosOP[2];
		DiscOutPort dopPosCL[2];
		PressureSource* psource;
		PressureSource* psourceinvent;

	public:
		void OnPostStep( double simt, double simdt, double mjd ) override;

		/**
		 * Creates a new valve.
		 * @param[in]	initpos	initial valve position (range: 0 - closed, 1 - open)
		 * @param[in]	imaxrate	maximum valve motion rate [%/sec]
		 * @param[in]	psource	pressure source to be controlled by the valve
		 * @param[in]	psourceinvent	pressure source "in the vent", used to open the valve (nullptr is not applicable)
		 */
		SolenoidLatchingValve( const string& name, double initpos, double rate, PressureSource* psource, PressureSource* psourceinvent );
		~SolenoidLatchingValve( void );

		/**
		 * Connects the valve to the specified discrete bundle at the specified line.
		 * @param[in]	input	chooses which of the 2 valve inputs to connect
		 * @param[in]	open	chooses if the input to connect refers to open or close
		 * @param[in]	pBundle	handle to discrete bundle
		 * @param[in]	iLine	line number in discrete bundle
		 */
		void ConnectInput( unsigned short input, bool open, DiscreteBundle* pBundle, unsigned short iLine );

		/**
		 * Connects on of the valve position sensors to the specified discrete bundle at the specified line.
		 * @param[in]	output	chooses which of the 2 valve position sensors to connect
		 * @param[in]	open	chooses if the output to connect refers to open or close
		 * @param[in]	pBundle	handle to discrete bundle
		 * @param[in]	iLine	line number in discrete bundle
		 */
		void ConnectPositionSensor( unsigned short output, bool open, DiscreteBundle* pBundle, unsigned short iLine );

		double Use( double flow, int source ) override;
};


#endif// _g_SolenoidValve_H_

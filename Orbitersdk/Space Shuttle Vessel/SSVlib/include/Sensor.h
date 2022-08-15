/****************************************************************************
  This file is part of Space Shuttle Vessel

  Sensor Definition


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
2020/08/24   GLS
2021/08/24   GLS
2022/07/16   GLS
2022/08/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Sensor Definition



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
#ifndef _g_Sensor_H_
#define _g_Sensor_H_


#include "DiscOutPort.h"


using discsignals::DiscOutPort;
using discsignals::DiscreteBundle;


/**
 * @brief	Implementation of the Sensor class.
 *
 * This class simulates a sensor, receiving input data and converting it to
 * a value from 0 to 5, and then sending it thru a discrete line. Minimum and
 * maximum input values are specified as constructor arguments. The output is
 * 0 for input values equal or less than MinValue, 5 for input values equal or
 * greater than MaxValue, and varies linearly between 0 and 5 for input values
 * between MinValue and MaxValue.
 */
class Sensor
{
	private:
		DiscOutPort dipOutput;

		double conversor;
		double error;

		double MaxValue;
		double MinValue;
	public:
		Sensor( double MinValue = 0.0, double MaxValue = 5000.0, double FSerror = 0.0 );
		~Sensor( void );

		/**
		 * Connects the sensor to the specified discrete bundle at the specified line.
		 * @param[in]	pBundle	handle to discrete bundle
		 * @param[in]	iLine	line number in discrete bundle
		 */
		void Connect( DiscreteBundle* pBundle, unsigned short iLine );

		/**
		 * Disconnects sensor from discrete bundle.
		 */
		void Disconnect( void );

		/**
		 * Sets the sensor input.
		 * @param[in]	value	sensor input
		 */
		void SetValue( double value );
};


#endif// _g_Sensor_H_

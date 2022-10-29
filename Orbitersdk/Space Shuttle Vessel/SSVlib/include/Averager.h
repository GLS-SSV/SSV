/****************************************************************************
  This file is part of Space Shuttle Vessel

  Avereger definition


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
2020/08/24   GLS
2021/08/03   GLS
2021/08/24   GLS
2022/07/16   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#ifndef _AVERAGER_H_
#define _AVERAGER_H_


#include <queue>

class Averager
{
	std::queue<double> previousValues;
	std::queue<double> previousTimestamps;
	double sum;
	double timeLimit;
	//unsigned int sizeLimit;
public:
	/**
	 * \param sampleSize (maxmimum) number of samples to average
	 */
	//Averager(unsigned int sampleSize);
	/**
	 * \param minTime minimum time (seconds) to average over
	 */
	explicit Averager(double minTime);
	~Averager();

	//void NewValue(double val);
	void NewValue(double val, double timestamp);
	double GetAvgValue() const;
};

#endif// _AVERAGER_H_

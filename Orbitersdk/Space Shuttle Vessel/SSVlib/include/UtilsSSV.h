/****************************************************************************
  This file is part of Space Shuttle Vessel

  Miscellaneous utilty functions


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
2020/08/24   GLS
2021/08/24   GLS
2022/07/16   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Miscellaneous utilty functions



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
#ifndef UTILSSSV_H_20C109CD_EC79_4414_9D5F_306162F99156
#define UTILSSSV_H_20C109CD_EC79_4414_9D5F_306162F99156
#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <Orbitersdk.h>


/**
 * Reads line containing multiple values, separated by commas, into std::vector.
 * \param line string contaning comma-separated values
 * \param data vector which will be filled with data from line
 */
template <typename T>
void ReadCSVLine(const std::string &line, std::vector<T> &data)
{
	data.clear(); // empty vector before adding data
	std::istringstream inputStream(line);
	while(!inputStream.eof()) {
		T value;
		inputStream>>value;
		data.push_back(value);
		inputStream.ignore(1, ',');
	}
}


double CalculateThrustPower( VESSEL* v, const VECTOR3& vtx_lt, const VECTOR3& vtx_rt, const VECTOR3& vtx_lb, const VECTOR3& vtx_rb );


double GetMassAndCoGOfAttachedObject( VESSEL* vp, ATTACHMENTHANDLE ah, VECTOR3& CoG );

/**
 * Computes mass and CoG of vessel, including attached payload
 * Return mass and CoG in local reference frame of vessel
 */
double GetMassAndCoG( VESSEL* v, VECTOR3& CoG );

#endif // UTILSSSV_H_20C109CD_EC79_4414_9D5F_306162F99156

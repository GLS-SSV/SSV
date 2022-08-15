/****************************************************************************
  This file is part of Space Shuttle Vessel

  Discrete line bundle definition


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
2020/05/08   GLS
2020/05/10   GLS
2020/08/24   GLS
2021/08/24   GLS
2022/07/16   GLS
2022/08/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Discrete line bundle definition



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
#if !defined(AFX_DISCRETEBUNDLE_H__A928D10B_004B_495D_87CD_3A0309B3EFDA__INCLUDED_)
#define AFX_DISCRETEBUNDLE_H__A928D10B_004B_495D_87CD_3A0309B3EFDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

namespace discsignals
{
	using namespace std;

	class DiscretePort;

/**
 * class for handling multiple discrete data lines or analog inputs
 * State for each discrete can be -28V to +28V
 * One bundle can have up to 16 lines.
 * one line has a beginning and a end point.
 * 0 = ground (GND)
 */
class DiscreteBundle
{
	string ident;
	unsigned short snLines;
	float fState;
	float fLines[16];
	/**
	 * Indicate that a line is broken and does always return 0V.
	 */
	bool bBrokenLine[16];
public:
	explicit DiscreteBundle(const string& _ident, unsigned short nLines = 16);
	virtual ~DiscreteBundle();

	unsigned short CountLines() const throw();
	/**
	 * Set the mode how the Discrete bundle class handles logging information
	 */
	void SetLogMode(short iMode);
	float GetVoltage(unsigned short iIndex) const;
	const string& GetIdentity() const;
	void SetDiscrete(unsigned short iIndex, float fVoltage);
};

};

#endif // !defined(AFX_DISCRETEBUNDLE_H__A928D10B_004B_495D_87CD_3A0309B3EFDA__INCLUDED_)

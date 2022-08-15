/****************************************************************************
  This file is part of Space Shuttle Vessel

  Basic switch VC Component definition


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
2020/03/20   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/08/24   GLS
2021/12/26   GLS
2022/08/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Basic switch VC Component definition



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
#if !defined(AFX_BASICSWITCH_H__3790BCEE_A9B9_492A_A7F4_B0DA5E454AFB__INCLUDED_)
#define AFX_BASICSWITCH_H__3790BCEE_A9B9_492A_A7F4_B0DA5E454AFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AtlantisVCComponent.h"
#include <vector>
#include <string>

namespace vc {

using namespace std;

class BasicSwitch : public AtlantisVCComponent
{
protected:
	UINT grpIndex;
	bool bOrientation;
	bool bSpringLoaded;
	unsigned short usNumPositions;
	vector<string> labels;
	vector<bool> vbSpringLoaded;
	unsigned short usCurrentPosition;
	int switchSound; // if zero, don't play sound
public:
	/**
	 * \param usNumPositions number of switch positions
	 * \param _ident identifying string (i.e. switch name)
	 * \param switchSoundID ID of sound to play when switch changes position (if 0, no sound is played)
	 */
	BasicSwitch(Atlantis* _sts, unsigned short usNumPositions, const string& _ident, int switchSoundID=0);
	virtual ~BasicSwitch();

	void DefineGroup( UINT _grpIndex );

	void SetLabel(unsigned short iPosition, const string& _label);
	/**
	* Sets initial position of switch
	* If used, it has to be called as early as possible so it doesn't overwrite scenario entry.
	*/
	void SetInitialPosition(unsigned short usPos);
	void SetOrientation(bool bHorizontal);
	/**
	 * Fully spring loaded switch
	 */
	void SetSpringLoaded(bool IsSpringLoaded);
	/**
	 * Set a single switch position to be spring loaded
	 */
	void SetSpringLoaded(bool IsSpringLoaded, unsigned short usPos);

	/**
	 * Returns true if the switch has more than one non-spring loaded position.
	 */
	bool IsFullySpringLoaded( void );

	void DefineVCAnimations(UINT vc_idx) override;
	bool GetStateString(unsigned long ulBufferSize, char* pszBuffer) override;

	bool OnMouseEvent(int _event, float x, float y) override;

	bool OnParseLine(const char* line) override;
	virtual void OnPositionUp();
	virtual void OnPositionDown();
	virtual void OnPositionChange(unsigned short usNewPosition);

	void OnSaveState(FILEHANDLE scn) const override;

};

};

#endif // !defined(AFX_BASICSWITCH_H__3790BCEE_A9B9_492A_A7F4_B0DA5E454AFB__INCLUDED_)

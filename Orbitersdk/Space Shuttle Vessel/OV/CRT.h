/****************************************************************************
  This file is part of Space Shuttle Vessel

  CRT definition



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
2020/04/07   GLS
2020/05/08   GLS
2020/06/20   GLS
2021/06/03   GLS
2021/06/06   GLS
2021/08/03   GLS
2021/08/24   GLS
2021/12/26   GLS
2022/09/29   GLS
********************************************/

#ifndef __CRT_H
#define __CRT_H


#include <Orbitersdk.h>


namespace vc
{
	class MDU;
}

class CRT: public MFD2
{
	//friend class Atlantis;
public:
	CRT( DWORD w, DWORD h, VESSEL *vessel, int MDUID );
	~CRT ();
	char *ButtonLabel (int bt) override;
	int ButtonMenu (const MFDBUTTONMENU **menu) const override;
	bool ConsumeKeyBuffered (DWORD key) override;
	bool ConsumeButton (int bt, int event) override;
	bool Update( oapi::Sketchpad* skp ) override;
	static OAPI_MSGTYPE MsgProc (UINT msg, UINT mfd, WPARAM wparam, LPARAM lparam);

	vc::MDU* mdu;

private:
	int MDUID;
};

#endif // !__CRT_H

/****************************************************************************
  This file is part of Space Shuttle Vessel

  Basic discrete I/O port definition


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
2021/08/23   GLS
2021/08/24   GLS
2022/07/16   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/10/09   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Basic discrete I/O port definition



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
#ifndef _DISCRETEPORT_H_
#define _DISCRETEPORT_H_


namespace discsignals
{

class DiscreteBundle;

class DiscretePort
{
protected:
	DiscreteBundle* pBundle;
	unsigned short usLine;
public:
	virtual bool Connect(DiscreteBundle* pBundle, unsigned short iLine);
	bool Disconnect();
	bool IsConnected( void ) const;
	DiscretePort();
	DiscretePort(DiscreteBundle* pBundle, unsigned short iLine);
	virtual ~DiscretePort();
};

class DiscMultiplex {
public:
	DiscMultiplex();
	virtual ~DiscMultiplex();
	virtual void Propagate(double simt, double simdt, double mjd);
};

}

#endif// _DISCRETEPORT_H_

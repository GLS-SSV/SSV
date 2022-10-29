/****************************************************************************
  This file is part of Space Shuttle Vessel

  Pad-to-MLP Interface definition


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
2020/06/20   GLS
2021/08/24   GLS
2021/12/25   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Pad-to-MLP Interface definition



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
#ifndef PADMLPIF
#define PADMLPIF


class PadMLPInterface
{
	public:
		virtual ~PadMLPInterface() {};

		// to MLP
		virtual void FireSSMEH2BurnPICs( void ) = 0;

		// to SSV
		virtual void SetGMTLO( double GMTLO ) = 0;
		virtual void SetGMTLOSetCommandFlag( bool val ) = 0;
		virtual void SetLPSCountdownHoldFlag( bool val ) = 0;
		virtual void SetLPSGoForAutoSequenceStartFlag( bool val ) = 0;
		virtual void SetLPSGoForEngineStartFlag( bool val ) = 0;
		virtual void SetResumeCountCommandFlag( bool val ) = 0;
		virtual bool GetRSCountdownHoldFlag( void ) = 0;
		virtual bool GetLaunchSequenceAbortFlag( void ) = 0;
		virtual void PSN4( void ) = 0;
		virtual double GetHydSysPress( int sys ) = 0;
		virtual int GetHeTankPress( int sys ) = 0;
		virtual int GetHeRegPress( int sys ) = 0;
		virtual void HeFillTank( int sys, double mass ) = 0;
		virtual void SetSSMEActPos( int num, double Ppos, double Ypos ) = 0;
		virtual unsigned int GetHoldFlags( void ) = 0;
};

#endif// PADMLPIF

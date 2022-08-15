/****************************************************************************
  This file is part of Space Shuttle Vessel

  T0 Umbilical Reference definition


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
2020/05/08   GLS
2020/06/20   GLS
2021/07/03   GLS
2021/08/24   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  T0 Umbilical Reference definition



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
#ifndef T0UMBREF
#define T0UMBREF


#include "T0UmbilicalMLPInterface.h"


class Atlantis;


class T0UmbilicalReference
{
	private:
		Atlantis* sts;
		T0UmbilicalMLPInterface* T0Umb;
		bool T0UmbilicalConnected;

	public:
		explicit T0UmbilicalReference( Atlantis* sts );
		virtual ~T0UmbilicalReference( void );

		void Connect( void );
		void Connect( T0UmbilicalMLPInterface* ref );

		// from MLP to OV
		virtual void SetGMTLO( double GMTLO );
		virtual void SetGMTLOSetCommandFlag( bool val );
		virtual void SetLPSCountdownHoldFlag( bool val );
		virtual void SetLPSGoForAutoSequenceStartFlag( bool val );
		virtual void SetLPSGoForEngineStartFlag( bool val );
		virtual void SetResumeCountCommandFlag( bool val );
		virtual bool GetRSCountdownHoldFlag( void );
		virtual bool GetLaunchSequenceAbortFlag( void );
		virtual void PSN4( void );
		virtual double GetHydSysPress( int sys );
		virtual int GetHeTankPress( int sys );
		virtual int GetHeRegPress( int sys );
		virtual void HeFillTank( int sys, double mass );
		virtual void SetSSMEActPos( int num, double Ppos, double Ypos );
		virtual unsigned int GetHoldFlags( void );

		// from OV to MLP
		void FireHDPPICs( void );
		void FireT0UmbilicalPICs( void );
};

#endif// T0UMBREF
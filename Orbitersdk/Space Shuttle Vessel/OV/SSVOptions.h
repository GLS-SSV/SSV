/****************************************************************************
  This file is part of Space Shuttle Vessel

  SSV Options definition


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
2020/05/01   GLS
2020/06/20   GLS
2020/06/21   GLS
2021/07/03   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/10/06   GLS
2022/10/07   GLS
********************************************/
#ifndef SSV_OPTIONS
#define SSV_OPTIONS


#include <OrbiterAPI.h>
#include <string>
#include "ParameterValues.h"


class SSVOptions
{
	private:
		bool bEIUDataRecorder;
		unsigned short usPositionLabelTime;
		bool bAutoActionLandingGear;
		bool bAutoActionDragChute;
		double dRHCRate;
		double dRPTARate;
		double dBrakeRate;

	public:
		SSVOptions(void):
			bEIUDataRecorder(false), usPositionLabelTime(3), bAutoActionLandingGear(true), bAutoActionDragChute(true), dRHCRate(RHC_RATE), dRPTARate(RPTA_RATE), dBrakeRate(BRAKE_RATE)
		{
		}

		virtual ~SSVOptions( void )
		{
		}

		void Parse( FILEHANDLE cfg )
		{
			int tmp = 0;

			oapiReadItem_bool( cfg, "EIUDataRecorder", bEIUDataRecorder );

			oapiReadItem_int( cfg, "PositionLabelTime", tmp );
			if ((tmp >= 0) && (tmp <= 60)) usPositionLabelTime = tmp;

			oapiReadItem_bool( cfg, "AutoActionLandingGear", bAutoActionLandingGear );

			oapiReadItem_bool( cfg, "AutoActionDragChute", bAutoActionDragChute );

			oapiReadItem_float( cfg, "RHCRate", dRHCRate );

			oapiReadItem_float( cfg, "RPTARate", dRPTARate );
			
			oapiReadItem_float( cfg, "BrakeRate", dBrakeRate );
			return;
		}

		bool EIUDataRecorder( void ) const
		{
			return bEIUDataRecorder;
		}

		unsigned short PositionLabelTime( void ) const
		{
			return usPositionLabelTime;
		}

		bool AutoActionLandingGear( void ) const
		{
			return bAutoActionLandingGear;
		}

		bool AutoActionDragChute( void ) const
		{
			return bAutoActionDragChute;
		}

		double RHCRate( void ) const
		{
			return dRHCRate;
		}

		double RPTARate( void ) const
		{
			return dRPTARate;
		}

		double BrakeRate( void ) const
		{
			return dBrakeRate;
		}
};

#endif// SSV_OPTIONS

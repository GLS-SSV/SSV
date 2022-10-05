/****************************************************************************
  This file is part of Space Shuttle Vessel

  Space Shuttle Main Engine Block II subsystem definition


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
2020/04/01   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/06/06   GLS
2021/07/03   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/23   GLS
2021/12/30   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Space Shuttle Main Engine Block II definition



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
#ifndef _mps_SSME_BLOCK_II_H_
#define _mps_SSME_BLOCK_II_H_


#include "SSME.h"
#include "../AtlantisSubsystem.h"
#include <Sensor.h>


namespace mps
{
	using namespace discsignals;


	class SSME_BLOCK_II:public SSME
	{
		private:
			// vars for RUN2
			double posMOV;
			double posMFV;

			double IMSLHeUsage;

			Sensor Sensor_Press[22];
			Sensor Sensor_Temp[16];
			Sensor Sensor_Flow[4];
			Sensor Sensor_Speed[4];

		public:
			SSME_BLOCK_II( AtlantisSubsystemDirector* _director, const string& _ident, unsigned short nID, int controllertype, const string& sw, HeSysEng* HeSys );
			~SSME_BLOCK_II( void );

			void RUN1( double time, double dt ) override;// pre-start
			void RUN2( double time, double dt ) override;// ignition
			void RUN3( double time, double dt ) override;// mainstage
			void RUN4( double time, double dt ) override;// cutoff
			void RUN5( double time, double dt ) override;// post-shutdown

			void ConnectSensors( DiscreteBundle* IEchA_Press, DiscreteBundle* IEchB_Press, DiscreteBundle* IEchA_Temp, DiscreteBundle* IEchB_Temp, DiscreteBundle* IEchA_Flow, DiscreteBundle* IEchB_Flow, DiscreteBundle* IEchA_Speed, DiscreteBundle* IEchB_Speed ) override;

			void OnSaveState( FILEHANDLE scn ) const override;
			bool OnParseLine( const char* line ) override;

			double GetSubsystemMass( void ) const override;
			bool GetSubsystemCoG( VECTOR3& CoG ) const override;
	};
}


#endif// _mps_SSME_BLOCK_II_H_

/****************************************************************************
  This file is part of Space Shuttle Vessel

  Air Data Probes subsystem definition


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
2020/10/11   GLS
2020/11/10   GLS
2021/05/30   GLS
2021/06/09   GLS
2021/06/10   GLS
2021/06/11   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
********************************************/
#ifndef _AIRDATAPROBE_H_
#define _AIRDATAPROBE_H_


#include "AtlantisSubsystem.h"
#include <discsignals.h>


using namespace discsignals;

class AirDataProbes : public AtlantisSubsystem
{
	public:
		explicit AirDataProbes( AtlantisSubsystemDirector* _director );
		virtual ~AirDataProbes();

		void OnPreStep( double simt, double simdt, double mjd ) override;

		void Realize( void ) override;

		bool OnParseLine( const char* line ) override;
		void OnSaveState( FILEHANDLE scn ) const override;
		bool SingleParamParseLine() const override {return true;};
	private:

		void AddAnimation( void );

		UINT animleft;
		UINT animright;

		double posleft;// 0 = stowed; 1 = deployed
		double posright;// 0 = stowed; 1 = deployed

		DiscOutPort L_ADP_STOW_1;
		DiscOutPort L_ADP_DEPLOY_1;
		DiscInPort LEFT_PROBE_MOTOR_1_PWR;
		DiscOutPort L_ADP_STOW_2;
		DiscOutPort L_ADP_DEPLOY_2;
		DiscInPort LEFT_PROBE_MOTOR_2_PWR;
		DiscOutPort R_ADP_STOW_1;
		DiscOutPort R_ADP_DEPLOY_1;
		DiscInPort RIGHT_PROBE_MOTOR_1_PWR;
		DiscOutPort R_ADP_STOW_2;
		DiscOutPort R_ADP_DEPLOY_2;
		DiscInPort RIGHT_PROBE_MOTOR_2_PWR;
};

#endif// _AIRDATAPROBE_H_

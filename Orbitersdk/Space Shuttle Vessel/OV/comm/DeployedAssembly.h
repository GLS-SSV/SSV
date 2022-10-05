/****************************************************************************
  This file is part of Space Shuttle Vessel

  Deployed Assembly subsystem definition


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
2020/04/01   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/02/16   GLS
2021/06/06   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Deployed Assembly definition



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

#ifndef _comm_DA_H_
#define _comm_DA_H_


#include <Orbitersdk.h>
#include <discsignals.h>
#include "../AtlantisSubsystem.h"


using namespace discsignals;


namespace comm
{
	// no clue what the real values are for the locking pins
	inline constexpr double LOCKINGPIN1_SPEED = 0.071429;// 1/sec
	inline constexpr double LOCKINGPIN2_SPEED = 0.142857;// 1/sec

	inline constexpr double ALPHA_MASTER_PULSE_INDEX = 116.5;// deg
	inline constexpr double BETA_MASTER_PULSE_INDEX = -23.25;// deg

	/**
	 * Structural and mechanical model of the deployed assembly.
	 */
	class DeployedAssembly:public AtlantisSubsystem
	{
			double alpha;
			double beta;
			double LockingPin1;
			double LockingPin2;

			DiscOutPort BoomStowEnableII;
			DiscOutPort AlphaMIP;
			DiscOutPort BetaMIP;
			DiscInPort GimbalLockMotors;
			DiscInPort GimbalMotorAlpha;
			DiscInPort GimbalMotorBeta;
			DiscOutPort AlphaEncoder;
			DiscOutPort BetaEncoder;

			MESHHANDLE hMesh;
			UINT mesh_idx;

			UINT anim_kualpha;
			UINT anim_kubeta;

			void AddAnimation( void );
			void AddMesh( void );
			void SetKuGimbalAngles( void );

		public:
			explicit DeployedAssembly( AtlantisSubsystemDirector* _director );
			virtual ~DeployedAssembly();

			void Realize( void ) override;
			void OnPostStep( double simt, double simdt, double mjd ) override;

			bool SingleParamParseLine() const override {return true;};
			bool OnParseLine( const char* line ) override;
			void OnSaveState( FILEHANDLE scn ) const override;
	};

}

#endif// _comm_DA_H_

/****************************************************************************
  This file is part of Space Shuttle Vessel

  Active Latch Group subsystem definition


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
2020/05/10   GLS
2020/06/20   GLS
2020/06/25   GLS
2020/06/26   GLS
2020/06/28   GLS
2020/08/23   GLS
2020/08/27   GLS
2020/09/04   GLS
2020/09/20   GLS
2021/06/06   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/21   GLS
2022/09/29   GLS
2022/10/30   GLS
2022/11/09   GLS
2022/11/12   GLS
2023/07/25   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Latch definition



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
#ifndef __ACTIVELATCHGROUP_H
#define __ACTIVELATCHGROUP_H


#include "Latch.h"
#include <vector>
#include "mission/Mission.h"
#include <VesselAPI.h>
#include <discsignals.h>


using namespace discsignals;

/**
 * Class for PLB latches that can be operated on-orbit
 */
class ActiveLatchGroup : public LatchSystem
{
	public:
		ActiveLatchGroup( AtlantisSubsystemDirector *_director, const std::string &_ident, unsigned short id, const struct mission::MissionPayloads& payloads );
		virtual ~ActiveLatchGroup();

		void OnPreStep( double simt, double simdt, double mjd ) override;
		void Realize( void ) override;

		bool OnParseLine( const char* line ) override;
		void OnSaveState( FILEHANDLE scn ) const override;

		void CreateAttachment( void ) override;

	protected:
		void OnAttach( void ) override;
		void OnDetach( void ) override;

	private:
		bool CheckRFL( void ) const;

		/**
		 * Checks if all latches are open enough for payload release, i.e., >= 50%.
		 */
		bool AllLatchesOpen( void ) const;

		void LoadPayload( void );

		unsigned short id;

		VECTOR3 attachpos;

		struct mission::MissionPayloads payloads;

		/**
		* Previous latch state, true if open.
		*/
		bool PrevLatchState;

		bool LatchInstalled[12];
		double LatchState[12];// 0 = closed; 1 = open
		unsigned short PL_Sys[12];
		unsigned short PL_Latch[12];
		DiscOutPort LAT_A[12];
		DiscOutPort LAT_B[12];
		DiscOutPort REL_A[12];
		DiscOutPort REL_B[12];
		DiscInPort MOTOR_1_PWR[12];
		DiscInPort MOTOR_2_PWR[12];
		DiscInPort IND_A[12];
		DiscInPort IND_B[12];
		DiscOutPort LAT_A_TB[12];
		DiscOutPort REL_A_TB[12];
		DiscOutPort RDY_A_TB[12];
		DiscOutPort REL_A_TM[12];
		DiscOutPort LAT_A_TM[12];
		DiscOutPort RDY_A_TM[12];
		DiscOutPort REL_B_TM[12];
		DiscOutPort LAT_B_TM[12];
		DiscOutPort RDY_B_TM[12];

		UINT animActiveLatch[12];
};

#endif //__ACTIVELATCHGROUP_H

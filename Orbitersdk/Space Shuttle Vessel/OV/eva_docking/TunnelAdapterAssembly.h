/****************************************************************************
  This file is part of Space Shuttle Vessel

  Tunnel Adapter Assembly subsystem definition


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
2020/05/10   GLS
2020/06/01   GLS
2020/06/20   GLS
2020/06/23   GLS
2020/08/25   GLS
2020/09/12   GLS
2020/10/07   GLS
2021/06/30   GLS
2021/07/03   GLS
2021/08/24   GLS
2022/01/01   GLS
2022/01/10   GLS
2022/02/16   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Tunnel Adapter Assembly System definition



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
#ifndef __TAA_H_
#define __TAA_H_


#include "../AtlantisSubsystem.h"


namespace eva_docking
{
	class TunnelAdapterAssembly:public AtlantisSubsystem
	{
		private:
			bool aft;
			bool extal;
			MESHHANDLE hMesh;
			UINT mesh_idx;

			void AddMesh( void );

		public:
			explicit TunnelAdapterAssembly( AtlantisSubsystemDirector* _director, bool aftlocation, bool extal );
			~TunnelAdapterAssembly( void );

			double GetSubsystemMass( void ) const override;
			bool GetSubsystemCoG( VECTOR3& CoG ) const override;
			void Realize( void ) override;

			void VisualCreated( VISHANDLE vis ) override;

			void GetPLBInfo( unsigned short& PLID_longeron1, unsigned short& PLID_longeron2, unsigned short& PLID_keel, bool& Reversed_longeron1, bool& Reversed_longeron2 ) const;
	};
};

#endif// __TAA_H_

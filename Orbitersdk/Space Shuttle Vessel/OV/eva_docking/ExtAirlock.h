/****************************************************************************
  This file is part of Space Shuttle Vessel

  External Airlock subsystem definition


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
2020/05/10   GLS
2020/05/23   GLS
2020/06/01   GLS
2020/06/20   GLS
2020/06/23   GLS
2020/08/25   GLS
2020/09/12   GLS
2020/10/07   GLS
2021/06/30   GLS
2021/07/03   GLS
2021/08/24   GLS
2022/01/10   GLS
2022/02/16   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/08/05   GLS
2022/09/29   GLS
2023/01/14   GLS
2023/02/12   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  External Airlock subsystem definition



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
#ifndef _EXTAL_H_
#define _EXTAL_H_


#include "../AtlantisSubsystem.h"
#include <EngConst.h>


class ExternalLight;


namespace eva_docking
{
	inline constexpr double EXTAL_MASS = 4310.0 * LBM2KG;// [kg]
	inline constexpr VECTOR3 EXTAL_CG = {0.0, -1.0621, 7.7544};// (approx) Xo+649.0 Yo+0.0 Zo+375.0
	inline constexpr VECTOR3 EXTAL_AFT_CG = {0.0, -1.0621, 5.65636};// (approx) Xo+731.60 Yo+0.0 Zo+375.0


	class ExtAirlock: public AtlantisSubsystem
	{
	protected:
		bool aft;
		double fHatchState;
		double fExtALPress[2];

		bool HideTopCover;

		UINT mesh_extal;
		MESHHANDLE hExtALMesh;

		ExternalLight* truss_lights[2];

		void AddMesh( void );

		void RunLights( double simdt );

	public:
		ExtAirlock( AtlantisSubsystemDirector* _director, const string& _ident, bool aftlocation, bool HideTopCover = false);
		virtual ~ExtAirlock();

		void Realize() override;
		void VisualCreated( VISHANDLE vis ) override;
		void OnPostStep( double simt, double simdt, double mjd ) override;
		double GetSubsystemMass() const override {return EXTAL_MASS;};
		bool GetSubsystemCoG( VECTOR3& CoG ) const override {CoG = aft ? EXTAL_AFT_CG : EXTAL_CG; return true;};
		virtual void ShiftCG( const VECTOR3& shift ) override;

		double GetZPos( void ) const;

		void GetPLBInfo( unsigned short& PLID_longeron1, unsigned short& PLID_longeron2, unsigned short& PLID_keel, bool& Reversed_longeron1, bool& Reversed_longeron2 ) const;
	};
}

#endif// _EXTAL_H_

/****************************************************************************
  This file is part of Space Shuttle Vessel

  AeroSurfaces System definition


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
2020/05/08   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/01/11   GLS
2021/01/18   GLS
2021/01/23   GLS
2021/01/25   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/12/26   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  AeroSurfaces System definition



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
#ifndef __AEROSURFACES_H_
#define __AEROSURFACES_H_


#include "AtlantisSubsystem.h"
#include <discsignals.h>
#include <Orbitersdk.h>


using namespace discsignals;


class AeroSurfaces:public AtlantisSubsystem
{
	friend class Atlantis;

	private:
		// commands
		DiscInPort dipElevon_LOB;
		DiscInPort dipElevon_LIB;
		DiscInPort dipElevon_RIB;
		DiscInPort dipElevon_ROB;
		DiscInPort dipRudder;
		DiscInPort dipSpeedBrake;
		DiscInPort dipBodyFlap;

		// positions
		DiscOutPort dopElevon_LOB;
		DiscOutPort dopElevon_LIB;
		DiscOutPort dopElevon_RIB;
		DiscOutPort dopElevon_ROB;
		DiscOutPort dopRudder;
		DiscOutPort dopSpeedBrake;
		DiscOutPort dopBodyFlap;

		// physical status [deg]
		double Elevon_LOB;
		double Elevon_LIB;
		double Elevon_RIB;
		double Elevon_ROB;
		double Rudder;
		double SpeedBrake;
		double BodyFlap;

		UINT anim_lobelevon;
		UINT anim_libelevon;
		UINT anim_ribelevon;
		UINT anim_robelevon;
		UINT anim_leftelevonsealpanel1;
		UINT anim_leftelevonsealpanel2;
		UINT anim_leftelevonsealpanel3;
		UINT anim_leftelevonsealpanel4;
		UINT anim_leftelevonsealpanel5;
		UINT anim_leftelevonsealpanel6;
		UINT anim_leftelevonsealpanel7;
		UINT anim_leftelevonsealpanel8;
		UINT anim_leftelevonsealpanel9;
		UINT anim_leftelevonsealpanel10;
		UINT anim_leftelevonsealpanel11;
		UINT anim_leftelevonsealpanel12;
		UINT anim_leftelevonsealpanel13;
		UINT anim_leftelevonsealpanel14;
		UINT anim_leftelevonsealpanel15;
		UINT anim_rightelevonsealpanel1;
		UINT anim_rightelevonsealpanel2;
		UINT anim_rightelevonsealpanel3;
		UINT anim_rightelevonsealpanel4;
		UINT anim_rightelevonsealpanel5;
		UINT anim_rightelevonsealpanel6;
		UINT anim_rightelevonsealpanel7;
		UINT anim_rightelevonsealpanel8;
		UINT anim_rightelevonsealpanel9;
		UINT anim_rightelevonsealpanel10;
		UINT anim_rightelevonsealpanel11;
		UINT anim_rightelevonsealpanel12;
		UINT anim_rightelevonsealpanel13;
		UINT anim_rightelevonsealpanel14;
		UINT anim_rightelevonsealpanel15;
		UINT anim_bf;
		UINT anim_rsb_right;
		UINT anim_rsb_left;


		void AddAnimation( void );

		void SetDigitals( void );
		void SetAerosurfacePosition( double Elevon_LOB, double Elevon_LIB, double Elevon_RIB, double Elevon_ROB, double Rudder, double SpeedBrake, double BodyFlap );

		double GetElevonSealPanel1AnimState( double elevon ) const;
		double GetElevonSealPanel8AnimState( double elevon ) const;
		double GetElevonSealPanel9AnimState( double elevon ) const;
		double GetElevonSealPanel15AnimState( double elevon ) const;

	public:
		explicit AeroSurfaces( AtlantisSubsystemDirector* _director );
		~AeroSurfaces( void );

		bool SingleParamParseLine() const override {return true;};
		bool OnParseLine( const char* line ) override;
		void OnSaveState( FILEHANDLE scn ) const override;
		void Realize( void ) override;
		void OnPostStep( double simt, double simdt, double mjd ) override;
};


#endif// __AEROSURFACES_H_
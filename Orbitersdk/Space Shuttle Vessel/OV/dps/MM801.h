/****************************************************************************
  This file is part of Space Shuttle Vessel

  MM801 definition


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
2020/06/20   GLS
2021/07/03   GLS
2021/08/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/06/10   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  MM801 definition



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
#ifndef __MM801_H_
#define __MM801_H_


#include "SimpleGPCSoftware.h"


namespace dps
{
	class MM801 : public SimpleGPCSoftware
	{
		public:
			explicit MM801(SimpleGPCSystem* _gpc);
			virtual ~MM801();
			void OnPreStep(double simt, double simdt, double mjd) override;

			bool OnMajorModeChange(unsigned int newMajorMode) override;
			bool OnParseLine(const char* keyword, const char* value) override;
			void OnSaveState(FILEHANDLE scn) const override;

			bool ItemInput(int spec, int item, const char* Data, bool &IllegalEntry ) override;
			bool OnPaint(int spec, vc::MDU* pMDU) const override;

		private:
			enum AEROSURFACE_DRIVE_TARGET {FV1, FV2, FV3}; // during aerosurface drive, aerosurfaces cycle between FV-1 and FV-2 positions, and are driven to FV-3 position at end of test

			double GetAerosurfaceCommand(double curTarget, double simdt, AEROSURFACE_DRIVE_TARGET& targetIdx, const double RATE, const double* POSITIONS);
			double GetBodyflapCommand( double curDrive, double curPosition, AEROSURFACE_DRIVE_TARGET& targetIdx, const double* POSITIONS );
			void PrintElevonPos(double pos, char* buff) const;
			void PrintRudderPos(double pos, char* buff) const;
			void PrintSpeedbrakePos(double pos, char* buff) const;

			bool bFCSTestActive, bFCSTestEnding;
			AEROSURFACE_DRIVE_TARGET ElevonTargetIdx;
			AEROSURFACE_DRIVE_TARGET RudderTargetIdx;
			AEROSURFACE_DRIVE_TARGET SpeedbrakeTargetIdx;
			AEROSURFACE_DRIVE_TARGET BodyflapTargetIdx;
			double ElevonTarget, RudderTarget, SpeedbrakeTarget;
			double BodyflapDrive;
			bool ModeLT;

			bool downarrow_ElevonLOB;
			bool downarrow_ElevonLIB;
			bool downarrow_ElevonRIB;
			bool downarrow_ElevonROB;
			bool downarrow_Rudder;
			bool downarrow_Speedbrake;
	};


}

#endif// __MM801_H_

/****************************************************************************
  This file is part of Space Shuttle Vessel

  Video Control Unit subsystem definition


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
2020/03/20   GLS
2020/04/01   GLS
2020/04/07   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/06/19   GLS
2021/07/01   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/18   GLS
2022/09/19   GLS
2023/02/05   GLS
2023/02/13   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Video Control Unit definition



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
#ifndef __VCU_H_
#define __VCU_H_


#include "AtlantisSubsystem.h"
#include <DiscInPort.h>
#include <DiscOutPort.h>
#include <gcCoreAPI.h>


inline constexpr int IMAGE_SIZE = 512;// [px]
inline constexpr int IMAGE_SIZE2 = IMAGE_SIZE / 2;// [px]
inline constexpr int IMAGE_SIZE4 = IMAGE_SIZE / 4;// [px]


// input from PB and output to light
inline constexpr unsigned int VideoInputA = 0;
inline constexpr unsigned int VideoInputB = 1;
inline constexpr unsigned int VideoInputC = 2;
inline constexpr unsigned int VideoInputD = 3;
inline constexpr unsigned int VideoInputRMS = 4;
inline constexpr unsigned int VideoInputFltDeck = 5;
inline constexpr unsigned int VideoInputMidDeck = 6;
inline constexpr unsigned int VideoInputPL1 = 7;
inline constexpr unsigned int VideoInputPL2 = 8;
inline constexpr unsigned int VideoInputPL3 = 9;
inline constexpr unsigned int VideoInputMUX1 = 10;
inline constexpr unsigned int VideoInputMUX2 = 11;
inline constexpr unsigned int VideoInputTest = 12;
inline constexpr unsigned int VideoOutputMon1 = 13;
inline constexpr unsigned int VideoOutputMon2 = 14;
inline constexpr unsigned int VideoOutputDownLink = 15;
inline constexpr unsigned int VideoOutputDTV = 16;
inline constexpr unsigned int VideoOutputMUX1L = 17;
inline constexpr unsigned int VideoOutputMUX1R = 18;
inline constexpr unsigned int VideoOutputMUX2L = 19;
inline constexpr unsigned int VideoOutputMUX2R = 20;
inline constexpr unsigned int MenuALC = 21;
inline constexpr unsigned int MenuManGain = 22;
inline constexpr unsigned int MenuColorBalLTLevel = 23;
inline constexpr unsigned int Mode1 = 24;
inline constexpr unsigned int Mode2 = 25;
inline constexpr unsigned int Mode3 = 26;

// input from switches
inline constexpr unsigned int CameraPowerOnA = 27;
inline constexpr unsigned int CameraPowerOffA = 28;
inline constexpr unsigned int CameraPowerOnB = 29;
inline constexpr unsigned int CameraPowerOffB = 30;
inline constexpr unsigned int CameraPowerOnC = 31;
inline constexpr unsigned int CameraPowerOffC = 32;
inline constexpr unsigned int CameraPowerOnD = 33;
inline constexpr unsigned int CameraPowerOffD = 34;
inline constexpr unsigned int CameraPowerOnRMS = 35;
inline constexpr unsigned int CameraPowerOffRMS = 36;

inline constexpr unsigned int CameraCommandReset = 37;
inline constexpr unsigned int CameraCommandLowRate = 38;
inline constexpr unsigned int CameraCommandTiltUp = 39;
inline constexpr unsigned int CameraCommandTiltDown = 40;
inline constexpr unsigned int CameraCommandPanLeft = 41;
inline constexpr unsigned int CameraCommandPanRight = 42;
inline constexpr unsigned int CameraCommandZoomIn = 43;
inline constexpr unsigned int CameraCommandZoomOut = 44;

inline constexpr unsigned int INPUT_COUNT = 45;


// output to tb
inline constexpr unsigned int CameraPower_FWD_BAY_TB = 27;
inline constexpr unsigned int CameraPower_KEEL_EVA_TB = 28;
inline constexpr unsigned int CameraPower_AFT_BAY_TB = 29;
inline constexpr unsigned int CameraPower_STBD_RMS_TB = 30;
inline constexpr unsigned int CameraPower_PORT_RMS_TB = 31;

// output to cameras
inline constexpr unsigned int CameraOn_FWD_BAY = 32;
inline constexpr unsigned int CameraOn_KEEL_EVA = 33;
inline constexpr unsigned int CameraOn_AFT_BAY = 34;
inline constexpr unsigned int CameraOn_STBD_RMS = 35;
inline constexpr unsigned int CameraOn_PORT_RMS = 36;

inline constexpr unsigned int OUTPUT_COUNT = 37;


// video outputs
inline constexpr unsigned int OUT_MON1 = 0;
inline constexpr unsigned int OUT_MON2 = 1;
inline constexpr unsigned int OUT_DOWNLINK = 2;
inline constexpr unsigned int OUT_DTV = 3;
inline constexpr unsigned int OUT_MUX1L = 4;
inline constexpr unsigned int OUT_MUX1R = 5;
inline constexpr unsigned int OUT_MUX2L = 6;
inline constexpr unsigned int OUT_MUX2R = 7;

// video inputs
inline constexpr unsigned int IN_FWD_BAY = 0;
inline constexpr unsigned int IN_KEEL_EVA = 1;
inline constexpr unsigned int IN_AFT_BAY = 2;
inline constexpr unsigned int IN_STBD_RMS = 3;
inline constexpr unsigned int IN_PORT_RMS = 4;
inline constexpr unsigned int IN_FD = 5;
inline constexpr unsigned int IN_MD = 6;
inline constexpr unsigned int IN_PL1 = 7;
inline constexpr unsigned int IN_PL2 = 8;
inline constexpr unsigned int IN_PL3 = 9;
inline constexpr unsigned int IN_MUX1 = 10;
inline constexpr unsigned int IN_MUX2 = 11;
inline constexpr unsigned int IN_TEST = 12;


using namespace discsignals;
class VideoSource;

class VideoControlUnit:public AtlantisSubsystem
{
	private:
		DiscInPort input[INPUT_COUNT];
		DiscOutPort output[OUTPUT_COUNT];

		DiscInPort A_ON;
		DiscInPort B_ON;
		DiscInPort MNA;
		DiscInPort MNB;

		DiscInPort ManPanLeft;
		DiscInPort ManPanRight;
		DiscInPort ManTiltUp;
		DiscInPort ManTiltDown;

		bool power;

		int outsel;// current selected output
		int outsel_in[8];// selected input for each output

		VideoSource* cameras[10];

		bool camerapowerA;
		bool camerapowerB;
		bool camerapowerC;
		bool camerapowerD;
		bool camerapowerRMS;

		CAMERAHANDLE camhdl[2][2];// D3D9 camera handles for Monitors 1 and 2, and for each side of MUX
		SURFHANDLE hSurfMon[2][2];// surface handles for Monitors 1 and 2, and for each side of MUX
		SURFHANDLE hSurfBlack;// surface handle for black image (no video)

		bool GetVideo( const unsigned int cameraidx, const unsigned short mon, const unsigned int monidx, double& pan, double& tilt, double& zoom );

	public:
		explicit VideoControlUnit( AtlantisSubsystemDirector* _director );
		virtual ~VideoControlUnit( void );

		void Realize( void ) override;
		bool OnParseLine( const char* line ) override;
		void OnSaveState( FILEHANDLE scn ) const override;
		bool SingleParamParseLine( void ) const override {return true;};
		void OnPreStep( double simt, double simdt, double mjd ) override;

		void GetMonitorImage( const unsigned short mon, SURFHANDLE& hSurf, std::string& name, double& pan, double& tilt, double& zoom );

		void AddCamera( VideoSource* camera, unsigned int input );
};


#endif// __VCU_H_

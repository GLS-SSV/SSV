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
#include <gcConst.h>


inline constexpr int IMAGE_WIDTH = 512;// [px]
inline constexpr int IMAGE_WIDTH2 = IMAGE_WIDTH / 2;// [px]
inline constexpr int IMAGE_WIDTH4 = IMAGE_WIDTH / 4;// [px]
inline constexpr int IMAGE_HEIGHT = 512;// [px]


// input from PB and output to light
const int VideoInputA = 0;
const int VideoInputB = 1;
const int VideoInputC = 2;
const int VideoInputD = 3;
const int VideoInputRMS = 4;
const int VideoInputFltDeck = 5;
const int VideoInputMidDeck = 6;
const int VideoInputPL1 = 7;
const int VideoInputPL2 = 8;
const int VideoInputPL3 = 9;
const int VideoInputMUX1 = 10;
const int VideoInputMUX2 = 11;
const int VideoInputTest = 12;
const int VideoOutputMon1 = 13;
const int VideoOutputMon2 = 14;
const int VideoOutputDownLink = 15;
const int VideoOutputDTV = 16;
const int VideoOutputMUX1L = 17;
const int VideoOutputMUX1R = 18;
const int VideoOutputMUX2L = 19;
const int VideoOutputMUX2R = 20;
const int MenuALC = 21;
const int MenuManGain = 22;
const int MenuColorBalLTLevel = 23;
const int Mode1 = 24;
const int Mode2 = 25;
const int Mode3 = 26;

// input from switches
const int CameraPowerOnA = 27;
const int CameraPowerOffA = 28;
const int CameraPowerOnB = 29;
const int CameraPowerOffB = 30;
const int CameraPowerOnC = 31;
const int CameraPowerOffC = 32;
const int CameraPowerOnD = 33;
const int CameraPowerOffD = 34;
const int CameraPowerOnRMS = 35;
const int CameraPowerOffRMS = 36;
const int CameraRMSWrist = 37;
const int CameraRMSElbow = 38;

const int CameraCommandReset = 39;
const int CameraCommandLowRate = 40;
const int CameraCommandTiltUp = 41;
const int CameraCommandTiltDown = 42;
const int CameraCommandPanLeft = 43;
const int CameraCommandPanRight = 44;
const int CameraCommandZoomIn = 45;
const int CameraCommandZoomOut = 46;

// input from PTUs
const int PanCameraA = 47;
const int TiltCameraA = 48;
const int ZoomCameraA = 49;
const int PanCameraB = 50;
const int TiltCameraB = 51;
const int ZoomCameraB = 52;
const int PanCameraC = 53;
const int TiltCameraC = 54;
const int ZoomCameraC = 55;
const int PanCameraD = 56;
const int TiltCameraD = 57;
const int ZoomCameraD = 58;
const int PanCameraRMS = 59;
const int TiltCameraRMS = 60;
const int ZoomCameraRMS = 61;

const int INPUT_COUNT = 62;


// output to tb
const int CameraPowerA_TB = 27;
const int CameraPowerB_TB = 28;
const int CameraPowerC_TB = 29;
const int CameraPowerD_TB = 30;
const int CameraPowerRMS_TB = 31;

// output to PTUs
const int PTU_HighRate = 32;
const int PanLeftCameraA = 33;
const int PanRightCameraA = 34;
const int TiltUpCameraA = 35;
const int TiltDownCameraA = 36;
const int ZoomInCameraA = 37;
const int ZoomOutCameraA = 38;
const int PanLeftCameraB = 39;
const int PanRightCameraB = 40;
const int TiltUpCameraB = 41;
const int TiltDownCameraB = 42;

const int ZoomInCameraB = 43;
const int ZoomOutCameraB = 44;
const int PanLeftCameraC = 45;
const int PanRightCameraC = 46;
const int TiltUpCameraC = 47;
const int TiltDownCameraC = 48;
const int ZoomInCameraC = 49;
const int ZoomOutCameraC = 50;
const int PanLeftCameraD = 51;
const int PanRightCameraD = 52;
const int TiltUpCameraD = 53;
const int TiltDownCameraD = 54;
const int ZoomInCameraD = 55;
const int ZoomOutCameraD = 56;
const int PanLeftCameraRMS = 57;
const int PanRightCameraRMS = 58;

const int TiltUpCameraRMS = 59;
const int TiltDownCameraRMS = 60;
const int ZoomInCameraRMS = 61;
const int ZoomOutCameraRMS = 62;

const int OUTPUT_COUNT = 63;


// video outputs
const int OUT_MON1 = 0;
const int OUT_MON2 = 1;
const int OUT_DOWNLINK = 2;
const int OUT_DTV = 3;
const int OUT_MUX1L = 4;
const int OUT_MUX1R = 5;
const int OUT_MUX2L = 6;
const int OUT_MUX2R = 7;

// video inputs
const int IN_A = 0;
const int IN_B = 1;
const int IN_C = 2;
const int IN_D = 3;
const int IN_RMS = 4;
const int IN_FD = 5;
const int IN_MD = 6;
const int IN_PL1 = 7;
const int IN_PL2 = 8;
const int IN_PL3 = 9;
const int IN_MUX1 = 10;
const int IN_MUX2 = 11;
const int IN_TEST = 12;


using namespace discsignals;
class PayloadBay;
class RMS;

class VideoControlUnit:public AtlantisSubsystem
{
	private:
		DiscInPort input[INPUT_COUNT];
		DiscOutPort output[OUTPUT_COUNT];

		DiscInPort ManPanLeft;
		DiscInPort ManPanRight;
		DiscInPort ManTiltUp;
		DiscInPort ManTiltDown;

		int outsel;// current selected output
		int outsel_in[8];// selected input for each output


		PayloadBay* pPLB;
		RMS* pRMS;

		bool camerapowerA;
		bool camerapowerB;
		bool camerapowerC;
		bool camerapowerD;
		bool camerapowerRMS;

		CAMERAHANDLE camhdl_camA;
		CAMERAHANDLE camhdl_camB;
		CAMERAHANDLE camhdl_camC;
		CAMERAHANDLE camhdl_camD;
		CAMERAHANDLE camhdl_camRMS;

		SURFHANDLE hSurf_camA;
		SURFHANDLE hSurf_camB;
		SURFHANDLE hSurf_camC;
		SURFHANDLE hSurf_camD;
		SURFHANDLE hSurf_camRMS;

	public:
		explicit VideoControlUnit( AtlantisSubsystemDirector* _director );
		virtual ~VideoControlUnit( void );

		void Realize( void ) override;
		bool OnParseLine( const char* line ) override;
		void OnSaveState( FILEHANDLE scn ) const override;
		bool SingleParamParseLine( void ) const override {return true;};
		void OnPreStep( double simt, double simdt, double mjd ) override;

		void GetMonitorImage( const unsigned short mon, SURFHANDLE& hSurf, std::string& name, double& pan, double& tilt, double& zoom ) const;
};


#endif// __VCU_H_
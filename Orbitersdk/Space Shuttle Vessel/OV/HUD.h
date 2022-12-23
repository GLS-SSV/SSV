/****************************************************************************
  This file is part of Space Shuttle Vessel

  Heads-up Display subsystem definition


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
2020/04/07   GLS
2020/05/10   GLS
2020/06/20   GLS
2020/09/21   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/08/27   GLS
2022/09/29   GLS
2022/12/18   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Heads-up Display subsystem definition



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
#ifndef __HUD
#define __HUD


#include "AtlantisSubsystem.h"
#include "dps/SimpleBTU.h"
#include <DiscInPort.h>


using namespace discsignals;
using namespace dps;


class HUD : public AtlantisSubsystem, public SimpleBTU
{
	private:
		unsigned short ID;

		DiscInPort HUDPower;
		DiscInPort HUDBright;
		DiscInPort HUDBrightNight;
		DiscInPort HUDBrightDay;
		DiscInPort HUDDCLT;
		DiscInPort HUDTest;
		DiscInPort NLG_Down;
		DiscInPort LMG_Down;
		DiscInPort RMG_Down;
		DiscInPort NLG_Door_Up;
		DiscInPort LMG_Door_Up;
		DiscInPort RMG_Door_Up;

		bool testactive;
		double testrot;// rad

		char UpperLeftWindow[5 + 1];
		char UpperRightWindow1[5 + 1];
		char UpperRightWindow2[5 + 1];
		char SituationLine[29 + 1];
		bool UpperLeftWindowFlash;

		bool dclt_sw_on;
		unsigned int declutter_level;

		/**
		* 0) wait for deploy or deploy cues
		* 1) wait for downlocks
		* 2) run timer post deploy
		* 3) post deploy
		*/
		unsigned short gearstate;
		double tGear;

		/**
		* 0) wait for CSS engaged
		* 1) wait for CSS not engaged and run timer
		* 2) wait for CSS not engaged
		*/
		unsigned short cssstate;
		double tCSS;

		/**
		* 0) wait for MLS not in NAV
		* 1) wait for MLS in NAV and run timer
		* 2) wait for MLS in NAV
		*/
		unsigned short mlsnvstate;
		double tMLSNV;

		/**
		* 0) wait for B/F not at trail
		* 1) wait for B/F at trail and run timer
		* 2) wait for B/F at trail
		*/
		unsigned short bfstate;
		double tBF;

		double HUDFlashTime;
		bool bHUDFlasher; // used for flashing values on HUD

		double Roll;// [deg]
		double Pitch;// [deg]

		double GSI;// needle deflection [deg]
		bool GSIValid;

		double IndicatedAltitude;// [ft]
		bool IndicatedAltitudeValid;
		double RadarAltitude;// [ft]
		bool RadarAltitudeValid;
		double AngleOfAttack;// [deg]
		double EquivalentAirspeed;// [knots]
		bool EquivalentAirspeedValid;

		unsigned short SpeedbrakePosition;// [%]
		unsigned short SpeedbrakeCommand;// [%]

		int DR;// [ft]
		int CR;// [ft]
		int HR;// [ft]

		double rwXdot;// [fps]
		double rwYdot;// [fps]

		double VehicleHeading;// [deg]
		double RunwayHeading;// [deg]

		double FlightPath1;// [deg]
		double FlightPath2;// [deg]
		double X_zero;// [ft]

		double RollError;// [deg]
		double PitchError;// [deg]

		unsigned short HUD_CNTL1;
		unsigned short FlagsWord1;
		unsigned short FlagsWord2;

		bool NZValid;
		double NZ;// [g]
		double Beta;// [deg]

		unsigned short RW_LNGTH;// [ft]
		unsigned short RunwayToGo;// [ft]
		double DECEL_CMD_MAX;// [fps^2]

		double FDVVoffsetX;
		double FDVVoffsetY;
		double GuidanceoffsetX;
		double GuidanceoffsetY;

		bool hassetmode;

		double groundspeedFPS;// [fps]
		double groundspeedKNOTS;// [knots]
		double groundspeedFPS0;// [fps]
		double GSt0;// [sec]
		double GSdecel;//[fps^2]

		/**
		* Draws pitch ladder line on HUD.
		* Rotated font (for labelling line) is assumed to be selected into sketchpad
		* @param skp HUD Sketchpad instance
		* @param hps HUD HUDPAINTSPEC instance
		* @param ladderPitch pitch corresponding to line being drawn
		* @param orbiterPitch current pitch angle of orbiter
		* @param orbiterBank current bank angle of orbiter
		* @returns false if line is out of HUD area; true otherwise
		*/
		bool DrawHUDPitchLine( oapi::Sketchpad *skp, const HUDPAINTSPEC *hps, int ladderPitch, double orbiterPitch, double orbiterBank );

		/**
		* Draws triangle on sketchpad
		* VECTOR3s are passed because this is what DrawHUDGuidanceTriangles uses
		*/
		void DrawTriangle( oapi::Sketchpad *skp, const VECTOR3& pt1, const VECTOR3& pt2, const VECTOR3& pt3 );

		/**
		* Draws guidance triangles (rotated to be || with horizon) on HUD
		* @param skp HUD Sketchpad instance
		* @param hps HUD HUDPAINTSPEC instance
		* @param trianglePitch pitch corresponding to triangle being drawn
		* @param orbiterPitch current pitch angle of orbiter
		* @param orbiterBank current bank angle of orbiter
		* @param fdvv_x current x position of FD/VV symbol, so triangles are drawn on the sides
		*/
		void DrawHUDGuidanceTriangles( oapi::Sketchpad *skp, const HUDPAINTSPEC *hps, double degTrianglePitch, double degOrbiterPitch, double degOrbiterBank, double fdvv_x );

		/**
		* Calculates y distance between 2 altitudes in scale 3.
		* \param x1	HUD altitude 1
		* \param x2	HUD altitude 2
		* \return	y distance between altitudes (> 0 if x1 > x2)
		*/
		double HUDScale3Diff( double x1, double x2 ) const;

		/**
		* Draws selected altitude tape scale in the HUD.
		* \param skp	HUD Sketchpad instance
		* \param hps	HUD HUDPAINTSPEC instance
		* \param scale	selects altitude scale to draw
		* \param pos	y position to start drawing scale
		* \param alt	current altitude (ft), rounded to scale interval
		* \param up	if true, prints scale upward from pos parameter
		* \return	false if reached display edge (drawing done on that side)
		*/
		bool DrawHUDAltTapeScale( oapi::Sketchpad *skp, const HUDPAINTSPEC *hps, int scale, int& pos, int &alt, bool up );

		/**
		* Draws altitude tape in the HUD.
		* \param skp	HUD Sketchpad instance
		* \param hps	HUD HUDPAINTSPEC instance
		* \param alt	current altitude (ft)
		*/
		void DrawHUDAltTape( oapi::Sketchpad *skp, const HUDPAINTSPEC *hps, double alt );

		/**
		* Draws lower left window text in the HUD.
		* \param skp	HUD Sketchpad instance
		* \param hps	HUD HUDPAINTSPEC instance
		*/
		void DrawLowerLeftWindow( oapi::Sketchpad *skp, const HUDPAINTSPEC *hps );

		/**
		* Draws Speedbrake scale in the HUD.
		* \param skp	HUD Sketchpad instance
		* \param hps	HUD HUDPAINTSPEC instance
		*/
		void DrawHUDSBScale( oapi::Sketchpad *skp, const HUDPAINTSPEC *hps ) const;

		/**
		* Draws deceleration scale in the HUD.
		* \param skp	HUD Sketchpad instance
		* \param hps	HUD HUDPAINTSPEC instance
		*/
		void DrawHUDDecelerationScale( oapi::Sketchpad *skp, const HUDPAINTSPEC *hps ) const;

		/**
		* Draws runway overlay in the HUD.
		* \param skp	HUD Sketchpad instance
		* \param hps	HUD HUDPAINTSPEC instance
		*/
		void DrawHUDRunwayOverlay( oapi::Sketchpad *skp, const HUDPAINTSPEC *hps ) const;

		/**
		* Draws normal acceleration value in the HUD.
		* \param skp	HUD Sketchpad instance
		* \param hps	HUD HUDPAINTSPEC instance
		*/
		void DrawHUDNormalAccel( oapi::Sketchpad *skp, const HUDPAINTSPEC *hps ) const;

		/**
		 * Converts a point in runway coordinate system to HUD.
		 */
		bool Runway2HUD_Point( const VECTOR3& pt_rwy, int& pt_HUD_X, int& pt_HUD_Y, double pitch, double roll, double hdg_ofs, const HUDPAINTSPEC *hps ) const;

		/**
		 * Converts the end points of a line in runway coordinate system to HUD.
		 * @return true if any segment of the line is in view
		 */
		bool Runway2HUD_Line( const VECTOR3& pt1_rwy, const VECTOR3& pt2_rwy, int& pt1_HUD_X, int& pt1_HUD_Y, int& pt2_HUD_X, int& pt2_HUD_Y, double pitch, double roll, double hdg_ofs, const HUDPAINTSPEC *hps ) const;

		void DrawGSI( const HUDPAINTSPEC* hps, oapi::Sketchpad* skp );

		void SetBrightness( void );

	public:
		HUD( AtlantisSubsystemDirector* _director, const string& _ident, unsigned short ID );
		~HUD( void );

		void busCommand( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw ) override;
		void busRead( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw ) override;

		bool OnParseLine( const char* line ) override;
		void OnSaveState( FILEHANDLE scn ) const override;
		bool SingleParamParseLine() const override {return true;};
		void Realize( void ) override;
		void OnPostStep( double simt, double simdt, double mjd ) override;

		bool Draw( const HUDPAINTSPEC* hps, oapi::Sketchpad* skp );
};

#endif// __HUD

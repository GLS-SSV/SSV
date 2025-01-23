/****************************************************************************
  This file is part of Space Shuttle Vessel

  Multi-Function Display Unit definition


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
2020/06/20   GLS
2020/08/24   GLS
2020/08/30   GLS
2020/09/07   GLS
2021/01/20   GLS
2021/06/20   GLS
2021/06/22   GLS
2021/07/03   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/03/24   GLS
2022/04/17   GLS
2022/06/13   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/12/18   indy91
2023/04/26   GLS
2023/05/12   GLS
2023/10/22   GLS
2025/01/23   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Multi-Function Display Unit definition



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
#ifndef _VC_MDU_H_
#define _VC_MDU_H_


#include "AtlantisVCComponent.h"
#include <vector>
#include "../dps/dps_defs.h"
#include <MathSSV.h>
#include <DrawAPI.h>
#include "discsignals.h"
#include <BusTerminal.h>


#define CR_BLACK RGB( 10, 18, 61 )
#define CR_DARK_GRAY RGB( 60, 60, 80 )
#define CR_LIGHT_GRAY RGB( 180, 180, 200 )
#define CR_WHITE RGB( 255, 255, 255 )
//#define CR_ORANGE RGB( 255, 128, 0 )
#define CR_RED RGB( 255, 0, 0 )
#define CR_YELLOW RGB( 255, 255, 0 )
#define CR_CYAN RGB( 0, 255, 255 )
#define CR_MAGENTA RGB( 255, 0, 255 )
#define CR_LIGHT_GREEN RGB( 0, 255, 0 )
#define CR_DARK_GREEN RGB( 0, 160, 0 )
#define CR_BLUE RGB( 0, 0, 255 )
//#define CR_PINK RGB( 220, 150, 220 )
//#define CR_BROWN RGB( 190, 50, 30 )

#define CR_DPS_GREEN RGB( 128, 255, 0 )

inline constexpr int ORBITER_TOP_COUNT = 66;
// horizontal "slices" left to right, nose to tail
inline constexpr int ORBITER_TOP_X[ORBITER_TOP_COUNT] = {
	0, 1,
	-1, 0, 1, 2,
	-1, 0, 1, 2,
	-1, 2,
	-2, -1, 2, 3,
	-2, -1, 2, 3,
	-2, -1, 2, 3,
	-2, -1, 2, 3,
	-3, -2, 3, 4,
	-4, -3, 4, 5,
	-5, -4, 5, 6,
	-5, -4, 5, 6,
	-5, -4, -3, -2, -1, 2, 3, 4, 5, 6,
	-4, -3, -2, -1, 0, 1, 2, 3, 4, 5,
	0, 1
	};
inline constexpr int ORBITER_TOP_Y[ORBITER_TOP_COUNT] = {
	0, 0,
	1, 1, 1, 1,
	2, 2, 2, 2,
	3, 3,
	4, 4, 4, 4,
	5, 5, 5, 5,
	6, 6, 6, 6,
	7, 7, 7, 7,
	8, 8, 8, 8,
	9, 9, 9, 9,
	10, 10, 10, 10,
	11, 11, 11, 11,
	12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
	13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
	14, 14
	};

inline constexpr int ORBITER_SIDE_COUNT = 66;
// vertical "slices" top down, nose to tail
inline constexpr int ORBITER_SIDE_X[ORBITER_SIDE_COUNT] = {
	-7, -7,
	-6, -6, -6, -6,
	-5, -5, -5, -5,
	-4, -4, -4, -4,
	-3, -3, -3, -3,
	-2, -2, -2, -2,
	-1, -1, -1, -1,
	0, 0, 0, 0,
	1, 1, 1, 1,
	2, 2, 2, 2,
	3, 3, 3, 3,
	4, 4, 4, 4,
	5, 5, 5, 5, 5, 5,
	6, 6, 6, 6, 6, 6, 6, 6,
	7, 7, 7, 7, 7,
	8
	};
inline constexpr int ORBITER_SIDE_Y[ORBITER_SIDE_COUNT] = {
	-3, -2,
	-4, -3, -2, -1,
	-5, -4, -1, 0,
	-6, -5, -1, 0,
	-6, -5, -1, 0,
	-6, -5, -1, 0,
	-6, -5, -1, 0,
	-6, -5, -1, 0,
	-6, -5, -1, 0,
	-6, -5, -1, 0,
	-7, -6, -1, 0,
	-8, -7, -1, 0,
	-9, -8, -6, -5, -1, 0,
	-9, -8, -7, -6, -5, -4, -2, -1,
	-9, -8, -4, -3, -2,
	-3
	};


namespace dps
{
	class IDP;
}


namespace vc
{
	class MDU: public AtlantisVCComponent, public BusTerminal
	{
		double t0;
		bool counting;

		bool BezelPower;
		discsignals::DiscInPort dipPower;

		MGROUP_ROTATE* pPowerAnim;
		UINT anim_power;
		UINT grpPowerIndex;
		VECTOR3 refPower;
		VECTOR3 dirPower;


		// MEDS pens and brushes
		static HBRUSH gdiBlackBrush;
		static HBRUSH gdiDarkGrayBrush;
		static HBRUSH gdiLightGrayBrush;
		static HBRUSH gdiWhiteBrush;
		static HBRUSH gdiRedBrush;
		static HBRUSH gdiYellowBrush;
		static HBRUSH gdiCyanBrush;
		static HBRUSH gdiMagentaBrush;
		static HBRUSH gdiLightGreenBrush;
		static HBRUSH gdiBlueBrush;

		static oapi::Brush* skpBlackBrush;
		static oapi::Brush* skpDarkGrayBrush;
		static oapi::Brush* skpLightGrayBrush;
		static oapi::Brush* skpWhiteBrush;
		static oapi::Brush* skpRedBrush;
		static oapi::Brush* skpYellowBrush;
		static oapi::Brush* skpCyanBrush;
		static oapi::Brush* skpMagentaBrush;
		static oapi::Brush* skpLightGreenBrush;
		static oapi::Brush* skpBlueBrush;
		static oapi::Brush* _skpBlackBrush;// "true" black, just for bitblt operations

		static HPEN gdiBlackPen;
		static HPEN gdiDarkGrayPen;
		static HPEN gdiLightGrayPen;
		static HPEN gdiLightGrayThickPen;
		static HPEN gdiWhitePen;
		static HPEN gdiRedPen;
		static HPEN gdiYellowPen;
		static HPEN gdiCyanPen;
		static HPEN gdiMagentaPen;
		static HPEN gdiLightGreenPen;
		static HPEN gdiDarkGreenPen;
		static HPEN gdiLightGreenThickPen;

		static oapi::Pen* skpBlackPen;
		static oapi::Pen* skpDarkGrayPen;
		static oapi::Pen* skpLightGrayThickPen;
		static oapi::Pen* skpLightGrayPen;
		static oapi::Pen* skpWhitePen;
		static oapi::Pen* skpRedPen;
		static oapi::Pen* skpYellowPen;
		static oapi::Pen* skpCyanPen;
		static oapi::Pen* skpMagentaPen;
		static oapi::Pen* skpLightGreenPen;
		static oapi::Pen* skpDarkGreenPen;
		static oapi::Pen* skpLightGreenThickPen;
		static oapi::Pen* _skpBlackPen;// "true" black, just for bitblt operations

		// DPS pens
		static HPEN gdiNormalPen;
		static HPEN gdiDashedNormalPen;
		static HPEN gdiOverbrightPen;

		static oapi::Pen* skpNormalPen;
		static oapi::Pen* skpDashedNormalPen;
		static oapi::Pen* skpOverbrightPen;

		// fonts
		static HFONT gdiSSVAFont_h40w34;
		static HFONT gdiSSVAFont_h19w19;// DPS small
		static HFONT gdiSSVAFont_h22w22;// DPS large
		static HFONT gdiSSVAFont_h19w19bold;
		static HFONT gdiSSVAFont_h22w18;
		static HFONT gdiSSVBFont_h36w18;
		static HFONT gdiSSVBFont_h24w14;
		static HFONT gdiSSVBFont_h32w18;
		HFONT gdiSSVAFont_h19w19rot;// DPS small
		HFONT gdiSSVAFont_h22w22rot;// DPS large

		static oapi::Font* skpSSVAFont_h40w34;
		static oapi::Font* skpSSVAFont_h19w19;// DPS small
		static oapi::Font* skpSSVAFont_h22w22;// DPS large
		static oapi::Font* skpSSVAFont_h19w19bold;
		static oapi::Font* skpSSVAFont_h22w18;
		static oapi::Font* skpSSVBFont_h36w18;
		static oapi::Font* skpSSVBFont_h24w14;
		static oapi::Font* skpSSVBFont_h32w18;

		double fontrotsmall;
		double fontrotlarge;

		void CreateGDIObjects();
		void DestroyGDIObjects();
		void CreateSketchpadObjects();
		void DestroySketchpadObjects();

		static HDC hDC_Tape_MACHV;
		static HDC hDC_Tape_KEAS;
		static HDC hDC_Tape_Alpha;
		static HDC hDC_Tape_H;
		static HDC hDC_Tape_Hdot;
		HDC hDC_ADI;
		HDC hDC_ADI_ORBIT;
		static HDC hDC_ADIMASK;
		static HDC hDC_ADIMASK_ORBIT;

		static HBITMAP hBM_Tape_MACHV_tmp;
		static HBITMAP hBM_Tape_KEAS_tmp;
		static HBITMAP hBM_Tape_Alpha_tmp;
		static HBITMAP hBM_Tape_H_tmp;
		static HBITMAP hBM_Tape_Hdot_tmp;
		HBITMAP hBM_ADI_tmp;
		HBITMAP hBM_ADI_ORBIT_tmp;
		static HBITMAP hBM_ADIMASK_tmp;
		static HBITMAP hBM_ADIMASK_ORBIT_tmp;

		int save_ADI;
		int save_ADI_ORBIT;

		static SURFHANDLE sfh_Tape_MACHV;
		static SURFHANDLE sfh_Tape_KEAS;
		static SURFHANDLE sfh_Tape_Alpha;
		static SURFHANDLE sfh_Tape_H;
		static SURFHANDLE sfh_Tape_Hdot;

		MESHHANDLE hADIball;

		unsigned short pribus;
		unsigned short secbus;

		void CreateTapes_GDI( void );
		void CreateTapes_Sketchpad( void );
		void DrawAlphaTapeBG_GDI( void );
		void DrawAlphaTapeBG_Sketchpad( void );
		void DrawAlphaTapeFG_GDI( int min, int max );
		void DrawAlphaTapeFG_Sketchpad( int min, int max );
		void DrawAlphaTapeLim_GDI( double min, double max );
		void DrawAlphaTapeLim_Sketchpad( double min, double max );
		void DestroyTapes( void );
		void CreateADI( void );
		void DestroyADI( void );

		/**
		 * Paints the DPS display.
		 */
		void DPS( HDC hDC );
		void DPS( oapi::Sketchpad* skp );

		// for DPS display drawing
		bool DPS_use_HDC;
		HDC hDC_DPS;
		oapi::Sketchpad* skp_DPS;

		/**
		 * MEDS Display functions
		 */
		void SystemStatusDisplay_CSTMenu( HDC hDC );
		void SystemStatusDisplay_CSTMenu( oapi::Sketchpad* skp );
		void SystemStatusDisplay_IDPInteractiveCST( HDC hDC );
		void SystemStatusDisplay_IDPInteractiveCST( oapi::Sketchpad* skp );
		void AEPFD( HDC hDC );
		void AEPFD( oapi::Sketchpad* skp );
		void ORBITPFD( HDC hDC );
		void ORBITPFD( oapi::Sketchpad* skp );
		void OMSMPS( HDC hDC );
		void OMSMPS( oapi::Sketchpad* skp );
		void APUHYD( HDC hDC );
		void APUHYD( oapi::Sketchpad* skp );
		void SPI( HDC hDC );
		void SPI( oapi::Sketchpad* skp );

		void Tape_Alpha( HDC hDC, double alpha, double vel );
		void Tape_Alpha( oapi::Sketchpad* skp, double alpha, double vel );
		void Tape_EAS( HDC hDC, double eas );
		void Tape_EAS( oapi::Sketchpad* skp, double eas );
		void Tape_MV( HDC hDC, char label, double mach );
		void Tape_MV( oapi::Sketchpad* skp, char label, double mach );
		void Tape_H_Hdot( HDC hDC, double Altitude_ft, double Hdot );
		void Tape_H_Hdot( oapi::Sketchpad* skp, double Altitude_ft, double Hdot );
		void Tapes_Invalid( HDC hDC );
		void Tapes_Invalid( oapi::Sketchpad* skp );

		void Box_EAS( HDC hDC, double eas );
		void Box_EAS( oapi::Sketchpad* skp, double eas );
		void Box_MVR( HDC hDC, double mach );
		void Box_MVR( oapi::Sketchpad* skp, double mach );

		void ADI_STATIC( HDC hDC );
		void ADI_STATIC( oapi::Sketchpad* skp );
		void ADI_STATIC_ORBIT( HDC hDC );
		void ADI_STATIC_ORBIT( oapi::Sketchpad* skp );
		void ADI( HDC hDC, double sinpitch, double cospitch, double sinroll, double cosroll, double sinyaw, double cosyaw );
		void ADI( oapi::Sketchpad* skp, double sinpitch, double cospitch, double sinroll, double cosroll, double sinyaw, double cosyaw );
		void ADI_ORBIT( HDC hDC, double sinpitch, double cospitch, double sinroll, double cosroll, double sinyaw, double cosyaw );
		void ADI_ORBIT( oapi::Sketchpad* skp, double sinpitch, double cospitch, double sinroll, double cosroll, double sinyaw, double cosyaw );
		void ADI_RATE( HDC hDC, unsigned short pitchrate, unsigned short rollrate, unsigned short yawrate, unsigned short pitchratescale, unsigned short rollratescale, unsigned short yawratescale, unsigned short TGOSEC, unsigned short ADIRR_0_ON_R );
		void ADI_RATE( oapi::Sketchpad* skp, unsigned short pitchrate, unsigned short rollrate, unsigned short yawrate, unsigned short pitchratescale, unsigned short rollratescale, unsigned short yawratescale, unsigned short TGOSEC, unsigned short ADIRR_0_ON_R );
		void ADI_RATE_ORBIT( HDC hDC, unsigned short pitchrate, unsigned short rollrate, unsigned short yawrate );
		void ADI_RATE_ORBIT( oapi::Sketchpad* skp, unsigned short pitchrate, unsigned short rollrate, unsigned short yawrate );
		void ADI_ERROR( HDC hDC, unsigned short pitcherror, unsigned short rollerror, unsigned short yawerror, unsigned short pitcherrorscale );
		void ADI_ERROR( oapi::Sketchpad* skp, unsigned short pitcherror, unsigned short rollerror, unsigned short yawerror, unsigned short pitcherrorscale );
		void ADI_ERROR_ORBIT( HDC hDC, unsigned short pitcherror, unsigned short rollerror, unsigned short yawerror );
		void ADI_ERROR_ORBIT( oapi::Sketchpad* skp, unsigned short pitcherror, unsigned short rollerror, unsigned short yawerror );

		void HSI_A( HDC hDC, double heading, unsigned short roll_sw, bool drawcourse, double course, bool drawCDI, bool CDIflag, double CDIscale, double CDIdeviation, char primarytype, double primarybearing, char secondarytype, double secondarybearing );
		void HSI_A( oapi::Sketchpad* skp, double heading, unsigned short roll_sw, bool drawcourse, double course, bool drawCDI, bool CDIflag, double CDIscale, double CDIdeviation, char primarytype, double primarybearing, char secondarytype, double secondarybearing );
		void HSI_E( HDC hDC, double heading, bool drawcourse, double course, bool drawCDI, bool CDIflag, double CDIscale, double CDIdeviation, char primarytype, double primarybearing, char secondarytype, double secondarybearing );
		void HSI_E( oapi::Sketchpad* skp, double heading, bool drawcourse, double course, bool drawCDI, bool CDIflag, double CDIscale, double CDIdeviation, char primarytype, double primarybearing, char secondarytype, double secondarybearing );
		void HSI_CourseArrow( HDC hDC );
		void HSI_CourseArrow( oapi::Sketchpad* skp );
		void HSI_CDI( HDC hDC, bool flag, double scale, double deviation );
		void HSI_CDI( oapi::Sketchpad* skp, bool flag, double scale, double deviation );
		void HSI_Bearing( HDC hDC, char primarytype, double primarybearing, char secondarytype, double secondarybearing );
		void HSI_Bearing( oapi::Sketchpad* skp, char primarytype, double primarybearing, char secondarytype, double secondarybearing );
		void HSI_Bearing_E( HDC hDC, double bearing, bool pri );
		void HSI_Bearing_E( oapi::Sketchpad* skp, double bearing, bool pri );
		void HSI_Bearing_I( HDC hDC, double bearing );
		void HSI_Bearing_I( oapi::Sketchpad* skp, double bearing );
		void HSI_Bearing_RH( HDC hDC, double bearing, char chr );
		void HSI_Bearing_RH( oapi::Sketchpad* skp, double bearing, char chr );
		void HSI_Bearing_C( HDC hDC, double bearing );
		void HSI_Bearing_C( oapi::Sketchpad* skp, double bearing );

		void AEPFD_Header( HDC hDC, unsigned short MM, bool rtls, bool tal, bool ato, bool aoa, bool ca, unsigned short adiatt, bool autodappitch, bool autothrotry, bool blankthrotry, bool autosb, double mach );
		void AEPFD_Header( oapi::Sketchpad* skp, unsigned short MM, bool rtls, bool tal, bool ato, bool aoa, bool ca, unsigned short adiatt, bool autodappitch, bool autothrotry, bool blankthrotry, bool autosb, double mach );
		void AEPFD_BETA( HDC hDC, double beta );
		void AEPFD_BETA( oapi::Sketchpad* skp, double beta );
		void AEPFD_GMETER_STATIC( HDC hDC );
		void AEPFD_GMETER_STATIC( oapi::Sketchpad* skp );
		void AEPFD_GMETER( HDC hDC, short type, double accel );
		void AEPFD_GMETER( oapi::Sketchpad* skp, short type, double accel );
		void AEPFD_HACCEL( HDC hDC, double vacc );
		void AEPFD_HACCEL( oapi::Sketchpad* skp, double vacc );
		void AEPFD_RANGERW( HDC hDC );
		void AEPFD_RANGERW( oapi::Sketchpad* skp );
		void AEPFD_RANGEHACC( HDC hDC, double range );
		void AEPFD_RANGEHACC( oapi::Sketchpad* skp, double range );
		void AEPFD_dAZ_HTA( HDC hDC, bool flash, unsigned short daz );
		void AEPFD_dAZ_HTA( oapi::Sketchpad* skp, bool flash, unsigned short daz );
		void AEPFD_dXTRK( HDC hDC );
		void AEPFD_dXTRK( oapi::Sketchpad* skp );
		void AEPFD_XTRK( HDC hDC );
		void AEPFD_XTRK( oapi::Sketchpad* skp );
		void AEPFD_dINC( HDC hDC, double dinc );
		void AEPFD_dINC( oapi::Sketchpad* skp, double dinc );
		void AEPFD_TGTINC( HDC hDC );
		void AEPFD_TGTINC( oapi::Sketchpad* skp );
		void AEPFD_GSI( HDC hDC, bool flag, double scale, short deviation );
		void AEPFD_GSI( oapi::Sketchpad* skp, bool flag, double scale, short deviation );

		inline bool GetFlash( void ) const
		{
			int SimT=(int)(oapiGetSimTime() * 2);
			return (SimT%2)==1;
		}

	protected:
		unsigned short usMDUID;
		dps::IDP* prim_idp;
		dps::IDP* sec_idp;
		bool bInverseX;
		bool bUseSecondaryPort;
		bool bPortConfigMan;
		unsigned int FC;
		EXTMFDSPEC mfdspec;
		DWORD mat_idx;
		double fBrightness;
		bool bPower;

		int display;
		int menu;

		virtual void RegisterMFDContext(int id);

		void DrawMenuButton( HDC hDC, int x );
		void DrawMenuButton( oapi::Sketchpad* skp, int x );

		void TogglePort( void );

	public:
		MDU( Atlantis* _sts, const string& _ident, unsigned short _usMDUID, BusManager* pBusManager );
		virtual ~MDU();

		virtual bool OnReadState( FILEHANDLE scn ) override;
		virtual void OnSaveState( FILEHANDLE scn ) const override;
		virtual bool IsMultiLineSaveState() const override { return true; };

		void Rx( const BUS_ID id, void* data, const unsigned short datalen ) override;

		bool SetPrimaryIDP(dps::IDP* idp);
		bool SetSecondaryIDP(dps::IDP* idp);
		inline dps::IDP* GetIDP() const {
			if(bUseSecondaryPort)
				return sec_idp;
			else
				return prim_idp;
		}

		void VisualCreated( void ) override;

		/**
		 * Does nothing as it currently has no animations.
		 * @sa BasicVCComponent::DefineVCAnimations
		 */
		virtual void DefineVCAnimations(UINT vc_idx) override;

		/**
		 * Defines material id for screen brightness changes.
		 * param _mat_idx material id
		 */
		virtual void DefineMaterial( DWORD _mat_idx );

		/**
		 * Defines the group index for power button animation.
		 * param _grpIndex	group index
		 */
		virtual void DefinePowerButtonGroup( const UINT _grpIndex );

		/**
		 * Defines position and direction vectors for power button animation .
		 * param ref	reference position
		 * param dir	direction
		 */
		virtual void SetPowerButtonReference( const VECTOR3& ref, const VECTOR3& dir );

		/**
		 * handle mouse events
		 * @sa BasicVCComponent::OnMouseEvent
		 */
		virtual bool OnMouseEvent(int _event, float x, float y) override;

		virtual void OnPreStep( double simt, double simdt, double mjd ) override;

		/**
		 * Paint the edge menu area on this HDC.
		 */
		virtual void PaintEdgeMenu( HDC hDC );
		/**
		 * Paint the edge menu area on this Sketchpad.
		 */
		virtual void PaintEdgeMenu( oapi::Sketchpad* skp );
		/**
		 * Register the MFD area for Orbiter. Does nothing when MFD rendering
		 * is bypassed.
		 */
		virtual bool RealizeMFD(int id);

		virtual bool DefineVCGroup(UINT mgrp);

		virtual void ConnectPower( discsignals::DiscreteBundle* Bundle, const unsigned short Line );


		//IDP interface functions
		/**
		 * Print text.
		 */
		void Text( const short x, const short y, const char* txt, const unsigned int len, const unsigned char attributes, const double rot );

		/**
		 * Draw line.
		 * Coordinates should be between 0 and 511
		 */
		void Line( const short x1, const short y1, const short x2, const short y2, const char attributes );

		/**
		 * Draw circle.
		 * Coordinates should be between 0 and 511
		 */
		void Circle( const short x, const short y, const unsigned short r, const char attributes );


		inline void OrbiterSymbolSide( int x, int y, double rotation, char attributes = 0 )
		{
			/*double sinrot = sin( rotation );
			double cosrot = cos( rotation );

			DEU_PIXEL pixel;
			pixel.cAttr = attributes;

			for (int i = 0; i < ORBITER_SIDE_COUNT; i++)
			{
				pixel.x = Round( (ORBITER_SIDE_X[i] * cosrot) - (ORBITER_SIDE_Y[i] * sinrot) ) + x ;
				pixel.y = Round( (ORBITER_SIDE_X[i] * sinrot) + (ORBITER_SIDE_Y[i] * cosrot) ) + y + DPS_DISPLAY_VERTICAL_OFFSET;
				pixels.push_back( pixel );
			}*/
		}

		/**
		 * Draw a thick dot on DEU.
		 */
		inline void ThickDot( int x, int y, char attributes = 0 )
		{
			/*DEU_PIXEL pixel;
			pixel.cAttr = attributes;
			pixel.x = x - 2;
			pixel.y = y + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			pixel.x = x - 1;
			pixel.y = y - 1 + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			//pixel.x = x - 1;
			pixel.y = y + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			//pixel.x = x - 1;
			pixel.y = y + 1 + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			pixel.x = x;
			pixel.y = y - 2 + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			//pixel.x = x;
			pixel.y = y - 1 + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			//pixel.x = x;
			pixel.y = y + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			//pixel.x = x;
			pixel.y = y + 1 + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			//pixel.x = x;
			pixel.y = y + 2 + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			pixel.x = x + 1;
			pixel.y = y - 1 + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			//pixel.x = x + 1;
			pixel.y = y + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			//pixel.x = x + 1;
			pixel.y = y + 1 + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			pixel.x = x + 2;
			pixel.y = y + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );*/
			return;
		}

		/**
		 * Draw a filled left arrow on DEU.
		 */
		inline void LeftArrowFilled( int x, int y, char attributes = 0 )
		{
			/*DEU_LINE line;
			line.cAttr = attributes;
			line.x0 = x + 3;
			line.y0 = y - 2 + DPS_DISPLAY_VERTICAL_OFFSET;
			line.x1 = x + 12;
			line.y1 = line.y0;
			lines.push_back( line );

			//line.x0 = x + 3;
			line.y0 = y + DPS_DISPLAY_VERTICAL_OFFSET;
			//line.x1 = x + 12;
			line.y1 = line.y0;
			lines.push_back( line );

			//line.x0 = x + 3;
			line.y0 = y + 2 + DPS_DISPLAY_VERTICAL_OFFSET;
			//line.x1 = x + 12;
			line.y1 = line.y0;
			lines.push_back( line );

			DEU_PIXEL pixel;
			pixel.cAttr = attributes;
			pixel.x = x;
			pixel.y = y + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			//pixel.x = x;
			pixel.y = y - 1 + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			pixel.x = x + 1;
			pixel.y = y + 1 + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			//pixel.x = x + 1;
			pixel.y = y + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			//pixel.x = x + 1;
			pixel.y = y - 1 + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			//pixel.x = x + 1;
			pixel.y = y - 2 + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			pixel.x = x + 2;
			pixel.y = y + 2 + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			//pixel.x = x + 2;
			pixel.y = y + 1 + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			//pixel.x = x + 2;
			pixel.y = y + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			//pixel.x = x + 2;
			pixel.y = y - 1 + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			//pixel.x = x + 2;
			pixel.y = y - 2 + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			//pixel.x = x + 2;
			pixel.y = y - 3 + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			pixel.x = x + 3;
			pixel.y = y + 3 + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			//pixel.x = x + 3;
			pixel.y = y + 2 + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			//pixel.x = x + 3;
			pixel.y = y + 1 + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			//pixel.x = x + 3;
			pixel.y = y + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			//pixel.x = x + 3;
			pixel.y = y - 1 + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			//pixel.x = x + 3;
			pixel.y = y - 2 + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			//pixel.x = x + 3;
			pixel.y = y - 3 + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			//pixel.x = x + 3;
			pixel.y = y - 4 + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );*/
		}

		/**
		 * Draw a hollow left arrow on DEU.
		 */
		inline void LeftArrowHollow( int x, int y, char attributes = 0 )
		{
			/*Line( x, y, x + 5, y + 5, attributes );
			Line( x, y, x + 5, y - 5, attributes );

			Line( x + 5, y + 3, x + 13, y + 3, attributes );
			Line( x + 13, y + 3, x + 13, y - 3, attributes );
			Line( x + 5, y - 3, x + 13, y - 3, attributes );*/
			return;
		}

		virtual bool GetViewAngle() const;
		virtual short GetPortConfig() const;
		virtual bool GetSelectedPort() const;

		/**
		 * Return the identification of the IDP driving this
		 * display.
		 * @return 0 if not connected to IDP or IDP failed
		 */
		virtual unsigned short GetDrivingIDP() const;

		virtual void PaintDisplay( oapi::Sketchpad* skp );
		virtual bool NavigateMenu( DWORD key );
		virtual char* ButtonLabel( int bt );
		virtual int ButtonMenu( const MFDBUTTONMENU **menu ) const;
	};
}

#endif// _VC_MDU_H_

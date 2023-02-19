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

#define CR_DPS_NORMAL RGB( 128, 255, 0 )
#define CR_DPS_OVERBRIGHT RGB( 255, 255, 0 )

inline constexpr int DPS_DISPLAY_VERTICAL_OFFSET = 32;

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
	class MDU: public AtlantisVCComponent
	{
		double t0;
		bool counting;

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
		static HPEN gdiOverbrightPen;
		static HPEN gdiNormalPen;
		static HPEN gdiDashedNormalPen;

		static oapi::Pen* skpOverbrightPen;
		static oapi::Pen* skpNormalPen;
		static oapi::Pen* skpDashedNormalPen;

		// fonts
		static HFONT gdiSSVAFont_h20w17;
		static HFONT gdiSSVAFont_h10w10bold;
		static HFONT gdiSSVAFont_h11w9;
		static HFONT gdiSSVBFont_h18w9;
		static HFONT gdiSSVBFont_h12w7;
		static HFONT gdiSSVBFont_h16w9;

		static oapi::Font* skpSSVAFont_h20w17;
		static oapi::Font* skpSSVAFont_h10w10bold;
		static oapi::Font* skpSSVAFont_h11w9;
		static oapi::Font* skpSSVBFont_h18w9;
		static oapi::Font* skpSSVBFont_h12w7;
		static oapi::Font* skpSSVBFont_h16w9;

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

		void Tape_Alpha( HDC hDC, double vel );
		void Tape_Alpha( oapi::Sketchpad* skp, double vel );
		void Tape_KEAS_MVR( HDC hDC, double vel );
		void Tape_KEAS_MVR( oapi::Sketchpad* skp, double vel );
		void Tape_MV_KEAS( HDC hDC, char label, double vel );
		void Tape_MV_KEAS( oapi::Sketchpad* skp, char label, double vel );
		void Tape_H_Hdot( HDC hDC, double Altitude_ft, double Hdot );
		void Tape_H_Hdot( oapi::Sketchpad* skp, double Altitude_ft, double Hdot );
		void Tapes_Invalid( HDC hDC );
		void Tapes_Invalid( oapi::Sketchpad* skp );

		void ADI_STATIC( HDC hDC );
		void ADI_STATIC( oapi::Sketchpad* skp );
		void ADI_STATIC_ORBIT( HDC hDC );
		void ADI_STATIC_ORBIT( oapi::Sketchpad* skp );
		void ADI( HDC hDC, double pitch, double roll, double yaw );
		void ADI( oapi::Sketchpad* skp, double pitch, double roll, double yaw );
		void ADI_ORBIT( HDC hDC, double pitch, double roll, double yaw );
		void ADI_ORBIT( oapi::Sketchpad* skp, double pitch, double roll, double yaw );
		void ADI_RATE_A( HDC hDC, double pitch, double roll, double yaw, int adirate );// 10/5/1
		void ADI_RATE_A( oapi::Sketchpad* skp, double pitch, double roll, double yaw, int adirate );// 10/5/1
		void ADI_RATE_B( HDC hDC, double pitch, double roll, double yaw, int adirate, double Altitude_ft );// 5/(5/etc)/5
		void ADI_RATE_B( oapi::Sketchpad* skp, double pitch, double roll, double yaw, int adirate, double Altitude_ft );// 5/(5/etc)/5
		void ADI_RATE_ORBIT( HDC hDC, double pitch, double roll, double yaw, int adirate );// 10/5/1
		void ADI_RATE_ORBIT( oapi::Sketchpad* skp, double pitch, double roll, double yaw, int adirate );// 10/5/1
		void ADI_ERROR_A( HDC hDC, double pitch, double roll, double yaw, int adierr );// 10/5/1
		void ADI_ERROR_A( oapi::Sketchpad* skp, double pitch, double roll, double yaw, int adierr );// 10/5/1
		void ADI_ERROR_B( HDC hDC, double pitch, double roll, double yaw, int adierr );// 25/25/10 5/2/1 2.5/2.5/2.5
		void ADI_ERROR_B( oapi::Sketchpad* skp, double pitch, double roll, double yaw, int adierr );// 25/25/10 5/2/1 2.5/2.5/2.5
		void ADI_ERROR_C( HDC hDC, double pitch, double roll, double yaw, int adierr );// 25/25/10 1.25/1.25/0.5 2.5/2.5/2.5
		void ADI_ERROR_C( oapi::Sketchpad* skp, double pitch, double roll, double yaw, int adierr );// 25/25/10 1.25/1.25/0.5 2.5/2.5/2.5
		void ADI_ERROR_D( HDC hDC, double pitch, double roll, double yaw, int adierr );// 20/5/1 10/5/1 2.5/2.5/2.5
		void ADI_ERROR_D( oapi::Sketchpad* skp, double pitch, double roll, double yaw, int adierr );// 20/5/1 10/5/1 2.5/2.5/2.5
		void ADI_ERROR_ORBIT( HDC hDC, double pitch, double roll, double yaw, int adierr );// 10/5/1
		void ADI_ERROR_ORBIT( oapi::Sketchpad* skp, double pitch, double roll, double yaw, int adierr );// 10/5/1

		void HSI_A( HDC hDC, double course, double roll, bool bearingon, double bearing, bool CDIflag, bool CDIbar, double CDIscale, double CDIdeviation, char primarytype, double primarybearing, char secondarytype, double secondarybearing );
		void HSI_A( oapi::Sketchpad* skp, double course, double roll, bool bearingon, double bearing, bool CDIflag, bool CDIbar, double CDIscale, double CDIdeviation, char primarytype, double primarybearing, char secondarytype, double secondarybearing );
		void HSI_E( HDC hDC, double course, bool bearingon, double bearing, bool CDIflag, bool CDIbar, double CDIscale, double CDIdeviation, char primarytype, double primarybearing, char secondarytype, double secondarybearing );
		void HSI_E( oapi::Sketchpad* skp, double course, bool bearingon, double bearing, bool CDIflag, bool CDIbar, double CDIscale, double CDIdeviation, char primarytype, double primarybearing, char secondarytype, double secondarybearing );
		void HSI_CourseArrow( HDC hDC );
		void HSI_CourseArrow( oapi::Sketchpad* skp );
		void HSI_CDI( HDC hDC, bool flag, bool bar, double scale, double deviation );
		void HSI_CDI( oapi::Sketchpad* skp, bool flag, bool bar, double scale, double deviation );
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

		void AEPFD_Header_AscentDAP( HDC hDC, int MM, int adiatt );
		void AEPFD_Header_AscentDAP( oapi::Sketchpad* skp, int MM, int adiatt );
		void AEPFD_Header_TransDAP( HDC hDC, int MM, int adiatt );
		void AEPFD_Header_TransDAP( oapi::Sketchpad* skp, int MM, int adiatt );
		void AEPFD_Header_AerojetDAP( HDC hDC, int MM, double vel );
		void AEPFD_Header_AerojetDAP( oapi::Sketchpad* skp, int MM, double vel );
		void AEPFD_BETA( HDC hDC );
		void AEPFD_BETA( oapi::Sketchpad* skp );
		void AEPFD_GMETER_STATIC( HDC hDC );
		void AEPFD_GMETER_STATIC( oapi::Sketchpad* skp );
		void AEPFD_GMETER_ACCEL( HDC hDC );
		void AEPFD_GMETER_ACCEL( oapi::Sketchpad* skp );
		void AEPFD_GMETER_NZ( HDC hDC );
		void AEPFD_GMETER_NZ( oapi::Sketchpad* skp );
		void AEPFD_HACCEL( HDC hDC );
		void AEPFD_HACCEL( oapi::Sketchpad* skp );
		void AEPFD_RANGERW( HDC hDC );
		void AEPFD_RANGERW( oapi::Sketchpad* skp );
		void AEPFD_RANGEHACC( HDC hDC );
		void AEPFD_RANGEHACC( oapi::Sketchpad* skp );
		void AEPFD_dAZ_HTA( HDC hDC );
		void AEPFD_dAZ_HTA( oapi::Sketchpad* skp );
		void AEPFD_dXTRK( HDC hDC );
		void AEPFD_dXTRK( oapi::Sketchpad* skp );
		void AEPFD_XTRK( HDC hDC );
		void AEPFD_XTRK( oapi::Sketchpad* skp );
		void AEPFD_dINC( HDC hDC );
		void AEPFD_dINC( oapi::Sketchpad* skp );
		void AEPFD_TGTINC( HDC hDC );
		void AEPFD_TGTINC( oapi::Sketchpad* skp );
		void AEPFD_GSI( HDC hDC, bool flag, double scale, double deviation );
		void AEPFD_GSI( oapi::Sketchpad* skp, bool flag, double scale, double deviation );

		inline bool GetFlash( void ) const
		{
			int SimT=(int)(oapiGetSimTime() * 2);
			return (SimT%2)==1;
		}

	protected:
		unsigned short usMDUID;
		dps::DEUCHAR textBuffer[51][26];
		dps::IDP* prim_idp;
		dps::IDP* sec_idp;
		bool bInverseX;
		bool bUseSecondaryPort;
		bool bPortConfigMan;
		EXTMFDSPEC mfdspec;
		DWORD mat_idx;
		double fBrightness;
		bool bPower;

		int display;
		int menu;

		std::vector<dps::DEU_LINE> lines;
		std::vector<dps::DEU_ELLIPSE> ellipses;
		std::vector<dps::DEU_PIXEL> pixels;

		//Use a paint buffer for storing primitives?
		virtual void RegisterMFDContext(int id);
		virtual void PrintToBuffer( const char* string, unsigned short length, unsigned short col, unsigned short row, char attributes );

		void DrawMenuButton( HDC hDC, int x );
		void DrawMenuButton( oapi::Sketchpad* skp, int x );

		void TogglePort( void );

	public:
		MDU(Atlantis* _sts, const string& _ident, unsigned short _usMDUID);
		virtual ~MDU();

		virtual bool OnReadState( FILEHANDLE scn ) override;
		virtual void OnSaveState( FILEHANDLE scn ) const override;
		virtual bool IsMultiLineSaveState() const override { return true; };

		//bool PrintChar(unsigned short x, unsigned short y, DEUCHAR c);
		//bool PrintString(unsigned short x, unsigned short y, char* pText, short sLength, char cAttr = DEUATT_NORMAL);
		//DEUCHAR GetTextBuffer(unsigned short x, unsigned short y) const;
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
		 * handle mouse events
		 * @sa BasicVCComponent::OnMouseEvent
		 */
		virtual bool OnMouseEvent(int _event, float x, float y) override;

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

		virtual void UpdateTextBuffer();


		//IDP interface functions
		/**
		 * Act like the curses function
		 */
		inline void mvprint( unsigned short x, unsigned short y, const char* pszLine, char attributes = 0 )
		{
			PrintToBuffer( pszLine, static_cast<unsigned short>(strlen( pszLine )), x, y, attributes );
		}

		/**
		 * Draw line on DEU.
		 * Coordinates should be between 0 and 511
		 */
		inline void Line(int x1, int y1, int x2, int y2, char attributes = 0)
		{
			dps::DEU_LINE line;
			line.x0 = x1;
			line.y0 = y1 + DPS_DISPLAY_VERTICAL_OFFSET;
			line.x1 = x2;
			line.y1 = y2 + DPS_DISPLAY_VERTICAL_OFFSET;
			line.cAttr = attributes;
			lines.push_back(line);
		}

		/**
		 * Draw ellipse on DEU.
		 * Coordinates should be between 0 and 511
		 */
		inline void Ellipse(int xLeft, int yTop, int xRight, int yBottom, char attributes = 0)
		{
			dps::DEU_ELLIPSE ellipse;
			ellipse.xLeft = xLeft;
			ellipse.yTop = yTop + DPS_DISPLAY_VERTICAL_OFFSET;
			ellipse.xRight = xRight;
			ellipse.yBottom = yBottom + DPS_DISPLAY_VERTICAL_OFFSET;
			ellipse.cAttr = attributes;
			ellipses.push_back(ellipse);
		}

		/**
		 * Draw circle on DEU.
		 * Coordinates should be between 0 and 511
		 */
		inline void Circle(int xCenter, int yCenter, int radius, char attributes = 0)
		{
			Ellipse(xCenter-radius, yCenter-radius, xCenter+radius, yCenter+radius, attributes);
		}

		/**
		 * Draws delta character at specified location on MDU.
		 */
		inline void Delta( unsigned int x, unsigned int y, char attributes = 0 )
		{
			assert( (x < 51) && "MDU::Delta.x" );
			assert( (y < 26) && "MDU::Delta.y" );

			textBuffer[x][y].cSymbol = 255;
			textBuffer[x][y].cAttr = attributes;
		}

		/**
		 * Draws theta character at specified location on MDU.
		 */
		inline void Theta( unsigned int x, unsigned int y, char attributes = 0 )
		{
			assert( (x < 51) && "MDU::Theta.x" );
			assert( (y < 26) && "MDU::Theta.y" );

			textBuffer[x][y].cSymbol = 253;
			textBuffer[x][y].cAttr = attributes;
		}

		/**
		 * Adds dot above specified character on MDU.
		 * This is usually used to signify rates (i.e. rdot or hdot).
		 */
		inline void DotCharacter(int x, int y, char attributes = 0)
		{
			dps::DEU_PIXEL pixel;
			pixel.cAttr = attributes;
			pixel.x = (10 * x) + 5;
			pixel.y = (14 * y) + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			pixel.x = (10 * x) + 4;
			//pixel.y = (14 * y) + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			pixel.x = (10 * x) + 5;
			pixel.y = (14 * y) - 1 + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );

			pixel.x = (10 * x) + 4;
			//pixel.y = (14 * y) - 1 + DPS_DISPLAY_VERTICAL_OFFSET;
			pixels.push_back( pixel );
		}

		/**
		 * Draws alpha character at specified location on MDU.
		 */
		inline void Alpha( unsigned int x, unsigned int y, char attributes = 0 )
		{
			assert( (x < 51) && "MDU::Alpha.x" );
			assert( (y < 26) && "MDU::Alpha.y" );

			textBuffer[x][y].cSymbol = 254;
			textBuffer[x][y].cAttr = attributes;
		}

		/**
		 * Draws sigma character at specified location on MDU.
		 */
		inline void Sigma( unsigned int x, unsigned int y, char attributes = 0 )
		{
			assert( (x < 51) && "MDU::Sigma.x" );
			assert( (y < 26) && "MDU::Sigma.y" );

			textBuffer[x][y].cSymbol = 252;
			textBuffer[x][y].cAttr = attributes;
		}

		/**
		* Draws omega character at specified location on MDU.
		*/
		inline void Omega(unsigned int x, unsigned int y, char attributes = 0)
		{
			assert((x < 51) && "MDU::Omega.x");
			assert((y < 26) && "MDU::Omega.y");

			textBuffer[x][y].cSymbol = 251;
			textBuffer[x][y].cAttr = attributes;
		}

		/**
		 * Draws up arrow character at specified location on MDU.
		 */
		inline void UpArrow( unsigned int x, unsigned int y, char attributes = 0 )
		{
			assert( (x < 51) && "MDU::UpArrow.x" );
			assert( (y < 26) && "MDU::UpArrow.y" );

			textBuffer[x][y].cSymbol = 247;
			textBuffer[x][y].cAttr = attributes;
		}

		/**
		 * Draws down arrow character at specified location on MDU.
		 */
		inline void DownArrow( unsigned int x, unsigned int y, char attributes = 0 )
		{
			assert( (x < 51) && "MDU::DownArrow.x" );
			assert( (y < 26) && "MDU::DownArrow.y" );

			textBuffer[x][y].cSymbol = 248;
			textBuffer[x][y].cAttr = attributes;
		}

		/**
		 * Draws left arrow character at specified location on MDU.
		 */
		inline void LeftArrow( unsigned int x, unsigned int y, char attributes = 0 )
		{
			assert( (x < 51) && "MDU::LeftArrow.x" );
			assert( (y < 26) && "MDU::LeftArrow.y" );

			textBuffer[x][y].cSymbol = 246;
			textBuffer[x][y].cAttr = attributes;
		}

		/**
		 * Draws right arrow character at specified location on MDU.
		 */
		inline void RightArrow( unsigned int x, unsigned int y, char attributes = 0 )
		{
			assert( (x < 51) && "MDU::RightArrow.x" );
			assert( (y < 26) && "MDU::RightArrow.y" );

			textBuffer[x][y].cSymbol = 245;
			textBuffer[x][y].cAttr = attributes;
		}

		/**
		 * Draws the orbiter symbol, as viewed from the top at specified location on MDU.
		 */
		inline void OrbiterSymbolTop( int x, int y, char attributes = 0 )
		{
			dps::DEU_PIXEL pixel;
			pixel.cAttr = attributes;

			for (int i = 0; i < ORBITER_TOP_COUNT; i++)
			{
				pixel.x = ORBITER_TOP_X[i] + x;
				pixel.y = ORBITER_TOP_Y[i] + y + DPS_DISPLAY_VERTICAL_OFFSET;
				pixels.push_back( pixel );
			}
		}

		inline void OrbiterSymbolSide( int x, int y, double rotation, char attributes = 0 )
		{
			double sinrot = sin( rotation );
			double cosrot = cos( rotation );

			dps::DEU_PIXEL pixel;
			pixel.cAttr = attributes;

			for (int i = 0; i < ORBITER_SIDE_COUNT; i++)
			{
				pixel.x = Round( (ORBITER_SIDE_X[i] * cosrot) - (ORBITER_SIDE_Y[i] * sinrot) ) + x ;
				pixel.y = Round( (ORBITER_SIDE_X[i] * sinrot) + (ORBITER_SIDE_Y[i] * cosrot) ) + y + DPS_DISPLAY_VERTICAL_OFFSET;
				pixels.push_back( pixel );
			}
		}

		/**
		 * Draw a square on DEU.
		 */
		inline void Square( int x, int y, char attributes = 0 )
		{
			dps::DEU_LINE line;
			line.cAttr = attributes;
			line.x0 = x - 5;
			line.y0 = y - 5 + DPS_DISPLAY_VERTICAL_OFFSET;
			line.x1 = x + 5;
			line.y1 = line.y0;
			lines.push_back( line );

			line.x0 = x + 5;
			line.y0 = y - 5 + DPS_DISPLAY_VERTICAL_OFFSET;
			line.x1 = line.x0;
			line.y1 = y + 5 + DPS_DISPLAY_VERTICAL_OFFSET;
			lines.push_back( line );

			line.x0 = x + 5;
			line.y0 = y + 5 + DPS_DISPLAY_VERTICAL_OFFSET;
			line.x1 = x - 5;
			line.y1 = line.y0;
			lines.push_back( line );

			line.x0 = x - 5;
			line.y0 = y + 5 + DPS_DISPLAY_VERTICAL_OFFSET;
			line.x1 = line.x0;
			line.y1 = y - 5 + DPS_DISPLAY_VERTICAL_OFFSET;
			lines.push_back( line );
			return;
		}

		/**
		 * Draw a thick dot on DEU.
		 */
		inline void ThickDot( int x, int y, char attributes = 0 )
		{
			dps::DEU_PIXEL pixel;
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
			pixels.push_back( pixel );
			return;
		}

		/**
		 * Draw a filled left arrow on DEU.
		 */
		inline void LeftArrowFilled( int x, int y, char attributes = 0 )
		{
			dps::DEU_LINE line;
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

			dps::DEU_PIXEL pixel;
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
			pixels.push_back( pixel );
		}

		/**
		 * Draw a hollow left arrow on DEU.
		 */
		inline void LeftArrowHollow( int x, int y, char attributes = 0 )
		{
			Line( x, y, x + 5, y + 5, attributes );
			Line( x, y, x + 5, y - 5, attributes );

			Line( x + 5, y + 3, x + 13, y + 3, attributes );
			Line( x + 13, y + 3, x + 13, y - 3, attributes );
			Line( x + 5, y - 3, x + 13, y - 3, attributes );
			return;
		}

		/**
		 * Draws a right-pointing triangle on the DEU (coordinates refer to the tip).
		 */
		inline void RightTriangle( int x, int y, char attributes = 0 )
		{
			Line( x + 8, y, x, y + 6, attributes );
			Line( x, y + 6, x, y - 6, attributes );
			Line( x, y - 6, x + 8, y, attributes );
			return;
		}

		/**
		 * Draws a left-pointing triangle on the DEU (coordinates refer to the tip).
		 */
		inline void LeftTriangle( int x, int y, char attributes = 0 )
		{
			Line( x, y, x + 8, y + 6, attributes );
			Line( x + 8, y + 6, x + 8, y - 6, attributes );
			Line( x + 8, y - 6, x, y, attributes );
			return;
		}

		/**
		 * Draws sign of number at specified location on MDU.
		 */
		inline void NumberSign( int x, int y, double number, char attributes = 0 )
		{
			if (number > 0.0) mvprint( x, y, "+", attributes );
			else if (number < 0.0) mvprint( x, y, "-", attributes );
			else mvprint( x, y, " ", attributes );
		}

		/**
		 * Draws sign of number with brackets at specified location on MDU.
		 */
		inline void NumberSignBracket( int x, int y, double number, char attributes = 0 )
		{
			if (number > 0.0) mvprint( x, y, "+", attributes );
			else if (number < 0.0) mvprint( x, y, "-", attributes );
			else mvprint( x, y, " ", attributes );

			Line( x * 10, (y * 14) + 1, (x * 10) + 3, (y * 14) + 1, attributes );
			Line( x * 10, (y * 14) + 12, (x * 10) + 3, (y * 14) + 12, attributes );

			Line( (x * 10) + 9, (y * 14) + 1, (x * 10) + 6, (y * 14) + 1, attributes );
			Line( (x * 10) + 9, (y * 14) + 12, (x * 10) + 6, (y * 14) + 12, attributes );

			Line( x * 10, y * 14, x * 10, (y * 14) + 12, attributes );
			Line( (x * 10) + 9, y * 14, (x * 10) + 9, (y * 14) + 12, attributes );
		}

		/**
		 * Draws underline the character at the specified location on MDU.
		 */
		inline void Underline( int x, int y, char attributes = 0 )
		{
			Line( (x * 10) + 1, (y * 14) + 14, (x * 10) + 9, (y * 14) + 14, attributes );
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

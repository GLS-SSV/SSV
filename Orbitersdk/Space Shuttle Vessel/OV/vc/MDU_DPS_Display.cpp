/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2020/08/30   GLS
2020/09/07   GLS
2021/06/06   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
2025/01/23   GLS
********************************************/
#include "MDU.h"
#include "../Atlantis.h"
#include "../dps/IDP.h"


namespace vc
{
	constexpr unsigned char ATT_GREEN = 0x00;
	constexpr unsigned char ATT_YELLOW = 0x01;
	constexpr unsigned char ATT_ORANGE = 0x02;
	//constexpr unsigned char ATT_FLASH = 0x10;
	constexpr unsigned char ATT_DASHED = 0x20;
	constexpr unsigned char ATT_LARGE = 0x80;

	constexpr short MDU_DPS_DISPLAY_Y_OFFSET = 64;// offset between top of MDU and top of DPS display
	constexpr short MDU_DPS_DISPLAY_CHAR_Y_CORRECTION = 3;// correction to char vertical position due to font

	void MDU::DPS( HDC hDC )
	{
		// draw DPS display
		DPS_use_HDC = true;
		hDC_DPS = hDC;

		if (prim_idp)
		{
			prim_idp->OnPaint( this );
		}
		else
		{
			//PrintToBuffer( "ERROR: IDP NOT CONNECTED", 24, 0, 0, 0 );
		}

		// driving IDP and active keyboards display
		SelectObject( hDC, gdiNormalPen );
		Rectangle( hDC, 472, 830, 552, 906 );
		SelectObject( hDC, gdiSSVAFont_h40w34 );
		SetTextColor( hDC, CR_DPS_GREEN );
		char cbuf[2];
		sprintf_s( cbuf, 2, "%d", GetDrivingIDP() );
		TextOut( hDC, 494, 846, cbuf, 1 );
		int kb = GetIDP()->GetActiveKeyboard();
		if ((kb & 1) == 1)// CDR
		{
			SelectObject( hDC, gdiRedPen );
			SelectObject( hDC, gdiRedBrush );
			Rectangle( hDC, 220, 876, 470, 886 );
		}
		if ((kb & 2) == 2)// PLT
		{
			SelectObject( hDC, gdiYellowPen );
			SelectObject( hDC, gdiYellowBrush );
			Rectangle( hDC, 554, 876, 804, 886 );
		}
		return;
	}

	void MDU::DPS( oapi::Sketchpad* skp )
	{
		// draw DPS display
		DPS_use_HDC = false;
		skp_DPS = skp;

		if (prim_idp)
		{
			prim_idp->OnPaint( this );
		}
		else
		{
			//PrintToBuffer( "ERROR: IDP NOT CONNECTED", 24, 0, 0, 0 );
		}

		// driving IDP and active keyboards display
		skp->SetPen( skpNormalPen );
		skp->Rectangle( 472, 830, 552, 906 );
		skp->SetFont( skpSSVAFont_h40w34 );
		skp->SetTextColor( CR_DPS_GREEN );
		char cbuf[2];
		sprintf_s( cbuf, 2, "%d", GetDrivingIDP() );
		skp->Text( 494, 846, cbuf, 1 );
		int kb = GetIDP()->GetActiveKeyboard();
		if ((kb & 1) == 1)// CDR
		{
			skp->SetPen( skpRedPen );
			skp->SetBrush( skpRedBrush );
			skp->Rectangle( 220, 876, 470, 886 );
		}
		if ((kb & 2) == 2)// PLT
		{
			skp->SetPen( skpYellowPen );
			skp->SetBrush( skpYellowBrush );
			skp->Rectangle( 554, 876, 804, 886 );
		}
		return;
	}

	void MDU::Text( const short x, const short y, const char* txt, const unsigned int len, const unsigned char attributes, const double rot )
	{
		bool large = (attributes & ATT_LARGE) != 0;
		double* fontrot = large ? &fontrotlarge : &fontrotsmall;

		if (DPS_use_HDC)
		{
			// hDC
			if ((attributes & ATT_YELLOW) != 0) SetTextColor( hDC_DPS, CR_YELLOW );
			else if ((attributes & ATT_ORANGE) != 0) SetTextColor( hDC_DPS, CR_RED );
			else SetTextColor( hDC_DPS, CR_DPS_GREEN );

			// select font
			if (fabs( rot ) < 5)// "default font" close enough?
			{
				SelectObject( hDC_DPS, large ? gdiSSVAFont_h22w22 : gdiSSVAFont_h19w19 );
			}
			else if (fabs( rot - *fontrot ) < 5)// "rotated font" close enough?
			{
				SelectObject( hDC_DPS, large ? gdiSSVAFont_h22w22rot : gdiSSVAFont_h19w19rot );
			}
			else// create new "rotated font"
			{
				DeleteObject( large ? gdiSSVAFont_h22w22rot : gdiSSVAFont_h19w19rot );

				*fontrot = rot;

				if (large)
				{
					if (!(gdiSSVAFont_h22w22rot = CreateFont( 22, 22, -static_cast<int>(*fontrot * 10), -static_cast<int>(*fontrot * 10), FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FIXED_PITCH, "SSV_Font_A" )))
					{
						throw std::exception( "CreateFont() failed" );
					}
				}
				else
				{
					if (!(gdiSSVAFont_h19w19rot = CreateFont( 19, 19, -static_cast<int>(*fontrot * 10), -static_cast<int>(*fontrot * 10), FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FIXED_PITCH, "SSV_Font_A" )))
					{
						throw std::exception( "CreateFont() failed" );
					}
				}

				SelectObject( hDC_DPS, large ? gdiSSVAFont_h22w22rot : gdiSSVAFont_h19w19rot );
			}

			TextOut( hDC_DPS, x, y + MDU_DPS_DISPLAY_Y_OFFSET + MDU_DPS_DISPLAY_CHAR_Y_CORRECTION, txt, len );
		}
		else
		{
			// Sketchpad
			if ((attributes & ATT_YELLOW) != 0) skp_DPS->SetTextColor( CR_YELLOW );
			else if ((attributes & ATT_ORANGE) != 0) skp_DPS->SetTextColor( CR_RED );
			else skp_DPS->SetTextColor( CR_DPS_GREEN );

			// select font
			skp_DPS->SetFont( large ? skpSSVAFont_h22w22 : skpSSVAFont_h19w19 );
			if (rot != 0)
			{
				skp_DPS->TextEx( static_cast<float>(x), static_cast<float>(y + MDU_DPS_DISPLAY_Y_OFFSET + MDU_DPS_DISPLAY_CHAR_Y_CORRECTION), txt, 1.0f, static_cast<float>(-rot) );
			}
			else
			{
				skp_DPS->Text( x, y + MDU_DPS_DISPLAY_Y_OFFSET + MDU_DPS_DISPLAY_CHAR_Y_CORRECTION, txt, len );
			}
		}
		return;
	}

	void MDU::Line( const short x1, const short y1, const short x2, const short y2, const char attributes )
	{
		if (DPS_use_HDC)
		{
			// hDC
			if ((attributes & ATT_YELLOW) != 0) SelectObject( hDC_DPS, gdiOverbrightPen );
			else if ((attributes & ATT_DASHED) != 0) SelectObject( hDC_DPS, gdiDashedNormalPen );
			else if ((attributes & ATT_ORANGE) != 0) SelectObject( hDC_DPS, gdiRedPen );
			else SelectObject( hDC_DPS, gdiNormalPen );

			MoveToEx( hDC_DPS, x1, y1 + MDU_DPS_DISPLAY_Y_OFFSET, NULL );
			LineTo( hDC_DPS, x2, y2 + MDU_DPS_DISPLAY_Y_OFFSET );
		}
		else
		{
			// Sketchpad
			if ((attributes& ATT_YELLOW) != 0) skp_DPS->SetPen( skpOverbrightPen );
			else if ((attributes & ATT_DASHED) != 0) skp_DPS->SetPen( skpDashedNormalPen );
			else if ((attributes & ATT_ORANGE) != 0) skp_DPS->SetPen( skpRedPen );
			else skp_DPS->SetPen( skpNormalPen );

			skp_DPS->Line( x1, y1 - 1 + MDU_DPS_DISPLAY_Y_OFFSET, x2, y2 - 1 + MDU_DPS_DISPLAY_Y_OFFSET );// 1px up to match GDI
		}
		return;
	}

	void MDU::Circle( const short x, const short y, const unsigned short r, const char attributes )
	{
		if (DPS_use_HDC)
		{
			// hDC
			if (attributes == ATT_YELLOW) SelectObject( hDC_DPS, gdiOverbrightPen );
			else SelectObject( hDC_DPS, gdiNormalPen );

			::Ellipse( hDC_DPS, x - r, y - r + MDU_DPS_DISPLAY_Y_OFFSET, x + r, y + r + MDU_DPS_DISPLAY_Y_OFFSET );
		}
		else
		{
			// Sketchpad
			if (attributes == ATT_YELLOW) skp_DPS->SetPen( skpOverbrightPen );
			else skp_DPS->SetPen( skpNormalPen );

			skp_DPS->Ellipse( x - r, y - r + MDU_DPS_DISPLAY_Y_OFFSET, x + r, y + r + MDU_DPS_DISPLAY_Y_OFFSET );
		}
		return;
	}
}

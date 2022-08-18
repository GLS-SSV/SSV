/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2020/08/30   GLS
2020/09/07   GLS
2021/06/06   GLS
2021/08/24   GLS
2022/08/05   GLS
********************************************/
#include "MDU.h"
#include "../Atlantis.h"
#include "../dps/IDP.h"


extern GDIParams g_Param;


namespace vc
{
	//find location on bitmap of letter
	void BitmapLocation( unsigned char ch, int &x, int &y )
	{
		/*
		max size on bitmap: 18*28

		size on mdu: 10*14

		box on bitmap; 32*32

		display:
		32 top offset
		364 text height
		*/
		int row = ch / 16;
		int col = ch - (16 * row);
		x = 7 + 32 * col;
		y = 2 + 32 * row;
	}

	void MDU::DPS( HDC hDC )
	{
		UpdateTextBuffer();

		bool flash = GetFlash();

		// main text
		for (int i = 0; i < 51; i++)
		{
			for (int j = 0; j < 24; j++)
			{
				if (textBuffer[i][j].cSymbol >= '!')
				{
					if (((textBuffer[i][j].cAttr & dps::DEUATT_FLASHING) == 0) || (flash == true))
					{
						int x, y;
						vc::BitmapLocation( textBuffer[i][j].cSymbol, x, y );

						if ((textBuffer[i][j].cAttr & dps::DEUATT_OVERBRIGHT) != 0)
						{
							// overbright intensity
							BitBlt( hDC, i * 10, j * 14 + DPS_DISPLAY_VERTICAL_OFFSET, 10, 14, g_Param.DeuCharOvrBrgtBitmapDC, (int)(x * 0.555555), (int)(y * 0.5), SRCCOPY );
						}
						else
						{
							// default
							// normal intensity
							BitBlt( hDC, i * 10, j * 14 + DPS_DISPLAY_VERTICAL_OFFSET, 10, 14, g_Param.DeuCharBitmapDC, (int)(x * 0.555555), (int)(y * 0.5), SRCCOPY );
						}
					}
				}
			}
		}

		// fault line
		for (int i = 0; i < 51; i++)
		{
			if (textBuffer[i][24].cSymbol >= '!')
			{
				if (((textBuffer[i][24].cAttr & dps::DEUATT_FLASHING) == 0) || (flash == true))
				{
					int x, y;
					vc::BitmapLocation( textBuffer[i][24].cSymbol, x, y );

					BitBlt( hDC, i * 10, 24 * 14 + DPS_DISPLAY_VERTICAL_OFFSET, 10, 14, g_Param.DeuCharFaultBitmapDC, (int)(x * 0.555555), (int)(y * 0.5), SRCCOPY );
				}
			}
		}

		// scratchpad line
		for (int i = 0; i < 51; i++)
		{
			if (textBuffer[i][25].cSymbol >= '!')
			{
				if (((textBuffer[i][25].cAttr & dps::DEUATT_FLASHING) == 0) || (flash == true))
				{
					int x, y;
					vc::BitmapLocation( textBuffer[i][25].cSymbol, x, y );

					BitBlt( hDC, i * 10, 25 * 14 + DPS_DISPLAY_VERTICAL_OFFSET, 10, 14, g_Param.DeuCharBitmapDC, (int)(x * 0.555555), (int)(y * 0.5), SRCCOPY );
				}
			}
		}

		for (unsigned int i = 0; i < lines.size(); i++)
		{
			if (((lines[i].cAttr & dps::DEUATT_FLASHING) == 0) || flash)
			{
				if ((lines[i].cAttr & dps::DEUATT_OVERBRIGHT) != 0) SelectObject( hDC, gdiOverbrightPen );
				else if ((lines[i].cAttr & dps::DEUATT_DASHED) != 0) SelectObject( hDC, gdiDashedNormalPen );
				else SelectObject( hDC, gdiNormalPen );
				MoveToEx( hDC, lines[i].x0, lines[i].y0, NULL );
				LineTo( hDC, lines[i].x1, lines[i].y1 );
			}
		}
		for (unsigned int i = 0; i < ellipses.size(); i++)
		{
			if (ellipses[i].cAttr != dps::DEUATT_FLASHING || flash)
			{
				if (ellipses[i].cAttr == dps::DEUATT_OVERBRIGHT) SelectObject( hDC, gdiOverbrightPen );
				else SelectObject( hDC, gdiNormalPen );
				::Ellipse( hDC, ellipses[i].xLeft, ellipses[i].yTop, ellipses[i].xRight, ellipses[i].yBottom );
			}
		}
		for (unsigned int i = 0; i < pixels.size(); i++)
		{
			if (((pixels[i].cAttr & dps::DEUATT_FLASHING) == 0) || flash)
			{
				if ((pixels[i].cAttr & dps::DEUATT_OVERBRIGHT) != 0) SetPixel( hDC, pixels[i].x, pixels[i].y, CR_DPS_OVERBRIGHT );
				else SetPixel( hDC, pixels[i].x, pixels[i].y, CR_DPS_NORMAL );
			}
		}

		// driving IDP and active keyboards display
		SelectObject( hDC, gdiNormalPen );
		Rectangle( hDC, 236, 415, 276, 453 );
		SelectObject( hDC, gdiSSVAFont_h20w17 );
		SetTextColor( hDC, CR_DPS_NORMAL );
		char cbuf[2];
		sprintf_s( cbuf, 2, "%d", GetDrivingIDP() );
		TextOut( hDC, 247, 423, cbuf, 1 );
		int kb = GetIDP()->GetActiveKeyboard();
		if ((kb & 1) == 1)// CDR
		{
			SelectObject( hDC, gdiRedPen );
			SelectObject( hDC, gdiRedBrush );
			Rectangle( hDC, 110, 438, 235, 443 );
		}
		if ((kb & 2) == 2)// PLT
		{
			SelectObject( hDC, gdiYellowPen );
			SelectObject( hDC, gdiYellowBrush );
			Rectangle( hDC, 277, 438, 402, 443 );
		}
		return;
	}

	void MDU::DPS( oapi::Sketchpad* skp )
	{
		UpdateTextBuffer();

		bool flash = GetFlash();
		RECT src;
		RECT tgt;

		//draw stuff
		for (int i = 0; i < 51; i++)
		{
			for (int j = 0; j < 24; j++)
			{
				if (textBuffer[i][j].cSymbol >= '!')
				{
					if (((textBuffer[i][j].cAttr & dps::DEUATT_FLASHING) == 0) || (flash == true))
					{
						int x, y;
						vc::BitmapLocation( textBuffer[i][j].cSymbol, x, y );

						if ((textBuffer[i][j].cAttr & dps::DEUATT_OVERBRIGHT) != 0)
						{
							// overbright intensity
							src.left = x;
							src.top = y;
							src.right = src.left + 18;
							src.bottom = src.top + 28;
							tgt.left = i * 10;
							tgt.top = j * 14 + DPS_DISPLAY_VERTICAL_OFFSET;
							tgt.right = tgt.left + 10;
							tgt.bottom = tgt.top + 14;
							skp->StretchRect( g_Param.deu_characters_overbrightSH, &src, &tgt );
						}
						else
						{
							// default
							// normal intensity
							src.left = x;
							src.top = y;
							src.right = src.left + 18;
							src.bottom = src.top + 28;
							tgt.left = i * 10;
							tgt.top = j * 14 + DPS_DISPLAY_VERTICAL_OFFSET;
							tgt.right = tgt.left + 10;
							tgt.bottom = tgt.top + 14;
							skp->StretchRect( g_Param.deu_charactersSH, &src, &tgt );
						}
					}
				}
			}
		}

		// fault line
		for (int i = 0; i < 51; i++)
		{
			if (textBuffer[i][24].cSymbol >= '!')
			{
				if (((textBuffer[i][24].cAttr & dps::DEUATT_FLASHING) == 0) || (flash == true))
				{
					int x, y;
					vc::BitmapLocation( textBuffer[i][24].cSymbol, x, y );

					src.left = x;
					src.top = y;
					src.right = src.left + 18;
					src.bottom = src.top + 28;
					tgt.left = i * 10;
					tgt.top = 24 * 14 + DPS_DISPLAY_VERTICAL_OFFSET;
					tgt.right = tgt.left + 10;
					tgt.bottom = tgt.top + 14;
					skp->StretchRect( g_Param.deu_characters_faultSH, &src, &tgt );
				}
			}
		}

		// scratchpad line
		for (int i = 0; i < 51; i++)
		{
			if (textBuffer[i][25].cSymbol >= '!')
			{
				if (((textBuffer[i][25].cAttr & dps::DEUATT_FLASHING) == 0) || (flash == true))
				{
					int x, y;
					vc::BitmapLocation( textBuffer[i][25].cSymbol, x, y );

					src.left = x;
					src.top = y;
					src.right = src.left + 18;
					src.bottom = src.top + 28;
					tgt.left = i * 10;
					tgt.top = 25 * 14 + DPS_DISPLAY_VERTICAL_OFFSET;
					tgt.right = tgt.left + 10;
					tgt.bottom = tgt.top + 14;
					skp->StretchRect( g_Param.deu_charactersSH, &src, &tgt );
				}
			}
		}

		for (unsigned int i = 0; i < lines.size(); i++)
		{
			if (((lines[i].cAttr & dps::DEUATT_FLASHING) == 0) || flash)
			{
				if ((lines[i].cAttr & dps::DEUATT_OVERBRIGHT) != 0) skp->SetPen( skpOverbrightPen );
				else if ((lines[i].cAttr & dps::DEUATT_DASHED) != 0) skp->SetPen( skpDashedNormalPen );
				else skp->SetPen( skpNormalPen );
				skp->Line( lines[i].x0, lines[i].y0 - 1, lines[i].x1, lines[i].y1 - 1 );// 1px up to match GDI
			}
		}
		for (unsigned int i = 0; i < ellipses.size(); i++)
		{
			if (ellipses[i].cAttr != dps::DEUATT_FLASHING || flash)
			{
				if (ellipses[i].cAttr == dps::DEUATT_OVERBRIGHT) skp->SetPen( skpOverbrightPen );
				else skp->SetPen( skpNormalPen );
				skp->Ellipse( ellipses[i].xLeft, ellipses[i].yTop, ellipses[i].xRight, ellipses[i].yBottom );
			}
		}
		for (unsigned int i = 0; i < pixels.size(); i++)
		{
			if (((pixels[i].cAttr & dps::DEUATT_FLASHING) == 0) || flash)
			{
				if ((pixels[i].cAttr & dps::DEUATT_OVERBRIGHT) != 0) skp->Pixel( pixels[i].x, pixels[i].y, CR_DPS_OVERBRIGHT );
				else skp->Pixel( pixels[i].x, pixels[i].y, CR_DPS_NORMAL );
			}
		}

		// driving IDP and active keyboards display
		skp->SetPen( skpNormalPen );
		skp->Rectangle( 236, 415, 276, 453 );
		skp->SetFont( skpSSVAFont_h20w17 );
		skp->SetTextColor( CR_DPS_NORMAL );
		char cbuf[2];
		sprintf_s( cbuf, 2, "%d", GetDrivingIDP() );
		skp->Text( 247, 423, cbuf, 1 );
		int kb = GetIDP()->GetActiveKeyboard();
		if ((kb & 1) == 1)// CDR
		{
			skp->SetPen( skpRedPen );
			skp->SetBrush( skpRedBrush );
			skp->Rectangle( 110, 438, 235, 443 );
		}
		if ((kb & 2) == 2)// PLT
		{
			skp->SetPen( skpYellowPen );
			skp->SetBrush( skpYellowBrush );
			skp->Rectangle( 277, 438, 402, 443 );
		}
		return;
	}
};

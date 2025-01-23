/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2020/08/24   GLS
2020/08/30   GLS
2020/09/07   GLS
2021/08/24   GLS
2022/01/10   GLS
2022/02/17   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/10/09   GLS
2022/10/12   GLS
2022/11/09   GLS
2022/12/17   GLS
2023/08/28   GLS
2024/05/14   GLS
2025/01/23   GLS
********************************************/
#include "MDU.h"
#include "../dps/IDP.h"
#include <MathSSV.h>


namespace vc
{
	void MDU::OMSMPS( HDC hDC )
	{
		unsigned short usNum;
		char cbuf[16];

		SetTextColor( hDC, CR_DARK_GREEN );
		SelectObject( hDC, gdiSSVBFont_h36w18 );
		SelectObject( hDC, gdiDarkGreenPen );
		SelectObject( hDC, gdiBlackBrush );

		TextOut( hDC, 152, 2, "OMS", 3 );
		TextOut( hDC, 602, 2, "MPS", 3 );
		MoveToEx( hDC, 326, 24, NULL );
		LineTo( hDC, 326, 792 );
		MoveToEx( hDC, 58, 24, NULL );
		LineTo( hDC, 112, 24 );
		MoveToEx( hDC, 230, 24, NULL );
		LineTo( hDC, 584, 24 );
		MoveToEx( hDC, 670, 24, NULL );
		LineTo( hDC, 960, 24 );
		MoveToEx( hDC, 58, 24, NULL );
		LineTo( hDC, 58, 90 );
		MoveToEx( hDC, 960, 24, NULL );
		LineTo( hDC, 960, 90 );

		SetTextColor( hDC, CR_WHITE );
		SelectObject( hDC, gdiSSVAFont_h19w19bold );

		//OMS
		TextOut( hDC, 146, 56, "L", 1 );
		TextOut( hDC, 248, 56, "R", 1 );
		Rectangle( hDC, 110, 84, 198, 118 );
		Rectangle( hDC, 214, 84, 302, 118 );
		Rectangle( hDC, 110, 302, 198, 336 );
		Rectangle( hDC, 214, 302, 302, 336 );
		Rectangle( hDC, 112, 550, 184, 600 );
		Rectangle( hDC, 220, 550, 292, 600 );
		//MPS
		TextOut( hDC, 634, 56, "L/2", 3 );
		TextOut( hDC, 744, 44, "C/1", 3 );
		TextOut( hDC, 852, 56, "R/3", 3 );
		//Tank P
		Rectangle( hDC, 422, 84, 510, 118 );
		Rectangle( hDC, 616, 84, 704, 118 );
		Rectangle( hDC, 728, 72, 816, 106 );
		Rectangle( hDC, 840, 84, 928, 118 );
		//Reg Press
		Rectangle( hDC, 422, 302, 510, 336 );
		Rectangle( hDC, 616, 302, 704, 336 );
		Rectangle( hDC, 728, 290, 816, 326 );
		Rectangle( hDC, 840, 302, 928, 336 );
		//Engine Pc
		TextOut( hDC, 626, 520, "L/2", 3 );
		TextOut( hDC, 732, 492, "C/1", 3 );
		TextOut( hDC, 844, 520, "R/3", 3 );
		Rectangle( hDC, 620, 550, 692, 600 );
		Rectangle( hDC, 724, 520, 796, 570 );
		Rectangle( hDC, 840, 550, 912, 600 );
		// ENG MANF
		Rectangle( hDC, 352, 594, 424, 628 );
		Rectangle( hDC, 454, 594, 526, 628 );

		SelectObject(hDC, gdiWhitePen);

		//OMS
		TextOut( hDC, 64, 136, "He", 2 );
		TextOut( hDC, 64, 170, "TK", 2 );
		TextOut( hDC, 72, 204, "P", 1 );
		Rectangle( hDC, 136, 136, 174, 258 );
		Rectangle( hDC, 240, 136, 278, 258 );
		MoveToEx( hDC, 172, 220, NULL );
		LineTo( hDC, 192, 220 );
		MoveToEx( hDC, 276, 220, NULL );
		LineTo( hDC, 296, 220 );

		TextOut( hDC, 64, 366, "N", 1 );
		TextOut( hDC, 84, 372, "2", 1 );
		TextOut( hDC, 64, 400, "TK", 2 );
		TextOut( hDC, 72, 434, "P", 1 );
		Rectangle( hDC, 136, 354, 174, 476 );
		Rectangle( hDC, 240, 354, 278, 476 );
		MoveToEx( hDC, 172, 426, NULL );
		LineTo( hDC, 192, 426 );
		MoveToEx( hDC, 276, 426, NULL );
		LineTo( hDC, 296, 426 );

		TextOut( hDC, 136, 520, "L", 1 );
		TextOut( hDC, 242, 520, "R", 1 );
		TextOut( hDC, 70, 670, "Pc", 2 );
		TextOut( hDC, 82, 716, "%", 1 );
		Rectangle( hDC, 128, 612, 168, 806 );
		Rectangle( hDC, 236, 612, 276, 806 );
		MoveToEx( hDC, 166, 678, NULL );
		LineTo( hDC, 186, 678 );
		MoveToEx( hDC, 274, 678, NULL );
		LineTo( hDC, 294, 678 );

		//MPS
		TextOut( hDC, 426, 56, "PNEU", 4 );
		TextOut( hDC, 348, 182, "TANK", 4 );
		TextOut( hDC, 378, 216, "P", 1 );
		Rectangle( hDC, 448, 136, 486, 258 );
		TextOut( hDC, 564, 136, "He", 2 );
		TextOut( hDC, 546, 170, "TANK", 4 );
		TextOut( hDC, 570, 204, "P", 1 );
		Rectangle( hDC, 642, 136, 680, 258 );
		Rectangle( hDC, 754, 136, 792, 258 );
		Rectangle( hDC, 866, 136, 904, 258 );
		MoveToEx( hDC, 484, 208, NULL );
		LineTo( hDC, 504, 208 );
		MoveToEx( hDC, 678, 250, NULL );
		LineTo( hDC, 698, 250 );
		MoveToEx( hDC, 790, 250, NULL );
		LineTo( hDC, 810, 250 );
		MoveToEx( hDC, 902, 250, NULL );
		LineTo( hDC, 922, 250 );

		TextOut( hDC, 356, 366, "REG", 3 );
		TextOut( hDC, 378, 404, "P", 1 );
		Rectangle( hDC, 448, 354, 486, 476 );
		TextOut( hDC, 550, 358, "He", 2 );
		TextOut( hDC, 532, 392, "REG A", 5 );
		TextOut( hDC, 570, 426, "P", 1 );
		Rectangle( hDC, 642, 354, 680, 476 );
		Rectangle( hDC, 754, 354, 792, 476 );
		Rectangle( hDC, 866, 354, 904, 476 );
		MoveToEx( hDC, 484, 392, NULL );
		LineTo( hDC, 504, 392 );
		MoveToEx( hDC, 484, 442, NULL );
		LineTo( hDC, 504, 442 );
		MoveToEx( hDC, 678, 392, NULL );
		LineTo( hDC, 698, 392 );
		MoveToEx( hDC, 678, 442, NULL );
		LineTo( hDC, 698, 442 );
		MoveToEx( hDC, 790, 392, NULL );
		LineTo( hDC, 810, 392 );
		MoveToEx( hDC, 790, 442, NULL );
		LineTo( hDC, 810, 442 );
		MoveToEx( hDC, 902, 392, NULL );
		LineTo( hDC, 922, 392 );
		MoveToEx( hDC, 902, 442, NULL );
		LineTo( hDC, 922, 442 );

		TextOut( hDC, 686, 670, "Pc", 2 );
		TextOut( hDC, 698, 694, "%", 1 );
		TextOut( hDC, 796, 670, "Pc", 2 );
		TextOut( hDC, 808, 694, "%", 1 );
		Rectangle( hDC, 636, 612, 676, 806 );
		Rectangle( hDC, 742, 612, 782, 806 );
		Rectangle( hDC, 856, 612, 896, 806 );
		MoveToEx( hDC, 674, 630, NULL );
		LineTo( hDC, 694, 630 );
		MoveToEx( hDC, 780, 630, NULL );
		LineTo( hDC, 800, 630 );
		MoveToEx( hDC, 894, 630, NULL );
		LineTo( hDC, 914, 630 );
		MoveToEx( hDC, 674, 738, NULL );
		LineTo( hDC, 694, 738 );
		MoveToEx( hDC, 780, 738, NULL );
		LineTo( hDC, 800, 738 );
		MoveToEx( hDC, 894, 738, NULL );
		LineTo( hDC, 914, 738 );

		TextOut( hDC, 364, 524, "ENG MANF", 8 );
		TextOut( hDC, 358, 558, "LO2", 3 );
		TextOut( hDC, 458, 558, "LH2", 3 );
		TextOut( hDC, 430, 632, "P", 1 );
		TextOut( hDC, 430, 664, "S", 1 );
		TextOut( hDC, 430, 696, "I", 1 );
		TextOut( hDC, 430, 728, "A", 1 );
		Rectangle( hDC, 368, 652, 406, 774 );
		Rectangle( hDC, 470, 652, 508, 774 );
		MoveToEx( hDC, 404, 676, NULL );
		LineTo( hDC, 424, 676 );
		MoveToEx( hDC, 506, 696, NULL );
		LineTo( hDC, 526, 696 );

		unsigned short PC_OMS_L;
		unsigned short PC_OMS_R;
		unsigned short He_L;
		unsigned short He_R;
		unsigned short N2_L;
		unsigned short N2_R;
		GetIDP()->GetOMSdata( PC_OMS_L, PC_OMS_R, He_L, He_R, N2_L, N2_R );

		unsigned short PC_C;
		unsigned short PC_L;
		unsigned short PC_R;
		unsigned short HeTk_C;
		unsigned short HeTk_L;
		unsigned short HeTk_R;
		unsigned short HeTk_Pneu;
		unsigned short HeReg_C;
		unsigned short HeReg_L;
		unsigned short HeReg_R;
		unsigned short HeReg_Pneu;
		unsigned short LH2_Manif;
		unsigned short LO2_Manif;
		GetIDP()->GetMPSdata( PC_C, PC_L, PC_R, HeTk_C, HeTk_L, HeTk_R, HeTk_Pneu, HeReg_C, HeReg_L, HeReg_R, HeReg_Pneu, LH2_Manif, LO2_Manif );

		// OMS He L
		usNum = He_L;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		TextOut( hDC, 112, 90, cbuf, strlen( cbuf ) );
		if (usNum >= 1500)
		{
			SelectObject( hDC, gdiLightGreenBrush );
			SelectObject( hDC, gdiLightGreenPen );
			if (usNum > 5000) usNum = 5000;
		}
		else
		{
			SelectObject( hDC, gdiRedBrush );
			SelectObject( hDC, gdiRedPen );
		}
		Rectangle( hDC, 140, Round( (254 - 0.0228 * usNum) ), 170, 254 );

		// OMS He R
		usNum = He_R;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		TextOut( hDC, 216, 90, cbuf, strlen( cbuf ) );
		if (usNum >= 1500)
		{
			SelectObject( hDC, gdiLightGreenBrush );
			SelectObject( hDC, gdiLightGreenPen );
			if (usNum > 5000) usNum = 5000;
		}
		else
		{
			SelectObject( hDC, gdiRedBrush );
			SelectObject( hDC, gdiRedPen );
		}
		Rectangle( hDC, 244, Round( (254 - 0.0228 * usNum) ), 274, 254 );

		// OMS N2 L
		usNum = N2_L;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		TextOut( hDC, 112, 308, cbuf, strlen( cbuf ) );
		if (usNum >= 1200)
		{
			SelectObject( hDC, gdiLightGreenBrush );
			SelectObject( hDC, gdiLightGreenPen );
			if (usNum > 3000) usNum = 3000;
		}
		else
		{
			SelectObject( hDC, gdiRedBrush );
			SelectObject( hDC, gdiRedPen );
		}
		Rectangle( hDC, 244, Round( (472 - 0.038 * usNum) ), 274, 472 );

		// OMS N2 R
		usNum = N2_R;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		TextOut( hDC, 216, 308, cbuf, strlen( cbuf ) );
		if (usNum >= 1200)
		{
			SelectObject( hDC, gdiLightGreenBrush );
			SelectObject( hDC, gdiLightGreenPen );
			if (usNum > 3000) usNum = 3000;
		}
		else
		{
			SelectObject( hDC, gdiRedBrush );
			SelectObject( hDC, gdiRedPen );
		}
		Rectangle( hDC, 348, Round( (472 - 0.038 * usNum) ), 378, 472 );


		// He Tank Press Pneu
		usNum = HeTk_Pneu;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		TextOut( hDC, 424, 90, cbuf, strlen( cbuf ) );
		if (usNum >= 3800)
		{
			SelectObject( hDC, gdiLightGreenBrush );
			SelectObject( hDC, gdiLightGreenPen );
			if (usNum > 5000) usNum = 5000;
		}
		else
		{
			SelectObject( hDC, gdiRedBrush );
			SelectObject( hDC, gdiRedPen );
			if (usNum < 3000) usNum = 3000;
		}
		Rectangle( hDC, 452, Round( 425 - (0.057 * usNum) ), 482, 254 );

		// He Tank Press Eng 2
		usNum = HeTk_L;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		TextOut( hDC, 618, 90, cbuf, strlen( cbuf ) );
		if (usNum >= 1150)
		{
			SelectObject( hDC, gdiLightGreenBrush );
			SelectObject( hDC, gdiLightGreenPen );
			if (usNum > 5000) usNum = 5000;
		}
		else
		{
			SelectObject( hDC, gdiRedBrush );
			SelectObject( hDC, gdiRedPen );
			if (usNum < 1000) usNum = 1000;
		}
		Rectangle( hDC, 646, Round( 282.5 - (0.0285 * usNum) ), 676, 254 );

		// He Tank Press Eng 1
		usNum = HeTk_C;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		TextOut( hDC, 730, 78, cbuf, strlen( cbuf ) );
		if (usNum >= 1150)
		{
			SelectObject( hDC, gdiLightGreenBrush );
			SelectObject( hDC, gdiLightGreenPen );
			if (usNum > 5000) usNum = 5000;
		}
		else
		{
			SelectObject( hDC, gdiRedBrush );
			SelectObject( hDC, gdiRedPen );
			if (usNum < 1000) usNum = 1000;
		}
		Rectangle( hDC, 758, Round( 282.5 - (0.0285 * usNum) ), 788, 254 );

		// He Tank Press Eng 3
		usNum = HeTk_R;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		TextOut( hDC, 842, 90, cbuf, strlen( cbuf ) );
		if (usNum >= 1150)
		{
			SelectObject( hDC, gdiLightGreenBrush );
			SelectObject( hDC, gdiLightGreenPen );
			if (usNum > 5000) usNum = 5000;
		}
		else
		{
			SelectObject( hDC, gdiRedBrush );
			SelectObject( hDC, gdiRedPen );
			if (usNum < 1000) usNum = 1000;
		}
		Rectangle( hDC, 870, Round( 282.5 - (0.0285 * usNum) ), 900, 254 );

		// He Reg Press Pneu
		usNum = HeReg_Pneu;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		TextOut( hDC, 424, 308, cbuf, strlen( cbuf ) );
		if ((usNum >= 680) && (usNum <= 810))
		{
			SelectObject( hDC, gdiLightGreenBrush );
			SelectObject( hDC, gdiLightGreenPen );
		}
		else
		{
			SelectObject( hDC, gdiRedBrush );
			SelectObject( hDC, gdiRedPen );
			if (usNum < 600) usNum = 600;
			if (usNum > 900) usNum = 900;
		}
		Rectangle( hDC, 452, Round( 700 - (0.38 * usNum) ), 482, 472 );

		// He Reg Press Eng 2
		usNum = HeReg_L;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		TextOut( hDC, 618, 308, cbuf, strlen( cbuf ) );
		if ((usNum >= 680) && (usNum <= 810))
		{
			SelectObject( hDC, gdiLightGreenBrush );
			SelectObject( hDC, gdiLightGreenPen );
		}
		else
		{
			SelectObject( hDC, gdiRedBrush );
			SelectObject( hDC, gdiRedPen );
			if (usNum < 600) usNum = 600;
			if (usNum > 900) usNum = 900;
		}
		Rectangle( hDC, 646, Round( 700 - (0.38 * usNum) ), 676, 472 );

		// He Reg Press Eng 1
		usNum = HeReg_C;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		TextOut( hDC, 730, 296, cbuf, strlen( cbuf ) );
		if ((usNum >= 680) && (usNum <= 810))
		{
			SelectObject( hDC, gdiLightGreenBrush );
			SelectObject( hDC, gdiLightGreenPen );
		}
		else
		{
			SelectObject( hDC, gdiRedBrush );
			SelectObject( hDC, gdiRedPen );
			if (usNum < 600) usNum = 600;
			if (usNum > 900) usNum = 900;
		}
		Rectangle( hDC, 758, Round( 700 - (0.38 * usNum) ), 788, 472 );

		// He Reg Press Eng 3
		usNum = HeReg_R;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		TextOut( hDC, 842, 308, cbuf, strlen( cbuf ) );
		if ((usNum >= 680) && (usNum <= 810))
		{
			SelectObject( hDC, gdiLightGreenBrush );
			SelectObject( hDC, gdiLightGreenPen );
		}
		else
		{
			SelectObject( hDC, gdiRedBrush );
			SelectObject( hDC, gdiRedPen );
			if (usNum < 600) usNum = 600;
			if (usNum > 900) usNum = 900;
		}
		Rectangle( hDC, 870, Round( 700 - (0.38 * usNum) ), 900, 472 );

		// ENG MANF LO2
		usNum = LO2_Manif;
		sprintf_s( cbuf, 16, "%03hu", usNum );
		TextOut( hDC, 356, 600, cbuf, strlen( cbuf ) );
		if (usNum >= 250)
		{
			SelectObject( hDC, gdiRedBrush );
			SelectObject( hDC, gdiRedPen );
			if (usNum > 300) usNum = 300;
		}
		else
		{
			SelectObject( hDC, gdiLightGreenBrush );
			SelectObject( hDC, gdiLightGreenPen );
		}
		Rectangle( hDC, 372, Round( 770 - (0.38 * usNum) ), 402, 770 );

		// ENG MANF LH2
		usNum = LH2_Manif;
		sprintf_s( cbuf, 16, "%03hu", usNum );
		TextOut( hDC, 458, 600, cbuf, strlen( cbuf ) );
		if (usNum >= 66)
		{
			SelectObject( hDC, gdiRedBrush );
			SelectObject( hDC, gdiRedPen );
			if (usNum > 100) usNum = 100;
		}
		else
		{
			SelectObject( hDC, gdiLightGreenBrush );
			SelectObject( hDC, gdiLightGreenPen );
		}
		Rectangle( hDC, 474, Round( 770 - (1.14 * usNum) ), 504, 770 );

		SelectObject( hDC, gdiSSVBFont_h36w18 );

		// L OMS
		usNum = PC_OMS_L;
		sprintf_s( cbuf, 16, "%03hu", usNum );
		TextOut( hDC, 120, 552, cbuf, strlen( cbuf ) );
		if (usNum >= 80)
		{
			SelectObject( hDC, gdiWhiteBrush );
			SelectObject( hDC, gdiWhitePen );
			if (usNum > 120) usNum = 120;
		}
		else if (usNum >= 4)
		{
			SelectObject( hDC, gdiRedBrush );
			SelectObject( hDC, gdiRedPen );
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			SelectObject( hDC, gdiBlackPen );
		}
		Rectangle( hDC, 132, Round( 802 - (1.55 * usNum) ), 164, 802 );

		// R OMS
		usNum = PC_OMS_R;
		sprintf_s( cbuf, 16, "%03hu", usNum );
		TextOut( hDC, 228, 552, cbuf, strlen( cbuf ) );
		if (usNum >= 80)
		{
			SelectObject( hDC, gdiWhiteBrush );
			SelectObject( hDC, gdiWhitePen );
			if (usNum > 120) usNum = 120;
		}
		else if (usNum >= 4)
		{
			SelectObject( hDC, gdiRedBrush );
			SelectObject( hDC, gdiRedPen );
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			SelectObject( hDC, gdiBlackPen );
		}
		Rectangle( hDC, 240, Round( 802 - (1.55 * usNum) ), 272, 802 );

		// PC L/2
		usNum = PC_L;
		sprintf_s( cbuf, 16, "%03hu", usNum );
		TextOut( hDC, 628, 552, cbuf, strlen( cbuf ) );
		if (usNum >= 65)
		{
			SelectObject( hDC, gdiWhiteBrush );
			SelectObject( hDC, gdiWhitePen );
			if (usNum > 109) usNum = 109;
		}
		else
		{
			SelectObject( hDC, gdiRedBrush );
			SelectObject( hDC, gdiRedPen );
			if (usNum < 45) usNum = 45;
		}
		Rectangle( hDC, 640, Round( 932.779 - (2.9062 * usNum) ), 672, 802 );

		// PC C/1
		usNum = PC_C;
		sprintf_s( cbuf, 16, "%03hu", usNum );
		TextOut( hDC, 732, 522, cbuf, strlen( cbuf ) );
		if (usNum >= 65)
		{
			SelectObject( hDC, gdiWhiteBrush );
			SelectObject( hDC, gdiWhitePen );
			if (usNum > 109) usNum = 109;
		}
		else
		{
			SelectObject( hDC, gdiRedBrush );
			SelectObject( hDC, gdiRedPen );
			if (usNum < 45) usNum = 45;
		}
		Rectangle( hDC, 746, Round( 932.779 - (2.9062 * usNum) ), 778, 802 );

		// PC R/3
		usNum = PC_R;
		sprintf_s( cbuf, 16, "%03hu", usNum );
		TextOut( hDC, 848, 552, cbuf, strlen( cbuf ) );
		if (usNum >= 65)
		{
			SelectObject( hDC, gdiWhiteBrush );
			SelectObject( hDC, gdiWhitePen );
			if (usNum > 109) usNum = 109;
		}
		else
		{
			SelectObject( hDC, gdiRedBrush );
			SelectObject( hDC, gdiRedPen );
			if (usNum < 45) usNum = 45;
		}
		Rectangle( hDC, 860, Round( 932.779 - (2.9062 * usNum) ), 892, 802 );
		return;
	}

	void MDU::OMSMPS( oapi::Sketchpad* skp )
	{
		unsigned short usNum;
		char cbuf[16];

		skp->SetTextColor( CR_DARK_GREEN );
		skp->SetFont( skpSSVBFont_h36w18 );
		skp->SetPen( skpDarkGreenPen );
		skp->SetBrush( skpBlackBrush );

		skp->Text( 152, 2, "OMS", 3 );
		skp->Text( 602, 2, "MPS", 3 );
		skp->Line( 326, 24, 326, 792 );
		skp->Line( 58, 24, 112, 24 );
		skp->Line( 230, 24, 584, 24 );
		skp->Line( 670, 24, 960, 24 );
		skp->Line( 58, 24, 58, 90 );
		skp->Line( 960, 24, 960, 90 );

		skp->SetTextColor( CR_WHITE );
		skp->SetFont( skpSSVAFont_h19w19bold );

		//OMS
		skp->Text( 146, 56, "L", 1 );
		skp->Text( 248, 56, "R", 1 );
		skp->Rectangle( 110, 84, 198, 118 );
		skp->Rectangle( 214, 84, 302, 118 );
		skp->Rectangle( 110, 302, 198, 336 );
		skp->Rectangle( 214, 302, 302, 336 );
		skp->Rectangle( 112, 550, 184, 600 );
		skp->Rectangle( 220, 550, 292, 600 );
		//MPS
		skp->Text( 634, 56, "L/2", 3 );
		skp->Text( 744, 44, "C/1", 3 );
		skp->Text( 852, 56, "R/3", 3 );
		//Tank P
		skp->Rectangle( 422, 84, 510, 118 );
		skp->Rectangle( 616, 84, 704, 118 );
		skp->Rectangle( 728, 72, 816, 106 );
		skp->Rectangle( 840, 84, 928, 118 );
		//Reg Press
		skp->Rectangle( 422, 302, 510, 336 );
		skp->Rectangle( 616, 302, 704, 336 );
		skp->Rectangle( 728, 290, 816, 326 );
		skp->Rectangle( 840, 302, 928, 336 );
		//Engine Pc
		skp->Text( 626, 520, "L/2", 3 );
		skp->Text( 732, 492, "C/1", 3 );
		skp->Text( 844, 520, "R/3", 3 );
		skp->Rectangle( 620, 550, 692, 600 );
		skp->Rectangle( 724, 520, 796, 570 );
		skp->Rectangle( 840, 550, 912, 600 );
		// ENG MANF
		skp->Rectangle( 352, 594, 424, 628 );
		skp->Rectangle( 454, 594, 526, 628 );

		skp->SetPen( skpWhitePen );

		//OMS
		skp->Text( 64, 136, "He", 2 );
		skp->Text( 64, 170, "TK", 2 );
		skp->Text( 72, 204, "P", 1 );
		skp->Rectangle( 136, 136, 174, 258 );
		skp->Rectangle( 240, 136, 278, 258 );
		skp->Line( 172, 220, 192, 220 );
		skp->Line( 276, 220, 296, 220 );

		skp->Text( 64, 366, "N", 1 );
		skp->Text( 84, 372, "2", 1 );
		skp->Text( 64, 400, "TK", 2 );
		skp->Text( 72, 434, "P", 1 );
		skp->Rectangle( 136, 354, 174, 476 );
		skp->Rectangle( 240, 354, 278, 476 );
		skp->Line( 172, 426, 192, 426 );
		skp->Line( 276, 426, 296, 426 );

		skp->Text( 136, 520, "L", 1 );
		skp->Text( 242, 520, "R", 1 );
		skp->Text( 70, 670, "Pc", 2 );
		skp->Text( 82, 716, "%", 1 );
		skp->Rectangle( 128, 612, 168, 806 );
		skp->Rectangle( 236, 612, 276, 806 );
		skp->Line( 166, 678, 186, 678 );
		skp->Line( 274, 678, 294, 678 );

		//MPS
		skp->Text( 426, 56, "PNEU", 4 );
		skp->Text( 348, 182, "TANK", 4 );
		skp->Text( 378, 216, "P", 1 );
		skp->Rectangle( 448, 136, 486, 258 );
		skp->Text( 564, 136, "He", 2 );
		skp->Text( 546, 170, "TANK", 4 );
		skp->Text( 570, 204, "P", 1 );
		skp->Rectangle( 642, 136, 680, 258 );
		skp->Rectangle( 754, 136, 792, 258 );
		skp->Rectangle( 866, 136, 904, 258 );
		skp->Line( 484, 208, 504, 208 );
		skp->Line( 678, 250, 698, 250 );
		skp->Line( 790, 250, 810, 250 );
		skp->Line( 902, 250, 922, 250 );

		skp->Text( 356, 366, "REG", 3 );
		skp->Text( 378, 404, "P", 1 );
		skp->Rectangle( 448, 354, 486, 476 );
		skp->Text( 550, 358, "He", 2 );
		skp->Text( 532, 392, "REG A", 5 );
		skp->Text( 570, 426, "P", 1 );
		skp->Rectangle( 642, 354, 680, 476 );
		skp->Rectangle( 754, 354, 792, 476 );
		skp->Rectangle( 866, 354, 904, 476 );
		skp->Line( 484, 392, 504, 392 );
		skp->Line( 484, 442, 504, 442 );
		skp->Line( 678, 392, 698, 392 );
		skp->Line( 678, 442, 698, 442 );
		skp->Line( 790, 392, 810, 392 );
		skp->Line( 790, 442, 810, 442 );
		skp->Line( 902, 392, 922, 392 );
		skp->Line( 902, 442, 922, 442 );

		skp->Text( 686, 670, "Pc", 2 );
		skp->Text( 698, 694, "%", 1 );
		skp->Text( 796, 670, "Pc", 2 );
		skp->Text( 808, 694, "%", 1 );
		skp->Rectangle( 636, 612, 676, 806 );
		skp->Rectangle( 742, 612, 782, 806 );
		skp->Rectangle( 856, 612, 896, 806 );
		skp->Line( 674, 630, 694, 630 );
		skp->Line( 780, 630, 800, 630 );
		skp->Line( 894, 630, 914, 630 );
		skp->Line( 674, 738, 694, 738 );
		skp->Line( 780, 738, 800, 738 );
		skp->Line( 894, 738, 914, 738 );

		skp->Text( 364, 524, "ENG MANF", 8 );
		skp->Text( 358, 558, "LO2", 3 );
		skp->Text( 458, 558, "LH2", 3 );
		skp->Text( 430, 632, "P", 1 );
		skp->Text( 430, 664, "S", 1 );
		skp->Text( 430, 696, "I", 1 );
		skp->Text( 430, 728, "A", 1 );
		skp->Rectangle( 368, 652, 406, 774 );
		skp->Rectangle( 470, 652, 508, 774 );
		skp->Line( 404, 676, 424, 676 );
		skp->Line( 506, 696, 526, 696 );

		unsigned short PC_OMS_L;
		unsigned short PC_OMS_R;
		unsigned short He_L;
		unsigned short He_R;
		unsigned short N2_L;
		unsigned short N2_R;
		GetIDP()->GetOMSdata( PC_OMS_L, PC_OMS_R, He_L, He_R, N2_L, N2_R );

		unsigned short PC_C;
		unsigned short PC_L;
		unsigned short PC_R;
		unsigned short HeTk_C;
		unsigned short HeTk_L;
		unsigned short HeTk_R;
		unsigned short HeTk_Pneu;
		unsigned short HeReg_C;
		unsigned short HeReg_L;
		unsigned short HeReg_R;
		unsigned short HeReg_Pneu;
		unsigned short LH2_Manif;
		unsigned short LO2_Manif;
		GetIDP()->GetMPSdata( PC_C, PC_L, PC_R, HeTk_C, HeTk_L, HeTk_R, HeTk_Pneu, HeReg_C, HeReg_L, HeReg_R, HeReg_Pneu, LH2_Manif, LO2_Manif );

		// OMS He L
		usNum = He_L;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		skp->Text( 112, 90, cbuf, strlen( cbuf ) );
		if (usNum >= 1500)
		{
			skp->SetBrush( skpLightGreenBrush );
			skp->SetPen( skpLightGreenPen );
			if (usNum > 5000) usNum = 5000;
		}
		else
		{
			skp->SetBrush( skpRedBrush );
			skp->SetPen( skpRedPen );
		}
		skp->Rectangle( 140, Round( (254 - 0.0228 * usNum) ), 170, 254 );

		// OMS He R
		usNum = He_R;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		skp->Text( 216, 90, cbuf, strlen( cbuf ) );
		if (usNum >= 1500)
		{
			skp->SetBrush( skpLightGreenBrush );
			skp->SetPen( skpLightGreenPen );
			if (usNum > 5000) usNum = 5000;
		}
		else
		{
			skp->SetBrush( skpRedBrush );
			skp->SetPen( skpRedPen );
		}
		skp->Rectangle( 244, Round( (254 - 0.0228 * usNum) ), 274, 254 );

		// OMS N2 L
		usNum = N2_L;
		sprintf_s(cbuf, 16, "%04hu", usNum);
		skp->Text( 112, 308, cbuf, strlen(cbuf) );
		if (usNum >= 1200)
		{
			skp->SetBrush( skpLightGreenBrush );
			skp->SetPen( skpLightGreenPen );
			if (usNum > 3000) usNum = 3000;
		}
		else
		{
			skp->SetBrush( skpRedBrush );
			skp->SetPen( skpRedPen );
		}
		skp->Rectangle( 244, Round( (472 - 0.038 * usNum) ), 274, 472 );

		// OMS N2 R
		usNum = N2_R;
		sprintf_s(cbuf, 16, "%04hu", usNum);
		skp->Text( 216, 308, cbuf, strlen(cbuf) );
		if (usNum >= 1200)
		{
			skp->SetBrush( skpLightGreenBrush );
			skp->SetPen( skpLightGreenPen );
			if (usNum > 3000) usNum = 3000;
		}
		else
		{
			skp->SetBrush( skpRedBrush );
			skp->SetPen( skpRedPen );
		}
		skp->Rectangle( 348, Round( (472 - 0.038 * usNum) ), 378, 472 );

		// He Tank Press Pneu
		usNum = HeTk_Pneu;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		skp->Text( 424, 90, cbuf, strlen( cbuf ) );
		if (usNum >= 3800)
		{
			skp->SetBrush( skpLightGreenBrush );
			skp->SetPen( skpLightGreenPen );
			if (usNum > 5000) usNum = 5000;
		}
		else
		{
			skp->SetBrush( skpRedBrush );
			skp->SetPen( skpRedPen );
			if (usNum < 3000) usNum = 3000;
		}
		skp->Rectangle( 452, Round( 425 - (0.057 * usNum) ), 482, 254 );

		// He Tank Press Eng 2
		usNum = HeTk_L;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		skp->Text( 618, 90, cbuf, strlen( cbuf ) );
		if (usNum >= 1150)
		{
			skp->SetBrush( skpLightGreenBrush );
			skp->SetPen( skpLightGreenPen );
			if (usNum > 5000) usNum = 5000;
		}
		else
		{
			skp->SetBrush( skpRedBrush );
			skp->SetPen( skpRedPen );
			if (usNum < 1000) usNum = 1000;
		}
		skp->Rectangle( 646, Round( 282.5 - (0.0285 * usNum) ), 676, 254 );

		// He Tank Press Eng 1
		usNum = HeTk_C;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		skp->Text( 730, 78, cbuf, strlen( cbuf ) );
		if (usNum >= 1150)
		{
			skp->SetBrush( skpLightGreenBrush );
			skp->SetPen( skpLightGreenPen );
			if (usNum > 5000) usNum = 5000;
		}
		else
		{
			skp->SetBrush( skpRedBrush );
			skp->SetPen( skpRedPen );
			if (usNum < 1000) usNum = 1000;
		}
		skp->Rectangle( 758, Round( 282.5 - (0.0285 * usNum) ), 788, 254 );

		// He Tank Press Eng 3
		usNum = HeTk_R;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		skp->Text( 842, 90, cbuf, strlen( cbuf ) );
		if (usNum >= 1150)
		{
			skp->SetBrush( skpLightGreenBrush );
			skp->SetPen( skpLightGreenPen );
			if (usNum > 5000) usNum = 5000;
		}
		else
		{
			skp->SetBrush( skpRedBrush );
			skp->SetPen( skpRedPen );
			if (usNum < 1000) usNum = 1000;
		}
		skp->Rectangle( 870, Round( 282.5 - (0.0285 * usNum) ), 900, 254 );

		// He Reg Press Pneu
		usNum = HeReg_Pneu;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		skp->Text( 424, 308, cbuf, strlen( cbuf ) );
		if ((usNum >= 680) && (usNum <= 810))
		{
			skp->SetBrush( skpLightGreenBrush );
			skp->SetPen( skpLightGreenPen );
		}
		else
		{
			skp->SetBrush( skpRedBrush );
			skp->SetPen( skpRedPen );
			if (usNum < 600) usNum = 600;
			if (usNum > 900) usNum = 900;
		}
		skp->Rectangle( 452, Round( 700 - (0.38 * usNum) ), 482, 472 );

		// He Reg Press Eng 2
		usNum = HeReg_L;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		skp->Text( 618, 308, cbuf, strlen( cbuf ) );
		if ((usNum >= 680) && (usNum <= 810))
		{
			skp->SetBrush( skpLightGreenBrush );
			skp->SetPen( skpLightGreenPen );
		}
		else
		{
			skp->SetBrush( skpRedBrush );
			skp->SetPen( skpRedPen );
			if (usNum < 600) usNum = 600;
			if (usNum > 900) usNum = 900;
		}
		skp->Rectangle( 646, Round( 700 - (0.38 * usNum) ), 676, 472 );

		// He Reg Press Eng 1
		usNum = HeReg_C;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		skp->Text( 730, 296, cbuf, strlen( cbuf ) );
		if ((usNum >= 680) && (usNum <= 810))
		{
			skp->SetBrush( skpLightGreenBrush );
			skp->SetPen( skpLightGreenPen );
		}
		else
		{
			skp->SetBrush( skpRedBrush );
			skp->SetPen( skpRedPen );
			if (usNum < 600) usNum = 600;
			if (usNum > 900) usNum = 900;
		}
		skp->Rectangle( 758, Round( 700 - (0.38 * usNum) ), 788, 472 );

		// He Reg Press Eng 3
		usNum = HeReg_R;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		skp->Text( 842, 308, cbuf, strlen( cbuf ) );
		if ((usNum >= 680) && (usNum <= 810))
		{
			skp->SetBrush( skpLightGreenBrush );
			skp->SetPen( skpLightGreenPen );
		}
		else
		{
			skp->SetBrush( skpRedBrush );
			skp->SetPen( skpRedPen );
			if (usNum < 600) usNum = 600;
			if (usNum > 900) usNum = 900;
		}
		skp->Rectangle( 870, Round( 700 - (0.38 * usNum) ), 900, 472 );

		// ENG MANF LO2
		usNum = LO2_Manif;
		sprintf_s( cbuf, 16, "%03hu", usNum );
		skp->Text( 356, 600, cbuf, strlen( cbuf ) );
		if (usNum >= 250)
		{
			skp->SetBrush( skpRedBrush );
			skp->SetPen( skpRedPen );
			if (usNum > 300) usNum = 300;
		}
		else
		{
			skp->SetBrush( skpLightGreenBrush );
			skp->SetPen( skpLightGreenPen );
		}
		skp->Rectangle( 372, Round( 770 - (0.38 * usNum) ), 402, 770 );

		// ENG MANF LH2
		usNum = LH2_Manif;
		sprintf_s( cbuf, 16, "%03hu", usNum );
		skp->Text( 458, 600, cbuf, strlen( cbuf ) );
		if (usNum >= 66)
		{
			skp->SetBrush( skpRedBrush );
			skp->SetPen( skpRedPen );
			if (usNum > 100) usNum = 100;
		}
		else
		{
			skp->SetBrush( skpLightGreenBrush );
			skp->SetPen( skpLightGreenPen );
		}
		skp->Rectangle( 474, Round( 770 - (1.14 * usNum) ), 504, 770 );

		skp->SetFont( skpSSVBFont_h36w18 );

		// L OMS
		usNum = PC_OMS_L;
		sprintf_s( cbuf, 16, "%03hu", usNum );
		skp->Text( 120, 552, cbuf, strlen( cbuf ) );
		if (usNum >= 80)
		{
			skp->SetBrush( skpWhiteBrush );
			skp->SetPen( skpWhitePen );
			if (usNum > 120) usNum = 120;
		}
		else if (usNum >= 4)
		{
			skp->SetBrush( skpRedBrush );
			skp->SetPen( skpRedPen );
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->SetPen( skpBlackPen );
		}
		skp->Rectangle( 132, Round( 802 - (1.55 * usNum) ), 164, 802 );

		// R OMS
		usNum = PC_OMS_R;
		sprintf_s( cbuf, 16, "%03hu", usNum );
		skp->Text( 228, 552, cbuf, strlen( cbuf ) );
		if (usNum >= 80)
		{
			skp->SetBrush( skpWhiteBrush );
			skp->SetPen( skpWhitePen );
			if (usNum > 120) usNum = 120;
		}
		else if (usNum >= 4)
		{
			skp->SetBrush( skpRedBrush );
			skp->SetPen( skpRedPen );
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->SetPen( skpBlackPen );
		}
		skp->Rectangle( 240, Round( 802 - (1.55 * usNum) ), 272, 802 );

		// PC L/2
		usNum = PC_L;
		sprintf_s( cbuf, 16, "%03hu", usNum );
		skp->Text( 628, 552, cbuf, strlen( cbuf ) );
		if (usNum >= 65)
		{
			skp->SetBrush( skpWhiteBrush );
			skp->SetPen( skpWhitePen );
			if (usNum > 109) usNum = 109;
		}
		else
		{
			skp->SetBrush( skpRedBrush );
			skp->SetPen( skpRedPen );
			if (usNum < 45) usNum = 45;
		}
		skp->Rectangle( 640, Round( 932.779 - (2.9062 * usNum) ), 672, 802 );

		// PC C/1
		usNum = PC_C;
		sprintf_s( cbuf, 16, "%03hu", usNum );
		skp->Text( 732, 522, cbuf, strlen( cbuf ) );
		if (usNum >= 65)
		{
			skp->SetBrush( skpWhiteBrush );
			skp->SetPen( skpWhitePen );
			if (usNum > 109) usNum = 109;
		}
		else
		{
			skp->SetBrush( skpRedBrush );
			skp->SetPen( skpRedPen );
			if (usNum < 45) usNum = 45;
		}
		skp->Rectangle( 746, Round( 932.779 - (2.9062 * usNum) ), 778, 802 );

		// PC R/3
		usNum = PC_R;
		sprintf_s( cbuf, 16, "%03hu", usNum );
		skp->Text( 848, 552, cbuf, strlen( cbuf ) );
		if (usNum >= 65)
		{
			skp->SetBrush( skpWhiteBrush );
			skp->SetPen( skpWhitePen );
			if (usNum > 109) usNum = 109;
		}
		else
		{
			skp->SetBrush( skpRedBrush );
			skp->SetPen( skpRedPen );
			if (usNum < 45) usNum = 45;
		}
		skp->Rectangle( 860, Round( 932.779 - (2.9062 * usNum) ), 892, 802 );

		return;
	}

	void MDU::APUHYD( HDC hDC )
	{
		int nPos;
		unsigned short usNum;
		char cbuf[16];

		SelectObject( hDC, gdiSSVBFont_h36w18 );
		SelectObject( hDC, gdiDarkGreenPen );
		SelectObject( hDC, gdiBlackBrush );

		SetTextColor( hDC, CR_DARK_GREEN );
		TextOut( hDC, 478, 12, "APU", 3 );
		MoveToEx( hDC, 76, 30, NULL );
		LineTo( hDC, 470, 30 );
		MoveToEx( hDC, 548, 30, NULL );
		LineTo( hDC, 944, 30 );
		MoveToEx( hDC, 76, 30, NULL );
		LineTo( hDC, 76, 66 );
		MoveToEx( hDC, 944, 30, NULL );
		LineTo( hDC, 944, 66 );

		TextOut( hDC, 432, 522, "HYDRAULIC", 9 );
		MoveToEx( hDC, 40, 536, NULL );
		LineTo( hDC, 416, 536 );
		MoveToEx( hDC, 606, 536, NULL );
		LineTo( hDC, 944, 536 );
		MoveToEx( hDC, 40, 536, NULL );
		LineTo( hDC, 40, 572 );
		MoveToEx( hDC, 944, 536, NULL );
		LineTo( hDC, 944, 572 );

		SetTextColor( hDC, CR_WHITE );
		SelectObject( hDC, gdiSSVAFont_h19w19bold );

		// APU
		TextOut( hDC, 166, 62, "1", 1 );
		TextOut( hDC, 270, 62, "2", 1 );
		TextOut( hDC, 374, 62, "3", 1 );
		TextOut( hDC, 66, 180, "FUEL", 4 );
		TextOut( hDC, 70, 208, "QTY", 3 );
		TextOut( hDC, 92, 236, "%", 1 );
		Rectangle( hDC, 142, 94, 214, 128 );
		Rectangle( hDC, 246, 94, 318, 128 );
		Rectangle( hDC, 350, 94, 422, 128 );

		TextOut( hDC, 70, 362, "H O", 3 );
		TextOut( hDC, 92, 370, "2", 1 );
		TextOut( hDC, 70, 394, "QTY", 3 );
		TextOut( hDC, 92, 422, "%", 1 );
		Rectangle( hDC, 142, 294, 214, 328 );
		Rectangle( hDC, 246, 294, 318, 328 );
		Rectangle( hDC, 350, 294, 422, 328 );

		TextOut( hDC, 636, 62, "1", 1 );
		TextOut( hDC, 744, 62, "2", 1 );
		TextOut( hDC, 852, 62, "3", 1 );
		TextOut( hDC, 528, 180, "FUEL", 4 );
		TextOut( hDC, 558, 208, "P", 1 );
		Rectangle( hDC, 602, 94, 690, 128 );
		Rectangle( hDC, 710, 94, 798, 128 );
		Rectangle( hDC, 818, 94, 906, 128 );

		TextOut( hDC, 514, 362, "OIL", 3 );
		TextOut( hDC, 476, 394, "IN TEMP", 7 );
		TextOut( hDC, 510, 422, "\xB0""F", 2 );
		Rectangle( hDC, 602, 294, 690, 328 );
		Rectangle( hDC, 710, 294, 798, 328 );
		Rectangle( hDC, 818, 294, 906, 328 );

		// HYD
		TextOut( hDC, 166, 578, "1", 1 );
		TextOut( hDC, 270, 578, "2", 1 );
		TextOut( hDC, 374, 578, "3", 1 );
		TextOut( hDC, 70, 688, "QTY", 3 );
		TextOut( hDC, 92, 716, "%", 1 );
		Rectangle( hDC, 142, 614, 214, 648 );
		Rectangle( hDC, 246, 614, 318, 648 );
		Rectangle( hDC, 350, 614, 422, 648 );

		TextOut( hDC, 636, 578, "1", 1 );
		TextOut( hDC, 744, 578, "2", 1 );
		TextOut( hDC, 852, 578, "3", 1 );
		TextOut( hDC, 520, 706, "PRESS", 5 );
		Rectangle( hDC, 602, 614, 690, 648 );
		Rectangle( hDC, 710, 614, 798, 648 );
		Rectangle( hDC, 818, 614, 906, 648 );
		TextOut( hDC, 702, 752, "L", 1 );
		TextOut( hDC, 810, 752, "L", 1 );
		TextOut( hDC, 918, 752, "L", 1 );

		SelectObject( hDC, gdiWhitePen );

		//Fuel Qty
		Rectangle( hDC, 158, 152, 196, 266 );
		Rectangle( hDC, 262, 152, 300, 266 );
		Rectangle( hDC, 366, 152, 404, 266 );
		MoveToEx( hDC, 194, 240, NULL );
		LineTo( hDC, 214, 240 );
		MoveToEx( hDC, 298, 240, NULL );
		LineTo( hDC, 318, 240 );
		MoveToEx( hDC, 402, 240, NULL );
		LineTo( hDC, 422, 240 );

		//H2O Qty
		Rectangle( hDC, 158, 350, 196, 464 );
		Rectangle( hDC, 262, 350, 300, 464 );
		Rectangle( hDC, 366, 350, 404, 464 );
		MoveToEx( hDC, 194, 418, NULL );
		LineTo( hDC, 214, 418 );
		MoveToEx( hDC, 298, 418, NULL );
		LineTo( hDC, 318, 418 );
		MoveToEx( hDC, 402, 418, NULL );
		LineTo( hDC, 422, 418 );

		//Fuel P
		Rectangle( hDC, 628, 144, 666, 266 );
		Rectangle( hDC, 736, 144, 774, 266 );
		Rectangle( hDC, 844, 144, 882, 266 );

		//Oil In Temp
		Rectangle( hDC, 628, 342, 666, 464 );
		Rectangle( hDC, 736, 342, 774, 464 );
		Rectangle( hDC, 844, 342, 882, 464 );
		MoveToEx( hDC, 664, 450, NULL );
		LineTo( hDC, 684, 450 );
		MoveToEx( hDC, 772, 450, NULL );
		LineTo( hDC, 792, 450 );
		MoveToEx( hDC, 880, 450, NULL );
		LineTo( hDC, 900, 450 );
		MoveToEx( hDC, 664, 394, NULL );
		LineTo( hDC, 684, 394 );
		MoveToEx( hDC, 772, 394, NULL );
		LineTo( hDC, 792, 394 );
		MoveToEx( hDC, 880, 394, NULL );
		LineTo( hDC, 900, 394 );

		//Hydraulic Qty
		Rectangle( hDC, 158, 670, 196, 784 );
		Rectangle( hDC, 262, 670, 300, 784 );
		Rectangle( hDC, 366, 670, 404, 784 );
		MoveToEx( hDC, 194, 738, NULL );
		LineTo( hDC, 214, 738 );
		MoveToEx( hDC, 298, 738, NULL );
		LineTo( hDC, 318, 738 );
		MoveToEx( hDC, 402, 738, NULL );
		LineTo( hDC, 422, 738 );
		MoveToEx( hDC, 194, 680, NULL );
		LineTo( hDC, 214, 680 );
		MoveToEx( hDC, 298, 680, NULL );
		LineTo( hDC, 318, 680 );
		MoveToEx( hDC, 402, 680, NULL );
		LineTo( hDC, 422, 680 );

		//Hydraulic Press
		Rectangle( hDC, 628, 670, 666, 784 );
		Rectangle( hDC, 736, 670, 774, 784 );
		Rectangle( hDC, 844, 670, 882, 784 );
		MoveToEx( hDC, 664, 766, NULL );
		LineTo( hDC, 684, 766 );
		MoveToEx( hDC, 772, 766, NULL );
		LineTo( hDC, 792, 766 );
		MoveToEx( hDC, 880, 766, NULL );
		LineTo( hDC, 900, 766 );
		MoveToEx( hDC, 664, 754, NULL );
		LineTo( hDC, 684, 754 );
		MoveToEx( hDC, 772, 754, NULL );
		LineTo( hDC, 792, 754 );
		MoveToEx( hDC, 880, 754, NULL );
		LineTo( hDC, 900, 754 );
		MoveToEx( hDC, 664, 716, NULL );
		LineTo( hDC, 684, 716 );
		MoveToEx( hDC, 772, 716, NULL );
		LineTo( hDC, 792, 716 );
		MoveToEx( hDC, 880, 716, NULL );
		LineTo( hDC, 900, 716 );

		unsigned short FuQty[3];
		unsigned short Fu_Press[3];
		unsigned short H2OQty[3];
		unsigned short OilIn[3];
		GetIDP()->GetAPUdata( FuQty[0], FuQty[1], FuQty[2], Fu_Press[0], Fu_Press[1], Fu_Press[2], H2OQty[0], H2OQty[1], H2OQty[2], OilIn[0], OilIn[1], OilIn[2] );
		
		unsigned short Qty[3];
		unsigned short Press[3];
		GetIDP()->GetHYDdata( Qty[0], Qty[1], Qty[2], Press[0], Press[1], Press[2] );

		for (nPos = 0; nPos < 3; nPos++)
		{
			//Fuel Qty
			usNum = FuQty[nPos];
			sprintf_s( cbuf, 16, "%03hu", usNum );
			TextOut( hDC, 146 + 104 * nPos, 100, cbuf, strlen( cbuf ) );
			if (usNum >= 20)
			{
				SelectObject( hDC, gdiLightGreenBrush );
				SelectObject( hDC, gdiLightGreenPen );
				if (usNum > 100) usNum = 100;
			}
			else
			{
				SelectObject( hDC, gdiRedBrush );
				SelectObject( hDC, gdiRedPen );
			}
			Rectangle( hDC, 162 + 104 * nPos, static_cast<int>(262 - 1.06 * usNum), 192 + 104 * nPos, 262 );

			//H2O Qty
			usNum = H2OQty[nPos];
			sprintf_s( cbuf, 16, "%03hu", usNum );
			TextOut( hDC, 146 + 104 * nPos, 300, cbuf, strlen( cbuf ) );
			if (usNum >= 40)
			{
				SelectObject( hDC, gdiLightGreenBrush );
				SelectObject( hDC, gdiLightGreenPen );
				if (usNum > 100) usNum = 100;
			}
			else
			{
				SelectObject( hDC, gdiRedBrush );
				SelectObject( hDC, gdiRedPen );
			}
			Rectangle( hDC, 162 + 104 * nPos, static_cast<int>(460 - 1.06 * usNum), 192 + 104 * nPos, 460 );

			//Fuel P
			usNum = Fu_Press[nPos];
			sprintf_s( cbuf, 16, "%04hu", usNum );
			TextOut( hDC, 604 + 108 * nPos, 100, cbuf, strlen( cbuf ) );
			SelectObject( hDC, gdiLightGreenBrush );
			SelectObject( hDC, gdiLightGreenPen );
			if (usNum > 500) usNum = 500;
			Rectangle( hDC, 632 + 108 * nPos, static_cast<int>(262 - 0.228 * usNum), 662 + 108 * nPos, 262 );

			//Oil In Temp
			usNum = OilIn[nPos];
			sprintf_s( cbuf, 16, "%04hu", usNum );
			TextOut( hDC, 604 + 108 * nPos, 300, cbuf, strlen( cbuf ) );
			if (usNum >= 291)
			{
				SelectObject( hDC, gdiRedBrush );
				SelectObject( hDC, gdiRedPen );
				if (usNum > 500) usNum = 500;
			}
			else if (usNum >= 45)
			{
				SelectObject( hDC, gdiLightGreenBrush );
				SelectObject( hDC, gdiLightGreenPen );
			}
			else
			{
				SelectObject( hDC, gdiRedBrush );
				SelectObject( hDC, gdiRedPen );
			}
			Rectangle( hDC, 632 + 108 * nPos, static_cast<int>(460 - 0.228 * usNum), 662 + 108 * nPos, 460 );

			//Hydraulic Qty
			usNum = Qty[nPos];
			sprintf_s( cbuf, 16, "%03hu", usNum );
			TextOut( hDC, 146 + 104 * nPos, 620, cbuf, strlen( cbuf ) );
			if (usNum >= 96)
			{
				SelectObject( hDC, gdiRedBrush );
				SelectObject( hDC, gdiRedPen );
				if (usNum > 100) usNum = 100;
			}
			else if (usNum >= 40)
			{
				SelectObject( hDC, gdiLightGreenBrush );
				SelectObject( hDC, gdiLightGreenPen );
			}
			else
			{
				SelectObject( hDC, gdiRedBrush );
				SelectObject( hDC, gdiRedPen );
			}
			Rectangle( hDC, 162 + 104 * nPos, static_cast<int>(780 - 1.06 * usNum), 192 + 104 * nPos, 780 );

			//Hydraulic Press
			usNum = Press[nPos];
			sprintf_s( cbuf, 16, "%04hu", usNum );
			TextOut( hDC, 604 + 108 * nPos, 620, cbuf, strlen( cbuf ) );
			if (usNum >= 2400)
			{
				SelectObject( hDC, gdiLightGreenBrush );
				SelectObject( hDC, gdiLightGreenPen );
				if (usNum > 4000) usNum = 4000;
			}
			else if (usNum >= 1001)
			{
				SelectObject( hDC, gdiRedBrush );
				SelectObject( hDC, gdiRedPen );
			}
			else if (usNum >= 501)
			{
				SelectObject( hDC, gdiLightGreenBrush );
				SelectObject( hDC, gdiLightGreenPen );
			}
			else
			{
				SelectObject( hDC, gdiRedBrush );
				SelectObject( hDC, gdiRedPen );
			}
			Rectangle( hDC, 632 + 108 * nPos, static_cast<int>(780 - 0.0265 * usNum), 662 + 108 * nPos, 780 );
		}
		return;
	}

	void MDU::APUHYD( oapi::Sketchpad* skp )
	{
		int nPos;
		unsigned short usNum;
		char cbuf[16];

		skp->SetFont( skpSSVBFont_h36w18 );
		skp->SetPen( skpDarkGreenPen );
		skp->SetBrush( skpBlackBrush );

		skp->SetTextColor( CR_DARK_GREEN );
		skp->Text( 478, 12, "APU", 3 );
		skp->Line( 76, 30, 470, 30 );
		skp->Line( 548, 30, 944, 30 );
		skp->Line( 76, 30, 76, 66 );
		skp->Line( 944, 30, 944, 66 );

		skp->Text( 432, 522, "HYDRAULIC", 9 );
		skp->Line( 40, 536, 416, 536 );
		skp->Line( 606, 536, 944, 536 );
		skp->Line( 40, 536, 40, 572 );
		skp->Line( 944, 536, 944, 572 );

		skp->SetTextColor( CR_WHITE );
		skp->SetFont( skpSSVAFont_h19w19bold );

		// APU
		skp->Text( 166, 62, "1", 1 );
		skp->Text( 270, 62, "2", 1 );
		skp->Text( 374, 62, "3", 1 );
		skp->Text( 66, 180, "FUEL", 4 );
		skp->Text( 70, 208, "QTY", 3 );
		skp->Text( 92, 236, "%", 1 );
		skp->Rectangle( 142, 94, 214, 128 );
		skp->Rectangle( 246, 94, 318, 128 );
		skp->Rectangle( 350, 94, 422, 128 );

		skp->Text( 70, 362, "H O", 3 );
		skp->Text( 92, 370, "2", 1 );
		skp->Text( 70, 394, "QTY", 3 );
		skp->Text( 92, 422, "%", 1 );
		skp->Rectangle( 142, 294, 214, 328 );
		skp->Rectangle( 246, 294, 318, 328 );
		skp->Rectangle( 350, 294, 422, 328 );

		skp->Text( 636, 62, "1", 1 );
		skp->Text( 744, 62, "2", 1 );
		skp->Text( 852, 62, "3", 1 );
		skp->Text( 528, 180, "FUEL", 4 );
		skp->Text( 558, 208, "P", 1 );
		skp->Rectangle( 602, 94, 690, 128 );
		skp->Rectangle( 710, 94, 798, 128 );
		skp->Rectangle( 818, 94, 906, 128 );

		skp->Text( 514, 362, "OIL", 3 );
		skp->Text( 476, 394, "IN TEMP", 7 );
		skp->Text( 510, 422, "░F", 2 );
		skp->Rectangle( 602, 294, 690, 328 );
		skp->Rectangle( 710, 294, 798, 328 );
		skp->Rectangle( 818, 294, 906, 328 );

		// HYD
		skp->Text( 166, 578, "1", 1 );
		skp->Text( 270, 578, "2", 1 );
		skp->Text( 374, 578, "3", 1 );
		skp->Text( 70, 688, "QTY", 3 );
		skp->Text( 92, 716, "%", 1 );
		skp->Rectangle( 142, 614, 214, 648 );
		skp->Rectangle( 246, 614, 318, 648 );
		skp->Rectangle( 350, 614, 422, 648 );

		skp->Text( 636, 578, "1", 1 );
		skp->Text( 744, 578, "2", 1 );
		skp->Text( 852, 578, "3", 1 );
		skp->Text( 520, 706, "PRESS", 5 );
		skp->Rectangle( 602, 614, 690, 648 );
		skp->Rectangle( 710, 614, 798, 648 );
		skp->Rectangle( 818, 614, 906, 648 );
		skp->Text( 702, 752, "L", 1 );
		skp->Text( 810, 752, "L", 1 );
		skp->Text( 918, 752, "L", 1 );

		skp->SetPen( skpWhitePen );

		//Fuel Qty
		skp->Rectangle( 158, 152, 196, 266 );
		skp->Rectangle( 262, 152, 300, 266 );
		skp->Rectangle( 366, 152, 404, 266 );
		skp->Line( 194, 240, 214, 240 );
		skp->Line( 298, 240, 318, 240 );
		skp->Line( 402, 240, 422, 240 );

		//H2O Qty
		skp->Rectangle( 158, 350, 196, 464 );
		skp->Rectangle( 262, 350, 300, 464 );
		skp->Rectangle( 366, 350, 404, 464 );
		skp->Line( 194, 418, 214, 418 );
		skp->Line( 298, 418, 318, 418 );
		skp->Line( 402, 418, 422, 418 );

		//Fuel P
		skp->Rectangle( 628, 144, 666, 266 );
		skp->Rectangle( 736, 144, 774, 266 );
		skp->Rectangle( 844, 144, 882, 266 );

		//Oil In Temp
		skp->Rectangle( 628, 342, 666, 464 );
		skp->Rectangle( 736, 342, 774, 464 );
		skp->Rectangle( 844, 342, 882, 464 );
		skp->Line( 664, 450, 684, 450 );
		skp->Line( 772, 450, 792, 450 );
		skp->Line( 880, 450, 900, 450 );
		skp->Line( 664, 394, 684, 394 );
		skp->Line( 772, 394, 792, 394 );
		skp->Line( 880, 394, 900, 394 );

		//Hydraulic Qty
		skp->Rectangle( 158, 670, 196, 784 );
		skp->Rectangle( 262, 670, 300, 784 );
		skp->Rectangle( 366, 670, 404, 784 );
		skp->Line( 194, 738, 214, 738 );
		skp->Line( 298, 738, 318, 738 );
		skp->Line( 402, 738, 422, 738 );
		skp->Line( 194, 680, 214, 680 );
		skp->Line( 298, 680, 318, 680 );
		skp->Line( 402, 680, 422, 680 );

		//Hydraulic Press
		skp->Rectangle( 628, 670, 666, 784 );
		skp->Rectangle( 736, 670, 774, 784 );
		skp->Rectangle( 844, 670, 882, 784 );
		skp->Line( 664, 766, 684, 766 );
		skp->Line( 772, 766, 792, 766 );
		skp->Line( 880, 766, 900, 766 );
		skp->Line( 664, 754, 684, 754 );
		skp->Line( 772, 754, 792, 754 );
		skp->Line( 880, 754, 900, 754 );
		skp->Line( 664, 716, 684, 716 );
		skp->Line( 772, 716, 792, 716 );
		skp->Line( 880, 716, 900, 716 );

		unsigned short FuQty[3];
		unsigned short Fu_Press[3];
		unsigned short H2OQty[3];
		unsigned short OilIn[3];
		GetIDP()->GetAPUdata( FuQty[0], FuQty[1], FuQty[2], Fu_Press[0], Fu_Press[1], Fu_Press[2], H2OQty[0], H2OQty[1], H2OQty[2], OilIn[0], OilIn[1], OilIn[2] );
		
		unsigned short Qty[3];
		unsigned short Press[3];
		GetIDP()->GetHYDdata( Qty[0], Qty[1], Qty[2], Press[0], Press[1], Press[2] );

		for (nPos = 0; nPos < 3; nPos++)
		{
			//Fuel Qty
			usNum = FuQty[nPos];
			sprintf_s( cbuf, 16, "%03hu", usNum );
			skp->Text( 146 + 104 * nPos, 100, cbuf, strlen( cbuf ) );
			if (usNum >= 20)
			{
				skp->SetBrush( skpLightGreenBrush );
				skp->SetPen( skpLightGreenPen );
				if (usNum > 100) usNum = 100;
			}
			else
			{
				skp->SetBrush( skpRedBrush );
				skp->SetPen( skpRedPen );
			}
			skp->Rectangle( 162 + 104 * nPos, static_cast<int>(262 - 1.06 * usNum), 192 + 104 * nPos, 262 );

			//H2O Qty
			usNum = H2OQty[nPos];
			sprintf_s( cbuf, 16, "%03hu", usNum );
			skp->Text( 146 + 104 * nPos, 300, cbuf, strlen( cbuf ) );
			if (usNum >= 40)
			{
				skp->SetBrush( skpLightGreenBrush );
				skp->SetPen( skpLightGreenPen );
				if (usNum > 100) usNum = 100;
			}
			else
			{
				skp->SetBrush( skpRedBrush );
				skp->SetPen( skpRedPen );
			}
			skp->Rectangle( 162 + 104 * nPos, static_cast<int>(460 - 1.06 * usNum), 192 + 104 * nPos, 460 );

			//Fuel P
			usNum = Fu_Press[nPos];
			sprintf_s( cbuf, 16, "%04hu", usNum );
			skp->Text( 604 + 108 * nPos, 100, cbuf, strlen( cbuf ) );
			skp->SetBrush( skpLightGreenBrush );
			skp->SetPen( skpLightGreenPen );
			if (usNum > 500) usNum = 500;
			skp->Rectangle( 632 + 108 * nPos, static_cast<int>(262 - 0.228 * usNum), 662 + 108 * nPos, 262 );

			//Oil In Temp
			usNum = OilIn[nPos];
			sprintf_s( cbuf, 16, "%04hu", usNum );
			skp->Text( 604 + 108 * nPos, 300, cbuf, strlen( cbuf ) );
			if (usNum >= 291)
			{
				skp->SetBrush( skpRedBrush );
				skp->SetPen( skpRedPen );
				if (usNum > 500) usNum = 500;
			}
			else if (usNum >= 45)
			{
				skp->SetBrush( skpLightGreenBrush );
				skp->SetPen( skpLightGreenPen );
			}
			else
			{
				skp->SetBrush( skpRedBrush );
				skp->SetPen( skpRedPen );
			}
			skp->Rectangle( 632 + 108 * nPos, static_cast<int>(460 - 0.228 * usNum), 662 + 108 * nPos, 460 );

			//Hydraulic Qty
			usNum = Qty[nPos];
			sprintf_s( cbuf, 16, "%03hu", usNum );
			skp->Text( 146 + 104 * nPos, 620, cbuf, strlen( cbuf ) );
			if (usNum >= 96)
			{
				skp->SetBrush( skpRedBrush );
				skp->SetPen( skpRedPen );
				if (usNum > 100) usNum = 100;
			}
			else if (usNum >= 40)
			{
				skp->SetBrush( skpLightGreenBrush );
				skp->SetPen( skpLightGreenPen );
			}
			else
			{
				skp->SetBrush( skpRedBrush );
				skp->SetPen( skpRedPen );
			}
			skp->Rectangle( 162 + 104 * nPos, static_cast<int>(780 - 1.06 * usNum), 192 + 104 * nPos, 780 );

			//Hydraulic Press
			usNum = Press[nPos];
			sprintf_s( cbuf, 16, "%04hu", usNum );
			skp->Text( 604 + 108 * nPos, 620, cbuf, strlen( cbuf ) );
			if (usNum >= 2400)
			{
				skp->SetBrush( skpLightGreenBrush );
				skp->SetPen( skpLightGreenPen );
				if (usNum > 4000) usNum = 4000;
			}
			else if (usNum >= 1001)
			{
				skp->SetBrush( skpRedBrush );
				skp->SetPen( skpRedPen );
			}
			else if (usNum >= 501)
			{
				skp->SetBrush( skpLightGreenBrush );
				skp->SetPen( skpLightGreenPen );
			}
			else
			{
				skp->SetBrush( skpRedBrush );
				skp->SetPen( skpRedPen );
			}
			skp->Rectangle( 632 + 108 * nPos, static_cast<int>(780 - 0.0265 * usNum), 662 + 108 * nPos, 780 );
		}
		return;
	}

	void MDU::SPI( HDC hDC )// 304, 305, 602, 603, 801, 901
	{
		POINT tri[3];
		int nPos;
		double dNum;
		char cbuf[8];
		bool active;
		double LOB;
		double LIB;
		double RIB;
		double ROB;
		double DAFB;
		double DRFB;
		double DBFOFB;
		double Speedbrake_Pos;
		double Speedbrake_Cmd;
		active = GetIDP()->GetAerosurfacePositions( LOB, LIB, RIB, ROB, DAFB, DRFB, DBFOFB, Speedbrake_Pos, Speedbrake_Cmd );

		SelectObject( hDC, gdiSSVAFont_h19w19bold );
		SelectObject( hDC, gdiDarkGreenPen );
		SetTextColor( hDC, CR_DARK_GREEN );

		MoveToEx( hDC, 6, 150, NULL );
		LineTo( hDC, 6, 108 );
		MoveToEx( hDC, 6, 110, NULL );
		LineTo( hDC, 154, 110 );
		MoveToEx( hDC, 306, 110, NULL );
		LineTo( hDC, 454, 110 );
		MoveToEx( hDC, 454, 110, NULL );
		LineTo( hDC, 454, 150 );

		MoveToEx( hDC, 6, 672, NULL );
		LineTo( hDC, 6, 712 );
		MoveToEx( hDC, 6, 712, NULL );
		LineTo( hDC, 154, 712 );
		MoveToEx( hDC, 306, 712, NULL );
		LineTo( hDC, 454, 712 );
		MoveToEx( hDC, 454, 712, NULL );
		LineTo( hDC, 454, 672 );

		TextOut( hDC, 176, 98, "TE UP", 5 );
		TextOut( hDC, 176, 700, "TE DN", 5 );

		TextOut( hDC, 518, 216, "L RUD", 5 );
		TextOut( hDC, 916, 216, "R RUD", 5 );

		TextOut( hDC, 518, 416, "L AIL", 5 );
		TextOut( hDC, 916, 416, "R AIL", 5 );

		// gray boxes
		SelectObject( hDC, gdiDarkGrayBrush );
		SelectObject( hDC, gdiDarkGrayPen );

		Rectangle( hDC, 72, 182, 94, 646 );
		Rectangle( hDC, 230, 182, 254, 646 );

		Rectangle( hDC, 362, 182, 388, 646 );

		Rectangle( hDC, 528, 166, 1008, 194 );

		Rectangle( hDC, 528, 366, 1008, 392 );

		Rectangle( hDC, 528, 620, 1008, 646 );

		SetTextColor( hDC, CR_WHITE );
		TextOut( hDC, 50, 54, "ELEVONS", 7 );
		TextOut( hDC, 90, 80, "DEG", 3 );
		TextOut( hDC, 126, 214, "-30", 3 );
		TextOut( hDC, 126, 294, "-20", 3 );
		TextOut( hDC, 126, 376, "-10", 3 );
		TextOut( hDC, 126, 534, "+10", 3 );
		TextOut( hDC, 126, 614, "+20", 3 );

		TextOut( hDC, 272, 54, "BODY FLAP", 9 );
		TextOut( hDC, 356, 80, "%", 1 );
		TextOut( hDC, 438, 184, "0", 1 );
		TextOut( hDC, 438, 272, "20", 2 );
		TextOut( hDC, 438, 360, "40", 2 );
		TextOut( hDC, 438, 448, "60", 2 );
		TextOut( hDC, 438, 536, "80", 2 );
		TextOut( hDC, 438, 624, "100", 3 );

		TextOut( hDC, 650, 62, "RUDDER-DEG", 10 );
		TextOut( hDC, 512, 106, "30", 2 );
		TextOut( hDC, 588, 106, "20", 2 );
		TextOut( hDC, 664, 106, "10", 2 );
		TextOut( hDC, 816, 106, "10", 2 );
		TextOut( hDC, 892, 106, "20", 2 );
		TextOut( hDC, 968, 106, "30", 2 );

		TextOut( hDC, 650, 278, "AILERON-DEG", 11 );
		TextOut( hDC, 528, 306, "5", 1 );
		TextOut( hDC, 982, 306, "5", 1 );

		TextOut( hDC, 622, 480, "SPEEDBRAKE  %", 13 );
		TextOut( hDC, 528, 560, "0", 1 );
		TextOut( hDC, 604, 560, "20", 2 );
		TextOut( hDC, 696, 560, "40", 2 );
		TextOut( hDC, 786, 560, "60", 2 );
		TextOut( hDC, 878, 560, "80", 2 );
		TextOut( hDC, 962, 560, "100", 3 );

		SetTextColor( hDC, CR_YELLOW );
		TextOut( hDC, 148, 462, "0", 1 );
		TextOut( hDC, 754, 106, "0", 1 );
		TextOut( hDC, 756, 306, "0", 1 );

		TextOut( hDC, 702, 516, "ACTUAL", 6 );

		SetTextColor( hDC, CR_CYAN );
		TextOut( hDC, 702, 722, "COMMAND", 7 );

		// white lines
		if (active) SelectObject( hDC, gdiWhitePen );
		else SelectObject( hDC, gdiRedPen );

		// elevons
		MoveToEx( hDC, 64, 194, NULL );
		LineTo( hDC, 64, 634 );
		MoveToEx( hDC, 102, 194, NULL );
		LineTo( hDC, 102, 634 );
		MoveToEx( hDC, 222, 194, NULL );
		LineTo( hDC, 222, 634 );
		MoveToEx( hDC, 260, 194, NULL );
		LineTo( hDC, 260, 634 );
		for (int i = 0; i < 4; i++)
		{
			MoveToEx( hDC, 62, 194 + (i * 80), NULL );
			LineTo( hDC, 44, 194 + (i * 80) );

			MoveToEx( hDC, 102, 194 + (i * 80), NULL );
			LineTo( hDC, 120, 194 + (i * 80) );

			MoveToEx( hDC, 220, 194 + (i * 80), NULL );
			LineTo( hDC, 202, 194 + (i * 80) );

			MoveToEx( hDC, 260, 194 + (i * 80), NULL );
			LineTo( hDC, 278, 194 + (i * 80) );
		}
		for (int i = 0; i < 3; i++)
		{
			MoveToEx( hDC, 62, 234 + (i * 80), NULL );
			LineTo( hDC, 36, 234 + (i * 80) );

			MoveToEx( hDC, 102, 234 + (i * 80), NULL );
			LineTo( hDC, 128, 234 + (i * 80) );

			MoveToEx( hDC, 220, 234 + (i * 80), NULL );
			LineTo( hDC, 194, 234 + (i * 80) );

			MoveToEx( hDC, 260, 234 + (i * 80), NULL );
			LineTo( hDC, 286, 234 + (i * 80) );
		}
		// (yellow line)
		for (int i = 0; i < 2; i++)
		{
			MoveToEx( hDC, 62, 514 + (i * 80), NULL );
			LineTo( hDC, 44, 514 + (i * 80) );

			MoveToEx( hDC, 102, 514 + (i * 80), NULL );
			LineTo( hDC, 120, 514 + (i * 80) );

			MoveToEx( hDC, 220, 514 + (i * 80), NULL );
			LineTo( hDC, 202, 514 + (i * 80) );

			MoveToEx( hDC, 260, 514 + (i * 80), NULL );
			LineTo( hDC, 278, 514 + (i * 80) );
		}
		for (int i = 0; i < 2; i++)
		{
			MoveToEx( hDC, 62, 554 + (i * 80), NULL );
			LineTo( hDC, 36, 554 + (i * 80) );

			MoveToEx( hDC, 102, 554 + (i * 80), NULL );
			LineTo( hDC, 128, 554 + (i * 80) );

			MoveToEx( hDC, 220, 554 + (i * 80), NULL );
			LineTo( hDC, 194, 554 + (i * 80) );

			MoveToEx( hDC, 260, 554 + (i * 80), NULL );
			LineTo( hDC, 286, 554 + (i * 80) );
		}

		// body flap
		MoveToEx( hDC, 394, 194, NULL );
		LineTo( hDC, 394, 634 );
		for (int i = 0; i < 6; i++)
		{
			MoveToEx( hDC, 394, 194 + (i * 88), NULL );
			LineTo( hDC, 420, 194 + (i * 88) );
		}
		for (int i = 0; i < 5; i++)
		{
			MoveToEx( hDC, 394, 238 + (i * 88), NULL );
			LineTo( hDC, 412, 238 + (i * 88) );
		}

		// rudder
		MoveToEx( hDC, 540, 158, NULL );
		LineTo( hDC, 996, 158 );
		for (int i = 0; i < 3; i++)
		{
			MoveToEx( hDC, 540 + (i * 76), 156, NULL );
			LineTo( hDC, 540 + (i * 76), 130 );

			MoveToEx( hDC, 578 + (i * 76), 156, NULL );
			LineTo( hDC, 578 + (i * 76), 138 );
		}
		// (yellow line)
		for (int i = 0; i < 3; i++)
		{
			MoveToEx( hDC, 806 + (i * 76), 156, NULL );
			LineTo( hDC, 806 + (i * 76), 138 );

			MoveToEx( hDC, 844 + (i * 76), 156, NULL );
			LineTo( hDC, 844 + (i * 76), 130 );
		}

		// aileron
		MoveToEx( hDC, 540, 358, NULL );
		LineTo( hDC, 996, 358 );

		MoveToEx( hDC, 540, 356, NULL );
		LineTo( hDC, 540, 330 );
		MoveToEx( hDC, 562, 356, NULL );
		LineTo( hDC, 562, 338 );
		MoveToEx( hDC, 586, 356, NULL );
		LineTo( hDC, 586, 330 );
		MoveToEx( hDC, 608, 356, NULL );
		LineTo( hDC, 608, 338 );
		MoveToEx( hDC, 632, 356, NULL );
		LineTo( hDC, 632, 330 );
		MoveToEx( hDC, 654, 356, NULL );
		LineTo( hDC, 654, 338 );
		MoveToEx( hDC, 676, 356, NULL );
		LineTo( hDC, 676, 330 );
		MoveToEx( hDC, 700, 356, NULL );
		LineTo( hDC, 700, 338 );
		MoveToEx( hDC, 722, 356, NULL );
		LineTo( hDC, 722, 330 );
		MoveToEx( hDC, 746, 356, NULL );
		LineTo( hDC, 746, 338 );
		// (yellow line)
		MoveToEx( hDC, 790, 356, NULL );
		LineTo( hDC, 790, 338 );
		MoveToEx( hDC, 814, 356, NULL );
		LineTo( hDC, 814, 330 );
		MoveToEx( hDC, 836, 356, NULL );
		LineTo( hDC, 836, 338 );
		MoveToEx( hDC, 860, 356, NULL );
		LineTo( hDC, 860, 330 );
		MoveToEx( hDC, 882, 356, NULL );
		LineTo( hDC, 882, 338 );
		MoveToEx( hDC, 904, 356, NULL );
		LineTo( hDC, 904, 330 );
		MoveToEx( hDC, 928, 356, NULL );
		LineTo( hDC, 928, 338 );
		MoveToEx( hDC, 950, 356, NULL );
		LineTo( hDC, 950, 330 );
		MoveToEx( hDC, 974, 356, NULL );
		LineTo( hDC, 974, 338 );
		MoveToEx( hDC, 996, 356, NULL );
		LineTo( hDC, 996, 330 );

		// speedbrake
		MoveToEx( hDC, 540, 612, NULL );
		LineTo( hDC, 996, 612 );
		MoveToEx( hDC, 540, 610, NULL );
		LineTo( hDC, 540, 584 );
		MoveToEx( hDC, 586, 610, NULL );
		LineTo( hDC, 586, 592 );
		MoveToEx( hDC, 632, 610, NULL );
		LineTo( hDC, 632, 584 );
		MoveToEx( hDC, 676, 610, NULL );
		LineTo( hDC, 676, 592 );
		MoveToEx( hDC, 722, 610, NULL );
		LineTo( hDC, 722, 584 );
		MoveToEx( hDC, 768, 610, NULL );
		LineTo( hDC, 768, 592 );
		MoveToEx( hDC, 814, 610, NULL );
		LineTo( hDC, 814, 584 );
		MoveToEx( hDC, 860, 610, NULL );
		LineTo( hDC, 860, 592 );
		MoveToEx( hDC, 904, 610, NULL );
		LineTo( hDC, 904, 584 );
		MoveToEx( hDC, 950, 610, NULL );
		LineTo( hDC, 950, 592 );
		MoveToEx( hDC, 996, 610, NULL );
		LineTo( hDC, 996, 584 );

		MoveToEx( hDC, 540, 652, NULL );
		LineTo( hDC, 996, 652 );
		MoveToEx( hDC, 540, 652, NULL );
		LineTo( hDC, 540, 678 );
		MoveToEx( hDC, 586, 652, NULL );
		LineTo( hDC, 586, 670 );
		MoveToEx( hDC, 632, 652, NULL );
		LineTo( hDC, 632, 678 );
		MoveToEx( hDC, 676, 652, NULL );
		LineTo( hDC, 676, 670 );
		MoveToEx( hDC, 722, 652, NULL );
		LineTo( hDC, 722, 678 );
		MoveToEx( hDC, 768, 652, NULL );
		LineTo( hDC, 768, 670 );
		MoveToEx( hDC, 814, 652, NULL );
		LineTo( hDC, 814, 678 );
		MoveToEx( hDC, 860, 652, NULL );
		LineTo( hDC, 860, 670 );
		MoveToEx( hDC, 904, 652, NULL );
		LineTo( hDC, 904, 678 );
		MoveToEx( hDC, 950, 652, NULL );
		LineTo( hDC, 950, 670 );
		MoveToEx( hDC, 996, 652, NULL );
		LineTo( hDC, 996, 678 );

		// white boxes
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 910, 510, 988, 544 );
		Rectangle( hDC, 910, 716, 988, 750 );

		// yellow lines
		if (active) SelectObject( hDC, gdiYellowPen );
		else SelectObject( hDC, gdiRedPen );

		MoveToEx( hDC, 62, 474, NULL );
		LineTo( hDC, 36, 474 );
		MoveToEx( hDC, 102, 474, NULL );
		LineTo( hDC, 128, 474 );

		MoveToEx( hDC, 220, 474, NULL );
		LineTo( hDC, 194, 474 );
		MoveToEx( hDC, 260, 474, NULL );
		LineTo( hDC, 286, 474 );

		MoveToEx( hDC, 768, 156, NULL );
		LineTo( hDC, 768, 130 );

		MoveToEx( hDC, 768, 356, NULL );
		LineTo( hDC, 768, 330 );

		// body flap trail mark
		SelectObject( hDC, gdiYellowPen );
		SelectObject( hDC, gdiYellowBrush );
		tri[0].x = 414;
		tri[0].y = 344;
		tri[1].x = 434;
		tri[1].y = 334;
		tri[2].x = 434;
		tri[2].y = 354;
		Polygon( hDC, tri, 3 );
		Rectangle( hDC, 432, 336, 452, 356 );

		if (!active) return;

		// elevons
		nPos = Round( 474 + (8 * range( -35.0, LOB, 20.0 )) );
		tri[0].x = 44;
		tri[0].y = nPos;
		tri[1].x = 76;
		tri[1].y = nPos - 16;
		tri[2].x = 76;
		tri[2].y = nPos + 16;
		Polygon( hDC, tri, 3 );

		nPos = Round( 474 + (8 * range( -35.0, LIB, 20.0 )) );
		tri[0].x = 120;
		tri[0].y = nPos;
		tri[1].x = 88;
		tri[1].y = nPos - 16;
		tri[2].x = 88;
		tri[2].y = nPos + 16;
		Polygon( hDC, tri, 3 );

		nPos = Round( 474 + (8 * range( -35.0, RIB, 20.0 )) );
		tri[0].x = 202;
		tri[0].y = nPos;
		tri[1].x = 234;
		tri[1].y = nPos - 16;
		tri[2].x = 234;
		tri[2].y = nPos + 16;
		Polygon( hDC, tri, 3 );

		nPos = Round( 474 + (8 * range( -35.0, ROB, 20.0 )) );
		tri[0].x = 278;
		tri[0].y = nPos;
		tri[1].x = 246;
		tri[1].y = nPos - 16;
		tri[2].x = 246;
		tri[2].y = nPos + 16;
		Polygon( hDC, tri, 3 );

		// body flap
		nPos = Round( 194 + (4.4 * range( 0.0, DBFOFB, 100.0 )) );
		tri[0].x = 412;
		tri[0].y = nPos;
		tri[1].x = 380;
		tri[1].y = nPos - 16;
		tri[2].x = 380;
		tri[2].y = nPos + 16;
		Polygon( hDC, tri, 3 );

		// rudder
		nPos = Round( 768 - (7.6 * range( -30.0, DRFB, 30.0 )) );
		tri[0].x = nPos;
		tri[0].y = 140;
		tri[1].x = nPos - 16;
		tri[1].y = 172;
		tri[2].x = nPos + 16;
		tri[2].y = 172;
		Polygon( hDC, tri, 3 );

		// aileron
		nPos = Round( 768 + (45.6 * range( -5.0, DAFB, 5.0 )) );
		tri[0].x = nPos;
		tri[0].y = 340;
		tri[1].x = nPos - 16;
		tri[1].y = 372;
		tri[2].x = nPos + 16;
		tri[2].y = 372;
		Polygon( hDC, tri, 3 );

		// speedbrake
		SetTextColor( hDC, CR_YELLOW );
		dNum = range( 0.0, Speedbrake_Pos, 100.0 );
		sprintf_s( cbuf, 8, "%03.0f", dNum );
		TextOut( hDC, 918, 516, cbuf, strlen( cbuf ) );
		nPos = Round( 540 + (4.56 * dNum) );
		tri[0].x = nPos;
		tri[0].y = 594;
		tri[1].x = nPos + 16;
		tri[1].y = 626;
		tri[2].x = nPos - 16;
		tri[2].y = 626;
		Polygon( hDC, tri, 3 );

		SelectObject( hDC, gdiCyanPen );
		SelectObject( hDC, gdiCyanBrush );
		SetTextColor( hDC, CR_CYAN );
		dNum = range( 0.0, Speedbrake_Cmd, 100.0 );
		sprintf_s( cbuf, 8, "%03.0f", dNum );
		TextOut( hDC, 918, 722, cbuf, strlen( cbuf ) );
		nPos = Round( 540 + (4.56 * dNum) );
		tri[0].x = nPos;
		tri[0].y = 670;
		tri[1].x = nPos + 16;
		tri[1].y = 638;
		tri[2].x = nPos - 16;
		tri[2].y = 638;
		Polygon( hDC, tri, 3 );
		return;
	}

	void MDU::SPI( oapi::Sketchpad* skp )
	{
		oapi::IVECTOR2 tri[3];
		int nPos;
		double dNum;
		char cbuf[8];
		bool active;
		double LOB;
		double LIB;
		double RIB;
		double ROB;
		double DAFB;
		double DRFB;
		double DBFOFB;
		double Speedbrake_Pos;
		double Speedbrake_Cmd;
		active = GetIDP()->GetAerosurfacePositions( LOB, LIB, RIB, ROB, DAFB, DRFB, DBFOFB, Speedbrake_Pos, Speedbrake_Cmd );

		skp->SetFont( skpSSVAFont_h19w19bold );
		skp->SetPen( skpDarkGreenPen );
		skp->SetTextColor( CR_DARK_GREEN );

		skp->Line( 6, 150, 6, 108 );
		skp->Line( 6, 110, 154, 110 );
		skp->Line( 306, 110, 454, 110 );
		skp->Line( 454, 110, 454, 150 );

		skp->Line( 6, 672, 6, 712 );
		skp->Line( 6, 712, 154, 712 );
		skp->Line( 306, 712, 454, 712 );
		skp->Line( 454, 712, 454, 672 );

		skp->Text( 176, 98, "TE UP", 5 );
		skp->Text( 176, 700, "TE DN", 5 );

		skp->Text( 518, 216, "L RUD", 5 );
		skp->Text( 916, 216, "R RUD", 5 );

		skp->Text( 518, 416, "L AIL", 5 );
		skp->Text( 916, 416, "R AIL", 5 );

		// gray boxes
		skp->SetBrush( skpDarkGrayBrush );
		skp->SetPen( skpDarkGrayPen );

		skp->Rectangle( 72, 182, 94, 646 );
		skp->Rectangle( 230, 182, 254, 646 );

		skp->Rectangle( 362, 182, 388, 646 );

		skp->Rectangle( 528, 166, 1008, 194 );

		skp->Rectangle( 528, 366, 1008, 392 );

		skp->Rectangle( 528, 620, 1008, 646 );

		skp->SetTextColor( CR_WHITE );
		skp->Text( 50, 54, "ELEVONS", 7 );
		skp->Text( 90, 80, "DEG", 3 );
		skp->Text( 126, 214, "-30", 3 );
		skp->Text( 126, 294, "-20", 3 );
		skp->Text( 126, 376, "-10", 3 );
		skp->Text( 126, 534, "+10", 3 );
		skp->Text( 126, 614, "+20", 3 );

		skp->Text( 272, 54, "BODY FLAP", 9 );
		skp->Text( 356, 80, "%", 1 );
		skp->Text( 438, 184, "0", 1 );
		skp->Text( 438, 272, "20", 2 );
		skp->Text( 438, 360, "40", 2 );
		skp->Text( 438, 448, "60", 2 );
		skp->Text( 438, 536, "80", 2 );
		skp->Text( 438, 624, "100", 3 );

		skp->Text( 650, 62, "RUDDER-DEG", 10 );
		skp->Text( 512, 106, "30", 2 );
		skp->Text( 588, 106, "20", 2 );
		skp->Text( 664, 106, "10", 2 );
		skp->Text( 816, 106, "10", 2 );
		skp->Text( 892, 106, "20", 2 );
		skp->Text( 968, 106, "30", 2 );

		skp->Text( 650, 278, "AILERON-DEG", 11 );
		skp->Text( 528, 306, "5", 1 );
		skp->Text( 982, 306, "5", 1 );

		skp->Text( 622, 480, "SPEEDBRAKE  %", 13 );
		skp->Text( 528, 560, "0", 1 );
		skp->Text( 604, 560, "20", 2 );
		skp->Text( 696, 560, "40", 2 );
		skp->Text( 786, 560, "60", 2 );
		skp->Text( 878, 560, "80", 2 );
		skp->Text( 962, 560, "100", 3 );

		skp->SetTextColor( CR_YELLOW );
		skp->Text( 148, 462, "0", 1 );
		skp->Text( 754, 106, "0", 1 );
		skp->Text( 756, 306, "0", 1 );

		skp->Text( 702, 516, "ACTUAL", 6 );

		skp->SetTextColor( CR_CYAN );
		skp->Text( 702, 722, "COMMAND", 7 );

		// white lines
		if (active) skp->SetPen( skpWhitePen );
		else skp->SetPen( skpRedPen );

		// elevons
		skp->Line( 64, 194, 64, 634 );
		skp->Line( 62, 194, 44, 194 );
		skp->Line( 62, 234, 36, 234 );
		skp->Line( 62, 274, 44, 274 );
		skp->Line( 62, 314, 36, 314 );
		skp->Line( 62, 354, 44, 354 );
		skp->Line( 62, 394, 36, 394 );
		skp->Line( 62, 434, 44, 434 );
		// (yellow line)
		skp->Line( 62, 514, 44, 514 );
		skp->Line( 62, 554, 36, 554 );
		skp->Line( 62, 594, 44, 594 );
		skp->Line( 62, 634, 36, 634 );

		skp->Line( 102, 194, 102, 634 );
		skp->Line( 102, 194, 120, 194 );
		skp->Line( 102, 234, 128, 234 );
		skp->Line( 102, 274, 120, 274 );
		skp->Line( 102, 314, 128, 314 );
		skp->Line( 102, 354, 120, 354 );
		skp->Line( 102, 394, 128, 394 );
		skp->Line( 102, 434, 120, 434 );
		// (yellow line)
		skp->Line( 102, 514, 120, 514 );
		skp->Line( 102, 554, 128, 554 );
		skp->Line( 102, 594, 120, 594 );
		skp->Line( 102, 634, 128, 634 );

		skp->Line( 222, 194, 222, 634 );
		skp->Line( 220, 194, 202, 194 );
		skp->Line( 220, 234, 194, 234 );
		skp->Line( 220, 274, 202, 274 );
		skp->Line( 220, 314, 194, 314 );
		skp->Line( 220, 354, 202, 354 );
		skp->Line( 220, 394, 194, 394 );
		skp->Line( 220, 434, 202, 434 );
		// (yellow line)
		skp->Line( 220, 514, 202, 514 );
		skp->Line( 220, 554, 194, 554 );
		skp->Line( 220, 594, 202, 594 );
		skp->Line( 220, 634, 194, 634 );

		skp->Line( 260, 194, 260, 634 );
		skp->Line( 260, 194, 278, 194 );
		skp->Line( 260, 234, 286, 234 );
		skp->Line( 260, 274, 278, 274 );
		skp->Line( 260, 314, 286, 314 );
		skp->Line( 260, 354, 278, 354 );
		skp->Line( 260, 394, 286, 394 );
		skp->Line( 260, 434, 278, 434 );
		// (yellow line)
		skp->Line( 260, 514, 278, 514 );
		skp->Line( 260, 554, 286, 554 );
		skp->Line( 260, 594, 278, 594 );
		skp->Line( 260, 634, 286, 634 );

		// body flap
		skp->Line( 394, 194, 394, 634 );
		skp->Line( 394, 194, 420, 194 );
		skp->Line( 394, 238, 412, 238 );
		skp->Line( 394, 282, 420, 282 );
		skp->Line( 394, 326, 412, 326 );
		skp->Line( 394, 370, 420, 370 );
		skp->Line( 394, 414, 412, 414 );
		skp->Line( 394, 458, 420, 458 );
		skp->Line( 394, 502, 412, 502 );
		skp->Line( 394, 546, 420, 546 );
		skp->Line( 394, 590, 412, 590 );
		skp->Line( 394, 634, 420, 634 );

		// rudder
		skp->Line( 540, 158, 996, 158 );
		skp->Line( 540, 156, 540, 130 );
		skp->Line( 578, 156, 578, 138 );
		skp->Line( 616, 156, 616, 130 );
		skp->Line( 654, 156, 654, 138 );
		skp->Line( 692, 156, 692, 130 );
		skp->Line( 730, 156, 730, 138 );
		// (yellow line)
		skp->Line( 806, 156, 806, 138 );
		skp->Line( 844, 156, 844, 130 );
		skp->Line( 882, 156, 882, 138 );
		skp->Line( 920, 156, 920, 130 );
		skp->Line( 958, 156, 958, 138 );
		skp->Line( 996, 156, 996, 130 );

		// aileron
		skp->Line( 540, 358, 996, 358 );
		skp->Line( 540, 356, 540, 330 );
		skp->Line( 562, 356, 562, 338 );
		skp->Line( 586, 356, 586, 330 );
		skp->Line( 608, 356, 608, 338 );
		skp->Line( 632, 356, 632, 330 );
		skp->Line( 654, 356, 654, 338 );
		skp->Line( 676, 356, 676, 330 );
		skp->Line( 700, 356, 700, 338 );
		skp->Line( 722, 356, 722, 330 );
		skp->Line( 746, 356, 746, 338 );
		// (yellow line)
		skp->Line( 790, 356, 790, 338 );
		skp->Line( 814, 356, 814, 330 );
		skp->Line( 836, 356, 836, 338 );
		skp->Line( 860, 356, 860, 330 );
		skp->Line( 882, 356, 882, 338 );
		skp->Line( 904, 356, 904, 330 );
		skp->Line( 928, 356, 928, 338 );
		skp->Line( 950, 356, 950, 330 );
		skp->Line( 974, 356, 974, 338 );
		skp->Line( 996, 356, 996, 330 );

		// speedbrake
		skp->Line( 540, 612, 996, 612 );
		skp->Line( 540, 610, 540, 584 );
		skp->Line( 586, 610, 586, 592 );
		skp->Line( 632, 610, 632, 584 );
		skp->Line( 676, 610, 676, 592 );
		skp->Line( 722, 610, 722, 584 );
		skp->Line( 768, 610, 768, 592 );
		skp->Line( 814, 610, 814, 584 );
		skp->Line( 860, 610, 860, 592 );
		skp->Line( 904, 610, 904, 584 );
		skp->Line( 950, 610, 950, 592 );
		skp->Line( 996, 610, 996, 584 );

		skp->Line( 540, 652, 996, 652 );
		skp->Line( 540, 652, 540, 678 );
		skp->Line( 586, 652, 586, 670 );
		skp->Line( 632, 652, 632, 678 );
		skp->Line( 676, 652, 676, 670 );
		skp->Line( 722, 652, 722, 678 );
		skp->Line( 768, 652, 768, 670 );
		skp->Line( 814, 652, 814, 678 );
		skp->Line( 860, 652, 860, 670 );
		skp->Line( 904, 652, 904, 678 );
		skp->Line( 950, 652, 950, 670 );
		skp->Line( 996, 652, 996, 678 );

		// white boxes
		skp->SetBrush( skpBlackBrush );
		skp->Rectangle( 910, 510, 988, 544 );
		skp->Rectangle( 910, 716, 988, 750 );

		// yellow lines
		if (active) skp->SetPen( skpYellowPen );
		else skp->SetPen( skpRedPen );

		skp->Line( 62, 474, 36, 474 );
		skp->Line( 102, 474, 128, 474 );

		skp->Line( 220, 474, 194, 474 );
		skp->Line( 260, 474, 286, 474 );

		skp->Line( 768, 156, 768, 130 );

		skp->Line( 768, 356, 768, 330 );

		// body flap trail mark
		skp->SetPen( skpYellowPen );
		skp->SetBrush( skpYellowBrush );
		tri[0].x = 414;
		tri[0].y = 344;
		tri[1].x = 434;
		tri[1].y = 334;
		tri[2].x = 434;
		tri[2].y = 354;
		skp->Polygon( tri, 3 );
		skp->Rectangle( 432, /*336*/334, 452, 356 );

		if (!active) return;

		// elevons
		nPos = Round( 474 + (8 * range( -35.0, LOB, 20.0 )) );
		tri[0].x = 44;
		tri[0].y = nPos;
		tri[1].x = 76;
		tri[1].y = nPos - 16;
		tri[2].x = 76;
		tri[2].y = nPos + 16;
		skp->Polygon( tri, 3 );

		nPos = Round( 474 + (8 * range( -35.0, LIB, 20.0 )) );
		tri[0].x = 120;
		tri[0].y = nPos;
		tri[1].x = 88;
		tri[1].y = nPos - 16;
		tri[2].x = 88;
		tri[2].y = nPos + 16;
		skp->Polygon( tri, 3 );

		nPos = Round( 474 + (8 * range( -35.0, RIB, 20.0 )) );
		tri[0].x = 202;
		tri[0].y = nPos;
		tri[1].x = 234;
		tri[1].y = nPos - 16;
		tri[2].x = 234;
		tri[2].y = nPos + 16;
		skp->Polygon( tri, 3 );

		nPos = Round( 474 + (8 * range( -35.0, ROB, 20.0 )) );
		tri[0].x = 278;
		tri[0].y = nPos;
		tri[1].x = 246;
		tri[1].y = nPos - 16;
		tri[2].x = 246;
		tri[2].y = nPos + 16;
		skp->Polygon( tri, 3 );

		// body flap
		nPos = Round( 194 + (4.4 * range( 0.0, DBFOFB, 100.0 )) );
		tri[0].x = 412;
		tri[0].y = nPos;
		tri[1].x = 380;
		tri[1].y = nPos - 16;
		tri[2].x = 380;
		tri[2].y = nPos + 16;
		skp->Polygon( tri, 3 );

		// rudder
		nPos = Round( 768 - (7.6 * range( -30.0, DRFB, 30.0 )) );
		tri[0].x = nPos;
		tri[0].y = 140;
		tri[1].x = nPos - 16;
		tri[1].y = 172;
		tri[2].x = nPos + 16;
		tri[2].y = 172;
		skp->Polygon( tri, 3 );

		// aileron
		nPos = Round( 768 + (45.6 * range( -5.0, DAFB, 5.0 )) );
		tri[0].x = nPos;
		tri[0].y = 340;
		tri[1].x = nPos - 16;
		tri[1].y = 372;
		tri[2].x = nPos + 16;
		tri[2].y = 372;
		skp->Polygon( tri, 3 );

		// speedbrake
		skp->SetTextColor( CR_YELLOW );
		dNum = range( 0.0, Speedbrake_Pos, 100.0 );
		sprintf_s( cbuf, 8, "%03.0f", dNum );
		skp->Text( 918, 516, cbuf, strlen( cbuf ) );
		nPos = Round( 540 + (4.56 * dNum) );
		tri[0].x = nPos;
		tri[0].y = 594;
		tri[1].x = nPos + 16;
		tri[1].y = 626;
		tri[2].x = nPos - 16;
		tri[2].y = 626;
		skp->Polygon( tri, 3 );

		skp->SetPen( skpCyanPen );
		skp->SetBrush( skpCyanBrush );
		skp->SetTextColor( CR_CYAN );
		dNum = range( 0.0, Speedbrake_Cmd, 100.0 );
		sprintf_s( cbuf, 8, "%03.0f", dNum );
		skp->Text( 918, 722, cbuf, strlen( cbuf ) );
		nPos = Round( 540 + (4.56 * dNum) );
		tri[0].x = nPos;
		tri[0].y = 670;
		tri[1].x = nPos + 16;
		tri[1].y = 638;
		tri[2].x = nPos - 16;
		tri[2].y = 638;
		skp->Polygon( tri, 3 );
		return;
	}
}

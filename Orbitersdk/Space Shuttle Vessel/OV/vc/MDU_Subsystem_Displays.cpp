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
		SelectObject( hDC, gdiSSVBFont_h18w9 );
		SelectObject( hDC, gdiDarkGreenPen );
		SelectObject( hDC, gdiBlackBrush );

		TextOut( hDC, 76, 1, "OMS", 3 );
		TextOut( hDC, 301, 1, "MPS", 3 );
		MoveToEx( hDC, 163, 12, NULL );
		LineTo( hDC, 163, 396 );
		MoveToEx( hDC, 29, 12, NULL );
		LineTo( hDC, 56, 12 );
		MoveToEx( hDC, 115, 12, NULL );
		LineTo( hDC, 292, 12 );
		MoveToEx( hDC, 335, 12, NULL );
		LineTo( hDC, 480, 12 );
		MoveToEx( hDC, 29, 12, NULL );
		LineTo( hDC, 29, 45 );
		MoveToEx( hDC, 480, 12, NULL );
		LineTo( hDC, 480, 45 );

		SetTextColor( hDC, CR_WHITE );
		SelectObject( hDC, gdiSSVAFont_h10w10bold );

		//OMS
		TextOut( hDC, 73, 28, "L", 1 );
		TextOut( hDC, 124, 28, "R", 1 );
		Rectangle( hDC, 55, 42, 99, 59 );
		Rectangle( hDC, 107, 42, 151, 59 );
		Rectangle( hDC, 55, 151, 99, 168 );
		Rectangle( hDC, 107, 151, 151, 168 );
		Rectangle( hDC, 56, 275, 92, 300 );
		Rectangle( hDC, 110, 275, 146, 300 );
		//MPS
		TextOut( hDC, 317, 28, "L/2", 3 );
		TextOut( hDC, 372, 22, "C/1", 3 );
		TextOut( hDC, 426, 28, "R/3", 3 );
		//Tank P
		Rectangle( hDC, 211, 42, 255, 59 );
		Rectangle( hDC, 308, 42, 352, 59 );
		Rectangle( hDC, 364, 36, 408, 53 );
		Rectangle( hDC, 420, 42, 464, 59 );
		//Reg Press
		Rectangle( hDC, 211, 151, 255, 168 );
		Rectangle( hDC, 308, 151, 352, 168 );
		Rectangle( hDC, 364, 145, 408, 163 );
		Rectangle( hDC, 420, 151, 464, 168 );
		//Engine Pc
		TextOut( hDC, 313, 260, "L/2", 3 );
		TextOut( hDC, 366, 246, "C/1", 3 );
		TextOut( hDC, 422, 260, "R/3", 3 );
		Rectangle( hDC, 310, 275, 346, 300 );
		Rectangle( hDC, 362, 260, 398, 285 );
		Rectangle( hDC, 420, 275, 456, 300 );
		// ENG MANF
		Rectangle( hDC, 176, 297, 212, 314 );
		Rectangle( hDC, 227, 297, 263, 314 );

		SelectObject(hDC, gdiWhitePen);

		//OMS
		TextOut( hDC, 32, 68, "He", 2 );
		TextOut( hDC, 32, 85, "TK", 2 );
		TextOut( hDC, 36, 102, "P", 1 );
		Rectangle( hDC, 68, 68, 87, 129 );
		Rectangle( hDC, 120, 68, 139, 129 );
		MoveToEx( hDC, 86, 110, NULL );
		LineTo( hDC, 96, 110 );
		MoveToEx( hDC, 138, 110, NULL );
		LineTo( hDC, 148, 110 );

		TextOut( hDC, 32, 183, "N", 1 );
		TextOut( hDC, 42, 186, "2", 1 );
		TextOut( hDC, 32, 200, "TK", 2 );
		TextOut( hDC, 36, 217, "P", 1 );
		Rectangle( hDC, 68, 177, 87, 238 );
		Rectangle( hDC, 120, 177, 139, 238 );
		MoveToEx( hDC, 86, 213, NULL );
		LineTo( hDC, 96, 213 );
		MoveToEx( hDC, 138, 213, NULL );
		LineTo( hDC, 148, 213 );

		TextOut( hDC, 68, 260, "L", 1 );
		TextOut( hDC, 121, 260, "R", 1 );
		TextOut( hDC, 35, 335, "Pc", 2 );
		TextOut( hDC, 41, 358, "%", 1 );
		Rectangle( hDC, 64, 306, 84, 403 );
		Rectangle( hDC, 118, 306, 138, 403 );
		MoveToEx( hDC, 83, 339, NULL );
		LineTo( hDC, 93, 339 );
		MoveToEx( hDC, 137, 339, NULL );
		LineTo( hDC, 147, 339 );

		//MPS
		TextOut( hDC, 213, 28, "PNEU", 4 );
		TextOut( hDC, 174, 91, "TANK", 4 );
		TextOut( hDC, 189, 108, "P", 1 );
		Rectangle( hDC, 224, 68, 243, 129 );
		TextOut( hDC, 282, 68, "He", 2 );
		TextOut( hDC, 273, 85, "TANK", 4 );
		TextOut( hDC, 285, 102, "P", 1 );
		Rectangle( hDC, 321, 68, 340, 129 );
		Rectangle( hDC, 377, 68, 396, 129 );
		Rectangle( hDC, 433, 68, 452, 129 );
		MoveToEx( hDC, 242, 104, NULL );
		LineTo( hDC, 252, 104 );
		MoveToEx( hDC, 339, 125, NULL );
		LineTo( hDC, 349, 125 );
		MoveToEx( hDC, 395, 125, NULL );
		LineTo( hDC, 405, 125 );
		MoveToEx( hDC, 451, 125, NULL );
		LineTo( hDC, 461, 125 );

		TextOut( hDC, 178, 183, "REG", 3 );
		TextOut( hDC, 189, 202, "P", 1 );
		Rectangle( hDC, 224, 177, 243, 238 );
		TextOut( hDC, 275, 179, "He", 2 );
		TextOut( hDC, 266, 196, "REG A", 5 );
		TextOut( hDC, 285, 213, "P", 1 );
		Rectangle( hDC, 321, 177, 340, 238 );
		Rectangle( hDC, 377, 177, 396, 238 );
		Rectangle( hDC, 433, 177, 452, 238 );
		MoveToEx( hDC, 242, 196, NULL );
		LineTo( hDC, 252, 196 );
		MoveToEx( hDC, 242, 221, NULL );
		LineTo( hDC, 252, 221 );
		MoveToEx( hDC, 339, 196, NULL );
		LineTo( hDC, 349, 196 );
		MoveToEx( hDC, 339, 221, NULL );
		LineTo( hDC, 349, 221 );
		MoveToEx( hDC, 395, 196, NULL );
		LineTo( hDC, 405, 196 );
		MoveToEx( hDC, 395, 221, NULL );
		LineTo( hDC, 405, 221 );
		MoveToEx( hDC, 451, 196, NULL );
		LineTo( hDC, 461, 196 );
		MoveToEx( hDC, 451, 221, NULL );
		LineTo( hDC, 461, 221 );

		TextOut( hDC, 343, 335, "Pc", 2 );
		TextOut( hDC, 349, 347, "%", 1 );
		TextOut( hDC, 398, 335, "Pc", 2 );
		TextOut( hDC, 404, 347, "%", 1 );
		Rectangle( hDC, 318, 306, 338, 403 );
		Rectangle( hDC, 371, 306, 391, 403 );
		Rectangle( hDC, 428, 306, 448, 403 );
		MoveToEx( hDC, 337, 315, NULL );
		LineTo( hDC, 347, 315 );
		MoveToEx( hDC, 390, 315, NULL );
		LineTo( hDC, 400, 315 );
		MoveToEx( hDC, 447, 315, NULL );
		LineTo( hDC, 457, 315 );
		MoveToEx( hDC, 337, 369, NULL );
		LineTo( hDC, 347, 369 );
		MoveToEx( hDC, 390, 369, NULL );
		LineTo( hDC, 400, 369 );
		MoveToEx( hDC, 447, 369, NULL );
		LineTo( hDC, 457, 369 );

		TextOut( hDC, 182, 262, "ENG MANF", 8 );
		TextOut( hDC, 179, 279, "LO2", 3 );
		TextOut( hDC, 229, 279, "LH2", 3 );
		TextOut( hDC, 215, 316, "P", 1 );
		TextOut( hDC, 215, 332, "S", 1 );
		TextOut( hDC, 215, 348, "I", 1 );
		TextOut( hDC, 215, 364, "A", 1 );
		Rectangle( hDC, 184, 326, 203, 387 );
		Rectangle( hDC, 235, 326, 254, 387 );
		MoveToEx( hDC, 202, 338, NULL );
		LineTo( hDC, 212, 338 );
		MoveToEx( hDC, 253, 348, NULL );
		LineTo( hDC, 263, 348 );

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
		TextOut( hDC, 56, 45, cbuf, strlen( cbuf ) );
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
		Rectangle( hDC, 70, Round( (127 - 0.0114 * usNum) ), 85, 127 );

		// OMS He R
		usNum = He_R;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		TextOut( hDC, 108, 45, cbuf, strlen( cbuf ) );
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
		Rectangle( hDC, 122, Round( (127 - 0.0114 * usNum) ), 137, 127 );

		// OMS N2 L
		usNum = N2_L;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		TextOut( hDC, 56, 154, cbuf, strlen( cbuf ) );
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
		Rectangle( hDC, 122, Round( (236 - 0.019 * usNum) ), 137, 236 );

		// OMS N2 R
		usNum = N2_R;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		TextOut( hDC, 108, 154, cbuf, strlen( cbuf ) );
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
		Rectangle( hDC, 174, Round( (236 - 0.019 * usNum) ), 189, 236 );


		// He Tank Press Pneu
		usNum = HeTk_Pneu;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		TextOut( hDC, 212, 45, cbuf, strlen( cbuf ) );
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
		Rectangle( hDC, 226, Round( 212.5 - (0.0285 * usNum) ), 241, 127 );

		// He Tank Press Eng 2
		usNum = HeTk_L;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		TextOut( hDC, 309, 45, cbuf, strlen( cbuf ) );
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
		Rectangle( hDC, 323, Round( 141.25 - (0.01425 * usNum) ), 338, 127 );

		// He Tank Press Eng 1
		usNum = HeTk_C;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		TextOut( hDC, 365, 39, cbuf, strlen( cbuf ) );
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
		Rectangle( hDC, 379, Round( 141.25 - (0.01425 * usNum) ), 394, 127 );

		// He Tank Press Eng 3
		usNum = HeTk_R;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		TextOut( hDC, 421, 45, cbuf, strlen( cbuf ) );
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
		Rectangle( hDC, 435, Round( 141.25 - (0.01425 * usNum) ), 450, 127 );

		// He Reg Press Pneu
		usNum = HeReg_Pneu;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		TextOut( hDC, 212, 154, cbuf, strlen( cbuf ) );
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
		Rectangle( hDC, 226, Round( 350 - (0.19 * usNum) ), 241, 236 );

		// He Reg Press Eng 2
		usNum = HeReg_L;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		TextOut( hDC, 309, 154, cbuf, strlen( cbuf ) );
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
		Rectangle( hDC, 323, Round( 350 - (0.19 * usNum) ), 338, 236 );

		// He Reg Press Eng 1
		usNum = HeReg_C;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		TextOut( hDC, 365, 148, cbuf, strlen( cbuf ) );
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
		Rectangle( hDC, 379, Round( 350 - (0.19 * usNum) ), 394, 236 );

		// He Reg Press Eng 3
		usNum = HeReg_R;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		TextOut( hDC, 421, 154, cbuf, strlen( cbuf ) );
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
		Rectangle( hDC, 435, Round( 350 - (0.19 * usNum) ), 450, 236 );

		// ENG MANF LO2
		usNum = LO2_Manif;
		sprintf_s( cbuf, 16, "%03hu", usNum );
		TextOut( hDC, 178, 300, cbuf, strlen( cbuf ) );
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
		Rectangle( hDC, 186, Round( 385 - (0.19 * usNum) ), 201, 385 );

		// ENG MANF LH2
		usNum = LH2_Manif;
		sprintf_s( cbuf, 16, "%03hu", usNum );
		TextOut( hDC, 229, 300, cbuf, strlen( cbuf ) );
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
		Rectangle( hDC, 237, Round( 385 - (0.57 * usNum) ), 252, 385 );

		SelectObject( hDC, gdiSSVBFont_h18w9 );

		// L OMS
		usNum = PC_OMS_L;
		sprintf_s( cbuf, 16, "%03hu", usNum );
		TextOut( hDC, 60, 276, cbuf, strlen( cbuf ) );
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
		Rectangle( hDC, 66, Round( 401 - (0.775 * usNum) ), 82, 401 );

		// R OMS
		usNum = PC_OMS_R;
		sprintf_s( cbuf, 16, "%03hu", usNum );
		TextOut( hDC, 114, 276, cbuf, strlen( cbuf ) );
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
		Rectangle( hDC, 120, Round( 401 - (0.775 * usNum) ), 136, 401 );

		// PC L/2
		usNum = PC_L;
		sprintf_s( cbuf, 16, "%03hu", usNum );
		TextOut( hDC, 314, 276, cbuf, strlen( cbuf ) );
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
		Rectangle( hDC, 320, Round( 466.3895 - (1.4531 * usNum) ), 336, 401 );

		// PC C/1
		usNum = PC_C;
		sprintf_s( cbuf, 16, "%03hu", usNum );
		TextOut( hDC, 366, 261, cbuf, strlen( cbuf ) );
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
		Rectangle( hDC, 373, Round( 466.3895 - (1.4531 * usNum) ), 389, 401 );

		// PC R/3
		usNum = PC_R;
		sprintf_s( cbuf, 16, "%03hu", usNum );
		TextOut( hDC, 424, 276, cbuf, strlen( cbuf ) );
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
		Rectangle( hDC, 430, Round( 466.3895 - (1.4531 * usNum) ), 446, 401 );
		return;
	}

	void MDU::OMSMPS( oapi::Sketchpad2* skp )
	{
		unsigned short usNum;
		char cbuf[16];

		skp->SetTextColor( CR_DARK_GREEN );
		skp->SetFont( skpSSVBFont_h18w9 );
		skp->SetPen( skpDarkGreenPen );
		skp->SetBrush( skpBlackBrush );

		skp->Text( 76, 1, "OMS", 3);
		skp->Text( 301, 1, "MPS", 3);
		skp->Line( 163, 12, 163, 396 );
		skp->Line( 29, 12, 56, 12 );
		skp->Line( 115, 12, 292, 12 );
		skp->Line( 335, 12, 480, 12 );
		skp->Line( 29, 12, 29, 45 );
		skp->Line( 480, 12, 480, 45 );

		skp->SetTextColor( CR_WHITE );
		skp->SetFont( skpSSVAFont_h10w10bold );

		//OMS
		skp->Text( 73, 28, "L", 1 );
		skp->Text( 124, 28, "R", 1 );
		skp->Rectangle( 55, 42, 99, 59 );
		skp->Rectangle( 107, 42, 151, 59 );
		skp->Rectangle( 55, 151, 99, 168 );
		skp->Rectangle( 107, 151, 151, 168 );
		skp->Rectangle( 56, 275, 92, 300 );
		skp->Rectangle( 110, 275, 146, 300 );
		//MPS
		skp->Text( 317, 28, "L/2", 3 );
		skp->Text( 372, 22, "C/1", 3 );
		skp->Text( 426, 28, "R/3", 3 );
		//Tank P
		skp->Rectangle( 211, 42, 255, 59 );
		skp->Rectangle( 308, 42, 352, 59 );
		skp->Rectangle( 364, 36, 408, 53 );
		skp->Rectangle( 420, 42, 464, 59 );
		//Reg Press
		skp->Rectangle( 211, 151, 255, 168 );
		skp->Rectangle( 308, 151, 352, 168 );
		skp->Rectangle( 364, 145, 408, 163 );
		skp->Rectangle( 420, 151, 464, 168 );
		//Engine Pc
		skp->Text( 313, 260, "L/2", 3 );
		skp->Text( 366, 246, "C/1", 3 );
		skp->Text( 422, 260, "R/3", 3 );
		skp->Rectangle( 310, 275, 346, 300 );
		skp->Rectangle( 362, 260, 398, 285 );
		skp->Rectangle( 420, 275, 456, 300 );
		// ENG MANF
		skp->Rectangle( 176, 297, 212, 314 );
		skp->Rectangle( 227, 297, 263, 314 );

		skp->SetPen( skpWhitePen );

		//OMS
		skp->Text( 32, 68, "He", 2 );
		skp->Text( 32, 85, "TK", 2 );
		skp->Text( 36, 102, "P", 1 );
		skp->Rectangle( 68, 68, 87, 129 );
		skp->Rectangle( 120, 68, 139, 129 );
		skp->Line( 86, 110, 96, 110 );
		skp->Line( 138, 110, 148, 110 );

		skp->Text( 32, 183, "N", 1 );
		skp->Text( 42, 186, "2", 1 );
		skp->Text( 32, 200, "TK", 2 );
		skp->Text( 36, 217, "P", 1 );
		skp->Rectangle( 68, 177, 87, 238 );
		skp->Rectangle( 120, 177, 139, 238 );
		skp->Line( 86, 213, 96, 213 );
		skp->Line( 138, 213, 148, 213 );

		skp->Text( 68, 260, "L", 1 );
		skp->Text( 121, 260, "R", 1 );
		skp->Text( 35, 335, "Pc", 2 );
		skp->Text( 41, 358, "%", 1 );
		skp->Rectangle( 64, 306, 84, 403 );
		skp->Rectangle( 118, 306, 138, 403 );
		skp->Line( 83, 339, 93, 339 );
		skp->Line( 137, 339, 147, 339 );

		//MPS
		skp->Text( 213, 28, "PNEU", 4 );
		skp->Text( 174, 91, "TANK", 4 );
		skp->Text( 189, 108, "P", 1);
		skp->Rectangle( 224, 68, 243, 129 );
		skp->Text( 282, 68, "He", 2 );
		skp->Text( 273, 85, "TANK", 4 );
		skp->Text( 285, 102, "P", 1 );
		skp->Rectangle( 321, 68, 340, 129 );
		skp->Rectangle( 377, 68, 396, 129 );
		skp->Rectangle( 433, 68, 452, 129 );
		skp->Line( 242, 104, 252, 104 );
		skp->Line( 339, 125, 349, 125 );
		skp->Line( 395, 125, 405, 125 );
		skp->Line( 451, 125, 461, 125 );

		skp->Text( 178, 183, "REG", 3 );
		skp->Text( 189, 202, "P", 1 );
		skp->Rectangle( 224, 177, 243, 238 );
		skp->Text( 275, 179, "He", 2 );
		skp->Text( 266, 196, "REG A", 5 );
		skp->Text( 285, 213, "P", 1 );
		skp->Rectangle( 321, 177, 340, 238 );
		skp->Rectangle( 377, 177, 396, 238 );
		skp->Rectangle( 433, 177, 452, 238 );
		skp->Line( 242, 196, 252, 196 );
		skp->Line( 242, 221, 252, 221 );
		skp->Line( 339, 196, 349, 196 );
		skp->Line( 339, 221, 349, 221 );
		skp->Line( 395, 196, 405, 196 );
		skp->Line( 395, 221, 405, 221 );
		skp->Line( 451, 196, 461, 196 );
		skp->Line( 451, 221, 461, 221 );

		skp->Text( 343, 335, "Pc", 2 );
		skp->Text( 349, 347, "%", 1 );
		skp->Text( 398, 335, "Pc", 2 );
		skp->Text( 404, 347, "%", 1 );
		skp->Rectangle( 318, 306, 338, 403 );
		skp->Rectangle( 371, 306, 391, 403 );
		skp->Rectangle( 428, 306, 448, 403 );
		skp->Line( 337, 315, 347, 315 );
		skp->Line( 390, 315, 400, 315 );
		skp->Line( 447, 315, 457, 315 );
		skp->Line( 337, 369, 347, 369 );
		skp->Line( 390, 369, 400, 369 );
		skp->Line( 447, 369, 457, 369 );

		skp->Text( 182, 262, "ENG MANF", 8 );
		skp->Text( 179, 279, "LO2", 3 );
		skp->Text( 229, 279, "LH2", 3 );
		skp->Text( 215, 316, "P", 1 );
		skp->Text( 215, 332, "S", 1 );
		skp->Text( 215, 348, "I", 1 );
		skp->Text( 215, 364, "A", 1 );
		skp->Rectangle( 184, 326, 203, 387 );
		skp->Rectangle( 235, 326, 254, 387 );
		skp->Line( 202, 338, 212, 338 );
		skp->Line( 253, 348, 263, 348 );

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
		skp->Text( 56, 45, cbuf, strlen( cbuf ) );
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
		skp->Rectangle( 70, Round( (127 - 0.0114 * usNum) ), 85, 127 );

		// OMS He R
		usNum = He_R;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		skp->Text( 108, 45, cbuf, strlen( cbuf ) );
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
		skp->Rectangle( 122, Round( (127 - 0.0114 * usNum) ), 137, 127 );

		// OMS N2 L
		usNum = N2_L;
		sprintf_s(cbuf, 16, "%04hu", usNum);
		skp->Text( 56, 154, cbuf, strlen(cbuf) );
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
		skp->Rectangle( 122, Round( (236 - 0.019 * usNum) ), 137, 236 );

		// OMS N2 R
		usNum = N2_R;
		sprintf_s(cbuf, 16, "%04hu", usNum);
		skp->Text( 108, 154, cbuf, strlen(cbuf) );
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
		skp->Rectangle( 174, Round( (236 - 0.019 * usNum) ), 189, 236 );

		// He Tank Press Pneu
		usNum = HeTk_Pneu;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		skp->Text( 212, 45, cbuf, strlen( cbuf ) );
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
		skp->Rectangle( 226, Round( 212.5 - (0.0285 * usNum) ), 241, 127 );

		// He Tank Press Eng 2
		usNum = HeTk_L;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		skp->Text( 309, 45, cbuf, strlen( cbuf ) );
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
		skp->Rectangle( 323, Round( 141.25 - (0.01425 * usNum) ), 338, 127 );

		// He Tank Press Eng 1
		usNum = HeTk_C;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		skp->Text( 365, 39, cbuf, strlen( cbuf ) );
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
		skp->Rectangle( 379, Round( 141.25 - (0.01425 * usNum) ), 394, 127 );

		// He Tank Press Eng 3
		usNum = HeTk_R;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		skp->Text( 421, 45, cbuf, strlen( cbuf ) );
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
		skp->Rectangle( 435, Round( 141.25 - (0.01425 * usNum) ), 450, 127 );

		// He Reg Press Pneu
		usNum = HeReg_Pneu;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		skp->Text( 212, 154, cbuf, strlen( cbuf ) );
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
		skp->Rectangle( 226, Round( 350 - (0.19 * usNum) ), 241, 236 );

		// He Reg Press Eng 2
		usNum = HeReg_L;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		skp->Text( 309, 154, cbuf, strlen( cbuf ) );
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
		skp->Rectangle( 323, Round( 350 - (0.19 * usNum) ), 338, 236 );

		// He Reg Press Eng 1
		usNum = HeReg_C;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		skp->Text( 365, 148, cbuf, strlen( cbuf ) );
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
		skp->Rectangle( 379, Round( 350 - (0.19 * usNum) ), 394, 236 );

		// He Reg Press Eng 3
		usNum = HeReg_R;
		sprintf_s( cbuf, 16, "%04hu", usNum );
		skp->Text( 421, 154, cbuf, strlen( cbuf ) );
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
		skp->Rectangle( 435, Round( 350 - (0.19 * usNum) ), 450, 236 );

		// ENG MANF LO2
		usNum = LO2_Manif;
		sprintf_s( cbuf, 16, "%03hu", usNum );
		skp->Text( 178, 300, cbuf, strlen( cbuf ) );
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
		skp->Rectangle( 186, Round( 385 - (0.19 * usNum) ), 201, 385 );

		// ENG MANF LH2
		usNum = LH2_Manif;
		sprintf_s( cbuf, 16, "%03hu", usNum );
		skp->Text( 229, 300, cbuf, strlen( cbuf ) );
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
		skp->Rectangle( 237, Round( 385 - (0.57 * usNum) ), 252, 385 );

		skp->SetFont( skpSSVBFont_h18w9 );

		// L OMS
		usNum = PC_OMS_L;
		sprintf_s( cbuf, 16, "%03hu", usNum );
		skp->Text( 60, 276, cbuf, strlen( cbuf ) );
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
		skp->Rectangle( 66, Round( 401 - (0.775 * usNum) ), 82, 401 );

		// R OMS
		usNum = PC_OMS_R;
		sprintf_s( cbuf, 16, "%03hu", usNum );
		skp->Text( 114, 276, cbuf, strlen( cbuf ) );
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
		skp->Rectangle( 120, Round( 401 - (0.775 * usNum) ), 136, 401 );

		// PC L/2
		usNum = PC_L;
		sprintf_s( cbuf, 16, "%03hu", usNum );
		skp->Text( 314, 276, cbuf, strlen( cbuf ) );
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
		skp->Rectangle( 320, Round( 466.3895 - (1.4531 * usNum) ), 336, 401 );

		// PC C/1
		usNum = PC_C;
		sprintf_s( cbuf, 16, "%03hu", usNum );
		skp->Text( 366, 261, cbuf, strlen( cbuf ) );
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
		skp->Rectangle( 373, Round( 466.3895 - (1.4531 * usNum) ), 389, 401 );

		// PC R/3
		usNum = PC_R;
		sprintf_s( cbuf, 16, "%03hu", usNum );
		skp->Text( 424, 276, cbuf, strlen( cbuf ) );
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
		skp->Rectangle( 430, Round( 466.3895 - (1.4531 * usNum) ), 446, 401 );

		return;
	}

	void MDU::APUHYD( HDC hDC )
	{
		int nPos;
		unsigned short usNum;
		char cbuf[16];

		SelectObject( hDC, gdiSSVBFont_h18w9 );
		SelectObject( hDC, gdiDarkGreenPen );
		SelectObject( hDC, gdiBlackBrush );

		SetTextColor( hDC, CR_DARK_GREEN );
		TextOut( hDC, 239, 6, "APU", 3 );
		MoveToEx( hDC, 38, 15, NULL );
		LineTo( hDC, 235, 15 );
		MoveToEx( hDC, 274, 15, NULL );
		LineTo( hDC, 472, 15 );
		MoveToEx( hDC, 38, 15, NULL );
		LineTo( hDC, 38, 33 );
		MoveToEx( hDC, 472, 15, NULL );
		LineTo( hDC, 472, 33 );

		TextOut( hDC, 216, 261, "HYDRAULIC", 9 );
		MoveToEx( hDC, 20, 268, NULL );
		LineTo( hDC, 208, 268 );
		MoveToEx( hDC, 303, 268, NULL );
		LineTo( hDC, 472, 268 );
		MoveToEx( hDC, 20, 268, NULL );
		LineTo( hDC, 20, 286 );
		MoveToEx( hDC, 472, 268, NULL );
		LineTo( hDC, 472, 286 );

		SetTextColor( hDC, CR_WHITE );
		SelectObject( hDC, gdiSSVAFont_h10w10bold );

		// APU
		TextOut( hDC, 83, 31, "1", 1 );
		TextOut( hDC, 135, 31, "2", 1 );
		TextOut( hDC, 187, 31, "3", 1 );
		TextOut( hDC, 33, 90, "FUEL", 4 );
		TextOut( hDC, 35, 104, "QTY", 3 );
		TextOut( hDC, 46, 118, "%", 1 );
		Rectangle( hDC, 71, 47, 107, 64 );
		Rectangle( hDC, 123, 47, 159, 64 );
		Rectangle( hDC, 175, 47, 211, 64 );

		TextOut( hDC, 35, 181, "H O", 3 );
		TextOut( hDC, 46, 185, "2", 1 );
		TextOut( hDC, 35, 197, "QTY", 3 );
		TextOut( hDC, 46, 211, "%", 1 );
		Rectangle( hDC, 71, 147, 107, 164 );
		Rectangle( hDC, 123, 147, 159, 164 );
		Rectangle( hDC, 175, 147, 211, 164 );

		TextOut( hDC, 318, 31, "1", 1 );
		TextOut( hDC, 372, 31, "2", 1 );
		TextOut( hDC, 426, 31, "3", 1 );
		TextOut( hDC, 264, 90, "FUEL", 4 );
		TextOut( hDC, 279, 104, "P", 1 );
		Rectangle( hDC, 301, 47, 345, 64 );
		Rectangle( hDC, 355, 47, 399, 64 );
		Rectangle( hDC, 409, 47, 453, 64 );

		TextOut( hDC, 257, 181, "OIL", 3 );
		TextOut( hDC, 238, 197, "IN TEMP", 7 );
		sprintf_s( cbuf, 16, "%cF", 176 );
		TextOut( hDC, 255, 211, cbuf, 2 );
		Rectangle( hDC, 301, 147, 345, 164 );
		Rectangle( hDC, 355, 147, 399, 164 );
		Rectangle( hDC, 409, 147, 453, 164 );

		// HYD
		TextOut( hDC, 83, 289, "1", 1 );
		TextOut( hDC, 135, 289, "2", 1 );
		TextOut( hDC, 187, 289, "3", 1 );
		TextOut( hDC, 35, 344, "QTY", 3 );
		TextOut( hDC, 46, 358, "%", 1 );
		Rectangle( hDC, 71, 307, 107, 324 );
		Rectangle( hDC, 123, 307, 159, 324 );
		Rectangle( hDC, 175, 307, 211, 324 );

		TextOut( hDC, 318, 289, "1", 1 );
		TextOut( hDC, 372, 289, "2", 1 );
		TextOut( hDC, 426, 289, "3", 1 );
		TextOut( hDC, 260, 353, "PRESS", 5 );
		Rectangle( hDC, 301, 307, 345, 324 );
		Rectangle( hDC, 355, 307, 399, 324 );
		Rectangle( hDC, 409, 307, 453, 324 );
		TextOut( hDC, 351, 376, "L", 1 );
		TextOut( hDC, 405, 376, "L", 1 );
		TextOut( hDC, 459, 376, "L", 1 );

		SelectObject( hDC, gdiWhitePen );

		//Fuel Qty
		Rectangle( hDC, 79, 76, 98, 133 );
		Rectangle( hDC, 131, 76, 150, 133 );
		Rectangle( hDC, 183, 76, 202, 133 );
		MoveToEx( hDC, 97, 120, NULL );
		LineTo( hDC, 107, 120 );
		MoveToEx( hDC, 149, 120, NULL );
		LineTo( hDC, 159, 120 );
		MoveToEx( hDC, 201, 120, NULL );
		LineTo( hDC, 211, 120 );

		//H2O Qty
		Rectangle( hDC, 79, 175, 98, 232 );
		Rectangle( hDC, 131, 175, 150, 232 );
		Rectangle( hDC, 183, 175, 202, 232 );
		MoveToEx( hDC, 97, 209, NULL );
		LineTo( hDC, 107, 209 );
		MoveToEx( hDC, 149, 209, NULL );
		LineTo( hDC, 159, 209 );
		MoveToEx( hDC, 201, 209, NULL );
		LineTo( hDC, 211, 209 );

		//Fuel P
		Rectangle( hDC, 314, 72, 333, 133 );
		Rectangle( hDC, 368, 72, 387, 133 );
		Rectangle( hDC, 422, 72, 441, 133 );

		//Oil In Temp
		Rectangle( hDC, 314, 171, 333, 232 );
		Rectangle( hDC, 368, 171, 387, 232 );
		Rectangle( hDC, 422, 171, 441, 232 );
		MoveToEx( hDC, 332, 225, NULL );
		LineTo( hDC, 342, 225 );
		MoveToEx( hDC, 386, 225, NULL );
		LineTo( hDC, 396, 225 );
		MoveToEx( hDC, 440, 225, NULL );
		LineTo( hDC, 450, 225 );
		MoveToEx( hDC, 332, 197, NULL );
		LineTo( hDC, 342, 197 );
		MoveToEx( hDC, 386, 197, NULL );
		LineTo( hDC, 396, 197 );
		MoveToEx( hDC, 440, 197, NULL );
		LineTo( hDC, 450, 197 );

		//Hydraulic Qty
		Rectangle( hDC, 79, 335, 98, 392 );
		Rectangle( hDC, 131, 335, 150, 392 );
		Rectangle( hDC, 183, 335, 202, 392 );
		MoveToEx( hDC, 97, 369, NULL );
		LineTo( hDC, 107, 369 );
		MoveToEx( hDC, 149, 369, NULL );
		LineTo( hDC, 159, 369 );
		MoveToEx( hDC, 201, 369, NULL );
		LineTo( hDC, 211, 369 );
		MoveToEx( hDC, 97, 340, NULL );
		LineTo( hDC, 107, 340 );
		MoveToEx( hDC, 149, 340, NULL );
		LineTo( hDC, 159, 340 );
		MoveToEx( hDC, 201, 340, NULL );
		LineTo( hDC, 211, 340 );

		//Hydraulic Press
		Rectangle( hDC, 314, 335, 333, 392 );
		Rectangle( hDC, 368, 335, 387, 392 );
		Rectangle( hDC, 422, 335, 441, 392 );
		MoveToEx( hDC, 332, 383, NULL );
		LineTo( hDC, 342, 383 );
		MoveToEx( hDC, 386, 383, NULL );
		LineTo( hDC, 396, 383 );
		MoveToEx( hDC, 440, 383, NULL );
		LineTo( hDC, 450, 383 );
		MoveToEx( hDC, 332, 377, NULL );
		LineTo( hDC, 342, 377 );
		MoveToEx( hDC, 386, 377, NULL );
		LineTo( hDC, 396, 377 );
		MoveToEx( hDC, 440, 377, NULL );
		LineTo( hDC, 450, 377 );
		MoveToEx( hDC, 332, 358, NULL );
		LineTo( hDC, 342, 358 );
		MoveToEx( hDC, 386, 358, NULL );
		LineTo( hDC, 396, 358 );
		MoveToEx( hDC, 440, 358, NULL );
		LineTo( hDC, 450, 358 );

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
			TextOut( hDC, 73 + 52 * nPos, 50, cbuf, strlen( cbuf ) );
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
			Rectangle( hDC, 81 + 52 * nPos, static_cast<int>(131 - 0.53 * usNum), 96 + 52 * nPos, 131 );

			//H2O Qty
			usNum = H2OQty[nPos];
			sprintf_s( cbuf, 16, "%03hu", usNum );
			TextOut( hDC, 73 + 52 * nPos, 150, cbuf, strlen( cbuf ) );
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
			Rectangle( hDC, 81 + 52 * nPos, static_cast<int>(230 - 0.53 * usNum), 96 + 52 * nPos, 230 );

			//Fuel P
			usNum = Fu_Press[nPos];
			sprintf_s( cbuf, 16, "%04hu", usNum );
			TextOut( hDC, 302 + 54 * nPos, 50, cbuf, strlen( cbuf ) );
			SelectObject( hDC, gdiLightGreenBrush );
			SelectObject( hDC, gdiLightGreenPen );
			if (usNum > 500) usNum = 500;
			Rectangle( hDC, 316 + 54 * nPos, static_cast<int>(131 - 0.114 * usNum), 331 + 54 * nPos, 131 );

			//Oil In Temp
			usNum = OilIn[nPos];
			sprintf_s( cbuf, 16, "%04hu", usNum );
			TextOut( hDC, 302 + 54 * nPos, 150, cbuf, strlen( cbuf ) );
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
			Rectangle( hDC, 316 + 54 * nPos, static_cast<int>(230 - 0.114 * usNum), 331 + 54 * nPos, 230 );

			//Hydraulic Qty
			usNum = Qty[nPos];
			sprintf_s( cbuf, 16, "%03hu", usNum );
			TextOut( hDC, 73 + 52 * nPos, 310, cbuf, strlen( cbuf ) );
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
			Rectangle( hDC, 81 + 52 * nPos, static_cast<int>(390 - 0.53 * usNum), 96 + 52 * nPos, 390 );

			//Hydraulic Press
			usNum = Press[nPos];
			sprintf_s( cbuf, 16, "%04hu", usNum );
			TextOut( hDC, 302 + 54 * nPos, 310, cbuf, strlen( cbuf ) );
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
			Rectangle( hDC, 316 + 54 * nPos, static_cast<int>(390 - 0.01325 * usNum), 331 + 54 * nPos, 390 );
		}
		return;
	}

	void MDU::APUHYD( oapi::Sketchpad2* skp )
	{
		int nPos;
		unsigned short usNum;
		char cbuf[16];

		skp->SetFont( skpSSVBFont_h18w9 );
		skp->SetPen( skpDarkGreenPen );
		skp->SetBrush( skpBlackBrush );

		skp->SetTextColor( CR_DARK_GREEN );
		skp->Text( 239, 6, "APU", 3 );
		skp->Line( 38, 15, 235, 15 );
		skp->Line( 274, 15, 472, 15 );
		skp->Line( 38, 15, 38, 33 );
		skp->Line( 472, 15, 472, 33 );

		skp->Text( 216, 261, "HYDRAULIC", 9 );
		skp->Line( 20, 268, 208, 268 );
		skp->Line( 303, 268, 472, 268 );
		skp->Line( 20, 268, 20, 286 );
		skp->Line( 472, 268, 472, 286 );

		skp->SetTextColor( CR_WHITE );
		skp->SetFont( skpSSVAFont_h10w10bold );

		// APU
		skp->Text( 83, 31, "1", 1 );
		skp->Text( 135, 31, "2", 1 );
		skp->Text( 187, 31, "3", 1 );
		skp->Text( 33, 90, "FUEL", 4 );
		skp->Text( 35, 104, "QTY", 3 );
		skp->Text( 46, 118, "%", 1 );
		skp->Rectangle( 71, 47, 107, 64 );
		skp->Rectangle( 123, 47, 159, 64 );
		skp->Rectangle( 175, 47, 211, 64 );

		skp->Text( 35, 181, "H O", 3 );
		skp->Text( 46, 185, "2", 1 );
		skp->Text( 35, 197, "QTY", 3 );
		skp->Text( 46, 211, "%", 1 );
		skp->Rectangle( 71, 147, 107, 164 );
		skp->Rectangle( 123, 147, 159, 164 );
		skp->Rectangle( 175, 147, 211, 164 );

		skp->Text( 318, 31, "1", 1 );
		skp->Text( 372, 31, "2", 1 );
		skp->Text( 426, 31, "3", 1 );
		skp->Text( 264, 90, "FUEL", 4 );
		skp->Text( 279, 104, "P", 1 );
		skp->Rectangle( 301, 47, 345, 64 );
		skp->Rectangle( 355, 47, 399, 64 );
		skp->Rectangle( 409, 47, 453, 64 );

		skp->Text( 257, 181, "OIL", 3 );
		skp->Text( 238, 197, "IN TEMP", 7 );
		sprintf_s( cbuf, 16, "%cF", 176 );
		skp->Text( 255, 211, cbuf, 2 );
		skp->Rectangle( 301, 147, 345, 164 );
		skp->Rectangle( 355, 147, 399, 164 );
		skp->Rectangle( 409, 147, 453, 164 );

		// HYD
		skp->Text( 83, 289, "1", 1 );
		skp->Text( 135, 289, "2", 1 );
		skp->Text( 187, 289, "3", 1 );
		skp->Text( 35, 344, "QTY", 3 );
		skp->Text( 46, 358, "%", 1 );
		skp->Rectangle( 71, 307, 107, 324 );
		skp->Rectangle( 123, 307, 159, 324 );
		skp->Rectangle( 175, 307, 211, 324 );

		skp->Text( 318, 289, "1", 1 );
		skp->Text( 372, 289, "2", 1 );
		skp->Text( 426, 289, "3", 1 );
		skp->Text( 260, 353, "PRESS", 5 );
		skp->Rectangle( 301, 307, 345, 324 );
		skp->Rectangle( 355, 307, 399, 324 );
		skp->Rectangle( 409, 307, 453, 324 );
		skp->Text( 351, 376, "L", 1 );
		skp->Text( 405, 376, "L", 1 );
		skp->Text( 459, 376, "L", 1 );

		skp->SetPen( skpWhitePen );

		//Fuel Qty
		skp->Rectangle( 79, 76, 98, 133 );
		skp->Rectangle( 131, 76, 150, 133 );
		skp->Rectangle( 183, 76, 202, 133 );
		skp->Line( 97, 120, 107, 120 );
		skp->Line( 149, 120, 159, 120 );
		skp->Line( 201, 120, 211, 120 );

		//H2O Qty
		skp->Rectangle( 79, 175, 98, 232 );
		skp->Rectangle( 131, 175, 150, 232 );
		skp->Rectangle( 183, 175, 202, 232 );
		skp->Line( 97, 209, 107, 209 );
		skp->Line( 149, 209, 159, 209 );
		skp->Line( 201, 209, 211, 209 );

		//Fuel P
		skp->Rectangle( 314, 72, 333, 133 );
		skp->Rectangle( 368, 72, 387, 133 );
		skp->Rectangle( 422, 72, 441, 133 );

		//Oil In Temp
		skp->Rectangle( 314, 171, 333, 232 );
		skp->Rectangle( 368, 171, 387, 232 );
		skp->Rectangle( 422, 171, 441, 232 );
		skp->Line( 332, 225, 342, 225 );
		skp->Line( 386, 225, 396, 225 );
		skp->Line( 440, 225, 450, 225 );
		skp->Line( 332, 197, 342, 197 );
		skp->Line( 386, 197, 396, 197 );
		skp->Line( 440, 197, 450, 197 );

		//Hydraulic Qty
		skp->Rectangle( 79, 335, 98, 392 );
		skp->Rectangle( 131, 335, 150, 392 );
		skp->Rectangle( 183, 335, 202, 392 );
		skp->Line( 97, 369, 107, 369 );
		skp->Line( 149, 369, 159, 369 );
		skp->Line( 201, 369, 211, 369 );
		skp->Line( 97, 340, 107, 340 );
		skp->Line( 149, 340, 159, 340 );
		skp->Line( 201, 340, 211, 340 );

		//Hydraulic Press
		skp->Rectangle( 314, 335, 333, 392 );
		skp->Rectangle( 368, 335, 387, 392 );
		skp->Rectangle( 422, 335, 441, 392 );
		skp->Line( 332, 383, 342, 383 );
		skp->Line( 386, 383, 396, 383 );
		skp->Line( 440, 383, 450, 383 );
		skp->Line( 332, 377, 342, 377 );
		skp->Line( 386, 377, 396, 377 );
		skp->Line( 440, 377, 450, 377 );
		skp->Line( 332, 358, 342, 358 );
		skp->Line( 386, 358, 396, 358 );
		skp->Line( 440, 358, 450, 358 );

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
			skp->Text( 73 + 52 * nPos, 50, cbuf, strlen( cbuf ) );
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
			skp->Rectangle( 81 + 52 * nPos, static_cast<int>(131 - 0.53 * usNum), 96 + 52 * nPos, 131 );

			//H2O Qty
			usNum = H2OQty[nPos];
			sprintf_s( cbuf, 16, "%03hu", usNum );
			skp->Text( 73 + 52 * nPos, 150, cbuf, strlen( cbuf ) );
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
			skp->Rectangle( 81 + 52 * nPos, static_cast<int>(230 - 0.53 * usNum), 96 + 52 * nPos, 230 );

			//Fuel P
			usNum = Fu_Press[nPos];
			sprintf_s( cbuf, 16, "%04hu", usNum );
			skp->Text( 302 + 54 * nPos, 50, cbuf, strlen( cbuf ) );
			skp->SetBrush( skpLightGreenBrush );
			skp->SetPen( skpLightGreenPen );
			if (usNum > 500) usNum = 500;
			skp->Rectangle( 316 + 54 * nPos, static_cast<int>(131 - 0.114 * usNum), 331 + 54 * nPos, 131 );

			//Oil In Temp
			usNum = OilIn[nPos];
			sprintf_s( cbuf, 16, "%04hu", usNum );
			skp->Text( 302 + 54 * nPos, 150, cbuf, strlen( cbuf ) );
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
			skp->Rectangle( 316 + 54 * nPos, static_cast<int>(230 - 0.114 * usNum), 331 + 54 * nPos, 230 );

			//Hydraulic Qty
			usNum = Qty[nPos];
			sprintf_s( cbuf, 16, "%03hu", usNum );
			skp->Text( 73 + 52 * nPos, 310, cbuf, strlen( cbuf ) );
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
			skp->Rectangle( 81 + 52 * nPos, static_cast<int>(390 - 0.53 * usNum), 96 + 52 * nPos, 390 );

			//Hydraulic Press
			usNum = Press[nPos];
			sprintf_s( cbuf, 16, "%04hu", usNum );
			skp->Text( 302 + 54 * nPos, 310, cbuf, strlen( cbuf ) );
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
			skp->Rectangle( 316 + 54 * nPos, static_cast<int>(390 - 0.01325 * usNum), 331 + 54 * nPos, 390 );
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

		SelectObject( hDC, gdiSSVAFont_h10w10bold );
		SelectObject( hDC, gdiDarkGreenPen );
		SetTextColor( hDC, CR_DARK_GREEN );

		MoveToEx( hDC, 3, 75, NULL );
		LineTo( hDC, 3, 54 );
		MoveToEx( hDC, 3, 55, NULL );
		LineTo( hDC, 77, 55 );
		MoveToEx( hDC, 153, 55, NULL );
		LineTo( hDC, 227, 55 );
		MoveToEx( hDC, 227, 55, NULL );
		LineTo( hDC, 227, 75 );

		MoveToEx( hDC, 3, 336, NULL );
		LineTo( hDC, 3, 356 );
		MoveToEx( hDC, 3, 356, NULL );
		LineTo( hDC, 77, 356 );
		MoveToEx( hDC, 153, 356, NULL );
		LineTo( hDC, 227, 356 );
		MoveToEx( hDC, 227, 356, NULL );
		LineTo( hDC, 227, 336 );

		TextOut( hDC, 88, 49, "TE UP", 5 );
		TextOut( hDC, 88, 350, "TE DN", 5 );

		TextOut( hDC, 259, 108, "L RUD", 5 );
		TextOut( hDC, 458, 108, "R RUD", 5 );

		TextOut( hDC, 259, 208, "L AIL", 5 );
		TextOut( hDC, 458, 208, "R AIL", 5 );

		// gray boxes
		SelectObject( hDC, gdiDarkGrayBrush );
		SelectObject( hDC, gdiDarkGrayPen );

		Rectangle( hDC, 36, 91, 47, 323 );
		Rectangle( hDC, 115, 91, 127, 323 );

		Rectangle( hDC, 181, 91, 194, 323 );

		Rectangle( hDC, 264, 83, 504, 97 );

		Rectangle( hDC, 264, 183, 504, 196 );

		Rectangle( hDC, 264, 310, 504, 323 );

		SetTextColor( hDC, CR_WHITE );
		TextOut( hDC, 25, 27, "ELEVONS", 7 );
		TextOut( hDC, 45, 40, "DEG", 3 );
		TextOut( hDC, 63, 107, "-30", 3 );
		TextOut( hDC, 63, 147, "-20", 3 );
		TextOut( hDC, 63, 188, "-10", 3 );
		TextOut( hDC, 63, 267, "+10", 3 );
		TextOut( hDC, 63, 307, "+20", 3 );

		TextOut( hDC, 136, 27, "BODY FLAP", 9 );
		TextOut( hDC, 178, 40, "%", 1 );
		TextOut( hDC, 219, 92, "0", 1 );
		TextOut( hDC, 219, 136, "20", 2 );
		TextOut( hDC, 219, 180, "40", 2 );
		TextOut( hDC, 219, 224, "60", 2 );
		TextOut( hDC, 219, 268, "80", 2 );
		TextOut( hDC, 219, 312, "100", 3 );

		TextOut( hDC, 325, 31, "RUDDER-DEG", 10 );
		TextOut( hDC, 256, 53, "30", 2 );
		TextOut( hDC, 294, 53, "20", 2 );
		TextOut( hDC, 332, 53, "10", 2 );
		TextOut( hDC, 408, 53, "10", 2 );
		TextOut( hDC, 446, 53, "20", 2 );
		TextOut( hDC, 484, 53, "30", 2 );

		TextOut( hDC, 325, 139, "AILERON-DEG", 11 );
		TextOut( hDC, 264, 153, "5", 1 );
		TextOut( hDC, 491, 153, "5", 1 );

		TextOut( hDC, 311, 240, "SPEEDBRAKE  %", 13 );
		TextOut( hDC, 264, 280, "0", 1 );
		TextOut( hDC, 302, 280, "20", 2 );
		TextOut( hDC, 348, 280, "40", 2 );
		TextOut( hDC, 393, 280, "60", 2 );
		TextOut( hDC, 439, 280, "80", 2 );
		TextOut( hDC, 481, 280, "100", 3 );

		SetTextColor( hDC, CR_YELLOW );
		TextOut( hDC, 74, 231, "0", 1 );
		TextOut( hDC, 377, 53, "0", 1 );
		TextOut( hDC, 378, 153, "0", 1 );

		TextOut( hDC, 351, 258, "ACTUAL", 6 );

		SetTextColor( hDC, CR_CYAN );
		TextOut( hDC, 351, 361, "COMMAND", 7 );

		// white lines
		if (active) SelectObject( hDC, gdiWhitePen );
		else SelectObject( hDC, gdiRedPen );

		// elevons
		MoveToEx( hDC, 32, 97, NULL );
		LineTo( hDC, 32, 317 );
		MoveToEx( hDC, 31, 97, NULL );
		LineTo( hDC, 22, 97 );
		MoveToEx( hDC, 31, 117, NULL );
		LineTo( hDC, 18, 117 );
		MoveToEx( hDC, 31, 137, NULL );
		LineTo( hDC, 22, 137 );
		MoveToEx( hDC, 31, 157, NULL );
		LineTo( hDC, 18, 157 );
		MoveToEx( hDC, 31, 177, NULL );
		LineTo( hDC, 22, 177 );
		MoveToEx( hDC, 31, 197, NULL );
		LineTo( hDC, 18, 197 );
		MoveToEx( hDC, 31, 217, NULL );
		LineTo( hDC, 22, 217 );
		// (yellow line)
		MoveToEx( hDC, 31, 257, NULL );
		LineTo( hDC, 22, 257 );
		MoveToEx( hDC, 31, 277, NULL );
		LineTo( hDC, 18, 277 );
		MoveToEx( hDC, 31, 297, NULL );
		LineTo( hDC, 22, 297 );
		MoveToEx( hDC, 31, 317, NULL );
		LineTo( hDC, 18, 317 );

		MoveToEx( hDC, 51, 97, NULL );
		LineTo( hDC, 51, 317 );
		MoveToEx( hDC, 51, 97, NULL );
		LineTo( hDC, 60, 97 );
		MoveToEx( hDC, 51, 117, NULL );
		LineTo( hDC, 64, 117 );
		MoveToEx( hDC, 51, 137, NULL );
		LineTo( hDC, 60, 137 );
		MoveToEx( hDC, 51, 157, NULL );
		LineTo( hDC, 64, 157 );
		MoveToEx( hDC, 51, 177, NULL );
		LineTo( hDC, 60, 177 );
		MoveToEx( hDC, 51, 197, NULL );
		LineTo( hDC, 64, 197 );
		MoveToEx( hDC, 51, 217, NULL );
		LineTo( hDC, 60, 217 );
		// (yellow line)
		MoveToEx( hDC, 51, 257, NULL );
		LineTo( hDC, 60, 257 );
		MoveToEx( hDC, 51, 277, NULL );
		LineTo( hDC, 64, 277 );
		MoveToEx( hDC, 51, 297, NULL );
		LineTo( hDC, 60, 297 );
		MoveToEx( hDC, 51, 317, NULL );
		LineTo( hDC, 64, 317 );

		MoveToEx( hDC, 111, 97, NULL );
		LineTo( hDC, 111, 317 );
		MoveToEx( hDC, 110, 97, NULL );
		LineTo( hDC, 101, 97 );
		MoveToEx( hDC, 110, 117, NULL );
		LineTo( hDC, 97, 117 );
		MoveToEx( hDC, 110, 137, NULL );
		LineTo( hDC, 101, 137 );
		MoveToEx( hDC, 110, 157, NULL );
		LineTo( hDC, 97, 157 );
		MoveToEx( hDC, 110, 177, NULL );
		LineTo( hDC, 101, 177 );
		MoveToEx( hDC, 110, 197, NULL );
		LineTo( hDC, 97, 197 );
		MoveToEx( hDC, 110, 217, NULL );
		LineTo( hDC, 101, 217 );
		// (yellow line)
		MoveToEx( hDC, 110, 257, NULL );
		LineTo( hDC, 101, 257 );
		MoveToEx( hDC, 110, 277, NULL );
		LineTo( hDC, 97, 277 );
		MoveToEx( hDC, 110, 297, NULL );
		LineTo( hDC, 101, 297 );
		MoveToEx( hDC, 110, 317, NULL );
		LineTo( hDC, 97, 317 );

		MoveToEx( hDC, 130, 97, NULL );
		LineTo( hDC, 130, 317 );
		MoveToEx( hDC, 130, 97, NULL );
		LineTo( hDC, 139, 97 );
		MoveToEx( hDC, 130, 117, NULL );
		LineTo( hDC, 143, 117 );
		MoveToEx( hDC, 130, 137, NULL );
		LineTo( hDC, 139, 137 );
		MoveToEx( hDC, 130, 157, NULL );
		LineTo( hDC, 143, 157 );
		MoveToEx( hDC, 130, 177, NULL );
		LineTo( hDC, 139, 177 );
		MoveToEx( hDC, 130, 197, NULL );
		LineTo( hDC, 143, 197 );
		MoveToEx( hDC, 130, 217, NULL );
		LineTo( hDC, 139, 217 );
		// (yellow line)
		MoveToEx( hDC, 130, 257, NULL );
		LineTo( hDC, 139, 257 );
		MoveToEx( hDC, 130, 277, NULL );
		LineTo( hDC, 143, 277 );
		MoveToEx( hDC, 130, 297, NULL );
		LineTo( hDC, 139, 297 );
		MoveToEx( hDC, 130, 317, NULL );
		LineTo( hDC, 143, 317 );

		// body flap
		MoveToEx( hDC, 197, 97, NULL );
		LineTo( hDC, 197, 317 );
		MoveToEx( hDC, 197, 97, NULL );
		LineTo( hDC, 210, 97 );
		MoveToEx( hDC, 197, 119, NULL );
		LineTo( hDC, 206, 119 );
		MoveToEx( hDC, 197, 141, NULL );
		LineTo( hDC, 210, 141 );
		MoveToEx( hDC, 197, 163, NULL );
		LineTo( hDC, 206, 163 );
		MoveToEx( hDC, 197, 185, NULL );
		LineTo( hDC, 210, 185 );
		MoveToEx( hDC, 197, 207, NULL );
		LineTo( hDC, 206, 207 );
		MoveToEx( hDC, 197, 229, NULL );
		LineTo( hDC, 210, 229 );
		MoveToEx( hDC, 197, 251, NULL );
		LineTo( hDC, 206, 251 );
		MoveToEx( hDC, 197, 273, NULL );
		LineTo( hDC, 210, 273 );
		MoveToEx( hDC, 197, 295, NULL );
		LineTo( hDC, 206, 295 );
		MoveToEx( hDC, 197, 317, NULL );
		LineTo( hDC, 210, 317 );

		// rudder
		MoveToEx( hDC, 270, 79, NULL );
		LineTo( hDC, 498, 79 );
		MoveToEx( hDC, 270, 78, NULL );
		LineTo( hDC, 270, 65 );
		MoveToEx( hDC, 289, 78, NULL );
		LineTo( hDC, 289, 69 );
		MoveToEx( hDC, 308, 78, NULL );
		LineTo( hDC, 308, 65 );
		MoveToEx( hDC, 327, 78, NULL );
		LineTo( hDC, 327, 69 );
		MoveToEx( hDC, 346, 78, NULL );
		LineTo( hDC, 346, 65 );
		MoveToEx( hDC, 365, 78, NULL );
		LineTo( hDC, 365, 69 );
		// (yellow line)
		MoveToEx( hDC, 403, 78, NULL );
		LineTo( hDC, 403, 69 );
		MoveToEx( hDC, 422, 78, NULL );
		LineTo( hDC, 422, 65 );
		MoveToEx( hDC, 441, 78, NULL );
		LineTo( hDC, 441, 69 );
		MoveToEx( hDC, 460, 78, NULL );
		LineTo( hDC, 460, 65 );
		MoveToEx( hDC, 479, 78, NULL );
		LineTo( hDC, 479, 69 );
		MoveToEx( hDC, 498, 79, NULL );
		LineTo( hDC, 498, 65 );

		// aileron
		MoveToEx( hDC, 270, 179, NULL );
		LineTo( hDC, 498, 179 );
		MoveToEx( hDC, 270, 178, NULL );
		LineTo( hDC, 270, 165 );
		MoveToEx( hDC, 281, 178, NULL );
		LineTo( hDC, 281, 169 );
		MoveToEx( hDC, 293, 178, NULL );
		LineTo( hDC, 293, 165 );
		MoveToEx( hDC, 304, 178, NULL );
		LineTo( hDC, 304, 169 );
		MoveToEx( hDC, 316, 178, NULL );
		LineTo( hDC, 316, 165 );
		MoveToEx( hDC, 327, 178, NULL );
		LineTo( hDC, 327, 169 );
		MoveToEx( hDC, 338, 178, NULL );
		LineTo( hDC, 338, 165 );
		MoveToEx( hDC, 350, 178, NULL );
		LineTo( hDC, 350, 169 );
		MoveToEx( hDC, 361, 178, NULL );
		LineTo( hDC, 361, 165 );
		MoveToEx( hDC, 373, 178, NULL );
		LineTo( hDC, 373, 169 );
		// (yellow line)
		MoveToEx( hDC, 395, 178, NULL );
		LineTo( hDC, 395, 169 );
		MoveToEx( hDC, 407, 178, NULL );
		LineTo( hDC, 407, 165 );
		MoveToEx( hDC, 418, 178, NULL );
		LineTo( hDC, 418, 169 );
		MoveToEx( hDC, 430, 178, NULL );
		LineTo( hDC, 430, 165 );
		MoveToEx( hDC, 441, 178, NULL );
		LineTo( hDC, 441, 169 );
		MoveToEx( hDC, 452, 178, NULL );
		LineTo( hDC, 452, 165 );
		MoveToEx( hDC, 464, 178, NULL );
		LineTo( hDC, 464, 169 );
		MoveToEx( hDC, 475, 178, NULL );
		LineTo( hDC, 475, 165 );
		MoveToEx( hDC, 487, 178, NULL );
		LineTo( hDC, 487, 169 );
		MoveToEx( hDC, 498, 178, NULL );
		LineTo( hDC, 498, 165 );

		// speedbrake
		MoveToEx( hDC, 270, 306, NULL );
		LineTo( hDC, 498, 306 );
		MoveToEx( hDC, 270, 305, NULL );
		LineTo( hDC, 270, 292 );
		MoveToEx( hDC, 293, 305, NULL );
		LineTo( hDC, 293, 296 );
		MoveToEx( hDC, 316, 305, NULL );
		LineTo( hDC, 316, 292 );
		MoveToEx( hDC, 338, 305, NULL );
		LineTo( hDC, 338, 296 );
		MoveToEx( hDC, 361, 305, NULL );
		LineTo( hDC, 361, 292 );
		MoveToEx( hDC, 384, 305, NULL );
		LineTo( hDC, 384, 296 );
		MoveToEx( hDC, 407, 305, NULL );
		LineTo( hDC, 407, 292 );
		MoveToEx( hDC, 430, 305, NULL );
		LineTo( hDC, 430, 296 );
		MoveToEx( hDC, 452, 305, NULL );
		LineTo( hDC, 452, 292 );
		MoveToEx( hDC, 475, 305, NULL );
		LineTo( hDC, 475, 296 );
		MoveToEx( hDC, 498, 305, NULL );
		LineTo( hDC, 498, 292 );

		MoveToEx( hDC, 270, 326, NULL );
		LineTo( hDC, 498, 326 );
		MoveToEx( hDC, 270, 326, NULL );
		LineTo( hDC, 270, 339 );
		MoveToEx( hDC, 293, 326, NULL );
		LineTo( hDC, 293, 335 );
		MoveToEx( hDC, 316, 326, NULL );
		LineTo( hDC, 316, 339 );
		MoveToEx( hDC, 338, 326, NULL );
		LineTo( hDC, 338, 335 );
		MoveToEx( hDC, 361, 326, NULL );
		LineTo( hDC, 361, 339 );
		MoveToEx( hDC, 384, 326, NULL );
		LineTo( hDC, 384, 335 );
		MoveToEx( hDC, 407, 326, NULL );
		LineTo( hDC, 407, 339 );
		MoveToEx( hDC, 430, 326, NULL );
		LineTo( hDC, 430, 335 );
		MoveToEx( hDC, 452, 326, NULL );
		LineTo( hDC, 452, 339 );
		MoveToEx( hDC, 475, 326, NULL );
		LineTo( hDC, 475, 335 );
		MoveToEx( hDC, 498, 326, NULL );
		LineTo( hDC, 498, 339 );

		// white boxes
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 455, 255, 494, 272 );
		Rectangle( hDC, 455, 358, 494, 375 );

		// yellow lines
		if (active) SelectObject( hDC, gdiYellowPen );
		else SelectObject( hDC, gdiRedPen );

		MoveToEx( hDC, 31, 237, NULL );
		LineTo( hDC, 18, 237 );
		MoveToEx( hDC, 51, 237, NULL );
		LineTo( hDC, 64, 237 );

		MoveToEx( hDC, 110, 237, NULL );
		LineTo( hDC, 97, 237 );
		MoveToEx( hDC, 130, 237, NULL );
		LineTo( hDC, 143, 237 );

		MoveToEx( hDC, 384, 78, NULL );
		LineTo( hDC, 384, 65 );

		MoveToEx( hDC, 384, 178, NULL );
		LineTo( hDC, 384, 165 );

		// body flap trail mark
		SelectObject( hDC, gdiYellowPen );
		SelectObject( hDC, gdiYellowBrush );
		tri[0].x = 207;
		tri[0].y = 172;
		tri[1].x = 217;
		tri[1].y = 167;
		tri[2].x = 217;
		tri[2].y = 177;
		Polygon( hDC, tri, 3 );
		Rectangle( hDC, 216, 168, 226, 178 );

		if (!active) return;

		// elevons
		nPos = Round( 237 + (4 * range( -35.0, LOB, 20.0 )) );
		tri[0].x = 22;
		tri[0].y = nPos;
		tri[1].x = 38;
		tri[1].y = nPos - 8;
		tri[2].x = 38;
		tri[2].y = nPos + 8;
		Polygon( hDC, tri, 3 );

		nPos = Round( 237 + (4 * range( -35.0, LIB, 20.0 )) );
		tri[0].x = 60;
		tri[0].y = nPos;
		tri[1].x = 44;
		tri[1].y = nPos - 8;
		tri[2].x = 44;
		tri[2].y = nPos + 8;
		Polygon( hDC, tri, 3 );

		nPos = Round( 237 + (4 * range( -35.0, RIB, 20.0 )) );
		tri[0].x = 101;
		tri[0].y = nPos;
		tri[1].x = 117;
		tri[1].y = nPos - 8;
		tri[2].x = 117;
		tri[2].y = nPos + 8;
		Polygon( hDC, tri, 3 );

		nPos = Round( 237 + (4 * range( -35.0, ROB, 20.0 )) );
		tri[0].x = 139;
		tri[0].y = nPos;
		tri[1].x = 123;
		tri[1].y = nPos - 8;
		tri[2].x = 123;
		tri[2].y = nPos + 8;
		Polygon( hDC, tri, 3 );

		// body flap
		nPos = Round( 97 + (2.2 * range( 0.0, DBFOFB, 100.0 )) );
		tri[0].x = 206;
		tri[0].y = nPos;
		tri[1].x = 190;
		tri[1].y = nPos - 8;
		tri[2].x = 190;
		tri[2].y = nPos + 8;
		Polygon( hDC, tri, 3 );

		// rudder
		nPos = Round( 384 + (3.8 * range( -30.0, DRFB, 30.0 )) );
		tri[0].x = nPos;
		tri[0].y = 70;
		tri[1].x = nPos - 8;
		tri[1].y = 86;
		tri[2].x = nPos + 8;
		tri[2].y = 86;
		Polygon( hDC, tri, 3 );

		// aileron
		nPos = Round( 384 + (22.8 * range( -5.0, DAFB, 5.0 )) );
		tri[0].x = nPos;
		tri[0].y = 170;
		tri[1].x = nPos - 8;
		tri[1].y = 186;
		tri[2].x = nPos + 8;
		tri[2].y = 186;
		Polygon( hDC, tri, 3 );

		// speedbrake
		SetTextColor( hDC, CR_YELLOW );
		dNum = range( 0.0, Speedbrake_Pos, 100.0 );
		sprintf_s( cbuf, 8, "%03.0f", dNum );
		TextOut( hDC, 459, 258, cbuf, strlen( cbuf ) );
		nPos = Round( 270 + (2.28 * dNum) );
		tri[0].x = nPos;
		tri[0].y = 297;
		tri[1].x = nPos + 8;
		tri[1].y = 313;
		tri[2].x = nPos - 8;
		tri[2].y = 313;
		Polygon( hDC, tri, 3 );

		SelectObject( hDC, gdiCyanPen );
		SelectObject( hDC, gdiCyanBrush );
		SetTextColor( hDC, CR_CYAN );
		dNum = range( 0.0, Speedbrake_Cmd, 100.0 );
		sprintf_s( cbuf, 8, "%03.0f", dNum );
		TextOut( hDC, 459, 361, cbuf, strlen( cbuf ) );
		nPos = Round( 270 + (2.28 * dNum) );
		tri[0].x = nPos;
		tri[0].y = 335;
		tri[1].x = nPos + 8;
		tri[1].y = 319;
		tri[2].x = nPos - 8;
		tri[2].y = 319;
		Polygon( hDC, tri, 3 );
		return;
	}

	void MDU::SPI( oapi::Sketchpad2* skp )
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

		skp->SetFont( skpSSVAFont_h10w10bold );
		skp->SetPen( skpDarkGreenPen );
		skp->SetTextColor( CR_DARK_GREEN );

		skp->Line( 3, 75, 3, 54 );
		skp->Line( 3, 55, 77, 55 );
		skp->Line( 153, 55, 227, 55 );
		skp->Line( 227, 55, 227, 75 );

		skp->Line( 3, 336, 3, 356 );
		skp->Line( 3, 356, 77, 356 );
		skp->Line( 153, 356, 227, 356 );
		skp->Line( 227, 356, 227, 336 );

		skp->Text( 88, 49, "TE UP", 5 );
		skp->Text( 88, 350, "TE DN", 5 );

		skp->Text( 259, 108, "L RUD", 5 );
		skp->Text( 458, 108, "R RUD", 5 );

		skp->Text( 259, 208, "L AIL", 5 );
		skp->Text( 458, 208, "R AIL", 5 );

		// gray boxes
		skp->SetBrush( skpDarkGrayBrush );
		skp->SetPen( skpDarkGrayPen );

		skp->Rectangle( 36, 91, 47, 323 );
		skp->Rectangle( 115, 91, 127, 323 );

		skp->Rectangle( 181, 91, 194, 323 );

		skp->Rectangle( 264, 83, 504, 97 );

		skp->Rectangle( 264, 183, 504, 196 );

		skp->Rectangle( 264, 310, 504, 323 );

		skp->SetTextColor( CR_WHITE );
		skp->Text( 25, 27, "ELEVONS", 7 );
		skp->Text( 45, 40, "DEG", 3 );
		skp->Text( 63, 107, "-30", 3 );
		skp->Text( 63, 147, "-20", 3 );
		skp->Text( 63, 188, "-10", 3 );
		skp->Text( 63, 267, "+10", 3 );
		skp->Text( 63, 307, "+20", 3 );

		skp->Text( 136, 27, "BODY FLAP", 9 );
		skp->Text( 178, 40, "%", 1 );
		skp->Text( 219, 92, "0", 1 );
		skp->Text( 219, 136, "20", 2 );
		skp->Text( 219, 180, "40", 2 );
		skp->Text( 219, 224, "60", 2 );
		skp->Text( 219, 268, "80", 2 );
		skp->Text( 219, 312, "100", 3 );

		skp->Text( 325, 31, "RUDDER-DEG", 10 );
		skp->Text( 256, 53, "30", 2 );
		skp->Text( 294, 53, "20", 2 );
		skp->Text( 332, 53, "10", 2 );
		skp->Text( 408, 53, "10", 2 );
		skp->Text( 446, 53, "20", 2 );
		skp->Text( 484, 53, "30", 2 );

		skp->Text( 325, 139, "AILERON-DEG", 11 );
		skp->Text( 264, 153, "5", 1 );
		skp->Text( 491, 153, "5", 1 );

		skp->Text( 311, 240, "SPEEDBRAKE  %", 13 );
		skp->Text( 264, 280, "0", 1 );
		skp->Text( 302, 280, "20", 2 );
		skp->Text( 348, 280, "40", 2 );
		skp->Text( 393, 280, "60", 2 );
		skp->Text( 439, 280, "80", 2 );
		skp->Text( 481, 280, "100", 3 );

		skp->SetTextColor( CR_YELLOW );
		skp->Text( 74, 231, "0", 1 );
		skp->Text( 377, 53, "0", 1 );
		skp->Text( 378, 153, "0", 1 );

		skp->Text( 351, 258, "ACTUAL", 6 );

		skp->SetTextColor( CR_CYAN );
		skp->Text( 351, 361, "COMMAND", 7 );

		// white lines
		if (active) skp->SetPen( skpWhitePen );
		else skp->SetPen( skpRedPen );

		// elevons
		skp->Line( 32, 97, 32, 317 );
		skp->Line( 31, 97, 22, 97 );
		skp->Line( 31, 117, 18, 117 );
		skp->Line( 31, 137, 22, 137 );
		skp->Line( 31, 157, 18, 157 );
		skp->Line( 31, 177, 22, 177 );
		skp->Line( 31, 197, 18, 197 );
		skp->Line( 31, 217, 22, 217 );
		// (yellow line)
		skp->Line( 31, 257, 22, 257 );
		skp->Line( 31, 277, 18, 277 );
		skp->Line( 31, 297, 22, 297 );
		skp->Line( 31, 317, 18, 317 );

		skp->Line( 51, 97, 51, 317 );
		skp->Line( 51, 97, 60, 97 );
		skp->Line( 51, 117, 64, 117 );
		skp->Line( 51, 137, 60, 137 );
		skp->Line( 51, 157, 64, 157 );
		skp->Line( 51, 177, 60, 177 );
		skp->Line( 51, 197, 64, 197 );
		skp->Line( 51, 217, 60, 217 );
		// (yellow line)
		skp->Line( 51, 257, 60, 257 );
		skp->Line( 51, 277, 64, 277 );
		skp->Line( 51, 297, 60, 297 );
		skp->Line( 51, 317, 64, 317 );

		skp->Line( 111, 97, 111, 317 );
		skp->Line( 110, 97, 101, 97 );
		skp->Line( 110, 117, 97, 117 );
		skp->Line( 110, 137, 101, 137 );
		skp->Line( 110, 157, 97, 157 );
		skp->Line( 110, 177, 101, 177 );
		skp->Line( 110, 197, 97, 197 );
		skp->Line( 110, 217, 101, 217 );
		// (yellow line)
		skp->Line( 110, 257, 101, 257 );
		skp->Line( 110, 277, 97, 277 );
		skp->Line( 110, 297, 101, 297 );
		skp->Line( 110, 317, 97, 317 );

		skp->Line( 130, 97, 130, 317 );
		skp->Line( 130, 97, 139, 97 );
		skp->Line( 130, 117, 143, 117 );
		skp->Line( 130, 137, 139, 137 );
		skp->Line( 130, 157, 143, 157 );
		skp->Line( 130, 177, 139, 177 );
		skp->Line( 130, 197, 143, 197 );
		skp->Line( 130, 217, 139, 217 );
		// (yellow line)
		skp->Line( 130, 257, 139, 257 );
		skp->Line( 130, 277, 143, 277 );
		skp->Line( 130, 297, 139, 297 );
		skp->Line( 130, 317, 143, 317 );

		// body flap
		skp->Line( 197, 97, 197, 317 );
		skp->Line( 197, 97, 210, 97 );
		skp->Line( 197, 119, 206, 119 );
		skp->Line( 197, 141, 210, 141 );
		skp->Line( 197, 163, 206, 163 );
		skp->Line( 197, 185, 210, 185 );
		skp->Line( 197, 207, 206, 207 );
		skp->Line( 197, 229, 210, 229 );
		skp->Line( 197, 251, 206, 251 );
		skp->Line( 197, 273, 210, 273 );
		skp->Line( 197, 295, 206, 295 );
		skp->Line( 197, 317, 210, 317 );

		// rudder
		skp->Line( 270, 79, 498, 79 );
		skp->Line( 270, 78, 270, 65 );
		skp->Line( 289, 78, 289, 69 );
		skp->Line( 308, 78, 308, 65 );
		skp->Line( 327, 78, 327, 69 );
		skp->Line( 346, 78, 346, 65 );
		skp->Line( 365, 78, 365, 69 );
		// (yellow line)
		skp->Line( 403, 78, 403, 69 );
		skp->Line( 422, 78, 422, 65 );
		skp->Line( 441, 78, 441, 69 );
		skp->Line( 460, 78, 460, 65 );
		skp->Line( 479, 78, 479, 69 );
		skp->Line( 498, 78, 498, 65 );

		// aileron
		skp->Line( 270, 179, 498, 179 );
		skp->Line( 270, 178, 270, 165 );
		skp->Line( 281, 178, 281, 169 );
		skp->Line( 293, 178, 293, 165 );
		skp->Line( 304, 178, 304, 169 );
		skp->Line( 316, 178, 316, 165 );
		skp->Line( 327, 178, 327, 169 );
		skp->Line( 338, 178, 338, 165 );
		skp->Line( 350, 178, 350, 169 );
		skp->Line( 361, 178, 361, 165 );
		skp->Line( 373, 178, 373, 169 );
		// (yellow line)
		skp->Line( 395, 178, 395, 169 );
		skp->Line( 407, 178, 407, 165 );
		skp->Line( 418, 178, 418, 169 );
		skp->Line( 430, 178, 430, 165 );
		skp->Line( 441, 178, 441, 169 );
		skp->Line( 452, 178, 452, 165 );
		skp->Line( 464, 178, 464, 169 );
		skp->Line( 475, 178, 475, 165 );
		skp->Line( 487, 178, 487, 169 );
		skp->Line( 498, 178, 498, 165 );

		// speedbrake
		skp->Line( 270, 306, 498, 306 );
		skp->Line( 270, 305, 270, 292 );
		skp->Line( 293, 305, 293, 296 );
		skp->Line( 316, 305, 316, 292 );
		skp->Line( 338, 305, 338, 296 );
		skp->Line( 361, 305, 361, 292 );
		skp->Line( 384, 305, 384, 296 );
		skp->Line( 407, 305, 407, 292 );
		skp->Line( 430, 305, 430, 296 );
		skp->Line( 452, 305, 452, 292 );
		skp->Line( 475, 305, 475, 296 );
		skp->Line( 498, 305, 498, 292 );

		skp->Line( 270, 326, 498, 326 );
		skp->Line( 270, 326, 270, 339 );
		skp->Line( 293, 326, 293, 335 );
		skp->Line( 316, 326, 316, 339 );
		skp->Line( 338, 326, 338, 335 );
		skp->Line( 361, 326, 361, 339 );
		skp->Line( 384, 326, 384, 335 );
		skp->Line( 407, 326, 407, 339 );
		skp->Line( 430, 326, 430, 335 );
		skp->Line( 452, 326, 452, 339 );
		skp->Line( 475, 326, 475, 335 );
		skp->Line( 498, 326, 498, 339 );

		// white boxes
		skp->SetBrush( skpBlackBrush );
		skp->Rectangle( 455, 255, 494, 272 );
		skp->Rectangle( 455, 358, 494, 375 );

		// yellow lines
		if (active) skp->SetPen( skpYellowPen );
		else skp->SetPen( skpRedPen );

		skp->Line( 31, 237, 18, 237 );
		skp->Line( 51, 237, 64, 237 );

		skp->Line( 110, 237, 97, 237 );
		skp->Line( 130, 237, 143, 237 );

		skp->Line( 384, 78, 384, 65 );

		skp->Line( 384, 178, 384, 165 );

		// body flap trail mark
		skp->SetPen( skpYellowPen );
		skp->SetBrush( skpYellowBrush );
		tri[0].x = 207;
		tri[0].y = 172;
		tri[1].x = 217;
		tri[1].y = 167;
		tri[2].x = 217;
		tri[2].y = 177;
		skp->Polygon( tri, 3 );
		skp->Rectangle( 216, /*168*/167, 226, 178 );

		if (!active) return;

		// elevons
		nPos = Round( 237 + (4 * range( -35.0, LOB, 20.0 )) );
		tri[0].x = 22;
		tri[0].y = nPos;
		tri[1].x = 38;
		tri[1].y = nPos - 8;
		tri[2].x = 38;
		tri[2].y = nPos + 8;
		skp->Polygon( tri, 3 );

		nPos = Round( 237 + (4 * range( -35.0, LIB, 20.0 )) );
		tri[0].x = 60;
		tri[0].y = nPos;
		tri[1].x = 44;
		tri[1].y = nPos - 8;
		tri[2].x = 44;
		tri[2].y = nPos + 8;
		skp->Polygon( tri, 3 );

		nPos = Round( 237 + (4 * range( -35.0, RIB, 20.0 )) );
		tri[0].x = 101;
		tri[0].y = nPos;
		tri[1].x = 117;
		tri[1].y = nPos - 8;
		tri[2].x = 117;
		tri[2].y = nPos + 8;
		skp->Polygon( tri, 3 );

		nPos = Round( 237 + (4 * range( -35.0, ROB, 20.0 )) );
		tri[0].x = 139;
		tri[0].y = nPos;
		tri[1].x = 123;
		tri[1].y = nPos - 8;
		tri[2].x = 123;
		tri[2].y = nPos + 8;
		skp->Polygon( tri, 3 );

		// body flap
		nPos = Round( 97 + (2.2 * range( 0.0, DBFOFB, 100.0 )) );
		tri[0].x = 206;
		tri[0].y = nPos;
		tri[1].x = 190;
		tri[1].y = nPos - 8;
		tri[2].x = 190;
		tri[2].y = nPos + 8;
		skp->Polygon( tri, 3 );

		// rudder
		nPos = Round( 384 + (3.8 * range( -30.0, DRFB, 30.0 )) );
		tri[0].x = nPos;
		tri[0].y = 70;
		tri[1].x = nPos - 8;
		tri[1].y = 86;
		tri[2].x = nPos + 8;
		tri[2].y = 86;
		skp->Polygon( tri, 3 );

		// aileron
		nPos = Round( 384 + (22.8 * range( -5.0, DAFB, 5.0 )) );
		tri[0].x = nPos;
		tri[0].y = 170;
		tri[1].x = nPos - 8;
		tri[1].y = 186;
		tri[2].x = nPos + 8;
		tri[2].y = 186;
		skp->Polygon( tri, 3 );

		// speedbrake
		skp->SetTextColor( CR_YELLOW );
		dNum = range( 0.0, Speedbrake_Pos, 100.0 );
		sprintf_s( cbuf, 8, "%03.0f", dNum );
		skp->Text( 459, 258, cbuf, strlen( cbuf ) );
		nPos = Round( 270 + (2.28 * dNum) );
		tri[0].x = nPos;
		tri[0].y = 297;
		tri[1].x = nPos + 8;
		tri[1].y = 313;
		tri[2].x = nPos - 8;
		tri[2].y = 313;
		skp->Polygon( tri, 3 );

		skp->SetPen( skpCyanPen );
		skp->SetBrush( skpCyanBrush );
		skp->SetTextColor( CR_CYAN );
		dNum = range( 0.0, Speedbrake_Cmd, 100.0 );
		sprintf_s( cbuf, 8, "%03.0f", dNum );
		skp->Text( 459, 361, cbuf, strlen( cbuf ) );
		nPos = Round( 270 + (2.28 * dNum) );
		tri[0].x = nPos;
		tri[0].y = 335;
		tri[1].x = nPos + 8;
		tri[1].y = 319;
		tri[2].x = nPos - 8;
		tri[2].y = 319;
		skp->Polygon( tri, 3 );
		return;
	}
}

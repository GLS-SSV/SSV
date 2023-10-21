/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2020/08/24   GLS
2020/08/30   GLS
2020/09/07   GLS
2021/06/13   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/12/17   GLS
2023/10/22   GLS
********************************************/
#include "MDU.h"
#include "../Atlantis.h"
#include "../dps/IDP.h"
#include <MathSSV.h>


namespace vc
{
	void MDU::ORBITPFD( HDC hDC )
	{
		int MM = STS()->GetGPCMajorMode();
		double sinpitch;
		double cospitch;
		double sinroll;
		double cosroll;
		double sinyaw;
		double cosyaw;
		GetIDP()->GetADIAtt( usMDUID, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
		unsigned short pitchrate;
		unsigned short rollrate;
		unsigned short yawrate;
		unsigned short pitchratescale;// not used
		unsigned short rollratescale;// not used
		unsigned short yawratescale;// not used
		unsigned short TGOSEC;// not used
		unsigned short ADIRR_0_ON_R;// not used
		GetIDP()->GetADIRate( usMDUID, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
		unsigned short pitcherror;
		unsigned short rollerror;
		unsigned short yawerror;
		unsigned short pitcherrorscale;// not used
		GetIDP()->GetADIError( usMDUID, pitcherror, rollerror, yawerror, pitcherrorscale );

		SelectObject( hDC, gdiSSVBFont_h12w7 );

		ADI_STATIC_ORBIT( hDC );
		if ((MM == 201) || (MM == 202) || (MM == 801))
		{
			ADI_ORBIT( hDC, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
			ADI_RATE_ORBIT( hDC, pitchrate, rollrate, yawrate );
			ADI_ERROR_ORBIT( hDC, pitcherror, rollerror, yawerror );
		}
		else ADI_ORBIT( hDC, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
		return;
	}

	void MDU::ORBITPFD( oapi::Sketchpad2* skp )
	{
		int MM = STS()->GetGPCMajorMode();
		double sinpitch;
		double cospitch;
		double sinroll;
		double cosroll;
		double sinyaw;
		double cosyaw;
		GetIDP()->GetADIAtt( usMDUID, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
		unsigned short pitchrate;
		unsigned short rollrate;
		unsigned short yawrate;
		unsigned short pitchratescale;// not used
		unsigned short rollratescale;// not used
		unsigned short yawratescale;// not used
		unsigned short TGOSEC;// not used
		unsigned short ADIRR_0_ON_R;// not used
		GetIDP()->GetADIRate( usMDUID, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
		unsigned short pitcherror;
		unsigned short rollerror;
		unsigned short yawerror;
		unsigned short pitcherrorscale;// not used
		GetIDP()->GetADIError( usMDUID, pitcherror, rollerror, yawerror, pitcherrorscale );

		skp->SetFont( skpSSVBFont_h12w7 );

		ADI_STATIC_ORBIT( skp );
		if ((MM == 201) || (MM == 202) || (MM == 801))
		{
			ADI_ORBIT( skp, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
			ADI_RATE_ORBIT( skp, pitchrate, rollrate, yawrate );
			ADI_ERROR_ORBIT( skp, pitcherror, rollerror, yawerror );
		}
		else ADI_ORBIT( skp, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
		return;
	}

	void MDU::ADI_STATIC_ORBIT( HDC hDC )
	{
		SetTextColor( hDC, CR_LIGHT_GRAY );
		TextOut( hDC, 379, 56, "R", 1 );
		TextOut( hDC, 379, 70, "P", 1 );
		TextOut( hDC, 379, 84, "Y", 1 );

		TextOut( hDC, 253, 61, "0", 1 );
		TextOut( hDC, 409, 216, "0", 1 );
		TextOut( hDC, 253, 371, "0", 1 );

		SelectObject( hDC, gdiWhitePen );
		::Ellipse( hDC, 124, 91, 388, 355 );

		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiLightGrayBrush );
		POINT diamond[4];
		diamond[0].x = 256;
		diamond[0].y = 99;
		diamond[1].x = 261;
		diamond[1].y = 106;
		diamond[2].x = 256;
		diamond[2].y = 113;
		diamond[3].x = 251;
		diamond[3].y = 106;
		Polygon( hDC, diamond, 4 );// top
		//diamond[0].x = 256;
		diamond[0].y = 333;
		//diamond[1].x = 261;
		diamond[1].y = 340;
		//diamond[2].x = 256;
		diamond[2].y = 347;
		//diamond[3].x = 251;
		diamond[3].y = 340;
		Polygon( hDC, diamond, 4 );// bottom
		diamond[0].x = 373;
		diamond[0].y = 218;
		diamond[1].x = 380;
		diamond[1].y = 223;
		diamond[2].x = 373;
		diamond[2].y = 228;
		diamond[3].x = 366;
		diamond[3].y = 223;
		Polygon( hDC, diamond, 4 );// right
		diamond[0].x = 139;
		//diamond[0].y = 218;
		diamond[1].x = 146;
		//diamond[1].y = 223;
		diamond[2].x = 139;
		//diamond[2].y = 228;
		diamond[3].x = 132;
		//diamond[3].y = 223;
		Polygon( hDC, diamond, 4 );// left

		// rate scales
		// top scale
		MoveToEx( hDC, 167, 76, NULL );
		LineTo( hDC, 345, 76 );
		MoveToEx( hDC, 167, 76, NULL );
		LineTo( hDC, 167, 86 );
		MoveToEx( hDC, 185, 76, NULL );
		LineTo( hDC, 185, 81 );
		MoveToEx( hDC, 203, 76, NULL );
		LineTo( hDC, 203, 81 );
		MoveToEx( hDC, 220, 76, NULL );
		LineTo( hDC, 220, 81 );
		MoveToEx( hDC, 238, 76, NULL );
		LineTo( hDC, 238, 81 );
		MoveToEx( hDC, 256, 76, NULL );
		LineTo( hDC, 256, 86 );
		MoveToEx( hDC, 274, 76, NULL );
		LineTo( hDC, 274, 81 );
		MoveToEx( hDC, 292, 76, NULL );
		LineTo( hDC, 292, 81 );
		MoveToEx( hDC, 309, 76, NULL );
		LineTo( hDC, 309, 81 );
		MoveToEx( hDC, 327, 76, NULL );
		LineTo( hDC, 327, 81 );
		MoveToEx( hDC, 345, 76, NULL );
		LineTo( hDC, 345, 86 );

		// side scale
		MoveToEx( hDC, 403, 134, NULL );
		LineTo( hDC, 403, 312 );
		MoveToEx( hDC, 403, 134, NULL );
		LineTo( hDC, 393, 134 );
		MoveToEx( hDC, 403, 152, NULL );
		LineTo( hDC, 398, 152 );
		MoveToEx( hDC, 403, 170, NULL );
		LineTo( hDC, 398, 170 );
		MoveToEx( hDC, 403, 187, NULL );
		LineTo( hDC, 398, 187 );
		MoveToEx( hDC, 403, 205, NULL );
		LineTo( hDC, 398, 205 );
		MoveToEx( hDC, 403, 223, NULL );
		LineTo( hDC, 393, 223 );
		MoveToEx( hDC, 403, 241, NULL );
		LineTo( hDC, 398, 241 );
		MoveToEx( hDC, 403, 259, NULL );
		LineTo( hDC, 398, 259 );
		MoveToEx( hDC, 403, 276, NULL );
		LineTo( hDC, 398, 276 );
		MoveToEx( hDC, 403, 294, NULL );
		LineTo( hDC, 398, 294 );
		MoveToEx( hDC, 403, 312, NULL );
		LineTo( hDC, 393, 312 );

		// bottom scale
		MoveToEx( hDC, 167, 370, NULL );
		LineTo( hDC, 345, 370 );
		MoveToEx( hDC, 167, 370, NULL );
		LineTo( hDC, 167, 360 );
		MoveToEx( hDC, 185, 370, NULL );
		LineTo( hDC, 185, 365 );
		MoveToEx( hDC, 203, 370, NULL );
		LineTo( hDC, 203, 365 );
		MoveToEx( hDC, 220, 370, NULL );
		LineTo( hDC, 220, 365 );
		MoveToEx( hDC, 238, 370, NULL );
		LineTo( hDC, 238, 365 );
		MoveToEx( hDC, 256, 370, NULL );
		LineTo( hDC, 256, 360 );
		MoveToEx( hDC, 274, 370, NULL );
		LineTo( hDC, 274, 365 );
		MoveToEx( hDC, 292, 370, NULL );
		LineTo( hDC, 292, 365 );
		MoveToEx( hDC, 309, 370, NULL );
		LineTo( hDC, 309, 365 );
		MoveToEx( hDC, 327, 370, NULL );
		LineTo( hDC, 327, 365 );
		MoveToEx( hDC, 345, 370, NULL );
		LineTo( hDC, 345, 360 );

		// roll lines
		MoveToEx( hDC, 246, 109, NULL );// 5º/185º
		LineTo( hDC, 266, 337 );
		MoveToEx( hDC, 236, 111, NULL );// 10º/190º
		LineTo( hDC, 276, 335 );
		MoveToEx( hDC, 226, 113, NULL );// 15º/195º
		LineTo( hDC, 286, 333 );
		MoveToEx( hDC, 217, 116, NULL );// 20º/200º
		LineTo( hDC, 295, 330 );
		MoveToEx( hDC, 208, 120, NULL );// 25º/205º
		LineTo( hDC, 304, 326 );

		MoveToEx( hDC, 191, 130, NULL );// 35º/215º
		LineTo( hDC, 321, 316 );
		MoveToEx( hDC, 183, 136, NULL );// 40º/220º
		LineTo( hDC, 329, 310 );
		MoveToEx( hDC, 175, 142, NULL );// 45º/225º
		LineTo( hDC, 337, 304 );
		MoveToEx( hDC, 169, 150, NULL );// 50º/230º
		LineTo( hDC, 343, 296 );
		MoveToEx( hDC, 163, 158, NULL );// 55º/235º
		LineTo( hDC, 349, 288 );

		MoveToEx( hDC, 153, 175, NULL );// 65º/245º
		LineTo( hDC, 359, 271 );
		MoveToEx( hDC, 149, 184, NULL );// 70º/250º
		LineTo( hDC, 363, 262 );
		MoveToEx( hDC, 146, 193, NULL );// 75º/255º
		LineTo( hDC, 366, 253 );
		MoveToEx( hDC, 144, 203, NULL );// 80º/260º
		LineTo( hDC, 368, 243 );
		MoveToEx( hDC, 142, 213, NULL );// 85º/265º
		LineTo( hDC, 370, 233 );

		MoveToEx( hDC, 142, 233, NULL );// 95º/275º
		LineTo( hDC, 370, 213 );
		MoveToEx( hDC, 144, 243, NULL );// 100º/280º
		LineTo( hDC, 368, 203 );
		MoveToEx( hDC, 146, 253, NULL );// 105º/285º
		LineTo( hDC, 366, 193 );
		MoveToEx( hDC, 149, 262, NULL );// 110º/290º
		LineTo( hDC, 363, 184 );
		MoveToEx( hDC, 153, 271, NULL );// 115º/295º
		LineTo( hDC, 359, 175 );

		MoveToEx( hDC, 163, 288, NULL );// 125º/305º
		LineTo( hDC, 349, 158 );
		MoveToEx( hDC, 169, 296, NULL );// 130º/310º
		LineTo( hDC, 343, 150 );
		MoveToEx( hDC, 175, 304, NULL );// 135º/315º
		LineTo( hDC, 337, 142 );
		MoveToEx( hDC, 183, 310, NULL );// 140º/320º
		LineTo( hDC, 329, 136 );
		MoveToEx( hDC, 191, 316, NULL );// 145º/325º
		LineTo( hDC, 321, 130 );

		MoveToEx( hDC, 208, 326, NULL );// 155º/335º
		LineTo( hDC, 304, 120 );
		MoveToEx( hDC, 217, 330, NULL );// 160º/340º
		LineTo( hDC, 295, 116 );
		MoveToEx( hDC, 226, 333, NULL );// 165º/345º
		LineTo( hDC, 286, 113 );
		MoveToEx( hDC, 236, 335, NULL );// 170º/350º
		LineTo( hDC, 276, 111 );
		MoveToEx( hDC, 246, 337, NULL );// 175º/355º
		LineTo( hDC, 266, 109 );
		SelectObject( hDC, gdiLightGrayThickPen );
		MoveToEx( hDC, 197, 121, NULL );// 30º/210º
		LineTo( hDC, 315, 325 );
		MoveToEx( hDC, 154, 164, NULL );// 60º/240º
		LineTo( hDC, 358, 282 );
		MoveToEx( hDC, 154, 282, NULL );// 120º/300º
		LineTo( hDC, 358, 164 );
		MoveToEx( hDC, 197, 325, NULL );// 150º/330º
		LineTo( hDC, 315, 121 );

		// cover center for ADI SRCPAINT
		SelectObject( hDC, GetStockObject( BLACK_BRUSH ) );
		SelectObject( hDC, GetStockObject( BLACK_PEN ) );
		::Ellipse( hDC, 146, 113, 366, 333 );

		TextOut( hDC, 317, 115, "33", 2 );
		TextOut( hDC, 351, 150, "30", 2 );
		TextOut( hDC, 351, 283, "24", 2 );
		TextOut( hDC, 317, 318, "21", 2 );
		TextOut( hDC, 181, 318, "15", 2 );
		TextOut( hDC, 148, 282, "12", 2 );
		TextOut( hDC, 148, 149, "06", 2 );
		TextOut( hDC, 181, 115, "03", 2 );

		// att needles
		// top scale
		SelectObject( hDC, gdiMagentaPen );
		SelectObject( hDC, gdiMagentaBrush );
		Arc( hDC, 131, 98, 381, 348, 306, 108, 206, 108 );
		MoveToEx( hDC, 206, 109, NULL );
		LineTo( hDC, 206, 114 );
		MoveToEx( hDC, 216, 106, NULL );
		LineTo( hDC, 216, 111 );
		MoveToEx( hDC, 226, 103, NULL );
		LineTo( hDC, 226, 108 );
		MoveToEx( hDC, 236, 101, NULL );
		LineTo( hDC, 236, 106 );
		MoveToEx( hDC, 246, 100, NULL );
		LineTo( hDC, 246, 105 );
		MoveToEx( hDC, 256, 99, NULL );
		LineTo( hDC, 256, 104 );
		MoveToEx( hDC, 266, 100, NULL );
		LineTo( hDC, 266, 105 );
		MoveToEx( hDC, 276, 101, NULL );
		LineTo( hDC, 276, 106 );
		MoveToEx( hDC, 286, 103, NULL );
		LineTo( hDC, 286, 109 );
		MoveToEx( hDC, 296, 106, NULL );
		LineTo( hDC, 296, 111 );
		MoveToEx( hDC, 306, 109, NULL );
		LineTo( hDC, 306, 114 );

		// side scale
		Arc( hDC, 131, 98, 381, 348, 371, 273, 371, 173 );
		MoveToEx( hDC, 370, 173, NULL );
		LineTo( hDC, 365, 173 );
		MoveToEx( hDC, 373, 183, NULL );
		LineTo( hDC, 368, 183 );
		MoveToEx( hDC, 376, 193, NULL );
		LineTo( hDC, 371, 193 );
		MoveToEx( hDC, 378, 203, NULL );
		LineTo( hDC, 373, 203 );
		MoveToEx( hDC, 379, 213, NULL );
		LineTo( hDC, 374, 213 );
		MoveToEx( hDC, 380, 223, NULL );
		LineTo( hDC, 375, 223 );
		MoveToEx( hDC, 379, 233, NULL );
		LineTo( hDC, 374, 233 );
		MoveToEx( hDC, 378, 243, NULL );
		LineTo( hDC, 373, 243 );
		MoveToEx( hDC, 376, 253, NULL );
		LineTo( hDC, 371, 253 );
		MoveToEx( hDC, 373, 263, NULL );
		LineTo( hDC, 368, 263 );
		MoveToEx( hDC, 370, 273, NULL );
		LineTo( hDC, 365, 273 );

		// bottom scale
		Arc( hDC, 131, 98, 381, 348, 206, 338, 306, 338 );
		MoveToEx( hDC, 206, 336, NULL );
		LineTo( hDC, 206, 331 );
		MoveToEx( hDC, 216, 339, NULL );
		LineTo( hDC, 216, 334 );
		MoveToEx( hDC, 226, 342, NULL );
		LineTo( hDC, 226, 337 );
		MoveToEx( hDC, 236, 344, NULL );
		LineTo( hDC, 236, 339 );
		MoveToEx( hDC, 246, 345, NULL );
		LineTo( hDC, 246, 340 );
		MoveToEx( hDC, 256, 346, NULL );
		LineTo( hDC, 256, 341 );
		MoveToEx( hDC, 266, 345, NULL );
		LineTo( hDC, 266, 340 );
		MoveToEx( hDC, 276, 344, NULL );
		LineTo( hDC, 276, 339 );
		MoveToEx( hDC, 286, 342, NULL );
		LineTo( hDC, 286, 337 );
		MoveToEx( hDC, 296, 339, NULL );
		LineTo( hDC, 296, 334 );
		MoveToEx( hDC, 306, 336, NULL );
		LineTo( hDC, 306, 331 );
		return;
	}

	void MDU::ADI_STATIC_ORBIT( oapi::Sketchpad2* skp )
	{
		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Text( 379, 56, "R", 1 );
		skp->Text( 379, 70, "P", 1 );
		skp->Text( 379, 84, "Y", 1 );

		skp->Text( 253, 61, "0", 1 );
		skp->Text( 409, 216, "0", 1 );
		skp->Text( 253, 371, "0", 1 );

		skp->SetPen( skpWhitePen );
		skp->Ellipse( 124, 91, 388, 355 );

		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpLightGrayBrush );
		oapi::IVECTOR2 diamond[4];
		diamond[0].x = 256;
		diamond[0].y = 99;
		diamond[1].x = 261;
		diamond[1].y = 106;
		diamond[2].x = 256;
		diamond[2].y = 113;
		diamond[3].x = 251;
		diamond[3].y = 106;
		skp->Polygon( diamond, 4 );// top
		//diamond[0].x = 256;
		diamond[0].y = 333;
		//diamond[1].x = 261;
		diamond[1].y = 340;
		//diamond[2].x = 256;
		diamond[2].y = 347;
		//diamond[3].x = 251;
		diamond[3].y = 340;
		skp->Polygon( diamond, 4 );// bottom
		diamond[0].x = 373;
		diamond[0].y = 218;
		diamond[1].x = 380;
		diamond[1].y = 223;
		diamond[2].x = 373;
		diamond[2].y = 228;
		diamond[3].x = 366;
		diamond[3].y = 223;
		skp->Polygon( diamond, 4 );// right
		diamond[0].x = 139;
		//diamond[0].y = 218;
		diamond[1].x = 146;
		//diamond[1].y = 223;
		diamond[2].x = 139;
		//diamond[2].y = 228;
		diamond[3].x = 132;
		//diamond[3].y = 223;
		skp->Polygon( diamond, 4 );// left

		// rate scales
		// top scale
		skp->Line( 167, 76, 345, 76 );
		skp->Line( 167, 76, 167, 86 );
		skp->Line( 185, 76, 185, 81 );
		skp->Line( 203, 76, 203, 81 );
		skp->Line( 220, 76, 220, 81 );
		skp->Line( 238, 76, 238, 81 );
		skp->Line( 256, 76, 256, 86 );
		skp->Line( 274, 76, 274, 81 );
		skp->Line( 292, 76, 292, 81 );
		skp->Line( 309, 76, 309, 81 );
		skp->Line( 327, 76, 327, 81 );
		skp->Line( 345, 76, 345, 86 );

		// side scale
		skp->Line( 403, 134, 403, 312 );
		skp->Line( 403, 134, 393, 134 );
		skp->Line( 403, 152, 398, 152 );
		skp->Line( 403, 170, 398, 170 );
		skp->Line( 403, 187, 398, 187 );
		skp->Line( 403, 205, 398, 205 );
		skp->Line( 403, 223, 393, 223 );
		skp->Line( 403, 241, 398, 241 );
		skp->Line( 403, 259, 398, 259 );
		skp->Line( 403, 276, 398, 276 );
		skp->Line( 403, 294, 398, 294 );
		skp->Line( 403, 312, 393, 312 );

		// bottom scale
		skp->Line( 167, 370, 345, 370 );
		skp->Line( 167, 370, 167, 360 );
		skp->Line( 185, 370, 185, 365 );
		skp->Line( 203, 370, 203, 365 );
		skp->Line( 220, 370, 220, 365 );
		skp->Line( 238, 370, 238, 365 );
		skp->Line( 256, 370, 256, 360 );
		skp->Line( 274, 370, 274, 365 );
		skp->Line( 292, 370, 292, 365 );
		skp->Line( 309, 370, 309, 365 );
		skp->Line( 327, 370, 327, 365 );
		skp->Line( 345, 370, 345, 360 );

		// roll lines
		skp->Line( 246, 109, 266, 337 );// 5º/185º
		skp->Line( 236, 111, 276, 335 );// 10º/190º
		skp->Line( 226, 113, 286, 333 );// 15º/195º
		skp->Line( 217, 116, 295, 330 );// 20º/200º
		skp->Line( 208, 120, 304, 326 );// 25º/205º

		skp->Line( 191, 130, 321, 316 );// 35º/215º
		skp->Line( 183, 136, 329, 310 );// 40º/220º
		skp->Line( 175, 142, 337, 304 );// 45º/225º
		skp->Line( 169, 150, 343, 296 );// 50º/230º
		skp->Line( 163, 158, 349, 288 );// 55º/235º

		skp->Line( 153, 175, 359, 271 );// 65º/245º
		skp->Line( 149, 184, 363, 262 );// 70º/250º
		skp->Line( 146, 193, 366, 253 );// 75º/255º
		skp->Line( 144, 203, 368, 243 );// 80º/260º
		skp->Line( 142, 213, 370, 233 );// 85º/265º

		skp->Line( 142, 233, 370, 213 );// 95º/275º
		skp->Line( 144, 243, 368, 203 );// 100º/280º
		skp->Line( 146, 253, 366, 193 );// 105º/285º
		skp->Line( 149, 262, 363, 184 );// 110º/290º
		skp->Line( 153, 271, 359, 175 );// 115º/295º

		skp->Line( 163, 288, 349, 158 );// 125º/305º
		skp->Line( 169, 296, 343, 150 );// 130º/310º
		skp->Line( 175, 304, 337, 142 );// 135º/315º
		skp->Line( 183, 310, 329, 136 );// 140º/320º
		skp->Line( 191, 316, 321, 130 );// 145º/325º

		skp->Line( 208, 326, 304, 120 );// 155º/335º
		skp->Line( 217, 330, 295, 116 );// 160º/340º
		skp->Line( 226, 333, 286, 113 );// 165º/345º
		skp->Line( 236, 335, 276, 111 );// 170º/350º
		skp->Line( 246, 337, 266, 109 );// 175º/355º

		skp->SetPen( skpLightGrayThickPen );
		skp->Line( 197, 121, 315, 325 );// 30º/210º
		skp->Line( 154, 164, 358, 282 );// 60º/240º
		skp->Line( 154, 282, 358, 164 );// 120º/300º
		skp->Line( 197, 325, 315, 121 );// 150º/330º

		// cover center for ADI SRCPAINT
		skp->SetBrush( _skpBlackBrush );
		skp->SetPen( _skpBlackPen );
		skp->Ellipse( 146, 113, 366, 333 );

		skp->Text( 317, 115, "33", 2 );
		skp->Text( 351, 150, "30", 2 );
		skp->Text( 351, 283, "24", 2 );
		skp->Text( 317, 318, "21", 2 );
		skp->Text( 181, 318, "15", 2 );
		skp->Text( 148, 282, "12", 2 );
		skp->Text( 148, 149, "06", 2 );
		skp->Text( 181, 115, "03", 2 );

		// att needles
		// top scale
		skp->SetPen( skpMagentaPen );
		skp->SetBrush( skpMagentaBrush );
		//Arc( hDC, 131, 98, 381, 348, 306, 108, 206, 108 );
		// HACK makeshift arc
		skp->Line( 206, 109, 216, 106 );
		skp->Line( 216, 106, 226, 103 );
		skp->Line( 226, 103, 236, 101 );
		skp->Line( 236, 101, 246, 100 );
		skp->Line( 246, 100, 256, 99 );
		skp->Line( 256, 99, 266, 100 );
		skp->Line( 266, 100, 276, 101 );
		skp->Line( 276, 101, 286, 103 );
		skp->Line( 286, 103, 296, 106 );
		skp->Line( 296, 106, 306, 109 );

		skp->Line( 206, 109, 206, 114 );
		skp->Line( 216, 106, 216, 111 );
		skp->Line( 226, 103, 226, 108 );
		skp->Line( 236, 101, 236, 106 );
		skp->Line( 246, 100, 246, 105 );
		skp->Line( 256, 99, 256, 104 );
		skp->Line( 266, 100, 266, 105 );
		skp->Line( 276, 101, 276, 106 );
		skp->Line( 286, 103, 286, 109 );
		skp->Line( 296, 106, 296, 111 );
		skp->Line( 306, 109, 306, 114 );

		// side scale
		//Arc( hDC, 131, 98, 381, 348, 371, 273, 371, 173 );
		// HACK makeshift arc
		skp->Line( 370, 173, 373, 183 );
		skp->Line( 373, 183, 376, 193 );
		skp->Line( 376, 193, 378, 203 );
		skp->Line( 378, 203, 379, 213 );
		skp->Line( 379, 213, 380, 223 );
		skp->Line( 380, 223, 379, 233 );
		skp->Line( 379, 233, 378, 243 );
		skp->Line( 378, 243, 376, 253 );
		skp->Line( 376, 253, 373, 263 );
		skp->Line( 373, 263, 370, 273 );

		skp->Line( 370, 173, 365, 173 );
		skp->Line( 373, 183, 368, 183 );
		skp->Line( 376, 193, 371, 193 );
		skp->Line( 378, 203, 373, 203 );
		skp->Line( 379, 213, 374, 213 );
		skp->Line( 380, 223, 375, 223 );
		skp->Line( 379, 233, 374, 233 );
		skp->Line( 378, 243, 373, 243 );
		skp->Line( 376, 253, 371, 253 );
		skp->Line( 373, 263, 368, 263 );
		skp->Line( 370, 273, 365, 273 );

		// bottom scale
		//Arc( hDC, 131, 98, 381, 348, 206, 338, 306, 338 );
		// HACK makeshift arc
		skp->Line( 206, 336, 216, 339 );
		skp->Line( 216, 339, 226, 342 );
		skp->Line( 226, 342, 236, 344 );
		skp->Line( 236, 344, 246, 345 );
		skp->Line( 246, 345, 256, 346 );
		skp->Line( 256, 346, 266, 345 );
		skp->Line( 266, 345, 276, 344 );
		skp->Line( 276, 344, 286, 342 );
		skp->Line( 286, 342, 296, 339 );
		skp->Line( 296, 339, 306, 336 );

		skp->Line( 206, 336, 206, 331 );
		skp->Line( 216, 339, 216, 334 );
		skp->Line( 226, 342, 226, 337 );
		skp->Line( 236, 344, 236, 339 );
		skp->Line( 246, 345, 246, 340 );
		skp->Line( 256, 346, 256, 341 );
		skp->Line( 266, 345, 266, 340 );
		skp->Line( 276, 344, 276, 339 );
		skp->Line( 286, 342, 286, 337 );
		skp->Line( 296, 339, 296, 334 );
		skp->Line( 306, 336, 306, 331 );
		return;
	}

	void MDU::ADI_ORBIT( HDC hDC, double sinpitch, double cospitch, double sinroll, double cosroll, double sinyaw, double cosyaw )
	{
		// center (256,223) r = 132
		// view r = 110, ball r = 110 * sqrt( 2 )
		// 90º pitch/yaw "FOV"

		double digitalpitch = atan2( sinpitch, cospitch );
		double ballpitch = digitalpitch * DEG;
		if (digitalpitch < 0.0) digitalpitch += PI2;
		double digitalroll = atan2( sinroll, cosroll );
		if (digitalroll < 0.0) digitalroll += PI2;
		double digitalyaw = atan2( sinyaw, cosyaw );
		if (digitalyaw > PI05) digitalyaw = PI - digitalyaw;
		if (digitalyaw < -PI05) digitalyaw = PI - digitalyaw;
		if (digitalyaw < 0.0) digitalyaw += PI2;

		// apply roll
		XFORM WTroll;
		WTroll.eM11 = (FLOAT)cosroll;
		WTroll.eM12 = (FLOAT)sinroll;
		WTroll.eM21 = -WTroll.eM12;
		WTroll.eM22 = WTroll.eM11;
		WTroll.eDx = (FLOAT)(111 * (1 - WTroll.eM11 - WTroll.eM21));
		WTroll.eDy = (FLOAT)(111 * (1 - WTroll.eM11 + WTroll.eM21));
		SetGraphicsMode( hDC_ADI_ORBIT, GM_ADVANCED );
		SetWorldTransform( hDC_ADI_ORBIT, &WTroll );

		// 0º pitch line/labels
		int hP;
		double hP2;
		SetTextColor( hDC_ADI_ORBIT, CR_BLACK );
		SetBkColor( hDC_ADI_ORBIT, CR_WHITE );
		if (fabs( ballpitch ) <= 45)
		{
			hP = Round( 155.5635 * sinpitch );
			if (ballpitch < 0)
			{
				SelectObject( hDC_ADI_ORBIT, gdiWhiteBrush );
				SelectObject( hDC_ADI_ORBIT, gdiWhitePen );
				Rectangle( hDC_ADI_ORBIT, 0, 0, 224, 112 );
				SelectObject( hDC_ADI_ORBIT, gdiDarkGrayBrush );
				SelectObject( hDC_ADI_ORBIT, gdiDarkGrayPen );
				Chord( hDC_ADI_ORBIT, -44, 112 - hP, 268, 112 + hP, 268, 112, -44, 112 );
				Rectangle( hDC_ADI_ORBIT, 0, 112, 224, 224 );
			}
			else
			{
				SelectObject( hDC_ADI_ORBIT, gdiDarkGrayBrush );
				SelectObject( hDC_ADI_ORBIT, gdiDarkGrayPen );
				Rectangle( hDC_ADI_ORBIT, 0, 112, 224, 224 );
				SelectObject( hDC_ADI_ORBIT, gdiWhiteBrush );
				SelectObject( hDC_ADI_ORBIT, gdiWhitePen );
				Chord( hDC_ADI_ORBIT, -44, 112 - hP, 268, 112 + hP, -44, 112, 268, 112 );
				Rectangle( hDC_ADI_ORBIT, 0, 0, 224, 112 );
			}
			hP = 110 + Round( 150.262794 * sinpitch );
			TextOut( hDC_ADI_ORBIT, 70, hP, "0", 1 );
			TextOut( hDC_ADI_ORBIT, 150, hP, "0", 1 );
		}
		else if (ballpitch > 0)
		{
			SelectObject( hDC_ADI_ORBIT, gdiWhiteBrush );
			Rectangle( hDC_ADI_ORBIT, -2, -2, 224, 224 );
		}
		else
		{
			SelectObject( hDC_ADI_ORBIT, gdiDarkGrayBrush );
			Rectangle( hDC_ADI_ORBIT, -2, -2, 224, 224 );
		}

		// pitch lines/labels for +30º/+60º/+90º/+120º/+150º
		SelectObject( hDC_ADI_ORBIT, gdiBlackPen );
		// +30º
		if (fabs( ballpitch - 30 ) <= 45)
		{
			hP2 = sinpitch * 134.721936 - cospitch * 77.781746;//hP = 138.592 * sin( (pitch - 30) * RAD );
			hP = Round( hP2 );
			if (ballpitch < 30) Arc( hDC_ADI_ORBIT, -44, 112 - hP, 268, 112 + hP, 268, 112, -44, 112 );
			else Arc( hDC_ADI_ORBIT, -44, 112 - hP, 268, 112 + hP, -44, 112, 268, 112 );
			hP = 105 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI_ORBIT, 70, hP, "3", 1 );
			TextOut( hDC_ADI_ORBIT, 150, hP, "3", 1 );
		}
		// +60º
		if (fabs( ballpitch - 60 ) <= 45)
		{
			hP2 = sinpitch * 77.781746 - cospitch * 134.721936;
			hP = Round( hP2 );
			if (ballpitch < 60) Arc( hDC_ADI_ORBIT, -44, 112 - hP, 268, 112 + hP, 268, 112, -44, 112 );
			else Arc( hDC_ADI_ORBIT, -44, 112 - hP, 268, 112 + hP, -44, 112, 268, 112 );
			hP = 105 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI_ORBIT, 70, hP, "6", 1 );
			TextOut( hDC_ADI_ORBIT, 150, hP, "6", 1 );
		}
		// +90º
		if (fabs( ballpitch - 90 ) <= 45)
		{
			hP2 = 155.5634 * (-cospitch);
			hP = Round( hP2 );
			if (ballpitch < 90) Arc( hDC_ADI_ORBIT, -44, 112 - hP, 268, 112 + hP, 268, 112, -44, 112 );
			else Arc( hDC_ADI_ORBIT, -44, 112 - hP, 268, 112 + hP, -44, 112, 268, 112 );
			hP = 105 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI_ORBIT, 70, hP, "9", 1 );
			TextOut( hDC_ADI_ORBIT, 150, hP, "9", 1 );
		}
		// +120º
		if (fabs( ballpitch - 120 ) <= 45)
		{
			hP2 = (-sinpitch) * 77.781746 - cospitch * 134.721936;
			hP = Round( hP2 );
			if (ballpitch < 120) Arc( hDC_ADI_ORBIT, -44, 112 - hP, 268, 112 + hP, 268, 112, -44, 112 );
			else Arc( hDC_ADI_ORBIT, -44, 112 - hP, 268, 112 + hP, -44, 112, 268, 112 );
			hP = 105 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI_ORBIT, 66, hP, "12", 2 );
			TextOut( hDC_ADI_ORBIT, 146, hP, "12", 2 );
		}
		// +150º
		if (fabs( ballpitch - 150 ) <= 45)
		{
			hP2 = (-sinpitch) * 134.721936 - cospitch * 77.781746;
			hP = Round( hP2 );
			if (ballpitch < 150) Arc( hDC_ADI_ORBIT, -44, 112 - hP, 268, 112 + hP, 268, 112, -44, 112 );
			else Arc( hDC_ADI_ORBIT, -44, 112 - hP, 268, 112 + hP, -44, 112, 268, 112 );
			hP = 105 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI_ORBIT, 66, hP, "15", 2 );
			TextOut( hDC_ADI_ORBIT, 146, hP, "15", 2 );
		}

		// pitch lines/labels for -30º/-60º/-90º/-120º/-150º
		SelectObject( hDC_ADI_ORBIT, gdiWhitePen );
		SetTextColor( hDC_ADI_ORBIT, CR_WHITE );
		SetBkColor( hDC_ADI_ORBIT, CR_DARK_GRAY );
		// -30º
		if (fabs( ballpitch + 30 ) <= 45)
		{
			hP2 = sinpitch * 134.721936 + cospitch * 77.781746;
			hP = Round( hP2 );
			if (ballpitch < -30) Arc( hDC_ADI_ORBIT, -44, 112 - hP, 268, 112 + hP, 268, 112, -44, 112 );
			else Arc( hDC_ADI_ORBIT, -44, 112 - hP, 268, 112 + hP, -44, 112, 268, 112 );
			hP = 105 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI_ORBIT, 66, hP, "33", 2 );
			TextOut( hDC_ADI_ORBIT, 146, hP, "33", 2 );
		}
		// -60º
		if (fabs( ballpitch + 60 ) <= 45)
		{
			hP2 = sinpitch * 77.781746 + cospitch * 134.721936;
			hP = Round( hP2 );
			if (ballpitch < -60) Arc( hDC_ADI_ORBIT, -44, 112 - hP, 268, 112 + hP, 268, 112, -44, 112 );
			else Arc( hDC_ADI_ORBIT, -44, 112 - hP, 268, 112 + hP, -44, 112, 268, 112 );
			hP = 105 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI_ORBIT, 66, hP, "30", 2 );
			TextOut( hDC_ADI_ORBIT, 146, hP, "30", 2 );
		}
		// -90º
		if (fabs( ballpitch + 90 ) <= 45)
		{
			hP2 = 155.5634 * cospitch;
			hP = Round( hP2 );
			if (ballpitch < -90) Arc( hDC_ADI_ORBIT, -44, 112 - hP, 268, 112 + hP, 268, 112, -44, 112 );
			else Arc( hDC_ADI_ORBIT, -44, 112 - hP, 268, 112 + hP, -44, 112, 268, 112 );
			hP = 105 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI_ORBIT, 66, hP, "27", 2 );
			TextOut( hDC_ADI_ORBIT, 146, hP, "27", 2 );
		}
		// -120º
		if (fabs( ballpitch + 120 ) <= 45)
		{
			hP2 = (-sinpitch) * 77.781746 + cospitch * 134.721936;
			hP = Round( hP2 );
			if (ballpitch < -120) Arc( hDC_ADI_ORBIT, -44, 112 - hP, 268, 112 + hP, 268, 112, -44, 112 );
			else Arc( hDC_ADI_ORBIT, -44, 112 - hP, 268, 112 + hP, -44, 112, 268, 112 );
			hP = 105 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI_ORBIT, 66, hP, "24", 2 );
			TextOut( hDC_ADI_ORBIT, 146, hP, "24", 2 );
		}
		// -150º
		if (fabs( ballpitch + 150 ) <= 45)
		{
			hP2 = (-sinpitch) * 134.721936 + cospitch * 77.781746;
			hP = Round( hP2 );
			if (ballpitch < -150) Arc( hDC_ADI_ORBIT, -44, 112 - hP, 268, 112 + hP, 268, 112, -44, 112 );
			else Arc( hDC_ADI_ORBIT, -44, 112 - hP, 268, 112 + hP, -44, 112, 268, 112 );
			hP = 105 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI_ORBIT, 66, hP, "21", 2 );
			TextOut( hDC_ADI_ORBIT, 146, hP, "21", 2 );
		}

		// TODO yaw
		// HACK
		// "central plane"
		SelectObject( hDC_ADI_ORBIT, gdiWhiteBrush );
		SelectObject( hDC_ADI_ORBIT, gdiBlackPen );
		Rectangle( hDC_ADI_ORBIT, 108, 0, 116, 222 );
		MoveToEx( hDC_ADI_ORBIT, 112, 0, NULL );
		LineTo( hDC_ADI_ORBIT, 112, 222 );

		SelectObject( hDC_ADI_ORBIT, gdiBlackPen );
		// yaw line 30º (above horizon)
		MoveToEx( hDC_ADI_ORBIT, 190, 0, NULL );
		LineTo( hDC_ADI_ORBIT, 190, 114 + Round( 134.721936 * sinpitch ) );
		// yaw line 330º (above horizon)
		MoveToEx( hDC_ADI_ORBIT, 34, 0, NULL );
		LineTo( hDC_ADI_ORBIT, 34, 114 + Round( 134.721936 * sinpitch ) );
		SelectObject( hDC_ADI_ORBIT, gdiWhitePen );
		// yaw line 30º (below horizon)
		MoveToEx( hDC_ADI_ORBIT, 190, 222, NULL );
		LineTo( hDC_ADI_ORBIT, 190, 114 + Round( 134.721936 * sinpitch ) );
		// yaw line 330º (below horizon)
		MoveToEx( hDC_ADI_ORBIT, 34, 222, NULL );
		LineTo( hDC_ADI_ORBIT, 34, 114 + Round( 134.721936 * sinpitch ) );

		// TODO yaw labels

		// roll triangle
		SelectObject( hDC_ADI_ORBIT, gdiLightGreenPen );
		SelectObject( hDC_ADI_ORBIT, gdiLightGreenBrush );
		POINT tri[3];
		tri[0].x = 111;
		tri[0].y = 1;
		tri[1].x = 105;
		tri[1].y = 12;
		tri[2].x = 117;
		tri[2].y = 12;
		Polygon( hDC_ADI_ORBIT, tri, 3 );

		// clean up
		ModifyWorldTransform( hDC_ADI_ORBIT, &WTroll, MWT_IDENTITY );
		SetGraphicsMode( hDC_ADI_ORBIT, GM_COMPATIBLE );

		// digital RPY
		SetTextColor( hDC, CR_WHITE );
		char cbuf[8];
		sprintf_s( cbuf, 8, "%03.0f", digitalroll * DEG );
		TextOut( hDC, 393, 56, cbuf, strlen( cbuf ) );
		sprintf_s( cbuf, 8, "%03.0f", digitalpitch * DEG );
		TextOut( hDC, 393, 70, cbuf, strlen( cbuf ) );
		sprintf_s( cbuf, 8, "%03.0f", digitalyaw * DEG );
		TextOut( hDC, 393, 84, cbuf, strlen( cbuf ) );

		// copy ball
		BitBlt( hDC_ADI_ORBIT, 0, 0, 222, 222, hDC_ADIMASK_ORBIT, 0, 0, SRCAND );
		BitBlt( hDC, 146, 113, 220, 220, hDC_ADI_ORBIT, 1, 1, SRCPAINT );

		// flight director
		SelectObject( hDC, gdiBlackPen );
		SelectObject( hDC, gdiLightGreenBrush );
		POINT fd[18] = {{214,221},{214,225},{238,225},{243,235},{252,241},{260,241},{269,235},{274,225},{298,225},{298,221},{270,221},{270,225},{266,232},{259,237},{253,237},{246,232},{242,225},{242,221}};
		Polygon( hDC, fd, 18 );
		// center marker
		SelectObject( hDC, gdiLightGreenPen );
		Rectangle( hDC, 255, 191, 257, 255 );
		Rectangle( hDC, 224, 222, 288, 224 );
		return;
	}

	void MDU::ADI_ORBIT( oapi::Sketchpad2* skp, double sinpitch, double cospitch, double sinroll, double cosroll, double sinyaw, double cosyaw )
	{
		// center (256,223) r = 132
		// view r = 110, ball r = 110 * sqrt( 2 )
		// 90º pitch/yaw "FOV"

		double digitalpitch = atan2( sinpitch, cospitch );
		double digitalroll = atan2( sinroll, cosroll );
		double digitalyaw = atan2( sinyaw, cosyaw );

		if (digitalpitch < 0.0) digitalpitch += PI2;
		if (digitalroll < 0.0) digitalroll += PI2;
		if (digitalyaw < 0.0) digitalyaw += PI2;

		// draw ball mesh
		FMATRIX4 mat;
		int H = 446;
		int W = 512;

		// original
		/*
		double roll = -STS()->GetBank() * DEG;
		if (roll <= 0) roll += 360;
		double pitch = STS()->GetPitch() * DEG;
		if (pitch <= 0) pitch += 360;
		double yaw = STS()->GetSlipAngle() * DEG;
		if (yaw <= 0) yaw += 360;

		double croll = cos( roll * RAD );
		double sroll = sin( -roll * RAD );
		double cyaw = cos( yaw * RAD );
		double syaw = sin( yaw * RAD );
		double cpitch = cos( pitch * RAD );
		double spitch = sin( pitch * RAD );

		VECTOR3 xdir = _V( cyaw * croll, sroll, -croll * syaw );
		VECTOR3 zdir = _V( syaw * cpitch + sroll * cyaw * spitch, -croll * spitch, cpitch * cyaw - syaw * sroll * spitch );
		*/



		/*if (cospitch < 0.0)
		{
			sinroll = -sinroll;
		}*/
		//VECTOR3 xdir = _V( cosyaw * cosroll, sinroll, -cosroll * sinyaw );
		//VECTOR3 zdir = _V( sinyaw * cospitch + sinroll * cosyaw * sinpitch, -cosroll * sinpitch, cospitch * cosyaw - sinyaw * sinroll * sinpitch );

		VECTOR3 xdir = _V( cosyaw * cosroll, sinroll, -cosroll * sinyaw );
		VECTOR3 zdir = _V( sinyaw * cospitch + sinroll * cosyaw * sinpitch, -cosroll * sinpitch, cospitch * cosyaw - sinyaw * sinroll * sinpitch );
		if (cospitch < 0.0)
		{
			//xdir = -xdir;
			//zdir = -zdir;
		}
		//sprintf_s( oapiDebugString(), 255, "%.2f %.2f %.2f     %.2f %.2f %.2f", xdir.x, xdir.y, xdir.z, zdir.x, zdir.y, zdir.z );

		/*VECTOR3 cp = crossp (_V( 1,0,0), _V( 0,0,1));
		sprintf_s( oapiDebugString(), 255, "%.2f %.2f %.2f", cp.x, cp.y, cp.z );*/

		/*VECTOR3 xdir = _V( cosyaw * cosroll, -sinroll, -cosroll * sinyaw );
		VECTOR3 zdir = _V( sinyaw * cospitch - sinroll * cosyaw * sinpitch, -cosroll * sinpitch, cospitch * cosyaw + sinyaw * sinroll * sinpitch );*/

		// good roll, bad pitch, yaw?
		//VECTOR3 xdir = _V( cosyaw * cosroll, -sinroll, -cosroll * sinyaw );
		//VECTOR3 zdir = _V( sinyaw * cospitch + sinroll * cosyaw * sinpitch, cosroll * sinpitch, cospitch * cosyaw - sinyaw * sinroll * sinpitch );

		// bad pitch
		//VECTOR3 xdir = _V( cosyaw * cosroll, -sinroll, -cosroll * sinyaw );
		//VECTOR3 zdir = _V( -sinyaw * cospitch - sinroll * cosyaw * sinpitch, -cosroll * sinpitch, -cospitch * cosyaw + sinyaw * sinroll * sinpitch );

		// good pitch, roll?
		//VECTOR3 xdir = _V( cosyaw * cosroll, -sinroll, -cosroll * sinyaw );
		//VECTOR3 zdir = _V( sinyaw * cospitch - sinroll * cosyaw * sinpitch, -cosroll * sinpitch, cospitch * cosyaw + sinyaw * sinroll * sinpitch );

		//VECTOR3 xdir = _V( cosyaw * cosroll, -sinroll, -cosroll * sinyaw );
		// p,r,y   x,y,z(-x,z,-y)
		// 0,0,0 = 1,0,0
		// 0,90,0 = 0,-1,0
		// 0,0,90 = 0,0,-1
		// 0,45,45 = 0.5,-0.7,-0.5	-x,+y,+z
		//VECTOR3 zdir = _V( sinyaw * cospitch - sinroll * cosyaw * sinpitch, -cosroll * sinpitch, cospitch * cosyaw + sinyaw * sinroll * sinpitch );

		// a = pitch
		// b = roll
		// g = yaw
		//VECTOR3 zdir = _V( -sinyaw * cospitch + sinroll * cosyaw * sinpitch,	cosroll * sinpitch,	cospitch * cosyaw + sinyaw * sinroll * sinpitch );
		//VECTOR3 xdir = _V( cosyaw * cosroll,					-sinroll,		cosroll * sinyaw );

		// good (original)
		//VECTOR3 zdir = _V( sinyaw * cospitch - sinroll * cosyaw * sinpitch,	-cosroll * sinpitch,	cospitch * cosyaw + sinyaw * sinroll * sinpitch );
		//VECTOR3 xdir = _V( cosyaw * cosroll,					-sinroll,		-cosroll * sinyaw );


		// a1 = pitch
		// b2 = yaw
		// g3 = roll
		//VECTOR3 xdir = _V( cosyaw * cosroll,					-cosyaw * sinroll,					sinyaw );
		//VECTOR3 zdir = _V( sinpitch * sinroll - cospitch * cosroll * sinyaw,	cosroll * sinpitch + cospitch * sinyaw * sinroll,	cospitch * cosyaw );

		double c1 = cospitch;
		double s1 = sinpitch;
		
		double c2 = cosyaw;
		double s2 = sinyaw;
		
		double c3 = cosroll;
		double s3 = sinroll;

		// TB
		// x1y2z3
		//VECTOR3 xdir = _V( cosyaw * cosroll,					-cosyaw * sinroll,					-sinyaw );
		//VECTOR3 zdir = _V( -sinpitch * sinroll + cospitch * cosroll * sinyaw,	-cosroll * sinpitch - cospitch * sinyaw * sinroll,	cospitch * cosyaw );
		

		// E
		// horiz
		//VECTOR3 xdir = _V( c2,		s2 * s3,			c3 * s2 );
		//VECTOR3 zdir = _V( -c1 * s2,	c3 * s1 + c1 * c2 * s3,		c1 * c2 * c3 - s1 * s3	);



		STS()->D3D9()->WorldMatrix( &mat, _V( W / 2, H / 2, W + 110 ), xdir, zdir, 1.5556 );

		skp->SetWorldTransform( &mat );
		skp->SetPen( skpWhitePen );
		skp->DrawSketchMesh( hADIball, 0, 0 );
		skp->SetWorldTransform();

		// roll triangle
		skp->SetPen( skpLightGreenPen );
		skp->SetBrush( skpLightGreenBrush );
		oapi::IVECTOR2 tri[3];
		tri[0].x = (long)(256 + 110 * sinroll);
		tri[0].y = (long)(223 - 110 * cosroll);
		tri[1].x = (long)(256 - 6 * cosroll + 99 * sinroll);
		tri[1].y = (long)(223 - 6 * sinroll - 99 * cosroll);
		tri[2].x = (long)(256 + 6 * cosroll + 99 * sinroll);
		tri[2].y = (long)(223 + 6 * sinroll - 99 * cosroll);
		skp->Polygon( tri, 3 );

		// digital RPY
		skp->SetTextColor( CR_WHITE );
		char cbuf[8];
		sprintf_s( cbuf, 8, "%03.0f", digitalroll * DEG );
		skp->Text( 393, 56, cbuf, strlen( cbuf ) );
		sprintf_s( cbuf, 8, "%03.0f", digitalpitch * DEG );
		skp->Text( 393, 70, cbuf, strlen( cbuf ) );
		sprintf_s( cbuf, 8, "%03.0f", digitalyaw * DEG );
		skp->Text( 393, 84, cbuf, strlen( cbuf ) );

		// flight director
		skp->SetPen( skpBlackPen );
		oapi::IVECTOR2 fd[18] = {{214,221},{214,225},{238,225},{243,235},{252,241},{260,241},{269,235},{274,225},{298,225},{298,221},{270,221},{270,225},{266,232},{259,237},{253,237},{246,232},{242,225},{242,221}};
		skp->Polygon( fd, 18 );
		// center marker
		skp->SetPen( skpLightGreenPen );
		skp->Rectangle( 255, 191, 257, 255 );
		skp->Rectangle( 224, 222, 288, 224 );
		return;
	}

	void MDU::ADI_RATE_ORBIT( HDC hDC, unsigned short pitchrate, unsigned short rollrate, unsigned short yawrate )
	{
		POINT tri[3];

		// triangles
		SelectObject( hDC, gdiLightGreenPen );
		SelectObject( hDC, gdiLightGreenBrush );

		tri[0].x = 256 + Round( static_cast<short>(rollrate) * (89.0 / (4095 * 8)) );
		tri[0].y = 76;
		tri[1].x = tri[0].x + 10;
		tri[1].y = 58;
		tri[2].x = tri[0].x - 10;
		tri[2].y = 58;
		Polygon( hDC, tri, 3 );

		tri[0].x = 403;
		tri[0].y = 223 - Round( static_cast<short>(pitchrate) * (89.0 / (4095 * 8)) );
		tri[1].x = 421;
		tri[1].y = tri[0].y - 10;
		tri[2].x = 421;
		tri[2].y = tri[0].y + 10;
		Polygon( hDC, tri, 3 );

		tri[0].x = 256 + Round( static_cast<short>(yawrate) * (89.0 / (4095 * 8)) );
		tri[0].y = 370;
		tri[1].x = tri[0].x - 10;
		tri[1].y = 388;
		tri[2].x = tri[0].x + 10;
		tri[2].y = 388;
		Polygon( hDC, tri, 3 );
		return;
	}

	void MDU::ADI_RATE_ORBIT( oapi::Sketchpad2* skp, unsigned short pitchrate, unsigned short rollrate, unsigned short yawrate )
	{
		oapi::IVECTOR2 tri[3];

		// triangles
		skp->SetPen( skpLightGreenPen );
		skp->SetBrush( skpLightGreenBrush );

		tri[0].x = 256 + Round( static_cast<short>(rollrate) * (89.0 / (4095 * 8)) );
		tri[0].y = 76;
		tri[1].x = tri[0].x + 10;
		tri[1].y = 58;
		tri[2].x = tri[0].x - 10;
		tri[2].y = 58;
		skp->Polygon( tri, 3 );

		tri[0].x = 403;
		tri[0].y = 223 - Round( static_cast<short>(pitchrate) * (89.0 / (4095 * 8)) );
		tri[1].x = 421;
		tri[1].y = tri[0].y - 10;
		tri[2].x = 421;
		tri[2].y = tri[0].y + 10;
		skp->Polygon( tri, 3 );

		tri[0].x = 256 + Round( static_cast<short>(yawrate) * (89.0 / (4095 * 8)) );
		tri[0].y = 370;
		tri[1].x = tri[0].x - 10;
		tri[1].y = 388;
		tri[2].x = tri[0].x + 10;
		tri[2].y = 388;
		skp->Polygon( tri, 3 );
		return;
	}

	void MDU::ADI_ERROR_ORBIT( HDC hDC, unsigned short pitcherror, unsigned short rollerror, unsigned short yawerror )
	{
		double pos;

		// needles
		SelectObject( hDC, gdiMagentaPen );
		SelectObject( hDC, gdiMagentaBrush );

		pos = -(static_cast<short>(rollerror) * (50.0 / (4095 * 8)));
		Rectangle( hDC, 255 + Round( pos ), 224 - Round( sqrt( 15625 - (pos * pos) ) ), 257 + Round( pos ), 188 );

		pos = (static_cast<short>(pitcherror) * (50.0 / (4095 * 8)));
		Rectangle( hDC, 291, 222 + Round( pos ), 256 + Round( sqrt( 15625 - (pos * pos) ) ), 224 + Round( pos ) );

		pos = -(static_cast<short>(yawerror) * (50.0 / (4095 * 8)));
		Rectangle( hDC, 255 + Round( pos ), 258, 257 + Round( pos ), 223 + Round( sqrt( 15625 - (pos * pos) ) ) );
		return;
	}

	void MDU::ADI_ERROR_ORBIT( oapi::Sketchpad2* skp, unsigned short pitcherror, unsigned short rollerror, unsigned short yawerror )
	{
		double pos;

		// needles
		skp->SetPen( skpMagentaPen );
		skp->SetBrush( skpMagentaBrush );

		pos = -(static_cast<short>(rollerror) * (50.0 / (4095 * 8)));
		skp->Rectangle( 255 + Round( pos ), 224 - Round( sqrt( 15625 - (pos * pos) ) ), 257 + Round( pos ), 188 );

		pos = (static_cast<short>(pitcherror) * (50.0 / (4095 * 8)));
		skp->Rectangle( 291, 222 + Round( pos ), 256 + Round( sqrt( 15625 - (pos * pos) ) ), 224 + Round( pos ) );

		pos = -(static_cast<short>(yawerror) * (50.0 / (4095 * 8)));
		skp->Rectangle( 255 + Round( pos ), 258, 257 + Round( pos ), 223 + Round( sqrt( 15625 - (pos * pos) ) ) );
		return;
	}
}

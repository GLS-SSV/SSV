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
2022/10/05   GLS
2022/12/17   GLS
2023/10/22   GLS
2023/10/29   GLS
2024/12/30   GLS
2025/01/23   GLS
********************************************/
#include "MDU.h"
#include "../Atlantis.h"
#include "../dps/IDP.h"
#include <MathSSV.h>
#include <gcCoreAPI.h>


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

		SelectObject( hDC, gdiSSVBFont_h24w14 );

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

	void MDU::ORBITPFD( oapi::Sketchpad* skp )
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

		skp->SetFont( skpSSVBFont_h24w14 );

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
		TextOut( hDC, 758, 112, "R", 1 );
		TextOut( hDC, 758, 140, "P", 1 );
		TextOut( hDC, 758, 168, "Y", 1 );

		TextOut( hDC, 506, 122, "0", 1 );
		TextOut( hDC, 818, 432, "0", 1 );
		TextOut( hDC, 506, 742, "0", 1 );

		SelectObject( hDC, gdiWhitePen );
		::Ellipse( hDC, 248, 182, 776, 710 );

		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiLightGrayBrush );
		POINT diamond[4];
		diamond[0].x = 512;
		diamond[0].y = 198;
		diamond[1].x = 522;
		diamond[1].y = 212;
		diamond[2].x = 512;
		diamond[2].y = 226;
		diamond[3].x = 502;
		diamond[3].y = 212;
		Polygon( hDC, diamond, 4 );// top
		//diamond[0].x = 512;
		diamond[0].y = 666;
		//diamond[1].x = 522;
		diamond[1].y = 680;
		//diamond[2].x = 512;
		diamond[2].y = 694;
		//diamond[3].x = 502;
		diamond[3].y = 680;
		Polygon( hDC, diamond, 4 );// bottom
		diamond[0].x = 746;
		diamond[0].y = 436;
		diamond[1].x = 760;
		diamond[1].y = 446;
		diamond[2].x = 746;
		diamond[2].y = 456;
		diamond[3].x = 732;
		diamond[3].y = 446;
		Polygon( hDC, diamond, 4 );// right
		diamond[0].x = 278;
		//diamond[0].y = 436;
		diamond[1].x = 292;
		//diamond[1].y = 446;
		diamond[2].x = 278;
		//diamond[2].y = 456;
		diamond[3].x = 264;
		//diamond[3].y = 446;
		Polygon( hDC, diamond, 4 );// left

		// rate scales
		// top scale
		MoveToEx( hDC, 334, 152, NULL );
		LineTo( hDC, 690, 152 );
		MoveToEx( hDC, 334, 152, NULL );
		LineTo( hDC, 334, 172 );
		MoveToEx( hDC, 370, 152, NULL );
		LineTo( hDC, 370, 162 );
		MoveToEx( hDC, 406, 152, NULL );
		LineTo( hDC, 406, 162 );
		MoveToEx( hDC, 440, 152, NULL );
		LineTo( hDC, 440, 162 );
		MoveToEx( hDC, 476, 152, NULL );
		LineTo( hDC, 476, 162 );
		MoveToEx( hDC, 512, 152, NULL );
		LineTo( hDC, 512, 172 );
		MoveToEx( hDC, 548, 152, NULL );
		LineTo( hDC, 548, 162 );
		MoveToEx( hDC, 584, 152, NULL );
		LineTo( hDC, 584, 162 );
		MoveToEx( hDC, 618, 152, NULL );
		LineTo( hDC, 618, 162 );
		MoveToEx( hDC, 654, 152, NULL );
		LineTo( hDC, 654, 162 );
		MoveToEx( hDC, 690, 152, NULL );
		LineTo( hDC, 690, 172 );

		// side scale
		MoveToEx( hDC, 806, 268, NULL );
		LineTo( hDC, 806, 624 );
		MoveToEx( hDC, 806, 268, NULL );
		LineTo( hDC, 786, 268 );
		MoveToEx( hDC, 806, 304, NULL );
		LineTo( hDC, 796, 304 );
		MoveToEx( hDC, 806, 340, NULL );
		LineTo( hDC, 796, 340 );
		MoveToEx( hDC, 806, 374, NULL );
		LineTo( hDC, 796, 374 );
		MoveToEx( hDC, 806, 410, NULL );
		LineTo( hDC, 796, 410 );
		MoveToEx( hDC, 806, 446, NULL );
		LineTo( hDC, 786, 446 );
		MoveToEx( hDC, 806, 482, NULL );
		LineTo( hDC, 796, 482 );
		MoveToEx( hDC, 806, 518, NULL );
		LineTo( hDC, 796, 518 );
		MoveToEx( hDC, 806, 552, NULL );
		LineTo( hDC, 796, 552 );
		MoveToEx( hDC, 806, 588, NULL );
		LineTo( hDC, 796, 588 );
		MoveToEx( hDC, 806, 624, NULL );
		LineTo( hDC, 786, 624 );

		// bottom scale
		MoveToEx( hDC, 334, 740, NULL );
		LineTo( hDC, 690, 740 );
		MoveToEx( hDC, 334, 740, NULL );
		LineTo( hDC, 334, 720 );
		MoveToEx( hDC, 370, 740, NULL );
		LineTo( hDC, 370, 730 );
		MoveToEx( hDC, 406, 740, NULL );
		LineTo( hDC, 406, 730 );
		MoveToEx( hDC, 440, 740, NULL );
		LineTo( hDC, 440, 730 );
		MoveToEx( hDC, 476, 740, NULL );
		LineTo( hDC, 476, 730 );
		MoveToEx( hDC, 512, 740, NULL );
		LineTo( hDC, 512, 720 );
		MoveToEx( hDC, 548, 740, NULL );
		LineTo( hDC, 548, 730 );
		MoveToEx( hDC, 584, 740, NULL );
		LineTo( hDC, 584, 730 );
		MoveToEx( hDC, 618, 740, NULL );
		LineTo( hDC, 618, 730 );
		MoveToEx( hDC, 654, 740, NULL );
		LineTo( hDC, 654, 730 );
		MoveToEx( hDC, 690, 740, NULL );
		LineTo( hDC, 690, 720 );

		// roll lines
		MoveToEx( hDC, 492, 218, NULL );// 5º/185º
		LineTo( hDC, 532, 674 );
		MoveToEx( hDC, 472, 222, NULL );// 10º/190º
		LineTo( hDC, 552, 670 );
		MoveToEx( hDC, 452, 226, NULL );// 15º/195º
		LineTo( hDC, 572, 666 );
		MoveToEx( hDC, 434, 232, NULL );// 20º/200º
		LineTo( hDC, 590, 660 );
		MoveToEx( hDC, 416, 240, NULL );// 25º/205º
		LineTo( hDC, 608, 652 );

		MoveToEx( hDC, 382, 260, NULL );// 35º/215º
		LineTo( hDC, 642, 632 );
		MoveToEx( hDC, 366, 272, NULL );// 40º/220º
		LineTo( hDC, 658, 620 );
		MoveToEx( hDC, 350, 284, NULL );// 45º/225º
		LineTo( hDC, 674, 608 );
		MoveToEx( hDC, 338, 300, NULL );// 50º/230º
		LineTo( hDC, 686, 592 );
		MoveToEx( hDC, 326, 316, NULL );// 55º/235º
		LineTo( hDC, 698, 576 );

		MoveToEx( hDC, 306, 350, NULL );// 65º/245º
		LineTo( hDC, 718, 542 );
		MoveToEx( hDC, 298, 368, NULL );// 70º/250º
		LineTo( hDC, 726, 524 );
		MoveToEx( hDC, 292, 386, NULL );// 75º/255º
		LineTo( hDC, 732, 506 );
		MoveToEx( hDC, 288, 406, NULL );// 80º/260º
		LineTo( hDC, 736, 486 );
		MoveToEx( hDC, 284, 426, NULL );// 85º/265º
		LineTo( hDC, 740, 466 );

		MoveToEx( hDC, 284, 466, NULL );// 95º/275º
		LineTo( hDC, 740, 426 );
		MoveToEx( hDC, 288, 486, NULL );// 100º/280º
		LineTo( hDC, 736, 406 );
		MoveToEx( hDC, 292, 506, NULL );// 105º/285º
		LineTo( hDC, 732, 386 );
		MoveToEx( hDC, 298, 524, NULL );// 110º/290º
		LineTo( hDC, 726, 368 );
		MoveToEx( hDC, 306, 542, NULL );// 115º/295º
		LineTo( hDC, 718, 350 );

		MoveToEx( hDC, 326, 576, NULL );// 125º/305º
		LineTo( hDC, 698, 316 );
		MoveToEx( hDC, 338, 592, NULL );// 130º/310º
		LineTo( hDC, 686, 300 );
		MoveToEx( hDC, 350, 608, NULL );// 135º/315º
		LineTo( hDC, 674, 284 );
		MoveToEx( hDC, 366, 620, NULL );// 140º/320º
		LineTo( hDC, 658, 272 );
		MoveToEx( hDC, 382, 632, NULL );// 145º/325º
		LineTo( hDC, 642, 260 );

		MoveToEx( hDC, 416, 652, NULL );// 155º/335º
		LineTo( hDC, 608, 240 );
		MoveToEx( hDC, 434, 660, NULL );// 160º/340º
		LineTo( hDC, 590, 232 );
		MoveToEx( hDC, 452, 666, NULL );// 165º/345º
		LineTo( hDC, 572, 226 );
		MoveToEx( hDC, 472, 670, NULL );// 170º/350º
		LineTo( hDC, 552, 222 );
		MoveToEx( hDC, 492, 674, NULL );// 175º/355º
		LineTo( hDC, 532, 218 );
		SelectObject( hDC, gdiLightGrayThickPen );
		MoveToEx( hDC, 394, 242, NULL );// 30º/210º
		LineTo( hDC, 630, 650 );
		MoveToEx( hDC, 308, 328, NULL );// 60º/240º
		LineTo( hDC, 716, 564 );
		MoveToEx( hDC, 308, 564, NULL );// 120º/300º
		LineTo( hDC, 716, 328 );
		MoveToEx( hDC, 394, 650, NULL );// 150º/330º
		LineTo( hDC, 630, 242 );

		// cover center for ADI SRCPAINT
		SelectObject( hDC, GetStockObject( BLACK_BRUSH ) );
		SelectObject( hDC, GetStockObject( BLACK_PEN ) );
		::Ellipse( hDC, 292, 226, 732, 666 );

		TextOut( hDC, 634, 230, "33", 2 );
		TextOut( hDC, 702, 300, "30", 2 );
		TextOut( hDC, 702, 566, "24", 2 );
		TextOut( hDC, 634, 636, "21", 2 );
		TextOut( hDC, 362, 636, "15", 2 );
		TextOut( hDC, 296, 564, "12", 2 );
		TextOut( hDC, 296, 298, "06", 2 );
		TextOut( hDC, 362, 230, "03", 2 );

		// att needles
		// top scale
		SelectObject( hDC, gdiMagentaPen );
		SelectObject( hDC, gdiMagentaBrush );
		Arc( hDC, 262, 196, 762, 696, 612, 216, 412, 216 );
		MoveToEx( hDC, 412, 218, NULL );
		LineTo( hDC, 412, 228 );
		MoveToEx( hDC, 432, 212, NULL );
		LineTo( hDC, 432, 222 );
		MoveToEx( hDC, 452, 206, NULL );
		LineTo( hDC, 452, 216 );
		MoveToEx( hDC, 472, 202, NULL );
		LineTo( hDC, 472, 212 );
		MoveToEx( hDC, 492, 200, NULL );
		LineTo( hDC, 492, 210 );
		MoveToEx( hDC, 512, 198, NULL );
		LineTo( hDC, 512, 208 );
		MoveToEx( hDC, 532, 200, NULL );
		LineTo( hDC, 532, 210 );
		MoveToEx( hDC, 552, 202, NULL );
		LineTo( hDC, 552, 212 );
		MoveToEx( hDC, 572, 206, NULL );
		LineTo( hDC, 572, 218 );
		MoveToEx( hDC, 592, 212, NULL );
		LineTo( hDC, 592, 222 );
		MoveToEx( hDC, 612, 218, NULL );
		LineTo( hDC, 612, 228 );

		// side scale
		Arc( hDC, 262, 196, 762, 696, 742, 546, 742, 346 );
		MoveToEx( hDC, 740, 346, NULL );
		LineTo( hDC, 730, 346 );
		MoveToEx( hDC, 746, 366, NULL );
		LineTo( hDC, 736, 366 );
		MoveToEx( hDC, 752, 386, NULL );
		LineTo( hDC, 742, 386 );
		MoveToEx( hDC, 756, 406, NULL );
		LineTo( hDC, 746, 406 );
		MoveToEx( hDC, 758, 426, NULL );
		LineTo( hDC, 748, 426 );
		MoveToEx( hDC, 760, 446, NULL );
		LineTo( hDC, 750, 446 );
		MoveToEx( hDC, 758, 466, NULL );
		LineTo( hDC, 748, 466 );
		MoveToEx( hDC, 756, 486, NULL );
		LineTo( hDC, 746, 486 );
		MoveToEx( hDC, 752, 506, NULL );
		LineTo( hDC, 742, 506 );
		MoveToEx( hDC, 746, 526, NULL );
		LineTo( hDC, 736, 526 );
		MoveToEx( hDC, 740, 546, NULL );
		LineTo( hDC, 730, 546 );

		// bottom scale
		Arc( hDC, 262, 196, 762, 696, 412, 676, 612, 676 );
		MoveToEx( hDC, 412, 672, NULL );
		LineTo( hDC, 412, 662 );
		MoveToEx( hDC, 432, 678, NULL );
		LineTo( hDC, 432, 668 );
		MoveToEx( hDC, 452, 684, NULL );
		LineTo( hDC, 452, 674 );
		MoveToEx( hDC, 472, 688, NULL );
		LineTo( hDC, 472, 678 );
		MoveToEx( hDC, 492, 690, NULL );
		LineTo( hDC, 492, 680 );
		MoveToEx( hDC, 512, 692, NULL );
		LineTo( hDC, 512, 682 );
		MoveToEx( hDC, 532, 690, NULL );
		LineTo( hDC, 532, 680 );
		MoveToEx( hDC, 552, 688, NULL );
		LineTo( hDC, 552, 678 );
		MoveToEx( hDC, 572, 684, NULL );
		LineTo( hDC, 572, 674 );
		MoveToEx( hDC, 592, 678, NULL );
		LineTo( hDC, 592, 668 );
		MoveToEx( hDC, 612, 672, NULL );
		LineTo( hDC, 612, 662 );
		return;
	}

	void MDU::ADI_STATIC_ORBIT( oapi::Sketchpad* skp )
	{
		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Text( 758, 112, "R", 1 );
		skp->Text( 758, 140, "P", 1 );
		skp->Text( 758, 168, "Y", 1 );

		skp->Text( 506, 122, "0", 1 );
		skp->Text( 818, 432, "0", 1 );
		skp->Text( 506, 742, "0", 1 );

		skp->SetPen( skpWhitePen );
		skp->Ellipse( 248, 182, 776, 710 );

		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpLightGrayBrush );
		oapi::IVECTOR2 diamond[4];
		diamond[0].x = 512;
		diamond[0].y = 198;
		diamond[1].x = 522;
		diamond[1].y = 212;
		diamond[2].x = 512;
		diamond[2].y = 226;
		diamond[3].x = 502;
		diamond[3].y = 212;
		skp->Polygon( diamond, 4 );// top
		//diamond[0].x = 512;
		diamond[0].y = 666;
		//diamond[1].x = 522;
		diamond[1].y = 680;
		//diamond[2].x = 512;
		diamond[2].y = 694;
		//diamond[3].x = 502;
		diamond[3].y = 680;
		skp->Polygon( diamond, 4 );// bottom
		diamond[0].x = 746;
		diamond[0].y = 436;
		diamond[1].x = 760;
		diamond[1].y = 446;
		diamond[2].x = 746;
		diamond[2].y = 456;
		diamond[3].x = 732;
		diamond[3].y = 446;
		skp->Polygon( diamond, 4 );// right
		diamond[0].x = 278;
		//diamond[0].y = 436;
		diamond[1].x = 292;
		//diamond[1].y = 446;
		diamond[2].x = 278;
		//diamond[2].y = 456;
		diamond[3].x = 264;
		//diamond[3].y = 446;
		skp->Polygon( diamond, 4 );// left

		// rate scales
		// top scale
		skp->Line( 334, 152, 690, 152 );
		skp->Line( 334, 152, 334, 172 );
		skp->Line( 370, 152, 370, 162 );
		skp->Line( 406, 152, 406, 162 );
		skp->Line( 440, 152, 440, 162 );
		skp->Line( 476, 152, 476, 162 );
		skp->Line( 512, 152, 512, 172 );
		skp->Line( 548, 152, 548, 162 );
		skp->Line( 584, 152, 584, 162 );
		skp->Line( 618, 152, 618, 162 );
		skp->Line( 654, 152, 654, 162 );
		skp->Line( 690, 152, 690, 172 );

		// side scale
		skp->Line( 806, 268, 806, 624 );
		skp->Line( 806, 268, 786, 268 );
		skp->Line( 806, 304, 796, 304 );
		skp->Line( 806, 340, 796, 340 );
		skp->Line( 806, 374, 796, 374 );
		skp->Line( 806, 410, 796, 410 );
		skp->Line( 806, 446, 786, 446 );
		skp->Line( 806, 482, 796, 482 );
		skp->Line( 806, 518, 796, 518 );
		skp->Line( 806, 552, 796, 552 );
		skp->Line( 806, 588, 796, 588 );
		skp->Line( 806, 624, 786, 624 );

		// bottom scale
		skp->Line( 334, 740, 690, 740 );
		skp->Line( 334, 740, 334, 720 );
		skp->Line( 370, 740, 370, 730 );
		skp->Line( 406, 740, 406, 730 );
		skp->Line( 440, 740, 440, 730 );
		skp->Line( 476, 740, 476, 730 );
		skp->Line( 512, 740, 512, 720 );
		skp->Line( 548, 740, 548, 730 );
		skp->Line( 584, 740, 584, 730 );
		skp->Line( 618, 740, 618, 730 );
		skp->Line( 654, 740, 654, 730 );
		skp->Line( 690, 740, 690, 720 );

		// roll lines
		skp->Line( 492, 218, 532, 674 );// 5º/185º
		skp->Line( 472, 222, 552, 670 );// 10º/190º
		skp->Line( 452, 226, 572, 666 );// 15º/195º
		skp->Line( 434, 232, 590, 660 );// 20º/200º
		skp->Line( 416, 240, 608, 652 );// 25º/205º

		skp->Line( 382, 260, 642, 632 );// 35º/215º
		skp->Line( 366, 272, 658, 620 );// 40º/220º
		skp->Line( 350, 284, 674, 608 );// 45º/225º
		skp->Line( 338, 300, 686, 592 );// 50º/230º
		skp->Line( 326, 316, 698, 576 );// 55º/235º

		skp->Line( 306, 350, 718, 542 );// 65º/245º
		skp->Line( 298, 368, 726, 524 );// 70º/250º
		skp->Line( 292, 386, 732, 506 );// 75º/255º
		skp->Line( 288, 406, 736, 486 );// 80º/260º
		skp->Line( 284, 426, 740, 466 );// 85º/265º

		skp->Line( 284, 466, 740, 426 );// 95º/275º
		skp->Line( 288, 486, 736, 406 );// 100º/280º
		skp->Line( 292, 506, 732, 386 );// 105º/285º
		skp->Line( 298, 524, 726, 368 );// 110º/290º
		skp->Line( 306, 542, 718, 350 );// 115º/295º

		skp->Line( 326, 576, 698, 316 );// 125º/305º
		skp->Line( 338, 592, 686, 300 );// 130º/310º
		skp->Line( 350, 608, 674, 284 );// 135º/315º
		skp->Line( 366, 620, 658, 272 );// 140º/320º
		skp->Line( 382, 632, 642, 260 );// 145º/325º

		skp->Line( 416, 652, 608, 240 );// 155º/335º
		skp->Line( 434, 660, 590, 232 );// 160º/340º
		skp->Line( 452, 666, 572, 226 );// 165º/345º
		skp->Line( 472, 670, 552, 222 );// 170º/350º
		skp->Line( 492, 674, 532, 218 );// 175º/355º

		skp->SetPen( skpLightGrayThickPen );
		skp->Line( 394, 242, 630, 650 );// 30º/210º
		skp->Line( 308, 328, 716, 564 );// 60º/240º
		skp->Line( 308, 564, 716, 328 );// 120º/300º
		skp->Line( 394, 650, 630, 242 );// 150º/330º

		// cover center for ADI SRCPAINT
		skp->SetBrush( _skpBlackBrush );
		skp->SetPen( _skpBlackPen );
		skp->Ellipse( 292, 226, 732, 666 );

		skp->Text( 634, 230, "33", 2 );
		skp->Text( 702, 300, "30", 2 );
		skp->Text( 702, 566, "24", 2 );
		skp->Text( 634, 636, "21", 2 );
		skp->Text( 362, 636, "15", 2 );
		skp->Text( 296, 564, "12", 2 );
		skp->Text( 296, 298, "06", 2 );
		skp->Text( 362, 230, "03", 2 );

		// att needles
		// top scale
		skp->SetPen( skpMagentaPen );
		skp->SetBrush( skpMagentaBrush );
		//Arc( hDC, 262, 196, 762, 696, 612, 216, 412, 216 );
		// HACK makeshift arc
		skp->Line( 412, 218, 432, 212 );
		skp->Line( 432, 212, 452, 206 );
		skp->Line( 452, 206, 472, 202 );
		skp->Line( 472, 202, 492, 200 );
		skp->Line( 492, 200, 512, 198 );
		skp->Line( 512, 198, 532, 200 );
		skp->Line( 532, 200, 552, 202 );
		skp->Line( 552, 202, 572, 206 );
		skp->Line( 572, 206, 592, 212 );
		skp->Line( 592, 212, 612, 218 );

		skp->Line( 412, 218, 412, 228 );
		skp->Line( 432, 212, 432, 222 );
		skp->Line( 452, 206, 452, 216 );
		skp->Line( 472, 202, 472, 212 );
		skp->Line( 492, 200, 492, 210 );
		skp->Line( 512, 198, 512, 208 );
		skp->Line( 532, 200, 532, 210 );
		skp->Line( 552, 202, 552, 212 );
		skp->Line( 572, 206, 572, 218 );
		skp->Line( 592, 212, 592, 222 );
		skp->Line( 612, 218, 612, 228 );

		// side scale
		//Arc( hDC, 262, 196, 762, 696, 742, 546, 742, 346 );
		// HACK makeshift arc
		skp->Line( 740, 346, 746, 366 );
		skp->Line( 746, 366, 752, 386 );
		skp->Line( 752, 386, 756, 406 );
		skp->Line( 756, 406, 758, 426 );
		skp->Line( 758, 426, 760, 446 );
		skp->Line( 760, 446, 758, 466 );
		skp->Line( 758, 466, 756, 486 );
		skp->Line( 756, 486, 752, 506 );
		skp->Line( 752, 506, 746, 526 );
		skp->Line( 746, 526, 740, 546 );

		skp->Line( 740, 346, 730, 346 );
		skp->Line( 746, 366, 736, 366 );
		skp->Line( 752, 386, 742, 386 );
		skp->Line( 756, 406, 746, 406 );
		skp->Line( 758, 426, 748, 426 );
		skp->Line( 760, 446, 750, 446 );
		skp->Line( 758, 466, 748, 466 );
		skp->Line( 756, 486, 746, 486 );
		skp->Line( 752, 506, 742, 506 );
		skp->Line( 746, 526, 736, 526 );
		skp->Line( 740, 546, 730, 546 );

		// bottom scale
		//Arc( hDC, 262, 196, 762, 696, 412, 676, 612, 676 );
		// HACK makeshift arc
		skp->Line( 412, 672, 432, 678 );
		skp->Line( 432, 678, 452, 684 );
		skp->Line( 452, 684, 472, 688 );
		skp->Line( 472, 688, 492, 690 );
		skp->Line( 492, 690, 512, 692 );
		skp->Line( 512, 692, 532, 690 );
		skp->Line( 532, 690, 552, 688 );
		skp->Line( 552, 688, 572, 684 );
		skp->Line( 572, 684, 592, 678 );
		skp->Line( 592, 678, 612, 672 );

		skp->Line( 412, 672, 412, 662 );
		skp->Line( 432, 678, 432, 668 );
		skp->Line( 452, 684, 452, 674 );
		skp->Line( 472, 688, 472, 678 );
		skp->Line( 492, 690, 492, 680 );
		skp->Line( 512, 692, 512, 682 );
		skp->Line( 532, 690, 532, 680 );
		skp->Line( 552, 688, 552, 678 );
		skp->Line( 572, 684, 572, 674 );
		skp->Line( 592, 678, 592, 668 );
		skp->Line( 612, 672, 612, 662 );
		return;
	}

	void MDU::ADI_ORBIT( HDC hDC, double sinpitch, double cospitch, double sinroll, double cosroll, double sinyaw, double cosyaw )
	{
		// center (512,446) r = 264
		// view r = 220, ball r = 220 * sqrt( 2 )
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
		WTroll.eM12 = -(FLOAT)sinroll;
		WTroll.eM21 = -WTroll.eM12;
		WTroll.eM22 = WTroll.eM11;
		WTroll.eDx = (FLOAT)(222 * (1 - WTroll.eM11 - WTroll.eM21));
		WTroll.eDy = (FLOAT)(222 * (1 - WTroll.eM11 + WTroll.eM21));
		SetGraphicsMode( hDC_ADI_ORBIT, GM_ADVANCED );
		SetWorldTransform( hDC_ADI_ORBIT, &WTroll );

		// 0º pitch line/labels
		int hP;
		double hP2;
		SetTextColor( hDC_ADI_ORBIT, CR_BLACK );
		SetBkColor( hDC_ADI_ORBIT, CR_WHITE );
		if (fabs( ballpitch ) <= 45)
		{
			hP = Round( 311.127 * sinpitch );
			if (ballpitch < 0)
			{
				SelectObject( hDC_ADI_ORBIT, gdiWhiteBrush );
				SelectObject( hDC_ADI_ORBIT, gdiWhitePen );
				Rectangle( hDC_ADI_ORBIT, 0, 0, 448, 224 );
				SelectObject( hDC_ADI_ORBIT, gdiDarkGrayBrush );
				SelectObject( hDC_ADI_ORBIT, gdiDarkGrayPen );
				Chord( hDC_ADI_ORBIT, -88, 224 - hP, 536, 224 + hP, 536, 224, -88, 224 );
				Rectangle( hDC_ADI_ORBIT, 0, 224, 448, 448 );
			}
			else
			{
				SelectObject( hDC_ADI_ORBIT, gdiDarkGrayBrush );
				SelectObject( hDC_ADI_ORBIT, gdiDarkGrayPen );
				Rectangle( hDC_ADI_ORBIT, 0, 224, 448, 448 );
				SelectObject( hDC_ADI_ORBIT, gdiWhiteBrush );
				SelectObject( hDC_ADI_ORBIT, gdiWhitePen );
				Chord( hDC_ADI_ORBIT, -88, 224 - hP, 536, 224 + hP, -88, 224, 536, 224 );
				Rectangle( hDC_ADI_ORBIT, 0, 0, 448, 224 );
			}
			hP = 220 + Round( 300.525588 * sinpitch );
			TextOut( hDC_ADI_ORBIT, 140, hP, "0", 1 );
			TextOut( hDC_ADI_ORBIT, 300, hP, "0", 1 );
		}
		else if (ballpitch > 0)
		{
			SelectObject( hDC_ADI_ORBIT, gdiWhiteBrush );
			Rectangle( hDC_ADI_ORBIT, -4, -4, 448, 448 );
		}
		else
		{
			SelectObject( hDC_ADI_ORBIT, gdiDarkGrayBrush );
			Rectangle( hDC_ADI_ORBIT, -4, -4, 448, 448 );
		}

		// pitch lines/labels for +30º/+60º/+90º/+120º/+150º
		SelectObject( hDC_ADI_ORBIT, gdiBlackPen );
		// +30º
		if (fabs( ballpitch - 30 ) <= 45)
		{
			hP2 = sinpitch * 269.443872 - cospitch * 155.563492;//hP = 277.184 * sin( (pitch - 30) * RAD );
			hP = Round( hP2 );
			if (ballpitch < 30) Arc( hDC_ADI_ORBIT, -88, 224 - hP, 536, 224 + hP, 536, 224, -88, 224 );
			else Arc( hDC_ADI_ORBIT, -88, 224 - hP, 536, 224 + hP, -88, 224, 536, 224 );
			hP = 210 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI_ORBIT, 140, hP, "3", 1 );
			TextOut( hDC_ADI_ORBIT, 300, hP, "3", 1 );
		}
		// +60º
		if (fabs( ballpitch - 60 ) <= 45)
		{
			hP2 = sinpitch * 155.563492 - cospitch * 269.443872;
			hP = Round( hP2 );
			if (ballpitch < 60) Arc( hDC_ADI_ORBIT, -88, 224 - hP, 536, 224 + hP, 536, 224, -88, 224 );
			else Arc( hDC_ADI_ORBIT, -88, 224 - hP, 536, 224 + hP, -88, 224, 536, 224 );
			hP = 210 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI_ORBIT, 140, hP, "6", 1 );
			TextOut( hDC_ADI_ORBIT, 300, hP, "6", 1 );
		}
		// +90º
		if (fabs( ballpitch - 90 ) <= 45)
		{
			hP2 = 311.1268 * (-cospitch);
			hP = Round( hP2 );
			if (ballpitch < 90) Arc( hDC_ADI_ORBIT, -88, 224 - hP, 536, 224 + hP, 536, 224, -88, 224 );
			else Arc( hDC_ADI_ORBIT, -88, 224 - hP, 536, 224 + hP, -88, 224, 536, 224 );
			hP = 210 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI_ORBIT, 140, hP, "9", 1 );
			TextOut( hDC_ADI_ORBIT, 300, hP, "9", 1 );
		}
		// +120º
		if (fabs( ballpitch - 120 ) <= 45)
		{
			hP2 = (-sinpitch) * 155.563492 - cospitch * 269.443872;
			hP = Round( hP2 );
			if (ballpitch < 120) Arc( hDC_ADI_ORBIT, -88, 224 - hP, 536, 224 + hP, 536, 224, -88, 224 );
			else Arc( hDC_ADI_ORBIT, -88, 224 - hP, 536, 224 + hP, -88, 224, 536, 224 );
			hP = 210 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI_ORBIT, 132, hP, "12", 2 );
			TextOut( hDC_ADI_ORBIT, 292, hP, "12", 2 );
		}
		// +150º
		if (fabs( ballpitch - 150 ) <= 45)
		{
			hP2 = (-sinpitch) * 269.443872 - cospitch * 155.563492;
			hP = Round( hP2 );
			if (ballpitch < 150) Arc( hDC_ADI_ORBIT, -88, 224 - hP, 536, 224 + hP, 536, 224, -88, 224 );
			else Arc( hDC_ADI_ORBIT, -88, 224 - hP, 536, 224 + hP, -88, 224, 536, 224 );
			hP = 210 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI_ORBIT, 132, hP, "15", 2 );
			TextOut( hDC_ADI_ORBIT, 292, hP, "15", 2 );
		}

		// pitch lines/labels for -30º/-60º/-90º/-120º/-150º
		SelectObject( hDC_ADI_ORBIT, gdiWhitePen );
		SetTextColor( hDC_ADI_ORBIT, CR_WHITE );
		SetBkColor( hDC_ADI_ORBIT, CR_DARK_GRAY );
		// -30º
		if (fabs( ballpitch + 30 ) <= 45)
		{
			hP2 = sinpitch * 269.443872 + cospitch * 155.563492;
			hP = Round( hP2 );
			if (ballpitch < -30) Arc( hDC_ADI_ORBIT, -88, 224 - hP, 536, 224 + hP, 536, 224, -88, 224 );
			else Arc( hDC_ADI_ORBIT, -88, 224 - hP, 536, 224 + hP, -88, 224, 536, 224 );
			hP = 210 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI_ORBIT, 132, hP, "33", 2 );
			TextOut( hDC_ADI_ORBIT, 292, hP, "33", 2 );
		}
		// -60º
		if (fabs( ballpitch + 60 ) <= 45)
		{
			hP2 = sinpitch * 155.563492 + cospitch * 269.443872;
			hP = Round( hP2 );
			if (ballpitch < -60) Arc( hDC_ADI_ORBIT, -88, 224 - hP, 536, 224 + hP, 536, 224, -88, 224 );
			else Arc( hDC_ADI_ORBIT, -88, 224 - hP, 536, 224 + hP, -88, 224, 536, 224 );
			hP = 210 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI_ORBIT, 132, hP, "30", 2 );
			TextOut( hDC_ADI_ORBIT, 292, hP, "30", 2 );
		}
		// -90º
		if (fabs( ballpitch + 90 ) <= 45)
		{
			hP2 = 311.1268 * cospitch;
			hP = Round( hP2 );
			if (ballpitch < -90) Arc( hDC_ADI_ORBIT, -88, 224 - hP, 536, 224 + hP, 536, 224, -88, 224 );
			else Arc( hDC_ADI_ORBIT, -88, 224 - hP, 536, 224 + hP, -88, 224, 536, 224 );
			hP = 210 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI_ORBIT, 132, hP, "27", 2 );
			TextOut( hDC_ADI_ORBIT, 292, hP, "27", 2 );
		}
		// -120º
		if (fabs( ballpitch + 120 ) <= 45)
		{
			hP2 = (-sinpitch) * 155.563492 + cospitch * 269.443872;
			hP = Round( hP2 );
			if (ballpitch < -120) Arc( hDC_ADI_ORBIT, -88, 224 - hP, 536, 224 + hP, 536, 224, -88, 224 );
			else Arc( hDC_ADI_ORBIT, -88, 224 - hP, 536, 224 + hP, -88, 224, 536, 224 );
			hP = 210 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI_ORBIT, 132, hP, "24", 2 );
			TextOut( hDC_ADI_ORBIT, 292, hP, "24", 2 );
		}
		// -150º
		if (fabs( ballpitch + 150 ) <= 45)
		{
			hP2 = (-sinpitch) * 269.443872 + cospitch * 155.563492;
			hP = Round( hP2 );
			if (ballpitch < -150) Arc( hDC_ADI_ORBIT, -88, 224 - hP, 536, 224 + hP, 536, 224, -88, 224 );
			else Arc( hDC_ADI_ORBIT, -88, 224 - hP, 536, 224 + hP, -88, 224, 536, 224 );
			hP = 210 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI_ORBIT, 132, hP, "21", 2 );
			TextOut( hDC_ADI_ORBIT, 292, hP, "21", 2 );
		}

		// TODO yaw
		// HACK
		// "central plane"
		SelectObject( hDC_ADI_ORBIT, gdiWhiteBrush );
		SelectObject( hDC_ADI_ORBIT, gdiBlackPen );
		Rectangle( hDC_ADI_ORBIT, 216, 0, 232, 444 );
		MoveToEx( hDC_ADI_ORBIT, 224, 0, NULL );
		LineTo( hDC_ADI_ORBIT, 224, 444 );

		SelectObject( hDC_ADI_ORBIT, gdiBlackPen );
		// yaw line 30º (above horizon)
		MoveToEx( hDC_ADI_ORBIT, 380, 0, NULL );
		LineTo( hDC_ADI_ORBIT, 380, 228 + Round( 269.443872 * sinpitch ) );
		// yaw line 330º (above horizon)
		MoveToEx( hDC_ADI_ORBIT, 68, 0, NULL );
		LineTo( hDC_ADI_ORBIT, 68, 228 + Round( 269.443872 * sinpitch ) );
		SelectObject( hDC_ADI_ORBIT, gdiWhitePen );
		// yaw line 30º (below horizon)
		MoveToEx( hDC_ADI_ORBIT, 380, 444, NULL );
		LineTo( hDC_ADI_ORBIT, 380, 228 + Round( 269.443872 * sinpitch ) );
		// yaw line 330º (below horizon)
		MoveToEx( hDC_ADI_ORBIT, 68, 444, NULL );
		LineTo( hDC_ADI_ORBIT, 68, 228 + Round( 269.443872 * sinpitch ) );

		// TODO yaw labels

		// roll triangle
		SelectObject( hDC_ADI_ORBIT, gdiLightGreenPen );
		SelectObject( hDC_ADI_ORBIT, gdiLightGreenBrush );
		POINT tri[3];
		tri[0].x = 222;
		tri[0].y = 2;
		tri[1].x = 210;
		tri[1].y = 24;
		tri[2].x = 234;
		tri[2].y = 24;
		Polygon( hDC_ADI_ORBIT, tri, 3 );

		// clean up
		ModifyWorldTransform( hDC_ADI_ORBIT, &WTroll, MWT_IDENTITY );
		SetGraphicsMode( hDC_ADI_ORBIT, GM_COMPATIBLE );

		// digital RPY
		SetTextColor( hDC, CR_WHITE );
		char cbuf[8];
		sprintf_s( cbuf, 8, "%03.0f", digitalroll * DEG );
		TextOut( hDC, 786, 112, cbuf, strlen( cbuf ) );
		sprintf_s( cbuf, 8, "%03.0f", digitalpitch * DEG );
		TextOut( hDC, 786, 140, cbuf, strlen( cbuf ) );
		sprintf_s( cbuf, 8, "%03.0f", digitalyaw * DEG );
		TextOut( hDC, 786, 168, cbuf, strlen( cbuf ) );

		// copy ball
		BitBlt( hDC_ADI_ORBIT, 0, 0, 444, 444, hDC_ADIMASK_ORBIT, 0, 0, SRCAND );
		BitBlt( hDC, 292, 226, 440, 440, hDC_ADI_ORBIT, 1, 1, SRCPAINT );

		// flight director
		SelectObject( hDC, gdiBlackPen );
		SelectObject( hDC, gdiLightGreenBrush );
		POINT fd[18] = {{428,442},{428,450},{476,450},{486,470},{504,482},{520,482},{538,470},{548,450},{596,450},{596,442},{540,442},{540,450},{532,464},{518,474},{506,474},{492,464},{484,450},{484,442}};
		Polygon( hDC, fd, 18 );
		// center marker
		SelectObject( hDC, gdiLightGreenPen );
		Rectangle( hDC, 510, 382, 514, 510 );
		Rectangle( hDC, 448, 444, 576, 448 );
		return;
	}

	void MDU::ADI_ORBIT( oapi::Sketchpad* skp, double sinpitch, double cospitch, double sinroll, double cosroll, double sinyaw, double cosyaw )
	{
		// center (512,446) r = 264
		// view r = 220, ball r = 220 * sqrt( 2 )
		// 90º pitch/yaw "FOV"

		double digitalpitch = atan2( sinpitch, cospitch );
		double digitalroll = atan2( sinroll, cosroll );
		double digitalyaw = atan2( sinyaw, cosyaw );

		if (digitalpitch < 0.0) digitalpitch += PI2;
		if (digitalroll < 0.0) digitalroll += PI2;
		if (digitalyaw < 0.0) digitalyaw += PI2;

		// draw ball mesh
		oapi::FMATRIX4 mat;
		int H = 892;
		int W = 1024;

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



		STS()->D3D9()->WorldMatrix( &mat, _V( W / 2, H / 2, W + 220 ), xdir, zdir, 3.11127 );

		skp->SetWorldTransform( &mat );
		skp->SetPen( skpWhitePen );
		skp->DrawMeshGroup( hADIball, 0, oapi::Sketchpad::MeshFlags::RENDER_ALL );
		skp->SetWorldTransform();

		// roll triangle
		skp->SetPen( skpLightGreenPen );
		skp->SetBrush( skpLightGreenBrush );
		oapi::IVECTOR2 tri[3];
		tri[0].x = (long)(512 - 220 * sinroll);
		tri[0].y = (long)(446 - 220 * cosroll);
		tri[1].x = (long)(512 - 12 * cosroll - 198 * sinroll);
		tri[1].y = (long)(446 + 12 * sinroll - 198 * cosroll);
		tri[2].x = (long)(512 + 12 * cosroll - 198 * sinroll);
		tri[2].y = (long)(446 - 12 * sinroll - 198 * cosroll);
		skp->Polygon( tri, 3 );

		// digital RPY
		skp->SetTextColor( CR_WHITE );
		char cbuf[8];
		sprintf_s( cbuf, 8, "%03.0f", digitalroll * DEG );
		skp->Text( 786, 112, cbuf, strlen( cbuf ) );
		sprintf_s( cbuf, 8, "%03.0f", digitalpitch * DEG );
		skp->Text( 786, 140, cbuf, strlen( cbuf ) );
		sprintf_s( cbuf, 8, "%03.0f", digitalyaw * DEG );
		skp->Text( 786, 168, cbuf, strlen( cbuf ) );

		// flight director
		skp->SetPen( skpBlackPen );
		oapi::IVECTOR2 fd[18] = {{428,442},{428,450},{476,450},{486,470},{504,482},{520,482},{538,470},{548,450},{596,450},{596,442},{540,442},{540,450},{532,464},{518,474},{506,474},{492,464},{484,450},{484,442}};
		skp->Polygon( fd, 18 );
		// center marker
		skp->SetPen( skpLightGreenPen );
		skp->Rectangle( 510, 382, 514, 510 );
		skp->Rectangle( 448, 444, 576, 448 );
		return;
	}

	void MDU::ADI_RATE_ORBIT( HDC hDC, unsigned short pitchrate, unsigned short rollrate, unsigned short yawrate )
	{
		POINT tri[3];

		// triangles
		SelectObject( hDC, gdiLightGreenPen );
		SelectObject( hDC, gdiLightGreenBrush );

		tri[0].x = 512 + Round( static_cast<short>(rollrate) * (178.0 / (4095 * 8)) );
		tri[0].y = 152;
		tri[1].x = tri[0].x + 20;
		tri[1].y = 116;
		tri[2].x = tri[0].x - 20;
		tri[2].y = 116;
		Polygon( hDC, tri, 3 );

		tri[0].x = 806;
		tri[0].y = 446 - Round( static_cast<short>(pitchrate) * (178.0 / (4095 * 8)) );
		tri[1].x = 842;
		tri[1].y = tri[0].y - 20;
		tri[2].x = 842;
		tri[2].y = tri[0].y + 20;
		Polygon( hDC, tri, 3 );

		tri[0].x = 512 + Round( static_cast<short>(yawrate) * (178.0 / (4095 * 8)) );
		tri[0].y = 740;
		tri[1].x = tri[0].x - 20;
		tri[1].y = 776;
		tri[2].x = tri[0].x + 20;
		tri[2].y = 776;
		Polygon( hDC, tri, 3 );
		return;
	}

	void MDU::ADI_RATE_ORBIT( oapi::Sketchpad* skp, unsigned short pitchrate, unsigned short rollrate, unsigned short yawrate )
	{
		oapi::IVECTOR2 tri[3];

		// triangles
		skp->SetPen( skpLightGreenPen );
		skp->SetBrush( skpLightGreenBrush );

		tri[0].x = 512 + Round( static_cast<short>(rollrate) * (178.0 / (4095 * 8)) );
		tri[0].y = 152;
		tri[1].x = tri[0].x + 20;
		tri[1].y = 116;
		tri[2].x = tri[0].x - 20;
		tri[2].y = 116;
		skp->Polygon( tri, 3 );

		tri[0].x = 806;
		tri[0].y = 446 - Round( static_cast<short>(pitchrate) * (178.0 / (4095 * 8)) );
		tri[1].x = 842;
		tri[1].y = tri[0].y - 20;
		tri[2].x = 842;
		tri[2].y = tri[0].y + 20;
		skp->Polygon( tri, 3 );

		tri[0].x = 512 + Round( static_cast<short>(yawrate) * (178.0 / (4095 * 8)) );
		tri[0].y = 740;
		tri[1].x = tri[0].x - 20;
		tri[1].y = 776;
		tri[2].x = tri[0].x + 20;
		tri[2].y = 776;
		skp->Polygon( tri, 3 );
		return;
	}

	void MDU::ADI_ERROR_ORBIT( HDC hDC, unsigned short pitcherror, unsigned short rollerror, unsigned short yawerror )
	{
		double pos;

		// needles
		SelectObject( hDC, gdiMagentaPen );
		SelectObject( hDC, gdiMagentaBrush );

		pos = -(static_cast<short>(rollerror) * (100.0 / (4095 * 8)));
		Rectangle( hDC, 510 + Round( pos ), 448 - Round( sqrt( 62500 - (pos * pos) ) ), 514 + Round( pos ), 376 );

		pos = (static_cast<short>(pitcherror) * (100.0 / (4095 * 8)));
		Rectangle( hDC, 582, 444 + Round( pos ), 512 + Round( sqrt( 62500 - (pos * pos) ) ), 448 + Round( pos ) );

		pos = -(static_cast<short>(yawerror) * (100.0 / (4095 * 8)));
		Rectangle( hDC, 510 + Round( pos ), 516, 514 + Round( pos ), 446 + Round( sqrt( 62500 - (pos * pos) ) ) );
		return;
	}

	void MDU::ADI_ERROR_ORBIT( oapi::Sketchpad* skp, unsigned short pitcherror, unsigned short rollerror, unsigned short yawerror )
	{
		double pos;

		// needles
		skp->SetPen( skpMagentaPen );
		skp->SetBrush( skpMagentaBrush );

		pos = -(static_cast<short>(rollerror) * (100.0 / (4095 * 8)));
		skp->Rectangle( 510 + Round( pos ), 448 - Round( sqrt( 62500 - (pos * pos) ) ), 514 + Round( pos ), 376 );

		pos = (static_cast<short>(pitcherror) * (100.0 / (4095 * 8)));
		skp->Rectangle( 582, 444 + Round( pos ), 512 + Round( sqrt( 62500 - (pos * pos) ) ), 448 + Round( pos ) );

		pos = -(static_cast<short>(yawerror) * (100.0 / (4095 * 8)));
		skp->Rectangle( 510 + Round( pos ), 516, 514 + Round( pos ), 446 + Round( sqrt( 62500 - (pos * pos) ) ) );
		return;
	}
}

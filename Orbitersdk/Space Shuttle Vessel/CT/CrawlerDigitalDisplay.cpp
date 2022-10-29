/******* SSV File Modification Notice *******
Date         Developer
2020/06/14   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "CrawlerDigitalDisplay.h"
#include "Crawler.h"
#include <MathSSV.h>

extern GlobalHandles g_Resources;

namespace vc
{

CrawlerDigitalDisplay::CrawlerDigitalDisplay(Crawler* _v, const std::string& _ident)
: BasicVCComponent(_v, _ident), fOldValue(-2.0), fScale(1.0)
{
}

CrawlerDigitalDisplay::~CrawlerDigitalDisplay()
{
}

void CrawlerDigitalDisplay::OnPreStep(double simt, double simdt, double mjd)
{
	if(!Eq(fOldValue, input.GetVoltage(), 0.01/fScale)) {
		TriggerRedraw();
		fOldValue = input.GetVoltage();
	}
}

bool CrawlerDigitalDisplay::OnVCRedrawEvent(int id, int _event, SURFHANDLE surf)
{
	const int NUMX[10] = {64, 0, 64, 128, 192, 256, 320, 384, 448, 0};
	const int NUMY[10] = {384, 448, 448, 448, 448, 448, 448, 448, 448, 384};

	/*char pszString[10];
	int size = sprintf_s(pszString, 10, "%.2f", input.GetVoltage());
	oapiWriteLog(pszString);

	unsigned short left = redrawBase.x + usWidth
	for(int i=size-1;i>=0;i--) {
		int asciiValue = static_cast<int>(pszString[i]);
		//RECT tgtRect = _R(

		//if(asciiValue>=48 && asciiValue<=57) // number
			//oapiBlt(
	}*/
	RECT tgt_rect, src_rect;
	char pszLedOut[10];
	short nValue, pointPos=-1;

	int stringSize = sprintf_s(pszLedOut, 10, "%.2f", abs(input.GetVoltage()*fScale));
	if(stringSize > usDigitCount) { // ignore decimal point in string length
		oapiWriteLog("ERROR: CrawlerDigitalDisplay overflow");
		return false;
	}

	int start = usDigitCount - stringSize;
	for(int i=start+1, counter=0;(i<usDigitCount && counter<stringSize);i++, counter++) {
		// don't print decimal point or sign as a number
		if(pszLedOut[counter]=='-' || pszLedOut[counter]=='+')
			counter++; // move to next digit
		if(pszLedOut[counter]=='.') {
			//pointPos=counter;
			pointPos=i;
			counter++; // move to next digit
		}

		// print digit
		nValue = pszLedOut[counter]-'0';
		src_rect = _R(NUMX[nValue], NUMY[nValue], NUMX[nValue]+64, NUMY[nValue]+64);
		tgt_rect = _R(usDigitWidth*i, 0, usDigitWidth*(i+1), usHeight);
		oapiBlt(surf, g_Resources.digits_7seg, &tgt_rect, &src_rect);
	}

	// print sign
	if(input.GetVoltage()*fScale < 0.0) {
		src_rect = _R(64, 0, 128, 64);
		tgt_rect = _R(0, 0, usDigitWidth+start*usDigitWidth, usHeight);
		oapiBlt(surf, g_Resources.digits_7seg, &tgt_rect, &src_rect);
	}
	else {
		// clear sign section of display
		oapiBlt(surf, g_Resources.digits_7seg, 0, 0, 0, 120, usDigitWidth+start*usDigitWidth, usHeight);
	}
	/*if(LEDValues[id-AID_A8_LED1]>=0.0) src_rect = _R(0, 0, 64, 64);
	else src_rect = _R(64, 0, 128, 64);
	tgt_rect = _R(0, 0, 22, 22);
	oapiBlt(surf, g_Param.digits_7seg, &tgt_rect, &src_rect);*/

	// print decimal point
	if(pointPos!=-1 && pointPos<4) {
		src_rect = _R(184, 56, 192, 64);
		tgt_rect = _R(usDigitWidth*pointPos-3, usHeight-6, usDigitWidth*pointPos, usHeight-3);
		oapiBlt(surf, g_Resources.digits_7seg, &tgt_rect, &src_rect);
	}

	return true;
}

void CrawlerDigitalDisplay::ConnectPort(DiscreteBundle* pBundle, unsigned short usLine)
{
	input.Connect(pBundle, usLine);
}

void CrawlerDigitalDisplay::SetScaleValue(float _fScale)
{
	fScale = _fScale;
}

void CrawlerDigitalDisplay::SetDimensions(unsigned short _usWidth, unsigned short _usHeight, unsigned short _usDigitCount)
{
	usWidth = _usWidth;
	usHeight = _usHeight;
	usDigitCount = _usDigitCount;
	usDigitWidth = _usWidth/_usDigitCount;
}

void CrawlerDigitalDisplay::SetBaseCoords(unsigned short usX, unsigned short usY)
{
	redrawBase.x = usX;
	redrawBase.y = usY;
}

}

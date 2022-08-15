/******* SSV File Modification Notice *******
Date         Developer
2020/06/14   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
********************************************/
#include "CrawlerBarGauge.h"
#include "DrawAPI.h"
#include <MathSSV.h>

namespace vc
{

CrawlerBarGauge::CrawlerBarGauge(Crawler* _v, const std::string& _ident, bool IsVertical)
: BasicVCComponent(_v, _ident), bVertical(IsVertical), fOldValue(-2.0), fScale(1.0)
{
}

CrawlerBarGauge::~CrawlerBarGauge()
{
}

void CrawlerBarGauge::OnPreStep(double simt, double simdt, double mjd)
{
	if(!Eq(fOldValue, input.GetVoltage(), 0.01/fScale)) {
		TriggerRedraw();
		fOldValue = input.GetVoltage();
	}
}

bool CrawlerBarGauge::OnVCRedrawEvent(int id, int _event, SURFHANDLE surf)
{
	int midPos;
	RECT litRect;
	if(!bVertical) {
		double barSize = (usWidth*input.GetVoltage()*fScale)/abs(max-min);
		int segmentCount = static_cast<int>(barSize)/usBarWidth; // get integer number of segments
		//midPos = static_cast<int>(usWidth*((1.0+max+min)/2.0));
		midPos = static_cast<int>(usWidth*(-min/(max-min)));

		litRect.top = redrawBase.y;
		litRect.bottom = redrawBase.y+usHeight;
		if(input.GetVoltage() < 0.0) {
			litRect.left = redrawBase.x + max(midPos + segmentCount*usBarWidth, 0);
			litRect.right = redrawBase.x + midPos;
		}
		else {
			litRect.left = redrawBase.x + midPos;
			litRect.right = redrawBase.x + min(midPos + segmentCount*usBarWidth, usWidth);
		}
	}
	else {
		double barSize = (usHeight*input.GetVoltage()*fScale)/abs(max-min);
		int segmentCount = static_cast<int>(barSize)/usBarWidth; // get integer number of segments
		//midPos = static_cast<int>(usHeight*((1.0+max+min)/2.0));
		midPos = static_cast<int>(usHeight*(1.0 + min/(max-min)));

		litRect.left = redrawBase.x;
		litRect.right = redrawBase.x+usWidth;
		if(input.GetVoltage() < 0.0) {
			// TODO: make sure this works for -ve values (we don't need it yet)
			litRect.bottom = redrawBase.y + max(midPos - segmentCount*usBarWidth, 0);
			litRect.top = redrawBase.y + midPos;
		}
		else {
			litRect.bottom = redrawBase.y + midPos;
			litRect.top = redrawBase.y + min(midPos - segmentCount*usBarWidth, usHeight);
		}
	}
	RECT gaugeRect;
	gaugeRect.top = redrawBase.y;
	gaugeRect.bottom = redrawBase.y+usHeight;
	gaugeRect.left = redrawBase.x;
	gaugeRect.right = redrawBase.x+usWidth;
	// draw gauge
	HDC hDC = oapiGetDC(surf);
	HBRUSH hUnlitBrush = CreateSolidBrush(RGB(70, 76, 88));
	FillRect(hDC, &gaugeRect, hUnlitBrush);
	HBRUSH hLitBrush = CreateSolidBrush(RGB(144, 77, 101));
	FillRect(hDC, &litRect, hLitBrush);

	// draw lines
	HBRUSH hLineBrush = CreateSolidBrush(RGB(0, 0, 0));
	HGDIOBJ oldBrush = SelectObject(hDC, hLineBrush);
	int maxPos;
	if(bVertical) maxPos = usHeight;
	else maxPos = usWidth;
	for(int pos=midPos;pos < maxPos;pos+=usBarWidth) {
		if(bVertical) {
			MoveToEx(hDC, redrawBase.x, redrawBase.y+pos, NULL);
			LineTo(hDC, redrawBase.x+usWidth, redrawBase.y+pos);
		}
		else {
			MoveToEx(hDC, redrawBase.x+pos, redrawBase.y, NULL);
			LineTo(hDC, redrawBase.x+pos, redrawBase.y+usHeight);
		}
	}
	for(int pos=midPos-usBarWidth;pos >= 0;pos-=usBarWidth) {
		if(bVertical) {
			MoveToEx(hDC, redrawBase.x, redrawBase.y+pos, NULL);
			LineTo(hDC, redrawBase.x+usWidth, redrawBase.y+pos);
		}
		else {
			MoveToEx(hDC, redrawBase.x+pos, redrawBase.y, NULL);
			LineTo(hDC, redrawBase.x+pos, redrawBase.y+usHeight);
		}
	}
	SelectObject(hDC, oldBrush);

	oapiReleaseDC(surf, hDC);
	DeleteObject(hUnlitBrush);
	DeleteObject(hLitBrush);
	DeleteObject(hLineBrush);

	return true;
}

void CrawlerBarGauge::SetScaleValue(float _fScale)
{
	fScale = _fScale;
}

void CrawlerBarGauge::SetRange(double _min, double _max)
{
	max = _max;
	min = _min;
}

void CrawlerBarGauge::SetDimensions(unsigned short _usWidth, unsigned short _usHeight, unsigned short _usBarCount)
{
	usWidth = _usWidth;
	usHeight = _usHeight;
	if(bVertical) usBarWidth = _usHeight/_usBarCount;
	else usBarWidth = _usWidth/_usBarCount;
}

void CrawlerBarGauge::SetBaseCoords(unsigned short usX, unsigned short usY)
{
	redrawBase.x = usX;
	redrawBase.y = usY;
}

void CrawlerBarGauge::ConnectPort(discsignals::DiscreteBundle *pBundle, unsigned short usLine)
{
	input.Connect(pBundle, usLine);
}

};
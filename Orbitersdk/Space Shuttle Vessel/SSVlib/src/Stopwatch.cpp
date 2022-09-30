/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/08/24   GLS
2021/10/23   GLS
2022/08/05   GLS
2022/09/30   GLS
********************************************/
#include <Stopwatch.h>

Stopwatch::Stopwatch()
{
	QueryPerformanceFrequency(&liFrequency);
}

Stopwatch::~Stopwatch()
{
}

void Stopwatch::Start()
{
	QueryPerformanceCounter(&liLast);
}

double Stopwatch::Stop()
{
	QueryPerformanceCounter(&liCurrent);

	double fPerfElapsed =(((liCurrent.QuadPart - liLast.QuadPart)
            * 1000000.0) / liFrequency.QuadPart);

	return fPerfElapsed;
}

/******* SSV File Modification Notice *******
Date         Developer
2020/08/24   GLS
2021/08/24   GLS
********************************************/
#include "Averager.h"

Averager::Averager(double minTime)
: sum(0.0), timeLimit(minTime)
{
}

Averager::~Averager()
{
}

void Averager::NewValue(double val, double timestamp)
{
	sum += val;
	previousValues.push(val);
	previousTimestamps.push(timestamp);
	while(previousTimestamps.back()-previousTimestamps.front() > timeLimit) {
		sum -= previousValues.front();
		previousValues.pop();
		previousTimestamps.pop();
	}
}

double Averager::GetAvgValue() const
{
	if(previousValues.size() < 1) return 0.0;
	return sum/previousValues.size();
}

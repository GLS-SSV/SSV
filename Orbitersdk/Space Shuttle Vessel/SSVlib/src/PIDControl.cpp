/******* SSV File Modification Notice *******
Date         Developer
2020/08/24   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
********************************************/
#include "PIDControl.h"
#include "MathSSV.h"

PIDControl::PIDControl(double pGain, double dGain, double iGain)
	: integral(0.0), lastValue(0.0), firstStep(true), outputLimitsSet(false), integralLimitsSet(false)
{
	SetGains(pGain, dGain, iGain);
}

PIDControl::PIDControl(double pGain, double dGain, double iGain, double min, double max)
	: integral(0.0), lastValue(0.0), firstStep(true), integralLimitsSet(false)
{
	SetGains(pGain, dGain, iGain);
	SetLimits(min, max);
}

PIDControl::PIDControl(double pGain, double dGain, double iGain, double min, double max, double iMin, double iMax)
	: integral(0.0), lastValue(0.0), firstStep(true)
{
	SetGains(pGain, dGain, iGain);
	SetLimits(min, max);
	SetIntegralLimits(iMin, iMax);
}

PIDControl::~PIDControl()
{
}

void PIDControl::Reset()
{
	integral=0.0;
	lastValue=0.0;
	firstStep=true;
}

double PIDControl::Step(double value, double simdt)
{
	double derivative=0.0;

	if(!firstStep) {
		derivative = (value-lastValue)/simdt;
		//for the moment, use trapezoidal rule to calculate integral
		integral += simdt*((value+lastValue)/2.0);
	}
	else firstStep=false;
	//store value for next timestep
	lastValue=value;

	double limitedIntegral;
	if(integralLimitsSet)
		limitedIntegral = range(integralMin, integral, integralMax);
	else limitedIntegral = integral;

	double result = proportionalGain * value
		+ derivativeGain * derivative
		+ integralGain * limitedIntegral;
	if(outputLimitsSet) result = range(minOutput, result, maxOutput);
	return result;
}

void PIDControl::SetGains(double pGain, double dGain, double iGain)
{
	proportionalGain=pGain;
	derivativeGain=dGain;
	integralGain=iGain;
}

void PIDControl::SetLimits(double min, double max)
{
	minOutput = min;
	maxOutput = max;
	outputLimitsSet = true;
}

void PIDControl::SetIntegralLimits(double min, double max)
{
	integralMin = min;
	integralMax = max;
	integralLimitsSet = true;
}
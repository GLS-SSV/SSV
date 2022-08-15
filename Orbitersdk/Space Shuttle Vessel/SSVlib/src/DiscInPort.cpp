/******* SSV File Modification Notice *******
Date         Developer
2020/08/24   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
********************************************/
#include "DiscInPort.h"
#include "DiscreteBundle.h"

namespace discsignals {

	DiscInPort::DiscInPort()
		:DiscretePort()
	{
	}

	DiscInPort::~DiscInPort()
	{
	}

	float DiscInPort::GetVoltage() const
	{
		if(pBundle) {
			return pBundle->GetVoltage(usLine);
		}
		else
			return 0.0;
	}

	bool DiscInPort::IsSet() const {
		return IsSet(4.7f);
	}

	bool DiscInPort::IsSet(float fThreshold) const {
		if(pBundle)
		{
			return (pBundle->GetVoltage(usLine) > fThreshold);
		}
		else {
			return false;
		}
	}

	DiscDemultiplex16::DiscDemultiplex16() {
		usLatch = 0;
	}

	DiscDemultiplex16::~DiscDemultiplex16() {
	}

	void DiscDemultiplex16::Propagate(double simt, double simdt, double mjd) {
		unsigned short x = 0;
		for(unsigned int i = 0; i<16; i++) {
			if(r[15-i].IsSet()) x |= 1;
			x <<= 1;
		}
		usLatch = x;
	}



};

/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/09/29   GLS
********************************************/
#include "StandardRotarySwitch.h"

namespace vc
{
	RotaryDemuxSwitch::RotaryDemuxSwitch(Atlantis *_sts, const std::string &_ident, unsigned short _usNumPositions)
		: BasicRotarySwitch(_sts, _usNumPositions, _ident), outputSignals(_usNumPositions),
		bInputConnected(false)
	{
	}

	RotaryDemuxSwitch::~RotaryDemuxSwitch()
	{
	}

	void RotaryDemuxSwitch::ConnectInputSignal(discsignals::DiscreteBundle *pBundle, unsigned short usLine)
	{
		inputSignal.Connect(pBundle, usLine);
		bInputConnected=true;
	}

	void RotaryDemuxSwitch::ConnectOutputSignal(unsigned short usIndex, discsignals::DiscreteBundle *pBundle, unsigned short usLine)
	{
		outputSignals.at(usIndex).Connect(pBundle, usLine);
	}

	void RotaryDemuxSwitch::OnPositionChange(unsigned short usNewPosition)
	{
		BasicRotarySwitch::OnPositionChange(usNewPosition);

		// if we have an input signal, use input value as output
		// otherwise, set output signal
		bool bOutput=true;
		if(bInputConnected) bOutput=inputSignal.IsSet();

		for(unsigned short i=0;i<usNumPositions;i++) {
			if(i==usNewPosition && bOutput) outputSignals.at(i).SetLine();
			else outputSignals.at(i).ResetLine();
		}
	}


	StandardRotarySwitch::StandardRotarySwitch( Atlantis *_sts, const std::string &_ident, unsigned short _usNumPositions, unsigned short _usNumMuxes ):BasicRotarySwitch( _sts, _usNumPositions, _ident ),
		inputSignals( _usNumMuxes, vector<DiscInPort>( _usNumPositions ) ),
		outputSignal( _usNumMuxes )
	{
	}

	StandardRotarySwitch::~StandardRotarySwitch()
	{
	}

	void StandardRotarySwitch::ConnectInputSignal( unsigned short usMux, unsigned short usIndex, DiscreteBundle *pBundle, unsigned short usLine )
	{
		inputSignals.at( usMux ).at( usIndex ).Connect( pBundle, usLine );
		return;
	}

	void StandardRotarySwitch::ConnectOutputSignal( unsigned short usMux, DiscreteBundle *pBundle, unsigned short usLine)
	{
		outputSignal.at( usMux ).Connect( pBundle, usLine );
		return;
	}

	void StandardRotarySwitch::OnPreStep( double simt, double simdt, double mjd )
	{
		for (int i = outputSignal.size() - 1; i >= 0; i--) outputSignal.at( i ).SetLine( inputSignals.at( i ).at( usCurrentPosition ).GetVoltage() );
		return;
	}
}

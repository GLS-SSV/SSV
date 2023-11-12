/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/09/29   GLS
2023/02/19   GLS
2023/11/11   GLS
********************************************/
#include "StandardRotarySwitch.h"
#include <cassert>


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

	void RotaryDemuxSwitch::ConnectOutputSignal( unsigned short usIndex, discsignals::DiscreteBundle* pBundle, unsigned short usLine )
	{
		assert( (usIndex < usNumPositions) && "RotaryDemuxSwitch::ConnectOutputSignal::usIndex" );
		outputSignals[usIndex].Connect( pBundle, usLine );
	}

	void RotaryDemuxSwitch::OnPositionChange(unsigned short usNewPosition)
	{
		BasicRotarySwitch::OnPositionChange(usNewPosition);

		// if we have an input signal, use input value as output
		// otherwise, set output signal
		bool bOutput = true;
		if (bInputConnected) bOutput = inputSignal.IsSet();

		for (unsigned short i = 0; i < usNumPositions; i++)
		{
			if ((i == usNewPosition) && bOutput) outputSignals[i].SetLine( 28.0f );
			else outputSignals[i].ResetLine();
		}
		return;
	}


	StandardRotarySwitch::StandardRotarySwitch( Atlantis *_sts, const std::string &_ident, unsigned short _usNumPositions, unsigned short _usNumMuxes ):BasicRotarySwitch( _sts, _usNumPositions, _ident ),
		inputSignals( _usNumMuxes, vector<DiscInPort>( _usNumPositions ) ),
		outputSignal( _usNumMuxes ),
		usNumMuxes(_usNumMuxes)
	{
	}

	StandardRotarySwitch::~StandardRotarySwitch()
	{
	}

	void StandardRotarySwitch::ConnectInputSignal( unsigned short usMux, unsigned short usIndex, DiscreteBundle *pBundle, unsigned short usLine )
	{
		assert( (usMux < usNumMuxes) && "StandardRotarySwitch::ConnectInputSignal::usMux" );
		assert( (usIndex < usNumPositions) && "StandardRotarySwitch::ConnectInputSignal::usIndex" );
		inputSignals[usMux][usIndex].Connect( pBundle, usLine );
		return;
	}

	void StandardRotarySwitch::ConnectOutputSignal( unsigned short usMux, DiscreteBundle *pBundle, unsigned short usLine )
	{
		assert( (usMux < usNumMuxes) && "StandardRotarySwitch::ConnectOutputSignal::usMux" );
		outputSignal[usMux].Connect( pBundle, usLine );
		return;
	}

	void StandardRotarySwitch::OnPreStep( double simt, double simdt, double mjd )
	{
		for (int i = outputSignal.size() - 1; i >= 0; i--) outputSignal[i].SetLine( inputSignals[i][usCurrentPosition].GetVoltage() );
		return;
	}
}

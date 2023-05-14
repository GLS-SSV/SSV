/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/01/20   GLS
2021/08/24   GLS
2022/06/04   GLS
2022/09/29   GLS
2022/10/09   GLS
2022/10/12   GLS
2022/11/15   GLS
2022/11/16   GLS
2022/12/31   GLS
2023/05/14   GLS
********************************************/
#include "SimpleMDM.h"
#include "../gnc/RA.h"
#include "MathSSV.h"
#include <cassert>


namespace dps
{
	SimpleMDM::SimpleMDM( AtlantisSubsystemDirector* _director, const string& _ident, BusManager* pBusManager ):AtlantisSubsystem( _director, _ident ), BusTerminal( pBusManager )
	{
	}

	SimpleMDM::~SimpleMDM()
	{
	}

	void SimpleMDM::IOM_TAC( unsigned short task, unsigned int ch, unsigned short& data, gnc::RadarAltimeter* pRA )
	{
		if (task == 0b000)
		{
			// input
			switch (ch)
			{
				case 0b00000:// TACAN bearing A
					break;
				case 0b00001:// TACAN bearing B
					break;
				case 0b00010:// TACAN range A
					break;
				case 0b00011:// TACAN range B
					break;
				case 0b00100:// Radar Altimeter data
					data = pRA->GetData();
					break;
				case 0b00101:// TACAN cntl panel and Radar Alt discretes
					break;
				case 0b00110:// TACAN cntl wd
					break;
			}
		}
		else if (task == 0b001)
		{
			// output
		}
		return;
	}

	void SimpleMDM::IOM_DIL( unsigned short task, unsigned int ch, unsigned short& data, DiscInPort dip[3][16] )
	{
		assert( (ch < 3) && "SimpleMDM::IOM_DIL.ch" );

		if (task == 0b000)
		{
			// input
			data = 0;
			for (int i = 15; i >= 0; i--)
			{
				data <<= 1;
				data |= static_cast<unsigned short>(dip[ch][i].IsSet( /*2.25*/ ));// TODO use correct voltage level
			}
		}
		/*else if (task == 0b001)
		{
			// output
		}*/
		return;
	}

	void SimpleMDM::IOM_DIH( unsigned short task, unsigned int ch, unsigned short& data, DiscInPort dip[3][16] )
	{
		assert( (ch < 3) && "SimpleMDM::IOM_DIH.ch" );

		if (task == 0b000)
		{
			// input
			data = 0;
			for (int i = 15; i >= 0; i--)
			{
				data <<= 1;
				data |= static_cast<unsigned short>(dip[ch][i].IsSet( /*8.0*/ ));// TODO use correct voltage level
			}
		}
		/*else if (task == 0b001)
		{
			// output
		}*/
		return;
	}

	void SimpleMDM::IOM_AIS( unsigned short task, unsigned int ch, unsigned short& data, DiscInPort dip[32] )
	{
		assert( (ch < 32) && "SimpleMDM::IOM_AIS.ch" );

		if (task == 0b000)
		{
			// input
			double v = dip[ch].GetVoltage();
			v = range( -5.12, v, 5.11 );// input bounds [-5.12V, +5.11V]
			data = static_cast<short>(v / 0.01) & 0x3FF;// LSB 10mv
		}
		/*else if (task == 0b001)
		{
			// output
		}*/
		return;
	}

	void SimpleMDM::IOM_DOL( unsigned short task, unsigned int ch, unsigned short& data, DiscOutPort dop[3][16] )
	{
		assert( (ch < 3) && "SimpleMDM::IOM_DOL.ch" );

		/*if (task == 0b000)
		{
			// input
		}
		else*/ if (task == 0b001)
		{
			// output
			unsigned short tmp = data;
			for (int i = 0; i <= 15; i++)
			{
				dop[ch][i].SetLine( (tmp & 0x0001) ? 5.0f : 0.0f );// TODO use correct voltage level
				tmp >>= 1;
			}
		}
		return;
	}

	void SimpleMDM::IOM_DOH( unsigned short task, unsigned int ch, unsigned short& data, DiscOutPort dop[3][16] )
	{
		assert( (ch < 3) && "SimpleMDM::IOM_DOH.ch" );

		/*if (task == 0b000)
		{
			// input
		}
		else*/ if (task == 0b001)
		{
			// output
			unsigned short tmp = data;
			for (int i = 0; i <= 15; i++)
			{
				dop[ch][i].SetLine( (tmp & 0x0001) ? 5.0f : 0.0f );// TODO use correct voltage level
				tmp >>= 1;
			}
		}
		return;
	}

	void SimpleMDM::IOM_AOD( unsigned short task, unsigned int ch, unsigned short& data, DiscOutPort dopHI[16], DiscOutPort dopLO[16] )
	{
		assert( (ch < 16) && "SimpleMDM::IOM_AOD.ch" );

		/*if (task == 0b000)
		{
			// input
		}
		else*/ if (task == 0b001)
		{
			// output
			bool hasHI = dopHI[ch].IsConnected();
			bool hasLO = dopLO[ch].IsConnected();
			double out = data & 0x07FF;

			// scale
			out *= 0.0025;// 5.12 / 2048

			// if double-ended output, split the value between the outputs to maintain 5.12v range
			if (hasHI == hasLO) out /= 2;

			// handle sign
			if (data & 0x0800) out = -out;

			if (hasHI) dopHI[ch].SetLine( static_cast<float>(out) );
			if (hasLO) dopLO[ch].SetLine( static_cast<float>(-out) );

		}
		return;
	}
}

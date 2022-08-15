/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/01/20   GLS
2021/08/24   GLS
2022/06/04   GLS
********************************************/
#include "SimpleMDM.h"
#include "SimpleShuttleBus.h"
#include <cassert>


namespace dps
{
	SimpleMDM::SimpleMDM( AtlantisSubsystemDirector* _director, const string& _ident ):AtlantisSubsystem( _director, _ident )
	{
	}

	SimpleMDM::~SimpleMDM()
	{
	}

	void SimpleMDM::Realize( void )
	{
		return;
	}

	void SimpleMDM::busCommand( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw )
	{
		return;
	}

	void SimpleMDM::busRead( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw )
	{
		return;
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
}

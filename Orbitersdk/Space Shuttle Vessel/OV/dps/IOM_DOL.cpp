#include "IOM_DOL.h"


namespace dps
{
	IOM_DOL::IOM_DOL( const std::string& mdmname, const unsigned short iomidx ):IOM( mdmname, iomidx )
	{
		for (auto& x : driver) x = 0;
		return;
	}

	IOM_DOL::~IOM_DOL()
	{
		return;
	}

	void IOM_DOL::Connect( discsignals::DiscreteBundleManager* bman )
	{
		for (int c = 0; c < 3; c++)
		{
			std::string str = "MDM_" + mdmname + "_IOM" + std::to_string( iomidx ) + "_CH" + std::to_string( c );
			discsignals::DiscreteBundle* pBundle = bman->CreateBundle( str, 16 );

			for (int b = 0; b < 16; b++)
			{
				port[c][b].Connect( pBundle, b );
			}

			Output( c );
		}
		return;
	}

	bool IOM_DOL::LoadState( const char* line )
	{
		std::string str = "IOM" + std::to_string( iomidx );
		if (!_strnicmp( line, str.c_str(), str.length() ))
		{
			sscanf_s( line + str.length() + 1, "%hu %hu %hu", &driver[0], &driver[1], &driver[2] );
			return true;
		}
		return false;
	}

	void IOM_DOL::SaveState( FILEHANDLE scn ) const
	{
		std::string str = "IOM" + std::to_string( iomidx );
		char cbuf[64];

		sprintf_s( cbuf, 16, "%hu %hu %hu", driver[0], driver[1], driver[2] );

		oapiWriteScenario_string( scn, (char*)str.c_str(), cbuf );
		return;
	}

	void IOM_DOL::PowerLoss( void )
	{
		for (int i = 0; i < 3; i++)
		{
			driver[i] = 0;
			Output( i );
		}
		return;
	}

	bool IOM_DOL::busSCU( const unsigned char addr, const unsigned char task, unsigned short& data )
	{
		if (addr > 2) return false;

		switch (task)
		{
			case 0b000:// response data word transfer
				break;
			case 0b001:// command data word transfer
				driver[addr] = data;
				Output( addr );
				break;
			case 0b010:// reset IOM
			case 0b011:// reset IOM
				for (auto& x : driver) x = 0;
				break;
			case 0b100:// BITE test 1
			case 0b110:// BITE test 1
				break;
			case 0b101:// BITE test 2
			case 0b111:// BITE test 2
				break;
		}
		return true;
	}
	
	void IOM_DOL::Output( const unsigned short addr )
	{
		unsigned short tmp = driver[addr];
		for (int i = 0; i <= 15; i++)
		{
			port[addr][i].SetLine( (tmp & 0x0001) ? 6.0f : 0.0f );
			tmp >>= 1;
		}
		return;
	}
}

#include "IOM_AOD.h"
#include <sstream>


namespace dps
{
	IOM_AOD::IOM_AOD( const std::string& mdmname, const unsigned short iomidx ):IOM( mdmname, iomidx )
	{
		for (auto& x : driver) x = 0;
		return;
	}

	IOM_AOD::~IOM_AOD()
	{
		return;
	}

	void IOM_AOD::Connect( discsignals::DiscreteBundleManager* bman )
	{
		std::string str = "MDM_" + mdmname + "_IOM" + std::to_string( iomidx ) + "_PLUS";
		discsignals::DiscreteBundle* pBundle = bman->CreateBundle( str, 16 );
		for (int c = 0; c < 16; c++)
		{
			portPlus[c].Connect( pBundle, c );
		}

		str = "MDM_" + mdmname + "_IOM" + std::to_string( iomidx ) + "_MINUS";
		pBundle = bman->CreateBundle( str, 16 );
		for (int c = 0; c < 16; c++)
		{
			portMinus[c].Connect( pBundle, c );

			Output( c );
		}
		return;
	}

	bool IOM_AOD::LoadState( const char* line )
	{
		std::string str = "IOM" + std::to_string( iomidx );
		if (!_strnicmp( line, str.c_str(), str.length() ))
		{
			std::string input = line + str.length() + 1;
			std::string tmp;
			std::stringstream ssinput( input );
			unsigned short i = 0;
			while (getline( ssinput, tmp, ' ' ) && (i < 16))
			{
				driver[i] = std::stoi( tmp ) & 0xFFFF;
				i++;
			}
			return true;
		}
		return false;
	}

	void IOM_AOD::SaveState( FILEHANDLE scn ) const
	{
		std::string str = "IOM" + std::to_string( iomidx );
		std::string cbuf;
		for (int i = 0; i < 16; i++) cbuf += std::to_string( driver[i] ) + " ";
		cbuf[cbuf.length() - 1] = 0;// delete space at end

		oapiWriteScenario_string( scn, (char*)str.c_str(), (char*)cbuf.c_str() );
		return;
	}

	void IOM_AOD::PowerLoss( void )
	{
		for (int i = 0; i < 16; i++)
		{
			driver[i] = 0;
			Output( i );
		}
		return;
	}

	bool IOM_AOD::busSCU( const unsigned char addr, const unsigned char task, unsigned short& data )
	{
		if (addr > 15) return false;

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
	
	void IOM_AOD::Output( const unsigned short addr )
	{
		bool hasPlus = portPlus[addr].IsConnected();
		bool hasMinus = portMinus[addr].IsConnected();
		double out = driver[addr] & 0x07FF;

		// scale
		out *= 0.0025;// 5.12 / 2048

		// if double-ended output, split the value between the outputs to maintain 5.12v range
		if (hasPlus == hasMinus) out /= 2;

		// handle sign
		if (driver[addr] & 0x0800) out = -out;

		if (hasPlus) portPlus[addr].SetLine( static_cast<float>(out) );
		if (hasMinus) portMinus[addr].SetLine( static_cast<float>(-out) );
		return;
	}
}

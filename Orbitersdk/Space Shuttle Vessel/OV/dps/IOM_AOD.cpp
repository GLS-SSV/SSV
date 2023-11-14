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
		std::string strHi = "MDM_" + mdmname + "_IOM" + std::to_string( iomidx ) + "_HI";
		discsignals::DiscreteBundle* pBundleHi = bman->CreateBundle( strHi, 16 );
		std::string strLo = "MDM_" + mdmname + "_IOM" + std::to_string( iomidx ) + "_LO";
		discsignals::DiscreteBundle* pBundleLo = bman->CreateBundle( strLo, 16 );

		// HACK bundles for single-ended outputs
		std::string strHiSingle = "MDM_" + mdmname + "_IOM" + std::to_string( iomidx ) + "_HI_SINGLE";
		discsignals::DiscreteBundle* pBundleHiSingle = bman->CreateBundle( strHiSingle, 16 );
		std::string strLoSingle = "MDM_" + mdmname + "_IOM" + std::to_string( iomidx ) + "_LO_SINGLE";
		discsignals::DiscreteBundle* pBundleLoSingle = bman->CreateBundle( strLoSingle, 16 );

		for (int c = 0; c < 16; c++)
		{
			portHiDoubleEnded[c].Connect( pBundleHi, c );
			portLoDoubleEnded[c].Connect( pBundleLo, c );

			portHiSingleEnded[c].Connect( pBundleHiSingle, c );
			portLoSingleEnded[c].Connect( pBundleLoSingle, c );

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
				// TODO update gnds
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
		double out = (driver[addr] & 0x7FF0) >> 4;

		// scale
		out *= 0.0025;// 5.12 / 2048

		// handle sign
		if (driver[addr] & 0x8000) out = -out;

		// HACK output single-ended signals
		portHiSingleEnded[addr].SetLine( static_cast<float>(out) );
		portLoSingleEnded[addr].SetLine( static_cast<float>(-out) );

		// split the value between the outputs to maintain 5.12v range
		out /= 2;

		// output double-ended signals
		portHiDoubleEnded[addr].SetLine( static_cast<float>(out) );
		portLoDoubleEnded[addr].SetLine( static_cast<float>(-out) );
		return;
	}
}

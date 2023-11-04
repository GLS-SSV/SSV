#include "IOM_AID.h"
#include "MathSSV.h"


namespace dps
{
	IOM_AID::IOM_AID( const std::string& mdmname, const unsigned short iomidx ):IOM( mdmname, iomidx )
	{
		return;
	}

	IOM_AID::~IOM_AID()
	{
		return;
	}

	void IOM_AID::Connect( discsignals::DiscreteBundleManager* bman )
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
		}
		return;
	}

	bool IOM_AID::busSCU( const unsigned char addr, const unsigned char task, unsigned short& data )
	{
		if (addr > 15) return false;

		switch (task)
		{
			case 0b000:// response data word transfer
				{
					double vHI = portPlus[addr].IsConnected() ? portPlus[addr].GetVoltage() : 0.0;
					double vLO = portMinus[addr].IsConnected() ? portMinus[addr].GetVoltage() : 0.0;
					vHI = range( -5.12, vHI, 5.11 );// input bounds [-5.12V, +5.11V]
					vLO = range( -5.12, vLO, 5.11 );// input bounds [-5.12V, +5.11V]
					data = static_cast<short>((vHI - vLO) / 0.01) & 0x3FF;// LSB 10mv
				}
				break;
			case 0b001:// command data word transfer
				break;
			case 0b010:// reset IOM
			case 0b011:// reset IOM
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
}

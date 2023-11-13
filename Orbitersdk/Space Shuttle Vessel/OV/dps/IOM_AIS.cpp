#include "IOM_AIS.h"
#include "MathSSV.h"


namespace dps
{
	IOM_AIS::IOM_AIS( const std::string& mdmname, const unsigned short iomidx ):IOM( mdmname, iomidx )
	{
		return;
	}

	IOM_AIS::~IOM_AIS()
	{
		return;
	}

	void IOM_AIS::Connect( discsignals::DiscreteBundleManager* bman )
	{
		std::string str = "MDM_" + mdmname + "_IOM" + std::to_string( iomidx ) + "_CH0_15";
		discsignals::DiscreteBundle* pBundle = bman->CreateBundle( str, 16 );
		for (int c = 0; c < 16; c++)
		{
			port[c].Connect( pBundle, c );
		}

		str = "MDM_" + mdmname + "_IOM" + std::to_string( iomidx ) + "_CH16_31";
		pBundle = bman->CreateBundle( str, 16 );
		for (int c = 16; c < 32; c++)
		{
			port[c].Connect( pBundle, c - 16 );
		}
		return;
	}

	bool IOM_AIS::busSCU( const unsigned char addr, const unsigned char task, unsigned short& data )
	{
		if (addr > 31) return false;

		switch (task)
		{
			case 0b000:// response data word transfer
				{
					double v = port[addr].GetVoltage();
					v = range( -5.12, v, 5.11 );// input bounds [-5.12V, +5.11V]
					data = static_cast<short>(v / 0.01) & 0x3FF;// LSB 10mv
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

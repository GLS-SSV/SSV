#include "IOM_SIO.h"


namespace dps
{
	IOM_SIO::IOM_SIO( const std::string& mdmname, const unsigned short iomidx ):IOM( mdmname, iomidx )
	{
		return;
	}

	IOM_SIO::~IOM_SIO()
	{
		return;
	}

	bool IOM_SIO::busSCU( const unsigned char addr, const unsigned char task, unsigned short& data )
	{
		if (addr > 3) return false;

		switch (task)
		{
			case 0b000:// response data word transfer
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

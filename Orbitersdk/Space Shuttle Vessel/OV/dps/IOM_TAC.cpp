#include "IOM_TAC.h"
#include "../gnc/RA.h"
#include "MathSSV.h"
#include <cassert>


namespace dps
{
	IOM_TAC::IOM_TAC( const string& mdmname, const unsigned short iomidx ):IOM( mdmname, iomidx )
	{
		return;
	}

	IOM_TAC::~IOM_TAC()
	{
		return;
	}

	bool IOM_TAC::busSCU( const unsigned char addr, const unsigned char task, unsigned short& data )
	{
		if (addr > 6) return false;

		switch (task)
		{
			case 0b000:// response data word transfer
				switch (addr)
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

	void IOM_TAC::ConnectRA( gnc::RadarAltimeter* pRA )
	{
		this->pRA = pRA;
		return;
	}
}

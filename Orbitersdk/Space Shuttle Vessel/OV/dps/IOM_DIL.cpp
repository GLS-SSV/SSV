#include "IOM_DIL.h"


namespace dps
{
	IOM_DIL::IOM_DIL( const std::string& mdmname, const unsigned short iomidx ):IOM( mdmname, iomidx )
	{
		return;
	}

	IOM_DIL::~IOM_DIL()
	{
		return;
	}

	void IOM_DIL::Connect( discsignals::DiscreteBundleManager* bman )
	{
		for (int c = 0; c < 3; c++)
		{
			std::string str = "MDM_" + mdmname + "_IOM" + std::to_string( iomidx ) + "_CH" + std::to_string( c );
			discsignals::DiscreteBundle* pBundle = bman->CreateBundle( str, 16 );

			for (int b = 0; b < 16; b++)
			{
				port[c][b].Connect( pBundle, b );
			}
		}
		return;
	}

	bool IOM_DIL::busSCU( const unsigned char addr, const unsigned char task, unsigned short& data )
	{
		if (addr > 2) return false;

		switch (task)
		{
			case 0b000:// response data word transfer
				data = 0;
				for (int i = 15; i >= 0; i--)
				{
					data <<= 1;
					data |= static_cast<unsigned short>(port[addr][i].IsSet( 2.25 ));
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

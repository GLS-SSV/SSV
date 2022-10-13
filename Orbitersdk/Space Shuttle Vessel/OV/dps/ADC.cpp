#include "ADC.h"
#include <DiscreteBundleManager.h>
#include <MathSSV.h>
#include "../APU.h"


namespace dps
{
	ADC::ADC( AtlantisSubsystemDirector* _director, const string& _ident ):AtlantisSubsystem( _director, _ident )
	{
		std::string tmp = _ident.substr( _ident.length() - 2, 2 );
		if (tmp == "1A") id = 1;
		else if (tmp == "1B") id = 2;
		else if (tmp == "2A") id = 3;
		else /*if (tmp == "2B")*/ id = 4;
		return;
	}

	ADC::~ADC( void )
	{
		return;
	}

	void ADC::Realize( void )
	{
		discsignals::DiscreteBundle* pBundle;

		switch (id)
		{
			case 1:// 1A
			case 2:// 1B
				// SPI, OMS/RCS
				pBundle = BundleManager()->CreateBundle( "SPI_DRIVE_SIGNALS", 16 );
				input[0].Connect( pBundle, 7 );// 1 - Body Flap Position
				input[1].Connect( pBundle, 8 );// 2 - Aileron Position
				input[2].Connect( pBundle, 3 );// 3 - Left Inboard Elevon Position
				input[3].Connect( pBundle, 4 );// 4 - Left Outboard Elevon Position
				input[4].Connect( pBundle, 5 );// 5 - Right Inboard Elevon Position
				input[5].Connect( pBundle, 6 );// 6 - Right Outboard Elevon Position
				input[6].Connect( pBundle, 1 );// 7 - Speed Brake Position
				input[7].Connect( pBundle, 0 );// 8 - Rudder Position
				input[8].Connect( pBundle, 9 );// 9 - Valid Flag
				input[9].Connect( pBundle, 2 );// 10 - Speed Brake Command Position
				pBundle = BundleManager()->CreateBundle( "MPS_ENGINE_PC", 3 );
				input[10].Connect( pBundle, 0 );// 11 - MPS Center Engine Chamber Pressure
				input[11].Connect( pBundle, 1 );// 12 - MPS Left Engine Chamber Pressure
				input[12].Connect( pBundle, 2 );// 13 - MPS Right Engine Chamber Pressure
				pBundle = BundleManager()->CreateBundle( "MPS_SENSORS", 2 );
				input[13].Connect( pBundle, 1 );// 14 - MPS LH2 Manifold Pressure
				input[18].Connect( pBundle, 0 );// 19 - MPS LO2 Manifold Pressure
				pBundle = BundleManager()->CreateBundle( "MPS_HE_SENSORS", 12 );
				input[14].Connect( pBundle, 3 );// 15 - MPS Left Engine He Tank Pressure
				input[15].Connect( pBundle, 4 );// 16 - MPS Left Engine He Regulator Pressure
				input[16].Connect( pBundle, 9 );// 17 - MPS PNEU He Tank Pressure
				input[17].Connect( pBundle, 10 );// 18 - MPS PNEU He Regulator Pressure
				input[19].Connect( pBundle, 0 );// 20 - MPS Center Engine He Tank Pressure
				input[20].Connect( pBundle, 1 );// 21 - MPS Center Engine He Regulator Pressure
				input[21].Connect( pBundle, 6 );// 22 - MPS Right Engine He Tank Pressure
				input[22].Connect( pBundle, 7 );// 23 - MPS Right Engine He Regulator Pressure
				pBundle = BundleManager()->CreateBundle( "LOMS_SENSORS", 16 );
				input[23].Connect( pBundle, 3 );// 24 - OMS Left He Tank Pressure
				input[24].Connect( pBundle, 1 );// 25 - OMS Left N2 Tank Pressure
				input[25].Connect( pBundle, 0 );// 26 - OMS Left Chamber Pressure
				pBundle = BundleManager()->CreateBundle( "ROMS_SENSORS", 16 );
				input[27].Connect( pBundle, 3 );// 28 - OMS Right He Tank Pressure
				input[28].Connect( pBundle, 1 );// 29 - OMS Right N2 Tank Pressure
				input[29].Connect( pBundle, 0 );// 30 - OMS Right Chamber Pressure
				break;
			case 3:// 2A
			case 4:// 2B
				// APU/HYD
				//input[0].Connect( pBundle, 0 );// 1 - APU 1 Fuel Quantity
				//input[1].Connect( pBundle, 0 );// 2 - APU 1 H2O Quantity
				//input[2].Connect( pBundle, 0 );// 3 - APU 2 Fuel Quantity
				//input[3].Connect( pBundle, 0 );// 4 - APU 2 H2O Quantity
				//input[4].Connect( pBundle, 0 );// 5 - APU 3 H2O Quantity
				//input[5].Connect( pBundle, 0 );// 6 - APU 3 Fuel Quantity
				pBundle = BundleManager()->CreateBundle( "APU_1_SENSORS", 16 );
				input[6].Connect( pBundle, 0 );// 7 - APU 1 Fuel Pressure
				//input[7].Connect( pBundle, 0 );// 8 - APU 1 Oil In Temperature
				pBundle = BundleManager()->CreateBundle( "HYD_PMP_PRESS", 16 );
				input[9].Connect( pBundle, 0 );// 10 - Hydraulic 1 Pressure
				input[14].Connect( pBundle, 3 );// 15 - Hydraulic 2 Pressure
				input[19].Connect( pBundle, 6 );// 20 - Hydraulic 3 Pressure
				//input[10].Connect( pBundle, 0 );// 11 - Hydraulic 1 Reservoir Quantity
				pBundle = BundleManager()->CreateBundle( "APU_2_SENSORS", 16 );
				input[11].Connect( pBundle, 0 );// 12 - APU 2 Fuel Pressure
				//input[12].Connect( pBundle, 0 );// 13 - APU 2 Oil In Temperature
				//input[15].Connect( pBundle, 0 );// 16 - Hydraulic 2 Reservoir Quantity
				pBundle = BundleManager()->CreateBundle( "APU_3_SENSORS", 16 );
				input[16].Connect( pBundle, 0 );// 17 - APU 3 Fuel Pressure
				//input[17].Connect( pBundle, 0 );// 18 - APU 3 Oil In Temperature
				//input[20].Connect( pBundle, 0 );// 21 - Hydraulic 3 Reservoir Quantity

				pAPU[0] = dynamic_cast<APU*>(director->GetSubsystemByName( "APU1" ));
				pAPU[1] = dynamic_cast<APU*>(director->GetSubsystemByName( "APU2" ));
				pAPU[2] = dynamic_cast<APU*>(director->GetSubsystemByName( "APU3" ));
				break;
		}
		return;
	}

	unsigned short ADC::GetData( const unsigned short idx ) const
	{
		unsigned short ret = 0;// 12 bytes, signed

		// HACK calculate here apu fu qty
		if ((id >= 3) && ((idx == 1) || (idx == 3) || (idx == 6)))
		{
			if (idx == 1)
			{
				ret = static_cast<unsigned short>((pAPU[0]->GetFuelLevel() / APU_FUEL_TANK_MASS) * 2048);// APU 1 Fuel Quantity
			}
			else if (idx == 3)
			{
				ret = static_cast<unsigned short>((pAPU[1]->GetFuelLevel() / APU_FUEL_TANK_MASS) * 2048);// APU 2 Fuel Quantity
			}
			else// if (idx == 6)
			{
				ret = static_cast<unsigned short>((pAPU[2]->GetFuelLevel() / APU_FUEL_TANK_MASS) * 2048);// APU 3 Fuel Quantity
			}
			return ret;
		}

		double in = input[idx - 1].GetVoltage();
		bool neg = (in < 0.0);
		in /= 0.00244140625;// 5 / 2048
		ret = Round( in );
		// handle potential overflow
		if (ret >= 2048) ret = 2047;
		if (neg) ret &= 0x0800;
		return ret;
	}
}

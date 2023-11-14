#include "MDM_OF4.h"
#include "IOM_DIL.h"
#include "IOM_DIH.h"
#include "IOM_AIS.h"


namespace dps
{
	constexpr unsigned short OF4_ADDR = 23;


	MDM_OF4::MDM_OF4( AtlantisSubsystemDirector* _director, BusManager* pBusManager ):MDM( _director, "MDM_OF4", pBusManager, OF4_ADDR, BUS_PL1, BUS_PL2 )
	{
		// HACK no PCMMU yet, so connect to PL busses

		iom.push_back( new IOM_DIL( "OF4", 0 ) );
		iom.push_back( new IOM_AIS( "OF4", 1 ) );
		iom.push_back( new IOM_DIH( "OF4", 2 ) );
		iom.push_back( new IOM_DIL( "OF4", 3 ) );
		iom.push_back( new IOM_DIH( "OF4", 4 ) );
		iom.push_back( new IOM_DIH( "OF4", 5 ) );
		iom.push_back( new IOM_AIS( "OF4", 6 ) );
		iom.push_back( new IOM_DIH( "OF4", 7 ) );
		iom.push_back( new IOM_DIL( "OF4", 8 ) );
		iom.push_back( new IOM_AIS( "OF4", 9 ) );
		iom.push_back( new IOM_DIH( "OF4", 10 ) );
		iom.push_back( new IOM_AIS( "OF4", 11 ) );
		iom.push_back( new IOM_DIH( "OF4", 12 ) );
		iom.push_back( new IOM_DIH( "OF4", 13 ) );
		iom.push_back( new IOM_AIS( "OF4", 14 ) );
		iom.push_back( new IOM_DIH( "OF4", 15 ) );
		return;
	}

	MDM_OF4::~MDM_OF4()
	{
		return;
	}

	void MDM_OF4::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 13 );
		Power2.Connect( pBundle, 15 );

		for (auto x : iom) x->Connect( BundleManager() );
		return;
	}
}

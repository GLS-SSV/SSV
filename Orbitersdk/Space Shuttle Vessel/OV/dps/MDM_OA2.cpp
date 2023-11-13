#include "MDM_OA2.h"
#include "IOM_DIL.h"
#include "IOM_DIH.h"
#include "IOM_AIS.h"


namespace dps
{
	constexpr unsigned short OA2_ADDR = 25;


	MDM_OA2::MDM_OA2( AtlantisSubsystemDirector* _director, BusManager* pBusManager ):MDM( _director, "MDM_OA2", pBusManager, OA2_ADDR, BUS_PL1, BUS_PL2 )
	{
		// HACK no PCMMU yet, so connect to PL busses

		iom.push_back( new IOM_AIS( "OA2", 0 ) );
		iom.push_back( new IOM_DIH( "OA2", 1 ) );
		iom.push_back( new IOM_AIS( "OA2", 2 ) );
		iom.push_back( new IOM_DIL( "OA2", 3 ) );
		iom.push_back( new IOM_AIS( "OA2", 4 ) );
		iom.push_back( new IOM_DIH( "OA2", 5 ) );
		iom.push_back( new IOM_AIS( "OA2", 6 ) );
		iom.push_back( new IOM_DIH( "OA2", 7 ) );
		iom.push_back( new IOM_DIL( "OA2", 8 ) );
		iom.push_back( new IOM_AIS( "OA2", 9 ) );
		iom.push_back( new IOM_DIH( "OA2", 10 ) );
		iom.push_back( new IOM_AIS( "OA2", 11 ) );
		iom.push_back( new IOM_DIH( "OA2", 12 ) );
		iom.push_back( new IOM_AIS( "OA2", 13 ) );
		iom.push_back( new IOM_DIL( "OA2", 14 ) );
		iom.push_back( new IOM_AIS( "OA2", 15 ) );
		return;
	}

	MDM_OA2::~MDM_OA2()
	{
		return;
	}

	void MDM_OA2::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 11 );
		Power2.Connect( pBundle, 11 );

		for (auto x : iom) x->Connect( BundleManager() );
		return;
	}
}

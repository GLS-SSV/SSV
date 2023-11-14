#include "MDM_OA3.h"
#include "IOM_DIL.h"
#include "IOM_DIH.h"
#include "IOM_AIS.h"


namespace dps
{
	constexpr unsigned short OA3_ADDR = 26;


	MDM_OA3::MDM_OA3( AtlantisSubsystemDirector* _director, BusManager* pBusManager ):MDM( _director, "MDM_OA3", pBusManager, OA3_ADDR, BUS_PL1, BUS_PL2 )
	{
		// HACK no PCMMU yet, so connect to PL busses

		iom.push_back( new IOM_AIS( "OA3", 0 ) );
		iom.push_back( new IOM_DIH( "OA3", 1 ) );
		iom.push_back( new IOM_AIS( "OA3", 2 ) );
		iom.push_back( new IOM_DIL( "OA3", 3 ) );
		iom.push_back( new IOM_AIS( "OA3", 4 ) );
		iom.push_back( new IOM_DIH( "OA3", 5 ) );
		iom.push_back( new IOM_AIS( "OA3", 6 ) );
		iom.push_back( new IOM_DIH( "OA3", 7 ) );
		iom.push_back( new IOM_DIL( "OA3", 8 ) );
		iom.push_back( new IOM_AIS( "OA3", 9 ) );
		iom.push_back( new IOM_DIH( "OA3", 10 ) );
		iom.push_back( new IOM_AIS( "OA3", 11 ) );
		iom.push_back( new IOM_DIH( "OA3", 12 ) );
		iom.push_back( new IOM_AIS( "OA3", 13 ) );
		iom.push_back( new IOM_DIL( "OA3", 14 ) );
		iom.push_back( new IOM_AIS( "OA3", 15 ) );
		return;
	}

	MDM_OA3::~MDM_OA3()
	{
		return;
	}

	void MDM_OA3::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 11 );
		Power2.Connect( pBundle, 11 );

		for (auto x : iom) x->Connect( BundleManager() );
		return;
	}
}

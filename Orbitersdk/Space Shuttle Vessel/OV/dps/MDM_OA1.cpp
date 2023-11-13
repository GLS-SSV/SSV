#include "MDM_OA1.h"
#include "IOM_DIL.h"
#include "IOM_DIH.h"
#include "IOM_AIS.h"


namespace dps
{
	constexpr unsigned short OA1_ADDR = 24;


	MDM_OA1::MDM_OA1( AtlantisSubsystemDirector* _director, BusManager* pBusManager ):MDM( _director, "MDM_OA1", pBusManager, OA1_ADDR, BUS_PL1, BUS_PL2 )
	{
		// HACK no PCMMU yet, so connect to PL busses

		iom.push_back( new IOM_AIS( "OA1", 0 ) );
		iom.push_back( new IOM_DIH( "OA1", 1 ) );
		iom.push_back( new IOM_AIS( "OA1", 2 ) );
		iom.push_back( new IOM_DIL( "OA1", 3 ) );
		iom.push_back( new IOM_AIS( "OA1", 4 ) );
		iom.push_back( new IOM_DIH( "OA1", 5 ) );
		iom.push_back( new IOM_AIS( "OA1", 6 ) );
		iom.push_back( new IOM_DIH( "OA1", 7 ) );
		iom.push_back( new IOM_DIL( "OA1", 8 ) );
		iom.push_back( new IOM_AIS( "OA1", 9 ) );
		iom.push_back( new IOM_DIH( "OA1", 10 ) );
		iom.push_back( new IOM_AIS( "OA1", 11 ) );
		iom.push_back( new IOM_DIH( "OA1", 12 ) );
		iom.push_back( new IOM_AIS( "OA1", 13 ) );
		iom.push_back( new IOM_DIL( "OA1", 14 ) );
		iom.push_back( new IOM_AIS( "OA1", 15 ) );
		return;
	}

	MDM_OA1::~MDM_OA1()
	{
		return;
	}

	void MDM_OA1::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 11 );
		Power2.Connect( pBundle, 11 );

		for (auto x : iom) x->Connect( BundleManager() );
		return;
	}
}

#include "MDM_OF1.h"
#include "IOM_DIL.h"
#include "IOM_DIH.h"
#include "IOM_AIS.h"
#include "IOM_AID.h"
#include "IOM_SIO.h"


namespace dps
{
	constexpr unsigned short OF1_ADDR = 20;


	MDM_OF1::MDM_OF1( AtlantisSubsystemDirector* _director, BusManager* pBusManager ):MDM( _director, "MDM_OF1", pBusManager, OF1_ADDR, BUS_PL1, BUS_PL2 )
	{
		// HACK no PCMMU yet, so connect to PL busses

		iom.push_back( new IOM_SIO( "OF1", 0 ) );
		iom.push_back( new IOM_AIS( "OF1", 1 ) );
		iom.push_back( new IOM_DIL( "OF1", 2 ) );
		iom.push_back( new IOM_AIS( "OF1", 3 ) );
		iom.push_back( new IOM_DIH( "OF1", 4 ) );
		iom.push_back( new IOM_AIS( "OF1", 5 ) );
		iom.push_back( new IOM_DIH( "OF1", 6 ) );
		iom.push_back( new IOM_AIS( "OF1", 7 ) );
		iom.push_back( new IOM_AID( "OF1", 8 ) );
		iom.push_back( new IOM_AIS( "OF1", 9 ) );
		iom.push_back( new IOM_DIL( "OF1", 10 ) );
		iom.push_back( new IOM_AIS( "OF1", 11 ) );
		iom.push_back( new IOM_DIH( "OF1", 12 ) );
		iom.push_back( new IOM_AIS( "OF1", 13 ) );
		iom.push_back( new IOM_DIH( "OF1", 14 ) );
		iom.push_back( new IOM_AIS( "OF1", 15 ) );
		return;
	}

	MDM_OF1::~MDM_OF1()
	{
		return;
	}

	void MDM_OF1::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 12 );
		Power2.Connect( pBundle, 14 );

		for (auto x : iom) x->Connect( BundleManager() );
		return;
	}
}

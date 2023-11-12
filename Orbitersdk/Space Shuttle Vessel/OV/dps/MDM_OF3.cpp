#include "MDM_OF3.h"
#include "IOM_DIL.h"
#include "IOM_DIH.h"
#include "IOM_AIS.h"
#include "IOM_AID.h"
#include "IOM_SIO.h"


namespace dps
{
	constexpr unsigned short OF3_ADDR = 22;


	MDM_OF3::MDM_OF3( AtlantisSubsystemDirector* _director, BusManager* pBusManager ):MDM( _director, "MDM_OF3", pBusManager, OF3_ADDR, BUS_PL1, BUS_PL2 )
	{
		// HACK no PCMMU yet, so connect to PL busses

		iom.push_back( new IOM_SIO( "OF3", 0 ) );
		iom.push_back( new IOM_AIS( "OF3", 1 ) );
		iom.push_back( new IOM_DIL( "OF3", 2 ) );
		iom.push_back( new IOM_AIS( "OF3", 3 ) );
		iom.push_back( new IOM_DIH( "OF3", 4 ) );
		iom.push_back( new IOM_AIS( "OF3", 5 ) );
		iom.push_back( new IOM_DIH( "OF3", 6 ) );
		iom.push_back( new IOM_AIS( "OF3", 7 ) );
		iom.push_back( new IOM_AID( "OF3", 8 ) );
		iom.push_back( new IOM_AIS( "OF3", 9 ) );
		iom.push_back( new IOM_DIL( "OF3", 10 ) );
		iom.push_back( new IOM_AIS( "OF3", 11 ) );
		iom.push_back( new IOM_DIH( "OF3", 12 ) );
		iom.push_back( new IOM_AIS( "OF3", 13 ) );
		iom.push_back( new IOM_DIH( "OF3", 14 ) );
		iom.push_back( new IOM_AIS( "OF3", 15 ) );
		return;
	}

	MDM_OF3::~MDM_OF3()
	{
		return;
	}

	void MDM_OF3::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 13 );
		Power2.Connect( pBundle, 15 );

		for (auto x : iom) x->Connect( BundleManager() );
		return;
	}
}

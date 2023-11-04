#include "MDM_OF2.h"
#include "IOM_DIL.h"
#include "IOM_DIH.h"
#include "IOM_AIS.h"
#include "IOM_AID.h"
#include "IOM_SIO.h"


namespace dps
{
	constexpr unsigned short OF2_ADDR = 21;


	MDM_OF2::MDM_OF2( AtlantisSubsystemDirector* _director, BusManager* pBusManager ):MDM( _director, "MDM_OF2", pBusManager, OF2_ADDR, BUS_PL1, BUS_PL2 )
	{
		// HACK no PCMMU yet, so connect to PL busses

		iom.push_back( new IOM_SIO( "OF2", 0 ) );
		iom.push_back( new IOM_AIS( "OF2", 1 ) );
		iom.push_back( new IOM_DIL( "OF2", 2 ) );
		iom.push_back( new IOM_AIS( "OF2", 3 ) );
		iom.push_back( new IOM_DIH( "OF2", 4 ) );
		iom.push_back( new IOM_AIS( "OF2", 5 ) );
		iom.push_back( new IOM_DIH( "OF2", 6 ) );
		iom.push_back( new IOM_AIS( "OF2", 7 ) );
		iom.push_back( new IOM_AID( "OF2", 8 ) );
		iom.push_back( new IOM_AIS( "OF2", 9 ) );
		iom.push_back( new IOM_DIL( "OF2", 10 ) );
		iom.push_back( new IOM_AIS( "OF2", 11 ) );
		iom.push_back( new IOM_DIH( "OF2", 12 ) );
		iom.push_back( new IOM_AIS( "OF2", 13 ) );
		iom.push_back( new IOM_DIH( "OF2", 14 ) );
		iom.push_back( new IOM_AIS( "OF2", 15 ) );
		return;
	}

	MDM_OF2::~MDM_OF2()
	{
		return;
	}

	void MDM_OF2::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 12 );
		Power2.Connect( pBundle, 14 );

		for (auto x : iom) x->Connect( BundleManager() );
		return;
	}
}

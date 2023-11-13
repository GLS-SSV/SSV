#include "MDM_FA3.h"
#include "IOM_DIL.h"
#include "IOM_DIH.h"
#include "IOM_DOL.h"
#include "IOM_DOH.h"
#include "IOM_AIS.h"
#include "IOM_AID.h"
#include "IOM_AOD.h"


namespace dps
{
	constexpr unsigned short FA3_ADDR = 12;


	MDM_FA3::MDM_FA3( AtlantisSubsystemDirector* _director, BusManager* pBusManager ):MDM( _director, "MDM_FA3", pBusManager, FA3_ADDR, BUS_FC3, BUS_FC7 )
	{
		iom.push_back( new IOM_AOD( "FA3", 0 ) );
		iom.push_back( new IOM_AID( "FA3", 1 ) );
		iom.push_back( new IOM_DOL( "FA3", 2 ) );
		iom.push_back( new IOM_DIH( "FA3", 3 ) );
		iom.push_back( new IOM_AOD( "FA3", 4 ) );
		iom.push_back( new IOM_DIL( "FA3", 5 ) );
		iom.push_back( new IOM_AIS( "FA3", 6 ) );
		iom.push_back( new IOM_DOH( "FA3", 7 ) );
		iom.push_back( new IOM_DIH( "FA3", 8 ) );
		iom.push_back( new IOM_AID( "FA3", 9 ) );
		iom.push_back( new IOM_DOL( "FA3", 10 ) );
		iom.push_back( new IOM_DIH( "FA3", 11 ) );
		iom.push_back( new IOM_DOH( "FA3", 12 ) );
		iom.push_back( new IOM_DIL( "FA3", 13 ) );
		iom.push_back( new IOM_AIS( "FA3", 14 ) );
		iom.push_back( new IOM_DOH( "FA3", 15 ) );
		return;
	}

	MDM_FA3::~MDM_FA3()
	{
		return;
	}

	void MDM_FA3::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 6 );
		Power2.Connect( pBundle, 6 );

		for (auto x : iom) x->Connect( BundleManager() );
		return;
	}
}

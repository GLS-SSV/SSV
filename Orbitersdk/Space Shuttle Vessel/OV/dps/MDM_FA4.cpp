#include "MDM_FA4.h"
#include "IOM_DIL.h"
#include "IOM_DIH.h"
#include "IOM_DOL.h"
#include "IOM_DOH.h"
#include "IOM_AIS.h"
#include "IOM_AID.h"
#include "IOM_AOD.h"


namespace dps
{
	constexpr unsigned short FA4_ADDR = 12;


	MDM_FA4::MDM_FA4( AtlantisSubsystemDirector* _director, BusManager* pBusManager ):MDM( _director, "MDM_FA4", pBusManager, FA4_ADDR, BUS_FC4, BUS_FC8 )
	{
		iom.push_back( new IOM_AOD( "FA4", 0 ) );
		iom.push_back( new IOM_AID( "FA4", 1 ) );
		iom.push_back( new IOM_DOL( "FA4", 2 ) );
		iom.push_back( new IOM_DIH( "FA4", 3 ) );
		iom.push_back( new IOM_AOD( "FA4", 4 ) );
		iom.push_back( new IOM_DIL( "FA4", 5 ) );
		iom.push_back( new IOM_AIS( "FA4", 6 ) );
		iom.push_back( new IOM_DOH( "FA4", 7 ) );
		iom.push_back( new IOM_DIH( "FA4", 8 ) );
		iom.push_back( new IOM_AID( "FA4", 9 ) );
		iom.push_back( new IOM_DOL( "FA4", 10 ) );
		iom.push_back( new IOM_DIH( "FA4", 11 ) );
		iom.push_back( new IOM_DOH( "FA4", 12 ) );
		iom.push_back( new IOM_DIL( "FA4", 13 ) );
		iom.push_back( new IOM_AIS( "FA4", 14 ) );
		iom.push_back( new IOM_DOH( "FA4", 15 ) );
		return;
	}

	MDM_FA4::~MDM_FA4()
	{
		return;
	}

	void MDM_FA4::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 6 );
		Power2.Connect( pBundle, 6 );

		for (auto x : iom) x->Connect( BundleManager() );
		return;
	}
}

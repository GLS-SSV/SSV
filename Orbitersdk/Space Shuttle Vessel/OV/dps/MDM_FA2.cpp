#include "MDM_FA2.h"
#include "IOM_TAC.h"
#include "IOM_DIL.h"
#include "IOM_DIH.h"
#include "IOM_DOL.h"
#include "IOM_DOH.h"
#include "IOM_AIS.h"
#include "IOM_AID.h"
#include "IOM_AOD.h"
#include "IOM_SIO.h"


namespace dps
{
	constexpr unsigned short FA2_ADDR = 12;


	MDM_FA2::MDM_FA2( AtlantisSubsystemDirector* _director, BusManager* pBusManager ):MDM( _director, "MDM_FA2", pBusManager, FA2_ADDR, BUS_FC2, BUS_FC6 )
	{
		iom.push_back( new IOM_AOD( "FA2", 0 ) );
		iom.push_back( new IOM_AID( "FA2", 1 ) );
		iom.push_back( new IOM_DOL( "FA2", 2 ) );
		iom.push_back( new IOM_DIH( "FA2", 3 ) );
		iom.push_back( new IOM_AOD( "FA2", 4 ) );
		iom.push_back( new IOM_DIL( "FA2", 5 ) );
		iom.push_back( new IOM_AIS( "FA2", 6 ) );
		iom.push_back( new IOM_DOH( "FA2", 7 ) );
		iom.push_back( new IOM_DIH( "FA2", 8 ) );
		iom.push_back( new IOM_AID( "FA2", 9 ) );
		iom.push_back( new IOM_DOL( "FA2", 10 ) );
		iom.push_back( new IOM_DIH( "FA2", 11 ) );
		iom.push_back( new IOM_DOH( "FA2", 12 ) );
		iom.push_back( new IOM_DIL( "FA2", 13 ) );
		iom.push_back( new IOM_AIS( "FA2", 14 ) );
		iom.push_back( new IOM_DOH( "FA2", 15 ) );
		return;
	}

	MDM_FA2::~MDM_FA2()
	{
		return;
	}

	void MDM_FA2::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 5 );
		Power2.Connect( pBundle, 5 );

		for (auto x : iom) x->Connect( BundleManager() );
		return;
	}
}

#include "MDM_FA1.h"
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
	constexpr unsigned short FA1_ADDR = 12;


	MDM_FA1::MDM_FA1( AtlantisSubsystemDirector* _director, BusManager* pBusManager ):MDM( _director, "MDM_FA1", pBusManager, FA1_ADDR, BUS_FC1, BUS_FC5 )
	{
		iom.push_back( new IOM_AOD( "FA1", 0 ) );
		iom.push_back( new IOM_AID( "FA1", 1 ) );
		iom.push_back( new IOM_DOL( "FA1", 2 ) );
		iom.push_back( new IOM_DIH( "FA1", 3 ) );
		iom.push_back( new IOM_AOD( "FA1", 4 ) );
		iom.push_back( new IOM_DIL( "FA1", 5 ) );
		iom.push_back( new IOM_AIS( "FA1", 6 ) );
		iom.push_back( new IOM_DOH( "FA1", 7 ) );
		iom.push_back( new IOM_DIH( "FA1", 8 ) );
		iom.push_back( new IOM_AID( "FA1", 9 ) );
		iom.push_back( new IOM_DOL( "FA1", 10 ) );
		iom.push_back( new IOM_DIH( "FA1", 11 ) );
		iom.push_back( new IOM_DOH( "FA1", 12 ) );
		iom.push_back( new IOM_DIL( "FA1", 13 ) );
		iom.push_back( new IOM_AIS( "FA1", 14 ) );
		iom.push_back( new IOM_DOH( "FA1", 15 ) );
		return;
	}

	MDM_FA1::~MDM_FA1()
	{
		return;
	}

	void MDM_FA1::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 4 );
		Power2.Connect( pBundle, 4 );

		for (auto x : iom) x->Connect( BundleManager() );
		return;
	}
}

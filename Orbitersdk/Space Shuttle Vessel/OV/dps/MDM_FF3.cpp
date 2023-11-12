#include "MDM_FF3.h"
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
	constexpr unsigned short FF3_ADDR = 10;


	MDM_FF3::MDM_FF3( AtlantisSubsystemDirector* _director, BusManager* pBusManager ):MDM( _director, "MDM_FF3", pBusManager, FF3_ADDR, BUS_FC3, BUS_FC7 )
	{
		iom.push_back( new IOM_TAC( "FF3", 0 ) );
		iom.push_back( new IOM_AID( "FF3", 1 ) );
		iom.push_back( new IOM_DOH( "FF3", 2 ) );
		iom.push_back( new IOM_SIO( "FF3", 3 ) );
		iom.push_back( new IOM_DIH( "FF3", 4 ) );
		iom.push_back( new IOM_DOL( "FF3", 5 ) );
		iom.push_back( new IOM_DIL( "FF3", 6 ) );
		iom.push_back( new IOM_AIS( "FF3", 7 ) );
		iom.push_back( new IOM_AOD( "FF3", 8 ) );
		iom.push_back( new IOM_DIH( "FF3", 9 ) );
		iom.push_back( new IOM_DOH( "FF3", 10 ) );
		iom.push_back( new IOM_SIO( "FF3", 11 ) );
		iom.push_back( new IOM_DIH( "FF3", 12 ) );
		iom.push_back( new IOM_DOL( "FF3", 13 ) );
		iom.push_back( new IOM_AID( "FF3", 14 ) );
		iom.push_back( new IOM_DIL( "FF3", 15 ) );
		return;
	}

	MDM_FF3::~MDM_FF3()
	{
		return;
	}

	void MDM_FF3::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 2 );
		Power2.Connect( pBundle, 2 );

		for (auto x : iom) x->Connect( BundleManager() );
		return;
	}
}

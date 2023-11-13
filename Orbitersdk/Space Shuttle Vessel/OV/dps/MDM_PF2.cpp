#include "MDM_PF2.h"
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
	constexpr unsigned short PF2_ADDR = 12;


	MDM_PF2::MDM_PF2( AtlantisSubsystemDirector* _director, BusManager* pBusManager ):MDM( _director, "MDM_PF2", pBusManager, PF2_ADDR, BUS_PL1, BUS_PL2 )
	{
		iom.push_back( new IOM_DOL( "PF2", 0 ) );
		iom.push_back( new IOM_AID( "PF2", 1 ) );
		iom.push_back( new IOM_DOH( "PF2", 2 ) );
		iom.push_back( new IOM_DIH( "PF2", 3 ) );
		iom.push_back( new IOM_AID( "PF2", 4 ) );
		iom.push_back( new IOM_DIL( "PF2", 5 ) );
		iom.push_back( new IOM_DIH( "PF2", 6 ) );
		iom.push_back( new IOM_DOH( "PF2", 7 ) );
		iom.push_back( new IOM_SIO( "PF2", 8 ) );
		iom.push_back( new IOM_DIH( "PF2", 9 ) );
		iom.push_back( new IOM_DOL( "PF2", 10 ) );
		iom.push_back( new IOM_AID( "PF2", 11 ) );
		iom.push_back( new IOM_AOD( "PF2", 12 ) );
		iom.push_back( new IOM_DIL( "PF2", 13 ) );
		iom.push_back( new IOM_DOH( "PF2", 14 ) );
		iom.push_back( new IOM_SIO( "PF2", 15 ) );
		return;
	}

	MDM_PF2::~MDM_PF2()
	{
		return;
	}

	void MDM_PF2::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 9 );
		Power2.Connect( pBundle, 9 );

		for (auto x : iom) x->Connect( BundleManager() );
		return;
	}
}

#include "MDM_PF1.h"
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
	constexpr unsigned short PF1_ADDR = 10;


	MDM_PF1::MDM_PF1( AtlantisSubsystemDirector* _director, BusManager* pBusManager ):MDM( _director, "MDM_PF1", pBusManager, PF1_ADDR, BUS_PL1, BUS_PL2 )
	{
		iom.push_back( new IOM_DOL( "PF1", 0 ) );
		iom.push_back( new IOM_AID( "PF1", 1 ) );
		iom.push_back( new IOM_DOH( "PF1", 2 ) );
		iom.push_back( new IOM_DIH( "PF1", 3 ) );
		iom.push_back( new IOM_AID( "PF1", 4 ) );
		iom.push_back( new IOM_DIL( "PF1", 5 ) );
		iom.push_back( new IOM_DIH( "PF1", 6 ) );
		iom.push_back( new IOM_DOH( "PF1", 7 ) );
		iom.push_back( new IOM_SIO( "PF1", 8 ) );
		iom.push_back( new IOM_DIH( "PF1", 9 ) );
		iom.push_back( new IOM_DOL( "PF1", 10 ) );
		iom.push_back( new IOM_AID( "PF1", 11 ) );
		iom.push_back( new IOM_AOD( "PF1", 12 ) );
		iom.push_back( new IOM_DIL( "PF1", 13 ) );
		iom.push_back( new IOM_DOH( "PF1", 14 ) );
		iom.push_back( new IOM_SIO( "PF1", 15 ) );
		return;
	}

	MDM_PF1::~MDM_PF1()
	{
		return;
	}

	void MDM_PF1::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 8 );
		Power2.Connect( pBundle, 8 );

		for (auto x : iom) x->Connect( BundleManager() );
		return;
	}
}

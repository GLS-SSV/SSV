#include "MDM_FF1.h"
#include "IOM_TAC.h"
#include "IOM_DIL.h"
#include "IOM_DIH.h"
#include "IOM_DOL.h"
#include "IOM_DOH.h"
#include "IOM_AIS.h"
#include "IOM_AID.h"
#include "IOM_AOD.h"
#include "IOM_SIO.h"
#include "../gnc/RA.h"
#include <cassert>


namespace dps
{
	constexpr unsigned short FF1_ADDR = 10;


	MDM_FF1::MDM_FF1( AtlantisSubsystemDirector* _director, BusManager* pBusManager ):MDM( _director, "MDM_FF1", pBusManager, FF1_ADDR, BUS_FC1, BUS_FC5 )
	{
		iom.push_back( new IOM_TAC( "FF1", 0 ) );
		iom.push_back( new IOM_AID( "FF1", 1 ) );
		iom.push_back( new IOM_DOH( "FF1", 2 ) );
		iom.push_back( new IOM_SIO( "FF1", 3 ) );
		iom.push_back( new IOM_DIH( "FF1", 4 ) );
		iom.push_back( new IOM_DOL( "FF1", 5 ) );
		iom.push_back( new IOM_DIL( "FF1", 6 ) );
		iom.push_back( new IOM_AIS( "FF1", 7 ) );
		iom.push_back( new IOM_AOD( "FF1", 8 ) );
		iom.push_back( new IOM_DIH( "FF1", 9 ) );
		iom.push_back( new IOM_DOH( "FF1", 10 ) );
		iom.push_back( new IOM_SIO( "FF1", 11 ) );
		iom.push_back( new IOM_DIH( "FF1", 12 ) );
		iom.push_back( new IOM_DOL( "FF1", 13 ) );
		iom.push_back( new IOM_AID( "FF1", 14 ) );
		iom.push_back( new IOM_DIL( "FF1", 15 ) );
		return;
	}

	MDM_FF1::~MDM_FF1()
	{
		return;
	}

	void MDM_FF1::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 0 );
		Power2.Connect( pBundle, 0 );

		for (auto x : iom) x->Connect( BundleManager() );

		gnc::RadarAltimeter* pRA1 = dynamic_cast<gnc::RadarAltimeter*>(director->GetSubsystemByName( "RA1" ));
		assert( (pRA1 != NULL) && "MDM_FF1::Realize.pRA1" );
		dynamic_cast<IOM_TAC*>(iom[0])->ConnectRA( pRA1 );
		return;
	}
}

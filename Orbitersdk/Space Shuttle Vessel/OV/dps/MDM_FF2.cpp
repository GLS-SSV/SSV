#include "MDM_FF2.h"
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
	constexpr unsigned short FF2_ADDR = 10;


	MDM_FF2::MDM_FF2( AtlantisSubsystemDirector* _director, BusManager* pBusManager ):MDM( _director, "MDM_FF2", pBusManager, FF2_ADDR, BUS_FC2, BUS_FC6 )
	{
		iom.push_back( new IOM_TAC( "FF2", 0 ) );
		iom.push_back( new IOM_AID( "FF2", 1 ) );
		iom.push_back( new IOM_DOH( "FF2", 2 ) );
		iom.push_back( new IOM_SIO( "FF2", 3 ) );
		iom.push_back( new IOM_DIH( "FF2", 4 ) );
		iom.push_back( new IOM_DOL( "FF2", 5 ) );
		iom.push_back( new IOM_DIL( "FF2", 6 ) );
		iom.push_back( new IOM_AIS( "FF2", 7 ) );
		iom.push_back( new IOM_AOD( "FF2", 8 ) );
		iom.push_back( new IOM_DIH( "FF2", 9 ) );
		iom.push_back( new IOM_DOH( "FF2", 10 ) );
		iom.push_back( new IOM_SIO( "FF2", 11 ) );
		iom.push_back( new IOM_DIH( "FF2", 12 ) );
		iom.push_back( new IOM_DOL( "FF2", 13 ) );
		iom.push_back( new IOM_AID( "FF2", 14 ) );
		iom.push_back( new IOM_DIL( "FF2", 15 ) );
		return;
	}

	MDM_FF2::~MDM_FF2()
	{
		return;
	}

	void MDM_FF2::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 1 );
		Power2.Connect( pBundle, 1 );

		for (auto x : iom) x->Connect( BundleManager() );

		gnc::RadarAltimeter* pRA2 = dynamic_cast<gnc::RadarAltimeter*>(director->GetSubsystemByName( "RA2" ));
		assert( (pRA2 != NULL) && "MDM_FF2::Realize.pRA2" );
		dynamic_cast<IOM_TAC*>(iom[0])->ConnectRA( pRA2 );
		return;
	}
}

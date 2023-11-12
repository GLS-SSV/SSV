#include "MDM_FF4.h"
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
	constexpr unsigned short FF4_ADDR = 10;


	MDM_FF4::MDM_FF4( AtlantisSubsystemDirector* _director, BusManager* pBusManager ):MDM( _director, "MDM_FF4", pBusManager, FF4_ADDR, BUS_FC4, BUS_FC8 )
	{
		iom.push_back( new IOM_TAC( "FF4", 0 ) );
		iom.push_back( new IOM_AID( "FF4", 1 ) );
		iom.push_back( new IOM_DOH( "FF4", 2 ) );
		iom.push_back( new IOM_SIO( "FF4", 3 ) );
		iom.push_back( new IOM_DIH( "FF4", 4 ) );
		iom.push_back( new IOM_DOL( "FF4", 5 ) );
		iom.push_back( new IOM_DIL( "FF4", 6 ) );
		iom.push_back( new IOM_AIS( "FF4", 7 ) );
		iom.push_back( new IOM_AOD( "FF4", 8 ) );
		iom.push_back( new IOM_DIH( "FF4", 9 ) );
		iom.push_back( new IOM_DOH( "FF4", 10 ) );
		iom.push_back( new IOM_SIO( "FF4", 11 ) );
		iom.push_back( new IOM_DIH( "FF4", 12 ) );
		iom.push_back( new IOM_DOL( "FF4", 13 ) );
		iom.push_back( new IOM_AID( "FF4", 14 ) );
		iom.push_back( new IOM_DIL( "FF4", 15 ) );
		return;
	}

	MDM_FF4::~MDM_FF4()
	{
		return;
	}

	void MDM_FF4::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 3 );
		Power2.Connect( pBundle, 3 );

		for (auto x : iom) x->Connect( BundleManager() );
		return;
	}
}

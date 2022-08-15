/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/01/20   GLS
2021/06/28   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/12/27   GLS
2021/12/28   GLS
2021/12/30   GLS
2022/01/10   GLS
2022/03/21   GLS
********************************************/
#include "RHC.h"
#include "Atlantis.h"
#include <cassert>


RHC::RHC( AtlantisSubsystemDirector* _director, const string& _ident, unsigned short ID ):AtlantisSubsystem( _director, _ident )
{
	assert( ((ID == 1) || (ID == 2) || (ID == 3)) && "RHC::RHC:ID" );
	this->ID = ID;
	return;
}

RHC::~RHC( void )
{
}

void RHC::Realize( void )
{
	DiscreteBundle* pBundleA;
	DiscreteBundle* pBundleB;

	if (ID == 1)
	{
		pBundleA = BundleManager()->CreateBundle( "LeftRHCTHC_A", 16 );
		pBundleB = BundleManager()->CreateBundle( "LeftRHCTHC_B", 16 );
	}
	else if (ID == 2)
	{
		pBundleA = BundleManager()->CreateBundle( "RightRHC_A", 16 );
		pBundleB = BundleManager()->CreateBundle( "RightRHC_B", 16 );
	}
	else
	{
		pBundleA = BundleManager()->CreateBundle( "AftRHCTHC_A", 16 );
		pBundleB = NULL;
	}
	for (int i = 0; i < 9; i++) dopRHC[i].Connect( pBundleA, i );

	if (ID != 3)
	{
		for (int i = 9; i < 16; i++) dopRHCTrim[i - 9].Connect( pBundleA, i );
		dopRHCTrim[7].Connect( pBundleB, 0 );
	}

	pBundleA = BundleManager()->CreateBundle( "DDU_POWER", 16 );
	dipPower.Connect( pBundleA, 3 + (4 * (ID - 1)) );
	return;
}

void RHC::OnPreStep( double simt, double simdt, double mjd )
{
	if (dipPower.IsSet())
	{
		double pitch = 0.0;
		double roll = 0.0;
		double yaw = 0.0;
		short pitchtrim = 0;
		short rolltrim = 0;

		STS()->GetRHCPosition( ID, pitch, roll, yaw, pitchtrim, rolltrim );

		dopRHC[0].SetLine( static_cast<float>(pitch) );
		dopRHC[1].SetLine( static_cast<float>(pitch) );
		dopRHC[2].SetLine( static_cast<float>(pitch) );

		dopRHC[3].SetLine( static_cast<float>(roll) );
		dopRHC[4].SetLine( static_cast<float>(roll) );
		dopRHC[5].SetLine( static_cast<float>(roll) );

		dopRHC[6].SetLine( static_cast<float>(yaw) );
		dopRHC[7].SetLine( static_cast<float>(yaw) );
		dopRHC[8].SetLine( static_cast<float>(yaw) );

		if (ID != 3)
		{
			dopRHCTrim[0].SetLine( (pitchtrim == 1) ? 5.0f : 0.0f );
			dopRHCTrim[1].SetLine( (pitchtrim == 1) ? 5.0f : 0.0f );
			dopRHCTrim[2].SetLine( (pitchtrim == -1) ? 5.0f : 0.0f );
			dopRHCTrim[3].SetLine( (pitchtrim == -1) ? 5.0f : 0.0f );

			dopRHCTrim[4].SetLine( (rolltrim == 1) ? 5.0f : 0.0f );
			dopRHCTrim[5].SetLine( (rolltrim == 1) ? 5.0f : 0.0f );
			dopRHCTrim[6].SetLine( (rolltrim == -1) ? 5.0f : 0.0f );
			dopRHCTrim[7].SetLine( (rolltrim == -1) ? 5.0f : 0.0f );
		}
	}
	else
	{
		for (auto &x : dopRHC) x.ResetLine();
		for (auto &x : dopRHCTrim) x.ResetLine();
	}
	return;
}

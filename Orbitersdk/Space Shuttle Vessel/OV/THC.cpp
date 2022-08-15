/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/01/20   GLS
2021/06/28   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/12/27   GLS
2021/12/30   GLS
2022/06/04   GLS
2022/08/05   GLS
********************************************/
#include "THC.h"
#include "Atlantis.h"
#include <cassert>


THC::THC( AtlantisSubsystemDirector* _director, const string& _ident, unsigned short ID ):AtlantisSubsystem( _director, _ident )
{
	assert( ((ID == 1) || (ID == 3)) && "THC::THC:ID" );
	this->ID = ID;
	return;
}

THC::~THC( void )
{
}

void THC::Realize( void )
{
	DiscreteBundle* pBundleB;
	DiscreteBundle* pBundleC;

	if (ID == 1)
	{
		pBundleB = BundleManager()->CreateBundle( "LeftRHCTHC_B", 16 );
		pBundleC = BundleManager()->CreateBundle( "LeftRHCTHC_C", 16 );
	}
	else
	{
		pBundleB = BundleManager()->CreateBundle( "AftRHCTHC_B", 16 );
		pBundleC = BundleManager()->CreateBundle( "AftRHCTHC_C", 16 );
	}
	for (int i = 14; i < 16; i++) dopTHC[i - 14].Connect( pBundleB, i );
	for (int i = 0; i < 16; i++) dopTHC[i + 2].Connect( pBundleC, i );

	pBundleB = BundleManager()->CreateBundle( "DDU_POWER", 16 );
	dipPower.Connect( pBundleB, 3 + (4 * (ID - 1)) );
	return;
}

void THC::OnPreStep( double simt, double simdt, double mjd )
{
	if (dipPower.IsSet())
	{
		short X = 0;
		short Y = 0;
		short Z = 0;

		STS()->GetTHCPosition( ID, X, Y, Z );

		dopTHC[0].SetLine( (X == 1) ? 15.0f : 0.0f );
		dopTHC[1].SetLine( (X == 1) ? 15.0f : 0.0f );
		dopTHC[2].SetLine( (X == 1) ? 15.0f : 0.0f );
		dopTHC[3].SetLine( (X == -1) ? 15.0f : 0.0f );
		dopTHC[4].SetLine( (X == -1) ? 15.0f : 0.0f );
		dopTHC[5].SetLine( (X == -1) ? 15.0f : 0.0f );

		dopTHC[6].SetLine( (Y == 1) ? 15.0f : 0.0f );
		dopTHC[7].SetLine( (Y == 1) ? 15.0f : 0.0f );
		dopTHC[8].SetLine( (Y == 1) ? 15.0f : 0.0f );
		dopTHC[9].SetLine( (Y == -1) ? 15.0f : 0.0f );
		dopTHC[10].SetLine( (Y == -1) ? 15.0f : 0.0f );
		dopTHC[11].SetLine( (Y == -1) ? 15.0f : 0.0f );

		dopTHC[12].SetLine( (Z == 1) ? 15.0f : 0.0f );
		dopTHC[13].SetLine( (Z == 1) ? 15.0f : 0.0f );
		dopTHC[14].SetLine( (Z == 1) ? 15.0f : 0.0f );
		dopTHC[15].SetLine( (Z == -1) ? 15.0f : 0.0f );
		dopTHC[16].SetLine( (Z == -1) ? 15.0f : 0.0f );
		dopTHC[17].SetLine( (Z == -1) ? 15.0f : 0.0f );
	}
	else for (auto &x : dopTHC) x.ResetLine();
	return;
}

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
2023/11/11   GLS
2025/07/20   GLS
2026/09/18   GLS
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
	DiscreteBundle* pBundle;

	if (ID == 1)
	{
		// left
		pBundle = BundleManager()->CreateBundle( "MDM_FF1_IOM6_CH1", 16 );
		dopRHCTrim[0].Connect( pBundle, 1 );
		dopRHCTrim[2].Connect( pBundle, 2 );
		dopRHCTrim[4].Connect( pBundle, 3 );
		dopRHCTrim[6].Connect( pBundle, 4 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF2_IOM6_CH1", 16 );
		dopRHCTrim[1].Connect( pBundle, 1 );
		dopRHCTrim[3].Connect( pBundle, 2 );
		dopRHCTrim[5].Connect( pBundle, 3 );
		dopRHCTrim[7].Connect( pBundle, 4 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF1_IOM1_HI", 16 );
		dopRHC[3].Connect( pBundle, 0 );
		dopRHC[0].Connect( pBundle, 1 );
		dopRHC[6].Connect( pBundle, 2 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF2_IOM1_HI", 16 );
		dopRHC[4].Connect( pBundle, 0 );
		dopRHC[1].Connect( pBundle, 1 );
		dopRHC[7].Connect( pBundle, 2 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM1_HI", 16 );
		dopRHC[5].Connect( pBundle, 0 );
		dopRHC[2].Connect( pBundle, 1 );
		dopRHC[8].Connect( pBundle, 2 );
	}
	else if (ID == 2)
	{
		// right
		pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM15_CH1", 16 );
		dopRHCTrim[0].Connect( pBundle, 1 );
		dopRHCTrim[2].Connect( pBundle, 2 );
		dopRHCTrim[4].Connect( pBundle, 3 );
		dopRHCTrim[6].Connect( pBundle, 4 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF4_IOM15_CH1", 16 );
		dopRHCTrim[1].Connect( pBundle, 1 );
		dopRHCTrim[3].Connect( pBundle, 2 );
		dopRHCTrim[5].Connect( pBundle, 3 );
		dopRHCTrim[7].Connect( pBundle, 4 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF2_IOM14_HI", 16 );
		dopRHC[3].Connect( pBundle, 0 );
		dopRHC[0].Connect( pBundle, 1 );
		dopRHC[6].Connect( pBundle, 2 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM14_HI", 16 );
		dopRHC[4].Connect( pBundle, 0 );
		dopRHC[1].Connect( pBundle, 1 );
		dopRHC[7].Connect( pBundle, 2 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF4_IOM14_HI", 16 );
		dopRHC[5].Connect( pBundle, 0 );
		dopRHC[2].Connect( pBundle, 1 );
		dopRHC[8].Connect( pBundle, 2 );
	}
	else
	{
		// aft
		pBundle = BundleManager()->CreateBundle( "MDM_FF1_IOM1_HI", 16 );
		dopRHC[3].Connect( pBundle, 5 );
		dopRHC[0].Connect( pBundle, 6 );
		dopRHC[6].Connect( pBundle, 7 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF2_IOM1_HI", 16 );
		dopRHC[4].Connect( pBundle, 5 );
		dopRHC[1].Connect( pBundle, 6 );
		dopRHC[7].Connect( pBundle, 7 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM1_HI", 16 );
		dopRHC[5].Connect( pBundle, 5 );
		dopRHC[2].Connect( pBundle, 6 );
		dopRHC[8].Connect( pBundle, 7 );
	}

	pBundle = BundleManager()->CreateBundle( "DDU_POWER", 16 );
	dipPower.Connect( pBundle, 3 + (4 * (ID - 1)) );
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

		// limit output voltage to match position limit voltage to MDM input voltage
		dopRHC[0].SetLine( static_cast<float>(pitch * 5.11) );
		dopRHC[1].SetLine( static_cast<float>(pitch * 5.11) );
		dopRHC[2].SetLine( static_cast<float>(pitch * 5.11) );

		dopRHC[3].SetLine( static_cast<float>(roll * 5.11) );
		dopRHC[4].SetLine( static_cast<float>(roll * 5.11) );
		dopRHC[5].SetLine( static_cast<float>(roll * 5.11) );

		dopRHC[6].SetLine( static_cast<float>(yaw * 5.11) );
		dopRHC[7].SetLine( static_cast<float>(yaw * 5.11) );
		dopRHC[8].SetLine( static_cast<float>(yaw * 5.11) );

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

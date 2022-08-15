/******* SSV File Modification Notice *******
Date         Developer
2020/04/07   GLS
2020/06/20   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/08/05   GLS
********************************************/
#include "IntAirlock.h"
#include <EngConst.h>


namespace eva_docking
{
	constexpr double INTAL_MASS = 825.0 * LBM2KG;// empty [kg]
	constexpr VECTOR3 INTAL_CG = {0.0, -1.4431, 10.4468};// (approx) Xo543.0 Yo+0.0 Zo+360.0


	IntAirlock::IntAirlock( AtlantisSubsystemDirector* _director ):AtlantisSubsystem( _director, "InternalAirlock" )
	{
	}

	IntAirlock::~IntAirlock()
	{
	}

	double IntAirlock::GetSubsystemMass( void ) const
	{
		return INTAL_MASS;
	}

	bool IntAirlock::GetSubsystemCoG( VECTOR3& CoG ) const
	{
		CoG = INTAL_CG;
		return true;
	}
};
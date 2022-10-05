/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/06/20   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "OMS.h"
#include "../Atlantis.h"
#include <cassert>


namespace oms
{
	OMS::OMS( AtlantisSubsystemDirector* _director, const string& _ident, unsigned int ID ):AtlantisSubsystem( _director, _ident )
	{
		assert( (ID <= 1) && "OMS::OMS.ID" );
		this->ID = ID;
		return;
	}

	OMS::~OMS( void )
	{
	}

	void OMS::Realize( void )
	{
		DiscreteBundle* pBundle;
		if (ID == 0) pBundle = BundleManager()->CreateBundle( "LOMS", 4 );
		else pBundle = BundleManager()->CreateBundle( "ROMS", 4 );

		OMS_Arm.Connect( pBundle, 0 );
		OMS_ArmPress.Connect( pBundle, 1 );
		OMS_Vlv_Coil.Connect( pBundle, 2 );
		OMS_Eng_Vlv.Connect( pBundle, 3 );
		return;
	}

	bool OMS::OnParseLine( const char* line )
	{
		return false;
	}

	void OMS::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	void OMS::OnPreStep( double simt, double simdt, double mjd )
	{
		STS()->SetOMSThrustLevel( ID, 1.0 * (((OMS_Arm | OMS_ArmPress) & OMS_Eng_Vlv) & OMS_Vlv_Coil) );
		return;
	}
}

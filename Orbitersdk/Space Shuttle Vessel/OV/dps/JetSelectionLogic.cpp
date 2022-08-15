/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
********************************************/
#include "JetSelectionLogic.h"
#include "..\Atlantis.h"


namespace dps
{
	JetSelectionLogic::JetSelectionLogic( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "JetSelectionLogic" )
	{
		return;
	}

	JetSelectionLogic::~JetSelectionLogic( void )
	{
		return;
	}

	void JetSelectionLogic::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "THRUSTER_CMD", 16 );
		RCSPitchCommand.Connect( pBundle, 0 );
		RCSYawCommand.Connect( pBundle, 1 );
		RCSRollCommand.Connect( pBundle, 2 );
		return;
	}

	void JetSelectionLogic::OnPostStep( double simt, double simdt, double mjd )
	{
		short UXCMD = ReadCOMPOOL_IS( SCP_UXCMD );
		short UYCMD = ReadCOMPOOL_IS( SCP_UYCMD );
		short UZCMD = ReadCOMPOOL_IS( SCP_UZCMD );

		RCSRollCommand.SetLine( static_cast<float>(UXCMD / 8.0) );// 8
		RCSPitchCommand.SetLine( static_cast<float>(UYCMD / 9.5) );// 10 up, 9 dn, avg 9.5
		RCSYawCommand.SetLine( static_cast<float>(UZCMD / 6.0) );// 6
		return;
	}

	bool JetSelectionLogic::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			/*case 102:
			case 103:
			case 104:
			case 105:
			case 106:
			case 201:
			case 202:
			case 301:
			case 302:
			case 303:*/
			case 304:
			case 305:
			/*case 601:
			case 602:
			case 603:
			case 801:*/
				return true;
			default:
				return false;
		}
	}
}
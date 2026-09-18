/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/09/29   GLS
2022/12/23   GLS
2026/09/18   GLS
********************************************/
#include "JetSelectionLogic.h"


namespace dps
{
	JetSelectionLogic::JetSelectionLogic( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "JetSelectionLogic" )
	{
		{
			DiscreteBundle* pBundle = BundleManager()->CreateBundle( "THRUSTER_CMD", 16 );
			RCSPitchCommand.Connect( pBundle, 0 );
			RCSYawCommand.Connect( pBundle, 1 );
			RCSRollCommand.Connect( pBundle, 2 );
		}
		return;
	}

	JetSelectionLogic::~JetSelectionLogic( void )
	{
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
}

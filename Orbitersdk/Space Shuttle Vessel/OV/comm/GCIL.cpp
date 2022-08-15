/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/12/30   GLS
2022/08/05   GLS
********************************************/
#include "GCIL.h"
#include "..\Atlantis.h"


namespace comm
{
	GCIL::GCIL( AtlantisSubsystemDirector *_direct ):AtlantisSubsystem( _direct, "GCIL" )
	{
	}

	GCIL::~GCIL()
	{
	}

	void GCIL::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "A1U_SWITCHES_B", 16 );
		pControl_Command.Connect( pBundle, 0 );
		pSteeringMode_GPC.Connect( pBundle, 1 );
		pSteeringMode_GPCDesig.Connect( pBundle, 2 );
		pSteeringMode_AutoTrack.Connect( pBundle, 3 );
		pSteeringMode_ManSlew.Connect( pBundle, 4 );
		pPower_Off.Connect( pBundle, 5 );
		pPower_On.Connect( pBundle, 6 );
		pMode_COMM.Connect( pBundle, 7 );
		pMode_RDRCOOP.Connect( pBundle, 8 );

		pBundle = BundleManager()->CreateBundle( "GCIL_EA1", 16 );
		COMM_ON.Connect( pBundle, 0 );
		RDR_STANDBY.Connect( pBundle, 1 );
		COMM_STANDBY.Connect( pBundle, 2 );
		RDR_ON.Connect( pBundle, 3 );
		ANT_STRG_GPC.Connect( pBundle, 4 );
		ANT_STRG_GPC_DESIG.Connect( pBundle, 5 );
		ANT_STRG_AUTO_TRK.Connect( pBundle, 6 );
		ANT_STRG_MAN_SLEW.Connect( pBundle, 7 );
	}

	void GCIL::OnPreStep( double simt, double simdt, double mjd )
	{
		if (pControl_Command.IsSet())
		{
			// control command
			// TODO ground commands
			COMM_ON.ResetLine();
			RDR_STANDBY.ResetLine();
			COMM_STANDBY.ResetLine();
			RDR_ON.ResetLine();
			ANT_STRG_GPC.ResetLine();
			ANT_STRG_GPC_DESIG.ResetLine();
			ANT_STRG_AUTO_TRK.ResetLine();
			ANT_STRG_MAN_SLEW.ResetLine();
		}
		else
		{
			// control panel
			COMM_ON.SetLine( 5.0f * (int)(pPower_On && pMode_COMM) );
			RDR_STANDBY.SetLine( 5.0f * (int)(!(pPower_Off || pPower_On) && (pMode_RDRCOOP || !(pMode_COMM || pMode_RDRCOOP))) );
			COMM_STANDBY.SetLine( 5.0f * (int)(!(pPower_Off || pPower_On) && pMode_COMM) );
			RDR_ON.SetLine( 5.0f * (int)(pPower_On && !pMode_COMM) );
			ANT_STRG_GPC.SetLine( 5.0f * (int)(pPower_On && pSteeringMode_GPC) );
			ANT_STRG_GPC_DESIG.SetLine( 5.0f * (int)(pPower_On && pSteeringMode_GPCDesig) );
			ANT_STRG_AUTO_TRK.SetLine( 5.0f * (int)(pPower_On && pSteeringMode_AutoTrack) );
			ANT_STRG_MAN_SLEW.SetLine( 5.0f * (int)(pPower_On && pSteeringMode_ManSlew) );
		}
		return;
	}

};
#include "ORB_THREE_AX_RHC_SOP.h"
#include "TWO_AX_RHC_SOP.h"
#include "RHC_RM.h"
#include <cassert>
#include <MathSSV.h>


namespace dps
{
	// constants
	constexpr float SSPHYS1 = 21.161f;// RHC PITCH SOFT STOP 1 (V97U6227C) [deg]
	constexpr float SSPHYS2 = 21.171f;// RHC PITCH SOFT STOP 2 (V97U6228C) [deg]
	constexpr float SSRHYS1 = 21.166f;// RHC ROLL SOFT STOP 1 (V97U6229C) [deg]
	constexpr float SSRHYS2 = 21.176f;// RHC ROLL SOFT STOP 2 (V97U6230C) [deg]
	constexpr float SSYHYS1 = 11.407f;// RHC YAW SOFT STOP 1 (V97U6231C) [deg]
	constexpr float SSYHYS2 = 11.417f;// RHC YAW SOFT STOP 2 (V97U6232C) [deg]


	ORB_THREE_AX_RHC_SOP::ORB_THREE_AX_RHC_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "ORB_THREE_AX_RHC_SOP" )
	{
		return;
	}

	ORB_THREE_AX_RHC_SOP::~ORB_THREE_AX_RHC_SOP( void )
	{
		return;
	}

	void ORB_THREE_AX_RHC_SOP::Realize( void )
	{
		pRHC_RM = dynamic_cast<RHC_RM*>(FindSoftware( "RHC_RM" ));
		assert( (pRHC_RM != NULL) && "ORB_THREE_AX_RHC_SOP::Realize.pRHC_RM" );
		return;
	}

	void ORB_THREE_AX_RHC_SOP::OnPreStep( double simt, double simdt, double mjd )
	{
		ORB_3_COMP();
		ORB_3_VALID();
		ORB_3_DB();
		RHC_SCALAR_TRANS();
		ORB_3_STA_SEL();
		ORB_3_DETENT();
		RHC_INT_TRANS();
		ORB_INT_STA_SEL();
		ORB_3_SOFT_STOP();
		RHC_DISC_TRANS();
		ORB_DISC_STA_SEC();
		return;
	}

	bool ORB_THREE_AX_RHC_SOP::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 201:
			case 202:
				return true;
			default:
				return false;
		}
	}

	void ORB_THREE_AX_RHC_SOP::ORB_3_COMP( void )
	{
		//_3_AX_COMP();
		// HACK code copied to here

		// TODO use proper source and conversion to degrees
		double L_P = 0.0;
		double L_R = 0.0;
		double L_Y = 0.0;
		double R_P = 0.0;
		double R_R = 0.0;
		double R_Y = 0.0;
		double A_P = 0.0;
		double A_R = 0.0;
		double A_Y = 0.0;

		// get data from RM
		pRHC_RM->GetRHCData_L( L_P, L_R, L_Y );
		pRHC_RM->GetRHCData_R( R_P, R_R, R_Y );
		pRHC_RM->GetRHCData_A( A_P, A_R, A_Y );

		// convert to degrees
		DACC = static_cast<float>(L_R * 24.3);// [-24.3, +24.3]
		DAPC = static_cast<float>(R_R * 24.3);// [-24.3, +24.3]
		DAAC = static_cast<float>(A_R * 24.3);// [-24.3, +24.3]
		DECC = static_cast<float>(L_P * 24.3);// [-24.3, +24.3]
		DEPC = static_cast<float>(R_P * 24.3);// [-24.3, +24.3]
		DEAC = static_cast<float>(A_P * 24.3);// [-24.3, +24.3]
		DYCC = static_cast<float>(L_Y * 14.3);// [-14.3, +14.3]
		DYPC = static_cast<float>(R_Y * 14.3);// [-14.3, +14.3]
		DYAC = static_cast<float>(A_Y * 14.3);// [-14.3, +14.3]


		if (ReadCOMPOOL_IS( SCP_SENSE_SW ) == 0)
		{
			DAAC = DAAC * ReadCOMPOOL_SS( SCP_TRANS_ROLL );
			DYAC = DYAC * ReadCOMPOOL_SS( SCP_TRANS_YAW );
		}
		return;
	}

	void ORB_THREE_AX_RHC_SOP::ORB_3_VALID( void )
	{
		//_3_AX_VALID();
		// HACK code copied to here
		if ((ReadCOMPOOL_IS( SCP_L_PIT_DG ) == 1) && (ReadCOMPOOL_IS( SCP_L_ROL_DG ) == 1) && (ReadCOMPOOL_IS( SCP_L_YAW_DG ) == 1))
		{
			DECV = DECC;
			DACV = DACC;
			DYCV = DYCC;
		}
		else
		{
			DECV = 0.0;
			DACV = 0.0;
			DYCV = 0.0;
		}

		
		if ((ReadCOMPOOL_IS( SCP_R_PIT_DG ) == 1) && (ReadCOMPOOL_IS( SCP_R_ROL_DG ) == 1) && (ReadCOMPOOL_IS( SCP_R_YAW_DG ) == 1))
		{
			DEPV = DEPC;
			DAPV = DAPC;
			DYPV = DYPC;
		}
		else
		{
			DEPV = 0.0;
			DAPV = 0.0;
			DYPV = 0.0;
		}


		// aft
		if ((ReadCOMPOOL_IS( SCP_A_PIT_DG ) == 1) && (ReadCOMPOOL_IS( SCP_A_ROL_DG ) == 1) && (ReadCOMPOOL_IS( SCP_A_YAW_DG ) == 1))
		{
			DEAV = DEAC;
			DAAV = DAAC;
			DYAV = DYAC;
		}
		else
		{
			DEAV = 0.0;
			DAAV = 0.0;
			DYAV = 0.0;
		}
		return;
	}

	void ORB_THREE_AX_RHC_SOP::ORB_3_DB( void )
	{
		float DB1 = ReadCOMPOOL_SS( SCP_DB1 );
		float DB2 = ReadCOMPOOL_SS( SCP_DB2 );
		float DB3 = ReadCOMPOOL_SS( SCP_DB3 );

		//_3_AX_DB();
		// HACK code copied to here
		// LH pitch
		DECDB = DEADBAND( DECV, DB2 );

		// LH roll
		DACDB = DEADBAND( DACV, DB1 );

		// LH yaw
		DYCDB = DEADBAND( DYCV, DB3 );
		
		// RH pitch
		DEPDB = DEADBAND( DEPV, DB2 );

		// RH roll
		DAPDB = DEADBAND( DAPV, DB1 );

		// RH yaw
		DYPDB = DEADBAND( DYPV, DB3 );


		// aft pitch
		DEADB = DEADBAND( DEAV, DB2 );

		// aft roll
		DAADB = DEADBAND( DAAV, DB1 );

		// aft yaw
		DYADB = DEADBAND( DYAV, DB3 );
		return;
	}

	void ORB_THREE_AX_RHC_SOP::RHC_SCALAR_TRANS( void )
	{
		DEAT = -DEADB;

		if (ReadCOMPOOL_IS( SCP_SENSE_SW ) == 1)
		{
			// -X sense roll trans
			DAAT = -DAADB;

			// yaw trans
			DYAT = DYADB;
		}
		else
		{
			// -Z sense roll trans
			DAAT = -DYADB;

			// yaw trans
			DYAT = -DAADB;
		}
		return;
	}

	void ORB_THREE_AX_RHC_SOP::ORB_3_STA_SEL( void )
	{
		// pitch
		WriteCOMPOOL_SS( SCP_DEMAN, DECDB + DEPDB + DEAT );

		// roll
		WriteCOMPOOL_SS( SCP_DAMAN, DACDB + DAPDB + DAAT );

		// yaw
		WriteCOMPOOL_SS( SCP_DYMAN, DYCDB + DYPDB + DYAT );
		return;
	}

	void ORB_THREE_AX_RHC_SOP::ORB_3_DETENT( void )
	{
		float DRHYS1 = ReadCOMPOOL_SS( SCP_DRHYS1 );
		float DRHYS2 = ReadCOMPOOL_SS( SCP_DRHYS2 );
		float DPHYS1 = ReadCOMPOOL_SS( SCP_DPHYS1 );
		float DPHYS2 = ReadCOMPOOL_SS( SCP_DPHYS2 );
		float DYHYS1 = ReadCOMPOOL_SS( SCP_DYHYS1 );
		float DYHYS2 = ReadCOMPOOL_SS( SCP_DYHYS2 );

		//_3_AX_DETENT();
		// HACK code copied to here
		// LH
		HYSTER_1( DACD, DACV, DRHYS2, DRHYS1 );

		// RH
		HYSTER_1( DAPD, DAPV, DRHYS2, DRHYS1 );

		// LH
		HYSTER_1( DECD, DECV, DPHYS2, DPHYS1 );

		// RH
		HYSTER_1( DEPD, DEPV, DPHYS2, DPHYS1 );

		// LH
		HYSTER_1( DYCD, DYCV, DYHYS2, DYHYS1 );

		// RH
		HYSTER_1( DYPD, DYPV, DYHYS2, DYHYS1 );

		// aft roll
		HYSTER_1( DAAD, DAAV, DRHYS2, DRHYS1 );

		// aft pitch
		HYSTER_1( DEAD, DEAV, DPHYS2, DPHYS1 );

		// aft yaw
		HYSTER_1( DYAD, DYAV, DYHYS2, DYHYS1 );
		return;
	}

	void ORB_THREE_AX_RHC_SOP::RHC_INT_TRANS( void )
	{
		DEADT = -DEAD;

		if (ReadCOMPOOL_IS( SCP_SENSE_SW ) == 1)
		{
			// -X sense roll
			DAADT = -DAAD;

			// yaw
			DYADT = DYAD;
		}
		else
		{
			// -Z sense roll
			DAADT = -DYAD;

			// yaw
			DYADT = -DAAD;
		}
		return;
	}

	void ORB_THREE_AX_RHC_SOP::ORB_INT_STA_SEL( void )
	{
		short R_STATES = DACD + DAPD + DAADT;

		// roll state
		WriteCOMPOOL_AIS( SCP_RHC_STATE, 1, static_cast<short>(midval( -1, R_STATES, 1 )), 3 );

		short P_STATES = DECD + DEPD + DEADT;

		// pitch state
		WriteCOMPOOL_AIS( SCP_RHC_STATE, 2, static_cast<short>(midval( -1, P_STATES, 1 )), 3 );

		short Y_STATES = DYCD + DYPD + DYADT;

		// yaw state
		WriteCOMPOOL_AIS( SCP_RHC_STATE, 3, static_cast<short>(midval( -1, Y_STATES, 1 )), 3 );

		// TODO LAMP_AUTO
		/*if (LAMP_AUTO == ON)
		{
			WriteCOMPOOL_IS( SCP_DAP_ALERT, 0 );
		}

		if (((fabs( ReadCOMPOOL_AIS( SCP_RHC_STATE, 1, 3 ) ) == 1) || (fabs( ReadCOMPOOL_AIS( SCP_RHC_STATE, 2, 3 ) ) == 1) || (fabs( ReadCOMPOOL_AIS( SCP_RHC_STATE, 3, 3 ) ) == 1)) && (LAMP_AUTO == ON))
		{
			WriteCOMPOOL_IS( SCP_DAP_ALERT, 1 );
		}*/
		return;
	}

	void ORB_THREE_AX_RHC_SOP::ORB_3_SOFT_STOP( void )
	{
		//_3_AX_SOFT_STOP();
		// HACK code copied to here
		// LH
		HYSTER_2( DACSS, DACV, SSRHYS2, SSRHYS1 );
		
		// RH
		HYSTER_2( DAPSS, DAPV, SSRHYS2, SSRHYS1 );
		
		// LH
		HYSTER_2( DECSS, DECV, SSPHYS2, SSPHYS1 );
		
		// RH
		HYSTER_2( DEPSS, DEPV, SSPHYS2, SSPHYS1 );

		// LH
		HYSTER_2( DYCSS, DYCV, SSYHYS2, SSYHYS1 );
		
		// RH
		HYSTER_2( DYPSS, DYPV, SSYHYS2, SSYHYS1 );


		HYSTER_2( DAASS, DAAV, SSRHYS2, SSRHYS1 );

		HYSTER_2( DEASS, DEAV, SSPHYS2, SSPHYS1 );

		HYSTER_2( DYASS, DYAV, SSYHYS2, SSYHYS1 );
		return;
	}

	void ORB_THREE_AX_RHC_SOP::RHC_DISC_TRANS( void )
	{
		DEASST = DEASS;

		if (ReadCOMPOOL_IS( SCP_SENSE_SW ) == 1)
		{
			// -X sense roll
			DAASST = DAASS;

			// yaw
			DYASST = DYASS;
		}
		else
		{
			// -Z sense roll
			DAASST = DYASS;

			// yaw
			DYASST = DAASS;
		}
		return;
	}

	void ORB_THREE_AX_RHC_SOP::ORB_DISC_STA_SEC( void )
	{
		// roll
		WriteCOMPOOL_IS( SCP_RSS_EXCEED, DACSS || DAPSS || DAASST );

		// pitch
		WriteCOMPOOL_IS( SCP_PSS_EXCEED, DECSS || DEPSS || DEASST );

		// yaw
		WriteCOMPOOL_IS( SCP_YSS_EXCEED, DYCSS || DYPSS || DYASST );
		return;
	}
}

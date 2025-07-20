#include "THREE_AX_RHC_SOP.h"
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


	THREE_AX_RHC_SOP::THREE_AX_RHC_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "THREE_AX_RHC_SOP" )
	{
		return;
	}

	THREE_AX_RHC_SOP::~THREE_AX_RHC_SOP( void )
	{
		return;
	}

	void THREE_AX_RHC_SOP::Realize( void )
	{
		pRHC_RM = dynamic_cast<RHC_RM*>(FindSoftware( "RHC_RM" ));
		assert( (pRHC_RM != NULL) && "THREE_AX_RHC_SOP::Realize.pRHC_RM" );
		return;
	}

	void THREE_AX_RHC_SOP::OnPreStep( double simt, double simdt, double mjd )
	{
		unsigned short ME_ZERO = ReadCOMPOOL_IS( SCP_MECO_CONFIRMED );// HACK until ME_ZERO exists
		if ((ME_ZERO == 1) || ((ME_ZERO == 0) && (ReadCOMPOOL_IS( SCP_LCSS_PLAMP ) == 1)))
		{
			_3_AX_COMP();
			_3_AX_VALID();
			_3_AX_DB();
			_3_AX_STA_SEL();
			_3_AX_DETENT();
			INT_STA_SEL();
			_3_AX_SOFT_STOP();
			DISC_STA_SEL();
		}
		return;
	}

	bool THREE_AX_RHC_SOP::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 102:
			case 103:
			case 104:
			case 105:
			case 106:
			case 301:
			case 302:
			case 303:
			case 601:
				return true;
			default:
				return false;
		}
	}

	void THREE_AX_RHC_SOP::_3_AX_COMP( void )
	{
		// TODO use proper source and conversion to degrees
		double L_P = 0.0;
		double L_R = 0.0;
		double L_Y = 0.0;
		double R_P = 0.0;
		double R_R = 0.0;
		double R_Y = 0.0;

		// get data from RM
		pRHC_RM->GetRHCData_L( L_P, L_R, L_Y );
		pRHC_RM->GetRHCData_R( R_P, R_R, R_Y );

		// convert to degrees
		DACC = static_cast<float>(L_R * 24.3);// [-24.3, +24.3]
		DAPC = static_cast<float>(R_R * 24.3);// [-24.3, +24.3]
		DECC = static_cast<float>(L_P * 24.3);// [-24.3, +24.3]
		DEPC = static_cast<float>(R_P * 24.3);// [-24.3, +24.3]
		DYCC = static_cast<float>(L_Y * 14.3);// [-14.3, +14.3]
		DYPC = static_cast<float>(R_Y * 14.3);// [-14.3, +14.3]
		return;
	}

	void THREE_AX_RHC_SOP::_3_AX_VALID( void )
	{
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
		return;
	}

	void THREE_AX_RHC_SOP::_3_AX_DB( void )
	{
		float DB1 = ReadCOMPOOL_SS( SCP_DB1 );
		float DB2 = ReadCOMPOOL_SS( SCP_DB2 );
		float DB3 = ReadCOMPOOL_SS( SCP_DB3 );

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
		return;
	}

	void THREE_AX_RHC_SOP::_3_AX_STA_SEL( void )
	{
		// pitch
		WriteCOMPOOL_SS( SCP_DEMAN, DECDB + DEPDB );

		// roll
		WriteCOMPOOL_SS( SCP_DAMAN, DACDB + DAPDB );

		// yaw
		WriteCOMPOOL_SS( SCP_DYMAN, DYCDB + DYPDB );
		return;
	}

	void THREE_AX_RHC_SOP::_3_AX_DETENT( void )
	{
		float DRHYS1 = ReadCOMPOOL_SS( SCP_DRHYS1 );
		float DRHYS2 = ReadCOMPOOL_SS( SCP_DRHYS2 );
		float DPHYS1 = ReadCOMPOOL_SS( SCP_DPHYS1 );
		float DPHYS2 = ReadCOMPOOL_SS( SCP_DPHYS2 );
		float DYHYS1 = ReadCOMPOOL_SS( SCP_DYHYS1 );
		float DYHYS2 = ReadCOMPOOL_SS( SCP_DYHYS2 );

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
		return;
	}

	void THREE_AX_RHC_SOP::INT_STA_SEL( void )
	{
		short R_STATES = DACD + DAPD;

		// roll state
		WriteCOMPOOL_AIS( SCP_RHC_STATE, 1,static_cast<short>( midval( -1, R_STATES, 1 )), 3 );

		short P_STATES = DECD + DEPD;

		// pitch state
		WriteCOMPOOL_AIS( SCP_RHC_STATE, 2, static_cast<short>(midval( -1, P_STATES, 1 )), 3 );

		short Y_STATES = DYCD + DYPD;

		// yaw state
		WriteCOMPOOL_AIS( SCP_RHC_STATE, 3, static_cast<short>(midval( -1, Y_STATES, 1 )), 3 );

		// TODO ME_ZERO and AUTO_MODE
		//if ((ME_ZERO == 1) && (/*TODO*/ReadCOMPOOL_IS( SCP_MM ) == 601/*MM_601 == 0*/))
		//{
		//	if (AUTO_MODE == ON)
		//	{
		//		WriteCOMPOOL_IS( SCP_DAP_ALERT, 0 );
		//	}

		//	if (((fabs( ReadCOMPOOL_AIS( SCP_RHC_STATE, 1, 3 ) ) == 1) || (fabs( ReadCOMPOOL_AIS( SCP_RHC_STATE, 2, 3 ) ) == 1) || (fabs( ReadCOMPOOL_AIS( SCP_RHC_STATE, 3, 3 ) ) == 1)) && (AUTO_MODE == ON))
		//	{
		//		WriteCOMPOOL_IS( SCP_DAP_ALERT, 1 );
		//	}
		//}
		return;
	}

	void THREE_AX_RHC_SOP::_3_AX_SOFT_STOP( void )
	{
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
		return;
	}

	void THREE_AX_RHC_SOP::DISC_STA_SEL( void )
	{
		WriteCOMPOOL_IS( SCP_RSS_EXCEED, (DACSS || DAPSS) ? 1 : 0 );

		WriteCOMPOOL_IS( SCP_PSS_EXCEED, (DECSS || DEPSS) ? 1 : 0 );

		WriteCOMPOOL_IS( SCP_YSS_EXCEED, (DYCSS || DYPSS) ? 1 : 0 );
		return;
	}
}

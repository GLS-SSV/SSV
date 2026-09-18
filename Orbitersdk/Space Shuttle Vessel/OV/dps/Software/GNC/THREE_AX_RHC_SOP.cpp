#include "THREE_AX_RHC_SOP.h"
#include "GNCUtilities.h"
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

	void THREE_AX_RHC_SOP::OnPreStep( double simt, double simdt, double mjd )
	{
		if ((((ReadCOMPOOL_IS( SCP_MM_CODE_102 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_103 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_601 ) == 1)) && (ReadCOMPOOL_IS( SCP_ME_ZERO ) == 0) && (ReadCOMPOOL_IS( SCP_LCSS_PLAMP ) == 1)) ||
			((ReadCOMPOOL_IS( SCP_ME_ZERO ) == 1) && ((ReadCOMPOOL_IS( SCP_MM_CODE_103 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_104 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_105 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_106 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_601 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_301 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_302 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_303 ) == 1))))
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

	void THREE_AX_RHC_SOP::_3_AX_COMP( void )
	{
		float DAC = ReadCOMPOOL_SS( SCP_DAC );
		float DAP = ReadCOMPOOL_SS( SCP_DAP );
		float DEC = ReadCOMPOOL_SS( SCP_DEC );
		float DEP = ReadCOMPOOL_SS( SCP_DEP );
		float DYC = ReadCOMPOOL_SS( SCP_DYC );
		float DYP = ReadCOMPOOL_SS( SCP_DYP );
		float CRHCPC = ReadCOMPOOL_SS( SCP_CRHCPC );
		float CRHCPP = ReadCOMPOOL_SS( SCP_CRHCPP );
		float CRHCRC = ReadCOMPOOL_SS( SCP_CRHCRC );
		float CRHCRP = ReadCOMPOOL_SS( SCP_CRHCRP );
		float CRHCYC = ReadCOMPOOL_SS( SCP_CRHCYC );
		float CRHCYP = ReadCOMPOOL_SS( SCP_CRHCYP );
		float KRHCPC = ReadCOMPOOL_SS( SCP_KRHCPC );
		float KRHCPP = ReadCOMPOOL_SS( SCP_KRHCPP );
		float KRHCRC = ReadCOMPOOL_SS( SCP_KRHCRC );
		float KRHCRP = ReadCOMPOOL_SS( SCP_KRHCRP );
		float KRHCYC = ReadCOMPOOL_SS( SCP_KRHCYC );
		float KRHCYP = ReadCOMPOOL_SS( SCP_KRHCYP );

		// LH PITCH
		DECC = (DEC * CRHCPC) + KRHCPC;

		// RH PITCH
		DEPC = (DEP * CRHCPP) + KRHCPP;

		// LH ROLL
		DACC = (DAC * CRHCRC) + KRHCRC;

		// RH ROLL
		DAPC = (DAP * CRHCRP) + KRHCRP;

		// LH YAW
		DYCC = (DYC * CRHCYC) + KRHCYC;

		// RH YAW
		DYPC = (DYP * CRHCYP) + KRHCYP;
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

		// TODO AUTO_MODE
		//if ((ReadCOMPOOL_IS( SCP_ME_ZERO ) == 1) && (ReadCOMPOOL_IS( SCP_MM_CODE_601 ) == 1))
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

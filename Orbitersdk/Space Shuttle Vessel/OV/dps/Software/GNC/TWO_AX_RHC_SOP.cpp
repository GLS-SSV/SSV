/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/04/07   GLS
2020/06/20   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/06/04   GLS
2023/06/03   GLS
2025/07/20   GLS
********************************************/
#include "TWO_AX_RHC_SOP.h"
#include "RHC_RM.h"
#include <cassert>


namespace dps
{
	TWO_AX_RHC_SOP::TWO_AX_RHC_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "TWO_AX_RHC_SOP" )
	{
		ALERT1 = false;
		ALERT2 = false;
		return;
	}

	TWO_AX_RHC_SOP::~TWO_AX_RHC_SOP( void )
	{
		return;
	}

	void TWO_AX_RHC_SOP::Realize( void )
	{
		pRHC_RM = dynamic_cast<RHC_RM*>(FindSoftware( "RHC_RM" ));
		assert( (pRHC_RM != NULL) && "TWO_AX_RHC_SOP::Realize.pRHC_RM" );
		return;
	}

	void TWO_AX_RHC_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		// TODO 12.5Hz in MM 304/305 and 25Hz from A/L, and limit rates of some functions below

		RHC_COMP();
		RHC_DB();
		RHC_DOWNMODE();
		RHC_STA_SEL();
		PAN_TRIM();
		RHC_TRIM();
		return;
	}

	bool TWO_AX_RHC_SOP::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 304:
			case 305:
			case 602:
			case 603:
				return true;
			default:
				return false;
		}
	}

	void TWO_AX_RHC_SOP::RHC_COMP( void )
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
		return;
	}

	void TWO_AX_RHC_SOP::RHC_DB( void )
	{
		float DB1 = ReadCOMPOOL_SS( SCP_DB1 );
		float DB2 = ReadCOMPOOL_SS( SCP_DB2 );
		float DB3 = ReadCOMPOOL_SS( SCP_DB3 );

		if ((ReadCOMPOOL_IS( SCP_L_PIT_DG ) == 1) && (ReadCOMPOOL_IS( SCP_L_ROL_DG ) == 1))
		{
			DECS = DECC;
			DACS = DACC;
		}
		else
		{
			DECS = 0.0;
			DACS = 0.0;
		}

		DECDB = DEADBAND( DECS, DB2 );
		DACDB = DEADBAND( DACS, DB1 );

		
		if ((ReadCOMPOOL_IS( SCP_R_PIT_DG ) == 1) && (ReadCOMPOOL_IS( SCP_R_ROL_DG ) == 1))
		{
			DEPS = DEPC;
			DAPS = DAPC;
		}
		else
		{
			DEPS = 0.0;
			DAPS = 0.0;
		}

		DEPDB = DEADBAND( DEPS, DB2 );
		DAPDB = DEADBAND( DAPS, DB1 );
		return;
	}

	void TWO_AX_RHC_SOP::RHC_DOWNMODE( void )
	{
		bool DNMDP1;
		bool DNMDP2;
		bool DNMDRY1;
		bool DNMDRY2;
		float RHC_PTCH_DNMD_TH;

		if (ReadCOMPOOL_IS( SCP_LOAD_RELIEF ) == 0)
		{
			RHC_PTCH_DNMD_TH = ReadCOMPOOL_SS( SCP_RHC_PTCH_DNMD_THLD );
		}
		else
		{
			RHC_PTCH_DNMD_TH = ReadCOMPOOL_SS( SCP_RHC_PTCH_DNMD_THLD_LREL );
		}

		// left pitch
		if (fabs( DECS ) >= RHC_PTCH_DNMD_TH)
		{
			DNMDP1 = true;
		}
		else
		{
			DNMDP1 = false;
		}

		// right pitch
		if (fabs( DEPS ) >= RHC_PTCH_DNMD_TH)
		{
			DNMDP2 = true;
		}
		else
		{
			DNMDP2 = false;
		}

		// left roll/yaw
		if (fabs( DACS ) >= ReadCOMPOOL_SS( SCP_RHC_RY_DNMD_THLD ))
		{
			DNMDRY1 = true;
		}
		else
		{
			DNMDRY1 = false;
		}

		// right roll/yaw
		if (fabs( DAPS ) >= ReadCOMPOOL_SS( SCP_RHC_RY_DNMD_THLD ))
		{
			DNMDRY2 = true;
		}
		else
		{
			DNMDRY2 = false;
		}

		WriteCOMPOOL_AIS( SCP_RHC_STATE, 2, (DNMDP1 || DNMDP2) ? 1 : 0, 3 );
		WriteCOMPOOL_AIS( SCP_RHC_STATE, 1, (DNMDRY1 || DNMDRY2) ? 1 : 0, 3 );

		if (ReadCOMPOOL_SS( SCP_M ) >= 1.0)
		{
			unsigned int AUTORY_LAMP = ReadCOMPOOL_IS( SCP_AUTORY_IND );
			unsigned int AUTOP_LAMP = ReadCOMPOOL_IS( SCP_AUTOP_IND );

			if (AUTORY_LAMP == 1)
			{
				ALERT1 = false;
			}

			if ((AUTORY_LAMP == 1) && (ReadCOMPOOL_AIS( SCP_RHC_STATE, 1, 3 ) == 1))
			{
				ALERT1 = true;
			}
			
			if (AUTOP_LAMP == 1)
			{
				ALERT2 = false;
			}

			if ((AUTOP_LAMP == 1) && (ReadCOMPOOL_AIS( SCP_RHC_STATE, 2, 3 ) == 1))
			{
				ALERT2 = true;
			}

			WriteCOMPOOL_IS( SCP_DAP_ALERT, (ALERT1 || ALERT2) ? 1 : 0 );
		}
		return;
	}

	void TWO_AX_RHC_SOP::RHC_STA_SEL( void )
	{
		// pitch
		WriteCOMPOOL_SS( SCP_DEMAN, DECDB + DEPDB );

		// roll
		WriteCOMPOOL_SS( SCP_DAMAN, DACDB + DAPDB );
		return;
	}

	void TWO_AX_RHC_SOP::PAN_TRIM( void )
	{
		bool PANATUS[2];
		bool PANATDS[2];
		bool PANETUS[2];
		bool PANETDS[2];
		bool INHIBIT[2];
		PANATUS[0] = ReadCOMPOOL_AIS( SCP_PANATUS, 1, 2 );
		PANATUS[1] = ReadCOMPOOL_AIS( SCP_PANATUS, 2, 2 );
		PANATDS[0] = ReadCOMPOOL_AIS( SCP_PANATDS, 1, 2 );
		PANATDS[1] = ReadCOMPOOL_AIS( SCP_PANATDS, 2, 2 );
		PANETUS[0] = ReadCOMPOOL_AIS( SCP_PANETUS, 1, 2 );
		PANETUS[1] = ReadCOMPOOL_AIS( SCP_PANETUS, 2, 2 );
		PANETDS[0] = ReadCOMPOOL_AIS( SCP_PANETDS, 1, 2 );
		PANETDS[1] = ReadCOMPOOL_AIS( SCP_PANETDS, 2, 2 );
		INHIBIT[0] = ReadCOMPOOL_AIS( SCP_DISABL, 1, 2 );
		INHIBIT[1] = ReadCOMPOOL_AIS( SCP_DISABL, 2, 2 );

		bool PATU = (PANATUS[0] && !INHIBIT[0]) || (PANATUS[1] && !INHIBIT[1]);
		bool PATD = (PANATDS[0] && !INHIBIT[0]) || (PANATDS[1] && !INHIBIT[1]);
		bool PETU = (PANETUS[0] && !INHIBIT[0]) || (PANETUS[1] && !INHIBIT[1]);
		bool PETD = (PANETDS[0] && !INHIBIT[0]) || (PANETDS[1] && !INHIBIT[1]);

		// left roll trim cmd
		WriteCOMPOOL_IS( SCP_DATM_PAN, static_cast<int>(PATU) - static_cast<int>(PATD) );

		// panel pitch trim cmd
		WriteCOMPOOL_IS( SCP_DETM_PAN, static_cast<int>(PETU) - static_cast<int>(PETD) );
		return;
	}

	void TWO_AX_RHC_SOP::RHC_TRIM( void )
	{
		if (ReadCOMPOOL_IS( SCP_WOWLON_IND ) == 1)
		{
			bool RHCETDS[2];
			RHCETDS[0] = ReadCOMPOOL_AIS( SCP_RHCETDS, 1, 2 );
			RHCETDS[1] = ReadCOMPOOL_AIS( SCP_RHCETDS, 2, 2 );

			bool RHCETD = RHCETDS[0] || RHCETDS[1];
			WriteCOMPOOL_IS( SCP_DETM_RHC, -static_cast<int>(RHCETD) );
			WriteCOMPOOL_IS( SCP_DATM_RHC, 0 );
		}
		else
		{
			bool RHCATUS[2];
			bool RHCATDS[2];
			bool RHCETUS[2];
			bool RHCETDS[2];
			bool INHIBIT[2];
			RHCATUS[0] = ReadCOMPOOL_AIS( SCP_RHCATUS, 1, 2 );
			RHCATUS[1] = ReadCOMPOOL_AIS( SCP_RHCATUS, 2, 2 );
			RHCATDS[0] = ReadCOMPOOL_AIS( SCP_RHCATDS, 1, 2 );
			RHCATDS[1] = ReadCOMPOOL_AIS( SCP_RHCATDS, 2, 2 );
			RHCETUS[0] = ReadCOMPOOL_AIS( SCP_RHCETUS, 1, 2 );
			RHCETUS[1] = ReadCOMPOOL_AIS( SCP_RHCETUS, 2, 2 );
			RHCETDS[0] = ReadCOMPOOL_AIS( SCP_RHCETDS, 1, 2 );
			RHCETDS[1] = ReadCOMPOOL_AIS( SCP_RHCETDS, 2, 2 );
			INHIBIT[0] = ReadCOMPOOL_AIS( SCP_DISABL, 1, 2 );
			INHIBIT[1] = ReadCOMPOOL_AIS( SCP_DISABL, 2, 2 );

			// + RHC roll
			bool RHCATU = (RHCATUS[0] && !INHIBIT[0]) || (RHCATUS[1] && !INHIBIT[1]);

			// - RHC roll
			bool RHCATD = (RHCATDS[0] && !INHIBIT[0]) || (RHCATDS[1] && !INHIBIT[1]);

			// + RHC pitch
			bool RHCETU = (RHCETUS[0] && !INHIBIT[0]) || (RHCETUS[1] && !INHIBIT[1]);

			// - RHC pitch
			bool RHCETD = (RHCETDS[0] && !INHIBIT[0]) || (RHCETDS[1] && !INHIBIT[1]);

			// RHC roll trim cmd
			WriteCOMPOOL_IS( SCP_DATM_RHC, static_cast<int>(RHCATU) - static_cast<int>(RHCATD) );

			// RHC pitch trim cmd
			WriteCOMPOOL_IS( SCP_DETM_RHC, static_cast<int>(RHCETU) - static_cast<int>(RHCETD) );
		}
		return;
	}
}

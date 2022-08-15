/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/04/15   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/08/14   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/12/30   GLS
2022/08/05   GLS
********************************************/
#include "NW_POSN_SOP.h"
#include <MathSSV.h>


namespace dps
{
	NW_POSN_SOP::NW_POSN_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "NW_POSN_SOP" )
	{
		DNWC = 0.0;
		LAST_NW_POS = 0.0;
		NW_POS_ERR_CNT[0] = 0.0;
		NW_POS_ERR_CNT[1] = 0.0;

		NW_POS_ERR = false;
		NWS1_fail = false;
		NWS2_fail = false;
		return;
	}

	NW_POSN_SOP::~NW_POSN_SOP( void )
	{
		return;
	}

	void NW_POSN_SOP::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "NWS", 16 );
		dipNWS1_ON.Connect( pBundle, 2 );
		dipNWS2_ON.Connect( pBundle, 3 );
		dopNWS1_ENABLE_A_CMD.Connect( pBundle, 6 );
		dopNWS1_ENABLE_B_CMD.Connect( pBundle, 7 );
		dopNWS2_ENABLE_A_CMD.Connect( pBundle, 8 );
		dopNWS2_ENABLE_B_CMD.Connect( pBundle, 9 );
		dipNWS_POS_A.Connect( pBundle, 10 );
		dipNWS_POS_B.Connect( pBundle, 11 );
		dipNWS_POS_C.Connect( pBundle, 12 );
		dipNWS1_ACT.Connect( pBundle, 13 );
		dipNWS2_ACT.Connect( pBundle, 14 );
		dopNW_POSN_ERROR.Connect( pBundle, 15 );
		return;
	}

	void NW_POSN_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		unsigned short GSENBL = ReadCOMPOOL_IS( SCP_GSENBL );
		double SEL_NW_POS = midval( dipNWS_POS_A.GetVoltage(), dipNWS_POS_B.GetVoltage(), dipNWS_POS_C.GetVoltage() );
		double NW_POS = -1.0 - (SEL_NW_POS * (12.0 / 5.0));// convert to degrees and correct sensor bias

		// NWS mode interpretation logic
		bool A = false;// TODO NWS 1 switch commfault
		bool B = false;// TODO NWS 2 switch commfault
		bool C = false;// TODO NWS 1 Active switch commfault
		bool D = false;// TODO NWS 2 Active switch commfault
		bool E = dipNWS1_ON.IsSet();
		bool F = dipNWS2_ON.IsSet();
		bool G = dipNWS1_ACT.IsSet();
		bool H = dipNWS2_ACT.IsSet();
		bool NWS1 = (!D && (!H && ((!C && G && (!F || B)) || (A && !B && C && !F) || (!A && E)) || (A && !B && !C && F && G && H))) || (!C && D && G && ((!B && !F) || (!A && E))) || (!A && E && (B || !F));
		bool NWS2 = !((!D && !H && ((B && !C && (G || !A)) || (!B && !F) || (!A && E))) || (!C && D && ((!B && !F && (!A || G)) || (!A && E && G))) || (!A && E && (B || !F)) || (A && !B && !C && !F && G && H));

		// NW position comparison
		if (NWS1 && !NWS1_fail)
		{
			NW_POS_ERR = NosewheelPositionComparison( DNWC, NW_POS, simdt );
			NWS1_fail = NW_POS_ERR;
		}
		else if (NWS2 && !NWS2_fail)
		{
			NW_POS_ERR = NosewheelPositionComparison( DNWC, NW_POS, simdt );
			NWS2_fail = NW_POS_ERR;
		}
		else
		{
			NW_POS_ERR_CNT[0] = 0.0;
			NW_POS_ERR_CNT[1] = 0.0;
		}

		// output enable signals
		if ((GSENBL == 1) && (!NW_POS_ERR))
		{
			dopNWS1_ENABLE_A_CMD.SetLine();
			dopNWS1_ENABLE_B_CMD.SetLine();
			dopNWS2_ENABLE_A_CMD.SetLine();
			dopNWS2_ENABLE_B_CMD.SetLine();
		}
		else
		{
			dopNWS1_ENABLE_A_CMD.ResetLine();
			dopNWS1_ENABLE_B_CMD.ResetLine();
			dopNWS2_ENABLE_A_CMD.ResetLine();
			dopNWS2_ENABLE_B_CMD.ResetLine();
		}

		// output to NWS FAIL light
		dopNW_POSN_ERROR.SetLine( 5.0f * (int)(NW_POS_ERR) );

		DNWC = ReadCOMPOOL_SD( SCP_DNWC );
		LAST_NW_POS = NW_POS;
		return;
	}

	bool NW_POSN_SOP::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 101:
			case 305:
			case 603:
			case 801:
				return true;
			default:
				return false;
		}
	}

	bool NW_POSN_SOP::NosewheelPositionComparison( double DNWC, double NW_POS, double dt )
	{
		bool _NW_POS_ERR = false;
		double NW_POS_DIFF = DNWC - NW_POS;

		if (fabs( NW_POS_DIFF ) > 2.0)
		{
			double ACT_NW_RATE = NW_POS - LAST_NW_POS;
			if ((NW_POS_DIFF * ACT_NW_RATE) < 0.0)
			{
				// HACK 3 cycles (@ 25Hz)
				NW_POS_ERR_CNT[0]++;
				if (NW_POS_ERR_CNT[0] >= 3) _NW_POS_ERR = true;
			}
			else NW_POS_ERR_CNT[0] = 0.0;

			if (fabs( ACT_NW_RATE / dt ) < 5.0)
			{
				// HACK 6 cycles (@ 25Hz)
				NW_POS_ERR_CNT[1]++;
				if (NW_POS_ERR_CNT[1] >= 6) _NW_POS_ERR = true;
			}
			else NW_POS_ERR_CNT[1] = 0.0;
		}
		else
		{
			NW_POS_ERR_CNT[0] = 0.0;
			NW_POS_ERR_CNT[1] = 0.0;
		}
		return _NW_POS_ERR;
	}
}
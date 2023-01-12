/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/04/07   GLS
2020/06/20   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/06/04   GLS
********************************************/
#include "RHC_SOP.h"
#include "RHC_RM.h"
#include <cassert>


namespace dps
{
	RHC_SOP::RHC_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "RHC_SOP" )
	{
		FCS_MAN_TAKEOVER_PITCH = false;
		FCS_MAN_TAKEOVER_ROLL = false;
		FCS_MAN_TAKEOVER_YAW = false;

		DETENT_PITCH = true;
		DETENT_ROLL = true;
		DETENT_YAW = true;

		PAST_SOFTSTOP_PITCH = false;
		PAST_SOFTSTOP_ROLL = false;
		PAST_SOFTSTOP_YAW = false;

		RHC_P = 0;
		RHC_R = 0;
		RHC_Y = 0;
		return;
	}

	RHC_SOP::~RHC_SOP( void )
	{
		return;
	}

	void RHC_SOP::Realize( void )
	{
		pRHC_RM = dynamic_cast<RHC_RM*>(FindSoftware( "RHC_RM" ));
		assert( (pRHC_RM != NULL) && "RHC_SOP::Realize.pRHC_RM" );
		return;
	}

	void RHC_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		switch (GetMajorMode())
		{
			case 304:
			case 305:
			case 602:
			case 603:
				TwoAxis();
				break;
			default:
				ThreeAxis();
				break;
		}
		return;
	}

	bool RHC_SOP::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void RHC_SOP::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	bool RHC_SOP::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 102:
			case 103:
			case 104:
			case 105:
			case 106:
			case 201:
			case 202:
			case 301:
			case 302:
			case 303:
			case 304:
			case 305:
			case 601:
			case 602:
			case 603:
			case 801:
				return true;
			default:
				return false;
		}
	}

	void RHC_SOP::TwoAxis( void )
	{
		double L_P = 0.0;
		double L_R = 0.0;
		double L_Y = 0.0;
		bool DG_L_P = false;
		bool DG_L_R = false;
		bool DG_L_Y = false;
		double R_P = 0.0;
		double R_R = 0.0;
		double R_Y = 0.0;
		bool DG_R_P = false;
		bool DG_R_R = false;
		bool DG_R_Y = false;

		// get data from RM
		pRHC_RM->GetRHCData_L( L_P, L_R, L_Y, DG_L_P, DG_L_R, DG_L_Y );
		pRHC_RM->GetRHCData_R( R_P, R_R, R_Y, DG_R_P, DG_R_R, DG_R_Y );

		// convert to degrees
		L_P *= 24.3;// [-24.3, +24.3]
		L_R *= 24.3;// [-24.3, +24.3]
		R_P *= 24.3;// [-24.3, +24.3]
		R_R *= 24.3;// [-24.3, +24.3]

		// check data good flag
		if ((DG_L_P == false) || (DG_L_R == false))
		{
			L_P = 0.0;
			L_R = 0.0;
		}
		if ((DG_R_P == false) || (DG_R_R == false))
		{
			R_P = 0.0;
			R_R = 0.0;
		}

		// detent
		if ((fabs( L_P ) >= 1.15) || (fabs( R_P ) >= 1.15)) DETENT_PITCH = false;
		else DETENT_PITCH = true;
		if ((fabs( L_R ) >= 1.25) || (fabs( R_R ) >= 1.25)) DETENT_ROLL = false;
		else DETENT_ROLL = true;
		DETENT_YAW = true;

		// FCS manual takeover (TODO is it 7º or 6º?)
		if ((fabs( L_P ) > 7.0) || (fabs( R_P ) > 7.0)) FCS_MAN_TAKEOVER_PITCH = true;
		else FCS_MAN_TAKEOVER_PITCH = false;
		if ((fabs( L_R ) > 7.0) || (fabs( R_R ) > 7.0)) FCS_MAN_TAKEOVER_ROLL = true;
		else FCS_MAN_TAKEOVER_ROLL = false;
		FCS_MAN_TAKEOVER_YAW = false;

		// sum all RHC commands
		RHC_P = L_P + R_P;
		RHC_R = L_R + R_R;
		RHC_Y = 0.0;
		return;
	}

	void RHC_SOP::ThreeAxis( void )
	{
		unsigned int MM = GetMajorMode();
		if ((MM == 201) || (MM == 202) || (MM == 801))
		{
			double L_P = 0.0;
			double L_R = 0.0;
			double L_Y = 0.0;
			bool DG_L_P = false;
			bool DG_L_R = false;
			bool DG_L_Y = false;
			double R_P = 0.0;
			double R_R = 0.0;
			double R_Y = 0.0;
			bool DG_R_P = false;
			bool DG_R_R = false;
			bool DG_R_Y = false;
			double A_P = 0.0;
			double A_R = 0.0;
			double A_Y = 0.0;
			bool DG_A_P = false;
			bool DG_A_R = false;
			bool DG_A_Y = false;

			// get data from RM
			pRHC_RM->GetRHCData_L( L_P, L_R, L_Y, DG_L_P, DG_L_R, DG_L_Y );
			pRHC_RM->GetRHCData_R( R_P, R_R, R_Y, DG_R_P, DG_R_R, DG_R_Y );
			pRHC_RM->GetRHCData_A( A_P, A_R, A_Y, DG_A_P, DG_A_R, DG_A_Y );

			// aft sense logic
			if (ReadCOMPOOL_IS( SCP_SENSE_SWITCH ) == 0)
			{
				// -Z
				double tmp_R = A_R;
				A_P = -A_P;
				A_R = -A_Y;
				A_Y = -tmp_R;
			}
			else
			{
				// -X
				A_P = -A_P;
				A_R = -A_R;
				//A_Y = A_Y;
			}

			// convert to degrees
			L_P *= 24.3;// [-24.3, +24.3]
			L_R *= 24.3;// [-24.3, +24.3]
			L_Y *= 14.3;// [-14.3, +14.3]
			R_P *= 24.3;// [-24.3, +24.3]
			R_R *= 24.3;// [-24.3, +24.3]
			R_Y *= 14.3;// [-14.3, +14.3]
			A_P *= 24.3;// [-24.3, +24.3]
			A_R *= 24.3;// [-24.3, +24.3]
			A_Y *= 14.3;// [-14.3, +14.3]

			// check data good flag
			if ((DG_L_P == false) || (DG_L_R == false) || (DG_L_Y == false))
			{
				L_P = 0.0;
				L_R = 0.0;
				L_Y = 0.0;
			}
			if ((DG_R_P == false) || (DG_R_R == false) || (DG_R_Y == false))
			{
				R_P = 0.0;
				R_R = 0.0;
				R_Y = 0.0;
			}
			if ((DG_A_P == false) || (DG_A_R == false) || (DG_A_Y == false))
			{
				A_P = 0.0;
				A_R = 0.0;
				A_Y = 0.0;
			}

			// detent
			if ((fabs( L_P ) >= 1.15) || (fabs( R_P ) >= 1.15) || (fabs( A_P ) >= 1.15)) DETENT_PITCH = false;
			else DETENT_PITCH = true;
			if ((fabs( L_R ) >= 1.25) || (fabs( R_R ) >= 1.25) || (fabs( A_R ) >= 1.25)) DETENT_ROLL = false;
			else DETENT_ROLL = true;
			if ((fabs( L_Y ) >= 0.65) || (fabs( R_Y ) >= 0.65) || (fabs( A_Y ) >= 0.65)) DETENT_YAW = false;
			else DETENT_YAW = true;

			// FCS manual takeover (TODO is it 7º or 6º?)
			if ((fabs( L_P ) > 7.0) || (fabs( R_P ) > 7.0) || (fabs( A_P ) > 7.0)) FCS_MAN_TAKEOVER_PITCH = true;
			else FCS_MAN_TAKEOVER_PITCH = false;
			if ((fabs( L_R ) > 7.0) || (fabs( R_R ) > 7.0) || (fabs( A_R ) > 7.0)) FCS_MAN_TAKEOVER_ROLL = true;
			else FCS_MAN_TAKEOVER_ROLL = false;
			if ((fabs( L_Y ) > 7.0) || (fabs( R_Y ) > 7.0) || (fabs( A_Y ) > 7.0)) FCS_MAN_TAKEOVER_YAW = true;
			else FCS_MAN_TAKEOVER_YAW = false;

			// sw softstop (TODO no clue what the numbers are, using ~75% of axis deflection as previously used in OrbitDAP)
			if ((fabs( L_P ) > 18.2) || (fabs( R_P ) > 18.2) || (fabs( A_P ) > 18.2)) PAST_SOFTSTOP_PITCH = true;
			else PAST_SOFTSTOP_PITCH = false;
			if ((fabs( L_R ) > 18.2) || (fabs( R_R ) > 18.2) || (fabs( A_R ) > 18.2)) PAST_SOFTSTOP_ROLL = true;
			else PAST_SOFTSTOP_ROLL = false;
			if ((fabs( L_Y ) > 10.7) || (fabs( R_Y ) > 10.7) || (fabs( A_Y ) > 10.7)) PAST_SOFTSTOP_YAW = true;
			else PAST_SOFTSTOP_YAW = false;

			// sum all RHC commands
			RHC_P = L_P + R_P + A_P;
			RHC_R = L_R + R_R + A_R;
			RHC_Y = L_Y + R_Y + A_Y;
		}
		else
		{
			double L_P = 0.0;
			double L_R = 0.0;
			double L_Y = 0.0;
			bool DG_L_P = false;
			bool DG_L_R = false;
			bool DG_L_Y = false;
			double R_P = 0.0;
			double R_R = 0.0;
			double R_Y = 0.0;
			bool DG_R_P = false;
			bool DG_R_R = false;
			bool DG_R_Y = false;

			// get data from RM
			pRHC_RM->GetRHCData_L( L_P, L_R, L_Y, DG_L_P, DG_L_R, DG_L_Y );
			pRHC_RM->GetRHCData_R( R_P, R_R, R_Y, DG_R_P, DG_R_R, DG_R_Y );

			// convert to degrees
			L_P *= 24.3;// [-24.3, +24.3]
			L_R *= 24.3;// [-24.3, +24.3]
			L_Y *= 14.3;// [-14.3, +14.3]
			R_P *= 24.3;// [-24.3, +24.3]
			R_R *= 24.3;// [-24.3, +24.3]
			R_Y *= 14.3;// [-14.3, +14.3]

			// check data good flag
			if ((DG_L_P == false) || (DG_L_R == false) || (DG_L_Y == false))
			{
				L_P = 0.0;
				L_R = 0.0;
				L_Y = 0.0;
			}
			if ((DG_R_P == false) || (DG_R_R == false) || (DG_R_Y == false))
			{
				R_P = 0.0;
				R_R = 0.0;
				R_Y = 0.0;
			}

			// detent
			if ((fabs( L_P ) >= 1.15) || (fabs( R_P ) >= 1.15)) DETENT_PITCH = false;
			else DETENT_PITCH = true;
			if ((fabs( L_R ) >= 1.25) || (fabs( R_R ) >= 1.25)) DETENT_ROLL = false;
			else DETENT_ROLL = true;
			if ((fabs( L_Y ) >= 0.65) || (fabs( R_Y ) >= 0.65)) DETENT_YAW = false;
			else DETENT_YAW = true;

			// FCS manual takeover (TODO is it 7º or 6º?)
			if ((fabs( L_P ) > 7.0) || (fabs( R_P ) > 7.0)) FCS_MAN_TAKEOVER_PITCH = true;
			else FCS_MAN_TAKEOVER_PITCH = false;
			if ((fabs( L_R ) > 7.0) || (fabs( R_R ) > 7.0)) FCS_MAN_TAKEOVER_ROLL = true;
			else FCS_MAN_TAKEOVER_ROLL = false;
			if ((fabs( L_Y ) > 7.0) || (fabs( R_Y ) > 7.0)) FCS_MAN_TAKEOVER_YAW = true;
			else FCS_MAN_TAKEOVER_YAW = false;

			// sw softstop (TODO no clue what the numbers are, using ~75% of axis deflection as previously used in OrbitDAP)
			if ((fabs( L_P ) > 18.2) || (fabs( R_P ) > 18.2)) PAST_SOFTSTOP_PITCH = true;
			else PAST_SOFTSTOP_PITCH = false;
			if ((fabs( L_R ) > 18.2) || (fabs( R_R ) > 18.2)) PAST_SOFTSTOP_ROLL = true;
			else PAST_SOFTSTOP_ROLL = false;
			if ((fabs( L_Y ) > 10.7) || (fabs( R_Y ) > 10.7)) PAST_SOFTSTOP_YAW = true;
			else PAST_SOFTSTOP_YAW = false;

			// sum all RHC commands
			RHC_P = L_P + R_P;
			RHC_R = L_R + R_R;
			RHC_Y = L_Y + R_Y;
		}
		return;
	}

	double RHC_SOP::GetPitchCommand( void ) const
	{
		return RHC_P;
	}

	double RHC_SOP::GetRollCommand( void ) const
	{
		return RHC_R;
	}

	double RHC_SOP::GetYawCommand( void ) const
	{
		return RHC_Y;
	}

	bool RHC_SOP::GetPitchManTakeOver( void ) const
	{
		return FCS_MAN_TAKEOVER_PITCH;
	}

	bool RHC_SOP::GetRollManTakeOver( void ) const
	{
		return FCS_MAN_TAKEOVER_ROLL;
	}

	bool RHC_SOP::GetYawManTakeOver( void ) const
	{
		return FCS_MAN_TAKEOVER_YAW;
	}

	bool RHC_SOP::GetPitchDetent( void ) const
	{
		return DETENT_PITCH;
	}

	bool RHC_SOP::GetRollDetent( void ) const
	{
		return DETENT_ROLL;
	}

	bool RHC_SOP::GetYawDetent( void ) const
	{
		return DETENT_YAW;
	}

	bool RHC_SOP::GetPitchPastSoftStop( void ) const
	{
		return PAST_SOFTSTOP_PITCH;
	}

	bool RHC_SOP::GetRollPastSoftStop( void ) const
	{
		return PAST_SOFTSTOP_ROLL;
	}

	bool RHC_SOP::GetYawPastSoftStop( void ) const
	{
		return PAST_SOFTSTOP_YAW;
	}
}
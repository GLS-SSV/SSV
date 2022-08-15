/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/04/07   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/01/20   GLS
2021/04/15   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
********************************************/
#include "OMS_TVC_Command_SOP.h"
#include "OMSBurnSoftware.h"
#include <MathSSV.h>
#include <cassert>


namespace dps
{
	OMSTVCCMD_SOP::OMSTVCCMD_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "OMS_TVC_Command_SOP" )
	{
		L_pitch = 0.0;
		L_yaw = 0.0;
		R_pitch = 0.0;
		R_yaw = 0.0;
		GimbalCheckTimer = 0.0;

		GimbalCheck = false;
		return;
	}

	OMSTVCCMD_SOP::~OMSTVCCMD_SOP( void )
	{
		return;
	}

	void OMSTVCCMD_SOP::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "OMS_TVC_CMD", 16 );
		L_OMS_ENG_PRI_ENA_1.Connect( pBundle, 0 );
		L_OMS_ENG_PRI_ENA_2.Connect( pBundle, 1 );
		L_OMS_ENG_SEC_ENA_1.Connect( pBundle, 2 );
		L_OMS_ENG_SEC_ENA_2.Connect( pBundle, 3 );
		R_OMS_ENG_PRI_ENA_1.Connect( pBundle, 4 );
		R_OMS_ENG_PRI_ENA_2.Connect( pBundle, 5 );
		R_OMS_ENG_SEC_ENA_1.Connect( pBundle, 6 );
		R_OMS_ENG_SEC_ENA_2.Connect( pBundle, 7 );
		L_OMS_PRI_P_ACTR_CMD.Connect( pBundle, 8 );
		L_OMS_SEC_P_ACTR_CMD.Connect( pBundle, 9 );
		L_OMS_PRI_Y_ACTR_CMD.Connect( pBundle, 10 );
		L_OMS_SEC_Y_ACTR_CMD.Connect( pBundle, 11 );
		R_OMS_PRI_P_ACTR_CMD.Connect( pBundle, 12 );
		R_OMS_SEC_P_ACTR_CMD.Connect( pBundle, 13 );
		R_OMS_PRI_Y_ACTR_CMD.Connect( pBundle, 14 );
		R_OMS_SEC_Y_ACTR_CMD.Connect( pBundle, 15 );

		pOMSBurnSoftware = dynamic_cast<OMSBurnSoftware*>(FindSoftware( "OMSBurnSoftware" ));
		assert( (pOMSBurnSoftware != NULL) && "OMSTVCCMD_SOP::Realize.pOMSBurnSoftware" );
		return;
	}

	void OMSTVCCMD_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		// actr ch management
		unsigned int L_actr = pOMSBurnSoftware->GetOMSGimbalActrSel( 0 );
		switch (L_actr)
		{
			case 0:
				L_OMS_ENG_PRI_ENA_1.ResetLine();
				L_OMS_ENG_PRI_ENA_2.ResetLine();
				L_OMS_ENG_SEC_ENA_1.ResetLine();
				L_OMS_ENG_SEC_ENA_2.ResetLine();
				break;
			case 1:
				L_OMS_ENG_PRI_ENA_1.SetLine();
				L_OMS_ENG_PRI_ENA_2.SetLine();
				L_OMS_ENG_SEC_ENA_1.ResetLine();
				L_OMS_ENG_SEC_ENA_2.ResetLine();
				break;
			case 2:
				L_OMS_ENG_PRI_ENA_1.ResetLine();
				L_OMS_ENG_PRI_ENA_2.ResetLine();
				L_OMS_ENG_SEC_ENA_1.SetLine();
				L_OMS_ENG_SEC_ENA_2.SetLine();
				break;
		}

		unsigned int R_actr = pOMSBurnSoftware->GetOMSGimbalActrSel( 1 );
		switch (R_actr)
		{
			case 0:
				R_OMS_ENG_PRI_ENA_1.ResetLine();
				R_OMS_ENG_PRI_ENA_2.ResetLine();
				R_OMS_ENG_SEC_ENA_1.ResetLine();
				R_OMS_ENG_SEC_ENA_2.ResetLine();
				break;
			case 1:
				R_OMS_ENG_PRI_ENA_1.SetLine();
				R_OMS_ENG_PRI_ENA_2.SetLine();
				R_OMS_ENG_SEC_ENA_1.ResetLine();
				R_OMS_ENG_SEC_ENA_2.ResetLine();
				break;
			case 2:
				R_OMS_ENG_PRI_ENA_1.ResetLine();
				R_OMS_ENG_PRI_ENA_2.ResetLine();
				R_OMS_ENG_SEC_ENA_1.SetLine();
				R_OMS_ENG_SEC_ENA_2.SetLine();
				break;
		}

		// TODO other flags
		if (GimbalCheck)
		{
			// gimbal check
			GimbalCheckTimer += simdt;

			// HACK no clue about times, these are enough to cover range at 3º/s
			if (GimbalCheckTimer < 3.0)
			{
				// 1 (0-3s): drive to p0, y0
				L_pitch = 0.0;
				L_yaw = 0.0;
				R_pitch = 0.0;
				R_yaw = 0.0;
			}
			else if (GimbalCheckTimer < 6.0)
			{
				// 2 (3-6s): drive to p+6 y+7
				L_pitch = 6.0;
				L_yaw = 7.0;
				R_pitch = 6.0;
				R_yaw = 7.0;
			}
			else if (GimbalCheckTimer < 9.0)
			{
				// 3 (6-9s): drive to p0, y0
				L_pitch = 0.0;
				L_yaw = 0.0;
				R_pitch = 0.0;
				R_yaw = 0.0;
			}
			else if (GimbalCheckTimer < 12.0)
			{
				// 4 (9-12s): drive to p-6 y-7
				L_pitch = -6.0;
				L_yaw = -7.0;
				R_pitch = -6.0;
				R_yaw = -7.0;
			}
			else if (GimbalCheckTimer < 15.0)
			{
				// 5 (12-15): drive to p0, y0
				L_pitch = 0.0;
				L_yaw = 0.0;
				R_pitch = 0.0;
				R_yaw = 0.0;
			}
			else
			{
				// end
				GimbalCheckTimer = 0.0;
				GimbalCheck = false;
			}
		}

		// send DAP gimbal commands
		if (L_actr == 1)
		{
			L_OMS_PRI_P_ACTR_CMD.SetLine( static_cast<float>(L_pitch) );
			L_OMS_PRI_Y_ACTR_CMD.SetLine( static_cast<float>(L_yaw) );
		}
		else if (L_actr == 2)
		{
			L_OMS_SEC_P_ACTR_CMD.SetLine( static_cast<float>(L_pitch) );
			L_OMS_SEC_Y_ACTR_CMD.SetLine( static_cast<float>(L_yaw) );
		}

		if (R_actr == 1)
		{
			R_OMS_PRI_P_ACTR_CMD.SetLine( static_cast<float>(R_pitch) );
			R_OMS_PRI_Y_ACTR_CMD.SetLine( static_cast<float>(R_yaw) );
		}
		else if (R_actr == 2)
		{
			R_OMS_SEC_P_ACTR_CMD.SetLine( static_cast<float>(R_pitch) );
			R_OMS_SEC_Y_ACTR_CMD.SetLine( static_cast<float>(R_yaw) );
		}
		return;
	}

	bool OMSTVCCMD_SOP::OnParseLine( const char* keyword, const char* value )
	{
		if (!_strnicmp( keyword, "LEFT_PITCH", 10 ))
		{
			sscanf_s( value, "%lf", &L_pitch );
			if ((L_pitch > 6.0) || (L_pitch < -6.0)) L_pitch = 0.0;
			return true;
		}
		else if (!_strnicmp( keyword, "LEFT_YAW", 8 ))
		{
			sscanf_s( value, "%lf", &L_yaw );
			if ((L_yaw > 7.0) || (L_yaw < -7.0)) L_yaw = 0.0;
			return true;
		}
		else if (!_strnicmp( keyword, "RIGHT_PITCH", 11 ))
		{
			sscanf_s( value, "%lf", &R_pitch );
			if ((R_pitch > 6.0) || (R_pitch < -6.0)) R_pitch = 0.0;
			return true;
		}
		else if (!_strnicmp( keyword, "RIGHT_YAW", 9 ))
		{
			sscanf_s( value, "%lf", &R_yaw );
			if ((R_yaw > 7.0) || (R_yaw < -7.0)) R_yaw = 0.0;
			return true;
		}
		return false;
	}

	void OMSTVCCMD_SOP::OnSaveState( FILEHANDLE scn ) const
	{
		oapiWriteScenario_float( scn, "LEFT_PITCH", L_pitch );
		oapiWriteScenario_float( scn, "LEFT_YAW", L_yaw );
		oapiWriteScenario_float( scn, "RIGHT_PITCH", R_pitch );
		oapiWriteScenario_float( scn, "RIGHT_YAW", R_yaw );
		return;
	}

	bool OMSTVCCMD_SOP::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 104:
			case 105:
			case 106:
			case 202:
			case 301:
			case 302:
			case 601:
			case 801:
			case 901:
				return true;
			case 303:// set entry stow positions
				L_pitch = 5.9;
				L_yaw = 6.4;
				R_pitch = 5.9;
				R_yaw = -6.4;
				return true;
			default:
				return false;
		}
	}

	void OMSTVCCMD_SOP::SetGimbalCheckFlag( void )
	{
		GimbalCheck = true;
		return;
	}

	bool OMSTVCCMD_SOP::GetGimbalCheckFlag( void ) const
	{
		return GimbalCheck;
	}

	void OMSTVCCMD_SOP::SetPitch( unsigned int eng, double pitch )
	{
		if (eng == 0) L_pitch = range( -6.0, pitch, 6.0 );
		else R_pitch = range( -6.0, pitch, 6.0 );
		return;
	}

	void OMSTVCCMD_SOP::SetYaw( unsigned int eng, double yaw )
	{
		if (eng == 0) L_yaw = range( -7.0, yaw, 7.0 );
		else R_yaw = range( -7.0, yaw, 7.0 );
		return;
	}
}
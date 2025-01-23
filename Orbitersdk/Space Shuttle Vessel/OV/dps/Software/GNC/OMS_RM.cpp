#include "OMS_RM.h"
#include <EngConst.h>
#include <cassert>


namespace dps
{
	// K-LOADs
	constexpr float OMS_SER_D_Z = 2.0f;// OMS SERVO AMP DEAD ZONE (V97U3077C) [deg]
	constexpr unsigned short O_A_COUNT = 24;// OMS ACTUATOR FAILURE COUNTER (V97U3061C) [1]
	constexpr unsigned short O_E_COUNT = 4;// OMS ENG FAILURE COUNTER (V97U3061C) [1]
	constexpr float PC_THRESH = 2.5f;// OMS ENG PRESSURE THRESHOLD (V97U4208C) [vdc]
	constexpr float C1 = 4118.0f;// C(1) (V97U3017C) [SLUG*FT/SEC/CYCLE]
	constexpr float C2 = 9896.0f;// C(2) (V97U3018C) [SLUG*FT/SEC/CYCLE]


	OMS_RM::OMS_RM( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "OMS_RM" ),
	stepENG(0.96), stepACT(0.16),
		ONE_ENG_THRESH(0.0f), TWO_ENG_THRESH(0.0f), FAIL_COUNTER{0,0,0}, VEL_FAIL_FLAG(0),
		REF_EXT_I{0,0,0,0}, ACTUATOR_FAIL_COUNTER_I{0,0,0,0}, OMS_ACTUATOR_FAIL_I{0,0,0,0}, PREV_OMSL_ACT_SEL(0), PREV_OMSR_ACT_SEL(0)
	{
		return;
	}

	OMS_RM::~OMS_RM( void )
	{
		return;
	}

	void OMS_RM::OnPreStep( double simt, double simdt, double mjd )
	{
		stepENG += simdt;
		stepACT += simdt;

		switch (ReadCOMPOOL_IS( SCP_MM ))
		{
			case 102:
			case 103:
			case 601:
			case 602:
				OMS_ENGINE_FDI();
				break;
			case 106:
			case 301:
			case 303:
				OMS_ACTUATOR_FDI();
				break;
			case 104:
			case 105:
			case 202:
			case 302:
			case 304:
				OMS_ENGINE_FDI();
				OMS_ACTUATOR_FDI();
				break;
		}
		return;
	}

	void OMS_RM::OMS_ENGINE_FDI( void )
	{
		if (stepENG >= 0.96)// 1.04Hz
		{
			unsigned short VEL_PREFAIL = 0;
			unsigned short L_CHAMB_PRESS_PREFAIL = 0;
			unsigned short R_CHAMB_PRESS_PREFAIL = 0;

			float L_OMS_CHAMB_PRESS = ReadCOMPOOL_IS( SCP_FA3_IOM6_CH18_DATA ) * 32.0f;
			float R_OMS_CHAMB_PRESS = ReadCOMPOOL_IS( SCP_FA4_IOM6_CH18_DATA ) * 32.0f;
			unsigned short L_OMS_CHAMB_PRESS_CF = 0;// TODO
			unsigned short R_OMS_CHAMB_PRESS_CF = 0;// TODO
			float DVB_SEC_X = 999999.9f;// TODO
			float CURRENT_ORBITER_MASS = 215000 * LBS2SL;// TODO

			WriteCOMPOOL_IS( SCP_OMS_ENGINE_FDI_INIT_RESET_FLAG, 0 );
			if (ReadCOMPOOL_IS( SCP_OMS_ENGINE_FDI_INIT_FLAG ) == 1)
			{
				ONE_ENG_THRESH = C1 / CURRENT_ORBITER_MASS;
				TWO_ENG_THRESH = C2 / CURRENT_ORBITER_MASS;

				FAIL_COUNTER[0] = 0;
				FAIL_COUNTER[1] = 0;
				FAIL_COUNTER[2] = 0;

				WriteCOMPOOL_IS( SCP_L_OMS_ALERT, 0 );
				WriteCOMPOOL_IS( SCP_S_LOMS_FAIL, 0 );
				WriteCOMPOOL_IS( SCP_R_OMS_ALERT, 0 );
				WriteCOMPOOL_IS( SCP_S_ROMS_FAIL, 0 );

				//K = C2;

				/*VEL_PREFAIL = 0;
				L_CHAMB_PRESS_PREFAIL = 0;
				R_CHAMB_PRESS_PREFAIL = 0;*/

				VEL_FAIL_FLAG = 0;
				WriteCOMPOOL_IS( SCP_OMS_L_CHAMB_PRESS_FAIL, 0 );
				WriteCOMPOOL_IS( SCP_OMS_R_CHAMB_PRESS_FAIL, 0 );

				WriteCOMPOOL_IS( SCP_OMS_ENGINE_FDI_INIT_FLAG, 0 );
				WriteCOMPOOL_IS( SCP_OMS_ENGINE_FDI_INIT_RESET_FLAG, 1 );
			}

			unsigned short L_OMS_ARM_STATUS = ReadCOMPOOL_IS( SCP_SEL_OMS_L_ENG_ARM_CMD ) | ReadCOMPOOL_IS( SCP_SEL_OMS_L_ENG_ARMPRESS_CMD );
			unsigned short R_OMS_ARM_STATUS = ReadCOMPOOL_IS( SCP_SEL_OMS_R_ENG_ARM_CMD ) | ReadCOMPOOL_IS( SCP_SEL_OMS_R_ENG_ARMPRESS_CMD );

			if ((ReadCOMPOOL_IS( SCP_OMS_L_ON_CMD_IND ) == 1) || (ReadCOMPOOL_IS( SCP_OMS_R_ON_CMD_IND ) == 1))
			{
				if (ReadCOMPOOL_IS( SCP_MECO_CONFIRMED ) == 1)
				{
					if (ReadCOMPOOL_IS( SCP_OMS_R_ON_CMD_IND ) == ReadCOMPOOL_IS( SCP_OMS_L_ON_CMD_IND ))
					{
						if (DVB_SEC_X > TWO_ENG_THRESH)
						{
							VEL_PREFAIL = 0;
						}
						else
						{
							VEL_PREFAIL = 1;
						}
					}
					else
					{
						if (DVB_SEC_X <= ONE_ENG_THRESH)
						{
							VEL_PREFAIL = 1;
						}
						else
						{
							VEL_PREFAIL = 0;
						}
					}
				}
			}

			if (L_OMS_CHAMB_PRESS > PC_THRESH)
			{
				L_CHAMB_PRESS_PREFAIL = (ReadCOMPOOL_IS( SCP_OMS_L_ON_CMD_IND ) == 1) ? 0 : 1;
			}
			else
			{
				L_CHAMB_PRESS_PREFAIL = ReadCOMPOOL_IS( SCP_OMS_L_ON_CMD_IND );
			}
			if (R_OMS_CHAMB_PRESS > PC_THRESH)
			{
				R_CHAMB_PRESS_PREFAIL = (ReadCOMPOOL_IS( SCP_OMS_R_ON_CMD_IND ) == 1) ? 0 : 1;
			}
			else
			{
				R_CHAMB_PRESS_PREFAIL = ReadCOMPOOL_IS( SCP_OMS_R_ON_CMD_IND );
			}

			if (VEL_PREFAIL == 1)
			{
				FAIL_COUNTER[0] += 1;
				if (FAIL_COUNTER[0] >= O_E_COUNT)
				{
					VEL_FAIL_FLAG = 1;
				}
			}
			else
			{
				FAIL_COUNTER[0] = 0;
				TWO_ENG_THRESH = /*K*/C2 / CURRENT_ORBITER_MASS;
			}
			if (L_OMS_CHAMB_PRESS_CF == 0)
			{
				if (L_CHAMB_PRESS_PREFAIL == 1)
				{
					FAIL_COUNTER[1] += 1;
					if (FAIL_COUNTER[1] >= O_E_COUNT)
					{
						WriteCOMPOOL_IS( SCP_OMS_L_CHAMB_PRESS_FAIL, 1 );
					}
				}
				else
				{
					FAIL_COUNTER[1] = 0;
				}
			}
			if (R_OMS_CHAMB_PRESS_CF == 0)
			{
				if (R_CHAMB_PRESS_PREFAIL == 1)
				{
					FAIL_COUNTER[2] += 1;
					if (FAIL_COUNTER[2] >= O_E_COUNT)
					{
						WriteCOMPOOL_IS( SCP_OMS_R_CHAMB_PRESS_FAIL, 1 );
					}
				}
				else
				{
					FAIL_COUNTER[2] = 0;
				}
			}

			WriteCOMPOOL_IS( SCP_L_OMS_ALERT, VEL_FAIL_FLAG & ReadCOMPOOL_IS( SCP_OMS_L_CHAMB_PRESS_FAIL ) );
			WriteCOMPOOL_IS( SCP_R_OMS_ALERT, VEL_FAIL_FLAG & ReadCOMPOOL_IS( SCP_OMS_R_CHAMB_PRESS_FAIL ) );

			if ((ReadCOMPOOL_IS( SCP_L_OMS_ALERT ) == 1) && (L_OMS_ARM_STATUS == 0))
			{
				WriteCOMPOOL_IS( SCP_S_LOMS_FAIL, 1 );
			}
			if ((ReadCOMPOOL_IS( SCP_R_OMS_ALERT ) == 1) && (R_OMS_ARM_STATUS == 0))
			{
				WriteCOMPOOL_IS( SCP_S_ROMS_FAIL, 1 );
			}

			stepENG = 0.0;
		}
		return;
	}

	void OMS_RM::OMS_ACTUATOR_FDI( void )
	{
		if (stepACT >= 0.16)// 6.25Hz
		{
			unsigned short OMSL_ACT_SEL = ReadCOMPOOL_IS( SCP_OMSL_ACT_SEL );
			unsigned short OMSR_ACT_SEL = ReadCOMPOOL_IS( SCP_OMSR_ACT_SEL );
			float OMS_ACTUATOR_CMD[4];
			float OMS_ACTUATOR_FB[4];
			unsigned short DG[4];

			WriteCOMPOOL_IS( SCP_OMS_ACT_FDI_INIT_RESET_FLAG, 0 );
			if (ReadCOMPOOL_IS( SCP_OMS_ACT_FDI_INIT_FLAG ) == 1)
			{
				for (int i = 0; i < 4; i++)
				{
					REF_EXT_I[i] = 0;
					ACTUATOR_FAIL_COUNTER_I[i] = 0;
					OMS_ACTUATOR_FAIL_I[i] = 0;
				}

				WriteCOMPOOL_IS( SCP_OMS_ACT_FDI_INIT_FLAG, 0 );
				WriteCOMPOOL_IS( SCP_OMS_ACT_FDI_INIT_RESET_FLAG, 1 );
			}

			OMS_ACTUATOR_CMD[0] = ReadCOMPOOL_SS( SCP_SEL_OMS_RP_CMD );
			OMS_ACTUATOR_CMD[1] = ReadCOMPOOL_SS( SCP_SEL_OMS_RY_CMD );
			OMS_ACTUATOR_CMD[2] = ReadCOMPOOL_SS( SCP_SEL_OMS_LP_CMD );
			OMS_ACTUATOR_CMD[3] = ReadCOMPOOL_SS( SCP_SEL_OMS_LY_CMD );

			OMS_ACTUATOR_FB[0] = ReadCOMPOOL_SS( SCP_SOMSRPFDBK );
			OMS_ACTUATOR_FB[1] = ReadCOMPOOL_SS( SCP_SOMSRYFDBK );
			OMS_ACTUATOR_FB[2] = ReadCOMPOOL_SS( SCP_SOMSLPFDBK );
			OMS_ACTUATOR_FB[3] = ReadCOMPOOL_SS( SCP_SOMSLYFDBK );

			DG[0] = ReadCOMPOOL_IS( SCP_ROMSPDG );
			DG[1] = ReadCOMPOOL_IS( SCP_ROMSYDG );
			DG[2] = ReadCOMPOOL_IS( SCP_LOMSPDG );
			DG[3] = ReadCOMPOOL_IS( SCP_LOMSYDG );


			if (OMSR_ACT_SEL != PREV_OMSR_ACT_SEL)
			{
				ACTUATOR_FAIL_COUNTER_I[0] = 0;
				ACTUATOR_FAIL_COUNTER_I[1] = 0;

				if (OMSR_ACT_SEL != 2)
				{
					OMS_ACTUATOR_FAIL_I[0] = 0;
					OMS_ACTUATOR_FAIL_I[1] = 0;
				}
			}

			if (OMSL_ACT_SEL != PREV_OMSL_ACT_SEL)
			{
				ACTUATOR_FAIL_COUNTER_I[2] = 0;
				ACTUATOR_FAIL_COUNTER_I[3] = 0;

				if (OMSL_ACT_SEL != 2)
				{
					OMS_ACTUATOR_FAIL_I[2] = 0;
					OMS_ACTUATOR_FAIL_I[3] = 0;
				}
			}

			PREV_OMSR_ACT_SEL = OMSR_ACT_SEL;
			PREV_OMSL_ACT_SEL = OMSL_ACT_SEL;

			for (int i = 0; i < 4; i++)
			{
				if (DG[i] == 0) continue;

				float OMS_GIMBAL_ERROR = OMS_ACTUATOR_CMD[i] - OMS_ACTUATOR_FB[i];
				short EXTEND;

				if (fabs( OMS_GIMBAL_ERROR ) > OMS_SER_D_Z)
				{
					EXTEND = (OMS_GIMBAL_ERROR > 0.0) ? 1 : -1;
				}
				else
				{
					EXTEND = 0;
					ACTUATOR_FAIL_COUNTER_I[i] = 0;
				}

				if ((EXTEND != REF_EXT_I[i]) || (EXTEND == 0))
				{
					ACTUATOR_FAIL_COUNTER_I[i] = 0;
					REF_EXT_I[i] = EXTEND;
				}
				else
				{
					ACTUATOR_FAIL_COUNTER_I[i] = ACTUATOR_FAIL_COUNTER_I[i] + 1;
					if (ACTUATOR_FAIL_COUNTER_I[i] >= O_A_COUNT)
					{
						OMS_ACTUATOR_FAIL_I[i] = 1;
					}
				}
			}

			WriteCOMPOOL_IS( SCP_OMSR_PITCH_FAIL, OMS_ACTUATOR_FAIL_I[0] );
			WriteCOMPOOL_IS( SCP_OMSR_YAW_FAIL, OMS_ACTUATOR_FAIL_I[1] );
			WriteCOMPOOL_IS( SCP_OMSL_PITCH_FAIL, OMS_ACTUATOR_FAIL_I[2] );
			WriteCOMPOOL_IS( SCP_OMSL_YAW_FAIL, OMS_ACTUATOR_FAIL_I[3] );

			WriteCOMPOOL_IS( SCP_OMSR_PITCH_STATUS, (DG[0] == 0) ? 1 : ((OMS_ACTUATOR_FAIL_I[0] == 1) ? 2 : 0) );
			WriteCOMPOOL_IS( SCP_OMSR_YAW_STATUS, (DG[1] == 0) ? 1 : ((OMS_ACTUATOR_FAIL_I[1] == 1) ? 2 : 0) );
			WriteCOMPOOL_IS( SCP_OMSL_PITCH_STATUS, (DG[2] == 0) ? 1 : ((OMS_ACTUATOR_FAIL_I[2] == 1) ? 2 : 0) );
			WriteCOMPOOL_IS( SCP_OMSL_YAW_STATUS, (DG[3] == 0) ? 1 : ((OMS_ACTUATOR_FAIL_I[3] == 1) ? 2 : 0) );

			stepACT = 0.0;
		}
		return;
	}

	bool OMS_RM::OnParseLine( const char* keyword, const char* value )
	{
		if (!_strnicmp( keyword, "REF_EXT_I", 9 ))
		{
			sscanf_s( value, "%hd %hd %hd %hd", &REF_EXT_I[0], &REF_EXT_I[1], &REF_EXT_I[2], &REF_EXT_I[3] );
			return true;
		}
		else if (!_strnicmp( keyword, "ACTUATOR_FAIL_COUNTER_I", 23 ))
		{
			sscanf_s( value, "%hu %hu %hu %hu", &ACTUATOR_FAIL_COUNTER_I[0], &ACTUATOR_FAIL_COUNTER_I[1], &ACTUATOR_FAIL_COUNTER_I[2], &ACTUATOR_FAIL_COUNTER_I[3] );
			return true;
		}
		else if (!_strnicmp( keyword, "OMS_ACTUATOR_FAIL_I", 19 ))
		{
			sscanf_s( value, "%hu %hu %hu %hu", &OMS_ACTUATOR_FAIL_I[0], &OMS_ACTUATOR_FAIL_I[1], &OMS_ACTUATOR_FAIL_I[2], &OMS_ACTUATOR_FAIL_I[3] );
			return true;
		}
		else if (!_strnicmp( keyword, "PREV_OMSL_ACT_SEL", 17 ))
		{
			sscanf_s( value, "%hu", &PREV_OMSL_ACT_SEL );
			return true;
		}
		else if (!_strnicmp( keyword, "PREV_OMSR_ACT_SEL", 17 ))
		{
			sscanf_s( value, "%hu", &PREV_OMSR_ACT_SEL );
			return true;
		}
		return false;
	}

	void OMS_RM::OnSaveState( FILEHANDLE scn ) const
	{
		char cbuf[256];

		sprintf_s( cbuf, 256, "%hd %hd %hd %hd", REF_EXT_I[0], REF_EXT_I[1], REF_EXT_I[2], REF_EXT_I[3] );
		oapiWriteScenario_string( scn, "REF_EXT_I", cbuf );
		sprintf_s( cbuf, 256, "%hu %hu %hu %hu", ACTUATOR_FAIL_COUNTER_I[0], ACTUATOR_FAIL_COUNTER_I[1], ACTUATOR_FAIL_COUNTER_I[2], ACTUATOR_FAIL_COUNTER_I[3] );
		oapiWriteScenario_string( scn, "ACTUATOR_FAIL_COUNTER_I", cbuf );
		sprintf_s( cbuf, 256, "%hu %hu %hu %hu", OMS_ACTUATOR_FAIL_I[0], OMS_ACTUATOR_FAIL_I[1], OMS_ACTUATOR_FAIL_I[2], OMS_ACTUATOR_FAIL_I[3] );
		oapiWriteScenario_string( scn, "OMS_ACTUATOR_FAIL_I", cbuf );
		oapiWriteScenario_int( scn, "PREV_OMSL_ACT_SEL", PREV_OMSL_ACT_SEL );
		oapiWriteScenario_int( scn, "PREV_OMSR_ACT_SEL", PREV_OMSR_ACT_SEL );
		return;
	}

	bool OMS_RM::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 102:
			case 103:
			case 104:
			case 105:
			case 106:
			case 202:
			case 301:
			case 302:
			case 303:
			case 304:
			case 601:
			case 602:
				return true;
			default:
				return false;
		}
	}
}

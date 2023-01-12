#include "OMS_RM.h"
#include <cassert>


namespace dps
{
	// K-LOADs
	constexpr float OMS_SER_D_Z = 2.0f;// OMS SERVO AMP DEAD ZONE (V97U3077C) [deg]
	constexpr unsigned short O_A_COUNT = 24;// OMS ACTUATOR FAILURE COUNTER (V97U3061C) [1]


	OMS_RM::OMS_RM( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "OMS_RM" ),
	step(0.16), REF_EXT_I{0,0,0,0}, ACTUATOR_FAIL_COUNTER_I{0,0,0,0}, OMS_ACTUATOR_FAIL_I{0,0,0,0}, PREV_OMSL_ACT_SEL(0), PREV_OMSR_ACT_SEL(0)
	{
		return;
	}

	OMS_RM::~OMS_RM( void )
	{
		return;
	}

	void OMS_RM::OnPreStep( double simt, double simdt, double mjd )
	{
		// TODO engine FDI rate
		step += simdt;
		if (step < 0.16) return;

		unsigned short OMSL_ACT_SEL = ReadCOMPOOL_IS( SCP_OMSL_ACT_SEL );
		unsigned short OMSR_ACT_SEL = ReadCOMPOOL_IS( SCP_OMSR_ACT_SEL );
		float OMS_ACTUATOR_CMD[4];
		float OMS_ACTUATOR_FB[4];
		unsigned short DG[4];

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

		step = 0.0;
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
			case 104:
			case 105:
			case 106:
			case 202:
			case 301:
			case 302:
			case 303:
			case 304:
				return true;
			default:
				return false;
		}
	}
}

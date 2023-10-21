#include "ATT_PROC.h"
#include "../../../Atlantis.h"


namespace dps
{
	ATT_PROC::ATT_PROC( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "ATT_PROC" )
	{
#if 1// for OSFS2016 only, r87 fixes issue
		firststep = true;
		COSPHI_0 = 1.0f;
		SINPHI_0 = 0.0f;
		BETA_0 = 0.0f;
		ALPHA_0 = 0.0f;
		PHI_0 = 0.0f;
#endif// for OSFS2016 only, r87 fixes issue
		return;
	}

	ATT_PROC::~ATT_PROC( void )
	{
		return;
	}

	void ATT_PROC::Realize( void )
	{
		return;
	}

	void ATT_PROC::OnPreStep( double simt, double simdt, double mjd )
	{
		unsigned short ATT_MODE;// 1 = ascent, 2 = transition, 3 = entry
		unsigned short MM = ReadCOMPOOL_IS( SCP_MM );

		// TODO account for TRANS DAP post-MECO?
		switch (MM)
		{
			case 101:
			case 102:
			case 103:
			case 601:
				ATT_MODE = 1;
				break;
			case 104:
			case 105:
			case 106:
			case 301:
			case 302:
			case 303:
				ATT_MODE = 2;
				break;
			case 304:
			case 305:
			case 602:
			case 603:
				ATT_MODE = 3;
				break;
		}

		ATT_PROC_EULER( ATT_MODE, MM );
		ATT_PROC_DISP( ATT_MODE, MM );

#if 1// for OSFS2016 only, r87 fixes issue
		// HACK to avoid wrong data in first timestep, load parameters from scenario (or default values)
		if (firststep)
		{
			firststep = false;
			WriteCOMPOOL_SS( SCP_COSPHI, COSPHI_0 );
			WriteCOMPOOL_SS( SCP_SINPHI, SINPHI_0 );
			WriteCOMPOOL_SS( SCP_BETA_N, BETA_0 );
			WriteCOMPOOL_SS( SCP_ALPHA_N, ALPHA_0 );
			WriteCOMPOOL_SS( SCP_PHI, PHI_0 );
		}
#endif// for OSFS2016 only, r87 fixes issue
		return;
	}

	bool ATT_PROC::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 101:
			case 102:
			case 103:
			case 104:
			case 105:
			case 106:
			case 301:
			case 302:
			case 303:
			case 304:
			case 305:
			case 601:
			case 602:
			case 603:
				return true;
			default:
				return false;
		}
	}

	void ATT_PROC::ATT_PROC_INIT( void )
	{
		return;
	}

	void ATT_PROC::ATT_PROC_OUTER( void )
	{
		return;
	}

	void ATT_PROC::ATT_PROC_INNER( void )
	{
		return;
	}

	void ATT_PROC::ATT_PROC_EULER( const unsigned short ATT_MODE, const unsigned short MM )
	{
		double PHI = -STS()->GetBank();
		WriteCOMPOOL_SS( SCP_COSPHI, static_cast<float>(cos( PHI )) );
		WriteCOMPOOL_SS( SCP_SINPHI, static_cast<float>(sin( PHI )) );

		if (ATT_MODE == 3)
		{
			WriteCOMPOOL_SS( SCP_BANK, static_cast<float>(PHI * DEG) );
		}

		WriteCOMPOOL_SS( SCP_BETA_N, -static_cast<float>(STS()->GetSlipAngle() * DEG) );
		WriteCOMPOOL_SS( SCP_ALPHA_N, static_cast<float>(STS()->GetAOA() * DEG) );

		if ((ATT_MODE == 3) || (MM == 601))
		{
			WriteCOMPOOL_SS( SCP_PSI_HSIMV, static_cast<float>(STS()->GetYaw()) );// TODO runway (mag) hdg
		}

		double THETA = STS()->GetPitch();
		WriteCOMPOOL_SS( SCP_THETA, static_cast<float>(THETA * DEG) );
		WriteCOMPOOL_SS( SCP_SINTH, static_cast<float>(sin( THETA )) );
		WriteCOMPOOL_SS( SCP_COSTH, static_cast<float>(cos( THETA )) );
		WriteCOMPOOL_SS( SCP_PHI, static_cast<float>(PHI * DEG) );
		WriteCOMPOOL_SS( SCP_MEDS_ALPHA, ReadCOMPOOL_SS( SCP_ALPHA_N ) );
		WriteCOMPOOL_SS( SCP_MEDS_BETA, ReadCOMPOOL_SS( SCP_BETA_N ) );
		return;
	}

	void ATT_PROC::ATT_PROC_DISP( const unsigned short ATT_MODE, const unsigned short MM )
	{
		WriteCOMPOOL_VS( SCP_BODY_ERR_ANG, 1, 0.0f, 3 );
		WriteCOMPOOL_VS( SCP_BODY_ERR_ANG, 2, 0.0f, 3 );
		WriteCOMPOOL_VS( SCP_BODY_ERR_ANG, 3, 0.0f, 3 );

		double pitch = STS()->GetPitch();
		double roll = -STS()->GetBank();

		float PTCHSINE[2];
		float PTCHCOS[2];
		float YAWSINE[2];
		float YAWCOS[2];
		float ROLLSINE[2];
		float ROLLCOS[2];
		if (ATT_MODE != 3)
		{
			PTCHSINE[0] = static_cast<float>(sin( pitch ));
			PTCHCOS[0] = static_cast<float>(cos( pitch ));
			YAWSINE[0] = 0.0f;
			YAWCOS[0] = 1.0f;
			ROLLSINE[0] = static_cast<float>(sin( roll ));
			ROLLCOS[0] = static_cast<float>(cos( roll ));

			PTCHSINE[1] = PTCHSINE[0];
			PTCHCOS[1] = PTCHCOS[0];
			YAWSINE[1] = YAWSINE[0];
			YAWCOS[1] = YAWCOS[0];
			ROLLSINE[1] = ROLLSINE[0];
			ROLLCOS[1] = ROLLCOS[0];
		}
		else
		{
			PTCHSINE[0] = static_cast<float>(sin( pitch ));
			PTCHCOS[0] = static_cast<float>(cos( pitch ));
			YAWSINE[0] = 0.0f;
			YAWCOS[0] = 1.0f;
			ROLLSINE[0] = static_cast<float>(sin( roll ));
			ROLLCOS[0] = static_cast<float>(cos( roll ));

			PTCHSINE[1] = PTCHSINE[0];
			PTCHCOS[1] = PTCHCOS[0];
			YAWSINE[1] = YAWSINE[0];
			YAWCOS[1] = YAWCOS[0];
			ROLLSINE[1] = ROLLSINE[0];
			ROLLCOS[1] = ROLLCOS[0];
		}
		WriteCOMPOOL_VS( SCP_PTCHSINE, 1, PTCHSINE[0], 3 );
		WriteCOMPOOL_VS( SCP_PTCHCOS, 1, PTCHCOS[0], 3 );
		WriteCOMPOOL_VS( SCP_YAWSINE, 1, YAWSINE[0], 3 );
		WriteCOMPOOL_VS( SCP_YAWCOS, 1, YAWCOS[0], 3 );
		WriteCOMPOOL_VS( SCP_ROLLSINE, 1, ROLLSINE[0], 3 );
		WriteCOMPOOL_VS( SCP_ROLLCOS, 1, ROLLCOS[0], 3 );

		WriteCOMPOOL_VS( SCP_PTCHSINE, 2, PTCHSINE[1], 3 );
		WriteCOMPOOL_VS( SCP_PTCHCOS, 2, PTCHCOS[1], 3 );
		WriteCOMPOOL_VS( SCP_YAWSINE, 2, YAWSINE[1], 3 );
		WriteCOMPOOL_VS( SCP_YAWCOS, 2, YAWCOS[1], 3 );
		WriteCOMPOOL_VS( SCP_ROLLSINE, 2, ROLLSINE[1], 3 );
		WriteCOMPOOL_VS( SCP_ROLLCOS, 2, ROLLCOS[1], 3 );

		if (fabs( ReadCOMPOOL_SS( SCP_COSTH ) )>= 0.03)
		{
			//STS()->GetYaw() - GetIDP()->GetTargetHeading();
			WriteCOMPOOL_SS( SCP_YAW_IY, static_cast<float>(STS()->GetYaw()) );
		}

		if (1)// TODO NAV INIT
		{
			// TODO fix this
			if (fabs( STS()->GetBank() ) <= 90.0) WriteCOMPOOL_SS( SCP_ROLL_SW, 1 );
			else WriteCOMPOOL_SS( SCP_ROLL_SW, -1 );
		}
		return;
	}

	void ATT_PROC::ATT_PROC_PREFIL( void )
	{
		return;
	}

	void ATT_PROC::ATT_PROC_RGASW( void )
	{
		return;
	}

	void ATT_PROC::ADI_QUAT_UPLINK( void )
	{
		return;
	}

	bool ATT_PROC::OnParseLine( const char* keyword, const char* value )
	{
#if 1// for OSFS2016 only, r87 fixes issue
		if (!_strnicmp( keyword, "COSPHI", 6 ))
		{
			float tmp = 0.0f;
			sscanf_s( value, "%f", &tmp );
			COSPHI_0 = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "SINPHI", 6 ))
		{
			float tmp = 0.0f;
			sscanf_s( value, "%f", &tmp );
			SINPHI_0 = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "BETA", 4 ))
		{
			float tmp = 0.0f;
			sscanf_s( value, "%f", &tmp );
			BETA_0 = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "ALPHA", 5 ))
		{
			float tmp = 0.0f;
			sscanf_s( value, "%f", &tmp );
			ALPHA_0 = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "PHI", 3 ))
		{
			float tmp = 0.0f;
			sscanf_s( value, "%f", &tmp );
			PHI_0 = tmp;
			return true;
		}
#endif// for OSFS2016 only, r87 fixes issue
		return false;
	}

	void ATT_PROC::OnSaveState( FILEHANDLE scn ) const
	{
#if 1// for OSFS2016 only, r87 fixes issue
		float COSPHI = ReadCOMPOOL_SS( SCP_COSPHI );
		float SINPHI = ReadCOMPOOL_SS( SCP_SINPHI );
		float BETA = ReadCOMPOOL_SS( SCP_BETA_N );
		float ALPHA = ReadCOMPOOL_SS( SCP_ALPHA_N );
		float PHI = ReadCOMPOOL_SS( SCP_PHI );

		oapiWriteScenario_float( scn, "COSPHI", COSPHI );
		oapiWriteScenario_float( scn, "SINPHI", SINPHI );
		oapiWriteScenario_float( scn, "BETA", BETA );
		oapiWriteScenario_float( scn, "ALPHA", ALPHA );
		oapiWriteScenario_float( scn, "PHI", PHI );
#endif// for OSFS2016 only, r87 fixes issue
		return;
	}
}

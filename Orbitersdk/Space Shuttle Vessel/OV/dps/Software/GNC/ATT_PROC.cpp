#include "ATT_PROC.h"
#include "../../../Atlantis.h"
#include <MathSSV.h>


namespace dps
{
	ATT_PROC::ATT_PROC( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "ATT_PROC" )
	{
		return;
	}

	ATT_PROC::~ATT_PROC( void )
	{
		return;
	}

	void ATT_PROC::OnPreStep( double simt, double simdt, double mjd )
	{
		unsigned short ATT_MODE;// 1 = ascent, 2 = transition, 3 = entry
		unsigned short MECO_CMD = ReadCOMPOOL_IS( SCP_MECO_CMD );
		unsigned short MM_CODE_101 = ReadCOMPOOL_IS( SCP_MM_CODE_101 );
		unsigned short MM_CODE_102 = ReadCOMPOOL_IS( SCP_MM_CODE_102 );
		unsigned short MM_CODE_103 = ReadCOMPOOL_IS( SCP_MM_CODE_103 );
		unsigned short MM_CODE_304 = ReadCOMPOOL_IS( SCP_MM_CODE_304 );
		unsigned short MM_CODE_305 = ReadCOMPOOL_IS( SCP_MM_CODE_305 );
		unsigned short MM_CODE_601 = ReadCOMPOOL_IS( SCP_MM_CODE_601 );
		unsigned short MM_CODE_602 = ReadCOMPOOL_IS( SCP_MM_CODE_602 );
		unsigned short MM_CODE_603 = ReadCOMPOOL_IS( SCP_MM_CODE_603 );

		if (((MM_CODE_101 == 1) || (MM_CODE_102 == 1) || (MM_CODE_103 == 1) || (MM_CODE_601 == 1)) && (MECO_CMD == 0))
		{
			ATT_MODE = 1;
		}
		else if ((MM_CODE_304 == 1) || (MM_CODE_305 == 1) || (MM_CODE_602 == 1) || (MM_CODE_603 == 1))
		{
			ATT_MODE = 3;
		}
		else
		{
			ATT_MODE = 2;
		}

		ATT_PROC_EULER( ATT_MODE );
		ATT_PROC_DISP( ATT_MODE );
		return;
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

	void ATT_PROC::ATT_PROC_EULER( const unsigned short ATT_MODE )
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

		if ((ATT_MODE == 3) || (ReadCOMPOOL_IS( SCP_MM_CODE_601 ) == 1))
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

	void ATT_PROC::ATT_PROC_DISP( const unsigned short ATT_MODE )
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
		WriteCOMPOOL_ASS( SCP_PTCHSINE, 1, PTCHSINE[0], 3 );
		WriteCOMPOOL_ASS( SCP_PTCHCOS, 1, PTCHCOS[0], 3 );
		WriteCOMPOOL_ASS( SCP_YAWSINE, 1, YAWSINE[0], 3 );
		WriteCOMPOOL_ASS( SCP_YAWCOS, 1, YAWCOS[0], 3 );
		WriteCOMPOOL_ASS( SCP_ROLLSINE, 1, ROLLSINE[0], 3 );
		WriteCOMPOOL_ASS( SCP_ROLLCOS, 1, ROLLCOS[0], 3 );

		WriteCOMPOOL_ASS( SCP_PTCHSINE, 2, PTCHSINE[1], 3 );
		WriteCOMPOOL_ASS( SCP_PTCHCOS, 2, PTCHCOS[1], 3 );
		WriteCOMPOOL_ASS( SCP_YAWSINE, 2, YAWSINE[1], 3 );
		WriteCOMPOOL_ASS( SCP_YAWCOS, 2, YAWCOS[1], 3 );
		WriteCOMPOOL_ASS( SCP_ROLLSINE, 2, ROLLSINE[1], 3 );
		WriteCOMPOOL_ASS( SCP_ROLLCOS, 2, ROLLCOS[1], 3 );

		if (fabs( ReadCOMPOOL_SS( SCP_COSTH )) >= 0.03)
		{
			//STS()->GetYaw() - GetIDP()->GetTargetHeading();
			float YAW_IY = static_cast<float>(STS()->GetYaw());

			WriteCOMPOOL_SS( SCP_YAW_IY, YAW_IY );
		}

		if (1)// TODO NAV INIT
		{
			double sgn = sign( PI05 - fabs( roll ) );
			WriteCOMPOOL_IS( SCP_ROLL_SW, static_cast<short>(sgn) );
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
}

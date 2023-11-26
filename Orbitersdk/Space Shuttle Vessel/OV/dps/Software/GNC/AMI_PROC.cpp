#include "AMI_PROC.h"
#include <MathSSV.h>
#include <EngConst.h>


namespace dps
{
	constexpr float KTS_PER_FPS = static_cast<float>(MPS2KTS / MPS2FPS);
	const float G_FPS = static_cast<float>(G * MPS2FPS);


	AMI_PROC::AMI_PROC( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "AMI_PROC" )
	{
		return;
	}

	AMI_PROC::~AMI_PROC( void )
	{
		return;
	}

	void AMI_PROC::Realize( void )
	{
		return;
	}

	void AMI_PROC::OnPostStep( double simt, double simdt, double mjd )
	{
		// TODO FOH

		// inputs
		unsigned short MM = ReadCOMPOOL_IS( SCP_MM );
		unsigned short ADPVALIDC = ReadCOMPOOL_IS( SCP_ADPVALIDC );
		unsigned short ADPVALIDP = ReadCOMPOOL_IS( SCP_ADPVALIDP );
		unsigned short S_RTLS_TURN = 0;// TODO
		float DDMC = ReadCOMPOOL_SS( SCP_DDMC );
		float DDMP = ReadCOMPOOL_SS( SCP_DDMP );
		float REL_VEL_MAG = ReadCOMPOOL_SS( SCP_REL_VEL_MAG );
		float V_INERTIAL_MAG = ReadCOMPOOL_SS( SCP_V_INERTIAL_MAG );
		float DDALPHAC = ReadCOMPOOL_SS( SCP_DDALPHAC );
		float DDALPHAP = ReadCOMPOOL_SS( SCP_DDALPHAP );
		float MEDS_ALPHA = ReadCOMPOOL_SS( SCP_MEDS_ALPHA );
		float DDEASC = ReadCOMPOOL_SS( SCP_DDEASC );
		float DDEASP = ReadCOMPOOL_SS( SCP_DDEASP );
		float EAS = ReadCOMPOOL_SS( SCP_EAS );
		unsigned short WOWLON = ReadCOMPOOL_IS( SCP_WOWLON_IND );
		float ACC_DRAG = ReadCOMPOOL_SS( SCP_ACC_DRAG );
		float NZ = ReadCOMPOOL_SS( SCP_NZ );
		float LOAD_TOTAL = ReadCOMPOOL_SS( SCP_LOAD_TOTAL );

		// outputs
		unsigned short LMACOUT = 0;
		unsigned short RMACOUT = 0;
		unsigned short LALPOUT = 0;
		unsigned short RALPOUT = 0;
		unsigned short LEASOUT = 0;
		unsigned short REASOUT = 0;
		unsigned short LTACOUT = 0;
		unsigned short RTACOUT = 0;

		// Left/Right AMI Control Words (LAMI1/RAMI1)
		unsigned short LAMI_C2 = 1;
		unsigned short LAMI_C3 = 1;
		unsigned short LAMI_C4 = 1;
		unsigned short LAMI_C5 = 1;
		unsigned short LAMI_C6 = 1;
		unsigned short RAMI_C2 = 1;
		unsigned short RAMI_C3 = 1;
		unsigned short RAMI_C4 = 1;
		unsigned short RAMI_C5 = 1;
		unsigned short RAMI_C6 = 1;
		if ((MM == 102) || (MM == 103) || (MM == 601))
		{
			LAMI_C3 = 1;
			LAMI_C4 = 1;
			LAMI_C5 = 1;
			LAMI_C6 = 1;
			RAMI_C3 = 1;
			RAMI_C4 = 1;
			RAMI_C5 = 1;
			RAMI_C6 = 1;
		}
		else //if ((MM == 304) || (MM == 305) || (MM == 602) || (MM == 603))
		{
			LAMI_C3 = ADPVALIDC;
			LAMI_C4 = ADPVALIDC;
			LAMI_C5 = ADPVALIDC;
			RAMI_C3 = ADPVALIDP;
			RAMI_C4 = ADPVALIDP;
			RAMI_C5 = ADPVALIDP;
			LAMI_C6 = 1;
			RAMI_C6 = 1;
		}
		unsigned short LAMI1 = (LAMI_C2 << 15) | (LAMI_C3 << 14) | (LAMI_C4 << 13) | (LAMI_C5 << 12) | (LAMI_C6 << 11);
		unsigned short RAMI1 = (RAMI_C2 << 15) | (RAMI_C3 << 14) | (RAMI_C4 << 13) | (RAMI_C5 << 12) | (RAMI_C6 << 11);
		// TODO handle C3 freeze in MM104

		// Left Test Word (LAMI2)
		unsigned short LAMI2 = 0b1010101010101001;

		// Right Test Word (RAMI2)
		unsigned short RAMI2 = 0b1010101010101001;

		// Left/Right AMI_Mach Number (LMACOUT/RMACOUT) 160 ms
		double LM_C = 0.0;
		double LM_P = 0.0;
		if ((MM == 304) || (MM == 305) || (MM == 602) || (MM == 603))
		{
			LM_C = DDMC;
			LM_P = DDMP;
		}
		else if ((MM == 102) || ((MM == 601) && (S_RTLS_TURN == 1)))
		{
			LM_C = range( 0, REL_VEL_MAG / 1000.0, 27 );
			LM_P = LM_C;
		}
		else //if ((MM == 103) || ((MM == 601) && (S_RTLS_TURN == 0)))
		{
			LM_C = range( 0, V_INERTIAL_MAG / 1000.0, 27 );
			LM_P = LM_C;
		}
		LMACOUT = 8 * static_cast<unsigned short>(LM_C / 0.0075);// (LSB = 0.0075 mach)
		RMACOUT = 8 * static_cast<unsigned short>(LM_P / 0.0075);// (LSB = 0.0075 mach)

		// Left/Right AMI_Alpha (LALPOUT/RALPOUT) 160 ms
		double LAA_C = 0.0;
		double LAA_P = 0.0;
		if ((MM == 304) || (MM == 305) || (MM == 603))
		{
			LAA_C = DDALPHAC;
			LAA_P = DDALPHAP;
		}
		else if ((MM == 102) || (MM == 103) || (MM == 601))
		{
			LAA_C = MEDS_ALPHA;
			LAA_P = LAA_C;
		}
		else //if (MM == 602)
		{
			LAA_C = MEDS_ALPHA;
			LAA_P = LAA_C;
		}
		LALPOUT = 2 * static_cast<unsigned short>(LAA_C / 0.015);// (LSB = 0.015 DEG)
		RALPOUT = 2 * static_cast<unsigned short>(LAA_P / 0.015);// (LSB = 0.015 DEG)

		// Left/Right AMI_Equivalent Airspeed (LEASOUT/REASOUT) 960 ms
		double EA_C = 0.0;
		double EA_P = 0.0;
		if ((MM == 304) || (MM == 305) || (MM == 603))
		{
			EA_C = DDEASC * KTS_PER_FPS;
			EA_P = DDEASP * KTS_PER_FPS;
		}
		else //if ((MM == 102) || (MM == 103) || (MM == 601))
		{
			EA_C = EAS * KTS_PER_FPS;
			EA_P = EA_C;
		}
		double LEA_C = range( 0, EA_C, 500 );
		double LEA_P = range( 0, EA_P, 500 );
		LEASOUT = 8 * static_cast<unsigned short>(LEA_C / 0.125);// (LSB = 0.125 knots)
		REASOUT = 8 * static_cast<unsigned short>(LEA_P / 0.125);// (LSB = 0.125 knots)

		// Left/Right AMI_Vehicle Acceleration (LTACOUT/RTACOUT) 160 ms
		double TAC = 0.0;
		if (((MM == 305) || (MM == 603)) && (WOWLON == 1))
		{
			TAC = -ACC_DRAG / G_FPS;
		}
		else if ((MM == 304) || (MM == 602) || (((MM == 305) || (MM == 603)) && (WOWLON == 0)))
		{
			TAC = NZ;
		}
		else //if ((MM == 102) || (MM == 103) || (MM == 601))
		{
			TAC = LOAD_TOTAL;
		}
		double LTAC = range( -5.0, TAC, 10 );
		if (LTAC < 0)
		{
			LTACOUT = 8 * static_cast<unsigned short>(-LTAC / 0.00125);// (LSB = .00125 g's)
			LTACOUT |= 0x8000;// sign
		}
		else
		{
			LTACOUT = 8 * static_cast<unsigned short>(LTAC / 0.00250);// (LSB = .00250 g's)
		}
		RTACOUT = LTACOUT;


		// output
		// Word 1 Cont Word
		WriteCOMPOOL_AIS( SCP_DDU1_AMI, 1, LAMI1, 6 );
		WriteCOMPOOL_AIS( SCP_DDU2_AMI, 1, RAMI1, 6 );
		// Word 2 AMI Test Word
		WriteCOMPOOL_AIS( SCP_DDU1_AMI, 2, LAMI2, 6 );
		WriteCOMPOOL_AIS( SCP_DDU2_AMI, 2, RAMI2, 6 );
		// Word 3 Mach Number
		WriteCOMPOOL_AIS( SCP_DDU1_AMI, 3, LMACOUT, 6 );
		WriteCOMPOOL_AIS( SCP_DDU2_AMI, 3, RMACOUT, 6 );
		// Word 4 Alpha
		WriteCOMPOOL_AIS( SCP_DDU1_AMI, 4, LALPOUT, 6 );
		WriteCOMPOOL_AIS( SCP_DDU2_AMI, 4, RALPOUT, 6 );
		// Word 5 Equiv. Air Speed
		WriteCOMPOOL_AIS( SCP_DDU1_AMI, 5, LEASOUT, 6 );
		WriteCOMPOOL_AIS( SCP_DDU2_AMI, 5, REASOUT, 6 );
		// Word 6 Vehicle Acceleration
		WriteCOMPOOL_AIS( SCP_DDU1_AMI, 6, LTACOUT, 6 );
		WriteCOMPOOL_AIS( SCP_DDU2_AMI, 6, RTACOUT, 6 );
		return;
	}

	bool AMI_PROC::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 102:
			case 103:
			case 104:
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

	bool AMI_PROC::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void AMI_PROC::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}
}

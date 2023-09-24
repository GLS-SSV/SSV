#include "AVVI_PROC.h"
#include <MathSSV.h>


namespace dps
{
	// K-Loads
	constexpr float RA_CONST = 18.2f;// ANT/WHEEL DIST-NOM LDG ATT (V97U6861C) [ft]


	AVVI_PROC::AVVI_PROC( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "AVVI_PROC" )
	{
		return;
	}

	AVVI_PROC::~AVVI_PROC( void )
	{
		return;
	}

	void AVVI_PROC::Realize( void )
	{
		return;
	}

	void AVVI_PROC::OnPostStep( double simt, double simdt, double mjd )
	{
		// TODO FOH

		// inputs
		unsigned short MM = ReadCOMPOOL_IS( SCP_MM );
		unsigned short ADPVALIDC = ReadCOMPOOL_IS( SCP_ADPVALIDC );
		unsigned short ADPVALIDP = ReadCOMPOOL_IS( SCP_ADPVALIDP );
		unsigned short LRAS1 = ReadCOMPOOL_IS( SCP_LRAS1 );
		unsigned short RRAS1 = ReadCOMPOOL_IS( SCP_RRAS1 );
		unsigned short RALT_CMLK[2];
		RALT_CMLK[0] = ReadCOMPOOL_AIS( SCP_RALT_CMLK, 1, 2 );
		RALT_CMLK[1] = ReadCOMPOOL_AIS( SCP_RALT_CMLK, 2, 2 );
		float ALT_RW = ReadCOMPOOL_SS( SCP_ALT_RW );
		float DELH_MSL_ELLIPSOID_RW = ReadCOMPOOL_SS( SCP_DELH_MSL_ELLIPSOID_RW );
		unsigned short LADS = 0;// TODO
		unsigned short RADS = 0;// TODO
		float DDALTC = ReadCOMPOOL_SS( SCP_DDALTC );
		float DDALTP = ReadCOMPOOL_SS( SCP_DDALTP );
		float ALT = ReadCOMPOOL_SS( SCP_ALT );
		float DDHDOTC = ReadCOMPOOL_SS( SCP_DDHDOTC );
		float DDHDOTP = ReadCOMPOOL_SS( SCP_DDHDOTP );
		float H_DOT = ReadCOMPOOL_SS( SCP_H_DOT );
		float H_DOT_ELLIPSOID = ReadCOMPOOL_SS( SCP_H_DOT_ELLIPSOID );
		float RA_ALTO[2];
		RA_ALTO[0] = ReadCOMPOOL_VS( SCP_RA_ALTO, 1, 2 );
		RA_ALTO[1] = ReadCOMPOOL_VS( SCP_RA_ALTO, 2, 2 );
		float ACC_VERT = ReadCOMPOOL_SS( SCP_ACC_VERT );

		// outputs
		unsigned short LALTOUT = 0;
		unsigned short RALTOUT = 0;
		unsigned short LVVLOUT = 0;
		unsigned short RVVLOUT = 0;
		unsigned short LRAOUT = 0;
		unsigned short RRAOUT = 0;
		unsigned short LVACOUT = 0;
		unsigned short RVACOUT = 0;


		// Left/Right AVVI_Control Word (LAVVI1/RAVVI1) 960 ms
		unsigned short LAVVI_C2 = 1;
		unsigned short LAVVI_C3 = 1;
		unsigned short LAVVI_C4 = 1;
		unsigned short LAVVI_C5 = 1;
		unsigned short LAVVI_C6 = 1;
		unsigned short RAVVI_C2 = 1;
		unsigned short RAVVI_C3 = 1;
		unsigned short RAVVI_C4 = 1;
		unsigned short RAVVI_C5 = 1;
		unsigned short RAVVI_C6 = 1;
		if ((MM == 102) || (MM == 103) || (MM == 601))
		{
			LAVVI_C3 = 1;
			LAVVI_C4 = 1;
			RAVVI_C3 = 1;
			RAVVI_C4 = 1;
			LAVVI_C5 = 0;
			LAVVI_C6 = 0;
			RAVVI_C5 = 0;
			RAVVI_C6 = 0;
		}
		else //if ((MM == 304) || (MM == 305) || (MM == 602) || (MM == 603))
		{
			LAVVI_C3 = ADPVALIDC;
			LAVVI_C4 = ADPVALIDC;
			RAVVI_C3 = ADPVALIDP;
			RAVVI_C4 = ADPVALIDP;
			if (((LRAS1 == 1) && (RALT_CMLK[0] == 1)) || ((LRAS1 == 2) && (RALT_CMLK[1] == 1)))
			{
				LAVVI_C5 = 1;
			}
			else
			{
				LAVVI_C5 = 0;
			}
			if (((RRAS1 == 1) && (RALT_CMLK[0] == 1)) || ((RRAS1 == 2) && (RALT_CMLK[1] == 1)))
			{
				RAVVI_C5 = 1;
			}
			else
			{
				RAVVI_C5 = 0;
			}
			LAVVI_C6 = 1;
			RAVVI_C6 = 1;
		}
		unsigned short LAVVI1 = (LAVVI_C2 << 15) | (LAVVI_C3 << 14) | (LAVVI_C4 << 13) | (LAVVI_C5 << 12) | (LAVVI_C6 << 11);
		unsigned short RAVVI1 = (RAVVI_C2 << 15) | (RAVVI_C3 << 14) | (RAVVI_C4 << 13) | (RAVVI_C5 << 12) | (RAVVI_C6 << 11);
		// TODO handle C3 and C4 freeze in MM104

		// Left AVVI_Test Word (LAVVI2)
		unsigned short LAVVI2 = 0b1010101010101001;

		// Right AVVI_Test Word (RAVVI2)
		unsigned short RAVVI2 = 0b1010101010101001;

		// Left/Right AVVI Indicated Altitude (LALTOUT/RALTOUT) 160 ms
		double ALT_L = 0.0;
		double ALT_R = 0.0;
		if ((MM == 304) || (MM == 305) || (MM == 602) || (MM == 603))
		{
			double RW_ALT_MSL = ALT_RW - DELH_MSL_ELLIPSOID_RW;
			if (LADS == 1)
			{
				ALT_L = DDALTC - RW_ALT_MSL;
			}
			else //if (LADS == 0)
			{
				ALT_L = DDALTC - ALT_RW;
			}

			if (RADS == 1)
			{
				ALT_R = DDALTP - RW_ALT_MSL;
			}
			else //if (RADS == 0)
			{
				ALT_R = DDALTP - ALT_RW;
			}
		}
		else //if ((MM == 102) || (MM == 103) || (MM == 601))
		{
			ALT_L = ALT - ALT_RW;
			ALT_R = ALT_L;
		}
		double LA = range( -1100, ALT_L, 1e6 );
		if ((-1100 <= LA) && (LA < -100))
		{
			LALTOUT = 8 * static_cast<unsigned short>(220 + (0.2 * LA));// (LSB = 5 ft)
		}
		else if ((-100 <= LA) && (LA <= 0))
		{
			LALTOUT = 8 * static_cast<unsigned short>(280 + (0.8 * LA));// (LSB = 1.25 ft)
		}
		else if ((0 <= LA) && (LA <= 500))
		{
			LALTOUT = 8 * static_cast<unsigned short>(280 + (0.6343 * LA) - (0.4686e-3 * LA * LA));// (LSB = Variable)
		}
		else if ((500 < LA) && (LA < 1e5))
		{
			LALTOUT = 8 * static_cast<unsigned short>(470 + (0.02 * LA));// (LSB = 50 ft)
		}
		else //if ((1e5 <= LA) && (LA < 1e6))
		{
			LALTOUT = 8 * static_cast<unsigned short>(200 + 300 + 1970 + ((LA - 1e5) / 625.0));// (LSB = 625 ft)
		}
		LA = range( -1100, ALT_R, 1e6 );
		if ((-1100 <= LA) && (LA < -100))
		{
			RALTOUT = 8 * static_cast<unsigned short>(220 + (0.2 * LA));// (LSB = 5 ft)
		}
		else if ((-100 <= LA) && (LA <= 0))
		{
			RALTOUT = 8 * static_cast<unsigned short>(280 + (0.8 * LA));// (LSB = 1.25 ft)
		}
		else if ((0 <= LA) && (LA <= 500))
		{
			RALTOUT = 8 * static_cast<unsigned short>(280 + (0.6343 * LA) - (0.4686e-3 * LA * LA));// (LSB = Variable)
		}
		else if ((500 < LA) && (LA < 1e5))
		{
			RALTOUT = 8 * static_cast<unsigned short>(470 + (0.02 * LA));// (LSB = 50 ft)
		}
		else //if ((1e5 <= LA) && (LA < 1e6))
		{
			RALTOUT = 8 * static_cast<unsigned short>(200 + 300 + 1970 + ((LA - 1e5) / 625.0));// (LSB = 625 ft)
		}

		// Left/Right AVVI Vertical Velocity (LVVLOUT/RVVLOUT) 160 ms
		float VV_L = 0.0;
		float VV_R = 0.0;
		if ((MM == 304) || (MM == 305) || (MM == 602) || (MM == 603))
		{
			VV_L = DDHDOTC;
			VV_R = DDHDOTP;
		}
		else if ((MM == 102) || (MM == 103))
		{
			VV_L = H_DOT;
			VV_R = H_DOT;
		}
		else //if (MM == 601)
		{
			VV_L = H_DOT_ELLIPSOID;
			VV_R = H_DOT_ELLIPSOID;
		}
		double LVV = range( -2940, VV_L, 2940 );
		if (fabs( LVV ) <= 100)
		{
			LVVLOUT = 8 * static_cast<unsigned short>((-sign( LVV ) * 0.0292875 * LVV * LVV) + (7.92875 * LVV));// (LSB = VAR)
		}
		else if ((100 < fabs( LVV )) && (fabs( LVV ) <= 740))
		{
			LVVLOUT = 8 * static_cast<unsigned short>((187.5 * sign( LVV )) + (3.125 * LVV));// (LSB = .32 fps)
		}
		else //if ((740 < fabs( LVV )) && (fabs( LVV ) <= 2940))
		{
			LVVLOUT = 8 * static_cast<unsigned short>((2204 * sign( LVV )) + (0.4 * LVV));// (LSB = 2.5 fps)
		}
		LVV = range( -2940, VV_R, 2940 );
		if (fabs( LVV ) <= 100)
		{
			RVVLOUT = 8 * static_cast<unsigned short>((-sign( LVV ) * 0.0292875 * LVV * LVV) + (7.92875 * LVV));// (LSB = VAR)
		}
		else if ((100 < fabs( LVV )) && (fabs( LVV ) <= 740))
		{
			RVVLOUT = 8 * static_cast<unsigned short>((187.5 * sign( LVV )) + (3.125 * LVV));// (LSB = .32 fps)
		}
		else //if ((740 < fabs( LVV )) && (fabs( LVV ) <= 2940))
		{
			RVVLOUT = 8 * static_cast<unsigned short>((2204 * sign( LVV )) + (0.4 * LVV));// (LSB = 2.5 fps)
		}

		// Left/Right AVVI Radar Altitude (LRAOUT/RRAOUT) 160 ms
		if ((MM == 304) || (MM == 305) || (MM == 602) || (MM == 603))
		{
			double SRA_L = 0.0;
			double SRA_R = 0.0;
			if (LRAS1 == 2)
			{
				SRA_L = RA_ALTO[1] - RA_CONST;
			}
			else
			{
				SRA_L = RA_ALTO[0] - RA_CONST;
			}
			if (RRAS1 == 2)
			{
				SRA_R = RA_ALTO[1] - RA_CONST;
			}
			else
			{
				SRA_R = RA_ALTO[0] - RA_CONST;
			}

			double LRA = range( 0, SRA_L, 9000 );
			if ((0 <= LRA) && (LRA < 500))
			{
				LRAOUT = 16 * static_cast<unsigned short>((3.1715 * LRA) - (2.343e-3 * LRA * LRA));// (LSB = variable)
			}
			else if ((500 <= LRA) && (LRA < 9000))
			{
				LRAOUT = 16 * static_cast<unsigned short>(1000 + ((LRA - 500) / 10.0));// (LSB = 10ft)
			}
			LRA = range( 0, SRA_R, 9000 );
			if ((0 <= LRA) && (LRA < 500))
			{
				RRAOUT = 16 * static_cast<unsigned short>((3.1715 * LRA) - (2.343e-3 * LRA * LRA));// (LSB = variable)
			}
			else if ((500 <= LRA) && (LRA < 9000))
			{
				RRAOUT = 16 * static_cast<unsigned short>(1000 + ((LRA - 500) / 10.0));// (LSB = 10ft)
			}
		}
		// TODO RA needle park

		// Left/Right AVVI Vertical Acceleration (LVACOUT/RVACOUT) 160 ms
		if ((MM == 304) || (MM == 305) || (MM == 602) || (MM == 603))
		{
			double LVA = range( -12.75, ACC_VERT, 12.75 );
			LVACOUT = 128 * static_cast<unsigned short>(LVA / 0.05);// (LSB = 0.05 fps2)
			RVACOUT = LVACOUT;
		}


		// output
		// Word 1 AVVI Contl Word
		WriteCOMPOOL_AIS( SCP_DDU1_AVVI, 1, LAVVI1, 6 );
		WriteCOMPOOL_AIS( SCP_DDU2_AVVI, 1, RAVVI1, 6 );
		// Word 2 AVVI Test Word
		WriteCOMPOOL_AIS( SCP_DDU1_AVVI, 2, LAVVI2, 6 );
		WriteCOMPOOL_AIS( SCP_DDU2_AVVI, 2, RAVVI2, 6 );
		// Word 3 Indic Alt
		WriteCOMPOOL_AIS( SCP_DDU1_AVVI, 3, LALTOUT, 6 );
		WriteCOMPOOL_AIS( SCP_DDU2_AVVI, 3, RALTOUT, 6 );
		// Word 4 Vertical Velocity
		WriteCOMPOOL_AIS( SCP_DDU1_AVVI, 4, LVVLOUT, 6 );
		WriteCOMPOOL_AIS( SCP_DDU2_AVVI, 4, RVVLOUT, 6 );
		// Word 5 Radar Alt
		WriteCOMPOOL_AIS( SCP_DDU1_AVVI, 5, LRAOUT, 6 );
		WriteCOMPOOL_AIS( SCP_DDU2_AVVI, 5, RRAOUT, 6 );
		// Word 6 vertical Acceleration
		WriteCOMPOOL_AIS( SCP_DDU1_AVVI, 6, LVACOUT, 6 );
		WriteCOMPOOL_AIS( SCP_DDU2_AVVI, 6, RVACOUT, 6 );
		return;
	}

	bool AVVI_PROC::OnMajorModeChange( unsigned int newMajorMode )
	{
		// TODO init validity flags on transition
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

	bool AVVI_PROC::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void AVVI_PROC::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}
}

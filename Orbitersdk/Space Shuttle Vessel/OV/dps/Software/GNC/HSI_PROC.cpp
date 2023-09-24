#include "HSI_PROC.h"
#include <MathSSV.h>


namespace dps
{
	static float MOD( float val, float lim )
	{
		while (val > lim) val -= lim;
		while (val < 0) val += lim;
		return val;
	}

	static unsigned short BCD( unsigned short in )
	{
		unsigned short ret = 0;
		unsigned short sh = 0;
		while (in > 0)
		{
			ret |= (in % 10) << (sh << 2);
			sh++;
			in /= 10;
		}
		return ret;
	}

	// I-Loads
	constexpr float ALT_HEAT = 200000.0f;// (V97U1408C) [ft]
	constexpr float MET_HEAT = 150.0f;// (V97U2060C) [s]


	HSI_PROC::HSI_PROC( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "HSI_PROC" )
	{
		return;
	}

	HSI_PROC::~HSI_PROC( void )
	{
		return;
	}

	void HSI_PROC::Realize( void )
	{
		return;
	}

	void HSI_PROC::OnPostStep( double simt, double simdt, double mjd )
	{
		// TODO FOH

		// inputs
		unsigned short MM = ReadCOMPOOL_IS( SCP_MM );
		unsigned short TAL_ABORT_DECLARED = 0;// TODO
		unsigned short HDG_FLAG_LEFT = ReadCOMPOOL_IS( SCP_HDG_FLAG_LEFT );
		unsigned short HDG_FLAG_RIGHT = ReadCOMPOOL_IS( SCP_HDG_FLAG_RIGHT );
		unsigned short BRG_FLAG_LEFT = ReadCOMPOOL_IS( SCP_BRG_FLAG_LEFT );
		unsigned short BRG_FLAG_RIGHT = ReadCOMPOOL_IS( SCP_BRG_FLAG_RIGHT );
		unsigned short CDI_FLAG_LEFT = ReadCOMPOOL_IS( SCP_CDI_FLAG_LEFT );
		unsigned short CDI_FLAG_RIGHT = ReadCOMPOOL_IS( SCP_CDI_FLAG_RIGHT );
		unsigned short GSI_FLAG_LEFT = ReadCOMPOOL_IS( SCP_GSI_FLAG_LEFT );
		unsigned short GSI_FLAG_RIGHT = ReadCOMPOOL_IS( SCP_GSI_FLAG_RIGHT );
		float AZIMUTH_RW = ReadCOMPOOL_SS( SCP_AZIMUTH_RW );
		float ANGLE_CORR_TNTOMAG_RW = ReadCOMPOOL_SS( SCP_ANGLE_CORR_TNTOMAG_RW );
		float HEADING_LEFT = ReadCOMPOOL_SS( SCP_HEADING_LEFT );
		float HEADING_RIGHT = ReadCOMPOOL_SS( SCP_HEADING_RIGHT );
		unsigned short ROLL_SW = ReadCOMPOOL_IS( SCP_ROLL_SW );
		float YAW_IY = ReadCOMPOOL_SS( SCP_YAW_IY );
		float HEADING_ATO = ReadCOMPOOL_SS( SCP_HEADING_ATO );
		float HEADING_TAL = ReadCOMPOOL_SS( SCP_HEADING_TAL );
		float HEADING_V_I = ReadCOMPOOL_SS( SCP_HEADING_V_I );
		float PSI_HSIMV = ReadCOMPOOL_SS( SCP_PSI_HSIMV );
		float PRIBEAR_LEFT = ReadCOMPOOL_SS( SCP_PRIBEAR_LEFT );
		float PRIBEAR_RIGHT = ReadCOMPOOL_SS( SCP_PRIBEAR_RIGHT );
		float HEADING_RW = ReadCOMPOOL_SS( SCP_HEADING_RW );
		float SECBEAR_LEFT = ReadCOMPOOL_SS( SCP_SECBEAR_LEFT );
		float SECBEAR_RIGHT = ReadCOMPOOL_SS( SCP_SECBEAR_RIGHT );
		float PRIRANGE_LEFT = ReadCOMPOOL_SS( SCP_PRIRANGE_LEFT );
		float PRIRANGE_RIGHT = ReadCOMPOOL_SS( SCP_PRIRANGE_RIGHT );
		float SECRANGE_LEFT = ReadCOMPOOL_SS( SCP_SECRANGE_LEFT );
		float SECRANGE_RIGHT = ReadCOMPOOL_SS( SCP_SECRANGE_RIGHT );
		float V_GROUNDSPEED = ReadCOMPOOL_SS( SCP_V_GROUNDSPEED );
		float PW_RANGE = ReadCOMPOOL_SS( SCP_PW_RANGE );
		float CDI_LEFT = ReadCOMPOOL_SS( SCP_CDI_LEFT );
		float CDI_RIGHT = ReadCOMPOOL_SS( SCP_CDI_RIGHT );
		float XTRK_CDI = ReadCOMPOOL_SS( SCP_XTRK_CDI );
		unsigned short CDI_SCALE = ReadCOMPOOL_IS( SCP_CDI_SCALE );
		float GSI_LEFT = ReadCOMPOOL_SS( SCP_GSI_LEFT );
		float GSI_RIGHT = ReadCOMPOOL_SS( SCP_GSI_RIGHT );
		double CLOCKTIME = ReadCOMPOOL_SD( SCP_CLOCK );
		double T_GMTLO = ReadCOMPOOL_SD( SCP_T_MET_REF );
		float ALT = ReadCOMPOOL_SS( SCP_ALT );
		float HEADING_V_REL = ReadCOMPOOL_SS( SCP_HEADING_V_REL );

		// outputs
		unsigned short HLWORD3 = 0;
		unsigned short HRWORD3 = 0;
		unsigned short HLWORD4 = 0;
		unsigned short HRWORD4 = 0;
		unsigned short HLWORD5 = 0;
		unsigned short HRWORD5 = 0;
		unsigned short HLWORD6 = 0;
		unsigned short HRWORD6 = 0;
		unsigned short HLWORD7 = 0;
		unsigned short HRWORD7 = 0;
		unsigned short HLWORD8 = 0;
		unsigned short HRWORD8 = 0;
		unsigned short HLWORD9 = 0;
		unsigned short HRWORD9 = 0;
		unsigned short HLWORD10 = 0;
		unsigned short HRWORD10 = 0;
		unsigned short MEDS_BETAHVR_VALID = 0;
		unsigned short MEDS_H_VR = 0;

		// Control Word (HLWORD1) 960 ms
		unsigned short LHSI_C2 = 1;
		unsigned short LHSI_C3 = 1;
		unsigned short LHSI_C4 = 1;
		unsigned short LHSI_C5 = 1;
		unsigned short LHSI_C6 = 1;
		unsigned short LHSI_C7 = 1;
		unsigned short LHSI_C8 = 1;
		unsigned short LHSI_C9 = 1;
		unsigned short LHSI_C10 = 1;
		unsigned short RHSI_C2 = 1;
		unsigned short RHSI_C3 = 1;
		unsigned short RHSI_C4 = 1;
		unsigned short RHSI_C5 = 1;
		unsigned short RHSI_C6 = 1;
		unsigned short RHSI_C7 = 1;
		unsigned short RHSI_C8 = 1;
		unsigned short RHSI_C9 = 1;
		unsigned short RHSI_C10 = 1;
		if ((MM == 101) || (MM == 102) || (MM == 103) || (MM == 601))
		{
			LHSI_C4 = 1;
			LHSI_C8 = 0;
			LHSI_C10 = 0;
			RHSI_C4 = 1;
			RHSI_C8 = 0;
			RHSI_C10 = 0;
			if (MM == 601)
			{
				LHSI_C5 = 1;
				LHSI_C7 = 1;
				LHSI_C3 = 0;
				LHSI_C6 = 0;
				LHSI_C9 = 0;
				RHSI_C5 = 1;
				RHSI_C7 = 1;
				RHSI_C3 = 0;
				RHSI_C6 = 0;
				RHSI_C9 = 0;
			}
			else
			{
				LHSI_C3 = 1;
				LHSI_C6 = 1;
				LHSI_C9 = 1;
				RHSI_C3 = 1;
				RHSI_C6 = 1;
				RHSI_C9 = 1;
				if (TAL_ABORT_DECLARED == 1)
				{
					LHSI_C5 = 1;
					LHSI_C7 = 1;
					RHSI_C5 = 1;
					RHSI_C7 = 1;
				}
				else
				{
					LHSI_C5 = 0;
					LHSI_C7 = 0;
					RHSI_C5 = 0;
					RHSI_C7 = 0;
				}
			}
		}
		else
		{
			LHSI_C3 = HDG_FLAG_LEFT;
			LHSI_C4 = HDG_FLAG_LEFT;
			LHSI_C5 = BRG_FLAG_LEFT;
			LHSI_C6 = BRG_FLAG_LEFT;
			LHSI_C7 = BRG_FLAG_LEFT;
			LHSI_C8 = BRG_FLAG_LEFT;
			LHSI_C9 = CDI_FLAG_LEFT;
			LHSI_C10 = GSI_FLAG_LEFT;
			RHSI_C3 = HDG_FLAG_RIGHT;
			RHSI_C4 = HDG_FLAG_RIGHT;
			RHSI_C5 = BRG_FLAG_RIGHT;
			RHSI_C6 = BRG_FLAG_RIGHT;
			RHSI_C7 = BRG_FLAG_RIGHT;
			RHSI_C8 = BRG_FLAG_RIGHT;
			RHSI_C9 = CDI_FLAG_RIGHT;
			RHSI_C10 = GSI_FLAG_RIGHT;
		}
		unsigned short HLWORD1 = (LHSI_C2 << 15) | (LHSI_C3 << 14) | (LHSI_C4 << 13) | (LHSI_C5 << 12) | (LHSI_C6 << 11) | (LHSI_C7 << 10) | (LHSI_C8 << 9) | (LHSI_C9 << 8) | (LHSI_C10 << 7);
		unsigned short HRWORD1 = (RHSI_C2 << 15) | (RHSI_C3 << 14) | (RHSI_C4 << 13) | (RHSI_C5 << 12) | (RHSI_C6 << 11) | (RHSI_C7 << 10) | (RHSI_C8 << 9) | (RHSI_C9 << 8) | (RHSI_C10 << 7);

		// HSI Test Word (HLWORD2)
		unsigned short HLWORD2 = 0b0111111111000000;
		unsigned short HRWORD2 = 0b0111111111000000;

		// Selected Course (HLWORD3) 320 ms
		if ((MM == 304) || (MM == 305) || (MM == 602) || (MM == 603))
		{
			HLWORD3 = 16 * static_cast<unsigned short>(MOD( AZIMUTH_RW - ANGLE_CORR_TNTOMAG_RW - HEADING_LEFT, static_cast<float>(2 * PI) ) * (1024 / PI));
			HRWORD3 = 16 * static_cast<unsigned short>(MOD( AZIMUTH_RW - ANGLE_CORR_TNTOMAG_RW - HEADING_RIGHT, static_cast<float>(2 * PI) ) * (1024 / PI));
		}
		else if ((MM == 101) || (MM == 102) || ((MM == 103) && (TAL_ABORT_DECLARED == 0)))
		{
			HLWORD3 = 16 * static_cast<unsigned short>(MOD( -ROLL_SW * (YAW_IY - HEADING_ATO), static_cast<float>(2 * PI) ) * (1024 / PI));
			HRWORD3 = HLWORD3;
		}
		else if ((MM == 103) && (TAL_ABORT_DECLARED == 1))
		{
			HLWORD3 = 16 * static_cast<unsigned short>(MOD( ROLL_SW * (HEADING_TAL + HEADING_V_I - YAW_IY), static_cast<float>(2 * PI) ) * (1024 / PI));
			HRWORD3 = HLWORD3;
		}
		else //if (MM == 601)
		{
			HLWORD3 = 0;
			HRWORD3 = 0;
		}

		// Heading (HLWORD4) 320 ms
		if ((MM == 304) || (MM == 305) || (MM == 602) || (MM == 603))
		{
			HLWORD4 = 16 * static_cast<unsigned short>(HEADING_LEFT * (1024 / PI));
			HRWORD4 = 16 * static_cast<unsigned short>(HEADING_RIGHT * (1024 / PI));
		}
		else if ((MM == 101) || (MM == 102) || (MM == 103))
		{
			HLWORD4 = 16 * static_cast<unsigned short>(MOD( YAW_IY, static_cast<float>(2 * PI) ) * (1024 / PI));
			HRWORD4 = HLWORD4;
		}
		else //if (MM == 601)
		{
			HLWORD4 = 16 * static_cast<unsigned short>(MOD( PSI_HSIMV, static_cast<float>(2 * PI) ) * (1024 / PI));
			HRWORD4 = HLWORD4;
		}

		// Primary Bearing (HLWORD5) 320 ms
		if ((MM == 304) || (MM == 305) || (MM == 602) || (MM == 603))
		{
			HLWORD5 = 16 * static_cast<unsigned short>(MOD( PRIBEAR_LEFT - HEADING_LEFT, static_cast<float>(2 * PI) ) * 1024 / (2 * PI));
			HRWORD5 = 16 * static_cast<unsigned short>(MOD( PRIBEAR_RIGHT - HEADING_RIGHT, static_cast<float>(2 * PI) ) * 1024 / (2 * PI));
		}
		else if ((MM == 101) || (MM == 102) || ((MM == 103) && (TAL_ABORT_DECLARED == 0)))
		{
			HLWORD5 = 16384;
			HRWORD5 = 16384;
		}
		else //if ((MM == 601) || ((MM == 103) && (TAL_ABORT_DECLARED == 1)))
		{
			HLWORD5 = 16 * static_cast<unsigned short>(MOD( (ROLL_SW * (HEADING_RW - YAW_IY)), static_cast<float>(2 * PI) ) * (1024 / PI) );
			HRWORD5 = HLWORD5;
		}

		// Secondary Bearing (HLWORD6) 320 ms
		if ((MM == 304) || (MM == 305) || (MM == 602) || (MM == 603))
		{
			HLWORD6 = 16 * static_cast<unsigned short>(MOD( SECBEAR_LEFT - HEADING_LEFT, static_cast<float>(2 * PI) ) * (1024 / PI));
			HRWORD6 = 16 * static_cast<unsigned short>(MOD( SECBEAR_RIGHT - HEADING_RIGHT, static_cast<float>(2 * PI) ) * (1024 / PI));
		}
		else if ((MM == 101) || (MM == 102) || (MM == 103))
		{
			HLWORD6 = 16 * static_cast<unsigned short>(MOD( ROLL_SW * (HEADING_V_I - YAW_IY), static_cast<float>(2 * PI) ) * (1024 / PI));
			HRWORD6 = HLWORD6;
		}
		else //if (MM == 601)
		{
			HLWORD6 = 16384;
			HRWORD6 = 16384;
		}

		// Primary/Secondary Distance (HLWORD7/HLWORD8) 960 ms
		if ((MM == 304) || (MM == 305) || (MM == 602) || (MM == 603))
		{
			HLWORD7 = BCD( min(3999, static_cast<unsigned short>(PRIRANGE_LEFT)) ) << 1;
			HLWORD8 = BCD( min(3999, static_cast<unsigned short>(SECRANGE_LEFT)) ) << 1;

			HRWORD7 = BCD( min(3999, static_cast<unsigned short>(PRIRANGE_RIGHT)) ) << 1;
			HRWORD8 = BCD( min(3999, static_cast<unsigned short>(SECRANGE_RIGHT)) ) << 1;

			if ((MM == 304) || (MM == 602) || (V_GROUNDSPEED > 6000))
			{
				HLWORD7 &= 0b1111111111100000;
				HLWORD8 &= 0b1111111111100000;

				HRWORD7 &= 0b1111111111100000;
				HRWORD8 &= 0b1111111111100000;
			}
		}
		else if (((MM == 103) && (TAL_ABORT_DECLARED == 1)) || (MM == 601))
		{
			HLWORD7 = BCD( max(3999, static_cast<unsigned short>(PW_RANGE)) ) << 1;
			HLWORD8 = 0;

			HRWORD7 = HLWORD7;
			HRWORD8 = 0;
		}
		else
		{
			HLWORD7 = 0;
			HLWORD8 = 0;

			HRWORD7 = 0;
			HRWORD8 = 0;
		}

		// Course Deviation (HLWORD9) 320 ms
		if ((MM == 304) || (MM == 305) || (MM == 602) || (MM == 603))
		{
			HLWORD9 = 64 * static_cast<unsigned short>(range( -512, CDI_LEFT * 24576 / PI, 511 ));
			HRWORD9 = 64 * static_cast<unsigned short>(range( -512, CDI_RIGHT * 24576 / PI, 511 ));
		}
		else if ((MM == 101) || (MM == 102) || (MM == 103))
		{
			HLWORD9 = 64 * static_cast<unsigned short>(range( -512, ROLL_SW * XTRK_CDI * 512 / 1.5 / CDI_SCALE, 511 ));
			HRWORD9 = HLWORD9;
		}
		else //if (MM == 601)
		{
			HLWORD9 = 0;
			HRWORD9 = 0;
		}

		// Glide Slope Deviation (HLWORD10) 320 ms
		if ((MM == 304) || (MM == 305) || (MM == 602) || (MM == 603))
		{
			HLWORD10 = 64 * static_cast<unsigned short>(range( -512, GSI_LEFT * (256 / 750.0), 511 ));
			HRWORD10 = 64 * static_cast<unsigned short>(range( -512, GSI_RIGHT * (256 / 750.0), 511 ));
		}
		else
		{
			HLWORD10 = 0;
			HRWORD10 = 0;
		}

		// MEDS Data Transfer
		double MET = CLOCKTIME - T_GMTLO;
		MEDS_BETAHVR_VALID = 0;
		if ((((MM == 102) || (MM == 103)) && ((MET < MET_HEAT) && (ALT < ALT_HEAT))) || (MM == 601))
		{
			MEDS_H_VR = 16 * static_cast<unsigned short>(MOD( ROLL_SW * (HEADING_V_REL - YAW_IY), static_cast<float>(2 * PI) ) * (1024 / PI));
			MEDS_BETAHVR_VALID = 1;
		}
		else
		{
			MEDS_H_VR = 0;
		}


		// output
		// Contl Word Wrd 1
		WriteCOMPOOL_AIS( SCP_DDU1_HSI, 1, HLWORD1, 10 );
		WriteCOMPOOL_AIS( SCP_DDU2_HSI, 1, HRWORD1, 10 );
		// HSI Word Wrd 2
		WriteCOMPOOL_AIS( SCP_DDU1_HSI, 2, HLWORD2, 10 );
		WriteCOMPOOL_AIS( SCP_DDU2_HSI, 2, HRWORD2, 10 );
		// Selctd Course Wrd 3
		WriteCOMPOOL_AIS( SCP_DDU1_HSI, 3, HLWORD3, 10 );
		WriteCOMPOOL_AIS( SCP_DDU2_HSI, 3, HRWORD3, 10 );
		// Hdng Wrd 4
		WriteCOMPOOL_AIS( SCP_DDU1_HSI, 4, HLWORD4, 10 );
		WriteCOMPOOL_AIS( SCP_DDU2_HSI, 4, HRWORD4, 10 );
		// Prim. Brng. Wrd 5
		WriteCOMPOOL_AIS( SCP_DDU1_HSI, 5, HLWORD5, 10 );
		WriteCOMPOOL_AIS( SCP_DDU2_HSI, 5, HRWORD5, 10 );
		// Sec. Brng. Wrd 6
		WriteCOMPOOL_AIS( SCP_DDU1_HSI, 6, HLWORD6, 10 );
		WriteCOMPOOL_AIS( SCP_DDU2_HSI, 6, HRWORD6, 10 );
		// Prim. Dist. Wrd 7
		WriteCOMPOOL_AIS( SCP_DDU1_HSI, 7, HLWORD7, 10 );
		WriteCOMPOOL_AIS( SCP_DDU2_HSI, 7, HRWORD7, 10 );
		// Sec. Dist. Wrd 8
		WriteCOMPOOL_AIS( SCP_DDU1_HSI, 8, HLWORD8, 10 );
		WriteCOMPOOL_AIS( SCP_DDU2_HSI, 8, HRWORD8, 10 );
		// Course Dev. Wrd 9
		WriteCOMPOOL_AIS( SCP_DDU1_HSI, 9, HLWORD9, 10 );
		WriteCOMPOOL_AIS( SCP_DDU2_HSI, 9, HRWORD9, 10 );
		// Glide Slope Deviation Word 10
		WriteCOMPOOL_AIS( SCP_DDU1_HSI, 10, HLWORD10, 10 );
		WriteCOMPOOL_AIS( SCP_DDU2_HSI, 10, HRWORD10, 10 );

		// MEDS
		WriteCOMPOOL_IS( SCP_MEDS_BETAHVR_VALID, MEDS_BETAHVR_VALID );
		WriteCOMPOOL_IS( SCP_MEDS_H_VR, MEDS_H_VR );
		return;
	}

	bool HSI_PROC::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 101:
			case 102:
			case 103:
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

	bool HSI_PROC::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void HSI_PROC::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}
}

#include "ASC_ADI_PROC.h"
#include <MathSSV.h>


namespace dps
{
	ASC_ADI_PROC::ASC_ADI_PROC( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "ASC_ADI_PROC" )
	{
		return;
	}

	ASC_ADI_PROC::~ASC_ADI_PROC( void )
	{
		return;
	}

	void ASC_ADI_PROC::OnPostStep( double simt, double simdt, double mjd )
	{
		// TODO FOH

		// inputs
		unsigned short MM = ReadCOMPOOL_IS( SCP_MM );
		unsigned short S_UNCONV = 0;// TODO
		float ROLLSINE1 = ReadCOMPOOL_VS( SCP_ROLLSINE, 1, 3 );
		float ROLLSINE2 = ReadCOMPOOL_VS( SCP_ROLLSINE, 2, 3 );
		float ROLLCOS1 = ReadCOMPOOL_VS( SCP_ROLLCOS, 1, 3 );
		float ROLLCOS2 = ReadCOMPOOL_VS( SCP_ROLLCOS, 2, 3 );
		float PTCHSINE1 = ReadCOMPOOL_VS( SCP_PTCHSINE, 1, 3 );
		float PTCHSINE2 = ReadCOMPOOL_VS( SCP_PTCHSINE, 2, 3 );
		float PTCHCOS1 = ReadCOMPOOL_VS( SCP_PTCHCOS, 1, 3 );
		float PTCHCOS2 = ReadCOMPOOL_VS( SCP_PTCHCOS, 2, 3 );
		float YAWSINE1 = ReadCOMPOOL_VS( SCP_YAWSINE, 1, 3 );
		float YAWSINE2 = ReadCOMPOOL_VS( SCP_YAWSINE, 2, 3 );
		float YAWCOS1 = ReadCOMPOOL_VS( SCP_YAWCOS, 1, 3 );
		float YAWCOS2 = ReadCOMPOOL_VS( SCP_YAWCOS, 2, 3 );
		float P_ORB = 0.0;// TODO
		float Q_ORB = 0.0;// TODO
		float R_ORB = 0.0;// TODO
		unsigned short LADIRSW = ReadCOMPOOL_IS( SCP_LADIRSW );
		unsigned short RADIRSW = ReadCOMPOOL_IS( SCP_RADIRSW );
		unsigned short LADIESW = ReadCOMPOOL_IS( SCP_LADIESW );
		unsigned short RADIESW = ReadCOMPOOL_IS( SCP_RADIESW );
		// HACK convert xADIRSW from [1,2,3] (output from GNC SW RM) to [-1,0,+1] (usage here)
		{
			if (LADIRSW == 1) LADIRSW = -1;
			else if (LADIRSW == 3) LADIRSW = 1;
			else /*if (LADIRSW == 2)*/ LADIRSW = 0;

			if (RADIRSW == 1) RADIRSW = -1;
			else if (RADIRSW == 3) RADIRSW = 1;
			else /*if (RADIRSW == 2)*/ RADIRSW = 0;

			if (LADIESW == 1) LADIESW = -1;
			else if (LADIESW == 3) LADIESW = 1;
			else /*if (LADIESW == 2)*/ LADIESW = 0;

			if (RADIESW == 1) RADIESW = -1;
			else if (RADIESW == 3) RADIESW = 1;
			else /*if (RADIESW == 2)*/ RADIESW = 0;
		}
		float EBDB_1 = 0.0;// TODO
		float EBDB_2 = 0.0;// TODO
		float EBDB_3 = 0.0;// TODO
		float BODY_ERR_ANG[3];
		BODY_ERR_ANG[0] = ReadCOMPOOL_VS( SCP_BODY_ERR_ANG, 1, 3 );
		BODY_ERR_ANG[1] = ReadCOMPOOL_VS( SCP_BODY_ERR_ANG, 2, 3 );
		BODY_ERR_ANG[2] = ReadCOMPOOL_VS( SCP_BODY_ERR_ANG, 3, 3 );
		unsigned short MECO_CMD = 0;// TODO

		// outputs
		unsigned short LADIRS;
		unsigned short RADIRS;
		unsigned short LADIRC;
		unsigned short RADIRC;
		unsigned short LADIPS;
		unsigned short RADIPS;
		unsigned short LADIPC;
		unsigned short RADIPC;
		unsigned short LADIYS;
		unsigned short RADIYS;
		unsigned short LADIYC;
		unsigned short RADIYC;
		unsigned short LADIRR;
		unsigned short RADIRR;
		unsigned short LADIPR;
		unsigned short RADIPR;
		unsigned short LADIYR;
		unsigned short RADIYR;
		unsigned short MEDS_LADIRR_SCALE;
		unsigned short MEDS_RADIRR_SCALE;
		unsigned short MEDS_LADIPR_SCALE;
		unsigned short MEDS_RADIPR_SCALE;
		unsigned short MEDS_LADIYR_SCALE;
		unsigned short MEDS_RADIYR_SCALE;
		unsigned short MEDS_LADIPE_SCALE;
		unsigned short MEDS_RADIPE_SCALE;
		unsigned short LADIRE;
		unsigned short RADIRE;
		unsigned short LADIPE;
		unsigned short RADIPE;
		unsigned short LADIYE;
		unsigned short RADIYE;


		// Left ADI Control Word (LADIWORD1) 160 ms
		unsigned short LADI_C2 = 1;
		unsigned short LADI_C3 = 1;
		unsigned short LADI_C4 = 1;
		unsigned short LADI_C5 = 1;
		unsigned short LADI_C6 = 1;
		unsigned short LADI_C7 = 1;
		unsigned short LADI_C8 = 1;
		unsigned short LADI_C9 = 1;
		unsigned short LADI_C10 = 1;
		unsigned short LADI_C11 = 1;
		unsigned short LADI_C12 = 1;
		unsigned short LADI_C13 = 1;
		unsigned short LADI_C14 = 1;
		if (S_UNCONV == 1)
		{
			LADI_C12 = 0;
			LADI_C13 = 0;
			LADI_C14 = 0;
		}
		unsigned short LADIWORD1 = (LADI_C2 << 15) | (LADI_C3 << 14) | (LADI_C4 << 13) | (LADI_C5 << 12) | (LADI_C6 << 11) | (LADI_C7 << 10) |
			(LADI_C8 << 9) | (LADI_C9 << 8) | (LADI_C10 << 7) | (LADI_C11 << 6) | (LADI_C12 << 5) | (LADI_C13 << 4) | (LADI_C14 << 3);

		// Right ADI Control Word (RADIWORD1) 160 ms
		unsigned short RADI_C2 = 1;
		unsigned short RADI_C3 = 1;
		unsigned short RADI_C4 = 1;
		unsigned short RADI_C5 = 1;
		unsigned short RADI_C6 = 1;
		unsigned short RADI_C7 = 1;
		unsigned short RADI_C8 = 1;
		unsigned short RADI_C9 = 1;
		unsigned short RADI_C10 = 1;
		unsigned short RADI_C11 = 1;
		unsigned short RADI_C12 = 1;
		unsigned short RADI_C13 = 1;
		unsigned short RADI_C14 = 1;
		if (S_UNCONV == 1)
		{
			RADI_C12 = 0;
			RADI_C13 = 0;
			RADI_C14 = 0;
		}
		unsigned short RADIWORD1 = (RADI_C2 << 15) | (RADI_C3 << 14) | (RADI_C4 << 13) | (RADI_C5 << 12) | (RADI_C6 << 11) | (RADI_C7 << 10) |
			(RADI_C8 << 9) | (RADI_C9 << 8) | (RADI_C10 << 7) | (RADI_C11 << 6) | (RADI_C12 << 5) | (RADI_C13 << 4) | (RADI_C14 << 3);

		// Left ADI Test Word (LADIWORD2)
		unsigned short LADIWORD2 = 0b0111111111111000;

		// Right ADI Test Word (RADIWORD2)
		unsigned short RADIWORD2 = 0b0111111111111000;

		// Left ADI Roll Sine(LADIRS) 80 ms
		LADIRS = 8 * static_cast<unsigned short>(4095 * (range( -1.0, ROLLSINE1, 1.0 )));

		// Right ADI Roll Sine(RADIRS) 80 ms
		RADIRS = 8 * static_cast<unsigned short>(4095 * (range( -1.0, ROLLSINE2, 1.0 )));

		// Left ADI Roll Cosine(LADIRC) 80 ms
		LADIRC = 8 * static_cast<unsigned short>(4095 * (range( -1.0, ROLLCOS1, 1.0 )));

		// Right ADI Roll Cosine(RADIRC) 80 ms
		RADIRC = 8 * static_cast<unsigned short>(4095 * (range( -1.0, ROLLCOS2, 1.0 )));

		// Left ADI Pitch Sine(LADIPS) 80 ms
		LADIPS = 8 * static_cast<unsigned short>(4095 * (range( -1.0, PTCHSINE1, 1.0 )));

		// Right ADI Pitch Sine(RADIPS) 80 ms
		RADIPS = 8 * static_cast<unsigned short>(4095 * (range( -1.0, PTCHSINE2, 1.0 )));

		// Left ADI Pitch Cosine(LADIPC) 80 ms
		LADIPC = 8 * static_cast<unsigned short>(4095 * (range( -1.0, PTCHCOS1, 1.0 )));

		// Right ADI Pitch Cosine(RADIPC) 80 ms
		RADIPC = 8 * static_cast<unsigned short>(4095 * (range( -1.0, PTCHCOS2, 1.0 )));

		// Left ADI Yaw Sine(LADIYS) 80 ms
		LADIYS = 8 * static_cast<unsigned short>(4095 * (range( -1.0, YAWSINE1, 1.0 )));

		// Right ADI Yaw Sine(RADIYS) 80 ms
		RADIYS = 8 * static_cast<unsigned short>(4095 * (range( -1.0, YAWSINE2, 1.0 )));

		// Left ADI Yaw Cosine(LADIYC) 80 ms
		LADIYC = 8 * static_cast<unsigned short>(4095 * (range( -1.0, YAWCOS1, 1.0 )));

		// Right ADI Yaw Cosine(RADIYC) 80 ms
		RADIYC = 8 * static_cast<unsigned short>(4095 * (range( -1.0, YAWCOS2, 1.0 )));

		// Attitude Rate Data
		// Left ADI Roll Rate (LADIRR) 160 ms
		if (LADIRSW == 1)
		{
			LADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 10.0) * P_ORB, 4095 ));
			MEDS_LADIRR_SCALE = static_cast<unsigned short>(10);
		}
		else if (LADIRSW == 0)
		{
			LADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 5.0) * P_ORB, 4095 ));
			MEDS_LADIRR_SCALE = static_cast<unsigned short>(5);
		}
		else //if (LADIRSW == -1)
		{
			LADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 1.0) * P_ORB, 4095 ));
			MEDS_LADIRR_SCALE = static_cast<unsigned short>(1);
		}

		// Right ADI Roll Rate (RADIRR) 160 ms
		if (RADIRSW == 1)
		{
			RADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 10.0) * P_ORB, 4095 ));
			MEDS_RADIRR_SCALE = static_cast<unsigned short>(10);
		}
		else if (RADIRSW == 0)
		{
			RADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 5.0) * P_ORB, 4095 ));
			MEDS_RADIRR_SCALE = static_cast<unsigned short>(5);
		}
		else //if (RADIRSW == -1)
		{
			RADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 1.0) * P_ORB, 4095 ));
			MEDS_RADIRR_SCALE = static_cast<unsigned short>(1);
		}

		// Left ADI Pitch Rate (LADIPR) 160 ms
		if (LADIRSW == 1)
		{
			LADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 10.0) * Q_ORB, 4095 ));
			MEDS_LADIPR_SCALE = static_cast<unsigned short>(10);
		}
		else if (LADIRSW == 0)
		{
			LADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 5.0) * Q_ORB, 4095 ));
			MEDS_LADIPR_SCALE = static_cast<unsigned short>(5);
		}
		else //if (LADIRSW == -1)
		{
			LADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 1.0) * Q_ORB, 4095 ));
			MEDS_LADIPR_SCALE = static_cast<unsigned short>(1);
		}

		// Right ADI Pitch Rate (RADIPR) 160 ms
		if (RADIRSW == 1)
		{
			RADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 10.0) * Q_ORB, 4095 ));
			MEDS_RADIPR_SCALE = static_cast<unsigned short>(10);
		}
		else if (RADIRSW == 0)
		{
			RADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 5.0) * Q_ORB, 4095 ));
			MEDS_RADIPR_SCALE = static_cast<unsigned short>(5);
		}
		else //if (RADIRSW == -1)
		{
			RADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 1.0) * Q_ORB, 4095 ));
			MEDS_RADIPR_SCALE = static_cast<unsigned short>(1);
		}

		// Left ADI Yaw Rate (LADIYR) 160 ms
		if (LADIRSW == 1)
		{
			LADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 10.0) * R_ORB, 4095 ));
			MEDS_LADIYR_SCALE = static_cast<unsigned short>(10);
		}
		else if (LADIRSW == 0)
		{
			LADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 5.0) * R_ORB, 4095 ));
			MEDS_LADIYR_SCALE = static_cast<unsigned short>(5);
		}
		else //if (LADIRSW == -1)
		{
			LADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 1.0) * R_ORB, 4095 ));
			MEDS_LADIYR_SCALE = static_cast<unsigned short>(1);
		}

		// Right ADI Yaw Rate (RADIYR) 160 ms
		if (RADIRSW == 1)
		{
			RADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 10.0) * R_ORB, 4095 ));
			MEDS_RADIYR_SCALE = static_cast<unsigned short>(10);
		}
		else if (RADIRSW == 0)
		{
			RADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 5.0) * R_ORB, 4095 ));
			MEDS_RADIYR_SCALE = static_cast<unsigned short>(5);
		}
		else //if (RADIRSW == -1)
		{
			RADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 1.0) * R_ORB, 4095 ));
			MEDS_RADIYR_SCALE = static_cast<unsigned short>(1);
		}

		// Attitude Error Data
		float ROLL_ERR;
		float PITCH_ERR;
		float YAW_ERR;
		if ((MM == 601) || (MECO_CMD == 0))
		{
			ROLL_ERR = EBDB_1;
			PITCH_ERR = EBDB_2;
			YAW_ERR = EBDB_3;
		}
		else
		{
			ROLL_ERR = BODY_ERR_ANG[0];
			PITCH_ERR = BODY_ERR_ANG[1];
			YAW_ERR = BODY_ERR_ANG[2];
		}
		double RECC_L;
		double RECC_R;
		if (LADIESW == 1)
		{
			RECC_L = 4095 / 10.0;
		}
		else if (LADIESW == 0)
		{
			RECC_L = 4095 / 5.0;
		}
		else //if (LADIESW == –1)
		{
			RECC_L = 4095;
		}
		if (RADIESW == 1)
		{
			RECC_R = 4095 / 10.0;
		}
		else if (RADIESW == 0)
		{
			RECC_R = 4095 / 5.0;
		}
		else //if (RADIESW == –1)
		{
			RECC_R = 4095;
		}

		// Left/Right ADI Roll Error (LADIRE/RADIRE) 160 ms
		LADIRE = 8 * static_cast<unsigned short>(range( -4096, RECC_L * ROLL_ERR, 4095 ));
		RADIRE = 8 * static_cast<unsigned short>(range( -4096, RECC_R * ROLL_ERR, 4095 ));

		// Left/Right ADI Pitch Error (LADIPE/RADIPE) 160 ms
		LADIPE = 8 * static_cast<unsigned short>(range( -4096, RECC_L * PITCH_ERR, 4095 ));
		RADIPE = 8 * static_cast<unsigned short>(range( -4096, RECC_R * PITCH_ERR, 4095 ));
		MEDS_LADIPE_SCALE = static_cast<unsigned short>((4095 / RECC_L) * 4);// LSB 0.25º
		MEDS_RADIPE_SCALE = static_cast<unsigned short>((4095 / RECC_R) * 4);// LSB 0.25º

		// Left/Right ADI Yaw Error (LADIYE/RADIYE) 160 ms
		LADIYE = 8 * static_cast<unsigned short>(range( -4096, RECC_L * YAW_ERR, 4095 ));
		RADIYE = 8 * static_cast<unsigned short>(range( -4096, RECC_R * YAW_ERR, 4095 ));


		// output
		// Word 1 ADI Contl Word
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 1, LADIWORD1, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 1, RADIWORD1, 14 );
		// Word 2 Test Word
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 2, LADIWORD2, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 2, RADIWORD2, 14 );
		// Word 3 Roll Sine
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 3, LADIRS, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 3, RADIRS, 14 );
		// Word 4 Roll Cosine
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 4, LADIRC, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 4, RADIRC, 14 );
		// Word 5 Pitch Sine
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 5, LADIPS, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 5, RADIPS, 14 );
		// Word 6 Pitch Cosine
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 6, LADIPC, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 6, RADIPC, 14 );
		// Word 7 Yaw Sine
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 7, LADIYS, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 7, RADIYS, 14 );
		// Word 8 Yaw Cosine
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 8, LADIYC, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 8, RADIYC, 14 );
		// Word 9 Roll Rate
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 9, LADIRR, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 9, RADIRR, 14 );
		// Word 10 Pitch Rate
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 10, LADIPR, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 10, RADIPR, 14 );
		// Word 11 Yaw Rate
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 11, LADIYR, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 11, RADIYR, 14 );
		// Word 12 Roll Error
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 12, LADIRE, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 12, RADIRE, 14 );
		// Word 13 Pitch Error
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 13, LADIPE, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 13, RADIPE, 14 );
		// Word 14 Yaw Error
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 14, LADIYE, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 14, RADIYE, 14 );

		// MEDS
		WriteCOMPOOL_IS( SCP_MEDS_LADIRR_SCALE, MEDS_LADIRR_SCALE );
		WriteCOMPOOL_IS( SCP_MEDS_RADIRR_SCALE, MEDS_RADIRR_SCALE );
		WriteCOMPOOL_IS( SCP_MEDS_LADIPR_SCALE, MEDS_LADIPR_SCALE );
		WriteCOMPOOL_IS( SCP_MEDS_RADIPR_SCALE, MEDS_RADIPR_SCALE );
		WriteCOMPOOL_IS( SCP_MEDS_LADIYR_SCALE, MEDS_LADIYR_SCALE );
		WriteCOMPOOL_IS( SCP_MEDS_RADIYR_SCALE, MEDS_RADIYR_SCALE );
		WriteCOMPOOL_IS( SCP_MEDS_LADIPE_SCALE, MEDS_LADIPE_SCALE );
		WriteCOMPOOL_IS( SCP_MEDS_RADIPE_SCALE, MEDS_RADIPE_SCALE );
		return;
	}

	bool ASC_ADI_PROC::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 101:
			case 102:
			case 103:
			case 104:
			case 105:
			case 106:
			case 601:
				return true;
			default:
				return false;
		}
	}

	bool ASC_ADI_PROC::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void ASC_ADI_PROC::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}
}

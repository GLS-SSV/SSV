#include "ORB_ADI_PROC.h"
#include <MathSSV.h>


namespace dps
{
	ORB_ADI_PROC::ORB_ADI_PROC( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "ORB_ADI_PROC" )
	{
		return;
	}

	ORB_ADI_PROC::~ORB_ADI_PROC( void )
	{
		return;
	}

	void ORB_ADI_PROC::OnPreStep( double simt, double simdt, double mjd )
	{
		// TODO FOH

		// inputs
		unsigned short MM = ReadCOMPOOL_IS( SCP_MM );
		unsigned short ADI_ATT = 1;// TODO
		unsigned short FWD_ADI_INT = 0;// TODO
		unsigned short AFT_ADI_INT = 0;// TODO
		float ROLLSINE1 = ReadCOMPOOL_VS( SCP_ROLLSINE, 1, 3 );
		float ROLLSINE2 = ReadCOMPOOL_VS( SCP_ROLLSINE, 2, 3 );
		float ROLLSINE3 = ReadCOMPOOL_VS( SCP_ROLLSINE, 3, 3 );
		float ROLLCOS1 = ReadCOMPOOL_VS( SCP_ROLLCOS, 1, 3 );
		float ROLLCOS2 = ReadCOMPOOL_VS( SCP_ROLLCOS, 2, 3 );
		float ROLLCOS3 = ReadCOMPOOL_VS( SCP_ROLLCOS, 3, 3 );
		float PTCHSINE1 = ReadCOMPOOL_VS( SCP_PTCHSINE, 1, 3 );
		float PTCHSINE2 = ReadCOMPOOL_VS( SCP_PTCHSINE, 2, 3 );
		float PTCHSINE3 = ReadCOMPOOL_VS( SCP_PTCHSINE, 3, 3 );
		float PTCHCOS1 = ReadCOMPOOL_VS( SCP_PTCHCOS, 1, 3 );
		float PTCHCOS2 = ReadCOMPOOL_VS( SCP_PTCHCOS, 2, 3 );
		float PTCHCOS3 = ReadCOMPOOL_VS( SCP_PTCHCOS, 3, 3 );
		float YAWSINE1 = ReadCOMPOOL_VS( SCP_YAWSINE, 1, 3 );
		float YAWSINE2 = ReadCOMPOOL_VS( SCP_YAWSINE, 2, 3 );
		float YAWSINE3 = ReadCOMPOOL_VS( SCP_YAWSINE, 3, 3 );
		float YAWCOS1 = ReadCOMPOOL_VS( SCP_YAWCOS, 1, 3 );
		float YAWCOS2 = ReadCOMPOOL_VS( SCP_YAWCOS, 2, 3 );
		float YAWCOS3 = ReadCOMPOOL_VS( SCP_YAWCOS, 3, 3 );
		float RATE_EST_1 = -ReadCOMPOOL_VS( SCP_RATE_EST, 1, 3 );// HACK switch sign to keep fly-to-null
		float RATE_EST_2 = -ReadCOMPOOL_VS( SCP_RATE_EST, 2, 3 );
		float RATE_EST_3 = -ReadCOMPOOL_VS( SCP_RATE_EST, 3, 3 );
		unsigned short LADIRSW = ReadCOMPOOL_IS( SCP_LADIRSW );
		unsigned short RADIRSW = ReadCOMPOOL_IS( SCP_RADIRSW );
		unsigned short AADIRSW = ReadCOMPOOL_IS( SCP_AADIRSW );
		unsigned short LADIESW = ReadCOMPOOL_IS( SCP_LADIESW );
		unsigned short RADIESW = ReadCOMPOOL_IS( SCP_RADIESW );
		unsigned short AADIESW = ReadCOMPOOL_IS( SCP_AADIESW );
		// HACK convert xADIRSW from [1,2,3] (output from GNC SW RM) to [-1,0,+1] (usage here)
		{
			if (LADIRSW == 1) LADIRSW = -1;
			else if (LADIRSW == 3) LADIRSW = 1;
			else /*if (LADIRSW == 2)*/ LADIRSW = 0;

			if (RADIRSW == 1) RADIRSW = -1;
			else if (RADIRSW == 3) RADIRSW = 1;
			else /*if (RADIRSW == 2)*/ RADIRSW = 0;
			
			if (AADIRSW == 1) AADIRSW = -1;
			else if (AADIRSW == 3) AADIRSW = 1;
			else /*if (AADIRSW == 2)*/ AADIRSW = 0;

			if (LADIESW == 1) LADIESW = -1;
			else if (LADIESW == 3) LADIESW = 1;
			else /*if (LADIESW == 2)*/ LADIESW = 0;

			if (RADIESW == 1) RADIESW = -1;
			else if (RADIESW == 3) RADIESW = 1;
			else /*if (RADIESW == 2)*/ RADIESW = 0;

			if (AADIESW == 1) AADIESW = -1;
			else if (AADIESW == 3) AADIESW = 1;
			else /*if (AADIESW == 2)*/ AADIESW = 0;
		}
		unsigned short ERR_SEL = 0;// TODO
		float BODY_ERR_ANG[3];
		BODY_ERR_ANG[0] = ReadCOMPOOL_VS( SCP_BODY_ERR_ANG, 1, 3 );
		BODY_ERR_ANG[1] = ReadCOMPOOL_VS( SCP_BODY_ERR_ANG, 2, 3 );
		BODY_ERR_ANG[2] = ReadCOMPOOL_VS( SCP_BODY_ERR_ANG, 3, 3 );
		float ATTITUDE_ERROR_1 = 0.0;// TODO
		float ATTITUDE_ERROR_2 = 0.0;// TODO
		float ATTITUDE_ERROR_3 = 0.0;// TODO
		unsigned short SEN_SW = ReadCOMPOOL_IS( SCP_SENSE_SW );

		// outputs
		unsigned short LADIRS;
		unsigned short RADIRS;
		unsigned short AADIRS;
		unsigned short LADIRC;
		unsigned short RADIRC;
		unsigned short AADIRC;
		unsigned short LADIPS;
		unsigned short RADIPS;
		unsigned short AADIPS;
		unsigned short LADIPC;
		unsigned short RADIPC;
		unsigned short AADIPC;
		unsigned short LADIYS;
		unsigned short RADIYS;
		unsigned short AADIYS;
		unsigned short LADIYC;
		unsigned short RADIYC;
		unsigned short AADIYC;
		unsigned short LADIRR;
		unsigned short RADIRR;
		unsigned short AADIRR;
		unsigned short LADIPR;
		unsigned short RADIPR;
		unsigned short AADIPR;
		unsigned short LADIYR;
		unsigned short RADIYR;
		unsigned short AADIYR;
		unsigned short LADIRE;
		unsigned short RADIRE;
		unsigned short AADIRE;
		unsigned short LADIPE;
		unsigned short RADIPE;
		unsigned short AADIPE;
		unsigned short LADIYE;
		unsigned short RADIYE;
		unsigned short AADIYE;


		// TODO OPS 8 interrupt
		if (FWD_ADI_INT == 0)
		{
			//
		}
		if (AFT_ADI_INT == 0)
		{
			//
		}

		// Left ADI Control Word (LADIWORD1) 160 ms
		unsigned short LADI_C2 = 1;
		unsigned short LADI_C3 = ADI_ATT;
		unsigned short LADI_C4 = ADI_ATT;
		unsigned short LADI_C5 = ADI_ATT;
		unsigned short LADI_C6 = ADI_ATT;
		unsigned short LADI_C7 = ADI_ATT;
		unsigned short LADI_C8 = ADI_ATT;
		unsigned short LADI_C9 = ADI_ATT;
		unsigned short LADI_C10 = ADI_ATT;
		unsigned short LADI_C11 = ADI_ATT;
		unsigned short LADI_C12 = ADI_ATT;
		unsigned short LADI_C13 = ADI_ATT;
		unsigned short LADI_C14 = ADI_ATT;
		unsigned short LADIWORD1 = (LADI_C2 << 15) | (LADI_C3 << 14) | (LADI_C4 << 13) | (LADI_C5 << 12) | (LADI_C6 << 11) | (LADI_C7 << 10) |
			(LADI_C8 << 9) | (LADI_C9 << 8) | (LADI_C10 << 7) | (LADI_C11 << 6) | (LADI_C12 << 5) | (LADI_C13 << 4) | (LADI_C14 << 3);

		// Right ADI Control Word (RADIWORD1) 160 ms
		unsigned short RADI_C2 = 1;
		unsigned short RADI_C3 = ADI_ATT;
		unsigned short RADI_C4 = ADI_ATT;
		unsigned short RADI_C5 = ADI_ATT;
		unsigned short RADI_C6 = ADI_ATT;
		unsigned short RADI_C7 = ADI_ATT;
		unsigned short RADI_C8 = ADI_ATT;
		unsigned short RADI_C9 = ADI_ATT;
		unsigned short RADI_C10 = ADI_ATT;
		unsigned short RADI_C11 = ADI_ATT;
		unsigned short RADI_C12 = ADI_ATT;
		unsigned short RADI_C13 = ADI_ATT;
		unsigned short RADI_C14 = ADI_ATT;
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
			LADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 5.0) * RATE_EST_1, 4095 ));
		}
		else if (LADIRSW == 0)
		{
			LADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 1.0) * RATE_EST_1, 4095 ));
		}
		else //if (LADIRSW == -1)
		{
			LADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 0.2) * RATE_EST_1, 4095 ));
		}

		// Right ADI Roll Rate (RADIRR) 160 ms
		if (RADIRSW == 1)
		{
			RADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 5.0) * RATE_EST_1, 4095 ));
		}
		else if (RADIRSW == 0)
		{
			RADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 1.0) * RATE_EST_1, 4095 ));
		}
		else //if (RADIRSW == -1)
		{
			RADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 0.2) * RATE_EST_1, 4095 ));
		}

		// Left ADI Pitch Rate (LADIPR) 160 ms
		if (LADIRSW == 1)
		{
			LADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 5.0) * RATE_EST_2, 4095 ));
		}
		else if (LADIRSW == 0)
		{
			LADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 1.0) * RATE_EST_2, 4095 ));
		}
		else //if (LADIRSW == -1)
		{
			LADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 0.2) * RATE_EST_2, 4095 ));
		}

		// Right ADI Pitch Rate (RADIPR) 160 ms
		if (RADIRSW == 1)
		{
			RADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 5.0) * RATE_EST_2, 4095 ));
		}
		else if (RADIRSW == 0)
		{
			RADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 1.0) * RATE_EST_2, 4095 ));
		}
		else //if (RADIRSW == -1)
		{
			RADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 0.2) * RATE_EST_2, 4095 ));
		}

		// Left ADI Yaw Rate (LADIYR) 160 ms
		if (LADIRSW == 1)
		{
			LADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 5.0) * RATE_EST_3, 4095 ));
		}
		else if (LADIRSW == 0)
		{
			LADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 1.0) * RATE_EST_3, 4095 ));
		}
		else //if (LADIRSW == -1)
		{
			LADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 0.2) * RATE_EST_3, 4095 ));
		}

		// Right ADI Yaw Rate (RADIYR) 160 ms
		if (RADIRSW == 1)
		{
			RADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 5.0) * RATE_EST_3, 4095 ));
		}
		else if (RADIRSW == 0)
		{
			RADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 1.0) * RATE_EST_3, 4095 ));
		}
		else //if (RADIRSW == -1)
		{
			RADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 0.2) * RATE_EST_3, 4095 ));
		}

		// Attitude Error Data
		float ROLL_ERR;
		float PITCH_ERR;
		float YAW_ERR;
		if ((ERR_SEL == 1) || (MM == 202))
		{
			ROLL_ERR = BODY_ERR_ANG[0];
			PITCH_ERR = BODY_ERR_ANG[1];
			YAW_ERR = BODY_ERR_ANG[2];
		}
		else
		{
			ROLL_ERR = ATTITUDE_ERROR_1;
			PITCH_ERR = ATTITUDE_ERROR_2;
			YAW_ERR = ATTITUDE_ERROR_3;
		}
		double RECC_L;
		double RECC_R;
		double RECC_A;
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
		if (AADIESW == 1)
		{
			RECC_A = 4095 / 10.0;
		}
		else if (AADIESW == 0)
		{
			RECC_A = 4095 / 5.0;
		}
		else //if (AADIESW == –1)
		{
			RECC_A = 4095;
		}

		// Left/Right ADI Roll Error (LADIRE/RADIRE) 80 ms
		LADIRE = 8 * static_cast<unsigned short>(range( -4096, RECC_L * ROLL_ERR, 4095 ));
		RADIRE = 8 * static_cast<unsigned short>(range( -4096, RECC_R * ROLL_ERR, 4095 ));

		// Left/Right ADI Pitch Error (LADIPE/RADIPE) 80 ms
		LADIPE = 8 * static_cast<unsigned short>(range( -4096, RECC_L * PITCH_ERR, 4095 ));
		RADIPE = 8 * static_cast<unsigned short>(range( -4096, RECC_R * PITCH_ERR, 4095 ));

		// Left/Right ADI Yaw Error (LADIYE/RADIYE) 80 ms
		LADIYE = 8 * static_cast<unsigned short>(range( -4096, RECC_L * YAW_ERR, 4095 ));
		RADIYE = 8 * static_cast<unsigned short>(range( -4096, RECC_R * YAW_ERR, 4095 ));


		// Aft ADI Control Word (AADIWORD1) 160 ms
		unsigned short AADI_C2 = 1;
		unsigned short AADI_C3 = ADI_ATT;
		unsigned short AADI_C4 = ADI_ATT;
		unsigned short AADI_C5 = ADI_ATT;
		unsigned short AADI_C6 = ADI_ATT;
		unsigned short AADI_C7 = ADI_ATT;
		unsigned short AADI_C8 = ADI_ATT;
		unsigned short AADI_C9 = ADI_ATT;
		unsigned short AADI_C10 = ADI_ATT;
		unsigned short AADI_C11 = ADI_ATT;
		unsigned short AADI_C12 = ADI_ATT;
		unsigned short AADI_C13 = ADI_ATT;
		unsigned short AADI_C14 = ADI_ATT;
		unsigned short AADIWORD1 = (AADI_C2 << 15) | (AADI_C3 << 14) | (AADI_C4 << 13) | (AADI_C5 << 12) | (AADI_C6 << 11) | (AADI_C7 << 10) |
			(AADI_C8 << 9) | (AADI_C9 << 8) | (AADI_C10 << 7) | (AADI_C11 << 6) | (AADI_C12 << 5) | (AADI_C13 << 4) | (AADI_C14 << 3);

		// Aft ADI Test Word (AADIWORD2)
		unsigned short AADIWORD2 = 0b0111111111111000;

		// Aft ADI Roll Sine(AADIRS) 80 ms
		AADIRS = 8 * static_cast<unsigned short>(4095 * (range( -1.0, ROLLSINE3, 1.0 )));

		// Aft ADI Roll Cosine(AADIRC) 80 ms
		AADIRC = 8 * static_cast<unsigned short>(4095 * (range( -1.0, ROLLCOS3, 1.0 )));

		// Aft ADI Pitch Sine(AADIPS) 80 ms
		AADIPS = 8 * static_cast<unsigned short>(4095 * (range( -1.0, PTCHSINE3, 1.0 )));

		// Aft ADI Pitch Cosine(AADIPC) 80 ms
		AADIPC = 8 * static_cast<unsigned short>(4095 * (range( -1.0, PTCHCOS3, 1.0 )));

		// Aft ADI Yaw Sine(AADIYS) 80 ms
		AADIYS = 8 * static_cast<unsigned short>(4095 * (range( -1.0, YAWSINE3, 1.0 )));

		// Aft ADI Yaw Cosine(AADIYC) 80 m
		AADIYC = 8 * static_cast<unsigned short>(4095 * (range( -1.0, YAWCOS3, 1.0 )));

		// Aft Rate and Error Data
		// Aft ADI Roll Rate (AADIRR) 160 ms
		if (SEN_SW == 1)
		{
			// -X
			if (AADIRSW == 1)
			{
				AADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 5.0) * (-RATE_EST_1), 4095 ));
			}
			else if (AADIRSW == 0)
			{
				AADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 1.0) * (-RATE_EST_1), 4095 ));
			}
			else //if (AADIRSW == -1)
			{
				AADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 0.2) * (-RATE_EST_1), 4095 ));
			}
		}
		else
		{
			// -Z
			if (AADIRSW == 1)
			{
				AADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 5.0) * (-RATE_EST_3), 4095 ));
			}
			else if (AADIRSW == 0)
			{
				AADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 1.0) * (-RATE_EST_3), 4095 ));
			}
			else //if (AADIRSW == -1)
			{
				AADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 0.2) * (-RATE_EST_3), 4095 ));
			}
		}

		// Aft ADI Pitch Rate (AADIPR) 160 ms
		if (AADIRSW == 1)
		{
			AADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 5.0) * (-RATE_EST_2), 4095 ));
		}
		else if (AADIRSW == 0)
		{
			AADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 1.0) * (-RATE_EST_2), 4095 ));
		}
		else //if (AADIRSW == -1)
		{
			AADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 0.2) * (-RATE_EST_2), 4095 ));
		}

		// Aft ADI Yaw Rate (AADIYR) 160 ms
		if (SEN_SW == 1)
		{
			// -X
			if (AADIRSW == 1)
			{
				AADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 5.0) * RATE_EST_3, 4095 ));
			}
			else if (AADIRSW == 0)
			{
				AADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 1.0) * RATE_EST_3, 4095 ));
			}
			else //if (AADIRSW == -1)
			{
				AADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 0.2) * RATE_EST_3, 4095 ));
			}
		}
		else
		{
			// -Z
			if (AADIRSW == 1)
			{
				AADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 5.0) * (-RATE_EST_1), 4095 ));
			}
			else if (AADIRSW == 0)
			{
				AADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 1.0) * (-RATE_EST_1), 4095 ));
			}
			else //if (AADIRSW == -1)
			{
				AADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 0.2) * (-RATE_EST_1), 4095 ));
			}
		}

		// Aft ADI Roll Error AADIRE 80 ms
		if (SEN_SW == 1)
		{
			AADIRE = 8 * static_cast<unsigned short>(range( -4096, RECC_A * (-ROLL_ERR), 4095 ));
		}
		else
		{
			AADIRE = 8 * static_cast<unsigned short>(range( -4096, RECC_A * (-YAW_ERR), 4095 ));
		}

		// Aft ADI Pitch Error AADIPE 80 ms
		AADIPE = 8 * static_cast<unsigned short>(range( -4096, RECC_A * (-PITCH_ERR), 4095 ));

		// Aft ADI Yaw Error AADIYE 80 ms
		if (SEN_SW == 1)
		{
			AADIYE = 8 * static_cast<unsigned short>(range( -4096, RECC_A * YAW_ERR, 4095 ));
		}
		else
		{
			AADIYE = 8 * static_cast<unsigned short>(range( -4096, RECC_A * (-ROLL_ERR), 4095 ));
		}


		// output
		// Word 1 ADI Contl Word
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 1, LADIWORD1, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 1, RADIWORD1, 14 );
		WriteCOMPOOL_AIS( SCP_DDU3_ADI, 1, AADIWORD1, 14 );
		// Word 2 Test Word
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 2, LADIWORD2, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 2, RADIWORD2, 14 );
		WriteCOMPOOL_AIS( SCP_DDU3_ADI, 2, AADIWORD2, 14 );
		// Word 3 Roll Sine
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 3, LADIRS, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 3, RADIRS, 14 );
		WriteCOMPOOL_AIS( SCP_DDU3_ADI, 3, AADIRS, 14 );
		// Word 4 Roll Cosine
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 4, LADIRC, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 4, RADIRC, 14 );
		WriteCOMPOOL_AIS( SCP_DDU3_ADI, 4, AADIRC, 14 );
		// Word 5 Pitch Sine
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 5, LADIPS, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 5, RADIPS, 14 );
		WriteCOMPOOL_AIS( SCP_DDU3_ADI, 5, AADIPS, 14 );
		// Word 6 Pitch Cosine
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 6, LADIPC, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 6, RADIPC, 14 );
		WriteCOMPOOL_AIS( SCP_DDU3_ADI, 6, AADIPC, 14 );
		// Word 7 Yaw Sine
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 7, LADIYS, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 7, RADIYS, 14 );
		WriteCOMPOOL_AIS( SCP_DDU3_ADI, 7, AADIYS, 14 );
		// Word 8 Yaw Cosine
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 8, LADIYC, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 8, RADIYC, 14 );
		WriteCOMPOOL_AIS( SCP_DDU3_ADI, 8, AADIYC, 14 );
		// Word 9 Roll Rate
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 9, LADIRR, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 9, RADIRR, 14 );
		WriteCOMPOOL_AIS( SCP_DDU3_ADI, 9, AADIRR, 14 );
		// Word 10 Pitch Rate
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 10, LADIPR, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 10, RADIPR, 14 );
		WriteCOMPOOL_AIS( SCP_DDU3_ADI, 10, AADIPR, 14 );
		// Word 11 Yaw Rate
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 11, LADIYR, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 11, RADIYR, 14 );
		WriteCOMPOOL_AIS( SCP_DDU3_ADI, 11, AADIYR, 14 );
		// Word 12 Roll Error
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 12, LADIRE, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 12, RADIRE, 14 );
		WriteCOMPOOL_AIS( SCP_DDU3_ADI, 12, AADIRE, 14 );
		// Word 13 Pitch Error
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 13, LADIPE, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 13, RADIPE, 14 );
		WriteCOMPOOL_AIS( SCP_DDU3_ADI, 13, AADIPE, 14 );
		// Word 14 Yaw Error
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 14, LADIYE, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 14, RADIYE, 14 );
		WriteCOMPOOL_AIS( SCP_DDU3_ADI, 14, AADIYE, 14 );
		return;
	}

	bool ORB_ADI_PROC::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 201:
			case 202:
			case 801:
				return true;
			default:
				return false;
		}
	}

	bool ORB_ADI_PROC::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void ORB_ADI_PROC::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}
}

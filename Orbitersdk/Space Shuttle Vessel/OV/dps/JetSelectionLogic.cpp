/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/06/07   GLS
2020/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
********************************************/
#include "JetSelectionLogic.h"
#include "..\Atlantis.h"


namespace dps
{
	JetSelectionLogic::JetSelectionLogic( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "JetSelectionLogic" )
	{
		return;
	}

	JetSelectionLogic::~JetSelectionLogic( void )
	{
		return;
	}

	void JetSelectionLogic::Realize( void )
	{
		/*DiscreteBundle* pBundle = BundleManager()->CreateBundle( "THRUSTER_CMD", 16 );
		RCSPitchCommand.Connect( pBundle, 0 );
		RCSYawCommand.Connect( pBundle, 1 );
		RCSRollCommand.Connect( pBundle, 2 );*/
		return;
	}

	void JetSelectionLogic::OnPostStep( double simt, double simdt, double mjd )
	{
		// TODO RCS pod limit

		short UXCMD = ReadCOMPOOL_IS( SCP_UXCMD );
		short UYCMD = ReadCOMPOOL_IS( SCP_UYCMD );
		short UZCMD = ReadCOMPOOL_IS( SCP_UZCMD );

		//RCSRollCommand.SetLine( static_cast<float>(UXCMD / 8.0) );// 8
		//RCSPitchCommand.SetLine( static_cast<float>(UYCMD / 9.5) );// 10 up, 9 dn, avg 9.5
		//RCSYawCommand.SetLine( static_cast<float>(UZCMD / 6.0) );// 6




		/////


		bool NEW_JON[20];
		for (auto &x : NEW_JON) x = false;
		/*
		 0  2 L1L
		 1  3 L3L
		 2  3 L1U
		 3  5 R1R
		 4  6 R1U
		 5 11 L3D
		 6 13 R3R
		 7 14 R3D
		 8 17 L2L
		 9 18 L2U
		10 19 L2D
		11 20 R2R
		12 21 R2U
		13 22 R2D
		14 23 L4L
		15 24 L4U
		16 25 L4D
		17 26 R4R
		18 27 R4U
		19 28 R4D
		*/

		// R
		// 11 12 13 14
		if (UXCMD <= -2)
		{
			NEW_JON[2] = true;// L1U
			NEW_JON[7] = true;// R3D

			if (UXCMD <= -4)
			{
				NEW_JON[9] = true;// L2U
				NEW_JON[13] = true;// R2D

				if (UXCMD == -6)
				{
					NEW_JON[15] = true;// L4U
					NEW_JON[19] = true;// R4D
				}
			}
		}
		else if (UXCMD >= 2)
		{
			NEW_JON[5] = true;// L3D
			NEW_JON[4] = true;// R1U

			if (UXCMD >= 4)
			{
				NEW_JON[10] = true;// L2D
				NEW_JON[12] = true;// R2U

				if (UXCMD == 6)
				{
					NEW_JON[16] = true;// L4D
					NEW_JON[18] = true;// R4U
				}
			}
		}

		// P
		// 11 12 13 14
		if (UYCMD <= -2)
		{
			NEW_JON[5] = true;// L3D
			NEW_JON[7] = true;// R3D

			if (UYCMD <= -4)
			{
				NEW_JON[10] = true;// L2D
				NEW_JON[13] = true;// R2D

				if (UYCMD == -6)
				{
					NEW_JON[16] = true;// L4D
					NEW_JON[19] = true;// R4D
				}
			}
		}
		else if (UYCMD >= 2)
		{
			NEW_JON[2] = true;// L1U
			NEW_JON[4] = true;// R1U

			if (UYCMD >= 4)
			{
				NEW_JON[9] = true;// L2U
				NEW_JON[12] = true;// R2U

				if (UYCMD == 6)
				{
					NEW_JON[15] = true;// L4U
					NEW_JON[18] = true;// R4U
				}
			}
		}

		sprintf_s( oapiDebugString(), 255, "UXCMD%+d UYCMD%+d UZCMD%+d", UXCMD, UYCMD, UZCMD );

		// Y
		// 9 10
		if (UZCMD <= -1)
		{
			NEW_JON[0] = true;// L1L

			if (UZCMD <= -2)
			{
				NEW_JON[1] = true;// L3L

				if (UZCMD <= -3)
				{
					NEW_JON[8] = true;// L2L

					if (UZCMD == -4)
					{
						NEW_JON[14] = true;// L4L
					}
				}
			}
		}
		else if (UZCMD >= 1)
		{
			NEW_JON[3] = true;// R1R

			if (UZCMD >= 2)
			{
				NEW_JON[6] = true;// R3R

				if (UZCMD >= 3)
				{
					NEW_JON[11] = true;// R2R

					if (UZCMD == 4)
					{
						NEW_JON[17] = true;// R4R
					}
				}
			}
		}

		



		// TODO RCS CMD SOP
		WriteCOMPOOL_IS( SCP_FF1_IOM5_CH0_DATA, 0x0000 );
		WriteCOMPOOL_IS( SCP_FF1_IOM13_CH0_DATA, 0x0000 );

		WriteCOMPOOL_IS( SCP_FF2_IOM5_CH0_DATA, 0x0000 );
		WriteCOMPOOL_IS( SCP_FF2_IOM13_CH0_DATA, 0x0000 );

		WriteCOMPOOL_IS( SCP_FF3_IOM5_CH0_DATA, 0x0000 );
		WriteCOMPOOL_IS( SCP_FF3_IOM13_CH0_DATA, 0x0000 );

		WriteCOMPOOL_IS( SCP_FF4_IOM5_CH0_DATA, 0x0000 );
		WriteCOMPOOL_IS( SCP_FF4_IOM13_CH0_DATA, 0x0000 );

		unsigned short cmd = 0;
		if (NEW_JON[0]) cmd |= 0x0002;// L1L
		if (NEW_JON[2]) cmd |= 0x0004;// L1U
		if (NEW_JON[3]) cmd |= 0x0010;// R1R
		if (NEW_JON[4]) cmd |= 0x0020;// R1U
		WriteCOMPOOL_IS( SCP_FA1_IOM2_CH0_DATA, cmd );
		WriteCOMPOOL_IS( SCP_FA1_IOM10_CH0_DATA, cmd );

		cmd = 0;
		if (NEW_JON[1]) cmd |= 0x0002;// L3L
		if (NEW_JON[5]) cmd |= 0x0004;// L3D
		if (NEW_JON[6]) cmd |= 0x0010;// R3R
		if (NEW_JON[7]) cmd |= 0x0020;// R3D
		WriteCOMPOOL_IS( SCP_FA2_IOM2_CH0_DATA, cmd );
		WriteCOMPOOL_IS( SCP_FA2_IOM10_CH0_DATA, cmd );
		
		cmd = 0;
		if (NEW_JON[8]) cmd |= 0x0001;// L2L
		if (NEW_JON[9]) cmd |= 0x0002;// L2U
		if (NEW_JON[10]) cmd |= 0x0004;// L2D
		if (NEW_JON[11]) cmd |= 0x0008;// R2R
		if (NEW_JON[12]) cmd |= 0x0010;// R2U
		if (NEW_JON[13]) cmd |= 0x0020;// R2D
		WriteCOMPOOL_IS( SCP_FA3_IOM2_CH0_DATA, cmd );
		WriteCOMPOOL_IS( SCP_FA3_IOM10_CH0_DATA, cmd );

		cmd = 0;
		if (NEW_JON[14]) cmd |= 0x0001;// L4L
		if (NEW_JON[15]) cmd |= 0x0002;// L4U
		if (NEW_JON[16]) cmd |= 0x0004;// L4D
		if (NEW_JON[17]) cmd |= 0x0008;// R4R
		if (NEW_JON[18]) cmd |= 0x0010;// R4U
		if (NEW_JON[19]) cmd |= 0x0020;// R4D
		WriteCOMPOOL_IS( SCP_FA4_IOM2_CH0_DATA, cmd );
		WriteCOMPOOL_IS( SCP_FA4_IOM10_CH0_DATA, cmd );
		return;
	}

	bool JetSelectionLogic::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			/*case 102:
			case 103:
			case 104:
			case 105:
			case 106:
			case 201:
			case 202:
			case 301:
			case 302:
			case 303:*/
			case 304:
			case 305:
			/*case 601:
			case 602:
			case 603:
			case 801:*/
				return true;
			default:
				return false;
		}
	}
}
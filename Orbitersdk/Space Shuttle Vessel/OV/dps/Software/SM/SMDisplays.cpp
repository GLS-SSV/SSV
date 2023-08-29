#include "SMDisplays.h"
#include "../../IDP.h"
#include "../../../vc/MDU.h"


namespace dps
{
	SMDisplays::SMDisplays( SimpleGPCSystem* _gpc ):GeneralDisplays( _gpc, "SMDisplays" )
	{
		RMS_SEL = 1;
		return;
	}

	SMDisplays::~SMDisplays()
	{
	}

	bool SMDisplays::OnMajorModeChange( unsigned int newMajorMode )
	{
		// always running
		return true;
	}

	bool SMDisplays::ItemInput( int spec, int item, const char* Data )
	{
		switch (spec)
		{
			case 94:
				return ItemInput_SM_SPEC94_PASS( item, Data );
			case dps::MODE_UNDEFINED:
				switch (GetMajorMode())
				{
					case 201:
						return ItemInput_SM_ANTENNA_PASS( item, Data );
					case 202:
						return ItemInput_SM_PLBAYDOORS_PASS( item, Data );
				}
		}
		return false;
	}

	bool SMDisplays::ItemInput_SM_SPEC94_PASS( int item, const char* Data )
	{
		if (item == 1)
		{
			RMS_SEL = 1;
		}
		else if (item == 2)
		{
			RMS_SEL = 2;
		}
		else return false;
		return true;
	}

	bool SMDisplays::ItemInput_SM_ANTENNA_PASS( int item, const char* Data )
	{
		// TODO
		return false;
	}

	bool SMDisplays::ItemInput_SM_PLBAYDOORS_PASS( int item, const char* Data )
	{
		if (item > 17) return false;
		if (item < 3)
		{
			if (item == 1)
			{
				WriteCOMPOOL_IS( SCP_CSBB_POWER_ON_OFF_ITEM, 0x0001 );
			}
			else
			{
				WriteCOMPOOL_IS( SCP_CSBB_POWER_ON_OFF_ITEM, 0x0002 );
			}
			WriteCOMPOOL_IS( SCP_CSBB_POWER_ON_OFF_FLAG, 1 );
		}
		else
		{
			if (item < 14)
			{
				if (item == 3)
				{
					if (ReadCOMPOOL_IS( SCP_CSBB_CONTROL_SWITCH_POS_INDIC ) == 0)
					{
						WriteCOMPOOL_IS( SCP_CSBB_AUTO_MODE_ITEM, ReadCOMPOOL_IS( SCP_CSBB_AUTO_MODE_ITEM ) ^ 1 );
						WriteCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM, 0 );
					}
					else
					{
						return false;
					}
				}
				else
				{
					unsigned short itembit = 1 << (item - 1);
					if (ReadCOMPOOL_IS( SCP_CSBB_CONTROL_SWITCH_POS_INDIC ) == 0)
					{
						WriteCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM, ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) ^ itembit );
						WriteCOMPOOL_IS( SCP_CSBB_AUTO_MODE_ITEM, 0 );
					}
					else
					{
						if (((ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & ~itembit) != 0) && ((ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & itembit) == 0))
						{
							WriteCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM, ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) | itembit );
							WriteCOMPOOL_IS( SCP_CSBB_AUTO_MODE_ITEM, 0 );
						}
						else
						{
							return false;
						}
					}
				}
			}
			else
			{
				if (item == 14)
				{
					if (ReadCOMPOOL_IS( SCP_CSBB_SWITCH_BYPASS_ITEM ) == 1)
					{
						WriteCOMPOOL_IS( SCP_CSBB_SWITCH_BYPASS_ITEM, 0 );
						WriteCOMPOOL_IS( SCP_CSBB_PBD_OPEN_ITEM, 0 );
						WriteCOMPOOL_IS( SCP_CSBB_PBD_STOP_ITEM, 0 );
						WriteCOMPOOL_IS( SCP_CSBB_PBD_CLOSE_ITEM, 0 );
					}
					else
					{
						WriteCOMPOOL_IS( SCP_CSBB_SWITCH_BYPASS_ITEM, 1 );
						WriteCOMPOOL_IS( SCP_CSBB_PBD_STOP_ITEM, 1 );
					}
				}
				else
				{
					if (ReadCOMPOOL_IS( SCP_CSBB_SWITCH_BYPASS_ITEM ) == 1)
					{
						if (item == 15)
						{
							WriteCOMPOOL_IS( SCP_CSBB_PBD_OPEN_ITEM, 1 );
							WriteCOMPOOL_IS( SCP_CSBB_PBD_STOP_ITEM, 0 );
							WriteCOMPOOL_IS( SCP_CSBB_PBD_CLOSE_ITEM, 0 );
						}
						else
						{
							if (item == 16)
							{
								WriteCOMPOOL_IS( SCP_CSBB_PBD_STOP_ITEM, 1 );
								WriteCOMPOOL_IS( SCP_CSBB_PBD_OPEN_ITEM, 0 );
								WriteCOMPOOL_IS( SCP_CSBB_PBD_CLOSE_ITEM, 0 );
							}
							else
							{
								WriteCOMPOOL_IS( SCP_CSBB_PBD_CLOSE_ITEM, 1 );
								WriteCOMPOOL_IS( SCP_CSBB_PBD_OPEN_ITEM, 0 );
								WriteCOMPOOL_IS( SCP_CSBB_PBD_STOP_ITEM, 0 );
							}
						}
					}
					else
					{
						return false;
					}
				}
			}
		}
		return true;
	}

	bool SMDisplays::OnPaint( int spec, vc::MDU* pMDU ) const
	{
		switch (GetMajorMode() / 100)
		{
			case 2:
				switch (spec)
				{
					case 94:
						OnPaint_SM_SPEC94_PASS( pMDU );// PDRS CONTROL
						return true;
					case 95:
						OnPaint_SM_DISP95_PASS( pMDU );// PDRS OVERRIDE
						return true;
					case 96:
						OnPaint_SM_DISP96_PASS( pMDU );// PDRS FAULTS
						return true;
					case 97:
						OnPaint_SM_DISP97_PASS( pMDU );// PL RETENTION
						return true;
					case 169:
						OnPaint_SM_DISP169_PASS( pMDU );// PDRS STATUS
						return true;
					case dps::MODE_UNDEFINED:
						switch (GetMajorMode())
						{
							case 201:
								OnPaint_SM_ANTENNA_PASS( pMDU );// ANTENNA
								return true;
							case 202:
								OnPaint_SM_PLBAYDOORS_PASS( pMDU );// PL BAY DOORS
								return true;
							default:
								return false;
						}
					default:
						return false;
				}
			default:
				return false;
		}
		return false;
	}

	void SMDisplays::OnPaint_SM_SPEC94_PASS( vc::MDU* pMDU ) const
	{
		PrintCommonHeader( "   PDRS CONTROL", pMDU );

		// static parts (labels)
		pMDU->mvprint( 0, 2, "RMS SEL:" );
		pMDU->mvprint( 5, 3, "PORT  1" );
		pMDU->mvprint( 5, 4, "STBD  2" );
		pMDU->mvprint( 2, 5, "3 PL ID" );
		pMDU->mvprint( 2, 6, "4 END EFF" );

		pMDU->mvprint( 18, 2, "RMS PWR" );
		pMDU->mvprint( 15, 3, "34 RMS S/N" );
		pMDU->mvprint( 20, 4, "I/O ON 5" );
		pMDU->mvprint( 23, 5, "OFF 6" );
		
		pMDU->mvprint( 43, 2, "ENA INH" );
		pMDU->mvprint( 32, 3, "SOFT STOP   7   8" );
		pMDU->mvprint( 32, 4, "AUTO BRAKE  9  10" );
		pMDU->mvprint( 32, 5, "POS ENC CK 11  12" );
		pMDU->mvprint( 32, 6, "POHS CNTL  28  29" );

		pMDU->mvprint( 21, 7, "AUTO MODES" );
		pMDU->mvprint( 5, 8, "1" );
		pMDU->mvprint( 13, 8, "2" );
		pMDU->mvprint( 21, 8, "3" );
		pMDU->mvprint( 29, 8, "4" );
		pMDU->mvprint( 3, 9, "13" );
		pMDU->mvprint( 11, 9, "14" );
		pMDU->mvprint( 19, 9, "15" );
		pMDU->mvprint( 27, 9, "16" );
		pMDU->mvprint( 36, 8, "17 START PT" );
		pMDU->mvprint( 39, 9, "LAST  PT" );

		pMDU->mvprint( 14, 11, "OPR CMD MODES / POR REF" );
		pMDU->mvprint( 2, 12, "END POS" );
		pMDU->mvprint( 15, 12, "END ATT" );
		pMDU->mvprint( 0, 13, "18 X" );
		pMDU->mvprint( 0, 14, "19 Y" );
		pMDU->mvprint( 0, 15, "20 Z" );
		pMDU->mvprint( 14, 13, "21 P" );
		pMDU->mvprint( 14, 14, "22 Y" );
		pMDU->mvprint( 14, 15, "23 R" );
		pMDU->mvprint( 27, 12, "24 PL INIT ID" );
		pMDU->mvprint( 27, 14, "CMD CK 25" );
		pMDU->mvprint( 27, 16, "POR DISPLAY 30" );

		pMDU->mvprint( 6, 17, "STO/DPY" );
		pMDU->mvprint( 1, 18, "MPM" );
		
		pMDU->mvprint( 5, 20, "LAT/REL/RDY" );
		pMDU->mvprint( 1, 21, "AFT" );
		pMDU->mvprint( 1, 22, "MID" );
		pMDU->mvprint( 1, 23, "FWD" );
		
		pMDU->mvprint( 31, 18, "ORB LD CMD REF" );
		pMDU->mvprint( 27, 19, "NORM  FLY-CAMR  FLY-PL" );
		pMDU->mvprint( 28, 20, "31" );
		pMDU->mvprint( 36, 20, "32" );
		pMDU->mvprint( 45, 20, "33" );
		
		pMDU->mvprint( 27, 22, "26 WR RANGE" );
		pMDU->mvprint( 27, 23, "AUTO BRAKE CK 27" );

		// dynamic parts
		pMDU->mvprint( 12, (RMS_SEL == 1) ? 3 : 4, "*" );

		if (RMS_SEL == 1)
		{
			// PORT RMS
			unsigned short msw_oa2_5_0 = ReadCOMPOOL_IS( SCP_OA2_IOM5_CH0_DATA );
			unsigned short msw_oa2_7_2 = ReadCOMPOOL_IS( SCP_OA2_IOM7_CH2_DATA );
			unsigned short msw_oa2_12_1 = ReadCOMPOOL_IS( SCP_OA2_IOM12_CH1_DATA );
			unsigned short msw_oa2_1_2 = ReadCOMPOOL_IS( SCP_OA2_IOM1_CH2_DATA );
			unsigned short msw_oa3_5_0 = ReadCOMPOOL_IS( SCP_OA3_IOM5_CH0_DATA );
			unsigned short msw_of1_6_2 = ReadCOMPOOL_IS( SCP_OF1_IOM6_CH2_DATA );
			unsigned short msw_oa3_10_2 = ReadCOMPOOL_IS( SCP_OA3_IOM10_CH2_DATA );
			unsigned short msw_of1_12_0 = ReadCOMPOOL_IS( SCP_OF1_IOM12_CH0_DATA );
			unsigned short msw_oa3_1_2 = ReadCOMPOOL_IS( SCP_OA3_IOM1_CH2_DATA );
			unsigned short msw_of1_4_2 = ReadCOMPOOL_IS( SCP_OF1_IOM4_CH2_DATA );
			unsigned short msw_of4_4_1 = ReadCOMPOOL_IS( SCP_OF4_IOM4_CH1_DATA );
			unsigned short msw_oa1_10_1 = ReadCOMPOOL_IS( SCP_OA1_IOM10_CH1_DATA );
			unsigned short msw_of4_5_2 = ReadCOMPOOL_IS( SCP_OF4_IOM5_CH2_DATA );
			unsigned short msw_oa1_12_0 = ReadCOMPOOL_IS( SCP_OA1_IOM12_CH0_DATA );
			unsigned short msw_of4_2_1 = ReadCOMPOOL_IS( SCP_OF4_IOM2_CH1_DATA );
			unsigned short msw_oa1_7_1 = ReadCOMPOOL_IS( SCP_OA1_IOM7_CH1_DATA );
			unsigned short msw_oa2_5_2 = ReadCOMPOOL_IS( SCP_OA2_IOM5_CH2_DATA );
			unsigned short msw_oa2_12_2 = ReadCOMPOOL_IS( SCP_OA2_IOM12_CH2_DATA );
			unsigned short msw_oa2_10_2 = ReadCOMPOOL_IS( SCP_OA2_IOM10_CH2_DATA );
			unsigned short msw_oa2_12_0 = ReadCOMPOOL_IS( SCP_OA2_IOM12_CH0_DATA );

			// STO/DPLY
			pMDU->mvprint( 0, 17, "PORT" );
			// MPM
			pMDU->mvprint( 6, 18, (msw_oa2_5_0 & 0x0001) ? "1" : "0" );
			pMDU->mvprint( 8, 18, (msw_oa2_7_2 & 0x0002) ? "1" : "0" );
			pMDU->mvprint( 10, 18, (msw_oa2_12_1 & 0x0001) ? "1" : "0" );
			pMDU->mvprint( 12, 18, (msw_oa2_1_2 & 0x0002) ? "1" : "0" );
			// LAT/REL/RDY
			// AFT
			pMDU->mvprint( 5, 21, (msw_oa3_5_0 & 0x0001) ? "1" : "0" );
			pMDU->mvprint( 7, 21, (msw_of1_6_2 & 0x0001) ? "1" : "0" );
			pMDU->mvprint( 9, 21, (msw_oa3_10_2 & 0x0001) ? "1" : "0" );
			pMDU->mvprint( 11, 21, (msw_of1_12_0 & 0x0001) ? "1" : "0" );
			pMDU->mvprint( 13, 21, (msw_oa3_1_2 & 0x0002) ? "1" : "0" );
			pMDU->mvprint( 15, 21, (msw_of1_4_2 & 0x0002) ? "1" : "0" );
			// MID
			pMDU->mvprint( 5, 22, (msw_of4_4_1 & 0x0001) ? "1" : "0" );
			pMDU->mvprint( 7, 22, (msw_oa1_10_1 & 0x0001) ? "1" : "0" );
			pMDU->mvprint( 9, 22, (msw_of4_5_2 & 0x0001) ? "1" : "0" );
			pMDU->mvprint( 11, 22, (msw_oa1_12_0 & 0x0001) ? "1" : "0" );
			pMDU->mvprint( 13, 22, (msw_of4_2_1 & 0x0002) ? "1" : "0" );
			pMDU->mvprint( 15, 22, (msw_oa1_7_1 & 0x0001) ? "1" : "0" );
			// FWD
			pMDU->mvprint( 5, 23, (msw_oa2_5_2 & 0x0001) ? "1" : "0" );
			pMDU->mvprint( 7, 23, (msw_oa2_12_2 & 0x0001) ? "1" : "0" );
			pMDU->mvprint( 9, 23, (msw_oa2_1_2 & 0x0001) ? "1" : "0" );
			pMDU->mvprint( 11, 23, (msw_oa2_7_2 & 0x0001) ? "1" : "0" );
			pMDU->mvprint( 13, 23, (msw_oa2_10_2 & 0x0001) ? "1" : "0" );
			pMDU->mvprint( 15, 23, (msw_oa2_12_0 & 0x0001) ? "1" : "0" );
		}
		else
		{
			// STBD RMS
			unsigned short msw_oa2_5_0 = ReadCOMPOOL_IS( SCP_OA2_IOM5_CH0_DATA );
			unsigned short msw_oa2_7_2 = ReadCOMPOOL_IS( SCP_OA2_IOM7_CH2_DATA );
			unsigned short msw_oa2_12_1 = ReadCOMPOOL_IS( SCP_OA2_IOM12_CH1_DATA );
			unsigned short msw_oa2_1_2 = ReadCOMPOOL_IS( SCP_OA2_IOM1_CH2_DATA );
			unsigned short msw_oa3_5_0 = ReadCOMPOOL_IS( SCP_OA3_IOM5_CH0_DATA );
			unsigned short msw_of1_6_2 = ReadCOMPOOL_IS( SCP_OF1_IOM6_CH2_DATA );
			unsigned short msw_oa3_10_2 = ReadCOMPOOL_IS( SCP_OA3_IOM10_CH2_DATA );
			unsigned short msw_of1_12_0 = ReadCOMPOOL_IS( SCP_OF1_IOM12_CH0_DATA );
			unsigned short msw_oa3_1_2 = ReadCOMPOOL_IS( SCP_OA3_IOM1_CH2_DATA );
			unsigned short msw_of1_4_2 = ReadCOMPOOL_IS( SCP_OF1_IOM4_CH2_DATA );
			unsigned short msw_of4_4_1 = ReadCOMPOOL_IS( SCP_OF4_IOM4_CH1_DATA );
			unsigned short msw_oa1_10_1 = ReadCOMPOOL_IS( SCP_OA1_IOM10_CH1_DATA );
			unsigned short msw_of4_5_2 = ReadCOMPOOL_IS( SCP_OF4_IOM5_CH2_DATA );
			unsigned short msw_oa1_12_0 = ReadCOMPOOL_IS( SCP_OA1_IOM12_CH0_DATA );
			unsigned short msw_of4_2_1 = ReadCOMPOOL_IS( SCP_OF4_IOM2_CH1_DATA );
			unsigned short msw_oa1_7_1 = ReadCOMPOOL_IS( SCP_OA1_IOM7_CH1_DATA );
			unsigned short msw_oa2_5_2 = ReadCOMPOOL_IS( SCP_OA2_IOM5_CH2_DATA );
			unsigned short msw_oa2_12_2 = ReadCOMPOOL_IS( SCP_OA2_IOM12_CH2_DATA );
			unsigned short msw_oa2_10_2 = ReadCOMPOOL_IS( SCP_OA2_IOM10_CH2_DATA );
			unsigned short msw_oa2_12_0 = ReadCOMPOOL_IS( SCP_OA2_IOM12_CH0_DATA );

			// STO/DPLY
			pMDU->mvprint( 0, 17, "STBD" );
			// MPM
			pMDU->mvprint( 6, 18, (msw_oa2_5_0 & 0x0002) ? "1" : "0" );
			pMDU->mvprint( 8, 18, (msw_oa2_7_2 & 0x0008) ? "1" : "0" );
			pMDU->mvprint( 10, 18, (msw_oa2_12_1 & 0x0002) ? "1" : "0" );
			pMDU->mvprint( 12, 18, (msw_oa2_1_2 & 0x0008) ? "1" : "0" );
			// LAT/REL/RDY
			// AFT
			pMDU->mvprint( 5, 21, (msw_oa3_5_0 & 0x0002) ? "1" : "0" );
			pMDU->mvprint( 7, 21, (msw_of1_6_2 & 0x0002) ? "1" : "0" );
			pMDU->mvprint( 9, 21, (msw_oa3_10_2 & 0x0002) ? "1" : "0" );
			pMDU->mvprint( 11, 21, (msw_of1_12_0 & 0x0002) ? "1" : "0" );
			pMDU->mvprint( 13, 21, (msw_oa3_1_2 & 0x0004) ? "1" : "0" );
			pMDU->mvprint( 15, 21, (msw_of1_4_2 & 0x0004) ? "1" : "0" );
			// MID
			pMDU->mvprint( 5, 22, (msw_of4_4_1 & 0x0002) ? "1" : "0" );
			pMDU->mvprint( 7, 22, (msw_oa1_10_1 & 0x0002) ? "1" : "0" );
			pMDU->mvprint( 9, 22, (msw_of4_5_2 & 0x0002) ? "1" : "0" );
			pMDU->mvprint( 11, 22, (msw_oa1_12_0 & 0x0002) ? "1" : "0" );
			pMDU->mvprint( 13, 22, (msw_of4_2_1 & 0x0004) ? "1" : "0" );
			pMDU->mvprint( 15, 22, (msw_oa1_7_1 & 0x0002) ? "1" : "0" );
			// FWD
			pMDU->mvprint( 5, 23, (msw_oa2_5_2 & 0x0002) ? "1" : "0" );
			pMDU->mvprint( 7, 23, (msw_oa2_12_2 & 0x0002) ? "1" : "0" );
			pMDU->mvprint( 9, 23, (msw_oa2_1_2 & 0x0004) ? "1" : "0" );
			pMDU->mvprint( 11, 23, (msw_oa2_7_2 & 0x0004) ? "1" : "0" );
			pMDU->mvprint( 13, 23, (msw_oa2_10_2 & 0x0002) ? "1" : "0" );
			pMDU->mvprint( 15, 23, (msw_oa2_12_0 & 0x0002) ? "1" : "0" );
		}

		// TODO
		return;
	}

	void SMDisplays::OnPaint_SM_DISP95_PASS( vc::MDU* pMDU ) const
	{
		PrintCommonHeader( " PDRS OVERRIDE", pMDU );

		// static parts (labels)
		pMDU->mvprint( 0, 2, "MODE SW OVRD 1" );
		pMDU->mvprint( 3, 3, "MODE   SEL IND" );
		pMDU->mvprint( 2, 4, "ORB UNL  2" );
		pMDU->mvprint( 2, 5, "SINGLE   3" );
		pMDU->mvprint( 2, 6, "END EFF  4" );
		pMDU->mvprint( 2, 7, "ORB LD   5" );
		pMDU->mvprint( 2, 8, "PL       6" );
		pMDU->mvprint( 2, 9, "OPR CMD  7" );
		pMDU->mvprint( 2, 10, "AUTO 1   8" );
		pMDU->mvprint( 2, 11, "AUTO 2   9" );
		pMDU->mvprint( 2, 12, "AUTO 3  10" );
		pMDU->mvprint( 2, 13, "AUTO 4  11" );
		pMDU->mvprint( 2, 14, "TEST    12" );
		pMDU->mvprint( 2, 15, "ENTER   13" );
		
		pMDU->mvprint( 0, 17, "LOADED RATE  14" );
		pMDU->mvprint( 0, 18, "STOWED OPS   15" );
		pMDU->mvprint( 0, 19, "SIN/DIR SW" );
		pMDU->mvprint( 3, 20, "REASSIGN  16" );
		
		pMDU->mvprint( 18, 3, "JNT SW OVRD 17" );
		pMDU->mvprint( 19, 4, "JOINT      SEL" );
		pMDU->mvprint( 19, 5, "SH YAW     18" );
		pMDU->mvprint( 19, 6, "SH PITCH   19" );
		pMDU->mvprint( 19, 7, "EL PITCH   20" );
		pMDU->mvprint( 19, 8, "WR PITCH   21" );
		pMDU->mvprint( 19, 9, "WR YAW     22" );
		pMDU->mvprint( 19, 10, "WR ROLL    23" );
		pMDU->mvprint( 19, 11, "EE TEMP    24" );
		pMDU->mvprint( 19, 12, "CRIT TEMP  25" );
		
		pMDU->mvprint( 18, 14, "MCIU OVERRIDE" );
		pMDU->mvprint( 19, 15, "SAFING CAN 35" );
		pMDU->mvprint( 19, 16, "ABE OVRD A 36" );
		pMDU->mvprint( 19, 17, "ABE OVRD B 37" );
		pMDU->mvprint( 19, 18, "ABE OVRD C 38" );
		
		pMDU->mvprint( 35, 3, "RATE SW OVRD 26" );
		pMDU->mvprint( 36, 4, "VERNIER     27" );
		pMDU->mvprint( 36, 5, "COARSE      28" );

		pMDU->mvprint( 35, 7, "AUTO SW OVRD 29" );
		pMDU->mvprint( 36, 8, "PROCEED     30" );
		pMDU->mvprint( 36, 9, "STOP        31" );
		
		pMDU->mvprint( 35, 11, "HC AXIS CHG  32" );
		pMDU->mvprint( 36, 12, "THC         33" );
		pMDU->mvprint( 36, 13, "RHC         34" );

		// static parts (lines)
		pMDU->Line( 170, 28, 170, 294 );
		pMDU->Line( 340, 42, 340, 266 );
		
		pMDU->Line( 170, 196, 340, 196 );

		// dynamic parts
		// TODO
		return;
	}

	void SMDisplays::OnPaint_SM_DISP96_PASS( vc::MDU* pMDU ) const
	{
		PrintCommonHeader( "   PDRS FAULTS", pMDU );

		// static parts (labels)
		pMDU->mvprint( 0, 2, "ABE BITE:" );
		pMDU->mvprint( 22, 2, "SY SP EP WP WY WR" );
		pMDU->mvprint( 1, 3, "MDA OVERCURRENT/" );
		pMDU->mvprint( 3, 4, "MOTOR DRV FAULT" );
		pMDU->mvprint( 1, 5, "COMMUTATOR" );
		pMDU->mvprint( 1, 6, "TACHOMETER" );
		pMDU->mvprint( 1, 7, "TOTAL COMPENSATOR" );
		pMDU->mvprint( 1, 8, "MICROCOMPUTER" );
		pMDU->mvprint( 1, 9, "MDA DEMAND VOLTAGE" );
		pMDU->mvprint( 1, 10, "A/D CONVERTER" );
		pMDU->mvprint( 1, 11, "BRAKE" );
		pMDU->mvprint( 1, 12, "POS ENCONDER" );
		pMDU->mvprint( 1, 13, "BACKUP RELAY" );
		pMDU->mvprint( 1, 14, "CHECK CRT:" );
		pMDU->mvprint( 1, 15, "DIRECT DRIVE BITE" );
		pMDU->mvprint( 1, 16, "POS ENCODER" );
		pMDU->mvprint( 0, 17, "CONTR ERROR" );
		pMDU->mvprint( 0, 18, "REACH LIMIT" );
		
		pMDU->mvprint( 40, 3, "MCIU:" );
		pMDU->mvprint( 41, 4, "MADC" );
		pMDU->mvprint( 41, 5, "MCPC" );
		pMDU->mvprint( 41, 6, "ICP" );
		
		pMDU->mvprint( 40, 8, "ABE:" );
		pMDU->mvprint( 41, 9, "COMM" );
		
		pMDU->mvprint( 40, 11, "CHECK CRT:" );
		pMDU->mvprint( 41, 12, "DC/MCIU" );
		pMDU->mvprint( 41, 13, "EXT FS" );
		pMDU->mvprint( 41, 14, "EE FLAG" );
		pMDU->mvprint( 41, 15, "EEEU" );
		pMDU->mvprint( 41, 16, "EE CMDS" );
		pMDU->mvprint( 41, 17, "HC" );
		pMDU->mvprint( 41, 18, "MCIU HC" );
		pMDU->mvprint( 41, 19, "TMP CKT" );
		
		pMDU->mvprint( 0, 21, "CHECK CRT:" );
		pMDU->mvprint( 16, 21, "SY" );
		pMDU->mvprint( 21, 21, "SP" );
		pMDU->mvprint( 26, 21, "EP" );
		pMDU->mvprint( 31, 21, "WP" );
		pMDU->mvprint( 36, 21, "WY" );
		pMDU->mvprint( 41, 21, "WR" );
		pMDU->mvprint( 1, 22, "SPA BITE TEST" );

		// static parts (lines)
		pMDU->Line( 0, 42, 30, 42 );
		pMDU->Line( 220, 42, 390, 42 );
		pMDU->Line( 10, 210, 100, 210 );
		pMDU->Line( 0, 252, 90, 252 );
		pMDU->Line( 0, 266, 90, 266 );
		pMDU->Line( 400, 56, 440, 56 );
		pMDU->Line( 400, 126, 430, 126 );
		pMDU->Line( 400, 168, 490, 168 );
		pMDU->Line( 0, 308, 90, 308 );
		pMDU->Line( 150, 308, 440, 308 );

		// dynamic parts
		// TODO
		return;
	}

	void SMDisplays::OnPaint_SM_DISP97_PASS( vc::MDU* pMDU ) const
	{
		PrintCommonHeader( "  PL RETENTION", pMDU );

		// static parts (labels)
		pMDU->mvprint( 17, 4, "LATCH LATCH LATCH LATCH LATCH" );
		pMDU->mvprint( 19, 5, "1" );
		pMDU->mvprint( 25, 5, "2" );
		pMDU->mvprint( 31, 5, "3" );
		pMDU->mvprint( 37, 5, "4" );
		pMDU->mvprint( 43, 5, "5" );
		pMDU->mvprint( 17, 6, "AB/AB AB/AB AB/AB AB/AB AB/AB" );
		
		pMDU->mvprint( 4, 7, "PL SEL 1" );
		pMDU->mvprint( 5, 8, "RDY-FOR-LAT" );
		pMDU->mvprint( 9, 9, "LAT/REL" );
		pMDU->mvprint( 19, 9, "/" );
		pMDU->mvprint( 25, 9, "/" );
		pMDU->mvprint( 31, 9, "/" );
		pMDU->mvprint( 37, 9, "/" );
		pMDU->mvprint( 43, 9, "/" );

		pMDU->mvprint( 4, 11, "PL SEL 2" );
		pMDU->mvprint( 5, 12, "RDY-FOR-LAT" );
		pMDU->mvprint( 9, 13, "LAT/REL" );
		pMDU->mvprint( 19, 13, "/" );
		pMDU->mvprint( 25, 13, "/" );
		pMDU->mvprint( 31, 13, "/" );
		pMDU->mvprint( 37, 13, "/" );
		pMDU->mvprint( 43, 13, "/" );

		pMDU->mvprint( 4, 15, "PL SEL 3" );
		pMDU->mvprint( 5, 16, "RDY-FOR-LAT" );
		pMDU->mvprint( 9, 17, "LAT/REL" );
		pMDU->mvprint( 19, 17, "/" );
		pMDU->mvprint( 25, 17, "/" );
		pMDU->mvprint( 31, 17, "/" );
		pMDU->mvprint( 37, 17, "/" );
		pMDU->mvprint( 43, 17, "/" );

		// static parts (lines)
		pMDU->Line( 30, 98, 465, 98 );
		pMDU->Line( 30, 154, 465, 154 );
		pMDU->Line( 30, 210, 465, 210 );
		pMDU->Line( 30, 266, 465, 266 );
		
		pMDU->Line( 165, 42, 165, 266 );
		pMDU->Line( 225, 42, 225, 266 );
		pMDU->Line( 285, 42, 285, 266 );
		pMDU->Line( 345, 42, 345, 266 );
		pMDU->Line( 405, 42, 405, 266 );
		pMDU->Line( 465, 42, 465, 266 );

		// dynamic parts
		unsigned short msw_of1_4_1 = ReadCOMPOOL_IS( SCP_OF1_IOM4_CH1_DATA );
		unsigned short msw_of1_4_2 = ReadCOMPOOL_IS( SCP_OF1_IOM4_CH2_DATA );
		unsigned short msw_of1_6_1 = ReadCOMPOOL_IS( SCP_OF1_IOM6_CH1_DATA );
		unsigned short msw_of1_14_0 = ReadCOMPOOL_IS( SCP_OF1_IOM14_CH0_DATA );
		unsigned short msw_of1_14_1 = ReadCOMPOOL_IS( SCP_OF1_IOM14_CH1_DATA );
		unsigned short msw_of2_4_1 = ReadCOMPOOL_IS( SCP_OF2_IOM4_CH1_DATA );
		unsigned short msw_of2_4_2 = ReadCOMPOOL_IS( SCP_OF2_IOM4_CH2_DATA );
		unsigned short msw_of2_6_2 = ReadCOMPOOL_IS( SCP_OF2_IOM6_CH2_DATA );
		unsigned short msw_of2_12_1 = ReadCOMPOOL_IS( SCP_OF2_IOM12_CH1_DATA );
		unsigned short msw_of2_12_2 = ReadCOMPOOL_IS( SCP_OF2_IOM12_CH2_DATA );
		unsigned short msw_of2_14_0 = ReadCOMPOOL_IS( SCP_OF2_IOM14_CH0_DATA );
		unsigned short msw_of2_14_1 = ReadCOMPOOL_IS( SCP_OF2_IOM14_CH1_DATA );
		unsigned short msw_of2_14_2 = ReadCOMPOOL_IS( SCP_OF2_IOM14_CH2_DATA );
		unsigned short msw_of4_7_2 = ReadCOMPOOL_IS( SCP_OF4_IOM7_CH2_DATA );
		unsigned short msw_of4_10_0 = ReadCOMPOOL_IS( SCP_OF4_IOM10_CH0_DATA );
		unsigned short msw_of4_13_0 = ReadCOMPOOL_IS( SCP_OF4_IOM13_CH0_DATA );
		unsigned short msw_of4_13_1 = ReadCOMPOOL_IS( SCP_OF4_IOM13_CH1_DATA );
		unsigned short msw_of4_15_0 = ReadCOMPOOL_IS( SCP_OF4_IOM15_CH0_DATA );
		unsigned short msw_oa3_1_2 = ReadCOMPOOL_IS( SCP_OA3_IOM1_CH2_DATA );
		unsigned short msw_oa3_12_0 = ReadCOMPOOL_IS( SCP_OA3_IOM12_CH0_DATA );
		unsigned short msw_oa3_12_1 = ReadCOMPOOL_IS( SCP_OA3_IOM12_CH1_DATA );
		// RDY, LAT, REL
		// PL 1
		if ((msw_of4_15_0 & 0x0200) || (msw_of4_10_0 & 0x0001))// PL1 or MON
		{
			// 1A
			pMDU->mvprint( 17, 8, (msw_oa3_12_0 & 0x0004) ? "1" : "0" );
			pMDU->mvprint( 17, 9, (msw_oa3_12_0 & 0x0002) ? "1" : "0" );
			pMDU->mvprint( 20, 9, (msw_oa3_12_0 & 0x0001) ? "1" : "0" );
			// 1B
			pMDU->mvprint( 18, 8, (msw_of2_14_0 & 0x0020) ? "1" : "0" );
			pMDU->mvprint( 18, 9, (msw_of2_14_0 & 0x0010) ? "1" : "0" );
			pMDU->mvprint( 21, 9, (msw_of2_14_0 & 0x0008) ? "1" : "0" );
			// 2A
			pMDU->mvprint( 23, 8, (msw_oa3_12_0 & 0x0100) ? "1" : "0" );
			pMDU->mvprint( 23, 9, (msw_oa3_12_0 & 0x0080) ? "1" : "0" );
			pMDU->mvprint( 26, 9, (msw_oa3_12_0 & 0x0040) ? "1" : "0" );
			// 2B
			pMDU->mvprint( 24, 8, (msw_of2_14_0 & 0x4000) ? "1" : "0" );
			pMDU->mvprint( 24, 9, (msw_of2_14_0 & 0x2000) ? "1" : "0" );
			pMDU->mvprint( 27, 9, (msw_of2_14_0 & 0x1000) ? "1" : "0" );
			// 3A
			pMDU->mvprint( 29, 8, (msw_oa3_12_1 & 0x0004) ? "1" : "0" );
			pMDU->mvprint( 29, 9, (msw_oa3_12_1 & 0x0002) ? "1" : "0" );
			pMDU->mvprint( 32, 9, (msw_oa3_12_1 & 0x0001) ? "1" : "0" );
			// 3B
			pMDU->mvprint( 30, 8, (msw_of2_14_1 & 0x0020) ? "1" : "0" );
			pMDU->mvprint( 30, 9, (msw_of2_14_1 & 0x0010) ? "1" : "0" );
			pMDU->mvprint( 33, 9, (msw_of2_14_1 & 0x0008) ? "1" : "0" );
			// 4A
			pMDU->mvprint( 35, 8, (msw_oa3_12_1 & 0x0020) ? "1" : "0" );
			pMDU->mvprint( 35, 9, (msw_oa3_12_1 & 0x0010) ? "1" : "0" );
			pMDU->mvprint( 38, 9, (msw_oa3_12_1 & 0x0008) ? "1" : "0" );
			// 4B
			pMDU->mvprint( 36, 8, (msw_of2_14_1 & 0x0800) ? "1" : "0" );
			pMDU->mvprint( 36, 9, (msw_of2_14_1 & 0x0400) ? "1" : "0" );
			pMDU->mvprint( 39, 9, (msw_of2_14_1 & 0x0200) ? "1" : "0" );
			// 5A
			pMDU->mvprint( 41, 8, (msw_oa3_12_1 & 0x0100) ? "1" : "0" );
			pMDU->mvprint( 41, 9, (msw_oa3_12_1 & 0x0080) ? "1" : "0" );
			pMDU->mvprint( 44, 9, (msw_oa3_12_1 & 0x0040) ? "1" : "0" );
			// 5B
			pMDU->mvprint( 42, 8, (msw_of2_14_2 & 0x0020) ? "1" : "0" );
			pMDU->mvprint( 42, 9, (msw_of2_14_2 & 0x0010) ? "1" : "0" );
			pMDU->mvprint( 45, 9, (msw_of2_14_2 & 0x0008) ? "1" : "0" );
		}

		// PL 2
		if ((msw_of4_13_1 & 0x0001) || (msw_of4_10_0 & 0x0001))// PL2 or MON
		{
			// 1A
			pMDU->mvprint( 17, 12, (msw_oa3_12_0 & 0x0020) ? "1" : "0" );
			pMDU->mvprint( 17, 13, (msw_oa3_1_2 & 0x0001) ? "1" : "0" );
			pMDU->mvprint( 20, 13, (msw_oa3_12_0 & 0x0008) ? "1" : "0" );
			// 1B
			pMDU->mvprint( 18, 12, (msw_of2_14_0 & 0x0100) ? "1" : "0" );
			pMDU->mvprint( 18, 13, (msw_of2_12_2 & 0x0001) ? "1" : "0" );
			pMDU->mvprint( 21, 13, (msw_of2_14_0 & 0x0040) ? "1" : "0" );
			// 2A
			pMDU->mvprint( 23, 12, (msw_of4_15_0 & 0x0004) ? "1" : "0" );
			pMDU->mvprint( 23, 13, (msw_of4_7_2 & 0x0001) ? "1" : "0" );
			pMDU->mvprint( 26, 13, (msw_of4_15_0 & 0x0001) ? "1" : "0" );
			// 2B
			pMDU->mvprint( 24, 12, (msw_of1_14_0 & 0x0020) ? "1" : "0" );
			pMDU->mvprint( 24, 13, (msw_of1_4_1 & 0x0002) ? "1" : "0" );
			pMDU->mvprint( 27, 13, (msw_of1_14_0 & 0x0008) ? "1" : "0" );
			// 3A
			pMDU->mvprint( 29, 12, (msw_of4_15_0 & 0x0020) ? "1" : "0" );
			pMDU->mvprint( 29, 13, (msw_of4_15_0 & 0x0010) ? "1" : "0" );
			pMDU->mvprint( 32, 13, (msw_of4_15_0 & 0x0008) ? "1" : "0" );
			// 3B
			pMDU->mvprint( 30, 12, (msw_of1_14_0 & 0x0800) ? "1" : "0" );
			pMDU->mvprint( 30, 13, (msw_of1_14_0 & 0x0400) ? "1" : "0" );
			pMDU->mvprint( 33, 13, (msw_of1_14_0 & 0x0200) ? "1" : "0" );
			// 4A
			pMDU->mvprint( 35, 12, (msw_of4_15_0 & 0x0100) ? "1" : "0" );
			pMDU->mvprint( 35, 13, (msw_of4_15_0 & 0x0080) ? "1" : "0" );
			pMDU->mvprint( 38, 13, (msw_of4_15_0 & 0x0040) ? "1" : "0" );
			// 4B
			pMDU->mvprint( 36, 12, (msw_of1_14_1 & 0x0004) ? "1" : "0" );
			pMDU->mvprint( 36, 13, (msw_of1_14_1 & 0x0002) ? "1" : "0" );
			pMDU->mvprint( 39, 13, (msw_of1_14_1 & 0x0001) ? "1" : "0" );
			// 5A
			pMDU->mvprint( 41, 12, (msw_of2_14_1 & 0x4000) ? "1" : "0" );
			pMDU->mvprint( 41, 13, (msw_of2_14_1 & 0x2000) ? "1" : "0" );
			pMDU->mvprint( 44, 13, (msw_of2_14_1 & 0x1000) ? "1" : "0" );
			// 5B
			pMDU->mvprint( 42, 12, (msw_of1_14_1 & 0x0100) ? "1" : "0" );
			pMDU->mvprint( 42, 13, (msw_of1_14_1 & 0x0080) ? "1" : "0" );
			pMDU->mvprint( 45, 13, (msw_of1_14_1 & 0x0040) ? "1" : "0" );
		}

		// PL 3
		if ((msw_of4_13_0 & 0x0001) || (msw_of4_10_0 & 0x0001))// PL3 or MON
		{
			// 1A
			pMDU->mvprint( 17, 16, (msw_of2_14_0 & 0x0004) ? "1" : "0" );
			pMDU->mvprint( 17, 17, (msw_of2_14_0 & 0x0002) ? "1" : "0" );
			pMDU->mvprint( 20, 17, (msw_of2_14_0 & 0x0001) ? "1" : "0" );
			// 1B
			pMDU->mvprint( 18, 16, (msw_of1_14_0 & 0x0004) ? "1" : "0" );
			pMDU->mvprint( 18, 17, (msw_of1_14_0 & 0x0002) ? "1" : "0" );
			pMDU->mvprint( 21, 17, (msw_of1_14_0 & 0x0001) ? "1" : "0" );
			// 2A
			pMDU->mvprint( 23, 16, (msw_of2_14_0 & 0x0800) ? "1" : "0" );
			pMDU->mvprint( 23, 17, (msw_of2_14_0 & 0x0400) ? "1" : "0" );
			pMDU->mvprint( 26, 17, (msw_of2_14_0 & 0x0200) ? "1" : "0" );
			// 2B
			pMDU->mvprint( 24, 16, (msw_of1_14_0 & 0x0100) ? "1" : "0" );
			pMDU->mvprint( 24, 17, (msw_of1_14_0 & 0x0080) ? "1" : "0" );
			pMDU->mvprint( 27, 17, (msw_of1_14_0 & 0x0040) ? "1" : "0" );
			// 3A
			pMDU->mvprint( 29, 16, (msw_of2_14_1 & 0x0004) ? "1" : "0" );
			pMDU->mvprint( 29, 17, (msw_of2_12_1 & 0x0004) ? "1" : "0" );
			pMDU->mvprint( 32, 17, (msw_of2_14_1 & 0x0001) ? "1" : "0" );
			// 3B
			pMDU->mvprint( 30, 16, (msw_of1_14_0 & 0x4000) ? "1" : "0" );
			pMDU->mvprint( 30, 17, (msw_of1_14_0 & 0x2000) ? "1" : "0" );
			pMDU->mvprint( 33, 17, (msw_of1_14_0 & 0x1000) ? "1" : "0" );
			// 4A
			pMDU->mvprint( 35, 16, (msw_of2_14_1 & 0x0100) ? "1" : "0" );
			pMDU->mvprint( 35, 17, (msw_of2_6_2 & 0x0001) ? "1" : "0" );
			pMDU->mvprint( 38, 17, (msw_of2_4_1 & 0x0002) ? "1" : "0" );
			// 4B
			pMDU->mvprint( 36, 16, (msw_of1_14_1 & 0x0020) ? "1" : "0" );
			pMDU->mvprint( 36, 17, (msw_of1_6_1 & 0x0001) ? "1" : "0" );
			pMDU->mvprint( 39, 17, (msw_of1_4_2 & 0x0001) ? "1" : "0" );
			// 5A
			pMDU->mvprint( 41, 16, (msw_of2_14_2 & 0x0004) ? "1" : "0" );
			pMDU->mvprint( 41, 17, (msw_of2_4_2 & 0x0001) ? "1" : "0" );
			pMDU->mvprint( 44, 17, (msw_of2_14_1 & 0x0002) ? "1" : "0" );
			// 5B
			pMDU->mvprint( 42, 16, (msw_of1_14_1 & 0x0800) ? "1" : "0" );
			pMDU->mvprint( 42, 17, (msw_of1_4_1 & 0x0001) ? "1" : "0" );
			pMDU->mvprint( 45, 17, (msw_of1_14_1 & 0x0200) ? "1" : "0" );
		}
		return;
	}

	void SMDisplays::OnPaint_SM_DISP169_PASS( vc::MDU* pMDU ) const
	{
		PrintCommonHeader( "   PDRS STATUS", pMDU );

		// static parts (labels)
		pMDU->mvprint( 0, 2, "RMS SEL:" );
		pMDU->mvprint( 0, 3, "POR REF SEL:" );

		pMDU->mvprint( 37, 3, "LAST  PT" );
		pMDU->mvprint( 22, 4, "POHS ERR" );
		pMDU->mvprint( 36, 4, "ATT ERR" );
		
		pMDU->mvprint( 20, 5, "X/P" );
		pMDU->mvprint( 32, 5, "Y/Y" );
		pMDU->mvprint( 44, 5, "Z/R" );
		pMDU->mvprint( 0, 6, "POHS POS REF" );
		pMDU->mvprint( 0, 7, "POHS ATT REF" );
		pMDU->mvprint( 0, 9, "POSITION" );
		pMDU->mvprint( 0, 10, "ATTITUDE" );
		pMDU->mvprint( 0, 12, "TRANS RATES ACT" );
		pMDU->mvprint( 12, 13, "CMD" );
		pMDU->mvprint( 0, 15, "ROT RATES   ACT" );
		pMDU->mvprint( 12, 16, "CMD" );

		pMDU->mvprint( 8, 18, "JOINT ANGLES" );
		pMDU->mvprint( 3, 19, "SY" );
		pMDU->mvprint( 13, 19, "SP" );
		pMDU->mvprint( 23, 19, "EP" );
		pMDU->mvprint( 3, 21, "WP" );
		pMDU->mvprint( 13, 21, "WY" );
		pMDU->mvprint( 23, 21, "WR" );

		pMDU->mvprint( 34, 18, "END EFFECTOR" );
		pMDU->mvprint( 31, 19, "RIGID CLOSE CAPTURE" );
		pMDU->mvprint( 31, 21, "DERIG  OPEN  EXTEND" );

		// static parts (lines)
		pMDU->Line( 180, 84, 490, 84 );
		pMDU->Line( 0, 266, 280, 266 );
		pMDU->Line( 310, 266, 500, 266 );

		// dynamic parts
		// TODO
		return;
	}

	void SMDisplays::OnPaint_SM_ANTENNA_PASS( vc::MDU* pMDU ) const
	{
		PrintCommonHeader( "  ANTENNA", pMDU );

		// static parts (labels)
		pMDU->mvprint( 0, 2, "KU BAND" );
		pMDU->mvprint( 0, 3, "SS" );
		
		pMDU->mvprint( 43, 2, "S BAND" );
		pMDU->mvprint( 43, 3, "SS" );

		pMDU->mvprint( 0, 5, "RDR RNG" );
		pMDU->mvprint( 4, 6, "AUTO  16" );
		pMDU->mvprint( 4, 7, "MIN   17" );
		
		pMDU->mvprint( 43, 5, "ANT ELEC" );
		
		pMDU->mvprint( 43, 8, "ANT" );
		pMDU->mvprint( 43, 9, "PM" );
		pMDU->mvprint( 43, 10, "FM" );
		
		pMDU->mvprint( 43, 12, "GPC PTG" );
		pMDU->mvprint( 43, 13, "ENA  11" );
		pMDU->mvprint( 43, 14, "INH  12" );
		pMDU->mvprint( 43, 15, "OVRD 13" );
		
		pMDU->mvprint( 0, 15, "KU" );
		pMDU->mvprint( 1, 16, "SELF TEST  7" );
		pMDU->mvprint( 1, 17, "O/I RESET  8" );
		
		pMDU->mvprint( 41, 17, "MODE" );
		
		pMDU->mvprint( 0, 19, "TDRS KU" );
		pMDU->mvprint( 1, 20, "A PRI  9" );
		pMDU->mvprint( 1, 21, "B PRI 10" );

		pMDU->mvprint( 41, 19, "TDRS S" );
		pMDU->mvprint( 42, 20, "A PRI 14" );
		pMDU->mvprint( 42, 21, "B PRI 15" );
		
		pMDU->mvprint( 42, 23, "STDN" );
		
		pMDU->mvprint( 26, 1, "+X" );
		pMDU->UpArrow( 27, 2 );
		pMDU->mvprint( 15, 3, "LL  90  UL  0  UR  -90  LR" );
		pMDU->mvprint( 11, 4, "90" );
		pMDU->mvprint( 12, 9, "0" );
		pMDU->mvprint( 10, 14, "-90" );
		pMDU->mvprint( 0, 10, "EL CMD" );
		pMDU->mvprint( 3, 11, "ACT" );
		pMDU->mvprint( 0, 12, "AZ CMD" );
		pMDU->mvprint( 3, 13, "ACT" );
		pMDU->mvprint( 18, 15, "TDRS STATE VECTORS" );
		pMDU->mvprint( 20, 16, "TGT SAT  IN  GPC" );
		pMDU->mvprint( 20, 17, "A B LON VIEW K S" );
		pMDU->mvprint( 18, 18, "1" );
		pMDU->mvprint( 18, 19, "2" );
		pMDU->mvprint( 18, 20, "3" );
		pMDU->mvprint( 18, 21, "4" );
		pMDU->mvprint( 18, 22, "5" );
		pMDU->mvprint( 18, 23, "6" );

		// static parts (lines)
		pMDU->Line( 0, 140, 130, 140 );
		pMDU->Line( 0, 168, 130, 168 );
		pMDU->Line( 0, 196, 130, 196 );
		
		pMDU->Line( 60, 140, 60, 196 );
		
		pMDU->Line( 130, 56, 420, 56 );
		pMDU->Line( 130, 210, 420, 210 );
		
		pMDU->Line( 130, 56, 130, 210 );
		pMDU->Line( 420, 56, 420, 210 );

		// dynamic parts
		// TODO
		return;
	}

	void SMDisplays::OnPaint_SM_PLBAYDOORS_PASS( vc::MDU* pMDU ) const
	{
		PrintCommonHeader( "  PL BAY DOORS", pMDU );

		// static parts (labels)
		pMDU->mvprint( 2, 2, "AC POWER   ON  1" );
		pMDU->mvprint( 12, 3, "OFF  2" );
		pMDU->mvprint( 2, 4, "AUTO MODE SEL  3" );
		pMDU->mvprint( 21, 3, "PBD SW-" );

		pMDU->mvprint( 31, 4, "MICRO-SW STAT" );
		pMDU->mvprint( 32, 5, "LATS  DOORS" );
		pMDU->mvprint( 16, 6, "MAN OP/CL AUTO  CCOO  CRRRO" );
		pMDU->mvprint( 1, 7, "CENTER LATCHES SEL" );
		pMDU->mvprint( 27, 7, "SEQ  ABAB   ABC" );
		pMDU->mvprint( 10, 8, "5- 8   4" );
		pMDU->mvprint( 10, 9, "9-12   5" );
		pMDU->mvprint( 10, 10, "1- 4   6" );
		pMDU->mvprint( 9, 11, "13-16   7" );
		pMDU->mvprint( 1, 12, "STBD" );
		pMDU->mvprint( 4, 13, "FWD LATCHES  8" );
		pMDU->mvprint( 4, 14, "AFT LATCHES  9" );
		pMDU->mvprint( 4, 15, "DOOR        10" );
		pMDU->mvprint( 1, 16, "PORT" );
		pMDU->mvprint( 4, 17, "FWD LATCHES 11" );
		pMDU->mvprint( 4, 18, "AFT LATCHES 12" );
		pMDU->mvprint( 4, 19, "DOOR        13" );
		
		pMDU->mvprint( 21, 21, "OPEN 15" );
		pMDU->mvprint( 2, 22, "PBD SW BYPASS 14   STOP 16" );
		pMDU->mvprint( 20, 23, "CLOSE 17" );

		// static parts (lines)
		pMDU->Line( 160, 70, 160, 280 );
		pMDU->Line( 190, 70, 190, 280 );
		pMDU->Line( 250, 70, 250, 280 );
		pMDU->Line( 300, 56, 300, 280 );

		// dynamic parts
		if (ReadCOMPOOL_IS( SCP_CSBB_POWER_ON_OFF_ITEM ) & 0x0001) pMDU->mvprint( 18, 2, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_POWER_ON_OFF_ITEM ) & 0x0002) pMDU->mvprint( 18, 3, "*" );

		if (ReadCOMPOOL_IS( SCP_CSBB_AUTO_MODE_ITEM ) == 1) pMDU->mvprint( 18, 4, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0008) pMDU->mvprint( 18, 8, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0010) pMDU->mvprint( 18, 9, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0020) pMDU->mvprint( 18, 10, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0040) pMDU->mvprint( 18, 11, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0080) pMDU->mvprint( 18, 13, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0100) pMDU->mvprint( 18, 14, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0200) pMDU->mvprint( 18, 15, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0400) pMDU->mvprint( 18, 17, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0800) pMDU->mvprint( 18, 18, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x1000) pMDU->mvprint( 18, 19, "*" );

		if (ReadCOMPOOL_IS( SCP_CSBB_SWITCH_BYPASS_ITEM ) == 1) pMDU->mvprint( 18, 22, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_PBD_OPEN_ITEM ) == 1) pMDU->mvprint( 28, 21, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_PBD_STOP_ITEM ) == 1) pMDU->mvprint( 28, 22, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_PBD_CLOSE_ITEM ) == 1) pMDU->mvprint( 28, 23, "*" );

		char swtxt[8];
		memset( swtxt, 0, 8 );
		ReadCOMPOOL_C( SCP_CSBB_PBD_SWITCH_IND_TEXT, swtxt, 4 );
		pMDU->mvprint( 28, 3, swtxt );

		memset( swtxt, 0, 8 );
		ReadCOMPOOL_C( SCP_CSBB_C_LCH_5_8_TEXT, swtxt, 2 );
		pMDU->mvprint( 21, 8, swtxt );
		memset( swtxt, 0, 8 );
		ReadCOMPOOL_C( SCP_CSBB_C_LCH_9_12_TEXT, swtxt, 2 );
		pMDU->mvprint( 21, 9, swtxt );
		memset( swtxt, 0, 8 );
		ReadCOMPOOL_C( SCP_CSBB_C_LCH_1_4_TEXT, swtxt, 2 );
		pMDU->mvprint( 21, 10, swtxt );
		memset( swtxt, 0, 8 );
		ReadCOMPOOL_C( SCP_CSBB_C_LCH_13_16_TEXT, swtxt, 2 );
		pMDU->mvprint( 21, 11, swtxt );

		memset( swtxt, 0, 8 );
		ReadCOMPOOL_C( SCP_CSBB_R_FWD_BHD_TEXT, swtxt, 2 );
		pMDU->mvprint( 21, 13, swtxt );
		memset( swtxt, 0, 8 );
		ReadCOMPOOL_C( SCP_CSBB_R_AFT_BHD_TEXT, swtxt, 2 );
		pMDU->mvprint( 21, 14, swtxt );
		memset( swtxt, 0, 8 );
		ReadCOMPOOL_C( SCP_CSBB_R_DOOR_TEXT, swtxt, 3 );
		pMDU->mvprint( 20, 15, swtxt );

		memset( swtxt, 0, 8 );
		ReadCOMPOOL_C( SCP_CSBB_L_FWD_BHD_TEXT, swtxt, 2 );
		pMDU->mvprint( 21, 17, swtxt );
		memset( swtxt, 0, 8 );
		ReadCOMPOOL_C( SCP_CSBB_L_AFT_BHD_TEXT, swtxt, 2 );
		pMDU->mvprint( 21, 18, swtxt );
		memset( swtxt, 0, 8 );
		ReadCOMPOOL_C( SCP_CSBB_L_DOOR_TEXT, swtxt, 3 );
		pMDU->mvprint( 20, 19, swtxt );


		unsigned short CSBB_OPEN_FAIL_INDICATOR = ReadCOMPOOL_IS( SCP_CSBB_OPEN_FAIL_INDICATOR );
		unsigned short CSBB_CLOSE_FAIL_INDICATOR = ReadCOMPOOL_IS( SCP_CSBB_CLOSE_FAIL_INDICATOR );
		if (((CSBB_OPEN_FAIL_INDICATOR | CSBB_CLOSE_FAIL_INDICATOR) & 0x0001) != 0) pMDU->DownArrow( 28, 8, DEUATT_OVERBRIGHT );
		if (((CSBB_OPEN_FAIL_INDICATOR | CSBB_CLOSE_FAIL_INDICATOR) & 0x0002) != 0) pMDU->DownArrow( 28, 9, DEUATT_OVERBRIGHT );
		if (((CSBB_OPEN_FAIL_INDICATOR | CSBB_CLOSE_FAIL_INDICATOR) & 0x0004) != 0) pMDU->DownArrow( 28, 10, DEUATT_OVERBRIGHT );
		if (((CSBB_OPEN_FAIL_INDICATOR | CSBB_CLOSE_FAIL_INDICATOR) & 0x0008) != 0) pMDU->DownArrow( 28, 11, DEUATT_OVERBRIGHT );

		if (((CSBB_OPEN_FAIL_INDICATOR | CSBB_CLOSE_FAIL_INDICATOR) & 0x0010) != 0) pMDU->DownArrow( 28, 13, DEUATT_OVERBRIGHT );
		if (((CSBB_OPEN_FAIL_INDICATOR | CSBB_CLOSE_FAIL_INDICATOR) & 0x0020) != 0) pMDU->DownArrow( 28, 14, DEUATT_OVERBRIGHT );
		if (((CSBB_OPEN_FAIL_INDICATOR | CSBB_CLOSE_FAIL_INDICATOR) & 0x0040) != 0) pMDU->DownArrow( 28, 15, DEUATT_OVERBRIGHT );

		if (((CSBB_OPEN_FAIL_INDICATOR | CSBB_CLOSE_FAIL_INDICATOR) & 0x0080) != 0) pMDU->DownArrow( 28, 17, DEUATT_OVERBRIGHT );
		if (((CSBB_OPEN_FAIL_INDICATOR | CSBB_CLOSE_FAIL_INDICATOR) & 0x0100) != 0) pMDU->DownArrow( 28, 18, DEUATT_OVERBRIGHT );
		if (((CSBB_OPEN_FAIL_INDICATOR | CSBB_CLOSE_FAIL_INDICATOR) & 0x0200) != 0) pMDU->DownArrow( 28, 19, DEUATT_OVERBRIGHT );


		unsigned short PF1_IOM3_CH0 = ReadCOMPOOL_IS( SCP_PF1_IOM3_CH0_DATA );
		unsigned short PF1_IOM6_CH0 = ReadCOMPOOL_IS( SCP_PF1_IOM6_CH0_DATA );
		unsigned short PF1_IOM9_CH0 = ReadCOMPOOL_IS( SCP_PF1_IOM9_CH0_DATA );
		unsigned short PF2_IOM3_CH0 = ReadCOMPOOL_IS( SCP_PF2_IOM3_CH0_DATA );
		unsigned short PF2_IOM6_CH0 = ReadCOMPOOL_IS( SCP_PF2_IOM6_CH0_DATA );
		unsigned short PF2_IOM9_CH0 = ReadCOMPOOL_IS( SCP_PF2_IOM9_CH0_DATA );

		bool PLB_RIGHT_FWD_BHD_READY_FOR_LCH_1 = ((PF1_IOM3_CH0 & 0x0001) != 0);
		bool PLB_RIGHT_AFT_BHD_READY_FOR_LCH_1 = ((PF1_IOM3_CH0 & 0x0002) != 0);
		bool PLB_RIGHT_FWD_BHD_LATCH_REL_1 = ((PF1_IOM3_CH0 & 0x0004) != 0);
		bool PLB_RIGHT_FWD_BHD_LATCH_LCH_1 = ((PF1_IOM3_CH0 & 0x0008) != 0);
		bool PLB_RIGHT_AFT_BHD_LATCH_REL_2 = ((PF1_IOM3_CH0 & 0x0010) != 0);
		bool PLB_RIGHT_AFT_BHD_LATCH_LCH_2 = ((PF1_IOM3_CH0 & 0x0020) != 0);
		bool PLB_RIGHT_OPEN_1 = ((PF1_IOM3_CH0 & 0x0040) != 0);
		bool PLB_RIGHT_CLOSE_1 = ((PF1_IOM3_CH0 & 0x0400) != 0);

		bool PLB_LEFT_FWD_BHD_READY_FOR_LCH_1 = ((PF1_IOM6_CH0 & 0x0001) != 0);
		bool PLB_LEFT_AFT_BHD_READY_FOR_LCH_1 = ((PF1_IOM6_CH0 & 0x0002) != 0);
		bool PLB_LEFT_FWD_BHD_LATCH_REL_1 = ((PF1_IOM6_CH0 & 0x0004) != 0);
		bool PLB_LEFT_FWD_BHD_LATCH_LCH_1 = ((PF1_IOM6_CH0 & 0x0008) != 0);
		bool PLB_LEFT_AFT_BHD_LATCH_REL_1 = ((PF1_IOM6_CH0 & 0x0010) != 0);
		bool PLB_LEFT_AFT_BHD_LATCH_LCH_1 = ((PF1_IOM6_CH0 & 0x0020) != 0);
		bool PLB_LEFT_OPEN_2 = ((PF1_IOM6_CH0 & 0x0040) != 0);
		bool PLB_LEFT_CLOSE_2 = ((PF1_IOM6_CH0 & 0x0800) != 0);

		bool PLB_LEFT_FWD_BHD_READY_FOR_LCH_2 = ((PF1_IOM9_CH0 & 0x0001) != 0);
		bool PLB_LEFT_AFT_BHD_READY_FOR_LCH_2 = ((PF1_IOM9_CH0 & 0x0002) != 0);
		bool PLB_CENTERLINE_LCH_1_4_REL_1 = ((PF1_IOM9_CH0 & 0x0004) != 0);
		bool PLB_CENTERLINE_LCH_1_4_LCH_1 = ((PF1_IOM9_CH0 & 0x0008) != 0);
		bool PLB_CENTERLINE_LCH_5_8_REL_1 = ((PF1_IOM9_CH0 & 0x0010) != 0);
		bool PLB_CENTERLINE_LCH_5_8_LCH_1 = ((PF1_IOM9_CH0 & 0x0020) != 0);
		bool PLB_CENTERLINE_LCH_9_12_LCH_1 = ((PF1_IOM9_CH0 & 0x0040) != 0);
		bool PLB_CENTERLINE_LCH_9_12_REL_1 = ((PF1_IOM9_CH0 & 0x0080) != 0);
		bool PLB_CENTERLINE_LCH_13_16_LCH_2 = ((PF1_IOM9_CH0 & 0x0100) != 0);
		bool PLB_CENTERLINE_LCH_13_16_REL_2 = ((PF1_IOM9_CH0 & 0x0200) != 0);

		bool PLB_RIGHT_FWD_BHD_READY_FOR_LCH_2 = ((PF2_IOM3_CH0 & 0x0001) != 0);
		bool PLB_RIGHT_AFT_BHD_READY_FOR_LCH_2 = ((PF2_IOM3_CH0 & 0x0002) != 0);
		bool PLB_RIGHT_FWD_BHD_LATCH_REL_2 = ((PF2_IOM3_CH0 & 0x0004) != 0);
		bool PLB_RIGHT_FWD_BHD_LATCH_LCH_2 = ((PF2_IOM3_CH0 & 0x0008) != 0);
		bool PLB_RIGHT_AFT_BHD_LATCH_REL_1 = ((PF2_IOM3_CH0 & 0x0010) != 0);
		bool PLB_RIGHT_AFT_BHD_LATCH_LCH_1 = ((PF2_IOM3_CH0 & 0x0020) != 0);
		bool PLB_RIGHT_OPEN_2 = ((PF2_IOM3_CH0 & 0x0040) != 0);
		bool PLB_RIGHT_CLOSE_2 = ((PF2_IOM3_CH0 & 0x0400) != 0);

		bool PLB_LEFT_FWD_BHD_READY_FOR_LCH_3 = ((PF2_IOM6_CH0 & 0x0001) != 0);
		bool PLB_LEFT_AFT_BHD_READY_FOR_LCH_3 = ((PF2_IOM6_CH0 & 0x0002) != 0);
		bool PLB_LEFT_FWD_BHD_LATCH_REL_2 = ((PF2_IOM6_CH0 & 0x0004) != 0);
		bool PLB_LEFT_FWD_BHD_LATCH_LCH_2 = ((PF2_IOM6_CH0 & 0x0008) != 0);
		bool PLB_LEFT_AFT_BHD_LATCH_REL_2 = ((PF2_IOM6_CH0 & 0x0010) != 0);
		bool PLB_LEFT_AFT_BHD_LATCH_LCH_2 = ((PF2_IOM6_CH0 & 0x0020) != 0);
		bool PLB_LEFT_OPEN_1 = ((PF2_IOM6_CH0 & 0x0040) != 0);
		bool PLB_LEFT_CLOSE_1 = ((PF2_IOM6_CH0 & 0x0800) != 0);

		bool PLB_RIGHT_FWD_BHD_READY_FOR_LCH_3 = ((PF2_IOM9_CH0 & 0x0001) != 0);
		bool PLB_RIGHT_AFT_BHD_READY_FOR_LCH_3 = ((PF2_IOM9_CH0 & 0x0002) != 0);
		bool PLB_CENTERLINE_LCH_1_4_REL_2 = ((PF2_IOM9_CH0 & 0x0004) != 0);
		bool PLB_CENTERLINE_LCH_1_4_LCH_2 = ((PF2_IOM9_CH0 & 0x0008) != 0);
		bool PLB_CENTERLINE_LCH_5_8_REL_2 = ((PF2_IOM9_CH0 & 0x0010) != 0);
		bool PLB_CENTERLINE_LCH_5_8_LCH_2 = ((PF2_IOM9_CH0 & 0x0020) != 0);
		bool PLB_CENTERLINE_LCH_9_12_LCH_2 = ((PF2_IOM9_CH0 & 0x0040) != 0);
		bool PLB_CENTERLINE_LCH_9_12_REL_2 = ((PF2_IOM9_CH0 & 0x0080) != 0);
		bool PLB_CENTERLINE_LCH_13_16_LCH_1 = ((PF2_IOM9_CH0 & 0x0100) != 0);
		bool PLB_CENTERLINE_LCH_13_16_REL_1 = ((PF2_IOM9_CH0 & 0x0200) != 0);


		pMDU->mvprint( 32, 8, PLB_CENTERLINE_LCH_5_8_LCH_1 ? "1" : "0" );
		pMDU->mvprint( 33, 8, PLB_CENTERLINE_LCH_5_8_LCH_2 ? "1" : "0" );
		pMDU->mvprint( 34, 8, PLB_CENTERLINE_LCH_5_8_REL_1 ? "1" : "0" );
		pMDU->mvprint( 35, 8, PLB_CENTERLINE_LCH_5_8_REL_2 ? "1" : "0" );
		pMDU->mvprint( 32, 9, PLB_CENTERLINE_LCH_9_12_LCH_1 ? "1" : "0" );
		pMDU->mvprint( 33, 9, PLB_CENTERLINE_LCH_9_12_LCH_2 ? "1" : "0" );
		pMDU->mvprint( 34, 9, PLB_CENTERLINE_LCH_9_12_REL_1 ? "1" : "0" );
		pMDU->mvprint( 35, 9, PLB_CENTERLINE_LCH_9_12_REL_2 ? "1" : "0" );
		pMDU->mvprint( 32, 10, PLB_CENTERLINE_LCH_1_4_LCH_1 ? "1" : "0" );
		pMDU->mvprint( 33, 10, PLB_CENTERLINE_LCH_1_4_LCH_2 ? "1" : "0" );
		pMDU->mvprint( 34, 10, PLB_CENTERLINE_LCH_1_4_REL_1 ? "1" : "0" );
		pMDU->mvprint( 35, 10, PLB_CENTERLINE_LCH_1_4_REL_2 ? "1" : "0" );
		pMDU->mvprint( 32, 11, PLB_CENTERLINE_LCH_13_16_LCH_1 ? "1" : "0" );
		pMDU->mvprint( 33, 11, PLB_CENTERLINE_LCH_13_16_LCH_2 ? "1" : "0" );
		pMDU->mvprint( 34, 11, PLB_CENTERLINE_LCH_13_16_REL_1 ? "1" : "0" );
		pMDU->mvprint( 35, 11, PLB_CENTERLINE_LCH_13_16_REL_2 ? "1" : "0" );

		pMDU->mvprint( 32, 13, PLB_RIGHT_FWD_BHD_LATCH_LCH_1 ? "1" : "0" );
		pMDU->mvprint( 33, 13, PLB_RIGHT_FWD_BHD_LATCH_LCH_2 ? "1" : "0" );
		pMDU->mvprint( 34, 13, PLB_RIGHT_FWD_BHD_LATCH_REL_1 ? "1" : "0" );
		pMDU->mvprint( 35, 13, PLB_RIGHT_FWD_BHD_LATCH_REL_2 ? "1" : "0" );
		pMDU->mvprint( 38, 13, PLB_RIGHT_CLOSE_1 ? "1" : "0" );
		pMDU->mvprint( 39, 13, PLB_RIGHT_FWD_BHD_READY_FOR_LCH_1 ? "1" : "0" );
		pMDU->mvprint( 40, 13, PLB_RIGHT_FWD_BHD_READY_FOR_LCH_2 ? "1" : "0" );
		pMDU->mvprint( 41, 13, PLB_RIGHT_FWD_BHD_READY_FOR_LCH_3 ? "1" : "0" );
		pMDU->mvprint( 42, 13, PLB_RIGHT_OPEN_1 ? "1" : "0" );

		pMDU->mvprint( 32, 14, PLB_RIGHT_AFT_BHD_LATCH_LCH_1 ? "1" : "0" );
		pMDU->mvprint( 33, 14, PLB_RIGHT_AFT_BHD_LATCH_LCH_2 ? "1" : "0" );
		pMDU->mvprint( 34, 14, PLB_RIGHT_AFT_BHD_LATCH_REL_1 ? "1" : "0" );
		pMDU->mvprint( 35, 14, PLB_RIGHT_AFT_BHD_LATCH_REL_2 ? "1" : "0" );
		pMDU->mvprint( 38, 14, PLB_RIGHT_CLOSE_2 ? "1" : "0" );
		pMDU->mvprint( 39, 14, PLB_RIGHT_AFT_BHD_READY_FOR_LCH_1 ? "1" : "0" );
		pMDU->mvprint( 40, 14, PLB_RIGHT_AFT_BHD_READY_FOR_LCH_2 ? "1" : "0" );
		pMDU->mvprint( 41, 14, PLB_RIGHT_AFT_BHD_READY_FOR_LCH_3 ? "1" : "0" );
		pMDU->mvprint( 42, 14, PLB_RIGHT_OPEN_2 ? "1" : "0" );

		pMDU->mvprint( 32, 17, PLB_LEFT_FWD_BHD_LATCH_LCH_1 ? "1" : "0" );
		pMDU->mvprint( 33, 17, PLB_LEFT_FWD_BHD_LATCH_LCH_2 ? "1" : "0" );
		pMDU->mvprint( 34, 17, PLB_LEFT_FWD_BHD_LATCH_REL_1 ? "1" : "0" );
		pMDU->mvprint( 35, 17, PLB_LEFT_FWD_BHD_LATCH_REL_2 ? "1" : "0" );
		pMDU->mvprint( 38, 17, PLB_LEFT_CLOSE_1 ? "1" : "0" );
		pMDU->mvprint( 39, 17, PLB_LEFT_FWD_BHD_READY_FOR_LCH_1 ? "1" : "0" );
		pMDU->mvprint( 40, 17, PLB_LEFT_FWD_BHD_READY_FOR_LCH_2 ? "1" : "0" );
		pMDU->mvprint( 41, 17, PLB_LEFT_FWD_BHD_READY_FOR_LCH_3 ? "1" : "0" );
		pMDU->mvprint( 42, 17, PLB_LEFT_OPEN_1 ? "1" : "0" );

		pMDU->mvprint( 32, 18, PLB_LEFT_AFT_BHD_LATCH_LCH_1 ? "1" : "0" );
		pMDU->mvprint( 33, 18, PLB_LEFT_AFT_BHD_LATCH_LCH_2 ? "1" : "0" );
		pMDU->mvprint( 34, 18, PLB_LEFT_AFT_BHD_LATCH_REL_1 ? "1" : "0" );
		pMDU->mvprint( 35, 18, PLB_LEFT_AFT_BHD_LATCH_REL_2 ? "1" : "0" );
		pMDU->mvprint( 38, 18, PLB_LEFT_CLOSE_2 ? "1" : "0" );
		pMDU->mvprint( 39, 18, PLB_LEFT_AFT_BHD_READY_FOR_LCH_1 ? "1" : "0" );
		pMDU->mvprint( 40, 18, PLB_LEFT_AFT_BHD_READY_FOR_LCH_2 ? "1" : "0" );
		pMDU->mvprint( 41, 18, PLB_LEFT_AFT_BHD_READY_FOR_LCH_3 ? "1" : "0" );
		pMDU->mvprint( 42, 18, PLB_LEFT_OPEN_2 ? "1" : "0" );
		return;
	}
}

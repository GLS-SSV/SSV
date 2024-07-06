#include "SMDisplays.h"
#include "../CRT_Interface.h"


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
				return ItemInput_SPEC94( item, Data );
			case dps::MODE_UNDEFINED:
				switch (GetMajorMode())
				{
					case 201:
						return ItemInput_ANTENNA( item, Data );
					case 202:
						return ItemInput_PLBAYDOORS( item, Data );
				}
		}
		return false;
	}

	bool SMDisplays::ItemInput_SPEC94( int item, const char* Data )
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

	bool SMDisplays::ItemInput_ANTENNA( int item, const char* Data )
	{
		// TODO
		return false;
	}

	bool SMDisplays::ItemInput_PLBAYDOORS( int item, const char* Data )
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

	void SMDisplays::Paint( CRT_Interface* crt, unsigned short page ) const
	{
		switch (page)
		{
			case 94:// PDRS CONTROL
				OnPaint_SPEC94( crt );
				break;
			case 95:// PDRS OVERRIDE
				OnPaint_SPEC95( crt );
				break;
			case 96:// PDRS FAULTS
				OnPaint_DISP96( crt );
				break;
			case 97:// PL RETENTION
				OnPaint_DISP97( crt );
				break;
			case 169:// PDRS STATUS
				OnPaint_DISP169( crt );
				break;
			////
			case 201:// ANTENNA
				OnPaint_ANTENNA( crt );
				break;
			case 202:// PL BAY DOORS
				OnPaint_PLBAYDOORS( crt );
				break;
		}
		return;
	}

	void SMDisplays::PaintBackground( CRT_Interface* crt, unsigned short page ) const
	{
		switch (page)
		{
			case 94:// PDRS CONTROL
				BackgroundData_SPEC94( crt );
				break;
			case 95:// PDRS OVERRIDE
				BackgroundData_SPEC95( crt );
				break;
			case 96:// PDRS FAULTS
				BackgroundData_DISP96( crt );
				break;
			case 97:// PL RETENTION
				BackgroundData_DISP97( crt );
				break;
			case 169:// PDRS STATUS
				BackgroundData_DISP169( crt );
				break;
			////
			case 201:// ANTENNA
				BackgroundData_ANTENNA( crt );
				break;
			case 202:// PL BAY DOORS
				BackgroundData_PLBAYDOORS( crt );
				break;
		}
		return;
	}

	void SMDisplays::OnPaint_SPEC94( CRT_Interface* crt ) const
	{
		crt->TextGrid( 12, (RMS_SEL == 1) ? 3 : 4, "*" );

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
			crt->TextGrid( 1, 18, "PORT" );
			// MPM
			crt->TextGrid( 7, 19, (msw_oa2_5_0 & 0x0001) ? "1" : "0" );
			crt->TextGrid( 9, 19, (msw_oa2_7_2 & 0x0002) ? "1" : "0" );
			crt->TextGrid( 11, 19, (msw_oa2_12_1 & 0x0001) ? "1" : "0" );
			crt->TextGrid( 13, 19, (msw_oa2_1_2 & 0x0002) ? "1" : "0" );
			// LAT/REL/RDY
			// AFT
			crt->TextGrid( 6, 22, (msw_oa3_5_0 & 0x0001) ? "1" : "0" );
			crt->TextGrid( 8, 22, (msw_of1_6_2 & 0x0001) ? "1" : "0" );
			crt->TextGrid( 10, 22, (msw_oa3_10_2 & 0x0001) ? "1" : "0" );
			crt->TextGrid( 12, 22, (msw_of1_12_0 & 0x0001) ? "1" : "0" );
			crt->TextGrid( 14, 22, (msw_oa3_1_2 & 0x0002) ? "1" : "0" );
			crt->TextGrid( 16, 22, (msw_of1_4_2 & 0x0002) ? "1" : "0" );
			// MID
			crt->TextGrid( 6, 23, (msw_of4_4_1 & 0x0001) ? "1" : "0" );
			crt->TextGrid( 8, 23, (msw_oa1_10_1 & 0x0001) ? "1" : "0" );
			crt->TextGrid( 10, 23, (msw_of4_5_2 & 0x0001) ? "1" : "0" );
			crt->TextGrid( 12, 23, (msw_oa1_12_0 & 0x0001) ? "1" : "0" );
			crt->TextGrid( 14, 23, (msw_of4_2_1 & 0x0002) ? "1" : "0" );
			crt->TextGrid( 16, 23, (msw_oa1_7_1 & 0x0001) ? "1" : "0" );
			// FWD
			crt->TextGrid( 6, 24, (msw_oa2_5_2 & 0x0001) ? "1" : "0" );
			crt->TextGrid( 8, 24, (msw_oa2_12_2 & 0x0001) ? "1" : "0" );
			crt->TextGrid( 10, 24, (msw_oa2_1_2 & 0x0001) ? "1" : "0" );
			crt->TextGrid( 12, 24, (msw_oa2_7_2 & 0x0001) ? "1" : "0" );
			crt->TextGrid( 14, 24, (msw_oa2_10_2 & 0x0001) ? "1" : "0" );
			crt->TextGrid( 16, 24, (msw_oa2_12_0 & 0x0001) ? "1" : "0" );
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
			crt->TextGrid( 1, 18, "STBD" );
			// MPM
			crt->TextGrid( 7, 19, (msw_oa2_5_0 & 0x0002) ? "1" : "0" );
			crt->TextGrid( 9, 19, (msw_oa2_7_2 & 0x0008) ? "1" : "0" );
			crt->TextGrid( 11, 19, (msw_oa2_12_1 & 0x0002) ? "1" : "0" );
			crt->TextGrid( 13, 19, (msw_oa2_1_2 & 0x0008) ? "1" : "0" );
			// LAT/REL/RDY
			// AFT
			crt->TextGrid( 6, 22, (msw_oa3_5_0 & 0x0002) ? "1" : "0" );
			crt->TextGrid( 8, 22, (msw_of1_6_2 & 0x0002) ? "1" : "0" );
			crt->TextGrid( 10, 22, (msw_oa3_10_2 & 0x0002) ? "1" : "0" );
			crt->TextGrid( 12, 22, (msw_of1_12_0 & 0x0002) ? "1" : "0" );
			crt->TextGrid( 14, 2, (msw_oa3_1_2 & 0x0004) ? "1" : "0" );
			crt->TextGrid( 16, 221, (msw_of1_4_2 & 0x0004) ? "1" : "0" );
			// MID
			crt->TextGrid( 6, 23, (msw_of4_4_1 & 0x0002) ? "1" : "0" );
			crt->TextGrid( 8, 23, (msw_oa1_10_1 & 0x0002) ? "1" : "0" );
			crt->TextGrid( 10, 23, (msw_of4_5_2 & 0x0002) ? "1" : "0" );
			crt->TextGrid( 12, 23, (msw_oa1_12_0 & 0x0002) ? "1" : "0" );
			crt->TextGrid( 14, 23, (msw_of4_2_1 & 0x0004) ? "1" : "0" );
			crt->TextGrid( 16, 23, (msw_oa1_7_1 & 0x0002) ? "1" : "0" );
			// FWD
			crt->TextGrid( 6, 24, (msw_oa2_5_2 & 0x0002) ? "1" : "0" );
			crt->TextGrid( 8, 24, (msw_oa2_12_2 & 0x0002) ? "1" : "0" );
			crt->TextGrid( 10, 24, (msw_oa2_1_2 & 0x0004) ? "1" : "0" );
			crt->TextGrid( 12, 24, (msw_oa2_7_2 & 0x0004) ? "1" : "0" );
			crt->TextGrid( 14, 24, (msw_oa2_10_2 & 0x0002) ? "1" : "0" );
			crt->TextGrid( 16, 24, (msw_oa2_12_0 & 0x0002) ? "1" : "0" );
		}

		// TODO
		return;
	}

	void SMDisplays::OnPaint_SPEC95( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::OnPaint_DISP96( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::OnPaint_DISP97( CRT_Interface* crt ) const
	{
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
			crt->TextGrid( 18, 9, (msw_oa3_12_0 & 0x0004) ? "1" : "0" );
			crt->TextGrid( 18, 10, (msw_oa3_12_0 & 0x0002) ? "1" : "0" );
			crt->TextGrid( 21, 10, (msw_oa3_12_0 & 0x0001) ? "1" : "0" );
			// 1B
			crt->TextGrid( 19, 9, (msw_of2_14_0 & 0x0020) ? "1" : "0" );
			crt->TextGrid( 19, 10, (msw_of2_14_0 & 0x0010) ? "1" : "0" );
			crt->TextGrid( 22, 10, (msw_of2_14_0 & 0x0008) ? "1" : "0" );
			// 2A
			crt->TextGrid( 24, 9, (msw_oa3_12_0 & 0x0100) ? "1" : "0" );
			crt->TextGrid( 24, 10, (msw_oa3_12_0 & 0x0080) ? "1" : "0" );
			crt->TextGrid( 27, 10, (msw_oa3_12_0 & 0x0040) ? "1" : "0" );
			// 2B
			crt->TextGrid( 25, 9, (msw_of2_14_0 & 0x4000) ? "1" : "0" );
			crt->TextGrid( 25, 10, (msw_of2_14_0 & 0x2000) ? "1" : "0" );
			crt->TextGrid( 28, 10, (msw_of2_14_0 & 0x1000) ? "1" : "0" );
			// 3A
			crt->TextGrid( 30, 9, (msw_oa3_12_1 & 0x0004) ? "1" : "0" );
			crt->TextGrid( 30, 10, (msw_oa3_12_1 & 0x0002) ? "1" : "0" );
			crt->TextGrid( 33, 10, (msw_oa3_12_1 & 0x0001) ? "1" : "0" );
			// 3B
			crt->TextGrid( 31, 9, (msw_of2_14_1 & 0x0020) ? "1" : "0" );
			crt->TextGrid( 31, 10, (msw_of2_14_1 & 0x0010) ? "1" : "0" );
			crt->TextGrid( 34, 10, (msw_of2_14_1 & 0x0008) ? "1" : "0" );
			// 4A
			crt->TextGrid( 36, 9, (msw_oa3_12_1 & 0x0020) ? "1" : "0" );
			crt->TextGrid( 36, 10, (msw_oa3_12_1 & 0x0010) ? "1" : "0" );
			crt->TextGrid( 39, 10, (msw_oa3_12_1 & 0x0008) ? "1" : "0" );
			// 4B
			crt->TextGrid( 37, 9, (msw_of2_14_1 & 0x0800) ? "1" : "0" );
			crt->TextGrid( 37, 10, (msw_of2_14_1 & 0x0400) ? "1" : "0" );
			crt->TextGrid( 40, 10, (msw_of2_14_1 & 0x0200) ? "1" : "0" );
			// 5A
			crt->TextGrid( 42, 9, (msw_oa3_12_1 & 0x0100) ? "1" : "0" );
			crt->TextGrid( 42, 10, (msw_oa3_12_1 & 0x0080) ? "1" : "0" );
			crt->TextGrid( 45, 10, (msw_oa3_12_1 & 0x0040) ? "1" : "0" );
			// 5B
			crt->TextGrid( 43, 9, (msw_of2_14_2 & 0x0020) ? "1" : "0" );
			crt->TextGrid( 43, 10, (msw_of2_14_2 & 0x0010) ? "1" : "0" );
			crt->TextGrid( 46, 10, (msw_of2_14_2 & 0x0008) ? "1" : "0" );
		}

		// PL 2
		if ((msw_of4_13_1 & 0x0001) || (msw_of4_10_0 & 0x0001))// PL2 or MON
		{
			// 1A
			crt->TextGrid( 18, 13, (msw_oa3_12_0 & 0x0020) ? "1" : "0" );
			crt->TextGrid( 18, 14, (msw_oa3_1_2 & 0x0001) ? "1" : "0" );
			crt->TextGrid( 21, 14, (msw_oa3_12_0 & 0x0008) ? "1" : "0" );
			// 1B
			crt->TextGrid( 19, 13, (msw_of2_14_0 & 0x0100) ? "1" : "0" );
			crt->TextGrid( 19, 14, (msw_of2_12_2 & 0x0001) ? "1" : "0" );
			crt->TextGrid( 22, 14, (msw_of2_14_0 & 0x0040) ? "1" : "0" );
			// 2A
			crt->TextGrid( 24, 13, (msw_of4_15_0 & 0x0004) ? "1" : "0" );
			crt->TextGrid( 24, 14, (msw_of4_7_2 & 0x0001) ? "1" : "0" );
			crt->TextGrid( 27, 14, (msw_of4_15_0 & 0x0001) ? "1" : "0" );
			// 2B
			crt->TextGrid( 25, 13, (msw_of1_14_0 & 0x0020) ? "1" : "0" );
			crt->TextGrid( 25, 14, (msw_of1_4_1 & 0x0002) ? "1" : "0" );
			crt->TextGrid( 28, 14, (msw_of1_14_0 & 0x0008) ? "1" : "0" );
			// 3A
			crt->TextGrid( 30, 13, (msw_of4_15_0 & 0x0020) ? "1" : "0" );
			crt->TextGrid( 30, 14, (msw_of4_15_0 & 0x0010) ? "1" : "0" );
			crt->TextGrid( 33, 14, (msw_of4_15_0 & 0x0008) ? "1" : "0" );
			// 3B
			crt->TextGrid( 31, 13, (msw_of1_14_0 & 0x0800) ? "1" : "0" );
			crt->TextGrid( 31, 14, (msw_of1_14_0 & 0x0400) ? "1" : "0" );
			crt->TextGrid( 34, 14, (msw_of1_14_0 & 0x0200) ? "1" : "0" );
			// 4A
			crt->TextGrid( 36, 13, (msw_of4_15_0 & 0x0100) ? "1" : "0" );
			crt->TextGrid( 36, 14, (msw_of4_15_0 & 0x0080) ? "1" : "0" );
			crt->TextGrid( 39, 14, (msw_of4_15_0 & 0x0040) ? "1" : "0" );
			// 4B
			crt->TextGrid( 37, 13, (msw_of1_14_1 & 0x0004) ? "1" : "0" );
			crt->TextGrid( 37, 14, (msw_of1_14_1 & 0x0002) ? "1" : "0" );
			crt->TextGrid( 40, 14, (msw_of1_14_1 & 0x0001) ? "1" : "0" );
			// 5A
			crt->TextGrid( 42, 13, (msw_of2_14_1 & 0x4000) ? "1" : "0" );
			crt->TextGrid( 42, 14, (msw_of2_14_1 & 0x2000) ? "1" : "0" );
			crt->TextGrid( 45, 14, (msw_of2_14_1 & 0x1000) ? "1" : "0" );
			// 5B
			crt->TextGrid( 43, 13, (msw_of1_14_1 & 0x0100) ? "1" : "0" );
			crt->TextGrid( 43, 14, (msw_of1_14_1 & 0x0080) ? "1" : "0" );
			crt->TextGrid( 46, 14, (msw_of1_14_1 & 0x0040) ? "1" : "0" );
		}

		// PL 3
		if ((msw_of4_13_0 & 0x0001) || (msw_of4_10_0 & 0x0001))// PL3 or MON
		{
			// 1A
			crt->TextGrid( 18, 17, (msw_of2_14_0 & 0x0004) ? "1" : "0" );
			crt->TextGrid( 18, 18, (msw_of2_14_0 & 0x0002) ? "1" : "0" );
			crt->TextGrid( 21, 18, (msw_of2_14_0 & 0x0001) ? "1" : "0" );
			// 1B
			crt->TextGrid( 19, 17, (msw_of1_14_0 & 0x0004) ? "1" : "0" );
			crt->TextGrid( 19, 18, (msw_of1_14_0 & 0x0002) ? "1" : "0" );
			crt->TextGrid( 22, 18, (msw_of1_14_0 & 0x0001) ? "1" : "0" );
			// 2A
			crt->TextGrid( 24, 17, (msw_of2_14_0 & 0x0800) ? "1" : "0" );
			crt->TextGrid( 24, 18, (msw_of2_14_0 & 0x0400) ? "1" : "0" );
			crt->TextGrid( 27, 18, (msw_of2_14_0 & 0x0200) ? "1" : "0" );
			// 2B
			crt->TextGrid( 25, 17, (msw_of1_14_0 & 0x0100) ? "1" : "0" );
			crt->TextGrid( 25, 18, (msw_of1_14_0 & 0x0080) ? "1" : "0" );
			crt->TextGrid( 28, 18, (msw_of1_14_0 & 0x0040) ? "1" : "0" );
			// 3A
			crt->TextGrid( 30, 17, (msw_of2_14_1 & 0x0004) ? "1" : "0" );
			crt->TextGrid( 30, 18, (msw_of2_12_1 & 0x0004) ? "1" : "0" );
			crt->TextGrid( 33, 18, (msw_of2_14_1 & 0x0001) ? "1" : "0" );
			// 3B
			crt->TextGrid( 31, 17, (msw_of1_14_0 & 0x4000) ? "1" : "0" );
			crt->TextGrid( 31, 18, (msw_of1_14_0 & 0x2000) ? "1" : "0" );
			crt->TextGrid( 34, 18, (msw_of1_14_0 & 0x1000) ? "1" : "0" );
			// 4A
			crt->TextGrid( 36, 17, (msw_of2_14_1 & 0x0100) ? "1" : "0" );
			crt->TextGrid( 36, 18, (msw_of2_6_2 & 0x0001) ? "1" : "0" );
			crt->TextGrid( 39, 18, (msw_of2_4_1 & 0x0002) ? "1" : "0" );
			// 4B
			crt->TextGrid( 37, 17, (msw_of1_14_1 & 0x0020) ? "1" : "0" );
			crt->TextGrid( 37, 18, (msw_of1_6_1 & 0x0001) ? "1" : "0" );
			crt->TextGrid( 40, 18, (msw_of1_4_2 & 0x0001) ? "1" : "0" );
			// 5A
			crt->TextGrid( 42, 17, (msw_of2_14_2 & 0x0004) ? "1" : "0" );
			crt->TextGrid( 42, 18, (msw_of2_4_2 & 0x0001) ? "1" : "0" );
			crt->TextGrid( 45, 18, (msw_of2_14_1 & 0x0002) ? "1" : "0" );
			// 5B
			crt->TextGrid( 43, 17, (msw_of1_14_1 & 0x0800) ? "1" : "0" );
			crt->TextGrid( 43, 18, (msw_of1_4_1 & 0x0001) ? "1" : "0" );
			crt->TextGrid( 46, 18, (msw_of1_14_1 & 0x0200) ? "1" : "0" );
		}
		return;
	}

	void SMDisplays::OnPaint_DISP169( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::OnPaint_ANTENNA( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::OnPaint_PLBAYDOORS( CRT_Interface* crt ) const
	{
		if (ReadCOMPOOL_IS( SCP_CSBB_POWER_ON_OFF_ITEM ) & 0x0001) crt->TextGrid( 19, 3, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_POWER_ON_OFF_ITEM ) & 0x0002) crt->TextGrid( 19, 4, "*" );

		if (ReadCOMPOOL_IS( SCP_CSBB_AUTO_MODE_ITEM ) == 1) crt->TextGrid( 19, 5, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0008) crt->TextGrid( 19, 9, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0010) crt->TextGrid( 19, 10, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0020) crt->TextGrid( 19, 11, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0040) crt->TextGrid( 19, 12, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0080) crt->TextGrid( 19, 14, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0100) crt->TextGrid( 19, 15, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0200) crt->TextGrid( 19, 16, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0400) crt->TextGrid( 19, 18, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0800) crt->TextGrid( 19, 19, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x1000) crt->TextGrid( 19, 20, "*" );

		if (ReadCOMPOOL_IS( SCP_CSBB_SWITCH_BYPASS_ITEM ) == 1) crt->TextGrid( 19, 23, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_PBD_OPEN_ITEM ) == 1) crt->TextGrid( 29, 22, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_PBD_STOP_ITEM ) == 1) crt->TextGrid( 29, 23, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_PBD_CLOSE_ITEM ) == 1) crt->TextGrid( 29, 24, "*" );

		char swtxt[8];
		memset( swtxt, 0, 8 );
		ReadCOMPOOL_C( SCP_CSBB_PBD_SWITCH_IND_TEXT, swtxt, 4 );
		crt->TextGrid( 29, 4, swtxt );

		memset( swtxt, 0, 8 );
		ReadCOMPOOL_C( SCP_CSBB_C_LCH_5_8_TEXT, swtxt, 2 );
		crt->TextGrid( 22, 9, swtxt );
		memset( swtxt, 0, 8 );
		ReadCOMPOOL_C( SCP_CSBB_C_LCH_9_12_TEXT, swtxt, 2 );
		crt->TextGrid( 22, 10, swtxt );
		memset( swtxt, 0, 8 );
		ReadCOMPOOL_C( SCP_CSBB_C_LCH_1_4_TEXT, swtxt, 2 );
		crt->TextGrid( 22, 11, swtxt );
		memset( swtxt, 0, 8 );
		ReadCOMPOOL_C( SCP_CSBB_C_LCH_13_16_TEXT, swtxt, 2 );
		crt->TextGrid( 22, 12, swtxt );

		memset( swtxt, 0, 8 );
		ReadCOMPOOL_C( SCP_CSBB_R_FWD_BHD_TEXT, swtxt, 2 );
		crt->TextGrid( 22, 14, swtxt );
		memset( swtxt, 0, 8 );
		ReadCOMPOOL_C( SCP_CSBB_R_AFT_BHD_TEXT, swtxt, 2 );
		crt->TextGrid( 22, 15, swtxt );
		memset( swtxt, 0, 8 );
		ReadCOMPOOL_C( SCP_CSBB_R_DOOR_TEXT, swtxt, 3 );
		crt->TextGrid( 21, 16, swtxt );

		memset( swtxt, 0, 8 );
		ReadCOMPOOL_C( SCP_CSBB_L_FWD_BHD_TEXT, swtxt, 2 );
		crt->TextGrid( 22, 18, swtxt );
		memset( swtxt, 0, 8 );
		ReadCOMPOOL_C( SCP_CSBB_L_AFT_BHD_TEXT, swtxt, 2 );
		crt->TextGrid( 22, 19, swtxt );
		memset( swtxt, 0, 8 );
		ReadCOMPOOL_C( SCP_CSBB_L_DOOR_TEXT, swtxt, 3 );
		crt->TextGrid( 21, 20, swtxt );


		unsigned short CSBB_OPEN_FAIL_INDICATOR = ReadCOMPOOL_IS( SCP_CSBB_OPEN_FAIL_INDICATOR );
		unsigned short CSBB_CLOSE_FAIL_INDICATOR = ReadCOMPOOL_IS( SCP_CSBB_CLOSE_FAIL_INDICATOR );
		if (((CSBB_OPEN_FAIL_INDICATOR | CSBB_CLOSE_FAIL_INDICATOR) & 0x0001) != 0) crt->TextGrid( 29, 9, "\x1D", crt->DEUATT_OVERBRIGHT );
		if (((CSBB_OPEN_FAIL_INDICATOR | CSBB_CLOSE_FAIL_INDICATOR) & 0x0002) != 0) crt->TextGrid( 29, 10, "\x1D", crt->DEUATT_OVERBRIGHT );
		if (((CSBB_OPEN_FAIL_INDICATOR | CSBB_CLOSE_FAIL_INDICATOR) & 0x0004) != 0) crt->TextGrid( 29, 11, "\x1D", crt->DEUATT_OVERBRIGHT );
		if (((CSBB_OPEN_FAIL_INDICATOR | CSBB_CLOSE_FAIL_INDICATOR) & 0x0008) != 0) crt->TextGrid( 29, 12, "\x1D", crt->DEUATT_OVERBRIGHT );

		if (((CSBB_OPEN_FAIL_INDICATOR | CSBB_CLOSE_FAIL_INDICATOR) & 0x0010) != 0) crt->TextGrid( 29, 14, "\x1D", crt->DEUATT_OVERBRIGHT );
		if (((CSBB_OPEN_FAIL_INDICATOR | CSBB_CLOSE_FAIL_INDICATOR) & 0x0020) != 0) crt->TextGrid( 29, 15, "\x1D", crt->DEUATT_OVERBRIGHT );
		if (((CSBB_OPEN_FAIL_INDICATOR | CSBB_CLOSE_FAIL_INDICATOR) & 0x0040) != 0) crt->TextGrid( 29, 16, "\x1D", crt->DEUATT_OVERBRIGHT );

		if (((CSBB_OPEN_FAIL_INDICATOR | CSBB_CLOSE_FAIL_INDICATOR) & 0x0080) != 0) crt->TextGrid( 29, 18, "\x1D", crt->DEUATT_OVERBRIGHT );
		if (((CSBB_OPEN_FAIL_INDICATOR | CSBB_CLOSE_FAIL_INDICATOR) & 0x0100) != 0) crt->TextGrid( 29, 19, "\x1D", crt->DEUATT_OVERBRIGHT );
		if (((CSBB_OPEN_FAIL_INDICATOR | CSBB_CLOSE_FAIL_INDICATOR) & 0x0200) != 0) crt->TextGrid( 29, 20, "\x1D", crt->DEUATT_OVERBRIGHT );


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


		crt->TextGrid( 33, 9, PLB_CENTERLINE_LCH_5_8_LCH_1 ? "1" : "0" );
		crt->TextGrid( 34, 9, PLB_CENTERLINE_LCH_5_8_LCH_2 ? "1" : "0" );
		crt->TextGrid( 35, 9, PLB_CENTERLINE_LCH_5_8_REL_1 ? "1" : "0" );
		crt->TextGrid( 36, 9, PLB_CENTERLINE_LCH_5_8_REL_2 ? "1" : "0" );
		crt->TextGrid( 33, 10, PLB_CENTERLINE_LCH_9_12_LCH_1 ? "1" : "0" );
		crt->TextGrid( 34, 10, PLB_CENTERLINE_LCH_9_12_LCH_2 ? "1" : "0" );
		crt->TextGrid( 35, 10, PLB_CENTERLINE_LCH_9_12_REL_1 ? "1" : "0" );
		crt->TextGrid( 36, 10, PLB_CENTERLINE_LCH_9_12_REL_2 ? "1" : "0" );
		crt->TextGrid( 33, 11, PLB_CENTERLINE_LCH_1_4_LCH_1 ? "1" : "0" );
		crt->TextGrid( 34, 11, PLB_CENTERLINE_LCH_1_4_LCH_2 ? "1" : "0" );
		crt->TextGrid( 35, 11, PLB_CENTERLINE_LCH_1_4_REL_1 ? "1" : "0" );
		crt->TextGrid( 36, 11, PLB_CENTERLINE_LCH_1_4_REL_2 ? "1" : "0" );
		crt->TextGrid( 33, 12, PLB_CENTERLINE_LCH_13_16_LCH_1 ? "1" : "0" );
		crt->TextGrid( 34, 12, PLB_CENTERLINE_LCH_13_16_LCH_2 ? "1" : "0" );
		crt->TextGrid( 35, 12, PLB_CENTERLINE_LCH_13_16_REL_1 ? "1" : "0" );
		crt->TextGrid( 36, 12, PLB_CENTERLINE_LCH_13_16_REL_2 ? "1" : "0" );

		crt->TextGrid( 33, 14, PLB_RIGHT_FWD_BHD_LATCH_LCH_1 ? "1" : "0" );
		crt->TextGrid( 34, 14, PLB_RIGHT_FWD_BHD_LATCH_LCH_2 ? "1" : "0" );
		crt->TextGrid( 35, 14, PLB_RIGHT_FWD_BHD_LATCH_REL_1 ? "1" : "0" );
		crt->TextGrid( 36, 14, PLB_RIGHT_FWD_BHD_LATCH_REL_2 ? "1" : "0" );
		crt->TextGrid( 39, 14, PLB_RIGHT_CLOSE_1 ? "1" : "0" );
		crt->TextGrid( 40, 14, PLB_RIGHT_FWD_BHD_READY_FOR_LCH_1 ? "1" : "0" );
		crt->TextGrid( 41, 14, PLB_RIGHT_FWD_BHD_READY_FOR_LCH_2 ? "1" : "0" );
		crt->TextGrid( 42, 14, PLB_RIGHT_FWD_BHD_READY_FOR_LCH_3 ? "1" : "0" );
		crt->TextGrid( 43, 14, PLB_RIGHT_OPEN_1 ? "1" : "0" );

		crt->TextGrid( 33, 15, PLB_RIGHT_AFT_BHD_LATCH_LCH_1 ? "1" : "0" );
		crt->TextGrid( 34, 15, PLB_RIGHT_AFT_BHD_LATCH_LCH_2 ? "1" : "0" );
		crt->TextGrid( 35, 15, PLB_RIGHT_AFT_BHD_LATCH_REL_1 ? "1" : "0" );
		crt->TextGrid( 36, 15, PLB_RIGHT_AFT_BHD_LATCH_REL_2 ? "1" : "0" );
		crt->TextGrid( 39, 15, PLB_RIGHT_CLOSE_2 ? "1" : "0" );
		crt->TextGrid( 40, 15, PLB_RIGHT_AFT_BHD_READY_FOR_LCH_1 ? "1" : "0" );
		crt->TextGrid( 41, 15, PLB_RIGHT_AFT_BHD_READY_FOR_LCH_2 ? "1" : "0" );
		crt->TextGrid( 42, 15, PLB_RIGHT_AFT_BHD_READY_FOR_LCH_3 ? "1" : "0" );
		crt->TextGrid( 43, 15, PLB_RIGHT_OPEN_2 ? "1" : "0" );

		crt->TextGrid( 33, 18, PLB_LEFT_FWD_BHD_LATCH_LCH_1 ? "1" : "0" );
		crt->TextGrid( 34, 18, PLB_LEFT_FWD_BHD_LATCH_LCH_2 ? "1" : "0" );
		crt->TextGrid( 35, 18, PLB_LEFT_FWD_BHD_LATCH_REL_1 ? "1" : "0" );
		crt->TextGrid( 36, 18, PLB_LEFT_FWD_BHD_LATCH_REL_2 ? "1" : "0" );
		crt->TextGrid( 39, 18, PLB_LEFT_CLOSE_1 ? "1" : "0" );
		crt->TextGrid( 40, 18, PLB_LEFT_FWD_BHD_READY_FOR_LCH_1 ? "1" : "0" );
		crt->TextGrid( 41, 18, PLB_LEFT_FWD_BHD_READY_FOR_LCH_2 ? "1" : "0" );
		crt->TextGrid( 42, 18, PLB_LEFT_FWD_BHD_READY_FOR_LCH_3 ? "1" : "0" );
		crt->TextGrid( 43, 18, PLB_LEFT_OPEN_1 ? "1" : "0" );

		crt->TextGrid( 33, 19, PLB_LEFT_AFT_BHD_LATCH_LCH_1 ? "1" : "0" );
		crt->TextGrid( 34, 19, PLB_LEFT_AFT_BHD_LATCH_LCH_2 ? "1" : "0" );
		crt->TextGrid( 35, 19, PLB_LEFT_AFT_BHD_LATCH_REL_1 ? "1" : "0" );
		crt->TextGrid( 36, 19, PLB_LEFT_AFT_BHD_LATCH_REL_2 ? "1" : "0" );
		crt->TextGrid( 39, 19, PLB_LEFT_CLOSE_2 ? "1" : "0" );
		crt->TextGrid( 40, 19, PLB_LEFT_AFT_BHD_READY_FOR_LCH_1 ? "1" : "0" );
		crt->TextGrid( 41, 19, PLB_LEFT_AFT_BHD_READY_FOR_LCH_2 ? "1" : "0" );
		crt->TextGrid( 42, 19, PLB_LEFT_AFT_BHD_READY_FOR_LCH_3 ? "1" : "0" );
		crt->TextGrid( 43, 19, PLB_LEFT_OPEN_2 ? "1" : "0" );
		return;
	}

	void SMDisplays::BackgroundData_SPEC94( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 20, 1, "PDRS CONTROL" );

		// labels
		crt->TextGrid( 1, 3, "RMS SEL:" );
		crt->TextGrid( 6, 4, "PORT" );
		crt->TextGrid( 12, 4, "1" );
		crt->TextGrid( 6, 5, "STBD" );
		crt->TextGrid( 12, 5, "2" );
		crt->TextGrid( 3, 6, "3 PL" );
		crt->TextGrid( 8, 6, "ID" );
		crt->TextGrid( 3, 7, "4 END EFF" );

		crt->TextGrid( 19, 3, "RMS PWR" );
		crt->TextGrid( 16, 4, "34 RMS S/N" );
		crt->TextGrid( 21, 5, "I/O ON 5" );
		crt->TextGrid( 24, 6, "OFF 6" );

		crt->TextGrid( 44, 3, "ENA INH" );
		crt->TextGrid( 33, 4, "SOFT" );
		crt->TextGrid( 38, 4, "STOP" );
		crt->TextGrid( 45, 4, "7" );
		crt->TextGrid( 49, 4, "8" );
		crt->TextGrid( 33, 5, "AUTO BRAKE" );
		crt->TextGrid( 45, 5, "9" );
		crt->TextGrid( 48, 5, "10" );
		crt->TextGrid( 33, 6, "POS ENC CK" );
		crt->TextGrid( 44, 6, "11" );
		crt->TextGrid( 48, 6, "12" );
		crt->TextGrid( 33, 7, "POHS" );
		crt->TextGrid( 38, 7, "CNTL" );
		crt->TextGrid( 44, 7, "28" );
		crt->TextGrid( 48, 7, "29" );

		crt->TextGrid( 22, 8, "AUTO MODES" );
		crt->TextGrid( 6, 9, "1" );
		crt->TextGrid( 14, 9, "2" );
		crt->TextGrid( 22, 9, "3" );
		crt->TextGrid( 30, 9, "4" );
		crt->TextGrid( 4, 10, "13" );
		crt->TextGrid( 12, 10, "14" );
		crt->TextGrid( 20, 10, "15" );
		crt->TextGrid( 28, 10, "16" );
		crt->TextGrid( 37, 9, "17" );
		crt->TextGrid( 40, 9, "START PT" );
		crt->TextGrid( 40, 10, "LAST" );
		crt->TextGrid( 46, 10, "PT" );

		crt->TextGrid( 15, 12, "OPR CMD MODES" );
		crt->TextGrid( 29, 12, "/ POR REF" );
		crt->TextGrid( 3, 13, "END POS" );
		crt->TextGrid( 16, 13, "END ATT" );
		crt->TextGrid( 1, 14, "18 X" );
		crt->TextGrid( 1, 15, "19 Y" );
		crt->TextGrid( 1, 16, "20 Z" );
		crt->TextGrid( 15, 14, "21 P" );
		crt->TextGrid( 15, 15, "22 Y" );
		crt->TextGrid( 15, 16, "23 R" );
		crt->TextGrid( 28, 13, "24" );
		crt->TextGrid( 31, 13, "PL" );
		crt->TextGrid( 34, 13, "INIT" );
		crt->TextGrid( 39, 13, "ID" );
		crt->TextGrid( 28, 15, "CMD CK" );
		crt->TextGrid( 35, 15, "25" );
		crt->TextGrid( 28, 17, "POR DISPLAY 30" );

		crt->TextGrid( 7, 18, "STO/DPY" );
		crt->TextGrid( 2, 19, "MPM" );

		crt->TextGrid( 6, 21, "LAT/REL/RDY" );
		crt->TextGrid( 2, 22, "AFT" );
		crt->TextGrid( 2, 23, "MID" );
		crt->TextGrid( 2, 24, "FWD" );

		crt->TextGrid( 32, 19, "ORB LD CMD REF" );
		crt->TextGrid( 28, 20, "NORM" );
		crt->TextGrid( 34, 20, "FLY-CAMR" );
		crt->TextGrid( 44, 20, "FLY-PL" );
		crt->TextGrid( 29, 21, "31" );
		crt->TextGrid( 37, 21, "32" );
		crt->TextGrid( 46, 21, "33" );

		crt->TextGrid( 28, 23, "26" );
		crt->TextGrid( 31, 23, "WR RANGE" );
		crt->TextGrid( 28, 24, "AUTO" );
		crt->TextGrid( 33, 24, "BRAKE CK" );
		crt->TextGrid( 42, 24, "27" );
		return;
	}

	void SMDisplays::BackgroundData_SPEC95( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 18, 1, "PDRS OVERRIDE" );

		// labels
		crt->TextGrid( 1, 3, "MODE" );
		crt->TextGrid( 6, 3, "SW" );
		crt->TextGrid( 9, 3, "OVRD 1" );
		crt->TextGrid( 4, 4, "MODE" );
		crt->TextGrid( 11, 4, "SEL IND" );
		crt->TextGrid( 3, 5, "ORB UNL  2" );
		crt->TextGrid( 3, 6, "SINGLE" );
		crt->TextGrid( 12, 6, "3" );
		crt->TextGrid( 3, 7, "END EFF  4" );
		crt->TextGrid( 3, 8, "ORB LD" );
		crt->TextGrid( 12, 8, "5" );
		crt->TextGrid( 3, 9, "PL" );
		crt->TextGrid( 12, 9, "6" );
		crt->TextGrid( 3, 10, "OPR CMD  7" );
		crt->TextGrid( 3, 11, "AUTO 1" );
		crt->TextGrid( 12, 11, "8" );
		crt->TextGrid( 3, 12, "AUTO 2" );
		crt->TextGrid( 12, 12, "9" );
		crt->TextGrid( 3, 13, "AUTO 3" );
		crt->TextGrid( 11, 13, "10" );
		crt->TextGrid( 3, 14, "AUTO 4" );
		crt->TextGrid( 11, 14, "11" );
		crt->TextGrid( 3, 15, "TEST" );
		crt->TextGrid( 11, 15, "12" );
		crt->TextGrid( 3, 16, "ENTER" );
		crt->TextGrid( 11, 16, "13" );

		crt->TextGrid( 3, 18, "LOADED" );
		crt->TextGrid( 8, 18, "RATE" );
		crt->TextGrid( 14, 18, "14" );
		crt->TextGrid( 1, 19, "STOWED OPS" );
		crt->TextGrid( 14, 19, "15" );
		crt->TextGrid( 1, 20, "SIN/DIR SW" );
		crt->TextGrid( 4, 21, "REASSIGN" );
		crt->TextGrid( 14, 21, "16" );

		crt->TextGrid( 19, 4, "JNT SW" );
		crt->TextGrid( 26, 4, "OVRD" );
		crt->TextGrid( 31, 4, "17" );
		crt->TextGrid( 20, 5, "JOINT" );
		crt->TextGrid( 31, 5, "SEL" );
		crt->TextGrid( 20, 6, "SH YAW" );
		crt->TextGrid( 31, 6, "18" );
		crt->TextGrid( 20, 7, "SH PITCH" );
		crt->TextGrid( 31, 7, "19" );
		crt->TextGrid( 20, 8, "EL PITCH" );
		crt->TextGrid( 31, 8, "20" );
		crt->TextGrid( 20, 9, "WR PITCH" );
		crt->TextGrid( 31, 9, "21" );
		crt->TextGrid( 20, 10, "WR YAW" );
		crt->TextGrid( 31, 10, "22" );
		crt->TextGrid( 20, 11, "WR ROLL" );
		crt->TextGrid( 31, 11, "23" );
		crt->TextGrid( 20, 12, "EE TEMP" );
		crt->TextGrid( 31, 12, "24" );
		crt->TextGrid( 20, 13, "CRIT TEMP" );
		crt->TextGrid( 31, 13, "25" );

		crt->TextGrid( 19, 15, "MCIU" );
		crt->TextGrid( 24, 15, "OVERRIDE" );
		crt->TextGrid( 20, 16, "SAFING CAN" );
		crt->TextGrid( 31, 16, "35" );
		crt->TextGrid( 20, 17, "ABE OVRD A" );
		crt->TextGrid( 31, 17, "36" );
		crt->TextGrid( 20, 18, "ABE OVRD B" );
		crt->TextGrid( 31, 18, "37" );
		crt->TextGrid( 20, 19, "ABE OVRD C" );
		crt->TextGrid( 31, 19, "38" );

		crt->TextGrid( 36, 4, "RATE" );
		crt->TextGrid( 41, 4, "SW" );
		crt->TextGrid( 44, 4, "OVRD" );
		crt->TextGrid( 49, 4, "26" );
		crt->TextGrid( 37, 5, "VERNIER" );
		crt->TextGrid( 49, 5, "27" );
		crt->TextGrid( 37, 6, "COARSE" );
		crt->TextGrid( 49, 6, "28" );

		crt->TextGrid( 36, 8, "AUTO" );
		crt->TextGrid( 41, 8, "SW" );
		crt->TextGrid( 44, 8, "OVRD" );
		crt->TextGrid( 49, 8, "29" );
		crt->TextGrid( 37, 9, "PROCEED" );
		crt->TextGrid( 49, 9, "30" );
		crt->TextGrid( 37, 10, "STOP" );
		crt->TextGrid( 49, 10, "31" );

		crt->TextGrid( 36, 12, "HC" );
		crt->TextGrid( 39, 12, "AXIS CHG" );
		crt->TextGrid( 49, 12, "32" );
		crt->TextGrid( 37, 13, "THC" );
		crt->TextGrid( 49, 13, "33" );
		crt->TextGrid( 37, 14, "RHC" );
		crt->TextGrid( 49, 14, "34" );

		// lines
		crt->Line( 170, 28, 170, 294 );
		crt->Line( 340, 42, 340, 266 );

		crt->Line( 170, 196, 340, 196 );
		return;
	}

	void SMDisplays::BackgroundData_DISP96( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 18, 1, "PDRS FAULTS" );

		// labels
		crt->TextGrid( 1, 3, "ABE BITE:" );
		crt->TextGrid( 23, 3, "SY" );
		crt->TextGrid( 26, 3, "SP" );
		crt->TextGrid( 29, 3, "EP" );
		crt->TextGrid( 32, 3, "WP" );
		crt->TextGrid( 35, 3, "WY" );
		crt->TextGrid( 38, 3, "WR" );
		crt->TextGrid( 2, 4, "MDA OVERCURRENT/" );
		crt->TextGrid( 4, 5, "MOTOR DRV FAULT" );
		crt->TextGrid( 2, 6, "COMMUTATOR" );
		crt->TextGrid( 2, 7, "TACHOMETER" );
		crt->TextGrid( 2, 8, "TOTAL COMPENSATOR" );
		crt->TextGrid( 2, 9, "MICROCOMPUTER" );
		crt->TextGrid( 2, 10, "MDA DEMAND VOLTAGE" );
		crt->TextGrid( 2, 11, "A/D CONVERTER" );
		crt->TextGrid( 2, 12, "BRAKE" );
		crt->TextGrid( 2, 13, "POS ENCONDER" );
		crt->TextGrid( 2, 14, "BACKUP RELAY" );
		crt->TextGrid( 2, 15, "CHECK CRT:" );
		crt->TextGrid( 2, 16, "DIRECT DRIVE" );
		crt->TextGrid( 15, 16, "BITE" );
		crt->TextGrid( 2, 17, "POS ENCODER" );
		crt->TextGrid( 1, 18, "CONTR ERROR" );
		crt->TextGrid( 1, 19, "REACH LIMIT" );

		crt->TextGrid( 41, 4, "MCIU:" );
		crt->TextGrid( 42, 5, "MADC" );
		crt->TextGrid( 42, 6, "MCPC" );
		crt->TextGrid( 42, 7, "ICP" );

		crt->TextGrid( 41, 9, "ABE:" );
		crt->TextGrid( 42, 10, "COMM" );

		crt->TextGrid( 41, 12, "CHECK CRT:" );
		crt->TextGrid( 42, 13, "DC/MCIU" );
		crt->TextGrid( 42, 14, "EXT FS" );
		crt->TextGrid( 42, 15, "EE" );
		crt->TextGrid( 45, 15, "FLAG" );
		crt->TextGrid( 42, 16, "EEEU" );
		crt->TextGrid( 42, 17, "EE" );
		crt->TextGrid( 45, 17, "CMDS" );
		crt->TextGrid( 42, 18, "HC" );
		crt->TextGrid( 42, 19, "MCIU" );
		crt->TextGrid( 47, 19, "HC" );
		crt->TextGrid( 42, 20, "TMP CKT" );

		crt->TextGrid( 1, 22, "CHECK CRT:" );
		crt->TextGrid( 17, 22, "SY" );
		crt->TextGrid( 22, 22, "SP" );
		crt->TextGrid( 27, 22, "EP" );
		crt->TextGrid( 32, 22, "WP" );
		crt->TextGrid( 37, 22, "WY" );
		crt->TextGrid( 42, 22, "WR" );
		crt->TextGrid( 2, 23, "SPA BITE" );
		crt->TextGrid( 11, 23, "TEST" );

		// lines
		crt->Line( 0, 42, 30, 42 );
		crt->Line( 220, 42, 390, 42 );
		crt->Line( 10, 210, 100, 210 );
		crt->Line( 0, 252, 90, 252 );
		crt->Line( 0, 266, 90, 266 );
		crt->Line( 400, 56, 440, 56 );
		crt->Line( 400, 126, 430, 126 );
		crt->Line( 400, 168, 490, 168 );
		crt->Line( 0, 308, 90, 308 );
		crt->Line( 150, 308, 440, 308 );
		return;
	}

	void SMDisplays::BackgroundData_DISP97( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 19, 1, "PL RETENTION" );

		// labels
		crt->TextGrid( 18, 5, "LATCH LATCH LATCH LATCH LATCH" );
		crt->TextGrid( 20, 6, "1" );
		crt->TextGrid( 26, 6, "2" );
		crt->TextGrid( 32, 6, "3" );
		crt->TextGrid( 38, 6, "4" );
		crt->TextGrid( 44, 6, "5" );
		crt->TextGrid( 18, 7, "AB/AB AB/AB AB/AB AB/AB AB/AB" );

		crt->TextGrid( 5, 8, "PL SEL 1" );
		crt->TextGrid( 6, 9, "RDY-FOR-LAT" );
		crt->TextGrid( 10, 10, "LAT/REL" );
		crt->TextGrid( 20, 10, "/" );
		crt->TextGrid( 26, 10, "/" );
		crt->TextGrid( 32, 10, "/" );
		crt->TextGrid( 38, 10, "/" );
		crt->TextGrid( 44, 10, "/" );

		crt->TextGrid( 5, 12, "PL SEL 2" );
		crt->TextGrid( 6, 13, "RDY-FOR-LAT" );
		crt->TextGrid( 10, 14, "LAT/REL" );
		crt->TextGrid( 20, 14, "/" );
		crt->TextGrid( 26, 14, "/" );
		crt->TextGrid( 32, 14, "/" );
		crt->TextGrid( 38, 14, "/" );
		crt->TextGrid( 44, 14, "/" );

		crt->TextGrid( 5, 16, "PL SEL 3" );
		crt->TextGrid( 6, 17, "RDY-FOR-LAT" );
		crt->TextGrid( 10, 18, "LAT/REL" );
		crt->TextGrid( 20, 18, "/" );
		crt->TextGrid( 26, 18, "/" );
		crt->TextGrid( 32, 18, "/" );
		crt->TextGrid( 38, 18, "/" );
		crt->TextGrid( 44, 18, "/" );

		// lines
		crt->Line( 30, 98, 465, 98 );
		crt->Line( 30, 154, 465, 154 );
		crt->Line( 30, 210, 465, 210 );
		crt->Line( 30, 266, 465, 266 );

		crt->Line( 165, 42, 165, 266 );
		crt->Line( 225, 42, 225, 266 );
		crt->Line( 285, 42, 285, 266 );
		crt->Line( 345, 42, 345, 266 );
		crt->Line( 405, 42, 405, 266 );
		crt->Line( 465, 42, 465, 266 );
		return;
	}

	void SMDisplays::BackgroundData_DISP169( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 20, 1, "PDRS STATUS" );

		// labels
		crt->TextGrid( 1, 3, "RMS SEL:" );
		crt->TextGrid( 1, 4, "POR REF SEL:" );

		crt->TextGrid( 38, 4, "LAST" );
		crt->TextGrid( 44, 4, "PT" );
		crt->TextGrid( 23, 5, "POHS ERR" );
		crt->TextGrid( 37, 5, "ATT ERR" );

		crt->TextGrid( 21, 6, "X/P" );
		crt->TextGrid( 33, 6, "Y/Y" );
		crt->TextGrid( 45, 6, "Z/R" );
		crt->TextGrid( 1, 7, "POHS POS REF" );
		crt->TextGrid( 1, 8, "POHS ATT REF" );
		crt->TextGrid( 1, 10, "POSITION" );
		crt->TextGrid( 1, 11, "ATTITUDE" );
		crt->TextGrid( 1, 13, "TRANS RATES ACT" );
		crt->TextGrid( 13, 14, "CMD" );
		crt->TextGrid( 1, 16, "ROT RATES" );
		crt->TextGrid( 13, 16, "ACT" );
		crt->TextGrid( 13, 17, "CMD" );

		crt->TextGrid( 9, 19, "JOINT ANGLES" );
		crt->TextGrid( 4, 20, "SY" );
		crt->TextGrid( 14, 20, "SP" );
		crt->TextGrid( 24, 20, "EP" );
		crt->TextGrid( 4, 22, "WP" );
		crt->TextGrid( 14, 22, "WY" );
		crt->TextGrid( 24, 22, "WR" );

		crt->TextGrid( 35, 19, "END EFFECTOR" );
		crt->TextGrid( 32, 20, "RIGID CLOSE CAPTURE" );
		crt->TextGrid( 32, 22, "DERIG" );
		crt->TextGrid( 39, 22, "OPEN" );
		crt->TextGrid( 45, 22, "EXTEND" );

		// lines
		crt->Line( 180, 84, 490, 84 );
		crt->Line( 0, 266, 280, 266 );
		crt->Line( 310, 266, 500, 266 );
		return;
	}

	void SMDisplays::BackgroundData_ANTENNA( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 19, 1, "ANTENNA" );

		// labels
		crt->TextGrid( 1, 3, "KU" );
		crt->TextGrid( 4, 3, "BAND" );
		crt->TextGrid( 1, 4, "SS" );

		crt->TextGrid( 44, 3, "S BAND" );
		crt->TextGrid( 44, 4, "SS" );

		crt->TextGrid( 1, 6, "RDR RNG" );
		crt->TextGrid( 5, 7, "AUTO" );
		crt->TextGrid( 11, 7, "16" );
		crt->TextGrid( 5, 8, "MIN" );
		crt->TextGrid( 11, 8, "17" );

		crt->TextGrid( 44, 6, "ANT ELEC" );

		crt->TextGrid( 44, 9, "ANT" );
		crt->TextGrid( 44, 10, "PM" );
		crt->TextGrid( 44, 11, "FM" );

		crt->TextGrid( 44, 13, "GPC PTG" );
		crt->TextGrid( 44, 14, "ENA" );
		crt->TextGrid( 49, 14, "11" );
		crt->TextGrid( 44, 15, "INH" );
		crt->TextGrid( 49, 15, "12" );
		crt->TextGrid( 44, 16, "OVRD" );
		crt->TextGrid( 49, 16, "13" );

		crt->TextGrid( 1, 16, "KU" );
		crt->TextGrid( 2, 17, "SELF" );
		crt->TextGrid( 7, 17, "TEST" );
		crt->TextGrid( 13, 17, "7" );
		crt->TextGrid( 2, 18, "O/I RESET  8" );

		crt->TextGrid( 42, 18, "MODE" );

		crt->TextGrid( 1, 20, "TDRS" );
		crt->TextGrid( 6, 20, "KU" );
		crt->TextGrid( 2, 21, "A PRI  9" );
		crt->TextGrid( 2, 22, "B PRI 10" );

		crt->TextGrid( 42, 20, "TDRS S" );
		crt->TextGrid( 43, 21, "A PRI 14" );
		crt->TextGrid( 43, 22, "B PRI 15" );

		crt->TextGrid( 43, 24, "STDN" );

		crt->TextGrid( 27, 2, "+X" );
		crt->TextGrid( 28, 3, "\x1C" );
		crt->TextGrid( 16, 4, "LL" );
		crt->TextGrid( 20, 4, "90" );
		crt->TextGrid( 24, 4, "UL" );
		crt->TextGrid( 28, 4, "0" );
		crt->TextGrid( 31, 4, "UR" );
		crt->TextGrid( 35, 4, "-90" );
		crt->TextGrid( 40, 4, "LR" );
		crt->TextGrid( 12, 5, "90" );
		crt->TextGrid( 13, 10, "0" );
		crt->TextGrid( 11, 15, "-90" );
		crt->TextGrid( 1, 11, "EL CMD" );
		crt->TextGrid( 4, 12, "ACT" );
		crt->TextGrid( 1, 13, "AZ CMD" );
		crt->TextGrid( 4, 14, "ACT" );
		crt->TextGrid( 19, 16, "TDRS STATE VECTORS" );
		crt->TextGrid( 21, 17, "TGT SAT" );
		crt->TextGrid( 30, 17, "IN" );
		crt->TextGrid( 34, 17, "GPC" );
		crt->TextGrid( 21, 18, "A B LON VIEW K S" );
		crt->TextGrid( 19, 19, "1" );
		crt->TextGrid( 19, 20, "2" );
		crt->TextGrid( 19, 21, "3" );
		crt->TextGrid( 19, 22, "4" );
		crt->TextGrid( 19, 23, "5" );
		crt->TextGrid( 19, 24, "6" );

		// lines
		crt->Line( 0, 140, 130, 140 );
		crt->Line( 0, 168, 130, 168 );
		crt->Line( 0, 196, 130, 196 );

		crt->Line( 60, 140, 60, 196 );

		crt->Line( 130, 56, 420, 56 );
		crt->Line( 130, 210, 420, 210 );

		crt->Line( 130, 56, 130, 210 );
		crt->Line( 420, 56, 420, 210 );
		return;
	}

	void SMDisplays::BackgroundData_PLBAYDOORS( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 19, 1, "PL BAY DOORS" );

		// labels
		crt->TextGrid( 3, 3, "AC POWER" );
		crt->TextGrid( 14, 3, "ON" );
		crt->TextGrid( 18, 3, "1" );
		crt->TextGrid( 13, 4, "OFF  2" );
		crt->TextGrid( 3, 5, "AUTO" );
		crt->TextGrid( 8, 5, "MODE SEL" );
		crt->TextGrid( 18, 5, "3" );
		crt->TextGrid( 22, 4, "PBD SW-" );

		crt->TextGrid( 32, 5, "MICRO-SW" );
		crt->TextGrid( 41, 5, "STAT" );
		crt->TextGrid( 33, 6, "LATS" );
		crt->TextGrid( 39, 6, "DOORS" );
		crt->TextGrid( 17, 7, "MAN OP/CL AUTO" );
		crt->TextGrid( 33, 7, "CCOO" );
		crt->TextGrid( 39, 7, "CRRRO" );
		crt->TextGrid( 2, 8, "CENTER LATCHES SEL" );
		crt->TextGrid( 28, 8, "SEQ" );
		crt->TextGrid( 33, 8, "ABAB" );
		crt->TextGrid( 40, 8, "ABC" );
		crt->TextGrid( 11, 9, "5- 8" );
		crt->TextGrid( 18, 9, "4" );
		crt->TextGrid( 11, 10, "9-12" );
		crt->TextGrid( 18, 10, "5" );
		crt->TextGrid( 11, 11, "1- 4" );
		crt->TextGrid( 18, 11, "6" );
		crt->TextGrid( 10, 12, "13-16" );
		crt->TextGrid( 18, 12, "7" );
		crt->TextGrid( 2, 13, "STBD" );
		crt->TextGrid( 5, 14, "FWD LATCHES  8" );
		crt->TextGrid( 5, 15, "AFT LATCHES  9" );
		crt->TextGrid( 5, 16, "DOOR" );
		crt->TextGrid( 17, 16, "10" );
		crt->TextGrid( 2, 17, "PORT" );
		crt->TextGrid( 5, 18, "FWD LATCHES 11" );
		crt->TextGrid( 5, 19, "AFT LATCHES 12" );
		crt->TextGrid( 5, 20, "DOOR" );
		crt->TextGrid( 17, 20, "13" );

		crt->TextGrid( 22, 22, "OPEN" );
		crt->TextGrid( 27, 22, "15" );
		crt->TextGrid( 3, 23, "PBD SW" );
		crt->TextGrid( 10, 23, "BYPASS" );
		crt->TextGrid( 17, 23, "14" );
		crt->TextGrid( 22, 23, "STOP" );
		crt->TextGrid( 27, 23, "16" );
		crt->TextGrid( 21, 24, "CLOSE" );
		crt->TextGrid( 27, 24, "17" );

		// lines
		crt->Line( 160, 70, 160, 280 );
		crt->Line( 190, 70, 190, 280 );
		crt->Line( 250, 70, 250, 280 );
		crt->Line( 300, 56, 300, 280 );
		return;
	}
}

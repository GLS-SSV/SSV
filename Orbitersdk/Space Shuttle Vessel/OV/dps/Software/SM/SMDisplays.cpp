#include "SMDisplays.h"
#include "../CRT_Interface.h"


namespace dps
{
	SMDisplays::SMDisplays( SimpleGPCSystem* _gpc ):GeneralDisplays( _gpc, "SMDisplays" )
	{
		return;
	}

	SMDisplays::~SMDisplays()
	{
	}

	void SMDisplays::Paint( CRT_Interface* crt, unsigned short page ) const
	{
		switch (page)
		{
			case 60:
				OnPaint_SMTABLEMAINT( crt );
				break;
			case 62:
				OnPaint_PCMMUPLCOMM( crt );
				break;
			case 64:
				OnPaint_SMGROUNDCHECKOUT( crt );
				break;
			case 66:
				OnPaint_ENVIRONMENT( crt );
				break;
			case 67:
				OnPaint_ELECTRIC( crt );
				break;
			case 68:
				OnPaint_CRYOSYSTEM( crt );
				break;
			case 69:
				OnPaint_FUELCELLS( crt );
				break;
			case 76:
				OnPaint_COMMUNICATIONS( crt );
				break;
			case 77:
				OnPaint_EVAMMUFSS( crt );
				break;
			case 78:
				OnPaint_SMSYSSUMM1( crt );
				break;
			case 79:
				OnPaint_SMSYSSUMM2( crt );
				break;
			case 85:
				OnPaint_MASSMEMORYRW( crt );
				break;
			case 86:
				OnPaint_APUHYD( crt );
				break;
			case 87:
				OnPaint_HYDTHERMAL( crt );
				break;
			case 88:
				OnPaint_APUENVIRONTHERM( crt );
				break;
			case 89:
				OnPaint_PRPLTTHERMAL( crt );
				break;
			case 90:
				OnPaint_PCSCONTROL( crt );
				break;
			case 94:
				OnPaint_PDRSCONTROL( crt );
				break;
			case 95:
				OnPaint_PDRSOVERRIDE( crt );
				break;
			case 96:
				OnPaint_PDRSFAULTS( crt );
				break;
			case 97:
				OnPaint_PLRETENTION( crt );
				break;
			case 98:
				OnPaint_SPDS( crt );
				break;
			case 167:
				OnPaint_DOCKINGSTATUS( crt );
				break;
			case 168:
				OnPaint_CARGOLOOP( crt );
				break;
			case 169:
				OnPaint_PDRSSTATUS( crt );
				break;
			case 177:
				OnPaint_EXTERNALAIRLOCK( crt );
				break;
			case 179:
				OnPaint_POWERTRANSFER( crt );
				break;
			case 2011:
				OnPaint_ANTENNA( crt );
				break;
			case 2021:
				OnPaint_PLBAYDOORS( crt );
				break;
		}
		return;
	}

	void SMDisplays::PaintBackground( CRT_Interface* crt, unsigned short page ) const
	{
		switch (page)
		{
			case 60:
				BackgroundData_SMTABLEMAINT( crt );
				break;
			case 62:
				BackgroundData_PCMMUPLCOMM( crt );
				break;
			case 64:
				BackgroundData_SMGROUNDCHECKOUT( crt );
				break;
			case 66:
				BackgroundData_ENVIRONMENT( crt );
				break;
			case 67:
				BackgroundData_ELECTRIC( crt );
				break;
			case 68:
				BackgroundData_CRYOSYSTEM( crt );
				break;
			case 69:
				BackgroundData_FUELCELLS( crt );
				break;
			case 76:
				BackgroundData_COMMUNICATIONS( crt );
				break;
			case 77:
				BackgroundData_EVAMMUFSS( crt );
				break;
			case 78:
				BackgroundData_SMSYSSUMM1( crt );
				break;
			case 79:
				BackgroundData_SMSYSSUMM2( crt );
				break;
			case 85:
				BackgroundData_MASSMEMORYRW( crt );
				break;
			case 86:
				BackgroundData_APUHYD( crt );
				break;
			case 87:
				BackgroundData_HYDTHERMAL( crt );
				break;
			case 88:
				BackgroundData_APUENVIRONTHERM( crt );
				break;
			case 89:
				BackgroundData_PRPLTTHERMAL( crt );
				break;
			case 90:
				BackgroundData_PCSCONTROL( crt );
				break;
			case 94:
				BackgroundData_PDRSCONTROL( crt );
				break;
			case 95:
				BackgroundData_PDRSOVERRIDE( crt );
				break;
			case 96:
				BackgroundData_PDRSFAULTS( crt );
				break;
			case 97:
				BackgroundData_PLRETENTION( crt );
				break;
			case 98:
				BackgroundData_SPDS( crt );
				break;
			case 167:
				BackgroundData_DOCKINGSTATUS( crt );
				break;
			case 168:
				BackgroundData_CARGOLOOP( crt );
				break;
			case 169:
				BackgroundData_PDRSSTATUS( crt );
				break;
			case 177:
				BackgroundData_EXTERNALAIRLOCK( crt );
				break;
			case 179:
				BackgroundData_POWERTRANSFER( crt );
				break;
			case 2011:
				BackgroundData_ANTENNA( crt );
				break;
			case 2021:
				BackgroundData_PLBAYDOORS( crt );
				break;
		}
		return;
	}

	void SMDisplays::OnPaint_SMTABLEMAINT( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::OnPaint_PCMMUPLCOMM( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::OnPaint_SMGROUNDCHECKOUT( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::OnPaint_ENVIRONMENT( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::OnPaint_ELECTRIC( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::OnPaint_CRYOSYSTEM( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::OnPaint_FUELCELLS( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::OnPaint_COMMUNICATIONS( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::OnPaint_EVAMMUFSS( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::OnPaint_SMSYSSUMM1( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::OnPaint_SMSYSSUMM2( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::OnPaint_MASSMEMORYRW( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::OnPaint_APUHYD( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::OnPaint_HYDTHERMAL( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::OnPaint_APUENVIRONTHERM( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::OnPaint_PRPLTTHERMAL( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::OnPaint_PCSCONTROL( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::OnPaint_PDRSCONTROL( CRT_Interface* crt ) const
	{
		crt->TextGrid( 13, (ReadCOMPOOL_IS( SCP_CRGV_ARM_INIT_DISP ) == 1) ? 4 : 5, "*" );

		if (ReadCOMPOOL_IS( SCP_CRGV_ARM_INIT_DISP ) == 1)
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
			crt->TextGrid( 14, 22, (msw_oa3_1_2 & 0x0004) ? "1" : "0" );
			crt->TextGrid( 16, 22, (msw_of1_4_2 & 0x0004) ? "1" : "0" );
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

	void SMDisplays::OnPaint_PDRSOVERRIDE( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::OnPaint_PDRSFAULTS( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::OnPaint_PLRETENTION( CRT_Interface* crt ) const
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

	void SMDisplays::OnPaint_SPDS( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::OnPaint_DOCKINGSTATUS( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::OnPaint_CARGOLOOP( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::OnPaint_PDRSSTATUS( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::OnPaint_EXTERNALAIRLOCK( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::OnPaint_POWERTRANSFER( CRT_Interface* crt ) const
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
		if (ReadCOMPOOL_IS( SCP_CSBB_POWER_ON_OFF_ITEM ) & 0x8000) crt->TextGrid( 19, 3, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_POWER_ON_OFF_ITEM ) & 0x4000) crt->TextGrid( 19, 4, "*" );

		if (ReadCOMPOOL_IS( SCP_CSBB_AUTO_MODE_ITEM ) == 1) crt->TextGrid( 19, 5, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEMS ) & 0x1000) crt->TextGrid( 19, 9, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEMS ) & 0x0800) crt->TextGrid( 19, 10, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEMS ) & 0x0400) crt->TextGrid( 19, 11, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEMS ) & 0x0200) crt->TextGrid( 19, 12, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEMS ) & 0x0100) crt->TextGrid( 19, 14, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEMS ) & 0x0080) crt->TextGrid( 19, 15, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEMS ) & 0x0040) crt->TextGrid( 19, 16, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEMS ) & 0x0020) crt->TextGrid( 19, 18, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEMS ) & 0x0010) crt->TextGrid( 19, 19, "*" );
		if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEMS ) & 0x0008) crt->TextGrid( 19, 20, "*" );

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
		if (((CSBB_OPEN_FAIL_INDICATOR | CSBB_CLOSE_FAIL_INDICATOR) & 0x8000) != 0) crt->TextGrid( 29, 9, "\x1D", crt->DEUATT_OVERBRIGHT );
		if (((CSBB_OPEN_FAIL_INDICATOR | CSBB_CLOSE_FAIL_INDICATOR) & 0x4000) != 0) crt->TextGrid( 29, 10, "\x1D", crt->DEUATT_OVERBRIGHT );
		if (((CSBB_OPEN_FAIL_INDICATOR | CSBB_CLOSE_FAIL_INDICATOR) & 0x2000) != 0) crt->TextGrid( 29, 11, "\x1D", crt->DEUATT_OVERBRIGHT );
		if (((CSBB_OPEN_FAIL_INDICATOR | CSBB_CLOSE_FAIL_INDICATOR) & 0x1000) != 0) crt->TextGrid( 29, 12, "\x1D", crt->DEUATT_OVERBRIGHT );

		if (((CSBB_OPEN_FAIL_INDICATOR | CSBB_CLOSE_FAIL_INDICATOR) & 0x0800) != 0) crt->TextGrid( 29, 14, "\x1D", crt->DEUATT_OVERBRIGHT );
		if (((CSBB_OPEN_FAIL_INDICATOR | CSBB_CLOSE_FAIL_INDICATOR) & 0x0400) != 0) crt->TextGrid( 29, 15, "\x1D", crt->DEUATT_OVERBRIGHT );
		if (((CSBB_OPEN_FAIL_INDICATOR | CSBB_CLOSE_FAIL_INDICATOR) & 0x0200) != 0) crt->TextGrid( 29, 16, "\x1D", crt->DEUATT_OVERBRIGHT );

		if (((CSBB_OPEN_FAIL_INDICATOR | CSBB_CLOSE_FAIL_INDICATOR) & 0x0100) != 0) crt->TextGrid( 29, 18, "\x1D", crt->DEUATT_OVERBRIGHT );
		if (((CSBB_OPEN_FAIL_INDICATOR | CSBB_CLOSE_FAIL_INDICATOR) & 0x0080) != 0) crt->TextGrid( 29, 19, "\x1D", crt->DEUATT_OVERBRIGHT );
		if (((CSBB_OPEN_FAIL_INDICATOR | CSBB_CLOSE_FAIL_INDICATOR) & 0x0040) != 0) crt->TextGrid( 29, 20, "\x1D", crt->DEUATT_OVERBRIGHT );


		unsigned short PF1_IOM3_CH0 = ReadCOMPOOL_IS( SCP_PF1_IOM3_CH0_DATA );
		unsigned short PF1_IOM6_CH0 = ReadCOMPOOL_IS( SCP_PF1_IOM6_CH0_DATA );
		unsigned short PF1_IOM9_CH0 = ReadCOMPOOL_IS( SCP_PF1_IOM9_CH0_DATA );
		unsigned short PF2_IOM3_CH0 = ReadCOMPOOL_IS( SCP_PF2_IOM3_CH0_DATA );
		unsigned short PF2_IOM6_CH0 = ReadCOMPOOL_IS( SCP_PF2_IOM6_CH0_DATA );
		unsigned short PF2_IOM9_CH0 = ReadCOMPOOL_IS( SCP_PF2_IOM9_CH0_DATA );

		bool PLB_RIGHT_FWD_BHD_READY_FOR_LCH_1 = ((PF1_IOM3_CH0 & 0x8000) != 0);
		bool PLB_RIGHT_AFT_BHD_READY_FOR_LCH_1 = ((PF1_IOM3_CH0 & 0x4000) != 0);
		bool PLB_RIGHT_FWD_BHD_LATCH_REL_1 = ((PF1_IOM3_CH0 & 0x2000) != 0);
		bool PLB_RIGHT_FWD_BHD_LATCH_LCH_1 = ((PF1_IOM3_CH0 & 0x1000) != 0);
		bool PLB_RIGHT_AFT_BHD_LATCH_REL_2 = ((PF1_IOM3_CH0 & 0x0800) != 0);
		bool PLB_RIGHT_AFT_BHD_LATCH_LCH_2 = ((PF1_IOM3_CH0 & 0x0400) != 0);
		bool PLB_RIGHT_OPEN_1 = ((PF1_IOM3_CH0 & 0x0200) != 0);
		bool PLB_RIGHT_CLOSE_1 = ((PF1_IOM3_CH0 & 0x0020) != 0);

		bool PLB_LEFT_FWD_BHD_READY_FOR_LCH_1 = ((PF1_IOM6_CH0 & 0x8000) != 0);
		bool PLB_LEFT_AFT_BHD_READY_FOR_LCH_1 = ((PF1_IOM6_CH0 & 0x4000) != 0);
		bool PLB_LEFT_FWD_BHD_LATCH_REL_1 = ((PF1_IOM6_CH0 & 0x2000) != 0);
		bool PLB_LEFT_FWD_BHD_LATCH_LCH_1 = ((PF1_IOM6_CH0 & 0x1000) != 0);
		bool PLB_LEFT_AFT_BHD_LATCH_REL_1 = ((PF1_IOM6_CH0 & 0x0800) != 0);
		bool PLB_LEFT_AFT_BHD_LATCH_LCH_1 = ((PF1_IOM6_CH0 & 0x0400) != 0);
		bool PLB_LEFT_OPEN_2 = ((PF1_IOM6_CH0 & 0x0200) != 0);
		bool PLB_LEFT_CLOSE_2 = ((PF1_IOM6_CH0 & 0x0010) != 0);

		bool PLB_LEFT_FWD_BHD_READY_FOR_LCH_2 = ((PF1_IOM9_CH0 & 0x8000) != 0);
		bool PLB_LEFT_AFT_BHD_READY_FOR_LCH_2 = ((PF1_IOM9_CH0 & 0x4000) != 0);
		bool PLB_CENTERLINE_LCH_1_4_REL_1 = ((PF1_IOM9_CH0 & 0x2000) != 0);
		bool PLB_CENTERLINE_LCH_1_4_LCH_1 = ((PF1_IOM9_CH0 & 0x1000) != 0);
		bool PLB_CENTERLINE_LCH_5_8_REL_1 = ((PF1_IOM9_CH0 & 0x0800) != 0);
		bool PLB_CENTERLINE_LCH_5_8_LCH_1 = ((PF1_IOM9_CH0 & 0x0400) != 0);
		bool PLB_CENTERLINE_LCH_9_12_LCH_1 = ((PF1_IOM9_CH0 & 0x0200) != 0);
		bool PLB_CENTERLINE_LCH_9_12_REL_1 = ((PF1_IOM9_CH0 & 0x0100) != 0);
		bool PLB_CENTERLINE_LCH_13_16_LCH_2 = ((PF1_IOM9_CH0 & 0x0080) != 0);
		bool PLB_CENTERLINE_LCH_13_16_REL_2 = ((PF1_IOM9_CH0 & 0x0040) != 0);

		bool PLB_RIGHT_FWD_BHD_READY_FOR_LCH_2 = ((PF2_IOM3_CH0 & 0x8000) != 0);
		bool PLB_RIGHT_AFT_BHD_READY_FOR_LCH_2 = ((PF2_IOM3_CH0 & 0x4000) != 0);
		bool PLB_RIGHT_FWD_BHD_LATCH_REL_2 = ((PF2_IOM3_CH0 & 0x2000) != 0);
		bool PLB_RIGHT_FWD_BHD_LATCH_LCH_2 = ((PF2_IOM3_CH0 & 0x1000) != 0);
		bool PLB_RIGHT_AFT_BHD_LATCH_REL_1 = ((PF2_IOM3_CH0 & 0x0800) != 0);
		bool PLB_RIGHT_AFT_BHD_LATCH_LCH_1 = ((PF2_IOM3_CH0 & 0x0400) != 0);
		bool PLB_RIGHT_OPEN_2 = ((PF2_IOM3_CH0 & 0x0200) != 0);
		bool PLB_RIGHT_CLOSE_2 = ((PF2_IOM3_CH0 & 0x0020) != 0);

		bool PLB_LEFT_FWD_BHD_READY_FOR_LCH_3 = ((PF2_IOM6_CH0 & 0x8000) != 0);
		bool PLB_LEFT_AFT_BHD_READY_FOR_LCH_3 = ((PF2_IOM6_CH0 & 0x4000) != 0);
		bool PLB_LEFT_FWD_BHD_LATCH_REL_2 = ((PF2_IOM6_CH0 & 0x2000) != 0);
		bool PLB_LEFT_FWD_BHD_LATCH_LCH_2 = ((PF2_IOM6_CH0 & 0x1000) != 0);
		bool PLB_LEFT_AFT_BHD_LATCH_REL_2 = ((PF2_IOM6_CH0 & 0x0800) != 0);
		bool PLB_LEFT_AFT_BHD_LATCH_LCH_2 = ((PF2_IOM6_CH0 & 0x0400) != 0);
		bool PLB_LEFT_OPEN_1 = ((PF2_IOM6_CH0 & 0x0200) != 0);
		bool PLB_LEFT_CLOSE_1 = ((PF2_IOM6_CH0 & 0x0010) != 0);

		bool PLB_RIGHT_FWD_BHD_READY_FOR_LCH_3 = ((PF2_IOM9_CH0 & 0x8000) != 0);
		bool PLB_RIGHT_AFT_BHD_READY_FOR_LCH_3 = ((PF2_IOM9_CH0 & 0x4000) != 0);
		bool PLB_CENTERLINE_LCH_1_4_REL_2 = ((PF2_IOM9_CH0 & 0x2000) != 0);
		bool PLB_CENTERLINE_LCH_1_4_LCH_2 = ((PF2_IOM9_CH0 & 0x1000) != 0);
		bool PLB_CENTERLINE_LCH_5_8_REL_2 = ((PF2_IOM9_CH0 & 0x0800) != 0);
		bool PLB_CENTERLINE_LCH_5_8_LCH_2 = ((PF2_IOM9_CH0 & 0x0400) != 0);
		bool PLB_CENTERLINE_LCH_9_12_LCH_2 = ((PF2_IOM9_CH0 & 0x0200) != 0);
		bool PLB_CENTERLINE_LCH_9_12_REL_2 = ((PF2_IOM9_CH0 & 0x0100) != 0);
		bool PLB_CENTERLINE_LCH_13_16_LCH_1 = ((PF2_IOM9_CH0 & 0x0080) != 0);
		bool PLB_CENTERLINE_LCH_13_16_REL_1 = ((PF2_IOM9_CH0 & 0x0040) != 0);


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

	void SMDisplays::BackgroundData_SMTABLEMAINT( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 18, 1, "SM TABLE MAINT" );

		// labels
		crt->TextGrid( 2, 2, "SM" );
		crt->TextGrid( 5, 2, "COMM" );
		crt->TextGrid( 9, 2, "BUFF" );
		crt->TextGrid( 2, 3, "PARAM" );
		crt->TextGrid( 4, 4, "1 ID" );
		crt->TextGrid( 6, 5, "VALUE= \x7D" );
		crt->TextGrid( 13, 5, "\x01" );
		crt->TextGrid( 13, 5, "\x02" );
		crt->TextGrid( 23, 6, "LIMITS" );

		crt->TextGrid( 12, 7, "ALERT" );
		crt->TextGrid( 7, 8, "LOW" );
		crt->TextGrid( 20, 8, "HIGH" );

		crt->TextGrid( 2, 9, "2" );
		crt->TextGrid( 4, 9, "\x01" );
		crt->TextGrid( 4, 9, "\x02" );
		crt->TextGrid( 4, 9, "\x7D\x7D\x7D\x7D\x7D\x7D\x7D\x7D\x7D" );

		crt->TextGrid( 15, 9, "3" );
		crt->TextGrid( 17, 9, "\x01" );
		crt->TextGrid( 17, 9, "\x02" );
		crt->TextGrid( 17, 9, "\x7D\x7D\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 24, 9, "\x7D\x7D" );

		crt->TextGrid( 2, 10, "4" );
		crt->TextGrid( 4, 10, "\x01" );
		crt->TextGrid( 4, 10, "\x02" );

		crt->TextGrid( 15, 10, "5" );
		crt->TextGrid( 17, 10, "\x01" );
		crt->TextGrid( 17, 10, "\x02" );

		crt->TextGrid( 2, 11, "6" );
		crt->TextGrid( 4, 11, "\x01" );
		crt->TextGrid( 4, 11, "\x02" );

		crt->TextGrid( 15, 11, "7" );
		crt->TextGrid( 17, 11, "\x01" );
		crt->TextGrid( 17, 11, "\x02" );

		crt->TextGrid( 10, 12, "8 FILTER" );
		crt->TextGrid( 19, 12, "\x7D\x7D" );
		crt->TextGrid( 10, 13, "ENA  9" );
		crt->TextGrid( 10, 14, "INH 10" );

		crt->TextGrid( 35, 7, "BACKUP C&W" );
		crt->TextGrid( 32, 8, "LOW" );
		crt->TextGrid( 46, 8, "HIGH" );

		crt->TextGrid( 26, 9, "11" );
		crt->TextGrid( 29, 9, "\x01" );
		crt->TextGrid( 29, 9, "\x02" );
		crt->TextGrid( 29, 9, "\x7D\x7D\x7D\x7D\x7D\x7D\x7D\x7D\x7D" );

		crt->TextGrid( 40, 9, "12" );
		crt->TextGrid( 43, 9, "\x01" );
		crt->TextGrid( 43, 9, "\x02" );
		crt->TextGrid( 43, 9, "\x7D\x7D\x7D\x7D\x7D\x7D\x7D\x7D\x7D" );

		crt->TextGrid( 34, 12, "13 FILTER" );
		crt->TextGrid( 44, 12, "\x7D\x7D" );
		crt->TextGrid( 34, 13, "ENA 14" );
		crt->TextGrid( 34, 14, "INH 15" );

		crt->TextGrid( 2, 16, "CONSTANT" );
		crt->TextGrid( 4, 17, "16" );
		crt->TextGrid( 7, 17, "ID \x7D\x7D\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 4, 18, "17" );
		crt->TextGrid( 7, 18, "VALUE=" );
		crt->TextGrid( 14, 18, "\x01" );
		crt->TextGrid( 14, 18, "\x02" );
		crt->TextGrid( 14, 18, "\x7D\x7D\x7D\x7D\x7D\x7D\x7D\x7D\x7D\x7D\x7D\x7D\x7D\x7D\x7D" );

		crt->TextGrid( 2, 20, "CHECKPT" );
		crt->TextGrid( 14, 20, "/" );
		crt->TextGrid( 17, 20, ":  :" );
		crt->TextGrid( 4, 21, "INITIATE" );
		crt->TextGrid( 13, 21, "18" );
		crt->TextGrid( 4, 22, "STATUS" );

		crt->TextGrid( 27, 20, "FDA" );
		crt->TextGrid( 28, 21, "ENA 19" );
		crt->TextGrid( 28, 22, "INH 20" );

		// lines
		crt->Line( 503, 176, 503, 392 );
		return;
	}

	void SMDisplays::BackgroundData_PCMMUPLCOMM( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::BackgroundData_SMGROUNDCHECKOUT( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::BackgroundData_ENVIRONMENT( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 19, 1, "ENVIRONMENT" );

		// labels
		crt->TextGrid( 10, 3, "CABIN" );
		crt->TextGrid( 1, 4, "dP/dT" );
		crt->TextGrid( 1, 5, "PPO2" );
		crt->TextGrid( 5, 6, "A" );
		crt->TextGrid( 5, 7, "B" );
		crt->TextGrid( 5, 8, "C" );
		crt->TextGrid( 1, 9, "PPCO2" );
		crt->TextGrid( 13, 4, "PRESS" );
		crt->TextGrid( 13, 5, "AIRLK P" );
		crt->TextGrid( 13, 6, "FAN" );
		crt->TextGrid( 18, 6, "\x7FP" );
		crt->TextGrid( 13, 7, "HX OUT T" );
		crt->TextGrid( 13, 8, "CABIN  T" );

		crt->TextGrid( 17, 10, "1" );
		crt->TextGrid( 23, 10, "2" );
		crt->TextGrid( 1, 11, "O2" );
		crt->TextGrid( 4, 11, "FLOW" );
		crt->TextGrid( 4, 12, "REG P" );
		crt->TextGrid( 1, 13, "N2" );
		crt->TextGrid( 4, 13, "FLOW" );
		crt->TextGrid( 4, 14, "REG P" );
		crt->TextGrid( 1, 15, "O2/N2 CNTL VLV" );
		crt->TextGrid( 1, 16, "H2O TK" );
		crt->TextGrid( 8, 16, "N2 P" );
		crt->TextGrid( 1, 17, "N2 QTY" );
		crt->TextGrid( 1, 18, "EMER O2" );
		crt->TextGrid( 9, 18, "REG P" );

		crt->TextGrid( 12, 21, "A" );
		crt->TextGrid( 15, 21, "B" );
		crt->TextGrid( 18, 21, "C" );
		crt->TextGrid( 23, 21, "\x7FP" );
		crt->TextGrid( 1, 22, "IMU" );
		crt->TextGrid( 7, 22, "FAN" );
		crt->TextGrid( 1, 23, "HUMID SEP" );

		crt->TextGrid( 28, 3, "AV BAY" );
		crt->TextGrid( 37, 3, "1" );
		crt->TextGrid( 43, 3, "2" );
		crt->TextGrid( 49, 3, "3" );
		crt->TextGrid( 27, 4, "TEMP" );
		crt->TextGrid( 27, 5, "FAN" );
		crt->TextGrid( 32, 5, "\x7FP" );
		crt->TextGrid( 28, 6, "SUPPLY H2O" );
		crt->TextGrid( 27, 7, "QTY A" );
		crt->TextGrid( 31, 8, "B" );
		crt->TextGrid( 31, 9, "C" );
		crt->TextGrid( 31, 10, "D" );
		crt->TextGrid( 39, 7, "PRESS" );
		crt->TextGrid( 39, 8, "DMP LN T" );
		crt->TextGrid( 39, 9, "NOZ  T A" );
		crt->TextGrid( 46, 10, "B" );

		crt->TextGrid( 28, 11, "WASTE H2O" );
		crt->TextGrid( 27, 12, "QTY 1" );
		crt->TextGrid( 39, 12, "PRESS" );
		crt->TextGrid( 39, 13, "DMP LN T" );
		crt->TextGrid( 39, 14, "NOZ  T A" );
		crt->TextGrid( 46, 15, "B" );
		crt->TextGrid( 35, 16, "VAC VT NOZ T" );

		crt->TextGrid( 28, 17, "CO2 CNTLR" );
		crt->TextGrid( 43, 17, "1" );
		crt->TextGrid( 49, 17, "2" );
		crt->TextGrid( 27, 18, "FILTER" );
		crt->TextGrid( 34, 18, "\x7FP" );
		crt->TextGrid( 27, 19, "PPCO2" );
		crt->TextGrid( 27, 20, "TEMP" );
		crt->TextGrid( 27, 21, "BED A PRESS" );
		crt->TextGrid( 31, 22, "B PRESS" );
		crt->TextGrid( 31, 23, "\x7FP" );
		crt->TextGrid( 27, 24, "VAC PRESS" );

		// lines
		crt->Line( 28, 257, 513, 257 );
		crt->Line( 28, 541, 513, 541 );
		crt->Line( 513, 149, 997, 149 );
		crt->Line( 513, 284, 997, 284 );
		crt->Line( 513, 446, 997, 446 );
		crt->Line( 513, 68, 513, 662 );
		return;
	}

	void SMDisplays::BackgroundData_ELECTRIC( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 21, 1, "ELECTRIC" );

		// labels
		crt->TextGrid( 2, 3, "DC" );
		crt->TextGrid( 10, 3, "1/A" );
		crt->TextGrid( 16, 3, "2/B" );
		crt->TextGrid( 22, 3, "3/C" );
		crt->TextGrid( 1, 4, "VOLT" );
		crt->TextGrid( 7, 4, "FC" );
		crt->TextGrid( 7, 5, "MN" );
		crt->TextGrid( 2, 6, "PCA FWD" );
		crt->TextGrid( 6, 7, "AFT" );
		crt->TextGrid( 2, 8, "ESS" );
		crt->TextGrid( 9, 9, "A" );
		crt->TextGrid( 15, 9, "B" );
		crt->TextGrid( 21, 9, "C" );
		crt->TextGrid( 27, 9, "A" );
		crt->TextGrid( 2, 10, "CNTL" );
		crt->TextGrid( 8, 10, "1" );
		crt->TextGrid( 8, 11, "2" );
		crt->TextGrid( 8, 12, "3" );

		crt->TextGrid( 1, 14, "AMPS" );
		crt->TextGrid( 7, 14, "FC" );
		crt->TextGrid( 6, 15, "FWD" );
		crt->TextGrid( 6, 16, "MID" );
		crt->TextGrid( 6, 17, "AFT" );

		crt->TextGrid( 1, 20, "TOTAL AMPS" );
		crt->TextGrid( 9, 21, "KW" );

		crt->TextGrid( 29, 3, "AC" );
		crt->TextGrid( 37, 3, "1" );
		crt->TextGrid( 43, 3, "2" );
		crt->TextGrid( 49, 3, "3" );
		crt->TextGrid( 28, 4, "V" );
		crt->TextGrid( 32, 4, "\x5F""A" );
		crt->TextGrid( 32, 5, "\x5F""B" );
		crt->TextGrid( 32, 6, "\x5F""C" );
		crt->TextGrid( 28, 7, "AMP" );
		crt->TextGrid( 32, 7, "\x5F""A" );
		crt->TextGrid( 32, 8, "\x5F""B" );
		crt->TextGrid( 32, 9, "\x5F""C" );
		crt->TextGrid( 28, 10, "OVLD" );
		crt->TextGrid( 28, 11, "O/U V" );

		crt->TextGrid( 29, 14, "PAYLOAD DC" );
		crt->TextGrid( 40, 14, "AMPS" );
		crt->TextGrid( 31, 15, "AFT B" );
		crt->TextGrid( 35, 16, "C" );

		// lines
		crt->Line( 541, 68, 541, 581 );
		crt->Line( 199, 244, 294, 244 );
		crt->Line( 313, 244, 408, 244 );
		crt->Line( 427, 244, 522, 244 );
		return;
	}

	void SMDisplays::BackgroundData_CRYOSYSTEM( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 18, 1, "CRYO SYSTEM" );

		// labels
		crt->TextGrid( 17, 3, "TK" );
		crt->TextGrid( 3, 4, "O2" );
		crt->TextGrid( 10, 4, "1" );
		crt->TextGrid( 15, 4, "2" );
		crt->TextGrid( 20, 4, "3" );
		crt->TextGrid( 25, 4, "4" );
		crt->TextGrid( 30, 4, "5" );
		crt->TextGrid( 1, 5, "P" );
		crt->TextGrid( 1, 6, "TK P" );
		crt->TextGrid( 1, 7, "QTY" );
		crt->TextGrid( 1, 8, "T" );
		crt->TextGrid( 1, 9, "HTR T 1" );
		crt->TextGrid( 7, 10, "2" );
		crt->TextGrid( 1, 11, "HTR" );
		crt->TextGrid( 6, 11, "1A" );
		crt->TextGrid( 1, 12, "CUR" );
		crt->TextGrid( 6, 12, "1B" );
		crt->TextGrid( 1, 13, "SNSR" );
		crt->TextGrid( 6, 13, "2A" );
		crt->TextGrid( 6, 14, "2B" );
		crt->TextGrid( 1, 15, "MANF P" );
		crt->TextGrid( 5, 16, "VLV" );

		crt->TextGrid( 3, 17, "H2" );
		crt->TextGrid( 1, 18, "P" );
		crt->TextGrid( 1, 19, "TK P" );
		crt->TextGrid( 1, 20, "QTY" );
		crt->TextGrid( 1, 21, "T" );
		crt->TextGrid( 1, 22, "HTR T" );
		crt->TextGrid( 1, 23, "MANF P" );
		crt->TextGrid( 5, 24, "VLV" );

		// lines
		crt->Line( 161, 95, 161, 662 );
		crt->Line( 256, 95, 256, 662 );
		crt->Line( 351, 95, 351, 662 );
		crt->Line( 446, 95, 446, 662 );
		crt->Line( 541, 95, 541, 662 );
		crt->Line( 636, 95, 636, 662 );
		crt->Line( 28, 446, 636, 446 );
		return;
	}

	void SMDisplays::BackgroundData_FUELCELLS( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 18, 1, "FUEL CELLS" );

		// labels
		crt->TextGrid( 17, 3, "FC" );
		crt->TextGrid( 12, 4, "1" );
		crt->TextGrid( 18, 4, "2" );
		crt->TextGrid( 24, 4, "3" );
		crt->TextGrid( 1, 5, "VOLTS" );
		crt->TextGrid( 1, 6, "AMPS" );
		crt->TextGrid( 1, 8, "FLOW" );
		crt->TextGrid( 6, 8, "O2" );
		crt->TextGrid( 6, 9, "H2" );
		crt->TextGrid( 1, 10, "REAC" );
		crt->TextGrid( 6, 10, "O2" );
		crt->TextGrid( 6, 11, "H2" );
		crt->TextGrid( 1, 13, "STACK T" );
		crt->TextGrid( 1, 14, "EXIT" );
		crt->TextGrid( 7, 14, "T" );
		crt->TextGrid( 1, 15, "COOL" );
		crt->TextGrid( 7, 15, "T" );
		crt->TextGrid( 7, 16, "P" );
		crt->TextGrid( 4, 17, "PUMP" );
		crt->TextGrid( 1, 18, "H2" );
		crt->TextGrid( 4, 18, "PUMP" );
		crt->TextGrid( 3, 19, "READY" );
		crt->TextGrid( 1, 21, "H2O" );
		crt->TextGrid( 1, 22, "PRI LN T" );
		crt->TextGrid( 4, 23, "VLV T" );
		crt->TextGrid( 1, 24, "ALT LN T" );

		crt->TextGrid( 28, 5, "H2O RLF LINE T" );
		crt->TextGrid( 37, 6, "NOZ T A" );
		crt->TextGrid( 43, 7, "B" );
		crt->TextGrid( 37, 8, "HTR SW" );
		crt->TextGrid( 28, 9, "PURGE LN" );
		crt->TextGrid( 38, 9, "O2 T" );
		crt->TextGrid( 38, 10, "H2 T1" );
		crt->TextGrid( 41, 11, "T2" );
		crt->TextGrid( 28, 12, "H2O LINE" );
		crt->TextGrid( 38, 12, "PH" );

		crt->TextGrid( 42, 15, "FC" );
		crt->TextGrid( 38, 16, "1" );
		crt->TextGrid( 43, 16, "2" );
		crt->TextGrid( 48, 16, "3" );
		crt->TextGrid( 28, 17, "PH" );
		crt->TextGrid( 28, 18, "\x7FV" );
		crt->TextGrid( 32, 18, "SS1" );
		crt->TextGrid( 32, 19, "SS2" );
		crt->TextGrid( 32, 20, "SS3" );
		crt->TextGrid( 28, 21, "\x7F""AMPS" );

		// lines
		crt->Line( 180, 95, 180, 662 );
		crt->Line( 294, 95, 294, 662 );
		crt->Line( 408, 95, 408, 662 );
		crt->Line( 522, 95, 522, 662 );
		crt->Line( 693, 419, 693, 581 );
		crt->Line( 788, 419, 788, 581 );
		crt->Line( 883, 419, 883, 581 );
		return;
	}

	void SMDisplays::BackgroundData_COMMUNICATIONS( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::BackgroundData_EVAMMUFSS( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::BackgroundData_SMSYSSUMM1( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 19, 1, "SM SYS SUMM 1" );

		// labels
		crt->TextGrid( 1, 3, "SMOKE" );
		crt->TextGrid( 12, 3, "1/A" );
		crt->TextGrid( 18, 3, "2/B" );
		crt->TextGrid( 2, 4, "CABIN" );
		crt->TextGrid( 2, 5, "L/R FD" );
		crt->TextGrid( 2, 6, "AV BAY 1" );
		crt->TextGrid( 9, 7, "2" );
		crt->TextGrid( 9, 8, "3" );

		crt->TextGrid( 7, 9, "CABIN" );
		crt->TextGrid( 2, 10, "PRESS" );
		crt->TextGrid( 2, 11, "dP/dT-EQ" );
		crt->TextGrid( 2, 12, "O2" );
		crt->TextGrid( 5, 12, "CONC" );
		crt->TextGrid( 2, 13, "PPO2" );
		crt->TextGrid( 2, 14, "FAN \x7FP" );
		crt->TextGrid( 2, 15, "HX OUT T" );
		crt->TextGrid( 2, 16, "O2" );
		crt->TextGrid( 5, 16, "FLOW" );
		crt->TextGrid( 2, 17, "N2" );
		crt->TextGrid( 5, 17, "FLOW" );
		crt->TextGrid( 2, 18, "IMU FAN" );
		crt->TextGrid( 11, 18, "A" );
		crt->TextGrid( 15, 18, "B" );
		crt->TextGrid( 19, 18, "C" );

		crt->TextGrid( 3, 19, "\x7FV" );
		crt->TextGrid( 6, 19, "FC1" );
		crt->TextGrid( 11, 19, "FC2" );
		crt->TextGrid( 16, 19, "FC3" );
		crt->TextGrid( 2, 20, "SS1" );
		crt->TextGrid( 2, 21, "SS2" );
		crt->TextGrid( 2, 22, "SS3" );
		crt->TextGrid( 2, 23, "TOTAL AMPS" );
		crt->TextGrid( 10, 24, "KW" );

		crt->TextGrid( 23, 3, "DC VOLTS" );
		crt->TextGrid( 35, 3, "1/A" );
		crt->TextGrid( 41, 3, "2/B" );
		crt->TextGrid( 47, 3, "3/C" );
		crt->TextGrid( 25, 4, "FC" );
		crt->TextGrid( 25, 5, "MAIN" );
		crt->TextGrid( 25, 6, "ESS" );
		crt->TextGrid( 33, 7, "A" );
		crt->TextGrid( 39, 7, "B" );
		crt->TextGrid( 45, 7, "C" );
		crt->TextGrid( 51, 7, "A" );
		crt->TextGrid( 25, 8, "CNTL" );
		crt->TextGrid( 31, 8, "1" );
		crt->TextGrid( 31, 9, "2" );
		crt->TextGrid( 31, 10, "3" );

		crt->TextGrid( 23, 11, "AC" );
		crt->TextGrid( 25, 12, "VOLT" );
		crt->TextGrid( 30, 12, "\x5F""A" );
		crt->TextGrid( 30, 13, "\x5F""B" );
		crt->TextGrid( 30, 14, "\x5F""C" );
		crt->TextGrid( 25, 15, "AMPS" );
		crt->TextGrid( 30, 15, "\x5F""A" );
		crt->TextGrid( 30, 16, "\x5F""B" );
		crt->TextGrid( 30, 17, "\x5F""C" );

		crt->TextGrid( 23, 18, "FUEL" );
		crt->TextGrid( 28, 18, "CELL" );
		crt->TextGrid( 25, 19, "AMPS" );
		crt->TextGrid( 25, 20, "REAC VLV" );
		crt->TextGrid( 25, 21, "STACK T" );
		crt->TextGrid( 25, 22, "EXIT" );
		crt->TextGrid( 31, 22, "T" );
		crt->TextGrid( 25, 23, "COOL" );
		crt->TextGrid( 31, 23, "P" );
		crt->TextGrid( 28, 24, "PUMP" );

		// lines
		crt->Line( 28, 230, 446, 230 );
		crt->Line( 28, 500, 446, 500 );
		crt->Line( 446, 68, 446, 662 );
		crt->Line( 655, 190, 750, 190 );
		crt->Line( 769, 190, 864, 190 );
		crt->Line( 883, 190, 978, 190 );
		return;
	}

	void SMDisplays::BackgroundData_SMSYSSUMM2( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 19, 1, "SM SYS SUMM 2" );

		// labels
		crt->TextGrid( 3, 4, "CRYO" );
		crt->TextGrid( 8, 4, "TK" );
		crt->TextGrid( 12, 4, "1" );
		crt->TextGrid( 18, 4, "2" );
		crt->TextGrid( 24, 4, "3" );
		crt->TextGrid( 30, 4, "4" );
		crt->TextGrid( 36, 4, "5" );
		crt->TextGrid( 41, 4, "MANF1 MANF2" );
		crt->TextGrid( 1, 5, "H2 PRESS" );
		crt->TextGrid( 1, 6, "O2 PRESS" );
		crt->TextGrid( 1, 7, "HTR T1" );
		crt->TextGrid( 5, 8, "T2" );

		crt->TextGrid( 3, 10, "APU" );
		crt->TextGrid( 12, 10, "1" );
		crt->TextGrid( 18, 10, "2" );
		crt->TextGrid( 24, 10, "3" );
		crt->TextGrid( 1, 11, "TEMP EGT" );
		crt->TextGrid( 2, 12, "B/U EGT" );
		crt->TextGrid( 3, 13, "OIL" );
		crt->TextGrid( 7, 13, "IN" );
		crt->TextGrid( 6, 14, "OUT" );
		crt->TextGrid( 1, 15, "SPEED  %" );
		crt->TextGrid( 1, 16, "FUEL QTY" );
		crt->TextGrid( 2, 17, "PMP LK P" );
		crt->TextGrid( 1, 18, "OIL OUT P" );

		crt->TextGrid( 3, 20, "AV BAY" );
		crt->TextGrid( 1, 21, "TEMP" );
		crt->TextGrid( 1, 22, "FAN \x7FP" );

		crt->TextGrid( 30, 10, "HYD" );
		crt->TextGrid( 37, 10, "1" );
		crt->TextGrid( 43, 10, "2" );
		crt->TextGrid( 49, 10, "3" );
		crt->TextGrid( 28, 11, "PRESS" );
		crt->TextGrid( 28, 12, "RSVR T" );
		crt->TextGrid( 33, 13, "P" );
		crt->TextGrid( 31, 14, "QTY" );
		crt->TextGrid( 30, 15, "W/B" );
		crt->TextGrid( 28, 16, "H2O QTY" );
		crt->TextGrid( 28, 17, "BYP VLV" );

		crt->TextGrid( 30, 19, "THERM CNTL" );
		crt->TextGrid( 43, 19, "1" );
		crt->TextGrid( 49, 19, "2" );
		crt->TextGrid( 28, 20, "H2O PUMP P" );
		crt->TextGrid( 28, 21, "FREON FLOW" );
		crt->TextGrid( 28, 22, "EVAP OUT T" );

		// lines
		crt->Line( 28, 247, 997, 247 );
		crt->Line( 532, 247, 532, 608 );
		return;
	}

	void SMDisplays::BackgroundData_MASSMEMORYRW( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::BackgroundData_APUHYD( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::BackgroundData_HYDTHERMAL( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::BackgroundData_APUENVIRONTHERM( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::BackgroundData_PRPLTTHERMAL( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 18, 1, "PRPLT THERMAL" );

		// labels
		crt->TextGrid( 6, 2, "POD" );
		crt->TextGrid( 16, 2, "L" );
		crt->TextGrid( 21, 2, "R" );
		crt->TextGrid( 2, 3, "OMS TK" );
		crt->TextGrid( 12, 3, "OX" );
		crt->TextGrid( 12, 4, "FU" );
		crt->TextGrid( 2, 5, "ENG I/F" );
		crt->TextGrid( 12, 5, "OX" );
		crt->TextGrid( 12, 6, "FU" );
		crt->TextGrid( 8, 7, "OX VLV" );
		crt->TextGrid( 8, 8, "FU INJ" );

		crt->TextGrid( 2, 10, "WEB KEEL" );
		crt->TextGrid( 13, 10, "1" );
		crt->TextGrid( 13, 11, "2" );
		crt->TextGrid( 6, 12, "Y" );
		crt->TextGrid( 12, 12, "OB" );
		crt->TextGrid( 12, 13, "UP" );
		crt->TextGrid( 2, 14, "OX DRN PLN 1" );
		crt->TextGrid( 13, 15, "2" );
		crt->TextGrid( 2, 16, "ENG" );
		crt->TextGrid( 9, 16, "COVER" );
		crt->TextGrid( 6, 17, "SERV PNL" );
		crt->TextGrid( 2, 18, "GSE SERV PNL" );
		crt->TextGrid( 2, 19, "TEST HE/OX 1" );
		crt->TextGrid( 13, 20, "2" );

		crt->TextGrid( 26, 4, "OMS CRSFD" );
		crt->TextGrid( 38, 4, "L" );
		crt->TextGrid( 43, 4, "R" );
		crt->TextGrid( 48, 4, "C" );
		crt->TextGrid( 25, 5, "XFD" );
		crt->TextGrid( 34, 5, "OX" );
		crt->TextGrid( 29, 6, "GMBL LN" );
		crt->TextGrid( 25, 7, "DRN" );
		crt->TextGrid( 34, 7, "OX" );

		crt->TextGrid( 26, 15, "FWD" );
		crt->TextGrid( 30, 15, "RCS" );
		crt->TextGrid( 38, 15, "FU" );
		crt->TextGrid( 43, 15, "OX" );
		crt->TextGrid( 29, 16, "LINE" );
		crt->TextGrid( 34, 16, "T1" );
		crt->TextGrid( 34, 17, "T2" );

		crt->TextGrid( 26, 19, "AFT" );
		crt->TextGrid( 30, 19, "RCS" );
		crt->TextGrid( 38, 19, "L" );
		crt->TextGrid( 43, 19, "R" );
		crt->TextGrid( 25, 20, "MANF 1" );
		crt->TextGrid( 34, 20, "OX" );
		crt->TextGrid( 25, 21, "DRN PNL" );
		crt->TextGrid( 35, 21, "1" );
		crt->TextGrid( 35, 22, "2" );
		crt->TextGrid( 25, 23, "VERN" );
		crt->TextGrid( 30, 23, "PNL" );
		crt->TextGrid( 35, 23, "1" );
		crt->TextGrid( 35, 24, "2" );

		// lines
		crt->Line( 465, 41, 465, 662 );
		crt->Line( 465, 365, 978, 365 );
		crt->Line( 465, 473, 978, 473 );
		return;
	}

	void SMDisplays::BackgroundData_PCSCONTROL( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::BackgroundData_PDRSCONTROL( CRT_Interface* crt ) const
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

	void SMDisplays::BackgroundData_PDRSOVERRIDE( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 17, 1, "PDRS OVERRIDE" );

		// labels
		crt->TextGrid( 1, 3, "MODE" );
		crt->TextGrid( 6, 3, "SW" );
		crt->TextGrid( 9, 3, "OVRD 1" );
		crt->TextGrid( 3, 4, "MODE" );
		crt->TextGrid( 9, 4, "SEL  IND" );
		crt->TextGrid( 2, 5, "ORB UNL 2" );
		crt->TextGrid( 2, 6, "SINGLE" );
		crt->TextGrid( 10, 6, "3" );
		crt->TextGrid( 2, 7, "END EFF 4" );
		crt->TextGrid( 2, 8, "ORB LD" );
		crt->TextGrid( 10, 8, "5" );
		crt->TextGrid( 2, 9, "PL" );
		crt->TextGrid( 10, 9, "6" );
		crt->TextGrid( 2, 10, "OPR CMD 7" );
		crt->TextGrid( 2, 11, "AUTO 1" );
		crt->TextGrid( 10, 11, "8" );
		crt->TextGrid( 2, 12, "AUTO 2" );
		crt->TextGrid( 10, 12, "9" );
		crt->TextGrid( 2, 13, "AUTO 3" );
		crt->TextGrid( 9, 13, "10" );
		crt->TextGrid( 2, 14, "AUTO 4" );
		crt->TextGrid( 9, 14, "11" );
		crt->TextGrid( 2, 15, "TEST" );
		crt->TextGrid( 9, 15, "12" );
		crt->TextGrid( 2, 16, "ENTER" );
		crt->TextGrid( 9, 16, "13" );

		crt->TextGrid( 1, 18, "LOADED" );
		crt->TextGrid( 8, 18, "RATE" );
		crt->TextGrid( 13, 18, "14" );
		crt->TextGrid( 1, 19, "STOWED OPS" );
		crt->TextGrid( 13, 19, "15" );
		crt->TextGrid( 1, 20, "SIN/DIR SW" );
		crt->TextGrid( 4, 21, "REASSIGN" );
		crt->TextGrid( 13, 21, "16" );

		crt->TextGrid( 18, 4, "JNT SW" );
		crt->TextGrid( 25, 4, "OVRD" );
		crt->TextGrid( 31, 4, "17" );
		crt->TextGrid( 19, 5, "JOINT" );
		crt->TextGrid( 31, 5, "SEL" );
		crt->TextGrid( 19, 6, "SH YAW" );
		crt->TextGrid( 31, 6, "18" );
		crt->TextGrid( 19, 7, "SH PITCH" );
		crt->TextGrid( 31, 7, "19" );
		crt->TextGrid( 19, 8, "EL PITCH" );
		crt->TextGrid( 31, 8, "20" );
		crt->TextGrid( 19, 9, "WR PITCH" );
		crt->TextGrid( 31, 9, "21" );
		crt->TextGrid( 19, 10, "WR YAW" );
		crt->TextGrid( 31, 10, "22" );
		crt->TextGrid( 19, 11, "WR ROLL" );
		crt->TextGrid( 31, 11, "23" );
		crt->TextGrid( 19, 12, "EE TEMP" );
		crt->TextGrid( 31, 12, "24" );
		crt->TextGrid( 19, 13, "CRIT TEMP" );
		crt->TextGrid( 31, 13, "25" );

		crt->TextGrid( 18, 15, "MCIU" );
		crt->TextGrid( 24, 15, "OVERRIDE" );
		crt->TextGrid( 19, 16, "SAFING CAN" );
		crt->TextGrid( 31, 16, "35" );
		crt->TextGrid( 19, 17, "ABE OVRD A" );
		crt->TextGrid( 31, 17, "36" );
		crt->TextGrid( 19, 18, "ABE OVRD B" );
		crt->TextGrid( 31, 18, "37" );
		crt->TextGrid( 19, 19, "ABE OVRD C" );
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
		crt->Line( 342, 68, 342, 581 );
		crt->Line( 684, 95, 684, 527 );

		crt->Line( 342, 379, 684, 379 );
		return;
	}

	void SMDisplays::BackgroundData_PDRSFAULTS( CRT_Interface* crt ) const
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
		crt->TextGrid( 2, 13, "POS ENCODER" );
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
		crt->TextGrid( 42, 7, "ICF" );

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
		crt->Line( 28, 95, 85, 95 );
		crt->Line( 47, 419, 218, 419 );
		crt->Line( 28, 500, 199, 500 );
		crt->Line( 28, 527, 199, 527 );
		crt->Line( 28, 608, 199, 608 );
		crt->Line( 446, 95, 769, 95 );
		crt->Line( 313, 608, 864, 608 );
		crt->Line( 788, 122, 864, 122 );
		crt->Line( 788, 257, 845, 257 );
		crt->Line( 788, 338, 959, 338 );
		return;
	}

	void SMDisplays::BackgroundData_PLRETENTION( CRT_Interface* crt ) const
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
		crt->Line( 104, 203, 912, 203 );
		crt->Line( 104, 298, 912, 298 );
		crt->Line( 104, 406, 912, 406 );
		crt->Line( 104, 514, 912, 514 );

		crt->Line( 342, 122, 342, 514 );
		crt->Line( 456, 122, 456, 514 );
		crt->Line( 570, 122, 570, 514 );
		crt->Line( 684, 122, 684, 514 );
		crt->Line( 798, 122, 798, 514 );
		crt->Line( 912, 122, 912, 514 );
		return;
	}

	void SMDisplays::BackgroundData_SPDS( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::BackgroundData_DOCKINGSTATUS( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::BackgroundData_CARGOLOOP( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::BackgroundData_PDRSSTATUS( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 20, 1, "PDRS STATUS" );

		// labels
		crt->TextGrid( 1, 3, "RMS SEL:" );
		crt->TextGrid( 1, 4, "POR REF SEL:" );

		crt->TextGrid( 38, 4, "LAST" );
		crt->TextGrid( 43, 4, "PT" );
		crt->TextGrid( 23, 5, "POHS ERR" );
		crt->TextGrid( 37, 5, "ATT ERR" );

		crt->TextGrid( 21, 6, "X/P" );
		crt->TextGrid( 33, 6, "Y/Y" );
		crt->TextGrid( 45, 6, "Z/R" );
		crt->TextGrid( 1, 7, "POHS POS REF" );
		crt->TextGrid( 1, 8, "POHS ATT REF" );
		crt->TextGrid( 1, 10, "POSITION" );
		crt->TextGrid( 1, 11, "ATTITUDE" );
		crt->TextGrid( 1, 13, "TRANS RATES" );
		crt->TextGrid( 14, 13, "ACT" );
		crt->TextGrid( 14, 14, "CMD" );
		crt->TextGrid( 1, 16, "ROT RATES" );
		crt->TextGrid( 14, 16, "ACT" );
		crt->TextGrid( 14, 17, "CMD" );

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
		crt->Line( 370, 176, 959, 176 );
		crt->Line( 28, 527, 560, 527 );
		crt->Line( 617, 527, 978, 527 );
		return;
	}

	void SMDisplays::BackgroundData_EXTERNALAIRLOCK( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::BackgroundData_POWERTRANSFER( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SMDisplays::BackgroundData_ANTENNA( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 18, 1, "ANTENNA" );

		// labels
		crt->TextGrid( 1, 3, "KU" );
		crt->TextGrid( 4, 3, "BAND" );
		crt->TextGrid( 1, 4, "SS" );

		crt->TextGrid( 44, 3, "S BAND" );
		crt->TextGrid( 44, 4, "SS" );

		crt->TextGrid( 1, 6, "RDR RNG" );
		crt->TextGrid( 5, 7, "AUTO" );
		crt->TextGrid( 10, 7, "16" );
		crt->TextGrid( 5, 8, "MIN" );
		crt->TextGrid( 10, 8, "17" );

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
		crt->TextGrid( 3, 17, "SELF" );
		crt->TextGrid( 8, 17, "TEST" );
		crt->TextGrid( 13, 17, "7" );
		crt->TextGrid( 3, 18, "O/I RESET 8" );

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

		crt->Text( 417, 131, "\x18" );
		crt->Text( 417, 419, "\x18" );
		crt->Text( 560, 131, "\x18" );
		crt->Text( 560, 419, "\x18" );
		crt->Text( 702, 131, "\x18" );
		crt->Text( 702, 419, "\x18" );

		// lines
		crt->Line( 275, 419, 275, 122 );// Left elevation (+-90 degree)
		crt->Line( 275, 122, 845, 122 );// Top abscissa (+-180 degree)
		crt->Line( 845, 122, 845, 419 );// Right elevation (+-90 degree)
		crt->Line( 845, 419, 275, 419 );// Lower abscissa (+-180 degree)

		crt->Line( 282, 272, 285, 272 );// Blockage pattern of nose and P/L doors (Line 1)
		crt->Line( 285, 272, 303, 192 );// Blockage pattern of nose and P/L doors (Line 2)
		crt->Line( 303, 192, 317, 176 );// Blockage pattern of nose and P/L doors (Line 3)
		crt->Line( 317, 176, 336, 162 );// Blockage pattern of nose and P/L doors (Line 4)
		crt->Line( 336, 162, 372, 162 );// Blockage pattern of nose and P/L doors (Line 5)
		crt->Line( 372, 162, 408, 162 );// Blockage pattern of nose and P/L doors (Line 6)
		crt->Line( 408, 162, 441, 183 );// Blockage pattern of nose and P/L doors (Line 7)
		crt->Line( 441, 183, 474, 223 );// Blockage pattern of nose and P/L doors (Line 8)
		crt->Line( 474, 223, 474, 305 );// Blockage pattern of nose and P/L doors (Line 9)
		crt->Line( 474, 305, 457, 311 );// Blockage pattern of nose and P/L doors (Line 10)
		crt->Line( 457, 311, 465, 359 );// Blockage pattern of nose and P/L doors (Line 11)
		crt->Line( 465, 359, 474, 372 );// Blockage pattern of nose and P/L doors (Line 12)
		crt->Line( 474, 372, 479, 377 );// Blockage pattern of nose and P/L doors (Line 13)
		crt->Line( 479, 377, 493, 379 );// Blockage pattern of nose and P/L doors (Line 14)
		crt->Line( 493, 379, 541, 365 );// Blockage pattern of nose and P/L doors (Line 15)
		crt->Line( 541, 365, 548, 366 );// Blockage pattern of nose and P/L doors (Line 16)
		crt->Line( 548, 366, 574, 392 );// Blockage pattern of nose and P/L doors (Line 17)
		crt->Line( 574, 392, 680, 397 );// Blockage pattern of nose and P/L doors (Line 18)
		crt->Line( 680, 397, 693, 383 );// Blockage pattern of right wing (Line 1)
		crt->Line( 693, 383, 702, 372 );// Blockage pattern of right wing (Line 2)
		crt->Line( 702, 372, 721, 271 );// Blockage pattern of right wing (Line 3)
		crt->Line( 721, 271, 845, 264 );// Blockage pattern of right wing (Line 4)

		crt->Line( 142, 284, 142, 392 );
		crt->Line( 28, 284, 275, 284 );
		crt->Line( 28, 338, 275, 338 );
		crt->Line( 28, 392, 275, 392 );
		return;
	}

	void SMDisplays::BackgroundData_PLBAYDOORS( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 18, 1, "PL BAY DOORS" );

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
		crt->Line( 322, 176, 322, 554 );
		crt->Line( 399, 176, 399, 554 );
		crt->Line( 512, 176, 512, 554 );
		crt->Line( 608, 122, 608, 554 );
		return;
	}
}

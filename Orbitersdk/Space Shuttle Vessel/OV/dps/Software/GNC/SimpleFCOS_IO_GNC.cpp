/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2021/06/28   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/28   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/05/13   GLS
2022/05/19   GLS
2022/05/29   GLS
2022/06/04   GLS
2022/06/06   GLS
2022/06/10   GLS
2022/06/16   GLS
2022/06/23   GLS
2022/07/02   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/10/09   GLS
2022/10/11   GLS
2022/10/12   GLS
2022/10/20   GLS
2022/10/25   GLS
2022/10/27   GLS
2022/11/01   GLS
2022/11/15   GLS
2022/12/23   GLS
2022/12/27   GLS
2023/05/07   GLS
********************************************/
#include "SimpleFCOS_IO_GNC.h"
#include "../../SimpleGPCSystem.h"


namespace dps
{
	SimpleFCOS_IO_GNC::SimpleFCOS_IO_GNC( SimpleGPCSystem* _gpc ):SimpleFCOS_IO( _gpc )
	{
	}

	SimpleFCOS_IO_GNC::~SimpleFCOS_IO_GNC()
	{
	}

	void SimpleFCOS_IO_GNC::input( void )
	{
		// send data requests to subystems
		SIMPLEBUS_COMMAND_WORD cw;
		//SIMPLEBUS_COMMANDDATA_WORD cdw[32];

		// SSME SOP input
		switch (pGPC->GetMajorMode())
		{
			case 101:
			case 102:
			case 103:
			case 104:
			case 601:
			case 602:
			case 603:
				{
					// EIU-1
					pGPC->WriteBufferAddress = SCP_EIU_1_PRIDATA;
					pGPC->WriteBufferLength = 32;
					pGPC->SubSystemAddress = EIU1_Address;

					cw.MIAaddr = pGPC->SubSystemAddress;
					cw.payload = 0b00001 << 9;
					cw.numwords = pGPC->WriteBufferLength - 1;
					pGPC->busCommand( cw, NULL );

					// HACK get secondary data
					pGPC->WriteBufferAddress = SCP_EIU_1_SECDATA;
					pGPC->WriteBufferLength = 6;

					cw.payload = 0b00011 << 9;
					cw.numwords = pGPC->WriteBufferLength - 1;
					pGPC->busCommand( cw, NULL );

					// EIU-2
					pGPC->WriteBufferAddress = SCP_EIU_2_PRIDATA;
					pGPC->WriteBufferLength = 32;
					pGPC->SubSystemAddress = EIU2_Address;

					cw.MIAaddr = pGPC->SubSystemAddress;
					cw.payload = 0b00001 << 9;
					cw.numwords = pGPC->WriteBufferLength - 1;
					pGPC->busCommand( cw, NULL );

					// HACK get secondary data
					pGPC->WriteBufferAddress = SCP_EIU_2_SECDATA;
					pGPC->WriteBufferLength = 6;

					cw.payload = 0b00011 << 9;
					cw.numwords = pGPC->WriteBufferLength - 1;
					pGPC->busCommand( cw, NULL );

					// EIU-3
					pGPC->WriteBufferAddress = SCP_EIU_3_PRIDATA;
					pGPC->WriteBufferLength = 32;
					pGPC->SubSystemAddress = EIU3_Address;

					cw.MIAaddr = pGPC->SubSystemAddress;
					cw.payload = 0b00001 << 9;
					cw.numwords = pGPC->WriteBufferLength - 1;
					pGPC->busCommand( cw, NULL );

					// HACK get secondary data
					pGPC->WriteBufferAddress = SCP_EIU_3_SECDATA;
					pGPC->WriteBufferLength = 6;

					cw.payload = 0b00011 << 9;
					cw.numwords = pGPC->WriteBufferLength - 1;
					pGPC->busCommand( cw, NULL );
				}
				break;
		}

		// MDM FF 1
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00000001) == 0) MDMReturnWord( MDM_FF1_Address, SCP_COMMFAULT_WORD_1, SCP_COMMFAULT_WORD_COUNTER_1, 0x00000001, "FF1 " );
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00000001) == 0)
		{
			InputMDMDiscretes( MDM_FF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM0, ChannelAddress_4, SCP_FF1_IOM0_CH4_DATA );
			InputMDMDiscretes( MDM_FF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM4, ChannelAddress_0, SCP_FF1_IOM4_CH0_DATA );
			InputMDMDiscretes( MDM_FF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM4, ChannelAddress_1, SCP_FF1_IOM4_CH1_DATA );
			InputMDMDiscretes( MDM_FF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM4, ChannelAddress_2, SCP_FF1_IOM4_CH2_DATA );
			InputMDMDiscretes( MDM_FF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM6, ChannelAddress_0, SCP_FF1_IOM6_CH0_DATA );
			InputMDMDiscretes( MDM_FF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM6, ChannelAddress_1, SCP_FF1_IOM6_CH1_DATA );
			InputMDMDiscretes( MDM_FF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM9, ChannelAddress_0, SCP_FF1_IOM9_CH0_DATA );
			InputMDMDiscretes( MDM_FF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM9, ChannelAddress_1, SCP_FF1_IOM9_CH1_DATA );
			InputMDMDiscretes( MDM_FF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM9, ChannelAddress_2, SCP_FF1_IOM9_CH2_DATA );
			InputMDMDiscretes( MDM_FF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM12, ChannelAddress_0, SCP_FF1_IOM12_CH0_DATA );
			InputMDMDiscretes( MDM_FF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM12, ChannelAddress_1, SCP_FF1_IOM12_CH1_DATA );
			InputMDMDiscretes( MDM_FF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM12, ChannelAddress_2, SCP_FF1_IOM12_CH2_DATA );
			InputMDMDiscretes( MDM_FF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM15, ChannelAddress_0, SCP_FF1_IOM15_CH0_DATA );
			InputMDMDiscretes( MDM_FF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM15, ChannelAddress_1, SCP_FF1_IOM15_CH1_DATA );
		}

		// MDM FF 2
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00000002) == 0) MDMReturnWord( MDM_FF2_Address, SCP_COMMFAULT_WORD_1, SCP_COMMFAULT_WORD_COUNTER_1, 0x00000002, "FF2 " );
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00000002) == 0)
		{
			InputMDMDiscretes( MDM_FF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM0, ChannelAddress_4, SCP_FF2_IOM0_CH4_DATA );
			InputMDMDiscretes( MDM_FF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM4, ChannelAddress_0, SCP_FF2_IOM4_CH0_DATA );
			InputMDMDiscretes( MDM_FF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM4, ChannelAddress_1, SCP_FF2_IOM4_CH1_DATA );
			InputMDMDiscretes( MDM_FF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM4, ChannelAddress_2, SCP_FF2_IOM4_CH2_DATA );
			InputMDMDiscretes( MDM_FF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM6, ChannelAddress_0, SCP_FF2_IOM6_CH0_DATA );
			InputMDMDiscretes( MDM_FF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM6, ChannelAddress_1, SCP_FF2_IOM6_CH1_DATA );
			InputMDMDiscretes( MDM_FF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM9, ChannelAddress_0, SCP_FF2_IOM9_CH0_DATA );
			InputMDMDiscretes( MDM_FF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM9, ChannelAddress_1, SCP_FF2_IOM9_CH1_DATA );
			InputMDMDiscretes( MDM_FF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM9, ChannelAddress_2, SCP_FF2_IOM9_CH2_DATA );
			InputMDMDiscretes( MDM_FF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM12, ChannelAddress_0, SCP_FF2_IOM12_CH0_DATA );
			InputMDMDiscretes( MDM_FF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM12, ChannelAddress_1, SCP_FF2_IOM12_CH1_DATA );
			InputMDMDiscretes( MDM_FF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM12, ChannelAddress_2, SCP_FF2_IOM12_CH2_DATA );
			InputMDMDiscretes( MDM_FF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM15, ChannelAddress_0, SCP_FF2_IOM15_CH0_DATA );
		}

		// MDM FF 3
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00000004) == 0) MDMReturnWord( MDM_FF3_Address, SCP_COMMFAULT_WORD_1, SCP_COMMFAULT_WORD_COUNTER_1, 0x00000004, "FF3 " );
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00000004) == 0)
		{
			InputMDMDiscretes( MDM_FF3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM4, ChannelAddress_0, SCP_FF3_IOM4_CH0_DATA );
			InputMDMDiscretes( MDM_FF3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM4, ChannelAddress_1, SCP_FF3_IOM4_CH1_DATA );
			InputMDMDiscretes( MDM_FF3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM4, ChannelAddress_2, SCP_FF3_IOM4_CH2_DATA );
			InputMDMDiscretes( MDM_FF3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM6, ChannelAddress_0, SCP_FF3_IOM6_CH0_DATA );
			InputMDMDiscretes( MDM_FF3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM6, ChannelAddress_1, SCP_FF3_IOM6_CH1_DATA );
			InputMDMDiscretes( MDM_FF3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM9, ChannelAddress_0, SCP_FF3_IOM9_CH0_DATA );
			InputMDMDiscretes( MDM_FF3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM9, ChannelAddress_1, SCP_FF3_IOM9_CH1_DATA );
			InputMDMDiscretes( MDM_FF3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM9, ChannelAddress_2, SCP_FF3_IOM9_CH2_DATA );
			InputMDMDiscretes( MDM_FF3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM12, ChannelAddress_0, SCP_FF3_IOM12_CH0_DATA );
			InputMDMDiscretes( MDM_FF3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM12, ChannelAddress_1, SCP_FF3_IOM12_CH1_DATA );
			InputMDMDiscretes( MDM_FF3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM12, ChannelAddress_2, SCP_FF3_IOM12_CH2_DATA );
			InputMDMDiscretes( MDM_FF3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM15, ChannelAddress_0, SCP_FF3_IOM15_CH0_DATA );
			InputMDMDiscretes( MDM_FF3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM15, ChannelAddress_1, SCP_FF3_IOM15_CH1_DATA );
		}

		// MDM FF 4
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00000008) == 0) MDMReturnWord( MDM_FF4_Address, SCP_COMMFAULT_WORD_1, SCP_COMMFAULT_WORD_COUNTER_1, 0x00000008, "FF4 " );
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00000008) == 0)
		{
			InputMDMDiscretes( MDM_FF4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM4, ChannelAddress_0, SCP_FF4_IOM4_CH0_DATA );
			InputMDMDiscretes( MDM_FF4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM4, ChannelAddress_2, SCP_FF4_IOM4_CH2_DATA );
			InputMDMDiscretes( MDM_FF4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM6, ChannelAddress_1, SCP_FF4_IOM6_CH1_DATA );
			InputMDMDiscretes( MDM_FF4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM9, ChannelAddress_0, SCP_FF4_IOM9_CH0_DATA );
			InputMDMDiscretes( MDM_FF4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM9, ChannelAddress_1, SCP_FF4_IOM9_CH1_DATA );
			InputMDMDiscretes( MDM_FF4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM9, ChannelAddress_2, SCP_FF4_IOM9_CH2_DATA );
			InputMDMDiscretes( MDM_FF4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM12, ChannelAddress_0, SCP_FF4_IOM12_CH0_DATA );
			InputMDMDiscretes( MDM_FF4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM12, ChannelAddress_1, SCP_FF4_IOM12_CH1_DATA );
			InputMDMDiscretes( MDM_FF4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM12, ChannelAddress_2, SCP_FF4_IOM12_CH2_DATA );
			InputMDMDiscretes( MDM_FF4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM15, ChannelAddress_0, SCP_FF4_IOM15_CH0_DATA );
			InputMDMDiscretes( MDM_FF4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM15, ChannelAddress_1, SCP_FF4_IOM15_CH1_DATA );
		}

		// MDM FA 1
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00001000) == 0) MDMReturnWord( MDM_FA1_Address, SCP_COMMFAULT_WORD_1, SCP_COMMFAULT_WORD_COUNTER_1, 0x00001000, "FA1 " );
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00001000) == 0)
		{
			InputMDMDiscretes( MDM_FA1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM3, ChannelAddress_0, SCP_FA1_IOM3_CH0_DATA );
			InputMDMDiscretes( MDM_FA1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM11, ChannelAddress_0, SCP_FA1_IOM11_CH0_DATA );
			InputMDMAnalogs( MDM_FA1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM6, ChannelAddress_27, SCP_FA1_IOM6_CH27_DATA );
			InputMDMAnalogs( MDM_FA1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM6, ChannelAddress_28, SCP_FA1_IOM6_CH28_DATA );
			InputMDMAnalogs( MDM_FA1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM14, ChannelAddress_14, SCP_FA1_IOM14_CH14_DATA );
			InputMDMAnalogs( MDM_FA1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM14, ChannelAddress_15, SCP_FA1_IOM14_CH15_DATA );
			InputMDMAnalogs( MDM_FA1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM14, ChannelAddress_22, SCP_FA1_IOM14_CH22_DATA );
		}

		// MDM FA 2
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00002000) == 0) MDMReturnWord( MDM_FA2_Address, SCP_COMMFAULT_WORD_1, SCP_COMMFAULT_WORD_COUNTER_1, 0x00002000, "FA2 " );
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00002000) == 0)
		{
			InputMDMDiscretes( MDM_FA2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM3, ChannelAddress_0, SCP_FA2_IOM3_CH0_DATA );
			InputMDMDiscretes( MDM_FA2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM11, ChannelAddress_0, SCP_FA2_IOM11_CH0_DATA );
			InputMDMAnalogs( MDM_FA2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM6, ChannelAddress_27, SCP_FA2_IOM6_CH27_DATA );
			InputMDMAnalogs( MDM_FA2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM6, ChannelAddress_28, SCP_FA2_IOM6_CH28_DATA );
			InputMDMAnalogs( MDM_FA2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM14, ChannelAddress_14, SCP_FA2_IOM14_CH14_DATA );
			InputMDMAnalogs( MDM_FA2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM14, ChannelAddress_15, SCP_FA2_IOM14_CH15_DATA );
			InputMDMAnalogs( MDM_FA2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM14, ChannelAddress_22, SCP_FA2_IOM14_CH22_DATA );
		}

		// MDM FA 3
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00004000) == 0) MDMReturnWord( MDM_FA3_Address, SCP_COMMFAULT_WORD_1, SCP_COMMFAULT_WORD_COUNTER_1, 0x00004000, "FA3 " );
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00004000) == 0)
		{
			InputMDMDiscretes( MDM_FA3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM3, ChannelAddress_0, SCP_FA3_IOM3_CH0_DATA );
			InputMDMDiscretes( MDM_FA3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM11, ChannelAddress_0, SCP_FA3_IOM11_CH0_DATA );
			InputMDMAnalogs( MDM_FA3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM6, ChannelAddress_27, SCP_FA3_IOM6_CH27_DATA );
			InputMDMAnalogs( MDM_FA3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM6, ChannelAddress_28, SCP_FA3_IOM6_CH28_DATA );
			InputMDMAnalogs( MDM_FA3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM14, ChannelAddress_14, SCP_FA3_IOM14_CH14_DATA );
			InputMDMAnalogs( MDM_FA3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM14, ChannelAddress_15, SCP_FA3_IOM14_CH15_DATA );
		}

		// MDM FA 4
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00008000) == 0) MDMReturnWord( MDM_FA4_Address, SCP_COMMFAULT_WORD_1, SCP_COMMFAULT_WORD_COUNTER_1, 0x00008000, "FA4 " );
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00008000) == 0)
		{
			InputMDMDiscretes( MDM_FA4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM3, ChannelAddress_0, SCP_FA4_IOM3_CH0_DATA );
			InputMDMDiscretes( MDM_FA4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM11, ChannelAddress_0, SCP_FA4_IOM11_CH0_DATA );
			InputMDMAnalogs( MDM_FA4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM14, ChannelAddress_14, SCP_FA4_IOM14_CH14_DATA );
			InputMDMAnalogs( MDM_FA4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM14, ChannelAddress_15, SCP_FA4_IOM14_CH15_DATA );
		}
		return;
	}

	void SimpleFCOS_IO_GNC::output( void )
	{
		// send commands to subystems
		SIMPLEBUS_COMMAND_WORD cw;
		SIMPLEBUS_COMMANDDATA_WORD cdw[32];

		// SSME SOP output
		switch (pGPC->GetMajorMode())
		{
			case 101:
			case 102:
			case 103:
			case 104:
			case 601:
			case 602:
			case 603:
				{
					// EIU-1
					if (pGPC->SimpleCOMPOOL[SCP_EIU_1_CMD] != 0)
					{
						pGPC->SubSystemAddress = EIU1_Address;
						pGPC->WriteBufferLength = 0;

						// HACK should be sending 2 data words
						cw.MIAaddr = pGPC->SubSystemAddress;
						cw.payload = 0b10011 << 9;
						cdw[0].MIAaddr = pGPC->SubSystemAddress;
						cdw[0].payload = pGPC->SimpleCOMPOOL[SCP_EIU_1_CMD];
						cdw[0].SEV = 0b101;
						pGPC->busCommand( cw, cdw );
					}

					// EIU-2
					if (pGPC->SimpleCOMPOOL[SCP_EIU_2_CMD] != 0)
					{
						pGPC->SubSystemAddress = EIU2_Address;
						pGPC->WriteBufferLength = 0;

						// HACK should be sending 2 data words
						cw.MIAaddr = pGPC->SubSystemAddress;
						cw.payload = 0b10011 << 9;
						cdw[0].MIAaddr = pGPC->SubSystemAddress;
						cdw[0].payload = pGPC->SimpleCOMPOOL[SCP_EIU_2_CMD];
						cdw[0].SEV = 0b101;
						pGPC->busCommand( cw, cdw );
					}

					// EIU-3
					if (pGPC->SimpleCOMPOOL[SCP_EIU_3_CMD] != 0)
					{
						pGPC->SubSystemAddress = EIU3_Address;
						pGPC->WriteBufferLength = 0;

						// HACK should be sending 2 data words
						cw.MIAaddr = pGPC->SubSystemAddress;
						cw.payload = 0b10011 << 9;
						cdw[0].MIAaddr = pGPC->SubSystemAddress;
						cdw[0].payload = pGPC->SimpleCOMPOOL[SCP_EIU_3_CMD];
						cdw[0].SEV = 0b101;
						pGPC->busCommand( cw, cdw );
					}
				}
				break;
		}

		// Dedicated Display SOP output
		switch (pGPC->GetMajorMode())
		{
			case 305:
			case 603:
				// ADI, DDU 1/HUD 1
				OutputDDU( DDU1_Address, 0b00001, SCP_DDU1_ADI, 14 );

				// ADI, DDU 2/HUD 2
				OutputDDU( DDU2_Address, 0b00001, SCP_DDU2_ADI, 14 );

				// HSI, DDU 1/HUD 1
				OutputDDU( DDU1_Address, 0b00010, SCP_DDU1_HSI, 10 );

				// HSI, DDU 2/HUD 2
				OutputDDU( DDU2_Address, 0b00010, SCP_DDU2_HSI, 10 );

				// AVVI, DDU 1/HUD 1
				OutputDDU( DDU1_Address, 0b00011, SCP_DDU1_AVVI, 6 );

				// AVVI, DDU 2/HUD 2
				OutputDDU( DDU2_Address, 0b00011, SCP_DDU2_AVVI, 6 );

				// AMI, DDU 1/HUD 1
				OutputDDU( DDU1_Address, 0b00100, SCP_DDU1_AMI, 6 );

				// AMI, DDU 2/HUD 2
				OutputDDU( DDU2_Address, 0b00100, SCP_DDU2_AMI, 6 );

				// HUD message 1, HUD 1
				OutputDDU( HUD1_Address, 0b10001, SCP_HUD1_MSG1, 31 );

				// HUD message 1, HUD 2
				OutputDDU( HUD2_Address, 0b10001, SCP_HUD2_MSG1, 31 );

				// HUD message 2, HUD 1
				OutputDDU( HUD1_Address, 0b10010, SCP_HUD1_MSG2, 12 );

				// HUD message 2, HUD 2
				OutputDDU( HUD2_Address, 0b10010, SCP_HUD2_MSG2, 12 );
				break;
		}

		// MDM FF 1
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00000001) == 0)
		{
			OutputMDMDiscretes( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_0, SCP_FF1_IOM2_CH0_DATA );
			OutputMDMDiscretes( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_1, SCP_FF1_IOM2_CH1_DATA );
			OutputMDMDiscretes( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_2, SCP_FF1_IOM2_CH2_DATA );
			OutputMDMDiscretes( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM5, ChannelAddress_1, SCP_FF1_IOM5_CH1_DATA );
			OutputMDMDiscretes( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_0, SCP_FF1_IOM10_CH0_DATA );
			OutputMDMDiscretes( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_1, SCP_FF1_IOM10_CH1_DATA );
			OutputMDMDiscretes( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_2, SCP_FF1_IOM10_CH2_DATA );
			OutputMDMAnalogs( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM8, ChannelAddress_0, SCP_FF1_IOM8_CH0_DATA );
			OutputMDMAnalogs( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM8, ChannelAddress_7, SCP_FF1_IOM8_CH7_DATA );
			OutputMDMAnalogs( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM8, ChannelAddress_8, SCP_FF1_IOM8_CH8_DATA );
			OutputMDMAnalogs( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM8, ChannelAddress_9, SCP_FF1_IOM8_CH9_DATA );
			OutputMDMAnalogs( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM8, ChannelAddress_10, SCP_FF1_IOM8_CH10_DATA );
			OutputMDMAnalogs( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM8, ChannelAddress_11, SCP_FF1_IOM8_CH11_DATA );
			OutputMDMAnalogs( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM8, ChannelAddress_12, SCP_FF1_IOM8_CH12_DATA );
			OutputMDMAnalogs( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM8, ChannelAddress_13, SCP_FF1_IOM8_CH13_DATA );
		}
		else
		{
			// reset outputs
			pGPC->SimpleCOMPOOL[SCP_FF1_IOM2_CH0_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF1_IOM2_CH1_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF1_IOM2_CH2_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF1_IOM5_CH1_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF1_IOM10_CH0_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF1_IOM10_CH1_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF1_IOM10_CH2_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF1_IOM8_CH0_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF1_IOM8_CH7_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF1_IOM8_CH8_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF1_IOM8_CH9_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF1_IOM8_CH10_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF1_IOM8_CH11_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF1_IOM8_CH12_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF1_IOM8_CH13_DATA] = 0;
		}

		// MDM FF 2
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00000002) == 0)
		{
			OutputMDMDiscretes( MDM_FF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_0, SCP_FF2_IOM2_CH0_DATA );
			OutputMDMDiscretes( MDM_FF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_1, SCP_FF2_IOM2_CH1_DATA );
			OutputMDMDiscretes( MDM_FF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_2, SCP_FF2_IOM2_CH2_DATA );
			OutputMDMDiscretes( MDM_FF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_0, SCP_FF2_IOM10_CH0_DATA );
			OutputMDMDiscretes( MDM_FF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_1, SCP_FF2_IOM10_CH1_DATA );
			OutputMDMDiscretes( MDM_FF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_2, SCP_FF2_IOM10_CH2_DATA );
			OutputMDMAnalogs( MDM_FF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM8, ChannelAddress_0, SCP_FF2_IOM8_CH0_DATA );
			OutputMDMAnalogs( MDM_FF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM8, ChannelAddress_8, SCP_FF2_IOM8_CH8_DATA );
			OutputMDMAnalogs( MDM_FF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM8, ChannelAddress_9, SCP_FF2_IOM8_CH9_DATA );
		}
		else
		{
			// reset outputs
			pGPC->SimpleCOMPOOL[SCP_FF2_IOM2_CH0_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF2_IOM2_CH1_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF2_IOM2_CH2_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF2_IOM10_CH0_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF2_IOM10_CH1_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF2_IOM10_CH2_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF2_IOM8_CH0_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF2_IOM8_CH8_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF2_IOM8_CH9_DATA] = 0;
		}

		// MDM FF 3
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00000004) == 0)
		{
			OutputMDMDiscretes( MDM_FF3_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_0, SCP_FF3_IOM2_CH0_DATA );
			OutputMDMDiscretes( MDM_FF3_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_1, SCP_FF3_IOM2_CH1_DATA );
			OutputMDMDiscretes( MDM_FF3_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_2, SCP_FF3_IOM2_CH2_DATA );
			OutputMDMDiscretes( MDM_FF3_Address, ModeControl_MDM_Receive, ModuleAddress_IOM5, ChannelAddress_1, SCP_FF3_IOM5_CH1_DATA );
			OutputMDMDiscretes( MDM_FF3_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_0, SCP_FF3_IOM10_CH0_DATA );
			OutputMDMDiscretes( MDM_FF3_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_1, SCP_FF3_IOM10_CH1_DATA );
			OutputMDMDiscretes( MDM_FF3_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_2, SCP_FF3_IOM10_CH2_DATA );
			OutputMDMAnalogs( MDM_FF3_Address, ModeControl_MDM_Receive, ModuleAddress_IOM8, ChannelAddress_0, SCP_FF3_IOM8_CH0_DATA );
		}
		else
		{
			// reset outputs
			pGPC->SimpleCOMPOOL[SCP_FF3_IOM2_CH0_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF3_IOM2_CH1_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF3_IOM2_CH2_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF3_IOM5_CH1_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF3_IOM10_CH0_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF3_IOM10_CH1_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF3_IOM10_CH2_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF3_IOM8_CH0_DATA] = 0;
		}

		// MDM FF 4
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00000008) == 0)
		{
			OutputMDMDiscretes( MDM_FF4_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_0, SCP_FF4_IOM2_CH0_DATA );
			OutputMDMDiscretes( MDM_FF4_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_1, SCP_FF4_IOM2_CH1_DATA );
			OutputMDMDiscretes( MDM_FF4_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_2, SCP_FF4_IOM2_CH2_DATA );
			OutputMDMDiscretes( MDM_FF4_Address, ModeControl_MDM_Receive, ModuleAddress_IOM5, ChannelAddress_1, SCP_FF4_IOM5_CH1_DATA );
			OutputMDMDiscretes( MDM_FF4_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_0, SCP_FF4_IOM10_CH0_DATA );
			OutputMDMDiscretes( MDM_FF4_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_2, SCP_FF4_IOM10_CH2_DATA );
		}
		else
		{
			// reset outputs
			pGPC->SimpleCOMPOOL[SCP_FF4_IOM2_CH0_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF4_IOM2_CH1_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF4_IOM2_CH2_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF4_IOM5_CH1_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF4_IOM10_CH0_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FF4_IOM10_CH2_DATA] = 0;
		}

		// MDM FA 1
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00001000) == 0)
		{
			OutputMDMAnalogs( MDM_FA1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM4, ChannelAddress_7, SCP_FA1_IOM4_CH7_DATA );
			OutputMDMAnalogs( MDM_FA1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM4, ChannelAddress_8, SCP_FA1_IOM4_CH8_DATA );
			OutputMDMDiscretes( MDM_FA1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM7, ChannelAddress_0, SCP_FA1_IOM7_CH0_DATA );
			OutputMDMDiscretes( MDM_FA1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM15, ChannelAddress_0, SCP_FA1_IOM15_CH0_DATA );
		}
		else
		{
			// reset outputs
			pGPC->SimpleCOMPOOL[SCP_FA1_IOM4_CH7_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FA1_IOM4_CH8_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FA1_IOM7_CH0_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FA1_IOM15_CH0_DATA] = 0;
		}

		// MDM FA 2
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00002000) == 0)
		{
			OutputMDMAnalogs( MDM_FA2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM4, ChannelAddress_7, SCP_FA2_IOM4_CH7_DATA );
			OutputMDMAnalogs( MDM_FA2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM4, ChannelAddress_8, SCP_FA2_IOM4_CH8_DATA );
			OutputMDMDiscretes( MDM_FA2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM7, ChannelAddress_0, SCP_FA2_IOM7_CH0_DATA );
			OutputMDMDiscretes( MDM_FA2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM15, ChannelAddress_0, SCP_FA2_IOM15_CH0_DATA );
		}
		else
		{
			// reset outputs
			pGPC->SimpleCOMPOOL[SCP_FA2_IOM4_CH7_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FA2_IOM4_CH8_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FA2_IOM7_CH0_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FA2_IOM15_CH0_DATA] = 0;
		}

		// MDM FA 3
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00004000) == 0)
		{
			OutputMDMAnalogs( MDM_FA3_Address, ModeControl_MDM_Receive, ModuleAddress_IOM4, ChannelAddress_7, SCP_FA3_IOM4_CH7_DATA );
			OutputMDMAnalogs( MDM_FA3_Address, ModeControl_MDM_Receive, ModuleAddress_IOM4, ChannelAddress_8, SCP_FA3_IOM4_CH8_DATA );
			OutputMDMDiscretes( MDM_FA3_Address, ModeControl_MDM_Receive, ModuleAddress_IOM7, ChannelAddress_0, SCP_FA3_IOM7_CH0_DATA );
			OutputMDMDiscretes( MDM_FA3_Address, ModeControl_MDM_Receive, ModuleAddress_IOM15, ChannelAddress_0, SCP_FA3_IOM15_CH0_DATA );
		}
		else
		{
			// reset outputs
			pGPC->SimpleCOMPOOL[SCP_FA3_IOM4_CH7_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FA3_IOM4_CH8_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FA3_IOM7_CH0_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FA3_IOM15_CH0_DATA] = 0;
		}

		// MDM FA 4
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00008000) == 0)
		{
			OutputMDMAnalogs( MDM_FA4_Address, ModeControl_MDM_Receive, ModuleAddress_IOM4, ChannelAddress_7, SCP_FA4_IOM4_CH7_DATA );
			OutputMDMAnalogs( MDM_FA4_Address, ModeControl_MDM_Receive, ModuleAddress_IOM4, ChannelAddress_8, SCP_FA4_IOM4_CH8_DATA );
			OutputMDMDiscretes( MDM_FA4_Address, ModeControl_MDM_Receive, ModuleAddress_IOM7, ChannelAddress_0, SCP_FA4_IOM7_CH0_DATA );
			OutputMDMDiscretes( MDM_FA4_Address, ModeControl_MDM_Receive, ModuleAddress_IOM15, ChannelAddress_0, SCP_FA4_IOM15_CH0_DATA );
		}
		else
		{
			// reset outputs
			pGPC->SimpleCOMPOOL[SCP_FA4_IOM4_CH7_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FA4_IOM4_CH8_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FA4_IOM7_CH0_DATA] = 0;
			pGPC->SimpleCOMPOOL[SCP_FA4_IOM15_CH0_DATA] = 0;
		}

		switch (pGPC->GetMajorMode())// if OPS 2, let SM command PFs
		{
			case 101:
			case 102:
			case 103:
			case 104:
			case 105:
			case 106:
			case 601:
			case 602:
			case 603:
			case 301:
			case 302:
			case 303:
			case 304:
			case 305:
			case 801:
			case 901:
				// MDM PF 1
				OutputMDMDiscretes( MDM_PF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_0, SCP_PF1_IOM2_CH0_DATA );

				// MDM PF 2
				OutputMDMDiscretes( MDM_PF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_0, SCP_PF2_IOM2_CH0_DATA );
				OutputMDMDiscretes( MDM_PF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_2, SCP_PF2_IOM10_CH2_DATA );
		}
		return;
	}

	void SimpleFCOS_IO_GNC::OutputDDU( unsigned short addr, unsigned short channeladdr, unsigned short dataddr, unsigned short datalen )
	{
		unsigned int data[32];
		memset( data, 0, 32 * sizeof(unsigned int) );
		pGPC->WriteBufferLength = 0;

		// build command word
		data[0] |= addr << 20;// MIA address
		data[0] |= channeladdr << 6;// channel
		data[0] |= (datalen - 1) << 1;// number of words
		data[0] |= (!CalcParity( data[0] )) & 1;// parity

		// build command data words
		for (unsigned int i = 1; i <= datalen; i++)
		{
			data[i] |= addr << 20;// MIA address
			data[i] |= pGPC->SimpleCOMPOOL[dataddr + i - 1] << 4;// data
			data[i] |= 0b101 << 1;//SEV
			data[i] |= (!CalcParity( data[i] )) & 1;// parity
		}

		pGPC->_Tx( BUS_FC1, data, datalen + 1 );
		pGPC->_Tx( BUS_FC2, data, datalen + 1 );
		pGPC->_Tx( BUS_FC3, data, datalen + 1 );
		pGPC->_Tx( BUS_FC4, data, datalen + 1 );
		return;
	}
}

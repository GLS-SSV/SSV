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
2023/05/12   GLS
2023/05/14   GLS
2023/05/27   GLS
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

		// HACK send DK polls only in GNC GPC, both GPCs get the response and MF field is used to filter who processes it
		// TODO 2.08Hz (480ms)
		PollDK( 1 );
		PollDK( 2 );
		PollDK( 3 );
		PollDK( 4 );

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
				// EIU-1
				InputEIU( EIU1_Address, SCP_EIU_1_PRIDATA, 32, BUS_FC5 );
				InputEIU( EIU1_Address, SCP_EIU_1_SECDATA, 6, BUS_FC8 );

				// EIU-2
				InputEIU( EIU2_Address, SCP_EIU_2_PRIDATA, 32, BUS_FC6 );
				InputEIU( EIU2_Address, SCP_EIU_2_SECDATA, 6, BUS_FC8 );

				// EIU-3
				InputEIU( EIU3_Address, SCP_EIU_3_PRIDATA, 32, BUS_FC7 );
				InputEIU( EIU3_Address, SCP_EIU_3_SECDATA, 6, BUS_FC8 );
				break;
		}

		BUS_ID bus;

		// MDM FF 1
		bus = BUS_FC1;
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00000001) == 0) MDMReturnWord( MDM_FF1_Address, SCP_COMMFAULT_WORD_1, SCP_COMMFAULT_WORD_COUNTER_1, 0x00000001, "FF1 ", bus );
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00000001) == 0)
		{
			InputMDM( MDM_FF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM0, ChannelAddress_4, SCP_FF1_IOM0_CH4_DATA, bus );
			InputMDM( MDM_FF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM4, ChannelAddress_0, SCP_FF1_IOM4_CH0_DATA, bus );
			InputMDM( MDM_FF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM4, ChannelAddress_1, SCP_FF1_IOM4_CH1_DATA, bus );
			InputMDM( MDM_FF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM4, ChannelAddress_2, SCP_FF1_IOM4_CH2_DATA, bus );
			InputMDM( MDM_FF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM6, ChannelAddress_0, SCP_FF1_IOM6_CH0_DATA, bus );
			InputMDM( MDM_FF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM6, ChannelAddress_1, SCP_FF1_IOM6_CH1_DATA, bus );
			InputMDM( MDM_FF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM9, ChannelAddress_0, SCP_FF1_IOM9_CH0_DATA, bus );
			InputMDM( MDM_FF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM9, ChannelAddress_1, SCP_FF1_IOM9_CH1_DATA, bus );
			InputMDM( MDM_FF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM9, ChannelAddress_2, SCP_FF1_IOM9_CH2_DATA, bus );
			InputMDM( MDM_FF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM12, ChannelAddress_0, SCP_FF1_IOM12_CH0_DATA, bus );
			InputMDM( MDM_FF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM12, ChannelAddress_1, SCP_FF1_IOM12_CH1_DATA, bus );
			InputMDM( MDM_FF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM12, ChannelAddress_2, SCP_FF1_IOM12_CH2_DATA, bus );
			InputMDM( MDM_FF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM15, ChannelAddress_0, SCP_FF1_IOM15_CH0_DATA, bus );
			InputMDM( MDM_FF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM15, ChannelAddress_1, SCP_FF1_IOM15_CH1_DATA, bus );
		}

		// MDM FF 2
		bus = BUS_FC2;
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00000002) == 0) MDMReturnWord( MDM_FF2_Address, SCP_COMMFAULT_WORD_1, SCP_COMMFAULT_WORD_COUNTER_1, 0x00000002, "FF2 ", bus );
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00000002) == 0)
		{
			InputMDM( MDM_FF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM0, ChannelAddress_4, SCP_FF2_IOM0_CH4_DATA, bus );
			InputMDM( MDM_FF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM4, ChannelAddress_0, SCP_FF2_IOM4_CH0_DATA, bus );
			InputMDM( MDM_FF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM4, ChannelAddress_1, SCP_FF2_IOM4_CH1_DATA, bus );
			InputMDM( MDM_FF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM4, ChannelAddress_2, SCP_FF2_IOM4_CH2_DATA, bus );
			InputMDM( MDM_FF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM6, ChannelAddress_0, SCP_FF2_IOM6_CH0_DATA, bus );
			InputMDM( MDM_FF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM6, ChannelAddress_1, SCP_FF2_IOM6_CH1_DATA, bus );
			InputMDM( MDM_FF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM9, ChannelAddress_0, SCP_FF2_IOM9_CH0_DATA, bus );
			InputMDM( MDM_FF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM9, ChannelAddress_1, SCP_FF2_IOM9_CH1_DATA, bus );
			InputMDM( MDM_FF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM9, ChannelAddress_2, SCP_FF2_IOM9_CH2_DATA, bus );
			InputMDM( MDM_FF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM12, ChannelAddress_0, SCP_FF2_IOM12_CH0_DATA, bus );
			InputMDM( MDM_FF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM12, ChannelAddress_1, SCP_FF2_IOM12_CH1_DATA, bus );
			InputMDM( MDM_FF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM12, ChannelAddress_2, SCP_FF2_IOM12_CH2_DATA, bus );
			InputMDM( MDM_FF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM15, ChannelAddress_0, SCP_FF2_IOM15_CH0_DATA, bus );
		}

		// MDM FF 3
		bus = BUS_FC3;
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00000004) == 0) MDMReturnWord( MDM_FF3_Address, SCP_COMMFAULT_WORD_1, SCP_COMMFAULT_WORD_COUNTER_1, 0x00000004, "FF3 ", bus );
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00000004) == 0)
		{
			InputMDM( MDM_FF3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM4, ChannelAddress_0, SCP_FF3_IOM4_CH0_DATA, bus );
			InputMDM( MDM_FF3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM4, ChannelAddress_1, SCP_FF3_IOM4_CH1_DATA, bus );
			InputMDM( MDM_FF3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM4, ChannelAddress_2, SCP_FF3_IOM4_CH2_DATA, bus );
			InputMDM( MDM_FF3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM6, ChannelAddress_0, SCP_FF3_IOM6_CH0_DATA, bus );
			InputMDM( MDM_FF3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM6, ChannelAddress_1, SCP_FF3_IOM6_CH1_DATA, bus );
			InputMDM( MDM_FF3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM9, ChannelAddress_0, SCP_FF3_IOM9_CH0_DATA, bus );
			InputMDM( MDM_FF3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM9, ChannelAddress_1, SCP_FF3_IOM9_CH1_DATA, bus );
			InputMDM( MDM_FF3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM9, ChannelAddress_2, SCP_FF3_IOM9_CH2_DATA, bus );
			InputMDM( MDM_FF3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM12, ChannelAddress_0, SCP_FF3_IOM12_CH0_DATA, bus );
			InputMDM( MDM_FF3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM12, ChannelAddress_1, SCP_FF3_IOM12_CH1_DATA, bus );
			InputMDM( MDM_FF3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM12, ChannelAddress_2, SCP_FF3_IOM12_CH2_DATA, bus );
			InputMDM( MDM_FF3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM15, ChannelAddress_0, SCP_FF3_IOM15_CH0_DATA, bus );
			InputMDM( MDM_FF3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM15, ChannelAddress_1, SCP_FF3_IOM15_CH1_DATA, bus );
		}

		// MDM FF 4
		bus = BUS_FC4;
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00000008) == 0) MDMReturnWord( MDM_FF4_Address, SCP_COMMFAULT_WORD_1, SCP_COMMFAULT_WORD_COUNTER_1, 0x00000008, "FF4 ", bus );
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00000008) == 0)
		{
			InputMDM( MDM_FF4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM4, ChannelAddress_0, SCP_FF4_IOM4_CH0_DATA, bus );
			InputMDM( MDM_FF4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM4, ChannelAddress_2, SCP_FF4_IOM4_CH2_DATA, bus );
			InputMDM( MDM_FF4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM6, ChannelAddress_1, SCP_FF4_IOM6_CH1_DATA, bus );
			InputMDM( MDM_FF4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM9, ChannelAddress_0, SCP_FF4_IOM9_CH0_DATA, bus );
			InputMDM( MDM_FF4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM9, ChannelAddress_1, SCP_FF4_IOM9_CH1_DATA, bus );
			InputMDM( MDM_FF4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM9, ChannelAddress_2, SCP_FF4_IOM9_CH2_DATA, bus );
			InputMDM( MDM_FF4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM12, ChannelAddress_0, SCP_FF4_IOM12_CH0_DATA, bus );
			InputMDM( MDM_FF4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM12, ChannelAddress_1, SCP_FF4_IOM12_CH1_DATA, bus );
			InputMDM( MDM_FF4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM12, ChannelAddress_2, SCP_FF4_IOM12_CH2_DATA, bus );
			InputMDM( MDM_FF4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM15, ChannelAddress_0, SCP_FF4_IOM15_CH0_DATA, bus );
			InputMDM( MDM_FF4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM15, ChannelAddress_1, SCP_FF4_IOM15_CH1_DATA, bus );
		}

		// MDM FA 1
		bus = BUS_FC1;
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00001000) == 0) MDMReturnWord( MDM_FA1_Address, SCP_COMMFAULT_WORD_1, SCP_COMMFAULT_WORD_COUNTER_1, 0x00001000, "FA1 ", bus );
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00001000) == 0)
		{
			InputMDM( MDM_FA1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM3, ChannelAddress_0, SCP_FA1_IOM3_CH0_DATA, bus );
			InputMDM( MDM_FA1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM11, ChannelAddress_0, SCP_FA1_IOM11_CH0_DATA, bus );
			InputMDM( MDM_FA1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM6, ChannelAddress_27, SCP_FA1_IOM6_CH27_DATA, bus );
			InputMDM( MDM_FA1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM6, ChannelAddress_28, SCP_FA1_IOM6_CH28_DATA, bus );
			InputMDM( MDM_FA1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM14, ChannelAddress_14, SCP_FA1_IOM14_CH14_DATA, bus );
			InputMDM( MDM_FA1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM14, ChannelAddress_15, SCP_FA1_IOM14_CH15_DATA, bus );
			InputMDM( MDM_FA1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM14, ChannelAddress_22, SCP_FA1_IOM14_CH22_DATA, bus );
		}

		// MDM FA 2
		bus = BUS_FC2;
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00002000) == 0) MDMReturnWord( MDM_FA2_Address, SCP_COMMFAULT_WORD_1, SCP_COMMFAULT_WORD_COUNTER_1, 0x00002000, "FA2 ", bus );
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00002000) == 0)
		{
			InputMDM( MDM_FA2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM3, ChannelAddress_0, SCP_FA2_IOM3_CH0_DATA, bus );
			InputMDM( MDM_FA2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM11, ChannelAddress_0, SCP_FA2_IOM11_CH0_DATA, bus );
			InputMDM( MDM_FA2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM6, ChannelAddress_27, SCP_FA2_IOM6_CH27_DATA, bus );
			InputMDM( MDM_FA2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM6, ChannelAddress_28, SCP_FA2_IOM6_CH28_DATA, bus );
			InputMDM( MDM_FA2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM14, ChannelAddress_14, SCP_FA2_IOM14_CH14_DATA, bus );
			InputMDM( MDM_FA2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM14, ChannelAddress_15, SCP_FA2_IOM14_CH15_DATA, bus );
			InputMDM( MDM_FA2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM14, ChannelAddress_22, SCP_FA2_IOM14_CH22_DATA, bus );
		}

		// MDM FA 3
		bus = BUS_FC3;
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00004000) == 0) MDMReturnWord( MDM_FA3_Address, SCP_COMMFAULT_WORD_1, SCP_COMMFAULT_WORD_COUNTER_1, 0x00004000, "FA3 ", bus );
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00004000) == 0)
		{
			InputMDM( MDM_FA3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM3, ChannelAddress_0, SCP_FA3_IOM3_CH0_DATA, bus );
			InputMDM( MDM_FA3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM11, ChannelAddress_0, SCP_FA3_IOM11_CH0_DATA, bus );
			InputMDM( MDM_FA3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM6, ChannelAddress_27, SCP_FA3_IOM6_CH27_DATA, bus );
			InputMDM( MDM_FA3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM6, ChannelAddress_28, SCP_FA3_IOM6_CH28_DATA, bus );
			InputMDM( MDM_FA3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM14, ChannelAddress_14, SCP_FA3_IOM14_CH14_DATA, bus );
			InputMDM( MDM_FA3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM14, ChannelAddress_15, SCP_FA3_IOM14_CH15_DATA, bus );
		}

		// MDM FA 4
		bus = BUS_FC4;
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00008000) == 0) MDMReturnWord( MDM_FA4_Address, SCP_COMMFAULT_WORD_1, SCP_COMMFAULT_WORD_COUNTER_1, 0x00008000, "FA4 ", bus );
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00008000) == 0)
		{
			InputMDM( MDM_FA4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM3, ChannelAddress_0, SCP_FA4_IOM3_CH0_DATA, bus );
			InputMDM( MDM_FA4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM11, ChannelAddress_0, SCP_FA4_IOM11_CH0_DATA, bus );
			InputMDM( MDM_FA4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM14, ChannelAddress_14, SCP_FA4_IOM14_CH14_DATA, bus );
			InputMDM( MDM_FA4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM14, ChannelAddress_15, SCP_FA4_IOM14_CH15_DATA, bus );
		}
		return;
	}

	void SimpleFCOS_IO_GNC::output( void )
	{
		// send commands to subystems

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
				// EIU-1
				OutputEIU( EIU1_Address, SCP_EIU_1_CMD );

				// EIU-2
				OutputEIU( EIU2_Address, SCP_EIU_2_CMD );

				// EIU-3
				OutputEIU( EIU3_Address, SCP_EIU_3_CMD );
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

		BUS_ID bus;

		// MDM FF 1
		bus = BUS_FC1;
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00000001) == 0)
		{
			OutputMDM( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_0, SCP_FF1_IOM2_CH0_DATA, bus );
			OutputMDM( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_1, SCP_FF1_IOM2_CH1_DATA, bus );
			OutputMDM( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_2, SCP_FF1_IOM2_CH2_DATA, bus );
			OutputMDM( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM5, ChannelAddress_1, SCP_FF1_IOM5_CH1_DATA, bus );
			OutputMDM( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_0, SCP_FF1_IOM10_CH0_DATA, bus );
			OutputMDM( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_1, SCP_FF1_IOM10_CH1_DATA, bus );
			OutputMDM( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_2, SCP_FF1_IOM10_CH2_DATA, bus );
			OutputMDM( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM8, ChannelAddress_0, SCP_FF1_IOM8_CH0_DATA, bus );
			OutputMDM( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM8, ChannelAddress_7, SCP_FF1_IOM8_CH7_DATA, bus );
			OutputMDM( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM8, ChannelAddress_8, SCP_FF1_IOM8_CH8_DATA, bus );
			OutputMDM( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM8, ChannelAddress_9, SCP_FF1_IOM8_CH9_DATA, bus );
			OutputMDM( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM8, ChannelAddress_10, SCP_FF1_IOM8_CH10_DATA, bus );
			OutputMDM( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM8, ChannelAddress_11, SCP_FF1_IOM8_CH11_DATA, bus );
			OutputMDM( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM8, ChannelAddress_12, SCP_FF1_IOM8_CH12_DATA, bus );
			OutputMDM( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM8, ChannelAddress_13, SCP_FF1_IOM8_CH13_DATA, bus );
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
		bus = BUS_FC2;
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00000002) == 0)
		{
			OutputMDM( MDM_FF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_0, SCP_FF2_IOM2_CH0_DATA, bus );
			OutputMDM( MDM_FF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_1, SCP_FF2_IOM2_CH1_DATA, bus );
			OutputMDM( MDM_FF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_2, SCP_FF2_IOM2_CH2_DATA, bus );
			OutputMDM( MDM_FF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_0, SCP_FF2_IOM10_CH0_DATA, bus );
			OutputMDM( MDM_FF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_1, SCP_FF2_IOM10_CH1_DATA, bus );
			OutputMDM( MDM_FF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_2, SCP_FF2_IOM10_CH2_DATA, bus );
			OutputMDM( MDM_FF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM8, ChannelAddress_0, SCP_FF2_IOM8_CH0_DATA, bus );
			OutputMDM( MDM_FF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM8, ChannelAddress_8, SCP_FF2_IOM8_CH8_DATA, bus );
			OutputMDM( MDM_FF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM8, ChannelAddress_9, SCP_FF2_IOM8_CH9_DATA, bus );
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
		bus = BUS_FC3;
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00000004) == 0)
		{
			OutputMDM( MDM_FF3_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_0, SCP_FF3_IOM2_CH0_DATA, bus );
			OutputMDM( MDM_FF3_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_1, SCP_FF3_IOM2_CH1_DATA, bus );
			OutputMDM( MDM_FF3_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_2, SCP_FF3_IOM2_CH2_DATA, bus );
			OutputMDM( MDM_FF3_Address, ModeControl_MDM_Receive, ModuleAddress_IOM5, ChannelAddress_1, SCP_FF3_IOM5_CH1_DATA, bus );
			OutputMDM( MDM_FF3_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_0, SCP_FF3_IOM10_CH0_DATA, bus );
			OutputMDM( MDM_FF3_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_1, SCP_FF3_IOM10_CH1_DATA, bus );
			OutputMDM( MDM_FF3_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_2, SCP_FF3_IOM10_CH2_DATA, bus );
			OutputMDM( MDM_FF3_Address, ModeControl_MDM_Receive, ModuleAddress_IOM8, ChannelAddress_0, SCP_FF3_IOM8_CH0_DATA, bus );
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
		bus = BUS_FC4;
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00000008) == 0)
		{
			OutputMDM( MDM_FF4_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_0, SCP_FF4_IOM2_CH0_DATA, bus );
			OutputMDM( MDM_FF4_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_1, SCP_FF4_IOM2_CH1_DATA, bus );
			OutputMDM( MDM_FF4_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_2, SCP_FF4_IOM2_CH2_DATA, bus );
			OutputMDM( MDM_FF4_Address, ModeControl_MDM_Receive, ModuleAddress_IOM5, ChannelAddress_1, SCP_FF4_IOM5_CH1_DATA, bus );
			OutputMDM( MDM_FF4_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_0, SCP_FF4_IOM10_CH0_DATA, bus );
			OutputMDM( MDM_FF4_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_2, SCP_FF4_IOM10_CH2_DATA, bus );
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
		bus = BUS_FC1;
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00001000) == 0)
		{
			OutputMDM( MDM_FA1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM4, ChannelAddress_7, SCP_FA1_IOM4_CH7_DATA, bus );
			OutputMDM( MDM_FA1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM4, ChannelAddress_8, SCP_FA1_IOM4_CH8_DATA, bus );
			OutputMDM( MDM_FA1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM7, ChannelAddress_0, SCP_FA1_IOM7_CH0_DATA, bus );
			OutputMDM( MDM_FA1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM15, ChannelAddress_0, SCP_FA1_IOM15_CH0_DATA, bus );
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
		bus = BUS_FC2;
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00002000) == 0)
		{
			OutputMDM( MDM_FA2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM4, ChannelAddress_7, SCP_FA2_IOM4_CH7_DATA, bus );
			OutputMDM( MDM_FA2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM4, ChannelAddress_8, SCP_FA2_IOM4_CH8_DATA, bus );
			OutputMDM( MDM_FA2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM7, ChannelAddress_0, SCP_FA2_IOM7_CH0_DATA, bus );
			OutputMDM( MDM_FA2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM15, ChannelAddress_0, SCP_FA2_IOM15_CH0_DATA, bus );
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
		bus = BUS_FC3;
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00004000) == 0)
		{
			OutputMDM( MDM_FA3_Address, ModeControl_MDM_Receive, ModuleAddress_IOM4, ChannelAddress_7, SCP_FA3_IOM4_CH7_DATA, bus );
			OutputMDM( MDM_FA3_Address, ModeControl_MDM_Receive, ModuleAddress_IOM4, ChannelAddress_8, SCP_FA3_IOM4_CH8_DATA, bus );
			OutputMDM( MDM_FA3_Address, ModeControl_MDM_Receive, ModuleAddress_IOM7, ChannelAddress_0, SCP_FA3_IOM7_CH0_DATA, bus );
			OutputMDM( MDM_FA3_Address, ModeControl_MDM_Receive, ModuleAddress_IOM15, ChannelAddress_0, SCP_FA3_IOM15_CH0_DATA, bus );
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
		bus = BUS_FC4;
		if ((pGPC->ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00008000) == 0)
		{
			OutputMDM( MDM_FA4_Address, ModeControl_MDM_Receive, ModuleAddress_IOM4, ChannelAddress_7, SCP_FA4_IOM4_CH7_DATA, bus );
			OutputMDM( MDM_FA4_Address, ModeControl_MDM_Receive, ModuleAddress_IOM4, ChannelAddress_8, SCP_FA4_IOM4_CH8_DATA, bus );
			OutputMDM( MDM_FA4_Address, ModeControl_MDM_Receive, ModuleAddress_IOM7, ChannelAddress_0, SCP_FA4_IOM7_CH0_DATA, bus );
			OutputMDM( MDM_FA4_Address, ModeControl_MDM_Receive, ModuleAddress_IOM15, ChannelAddress_0, SCP_FA4_IOM15_CH0_DATA, bus );
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
				bus = BUS_PL1;
				OutputMDM( MDM_PF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_0, SCP_PF1_IOM2_CH0_DATA, bus );

				// MDM PF 2
				bus = BUS_PL2;
				OutputMDM( MDM_PF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_0, SCP_PF2_IOM2_CH0_DATA, bus );
				OutputMDM( MDM_PF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_2, SCP_PF2_IOM10_CH2_DATA, bus );
		}
		return;
	}

	void SimpleFCOS_IO_GNC::InputEIU( unsigned short addr, unsigned short dataaddr, unsigned short datalen, BUS_ID busid )
	{
		unsigned int data[2];
		memset( data, 0, 2 * sizeof(unsigned int) );
		pGPC->WriteBufferAddress = dataaddr;
		pGPC->WriteBufferLength = datalen;
		pGPC->SubSystemAddress = addr;

		// build command word
		data[0] |= addr << 20;// MIA address
		data[0] |= 0b00001 << 15;// mode control
		data[0] |= (datalen - 1) << 1;// number of words
		data[0] |= (~CalcParity( data[0] )) & 1;// parity

		pGPC->_Tx( busid, data, 1 );
		return;
	}

	void SimpleFCOS_IO_GNC::OutputEIU( unsigned short addr, unsigned short dataaddr )
	{
		if (pGPC->SimpleCOMPOOL[dataaddr] == 0) return;

		unsigned int data[2];
		memset( data, 0, 2 * sizeof(unsigned int) );
		pGPC->SubSystemAddress = addr;
		pGPC->WriteBufferLength = 0;

		// build command word
		data[0] |= addr << 20;// MIA address
		data[0] |= 0b10011 << 15;// mode control
		data[0] |= (1 - 1) << 1;// number of words
		data[0] |= (~CalcParity( data[0] )) & 1;// parity

		// build command data words
		// HACK should be sending 2 data words
		data[1] |= addr << 20;// MIA address
		data[1] |= pGPC->SimpleCOMPOOL[dataaddr] << 4;// data
		data[1] |= 0b101 << 1;// SEV
		data[1] |= (~CalcParity( data[1] )) & 1;// parity

		pGPC->_Tx( BUS_FC5, data, 2 );
		pGPC->_Tx( BUS_FC6, data, 2 );
		pGPC->_Tx( BUS_FC7, data, 2 );
		pGPC->_Tx( BUS_FC8, data, 2 );
		return;
	}

	void SimpleFCOS_IO_GNC::OutputDDU( unsigned short addr, unsigned short channeladdr, unsigned short dataaddr, unsigned short datalen )
	{
		unsigned int data[32];
		memset( data, 0, 32 * sizeof(unsigned int) );
		pGPC->WriteBufferLength = 0;

		// build command word
		data[0] |= addr << 20;// MIA address
		data[0] |= channeladdr << 6;// channel
		data[0] |= (datalen - 1) << 1;// number of words
		data[0] |= (~CalcParity( data[0] )) & 1;// parity

		// build command data words
		for (unsigned int i = 1; i <= datalen; i++)
		{
			data[i] |= addr << 20;// MIA address
			data[i] |= pGPC->SimpleCOMPOOL[dataaddr + i - 1] << 4;// data
			data[i] |= 0b101 << 1;// SEV
			data[i] |= (~CalcParity( data[i] )) & 1;// parity
		}

		pGPC->_Tx( BUS_FC1, data, datalen + 1 );
		pGPC->_Tx( BUS_FC2, data, datalen + 1 );
		pGPC->_Tx( BUS_FC3, data, datalen + 1 );
		pGPC->_Tx( BUS_FC4, data, datalen + 1 );
		return;
	}

	void SimpleFCOS_IO_GNC::PollDK( const unsigned short dk )
	{
		BUS_ID bus;
		if (dk == 1) bus = BUS_DK1;
		else if (dk == 2) bus = BUS_DK2;
		else if (dk == 3) bus = BUS_DK3;
		else /*if (dk == 4)*/ bus = BUS_DK4;

		unsigned int data = 0;

		// build command word
		data |= 10 << 20;// MIA address
		data |= 0b00000 << 15;// msg type
		data |= 0b100 << 12;// subfield
		data |= 0 << 1;// number of words
		data |= (~CalcParity( data )) & 1;// parity

		pGPC->_Tx( bus, &data, 1 );
		return;
	}
}

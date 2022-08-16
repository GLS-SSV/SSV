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
2022/05/29   GLS
2022/06/04   GLS
2022/06/06   GLS
2022/06/10   GLS
2022/06/16   GLS
2022/06/23   GLS
2022/07/02   GLS
2022/08/05   GLS
********************************************/
#include "SimpleFCOS_IO.h"
#include "SimpleGPCSystem.h"


namespace dps
{
	constexpr unsigned short EIU1_Address = 17;
	constexpr unsigned short EIU2_Address = 23;
	constexpr unsigned short EIU3_Address = 24;
	constexpr unsigned short HUD1_Address = 6;
	constexpr unsigned short HUD2_Address = 9;
	constexpr unsigned short MDM_FF1_Address = 25;
	constexpr unsigned short MDM_FF2_Address = 26;
	constexpr unsigned short MDM_FF3_Address = 27;
	constexpr unsigned short MDM_FF4_Address = 28;
	constexpr unsigned short MDM_FA1_Address = 19;
	constexpr unsigned short MDM_FA2_Address = 20;
	constexpr unsigned short MDM_FA3_Address = 21;
	constexpr unsigned short MDM_FA4_Address = 22;
	constexpr unsigned short MDM_PF1_Address = 29;
	constexpr unsigned short MDM_PF2_Address = 30;

	constexpr unsigned short ModeControl_MDM_Receive = 0b1000;
	constexpr unsigned short ModeControl_MDM_Transmit = 0b1001;

	constexpr unsigned short ModuleAddress_IOM0 = 0b0000;
	constexpr unsigned short ModuleAddress_IOM1 = 0b0001;
	constexpr unsigned short ModuleAddress_IOM2 = 0b0010;
	constexpr unsigned short ModuleAddress_IOM3 = 0b0011;
	constexpr unsigned short ModuleAddress_IOM4 = 0b0100;
	constexpr unsigned short ModuleAddress_IOM5 = 0b0101;
	constexpr unsigned short ModuleAddress_IOM6 = 0b0110;
	constexpr unsigned short ModuleAddress_IOM7 = 0b0111;
	constexpr unsigned short ModuleAddress_IOM8 = 0b1000;
	constexpr unsigned short ModuleAddress_IOM9 = 0b1001;
	constexpr unsigned short ModuleAddress_IOM10 = 0b1010;
	constexpr unsigned short ModuleAddress_IOM11 = 0b1011;
	constexpr unsigned short ModuleAddress_IOM12 = 0b1100;
	constexpr unsigned short ModuleAddress_IOM13 = 0b1101;
	constexpr unsigned short ModuleAddress_IOM14 = 0b1110;
	constexpr unsigned short ModuleAddress_IOM15 = 0b1111;

	constexpr unsigned int ChannelAddress_0 = 0b00000;
	constexpr unsigned int ChannelAddress_1 = 0b00001;
	constexpr unsigned int ChannelAddress_2 = 0b00010;
	constexpr unsigned int ChannelAddress_3 = 0b00011;
	constexpr unsigned int ChannelAddress_4 = 0b00100;

	SimpleFCOS_IO::SimpleFCOS_IO( SimpleGPCSystem* _gpc )
	{
		pGPC = _gpc;
	}

	SimpleFCOS_IO::~SimpleFCOS_IO()
	{
	}

	void SimpleFCOS_IO::InputMDMDiscretes( unsigned short addr, unsigned short mode, unsigned short moduleaddr, unsigned short modulech, unsigned short memoryaddr )
	{
		SIMPLEBUS_COMMAND_WORD cw;

		pGPC->WriteBufferAddress = memoryaddr;
		pGPC->WriteBufferLength = 1;
		pGPC->SubSystemAddress = addr;
		cw.MIAaddr = pGPC->SubSystemAddress;
		cw.payload = (mode << 9) | (moduleaddr << 5) | modulech;
		cw.numwords = 0;
		pGPC->busCommand( cw, NULL );
		return;
	}

	void SimpleFCOS_IO::OutputMDMDiscretes( unsigned short addr, unsigned short mode, unsigned short moduleaddr, unsigned short modulech, unsigned short memoryaddr )
	{
		SIMPLEBUS_COMMAND_WORD cw;
		SIMPLEBUS_COMMANDDATA_WORD cdw[32];

		pGPC->SubSystemAddress = addr;
		pGPC->WriteBufferLength = 0;

		cw.MIAaddr = pGPC->SubSystemAddress;
		cw.payload = (mode << 9) | (moduleaddr << 5) | modulech;
		cw.numwords = 0;
		cdw[0].MIAaddr = pGPC->SubSystemAddress;
		cdw[0].payload = pGPC->SimpleCOMPOOL[memoryaddr];
		cdw[0].SEV = 0b101;
		pGPC->busCommand( cw, cdw );

		// reset memory location
		pGPC->SimpleCOMPOOL[memoryaddr] = 0;
		return;
	}

	void SimpleFCOS_IO::input( void )
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

		// MDM FF 2
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

		// MDM FF 3
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

		// MDM FF 4
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
		return;
	}

	void SimpleFCOS_IO::output( void )
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
				pGPC->SubSystemAddress = HUD1_Address;
				pGPC->WriteBufferLength = 0;

				cw.MIAaddr = pGPC->SubSystemAddress;
				cw.payload = 0b00001 << 9;
				cw.numwords = 13;
				for (unsigned int i = 0; i < 14; i++)
				{
					cdw[i].MIAaddr = pGPC->SubSystemAddress;
					cdw[i].payload = pGPC->SimpleCOMPOOL[SCP_DDU1_ADI + i];
					cdw[i].SEV = 0b101;
				}
				pGPC->busCommand( cw, cdw );

				// ADI, DDU 2/HUD 2
				pGPC->SubSystemAddress = HUD2_Address;
				pGPC->WriteBufferLength = 0;

				cw.MIAaddr = pGPC->SubSystemAddress;
				for (unsigned int i = 0; i < 14; i++)
				{
					cdw[i].MIAaddr = pGPC->SubSystemAddress;
					cdw[i].payload = pGPC->SimpleCOMPOOL[SCP_DDU2_ADI + i];
				}
				pGPC->busCommand( cw, cdw );

				// HSI, DDU 1/HUD 1
				pGPC->SubSystemAddress = HUD1_Address;
				pGPC->WriteBufferLength = 0;

				cw.MIAaddr = pGPC->SubSystemAddress;
				cw.payload = 0b00010 << 9;
				cw.numwords = 9;
				for (unsigned int i = 0; i < 10; i++)
				{
					cdw[i].MIAaddr = pGPC->SubSystemAddress;
					cdw[i].payload = pGPC->SimpleCOMPOOL[SCP_DDU1_HSI + i];
					cdw[i].SEV = 0b101;
				}
				pGPC->busCommand( cw, cdw );

				// HSI, DDU 2/HUD 2
				pGPC->SubSystemAddress = HUD2_Address;
				pGPC->WriteBufferLength = 0;

				cw.MIAaddr = pGPC->SubSystemAddress;
				for (unsigned int i = 0; i < 10; i++)
				{
					cdw[i].MIAaddr = pGPC->SubSystemAddress;
					cdw[i].payload = pGPC->SimpleCOMPOOL[SCP_DDU2_HSI + i];
				}
				pGPC->busCommand( cw, cdw );

				// AVVI, DDU 1/HUD 1
				pGPC->SubSystemAddress = HUD1_Address;
				pGPC->WriteBufferLength = 0;

				cw.MIAaddr = pGPC->SubSystemAddress;
				cw.payload = 0b00011 << 9;
				cw.numwords = 5;
				for (unsigned int i = 0; i < 6; i++)
				{
					cdw[i].MIAaddr = pGPC->SubSystemAddress;
					cdw[i].payload = pGPC->SimpleCOMPOOL[SCP_DDU1_AVVI + i];
					cdw[i].SEV = 0b101;
				}
				pGPC->busCommand( cw, cdw );

				// AVVI, DDU 2/HUD 2
				pGPC->SubSystemAddress = HUD2_Address;
				pGPC->WriteBufferLength = 0;

				cw.MIAaddr = pGPC->SubSystemAddress;
				for (unsigned int i = 0; i < 6; i++)
				{
					cdw[i].MIAaddr = pGPC->SubSystemAddress;
					cdw[i].payload = pGPC->SimpleCOMPOOL[SCP_DDU2_AVVI + i];
				}
				pGPC->busCommand( cw, cdw );

				// AMI, DDU 1/HUD 1
				pGPC->SubSystemAddress = HUD1_Address;
				pGPC->WriteBufferLength = 0;

				cw.MIAaddr = pGPC->SubSystemAddress;
				cw.payload = 0b00100 << 9;
				cw.numwords = 5;
				for (unsigned int i = 0; i < 6; i++)
				{
					cdw[i].MIAaddr = pGPC->SubSystemAddress;
					cdw[i].payload = pGPC->SimpleCOMPOOL[SCP_DDU1_AMI + i];
					cdw[i].SEV = 0b101;
				}
				pGPC->busCommand( cw, cdw );

				// AMI, DDU/2HUD 2
				pGPC->SubSystemAddress = HUD2_Address;
				pGPC->WriteBufferLength = 0;

				cw.MIAaddr = pGPC->SubSystemAddress;
				for (unsigned int i = 0; i < 6; i++)
				{
					cdw[i].MIAaddr = pGPC->SubSystemAddress;
					cdw[i].payload = pGPC->SimpleCOMPOOL[SCP_DDU2_AMI + i];
				}
				pGPC->busCommand( cw, cdw );

				// HUD message 1, HUD 1
				pGPC->SubSystemAddress = HUD1_Address;
				pGPC->WriteBufferLength = 0;

				cw.MIAaddr = pGPC->SubSystemAddress;
				cw.payload = 0b10001 << 9;
				cw.numwords = 30;
				for (unsigned int i = 0; i < 31; i++)
				{
					cdw[i].MIAaddr = pGPC->SubSystemAddress;
					cdw[i].payload = pGPC->SimpleCOMPOOL[SCP_HUD1_MSG1 + i];
					cdw[i].SEV = 0b101;
				}
				pGPC->busCommand( cw, cdw );

				// HUD message 1, HUD 2
				pGPC->SubSystemAddress = HUD2_Address;
				pGPC->WriteBufferLength = 0;

				cw.MIAaddr = pGPC->SubSystemAddress;
				for (unsigned int i = 0; i < 31; i++)
				{
					cdw[i].MIAaddr = pGPC->SubSystemAddress;
					cdw[i].payload = pGPC->SimpleCOMPOOL[SCP_HUD2_MSG1 + i];
				}
				pGPC->busCommand( cw, cdw );

				// HUD message 2, HUD 1
				pGPC->SubSystemAddress = HUD1_Address;
				pGPC->WriteBufferLength = 0;

				cw.MIAaddr = pGPC->SubSystemAddress;
				cw.payload = 0b10010 << 9;
				cw.numwords = 11;
				for (unsigned int i = 0; i < 12; i++)
				{
					cdw[i].MIAaddr = pGPC->SubSystemAddress;
					cdw[i].payload = pGPC->SimpleCOMPOOL[SCP_HUD1_MSG2 + i];
					cdw[i].SEV = 0b101;
				}
				pGPC->busCommand( cw, cdw );

				// HUD message 2, HUD 2
				pGPC->SubSystemAddress = HUD2_Address;
				pGPC->WriteBufferLength = 0;

				cw.MIAaddr = pGPC->SubSystemAddress;
				for (unsigned int i = 0; i < 12; i++)
				{
					cdw[i].MIAaddr = pGPC->SubSystemAddress;
					cdw[i].payload = pGPC->SimpleCOMPOOL[SCP_HUD2_MSG2 + i];
				}
				pGPC->busCommand( cw, cdw );
				break;
		}

		// MDM FF 1
		OutputMDMDiscretes( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_1, SCP_FF1_IOM2_CH1_DATA );
		OutputMDMDiscretes( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_2, SCP_FF1_IOM2_CH2_DATA );
		OutputMDMDiscretes( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM5, ChannelAddress_1, SCP_FF1_IOM5_CH1_DATA );
		OutputMDMDiscretes( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_0, SCP_FF1_IOM10_CH0_DATA );
		OutputMDMDiscretes( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_1, SCP_FF1_IOM10_CH1_DATA );
		OutputMDMDiscretes( MDM_FF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_2, SCP_FF1_IOM10_CH2_DATA );

		// MDM FF 2
		OutputMDMDiscretes( MDM_FF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_1, SCP_FF2_IOM2_CH1_DATA );
		OutputMDMDiscretes( MDM_FF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_0, SCP_FF2_IOM10_CH0_DATA );
		OutputMDMDiscretes( MDM_FF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_1, SCP_FF2_IOM10_CH1_DATA );
		OutputMDMDiscretes( MDM_FF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_2, SCP_FF2_IOM10_CH2_DATA );

		// MDM FF 3
		OutputMDMDiscretes( MDM_FF3_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_1, SCP_FF3_IOM2_CH1_DATA );
		OutputMDMDiscretes( MDM_FF3_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_2, SCP_FF3_IOM2_CH2_DATA );
		OutputMDMDiscretes( MDM_FF3_Address, ModeControl_MDM_Receive, ModuleAddress_IOM5, ChannelAddress_1, SCP_FF3_IOM5_CH1_DATA );
		OutputMDMDiscretes( MDM_FF3_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_0, SCP_FF3_IOM10_CH0_DATA );
		OutputMDMDiscretes( MDM_FF3_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_1, SCP_FF3_IOM10_CH1_DATA );
		OutputMDMDiscretes( MDM_FF3_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_2, SCP_FF3_IOM10_CH2_DATA );

		// MDM FF 4
		OutputMDMDiscretes( MDM_FF4_Address, ModeControl_MDM_Receive, ModuleAddress_IOM5, ChannelAddress_1, SCP_FF4_IOM5_CH1_DATA );
		OutputMDMDiscretes( MDM_FF4_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_0, SCP_FF4_IOM10_CH0_DATA );
		OutputMDMDiscretes( MDM_FF4_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_2, SCP_FF4_IOM10_CH2_DATA );

		// MDM PF 1
		OutputMDMDiscretes( MDM_PF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_0, SCP_PF1_IOM2_CH0_DATA );

		// MDM PF 2
		OutputMDMDiscretes( MDM_PF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_0, SCP_PF2_IOM2_CH0_DATA );
		OutputMDMDiscretes( MDM_PF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_2, SCP_PF2_IOM10_CH2_DATA );
		return;
	}

	void SimpleFCOS_IO::busRead( SIMPLEBUS_COMMANDDATA_WORD* cdw )
	{
		// save data from subsystem

		for (unsigned short i = 0; i < pGPC->WriteBufferLength; i++)
		{
			if (cdw[i].MIAaddr != pGPC->SubSystemAddress) return;// check if addr matches subsystem we're waiting data from
			pGPC->SimpleCOMPOOL[pGPC->WriteBufferAddress + i] = cdw[i].payload;
		}
		return;
	}
};

#include "SimpleFCOS_IO_SM.h"
#include "../../SimpleGPCSystem.h"


namespace dps
{
	SimpleFCOS_IO_SM::SimpleFCOS_IO_SM( SimpleGPCSystem* _gpc ):SimpleFCOS_IO( _gpc )
	{
	}

	SimpleFCOS_IO_SM::~SimpleFCOS_IO_SM()
	{
	}

	void SimpleFCOS_IO_SM::input( void )
	{
		// send data requests to subystems
		switch (pGPC->GetMajorMode())
		{
			case 201:
			case 202:
				// MDM PF 1
				InputMDMDiscretes( MDM_PF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM3, ChannelAddress_0, SCP_PF1_IOM3_CH0_DATA );
				InputMDMDiscretes( MDM_PF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM6, ChannelAddress_0, SCP_PF1_IOM6_CH0_DATA );
				InputMDMDiscretes( MDM_PF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM9, ChannelAddress_0, SCP_PF1_IOM9_CH0_DATA );

				// MDM PF 2
				InputMDMDiscretes( MDM_PF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM3, ChannelAddress_0, SCP_PF2_IOM3_CH0_DATA );
				InputMDMDiscretes( MDM_PF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM6, ChannelAddress_0, SCP_PF2_IOM6_CH0_DATA );
				InputMDMDiscretes( MDM_PF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM9, ChannelAddress_0, SCP_PF2_IOM9_CH0_DATA );

				// HACK get OI data directly
				// MDM OF 1
				InputMDMDiscretes( MDM_OF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM14, ChannelAddress_0, SCP_OF1_IOM14_CH0_DATA );
				InputMDMDiscretes( MDM_OF1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM14, ChannelAddress_1, SCP_OF1_IOM14_CH1_DATA );

				// MDM OF 2
				InputMDMDiscretes( MDM_OF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM14, ChannelAddress_0, SCP_OF2_IOM14_CH0_DATA );
				InputMDMDiscretes( MDM_OF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM14, ChannelAddress_1, SCP_OF2_IOM14_CH1_DATA );
				InputMDMDiscretes( MDM_OF2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM14, ChannelAddress_2, SCP_OF2_IOM14_CH2_DATA );

				// MDM OF 3
				//InputMDMDiscretes( MDM_OF3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM0, ChannelAddress_0, SCP_OF3_IOM0_CH0_DATA );// TODO

				// MDM OF 4
				InputMDMDiscretes( MDM_OF4_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM15, ChannelAddress_0, SCP_OF4_IOM15_CH0_DATA );

				// MDM OA 1
				//InputMDMDiscretes( MDM_OA1_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM0, ChannelAddress_0, SCP_OA1_IOM0_CH0_DATA );// TODO

				// MDM OA 2
				//InputMDMDiscretes( MDM_OA2_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM0, ChannelAddress_0, SCP_OA2_IOM0_CH0_DATA );// TODO

				// MDM OA 3
				InputMDMDiscretes( MDM_OA3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM12, ChannelAddress_0, SCP_OA3_IOM12_CH0_DATA );
				InputMDMDiscretes( MDM_OA3_Address, ModeControl_MDM_Transmit, ModuleAddress_IOM12, ChannelAddress_1, SCP_OA3_IOM12_CH1_DATA );
				break;
		}
		return;
	}

	void SimpleFCOS_IO_SM::output( void )
	{
		// send commands to subystems
		switch (pGPC->GetMajorMode())// if OPS 2, let SM command PFs
		{
			case 201:
			case 202:
				// MDM PF 1
				OutputMDMDiscretes( MDM_PF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_0, SCP_PF1_IOM2_CH0_DATA );
				OutputMDMDiscretes( MDM_PF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM7, ChannelAddress_0, SCP_PF1_IOM7_CH0_DATA );
				OutputMDMDiscretes( MDM_PF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM14, ChannelAddress_0, SCP_PF1_IOM14_CH0_DATA );
				OutputMDMDiscretes( MDM_PF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM14, ChannelAddress_2, SCP_PF1_IOM14_CH2_DATA );

				// MDM PF 2
				OutputMDMDiscretes( MDM_PF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_0, SCP_PF2_IOM2_CH0_DATA );
				OutputMDMDiscretes( MDM_PF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM7, ChannelAddress_0, SCP_PF2_IOM7_CH0_DATA );
				OutputMDMDiscretes( MDM_PF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_2, SCP_PF2_IOM10_CH2_DATA );
				OutputMDMDiscretes( MDM_PF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM14, ChannelAddress_0, SCP_PF2_IOM14_CH0_DATA );
				OutputMDMDiscretes( MDM_PF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM14, ChannelAddress_2, SCP_PF2_IOM14_CH2_DATA );
		}
		return;
	}
}

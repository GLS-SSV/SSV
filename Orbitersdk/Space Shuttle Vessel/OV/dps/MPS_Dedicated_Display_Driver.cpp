/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/04/07   GLS
2020/04/28   GLS
2020/06/20   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/05/29   GLS
2022/08/05   GLS
2022/08/15   GLS
2022/10/03   GLS
********************************************/
#include "MPS_Dedicated_Display_Driver.h"
#include "SSME_SOP.h"
#include <cassert>


namespace dps
{
	MPS_Dedicated_Display_Driver::MPS_Dedicated_Display_Driver( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "MPS_Dedicated_Display_Driver" )
	{
		return;
	}

	MPS_Dedicated_Display_Driver::~MPS_Dedicated_Display_Driver( void )
	{
		return;
	}

	void MPS_Dedicated_Display_Driver::OnPostStep( double simt, double simdt, double mjd )
	{
		if (ReadCOMPOOL_IS( SCP_ET_SEP_CMD ) == 1)
		{
			// all lights off
			AmberStatusLight[0] = false;
			AmberStatusLight[1] = false;
			AmberStatusLight[2] = false;

			RedStatusLight[0] = false;
			RedStatusLight[1] = false;
			RedStatusLight[2] = false;
		}
		else
		{
			for (int i = 1; i <= 3; i++)// red lights
			{
				if ((ReadCOMPOOL_AIS( SCP_ME_LIM_EX, i, 3 ) == 1) ||
					(ReadCOMPOOL_AIS( SCP_MESHDN, i, 3 ) == 1) ||
					(ReadCOMPOOL_AIS( SCP_MEPSTSHDN, i, 3 ) == 1))
				{
					// red light on
					RedStatusLight[i - 1] = true;
				}
				else
				{
					// red light off
					RedStatusLight[i - 1] = false;
				}
			}

			for (int i = 1; i <= 3; i++)// amber lights
			{
				if ((ReadCOMPOOL_AIS( SCP_ME_ELEC_LOCKUP, i, 3 ) == 1) ||
					(ReadCOMPOOL_AIS( SCP_ME_HYD_LOCKUP, i, 3 ) == 1) ||
					(ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, i, 3 ) == 1) ||
					(ReadCOMPOOL_AIS( SCP_ME_CMD_PATH_FAIL, i, 3 ) == 1))
				{
					// amber light on
					AmberStatusLight[i - 1] = true;
				}
				else
				{
					// amber light off
					AmberStatusLight[i - 1] = false;
				}
			}
		}

		if (AmberStatusLight[0]) WriteCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA ) | 0x0001 );
		if (AmberStatusLight[1]) WriteCOMPOOL_IS( SCP_FF2_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM2_CH1_DATA ) | 0x0001 );
		if (AmberStatusLight[2]) WriteCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA ) | 0x0001 );
		if (RedStatusLight[0]) WriteCOMPOOL_IS( SCP_FF1_IOM10_CH1_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH1_DATA ) | 0x0001 );
		if (RedStatusLight[1]) WriteCOMPOOL_IS( SCP_FF2_IOM10_CH1_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH1_DATA ) | 0x0001 );
		if (RedStatusLight[2]) WriteCOMPOOL_IS( SCP_FF3_IOM10_CH1_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH1_DATA ) | 0x0001 );
		return;
	}

	bool MPS_Dedicated_Display_Driver::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 101:
			case 102:
			case 103:
			case 104:
			case 601:
				return true;
			default:
				return false;
		}
	}
}
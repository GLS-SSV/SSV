/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2021/02/28   GLS
2021/08/23   GLS
2021/08/24   GLS
2023/09/03   GLS
********************************************/
#include "RA_SOP.h"


namespace dps
{
	static bool checkoddparity( unsigned short val )
	{
		val ^= val >> 8;
		val ^= val >> 4;
		val ^= val >> 2;
		val ^= val >> 1;
		return ((~val) & 1) == 0;
	}

	RA_SOP::RA_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "RA_SOP" )
	{
		return;
	}

	RA_SOP::~RA_SOP( void )
	{
		return;
	}

	void RA_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		unsigned short RA_ALTIN[2];
		RA_ALTIN[0] = ReadCOMPOOL_IS( SCP_FF1_IOM0_CH4_DATA );
		RA_ALTIN[1] = ReadCOMPOOL_IS( SCP_FF2_IOM0_CH4_DATA );

		for (int i = 1; i <= 2; i++)
		{
			WriteCOMPOOL_AIS( SCP_RALT_DG, i, 0, 2 );
			WriteCOMPOOL_AIS( SCP_RALT_CMLK, i, 0, 2 );

			if (RA_ALTIN[i - 1] != 0/*RA_PWR_ON[i - 1] == 1*/)// TODO find RA_PWR_ON source
			{
				bool RAPODD = checkoddparity( RA_ALTIN[i - 1] );
				if (RAPODD)
				{
					if (RA_ALTIN[i - 1] & 0x2)// validity
					{
						WriteCOMPOOL_AIS( SCP_RALT_DG, i, 1, 2 );
						if (1/*TODO not commfault*/)
						{
							WriteCOMPOOL_AIS( SCP_RALT_CMLK, i, 1, 2 );
						}
					}

					WriteCOMPOOL_VS( SCP_RA_ALTO, i, static_cast<float>((RA_ALTIN[i - 1] & 0x7FFC) >> 2), 2 );
					//RA_TIME = CLOCK;
				}
			}
		}
		return;
	}

	bool RA_SOP::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 305:
			case 603:
			case 801:
				return true;
			default:
				return false;
		}
	}
}

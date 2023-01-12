/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2021/02/28   GLS
2021/08/23   GLS
2021/08/24   GLS
********************************************/
#include "RadarAltimeter_SOP.h"


namespace dps
{
	RadarAltimeter_SOP::RadarAltimeter_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "RadarAltimeter_SOP" )
	{
		return;
	}

	RadarAltimeter_SOP::~RadarAltimeter_SOP( void )
	{
		return;
	}

	void RadarAltimeter_SOP::Realize( void )
	{
		return;
	}

	void RadarAltimeter_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		bool RA1_CDR = (ReadCOMPOOL_IS( SCP_FF1_IOM12_CH0_DATA ) & 0x2000) != 0;
		bool RA1_PLT = (ReadCOMPOOL_IS( SCP_FF2_IOM12_CH0_DATA ) & 0x2000) != 0;

		unsigned short tmp = ReadCOMPOOL_IS( SCP_FF1_IOM0_CH4_DATA );
		unsigned short RA1_control = tmp & 0x0001;
		unsigned short RA1_validity = (tmp & 0x0002) >> 1;
		unsigned short RA1_data = (tmp & 0x7FFC) >> 2;
		unsigned short RA1_parity = (tmp & 0x8000) >> 15;
		tmp = ReadCOMPOOL_IS( SCP_FF2_IOM0_CH4_DATA );
		unsigned short RA2_control = tmp & 0x0001;
		unsigned short RA2_validity = (tmp & 0x0002) >> 1;
		unsigned short RA2_data = (tmp & 0x7FFC) >> 2;
		unsigned short RA2_parity = (tmp & 0x8000) >> 15;

		unsigned short RA_CDR_data = 0;
		unsigned short RA_CDR_val = 0;
		unsigned short RA_PLT_data = 0;
		unsigned short RA_PLT_val = 0;

		if (RA1_CDR)
		{
			RA_CDR_data = RA1_data;
			RA_CDR_val = RA1_validity;
		}
		else
		{
			RA_CDR_data = RA2_data;
			RA_CDR_val = RA2_validity;
		}

		if (RA1_PLT)
		{
			RA_PLT_data = RA1_data;
			RA_PLT_val = RA1_validity;
		}
		else
		{
			RA_PLT_data = RA2_data;
			RA_PLT_val = RA2_validity;
		}

		// HACK correct for wheels (not sure where this is done)
		RA_CDR_data = max(0, RA_CDR_data - 20);
		RA_PLT_data = max(0, RA_PLT_data - 20);

		WriteCOMPOOL_IS( SCP_RA_DATA_CDR_SEL, RA_CDR_data );
		WriteCOMPOOL_IS( SCP_RA_VALIDITY_CDR_SEL, RA_CDR_val );
		WriteCOMPOOL_IS( SCP_RA_DATA_PLT_SEL, RA_PLT_data );
		WriteCOMPOOL_IS( SCP_RA_VALIDITY_PLT_SEL, RA_PLT_val );
		return;
	}

	bool RadarAltimeter_SOP::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void RadarAltimeter_SOP::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	bool RadarAltimeter_SOP::OnMajorModeChange( unsigned int newMajorMode )
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

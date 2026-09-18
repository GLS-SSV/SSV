/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/04/07   GLS
2020/06/20   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
2025/07/20   GLS
2026/09/18   GLS
********************************************/
#include "RPTA_SOP.h"
#include "GNCUtilities.h"
#include <cassert>


namespace dps
{
	RPTA_SOP::RPTA_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "RPTA_SOP" )
	{
		return;
	}

	RPTA_SOP::~RPTA_SOP( void )
	{
		return;
	}

	void RPTA_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		RPTA_COMP();

		RPTA_STA_SEL();

		RPTA_DB();

		YAW_TRIM();
		return;
	}

	bool RPTA_SOP::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void RPTA_SOP::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	void RPTA_SOP::RPTA_COMP( void )
	{
		float DRCMDR = ReadCOMPOOL_SS( SCP_DRCMDR );
		float DRPLT = ReadCOMPOOL_SS( SCP_DRPLT );

		// LEFT RPTA
		DRCMDRC = (DRCMDR * ReadCOMPOOL_SS( SCP_CRPTC )) + ReadCOMPOOL_SS( SCP_KRPTC );

		// RIGHT RPTA
		DRPLTC = (DRPLT * ReadCOMPOOL_SS( SCP_CRPTP )) + ReadCOMPOOL_SS( SCP_KRPTP );
		return;
	}

	void RPTA_SOP::RPTA_STA_SEL( void )
	{
		unsigned short L_RPTA_DG = ReadCOMPOOL_IS( SCP_L_RPTA_DG );
		unsigned short R_RPTA_DG = ReadCOMPOOL_IS( SCP_R_RPTA_DG );

		if ((R_RPTA_DG == 1) && (L_RPTA_DG == 1))
		{
			if (fabs( DRCMDRC ) >= fabs( DRPLTC ))
			{
				DRSEL = DRCMDRC;
			}
			else
			{
				DRSEL = DRPLTC;
			}
		}
		else
		{
			if (R_RPTA_DG == 1)
			{
				DRSEL = DRPLTC;
			}
			else
			{
				if (L_RPTA_DG == 1)
				{
					DRSEL = DRCMDRC;
				}
				else
				{
					DRSEL = 0.0;
				}
			}
		}
		return;
	}

	void RPTA_SOP::RPTA_DB( void )
	{
		WriteCOMPOOL_SS( SCP_DRMAN, DEADBAND( DRSEL, ReadCOMPOOL_SS( SCP_DRMDB ) ) );
		return;
	}

	void RPTA_SOP::YAW_TRIM( void )
	{
		bool DETYPS[2];
		bool DETYMS[2];
		bool INHIBIT[2];
		DETYPS[0] = ReadCOMPOOL_AIS( SCP_DETYPS, 1, 2 );
		DETYPS[1] = ReadCOMPOOL_AIS( SCP_DETYPS, 2, 2 );
		DETYMS[0] = ReadCOMPOOL_AIS( SCP_DETYMS, 1, 2 );
		DETYMS[1] = ReadCOMPOOL_AIS( SCP_DETYMS, 2, 2 );
		INHIBIT[0] = ReadCOMPOOL_AIS( SCP_DISABL, 1, 2 );
		INHIBIT[1] = ReadCOMPOOL_AIS( SCP_DISABL, 2, 2 );

		bool DETYP = (DETYPS[0] && !INHIBIT[0]) || (DETYPS[1] && !INHIBIT[1]);

		bool DETYM = (DETYMS[0] && !INHIBIT[0]) || (DETYMS[1] && !INHIBIT[1]);

		// yaw trim cmd
		WriteCOMPOOL_IS( SCP_DRT, static_cast<int>(DETYP) - static_cast<int>(DETYM) );
		return;
	}
}

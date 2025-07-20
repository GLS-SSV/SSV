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
********************************************/
#include "RPTA_SOP.h"
#include "RPTA_RM.h"
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

	void RPTA_SOP::Realize( void )
	{
		pRPTA_RM = dynamic_cast<RPTA_RM*>(FindSoftware( "RPTA_RM" ));
		assert( (pRPTA_RM != NULL) && "RPTA_SOP::Realize.pRPTA_RM" );
		return;
	}

	void RPTA_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		double DRMAN = 0.0;
		double L = 0.0;
		bool DG_L = false;
		double R = 0.0;
		bool DG_R = false;

		// get data from RM
		pRPTA_RM->GetRPTAData_L( L, DG_L );
		pRPTA_RM->GetRPTAData_R( R, DG_R );

		// convert to degrees (TODO should be [-22.9, +22.8])
		L *= 22.8;// [-22.8, +22.8]
		R *= 22.8;// [-22.8, +22.8]

		// check data good flag
		if (DG_L == false) L = 0.0;
		if (DG_R == false) R = 0.0;

		// output largest magnitude cmd
		if (fabs( L ) > fabs( R )) DRMAN = L;// output will be L if they are symmetrical
		else DRMAN = R;

		// 1.125º deadband
		if (fabs( DRMAN ) < 1.125) DRMAN = 0.0;

		WriteCOMPOOL_SS( SCP_DRMAN, static_cast<float>(DRMAN) );
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

	bool RPTA_SOP::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 304:
			case 305:
			case 602:
			case 603:
				return true;
			default:
				return false;
		}
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

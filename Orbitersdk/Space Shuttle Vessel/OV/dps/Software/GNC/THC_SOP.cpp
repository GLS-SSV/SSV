/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/04/07   GLS
2020/06/20   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/06/04   GLS
2023/06/03   GLS
2026/09/18   GLS
********************************************/
#include "THC_SOP.h"
#include <cassert>


namespace dps
{
	THC_SOP::THC_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "THC_SOP" )
	{
		return;
	}

	THC_SOP::~THC_SOP( void )
	{
		return;
	}

	void THC_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		THC_TRANS();
		THC_STA_SEL();
		return;
	}

	bool THC_SOP::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void THC_SOP::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	void THC_SOP::THC_TRANS( void )
	{
		unsigned short SENS_SW = ReadCOMPOOL_IS( SCP_SENSE_SW );
		// TRANSFORMS Y CMDS
		THC_ATP[2 - 1] = ReadCOMPOOL_AIS( SCP_THC_ASP, 3, 3 );

		THC_ATN[2 - 1] = ReadCOMPOOL_AIS( SCP_THC_ASN, 3, 3 );

		THC_ATP[1 - 1] = (ReadCOMPOOL_AIS( SCP_THC_ASN, 1, 3 ) && SENS_SW) || (ReadCOMPOOL_AIS( SCP_THC_ASN, 2, 3 ) && !SENS_SW);

		THC_ATN[1 - 1] = (ReadCOMPOOL_AIS( SCP_THC_ASP, 1, 3 ) && SENS_SW) || (ReadCOMPOOL_AIS( SCP_THC_ASP, 2, 3 ) && !SENS_SW);

		THC_ATP[3 - 1] = (ReadCOMPOOL_AIS( SCP_THC_ASP, 2, 3 ) && SENS_SW) || (ReadCOMPOOL_AIS( SCP_THC_ASN, 1, 3 ) && !SENS_SW);

		THC_ATN[3 - 1] = (ReadCOMPOOL_AIS( SCP_THC_ASN, 2, 3 ) && SENS_SW) || (ReadCOMPOOL_AIS( SCP_THC_ASP, 1, 3 ) && !SENS_SW);
		return;
	}

	void THC_SOP::THC_STA_SEL( void )
	{
		// THC + X
		short THCXP = THC_ATP[1 - 1] || ReadCOMPOOL_AIS( SCP_THC_FSP, 1, 3 );

		// THC - X
		short THCXN = THC_ATN[1 - 1] || ReadCOMPOOL_AIS( SCP_THC_FSN, 1, 3 );

		// THC + Y
		short THCYP = THC_ATP[2 - 1] || ReadCOMPOOL_AIS( SCP_THC_FSP, 2, 3 );

		// THC - Y
		short THCYN = THC_ATN[2 - 1] || ReadCOMPOOL_AIS( SCP_THC_FSN, 2, 3 );

		// THC + Z
		short THCZP = THC_ATP[3 - 1] || ReadCOMPOOL_AIS( SCP_THC_FSP, 3, 3 );

		// THC - Z
		short THCZN = THC_ATN[3 - 1] || ReadCOMPOOL_AIS( SCP_THC_FSN, 3, 3 );

		// X TRANS CMD
		WriteCOMPOOL_AIS( SCP_THC, 1, THCXP - THCXN, 3 );

		// Y TRANS CMD
		WriteCOMPOOL_AIS( SCP_THC, 2, THCYP - THCYN, 3 );

		// Z TRANS CMD
		WriteCOMPOOL_AIS( SCP_THC, 3, THCZP - THCZN, 3 );
		return;
	}
}

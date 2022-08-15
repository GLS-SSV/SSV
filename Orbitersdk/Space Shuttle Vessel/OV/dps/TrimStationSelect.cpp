#include "TrimStationSelect.h"
#include <MathSSV.h>


namespace dps
{
	TrimStationSelect::TrimStationSelect( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "TrimStationSelect" )
	{
		return;
	}

	TrimStationSelect::~TrimStationSelect( void )
	{
		return;
	}

	void TrimStationSelect::OnPreStep( double simt, double simdt, double mjd )
	{
		unsigned short LH_RHC_TRIM_INHIBIT = ReadCOMPOOL_IS( SCP_LH_RHC_TRIM_INHIBIT );
		unsigned short RH_RHC_TRIM_INHIBIT = ReadCOMPOOL_IS( SCP_RH_RHC_TRIM_INHIBIT );

		short DETM_RHC = 0;
		short DATM_RHC = 0;
		short DETM_PAN = 0;
		short DATM_PAN = 0;
		short DRT = 0;

		if (LH_RHC_TRIM_INHIBIT == 0)
		{
			DATM_RHC = static_cast<short>(ReadCOMPOOL_IS( SCP_LH_RHC_PLUS_ROLL_TRIM )) - static_cast<short>(ReadCOMPOOL_IS( SCP_LH_RHC_MINUS_ROLL_TRIM ));
			DETM_PAN = static_cast<short>(ReadCOMPOOL_IS( SCP_LH_PLUS_PITCH_TRIM )) - static_cast<short>(ReadCOMPOOL_IS( SCP_LH_MINUS_PITCH_TRIM ));
			DATM_PAN = static_cast<short>(ReadCOMPOOL_IS( SCP_LH_PLUS_ROLL_TRIM )) - static_cast<short>(ReadCOMPOOL_IS( SCP_LH_MINUS_ROLL_TRIM ));
			DRT = static_cast<short>(ReadCOMPOOL_IS( SCP_LH_PLUS_YAW_TRIM )) - static_cast<short>(ReadCOMPOOL_IS( SCP_LH_MINUS_YAW_TRIM ));
		}

		// special logic for LH RHC pitch down trim for derotation
		if ((ReadCOMPOOL_IS( SCP_WOWLON ) == 1) && (ReadCOMPOOL_IS( SCP_ROLLOUT ) == 0))
		{
			DETM_RHC = -static_cast<short>(ReadCOMPOOL_IS( SCP_LH_RHC_MINUS_PITCH_TRIM ));
		}
		else if (LH_RHC_TRIM_INHIBIT == 0)
		{
			DETM_RHC = static_cast<short>(ReadCOMPOOL_IS( SCP_LH_RHC_PLUS_PITCH_TRIM )) - static_cast<short>(ReadCOMPOOL_IS( SCP_LH_RHC_MINUS_PITCH_TRIM ));
		}

		if (RH_RHC_TRIM_INHIBIT == 0)
		{
			DETM_RHC += static_cast<short>(ReadCOMPOOL_IS( SCP_RH_RHC_PLUS_PITCH_TRIM )) - static_cast<short>(ReadCOMPOOL_IS( SCP_RH_RHC_MINUS_PITCH_TRIM ));
			DATM_RHC += static_cast<short>(ReadCOMPOOL_IS( SCP_RH_RHC_PLUS_ROLL_TRIM )) - static_cast<short>(ReadCOMPOOL_IS( SCP_RH_RHC_MINUS_ROLL_TRIM ));
			DETM_PAN += static_cast<short>(ReadCOMPOOL_IS( SCP_RH_PLUS_PITCH_TRIM )) - static_cast<short>(ReadCOMPOOL_IS( SCP_RH_MINUS_PITCH_TRIM ));
			DATM_PAN += static_cast<short>(ReadCOMPOOL_IS( SCP_RH_PLUS_ROLL_TRIM )) - static_cast<short>(ReadCOMPOOL_IS( SCP_RH_MINUS_ROLL_TRIM ));
			DRT += static_cast<short>(ReadCOMPOOL_IS( SCP_RH_PLUS_YAW_TRIM )) - static_cast<short>(ReadCOMPOOL_IS( SCP_RH_MINUS_YAW_TRIM ));
		}

		WriteCOMPOOL_IS( SCP_DETM_RHC, rangeint( -1, DETM_RHC, 1 ) );
		WriteCOMPOOL_IS( SCP_DATM_RHC, rangeint( -1, DATM_RHC, 1 ) );
		WriteCOMPOOL_IS( SCP_DETM_PAN, rangeint( -1, DETM_PAN, 1 ) );
		WriteCOMPOOL_IS( SCP_DATM_PAN, rangeint( -1, DATM_PAN, 1 ) );
		WriteCOMPOOL_IS( SCP_DRT, rangeint( -1, DRT, 1 ) );
		return;
	}

	bool TrimStationSelect::OnMajorModeChange( unsigned int newMajorMode )
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
}

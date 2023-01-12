#include "BF_Slew_SOP.h"


namespace dps
{
	BF_Slew_SOP::BF_Slew_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "BF_Slew_SOP" )
	{
		return;
	}

	BF_Slew_SOP::~BF_Slew_SOP( void )
	{
		return;
	}

	void BF_Slew_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		short lh = static_cast<short>(ReadCOMPOOL_IS( SCP_LH_BODY_FLAP_DOWN )) - static_cast<short>(ReadCOMPOOL_IS( SCP_LH_BODY_FLAP_UP ));
		short rh = static_cast<short>(ReadCOMPOOL_IS( SCP_RH_BODY_FLAP_DOWN )) - static_cast<short>(ReadCOMPOOL_IS( SCP_RH_BODY_FLAP_UP ));

		short DBFMAN;
		if (lh != 0)
		{
			if (rh != 0)
			{
				if (lh != rh)
				{
					DBFMAN = -1;// output up cmd for conflicting signals
				}
				else
				{
					DBFMAN = lh;
				}
			}
			else
			{
				DBFMAN = lh;
			}
		}
		else
		{
			DBFMAN = rh;
		}
		WriteCOMPOOL_IS( SCP_DBFMAN, DBFMAN );
		return;
	}

	bool BF_Slew_SOP::OnMajorModeChange( unsigned int newMajorMode )
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

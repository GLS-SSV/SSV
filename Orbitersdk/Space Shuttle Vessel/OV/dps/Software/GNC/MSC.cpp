#include "MSC.h"
#include "..\..\..\Atlantis.h"


namespace dps
{
	MSC::MSC( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "MSC" ),
		SRBSepSequence(false),tSRBSep(-1)
	{
		return;
	}

	MSC::~MSC( void )
	{
		return;
	}

	void MSC::OnPreStep( double simt, double simdt, double mjd )
	{
		// schedule SRB SEP SEQ
		if ((ReadCOMPOOL_IS( SCP_MM_CODE_102 ) == 1) && (SRBSepSequence == false))// TODO add MECO false check
		{
			if (STS()->GetMET() >= ReadCOMPOOL_SS( SCP_SRB_SEP_SEQUENCE_START_TIME ))
			{
				SCHEDULE( "SRBSepSequence" );
				SRBSepSequence = true;
			}
		}

		// handle 
		if (ReadCOMPOOL_IS( SCP_MM_CODE_103 ) == 1)
		{
			if (tSRBSep < 0.0)
			{
				tSRBSep = STS()->GetMET();
			}
			else if (ReadCOMPOOL_IS( SCP_GUIDANCE_INITIATE ) == 0)
			{
				if (STS()->GetMET() >= (tSRBSep + 4.0))// TODO CGGS_GUID_INITIATION_DELAY I-Load???
				{
					WriteCOMPOOL_IS( SCP_GUIDANCE_INITIATE, 1 );
				}
			}
		}

		

		/*if (ReadCOMPOOL_IS( SCP_BURN_ENABLE ) == 1)
		{
			// re-init OMS RM
			WriteCOMPOOL_IS( SCP_OMS_ENGINE_FDI_INIT_FLAG, 1 );
			WriteCOMPOOL_IS( SCP_OMS_ACT_FDI_INIT_FLAG, 1 );

			// fire OMS
			pGPC->SCHEDULE( "OMS_FIRE_SEQ" );
			WriteCOMPOOL_IS( SCP_BURN_ENABLE, 0 );
		}*/


		// MPS DUMP: MECO confirmed plus an I-load time delay and continues until OPS 2 or 3 transition.

		// OMS Assist
		/*if (OMSASS == 1)
		{
			if ((STS()->GetMET() >= (tSRBSep + 10)) && (STS()->GetMET() < (tSRBSep + 10 + NOMTM)))
			{
				OMSCommand[LEFT].SetLine();
				OMSCommand[RIGHT].SetLine();
			}
			else
			{
				OMSCommand[LEFT].ResetLine();
				OMSCommand[RIGHT].ResetLine();
			}
		}*/
		return;
	}
}

#include "GPC_RECONFIG.h"
#include "MC_1.h"
#include "MC_2.h"
#include "MC_3.h"
#include "MC_4.h"
#include "MC_8.h"
#include "MC_9.h"


namespace dps
{
	GPC_RECONFIG::GPC_RECONFIG( SimpleGPCSystem* pGPC ):SimpleGPCSoftware( pGPC, "GPC_RECONFIG" ),
		pGPC(pGPC), reconf_time(-1.0)
	{
		return;
	}

	GPC_RECONFIG::~GPC_RECONFIG( void )
	{
		return;
	}

	void GPC_RECONFIG::OnPreStep( double simt, double simdt, double mjd )
	{
		// kill exiting MC
		if (reconf_time < 0.0)
		{
			if (pGPC->pMC)
			{
				delete pGPC->pMC;
				pGPC->pMC = NULL;
			}

			for (unsigned int i = 0; i < pGPC->vCOMSUB.size(); i++)
			{
				delete pGPC->vCOMSUB[i];
			}
			pGPC->vCOMSUB.clear();

			reconf_time = 5.0;
			return;
		}

		// wait for a while
		reconf_time -= simdt;

		// load new MC
		if (reconf_time <= 0.0)
		{
			bool ok = true;
			if (LoadMC( ReadCOMPOOL_IS( SCP_CZ2V_REC_GRT_INDEX ), pGPC ) == false)
			{
				ok = false;
				WriteCOMPOOL_IS( SCP_CZ2V_REC_XERR, 101 );
			}

			if (ok)
			{
				pGPC->pMC->Init( pGPC->vCOMSUB, pGPC->vDFB );

				WriteCOMPOOL_IS( SCP_CZ2V_REC_XERR, 100 );

				SCP_MACT CZ1V_D_MACT;
				ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, ReadCOMPOOL_IS( SCP_CZ2V_REC_DEU ), &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
				CZ1V_D_MACT.CZ1B_D_FLAGS |= 0x0010;
				WriteCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, ReadCOMPOOL_IS( SCP_CZ2V_REC_DEU ), &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );

				WriteCOMPOOL_AIS( SCP_CZ1E_D_MACT_EVTS, ReadCOMPOOL_IS( SCP_CZ2V_REC_DEU ), 1, 4 );

				WriteCOMPOOL_IS( SCP_CDME_APP_SERVICE, 1 );
			}

			// good night
			pGPC->CANCEL( "GPC_RECONFIG" );
		}
		return;
	}

	bool GPC_RECONFIG::LoadMC( const unsigned short mc, SimpleGPCSystem* pGPC )
	{
		switch (mc)
		{
			case 1:
				pGPC->pMC = new MC_1( pGPC );
				break;
			case 2:
				pGPC->pMC = new MC_2( pGPC );
				break;
			case 3:
				pGPC->pMC = new MC_3( pGPC );
				break;
			case 4:
				pGPC->pMC = new MC_4( pGPC );
				break;
			case 8:
				pGPC->pMC = new MC_8( pGPC );
				break;
			case 9:
				pGPC->pMC = new MC_9( pGPC );
				break;
			default:
				// kaput
				return false;
		}

		return true;
	}
}

#include "AIE_SIP.h"
#include "ICC_Interface.h"


namespace dps
{
	AIE_SIP::AIE_SIP( SimpleGPCSystem* pGPC ):SimpleGPCSoftware( pGPC, "AIE_SIP" ),
		pGPC(pGPC)
	{
		return;
	}

	AIE_SIP::~AIE_SIP( void )
	{
		return;
	}

	void AIE_SIP::OnPreStep( double simt, double simdt, double mjd )
	{
		ICC_Interface* pICC = dynamic_cast<ICC_Interface*>(pGPC->GetCOMSUB( "ICC_Interface" ));
		pICC->DME_ICC_ROUT();
		return;
	}
}

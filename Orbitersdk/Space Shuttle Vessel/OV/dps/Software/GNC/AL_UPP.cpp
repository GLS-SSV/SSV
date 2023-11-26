/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2020/08/24   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/12/29   GLS
2022/03/24   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/12/01   indy91
2022/12/23   GLS
2023/11/26   GLS
********************************************/
#include "AL_UPP.h"
#include "Entry_UPP.h"
#include "../../../Atlantis.h"
#include <EngConst.h>


namespace dps
{
	AL_UPP::AL_UPP( SimpleGPCSystem* _gpc ):SimpleGPCSoftware( _gpc, "AL_UPP" )
	{
		return;
	}

	AL_UPP::~AL_UPP( void )
	{
		return;
	}

	void AL_UPP::Realize( void )
	{
		pEntry_UPP = dynamic_cast<Entry_UPP*>(FindSoftware( "Entry_UPP" ));
		return;
	}

	void AL_UPP::OnPreStep( double simt, double simdt, double mjd )
	{
		if (ReadCOMPOOL_IS( SCP_TG_END ) == 0) return;

		pEntry_UPP->GUIDECOMP();

		double weight = STS()->GetMass();
		WriteCOMPOOL_SS( SCP_WEIGHT, static_cast<float>(weight * KG2LBM * LBS2SL) );
		return;
	}

	bool AL_UPP::OnMajorModeChange( unsigned int newMajorMode )
	{
		if (newMajorMode == 305) return true;
		else return false;
	}
}

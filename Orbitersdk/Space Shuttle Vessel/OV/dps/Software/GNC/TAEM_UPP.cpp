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
#include "TAEM_UPP.h"
#include "Entry_UPP.h"
#include "../../../Atlantis.h"
#include <EngConst.h>


namespace dps
{
	TAEM_UPP::TAEM_UPP( SimpleGPCSystem* _gpc ):SimpleGPCSoftware( _gpc, "TAEM_UPP" )
	{
		return;
	}

	TAEM_UPP::~TAEM_UPP( void )
	{
		return;
	}

	void TAEM_UPP::Realize( void )
	{
		pEntry_UPP = dynamic_cast<Entry_UPP*>(FindSoftware( "Entry_UPP" ));
		return;
	}

	void TAEM_UPP::OnPreStep( double simt, double simdt, double mjd )
	{
		if (ReadCOMPOOL_IS( SCP_TG_END ) == 1) return;

		pEntry_UPP->H_HDOT_ACCVERT();
		pEntry_UPP->GUIDECOMP();

		double weight = STS()->GetMass();
		WriteCOMPOOL_SS( SCP_WEIGHT, static_cast<float>(weight * KG2LBM * LBS2SL) );
		return;
	}

	bool TAEM_UPP::OnMajorModeChange( unsigned int newMajorMode )
	{
		if (newMajorMode == 305) return true;
		else return false;
	}
}

/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/04/07   GLS
2020/04/28   GLS
2020/05/08   GLS
2020/06/20   GLS
2020/06/28   GLS
2020/08/24   GLS
2021/06/18   GLS
2021/06/26   GLS
2021/06/28   GLS
2021/07/31   GLS
2021/08/14   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/27   GLS
2021/12/28   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/02/14   GLS
2022/03/24   GLS
2022/06/04   GLS
2022/06/06   GLS
2022/08/05   GLS
********************************************/
#include "GeneralDisplays.h"


namespace dps
{
	GeneralDisplays::GeneralDisplays( SimpleGPCSystem* _gpc, const string& _ident ):SimpleGPCSoftware( _gpc, _ident )
	{
		return;
	}

	GeneralDisplays::~GeneralDisplays()
	{
	}

	void GeneralDisplays::Realize( void )
	{
		return;
	}

	void GeneralDisplays::OnPreStep( double simt, double simdt, double mjd )
	{
		return;
	}
};

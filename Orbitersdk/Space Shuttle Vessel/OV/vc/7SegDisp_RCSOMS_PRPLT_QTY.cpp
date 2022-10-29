/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/08/24   GLS
2022/01/10   GLS
2022/02/17   GLS
2022/09/29   GLS
********************************************/
#include "7SegDisp_RCSOMS_PRPLT_QTY.h"
#include "../Atlantis.h"


namespace vc
{
	_7SegDisp_RCSOMS_PRPLT_QTY::_7SegDisp_RCSOMS_PRPLT_QTY( Atlantis* _sts, const std::string& _ident ):_7SegDisp( _sts, _ident )
	{
	}

	_7SegDisp_RCSOMS_PRPLT_QTY::~_7SegDisp_RCSOMS_PRPLT_QTY()
	{
	}

	void _7SegDisp_RCSOMS_PRPLT_QTY::Realize( void )
	{
		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "O3_Timer_OMSRCS", 16 );
		pRCSOMS_PRPLT_QTY_OMSFUEL.Connect( pBundle, 2 );
		pRCSOMS_PRPLT_QTY_OMSOXID.Connect( pBundle, 3 );
		pRCSOMS_PRPLT_QTY_LOWEST.Connect( pBundle, 4 );
		pRCSOMS_PRPLT_QTY_RCSFUEL.Connect( pBundle, 5 );
		pRCSOMS_PRPLT_QTY_RCSOXID.Connect( pBundle, 6 );
		return;
	}

	void _7SegDisp_RCSOMS_PRPLT_QTY::Controller( void )
	{
		short qtyL = 0;
		short qtyF = 0;
		short qtyR = 0;

		if (pRCSOMS_PRPLT_QTY_RCSOXID.IsSet())
		{
			qtyL = min( 99, static_cast<short>(STS()->GetPropellantLevel( STS()->ph_lrcs )) );
			qtyF = min( 99, static_cast<short>(STS()->GetPropellantLevel( STS()->ph_frcs )) );
			qtyR = min( 99, static_cast<short>(STS()->GetPropellantLevel( STS()->ph_rrcs )) );
		}
		else if (pRCSOMS_PRPLT_QTY_RCSFUEL.IsSet())
		{
			qtyL = min( 99, static_cast<short>(STS()->GetPropellantLevel( STS()->ph_lrcs )) );
			qtyF = min( 99, static_cast<short>(STS()->GetPropellantLevel( STS()->ph_frcs )) );
			qtyR = min( 99, static_cast<short>(STS()->GetPropellantLevel( STS()->ph_rrcs )) );
		}
		else if (pRCSOMS_PRPLT_QTY_LOWEST.IsSet())
		{
			qtyL = min( 99, static_cast<short>(STS()->GetPropellantLevel( STS()->ph_lrcs )) );
			qtyF = min( 99, static_cast<short>(STS()->GetPropellantLevel( STS()->ph_frcs )) );
			qtyR = min( 99, static_cast<short>(STS()->GetPropellantLevel( STS()->ph_rrcs )) );
		}
		else if (pRCSOMS_PRPLT_QTY_OMSOXID.IsSet())
		{
			qtyL = min( 99, static_cast<short>(STS()->GetPropellantLevel( STS()->ph_loms )) );
			qtyF = min( 99, static_cast<short>(STS()->GetPropellantLevel( STS()->ph_koms )) );
			qtyR = min( 99, static_cast<short>(STS()->GetPropellantLevel( STS()->ph_roms )) );
		}
		else if (pRCSOMS_PRPLT_QTY_OMSFUEL.IsSet())
		{
			qtyL = min( 99, static_cast<short>(STS()->GetPropellantLevel( STS()->ph_loms )) );
			qtyF = min( 99, static_cast<short>(STS()->GetPropellantLevel( STS()->ph_koms )) );
			qtyR = min( 99, static_cast<short>(STS()->GetPropellantLevel( STS()->ph_roms )) );
		}

		next_state[5] = qtyL / 10;
		next_state[4] = qtyL % 10;
		next_state[3] = qtyF / 10;
		next_state[2] = qtyF % 10;
		next_state[1] = qtyR / 10;
		next_state[0] = qtyR % 10;
		return;
	}
}

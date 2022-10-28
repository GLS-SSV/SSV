/******* SSV File Modification Notice *******
Date         Developer
2020/06/14   GLS
2020/06/20   GLS
2021/08/24   GLS
2022/09/29   GLS
********************************************/
#include "BasicMechMeter.h"
#include "../Atlantis.h"


namespace vc
{
	BasicMechMeter::BasicMechMeter( Atlantis* _sts, const string& _ident ):AtlantisVCComponent( _sts, _ident )
	{
		anim = (UINT)(-1);
		grpIndex = (UINT)(-1);
	}

	BasicMechMeter::~BasicMechMeter()
	{
	}

	void BasicMechMeter::DefineNeedleGroup( UINT _grpIndex )
	{
		grpIndex = _grpIndex;
		return;
	}

	void BasicMechMeter::SetMotionRange( double range )
	{
		motionrange = range;
		return;
	}

	void BasicMechMeter::SetInput( DiscreteBundle* pBundle, unsigned short usLine )
	{
		input.Connect( pBundle, usLine );
		return;
	}
}

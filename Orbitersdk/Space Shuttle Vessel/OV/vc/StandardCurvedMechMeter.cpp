/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "StandardCurvedMechMeter.h"
#include "../Atlantis.h"
#include <MathSSV.h>


namespace vc
{
	StandardCurvedMechMeter::StandardCurvedMechMeter( Atlantis* _sts, const string& _ident ):BasicMechMeter( _sts, _ident )
	{
		needle_rot = NULL;
	}

	StandardCurvedMechMeter::~StandardCurvedMechMeter()
	{
		if (needle_rot) delete needle_rot;
	}

	void StandardCurvedMechMeter::DefineVCAnimations( UINT vc_idx )
	{
#if _DEBUG
		oapiWriteLogV( "Standard Curved Mech Meter[%s]:\tDefine VC Animations()", GetQualifiedIdentifier().c_str() );
#endif

		needle_rot = new MGROUP_ROTATE( vc_idx, &grpIndex, 1, GetReference(), GetDirection(), (float)(motionrange * RAD) );
		anim = STS()->CreateAnimation( InitialAnimState() );
		STS()->AddAnimationComponent( anim, 0.0, 1.0, needle_rot, NULL );
		return;
	}

	void StandardCurvedMechMeter::OnPostStep( double simt, double simdt, double mjd )
	{
		double tgt = range( 0.0, input.GetVoltage() / 5.0, 1.0 );
		double cur = STS()->GetAnimation( anim );
		double out = (0.5 * (tgt - cur)) + cur;
		out = range( 0.0, range( cur - (2 * simdt), out, cur + (2 * simdt) ), 1.0 );// limit needle speed to 2s from end to end

		STS()->SetAnimation( anim, out );
		return;
	}
}

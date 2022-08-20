#include "PushWheel.h"
#include "../Atlantis.h"
#include "..\..\SSVSound.h"
#include "MathSSV.h"
#include <cassert>


namespace vc
{
	constexpr double PISTON_MOVEMENT_RANGE = 0.02;// [m]


	PushWheel::PushWheel( Atlantis* _sts, const std::string& _ident ):ThumbWheel( _sts, _ident ),
	tgtpistonup(0), tgtpistondn(0)
	{
		piston_up = NULL;
		piston_dn = NULL;
	}

	PushWheel::~PushWheel()
	{
		if (piston_up) delete piston_up;
		if (piston_dn) delete piston_dn;
	}

	void PushWheel::DefinePusherGroups( UINT _grpIndexUp, UINT _grpIndexDn )
	{
		grpIndexUp = _grpIndexUp;
		grpIndexDn = _grpIndexDn;
		return;
	}

	void PushWheel::DefineVCAnimations( UINT vc_idx )
	{
		assert( bHasDirection && "PushWheel.bHasDirection" );
#if _DEBUG
		oapiWriteLogV( "Circuit Breaker[%s]:\tDefine VC Animations()", GetQualifiedIdentifier().c_str() );
#endif

		piston_up = new MGROUP_TRANSLATE( vc_idx, &grpIndexUp, 1, GetDirection() * PISTON_MOVEMENT_RANGE );
		anim_up = STS()->CreateAnimation( 0.0 );
		STS()->AddAnimationComponent( anim_up, 0.0, 1.0, piston_up );

		piston_dn = new MGROUP_TRANSLATE( vc_idx, &grpIndexDn, 1, GetDirection() * PISTON_MOVEMENT_RANGE );
		anim_dn = STS()->CreateAnimation( 0.0 );
		STS()->AddAnimationComponent( anim_dn, 0.0, 1.0, piston_dn );

		VerifyAnimations();
		return;
	}

	bool PushWheel::OnMouseEvent( int _event, float x, float y )
	{
		if ((_event & PANEL_MOUSE_LBDOWN))
		{
			if (y > 0.7)
			{
				if (OnChange( false ))
				{
					// dn piston in
					tgtpistondn = 1;
				}
				return true;
			}
			else if (y < 0.3)
			{
				if (OnChange( true ))
				{
					// up piston in
					tgtpistonup = 1;
				}
				return true;
			}
		}
		else if ((_event & PANEL_MOUSE_LBUP))
		{
			// pistons out
			tgtpistonup = 0;
			tgtpistondn = 0;
			return true;
		}
		return false;
	}

	void PushWheel::OnPostStep( double simt, double simdt, double mjd )
	{
		// set animations
		double tgt = tgtpistonup;
		double cur = STS()->GetAnimation( anim_up );
		if ((tgt - cur) > 0.0001)// in
		{
			tgt = min(cur + (THUMBWHEEL_RATE * simdt), 1.0);
			SetAnimation( anim_up, tgt );
		}
		else if (tgt != cur)// out
		{
			SetAnimation( anim_up, tgt );
		}

		tgt = tgtpistondn;
		cur = STS()->GetAnimation( anim_dn );
		if ((tgt - cur) > 0.0001)// in
		{
			tgt = min(cur + (THUMBWHEEL_RATE * simdt), 1.0);
			SetAnimation( anim_dn, tgt );
		}
		else if (tgt != cur)// out
		{
			SetAnimation( anim_dn, tgt );
		}

		ThumbWheel::OnPostStep( simt, simdt, mjd );
		return;
	}
};

#include "PushWheel.h"
#include "..\Atlantis.h"
#include "..\..\SSVSound.h"
#include "MathSSV.h"
#include <cassert>


namespace vc
{
	constexpr double PISTON_MOVEMENT_RANGE = 0.0085;// [m]
	constexpr double PISTON_RATE = WHEEL_RATE * 10.0;// [1/s]


	PushWheel::PushWheel( Atlantis* _sts, const std::string& _ident ):SelectorWheel( _sts, _ident ),
	tgtpistonup(0), tgtpistondn(0), bHasPushButtonDir(false)
	{
		piston_up = NULL;
		piston_dn = NULL;
	}

	PushWheel::~PushWheel()
	{
		if (piston_up) delete piston_up;
		if (piston_dn) delete piston_dn;
	}

	void PushWheel::DefinePushButtonGroups( UINT _grpIndexUp, UINT _grpIndexDn )
	{
		grpIndexUp = _grpIndexUp;
		grpIndexDn = _grpIndexDn;
		return;
	}

	void PushWheel::DefinePushButtonDirection( const VECTOR3& dir )
	{
		PushButtonDir = dir;
		bHasPushButtonDir = true;
		return;
	}

	void PushWheel::DefineVCAnimations( UINT vc_idx )
	{
		assert( bHasDirection && "PushWheel.bHasDirection" );
		assert( bHasPushButtonDir && "PushWheel.bHasPushButtonDir" );
		assert( ((grpIndexUp != -1) || (grpIndexDn != -1)) && "PushWheel.grp" );
#if _DEBUG
		oapiWriteLogV( "Circuit Breaker[%s]:\tDefine VC Animations()", GetQualifiedIdentifier().c_str() );
#endif// _DEBUG

		if (grpIndexUp != -1)
		{
			piston_up = new MGROUP_TRANSLATE( vc_idx, &grpIndexUp, 1, PushButtonDir * PISTON_MOVEMENT_RANGE );
			anim_up = STS()->CreateAnimation( 0.0 );
			STS()->AddAnimationComponent( anim_up, 0.0, 1.0, piston_up );
		}

		if (grpIndexDn != -1)
		{
			piston_dn = new MGROUP_TRANSLATE( vc_idx, &grpIndexDn, 1, PushButtonDir * PISTON_MOVEMENT_RANGE );
			anim_dn = STS()->CreateAnimation( 0.0 );
			STS()->AddAnimationComponent( anim_dn, 0.0, 1.0, piston_dn );
		}

		SelectorWheel::DefineVCAnimations( vc_idx );
		return;
	}

	bool PushWheel::OnMouseEvent( int _event, float x, float y )
	{
		if ((_event & PANEL_MOUSE_LBDOWN))
		{
			if ((y > 0.7) && (grpIndexDn != -1))
			{
				if (OnChange( false ))
				{
					// dn piston in
					tgtpistondn = 1;
				}
				return true;
			}
			else if ((y < 0.3) && (grpIndexUp != -1))
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
		if (grpIndexUp != -1)
		{
			double tgt = tgtpistonup;
			double cur = STS()->GetAnimation( anim_up );
			if ((tgt - cur) > 0.0001)// in
			{
				tgt = min(cur + (PISTON_RATE * simdt), 1.0);
				SetAnimation( anim_up, tgt );
			}
			else if (tgt != cur)// out
			{
				SetAnimation( anim_up, tgt );
			}
		}

		if (grpIndexDn != -1)
		{
			double tgt = tgtpistondn;
			double cur = STS()->GetAnimation( anim_dn );
			if ((tgt - cur) > 0.0001)// in
			{
				tgt = min(cur + (PISTON_RATE * simdt), 1.0);
				SetAnimation( anim_dn, tgt );
			}
			else if (tgt != cur)// out
			{
				SetAnimation( anim_dn, tgt );
			}
		}

		SelectorWheel::OnPostStep( simt, simdt, mjd );
		return;
	}
};

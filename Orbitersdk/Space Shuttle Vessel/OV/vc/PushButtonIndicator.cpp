/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/05/07   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/08/24   GLS
2022/06/13   GLS
2022/09/29   GLS
********************************************/
#include "PushButtonIndicator.h"
#include "../Atlantis.h"
#include "../../SSVSound.h"
#include <MathSSV.h>


namespace vc
{
	PushButtonIndicatorSingleLight::PushButtonIndicatorSingleLight( Atlantis* _sts, const string& _ident ):StandardSingleLight( _sts, _ident )
	{
		anim_pb = NULL;
		pPushDown = NULL;
		motionlength = PUSH_LENGTH;
	}

	PushButtonIndicatorSingleLight::~PushButtonIndicatorSingleLight()
	{
		if (pPushDown) delete pPushDown;
	}

	void PushButtonIndicatorSingleLight::DefineVCAnimations( UINT vc_idx )
	{
		if (bHasDirection && !bHasAnimations)
		{
#if _DEBUG
			oapiWriteLogV( "PUSH BUTTON INDICATOR[%s]:\tDefine VC Animations()", GetQualifiedIdentifier().c_str() );
#endif// _DEBUG

			anim_pb = STS()->CreateAnimation( InitialAnimState() );

			pPushDown = new MGROUP_TRANSLATE( vc_idx, &grpIndex, 1, Normalize( GetDirection() ) * motionlength );
			STS()->AddAnimationComponent( anim_pb, 0.0, 1.0, pPushDown );

			VerifyAnimations();
		}
	}

	bool PushButtonIndicatorSingleLight::OnMouseEvent( int _event, float x, float y )
	{
		if (_event & PANEL_MOUSE_LBDOWN)
		{
			OnPress();
			return true;
		}
		else if (_event & PANEL_MOUSE_LBUP)
		{
			OnRelease();
			return true;
		}
		return false;
	}

	void PushButtonIndicatorSingleLight::OnPress()
	{
		if (bHasAnimations) SetAnimation( anim_pb, 1.0 );
		output.SetLine();
		PlayVesselWave( STS()->GetSoundID(), KEY_PRESS_SOUND );
	}

	void PushButtonIndicatorSingleLight::OnRelease()
	{
		if (bHasAnimations) SetAnimation( anim_pb, 0.0 );
		output.ResetLine();
	}

	void PushButtonIndicatorSingleLight::ConnectPushButton( DiscreteBundle* pBundle, unsigned short usLine )
	{
		output.Connect( pBundle, usLine );
		return;
	}

	void PushButtonIndicatorSingleLight::SetMotionLength( double _motionlength )
	{
		motionlength = _motionlength;
		return;
	}



	PushButtonIndicatorDoubleLight::PushButtonIndicatorDoubleLight( Atlantis* _sts, const string& _ident ):StandardDoubleLight( _sts, _ident )
	{
		anim_pb = NULL;
		pPushDown = NULL;
		motionlength = PUSH_LENGTH;
	}

	PushButtonIndicatorDoubleLight::~PushButtonIndicatorDoubleLight()
	{
		if (pPushDown) delete pPushDown;
	}

	void PushButtonIndicatorDoubleLight::DefineVCAnimations( UINT vc_idx )
	{
		if (bHasDirection && !bHasAnimations)
		{
#if _DEBUG
			oapiWriteLogV( "PUSH BUTTON INDICATOR[%s]:\tDefine VC Animations()", GetQualifiedIdentifier().c_str() );
#endif// _DEBUG

			anim_pb = STS()->CreateAnimation( InitialAnimState() );

			pPushDown = new MGROUP_TRANSLATE( vc_idx, &grpIndex, 1, Normalize( GetDirection() ) * motionlength );
			STS()->AddAnimationComponent( anim_pb, 0.0, 1.0, pPushDown );

			VerifyAnimations();
		}
	}

	bool PushButtonIndicatorDoubleLight::OnMouseEvent( int _event, float x, float y )
	{
		if (_event & PANEL_MOUSE_LBDOWN)
		{
			OnPress();
			return true;
		}
		else if (_event & PANEL_MOUSE_LBUP)
		{
			OnRelease();
			return true;
		}
		return false;
	}

	void PushButtonIndicatorDoubleLight::OnPress()
	{
		if (bHasAnimations) SetAnimation( anim_pb, 1.0 );
		output.SetLine();
		PlayVesselWave( STS()->GetSoundID(), KEY_PRESS_SOUND );
	}

	void PushButtonIndicatorDoubleLight::OnRelease()
	{
		if (bHasAnimations) SetAnimation( anim_pb, 0.0 );
		output.ResetLine();
	}

	void PushButtonIndicatorDoubleLight::ConnectPushButton( DiscreteBundle* pBundle, unsigned short usLine )
	{
		output.Connect( pBundle, usLine );
		return;
	}

	void PushButtonIndicatorDoubleLight::SetMotionLength( double _motionlength )
	{
		motionlength = _motionlength;
		return;
	}
}

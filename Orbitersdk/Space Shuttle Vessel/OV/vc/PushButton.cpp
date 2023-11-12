/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/05/07   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/06/13   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/10/04   GLS
2023/11/11   GLS
********************************************/
#include "../Atlantis.h"
#include "PushButton.h"
#include "../../SSVSound.h"
#include <MathSSV.h>
#include <cassert>

namespace vc
{
	PushButton::PushButton( Atlantis* _sts, const std::string& _name )
		: AtlantisVCComponent( _sts, _name ), output()
	{
		anim_pb = NULL;
		pPushDown = NULL;
		uiGroup = 0xFFFF;
		motionlength = PUSH_LENGTH;
	}


	PushButton::~PushButton()
	{
		if (pPushDown) delete pPushDown;
	}

	void PushButton::DefineGroup(UINT _grpIndex) {
		uiGroup = _grpIndex;
	}

	void PushButton::DefineVCAnimations(UINT vc_idx) {
		if(bHasDirection && !bHasAnimations) {
#if _DEBUG
			oapiWriteLogV( "PUSH BUTTON[%s]:\tDefine VC Animations()", GetQualifiedIdentifier().c_str() );
#endif// _DEBUG

			anim_pb = STS()->CreateAnimation(InitialAnimState());

			pPushDown = new MGROUP_TRANSLATE(vc_idx, &uiGroup, 1,
				Normalize( GetDirection() ) * motionlength );
			STS()->AddAnimationComponent(anim_pb, 0.0, 1.0, pPushDown);

			VerifyAnimations();
		}
	}

	bool PushButton::OnMouseEvent(int _event, float x, float y) {
		if(_event & PANEL_MOUSE_LBDOWN) {
			OnPress();
			return true;
		}
		else if(_event & PANEL_MOUSE_LBUP) {
			OnDepress();
			return true;
		}
		return false;

	}

	void PushButton::OnPress() {
		if(bHasAnimations)
		{
			SetAnimation(anim_pb, 1.0);
		}
		for (int i = 0; i < PB_MAX_CONTACTS; i++) output[i].SetLine( 28.0f );
		PlayVesselWave( STS()->GetSoundID(), KEY_PRESS_SOUND );
	}

	void PushButton::OnDepress() {
		if(bHasAnimations)
		{
			SetAnimation(anim_pb, 0.0);
		}
		for (int i = 0; i < PB_MAX_CONTACTS; i++) output[i].ResetLine();
	}

	void PushButton::SetMotionLength( double _motionlength )
	{
		motionlength = _motionlength;
		return;
	}

	void PushButton::Connect( DiscreteBundle* pBundle, unsigned short usLine )
	{
		output[0].Connect( pBundle, usLine );
		return;
	}

	void PushButton::Connect( unsigned short usContact, DiscreteBundle* pBundle, unsigned short usLine )
	{
		assert( (usContact < PB_MAX_CONTACTS) && "PushButton::Connect::usContact" );
		output[usContact].Connect( pBundle, usLine );
		return;
	}
}


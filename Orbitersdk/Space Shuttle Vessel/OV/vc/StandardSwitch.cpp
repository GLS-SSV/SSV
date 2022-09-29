/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/03/29   GLS
2020/04/07   GLS
2020/05/07   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/06/14   GLS
2020/06/20   GLS
2021/08/24   GLS
2022/01/10   GLS
2022/01/15   GLS
2022/05/07   GLS
2022/05/29   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
// StandardSwitch.cpp: Implementierung der Klasse StandardSwitch.
//
//////////////////////////////////////////////////////////////////////

#include "StandardSwitch.h"
#include "../Atlantis.h"
#include "../../SSVSound.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

namespace vc {
	LockableLever::LockableLever(Atlantis *_sts, unsigned short usNumPositions, const std::string &_ident)
	: BasicSwitch(_sts, usNumPositions, _ident, SWITCH_THROW_SOUND), bHasPullDir(false), bIsPulled(false)
	{
		pswitchrot = NULL;
		pswitchpull = NULL;
		anim_switch = (UINT)(-1);
		anim_pull = (UINT)(-1);
	}

	LockableLever::~LockableLever()
	{
		if(pswitchrot) delete pswitchrot;
		if(pswitchpull) delete pswitchpull;
	}

	void LockableLever::SetPullDirection( const VECTOR3& _pullDir )
	{
		pullDir=_pullDir;
		bHasPullDir = true;
	}

	void LockableLever::DefineVCAnimations(UINT vc_idx)
	{
		 assert( bHasReference && bHasPullDir && bHasDirection && !bHasAnimations && "LockableLever::DefineVCAnimations" );
#if _DEBUG
		oapiWriteLogV( "Lockable Lever[%s]:\tDefine VC Animations()", GetQualifiedIdentifier().c_str() );
#endif
		//VECTOR3 ofs = STS()->GetOrbiterCoGOffset();

		pswitchrot = new MGROUP_ROTATE(LOCALVERTEXLIST, MAKEGROUPARRAY(&dummy_vec), 1, GetReference() /*+ ofs*/, GetDirection(), (float)(66 * RAD));
		anim_switch = STS()->CreateAnimation(InitialAnimState());
		ANIMATIONCOMPONENT_HANDLE parent = STS()->AddAnimationComponent(anim_switch, 0.0, 1.0, pswitchrot, NULL);

		pswitchpull = new MGROUP_TRANSLATE(vc_idx, &grpIndex, 1, pullDir*0.005);
		anim_pull = STS()->CreateAnimation(0.0);
		STS()->AddAnimationComponent(anim_pull, 0.0, 1.0, pswitchpull, parent);

		VerifyAnimations();

		OnPositionChange(usCurrentPosition);
	}

	bool LockableLever::OnMouseEvent(int _event, float x, float y)
	{
		if((_event & PANEL_MOUSE_LBUP) && bIsPulled) { // switch released
			// WARNING: this code assumes that on a 3 position LL, the center is never loaded
			if (vbSpringLoaded.at( usCurrentPosition ))
			{
				if (usCurrentPosition == 0) OnPositionUp();
				else if (usCurrentPosition == (usNumPositions - 1)) OnPositionDown();
			}

			bIsPulled=false;
			OnRelease();

			return true;
		}
		else if((_event & PANEL_MOUSE_LBPRESSED) && bIsPulled) { // move switch position
			if(bOrientation) { // horizontal
				if((x-fInitialMousePos) > 0.2) {
					OnPositionDown();
					fInitialMousePos = x;
				}
				else if((x-fInitialMousePos) < -0.2) {
					OnPositionUp();
					fInitialMousePos = x;
				}
				if(x>0.99 || x<0.01) { // if mouse is about to go out-of-bounds, release switch
					bIsPulled=false;
					OnRelease();
				}
			}
			else { //vertical
				if((y-fInitialMousePos) > 0.2) {
					OnPositionDown();
					fInitialMousePos = y;
				}
				else if((y-fInitialMousePos) < -0.2) {
					OnPositionUp();
					fInitialMousePos = y;
				}
				if(y>0.99 || y<0.01) { // if mouse is about to go out-of-bounds, release switch
					bIsPulled=false;
					OnRelease();
				}
			}

			return true;
		}
		else if((_event & PANEL_MOUSE_LBDOWN) && !bIsPulled) { // switch pulled
			bIsPulled=true;
			if(bOrientation) { // horizontal
				fInitialMousePos=x;
			}
			else { // vertical
				fInitialMousePos=y;
			}
			OnPull();

			return true;
		}
		return false;
	}

	void LockableLever::OnPositionChange(unsigned short usNewPosition)
	{
		BasicSwitch::OnPositionChange(usNewPosition);
		if(bHasAnimations) {
			SetAnimation(anim_switch, static_cast<double>(usNewPosition)/(usNumPositions - 1));
			//sprintf_s(oapiDebugString(), 256, "%s: Setting position %f", GetIdentifier().c_str(), static_cast<double>(usNewPosition)/(usNumPositions - 1));
		}
	}

	void LockableLever::OnPull()
	{
		if(bHasAnimations) SetAnimation(anim_pull, 1.0);
	}

	void LockableLever::OnRelease()
	{
		if(bHasAnimations) SetAnimation(anim_pull, 0.0);
	}

	void LockableLever::Realize()
	{
		// set animations and DiscPorts
		OnPositionChange(usCurrentPosition);
	}

	LockableLever2::LockableLever2(Atlantis* _sts, const std::string& _ident)
		: LockableLever(_sts, 2, _ident)
	{
	}

	LockableLever2::~LockableLever2()
	{
	}

	void LockableLever2::OnPositionChange(unsigned short usNewPosition)
	{
		LockableLever::OnPositionChange( usNewPosition );

		switch (usNewPosition)
		{
			case 0:
				output[0].SetLine();
				output[1].ResetLine();
				break;
			case 1:
				output[0].ResetLine();
				output[1].SetLine();
				break;
		}
		return;
	}

	void LockableLever2::ConnectPort( unsigned short usPort, DiscreteBundle* pBundle, unsigned short usLine )
	{
		assert( (usPort < 2) && "LockableLever2::ConnectPort::usPort" );
		output[usPort].Connect( pBundle, usLine );
		return;
	}

	LockableLever3::LockableLever3(Atlantis* _sts, const std::string& _ident)
		: LockableLever(_sts, 3, _ident)
	{
		usCurrentPosition = 1; // true for most switch
	}

	LockableLever3::~LockableLever3()
	{
	}

	void LockableLever3::OnPositionChange( unsigned short usNewPosition )
	{
		LockableLever::OnPositionChange( usNewPosition );

		switch (usNewPosition)
		{
			case 0:
				output[0].SetLine();
				output[1].ResetLine();
				output[2].ResetLine();
				break;
			case 1:
				output[0].ResetLine();
				output[1].SetLine();
				output[2].ResetLine();
				break;
			case 2:
				output[0].ResetLine();
				output[1].ResetLine();
				output[2].SetLine();
				break;
		}
		return;
	}

	void LockableLever3::ConnectPort( unsigned short usPort, DiscreteBundle* pBundle, unsigned short usLine )
	{
		assert( (usPort < 3) && "LockableLever3::ConnectPort::usPort" );
		output[usPort].Connect( pBundle, usLine );
		return;
	}

	StandardSwitch::StandardSwitch(Atlantis* _sts, unsigned short usNumPositions, const string& _ident)
	: BasicSwitch(_sts, usNumPositions, _ident, SWITCH_THROW_SOUND)
	{
		pswitchrot = NULL;
		anim_switch = NULL;
	}

	StandardSwitch::~StandardSwitch()
	{
		if(pswitchrot)
			delete pswitchrot;
	}


	void StandardSwitch::Realize()
	{
		//Don't add anything for Orbiter, use existing meshes

		// set animations and DiscPorts
		OnPositionChange(usCurrentPosition);
	}

	void StandardSwitch::DefineVCAnimations(UINT vc_idx)
	{
		assert( bHasReference && bHasDirection && !bHasAnimations && "StandardSwitch::DefineVCAnimations" );

	#if _DEBUG
		oapiWriteLogV( "STANDARD SWITCH[%s]:\tDefine VC Animations()", GetQualifiedIdentifier().c_str() );
	#endif

		//VECTOR3 ofs = STS()->GetOrbiterCoGOffset();
		pswitchrot = new MGROUP_ROTATE(vc_idx, &grpIndex, 1, GetReference() /*+ ofs*/, GetDirection(), (float)(66 * RAD));
		anim_switch = STS()->CreateAnimation(InitialAnimState());
		STS()->AddAnimationComponent(anim_switch, 0.0, 1.0, pswitchrot, NULL);
		VerifyAnimations();

		OnPositionChange(usCurrentPosition);
	}

	void StandardSwitch::OnPositionChange(unsigned short usNewPosition)
	{
		BasicSwitch::OnPositionChange(usNewPosition);
		if(bHasAnimations)
		{
			SetAnimation(anim_switch, (double)(usNewPosition)/(usNumPositions - 1));
		}
	}


	StdSwitch2::StdSwitch2(Atlantis *_sts, const std::string &_ident)
	: StandardSwitch(_sts, 2, _ident)
	{
	}

	StdSwitch2::~StdSwitch2()
	{
	}

	void StdSwitch2::ConnectPort( unsigned short usPort, DiscreteBundle* pBundle, unsigned short usLine )
	{
		assert( (usPort < 2) && "StdSwitch2::ConnectPort::usPort" );
		output[usPort].Connect( pBundle, usLine );
		return;
	}

	void StdSwitch2::OnPositionChange(unsigned short usNewPosition)
	{
		StandardSwitch::OnPositionChange( usNewPosition );

		switch (usNewPosition)
		{
			case 0:
				output[0].SetLine();
				output[1].ResetLine();
				break;
			case 1:
				output[0].ResetLine();
				output[1].SetLine();
				break;
		}
		return;
	}

	StdSwitch3::StdSwitch3(Atlantis *_sts, const std::string &_ident)
	: StandardSwitch(_sts, 3, _ident)
	{
		usCurrentPosition = 1; // true for most meshes
	}

	StdSwitch3::~StdSwitch3()
	{
	}

	void StdSwitch3::ConnectPort( unsigned short usPort, DiscreteBundle* pBundle, unsigned short usLine )
	{
		assert( (usPort < 3) && "StdSwitch3::ConnectPort::usPort" );
		output[usPort].Connect( pBundle, usLine );
		return;
	}

	void StdSwitch3::OnPositionChange(unsigned short usNewPosition)
	{
		StandardSwitch::OnPositionChange( usNewPosition );

		switch (usNewPosition)
		{
			case 0:
				output[0].SetLine();
				output[1].ResetLine();
				output[2].ResetLine();
				break;
			case 1:
				output[0].ResetLine();
				output[1].SetLine();
				output[2].ResetLine();
				break;
			case 2:
				output[0].ResetLine();
				output[1].ResetLine();
				output[2].SetLine();
				break;
		}
		return;
	}

};

/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/03/29   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/06/14   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/01/20   GLS
2021/08/24   GLS
2022/01/10   GLS
2022/01/15   GLS
2022/05/07   GLS
2022/08/05   GLS
2022/08/27   GLS
2022/09/29   GLS
2022/11/09   GLS
********************************************/
#include "BasicRotarySwitch.h"
#include <MathSSV.h>
#include <cassert>
#include "../Atlantis.h"
#include "../../SSVSound.h"


namespace vc
{
	BasicRotarySwitch::BasicRotarySwitch(Atlantis *_sts, unsigned short _usNumPositions, const std::string &_ident)
		: AtlantisVCComponent(_sts, _ident), usNumPositions(_usNumPositions), labels(_usNumPositions, ""), usCurrentPosition(_usNumPositions),
		allowWraparound(false), rotOffset(0.0), rotAngle(0.0)
	{
		pSwitchRot = NULL;
		anim_switch = (UINT)(-1);
		grpIndex = (UINT)(-1);
	}

	BasicRotarySwitch::~BasicRotarySwitch()
	{
		delete pSwitchRot;
	}

	void BasicRotarySwitch::Realize()
	{
		if(usCurrentPosition==usNumPositions) usCurrentPosition=0;
		OnPositionChange(usCurrentPosition);
	}

	void BasicRotarySwitch::SetLabel(unsigned short iPosition, const string& _label)
	{
		assert( (iPosition < usNumPositions) && "BasicRotarySwitch::SetLabel.iPosition" );

		labels.at(iPosition)=_label;
	}

	void BasicRotarySwitch::DefineGroup(UINT _grpIndex)
	{
		grpIndex = _grpIndex;
	}

	void BasicRotarySwitch::DefineRotationAngle(float _rotAngle)
	{
		rotAngle = _rotAngle;
	}

	void BasicRotarySwitch::SetOffset(float fOffset)
	{
		rotOffset=fOffset; // get angle from horizontal
	}

	void BasicRotarySwitch::SetInitialAnimState(double fState)
	{
		AtlantisVCComponent::SetInitialAnimState(fState);
		if(usCurrentPosition==usNumPositions)
			usCurrentPosition = static_cast<unsigned short>(fState*(usNumPositions-1));
	}

	void BasicRotarySwitch::SetWraparound(bool _allowWraparound)
	{
		allowWraparound=_allowWraparound;
	}

	void BasicRotarySwitch::DefineVCAnimations(UINT vc_idx)
	{
		if(bHasReference && bHasDirection && !bHasAnimations && !pSwitchRot)
		{
#if _DEBUG
			oapiWriteLogV( "BASIC ROTARY SWITCH[%s]:\tDefine VC Animations()",
				GetQualifiedIdentifier().c_str() );
#endif// _DEBUG

			//VECTOR3 ofs = STS()->GetOrbiterCoGOffset();
			pSwitchRot = new MGROUP_ROTATE(vc_idx, &grpIndex, 1, GetReference() /*+ ofs*/, GetDirection(), (float)(rotAngle*RAD));
			anim_switch = STS()->CreateAnimation(InitialAnimState());
			STS()->AddAnimationComponent(anim_switch, 0.0, 1.0, pSwitchRot);
			VerifyAnimations();
		}

		//OnPositionChange(usCurrentPosition);
	}

	bool BasicRotarySwitch::GetStateString(unsigned long ulBufferSize, char* pszBuffer)
	{
		if(labels.at(usCurrentPosition).compare("")) {
			sprintf_s(pszBuffer, ulBufferSize, "%s",
				labels.at(usCurrentPosition).c_str());
		} else {
			sprintf_s(pszBuffer, ulBufferSize, "[%d]",
				usCurrentPosition);
		}
		return true;
	}

	bool BasicRotarySwitch::OnParseLine(const char *line)
	{
		if(line[0] == '[') {
			usCurrentPosition = atoi(line+1);
			//OnPositionChange(usCurrentPosition);
			return true;
		} else {
			for(unsigned short i = 0; i<usNumPositions; i++) {
				if(labels.at(i) == line)
				{
					usCurrentPosition = i;
					//OnPositionChange(usCurrentPosition);
					return true;
				}
			}
		}
		return false;
	}

	bool BasicRotarySwitch::OnMouseEvent(int _event, float x, float y)
	{
		if(!(_event & PANEL_MOUSE_LBDOWN)) return false;

		float fPosition=static_cast<float>(usCurrentPosition);
		float fNumPositions=static_cast<float>(usNumPositions-1);
		float fAngle=rotOffset+fPosition*(rotAngle/fNumPositions); // angle between x-axis and switch label

		VECTOR3 curRot=RotateVectorZ(_V(0.0, 1.0, 0.0), fAngle);
		VECTOR3 cross_product=crossp(curRot, _V(x-0.5, y-0.5, 0.0));

		if(cross_product.z>0.05) {
			OnRotateLeft();
			return true;
		}
		else if(cross_product.z<-0.05) {
			OnRotateRight();
			return true;
		}

		return false;
	}

	void BasicRotarySwitch::OnRotateLeft()
	{
		if(usCurrentPosition>0) {
			usCurrentPosition--;
			OnPositionChange(usCurrentPosition);
		}
		else if(allowWraparound /*&& usCurrentPosition==0*/) {
			usCurrentPosition=usNumPositions-1;
			OnPositionChange(usCurrentPosition);
		}
	}

	void BasicRotarySwitch::OnRotateRight()
	{
		if(usCurrentPosition < usNumPositions-1) {
			usCurrentPosition++;
			OnPositionChange(usCurrentPosition);
		}
		else if(allowWraparound && usCurrentPosition==usNumPositions-1) {
			usCurrentPosition=0;
			OnPositionChange(usCurrentPosition);
		}
	}

	void BasicRotarySwitch::OnPositionChange(unsigned short usNewPosition)
	{
		assert( (usNewPosition < usNumPositions) && "BasicRotarySwitch::OnPositionChange.usNewPosition" );

		if(bHasAnimations)
		{
			SetAnimation(anim_switch, (double)(usNewPosition)/(usNumPositions - 1));
			//sprintf_s(oapiDebugString(), 256, "%s: animation %f %f", GetIdentifier().c_str(), rotAngle, (double)(usNewPosition)/(usNumPositions - 1));
		}

		PlayVesselWave( STS()->GetSoundID(), ROTATION_SWITCH_SOUND );
		return;
	}

	void BasicRotarySwitch::SetInitialPosition(unsigned short usPos)
	{
		assert( (usPos < usNumPositions) && "BasicRotarySwitch::SetInitialPosition.usPos" );

		usCurrentPosition=usPos;
	}
}

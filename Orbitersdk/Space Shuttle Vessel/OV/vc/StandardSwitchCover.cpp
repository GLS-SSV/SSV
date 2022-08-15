/******* SSV File Modification Notice *******
Date         Developer
2020/05/07   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/01/20   GLS
2021/05/26   GLS
2021/08/24   GLS
2022/08/05   GLS
********************************************/
#include "StandardSwitchCover.h"
#include "../Atlantis.h"
#include "..\..\SSVSound.h"
#include <cassert>

namespace vc
{
	StandardSwitchCover::StandardSwitchCover(Atlantis* _sts, const std::string& _ident)
	: BasicSwitch(_sts, 2, _ident, SWITCH_GUARD_SOUND)
	{
		anim_cover=NULL;
		pcoverrot=NULL;
		usCurrentPosition=0;

		labels.at(0) = "CLOSED";
		labels.at(1) = "OPEN";
	}

	StandardSwitchCover::~StandardSwitchCover()
	{
		delete pcoverrot;
	}

	void StandardSwitchCover::DefineVCAnimations(UINT vc_idx)
	{
		if(bHasReference && bHasDirection && !bHasAnimations)
		{
			//VECTOR3 ofs = STS()->GetOrbiterCoGOffset();
			pcoverrot = new MGROUP_ROTATE(vc_idx, &grpIndex, 1, GetReference() /*+ ofs*/, GetDirection(), (float)(90 * RAD));
			anim_cover = STS()->CreateAnimation(InitialAnimState());
			STS()->AddAnimationComponent(anim_cover, 0.0, 1.0, pcoverrot, NULL);
			VerifyAnimations();
		}

		OnPositionChange(usCurrentPosition);
	}

	bool StandardSwitchCover::OnMouseEvent(int _event, float x, float y)
	{
		if(!(_event & PANEL_MOUSE_LBDOWN))
			return false;

		usCurrentPosition=1-usCurrentPosition;
		OnPositionChange(usCurrentPosition);

		return true;
	}


	void StandardSwitchCover::OnPositionChange(unsigned short usNewPosition)
	{
		BasicSwitch::OnPositionChange(usNewPosition);
		if(bHasAnimations)
		{
			SetAnimation(anim_cover, usNewPosition);
		}
		AtlantisVCComponent::SetMouseRegion( mouseregion, mouse_a[usNewPosition].x, mouse_a[usNewPosition].y, mouse_d[usNewPosition].x, mouse_d[usNewPosition].y);
	}

	void StandardSwitchCover::SetMouseRegion( UINT aid, unsigned short position, float xmin, float ymin, float xmax, float ymax)
	{
		assert( (position < 2) && "StandardSwitchCover::SetMouseRegion.position" );

		mouseregion = aid;
		mouse_a[position].x=xmin;
		mouse_a[position].y=ymin;
		mouse_d[position].x=xmax;
		mouse_d[position].y=ymax;
	}
};

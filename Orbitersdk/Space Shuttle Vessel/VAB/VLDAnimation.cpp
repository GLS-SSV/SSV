/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/08/24   GLS
2022/08/05   GLS
********************************************/
#include "VAB.h"

VLDAnimation::VLDAnimation(VAB_VLD_INDEX vld_idx)
: index(vld_idx), pAnimVLD(NULL), pVAB(NULL),
	uiGroup((UINT)(-1)), fPosZ(0), fVelZ(0),
	state(STOPPED)
{
	fDistance = VAB_VLD_REF[index]-VAB_VLD_REF[0];
	fAccDistance = VAB_VLD_D_ACC/fDistance;
	fVelMax = VAB_VLD_SPEED / fDistance;

}

VLDAnimation::~VLDAnimation()
{
	if(pAnimVLD)
		delete pAnimVLD;
}

void VLDAnimation::create(VAB* vab, UINT mshidx, UINT group)
{
	uiGroup = group;
	pVAB = vab;
	VECTOR3 vt = _V(0,fDistance, 0);
	pAnimVLD = new MGROUP_TRANSLATE(mshidx, &uiGroup, 1, vt);
	animVLD = pVAB->CreateAnimation(0.0);
	pVAB->AddAnimationComponent(animVLD, 0.0, 1.0, pAnimVLD);
}

double VLDAnimation::getPosition() const throw()
{
	return fPosZ;
}

bool VLDAnimation::getSegmentPosition(VAB_VLD_INDEX &current) const throw()
{
	return false;
}

void VLDAnimation::move(double dt)
{
	switch(state)
	{
	case STOPPED:
		if(fabs(fVelZ) > 0.0001)
		{
			//slow down to stop
		}
		break;
	case MOVING_UP:
		//Decrease position
		break;
	case MOVING_DOWN:
		//Decrease position
		break;
	}
}

void VLDAnimation::setPosition(double apos)
{

}

void VLDAnimation::setPosition(VAB_VLD_INDEX spos)
{
}
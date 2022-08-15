/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/08/24   GLS
2022/08/05   GLS
********************************************/
#include "VAB.h"

HighBay::HighBay()
: pVAB (NULL), vld1(VAB_VLD1), vld2(VAB_VLD2),
  vld3(VAB_VLD3), vld4(VAB_VLD4),
  vld5(VAB_VLD5), vld6(VAB_VLD6),
  vld7(VAB_VLD7)
{
}

HighBay::~HighBay()
{
}

void HighBay::execute(double dt)
{
	vld1.move(dt);
	vld2.move(dt);
	vld3.move(dt);
	vld4.move(dt);
	vld5.move(dt);
	vld6.move(dt);
	vld7.move(dt);
}

void HighBay::init(VAB *vab, UINT mshidx, const VECTOR3& horDoorDir,
				   const UINT groups[])
{
	pVAB = vab;
	// horizontal moving doors
	uiLeftHorDoor[0] = groups[0];
	uiLeftHorDoor[1] = groups[1];
	uiRightHorDoor[0] = groups[2];
	uiRightHorDoor[1] = groups[3];
	//VLDs
	vld1.create(vab, mshidx, groups[4]);
	vld2.create(vab, mshidx, groups[5]);
	vld3.create(vab, mshidx, groups[6]);
	vld4.create(vab, mshidx, groups[7]);
	vld5.create(vab, mshidx, groups[8]);
	vld6.create(vab, mshidx, groups[9]);
	vld7.create(vab, mshidx, groups[10]);

}

bool HighBay::openTo(unsigned int segment)
{
	return false;
}
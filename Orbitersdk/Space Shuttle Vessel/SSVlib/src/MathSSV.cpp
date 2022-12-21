/******* SSV File Modification Notice *******
Date         Developer
2020/08/24   GLS
2021/06/16   GLS
2021/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/01/10   GLS
2022/01/15   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/12/15   indy91
2022/11/21   indy91
********************************************/
#include <MathSSV.h>
#include <algorithm>
#include <EngConst.h>


unsigned int GetLowerIndex(const std::vector<double> &list, double target) {
	// char buf[64];
	if(target<list[0]) return 0;
	if(target>=list[list.size()-1]) return list.size()-2;
	//  sprintf(oapiDebugString(),"target %f n_items %d ",target,n_items);
	for(unsigned int i=1;i<list.size();i++) {
		//if(i>10) {
		//    sprintf(buf,"list[%d] %.2f ",i,list[i]);
		//  strcat(oapiDebugString(),buf);
		//}
		if(list[i]>=target) {
			//sprintf(buf,"result %d",i-1);
			//strcat(oapiDebugString(),buf);
			return i-1;
		}
	}
	// sprintf(buf,"result %d",-46);
	// strcat(oapiDebugString(),buf);
	return 0; // we should never hit this point
}

unsigned int GetLowerIndex(const double* list, unsigned int size, double target)
{
	unsigned int diff = std::distance(list, std::upper_bound(list, list+size, target));
	if(diff > 0) diff -= 1; // upper_bound returns first element larger than target; we want one before this
	if(diff >= size-1) return size-2; // used for interpolation, so never return last element in array
	return diff;
}

double CalcEulerAngle(const MATRIX3 &RotMatrix, VECTOR3 &Axis)
{
	double Angle;
	double Trace=RotMatrix.m11+RotMatrix.m22+RotMatrix.m33;
	Angle=acos(0.5*(Trace-1));
	//Axis.x=(RotMatrix.m23-RotMatrix.m32)/(2*sin(Angle));
	//Axis.y=(RotMatrix.m31-RotMatrix.m13)/(2*sin(Angle));
	//Axis.z=(RotMatrix.m12-RotMatrix.m21)/(2*sin(Angle));
	Axis.x=(RotMatrix.m32-RotMatrix.m23)/(2*sin(Angle));
	Axis.y=(RotMatrix.m13-RotMatrix.m31)/(2*sin(Angle));
	Axis.z=(RotMatrix.m21-RotMatrix.m12)/(2*sin(Angle));
	if(Angle>PI) {
		Angle=PI2-Angle;
		Axis=-Axis;
	}
	return Angle;
}

VECTOR3 RotateVector(const VECTOR3 &Axis, double radAngle, const VECTOR3 &v)
{
	// Rodrigues' Rotation Formula
	return v*cos(radAngle) + crossp(Axis, v)*sin(radAngle) + Axis*dotp(Axis, v)*(1-cos(radAngle));
}

void RotateVector(const VECTOR3 &Initial, const VECTOR3 &Angles, VECTOR3 &Result)
{
	MATRIX3 RotMatrixX, RotMatrixY, RotMatrixZ;

	GetRotMatrixX(Angles.x, RotMatrixX);
	GetRotMatrixY(Angles.y, RotMatrixY);
	GetRotMatrixZ(Angles.z, RotMatrixZ);

	MATRIX3 RotMatrix=mul(RotMatrixX, RotMatrixY);
	RotMatrix=mul(RotMatrix, RotMatrixZ);
	Result=mul(RotMatrix, Initial);
}

VECTOR3 GetZYX_RYPAnglesFromMatrix(const MATRIX3 &RotMatrix)
{
	VECTOR3 Angles;
	Angles.data[PITCH]=atan2(RotMatrix.m32, RotMatrix.m33);
	Angles.data[YAW]=-asin(RotMatrix.m31);
	Angles.data[ROLL]=atan2(RotMatrix.m21, RotMatrix.m11);
	return Angles;
	/*const MATRIX3 mat=_M(0.0, 0.0, -1.0,
						0.0, 1.0, 0.0,
						1.0, 0.0, 0.0);
	MATRIX3 RM2=mul(mat, RotMatrix);
	sprintf_s(oapiDebugString(), 256, "X: %f %f %f Y: %f %f %f Z: %f %f %f", RM2.m11, RM2.m12, RM2.m13,
			RM2.m21, RM2.m22, RM2.m23, RM2.m31, RM2.m32, RM2.m33);
	return GetAnglesFromMatrix(mul(mat, RotMatrix));*/
}

VECTOR3 GetYZX_PYRAnglesFromMatrix(const MATRIX3 &RotMatrix)
{
	VECTOR3 Angles;
	Angles.data[YAW]=asin(RotMatrix.m21);
	if(Eq(abs(RotMatrix.m21), 1.0, 0.0001)) { // singularity; assume pitch is zero
		Angles.data[PITCH]=0.0;
		if(Angles.data[YAW] > 0.0) Angles.data[ROLL]=atan2(RotMatrix.m32, -RotMatrix.m12);
		else Angles.data[ROLL]=atan2(RotMatrix.m32, RotMatrix.m12);
	}
	else { // normal case
		Angles.data[PITCH]=atan2(-RotMatrix.m31, RotMatrix.m11);
		Angles.data[ROLL]=atan2(-RotMatrix.m23, RotMatrix.m22);
	}
	return Angles;
}

VECTOR3 GetZYXAnglesFromMatrixLH(const MATRIX3 &RotMatrix)
{
	VECTOR3 Angles;
	Angles.y = asin(RotMatrix.m31);
	if(Eq(abs(RotMatrix.m31), 1.0, 0.0001)) { // singularity
		Angles.x = 0;
		Angles.z = atan2(RotMatrix.m12, RotMatrix.m22);
	}
	else { // normal case
		Angles.z = atan2(-RotMatrix.m21, RotMatrix.m11);
		Angles.x = atan2(-RotMatrix.m32, RotMatrix.m33);
	}
	return Angles;
}

MATRIX3 GetRotationMatrixYZX(const VECTOR3& Angles)
{
	MATRIX3 RotMatrixX, RotMatrixY, RotMatrixZ;

	GetRotMatrixX(Angles.x, RotMatrixX);
	GetRotMatrixY(Angles.y, RotMatrixY);
	GetRotMatrixZ(Angles.z, RotMatrixZ);

	return mul(RotMatrixY, mul(RotMatrixZ, RotMatrixX));
}

// Returns the rotation matrix for a rotation of a given angle around the X axis (Pitch)
void GetRotMatrixX(double Angle, MATRIX3 &RotMatrixX)
{
	RotMatrixX.m11 = 1;
	RotMatrixX.m12 = 0;
	RotMatrixX.m13 = 0;
	RotMatrixX.m21 = 0;
	RotMatrixX.m22 = cos(Angle);
	RotMatrixX.m23 = -sin(Angle);
	RotMatrixX.m31 = 0;
	RotMatrixX.m32 = sin(Angle);
	RotMatrixX.m33 = cos(Angle);
}

// Returns the rotation matrix for a rotation of a given angle around the Y axis (Yaw)
void GetRotMatrixY(double Angle, MATRIX3 &RotMatrixY)
{
	RotMatrixY.m11 = cos(Angle);
	RotMatrixY.m12 = 0;
	RotMatrixY.m13 = sin(Angle);
	RotMatrixY.m21 = 0;
	RotMatrixY.m22 = 1;
	RotMatrixY.m23 = 0;
	RotMatrixY.m31 = -sin(Angle);
	RotMatrixY.m32 = 0;
	RotMatrixY.m33 = cos(Angle);
}

// Returns the rotation matrix for a rotation of a given angle around the Z axis (Roll)
void GetRotMatrixZ(double Angle, MATRIX3 &RotMatrixZ)
{
	RotMatrixZ.m11 = cos(Angle);
	RotMatrixZ.m12 = -sin(Angle);
	RotMatrixZ.m13 = 0;
	RotMatrixZ.m21 = sin(Angle);
	RotMatrixZ.m22 = cos(Angle);
	RotMatrixZ.m23 = 0;
	RotMatrixZ.m31 = 0;
	RotMatrixZ.m32 = 0;
	RotMatrixZ.m33 = 1;
}

MATRIX3 GetRotationMatrix(const VECTOR3& x_axis, double angle)
{
	VECTOR3 y_axis, z_axis;
	if(Eq(x_axis, _V(0, 1, 0), 0.01) || Eq(x_axis, _V(0, -1, 0), 0.01)) { // special case
		z_axis = _V(0, 0, 1);
	}
	else { // normal
		z_axis = crossp(x_axis, _V(0, 1, 0));
		z_axis /= length(z_axis);
	}
	z_axis = RotateVector(x_axis, angle, z_axis);
	y_axis = crossp(z_axis, x_axis);
	//return _M(x_axis.x, x_axis.y, x_axis.z,
	//y_axis.x, y_axis.y, y_axis.z,
	//z_axis.x, z_axis.y, z_axis.z);
	return _M(x_axis.x, y_axis.x, z_axis.x,
			  x_axis.y, y_axis.y, z_axis.y,
			  x_axis.z, y_axis.z, z_axis.z);
}

double NullStartAngle(double radRate, double Mass, double Moment, double Torque)
{
	if(!Eq(radRate, 0.0)) {
		//double Time = (Mass*Moment*Rate)/Torque;
		//double Angle=0.5*Rate*Time;
		double Angle = (0.5*radRate*radRate*Mass*Moment)/Torque;
		return DEG*Angle;
	}
	return 0.0;
}

double RotationRateChange(double Mass, double Moment, double Torque, double simdt)
{
	double acceleration = Torque/(Mass*Moment);
	double DeltaRate = acceleration*simdt;
	return DEG*DeltaRate;
}

/*VECTOR3 ConvertAnglesBetweenM50AndOrbiter(const VECTOR3 &Angles, bool ToOrbiter)
{
	VECTOR3 Output=_V(0, 0, 0);
	MATRIX3 RotMatrixX, RotMatrixY, RotMatrixZ;
	MATRIX3 M50, RotMatrixM50;

	GetRotMatrixX(-Angles.x, RotMatrixX);
	GetRotMatrixY(-Angles.y, RotMatrixY);
	GetRotMatrixZ(-Angles.z, RotMatrixZ);

	M50=_M(1, 0, 0,  0, -cos(AXIS_TILT), -sin(AXIS_TILT),  0, sin(AXIS_TILT), -cos(AXIS_TILT));
	GetRotMatrixY(-90*RAD, RotMatrixM50);
	M50=mul(RotMatrixM50, M50);
	if(ToOrbiter) {
		//transpose matrix
		M50=_M( M50.m11, M50.m21, M50.m31,
				M50.m12, M50.m22, M50.m32,
				M50.m13, M50.m23, M50.m33);
	}

	MATRIX3 Temp=mul(RotMatrixX, RotMatrixY);
	MATRIX3 RotMatrix=mul(Temp,RotMatrixZ);
	RotMatrix=mul(M50, RotMatrix);

	//get angles
	return GetXYZAnglesFromMatrix(RotMatrix);
	/*Output.data[PITCH]=atan2(RotMatrix.m23, RotMatrix.m33);
	Output.data[YAW]=-asin(RotMatrix.m13);
	Output.data[ROLL]=atan2(RotMatrix.m12, RotMatrix.m11);
	return Output;*
}*/

//MATRIX3 ConvertMatrixBetweenM50AndOrbiter(const MATRIX3 &RotMatrix, bool ToOrbiter)
/*MATRIX3 ConvertMatrixFromOrbiterToM50(const MATRIX3 &RotMatrix)
{
	// left-handed rotation matrix - converts from LH M50 to Orbitersim inertial frame
	// to convert to RH M50, swap Z and Y axes
	/*const MATRIX3 ToLH_M50=_M(1, 0, 0,
						 0, cos(AXIS_TILT), -sin(AXIS_TILT),
						 0, sin(AXIS_TILT), cos(AXIS_TILT));*
	const MATRIX3 ToLH_M50 = _M(1, 0, 0,
								0, cos(AXIS_TILT), sin(AXIS_TILT),
								0, -sin(AXIS_TILT), cos(AXIS_TILT));
	//MATRIX3 LH_M50;
	MATRIX3 Output;

	//GetRotMatrixY(-90*RAD, RotMatrixM50);
	//M50=mul(RotMatrixM50, M50);
	//Output = mul(RotMatrix, M50);
	//Output = mul(ToLH_M50, RotMatrix); // rotate matrix around X-axis (of Orbitersim global frame) to convert it to LH M50 frame
	MATRIX3 LH_M50 = mul(ToLH_M50, RotMatrix); // rotate matrix around X-axis (of Orbitersim global frame) to convert it to LH M50 frame
	// LH M50 frame is identical to RH M50 frame, but with Y and Z axes swapped
	// to get rotation matrix in RH frame (with +ve determinant), compute Euler angles for LH frame, then use these angles to compute RH frame
	VECTOR3 eulerAngles = GetZYXAnglesFromMatrixLH(LH_M50);
	return GetRotationMatrixYZX(eulerAngles);

	// swap Z and Y axes
	/*Output = _M(Output.m11, Output.m13, Output.m12,
				Output.m21, Output.m23, Output.m22,
				Output.m31, Output.m33, Output.m32);
	return Output;*
}*/

MATRIX3 ConvertOrbitersimRotationMatrixToM50(const MATRIX3 &RotMatrix)
{
	//Body to Orbiter local (right-handed)
	const MATRIX3 BodyAxis_To_OrbitersimLocal = _M(0, 1, 0, 1, 0, 0, 0, 0, -1);

	//Make Orbiter local to J2000 matrix right-handed
	MATRIX3 M50Matrix = MatrixRH_LH(RotMatrix);
	//Calculate body to J2000 matrix
	M50Matrix = mul(M50Matrix, BodyAxis_To_OrbitersimLocal);
	//Calculate body to M50 matrix
	M50Matrix = mul(M_J2000_to_M50, M50Matrix);
	return M50Matrix;
}

/*MATRIX3 ConvertLVLHAnglesToM50Matrix(const VECTOR3 &radAngles, const VECTOR3 &pos, const VECTOR3 &vel)
{
	// LVLH frame used here is different from shuttle LVLH frame
	// y-axis: position vector z-axis: velocity vector
	// PITCH: rotation around x-axis YAW: rotation around y-axis ROLL: rotation around z-axis
	VECTOR3 norm_GVel = vel/length(vel); // almost z-axis
	VECTOR3 y_axis = pos/length(pos);
	VECTOR3 x_axis = crossp(y_axis, norm_GVel);
	x_axis = x_axis/length(x_axis);
	VECTOR3 z_axis = crossp(x_axis, y_axis);
	MATRIX3 TFMatrix = _M(x_axis.x, y_axis.x, z_axis.x,
						x_axis.y, y_axis.y, z_axis.y,
						x_axis.z, y_axis.z, z_axis.z);

	// convert LVLH angles to rotation matrix
	/*VECTOR3 HorizonX, HorizonY, HorizonZ;
	RotateVectorPYR(_V(1, 0, 0), radAngles, HorizonX);
	RotateVectorPYR(_V(0, 1, 0), radAngles, HorizonY);
	RotateVectorPYR(_V(0, 0, 1), radAngles, HorizonZ);
	MATRIX3 LVLHMatrix = _M(HorizonX.x, HorizonY.x, HorizonZ.x,
							HorizonX.y, HorizonY.y, HorizonZ.y,
							HorizonX.z, HorizonY.z, HorizonZ.z);*
	MATRIX3 RotMatrixX, RotMatrixY, RotMatrixZ;
	// want left-handed rotations, so use negative rotation angles
	GetRotMatrixX(-radAngles.data[PITCH], RotMatrixX);
	GetRotMatrixY(radAngles.data[YAW], RotMatrixY); // converting from LH to RH frame, so this angle stays positive
	GetRotMatrixZ(-radAngles.data[ROLL], RotMatrixZ);
	MATRIX3 LVLHMatrix = mul(RotMatrixX, mul(RotMatrixY, RotMatrixZ));
	sprintf_s(oapiDebugString(), 256, "LVLH: m11: %f m12: %f m13 %f m21: %f m22: %f m23 %f m31: %f m32: %f m33 %f",
		LVLHMatrix.m11, LVLHMatrix.m12, LVLHMatrix.m13,
		LVLHMatrix.m21, LVLHMatrix.m22, LVLHMatrix.m23,
		LVLHMatrix.m31, LVLHMatrix.m32, LVLHMatrix.m33);
	oapiWriteLog(oapiDebugString());
	MATRIX3 RotMatrix=mul(TFMatrix, LVLHMatrix);
	//MATRIX3 RotMatrix=mul(LVLHMatrix, TFMatrix);

	RotMatrix=ConvertMatrixBetweenM50AndOrbiter(RotMatrix);
	return RotMatrix;
}*/

MATRIX3 ConvertPYOMToLVLH(double radP, double radY, double radOM)
{
	MATRIX3 RotMatrixP, RotMatrixY;
	GetRotMatrixY(radP, RotMatrixP);
	GetRotMatrixZ(radY, RotMatrixY);

	MATRIX3 Temp=mul(RotMatrixP, RotMatrixY);

	// above code calculates body vector (and can probably be optimized)
	// Y axis only changes when OM is changed
	VECTOR3 z_axis = _V(Temp.m11, Temp.m21, Temp.m31); // body vector; orbiter body axis vector pointed along +Z LVLH axis
	VECTOR3 x_axis, y_axis;
	if(!Eq(z_axis, _V(0, 1, 0), 0.0001) && !Eq(z_axis, _V(0, -1, 0), 0.0001)) {
		if(radOM > 0.0) y_axis = RotateVector(z_axis, -radOM, _V(0, 1, 0)); // orbiter should rotate in +ve direction, which means that ref. vector rotates in -ve direction
		//if(radOM > 0.0) y_axis = RotateVector(z_axis, radOM, _V(0, 1, 0));
		else y_axis = _V(0, 1, 0);
	}
	else {
		if(radOM > 0.0) y_axis = RotateVector(z_axis, -radOM, _V(0, 0, -1)); // orbiter should rotate in +ve direction, which means that ref. vector rotates in -ve direction
		else y_axis = _V(0, 0, -1);
	}
	x_axis = crossp(y_axis, z_axis);
	x_axis = x_axis/length(x_axis); // normalize X axis
	y_axis = crossp(z_axis, x_axis); // to get orthogonal frame, recalculate Y axis

	MATRIX3 RotMatrix = _M(x_axis.x, x_axis.y, x_axis.z,
						   y_axis.x, y_axis.y, y_axis.z,
						   z_axis.x, z_axis.y, z_axis.z); /*sprintf_s(oapiDebugString(), 256, "X axis: %f %f %f", x_axis.x, x_axis.y, x_axis.z);
	oapiWriteLog(oapiDebugString());
	sprintf_s(oapiDebugString(), 256, "m11: %f m12: %f m13 %f m21: %f m22: %f m23 %f m31: %f m32: %f m33 %f",
		RotMatrix.m11, RotMatrix.m12, RotMatrix.m13,
		RotMatrix.m21, RotMatrix.m22, RotMatrix.m23,
		RotMatrix.m31, RotMatrix.m32, RotMatrix.m33);
	oapiWriteLog(oapiDebugString());*/
	/*sprintf_s(oapiDebugString(), 256, "m11: %f m12: %f m13 %f m21: %f m22: %f m23 %f m31: %f m32: %f m33 %f",
		RotMatrix.m11, RotMatrix.m12, RotMatrix.m13,
		RotMatrix.m21, RotMatrix.m22, RotMatrix.m23,
		RotMatrix.m31, RotMatrix.m32, RotMatrix.m33);
	oapiWriteLog(oapiDebugString());*/

	//VECTOR3 angles = GetYZXAnglesFromMatrix(RotMatrix);
	//return angles;
	return RotMatrix;
}

MATRIX3 GetGlobalToLVLHMatrix(const VECTOR3& pos, const VECTOR3& vel)
{
	VECTOR3 z_unit = -unit(pos);
	VECTOR3 y_unit = unit(crossp(vel, pos));
	VECTOR3 x_unit = unit(crossp(y_unit, z_unit));

	return _M(x_unit.x, x_unit.y, x_unit.z,
		y_unit.x, y_unit.y, y_unit.z,
		z_unit.x, z_unit.y, z_unit.z);
}

double CalculateCameraRotationAngle(VECTOR3& dir, const VECTOR3& rot)
{
	// if camera is pointing straight up or down, make it slightly offset from (0,1,0) vector
	if(Eq(dotp(dir, _V(0, -1, 0)), 1.0, 1e-4)) dir = _V(1.74532924314e-4, -0.999999984769, 0.0);
	else if(Eq(dotp(dir, _V(0, 1, 0)), 1.0, 1e-4)) dir = _V(1.74532924314e-4, 0.999999984769, 0.0);

	VECTOR3 cam_rot = crossp(crossp(dir, _V(0, 1, 0)), dir);
	cam_rot /= length(cam_rot);
	if(cam_rot.y < 0) cam_rot = -cam_rot;
	return SignedAngle(cam_rot, rot, dir);
}

/*VECTOR3 GetPositionVector(OBJHANDLE hPlanet, double lat, double lng, double rad)
{
	VECTOR3 v;
	oapiEquToLocal(hPlanet, lng, lat, rad, &v);
	return v;
}

void ConvertEquToEcl(OBJHANDLE hPlanet, const VECTOR3& equPos, const VECTOR3& equVel, VECTOR3& eclPos, VECTOR3& eclVel)
{
	MATRIX3 obliquityMatrix;
	oapiGetPlanetObliquityMatrix(hPlanet, &obliquityMatrix);
	eclPos=mul(obliquityMatrix, equPos);
	eclVel=mul(obliquityMatrix, equVel);
}*/

int tpir(const double* list, int n_items, double target) {
	// char buf[64];
	if(target<list[0]) return 0;
	if(target>=list[n_items-1]) return n_items-2;
	//  sprintf(oapiDebugString(),"target %f n_items %d ",target,n_items);
	for(int i=1;i<n_items;i++) {
		//if(i>10) {
		//    sprintf(buf,"list[%d] %.2f ",i,list[i]);
		//  strcat(oapiDebugString(),buf);
		//}
		if(list[i]>=target) {
			//sprintf(buf,"result %d",i-1);
			//strcat(oapiDebugString(),buf);
			return i-1;
		}
	}
	// sprintf(buf,"result %d",-46);
	// strcat(oapiDebugString(),buf);
	return -46;
}

double linterp(double x0, double y0, double x1, double y1, double x) {
	double t=(x-x0)/(x1-x0);
	return y0*(1-t)+y1*t;
}

double listerp(const std::vector<double> &listx, const std::vector<double> &listy, double x) {
	unsigned int i=GetLowerIndex(listx,x);
	//  sprintf(oapiDebugString(),"i %d x0 %f y0 %f x1 %f y1 %f x %f",i,listx[i],listy[i],listx[i+1],listy[i+1],x);
	return linterp(listx[i],listy[i],listx[i+1],listy[i+1],x);
}

double listerp(const double* listx, const double* listy, int n_items, double x) {
	int i=tpir(listx,n_items,x);
	//  sprintf(oapiDebugString(),"i %d x0 %f y0 %f x1 %f y1 %f x %f",i,listx[i],listy[i],listx[i+1],listy[i+1],x);
	return linterp(listx[i],listy[i],listx[i+1],listy[i+1],x);
}

double tableterp(const double* table, const double* listrow, int n_row, const double* listcol, int n_col, double rowlookup, double collookup) {
	int i_row=tpir(listrow,n_row,rowlookup);
	double row0=listerp(listcol,&table[i_row*n_col],n_col,collookup);
	double row1=listerp(listcol,&table[(i_row+1)*n_col],n_col,collookup);
	double t=(rowlookup-listrow[i_row])/(listrow[i_row+1]-listrow[i_row]);
	double result=row0*(1-t)+row1*t;
	//  sprintf(oapiDebugString(),"rowlookup %f collookup %f i_row %d row0 %f row1 %f t %f result %f",rowlookup,collookup,i_row,row0,row1,t,result);
	return result;
	//  return 0;
}

MATRIX3 Inverse( const MATRIX3& m )
{
	double A = (m.m22 * m.m33) - (m.m32 * m.m23);
	double B = -((m.m21 * m.m33) - (m.m31 * m.m23));
	double C = (m.m21 * m.m32) - (m.m31 * m.m22);

	double d = (m.m11 * A) + (m.m12 * B) + (m.m13 * C);
	if (d == 0.0) return identity();// return I if m is non-invertible

	double D = -((m.m12 * m.m33) - (m.m32 * m.m13));
	double E = (m.m11 * m.m33) - (m.m31 * m.m13);
	double F = -((m.m11 * m.m32) - (m.m31 * m.m12));
	double _G = (m.m12 * m.m23) - (m.m22 * m.m13);
	double H = -((m.m11 * m.m23) - (m.m21 * m.m13));
	double I = (m.m11 * m.m22) - (m.m21 * m.m12);

	MATRIX3 r = _M( A, D, _G, B, E, H, C, F, I );
	r = r / d;
	return r;
}

VECTOR3 GetPosition_ECEF( VESSEL* hV, OBJHANDLE hObj )
{
	VECTOR3 r;
	VECTOR3 ECEF_pos;

	hV->GetGlobalPos( r );
	oapiGlobalToLocal( hObj, &r, &ECEF_pos );

	ECEF_pos = _V( ECEF_pos.x, ECEF_pos.z, ECEF_pos.y );
	return ECEF_pos;
}

VECTOR3 GetPosition_ECI( VESSEL* hV, OBJHANDLE hObj )
{
	VECTOR3 r;
	VECTOR3 ECI_pos;
	MATRIX3 R;

	hV->GetRelativePos( hObj, r );
	oapiGetPlanetObliquityMatrix( hObj, &R );

	ECI_pos = tmul( R, r );

	ECI_pos = _V( ECI_pos.x, ECI_pos.z, ECI_pos.y );
	return ECI_pos;
}

VECTOR3 GetVelocity_ECEF( VESSEL* hV, OBJHANDLE hObj )
{
	VECTOR3 r;
	VECTOR3 v;
	VECTOR3 ECEF_vel;
	MATRIX3 R;

	hV->GetRelativePos( hObj, r );
	hV->GetRelativeVel( hObj, v );
	oapiGetRotationMatrix( hObj, &R );

	VECTOR3 vloc = tmul( R, v );
	VECTOR3 rloc = tmul( R, r );
	double s = atan2( rloc.z, rloc.x );
	double T = oapiGetPlanetPeriod( hObj );
	VECTOR3 vsurf = _V( -sin( s ), 0.0, cos( s ) ) * PI2 / T * hypot( rloc.x, rloc.z );

	ECEF_vel = vloc - vsurf;

	ECEF_vel = _V( ECEF_vel.x, ECEF_vel.z, ECEF_vel.y );
	return ECEF_vel;
}

VECTOR3 GetVelocity_ECI( VESSEL* hV, OBJHANDLE hObj )
{
	VECTOR3 r;
	VECTOR3 v;
	VECTOR3 ECI_vel;
	MATRIX3 R;

	hV->GetRelativePos( hObj, r );
	hV->GetRelativeVel( hObj, v );
	oapiGetPlanetObliquityMatrix( hObj, &R );

	ECI_vel = tmul( R, v );

	ECI_vel = _V( ECI_vel.x, ECI_vel.z, ECI_vel.y );
	return ECI_vel;
}

double cot( double x )
{
	return tan( PI05 - x );
}

double GMTfromMJD(double mjd)
{
	//Calculate GMT since December 31 (on midnight January 1st the time is already up to 1 day, not 0)
	double mmjd = mjd - 15019.0; //Days since December 31, 1899
	double T1900 = mmjd / 365.25; //Years since then
	int Yr = 1900 + (int)(T1900); //Current year
	int LeapYears = (Yr - 1901) / 4; //Number of leap years since 1900
	double Days = mmjd - (double)((Yr - 1900) * 365 + LeapYears); //Days in year
	if (Days < 1.0)
	{
		//Special case for December 31.
		Yr--;
		LeapYears = (Yr - 1901) / 4;
		Days = mmjd - (double)((Yr - 1900) * 365 + LeapYears);
	}
	return Days * 86400.0;
}

MATRIX3 MatrixRH_LH(const MATRIX3 &A)
{
	return _M(A.m11, A.m13, A.m12, A.m31, A.m33, A.m32, A.m21, A.m23, A.m22);
}
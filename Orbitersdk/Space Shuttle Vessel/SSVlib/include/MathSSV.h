/****************************************************************************
  This file is part of Space Shuttle Vessel

  SSV mathematical functions


  Space Shuttle Vessel is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Vessel is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Vessel; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file SSV-LICENSE.txt for more details.

  **************************************************************************/
/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/04/07   GLS
2020/08/24   GLS
2021/01/20   GLS
2021/06/20   GLS
2021/06/28   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/12/28   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/01/10   GLS
2022/01/15   GLS
2022/07/16   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  SSU mathematical functions



  Space Shuttle Ultra is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Ultra is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Ultra; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file Doc\Space Shuttle Ultra\GPL.txt for more details.

  **************************************************************************/
#ifndef _MATHSSV_H
#define _MATHSSV_H


#include <Orbitersdk.h>
#include <cmath>
#include <vector>
#include <cassert>


const MATRIX3 IdentityMatrix = _M(1, 0, 0,
								  0, 1, 0,
								  0, 0, 1);
//Attitude ref. frame conversion
const double AXIS_TILT = 23.4458878*RAD;
//tilt of Earth's axis (radians)

/**
 * Converts current elements to state vector at a future time
 * Wrapper for kost functions; all input and output is in Orbiter frames/data structures
 */
//void PropagateStateVector(OBJHANDLE hPlanet, double time, const ELEMENTS& elements, VECTOR3& pos, VECTOR3& vel, bool nonsphericalGravity, double vesselMass=0.0);

//Math
/**
 * Calculates rotation axis and angle of rotation (in radians) corresponding to rotation matrix.
 */
double CalcEulerAngle(const MATRIX3 &RotMatrix, VECTOR3 &Axis);
/**
 * Returns vector v rotated by given angle about Axis
 */
VECTOR3 RotateVector(const VECTOR3 &Axis, double radAngle, const VECTOR3 &v);
/**
 * Rotates vector around specified Euler angles in XYZ order
 */
void RotateVector(const VECTOR3 &Initial, const VECTOR3 &Angles, VECTOR3 &Result);
/**
 * Returns Euler angles (in radians); Pitch=X axis, Yaw=Y axis, Roll=Z axis
 */
VECTOR3 GetZYX_RYPAnglesFromMatrix(const MATRIX3 &RotMatrix); //returns angles in radians
/**
 * Returns Euler angles (in radians); Pitch=Y axis, Yaw=Z axis, Roll=X axis
 */
VECTOR3 GetYZX_PYRAnglesFromMatrix(const MATRIX3 &RotMatrix);
/**
 * Returns Euler angles (in radians)
 * Value for each axis corresponds to angle around that axis
 */
VECTOR3 GetZYXAnglesFromMatrixLH(const MATRIX3 &RotMatrix);
/**
 * Returns rotation matrix corresponding to given Euler angles
 * Rotation is performed in YZX order - this corresponds to PYR order for shuttle body axis & LVLH frames
 * \param Angles Angle of rotation about each axis
 */
MATRIX3 GetRotationMatrixYZX(const VECTOR3& Angles);
/**
 * Calculates rotation matrix corresponding to rotation around X axis by specified angle (radians)
 */
void GetRotMatrixX(double Angle, MATRIX3 &RotMatrixX);
/**
 * Calculates rotation matrix corresponding to rotation around Y axis by specified angle (radians)
 */
void GetRotMatrixY(double Angle, MATRIX3 &RotMatrixY);
/**
 * Calculates rotation matrix corresponding to rotation around Z axis by specified angle (radians)
 */
void GetRotMatrixZ(double Angle, MATRIX3 &RotMatrixZ);
/**
 * Returns rotation matrix with x axis in specified direction, and z axis rotated around x axis by specified angle relative to reference frame.
 * \param x_axis Normalised vector in direction of x axis
 * \param angle Angle (in radians) between z axis and z axis in reference frame
 */
MATRIX3 GetRotationMatrix(const VECTOR3& x_axis, double angle);

/**
 * Returns angle (in degress) through which body will rotate before angular velocity is killed.
 * \param radRate rotation rate (rad/s)
 * \param Mass mass of body
 * \param Moment moment of inertia about rotation axis
 * \param Torque torque applied to null rotation
 */
double NullStartAngle(double radRate, double Mass, double Moment, double Torque);
/**
 * Returns change in rotation rate (DEG/s) over given time period.
 */
double RotationRateChange(double Mass, double Moment, double Torque, double simdt);

/**
 * Converts vessel rotation matrix (returned by VESSEL::GetRotationMatrix) to M50 frame.
 * Also transforms body axis frame to shuttle body axis frame (i.e. +X pointing forward, +Z pointing down).
 * \returns Rotation matrix to convert between body axis and M50 frame
 */
MATRIX3 ConvertOrbitersimRotationMatrixToM50(const MATRIX3 &RotMatrix);
//MATRIX3 ConvertOrbitersimAnglesToM50Matrix(const VECTOR3 &radAngles);
//MATRIX3 ConvertLVLHAnglesToM50Matrix(const VECTOR3 &radAngles, const VECTOR3 &pos, const VECTOR3 &vel);
/**
* Converts Pitch, Yaw and Omicron angles (entered in UNIV PTG display) to angles in shuttle body frame.
*/
//VECTOR3 ConvertPYOMToBodyAngles(double radP, double radY, double radOM);
/**
 * Converts Pitch, Yaw and Omicron angles (entered in UNIV PTG display) to LVLH rotation matrix
 * \returns LVLH rotation matrix (right-handed)
 */
MATRIX3 ConvertPYOMToLVLH(double radP, double radY, double radOM);

/**
 * Returns matrix to convert direction vector in global frame to LVLH frame
 * LVLH Frame:
 *		X: from target in +ve velocity vector Z: from target towards center of Earth
 * \param pos position of vessel in global frame
 * \param vel position of vessel in inertial frame
 * \param changeHandedness true to change handedness (i.e. LH global frame to RH LVLH frame)
 * \returns rotation matrix
 */
MATRIX3 GetGlobalToLVLHMatrix(const VECTOR3& pos, const VECTOR3& vel, bool changeHandedness = false);

/**
 * Calculates rotation angle to be passed to SetCameraDefaultDirection function
 * \param dir Camera direction vector (if equal to +/- Y-axis, will be changed slightly so Orbitersim doesn't ignore rotation angle)
 * \param rot Vector in direction of vertical axis for camera view
 * \returns rotation angle about direction vector
 */
double CalculateCameraRotationAngle(VECTOR3& dir, const VECTOR3& rot);

//VECTOR3 GetPositionVector(OBJHANDLE hPlanet, double lat, double lng, double rad);
//void ConvertEquToEcl(OBJHANDLE hPlanet, const VECTOR3& equPos, const VECTOR3& equVel, VECTOR3& eclPos, VECTOR3& eclVel);
//interpolation
/**
 * Returns index of largest element in (sorted) array which is smaller than target.
 * Maximum index returned will be size()-2 (this makes interpolation easier).
 */
unsigned int GetLowerIndex(const std::vector<double> &list, double target);
unsigned int GetLowerIndex(const double* list, unsigned int size, double target);
int tpir(const double* list, int n_items, double target);
double linterp(double x0, double y0, double x1, double y1, double x);
double listerp(const std::vector<double> &listx, const std::vector<double> &listy, double x);
double listerp(const double* listx, const double* listy, int n_items, double x);
double tableterp(const double* table, const double* listrow, int n_row, const double* listcol, int n_col, double rowlookup, double collookup);

MATRIX3 Inverse( const MATRIX3& m );

static inline VECTOR3 Normalize(const VECTOR3 &a)
{
	return (a/length(a));
}


static inline VECTOR3 Projection(const VECTOR3 &u, const VECTOR3 &v) //Proj u onto v
{
	return v*(dotp(u, v)/dotp(v, v));
}

/*static inline VECTOR3 ToRad(const VECTOR3 &Input)
{
		VECTOR3 Output;
		for(int i=0;i<3;i++) {
			Output.data[i]=Input.data[i]*RAD;
		}
		return Output;
	}

static inline VECTOR3 ToDeg(const VECTOR3 &Input)
{
	VECTOR3 Output;
	for(int i=0;i<3;i++) {
		Output.data[i]=Input.data[i]*DEG;
	}
	return Output;
}*/

/**
 * Converts between Orbiter left-handed frame and right-handed frame.
 * Swaps y and z values.
 * Used mainly when calling KOST functions
 */
static inline VECTOR3 ConvertBetweenLHAndRHFrames(const VECTOR3 &v)
{
	return _V(v.x, v.z, v.y);
}

/**
 * Returns vector normalized by adjusting z-component only - x & y values are not changed
 */
static inline VECTOR3 NormZ( const VECTOR3& v )
{
	// error checking
	/*if((pow(v.x,2)-pow(v.y,2))>0.1) {
		sprintf_s(oapiDebugString(), 256, "NormZ ERROR: Vector %f %f %f passed at T: %f",
			v.x, v.y, v.z, met);
		oapiWriteLog(oapiDebugString());
		return _V(0, 0, 1);
	}*/
	VECTOR3 o=v;
	o.z=sqrt(1.0-pow(v.x,2)-pow(v.y,2));
	return o;
}

static inline MATRIX3 Transpose(const MATRIX3& m)
{
	return _M(m.m11, m.m21, m.m31,
			  m.m12, m.m22, m.m32,
			  m.m13, m.m23, m.m33);
}

/**
 * Returns rotation matrix representing angle from current to target matrix
 */
static inline MATRIX3 GetRotationErrorMatrix(const MATRIX3& cur, const MATRIX3& tgt)
{
	return mul(Transpose(cur), tgt);
}

static inline bool Eq(const double d1, const double d2, double dDiff=0.00001)
{
	if(fabs(d1-d2)>dDiff) return false;
	return true;
}

static inline bool Eq(const VECTOR3& v1, const VECTOR3& v2, double dDiff=0.00001)
{
	for(int i=0;i<3;i++) {
		if(fabs(v1.data[i]-v2.data[i])>dDiff) return false;
	}
	return true;
}

static inline double range(double _min, double value, double _max)
{
	assert( (_min <= _max) && "range::min > range::max" );
	if(value<_min) return _min;
	if(value>_max) return _max;
	return value;
}

static inline int rangeint( int _min, int value, int _max )
{
	assert( (_min <= _max) && "range::min > range::max" );
	if(value<_min) return _min;
	if(value>_max) return _max;
	return value;
}

static inline double midval( double val_a, double val_b, double val_c )
{
	if (val_a > val_b)
	{
		if (val_b > val_c)
		{
			return val_b;
		}
		else
		{
			if (val_c > val_a)
			{
				return val_a;
			}
			else
			{
				return val_c;
			}
		}
	}
	else
	{
		if (val_a > val_c)
		{
			return val_a;
		}
		else
		{
			if (val_c > val_b)
			{
				return val_b;
			}
			else
			{
				return val_c;
			}
		}
	}
}

/**
 * Converts time in DD/HH:MM:SS format (array of 4 doubles) to time in seconds
 */
inline double ConvertDDHHMMSSToSeconds(const double ddhhmmss[])
{
	return ddhhmmss[0]*86400+ddhhmmss[1]*3600+ddhhmmss[2]*60+ddhhmmss[3];
}

/**
 * Converts time in seconds to time in DD/HH:MM:SS format (array of 4 doubles)
 */
inline void ConvertSecondsToDDHHMMSS(double seconds, double ddhhmmss[])
{
	ddhhmmss[0] = static_cast<int>(seconds/86400);
	seconds -= ddhhmmss[0]*86400;
	ddhhmmss[1] = static_cast<int>(seconds/3600);
	seconds -= ddhhmmss[1]*3600;
	ddhhmmss[2] = static_cast<int>(seconds/60);
	seconds -= ddhhmmss[2]*60;
	ddhhmmss[3] = seconds;
}

inline int Round(double value)
{
	return static_cast<int>(floor(value+0.5));
}

static inline double sign(double x)
{
	if(x>=0.0) return 1.0;
	else return -1.0;
}

/**
 * Calculated signed angle in radians [-pi to pi] from v1 to v2.
 * \param ref reference vector to measure angle around - should be in different plane from v1 & v2 (ideally perpendicular)
 */
static inline double SignedAngle(const VECTOR3& v1, const VECTOR3& v2, const VECTOR3& ref)
{
	double dot_product = range(-1.0, dotp(v1/length(v1), v2/length(v2)), 1.0); // dot product should always be between -1 and +1, but small numerical errors may cause acos to fail
	double angle = acos(dot_product);
	// if cross product of v1 and v2 is in opposite direction to reference vector, angle is negative (alternatively, > 180 degrees)
	if(dotp(ref, crossp(v1, v2)) < 0) angle = -angle;
	return angle;
}

static inline double angle(const VECTOR3& dir, const VECTOR3& dir0)
{
	return acos(dotp(dir, dir0) /
		(length(dir) * length(dir0)));
}

static inline VECTOR3 RotateVectorX(const VECTOR3 &v, double angle) //rotates about angle (in degrees) in X-axis
{
	VECTOR3 Output;
	Output.x=v.x;
	Output.z=v.z*cos(angle*RAD)-v.y*sin(angle*RAD);
	Output.y=v.y*cos(angle*RAD)+v.z*sin(angle*RAD);
	return Output;
}
static inline VECTOR3 RotateVectorY(const VECTOR3 &v, double angle) //rotates about angle (in degrees) in Y-axis
{
	VECTOR3 Output;
	Output.y=v.y;
	Output.x=v.x*cos(angle*RAD)-v.z*sin(angle*RAD);
	Output.z=v.z*cos(angle*RAD)+v.x*sin(angle*RAD);
	return Output;
}
static inline VECTOR3 RotateVectorZ(const VECTOR3 &v, double angle) //rotates about angle (in degrees) in Z-axis
{
	VECTOR3 Output;
	Output.x=v.x*cos(angle*RAD)-v.y*sin(angle*RAD);
	Output.y=v.x*sin(angle*RAD)+v.y*cos(angle*RAD);
	Output.z=v.z;
	return Output;
}

/**
 * Calculates the vessel's velocity in the Earth-centered Earth-fixed (ECEF) reference frame.
 * @param hV	handle to vessel
 * @param rw	handle to planetary body
 * @return	velocity in the ECEF reference frame
 */
VECTOR3 GetVelocity_ECEF( VESSEL* hV, OBJHANDLE hObj );

/**
 * Calculates the vessel's velocity in the Earth-centered inertial (ECI) reference frame.
 * @param hV	handle to vessel
 * @param rw	handle to planetary body
 * @return	velocity in the ECI reference frame
 */
VECTOR3 GetVelocity_ECI( VESSEL* hV, OBJHANDLE hObj );

/**
 * Calculates the vessel's position in the Earth-centered Earth-fixed (ECEF) reference frame.
 * @param hV	handle to vessel
 * @param rw	handle to planetary body
 * @return	position in the ECEF reference frame
 */
VECTOR3 GetPosition_ECEF( VESSEL* hV, OBJHANDLE hObj );

/**
 * Calculates the vessel's position in the Earth-centered inertial (ECI) reference frame.
 * @param hV	handle to vessel
 * @param rw	handle to planetary body
 * @return	position in the ECI reference frame
 */
VECTOR3 GetPosition_ECI( VESSEL* hV, OBJHANDLE hObj );

/**
 * Calculates the cotagent of an angle.
 * @param x	angle [rad]
 * @return	cotangent of the argument
 */
double cot( double x );

#endif// _MATHSSV_H

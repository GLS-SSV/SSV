/****************************************************************************
  This file is part of Space Shuttle Vessel

  GNC Utilities definition


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

#pragma once

#include "../SimpleGPCSoftware.h"

namespace dps
{
	//CONSTANTS

	//Earth rotational rate (rad/s)
	const double EARTH_RATE = 7.29211514646E-05;
	//Gravitational constant of the Earth (ft^3/s^2)
	const double EARTH_MU = 1.40764487566e16;
	//Earth's equatorial radius for gravity (ft)
	const double EARTH_RADIUS_GRAV = 2.09256561680e7;
	//Earth's ellipticity constant (ND)
	const double ELLIPT = 0.0; //Should be 3.352329869e-3, but Orbiter doesn't support it
	//Earth equatorial radis (ft)
	const double EARTH_RADIUS_EQUATOR = 20902263.7794; //Value from Orbiter, actually 2.09257414698e7
	//Feet to nautical miles conversion factor (NMI/ft)
	const float NAUTMI_PER_FT = 1.6457884e-4f;

	//GENERAL PURPOSE CONVERSIONS

	//Matrix from by three (row) vectors
	MATRIX3 MATRIX(VECTOR3 A, VECTOR3 B, VECTOR3 C);
	//Earth-Fixed to Topodetic
	MATRIX3 EF_TO_TOPDET(double LAT_GEOD, double LON);
	//Earth-Fixed to Runway
	MATRIX3 EF_TO_RUNWAY(double LAT_GEOD, double LON, double AZ);
	//Earth-Fixed To Scanner
	MATRIX3 EF_TO_SCANNER(double LAT_GEOD, double LON, double AZ);
	//Earth-Fixed to Geodetic
	void EF_TO_GEODETIC(VECTOR3 R_EF, double &LAT_GEOD, double &LON, double &ALT);
	//Geodetic to Earth-Fixed
	VECTOR3 GEODETIC_TO_EF(double LAT_GEOD, double LON, double ALT);
	//Conversion of a matrix to a Quaternion
	void MAT_TO_QUAT(MATRIX3 M, double &QS, VECTOR3 &QV);
	//Return quaternion from local orbital to M50 frame given position and velocity vectors
	void RV_TO_QLVLH(VECTOR3 XR, VECTOR3 XV, double &QS, VECTOR3 &QV);
	//Perform coordinate transformation using quaternion
	VECTOR3 QUAT_XFORM(double QBAS, VECTOR3 QBAV, VECTOR3 W_A);
	//Product of two quaternions
	void QUAT_MULT(double Q1S, VECTOR3 Q1V, double Q2S, VECTOR3 Q2V, double &Q3S, VECTOR3 &Q3V);
	//Extract ADI angles from quaternion
	void QUAT_TO_ADI_ANG(double XQS, VECTOR3 XQV, double &XPITCHSINE, double &XPITCHCOS, double &XYAWSINE, double &XYAWCOS, double &XROLLSINE, double &XROLLCOS, bool &XFLAG);

	class GNCUtilities : public SimpleGPCSoftware
	{
		//Calculate M50 to Earth-fixed rotation matrix and polar vector at epoch
		void M50_TO_EF_AT_EPOCH();

		//Reference time of M50 to EF matrix in GMT
		double T_EPOCH;
		//M50 to EF matrix at epoch
		MATRIX3 M_M50TOEF_AT_EPOCH;
		//J2 non-spherical gravity
		float J2_GRAV;
	public:
		explicit GNCUtilities(SimpleGPCSystem* _gpc);
		virtual ~GNCUtilities();

		void Realize() override;

		//Conversions that require COMPOOL variables

		//Rotation matrix from Earth fixed to M50 at given GMT
		MATRIX3 EARTH_FIXED_TO_M50_COORD(double TIME) const;
		//Height about Earth ellipsoid
		double H_ELLIPSOID(VECTOR3 R) const;
		//Velocity relative to a rotating Earth
		VECTOR3 V_REL(VECTOR3 V, VECTOR3 R) const;

		float GetJ2() const;
	};
}
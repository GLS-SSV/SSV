/***************************************************************************
 *   Copyright (C) 2008 by C J Plooy                                       *
 *   cornwarecjp@lavabit.com                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Lesser General Public License for more details.                   *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

/*
KOST is the Kepler Orbit Simulation Toolkit.
This header defines the data types of KOST.
*/

#ifndef KOST_TYPES_H
#define KOST_TYPES_H

#include "kost_settings.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef kostReal
typedef double kostReal;
#endif

#ifndef kostVector3
typedef struct
{

	kostReal x, y, z;

} kostVector3;
#endif

#ifndef kostMatrix3
typedef struct
{

	kostReal
		m11, m12, m13,
		m21, m22, m23,
		m31, m32, m33;

} kostMatrix3;
#endif

#ifndef kostElements
typedef struct
{
	kostReal a;      /*Semi-major axis*/
	kostReal e;      /*Eccentricity*/
	kostReal i;      /*Inclination*/
	kostReal theta;  /*Longitude of ascending node*/
	kostReal omegab; /*Longitude of periapsis*/
	kostReal L;      /*Mean longitude at epoch*/
} kostElements;
#endif

#ifndef kostOrbitParam
typedef struct
{
	/*Same as ORBITPARAM*/
	kostReal SMi;  /*semi-minor axis*/
	kostReal PeD;  /*periapsis distance*/
	kostReal ApD;  /*apoapsis distance*/
	kostReal MnA;  /*mean anomaly*/
	kostReal TrA;  /*true anomaly*/
	kostReal MnL;  /*mean longitude*/
	kostReal TrL;  /*true longitude*/
	kostReal EcA;  /*eccentric anomaly*/
	kostReal Lec;  /*linear eccentricity*/
	kostReal T;    /*orbit period*/
	kostReal PeT;  /*time to next periapsis passage*/
	kostReal ApT;  /*time to next apoapsis passage*/

	/*Additional*/
	kostReal AgP;  /*argument of periapsis*/
} kostOrbitParam;
#endif

typedef struct
{
	kostVector3 pos;
	kostVector3 vel;
} kostStateVector;


typedef struct
{
	kostVector3 pe, ap, dn, an;

	kostVector3 *points;
	unsigned int numPoints;

} kostOrbitShape;

#ifdef __cplusplus
}
#endif

#endif



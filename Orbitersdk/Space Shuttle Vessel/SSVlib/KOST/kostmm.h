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
This header file defines a C++ API
*/

#ifndef KOST_MM_H
#define KOST_MM_H

#include "kost.h"

#include "kost_settings.h"


#ifdef KOSTMM_LINALG_OPERATORS_VECTOR3

inline kostVector3 operator+(const kostVector3 &v1, const kostVector3 &v2)
	{return kostAddvv(&v1, &v2);}

inline kostVector3 operator-(const kostVector3 &v1, const kostVector3 &v2)
	{return kostSubvv(&v1, &v2);}

inline kostVector3 operator*(const kostVector3 &v, kostReal r)
	{return kostMulrv(r, &v);}

#endif

#ifndef dotProduct
inline kostReal dotProduct(const kostVector3 &v1, const kostVector3 &v2)
	{return kostDotProductvv(&v1, &v2);}
#endif

#ifndef crossProduct
inline kostVector3 crossProduct(const kostVector3 &v1, const kostVector3 &v2)
	{return kostCrossProductvv(&v1, &v2);}
#endif

#ifndef abs
inline kostReal abs(const kostVector3 &v)
	{return kostAbsv(&v);}
#endif

#ifndef abs2
inline kostReal abs2(const kostVector3 &v)
	{return kostAbs2v(&v);}
#endif

#ifndef normal
inline kostVector3 normal(const kostVector3 &v)
	{return kostNormalv(&v);}
#endif

#ifdef KOSTMM_LINALG_OPERATORS_MATRIX3

inline kostMatrix3 operator*(const kostMatrix3 &m1, const kostMatrix3 &m2)
	{return kostMulmm(&m1, &m2);}

inline kostVector3 operator*(const kostMatrix3 &m, kostVector3 &v)
	{return kostMulmv(&m, &v);}

inline kostVector3 &operator*=(kostVector3 &v, const kostMatrix3 &m)
{
	v = kostMulmv(&m, &v);
	return v;
}

#endif

#ifndef makeTranspose
inline void makeTranspose(kostMatrix3 &m)
	{kostMakeTransposem(&m);}
#endif

#endif



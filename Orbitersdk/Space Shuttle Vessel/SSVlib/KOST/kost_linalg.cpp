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

#include <math.h>

#include "kost_linalg.h"

kostVector3 kostConstructv(kostReal x, kostReal y, kostReal z)
{
	kostVector3 ret;
	ret.x = x;
	ret.y = y;
	ret.z = z;
	return ret;
}

kostVector3 kostAddvv(const kostVector3 *v1, const kostVector3 *v2)
{
	kostVector3 ret;
	ret.x = v1->x + v2->x;
	ret.y = v1->y + v2->y;
	ret.z = v1->z + v2->z;
	return ret;
}

kostVector3 kostSubvv(const kostVector3 *v1, const kostVector3 *v2)
{
	kostVector3 ret;
	ret.x = v1->x - v2->x;
	ret.y = v1->y - v2->y;
	ret.z = v1->z - v2->z;
	return ret;
}

kostVector3 kostMulrv(kostReal r, const kostVector3 *v)
{
	kostVector3 ret;
	ret.x = r * v->x;
	ret.y = r * v->y;
	ret.z = r * v->z;
	return ret;
}

kostReal kostDotProductvv(const kostVector3 *v1, const kostVector3 *v2)
{
	return v1->x*v2->x + v1->y*v2->y + v1->z*v2->z;
}

kostVector3 kostCrossProductvv(const kostVector3 *v1, const kostVector3 *v2)
{
	kostVector3 ret;
	ret.x = v1->y*v2->z - v1->z*v2->y;
	ret.y = v1->z*v2->x - v1->x*v2->z;
	ret.z = v1->x*v2->y - v1->y*v2->x;
	return ret;
}

kostReal kostAbsv(const kostVector3 *v)
{
	return sqrt(v->x*v->x + v->y*v->y + v->z*v->z);
}

kostReal kostAbs2v(const kostVector3 *v)
{
	return v->x*v->x + v->y*v->y + v->z*v->z;
}

kostVector3 kostNormalv(const kostVector3 *v)
{
	kostReal len = kostAbsv(v);
	/*TODO: check against division by zero*/
	kostReal invlen = 1.0 / len;
	return kostConstructv(invlen * v->x, invlen * v->y, invlen * v->z);
}

void kostMakeUnitm(kostMatrix3 *m)
{
	m->m11 = 1.0; m->m12 = 0.0; m->m13 = 0.0;
	m->m21 = 0.0; m->m22 = 1.0; m->m23 = 0.0;
	m->m31 = 0.0; m->m32 = 0.0; m->m33 = 1.0;
}

void kostMakeXRotm(kostMatrix3 *m, kostReal angle)
{
	m->m11 = 1.0; m->m12 = 0.0;        m->m13 =  0.0;
	m->m21 = 0.0; m->m22 = cos(angle); m->m23 = -sin(angle);
	m->m31 = 0.0; m->m32 = sin(angle); m->m33 =  cos(angle);
}

void kostMakeYRotm(kostMatrix3 *m, kostReal angle)
{
	m->m11 =  cos(angle); m->m12 = 0.0; m->m13 = sin(angle);
	m->m21 =  0.0;        m->m22 = 1.0; m->m23 = 0.0;
	m->m31 = -sin(angle); m->m32 = 0.0; m->m33 = cos(angle);
}

void kostMakeZRotm(kostMatrix3 *m, kostReal angle)
{
	m->m11 = cos(angle); m->m12 = -sin(angle); m->m13 = 0.0;
	m->m21 = sin(angle); m->m22 =  cos(angle); m->m23 = 0.0;
	m->m31 = 0.0;        m->m32 =  0.0;        m->m33 = 1.0;
}

void kostMakeTransposem(kostMatrix3 *m)
{
	kostReal tmp;

#define myswap(a, b) tmp = a; a = b; b = tmp;

	myswap(m->m12, m->m21);
	myswap(m->m13, m->m31);
	myswap(m->m23, m->m32);
}

kostVector3 kostMulmv(const kostMatrix3 *m, const kostVector3 *v)
{
	kostVector3 ret;
	ret.x = m->m11 * v->x + m->m12 * v->y + m->m13 * v->z;
	ret.y = m->m21 * v->x + m->m22 * v->y + m->m23 * v->z;
	ret.z = m->m31 * v->x + m->m32 * v->y + m->m33 * v->z;
	return ret;
}

kostMatrix3 kostMulmm(const kostMatrix3 *m1, const kostMatrix3 *m2)
{
	kostMatrix3 ret;

	ret.m11 = m1->m11 * m2->m11 + m1->m12 * m2->m21 + m1->m13 * m2->m31;
	ret.m12 = m1->m11 * m2->m12 + m1->m12 * m2->m22 + m1->m13 * m2->m32;
	ret.m13 = m1->m11 * m2->m13 + m1->m12 * m2->m23 + m1->m13 * m2->m33;

	ret.m21 = m1->m21 * m2->m11 + m1->m22 * m2->m21 + m1->m23 * m2->m31;
	ret.m22 = m1->m21 * m2->m12 + m1->m22 * m2->m22 + m1->m23 * m2->m32;
	ret.m23 = m1->m21 * m2->m13 + m1->m22 * m2->m23 + m1->m23 * m2->m33;

	ret.m31 = m1->m31 * m2->m11 + m1->m32 * m2->m21 + m1->m33 * m2->m31;
	ret.m32 = m1->m31 * m2->m12 + m1->m32 * m2->m22 + m1->m33 * m2->m32;
	ret.m33 = m1->m31 * m2->m13 + m1->m32 * m2->m23 + m1->m33 * m2->m33;

	return ret;
}


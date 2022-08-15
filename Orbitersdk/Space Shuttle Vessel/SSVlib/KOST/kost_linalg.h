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
This header file contains the linear algebra functions
*/

#ifndef KOST_LINALG_H
#define KOST_LINALG_H

#include "kost_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
Vector operations:
*/
kostVector3 kostConstructv(kostReal x, kostReal y, kostReal z);

kostVector3 kostAddvv(const kostVector3 *v1, const kostVector3 *v2);
kostVector3 kostSubvv(const kostVector3 *v1, const kostVector3 *v2);

kostVector3 kostMulrv(kostReal r, const kostVector3 *v);

kostReal    kostDotProductvv(const kostVector3 *v1, const kostVector3 *v2);
kostVector3 kostCrossProductvv(const kostVector3 *v1, const kostVector3 *v2);

kostReal    kostAbsv(const kostVector3 *v);  /*Absolute value (length)*/
kostReal    kostAbs2v(const kostVector3 *v); /*Square of absolute value (faster)*/

kostVector3 kostNormalv(const kostVector3 *v); /*Normalized vector*/

/*TODO: other ones*/

/*
Matrix operations:
*/

void kostMakeUnitm(kostMatrix3 *m);
void kostMakeXRotm(kostMatrix3 *m, kostReal angle);
void kostMakeYRotm(kostMatrix3 *m, kostReal angle);
void kostMakeZRotm(kostMatrix3 *m, kostReal angle);

void kostMakeTransposem(kostMatrix3 *m);

kostVector3 kostMulmv(const kostMatrix3 *m, const kostVector3 *v);

kostMatrix3 kostMulmm(const kostMatrix3 *m1, const kostMatrix3 *m2);

/*TODO: other ones*/


#ifdef __cplusplus
}
#endif

#endif



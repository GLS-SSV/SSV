/***************************************************************************
 *   Copyright (C) 2008 by C J Plooy / Tim Blaxland                        *
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
KOST is the Kepler Orbital Simulation Toolkit.
This header file contains function for determining past/future states
*/

#ifndef KOST_TIME_H
#define KOST_TIME_H

#include "kost_types.h"

#ifdef __cplusplus
extern "C" {
#endif

kostReal kostGetMeanAnomalyAtTime(
	kostReal mu,                  /* standard gravitational parameter */
	const kostElements *elements, /* pointer to orbital elements at epoch */
	kostReal timeSinceEpoch);     /* time since epoch in seconds */

int kostGetTrueAnomalyAtTime(
	kostReal mu,                  /* standard gravitational parameter */
	const kostElements *elements, /* pointer to orbital elements at epoch */
	kostReal *trueAnomaly,        /* location where result will be stored */
	kostReal timeSinceEpoch,      /* time since epoch in seconds */
	kostReal maxRelativeError,    /* maximum relative error in eccentric anomaly */
	int maxIterations);           /* max number of iterations for calculating eccentric anomaly */

kostReal kostGetLANAtTime(
	kostReal mu,                  /* standard gravitational parameter */
	const kostElements *elements, /* pointer to orbital elements at epoch */
	kostReal bodyRadius,          /* mean radius of the non-spherical body being orbited */
	kostReal jTwoCoeff,           /* J2 coefficient of the non-spherical body being orbited */
	kostReal timeSinceEpoch);     /* time since epoch in seconds */

kostReal kostGetArgPeAtTime(
	kostReal mu,                  /* standard gravitational parameter */
	const kostElements *elements, /* pointer to orbital elements at epoch */
	kostReal bodyRadius,          /* mean radius of the non-spherical body being orbited */
	kostReal jTwoCoeff,           /* J2 coefficient of the non-spherical body being orbited */
	kostReal timeSinceEpoch);     /* time since epoch in seconds */

int kostElements2StateVectorAtTime(
	kostReal mu,                  /* standard gravitational parameter */
	const kostElements *elements, /* pointer to orbital elements at epoch */
	kostStateVector *state,       /* pointer to where state vectors at epoch+timeSinceEpoch will be stored */
	kostReal timeSinceEpoch,      /* time since epoch in seconds */
	kostReal maxRelativeError,    /* maximum relative error in eccentric anomaly */
	int maxIterations,            /* max number of iterations for calculating eccentric anomaly */
	kostReal bodyRadius,          /* mean radius of the non-spherical body being orbited */
	kostReal jTwoCoeff);          /* J2 coefficient of the non-spherical body being orbited */

void kostGetElementsAtTime(
	kostReal mu,                     /* standard gravitational parameter */
	const kostElements *elements,    /* pointer to orbital elements at epoch */
	kostElements *newElements,       /* pointer to where elements at epoch+timeSinceEpoch will be stored */
	kostReal timeSinceEpoch,         /* time since epoch in seconds */
	kostReal bodyRadius,             /* mean radius of the non-spherical body being orbited */
	kostReal jTwoCoeff);             /* J2 coefficient of the non-spherical body being orbited */

#ifdef __cplusplus
}
#endif

#endif

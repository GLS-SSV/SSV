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
This header file contains orbital element tools
*/

#ifndef KOST_ELEMENTS_H
#define KOST_ELEMENTS_H

#include "kost_types.h"

#ifdef __cplusplus
extern "C" {
#endif

kostReal kostGetMeanAnomaly(
	kostReal mu,                   /* standard gravitational parameter */
	const kostElements *elements); /* pointer to orbital elements at epoch */

int kostGetEccentricAnomaly(
	const kostElements *elements,      /* pointer to orbital elements at epoch */
	kostReal *eccentricAnomaly,        /* location where result will be stored */
	kostReal meanAnomaly,              /* mean anomaly */
	kostReal eccentricAnomalyEstimate, /* initial estimate of eccentric anomaly, start with mean anomaly if no better estimate available */
	kostReal maxRelativeError,         /* maximum relative error in eccentric anomaly */
	int maxIterations);                /* max number of iterations for calculating eccentric anomaly */

int kostGetTrueAnomaly(
	kostReal mu,                  /* standard gravitational parameter */
	const kostElements *elements, /* pointer to orbital elements at epoch */
	kostReal *trueAnomaly,        /* location where result will be stored */
	kostReal maxRelativeError,    /* maximum relative error in eccentric anomaly */
	int maxIterations);           /* max number of iterations for calculating eccentric anomaly */

kostReal kostGetTrueAnomaly2(
	kostReal mu,                  /* standard gravitational parameter */
	const kostElements *elements, /* pointer to orbital elements at epoch */
	kostReal eccentricAnomaly);   /* eccentric anomaly */

void kostElements2StateVector2(
	kostReal mu,                  /* standard gravitational parameter */
	const kostElements *elements, /* pointer to orbital elements at epoch */
	kostStateVector *state,       /* pointer to location where state vector at epoch will be stored */
	kostReal trueAnomaly);        /* true anomaly */

int kostElements2StateVector(
	kostReal mu,                  /* standard gravitational parameter */
	const kostElements *elements, /* pointer to orbital elements at epoch */
	kostStateVector *state,       /* pointer to location where state vector will be stored */
	kostReal maxRelativeError,    /* maximum relative error in eccentric anomaly */
	int maxIterations);           /* max number of iterations for calculating eccentric anomaly */

void kostStateVector2Elements(
	kostReal mu,                  /* standard gravitational parameter */
	const kostStateVector *state, /* pointer to state vector at epoch */
	kostElements *elements,       /* pointer to location where orbital elements at epoch will be stored */
	kostOrbitParam *params);      /* pointer to location where extra orbital parameters will be stored */

#ifdef __cplusplus
}
#endif

#endif

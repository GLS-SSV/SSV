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
Changelog:

CJP       = C J Plooy
TBlaxland = Tim Blaxland

Format:
-----------------
date (dd-mm-yyyy)
author
changes

-----------------
27-02-09
CJP
Merged kostGetElementsAtTime and kostGetElementsAtTime2
Renamed these files to kost_propagate.*

-----------------
03-02-09
TBlaxland
Finished kostGetElementsAtTime
Added kostGetElementsAtTime2
Modified kostElements2StateVectorAtTime to use kostGetElementsAtTime2

-----------------
01-02-09
TBlaxland
Fixed bugs in kostGetMeanAnomalyAtTime

-----------------
24-01-2009
CJP
Initial version
Moved functions from kost_elements.c to here
Renamed several functions
*/

/***************************************************************************
 * Usage notes - kostElements2StateVectorX and related functions:
 *
 * Parabolic orbits are NOT currently supported.
 *
 * Position as a function of time can be found by either:
 *
 * 1. A call to kostElements2StateVector1. Depending on settings for
 *    maxIterations and maxRelativeError, this may adversly affect frame
 *    rates in graphical applications.
 *
 * 2. To minimise impact on frame rates:
 *    2.1. Call kostGetMeanAnomaly
 *    2.2. Call kostGetEccentricAnomaly on successive time steps with a
 *         small number of iterations in each call. Each call takes the
 *         result of the previous call as its eccentricAnomalyEstimate.
 *         Repeat until kostGetEccentricAnomaly returns > 0.
 *    2.3. Call kostGetTrueAnomaly2.
 *    2.4. Call kostElements2StateVector2.
 **************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "kost_linalg.h"
#include "kost_constants.h"
#include "kost_math.h"
#include "kost_elements.h"

#include "kost_propagate.h"

kostReal kostGetMeanAnomalyAtTime(
	kostReal mu,                  /* standard gravitational parameter */
	const kostElements *elements, /* pointer to orbital elements at epoch */
	kostReal timeSinceEpoch)      /* time since epoch in seconds */
{
	/* Pseudocode
	 *
	 * calc mean motion
	 * calc change in mean anomaly
	 * calc mean anomaly */

	kostReal meanMotion, deltaMeanAnomaly, meanAnomaly;

	/* calc mean motion */
	meanMotion = sqrt(mu/pow(fabs(elements->a),3.0));

	/* calc change in mean anomaly */
	deltaMeanAnomaly = timeSinceEpoch * meanMotion;

	/* calc mean anomaly */
	/* fmod takes care of overflow in the case where the mean anomaly exceeds one revolution */
	meanAnomaly = fmod(elements->L - elements->omegab + deltaMeanAnomaly, M_TWOPI);

	if (meanAnomaly<0) meanAnomaly += M_TWOPI;

	return meanAnomaly;
}

int kostGetTrueAnomalyAtTime(
	kostReal mu,                  /* standard gravitational parameter */
	const kostElements *elements, /* pointer to orbital elements at epoch */
	kostReal *trueAnomaly,        /* location where result will be stored */
	kostReal timeSinceEpoch,      /* time since epoch in seconds */
	kostReal maxRelativeError,    /* maximum relative error in eccentric anomaly */
	int maxIterations)            /* max number of iterations for calculating eccentric anomaly */
{
	/* Returns number of iterations if successful, returns 0 otherwise. */

	/* Pseudocode
	 *
	 * get mean anomaly
	 * get eccentric anomaly
	 * calc true anomaly */

	int ret;
	kostReal meanAnomaly, eccentricAnomaly;

	/* get mean anomaly */
	meanAnomaly = kostGetMeanAnomalyAtTime(mu,elements,timeSinceEpoch);

	/* get eccentric anomaly */
	ret = kostGetEccentricAnomaly(elements,&eccentricAnomaly,meanAnomaly,meanAnomaly,maxRelativeError,maxIterations);

	/* calc true anomaly */
	*trueAnomaly = kostGetTrueAnomaly2(mu,elements,eccentricAnomaly);

	return ret;
}

kostReal kostGetLANAtTime(
	kostReal mu,                  /* standard gravitational parameter */
	const kostElements *elements, /* pointer to orbital elements at epoch */
	kostReal bodyRadius,          /* mean radius of the non-spherical body being orbited */
	kostReal jTwoCoeff,           /* J2 coefficient of the non-spherical body being orbited */
	kostReal timeSinceEpoch)      /* time since epoch in seconds */
{
	kostReal meanMotion;

	if (elements->e < 1.0) /* elliptical orbit */
	{
		meanMotion = sqrt(mu/pow(elements->a,3.0));
		return ( elements->theta + timeSinceEpoch * (-3.0 * meanMotion/2.0) * pow(bodyRadius/elements->a,2.0) * (cos(elements->i)/pow(1.0-pow(elements->e,2.0),2.0)) * jTwoCoeff );
	}
	else /* hyperbolic orbit - non spherical effect is negligible */
		return elements->theta;
}

kostReal kostGetArgPeAtTime(
	kostReal mu,                  /* standard gravitational parameter */
	const kostElements *elements, /* pointer to orbital elements at epoch */
	kostReal bodyRadius,          /* mean radius of the non-spherical body being orbited */
	kostReal jTwoCoeff,           /* J2 coefficient of the non-spherical body being orbited */
	kostReal timeSinceEpoch)      /* time since epoch in seconds */
{
	kostReal meanMotion;

	if (elements->e < 1.0) /* elliptical orbit */
	{
		meanMotion = sqrt(mu/pow(elements->a,3.0));
		return ( elements->omegab - elements->theta + timeSinceEpoch * (3.0 * meanMotion/4.0) * pow(bodyRadius/elements->a,2.0) * ( (5.0 * pow(cos(elements->i),2.0) - 1.0)/pow(1.0-pow(elements->e,2.0),2.0) ) * jTwoCoeff );
	}
	else /* hyperbolic orbit - non spherical effect is negligible */
		return ( elements->omegab - elements->theta );
}

int kostElements2StateVectorAtTime(
	kostReal mu,                  /* standard gravitational parameter */
	const kostElements *elements, /* pointer to orbital elements at epoch */
	kostStateVector *state,       /* pointer to location where state vectors at epoch+timeSinceEpoch will be stored */
	kostReal timeSinceEpoch,      /* time since epoch in seconds */
	kostReal maxRelativeError,    /* maximum relative error in eccentric anomaly */
	int maxIterations,            /* max number of iterations for calculating eccentric anomaly */
	kostReal bodyRadius,          /* mean radius of the non-spherical body being orbited */
	kostReal jTwoCoeff)           /* J2 coefficient of the non-spherical body being orbited */
{
	/* Returns number of iterations if successful, returns 0 otherwise. */
	
	/* Pseudocode
	 *
	 * get true anomaly
	 * get longitude of ascending node and argument of periapsis
	 * calc state vectors */

	int ret;
	kostReal trueAnomaly;
	kostElements updatedElements;

	/* get true anomaly */
	ret = kostGetTrueAnomalyAtTime(mu,elements,&trueAnomaly,timeSinceEpoch,maxRelativeError,maxIterations);

	/* update elements for new epoch */
	kostGetElementsAtTime(mu,elements,&updatedElements,timeSinceEpoch,bodyRadius,jTwoCoeff);

	/* calc state vectors */
	kostElements2StateVector2(mu,&updatedElements,state,trueAnomaly);	

	return ret;
}

void kostGetElementsAtTime(
	kostReal mu,                     /* standard gravitational parameter */
	const kostElements *elements,    /* pointer to orbital elements at epoch */
	kostElements *newElements,       /* pointer to location where elements at epoch+timeSinceEpoch will be stored */
	kostReal timeSinceEpoch,         /* time since epoch in seconds */
	kostReal bodyRadius,             /* mean radius of the non-spherical body being orbited */
	kostReal jTwoCoeff)              /* J2 coefficient of the non-spherical body being orbited */
{
	*newElements = *elements;

	/* Mean longitude: */
	newElements->L = kostGetMeanAnomalyAtTime(mu,newElements,timeSinceEpoch) + newElements->omegab;

	if(bodyRadius > KOST_VERYSMALL)
	{
		/* longitude of ascending node */
		newElements->theta =
			kostGetLANAtTime(mu,newElements,bodyRadius,jTwoCoeff,timeSinceEpoch);

		/* argument of periapsis */
		newElements->omegab =
			newElements->theta + 
			kostGetArgPeAtTime(mu,newElements,bodyRadius,jTwoCoeff,timeSinceEpoch);
	}
}

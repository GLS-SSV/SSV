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
17-04-2010
CJP
Fixed the size of a small addition to the velocity
vector for radial orbits, so that extreme cases are
better supported.
Various fixes to make these functions pass the
accuracy test

-----------------
19-03-2010
CJP
Applied some of the patches as suggested by
TBlaxland to fix a bug reported by Pagnatious
and to avoid having an undefined velocity in
kostElements2StateVector2.

Made some other changes to how velocity calculation
is done in kostElements2StateVector2.

Changed kostStateVector2Elements, so that it approximates
parabolic orbits by ellipses in some cases.

Changed the output range of kostGetMeanAnomaly, the meanAnomaly
input range of kostGetEccentricAnomaly, and the output range
of kostGetEccentricAnomaly, to fix a bug for hyperbolic
orbits.

Added support for radial orbits

-----------------
01-03-2009
CJP
Replaced while loops with fmod, as suggested by TBlaxland

-----------------
01-02-2009
TBlaxland
Fixed bugs in kostGetMeanAnomaly and kostElements2StateVector2

-----------------
24-01-2009
CJP
Moved some functions to kost_time.c

-----------------
19-01-2009
TBlaxland
Fixed some minor bugs
Changed kostElements2StateVector2 from left-hand to right-hand coordinates

-----------------
17-01-2009
CJP
Changed some whitespace formatting
Made TBlaxland's functions ANSI compatible

-----------------
14-01-2009
TBlaxland
Added implementation of:
	kostGetMeanAnomaly
	kostGetEccentricAnomaly
	kostGetTrueAnomaly1
	kostGetTrueAnomaly2
	kostGetLAN
	kostGetArgPe
	kostElements2StateVector1
	kostElements2StateVector2
Fixed division by zero at e==1.0
-----------------
16-11-2008
CJP
Initial version
Added implementation of:
	kostStateVector2Elements
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

kostReal kostGetMeanAnomaly(
	kostReal mu,                   /* standard gravitational parameter */
	const kostElements *elements)  /* pointer to orbital elements at epoch */
{
	kostReal meanAnomaly;
	/* calc mean anomaly */
	meanAnomaly = elements->L - elements->omegab;

	if(elements->e < 1.0)
	{
		/* check range is in 0 to 2*pi */
		if(meanAnomaly < 0.0) meanAnomaly += M_TWOPI;
		if(meanAnomaly >  M_TWOPI) meanAnomaly -= M_TWOPI;
	}

	return meanAnomaly;
}

int kostGetEccentricAnomaly(
	const kostElements *elements,      /* pointer to orbital elements at epoch */
	kostReal *eccentricAnomaly,        /* location where result will be stored */
	kostReal meanAnomaly,              /* mean anomaly */
	kostReal eccentricAnomalyEstimate, /* initial estimate of eccentric anomaly, start with mean anomaly if no better estimate available */
	kostReal maxRelativeError,         /* maximum relative error in eccentric anomaly */
	int maxIterations)                 /* max number of iterations for calculating eccentric anomaly */
{
	/* Code will terminate when either maxIterations or maxRelativeError is reached.
	 * Returns number of iterations if relativeError < maxRelativeError, returns 0 otherwise. */

	/* Pseudocode
	 *
	 * do
	 *  calculate next estimate of the root of Kepler's equation using Newton's method
	 *  calculate estimate of mean anomaly from estimate of eccentric anomaly
	 *  calculate relativeError
	 * while ((iterations<=maxIterations)&&(relativeError<maxRelativeError))
	 * if iterations<=maxIterations return iterations, else return 0 */

	int i;
	kostReal relativeError, meanAnomalyEstimate, e;

	if(elements->e == 0.0) /* circular orbit */
	{
		*eccentricAnomaly = meanAnomaly;
		return 1;
	}

	if(elements->e == 1.0) /* parabolic orbit - approximate to hyperbolic */
		e = elements->e + KOST_VERYSMALL;
	else
		e = elements->e;

	i=0;
	do
	{
		if(elements->e < 1.0) /* elliptical orbit */
		{
			/* calculate next estimate of the root of Kepler's equation using Newton's method */
			eccentricAnomalyEstimate = eccentricAnomalyEstimate - (eccentricAnomalyEstimate - e * sin(eccentricAnomalyEstimate) - meanAnomaly)/(1 - e * cos(eccentricAnomalyEstimate));
			/* calculate estimate of mean anomaly from estimate of eccentric anomaly */
			meanAnomalyEstimate = eccentricAnomalyEstimate - e * sin(eccentricAnomalyEstimate);
		}
		else /* hyperbolic orbit */
		{
			/* calculate next estimate of the root of Kepler's equation using Newton's method */
			eccentricAnomalyEstimate = eccentricAnomalyEstimate - (e * sinh(eccentricAnomalyEstimate) - eccentricAnomalyEstimate - meanAnomaly)/(e * cosh(eccentricAnomalyEstimate) - 1.0);
			/* calculate estimate of mean anomaly from estimate of eccentric anomaly */
			meanAnomalyEstimate = e * sinh(eccentricAnomalyEstimate) - eccentricAnomalyEstimate;
		}
		/* calculate relativeError */
		relativeError = 1.0 - meanAnomalyEstimate/meanAnomaly;
		i++;
	}
	while( (i<maxIterations)&&(fabs(relativeError)>fabs(maxRelativeError)) );

	if(elements->e < 1.0)
	{
		/* check range is in 0 to 2*pi */
		eccentricAnomalyEstimate = fmod(eccentricAnomalyEstimate, M_TWOPI);
		if(eccentricAnomalyEstimate < 0.0) eccentricAnomalyEstimate += M_TWOPI;
		if(eccentricAnomalyEstimate > M_TWOPI) eccentricAnomalyEstimate -= M_TWOPI;
	}

	*eccentricAnomaly = eccentricAnomalyEstimate;

	if( fabs(relativeError)<fabs(maxRelativeError) )
		return i;
	else
		return 0;
}

int kostGetTrueAnomaly(
	kostReal mu,                  /* standard gravitational parameter */
	const kostElements *elements, /* pointer to orbital elements at epoch */
	kostReal *trueAnomaly,        /* location where result will be stored */
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
	meanAnomaly = kostGetMeanAnomaly(mu,elements);

	/* get eccentric anomaly */
	if(elements->e < 1.0)
	{
		ret = kostGetEccentricAnomaly(
			elements, &eccentricAnomaly,
			meanAnomaly, meanAnomaly,
			maxRelativeError, maxIterations);
	}
	else
	{
		ret = kostGetEccentricAnomaly(
			elements, &eccentricAnomaly,
			meanAnomaly, log(2.0*meanAnomaly/elements->e + 1.8),
			maxRelativeError, maxIterations);
	}

	/* calc true anomaly */
	*trueAnomaly = kostGetTrueAnomaly2(mu,elements,eccentricAnomaly);

	return ret;
}

kostReal kostGetTrueAnomaly2(
	kostReal mu,                  /* standard gravitational parameter */
	const kostElements *elements, /* pointer to orbital elements at epoch */
	kostReal eccentricAnomaly)    /* eccentric anomaly */
{
	kostReal ret;
	if (elements->e < 1.0) /* elliptical orbit */
	{
		ret = 2.0 * atan(sqrt((1.0+elements->e)/(1.0-elements->e)) * tan(eccentricAnomaly/2.0));
	}
	else /* hyperbolic orbit */
	{
		ret = acos((cosh(eccentricAnomaly) - elements->e)/(1 - elements->e * cosh(eccentricAnomaly)));
		if(eccentricAnomaly < 0.0) ret = -ret; /* Always the same sign */
	}

	return ret;
}

void kostElements2StateVector2(
	kostReal mu,                  /* standard gravitational parameter */
	const kostElements *elements, /* pointer to orbital elements at epoch */
	kostStateVector *state,       /* pointer to location where state vector at epoch will be stored */
	kostReal trueAnomaly)         /* true anomaly */
{
	/* Pseudocode
	 *
	 * calc nodal vector, n
	 * calc angular momentum vector, h
	 * calc position vector
	 *  calc argument of position
	 *  calc direction of position vector
	 *  calc length of position vector
	 * calc velocity vector
	 *  calculate magnitude of velocity vector
	 *  calc components of velocity vector perpendicular and parallel to radius vector
	 *  add to get velocity vector */

	kostVector3 n; /* unit vector in direction of ascending node */
	kostVector3 h; /* angular momentum vector */
	kostVector3 north; /* unit vector pointing ecliptic north */
	kostVector3 vPro, vO; /* prograde and outward components of velocity vector */
	kostVector3 tmpv; /* temporary vector value */
	kostReal argPos; /* argument of position, measured from the longitude of ascending node */
	kostReal rPe, vPe; /* radius and velocity at periapsis */
	kostReal v2; /* magnitude squared of velocity vector */
	kostReal e; /* eccentricity */
	kostReal tmpr; /* temporary real value */

	e = elements->e;
	if(e == 1.0) /* parabolic orbit - approximate to hyperbolic orbit */
		e += KOST_VERYSMALL;

	/* calc nodal vector */
	n = kostConstructv(cos(elements->theta),sin(elements->theta),0.0);

	/* equatorial north vector */
	north = kostConstructv(0.0,0.0,1.0);

	/* calc angular momentum vector, h */
	/* projection of h in ecliptic (xy) plane */
	h = kostCrossProductvv(&n, &north);
	h = kostMulrv( sin(elements->i), &h);

	/* elevation of h */
	h.z = cos(elements->i);
	h = kostNormalv(&h);

	/* calc magnitude of h */
	/* calc radius and velocity at periapsis */
	if (e < 1.0) /* elliptical orbit */
	{
		rPe = elements->a * (1.0 - e * e) / (1.0 + e);
		vPe = sqrt(mu*(2.0/rPe - 1.0/elements->a));
	}
	else /* hyperbolic orbit */
	{
		rPe = fabs(elements->a) * (e * e - 1.0) / (1.0 + e);
		vPe = sqrt(mu*(2.0/rPe + 1.0/fabs(elements->a)));
	}
	/* calc h */
	h = kostMulrv(rPe*vPe,&h);

	/* calc position vector */
	/* calc argument of position */
	argPos = elements->omegab - elements->theta + trueAnomaly;

	/*
	calc direction of position vector:
	r/|r| = sin(ArgPos) * ((h / |h|) x n) + cos(argPos) * n
	*/
	tmpv = kostMulrv(cos(argPos), &n);
	state->pos = kostNormalv(&h);
	state->pos = kostCrossProductvv(&state->pos,&n);
	state->pos = kostMulrv(sin(argPos), &(state->pos));
	state->pos = kostAddvv(&(state->pos), &tmpv);

	/* calc length of position vector */
	if (e < 1.0) /* elliptical orbit */
		state->pos = kostMulrv(elements->a * (1.0 - e * e) /
		(1.0 + e * cos(trueAnomaly)),&(state->pos));
	else /* hyperbolic orbit */
		state->pos = kostMulrv(fabs(elements->a) * (e * e - 1.0) /
		(1.0 + e * cos(trueAnomaly)),&(state->pos));

	/* calc velocity vector */
	/*  calculate magnitude of velocity vector */
	if (e < 1.0) /* elliptical orbit */
		{v2 = mu*(2.0/kostAbsv(&(state->pos)) - 1.0/elements->a);}
	else /* hyperbolic orbit */
		{v2 = mu*(2.0/kostAbsv(&(state->pos)) + 1.0/fabs(elements->a));}

	/* calc components of velocity vector perpendicular and parallel to radius vector:
	
	perpendicular:
	vPro = (|h|/|pos|) * normal(h x pos)

	parallel:
	vO = sqrt(v^2 - |vPro|^2) * sign(sin(trueAnomaly)) * normal(pos)
	*/
	vPro = kostCrossProductvv(&h, &(state->pos));
	vPro = kostNormalv(&vPro);
	vPro = kostMulrv( kostAbsv(&h)/kostAbsv(&(state->pos)) , &vPro);

	tmpr = sin(trueAnomaly);
	if(tmpr == 0.0) /* check for apsis condition to avoid divide by zero */
	{
		vO = kostConstructv(0.0,0.0,0.0);
	}
	else
	{
		kostReal signSinTrueAnomaly = tmpr / fabs(tmpr);

		kostReal v0_sq = v2 - kostAbs2v(&vPro);
		/* check for small negative numbers resulting from rounding */
		if(v0_sq < 0.0) v0_sq = 0.0;

		vO = kostNormalv(&(state->pos));
		vO = kostMulrv(sqrt(v0_sq)*signSinTrueAnomaly, &vO);
	}

	/* add to get velocity vector */
	state->vel = kostAddvv(&vPro, &vO);
}

int kostElements2StateVector(
	kostReal mu,                  /* standard gravitational parameter */
	const kostElements *elements, /* pointer to orbital elements at epoch */
	kostStateVector *state,       /* pointer to location where state vector will be stored */
	kostReal maxRelativeError,    /* maximum relative error in eccentric anomaly */
	int maxIterations)            /* max number of iterations for calculating eccentric anomaly */
{
	/*
	Code based on kostElements2StateVector1, made by TBlaxland
	*/

	/* Returns number of iterations if successful, returns 0 otherwise. */
	
	/* Pseudocode
	 *
	 * get true anomaly
	 * get longitude of ascending node and argument of periapsis
	 * calc state vectors */

	int ret;
	kostReal trueAnomaly;

	/* get true anomaly */
	ret = kostGetTrueAnomaly(mu, elements, &trueAnomaly, maxRelativeError, maxIterations);

	/* calc state vectors */
	kostElements2StateVector2(mu, elements, state, trueAnomaly);	

	return ret;
}

void kostStateVector2Elements(
	kostReal mu,
	const kostStateVector *state,
	kostElements *elements,
	kostOrbitParam *params)
{
	/*
	See appendix C in orbiter.pdf
	*/

	kostVector3 vel, h, n, e;
	kostReal absh, absn, absr, abse, E, tPe;
	int isEquatorial, isCircular, isHyperbola;
	int sin_TrA_isNegative = 0;

	if(params == NULL)
	{
		static kostOrbitParam dummy;
		params = &dummy;
	}

	vel = state->vel;

	absr  = kostAbsv(&state->pos);

	h = kostCrossProductvv(&state->pos, &vel);
	absh = kostAbsv(&h);

	/*
	Radial orbits are not supported.
	e is not significantly different from 1.0
	if |h| < sqrt(epsilon * mu * |r|)
	*/
	if(absh*absh < KOST_VERYSMALL * mu * absr)
	{
		/*
		We assume that the position is non-zero.
		Otherwise, we are in a singularity anyway,
		and no formula will get us out of there.
		*/
		kostVector3 v_ortho, v_parallel;
		kostReal v_ortho_size;

		/* component of v parallel to pos */
		v_parallel = kostMulrv(
			kostDotProductvv(&state->pos, &vel) / kostAbs2v(&state->pos),
			&state->pos);

		/*
		Calculate how large the orthogonal component
		should be to make e significantly different
		from 1.0:
		
		|v_ortho| = sqrt(epsilon*mu / |r|)
		*/
		v_ortho_size = sqrt(KOST_VERYSMALL * mu / absr);

		/* New orthogonal component */
		v_ortho = kostConstructv(0.0, 0.0, 1.0);
		v_ortho = kostCrossProductvv(&state->pos, &v_ortho);
		v_ortho = kostMulrv(v_ortho_size / kostAbsv(&v_ortho), &v_ortho);

		/* replace the old orthogonal part */
		vel = kostAddvv(&v_parallel, &v_ortho);

		h = kostCrossProductvv(&state->pos, &vel);
		absh = kostAbsv(&h);
	}

	n = kostConstructv(-h.y, h.x, 0.0);
	absn = kostAbsv(&n);

	E = 0.5*kostAbs2v(&vel) - mu / absr;
	if (E == 0.0) 
		E = KOST_VERYSMALL;

	/*
	Alternative formula for e:
	e = (v x h) / mu - r / |r|
	*/
	e = kostCrossProductvv(&vel, &h);
	e = kostMulrv((absr/mu), &e);
	e = kostSubvv(&e, &state->pos);
	e = kostMulrv((1.0/absr), &e);

	abse = kostAbsv(&e);

	/* parabolic orbit are not supported */
	if(abse > 1.0-KOST_VERYSMALL && abse < 1.0+KOST_VERYSMALL)
	{
		if(E >= 0.0)
		{
			abse = 1.0+KOST_VERYSMALL; /* Approximate with hyperbolic */
		}
		else
		{
			abse = 1.0-KOST_VERYSMALL; /* Approximate with elliptic */
		}
	}

	isEquatorial = absn < KOST_VERYSMALL;
	isCircular   = abse < KOST_VERYSMALL;
	isHyperbola  = abse >= 1.0;

	/*SMa*/
	elements->a = -mu / (2.0*E);

	/*Ecc*/
	elements->e = abse;

	/*
	dp = a * (1-e)
	da = a * (1+e)
	*/
	params->PeD = elements->a * (1.0 - elements->e);
	params->ApD = elements->a * (1.0 + elements->e);

	/*Inc*/
	if(absh == 0.0)
	{
		/*
		Avoid division by zero absh
		By convention, take the smallest possible i,
		which is the angle between r and the
		equatorial plane.
		*/
		elements->i = asin(state->pos.z / absr);
	}
	else
	{
		elements->i = acos(h.z / absh);
	}

	/*LAN*/
	if(isEquatorial)
	{
		elements->theta = 0.0;
	}
	else
	{
		elements->theta = acos(n.x / absn);
		if(n.y < 0.0) elements->theta = M_TWOPI - elements->theta;
	}

	/*AgP*/
	params->AgP = 0.0;
	if(isCircular)
	{
		params->AgP = 0.0;
	}
	else if(isEquatorial)
	{
		params->AgP = atan2(e.y,e.x);
		if(h.z < 0.0) params->AgP = -params->AgP;
	}
	else
	{
		params->AgP = acos(kostDotProductvv(&n, &e) / (absn*abse));
		if(e.z < 0.0) params->AgP = M_TWOPI - params->AgP;
	}

	/*TrA*/
	sin_TrA_isNegative = 0;
	if(isCircular)
	{
		if(isEquatorial)
		{
			params->TrA = acos(state->pos.x / absr);
			if(vel.x > 0.0)
			{
				sin_TrA_isNegative = 1;
				params->TrA = M_TWOPI - params->TrA;
			}
		}
		else
		{
			params->TrA = acos(kostDotProductvv(&n, &state->pos) / (absn*absr));
			if(kostDotProductvv(&n, &vel) > 0.0)
			{
				sin_TrA_isNegative = 1;
				params->TrA = M_TWOPI - params->TrA;
			}
		}
	}
	else
	{
		kostReal tmp = kostDotProductvv(&e, &state->pos) / (abse*absr);

		/*Avoid acos out of range:*/
		if(tmp <= -1.0)
			{params->TrA = M_PI;}
		else if(tmp >= 1.0)
			{params->TrA = 0.0;}
		else
			{params->TrA = acos(tmp);}

		if(kostDotProductvv(&state->pos, &vel) < 0.0)
		{
			sin_TrA_isNegative = 1;
			params->TrA = M_TWOPI - params->TrA;
		}
	}

	/*Lec*/
	params->Lec = elements->a * elements->e;

	/*
	SMi
	b^2 = a^2 * (1 - e^2)
	*/
	if(isHyperbola)
	{
		params->SMi =
			sqrt(elements->a*elements->a* (elements->e*elements->e - 1.0));
	}
	else
	{
		params->SMi =
			sqrt(elements->a*elements->a* (1.0 - elements->e*elements->e));
	}

	/*LPe*/
	elements->omegab = fmod(elements->theta + params->AgP, M_TWOPI);

	/*EcA*/
	if(isHyperbola)
	{
		kostReal tmp = (1.0 - absr/elements->a) / elements->e;

		/*Avoid acosh out of range:*/
		if(tmp <= 1.0)
			{params->EcA = 0.0;}
		else
			{params->EcA = Acosh(tmp);}
	}
	else if(isCircular)
	{
		params->EcA = 0.0;
	}
	else
	{
		kostReal tmp = (1.0 - absr/elements->a) / elements->e;

		/*Avoid acos out of range:*/
		if(tmp <= -1.0)
			{params->EcA = M_PI;}
		else if(tmp >= 1.0)
			{params->EcA = 0.0;}
		else
			{params->EcA = acos(tmp);}
	}

	if(isHyperbola)
	{
		/*Copy sign from sin(TrA)*/
		if(sin_TrA_isNegative != (params->EcA < 0.0) )
			params->EcA = -params->EcA;
	}
	else
	{
		/*Same rule basically, but with EcA in 0..2pi range*/
		if(sin_TrA_isNegative)
			params->EcA = M_TWOPI - params->EcA;
	}

	/*MnA*/
	if(isHyperbola)
	{
		params->MnA = elements->e * sinh(params->EcA) - params->EcA;
	}
	else
	{
		params->MnA = params->EcA - elements->e * sin(params->EcA);
	}

	/*MnL*/
	elements->L = params->MnA + elements->omegab;
	if(!isHyperbola)
		elements->L = fmod(elements->L, M_TWOPI);

	/*TrL*/
	params->TrL = fmod(elements->omegab + params->TrA, M_TWOPI);

	/*
	T = 2*pi*sqrt(a^3 / mu)

	fabs is for supporting hyperbola
	*/
	params->T = 
		M_TWOPI * sqrt(fabs(elements->a*elements->a*elements->a/mu));

	/*
	Calculating PeT and ApT:
	*/
	tPe = params->MnA * params->T / M_TWOPI; /*Time since last Pe*/

	if(isHyperbola)
	{
		params->PeT = -tPe;
	}
	else
	{
		params->PeT = params->T - tPe;
	}

	params->ApT = 0.5*params->T - tPe;
	if(params->ApT < 0.0) params->ApT += params->T;
}

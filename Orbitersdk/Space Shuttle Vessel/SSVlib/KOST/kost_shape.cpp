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

#include "kost_constants.h"
#include "kost_linalg.h"

#include "kost_shape.h"

void kostElements2Shape(const kostElements *elements, kostOrbitShape *shape)
{
	unsigned int i = 0;

	/*Some utility values: */
	kostReal multiplier = elements->a * (1.0 - elements->e*elements->e);
	kostReal AgP = elements->omegab - elements->theta;

	/*
	First: Orbit in its own coordinate system:
	*/

	/*Pe, Ap*/
	shape->pe = kostConstructv( elements->a * (1.0 - elements->e), 0.0, 0.0);
	shape->ap = kostConstructv(-elements->a * (1.0 + elements->e), 0.0, 0.0);

	/*Points*/
	if(shape->numPoints == 1)
	{
		shape->points[0] = shape->pe;
	}
	else if(shape->numPoints > 1)
	{
		kostReal maxTrA, dTrA, TrA;

		/*Range of angles*/
		maxTrA = M_PI;
		if(elements->e >= 1.0)
		{
			maxTrA = acos(-1.0 / elements->e);

			/*Make it a bit smaller to avoid division by zero:*/
			maxTrA *= (((kostReal)shape->numPoints) / (shape->numPoints + 1));
		}

		/*Angle change per segment*/
		dTrA = (2*maxTrA) / (shape->numPoints - 1);

		TrA = -maxTrA;
		for(i=0; i < shape->numPoints; i++)
		{
			kostReal absr = fabs(multiplier / (1.0 + elements->e*cos(TrA)));

			kostVector3 direction = kostConstructv(cos(TrA), sin(TrA), 0.0);
			shape->points[i] = kostMulrv(absr, &direction);

			TrA += dTrA;
		}
	}


	/*AN*/
	{
		kostReal TrA = -AgP;
		kostReal absr = multiplier / (1.0 + elements->e*cos(TrA));

		if(absr <= 0.0)
		{
			shape->an = kostConstructv(0.0, 0.0, 0.0);
		}
		else
		{
			kostVector3 direction = kostConstructv(cos(TrA), sin(TrA), 0.0);
			shape->an = kostMulrv(absr, &direction);
		}
	}

	/*DN*/
	{
		kostReal TrA = M_PI - AgP;
		kostReal absr = multiplier / (1.0 + elements->e*cos(TrA));

		if(absr <= 0.0)
		{
			shape->dn = kostConstructv(0.0, 0.0, 0.0);
		}
		else
		{
			kostVector3 direction = kostConstructv(cos(TrA), sin(TrA), 0.0);
			shape->dn = kostMulrv(absr, &direction);
		}
	}



	/*
	Then: rotate the coordinates:
	*/
	{
		kostMatrix3 AgPMat, LANMat, IncMat, transform;

		kostMakeZRotm(&AgPMat, AgP);
		kostMakeXRotm(&IncMat, elements->i);
		kostMakeZRotm(&LANMat, elements->theta);

		/* Now, global = LANMat * IncMat * AgPMat * local: */
		transform = kostMulmm(&LANMat   , &IncMat);
		transform = kostMulmm(&transform, &AgPMat);

		shape->pe = kostMulmv(&transform, &(shape->pe));
		shape->ap = kostMulmv(&transform, &(shape->ap));
		shape->an = kostMulmv(&transform, &(shape->an));
		shape->dn = kostMulmv(&transform, &(shape->dn));

		if(shape->numPoints != 0)
			for(i=0; i < shape->numPoints; i++)
				shape->points[i] = kostMulmv(&transform, &(shape->points[i]));
	}
}


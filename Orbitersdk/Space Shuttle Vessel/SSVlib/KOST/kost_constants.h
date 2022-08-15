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
This header file contains some useful constants
*/

#ifndef KOST_CONSTANTS_H
#define KOST_CONSTANTS_H

#include <math.h>

/*From windows calculator:*/
#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

#ifndef M_TWOPI
#define M_TWOPI         (M_PI * 2.0)
#endif

/*From orbiter.pdf:*/
#define KOST_GRAVITATIONAL_CONSTANT (6.67259e-11)
#define KOST_ASTRONOMICAL_UNIT (1.49597870691e11)

/* Found this in SpeedCrunch (http://www.speedcrunch.org) */
#define KOST_PARSEC (3.08567802e16)

/* Calibrated on Orbiter (probably not exactly right): */
/*This is a mean solar day: */
#define KOST_DAY (86400.0)

#define KOST_YEAR (365.25 * KOST_DAY)

#endif



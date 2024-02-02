/****************************************************************************
  This file is part of Space Shuttle Vessel

  OneShot definition


  Space Shuttle Vessel is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Vessel is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Vessel; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file SSV-LICENSE.txt for more details.

  **************************************************************************/
#ifndef _ONESHOT_H
#define _ONESHOT_H


/**
* Implementation of a OneShot logic.
* When input chnges from false to true, the output is true for t time.
*/
class OneShot
{
	private:
		double t;// base time [s]
		double tcount;// time remaining in current cycle [s]

	public:
		OneShot( double t );
		~OneShot();

		bool Run( const double dt, const bool input );
};

#endif// _ONESHOT_H

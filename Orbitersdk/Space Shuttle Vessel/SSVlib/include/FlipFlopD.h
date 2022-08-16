/****************************************************************************
  This file is part of Space Shuttle Vessel

  FlipFlop D definition


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
  file Doc\Space Shuttle Vessel\GPL.txt for more details.

  **************************************************************************/
#ifndef _FLIPFLOPD_H
#define _FLIPFLOPD_H


/**
* Implementation of a flip-flop D.
*/
class FlipFlopD
{
	private:
		bool clk;
		bool q;

	public:
		FlipFlopD( void );
		FlipFlopD( bool init );
		~FlipFlopD( void );
		
		void SaveState( char* line ) const;
		void LoadState( const char* line );
		
		bool run( bool CLK, bool D );
		bool run( bool CLK, bool D, bool R );
		bool run( bool CLK, bool D, bool R, bool S );
		
		bool get( void ) const {return q;};
};

#endif// _FLIPFLOPD_H

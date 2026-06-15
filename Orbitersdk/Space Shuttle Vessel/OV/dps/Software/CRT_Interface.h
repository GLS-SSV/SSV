/****************************************************************************
  This file is part of Space Shuttle Vessel

  CRT Interface definition


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
#ifndef _CRT_IF_H_
#define _CRT_IF_H_


namespace dps
{
	class SimpleGPCSystem;
	class GeneralDisplays;

	/**
	 * System Services \ User Interface \ Operations Control
	 */
	class CRT_Interface
	{
		private:
			double step;

			SimpleGPCSystem* pGPC;
			GeneralDisplays* pSystemDisplays;
			GeneralDisplays* pUserDisplays;

			unsigned short fcw_buf_cnt;
			unsigned short fcw_buf[1528];// 1527 + 1 addr

			unsigned short fcw_addr[4];

			// FCW_BASIC components
			unsigned short mode;
			unsigned short size;
			unsigned short flash;
			unsigned short dash;
			unsigned short intensity;
			unsigned short medsorange;
			double rot;


			void DCIBHDR( const unsigned char deu );

		public:
			explicit CRT_Interface( SimpleGPCSystem* pGPC, GeneralDisplays* pSystemDisplays, GeneralDisplays* pUserDisplays );
			virtual ~CRT_Interface( void );


			static constexpr unsigned char DEUATT_NORMAL = 0;
			static constexpr unsigned char DEUATT_OVERBRIGHT = 1;
			static constexpr unsigned char DEUATT_FLASHING = 2;
			static constexpr unsigned char DEUATT_UNDERLINED = 4;
			static constexpr unsigned char DEUATT_DASHED = 8;
			static constexpr unsigned char DEUATT_LARGE = 16;
			static constexpr unsigned char DEUATT_MEDSORANGE = 32;


			void DMC_NEW_DISPLAY( void );
			void DCICYC( double simdt );


			// functions for drawing CRT
			void TextGrid( const unsigned short x, const unsigned short y, const char* text, const unsigned char attributes = DEUATT_NORMAL );
			void Text( const short x, const short y, const char* text, const unsigned char attributes = DEUATT_NORMAL, const double angle = 0.0 );

			void NumberGrid( const unsigned short x, const unsigned short y, const double num, const unsigned short size_i, const unsigned short size_f, const unsigned char attributes = DEUATT_NORMAL );// TODO remove default arg?
			void NumberSignGrid( const unsigned short x, const unsigned short y, const double num, const unsigned short size_i, const unsigned short size_f, const char plus, const char minus, const unsigned char attributes = DEUATT_NORMAL );// TODO remove default arg?
			void NumberGrid( const unsigned short x, const unsigned short y, const int num, const unsigned short size, const unsigned char attributes = DEUATT_NORMAL );
			void NumberSignGrid( const unsigned short x, const unsigned short y, const int num, const unsigned short size, const char plus, const char minus, const unsigned char attributes = DEUATT_NORMAL );

			void Line( const short x1, const short y1, const short x2, const short y2, const unsigned char attributes = DEUATT_NORMAL );
			void Circle( const short x, const short y, const unsigned short radius, const unsigned char attributes = DEUATT_NORMAL );

	};
}

#endif// _CRT_IF_H_

/****************************************************************************
  This file is part of Space Shuttle Vessel

  IDP software definition


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

#ifndef _dps_IDP_SW_H_
#define _dps_IDP_SW_H_


namespace vc
{
	class MDU;
}

namespace dps
{
	class IDP;


	class IDP_software
	{
		private:
			IDP* pIDP;

			void DCP( const double dt );
			void MEDS( void );

			/**
			 * Returns true when symbol should be hidden.
			 */
			bool GetFlash( void ) const;

			/**
			 * Maps C0 control code chars (0x00-0x1F) to other location.
			 */
			void CharMap( char* str ) const;

			void ProcessFCW( const unsigned short* fcw_buff, unsigned short len, vc::MDU* pMDU ) const;

			void ProcessKeyboard( void );
			bool ConvertKeyCode( const unsigned short deu_kybd_key_code, unsigned char& deu_gpc_key_code );
			void FormatSPL( void );
			void AddSPLatt( unsigned int start, unsigned int len, char att );
			/**
			 * Saves keys for transmission to GPC.
			 */
			void SaveKeys( void );
			/**
			 * pack keys for transmission to GPC in poll response.
			 */
			void PackKeys( void );

			void ConvertTime( const long long input, unsigned short& d, unsigned short& h, unsigned short& m, unsigned short& s ) const;

			void PrintClocks( vc::MDU* pMDU );
			void PrintScratchPadLine( vc::MDU* pMDU ) const;
			void PrintDisplay( vc::MDU* pMDU ) const;
			void PrintMessageLine( vc::MDU* pMDU ) const;
			void PrintPollFail( vc::MDU* pMDU ) const;
			void PrintBigX( vc::MDU* pMDU ) const;

			void TextGrid( vc::MDU* pMDU, const short x, const short y, const char* txt, const unsigned int len, const unsigned char attributes, const double rot ) const;
			void Text( vc::MDU* pMDU, const short x, const short y, const char* txt, const unsigned int len, const unsigned char attributes, const double rot ) const;
			void Line( vc::MDU* pMDU, const short x1, const short y1, const short x2, const short y2, const unsigned char attributes ) const;
			void Circle( vc::MDU* pMDU, const short x, const short y, const short radius, const unsigned char attributes ) const;

		public:
			explicit IDP_software( IDP* pIDP );
			virtual ~IDP_software( void );

			void RUN( const double dt );

			void OnPaint( vc::MDU* pMDU );
	};
}

#endif// _dps_IDP_SW_H_

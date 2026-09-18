/****************************************************************************
  This file is part of Space Shuttle Vessel

  Horizontal Situation SPEC Control Segment definition


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

#ifndef _dps_HORIZ_SIT_SPEC_H_
#define _dps_HORIZ_SIT_SPEC_H_


#include "../ControlSegment.h"


namespace dps
{
	class HORIZ_SIT_SPEC_Block_1 : public CS_Block
	{
		public:
			HORIZ_SIT_SPEC_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS );

			void Init( void ) override;
			void Input( void ) override;
			void CleanUp( void ) override;
	};

	class HORIZ_SIT_SPEC : public ControlSegmentSPEC
	{
		public:
			HORIZ_SIT_SPEC( SimpleGPCSystem* pGPC );

			void Init( void ) override;
			void CleanUp( void ) override;

			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;
	};
}

#endif// _dps_HORIZ_SIT_SPEC_H_

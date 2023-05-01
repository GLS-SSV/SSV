/****************************************************************************
  This file is part of Space Shuttle Vessel

  RM/RCS Display Processing definition


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
#ifndef _dps_RMRCSDISPPROC_H_
#define _dps_RMRCSDISPPROC_H_


#include "..\SimpleGPCSoftware.h"


namespace dps
{
	class RM_RCS_Display_Processing:public SimpleGPCSoftware
	{
		private:
			void JetManfStatus( const unsigned int jetid, const unsigned int outid );
			void RCSManifOPCLIOStatus( const unsigned int dilemmaaddr, const unsigned int dilemmaidx, const unsigned int outaddr, const unsigned int outidx, const unsigned int outsz );
			void CopyControlFlags( const unsigned int maxinidx, const unsigned int inaddr, const unsigned int inidx, const unsigned int maxoutidx, const unsigned int outaddr, const unsigned int outidxfwd, const unsigned int outidxleft, const unsigned int outidxright );

		public:
			explicit RM_RCS_Display_Processing( SimpleGPCSystem* _gpc );
			~RM_RCS_Display_Processing( void );

			void OnPreStep( double simt, double simdt, double mjd ) override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;
	};
}


#endif// _dps_RMRCSDISPPROC_H_

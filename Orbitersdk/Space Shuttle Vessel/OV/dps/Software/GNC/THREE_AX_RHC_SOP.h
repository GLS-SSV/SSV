/****************************************************************************
  This file is part of Space Shuttle Vessel

  3-Axis Rotational Hand Controller Subsystem Operating Program definition


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

#ifndef _dps_3_AX_RHC_SOP_H_
#define _dps_3_AX_RHC_SOP_H_


#include "../SimpleGPCSoftware.h"


namespace dps
{
	class RHC_RM;

	/**
	 * @brief	Implementation of the 3-Axis RHC SOP software that runs in the GPCs.
	 *
	 * This class receives and processes RHC commands.
	 */
	class THREE_AX_RHC_SOP:public SimpleGPCSoftware
	{
		private:
			RHC_RM* pRHC_RM;

			float DACC;// compensated left roll [deg]
			float DAPC;// compensated right roll [deg]
			float DECC;// compensated left pitch [deg]
			float DEPC;// compensated right pitch [deg]
			float DYCC;// compensated left yaw [deg]
			float DYPC;// compensated right yaw [deg]

			float DACV;// validated left roll [deg]
			float DAPV;// validated right roll [deg]
			float DECV;// validated left pitch [deg]
			float DEPV;// validated right pitch [deg]
			float DYCV;// validated left yaw [deg]
			float DYPV;// validated right yaw [deg]

			float DACDB;// deadbanded left roll [deg]
			float DAPDB;// deadbanded right roll [deg]
			float DECDB;// deadbanded left pitch [deg]
			float DEPDB;// deadbanded right pitch [deg]
			float DYCDB;// deadbanded left yaw [deg]
			float DYPDB;// deadbanded right yaw [deg]

			short DACD;// out-of-detent in left roll
			short DAPD;// out-of-detent in right roll
			short DECD;// out-of-detent in left pitch
			short DEPD;// out-of-detent in right pitch
			short DYCD;// out-of-detent in left yaw
			short DYPD;// out-of-detent in right yaw

			bool DACSS;// past soft-stop in left roll
			bool DAPSS;// past soft-stop in right roll
			bool DECSS;// past soft-stop in left pitch
			bool DEPSS;// past soft-stop in right pitch
			bool DYCSS;// past soft-stop in left yaw
			bool DYPSS;// past soft-stop in right yaw


			void _3_AX_COMP( void );
			void _3_AX_VALID( void );
			void _3_AX_DB( void );
			void _3_AX_STA_SEL( void );
			void _3_AX_DETENT( void );
			void INT_STA_SEL( void );
			void _3_AX_SOFT_STOP( void );
			void DISC_STA_SEL( void );

		public:
			explicit THREE_AX_RHC_SOP( SimpleGPCSystem* _gpc );
			~THREE_AX_RHC_SOP( void );

			void Realize( void ) override;

			void OnPreStep( double simt, double simdt, double mjd ) override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;
	};
}

#endif// _dps_3_AX_RHC_SOP_H_

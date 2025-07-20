/****************************************************************************
  This file is part of Space Shuttle Vessel

  Orbital 3-Axis Rotational Hand Controller Subsystem Operating Program
  definition

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

#ifndef _dps_ORB_3_AX_RHC_SOP_H_
#define _dps_ORB_3_AX_RHC_SOP_H_


#include "../SimpleGPCSoftware.h"


namespace dps
{
	class RHC_RM;

	/**
	 * @brief	Implementation of the Orbital 3-Axis RHC SOP software that runs in the GPCs.
	 *
	 * This class receives and processes RHC commands.
	 */
	class ORB_THREE_AX_RHC_SOP:public SimpleGPCSoftware
	{
		private:
			RHC_RM* pRHC_RM;

			float DACC;// compensated left roll [deg]
			float DAPC;// compensated right roll [deg]
			float DAAC;// compensated aft roll [deg]
			float DECC;// compensated left pitch [deg]
			float DEPC;// compensated right pitch [deg]
			float DEAC;// compensated aft pitch [deg]
			float DYCC;// compensated left yaw [deg]
			float DYPC;// compensated right yaw [deg]
			float DYAC;// compensated aft yaw [deg]

			float DACV;// validated left roll [deg]
			float DAPV;// validated right roll [deg]
			float DAAV;// validated aft roll [deg]
			float DECV;// validated left pitch [deg]
			float DEPV;// validated right pitch [deg]
			float DEAV;// validated aft pitch [deg]
			float DYCV;// validated left yaw [deg]
			float DYPV;// validated right yaw [deg]
			float DYAV;// validated aft yaw [deg]

			float DACDB;// deadbanded left roll [deg]
			float DAPDB;// deadbanded right roll [deg]
			float DAADB;// deadbanded aft roll [deg]
			float DAAT;// deadbanded aft roll [deg] (transformed)
			float DECDB;// deadbanded left pitch [deg]
			float DEPDB;// deadbanded right pitch [deg]
			float DEADB;// deadbanded aft pitch [deg]
			float DEAT;// deadbanded aft pitch [deg] (transformed)
			float DYCDB;// deadbanded left yaw [deg]
			float DYPDB;// deadbanded right yaw [deg]
			float DYADB;// deadbanded aft yaw [deg]
			float DYAT;// deadbanded aft yaw [deg] (transformed)

			short DACD;// out-of-detent in left roll
			short DAPD;// out-of-detent in right roll
			short DAAD;// out-of-detent in aft roll
			short DAADT;// out-of-detent in aft roll (transformed)
			short DECD;// out-of-detent in left pitch
			short DEPD;// out-of-detent in right pitch
			short DEAD;// out-of-detent in aft pitch
			short DEADT;// out-of-detent in aft pitch (transformed)
			short DYCD;// out-of-detent in left yaw
			short DYPD;// out-of-detent in right yaw
			short DYAD;// out-of-detent in aft yaw
			short DYADT;// out-of-detent in aft yaw (transformed)

			bool DACSS;// past soft-stop in left roll
			bool DAPSS;// past soft-stop in right roll
			bool DAASS;// past soft-stop in aft roll
			bool DAASST;// past soft-stop in aft roll (transformed)
			bool DECSS;// past soft-stop in left pitch
			bool DEPSS;// past soft-stop in right pitch
			bool DEASS;// past soft-stop in aft pitch
			bool DEASST;// past soft-stop in aft pitch (transformed)
			bool DYCSS;// past soft-stop in left yaw
			bool DYPSS;// past soft-stop in right yaw
			bool DYASS;// past soft-stop in aft yaw
			bool DYASST;// past soft-stop in aft yaw (transformed)


			void ORB_3_COMP( void );
			void ORB_3_VALID( void );
			void ORB_3_DB( void );
			void RHC_SCALAR_TRANS( void );
			void ORB_3_STA_SEL( void );
			void ORB_3_DETENT( void );
			void RHC_INT_TRANS( void );
			void ORB_INT_STA_SEL( void );
			void ORB_3_SOFT_STOP( void );
			void RHC_DISC_TRANS( void );
			void ORB_DISC_STA_SEC( void );

		public:
			explicit ORB_THREE_AX_RHC_SOP( SimpleGPCSystem* _gpc );
			~ORB_THREE_AX_RHC_SOP( void );

			void Realize( void ) override;

			void OnPreStep( double simt, double simdt, double mjd ) override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;
	};
}

#endif// _dps_ORB_3_AX_RHC_SOP_H_

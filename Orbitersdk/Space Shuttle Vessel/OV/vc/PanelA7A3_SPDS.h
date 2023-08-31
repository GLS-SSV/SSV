/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel A7A3 SPDS definition



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
#ifndef __VC_PANELA7A3SPDS_H
#define __VC_PANELA7A3SPDS_H


#include "AtlantisPanel.h"


namespace vc
{
	class CircuitBreaker;
	class LockableLever2;
	class StandardTalkback3;
	class StandardTalkback2;


	class PanelA7A3_SPDS : public AtlantisPanel
	{
		private:
			CircuitBreaker* pPAYLOAD_RELEASE_MN_A;
			CircuitBreaker* pPAYLOAD_RELEASE_MN_B;
			CircuitBreaker* pPEDESTAL_DRIVE_XFER_MN_A;
			CircuitBreaker* pPEDESTAL_DRIVE_XFER_MN_B;

			LockableLever2* pPAYLOAD_RELEASE_SYS_A_ARM;
			LockableLever2* pPAYLOAD_RELEASE_SYS_B_ARM;
			LockableLever2* pPAYLOAD_RELEASE_SYS_A_FIRE;
			LockableLever2* pPAYLOAD_RELEASE_SYS_B_FIRE;
			LockableLever2* pPEDESTAL_DRIVE_XFER_SYS_A_ARM;
			LockableLever2* pPEDESTAL_DRIVE_XFER_SYS_B_ARM;
			LockableLever2* pPEDESTAL_DRIVE_XFER_SYS_A_FIRE;
			LockableLever2* pPEDESTAL_DRIVE_XFER_SYS_B_FIRE;

			StandardTalkback3* pPAYLOAD_RELEASE_PRI_PED_SYS_A;
			StandardTalkback3* pPAYLOAD_RELEASE_PRI_PED_SYS_B;
			StandardTalkback3* pPAYLOAD_RELEASE_SEC_PED_SYS_A;
			StandardTalkback3* pPAYLOAD_RELEASE_SEC_PED_SYS_B;
			StandardTalkback3* pPEDESTAL_DRIVE_XFER_PRI_PED_SYS_A;
			StandardTalkback3* pPEDESTAL_DRIVE_XFER_PRI_PED_SYS_B;
			StandardTalkback3* pPEDESTAL_DRIVE_XFER_SEC_PED_SYS_A;
			StandardTalkback3* pPEDESTAL_DRIVE_XFER_SEC_PED_SYS_B;

			StandardTalkback2* pZo_EXTEND_PRIMARY_EXTEND;
			StandardTalkback2* pZo_EXTEND_SECONDARY_EXTEND;
			StandardTalkback2* pYo_DRIVE_POS_PRIMARY_INBD;
			StandardTalkback2* pYo_DRIVE_POS_PRIMARY_BERTHED;
			StandardTalkback2* pYo_DRIVE_POS_PRIMARY_OUTBD;
			StandardTalkback2* pYo_DRIVE_POS_SECONDARY_INBD;
			StandardTalkback2* pYo_DRIVE_POS_SECONDARY_BERTHED;
			StandardTalkback2* pYo_DRIVE_POS_SECONDARY_OUTBD;
			StandardTalkback2* pRDU_PRIMARY_REBERTH;
			StandardTalkback2* pRDU_PRIMARY_STOW;
			StandardTalkback2* pRDU_PRIMARY_DEPLOY;
			StandardTalkback2* pRDU_SECONDARY_REBERTH;
			StandardTalkback2* pRDU_SECONDARY_STOW;
			StandardTalkback2* pRDU_SECONDARY_DEPLOY;

			// panel input
			DiscInPort dipPAYLOAD_RELEASE_MN_A;
			DiscInPort dipPAYLOAD_RELEASE_MN_B;
			DiscInPort dipPAYLOAD_RELEASE_SYS_A_ARM;
			DiscInPort dipPAYLOAD_RELEASE_SYS_B_ARM;
			DiscInPort dipPAYLOAD_RELEASE_SYS_A_FIRE;
			DiscInPort dipPAYLOAD_RELEASE_SYS_B_FIRE;
			DiscInPort dipPEDESTAL_DRIVE_XFER_MN_A;
			DiscInPort dipPEDESTAL_DRIVE_XFER_MN_B;
			DiscInPort dipPEDESTAL_DRIVE_XFER_SYS_A_ARM;
			DiscInPort dipPEDESTAL_DRIVE_XFER_SYS_B_ARM;
			DiscInPort dipPEDESTAL_DRIVE_XFER_SYS_A_FIRE;
			DiscInPort dipPEDESTAL_DRIVE_XFER_SYS_B_FIRE;

			// panel output
			DiscOutPort dopPAYLOAD_RELEASE_SYS_A_ARM;
			DiscOutPort dopPAYLOAD_RELEASE_SYS_B_ARM;
			DiscOutPort dopPAYLOAD_RELEASE_SYS_A_FIRE;
			DiscOutPort dopPAYLOAD_RELEASE_SYS_B_FIRE;
			DiscOutPort dopPEDESTAL_DRIVE_XFER_SYS_A_ARM;
			DiscOutPort dopPEDESTAL_DRIVE_XFER_SYS_B_ARM;
			DiscOutPort dopPEDESTAL_DRIVE_XFER_SYS_A_FIRE;
			DiscOutPort dopPEDESTAL_DRIVE_XFER_SYS_B_FIRE;

		public:
			explicit PanelA7A3_SPDS( Atlantis* _sts );
			virtual ~PanelA7A3_SPDS( void );

			void DefineVC( void ) override;
			void RegisterVC( void ) override;
			void Realize( void ) override;
			void OnPreStep( double simt, double simdt, double mjd ) override;
	};
}

#endif// __VC_PANELA7A3SPDS_H

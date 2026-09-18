/****************************************************************************
  This file is part of Space Shuttle Vessel

  LPS Interface definition


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
#ifndef _LPS_INTERFACE_H_
#define _LPS_INTERFACE_H_


#include "../AtlantisSubsystem.h"
#include <BusTerminal.h>
#include <vector>


using namespace discsignals;


namespace dps
{
	class LPS_Interface:public AtlantisSubsystem, public BusTerminal
	{
		protected:
			unsigned short ldbdata[32];
			unsigned short ldbdatalen;

			bool hasdata;

			unsigned short id;

			double GMTLO;
			bool LPSGoForAutoSequenceStart;
			bool LPSGoForEngineStart;
			bool GMTLOSetCommand;
			bool ResumeCountCommand;
			bool LPSCountdownHold;
			bool RecycleCountCmd;
			bool MPS_Slew;
			bool Aero_Slew;
			bool SRB_Slew;

			bool RSCountdownHold;
			bool LaunchSequenceAbort;
			unsigned int HoldFlags;

			void AssembleData( void );

		public:
			LPS_Interface( AtlantisSubsystemDirector* _director, BusManager* pBusManager );
			virtual ~LPS_Interface();

			void Rx( const BUS_ID id, void* data, const unsigned short datalen ) override;

			// old LPS interface
			void SetGMTLO( double GMTLO );
			void SetGMTLOSetCommandFlag( bool val );
			void SetLPSCountdownHoldFlag( bool val );
			void SetLPSGoForAutoSequenceStartFlag( bool val );
			void SetLPSGoForEngineStartFlag( bool val );
			void SetResumeCountCommandFlag( bool val );
			bool GetRSCountdownHoldFlag( void ) const;
			bool GetLaunchSequenceAbortFlag( void ) const;
			unsigned int GetHoldFlags( void ) const;
			void SetSSMEActPos( int num, double Ppos, double Ypos );
	};
}

#endif// _LPS_INTERFACE_H_

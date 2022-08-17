/****************************************************************************
  This file is part of Space Shuttle Vessel

  Reaction Jet Driver definition


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
#ifndef __RJD_H_
#define __RJD_H_


#include "..\AtlantisSubsystem.h"
#include <discsignals.h>


using namespace discsignals;

/*
The RJD driver and logic power for the aft and forward RJDs are controlled by the RJDA-1A L2/R2, RJDA-2A L4/R4
and RJDF-1B F1 manf logic and driver on and off switches on panel O14; RJDA-1B L1/L5/R1 and RJDF-1A F2 manf
logic and driver switches on panel O15; and RJDA-2B L3/R3/R5, RJDF-2A F3 and RJDF-2A F4/F5 manf logic and driver switches on panel O16.
*/
/*
RJDF-1A F2		O15
RJDF-1B F1		O14
RJDF-2A F3		O16
RJDF-2B F4/F5		O16

RJDA-1A L2/R2		O14
RJDA-1B L1/L5/R1	O15
RJDA-2A L4/R4		O14
RJDA-2B L3/R3/R5	O16

RJD MANF L5/F5/R5	O16
*/
namespace rcs
{
	class RJD_side;

	class RJD:public AtlantisSubsystem
	{
		friend class Atlantis;

		private:
			/**
			 * 0) RJDF-1
			 * 1) RJDF-2
			 * 2) RJDA-1
			 * 3) RJDA-2
			 */
			unsigned short ID;

			RJD_side* sideA;
			RJD_side* sideB;

		public:
			RJD( AtlantisSubsystemDirector* _director, const string& _ident, unsigned short ID );
			virtual ~RJD( void );
		
			void Realize( void ) override;
			void OnPreStep( double fSimT, double fDeltaT, double fMJD ) override;
	};

	class RJD_side
	{
		private:
			unsigned short jets;

			vector<double> PC_output;// previous output 0.0 or 15.0 [v]
			vector<DiscInPort> CMD_A;
			vector<DiscInPort> CMD_B;
			vector<DiscInPort> PC_Ind;
			vector<DiscOutPort> PC_Evt;
			vector<DiscOutPort> Driver;

		public:
			explicit RJD_side( unsigned short jets );
			virtual ~RJD_side( void );

			void ConnectJet( unsigned short jet, DiscreteBundle* CMD_A_bundle, unsigned int CMD_A_line, DiscreteBundle* CMD_B_bundle, unsigned int CMD_B_line, DiscreteBundle* PC_Evt_bundle, unsigned int PC_Evt_line, DiscreteBundle* PC_Ind_bundle, unsigned int PC_Ind_line, DiscreteBundle* Driver_bundle, unsigned int Driver_line );
			void OnPreStep( double fSimT, double fDeltaT );
	};
}


#endif// __RJD_H_

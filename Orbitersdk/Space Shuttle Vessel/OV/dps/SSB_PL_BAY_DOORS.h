/****************************************************************************
  This file is part of Space Shuttle Vessel

  Payload Bay Doors software definition


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

#ifndef _dps_SSB_PL_BAY_DOORS_H_
#define _dps_SSB_PL_BAY_DOORS_H_


#include "SimpleGPCSoftware.h"


namespace dps
{
	using namespace discsignals;

	/**
	 * @brief	Implementation of the Payload Bay Doors software that runs in the GPCs.
	 *
	 * This class generates commands to drive Payload Bay doors and latches.
	 */
	class SSB_PL_BAY_DOORS:public SimpleGPCSoftware
	{
		private:
			unsigned short PF1_IOM3_CH0;
			unsigned short PF1_IOM6_CH0;
			unsigned short PF1_IOM9_CH0;
			unsigned short PF2_IOM3_CH0;
			unsigned short PF2_IOM6_CH0;
			unsigned short PF2_IOM9_CH0;

			bool SSB_PBD_MORE_WORK_IND;
			double SSB_LATCH_DOOR_EXPIR_TIME;
			bool SSB_OPEN_CLOSE_FEEDBACK_INDIC;
			unsigned short SSB_PREVIOUS_SWITCH_POS;
			/**
			 * 1 = op; 2 = cl
			 */
			unsigned short SSB_OPEN_CLOSE_COMPLETE;
			unsigned short SSB_CURRENT_LATCH_DOOR_POINTER;
			unsigned short SSB_COMMANDS_ENABLED_ARRAY[6][2];

			/*
			PF1_IOM2_CH0
			0 - Right Door Open Command 1	V37K2050Y
			1 - Right Door Close Command 1	V37K2060Y
			2 - Right FWD BHD Latch Group Open Command 1	V37K2100Y
			3 - Right FWD BHD Latch Group Close Command 1	V37K2110Y
			4 - Right AFT BHD Latch Group Open Command 2	V37K2121Y
			5 - Right AFT BHD Latch Group Close Command 2	V37K2131Y
			6 - Power On/Off Command 1A	V37K2000Y
			7 - Power On/Off Command 3A	V37K2004Y
			8 - Power On/Off Command 4A	V37K2006Y
			9 - 
			10 - 
			11 - 
			12 - 
			13 - 
			14 - 
			15 - 
			*/
			unsigned short CSBB_PF01_OUTPUT_1;
			/*
			PF1_IOM7_CH0
			0 - 
			1 - 
			2 - Centerline Latch Group 1-4 Open Command 1	V37K2200Y
			3 - Centerline Latch Group 1-4 Close Command 1	V37K2210Y
			4 - Centerline Latch Group 5-8 Open Command 1	V37K2220Y
			5 - Centerline Latch Group 5-8 Close Command 1	V37K2230Y
			6 - Centerline Latch Group 9-12 Open Command 1	V37K2240Y
			7 - Centerline Latch Group 9-12 Close Command 1	V37K2250Y
			8 - Centerline Latch Group 13-16 Open Command 2		V37K2261Y
			9 - Centerline Latch Group 13-16 Close Command 2	V37K2271Y
			10 - 
			11 - 
			12 - 
			13 - 
			14 - 
			15 - 
			*/
			unsigned short CSBB_PF01_OUTPUT_2;
			/*
			PF1_IOM14_CH0
			0 - Left Door Open Command 2	V37K2071Y
			1 - Left Door Close Command 2	V37K2081Y
			2 - Left FWD BHD Latch Group Open Command 1	V37K2150Y
			3 - Left FWD BHD Latch Group Close Command 1	V37K2160Y
			4 - Left AFT BHD Latch Group Open Command 1	V37K2170Y
			5 - Left AFT BHD Latch Group Close Command 1	V37K2180Y
			6 - 
			7 - Power On/Off Command 3B	V37K2005Y
			8 - Power On/Off Command 4B	V37K2007Y
			9 - 
			10 - 
			11 - 
			12 - 
			13 - 
			14 - 
			15 - 
			*/
			unsigned short CSBB_PF01_OUTPUT_3;
			/*
			PF1_IOM14_CH2
			0 - 
			1 - 
			2 - 
			3 - 
			4 - 
			5 - 
			6 - 
			7 - Power On/Off Command 1B	V37K2001Y
			8 - 
			9 - 
			10 - 
			11 - 
			12 - 
			13 - 
			14 - 
			15 - 
			*/
			unsigned short CSBB_PF01_OUTPUT_4;

			/*
			PF2_IOM2_CH0
			0 - Right Door Open Command 2	V37K2051Y
			1 - Right Door Close Command 2	V37K2061Y
			2 - Right FWD BHD Latch Group Open Command 2	V37K2101Y
			3 - Right FWD BHD Latch Group Close Command 2	V37K2111Y
			4 - Right AFT BHD Latch Group Open Command 1	V37K2120Y
			5 - Right AFT BHD Latch Group Close Command 1	V37K2130Y
			6 - Power On/Off Command 2A	V37K2002Y
			7 - Power On/Off Command 5A	V37K2008Y
			8 - Power On/Off Command 6A	V37K2010Y
			9 - 
			10 - 
			11 - 
			12 - 
			13 - 
			14 - 
			15 - 
			*/
			unsigned short CSBB_PF02_OUTPUT_1;
			/*
			PF2_IOM7_CH0
			0 - 
			1 - 
			2 - Centerline Latch Group 1-4 Open Command 2	V37K2201Y
			3 - Centerline Latch Group 1-4 Close Command 2	V37K2211Y
			4 - Centerline Latch Group 5-8 Open Command 2	V37K2221Y
			5 - Centerline Latch Group 5-8 Close Command 2	V37K2231Y
			6 - Centerline Latch Group 9-12 Open Command 2	V37K2241Y
			7 - Centerline Latch Group 9-12 Close Command 2	V37K2251Y
			8 - Centerline Latch Group 13-16 Open Command 1		V37K2260Y
			9 - Centerline Latch Group 13-16 Close Command 1	V37K2270Y
			10 - 
			11 - 
			12 - 
			13 - 
			14 - 
			15 - 
			*/
			unsigned short CSBB_PF02_OUTPUT_2;
			/*
			PF2_IOM14_CH0
			0 - Left Door Open Command 1	V37K2070Y
			1 - Left Door Close Command 1	V37K2080Y
			2 - Left FWD BHD Latch Group Open Command 2	V37K2151Y
			3 - Left FWD BHD Latch Group Close Command 2	V37K2161Y
			4 - Left AFT BHD Latch Group Open Command 2	V37K2171Y
			5 - Left AFT BHD Latch Group Close Command 2	V37K2181Y
			6 - Power On/Off Command 2B	V37K2003Y
			7 - Power On/Off Command 5B	V37K2009Y
			8 - 
			9 - 
			10 - 
			11 - 
			12 - 
			13 - 
			14 - 
			15 - 
			*/
			unsigned short CSBB_PF02_OUTPUT_3;
			/*
			PF2_IOM14_CH2
			0 - 
			1 - Power On/Off Command 6B	V37K2011Y
			2 - 
			3 - 
			4 - 
			5 - 
			6 - 
			7 - 
			8 - 
			9 - 
			10 - 
			11 - 
			12 - 
			13 - 
			14 - 
			15 - 
			*/
			unsigned short CSBB_PF02_OUTPUT_4;


			void PBD_LATCH_STATUS( const bool p1, const bool p2, const bool p3, const bool p4, char* computedvalue ) const;
			void PBD_DOOR_STATUS( const bool p1, const bool p2, const bool p3, const bool p4, char* computedvalue ) const;
			void MODE_SELECTION( void );
			void DISABLE_COMMANDS( void );
			void DISABLE_UNVERIFIED_COMMANDS( void );

		public:
			explicit SSB_PL_BAY_DOORS( SimpleGPCSystem* _gpc );
			~SSB_PL_BAY_DOORS( void );

			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;
			void OnPostStep( double simt, double simdt, double mjd ) override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;
	};
}

#endif// _dps_SSB_PL_BAY_DOORS_H_

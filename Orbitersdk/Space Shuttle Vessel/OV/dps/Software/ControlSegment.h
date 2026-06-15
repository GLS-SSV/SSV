/****************************************************************************
  This file is part of Space Shuttle Vessel

  Control Segment definition


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

#ifndef _CONTROL_SEGMENT_H_
#define _CONTROL_SEGMENT_H_


#include <vector>
#include "SimpleGPCSoftware.h"
#include "DIS_PLAY.h"
#include "DNX_BMS.h"


/*
The mode 0 and block 0 are respectively the init mode and init block. After they run, the index is incremented

The mode and block beyond the last (user-defined) mode and block are respectively the cleanup mode and cleanup block. After they run, ...?
*/

namespace dps
{
	class ControlSegment;

	class CS_Block
	{
		protected:
			SimpleGPCSystem* pGPC;
			ControlSegment* pCS;
			unsigned short DisplayNumber;
			bool init;

			unsigned short key;
			unsigned short item_no;
			double item_s;
			int item_i;

			virtual void Init( void );
			virtual void Input( void );
			virtual void CleanUp( void );

			void DISPLAY( unsigned int display_num );

			/**
			Is an integer single value giving the ID of the MCDS key passed to UI. KEY may be used in conjunction with other macros to determine the identity of a particular entry.
			*/
			unsigned short KEY( void ) const;

			/**
			Gives the ID for the ITEM key when data is entered with the ITEM number.
			*/
			unsigned short ITEM( void ) const;

			/**
			Gives the ID for the EXEC key as received from the MCDS keyboard.
			*/
			unsigned short EXEC( void ) const;

			/**
			Gives access to the integer single item number entered with an ITEM key entry.
			*/
			unsigned short ITEM_NO( void ) const;

			/**
			Gives access to the scalar value as a double precision data item entered with an ITEM keyboard entry and associated with the current item number.
			*/
			double ITEM_S( void ) const;

			/**
			Gives access to the integer value as a double precision data item entered with an ITEM keyboard entry and associated with the current item number.
			*/
			int ITEM_I( void ) const;

			/**
			Gives the integer single value of the current OPS within the Miscellaneous Application Control Table (MACT).
			*/
			unsigned short D_OPS_NUMBER( void ) const;

			/**
			Gives the integer single value of the current MODE within the MACT.
			*/
			unsigned short D_MODE_NUMBER( void ) const;

			/**
			Gives the integer single value of the current SPEC within the MACT.
			*/
			unsigned short D_SPEC_NUMBER( void ) const;

			/**
			Gives the integer single value of the current BLOCK within the MACT.
			*/
			unsigned short D_BLOCK_NUMBER( void ) const;

			/**
			Gives the integer single value of the OPS for which a current OPS is being cancelled. This is valid only in the clean up segment.
			*/
			unsigned short D_NEW_OPS_NUMBER( void ) const;

			/**
			Gives the integer single value of the new mode being requested by the MCDS input for which a current mode is being cancelled. This is valid only in the clean up segment.
			*/
			unsigned short D_NEW_MODE_NUMBER( void ) const;

			/**
			Gives the integer single value of the DEU from which a keyboard entry to the control segment has been made.
			*/
			unsigned short D_DEU_NUMBER( void ) const;

		public:
			CS_Block( SimpleGPCSystem* pGPC, ControlSegment* pCS, const unsigned short DisplayNumber );
			virtual ~CS_Block( void );

			void Run( void );
	};

	////////////////////////////////////////////////////////////////

	class CS_Mode
	{
		protected:
			SimpleGPCSystem* pGPC;
			ControlSegment* pCS;
			std::vector<CS_Block*> Blocks;
			unsigned int Advance_Event;

			virtual void Init( void );
			virtual void CleanUp( void );

			/**
			Gives the integer single value of the current OPS within the Miscellaneous Application Control Table (MACT).
			*/
			unsigned short D_OPS_NUMBER( void ) const;

			/**
			Gives the integer single value of the current MODE within the MACT.
			*/
			unsigned short D_MODE_NUMBER( void ) const;

			/**
			Gives the integer single value of the current SPEC within the MACT.
			*/
			unsigned short D_SPEC_NUMBER( void ) const;

			/**
			Gives the integer single value of the OPS for which a current OPS is being cancelled. This is valid only in the clean up segment.
			*/
			unsigned short D_NEW_OPS_NUMBER( void ) const;

			/**
			Gives the integer single value of the new mode being requested by the MCDS input for which a current mode is being cancelled. This is valid only in the clean up segment.
			*/
			unsigned short D_NEW_MODE_NUMBER( void ) const;

			/**
			Gives the integer single value of the DEU from which a keyboard entry to the control segment has been made.
			*/
			unsigned short D_DEU_NUMBER( void ) const;

		public:
			CS_Mode( SimpleGPCSystem* pGPC, ControlSegment* pCS, const unsigned int Advance_Event );

			void Run( void );
	};

	////////////////////////////////////////////////////////////////

	class ControlSegment : public SimpleGPCSoftware
	{
		protected:
			SimpleGPCSystem* pGPC;
			unsigned short DIS_MACT_INDEX;

			virtual void Init( void );
			virtual void CleanUp( void );
			virtual void Run( void ) = 0;

			/**
			Gives the integer single value of the current OPS within the Miscellaneous Application Control Table (MACT).
			*/
			unsigned short D_OPS_NUMBER( void ) const;

			/**
			Gives the integer single value of the current MODE within the MACT.
			*/
			unsigned short D_MODE_NUMBER( void ) const;

			/**
			Gives the integer single value of the current SPEC within the MACT.
			*/
			unsigned short D_SPEC_NUMBER( void ) const;

			/**
			Gives the integer single value of the OPS for which a current OPS is being cancelled. This is valid only in the clean up segment.
			*/
			unsigned short D_NEW_OPS_NUMBER( void ) const;

			/**
			Gives the integer single value of the new mode being requested by the MCDS input for which a current mode is being cancelled. This is valid only in the clean up segment.
			*/
			unsigned short D_NEW_MODE_NUMBER( void ) const;

			/**
			Gives the integer single value of the DEU from which a keyboard entry to the control segment has been made.
			*/
			unsigned short D_DEU_NUMBER( void ) const;

		public:
			ControlSegment( SimpleGPCSystem* pGPC, const std::string& _ident );
			virtual ~ControlSegment( void );

			unsigned short GetDIS_MACT_INDEX( void ) const;

			virtual void OnPreStep( double simt, double simdt, double mjd ) override;
			virtual bool OnParseLine( const char* keyword, const char* value ) override;
			virtual void OnSaveState( FILEHANDLE scn ) const override;
	};


	class ControlSegmentOPS : public ControlSegment
	{
		protected:
			std::vector<CS_Mode*> Modes;

			void Run( void );

		public:
			ControlSegmentOPS( SimpleGPCSystem* pGPC, const std::string& _ident );
			virtual ~ControlSegmentOPS( void );
	};

	class ControlSegmentSPEC : public ControlSegment
	{
		protected:
			std::vector<CS_Block*> Blocks;

			void Run( void );

		public:
			ControlSegmentSPEC( SimpleGPCSystem* pGPC, const std::string& _ident );
			virtual ~ControlSegmentSPEC( void );
	};

	}


#endif //_CONTROL_SEGMENT_H_

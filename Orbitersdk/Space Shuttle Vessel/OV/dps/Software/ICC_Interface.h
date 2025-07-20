/****************************************************************************
  This file is part of Space Shuttle Vessel

  ICC Interface definition


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
#ifndef _ICCIF_H_
#define _ICCIF_H_


namespace dps
{
	class SimpleGPCSystem;


	/**
	 * System Services \ User Interface \ Command Input Process
	 */
	class ICC_Interface
	{
		private:
			SimpleGPCSystem* pGPC;

			unsigned short DIN_BUF_POINTER;// Pointer
			unsigned short DINB_BITVAL;// Message_Header
			unsigned short DIN_MSG_SIZE;// Message_Size
			unsigned short DIN_MSG_INDEX;// Message_Index

			unsigned short DME_A;// ICC_Message_Pointer
			unsigned short DME_B;// Buffer_End
			unsigned short DME_I;// Buffer_Number
			unsigned short DME_FILX;// Filter_Mask
			unsigned short DME_GPCI;// Processing_GPC
			unsigned short DME_MSGHEAD;// ICC_Message_Header
			unsigned short DME_MSGS;// Message_Size
			unsigned short DME_RCODE;// Routing_Code
			unsigned short DME_PROCV;// Processing_Value
			unsigned short DME_IMTI;// IMT_Index
			unsigned short DME_MSGTABV;// ICC_Message_Table_Value
			unsigned short DME_NBR_UNIQ[4];// Number_Of_Uniques
			unsigned short DME_MSG_VAL[4][16];// One_Word_Message_Contents (HACK no idea of size)


			void Message_Processing( unsigned short* DIN_ARRAY );// (485.1)

			void Processing_Initialization( void );// (490.1)
			void Valid_Buffer_To_Process( void );// (490.2)
			void Valid_IMT( void );// (490.3)
			void Type_1( void );// (490.4)
			void Type_2( void );// (490.5)
			void Type_20p( void );// (490.6)
			void Routing_Code_Process( void );// (490.7)

		public:
			explicit ICC_Interface( SimpleGPCSystem* pGPC );
			virtual ~ICC_Interface( void );

			void DIM_ICC_COLLECTOR( unsigned short* DIN_ARRAY );// ICC_Message_Collector (480)
			void DME_ICC_ROUT( void );// ICC_Message_Router (490)
	};
}

#endif// _ICCIF_H_

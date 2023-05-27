/****************************************************************************
  This file is part of Space Shuttle Vessel

  User Interface Control definition


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
#ifndef _UICONTROL_H_
#define _UICONTROL_H_


namespace dps
{
	class SimpleGPCSystem;


	class UserInterfaceControl
	{
		private:
			SimpleGPCSystem* pGPC;

			void SetIllegalEntry( const unsigned short deu );

			void DM1_KEYBOARD( const unsigned char deu );// Keyboard data processor
			void DM1_KEYSTROKE_PROC( const unsigned char deu );
			//void DM2_APPLICATION( void );// Application request processor
			//void DM3_DISPLAY( void );// Page locator
			//void DM4_DEU_PROC( void );// DEU background update processor
			//void DM5_NEW_CSEG( void );// Control segment scheduler
			void DM6_OPS_PROC( const unsigned char deu );// OPS request processor
			//void DM7_REQ_MFTERM( void );// Request MF termination processor
			void DM8_SPEC_PROC( const unsigned char deu );// SPEC request processor
			void DM9_ITEM( const unsigned char deu );// Item processor
			//void DMN_NEW_LOAD( void );// Buffer addressability processor
			//void DMR_RESUME( void );// Resume DEU processor
			//void DMZ_LOG( void );// UI control supervisor log function
			//void DMC_CC_SPEC( void );// Cargo control SPEC processor
			//void DXR_DMM_ROLLIN( void );// MM rollin display processor
			//void DXX_CSEG_TERM( void );// Control segment termination
			void DIR_IORESET( void );// I/O reset processor


			bool IsValidMajorModeTransition_GNC( unsigned short newMajorMode ) const;
			bool IsValidMajorModeTransition_SM( unsigned short newMajorMode ) const;

			bool IsValidSPEC_GNC( unsigned short spec ) const;
			bool IsValidSPEC_SM( unsigned short spec ) const;

			bool IsValidDISP_GNC( unsigned short disp ) const;
			bool IsValidDISP_SM( unsigned short disp ) const;

			/**
			 * Returns true if the specified SPEC is valid in the current OPS/MM.
			 */
			bool IsValidSPEC( unsigned short spec ) const;

			/**
			 * Returns true if the specified DISP is valid in the current OPS/MM.
			 */
			bool IsValidDISP( unsigned short disp ) const;

			/**
			 * Returns true if transition to major mode passed is valid.
			 */
			bool IsValidMajorModeTransition( unsigned short newMajorMode ) const;

		public:
			explicit UserInterfaceControl( SimpleGPCSystem* pGPC );
			virtual ~UserInterfaceControl( void );

			void DMC_SUPER( void );// User interface control supervisor
	};
}

#endif// _UICONTROL_H_

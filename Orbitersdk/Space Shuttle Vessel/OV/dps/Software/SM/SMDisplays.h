/****************************************************************************
  This file is part of Space Shuttle Vessel

  Systems Management Displays definition


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
#ifndef _dps_SMDISP_H_
#define _dps_SMDISP_H_


#include "../GeneralDisplays.h"
#include <discsignals.h>


namespace dps
{
	class SMDisplays:public GeneralDisplays
	{
		private:
			void OnPaint_SMTABLEMAINT( CRT_Interface* crt ) const;
			void OnPaint_PCMMUPLCOMM( CRT_Interface* crt ) const;
			void OnPaint_SMGROUNDCHECKOUT( CRT_Interface* crt ) const;
			void OnPaint_ENVIRONMENT( CRT_Interface* crt ) const;
			void OnPaint_ELECTRIC( CRT_Interface* crt ) const;
			void OnPaint_CRYOSYSTEM( CRT_Interface* crt ) const;
			void OnPaint_FUELCELLS( CRT_Interface* crt ) const;
			void OnPaint_COMMUNICATIONS( CRT_Interface* crt ) const;
			void OnPaint_EVAMMUFSS( CRT_Interface* crt ) const;
			void OnPaint_SMSYSSUMM1( CRT_Interface* crt ) const;
			void OnPaint_SMSYSSUMM2( CRT_Interface* crt ) const;
			void OnPaint_MASSMEMORYRW( CRT_Interface* crt ) const;
			void OnPaint_APUHYD( CRT_Interface* crt ) const;
			void OnPaint_HYDTHERMAL( CRT_Interface* crt ) const;
			void OnPaint_APUENVIRONTHERM( CRT_Interface* crt ) const;
			void OnPaint_PRPLTTHERMAL( CRT_Interface* crt ) const;
			void OnPaint_PCSCONTROL( CRT_Interface* crt ) const;
			void OnPaint_PDRSCONTROL( CRT_Interface* crt ) const;
			void OnPaint_PDRSOVERRIDE( CRT_Interface* crt ) const;
			void OnPaint_PDRSFAULTS( CRT_Interface* crt ) const;
			void OnPaint_PLRETENTION( CRT_Interface* crt ) const;
			void OnPaint_SPDS( CRT_Interface* crt ) const;
			void OnPaint_DOCKINGSTATUS( CRT_Interface* crt ) const;
			void OnPaint_CARGOLOOP( CRT_Interface* crt ) const;
			void OnPaint_PDRSSTATUS( CRT_Interface* crt ) const;
			void OnPaint_EXTERNALAIRLOCK( CRT_Interface* crt ) const;
			void OnPaint_POWERTRANSFER( CRT_Interface* crt ) const;
			void OnPaint_ANTENNA( CRT_Interface* crt ) const;
			void OnPaint_PLBAYDOORS( CRT_Interface* crt ) const;

			void BackgroundData_SMTABLEMAINT( CRT_Interface* crt ) const;
			void BackgroundData_PCMMUPLCOMM( CRT_Interface* crt ) const;
			void BackgroundData_SMGROUNDCHECKOUT( CRT_Interface* crt ) const;
			void BackgroundData_ENVIRONMENT( CRT_Interface* crt ) const;
			void BackgroundData_ELECTRIC( CRT_Interface* crt ) const;
			void BackgroundData_CRYOSYSTEM( CRT_Interface* crt ) const;
			void BackgroundData_FUELCELLS( CRT_Interface* crt ) const;
			void BackgroundData_COMMUNICATIONS( CRT_Interface* crt ) const;
			void BackgroundData_EVAMMUFSS( CRT_Interface* crt ) const;
			void BackgroundData_SMSYSSUMM1( CRT_Interface* crt ) const;
			void BackgroundData_SMSYSSUMM2( CRT_Interface* crt ) const;
			void BackgroundData_MASSMEMORYRW( CRT_Interface* crt ) const;
			void BackgroundData_APUHYD( CRT_Interface* crt ) const;
			void BackgroundData_HYDTHERMAL( CRT_Interface* crt ) const;
			void BackgroundData_APUENVIRONTHERM( CRT_Interface* crt ) const;
			void BackgroundData_PRPLTTHERMAL( CRT_Interface* crt ) const;
			void BackgroundData_PCSCONTROL( CRT_Interface* crt ) const;
			void BackgroundData_PDRSCONTROL( CRT_Interface* crt ) const;
			void BackgroundData_PDRSOVERRIDE( CRT_Interface* crt ) const;
			void BackgroundData_PDRSFAULTS( CRT_Interface* crt ) const;
			void BackgroundData_PLRETENTION( CRT_Interface* crt ) const;
			void BackgroundData_SPDS( CRT_Interface* crt ) const;
			void BackgroundData_DOCKINGSTATUS( CRT_Interface* crt ) const;
			void BackgroundData_CARGOLOOP( CRT_Interface* crt ) const;
			void BackgroundData_PDRSSTATUS( CRT_Interface* crt ) const;
			void BackgroundData_EXTERNALAIRLOCK( CRT_Interface* crt ) const;
			void BackgroundData_POWERTRANSFER( CRT_Interface* crt ) const;
			void BackgroundData_ANTENNA( CRT_Interface* crt ) const;
			void BackgroundData_PLBAYDOORS( CRT_Interface* crt ) const;

		public:
			explicit SMDisplays( SimpleGPCSystem* _gpc );
			~SMDisplays( void );

			/**
			 * Draws display on MDU.
			 */
			void Paint( CRT_Interface* crt, unsigned short page ) const override;

			/**
			 * Draws display on MDU.
			 */
			void PaintBackground( CRT_Interface* crt, unsigned short page ) const override;
	};
}


#endif// _dps_SMDISP_H_

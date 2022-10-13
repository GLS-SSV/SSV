/****************************************************************************
  This file is part of Space Shuttle Vessel

  Space Shuttle Main Engine Subsystem Operating Program definition


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
/******* SSV File Modification Notice *******
Date         Developer
2020/05/08   GLS
2020/06/20   GLS
2021/05/26   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/03/29   GLS
2022/03/31   GLS
2022/04/26   GLS
2022/08/05   GLS
2022/08/15   GLS
2022/10/12   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Space Shuttle Main Engine Subsystem Operating Program definition



  Space Shuttle Ultra is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Ultra is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Ultra; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file Doc\Space Shuttle Ultra\GPL.txt for more details.

  **************************************************************************/
#ifndef _dps_SSME_SOP_H_
#define _dps_SSME_SOP_H_


#include "SimpleGPCSoftware.h"


namespace dps
{
	inline constexpr unsigned short MPL = 65;
	inline constexpr unsigned short FPL = 109;

	// commands
	inline constexpr unsigned short SVRC = 0x2000;
	inline constexpr unsigned short LOXD = 0xA400;
	inline constexpr unsigned short XPOW = 0xAC00;
	inline constexpr unsigned short STEN = 0xC000;
	inline constexpr unsigned short IGNT = 0xC400;
	inline constexpr unsigned short SDEN = 0xC800;
	inline constexpr unsigned short STDN = 0xCC00;
	inline constexpr unsigned short TMSQ = 0xD000;
	inline constexpr unsigned short THRT = 0xD400;
	inline constexpr unsigned short ENLS = 0xE000;
	inline constexpr unsigned short INLS = 0xE400;

	inline constexpr unsigned short DATA_FAIL = 4;// I-LOAD

	/**
	 * @brief	Implementation of the SSME SOP software that runs in the GPCs.
	 *
	 * This class recieves commands to the SSMEs, formats and outputs them to the EIUs. It also reads from
	 * the EIUs SSME data, which is processed.
	 */
	class SSME_SOP:public SimpleGPCSoftware
	{
		private:
			unsigned short Phase[3];
			unsigned short Mode[3];
			unsigned short SelfTestStatus[3];
			unsigned short CommandStatus[3];
			unsigned short ChannelStatus[3];

			// command flags
			bool StartEnableCommand;// V90X8361X
			bool EngineStartCommand[3];// V90X8358X, V90X8359X, V90X8360X
			bool ShutdownEnableCommand[3];// V90X8367X, V90X8368X, V90X8369X
			bool ShutdownCommand[3];// V90X8370X, V90X8371X, V90X8372X
			bool ThrottleCommand[3];
			bool OxidizerDumpStartCommand[3];
			bool DumpStopCommand[3];
			bool LimitInhibitCommand[3];
			bool LimitEnableCommand[3];
			bool DCUSwitchVDTCommand[3];

			unsigned short LastCommand[3];

			bool ShutdownEnableCommandIssued[3];// TODO have a StartEnableCommandIssued????

			unsigned short CommandedThrottle;

			// status flags
			bool PadDataPathFailure[3];// V95X1217X, V95X1218X, V95X1219X
			bool MajorComponentFailure[3];// V95X1230X, V95X1231X, V95X1232X
			bool ChannelFailure[3];// V95X1236X, V95X1237X, V95X1238X

			double last_priTREF[3];
			double last_secTREF[3];

			bool PrimaryDataFail[3];
			bool SecondaryDataFail[3];
			bool DCUProcess[3];

			unsigned short PrimaryFailCounter[3];
			unsigned short SecondaryFailCounter[3];
			unsigned short DataFailCounter[3];

			double CPRESS[3];

			/**
			 * Processes Primary Data, decoding the status of the SSME and it's controller.
			 */
			void ProcessPriData( int eng );
			/**
			 * Processes Secondary Data, decoding the status of the SSME and it's controller.
			 */
			void ProcessSecData( int eng );

		public:
			explicit SSME_SOP( SimpleGPCSystem* _gpc );
			~SSME_SOP( void );

			void OnPreStep( double simt, double simdt, double mjd ) override;// read data
			void OnPostStep( double simt, double simdt, double mjd ) override;// send commands

			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;

			void ReadILOADs( const std::map<std::string,std::string>& ILOADs ) override;

			/**
			 * Causes the Start Enable Command to be issued for all 3 SSMEs.
			 */
			void SetStartEnableCommandFlag( void );

			/**
			 * Causes the Engine Start Command to be issued for a SSME.
			 * @param[in]	eng	SSME number
			 */
			void SetEngineStartCommandFlag( int eng );

			/**
			 * Causes the Shutdown Enable Command to be issued for a SSME.
			 * @param[in]	eng	SSME number
			 */
			void SetShutdownEnableCommandFlag( int eng );

			void ResetShutdownEnableCommandFlag( int eng );

			/**
			 * Causes the Shutdown Command to be issued for a SSME.
			 * @param[in]	eng	SSME number
			 */
			void SetShutdownCommandFlag( int eng );

			void ResetShutdownCommandFlag( int eng );

			/**
			 * Causes a Throttle Command to be issued to all SSMEs.
			 * @param[in]	pct	new throttle setting in percent of RPL
			 * @return		true = valid value
			 */
			bool SetThrottlePercent( unsigned short pct );

			/**
			 * Causes the Limit Inhibit Command to be issued for a SSME.
			 * @param[in]	eng	SSME number
			 */
			void SetLimitInhibitCommandFlag( int eng );

			/**
			 * Causes the Limit Enable Command to be issued for a SSME.
			 * @param[in]	eng	SSME number
			 */
			void SetLimitEnableCommandFlag( int eng );

			/**
			 * Causes the Oxidizer Dump Command to be issued for a SSME.
			 * @param[in]	eng	SSME number
			 */
			void SetOxidizerDumpStartCommandFlag( int eng );

			/**
			 * Causes the Terminate Sequence Command to be issued for a SSME.
			 * @param[in]	eng	SSME number
			 */
			void SetDumpStopCommandFlag( int eng );

			/**
			 * Returns an indication of whether the Shutdown Enable Command has been issued for a SSME.
			 * @param[in]	eng	SSME number
			 * @return		true = command issued
			 */
			bool GetShutdownEnableCommandIssuedFlag( int eng ) const;

			/**
			 * Returns an indication of whether a Pad Data Path Failure has occurred for a SSME.
			 * @param[in]	eng	SSME number
			 * @return		true = Pad Data Path Failure
			 */
			bool GetPadDataPathFailureFlag( int eng ) const;

			/**
			 * Returns an indication of whether a MCF has been posted on a SSME.
			 * @param[in]	eng	SSME number
			 * @return		true = MCF
			 */
			bool GetMajorComponentFailureFlag( int eng ) const;

			/**
			 * Returns an indication of whether a command channel has failed on a SSME.
			 * @param[in]	eng	SSME number
			 * @return		true = channel failed
			 */
			bool GetChannelFailureFlag( int eng ) const;

			/**
			 * Gets the chamber pressure in percent of RPL of a SSME.
			 * @param[in]	eng	SSME number
			 * @return		Chamber pressure in percent of RPL
			 */
			unsigned short GetPercentChamberPressVal( int eng ) const;
	};
}


#endif// _dps_SSME_SOP_H_
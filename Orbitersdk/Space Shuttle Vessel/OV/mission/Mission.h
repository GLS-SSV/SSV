/****************************************************************************
  This file is part of Space Shuttle Vessel

  Mission file handling definition


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
2020/05/10   GLS
2020/05/14   GLS
2020/06/20   GLS
2020/06/21   GLS
2020/06/28   GLS
2020/07/03   GLS
2020/07/30   GLS
2020/08/22   GLS
2020/08/23   GLS
2020/09/20   GLS
2020/10/03   GLS
2020/10/06   GLS
2020/10/10   GLS
2021/06/13   GLS
2021/07/03   GLS
2021/08/10   GLS
2021/08/24   GLS
2021/11/13   GLS
2021/11/27   GLS
2021/12/05   GLS
2021/12/30   GLS
2022/01/10   GLS
2022/02/25   GLS
2022/05/01   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Mission file handling definition



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
#ifndef _MISSION_H_
#define _MISSION_H_

#include <orbitersdk.h>
#include <string>
#include <map>
#include <cJSON.h>


/**
 * Contains all class definitions related to Mission Data Files and
 * handling mission data in the simulation
 */
namespace mission
{
	struct Latches
	{
		unsigned short PL;
		unsigned short Latch;
	};

	struct ActivePayload
	{
		bool IsUsed;
		unsigned short PLID[12];// Port1, Port2, Port3, Port4, Stbd1, Stbd2, Stbd3, Stbd4, Keel1, Keel2, Keel3, Keel4
		bool IsAttachment[12];// Port1, Port2, Port3, Port4, Stbd1, Stbd2, Stbd3, Stbd4, Keel1, Keel2, Keel3, Keel4
		bool Reversed[8];// Port1, Port2, Port3, Port4, Stbd1, Stbd2, Stbd3, Stbd4
		struct Latches Latches[12];// Port1, Port2, Port3, Port4, Stbd1, Stbd2, Stbd3, Stbd4, Keel1, Keel2, Keel3, Keel4
		unsigned short FwdGuide[8];// Port1, Port2, Port3, Port4, Stbd1, Stbd2, Stbd3, Stbd4
		unsigned short AftGuide[8];// Port1, Port2, Port3, Port4, Stbd1, Stbd2, Stbd3, Stbd4
	};

	struct PassivePayload
	{
		bool IsUsed;
		unsigned short PLID[12];// Port1, Port2, Port3, Port4, Stbd1, Stbd2, Stbd3, Stbd4, Keel1, Keel2, Keel3, Keel4
		bool IsAttachment[12];// Port1, Port2, Port3, Port4, Stbd1, Stbd2, Stbd3, Stbd4, Keel1, Keel2, Keel3, Keel4
		bool Reversed[8];// Port1, Port2, Port3, Port4, Stbd1, Stbd2, Stbd3, Stbd4
	};

	struct BayBridgePayload
	{
		bool IsUsed;
		unsigned short bay;
		unsigned short bridge;
	};

	struct MissionPayloads
	{
		struct ActivePayload active[5];
		struct PassivePayload passive[5];
		struct BayBridgePayload baybridge[8];
	};

	struct MPM_Pedestal
	{
		bool IsUsed;
		std::string mesh;
		unsigned short MRL;// 0 = none; 1 = forward; 2 = mid; 3 = aft
	};

	struct PayloadMPM
	{
		unsigned short attachment;// 0 = shoulder; 1 = forward; 2 = mid; 3 = aft
		MPM_Pedestal Shoulder;
		MPM_Pedestal Forward;
		MPM_Pedestal Mid;
		MPM_Pedestal Aft;
	};

	enum LongeronSillHW
	{
		None = 0, RMS, PLMPM, SPDS
	};

	class Mission {
	protected:
		std::string strFileName;
		std::string strOrbiter;
		std::string strOrbiterTexName;
		std::string strLOMSPodTexName;
		std::string strROMSPodTexName;

		std::string strLandingSiteTable;

		std::map<std::string,std::string> ILOADlist;

		MissionPayloads payloads;

		LongeronSillHW PortLongeronSill;
		LongeronSillHW StbdLongeronSill;

		PayloadMPM Stbd_PayloadMPM;

		double fMECOAlt;
		double fMECOVel;
		double fMECOFPA;
		double fTargetInc;

		bool bHasExtALODSKit;
		bool bHasODS;
		bool bHasExtAL;
		bool bHasTAA;
		bool bAftTAA;

		bool bHasKUBand;
		bool bHasBulkheadFloodlights;
		bool bHasDragChute;
		bool bHasPLBLiner;
		bool bHasDFIWireTray;
		bool bHasVentDoors4and7;

		unsigned short PLBDHingeFairings;// 0 = original; 1 = full; 2 = final
		bool ChinPanel;

		unsigned short Crew;
		unsigned short Galley;
		unsigned short SleepStations;
		bool EjectionSeats;
		bool CrewEscapeHardware;
		bool MEDSFlightDeck;

		double OVmass;

		bool bUseSILTS;

		bool bUseASE_IUS;
		bool bASE_IUS_Aft_Location;

		bool bUseCISS;
		bool bCISS_GPrime;

		Latches LargeUpperStage_Latches[3];// port, stbd, keel

		int InternalPRSDTankSets;
		bool bHasEDOKit;
		unsigned int EDOPallet;// 0 = none, 1 = single (4 tanks), 2 = dual (8 tanks, OV-105 only)

		bool bHasOMSKit;

		/**
		 * Initializes parameters to default values
		 */
		void SetDefaultValues( void );

		void LoadActivePayload( ActivePayload& pl, cJSON* root );
		void LoadPassivePayload( PassivePayload& pl, cJSON* root );
		void LoadBayBridgePayload( BayBridgePayload& pl, cJSON* root );
		void LoadPayloadMPM( PayloadMPM& plmpm, cJSON* root );
	public:
		/**
		 * Loads data from specified file.
		 * If strMission is empty string, returns default values.
		 */
		explicit Mission(const std::string& strMission);
		virtual ~Mission();

		bool LoadMissionFile( const std::string& strMission );
		void LoadMissionV1( cJSON* root );

		/**
		 * @return target equ inclination at MECO in radians
		 */
		virtual double GetMECOInc( void ) const;
		virtual double GetMECOAlt( void ) const;
		virtual double GetMECOVel( void ) const;
		virtual double GetMECOFPA( void ) const;

		virtual const std::string& GetOrbiter( void ) const;
		virtual const std::string& GetMissionFileName( void ) const;
		/**
		 * @return Name of OV texture file specified in mission file
		 * Empty string if no file is specified
		 */
		virtual const std::string& GetOrbiterTextureName( void ) const;
		/**
		 * @return Name of LH OMS pod texture file specified in mission file
		 * Empty string if no file is specified
		 */
		virtual const std::string& GetLOMSPodTextureName( void ) const;
		/**
		 * @return Name of RH OMS pod texture file specified in mission file
		 * Empty string if no file is specified
		 */
		virtual const std::string& GetROMSPodTextureName( void ) const;

		virtual bool IsExternalAirlockAftPos( void ) const;

		virtual bool HasRMS( void ) const;
		virtual bool HasPLMPM( void ) const;
		bool HasExtALODSKit( void ) const;
		virtual bool HasODS( void ) const;
		virtual bool HasExtAL( void ) const;
		virtual bool HasTAA( void ) const;
		virtual bool AftTAA( void ) const;
		virtual bool HasBulkheadFloodlights( void ) const;
		virtual bool HasDragChute( void ) const;

		/**
		 * Returns true if Payload Bay Liner is installed.
		 */
		bool HasPLBLiner( void ) const;

		/**
		 * Returns true if DFI Wire Tray is installed.
		 */
		bool HasDFIWireTray( void ) const;

		/**
		 * Returns true if Vent Doors 4 and 7 are installed.
		 */
		bool HasVentDoors4and7( void ) const;

		/**
		 * returns mass of the defined Orbiter Vehicle.
		 * @return	mass of Orbiter Vehicle (kg)
		 */
		virtual double GetOrbiterMass( void ) const;
		/**
		 * Returns true if KU-band antenna is installed.
		 */
		virtual bool HasKUBand( void ) const;
		/**
		 * Returns true if SILTS pod is installed.
		 */
		virtual bool UseSILTS( void ) const;

		/**
		 * Returns true is the ASE for the IUS is used.
		 */
		bool UseASE_IUS( void ) const;

		/**
		 * Returns true if the ASE for the IUS is located in its aft position in the payload bay (ignored if the ASE is not used).
		 */
		bool IsASELocationAft( void ) const;

		/**
		 * Returns true if the CISS is used.
		 */
		virtual bool UseCISS( void ) const;

		/**
		 * Returns true if the CISS used is the G Prime version.
		 */
		virtual bool IsCISSGPrime( void ) const;

		/**
		 * Returns number of internal PRSD tank sets.
		 */
		virtual int GetInternalPRSDTankSets( void ) const;

		/**
		 * Returns true if PRSD EDO hardware is installed (OV-102 and OV-105 only).
		 */
		virtual bool HasEDOKit( void ) const;

		/**
		 * Returns type of EDO pallet installed: 0 = none, 1 = single (4 tanks), 2 = dual (8 tanks, OV-105 only).
		 */
		virtual unsigned short GetEDOPallet( void ) const;

		virtual bool HasOMSKit( void ) const;

		virtual const std::string& GetLandingSiteTable( void ) const;

		const std::map<std::string,std::string>& Mission::GetILOADs( void ) const;
		void ClearILOADs( void );

		const struct MissionPayloads& GetPayloads( void ) const;

		const struct PayloadMPM& GetPayloadMPM( bool port ) const;

		const struct Latches* GetLargeUpperStageLatches( void ) const;

		unsigned short GetPLBDHingeFairings( void ) const;

		bool GetChinPanel( void ) const;
	};

}

#endif// _MISSION_H_

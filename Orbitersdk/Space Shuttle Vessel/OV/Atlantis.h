/****************************************************************************
  This file is part of Space Shuttle Vessel

  Orbiter Vehicle vessel definition


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
2020/03/25   GLS
2020/03/26   GLS
2020/03/29   GLS
2020/04/01   GLS
2020/04/02   GLS
2020/04/07   GLS
2020/04/15   GLS
2020/04/28   GLS
2020/05/06   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/05/14   GLS
2020/05/23   GLS
2020/05/25   GLS
2020/05/29   GLS
2020/05/31   GLS
2020/06/12   GLS
2020/06/14   GLS
2020/06/20   GLS
2020/06/21   GLS
2020/06/23   GLS
2020/06/28   GLS
2020/07/08   GLS
2020/07/10   GLS
2020/07/11   GLS
2020/08/25   GLS
2020/08/30   GLS
2020/08/31   GLS
2020/09/04   GLS
2020/09/07   GLS
2020/09/15   GLS
2020/10/07   GLS
2020/10/11   GLS
2021/01/11   GLS
2021/02/15   GLS
2021/02/16   GLS
2021/03/18   GLS
2021/05/21   GLS
2021/05/30   GLS
2021/05/31   GLS
2021/06/01   GLS
2021/06/03   GLS
2021/06/06   GLS
2021/06/13   GLS
2021/06/18   GLS
2021/06/20   GLS
2021/06/23   GLS
2021/06/28   GLS
2021/07/01   GLS
2021/07/02   GLS
2021/07/03   GLS
2021/08/07   GLS
2021/08/13   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/12/27   GLS
2021/12/30   GLS
2022/01/10   GLS
2022/01/19   GLS
2022/02/07   GLS
2022/02/16   GLS
2022/02/17   GLS
2022/03/21   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/05   GLS
2022/04/27   GLS
2022/05/13   GLS
2022/06/24   GLS
2022/08/05   GLS
2022/10/06   GLS
2022/10/09   GLS
2022/10/21   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  STS Orbiter vessel class definition



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

//Original copyright notice of Atlantis example
// ==============================================================
//                 ORBITER MODULE: Atlantis
//                  Part of the ORBITER SDK
//          Copyright (C) 2001-2003 Martin Schweiger
//                   All rights reserved
//
// Atlantis.h
// Class interface of Atlantis (Space Shuttle) vessel class
// module and associated subclasses (SRB, tank)
// ==============================================================

#ifndef __ATLANTIS_H
#define __ATLANTIS_H

#include <Orbitersdk.h>
#include <vector>
#include <PanelGroup.h>
#include <discsignals.h>
#include <Sensor.h>
#include <EngConst.h>


typedef struct {
	HINSTANCE hDLL;
	HBITMAP deu_characters;
	HBITMAP deu_characters_overbright;
	HBITMAP deu_characters_fault;
	HDC DeuCharBitmapDC;
	HDC DeuCharOvrBrgtBitmapDC;
	HDC DeuCharFaultBitmapDC;
	SURFHANDLE deu_charactersSH;
	SURFHANDLE deu_characters_overbrightSH;
	SURFHANDLE deu_characters_faultSH;
} GDIParams;


typedef struct
{
	double Elevator;// [-33.0º, +18.0º]
	double Aileron;// [-33.0º, +18.0º]
	double BodyFlap;// [-11.7º, +22.55º]
	double Speedbrake;// [0º, 87.2º]
	double Rudder;// [-27.1º, +27.1º]
	double LandingGear;// [0º, 98.0º]
	bool SILTSPOD;
} AerosurfacePositions;


class AtlantisSubsystemDirector;
class MPM;
class RMS;
class Payload_MPM;
class ASE_IUS;
class CISS;
class DragChute;
class ActiveLatchGroup;
class PayloadBay;
class HUD;
class APU;
class T0UmbilicalReference;

namespace dps
{
	class SimpleShuttleBus;
	class SimpleMDM;
	class SSME_SOP;
	class MPS_ATVC_CMD_SOP;
	class RSLS;
	class MasterTimingUnit;
	class IDP;
	class SimpleGPCSystem;
}

namespace eva_docking
{
	class ExtAirlock;
}

namespace mps
{
	class EIU;
	class MPS;
	class HeSysEng;
	class HeSysPneu;
}

namespace mission
{
	class Mission;
}

namespace rcs
{
	class RCS;
	class RJD;
}

namespace vc
{
	class MDU;
	class _7SegDisp_RCSOMS_PRPLT_QTY;
}

namespace oms
{
	class OMS;
}

class ET;
class SRB;

class gcCore;


typedef enum {
	LEFT = 0,
	RIGHT
} SIDE;

class SSVOptions;

using namespace discsignals;
using discsignals::DiscreteBundleManager;

// ==========================================================
// Interface for derived vessel class: Atlantis
// ==========================================================

class Atlantis: public VESSEL4
{
	friend class vc::_7SegDisp_RCSOMS_PRPLT_QTY;
	friend class Keyboard;
	friend class CRT;
	friend class vc::MDU;
	friend class oms::OMS;
	friend class dps::IDP;

	private:
		SSVOptions* options;
		mission::Mission* pMission;
		T0UmbilicalReference* pT0UmbRef;
		gcCore* pD3D9;
		AtlantisSubsystemDirector* psubsystems;
		vc::PanelGroup<Atlantis>* pgForward;
		vc::PanelGroup<Atlantis>* pgLeft;
		vc::PanelGroup<Atlantis>* pgCenter;
		vc::PanelGroup<Atlantis>* pgRight;
		vc::PanelGroup<Atlantis>* pgOverhead;
		vc::PanelGroup<Atlantis>* pgOverheadAft;
		vc::PanelGroup<Atlantis>* pgAftPort;
		vc::PanelGroup<Atlantis>* pgAft;
		vc::PanelGroup<Atlantis>* pgAftStbd;


		/* **************************************************
		 * Subsystem short cuts
		 * **************************************************/
		dps::MasterTimingUnit* pMTU;
		dps::IDP* pIDP[4];
		mps::EIU* pEIU[3];
		dps::SSME_SOP* pSSME_SOP;
		dps::RSLS* pRSLS;
		dps::MPS_ATVC_CMD_SOP* pMPS_ATVC_CMD_SOP;
		mps::HeSysEng* pHeEng[3];
		mps::HeSysPneu* pHePneu;
		mps::MPS* pMPS;
		APU* pAPU[3];
		eva_docking::ExtAirlock* pExtAirlock;
		RMS* pRMS;
		Payload_MPM* pPLMPM;
		ASE_IUS* pASE_IUS;
		CISS* pCISS;
		PayloadBay* pPayloadBay;
		DragChute* pDragChute;
		HUD* pHUD[2];
		std::vector<ActiveLatchGroup*> pActiveLatches;
		rcs::RCS* pRCS;
		rcs::RJD* pRJD[8];

		dps::SimpleGPCSystem *pSimpleGPC;
		dps::SimpleShuttleBus *pSimpleBus;
		dps::SimpleMDM* pSimpleMDM_FF1;
		dps::SimpleMDM* pSimpleMDM_FF2;
		dps::SimpleMDM* pSimpleMDM_FF3;
		dps::SimpleMDM* pSimpleMDM_FF4;
		dps::SimpleMDM* pSimpleMDM_FA1;
		dps::SimpleMDM* pSimpleMDM_FA2;
		dps::SimpleMDM* pSimpleMDM_FA3;
		dps::SimpleMDM* pSimpleMDM_FA4;
		dps::SimpleMDM* pSimpleMDM_PF1;
		dps::SimpleMDM* pSimpleMDM_PF2;
		dps::SimpleMDM* pSimpleMDM_OF1;
		dps::SimpleMDM* pSimpleMDM_OF2;
		dps::SimpleMDM* pSimpleMDM_OF3;
		dps::SimpleMDM* pSimpleMDM_OF4;
		dps::SimpleMDM* pSimpleMDM_OA1;
		dps::SimpleMDM* pSimpleMDM_OA2;
		dps::SimpleMDM* pSimpleMDM_OA3;

		VECTOR3 orbiter_ofs;
		VISHANDLE vis;      // handle for visual - note: we assume that only one visual per object is created!
		MESHHANDLE hOrbiterMesh;
		MESHHANDLE hOrbiterVCExternalMesh;
		MESHHANDLE hOrbiterVCMesh;
		MESHHANDLE hMidDeckMesh;
		MESHHANDLE hVerticalTailMesh;
		MESHHANDLE hOMSKitMesh;
		MESHHANDLE hSSMEMesh[3];
		DEVMESHHANDLE hDevOrbiterMesh;
		DEVMESHHANDLE hDevOrbiterVCExternalMesh;
		DEVMESHHANDLE hDevVerticalTailMesh;

		SURFHANDLE hOVTexture;
		SURFHANDLE hLOMSTexture;
		SURFHANDLE hROMSTexture;
		SURFHANDLE hAftBulkheadTexture;

		//C-P attachments
		ATTACHMENTHANDLE ahHDP;
		ATTACHMENTHANDLE ahTow;
		//P-C attachments
		ATTACHMENTHANDLE ahET, ahLeftSRB, ahRightSRB;

		int mfdID;

		double slag1, slag2, slag3;
		PSTREAM_HANDLE pshSlag1[2], pshSlag2[2], pshSlag3[2];
		PSTREAM_HANDLE pshSRBFlame[2];
		PSTREAM_HANDLE pshSRBSmoke[2];

		bool bHasODS;
		bool bHasExtAL;
		bool bMidDeckVisible;

		/**
		 * all animations that need to be deleted in destructor
		 */
		std::vector<MGROUP_TRANSFORM*> vpAnimations;

		// *******************************************************************************
		// Animations
		// *******************************************************************************
		// SBTCs animations
		UINT anim_leftsbtc;
		UINT anim_leftsbtcto;
		UINT anim_rightsbtc;
		UINT anim_rightsbtcto;

		// OMS engine animations
		UINT anim_leftOMSyaw;
		UINT anim_leftOMSpitch;
		UINT anim_rightOMSyaw;
		UINT anim_rightOMSpitch;

		// SSME ANIMATIONS
		UINT anim_ssme_yaw[3];
		UINT anim_ssme_pitch[3];
		UINT anim_ssme_gox_pos[3];
		UINT anim_ssme_vent_pos[3];
		UINT anim_ssme2_roll;

		//-----------------------------------------------
		// engine lights
		//-----------------------------------------------
		LightEmitter* SRBLight[2];
		LightEmitter* SSMELight;

		PROPELLANT_HANDLE ph_mps, ph_srb; // handles for propellant resources
		PROPELLANT_HANDLE ph_loms;
		PROPELLANT_HANDLE ph_roms;
		PROPELLANT_HANDLE ph_koms;
		PROPELLANT_HANDLE ph_frcs;
		PROPELLANT_HANDLE ph_lrcs;
		PROPELLANT_HANDLE ph_rrcs;
		THRUSTER_HANDLE th_ssme[3];                // handles for SSME
		THRUSTER_HANDLE th_oms[2];               // handles for OMS engines
		THRUSTER_HANDLE th_srb[2];                 // handles for SRB engines
		THRUSTER_HANDLE th_rcs[44];

		bool bSSMEsDefined, bOMSDefined, bRCSDefined;

		/**
		 * Particle stream handle for SSME GH2 burn effect at ignition and shutdown.
		 */
		PSTREAM_HANDLE SSMEGH2burn[3];

		/**
		 * Propellant handle for MPS LOX manifold. Used for MPS dump.
		 */
		PROPELLANT_HANDLE phLOXdump;

		/**
		 * Propellant handle for MPS LH2 manifold. Used for MPS dump.
		 */
		PROPELLANT_HANDLE phLH2dump;
		/**
		 * Used for the preflight GOX venting of the SSMEs.
		 */
		THRUSTER_HANDLE th_ssme_gox[3];
		/**
		 * Thruster handles for the various MPS dumps/vents. List follows:
		 * 0 = SSME-1
		 * 1 = SSME-2
		 * 2 = SSME-3
		 * 3 = LH2 B/U
		 * 4 = LH2 F/D
		 * 5 = LOX F/D
		 * 6 = LH2 FDLN Relief
		 * 7 = LOX FDLN Relief
		 */
		THRUSTER_HANDLE thMPSDump[8];

		THGROUP_HANDLE thg_pitchup, thg_pitchdown, thg_yawleft, thg_yawright, thg_rollleft, thg_rollright;
		THGROUP_HANDLE thg_transfwd, thg_transaft, thg_transup, thg_transdown, thg_transright, thg_transleft;
		UINT ex_main[3];						   // main engine exhaust
		PARTICLESTREAMSPEC RCS_PSSpec;
		SURFHANDLE RCS_Exhaust_tex;
		AIRFOILHANDLE hStackAirfoil;
		AIRFOILHANDLE hOVAirfoilV;
		AIRFOILHANDLE hOVAirfoilH;

		// SSME directions
		VECTOR3 ssme_dir[3];

		// SSME GOX vent and LOX vent positions (referenced to the SSME mesh)
		VECTOR3 ssme_gox_pos[3];
		VECTOR3 ssme_vent_pos[3];

		/**
		 * Mass of LOX in MPS manifold.
		 */
		double LOXmass;

		/**
		 * Mass of LH2 in MPS manifold.
		 */
		double LH2mass;

		bool hasPORT_RMS;
		bool hasSTBD_MPM;

		bool ControlRMS;
		// controller inputs
		VECTOR3 THC_AltInput; // uses arrows, Ins and Del keys to provide translation inputs; axis correspond to RCS FWD SENSE
		bool RHC_TrimUp;
		bool RHC_TrimDown;
		bool RHC_TrimLeft;
		bool RHC_TrimRight;
		double RPTA_Input;

		bool SBTCTO_Input;
		double SBTC_Input;

		double LeftBrake_Input;
		double RightBrake_Input;

		// controller positions (+-1 = full deflection)
		double LeftRHC[3];// pitch, roll, yaw
		double RightRHC[3];// pitch, roll, yaw
		double AftRHC[3];// pitch, roll, yaw
		short LeftRHCTrim[2];// pitch, roll
		short RightRHCTrim[2];// pitch, roll

		short LeftTHC[3];// X, Y, Z
		short AftTHC[3];// X, Y, Z

		double RPTAs;// <0 = left, >0 = right (CDR and PLT are connected)

		double LeftSBTC;
		double RightSBTC;
		bool LeftSBTCTO;
		bool RightSBTCTO;

		double BrakeCDR[2];// left, right
		double BrakePLT[2];// left, right


		bool bSRMsmoke;

		VCHUDSPEC huds;
		double pl_mass;

		VECTOR3 currentCoG; // 0,0,0 corresponds to CoG at center of Orbiter mesh

		bool hasCISS;


		VECTOR3 SRBNullDirection[3];


		bool firstStep; //call functions in first timestep

		DiscreteBundleManager* bundleManager;

		vc::MDU* mdus[11];

		double fTimeCameraLabel;
		NOTEHANDLE nhCameraLabel;
		char pszCameraLabelBuffer[80];

		//sound
		int SoundID;

		bool bLastCamInternal;

		bool bPLBCamPanLeft_Man, bPLBCamPanRight_Man, bPLBCamTiltUp_Man, bPLBCamTiltDown_Man;

		// used to trigger RCS sounds
		int lastRMSSJCommand; // -1, 0 or 1

		// Pan/Tilt PLB cameras (RMS elbow cam in RMS class)
		// 0=A, 1=B, 2=C, 3=D
		DiscInPort PLBCamPanLeft[4], PLBCamPanRight[4], PLBCamTiltUp[4], PLBCamTiltDown[4];

		// "manual" tilt/pan commands from camera vc
		DiscOutPort PLBCamPanLeft_Man, PLBCamPanRight_Man, PLBCamTiltUp_Man, PLBCamTiltDown_Man;

		DiscOutPort RMSGrapple, RMSRelease; // used by RMS dialog
		DiscOutPort RMS_RHCInput[3], RMS_THCInput[3], RMSDrivePlus, RMSDriveMinus;
		DiscInPort RMSCoarseRateIn;
		DiscOutPort RMSCoarseRateOut;

		DiscOutPort SSMEPBAnalog[3]; // to allow MECO to be commanded from keyboard

		DiscOutPort LandingGearArm;// to allow landing gear to be armed (wired to PLT PBIs)
		DiscOutPort LandingGearDown;// to allow landing gear to be deployed (wired to PLT PBIs)

		/**
		 * LOX low level sensors.
		 */
		Sensor LO2LowLevelSensor[4];

		/* **************************************************************
		 * Mesh indices for use in objects
		 ****************************************************************/
		UINT mesh_orbiter;                         // index for orbiter mesh
		UINT mesh_vcexternal;                         // index for cockpit mesh for external view
		UINT mesh_vc;                              // index for virtual cockpit mesh
		UINT mesh_middeck;                         // index for mid deck mesh
		UINT mesh_verticaltail;
		UINT mesh_OMSKit;
		UINT mesh_ssme[3];

		// Actual Virtual Cockpit Mode
		int VCMode;
		int scnVCMode; // VC view loaded from scenario
		/**
		 * Structural configuration
		 * - 0 launch configuration
		 * - 1 SRB's engaged
		 * - 2 SRB's separated
		 * - 3 Tank separated/orbiter only
		 */
		int status;

		double simTtwang;// SSME ignition simT time for twang
		double met;

		double SRBpc;



		void DetachSRB(SIDE side, double thrust, double prop);

		void AddPrimaryRCSExhaust( THRUSTER_HANDLE thX );
		void AddVernierRCSExhaust( THRUSTER_HANDLE thX );
		//-------------------------------------------------
		void CreateSSMEs(const VECTOR3& ofs);
		void CreateMPSGOXVents(const VECTOR3& ref_pos);
		void CreateMPSDumpVents( const VECTOR3& ofs );
		void CreateOrbiterTanks();
		void DefineSSMEExhaust();
		//-----------------------------------
		void ShowMidDeck();
		void HideMidDeck();
		//-----------------------------------
		void CreateRCSEngines( const VECTOR3& ofs );

		/**
		 * Updates the positions of controllers (RHC, THC, RPTA, SBTC and brakes), based on user input.
		 */
		void UpdateControllers( double dt );

		/**
		 * Calculates direction in which SSMEs/SRBs must thrust to point through CoG
		 */
		void UpdateNullDirections();

		// handle landing gear deployment from keyboard and automatically based on altitude
		void ManLandingGearArm( void );
		void ManLandingGearDown( void );

		void RealizeSubsystemConnections();

		ET* GetTankInterface() const;
		SRB* GetSRBInterface(SIDE side) const;

		/**
		 * Updates shuttle CoG.
		 * Estimates center of gravity relative to center of Orbiter mesh, then calls ShiftCG to update CG.
		 */
		void UpdateMassAndCoG( bool bUpdateAttachedVessels = false );

		void Twang(double timeFromEngineStart) const;

		void CreateOMSEngines( const VECTOR3& ofs );

		void UpdateOrbiterTexture( const std::string& strTextureName );
		void UpdateLOMSPodTexture( const std::string& strTextureName );
		void UpdateROMSPodTexture( const std::string& strTextureName );
		void UpdateAftBulkheadTexture( const std::string& ov );

		void CreateLights( void );
		void CreateSubsystems( void );
		void CreatePanels( void );

		void DisplayCameraLabel(const char* pszLabel);

		void AddSRBExhaust( bool smoke );

		void SetLaunchConfiguration (void);
		void SetOrbiterConfiguration (void);
		void SetOrbiterTankConfiguration (void);
		void SetPostLaunchConfiguration( void );

		void ClearMeshes ();
		void DefineAnimations (void);
		void DefineAttachments (const VECTOR3& ofs0);


	public:
		AerosurfacePositions aerosurfaces;


		Atlantis( OBJHANDLE hVessel, int fmodel );
		~Atlantis();

		// Overloaded callback functions
		void clbkSetClassCaps( FILEHANDLE cfg ) override;
		void clbkSaveState( FILEHANDLE scn ) override;
		void clbkLoadStateEx( FILEHANDLE scn, void* status ) override;
		void clbkSetStateEx( const void* status ) override;
		void clbkPostCreation( void ) override;
		void clbkFocusChanged( bool getfocus, OBJHANDLE hNewVessel, OBJHANDLE hOldVessel ) override;
		void clbkPreStep( double simt, double simdt, double mjd ) override;
		void clbkPostStep( double simt, double simdt, double mjd ) override;
		bool clbkPlaybackEvent( double simt, double event_t, const char* event_type, const char* event ) override;
		void clbkVisualCreated( VISHANDLE vis, int refcount ) override;
		void clbkVisualDestroyed( VISHANDLE vis, int refcount ) override;
		void clbkAnimate( double simt ) override;
		int clbkConsumeDirectKey( char* kstate ) override;
		int clbkConsumeBufferedKey( DWORD key, bool down, char* kstate ) override;
		bool clbkLoadGenericCockpit( void ) override;
		bool clbkLoadVC( int id ) override;
		bool clbkVCMouseEvent( int id, int event, VECTOR3& p ) override;
		bool clbkVCRedrawEvent( int id, int event, SURFHANDLE surf ) override;
		bool clbkDrawHUD( int mode, const HUDPAINTSPEC* hps, oapi::Sketchpad* skp ) override;

		void AddOrbiterVisual();
		virtual DiscreteBundleManager* BundleManager() const;
		mission::Mission* GetMissionData() const;
		SSVOptions* GetOptions( void ) const;


		virtual short GetETPropellant() const;
		virtual double GetETPropellant_B( void ) const;
		virtual double GetETLOXUllagePressure( void ) const;
		virtual double GetETLH2UllagePressure( void ) const;
		virtual unsigned short GetGPCMET(unsigned short usGPCID, unsigned short &usDay, unsigned short &usHour, unsigned short& usMin, unsigned short &usSec);
		virtual double GetMET() const;
		virtual dps::IDP* GetIDP(unsigned short usIDPNumber) const;
		virtual vc::MDU* GetMDU(unsigned short usMDUID) const;
		virtual const VECTOR3& GetOrbiterCoGOffset( void ) const;
		virtual double GetSRBChamberPressure( void );
		virtual unsigned int GetGPCMajorMode() const;
		int GetSoundID() const;
		double GetPropellantLevel(PROPELLANT_HANDLE ph) const;
		virtual bool RegisterMDU(unsigned short usMDUID, vc::MDU* pMDU);
		virtual void GetRHCPosition( unsigned short ID, double& Pitch, double& Roll, double& Yaw, short& TrimPitch, short& TrimRoll ) const;
		virtual void GetTHCPosition( unsigned short ID, short& X, short& Y, short& Z ) const;
		virtual void GetRPTAPosition( double& pos ) const;
		virtual void GetSBTCPosition( unsigned short ID, double& pos, bool& TO ) const;
		virtual void GetBrakePosition( double& CDRLeft, double& CDRRight, double& PLTLeft, double& PLTRight ) const;

		/**
		 * @param usMPSNo numerical ID of the SSME
		 * @param fThrust0 Vacuum thrust
		 * @param fISP0 Vacuum ISP
		 * @param fISP1 Sealevel ISP
		 * @return false for failure, true for success
		 */
		bool SetSSMEParams(unsigned short usMPSNo, double fThrust0, double fISP0, double fISP1);

		/**
		 * Sets SSME thrust direction, vent position and direction, and animation.
		 * @param usMPSNo numerical ID of the SSME - 1
		 * @param degPitch pitch gimbal angle (degrees)
		 * @param degYaw yaw gimbal angle (degrees)
		 * @return false for failure, true for success
		 */
		bool SetSSMEGimbalAngles(unsigned usMPSNo, double degPitch, double degYaw);

		/**
		 *	@param fThrustLevel Thrust level (in %) from 0.0 to 109.0 (max power level)
		 */
		bool SetSSMEThrustLevel(unsigned short usMPSNo, double fThrustLevel);

		/**
		 * @param usMPSNo numerical ID of the SSME
		 * @return 0 < SSME PC < 109.0
		 */
		double GetSSMEThrustLevel( unsigned short usMPSNo );

		/**
		 * Sets SRB gimbal direction based on specified gimbal angles.
		 * Function limits angles to +/- 5 degrees
		 */
		void SetSRBGimbalAngles(SIDE SRB, double degPitch, double degYaw);

		/**
		 * Allows control of the following MPS vents:
		 * 0 = SSME-1
		 * 1 = SSME-2
		 * 2 = SSME-3
		 * 3 = LH2 B/U
		 * 4 = LH2 F/D
		 * 5 = LOX F/D
		 * 6 = LH2 FDLN Relief
		 * 7 = LOX FDLN Relief
		 * @param[in]	vent	identification of vent to control
		 * @param[in]	level	level of vent (between 0 and 1)
		 */
		void SetMPSDumpLevel( unsigned int vent, double level );

		/**
		 * Allows control of the SSME GH2 burning effect at ignition and shutdown.
		 * @param[in]	eng	number of SSME
		 * @param[in]	burn	controls if burn effect is on or off
		 */
		void SetSSMEGH2burn( int eng, bool burn );

		void SetSSMEMesh( unsigned short ID, MESHHANDLE hMesh );

		double CalcNetSSMEThrust() const;
		double GetSSMEISP() const;
		void CalcSSMEThrustAngles( unsigned int eng, double& degAngleP, double& degAngleY ) const;

		/**
		 * Calls VESSEL::AttachChild and adds mass of child to shuttle mass
		 * Should always be called instead of AttachChild.
		 */
		bool AttachChildAndUpdateMass(OBJHANDLE child, ATTACHMENTHANDLE attachment, ATTACHMENTHANDLE child_attachment);
		/**
		 * Calls VESSEL::DetachChild and subtracts mass of child from shuttle mass
		 * Should always be called instead of DetachChild.
		 */
		bool DetachChildAndUpdateMass(ATTACHMENTHANDLE attachment, double vel = 0.0);

		/**
		 * Wrapper for AddAnimationComponent
		 * MGROUP_TRANSFORM passed MUST be allocated with new and will be deleted by Atlantis destructor
		 */
		ANIMATIONCOMPONENT_HANDLE AddManagedAnimationComponent(UINT anim, double state0, double state1,
			MGROUP_TRANSFORM *trans, ANIMATIONCOMPONENT_HANDLE parent = NULL);

		void IgniteSRBs();

		void SeparateBoosters (double met);
		void SeparateTank (void);

		// Communication thru T0 umbilical
		virtual void SetGMTLO( double GMTLO );
		virtual void SetGMTLOSetCommandFlag( bool val );
		virtual void SetLPSCountdownHoldFlag( bool val );
		virtual void SetLPSGoForAutoSequenceStartFlag( bool val );
		virtual void SetLPSGoForEngineStartFlag( bool val );
		virtual void SetResumeCountCommandFlag( bool val );
		virtual bool GetRSCountdownHoldFlag( void ) const;
		virtual bool GetLaunchSequenceAbortFlag( void ) const;
		virtual void PSN4( void );
		virtual void SetSSMEActPos( int num, double Ppos, double Ypos );
		virtual unsigned int GetHoldFlags( void ) const;
		virtual double GetHydSysPress( int sys ) const;

		virtual bool HydraulicsOK( void ) const;

		virtual int GetHeTankPress( int sys ) const;
		virtual int GetHeRegPress( int sys ) const;
		virtual void HeFillTank( int sys, double mass );
		virtual PROPELLANT_HANDLE GetLH2Tank( void ) const;
		virtual PROPELLANT_HANDLE GetLOXTank( void ) const;
		virtual double GetLOXManifPress( void ) const;
		virtual double GetLH2ManifPress( void ) const;

		gcCore* D3D9( void ) const;
		UINT OVmesh( void ) const;
		dps::MasterTimingUnit* MTU( void ) const;
		virtual T0UmbilicalReference* T0UmbRef( void ) const;
		APU* GetAPU( int apu ) const;
		MPM* GetPortMPM( void ) const;
		MPM* GetStarboardMPM( void ) const;
		ATTACHMENTHANDLE GetHDP( void ) const;
		VISHANDLE Get_vis( void ) const;
		DEVMESHHANDLE GetOVDevMesh( void ) const;
		int Get_status( void ) const;
		int GetVCMode( void ) const;
		AtlantisSubsystemDirector* SubsystemDirector( void ) const;

		/**
		 * Bridge function between MPS and ET to "deliver" GO2 and GH2 for
		 * tank pressurization. Note that no actual mass is sent from the
		 * MPS to the ET, but the mass is directly decreased from the
		 * propellant in the ET.
		 * @param[in]	GOXmass	mass of gaseous oxygen (in kg)
		 * @param[in]	GH2mass mass of gaseous hydrogen (in kg)
		 */
		void ETPressurization( double GOXmass, double GH2mass );

		/**
		 * Function called by MPS to "flow" mass from the ET to the MPS manifold.
		 */
		void UpdateMPSManifold( void );

		/**
		 * @param engine 0 for Left, 1 for Right
		 * @param pitch angle in degrees (relative to null position)
		 * @param yaw angle in degrees (relative to null position)
		 */
		void GimbalOMS( unsigned int engine, double pitch, double yaw );

		/**
		 * Sets a thrust level for the selected OMS engine.
		 * @param id		0 for Left, 1 for Right
		 * @param level		OMS engine thrust level (0, 1)
		 */
		void SetOMSThrustLevel( unsigned short id, double level );

		/**
		 * Gets the thrust level for the selected OMS engine.
		 * @param id		OMS engine id
		 */
		double GetOMSThrustLevel( unsigned short id );

		/**
		 * Sets a thrust level for the selected RCS engine.
		 * @param id		RCS engine id
		 * @param level		RCS engine thrust level (0, 1)
		 */
		void SetRCSThrustLevel( unsigned short id, double level );

		/**
		 * Gets the thrust level for the selected RCS engine.
		 * @param id		RCS engine id
		 */
		double GetRCSThrustLevel( unsigned short id );

		/**
		 * Sets a propellant source for the selected OMS engine.
		 * @param id		OMS engine id
		 * @param source	OMS propellant source
		 */
		void SetOMSPropSource( unsigned short id, unsigned short source );

		/**
		 * Sets a propellant source for the selected RCS engine.
		 * @param id		RCS engine id
		 * @param source	RCS propellant source
		 */
		void SetRCSPropSource( unsigned short id, unsigned short source );

		void DefineTouchdownPoints( void );
};

VECTOR3 CalcOMSThrustDir(unsigned int side, double pitch, double yaw);

#endif // !__ATLANTIS_H

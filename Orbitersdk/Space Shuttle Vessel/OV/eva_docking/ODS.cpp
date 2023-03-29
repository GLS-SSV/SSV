/******* SSV File Modification Notice *******
Date         Developer
2020/04/07   GLS
2020/04/21   GLS
2020/05/10   GLS
2020/05/23   GLS
2020/05/24   GLS
2020/06/20   GLS
2020/06/23   GLS
2021/06/06   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/13   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/01/10   GLS
2022/01/15   GLS
2022/02/16   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/05/07   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/10/29   GLS
2023/01/14   GLS
2023/02/12   GLS
2023/03/26   GLS
********************************************/
#include "ODS.h"
#include "../Atlantis.h"
#include "../ExternalLight.h"
#include "../ParameterValues.h"
#include "../meshres_ODS.h"
#include <VesselAPI.h>
#include "../../CommonDefs.h"
#include <EngConst.h>


namespace eva_docking
{
	const static char* MESHNAME_ODS = "SSV\\OV\\ODS";

	const VECTOR3 ODS_MESH_OFFSET = _V( 0.0, -1.49644, 7.7544 );// [m]
	const VECTOR3 ODS_MESH_AFT_OFFSET = _V( 0.0, -1.49644, 5.65636 );// [m]

	// offset between ODS mesh position and docking port position
	const VECTOR3 ODS_DOCKPOS_OFFSET = _V( 0.0, 2.59334, 0.0 );// [m]

	constexpr double ODS_MASS = 925.0 * LBM2KG;// [kg] (according to a SSP PRCB presentation on the STS-125 pros/cons of Single Pad vs Dual Pad ops for LON)
	constexpr VECTOR3 ODS_CG = {0.0, 0.8429, 7.7544};// (approx) Xo+649.0 Yo+0.0 Zo+450.0
	constexpr VECTOR3 ODS_AFT_CG = {0.0, 0.8429, 5.65636};// approx) Xo+731.60 Yo+0.0 Zo+450.0


	// light positions (aft position)
	const VECTOR3 LIGHT_VESTIBULE_PORT_POS = _V( -0.18542, 0.632334, 5.419124 );// Xo+740.94, Yo-7.30, Zo+441.71
	const VECTOR3 LIGHT_VESTIBULE_STBD_POS = _V( 0.28956, 0.632334, 5.739164 );// Xo+728.34, Yo+11.40, Zo+441.71

	const VECTOR3 LIGHT_DIR = _V( 0.0, 1.0, 0.0 );

	constexpr double LIGHT_RANGE = 20.0;// [m]
	const double LIGHT_UMBRA_ANGLE = 40.0 * RAD;// [rad]
	const double LIGHT_PENUMBRA_ANGLE = LIGHT_UMBRA_ANGLE + (20.0 * RAD);// [rad]

	constexpr double LIGHT_ATT0 = 0.4;// [1]
	constexpr double LIGHT_ATT1 = 0.3;// [1]
	constexpr double LIGHT_ATT2 = 0.03;// [1]


	const VECTOR3 ODS_RING_TRANSLATION = _V(0.0, 0.45, 0.0);

	constexpr double ODS_ROD_REF_Y = 2.20083 + 0.3292;// top of actuator rods
	constexpr double ODS_ROD_ACT_REF_Y = 2.05743 + 0.3292;// bottom of actuators main bases


	const VECTOR3 ODS_ROD1L_REF = _V( -0.407493, ODS_ROD_REF_Y, -0.052338 + 0.42789 );
	const VECTOR3 ODS_ROD1L_DIR = _V( 0.939693, 0.0, -0.342020 );
	const VECTOR3 ODS_ROD1L_ACT_REF = _V( -0.353414, ODS_ROD_ACT_REF_Y, 0.097919 + 0.42789 );
	const VECTOR3 ODS_ROD1L_ACT_DIR = _V( 0.939693, 0.0, -0.342020 );

	const VECTOR3 ODS_ROD1R_REF = _V( -0.527078, ODS_ROD_REF_Y, -0.259465 + 0.42789 );
	const VECTOR3 ODS_ROD1R_DIR = _V( -0.766044, 0.0, 0.6427878 );
	const VECTOR3 ODS_ROD1R_ACT_REF = _V( -0.632934, ODS_ROD_ACT_REF_Y, -0.386227 + 0.42789 );
	const VECTOR3 ODS_ROD1R_ACT_DIR = _V( -0.766044, 0.0, 0.6427878 );


	const VECTOR3 ODS_ROD2L_REF = _V( 0.52694, ODS_ROD_REF_Y, -0.259466 + 0.42789 );
	const VECTOR3 ODS_ROD2L_DIR = _V( -0.766044, 0.0, -0.6427878 );
	const VECTOR3 ODS_ROD2L_ACT_REF = _V( 0.632797, ODS_ROD_ACT_REF_Y, -0.386227 + 0.42789 );
	const VECTOR3 ODS_ROD2L_ACT_DIR = _V( -0.766044, 0.0, -0.6427878 );

	const VECTOR3 ODS_ROD2R_REF = _V( 0.407355, ODS_ROD_REF_Y, -0.052339 + 0.42789 );
	const VECTOR3 ODS_ROD2R_DIR = _V( 0.939693, 0.0, 0.342020 );
	const VECTOR3 ODS_ROD2R_ACT_REF = _V( 0.353276, ODS_ROD_ACT_REF_Y, 0.097918 + 0.42789 );
	const VECTOR3 ODS_ROD2R_ACT_DIR = _V( 0.939693, 0.0, 0.342020 );


	const VECTOR3 ODS_ROD3L_REF = _V( -0.119653, ODS_ROD_REF_Y, -0.965139 + 0.42789 );
	const VECTOR3 ODS_ROD3L_DIR = _V( -0.173648, 0.0, 0.984808 );
	const VECTOR3 ODS_ROD3L_ACT_REF = _V( -0.279591, ODS_ROD_ACT_REF_Y, -0.994763 + 0.42789 );
	const VECTOR3 ODS_ROD3L_ACT_DIR = _V( -0.173648, 0.0, 0.984808 );

	const VECTOR3 ODS_ROD3R_REF = _V( 0.119516, ODS_ROD_REF_Y, -0.965139 + 0.42789 );
	const VECTOR3 ODS_ROD3R_DIR = _V( -0.173648, 0.0, -0.984808 );
	const VECTOR3 ODS_ROD3R_ACT_REF = _V( 0.279452, ODS_ROD_ACT_REF_Y, -0.994763 + 0.42789 );
	const VECTOR3 ODS_ROD3R_ACT_DIR = _V( -0.173648, 0.0, -0.984808 );

	const VECTOR3 ODS_ROD_DISPLACEMENT = ODS_ROD3L_REF - ODS_ROD3L_ACT_REF;
	const double ODS_ROD_DISPLACEMENT_LEN = length(ODS_ROD_DISPLACEMENT);

	const double ODS_ROD_NULLANGLE = atan2(ODS_ROD_DISPLACEMENT.y, fabs(ODS_ROD_DISPLACEMENT.x));
	const float ODS_ROD_ROTATION = static_cast<float>(30.0f * RAD);

	const float ODS_RODDRIVE_ROTATION = static_cast<float>(400.0 * PI);// 20 rotations per meter


	ODS::ODS( AtlantisSubsystemDirector* _director, bool aftlocation ) : ExtAirlock( _director, "ODS", aftlocation, true ),
		bFirstStep(true), bTargetInCone(false),
		bTargetCaptured(false), APASdevices_populated(false), extend_goal(RETRACT_TO_FINAL),
		anim_ring(-1), anim_rods(-1),
		bPowerRelay(false), bAPDSCircuitProtectionOff(false), bFixersOn(true),
		bLatchesOpen(false), bLatchesClosed(true),
		bHooks1Open(true), bHooks1Closed(false),
		bHooks2Open(true), bHooks2Closed(false)
	{
		RingState.Set(AnimState::STOPPED, 0.0);
		target_pos = _V(0.0, 2000.0, 0.0);

		mesh_ods = MESH_UNDEFINED;
		hODSMesh = oapiLoadMeshGlobal( MESHNAME_ODS );
		oapiWriteLog( "(SSV_OV) [INFO] ODS mesh loaded" );

		ahDockAux = NULL;

		SetDockParams();

		// vestibule lights
		vestibule_lights[0] = new ExternalLight( STS(), LIGHT_VESTIBULE_PORT_POS + (aft ? _V( 0.0, 0.0, 0.0) : _V( 0.0, 0.0, ODS_MESH_OFFSET.z - ODS_MESH_AFT_OFFSET.z )), LIGHT_DIR, 0.0f, 0.0f, LIGHT_RANGE, LIGHT_ATT0, LIGHT_ATT1, LIGHT_ATT2, LIGHT_UMBRA_ANGLE, LIGHT_PENUMBRA_ANGLE, true );
		vestibule_lights[1] = new ExternalLight( STS(), LIGHT_VESTIBULE_STBD_POS + (aft ? _V( 0.0, 0.0, 0.0) : _V( 0.0, 0.0, ODS_MESH_OFFSET.z - ODS_MESH_AFT_OFFSET.z )), LIGHT_DIR, 0.0f, 0.0f, LIGHT_RANGE, LIGHT_ATT0, LIGHT_ATT1, LIGHT_ATT2, LIGHT_UMBRA_ANGLE, LIGHT_PENUMBRA_ANGLE, true );
	}

	ODS::~ODS()
	{
		delete vestibule_lights[0];
		delete vestibule_lights[1];
		return;
	}

	void ODS::PopulateAPASdevices( void )
	{
		APASdevices.clear();

		OBJHANDLE pOH;
		VESSEL* pV;
		ATTACHMENTHANDLE pAH;
		for (DWORD i = oapiGetVesselCount(); i > 0; i--)
		{
			pOH = oapiGetVesselByIndex( i - 1 );
			if (pOH != STS()->GetHandle())
			{
				pV = oapiGetVesselInterface( pOH );
				for (DWORD j = pV->AttachmentCount( true ); j > 0; j--)
				{
					pAH = pV->GetAttachmentHandle( true, j - 1 );

					if (!_strnicmp( pV->GetAttachmentId( pAH ), "APAS", 4 ))
					{
						APASdevices.push_back( make_pair( pOH, pAH ) );

						// log output
						oapiWriteLogV( "(SSV_OV) [DEBUG] ODS APAS search TGT:%s ID:%d", pV->GetName(), j );
					}
				}
			}
		}

		APASdevices_populated = true;
		return;
	}

	bool ODS::FindClosestAPAS( void )
	{
		bool ret = false;
		OBJHANDLE pOH;
		ATTACHMENTHANDLE pAH;
		VECTOR3 gpos;
		VECTOR3 tgt_pos;
		VECTOR3 tgtAPAS_pos;
		VECTOR3 tgtAPAS_dir;
		VECTOR3 tgtAPAS_rot;
		VECTOR3 tgt_pos_APAS;
		VECTOR3 rel_vel;

		target_pos = _V( 999, 999, 999 );// "reset" tgt vessel

		for (unsigned int i = APASdevices.size(); i > 0; i--)
		{
			pOH = APASdevices[i - 1].first;

			// calculate CG/CG distance
			oapiGetGlobalPos( pOH, &gpos );
			STS()->Global2Local( gpos, tgt_pos );

			// check if cg/cg distance is under 200m (protect for large vessels)
			if (length( tgt_pos ) < 200)
			{
				// calculate APAS/APAS distance
				pAH = APASdevices[i - 1].second;

				VESSEL* pV = oapiGetVesselInterface( pOH );

				pV->GetAttachmentParams( pAH, tgtAPAS_pos, tgtAPAS_dir, tgtAPAS_rot );
				pV->Local2Global( tgtAPAS_pos, gpos );
				STS()->Global2Local( gpos, tgt_pos_APAS );

				// correct for our APAS position and c.g.
				tgt_pos_APAS -= odsAttachVec[0] + STS()->GetOrbiterCoGOffset();

				// check if APAS/APAS distance under 5m
				if (length( tgt_pos_APAS ) < 5)
				{
					if (length( tgt_pos_APAS ) < length( target_pos ))
					{
						ahTarget = pAH;
						ohTarget = pOH;
						target_pos = tgt_pos_APAS;

						pV->Local2Global( tgtAPAS_pos + tgtAPAS_dir, gpos );
						STS()->Global2Local( gpos, target_dir );
						target_dir -= tgt_pos_APAS + odsAttachVec[0] + STS()->GetOrbiterCoGOffset();
						target_dir = -target_dir;// correct direction so when lined up the angle is 0º instead of 180º

						pV->Local2Global( tgtAPAS_pos + tgtAPAS_rot, gpos );
						STS()->Global2Local( gpos, target_rot );
						target_rot -= tgt_pos_APAS + odsAttachVec[0] + STS()->GetOrbiterCoGOffset();

						STS()->GetRelativeVel( pOH, rel_vel );
						target_vel.x = dotp( rel_vel, eX );
						target_vel.y = dotp( rel_vel, eY );
						target_vel.z = dotp( rel_vel, eZ );

						ret = true;
					}
				}
			}
		}
		return ret;
	}

	double ODS::GetSubsystemMass( void ) const
	{
		return EXTAL_MASS + ODS_MASS;
	}

	bool ODS::GetSubsystemCoG( VECTOR3& CoG ) const
	{
		VECTOR3 cgODS = aft ? ODS_AFT_CG : ODS_CG;
		VECTOR3 cgAL = aft ? EXTAL_AFT_CG : EXTAL_CG;
		CoG = ((cgAL * EXTAL_MASS) + (cgODS * ODS_MASS)) / (EXTAL_MASS + ODS_MASS);
		return true;
	}

	void ODS::CalculateRodAnimation()
	{
		double ringPos = RingState.pos * ODS_RING_TRANSLATION.y;

		double angle = atan2(ringPos + ODS_ROD_DISPLACEMENT.y, fabs(ODS_ROD_DISPLACEMENT.x));

		double pos = min(max((angle - ODS_ROD_NULLANGLE) / ODS_ROD_ROTATION, 0.0), 1.0);

		/*sprintf_s(oapiDebugString(), 256, "ODS ROD ANIMATION: %.1f cm ==> %5.2f°/%5.2f° ==> %5.3f pos",
			ringPos * 100.0, angle * DEG, ODS_ROD_NULLANGLE * DEG, pos);*/

		STS()->SetAnimation(anim_rods, pos);

	}

	void ODS::OnPostStep(double simt, double simdt, double mjd)
	{
		ExtAirlock::OnPostStep( simt, simdt, mjd );

		/*if (bFirstStep)
		{
			UpdateODSAttachment();
			bFirstStep = false;
		}*/
		RunLights( simdt );
		return;
	}

	void ODS::OnPreStep(double simt, double simdt, double mjd)
	{
		ExtAirlock::OnPreStep( simt, simdt, mjd );

		//if (!APASdevices_populated) PopulateAPASdevices();

		//STS()->GlobalRot(_V(1,0,0),eX);
		//STS()->GlobalRot(_V(0,1,0),eY);
		//STS()->GlobalRot(_V(0,0,1),eZ);
		//
		//if (bLatchesClosed && !bTargetCaptured)// search target to attach
		//{
		//	if (FindClosestAPAS())
		//	{
		//		VESSEL* pV = oapiGetVesselInterface( ohTarget );
		//		int iD = pV->GetAttachmentIndex( ahTarget );

		//		if ((target_pos.x < 0.1) &&(target_pos.y < 0.1) && (target_pos.z < 0.1) &&
		//			(acos( dotp( target_dir, odsAttachVec[1] - odsAttachVec[0] ) ) < (5 * RAD)) && (acos( dotp( target_rot, odsAttachVec[2] - odsAttachVec[0] ) ) < (5 * RAD)))
		//		{
		//			if (STS()->AttachChild( ohTarget, ahDockAux, ahTarget )) bTargetCaptured = true;
		//		}

		//		sprintf_s( oapiDebugString(), 256, "ODS: LOCK %s:%d | %5.4f %5.4f %5.4f | %5.4f %5.4f %5.4f | %.3f %.3f",
		//			pV->GetName(), iD, target_pos.x, target_pos.y, target_pos.z,
		//			target_vel.x, target_vel.y, target_vel.z,
		//			acos( dotp( target_dir, odsAttachVec[1] - odsAttachVec[0] ) ) * DEG, acos( dotp( target_rot, odsAttachVec[2] - odsAttachVec[0] ) ) * DEG );
		//		/*sprintf_s( oapiDebugString(), 256, "ODS: LOCK %s:%d | %5.4f\" %5.4f' %5.4f\" | %5.4f %5.4f %5.4f",
		//			pV->GetName(), iD, target_pos.x / INCH, target_pos.y / MPS2FPS, target_pos.z / INCH,
		//			target_vel.x / MPS2FPS, target_vel.y / MPS2FPS, target_vel.z / MPS2FPS);*/
		//	}
		//	else
		//	{
		//		sprintf_s( oapiDebugString(), 256, "ODS: APAS PORTS:%d", APASdevices.size() );
		//	}

		//	//If target in range:
		//	//Calculate contacts and trigger initial contact signal.
		//	//If all latches matching and overcoming resistence, capture.

		//	//if captured
		//	//simulate oscillations of structure
		//}

		bool CNTL_PNL = (dscu_ControlPanelPowerA.IsSet() && dscu_ControlPanelPowerB.IsSet()) || (dscu_ControlPanelPowerB.IsSet() && dscu_ControlPanelPowerC.IsSet()) || (dscu_ControlPanelPowerC.IsSet() && dscu_ControlPanelPowerA.IsSet());

		if ((dscu_APDSPowerA.IsSet() && dscu_APDSPowerB.IsSet()) || (dscu_APDSPowerB.IsSet() && dscu_APDSPowerC.IsSet()) || (dscu_APDSPowerC.IsSet() && dscu_APDSPowerA.IsSet()))
		{
			if (dscu_PowerOn.IsSet() && CNTL_PNL)
			{
				bPowerRelay = true;
				bAPDSCircuitProtectionOff = false;
			}

			if (dscu_PowerOff.IsSet() && CNTL_PNL) bPowerRelay = false;
		}
		else
		{
			bPowerRelay = false;
		}


		if (HasDSCUPower())
		{
			dscu_PowerOnLight.SetLine( (int)CNTL_PNL * 5.0f );
			dscu_RingAlignedLight.SetLine( (int)CNTL_PNL * 5.0f );

			if(dscu_APDSCircProtectionOff.IsSet() && CNTL_PNL) {
				bAPDSCircuitProtectionOff = true;
			}

			if(dscu_FixerOff && CNTL_PNL) {
				bFixersOn = false;
			}

			if(bAPDSCircuitProtectionOff) {
				dscu_APDSCircProtectLight.SetLine( (int)CNTL_PNL * 5.0f );
			} else {
				dscu_APDSCircProtectLight.ResetLine();
			}

			if(!bFixersOn) {
				dscu_FixersOffLight.SetLine( (int)CNTL_PNL * 5.0f );
			} else {
				dscu_FixersOffLight.ResetLine();
			}

			if(dscu_RingOut.IsSet() && CNTL_PNL && bAPDSCircuitProtectionOff) {
				RingState.action = AnimState::OPENING;
				extend_goal = EXTEND_TO_INITIAL;
				if(RingState.pos >= 0.7229167) {
					extend_goal = EXTEND_TO_FINAL;
				}
				bFixersOn = true;
			}


			if(dscu_RingIn.IsSet() && CNTL_PNL && bAPDSCircuitProtectionOff) {
				RingState.action = AnimState::CLOSING;
				extend_goal = RETRACT_TO_FINAL;
				bFixersOn = true;
			}


			if(RingState.Moving() && bPowerRelay) {
				RingState.Move(0.0039815 * simdt);

				if(RingState.pos >= 0.7361111 &&
					extend_goal == EXTEND_TO_INITIAL) {
					RingState.action = AnimState::STOPPED;
				}

				if(RingState.pos >= 1.0 &&
					extend_goal == EXTEND_TO_FINAL) {
					RingState.action = AnimState::STOPPED;
				}

				STS()->SetAnimation(anim_ring, RingState.pos);
				UpdateODSAttachment();

				CalculateRodAnimation();
			}

			if(RingState.pos < 0.0631944) {
				dscu_RingFinalLight.SetLine( (int)CNTL_PNL * 5.0f );
			} else {
				dscu_RingFinalLight.ResetLine();
			}

			if((RingState.pos >= 0.7229167&& RingState.pos < 0.7493056)) {
				dscu_RingInitialLight.SetLine( (int)CNTL_PNL * 5.0f );
			} else {
				dscu_RingInitialLight.ResetLine();
			}

			if(RingState.pos >= 0.9868056 ) {
				dscu_RingForwardLight.SetLine( (int)CNTL_PNL * 5.0f );
			} else {
				dscu_RingForwardLight.ResetLine();
			}

			if(bLatchesClosed) {
				dscu_LatchesClosedLight.SetLine( (int)CNTL_PNL * 5.0f );
			} else {
				dscu_LatchesClosedLight.ResetLine();
			}

			if(bLatchesOpen) {
				dscu_LatchesOpenLight.SetLine( (int)CNTL_PNL * 5.0f );
			} else {
				dscu_LatchesOpenLight.ResetLine();
			}

			if(bHooks1Open) {
				dscu_Hooks1OpenLight.SetLine( (int)CNTL_PNL * 5.0f );
			} else {
				dscu_Hooks1OpenLight.ResetLine();
			}

			if(bHooks2Open) {
				dscu_Hooks2OpenLight.SetLine( (int)CNTL_PNL * 5.0f );
			} else {
				dscu_Hooks2OpenLight.ResetLine();
			}

			if(bHooks1Closed) {
				dscu_Hooks1ClosedLight.SetLine( (int)CNTL_PNL * 5.0f );
			} else {
				dscu_Hooks1ClosedLight.ResetLine();
			}

			if(bHooks2Closed) {
				dscu_Hooks2ClosedLight.SetLine( (int)CNTL_PNL * 5.0f );
			} else {
				dscu_Hooks2ClosedLight.ResetLine();
			}

			if(bTargetCaptured) dscu_CaptureLight.SetLine( (int)CNTL_PNL * 5.0f );
			else dscu_CaptureLight.ResetLine();

		} else {
			dscu_PowerOnLight.ResetLine();
			dscu_APDSCircProtectLight.ResetLine();
			dscu_RingAlignedLight.ResetLine();
			dscu_FixersOffLight.ResetLine();
			dscu_RingInitialLight.ResetLine();
			dscu_Hooks1OpenLight.ResetLine();
			dscu_Hooks2OpenLight.ResetLine();
			dscu_LatchesClosedLight.ResetLine();
			dscu_UndockCompleteLight.ResetLine();

			dscu_InitialContactLight.ResetLine();
			dscu_CaptureLight.ResetLine();
			dscu_RingForwardLight.ResetLine();
			dscu_ReadyToHookLight.ResetLine();
			dscu_InterfSealedLight.ResetLine();
			dscu_Hooks1ClosedLight.ResetLine();
			dscu_Hooks2ClosedLight.ResetLine();
			dscu_LatchesOpenLight.ResetLine();
			dscu_RingFinalLight.ResetLine();
		}

		dscu_ADSLight.SetLine( (int)dscu_APDSPowerA.IsSet() * 5.0f );
		dscu_BDSLight.SetLine( (int)dscu_APDSPowerB.IsSet() * 5.0f );
		dscu_CDSLight.SetLine( (int)dscu_APDSPowerC.IsSet() * 5.0f );
		dscu_APLight.SetLine( (int)dscu_PyrosAp.IsSet() * 5.0f );
		dscu_BPLight.SetLine( (int)dscu_PyrosBp.IsSet() * 5.0f );
		dscu_CPLight.SetLine( (int)dscu_PyrosCp.IsSet() * 5.0f );
		return;
	}

	void ODS::Realize( void )
	{
		ExtAirlock::Realize();

		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "PANELA8A3_TO_DSCU_A", 16 );
		dscu_PowerOn.Connect( pBundle, 0 );
		dscu_PowerOff.Connect( pBundle, 1 );
		dscu_RingOut.Connect( pBundle, 2 );
		dscu_RingIn.Connect( pBundle, 3 );
		dscu_APDSCircProtectionOff.Connect( pBundle, 4 );
		dscu_CloseHooks.Connect( pBundle, 5 );
		dscu_CloseLatches.Connect( pBundle, 6 );
		dscu_FixerOff.Connect( pBundle, 7 );
		dscu_PyroCircProtOff.Connect( pBundle, 8 );
		dscu_PyroCircProtOn.Connect( pBundle, 9 );
		dscu_ActHooksFiring.Connect( pBundle, 10 );
		dscu_PasHooksFiring.Connect( pBundle, 11 );
		dscu_OpenHooks.Connect( pBundle, 12 );
		dscu_OpenLatches.Connect( pBundle, 13 );
		dscu_Undocking.Connect( pBundle, 14 );

		pBundle = BundleManager()->CreateBundle( "PANELA8A3_TO_DSCU_B", 16 );
		dscu_ControlPanelPowerA.Connect( pBundle, 0 );
		dscu_ControlPanelPowerB.Connect( pBundle, 1 );
		dscu_ControlPanelPowerC.Connect( pBundle, 2 );
		dscu_HeatersDCUPowerH1.Connect( pBundle, 3 );
		dscu_HeatersDCUPowerH2DCU.Connect( pBundle, 4 );
		dscu_HeatersDCUPowerH3DCU.Connect( pBundle, 5 );
		dscu_APDSPowerA.Connect( pBundle, 6 );
		dscu_APDSPowerB.Connect( pBundle, 7 );
		dscu_APDSPowerC.Connect( pBundle, 8 );
		dscu_PyrosAp.Connect( pBundle, 9 );
		dscu_PyrosBp.Connect( pBundle, 10 );
		dscu_PyrosCp.Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle("DSCU_TO_PANELA8A3_A", 16);
		dscu_PowerOnLight.Connect( pBundle, 0 );
		dscu_APDSCircProtectLight.Connect( pBundle, 1 );
		dscu_RingAlignedLight.Connect( pBundle, 2 );
		dscu_RingInitialLight.Connect( pBundle, 3 );
		dscu_FixersOffLight.Connect( pBundle, 4 );
		dscu_Hooks1OpenLight.Connect( pBundle, 5 );
		dscu_Hooks2OpenLight.Connect( pBundle, 6 );
		dscu_LatchesClosedLight.Connect( pBundle, 7 );
		dscu_UndockCompleteLight.Connect( pBundle, 8 );
		dscu_InitialContactLight.Connect( pBundle, 9 );
		dscu_CaptureLight.Connect( pBundle, 10 );
		dscu_RingForwardLight.Connect( pBundle, 11 );
		dscu_ReadyToHookLight.Connect( pBundle, 12 );
		dscu_InterfSealedLight.Connect( pBundle, 13 );
		dscu_Hooks1ClosedLight.Connect( pBundle, 14 );
		dscu_Hooks2ClosedLight.Connect( pBundle, 15 );

		pBundle = BundleManager()->CreateBundle("DSCU_TO_PANELA8A3_B", 16);
		dscu_LatchesOpenLight.Connect( pBundle, 0 );
		dscu_RingFinalLight.Connect( pBundle, 1 );
		dscu_PyroProtectCircuitOff.Connect( pBundle, 2 );
		dscu_ADSLight.Connect( pBundle, 3 );
		dscu_BDSLight.Connect( pBundle, 4 );
		dscu_CDSLight.Connect( pBundle, 5 );
		dscu_APLight.Connect( pBundle, 6 );
		dscu_BPLight.Connect( pBundle, 7 );
		dscu_CPLight.Connect( pBundle, 8 );

		AddMesh();
		DefineAnimations();

		STS()->SetAnimation(anim_ring, RingState.pos);

		CalculateRodAnimation();

		pBundle = BundleManager()->CreateBundle( "ODS_LIGHTS", 16 );
		vestibule_lights[0]->DefineState( 1, 0.5f, 0.0f, 1.0f, pBundle, 2 );
		vestibule_lights[0]->DefineMeshGroup( mesh_ods, GRP_CL_VESTIBULE_PORT_LIGHT_ODS );
		vestibule_lights[1]->DefineState( 1, 0.5f, 0.0f, 1.0f, pBundle, 3 );
		vestibule_lights[1]->DefineMeshGroup( mesh_ods, GRP_CL_VESTIBULE_STBD_LIGHT_ODS );
		return;
	}

	void ODS::OnSaveState(FILEHANDLE scn) const
	{
		WriteScenario_state(scn, "RING_STATE", RingState);
		return ExtAirlock::OnSaveState(scn);
	}

	void ODS::DefineAnimations( void )
	{
		anim_ring = STS()->CreateAnimation(0.0);

		static UINT grps_ring[2] = {GRP_DOCKING_RING_ODS, GRP_DOCKING_SIGHT_ODS};
		MGROUP_TRANSLATE* pRingAnim = new MGROUP_TRANSLATE(mesh_ods, grps_ring, 2, ODS_RING_TRANSLATION);
		ANIMATIONCOMPONENT_HANDLE parent = STS()->AddAnimationComponent(anim_ring, 0.0, 1.0, pRingAnim);
		SaveAnimation( pRingAnim );

		MGROUP_TRANSLATE* pRingAnimV = new MGROUP_TRANSLATE(LOCALVERTEXLIST, MAKEGROUPARRAY(odsAttachVec), 3, _V(0.0, 0.5446, 0.0));
		STS()->AddAnimationComponent(anim_ring, 0.0, 1.0, pRingAnimV);
		SaveAnimation( pRingAnimV );

		static UINT grps_coil[3] = { GRP_PETAL1_COIL_SPRING_ODS, GRP_PETAL2_COIL_SPRING_ODS, GRP_PETAL3_COIL_SPRING_ODS};
		MGROUP_SCALE* pCoilAnim = new MGROUP_SCALE(mesh_ods, grps_coil, 3, _V(0,2.10885 + 0.3292,0), _V(1,5.5,1));
		STS()->AddAnimationComponent(anim_ring, 0.0, 1.0, pCoilAnim);
		SaveAnimation( pCoilAnim );


		anim_rods = STS()->CreateAnimation(0.0);

		//Counterclockwise actuator of pair 1
		MGROUP_ROTATE* pRod1LAnim[2];
		static UINT grps_rod1l0[1] = {GRP_PETAL1_LEFTACTUATOR_ROD_ODS};
		pRod1LAnim[0] = new MGROUP_ROTATE(mesh_ods, grps_rod1l0, 1, ODS_ROD1L_REF, ODS_ROD1L_DIR, ODS_ROD_ROTATION);
		STS()->AddAnimationComponent(anim_rods, 0.0, 1.0, pRod1LAnim[0], parent);
		SaveAnimation( pRod1LAnim[0] );
		static UINT grps_rod1l1[1] = {GRP_PETAL1_LEFTACTUATOR_ODS};
		pRod1LAnim[1] = new MGROUP_ROTATE(mesh_ods, grps_rod1l1, 1, ODS_ROD1L_ACT_REF, ODS_ROD1L_ACT_DIR, ODS_ROD_ROTATION);
		STS()->AddAnimationComponent(anim_rods, 0.0, 1.0, pRod1LAnim[1]);
		SaveAnimation( pRod1LAnim[1] );

		//Clockwise actuator of pair 1
		MGROUP_ROTATE* pRod1RAnim[2];
		static UINT grps_rod1r0[1] = {GRP_PETAL1_RIGHTACTUATOR_ROD_ODS};
		pRod1RAnim[0] = new MGROUP_ROTATE(mesh_ods, grps_rod1r0, 1, ODS_ROD1R_REF, ODS_ROD1R_DIR, ODS_ROD_ROTATION);
		STS()->AddAnimationComponent(anim_rods, 0.0, 1.0, pRod1RAnim[0], parent);
		SaveAnimation( pRod1RAnim[0] );
		static UINT grps_rod1r1[1] = {GRP_PETAL1_RIGHTACTUATOR_ODS};
		pRod1RAnim[1] = new MGROUP_ROTATE(mesh_ods, grps_rod1r1, 1, ODS_ROD1R_ACT_REF, ODS_ROD1R_ACT_DIR, ODS_ROD_ROTATION);
		STS()->AddAnimationComponent(anim_rods, 0.0, 1.0, pRod1RAnim[1]);
		SaveAnimation( pRod1RAnim[1] );

		//Counterclockwise actuator of pair 2
		MGROUP_ROTATE* pRod2LAnim[2];
		static UINT grps_rod2l0[1] = {GRP_PETAL2_LEFTACTUATOR_ROD_ODS};
		pRod2LAnim[0] = new MGROUP_ROTATE(mesh_ods, grps_rod2l0, 1, ODS_ROD2L_REF, ODS_ROD2L_DIR, ODS_ROD_ROTATION);
		STS()->AddAnimationComponent(anim_rods, 0.0, 1.0, pRod2LAnim[0], parent);
		SaveAnimation( pRod2LAnim[0] );
		static UINT grps_rod2l1[1] = {GRP_PETAL2_LEFTACTUATOR_ODS};
		pRod2LAnim[1] = new MGROUP_ROTATE(mesh_ods, grps_rod2l1, 1, ODS_ROD2L_ACT_REF, ODS_ROD2L_ACT_DIR, ODS_ROD_ROTATION);
		STS()->AddAnimationComponent(anim_rods, 0.0, 1.0, pRod2LAnim[1]);
		SaveAnimation( pRod2LAnim[1] );

		//Clockwise actuator of pair 2
		MGROUP_ROTATE* pRod2RAnim[2];
		static UINT grps_rod2r0[1] = {GRP_PETAL2_RIGHTACTUATOR_ROD_ODS};
		pRod2RAnim[0] = new MGROUP_ROTATE(mesh_ods, grps_rod2r0, 1, ODS_ROD2R_REF, ODS_ROD2R_DIR, ODS_ROD_ROTATION);
		STS()->AddAnimationComponent(anim_rods, 0.0, 1.0, pRod2RAnim[0], parent);
		SaveAnimation( pRod2RAnim[0] );
		static UINT grps_rod2r1[1] = {GRP_PETAL2_RIGHTACTUATOR_ODS};
		pRod2RAnim[1] = new MGROUP_ROTATE(mesh_ods, grps_rod2r1, 1, ODS_ROD2R_ACT_REF, ODS_ROD2R_ACT_DIR, ODS_ROD_ROTATION);
		STS()->AddAnimationComponent(anim_rods, 0.0, 1.0, pRod2RAnim[1]);
		SaveAnimation( pRod2RAnim[1] );

		//Counterclockwise actuator of pair 3
		MGROUP_ROTATE* pRod3LAnim[2];
		static UINT grps_rod3l0[1] = {GRP_PETAL3_LEFTACTUATOR_ROD_ODS};
		pRod3LAnim[0] = new MGROUP_ROTATE(mesh_ods, grps_rod3l0, 1, ODS_ROD3L_REF, ODS_ROD3L_DIR, ODS_ROD_ROTATION);
		STS()->AddAnimationComponent(anim_rods, 0.0, 1.0, pRod3LAnim[0], parent);
		SaveAnimation( pRod3LAnim[0] );
		static UINT grps_rod3l1[1] = {GRP_PETAL3_LEFTACTUATOR_ODS};
		pRod3LAnim[1] = new MGROUP_ROTATE(mesh_ods, grps_rod3l1, 1, ODS_ROD3L_ACT_REF, ODS_ROD3L_ACT_DIR, ODS_ROD_ROTATION);
		STS()->AddAnimationComponent(anim_rods, 0.0, 1.0, pRod3LAnim[1]);
		SaveAnimation( pRod3LAnim[1] );

		//Clockwise actuator of pair 3
		MGROUP_ROTATE* pRod3RAnim[2];
		static UINT grps_rod3r0[1] = {GRP_PETAL3_RIGHTACTUATOR_ROD_ODS};
		pRod3RAnim[0] = new MGROUP_ROTATE(mesh_ods, grps_rod3r0, 1, ODS_ROD3R_REF, ODS_ROD3R_DIR, ODS_ROD_ROTATION);
		STS()->AddAnimationComponent(anim_rods, 0.0, 1.0, pRod3RAnim[0], parent);
		SaveAnimation( pRod3RAnim[0] );
		static UINT grps_rod3r1[1] = {GRP_PETAL3_RIGHTACTUATOR_ODS};
		pRod3RAnim[1] = new MGROUP_ROTATE(mesh_ods, grps_rod3r1, 1, ODS_ROD3R_ACT_REF, ODS_ROD3R_ACT_DIR, ODS_ROD_ROTATION);
		STS()->AddAnimationComponent(anim_rods, 0.0, 1.0, pRod3RAnim[1]);
		SaveAnimation( pRod3RAnim[1] );
		return;
	}

	bool ODS::HasDSCUPower() const {
		return bPowerRelay;
	}

	bool ODS::OnParseLine(const char* keyword, const char* line)
	{
		if(!_strnicmp(keyword, "RING_STATE", 10))
		{
			sscan_state((char*)line, RingState);
			return true;
		}
		else {
			return false;
		}
	}

	void ODS::VisualCreated( VISHANDLE vis )
	{
		ExtAirlock::VisualCreated( vis );

		// update UV in lights
		vestibule_lights[0]->VisualCreated();
		vestibule_lights[1]->VisualCreated();
		return;
	}

	void ODS::AddMesh( void )
	{
		VECTOR3 pos = aft ? ODS_MESH_AFT_OFFSET : ODS_MESH_OFFSET;
		mesh_ods = STS()->AddMesh( hODSMesh, &pos );
		STS()->SetMeshVisibilityMode( mesh_ods, MESHVIS_ALWAYS );
		oapiWriteLog( "(SSV_OV) [INFO] ODS mesh added" );
		return;
	}

	void ODS::SetDockParams( void )
	{
		VECTOR3 DockPos = ODS_DOCKPOS_OFFSET + (aft ? ODS_MESH_AFT_OFFSET : ODS_MESH_OFFSET);
		STS()->SetDockParams( DockPos, _V( 0, 1, 0 ), _V( 0, 0, -1 ) );

		odsAttachVec[0] = DockPos;
		odsAttachVec[1] = odsAttachVec[0] + _V(0.0, 1.0, 0.0);
		odsAttachVec[2] = odsAttachVec[0] + _V(0.0, 0.0, -1.0);
		return;
	}

	void ODS::UpdateODSAttachment( void )
	{
		/*if (ahDockAux) STS()->SetAttachmentParams( ahDockAux, odsAttachVec[0] + STS()->GetOrbiterCoGOffset(), odsAttachVec[1] - odsAttachVec[0], odsAttachVec[2] - odsAttachVec[0] );
		else ahDockAux = STS()->CreateAttachment( false, odsAttachVec[0] + STS()->GetOrbiterCoGOffset(), odsAttachVec[1] - odsAttachVec[0], odsAttachVec[2] - odsAttachVec[0], "APAS" );*/
		return;
	}

	void ODS::RunLights( double simdt )
	{
		vestibule_lights[0]->TimeStep( simdt );
		vestibule_lights[1]->TimeStep( simdt );
		return;
	}

	void ODS::ShiftCG( const VECTOR3& shift )
	{
		ExtAirlock::ShiftCG( shift );
		vestibule_lights[0]->ShiftLightPosition( shift );
		vestibule_lights[1]->ShiftLightPosition( shift );
		return;
	}
}

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
2023/02/05   GLS
2023/02/13   GLS
2023/02/12   GLS
2023/03/26   GLS
2023/08/29   GLS
2023/12/06   GLS
2023/12/20   GLS
********************************************/
#include "ODS.h"
#include "../Atlantis.h"
#include "../ExternalLight.h"
#include <CCTVCamera.h>
#include "../VideoControlUnit.h"
#include "APDS_Avionics.h"
#include "../meshres_ODS.h"
#include <VesselAPI.h>
#include "../../CommonDefs.h"
#include <EngConst.h>
#include <MathSSV.h>


namespace eva_docking
{
	const static char* MESHNAME_ODS = "SSV\\OV\\ODS";

	const VECTOR3 MESH_OFFSET = _V( 0.0, -1.49644, 7.7544 );// [m]
	const VECTOR3 MESH_AFT_OFFSET = _V( 0.0, -1.49644, 5.65636 );// [m]

	const VECTOR3 CL_CAMERA_POS = _V( 0.0, -0.278256, MESH_OFFSET.z );// Xo+649.0, Yo 0, Zo+405.86 [m]
	const VECTOR3 CL_CAMERA_POS_AFT = _V( 0.0, -0.278256, MESH_AFT_OFFSET.z );// Xo+731.60, Yo 0, Zo+405.86 [m]

	// offset between ODS mesh position and docking port position
	const VECTOR3 DOCKPOS_OFFSET = _V( 0.0, 2.59334, 0.0 );// [m]

	constexpr double MASS = 925.0 * LBM2KG;// [kg] (according to a SSP PRCB presentation on the STS-125 pros/cons of Single Pad vs Dual Pad ops for LON)
	constexpr VECTOR3 CG = {0.0, 0.8429, 7.7544};// (approx) Xo+649.0 Yo+0.0 Zo+450.0
	constexpr VECTOR3 AFT_CG = {0.0, 0.8429, 5.65636};// approx) Xo+731.60 Yo+0.0 Zo+450.0


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

	/*
	gaps [m]: fully ext <--> 0.108 <--> ready <--> 0.394 <--> interface <--> 0.006 <--> final
	*/
	const VECTOR3 RING_TRANSLATION = _V( 0.0, 0.508, 0.0 );

	const double RING_POS_FORWARD = 1.0;
	const double RING_POS_INITIAL = (0.394 + 0.006) / RING_TRANSLATION.y;
	const double RING_POS_INTERFACE = 0.006 / RING_TRANSLATION.y;// leveled with docking interface
	const double RING_POS_FINAL = 0.0;

	const double RING_POS_MARGIN = 0.025;

	const double RING_RATE = 0.0039815;// [1/s]


	constexpr double ROD_REF_Y = 2.53003;// top of actuator rods
	constexpr double ROD_ACT_REF_Y = 2.421608;// bottom of actuators main bases


	const VECTOR3 ROD1L_REF = _V( -0.369604, ROD_REF_Y, 0.351397 );
	const VECTOR3 ROD1L_DIR = _V( 0.5, 0.0, -0.866025 );
	const VECTOR3 ROD1L_ACT_REF = _V( -0.206963, ROD_ACT_REF_Y, 0.445277 );
	const VECTOR3 ROD1L_ACT_DIR = ROD1L_DIR;

	const VECTOR3 ROD1R_REF = _V( -0.48912, ROD_REF_Y, 0.144388 );
	const VECTOR3 ROD1R_DIR = _V( -1.0, 0.0, 0.0 );
	const VECTOR3 ROD1R_ACT_REF = _V( -0.489102, ROD_ACT_REF_Y, -0.043403 );
	const VECTOR3 ROD1R_ACT_DIR = ROD1R_DIR;


	const VECTOR3 ROD2L_REF = _V( 0.48912, ROD_REF_Y, 0.144388 );
	const VECTOR3 ROD2L_DIR = _V( -1.0, 0.0, 0.0 );
	const VECTOR3 ROD2L_ACT_REF = _V( 0.489102, ROD_ACT_REF_Y, -0.043403 );
	const VECTOR3 ROD2L_ACT_DIR = ROD2L_DIR;

	const VECTOR3 ROD2R_REF = _V( 0.369604, ROD_REF_Y, 0.351397 );
	const VECTOR3 ROD2R_DIR = _V( 0.5, 0.0, 0.866025 );
	const VECTOR3 ROD2R_ACT_REF = _V( 0.206963, ROD_ACT_REF_Y, 0.445277 );
	const VECTOR3 ROD2R_ACT_DIR = ROD2R_DIR;


	const VECTOR3 ROD3L_REF = _V( -0.119516, ROD_REF_Y, -0.495785 );
	const VECTOR3 ROD3L_DIR = _V( 0.5, 0.0, 0.866025 );
	const VECTOR3 ROD3L_ACT_REF = _V( -0.282139, ROD_ACT_REF_Y, -0.401873 );
	const VECTOR3 ROD3L_ACT_DIR = ROD3L_DIR;

	const VECTOR3 ROD3R_REF = _V( 0.119516, ROD_REF_Y, -0.495785 );
	const VECTOR3 ROD3R_DIR = _V( 0.5, 0.0, -0.866025 );
	const VECTOR3 ROD3R_ACT_REF = _V( 0.282139, ROD_ACT_REF_Y, -0.401873 );
	const VECTOR3 ROD3R_ACT_DIR = ROD3R_DIR;

	const VECTOR3 ROD_DISPLACEMENT = ROD3L_REF - ROD3L_ACT_REF;
	const double ROD_DISPLACEMENT_LEN = length( ROD_DISPLACEMENT );

	const double ROD_HORIZ_DIST = sqrt( pow( ROD_DISPLACEMENT.x, 2 ) + pow( ROD_DISPLACEMENT.z, 2 ) );// [m]
	const double ROD_NULLANGLE = atan2( ROD_DISPLACEMENT.y, ROD_HORIZ_DIST );// [rad]
	const float ROD_ROTATION = static_cast<float>(90.0f * RAD);

	const float RODDRIVE_ROTATION = static_cast<float>(400.0 * PI);// 20 rotations per meter

	const VECTOR3 CABLE_COIL_TOP_POS = _V( 0.0, 2.519931, 0.0 );
	const VECTOR3 CABLE_COIL_BOTTOM_POS = _V( 0.0, 2.43851, 0.0 );
	const double CABLE_COIL_INITIAL_LENGTH = CABLE_COIL_TOP_POS.y - CABLE_COIL_BOTTOM_POS.y;
	const VECTOR3 CABLE_COIL_SCALE = _V( 1.0, (CABLE_COIL_INITIAL_LENGTH + RING_TRANSLATION.y) / CABLE_COIL_INITIAL_LENGTH, 1.0 );


	// hook animation data
	const float HOOK_ROTATION = static_cast<float>(8.0f * RAD);
	const double HOOK_REF_Y = 2.498806;
	const double HOOK_POS_RADIUS = 0.6756;

	const VECTOR3 HOOK_1_REF = _V( -HOOK_POS_RADIUS * cos( 15 * RAD ), HOOK_REF_Y, HOOK_POS_RADIUS * sin( 15 * RAD ) );
	const VECTOR3 HOOK_1_DIR = _V( -cos( 15 * RAD ), 0.0, sin( 15 * RAD ) );

	const VECTOR3 HOOK_2_REF = _V( -HOOK_POS_RADIUS * cos( 45 * RAD ), HOOK_REF_Y, HOOK_POS_RADIUS * sin( 45 * RAD ) );
	const VECTOR3 HOOK_2_DIR = _V( -cos( 45 * RAD ), 0.0, sin( 45 * RAD ) );

	const VECTOR3 HOOK_3_REF = _V( -HOOK_POS_RADIUS * cos( 75 * RAD ), HOOK_REF_Y, HOOK_POS_RADIUS * sin( 75 * RAD ) );
	const VECTOR3 HOOK_3_DIR = _V( -cos( 75 * RAD ), 0.0, sin( 75 * RAD ) );

	const VECTOR3 HOOK_4_REF = _V( -HOOK_POS_RADIUS * cos( 105 * RAD ), HOOK_REF_Y, HOOK_POS_RADIUS * sin( 105 * RAD ) );
	const VECTOR3 HOOK_4_DIR = _V( -cos( 105 * RAD ), 0.0, sin( 105 * RAD ) );

	const VECTOR3 HOOK_5_REF = _V( -HOOK_POS_RADIUS * cos( 135 * RAD ), HOOK_REF_Y, HOOK_POS_RADIUS * sin( 135 * RAD ) );
	const VECTOR3 HOOK_5_DIR = _V( -cos( 135 * RAD ), 0.0, sin( 135 * RAD ) );

	const VECTOR3 HOOK_6_REF = _V( -HOOK_POS_RADIUS * cos( 165 * RAD ), HOOK_REF_Y, HOOK_POS_RADIUS * sin( 165 * RAD ) );
	const VECTOR3 HOOK_6_DIR = _V( -cos( 165 * RAD ), 0.0, sin( 165 * RAD ) );

	const VECTOR3 HOOK_7_REF = _V( -HOOK_POS_RADIUS * cos( 195 * RAD ), HOOK_REF_Y, HOOK_POS_RADIUS * sin( 195 * RAD ) );
	const VECTOR3 HOOK_7_DIR = _V( -cos( 195 * RAD ), 0.0, sin( 195 * RAD ) );

	const VECTOR3 HOOK_8_REF = _V( -HOOK_POS_RADIUS * cos( 225 * RAD ), HOOK_REF_Y, HOOK_POS_RADIUS * sin( 225 * RAD ) );
	const VECTOR3 HOOK_8_DIR = _V( -cos( 225 * RAD ), 0.0, sin( 225 * RAD ) );

	const VECTOR3 HOOK_9_REF = _V( -HOOK_POS_RADIUS * cos( 255 * RAD ), HOOK_REF_Y, HOOK_POS_RADIUS * sin( 255 * RAD ) );
	const VECTOR3 HOOK_9_DIR = _V( -cos( 255 * RAD ), 0.0, sin( 255 * RAD ) );

	const VECTOR3 HOOK_10_REF = _V( -HOOK_POS_RADIUS * cos( 285 * RAD ), HOOK_REF_Y, HOOK_POS_RADIUS * sin( 285 * RAD ) );
	const VECTOR3 HOOK_10_DIR = _V( -cos( 285 * RAD ), 0.0, sin( 285 * RAD ) );

	const VECTOR3 HOOK_11_REF = _V( -HOOK_POS_RADIUS * cos( 315 * RAD ), HOOK_REF_Y, HOOK_POS_RADIUS * sin( 315 * RAD ) );
	const VECTOR3 HOOK_11_DIR = _V( -cos( 315 * RAD ), 0.0, sin( 315 * RAD ) );

	const VECTOR3 HOOK_12_REF = _V( -HOOK_POS_RADIUS * cos( 345 * RAD ), HOOK_REF_Y, HOOK_POS_RADIUS * sin( 345 * RAD ) );
	const VECTOR3 HOOK_12_DIR = _V( -cos( 345 * RAD ), 0.0, sin( 345 * RAD ) );

	const double HOOK_RATE = 0.00333333;// ~300s (single motor) [1/s]


	ODS::ODS( AtlantisSubsystemDirector* _director, bool aftlocation ) : ExtAirlock( _director, "ODS", aftlocation, true, true ),
		fHooks1State(0.0), fHooks2State(0.0),
		bFirstStep(true), bTargetInCone(false),
		bTargetCaptured(false), APASdevices_populated(false), extend_goal(RETRACT_TO_FINAL),
		anim_ring(-1), anim_rods(-1),
		bPowerRelay(false), bFixersOn(true),
		hooks_1_cl_ind_1(true), hooks_1_cl_ind_2(true), hooks_1_cl_ind_3(true), hooks_1_op_ind_1(true), hooks_1_op_ind_2(true), hooks_1_op_ind_3(true),
		hooks_2_cl_ind_1(true), hooks_2_cl_ind_2(true), hooks_2_cl_ind_3(true), hooks_2_op_ind_1(true), hooks_2_op_ind_2(true), hooks_2_op_ind_3(true),
		gnd_hooks_1_cl_1(true), gnd_hooks_1_cl_2(true), gnd_hooks_1_cl_3(true),
		gnd_hooks_2_cl_1(true), gnd_hooks_2_cl_2(true), gnd_hooks_2_cl_3(true)
	{
		RingState.Set(AnimState::STOPPED, 0.0);
		target_pos = _V(0.0, 2000.0, 0.0);

		mesh_ods = MESH_UNDEFINED;
		hODSMesh = oapiLoadMeshGlobal( MESHNAME_ODS );
		oapiWriteLog( "(SSV_OV) [INFO] ODS mesh loaded" );

		ahDockAux = NULL;

		pPSU = new PSU();
		pDSCU = new DSCU();
		pPACU[0] = new PACU();
		pPACU[1] = new PACU();

		camera = new CCTVCamera( STS(), aftlocation ? CL_CAMERA_POS_AFT : CL_CAMERA_POS );

		SetDockParams();

		// vestibule lights
		vestibule_lights[0] = new ExternalLight( STS(), LIGHT_VESTIBULE_PORT_POS + (aft ? _V( 0.0, 0.0, 0.0) : _V( 0.0, 0.0, MESH_OFFSET.z - MESH_AFT_OFFSET.z )), LIGHT_DIR, 0.0f, 0.0f, LIGHT_RANGE, LIGHT_ATT0, LIGHT_ATT1, LIGHT_ATT2, LIGHT_UMBRA_ANGLE, LIGHT_PENUMBRA_ANGLE, INCANDESCENT );
		vestibule_lights[1] = new ExternalLight( STS(), LIGHT_VESTIBULE_STBD_POS + (aft ? _V( 0.0, 0.0, 0.0) : _V( 0.0, 0.0, MESH_OFFSET.z - MESH_AFT_OFFSET.z )), LIGHT_DIR, 0.0f, 0.0f, LIGHT_RANGE, LIGHT_ATT0, LIGHT_ATT1, LIGHT_ATT2, LIGHT_UMBRA_ANGLE, LIGHT_PENUMBRA_ANGLE, INCANDESCENT );
	}

	ODS::~ODS()
	{
		delete pPSU;
		delete pDSCU;
		delete pPACU[0];
		delete pPACU[1];

		delete camera;

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
		return EXTAL_MASS + MASS;
	}

	bool ODS::GetSubsystemCoG( VECTOR3& CoG ) const
	{
		VECTOR3 cgODS = aft ? AFT_CG : CG;
		VECTOR3 cgAL = aft ? EXTAL_AFT_CG : EXTAL_CG;
		CoG = ((cgAL * EXTAL_MASS) + (cgODS * MASS)) / (EXTAL_MASS + MASS);
		return true;
	}

	void ODS::CalculateRodAnimation()
	{
		double ringPos = RingState.pos * RING_TRANSLATION.y;
		double angle = atan2( ringPos + ROD_DISPLACEMENT.y, ROD_HORIZ_DIST );
		double pos = min(max((angle - ROD_NULLANGLE) / ROD_ROTATION, 0.0), 1.0);
		STS()->SetAnimation( anim_rods, pos );
		return;
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

		camera->TimeStep( simdt );

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

		/*bool CNTL_PNL = (dscu_ControlPanelPowerA.IsSet() && dscu_ControlPanelPowerB.IsSet()) || (dscu_ControlPanelPowerB.IsSet() && dscu_ControlPanelPowerC.IsSet()) || (dscu_ControlPanelPowerC.IsSet() && dscu_ControlPanelPowerA.IsSet());


		/*if (HasDSCUPower())
		{
			dscu_RingAlignedLight.SetLine( (int)CNTL_PNL * 5.0f );

			if(dscu_FixerOff && CNTL_PNL) {
				bFixersOn = false;
			}

			if(!bFixersOn) {
				dscu_FixersOffLight.SetLine( (int)CNTL_PNL * 5.0f );
			} else {
				dscu_FixersOffLight.ResetLine();
			}

			if(dscu_RingOut.IsSet() && CNTL_PNL && bAPDSCircuitProtectionOff) {
				RingState.action = AnimState::OPENING;
				extend_goal = EXTEND_TO_INITIAL;
				if(RingState.pos >= (RING_POS_INITIAL + RING_POS_MARGIN)) {
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
				RingState.Move(RING_RATE * simdt);

				if(RingState.pos >= RING_POS_INITIAL &&
					extend_goal == EXTEND_TO_INITIAL) {
					RingState.action = AnimState::STOPPED;
				}

				if(RingState.pos >= RING_POS_FORWARD &&
					extend_goal == EXTEND_TO_FINAL) {
					RingState.action = AnimState::STOPPED;
				}
				STS()->SetAnimation(anim_ring, RingState.pos);
				UpdateODSAttachment();

				CalculateRodAnimation();
			}

			if(RingState.pos < (RING_POS_FINAL + RING_POS_MARGIN)) {
				dscu_RingFinalLight.SetLine( (int)CNTL_PNL * 5.0f );
			} else {
				dscu_RingFinalLight.ResetLine();
			}

			if((RingState.pos >= (RING_POS_INITIAL - RING_POS_MARGIN) && RingState.pos < (RING_POS_INITIAL + RING_POS_MARGIN))) {
				dscu_RingInitialLight.SetLine( (int)CNTL_PNL * 5.0f );
			} else {
				dscu_RingInitialLight.ResetLine();
			}

			if(RingState.pos >= (RING_POS_FORWARD - RING_POS_MARGIN) ) {
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

			if(bTargetCaptured) dscu_CaptureLight.SetLine( (int)CNTL_PNL * 5.0f );
			else dscu_CaptureLight.ResetLine();

		}*/

		///////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////





		// hook position sensors (ground)
		bool hooks_1_cl_ind_a = !(fHooks1State >= 0.99);
		bool hooks_1_cl_ind_b = !(fHooks1State >= 0.99);
		bool hooks_1_op_ind_a = !(fHooks1State <= 0.01);
		bool hooks_1_op_ind_b = !(fHooks1State <= 0.01);
		bool inbetweenhooks_ind_1 = !((fHooks1State > 0.01) && (fHooks1State < 0.99));
		bool hooks_2_cl_ind_a = !(fHooks2State >= 0.99);
		bool hooks_2_cl_ind_b = !(fHooks2State >= 0.99);
		bool hooks_2_op_ind_a = !(fHooks2State <= 0.01);
		bool hooks_2_op_ind_b = !(fHooks2State <= 0.01);
		bool inbetweenhooks_ind_2 = !((fHooks2State > 0.01) && (fHooks2State < 0.99));

		bool interfacesealed_ind_1 = true;// TODO
		bool interfacesealed_ind_2 = true;// TODO
		bool interfacesealed_ind_3 = true;// TODO

		bool undockingcomplete_ind_1 = true;// TODO
		bool undockingcomplete_ind_2 = true;// TODO

		bool readytohook_ind_1 = true;// TODO
		bool readytohook_ind_2 = true;// TODO



		bool gnd_pnl = !dipControlPanelPowerA.IsSet() && !dipControlPanelPowerB.IsSet() && !dipControlPanelPowerC.IsSet();
		bool cntl_pnl_a = dipControlPanelPowerA.IsSet();
		bool cntl_pnl_b = dipControlPanelPowerB.IsSet();
		bool cntl_pnl_c = dipControlPanelPowerC.IsSet();

		bool gnd_c = !dipAPDSPowerA.IsSet() && !dipAPDSPowerB.IsSet() && !dipAPDSPowerC.IsSet();
		bool wa = dipAPDSPowerA.IsSet();
		bool wb = dipAPDSPowerB.IsSet();
		bool wc = dipAPDSPowerC.IsSet();

		bool cw1 = true;// TODO
		bool cw2 = true;// TODO
		bool gnd_cw1 = false;// TODO
		bool gnd_cw2 = false;// TODO


		// PSU
		PSU::PSU_IO psu_io;
		psu_io.cntl_pnl_a = cntl_pnl_a;
		psu_io.cntl_pnl_b = cntl_pnl_b;
		psu_io.cntl_pnl_c = cntl_pnl_c;
		psu_io.power_on = !dipPowerOn.IsSet();
		psu_io.power_off = !dipPowerOff.IsSet();
		psu_io.gnd_c = gnd_c;
		psu_io.wa = wa;
		psu_io.wb = wb;
		psu_io.wc = wc;
		psu_io.cw1 = cw1;
		psu_io.cw2 = cw2;

		pPSU->Run( simdt, psu_io );

		bool gnd_abc = psu_io.gnd_c_1 && psu_io.gnd_c_2 && psu_io.gnd_c_3;
		bool pwr_a = psu_io.pwr_wa_1 || psu_io.pwr_wa_2;
		bool pwr_b = psu_io.pwr_wb_1 || psu_io.pwr_wb_2;
		bool pwr_c = psu_io.pwr_wc_1 || psu_io.pwr_wc_2;


		// DSCU
		DSCU::DSCU_IO dscu_io;
		dscu_io.pwr_a = pwr_a;
		dscu_io.pwr_b = pwr_b;
		dscu_io.pwr_c = pwr_c;
		dscu_io.gnd_abc = gnd_abc;
		dscu_io.gnd_pnl = gnd_pnl;
		dscu_io.gnd_hooks_1_cl_1 = gnd_hooks_1_cl_1;
		dscu_io.gnd_hooks_1_cl_2 = gnd_hooks_1_cl_2;
		dscu_io.gnd_hooks_1_cl_3 = gnd_hooks_1_cl_3;
		dscu_io.gnd_hooks_2_cl_1 = gnd_hooks_2_cl_1;
		dscu_io.gnd_hooks_2_cl_2 = gnd_hooks_2_cl_2;
		dscu_io.gnd_hooks_2_cl_3 = gnd_hooks_2_cl_3;
		dscu_io.open_hooks = !dipOpenHooks.IsSet();
		dscu_io.close_hooks = !dipCloseHooks.IsSet();
		dscu_io.undocking = !dipUndocking.IsSet();
		dscu_io.apds_circ_prot_off = !dipAPDSCircProtOff.IsSet();
		dscu_io.hooks_1_cl_ind_1 = hooks_1_cl_ind_1;
		dscu_io.hooks_1_cl_ind_2 = hooks_1_cl_ind_2;
		dscu_io.hooks_1_cl_ind_3 = hooks_1_cl_ind_3;
		dscu_io.hooks_1_op_ind_1 = hooks_1_op_ind_1;
		dscu_io.hooks_1_op_ind_2 = hooks_1_op_ind_2;
		dscu_io.hooks_1_op_ind_3 = hooks_1_op_ind_3;
		dscu_io.hooks_2_cl_ind_1 = hooks_2_cl_ind_1;
		dscu_io.hooks_2_cl_ind_2 = hooks_2_cl_ind_2;
		dscu_io.hooks_2_cl_ind_3 = hooks_2_cl_ind_3;
		dscu_io.hooks_2_op_ind_1 = hooks_2_op_ind_1;
		dscu_io.hooks_2_op_ind_2 = hooks_2_op_ind_2;
		dscu_io.hooks_2_op_ind_3 = hooks_2_op_ind_3;
		dscu_io.interfacesealed_ind_1 = interfacesealed_ind_1;
		dscu_io.interfacesealed_ind_2 = interfacesealed_ind_2;
		dscu_io.interfacesealed_ind_3 = interfacesealed_ind_3;
		dscu_io.undockingcomplete_ind_1 = undockingcomplete_ind_1;
		dscu_io.undockingcomplete_ind_2 = undockingcomplete_ind_2;
		dscu_io.readytohook_ind_1 = readytohook_ind_1;
		dscu_io.readytohook_ind_2 = readytohook_ind_2;
		dscu_io.inbetweenhooks_ind_1 = inbetweenhooks_ind_1;
		dscu_io.inbetweenhooks_ind_2 = inbetweenhooks_ind_2,

		pDSCU->Run( simdt, dscu_io );


		// PACU
		PACU::PACU_IO pacu_io_1;
		pacu_io_1.gnd_1 = gnd_cw1;
		pacu_io_1.gnd_2 = gnd_cw2;
		pacu_io_1.gnd_abc = gnd_abc;
		pacu_io_1.pwr_1 = cw1;
		pacu_io_1.pwr_2 = cw2;
		pacu_io_1.pwr_a = pwr_a;
		pacu_io_1.pwr_b = pwr_b;
		pacu_io_1.pwr_c = pwr_c;
		pacu_io_1.hooks_cl_1 = dscu_io.hooks_1_cl_1;
		pacu_io_1.hooks_cl_2 = dscu_io.hooks_1_cl_2;
		pacu_io_1.hooks_cl_3 = dscu_io.hooks_1_cl_3;
		pacu_io_1.hooks_op_1 = dscu_io.hooks_1_op_1;
		pacu_io_1.hooks_op_2 = dscu_io.hooks_1_op_2;
		pacu_io_1.hooks_op_3 = dscu_io.hooks_1_op_3;
		pacu_io_1.hooks_cl_ind_a = hooks_1_cl_ind_a;
		pacu_io_1.hooks_cl_ind_b = hooks_1_cl_ind_b;
		pacu_io_1.hooks_op_ind_a = hooks_1_op_ind_a;
		pacu_io_1.hooks_op_ind_b = hooks_1_op_ind_b;

		pPACU[0]->Run( simdt, pacu_io_1 );

		hooks_1_cl_ind_1 = pacu_io_1.hooks_cl_ind_1;
		hooks_1_cl_ind_2 = pacu_io_1.hooks_cl_ind_2;
		hooks_1_cl_ind_3 = pacu_io_1.hooks_cl_ind_3;
		hooks_1_op_ind_1 = pacu_io_1.hooks_op_ind_1;
		hooks_1_op_ind_2 = pacu_io_1.hooks_op_ind_2;
		hooks_1_op_ind_3 = pacu_io_1.hooks_op_ind_3;
		gnd_hooks_1_cl_1 = pacu_io_1.gnd_hooks_cl_1;
		gnd_hooks_1_cl_2 = pacu_io_1.gnd_hooks_cl_2;
		gnd_hooks_1_cl_3 = pacu_io_1.gnd_hooks_cl_3;


		PACU::PACU_IO pacu_io_2;
		pacu_io_2.gnd_1 = gnd_cw1;
		pacu_io_2.gnd_2 = gnd_cw2;
		pacu_io_2.gnd_abc = gnd_abc;
		pacu_io_2.pwr_1 = cw1;
		pacu_io_2.pwr_2 = cw2;
		pacu_io_2.pwr_a = pwr_a;
		pacu_io_2.pwr_b = pwr_b;
		pacu_io_2.pwr_c = pwr_c;
		pacu_io_2.hooks_cl_1 = dscu_io.hooks_2_cl_1;
		pacu_io_2.hooks_cl_2 = dscu_io.hooks_2_cl_2;
		pacu_io_2.hooks_cl_3 = dscu_io.hooks_2_cl_3;
		pacu_io_2.hooks_op_1 = dscu_io.hooks_2_op_1;
		pacu_io_2.hooks_op_2 = dscu_io.hooks_2_op_2;
		pacu_io_2.hooks_op_3 = dscu_io.hooks_2_op_3;
		pacu_io_2.hooks_cl_ind_a = hooks_2_cl_ind_a;
		pacu_io_2.hooks_cl_ind_b = hooks_2_cl_ind_b;
		pacu_io_2.hooks_op_ind_a = hooks_2_op_ind_a;
		pacu_io_2.hooks_op_ind_b = hooks_2_op_ind_b;

		pPACU[1]->Run( simdt, pacu_io_2 );

		hooks_2_cl_ind_1 = pacu_io_2.hooks_cl_ind_1;
		hooks_2_cl_ind_2 = pacu_io_2.hooks_cl_ind_2;
		hooks_2_cl_ind_3 = pacu_io_2.hooks_cl_ind_3;
		hooks_2_op_ind_1 = pacu_io_2.hooks_op_ind_1;
		hooks_2_op_ind_2 = pacu_io_2.hooks_op_ind_2;
		hooks_2_op_ind_3 = pacu_io_2.hooks_op_ind_3;
		gnd_hooks_2_cl_1 = pacu_io_2.gnd_hooks_cl_1;
		gnd_hooks_2_cl_2 = pacu_io_2.gnd_hooks_cl_2;
		gnd_hooks_2_cl_3 = pacu_io_2.gnd_hooks_cl_3;


		// hooks motor logic and animation
		short hooks_1_motor_1_pwr_a = pacu_io_1.motor_1_pwr_a1 + pacu_io_1.motor_1_pwr_a2;
		short hooks_1_motor_1_pwr_b = pacu_io_1.motor_1_pwr_b1 + pacu_io_1.motor_1_pwr_b2;
		short hooks_1_motor_1_pwr = 0;
		if ((hooks_1_motor_1_pwr_a != 0) && (hooks_1_motor_1_pwr_b != 0))
		{
			if ((sign( hooks_1_motor_1_pwr_a ) > 0) && (sign( hooks_1_motor_1_pwr_b ) < 0))
			{
				hooks_1_motor_1_pwr = 1;
			}
			else if ((sign( hooks_1_motor_1_pwr_a ) < 0) && (sign( hooks_1_motor_1_pwr_b ) > 0))
			{
				hooks_1_motor_1_pwr = -1;
			}
		}

		short hooks_1_motor_2_pwr_a = pacu_io_1.motor_2_pwr_a1 + pacu_io_1.motor_2_pwr_a2;
		short hooks_1_motor_2_pwr_b = pacu_io_1.motor_2_pwr_b1 + pacu_io_1.motor_2_pwr_b2;
		short hooks_1_motor_2_pwr = 0;
		if ((hooks_1_motor_2_pwr_a != 0) && (hooks_1_motor_2_pwr_b != 0))
		{
			if ((sign( hooks_1_motor_2_pwr_a ) > 0) && (sign( hooks_1_motor_2_pwr_b ) < 0))
			{
				hooks_1_motor_2_pwr = 1;
			}
			else if ((sign( hooks_1_motor_2_pwr_a ) < 0) && (sign( hooks_1_motor_2_pwr_b ) > 0))
			{
				hooks_1_motor_2_pwr = -1;
			}
		}

		fHooks1State = range( 0.0, fHooks1State + (simdt * HOOK_RATE * (hooks_1_motor_1_pwr + hooks_1_motor_2_pwr)), 1.0 );

		short hooks_2_motor_1_pwr_a = pacu_io_2.motor_1_pwr_a1 + pacu_io_2.motor_1_pwr_a2;
		short hooks_2_motor_1_pwr_b = pacu_io_2.motor_1_pwr_b1 + pacu_io_2.motor_1_pwr_b2;
		short hooks_2_motor_1_pwr = 0;
		if ((hooks_2_motor_1_pwr_a != 0) && (hooks_2_motor_1_pwr_b != 0))
		{
			if ((sign( hooks_2_motor_1_pwr_a ) > 0) && (sign( hooks_2_motor_1_pwr_b ) < 0))
			{
				hooks_2_motor_1_pwr = 1;
			}
			else if ((sign( hooks_2_motor_1_pwr_a ) < 0) && (sign( hooks_2_motor_1_pwr_b ) > 0))
			{
				hooks_2_motor_1_pwr = -1;
			}
		}

		short hooks_2_motor_2_pwr_a = pacu_io_2.motor_2_pwr_a1 + pacu_io_2.motor_2_pwr_a2;
		short hooks_2_motor_2_pwr_b = pacu_io_2.motor_2_pwr_b1 + pacu_io_2.motor_2_pwr_b2;
		short hooks_2_motor_2_pwr = 0;
		if ((hooks_2_motor_2_pwr_a != 0) && (hooks_2_motor_2_pwr_b != 0))
		{
			if ((sign( hooks_2_motor_2_pwr_a ) > 0) && (sign( hooks_2_motor_2_pwr_b ) < 0))
			{
				hooks_2_motor_2_pwr = 1;
			}
			else if ((sign( hooks_2_motor_2_pwr_a ) < 0) && (sign( hooks_2_motor_2_pwr_b ) > 0))
			{
				hooks_2_motor_2_pwr = -1;
			}
		}

		fHooks2State = range( 0.0, fHooks2State + (simdt * HOOK_RATE * (hooks_2_motor_1_pwr + hooks_2_motor_2_pwr)), 1.0 );

		STS()->SetAnimation( anim_hooks1, fHooks1State );
		STS()->SetAnimation( anim_hooks2, fHooks2State );


		// panel lights output
		{
			bool out_1;
			bool out_2;

			_2of3VotingRelay( dscu_io.power_on_light_1, dscu_io.power_on_light_2, dscu_io.power_on_light_3, cntl_pnl_a, cntl_pnl_b, cntl_pnl_c, gnd_pnl, gnd_pnl, out_1, out_2 );
			dopPowerOnLight_A.SetLine( (int)!out_1 * 5.0f );
			dopPowerOnLight_C.SetLine( (int)!out_2 * 5.0f );

			// E23
			_2of3VotingRelay( dscu_io.readytohook_light_1, dscu_io.readytohook_light_2, dscu_io.readytohook_light_3, cntl_pnl_a, cntl_pnl_b, cntl_pnl_c, gnd_pnl, gnd_pnl, out_1, out_2 );
			dopReadyToHookLight_A.SetLine( (int)!out_1 * 5.0f );
			dopReadyToHookLight_C.SetLine( (int)!out_2 * 5.0f );

			// E24
			_2of3VotingRelay( dscu_io.interfsealed_light_1, dscu_io.interfsealed_light_2, dscu_io.interfsealed_light_3, cntl_pnl_a, cntl_pnl_b, cntl_pnl_c, gnd_pnl, gnd_pnl, out_1, out_2 );
			dopInterfSealedLight_A.SetLine( (int)!out_1 * 5.0f );
			dopInterfSealedLight_C.SetLine( (int)!out_2 * 5.0f );

			_2of3VotingRelay( dscu_io.hooks_1_op_light_1, dscu_io.hooks_1_op_light_2, dscu_io.hooks_1_op_light_3, cntl_pnl_a, cntl_pnl_b, cntl_pnl_c, gnd_pnl, gnd_pnl, out_1, out_2 );
			dopHooks1OpenLight_A.SetLine( (int)!out_1 * 5.0f );
			dopHooks1OpenLight_C.SetLine( (int)!out_2 * 5.0f );

			_2of3VotingRelay( dscu_io.hooks_2_op_light_1, dscu_io.hooks_2_op_light_2, dscu_io.hooks_2_op_light_3, cntl_pnl_a, cntl_pnl_b, cntl_pnl_c, gnd_pnl, gnd_pnl, out_1, out_2 );
			dopHooks2OpenLight_A.SetLine( (int)!out_1 * 5.0f );
			dopHooks2OpenLight_C.SetLine( (int)!out_2 * 5.0f );

			// E17
			_2of3VotingRelay( dscu_io.hooks_1_cl_light_1, dscu_io.hooks_1_cl_light_2, dscu_io.hooks_1_cl_light_3, cntl_pnl_a, cntl_pnl_b, cntl_pnl_c, gnd_pnl, gnd_pnl, out_1, out_2 );
			dopHooks1ClosedLight_A.SetLine( (int)!out_1 * 5.0f );
			dopHooks1ClosedLight_C.SetLine( (int)!out_2 * 5.0f );

			// E18
			_2of3VotingRelay( dscu_io.hooks_2_cl_light_1, dscu_io.hooks_2_cl_light_2, dscu_io.hooks_2_cl_light_3, cntl_pnl_a, cntl_pnl_b, cntl_pnl_c, gnd_pnl, gnd_pnl, out_1, out_2 );
			dopHooks2ClosedLight_A.SetLine( (int)!out_1 * 5.0f );
			dopHooks2ClosedLight_C.SetLine( (int)!out_2 * 5.0f );

			// E25
			_2of3VotingRelay( dscu_io.undockcomplet_light_1 && dscu_io.undockcomplet_light_2, dscu_io.undockcomplet_light_1, dscu_io.undockcomplet_light_2, cntl_pnl_a, cntl_pnl_b, cntl_pnl_c, gnd_pnl, gnd_pnl, out_1, out_2 );
			dopUndockCompletLight_A.SetLine( (int)!out_1 * 5.0f );
			dopUndockCompletLight_C.SetLine( (int)!out_2 * 5.0f );

			// E26
			_2of3VotingRelay( dscu_io.apdscirprotoff_light_1, dscu_io.apdscirprotoff_light_2, dscu_io.apdscirprotoff_light_1 && dscu_io.apdscirprotoff_light_2, cntl_pnl_a, cntl_pnl_b, cntl_pnl_c, gnd_pnl, gnd_pnl, out_1, out_2 );
			dopAPDSCircuitProtectOffLight_A.SetLine( (int)!out_1 * 5.0f );
			dopAPDSCircuitProtectOffLight_C.SetLine( (int)!out_2 * 5.0f );
		}

		return;
	}

	void ODS::Realize( void )
	{
		ExtAirlock::Realize();

		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "PANELA8A3_TO_AVIONICS_A", 16 );
		dipPowerOn.Connect( pBundle, 0 );
		dipPowerOff.Connect( pBundle, 1 );
		dipRingOut.Connect( pBundle, 2 );
		dipRingIn.Connect( pBundle, 3 );
		dipAPDSCircProtOff.Connect( pBundle, 4 );
		dipCloseHooks.Connect( pBundle, 5 );
		dipCloseLatches.Connect( pBundle, 6 );
		dipFixerOff.Connect( pBundle, 7 );
		dipPyroCircProtOff.Connect( pBundle, 8 );
		dipPyroCircProtOn.Connect( pBundle, 9 );
		dipActHooksFiring.Connect( pBundle, 10 );
		dipPasHooksFiring.Connect( pBundle, 11 );
		dipOpenHooks.Connect( pBundle, 12 );
		dipOpenLatches.Connect( pBundle, 13 );
		dipUndocking.Connect( pBundle, 14 );

		pBundle = BundleManager()->CreateBundle( "PANELA8A3_TO_AVIONICS_B", 16 );
		dipControlPanelPowerA.Connect( pBundle, 0 );
		dipControlPanelPowerB.Connect( pBundle, 1 );
		dipControlPanelPowerC.Connect( pBundle, 2 );
		dipHeatersDCUPowerH1.Connect( pBundle, 3 );
		dipHeatersDCUPowerH2DCU.Connect( pBundle, 4 );
		dipHeatersDCUPowerH3DCU.Connect( pBundle, 5 );
		dipAPDSPowerA.Connect( pBundle, 6 );
		dipAPDSPowerB.Connect( pBundle, 7 );
		dipAPDSPowerC.Connect( pBundle, 8 );
		dipPyrosAp.Connect( pBundle, 9 );
		dipPyrosBp.Connect( pBundle, 10 );
		dipPyrosCp.Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle( "AVIONICS_TO_PANELA8A3_A", 16 );
		dopPowerOnLight_A.Connect( pBundle, 0 );
		dopPowerOnLight_C.Connect( pBundle, 1 );
		dopAPDSCircuitProtectOffLight_A.Connect( pBundle, 2 );
		dopAPDSCircuitProtectOffLight_C.Connect( pBundle, 3 );
		dopRingAlignedLight_A.Connect( pBundle, 4 );
		dopRingAlignedLight_C.Connect( pBundle, 5 );
		dopRingInitialPositionLight_A.Connect( pBundle, 6 );
		dopRingInitialPositionLight_C.Connect( pBundle, 7 );
		dopFixersOffLight_A.Connect( pBundle, 8 );
		dopFixersOffLight_C.Connect( pBundle, 9 );
		dopHooks1OpenLight_A.Connect( pBundle, 10 );
		dopHooks1OpenLight_C.Connect( pBundle, 11 );
		dopHooks2OpenLight_A.Connect( pBundle, 12 );
		dopHooks2OpenLight_C.Connect( pBundle, 13 );
		dopLatchesClosedLight_A.Connect( pBundle, 14 );
		dopLatchesClosedLight_C.Connect( pBundle, 15 );

		pBundle = BundleManager()->CreateBundle( "AVIONICS_TO_PANELA8A3_B", 16 );
		dopUndockCompletLight_A.Connect( pBundle, 0 );
		dopUndockCompletLight_C.Connect( pBundle, 1 );
		dopInitialContactLight_A.Connect( pBundle, 2 );
		dopInitialContactLight_C.Connect( pBundle, 3 );
		dopCaptureCaptureLight_A.Connect( pBundle, 4 );
		dopCaptureCaptureLight_C.Connect( pBundle, 5 );
		dopRingForwardPositionLight_A.Connect( pBundle, 6 );
		dopRingForwardPositionLight_C.Connect( pBundle, 7 );
		dopReadyToHookLight_A.Connect( pBundle, 8 );
		dopReadyToHookLight_C.Connect( pBundle, 9 );
		dopInterfSealedLight_A.Connect( pBundle, 10 );
		dopInterfSealedLight_C.Connect( pBundle, 11 );
		dopHooks1ClosedLight_A.Connect( pBundle, 12 );
		dopHooks1ClosedLight_C.Connect( pBundle, 13 );
		dopHooks2ClosedLight_A.Connect( pBundle, 14 );
		dopHooks2ClosedLight_C.Connect( pBundle, 15 );

		pBundle = BundleManager()->CreateBundle( "AVIONICS_TO_PANELA8A3_C", 16 );
		dopLatchesOpenLight_A.Connect( pBundle, 0 );
		dopLatchesOpenLight_C.Connect( pBundle, 1 );
		dopRingFinalPositionLight_A.Connect( pBundle, 2 );
		dopRingFinalPositionLight_C.Connect( pBundle, 3 );
		dopPyroCircuitProtectOffLight_A.Connect( pBundle, 4 );
		dopPyroCircuitProtectOffLight_C.Connect( pBundle, 5 );
		dopADSLight.Connect( pBundle, 6 );
		dopBDSLight.Connect( pBundle, 7 );
		dopCDSLight.Connect( pBundle, 8 );
		dopAPLight.Connect( pBundle, 9 );
		dopBPLight.Connect( pBundle, 10 );
		dopCPLight.Connect( pBundle, 11 );

		AddMesh();
		DefineAnimations();

		{
			camera->DefineAnimations( 0.0, 90.0 );

			VideoControlUnit* pVCU = static_cast<VideoControlUnit*>(director->GetSubsystemByName( "VideoControlUnit" ));
			pVCU->AddCamera( camera, IN_PL2 );
			pBundle = STS()->BundleManager()->CreateBundle( "ODS_INTERNAL", 16 );
			camera->ConnectPowerCameraPTU( pBundle, 0 );
			//camera->ConnectPowerHeater( pBundle, 1 );
			camera->ConnectPowerOnOff( pBundle, 2 );
			DiscOutPort camerapower[3];// HACK no control panel yet, so have camera always powered on 
			camerapower[0].Connect( pBundle, 0 );
			camerapower[0].SetLine();
			/*camerapower[1].Connect( pBundle, 1 );
			camerapower[1].SetLine();*/
			camerapower[2].Connect( pBundle, 2 );
			camerapower[2].SetLine();
		}

		STS()->SetAnimation(anim_ring, RingState.pos);

		CalculateRodAnimation();

		pBundle = BundleManager()->CreateBundle( "ODS_LIGHTS", 16 );
		vestibule_lights[0]->DefineState( 1, 0.5f, 0.0f, 1.0f, pBundle, 2 );
		vestibule_lights[0]->DefineMeshGroup( mesh_ods, GRP_CL_VESTIBULE_PORT_LIGHT_ODS );
		vestibule_lights[1]->DefineState( 1, 0.5f, 0.0f, 1.0f, pBundle, 3 );
		vestibule_lights[1]->DefineMeshGroup( mesh_ods, GRP_CL_VESTIBULE_STBD_LIGHT_ODS );
		return;
	}

	void ODS::OnSaveState( FILEHANDLE scn ) const
	{
		char cbuf[256];

		WriteScenario_state( scn, "RING_STATE", RingState );
		camera->SaveState( cbuf );
		oapiWriteScenario_string( scn, "CL_CAM", cbuf );

		return ExtAirlock::OnSaveState( scn );
	}

	bool ODS::OnParseLine( const char* keyword, const char* line )
	{
		if (!_strnicmp( keyword, "RING_STATE", 10 ))
		{
			sscan_state( (char*)line, RingState );
			return true;
		}
		else if (!_strnicmp( keyword, "CL_CAM", 6 ))
		{
			camera->LoadState( line );
		}
		return false;
	}

	void ODS::DefineAnimations( void )
	{
		anim_ring = STS()->CreateAnimation(0.0);

		static UINT grps_ring[2] = {GRP_DOCKING_RING_ODS, GRP_CROSS_HAIR_ODS};
		MGROUP_TRANSLATE* pRingAnim = new MGROUP_TRANSLATE(mesh_ods, grps_ring, 2, RING_TRANSLATION);
		ANIMATIONCOMPONENT_HANDLE parent = STS()->AddAnimationComponent(anim_ring, 0.0, 1.0, pRingAnim);
		SaveAnimation( pRingAnim );

		MGROUP_TRANSLATE* pRingAnimV = new MGROUP_TRANSLATE(LOCALVERTEXLIST, MAKEGROUPARRAY(odsAttachVec), 3, _V(0.0, 0.5446, 0.0));
		STS()->AddAnimationComponent(anim_ring, 0.0, 1.0, pRingAnimV);
		SaveAnimation( pRingAnimV );

		static UINT grps_coil[3] = {GRP_PETAL1_CABLE_COIL_ODS, GRP_PETAL2_CABLE_COIL_ODS, GRP_PETAL3_CABLE_COIL_ODS};
		MGROUP_SCALE* pCoilAnim = new MGROUP_SCALE( mesh_ods, grps_coil, 3, CABLE_COIL_BOTTOM_POS, CABLE_COIL_SCALE );
		STS()->AddAnimationComponent(anim_ring, 0.0, 1.0, pCoilAnim);
		SaveAnimation( pCoilAnim );


		anim_rods = STS()->CreateAnimation(0.0);

		//Counterclockwise actuator of pair 1
		MGROUP_ROTATE* pRod1LAnim[2];
		static UINT grps_rod1l0[1] = {GRP_PETAL1_LEFTACTUATOR_ROD_ODS};
		pRod1LAnim[0] = new MGROUP_ROTATE(mesh_ods, grps_rod1l0, 1, ROD1L_REF, ROD1L_DIR, ROD_ROTATION);
		STS()->AddAnimationComponent(anim_rods, 0.0, 1.0, pRod1LAnim[0], parent);
		SaveAnimation( pRod1LAnim[0] );
		static UINT grps_rod1l1[1] = {GRP_PETAL1_LEFTACTUATOR_ODS};
		pRod1LAnim[1] = new MGROUP_ROTATE(mesh_ods, grps_rod1l1, 1, ROD1L_ACT_REF, ROD1L_ACT_DIR, ROD_ROTATION);
		STS()->AddAnimationComponent(anim_rods, 0.0, 1.0, pRod1LAnim[1]);
		SaveAnimation( pRod1LAnim[1] );

		//Clockwise actuator of pair 1
		MGROUP_ROTATE* pRod1RAnim[2];
		static UINT grps_rod1r0[1] = {GRP_PETAL1_RIGHTACTUATOR_ROD_ODS};
		pRod1RAnim[0] = new MGROUP_ROTATE(mesh_ods, grps_rod1r0, 1, ROD1R_REF, ROD1R_DIR, ROD_ROTATION);
		STS()->AddAnimationComponent(anim_rods, 0.0, 1.0, pRod1RAnim[0], parent);
		SaveAnimation( pRod1RAnim[0] );
		static UINT grps_rod1r1[1] = {GRP_PETAL1_RIGHTACTUATOR_ODS};
		pRod1RAnim[1] = new MGROUP_ROTATE(mesh_ods, grps_rod1r1, 1, ROD1R_ACT_REF, ROD1R_ACT_DIR, ROD_ROTATION);
		STS()->AddAnimationComponent(anim_rods, 0.0, 1.0, pRod1RAnim[1]);
		SaveAnimation( pRod1RAnim[1] );

		//Counterclockwise actuator of pair 2
		MGROUP_ROTATE* pRod2LAnim[2];
		static UINT grps_rod2l0[1] = {GRP_PETAL2_LEFTACTUATOR_ROD_ODS};
		pRod2LAnim[0] = new MGROUP_ROTATE(mesh_ods, grps_rod2l0, 1, ROD2L_REF, ROD2L_DIR, ROD_ROTATION);
		STS()->AddAnimationComponent(anim_rods, 0.0, 1.0, pRod2LAnim[0], parent);
		SaveAnimation( pRod2LAnim[0] );
		static UINT grps_rod2l1[1] = {GRP_PETAL2_LEFTACTUATOR_ODS};
		pRod2LAnim[1] = new MGROUP_ROTATE(mesh_ods, grps_rod2l1, 1, ROD2L_ACT_REF, ROD2L_ACT_DIR, ROD_ROTATION);
		STS()->AddAnimationComponent(anim_rods, 0.0, 1.0, pRod2LAnim[1]);
		SaveAnimation( pRod2LAnim[1] );

		//Clockwise actuator of pair 2
		MGROUP_ROTATE* pRod2RAnim[2];
		static UINT grps_rod2r0[1] = {GRP_PETAL2_RIGHTACTUATOR_ROD_ODS};
		pRod2RAnim[0] = new MGROUP_ROTATE(mesh_ods, grps_rod2r0, 1, ROD2R_REF, ROD2R_DIR, ROD_ROTATION);
		STS()->AddAnimationComponent(anim_rods, 0.0, 1.0, pRod2RAnim[0], parent);
		SaveAnimation( pRod2RAnim[0] );
		static UINT grps_rod2r1[1] = {GRP_PETAL2_RIGHTACTUATOR_ODS};
		pRod2RAnim[1] = new MGROUP_ROTATE(mesh_ods, grps_rod2r1, 1, ROD2R_ACT_REF, ROD2R_ACT_DIR, ROD_ROTATION);
		STS()->AddAnimationComponent(anim_rods, 0.0, 1.0, pRod2RAnim[1]);
		SaveAnimation( pRod2RAnim[1] );

		//Counterclockwise actuator of pair 3
		MGROUP_ROTATE* pRod3LAnim[2];
		static UINT grps_rod3l0[1] = {GRP_PETAL3_LEFTACTUATOR_ROD_ODS};
		pRod3LAnim[0] = new MGROUP_ROTATE(mesh_ods, grps_rod3l0, 1, ROD3L_REF, ROD3L_DIR, ROD_ROTATION);
		STS()->AddAnimationComponent(anim_rods, 0.0, 1.0, pRod3LAnim[0], parent);
		SaveAnimation( pRod3LAnim[0] );
		static UINT grps_rod3l1[1] = {GRP_PETAL3_LEFTACTUATOR_ODS};
		pRod3LAnim[1] = new MGROUP_ROTATE(mesh_ods, grps_rod3l1, 1, ROD3L_ACT_REF, ROD3L_ACT_DIR, ROD_ROTATION);
		STS()->AddAnimationComponent(anim_rods, 0.0, 1.0, pRod3LAnim[1]);
		SaveAnimation( pRod3LAnim[1] );

		//Clockwise actuator of pair 3
		MGROUP_ROTATE* pRod3RAnim[2];
		static UINT grps_rod3r0[1] = {GRP_PETAL3_RIGHTACTUATOR_ROD_ODS};
		pRod3RAnim[0] = new MGROUP_ROTATE(mesh_ods, grps_rod3r0, 1, ROD3R_REF, ROD3R_DIR, ROD_ROTATION);
		STS()->AddAnimationComponent(anim_rods, 0.0, 1.0, pRod3RAnim[0], parent);
		SaveAnimation( pRod3RAnim[0] );
		static UINT grps_rod3r1[1] = {GRP_PETAL3_RIGHTACTUATOR_ODS};
		pRod3RAnim[1] = new MGROUP_ROTATE(mesh_ods, grps_rod3r1, 1, ROD3R_ACT_REF, ROD3R_ACT_DIR, ROD_ROTATION);
		STS()->AddAnimationComponent(anim_rods, 0.0, 1.0, pRod3RAnim[1]);
		SaveAnimation( pRod3RAnim[1] );


		MGROUP_ROTATE* pHooksAnim[12];
		anim_hooks1 = STS()->CreateAnimation( 0.0 );
		static UINT grps_hook_1[1] = {GRP_ACTIVE_HOOK_1_ODS};
		pHooksAnim[0] = new MGROUP_ROTATE( mesh_ods, grps_hook_1, 1, HOOK_1_REF, HOOK_1_DIR, HOOK_ROTATION );
		STS()->AddAnimationComponent( anim_hooks1, 0.0, 1.0, pHooksAnim[0] );
		SaveAnimation( pHooksAnim[0] );

		static UINT grps_hook_3[1] = {GRP_ACTIVE_HOOK_3_ODS};
		pHooksAnim[2] = new MGROUP_ROTATE( mesh_ods, grps_hook_3, 1, HOOK_3_REF, HOOK_3_DIR, HOOK_ROTATION );
		STS()->AddAnimationComponent( anim_hooks1, 0.0, 1.0, pHooksAnim[2] );
		SaveAnimation( pHooksAnim[2] );

		static UINT grps_hook_5[1] = {GRP_ACTIVE_HOOK_5_ODS};
		pHooksAnim[4] = new MGROUP_ROTATE( mesh_ods, grps_hook_5, 1, HOOK_5_REF, HOOK_5_DIR, HOOK_ROTATION );
		STS()->AddAnimationComponent( anim_hooks1, 0.0, 1.0, pHooksAnim[4] );
		SaveAnimation( pHooksAnim[4] );

		static UINT grps_hook_7[1] = {GRP_ACTIVE_HOOK_7_ODS};
		pHooksAnim[6] = new MGROUP_ROTATE( mesh_ods, grps_hook_7, 1, HOOK_7_REF, HOOK_7_DIR, HOOK_ROTATION );
		STS()->AddAnimationComponent( anim_hooks1, 0.0, 1.0, pHooksAnim[6] );
		SaveAnimation( pHooksAnim[6] );

		static UINT grps_hook_9[1] = {GRP_ACTIVE_HOOK_9_ODS};
		pHooksAnim[8] = new MGROUP_ROTATE( mesh_ods, grps_hook_9, 1, HOOK_9_REF, HOOK_9_DIR, HOOK_ROTATION );
		STS()->AddAnimationComponent( anim_hooks1, 0.0, 1.0, pHooksAnim[8] );
		SaveAnimation( pHooksAnim[8] );

		static UINT grps_hook_11[1] = {GRP_ACTIVE_HOOK_11_ODS};
		pHooksAnim[10] = new MGROUP_ROTATE( mesh_ods, grps_hook_11, 1, HOOK_11_REF, HOOK_11_DIR, HOOK_ROTATION );
		STS()->AddAnimationComponent( anim_hooks1, 0.0, 1.0, pHooksAnim[10] );
		SaveAnimation( pHooksAnim[10] );


		anim_hooks2 = STS()->CreateAnimation( 0.0 );
		static UINT grps_hook_2[1] = {GRP_ACTIVE_HOOK_2_ODS};
		pHooksAnim[1] = new MGROUP_ROTATE( mesh_ods, grps_hook_2, 1, HOOK_2_REF, HOOK_2_DIR, HOOK_ROTATION );
		STS()->AddAnimationComponent( anim_hooks2, 0.0, 1.0, pHooksAnim[1] );
		SaveAnimation( pHooksAnim[1] );

		static UINT grps_hook_4[1] = {GRP_ACTIVE_HOOK_4_ODS};
		pHooksAnim[3] = new MGROUP_ROTATE( mesh_ods, grps_hook_4, 1, HOOK_4_REF, HOOK_4_DIR, HOOK_ROTATION );
		STS()->AddAnimationComponent( anim_hooks2, 0.0, 1.0, pHooksAnim[3] );
		SaveAnimation( pHooksAnim[3] );

		static UINT grps_hook_6[1] = {GRP_ACTIVE_HOOK_6_ODS};
		pHooksAnim[5] = new MGROUP_ROTATE( mesh_ods, grps_hook_6, 1, HOOK_6_REF, HOOK_6_DIR, HOOK_ROTATION );
		STS()->AddAnimationComponent( anim_hooks2, 0.0, 1.0, pHooksAnim[5] );
		SaveAnimation( pHooksAnim[5] );

		static UINT grps_hook_8[1] = {GRP_ACTIVE_HOOK_8_ODS};
		pHooksAnim[7] = new MGROUP_ROTATE( mesh_ods, grps_hook_8, 1, HOOK_8_REF, HOOK_8_DIR, HOOK_ROTATION );
		STS()->AddAnimationComponent( anim_hooks2, 0.0, 1.0, pHooksAnim[7] );
		SaveAnimation( pHooksAnim[7] );

		static UINT grps_hook_10[1] = {GRP_ACTIVE_HOOK_10_ODS};
		pHooksAnim[9] = new MGROUP_ROTATE( mesh_ods, grps_hook_10, 1, HOOK_10_REF, HOOK_10_DIR, HOOK_ROTATION );
		STS()->AddAnimationComponent( anim_hooks2, 0.0, 1.0, pHooksAnim[9] );
		SaveAnimation( pHooksAnim[9] );

		static UINT grps_hook_12[1] = {GRP_ACTIVE_HOOK_12_ODS};
		pHooksAnim[11] = new MGROUP_ROTATE( mesh_ods, grps_hook_12, 1, HOOK_12_REF, HOOK_12_DIR, HOOK_ROTATION );
		STS()->AddAnimationComponent( anim_hooks2, 0.0, 1.0, pHooksAnim[11] );
		SaveAnimation( pHooksAnim[11] );
		return;
	}

	bool ODS::HasDSCUPower() const {
		return bPowerRelay;
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
		VECTOR3 pos = aft ? MESH_AFT_OFFSET : MESH_OFFSET;
		mesh_ods = STS()->AddMesh( hODSMesh, &pos );
		STS()->SetMeshVisibilityMode( mesh_ods, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
		oapiWriteLog( "(SSV_OV) [INFO] ODS mesh added" );
		return;
	}

	void ODS::SetDockParams( void )
	{
		VECTOR3 DockPos = DOCKPOS_OFFSET + (aft ? MESH_AFT_OFFSET : MESH_OFFSET);
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

/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/05/06   GLS
2020/05/10   GLS
2020/05/14   GLS
2020/06/20   GLS
2020/06/26   GLS
2020/06/28   GLS
2020/07/30   GLS
2020/08/19   GLS
2020/08/23   GLS
2020/08/24   GLS
2020/08/27   GLS
2020/09/01   GLS
2020/09/04   GLS
2020/09/12   GLS
2020/09/20   GLS
2021/01/20   GLS
2021/06/06   GLS
2021/06/30   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/21   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/01/10   GLS
2022/01/15   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/20   GLS
2022/05/07   GLS
2022/08/05   GLS
2022/08/17   GLS
2022/10/30   GLS
2022/11/01   GLS
2022/11/09   GLS
********************************************/
#include "ActiveLatchGroup.h"
#include "Atlantis.h"
#include "ParameterValues.h"
#include <MathSSV.h>


constexpr int PLID_AKA_base = 154;// PLID of base index
constexpr bool PLID_AKA_FWD[] = {// true if AKA is fwd version
	/*154-155*/false, false,
	/*bay  1: 156-157*/false, false,
	/*158-165*/false, false, false, false, false, false, false, false,
	/*bay  2: 166-172*/true, true, true, false, false, false, false,
	/*173-179*/false, false, false, false, false, false, false,
	/*bay  3: 180-186*/true, true, true, true, false, false, false,
	/*187-194*/false, false, false, false, false, false, false, false,
	/*bay  4: 195-201*/true, true, true, false, false, false, false,
	/*202-208*/false, false, false, false, false, false, false,
	/*bay  5: 209-215*/true, true, true, false, false, false, false,
	/*216-222*/false, false, false, false, false, false, false,
	/*bay  6: 223-229*/true, true, true, true, false, false, false,
	/*230-237*/false, false, false, false, false, false, false, false,
	/*bay  7: 238-244*/true, true, true, false, false, false, false,
	/*245-252*/false, false, false, false, false, false, false, false,
	/*bay  8: 253-260*/true, true, true, true, false, false, false, false,
	/*261-267*/false, false, false, false, false, false, false,
	/*bay  9: 268-273*/true, true, true, false, false, false,
	/*274-280*/false, false, false, false, false, false, false,
	/*bay 10: 281-285*/true, true, true, false, false,
	/*286-293*/false, false, false, false, false, false, false, false,
	/*bay 11: 294-298*/true, true, false, false, false,
	/*299-305*/false, false, false, false, false, false, false,
	/*bay 12: 306-311*/true, true, true, false, false, false,
	/*312-330*/false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false
};
constexpr bool PLID_AKA_onesided[] = {// true if AKA is one sided version
	/*154-155*/false, false,
	/*bay  1: 156-157*/false, false,
	/*158-165*/false, false, false, false, false, false, false, false,
	/*bay  2: 166-172*/false, false, false, false, false, false, true,
	/*173-179*/false, false, false, false, false, false, false,
	/*bay  3: 180-186*/true, false, false, false, false, false, false,
	/*187-194*/false, false, false, false, false, false, false, false,
	/*bay  4: 195-201*/false, false, false, false, false, false, true,
	/*202-208*/false, false, false, false, false, false, false,
	/*bay  5: 209-215*/true, false, false, false, false, false, false,
	/*216-222*/false, false, false, false, false, false, false,
	/*bay  6: 223-229*/true, true, false, false, false, false, false,
	/*230-237*/false, false, false, false, false, false, false, false,
	/*bay  7: 238-244*/false, false, false, false, false, false, false,
	/*245-252*/false, false, false, false, false, false, false, false,
	/*bay  8: 253-260*/false, false, false, false, false, false, false, false,
	/*261-267*/false, false, false, false, false, false, false,
	/*bay  9: 268-273*/true, false, false, false, false, true,
	/*274-280*/false, false, false, false, false, false, false,
	/*bay 10: 281-285*/true, false, false, false, false,
	/*286-293*/false, false, false, false, false, false, false, false,
	/*bay 11: 294-298*/false, false, false, false, false,
	/*299-305*/false, false, false, false, false, false, false,
	/*bay 12: 306-311*/false, false, false, false, false, false,
	/*312-330*/false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false
};

const static char* MESHNAME_PRLA_PORT_ACTIVE = "SSV\\OV\\PRLA_Port_Active";
const static char* MESHNAME_PRLA_STBD_ACTIVE = "SSV\\OV\\PRLA_Starboard_Active";
const static char* MESHNAME_PRLA_GUIDE_PORT_22 = "SSV\\OV\\PRLA_Guide_Port_22";
const static char* MESHNAME_PRLA_GUIDE_PORT_24 = "SSV\\OV\\PRLA_Guide_Port_24";
const static char* MESHNAME_PRLA_GUIDE_STBD_22 = "SSV\\OV\\PRLA_Guide_Starboard_22";
const static char* MESHNAME_PRLA_GUIDE_STBD_24 = "SSV\\OV\\PRLA_Guide_Starboard_24";
const static char* MESHNAME_AKA_FWD = "SSV\\OV\\AKA_Forward";
const static char* MESHNAME_AKA_AFT = "SSV\\OV\\AKA_Aft";

const VECTOR3 ACTIVE_CL_FWD_POS = _V( 0.0, -2.839465, 0.0 );// Yo0.0, Zo+305.025 (fwd of 1191.0)
const VECTOR3 ACTIVE_CL_AFT_POS = _V( 0.0, -2.75374, 0.0 );// Yo0.0, Zo+308.40 (aft of 1191.0)
const VECTOR3 ACTIVE_PORT_POS = _V( -2.385695, -0.07023, 0.0 );// Yo-93.925, Zo+414.05
const VECTOR3 ACTIVE_STBD_POS = _V( 2.385695, -0.07023, 0.0 );// Yo+93.925, Zo+414.05
const VECTOR3 ACTIVE_DIR = _V( 0.0, 1.0, 0.0 );
const VECTOR3 ACTIVE_ROT = _V( 0.0, 0.0, 1.0 );

const VECTOR3 PRLA_HOOK_HINGE_POS = _V( 0.0, -0.0715, -0.086696 );
const VECTOR3 PRLA_HOOK_HINGE_DIR = _V( -1.0, 0.0, 0.0 );
const double PRLA_HOOK_HINGE_ANG = 90.0 * RAD;

const VECTOR3 AKA_FWD_DYNAMIC_LATCH_OPEN_TRANSLATION = _V( 0.0, 0.0, -0.1143 );
const VECTOR3 AKA_FWD_STATIC_LATCH_OPEN_TRANSLATION = _V( 0.0, 0.0, 0.1143 );
const VECTOR3 AKA_AFT_DYNAMIC_LATCH_OPEN_TRANSLATION = _V( 0.0, 0.0, 0.1143 );
const VECTOR3 AKA_AFT_STATIC_LATCH_OPEN_TRANSLATION = _V( 0.0, 0.0, -0.1143 );

constexpr double MAX_LATCHING_DIST = 0.05;// [m] max distance between (main) latch and PL attach point for successful latching
const double MAX_LATCHING_ANGLE = 1.0 * RAD;// [rad] max angle between PL and PLB for successful latching


ActiveLatchGroup::ActiveLatchGroup( AtlantisSubsystemDirector *_director, const std::string &_ident, unsigned short id, const struct mission::MissionPayloads& payloads )
	: LatchSystem( _director, _ident, "XS", MAX_LATCHING_DIST, MAX_LATCHING_ANGLE ), id(id), payloads(payloads)
{
	for (unsigned short i = 0; i < 12; i++)
	{
		LatchInstalled[i] = false;
		LatchState[i] = 1.0;
	}

	attachpos = ACTIVE_CL_FWD_POS;// default

	SetSearchForAttachments( true );// search for attachments to feed RFL
}

ActiveLatchGroup::~ActiveLatchGroup()
{
}

void ActiveLatchGroup::Realize( void )
{
	LatchSystem::Realize();

	LoadPayload();

	for (int i = 0; i < 12; i++)
	{
		if (LatchInstalled[i])
		{
			string str = "PL_" + std::to_string( PL_Sys[i] ) + "_SEL_LATCH_" + std::to_string( PL_Latch[i] );
			DiscreteBundle* pBundle = BundleManager()->CreateBundle( str, 10 );
			LAT_A[i].Connect( pBundle, 0 );
			REL_A[i].Connect( pBundle, 1 );
			RDY_A[i].Connect( pBundle, 2 );
			MOTOR_1_PWR[i].Connect( pBundle, 3 );
			IND_A[i].Connect( pBundle, 4 );
			LAT_B[i].Connect( pBundle, 5 );
			REL_B[i].Connect( pBundle, 6 );
			RDY_B[i].Connect( pBundle, 7 );
			MOTOR_2_PWR[i].Connect( pBundle, 8 );
			IND_B[i].Connect( pBundle, 9 );
		}
	}
	return;
}

void ActiveLatchGroup::OnPreStep( double simt, double simdt, double mjd )
{
	LatchSystem::OnPreStep( simt, simdt, mjd );

	bool rdy = CheckRFL();

	// run latches
	for (unsigned short i = 0; i < 12; i++)
	{
		if (LatchInstalled[i])
		{
			LatchState[i] = range( 0.0, LatchState[i] + (simdt * LATCH_OPERATION_SPEED * (MOTOR_1_PWR[i].GetVoltage() + MOTOR_2_PWR[i].GetVoltage())), 1.0 );

			// animation
			STS()->SetAnimation( animActiveLatch[i], LatchState[i] );

			// indications
			if (IND_A[i])
			{
				if (LatchState[i] == 0.0)
				{
					LAT_A[i].SetLine();
					REL_A[i].ResetLine();
				}
				else if (LatchState[i] == 1.0)
				{
					LAT_A[i].ResetLine();
					REL_A[i].SetLine();
				}
				else
				{
					LAT_A[i].ResetLine();
					REL_A[i].ResetLine();
				}

				if (rdy) RDY_A[i].SetLine();
				else RDY_A[i].ResetLine();
			}
			else
			{
				LAT_A[i].ResetLine();
				REL_A[i].ResetLine();
				RDY_A[i].ResetLine();
			}

			if (IND_B[i])
			{
				if (LatchState[i] == 0.0)
				{
					LAT_B[i].SetLine();
					REL_B[i].ResetLine();
				}
				else if (LatchState[i] == 1.0)
				{
					LAT_B[i].ResetLine();
					REL_B[i].SetLine();
				}
				else
				{
					LAT_B[i].ResetLine();
					REL_B[i].ResetLine();
				}

				if (rdy) RDY_B[i].SetLine();
				else RDY_B[i].ResetLine();
			}
			else
			{
				LAT_B[i].ResetLine();
				REL_B[i].ResetLine();
				RDY_B[i].ResetLine();
			}
		}
	}

	// handle attachment
	if (IsLatched())
	{
		// check for release
		if (AllLatchesOpen()) DetachPayload();
	}
	else
	{
		// check for latch
		if (!AllLatchesOpen()) AttachPayload();
	}
	return;
}

bool ActiveLatchGroup::OnParseLine( const char* line )
{
	if (LatchSystem::OnParseLine( line )) return true;
	else
	{
		if (!_strnicmp( line, "LATCH_STATE_", 12 ))
		{
			char num[3];
			num[0] = line[12];
			num[1] = line[13];
			num[2] = '\0';
			int index = atoi( num );

			if ((index >= 1) && (index <= 12))
			{
				// HACK accept latch position without checking if it is actually used (latch loading only happens after this)
				//if (LatchInstalled[index - 1])
				//{
					sscanf_s( line + 14, "%lf", &LatchState[index - 1] );
					LatchState[index - 1] = range( 0.0, LatchState[index - 1], 1.0 );
					//STS()->SetAnimation( animActiveLatch[index - 1], LatchState[index - 1] );
					return true;
				//}
				//else oapiWriteLogV( "(SSV_OV) [ERROR] Latch %d not installed in %s", index, GetIdentifier().c_str() );
			}
			else oapiWriteLogV( "(SSV_OV) [ERROR] Invalid latch %d in %s", index, GetIdentifier().c_str() );
		}
	}
	return false;
}

void ActiveLatchGroup::OnSaveState( FILEHANDLE scn ) const
{
	LatchSystem::OnSaveState( scn );

	char cbuf[16];
	for (unsigned int i = 0; i < 12; i++)
	{
		if (LatchInstalled[i])
		{
			sprintf_s( cbuf, 16, "LATCH_STATE_%d", i + 1 );
			oapiWriteScenario_float( scn, cbuf, LatchState[i] );
		}
	}
	return;
}

void ActiveLatchGroup::CreateAttachment( void )
{
	if (!hAttach) hAttach=STS()->CreateAttachment( false, STS()->GetOrbiterCoGOffset() + attachpos, ACTIVE_DIR, ACTIVE_ROT, "SSV_XS" );
	else STS()->SetAttachmentParams( hAttach, STS()->GetOrbiterCoGOffset() + attachpos, ACTIVE_DIR, ACTIVE_ROT );
	return;
}

void ActiveLatchGroup::OnAttach( void )
{
	if (IsFirstStep() && AllLatchesOpen())
	{
		// if scn file says we are attached and latches are open, set all latch states to LATCHED
		for (unsigned short i = 0; i < 12; i++)
		{
			if (LatchInstalled[i])
			{
				LatchState[i] = 0.0;
				STS()->SetAnimation( animActiveLatch[i], LatchState[i] );
			}
		}
	}

	oapiWriteLogV( "(SSV_OV) [INFO] %s latched", GetIdentifier().c_str() );
	return;
}

void ActiveLatchGroup::OnDetach( void )
{
	oapiWriteLogV( "(SSV_OV) [INFO] %s released", GetIdentifier().c_str() );
	return;
}

bool ActiveLatchGroup::CheckRFL( void ) const
{
	// if PL is latched, RFL switches should be set
	if (IsLatched()) return true;

	return (FindAttachment() != -1);
}

bool ActiveLatchGroup::AllLatchesOpen( void ) const
{
	for (unsigned short j = 0; j < 12; j++)
	{
		if (LatchInstalled[j] && (LatchState[j] <= 0.5)) return false;
	}
	return true;
}

void ActiveLatchGroup::LoadPayload( void )
{
	UINT mesh_idx;

	// port longeron
	for (int j = 0; j < 4; j++)
	{
		if (payloads.active[id].PLID[j] != 0)
		{
			// find PRLA Xo position
			double Xo = PLID_Xo[payloads.active[id].PLID[j] - PLID_Xo_base];
			if (Xo > 0.0)
			{
				// convert to z position
				VECTOR3 pos = _V( 0.0, 0.0, 24.239 - (Xo * IN2M) );

				// add PRLA mesh instance
				mesh_idx = STS()->AddMesh( payloads.active[id].Reversed[j] ? MESHNAME_PRLA_STBD_ACTIVE : MESHNAME_PRLA_PORT_ACTIVE, &pos );
				STS()->SetMeshVisibilityMode( mesh_idx, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

				// add PRLA animation (for positioning)
				ANIMATIONCOMPONENT_HANDLE parent = NULL;
				if (payloads.active[id].Reversed[j])
				{
					static UINT PRLA_Grp = {1};
					MGROUP_ROTATE* PRLA = new MGROUP_ROTATE( mesh_idx, &PRLA_Grp, 1, _V( 0.0, 0.0, 0.0 ), _V( 0.0, 1.0, 0.0 ), static_cast<float>(PI) );
					UINT animPRLA = STS()->CreateAnimation( 0.0 );
					STS()->SetAnimation( animPRLA, 1.0 );
					parent = STS()->AddAnimationComponent( animPRLA, 0.0, 1.0, PRLA );
					SaveAnimation( PRLA );
				}
				// add PRLA hook animation
				static UINT Hook_Grp = {0};
				MGROUP_ROTATE* PRLAHook = new MGROUP_ROTATE( mesh_idx, &Hook_Grp, 1, PRLA_HOOK_HINGE_POS, PRLA_HOOK_HINGE_DIR, static_cast<float>(PRLA_HOOK_HINGE_ANG) );
				animActiveLatch[j] = STS()->CreateAnimation( 0.0 );// closed position
				STS()->SetAnimation( animActiveLatch[j], LatchState[j] );// loaded position from scenario
				STS()->AddAnimationComponent( animActiveLatch[j], 0.0, 1.0, PRLAHook, parent );
				SaveAnimation( PRLAHook );

				// fwd guide
				if (payloads.active[id].FwdGuide[j] != 0)
				{
					// add mesh instance
					mesh_idx = STS()->AddMesh( (payloads.active[id].FwdGuide[j] == 1) ? MESHNAME_PRLA_GUIDE_PORT_22 : MESHNAME_PRLA_GUIDE_PORT_24, &pos );
					STS()->SetMeshVisibilityMode( mesh_idx, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
				}

				// aft guide
				if (payloads.active[id].AftGuide[j] != 0)
				{
					// add mesh instance
					mesh_idx = STS()->AddMesh( (payloads.active[id].AftGuide[j] == 1) ? MESHNAME_PRLA_GUIDE_STBD_22 : MESHNAME_PRLA_GUIDE_STBD_24, &pos );
					STS()->SetMeshVisibilityMode( mesh_idx, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

					// add PRLA guide animation
					static UINT AftGuide_Grp = {0};
					MGROUP_ROTATE* PRLAAFTGUIDE = new MGROUP_ROTATE( mesh_idx, &AftGuide_Grp, 1, _V( 0.0, 0.0, 0.0 ), _V( 0.0, 1.0, 0.0 ), static_cast<float>(PI) );
					UINT animAftGuide = STS()->CreateAnimation( 0.0 );
					STS()->SetAnimation( animAftGuide, 1.0 );
					STS()->AddAnimationComponent( animAftGuide, 0.0, 1.0, PRLAAFTGUIDE );
					SaveAnimation( PRLAAFTGUIDE );
				}

				// set attachment location
				if (payloads.active[id].IsAttachment[j])
					attachpos = ACTIVE_PORT_POS + pos;

				// save connection info
				LatchInstalled[j] = true;
				PL_Sys[j] = payloads.active[id].Latches[j].PL;
				PL_Latch[j] = payloads.active[id].Latches[j].Latch;
			}
			else oapiWriteLogV( "(SSV_OV) [ERROR] Invalid PLID %d in Active: %d %d", payloads.active[id].PLID[j], id, j );
		}
	}

	// starboard longeron
	for (int j = 4; j < 8; j++)
	{
		if (payloads.active[id].PLID[j] != 0)
		{
			// find PRLA Xo position
			double Xo = PLID_Xo[payloads.active[id].PLID[j] - PLID_Xo_base];
			if (Xo > 0.0)
			{
				// convert to z position
				VECTOR3 pos = _V( 0.0, 0.0, 24.239 - (Xo * IN2M) );

				// add PRLA mesh instance
				mesh_idx = STS()->AddMesh( payloads.active[id].Reversed[j] ? MESHNAME_PRLA_PORT_ACTIVE : MESHNAME_PRLA_STBD_ACTIVE, &pos );
				STS()->SetMeshVisibilityMode( mesh_idx, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

				// add PRLA animation (for positioning)
				ANIMATIONCOMPONENT_HANDLE parent = NULL;
				if (payloads.active[id].Reversed[j])
				{
					static UINT PRLA_Grp = {1};
					MGROUP_ROTATE* PRLA = new MGROUP_ROTATE( mesh_idx, &PRLA_Grp, 1, _V( 0.0, 0.0, 0.0 ), _V( 0.0, 1.0, 0.0 ), static_cast<float>(PI) );
					UINT animPRLA = STS()->CreateAnimation( 0.0 );
					STS()->SetAnimation( animPRLA, 1.0 );
					parent = STS()->AddAnimationComponent( animPRLA, 0.0, 1.0, PRLA );
					SaveAnimation( PRLA );
				}
				// add PRLA hook animation
				static UINT Hook_Grp = {0};
				MGROUP_ROTATE* PRLAHook = new MGROUP_ROTATE( mesh_idx, &Hook_Grp, 1, PRLA_HOOK_HINGE_POS, PRLA_HOOK_HINGE_DIR, static_cast<float>(PRLA_HOOK_HINGE_ANG) );
				animActiveLatch[j] = STS()->CreateAnimation( 0.0 );// closed position
				STS()->SetAnimation( animActiveLatch[j], LatchState[j] );// loaded position from scenario
				STS()->AddAnimationComponent( animActiveLatch[j], 0.0, 1.0, PRLAHook, parent );
				SaveAnimation( PRLAHook );

				// fwd guide
				if (payloads.active[id].FwdGuide[j] != 0)
				{
					// add mesh instance
					mesh_idx = STS()->AddMesh( (payloads.active[id].FwdGuide[j] == 1) ? MESHNAME_PRLA_GUIDE_STBD_22 : MESHNAME_PRLA_GUIDE_STBD_24, &pos );
					STS()->SetMeshVisibilityMode( mesh_idx, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
				}

				// aft guide
				if (payloads.active[id].AftGuide[j] != 0)
				{
					// add mesh instance
					mesh_idx = STS()->AddMesh( (payloads.active[id].AftGuide[j] == 1) ? MESHNAME_PRLA_GUIDE_PORT_22 : MESHNAME_PRLA_GUIDE_PORT_24, &pos );
					STS()->SetMeshVisibilityMode( mesh_idx, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

					// add PRLA guide animation
					static UINT AftGuide_Grp = {0};
					MGROUP_ROTATE* PRLAAFTGUIDE = new MGROUP_ROTATE( mesh_idx, &AftGuide_Grp, 1, _V( 0.0, 0.0, 0.0 ), _V( 0.0, 1.0, 0.0 ), static_cast<float>(PI) );
					UINT animAftGuide = STS()->CreateAnimation( 0.0 );
					STS()->SetAnimation( animAftGuide, 1.0 );
					STS()->AddAnimationComponent( animAftGuide, 0.0, 1.0, PRLAAFTGUIDE );
					SaveAnimation( PRLAAFTGUIDE );
				}

				// set attachment location
				if (payloads.active[id].IsAttachment[j])
					attachpos = ACTIVE_STBD_POS + pos;

				// save connection info
				LatchInstalled[j] = true;
				PL_Sys[j] = payloads.active[id].Latches[j].PL;
				PL_Latch[j] = payloads.active[id].Latches[j].Latch;
			}
			else oapiWriteLogV( "(SSV_OV) [ERROR] Invalid PLID %d in Active: %d %d", payloads.active[id].PLID[j], id, j );
		}
	}

	// keel
	for (int j = 8; j < 12; j++)
	{
		if (payloads.active[id].PLID[j] != 0)
		{
			// find PRLA Xo position
			double Xo = PLID_Xo[payloads.active[id].PLID[j] - PLID_Xo_base];
			if (Xo > 0.0)
			{
				// convert to z position
				VECTOR3 pos = _V( 0.0, 0.0, 24.239 - (Xo * IN2M) );

				// handle bay 12 vertical offset
				VECTOR3 posmesh = _V( 0.0, (Xo < 1191.0) ? 0.0 : (ACTIVE_CL_AFT_POS.y - ACTIVE_CL_FWD_POS.y), pos.z );

				// mesh instance
				bool fwd = PLID_AKA_FWD[payloads.active[id].PLID[j] - PLID_Xo_base];
				mesh_idx = STS()->AddMesh( fwd ? MESHNAME_AKA_FWD : MESHNAME_AKA_AFT, &posmesh );
				STS()->SetMeshVisibilityMode( mesh_idx, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

				// add animation
				bool onesided = PLID_AKA_onesided[payloads.active[id].PLID[j] - PLID_Xo_base];
				static UINT AKADynamic_Grp = {0};
				static UINT AKAStatic_Grp = {1};
				MGROUP_TRANSLATE* AKADynamic = new MGROUP_TRANSLATE( mesh_idx, &AKADynamic_Grp, 1, (fwd ? AKA_FWD_DYNAMIC_LATCH_OPEN_TRANSLATION : AKA_AFT_DYNAMIC_LATCH_OPEN_TRANSLATION) * (onesided ? 2.0 : 1.0) );
				MGROUP_TRANSLATE* AKAStatic = new MGROUP_TRANSLATE( mesh_idx, &AKAStatic_Grp, 1, (fwd ? AKA_FWD_STATIC_LATCH_OPEN_TRANSLATION : AKA_AFT_STATIC_LATCH_OPEN_TRANSLATION) * (onesided ? 0.0 : 1.0) );
				animActiveLatch[j] = STS()->CreateAnimation( 0.0 );// closed position
				STS()->SetAnimation( animActiveLatch[j], LatchState[j] );// loaded position from scenario
				STS()->AddAnimationComponent( animActiveLatch[j], 0.0, 1.0, AKADynamic );
				STS()->AddAnimationComponent( animActiveLatch[j], 0.0, 1.0, AKAStatic );
				SaveAnimation( AKADynamic );
				SaveAnimation( AKAStatic );

				// set attachment location
				if (payloads.active[id].IsAttachment[j])
					attachpos = ((Xo < 1191.0) ? ACTIVE_CL_FWD_POS : ACTIVE_CL_AFT_POS) + pos;

				// save connection info
				LatchInstalled[j] = true;
				PL_Sys[j] = payloads.active[id].Latches[j].PL;
				PL_Latch[j] = payloads.active[id].Latches[j].Latch;
			}
			else oapiWriteLogV( "(SSV_OV) [ERROR] Invalid PLID %d in Active: %d %d", payloads.active[id].PLID[j], id, j );
		}
	}

	CreateAttachment();// need to call this again to update positions
	return;
}

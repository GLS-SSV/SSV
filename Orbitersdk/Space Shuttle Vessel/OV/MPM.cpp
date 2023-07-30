/******* SSV File Modification Notice *******
Date         Developer
2020/05/06   GLS
2020/05/14   GLS
2020/06/20   GLS
2020/06/28   GLS
2020/10/10   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/12/26   GLS
2022/05/15   GLS
2022/05/16   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/10/30   GLS
2022/11/01   GLS
2022/11/02   GLS
2022/11/07   GLS
2022/11/09   GLS
2022/11/12   GLS
2022/11/13   GLS
2022/11/14   GLS
2023/07/30   GLS
********************************************/
#include "MPM.h"
#include "Atlantis.h"
#include "../CommonDefs.h"
#include "meshres_MPM_Port.h"
#include "meshres_MPM_Starboard.h"
#include <MathSSV.h>


const static char* MESHNAME_MPM_PORT = "SSV\\MPM_Port";
const static char* MESHNAME_MPM_STBD = "SSV\\MPM_Starboard";


MPM::MPM( AtlantisSubsystemDirector *_director, const std::string &_ident, const string& _attachID, bool _portside, double latchmaxdistance, double latchmaxangle )
	: LatchSystem( _director, _ident, _attachID, latchmaxdistance, latchmaxangle ), MPM_Base( _portside ), mpm_moved(false), doubleAttached(false), PrevLatchState(false), Rollout(1.0)
{
	mesh_index_MPM = MESH_UNDEFINED;
	hMesh_MPM = oapiLoadMeshGlobal( _portside ? MESHNAME_MPM_PORT : MESHNAME_MPM_STBD );

	MRL[0] = 1.0;
	MRL[1] = 1.0;
	MRL[2] = 1.0;
}

MPM::~MPM()
{
}

void MPM::Realize()
{
	AddMesh();
	AddAnimation();

	DiscreteBundle* pBundle = BundleManager()->CreateBundle( portside ? "PORT_MPM_CTRL_1" : "STBD_MPM_CTRL_1", 16 );
	SHLD_MECH_STOW_IND_1.Connect( pBundle, 0 );
	SHLD_MECH_STOW_IND_1_TB.Connect( pBundle, 1 );
	FWD_MECH_STOW_IND_1_TB.Connect( pBundle, 2 );
	MID_MECH_STOW_IND_1_TB.Connect( pBundle, 3 );
	AFT_MECH_STOW_IND_1_TB.Connect( pBundle, 4 );
	SHLD_MECH_DEPLOY_IND_1.Connect( pBundle, 5 );
	SHLD_MECH_DEPLOY_IND_1_TB.Connect( pBundle, 6 );
	FWD_MECH_DEPLOY_IND_1_TB.Connect( pBundle, 7 );
	MID_MECH_DEPLOY_IND_1_TB.Connect( pBundle, 8 );
	AFT_MECH_DEPLOY_IND_1_TB.Connect( pBundle, 9 );
	MPM_MOTOR_1_PWR.Connect( pBundle, 10 );
	MPM_SHOULDER_1_IND_PWR.Connect( pBundle, 11 );
	MPM_FWD_1_IND_PWR.Connect( pBundle, 12 );
	MPM_MID_1_IND_PWR.Connect( pBundle, 13 );
	MPM_AFT_1_IND_PWR.Connect( pBundle, 14 );

	pBundle = BundleManager()->CreateBundle( portside ? "PORT_MPM_CTRL_2" : "STBD_MPM_CTRL_2", 16 );
	SHLD_MECH_STOW_IND_2.Connect( pBundle, 0 );
	SHLD_MECH_STOW_IND_2_TB.Connect( pBundle, 1 );
	FWD_MECH_STOW_IND_2_TB.Connect( pBundle, 2 );
	MID_MECH_STOW_IND_2_TB.Connect( pBundle, 3 );
	AFT_MECH_STOW_IND_2_TB.Connect( pBundle, 4 );
	SHLD_MECH_DEPLOY_IND_2.Connect( pBundle, 5 );
	SHLD_MECH_DEPLOY_IND_2_TB.Connect( pBundle, 6 );
	FWD_MECH_DEPLOY_IND_2_TB.Connect( pBundle, 7 );
	MID_MECH_DEPLOY_IND_2_TB.Connect( pBundle, 8 );
	AFT_MECH_DEPLOY_IND_2_TB.Connect( pBundle, 9 );
	MPM_MOTOR_2_PWR.Connect( pBundle, 10 );
	MPM_SHOULDER_2_IND_PWR.Connect( pBundle, 11 );
	MPM_FWD_2_IND_PWR.Connect( pBundle, 12 );
	MPM_MID_2_IND_PWR.Connect( pBundle, 13 );
	MPM_AFT_2_IND_PWR.Connect( pBundle, 14 );

	pBundle = BundleManager()->CreateBundle( portside ? "PORT_FWD_MRL_CTRL" : "STBD_FWD_MRL_CTRL", 16 );
	FWD_MRL_LATCH_IND_1.Connect( pBundle, 0 );
	FWD_MRL_RELEASE_IND_1.Connect( pBundle, 1 );
	FWD_MRL_MOTOR_1_PWR.Connect( pBundle, 2 );
	FWD_MRL_IND_1_PWR.Connect( pBundle, 3 );
	FWD_RETNN_RFL_1_PWR.Connect( pBundle, 4 );
	FWD_MRL_LATCH_IND_1_TB.Connect( pBundle, 5 );
	FWD_MRL_RELEASE_IND_1_TB.Connect( pBundle, 6 );
	FWD_RETNN_RFL_1_TB.Connect( pBundle, 7 );
	FWD_MRL_LATCH_IND_2.Connect( pBundle, 8 );
	FWD_MRL_RELEASE_IND_2.Connect( pBundle, 9 );
	FWD_MRL_MOTOR_2_PWR.Connect( pBundle, 10 );
	FWD_MRL_IND_2_PWR.Connect( pBundle, 11 );
	FWD_RETNN_RFL_2_PWR.Connect( pBundle, 12 );

	pBundle = BundleManager()->CreateBundle( portside ? "PORT_MID_MRL_CTRL" : "STBD_MID_MRL_CTRL", 16 );
	MID_MRL_LATCH_IND_1.Connect( pBundle, 0 );
	MID_MRL_RELEASE_IND_1.Connect( pBundle, 1 );
	MID_MRL_MOTOR_1_PWR.Connect( pBundle, 2 );
	MID_MRL_IND_1_PWR.Connect( pBundle, 3 );
	MID_RETNN_RFL_1_PWR.Connect( pBundle, 4 );
	MID_MRL_LATCH_IND_1_TB.Connect( pBundle, 5 );
	MID_MRL_RELEASE_IND_1_TB.Connect( pBundle, 6 );
	MID_RETNN_RFL_1_TB.Connect( pBundle, 7 );
	MID_MRL_LATCH_IND_2.Connect( pBundle, 8 );
	MID_MRL_RELEASE_IND_2.Connect( pBundle, 9 );
	MID_MRL_MOTOR_2_PWR.Connect( pBundle, 10 );
	MID_MRL_IND_2_PWR.Connect( pBundle, 11 );
	MID_RETNN_RFL_2_PWR.Connect( pBundle, 12 );

	pBundle = BundleManager()->CreateBundle( portside ? "PORT_AFT_MRL_CTRL" : "STBD_AFT_MRL_CTRL", 16 );
	AFT_MRL_LATCH_IND_1.Connect( pBundle, 0 );
	AFT_MRL_RELEASE_IND_1.Connect( pBundle, 1 );
	AFT_MRL_MOTOR_1_PWR.Connect( pBundle, 2 );
	AFT_MRL_IND_1_PWR.Connect( pBundle, 3 );
	AFT_RETNN_RFL_1_PWR.Connect( pBundle, 4 );
	AFT_MRL_LATCH_IND_1_TB.Connect( pBundle, 5 );
	AFT_MRL_RELEASE_IND_1_TB.Connect( pBundle, 6 );
	AFT_RETNN_RFL_1_TB.Connect( pBundle, 7 );
	AFT_MRL_LATCH_IND_2.Connect( pBundle, 8 );
	AFT_MRL_RELEASE_IND_2.Connect( pBundle, 9 );
	AFT_MRL_MOTOR_2_PWR.Connect( pBundle, 10 );
	AFT_MRL_IND_2_PWR.Connect( pBundle, 11 );
	AFT_RETNN_RFL_2_PWR.Connect( pBundle, 12 );

	if (portside)
	{
		pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM12_CH2", 16 );
		FWD_MECH_STOW_IND_1_TM.Connect( pBundle, 0 );
		pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM14_CH1", 16 );
		AFT_MECH_STOW_IND_1_TM.Connect( pBundle, 3 );
		pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM4_CH1", 16 );
		FWD_MECH_DEPLOY_IND_1_TM.Connect( pBundle, 2 );
		pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM6_CH1", 16 );
		AFT_MECH_DEPLOY_IND_1_TM.Connect( pBundle, 1 );

		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM10_CH1", 16 );
		MID_MECH_STOW_IND_2_TM.Connect( pBundle, 0 );
		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM7_CH0", 16 );
		MID_MECH_DEPLOY_IND_2_TM.Connect( pBundle, 0 );

		pBundle = BundleManager()->CreateBundle( "MDM_OA1_IOM5_CH1", 16 );
		MID_MECH_STOW_IND_1_TM.Connect( pBundle, 0 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA1_IOM1_CH1", 16 );
		MID_MECH_DEPLOY_IND_1_TM.Connect( pBundle, 0 );

		pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM5_CH0", 16 );
		SHLD_MECH_STOW_IND_1_TM.Connect( pBundle, 0 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM12_CH1", 16 );
		SHLD_MECH_DEPLOY_IND_1_TM.Connect( pBundle, 0 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM7_CH2", 16 );
		SHLD_MECH_STOW_IND_2_TM.Connect( pBundle, 1 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM1_CH2", 16 );
		SHLD_MECH_DEPLOY_IND_2_TM.Connect( pBundle, 1 );

		pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM12_CH1", 16 );
		FWD_MECH_STOW_IND_2_TM.Connect( pBundle, 9 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM7_CH2", 16 );
		AFT_MECH_STOW_IND_2_TM.Connect( pBundle, 0 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM5_CH1", 16 );
		FWD_MECH_DEPLOY_IND_2_TM.Connect( pBundle, 0 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM1_CH1", 16 );
		AFT_MECH_DEPLOY_IND_2_TM.Connect( pBundle, 0 );

		pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM6_CH2", 16 );
		AFT_MRL_LATCH_IND_2_TM.Connect( pBundle, 0 );
		pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM12_CH0", 16 );
		AFT_MRL_RELEASE_IND_2_TM.Connect( pBundle, 0 );
		pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM4_CH2", 16 );
		AFT_RETNN_RFL_2_TM.Connect( pBundle, 1 );

		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM4_CH1", 16 );
		MID_MRL_LATCH_IND_1_TM.Connect( pBundle, 0 );
		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM5_CH2", 16 );
		MID_MRL_RELEASE_IND_1_TM.Connect( pBundle, 0 );
		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM2_CH1", 16 );
		MID_RETNN_RFL_1_TM.Connect( pBundle, 1 );

		pBundle = BundleManager()->CreateBundle( "MDM_OA1_IOM10_CH1", 16 );
		MID_MRL_LATCH_IND_2_TM.Connect( pBundle, 0 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA1_IOM12_CH0", 16 );
		MID_MRL_RELEASE_IND_2_TM.Connect( pBundle, 0 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA1_IOM7_CH1", 16 );
		MID_RETNN_RFL_2_TM.Connect( pBundle, 0 );

		pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM5_CH2", 16 );
		FWD_MRL_LATCH_IND_1_TM.Connect( pBundle, 0 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM1_CH2", 16 );
		FWD_MRL_RELEASE_IND_1_TM.Connect( pBundle, 0 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM12_CH2", 16 );
		FWD_MRL_LATCH_IND_2_TM.Connect( pBundle, 0 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM7_CH2", 16 );
		FWD_MRL_RELEASE_IND_2_TM.Connect( pBundle, 0 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM10_CH2", 16 );
		FWD_RETNN_RFL_1_TM.Connect( pBundle, 0 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM12_CH0", 16 );
		FWD_RETNN_RFL_2_TM.Connect( pBundle, 0 );

		pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM5_CH0", 16 );
		AFT_MRL_LATCH_IND_1_TM.Connect( pBundle, 0 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM10_CH2", 16 );
		AFT_MRL_RELEASE_IND_1_TM.Connect( pBundle, 0 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM1_CH2", 16 );
		AFT_RETNN_RFL_1_TM.Connect( pBundle, 1 );
	}
	else
	{
		pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM12_CH2", 16 );
		FWD_MECH_STOW_IND_1_TM.Connect( pBundle, 1 );
		pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM14_CH1", 16 );
		AFT_MECH_STOW_IND_1_TM.Connect( pBundle, 4 );
		pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM4_CH1", 16 );
		FWD_MECH_DEPLOY_IND_1_TM.Connect( pBundle, 3 );
		pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM6_CH1", 16 );
		AFT_MECH_DEPLOY_IND_1_TM.Connect( pBundle, 2 );

		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM10_CH1", 16 );
		MID_MECH_STOW_IND_2_TM.Connect( pBundle, 1 );
		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM7_CH0", 16 );
		MID_MECH_DEPLOY_IND_2_TM.Connect( pBundle, 1 );

		pBundle = BundleManager()->CreateBundle( "MDM_OA1_IOM5_CH1", 16 );
		MID_MECH_STOW_IND_1_TM.Connect( pBundle, 1 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA1_IOM1_CH1", 16 );
		MID_MECH_DEPLOY_IND_1_TM.Connect( pBundle, 1 );

		pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM5_CH0", 16 );
		SHLD_MECH_STOW_IND_1_TM.Connect( pBundle, 1 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM12_CH1", 16 );
		SHLD_MECH_DEPLOY_IND_1_TM.Connect( pBundle, 1 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM7_CH2", 16 );
		SHLD_MECH_STOW_IND_2_TM.Connect( pBundle, 3 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM1_CH2", 16 );
		SHLD_MECH_DEPLOY_IND_2_TM.Connect( pBundle, 3 );

		pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM12_CH1", 16 );
		FWD_MECH_STOW_IND_2_TM.Connect( pBundle, 10 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM7_CH2", 16 );
		AFT_MECH_STOW_IND_2_TM.Connect( pBundle, 1 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM5_CH1", 16 );
		FWD_MECH_DEPLOY_IND_2_TM.Connect( pBundle, 1 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM1_CH1", 16 );
		AFT_MECH_DEPLOY_IND_2_TM.Connect( pBundle, 1 );

		pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM6_CH2", 16 );
		AFT_MRL_LATCH_IND_2_TM.Connect( pBundle, 1 );
		pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM12_CH0", 16 );
		AFT_MRL_RELEASE_IND_2_TM.Connect( pBundle, 1 );
		pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM4_CH2", 16 );
		AFT_RETNN_RFL_2_TM.Connect( pBundle, 2 );

		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM4_CH1", 16 );
		MID_MRL_LATCH_IND_1_TM.Connect( pBundle, 1 );
		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM5_CH2", 16 );
		MID_MRL_RELEASE_IND_1_TM.Connect( pBundle, 1 );
		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM2_CH1", 16 );
		MID_RETNN_RFL_1_TM.Connect( pBundle, 2 );

		pBundle = BundleManager()->CreateBundle( "MDM_OA1_IOM10_CH1", 16 );
		MID_MRL_LATCH_IND_2_TM.Connect( pBundle, 1 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA1_IOM12_CH0", 16 );
		MID_MRL_RELEASE_IND_2_TM.Connect( pBundle, 1 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA1_IOM7_CH1", 16 );
		MID_RETNN_RFL_2_TM.Connect( pBundle, 1 );

		pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM5_CH2", 16 );
		FWD_MRL_LATCH_IND_1_TM.Connect( pBundle, 1 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM1_CH2", 16 );
		FWD_MRL_RELEASE_IND_1_TM.Connect( pBundle, 2 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM12_CH2", 16 );
		FWD_MRL_LATCH_IND_2_TM.Connect( pBundle, 1 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM7_CH2", 16 );
		FWD_MRL_RELEASE_IND_2_TM.Connect( pBundle, 2 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM10_CH2", 16 );
		FWD_RETNN_RFL_1_TM.Connect( pBundle, 1 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM12_CH0", 16 );
		FWD_RETNN_RFL_2_TM.Connect( pBundle, 1 );

		pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM5_CH0", 16 );
		AFT_MRL_LATCH_IND_1_TM.Connect( pBundle, 1 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM10_CH2", 16 );
		AFT_MRL_RELEASE_IND_1_TM.Connect( pBundle, 1 );
		pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM1_CH2", 16 );
		AFT_RETNN_RFL_1_TM.Connect( pBundle, 2 );
	}

	if (AllMRLLatchesOpen())
	{
		PrevLatchState = true;
		OnMRLReleased();
	}
	else
	{
		PrevLatchState = false;
		OnMRLLatched();
	}

	RunMicroswitches();
	return;
}

void MPM::OnPreStep( double simt, double simdt, double mjd )
{
	LatchSystem::OnPreStep( simt, simdt, mjd );

	if (!doubleAttached)// don't allow MPM movement when payload is attached to something else
	{
		double dpos = simdt * MPM_DEPLOY_SPEED * (MPM_MOTOR_1_PWR.GetVoltage() + MPM_MOTOR_2_PWR.GetVoltage());
		if (dpos != 0.0)
		{
			Rollout = range( 0.0, Rollout + dpos, 1.0 );
			STS()->SetAnimation( anim_mpm, Rollout );
			mpm_moved = true;
		}
		else mpm_moved = false;
	}

	MRL[0] = range( 0.0, MRL[0] + (simdt * MRL_LATCH_SPEED * (FWD_MRL_MOTOR_1_PWR.GetVoltage() + FWD_MRL_MOTOR_2_PWR.GetVoltage())), 1.0 );
	MRL[1] = range( 0.0, MRL[1] + (simdt * MRL_LATCH_SPEED * (MID_MRL_MOTOR_1_PWR.GetVoltage() + MID_MRL_MOTOR_2_PWR.GetVoltage())), 1.0 );
	MRL[2] = range( 0.0, MRL[2] + (simdt * MRL_LATCH_SPEED * (AFT_MRL_MOTOR_1_PWR.GetVoltage() + AFT_MRL_MOTOR_2_PWR.GetVoltage())), 1.0 );

	// handle attachment
	if (AllMRLLatchesOpen() != PrevLatchState)
	{
		if (PrevLatchState)
		{
			// op -> cl = check for latch
			PrevLatchState = false;
			OnMRLLatched();
		}
		else
		{
			// cl -> op = check for release
			PrevLatchState = true;
			OnMRLReleased();
		}
	}

	RunMicroswitches();
	return;
}

bool MPM::OnParseLine( const char* line )
{
	if (!_strnicmp( line, "MPM_ROLLOUT", 11 ))
	{
		sscanf_s( line + 11, "%lf", &Rollout );
		mpm_moved = true;
		return true;
	}
	else if (!_strnicmp( line, "MPM_LATCHES", 11 ))
	{
		sscanf_s( line + 11, "%lf %lf %lf", &MRL[0], &MRL[1], &MRL[2] );
		return true;
	}
	return LatchSystem::OnParseLine( line );
}

void MPM::OnSaveState( FILEHANDLE scn ) const
{
	char cbuf[255];

	oapiWriteScenario_float( scn, "MPM_ROLLOUT", Rollout );

	sprintf_s( cbuf, 255, "%f %f %f", MRL[0], MRL[1], MRL[2] );
	oapiWriteScenario_string( scn, "MPM_LATCHES", cbuf );

	LatchSystem::OnSaveState( scn );
	return;
}

void MPM::AddMesh( void )
{
	VECTOR3 ofs = STS()->GetOrbiterCoGOffset();
	mesh_index_MPM = STS()->AddMesh( hMesh_MPM, &ofs );
	STS()->SetMeshVisibilityMode( mesh_index_MPM, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
	return;
}

void MPM::AddAnimation( void )
{
	static UINT MPM_Port_GRP[4] = {GRP_LOWER_PEDESTAL_SHOULDER_MPM_Port, GRP_LOWER_PEDESTAL_FORWARD_MPM_Port, GRP_LOWER_PEDESTAL_MID_MPM_Port, GRP_LOWER_PEDESTAL_AFT_MPM_Port};
	static UINT MPM_Stbd_GRP[4] = {GRP_LOWER_PEDESTAL_SHOULDER_MPM_Starboard, GRP_LOWER_PEDESTAL_FORWARD_MPM_Starboard, GRP_LOWER_PEDESTAL_MID_MPM_Starboard, GRP_LOWER_PEDESTAL_AFT_MPM_Starboard};
	MGROUP_ROTATE* pMPMAnim = new MGROUP_ROTATE( mesh_index_MPM, portside ? MPM_Port_GRP : MPM_Stbd_GRP, 4,
		portside ? MPM_DEPLOY_REF_PORT : MPM_DEPLOY_REF_STBD,
		portside ? MPM_DEPLOY_AXIS_PORT : MPM_DEPLOY_AXIS_STBD,
		portside ? MPM_DEPLOY_ANGLE_PORT : MPM_DEPLOY_ANGLE_STBD
	);
	anim_mpm = STS()->CreateAnimation( 1.0 );
	mpmparent = STS()->AddAnimationComponent( anim_mpm, 0.0, 1.0, pMPMAnim );
	SaveAnimation( pMPMAnim );

	STS()->SetAnimation( anim_mpm, Rollout );
	return;
}

void MPM::OnAttach( void )
{
	return;
}

void MPM::OnDetach( void )
{
	doubleAttached = false;
	return;
}

bool MPM::SetDoubleAttach( VESSEL* vessel, bool attached )
{
	if ((attachedPayload == vessel) || (vessel->GetHandle() == STS()->GetAttachmentStatus( hAttach )))
		doubleAttached = attached;
	return doubleAttached;
}

void MPM::RunMicroswitches( void )
{
	if (Rollout == 1.0)
	{
		SHLD_MECH_STOW_IND_1.ResetLine();
		SHLD_MECH_STOW_IND_1_TB.ResetLine();
		SHLD_MECH_STOW_IND_1_TM.ResetLine();

		if (MPM_SHOULDER_1_IND_PWR)
		{
			SHLD_MECH_DEPLOY_IND_1.SetLine();
			SHLD_MECH_DEPLOY_IND_1_TB.SetLine();
			SHLD_MECH_DEPLOY_IND_1_TM.SetLine();
		}
		else
		{
			SHLD_MECH_DEPLOY_IND_1.ResetLine();
			SHLD_MECH_DEPLOY_IND_1_TB.ResetLine();
			SHLD_MECH_DEPLOY_IND_1_TM.ResetLine();
		}

		SHLD_MECH_STOW_IND_2.ResetLine();
		SHLD_MECH_STOW_IND_2_TB.ResetLine();
		SHLD_MECH_STOW_IND_2_TM.ResetLine();

		if (MPM_SHOULDER_2_IND_PWR)
		{
			SHLD_MECH_DEPLOY_IND_2.SetLine();
			SHLD_MECH_DEPLOY_IND_2_TB.SetLine();
			SHLD_MECH_DEPLOY_IND_2_TM.SetLine();
		}
		else
		{
			SHLD_MECH_DEPLOY_IND_2.ResetLine();
			SHLD_MECH_DEPLOY_IND_2_TB.ResetLine();
			SHLD_MECH_DEPLOY_IND_2_TM.ResetLine();
		}

		FWD_MECH_STOW_IND_1_TB.ResetLine();
		FWD_MECH_STOW_IND_1_TM.ResetLine();

		if (MPM_FWD_1_IND_PWR)
		{
			FWD_MECH_DEPLOY_IND_1_TB.SetLine();
			FWD_MECH_DEPLOY_IND_1_TM.SetLine();
		}
		else
		{
			FWD_MECH_DEPLOY_IND_1_TB.ResetLine();
			FWD_MECH_DEPLOY_IND_1_TM.ResetLine();
		}

		FWD_MECH_STOW_IND_2_TB.ResetLine();
		FWD_MECH_STOW_IND_2_TM.ResetLine();

		if (MPM_FWD_2_IND_PWR)
		{
			FWD_MECH_DEPLOY_IND_2_TB.SetLine();
			FWD_MECH_DEPLOY_IND_2_TM.SetLine();
		}
		else
		{
			FWD_MECH_DEPLOY_IND_2_TB.ResetLine();
			FWD_MECH_DEPLOY_IND_2_TM.ResetLine();
		}

		MID_MECH_STOW_IND_1_TB.ResetLine();
		MID_MECH_STOW_IND_1_TM.ResetLine();

		if (MPM_MID_1_IND_PWR)
		{
			MID_MECH_DEPLOY_IND_1_TB.SetLine();
			MID_MECH_DEPLOY_IND_1_TM.SetLine();
		}
		else
		{
			MID_MECH_DEPLOY_IND_1_TB.ResetLine();
			MID_MECH_DEPLOY_IND_1_TM.ResetLine();
		}

		MID_MECH_STOW_IND_2_TB.ResetLine();
		MID_MECH_STOW_IND_2_TM.ResetLine();

		if (MPM_MID_2_IND_PWR)
		{
			MID_MECH_DEPLOY_IND_2_TB.SetLine();
			MID_MECH_DEPLOY_IND_2_TM.SetLine();
		}
		else
		{
			MID_MECH_DEPLOY_IND_2_TB.ResetLine();
			MID_MECH_DEPLOY_IND_2_TM.ResetLine();
		}

		AFT_MECH_STOW_IND_1_TB.ResetLine();
		AFT_MECH_STOW_IND_1_TM.ResetLine();

		if (MPM_AFT_1_IND_PWR)
		{
			AFT_MECH_DEPLOY_IND_1_TB.SetLine();
			AFT_MECH_DEPLOY_IND_1_TM.SetLine();
		}
		else
		{
			AFT_MECH_DEPLOY_IND_1_TB.ResetLine();
			AFT_MECH_DEPLOY_IND_1_TM.ResetLine();
		}

		AFT_MECH_STOW_IND_2_TB.ResetLine();
		AFT_MECH_STOW_IND_2_TM.ResetLine();

		if (MPM_AFT_2_IND_PWR)
		{
			AFT_MECH_DEPLOY_IND_2_TB.SetLine();
			AFT_MECH_DEPLOY_IND_2_TM.SetLine();
		}
		else
		{
			AFT_MECH_DEPLOY_IND_2_TB.ResetLine();
			AFT_MECH_DEPLOY_IND_2_TM.ResetLine();
		}
	}
	else if (Rollout == 0.0)
	{
		if (MPM_SHOULDER_1_IND_PWR)
		{
			SHLD_MECH_STOW_IND_1.SetLine();
			SHLD_MECH_STOW_IND_1_TB.SetLine();
			SHLD_MECH_STOW_IND_1_TM.SetLine();
		}
		else
		{
			SHLD_MECH_STOW_IND_1.ResetLine();
			SHLD_MECH_STOW_IND_1_TB.ResetLine();
			SHLD_MECH_STOW_IND_1_TM.ResetLine();
		}

		SHLD_MECH_DEPLOY_IND_1.ResetLine();
		SHLD_MECH_DEPLOY_IND_1_TB.ResetLine();
		SHLD_MECH_DEPLOY_IND_1_TM.ResetLine();

		if (MPM_SHOULDER_2_IND_PWR)
		{
			SHLD_MECH_STOW_IND_2.SetLine();
			SHLD_MECH_STOW_IND_2_TB.SetLine();
			SHLD_MECH_STOW_IND_2_TM.SetLine();
		}
		else
		{
			SHLD_MECH_STOW_IND_2.ResetLine();
			SHLD_MECH_STOW_IND_2_TB.ResetLine();
			SHLD_MECH_STOW_IND_2_TM.ResetLine();
		}

		SHLD_MECH_DEPLOY_IND_2.ResetLine();
		SHLD_MECH_DEPLOY_IND_2_TB.ResetLine();
		SHLD_MECH_DEPLOY_IND_2_TM.ResetLine();

		if (MPM_FWD_1_IND_PWR)
		{
			FWD_MECH_STOW_IND_1_TB.SetLine();
			FWD_MECH_STOW_IND_1_TM.SetLine();
		}
		else
		{
			FWD_MECH_STOW_IND_1_TB.ResetLine();
			FWD_MECH_STOW_IND_1_TM.ResetLine();
		}

		FWD_MECH_DEPLOY_IND_1_TB.ResetLine();
		FWD_MECH_DEPLOY_IND_1_TM.ResetLine();

		if (MPM_FWD_2_IND_PWR)
		{
			FWD_MECH_STOW_IND_2_TB.SetLine();
			FWD_MECH_STOW_IND_2_TM.SetLine();
		}
		else
		{
			FWD_MECH_STOW_IND_2_TB.ResetLine();
			FWD_MECH_STOW_IND_2_TM.ResetLine();
		}

		FWD_MECH_DEPLOY_IND_2_TB.ResetLine();
		FWD_MECH_DEPLOY_IND_2_TM.ResetLine();

		if (MPM_MID_1_IND_PWR)
		{
			MID_MECH_STOW_IND_1_TB.SetLine();
			MID_MECH_STOW_IND_1_TM.SetLine();
		}
		else
		{
			MID_MECH_STOW_IND_1_TB.ResetLine();
			MID_MECH_STOW_IND_1_TM.ResetLine();
		}

		MID_MECH_DEPLOY_IND_1_TB.ResetLine();
		MID_MECH_DEPLOY_IND_1_TM.ResetLine();

		if (MPM_MID_2_IND_PWR)
		{
			MID_MECH_STOW_IND_2_TB.SetLine();
			MID_MECH_STOW_IND_2_TM.SetLine();
		}
		else
		{
			MID_MECH_STOW_IND_2_TB.ResetLine();
			MID_MECH_STOW_IND_2_TM.ResetLine();
		}

		MID_MECH_DEPLOY_IND_2_TB.ResetLine();
		MID_MECH_DEPLOY_IND_2_TM.ResetLine();

		if (MPM_AFT_1_IND_PWR)
		{
			AFT_MECH_STOW_IND_1_TB.SetLine();
			AFT_MECH_STOW_IND_1_TM.SetLine();
		}
		else
		{
			AFT_MECH_STOW_IND_1_TB.ResetLine();
			AFT_MECH_STOW_IND_1_TM.ResetLine();
		}

		AFT_MECH_DEPLOY_IND_1_TB.ResetLine();
		AFT_MECH_DEPLOY_IND_1_TM.ResetLine();

		if (MPM_AFT_2_IND_PWR)
		{
			AFT_MECH_STOW_IND_2_TB.SetLine();
			AFT_MECH_STOW_IND_2_TM.SetLine();
		}
		else
		{
			AFT_MECH_STOW_IND_2_TB.ResetLine();
			AFT_MECH_STOW_IND_2_TM.ResetLine();
		}

		AFT_MECH_DEPLOY_IND_2_TB.ResetLine();
		AFT_MECH_DEPLOY_IND_2_TM.ResetLine();
	}
	else
	{
		SHLD_MECH_STOW_IND_1.ResetLine();
		SHLD_MECH_STOW_IND_1_TB.ResetLine();
		SHLD_MECH_STOW_IND_1_TM.ResetLine();
		SHLD_MECH_DEPLOY_IND_1.ResetLine();
		SHLD_MECH_DEPLOY_IND_1_TB.ResetLine();
		SHLD_MECH_DEPLOY_IND_1_TM.ResetLine();
		SHLD_MECH_STOW_IND_2.ResetLine();
		SHLD_MECH_STOW_IND_2_TB.ResetLine();
		SHLD_MECH_STOW_IND_2_TM.ResetLine();
		SHLD_MECH_DEPLOY_IND_2.ResetLine();
		SHLD_MECH_DEPLOY_IND_2_TB.ResetLine();
		SHLD_MECH_DEPLOY_IND_2_TM.ResetLine();
		FWD_MECH_STOW_IND_1_TB.ResetLine();
		FWD_MECH_STOW_IND_1_TM.ResetLine();
		FWD_MECH_DEPLOY_IND_1_TB.ResetLine();
		FWD_MECH_DEPLOY_IND_1_TM.ResetLine();
		FWD_MECH_STOW_IND_2_TB.ResetLine();
		FWD_MECH_STOW_IND_2_TM.ResetLine();
		FWD_MECH_DEPLOY_IND_2_TB.ResetLine();
		FWD_MECH_DEPLOY_IND_2_TM.ResetLine();
		MID_MECH_STOW_IND_1_TB.ResetLine();
		MID_MECH_STOW_IND_1_TM.ResetLine();
		MID_MECH_DEPLOY_IND_1_TB.ResetLine();
		MID_MECH_DEPLOY_IND_1_TM.ResetLine();
		MID_MECH_STOW_IND_2_TB.ResetLine();
		MID_MECH_STOW_IND_2_TM.ResetLine();
		MID_MECH_DEPLOY_IND_2_TB.ResetLine();
		MID_MECH_DEPLOY_IND_2_TM.ResetLine();
		AFT_MECH_STOW_IND_1_TB.ResetLine();
		AFT_MECH_STOW_IND_1_TM.ResetLine();
		AFT_MECH_DEPLOY_IND_1_TB.ResetLine();
		AFT_MECH_DEPLOY_IND_1_TM.ResetLine();
		AFT_MECH_STOW_IND_2_TB.ResetLine();
		AFT_MECH_STOW_IND_2_TM.ResetLine();
		AFT_MECH_DEPLOY_IND_2_TB.ResetLine();
		AFT_MECH_DEPLOY_IND_2_TM.ResetLine();
	}


	if (MRL[0] == 1.0)
	{
		FWD_MRL_LATCH_IND_1.ResetLine();
		FWD_MRL_LATCH_IND_1_TB.ResetLine();
		FWD_MRL_LATCH_IND_1_TM.ResetLine();

		if (FWD_MRL_IND_1_PWR)
		{
			FWD_MRL_RELEASE_IND_1.SetLine();
			FWD_MRL_RELEASE_IND_1_TB.SetLine();
			FWD_MRL_RELEASE_IND_1_TM.SetLine();
		}
		else
		{
			FWD_MRL_RELEASE_IND_1.ResetLine();
			FWD_MRL_RELEASE_IND_1_TB.ResetLine();
			FWD_MRL_RELEASE_IND_1_TM.ResetLine();
		}

		FWD_MRL_LATCH_IND_2.ResetLine();
		FWD_MRL_LATCH_IND_2_TM.ResetLine();

		if (FWD_MRL_IND_2_PWR)
		{
			FWD_MRL_RELEASE_IND_2.SetLine();
			FWD_MRL_RELEASE_IND_2_TM.SetLine();
		}
		else
		{
			FWD_MRL_RELEASE_IND_2.ResetLine();
			FWD_MRL_RELEASE_IND_2_TM.ResetLine();
		}
	}
	else if (MRL[0] == 0.0)
	{
		if (FWD_MRL_IND_1_PWR)
		{
			FWD_MRL_LATCH_IND_1.SetLine();
			FWD_MRL_LATCH_IND_1_TB.SetLine();
			FWD_MRL_LATCH_IND_1_TM.SetLine();
		}
		else
		{
			FWD_MRL_LATCH_IND_1.ResetLine();
			FWD_MRL_LATCH_IND_1_TB.ResetLine();
			FWD_MRL_LATCH_IND_1_TM.ResetLine();
		}

		FWD_MRL_RELEASE_IND_1.ResetLine();
		FWD_MRL_RELEASE_IND_1_TB.ResetLine();
		FWD_MRL_RELEASE_IND_1_TM.ResetLine();

		if (FWD_MRL_IND_2_PWR)
		{
			FWD_MRL_LATCH_IND_2.SetLine();
			FWD_MRL_LATCH_IND_2_TM.SetLine();
		}
		else
		{
			FWD_MRL_LATCH_IND_2.ResetLine();
			FWD_MRL_LATCH_IND_2_TM.ResetLine();
		}

		FWD_MRL_RELEASE_IND_2.ResetLine();
		FWD_MRL_RELEASE_IND_2_TM.ResetLine();
	}
	else
	{
		FWD_MRL_LATCH_IND_1.ResetLine();
		FWD_MRL_LATCH_IND_1_TB.ResetLine();
		FWD_MRL_LATCH_IND_1_TM.ResetLine();
		FWD_MRL_RELEASE_IND_1.ResetLine();
		FWD_MRL_RELEASE_IND_1_TB.ResetLine();
		FWD_MRL_RELEASE_IND_1_TM.ResetLine();
		FWD_MRL_LATCH_IND_2.ResetLine();
		FWD_MRL_LATCH_IND_2_TM.ResetLine();
		FWD_MRL_RELEASE_IND_2.ResetLine();
		FWD_MRL_RELEASE_IND_2_TM.ResetLine();
	}

	if (MRL[1] == 1.0)
	{
		MID_MRL_LATCH_IND_1.ResetLine();
		MID_MRL_LATCH_IND_1_TB.ResetLine();
		MID_MRL_LATCH_IND_1_TM.ResetLine();

		if (MID_MRL_IND_1_PWR)
		{
			MID_MRL_RELEASE_IND_1.SetLine();
			MID_MRL_RELEASE_IND_1_TB.SetLine();
			MID_MRL_RELEASE_IND_1_TM.SetLine();
		}
		else
		{
			MID_MRL_RELEASE_IND_1.ResetLine();
			MID_MRL_RELEASE_IND_1_TB.ResetLine();
			MID_MRL_RELEASE_IND_1_TM.ResetLine();
		}

		MID_MRL_LATCH_IND_2.ResetLine();
		MID_MRL_LATCH_IND_2_TM.ResetLine();

		if (MID_MRL_IND_2_PWR)
		{
			MID_MRL_RELEASE_IND_2.SetLine();
			MID_MRL_RELEASE_IND_2_TM.SetLine();
		}
		else
		{
			MID_MRL_RELEASE_IND_2.ResetLine();
			MID_MRL_RELEASE_IND_2_TM.ResetLine();
		}
	}
	else if (MRL[1] == 0.0)
	{
		if (MID_MRL_IND_1_PWR)
		{
			MID_MRL_LATCH_IND_1.SetLine();
			MID_MRL_LATCH_IND_1_TB.SetLine();
			MID_MRL_LATCH_IND_1_TM.SetLine();
		}
		else
		{
			MID_MRL_LATCH_IND_1.ResetLine();
			MID_MRL_LATCH_IND_1_TB.ResetLine();
			MID_MRL_LATCH_IND_1_TM.ResetLine();
		}

		MID_MRL_RELEASE_IND_1.ResetLine();
		MID_MRL_RELEASE_IND_1_TB.ResetLine();
		MID_MRL_RELEASE_IND_1_TM.ResetLine();

		if (MID_MRL_IND_2_PWR)
		{
			MID_MRL_LATCH_IND_2.SetLine();
			MID_MRL_LATCH_IND_2_TM.SetLine();
		}
		else
		{
			MID_MRL_LATCH_IND_2.ResetLine();
			MID_MRL_LATCH_IND_2_TM.ResetLine();
		}

		MID_MRL_RELEASE_IND_2.ResetLine();
		MID_MRL_RELEASE_IND_2_TM.ResetLine();
	}
	else
	{
		MID_MRL_LATCH_IND_1.ResetLine();
		MID_MRL_LATCH_IND_1_TB.ResetLine();
		MID_MRL_LATCH_IND_1_TM.ResetLine();
		MID_MRL_RELEASE_IND_1.ResetLine();
		MID_MRL_RELEASE_IND_1_TB.ResetLine();
		MID_MRL_RELEASE_IND_1_TM.ResetLine();
		MID_MRL_LATCH_IND_2.ResetLine();
		MID_MRL_LATCH_IND_2_TM.ResetLine();
		MID_MRL_RELEASE_IND_2.ResetLine();
		MID_MRL_RELEASE_IND_2_TM.ResetLine();
	}

	if (MRL[2] == 1.0)
	{
		AFT_MRL_LATCH_IND_1.ResetLine();
		AFT_MRL_LATCH_IND_1_TB.ResetLine();
		AFT_MRL_LATCH_IND_1_TM.ResetLine();

		if (AFT_MRL_IND_1_PWR)
		{
			AFT_MRL_RELEASE_IND_1.SetLine();
			AFT_MRL_RELEASE_IND_1_TB.SetLine();
			AFT_MRL_RELEASE_IND_1_TM.SetLine();
		}
		else
		{
			AFT_MRL_RELEASE_IND_1.ResetLine();
			AFT_MRL_RELEASE_IND_1_TB.ResetLine();
			AFT_MRL_RELEASE_IND_1_TM.ResetLine();
		}

		AFT_MRL_LATCH_IND_2.ResetLine();
		AFT_MRL_LATCH_IND_2_TM.ResetLine();

		if (AFT_MRL_IND_2_PWR)
		{
			AFT_MRL_RELEASE_IND_2.SetLine();
			AFT_MRL_RELEASE_IND_2_TM.SetLine();
		}
		else
		{
			AFT_MRL_RELEASE_IND_2.ResetLine();
			AFT_MRL_RELEASE_IND_2_TM.ResetLine();
		}
	}
	else if (MRL[2] == 0.0)
	{
		if (AFT_MRL_IND_1_PWR)
		{
			AFT_MRL_LATCH_IND_1.SetLine();
			AFT_MRL_LATCH_IND_1_TB.SetLine();
			AFT_MRL_LATCH_IND_1_TM.SetLine();
		}
		else
		{
			AFT_MRL_LATCH_IND_1.ResetLine();
			AFT_MRL_LATCH_IND_1_TB.ResetLine();
			AFT_MRL_LATCH_IND_1_TM.ResetLine();
		}

		AFT_MRL_RELEASE_IND_1.ResetLine();
		AFT_MRL_RELEASE_IND_1_TB.ResetLine();
		AFT_MRL_RELEASE_IND_1_TM.ResetLine();

		if (AFT_MRL_IND_2_PWR)
		{
			AFT_MRL_LATCH_IND_2.SetLine();
			AFT_MRL_LATCH_IND_2_TM.SetLine();
		}
		else
		{
			AFT_MRL_LATCH_IND_2.ResetLine();
			AFT_MRL_LATCH_IND_2_TM.ResetLine();
		}

		AFT_MRL_RELEASE_IND_2.ResetLine();
		AFT_MRL_RELEASE_IND_2_TM.ResetLine();
	}
	else
	{
		AFT_MRL_LATCH_IND_1.ResetLine();
		AFT_MRL_LATCH_IND_1_TB.ResetLine();
		AFT_MRL_LATCH_IND_1_TM.ResetLine();
		AFT_MRL_RELEASE_IND_1.ResetLine();
		AFT_MRL_RELEASE_IND_1_TB.ResetLine();
		AFT_MRL_RELEASE_IND_1_TM.ResetLine();
		AFT_MRL_LATCH_IND_2.ResetLine();
		AFT_MRL_LATCH_IND_2_TM.ResetLine();
		AFT_MRL_RELEASE_IND_2.ResetLine();
		AFT_MRL_RELEASE_IND_2_TM.ResetLine();
	}
	return;
}

void MPM::SetRFL( bool fwd, bool mid, bool aft )
{
	if (fwd)
	{
		if (FWD_RETNN_RFL_1_PWR)
		{
			FWD_RETNN_RFL_1_TB.SetLine();
			FWD_RETNN_RFL_1_TM.SetLine();
		}
		else
		{
			FWD_RETNN_RFL_1_TB.ResetLine();
			FWD_RETNN_RFL_1_TM.ResetLine();
		}

		if (FWD_RETNN_RFL_2_PWR) FWD_RETNN_RFL_2_TM.SetLine();
		else FWD_RETNN_RFL_2_TM.ResetLine();
	}
	else
	{
		FWD_RETNN_RFL_1_TB.ResetLine();
		FWD_RETNN_RFL_1_TM.ResetLine();
		FWD_RETNN_RFL_2_TM.ResetLine();
	}

	if (mid)
	{
		if (MID_RETNN_RFL_1_PWR)
		{
			MID_RETNN_RFL_1_TB.SetLine();
			MID_RETNN_RFL_1_TM.SetLine();
		}
		else
		{
			MID_RETNN_RFL_1_TB.ResetLine();
			MID_RETNN_RFL_1_TM.ResetLine();
		}

		if (MID_RETNN_RFL_2_PWR) MID_RETNN_RFL_2_TM.SetLine();
		else MID_RETNN_RFL_2_TM.ResetLine();
	}
	else
	{
		MID_RETNN_RFL_1_TB.ResetLine();
		MID_RETNN_RFL_1_TM.ResetLine();
		MID_RETNN_RFL_2_TM.ResetLine();
	}

	if (aft)
	{
		if (AFT_RETNN_RFL_1_PWR)
		{
			AFT_RETNN_RFL_1_TB.SetLine();
			AFT_RETNN_RFL_1_TM.SetLine();
		}
		else
		{
			AFT_RETNN_RFL_1_TB.ResetLine();
			AFT_RETNN_RFL_1_TM.ResetLine();
		}

		if (AFT_RETNN_RFL_2_PWR) AFT_RETNN_RFL_2_TM.SetLine();
		else AFT_RETNN_RFL_2_TM.ResetLine();
	}
	else
	{
		AFT_RETNN_RFL_1_TB.ResetLine();
		AFT_RETNN_RFL_1_TM.ResetLine();
		AFT_RETNN_RFL_2_TM.ResetLine();
	}
	return;
}

bool MPM::AllMRLLatchesOpen( void ) const
{
	for (unsigned short j = 0; j < 3; j++)
	{
		if (MRL[j] <= 0.5) return false;
	}
	return true;
}

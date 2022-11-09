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
	: LatchSystem( _director, _ident, _attachID, latchmaxdistance, latchmaxangle ), MPM_Base( _portside )
{
	mesh_index_MPM = MESH_UNDEFINED;
	hMesh_MPM = oapiLoadMeshGlobal( _portside ? MESHNAME_MPM_PORT : MESHNAME_MPM_STBD );

	mpm_moved = false;
	doubleAttached = false;

	Rollout = 1.0;
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

	DiscreteBundle* pBundle;

	if (portside)
	{
		pBundle = BundleManager()->CreateBundle( "PORT_MPM_IND", 16 );
		SHLD_MECH_STOW_IND_1.Connect( pBundle, 0 );
		FWD_MECH_STOW_IND_1.Connect( pBundle, 1 );
		MID_MECH_STOW_IND_1.Connect( pBundle, 2 );
		AFT_MECH_STOW_IND_1.Connect( pBundle, 3 );
		SHLD_MECH_DEPLOY_IND_1.Connect( pBundle, 4 );
		FWD_MECH_DEPLOY_IND_1.Connect( pBundle, 5 );
		MID_MECH_DEPLOY_IND_1.Connect( pBundle, 6 );
		AFT_MECH_DEPLOY_IND_1.Connect( pBundle, 7 );
		SHLD_MECH_STOW_IND_2.Connect( pBundle, 8 );
		FWD_MECH_STOW_IND_2.Connect( pBundle, 9 );
		MID_MECH_STOW_IND_2.Connect( pBundle, 10 );
		AFT_MECH_STOW_IND_2.Connect( pBundle, 11 );
		SHLD_MECH_DEPLOY_IND_2.Connect( pBundle, 12 );
		FWD_MECH_DEPLOY_IND_2.Connect( pBundle, 13 );
		MID_MECH_DEPLOY_IND_2.Connect( pBundle, 14 );
		AFT_MECH_DEPLOY_IND_2.Connect( pBundle, 15 );

		pBundle = BundleManager()->CreateBundle( "PORT_MPM_PWR", 16 );
		MPM_MOTOR_1_PWR.Connect( pBundle, 0 );
		MPM_MOTOR_2_PWR.Connect( pBundle, 1 );
		MPM_SHOULDER_1_IND_PWR.Connect( pBundle, 2 );
		MPM_SHOULDER_2_IND_PWR.Connect( pBundle, 3 );
		MPM_FWD_1_IND_PWR.Connect( pBundle, 4 );
		MPM_FWD_2_IND_PWR.Connect( pBundle, 5 );
		MPM_MID_1_IND_PWR.Connect( pBundle, 6 );
		MPM_MID_2_IND_PWR.Connect( pBundle, 7 );
		MPM_AFT_1_IND_PWR.Connect( pBundle, 8 );
		MPM_AFT_2_IND_PWR.Connect( pBundle, 9 );

		pBundle = BundleManager()->CreateBundle( "FWD_MRL_IND", 16 );
		FWD_MRL_LATCH_IND_1.Connect( pBundle, 0 );
		FWD_MRL_RELEASE_IND_1.Connect( pBundle, 1 );
		FWD_MRL_LATCH_IND_2.Connect( pBundle, 2 );
		FWD_MRL_RELEASE_IND_2.Connect( pBundle, 3 );
		FWD_RETNN_RFL_1.Connect( pBundle, 4 );
		FWD_RETNN_RFL_2.Connect( pBundle, 5 );

		pBundle = BundleManager()->CreateBundle( "MID_MRL_IND", 16 );
		MID_MRL_LATCH_IND_1.Connect( pBundle, 0 );
		MID_MRL_RELEASE_IND_1.Connect( pBundle, 1 );
		MID_MRL_LATCH_IND_2.Connect( pBundle, 2 );
		MID_MRL_RELEASE_IND_2.Connect( pBundle, 3 );
		MID_RETNN_RFL_1.Connect( pBundle, 4 );
		MID_RETNN_RFL_2.Connect( pBundle, 5 );

		pBundle = BundleManager()->CreateBundle( "AFT_MRL_IND", 16 );
		AFT_MRL_LATCH_IND_1.Connect( pBundle, 0 );
		AFT_MRL_RELEASE_IND_1.Connect( pBundle, 1 );
		AFT_MRL_LATCH_IND_2.Connect( pBundle, 2 );
		AFT_MRL_RELEASE_IND_2.Connect( pBundle, 3 );
		AFT_RETNN_RFL_1.Connect( pBundle, 4 );
		AFT_RETNN_RFL_2.Connect( pBundle, 5 );

		pBundle = BundleManager()->CreateBundle( "FWD_MRL_PWR", 16 );
		FWD_MRL_MOTOR_1_PWR.Connect( pBundle, 0 );
		FWD_MRL_MOTOR_2_PWR.Connect( pBundle, 1 );
		FWD_MRL_IND_1_PWR.Connect( pBundle, 2 );
		FWD_MRL_IND_2_PWR.Connect( pBundle, 3 );
		FWD_RETNN_RFL_1_PWR.Connect( pBundle, 4 );
		FWD_RETNN_RFL_2_PWR.Connect( pBundle, 5 );

		pBundle = BundleManager()->CreateBundle( "MID_MRL_PWR", 16 );
		MID_MRL_MOTOR_1_PWR.Connect( pBundle, 0 );
		MID_MRL_MOTOR_2_PWR.Connect( pBundle, 1 );
		MID_MRL_IND_1_PWR.Connect( pBundle, 2 );
		MID_MRL_IND_2_PWR.Connect( pBundle, 3 );
		MID_RETNN_RFL_1_PWR.Connect( pBundle, 4 );
		MID_RETNN_RFL_2_PWR.Connect( pBundle, 5 );

		pBundle = BundleManager()->CreateBundle( "AFT_MRL_PWR", 16 );
		AFT_MRL_MOTOR_1_PWR.Connect( pBundle, 0 );
		AFT_MRL_MOTOR_2_PWR.Connect( pBundle, 1 );
		AFT_MRL_IND_1_PWR.Connect( pBundle, 2 );
		AFT_MRL_IND_2_PWR.Connect( pBundle, 3 );
		AFT_RETNN_RFL_1_PWR.Connect( pBundle, 4 );
		AFT_RETNN_RFL_2_PWR.Connect( pBundle, 5 );
	}
	else
	{
		pBundle = BundleManager()->CreateBundle( "STBD_MPM_IND", 16 );
		SHLD_MECH_STOW_IND_1.Connect( pBundle, 0 );
		FWD_MECH_STOW_IND_1.Connect( pBundle, 1 );
		MID_MECH_STOW_IND_1.Connect( pBundle, 2 );
		AFT_MECH_STOW_IND_1.Connect( pBundle, 3 );
		SHLD_MECH_DEPLOY_IND_1.Connect( pBundle, 4 );
		FWD_MECH_DEPLOY_IND_1.Connect( pBundle, 5 );
		MID_MECH_DEPLOY_IND_1.Connect( pBundle, 6 );
		AFT_MECH_DEPLOY_IND_1.Connect( pBundle, 7 );
		SHLD_MECH_STOW_IND_2.Connect( pBundle, 8 );
		FWD_MECH_STOW_IND_2.Connect( pBundle, 9 );
		MID_MECH_STOW_IND_2.Connect( pBundle, 10 );
		AFT_MECH_STOW_IND_2.Connect( pBundle, 11 );
		SHLD_MECH_DEPLOY_IND_2.Connect( pBundle, 12 );
		FWD_MECH_DEPLOY_IND_2.Connect( pBundle, 13 );
		MID_MECH_DEPLOY_IND_2.Connect( pBundle, 14 );
		AFT_MECH_DEPLOY_IND_2.Connect( pBundle, 15 );

		pBundle = BundleManager()->CreateBundle( "STBD_MPM_PWR", 16 );
		MPM_MOTOR_1_PWR.Connect( pBundle, 0 );
		MPM_MOTOR_2_PWR.Connect( pBundle, 1 );
		MPM_SHOULDER_1_IND_PWR.Connect( pBundle, 2 );
		MPM_SHOULDER_2_IND_PWR.Connect( pBundle, 3 );
		MPM_FWD_1_IND_PWR.Connect( pBundle, 4 );
		MPM_FWD_2_IND_PWR.Connect( pBundle, 5 );
		MPM_MID_1_IND_PWR.Connect( pBundle, 6 );
		MPM_MID_2_IND_PWR.Connect( pBundle, 7 );
		MPM_AFT_1_IND_PWR.Connect( pBundle, 8 );
		MPM_AFT_2_IND_PWR.Connect( pBundle, 9 );

		pBundle = BundleManager()->CreateBundle( "FWD_MRL_IND", 16 );
		FWD_MRL_LATCH_IND_1.Connect( pBundle, 6 );
		FWD_MRL_RELEASE_IND_1.Connect( pBundle, 7 );
		FWD_MRL_LATCH_IND_2.Connect( pBundle, 8 );
		FWD_MRL_RELEASE_IND_2.Connect( pBundle, 9 );
		FWD_RETNN_RFL_1.Connect( pBundle, 10 );
		FWD_RETNN_RFL_2.Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle( "MID_MRL_IND", 16 );
		MID_MRL_LATCH_IND_1.Connect( pBundle, 6 );
		MID_MRL_RELEASE_IND_1.Connect( pBundle, 7 );
		MID_MRL_LATCH_IND_2.Connect( pBundle, 8 );
		MID_MRL_RELEASE_IND_2.Connect( pBundle, 9 );
		MID_RETNN_RFL_1.Connect( pBundle, 10 );
		MID_RETNN_RFL_2.Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle( "AFT_MRL_IND", 16 );
		AFT_MRL_LATCH_IND_1.Connect( pBundle, 6 );
		AFT_MRL_RELEASE_IND_1.Connect( pBundle, 7 );
		AFT_MRL_LATCH_IND_2.Connect( pBundle, 8 );
		AFT_MRL_RELEASE_IND_2.Connect( pBundle, 9 );
		AFT_RETNN_RFL_1.Connect( pBundle, 10 );
		AFT_RETNN_RFL_2.Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle( "FWD_MRL_PWR", 16 );
		FWD_MRL_MOTOR_1_PWR.Connect( pBundle, 6 );
		FWD_MRL_MOTOR_2_PWR.Connect( pBundle, 7 );
		FWD_MRL_IND_1_PWR.Connect( pBundle, 8 );
		FWD_MRL_IND_2_PWR.Connect( pBundle, 9 );
		FWD_RETNN_RFL_1_PWR.Connect( pBundle, 10 );
		FWD_RETNN_RFL_2_PWR.Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle( "MID_MRL_PWR", 16 );
		MID_MRL_MOTOR_1_PWR.Connect( pBundle, 6 );
		MID_MRL_MOTOR_2_PWR.Connect( pBundle, 7 );
		MID_MRL_IND_1_PWR.Connect( pBundle, 8 );
		MID_MRL_IND_2_PWR.Connect( pBundle, 9 );
		MID_RETNN_RFL_1_PWR.Connect( pBundle, 10 );
		MID_RETNN_RFL_2_PWR.Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle( "AFT_MRL_PWR", 16 );
		AFT_MRL_MOTOR_1_PWR.Connect( pBundle, 6 );
		AFT_MRL_MOTOR_2_PWR.Connect( pBundle, 7 );
		AFT_MRL_IND_1_PWR.Connect( pBundle, 8 );
		AFT_MRL_IND_2_PWR.Connect( pBundle, 9 );
		AFT_RETNN_RFL_1_PWR.Connect( pBundle, 10 );
		AFT_RETNN_RFL_2_PWR.Connect( pBundle, 11 );
	}

	if ((MRL[0] + MRL[1] + MRL[2]) == 0.0) OnMRLLatched();
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
	if (IsMRLLatched())
	{
		// check for release
		if (AllMRLLatchesOpen()) OnMRLReleased();
	}
	else
	{
		// check for latch
		if (!AllMRLLatchesOpen()) OnMRLLatched();
	}
	/*if ((MRL[0] + MRL[1] + MRL[2]) == 3.0) OnMRLReleased();
	else if ((MRL[0] + MRL[1] + MRL[2]) == 0.0) OnMRLLatched();*/

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

void MPM::CheckDoubleAttach( VESSEL* vessel, bool attached )
{
	if((attachedPayload && attachedPayload==vessel) || (hAttach && vessel->GetHandle()==STS()->GetAttachmentStatus(hAttach))) doubleAttached=attached;
}

void MPM::RunMicroswitches( void )
{
	if (Rollout == 1.0)
	{
		SHLD_MECH_STOW_IND_1.ResetLine();

		if (MPM_SHOULDER_1_IND_PWR) SHLD_MECH_DEPLOY_IND_1.SetLine();
		else SHLD_MECH_DEPLOY_IND_1.ResetLine();

		SHLD_MECH_STOW_IND_2.ResetLine();

		if (MPM_SHOULDER_2_IND_PWR) SHLD_MECH_DEPLOY_IND_2.SetLine();
		else SHLD_MECH_DEPLOY_IND_2.ResetLine();

		FWD_MECH_STOW_IND_1.ResetLine();

		if (MPM_FWD_1_IND_PWR) FWD_MECH_DEPLOY_IND_1.SetLine();
		else FWD_MECH_DEPLOY_IND_1.ResetLine();

		FWD_MECH_STOW_IND_2.ResetLine();

		if (MPM_FWD_2_IND_PWR) FWD_MECH_DEPLOY_IND_2.SetLine();
		else FWD_MECH_DEPLOY_IND_2.ResetLine();

		MID_MECH_STOW_IND_1.ResetLine();

		if (MPM_MID_1_IND_PWR) MID_MECH_DEPLOY_IND_1.SetLine();
		else MID_MECH_DEPLOY_IND_1.ResetLine();

		MID_MECH_STOW_IND_2.ResetLine();

		if (MPM_MID_2_IND_PWR) MID_MECH_DEPLOY_IND_2.SetLine();
		else MID_MECH_DEPLOY_IND_2.ResetLine();

		AFT_MECH_STOW_IND_1.ResetLine();

		if (MPM_AFT_1_IND_PWR) AFT_MECH_DEPLOY_IND_1.SetLine();
		else AFT_MECH_DEPLOY_IND_1.ResetLine();

		AFT_MECH_STOW_IND_2.ResetLine();

		if (MPM_AFT_2_IND_PWR) AFT_MECH_DEPLOY_IND_2.SetLine();
		else AFT_MECH_DEPLOY_IND_2.ResetLine();
	}
	else if (Rollout == 0.0)
	{
		if (MPM_SHOULDER_1_IND_PWR) SHLD_MECH_STOW_IND_1.SetLine();
		else SHLD_MECH_STOW_IND_1.ResetLine();

		SHLD_MECH_DEPLOY_IND_1.ResetLine();

		if (MPM_SHOULDER_2_IND_PWR) SHLD_MECH_STOW_IND_2.SetLine();
		else SHLD_MECH_STOW_IND_2.ResetLine();

		SHLD_MECH_DEPLOY_IND_2.ResetLine();

		if (MPM_FWD_1_IND_PWR) FWD_MECH_STOW_IND_1.SetLine();
		else FWD_MECH_STOW_IND_1.ResetLine();

		FWD_MECH_DEPLOY_IND_1.ResetLine();

		if (MPM_FWD_2_IND_PWR) FWD_MECH_STOW_IND_2.SetLine();
		else FWD_MECH_STOW_IND_2.ResetLine();

		FWD_MECH_DEPLOY_IND_2.ResetLine();

		if (MPM_MID_1_IND_PWR) MID_MECH_STOW_IND_1.SetLine();
		else MID_MECH_STOW_IND_1.ResetLine();

		MID_MECH_DEPLOY_IND_1.ResetLine();

		if (MPM_MID_2_IND_PWR) MID_MECH_STOW_IND_2.SetLine();
		else MID_MECH_STOW_IND_2.ResetLine();

		MID_MECH_DEPLOY_IND_2.ResetLine();

		if (MPM_AFT_1_IND_PWR) AFT_MECH_STOW_IND_1.SetLine();
		else AFT_MECH_STOW_IND_1.ResetLine();

		AFT_MECH_DEPLOY_IND_1.ResetLine();

		if (MPM_AFT_2_IND_PWR) AFT_MECH_STOW_IND_2.SetLine();
		else AFT_MECH_STOW_IND_2.ResetLine();

		AFT_MECH_DEPLOY_IND_2.ResetLine();
	}
	else
	{
		SHLD_MECH_STOW_IND_1.ResetLine();
		SHLD_MECH_DEPLOY_IND_1.ResetLine();
		SHLD_MECH_STOW_IND_2.ResetLine();
		SHLD_MECH_DEPLOY_IND_2.ResetLine();
		FWD_MECH_STOW_IND_1.ResetLine();
		FWD_MECH_DEPLOY_IND_1.ResetLine();
		FWD_MECH_STOW_IND_2.ResetLine();
		FWD_MECH_DEPLOY_IND_2.ResetLine();
		MID_MECH_STOW_IND_1.ResetLine();
		MID_MECH_DEPLOY_IND_1.ResetLine();
		MID_MECH_STOW_IND_2.ResetLine();
		MID_MECH_DEPLOY_IND_2.ResetLine();
		AFT_MECH_STOW_IND_1.ResetLine();
		AFT_MECH_DEPLOY_IND_1.ResetLine();
		AFT_MECH_STOW_IND_2.ResetLine();
		AFT_MECH_DEPLOY_IND_2.ResetLine();
	}


	if (MRL[0] == 1.0)
	{
		FWD_MRL_LATCH_IND_1.ResetLine();

		if (FWD_MRL_IND_1_PWR) FWD_MRL_RELEASE_IND_1.SetLine();
		else FWD_MRL_RELEASE_IND_1.ResetLine();
		
		FWD_MRL_LATCH_IND_2.ResetLine();
		
		if (FWD_MRL_IND_2_PWR) FWD_MRL_RELEASE_IND_2.SetLine();
		else FWD_MRL_RELEASE_IND_2.ResetLine();
	}
	else if (MRL[0] == 0.0)
	{
		if (FWD_MRL_IND_1_PWR) FWD_MRL_LATCH_IND_1.SetLine();
		else FWD_MRL_LATCH_IND_1.ResetLine();

		FWD_MRL_RELEASE_IND_1.ResetLine();

		if (FWD_MRL_IND_2_PWR) FWD_MRL_LATCH_IND_2.SetLine();
		else FWD_MRL_LATCH_IND_2.ResetLine();

		FWD_MRL_RELEASE_IND_2.ResetLine();
	}
	else
	{
		FWD_MRL_LATCH_IND_1.ResetLine();
		FWD_MRL_RELEASE_IND_1.ResetLine();
		FWD_MRL_LATCH_IND_2.ResetLine();
		FWD_MRL_RELEASE_IND_2.ResetLine();
	}

	if (MRL[1] == 1.0)
	{
		MID_MRL_LATCH_IND_1.ResetLine();

		if (MID_MRL_IND_1_PWR) MID_MRL_RELEASE_IND_1.SetLine();
		else MID_MRL_RELEASE_IND_1.ResetLine();
		
		MID_MRL_LATCH_IND_2.ResetLine();
		
		if (MID_MRL_IND_2_PWR) MID_MRL_RELEASE_IND_2.SetLine();
		else MID_MRL_RELEASE_IND_2.ResetLine();
	}
	else if (MRL[1] == 0.0)
	{
		if (MID_MRL_IND_1_PWR) MID_MRL_LATCH_IND_1.SetLine();
		else MID_MRL_LATCH_IND_1.ResetLine();

		MID_MRL_RELEASE_IND_1.ResetLine();

		if (MID_MRL_IND_2_PWR) MID_MRL_LATCH_IND_2.SetLine();
		else MID_MRL_LATCH_IND_2.ResetLine();

		MID_MRL_RELEASE_IND_2.ResetLine();
	}
	else
	{
		MID_MRL_LATCH_IND_1.ResetLine();
		MID_MRL_RELEASE_IND_1.ResetLine();
		MID_MRL_LATCH_IND_2.ResetLine();
		MID_MRL_RELEASE_IND_2.ResetLine();
	}

	if (MRL[2] == 1.0)
	{
		AFT_MRL_LATCH_IND_1.ResetLine();

		if (AFT_MRL_IND_1_PWR) AFT_MRL_RELEASE_IND_1.SetLine();
		else AFT_MRL_RELEASE_IND_1.ResetLine();
		
		AFT_MRL_LATCH_IND_2.ResetLine();
		
		if (AFT_MRL_IND_2_PWR) AFT_MRL_RELEASE_IND_2.SetLine();
		else AFT_MRL_RELEASE_IND_2.ResetLine();
	}
	else if (MRL[2] == 0.0)
	{
		if (AFT_MRL_IND_1_PWR) AFT_MRL_LATCH_IND_1.SetLine();
		else AFT_MRL_LATCH_IND_1.ResetLine();

		AFT_MRL_RELEASE_IND_1.ResetLine();

		if (AFT_MRL_IND_2_PWR) AFT_MRL_LATCH_IND_2.SetLine();
		else AFT_MRL_LATCH_IND_2.ResetLine();

		AFT_MRL_RELEASE_IND_2.ResetLine();
	}
	else
	{
		AFT_MRL_LATCH_IND_1.ResetLine();
		AFT_MRL_RELEASE_IND_1.ResetLine();
		AFT_MRL_LATCH_IND_2.ResetLine();
		AFT_MRL_RELEASE_IND_2.ResetLine();
	}
	return;
}

void MPM::SetRFL( bool fwd, bool mid, bool aft )
{
	if (fwd)
	{
		if (FWD_RETNN_RFL_1_PWR) FWD_RETNN_RFL_1.SetLine();
		else FWD_RETNN_RFL_1.ResetLine();

		if (FWD_RETNN_RFL_2_PWR) FWD_RETNN_RFL_2.SetLine();
		else FWD_RETNN_RFL_2.ResetLine();
	}
	else
	{
		FWD_RETNN_RFL_1.ResetLine();
		FWD_RETNN_RFL_2.ResetLine();
	}

	if (mid)
	{
		if (MID_RETNN_RFL_1_PWR) MID_RETNN_RFL_1.SetLine();
		else MID_RETNN_RFL_1.ResetLine();

		if (MID_RETNN_RFL_2_PWR) MID_RETNN_RFL_2.SetLine();
		else MID_RETNN_RFL_2.ResetLine();
	}
	else
	{
		MID_RETNN_RFL_1.ResetLine();
		MID_RETNN_RFL_2.ResetLine();
	}

	if (aft)
	{
		if (AFT_RETNN_RFL_1_PWR) AFT_RETNN_RFL_1.SetLine();
		else AFT_RETNN_RFL_1.ResetLine();

		if (AFT_RETNN_RFL_2_PWR) AFT_RETNN_RFL_2.SetLine();
		else AFT_RETNN_RFL_2.ResetLine();
	}
	else
	{
		AFT_RETNN_RFL_1.ResetLine();
		AFT_RETNN_RFL_2.ResetLine();
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

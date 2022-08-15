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
2022/08/05   GLS
********************************************/
#include "MPM.h"
#include "Atlantis.h"
#include "..\CommonDefs.h"
#include "meshres_MPM_Port.h"
#include "meshres_MPM_Starboard.h"
#include <MathSSV.h>


const static char* MESHNAME_MPM_PORT = "SSV\\MPM_Port";
const static char* MESHNAME_MPM_STBD = "SSV\\MPM_Starboard";


MPM::MPM( AtlantisSubsystemDirector *_director, const std::string &_ident, const string& _attachID, bool _portside, double latchmaxdistance, double latchmaxangle )
	: LatchSystem( _director, _ident, _attachID, latchmaxdistance, latchmaxangle ), portside(_portside)
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
	if (portside) pBundle = BundleManager()->CreateBundle( "PORT_MPM_MRL", 16 );
	else pBundle = BundleManager()->CreateBundle( "STBD_MPM_MRL", 16 );
	Release.Connect(pBundle, 0);
	Latch.Connect(pBundle, 1);
	for(int i=0;i<3;i++) MRL_Rel_Microswitches[i].Connect(pBundle, i+2);
	for(int i=0;i<3;i++) MRL_RTL_Microswitches[i].Connect(pBundle, i+5);
	for(int i=0;i<3;i++) MRL_Lat_Microswitches[i].Connect(pBundle, i+8);
	MRL_Released.Connect(pBundle, 11);
	MRL_Latched.Connect(pBundle, 12);

	if (portside) pBundle = BundleManager()->CreateBundle( "PORT_MPM", 16 );
	else pBundle = BundleManager()->CreateBundle( "STBD_MPM", 16 );
	Deploy.Connect(pBundle, 0);
	Stow.Connect(pBundle, 1);
	Deployed.Connect(pBundle, 2);
	Stowed.Connect(pBundle, 3);

	pBundle = BundleManager()->CreateBundle( "RadiatorControlSW", 10 );
	PLBayMECHPWRSYS_ON[0].Connect( pBundle, 0 );
	PLBayMECHPWRSYS_ON[1].Connect( pBundle, 1 );

	RunMicroswitches();
	return;
}

void MPM::OnPreStep(double simt, double simdt, double mjd)
{
	LatchSystem::OnPreStep( simt, simdt, mjd );

	double dpos = simdt * MPM_DEPLOY_SPEED * (((int)PLBayMECHPWRSYS_ON[0] + (int)PLBayMECHPWRSYS_ON[1]) * 0.5) * (Deploy - Stow);
	if (dpos != 0.0)
	{
		Rollout = range( 0.0, Rollout + dpos, 1.0 );
		STS()->SetAnimation( anim_mpm, Rollout );
		mpm_moved = true;
	}
	else mpm_moved = false;

	for (int i = 0;i < 3; i++)
	{
		dpos = simdt * MRL_LATCH_SPEED * (((int)PLBayMECHPWRSYS_ON[0] + (int)PLBayMECHPWRSYS_ON[1]) * 0.5) * (Release - Latch);
		MRL[i] = range( 0.0, MRL[i] + dpos, 1.0 );
	}

	if ((MRL[0] + MRL[1] + MRL[2]) == 3.0) OnMRLReleased();
	else if ((MRL[0] + MRL[1] + MRL[2]) == 0.0) OnMRLLatched();

	RunMicroswitches();
	return;
}

bool MPM::OnParseLine(const char* line)
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

void MPM::OnSaveState(FILEHANDLE scn) const
{
	char cbuf[255];

	oapiWriteScenario_float( scn, "MPM_ROLLOUT", Rollout );

	sprintf_s( cbuf, 255, "%f %f %f", MRL[0], MRL[1], MRL[2] );
	oapiWriteScenario_string( scn, "MPM_LATCHES", cbuf );

	LatchSystem::OnSaveState( scn );
}

void MPM::AddMesh()
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

void MPM::OnMRLLatched()
{
}

void MPM::OnMRLReleased()
{
}

void MPM::OnAttach()
{
}

void MPM::OnDetach()
{
	doubleAttached=false;
}

void MPM::CheckDoubleAttach(VESSEL* vessel, bool attached)
{
	if((attachedPayload && attachedPayload==vessel) || (hAttach && vessel->GetHandle()==STS()->GetAttachmentStatus(hAttach))) doubleAttached=attached;
};

void MPM::RunMicroswitches( void )
{
	if (Rollout == 1.0)
	{
		Deployed.SetLine();
		Stowed.ResetLine();
	}
	else if (Rollout == 0.0)
	{
		Deployed.ResetLine();
		Stowed.SetLine();
	}
	else
	{
		Deployed.ResetLine();
		Stowed.ResetLine();
	}


	for (int i = 0;i < 3; i++)
	{
		if (MRL[i] == 1.0)
		{
			MRL_Rel_Microswitches[i].SetLine();
			MRL_Lat_Microswitches[i].ResetLine();
		}
		else if (MRL[i] == 0.0)
		{
			MRL_Rel_Microswitches[i].ResetLine();
			MRL_Lat_Microswitches[i].SetLine();
		}
		else
		{
			MRL_Rel_Microswitches[i].ResetLine();
			MRL_Lat_Microswitches[i].ResetLine();
		}
	}

	// HACK temporary MRL position output mux
	if ((MRL[0] + MRL[1] + MRL[2]) == 3.0)
	{
		MRL_Released.SetLine();
		MRL_Latched.ResetLine();
	}
	else if ((MRL[0] + MRL[1] + MRL[2]) == 0.0)
	{
		MRL_Released.ResetLine();
		MRL_Latched.SetLine();
	}
	else
	{
		MRL_Released.ResetLine();
		MRL_Latched.ResetLine();
	}
	return;
}
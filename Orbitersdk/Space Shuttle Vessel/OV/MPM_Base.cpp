#include "MPM_Base.h"
#include "Atlantis.h"
#include "../CommonDefs.h"


const static char* MESHNAME_MPM_PORT = "SSV\\MPM_Port";
const static char* MESHNAME_MPM_STBD = "SSV\\MPM_Starboard";


MPM_Base::MPM_Base( bool _portside ):portside(_portside)
{
	mesh_index_MPM = MESH_UNDEFINED;
	hMesh_MPM = oapiLoadMeshGlobal( _portside ? MESHNAME_MPM_PORT : MESHNAME_MPM_STBD );
}

MPM_Base::~MPM_Base()
{
}

void MPM_Base::AddMesh( const Atlantis* sts )
{
	VECTOR3 ofs = sts->GetOrbiterCoGOffset();
	mesh_index_MPM = sts->AddMesh( hMesh_MPM, &ofs );
	sts->SetMeshVisibilityMode( mesh_index_MPM, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
	return;
}
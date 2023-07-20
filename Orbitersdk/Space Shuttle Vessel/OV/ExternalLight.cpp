#include "ExternalLight.h"
#include "Atlantis.h"
#include <Orbitersdk.h>
#include <cassert>


constexpr unsigned int MAX_LIGHT_VTX = 128;
constexpr double LIGHT_RISE_RATE = 1.0 / 150.0;// light rise rate when turned on (2-3 minutes ~ 150s) [s]

//constexpr COLOUR4 diffuse_MetalHalide = {0.949f, 0.988f, 1.0f, 1.0f};// RGB for metal halide but it doesn't quite match up with actual photos
constexpr COLOUR4 diffuse_HgVapor = {0.847f, 0.968f, 1.0f, 1.0f};// RGB for mercury vapor, this better matches photos
constexpr COLOUR4 diffuse_Incandescent = {1.0f, 0.839f, 0.666f, 1.0f};
constexpr COLOUR4 diffuse_LED = {1.0f, 1.0f, 1.0f, 1.0f};
constexpr COLOUR4 specular = {0.0f, 0.0f, 0.0f, 1.0f};
constexpr COLOUR4 ambient = {0.0f, 0.0f, 0.0f, 1.0f};


ExternalLight::ExternalLight( Atlantis* sts, const VECTOR3& pos, const VECTOR3& dir, const float defaultoffsetU, const float defaultoffsetV, const double range, const double att0, const double att1, const double att2, const double umbra, const double penumbra, const EXTERNAL_LIGHT_TYPE type ):
	sts(sts), position(pos), type(type), state(-1), next_state(0), mesh(-1), grpIndex(-1), offsetU{defaultoffsetU, 0.0f, 0.0f}, offsetV{defaultoffsetV, 0.0f, 0.0f}, curlevel(1.0f), statelevel{0.0f, 0.0f}
{
	COLOUR4 diffuse = diffuse_HgVapor;
	if (type == INCANDESCENT) diffuse = diffuse_Incandescent;
	else if (type == LED) diffuse = diffuse_LED;

	Light = sts->AddSpotLight( position, dir, range, att0, att1, att2, umbra, penumbra, diffuse, specular, ambient );
	return;
}

ExternalLight::~ExternalLight()
{
	sts->DelLightEmitter( Light );
	return;
}

void ExternalLight::DefineState( const unsigned int state, const float stateoffsetU, const float stateoffsetV, const float level, discsignals::DiscreteBundle* pBundle, const unsigned short usLine )
{
	assert( (state > 0) && (state < 3) && "ExternalLight::DefineState.state" );
	assert( (level >= 0.0) && (level <= 1.0) && "ExternalLight::DefineState.level" );

	offsetU[state] = stateoffsetU;
	offsetV[state] = stateoffsetV;
	statelevel[state - 1] = level;
	input[state - 1].Connect( pBundle, usLine );
	return;
}

void ExternalLight::TimeStep( const double dt )
{
	// determine state
	if (input[0].IsSet()) next_state = 1;
	else if (input[1].IsSet()) next_state = 2;
	else next_state = 0;

	if (next_state != state)
	{
		UpdateUV();
	}

	// determine light level
	if (next_state == 1)
	{
		if (state == 0) Light->Activate( true );

		if (curlevel != statelevel[0])
		{
			float tmp = (type == HG_VAPOR) ? static_cast<float>(min(curlevel + (dt * LIGHT_RISE_RATE),statelevel[0])) : statelevel[0];
			Light->SetIntensity( tmp );
			curlevel = tmp;
		}
	}
	else if (next_state == 2)
	{
		if (state == 0) Light->Activate( true );

		if (curlevel != statelevel[1])
		{
			float tmp = (type == HG_VAPOR) ? static_cast<float>(min(curlevel + (dt * LIGHT_RISE_RATE),statelevel[1])) : statelevel[1];
			Light->SetIntensity( tmp );
			curlevel = tmp;
		}
	}
	else /*if (next_state == 0)*/
	{
		if (state != 0)
		{
			Light->Activate( false );
			curlevel = 0;
		}
	}

	state = next_state;
	return;
}

void ExternalLight::ShiftLightPosition( const VECTOR3& shift )
{
	position += shift;
	Light->SetPosition( position );
	return;
}

void ExternalLight::UpdateLightPosition( const VECTOR3& pos )
{
	position = pos;
	Light->SetPosition( position );
	return;
}

void ExternalLight::UpdateLightDirection( const VECTOR3& dir )
{
	Light->SetDirection( dir );
	return;
}

void ExternalLight::UpdateUV( void )
{
	if (sts->Get_vis() == 0) return;
	MESHHANDLE Template = sts->GetMeshTemplate( mesh );
	MESHGROUPEX* mg = oapiMeshGroupEx( Template, grpIndex );
	DEVMESHHANDLE hDevmesh = sts->GetDevMesh( sts->Get_vis(), mesh );

	assert( (mg->nVtx <= MAX_LIGHT_VTX) && "ExternalLight::UpdateUV.mg->nVtx" );
	static NTVERTEX Vtx[MAX_LIGHT_VTX];
	for (unsigned short i = 0; i < mg->nVtx; i++)
	{
		Vtx[i].tu = mg->Vtx[i].tu + (offsetU[next_state] - offsetU[0]);
		Vtx[i].tv = mg->Vtx[i].tv + (offsetV[next_state] - offsetV[0]);
	}

	GROUPEDITSPEC grpSpec;
	grpSpec.flags = GRPEDIT_VTXTEX;
	grpSpec.Vtx = Vtx;
	grpSpec.nVtx = mg->nVtx;
	grpSpec.vIdx = NULL;

	oapiEditMeshGroup( hDevmesh, grpIndex, &grpSpec );
	return;
}

void ExternalLight::DefineMeshGroup( UINT _mesh, UINT _grpIndex )
{
	mesh = _mesh;
	grpIndex = _grpIndex;
	return;
}

void ExternalLight::VisualCreated( void )
{
	UpdateUV();
	return;
}

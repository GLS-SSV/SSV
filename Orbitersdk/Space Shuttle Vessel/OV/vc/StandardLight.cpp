/******* SSV File Modification Notice *******
Date         Developer
2020/05/08   GLS
2020/06/20   GLS
2021/01/20   GLS
2021/06/18   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/07/24   GLS
2022/08/05   GLS
********************************************/
#include "StandardLight.h"
#include "../Atlantis.h"
#include <cassert>


constexpr unsigned int MAX_LIGHT_VTX = 64;

namespace vc
{
	StandardSingleLight::StandardSingleLight( Atlantis* _sts, const string& _ident ):BasicLight( _sts, _ident )
	{
		for (int i = 0; i < 2; i++)
		{
			offsetU[i] = 0.0;
			offsetV[i] = 0.0;
		}
	}

	StandardSingleLight::~StandardSingleLight()
	{
	}

	void StandardSingleLight::SetDefaultState( unsigned int _state )
	{
		assert( (_state < 2) && "StandardSingleLight::SetDefaultState._state" );
		default_state = _state;
		state = _state;
		return;
	}

	void StandardSingleLight::SetStateOffset( unsigned int _state, float _U, float _V )
	{
		assert( (_state < 2) && "StandardSingleLight::SetStateOffset._state" );
		offsetU[_state] = _U;
		offsetV[_state] = _V;
		return;
	}

	bool StandardSingleLight::ConnectLight( unsigned short usPort, DiscreteBundle* pBundle, unsigned short usLine )
	{
		assert( (usPort < 2) && "StandardSingleLight::ConnectLight.usPort" );
		input[usPort].Connect( pBundle, usLine );
		return true;
	}

	void StandardSingleLight::OnPostStep( double simt, double simdt, double mjd )
	{
		unsigned short tmp;

		if (input[0].IsSet() || input[1].IsSet()) tmp = 1;
		else tmp = 0;

		if (tmp != state)
		{
			next_state = tmp;
			UpdateUV();
		}
		return;
	}

	void StandardSingleLight::UpdateUV( void )
	{
		if (STS()->Get_vis() == 0) return;
		MESHHANDLE panelTemplate = STS()->GetMeshTemplate( panelmesh );
		MESHGROUPEX* mg = oapiMeshGroupEx( panelTemplate, grpIndex );
		DEVMESHHANDLE hDevpanelmesh = STS()->GetDevMesh( STS()->Get_vis(), panelmesh );

		assert( (mg->nVtx <= MAX_LIGHT_VTX) && "StandardSingleLight::UpdateUV.mg->nVtx" );
		static NTVERTEX Vtx[MAX_LIGHT_VTX];
		for (unsigned short i = 0; i < mg->nVtx; i++)
		{
			Vtx[i].tu = mg->Vtx[i].tu + (offsetU[next_state] - offsetU[default_state]);
			Vtx[i].tv = mg->Vtx[i].tv + (offsetV[next_state] - offsetV[default_state]);
		}
		state = next_state;

		GROUPEDITSPEC grpSpec;
		grpSpec.flags = GRPEDIT_VTXTEX;
		grpSpec.Vtx = Vtx;
		grpSpec.nVtx = mg->nVtx;
		grpSpec.vIdx = NULL;

		oapiEditMeshGroup( hDevpanelmesh, grpIndex, &grpSpec );
		return;
	}

	void StandardSingleLight::DefineMeshGroup( UINT _panelmesh, UINT _grpIndex )
	{
		panelmesh = _panelmesh;
		grpIndex = _grpIndex;
		return;
	}

	void StandardSingleLight::VisualCreated( void )
	{
		state = default_state;// return state to default
		UpdateUV();
		return;
	}

	StandardDoubleLight::StandardDoubleLight( Atlantis* _sts, const string& _ident ):BasicLight( _sts, _ident )
	{
		for (int i = 0; i < 4; i++)
		{
			offsetU[i] = 0.0;
			offsetV[i] = 0.0;
		}
	}

	StandardDoubleLight::~StandardDoubleLight()
	{
	}

	void StandardDoubleLight::SetDefaultState( unsigned int _state )
	{
		assert( (_state < 4) && "StandardDoubleLight::SetDefaultState._state" );
		default_state = _state;
		state = _state;
		return;
	}

	void StandardDoubleLight::SetStateOffset( unsigned int _state, float _U, float _V )
	{
		assert( (_state < 4) && "StandardDoubleLight::SetStateOffset._state" );
		offsetU[_state] = _U;
		offsetV[_state] = _V;
		return;
	}

	bool StandardDoubleLight::ConnectLight( unsigned short usPort, DiscreteBundle* pBundle, unsigned short usLine )
	{
		assert( (usPort < 4) && "StandardDoubleLight::ConnectLight.usPort" );
		input[usPort].Connect( pBundle, usLine );
		return true;
	}

	void StandardDoubleLight::OnPostStep( double simt, double simdt, double mjd )
	{
		unsigned short tmp;

		if (input[0].IsSet() || input[1].IsSet())
		{
			if (input[2].IsSet() || input[3].IsSet()) tmp = 3;
			else tmp = 1;
		}
		else
		{
			if (input[2].IsSet() || input[3].IsSet()) tmp = 2;
			else tmp = 0;
		}

		if (tmp != state)
		{
			next_state = tmp;
			UpdateUV();
		}
		return;
	}

	void StandardDoubleLight::UpdateUV( void )
	{
		if (STS()->Get_vis() == 0) return;
		MESHHANDLE panelTemplate = STS()->GetMeshTemplate( panelmesh );
		MESHGROUPEX* mg = oapiMeshGroupEx( panelTemplate, grpIndex );
		DEVMESHHANDLE hDevpanelmesh = STS()->GetDevMesh( STS()->Get_vis(), panelmesh );

		assert( (mg->nVtx <= MAX_LIGHT_VTX) && "StandardDoubleLight::UpdateUV.mg->nVtx" );
		static NTVERTEX Vtx[MAX_LIGHT_VTX];
		for (unsigned short i = 0; i < mg->nVtx; i++)
		{
			Vtx[i].tu = mg->Vtx[i].tu + (offsetU[next_state] - offsetU[default_state]);
			Vtx[i].tv = mg->Vtx[i].tv + (offsetV[next_state] - offsetV[default_state]);
		}
		state = next_state;

		GROUPEDITSPEC grpSpec;
		grpSpec.flags = GRPEDIT_VTXTEX;
		grpSpec.Vtx = Vtx;
		grpSpec.nVtx = mg->nVtx;
		grpSpec.vIdx = NULL;

		oapiEditMeshGroup( hDevpanelmesh, grpIndex, &grpSpec );
		return;
	}

	void StandardDoubleLight::DefineMeshGroup( UINT _panelmesh, UINT _grpIndex )
	{
		panelmesh = _panelmesh;
		grpIndex = _grpIndex;
		return;
	}

	void StandardDoubleLight::VisualCreated( void )
	{
		state = default_state;// return state to default
		UpdateUV();
		return;
	}
}

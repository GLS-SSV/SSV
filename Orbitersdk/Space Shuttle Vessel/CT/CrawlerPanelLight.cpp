/******* SSV File Modification Notice *******
Date         Developer
2020/05/08   GLS
2020/06/14   GLS
2020/06/20   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "CrawlerPanelLight.h"
#include "Crawler.h"
#include <cassert>


namespace vc
{
	CrawlerPanelLight::CrawlerPanelLight( Crawler* _v, const string& _ident ):BasicVCComponent( _v, _ident )
	{
		state = 0;
		next_state = 0;
		default_state = 0;

		for (int i = 0; i < 2; i++)
		{
			offsetU[i] = 0.0;
			offsetV[i] = 0.0;
		}
	}

	CrawlerPanelLight::~CrawlerPanelLight()
	{
	}

	void CrawlerPanelLight::SetDefaultState( unsigned int _state )
	{
		assert( (_state < 2) && "CrawlerPanelLight::SetDefaultState._state" );
		default_state = _state;
		state = _state;
		return;
	}

	void CrawlerPanelLight::SetStateOffset( unsigned int _state, float _U, float _V )
	{
		assert( (_state < 2) && "CrawlerPanelLight::SetStateOffset._state" );
		offsetU[_state] = _U;
		offsetV[_state] = _V;
		return;
	}

	bool CrawlerPanelLight::ConnectLight( unsigned short usPort, DiscreteBundle* pBundle, unsigned short usLine )
	{
		assert( (usPort < 2) && "CrawlerPanelLight::ConnectLight.usPort" );
		input[usPort].Connect( pBundle, usLine );
		return true;
	}

	void CrawlerPanelLight::OnPostStep( double simt, double simdt, double mjd )
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

	void CrawlerPanelLight::UpdateUV( void )
	{
		if (V()->vccVis == 0) return;
		MESHHANDLE panelTemplate = V()->GetMeshTemplate( panelmesh );
		MESHGROUPEX* mg = oapiMeshGroupEx( panelTemplate, grpIndex );
		DEVMESHHANDLE hDevpanelmesh = V()->GetDevMesh( V()->vccVis, panelmesh );

		assert( (mg->nVtx <= 32) && "CrawlerPanelLight::UpdateUV.mg->nVtx" );
		static NTVERTEX Vtx[32];
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

	void CrawlerPanelLight::DefineMeshGroup( UINT _panelmesh, UINT _grpIndex )
	{
		panelmesh = _panelmesh;
		grpIndex = _grpIndex;
		return;
	}

	void CrawlerPanelLight::VisualCreated( void )
	{
		state = default_state;// return state to default
		UpdateUV();
		return;
	}

	CrawlerPanelLight2::CrawlerPanelLight2( Crawler* _v, const string& _ident ):BasicVCComponent( _v, _ident )
	{
		state = 0;
		next_state = 0;
		default_state = 0;

		for (int i = 0; i < 4; i++)
		{
			offsetU[i] = 0.0;
			offsetV[i] = 0.0;
		}
	}

	CrawlerPanelLight2::~CrawlerPanelLight2()
	{
	}

	void CrawlerPanelLight2::SetDefaultState( unsigned int _state )
	{
		assert( (_state < 4) && "CrawlerPanelLight2::SetDefaultState._state" );
		default_state = _state;
		state = _state;
		return;
	}

	void CrawlerPanelLight2::SetStateOffset( unsigned int _state, float _U, float _V )
	{
		assert( (_state < 4) && "CrawlerPanelLight2::SetStateOffset._state" );
		offsetU[_state] = _U;
		offsetV[_state] = _V;
		return;
	}

	bool CrawlerPanelLight2::ConnectLight( unsigned short usPort, DiscreteBundle* pBundle, unsigned short usLine )
	{
		assert( (usPort < 4) && "CrawlerPanelLight2::ConnectLight.usPort" );
		input[usPort].Connect( pBundle, usLine );
		return true;
	}

	void CrawlerPanelLight2::OnPostStep( double simt, double simdt, double mjd )
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

	void CrawlerPanelLight2::UpdateUV( void )
	{
		if (V()->vccVis == 0) return;
		MESHHANDLE panelTemplate = V()->GetMeshTemplate( panelmesh );
		MESHGROUPEX* mg = oapiMeshGroupEx( panelTemplate, grpIndex );
		DEVMESHHANDLE hDevpanelmesh = V()->GetDevMesh( V()->vccVis, panelmesh );

		assert( (mg->nVtx <= 32) && "CrawlerPanelLight2::UpdateUV.mg->nVtx" );
		static NTVERTEX Vtx[32];
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

	void CrawlerPanelLight2::DefineMeshGroup( UINT _panelmesh, UINT _grpIndex )
	{
		panelmesh = _panelmesh;
		grpIndex = _grpIndex;
		return;
	}

	void CrawlerPanelLight2::VisualCreated( void )
	{
		state = default_state;// return state to default
		UpdateUV();
		return;
	}
}

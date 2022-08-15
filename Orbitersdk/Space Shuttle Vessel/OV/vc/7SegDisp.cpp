/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2021/01/20   GLS
2021/06/18   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
********************************************/
#include "7SegDisp.h"
#include "../Atlantis.h"
#include <cassert>


namespace vc
{
	constexpr int _7SD_STATE_MAX = 40;

	constexpr float _7SD_U_OFFSET[_7SD_STATE_MAX] = {0.0f, 0.0625f, 0.125f, 0.1875f, 0.25f, 0.3125f, 0.375f, 0.4375f, 0.5f, 0.5625f, 0.625f,
					0.0f, 0.0625f, 0.125f, 0.1875f, 0.25f, 0.3125f, 0.375f, 0.4375f, 0.5f, 0.5625f, 0.625f,
					0.0f, 0.0625f, 0.125f, 0.1875f, 0.25f, 0.3125f, 0.375f, 0.4375f, 0.5f, 0.5625f, 0.625f,
					0.75f, 0.75f, 0.75f,
					0.6875f, 0.6875f, 0.6875f, 0.875f};
	constexpr float _7SD_V_OFFSET[_7SD_STATE_MAX] = {0.125f, 0.125f, 0.125f, 0.125f, 0.125f, 0.125f, 0.125f, 0.125f, 0.125f, 0.125f, 0.125f,
					0.0625f, 0.0625f, 0.0625f, 0.0625f, 0.0625f, 0.0625f, 0.0625f, 0.0625f, 0.0625f, 0.0625f, 0.0625f,
					0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
					0.0625f, 0.125f, 0.0f,
					0.0625f, 0.125f, 0.0f, 0.0f};


	_7SegDisp::_7SegDisp( Atlantis* _sts, const std::string& _ident ):AtlantisVCComponent( _sts, _ident )
	{
		grpIndex.clear();
		//IsNumber.clear();
		//HasDecimalPoint.clear();
		//IsDoubleSign.clear();
		next_state.clear();
		state.clear();
		default_state.clear();
		panelmesh = (UINT)(-1);
	}

	_7SegDisp::~_7SegDisp()
	{
	}

	void _7SegDisp::OnPreStep( double simt, double simdt, double mjd )
	{
		Controller();

		for (unsigned int i = 0; i < state.size(); i++)
		{
			assert( (next_state[i] >= 0) && (next_state[i] < _7SD_STATE_MAX) && "_7SegDisp::OnPreStep.next_state" );

			if (next_state[i] != state[i]) UpdateUV( i );
		}
		return;
	}

	void _7SegDisp::UpdateUV( int component )
	{
		if (STS()->Get_vis() == 0) return;
		MESHHANDLE panelTemplate = STS()->GetMeshTemplate( panelmesh );
		MESHGROUPEX* mg = oapiMeshGroupEx( panelTemplate, grpIndex[component] );
		DEVMESHHANDLE hDevpanelmesh = STS()->GetDevMesh( STS()->Get_vis(), panelmesh );

		assert( (mg->nVtx == 4) && "_7SegDisp::UpdateUV.mg->nVtx" );
		static NTVERTEX Vtx[4];
		for (unsigned short i = 0; i < 4; i++)
		{
			Vtx[i].tu = mg->Vtx[i].tu + (_7SD_U_OFFSET[next_state[component]] - _7SD_U_OFFSET[default_state[component]]);
			Vtx[i].tv = mg->Vtx[i].tv + (_7SD_V_OFFSET[next_state[component]] - _7SD_V_OFFSET[default_state[component]]);
		}
		state[component] = next_state[component];

		GROUPEDITSPEC grpSpec;
		grpSpec.flags = GRPEDIT_VTXTEX;
		grpSpec.Vtx = Vtx;
		grpSpec.nVtx = 4;
		grpSpec.vIdx = NULL;

		oapiEditMeshGroup( hDevpanelmesh, grpIndex[component], &grpSpec );
		return;
	}

	void _7SegDisp::DefineMesh( UINT _panelmesh )
	{
		panelmesh = _panelmesh;
		return;
	}

	void _7SegDisp::DefineComponent( UINT _grpIndex, bool _IsNumber, bool _HasDecimalPoint, bool _IsDoubleSign, int _default_state )
	{
		grpIndex.push_back( _grpIndex );
		//IsNumber.push_back( _IsNumber );
		//HasDecimalPoint.push_back( _HasDecimalPoint );
		//IsDoubleSign.push_back( _IsDoubleSign );
		next_state.push_back( _default_state );
		state.push_back( _default_state );
		default_state.push_back( _default_state );
		return;
	}

	void _7SegDisp::VisualCreated( void )
	{
		state = default_state;// return state to default
		for (unsigned int i = 0; i < grpIndex.size(); i++) UpdateUV( i );
		return;
	}
};
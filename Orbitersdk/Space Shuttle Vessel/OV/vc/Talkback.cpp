/******* SSV File Modification Notice *******
Date         Developer
2020/05/07   GLS
2020/06/14   GLS
2020/06/20   GLS
2021/06/18   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/08/05   GLS
********************************************/
#include "Talkback.h"
#include "../Atlantis.h"
#include "vc_defs.h"
#include <cassert>
#include "..\..\SSVSound.h"


namespace vc
{
	constexpr float TALKBACK_U_OFFSET[19] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.250980f, 0.250980f, 0.0f, 0.250980f, 0.250980f, 0.250980f, 0.250980f, 0.250980f, 0.501961f, 0.501961f, 0.501961f, 0.501961f, 0.501961f};
	constexpr float TALKBACK_V_OFFSET[19] = {0.0f, 0.564706f, 0.282353f, 0.705882f, 0.847059f, 0.423529f, 0.0f, 0.141176f, 0.141176f, 0.282353f, 0.423529f, 0.564706f, 0.705882f, 0.847059f, 0.0f, 0.141176f, 0.282353f, 0.423529f, 0.564706f};


	BasicTalkback::BasicTalkback(Atlantis* _sts, const std::string& _ident)
		: AtlantisVCComponent(_sts, _ident)
	{
		panelmesh = (UINT)(-1);
		usInactiveFlag = TB_BARBERPOLE;
		tkbk_default_state = TB_BARBERPOLE;
	}

	BasicTalkback::~BasicTalkback()
	{
	}

	void BasicTalkback::SetInactiveSegment( unsigned short _usFlag )
	{
		usInactiveFlag = _usFlag;
	}

	void BasicTalkback::SoundOff( void ) const
	{
		PlayVesselWave( STS()->GetSoundID(), TB_OFF_SOUND );
		return;
	}

	void BasicTalkback::SoundOn( void ) const
	{
		PlayVesselWave( STS()->GetSoundID(), TB_ON_SOUND );
		return;
	}


	StandardTalkback2::StandardTalkback2( Atlantis* _sts, const std::string& _ident ):BasicTalkback( _sts, _ident )
	{
		tkbk_state_U = TB_GRAY;
		tkbk_state_L = TB_BARBERPOLE;
		tkbk_next_state_U = TB_GRAY;
		tkbk_next_state_L = TB_BARBERPOLE;
		grpIndex_U = 0;
		grpIndex_L = 0;
		usCover = TB_GRAY;
		flags = TB_BARBERPOLE;
	}

	StandardTalkback2::~StandardTalkback2()
	{
	}

	void StandardTalkback2::OnPostStep( double simt, double simdt, double mjd )
	{
		unsigned short tmp_U;
		unsigned short tmp_L;

		if (input.IsSet())
		{
			tmp_U = flags;
			tmp_L = usCover;
		}
		else
		{
			tmp_U = usCover;
			tmp_L = usInactiveFlag;
		}

		if ((tmp_U != tkbk_state_U) || (tmp_L != tkbk_state_L))
		{
			if (tmp_L == usInactiveFlag) SoundOff();
			else SoundOn();

			tkbk_next_state_U = tmp_U;
			tkbk_next_state_L = tmp_L;
			UpdateUV();
		}
		return;
	}

	void StandardTalkback2::UpdateUV( void )
	{
		// upper
		if (STS()->Get_vis() == 0) return;
		MESHHANDLE panelTemplate = STS()->GetMeshTemplate( panelmesh );
		MESHGROUPEX* mg = oapiMeshGroupEx( panelTemplate, grpIndex_U );
		DEVMESHHANDLE hDevpanelmesh = STS()->GetDevMesh( STS()->Get_vis(), panelmesh );

		assert( (mg->nVtx == 4) && "StandardTalkback2::UpdateUV.mg->nVtx" );
		static NTVERTEX Vtx[4];
		for (unsigned short i = 0; i < 4; i++)
		{
			Vtx[i].tu = mg->Vtx[i].tu + (TALKBACK_U_OFFSET[tkbk_next_state_U] - TALKBACK_U_OFFSET[tkbk_default_state]);
			Vtx[i].tv = mg->Vtx[i].tv + (TALKBACK_V_OFFSET[tkbk_next_state_U] - TALKBACK_V_OFFSET[tkbk_default_state]);
		}
		tkbk_state_U = tkbk_next_state_U;

		GROUPEDITSPEC grpSpec;
		grpSpec.flags = GRPEDIT_VTXTEX;
		grpSpec.Vtx = Vtx;
		grpSpec.nVtx = 4;
		grpSpec.vIdx = NULL;

		oapiEditMeshGroup( hDevpanelmesh, grpIndex_U, &grpSpec );

		// lower
		mg = oapiMeshGroupEx( panelTemplate, grpIndex_L );

		for (unsigned short i = 0; i < 4; i++)
		{
			Vtx[i].tu = mg->Vtx[i].tu + (TALKBACK_U_OFFSET[tkbk_next_state_L] - TALKBACK_U_OFFSET[tkbk_default_state]);
			Vtx[i].tv = mg->Vtx[i].tv + (TALKBACK_V_OFFSET[tkbk_next_state_L] - TALKBACK_V_OFFSET[tkbk_default_state]);
		}
		tkbk_state_L = tkbk_next_state_L;

		grpSpec.Vtx = Vtx;

		oapiEditMeshGroup( hDevpanelmesh, grpIndex_L, &grpSpec );
		return;
	}

	void StandardTalkback2::DefineMeshGroups( UINT _panelmesh, UINT _grpIndex_U, UINT _grpIndex_L )
	{
		assert( (_grpIndex_U != _grpIndex_L) && "StandardTalkback2::DefineMeshGroups._grpIndex" );
		panelmesh = _panelmesh;
		grpIndex_U = _grpIndex_U;
		grpIndex_L = _grpIndex_L;
		return;
	}

	void StandardTalkback2::SetInitialState( unsigned short _usFlag )
	{
		tkbk_default_state = _usFlag;
		tkbk_state_U = _usFlag;
		tkbk_state_L = _usFlag;
		return;
	}

	void StandardTalkback2::SetInput( DiscreteBundle* pBundle, unsigned short usLine, unsigned short usFlag )
	{
		input.Connect( pBundle, usLine );
		flags = usFlag;
		return;
	}

	void StandardTalkback2::SetCoverSegment( unsigned short _usFlag )
	{
		usCover = _usFlag;
		return;
	}

	void StandardTalkback2::VisualCreated( void )
	{
		tkbk_state_U = tkbk_default_state;// return state to default
		tkbk_state_L = tkbk_default_state;// return state to default
		UpdateUV();
		return;
	}


	StandardTalkback3::StandardTalkback3( Atlantis* _sts, const std::string& _ident ):BasicTalkback( _sts, _ident )
	{
		tkbk_state = TB_BARBERPOLE;
		tkbk_next_state = TB_BARBERPOLE;
		grpIndex = 0;
		flags[0] = TB_BARBERPOLE;
		flags[1] = TB_BARBERPOLE;
	}

	StandardTalkback3::~StandardTalkback3()
	{
	}

	void StandardTalkback3::OnPostStep( double simt, double simdt, double mjd )
	{
		unsigned short tmp;

		if (input[0].IsSet())
		{
			if (input[1].IsSet()) tmp = usInactiveFlag;// both on = set inactive
			else tmp = flags[0];// 0 on, 1 off = set 0
		}
		else
		{
			if (input[1].IsSet()) tmp = flags[1];// 0 off, 1 on = set 1
			else tmp = usInactiveFlag;// both off = set inactive
		}

		if (tmp != tkbk_state)
		{
			if (tmp == usInactiveFlag) SoundOff();
			else SoundOn();

			tkbk_next_state = tmp;
			UpdateUV();
		}
		return;
	}

	void StandardTalkback3::UpdateUV( void )
	{
		if (STS()->Get_vis() == 0) return;
		MESHHANDLE panelTemplate = STS()->GetMeshTemplate( panelmesh );
		MESHGROUPEX* mg = oapiMeshGroupEx( panelTemplate, grpIndex );
		DEVMESHHANDLE hDevpanelmesh = STS()->GetDevMesh( STS()->Get_vis(), panelmesh );

		assert( (mg->nVtx == 4) && "StandardTalkback3::UpdateUV.mg->nVtx" );
		static NTVERTEX Vtx[4];
		for (unsigned short i = 0; i < 4; i++)
		{
			Vtx[i].tu = mg->Vtx[i].tu + (TALKBACK_U_OFFSET[tkbk_next_state] - TALKBACK_U_OFFSET[tkbk_default_state]);
			Vtx[i].tv = mg->Vtx[i].tv + (TALKBACK_V_OFFSET[tkbk_next_state] - TALKBACK_V_OFFSET[tkbk_default_state]);
		}
		tkbk_state = tkbk_next_state;

		GROUPEDITSPEC grpSpec;
		grpSpec.flags = GRPEDIT_VTXTEX;
		grpSpec.Vtx = Vtx;
		grpSpec.nVtx = 4;
		grpSpec.vIdx = NULL;

		oapiEditMeshGroup( hDevpanelmesh, grpIndex, &grpSpec );
		return;
	}

	void StandardTalkback3::DefineMeshGroup( UINT _panelmesh, UINT _grpIndex )
	{
		panelmesh = _panelmesh;
		grpIndex = _grpIndex;
		return;
	}

	void StandardTalkback3::SetInitialState( unsigned short _usFlag )
	{
		tkbk_default_state = _usFlag;
		tkbk_state = _usFlag;
		return;
	}

	void StandardTalkback3::SetInput( unsigned short idx, DiscreteBundle* pBundle, unsigned short usLine, unsigned short usFlag )
	{
		assert( (idx < 2) && "StandardTalkback3::SetInput.idx" );
		input[idx].Connect( pBundle, usLine );
		flags[idx]=usFlag;
	}

	void StandardTalkback3::VisualCreated( void )
	{
		tkbk_state = tkbk_default_state;// return state to default
		UpdateUV();
		return;
	}
};
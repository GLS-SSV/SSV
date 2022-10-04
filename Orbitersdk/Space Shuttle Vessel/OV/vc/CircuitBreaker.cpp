/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/03/29   GLS
2020/05/07   GLS
2020/06/20   GLS
2021/01/20   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/09/29   GLS
********************************************/
#include "CircuitBreaker.h"
#include "../Atlantis.h"
#include "../../SSVSound.h"
#include <cassert>


namespace vc
{
	constexpr double CB_MOVEMENT_RANGE = 0.005;// meters
	constexpr double CB_MOVEMENT_TIME = 0.2;// seconds


	CircuitBreaker::CircuitBreaker( Atlantis* _sts, const std::string& _ident ):AtlantisVCComponent( _sts, _ident )
	{
		CBin = true;
		move = NULL;
		counting = false;
	}

	CircuitBreaker::~CircuitBreaker()
	{
		if (move) delete move;
	}

	bool CircuitBreaker::OnParseLine( const char* line )
	{
#if _DEBUG
		oapiWriteLogV( "\t\tSetting circuit breaker \"%s\" to state \"%s\".", GetQualifiedIdentifier().c_str(), line );
#endif// _DEBUG

		if (!_strnicmp( line, "OPEN", 4 )) CBin = false;
		else if (!_strnicmp( line, "CLOSED", 6 )) CBin = true;
		else
		{
#if _DEBUG
			oapiWriteLogV( "\t\tError setting circuit breaker \"%s\" state, default used.", GetQualifiedIdentifier().c_str() );
#endif// _DEBUG
		}
		return true;
	}

	bool CircuitBreaker::GetStateString( unsigned long ulBufferSize, char* pszBuffer )
	{
		if (CBin) sprintf_s( pszBuffer, ulBufferSize, "CLOSED" );
		else sprintf_s( pszBuffer, ulBufferSize, "OPEN" );
		return true;
	}

	void CircuitBreaker::DefineGroup( UINT _grpIndex )
	{
		grpIndex = _grpIndex;
		return;
	}

	void CircuitBreaker::SetInitialPosition( bool in )
	{
		CBin = in;
		return;
	}

	void CircuitBreaker::Connect( DiscreteBundle* pBundle, unsigned short usLine )
	{
		output.Connect( pBundle, usLine );
		return;
	}

	void CircuitBreaker::DefineVCAnimations( UINT vc_idx )
	{
		assert( bHasDirection && "CircuitBreaker.bHasDirection" );
#if _DEBUG
		oapiWriteLogV( "Circuit Breaker[%s]:\tDefine VC Animations()", GetQualifiedIdentifier().c_str() );
#endif// _DEBUG

		move = new MGROUP_TRANSLATE( vc_idx, &grpIndex, 1, GetDirection() * CB_MOVEMENT_RANGE );
		anim_move = STS()->CreateAnimation( InitialAnimState() );
		STS()->AddAnimationComponent( anim_move, 0.0, 1.0, move );

		VerifyAnimations();
		OnChange( CBin );
		return;
	}

	void CircuitBreaker::OnChange( bool _CBin )
	{
		CBin = _CBin;

		if (CBin)
		{
			output.SetLine();
			SetAnimation( anim_move, 0.0 );// in
		}
		else
		{
			output.ResetLine();
			SetAnimation( anim_move, 1.0 );// out
		}

		PlayVesselWave( STS()->GetSoundID(), CB_SOUND );
		return;
	}

	bool CircuitBreaker::OnMouseEvent( int _event, float x, float y )
	{
		if (_event & PANEL_MOUSE_LBDOWN)
		{
			t0 = oapiGetSysTime();
			counting = true;
			return true;
		}
		else if ((_event & PANEL_MOUSE_LBPRESSED) && counting && ((oapiGetSysTime() - t0) >= CB_MOVEMENT_TIME))
		{
			OnChange( !CBin );
			counting = false;
			return true;
		}
		return false;
	}
}

#include "RotarySwitchPotentiometer.h"
#include "../Atlantis.h"
#include <cassert>


namespace vc
{
	constexpr double ROT_SPEED = 90.0;// rotation speed [deg/s]


	RotarySwitchPotentiometer::RotarySwitchPotentiometer( Atlantis* _sts, const std::string& _ident ):AtlantisVCComponent( _sts, _ident )
	{
		pos = 0.0;
		ang = -1.0;
		rot = NULL;
	}

	RotarySwitchPotentiometer::~RotarySwitchPotentiometer()
	{
		if (rot) delete rot;
	}

	bool RotarySwitchPotentiometer::OnParseLine( const char* line )
	{
#if _DEBUG
		oapiWriteLogV( "\t\tRotary Switch Potentiometer \"%s\" to state \"%s\".", GetQualifiedIdentifier().c_str(), line );
#endif

		double tmp = -1.0;
		sscanf( line, "%lf", &tmp );
		if ((tmp >= 0.0) && (tmp <= 1.0)) pos = tmp;
		else
		{
#if _DEBUG
			oapiWriteLogV( "\t\tError setting Rotary Switch Potentiometer \"%s\" state, default used.", GetQualifiedIdentifier().c_str() );
#endif
		}
		return true;
	}

	bool RotarySwitchPotentiometer::GetStateString( unsigned long ulBufferSize, char* pszBuffer )
	{
		sprintf_s( pszBuffer, ulBufferSize, "%lf", pos );
		return true;
	}

	void RotarySwitchPotentiometer::DefineGroup( UINT _grpIndex )
	{
		grpIndex = _grpIndex;
		return;
	}

	void RotarySwitchPotentiometer::SetAngleRange( double ang )
	{
		assert( (ang > 0.0) && (pos < 360.0) && "RotarySwitchPotentiometer::SetAngleRange.ang" );
		this->ang = ang;
		return;
	}

	void RotarySwitchPotentiometer::Connect( DiscreteBundle* pBundle, unsigned short usLine )
	{
		output.Connect( pBundle, usLine );
		return;
	}

	void RotarySwitchPotentiometer::DefineVCAnimations( UINT vc_idx )
	{
		assert( bHasReference && "RotarySwitchPotentiometer.bHasReference" );
		assert( bHasDirection && "RotarySwitchPotentiometer.bHasDirection" );
		assert( (ang > 0.0) && "RotarySwitchPotentiometer.bHasDirection" );
#if _DEBUG
		oapiWriteLogV( "Rotary Switch Potentiometer[%s]:\tDefine VC Animations()", GetQualifiedIdentifier().c_str() );
#endif

		rot = new MGROUP_ROTATE( vc_idx, &grpIndex, 1, GetReference(), GetDirection(), static_cast<float>(ang * RAD) );
		anim_rot = STS()->CreateAnimation( InitialAnimState() );
		STS()->AddAnimationComponent( anim_rot, 0.0, 1.0, rot );

		VerifyAnimations();
		OnPositionChange();
		return;
	}

	void RotarySwitchPotentiometer::OnPositionChange( void )
	{
		output.SetLine( static_cast<float>(5.0 * pos) );
		SetAnimation( anim_rot, pos );
		return;
	}

	bool RotarySwitchPotentiometer::OnMouseEvent( int _event, float x, float y )
	{
		if (_event & PANEL_MOUSE_LBPRESSED)
		{
			if (x > 0.5)
			{
				// rotate CW (increase angle)
				pos += (ROT_SPEED * oapiGetSimStep()) / ang;
				if (pos > 1.0) pos = 1.0;
			}
			else
			{
				// rotate CCW (decrease angle)
				pos -= (ROT_SPEED * oapiGetSimStep()) / ang;
				if (pos < 0.0) pos = 0.0;
			}
			OnPositionChange();
			return true;
		}
		return false;
	}
};

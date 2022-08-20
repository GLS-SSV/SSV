#include "ThumbWheel.h"
#include "../Atlantis.h"
#include "..\..\SSVSound.h"
#include "MathSSV.h"
#include <cassert>


namespace vc
{
	ThumbWheel::ThumbWheel( Atlantis* _sts, const std::string& _ident ):AtlantisVCComponent( _sts, _ident ),
	dirsign(0), posidx(0), uboundidx(0), lboundidx(0), boundset(false)
	{
		wheel = NULL;

		for (unsigned int i = 0; i < 10; i++) outputval[i] = i;// default output mapping
	}

	ThumbWheel::~ThumbWheel()
	{
		if (wheel) delete wheel;
	}

	bool ThumbWheel::OnParseLine( const char* line )
	{
#if _DEBUG
		oapiWriteLogV( "\t\tSetting thumb wheel \"%s\" to state \"%s\".", GetQualifiedIdentifier().c_str(), line );
#endif

		posidx = atoi( line );
		if (posidx >= 10)
		{
#if _DEBUG
			posidx = 0;
			oapiWriteLogV( "\t\tError setting thumb wheel \"%s\" state, default used.", GetQualifiedIdentifier().c_str() );
#endif
		}
		return true;
	}

	bool ThumbWheel::GetStateString( unsigned long ulBufferSize, char* pszBuffer )
	{
		sprintf_s( pszBuffer, ulBufferSize, "%u", posidx );
		return true;
	}

	void ThumbWheel::DefineGroup( UINT _grpIndex )
	{
		grpIndex = _grpIndex;
		return;
	}

	void ThumbWheel::SetBounds( unsigned short upper, unsigned short lower )
	{
		uboundidx = upper;
		lboundidx = lower;
		boundset = true;
		return;
	}

	void ThumbWheel::Connect( DiscreteBundle* pBundle, unsigned short usLine, unsigned short bcdidx )
	{
		assert( (bcdidx <= 3) && "ThumbWheel::Connect.bcdidx" );

		output[bcdidx].Connect( pBundle, usLine );
		return;
	}

	void ThumbWheel::DefineOutputs( unsigned short idx, unsigned short val )
	{
		assert( (idx <= 9) && "ThumbWheel::DefineOutputs.idx" );
		assert( (val <= 9) && "ThumbWheel::DefineOutputs.val" );

		outputval[idx] = val;
		return;
	}

	void ThumbWheel::DefineVCAnimations( UINT vc_idx )
	{
		assert( bHasDirection && "ThumbWheel.bHasDirection" );
		assert( bHasReference && "ThumbWheel.bHasReference" );
#if _DEBUG
		oapiWriteLogV( "ThumbWheel[%s]:\tDefine VC Animations()", GetQualifiedIdentifier().c_str() );
#endif

		wheel = new MGROUP_ROTATE( vc_idx, &grpIndex, 1, GetReference(), GetDirection(), static_cast<float>(2.0 * PI) );
		anim_wheel = STS()->CreateAnimation( InitialAnimState() );
		STS()->AddAnimationComponent( anim_wheel, 0.0, 1.0, wheel );
		SetAnimation( anim_wheel, posidx / 9.0 );

		VerifyAnimations();
		return;
	}

	bool ThumbWheel::OnChange( bool up )
	{
		if (up)
		{
			// check bounds and update
			if (boundset)
			{
				if (posidx == uboundidx) return false;
				posidx++;
			}
			else
			{
				if (posidx == 9) posidx = 0;
				else posidx++;
			}
		}
		else
		{
			// check bounds and update
			if (boundset)
			{
				if (posidx == lboundidx) return false;
				posidx--;
			}
			else
			{
				if (posidx == 0) posidx = 9;
				else posidx--;
			}
		}

		// set output
		SetOutput();

		PlayChangeSound();
		return true;
	}

	bool ThumbWheel::OnMouseEvent( int _event, float x, float y )
	{
		if (!(_event & PANEL_MOUSE_LBDOWN))
			return false;

		if (y > 0.6)
		{
			OnChange( false );
			return true;
		}
		else if (y < 0.4)
		{
			OnChange( true );
			return true;
		}
		return false;
	}

	void ThumbWheel::OnPostStep( double simt, double simdt, double mjd )
	{
		// set animation
		double tgt = posidx / 10.0;
		double cur = STS()->GetAnimation( anim_wheel );

		if (dirsign == 1)// up
		{
			if (cur < tgt)
			{
				// no wrap
				cur += (THUMBWHEEL_RATE * simdt);
				if (cur >= tgt)
				{
					cur = tgt;
					dirsign = 0;
				}
			}
			else
			{
				// wrap
				cur += (THUMBWHEEL_RATE * simdt);
				if (cur >= 1.0)
				{
					cur -= 1.0;

					if (cur >= tgt)
					{
						cur = tgt;
						dirsign = 0;
					}
				}

			}
			SetAnimation( anim_wheel, cur );
		}
		else if (dirsign == -1)// dn
		{
			if (cur > tgt)
			{
				// no wrap
				cur -= (THUMBWHEEL_RATE * simdt);
				if (cur <= tgt)
				{
					cur = tgt;
					dirsign = 0;
				}
			}
			else
			{
				// wrap
				cur -= (THUMBWHEEL_RATE * simdt);
				if (cur <= 0.0)
				{
					cur += 1.0;

					if (cur <= tgt)
					{
						cur = tgt;
						dirsign = 0;
					}
				}

			}
			SetAnimation( anim_wheel, cur );
		}
		return;
	}

	void ThumbWheel::PlayChangeSound( void )
	{
		// TODO
		return;
	}

	void ThumbWheel::SetOutput( void )
	{
		unsigned short val = outputval[posidx];

		if (val & 0x0001) output[0].SetLine();
		else output[0].ResetLine();

		if (val & 0x0002) output[1].SetLine();
		else output[1].ResetLine();

		if (val & 0x0004) output[2].SetLine();
		else output[2].ResetLine();

		if (val & 0x0008) output[3].SetLine();
		else output[3].ResetLine();

		output[1].SetLine();
		output[2].SetLine();
		output[3].SetLine();
		return;
	}
};

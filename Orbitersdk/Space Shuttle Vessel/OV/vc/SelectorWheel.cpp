#include "SelectorWheel.h"
#include "../Atlantis.h"
#include "../../SSVSound.h"
#include <MathSSV.h>
#include <cassert>


namespace vc
{
	SelectorWheel::SelectorWheel( Atlantis* _sts, const std::string& _ident ):AtlantisVCComponent( _sts, _ident ),
	dirsign(0), posidx(0), uboundidx(0), lboundidx(0), boundset(false)
	{
		wheel = NULL;

		for (unsigned int i = 0; i < 10; i++) outputval[i] = i;// default output mapping
	}

	SelectorWheel::~SelectorWheel()
	{
		if (wheel) delete wheel;
	}

	bool SelectorWheel::OnParseLine( const char* line )
	{
#if _DEBUG
		oapiWriteLogV( "\t\tSetting thumb wheel \"%s\" to state \"%s\".", GetQualifiedIdentifier().c_str(), line );
#endif// _DEBUG

		posidx = atoi( line );
		if (posidx >= 10)
		{
#if _DEBUG
			posidx = 0;
			oapiWriteLogV( "\t\tError setting thumb wheel \"%s\" state, default used.", GetQualifiedIdentifier().c_str() );
#endif// _DEBUG
		}
		if (boundset)
		{
			if (posidx > uboundidx) posidx = uboundidx;
			else if (posidx < lboundidx) posidx = lboundidx;
		}
		SetOutput();
		return true;
	}

	bool SelectorWheel::GetStateString( unsigned long ulBufferSize, char* pszBuffer )
	{
		sprintf_s( pszBuffer, ulBufferSize, "%u", posidx );
		return true;
	}

	void SelectorWheel::DefineWheelGroup( UINT _grpIndex )
	{
		grpIndex = _grpIndex;
		return;
	}

	void SelectorWheel::SetBounds( unsigned short lower, unsigned short upper )
	{
		uboundidx = upper;
		lboundidx = lower;
		boundset = true;
		return;
	}

	void SelectorWheel::Connect( DiscreteBundle* pBundle, unsigned short usLine, unsigned short bcdidx )
	{
		assert( (bcdidx <= 3) && "SelectorWheel::Connect.bcdidx" );

		output[bcdidx].Connect( pBundle, usLine );
		return;
	}

	void SelectorWheel::DefineOutputs( unsigned short idx, unsigned short val )
	{
		assert( (idx <= 9) && "SelectorWheel::DefineOutputs.idx" );
		assert( (val <= 9) && "SelectorWheel::DefineOutputs.val" );

		outputval[idx] = val;
		return;
	}

	void SelectorWheel::DefineVCAnimations( UINT vc_idx )
	{
		assert( bHasDirection && "SelectorWheel.bHasDirection" );
		assert( bHasReference && "SelectorWheel.bHasReference" );
#if _DEBUG
		oapiWriteLogV( "SelectorWheel[%s]:\tDefine VC Animations()", GetQualifiedIdentifier().c_str() );
#endif// _DEBUG

		wheel = new MGROUP_ROTATE( vc_idx, &grpIndex, 1, GetReference(), GetDirection(), static_cast<float>(2.0 * PI) );
		anim_wheel = STS()->CreateAnimation( InitialAnimState() );
		STS()->AddAnimationComponent( anim_wheel, 0.0, 1.0, wheel );
		VerifyAnimations();

		SetAnimation( anim_wheel, posidx / 10.0 );
		return;
	}

	bool SelectorWheel::OnChange( bool up )
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
			dirsign = 1;
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
			dirsign = -1;
		}

		// set output
		SetOutput();

		PlayChangeSound();
		return true;
	}

	void SelectorWheel::OnPostStep( double simt, double simdt, double mjd )
	{
		// set animation
		double tgt = posidx / 10.0;
		double cur = STS()->GetAnimation( anim_wheel );

		if (dirsign == 1)// up
		{
			if (cur < tgt)
			{
				// no wrap
				cur += (WHEEL_RATE * simdt);
				if (cur >= tgt)
				{
					cur = tgt;
					dirsign = 0;
				}
			}
			else
			{
				// wrap
				cur += (WHEEL_RATE * simdt);
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
				cur -= (WHEEL_RATE * simdt);
				if (cur <= tgt)
				{
					cur = tgt;
					dirsign = 0;
				}
			}
			else
			{
				// wrap
				cur -= (WHEEL_RATE * simdt);
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

	void SelectorWheel::PlayChangeSound( void )
	{
		// TODO
		return;
	}

	void SelectorWheel::SetOutput( void )
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
		return;
	}
};

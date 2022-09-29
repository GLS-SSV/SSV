/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/05/07   GLS
2020/06/12   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/01/20   GLS
2021/07/03   GLS
2021/08/24   GLS
2022/09/29   GLS
********************************************/
#include "Keyboard.h"
#include "../Atlantis.h"
#include "../dps/IDP.h"
#include "../dps/dps_defs.h"
#include "../../SSVSound.h"
#include <MathSSV.h>
#include <cassert>


namespace vc
{
	const double PUSH_LENGTH = 0.0019;// [m]


	Keyboard::Keyboard( Atlantis* _sts, const std::string& _ident, int ID ):AtlantisVCComponent( _sts, _ident )
	{
		this->ID = ID;
		pIDP[0] = NULL;
		pIDP[1] = NULL;

		for (auto &x : anim_key) x = 0;
		for (auto &x : keyGrp) x = 0;
		for (auto &x : pKEY) x = NULL;
	}

	Keyboard::~Keyboard()
	{
		for (auto &x : pKEY) if (x) delete x;
	}

	void Keyboard::ConnectIDP( unsigned int num, dps::IDP* p_idp )
	{
		assert( (num < 2) && "Keyboard::ConnectIDP.num" );
		pIDP[num] = p_idp;
		return;
	}

	void Keyboard::DefineGroup( UINT* _grpIndex )
	{
		for (int i = 0; i < 32; i++) keyGrp[i] = _grpIndex[i];
	}

	void Keyboard::DefineVCAnimations( UINT vc_idx )
	{
		if (bHasDirection && !bHasAnimations)
		{
#if _DEBUG
			oapiWriteLogV( "Keyboard[%s]:\tDefineVCAnimations()", GetQualifiedIdentifier().c_str() );
#endif

			VECTOR3 len = Normalize( GetDirection() ) * PUSH_LENGTH;
			for (int i = 0; i < 32; i++)
			{
				anim_key[i] = STS()->CreateAnimation( 0.0 );

				pKEY[i] = new MGROUP_TRANSLATE( vc_idx, &keyGrp[i], 1, len );
				STS()->AddAnimationComponent( anim_key[i], 0.0, 1.0, pKEY[i] );
			}

			VerifyAnimations();
		}
		return;
	}

	bool Keyboard::OnMouseEvent( int _event, float x, float y )
	{
		static const float X1L = 0.0f;
		static const float X1R = 0.232558f;
		static const float X2L = 0.255814f;
		static const float X2R = 0.488372f;
		static const float X3L = 0.511628f;
		static const float X3R = 0.744186f;
		static const float X4L = 0.767442f;
		static const float X4R = 1.0f;

		static const float Y1U = 0.0f;
		static const float Y1D = 0.114943f;
		static const float Y2U = 0.126437f;
		static const float Y2D = 0.241379f;
		static const float Y3U = 0.252874f;
		static const float Y3D = 0.367816f;
		static const float Y4U = 0.379310f;
		static const float Y4D = 0.494253f;
		static const float Y5U = 0.505747f;
		static const float Y5D = 0.620690f;
		static const float Y6U = 0.632184f;
		static const float Y6D = 0.747126f;
		static const float Y7U = 0.758621f;
		static const float Y7D = 0.873563f;
		static const float Y8U = 0.885057f;
		static const float Y8D = 1.0f;

		if (x >= X1L && x < X1R)// first column of buttons
		{
			if (y >= Y1U && y < Y1D)// FAULT SUMM
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_FAULTSUMM );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_FAULTSUMM );
					return true;
				}
				else return false;
			}
			else if (y >= Y2U && y < Y2D)// GPC/CRT
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_GPCCRT );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_GPCCRT );
					return true;
				}
				else return false;
			}
			else if (y >= Y3U && y < Y3D)// I/O RESET
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_IORESET );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_IORESET );
					return true;
				}
				else return false;
			}
			else if (y >= Y4U && y < Y4D)// ITEM
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_ITEM );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_ITEM );
					return true;
				}
				else return false;
			}
			else if (y >= Y5U && y < Y5D)// EXEC
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_EXEC );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_EXEC );
					return true;
				}
				else return false;
			}
			else if (y >= Y6U && y < Y6D)// OPS
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_OPS );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_OPS );
					return true;
				}
				else return false;
			}
			else if (y >= Y7U && y < Y7D)// SPEC
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_SPEC );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_SPEC );
					return true;
				}
				else return false;
			}
			else if (y >= Y8U && y < Y8D)// RESUME
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_RESUME );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_RESUME );
					return true;
				}
				else return false;
			}
		}
		else if (x >= X2L && x < X2R)// second column of buttons
		{
			if (y >= Y1U && y < Y1D)// SYS SUMM
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_SYSSUMM );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_SYSSUMM );
					return true;
				}
				else return false;
			}
			else if (y >= Y2U && y < Y2D)// A
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_A );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_A );
					return true;
				}
				else return false;
			}
			else if (y >= Y3U && y < Y3D)// D
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_D );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_D );
					return true;
				}
				else return false;
			}
			else if (y >= Y4U && y < Y4D)// 1
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_1 );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_1 );
					return true;
				}
				else return false;
			}
			else if (y >= Y5U && y < Y5D)// 4
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_4 );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_4 );
					return true;
				}
				else return false;
			}
			else if (y >= Y6U && y < Y6D)// 7
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_7 );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_7 );
					return true;
				}
				else return false;
			}
			else if (y >= Y7U && y < Y7D)// -
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_MINUS );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_MINUS );
					return true;
				}
				else return false;
			}
			else if (y >= Y8U && y < Y8D)// CLEAR
			{
			if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_CLEAR );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_CLEAR );
					return true;
				}
				else return false;
			}
		}
		else if (x >= X3L && x < X3R)// third column of buttons
		{
			if (y >= Y1U && y < Y1D)// MSG RESET
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_MSGRESET );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_MSGRESET );
					return true;
				}
				else return false;
			}
			else if (y >= Y2U && y < Y2D)// B
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_B );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_B );
					return true;
				}
				else return false;
			}
			else if (y >= Y3U && y < Y3D)// E
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_E );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_E );
					return true;
				}
				else return false;
			}
			else if (y >= Y4U && y < Y4D)// 2
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_2 );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_2 );
					return true;
				}
				else return false;
			}
			else if (y >= Y5U && y < Y5D)// 5
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_5 );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_5 );
					return true;
				}
				else return false;
			}
			else if (y >= Y6U && y < Y6D)// 8
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_8 );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_8 );
					return true;
				}
				else return false;
			}
			else if (y >= Y7U && y < Y7D)// 0
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_0 );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_0 );
					return true;
				}
				else return false;
			}
			else if (y >= Y8U && y < Y8D)// .
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_DOT );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_DOT );
					return true;
				}
				else return false;
			}
		}
		else if (x >= X4L && x <= X4R)// fourth column of buttons
		{
			if (y >= Y1U && y < Y1D)// ACK
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_ACK );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_ACK );
					return true;
				}
				else return false;
			}
			else if (y >= Y2U && y < Y2D)// C
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_C );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_C );
					return true;
				}
				else return false;
			}
			else if (y >= Y3U && y < Y3D)// F
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_F );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_F );
					return true;
				}
				else return false;
			}
			else if (y >= Y4U && y < Y4D)// 3
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_3 );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_3 );
					return true;
				}
				else return false;
			}
			else if (y >= Y5U && y < Y5D)// 6
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_6 );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_6 );
					return true;
				}
				else return false;
			}
			else if (y >= Y6U && y < Y6D)// 9
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_9 );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_9 );
					return true;
				}
				else return false;
			}
			else if (y >= Y7U && y < Y7D)// +
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_PLUS );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_PLUS );
					return true;
				}
				else return false;
			}
			else if (y >= Y8U && y < Y8D)// PRO
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnKeyPress( SSV_KEY_PRO );
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnKeyRelease( SSV_KEY_PRO );
					return true;
				}
				else return false;
			}
		}
		return false;
	}

	void Keyboard::OnKeyPress( char key )
	{
		if (bHasAnimations) SetAnimation( anim_key[key - 1], 1.0 );
		if (pIDP[0] != NULL) pIDP[0]->PutKey( ID, key );
		if (pIDP[1] != NULL) pIDP[1]->PutKey( ID, key );
		PlayVesselWave( STS()->GetSoundID(), KEY_PRESS_SOUND );
		return;
	}

	void Keyboard::OnKeyRelease( char key )
	{
		if (bHasAnimations) SetAnimation( anim_key[key - 1], 0.0 );
		return;
	}
};
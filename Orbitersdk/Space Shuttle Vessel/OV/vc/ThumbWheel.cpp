#include "ThumbWheel.h"
#include "../Atlantis.h"
#include "../../SSVSound.h"
#include <MathSSV.h>
#include <cassert>


namespace vc
{
	ThumbWheel::ThumbWheel( Atlantis* _sts, const std::string& _ident ):SelectorWheel( _sts, _ident )
	{
	}

	ThumbWheel::~ThumbWheel()
	{
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
};

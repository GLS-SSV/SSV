/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/03/29   GLS
2020/05/08   GLS
2020/06/20   GLS
2020/06/21   GLS
2020/06/23   GLS
2021/06/03   GLS
2021/06/06   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/08/08   GLS
2022/09/29   GLS
********************************************/
#include "CRT.h"
#include "Atlantis.h"
#include "vc/MDU.h"


// ==============================================================
// MFD class implementation


CRT::CRT( DWORD w, DWORD h, VESSEL *vessel, int MDUID )
: MFD2( w, h, vessel )
{
	this->MDUID = MDUID;

	oapiWriteLogV( "(CRT) [INFO] %dx%d MDUID: %d", w, h, MDUID );

	Atlantis* sts = static_cast<Atlantis*>(pV);

	mdu = sts->GetMDU( MDUID );
	return;
}

CRT::~CRT ()
{
	return;
}

bool CRT::Update( oapi::Sketchpad* skp )
{
	try
	{
		if (mdu) mdu->PaintDisplay( skp );
		else return false;
		return true;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(CRT) [FATAL ERROR] Exception in CRT::Update: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLogV( "(CRT) [FATAL ERROR] Exception in CRT::Update" );
		abort();
	}
}

char *CRT::ButtonLabel (int bt)
{
	try
	{
		if (mdu) return mdu->ButtonLabel( bt );
		else return NULL;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(CRT) [FATAL ERROR] Exception in CRT::ButtonLabel: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLogV( "(CRT) [FATAL ERROR] Exception in CRT::ButtonLabel" );
		abort();
	}
}

// Return button menus
int CRT::ButtonMenu (const MFDBUTTONMENU **menu) const
{
	try
	{
		if (mdu) return mdu->ButtonMenu( menu );
		else return 0;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(CRT) [FATAL ERROR] Exception in CRT::ButtonMenu: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLogV( "(CRT) [FATAL ERROR] Exception in CRT::ButtonMenu" );
		abort();
	}
}

bool CRT::ConsumeKeyBuffered (DWORD key)
{
	try
	{
		if (mdu)
		{
			if (mdu->NavigateMenu( key ))
			{
				InvalidateDisplay();
				return true;
			}
		}
		return false;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(CRT) [FATAL ERROR] Exception in CRT::ConsumeKeyBuffered: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLogV( "(CRT) [FATAL ERROR] Exception in CRT::ConsumeKeyBuffered" );
		abort();
	}
}

bool CRT::ConsumeButton (int bt, int event)
{
	try
	{
		if (!(event & PANEL_MOUSE_LBDOWN)) return false;

		static const DWORD btkey[5] = {OAPI_KEY_U, OAPI_KEY_1, OAPI_KEY_2, OAPI_KEY_3, OAPI_KEY_4};

		if (bt < 5) return ConsumeKeyBuffered (btkey[bt]);
		else return false;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(CRT) [FATAL ERROR] Exception in CRT::ConsumeButton: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLogV( "(CRT) [FATAL ERROR] Exception in CRT::ConsumeButton" );
		abort();
	}
}

// MFD message parser
int CRT::MsgProc (UINT msg, UINT mfd, WPARAM wparam, LPARAM lparam)
{
	try
	{
		switch (msg) {
		case OAPI_MSG_MFD_OPENED:
			// Our new MFD mode has been selected, so we create the MFD and
			// return a pointer to it.
			return (int)(new CRT (LOWORD(wparam), HIWORD(wparam), (VESSEL*)lparam, mfd));
		}
		return 0;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(CRT) [FATAL ERROR] Exception in CRT::MsgProc: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLogV( "(CRT) [FATAL ERROR] Exception in CRT::MsgProc" );
		abort();
	}
}

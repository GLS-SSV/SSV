/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/03/29   GLS
2020/04/01   GLS
2020/05/07   GLS
2020/06/20   GLS
2020/06/21   GLS
2020/06/23   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "LCC_MFD.h"
#include "LCC.h"
#include "../LCCPadInterface.h"


LCC_MFD::LCC_MFD( DWORD w, DWORD h, VESSEL *v ):MFD2( w, h, v )
{
	pLCC = static_cast<LCC*>(v);
	return;
}

LCC_MFD::~LCC_MFD( void )
{
	return;
}

bool LCC_MFD::Update( oapi::Sketchpad* skp )
{
	try
	{
		Title( skp, "Space Shuttle Vessel LCC MFD" );

		char cbuf[64];
		double Ypos = 0.35;

		/*skp->SetTextColor( 0x00FF00 );

		sprintf_s( cbuf, 64, "co:%d hd:%d ch:%d", pLCC->cutoff, pLCC->LPSCountdownHold, pLCC->clockholding );
		skp->Text( (int)(W * 0.01), (int)(H * Ypos), cbuf, strlen( cbuf ) );

		Ypos += 0.05;
		sprintf_s( cbuf, 64, "%d%d%d%d%d%d", pLCC->hold0730, pLCC->hold0500, pLCC->hold0400, pLCC->hold0255, pLCC->hold0157, pLCC->hold0031 );
		skp->Text( (int)(W * 0.01), (int)(H * Ypos), cbuf, strlen( cbuf ) );

		Ypos += 0.05;
		sprintf_s( cbuf, 64, "ah:%d re:%d %.1f", pLCC->requestautohold, pLCC->resuming, pLCC->resumetimer );
		skp->Text( (int)(W * 0.01), (int)(H * Ypos), cbuf, strlen( cbuf ) );*/

		////////////////////////////////////////
		////////////////////////////////////////
		////////////////////////////////////////
		////////////////////////////////////////

		// center
		skp->SetTextColor( 0xFFFFFF );
		if (pLCC->CountdownTime <= 0.0)
		{
			if (pLCC->cutoff)
			{
				sprintf_s( cbuf, 64, "CUTOFF" );
				skp->Text( (int)(W * 0.2), (int)(H * 0.5), cbuf, strlen( cbuf ) );
			}
			else if (pLCC->LPSCountdownHold)
			{
				if (pLCC->resuming)
				{
					sprintf_s( cbuf, 64, "RESUMING IN %.1f", pLCC->resumetimer );
					skp->Text( (int)(W * 0.2), (int)(H * 0.5), cbuf, strlen( cbuf ) );
				}
				else
				{
					sprintf_s( cbuf, 64, "HOLDING" );
					skp->Text( (int)(W * 0.2), (int)(H * 0.5), cbuf, strlen( cbuf ) );
				}
			}
			sprintf_s( cbuf, 64, "T%+.1f", pLCC->CountdownTime );
			skp->Text( (int)(W * 0.2), (int)(H * 0.55), cbuf, strlen( cbuf ) );
		}

		sprintf_s( cbuf, 64, "FIREX" );
		skp->Text( (int)(W * 0.2), (int)(H * 0.7), cbuf, strlen( cbuf ) );
		sprintf_s( cbuf, 64, "SSME HEATSHIELD %s", pLCC->pPad->GetFirexState( 1 ) ? "ON" : "OFF" );
		skp->Text( (int)(W * 0.25), (int)(H * 0.75), cbuf, strlen( cbuf ) );
		sprintf_s( cbuf, 64, "T0 UMBILICALS %s", pLCC->pPad->GetFirexState( 2 ) ? "ON" : "OFF" );
		skp->Text( (int)(W * 0.25), (int)(H * 0.8), cbuf, strlen( cbuf ) );
		sprintf_s( cbuf, 64, "ORBITER SKIN %s", pLCC->pPad->GetFirexState( 3 ) ? "ON" : "OFF" );
		skp->Text( (int)(W * 0.25), (int)(H * 0.85), cbuf, strlen( cbuf ) );

		double s = round( (pLCC->launch_mjd - ((int)pLCC->launch_mjd)) * 864000.0 ) / 10.0;
		int h = (int)(s / 3600.0);
		s -= h * 3600.0;
		int m = (int)(s / 60.0);
		s -= m * 60.0;
		sprintf_s( cbuf, 64, "T0: %02d:%02d:%04.1f", h, m, s );
		skp->Text( (int)(W * 0.2), (int)(H * 0.6), cbuf, strlen( cbuf ) );

		// left side
		if (pLCC->LPSCountdownHold && !pLCC->resuming && !pLCC->cutoff) skp->SetTextColor( 0x00FF00 );
		else skp->SetTextColor( 0x808080 );
		skp->Text( (int)(W * 0.03), (int)(H * 0.142), "Resume", 6 );

		if (pLCC->LPSCountdownHold && !pLCC->resuming) skp->SetTextColor( 0x00FF00 );
		else skp->SetTextColor( 0x808080 );
		skp->Text( (int)(W * 0.03), (int)(H * 0.284), "Recycle", 7 );

		if ((pLCC->CountdownTime <= -31.0) || (pLCC->CountdownTime >= 0.0)) skp->SetTextColor( 0x808080 );
		else if (pLCC->cutoff) skp->SetTextColor( 0x0000FF );
		else skp->SetTextColor( 0x00FF00 );
		skp->Text( (int)(W * 0.03), (int)(H * 0.852), "Cutoff", 6 );

		// right side
		skp->SetTextColor( 0xFFFFFF );
		skp->Text( (int)(W * 0.8), (int)(H * 0.075), "Holds", 5 );

		skp->Line( (int)(W * 0.77), (int)(H * 0.075), (int)(W * 0.8), (int)(H * 0.075) );
		skp->Line( (int)(W * 0.77), (int)(H * 0.075), (int)(W * 0.77), (int)(H * 0.9) );

		Ypos = 0.142;
		double Ydelta = 0.142;
		sprintf_s( cbuf, 64, "T-7m30s" );
		if (pLCC->CountdownTime >= -450.0) skp->SetTextColor( 0x707070 );
		else if (pLCC->hold0730) skp->SetTextColor( 0x0000FF );
		else skp->SetTextColor( 0x00FF00 );
		skp->Text( (int)(W * 0.8), (int)(H * Ypos), cbuf, strlen( cbuf ) );

		Ypos += Ydelta;
		sprintf_s( cbuf, 64, "T-5m" );
		if (pLCC->CountdownTime >= -300.0) skp->SetTextColor( 0x808080 );
		else if (pLCC->hold0500) skp->SetTextColor( 0x0000FF );
		else skp->SetTextColor( 0x00FF00 );
		skp->Text( (int)(W * 0.8), (int)(H * Ypos), cbuf, strlen( cbuf ) );

		Ypos += Ydelta;
		sprintf_s( cbuf, 64, "T-4m" );
		if (pLCC->CountdownTime >= -240.0) skp->SetTextColor( 0x808080 );
		else if (pLCC->hold0400) skp->SetTextColor( 0x0000FF );
		else skp->SetTextColor( 0x00FF00 );
		skp->Text( (int)(W * 0.8), (int)(H * Ypos), cbuf, strlen( cbuf ) );

		Ypos += Ydelta;
		sprintf_s( cbuf, 64, "T-2m55s" );
		if (pLCC->CountdownTime >= -175.0) skp->SetTextColor( 0x808080 );
		else if (pLCC->hold0255) skp->SetTextColor( 0x0000FF );
		else skp->SetTextColor( 0x00FF00 );
		skp->Text( (int)(W * 0.8), (int)(H * Ypos), cbuf, strlen( cbuf ) );

		Ypos += Ydelta;
		sprintf_s( cbuf, 64, "T-1m57s" );
		if (pLCC->CountdownTime >= -117.0) skp->SetTextColor( 0x808080 );
		else if (pLCC->hold0157) skp->SetTextColor( 0x0000FF );
		else skp->SetTextColor( 0x00FF00 );
		skp->Text( (int)(W * 0.8), (int)(H * Ypos), cbuf, strlen( cbuf ) );

		Ypos += Ydelta;
		sprintf_s( cbuf, 64, "T-31s" );
		if (pLCC->CountdownTime >= -31.0) skp->SetTextColor( 0x808080 );
		else if (pLCC->hold0031) skp->SetTextColor( 0x0000FF );
		else skp->SetTextColor( 0x00FF00 );
		skp->Text( (int)(W * 0.8), (int)(H * Ypos), cbuf, strlen( cbuf ) );
		return true;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_LCC_MFD) [FATAL ERROR] Exception in LCC_MFD::Update: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_LCC_MFD) [FATAL ERROR] Exception in LCC_MFD::Update" );
		abort();
	}
}

char* LCC_MFD::ButtonLabel( int bt )
{
	try
	{
		static char *label[12] = {"RES", "RCY", "", "", "", "CUT",
					"<<", "<<", "<<", "<<", "<<", "<<"};

		return ((bt < 12) ? label[bt] : NULL);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_LCC_MFD) [FATAL ERROR] Exception in LCC_MFD::ButtonLabel: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_LCC_MFD) [FATAL ERROR] Exception in LCC_MFD::ButtonLabel" );
		abort();
	}
}

int LCC_MFD::ButtonMenu( const MFDBUTTONMENU** menu ) const
{
	try
	{
		static const MFDBUTTONMENU mnu[12] = {
			{"Resume Count", 0, 0}, {"Recycle to T-9m", 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {"Cutoff", 0, 0},
			{"Toggle Hold at T-7m30s", 0, 0},
			{"Toggle Hold at T-5m", 0, 0},
			{"Toggle Hold at T-4m", 0, 0},
			{"Toggle Hold at T-2m55s", 0, 0},
			{"Toggle Hold at T-1m57s", 0, 0},
			{"Toggle Hold at T-31s", 0, 0}};

		if (menu) *menu = mnu;
		return 12;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_LCC_MFD) [FATAL ERROR] Exception in LCC_MFD::ButtonMenu: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_LCC_MFD) [FATAL ERROR] Exception in LCC_MFD::ButtonMenu" );
		abort();
	}
}

bool LCC_MFD::ConsumeKeyBuffered( DWORD key )
{
	try
	{
		switch (key)
		{
			case OAPI_KEY_1:
				if (pLCC->pPad->GetFirexState( 1 )) pLCC->pPad->DeactivateFirex( 1 );
				else pLCC->pPad->ActivateFirex( 1 );
				return true;
			case OAPI_KEY_2:
				if (pLCC->pPad->GetFirexState( 2 )) pLCC->pPad->DeactivateFirex( 2 );
				else pLCC->pPad->ActivateFirex( 2 );
				return true;
			case OAPI_KEY_3:
				if (pLCC->pPad->GetFirexState( 3 )) pLCC->pPad->DeactivateFirex( 3 );
				else pLCC->pPad->ActivateFirex( 3 );
				return true;
		}
		return false;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_LCC_MFD) [FATAL ERROR] Exception in LCC_MFD::ConsumeKeyBuffered: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_LCC_MFD) [FATAL ERROR] Exception in LCC_MFD::ConsumeKeyBuffered" );
		abort();
	}
}

bool LCC_MFD::ConsumeButton( int bt, int event )
{
	try
	{
		if (!(event & PANEL_MOUSE_LBDOWN)) return false;

		switch (bt)
		{
			case 0:// resume
				if (pLCC->LPSCountdownHold && !pLCC->resuming && !pLCC->cutoff) pLCC->resumecmd = true;
				return true;
			case 1:// recycle
				// TODO
				//if (pLCC->LPSCountdownHold && !pLCC->resuming)
				return true;
			case 5:// cutoff
				if ((pLCC->CountdownTime > -31.0) && (pLCC->CountdownTime < 0.0)) pLCC->IssueCutoff();
				return true;
			case 6:
				if (pLCC->CountdownTime < -450.0) pLCC->hold0730 = !pLCC->hold0730;
				return true;
			case 7:
				if (pLCC->CountdownTime < -300.0)
				{
					pLCC->hold0500 = !pLCC->hold0500;
					pLCC->requestautohold = false;
				}
				return true;
			case 8:
				if (pLCC->CountdownTime < -240.0)
				{
					pLCC->hold0400 = !pLCC->hold0400;
					pLCC->requestautohold = false;
				}
				return true;
			case 9:
				if (pLCC->CountdownTime < -175.0) pLCC->hold0255 = !pLCC->hold0255;
				return true;
			case 10:
				if (pLCC->CountdownTime < -117.0) pLCC->hold0157 = !pLCC->hold0157;
				return true;
			case 11:
				if (pLCC->CountdownTime < -31.0)
				{
					pLCC->hold0031 = !pLCC->hold0031;
					pLCC->requestautohold = false;
				}
				return true;
		}

		return false;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_LCC_MFD) [FATAL ERROR] Exception in LCC_MFD::ConsumeButton: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_LCC_MFD) [FATAL ERROR] Exception in LCC_MFD::ConsumeButton" );
		abort();
	}
}

int LCC_MFD::MsgProc( UINT msg, UINT mfd, WPARAM wparam, LPARAM lparam )
{
	try
	{
		switch (msg)
		{
			case OAPI_MSG_MFD_OPENED:
				return (int)(new LCC_MFD( LOWORD(wparam), HIWORD(wparam), (VESSEL*)lparam ));
		}
		return 0;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_LCC_MFD) [FATAL ERROR] Exception in LCC_MFD::MsgProc: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_LCC_MFD) [FATAL ERROR] Exception in LCC_MFD::MsgProc" );
		abort();
	}
}

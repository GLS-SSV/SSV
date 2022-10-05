/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/03/29   GLS
2020/04/01   GLS
2020/05/14   GLS
2020/06/20   GLS
2020/06/21   GLS
2020/06/23   GLS
2020/06/28   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "Centaur_MFD.h"
#include "Centaur.h"


Centaur_MFD::Centaur_MFD( DWORD w, DWORD h, VESSEL *v ):MFD2( w, h, v )
{
	centaurvessel = static_cast<Centaur*>(v);
	return;
}

Centaur_MFD::~Centaur_MFD( void )
{
	return;
}

bool Centaur_MFD::Update( oapi::Sketchpad *skp )
{
	try
	{
		if (centaurvessel->isGPrime) Title( skp, "SSV Centaur G-Prime MFD" );
		else Title( skp, "SSV Centaur G MFD" );

		char cbuf[64];
		double Ypos = 0.3;

		skp->SetTextColor( 0x00FF00 );

		if (!centaurvessel->separated)
		{
			sprintf_s( cbuf, 64, "Not Active (still attached to CISS)" );
			skp->Text( (int)(W * 0.01), (int)(H * Ypos), cbuf, strlen( cbuf ) );
			return true;
		}

		sprintf_s( cbuf, 64, "ACS available: %.2f Kg", centaurvessel->GetPropellantMass( centaurvessel->phACS ) );
		skp->Text( (int)(W * 0.01), (int)(H * Ypos), cbuf, strlen( cbuf ) );
		Ypos += 0.05;

		if (!centaurvessel->RL10_ENA)
		{
			sprintf_s( cbuf, 64, "RL-10 inhibits removed in: %.0f s", RL10_ENA_DELAY - centaurvessel->timer_RL10_ENA );
			skp->Text( (int)(W * 0.01), (int)(H * Ypos), cbuf, strlen( cbuf ) );
			Ypos += 0.05;
		}
		else if ((centaurvessel->RL10_startseq) && (centaurvessel->RL10_chill))
		{
			sprintf_s( cbuf, 64, "RL-10 ignition in: %.0f s", RL10_START_SEQ - centaurvessel->timer_RL10_startseq );
			skp->Text( (int)(W * 0.01), (int)(H * Ypos), cbuf, strlen( cbuf ) );
			Ypos += 0.05;
		}

		if (!centaurvessel->ACS_ENA)
		{
			sprintf_s( cbuf, 64, "ACS inhibits removed in: %.0f s", ACS_ENA_DELAY - centaurvessel->timer_ACS_ENA );
			skp->Text( (int)(W * 0.01), (int)(H * Ypos), cbuf, strlen( cbuf ) );
			Ypos += 0.05;
		}

		OBJHANDLE earth = centaurvessel->GetGravityRef();
		char str[8];
		oapiGetObjectName( earth, str, 8 );
		if (!_strnicmp( str, "Earth", 5 ))
		{
			VECTOR3 vel;
			VECTOR3 pos;
			centaurvessel->GetRelativeVel( earth, vel );
			centaurvessel->GetRelativePos( earth, pos );
			double v = length( vel );
			double r = length( pos );
			static double mu = 398600439968871.19;
			double C3 = ((0.5 * v * v) - (mu / r)) * 0.000002;
			sprintf_s( cbuf, 64, "C3 energy: %.2f km^2/sec^2", C3 );
			skp->Text( (int)(W * 0.01), (int)(H * Ypos), cbuf, strlen( cbuf ) );
			Ypos += 0.05;
		}

		VECTOR3 avel;
		centaurvessel->GetAngularVel( avel );
		sprintf_s( cbuf, 64, "Roll rate: %.1f deg/s (%.1f RPM)", avel.z * DEG, fabs( avel.z ) * 9.549297 );
		skp->Text( (int)(W * 0.01), (int)(H * Ypos), cbuf, strlen( cbuf ) );
		return true;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_Centaur_MFD) [FATAL ERROR] Exception in Centaur_MFD::Update: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLogV( "(SSV_Centaur_MFD) [FATAL ERROR] Exception in Centaur_MFD::Update" );
		abort();
	}
}

OAPI_MSGTYPE Centaur_MFD::MsgProc( UINT msg, UINT mfd, WPARAM wparam, LPARAM lparam )
{
	try
	{
		switch (msg)
		{
			case OAPI_MSG_MFD_OPENED:
				return (OAPI_MSGTYPE)(new Centaur_MFD( LOWORD(wparam), HIWORD(wparam), (VESSEL*)lparam ));
		}
		return 0;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_Centaur_MFD) [FATAL ERROR] Exception in Centaur_MFD::MsgProc: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLogV( "(SSV_Centaur_MFD) [FATAL ERROR] Exception in Centaur_MFD::MsgProc" );
		abort();
	}
}

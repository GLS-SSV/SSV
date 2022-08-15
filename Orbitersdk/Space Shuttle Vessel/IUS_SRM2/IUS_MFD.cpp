/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/03/29   GLS
2020/04/01   GLS
2020/05/14   GLS
2020/06/20   GLS
2020/06/21   GLS
2020/06/23   GLS
2021/08/24   GLS
2022/03/22   GLS
2022/03/23   GLS
2022/03/24   GLS
2022/08/05   GLS
********************************************/
#include "IUS_MFD.h"
#include "IUS_SRM2.h"


IUS_MFD::IUS_MFD( DWORD w, DWORD h, VESSEL *v ):MFD2( w, h, v )
{
	iusvessel = static_cast<IUS_SRM2*>(v);
	return;
}

IUS_MFD::~IUS_MFD( void )
{
	return;
}

bool IUS_MFD::Update( oapi::Sketchpad *skp )
{
	try
	{
		Title( skp, "Space Shuttle Vessel IUS MFD" );

		char cbuf[64];
		double Ypos = 0.3;

		skp->SetTextColor( 0x00FF00 );

		if (!iusvessel->deployed)
		{
			sprintf_s( cbuf, 64, "Not Active (still attached to ASE)" );
			skp->Text( (int)(W * 0.01), (int)(H * Ypos), cbuf, strlen( cbuf ) );
			return true;
		}

		sprintf_s( cbuf, 64, "RCS available: %.2f Kg", iusvessel->GetPropellantMass( iusvessel->ph_rcs ) );
		skp->Text( (int)(W * 0.01), (int)(H * Ypos), cbuf, strlen( cbuf ) );
		Ypos += 0.05;

		if (!iusvessel->SRM_ENA)
		{
			sprintf_s( cbuf, 64, "SRM inhibits removed in: %.0f s", SRM_ENA_DELAY - iusvessel->timer_SRM_ENA );
			skp->Text( (int)(W * 0.01), (int)(H * Ypos), cbuf, strlen( cbuf ) );
			Ypos += 0.05;
		}

		if (!iusvessel->RCS_ENA)
		{
			sprintf_s( cbuf, 64, "RCS inhibits removed in: %.0f s", RCS_ENA_DELAY - iusvessel->timer_RCS_ENA );
			skp->Text( (int)(W * 0.01), (int)(H * Ypos), cbuf, strlen( cbuf ) );
			Ypos += 0.05;
		}

		OBJHANDLE earth = iusvessel->GetGravityRef();
		char str[8];
		oapiGetObjectName( earth, str, 8 );
		if (!_strnicmp( str, "Earth", 5 ))
		{
			VECTOR3 vel;
			VECTOR3 pos;
			iusvessel->GetRelativeVel( earth, vel );
			iusvessel->GetRelativePos( earth, pos );
			double v = length( vel );
			double r = length( pos );
			static double mu = 398600439968871.19;
			double C3 = ((0.5 * v * v) - (mu / r)) * 0.000002;
			sprintf_s( cbuf, 64, "C3 energy: %.2f km^2/sec^2", C3 );
			skp->Text( (int)(W * 0.01), (int)(H * Ypos), cbuf, strlen( cbuf ) );
			Ypos += 0.05;
		}

		VECTOR3 avel;
		iusvessel->GetAngularVel( avel );
		sprintf_s( cbuf, 64, "Roll rate: %.1f deg/s (%.1f RPM)", avel.z * DEG, fabs( avel.z ) * 9.549297 );
		skp->Text( (int)(W * 0.01), (int)(H * Ypos), cbuf, strlen( cbuf ) );
		return true;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_IUS_MFD) [FATAL ERROR] Exception in IUS_MFD::Update: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLogV( "(SSV_IUS_MFD) [FATAL ERROR] Exception in IUS_MFD::Update" );
		abort();
	}
}

int IUS_MFD::MsgProc( UINT msg, UINT mfd, WPARAM wparam, LPARAM lparam )
{
	try
	{
		switch (msg)
		{
			case OAPI_MSG_MFD_OPENED:
				return (int)(new IUS_MFD( LOWORD(wparam), HIWORD(wparam), (VESSEL*)lparam ));
		}
		return 0;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_IUS_MFD) [FATAL ERROR] Exception in IUS_MFD::MsgProc: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLogV( "(SSV_IUS_MFD) [FATAL ERROR] Exception in IUS_MFD::MsgProc" );
		abort();
	}
}
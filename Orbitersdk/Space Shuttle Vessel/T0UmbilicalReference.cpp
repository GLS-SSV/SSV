/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/05/07   GLS
2020/06/12   GLS
2020/06/20   GLS
2021/06/18   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "T0UmbilicalReference.h"
#include "T0UmbilicalMLPInterface.h"
#include "OV\Atlantis.h"
#include "MLP\MLP.h"
#include "SLC6\SLC6.h"


T0UmbilicalReference::T0UmbilicalReference( Atlantis* sts )
{
	this->sts = sts;
	T0Umb = NULL;
	T0UmbilicalConnected = false;
	return;
}

T0UmbilicalReference::~T0UmbilicalReference( void )
{
}

void T0UmbilicalReference::Connect( void )
{
	OBJHANDLE hT0Umb = sts->GetAttachmentStatus( sts->GetHDP() );
	if (hT0Umb != NULL)
	{
		VESSEL* pVessel = oapiGetVesselInterface( hT0Umb );
		if (pVessel != NULL)
		{
			if (!_strnicmp( pVessel->GetClassName(), "SSV_MLP", 7 ))
			{
				T0Umb = static_cast<MLP*>(pVessel);
				T0UmbilicalConnected = true;
				oapiWriteLog( "(SSV_OV) [INFO] Connected to T0UmbilicalReference (MLP)" );
			}
			else if (!_strnicmp( pVessel->GetClassName(), "SSV_SLC6", 8 ))
			{
				T0Umb = static_cast<SLC6*>(pVessel);
				T0UmbilicalConnected = true;
				oapiWriteLog( "(SSV_OV) [INFO] Connected to T0UmbilicalReference (SLC6)" );
			}
		}
	}
	return;
}

void T0UmbilicalReference::Connect( T0UmbilicalMLPInterface* ref )
{
	T0Umb = ref;
	T0UmbilicalConnected = true;
	return;
}

void T0UmbilicalReference::SetGMTLO( double GMTLO )
{
	sts->SetGMTLO( GMTLO );
	return;
}

void T0UmbilicalReference::SetGMTLOSetCommandFlag( bool val )
{
	sts->SetGMTLOSetCommandFlag( val );
	return;
}

void T0UmbilicalReference::SetLPSCountdownHoldFlag( bool val )
{
	sts->SetLPSCountdownHoldFlag( val );
	return;
}

void T0UmbilicalReference::SetLPSGoForAutoSequenceStartFlag( bool val )
{
	sts->SetLPSGoForAutoSequenceStartFlag( val );
	return;
}

void T0UmbilicalReference::SetLPSGoForEngineStartFlag( bool val )
{
	sts->SetLPSGoForEngineStartFlag( val );
	return;
}

void T0UmbilicalReference::SetResumeCountCommandFlag( bool val )
{
	sts->SetResumeCountCommandFlag( val );
	return;
}

bool T0UmbilicalReference::GetRSCountdownHoldFlag( void )
{
	return sts->GetRSCountdownHoldFlag();
}

bool T0UmbilicalReference::GetLaunchSequenceAbortFlag( void )
{
	return sts->GetLaunchSequenceAbortFlag();
}

void T0UmbilicalReference::PSN4( void )
{
	sts->PSN4();
	return;
}

double T0UmbilicalReference::GetHydSysPress( int sys )
{
	return sts->GetHydSysPress( sys );
}

int T0UmbilicalReference::GetHeTankPress( int sys )
{
	return sts->GetHeTankPress( sys );
}

int T0UmbilicalReference::GetHeRegPress( int sys )
{
	return sts->GetHeRegPress( sys );
}

void T0UmbilicalReference::HeFillTank( int sys, double mass )
{
	sts->HeFillTank( sys, mass );
	return;
}

void T0UmbilicalReference::SetSSMEActPos( int num, double Ppos, double Ypos )
{
	sts->SetSSMEActPos( num, Ppos, Ypos );
	return;
}

unsigned int T0UmbilicalReference::GetHoldFlags( void )
{
	return sts->GetHoldFlags();
}

void T0UmbilicalReference::FireHDPPICs( void )
{
	if (!T0UmbilicalConnected) return;

	T0Umb->FireHDPPICs();
	return;
}

void T0UmbilicalReference::FireT0UmbilicalPICs( void )
{
	if (!T0UmbilicalConnected) return;

	T0Umb->FireT0UmbilicalPICs();

	T0UmbilicalConnected = false;
	return;
}

/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/04/01   GLS
2020/06/20   GLS
2021/01/20   GLS
2021/06/18   GLS
2021/08/23   GLS
2021/08/24   GLS
********************************************/
#include "MasterEventsController.h"
#include <Orbitersdk.h>
#include "Atlantis.h"
#include "..\T0UmbilicalReference.h"
#include <cassert>


bool MasterEventsController::PIC_SRM_IGNITION = false;
bool MasterEventsController::PIC_T0_UMB = false;
bool MasterEventsController::PIC_SRB_SEP = false;
bool MasterEventsController::PIC_ET_SEP = false;


MasterEventsController::MasterEventsController( AtlantisSubsystemDirector* _director, const string& _ident, short nID ):AtlantisSubsystem( _director, _ident )
{
	assert( (nID >= 1) && (nID <= 2) && "MasterEventsController::MasterEventsController.nID" );
	ID = nID;

	for (int i = 0; i < CRsize; i++) CR[i] = false;
	return;
}

MasterEventsController::~MasterEventsController( void )
{
}

bool MasterEventsController::OnParseLine( const char* line )
{
	return false;
}

void MasterEventsController::OnSaveState( FILEHANDLE scn ) const
{
	return;
}

void MasterEventsController::Realize( void )
{
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "O17_MEC", 2 );
	power.Connect( pBundle, ID - 1 );
	return;
}

void MasterEventsController::OnPreStep( double simt, double simdt, double mjd )
{
	if (!power.IsSet()) return;

	// issue sep commands from PreStep so vessel states are set correctly

	if (CR[SRB_IGNITION_ARM] && CR[SRB_IGNITION_FIRE_1] && CR[SRB_IGNITION_FIRE_2])
	{
		if (!PIC_SRM_IGNITION)
		{
			STS()->IgniteSRBs();
			STS()->T0UmbRef()->FireHDPPICs();
			PIC_SRM_IGNITION = true;
			oapiWriteLog( "MEC: SRM IGNITION, HDP, ETVAS, ETVAS lanyard PICs fired" );
		}
	}

	if (CR[T0_UMB_RELEASE_ARM] && CR[T0_UMB_RELEASE_FIRE_1] && CR[T0_UMB_RELEASE_FIRE_2])
	{
		if (!PIC_T0_UMB)
		{
			STS()->T0UmbRef()->FireT0UmbilicalPICs();
			PIC_T0_UMB = true;
			oapiWriteLog( "MEC: T0 UMB PICs fired" );
		}
	}

	if (CR[SRB_SEP_ARM] && CR[SRB_SEP_FIRE_1] && CR[SRB_SEP_FIRE_2])
	{
		if (!PIC_SRB_SEP)
		{
			STS()->SeparateBoosters( STS()->GetMET() );
			PIC_SRB_SEP = true;
			oapiWriteLog( "MEC: SRB SEP PICs fired" );
		}
	}

	if (CR[ETORB_STRUCT_SEP_ARM] && CR[ETORB_STRUCT_SEP_FIRE_1] && CR[ETORB_STRUCT_SEP_FIRE_2])
	{
		if (!PIC_ET_SEP)
		{
			STS()->SeparateTank();
			PIC_ET_SEP = true;
			oapiWriteLog( "MEC: ET SEP PICs fired" );
		}
	}
	return;
}

/*void MasterEventsController::SetNonCriticalCmd( unsigned int cmd )
{
	return;
}

void MasterEventsController::ResetNonCriticalCmd( unsigned int cmd )
{
	return;
}*/

void MasterEventsController::SetCriticalCmd( unsigned short cmd )
{
	if (!power.IsSet()) return;

	switch (cmd)
	{
		case MEC_CR_SRB_IGNITION_ARM:
			CR[SRB_IGNITION_ARM] = true;
			break;
		case MEC_CR_SRB_IGNITION_FIRE_1:
			CR[SRB_IGNITION_FIRE_1] = true;
			break;
		case MEC_CR_SRB_IGNITION_FIRE_2:
			CR[SRB_IGNITION_FIRE_2] = true;
			break;
		case MEC_CR_SRB_SEP_ARM:
			CR[SRB_SEP_ARM] = true;
			break;
		case MEC_CR_SRB_SEP_FIRE_1:
			CR[SRB_SEP_FIRE_1] = true;
			break;
		case MEC_CR_SRB_SEP_FIRE_2:
			CR[SRB_SEP_FIRE_2] = true;
			break;
		case MEC_CR_ETORB_STRUCT_SEP_ARM:
			CR[ETORB_STRUCT_SEP_ARM] = true;
			break;
		case MEC_CR_ETORB_STRUCT_SEP_FIRE_1:
			CR[ETORB_STRUCT_SEP_FIRE_1] = true;
			break;
		case MEC_CR_ETORB_STRUCT_SEP_FIRE_2:
			CR[ETORB_STRUCT_SEP_FIRE_2] = true;
			break;
		case MEC_CR_T0_UMB_RELEASE_ARM:
			CR[T0_UMB_RELEASE_ARM] = true;
			break;
		case MEC_CR_T0_UMB_RELEASE_FIRE_1:
			CR[T0_UMB_RELEASE_FIRE_1] = true;
			break;
		case MEC_CR_T0_UMB_RELEASE_FIRE_2:
			CR[T0_UMB_RELEASE_FIRE_2] = true;
			break;
	}
	return;
}

void MasterEventsController::MasterResetCmd( void )
{
	if (!power.IsSet()) return;

	for (int i = 0; i < CRsize; i++) CR[i] = false;
	//oapiWriteLog( "MEC: MASTER RESET" );
	return;
}

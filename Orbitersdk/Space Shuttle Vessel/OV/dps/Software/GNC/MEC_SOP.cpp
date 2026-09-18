/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/04/07   GLS
2020/06/20   GLS
2021/01/20   GLS
2021/06/18   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/09/29   GLS
2022/12/23   GLS
2026/09/18   GLS
********************************************/
#include "MEC_SOP.h"
#include "../../../Atlantis.h"
#include "../../../AtlantisSubsystemDirector.h"
#include "../../../MasterEventsController.h"
#include <cassert>


namespace dps
{
	MEC_SOP::MEC_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "MEC_SOP" )
	{
		{// TODO fix IO
			pMEC1 = dynamic_cast<MasterEventsController*>(STS()->SubsystemDirector()->GetSubsystemByName( "MEC1" ));
			assert( (pMEC1 != NULL) && "MEC_SOP::Realize.pMEC1" );
			pMEC2 = dynamic_cast<MasterEventsController*>(STS()->SubsystemDirector()->GetSubsystemByName( "MEC2" ));
			assert( (pMEC2 != NULL) && "MEC_SOP::Realize.pMEC2" );
		}
		return;
	}

	MEC_SOP::~MEC_SOP( void )
	{
		return;
	}

	void MEC_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		if (ReadCOMPOOL_IS( SCP_SRM_IGN_ARM ) == 1)
		{
			pMEC1->SetCriticalCmd( MEC_CR_SRB_IGNITION_ARM );
			pMEC2->SetCriticalCmd( MEC_CR_SRB_IGNITION_ARM );
			//oapiWriteLog( "MEC SOP: SRB IGNITION ARM" );
		}
		if (ReadCOMPOOL_IS( SCP_SRM_IGN_FIRE1 ) == 1)
		{
			pMEC1->SetCriticalCmd( MEC_CR_SRB_IGNITION_FIRE_1 );
			pMEC2->SetCriticalCmd( MEC_CR_SRB_IGNITION_FIRE_1 );
			//oapiWriteLog( "MEC SOP: SRB IGNITION FIRE 1" );
		}
		if (ReadCOMPOOL_IS( SCP_SRM_IGN_FIRE23 ) == 1)
		{
			pMEC1->SetCriticalCmd( MEC_CR_SRB_IGNITION_FIRE_2 );
			pMEC2->SetCriticalCmd( MEC_CR_SRB_IGNITION_FIRE_2 );
			//oapiWriteLog( "MEC SOP: SRB IGNITION FIRE 2" );
		}

		if (ReadCOMPOOL_IS( SCP_T0_UMB_ARM ) == 1)
		{
			pMEC1->SetCriticalCmd( MEC_CR_T0_UMB_RELEASE_ARM );
			pMEC2->SetCriticalCmd( MEC_CR_T0_UMB_RELEASE_ARM );
			//oapiWriteLog( "MEC SOP: T0 UMB ARM" );
		}
		if (ReadCOMPOOL_IS( SCP_T0_UMB_FIRE1 ) == 1)
		{
			pMEC1->SetCriticalCmd( MEC_CR_T0_UMB_RELEASE_FIRE_1 );
			pMEC2->SetCriticalCmd( MEC_CR_T0_UMB_RELEASE_FIRE_1 );
			//oapiWriteLog( "MEC SOP: T0 UMB FIRE 1" );
		}
		if (ReadCOMPOOL_IS( SCP_T0_UMB_FIRE23 ) == 1)
		{
			pMEC1->SetCriticalCmd( MEC_CR_T0_UMB_RELEASE_FIRE_2 );
			pMEC2->SetCriticalCmd( MEC_CR_T0_UMB_RELEASE_FIRE_2 );
			//oapiWriteLog( "MEC SOP: T0 UMB FIRE 2" );
		}


		if (ReadCOMPOOL_IS( SCP_ET_SEP_ARM ) == 1)
		{
			pMEC1->SetCriticalCmd( MEC_CR_ETORB_STRUCT_SEP_ARM );
			pMEC2->SetCriticalCmd( MEC_CR_ETORB_STRUCT_SEP_ARM );
			//oapiWriteLog( "MEC SOP: ET SEP ARM" );
		}
		if (ReadCOMPOOL_IS( SCP_ET_SEP_FIRE1 ) == 1)
		{
			pMEC1->SetCriticalCmd( MEC_CR_ETORB_STRUCT_SEP_FIRE_1 );
			pMEC2->SetCriticalCmd( MEC_CR_ETORB_STRUCT_SEP_FIRE_1 );
			//oapiWriteLog( "MEC SOP: ET SEP FIRE 1" );
		}
		if (ReadCOMPOOL_IS( SCP_ET_SEP_FIRE23 ) == 1)
		{
			pMEC1->SetCriticalCmd( MEC_CR_ETORB_STRUCT_SEP_FIRE_2 );
			pMEC2->SetCriticalCmd( MEC_CR_ETORB_STRUCT_SEP_FIRE_2 );
			//oapiWriteLog( "MEC SOP: ET SEP FIRE 2" );
		}


		if (ReadCOMPOOL_IS( SCP_SRB_SEP_ARM ) == 1)
		{
			pMEC1->SetCriticalCmd( MEC_CR_SRB_SEP_ARM );
			pMEC2->SetCriticalCmd( MEC_CR_SRB_SEP_ARM );
			//oapiWriteLog( "MEC SOP: SRB SEP ARM" );
		}
		if (ReadCOMPOOL_IS( SCP_SRB_SEP_FIRE1 ) == 1)
		{
			pMEC1->SetCriticalCmd( MEC_CR_SRB_SEP_FIRE_1 );
			pMEC2->SetCriticalCmd( MEC_CR_SRB_SEP_FIRE_1 );
			//oapiWriteLog( "MEC SOP: SRB SEP FIRE 1" );
		}
		if (ReadCOMPOOL_IS( SCP_SRB_SEP_FIRE23 ) == 1)
		{
			pMEC1->SetCriticalCmd( MEC_CR_SRB_SEP_FIRE_2 );
			pMEC2->SetCriticalCmd( MEC_CR_SRB_SEP_FIRE_2 );
			//oapiWriteLog( "MEC SOP: SRB SEP FIRE 2" );
		}


		if (ReadCOMPOOL_IS( SCP_M_RSET_USER ) == 1)
		{
			pMEC1->MasterResetCmd();
			pMEC2->MasterResetCmd();
			WriteCOMPOOL_IS( SCP_M_RSET_USER, 0 );
			//oapiWriteLog( "MEC SOP: MASTER RESET" );
		}
		return;
	}

	bool MEC_SOP::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void MEC_SOP::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}
}

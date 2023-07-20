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
		LaunchSequencerFlag = 0;
		ETSepSequencerFlag = 0;
		SRBSepSequencerFlag = 0;

		MECMasterReset = false;
		return;
	}

	MEC_SOP::~MEC_SOP( void )
	{
		return;
	}

	void MEC_SOP::Realize( void )
	{
		pMEC1 = dynamic_cast<MasterEventsController*>(STS()->SubsystemDirector()->GetSubsystemByName( "MEC1" ));
		assert( (pMEC1 != NULL) && "MEC_SOP::Realize.pMEC1" );
		pMEC2 = dynamic_cast<MasterEventsController*>(STS()->SubsystemDirector()->GetSubsystemByName( "MEC2" ));
		assert( (pMEC2 != NULL) && "MEC_SOP::Realize.pMEC2" );
		return;
	}

	void MEC_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		if (LaunchSequencerFlag != 0)
		{
			if ((LaunchSequencerFlag & MECSOP_LAUNCH_SRM_IGNITION_ARM) != 0)
			{
				pMEC1->SetCriticalCmd( MEC_CR_SRB_IGNITION_ARM );
				pMEC2->SetCriticalCmd( MEC_CR_SRB_IGNITION_ARM );
				//oapiWriteLog( "MEC SOP: SRB IGNITION ARM" );
			}
			if ((LaunchSequencerFlag & MECSOP_LAUNCH_SRM_IGNITION_FIRE_1) != 0)
			{
				pMEC1->SetCriticalCmd( MEC_CR_SRB_IGNITION_FIRE_1 );
				pMEC2->SetCriticalCmd( MEC_CR_SRB_IGNITION_FIRE_1 );
				//oapiWriteLog( "MEC SOP: SRB IGNITION FIRE 1" );
			}
			if ((LaunchSequencerFlag & MECSOP_LAUNCH_SRM_IGNITION_FIRE_2) != 0)
			{
				pMEC1->SetCriticalCmd( MEC_CR_SRB_IGNITION_FIRE_2 );
				pMEC2->SetCriticalCmd( MEC_CR_SRB_IGNITION_FIRE_2 );
				//oapiWriteLog( "MEC SOP: SRB IGNITION FIRE 2" );
			}

			if ((LaunchSequencerFlag & MECSOP_LAUNCH_T0_UMB_RELEASE_ARM) != 0)
			{
				pMEC1->SetCriticalCmd( MEC_CR_T0_UMB_RELEASE_ARM );
				pMEC2->SetCriticalCmd( MEC_CR_T0_UMB_RELEASE_ARM );
				//oapiWriteLog( "MEC SOP: T0 UMB ARM" );
			}
			if ((LaunchSequencerFlag & MECSOP_LAUNCH_T0_UMB_RELEASE_FIRE_1) != 0)
			{
				pMEC1->SetCriticalCmd( MEC_CR_T0_UMB_RELEASE_FIRE_1 );
				pMEC2->SetCriticalCmd( MEC_CR_T0_UMB_RELEASE_FIRE_1 );
				//oapiWriteLog( "MEC SOP: T0 UMB FIRE 1" );
			}
			if ((LaunchSequencerFlag & MECSOP_LAUNCH_T0_UMB_RELEASE_FIRE_2) != 0)
			{
				pMEC1->SetCriticalCmd( MEC_CR_T0_UMB_RELEASE_FIRE_2 );
				pMEC2->SetCriticalCmd( MEC_CR_T0_UMB_RELEASE_FIRE_2 );
				//oapiWriteLog( "MEC SOP: T0 UMB FIRE 2" );
			}

			// reset flags
			LaunchSequencerFlag = 0;
		}
		else if (ETSepSequencerFlag != 0)
		{
			if ((ETSepSequencerFlag & MECSOP_ETSEP_ETORB_STR_SEPN_PICS_ARM) != 0)
			{
				pMEC1->SetCriticalCmd( MEC_CR_ETORB_STRUCT_SEP_ARM );
				pMEC2->SetCriticalCmd( MEC_CR_ETORB_STRUCT_SEP_ARM );
				//oapiWriteLog( "MEC SOP: ET SEP ARM" );
			}
			if ((ETSepSequencerFlag & MECSOP_ETSEP_ETORB_STR_SEPN_FIRE_1) != 0)
			{
				pMEC1->SetCriticalCmd( MEC_CR_ETORB_STRUCT_SEP_FIRE_1 );
				pMEC2->SetCriticalCmd( MEC_CR_ETORB_STRUCT_SEP_FIRE_1 );
				//oapiWriteLog( "MEC SOP: ET SEP FIRE 1" );
			}
			if ((ETSepSequencerFlag & MECSOP_ETSEP_ETORB_STR_SEPN_FIRE_2) != 0)
			{
				pMEC1->SetCriticalCmd( MEC_CR_ETORB_STRUCT_SEP_FIRE_2 );
				pMEC2->SetCriticalCmd( MEC_CR_ETORB_STRUCT_SEP_FIRE_2 );
				//oapiWriteLog( "MEC SOP: ET SEP FIRE 2" );
			}

			// reset flags
			ETSepSequencerFlag = 0;
		}
		else if (SRBSepSequencerFlag != 0)
		{
			if ((SRBSepSequencerFlag & MECSOP_SRBSEP_SRB_SEP_PICS_ARM) != 0)
			{
				pMEC1->SetCriticalCmd( MEC_CR_SRB_SEP_ARM );
				pMEC2->SetCriticalCmd( MEC_CR_SRB_SEP_ARM );
				//oapiWriteLog( "MEC SOP: SRB SEP ARM" );
			}
			if ((SRBSepSequencerFlag & MECSOP_SRBSEP_SRB_SEP_FIRE_1) != 0)
			{
				pMEC1->SetCriticalCmd( MEC_CR_SRB_SEP_FIRE_1 );
				pMEC2->SetCriticalCmd( MEC_CR_SRB_SEP_FIRE_1 );
				//oapiWriteLog( "MEC SOP: SRB SEP FIRE 1" );
			}
			if ((SRBSepSequencerFlag & MECSOP_SRBSEP_SRB_SEP_FIRE_2) != 0)
			{
				pMEC1->SetCriticalCmd( MEC_CR_SRB_SEP_FIRE_2 );
				pMEC2->SetCriticalCmd( MEC_CR_SRB_SEP_FIRE_2 );
				//oapiWriteLog( "MEC SOP: SRB SEP FIRE 2" );
			}

			// reset flags
			SRBSepSequencerFlag = 0;
		}
		else if (MECMasterReset)
		{
			pMEC1->MasterResetCmd();
			pMEC2->MasterResetCmd();

			//oapiWriteLog( "MEC SOP: MASTER RESET" );

			// reset flag
			MECMasterReset = false;
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

	bool MEC_SOP::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 101:
			case 102:
			case 103:
			case 104:
			case 601:
				return true;
			default:
				return false;
		}
	}

	void MEC_SOP::SetLaunchSequencerFlag( unsigned short flag )
	{
		LaunchSequencerFlag |= flag;
		return;
	}

	void MEC_SOP::SetSRBSepSequencerFlag( unsigned short flag )
	{
		SRBSepSequencerFlag |= flag;
		return;
	}

	void MEC_SOP::SetETSepSequencerFlag( unsigned short flag )
	{
		ETSepSequencerFlag |= flag;
		return;
	}

	void MEC_SOP::SetMECMasterResetFlag( void )
	{
		MECMasterReset = true;
		return;
	}
}
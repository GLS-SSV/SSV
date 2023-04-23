#include "PanelR14.h"
#include "CircuitBreaker.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_r14.h"


namespace vc
{
	const static char* MESHNAME_PANEL = "SSV\\OV\\panelR14";
	constexpr VECTOR3 OFFSET_PANEL = {1.33375, 1.626377, 13.604449};


	PanelR14::PanelR14( Atlantis* _sts ):AtlantisPanel( _sts, "R14" )
	{
		DefineMesh( MESHNAME_PANEL, OFFSET_PANEL );

		Add( pMNC_MDU_CDR_1 = new CircuitBreaker( _sts, "MNC MDU CDR 1" ) );
		Add( pMNB_MDU_CDR_2 = new CircuitBreaker( _sts, "MNB MDU CDR 2" ) );
		Add( pMNB_MDU_MFD_1 = new CircuitBreaker( _sts, "MNB MDU MFD 1" ) );
		Add( pMNA_MDU_MFD_2 = new CircuitBreaker( _sts, "MNA MDU MFD 2" ) );
		Add( pMNA_MDU_PLT_1 = new CircuitBreaker( _sts, "MNA MDU PLT 1" ) );
		Add( pMNC_MDU_PLT_2 = new CircuitBreaker( _sts, "MNC MDU PLT 2" ) );
		Add( pMNC_MDU_AFD_1 = new CircuitBreaker( _sts, "MNC MDU AFD 1" ) );
		Add( pMNA_ADC_1A_2A = new CircuitBreaker( _sts, "MNA ADC 1A 2A" ) );
		Add( pMNB_ADC_1B_2B = new CircuitBreaker( _sts, "MNB ADC 1B 2B" ) );

		Add( pMNB_TV_A_CAMR_CAMR_PTU = new CircuitBreaker( _sts, "MNB TV A CAMR CAMR/PTU" ) );

		Add( pMNB_TV_A_CAMR_CAMR_HTR = new CircuitBreaker( _sts, "MNB TV A CAMR CAMR HTR" ) );
		pMNB_TV_A_CAMR_CAMR_HTR->SetInitialPosition( false );

		Add( pMNB_TV_A_CAMR_ILLUM_PTU_HTR = new CircuitBreaker( _sts, "MNB TV A CAMR ILLUM/PTU HTR" ) );
		pMNB_TV_A_CAMR_ILLUM_PTU_HTR->SetInitialPosition( false );

		Add( pMNC_TV_B_CAMR_CAMR_PTU = new CircuitBreaker( _sts, "MNC TV B CAMR CAMR/PTU" ) );

		Add( pMNC_TV_B_CAMR_CAMR_HTR = new CircuitBreaker( _sts, "MNC TV B CAMR CAMR HTR" ) );
		pMNC_TV_B_CAMR_CAMR_HTR->SetInitialPosition( false );

		Add( pMNC_TV_B_CAMR_ILLUM_PTU_HTR = new CircuitBreaker( _sts, "MNC TV B CAMR ILLUM/PTU HTR" ) );
		pMNC_TV_B_CAMR_ILLUM_PTU_HTR->SetInitialPosition( false );

		Add( pMNA_TV_C_CAMR_CAMR_PTU = new CircuitBreaker( _sts, "MNA TV C CAMR CAMR/PTU" ) );

		Add( pMNA_TV_C_CAMR_CAMR_HTR = new CircuitBreaker( _sts, "MNA TV C CAMR CAMR HTR" ) );
		pMNA_TV_C_CAMR_CAMR_HTR->SetInitialPosition( false );

		Add( pMNA_TV_C_CAMR_ILLUM_PTU_HTR = new CircuitBreaker( _sts, "MNA TV C CAMR ILLUM/PTU HTR" ) );
		pMNA_TV_C_CAMR_ILLUM_PTU_HTR->SetInitialPosition( false );

		Add( pMNA_TV_D_CAMR_CAMR_PTU = new CircuitBreaker( _sts, "MNA TV D CAMR CAMR/PTU" ) );

		Add( pMNA_TV_D_CAMR_CAMR_HTR = new CircuitBreaker( _sts, "MNA TV D CAMR CAMR HTR" ) );
		pMNA_TV_D_CAMR_CAMR_HTR->SetInitialPosition( false );

		Add( pMNA_TV_D_CAMR_ILLUM_PTU_HTR = new CircuitBreaker( _sts, "MNA TV D CAMR ILLUM/PTU HTR" ) );
		pMNA_TV_D_CAMR_ILLUM_PTU_HTR->SetInitialPosition( false );

		Add( pMNB_TV_RMS_CAMR_CAMR_PTU = new CircuitBreaker( _sts, "MNB TV RMS CAMR CAMR/PTU" ) );

		Add( pMNB_TV_RMS_CAMR_WRIST_ILLUM_CAMR_HTR = new CircuitBreaker( _sts, "MNB TV RMS CAMR WRIST ILLUM/CAMR HTR" ) );
		pMNB_TV_RMS_CAMR_WRIST_ILLUM_CAMR_HTR->SetInitialPosition( false );

		Add( pMNB_TV_RMS_CAMR_ELB_ILLUM_PTU_HTR = new CircuitBreaker( _sts, "MNB TV RMS CAMR ELB ILLUM/PTU HTR" ) );
		pMNB_TV_RMS_CAMR_ELB_ILLUM_PTU_HTR->SetInitialPosition( false );

		Add( pMNA_TV_CONTR_UNIT = new CircuitBreaker( _sts, "MNA TV CONTR UNIT" ) );

		Add( pMNB_TV_CONTR_UNIT = new CircuitBreaker( _sts, "MNB TV CONTR UNIT" ) );

		Add( pMNA_TV_MON_1 = new CircuitBreaker( _sts, "MNA TV MON 1" ) );

		Add( pMNB_TV_MON_2 = new CircuitBreaker( _sts, "MNB TV MON 2" ) );
		return;
	}

	PanelR14::~PanelR14( void )
	{
		return;
	}

	void PanelR14::DefineVC( void )
	{
		const VECTOR3 CB_PULL = _V( -0.858513, -0.512792, 0.0 );

		AddAIDToMouseEventList( AID_R14 );

		pMNC_MDU_CDR_1->SetInitialAnimState( 1.0f );
		pMNC_MDU_CDR_1->DefineGroup( GRP_CB_G_R14_VC );
		pMNC_MDU_CDR_1->SetDirection( CB_PULL );
		pMNC_MDU_CDR_1->SetMouseRegion( AID_R14, 0.753938f, 0.316146f, 0.790604f, 0.361618f );

		pMNB_MDU_CDR_2->SetInitialAnimState( 1.0f );
		pMNB_MDU_CDR_2->DefineGroup( GRP_CB_F_R14_VC );
		pMNB_MDU_CDR_2->SetDirection( CB_PULL );
		pMNB_MDU_CDR_2->SetMouseRegion( AID_R14, 0.598109f, 0.316146f, 0.634106f, 0.361618f );

		pMNB_MDU_MFD_1->SetInitialAnimState( 1.0f );
		pMNB_MDU_MFD_1->DefineGroup( GRP_CB_E_R14_VC );
		pMNB_MDU_MFD_1->SetDirection( CB_PULL );
		pMNB_MDU_MFD_1->SetMouseRegion( AID_R14, 0.549593f, 0.316146f, 0.588844f, 0.361618f );

		pMNA_MDU_MFD_2->SetInitialAnimState( 1.0f );
		pMNA_MDU_MFD_2->DefineGroup( GRP_CB_B_R14_VC );
		pMNA_MDU_MFD_2->SetDirection( CB_PULL );
		pMNA_MDU_MFD_2->SetMouseRegion( AID_R14, 0.253264f, 0.316146f, 0.292443f, 0.361618f );

		pMNA_MDU_PLT_1->SetInitialAnimState( 1.0f );
		pMNA_MDU_PLT_1->DefineGroup( GRP_CB_C_R14_VC );
		pMNA_MDU_PLT_1->SetDirection( CB_PULL );
		pMNA_MDU_PLT_1->SetMouseRegion( AID_R14, 0.301228f, 0.316146f, 0.336629f, 0.361618f );

		pMNC_MDU_PLT_2->SetInitialAnimState( 1.0f );
		pMNC_MDU_PLT_2->DefineGroup( GRP_CB_H_R14_VC );
		pMNC_MDU_PLT_2->SetDirection( CB_PULL );
		pMNC_MDU_PLT_2->SetMouseRegion( AID_R14, 0.798144f, 0.316146f, 0.840385f, 0.361618f );

		pMNC_MDU_AFD_1->SetInitialAnimState( 1.0f );
		pMNC_MDU_AFD_1->DefineGroup( GRP_CB_I_R14_VC );
		pMNC_MDU_AFD_1->SetDirection( CB_PULL );
		pMNC_MDU_AFD_1->SetMouseRegion( AID_R14, 0.848391f, 0.316146f, 0.887296f, 0.361618f );

		pMNA_ADC_1A_2A->SetInitialAnimState( 1.0f );
		pMNA_ADC_1A_2A->DefineGroup( GRP_CB_A_R14_VC );
		pMNA_ADC_1A_2A->SetDirection( CB_PULL );
		pMNA_ADC_1A_2A->SetMouseRegion( AID_R14, 0.205871f, 0.316146f, 0.242745f, 0.361618f );

		pMNB_ADC_1B_2B->SetInitialAnimState( 1.0f );
		pMNB_ADC_1B_2B->DefineGroup( GRP_CB_D_R14_VC );
		pMNB_ADC_1B_2B->SetDirection( CB_PULL );
		pMNB_ADC_1B_2B->SetMouseRegion( AID_R14, 0.503839f, 0.316146f, 0.540347f, 0.361618f );

		pMNB_TV_A_CAMR_CAMR_PTU->SetInitialAnimState( 1.0f );
		pMNB_TV_A_CAMR_CAMR_PTU->DefineGroup( GRP_CB39_R14_VC );
		pMNB_TV_A_CAMR_CAMR_PTU->SetDirection( CB_PULL );
		pMNB_TV_A_CAMR_CAMR_PTU->SetMouseRegion( AID_R14, 0.361156f, 0.643122f, 0.397046f, 0.686773f );

		pMNB_TV_A_CAMR_CAMR_HTR->SetInitialAnimState( 1.0f );
		pMNB_TV_A_CAMR_CAMR_HTR->DefineGroup( GRP_CB40_R14_VC );
		pMNB_TV_A_CAMR_CAMR_HTR->SetDirection( CB_PULL );
		pMNB_TV_A_CAMR_CAMR_HTR->SetMouseRegion( AID_R14, 0.407430f, 0.643122f, 0.445012f, 0.686773f );

		pMNB_TV_A_CAMR_ILLUM_PTU_HTR->SetInitialAnimState( 1.0f );
		pMNB_TV_A_CAMR_ILLUM_PTU_HTR->DefineGroup( GRP_CB41_R14_VC );
		pMNB_TV_A_CAMR_ILLUM_PTU_HTR->SetDirection( CB_PULL );
		pMNB_TV_A_CAMR_ILLUM_PTU_HTR->SetMouseRegion( AID_R14, 0.454255f, 0.643122f, 0.495128f, 0.686773f );

		pMNC_TV_B_CAMR_CAMR_PTU->SetInitialAnimState( 1.0f );
		pMNC_TV_B_CAMR_CAMR_PTU->DefineGroup( GRP_CB45_R14_VC );
		pMNC_TV_B_CAMR_CAMR_PTU->SetDirection( CB_PULL );
		pMNC_TV_B_CAMR_CAMR_PTU->SetMouseRegion( AID_R14, 0.660184f, 0.643122f, 0.695554f, 0.686773f );

		pMNC_TV_B_CAMR_CAMR_HTR->SetInitialAnimState( 1.0f );
		pMNC_TV_B_CAMR_CAMR_HTR->DefineGroup( GRP_CB46_R14_VC );
		pMNC_TV_B_CAMR_CAMR_HTR->SetDirection( CB_PULL );
		pMNC_TV_B_CAMR_CAMR_HTR->SetMouseRegion( AID_R14, 0.704346f, 0.643122f, 0.744248f, 0.686773f );

		pMNC_TV_B_CAMR_ILLUM_PTU_HTR->SetInitialAnimState( 1.0f );
		pMNC_TV_B_CAMR_ILLUM_PTU_HTR->DefineGroup( GRP_CB47_R14_VC );
		pMNC_TV_B_CAMR_ILLUM_PTU_HTR->SetDirection( CB_PULL );
		pMNC_TV_B_CAMR_ILLUM_PTU_HTR->SetMouseRegion( AID_R14, 0.753938f, 0.643122f, 0.790604f, 0.686773f );

		pMNA_TV_C_CAMR_CAMR_PTU->SetInitialAnimState( 1.0f );
		pMNA_TV_C_CAMR_CAMR_PTU->DefineGroup( GRP_CB34_R14_VC );
		pMNA_TV_C_CAMR_CAMR_PTU->SetDirection( CB_PULL );
		pMNA_TV_C_CAMR_CAMR_PTU->SetMouseRegion( AID_R14, 0.109385f, 0.643122f, 0.146533f, 0.686773f );

		pMNA_TV_C_CAMR_CAMR_HTR->SetInitialAnimState( 1.0f );
		pMNA_TV_C_CAMR_CAMR_HTR->DefineGroup( GRP_CB35_R14_VC );
		pMNA_TV_C_CAMR_CAMR_HTR->SetDirection( CB_PULL );
		pMNA_TV_C_CAMR_CAMR_HTR->SetMouseRegion( AID_R14, 0.156239f, 0.643122f, 0.196399f, 0.686773f );

		pMNA_TV_C_CAMR_ILLUM_PTU_HTR->SetInitialAnimState( 1.0f );
		pMNA_TV_C_CAMR_ILLUM_PTU_HTR->DefineGroup( GRP_CB36_R14_VC );
		pMNA_TV_C_CAMR_ILLUM_PTU_HTR->SetDirection( CB_PULL );
		pMNA_TV_C_CAMR_ILLUM_PTU_HTR->SetMouseRegion( AID_R14, 0.205871f, 0.643122f, 0.242745f, 0.686773f );

		pMNA_TV_D_CAMR_CAMR_PTU->SetInitialAnimState( 1.0f );
		pMNA_TV_D_CAMR_CAMR_PTU->DefineGroup( GRP_CB51_R14_VC );
		pMNA_TV_D_CAMR_CAMR_PTU->SetDirection( CB_PULL );
		pMNA_TV_D_CAMR_CAMR_PTU->SetMouseRegion( AID_R14, 0.205871f, 0.750616f, 0.242745f, 0.795654f );

		pMNA_TV_D_CAMR_CAMR_HTR->SetInitialAnimState( 1.0f );
		pMNA_TV_D_CAMR_CAMR_HTR->DefineGroup( GRP_CB52_R14_VC );
		pMNA_TV_D_CAMR_CAMR_HTR->SetDirection( CB_PULL );
		pMNA_TV_D_CAMR_CAMR_HTR->SetMouseRegion( AID_R14, 0.253264f, 0.750616f, 0.292443f, 0.795654f );

		pMNA_TV_D_CAMR_ILLUM_PTU_HTR->SetInitialAnimState( 1.0f );
		pMNA_TV_D_CAMR_ILLUM_PTU_HTR->DefineGroup( GRP_CB53_R14_VC );
		pMNA_TV_D_CAMR_ILLUM_PTU_HTR->SetDirection( CB_PULL );
		pMNA_TV_D_CAMR_ILLUM_PTU_HTR->SetMouseRegion( AID_R14, 0.301228f, 0.750616f, 0.336629f, 0.795654f );

		pMNB_TV_RMS_CAMR_CAMR_PTU->SetInitialAnimState( 1.0f );
		pMNB_TV_RMS_CAMR_CAMR_PTU->DefineGroup( GRP_CB55_R14_VC );
		pMNB_TV_RMS_CAMR_CAMR_PTU->SetDirection( CB_PULL );
		pMNB_TV_RMS_CAMR_CAMR_PTU->SetMouseRegion( AID_R14, 0.503839f, 0.750616f, 0.540347f, 0.795654f );

		pMNB_TV_RMS_CAMR_WRIST_ILLUM_CAMR_HTR->SetInitialAnimState( 1.0f );
		pMNB_TV_RMS_CAMR_WRIST_ILLUM_CAMR_HTR->DefineGroup( GRP_CB56_R14_VC );
		pMNB_TV_RMS_CAMR_WRIST_ILLUM_CAMR_HTR->SetDirection( CB_PULL );
		pMNB_TV_RMS_CAMR_WRIST_ILLUM_CAMR_HTR->SetMouseRegion( AID_R14, 0.549593f, 0.750616f, 0.588844f, 0.795654f );

		pMNB_TV_RMS_CAMR_ELB_ILLUM_PTU_HTR->SetInitialAnimState( 1.0f );
		pMNB_TV_RMS_CAMR_ELB_ILLUM_PTU_HTR->DefineGroup( GRP_CB57_R14_VC );
		pMNB_TV_RMS_CAMR_ELB_ILLUM_PTU_HTR->SetDirection( CB_PULL );
		pMNB_TV_RMS_CAMR_ELB_ILLUM_PTU_HTR->SetMouseRegion( AID_R14, 0.598109f, 0.750616f, 0.634106f, 0.795654f );

		pMNA_TV_CONTR_UNIT->SetInitialAnimState( 1.0f );
		pMNA_TV_CONTR_UNIT->DefineGroup( GRP_CB37_R14_VC );
		pMNA_TV_CONTR_UNIT->SetDirection( CB_PULL );
		pMNA_TV_CONTR_UNIT->SetMouseRegion( AID_R14, 0.253264f, 0.643122f, 0.292443f, 0.686773f );

		pMNB_TV_CONTR_UNIT->SetInitialAnimState( 1.0f );
		pMNB_TV_CONTR_UNIT->DefineGroup( GRP_CB42_R14_VC );
		pMNB_TV_CONTR_UNIT->SetDirection( CB_PULL );
		pMNB_TV_CONTR_UNIT->SetMouseRegion( AID_R14, 0.503839f, 0.643122f, 0.540347f, 0.686773f );

		pMNA_TV_MON_1->SetInitialAnimState( 1.0f );
		pMNA_TV_MON_1->DefineGroup( GRP_CB38_R14_VC );
		pMNA_TV_MON_1->SetDirection( CB_PULL );
		pMNA_TV_MON_1->SetMouseRegion( AID_R14, 0.301228f, 0.643122f, 0.336629f, 0.686773f );

		pMNB_TV_MON_2->SetInitialAnimState( 1.0f );
		pMNB_TV_MON_2->DefineGroup( GRP_CB43_R14_VC );
		pMNB_TV_MON_2->SetDirection( CB_PULL );
		pMNB_TV_MON_2->SetMouseRegion( AID_R14, 0.549593f, 0.643122f, 0.588844f, 0.686773f );
		return;
	}

	void PanelR14::RegisterVC( void )
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET + OFFSET_PANEL;

		oapiVCRegisterArea( AID_R14, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_R14,
			_V( -0.254983, 0.426891, 0.0 ) + ofs, _V( -0.254983, 0.426891, -0.519337 ) + ofs,
			_V( 0.0, 0.0, 0.0 ) + ofs, _V( 0.0, 0.0, -0.519337 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelR14::Realize( void )
	{
		AtlantisPanel::Realize();

		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "MDU_ADC_Power", 16 );
		pMNC_MDU_CDR_1->Connect( pBundle, 0 );
		pMNB_MDU_CDR_2->Connect( pBundle, 1 );
		pMNB_MDU_MFD_1->Connect( pBundle, 2 );
		pMNA_MDU_MFD_2->Connect( pBundle, 3 );
		pMNA_MDU_PLT_1->Connect( pBundle, 4 );
		pMNC_MDU_PLT_2->Connect( pBundle, 5 );
		pMNC_MDU_AFD_1->Connect( pBundle, 6 );
		pMNA_ADC_1A_2A->Connect( pBundle, 7 );
		pMNB_ADC_1B_2B->Connect( pBundle, 8 );

		pBundle = STS()->BundleManager()->CreateBundle( "CAMERA_POWER", 16 );
		pMNB_TV_A_CAMR_CAMR_PTU->Connect( pBundle, 0 );
		pMNB_TV_A_CAMR_CAMR_HTR->Connect( pBundle, 1 );
		pMNB_TV_A_CAMR_ILLUM_PTU_HTR->Connect( pBundle, 2 );

		pMNC_TV_B_CAMR_CAMR_PTU->Connect( pBundle, 3 );
		pMNC_TV_B_CAMR_CAMR_HTR->Connect( pBundle, 4 );
		pMNC_TV_B_CAMR_ILLUM_PTU_HTR->Connect( pBundle, 5 );

		pMNA_TV_C_CAMR_CAMR_PTU->Connect( pBundle, 6 );
		pMNA_TV_C_CAMR_CAMR_HTR->Connect( pBundle, 7 );
		pMNA_TV_C_CAMR_ILLUM_PTU_HTR->Connect( pBundle, 8 );

		pMNA_TV_D_CAMR_CAMR_PTU->Connect( pBundle, 9 );
		pMNA_TV_D_CAMR_CAMR_HTR->Connect( pBundle, 10 );
		pMNA_TV_D_CAMR_ILLUM_PTU_HTR->Connect( pBundle, 11 );

		pMNB_TV_RMS_CAMR_CAMR_PTU->Connect( pBundle, 12 );
		pMNB_TV_RMS_CAMR_WRIST_ILLUM_CAMR_HTR->Connect( pBundle, 13 );
		pMNB_TV_RMS_CAMR_ELB_ILLUM_PTU_HTR->Connect( pBundle, 14 );

		pBundle = STS()->BundleManager()->CreateBundle( "VCU_MON_POWER", 16 );
		pMNA_TV_CONTR_UNIT->Connect( pBundle, 2 );
		pMNB_TV_CONTR_UNIT->Connect( pBundle, 3 );
		pMNA_TV_MON_1->Connect( pBundle, 4 );
		pMNB_TV_MON_2->Connect( pBundle, 5 );
		return;
	}
}

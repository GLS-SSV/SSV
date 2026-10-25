#include "PanelA13_102.h"
#include "StandardSwitch.h"
#include "ThumbWheel.h"
#include "RotarySwitchPotentiometer.h"
#include "StandardRotarySwitch.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_a13_102.h"


namespace vc
{
	const static char* MESHNAME_PANEL = "SSV\\OV\\PanelA13_102";
	constexpr VECTOR3 OFFSET_PANEL = {-0.2667, 1.79193, 12.4756};


	PanelA13_102::PanelA13_102( Atlantis* _sts ) : AtlantisPanel( _sts, "A13" )
	{
		DefineMesh( MESHNAME_PANEL, OFFSET_PANEL );

		Add( pOS_AUDIO_PAGE = new StdSwitch2( _sts, "OS AUDIO PAGE" ) );

		Add( pOS_AUDIO_POWER = new StdSwitch3( _sts, "OS AUDIO POWER" ) );
		pOS_AUDIO_POWER->SetLabel( 0, "OFF" );
		pOS_AUDIO_POWER->SetLabel( 1, "AUD" );
		pOS_AUDIO_POWER->SetLabel( 2, "AUD/TONE" );

		Add( pOS_AUDIO_AG_1 = new StdSwitch3( _sts, "OS AUDIO A/G 1" ) );
		pOS_AUDIO_AG_1->SetLabel( 0, "OFF" );
		pOS_AUDIO_AG_1->SetLabel( 1, "RCV" );
		pOS_AUDIO_AG_1->SetLabel( 2, "T/R" );

		Add( pOS_AUDIO_AG_2 = new StdSwitch3( _sts, "OS AUDIO A/G 2" ) );
		pOS_AUDIO_AG_2->SetLabel( 0, "OFF" );
		pOS_AUDIO_AG_2->SetLabel( 1, "RCV" );
		pOS_AUDIO_AG_2->SetLabel( 2, "T/R" );

		Add( pOS_AUDIO_AA = new StdSwitch3( _sts, "OS AUDIO A/A" ) );
		pOS_AUDIO_AA->SetLabel( 0, "OFF" );
		pOS_AUDIO_AA->SetLabel( 1, "RCV" );
		pOS_AUDIO_AA->SetLabel( 2, "T/R" );

		Add( pOS_AUDIO_ICOM_A = new StdSwitch3( _sts, "OS AUDIO ICOM A" ) );
		pOS_AUDIO_ICOM_A->SetLabel( 0, "OFF" );
		pOS_AUDIO_ICOM_A->SetLabel( 1, "RCV" );
		pOS_AUDIO_ICOM_A->SetLabel( 2, "T/R" );

		Add( pOS_AUDIO_ICOM_B = new StdSwitch3( _sts, "OS AUDIO ICOM B" ) );
		pOS_AUDIO_ICOM_B->SetLabel( 0, "OFF" );
		pOS_AUDIO_ICOM_B->SetLabel( 1, "RCV" );
		pOS_AUDIO_ICOM_B->SetLabel( 2, "T/R" );

		Add( pOS_AUDIO_SPKR_PWR = new StdSwitch3( _sts, "OS AUDIO SPKR PWR" ) );
		pOS_AUDIO_SPKR_PWR->SetLabel( 0, "OFF" );
		pOS_AUDIO_SPKR_PWR->SetLabel( 1, "SPKR" );
		pOS_AUDIO_SPKR_PWR->SetLabel( 2, "SPKR/MIC" );

		Add( pOS_AUDIO_VOX_SENSE = new RotarySwitchPotentiometer( _sts, "OS AUDIO VOX SENSE" ) );
		Add( pOS_AUDIO_MASTER_SPEAKER_VOLUME = new RotarySwitchPotentiometer( _sts, "OS AUDIO MASTER SPEAKER VOLUME" ) );

		Add( pOS_AUDIO_XMIT_ICOM_MODE = new RotaryDemuxSwitch( _sts, "OS AUDIO XMIT ICOM MODE", 4 ) );
		pOS_AUDIO_XMIT_ICOM_MODE->SetLabel( 0, "PTT/HOT" );
		pOS_AUDIO_XMIT_ICOM_MODE->SetLabel( 1, "PTT/VOX" );
		pOS_AUDIO_XMIT_ICOM_MODE->SetLabel( 2, "PTT/PTT" );
		pOS_AUDIO_XMIT_ICOM_MODE->SetLabel( 3, "VOX/VOX" );

		Add( pOS_AUDIO_VOLUME_AG_1 = new ThumbWheel( _sts, "OS AUDIO VOLUME A/G 1" ) );
		Add( pOS_AUDIO_VOLUME_AG_2 = new ThumbWheel( _sts, "OS AUDIO VOLUME A/G 2" ) );
		Add( pOS_AUDIO_VOLUME_AA = new ThumbWheel( _sts, "OS AUDIO VOLUME A/A" ) );
		Add( pOS_AUDIO_VOLUME_ICOM_A = new ThumbWheel( _sts, "OS AUDIO VOLUME ICOM A" ) );
		Add( pOS_AUDIO_VOLUME_ICOM_B = new ThumbWheel( _sts, "OS AUDIO VOLUME ICOM B" ) );
		return;
	}

	PanelA13_102::~PanelA13_102( void )
	{
		return;
	}

	void PanelA13_102::DefineVC( void )
	{
		const VECTOR3 switch_rot =  _V( -1.0, 0.0, 0.0 );
		const VECTOR3 rotary_switch_rot	 =  _V( 0.0, 0.0, 1.0 );

		AddAIDToMouseEventList( AID_A13 );

		pOS_AUDIO_PAGE->DefineGroup( GRP_S7_A13_102_VC );
		pOS_AUDIO_PAGE->SetInitialAnimState( 0.5 );
		pOS_AUDIO_PAGE->SetReference( _V( 0.0, 0.115642, -0.025329 ), switch_rot );
		pOS_AUDIO_PAGE->SetMouseRegion( AID_A13, 0.133112f, 0.584559f, 0.175175f, 0.657561f );
		pOS_AUDIO_PAGE->SetSpringLoaded( true );

		pOS_AUDIO_POWER->DefineGroup( GRP_S1_A13_102_VC );
		pOS_AUDIO_POWER->SetInitialAnimState( 0.5 );
		pOS_AUDIO_POWER->SetReference( _V( 0.0, 0.192517, -0.025329 ), switch_rot );
		pOS_AUDIO_POWER->SetMouseRegion( AID_A13, 0.133112f, 0.348200f, 0.175175f, 0.420804f );

		pOS_AUDIO_AG_1->DefineGroup( GRP_S2_A13_102_VC );
		pOS_AUDIO_AG_1->SetInitialAnimState( 0.5 );
		pOS_AUDIO_AG_1->SetReference( _V( 0.0, 0.192517, -0.025329 ), switch_rot );
		pOS_AUDIO_AG_1->SetMouseRegion( AID_A13, 0.248487f, 0.348200f, 0.290855f, 0.420804f );

		pOS_AUDIO_AG_2->DefineGroup( GRP_S3_A13_102_VC );
		pOS_AUDIO_AG_2->SetInitialAnimState( 0.5 );
		pOS_AUDIO_AG_2->SetReference( _V( 0.0, 0.192517, -0.025329 ), switch_rot );
		pOS_AUDIO_AG_2->SetMouseRegion( AID_A13, 0.319033f, 0.348200f, 0.361841f, 0.420804f );

		pOS_AUDIO_AA->DefineGroup( GRP_S4_A13_102_VC );
		pOS_AUDIO_AA->SetInitialAnimState( 0.5 );
		pOS_AUDIO_AA->SetReference( _V( 0.0, 0.192517, -0.025329 ), switch_rot );
		pOS_AUDIO_AA->SetMouseRegion( AID_A13, 0.385448f, 0.348200f, 0.428570f, 0.420804f );

		pOS_AUDIO_ICOM_A->DefineGroup( GRP_S5_A13_102_VC );
		pOS_AUDIO_ICOM_A->SetInitialAnimState( 0.5 );
		pOS_AUDIO_ICOM_A->SetReference( _V( 0.0, 0.192517, -0.025329 ), switch_rot );
		pOS_AUDIO_ICOM_A->SetMouseRegion( AID_A13, 0.456062f, 0.348200f, 0.499781f, 0.420804f );

		pOS_AUDIO_ICOM_B->DefineGroup( GRP_S6_A13_102_VC );
		pOS_AUDIO_ICOM_B->SetInitialAnimState( 0.5 );
		pOS_AUDIO_ICOM_B->SetReference( _V( 0.0, 0.192517, -0.025329 ), switch_rot );
		pOS_AUDIO_ICOM_B->SetMouseRegion( AID_A13, 0.523559f, 0.348200f, 0.566008f, 0.420804f );

		pOS_AUDIO_SPKR_PWR->DefineGroup( GRP_S10_A13_102_VC );
		pOS_AUDIO_SPKR_PWR->SetInitialAnimState( 0.5 );
		pOS_AUDIO_SPKR_PWR->SetReference( _V( 0.0, 0.115847, -0.025329 ), switch_rot );
		pOS_AUDIO_SPKR_PWR->SetMouseRegion( AID_A13, 0.774921f, 0.583987f, 0.816176f, 0.654383f );

		pOS_AUDIO_VOX_SENSE->DefineGroup( GRP_R1_A13_102_VC );
		pOS_AUDIO_VOX_SENSE->SetInitialAnimState( 0.5 );
		pOS_AUDIO_VOX_SENSE->SetReference( _V( 0.174308, 0.195321, 0.0 ), rotary_switch_rot );
		pOS_AUDIO_VOX_SENSE->SetMouseRegion( AID_A13, 0.635569f, 0.323541f, 0.711556f, 0.446770f );
		pOS_AUDIO_VOX_SENSE->SetAngleRange( 330.0 );

		pOS_AUDIO_MASTER_SPEAKER_VOLUME->DefineGroup( GRP_R2_A13_102_VC );
		pOS_AUDIO_MASTER_SPEAKER_VOLUME->SetInitialAnimState( 0.5 );
		pOS_AUDIO_MASTER_SPEAKER_VOLUME->SetReference( _V( 0.105666, 0.195321, 0.0 ), rotary_switch_rot );
		pOS_AUDIO_MASTER_SPEAKER_VOLUME->SetMouseRegion( AID_A13, 0.765740f, 0.323541f, 0.837536f, 0.446770f );
		pOS_AUDIO_MASTER_SPEAKER_VOLUME->SetAngleRange( 330.0 );

		pOS_AUDIO_XMIT_ICOM_MODE->DefineGroup( GRP_S11_A13_102_VC );
		pOS_AUDIO_XMIT_ICOM_MODE->SetInitialAnimState( 0.5 );
		pOS_AUDIO_XMIT_ICOM_MODE->SetReference( _V( 0.174308, 0.119339, 0.0 ), rotary_switch_rot );
		pOS_AUDIO_XMIT_ICOM_MODE->SetMouseRegion( AID_A13, 0.635569f, 0.564375f, 0.711556f, 0.689896f );
		pOS_AUDIO_XMIT_ICOM_MODE->DefineRotationAngle( 96.0f );
		pOS_AUDIO_XMIT_ICOM_MODE->SetOffset( -48.0f );

		{
			const VECTOR3 pos = _V( 0.0, 0.117, -0.02117 );

			pOS_AUDIO_VOLUME_AG_1->DefineWheelGroup( GRP_S8_THUMBWHEEL_AG_1_A13_102_VC );
			pOS_AUDIO_VOLUME_AG_1->SetReference( pos, switch_rot );
			pOS_AUDIO_VOLUME_AG_1->SetMouseRegion( AID_A13, 0.342878f, 0.586698f, 0.353147f, 0.674005f );
			pOS_AUDIO_VOLUME_AG_1->SetBounds( 0, 9 );

			pOS_AUDIO_VOLUME_AG_2->DefineWheelGroup( GRP_S8_THUMBWHEEL_AG_2_A13_102_VC );
			pOS_AUDIO_VOLUME_AG_2->SetReference( pos, switch_rot );
			pOS_AUDIO_VOLUME_AG_2->SetMouseRegion( AID_A13, 0.378593f, 0.586698f, 0.388632f, 0.674005f );
			pOS_AUDIO_VOLUME_AG_2->SetBounds( 0, 9 );

			pOS_AUDIO_VOLUME_AA->DefineWheelGroup( GRP_S8_THUMBWHEEL_AA_A13_102_VC );
			pOS_AUDIO_VOLUME_AA->SetReference( pos, switch_rot );
			pOS_AUDIO_VOLUME_AA->SetMouseRegion( AID_A13, 0.414247f, 0.586698f, 0.423880f, 0.674005f );
			pOS_AUDIO_VOLUME_AA->SetBounds( 0, 9 );

			pOS_AUDIO_VOLUME_ICOM_A->DefineWheelGroup( GRP_S8_THUMBWHEEL_ICOM_A_A13_102_VC );
			pOS_AUDIO_VOLUME_ICOM_A->SetReference( pos, switch_rot );
			pOS_AUDIO_VOLUME_ICOM_A->SetMouseRegion( AID_A13, 0.449443f, 0.586698f, 0.459468f, 0.674005f );
			pOS_AUDIO_VOLUME_ICOM_A->SetBounds( 0, 9 );

			pOS_AUDIO_VOLUME_ICOM_B->DefineWheelGroup( GRP_S8_THUMBWHEEL_ICOM_B_A13_102_VC );
			pOS_AUDIO_VOLUME_ICOM_B->SetReference( pos, switch_rot );
			pOS_AUDIO_VOLUME_ICOM_B->SetMouseRegion( AID_A13, 0.484779f, 0.586698f, 0.495206f, 0.674005f );
			pOS_AUDIO_VOLUME_ICOM_B->SetBounds( 0, 9 );
		}
		return;
	}

	void PanelA13_102::RegisterVC( void )
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET + OFFSET_PANEL;

		oapiVCRegisterArea( AID_A13, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_A13,
			_V( 0.5334, 0.3175, 0.0 ) + ofs, _V( 0.0, 0.3175, 0.0 ) + ofs,
			_V( 0.5334, 0.0, 0.0 ) + ofs, _V( 0.0, 0.0, 0.0 ) + ofs );
		return;
	}

	void PanelA13_102::Realize( void )
	{
		AtlantisPanel::Realize();

		// TODO
		return;
	}
}

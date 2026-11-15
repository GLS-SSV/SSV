#include "PanelA13.h"
#include "StandardSwitch.h"
#include "RotarySwitchPotentiometer.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_a13.h"


namespace vc
{
	const static char* MESHNAME_PANEL = "SSV\\OV\\PanelA13";
	constexpr VECTOR3 OFFSET_PANEL = {-0.2667, 1.79193, 12.4756};


	PanelA13::PanelA13( Atlantis* _sts, const std::string& ov ) : AtlantisPanel( _sts, "A13" ),
		hOV099Texture(NULL), OV099(false)
	{
		DefineMesh( MESHNAME_PANEL, OFFSET_PANEL );

		Add( pGPS_PRE_AMP_LC = new StdSwitch3( _sts, "GPS PRE AMP LC" ) );
		pGPS_PRE_AMP_LC->SetLabel( 0, "MN A" );
		pGPS_PRE_AMP_LC->SetLabel( 1, "OFF" );
		pGPS_PRE_AMP_LC->SetLabel( 2, "MN C" );

		Add( pGPS_PRE_AMP_UC = new StdSwitch3( _sts, "GPS PRE AMP UC" ) );
		pGPS_PRE_AMP_UC->SetLabel( 0, "MN C" );
		pGPS_PRE_AMP_UC->SetLabel( 1, "OFF" );
		pGPS_PRE_AMP_UC->SetLabel( 2, "MN A" );

		if (ov == "Challenger")
		{
			OV099 = true;
			Add( pS14 = new StdSwitch2( _sts, "GPS RECEIVER/PROCESSOR ASSY POWER 1" ) );
			pS14->SetLabel( 0, "OFF" );
			pS14->SetLabel( 1, "ON" );

			Add( pS15 = new StdSwitch2( _sts, "GPS RECEIVER/PROCESSOR ASSY POWER 2" ) );
			pS15->SetLabel( 0, "OFF" );
			pS15->SetLabel( 1, "ON" );

			Add( pS16 = new StdSwitch3( _sts, "GPS RECEIVER/PROCESSOR ASSY MODE 1" ) );
			pS16->SetLabel( 0, "DUMP" );
			pS16->SetLabel( 1, "HALT" );
			pS16->SetLabel( 2, "RUN" );

			Add( pS17 = new StdSwitch3( _sts, "GPS RECEIVER/PROCESSOR ASSY MODE 2" ) );
			pS17->SetLabel( 0, "DUMP" );
			pS17->SetLabel( 1, "HALT" );
			pS17->SetLabel( 2, "RUN" );
		}
		else
		{
			Add( pS14 = new StdSwitch2( _sts, "GPS MAGAR POWER" ) );
			pS14->SetLabel( 0, "OFF" );
			pS14->SetLabel( 1, "ON" );

			Add( pS15 = new StdSwitch2( _sts, "GPS SIGI POWER" ) );
			pS15->SetLabel( 0, "OFF" );
			pS15->SetLabel( 1, "ON" );

			Add( pS16 = new StdSwitch3( _sts, "GPS MAGAR ENCRYPT" ) );
			pS16->SetLabel( 0, "NORMAL" );
			pS16->SetLabel( 1, "HALT" );
			pS16->SetLabel( 2, "ZEROIZE" );

			Add( pS17 = new StdSwitch3( _sts, "GPS SIGI ENCRYPT" ) );
			pS17->SetLabel( 0, "NORMAL" );
			pS17->SetLabel( 1, "HALT" );
			pS17->SetLabel( 2, "ZEROIZE" );
		}

		Add( pOS_AUDIO_SPKR_PWR = new StdSwitch3( _sts, "OS AUDIO SPKR PWR" ) );
		pOS_AUDIO_SPKR_PWR->SetLabel( 0, "OFF" );
		pOS_AUDIO_SPKR_PWR->SetLabel( 1, "SPKR" );
		pOS_AUDIO_SPKR_PWR->SetLabel( 2, "SPKR/MIC" );

		Add( pOS_AUDIO_MASTER_SPEAKER_VOLUME = new RotarySwitchPotentiometer( _sts, "OS AUDIO MASTER SPEAKER VOLUME" ) );
		return;
	}

	PanelA13::~PanelA13( void )
	{
		if (hOV099Texture) oapiReleaseTexture( hOV099Texture );
		return;
	}

	void PanelA13::DefineVC( void )
	{
		const VECTOR3 switch_rot =  _V( -1.0, 0.0, 0.0 );
		const VECTOR3 rotary_switch_rot	 =  _V( 0.0, 0.0, 1.0 );

		AddAIDToMouseEventList( AID_A13 );

		pGPS_PRE_AMP_LC->DefineGroup( GRP_S12_A13_VC );
		pGPS_PRE_AMP_LC->SetInitialAnimState( 0.5 );
		pGPS_PRE_AMP_LC->SetReference(_V( 0.0, 0.115642, -0.025329 ), switch_rot );
		pGPS_PRE_AMP_LC->SetMouseRegion( AID_A13, 0.133112f, 0.584559f, 0.175175f, 0.657561f );

		pGPS_PRE_AMP_UC->DefineGroup( GRP_S13_A13_VC );
		pGPS_PRE_AMP_UC->SetInitialAnimState( 0.5 );
		pGPS_PRE_AMP_UC->SetReference( _V( 0.0, 0.192517, -0.025329 ), switch_rot );
		pGPS_PRE_AMP_UC->SetMouseRegion( AID_A13, 0.133112f, 0.348200f, 0.175175f, 0.420804f );

		pS14->DefineGroup( GRP_S14_A13_VC );
		pS14->SetInitialAnimState( 0.5 );
		pS14->SetReference( _V( 0.0, 0.192517, -0.025329 ), switch_rot );
		pS14->SetMouseRegion( AID_A13, 0.242606f, 0.348200f, 0.283769f, 0.420804f );

		pS15->DefineGroup( GRP_S15_A13_VC );
		pS15->SetInitialAnimState( 0.5 );
		pS15->SetReference( _V( 0.0, 0.192517, -0.025329 ), switch_rot );
		pS15->SetMouseRegion( AID_A13, 0.297844f, 0.348200f, 0.339818f, 0.420804f );

		pS16->DefineGroup( GRP_S16_A13_VC );
		pS16->SetInitialAnimState( 0.5 );
		pS16->SetReference( _V( 0.0, 0.192517, -0.025329 ), switch_rot );
		pS16->SetMouseRegion( AID_A13, 0.410435f, 0.348200f, 0.451617f, 0.420804f );

		pS17->DefineGroup( GRP_S17_A13_VC );
		pS17->SetInitialAnimState( 0.5 );
		pS17->SetReference( _V( 0.0, 0.192517, -0.025329 ), switch_rot );
		pS17->SetMouseRegion( AID_A13, 0.464404f, 0.348200f, 0.506193f, 0.420804f );

		pOS_AUDIO_SPKR_PWR->DefineGroup( GRP_S10_A13_VC );
		pOS_AUDIO_SPKR_PWR->SetInitialAnimState( 0.5 );
		pOS_AUDIO_SPKR_PWR->SetReference( _V( 0.0, 0.115847, -0.025329 ), switch_rot );
		pOS_AUDIO_SPKR_PWR->SetMouseRegion( AID_A13, 0.774921f, 0.583987f, 0.816176f, 0.654383f );

		pOS_AUDIO_MASTER_SPEAKER_VOLUME->DefineGroup( GRP_R2_A13_VC );
		pOS_AUDIO_MASTER_SPEAKER_VOLUME->SetInitialAnimState( 0.5 );
		pOS_AUDIO_MASTER_SPEAKER_VOLUME->SetReference( _V( 0.105666, 0.195321, 0.0 ), rotary_switch_rot );
		pOS_AUDIO_MASTER_SPEAKER_VOLUME->SetMouseRegion( AID_A13, 0.765740f, 0.323541f, 0.837536f, 0.446770f );
		pOS_AUDIO_MASTER_SPEAKER_VOLUME->SetAngleRange( 330.0 );
		return;
	}

	void PanelA13::RegisterVC( void )
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET + OFFSET_PANEL;

		oapiVCRegisterArea( AID_A13, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_A13,
			_V( 0.5334, 0.3175, 0.0 ) + ofs, _V( 0.0, 0.3175, 0.0 ) + ofs,
			_V( 0.5334, 0.0, 0.0 ) + ofs, _V( 0.0, 0.0, 0.0 ) + ofs );
		return;
	}

	void PanelA13::Realize( void )
	{
		AtlantisPanel::Realize();

		// TODO
		return;
	}

	void PanelA13::VisualCreated( void )
	{
		// change texture
		if (OV099)
		{
			DEVMESHHANDLE hDevMesh = STS()->GetDevMesh( STS()->Get_vis(), GetVCMeshIndex() );
			if (hDevMesh != NULL)
			{
				if (hOV099Texture == NULL) hOV099Texture = oapiLoadTexture( "SSV\\OV\\panelA13_099.dds" );
				if (hOV099Texture == NULL) throw std::exception( "Could not load texture in panel A13" );
				else oapiSetTexture( hDevMesh, TEX_SSV_OV_PANELA13_A13_VC, hOV099Texture );
			}
		}

		AtlantisPanel::VisualCreated();
		return;
	}
}

#include "PanelA14.h"
#include "StandardSwitch.h"
#include "StandardSwitchCover.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_a14.h"


namespace vc
{
	const static char* MESHNAME_PANEL = "SSV\\OV\\PanelA14";
	constexpr VECTOR3 OFFSET_PANEL = {-0.8001, 1.79193, 12.4756};


	PanelA14::PanelA14( Atlantis* _sts, const std::string &orbiter ) : AtlantisPanel( _sts, "A14" ),
		hOV103105Texture(NULL), mplm(false)
	{
		if ((orbiter == "Discovery") || (orbiter == "Endeavour")) mplm = true;

		DefineMesh( MESHNAME_PANEL, OFFSET_PANEL );

		Add( pRCSOMS_HEATERS_FWD_RCS = new StdSwitch3( _sts, "RCS/OMS HEATERS FWD RCS" ) );
		pRCSOMS_HEATERS_FWD_RCS->SetLabel( 0, "B AUTO" );
		pRCSOMS_HEATERS_FWD_RCS->SetLabel( 1, "OFF" );
		pRCSOMS_HEATERS_FWD_RCS->SetLabel( 2, "A AUTO" );

		Add( pRCSOMS_HEATERS_LEFT_POD_A_Cover = new StandardSwitchCover( _sts, "RCS/OMS HEATERS LEFT POD A COVER" ) );

		Add( pRCSOMS_HEATERS_LEFT_POD_A = new StdSwitch2( _sts, "RCS/OMS HEATERS LEFT POD A" ) );
		pRCSOMS_HEATERS_LEFT_POD_A->SetLabel( 0, "OFF" );
		pRCSOMS_HEATERS_LEFT_POD_A->SetLabel( 1, "AUTO" );

		Add( pRCSOMS_HEATERS_LEFT_POD_B_Cover = new StandardSwitchCover( _sts, "RCS/OMS HEATERS LEFT POD B COVER" ) );

		Add( pRCSOMS_HEATERS_LEFT_POD_B = new StdSwitch2( _sts, "RCS/OMS HEATERS LEFT POD B" ) );
		pRCSOMS_HEATERS_LEFT_POD_B->SetLabel( 0, "OFF" );
		pRCSOMS_HEATERS_LEFT_POD_B->SetLabel( 1, "AUTO" );

		Add( pRCSOMS_HEATERS_RIGHT_POD_A_Cover = new StandardSwitchCover( _sts, "RCS/OMS HEATERS RIGHT POD A COVER" ) );

		Add( pRCSOMS_HEATERS_RIGHT_POD_A = new StdSwitch2( _sts, "RCS/OMS HEATERS RIGHT POD A" ) );
		pRCSOMS_HEATERS_RIGHT_POD_A->SetLabel( 0, "OFF" );
		pRCSOMS_HEATERS_RIGHT_POD_A->SetLabel( 1, "AUTO" );

		Add( pRCSOMS_HEATERS_RIGHT_POD_B_Cover = new StandardSwitchCover( _sts, "RCS/OMS HEATERS RIGHT POD B COVER" ) );

		Add( pRCSOMS_HEATERS_RIGHT_POD_B = new StdSwitch2( _sts, "RCS/OMS HEATERS RIGHT POD B" ) );
		pRCSOMS_HEATERS_RIGHT_POD_B->SetLabel( 0, "OFF" );
		pRCSOMS_HEATERS_RIGHT_POD_B->SetLabel( 1, "AUTO" );

		Add( pRCSOMS_HEATERS_FWD_RCS_JET_1 = new StdSwitch2( _sts, "RCS/OMS HEATERS FWD RCS JET 1" ) );
		pRCSOMS_HEATERS_FWD_RCS_JET_1->SetLabel( 0, "OFF" );
		pRCSOMS_HEATERS_FWD_RCS_JET_1->SetLabel( 1, "AUTO" );

		Add( pRCSOMS_HEATERS_FWD_RCS_JET_2 = new StdSwitch2( _sts, "RCS/OMS HEATERS FWD RCS JET 2" ) );
		pRCSOMS_HEATERS_FWD_RCS_JET_2->SetLabel( 0, "OFF" );
		pRCSOMS_HEATERS_FWD_RCS_JET_2->SetLabel( 1, "AUTO" );

		Add( pRCSOMS_HEATERS_FWD_RCS_JET_3 = new StdSwitch2( _sts, "RCS/OMS HEATERS FWD RCS JET 3" ) );
		pRCSOMS_HEATERS_FWD_RCS_JET_3->SetLabel( 0, "OFF" );
		pRCSOMS_HEATERS_FWD_RCS_JET_3->SetLabel( 1, "AUTO" );

		Add( pRCSOMS_HEATERS_FWD_RCS_JET_4 = new StdSwitch2( _sts, "RCS/OMS HEATERS FWD RCS JET 4" ) );
		pRCSOMS_HEATERS_FWD_RCS_JET_4->SetLabel( 0, "OFF" );
		pRCSOMS_HEATERS_FWD_RCS_JET_4->SetLabel( 1, "AUTO" );

		Add( pRCSOMS_HEATERS_FWD_RCS_JET_5 = new StdSwitch2( _sts, "RCS/OMS HEATERS FWD RCS JET 5" ) );
		pRCSOMS_HEATERS_FWD_RCS_JET_5->SetLabel( 0, "OFF" );
		pRCSOMS_HEATERS_FWD_RCS_JET_5->SetLabel( 1, "AUTO" );

		Add( pRCSOMS_HEATERS_AFT_RCS_JET_1 = new StdSwitch2( _sts, "RCS/OMS HEATERS AFT RCS JET 1" ) );
		pRCSOMS_HEATERS_AFT_RCS_JET_1->SetLabel( 0, "OFF" );
		pRCSOMS_HEATERS_AFT_RCS_JET_1->SetLabel( 1, "AUTO" );

		Add( pRCSOMS_HEATERS_AFT_RCS_JET_2 = new StdSwitch2( _sts, "RCS/OMS HEATERS AFT RCS JET 2" ) );
		pRCSOMS_HEATERS_AFT_RCS_JET_2->SetLabel( 0, "OFF" );
		pRCSOMS_HEATERS_AFT_RCS_JET_2->SetLabel( 1, "AUTO" );

		Add( pRCSOMS_HEATERS_AFT_RCS_JET_3 = new StdSwitch2( _sts, "RCS/OMS HEATERS AFT RCS JET 3" ) );
		pRCSOMS_HEATERS_AFT_RCS_JET_3->SetLabel( 0, "OFF" );
		pRCSOMS_HEATERS_AFT_RCS_JET_3->SetLabel( 1, "AUTO" );

		Add( pRCSOMS_HEATERS_AFT_RCS_JET_4 = new StdSwitch2( _sts, "RCS/OMS HEATERS AFT RCS JET 4" ) );
		pRCSOMS_HEATERS_AFT_RCS_JET_4->SetLabel( 0, "OFF" );
		pRCSOMS_HEATERS_AFT_RCS_JET_4->SetLabel( 1, "AUTO" );

		Add( pRCSOMS_HEATERS_AFT_RCS_JET_5 = new StdSwitch2( _sts, "RCS/OMS HEATERS AFT RCS JET 5" ) );
		pRCSOMS_HEATERS_AFT_RCS_JET_5->SetLabel( 0, "OFF" );
		pRCSOMS_HEATERS_AFT_RCS_JET_5->SetLabel( 1, "AUTO" );

		Add( pRCSOMS_HEATERS_OMS_KIT = new StdSwitch3( _sts, "RCS/OMS HEATERS OMS KIT" ) );
		pRCSOMS_HEATERS_OMS_KIT->SetLabel( 0, "B AUTO" );
		pRCSOMS_HEATERS_OMS_KIT->SetLabel( 1, "OFF" );
		pRCSOMS_HEATERS_OMS_KIT->SetLabel( 2, "A AUTO" );

		Add( pRCSOMS_HEATERS_OMS_CRSFD_LINES_A = new StdSwitch2( _sts, "RCS/OMS HEATERS OMS CRSFD LINES A" ) );
		pRCSOMS_HEATERS_OMS_CRSFD_LINES_A->SetLabel( 0, "OFF" );
		pRCSOMS_HEATERS_OMS_CRSFD_LINES_A->SetLabel( 1, "AUTO" );

		Add( pRCSOMS_HEATERS_OMS_CRSFD_LINES_B = new StdSwitch2( _sts, "RCS/OMS HEATERS OMS CRSFD LINES B" ) );
		pRCSOMS_HEATERS_OMS_CRSFD_LINES_B->SetLabel( 0, "OFF" );
		pRCSOMS_HEATERS_OMS_CRSFD_LINES_B->SetLabel( 1, "AUTO" );

		Add( pPYRO_Cover = new StandardSwitchCover( _sts, "PYRO COVER" ) );

		Add( pPYRO_KU_ANT_ARM = new LockableLever2( _sts, "PYRO KU ANT ARM" ) );
		pPYRO_KU_ANT_ARM->SetLabel( 0, "SAFE" );
		pPYRO_KU_ANT_ARM->SetLabel( 1, "ARM" );

		Add( pPYRO_KU_ANT_JETT = new LockableLever2( _sts, "PYRO KU ANT JETT" ) );
		pPYRO_KU_ANT_JETT->SetLabel( 0, "SAFE" );
		pPYRO_KU_ANT_JETT->SetLabel( 1, "JETT" );

		Add( pPYRO_STARBOARD_RMS_ARM = new LockableLever3( _sts, "PYRO STARBOARD RMS ARM" ) );
		pPYRO_STARBOARD_RMS_ARM->SetLabel( 0, "GUILLOTINE" );
		pPYRO_STARBOARD_RMS_ARM->SetLabel( 1, "SAFE" );
		pPYRO_STARBOARD_RMS_ARM->SetLabel( 2, "JETT" );

		Add( pPYRO_STARBOARD_RMS_SHLDR = new LockableLever3( _sts, "PYRO STARBOARD RMS SHLDR" ) );
		pPYRO_STARBOARD_RMS_SHLDR->SetLabel( 0, "GUILLOTINE" );
		pPYRO_STARBOARD_RMS_SHLDR->SetLabel( 1, "SAFE" );
		pPYRO_STARBOARD_RMS_SHLDR->SetLabel( 2, "JETT" );

		Add( pPYRO_STARBOARD_RMS_LATCHES_FWD = new LockableLever3( _sts, "PYRO STARBOARD RMS LATCHES FWD" ) );
		pPYRO_STARBOARD_RMS_LATCHES_FWD->SetLabel( 0, "GUILLOTINE" );
		pPYRO_STARBOARD_RMS_LATCHES_FWD->SetLabel( 1, "SAFE" );
		pPYRO_STARBOARD_RMS_LATCHES_FWD->SetLabel( 2, "JETT" );

		Add( pPYRO_STARBOARD_RMS_LATCHES_MID = new LockableLever3( _sts, "PYRO STARBOARD RMS LATCHES MID" ) );
		pPYRO_STARBOARD_RMS_LATCHES_MID->SetLabel( 0, "GUILLOTINE" );
		pPYRO_STARBOARD_RMS_LATCHES_MID->SetLabel( 1, "SAFE" );
		pPYRO_STARBOARD_RMS_LATCHES_MID->SetLabel( 2, "JETT" );

		Add( pPYRO_STARBOARD_RMS_LATCHES_AFT = new LockableLever3( _sts, "PYRO STARBOARD RMS LATCHES AFT" ) );
		pPYRO_STARBOARD_RMS_LATCHES_AFT->SetLabel( 0, "GUILLOTINE" );
		pPYRO_STARBOARD_RMS_LATCHES_AFT->SetLabel( 1, "SAFE" );
		pPYRO_STARBOARD_RMS_LATCHES_AFT->SetLabel( 2, "JETT" );

		Add( pPYRO_PORT_RMS_ARM = new LockableLever3( _sts, "PYRO PORT RMS ARM" ) );
		pPYRO_PORT_RMS_ARM->SetLabel( 0, "GUILLOTINE" );
		pPYRO_PORT_RMS_ARM->SetLabel( 1, "SAFE" );
		pPYRO_PORT_RMS_ARM->SetLabel( 2, "JETT" );

		Add( pPYRO_PORT_RMS_SHLDR = new LockableLever3( _sts, "PYRO PORT RMS SHLDR" ) );
		pPYRO_PORT_RMS_SHLDR->SetLabel( 0, "GUILLOTINE" );
		pPYRO_PORT_RMS_SHLDR->SetLabel( 1, "SAFE" );
		pPYRO_PORT_RMS_SHLDR->SetLabel( 2, "JETT" );

		Add( pPYRO_PORT_RMS_LATCHES_FWD = new LockableLever3( _sts, "PYRO PORT RMS LATCHES FWD" ) );
		pPYRO_PORT_RMS_LATCHES_FWD->SetLabel( 0, "GUILLOTINE" );
		pPYRO_PORT_RMS_LATCHES_FWD->SetLabel( 1, "SAFE" );
		pPYRO_PORT_RMS_LATCHES_FWD->SetLabel( 2, "JETT" );

		Add( pPYRO_PORT_RMS_LATCHES_MID = new LockableLever3( _sts, "PYRO PORT RMS LATCHES MID" ) );
		pPYRO_PORT_RMS_LATCHES_MID->SetLabel( 0, "GUILLOTINE" );
		pPYRO_PORT_RMS_LATCHES_MID->SetLabel( 1, "SAFE" );
		pPYRO_PORT_RMS_LATCHES_MID->SetLabel( 2, "JETT" );

		Add( pPYRO_PORT_RMS_LATCHES_AFT = new LockableLever3( _sts, "PYRO PORT RMS LATCHES AFT" ) );
		pPYRO_PORT_RMS_LATCHES_AFT->SetLabel( 0, "GUILLOTINE" );
		pPYRO_PORT_RMS_LATCHES_AFT->SetLabel( 1, "SAFE" );
		pPYRO_PORT_RMS_LATCHES_AFT->SetLabel( 2, "JETT" );

		Add( pRMS_LATCHES = new LockableLever3( _sts, "RMS LATCHES" ) );
		pRMS_LATCHES->SetLabel( 0, "DEADFACE" );
		pRMS_LATCHES->SetLabel( 1, "SAFE" );
		pRMS_LATCHES->SetLabel( 2, "GND RESET" );

		if (mplm)
		{
			Add( pCARGO_COOLANT_LOOP_HEATERS_ORBITER_A = new StdSwitch3( _sts, "CARGO COOLANT LOOP HEATERS ORBITER A" ) );
			pCARGO_COOLANT_LOOP_HEATERS_ORBITER_A->SetLabel( 0, "ACCUM/LINE AUTO" );
			pCARGO_COOLANT_LOOP_HEATERS_ORBITER_A->SetLabel( 1, "OFF" );
			pCARGO_COOLANT_LOOP_HEATERS_ORBITER_A->SetLabel( 2, "ACCUM AUTO" );

			Add( pCARGO_COOLANT_LOOP_HEATERS_ORBITER_B = new StdSwitch3( _sts, "CARGO COOLANT LOOP HEATERS ORBITER B" ) );
			pCARGO_COOLANT_LOOP_HEATERS_ORBITER_B->SetLabel( 0, "ACCUM/LINE AUTO" );
			pCARGO_COOLANT_LOOP_HEATERS_ORBITER_B->SetLabel( 1, "OFF" );
			pCARGO_COOLANT_LOOP_HEATERS_ORBITER_B->SetLabel( 2, "ACCUM AUTO" );

			Add( pCARGO_COOLANT_LOOP_HEATERS_ORBITER_C = new StdSwitch3( _sts, "CARGO COOLANT LOOP HEATERS ORBITER C" ) );
			pCARGO_COOLANT_LOOP_HEATERS_ORBITER_C->SetLabel( 0, "ACCUM/LINE AUTO" );
			pCARGO_COOLANT_LOOP_HEATERS_ORBITER_C->SetLabel( 1, "OFF" );
			pCARGO_COOLANT_LOOP_HEATERS_ORBITER_C->SetLabel( 2, "ACCUM AUTO" );

			Add( pCARGO_COOLANT_LOOP_HEATERS_CARGO_LINE_A = new StdSwitch2( _sts, "CARGO COOLANT LOOP HEATERS CARGO LINE A" ) );
			pCARGO_COOLANT_LOOP_HEATERS_CARGO_LINE_A->SetLabel( 0, "OFF" );
			pCARGO_COOLANT_LOOP_HEATERS_CARGO_LINE_A->SetLabel( 1, "AUTO" );

			Add( pCARGO_COOLANT_LOOP_HEATERS_CARGO_LINE_B = new StdSwitch2( _sts, "CARGO COOLANT LOOP HEATERS CARGO LINE B" ) );
			pCARGO_COOLANT_LOOP_HEATERS_CARGO_LINE_B->SetLabel( 0, "OFF" );
			pCARGO_COOLANT_LOOP_HEATERS_CARGO_LINE_B->SetLabel( 1, "AUTO" );
		}
		return;
	}

	PanelA14::~PanelA14( void )
	{
		if (hOV103105Texture) oapiReleaseTexture( hOV103105Texture );
		return;
	}

	void PanelA14::DefineVC( void )
	{
		const VECTOR3 switch_rot =  _V( -1.0, 0.0, 0.0 );
		const VECTOR3 pull_dir = _V( 0.0, 0.0, 1.0 );

		AddAIDToMouseEventList( AID_A14 );

		pRCSOMS_HEATERS_FWD_RCS->DefineGroup( GRP_S3_A14_VC );
		pRCSOMS_HEATERS_FWD_RCS->SetInitialAnimState( 0.5 );
		pRCSOMS_HEATERS_FWD_RCS->SetReference( _V( 0.0, 0.221739, -0.025329 ), switch_rot );
		pRCSOMS_HEATERS_FWD_RCS->SetMouseRegion( AID_A14, 0.119480f, 0.267116f, 0.157981f, 0.328137f );

		pRCSOMS_HEATERS_LEFT_POD_A_Cover->DefineGroup( GRP_S1_COVER_A14_VC );
		pRCSOMS_HEATERS_LEFT_POD_A_Cover->SetReference( _V( 0.0, 0.236033, -0.006075 ), switch_rot );
		pRCSOMS_HEATERS_LEFT_POD_A_Cover->SetMouseRegion( AID_A14, 0, 0.166525f, 0.266808f, 0.209978f, 0.343812f );
		pRCSOMS_HEATERS_LEFT_POD_A_Cover->SetMouseRegion( AID_A14, 1, 0.166525f, 0.231625f, 0.209978f, 0.266808f );

		pRCSOMS_HEATERS_LEFT_POD_A->DefineGroup( GRP_S1_A14_VC );
		pRCSOMS_HEATERS_LEFT_POD_A->SetInitialAnimState( 0.5 );
		pRCSOMS_HEATERS_LEFT_POD_A->SetReference( _V( 0.0, 0.221739, -0.025329 ), switch_rot );
		pRCSOMS_HEATERS_LEFT_POD_A->SetMouseRegion( AID_A14, 0.171139f, 0.267116f, 0.209109f, 0.328137f );

		pRCSOMS_HEATERS_LEFT_POD_B_Cover->DefineGroup( GRP_S2_COVER_A14_VC );
		pRCSOMS_HEATERS_LEFT_POD_B_Cover->SetReference( _V( 0.0, 0.236033, -0.006075 ), switch_rot );
		pRCSOMS_HEATERS_LEFT_POD_B_Cover->SetMouseRegion( AID_A14, 0, 0.220072f, 0.266808f, 0.261993f, 0.343812f );
		pRCSOMS_HEATERS_LEFT_POD_B_Cover->SetMouseRegion( AID_A14, 1, 0.220072f, 0.231625f, 0.261993f, 0.266808f );

		pRCSOMS_HEATERS_LEFT_POD_B->DefineGroup( GRP_S2_A14_VC );
		pRCSOMS_HEATERS_LEFT_POD_B->SetInitialAnimState( 0.5 );
		pRCSOMS_HEATERS_LEFT_POD_B->SetReference( _V( 0.0, 0.221739, -0.025329 ), switch_rot );
		pRCSOMS_HEATERS_LEFT_POD_B->SetMouseRegion( AID_A14, 0.221586f, 0.267116f, 0.260185f, 0.328137f );

		pRCSOMS_HEATERS_RIGHT_POD_A_Cover->DefineGroup( GRP_S4_COVER_A14_VC );
		pRCSOMS_HEATERS_RIGHT_POD_A_Cover->SetReference( _V( 0.0, 0.236033, -0.006075 ), switch_rot );
		pRCSOMS_HEATERS_RIGHT_POD_A_Cover->SetMouseRegion( AID_A14, 0, 0.272091f, 0.266808f, 0.315541f, 0.343812f );
		pRCSOMS_HEATERS_RIGHT_POD_A_Cover->SetMouseRegion( AID_A14, 1, 0.272091f, 0.231625f, 0.315541f, 0.266808f );

		pRCSOMS_HEATERS_RIGHT_POD_A->DefineGroup( GRP_S4_A14_VC );
		pRCSOMS_HEATERS_RIGHT_POD_A->SetInitialAnimState( 0.5 );
		pRCSOMS_HEATERS_RIGHT_POD_A->SetReference( _V( 0.0, 0.221739, -0.025329 ), switch_rot );
		pRCSOMS_HEATERS_RIGHT_POD_A->SetMouseRegion( AID_A14, 0.272333f, 0.267116f, 0.310348f, 0.328137f );

		pRCSOMS_HEATERS_RIGHT_POD_B_Cover->DefineGroup( GRP_S5_COVER_A14_VC );
		pRCSOMS_HEATERS_RIGHT_POD_B_Cover->SetReference( _V( 0.0, 0.236033, -0.006075 ), switch_rot );
		pRCSOMS_HEATERS_RIGHT_POD_B_Cover->SetMouseRegion( AID_A14, 0, 0.325636f, 0.266808f, 0.367864f, 0.343812f );
		pRCSOMS_HEATERS_RIGHT_POD_B_Cover->SetMouseRegion( AID_A14, 1, 0.325636f, 0.231625f, 0.367864f, 0.266808f );

		pRCSOMS_HEATERS_RIGHT_POD_B->DefineGroup( GRP_S5_A14_VC );
		pRCSOMS_HEATERS_RIGHT_POD_B->SetInitialAnimState( 0.5 );
		pRCSOMS_HEATERS_RIGHT_POD_B->SetReference( _V( 0.0, 0.221739, -0.025329 ), switch_rot );
		pRCSOMS_HEATERS_RIGHT_POD_B->SetMouseRegion( AID_A14, 0.323690f, 0.267116f, 0.361703f, 0.328137f );

		pRCSOMS_HEATERS_FWD_RCS_JET_1->DefineGroup( GRP_S14_A14_VC );
		pRCSOMS_HEATERS_FWD_RCS_JET_1->SetInitialAnimState( 0.5 );
		pRCSOMS_HEATERS_FWD_RCS_JET_1->SetReference( _V( 0.0, 0.141813, -0.025329 ), switch_rot );
		pRCSOMS_HEATERS_FWD_RCS_JET_1->SetMouseRegion( AID_A14, 0.119480f, 0.508417f, 0.157981f, 0.571909f );

		pRCSOMS_HEATERS_FWD_RCS_JET_2->DefineGroup( GRP_S15_A14_VC );
		pRCSOMS_HEATERS_FWD_RCS_JET_2->SetInitialAnimState( 0.5 );
		pRCSOMS_HEATERS_FWD_RCS_JET_2->SetReference( _V( 0.0, 0.141813, -0.025329 ), switch_rot );
		pRCSOMS_HEATERS_FWD_RCS_JET_2->SetMouseRegion( AID_A14, 0.171139f, 0.508417f, 0.209109f, 0.571909f );

		pRCSOMS_HEATERS_FWD_RCS_JET_3->DefineGroup( GRP_S16_A14_VC );
		pRCSOMS_HEATERS_FWD_RCS_JET_3->SetInitialAnimState( 0.5 );
		pRCSOMS_HEATERS_FWD_RCS_JET_3->SetReference( _V( 0.0, 0.141813, -0.025329 ), switch_rot );
		pRCSOMS_HEATERS_FWD_RCS_JET_3->SetMouseRegion( AID_A14, 0.221586f, 0.508417f, 0.260185f, 0.571909f );

		pRCSOMS_HEATERS_FWD_RCS_JET_4->DefineGroup( GRP_S17_A14_VC );
		pRCSOMS_HEATERS_FWD_RCS_JET_4->SetInitialAnimState( 0.5 );
		pRCSOMS_HEATERS_FWD_RCS_JET_4->SetReference( _V( 0.0, 0.141813, -0.025329 ), switch_rot );
		pRCSOMS_HEATERS_FWD_RCS_JET_4->SetMouseRegion( AID_A14, 0.272333f, 0.508417f, 0.310348f, 0.571909f );

		pRCSOMS_HEATERS_FWD_RCS_JET_5->DefineGroup( GRP_S18_A14_VC );
		pRCSOMS_HEATERS_FWD_RCS_JET_5->SetInitialAnimState( 0.5 );
		pRCSOMS_HEATERS_FWD_RCS_JET_5->SetReference( _V( 0.0, 0.141813, -0.025329 ), switch_rot );
		pRCSOMS_HEATERS_FWD_RCS_JET_5->SetMouseRegion( AID_A14, 0.323690f, 0.508417f, 0.361703f, 0.571909f );

		pRCSOMS_HEATERS_AFT_RCS_JET_1->DefineGroup( GRP_S9_A14_VC );
		pRCSOMS_HEATERS_AFT_RCS_JET_1->SetInitialAnimState( 0.5 );
		pRCSOMS_HEATERS_AFT_RCS_JET_1->SetReference( _V( 0.0, 0.06164, -0.025329 ), switch_rot );
		pRCSOMS_HEATERS_AFT_RCS_JET_1->SetMouseRegion( AID_A14, 0.119480f, 0.753308f, 0.157981f, 0.814132f );

		pRCSOMS_HEATERS_AFT_RCS_JET_2->DefineGroup( GRP_S10_A14_VC );
		pRCSOMS_HEATERS_AFT_RCS_JET_2->SetInitialAnimState( 0.5 );
		pRCSOMS_HEATERS_AFT_RCS_JET_2->SetReference( _V( 0.0, 0.06164, -0.025329 ), switch_rot );
		pRCSOMS_HEATERS_AFT_RCS_JET_2->SetMouseRegion( AID_A14, 0.171139f, 0.753308f, 0.209109f, 0.814132f );

		pRCSOMS_HEATERS_AFT_RCS_JET_3->DefineGroup( GRP_S11_A14_VC );
		pRCSOMS_HEATERS_AFT_RCS_JET_3->SetInitialAnimState( 0.5 );
		pRCSOMS_HEATERS_AFT_RCS_JET_3->SetReference( _V( 0.0, 0.06164, -0.025329 ), switch_rot );
		pRCSOMS_HEATERS_AFT_RCS_JET_3->SetMouseRegion( AID_A14, 0.221586f, 0.753308f, 0.260185f, 0.814132f );

		pRCSOMS_HEATERS_AFT_RCS_JET_4->DefineGroup( GRP_S12_A14_VC );
		pRCSOMS_HEATERS_AFT_RCS_JET_4->SetInitialAnimState( 0.5 );
		pRCSOMS_HEATERS_AFT_RCS_JET_4->SetReference( _V( 0.0, 0.06164, -0.025329 ), switch_rot );
		pRCSOMS_HEATERS_AFT_RCS_JET_4->SetMouseRegion( AID_A14, 0.272333f, 0.753308f, 0.310348f, 0.814132f );

		pRCSOMS_HEATERS_AFT_RCS_JET_5->DefineGroup( GRP_S13_A14_VC );
		pRCSOMS_HEATERS_AFT_RCS_JET_5->SetInitialAnimState( 0.5 );
		pRCSOMS_HEATERS_AFT_RCS_JET_5->SetReference( _V( 0.0, 0.06164, -0.025329 ), switch_rot );
		pRCSOMS_HEATERS_AFT_RCS_JET_5->SetMouseRegion( AID_A14, 0.323690f, 0.753308f, 0.361703f, 0.814132f );

		pRCSOMS_HEATERS_OMS_KIT->DefineGroup( GRP_S6_A14_VC );
		pRCSOMS_HEATERS_OMS_KIT->SetInitialAnimState( 0.5 );
		pRCSOMS_HEATERS_OMS_KIT->SetReference( _V( 0.0, 0.221739, -0.025329 ), switch_rot );
		pRCSOMS_HEATERS_OMS_KIT->SetMouseRegion( AID_A14, 0.422056f, 0.267116f, 0.462572f, 0.328137f );

		pRCSOMS_HEATERS_OMS_CRSFD_LINES_A->DefineGroup( GRP_S7_A14_VC );
		pRCSOMS_HEATERS_OMS_CRSFD_LINES_A->SetInitialAnimState( 0.5 );
		pRCSOMS_HEATERS_OMS_CRSFD_LINES_A->SetReference( _V( 0.0, 0.221739, -0.025329 ), switch_rot );
		pRCSOMS_HEATERS_OMS_CRSFD_LINES_A->SetMouseRegion( AID_A14, 0.481304f, 0.267116f, 0.521772f, 0.328137f );

		pRCSOMS_HEATERS_OMS_CRSFD_LINES_B->DefineGroup( GRP_S8_A14_VC );
		pRCSOMS_HEATERS_OMS_CRSFD_LINES_B->SetInitialAnimState( 0.5 );
		pRCSOMS_HEATERS_OMS_CRSFD_LINES_B->SetReference( _V( 0.0, 0.221739, -0.025329 ), switch_rot );
		pRCSOMS_HEATERS_OMS_CRSFD_LINES_B->SetMouseRegion( AID_A14, 0.540440f, 0.267116f, 0.581673f, 0.328137f );

		pPYRO_Cover->DefineGroup( GRP_PYRO_COVER_A14_VC );
		pPYRO_Cover->SetReference( _V( 0.0, 0.040137, 0.003515 ), -switch_rot );
		pPYRO_Cover->SetMouseRegion( AID_A14, 0, 0.398683f, 0.389073f, 0.899245f, 0.859229f );
		pPYRO_Cover->SetMouseRegion( AID_A14, 1, 0.411231f, 0.872859f, 0.888890f, 0.980511f );

		pPYRO_KU_ANT_ARM->DefineGroup( GRP_S19_A14_VC );
		pPYRO_KU_ANT_ARM->SetInitialAnimState( 0.5 );
		pPYRO_KU_ANT_ARM->SetReference( _V( 0.0, 0.142823, -0.029279 ), switch_rot );
		pPYRO_KU_ANT_ARM->SetMouseRegion( AID_A14, 0.419366f, 0.507993f, 0.467825f, 0.566820f );
		pPYRO_KU_ANT_ARM->SetPullDirection( pull_dir );

		pPYRO_KU_ANT_JETT->DefineGroup( GRP_S20_A14_VC );
		pPYRO_KU_ANT_JETT->SetInitialAnimState( 0.5 );
		pPYRO_KU_ANT_JETT->SetReference( _V( 0.0, 0.142823, -0.029279 ), switch_rot );
		pPYRO_KU_ANT_JETT->SetMouseRegion( AID_A14, 0.477935f, 0.507993f, 0.515741f, 0.566820f );
		pPYRO_KU_ANT_JETT->SetPullDirection( pull_dir );

		pPYRO_STARBOARD_RMS_ARM->DefineGroup( GRP_S21_A14_VC );
		pPYRO_STARBOARD_RMS_ARM->SetInitialAnimState( 0.5 );
		pPYRO_STARBOARD_RMS_ARM->SetReference( _V( 0.0, 0.142823, -0.029279 ), switch_rot );
		pPYRO_STARBOARD_RMS_ARM->SetMouseRegion( AID_A14, 0.525500f, 0.507993f, 0.575108f, 0.566820f );
		pPYRO_STARBOARD_RMS_ARM->SetPullDirection( pull_dir );

		pPYRO_STARBOARD_RMS_SHLDR->DefineGroup( GRP_S22_A14_VC );
		pPYRO_STARBOARD_RMS_SHLDR->SetInitialAnimState( 0.5 );
		pPYRO_STARBOARD_RMS_SHLDR->SetReference( _V( 0.0, 0.142823, -0.029279 ), switch_rot );
		pPYRO_STARBOARD_RMS_SHLDR->SetMouseRegion( AID_A14, 0.585827f, 0.507993f, 0.623263f, 0.566820f );
		pPYRO_STARBOARD_RMS_SHLDR->SetPullDirection( pull_dir );

		pPYRO_STARBOARD_RMS_LATCHES_FWD->DefineGroup( GRP_S23_A14_VC );
		pPYRO_STARBOARD_RMS_LATCHES_FWD->SetInitialAnimState( 0.5 );
		pPYRO_STARBOARD_RMS_LATCHES_FWD->SetReference( _V( 0.0, 0.142823, -0.029279 ), switch_rot );
		pPYRO_STARBOARD_RMS_LATCHES_FWD->SetMouseRegion( AID_A14, 0.634345f, 0.507993f, 0.681736f, 0.566820f );
		pPYRO_STARBOARD_RMS_LATCHES_FWD->SetPullDirection( pull_dir );

		pPYRO_STARBOARD_RMS_LATCHES_MID->DefineGroup( GRP_S24_A14_VC );
		pPYRO_STARBOARD_RMS_LATCHES_MID->SetInitialAnimState( 0.5 );
		pPYRO_STARBOARD_RMS_LATCHES_MID->SetReference( _V( 0.0, 0.142823, -0.029279 ), switch_rot );
		pPYRO_STARBOARD_RMS_LATCHES_MID->SetMouseRegion( AID_A14, 0.694055f, 0.507993f, 0.730789f, 0.566820f );
		pPYRO_STARBOARD_RMS_LATCHES_MID->SetPullDirection( pull_dir );

		pPYRO_STARBOARD_RMS_LATCHES_AFT->DefineGroup( GRP_S25_A14_VC );
		pPYRO_STARBOARD_RMS_LATCHES_AFT->SetInitialAnimState( 0.5 );
		pPYRO_STARBOARD_RMS_LATCHES_AFT->SetReference( _V( 0.0, 0.142823, -0.029279 ), switch_rot );
		pPYRO_STARBOARD_RMS_LATCHES_AFT->SetMouseRegion( AID_A14, 0.748712f, 0.507993f, 0.786388f, 0.566820f );
		pPYRO_STARBOARD_RMS_LATCHES_AFT->SetPullDirection( pull_dir );

		pPYRO_PORT_RMS_ARM->DefineGroup( GRP_S28_A14_VC );
		pPYRO_PORT_RMS_ARM->SetInitialAnimState( 0.5 );
		pPYRO_PORT_RMS_ARM->SetReference( _V( 0.0, 0.083885, -0.029279 ), switch_rot );
		pPYRO_PORT_RMS_ARM->SetMouseRegion( AID_A14, 0.531705f, 0.685574f, 0.568910f, 0.744544f );
		pPYRO_PORT_RMS_ARM->SetPullDirection( pull_dir );

		pPYRO_PORT_RMS_SHLDR->DefineGroup( GRP_S29_A14_VC );
		pPYRO_PORT_RMS_SHLDR->SetInitialAnimState( 0.5 );
		pPYRO_PORT_RMS_SHLDR->SetReference( _V( 0.0, 0.083885, -0.029279 ), switch_rot );
		pPYRO_PORT_RMS_SHLDR->SetMouseRegion( AID_A14, 0.580354f, 0.685574f, 0.627780f, 0.744544f );
		pPYRO_PORT_RMS_SHLDR->SetPullDirection( pull_dir );

		pPYRO_PORT_RMS_LATCHES_FWD->DefineGroup( GRP_S30_A14_VC );
		pPYRO_PORT_RMS_LATCHES_FWD->SetInitialAnimState( 0.5 );
		pPYRO_PORT_RMS_LATCHES_FWD->SetReference( _V( 0.0, 0.083885, -0.029279 ), switch_rot );
		pPYRO_PORT_RMS_LATCHES_FWD->SetMouseRegion( AID_A14, 0.639204f, 0.685574f, 0.677593f, 0.744544f );
		pPYRO_PORT_RMS_LATCHES_FWD->SetPullDirection( pull_dir );

		pPYRO_PORT_RMS_LATCHES_MID->DefineGroup( GRP_S31_A14_VC );
		pPYRO_PORT_RMS_LATCHES_MID->SetInitialAnimState( 0.5 );
		pPYRO_PORT_RMS_LATCHES_MID->SetReference( _V( 0.0, 0.083885, -0.029279 ), switch_rot );
		pPYRO_PORT_RMS_LATCHES_MID->SetMouseRegion( AID_A14, 0.688231f, 0.685574f, 0.735833f, 0.744544f );
		pPYRO_PORT_RMS_LATCHES_MID->SetPullDirection( pull_dir );

		pPYRO_PORT_RMS_LATCHES_AFT->DefineGroup( GRP_S32_A14_VC );
		pPYRO_PORT_RMS_LATCHES_AFT->SetInitialAnimState( 0.5 );
		pPYRO_PORT_RMS_LATCHES_AFT->SetReference( _V( 0.0, 0.083885, -0.029279 ), switch_rot );
		pPYRO_PORT_RMS_LATCHES_AFT->SetMouseRegion( AID_A14, 0.747792f, 0.685574f, 0.785365f, 0.744544f );
		pPYRO_PORT_RMS_LATCHES_AFT->SetPullDirection( pull_dir );

		pRMS_LATCHES->DefineGroup( GRP_S33_A14_VC );
		pRMS_LATCHES->SetInitialAnimState( 0.5 );
		pRMS_LATCHES->SetReference( _V( 0.0, 0.083885, -0.029279 ), switch_rot );
		pRMS_LATCHES->SetMouseRegion( AID_A14, 0.821590f, 0.685574f, 0.857101f, 0.744544f );
		pRMS_LATCHES->SetPullDirection( pull_dir );
		pRMS_LATCHES->SetSpringLoaded( true, 2 );

		if (mplm)
		{
			pCARGO_COOLANT_LOOP_HEATERS_ORBITER_A->DefineGroup( GRP_S_A_A14_VC );
			pCARGO_COOLANT_LOOP_HEATERS_ORBITER_A->SetInitialAnimState( 0.5 );
			pCARGO_COOLANT_LOOP_HEATERS_ORBITER_A->SetReference( _V( 0.0, 0.221739, -0.025329 ), switch_rot );
			pCARGO_COOLANT_LOOP_HEATERS_ORBITER_A->SetMouseRegion( AID_A14, 0.603549f, 0.267116f, 0.642544f, 0.328137f );

			pCARGO_COOLANT_LOOP_HEATERS_ORBITER_B->DefineGroup( GRP_S_B_A14_VC );
			pCARGO_COOLANT_LOOP_HEATERS_ORBITER_B->SetInitialAnimState( 0.5 );
			pCARGO_COOLANT_LOOP_HEATERS_ORBITER_B->SetReference( _V( 0.0, 0.221739, -0.025329 ), switch_rot );
			pCARGO_COOLANT_LOOP_HEATERS_ORBITER_B->SetMouseRegion( AID_A14, 0.657352f, 0.267116f, 0.690906f, 0.328137f );

			pCARGO_COOLANT_LOOP_HEATERS_ORBITER_C->DefineGroup( GRP_S_C_A14_VC );
			pCARGO_COOLANT_LOOP_HEATERS_ORBITER_C->SetInitialAnimState( 0.5 );
			pCARGO_COOLANT_LOOP_HEATERS_ORBITER_C->SetReference( _V( 0.0, 0.221739, -0.025329 ), switch_rot );
			pCARGO_COOLANT_LOOP_HEATERS_ORBITER_C->SetMouseRegion( AID_A14, 0.705717f, 0.267116f, 0.744409f, 0.328137f );

			pCARGO_COOLANT_LOOP_HEATERS_CARGO_LINE_A->DefineGroup( GRP_S_D_A14_VC );
			pCARGO_COOLANT_LOOP_HEATERS_CARGO_LINE_A->SetInitialAnimState( 0.5 );
			pCARGO_COOLANT_LOOP_HEATERS_CARGO_LINE_A->SetReference( _V( 0.0, 0.221739, -0.025329 ), switch_rot );
			pCARGO_COOLANT_LOOP_HEATERS_CARGO_LINE_A->SetMouseRegion( AID_A14, 0.759221f, 0.267116f, 0.792169f, 0.328137f );

			pCARGO_COOLANT_LOOP_HEATERS_CARGO_LINE_B->DefineGroup( GRP_S_E_A14_VC );
			pCARGO_COOLANT_LOOP_HEATERS_CARGO_LINE_B->SetInitialAnimState( 0.5 );
			pCARGO_COOLANT_LOOP_HEATERS_CARGO_LINE_B->SetReference( _V( 0.0, 0.221739, -0.025329 ), switch_rot );
			pCARGO_COOLANT_LOOP_HEATERS_CARGO_LINE_B->SetMouseRegion( AID_A14, 0.805468f, 0.267116f, 0.838415f, 0.328137f );
		}
		return;
	}

	void PanelA14::RegisterVC( void )
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET + OFFSET_PANEL;

		oapiVCRegisterArea( AID_A14, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_A14,
			_V( 0.5334, 0.3175, 0.0 ) + ofs, _V( 0.0, 0.3175, 0.0 ) + ofs,
			_V( 0.5334, 0.0, 0.0 ) + ofs, _V( 0.0, 0.0, 0.0 ) + ofs );
		return;
	}

	void PanelA14::Realize( void )
	{
		AtlantisPanel::Realize();

		// TODO
		return;
	}

	void PanelA14::VisualCreated( void )
	{
		// hide unneeded panel
		DEVMESHHANDLE hDevMesh = STS()->GetDevMesh( STS()->Get_vis(), GetVCMeshIndex() );
		if (hDevMesh != NULL)
		{
			GROUPEDITSPEC grpSpec;
			grpSpec.flags = GRPEDIT_SETUSERFLAG;
			grpSpec.UsrFlag = 0x00000003;// hide group and shadow
			if (mplm)
			{
				oapiEditMeshGroup( hDevMesh, GRP_PANEL_A14_VC, &grpSpec );
				// change pyro cover texture
				if (hOV103105Texture == NULL) hOV103105Texture = oapiLoadTexture( "SSV\\OV\\panelA14_103_105.dds" );
				if (hOV103105Texture == NULL) throw std::exception( "Could not load texture in panel A14" );
				else oapiSetTexture( hDevMesh, TEX_SSV_OV_PANELA14_A14_VC, hOV103105Texture );

			}
			else
			{
				oapiEditMeshGroup( hDevMesh, GRP_PANEL_103_105_A14_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_GUARDS_103_105_A14_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S_A_A14_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S_B_A14_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S_C_A14_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S_D_A14_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S_E_A14_VC, &grpSpec );
			}
		}

		AtlantisPanel::VisualCreated();
		return;
	}
}

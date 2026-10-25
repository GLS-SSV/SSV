#include "PanelA12.h"
#include "StandardSwitch.h"
#include "Talkback.h"
#include "StandardSwitchCover.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_a12.h"


namespace vc
{
	const static char* MESHNAME_PANEL = "SSV\\OV\\PanelA12";
	constexpr VECTOR3 OFFSET_PANEL = {0.2667, 1.79193, 12.4756};


	PanelA12::PanelA12( Atlantis* _sts, const std::string &orbiter ) : AtlantisPanel( _sts, "A12" ),
		hOV099Texture(NULL), OV102(false), OV099(false)
	{
		DefineMesh( MESHNAME_PANEL, OFFSET_PANEL );

		if (orbiter == "Columbia") OV102 = true;
		else if (orbiter == "Challenger") OV099 = true;

		Add( pAPU_HEATER_GAS_GEN_FUEL_PUMP_1 = new StdSwitch3( _sts, "APU HEATER GAS GEN/FUEL PUMP 1" ) );
		pAPU_HEATER_GAS_GEN_FUEL_PUMP_1->SetLabel( 0, "B AUTO" );
		pAPU_HEATER_GAS_GEN_FUEL_PUMP_1->SetLabel( 1, "OFF" );
		pAPU_HEATER_GAS_GEN_FUEL_PUMP_1->SetLabel( 2, "A AUTO" );

		Add( pAPU_HEATER_GAS_GEN_FUEL_PUMP_2 = new StdSwitch3( _sts, "APU HEATER GAS GEN/FUEL PUMP 2" ) );
		pAPU_HEATER_GAS_GEN_FUEL_PUMP_2->SetLabel( 0, "B AUTO" );
		pAPU_HEATER_GAS_GEN_FUEL_PUMP_2->SetLabel( 1, "OFF" );
		pAPU_HEATER_GAS_GEN_FUEL_PUMP_2->SetLabel( 2, "A AUTO" );

		Add( pAPU_HEATER_GAS_GEN_FUEL_PUMP_3 = new StdSwitch3( _sts, "APU HEATER GAS GEN/FUEL PUMP 3" ) );
		pAPU_HEATER_GAS_GEN_FUEL_PUMP_3->SetLabel( 0, "B AUTO" );
		pAPU_HEATER_GAS_GEN_FUEL_PUMP_3->SetLabel( 1, "OFF" );
		pAPU_HEATER_GAS_GEN_FUEL_PUMP_3->SetLabel( 2, "A AUTO" );

		Add( pAPU_HEATER_LUBE_OIL_LINE_1 = new StdSwitch3( _sts, "APU HEATER LUBE OIL LINE 1" ) );
		pAPU_HEATER_LUBE_OIL_LINE_1->SetLabel( 0, "B AUTO" );
		pAPU_HEATER_LUBE_OIL_LINE_1->SetLabel( 1, "OFF" );
		pAPU_HEATER_LUBE_OIL_LINE_1->SetLabel( 2, "A AUTO" );

		Add( pAPU_HEATER_LUBE_OIL_LINE_2 = new StdSwitch3( _sts, "APU HEATER LUBE OIL LINE 2" ) );
		pAPU_HEATER_LUBE_OIL_LINE_2->SetLabel( 0, "B AUTO" );
		pAPU_HEATER_LUBE_OIL_LINE_2->SetLabel( 1, "OFF" );
		pAPU_HEATER_LUBE_OIL_LINE_2->SetLabel( 2, "A AUTO" );

		Add( pAPU_HEATER_LUBE_OIL_LINE_3 = new StdSwitch3( _sts, "APU HEATER LUBE OIL LINE 3" ) );
		pAPU_HEATER_LUBE_OIL_LINE_3->SetLabel( 0, "B AUTO" );
		pAPU_HEATER_LUBE_OIL_LINE_3->SetLabel( 1, "OFF" );
		pAPU_HEATER_LUBE_OIL_LINE_3->SetLabel( 2, "A AUTO" );

		Add( pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_1A = new StdSwitch2( _sts, "APU HEATER TANK/FUEL LINE/H2O SYS 1A" ) );
		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_1A->SetLabel( 0, "OFF" );
		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_1A->SetLabel( 1, "AUTO" );

		Add( pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_1B = new StdSwitch2( _sts, "APU HEATER TANK/FUEL LINE/H2O SYS 1B" ) );
		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_1B->SetLabel( 0, "OFF" );
		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_1B->SetLabel( 1, "AUTO" );

		Add( pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_2A = new StdSwitch2( _sts, "APU HEATER TANK/FUEL LINE/H2O SYS 2A" ) );
		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_2A->SetLabel( 0, "OFF" );
		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_2A->SetLabel( 1, "AUTO" );

		Add( pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_2B = new StdSwitch2( _sts, "APU HEATER TANK/FUEL LINE/H2O SYS 2B" ) );
		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_2B->SetLabel( 0, "OFF" );
		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_2B->SetLabel( 1, "AUTO" );

		Add( pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_3A = new StdSwitch2( _sts, "APU HEATER TANK/FUEL LINE/H2O SYS 3A" ) );
		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_3A->SetLabel( 0, "OFF" );
		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_3A->SetLabel( 1, "AUTO" );

		Add( pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_3B = new StdSwitch2( _sts, "APU HEATER TANK/FUEL LINE/H2O SYS 3B" ) );
		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_3B->SetLabel( 0, "OFF" );
		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_3B->SetLabel( 1, "AUTO" );

		Add( pHYDRAULIC_HEATER_RUDDER_SPD_BK_A = new StdSwitch2( _sts, "HYDRAULIC HEATER RUDDER SPD BK A" ) );
		pHYDRAULIC_HEATER_RUDDER_SPD_BK_A->SetLabel( 0, "OFF" );
		pHYDRAULIC_HEATER_RUDDER_SPD_BK_A->SetLabel( 1, "AUTO" );

		Add( pHYDRAULIC_HEATER_RUDDER_SPD_BK_B = new StdSwitch2( _sts, "HYDRAULIC HEATER RUDDER SPD BK B" ) );
		pHYDRAULIC_HEATER_RUDDER_SPD_BK_B->SetLabel( 0, "OFF" );
		pHYDRAULIC_HEATER_RUDDER_SPD_BK_B->SetLabel( 1, "AUTO" );

		Add( pHYDRAULIC_HEATER_BODY_FLAP_A = new StdSwitch2( _sts, "HYDRAULIC HEATER BODY FLAP A" ) );
		pHYDRAULIC_HEATER_BODY_FLAP_A->SetLabel( 0, "OFF" );
		pHYDRAULIC_HEATER_BODY_FLAP_A->SetLabel( 1, "AUTO" );

		Add( pHYDRAULIC_HEATER_BODY_FLAP_B = new StdSwitch2( _sts, "HYDRAULIC HEATER BODY FLAP B" ) );
		pHYDRAULIC_HEATER_BODY_FLAP_B->SetLabel( 0, "OFF" );
		pHYDRAULIC_HEATER_BODY_FLAP_B->SetLabel( 1, "AUTO" );

		Add( pHYDRAULIC_HEATER_ELEVON_A = new StdSwitch2( _sts, "HYDRAULIC HEATER ELEVON A" ) );
		pHYDRAULIC_HEATER_ELEVON_A->SetLabel( 0, "OFF" );
		pHYDRAULIC_HEATER_ELEVON_A->SetLabel( 1, "AUTO" );

		Add( pHYDRAULIC_HEATER_ELEVON_B = new StdSwitch2( _sts, "HYDRAULIC HEATER ELEVON B" ) );
		pHYDRAULIC_HEATER_ELEVON_B->SetLabel( 0, "OFF" );
		pHYDRAULIC_HEATER_ELEVON_B->SetLabel( 1, "AUTO" );

		Add( pHYDRAULIC_HEATER_AFT_FUSELAGE_A = new StdSwitch2( _sts, "HYDRAULIC HEATER AFT FUSELAGE A" ) );
		pHYDRAULIC_HEATER_AFT_FUSELAGE_A->SetLabel( 0, "OFF" );
		pHYDRAULIC_HEATER_AFT_FUSELAGE_A->SetLabel( 1, "AUTO" );

		Add( pHYDRAULIC_HEATER_AFT_FUSELAGE_B = new StdSwitch2( _sts, "HYDRAULIC HEATER AFT FUSELAGE B" ) );
		pHYDRAULIC_HEATER_AFT_FUSELAGE_B->SetLabel( 0, "OFF" );
		pHYDRAULIC_HEATER_AFT_FUSELAGE_B->SetLabel( 1, "AUTO" );

		Add( pHYD_CIRC_PUMP_POWER_1 = new StdSwitch2( _sts, "HYD CIRC PUMP POWER 1" ) );
		pHYD_CIRC_PUMP_POWER_1->SetLabel( 0, "MN B" );
		pHYD_CIRC_PUMP_POWER_1->SetLabel( 1, "MN A" );

		Add( pHYD_CIRC_PUMP_POWER_2 = new StdSwitch2( _sts, "HYD CIRC PUMP POWER 2" ) );
		pHYD_CIRC_PUMP_POWER_2->SetLabel( 0, "MN C" );
		pHYD_CIRC_PUMP_POWER_2->SetLabel( 1, "MN B" );

		Add( pHYD_CIRC_PUMP_POWER_3 = new StdSwitch2( _sts, "HYD CIRC PUMP POWER 3" ) );
		pHYD_CIRC_PUMP_POWER_3->SetLabel( 0, "MN A" );
		pHYD_CIRC_PUMP_POWER_3->SetLabel( 1, "MN C" );

		Add( pLG_ARM_DN_RESET = new LockableLever2( _sts, "LG ARM/DN RESET" ) );

		Add( pFC_3_STRUCT_RTN_TB = new StandardTalkback2( _sts, "FC 3 STRUCT RTN TB" ) );

		Add( pFC_3_STRUCT_RTN_Cover = new StandardSwitchCover( _sts, "FC 3 STRUCT RTN COVER" ) );

		Add( pFC_3_STRUCT_RTN = new StdSwitch3( _sts, "FC 3 STRUCT RTN" ) );

		if ((OV102) || (OV099))
		{
			Add( pGPS_POWER = new StdSwitch2( _sts, "GPS POWER" ) );
			pGPS_POWER->SetLabel( 0, "OFF" );
			pGPS_POWER->SetLabel( 1, "ON" );

			Add( pENCRYPT = new StdSwitch2( _sts, "ENCRYPT" ) );

			if (OV102)
			{
				Add( pGPS_PRE_AMP_UPPER = new StdSwitch2( _sts, "GPS PRE AMP UPPER" ) );
				pGPS_PRE_AMP_UPPER->SetLabel( 0, "OFF" );
				pGPS_PRE_AMP_UPPER->SetLabel( 1, "ON" );

				Add( pGPS_PRE_AMP_LOWER = new StdSwitch2( _sts, "GPS PRE AMP LOWER" ) );
				pGPS_PRE_AMP_LOWER->SetLabel( 0, "OFF" );
				pGPS_PRE_AMP_LOWER->SetLabel( 1, "ON" );
			}
		}
		return;
	}

	PanelA12::~PanelA12( void )
	{
		if (hOV099Texture) oapiReleaseTexture( hOV099Texture );
		return;
	}

	void PanelA12::DefineVC( void )
	{
		const VECTOR3 switch_rot =  _V( -1.0, 0.0, 0.0 );
		const VECTOR3 pull_dir = _V( 0.0, 0.0, 1.0 );

		AddAIDToMouseEventList( AID_A12 );

		pAPU_HEATER_GAS_GEN_FUEL_PUMP_1->DefineGroup( GRP_S1_A12_VC );
		pAPU_HEATER_GAS_GEN_FUEL_PUMP_1->SetInitialAnimState( 0.5 );
		pAPU_HEATER_GAS_GEN_FUEL_PUMP_1->SetReference( _V( 0.0, 0.219279, -0.025329 ), switch_rot );
		pAPU_HEATER_GAS_GEN_FUEL_PUMP_1->SetMouseRegion( AID_A12, 0.083925f, 0.269052f, 0.127878f, 0.348653f );

		pAPU_HEATER_GAS_GEN_FUEL_PUMP_2->DefineGroup( GRP_S2_A12_VC );
		pAPU_HEATER_GAS_GEN_FUEL_PUMP_2->SetInitialAnimState( 0.5 );
		pAPU_HEATER_GAS_GEN_FUEL_PUMP_2->SetReference( _V( 0.0, 0.219279, -0.025329 ), switch_rot );
		pAPU_HEATER_GAS_GEN_FUEL_PUMP_2->SetMouseRegion( AID_A12, 0.176045f, 0.269052f, 0.223415f, 0.348653f );

		pAPU_HEATER_GAS_GEN_FUEL_PUMP_3->DefineGroup( GRP_S3_A12_VC );
		pAPU_HEATER_GAS_GEN_FUEL_PUMP_3->SetInitialAnimState( 0.5 );
		pAPU_HEATER_GAS_GEN_FUEL_PUMP_3->SetReference( _V( 0.0, 0.219279, -0.025329 ), switch_rot );
		pAPU_HEATER_GAS_GEN_FUEL_PUMP_3->SetMouseRegion( AID_A12, 0.265732f, 0.269052f, 0.315370f, 0.348653f );

		pAPU_HEATER_LUBE_OIL_LINE_1->DefineGroup( GRP_S4_A12_VC );
		pAPU_HEATER_LUBE_OIL_LINE_1->SetInitialAnimState( 0.5 );
		pAPU_HEATER_LUBE_OIL_LINE_1->SetReference( _V( 0.0, 0.219279, -0.025329 ), switch_rot );
		pAPU_HEATER_LUBE_OIL_LINE_1->SetMouseRegion( AID_A12, 0.345949f, 0.269052f, 0.394612f, 0.348653f );

		pAPU_HEATER_LUBE_OIL_LINE_2->DefineGroup( GRP_S5_A12_VC );
		pAPU_HEATER_LUBE_OIL_LINE_2->SetInitialAnimState( 0.5 );
		pAPU_HEATER_LUBE_OIL_LINE_2->SetReference( _V( 0.0, 0.219279, -0.025329 ), switch_rot );
		pAPU_HEATER_LUBE_OIL_LINE_2->SetMouseRegion( AID_A12, 0.419632f, 0.269052f, 0.469324f, 0.348653f );

		pAPU_HEATER_LUBE_OIL_LINE_3->DefineGroup( GRP_S6_A12_VC );
		pAPU_HEATER_LUBE_OIL_LINE_3->SetInitialAnimState( 0.5 );
		pAPU_HEATER_LUBE_OIL_LINE_3->SetReference( _V( 0.0, 0.219279, -0.025329 ), switch_rot );
		pAPU_HEATER_LUBE_OIL_LINE_3->SetMouseRegion( AID_A12, 0.489348f, 0.269052f, 0.537535f, 0.348653f );

		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_1A->DefineGroup( GRP_S7_A12_VC );
		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_1A->SetInitialAnimState( 0.5 );
		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_1A->SetReference( _V( 0.0, 0.146979, -0.025329 ), switch_rot );
		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_1A->SetMouseRegion( AID_A12, 0.083925f, 0.497437f, 0.127878f, 0.574684f );

		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_1B->DefineGroup( GRP_S8_A12_VC );
		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_1B->SetInitialAnimState( 0.5 );
		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_1B->SetReference( _V( 0.0, 0.146979, -0.025329 ), switch_rot );
		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_1B->SetMouseRegion( AID_A12, 0.176045f, 0.497437f, 0.223415f, 0.574684f );

		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_2A->DefineGroup( GRP_S9_A12_VC );
		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_2A->SetInitialAnimState( 0.5 );
		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_2A->SetReference( _V( 0.0, 0.146979, -0.025329 ), switch_rot );
		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_2A->SetMouseRegion( AID_A12, 0.265732f, 0.497437f, 0.315370f, 0.574684f );

		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_2B->DefineGroup( GRP_S10_A12_VC );
		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_2B->SetInitialAnimState( 0.5 );
		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_2B->SetReference( _V( 0.0, 0.146979, -0.025329 ), switch_rot );
		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_2B->SetMouseRegion( AID_A12, 0.345949f, 0.497437f, 0.394612f, 0.574684f );

		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_3A->DefineGroup( GRP_S11_A12_VC );
		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_3A->SetInitialAnimState( 0.5 );
		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_3A->SetReference( _V( 0.0, 0.146979, -0.025329 ), switch_rot );
		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_3A->SetMouseRegion( AID_A12, 0.419632f, 0.497437f, 0.469324f, 0.574684f );

		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_3B->DefineGroup( GRP_S12_A12_VC );
		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_3B->SetInitialAnimState( 0.5 );
		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_3B->SetReference( _V( 0.0, 0.146979, -0.025329 ), switch_rot );
		pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_3B->SetMouseRegion( AID_A12, 0.489348f, 0.497437f, 0.537535f, 0.574684f );

		pHYDRAULIC_HEATER_RUDDER_SPD_BK_A->DefineGroup( GRP_S17_A12_VC );
		pHYDRAULIC_HEATER_RUDDER_SPD_BK_A->SetInitialAnimState( 0.5 );
		pHYDRAULIC_HEATER_RUDDER_SPD_BK_A->SetReference( _V( 0.0, 0.068879, -0.025329 ), switch_rot );
		pHYDRAULIC_HEATER_RUDDER_SPD_BK_A->SetMouseRegion( AID_A12, 0.083925f, 0.743055f, 0.127878f, 0.824873f );

		pHYDRAULIC_HEATER_RUDDER_SPD_BK_B->DefineGroup( GRP_S28_A12_VC );
		pHYDRAULIC_HEATER_RUDDER_SPD_BK_B->SetInitialAnimState( 0.5 );
		pHYDRAULIC_HEATER_RUDDER_SPD_BK_B->SetReference( _V( 0.0, 0.068879, -0.025329 ), switch_rot );
		pHYDRAULIC_HEATER_RUDDER_SPD_BK_B->SetMouseRegion( AID_A12, 0.176045f, 0.743055f, 0.223415f, 0.824873f );

		pHYDRAULIC_HEATER_BODY_FLAP_A->DefineGroup( GRP_S18_A12_VC );
		pHYDRAULIC_HEATER_BODY_FLAP_A->SetInitialAnimState( 0.5 );
		pHYDRAULIC_HEATER_BODY_FLAP_A->SetReference( _V( 0.0, 0.068879, -0.025329 ), switch_rot );
		pHYDRAULIC_HEATER_BODY_FLAP_A->SetMouseRegion( AID_A12, 0.265732f, 0.743055f, 0.315370f, 0.824873f );

		pHYDRAULIC_HEATER_BODY_FLAP_B->DefineGroup( GRP_S29_A12_VC );
		pHYDRAULIC_HEATER_BODY_FLAP_B->SetInitialAnimState( 0.5 );
		pHYDRAULIC_HEATER_BODY_FLAP_B->SetReference( _V( 0.0, 0.068879, -0.025329 ), switch_rot );
		pHYDRAULIC_HEATER_BODY_FLAP_B->SetMouseRegion( AID_A12, 0.345949f, 0.743055f, 0.394612f, 0.824873f );

		pHYDRAULIC_HEATER_ELEVON_A->DefineGroup( GRP_S21_A12_VC );
		pHYDRAULIC_HEATER_ELEVON_A->SetInitialAnimState( 0.5 );
		pHYDRAULIC_HEATER_ELEVON_A->SetReference( _V( 0.0, 0.068879, -0.025329 ), switch_rot );
		pHYDRAULIC_HEATER_ELEVON_A->SetMouseRegion( AID_A12, 0.419632f, 0.743055f, 0.469324f, 0.824873f );

		pHYDRAULIC_HEATER_ELEVON_B->DefineGroup( GRP_S22_A12_VC );
		pHYDRAULIC_HEATER_ELEVON_B->SetInitialAnimState( 0.5 );
		pHYDRAULIC_HEATER_ELEVON_B->SetReference( _V( 0.0, 0.068879, -0.025329 ), switch_rot );
		pHYDRAULIC_HEATER_ELEVON_B->SetMouseRegion( AID_A12, 0.489348f, 0.743055f, 0.537535f, 0.824873f );

		pHYDRAULIC_HEATER_AFT_FUSELAGE_A->DefineGroup( GRP_S19_A12_VC );
		pHYDRAULIC_HEATER_AFT_FUSELAGE_A->SetInitialAnimState( 0.5 );
		pHYDRAULIC_HEATER_AFT_FUSELAGE_A->SetReference( _V( 0.0, 0.068879, -0.025329 ), switch_rot );
		pHYDRAULIC_HEATER_AFT_FUSELAGE_A->SetMouseRegion( AID_A12, 0.567600f, 0.743055f, 0.615865f, 0.824873f );

		pHYDRAULIC_HEATER_AFT_FUSELAGE_B->DefineGroup( GRP_S20_A12_VC );
		pHYDRAULIC_HEATER_AFT_FUSELAGE_B->SetInitialAnimState( 0.5 );
		pHYDRAULIC_HEATER_AFT_FUSELAGE_B->SetReference( _V( 0.0, 0.068879, -0.025329 ), switch_rot );
		pHYDRAULIC_HEATER_AFT_FUSELAGE_B->SetMouseRegion( AID_A12, 0.637689f, 0.743055f, 0.686950f, 0.824873f );

		pHYD_CIRC_PUMP_POWER_1->DefineGroup( GRP_S25_A12_VC );
		pHYD_CIRC_PUMP_POWER_1->SetInitialAnimState( 0.5 );
		pHYD_CIRC_PUMP_POWER_1->SetReference( _V( 0.0, 0.068879, -0.025329 ), switch_rot );
		pHYD_CIRC_PUMP_POWER_1->SetMouseRegion( AID_A12, 0.737414f, 0.743055f, 0.786716f, 0.824873f );

		pHYD_CIRC_PUMP_POWER_2->DefineGroup( GRP_S26_A12_VC );
		pHYD_CIRC_PUMP_POWER_2->SetInitialAnimState( 0.5 );
		pHYD_CIRC_PUMP_POWER_2->SetReference( _V( 0.0, 0.068879, -0.025329 ), switch_rot );
		pHYD_CIRC_PUMP_POWER_2->SetMouseRegion( AID_A12, 0.807208f, 0.743055f, 0.857319f, 0.824873f );

		pHYD_CIRC_PUMP_POWER_3->DefineGroup( GRP_S27_A12_VC );
		pHYD_CIRC_PUMP_POWER_3->SetInitialAnimState( 0.5 );
		pHYD_CIRC_PUMP_POWER_3->SetReference( _V( 0.0, 0.068879, -0.025329 ), switch_rot );
		pHYD_CIRC_PUMP_POWER_3->SetMouseRegion( AID_A12, 0.876847f, 0.743055f, 0.927003f, 0.824873f );

		pLG_ARM_DN_RESET->DefineGroup( GRP_S13_A12_VC );
		pLG_ARM_DN_RESET->SetInitialAnimState( 0.5 );
		pLG_ARM_DN_RESET->SetReference( _V( 0.0, 0.18184, -0.025469 ), switch_rot );
		pLG_ARM_DN_RESET->SetMouseRegion( AID_A12, 0.673266f, 0.368038f, 0.721448f, 0.487179f );
		pLG_ARM_DN_RESET->SetPullDirection( pull_dir );
		pLG_ARM_DN_RESET->SetSpringLoaded( true, 1 );

		pFC_3_STRUCT_RTN_TB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS4_U_A12_VC, GRP_DS4_L_A12_VC );

		pFC_3_STRUCT_RTN_Cover->DefineGroup( GRP_S30_COVER_A12_VC );
		pFC_3_STRUCT_RTN_Cover->SetReference( _V( 0.0, 0.182846, -0.006075 ), switch_rot );
		pFC_3_STRUCT_RTN_Cover->SetMouseRegion( AID_A12, 0, 0.782076f, 0.442625f, 0.825631f, 0.521738f );
		pFC_3_STRUCT_RTN_Cover->SetMouseRegion( AID_A12, 1, 0.782076f, 0.412201f, 0.825631f, 0.442818f );

		pFC_3_STRUCT_RTN->DefineGroup( GRP_S30_A12_VC );
		pFC_3_STRUCT_RTN->SetInitialAnimState( 0.5 );
		pFC_3_STRUCT_RTN->SetReference( _V( 0.0, 0.169843, -0.025329 ), switch_rot );
		pFC_3_STRUCT_RTN->SetMouseRegion( AID_A12, 0.787993f, 0.442625f, 0.818006f, 0.490619f );
		pFC_3_STRUCT_RTN->SetSpringLoaded( true, 0 );
		pFC_3_STRUCT_RTN->SetSpringLoaded( true, 2 );

		if ((OV102) || (OV099))
		{
			pGPS_POWER->DefineGroup( GRP_S_A_A12_VC );
			pGPS_POWER->SetInitialAnimState( 0.5 );
			pGPS_POWER->SetReference( _V( 0.0, 0.219279, -0.025329 ), switch_rot );
			pGPS_POWER->SetMouseRegion( AID_A12, 0.563715f, 0.269052f, 0.615470f, 0.348653f );

			pENCRYPT->DefineGroup( GRP_S_B_A12_VC );
			pENCRYPT->SetInitialAnimState( 0.5 );
			pENCRYPT->SetReference( _V( 0.0, 0.146979, -0.025329 ), switch_rot );
			pENCRYPT->SetMouseRegion( AID_A12, 0.563715f, 0.497437f, 0.615470f, 0.574684f );
			pENCRYPT->SetSpringLoaded( true, 1 );

			if (OV102)
			{
				pGPS_PRE_AMP_UPPER->DefineGroup( GRP_S_C_A12_VC );
				pGPS_PRE_AMP_UPPER->SetInitialAnimState( 0.5 );
				pGPS_PRE_AMP_UPPER->SetReference( _V( 0.0, 0.169843, -0.025329 ), switch_rot );
				pGPS_PRE_AMP_UPPER->SetMouseRegion( AID_A12, 0.836082f, 0.442625f, 0.878834f, 0.490619f );

				pGPS_PRE_AMP_LOWER->DefineGroup( GRP_S_D_A12_VC );
				pGPS_PRE_AMP_LOWER->SetInitialAnimState( 0.5 );
				pGPS_PRE_AMP_LOWER->SetReference( _V( 0.0, 0.169843, -0.025329 ), switch_rot );
				pGPS_PRE_AMP_LOWER->SetMouseRegion( AID_A12, 0.881425f, 0.442625f, 0.926386f, 0.490619f );
			}
		}
		return;
	}

	void PanelA12::RegisterVC( void )
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET + OFFSET_PANEL;

		oapiVCRegisterArea( AID_A12, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_A12,
			_V( 0.5334, 0.3175, -0.0254 ) + ofs, _V( 0.0, 0.3175, -0.0254 ) + ofs,
			_V( 0.5334, 0.0, -0.0254 ) + ofs, _V( 0.0, 0.0, -0.0254 ) + ofs );
		return;
	}

	void PanelA12::Realize( void )
	{
		AtlantisPanel::Realize();

		// TODO
		return;
	}

	void PanelA12::VisualCreated( void )
	{
		DEVMESHHANDLE hDevMesh = STS()->GetDevMesh( STS()->Get_vis(), GetVCMeshIndex() );
		if (hDevMesh != NULL)
		{
			GROUPEDITSPEC grpSpec;
			grpSpec.flags = GRPEDIT_SETUSERFLAG;
			grpSpec.UsrFlag = 0x00000003;// hide group and shadow

			if (OV102)
			{
				// hide unused panel
				oapiEditMeshGroup( hDevMesh, GRP_PANEL_A12_VC, &grpSpec );
			}
			else if (OV099)
			{
				// hide unused panel and switches
				oapiEditMeshGroup( hDevMesh, GRP_PANEL_102_A12_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S_C_A12_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S_D_A12_VC, &grpSpec );

				// change texture
				if (hOV099Texture == NULL) hOV099Texture = oapiLoadTexture( "SSV\\OV\\panelA12_099.dds" );
				if (hOV099Texture == NULL) throw std::exception( "Could not load texture in panel A12" );
				else oapiSetTexture( hDevMesh, TEX_SSV_OV_PANELA12_A12_VC, hOV099Texture );
			}
			else
			{
				// hide unused panel and switches
				oapiEditMeshGroup( hDevMesh, GRP_PANEL_102_A12_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S_A_A12_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S_B_A12_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S_C_A12_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S_D_A12_VC, &grpSpec );
			}
		}

		AtlantisPanel::VisualCreated();
		return;
	}
}

#include "PanelA15.h"
#include "StandardSwitch.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_a15.h"


namespace vc
{
	const static char* MESHNAME_PANEL = "SSV\\OV\\PanelA15";
	constexpr VECTOR3 OFFSET_PANEL = {-1.64295, 1.27607, 12.4756};


	PanelA15::PanelA15( Atlantis* _sts) : AtlantisPanel( _sts, "A15" )
	{
		DefineMesh( MESHNAME_PANEL, OFFSET_PANEL );
		
		Add( pPSCommCCUPwr = new StdSwitch2( _sts, "PS COMM CCU PWR" ) );
		pPSCommCCUPwr->SetLabel( 0, "OFF" );
		pPSCommCCUPwr->SetLabel( 1, "ON" );
		Add( pDCUtilityPower = new StdSwitch2( _sts, "DC UTILITY POWER" ) );
		pDCUtilityPower->SetLabel( 0, "OFF" );
		pDCUtilityPower->SetLabel( 1, "ON" );
		Add( pACUtilityPower = new StdSwitch2( _sts, "AC UTILITY POWER" ) );
		pACUtilityPower->SetLabel( 0, "OFF" );
		pACUtilityPower->SetLabel( 1, "ON" );
		return;
	}

	PanelA15::~PanelA15( void )
	{
		return;
	}

	void PanelA15::DefineVC( void )
	{
		const VECTOR3 switch_rot =  _V( -1.0, 0.0, 0.0 );

		AddAIDToMouseEventList( AID_A15 );

		pPSCommCCUPwr->DefineGroup( GRP_S1_A15_VC );
		pPSCommCCUPwr->SetInitialAnimState( 0.5 );
		pPSCommCCUPwr->SetReference( _V( 0.0, 0.512777, -0.025329 ), switch_rot );
		pPSCommCCUPwr->SetMouseRegion( AID_A15, 0.451285f, 0.371773f, 0.484630f, 0.398001f );

		pDCUtilityPower->DefineGroup( GRP_S2_A15_VC );
		pDCUtilityPower->SetInitialAnimState( 0.5 );
		pDCUtilityPower->SetReference( _V( 0.0, 0.407409, -0.025329 ), switch_rot );
		pDCUtilityPower->SetMouseRegion( AID_A15, 0.452191f, 0.497690f, 0.484402f, 0.524807f );

		pACUtilityPower->DefineGroup( GRP_S3_A15_VC );
		pACUtilityPower->SetInitialAnimState( 0.5 );
		pACUtilityPower->SetReference( _V( 0.0, 0.30462, -0.025329 ), switch_rot );
		pACUtilityPower->SetMouseRegion( AID_A15, 0.446693f, 0.622405f, 0.484785f, 0.647413f );
		return;
	}

	void PanelA15::RegisterVC( void )
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET + OFFSET_PANEL;

		oapiVCRegisterArea( AID_A15, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_A15,
			_V( 0.84285, 0.83336, -0.0254 ) + ofs, _V( 0.27786, 0.83336, -0.0254 ) + ofs,
			_V( 0.84285, 0.0, -0.0254 ) + ofs, _V( 0.27786, 0.0, -0.0254 ) + ofs );
		return;
	}
}

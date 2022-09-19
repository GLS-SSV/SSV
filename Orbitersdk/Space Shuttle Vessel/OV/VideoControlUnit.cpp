/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/04/07   GLS
2020/05/08   GLS
2020/06/20   GLS
2021/06/18   GLS
2021/06/19   GLS
2021/07/01   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/04/08   GLS
2022/08/05   GLS
2022/09/18   GLS
2022/09/19   GLS
********************************************/
#include "VideoControlUnit.h"
#include "Atlantis.h"
#include "Atlantis_vc_defs.h"
#include "PayloadBay.h"
#include "RMS.h"
#include <Sketchpad2.h>


VideoControlUnit::VideoControlUnit( AtlantisSubsystemDirector* _director ):AtlantisSubsystem( _director, "VideoControlUnit" )
{
	outsel = OUT_MON1;
	outsel_in[OUT_MON1] = IN_A;
	outsel_in[OUT_MON2] = IN_A;
	outsel_in[OUT_DOWNLINK] = IN_A;
	outsel_in[OUT_DTV] = IN_A;
	outsel_in[OUT_MUX1L] = IN_A;
	outsel_in[OUT_MUX1R] = IN_A;
	outsel_in[OUT_MUX2L] = IN_A;
	outsel_in[OUT_MUX2R] = IN_A;

	camerapowerA = false;
	camerapowerB = false;
	camerapowerC = false;
	camerapowerD = false;
	camerapowerRMS = false;

	camhdl_camA = NULL;
	camhdl_camB = NULL;
	camhdl_camC = NULL;
	camhdl_camD = NULL;
	camhdl_camRMS = NULL;

	if (STS()->D3D9())
	{
		hSurf_camA = oapiCreateSurfaceEx( IMAGE_SIZE, IMAGE_SIZE, OAPISURFACE_RENDER3D | OAPISURFACE_TEXTURE | OAPISURFACE_RENDERTARGET | OAPISURFACE_NOMIPMAPS );
		hSurf_camB = oapiCreateSurfaceEx( IMAGE_SIZE, IMAGE_SIZE, OAPISURFACE_RENDER3D | OAPISURFACE_TEXTURE | OAPISURFACE_RENDERTARGET | OAPISURFACE_NOMIPMAPS );
		hSurf_camC = oapiCreateSurfaceEx( IMAGE_SIZE, IMAGE_SIZE, OAPISURFACE_RENDER3D | OAPISURFACE_TEXTURE | OAPISURFACE_RENDERTARGET | OAPISURFACE_NOMIPMAPS );
		hSurf_camD = oapiCreateSurfaceEx( IMAGE_SIZE, IMAGE_SIZE, OAPISURFACE_RENDER3D | OAPISURFACE_TEXTURE | OAPISURFACE_RENDERTARGET | OAPISURFACE_NOMIPMAPS );
		hSurf_camRMS = oapiCreateSurfaceEx( IMAGE_SIZE, IMAGE_SIZE, OAPISURFACE_RENDER3D | OAPISURFACE_TEXTURE | OAPISURFACE_RENDERTARGET | OAPISURFACE_NOMIPMAPS );
	}
	else
	{
		hSurf_camA = NULL;
		hSurf_camB = NULL;
		hSurf_camC = NULL;
		hSurf_camD = NULL;
		hSurf_camRMS = NULL;
	}
	return;
}

VideoControlUnit::~VideoControlUnit( void )
{
	if (camhdl_camA) STS()->D3D9()->DeleteCustomCamera( camhdl_camA );
	if (camhdl_camB) STS()->D3D9()->DeleteCustomCamera( camhdl_camB );
	if (camhdl_camC) STS()->D3D9()->DeleteCustomCamera( camhdl_camC );
	if (camhdl_camD) STS()->D3D9()->DeleteCustomCamera( camhdl_camD );
	if (camhdl_camRMS) STS()->D3D9()->DeleteCustomCamera( camhdl_camRMS );

	if (hSurf_camA) oapiDestroySurface( hSurf_camA );
	if (hSurf_camB) oapiDestroySurface( hSurf_camB );
	if (hSurf_camC) oapiDestroySurface( hSurf_camC );
	if (hSurf_camD) oapiDestroySurface( hSurf_camD );
	if (hSurf_camRMS) oapiDestroySurface( hSurf_camRMS );
}

void VideoControlUnit::Realize( void )
{
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "VCU_input_1", 16 );
	for (int i = 0; i < 16; i++) input[i].Connect( pBundle, i );

	pBundle = BundleManager()->CreateBundle( "VCU_input_2", 16 );
	for (int i = 16; i < 32; i++) input[i].Connect( pBundle, i - 16 );

	pBundle = BundleManager()->CreateBundle( "VCU_input_3", 16 );
	for (int i = 32; i < 48; i++) input[i].Connect( pBundle, i - 32 );

	pBundle = BundleManager()->CreateBundle( "VCU_input_4", 16 );
	for (int i = 48; i < 62; i++) input[i].Connect( pBundle, i - 48 );

	pBundle = BundleManager()->CreateBundle( "VCU_output_1", 16 );
	for (int i = 0; i < 16; i++) output[i + CameraPowerA_TB].Connect( pBundle, i );

	pBundle = BundleManager()->CreateBundle( "VCU_output_2", 16 );
	for (int i = 16; i < 32; i++) output[i + CameraPowerA_TB].Connect( pBundle, i - 16 );

	pBundle = BundleManager()->CreateBundle( "VCU_output_3", 16 );
	for (int i = 32; i < 36; i++) output[i + CameraPowerA_TB].Connect( pBundle, i - 32 );

	pBundle = BundleManager()->CreateBundle( "ACA4_1", 16 );
	output[VideoOutputMon1].Connect( pBundle, 2 );
	output[VideoOutputMUX1L].Connect( pBundle, 6 );
	output[VideoOutputMUX1R].Connect( pBundle, 10 );
	output[VideoOutputMon2].Connect( pBundle, 14 );

	pBundle = BundleManager()->CreateBundle( "ACA4_2", 16 );
	output[VideoOutputMUX2L].Connect( pBundle, 2 );
	output[VideoOutputMUX2R].Connect( pBundle, 6 );
	output[VideoInputA].Connect( pBundle, 10 );
	output[VideoInputB].Connect( pBundle, 14 );

	pBundle = BundleManager()->CreateBundle( "ACA4_3", 16 );
	output[VideoInputC].Connect( pBundle, 2 );
	output[VideoInputPL1].Connect( pBundle, 6 );
	output[VideoInputPL2].Connect( pBundle, 10 );
	output[VideoInputPL3].Connect( pBundle, 14 );

	pBundle = BundleManager()->CreateBundle( "ACA4_4", 16 );
	output[Mode1].Connect( pBundle, 2 );
	output[Mode2].Connect( pBundle, 6 );
	output[Mode3].Connect( pBundle, 10 );

	pBundle = BundleManager()->CreateBundle( "ACA4_5", 16 );
	output[VideoInputMidDeck].Connect( pBundle, 2 );

	pBundle = BundleManager()->CreateBundle( "ACA5_1", 16 );
	output[VideoOutputDownLink].Connect( pBundle, 10 );

	pBundle = BundleManager()->CreateBundle( "ACA5_2", 16 );
	output[VideoOutputDTV].Connect( pBundle, 6 );
	output[VideoInputD].Connect( pBundle, 10 );
	output[VideoInputRMS].Connect( pBundle, 14 );

	pBundle = BundleManager()->CreateBundle( "ACA5_3", 16 );
	output[VideoInputFltDeck].Connect( pBundle, 2 );
	output[VideoInputMUX1].Connect( pBundle, 6 );
	output[VideoInputMUX2].Connect( pBundle, 10 );
	output[VideoInputTest].Connect( pBundle, 14 );

	pBundle = BundleManager()->CreateBundle( "ACA5_4", 16 );
	output[MenuALC].Connect( pBundle, 2 );
	output[MenuManGain].Connect( pBundle, 6 );
	output[MenuColorBalLTLevel].Connect( pBundle, 10 );

	pBundle = BundleManager()->CreateBundle( "CameraManControl", 16 );
	ManPanLeft.Connect( pBundle, 0 );
	ManPanRight.Connect( pBundle, 1 );
	ManTiltUp.Connect( pBundle, 2 );
	ManTiltDown.Connect( pBundle, 3 );

	pPLB = static_cast<PayloadBay*>(director->GetSubsystemByName( "PayloadBay" ));
	pRMS = static_cast<RMS*>(director->GetSubsystemByName( "PORT_RMS" ));
	return;
}

bool VideoControlUnit::OnParseLine( const char* line )
{
	if (!_strnicmp( line, "CAMERA_POWER", 12 ))
	{
		int a = 0;
		int b = 0;
		int c = 0;
		int d = 0;
		int r = 0;
		sscanf_s( line + 12, "%d %d %d %d %d", &a, &b, &c, &d, &r );
		camerapowerA = (a != 0);
		camerapowerB = (b != 0);
		camerapowerC = (c != 0);
		camerapowerD = (d != 0);
		camerapowerRMS = (r != 0);
		return true;
	}
	else if (!_strnicmp( line, "OUTPUT", 6 ))
	{
		sscanf_s( line + 6, "%d", &outsel );
		return true;
	}
	else if (!_strnicmp( line, "INPUTS", 6 ))
	{
		sscanf_s( line + 6, "%d %d %d %d %d %d %d %d", &outsel_in[0], &outsel_in[1], &outsel_in[2], &outsel_in[3], &outsel_in[4], &outsel_in[5], &outsel_in[6], &outsel_in[7] );
		return true;
	}
	return false;
}

void VideoControlUnit::OnSaveState( FILEHANDLE scn ) const
{
	char cbuf[255];
	sprintf_s( cbuf, 255, "%d %d %d %d %d", camerapowerA, camerapowerB, camerapowerC, camerapowerD, camerapowerRMS );
	oapiWriteScenario_string( scn, "CAMERA_POWER", cbuf );

	oapiWriteScenario_int( scn, "OUTPUT", outsel );

	sprintf_s( cbuf, 255, "%d %d %d %d %d %d %d %d", outsel_in[0], outsel_in[1], outsel_in[2], outsel_in[3], outsel_in[4], outsel_in[5], outsel_in[6], outsel_in[7] );
	oapiWriteScenario_string( scn, "INPUTS", cbuf );
	return;
}

void VideoControlUnit::OnPreStep( double simt, double simdt, double mjd )
{
	// input
	camerapowerA = (camerapowerA & !input[CameraPowerOffA].IsSet()) | input[CameraPowerOnA].IsSet();
	camerapowerB = (camerapowerB & !input[CameraPowerOffB].IsSet()) | input[CameraPowerOnB].IsSet();
	camerapowerC = (camerapowerC & !input[CameraPowerOffC].IsSet()) | input[CameraPowerOnC].IsSet();
	camerapowerD = (camerapowerD & !input[CameraPowerOffD].IsSet()) | input[CameraPowerOnD].IsSet();
	camerapowerRMS = (camerapowerRMS & !input[CameraPowerOffRMS].IsSet()) | input[CameraPowerOnRMS].IsSet();

	if (input[VideoOutputMon1].IsSet()) outsel = OUT_MON1;
	else if (input[VideoOutputMon2].IsSet()) outsel = OUT_MON2;
	else if (input[VideoOutputDownLink].IsSet()) outsel = OUT_DOWNLINK;
	else if (input[VideoOutputDTV].IsSet()) outsel = OUT_DTV;
	else if (input[VideoOutputMUX1L].IsSet()) outsel = OUT_MUX1L;
	else if (input[VideoOutputMUX1R].IsSet()) outsel = OUT_MUX1R;
	else if (input[VideoOutputMUX2L].IsSet()) outsel = OUT_MUX2L;
	else if (input[VideoOutputMUX2R].IsSet()) outsel = OUT_MUX2R;

	if (input[VideoInputA].IsSet()) outsel_in[outsel] = IN_A;
	else if (input[VideoInputB].IsSet()) outsel_in[outsel] = IN_B;
	else if (input[VideoInputC].IsSet()) outsel_in[outsel] = IN_C;
	else if (input[VideoInputD].IsSet()) outsel_in[outsel] = IN_D;
	else if (input[VideoInputRMS].IsSet()) outsel_in[outsel] = IN_RMS;
	else if (input[VideoInputFltDeck].IsSet()) outsel_in[outsel] = IN_FD;
	else if (input[VideoInputMidDeck].IsSet()) outsel_in[outsel] = IN_MD;
	else if (input[VideoInputPL1].IsSet()) outsel_in[outsel] = IN_PL1;
	else if (input[VideoInputPL2].IsSet()) outsel_in[outsel] = IN_PL2;
	else if (input[VideoInputPL3].IsSet()) outsel_in[outsel] = IN_PL3;
	else if ((outsel != OUT_MUX1L) && (outsel != OUT_MUX1R) && (outsel != OUT_MUX2L) && (outsel != OUT_MUX2R))// don't select MUX or TEST into MUX
	{
		if (input[VideoInputMUX1].IsSet()) outsel_in[outsel] = IN_MUX1;
		else if (input[VideoInputMUX2].IsSet()) outsel_in[outsel] = IN_MUX2;
		else if (input[VideoInputTest].IsSet()) outsel_in[outsel] = IN_TEST;
	}

	int insel = outsel_in[outsel];

	// PTU ops
	bool left[5];
	bool right[5];
	bool up[5];
	bool down[5];
	bool in[5];
	bool out[5];
	for (int i = 0; i < 5; i++)
	{
		left[i] = false;
		right[i] = false;
		up[i] = false;
		down[i] = false;
		in[i] = false;
		out[i] = false;
	}

	if ((STS()->GetVCMode() >= VC_PLBCAMA) && (STS()->GetVCMode() <= VC_RMSCAM))
	{
		// "man" control
		if (ManPanLeft.IsSet())
		{
			left[STS()->GetVCMode() - VC_PLBCAMA] = true;
		}
		else if (ManPanRight.IsSet())
		{
			right[STS()->GetVCMode() - VC_PLBCAMA] = true;
		}

		if (ManTiltUp.IsSet())
		{
			up[STS()->GetVCMode() - VC_PLBCAMA] = true;
		}
		else if (ManTiltDown.IsSet())
		{
			down[STS()->GetVCMode() - VC_PLBCAMA] = true;
		}
	}
	else
	{
		// panel switches
		if (input[CameraCommandPanLeft].IsSet())
		{
			if (insel <= IN_RMS) left[insel] = true;
		}
		else if (input[CameraCommandPanRight].IsSet())
		{
			if (insel <= IN_RMS) right[insel] = true;
		}

		if (input[CameraCommandTiltUp].IsSet())
		{
			if (insel <= IN_RMS) up[insel] = true;
		}
		else if (input[CameraCommandTiltDown].IsSet())
		{
			if (insel <= IN_RMS) down[insel] = true;
		}
	}

	if (input[CameraCommandZoomIn].IsSet())
	{
		if (insel <= IN_RMS) in[insel] = true;
	}
	else if (input[CameraCommandZoomOut].IsSet())
	{
		if (insel <= IN_RMS) out[insel] = true;
	}

	if (STS()->D3D9())
	{
		if (camerapowerA)
		{
			double pan = (-input[PanCameraA].GetVoltage() + 90.0) * RAD;// [rad]
			double tilt = (input[TiltCameraA].GetVoltage() - 90.0) * RAD;// [rad]
			double zoom = input[ZoomCameraA].GetVoltage() * 0.5 * RAD;// [rad]
			VECTOR3 vPos;
			pPLB->GetPLBCameraPosition( 0, vPos );
			VECTOR3 vDir = _V( cos( pan ) * sin( tilt ), cos( tilt ), sin( pan ) * sin( tilt ) );
			VECTOR3 vUp = _V( cos( pan ) * sin( tilt + PI05 ), cos( tilt + PI05 ), sin( pan ) * sin( tilt + PI05 ) );

			camhdl_camA = STS()->D3D9()->SetupCustomCamera( camhdl_camA, STS()->GetHandle(), vPos, vDir, vUp, zoom, hSurf_camA, CUSTOMCAM_DEFAULTS );
		}
		else if (camhdl_camA)
		{
			STS()->D3D9()->DeleteCustomCamera( camhdl_camA );
			camhdl_camA = NULL;
	
			oapiClearSurface( hSurf_camA );
		}

		if (camerapowerB)
		{
			double pan = (-input[PanCameraB].GetVoltage() - 90.0) * RAD;// [rad]
			double tilt = (input[TiltCameraB].GetVoltage() - 90.0) * RAD;// [rad]
			double zoom = input[ZoomCameraB].GetVoltage() * 0.5 * RAD;// [rad]
			VECTOR3 vPos;
			pPLB->GetPLBCameraPosition( 1, vPos );
			VECTOR3 vDir = _V( cos( pan ) * sin( tilt ), cos( tilt ), sin( pan ) * sin( tilt ) );
			VECTOR3 vUp = _V( cos( pan ) * sin( tilt + PI05 ), cos( tilt + PI05 ), sin( pan ) * sin( tilt + PI05 ) );

			camhdl_camB = STS()->D3D9()->SetupCustomCamera( camhdl_camB, STS()->GetHandle(), vPos, vDir, vUp, zoom, hSurf_camB, CUSTOMCAM_DEFAULTS );
		}
		else if (camhdl_camB)
		{
			STS()->D3D9()->DeleteCustomCamera( camhdl_camB );
			camhdl_camB = NULL;
	
			oapiClearSurface( hSurf_camB );
		}

		if (camerapowerC)
		{
			double pan = (-input[PanCameraC].GetVoltage() - 90.0) * RAD;// [rad]
			double tilt = (input[TiltCameraC].GetVoltage() - 90.0) * RAD;// [rad]
			double zoom = input[ZoomCameraC].GetVoltage() * 0.5 * RAD;// [rad]
			VECTOR3 vPos;
			pPLB->GetPLBCameraPosition( 2, vPos );
			VECTOR3 vDir = _V( cos( pan ) * sin( tilt ), cos( tilt ), sin( pan ) * sin( tilt ) );
			VECTOR3 vUp = _V( cos( pan ) * sin( tilt + PI05 ), cos( tilt + PI05 ), sin( pan ) * sin( tilt + PI05 ) );

			camhdl_camC = STS()->D3D9()->SetupCustomCamera( camhdl_camC, STS()->GetHandle(), vPos, vDir, vUp, zoom, hSurf_camC, CUSTOMCAM_DEFAULTS );
		}
		else if (camhdl_camC)
		{
			STS()->D3D9()->DeleteCustomCamera( camhdl_camC );
			camhdl_camC = NULL;
	
			oapiClearSurface( hSurf_camC );
		}

		if (camerapowerD)
		{
			double pan = (-input[PanCameraD].GetVoltage() + 90.0) * RAD;// [rad]
			double tilt = (input[TiltCameraD].GetVoltage() - 90.0) * RAD;// [rad]
			double zoom = input[ZoomCameraD].GetVoltage() * 0.5 * RAD;// [rad]
			VECTOR3 vPos;
			pPLB->GetPLBCameraPosition( 3, vPos );
			VECTOR3 vDir = _V( cos( pan ) * sin( tilt ), cos( tilt ), sin( pan ) * sin( tilt ) );
			VECTOR3 vUp = _V( cos( pan ) * sin( tilt + PI05 ), cos( tilt + PI05 ), sin( pan ) * sin( tilt + PI05 ) );

			camhdl_camD = STS()->D3D9()->SetupCustomCamera( camhdl_camD, STS()->GetHandle(), vPos, vDir, vUp, zoom, hSurf_camD, CUSTOMCAM_DEFAULTS );
		}
		else if (camhdl_camD)
		{
			STS()->D3D9()->DeleteCustomCamera( camhdl_camD );
			camhdl_camD = NULL;
	
			oapiClearSurface( hSurf_camD );
		}

		if (camerapowerRMS && pRMS)
		{
			VECTOR3 vPos;
			VECTOR3 vDir;
			VECTOR3 vUp;
			//double pan;// [rad]
			//double tilt;// [rad]
			double zoom = input[ZoomCameraRMS].GetVoltage() * 0.5 * RAD;// [rad]
			if (input[CameraRMSWrist]) pRMS->GetCameraInfo( 0, vPos, vDir, vUp );// wrist
			else pRMS->GetCameraInfo( 1, vPos, vDir, vUp );// elbow

			sprintf_s( oapiDebugString(), 255, "%f %f %f    %f %f %f    %f %f %f   %f",
				vPos.x, vPos.y, vPos.z,
				vDir.x, vDir.y, vDir.z,
				vUp.x, vUp.y, vUp.z,
				zoom );

			camhdl_camRMS = STS()->D3D9()->SetupCustomCamera( camhdl_camRMS, STS()->GetHandle(), vPos, vDir, vUp, zoom, hSurf_camRMS, CUSTOMCAM_DEFAULTS );
		}
		else if (camhdl_camRMS)
		{
			STS()->D3D9()->DeleteCustomCamera( camhdl_camRMS );
			camhdl_camRMS = NULL;
	
			oapiClearSurface( hSurf_camRMS );
		}
	}



	// output
	output[VideoInputA].SetLine( 5.0f * (int)(insel == IN_A) );
	output[VideoInputB].SetLine( 5.0f * (int)(insel == IN_B) );
	output[VideoInputC].SetLine( 5.0f * (int)(insel == IN_C) );
	output[VideoInputD].SetLine( 5.0f * (int)(insel == IN_D) );
	output[VideoInputRMS].SetLine( 5.0f * (int)(insel == IN_RMS) );
	output[VideoInputFltDeck].SetLine( 5.0f * (int)(insel == IN_FD) );
	output[VideoInputMidDeck].SetLine( 5.0f * (int)(insel == IN_MD) );
	output[VideoInputPL1].SetLine( 5.0f * (int)(insel == IN_PL1) );
	output[VideoInputPL2].SetLine( 5.0f * (int)(insel == IN_PL2) );
	output[VideoInputPL3].SetLine( 5.0f * (int)(insel == IN_PL3) );
	output[VideoInputMUX1].SetLine( 5.0f * (int)(insel == IN_MUX1) );
	output[VideoInputMUX2].SetLine( 5.0f * (int)(insel == IN_MUX2) );
	output[VideoInputTest].SetLine( 5.0f * (int)(insel == IN_TEST) );
	output[VideoOutputMon1].SetLine( 5.0f * (int)(outsel == OUT_MON1) );
	output[VideoOutputMon2].SetLine( 5.0f * (int)(outsel == OUT_MON2) );
	output[VideoOutputDownLink].SetLine( 5.0f * (int)(outsel == OUT_DOWNLINK) );
	output[VideoOutputDTV].SetLine( 5.0f * (int)(outsel == OUT_DTV) );
	output[VideoOutputMUX1L].SetLine( 5.0f * (int)(outsel == OUT_MUX1L) );
	output[VideoOutputMUX1R].SetLine( 5.0f * (int)(outsel == OUT_MUX1R) );
	output[VideoOutputMUX2L].SetLine( 5.0f * (int)(outsel == OUT_MUX2L) );
	output[VideoOutputMUX2R].SetLine( 5.0f * (int)(outsel == OUT_MUX2R) );

	output[CameraPowerA_TB].SetLine( 5.0f * (int)camerapowerA );
	output[CameraPowerB_TB].SetLine( 5.0f * (int)camerapowerB );
	output[CameraPowerC_TB].SetLine( 5.0f * (int)camerapowerC );
	output[CameraPowerD_TB].SetLine( 5.0f * (int)camerapowerD );
	output[CameraPowerRMS_TB].SetLine( 5.0f * (int)camerapowerRMS );

	output[PTU_HighRate].SetLine( 5.0f * (int)(!input[CameraCommandReset].IsSet() & !input[CameraCommandLowRate].IsSet()) );
	output[PanLeftCameraA].SetLine( 5.0f * (int)(left[0] & camerapowerA) );
	output[PanRightCameraA].SetLine( 5.0f * (int)(right[0] & camerapowerA) );
	output[TiltUpCameraA].SetLine( 5.0f * (int)(up[0] & camerapowerA) );
	output[TiltDownCameraA].SetLine( 5.0f * (int)(down[0] & camerapowerA) );
	output[ZoomInCameraA].SetLine( 5.0f * (int)(in[0] & camerapowerA) );
	output[ZoomOutCameraA].SetLine( 5.0f * (int)(out[0] & camerapowerA) );
	output[PanLeftCameraB].SetLine( 5.0f * (int)(left[1] & camerapowerB) );
	output[PanRightCameraB].SetLine( 5.0f * (int)(right[1] & camerapowerB) );
	output[TiltUpCameraB].SetLine( 5.0f * (int)(up[1] & camerapowerB) );
	output[TiltDownCameraB].SetLine( 5.0f * (int)(down[1] & camerapowerB) );
	output[ZoomInCameraB].SetLine( 5.0f * (int)(in[1] & camerapowerB) );
	output[ZoomOutCameraB].SetLine( 5.0f * (int)(out[1] & camerapowerB) );
	output[PanLeftCameraC].SetLine( 5.0f * (int)(left[2] & camerapowerC) );
	output[PanRightCameraC].SetLine( 5.0f * (int)(right[2] & camerapowerC) );
	output[TiltUpCameraC].SetLine( 5.0f * (int)(up[2] & camerapowerC) );
	output[TiltDownCameraC].SetLine( 5.0f * (int)(down[2] & camerapowerC) );
	output[ZoomInCameraC].SetLine( 5.0f * (int)(in[2] & camerapowerC) );
	output[ZoomOutCameraC].SetLine( 5.0f * (int)(out[2] & camerapowerC) );
	output[PanLeftCameraD].SetLine( 5.0f * (int)(left[3] & camerapowerD) );
	output[PanRightCameraD].SetLine( 5.0f * (int)(right[3] & camerapowerD) );
	output[TiltUpCameraD].SetLine( 5.0f * (int)(up[3] & camerapowerD) );
	output[TiltDownCameraD].SetLine( 5.0f * (int)(down[3] & camerapowerD) );
	output[ZoomInCameraD].SetLine( 5.0f * (int)(in[3] & camerapowerD) );
	output[ZoomOutCameraD].SetLine( 5.0f * (int)(out[3] & camerapowerD) );
	output[PanLeftCameraRMS].SetLine( 5.0f * (int)(left[4] & camerapowerRMS) );
	output[PanRightCameraRMS].SetLine( 5.0f * (int)(right[4] & camerapowerRMS) );
	output[TiltUpCameraRMS].SetLine( 5.0f * (int)(up[4] & camerapowerRMS) );
	output[TiltDownCameraRMS].SetLine( 5.0f * (int)(down[4] & camerapowerRMS) );
	output[ZoomInCameraRMS].SetLine( 5.0f * (int)(in[4] & camerapowerRMS) );
	output[ZoomOutCameraRMS].SetLine( 5.0f * (int)(out[4] & camerapowerRMS) );
	return;
}

void VideoControlUnit::GetMonitorImage( const unsigned short mon, SURFHANDLE& hSurf, std::string& name, double& pan, double& tilt, double& zoom ) const
{
	switch (outsel_in[mon - 1])
	{
		case IN_A:
			oapiBlt( hSurf, hSurf_camA, 0, 0, 0, 0, IMAGE_SIZE, IMAGE_SIZE );
			name = "CAMA";
			pan = -input[PanCameraA].GetVoltage();
			tilt = input[TiltCameraA].GetVoltage();
			zoom = input[ZoomCameraA].GetVoltage();
			break;
		case IN_B:
			oapiBlt( hSurf, hSurf_camB, 0, 0, 0, 0, IMAGE_SIZE, IMAGE_SIZE );
			name = "CAMB";
			pan = -input[PanCameraB].GetVoltage();
			tilt = input[TiltCameraB].GetVoltage();
			zoom = input[ZoomCameraB].GetVoltage();
			break;
		case IN_C:
			oapiBlt( hSurf, hSurf_camC, 0, 0, 0, 0, IMAGE_SIZE, IMAGE_SIZE );
			name = "CAMC";
			pan = -input[PanCameraC].GetVoltage();
			tilt = input[TiltCameraC].GetVoltage();
			zoom = input[ZoomCameraC].GetVoltage();
			break;
		case IN_D:
			oapiBlt( hSurf, hSurf_camD, 0, 0, 0, 0, IMAGE_SIZE, IMAGE_SIZE );
			name = "CAMD";
			pan = -input[PanCameraD].GetVoltage();
			tilt = input[TiltCameraD].GetVoltage();
			zoom = input[ZoomCameraD].GetVoltage();
			break;
		case IN_RMS:
			oapiBlt( hSurf, hSurf_camRMS, 0, 0, 0, 0, IMAGE_SIZE, IMAGE_SIZE );
			name = "RMS";
			pan = 0.0;
			tilt = 0.0;
			zoom = 0.0;
			break;
		case IN_FD:
			name = "FLT";
			pan = 0.0;
			tilt = 0.0;
			zoom = 0.0;
			break;
		case IN_MD:
			name = "MID";
			pan = 0.0;
			tilt = 0.0;
			zoom = 0.0;
			break;
		case IN_PL1:
			name = "PL1";
			pan = 0.0;
			tilt = 0.0;
			zoom = 0.0;
			break;
		case IN_PL2:
			name = "PL2";
			pan = 0.0;
			tilt = 0.0;
			zoom = 0.0;
			break;
		case IN_PL3:
			name = "PL3";
			pan = 0.0;
			tilt = 0.0;
			zoom = 0.0;
			break;
		case IN_MUX1:
			switch (outsel_in[OUT_MUX1L])
			{
				case IN_A:
					oapiBlt( hSurf, hSurf_camA, 0, 0, IMAGE_SIZE4, 0, IMAGE_SIZE2, IMAGE_SIZE );
					break;
				case IN_B:
					oapiBlt( hSurf, hSurf_camB, 0, 0, IMAGE_SIZE4, 0, IMAGE_SIZE2, IMAGE_SIZE );
					break;
				case IN_C:
					oapiBlt( hSurf, hSurf_camC, 0, 0, IMAGE_SIZE4, 0, IMAGE_SIZE2, IMAGE_SIZE );
					break;
				case IN_D:
					oapiBlt( hSurf, hSurf_camD, 0, 0, IMAGE_SIZE4, 0, IMAGE_SIZE2, IMAGE_SIZE );
					break;
				case IN_RMS:
					oapiBlt( hSurf, hSurf_camRMS, 0, 0, IMAGE_SIZE4, 0, IMAGE_SIZE2, IMAGE_SIZE );
					break;
				case IN_FD:
					break;
				case IN_MD:
					break;
				case IN_PL1:
					break;
				case IN_PL2:
					break;
				case IN_PL3:
					break;
			}
			switch (outsel_in[OUT_MUX1R])
			{
				case IN_A:
					oapiBlt( hSurf, hSurf_camA, IMAGE_SIZE2, 0, IMAGE_SIZE4, 0, IMAGE_SIZE2, IMAGE_SIZE );
					break;
				case IN_B:
					oapiBlt( hSurf, hSurf_camB, IMAGE_SIZE2, 0, IMAGE_SIZE4, 0, IMAGE_SIZE2, IMAGE_SIZE );
					break;
				case IN_C:
					oapiBlt( hSurf, hSurf_camC, IMAGE_SIZE2, 0, IMAGE_SIZE4, 0, IMAGE_SIZE2, IMAGE_SIZE );
					break;
				case IN_D:
					oapiBlt( hSurf, hSurf_camD, IMAGE_SIZE2, 0, IMAGE_SIZE4, 0, IMAGE_SIZE2, IMAGE_SIZE );
					break;
				case IN_RMS:
					oapiBlt( hSurf, hSurf_camRMS, IMAGE_SIZE2, 0, IMAGE_SIZE4, 0, IMAGE_SIZE2, IMAGE_SIZE );
					break;
				case IN_FD:
					break;
				case IN_MD:
					break;
				case IN_PL1:
					break;
				case IN_PL2:
					break;
				case IN_PL3:
					break;
			}
			name = "MUX1";
			pan = 0.0;
			tilt = 0.0;
			zoom = 0.0;
			break;
		case IN_MUX2:
			switch (outsel_in[OUT_MUX2L])
			{
				case IN_A:
					oapiBlt( hSurf, hSurf_camA, 0, 0, IMAGE_SIZE4, 0, IMAGE_SIZE2, IMAGE_SIZE );
					break;
				case IN_B:
					oapiBlt( hSurf, hSurf_camB, 0, 0, IMAGE_SIZE4, 0, IMAGE_SIZE2, IMAGE_SIZE );
					break;
				case IN_C:
					oapiBlt( hSurf, hSurf_camC, 0, 0, IMAGE_SIZE4, 0, IMAGE_SIZE2, IMAGE_SIZE );
					break;
				case IN_D:
					oapiBlt( hSurf, hSurf_camD, 0, 0, IMAGE_SIZE4, 0, IMAGE_SIZE2, IMAGE_SIZE );
					break;
				case IN_RMS:
					oapiBlt( hSurf, hSurf_camRMS, 0, 0, IMAGE_SIZE4, 0, IMAGE_SIZE2, IMAGE_SIZE );
					break;
				case IN_FD:
					break;
				case IN_MD:
					break;
				case IN_PL1:
					break;
				case IN_PL2:
					break;
				case IN_PL3:
					break;
			}
			switch (outsel_in[OUT_MUX2R])
			{
				case IN_A:
					oapiBlt( hSurf, hSurf_camA, IMAGE_SIZE2, 0, IMAGE_SIZE4, 0, IMAGE_SIZE2, IMAGE_SIZE );
					break;
				case IN_B:
					oapiBlt( hSurf, hSurf_camB, IMAGE_SIZE2, 0, IMAGE_SIZE4, 0, IMAGE_SIZE2, IMAGE_SIZE );
					break;
				case IN_C:
					oapiBlt( hSurf, hSurf_camC, IMAGE_SIZE2, 0, IMAGE_SIZE4, 0, IMAGE_SIZE2, IMAGE_SIZE );
					break;
				case IN_D:
					oapiBlt( hSurf, hSurf_camD, IMAGE_SIZE2, 0, IMAGE_SIZE4, 0, IMAGE_SIZE2, IMAGE_SIZE );
					break;
				case IN_RMS:
					oapiBlt( hSurf, hSurf_camRMS, IMAGE_SIZE2, 0, IMAGE_SIZE4, 0, IMAGE_SIZE2, IMAGE_SIZE );
					break;
				case IN_FD:
					break;
				case IN_MD:
					break;
				case IN_PL1:
					break;
				case IN_PL2:
					break;
				case IN_PL3:
					break;
			}
			name = "MUX2";
			pan = 0.0;
			tilt = 0.0;
			zoom = 0.0;
			break;
		default:// case IN_TEST:
			break;
	}
	return;
}

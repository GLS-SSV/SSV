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
2023/02/05   GLS
2023/02/09   GLS
********************************************/
#include "VideoControlUnit.h"
#include "Atlantis.h"
#include "VideoSource.h"
#include "Atlantis_vc_defs.h"
#include <Sketchpad2.h>
#include <cassert>


VideoControlUnit::VideoControlUnit( AtlantisSubsystemDirector* _director ):AtlantisSubsystem( _director, "VideoControlUnit" ), power(false), cameras()
{
	outsel = OUT_MON1;
	outsel_in[OUT_MON1] = IN_FWD_BAY;
	outsel_in[OUT_MON2] = IN_FWD_BAY;
	outsel_in[OUT_DOWNLINK] = IN_FWD_BAY;
	outsel_in[OUT_DTV] = IN_FWD_BAY;
	outsel_in[OUT_MUX1L] = IN_FWD_BAY;
	outsel_in[OUT_MUX1R] = IN_FWD_BAY;
	outsel_in[OUT_MUX2L] = IN_FWD_BAY;
	outsel_in[OUT_MUX2R] = IN_FWD_BAY;

	camerapowerA = false;
	camerapowerB = false;
	camerapowerC = false;
	camerapowerD = false;
	camerapowerRMS = false;

	camhdl[0][0] = NULL;
	camhdl[0][1] = NULL;
	camhdl[1][0] = NULL;
	camhdl[1][1] = NULL;

	if (STS()->D3D9())
	{
		hSurfMon[0][0] = oapiCreateSurfaceEx( IMAGE_SIZE, IMAGE_SIZE, OAPISURFACE_RENDER3D | OAPISURFACE_TEXTURE | OAPISURFACE_RENDERTARGET | OAPISURFACE_NOMIPMAPS );
		hSurfMon[0][1] = oapiCreateSurfaceEx( IMAGE_SIZE, IMAGE_SIZE, OAPISURFACE_RENDER3D | OAPISURFACE_TEXTURE | OAPISURFACE_RENDERTARGET | OAPISURFACE_NOMIPMAPS );
		hSurfMon[1][0] = oapiCreateSurfaceEx( IMAGE_SIZE, IMAGE_SIZE, OAPISURFACE_RENDER3D | OAPISURFACE_TEXTURE | OAPISURFACE_RENDERTARGET | OAPISURFACE_NOMIPMAPS );
		hSurfMon[1][1] = oapiCreateSurfaceEx( IMAGE_SIZE, IMAGE_SIZE, OAPISURFACE_RENDER3D | OAPISURFACE_TEXTURE | OAPISURFACE_RENDERTARGET | OAPISURFACE_NOMIPMAPS );
		hSurfBlack = oapiCreateSurfaceEx( IMAGE_SIZE, IMAGE_SIZE, OAPISURFACE_RENDER3D | OAPISURFACE_TEXTURE | OAPISURFACE_RENDERTARGET | OAPISURFACE_NOMIPMAPS );
	}
	else
	{
		hSurfMon[0][0] = NULL;
		hSurfMon[0][1] = NULL;
		hSurfMon[1][0] = NULL;
		hSurfMon[1][1] = NULL;
		hSurfBlack = NULL;
	}

	for (auto &x : cameras) x = NULL;
	return;
}

VideoControlUnit::~VideoControlUnit( void )
{
	if (camhdl[0][0]) STS()->D3D9()->DeleteCustomCamera( camhdl[0][0] );
	if (camhdl[0][1]) STS()->D3D9()->DeleteCustomCamera( camhdl[0][1] );
	if (camhdl[1][0]) STS()->D3D9()->DeleteCustomCamera( camhdl[1][0] );
	if (camhdl[1][1]) STS()->D3D9()->DeleteCustomCamera( camhdl[1][1] );

	if (hSurfMon[0][0]) oapiDestroySurface( hSurfMon[0][0] );
	if (hSurfMon[0][1]) oapiDestroySurface( hSurfMon[0][1] );
	if (hSurfMon[1][0]) oapiDestroySurface( hSurfMon[1][0] );
	if (hSurfMon[1][1]) oapiDestroySurface( hSurfMon[1][1] );
	if (hSurfBlack) oapiDestroySurface( hSurfBlack );
	return;
}

void VideoControlUnit::Realize( void )
{
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "VCU_input_1", 16 );
	for (int i = 0; i < 16; i++) input[i].Connect( pBundle, i );

	pBundle = BundleManager()->CreateBundle( "VCU_input_2", 16 );
	for (int i = 16; i < 32; i++) input[i].Connect( pBundle, i - 16 );

	pBundle = BundleManager()->CreateBundle( "VCU_input_3", 16 );
	for (int i = 32; i < 47; i++) input[i].Connect( pBundle, i - 32 );

	pBundle = BundleManager()->CreateBundle( "VCU_output", 16 );
	for (int i = 0; i < 10; i++) output[i + CameraPower_FWD_BAY_TB].Connect( pBundle, i );

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

	pBundle = STS()->BundleManager()->CreateBundle( "VCU_MON_POWER", 16 );
	A_ON.Connect( pBundle, 0 );
	B_ON.Connect( pBundle, 1 );
	MNA.Connect( pBundle, 2 );
	MNB.Connect( pBundle, 3 );
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
	// power
	bool PWR_A = A_ON && MNA;
	bool PWR_B = B_ON && MNB;
	power = PWR_A ^ PWR_B;

	if (!power)
	{
		camerapowerA = false;
		camerapowerB = false;
		camerapowerC = false;
		camerapowerD = false;
		camerapowerRMS = false;

		for (auto &x : output) x.ResetLine();
		return;
	}

	// input
	camerapowerA = (camerapowerA && !input[CameraPowerOffA].IsSet()) || input[CameraPowerOnA].IsSet();
	camerapowerB = (camerapowerB && !input[CameraPowerOffB].IsSet()) || input[CameraPowerOnB].IsSet();
	camerapowerC = (camerapowerC && !input[CameraPowerOffC].IsSet()) || input[CameraPowerOnC].IsSet();
	camerapowerD = (camerapowerD && !input[CameraPowerOffD].IsSet()) || input[CameraPowerOnD].IsSet();
	camerapowerRMS = (camerapowerRMS && !input[CameraPowerOffRMS].IsSet()) || input[CameraPowerOnRMS].IsSet();

	if (input[VideoOutputMon1].IsSet()) outsel = OUT_MON1;
	else if (input[VideoOutputMon2].IsSet()) outsel = OUT_MON2;
	else if (input[VideoOutputDownLink].IsSet()) outsel = OUT_DOWNLINK;
	else if (input[VideoOutputDTV].IsSet()) outsel = OUT_DTV;
	else if (input[VideoOutputMUX1L].IsSet()) outsel = OUT_MUX1L;
	else if (input[VideoOutputMUX1R].IsSet()) outsel = OUT_MUX1R;
	else if (input[VideoOutputMUX2L].IsSet()) outsel = OUT_MUX2L;
	else if (input[VideoOutputMUX2R].IsSet()) outsel = OUT_MUX2R;

	if (input[VideoInputA].IsSet()) outsel_in[outsel] = IN_FWD_BAY;
	else if (input[VideoInputB].IsSet()) outsel_in[outsel] = IN_KEEL_EVA;
	else if (input[VideoInputC].IsSet()) outsel_in[outsel] = IN_AFT_BAY;
	else if (input[VideoInputD].IsSet()) outsel_in[outsel] = IN_STBD_RMS;
	else if (input[VideoInputRMS].IsSet()) outsel_in[outsel] = IN_PORT_RMS;
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
	bool left[10];
	bool right[10];
	bool up[10];
	bool down[10];
	bool in[10];
	bool out[10];
	for (int i = 0; i <= 9; i++)
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
			if (insel <= IN_PORT_RMS) left[insel] = true;
		}
		else if (input[CameraCommandPanRight].IsSet())
		{
			if (insel <= IN_PORT_RMS) right[insel] = true;
		}

		if (input[CameraCommandTiltUp].IsSet())
		{
			if (insel <= IN_PORT_RMS) up[insel] = true;
		}
		else if (input[CameraCommandTiltDown].IsSet())
		{
			if (insel <= IN_PORT_RMS) down[insel] = true;
		}
	}

	if (input[CameraCommandZoomIn].IsSet())
	{
		if (insel <= IN_PL3) in[insel] = true;
	}
	else if (input[CameraCommandZoomOut].IsSet())
	{
		if (insel <= IN_PL3) out[insel] = true;
	}

	// update VC camera position and direction
	if (oapiCameraInternal() && STS()->GetVCMode() >= VC_PLBCAMA && STS()->GetVCMode() <= VC_PLBCAMD/*VC_LEECAM*/)
	{
		double a = 0.0;
		double b = 0.0;
		double c = 0.0;
		double z = 20.0;// [deg]
		double pan;
		double tilt;
		double zoom;
		VECTOR3 vPos;
		VECTOR3 vDir;
		VECTOR3 vUp;

		switch (STS()->GetVCMode())
		{
			case VC_PLBCAMA:
				if (cameras[IN_FWD_BAY])
				{
					cameras[IN_FWD_BAY]->GetPhysicalData( vPos, vDir, vUp, zoom, pan, tilt );
					a = (-pan + 90.0) * RAD;
					b = (tilt - 90.0) * RAD;
					z = zoom;
				}
				break;
			case VC_PLBCAMB:
				if (cameras[IN_KEEL_EVA])
				{
					cameras[IN_KEEL_EVA]->GetPhysicalData( vPos, vDir, vUp, zoom, pan, tilt );
					a = (-pan - 90.0) * RAD;
					b = (tilt - 90.0) * RAD;
					z = zoom;
				}
				break;
			case VC_PLBCAMC:
				if (cameras[IN_AFT_BAY])
				{
					cameras[IN_AFT_BAY]->GetPhysicalData( vPos, vDir, vUp, zoom, pan, tilt );
					a = (-pan - 90.0) * RAD;
					b = (tilt - 90.0) * RAD;
					z = zoom;
				}
				break;
			case VC_PLBCAMD:
				if (cameras[IN_STBD_RMS])
				{
					cameras[IN_STBD_RMS]->GetPhysicalData( vPos, vDir, vUp, zoom, pan, tilt );
					a = (-pan + 90.0) * RAD;
					b = (tilt - 90.0) * RAD;
					z = zoom;
				}
				break;
			/*case VC_RMSCAM:
				break;
			case VC_LEECAM:
				break;*/
		}

		if (b > 0.0) c = 180.0 * RAD;

		STS()->SetCameraOffset( STS()->GetOrbiterCoGOffset() + vPos );
		STS()->SetCameraDefaultDirection( _V( cos( a ) * sin( b ), cos( b ), sin( a ) * sin( b ) ), c );
		oapiCameraSetCockpitDir( 0.0, 0.0 );
		oapiCameraSetAperture( z * 0.5 * RAD );

		// Pan and tilt from camera control not from alt + arrow but from the dialog
		STS()->SetCameraRotationRange( 0, 0, 0, 0 );
		// No lean for payload camera
		STS()->SetCameraMovement( _V(0, 0, 0), 0, 0, _V(0, 0, 0), 0, 0, _V(0, 0, 0), 0, 0 );
	}


	// output
	output[VideoInputA].SetLine( 5.0f * (int)(insel == IN_FWD_BAY) );
	output[VideoInputB].SetLine( 5.0f * (int)(insel == IN_KEEL_EVA) );
	output[VideoInputC].SetLine( 5.0f * (int)(insel == IN_AFT_BAY) );
	output[VideoInputD].SetLine( 5.0f * (int)(insel == IN_STBD_RMS) );
	output[VideoInputRMS].SetLine( 5.0f * (int)(insel == IN_PORT_RMS) );
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

	output[CameraPower_FWD_BAY_TB].SetLine( 5.0f * (int)camerapowerA );
	output[CameraPower_KEEL_EVA_TB].SetLine( 5.0f * (int)camerapowerB );
	output[CameraPower_AFT_BAY_TB].SetLine( 5.0f * (int)camerapowerC );
	output[CameraPower_STBD_RMS_TB].SetLine( 5.0f * (int)camerapowerD );
	output[CameraPower_PORT_RMS_TB].SetLine( 5.0f * (int)camerapowerRMS );

	output[CameraOn_FWD_BAY].SetLine( 5.0f * (int)camerapowerA );
	output[CameraOn_KEEL_EVA].SetLine( 5.0f * (int)camerapowerB );
	output[CameraOn_AFT_BAY].SetLine( 5.0f * (int)camerapowerC );
	output[CameraOn_STBD_RMS].SetLine( 5.0f * (int)camerapowerD );
	output[CameraOn_PORT_RMS].SetLine( 5.0f * (int)camerapowerRMS );


	for (int i = 0; i <= 9; i++)
	{
		if (cameras[i]) cameras[i]->SetCommands( left[i], right[i], up[i], down[i], !input[CameraCommandReset].IsSet() && !input[CameraCommandLowRate].IsSet(), in[i], out[i] );
	}
	return;
}

void VideoControlUnit::GetMonitorImage( const unsigned short mon, SURFHANDLE& hSurf, std::string& name, double& pan, double& tilt, double& zoom )
{
	assert( (mon >= 1) && (mon <= 2) && "VideoControlUnit::GetMonitorImage.mon" );

	if (!power)
	{
		oapiBlt( hSurf, hSurfBlack, 0, 0, 0, 0, IMAGE_SIZE, IMAGE_SIZE );
		pan = 0.0;
		tilt = 0.0;
		zoom = 0.0;
		return;
	}

	switch (outsel_in[mon - 1])
	{
		case IN_FWD_BAY:
			name = "CAMA";
			if (GetVideo( IN_FWD_BAY, mon, 0, pan, tilt, zoom )) oapiBlt( hSurf, hSurfMon[mon - 1][0], 0, 0, 0, 0, IMAGE_SIZE, IMAGE_SIZE );
			else
			{
				oapiBlt( hSurf, hSurfBlack, 0, 0, 0, 0, IMAGE_SIZE, IMAGE_SIZE );
				pan = 0.0;
				tilt = 0.0;
				zoom = 0.0;
			}
			break;
		case IN_KEEL_EVA:
			name = "CAMB";
			if (GetVideo( IN_KEEL_EVA, mon, 0, pan, tilt, zoom )) oapiBlt( hSurf, hSurfMon[mon - 1][0], 0, 0, 0, 0, IMAGE_SIZE, IMAGE_SIZE );
			else
			{
				oapiBlt( hSurf, hSurfBlack, 0, 0, 0, 0, IMAGE_SIZE, IMAGE_SIZE );
				pan = 0.0;
				tilt = 0.0;
				zoom = 0.0;
			}
			break;
		case IN_AFT_BAY:
			name = "CAMC";
			if (GetVideo( IN_AFT_BAY, mon, 0, pan, tilt, zoom )) oapiBlt( hSurf, hSurfMon[mon - 1][0], 0, 0, 0, 0, IMAGE_SIZE, IMAGE_SIZE );
			else
			{
				oapiBlt( hSurf, hSurfBlack, 0, 0, 0, 0, IMAGE_SIZE, IMAGE_SIZE );
				pan = 0.0;
				tilt = 0.0;
				zoom = 0.0;
			}
			break;
		case IN_STBD_RMS:
			name = "CAMD";
			if (GetVideo( IN_STBD_RMS, mon, 0, pan, tilt, zoom )) oapiBlt( hSurf, hSurfMon[mon - 1][0], 0, 0, 0, 0, IMAGE_SIZE, IMAGE_SIZE );
			else
			{
				oapiBlt( hSurf, hSurfBlack, 0, 0, 0, 0, IMAGE_SIZE, IMAGE_SIZE );
				pan = 0.0;
				tilt = 0.0;
				zoom = 0.0;
			}
			break;
		case IN_PORT_RMS:
			name = "RMS";
			if (GetVideo( IN_PORT_RMS, mon, 0, pan, tilt, zoom )) oapiBlt( hSurf, hSurfMon[mon - 1][0], 0, 0, 0, 0, IMAGE_SIZE, IMAGE_SIZE );
			else
			{
				oapiBlt( hSurf, hSurfBlack, 0, 0, 0, 0, IMAGE_SIZE, IMAGE_SIZE );
				pan = 0.0;
				tilt = 0.0;
				zoom = 0.0;
			}
			break;
		case IN_FD:
			/*name = "FLT";
			pan = 0.0;
			tilt = 0.0;
			zoom = 0.0;*/
			break;
		case IN_MD:
			/*name = "MID";
			pan = 0.0;
			tilt = 0.0;
			zoom = 0.0;*/
			break;
		case IN_PL1:
			name = "PL1";
			if (GetVideo( IN_PL1, mon, 0, pan, tilt, zoom )) oapiBlt( hSurf, hSurfMon[mon - 1][0], 0, 0, 0, 0, IMAGE_SIZE, IMAGE_SIZE );
			else
			{
				oapiBlt( hSurf, hSurfBlack, 0, 0, 0, 0, IMAGE_SIZE, IMAGE_SIZE );
				pan = 0.0;
				tilt = 0.0;
				zoom = 0.0;
			}
			break;
		case IN_PL2:
			name = "PL2";
			if (GetVideo( IN_PL2, mon, 0, pan, tilt, zoom )) oapiBlt( hSurf, hSurfMon[mon - 1][0], 0, 0, 0, 0, IMAGE_SIZE, IMAGE_SIZE );
			else
			{
				oapiBlt( hSurf, hSurfBlack, 0, 0, 0, 0, IMAGE_SIZE, IMAGE_SIZE );
				pan = 0.0;
				tilt = 0.0;
				zoom = 0.0;
			}
			break;
		case IN_PL3:
			name = "PL3";
			if (GetVideo( IN_PL3, mon, 0, pan, tilt, zoom )) oapiBlt( hSurf, hSurfMon[mon - 1][0], 0, 0, 0, 0, IMAGE_SIZE, IMAGE_SIZE );
			else
			{
				oapiBlt( hSurf, hSurfBlack, 0, 0, 0, 0, IMAGE_SIZE, IMAGE_SIZE );
				pan = 0.0;
				tilt = 0.0;
				zoom = 0.0;
			}
			break;
		case IN_MUX1:
			name = "MUX1";
			if (GetVideo( outsel_in[OUT_MUX1L], mon, 0, pan, tilt, zoom )) oapiBlt( hSurf, hSurfMon[mon - 1][0], 0, 0, IMAGE_SIZE4, 0, IMAGE_SIZE2, IMAGE_SIZE );
			else oapiBlt( hSurf, hSurfBlack, 0, 0, IMAGE_SIZE4, 0, IMAGE_SIZE2, IMAGE_SIZE );
			if (GetVideo( outsel_in[OUT_MUX1R], mon, 1, pan, tilt, zoom )) oapiBlt( hSurf, hSurfMon[mon - 1][1], IMAGE_SIZE2, 0, IMAGE_SIZE4, 0, IMAGE_SIZE2, IMAGE_SIZE );
			else oapiBlt( hSurf, hSurfBlack, IMAGE_SIZE2, 0, IMAGE_SIZE4, 0, IMAGE_SIZE2, IMAGE_SIZE );
			pan = 0.0;
			tilt = 0.0;
			zoom = 0.0;
			break;
		case IN_MUX2:
			name = "MUX2";
			if (GetVideo( outsel_in[OUT_MUX2L], mon, 0, pan, tilt, zoom )) oapiBlt( hSurf, hSurfMon[mon - 1][0], 0, 0, IMAGE_SIZE4, 0, IMAGE_SIZE2, IMAGE_SIZE );
			else oapiBlt( hSurf, hSurfBlack, 0, 0, IMAGE_SIZE4, 0, IMAGE_SIZE2, IMAGE_SIZE );
			if (GetVideo( outsel_in[OUT_MUX2R], mon, 1, pan, tilt, zoom )) oapiBlt( hSurf, hSurfMon[mon - 1][1], IMAGE_SIZE2, 0, IMAGE_SIZE4, 0, IMAGE_SIZE2, IMAGE_SIZE );
			else oapiBlt( hSurf, hSurfBlack, IMAGE_SIZE2, 0, IMAGE_SIZE4, 0, IMAGE_SIZE2, IMAGE_SIZE );
			pan = 0.0;
			tilt = 0.0;
			zoom = 0.0;
			break;
		default:// case IN_TEST:
			break;
	}

	// delete second camera for MUXs
	if ((outsel_in[mon - 1] != IN_MUX1) && (outsel_in[mon - 1] != IN_MUX2))
	{
		if (camhdl[mon - 1][1] != NULL)
		{
			STS()->D3D9()->DeleteCustomCamera( camhdl[mon - 1][1] );
			camhdl[mon - 1][1] = NULL;
		}
	}
	return;
}

bool VideoControlUnit::GetVideo( const unsigned int cameraidx, const unsigned short mon, const unsigned int monidx, double& pan, double& tilt, double& zoom )
{
	if (cameras[cameraidx] == NULL) return false;// no camera connected

	VECTOR3 vPos;
	VECTOR3 vDir;
	VECTOR3 vUp;
	if (cameras[cameraidx]->GetPhysicalData( vPos, vDir, vUp, zoom, pan, tilt ) == false) return false;// camera not powered

	vPos += STS()->GetOrbiterCoGOffset();
	camhdl[mon - 1][monidx] = STS()->D3D9()->SetupCustomCamera( camhdl[mon - 1][monidx], STS()->GetHandle(), vPos, vDir, vUp, zoom * 0.5 * RAD, hSurfMon[mon - 1][monidx], CUSTOMCAM_DEFAULTS );
	return true;
}

void VideoControlUnit::AddCamera( VideoSource* camera, unsigned int input )
{
	assert( (input <= 9) && "VideoControlUnit::AddCamera.input" );
	assert( (cameras[input] == NULL) && "VideoControlUnit::cameras[input]" );

	cameras[input] = camera;
	return;
}

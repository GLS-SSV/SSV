/******* SSV File Modification Notice *******
Date         Developer
2020/04/07   GLS
2020/05/10   GLS
2020/05/24   GLS
2020/05/26   GLS
2020/06/01   GLS
2020/06/12   GLS
2020/06/20   GLS
2020/06/21   GLS
2020/08/24   GLS
2020/08/30   GLS
2020/09/07   GLS
2021/06/13   GLS
2021/06/30   GLS
2021/08/24   GLS
2022/01/10   GLS
2022/01/15   GLS
2022/03/24   GLS
2022/04/17   GLS
2022/05/07   GLS
2022/08/05   GLS
2022/08/27   GLS
2022/09/29   GLS
2023/04/26   GLS
2023/05/12   GLS
2023/05/14   GLS
2025/01/23   GLS
********************************************/
#include "MDU.h"
#include "../Atlantis.h"
#include "../dps/IDP.h"
#include <MathSSV.h>
#include "vc_defs.h"
#include "../meshres_vc.h"


namespace vc
{
	HBRUSH MDU::gdiBlackBrush = NULL;
	HBRUSH MDU::gdiDarkGrayBrush;
	HBRUSH MDU::gdiLightGrayBrush;
	HBRUSH MDU::gdiWhiteBrush;
	HBRUSH MDU::gdiRedBrush;
	HBRUSH MDU::gdiYellowBrush;
	HBRUSH MDU::gdiCyanBrush;
	HBRUSH MDU::gdiMagentaBrush;
	HBRUSH MDU::gdiLightGreenBrush;
	HBRUSH MDU::gdiBlueBrush;

	oapi::Brush* MDU::skpBlackBrush = NULL;
	oapi::Brush* MDU::skpDarkGrayBrush;
	oapi::Brush* MDU::skpLightGrayBrush;
	oapi::Brush* MDU::skpWhiteBrush;
	oapi::Brush* MDU::skpRedBrush;
	oapi::Brush* MDU::skpYellowBrush;
	oapi::Brush* MDU::skpCyanBrush;
	oapi::Brush* MDU::skpMagentaBrush;
	oapi::Brush* MDU::skpLightGreenBrush;
	oapi::Brush* MDU::skpBlueBrush;
	oapi::Brush* MDU::_skpBlackBrush;

	HPEN MDU::gdiBlackPen;
	HPEN MDU::gdiDarkGrayPen;
	HPEN MDU::gdiLightGrayPen;
	HPEN MDU::gdiLightGrayThickPen;
	HPEN MDU::gdiWhitePen;
	HPEN MDU::gdiRedPen;
	HPEN MDU::gdiYellowPen;
	HPEN MDU::gdiCyanPen;
	HPEN MDU::gdiMagentaPen;
	HPEN MDU::gdiLightGreenPen;
	HPEN MDU::gdiDarkGreenPen;
	HPEN MDU::gdiLightGreenThickPen;

	oapi::Pen* MDU::skpBlackPen;
	oapi::Pen* MDU::skpDarkGrayPen;
	oapi::Pen* MDU::skpLightGrayThickPen;
	oapi::Pen* MDU::skpLightGrayPen;
	oapi::Pen* MDU::skpWhitePen;
	oapi::Pen* MDU::skpRedPen;
	oapi::Pen* MDU::skpYellowPen;
	oapi::Pen* MDU::skpCyanPen;
	oapi::Pen* MDU::skpMagentaPen;
	oapi::Pen* MDU::skpLightGreenPen;
	oapi::Pen* MDU::skpDarkGreenPen;
	oapi::Pen* MDU::skpLightGreenThickPen;
	oapi::Pen* MDU::_skpBlackPen;

	HPEN MDU::gdiNormalPen;
	HPEN MDU::gdiDashedNormalPen;
	HPEN MDU::gdiOverbrightPen;

	oapi::Pen* MDU::skpNormalPen;
	oapi::Pen* MDU::skpDashedNormalPen;
	oapi::Pen* MDU::skpOverbrightPen;

	HFONT MDU::gdiSSVAFont_h40w34;
	HFONT MDU::gdiSSVAFont_h19w19;
	HFONT MDU::gdiSSVAFont_h22w22;
	HFONT MDU::gdiSSVAFont_h19w19bold;
	HFONT MDU::gdiSSVAFont_h22w18;
	HFONT MDU::gdiSSVBFont_h36w18;
	HFONT MDU::gdiSSVBFont_h24w14;
	HFONT MDU::gdiSSVBFont_h32w18;

	oapi::Font* MDU::skpSSVAFont_h40w34;
	oapi::Font* MDU::skpSSVAFont_h19w19;
	oapi::Font* MDU::skpSSVAFont_h22w22;
	oapi::Font* MDU::skpSSVAFont_h19w19bold;
	oapi::Font* MDU::skpSSVAFont_h22w18;
	oapi::Font* MDU::skpSSVBFont_h36w18;
	oapi::Font* MDU::skpSSVBFont_h24w14;
	oapi::Font* MDU::skpSSVBFont_h32w18;

	HDC MDU::hDC_Tape_MACHV = NULL;
	HDC MDU::hDC_Tape_KEAS;
	HDC MDU::hDC_Tape_Alpha;
	HDC MDU::hDC_Tape_H;
	HDC MDU::hDC_Tape_Hdot;
	HDC MDU::hDC_ADIMASK = NULL;
	HDC MDU::hDC_ADIMASK_ORBIT;

	HBITMAP MDU::hBM_Tape_MACHV_tmp;
	HBITMAP MDU::hBM_Tape_KEAS_tmp;
	HBITMAP MDU::hBM_Tape_Alpha_tmp;
	HBITMAP MDU::hBM_Tape_H_tmp;
	HBITMAP MDU::hBM_Tape_Hdot_tmp;
	HBITMAP MDU::hBM_ADIMASK_tmp;
	HBITMAP MDU::hBM_ADIMASK_ORBIT_tmp;

	SURFHANDLE MDU::sfh_Tape_MACHV;
	SURFHANDLE MDU::sfh_Tape_KEAS;
	SURFHANDLE MDU::sfh_Tape_Alpha;
	SURFHANDLE MDU::sfh_Tape_H;
	SURFHANDLE MDU::sfh_Tape_Hdot;

	constexpr unsigned short MDU_1553_ADDR[11] = {// MDU addresses in 1553 bus
		26,// CDR1
		11,// CDR2
		28,// PLT1
		13,// PLT2
		22,// CRT1
		7,// CRT2
		21,// CRT3
		16,// CRT4
		14,// MFD1
		19,// MFD2
		25// AFD1
	};


	MDU::MDU( Atlantis* _sts, const string& _ident, unsigned short _usMDUID, BusManager* pBusManager )
		: AtlantisVCComponent(_sts, _ident), BusTerminal( pBusManager ), t0(0.0), counting(false), BezelPower(false), fontrotsmall(5.0), fontrotlarge(5.0), hADIball(NULL), usMDUID(_usMDUID),
		prim_idp(NULL), sec_idp(NULL), bInverseX(false), bUseSecondaryPort(false), bPortConfigMan(false), FC(1), fBrightness(0.8)
	{
		_sts->RegisterMDU(_usMDUID, this);

		hDC_ADI = NULL;

		if (STS()->D3D9())
		{
			// using Sketchpad in D3D9
			CreateSketchpadObjects();
			CreateTapes_Sketchpad();

			hADIball = oapiLoadMesh( "SSV\\OV\\ADI_MEDS" );
			if (!hADIball) throw std::exception( "ADI_MEDS.msh loading failed" );
		}
		else
		{
			// using GDI in MOGE
			CreateGDIObjects();
			CreateTapes_GDI();
			CreateADI();
		}

		display = 0;
		menu = 3;

		switch (usMDUID)
		{
			case MDUID_CDR1:
				pribus = 3;
				secbus = 1;
				break;
			case MDUID_CDR2:
				pribus = 1;
				secbus = 2;
				break;
			case MDUID_PLT1:
				pribus = 2;
				secbus = 1;
				break;
			case MDUID_PLT2:
				pribus = 3;
				secbus = 2;
				break;
			case MDUID_CRT1:
				pribus = 1;
				secbus = 0;
				break;
			case MDUID_CRT2:
				pribus = 2;
				secbus = 0;
				break;
			case MDUID_CRT3:
				pribus = 3;
				secbus = 0;
				break;
			case MDUID_CRT4:
				pribus = 4;
				secbus = 0;
				break;
			case MDUID_MFD1:
				pribus = 2;
				secbus = 3;
				break;
			case MDUID_MFD2:
				pribus = 1;
				secbus = 3;
				break;
			default:
			case MDUID_AFD1:
				pribus = 4;
				secbus = 2;
				break;
		}

		if (pribus == 1) BusConnect( BUS_MEDS1 );
		else if (pribus == 2) BusConnect( BUS_MEDS2 );
		else if (pribus == 3) BusConnect( BUS_MEDS3 );
		else if (pribus == 4) BusConnect( BUS_MEDS4 );

		if (secbus == 1) BusConnect( BUS_MEDS1 );
		else if (secbus == 2) BusConnect( BUS_MEDS2 );
		else if (secbus == 3) BusConnect( BUS_MEDS3 );
		else if (secbus == 4) BusConnect( BUS_MEDS4 );
		return;
	}

	MDU::~MDU()
	{
		DestroyADI();
		DestroyTapes();

		if (STS()->D3D9())
		{
			DestroySketchpadObjects();
		}
		else
		{
			DestroyGDIObjects();
		}

		if (hADIball) oapiDeleteMesh( hADIball );

		delete pPowerAnim;
		return;
	}

	bool MDU::OnReadState( FILEHANDLE scn )
	{
		char* line;

		while (oapiReadScenario_nextline( scn, line ))
		{
			if (!_strnicmp( line, "@ENDOBJECT", 10 ))
			{
				return true;
			}
			else if (!_strnicmp( line, "POWER", 5 ))
			{
				if (!_strnicmp( line + 6, "ON", 2 )) BezelPower = true;
			}
			else if (!_strnicmp( line, "DISPLAY", 7 ))
			{
				sscanf_s( (char*)(line + 7), "%d", &display );
			}
			else if (!_strnicmp( line, "MENU", 4 ))
			{
				sscanf_s( (char*)(line + 4), "%d", &menu );
			}
			else if (!_strnicmp( line, "PORT_CFG", 8 ))
			{
				if (!_strnicmp( line + 9, "MAN", 3 )) bPortConfigMan = true;
			}
			else if (!_strnicmp( line, "PORT_SEL", 8 ))
			{
				if (!_strnicmp( line + 9, "SEC", 3 ))
				{
					if (sec_idp) bUseSecondaryPort = true;
				}
			}
			else if (!_strnicmp( line, "BRIGHTNESS", 10 ))
			{
				sscanf_s( (char*)(line + 10), "%lf", &fBrightness );
				fBrightness = range( 0.2, fBrightness, 1.0 );
			}
		}
		return false;
	}

	void MDU::OnSaveState( FILEHANDLE scn ) const
	{
		oapiWriteScenario_string( scn, "POWER", BezelPower ? "ON" : "OFF" );
		oapiWriteScenario_int( scn, "DISPLAY", display );
		oapiWriteScenario_int( scn, "MENU", menu );
		oapiWriteScenario_string( scn, "PORT_CFG", bPortConfigMan ? "MAN" : "AUTO" );
		oapiWriteScenario_string( scn, "PORT_SEL", bUseSecondaryPort ? "SEC" : "PRI" );
		oapiWriteScenario_float( scn, "BRIGHTNESS", fBrightness );
		return;
	}

	void MDU::DefineVCAnimations( UINT vc_idx )
	{
		mfdspec.nmesh = vc_idx;

		// power button animation
		pPowerAnim = new MGROUP_ROTATE( vc_idx, &grpPowerIndex, 1, refPower /*+ ofs*/, dirPower, static_cast<float>(40.0 * RAD) );
		anim_power = STS()->CreateAnimation( 0.0 );
		STS()->AddAnimationComponent( anim_power, 0.0, 1.0, pPowerAnim );
		STS()->SetAnimation( anim_power, BezelPower ? 1.0 : 0.0 );
		return;
	}

	void MDU::DefineMaterial( DWORD _mat_idx )
	{
		mat_idx = _mat_idx;
		return;
	}

	void MDU::DefinePowerButtonGroup( const UINT _grpIndex )
	{
		grpPowerIndex = _grpIndex;
		return;
	}

	void MDU::SetPowerButtonReference( const VECTOR3& ref, const VECTOR3& dir )
	{
		refPower = ref;
		dirPower = dir;
		return;
	}

	void MDU::VisualCreated( void )
	{
		if (STS()->vis)
		{
			DEVMESHHANDLE hMesh = STS()->GetDevMesh( STS()->vis, mfdspec.nmesh );
			MATERIAL mat;
			oapiMeshMaterial( hMesh, mat_idx, &mat );
			mat.emissive.r = mat.emissive.g = mat.emissive.b = (float)fBrightness;
			oapiSetMaterial( hMesh, mat_idx, &mat );
		}
		return;
	}

	short MDU::GetPortConfig() const
	{
		return 0;
	}

	bool MDU::GetSelectedPort() const
	{
		return bUseSecondaryPort;
	}

	bool MDU::GetViewAngle() const
	{
		return bInverseX;
	}

	bool MDU::SetPrimaryIDP(dps::IDP *idp)
	{
		if(idp) {
			prim_idp=idp;
			return true;
		}
		else return false;
	}

	bool MDU::SetSecondaryIDP(dps::IDP *idp)
	{
		if(idp) {
			sec_idp=idp;
			return true;
		}
		else return false;
	}

	void MDU::TogglePort( void )
	{
		if (bUseSecondaryPort)
		{
			if (prim_idp) bUseSecondaryPort = false;
		}
		else if (sec_idp) bUseSecondaryPort = true;
		return;
	}

	bool MDU::OnMouseEvent(int _event, float x, float y)
	{
		//sprintf_s(oapiDebugString(), 256, "MDU %s mouse event %d (%f, %f)", GetQualifiedIdentifier().c_str(), _event, x, y);
		if ((y >= 0.842f) && (y <= 0.915f) && (x >= 0.005f) && (x <= 0.067f))
		{
			if(_event & PANEL_MOUSE_LBDOWN)
			{
				//sprintf_s(oapiDebugString(), 256, "MDU %s POWER ON/OFF", GetQualifiedIdentifier().c_str());
				BezelPower = !BezelPower;
				STS()->SetAnimation( anim_power, BezelPower ? 1.0 : 0.0 );
			}
		}
		else if ((y >= 0.842f) && (y <= 0.915f) && (x >= 0.932f) && (x <= 0.963f))
		{
			//sprintf_s(oapiDebugString(), 256, "MDU %s BRIGHTNESS", GetQualifiedIdentifier().c_str());
			if (_event & PANEL_MOUSE_LBPRESSED)
			{
				fBrightness -= oapiGetSimStep() * 0.4;
				if (fBrightness < 0.2) fBrightness = 0.2;

				VisualCreated();
			}
		}
		else if ((y >= 0.842f) && (y <= 0.915f) && (x >= 0.963f) && (x <= 0.994f))
		{
			//sprintf_s(oapiDebugString(), 256, "MDU %s BRIGHTNESS", GetQualifiedIdentifier().c_str());
			if (_event & PANEL_MOUSE_LBPRESSED)
			{
				fBrightness += oapiGetSimStep() * 0.4;
				if (fBrightness > 1.0) fBrightness = 1.0;

				VisualCreated();
			}
		}
		else if ((y >= 0.943f) && (y <= 0.994f))
		{
			float edgekeyClickPos = (x - 0.195f) / (0.806f - 0.195f); // calculate horizontal position of click relative to left edge of edgekey area (scaled between 0 and 1)
			if ((edgekeyClickPos >= 0.0) && (edgekeyClickPos <= 0.08))
			{
				if(_event & PANEL_MOUSE_LBDOWN)
				{
					//sprintf_s(oapiDebugString(), 256, "MDU %s BUTTON 1", GetQualifiedIdentifier().c_str());
					oapiProcessMFDButton (usMDUID, 0, _event);
				}
			}
			else if ((edgekeyClickPos >= 0.18) && (edgekeyClickPos <= 0.26))
			{
				if(_event & PANEL_MOUSE_LBDOWN)
				{
					//sprintf_s(oapiDebugString(), 256, "MDU %s BUTTON 2", GetQualifiedIdentifier().c_str());
					oapiProcessMFDButton (usMDUID, 1, _event);
				}
			}
			else if ((edgekeyClickPos >= 0.365) && (edgekeyClickPos <= 0.445))
			{
				if(_event & PANEL_MOUSE_LBDOWN)
				{
					//sprintf_s(oapiDebugString(), 256, "MDU %s BUTTON 3", GetQualifiedIdentifier().c_str());
					oapiProcessMFDButton (usMDUID, 2, _event);
				}
			}
			else if(edgekeyClickPos >= 0.55 && edgekeyClickPos <= 0.63)
			{
				if(_event & PANEL_MOUSE_LBDOWN)
				{
					//sprintf_s(oapiDebugString(), 256, "MDU %s BUTTON 4", GetQualifiedIdentifier().c_str());
					oapiProcessMFDButton (usMDUID, 3, _event);
				}
			}
			else if ((edgekeyClickPos >= 0.74) && (edgekeyClickPos <= 0.82))
			{
				if(_event & PANEL_MOUSE_LBDOWN)
				{
					//sprintf_s(oapiDebugString(), 256, "MDU %s BUTTON 5", GetQualifiedIdentifier().c_str());
					oapiProcessMFDButton (usMDUID, 4, _event);
				}
			}
			else if ((edgekeyClickPos >= 0.92) && (edgekeyClickPos <= 1.0))
			{
				if (_event & PANEL_MOUSE_LBDOWN) {
					t0 = oapiGetSysTime();
					//sprintf_s(oapiDebugString(), 256, "MDU %s BUTTON 6 (%f)", GetQualifiedIdentifier().c_str(), t0);
					counting = true;
				} else if ((_event & PANEL_MOUSE_LBUP) && counting) {
					//sprintf_s(oapiDebugString(), 256, "MDU %s BUTTON 6: SWITCH PAGE", GetQualifiedIdentifier().c_str());
					oapiSendMFDKey (usMDUID, OAPI_KEY_F2);
					counting = false;
				} else if ((_event & PANEL_MOUSE_LBPRESSED) && counting && (oapiGetSysTime()-t0 >= 1.0)) {
					//sprintf_s(oapiDebugString(), 256, "MDU %s BUTTON 6: SWITCH MODE", GetQualifiedIdentifier().c_str());
					oapiSendMFDKey (usMDUID, OAPI_KEY_F1);
					counting = false;
				}
			}
			//else sprintf_s(oapiDebugString(), 256, "MDU %s EDGEKEYS: %f", GetQualifiedIdentifier().c_str(), edgekeyClickPos);
		}
		return true;
	}

	void MDU::OnPreStep( double simt, double simdt, double mjd )
	{
		if (!dipPower.IsSet())
		{
			// no power supply -> force off
			if (oapiGetMFDMode( usMDUID ) != MFD_NONE)
			{
				oapiOpenMFD( MFD_NONE, usMDUID );
			}
			return;
		}

		if (BezelPower)
		{
			// if off -> turn on
			if (oapiGetMFDMode( usMDUID ) == MFD_NONE)
			{
				oapiOpenMFD( 1000, usMDUID );
			}
		}
		else
		{
			// if on -> turn off
			if (oapiGetMFDMode( usMDUID ) != MFD_NONE)
			{
				oapiOpenMFD( MFD_NONE, usMDUID );
			}
		}
		return;
	}

	void MDU::PaintDisplay( oapi::Sketchpad* skp )
	{
		switch (display)
		{
			case 0:// "DPS display"
				if (STS()->D3D9())
				{
					skp->SetBrush( skpBlackBrush );
					skp->SetPen( skpBlackPen );
					skp->Rectangle( 0, 0, 1024, 1024 );
					skp->SetBrush( NULL );// disable fill
					DPS( skp );
					PaintEdgeMenu( skp );
				}
				else
				{
					HDC hDC = skp->GetDC();
					if (hDC)
					{
						int save = SaveDC( hDC );
						SelectObject( hDC, gdiBlackBrush );
						SelectObject( hDC, gdiBlackPen );
						Rectangle( hDC, 0, 0, 1024, 1024 );
						SelectObject( hDC, GetStockObject( HOLLOW_BRUSH ) );// disable fill
						DPS( hDC );
						PaintEdgeMenu( hDC );
						RestoreDC( hDC, save );
					}
					else oapiWriteLog( "(SSV_OV) [ERROR] no GDI handle" );
				}
				break;
			case 1:// A/E PFD
				if (STS()->D3D9())
				{
					skp->SetBrush( skpBlackBrush );
					skp->SetPen( skpBlackPen );
					skp->Rectangle( 0, 0, 1024, 1024 );
					AEPFD( skp );
					PaintEdgeMenu( skp );
				}
				else
				{
					HDC hDC = skp->GetDC();
					if (hDC)
					{
						int save = SaveDC( hDC );
						SelectObject( hDC, gdiBlackBrush );
						SelectObject( hDC, gdiBlackPen );
						Rectangle( hDC, 0, 0, 1024, 1024 );
						AEPFD( hDC );
						PaintEdgeMenu( hDC );
						RestoreDC( hDC, save );
					}
					else oapiWriteLog( "(SSV_OV) [ERROR] no GDI handle" );
				}
				break;
			case 2:// ORBIT PFD
				if (STS()->D3D9())
				{
					skp->SetBrush( skpBlackBrush );
					skp->SetPen( skpBlackPen );
					skp->Rectangle( 0, 0, 1024, 1024 );
					ORBITPFD( skp );
					PaintEdgeMenu( skp );
				}
				else
				{
					HDC hDC = skp->GetDC();
					if (hDC)
					{
						int save = SaveDC( hDC );
						SelectObject( hDC, gdiBlackBrush );
						SelectObject( hDC, gdiBlackPen );
						Rectangle( hDC, 0, 0, 1024, 1024 );
						ORBITPFD( hDC );
						PaintEdgeMenu( hDC );
						RestoreDC( hDC, save );
					}
					else oapiWriteLog( "(SSV_OV) [ERROR] no GDI handle" );
				}
				break;
			case 3:// OMS/MPS
				if (STS()->D3D9())
				{
					skp->SetBrush( skpBlackBrush );
					skp->SetPen( skpBlackPen );
					skp->Rectangle( 0, 0, 1024, 1024 );
					OMSMPS( skp );
					PaintEdgeMenu( skp );
				}
				else
				{
					HDC hDC = skp->GetDC();
					if (hDC)
					{
						int save = SaveDC( hDC );
						SelectObject( hDC, gdiBlackBrush );
						SelectObject( hDC, gdiBlackPen );
						Rectangle( hDC, 0, 0, 1024, 1024 );
						OMSMPS( hDC );
						PaintEdgeMenu( hDC );
						RestoreDC( hDC, save );
					}
					else oapiWriteLog( "(SSV_OV) [ERROR] no GDI handle" );
				}
				break;
			case 4:// HYD/APU
				if (STS()->D3D9())
				{
					skp->SetBrush( skpBlackBrush );
					skp->SetPen( skpBlackPen );
					skp->Rectangle( 0, 0, 1024, 1024 );
					APUHYD( skp );
					PaintEdgeMenu( skp );
				}
				else
				{
					HDC hDC = skp->GetDC();
					if (hDC)
					{
						int save = SaveDC( hDC );
						SelectObject( hDC, gdiBlackBrush );
						SelectObject( hDC, gdiBlackPen );
						Rectangle( hDC, 0, 0, 1024, 1024 );
						APUHYD( hDC );
						PaintEdgeMenu( hDC );
						RestoreDC( hDC, save );
					}
					else oapiWriteLog( "(SSV_OV) [ERROR] no GDI handle" );
				}
				break;
			case 5:// SPI
				if (STS()->D3D9())
				{
					skp->SetBrush( skpBlackBrush );
					skp->SetPen( skpBlackPen );
					skp->Rectangle( 0, 0, 1024, 1024 );
					SPI( skp );
					PaintEdgeMenu( skp );
				}
				else
				{
					HDC hDC = skp->GetDC();
					if (hDC)
					{
						int save = SaveDC( hDC );
						SelectObject( hDC, gdiBlackBrush );
						SelectObject( hDC, gdiBlackPen );
						Rectangle( hDC, 0, 0, 1024, 1024 );
						SPI( hDC );
						PaintEdgeMenu( hDC );
						RestoreDC( hDC, save );
					}
					else oapiWriteLog( "(SSV_OV) [ERROR] no GDI handle" );
				}
				break;
			case 6:// CST Menu
				if (STS()->D3D9())
				{
					skp->SetBrush( skpBlackBrush );
					skp->SetPen( skpBlackPen );
					skp->Rectangle( 0, 0, 1024, 1024 );
					SystemStatusDisplay_CSTMenu( skp );
					PaintEdgeMenu( skp );
				}
				else
				{
					HDC hDC = skp->GetDC();
					if (hDC)
					{
						int save = SaveDC( hDC );
						SelectObject( hDC, gdiBlackBrush );
						SelectObject( hDC, gdiBlackPen );
						Rectangle( hDC, 0, 0, 1024, 1024 );
						SystemStatusDisplay_CSTMenu( hDC );
						PaintEdgeMenu( hDC );
						RestoreDC( hDC, save );
					}
					else oapiWriteLog( "(SSV_OV) [ERROR] no GDI handle" );
				}
				break;
			case 7:// IDP Interactive CST
				if (STS()->D3D9())
				{
					skp->SetBrush( skpBlackBrush );
					skp->SetPen( skpBlackPen );
					skp->Rectangle( 0, 0, 1024, 1024 );
					SystemStatusDisplay_IDPInteractiveCST( skp );
					PaintEdgeMenu( skp );
				}
				else
				{
					HDC hDC = skp->GetDC();
					if (hDC)
					{
						int save = SaveDC( hDC );
						SelectObject( hDC, gdiBlackBrush );
						SelectObject( hDC, gdiBlackPen );
						Rectangle( hDC, 0, 0, 1024, 1024 );
						SystemStatusDisplay_IDPInteractiveCST( hDC );
						PaintEdgeMenu( hDC );
						RestoreDC( hDC, save );
					}
					else oapiWriteLog( "(SSV_OV) [ERROR] no GDI handle" );
				}
				break;
		}
		return;
	}

	bool MDU::NavigateMenu( DWORD key )
	{
		switch (menu)
		{
			case 0:// MAIN MENU
				switch (key)
				{
					case OAPI_KEY_1:
						menu = 1;
						return true;
					case OAPI_KEY_2:
						menu = 2;
						return true;
					case OAPI_KEY_3:
						menu = 3;
						display = 0;
						return true;
					case OAPI_KEY_4:
						menu = 4;
						display = 6;
						return true;
				}
				break;
			case 1:// FLT INST
				switch (key)
				{
					case OAPI_KEY_U:
						menu = 0;
						return true;
					case OAPI_KEY_1:
						display = 1;
						return true;
					case OAPI_KEY_2:
						display = 2;
						return true;
				}
				break;
			case 2:// SUBSYS STATUS
				switch (key)
				{
					case OAPI_KEY_U:
						menu = 0;
						return true;
					case OAPI_KEY_1:
						display = 3;
						return true;
					case OAPI_KEY_2:
						display = 4;
						return true;
					case OAPI_KEY_3:
						display = 5;
						return true;
					case OAPI_KEY_4:
						TogglePort();
						return true;
				}
				break;
			case 3:// DPS MENU
				switch (key)
				{
					case OAPI_KEY_U:
						menu = 0;
						return true;
				}
				break;
			case 4:// MAINTENANCE MENU
				switch (key)
				{
					case OAPI_KEY_U:
						menu = 0;
						return true;
					case OAPI_KEY_2:
						menu = 7;
						return true;
					case OAPI_KEY_3:
						menu = 5;
						return true;
				}
				break;
			case 5:// CST MENU SELECTION
				switch (key)
				{
					case OAPI_KEY_U:
						menu = 4;
						display = 6;
						return true;
					case OAPI_KEY_2:
						menu = 6;
						display = 7;
						return true;
				}
				break;
			case 6:// IDPx INTERACTIVE CST
				switch (key)
				{
					case OAPI_KEY_U:
						menu = 5;
						return true;
				}
				break;
			case 7:// MDU CONFIGURATION MENU
				switch (key)
				{
					case OAPI_KEY_U:
						menu = 4;
						return true;
					case OAPI_KEY_1:
						TogglePort();
						return true;
					case OAPI_KEY_2:
						bPortConfigMan = !bPortConfigMan;
						return true;
				}
				break;
		}
		return false;
	}

	char* MDU::ButtonLabel( int bt )
	{
		static char *label[8][5] = {{"", "FLT", "SUB", "DPS", "MEDS1"},
			{"UP", "A/E", "ORBIT", "", ""},
			{"UP", "OMS", "HYD", "SPI", "PORT"},
			{"UP", "", "", "", ""},
			{"UP", "", "CFG", "CST", ""},
			{"UP", "", "S_IDP", "", ""},
			{"UP", "", "", "", ""},
			{"UP", "PORT", "AU/MA", "", ""}};

		return ((menu < 8 && bt < 5) ? label[menu][bt] : NULL);
	}

	int MDU::ButtonMenu( const MFDBUTTONMENU **menu ) const
	{
		static const MFDBUTTONMENU mnu[8][5] = {
			{{"", 0, 'U'}, {"FLT INST", 0, '1'}, {"SUBSYS STATUS", 0, '2'}, {"DPS", 0, '3'}, {"MEDS MAINT", 0, '4'}},
			{{"Move up", 0, 'U'}, {"A/E PFD", 0, '1'}, {"ORBIT PFD", 0, '2'}, {"", 0, '3'}, {"", 0, '4'}},
			{{"Move up", 0, 'U'}, {"OMS/MPS", 0, '1'}, {"HYD/APU", 0, '2'}, {"SPI", 0, '3'}, {"PORT SELECT", 0, '4'}},
			{{"Move up", 0, 'U'}, {"", 0, '1'}, {"", 0, '2'}, {"", 0, '3'}, {"", 0, '4'}},
			{{"Move up", 0, 'U'}, {"", 0, '1'}, {"CONFIG STATUS", 0, '2'}, {"CST", 0, '3'}, {"", 0, '4'}},
			{{"Move up", 0, 'U'}, {"", 0, '1'}, {"START IDP", 0, '2'}, {"", 0, '3'}, {"", 0, '4'}},
			{{"Move up", 0, 'U'}, {"", 0, '1'}, {"", 0, '2'}, {"0", 0, '3'}, {"", 0, '4'}},
			{{"Move up", 0, 'U'}, {"PORT SELECT", 0, '1'}, {"AUTO/MAN", 0, '2'}, {"0", 0, '3'}, {"", 0, '4'}}
			};

		if (menu) *menu = mnu[this->menu];
		return 5;// return the number of buttons used
	}

	void MDU::PaintEdgeMenu( HDC hDC )
	{
		SelectObject( hDC, gdiCyanPen );
		MoveToEx( hDC, 0, 912, NULL );
		LineTo( hDC, 1022, 912 );
		SelectObject( hDC, gdiSSVAFont_h22w18 );
		SetTextColor( hDC, CR_CYAN );
		SetTextAlign( hDC, TA_CENTER );

		// print buttons
		int x = 132;
		// button 1
		DrawMenuButton( hDC, x );
		if (menu != 0)
		{
			// draw up arrow
			MoveToEx( hDC, 108, 1020, NULL );
			LineTo( hDC, 108, 1000 );
			LineTo( hDC, 80, 1000 );
			LineTo( hDC, 132, 972 );
			LineTo( hDC, 184, 1000 );
			LineTo( hDC, 156, 1000 );
			LineTo( hDC, 156, 1020 );
			TextOut( hDC, x, 986, "UP", 2);
		}

		// button 2
		x += 152;
		if (menu == 0)
		{
			TextOut( hDC, x, 972, "FLT", 3 );
			TextOut( hDC, x, 998, " INST", 5 );
			DrawMenuButton( hDC, x );
		}
		else if (menu == 1)
		{
			if (display == 1)
			{
				SetTextColor( hDC, CR_WHITE );
				TextOut( hDC, x, 972, "A/E", 3 );
				TextOut( hDC, x, 998, "PFD", 3 );
				SetTextColor( hDC, CR_CYAN );
				SelectObject( hDC, gdiWhitePen );
				DrawMenuButton( hDC, x );
				SelectObject( hDC, gdiCyanPen );
			}
			else
			{
				TextOut( hDC, x, 972, "A/E", 3 );
				TextOut( hDC, x, 998, "PFD", 3 );
				DrawMenuButton( hDC, x );
			}
		}
		else if (menu == 2)
		{
			if (display == 3)
			{
				SetTextColor( hDC, CR_WHITE );
				TextOut( hDC, x, 972, "OMS/ ", 5 );
				TextOut( hDC, x, 998, "MPS", 3 );
				SetTextColor( hDC, CR_CYAN );
				SelectObject( hDC, gdiWhitePen );
				DrawMenuButton( hDC, x );
				SelectObject( hDC, gdiCyanPen );
			}
			else
			{
				TextOut( hDC, x, 972, "OMS/ ", 5 );
				TextOut( hDC, x, 998, "MPS", 3 );
				DrawMenuButton( hDC, x );
			}
		}
		else if (menu == 7)
		{
			TextOut( hDC, x, 972, "PORT ", 5 );
			TextOut( hDC, x, 998, "SELECT ", 7 );
			DrawMenuButton( hDC, x );
		}
		else DrawMenuButton( hDC, x );

		// button 3
		x += 152;
		if (menu == 0)
		{
			TextOut( hDC, x, 972, "SUBSYS ", 7 );
			TextOut( hDC, x, 998, "STATUS ", 7 );
			DrawMenuButton( hDC, x );
		}
		else if (menu == 1)
		{
			if (display == 2)
			{
				SetTextColor( hDC, CR_WHITE );
				TextOut( hDC, x, 972, "ORBIT", 5 );
				TextOut( hDC, x, 998, "PFD", 3 );
				SetTextColor( hDC, CR_CYAN );
				SelectObject( hDC, gdiWhitePen );
				DrawMenuButton( hDC, x );
				SelectObject( hDC, gdiCyanPen );
			}
			else
			{
				TextOut( hDC, x, 972, "ORBIT", 5 );
				TextOut( hDC, x, 998, "PFD", 3 );
				DrawMenuButton( hDC, x );
			}
		}
		else if (menu == 2)
		{
			if (display == 4)
			{
				SetTextColor( hDC, CR_WHITE );
				TextOut( hDC, x, 972, "HYD/ ", 5 );
				TextOut( hDC, x, 998, "APU", 3 );
				SetTextColor( hDC, CR_CYAN );
				SelectObject( hDC, gdiWhitePen );
				DrawMenuButton( hDC, x );
				SelectObject( hDC, gdiCyanPen );
			}
			else
			{
				TextOut( hDC, x, 972, "HYD/ ", 5 );
				TextOut( hDC, x, 998, "APU", 3 );
				DrawMenuButton( hDC, x );
			}
		}
		else if (menu == 4)
		{
			TextOut( hDC, x, 972, "CONFIG ", 7 );
			TextOut( hDC, x, 998, "STATUS ", 7 );
			DrawMenuButton( hDC, x );
		}
		else if (menu == 5)
		{
			TextOut( hDC, x, 972, "START", 5 );
			TextOut( hDC, x, 998, "IDP", 3 );
			DrawMenuButton( hDC, x );
		}
		else if (menu == 7)
		{
			TextOut( hDC, x, 972, "AUTO/", 5 );
			TextOut( hDC, x, 998, "MANUAL ", 7 );
			DrawMenuButton( hDC, x );
		}
		else DrawMenuButton( hDC, x );

		// button 4
		x += 152;
		if (menu == 0)
		{
			TextOut( hDC, x, 972, "DPS", 3 );
			DrawMenuButton( hDC, x );
		}
		else if (menu == 2)
		{
			if (display == 5)
			{
				SetTextColor( hDC, CR_WHITE );
				TextOut( hDC, x, 972, "SPI", 3 );
				SetTextColor( hDC, CR_CYAN );
				SelectObject( hDC, gdiWhitePen );
				DrawMenuButton( hDC, x );
				SelectObject( hDC, gdiCyanPen );
			}
			else
			{
				TextOut( hDC, x, 972, "SPI", 3 );
				DrawMenuButton( hDC, x );
			}
		}
		else if (menu == 4)
		{
			TextOut( hDC, x, 972, "CST", 3 );
			DrawMenuButton( hDC, x );
		}
		else DrawMenuButton( hDC, x );

		// button 5
		x += 152;
		DrawMenuButton( hDC, x );
		if (menu == 0)
		{
			TextOut( hDC, x, 972, "MEDS ", 5 );
			TextOut( hDC, x, 998, "MAINT", 5 );
		}
		else if (menu == 2)
		{
			TextOut( hDC, x, 972, "PORT ", 5 );
			TextOut( hDC, x, 998, "SELECT ", 7 );
		}

		// button 6
		x += 152;
		//TextOut( hDC, x, 50, "PG", 2 );
		DrawMenuButton( hDC, x );

		// print title
		switch (menu)
		{
			case 0:
				TextOut( hDC, 452, 942, "MAIN MENU", 9 );
				break;
			case 1:
				TextOut( hDC, 452, 942, " FLIGHT INSTRUMENT MENU", 23 );
				break;
			case 2:
				TextOut( hDC, 452, 942, "SUBSYSTEM MENU ", 15 );
				break;
			case 3:
				TextOut( hDC, 452, 942, "DPS MENU ", 9 );
				break;
			case 4:
				TextOut( hDC, 452, 942, " MAINTENANCE MENU", 17 );
				break;
			case 5:
				TextOut( hDC, 452, 942, " CST MENU SELECTION", 19 );
				break;
			case 6:
				{
					char buf[32];
					sprintf_s( buf, 32, " IDP%d INTERACTIVE CST", GetIDP()->GetIDPID() );
					TextOut( hDC, 452, 942, buf, strlen( buf ) );
				}
				break;
			case 7:
				TextOut( hDC, 452, 942, " MDU CONFIGURATION MENU", 23 );
				break;
			default:
				// print nothing
				break;
		}

		// print configuration info
		if (prim_idp)
		{
			char str[4];
			str[0] = 'P';
			str[1] = prim_idp->GetIDPID() + 48;
			str[2] = bUseSecondaryPort ? ' ' : '*';
			str[3] = 0;
			TextOut( hDC, 30, 972, str, 3 );
		}

		if (sec_idp)
		{
			char str[4];
			str[0] = 'S';
			str[1] = sec_idp->GetIDPID() + 48;
			str[2] = !bUseSecondaryPort ? ' ' : '*';
			str[3] = 0;
			TextOut( hDC, 30, 998, str, 3 );
		}
		{
			char str[4];
			str[0] = 'F';
			str[1] = 'C';
			str[2] = FC + 48;
			str[3] = 0;
			TextOut( hDC, 994, 972, str, 3 );
		}
		if (bPortConfigMan) TextOut( hDC, 994, 998, "MAN", 3 );
		else TextOut( hDC, 994, 998, "AUT", 3 );

		// print MEDS fault line
		/*if (!GetFlash())
		{
			SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 452, 916, "IDP 1 2 3 4 STILL WIP", 21 );
		}*/
		return;
	}

	void MDU::PaintEdgeMenu( oapi::Sketchpad* skp )
	{
		skp->SetPen( skpCyanPen );
		skp->Line( 0, 912, 1022, 912 );
		skp->SetFont( skpSSVAFont_h22w18 );
		skp->SetTextColor( CR_CYAN );
		skp->SetTextAlign( oapi::Sketchpad::CENTER );

		// print buttons
		int x = 132;
		// button 1
		DrawMenuButton( skp, x );
		if (menu != 0)
		{
			// draw up arrow
			skp->MoveTo( 108, 1020 );
			skp->LineTo( 108, 1000 );
			skp->LineTo( 80, 1000 );
			skp->LineTo( 132, 972 );
			skp->LineTo( 184, 1000 );
			skp->LineTo( 156, 1000 );
			skp->LineTo( 156, 1020 );
			skp->Text( x, 986, "UP", 2);
		}

		// button 2
		x += 152;
		if (menu == 0)
		{
			skp->Text( x, 972, "FLT", 3 );
			skp->Text( x, 998, " INST", 5 );
			DrawMenuButton( skp, x );
		}
		else if (menu == 1)
		{
			if (display == 1)
			{
				skp->SetTextColor( CR_WHITE );
				skp->Text( x, 972, "A/E", 3 );
				skp->Text( x, 998, "PFD", 3 );
				skp->SetTextColor( CR_CYAN );
				skp->SetPen( skpWhitePen );
				DrawMenuButton( skp, x );
				skp->SetPen( skpCyanPen );
			}
			else
			{
				skp->Text( x, 972, "A/E", 3 );
				skp->Text( x, 998, "PFD", 3 );
				DrawMenuButton( skp, x );
			}
		}
		else if (menu == 2)
		{
			if (display == 3)
			{
				skp->SetTextColor( CR_WHITE );
				skp->Text( x, 972, "OMS/ ", 5 );
				skp->Text( x, 998, "MPS", 3 );
				skp->SetTextColor( CR_CYAN );
				skp->SetPen( skpWhitePen );
				DrawMenuButton( skp, x );
				skp->SetPen( skpCyanPen );
			}
			else
			{
				skp->Text( x, 972, "OMS/ ", 5 );
				skp->Text( x, 998, "MPS", 3 );
				DrawMenuButton( skp, x );
			}
		}
		else if (menu == 7)
		{
			skp->Text( x, 972, "PORT ", 5 );
			skp->Text( x, 998, "SELECT ", 7 );
			DrawMenuButton( skp, x );
		}
		else DrawMenuButton( skp, x );

		// button 3
		x += 152;
		if (menu == 0)
		{
			skp->Text( x, 972, "SUBSYS ", 7 );
			skp->Text( x, 998, "STATUS ", 7 );
			DrawMenuButton( skp, x );
		}
		else if (menu == 1)
		{
			if (display == 2)
			{
				skp->SetTextColor( CR_WHITE );
				skp->Text( x, 972, "ORBIT", 5 );
				skp->Text( x, 998, "PFD", 3 );
				skp->SetTextColor( CR_CYAN );
				skp->SetPen( skpWhitePen );
				DrawMenuButton( skp, x );
				skp->SetPen( skpCyanPen );
			}
			else
			{
				skp->Text( x, 972, "ORBIT", 5 );
				skp->Text( x, 998, "PFD", 3 );
				DrawMenuButton( skp, x );
			}
		}
		else if (menu == 2)
		{
			if (display == 4)
			{
				skp->SetTextColor( CR_WHITE );
				skp->Text( x, 972, "HYD/ ", 5 );
				skp->Text( x, 998, "APU", 3 );
				skp->SetTextColor( CR_CYAN );
				skp->SetPen( skpWhitePen );
				DrawMenuButton( skp, x );
				skp->SetPen( skpCyanPen );
			}
			else
			{
				skp->Text( x, 972, "HYD/ ", 5 );
				skp->Text( x, 998, "APU", 3 );
				DrawMenuButton( skp, x );
			}
		}
		else if (menu == 4)
		{
			skp->Text( x, 972, "CONFIG ", 7 );
			skp->Text( x, 998, "STATUS ", 7 );
			DrawMenuButton( skp, x );
		}
		else if (menu == 5)
		{
			skp->Text( x, 972, "START", 5 );
			skp->Text( x, 998, "IDP", 3 );
			DrawMenuButton( skp, x );
		}
		else if (menu == 7)
		{
			skp->Text( x, 972, "AUTO/", 5 );
			skp->Text( x, 998, "MANUAL ", 7 );
			DrawMenuButton( skp, x );
		}
		else DrawMenuButton( skp, x );

		// button 4
		x += 152;
		if (menu == 0)
		{
			skp->Text( x, 972, "DPS", 3 );
			DrawMenuButton( skp, x );
		}
		else if (menu == 2)
		{
			if (display == 5)
			{
				skp->SetTextColor( CR_WHITE );
				skp->Text( x, 972, "SPI", 3 );
				skp->SetTextColor( CR_CYAN );
				skp->SetPen( skpWhitePen );
				DrawMenuButton( skp, x );
				skp->SetPen( skpCyanPen );
			}
			else
			{
				skp->Text( x, 972, "SPI", 3 );
				DrawMenuButton( skp, x );
			}
		}
		else if (menu == 4)
		{
			skp->Text( x, 972, "CST", 3 );
			DrawMenuButton( skp, x );
		}
		else DrawMenuButton( skp, x );

		// button 5
		x += 152;
		DrawMenuButton( skp, x );
		if (menu == 0)
		{
			skp->Text( x, 972, "MEDS ", 5 );
			skp->Text( x, 998, "MAINT", 5 );
		}
		else if (menu == 2)
		{
			skp->Text( x, 972, "PORT ", 5 );
			skp->Text( x, 998, "SELECT ", 7 );
		}

		// button 6
		x += 152;
		//skp->Text( x, 50, "PG", 2 );
		DrawMenuButton( skp, x );

		// print title
		switch (menu)
		{
			case 0:
				skp->Text( 452, 942, "MAIN MENU", 9 );
				break;
			case 1:
				skp->Text( 452, 942, " FLIGHT INSTRUMENT MENU", 23 );
				break;
			case 2:
				skp->Text( 452, 942, "SUBSYSTEM MENU ", 15 );
				break;
			case 3:
				skp->Text( 452, 942, "DPS MENU ", 9 );
				break;
			case 4:
				skp->Text( 452, 942, " MAINTENANCE MENU", 17 );
				break;
			case 5:
				skp->Text( 452, 942, " CST MENU SELECTION", 19 );
				break;
			case 6:
				{
					char buf[32];
					sprintf_s( buf, 32, " IDP%d INTERACTIVE CST", GetIDP()->GetIDPID() );
					skp->Text( 452, 942, buf, strlen( buf ) );
				}
				break;
			case 7:
				skp->Text( 452, 942, " MDU CONFIGURATION MENU", 23 );
				break;
			default:
				// print nothing
				break;
		}

		// print configuration info
		if (prim_idp)
		{
			char str[4];
			str[0] = 'P';
			str[1] = prim_idp->GetIDPID() + 48;
			str[2] = bUseSecondaryPort ? ' ' : '*';
			str[3] = 0;
			skp->Text( 30, 972, str, 3 );
		}

		if (sec_idp)
		{
			char str[4];
			str[0] = 'S';
			str[1] = sec_idp->GetIDPID() + 48;
			str[2] = !bUseSecondaryPort ? ' ' : '*';
			str[3] = 0;
			skp->Text( 30, 998, str, 3 );
		}
		{
			char str[4];
			str[0] = 'F';
			str[1] = 'C';
			str[2] = FC + 48;
			str[3] = 0;
			skp->Text( 994, 972, str, 3 );
		}
		if (bPortConfigMan) skp->Text( 994, 998, "MAN", 3 );
		else skp->Text( 994, 998, "AUT", 3 );

		// print MEDS fault line
		/*if (!GetFlash())
		{
			skp->SetTextColor( CR_WHITE );
			skp->Text( 452, 916, "IDP 1 2 3 4 STILL WIP", 21 );
		}*/
		return;
	}

	void MDU::DrawMenuButton( HDC hDC, int x )
	{
		MoveToEx( hDC, x - 72, 1020, NULL );
		LineTo( hDC, x - 72, 966 );
		MoveToEx( hDC, x - 72, 968, NULL );
		LineTo( hDC, x + 72, 968 );
		MoveToEx( hDC, x + 72, 966, NULL );
		LineTo( hDC, x + 72, 1020 );
		return;
	}

	void MDU::DrawMenuButton( oapi::Sketchpad* skp, int x )
	{
		skp->Line( x - 72, 1020, x - 72, 966 );
		skp->Line( x - 72, 968, x + 72, 968 );
		skp->Line( x + 72, 966, x + 72, 1020 );
		return;
	}

	bool MDU::RealizeMFD(int id)
	{
		if(id>=0) RegisterMFDContext(id);
		return false;
	}

	void MDU::RegisterMFDContext(int id)
	{
//		char pszBuffer[256];
		mfdspec.nbt1 = 5;
		mfdspec.nbt2 = 0;
		mfdspec.flag = MFD_SHOWMODELABELS;
		mfdspec.bt_yofs  = 1024/6;
		mfdspec.bt_ydist = 1024/7;
		oapiRegisterMFD (id, &mfdspec);
		//sprintf_s(pszBuffer, 256, "MFD %s (%d) registered", GetQualifiedIdentifier().c_str(), usMDUID);
		//oapiWriteLog(pszBuffer);
	}

	bool MDU::DefineVCGroup(UINT mgrp)
	{
		mfdspec.ngroup = mgrp;
		return true;
	}

	void MDU::ConnectPower( discsignals::DiscreteBundle* Bundle, const unsigned short Line )
	{
		dipPower.Connect( Bundle, Line );
		return;
	}

	unsigned short MDU::GetDrivingIDP() const
	{
		if(this->bUseSecondaryPort)
		{
			if(sec_idp)
			{
				return sec_idp->GetIDPID();
			} else {
				return 100;
			}
		} else {
			if(prim_idp)
			{
				return prim_idp->GetIDPID();
			} else {
				return 100;
			}
		}

	}

	void MDU::CreateGDIObjects()
	{
		if (!(gdiSSVAFont_h19w19rot = CreateFont( 19, 19, 0, static_cast<int>(fontrotsmall * 10), FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FIXED_PITCH, "SSV_Font_A" ))) throw std::exception( "CreateFont() failed" );
		if (!(gdiSSVAFont_h22w22rot = CreateFont( 22, 22, 0, static_cast<int>(fontrotlarge * 10), FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FIXED_PITCH, "SSV_Font_A" ))) throw std::exception( "CreateFont() failed" );

		if (gdiBlackBrush) return;// shared resources already created

		if (!(gdiBlackBrush = CreateSolidBrush( CR_BLACK ))) throw std::exception( "CreateSolidBrush() failed" );
		if (!(gdiDarkGrayBrush = CreateSolidBrush( CR_DARK_GRAY ))) throw std::exception( "CreateSolidBrush() failed" );
		if (!(gdiLightGrayBrush = CreateSolidBrush( CR_LIGHT_GRAY ))) throw std::exception( "CreateSolidBrush() failed" );
		if (!(gdiWhiteBrush = CreateSolidBrush( CR_WHITE ))) throw std::exception( "CreateSolidBrush() failed" );
		if (!(gdiRedBrush = CreateSolidBrush( CR_RED ))) throw std::exception( "CreateSolidBrush() failed" );
		if (!(gdiYellowBrush = CreateSolidBrush( CR_YELLOW ))) throw std::exception( "CreateSolidBrush() failed" );
		if (!(gdiCyanBrush = CreateSolidBrush( CR_CYAN ))) throw std::exception( "CreateSolidBrush() failed" );
		if (!(gdiMagentaBrush = CreateSolidBrush( CR_MAGENTA ))) throw std::exception( "CreateSolidBrush() failed" );
		if (!(gdiLightGreenBrush = CreateSolidBrush( CR_LIGHT_GREEN ))) throw std::exception( "CreateSolidBrush() failed" );
		if (!(gdiBlueBrush = CreateSolidBrush( CR_BLUE ))) throw std::exception( "CreateSolidBrush() failed" );

		if (!(gdiBlackPen = CreatePen( PS_SOLID, 4, CR_BLACK ))) throw std::exception( "CreatePen() failed" );
		if (!(gdiDarkGrayPen = CreatePen( PS_SOLID, 4, CR_DARK_GRAY ))) throw std::exception( "CreatePen() failed" );
		if (!(gdiLightGrayPen = CreatePen( PS_SOLID, 4, CR_LIGHT_GRAY ))) throw std::exception( "CreatePen() failed" );
		if (!(gdiLightGrayThickPen = CreatePen( PS_SOLID, 6, CR_LIGHT_GRAY ))) throw std::exception( "CreatePen() failed" );
		if (!(gdiWhitePen = CreatePen( PS_SOLID, 4, CR_WHITE ))) throw std::exception( "CreatePen() failed" );
		if (!(gdiRedPen = CreatePen( PS_SOLID, 4, CR_RED ))) throw std::exception( "CreatePen() failed" );
		if (!(gdiYellowPen = CreatePen( PS_SOLID, 4, CR_YELLOW ))) throw std::exception( "CreatePen() failed" );
		if (!(gdiCyanPen = CreatePen( PS_SOLID, 4, CR_CYAN ))) throw std::exception( "CreatePen() failed" );
		if (!(gdiMagentaPen = CreatePen( PS_SOLID, 4, CR_MAGENTA ))) throw std::exception( "CreatePen() failed" );
		if (!(gdiLightGreenPen = CreatePen( PS_SOLID, 4, CR_LIGHT_GREEN ))) throw std::exception( "CreatePen() failed" );
		if (!(gdiDarkGreenPen = CreatePen( PS_SOLID, 4, CR_DARK_GREEN ))) throw std::exception( "CreatePen() failed" );
		if (!(gdiLightGreenThickPen = CreatePen( PS_SOLID, 8, CR_LIGHT_GREEN ))) throw std::exception( "CreatePen() failed" );

		if (!(gdiNormalPen = CreatePen( PS_SOLID, 2, CR_DPS_GREEN ))) throw std::exception( "CreatePen() failed" );
		if (!(gdiOverbrightPen = CreatePen( PS_SOLID, 2, CR_YELLOW ))) throw std::exception( "CreatePen() failed" );
		LOGBRUSH lb = {BS_SOLID, CR_DPS_GREEN, 0};
		DWORD pstyle[2] = {16, 8};
		if (!(gdiDashedNormalPen = ExtCreatePen( PS_GEOMETRIC | PS_USERSTYLE, 2, &lb, 2, pstyle ))) throw std::exception( "ExtCreatePen() failed" );

		if (!(gdiSSVAFont_h40w34 = CreateFont( 40, 34, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FIXED_PITCH, "SSV_Font_A" ))) throw std::exception( "CreateFont() failed" );
		if (!(gdiSSVAFont_h19w19 = CreateFont( 19, 19, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FIXED_PITCH, "SSV_Font_A" ))) throw std::exception( "CreateFont() failed" );
		if (!(gdiSSVAFont_h22w22 = CreateFont( 22, 22, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FIXED_PITCH, "SSV_Font_A" ))) throw std::exception( "CreateFont() failed" );
		if (!(gdiSSVAFont_h19w19bold = CreateFont( 19, 19, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FIXED_PITCH, "SSV_Font_A" ))) throw std::exception( "CreateFont() failed" );
		if (!(gdiSSVAFont_h22w18 = CreateFont( 22, 18, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FIXED_PITCH, "SSV_Font_A" ))) throw std::exception( "CreateFont() failed" );
		if (!(gdiSSVBFont_h36w18 = CreateFont( 36, 18, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FIXED_PITCH, "SSV_Font_B" ))) throw std::exception( "CreateFont() failed" );
		if (!(gdiSSVBFont_h24w14 = CreateFont( 24, 14, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FIXED_PITCH, "SSV_Font_B" ))) throw std::exception( "CreateFont() failed" );
		if (!(gdiSSVBFont_h32w18 = CreateFont( 32, 18, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FIXED_PITCH, "SSV_Font_B" ))) throw std::exception( "CreateFont() failed" );
		return;
	}

	void MDU::DestroyGDIObjects()
	{
		DeleteObject( gdiSSVAFont_h19w19rot );
		DeleteObject( gdiSSVAFont_h22w22rot );

		if (!gdiBlackBrush) return;// shared resources already deleted

		DeleteObject( gdiBlackBrush );
		DeleteObject( gdiDarkGrayBrush );
		DeleteObject( gdiLightGrayBrush );
		DeleteObject( gdiWhiteBrush );
		DeleteObject( gdiRedBrush );
		DeleteObject( gdiYellowBrush );
		DeleteObject( gdiCyanBrush );
		DeleteObject( gdiMagentaBrush );
		DeleteObject( gdiLightGreenBrush );
		DeleteObject( gdiBlueBrush );

		DeleteObject( gdiBlackPen );
		DeleteObject( gdiDarkGrayPen );
		DeleteObject( gdiLightGrayPen );
		DeleteObject( gdiLightGrayThickPen );
		DeleteObject( gdiWhitePen );
		DeleteObject( gdiRedPen );
		DeleteObject( gdiYellowPen );
		DeleteObject( gdiCyanPen );
		DeleteObject( gdiMagentaPen );
		DeleteObject( gdiLightGreenPen );
		DeleteObject( gdiDarkGreenPen );
		DeleteObject( gdiLightGreenThickPen );

		DeleteObject( gdiNormalPen );
		DeleteObject( gdiDashedNormalPen );
		DeleteObject( gdiOverbrightPen );

		DeleteObject( gdiSSVAFont_h40w34 );
		DeleteObject( gdiSSVAFont_h19w19 );
		DeleteObject( gdiSSVAFont_h22w22 );
		DeleteObject( gdiSSVAFont_h19w19bold );
		DeleteObject( gdiSSVAFont_h22w18 );
		DeleteObject( gdiSSVBFont_h36w18 );
		DeleteObject( gdiSSVBFont_h24w14 );
		DeleteObject( gdiSSVBFont_h32w18 );

		gdiBlackBrush = NULL;
		return;
	}

	void MDU::CreateSketchpadObjects()
	{
		if (skpBlackBrush) return;// already created

		if (!(skpBlackBrush = oapiCreateBrush( CR_BLACK ))) throw std::exception( "oapiCreateBrush() failed" );
		if (!(skpDarkGrayBrush = oapiCreateBrush( CR_DARK_GRAY ))) throw std::exception( "oapiCreateBrush() failed" );
		if (!(skpLightGrayBrush = oapiCreateBrush( CR_LIGHT_GRAY ))) throw std::exception( "oapiCreateBrush() failed" );
		if (!(skpWhiteBrush = oapiCreateBrush( CR_WHITE ))) throw std::exception( "oapiCreateBrush() failed" );
		if (!(skpRedBrush = oapiCreateBrush( CR_RED ))) throw std::exception( "oapiCreateBrush() failed" );
		if (!(skpYellowBrush = oapiCreateBrush( CR_YELLOW ))) throw std::exception( "oapiCreateBrush() failed" );
		if (!(skpCyanBrush = oapiCreateBrush( CR_CYAN ))) throw std::exception( "oapiCreateBrush() failed" );
		if (!(skpMagentaBrush = oapiCreateBrush( CR_MAGENTA ))) throw std::exception( "oapiCreateBrush() failed" );
		if (!(skpLightGreenBrush = oapiCreateBrush( CR_LIGHT_GREEN ))) throw std::exception( "oapiCreateBrush() failed" );
		if (!(skpBlueBrush = oapiCreateBrush( CR_BLUE ))) throw std::exception( "oapiCreateBrush() failed" );
		if (!(_skpBlackBrush = oapiCreateBrush( RGB( 0, 0, 0 ) ))) throw std::exception( "oapiCreateBrush() failed" );

		if (!(skpBlackPen = oapiCreatePen( 1, 4, CR_BLACK ))) throw std::exception( "oapiCreatePen() failed" );
		if (!(skpDarkGrayPen = oapiCreatePen( 1, 4, CR_DARK_GRAY ))) throw std::exception( "oapiCreatePen() failed" );
		if (!(skpLightGrayPen = oapiCreatePen( 1, 4, CR_LIGHT_GRAY ))) throw std::exception( "oapiCreatePen() failed" );
		if (!(skpLightGrayThickPen = oapiCreatePen( 1, 6, CR_LIGHT_GRAY ))) throw std::exception( "oapiCreatePen() failed" );
		if (!(skpWhitePen = oapiCreatePen( 1, 4, CR_WHITE ))) throw std::exception( "oapiCreatePen() failed" );
		if (!(skpRedPen = oapiCreatePen( 1, 4, CR_RED ))) throw std::exception( "oapiCreatePen() failed" );
		if (!(skpYellowPen = oapiCreatePen( 1, 4, CR_YELLOW ))) throw std::exception( "oapiCreatePen() failed" );
		if (!(skpCyanPen = oapiCreatePen( 1, 4, CR_CYAN ))) throw std::exception( "oapiCreatePen() failed" );
		if (!(skpMagentaPen = oapiCreatePen( 1, 4, CR_MAGENTA ))) throw std::exception( "oapiCreatePen() failed" );
		if (!(skpLightGreenPen = oapiCreatePen( 1, 4, CR_LIGHT_GREEN ))) throw std::exception( "oapiCreatePen() failed" );
		if (!(skpDarkGreenPen = oapiCreatePen( 1, 4, CR_DARK_GREEN ))) throw std::exception( "oapiCreatePen() failed" );
		if (!(skpLightGreenThickPen = oapiCreatePen( 1, 8, CR_LIGHT_GREEN ))) throw std::exception( "oapiCreatePen() failed" );
		if (!(_skpBlackPen = oapiCreatePen( 1, 4, RGB( 0, 0, 0 ) ))) throw std::exception( "oapiCreatePen() failed" );

		if (!(skpNormalPen = oapiCreatePen( 1, 2, CR_DPS_GREEN ))) throw std::exception( "oapiCreatePen() failed" );
		if (!(skpDashedNormalPen = oapiCreatePen( 2, 2, CR_DPS_GREEN ))) throw std::exception( "oapiCreatePen() failed" );
		if (!(skpOverbrightPen = oapiCreatePen( 1, 2, CR_YELLOW ))) throw std::exception( "oapiCreatePen() failed" );

		if (!(skpSSVAFont_h40w34 = oapiCreateFontEx( 40, "SSV_Font_A", 34, FW_MEDIUM, FontStyle::FONT_NORMAL, 0.0f ))) throw std::exception( "oapiCreateFontEx() failed" );
		if (!(skpSSVAFont_h19w19 = oapiCreateFontEx( 19, "SSV_Font_A", 19, FW_MEDIUM, FontStyle::FONT_NORMAL, 0.0f ))) throw std::exception( "oapiCreateFontEx() failed" );
		if (!(skpSSVAFont_h22w22 = oapiCreateFontEx( 22, "SSV_Font_A", 22, FW_MEDIUM, FontStyle::FONT_NORMAL, 0.0f ))) throw std::exception( "oapiCreateFontEx() failed" );
		if (!(skpSSVAFont_h19w19bold = oapiCreateFontEx( 19, "SSV_Font_A", 19, FW_BOLD, FontStyle::FONT_NORMAL, 0.0f ))) throw std::exception( "oapiCreateFontEx() failed" );
		if (!(skpSSVAFont_h22w18 = oapiCreateFontEx( 22, "SSV_Font_A", 18, FW_MEDIUM, FontStyle::FONT_NORMAL, 0.0f ))) throw std::exception( "oapiCreateFontEx() failed" );
		if (!(skpSSVBFont_h36w18 = oapiCreateFontEx( 36, "SSV_Font_B", 18, FW_MEDIUM, FontStyle::FONT_NORMAL, 0.0f ))) throw std::exception( "oapiCreateFontEx() failed" );
		if (!(skpSSVBFont_h24w14 = oapiCreateFontEx( 24, "SSV_Font_B", 14, FW_MEDIUM, FontStyle::FONT_NORMAL, 0.0f ))) throw std::exception( "oapiCreateFontEx() failed" );
		if (!(skpSSVBFont_h32w18 = oapiCreateFontEx( 32, "SSV_Font_B", 12, FW_MEDIUM, FontStyle::FONT_NORMAL, 0.0f ))) throw std::exception( "oapiCreateFontEx() failed" );
		return;
	}

	void MDU::DestroySketchpadObjects()
	{
		if (!skpBlackBrush) return;// already deleted

		oapiReleaseBrush( skpBlackBrush );
		oapiReleaseBrush( skpDarkGrayBrush );
		oapiReleaseBrush( skpLightGrayBrush );
		oapiReleaseBrush( skpWhiteBrush );
		oapiReleaseBrush( skpRedBrush );
		oapiReleaseBrush( skpYellowBrush );
		oapiReleaseBrush( skpCyanBrush );
		oapiReleaseBrush( skpMagentaBrush );
		oapiReleaseBrush( skpLightGreenBrush );
		oapiReleaseBrush( skpBlueBrush );
		oapiReleaseBrush( _skpBlackBrush );

		oapiReleasePen( skpBlackPen );
		oapiReleasePen( skpDarkGrayPen );
		oapiReleasePen( skpLightGrayPen );
		oapiReleasePen( skpLightGrayThickPen );
		oapiReleasePen( skpWhitePen );
		oapiReleasePen( skpRedPen );
		oapiReleasePen( skpYellowPen );
		oapiReleasePen( skpCyanPen );
		oapiReleasePen( skpMagentaPen );
		oapiReleasePen( skpLightGreenPen );
		oapiReleasePen( skpDarkGreenPen );
		oapiReleasePen( skpLightGreenThickPen );
		oapiReleasePen( _skpBlackPen );

		oapiReleasePen( skpNormalPen );
		oapiReleasePen( skpDashedNormalPen );
		oapiReleasePen( skpOverbrightPen );

		oapiReleaseFont( skpSSVAFont_h40w34 );
		oapiReleaseFont( skpSSVAFont_h19w19 );
		oapiReleaseFont( skpSSVAFont_h22w22);
		oapiReleaseFont( skpSSVAFont_h19w19bold );
		oapiReleaseFont( skpSSVAFont_h22w18 );
		oapiReleaseFont( skpSSVBFont_h36w18 );
		oapiReleaseFont( skpSSVBFont_h24w14 );
		oapiReleaseFont( skpSSVBFont_h32w18 );

		skpBlackBrush = NULL;
		return;
	}

	void MDU::Rx( const BUS_ID id, void* data, const unsigned short datalen )
	{
		if (!dipPower.IsSet()) return;

		unsigned int* rcvd = static_cast<unsigned int*>(data);

		//// process command word
		{
			// check addr
			int dataaddr = (rcvd[0] >> 12) & 0b11111;
			if (MDU_1553_ADDR[usMDUID - 1] != dataaddr) return;
		}

		// check parity
		if (CalcParity( rcvd[0] ) == 0) return;


		unsigned short TR = (rcvd[0] >> 11) & 0b1;
		if (TR == 1)
		{
			// TODO transmit
		}
		else
		{
			// TODO receive
		}
		return;
	}
}

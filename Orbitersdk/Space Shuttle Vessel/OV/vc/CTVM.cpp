#include "CTVM.h"
#include "..\Atlantis.h"
#include "..\VideoControlUnit.h"
#include <Sketchpad2.h>


namespace vc
{
	constexpr int TOPLINE_Y = static_cast<int>(IMAGE_SIZE * 0.17);// [px]
	constexpr int BOTTOMLINE_Y = static_cast<int>(IMAGE_SIZE * 0.77);// [px]

	constexpr int ZOOMLABEL_X = static_cast<int>(IMAGE_SIZE * 0.15);// [px]
	constexpr int PANLABEL_X = static_cast<int>(IMAGE_SIZE * 0.11);// [px]
	constexpr int TILTLABEL_X = static_cast<int>(IMAGE_SIZE * 0.33);// [px]
	constexpr int NAMELABEL_X = static_cast<int>(IMAGE_SIZE * 0.85);// [px]

	constexpr int CROSSHAIR_LENGHT = 20;// [px]

	#define CR_LIGHT_GREEN RGB( 0, 255, 0 )

	static oapi::Pen* skpLightGreenPen = NULL;
	static oapi::Font* skpFont = NULL;


	CTVM::CTVM( unsigned short id, Atlantis* _sts, const string& _ident ):AtlantisVCComponent( _sts, _ident ),
		id(id), power(false),
		pPower(NULL), pFunction(NULL), pSelect(NULL), anim_power(NULL), anim_function(NULL), anim_select(NULL)
	{
		if (STS()->D3D9())
		{
			if (!(hSurf = oapiCreateSurfaceEx( IMAGE_SIZE, IMAGE_SIZE, OAPISURFACE_RENDER3D | OAPISURFACE_TEXTURE | OAPISURFACE_RENDERTARGET | OAPISURFACE_NOMIPMAPS ))) throw std::exception( "oapiCreateSurfaceEx() failed" );
			
			if (!skpLightGreenPen)
				if (!(skpLightGreenPen = oapiCreatePen( 1, 3, CR_LIGHT_GREEN ))) throw std::exception( "oapiCreatePen() failed" );
			if (!skpFont)
				if (!(skpFont = STS()->D3D9()->CreateSketchpadFont( 34, "Sans", 14, FW_BOLD, 0, 0.0f ))) throw std::exception( "CreateSketchpadFont() failed" );
		}
		else
		{
			hSurf = NULL;
		}
		return;
	}

	CTVM::~CTVM( void )
	{
		if (skpLightGreenPen)
		{
			oapiReleasePen( skpLightGreenPen );
			skpLightGreenPen = NULL;
		}
		if (skpFont)
		{
			oapiReleaseFont( skpFont );
			skpFont = NULL;
		}

		if (pPower) delete pPower;
		if (pFunction) delete pFunction;
		if (pSelect) delete pSelect;
		if (hSurf) oapiDestroySurface( hSurf );
		return;
	}

	void CTVM::SetReferences( const VECTOR3& refPower, const VECTOR3& refFunction )
	{
		this->refPower = refPower;
		this->refFunction = refFunction;
		return;
	}

	void CTVM::SetDirections( const VECTOR3& dirPower, const VECTOR3& dirFunction, const VECTOR3& dirSelect )
	{
		this->dirPower = dirPower;
		this->dirFunction = dirFunction;
		this->dirSelect = dirSelect;
		return;
	}

	void CTVM::SetGroups( UINT grpPower, UINT grpFunction, UINT grpSelect )
	{
		this->grpPower = grpPower;
		this->grpFunction = grpFunction;
		this->grpSelect = grpSelect;
		return;
	}

	void CTVM::DefineVCAnimations( UINT vc_idx )
	{
		pPower = new MGROUP_ROTATE( vc_idx, &grpPower, 1, refPower, dirPower, static_cast<float>(66.0 * RAD) );
		anim_power = STS()->CreateAnimation( 0.5 );
		STS()->AddAnimationComponent( anim_power, 0.0, 1.0, pPower, NULL );
		OnPowerChange();

		pFunction = new MGROUP_ROTATE( vc_idx, &grpFunction, 1, refFunction, dirFunction, static_cast<float>(66.0 * RAD) );
		anim_function = STS()->CreateAnimation( 0.5 );
		STS()->AddAnimationComponent( anim_function, 0.0, 1.0, pFunction, NULL );

		pSelect = new MGROUP_TRANSLATE( vc_idx, &grpSelect, 1, dirSelect * 0.005 );
		anim_select = STS()->CreateAnimation( 1.0 );
		STS()->AddAnimationComponent( anim_select, 0.0, 1.0, pSelect, NULL );
		return;
	}

	bool CTVM::OnMouseEvent( int _event, float x, float y )
	{
		constexpr float power_x_min = 0.21f;
		constexpr float power_x_max = 0.36f;
		constexpr float power_y_min = 0.12f;
		constexpr float power_y_max = 0.22f;

		if (_event & PANEL_MOUSE_LBDOWN)
		{
			if ((x > power_x_min) && (x < power_x_max))
			{
				if ((y > power_y_min) && (y < (power_y_min + 0.4 * (power_y_max - power_y_min))))
				{
					// on
					OnPowerOn();
					return true;
				}
				else if ((y < power_y_max) && (y > (power_y_max - 0.4 * (power_y_max - power_y_min))))
				{
					// off
					OnPowerOff();
					return true;
				}
			}
		}
		// TODO function
		// TODO select
		return false;
	}

	void CTVM::OnPowerOn( void )
	{
		power = true;
		OnPowerChange();
		return;
	}

	void CTVM::OnPowerOff( void )
	{
		power = false;
		OnPowerChange();
		return;
	}

	void CTVM::OnPowerChange( void )
	{
		STS()->SetAnimation( anim_power, power ? 1.0 : 0.0 );
		return;
	}

	bool CTVM::OnReadState( FILEHANDLE scn )
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
				if (!_strnicmp( line + 6, "ON", 2 )) power = true;
			}
		}
		return false;
	}

	void CTVM::OnSaveState( FILEHANDLE scn ) const
	{
		oapiWriteScenario_string( scn, "POWER", power ? "ON" : "OFF" );
		return;
	}

	void CTVM::OnPreStep( double simt, double simdt, double mjd )
	{
		// only works in D3D9
		if (!STS()->D3D9()) return;

		// TODO handle menu and config

		if (power)
		{
			std::string name = "";
			double pan = 0.0;
			double tilt = 0.0;
			double zoom = 0.0;
			char cbuf[32];

			// get image
			STS()->GetVCU()->GetMonitorImage( id, hSurf, name, pan, tilt, zoom );

			// TODO if camera info on -> draw it in surface
			oapi::Sketchpad* skp = oapiGetSketchpad( hSurf );
			
			skp->SetTextColor( CR_LIGHT_GREEN );
			skp->SetFont( skpFont );
			skp->SetPen( skpLightGreenPen );

			//// top line ////
			// zoom
			sprintf_s( cbuf, 32, "%04.1f ºFOV", zoom );
			skp->Text( ZOOMLABEL_X, TOPLINE_Y, cbuf, strlen( cbuf ) );

			//// top line ////
			// pan
			sprintf_s( cbuf, 32, "%+06.1fP", pan );
			skp->Text( PANLABEL_X, BOTTOMLINE_Y, cbuf, strlen( cbuf ) );
			// tilt
			sprintf_s( cbuf, 32, "%+06.1fT", tilt );
			skp->Text( TILTLABEL_X, BOTTOMLINE_Y, cbuf, strlen( cbuf ) );
			// name
			skp->Text( NAMELABEL_X, BOTTOMLINE_Y, name.c_str(), name.length() );

			//// crosshairs ////
			skp->Line( IMAGE_SIZE2, IMAGE_SIZE2 - CROSSHAIR_LENGHT, IMAGE_SIZE2, IMAGE_SIZE2 + CROSSHAIR_LENGHT );// center V
			skp->Line( IMAGE_SIZE2 - CROSSHAIR_LENGHT, IMAGE_SIZE2, IMAGE_SIZE2 + CROSSHAIR_LENGHT, IMAGE_SIZE2 );// center H
			skp->Line( 0, IMAGE_SIZE2, CROSSHAIR_LENGHT, IMAGE_SIZE2 );// left
			skp->Line( IMAGE_SIZE - CROSSHAIR_LENGHT, IMAGE_SIZE2, IMAGE_SIZE, IMAGE_SIZE2 );// right
			skp->Line( IMAGE_SIZE2, IMAGE_SIZE / 8, IMAGE_SIZE2, (IMAGE_SIZE / 8) + CROSSHAIR_LENGHT );// top
			skp->Line( IMAGE_SIZE2, IMAGE_SIZE - (IMAGE_SIZE / 8) - CROSSHAIR_LENGHT, IMAGE_SIZE2, IMAGE_SIZE );// bottom

			oapiReleaseSketchpad( skp );
		}
		return;
	}

	SURFHANDLE CTVM::GetMonitorSurf( void ) const
	{
		return hSurf;
	}
};

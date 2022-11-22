#include "CTVM.h"
#include "..\Atlantis.h"
#include "..\VideoControlUnit.h"
#include <Sketchpad2.h>


namespace vc
{
	constexpr int MENUTOP_NAME_Y = static_cast<int>(IMAGE_SIZE * 0.13);// [px]
	constexpr int MENUTOP_OPTION_Y = static_cast<int>(IMAGE_SIZE * 0.155);// [px]

	constexpr int MENUTOP_X[3] = {static_cast<int>(IMAGE_SIZE * 0.15), static_cast<int>(IMAGE_SIZE * 0.275), static_cast<int>(IMAGE_SIZE * 0.4)};// [px]

	constexpr int MENU_SELECT_LINE_OFFSET_X1 = static_cast<int>(IMAGE_SIZE * 0.06);// [px]
	constexpr int MENU_SELECT_LINE_OFFSET_X2 = static_cast<int>(IMAGE_SIZE * 0.05);// [px]
	constexpr int MENU_SELECT_LINE_OFFSET_Y1 = static_cast<int>(IMAGE_SIZE * 0.01);// [px]
	constexpr int MENU_SELECT_LINE_OFFSET_Y2 = static_cast<int>(IMAGE_SIZE * 0.02);// [px]


	constexpr int TOPLINE_Y = static_cast<int>(IMAGE_SIZE * 0.17);// [px]
	constexpr int BOTTOMLINE_Y = static_cast<int>(IMAGE_SIZE * 0.77);// [px]

	constexpr int ZOOMLABEL_X = static_cast<int>(IMAGE_SIZE * 0.15);// [px]
	constexpr int PANLABEL_X = static_cast<int>(IMAGE_SIZE * 0.11);// [px]
	constexpr int TILTLABEL_X = static_cast<int>(IMAGE_SIZE * 0.33);// [px]
	constexpr int NAMELABEL_X = static_cast<int>(IMAGE_SIZE * 0.85);// [px]

	constexpr int CROSSHAIR_LENGHT = 20;// [px]

	constexpr double MENU_DISPLAY_TIME = 10.0;// time menu stays visible after last input [s]

	char* MENU_HEADINGS[3] = {"L-DATA", "C-DATA", "XHAIR"};
	constexpr unsigned int MENU_OPTIONS_MAX_IDX[3] = {1, 2, 1};
	char* MENU_OPTIONS[3][3] = {{"OFF", "ON", ""},
				{"OFF", "GRN", "WHT"},
				{"OFF", "ON", ""}};

	#define CR_LIGHT_GREEN RGB( 0, 255, 0 )

	static oapi::Pen* skpThickLightGreenPen = NULL;
	static oapi::Pen* skpThinLightGreenPen = NULL;
	static oapi::Font* skpFontData = NULL;
	static oapi::Font* skpFontMenu = NULL;


	CTVM::CTVM( unsigned short id, Atlantis* _sts, const string& _ident ):AtlantisVCComponent( _sts, _ident ),
		id(id), menuoptions{0,0,0}, menuselect(0), power(false), menu(false), selectpressed(false), functionleft(false), functionright(false), menutime(0.0),
		pPower(NULL), pFunction(NULL), pSelect(NULL), anim_power(NULL), anim_function(NULL), anim_select(NULL)
	{
		if (STS()->D3D9())
		{
			if (!(hSurf = oapiCreateSurfaceEx( IMAGE_SIZE, IMAGE_SIZE, OAPISURFACE_RENDER3D | OAPISURFACE_TEXTURE | OAPISURFACE_RENDERTARGET | OAPISURFACE_NOMIPMAPS ))) throw std::exception( "oapiCreateSurfaceEx() failed" );
			
			if (!skpThickLightGreenPen)
				if (!(skpThickLightGreenPen = oapiCreatePen( 1, 3, CR_LIGHT_GREEN ))) throw std::exception( "oapiCreatePen() failed" );
			if (!skpThinLightGreenPen)
				if (!(skpThinLightGreenPen = oapiCreatePen( 1, 1, CR_LIGHT_GREEN ))) throw std::exception( "oapiCreatePen() failed" );
			if (!skpFontData)
				if (!(skpFontData = STS()->D3D9()->CreateSketchpadFont( 34, "Sans", 14, FW_BOLD, 0, 0.0f ))) throw std::exception( "CreateSketchpadFont() failed" );
			if (!skpFontMenu)
				if (!(skpFontMenu = STS()->D3D9()->CreateSketchpadFont( 17, "Sans", 7, FW_BOLD, 0, 0.0f ))) throw std::exception( "CreateSketchpadFont() failed" );}
		else
		{
			hSurf = NULL;
		}
		return;
	}

	CTVM::~CTVM( void )
	{
		if (skpThickLightGreenPen)
		{
			oapiReleasePen( skpThickLightGreenPen );
			skpThickLightGreenPen = NULL;
		}
		if (skpThinLightGreenPen)
		{
			oapiReleasePen( skpThinLightGreenPen );
			skpThinLightGreenPen = NULL;
		}
		if (skpFontData)
		{
			oapiReleaseFont( skpFontData );
			skpFontData = NULL;
		}
		if (skpFontMenu)
		{
			oapiReleaseFont( skpFontMenu );
			skpFontMenu = NULL;
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

		pSelect = new MGROUP_TRANSLATE( vc_idx, &grpSelect, 1, dirSelect * 0.0025 );
		anim_select = STS()->CreateAnimation( 0.0 );
		STS()->AddAnimationComponent( anim_select, 0.0, 1.0, pSelect, NULL );
		return;
	}

	bool CTVM::OnMouseEvent( int _event, float x, float y )
	{
		constexpr float power_x_min = 0.2036f;
		constexpr float power_x_max = 0.3671f;
		constexpr float power_y_min = 0.1467f;
		constexpr float power_y_max = 0.2495f;

		constexpr float select_x_min = 0.1774f;
		constexpr float select_x_max = 0.4237f;
		constexpr float select_y_min = 0.3321f;
		constexpr float select_y_max = 0.4129f;

		constexpr float function_x_min = 0.3274f;
		constexpr float function_x_max = 0.6402f;
		constexpr float function_y_min = 0.4610f;
		constexpr float function_y_max = 0.5148f;

		// power
		if ((x > power_x_min) && (x < power_x_max))
		{
			if ((y > power_y_min) && (y < (power_y_min + 0.4 * (power_y_max - power_y_min))))
			{
				// on
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnPowerOn();
					return true;
				}
			}
			else if ((y < power_y_max) && (y > (power_y_max - 0.4 * (power_y_max - power_y_min))))
			{
				// off
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnPowerOff();
					return true;
				}
			}
		}
		// select
		if ((x > select_x_min) && (x < select_x_max))
		{
			if ((y > select_y_min) && (y < select_y_max))
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnSelectPress();
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnSelectDepress();
					return true;
				}
			}
		}
		// function
		if ((y > function_y_min) && (y < function_y_max))
		{
			if ((x > function_x_min) && (x < (function_x_min + 0.4 * (function_x_max - function_x_min))))
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnFunctionLeft();
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnFunctionCenter();
					return true;
				}
			}
			else if ((x < function_x_max) && (x > (function_x_max - 0.4 * (function_x_max - function_x_min))))
			{
				if (_event & PANEL_MOUSE_LBDOWN)
				{
					OnFunctionRight();
					return true;
				}
				else if (_event & PANEL_MOUSE_LBUP)
				{
					OnFunctionCenter();
					return true;
				}
			}
		}
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

	void CTVM::OnSelectPress( void )
	{
		selectpressed = true;
		STS()->SetAnimation( anim_select, 1.0 );
		return;
	}

	void CTVM::OnSelectDepress( void )
	{
		STS()->SetAnimation( anim_select, 0.0 );
		return;
	}

	void CTVM::OnFunctionLeft( void )
	{
		functionleft = true;
		STS()->SetAnimation( anim_function, 1.0 );
		return;
	}

	void CTVM::OnFunctionCenter( void )
	{
		STS()->SetAnimation( anim_function, 0.5 );
		return;
	}

	void CTVM::OnFunctionRight( void )
	{
		functionright = true;
		STS()->SetAnimation( anim_function, 0.0 );
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
			else if (!_strnicmp( line, "L-DATA", 6 ))
			{
				sscanf_s( (char*)(line + 7), "%hu", &menuoptions[0] );
				if (menuoptions[0] > MENU_OPTIONS_MAX_IDX[0]) menuoptions[0] = MENU_OPTIONS_MAX_IDX[0];
			}
			else if (!_strnicmp( line, "C-DATA", 6 ))
			{
				sscanf_s( (char*)(line + 7), "%hu", &menuoptions[1] );
				if (menuoptions[1] > MENU_OPTIONS_MAX_IDX[1]) menuoptions[1] = MENU_OPTIONS_MAX_IDX[1];
			}
			else if (!_strnicmp( line, "XHAIR", 5 ))
			{
				sscanf_s( (char*)(line + 6), "%hu", &menuoptions[2] );
				if (menuoptions[2] > MENU_OPTIONS_MAX_IDX[2]) menuoptions[2] = MENU_OPTIONS_MAX_IDX[2];
			}
		}
		return false;
	}

	void CTVM::OnSaveState( FILEHANDLE scn ) const
	{
		oapiWriteScenario_string( scn, "POWER", power ? "ON" : "OFF" );
		oapiWriteScenario_int( scn, "L-DATA", menuoptions[0] );
		oapiWriteScenario_int( scn, "C-DATA", menuoptions[1] );
		oapiWriteScenario_int( scn, "XHAIR", menuoptions[2] );
		return;
	}

	void CTVM::OnPreStep( double simt, double simdt, double mjd )
	{
		// only works in D3D9
		if (!STS()->D3D9()) return;

		if (!power) return;

		// handle menu visibility and config
		if (selectpressed || functionleft || functionright)
		{
			// set timer of menu off
			menutime = simt + MENU_DISPLAY_TIME;

			// accept inputs if menu already on
			if (menu)
			{
				if (selectpressed)
				{
					if (menuoptions[menuselect] == MENU_OPTIONS_MAX_IDX[menuselect]) menuoptions[menuselect] = 0;
					else menuoptions[menuselect]++;
				}
				else if (functionleft)
				{
					if (menuselect == 0) menuselect = 2;
					else menuselect--;
				}
				else if (functionright)
				{
					if (menuselect == 2) menuselect = 0;
					else menuselect++;
				}
			}
			else
			{
				// show menu
				menu = true;
			}
			selectpressed = false;
			functionleft = false;
			functionright = false;
		}
		else if (menu)
		{
			if (menutime <= simt)
			{
				menu = false;
			}
		}

		// draw on image
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

		// menu
		if (menu)
		{
			skp->SetTextAlign( oapi::Sketchpad::TAlign_horizontal::CENTER );
			skp->SetFont( skpFontMenu );
			skp->SetPen( skpThinLightGreenPen );
			for (int i = 0; i < 3; i++)
			{
				skp->Text( MENUTOP_X[i], MENUTOP_NAME_Y, MENU_HEADINGS[i], strlen( MENU_HEADINGS[i] ) );
				skp->Text( MENUTOP_X[i], MENUTOP_OPTION_Y, MENU_OPTIONS[i][menuoptions[i]], strlen( MENU_OPTIONS[i][menuoptions[i]] ) );
			}

			skp->Line( MENUTOP_X[menuselect] + MENU_SELECT_LINE_OFFSET_X1, MENUTOP_NAME_Y + MENU_SELECT_LINE_OFFSET_Y1, MENUTOP_X[menuselect] + MENU_SELECT_LINE_OFFSET_X2, MENUTOP_NAME_Y + MENU_SELECT_LINE_OFFSET_Y1 );
			skp->Line( MENUTOP_X[menuselect] - MENU_SELECT_LINE_OFFSET_X1, MENUTOP_NAME_Y + MENU_SELECT_LINE_OFFSET_Y1, MENUTOP_X[menuselect] - MENU_SELECT_LINE_OFFSET_X2, MENUTOP_NAME_Y + MENU_SELECT_LINE_OFFSET_Y1 );
			skp->Line( MENUTOP_X[menuselect] + MENU_SELECT_LINE_OFFSET_X1, MENUTOP_NAME_Y + MENU_SELECT_LINE_OFFSET_Y1, MENUTOP_X[menuselect] + MENU_SELECT_LINE_OFFSET_X1, MENUTOP_NAME_Y + MENU_SELECT_LINE_OFFSET_Y2 );
			skp->Line( MENUTOP_X[menuselect] - MENU_SELECT_LINE_OFFSET_X1, MENUTOP_NAME_Y + MENU_SELECT_LINE_OFFSET_Y1, MENUTOP_X[menuselect] - MENU_SELECT_LINE_OFFSET_X1, MENUTOP_NAME_Y + MENU_SELECT_LINE_OFFSET_Y2 );
		}

		skp->SetTextAlign( oapi::Sketchpad::TAlign_horizontal::LEFT );
		skp->SetFont( skpFontData );
		skp->SetPen( skpThickLightGreenPen );

		//// lens data ////
		if (menuoptions[0] == 1)
		{
			// zoom
			sprintf_s( cbuf, 32, "%04.1f ºFOV", zoom );
			skp->Text( ZOOMLABEL_X, TOPLINE_Y, cbuf, strlen( cbuf ) );
		}

		//// camera data ////
		if (menuoptions[1] == 1)
		{
			// pan
			sprintf_s( cbuf, 32, "%+06.1fP", pan );
			skp->Text( PANLABEL_X, BOTTOMLINE_Y, cbuf, strlen( cbuf ) );
			// tilt
			sprintf_s( cbuf, 32, "%+06.1fT", tilt );
			skp->Text( TILTLABEL_X, BOTTOMLINE_Y, cbuf, strlen( cbuf ) );
			// name
			skp->Text( NAMELABEL_X, BOTTOMLINE_Y, name.c_str(), name.length() );
		}

		//// crosshairs ////
		if (menuoptions[2] == 1)
		{
			skp->Line( IMAGE_SIZE2, IMAGE_SIZE2 - CROSSHAIR_LENGHT, IMAGE_SIZE2, IMAGE_SIZE2 + CROSSHAIR_LENGHT );// center V
			skp->Line( IMAGE_SIZE2 - CROSSHAIR_LENGHT, IMAGE_SIZE2, IMAGE_SIZE2 + CROSSHAIR_LENGHT, IMAGE_SIZE2 );// center H
			skp->Line( 0, IMAGE_SIZE2, CROSSHAIR_LENGHT, IMAGE_SIZE2 );// left
			skp->Line( IMAGE_SIZE - CROSSHAIR_LENGHT, IMAGE_SIZE2, IMAGE_SIZE, IMAGE_SIZE2 );// right
			skp->Line( IMAGE_SIZE2, IMAGE_SIZE / 8, IMAGE_SIZE2, (IMAGE_SIZE / 8) + CROSSHAIR_LENGHT );// top
			skp->Line( IMAGE_SIZE2, IMAGE_SIZE - (IMAGE_SIZE / 8) - CROSSHAIR_LENGHT, IMAGE_SIZE2, IMAGE_SIZE );// bottom
		}

		oapiReleaseSketchpad( skp );
		return;
	}

	SURFHANDLE CTVM::GetMonitorSurf( void ) const
	{
		return hSurf;
	}
};

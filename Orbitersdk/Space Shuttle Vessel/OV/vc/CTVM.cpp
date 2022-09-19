#include "CTVM.h"
#include "..\Atlantis.h"
#include "..\VideoControlUnit.h"
#include <Sketchpad2.h>


namespace vc
{
	CTVM::CTVM( unsigned short id, Atlantis* _sts, const string& _ident ):AtlantisVCComponent( _sts, _ident ),
		id(id), power(false),
		pPower(NULL), pFunction(NULL), pSelect(NULL), anim_power(NULL), anim_function(NULL), anim_select(NULL)
	{
		if (STS()->D3D9())
		{
			hSurf = oapiCreateSurfaceEx( IMAGE_WIDTH, IMAGE_HEIGHT, OAPISURFACE_RENDER3D | OAPISURFACE_TEXTURE | OAPISURFACE_RENDERTARGET | OAPISURFACE_NOMIPMAPS );
		}
		else
		{
			hSurf = NULL;
		}
		return;
	}

	CTVM::~CTVM( void )
	{
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
			std::string name;
			double pan;
			double tilt;
			double zoom;

			// get image
			STS()->GetVCU()->GetMonitorImage( id, hSurf, name, pan, tilt, zoom );

			// TODO if camera info on -> draw it in surface
			oapi::Sketchpad* skp = oapiGetSketchpad( hSurf );
			skp->SetTextColor( 0x00FF00 );
			skp->Text( 450, 450, name.c_str(), name.length() );
			oapiReleaseSketchpad( skp );
		}
		return;
	}

	SURFHANDLE CTVM::GetMonitorSurf( void ) const
	{
		return hSurf;
	}
};

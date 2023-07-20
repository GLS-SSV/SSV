/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/04/07   GLS
2020/06/20   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/06/04   GLS
********************************************/
#include "THC_SOP.h"
#include "THC_RM.h"
#include <cassert>


namespace dps
{
	THC_SOP::THC_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "THC_SOP" )
	{
		THC_X = 0;
		THC_Y = 0;
		THC_Z = 0;
		return;
	}

	THC_SOP::~THC_SOP( void )
	{
		return;
	}

	void THC_SOP::Realize( void )
	{
		pTHC_RM = dynamic_cast<THC_RM*>(FindSoftware( "THC_RM" ));
		assert( (pTHC_RM != NULL) && "THC_SOP::Realize.pTHC_RM" );
		return;
	}

	void THC_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		unsigned int MM = GetMajorMode();
		if ((MM == 201) || (MM == 202) || (MM == 801))
		{
			// left and aft
			bool L_pX = false;
			bool L_mX = false;
			bool L_pY = false;
			bool L_mY = false;
			bool L_pZ = false;
			bool L_mZ = false;

			bool A_pX = false;
			bool A_mX = false;
			bool A_pY = false;
			bool A_mY = false;
			bool A_pZ = false;
			bool A_mZ = false;

			pTHC_RM->GetTHCData_L( L_pX, L_mX, L_pY, L_mY, L_pZ, L_mZ );
			pTHC_RM->GetTHCData_A( A_pX, A_mX, A_pY, A_mY, A_pZ, A_mZ );

			// aft sense logic
			if (ReadCOMPOOL_IS( SCP_SENSE_SWITCH ) == 0)
			{
				// -Z
				bool tmp_pX = A_pX;
				bool tmp_mX = A_mX;
				A_pX = A_mY;
				A_mX = A_pY;
				A_pY = A_pZ;
				A_mY = A_mZ;
				A_pZ = tmp_mX;
				A_mZ = tmp_pX;
			}
			else
			{
				// -X
				bool tmp_pX = A_pX;
				bool tmp_pY = A_pY;
				bool tmp_mY = A_mY;
				A_pX = A_mX;
				A_mX = tmp_pX;
				A_pY = A_pZ;
				A_mY = A_mZ;
				A_pZ = tmp_pY;
				A_mZ = tmp_mY;
			}

			THC_X = (int)(L_pX || A_pX) - (int)(L_mX || A_mX);
			THC_Y = (int)(L_pY || A_pY) - (int)(L_mY || A_mY);
			THC_Z = (int)(L_pZ || A_pZ) - (int)(L_mZ || A_mZ);
		}
		else
		{
			// left
			bool L_pX = false;
			bool L_mX = false;
			bool L_pY = false;
			bool L_mY = false;
			bool L_pZ = false;
			bool L_mZ = false;

			pTHC_RM->GetTHCData_L( L_pX, L_mX, L_pY, L_mY, L_pZ, L_mZ );

			THC_X = (int)L_pX - (int)L_mX;
			THC_Y = (int)L_pY - (int)L_mY;
			THC_Z = (int)L_pZ - (int)L_mZ;
		}
		return;
	}

	bool THC_SOP::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void THC_SOP::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	bool THC_SOP::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 103:
			case 104:
			case 105:
			case 106:
			case 201:
			case 202:
			case 301:
			case 302:
			case 303:
			case 601:
			case 801:
				return true;
			default:
				return false;
		}
	}

	int THC_SOP::GetXCommand( void ) const
	{
		return THC_X;
	}

	int THC_SOP::GetYCommand( void ) const
	{
		return THC_Y;
	}

	int THC_SOP::GetZCommand( void ) const
	{
		return THC_Z;
	}
}
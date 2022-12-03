/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/04/07   GLS
2020/04/08   GLS
2020/05/10   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/09/29   GLS
2022/12/01   indy91
********************************************/
#include "MPS_ATVC_CMD_SOP.h"
#include "../Atlantis.h"
#include <MathSSV.h>
#include <cassert>


namespace dps
{
	MPS_ATVC_CMD_SOP::MPS_ATVC_CMD_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "MPS_ATVC_CMD_SOP" )
	{
		Ppos[0] = 0.0;
		Ppos[1] = 0.0;
		Ppos[2] = 0.0;
		Ypos[0] = 0.0;
		Ypos[1] = 0.0;
		Ypos[2] = 0.0;
		return;
	}

	MPS_ATVC_CMD_SOP::~MPS_ATVC_CMD_SOP( void )
	{
		return;
	}

	void MPS_ATVC_CMD_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		if (GetMajorMode() == 304)
		{
			if (ReadCOMPOOL_SS( SCP_VE ) < 8000.0)
			{
				Ppos[0] = ENTRYSTOWCHUTECONFIG_1P;
				Ppos[1] = ENTRYSTOWCHUTECONFIG_2P;
				Ppos[2] = ENTRYSTOWCHUTECONFIG_3P;
				Ypos[0] = ENTRYSTOWCHUTECONFIG_1Y;
				Ypos[1] = ENTRYSTOWCHUTECONFIG_2Y;
				Ypos[2] = ENTRYSTOWCHUTECONFIG_3Y;
			}
		}

		// TODO check for nozzle collision
		// TODO position limit
		for (int i = 0; i < 3; i++)
		{
			dopPpos[i].SetLine( static_cast<float>(Ppos[i]) );
			dopYpos[i].SetLine( static_cast<float>(Ypos[i]) );
		}
		//sprintf_s( oapiDebugString(), 256, "%.2f %.2f %.2f %.2f %.2f %.2f", Ppos[0], Ppos[1], Ppos[2], Ypos[0], Ypos[1], Ypos[2] );
		return;
	}

	void MPS_ATVC_CMD_SOP::Realize( void )
	{
		DiscreteBundle* bundle = BundleManager()->CreateBundle( "ATVC", 10 );
		dopPpos[0].Connect( bundle, 0 );
		dopPpos[1].Connect( bundle, 1 );
		dopPpos[2].Connect( bundle, 2 );
		dopYpos[0].Connect( bundle, 3 );
		dopYpos[1].Connect( bundle, 4 );
		dopYpos[2].Connect( bundle, 5 );

		for (int i = 0; i < 3; i++)
		{
			dopPpos[i].SetLine( static_cast<float>(Ppos[i]) );
			dopYpos[i].SetLine( static_cast<float>(Ypos[i]) );
		}
		return;
	}

	bool MPS_ATVC_CMD_SOP::OnParseLine( const char* keyword, const char* value )
	{
		double tmp = 0;

		if (!_stricmp( keyword, "CenterPitch" ))
		{
			sscanf_s( value, "%lf", &tmp );
			Ppos[0] = range( -10.5, tmp, 10.5 );
			return true;
		}
		else if (!_stricmp( keyword, "CenterYaw" ))
		{
			sscanf_s( value, "%lf", &tmp );
			Ypos[0] = range( -8.5, tmp, 8.5 );
			return true;
		}
		else if (!_stricmp( keyword, "LeftPitch" ))
		{
			sscanf_s( value, "%lf", &tmp );
			Ppos[1] = range( -10.5, tmp, 10.5 );
			return true;
		}
		else if (!_stricmp( keyword, "LeftYaw" ))
		{
			sscanf_s( value, "%lf", &tmp );
			Ypos[1] = range( -8.5, tmp, 8.5 );
			return true;
		}
		else if (!_stricmp( keyword, "RightPitch" ))
		{
			sscanf_s( value, "%lf", &tmp );
			Ppos[2] = range( -10.5, tmp, 10.5 );
			return true;
		}
		else if (!_stricmp( keyword, "RightYaw" ))
		{
			sscanf_s( value, "%lf", &tmp );
			Ypos[2] = range( -8.5, tmp, 8.5 );
			return true;
		}
		return false;
	}

	void MPS_ATVC_CMD_SOP::OnSaveState( FILEHANDLE scn ) const
	{
		oapiWriteScenario_float( scn, "CenterPitch", Ppos[0] );
		oapiWriteScenario_float( scn, "CenterYaw", Ypos[0] );
		oapiWriteScenario_float( scn, "LeftPitch", Ppos[1] );
		oapiWriteScenario_float( scn, "LeftYaw", Ypos[1] );
		oapiWriteScenario_float( scn, "RightPitch", Ppos[2] );
		oapiWriteScenario_float( scn, "RightYaw", Ypos[2] );
		return;
	}

	bool MPS_ATVC_CMD_SOP::OnMajorModeChange( unsigned int newMajorMode )
	{
		return true;// HACK until proper logic is implemented
		/*switch (newMajorMode)
		{
			case 101:
			case 102:
			case 103:
			case 104:
			case 304:
			case 305:
			case 601:
			case 602:
			case 603:
			case 901:
				return true;
			default:
				return false;
		}*/
	}

	void MPS_ATVC_CMD_SOP::SetSSMEActPos( unsigned int num, double Ppos, double Ypos )
	{
		assert( (num <= 2) && "MPS_ATVC_CMD_SOP::SetSSMEActPos.num" );

		this->Ppos[num] = Ppos;
		this->Ypos[num] = Ypos;
		return;
	}
}
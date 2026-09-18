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
2022/12/23   GLS
2023/09/24   GLS
2026/09/18   GLS
********************************************/
#include "MPS_ATVC_CMD_SOP.h"
#include "../../../Atlantis.h"
#include <MathSSV.h>


namespace dps
{
	// K-Loads
	constexpr double MPSPDUMP1 = 0.0;// (V97U4115C) [deg]
	constexpr double MPSPDUMP2 = -10.0;// (V97U4116C) [deg]
	constexpr double MPSPDUMP3 = -10.0;// (V97U4117C) [deg]
	constexpr double MPSPSTOW1 = 0.0;// (V97U4118C) [deg]
	constexpr double MPSPSTOW2 = -10.0;// (V97U4119C) [deg]
	constexpr double MPSPSTOW3 = -10.0;// (V97U4120C) [deg]
	constexpr double MPSYDUMP1 = 0.0;// (V97U4121C) [deg]
	constexpr double MPSYDUMP2 = -3.5;// (V97U4122C) [deg]
	constexpr double MPSYDUMP3 = 3.5;// ()V97U4123C [deg]
	constexpr double MPSYSTOW1 = 0.0;// (V97U4124C) [deg]
	constexpr double MPSYSTOW2 = -3.5;// (V97U4125C) [deg]
	constexpr double MPSYSTOW3 = 3.5;// (V97U4126C) [deg]


	MPS_ATVC_CMD_SOP::MPS_ATVC_CMD_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "MPS_ATVC_CMD_SOP" )
	{
		Ppos[0] = 0.0;
		Ppos[1] = 0.0;
		Ppos[2] = 0.0;
		Ypos[0] = 0.0;
		Ypos[1] = 0.0;
		Ypos[2] = 0.0;

		{// TODO fix IO
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
		}
		return;
	}

	MPS_ATVC_CMD_SOP::~MPS_ATVC_CMD_SOP( void )
	{
		return;
	}

	void MPS_ATVC_CMD_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		if ((ReadCOMPOOL_IS( SCP_MM_CODE_301 ) == 1) || (ReadCOMPOOL_IS( SCP_ENT_STOW_GIM_POSN ) == 1))
		{
			if (ReadCOMPOOL_IS( SCP_RTLS_ABORT_DECLARED ) == 1)
			{
				// chute
				Ppos[0] = ReadCOMPOOL_SS( SCP_CHUTESTOW1 );
				Ppos[1] = ReadCOMPOOL_SS( SCP_CHUTESTOW2 );
				Ppos[2] = ReadCOMPOOL_SS( SCP_CHUTESTOW3 );
				Ypos[0] = MPSYSTOW1;
				Ypos[1] = MPSYSTOW2;
				Ypos[2] = MPSYSTOW3;
			}
			else
			{
				// stow
				Ppos[0] = MPSPSTOW1;
				Ppos[1] = MPSPSTOW2;
				Ppos[2] = MPSPSTOW3;
				Ypos[0] = MPSYSTOW1;
				Ypos[1] = MPSYSTOW2;
				Ypos[2] = MPSYSTOW3;
			}
		}
		else
		{
			if (ReadCOMPOOL_IS( SCP_MPS_DUMP_GIMBAL_POS_FLAG ) == 1)
			{
				// dump
				Ppos[0] = MPSPDUMP1;
				Ppos[1] = MPSPDUMP2;
				Ppos[2] = MPSPDUMP3;
				Ypos[0] = MPSYDUMP1;
				Ypos[1] = MPSYDUMP2;
				Ypos[2] = MPSYDUMP3;
			}
			else
			{
				// asc dap
				Ppos[0] = ReadCOMPOOL_SS( SCP_DYC1 );
				Ppos[1] = ReadCOMPOOL_SS( SCP_DYC2 );
				Ppos[2] = ReadCOMPOOL_SS( SCP_DYC3 );
				Ypos[0] = ReadCOMPOOL_SS( SCP_DZC1 );
				Ypos[1] = ReadCOMPOOL_SS( SCP_DZC2 );
				Ypos[2] = ReadCOMPOOL_SS( SCP_DZC3 );
			}
		}

		// HACK should be commanded by LDG GEAR VLV CNTL
		if (ReadCOMPOOL_IS( SCP_MM_CODE_304 ) == 1)
		{
			if (ReadCOMPOOL_SS( SCP_REL_VEL_MAG ) < 8000.0)
			{
				Ppos[0] = ReadCOMPOOL_SS( SCP_CHUTESTOW1 );
				Ppos[1] = ReadCOMPOOL_SS( SCP_CHUTESTOW2 );
				Ppos[2] = ReadCOMPOOL_SS( SCP_CHUTESTOW3 );
				Ypos[0] = MPSYSTOW1;
				Ypos[1] = MPSYSTOW2;
				Ypos[2] = MPSYSTOW3;
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
}

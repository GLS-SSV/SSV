/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/06/28   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/12/28   GLS
2021/12/30   GLS
2025/07/20   GLS
********************************************/
#include "RHC_RM.h"
#include <MathSSV.h>


namespace dps
{
	RHC_RM::RHC_RM( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "RHC_RM" )
	{
		RHC_L_P = 0.0;
		RHC_L_R = 0.0;
		RHC_L_Y = 0.0;

		RHC_R_P = 0.0;
		RHC_R_R = 0.0;
		RHC_R_Y = 0.0;

		RHC_A_P = 0.0;
		RHC_A_R = 0.0;
		RHC_A_Y = 0.0;
		return;
	}

	RHC_RM::~RHC_RM( void )
	{
		return;
	}

	void RHC_RM::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "LeftRHCTHC_A", 16 );
		for (int i = 0; i < 9; i++) LeftRHC[i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "RightRHC_A", 16 );
		for (int i = 0; i < 9; i++) RightRHC[i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "AftRHCTHC_A", 16 );
		for (int i = 0; i < 9; i++) AftRHC[i].Connect( pBundle, i );
		return;
	}

	void RHC_RM::OnPostStep( double simt, double simdt, double mjd )
	{
		RHC_L_P = midval( LeftRHC[0].GetVoltage(), LeftRHC[1].GetVoltage(), LeftRHC[2].GetVoltage() );
		RHC_L_R = midval( LeftRHC[3].GetVoltage(), LeftRHC[4].GetVoltage(), LeftRHC[5].GetVoltage() );
		RHC_L_Y = midval( LeftRHC[6].GetVoltage(), LeftRHC[7].GetVoltage(), LeftRHC[8].GetVoltage() );
		WriteCOMPOOL_IS( SCP_L_PIT_DG, 1 );
		WriteCOMPOOL_IS( SCP_L_ROL_DG, 1 );
		WriteCOMPOOL_IS( SCP_L_YAW_DG, 1 );

		RHC_R_P = midval( RightRHC[0].GetVoltage(), RightRHC[1].GetVoltage(), RightRHC[2].GetVoltage() );
		RHC_R_R = midval( RightRHC[3].GetVoltage(), RightRHC[4].GetVoltage(), RightRHC[5].GetVoltage() );
		RHC_R_Y = midval( RightRHC[6].GetVoltage(), RightRHC[7].GetVoltage(), RightRHC[8].GetVoltage() );
		WriteCOMPOOL_IS( SCP_R_PIT_DG, 1 );
		WriteCOMPOOL_IS( SCP_R_ROL_DG, 1 );
		WriteCOMPOOL_IS( SCP_R_YAW_DG, 1 );

		RHC_A_P = midval( AftRHC[0].GetVoltage(), AftRHC[1].GetVoltage(), AftRHC[2].GetVoltage() );
		RHC_A_R = midval( AftRHC[3].GetVoltage(), AftRHC[4].GetVoltage(), AftRHC[5].GetVoltage() );
		RHC_A_Y = midval( AftRHC[6].GetVoltage(), AftRHC[7].GetVoltage(), AftRHC[8].GetVoltage() );
		WriteCOMPOOL_IS( SCP_A_PIT_DG, 1 );
		WriteCOMPOOL_IS( SCP_A_ROL_DG, 1 );
		WriteCOMPOOL_IS( SCP_A_YAW_DG, 1 );
		return;
	}

	bool RHC_RM::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void RHC_RM::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	bool RHC_RM::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 102:
			case 103:
			case 104:
			case 105:
			case 106:
			case 201:
			case 202:
			case 301:
			case 302:
			case 303:
			case 304:
			case 305:
			case 601:
			case 602:
			case 603:
			case 801:
				return true;
			default:
				return false;
		}
	}

	void RHC_RM::GetRHCData_L( double &pitch, double &roll, double &yaw ) const
	{
		pitch = RHC_L_P;
		roll = RHC_L_R;
		yaw = RHC_L_Y;
		return;
	}

	void RHC_RM::GetRHCData_R( double &pitch, double &roll, double &yaw ) const
	{
		pitch = RHC_R_P;
		roll = RHC_R_R;
		yaw = RHC_R_Y;
		return;
	}

	void RHC_RM::GetRHCData_A( double &pitch, double &roll, double &yaw ) const
	{
		pitch = RHC_A_P;
		roll = RHC_A_R;
		yaw = RHC_A_Y;
		return;
	}
}

/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/06/28   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/12/27   GLS
2021/12/30   GLS
2022/06/04   GLS
2022/08/05   GLS
********************************************/
#include "THC_RM.h"


namespace dps
{
	THC_RM::THC_RM( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "THC_RM" )
	{
		THC_L_pX = false;
		THC_L_mX = false;
		THC_L_pY = false;
		THC_L_mY = false;
		THC_L_pZ = false;
		THC_L_mZ = false;

		THC_A_pX = false;
		THC_A_mX = false;
		THC_A_pY = false;
		THC_A_mY = false;
		THC_A_pZ = false;
		THC_A_mZ = false;
		return;
	}

	THC_RM::~THC_RM( void )
	{
		return;
	}

	void THC_RM::OnPostStep( double simt, double simdt, double mjd )
	{
		unsigned short FF1_IOM6_CH0 = ReadCOMPOOL_IS( SCP_FF1_IOM6_CH0_DATA );
		unsigned short FF1_IOM15_CH0 = ReadCOMPOOL_IS( SCP_FF1_IOM15_CH0_DATA );
		unsigned short FF2_IOM6_CH0 = ReadCOMPOOL_IS( SCP_FF2_IOM6_CH0_DATA );
		unsigned short FF2_IOM15_CH0 = ReadCOMPOOL_IS( SCP_FF2_IOM15_CH0_DATA );
		unsigned short FF3_IOM6_CH0 = ReadCOMPOOL_IS( SCP_FF3_IOM6_CH0_DATA );
		unsigned short FF3_IOM15_CH0 = ReadCOMPOOL_IS( SCP_FF3_IOM15_CH0_DATA );

		bool FWD_THC_POS_X_OUTPUT_A = ((FF1_IOM6_CH0 & 0x0080) != 0);
		bool FWD_THC_POS_X_OUTPUT_B = ((FF2_IOM6_CH0 & 0x0080) != 0);
		bool FWD_THC_POS_X_OUTPUT_C = ((FF3_IOM6_CH0 & 0x0080) != 0);
		bool FWD_THC_NEG_X_OUTPUT_A = ((FF1_IOM6_CH0 & 0x0100) != 0);
		bool FWD_THC_NEG_X_OUTPUT_B = ((FF2_IOM6_CH0 & 0x0100) != 0);
		bool FWD_THC_NEG_X_OUTPUT_C = ((FF3_IOM6_CH0 & 0x0100) != 0);
		bool FWD_THC_POS_Y_OUTPUT_A = ((FF1_IOM6_CH0 & 0x0200) != 0);
		bool FWD_THC_POS_Y_OUTPUT_B = ((FF2_IOM6_CH0 & 0x0200) != 0);
		bool FWD_THC_POS_Y_OUTPUT_C = ((FF3_IOM6_CH0 & 0x0200) != 0);
		bool FWD_THC_NEG_Y_OUTPUT_A = ((FF1_IOM6_CH0 & 0x0400) != 0);
		bool FWD_THC_NEG_Y_OUTPUT_B = ((FF2_IOM6_CH0 & 0x0400) != 0);
		bool FWD_THC_NEG_Y_OUTPUT_C = ((FF3_IOM6_CH0 & 0x0400) != 0);
		bool FWD_THC_POS_Z_OUTPUT_A = ((FF1_IOM6_CH0 & 0x0800) != 0);
		bool FWD_THC_POS_Z_OUTPUT_B = ((FF2_IOM6_CH0 & 0x0800) != 0);
		bool FWD_THC_POS_Z_OUTPUT_C = ((FF3_IOM6_CH0 & 0x0800) != 0);
		bool FWD_THC_NEG_Z_OUTPUT_A = ((FF1_IOM6_CH0 & 0x1000) != 0);
		bool FWD_THC_NEG_Z_OUTPUT_B = ((FF2_IOM6_CH0 & 0x1000) != 0);
		bool FWD_THC_NEG_Z_OUTPUT_C = ((FF3_IOM6_CH0 & 0x1000) != 0);

		bool AFT_THC_POS_X_OUTPUT_A = ((FF1_IOM15_CH0 & 0x0080) != 0);
		bool AFT_THC_POS_X_OUTPUT_B = ((FF2_IOM15_CH0 & 0x0080) != 0);
		bool AFT_THC_POS_X_OUTPUT_C = ((FF3_IOM15_CH0 & 0x0080) != 0);
		bool AFT_THC_NEG_X_OUTPUT_A = ((FF1_IOM15_CH0 & 0x0100) != 0);
		bool AFT_THC_NEG_X_OUTPUT_B = ((FF2_IOM15_CH0 & 0x0100) != 0);
		bool AFT_THC_NEG_X_OUTPUT_C = ((FF3_IOM15_CH0 & 0x0100) != 0);
		bool AFT_THC_POS_Y_OUTPUT_A = ((FF1_IOM15_CH0 & 0x0200) != 0);
		bool AFT_THC_POS_Y_OUTPUT_B = ((FF2_IOM15_CH0 & 0x0200) != 0);
		bool AFT_THC_POS_Y_OUTPUT_C = ((FF3_IOM15_CH0 & 0x0200) != 0);
		bool AFT_THC_NEG_Y_OUTPUT_A = ((FF1_IOM15_CH0 & 0x0400) != 0);
		bool AFT_THC_NEG_Y_OUTPUT_B = ((FF2_IOM15_CH0 & 0x0400) != 0);
		bool AFT_THC_NEG_Y_OUTPUT_C = ((FF3_IOM15_CH0 & 0x0400) != 0);
		bool AFT_THC_POS_Z_OUTPUT_A = ((FF1_IOM15_CH0 & 0x0800) != 0);
		bool AFT_THC_POS_Z_OUTPUT_B = ((FF2_IOM15_CH0 & 0x0800) != 0);
		bool AFT_THC_POS_Z_OUTPUT_C = ((FF3_IOM15_CH0 & 0x0800) != 0);
		bool AFT_THC_NEG_Z_OUTPUT_A = ((FF1_IOM15_CH0 & 0x1000) != 0);
		bool AFT_THC_NEG_Z_OUTPUT_B = ((FF2_IOM15_CH0 & 0x1000) != 0);
		bool AFT_THC_NEG_Z_OUTPUT_C = ((FF3_IOM15_CH0 & 0x1000) != 0);

		THC_L_pX = (FWD_THC_POS_X_OUTPUT_A && FWD_THC_POS_X_OUTPUT_B) || (FWD_THC_POS_X_OUTPUT_A && FWD_THC_POS_X_OUTPUT_C) || (FWD_THC_POS_X_OUTPUT_B && FWD_THC_POS_X_OUTPUT_C);
		THC_L_mX = (FWD_THC_NEG_X_OUTPUT_A && FWD_THC_NEG_X_OUTPUT_B) || (FWD_THC_NEG_X_OUTPUT_A && FWD_THC_NEG_X_OUTPUT_C) || (FWD_THC_NEG_X_OUTPUT_B && FWD_THC_NEG_X_OUTPUT_C);
		THC_L_pY = (FWD_THC_POS_Y_OUTPUT_A && FWD_THC_POS_Y_OUTPUT_B) || (FWD_THC_POS_Y_OUTPUT_A && FWD_THC_POS_Y_OUTPUT_C) || (FWD_THC_POS_Y_OUTPUT_B && FWD_THC_POS_Y_OUTPUT_C);
		THC_L_mY = (FWD_THC_NEG_Y_OUTPUT_A && FWD_THC_NEG_Y_OUTPUT_B) || (FWD_THC_NEG_Y_OUTPUT_A && FWD_THC_NEG_Y_OUTPUT_C) || (FWD_THC_NEG_Y_OUTPUT_B && FWD_THC_NEG_Y_OUTPUT_C);
		THC_L_pZ = (FWD_THC_POS_Z_OUTPUT_A && FWD_THC_POS_Z_OUTPUT_B) || (FWD_THC_POS_Z_OUTPUT_A && FWD_THC_POS_Z_OUTPUT_C) || (FWD_THC_POS_Z_OUTPUT_B && FWD_THC_POS_Z_OUTPUT_C);
		THC_L_mZ = (FWD_THC_NEG_Z_OUTPUT_A && FWD_THC_NEG_Z_OUTPUT_B) || (FWD_THC_NEG_Z_OUTPUT_A && FWD_THC_NEG_Z_OUTPUT_C) || (FWD_THC_NEG_Z_OUTPUT_B && FWD_THC_NEG_Z_OUTPUT_C);

		THC_A_pX = (AFT_THC_POS_X_OUTPUT_A && AFT_THC_POS_X_OUTPUT_B) || (AFT_THC_POS_X_OUTPUT_A && AFT_THC_POS_X_OUTPUT_C) || (AFT_THC_POS_X_OUTPUT_B && AFT_THC_POS_X_OUTPUT_C);
		THC_A_mX = (AFT_THC_NEG_X_OUTPUT_A && AFT_THC_NEG_X_OUTPUT_B) || (AFT_THC_NEG_X_OUTPUT_A && AFT_THC_NEG_X_OUTPUT_C) || (AFT_THC_NEG_X_OUTPUT_B && AFT_THC_NEG_X_OUTPUT_C);
		THC_A_pY = (AFT_THC_POS_Y_OUTPUT_A && AFT_THC_POS_Y_OUTPUT_B) || (AFT_THC_POS_Y_OUTPUT_A && AFT_THC_POS_Y_OUTPUT_C) || (AFT_THC_POS_Y_OUTPUT_B && AFT_THC_POS_Y_OUTPUT_C);
		THC_A_mY = (AFT_THC_NEG_Y_OUTPUT_A && AFT_THC_NEG_Y_OUTPUT_B) || (AFT_THC_NEG_Y_OUTPUT_A && AFT_THC_NEG_Y_OUTPUT_C) || (AFT_THC_NEG_Y_OUTPUT_B && AFT_THC_NEG_Y_OUTPUT_C);
		THC_A_pZ = (AFT_THC_POS_Z_OUTPUT_A && AFT_THC_POS_Z_OUTPUT_B) || (AFT_THC_POS_Z_OUTPUT_A && AFT_THC_POS_Z_OUTPUT_C) || (AFT_THC_POS_Z_OUTPUT_B && AFT_THC_POS_Z_OUTPUT_C);
		THC_A_mZ = (AFT_THC_NEG_Z_OUTPUT_A && AFT_THC_NEG_Z_OUTPUT_B) || (AFT_THC_NEG_Z_OUTPUT_A && AFT_THC_NEG_Z_OUTPUT_C) || (AFT_THC_NEG_Z_OUTPUT_B && AFT_THC_NEG_Z_OUTPUT_C);
		return;
	}

	bool THC_RM::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void THC_RM::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	bool THC_RM::OnMajorModeChange( unsigned int newMajorMode )
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

	void THC_RM::GetTHCData_L( bool &px, bool &mx, bool &py, bool &my, bool &pz, bool &mz ) const
	{
		px = THC_L_pX;
		mx = THC_L_mX;
		py = THC_L_pY;
		my = THC_L_mY;
		pz = THC_L_pZ;
		mz = THC_L_mZ;
		return;
	}

	void THC_RM::GetTHCData_A( bool &px, bool &mx, bool &py, bool &my, bool &pz, bool &mz ) const
	{
		px = THC_A_pX;
		mx = THC_A_mX;
		py = THC_A_pY;
		my = THC_A_mY;
		pz = THC_A_pZ;
		mz = THC_A_mZ;
		return;
	}
}
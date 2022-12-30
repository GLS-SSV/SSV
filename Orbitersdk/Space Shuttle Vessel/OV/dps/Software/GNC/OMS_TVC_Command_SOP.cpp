/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/04/07   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/01/20   GLS
2021/04/15   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/12/28   GLS
2022/12/29   GLS
********************************************/
#include "OMS_TVC_Command_SOP.h"
#include <MathSSV.h>
#include <cassert>


namespace dps
{
	constexpr float COMSLP = 0.6097f;// COMPENSATION SCALE FACTOR-OMS L PITCH CMD (V97U3971C) [vdc/deg]
	constexpr float COMSLY = 0.6114f;// COMPENSATION SCALE FACTOR-OMS L YAW CMD (V97U3973C) [vdc/deg]
	constexpr float COMSRP = 0.6097f;// COMPENSATION SCALE FACTOR-OMS R PITCH CMD (V97U3975C) [vdc/deg]
	constexpr float COMSRY = -0.6114f;// COMPENSATION SCALE FACTOR-OMS R YAW CMD (V97U3977C) [vdc/deg]

	constexpr float KOMSLP = -0.0448f;// COMPENSATION BIAS- OMS L PITCH CMD (V97U4082C) [vdc]
	constexpr float KOMSLY = -0.2595f;// COMPENSATION BIAS- OMS L YAW CMD (V97U4084C) [vdc]
	constexpr float KOMSRP = -0.0448f;// COMPENSATION BIAS- OMS R PITCH CMD (V97U4086C) [vdc]
	constexpr float KOMSRY = -0.2595f;// COMPENSATION BIAS- OMS R YAW CMD (V97U4088C) [vdc]

	constexpr float LOMSPOSNP1 = 5.89f;// OMS–L DRIVE CHECK PITCH POSN 1 (V97U4105C) [deg]
	constexpr float LOMSPOSNP2 = -5.89f;// OMS–L DRIVE CHECK PITCH POSN 2 (V97U4106C) [deg]
	constexpr float LOMSPOSNP3 = 5.89f;// OMS–L DRIVE CHECK PITCH POSN 3 (V97U4107C) [deg]
	constexpr float LOMSPOSNY1 = 6.44f;// OMS–L DRIVE CHECK YAW POSN 1 (V97U4108C) [deg]
	constexpr float LOMSPOSNY2 = -6.44f;// OMS–L DRIVE CHECK YAW POSN 2 (V97U4109C) [deg]
	constexpr float LOMSPOSNY3 = 6.44f;// OMS–L DRIVE CHECK YAW POSN 3 (V97U4110C) [deg]
	constexpr float ROMSPOSNP1 = 5.89f;// OMS–R DRIVE CHECK PITCH POSN 1 (V97U4138C) [deg]
	constexpr float ROMSPOSNP2 = -5.89f;// OMS–R DRIVE CHECK PITCH POSN 2 (V97U4139C) [deg]
	constexpr float ROMSPOSNP3 = 5.89f;// OMS–R DRIVE CHECK PITCH POSN 3 (V97U4140C) [deg]
	constexpr float ROMSPOSNY1 = 6.44f;// OMS–R DRIVE CHECK YAW POSN 1 (V97U4141C) [deg]
	constexpr float ROMSPOSNY2 = -6.44f;// OMS–R DRIVE CHECK YAW POSN 2 (V97U4142C) [deg]
	constexpr float ROMSPOSNY3 = 6.44f;// OMS–R DRIVE CHECK YAW POSN 3 (V97U4143C) [deg]

	constexpr float OMSLSTOW1 = 5.89f;// OMS-L ENG PITCH STOW POSN (V97U4131C) [deg]
	constexpr float OMSLSTOW2 = 6.44f;// OMS-L ENG YAW STOW POSN (V97U4132C) [deg]
	constexpr float OMSLTRIM1 = -0.86f;// OMS L ENG PITCH TRIM POSITION (V97U4196C) [deg]
	constexpr float OMSLTRIM2 = 6.44f;// OMS L ENG YAW TRIM POSITION (V97U4197C) [deg]
	constexpr float OMSRSTOW1 = 5.89f;// OMS-R ENG PITCH STOW POSN (V97U4133C) [deg]
	constexpr float OMSRSTOW2 = -6.44f;// OMS-R ENG YAW STOW POSN (V97U4134C) [deg]
	constexpr float OMSRTRIM1 = -0.86f;// OMS R ENG PITCH TRIM POSITION (V97U4198C) [deg]
	constexpr float OMSRTRIM2 = -6.44f;// OMS R ENG YAW TRIM POSITION (V97U4199C) [deg]
	constexpr float OMS_THRSHLDL[2] = {0.7f, 0.7f};// {OMS-L P FAIL STOW THRESHOLD (V97U4175C), OMS-L Y FAIL STOW THRESHOLD (V97U4176C)} [deg]
	constexpr float OMS_THRSHLDR[2] = {0.7f, 0.7f};// {OMS-R P FAIL STOW THRESHOLD (V97U4177C), OMS-R Y FAIL STOW THRESHOLD (V97U4178C)} [deg]


	OMSTVCCMD_SOP::OMSTVCCMD_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "OMS_TVC_Command_SOP" )
	{
		L_pitch = 0.0;
		L_yaw = 0.0;
		R_pitch = 0.0;
		R_yaw = 0.0;
		GimbalCheckTimer = 0.0;

		GimbalCheck = false;
		return;
	}

	OMSTVCCMD_SOP::~OMSTVCCMD_SOP( void )
	{
		return;
	}

	void OMSTVCCMD_SOP::Realize( void )
	{
		return;
	}

	void OMSTVCCMD_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		// stow positions
		float OMS_L_P = OMSLSTOW1;// [deg]
		float OMS_L_Y = OMSLSTOW2;// [deg]
		float OMS_R_P = OMSRSTOW1;// [deg]
		float OMS_R_Y = OMSRSTOW2;// [deg]

		if ((ReadCOMPOOL_IS( SCP_OMS_CK_ENA_CMD ) == 0) && (GetMajorMode() != 303) && (GetMajorMode() != 602))
		{
			// control law
			OMS_L_P = ReadCOMPOOL_VS( SCP_OMSL_PITCH_YAW_CMD, 1, 2 );
			OMS_L_Y = ReadCOMPOOL_VS( SCP_OMSL_PITCH_YAW_CMD, 2, 2 );
			OMS_R_P = ReadCOMPOOL_VS( SCP_OMSR_PITCH_YAW_CMD, 1, 2 );
			OMS_R_Y = ReadCOMPOOL_VS( SCP_OMSR_PITCH_YAW_CMD, 2, 2 );
		}

		if (((GetMajorMode() == 104) || (GetMajorMode() == 105) || (GetMajorMode() == 106) || (GetMajorMode() == 301) || (GetMajorMode() == 302) || (GetMajorMode() == 202)) && (ReadCOMPOOL_IS( SCP_OMS_CK_ENA_CMD ) == 1))
		{
			// gimbal check
		}

		if ((GetMajorMode() == 303) || (0/*TODO TAL_ABORT_DECLARED*/))
		{
			// unique stow positions
			OMS_L_P = OMSLSTOW1;
			OMS_L_Y = OMSLSTOW2;
			OMS_R_P = OMSRSTOW1;
			OMS_R_Y = OMSRSTOW2;
		}

		if (GetMajorMode() == 602)
		{
			if (0/*TODO CG_TRIM*/)
			{
				// unique trim positions
				OMS_L_P = OMSLTRIM1;
				OMS_L_Y = OMSLTRIM2;
				OMS_R_P = OMSRTRIM1;
				OMS_R_Y = OMSRTRIM2;
			}
			else
			{
				// stow positions
				OMS_L_P = OMSLSTOW1;
				OMS_L_Y = OMSLSTOW2;
				OMS_R_P = OMSRSTOW1;
				OMS_R_Y = OMSRSTOW2;
			}
		}

		if (GetMajorMode() == 304)
		{
			if (0/*TODO CG_TRIM*/)
			{
				// unique trim positions
				OMS_L_P = OMSLTRIM1;
				OMS_L_Y = OMSLTRIM2;
				OMS_R_P = OMSRTRIM1;
				OMS_R_Y = OMSRTRIM2;
			}
			else
			{
				// unique stow positions
				OMS_L_P = OMSLSTOW1;
				OMS_L_Y = OMSLSTOW2;
				OMS_R_P = OMSRSTOW1;
				OMS_R_Y = OMSRSTOW2;
			}
		}

		if ((GetMajorMode() == 104) || (GetMajorMode() == 105) || (GetMajorMode() == 106) || (GetMajorMode() == 202) || (GetMajorMode() == 301) || (GetMajorMode() == 302) || (GetMajorMode() == 303))
		{
			// ZAP commands
		}

		if (GetMajorMode() == 601)
		{
			if (0/*TODO MATED_CG_TRIM*/)
			{
				// TODO unique trim positions
				// OMS_L_P = MATED_OMS_L_TRIM1
				// OMS_L_Y = MATED_OMS_L_TRIM2
				// OMS_R_P = MATED_OMS_R_TRIM1
				// OMS_R_Y = MATED_OMS_R_TRIM2
			}
			else if (0/*TODO CG_TRIM*/)
			{
				// unique trim positions
				OMS_L_P = OMSLTRIM1;
				OMS_L_Y = OMSLTRIM2;
				OMS_R_P = OMSRTRIM1;
				OMS_R_Y = OMSRTRIM2;
			}
			else
			{
				// stow positions
				OMS_L_P = OMSLSTOW1;
				OMS_L_Y = OMSLSTOW2;
				OMS_R_P = OMSRSTOW1;
				OMS_R_Y = OMSRSTOW2;
			}
		}

		float COMP_OMS_L_P = (OMS_L_P * COMSLP) + KOMSLP;// [vdc]
		float COMP_OMS_L_Y = (OMS_L_Y * COMSLY) + KOMSLY;// [vdc]
		float COMP_OMS_R_P = (OMS_R_P * COMSRP) + KOMSRP;// [vdc]
		float COMP_OMS_R_Y = (OMS_R_Y * COMSRY) + KOMSRY;// [vdc]

		WriteCOMPOOL_IS( SCP_FA1_IOM4_CH7_DATA, static_cast<unsigned short>(COMP_OMS_L_P / 0.01/*10mv*/) );
		WriteCOMPOOL_IS( SCP_FA1_IOM4_CH8_DATA, static_cast<unsigned short>(COMP_OMS_L_Y / 0.01/*10mv*/) );
		WriteCOMPOOL_IS( SCP_FA4_IOM4_CH7_DATA, static_cast<unsigned short>(COMP_OMS_R_P / 0.01/*10mv*/) );
		WriteCOMPOOL_IS( SCP_FA4_IOM4_CH8_DATA, static_cast<unsigned short>(COMP_OMS_R_Y / 0.01/*10mv*/) );

		WriteCOMPOOL_IS( SCP_FA3_IOM4_CH7_DATA, static_cast<unsigned short>(COMP_OMS_L_P / 0.01/*10mv*/) );
		WriteCOMPOOL_IS( SCP_FA3_IOM4_CH8_DATA, static_cast<unsigned short>(COMP_OMS_L_Y / 0.01/*10mv*/) );
		WriteCOMPOOL_IS( SCP_FA2_IOM4_CH7_DATA, static_cast<unsigned short>(COMP_OMS_R_P / 0.01/*10mv*/) );
		WriteCOMPOOL_IS( SCP_FA2_IOM4_CH8_DATA, static_cast<unsigned short>(COMP_OMS_R_Y / 0.01/*10mv*/) );

		WriteCOMPOOL_IS( SCP_FF1_IOM2_CH2_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM2_CH2_DATA ) | 0x0006 );// L OMS TVC: PRI ENABLE 1 & 2
		WriteCOMPOOL_IS( SCP_FF2_IOM2_CH2_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM2_CH2_DATA ) | 0x0000 );// L OMS TVC: SEC ENABLE 1 & 2
		WriteCOMPOOL_IS( SCP_FF3_IOM2_CH2_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM2_CH2_DATA ) | 0x0006 );// R OMS TVC: PRI ENABLE 1 & 2
		WriteCOMPOOL_IS( SCP_FF4_IOM2_CH2_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM2_CH2_DATA ) | 0x0000 );// R OMS TVC: SEC ENABLE 1 & 2
		return;
	}

	bool OMSTVCCMD_SOP::OnParseLine( const char* keyword, const char* value )
	{
		if (!_strnicmp( keyword, "LEFT_PITCH", 10 ))
		{
			sscanf_s( value, "%lf", &L_pitch );
			if ((L_pitch > 6.0) || (L_pitch < -6.0)) L_pitch = 0.0;
			return true;
		}
		else if (!_strnicmp( keyword, "LEFT_YAW", 8 ))
		{
			sscanf_s( value, "%lf", &L_yaw );
			if ((L_yaw > 7.0) || (L_yaw < -7.0)) L_yaw = 0.0;
			return true;
		}
		else if (!_strnicmp( keyword, "RIGHT_PITCH", 11 ))
		{
			sscanf_s( value, "%lf", &R_pitch );
			if ((R_pitch > 6.0) || (R_pitch < -6.0)) R_pitch = 0.0;
			return true;
		}
		else if (!_strnicmp( keyword, "RIGHT_YAW", 9 ))
		{
			sscanf_s( value, "%lf", &R_yaw );
			if ((R_yaw > 7.0) || (R_yaw < -7.0)) R_yaw = 0.0;
			return true;
		}
		return false;
	}

	void OMSTVCCMD_SOP::OnSaveState( FILEHANDLE scn ) const
	{
		oapiWriteScenario_float( scn, "LEFT_PITCH", L_pitch );
		oapiWriteScenario_float( scn, "LEFT_YAW", L_yaw );
		oapiWriteScenario_float( scn, "RIGHT_PITCH", R_pitch );
		oapiWriteScenario_float( scn, "RIGHT_YAW", R_yaw );
		return;
	}

	bool OMSTVCCMD_SOP::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 104:
			case 105:
			case 106:
			case 202:
			case 301:
			case 302:
			case 601:
			case 801:
			case 901:
				return true;
			case 303:// set entry stow positions
				L_pitch = 5.9;
				L_yaw = 6.4;
				R_pitch = 5.9;
				R_yaw = -6.4;
				return true;
			default:
				return false;
		}
	}
}
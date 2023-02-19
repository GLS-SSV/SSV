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
2022/12/31   GLS
2023/01/01   GLS
2023/01/02   GLS
2023/01/07   GLS
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

	constexpr float LOMSPOSNP1 = 5.89f;// OMS-L DRIVE CHECK PITCH POSN 1 (V97U4105C) [deg]
	constexpr float LOMSPOSNP2 = -5.89f;// OMS-L DRIVE CHECK PITCH POSN 2 (V97U4106C) [deg]
	constexpr float LOMSPOSNP3 = 5.89f;// OMS-L DRIVE CHECK PITCH POSN 3 (V97U4107C) [deg]
	constexpr float LOMSPOSNY1 = 6.44f;// OMS-L DRIVE CHECK YAW POSN 1 (V97U4108C) [deg]
	constexpr float LOMSPOSNY2 = -6.44f;// OMS-L DRIVE CHECK YAW POSN 2 (V97U4109C) [deg]
	constexpr float LOMSPOSNY3 = 6.44f;// OMS-L DRIVE CHECK YAW POSN 3 (V97U4110C) [deg]
	constexpr float ROMSPOSNP1 = 5.89f;// OMS-R DRIVE CHECK PITCH POSN 1 (V97U4138C) [deg]
	constexpr float ROMSPOSNP2 = -5.89f;// OMS-R DRIVE CHECK PITCH POSN 2 (V97U4139C) [deg]
	constexpr float ROMSPOSNP3 = 5.89f;// OMS-R DRIVE CHECK PITCH POSN 3 (V97U4140C) [deg]
	constexpr float ROMSPOSNY1 = 6.44f;// OMS-R DRIVE CHECK YAW POSN 1 (V97U4141C) [deg]
	constexpr float ROMSPOSNY2 = -6.44f;// OMS-R DRIVE CHECK YAW POSN 2 (V97U4142C) [deg]
	constexpr float ROMSPOSNY3 = 6.44f;// OMS-R DRIVE CHECK YAW POSN 3 (V97U4143C) [deg]

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

	constexpr unsigned short OMS_DRIVE1 = 75;// OMS DRIVE CHECK COUNTER 1 (V97U4128C) [1]
	constexpr unsigned short OMS_DRIVE2 = 75;// OMS DRIVE CHECK COUNTER 2 (V97U4129C) [1]
	constexpr unsigned short OMS_DRIVE3 = 75;// OMS DRIVE CHECK COUNTER 3 (V97U4130C) [1]


	OMSTVCCMD_SOP::OMSTVCCMD_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "OMS_TVC_Command_SOP" ),
		step(0.08), SOMSLPCMD(0.0f), SOMSLYCMD(0.0f), SOMSRPCMD(0.0f), SOMSRYCMD(0.0f), N(0), DRIVE_LATCH(0)
	{
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
		// HACK limit rate to 12.5Hz
		// TODO set rate for MM and ZAP
		step += simdt;
		if (step >= 0.08)
		{
			step = 0.0;

			if ((GetMajorMode() == 303) || (0/*TODO TAL_ABORT_DECLARED*/) || ((GetMajorMode() == 602) && (1/*TODO CG_TRIM*/)) || ((GetMajorMode() == 304) && (1/*TODO CG_TRIM*/)) || ((GetMajorMode() == 601) && (1/*TODO MATED_CG_TRIM*/) && (1/*TODO CG_TRIM*/)))
			{
				SOMSLPCMD = OMSLSTOW1;
				SOMSLYCMD = OMSLSTOW2;
				SOMSRPCMD = OMSRSTOW1;
				SOMSRYCMD = OMSRSTOW2;
			}
			else
			{
				if (GetMajorMode() == 601)
				{
					if (0/*TODO MATED_CG_TRIM*/)
					{
						// TODO set I-LOADs
						// SOMSLPCMD = MATED_OMS_L_TRIM1
						// SOMSLYCMD = MATED_OMS_L_TRIM2
						// SOMSRPCMD = MATED_OMS_R_TRIM1
						// SOMSRYCMD = MATED_OMS_R_TRIM2
					}
					else if (0/*TODO CG_TRIM*/)
					{
						SOMSLPCMD = OMSLTRIM1;
						SOMSLYCMD = OMSLTRIM2;
						SOMSRPCMD = OMSRTRIM1;
						SOMSRYCMD = OMSRTRIM2;
					}
				}
				else if (((GetMajorMode() == 304) || (GetMajorMode() == 602)) && (0/*TODO CG_TRIM*/))
				{
					SOMSLPCMD = OMSLTRIM1;
					SOMSLYCMD = OMSLTRIM2;
					SOMSRPCMD = OMSRTRIM1;
					SOMSRYCMD = OMSRTRIM2;
				}
				else
				{
					if (ReadCOMPOOL_IS( SCP_OMS_CK_ENA_CMD ) == 1)
					{
						DRIVE_LATCH = 1;
						WriteCOMPOOL_IS( SCP_DRIVE_OMS, 1 );
						N = 0;// HACK reset cycle counter
						WriteCOMPOOL_IS( SCP_OMS_CK_ENA_CMD, 0 );// HACK not sure where it is reset
					}

					if (DRIVE_LATCH == 1)
					{
						DRIVE_CHECK();
					}
					else
					{
						SOMSLPCMD = ReadCOMPOOL_VS( SCP_OMSL_PITCH_YAW_CMD, 1, 2 );
						SOMSLYCMD = ReadCOMPOOL_VS( SCP_OMSL_PITCH_YAW_CMD, 2, 2 );
						SOMSRPCMD = ReadCOMPOOL_VS( SCP_OMSR_PITCH_YAW_CMD, 1, 2 );
						SOMSRYCMD = ReadCOMPOOL_VS( SCP_OMSR_PITCH_YAW_CMD, 2, 2 );
					}
				}
			}
		}

		WriteCOMPOOL_SS( SCP_SEL_OMS_LP_CMD, SOMSLPCMD );
		WriteCOMPOOL_SS( SCP_SEL_OMS_LY_CMD, SOMSLYCMD );
		WriteCOMPOOL_SS( SCP_SEL_OMS_RP_CMD, SOMSRPCMD );
		WriteCOMPOOL_SS( SCP_SEL_OMS_RY_CMD, SOMSRYCMD );

		float DOMSLAP = (SOMSLPCMD * COMSLP) + KOMSLP;// [vdc]
		float DOMSLAY = (SOMSLYCMD * COMSLY) + KOMSLY;// [vdc]
		float DOMSRAP = (SOMSRPCMD * COMSRP) + KOMSRP;// [vdc]
		float DOMSRAY = (SOMSRYCMD * COMSRY) + KOMSRY;// [vdc]

		// limit to voltage range
		DOMSLAP = static_cast<float>(range( -5.12, DOMSLAP, 5.11 ));
		float DOMSLSP = DOMSLAP;
		DOMSLAY = static_cast<float>(range( -5.12, DOMSLAY, 5.11 ));
		float DOMSLSY = DOMSLAY;
		DOMSRAP = static_cast<float>(range( -5.12, DOMSRAP, 5.11 ));
		float DOMSRSP = DOMSRAP;
		DOMSRAY = static_cast<float>(range( -5.12, DOMSRAY, 5.11 ));
		float DOMSRSY = DOMSRAY;

		// TODO ZAP

		unsigned short tmp = static_cast<unsigned short>(fabs( DOMSLAP ) / 0.0025/*2.5mv*/);
		if (DOMSLAP < 0.0) tmp |= 0x0800;
		WriteCOMPOOL_IS( SCP_FA1_IOM4_CH7_DATA, tmp );
		WriteCOMPOOL_IS( SCP_FA2_IOM4_CH7_DATA, tmp );

		tmp = static_cast<unsigned short>(fabs( DOMSLAY ) / 0.0025/*2.5mv*/);
		if (DOMSLAY < 0.0) tmp |= 0x0800;
		WriteCOMPOOL_IS( SCP_FA1_IOM4_CH8_DATA, tmp );
		WriteCOMPOOL_IS( SCP_FA2_IOM4_CH8_DATA, tmp );

		tmp = static_cast<unsigned short>(fabs( DOMSRAP ) / 0.0025/*2.5mv*/);
		if (DOMSRAP < 0.0) tmp |= 0x0800;
		WriteCOMPOOL_IS( SCP_FA4_IOM4_CH7_DATA, tmp );
		WriteCOMPOOL_IS( SCP_FA3_IOM4_CH7_DATA, tmp );

		tmp = static_cast<unsigned short>(fabs( DOMSRAY ) / 0.0025/*2.5mv*/);
		if (DOMSRAY < 0.0) tmp |= 0x0800;
		WriteCOMPOOL_IS( SCP_FA4_IOM4_CH8_DATA, tmp );
		WriteCOMPOOL_IS( SCP_FA3_IOM4_CH8_DATA, tmp );

		unsigned short OMSL_ACT_SEL = ReadCOMPOOL_IS( SCP_OMSL_ACT_SEL );
		unsigned short OMSR_ACT_SEL = ReadCOMPOOL_IS( SCP_OMSR_ACT_SEL );
		WriteCOMPOOL_IS( SCP_FF1_IOM2_CH2_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM2_CH2_DATA ) | ((OMSL_ACT_SEL == 0) ? 0x0006 : 0x0000) );// L OMS TVC: PRI ENABLE 1 & 2
		WriteCOMPOOL_IS( SCP_FF2_IOM2_CH2_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM2_CH2_DATA ) | ((OMSL_ACT_SEL == 1) ? 0x0006 : 0x0000) );// L OMS TVC: SEC ENABLE 1 & 2
		WriteCOMPOOL_IS( SCP_FF4_IOM2_CH2_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM2_CH2_DATA ) | ((OMSR_ACT_SEL == 0) ? 0x0006 : 0x0000) );// R OMS TVC: PRI ENABLE 1 & 2
		WriteCOMPOOL_IS( SCP_FF3_IOM2_CH2_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM2_CH2_DATA ) | ((OMSR_ACT_SEL == 1) ? 0x0006 : 0x0000) );// R OMS TVC: SEC ENABLE 1 & 2
		return;
	}

	bool OMSTVCCMD_SOP::OnParseLine( const char* keyword, const char* value )
	{
		if (!_strnicmp( keyword, "LEFT_PITCH", 10 ))
		{
			sscanf_s( value, "%f", &SOMSLPCMD );
			if ((SOMSLPCMD > 6.0) || (SOMSLPCMD < -6.0)) SOMSLPCMD = 0.0f;
			return true;
		}
		else if (!_strnicmp( keyword, "LEFT_YAW", 8 ))
		{
			sscanf_s( value, "%f", &SOMSLYCMD );
			if ((SOMSLYCMD > 7.0) || (SOMSLYCMD < -7.0)) SOMSLYCMD = 0.0f;
			return true;
		}
		else if (!_strnicmp( keyword, "RIGHT_PITCH", 11 ))
		{
			sscanf_s( value, "%f", &SOMSRPCMD );
			if ((SOMSRPCMD > 6.0) || (SOMSRPCMD < -6.0)) SOMSRPCMD = 0.0f;
			return true;
		}
		else if (!_strnicmp( keyword, "RIGHT_YAW", 9 ))
		{
			sscanf_s( value, "%f", &SOMSRYCMD );
			if ((SOMSRYCMD > 7.0) || (SOMSRYCMD < -7.0)) SOMSRYCMD = 0.0f;
			return true;
		}
		return false;
	}

	void OMSTVCCMD_SOP::OnSaveState( FILEHANDLE scn ) const
	{
		oapiWriteScenario_float( scn, "LEFT_PITCH", SOMSLPCMD );
		oapiWriteScenario_float( scn, "LEFT_YAW", SOMSLYCMD );
		oapiWriteScenario_float( scn, "RIGHT_PITCH", SOMSRPCMD );
		oapiWriteScenario_float( scn, "RIGHT_YAW", SOMSRYCMD );
		return;
	}

	bool OMSTVCCMD_SOP::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 101:
			case 102:
			case 103:
				// HACK init cmds in OPS 1
				WriteCOMPOOL_VS( SCP_OMSL_PITCH_YAW_CMD, 1, OMSLSTOW1, 2 );
				WriteCOMPOOL_VS( SCP_OMSL_PITCH_YAW_CMD, 2, OMSLSTOW2, 2 );
				WriteCOMPOOL_VS( SCP_OMSR_PITCH_YAW_CMD, 1, OMSRSTOW1, 2 );
				WriteCOMPOOL_VS( SCP_OMSR_PITCH_YAW_CMD, 2, OMSRSTOW2, 2 );
			case 104:
			case 105:
			case 106:
			case 202:
			case 301:
			case 302:
			case 303:
			case 304:
			case 601:
			case 602:
				return true;
			default:
				return false;
		}
	}

	void OMSTVCCMD_SOP::DRIVE_CHECK( void )
	{
		if (N <= OMS_DRIVE1)
		{
			SOMSLPCMD = LOMSPOSNP1;
			SOMSLYCMD = LOMSPOSNY1;
			SOMSRPCMD = ROMSPOSNP1;
			SOMSRYCMD = ROMSPOSNY1;
		}
		else if (N <= (OMS_DRIVE1 + OMS_DRIVE2))// HACK added previous cycles
		{
			SOMSLPCMD = LOMSPOSNP2;
			SOMSLYCMD = LOMSPOSNY2;
			SOMSRPCMD = ROMSPOSNP2;
			SOMSRYCMD = ROMSPOSNY2;
		}
		else if (N <= (OMS_DRIVE1 + OMS_DRIVE2 + OMS_DRIVE3))// HACK added previous cycles
		{
			SOMSLPCMD = LOMSPOSNP3;
			SOMSLYCMD = LOMSPOSNY3;
			SOMSRPCMD = ROMSPOSNP3;
			SOMSRYCMD = ROMSPOSNY3;
		}
		else
		{
			DRIVE_LATCH = 0;
			WriteCOMPOOL_IS( SCP_DRIVE_OMS, 0 );
		}

		N++;// increment cycle counter
		return;
	}
}
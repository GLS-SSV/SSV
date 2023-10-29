#include "HYD_SYS_SOP.h"
#include <MathSSV.h>


namespace dps
{
	HYD_SYS_SOP::HYD_SYS_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "HYD_SYS_SOP" )
	{
		return;
	}

	HYD_SYS_SOP::~HYD_SYS_SOP( void )
	{
		return;
	}

	void HYD_SYS_SOP::OnPreStep( double simt, double simdt, double mjd )
	{
		// TODO LOW PRESS LIMIT CHECKS

		// MG/NLG UPLOCK
		unsigned short FF2_IOM12_CH0 = ReadCOMPOOL_IS( SCP_FF2_IOM12_CH0_DATA );
		unsigned short FF2_IOM12_CH2 = ReadCOMPOOL_IS( SCP_FF2_IOM12_CH2_DATA );
		unsigned short FF3_IOM12_CH0 = ReadCOMPOOL_IS( SCP_FF3_IOM12_CH0_DATA );
		unsigned short FF3_IOM12_CH2 = ReadCOMPOOL_IS( SCP_FF3_IOM12_CH2_DATA );

		unsigned short LMG_UPLK = (FF2_IOM12_CH2 & 0x0400) >> 10;
		unsigned short RMG_UPLK = (FF3_IOM12_CH2 & 0x0400) >> 10;
		unsigned short NLG_UPLK = (FF2_IOM12_CH0 & 0x1000) >> 12;
		unsigned short LMG_DR_UPLK = (FF3_IOM12_CH2 & 0x0800) >> 11;
		unsigned short RMG_DR_UPLK = (FF2_IOM12_CH2 & 0x0800) >> 11;
		unsigned short NLG_DR_UPLK = (FF3_IOM12_CH0 & 0x4000) >> 14;
		double ALT_WHEELS = ReadCOMPOOL_SD( SCP_ALT_WHEELS );

		unsigned short DOWNLOCK = 0;
		unsigned short HUD_GEAR_TRANS = ReadCOMPOOL_IS( SCP_HUD_GEAR_TRANS );
		unsigned short MLY_GEAR_NOTUP = ReadCOMPOOL_IS( SCP_MLY_GEAR_NOTUP );
		unsigned short UPLOCK_REL = 0;

		bool gear_not_up = (
			(LMG_UPLK == 0) && (RMG_UPLK == 0) && (NLG_UPLK == 0) ||
			(LMG_UPLK == 0) && (RMG_UPLK == 0) && (LMG_DR_UPLK == 1) ||
			(LMG_UPLK == 0) && (RMG_UPLK == 0) && (RMG_DR_UPLK == 1) ||
			(LMG_UPLK == 0) && (RMG_UPLK == 0) && (NLG_DR_UPLK == 0) ||
			(LMG_UPLK == 0) && (NLG_UPLK == 0) && (LMG_DR_UPLK == 1) ||
			(LMG_UPLK == 0) && (NLG_UPLK == 0) && (RMG_DR_UPLK == 1) ||
			(LMG_UPLK == 0) && (NLG_UPLK == 0) && (NLG_DR_UPLK == 0) ||
			(LMG_UPLK == 0) && (LMG_DR_UPLK == 1) && (RMG_DR_UPLK == 1) ||
			(LMG_UPLK == 0) && (LMG_DR_UPLK == 1) && (NLG_DR_UPLK == 0) ||
			(LMG_UPLK == 0) && (RMG_DR_UPLK == 1) && (NLG_DR_UPLK == 0) ||
			(RMG_UPLK == 0) && (NLG_UPLK == 0) && (LMG_DR_UPLK == 1) ||
			(RMG_UPLK == 0) && (NLG_UPLK == 0) && (RMG_DR_UPLK == 1) ||
			(RMG_UPLK == 0) && (NLG_UPLK == 0) && (NLG_DR_UPLK == 0) ||
			(RMG_UPLK == 0) && (LMG_DR_UPLK == 1) && (RMG_DR_UPLK == 1) ||
			(RMG_UPLK == 0) && (LMG_DR_UPLK == 1) && (NLG_DR_UPLK == 0) ||
			(RMG_UPLK == 0) && (RMG_DR_UPLK == 1) && (NLG_DR_UPLK == 0) ||
			(NLG_UPLK == 0) && (LMG_DR_UPLK == 1) && (RMG_DR_UPLK == 1) ||
			(NLG_UPLK == 0) && (LMG_DR_UPLK == 1) && (NLG_DR_UPLK == 0) ||
			(NLG_UPLK == 0) && (RMG_DR_UPLK == 1) && (NLG_DR_UPLK == 0) ||
			(LMG_DR_UPLK == 1) && (RMG_DR_UPLK == 1) && (NLG_DR_UPLK == 0)
			);

		HUD_GEAR_TRANS = (gear_not_up || (HUD_GEAR_TRANS == 1)) ? 1 : 0;

		// TODO UPLOCK_REL and DOWNLOCK

		MLY_GEAR_NOTUP = (((ALT_WHEELS <= ReadCOMPOOL_SS( SCP_GR_DPY_ALT )) && gear_not_up) || (MLY_GEAR_NOTUP == 1)) ? 1 : 0;

		// output
		WriteCOMPOOL_IS( SCP_DOWNLOCK, DOWNLOCK );
		WriteCOMPOOL_IS( SCP_HUD_GEAR_TRANS, HUD_GEAR_TRANS );
		WriteCOMPOOL_IS( SCP_MLY_GEAR_NOTUP, MLY_GEAR_NOTUP );
		WriteCOMPOOL_IS( SCP_UPLOCK_REL, UPLOCK_REL );
		return;
	}

	bool HYD_SYS_SOP::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 101:
			case 102:
			case 103:
			case 104:
			case 105:
			case 106:
			case 301:
			case 302:
			case 303:
			case 304:
			case 305:
			case 601:
			case 602:
			case 603:
				return true;
			default:
				return false;
		}
	}

	bool HYD_SYS_SOP::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void HYD_SYS_SOP::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}
}

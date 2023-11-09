#include "PrimaryCautionWarning.h"
#include "../SSVSound.h"
#include "Atlantis.h"


constexpr double TD_TIME = 0.1;// [s]


constexpr unsigned char CombinationMemory[128] = {// 6x128
	0x01, 0x09, 0x0F, 0x10, 0x02, 0x0D, 0x19, 0x1B, 0x0E, 0x1D,
	0x01, 0x09, 0x0F, 0x10, 0x02, 0x0D, 0x19, 0x1B, 0x0E, 0x1D,
	0x01, 0x09, 0x0F, 0x10, 0x02, 0x0D, 0x19, 0x1B, 0x0E, 0x1D,
	0x01, 0x09, 0x0F, 0x18, 0x02, 0x0D, 0x1A, 0x23, 0x0E, 0x1D,
	0x01, 0x09, 0x0F, 0x18, 0x02, 0x0D, 0x1A, 0x23, 0x0E, 0x1D,
	0x08, 0x09, 0x0F, 0x18, 0x02, 0x06, 0x1A, 0x23, 0x0E, 0x1D,
	0x08, 0x09, 0x17, 0x20, 0x02, 0x06, 0x22, 0x24, 0x16, 0x1D,
	0x08, 0x09, 0x17, 0x20, 0x0A, 0x06, 0x22, 0x1C, 0x16, 0x1D,
	0x08, 0x09, 0x17, 0x20, 0x0A, 0x06, 0x22, 0x1C, 0x16, 0x25,
	0x08, 0x12, 0x1F, 0x0B, 0x0A, 0x06, 0x21, 0x07, 0x1E, 0x26,
	0x0C, 0x14, 0x1F, 0x11, 0x0A, 0x04, 0x03, 0x03, 0x1E, 0x26,
	0x13, 0x15, 0x1F, 0x05, 0x0A, 0x04, 0x03, 0x03, 0x1E, 0x26,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};
constexpr unsigned char MSK_LO = 0x00;
constexpr unsigned char MSK_HI = 0x80;
constexpr unsigned char LimitValuePROM[256] = {// 8x256
	// content: bits 0-6 = value, bit 7 = high limit
	// lower
	MSK_LO | 0x05, MSK_HI | 0x64, MSK_LO | 0x60, MSK_LO | 0x42, MSK_LO | 0x45, MSK_HI | 0x64, MSK_LO | 0x32, MSK_LO | 0x3A, MSK_HI | 0x64, MSK_LO | 0x17,
	MSK_LO | 0x05, MSK_HI | 0x64, MSK_LO | 0x60, MSK_LO | 0x42, MSK_HI | 0x64, MSK_HI | 0x64, MSK_LO | 0x32, MSK_LO | 0x3A, MSK_HI | 0x64, MSK_LO | 0x17,
	MSK_LO | 0x05, MSK_HI | 0x64, MSK_LO | 0x60, MSK_LO | 0x42, MSK_HI | 0x64, MSK_HI | 0x64, MSK_HI | 0x64, MSK_HI | 0x64, MSK_HI | 0x64, MSK_LO | 0x17,
	MSK_LO | 0x05, MSK_HI | 0x64, MSK_LO | 0x60, MSK_HI | 0x64, MSK_LO | 0x36, MSK_HI | 0x64, MSK_LO | 0x32, MSK_LO | 0x3A, MSK_HI | 0x64, MSK_LO | 0x44,
	MSK_LO | 0x05, MSK_HI | 0x64, MSK_LO | 0x60, MSK_HI | 0x64, MSK_LO | 0x36, MSK_HI | 0x64, MSK_LO | 0x32, MSK_LO | 0x3A, MSK_HI | 0x64, MSK_LO | 0x44,
	MSK_LO | 0x05, MSK_HI | 0x64, MSK_LO | 0x60, MSK_HI | 0x64, MSK_HI | 0x64, MSK_HI | 0x64, MSK_HI | 0x64, MSK_HI | 0x64, MSK_HI | 0x64, MSK_LO | 0x44,
	MSK_LO | 0x05, MSK_HI | 0x64, MSK_LO | 0x42, MSK_HI | 0x64, MSK_HI | 0x64, MSK_HI | 0x64, MSK_LO | 0x32, MSK_HI | 0x64, MSK_HI | 0x64, MSK_HI | 0x64,
	MSK_LO | 0x05, MSK_HI | 0x64, MSK_LO | 0x42, MSK_HI | 0x64, MSK_LO | 0x23, MSK_HI | 0x64, MSK_LO | 0x32, MSK_LO | 0x3A, MSK_HI | 0x64, MSK_HI | 0x64,
	MSK_LO | 0x05, MSK_HI | 0x64, MSK_LO | 0x42, MSK_HI | 0x64, MSK_HI | 0x64, MSK_HI | 0x64, MSK_HI | 0x64, MSK_LO | 0x3A, MSK_HI | 0x64, MSK_HI | 0x64,
	MSK_LO | 0x05, MSK_HI | 0x64, MSK_LO | 0x60, MSK_HI | 0x64, MSK_HI | 0x64, MSK_HI | 0x64, MSK_HI | 0x64, MSK_HI | 0x64, MSK_HI | 0x64, MSK_LO | 0x3C,
	MSK_HI | 0x64, MSK_HI | 0x64, MSK_LO | 0x60, MSK_HI | 0x64, MSK_HI | 0x64, MSK_LO | 0x0D, MSK_LO | 0x14, MSK_LO | 0x07, MSK_HI | 0x64, MSK_LO | 0x3C,
	MSK_HI | 0x64, MSK_HI | 0x64, MSK_LO | 0x60, MSK_HI | 0x64, MSK_HI | 0x64, MSK_LO | 0x1E, MSK_LO | 0x14, MSK_LO | 0x07, MSK_HI | 0x64, MSK_LO | 0x3C,
	MSK_LO | 0x60, MSK_LO | 0x53, MSK_LO | 0x47, MSK_LO | 0x3A, MSK_HI | 0x64, MSK_HI | 0x64, MSK_HI | 0x64, MSK_HI | 0x64,// self-test
	// upper
	MSK_HI | 0x5E, MSK_HI | 0x56, MSK_LO | 0x02, MSK_LO | 0x02, MSK_HI | 0x4C, MSK_HI | 0x32, MSK_HI | 0x4E, MSK_HI | 0x47, MSK_HI | 0x54, MSK_LO | 0x02,
	MSK_HI | 0x5E, MSK_HI | 0x56, MSK_LO | 0x02, MSK_LO | 0x02, MSK_HI | 0x62, MSK_HI | 0x32, MSK_HI | 0x4E, MSK_HI | 0x47, MSK_HI | 0x54, MSK_LO | 0x02,
	MSK_HI | 0x5E, MSK_HI | 0x56, MSK_LO | 0x02, MSK_LO | 0x02, MSK_HI | 0x62, MSK_HI | 0x32, MSK_HI | 0x32, MSK_HI | 0x32, MSK_HI | 0x54, MSK_LO | 0x02,
	MSK_HI | 0x5E, MSK_HI | 0x56, MSK_LO | 0x02, MSK_HI | 0x64, MSK_HI | 0x48, MSK_HI | 0x32, MSK_HI | 0x4E, MSK_HI | 0x47, MSK_HI | 0x3A, MSK_HI | 0x51,
	MSK_HI | 0x5E, MSK_HI | 0x56, MSK_LO | 0x02, MSK_HI | 0x64, MSK_HI | 0x48, MSK_HI | 0x32, MSK_HI | 0x4E, MSK_HI | 0x47, MSK_HI | 0x3A, MSK_HI | 0x51,
	MSK_HI | 0x5D, MSK_HI | 0x56, MSK_LO | 0x02, MSK_HI | 0x64, MSK_HI | 0x62, MSK_HI | 0x32, MSK_HI | 0x32, MSK_HI | 0x32, MSK_HI | 0x3A, MSK_HI | 0x51,
	MSK_HI | 0x5D, MSK_HI | 0x56, MSK_HI | 0x55, MSK_HI | 0x64, MSK_HI | 0x62, MSK_HI | 0x32, MSK_HI | 0x4E, MSK_HI | 0x32, MSK_HI | 0x64, MSK_HI | 0x53,
	MSK_HI | 0x5D, MSK_HI | 0x56, MSK_HI | 0x55, MSK_HI | 0x64, MSK_HI | 0x58, MSK_HI | 0x32, MSK_HI | 0x4E, MSK_HI | 0x47, MSK_HI | 0x64, MSK_HI | 0x3C,
	MSK_HI | 0x5D, MSK_HI | 0x56, MSK_HI | 0x55, MSK_HI | 0x64, MSK_HI | 0x55, MSK_HI | 0x32, MSK_HI | 0x32, MSK_HI | 0x47, MSK_HI | 0x64, MSK_HI | 0x32,
	MSK_HI | 0x5D, MSK_HI | 0x32, MSK_LO | 0x02, MSK_HI | 0x32, MSK_HI | 0x55, MSK_HI | 0x32, MSK_HI | 0x32, MSK_HI | 0x32, MSK_HI | 0x64, MSK_LO | 0x02,
	MSK_HI | 0x32, MSK_HI | 0x32, MSK_LO | 0x02, MSK_HI | 0x32, MSK_HI | 0x55, MSK_HI | 0x35, MSK_LO | 0x02, MSK_HI | 0x26, MSK_HI | 0x64, MSK_LO | 0x02,
	MSK_HI | 0x32, MSK_HI | 0x32, MSK_LO | 0x02, MSK_HI | 0x32, MSK_HI | 0x64, MSK_HI | 0x36, MSK_LO | 0x02, MSK_HI | 0x26, MSK_HI | 0x64, MSK_LO | 0x02,
	MSK_LO | 0x02, MSK_LO | 0x02, MSK_LO | 0x02, MSK_LO | 0x02, MSK_HI | 0x36, MSK_HI | 0x2A, MSK_HI | 0x1D, MSK_HI | 0x11// self-test
	};

// 1-4 low test 0.10v below ref value
// 5-8 high test 0.10v above ref value
/*
ST 1 4.90v	L	4.80v	96	0x60
ST 2 4.25v	L	4.15v	83	0x53
ST 3 3.65v	L	3.55v	71	0x47
ST 4 3.00v	L	2.90v	58	0x3A
ST 5 2.60v	H	2.70v	54	0x36
ST 6 2.00v	H	2.10v	42	0x2A
ST 7 1.35v	H	1.45v	29	0x1D
ST 8 0.75v	H	0.85v	17	0x11
*/

void boolarray2hexstr( std::string& str, const bool* array, unsigned int length )
{
	char ctmp[4];

	for (unsigned int i = 0; i < length; i += 8)
	{
		unsigned char btmp = (array[i + 7] ? 0x80 : 0x00) +
			(array[i + 6] ? 0x40 : 0x00) +
			(array[i + 5] ? 0x20 : 0x00) +
			(array[i + 4] ? 0x10 : 0x00) +
			(array[i + 3] ? 0x08 : 0x00) +
			(array[i + 2] ? 0x04 : 0x00) +
			(array[i + 1] ? 0x02 : 0x00) +
			(array[i] ? 0x01 : 0x00);
		sprintf_s( ctmp, 4, "%02hhx", btmp );

		str = ctmp + str;
	}
	return;
}

void nibblearray2hexstr( std::string& str, const unsigned char* array, unsigned int length )
{
	char ctmp[4];

	for (unsigned int i = 0; i < length; i += 2)
	{
		unsigned char btmp = ((array[i + 1] & 0x0F) << 4) + (array[i] & 0xF);
		sprintf_s( ctmp, 4, "%02hhx", btmp );

		str = ctmp + str;
	}
	return;
}

void bytearray2hexstr( std::string& str, const unsigned char* array, unsigned int length )
{
	char ctmp[4];

	for (unsigned int i = 0; i < length; i++)
	{
		sprintf_s( ctmp, 4, "%02hhx", array[i] );

		str = ctmp + str;
	}
	return;
}

bool hexstr2boolarray( bool* array, unsigned int length, const std::string& str )
{
	unsigned char btmp = 0;
	char ctmp[4];

	if ((str.length() * 4) != length)
	{
		return false;
	}

	ctmp[2] = 0;
	for (unsigned int i = 0, j = length - 1; i < str.length(); i += 2, j -= 8)
	{
		ctmp[0] = str[i];
		ctmp[1] = str[i + 1];

		sscanf_s( ctmp, "%02hhx", &btmp );

		array[j] = (btmp & 0x80) != 0;
		array[j - 1] = (btmp & 0x40) != 0;
		array[j - 2] = (btmp & 0x20) != 0;
		array[j - 3] = (btmp & 0x10) != 0;
		array[j - 4] = (btmp & 0x08) != 0;
		array[j - 5] = (btmp & 0x04) != 0;
		array[j - 6] = (btmp & 0x02) != 0;
		array[j - 7] = (btmp & 0x01) != 0;
	}
	return true;
}

bool hexstr2nibblearray( unsigned char* array, unsigned int length, const std::string& str )
{
	unsigned char btmp = 0;
	char ctmp[4];

	if (str.length() != length)
	{
		return false;
	}

	ctmp[2] = 0;
	for (unsigned int i = 0, j = length - 1; i < str.length(); i += 2, j -= 2)
	{
		ctmp[0] = str[i];
		ctmp[1] = str[i + 1];

		sscanf_s( ctmp, "%02hhx", &btmp );

		array[j] = (btmp >> 4) & 0x0F;
		array[j - 1] = btmp & 0x0F;
	}
	return true;
}

bool hexstr2bytearray( unsigned char* array, unsigned int length, const std::string& str )
{
	unsigned char btmp = 0;
	char ctmp[4];

	if (str.length() != (length * 2))
	{
		return false;
	}

	ctmp[2] = 0;
	for (unsigned int i = 0, j = length - 1; i < str.length(); i += 2, j -= 1)
	{
		ctmp[0] = str[i];
		ctmp[1] = str[i + 1];

		sscanf_s( ctmp, "%02hhx", &btmp );

		array[j] = btmp;
	}
	return true;
}

bool TDrun( bool input, bool& TDout, double& TDtime, double dt )
{
	if (input)
	{
		if (!TDout)
		{
			// count
			TDtime -= dt;
			if (TDtime <= 0.0)
			{
				TDout = true;
				TDtime = TD_TIME;
			}
		}
	}
	else
	{
		TDout = false;
		TDtime = TD_TIME;
	}
	return TDout;
}


PrimaryCautionWarning::PrimaryCautionWarning( AtlantisSubsystemDirector* _director ):AtlantisSubsystem( _director, "PrimaryCaution&Warning" ),
bCW_TONE(false), bSM_TONE(false)
{
	for (auto &x : InhibitMemory) x = false;
	for (auto &x : NCountMemory) x = 0;
	for (auto &x : NCountOverflowMemory) x = false;
	for (auto &x : RecallMemory) x = false;
	for (auto &x : PrimaryCWTriggerMemory) x = false;
	for (auto &x : LimitValueRAM) x = 0;

	TurnOn_TDout[0] = false;
	TurnOn_TDout[1] = false;
	TurnOff_TDout[0] = false;
	TurnOff_TDout[1] = false;
	TurnOn_TDtime[0] = TD_TIME;
	TurnOn_TDtime[1] = TD_TIME;
	TurnOff_TDtime[0] = TD_TIME;
	TurnOff_TDtime[1] = TD_TIME;

	ST_FAIL_1[0] = FlipFlopD( true );
	ST_FAIL_1[1] = FlipFlopD( true );
	return;
}

PrimaryCautionWarning::~PrimaryCautionWarning( void )
{
}

void PrimaryCautionWarning::Realize( void )
{
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "CW_SW_1", 16 );
	PARAMSTATUS_INHIBITED.Connect( pBundle, 0 );// INHIBITED
	PARAMSTATUS_INACTIVE.Connect( pBundle, 1 );// -
	PARAMSTATUS_TRIPPED.Connect( pBundle, 2 );// TRIPPED

	MEMORY_CLEAR.Connect( pBundle, 3 );// CLEAR
	MEMORY_INACTIVE.Connect( pBundle, 4 );// -
	MEMORY_READ.Connect( pBundle, 5 );// READ

	LAMPTEST_RIGHT.Connect( pBundle, 6 );// RIGHT
	LAMPTEST_INACTIVE.Connect( pBundle, 7 );// -
	LAMPTEST_LEFT.Connect( pBundle, 8 );// LEFT

	LIMIT_LOWER.Connect( pBundle, 9 );// LOWER
	LIMIT_UPPER.Connect( pBundle, 10 );// UPPER

	FUNC_READ.Connect( pBundle, 11 );// READ
	FUNC_INACTIVE.Connect( pBundle, 12 );// -
	FUNC_SET.Connect( pBundle, 13 );// SET

	MASTER_ALARM_RESET_A2.Connect( pBundle, 14 );// A7U
	MASTER_ALARM_RESET_B2.Connect( pBundle, 15 );// MO52J

	pBundle = BundleManager()->CreateBundle( "CW_SW_2", 16 );
	PARAM_INHIBIT.Connect( pBundle, 0 );// INHIBIT
	PARAM_INACTIVE.Connect( pBundle, 1 );// -
	PARAM_ENABLE.Connect( pBundle, 2 );// ENABLE

	CAUTIONWARNINGMEMORY_CLEAR.Connect( pBundle, 3 );// CLEAR
	CAUTIONWARNINGMEMORY_INACTIVE.Connect( pBundle, 4 );// -
	CAUTIONWARNINGMEMORY_READ.Connect( pBundle, 5 );// READ

	//CAUTIONWARNINGMODE_ASCENT.Connect( pBundle, 6 );// ASCENT
	CAUTIONWARNINGMODE_NORM.Connect( pBundle, 7 );// NORM
	CAUTIONWARNINGMODE_ACK.Connect( pBundle, 8 );// ACK

	MASTER_ALARM_RESET_A1.Connect( pBundle, 9 );// F2
	MASTER_ALARM_RESET_B1.Connect( pBundle, 10 );// F4

	CW_POWER_A.Connect( pBundle, 11 );
	CW_POWER_B.Connect( pBundle, 12 );

	pBundle = BundleManager()->CreateBundle( "R13_PARAMETER_SELECT", 16 );
	for (int i = 0; i < 9; i++) ParameterSelect[i].Connect( pBundle, i );

	pBundle = BundleManager()->CreateBundle( "R13_LIMIT_SET_VALUE", 16 );
	for (int i = 0; i < 8; i++) LimitValue[i].Connect( pBundle, i );

	pBundle = BundleManager()->CreateBundle( "ACA2_4", 16 );
	SMAlert_ACA2.Connect( pBundle, 8 );

	pBundle = BundleManager()->CreateBundle( "ACA3_4", 16 );
	SMAlert_ACA3.Connect( pBundle, 8 );

	pBundle = BundleManager()->CreateBundle( "ACA1_4", 16 );
	MasterAlarm_F4_A.Connect( pBundle, 14 );// 32
	pBundle = BundleManager()->CreateBundle( "ACA1_5", 16 );
	MasterAlarm_F2_A.Connect( pBundle, 0 );// 33
	MasterAlarm_MO52J_A.Connect( pBundle, 6 );// 36

	pBundle = BundleManager()->CreateBundle( "ACA2_5", 16 );
	MasterAlarm_F2_B.Connect( pBundle, 0 );// 33

	pBundle = BundleManager()->CreateBundle( "ACA3_4", 16 );
	MasterAlarm_F4_B.Connect( pBundle, 14 );// 32
	pBundle = BundleManager()->CreateBundle( "ACA3_5", 16 );
	MasterAlarm_MO52J_B.Connect( pBundle, 6 );// 36

	pBundle = BundleManager()->CreateBundle( "ACA4_4", 16 );
	MasterAlarm_A7U_A.Connect( pBundle, 14 );// 32

	pBundle = BundleManager()->CreateBundle( "ACA5_4", 16 );
	MasterAlarm_A7U_B.Connect( pBundle, 14 );// 32

	pBundle = BundleManager()->CreateBundle( "CW_ANNUNCIATOR_A", 16 );
	for (int i = 0; i < 16; i++) AnnunciatorLightSignals[i].Connect( pBundle, i );

	pBundle = BundleManager()->CreateBundle( "CW_ANNUNCIATOR_B", 16 );
	for (int i = 16; i < 32; i++) AnnunciatorLightSignals[i].Connect( pBundle, i - 16 );

	pBundle = BundleManager()->CreateBundle( "CW_ANNUNCIATOR_C", 16 );
	for (int i = 32; i < 40; i++) AnnunciatorLightSignals[i].Connect( pBundle, i - 32 );

	pBundle = STS()->BundleManager()->CreateBundle( "MDM_FF1_IOM5_CH1", 16 );
	ParameterData[56].Connect( pBundle, 11 );// DPS "LEFT RCS"

	pBundle = STS()->BundleManager()->CreateBundle( "MDM_FF1_IOM10_CH2", 16 );
	BU_CW_A_CMD_1.Connect( pBundle, 3 );
	SM_TONE_A_CMD_1.Connect( pBundle, 4 );
	SM_LIGHT_A_CMD_1.Connect( pBundle, 5 );

	pBundle = STS()->BundleManager()->CreateBundle( "MDM_FF2_IOM10_CH2", 16 );
	BU_CW_A_CMD_2.Connect( pBundle, 3 );
	SM_TONE_A_CMD_2.Connect( pBundle, 4 );
	SM_LIGHT_A_CMD_2.Connect( pBundle, 5 );

	pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM5_CH1", 16 );
	ParameterData[96].Connect( pBundle, 0 );// DPS "RCS JET"
	ParameterData[67].Connect( pBundle, 1 );// DPS "OMS TVC"
	ParameterData[27].Connect( pBundle, 2 );// DPS "LEFT OMS"
	ParameterData[57].Connect( pBundle, 3 );// DPS "RIGHT OMS"
	ParameterData[111].Connect( pBundle, 4 );// DPS "FCS CHANNEL"
	ParameterData[101].Connect( pBundle, 5 );// DPS "FCS SATURATION"
	ParameterData[103].Connect( pBundle, 6 );// DPS "IMU"
	ParameterData[110].Connect( pBundle, 7 );// DPS "RIGHT/AFT RHC"
	ParameterData[100].Connect( pBundle, 8 );// DPS "LEFT RHC"
	ParameterData[91].Connect( pBundle, 9 );// DPS "AIR DATA"
	ParameterData[93].Connect( pBundle, 10 );// DPS "RGA/ACCEL"
	ParameterData[86].Connect( pBundle, 11 );// DPS "RIGHT RCS"
	ParameterData[26].Connect( pBundle, 12 );// DPS "FWD RCS"

	pBundle = STS()->BundleManager()->CreateBundle( "MDM_FF3_IOM10_CH2", 16 );
	BU_CW_A_CMD_3.Connect( pBundle, 3 );
	SM_TONE_A_CMD_3.Connect( pBundle, 4 );
	SM_LIGHT_A_CMD_3.Connect( pBundle, 5 );

	pBundle = BundleManager()->CreateBundle( "MDM_FF4_IOM10_CH2", 16 );
	BU_CW_A_CMD_4.Connect( pBundle, 3 );
	SM_TONE_A_CMD_4.Connect( pBundle, 4 );
	SM_LIGHT_A_CMD_4.Connect( pBundle, 5 );

	pBundle = BundleManager()->CreateBundle( "MDM_PF1_IOM2_CH0", 16 );
	BU_CW_B_CMD_1.Connect( pBundle, 12 );
	SM_LIGHT_B_CMD_1.Connect( pBundle, 14 );
	SM_TONE_B_CMD_1.Connect( pBundle, 13 );

	pBundle = BundleManager()->CreateBundle( "MDM_PF2_IOM2_CH0", 16 );
	BU_CW_B_CMD_2.Connect( pBundle, 12 );
	SM_LIGHT_B_CMD_2.Connect( pBundle, 14 );
	SM_TONE_B_CMD_2.Connect( pBundle, 13 );

	pBundle = STS()->BundleManager()->CreateBundle( "MDM_PF2_IOM10_CH2", 16 );
	ParameterData[97].Connect( pBundle, 2 );// DPS "PAYLOAD WARNING"

	// subsys data x 105
	pBundle = BundleManager()->CreateBundle( "MPS_HE_SENSORS", 12 );
	ParameterData[9].Connect( pBundle, 0 );
	ParameterData[39].Connect( pBundle, 1 );
	ParameterData[19].Connect( pBundle, 3 );
	ParameterData[49].Connect( pBundle, 4 );
	ParameterData[29].Connect( pBundle, 6 );
	ParameterData[59].Connect( pBundle, 7 );

	pBundle = BundleManager()->CreateBundle( "MPS_SENSORS", 2 );
	ParameterData[69].Connect( pBundle, 0 );
	ParameterData[79].Connect( pBundle, 1 );

	pBundle = BundleManager()->CreateBundle( "HYD_PMP_PRESS", 16 );
	ParameterData[99].Connect( pBundle, 0 );
	ParameterData[109].Connect( pBundle, 3 );
	ParameterData[119].Connect( pBundle, 6 );

	// self-test data
	pBundle = BundleManager()->CreateBundle( "CW_SELF_TEST", 16 );
	ParameterData[120].Connect( pBundle, 0 );
	ParameterData[121].Connect( pBundle, 1 );
	ParameterData[122].Connect( pBundle, 2 );
	ParameterData[123].Connect( pBundle, 3 );
	ParameterData[124].Connect( pBundle, 4 );
	ParameterData[125].Connect( pBundle, 5 );
	ParameterData[126].Connect( pBundle, 6 );
	ParameterData[127].Connect( pBundle, 7 );
	ST[0].Connect( pBundle, 0 );
	ST[1].Connect( pBundle, 1 );
	ST[2].Connect( pBundle, 2 );
	ST[3].Connect( pBundle, 3 );
	ST[4].Connect( pBundle, 4 );
	ST[5].Connect( pBundle, 5 );
	ST[6].Connect( pBundle, 6 );
	ST[7].Connect( pBundle, 7 );

	pBundle = BundleManager()->CreateBundle( "CW_STATUS_MATRIX_A", 16 );
	for (int i = 0; i < 16; i++) MatrixLightSignals[i].Connect( pBundle, i );

	pBundle = BundleManager()->CreateBundle( "CW_STATUS_MATRIX_B", 16 );
	for (int i = 0; i < 16; i++) MatrixLightSignals[i + 16].Connect( pBundle, i );

	pBundle = BundleManager()->CreateBundle( "CW_STATUS_MATRIX_C", 16 );
	for (int i = 0; i < 16; i++) MatrixLightSignals[i + 32].Connect( pBundle, i );

	pBundle = BundleManager()->CreateBundle( "CW_STATUS_MATRIX_D", 16 );
	for (int i = 0; i < 16; i++) MatrixLightSignals[i + 48].Connect( pBundle, i );

	pBundle = BundleManager()->CreateBundle( "CW_STATUS_MATRIX_E", 16 );
	for (int i = 0; i < 16; i++) MatrixLightSignals[i + 64].Connect( pBundle, i );

	pBundle = BundleManager()->CreateBundle( "CW_STATUS_MATRIX_F", 16 );
	for (int i = 0; i < 16; i++) MatrixLightSignals[i + 80].Connect( pBundle, i );

	pBundle = BundleManager()->CreateBundle( "CW_STATUS_MATRIX_G", 16 );
	for (int i = 0; i < 16; i++) MatrixLightSignals[i + 96].Connect( pBundle, i );

	pBundle = BundleManager()->CreateBundle( "CW_STATUS_MATRIX_H", 16 );
	for (int i = 0; i < 8; i++) MatrixLightSignals[i + 112].Connect( pBundle, i );
	return;
}

bool PrimaryCautionWarning::OnParseLine( const char* line )
{
	if (!_strnicmp( line, "INHIBITMEMORY", 13 ))
	{
		if (!hexstr2boolarray( InhibitMemory, 128, line + 14 ))
		{
			oapiWriteLog( "(SSV_OV) [ERROR] Parsing PrimaryCautionWarning::OnParseLine parameter INHIBITMEMORY" );
		}
		return true;
	}
	else if (!_strnicmp( line, "NCOUNTMEMORY", 12 ))
	{
		if (!hexstr2nibblearray( NCountMemory, 128, line + 13 ))
		{
			oapiWriteLog( "(SSV_OV) [ERROR] Parsing PrimaryCautionWarning::OnParseLine parameter NCOUNTMEMORY" );
		}
		return true;
	}
	else if (!_strnicmp( line, "NCOUNTOVERFLOWMEMORY", 20 ))
	{
		if (!hexstr2boolarray( NCountOverflowMemory, 128, line + 21 ))
		{
			oapiWriteLog( "(SSV_OV) [ERROR] Parsing PrimaryCautionWarning::OnParseLine parameter NCOUNTOVERFLOWMEMORY" );
		}
		return true;
	}
	else if (!_strnicmp( line, "RECALLMEMORY", 12 ))
	{
		if (!hexstr2boolarray( RecallMemory, 128, line + 13 ))
		{
			oapiWriteLog( "(SSV_OV) [ERROR] Parsing PrimaryCautionWarning::OnParseLine parameter RECALLMEMORY" );
		}
		return true;
	}
	else if (!_strnicmp( line, "PRIMARYCWTRIGGERMEMORY", 22 ))
	{
		if (!hexstr2boolarray( PrimaryCWTriggerMemory, 128, line + 23 ))
		{
			oapiWriteLog( "(SSV_OV) [ERROR] Parsing PrimaryCautionWarning::OnParseLine parameter PRIMARYCWTRIGGERMEMORY" );
		}
		return true;
	}
	else if (!_strnicmp( line, "LIMITVALUERAM", 13 ))
	{
		if (!hexstr2bytearray( LimitValueRAM, 256, line + 14 ))
		{
			oapiWriteLog( "(SSV_OV) [ERROR] Parsing PrimaryCautionWarning::OnParseLine parameter LIMITVALUERAM" );
		}
		return true;
	}
	else if (!_strnicmp( line, "PRI_CW_A", 8 ))
	{
		PRI_CW[0].LoadState( line + 8 );
		return true;
	}
	else if (!_strnicmp( line, "PRI_CW_B", 8 ))
	{
		PRI_CW[1].LoadState( line + 8 );
		return true;
	}
	else if (!_strnicmp( line, "CW_TONE_ENABLE_A", 16 ))
	{
		CW_TONE_ENABLE[0].LoadState( line + 16 );
		return true;
	}
	else if (!_strnicmp( line, "CW_TONE_ENABLE_B", 16 ))
	{
		CW_TONE_ENABLE[1].LoadState( line + 16 );
		return true;
	}
	else if (!_strnicmp( line, "BU_CW_TONE_A", 12 ))
	{
		BU_CW_TONE[0].LoadState( line + 12 );
		return true;
	}
	else if (!_strnicmp( line, "BU_CW_TONE_B", 12 ))
	{
		BU_CW_TONE[1].LoadState( line + 12 );
		return true;
	}
	else if (!_strnicmp( line, "BU_CW_LIGHT_A", 13 ))
	{
		BU_CW_LIGHT[0].LoadState( line + 13 );
		return true;
	}
	else if (!_strnicmp( line, "BU_CW_LIGHT_B", 13 ))
	{
		BU_CW_LIGHT[1].LoadState( line + 13 );
		return true;
	}
	else if (!_strnicmp( line, "SW_TONE_A", 9 ))
	{
		SW_TONE[0].LoadState( line + 9 );
		return true;
	}
	else if (!_strnicmp( line, "SW_TONE_B", 9 ))
	{
		SW_TONE[1].LoadState( line + 9 );
		return true;
	}
	else if (!_strnicmp( line, "ST_FAIL_1_A", 11 ))
	{
		ST_FAIL_1[0].LoadState( line + 11 );
		return true;
	}
	else if (!_strnicmp( line, "ST_FAIL_1_B", 11 ))
	{
		ST_FAIL_1[1].LoadState( line + 11 );
		return true;
	}
	else if (!_strnicmp( line, "ST_FAIL_2_A", 11 ))
	{
		ST_FAIL_2[0].LoadState( line + 11 );
		return true;
	}
	else if (!_strnicmp( line, "ST_FAIL_2_B", 11 ))
	{
		ST_FAIL_2[1].LoadState( line + 11 );
		return true;
	}
	else return false;
}

void PrimaryCautionWarning::OnSaveState( FILEHANDLE scn ) const
{
	std::string stmp = "";
	boolarray2hexstr( stmp, InhibitMemory, 128 );
	oapiWriteScenario_string( scn, "INHIBITMEMORY", (char*)stmp.c_str() );

	stmp = "";
	nibblearray2hexstr( stmp, NCountMemory, 128 );
	oapiWriteScenario_string( scn, "NCOUNTMEMORY", (char*)stmp.c_str() );

	stmp = "";
	boolarray2hexstr( stmp, NCountOverflowMemory, 128 );
	oapiWriteScenario_string( scn, "NCOUNTOVERFLOWMEMORY", (char*)stmp.c_str() );

	stmp = "";
	boolarray2hexstr( stmp, RecallMemory, 128 );
	oapiWriteScenario_string( scn, "RECALLMEMORY", (char*)stmp.c_str() );

	stmp = "";
	boolarray2hexstr( stmp, PrimaryCWTriggerMemory, 128 );
	oapiWriteScenario_string( scn, "PRIMARYCWTRIGGERMEMORY", (char*)stmp.c_str() );

	stmp = "";
	bytearray2hexstr( stmp, LimitValueRAM, 256 );
	oapiWriteScenario_string( scn, "LIMITVALUERAM", (char*)stmp.c_str() );


	char cbuf[256];

	PRI_CW[0].SaveState( cbuf );
	oapiWriteScenario_string( scn, "PRI_CW_A", cbuf );
	PRI_CW[1].SaveState( cbuf );
	oapiWriteScenario_string( scn, "PRI_CW_B", cbuf );

	CW_TONE_ENABLE[0].SaveState( cbuf );
	oapiWriteScenario_string( scn, "CW_TONE_ENABLE_A", cbuf );
	CW_TONE_ENABLE[1].SaveState( cbuf );
	oapiWriteScenario_string( scn, "CW_TONE_ENABLE_B", cbuf );

	BU_CW_TONE[0].SaveState( cbuf );
	oapiWriteScenario_string( scn, "BU_CW_TONE_A", cbuf );
	BU_CW_TONE[1].SaveState( cbuf );
	oapiWriteScenario_string( scn, "BU_CW_TONE_B", cbuf );

	BU_CW_LIGHT[0].SaveState( cbuf );
	oapiWriteScenario_string( scn, "BU_CW_LIGHT_A", cbuf );
	BU_CW_LIGHT[1].SaveState( cbuf );
	oapiWriteScenario_string( scn, "BU_CW_LIGHT_B", cbuf );

	SW_TONE[0].SaveState( cbuf );
	oapiWriteScenario_string( scn, "SW_TONE_A", cbuf );
	SW_TONE[1].SaveState( cbuf );
	oapiWriteScenario_string( scn, "SW_TONE_B", cbuf );

	ST_FAIL_1[0].SaveState( cbuf );
	oapiWriteScenario_string( scn, "ST_FAIL_1_A", cbuf );
	ST_FAIL_1[1].SaveState( cbuf );
	oapiWriteScenario_string( scn, "ST_FAIL_1_B", cbuf );

	ST_FAIL_2[0].SaveState( cbuf );
	oapiWriteScenario_string( scn, "ST_FAIL_2_A", cbuf );
	ST_FAIL_2[1].SaveState( cbuf );
	oapiWriteScenario_string( scn, "ST_FAIL_2_B", cbuf );
	return;
}

void PrimaryCautionWarning::MasterAlarmToneLogic( unsigned int side, bool Power_me, bool Power_other, bool Pri_CW_Trigger, bool BU_CW, bool SM_TONE, bool& MasterAlarmRelaySignal, bool& cw_tone_request, bool& sm_tone_request, bool& PriCWlight, bool& BUCWlight, double dt )
{
	if (!Power_me)
	{
		PRI_CW[side].LoadState( "0" );
		BU_CW_LIGHT[side].LoadState( "0" );
		BU_CW_TONE[side].LoadState( "0" );
		CW_TONE_ENABLE[side].LoadState( "0" );
		ST_FAIL_1[side].LoadState( "0" );
		ST_FAIL_2[side].LoadState( "0" );
		SW_TONE[side].LoadState( "0" );

		MasterAlarmRelaySignal = false;
		cw_tone_request = false;
		sm_tone_request = false;
		PriCWlight = false;
		BUCWlight = false;
		return;
	}

	// TODO Klaxon and Siren logic
	bool MAR_Pulse = MASTER_ALARM_RESET_A1 || MASTER_ALARM_RESET_A2 || MASTER_ALARM_RESET_B1 || MASTER_ALARM_RESET_B2;// TODO generate pulse

	bool PRI_CW_Q = PRI_CW[side].run( Pri_CW_Trigger, true, MAR_Pulse );

	bool TurnOn = TDrun( !BU_CW, TurnOn_TDout[side], TurnOn_TDtime[side], dt );
	bool TurnOff = TDrun( BU_CW, TurnOff_TDout[side], TurnOff_TDtime[side], dt );

	bool BU_CW_LIGHT_Q = BU_CW_LIGHT[side].run( TurnOn || TurnOff, !BU_CW, false );
	bool BU_CW_TONE_Q = BU_CW_TONE[side].run( BU_CW_LIGHT_Q, !BU_CW, MAR_Pulse );

	bool CW_TONE_ENABLE_Q = CW_TONE_ENABLE[side].run( PRI_CW_Q || BU_CW_TONE_Q, true, MAR_Pulse );

	bool selftest = (!Power_other || false/*osc a fail*/ || false/*osc b fail*/ || false/*b st fail*/);// HACK omitted negation of OR gate

	bool ST_FAIL_1_Q = ST_FAIL_1[side].run( MAR_Pulse, true, selftest );
	bool ST_FAIL_2_Q = ST_FAIL_2[side].run( !ST_FAIL_1_Q, true, MAR_Pulse );

	bool SW_TONE_Q = SW_TONE[side].run( SM_TONE, true, MAR_Pulse );

	bool OR_1 = false/*EMERG_ENABLE*/ || CW_TONE_ENABLE_Q || ST_FAIL_2_Q;

	bool tone_enable = SW_TONE_Q || OR_1;

	MasterAlarmRelaySignal = OR_1;

	// request tones
	cw_tone_request = tone_enable && (ST_FAIL_2_Q || (BU_CW_TONE_Q || PRI_CW_Q));
	sm_tone_request = tone_enable && SM_TONE;

	PriCWlight = !ST_FAIL_1_Q;
	BUCWlight = BU_CW_LIGHT_Q;

	//oapiWriteLogV( "MasterAlarmToneLogic%d %.3f   %d   %d %d%d  %d %d", side, STS()->GetMET(), MAR_Pulse, BU_CW, TurnOn, TurnOff, BU_CW_LIGHT_Q, BU_CW_TONE_Q );
	return;
}

void PrimaryCautionWarning::OnPreStep( double simt, double simdt, double mjd )
{
	bool InvalidParam = false;
	bool Pri_CW_Trigger = false;

	//// power
	// (simplified) PS outputs
	bool PS_A = CW_POWER_A;
	bool PS_B = CW_POWER_B;


	// save OLIs for usage in data output
	bool oli[128];
	bool ni_oli[128];
	for (unsigned int i = 0; i < 128; i++)
	{
		oli[i] = false;
		ni_oli[i] = false;
	}


	//// inputs
	// convert selector wheels to binary
	unsigned short bParameterSelect = 0;
	bParameterSelect += ParameterSelect[0].IsSet() ? 1 : 0;
	bParameterSelect += ParameterSelect[1].IsSet() ? 2 : 0;
	bParameterSelect += ParameterSelect[2].IsSet() ? 4 : 0;
	bParameterSelect += ParameterSelect[3].IsSet() ? 8 : 0;
	bParameterSelect += ParameterSelect[4].IsSet() ? 10 : 0;
	bParameterSelect += ParameterSelect[5].IsSet() ? 20 : 0;
	bParameterSelect += ParameterSelect[6].IsSet() ? 40 : 0;
	bParameterSelect += ParameterSelect[7].IsSet() ? 80 : 0;
	bParameterSelect += ParameterSelect[8].IsSet() ? 100 : 0;
	InvalidParam = (bParameterSelect > 119);// detect invalid parameter
	bParameterSelect &= 0x7F;// limit output to 7b

	unsigned short bLimitValue = 0;
	bLimitValue += LimitValue[0].IsSet() ? 1 : 0;
	bLimitValue += LimitValue[1].IsSet() ? 2 : 0;
	bLimitValue += LimitValue[2].IsSet() ? 4 : 0;
	bLimitValue += LimitValue[3].IsSet() ? 8 : 0;
	bLimitValue += LimitValue[4].IsSet() ? 16 : 0;
	bLimitValue += LimitValue[5].IsSet() ? 20 : 0;
	bLimitValue += LimitValue[6].IsSet() ? 40 : 0;
	bLimitValue += LimitValue[7].IsSet() ? 80 : 0;

	// switches
	bool paramEna = PARAM_ENABLE && !PARAM_INACTIVE && !PARAM_INHIBIT;
	bool paramInh = !PARAM_ENABLE && !PARAM_INACTIVE && PARAM_INHIBIT;
	bool limitsetUpper = LIMIT_UPPER && !LIMIT_LOWER;
	bool funcSet = FUNC_SET && !FUNC_READ && !FUNC_INACTIVE;
	bool funcRead = !FUNC_SET && FUNC_READ && !FUNC_INACTIVE;
	bool paramstatusTri = !PARAMSTATUS_INHIBITED && !PARAMSTATUS_INACTIVE && PARAMSTATUS_TRIPPED;
	bool paramstatusInh = PARAMSTATUS_INHIBITED && !PARAMSTATUS_INACTIVE && !PARAMSTATUS_TRIPPED;
	bool lamptestLeft = LAMPTEST_LEFT && !LAMPTEST_INACTIVE && !LAMPTEST_RIGHT;
	bool lamptestRight = !LAMPTEST_LEFT && !LAMPTEST_INACTIVE && LAMPTEST_RIGHT;
	bool memoryClear = MEMORY_CLEAR && !MEMORY_INACTIVE && !MEMORY_READ;
	bool memoryRead = !MEMORY_CLEAR && !MEMORY_INACTIVE && MEMORY_READ;
	bool cwmemoryClear = CAUTIONWARNINGMEMORY_CLEAR && !CAUTIONWARNINGMEMORY_INACTIVE && !CAUTIONWARNINGMEMORY_READ;
	bool cwmemoryRead = !CAUTIONWARNINGMEMORY_CLEAR && !CAUTIONWARNINGMEMORY_INACTIVE && CAUTIONWARNINGMEMORY_READ;
	unsigned int LimitSelect = bParameterSelect + (limitsetUpper ? 0x80 : 0);

	if (PS_A)
	{
		//// drive self-test
		ST[0].SetLine( 4.90f );
		ST[1].SetLine( 4.25f );
		ST[2].SetLine( 3.65f );
		ST[3].SetLine( 3.00f );
		ST[4].SetLine( 2.60f );
		ST[5].SetLine( 2.00f );
		ST[6].SetLine( 1.35f );
		ST[7].SetLine( 0.75f );


		//// user action logic
		// param inh/ena
		if (!InvalidParam && (paramEna || paramInh)) InhibitMemory[bParameterSelect] = paramInh;

		// limit set
		if (!InvalidParam && funcSet) LimitValueRAM[LimitSelect] = bLimitValue | 0x80/*set value*/;

		//// parameter check logic
		for (int i = 0; i < 128; i++)
		{
			//////////////////////////
			// HACK skip check for not-yet-implemented parameters to avoid false alarms
			switch (i)
			{
				case 0:
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				//case 9:
				case 10:
				case 11:
				case 12:
				case 13:
				case 14:
				case 15:
				case 16:
				case 17:
				case 18:
				//case 19:
				case 20:
				case 21:
				case 22:
				case 23:
				case 24:
				case 25:
				case 26:
				case 27:
				case 28:
				//case 29:
				case 30:
				case 31:
				case 32:
				case 33:
				case 34:
				case 35:
				case 36:
				case 37:
				case 38:
				//case 39:
				case 40:
				case 41:
				case 42:
				case 43:
				case 44:
				case 45:
				case 46:
				case 47:
				case 48:
				//case 49:
				case 50:
				case 51:
				case 52:
				case 53:
				case 54:
				case 55:
				case 56:
				case 57:
				case 58:
				//case 59:
				case 60:
				case 61:
				case 62:
				case 63:
				case 64:
				case 65:
				case 66:
				//case 67:
				case 68:
				//case 69:
				case 70:
				case 71:
				case 72:
				case 73:
				case 74:
				case 75:
				case 76:
				case 77:
				case 78:
				//case 79:
				case 80:
				case 81:
				case 82:
				case 83:
				case 84:
				case 85:
				case 86:
				case 87:
				case 88:
				//case 89:
				case 90:
				case 91:
				case 92:
				case 93:
				case 94:
				case 95:
				case 96:
				case 97:
				case 98:
				//case 99:
				case 100:
				//case 101:
				case 102:
				case 103:
				case 104:
				case 105:
				case 106:
				case 107:
				case 108:
				//case 109:
				case 110:
				case 111:
				case 112:
				//case 113:
				case 114:
				case 115:
				case 116:
				case 117:
				case 118:
				//case 119:
					continue;
				default:
					break;
			}
			//////////////////////////
			bool CountUp = false;
			unsigned char ParamCount = i;
			for (unsigned int k = 0; k < 2; k++)
			{
				unsigned char limvalPROM = LimitValuePROM[ParamCount | (k << 7)];
				unsigned char limvalROM = LimitValueRAM[ParamCount | (k << 7)];
				unsigned char DigitalLimitValue = ((limvalROM & 0x80) != 0) ? (limvalROM & 0x7F) : (limvalPROM & 0x7F);
				bool HighLimit = (limvalPROM & 0x80) != 0;
				double AnalogLimit = 0.05 * DigitalLimitValue;

				bool LimitComparator = (AnalogLimit > ParameterData[ParamCount].GetVoltage());// lo in = 0, hi in = 1, lo out = 1, hi out = 0
				CountUp = CountUp || (LimitComparator != HighLimit);
			}

			unsigned char Count = NCountMemory[ParamCount];
			if (CountUp && (Count != 8)) Count++;
			else if (!CountUp && (Count != 0)) Count--;
			NCountMemory[ParamCount] = Count;
			if ((Count == 0) || (Count == 8)) NCountOverflowMemory[ParamCount] = (Count == 8);

			bool OLI = NCountOverflowMemory[ParamCount] && !InhibitMemory[ParamCount];
			bool NI_OLI = NCountOverflowMemory[ParamCount];
			Pri_CW_Trigger = Pri_CW_Trigger || (OLI && !PrimaryCWTriggerMemory[ParamCount]);

			bool O1 = !PRI_CW[0].get() && cwmemoryRead;
			bool O2 = RecallMemory[ParamCount] && !InhibitMemory[ParamCount];
			bool O3 = O1 && O2;
			bool A2 = OLI || O3;
			PrimaryCWTriggerMemory[ParamCount] = A2;//OLI || ((cwmemoryRead && !PRI_CW[0].get()) && (RecallMemory[ParamCount] && !InhibitMemory[ParamCount]));

			bool MemoryClear = cwmemoryClear || memoryClear;
			if (MemoryClear || NI_OLI) RecallMemory[ParamCount] = NI_OLI && !MemoryClear;

			oli[i] = OLI;
			ni_oli[i] = NI_OLI;
		}
	}
	else
	{
		// clear memories
		for (auto &x : InhibitMemory) x = false;
		for (auto &x : NCountMemory) x = 0;
		for (auto &x : NCountOverflowMemory) x = false;
		for (auto &x : RecallMemory) x = false;
		for (auto &x : PrimaryCWTriggerMemory) x = false;
		for (auto &x : LimitValueRAM) x = 0;
	}


	//// master alarm tone logic
	bool MasterAlarmRelaySignal_A = false;
	bool MasterAlarmRelaySignal_B = false;
	bool PrimaryCW_A = false;
	bool PrimaryCW_B = false;
	bool BackupCW_A = false;
	bool BackupCW_B = false;
	{
		bool BU_CW_A = !(BU_CW_A_CMD_3.IsSet( 26.0f ) || BU_CW_A_CMD_4.IsSet( 26.0f ) || BU_CW_B_CMD_2.IsSet( 26.0f ));
		bool BU_CW_B = !(BU_CW_A_CMD_1.IsSet( 26.0f ) || BU_CW_A_CMD_2.IsSet( 26.0f ) || BU_CW_B_CMD_1.IsSet( 26.0f ));

		bool SM_TONE_A = SM_TONE_A_CMD_1.IsSet( 26.0f ) || SM_TONE_A_CMD_2.IsSet( 26.0f ) || SM_TONE_A_CMD_3.IsSet( 26.0f ) || SM_TONE_A_CMD_4.IsSet( 26.0f ) || SM_TONE_B_CMD_1.IsSet( 26.0f ) || SM_TONE_B_CMD_2.IsSet( 26.0f );
		bool SM_TONE_B = SM_TONE_A_CMD_1.IsSet( 26.0f ) || SM_TONE_A_CMD_2.IsSet( 26.0f ) || SM_TONE_A_CMD_3.IsSet( 26.0f ) || SM_TONE_A_CMD_4.IsSet( 26.0f ) || SM_TONE_B_CMD_1.IsSet( 26.0f ) || SM_TONE_B_CMD_2.IsSet( 26.0f );

		bool cw_tone_request_a = false;
		bool cw_tone_request_b = false;
		bool sm_tone_request_a = false;
		bool sm_tone_request_b = false;

		MasterAlarmToneLogic( 0, PS_A, PS_B, Pri_CW_Trigger, BU_CW_A, SM_TONE_A, MasterAlarmRelaySignal_A, cw_tone_request_a, sm_tone_request_a, PrimaryCW_A, BackupCW_A, simdt );
		MasterAlarmToneLogic( 1, PS_B, PS_A, Pri_CW_Trigger, BU_CW_B, SM_TONE_B, MasterAlarmRelaySignal_B, cw_tone_request_b, sm_tone_request_b, PrimaryCW_B, BackupCW_B, simdt );

		// handle tone sounds
		if (sm_tone_request_a || sm_tone_request_b)
		{
			if (!bSM_TONE)
			{
				// start playing
				PlayVesselWave( STS()->GetSoundID(), SM_TONE_SOUND, LOOP );
				bSM_TONE = true;
			}
		}
		else
		{
			if (bSM_TONE)
			{
				// stop playing
				StopVesselWave( STS()->GetSoundID(), SM_TONE_SOUND );
				bSM_TONE = false;
			}
		}

		if (cw_tone_request_a || cw_tone_request_b)
		{
			if (!bCW_TONE)
			{
				// start playing
				PlayVesselWave( STS()->GetSoundID(), CW_TONE_SOUND, LOOP );
				bCW_TONE = true;
			}
		}
		else
		{
			if (bCW_TONE)
			{
				// stop playing
				StopVesselWave( STS()->GetSoundID(), CW_TONE_SOUND );
				bCW_TONE = false;
			}
		}
	}

	// master alarm relays
	if (MasterAlarmRelaySignal_A && CW_POWER_A)
	{
		if (CAUTIONWARNINGMODE_NORM.IsSet() || CAUTIONWARNINGMODE_ACK.IsSet()) MasterAlarm_F2_A.SetLine();
		else MasterAlarm_F2_A.ResetLine();
		MasterAlarm_F4_A.SetLine();
		MasterAlarm_A7U_A.SetLine();
		MasterAlarm_MO52J_A.SetLine();
	}
	else
	{
		MasterAlarm_F2_A.ResetLine();
		MasterAlarm_F4_A.ResetLine();
		MasterAlarm_A7U_A.ResetLine();
		MasterAlarm_MO52J_A.ResetLine();
	}
	if (MasterAlarmRelaySignal_B && CW_POWER_B)
	{
		if (CAUTIONWARNINGMODE_NORM.IsSet() || CAUTIONWARNINGMODE_ACK.IsSet()) MasterAlarm_F2_B.SetLine();
		else MasterAlarm_F2_B.ResetLine();
		MasterAlarm_F4_B.SetLine();
		MasterAlarm_A7U_B.SetLine();
		MasterAlarm_MO52J_B.SetLine();
	}
	else
	{
		MasterAlarm_F2_B.ResetLine();
		MasterAlarm_F4_B.ResetLine();
		MasterAlarm_A7U_B.ResetLine();
		MasterAlarm_MO52J_B.ResetLine();
	}


	//// outputs
	// CW lights
	bool cwlight[40];
	for (auto &x : cwlight) x = false;

	// Primary C&W light
	if (PrimaryCW_A || PrimaryCW_B) cwlight[14] = true;

	// Backup C&W light
	if (BackupCW_A || BackupCW_B) cwlight[7] = true;

	// remaining lights
	if (PS_A)
	{
		for (int i = 0; i < 128; i++)
		{
			// memory read (C3)
			bool O1 = !PRI_CW[0].get() && cwmemoryRead;
			bool O2 = RecallMemory[i] && !InhibitMemory[i];
			bool O3 = O1 && O2;
			bool O4 = oli[i] && !O1;
			bool A1 = O4 || O3;
			bool A2 = oli[i] || O3;
			bool O5 = !A2 && PrimaryCWTriggerMemory[i];
			bool A3 = O5 || A2;
			bool AnnunciatorData = A1;
			bool ena = A3;
			unsigned short addr = CombinationMemory[i];
			if (addr >= 14) addr += 1;
			else if ((addr <= 7) && (addr > 0)) addr -= 1;
			/*oapiWriteLogV( "CW lights %d %d %d %d | %d %d %d %d %d", i, AnnunciatorData, ena, addr, 
				oli[i], PRI_CW[0].get(), cwmemoryRead, RecallMemory[i], InhibitMemory[i] );*/
			if (AnnunciatorData && ena) cwlight[addr] = true;
		}
	}
	for (unsigned int i = 0; i < 40; i++)
	{
		bool pwr = (i == 7) ? PS_B : PS_A;
		if (cwlight[i] || !pwr)
			AnnunciatorLightSignals[i].SetLine();
		else
			AnnunciatorLightSignals[i].ResetLine();
	}

	// CW matrix 120b
	// HACK using discrete lines instead of serial data
	bool MatrixLight[120];
	for (auto &x : MatrixLight) x = false;

	if (PS_A)
	{
		// memory read (R13U)
		if (memoryRead)
		{
			for (int i = 0; i < 120; i++)
			{
				MatrixLight[i] |= RecallMemory[i];
			}
		}

		// limit value
		{
			bool LimitRead = !InvalidParam && funcRead;
			if (LimitRead)
			{
				unsigned char limvalPROM = LimitValuePROM[LimitSelect];
				unsigned char limvalROM = LimitValueRAM[LimitSelect];
				unsigned char DigitalLimitValue = ((limvalROM & 0x80) != 0) ? (limvalROM & 0x7F) : (limvalPROM & 0x7F);
				// bin to BCD converter
				bool A = (DigitalLimitValue & 0x01) != 0;
				bool B = (DigitalLimitValue & 0x02) != 0;
				bool C = (DigitalLimitValue & 0x04) != 0;
				bool D = (DigitalLimitValue & 0x08) != 0;
				bool E = (DigitalLimitValue & 0x10) != 0;
				bool F = (DigitalLimitValue & 0x20) != 0;
				bool G = (DigitalLimitValue & 0x40) != 0;
				bool cXX5 = A;
				bool cX1X = B;
				bool cX2X = (G && ((!F && !E && !C) || (!E && D && !C) || (!F && E && C) || (E && D && C) || (F && E && !D && !C))) || (!G && ((!F && !E && C) || (!E && D && C) || (!F && E && D && C) || (F && !E && !D && !C) || (F && E && !D && C)));//G(F'E'C' + E'DC' + F'EC + EDC + FED'C') + G'(F'E'C + E'DC + F'EDC + FE'D'C' + FED'C)
				bool cX4X = (F && ((!G && !D && !C) || (!G && E && !D) || (E && !D && !C) || (G && !E && D && C))) || (!F && ((!G && !E && D) || (E && D && C) || (G && D && !C) || (G && !E && !D && C)));//F(G'D'C' + G'ED' + ED'C' + GE'DC) + F'(G'E'D + EDC + GDC' + GE'D'C)
				bool cX8X = (G && ((!F && !E && D && C) || (F && !E && !D && !C) || (F && E && !D && C))) || (!G && ((!F && E && !D && !C) || (F && !E && !D && C) || (F && E && D && !C)));//G(F'E'DC + FE'D'C' + FED'C) + G'(F'ED'C' + FE'D'C + FEDC')
				bool c1XX = (G && ((!F && !E) || (!E && C) || (!E && D) || (F && E && !D))) || (!G && ((!F && E && C) || (!F && E && D) || (E && D && C) || (F && !E && !D) || (F && !E && !C && !B)));//G(F'E' + E'C + E'D + FED') + G'(F'EC + F'ED + EDC + FE'D' + FE'C'B')
				bool c2XX = (F && ((!G && (D || E)) || (E && D))) || (G && !F && !E);
				bool c4XX = G && (F || E);

				// display encoder
				// 0.0x
				if (cXX5) MatrixLight[53] = true;
				else MatrixLight[3] = true;
				// 0.x0
				MatrixLight[2] |= !cX1X && !cX2X && !cX4X && !cX8X;
				MatrixLight[12] |= cX1X && !cX2X && !cX4X && !cX8X;
				MatrixLight[22] |= !cX1X && cX2X && !cX4X && !cX8X;
				MatrixLight[32] |= cX1X && cX2X && !cX4X && !cX8X;
				MatrixLight[42] |= !cX1X && !cX2X && cX4X && !cX8X;
				MatrixLight[52] |= cX1X && !cX2X && cX4X && !cX8X;
				MatrixLight[62] |= !cX1X && cX2X && cX4X && !cX8X;
				MatrixLight[72] |= cX1X && cX2X && cX4X && !cX8X;
				MatrixLight[82] |= !cX1X && !cX2X && !cX4X && cX8X;
				MatrixLight[92] |= cX1X && !cX2X && !cX4X && cX8X;
				// x.00
				MatrixLight[0] |= !c1XX && !c2XX && !c4XX;
				MatrixLight[10] |= c1XX && !c2XX && !c4XX;
				MatrixLight[20] |= !c1XX && c2XX && !c4XX;
				MatrixLight[30] |= c1XX && c2XX && !c4XX;
				MatrixLight[40] |= !c1XX && !c2XX && c4XX;
				MatrixLight[50] |= c1XX && !c2XX && c4XX;
				MatrixLight[60] |= !c1XX && c2XX && c4XX;
				MatrixLight[70] |= c1XX && c2XX && c4XX;
			}
		}

		// tripped
		if (paramstatusTri)
		{
			for (int i = 0; i < 120; i++)
			{
				MatrixLight[i] |= ni_oli[i];
			}
		}

		// inhibited
		if (paramstatusInh)
		{
			for (int i = 0; i < 120; i++)
			{
				MatrixLight[i] |= InhibitMemory[i];
			}
		}

		// lamp test left
		// lamp test right
		for (int i = 0; i < 120; i += 10)
		{
			MatrixLight[i] |= lamptestLeft;
			MatrixLight[i + 1] |= lamptestLeft;
			MatrixLight[i + 2] |= lamptestLeft;
			MatrixLight[i + 3] |= lamptestLeft;
			MatrixLight[i + 4] |= lamptestLeft;
			MatrixLight[i + 5] |= lamptestRight;
			MatrixLight[i + 6] |= lamptestRight;
			MatrixLight[i + 7] |= lamptestRight;
			MatrixLight[i + 8] |= lamptestRight;
			MatrixLight[i + 9] |= lamptestRight;
		}
	}

	// send data
	for (int i = 0; i < 120; i++)
	{
		if (MatrixLight[i]) MatrixLightSignals[i].SetLine();
		else MatrixLightSignals[i].ResetLine();
	}


	//// external wiring
	if (SM_LIGHT_A_CMD_1.IsSet( 26.0f ) || SM_LIGHT_A_CMD_2.IsSet( 26.0f ) || SM_LIGHT_A_CMD_3.IsSet( 26.0f ) || SM_LIGHT_A_CMD_4.IsSet( 26.0f ) || SM_LIGHT_B_CMD_1.IsSet( 26.0f ) || SM_LIGHT_B_CMD_2.IsSet( 26.0f ))
	{
		// set SM light
		SMAlert_ACA2.SetLine();
		SMAlert_ACA3.SetLine();
	}
	else
	{
		// reset SM light
		SMAlert_ACA2.ResetLine();
		SMAlert_ACA3.ResetLine();
	}
	return;
}

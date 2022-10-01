#include "GAX.h"
#include <cassert>


constexpr double EXEC_DT = 0.96;// [s]

// major field = 3 + 1(space) + 10 + 1(space)
// minor field = 4
const char* CRTMSG_MAJOR_MPS_CMD_X =	"    MPS CMD   ";
const char* CRTMSG_MAJOR_MPS_DATA_X =	"    MPS DATA  ";
const char* CRTMSG_MAJOR_MPS_ELEC_X =	"    MPS ELEC  ";
const char* CRTMSG_MAJOR_MPS_HYD_X =	"    MPS HYD   ";
const char* CRTMSG_OTT_ST_IN =		"    OTT ST IN      ";
const char* CRTMSG_ROLL_REF =		"    ROLL REF       ";
const char* CRTMSG_MAJOR_SSME_FAIL_X =	"    SSME FAIL ";
const char* CRTMSG_SW_TO_MEP =		"    SW TO MEP      ";
const char* CRTMSG_ET_SEP_INH =		"    ET SEP-INH     ";
const char* CRTMSG_DAP_DNMODE_RHC =	"    DAP DNMODE RHC ";
const char* CRTMSG_FCS_SAT_POS =	"    FCS SAT    POS ";
const char* CRTMSG_SPD_BRK =		"    SPD BRK        ";

const char* CRTMSG_MINOR_MPS[3] = {	"   C",
					"   L",
					"   R"};


namespace dps
{
	GAX::GAX( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "GAX" ),
		step(EXEC_DT), bET_SEP_INH(false), bMPS_CMD{false, false, false}, bMPS_DATA{false, false, false}, bMPS_ELEC{false, false, false}, bMPS_HYD{false, false, false},
		bOTT_ST_IN(false), bROLL_REF(false), bSSME_FAIL{false,false,false}, bSW_TO_MEP(false), bDAP_DNMODE_RHC(false), bFCS_SAT_POS(false), bSPD_BRK(false)
	{
		return;
	}

	GAX::~GAX( void )
	{
		return;
	}

	void GAX::Realize( void )
	{
		return;
	}

	void GAX::ET_SEP_INH( void )// class 3
	{
		if (ReadCOMPOOL_IS( SCP_ET_AUTO_SEP_INHIBIT_CREW_ALERT ) == 1)
		{
			if (!bET_SEP_INH)
			{
				bET_SEP_INH = true;
				unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
				if (j < 5)
				{
					WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, CRTMSG_ET_SEP_INH, 5, 19 );
					WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 3, 5 );
					WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
				}
			}
		}
		else bET_SEP_INH = false;
		return;
	}

	void GAX::MPS_CMD_X( void )// class 3
	{
		for (unsigned int i = 0; i < 3; i++)
		{
			if (ReadCOMPOOL_AIS( SCP_ME_CMD_PATH_FAIL, i + 1, 3 ) == 1)
			{
				if (!bMPS_CMD[i])
				{
					bMPS_CMD[i] = true;
					unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
					if (j < 5)
					{
						char cbuf[32];
						sprintf_s( cbuf, "%s %s", CRTMSG_MAJOR_MPS_CMD_X, CRTMSG_MINOR_MPS[i] );
						WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, cbuf, 5, 19 );
						WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 3, 5 );
						WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
					}
				}
			}
		}
		return;
	}

	void GAX::MPS_DATA_X( void )// class 3
	{
		for (unsigned int i = 0; i < 3; i++)
		{
			if (ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, i + 1, 3 ) == 1)
			{
				if (!bMPS_DATA[i])
				{
					bMPS_DATA[i] = true;
					unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
					if (j < 5)
					{
						char cbuf[32];
						sprintf_s( cbuf, "%s %s", CRTMSG_MAJOR_MPS_DATA_X, CRTMSG_MINOR_MPS[i] );
						WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, cbuf, 5, 19 );
						WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 3, 5 );
						WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
					}
				}
			}
		}
		return;
	}

	void GAX::MPS_ELEC_X( void )// class 3
	{
		for (unsigned int i = 0; i < 3; i++)
		{
			if (ReadCOMPOOL_AIS( SCP_ME_ELEC_LOCKUP, i + 1, 3 ) == 1)
			{
				if (!bMPS_ELEC[i])
				{
					bMPS_ELEC[i] = true;
					unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
					if (j < 5)
					{
						char cbuf[32];
						sprintf_s( cbuf, "%s %s", CRTMSG_MAJOR_MPS_ELEC_X, CRTMSG_MINOR_MPS[i] );
						WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, cbuf, 5, 19 );
						WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 3, 5 );
						WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
					}
				}
			}
		}
		return;
	}

	void GAX::MPS_HYD_X( void )// class 3
	{
		for (unsigned int i = 0; i < 3; i++)
		{
			if (ReadCOMPOOL_AIS( SCP_ME_HYD_LOCKUP, i + 1, 3 ) == 1)
			{
				if (!bMPS_HYD[i])
				{
					bMPS_HYD[i] = true;
					unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
					if (j < 5)
					{
						char cbuf[32];
						sprintf_s( cbuf, "%s %s", CRTMSG_MAJOR_MPS_HYD_X, CRTMSG_MINOR_MPS[i] );
						WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, cbuf, 5, 19 );
						WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 3, 5 );
						WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
					}
				}
			}
		}
		return;
	}

	void GAX::OTT_ST_IN( void )// class 3
	{
		if (ReadCOMPOOL_IS( SCP_OTT_ST_IN ) == 1)
		{
			if (!bOTT_ST_IN)
			{
				bOTT_ST_IN = true;
				unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
				if (j < 5)
				{
					WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, CRTMSG_OTT_ST_IN, 5, 19 );
					WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 3, 5 );
					WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
				}
			}
		}
		else bOTT_ST_IN = false;
		return;
	}

	void GAX::ROLL_REF( void )// class 3
	{
		if (ReadCOMPOOL_IS( SCP_ROLL_REF_CREW_ALERT ) == 1)
		{
			if (!bROLL_REF)
			{
				bROLL_REF = true;
				unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
				if (j < 5)
				{
					WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, CRTMSG_ROLL_REF, 5, 19 );
					WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 3, 5 );
					WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
				}
			}
		}
		else bROLL_REF = false;
		return;
	}

	void GAX::SSME_FAIL_X( void )// class 2
	{
		unsigned short fail = 0;
		if (ReadCOMPOOL_IS( SCP_MECO_CMD ) == 1) return;

		for (unsigned int i = 0; i < 3; i++)
		{
			switch (i)
			{
				case 0:
					fail = ReadCOMPOOL_IS( SCP_ME1_FAIL_SHUTDOWN );
					break;
				case 1:
					fail = ReadCOMPOOL_IS( SCP_ME2_FAIL_SHUTDOWN );
					break;
				case 2:
					fail = ReadCOMPOOL_IS( SCP_ME3_FAIL_SHUTDOWN );
					break;
			}
			if (fail == 1)
			{
				if (!bSSME_FAIL[i])
				{
					bSSME_FAIL[i] = true;
					unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
					if (j < 5)
					{
						char cbuf[32];
						sprintf_s( cbuf, "%s %s", CRTMSG_MAJOR_SSME_FAIL_X, CRTMSG_MINOR_MPS[i] );
						WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, cbuf, 5, 19 );
						WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 2, 5 );
						WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
					}
				}
			}
		}
		return;
	}

	void GAX::SW_TO_MEP( void )// class 3
	{
		if (ReadCOMPOOL_IS( SCP_SW_TO_MEP ) == 1)
		{
			if (!bSW_TO_MEP)
			{
				bSW_TO_MEP = true;
				unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
				if (j < 5)
				{
					WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, CRTMSG_SW_TO_MEP, 5, 19 );
					WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 3, 5 );
					WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
				}
			}
		}
		else bSW_TO_MEP = false;
		return;
	}

	void GAX::DAP_DNMODE_RHC( void )// class 3
	{
		if (ReadCOMPOOL_IS( SCP_DAP_DNMODE_RHC_CREW_ALERT ) == 1)
		{
			if (!bDAP_DNMODE_RHC)
			{
				bDAP_DNMODE_RHC = true;
				unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
				if (j < 5)
				{
					WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, CRTMSG_DAP_DNMODE_RHC, 5, 19 );
					WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 3, 5 );
					WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
				}
			}
		}
		else bDAP_DNMODE_RHC = false;
		return;
	}

	void GAX::FCS_SAT_POS( void )// class 2
	{
		if ((ReadCOMPOOL_IS( SCP_LOB_SAT_POS_CREW_ALERT ) == 1) ||
			(ReadCOMPOOL_IS( SCP_LIB_SAT_POS_CREW_ALERT ) == 1) ||
			(ReadCOMPOOL_IS( SCP_RIB_SAT_POS_CREW_ALERT ) == 1) ||
			(ReadCOMPOOL_IS( SCP_ROB_SAT_POS_CREW_ALERT ) == 1))
		{
			if (!bFCS_SAT_POS)
			{
				bFCS_SAT_POS = true;
				unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
				if (j < 5)
				{
					WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, CRTMSG_FCS_SAT_POS, 5, 19 );
					WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 2, 5 );
					WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
				}

				// TODO CW matrix light
			}
		}
		else bFCS_SAT_POS = false;
		return;
	}

	void GAX::SPD_BRK( void )// class 3
	{
		if (ReadCOMPOOL_IS( SCP_SPEEDBRAKE_POS_CREW_ALERT ) == 1)
		{
			if (!bSPD_BRK)
			{
				bSPD_BRK = true;
				unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
				if (j < 5)
				{
					WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, CRTMSG_SPD_BRK, 5, 19 );
					WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 3, 5 );
					WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
				}
			}
		}
		else bSPD_BRK = false;
		return;
	}

	void GAX::OnPostStep( double simt, double simdt, double mjd )
	{
		step += simdt;
		if (step < EXEC_DT) return;

		switch (ReadCOMPOOL_IS( SCP_MM ))
		{
			case 101:
				MPS_CMD_X();
				MPS_DATA_X();
				MPS_ELEC_X();
				MPS_HYD_X();
				OTT_ST_IN();
				SW_TO_MEP();
				break;
			case 102:
				MPS_CMD_X();
				MPS_DATA_X();
				MPS_ELEC_X();
				MPS_HYD_X();
				OTT_ST_IN();
				SSME_FAIL_X();
				SW_TO_MEP();
				ET_SEP_INH();
				break;
			case 103:
				MPS_CMD_X();
				MPS_DATA_X();
				MPS_ELEC_X();
				MPS_HYD_X();
				OTT_ST_IN();
				SSME_FAIL_X();
				SW_TO_MEP();
				ET_SEP_INH();
				break;
			case 104:
				MPS_CMD_X();
				MPS_DATA_X();
				OTT_ST_IN();
				SW_TO_MEP();
				ET_SEP_INH();
				break;
			case 105:
				OTT_ST_IN();
				SW_TO_MEP();
				break;
			case 106:
				OTT_ST_IN();
				SW_TO_MEP();
				break;
			case 201:
				break;
			case 202:
				break;
			case 301:
				OTT_ST_IN();
				ROLL_REF();
				SW_TO_MEP();
				FCS_SAT_POS();
				break;
			case 302:
				OTT_ST_IN();
				ROLL_REF();
				SW_TO_MEP();
				FCS_SAT_POS();
				break;
			case 303:
				OTT_ST_IN();
				ROLL_REF();
				SW_TO_MEP();
				FCS_SAT_POS();
				break;
			case 304:
				OTT_ST_IN();
				ROLL_REF();
				SW_TO_MEP();
				DAP_DNMODE_RHC();
				FCS_SAT_POS();
				SPD_BRK();
				break;
			case 305:
				OTT_ST_IN();
				ROLL_REF();
				SW_TO_MEP();
				DAP_DNMODE_RHC();
				FCS_SAT_POS();
				SPD_BRK();
				break;
			case 601:
				MPS_CMD_X();
				MPS_DATA_X();
				MPS_ELEC_X();
				MPS_HYD_X();
				OTT_ST_IN();
				SSME_FAIL_X();
				SW_TO_MEP();
				break;
			case 602:
				OTT_ST_IN();
				SW_TO_MEP();
				DAP_DNMODE_RHC();
				FCS_SAT_POS();
				SPD_BRK();
				break;
			case 603:
				OTT_ST_IN();
				SW_TO_MEP();
				DAP_DNMODE_RHC();
				FCS_SAT_POS();
				SPD_BRK();
				break;
			case 801:
				break;
			case 901:
				break;
			default:
				break;
		}

		if (bFCS_SAT_POS) WriteCOMPOOL_IS( SCP_FF3_IOM5_CH1_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM5_CH1_DATA ) | 0x0020 );
		return;
	}

	bool GAX::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 101:
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
			case 901:
				return true;
			default:
				return false;
		}
	}

	bool GAX::OnParseLine( const char* keyword, const char* value )
	{
		unsigned int tmp1 = 0;
		unsigned int tmp2 = 0;
		unsigned int tmp3 = 0;

		if (!_strnicmp( keyword, "ET_SEP_INH", 9 ))
		{
			sscanf_s( value, "%u", &tmp1 );
			bET_SEP_INH = (tmp1 == 1);
			return true;
		}
		else if (!_strnicmp( keyword, "MPS_CMD", 7 ))
		{
			sscanf_s( value, "%u %u %u", &tmp1, &tmp2, &tmp3 );
			bMPS_CMD[0] = (tmp1 == 1);
			bMPS_CMD[1] = (tmp2 == 1);
			bMPS_CMD[2] = (tmp3 == 1);
			return true;
		}
		else if (!_strnicmp( keyword, "MPS_DATA", 8 ))
		{
			sscanf_s( value, "%u %u %u", &tmp1, &tmp2, &tmp3 );
			bMPS_DATA[0] = (tmp1 == 1);
			bMPS_DATA[1] = (tmp2 == 1);
			bMPS_DATA[2] = (tmp3 == 1);
			return true;
		}
		else if (!_strnicmp( keyword, "MPS_ELEC", 8 ))
		{
			sscanf_s( value, "%u %u %u", &tmp1, &tmp2, &tmp3 );
			bMPS_ELEC[0] = (tmp1 == 1);
			bMPS_ELEC[1] = (tmp2 == 1);
			bMPS_ELEC[2] = (tmp3 == 1);
			return true;
		}
		else if (!_strnicmp( keyword, "MPS_HYD", 7 ))
		{
			sscanf_s( value, "%u %u %u", &tmp1, &tmp2, &tmp3 );
			bMPS_HYD[0] = (tmp1 == 1);
			bMPS_HYD[1] = (tmp2 == 1);
			bMPS_HYD[2] = (tmp3 == 1);
			return true;
		}
		else if (!_strnicmp( keyword, "OTT_ST_IN", 9 ))
		{
			sscanf_s( value, "%u", &tmp1 );
			bOTT_ST_IN = (tmp1 == 1);
			return true;
		}
		else if (!_strnicmp( keyword, "ROLL_REF", 8 ))
		{
			sscanf_s( value, "%u", &tmp1 );
			bROLL_REF = (tmp1 == 1);
			return true;
		}
		else if (!_strnicmp( keyword, "SSME_FAIL", 9 ))
		{
			sscanf_s( value, "%u %u %u", &tmp1, &tmp2, &tmp3 );
			bSSME_FAIL[0] = (tmp1 == 1);
			bSSME_FAIL[1] = (tmp2 == 1);
			bSSME_FAIL[2] = (tmp3 == 1);
			return true;
		}
		else if (!_strnicmp( keyword, "SW_TO_MEP", 9 ))
		{
			sscanf_s( value, "%u", &tmp1 );
			bSW_TO_MEP = (tmp1 == 1);
			return true;
		}
		else if (!_strnicmp( keyword, "DAP_DNMODE_RHC", 14 ))
		{
			sscanf_s( value, "%u", &tmp1 );
			bDAP_DNMODE_RHC = (tmp1 == 1);
			return true;
		}
		else if (!_strnicmp( keyword, "FCS_SAT_POS", 11 ))
		{
			sscanf_s( value, "%u", &tmp1 );
			bFCS_SAT_POS = (tmp1 == 1);
			return true;
		}
		else if (!_strnicmp( keyword, "SPD_BRK", 7 ))
		{
			sscanf_s( value, "%u", &tmp1 );
			bSPD_BRK = (tmp1 == 1);
			return true;
		}
		else return false;
	}

	void GAX::OnSaveState( FILEHANDLE scn ) const
	{
		char cbuf[16];
		oapiWriteScenario_int( scn, "ET_SEP_INH", bET_SEP_INH ? 1 : 0 );
		sprintf_s( cbuf, 16, "%d %d %d", bMPS_CMD[0] ? 1 : 0, bMPS_CMD[1] ? 1 : 0, bMPS_CMD[2] ? 1 : 0 );
		oapiWriteScenario_string( scn, "MPS_CMD", cbuf );
		sprintf_s( cbuf, 16, "%d %d %d", bMPS_DATA[0] ? 1 : 0, bMPS_DATA[1] ? 1 : 0, bMPS_DATA[2] ? 1 : 0 );
		oapiWriteScenario_string( scn, "MPS_DATA", cbuf );
		sprintf_s( cbuf, 16, "%d %d %d", bMPS_ELEC[0] ? 1 : 0, bMPS_ELEC[1] ? 1 : 0, bMPS_ELEC[2] ? 1 : 0 );
		oapiWriteScenario_string( scn, "MPS_ELEC", cbuf );
		sprintf_s( cbuf, 16, "%d %d %d", bMPS_HYD[0] ? 1 : 0, bMPS_HYD[1] ? 1 : 0, bMPS_HYD[2] ? 1 : 0 );
		oapiWriteScenario_string( scn, "MPS_HYD", cbuf );
		oapiWriteScenario_int( scn, "OTT_ST_IN", bOTT_ST_IN ? 1 : 0 );
		oapiWriteScenario_int( scn, "ROLL_REF", bROLL_REF ? 1 : 0 );
		sprintf_s( cbuf, 16, "%d %d %d", bSSME_FAIL[0] ? 1 : 0, bSSME_FAIL[1] ? 1 : 0, bSSME_FAIL[2] ? 1 : 0 );
		oapiWriteScenario_string( scn, "SSME_FAIL", cbuf );
		oapiWriteScenario_int( scn, "SW_TO_MEP", bSW_TO_MEP ? 1 : 0 );
		oapiWriteScenario_int( scn, "DAP_DNMODE_RHC", bDAP_DNMODE_RHC ? 1 : 0 );
		oapiWriteScenario_int( scn, "FCS_SAT_POS", bFCS_SAT_POS ? 1 : 0 );
		oapiWriteScenario_int( scn, "SPD_BRK", bSPD_BRK ? 1 : 0 );
		return;
	}
}

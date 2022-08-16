#include "GAX.h"
#include <cassert>


constexpr double EXEC_DT = 0.96;// [s]

// major field = 3 + 1(space) + 10 + 1(space)
// minor field = 4
const char* CRTMSG_MAJOR_MPS_CMD_X =	"    MPS CMD   ";
const char* CRTMSG_MAJOR_MPS_DATA_X =	"    MPS DATA  ";
const char* CRTMSG_MAJOR_MPS_ELEC_X =	"    MPS ELEC  ";
const char* CRTMSG_MAJOR_MPS_HYD_X =	"    MPS HYD   ";
const char* CRTMSG_OTT_ST_IN =	"    OTT ST IN      ";
const char* CRTMSG_ROLL_REF =	"    ROLL REF       ";
const char* CRTMSG_MAJOR_SSME_FAIL_X =	"    SSME FAIL ";
const char* CRTMSG_SW_TO_MEP =	"    SW TO MEP      ";
const char* CRTMSG_ET_SEP_INH =	"    ET SEP-INH     ";

const char* CRTMSG_MINOR_MPS[3] = {	"   C",
					"   L",
					"   R"};


namespace dps
{
	GAX::GAX( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "GAX" ),
		step(EXEC_DT), bMPS_CMD{false, false, false}, bMPS_DATA{false, false, false}, bMPS_ELEC{false, false, false}, bMPS_HYD{false, false, false},
		bOTT_ST_IN(false), bROLL_REF(false), bSSME_FAIL{false,false,false}, bSW_TO_MEP(false), bET_SEP_INH(false)
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
		// TODO
		/*if (ReadCOMPOOL_IS( SCP_ ) == 1)
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
		else bROLL_REF = false;*/
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
				break;
			case 302:
				OTT_ST_IN();
				ROLL_REF();
				SW_TO_MEP();
				break;
			case 303:
				OTT_ST_IN();
				ROLL_REF();
				SW_TO_MEP();
				break;
			case 304:
				OTT_ST_IN();
				ROLL_REF();
				SW_TO_MEP();
				break;
			case 305:
				OTT_ST_IN();
				ROLL_REF();
				SW_TO_MEP();
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
				break;
			case 603:
				OTT_ST_IN();
				SW_TO_MEP();
				break;
			case 801:
				break;
			case 901:
				break;
			default:
				break;
		}
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
}

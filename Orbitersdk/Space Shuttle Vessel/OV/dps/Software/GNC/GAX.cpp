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
const char* CRTMSG_TGT_DELTA_T =	"    TGT \xFFT         ";
const char* CRTMSG_TGT_EL_ANG =		"    TGT EL ANG     ";
const char* CRTMSG_TGT_ITER =		"    TGT ITER       ";
const char* CRTMSG_L_OMS_GMBL =		"    L OMS      GMBL";
const char* CRTMSG_R_OMS_GMBL =		"    R OMS      GMBL";

const char* CRTMSG_F_RCS_FJET =		"    F RCS      FJET";
const char* CRTMSG_F_RCS_LJET =		"    F RCS      LJET";
const char* CRTMSG_F_RCS_RJET =		"    F RCS      RJET";
const char* CRTMSG_F_RCS_UJET =		"    F RCS      UJET";
const char* CRTMSG_L_RCS_DJET =		"    L RCS      DJET";
const char* CRTMSG_L_RCS_LJET =		"    L RCS      LJET";
const char* CRTMSG_L_RCS_UJET =		"    L RCS      UJET";
const char* CRTMSG_L_RCS_AJET =		"    L RCS      AJET";
const char* CRTMSG_R_RCS_DJET =		"    R RCS      DJET";
const char* CRTMSG_R_RCS_RJET =		"    R RCS      RJET";
const char* CRTMSG_R_RCS_UJET =		"    R RCS      UJET";
const char* CRTMSG_R_RCS_AJET =		"    R RCS      AJET";

const char* CRTMSG_MINOR_MPS[3] = {	"   C",
					"   L",
					"   R"};


constexpr double SAT_POS_UP = -15.0;// [deg]
constexpr double SAT_POS_DN = 12.0;// [deg]


namespace dps
{
	GAX::GAX( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "GAX" ),
		step(EXEC_DT), bET_SEP_INH(false), bMPS_CMD{false, false, false}, bMPS_DATA{false, false, false}, bMPS_ELEC{false, false, false}, bMPS_HYD{false, false, false},
		bOTT_ST_IN(false), bROLL_REF(false), bSSME_FAIL{false,false,false}, bSW_TO_MEP(false), bDAP_DNMODE_RHC(false), bFCS_SAT_POS(false), bSPD_BRK(false), bTGT_DELTA_T(false),
		bTGT_EL_ANG(false), bTGT_ITER(false), bL_OMS_GMBL(false), bR_OMS_GMBL(false), bRCS_ON{}, bRCS_LK{}, bRCS_OFF{}
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
		if (ReadCOMPOOL_IS( SCP_REF_ROL_STAT ) == 1)
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
		if (ReadCOMPOOL_IS( SCP_DAP_ALERT ) == 1)
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
		if (((GetMajorMode() != 305) && (GetMajorMode() != 603)) || (ReadCOMPOOL_IS( SCP_WOWLON ) == 0))
		{
			float LOB_ELVN_POS_FDBK = ReadCOMPOOL_SS( SCP_LOB_ELVN_POS_FDBK );
			float LIB_ELVN_POS_FDBK = ReadCOMPOOL_SS( SCP_LIB_ELVN_POS_FDBK );
			float RIB_ELVN_POS_FDBK = ReadCOMPOOL_SS( SCP_RIB_ELVN_POS_FDBK );
			float ROB_ELVN_POS_FDBK = ReadCOMPOOL_SS( SCP_ROB_ELVN_POS_FDBK );
			bool sat = false;
			
			if (LOB_ELVN_POS_FDBK > SAT_POS_DN)
			{
				sat = true;
				WriteCOMPOOL_IS( SCP_LOB_HI_LO_SATURATION_STATUS, 1 );
			}
			else if (LOB_ELVN_POS_FDBK < SAT_POS_UP)
			{
				sat = true;
				WriteCOMPOOL_IS( SCP_LOB_HI_LO_SATURATION_STATUS, 0 );
			}
			else
			{
				WriteCOMPOOL_IS( SCP_LOB_HI_LO_SATURATION_STATUS, 2 );
			}

			if (LIB_ELVN_POS_FDBK > SAT_POS_DN)
			{
				sat = true;
				WriteCOMPOOL_IS( SCP_LIB_HI_LO_SATURATION_STATUS, 1 );
			}
			else if (LIB_ELVN_POS_FDBK < SAT_POS_UP)
			{
				sat = true;
				WriteCOMPOOL_IS( SCP_LIB_HI_LO_SATURATION_STATUS, 0 );
			}
			else
			{
				WriteCOMPOOL_IS( SCP_LIB_HI_LO_SATURATION_STATUS, 2 );
			}

			if (ROB_ELVN_POS_FDBK > SAT_POS_DN)
			{
				sat = true;
				WriteCOMPOOL_IS( SCP_ROB_HI_LO_SATURATION_STATUS, 1 );
			}
			else if (ROB_ELVN_POS_FDBK < SAT_POS_UP)
			{
				sat = true;
				WriteCOMPOOL_IS( SCP_ROB_HI_LO_SATURATION_STATUS, 0 );
			}
			else
			{
				WriteCOMPOOL_IS( SCP_ROB_HI_LO_SATURATION_STATUS, 2 );
			}

			if (RIB_ELVN_POS_FDBK > SAT_POS_DN)
			{
				sat = true;
				WriteCOMPOOL_IS( SCP_RIB_HI_LO_SATURATION_STATUS, 1 );
			}
			else if (RIB_ELVN_POS_FDBK < SAT_POS_UP)
			{
				sat = true;
				WriteCOMPOOL_IS( SCP_RIB_HI_LO_SATURATION_STATUS, 0 );
			}
			else
			{
				WriteCOMPOOL_IS( SCP_RIB_HI_LO_SATURATION_STATUS, 2 );
			}
			
			if (sat)
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
				}
			}
			else bFCS_SAT_POS = false;
		}
		return;
	}

	void GAX::SPD_BRK( void )// class 3
	{
		if (ReadCOMPOOL_IS( SCP_SPEED_BRAKE_CREW_ALERT ) == 1)
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

	void GAX::TGT_DELTA_T(void)
	{
		if (ReadCOMPOOL_IS(SCP_TGT_DELTA_T_CREW_ALERT) == 1)
		{
			if (!bTGT_DELTA_T)
			{
				bTGT_DELTA_T = true;
				unsigned int j = ReadCOMPOOL_IS(SCP_FAULT_IN_IDX);
				if (j < 5)
				{
					WriteCOMPOOL_AC(SCP_FAULT_IN_MSG, j, CRTMSG_TGT_DELTA_T, 5, 19);
					WriteCOMPOOL_AIS(SCP_FAULT_IN_CWCLASS, j, 3, 5);
					WriteCOMPOOL_IS(SCP_FAULT_IN_IDX, ++j);
				}
			}
		}
		else bTGT_DELTA_T = false;
		return;
	}

	void GAX::TGT_EL_ANG(void)
	{
		if (ReadCOMPOOL_IS(SCP_TGT_EL_ANG_CREW_ALERT) == 1)
		{
			if (!bTGT_EL_ANG)
			{
				bTGT_EL_ANG = true;
				unsigned int j = ReadCOMPOOL_IS(SCP_FAULT_IN_IDX);
				if (j < 5)
				{
					WriteCOMPOOL_AC(SCP_FAULT_IN_MSG, j, CRTMSG_TGT_EL_ANG, 5, 19);
					WriteCOMPOOL_AIS(SCP_FAULT_IN_CWCLASS, j, 3, 5);
					WriteCOMPOOL_IS(SCP_FAULT_IN_IDX, ++j);
				}
			}
		}
		else bTGT_EL_ANG = false;
		return;
	}

	void GAX::TGT_ITER(void)
	{
		if (ReadCOMPOOL_IS(SCP_TGT_ITER_CREW_ALERT) == 1)
		{
			if (!bTGT_ITER)
			{
				bTGT_ITER = true;
				unsigned int j = ReadCOMPOOL_IS(SCP_FAULT_IN_IDX);
				if (j < 5)
				{
					WriteCOMPOOL_AC(SCP_FAULT_IN_MSG, j, CRTMSG_TGT_ITER, 5, 19);
					WriteCOMPOOL_AIS(SCP_FAULT_IN_CWCLASS, j, 3, 5);
					WriteCOMPOOL_IS(SCP_FAULT_IN_IDX, ++j);
				}
			}
		}
		else bTGT_ITER = false;
		return;
	}

	void GAX::L_OMS_GMBL( void )// class 2
	{
		if ((ReadCOMPOOL_IS( SCP_OMSL_PITCH_FAIL ) == 1) ||
			(ReadCOMPOOL_IS( SCP_OMSL_YAW_FAIL ) == 1))
		{
			if (!bL_OMS_GMBL)
			{
				bL_OMS_GMBL = true;
				unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
				if (j < 5)
				{
					WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, CRTMSG_L_OMS_GMBL, 5, 19 );
					WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 2, 5 );
					WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
				}
			}
		}
		else bL_OMS_GMBL = false;
		return;
	}

	void GAX::R_OMS_GMBL( void )// class 2
	{
		if ((ReadCOMPOOL_IS( SCP_OMSR_PITCH_FAIL ) == 1) ||
			(ReadCOMPOOL_IS( SCP_OMSR_YAW_FAIL ) == 1))
		{
			if (!bR_OMS_GMBL)
			{
				bR_OMS_GMBL = true;
				unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
				if (j < 5)
				{
					WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, CRTMSG_R_OMS_GMBL, 5, 19 );
					WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 2, 5 );
					WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
				}
			}
		}
		else bR_OMS_GMBL = false;
		return;
	}

	void GAX::RCS( void )// class 2
	{
		bool RCS_ON[44];
		bool RCS_LK[44];
		bool RCS_OFF[44];
		for (int i = 0; i < 44; i++)
		{
			RCS_ON[i] = ReadCOMPOOL_AIS( SCP_JET_FAILED_ON, i + 1, 44 );
			RCS_LK[i] = ReadCOMPOOL_AIS( SCP_JET_LEAKING, i + 1, 44 );
			RCS_OFF[i] = ReadCOMPOOL_AIS( SCP_JET_FAILED_OFF, i + 1, 44 );
		}

		// fault message
		// FxF
		if ((RCS_ON[0] != bRCS_ON[0]) || (RCS_ON[4] != bRCS_ON[4]) || (RCS_ON[8] != bRCS_ON[8]) ||
			(RCS_LK[0] != bRCS_LK[0]) || (RCS_LK[4] != bRCS_LK[4]) || (RCS_LK[8] != bRCS_LK[8]) ||
			(RCS_OFF[0] != bRCS_OFF[0]) || (RCS_OFF[4] != bRCS_OFF[4]) || (RCS_OFF[8] != bRCS_OFF[8]))
		{
			unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
			if (j < 5)
			{
				WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, CRTMSG_F_RCS_FJET, 5, 19 );
				WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 2, 5 );
				WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
			}
		}

		// FxL
		if ((RCS_ON[1] != bRCS_ON[1]) || (RCS_ON[9] != bRCS_ON[9]) || (RCS_ON[14] != bRCS_ON[14]) ||
			(RCS_LK[1] != bRCS_LK[1]) || (RCS_LK[9] != bRCS_LK[9]) || (RCS_LK[14] != bRCS_LK[14]) ||
			(RCS_OFF[1] != bRCS_OFF[1]) || (RCS_OFF[9] != bRCS_OFF[9]) || (RCS_OFF[14] != bRCS_OFF[14]))
		{
			unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
			if (j < 5)
			{
				WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, CRTMSG_F_RCS_LJET, 5, 19 );
				WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 2, 5 );
				WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
			}
		}

		// FxR
		if ((RCS_ON[5] != bRCS_ON[5]) || (RCS_ON[12] != bRCS_ON[12]) || (RCS_ON[15] != bRCS_ON[15]) ||
			(RCS_LK[5] != bRCS_LK[5]) || (RCS_LK[12] != bRCS_LK[12]) || (RCS_LK[15] != bRCS_LK[15]) ||
			(RCS_OFF[5] != bRCS_OFF[5]) || (RCS_OFF[12] != bRCS_OFF[12]) || (RCS_OFF[15] != bRCS_OFF[15]))
		{
			unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
			if (j < 5)
			{
				WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, CRTMSG_F_RCS_RJET, 5, 19 );
				WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 2, 5 );
				WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
			}
		}

		// FxU
		if ((RCS_ON[2] != bRCS_ON[2]) || (RCS_ON[6] != bRCS_ON[6]) || (RCS_ON[10] != bRCS_ON[10]) ||
			(RCS_LK[2] != bRCS_LK[2]) || (RCS_LK[6] != bRCS_LK[6]) || (RCS_LK[10] != bRCS_LK[10]) ||
			(RCS_OFF[2] != bRCS_OFF[2]) || (RCS_OFF[6] != bRCS_OFF[6]) || (RCS_OFF[10] != bRCS_OFF[10]))
		{
			unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
			if (j < 5)
			{
				WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, CRTMSG_F_RCS_UJET, 5, 19 );
				WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 2, 5 );
				WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
			}
		}

		// LxD
		if ((RCS_ON[21] != bRCS_ON[21]) || (RCS_ON[24] != bRCS_ON[24]) || (RCS_ON[27] != bRCS_ON[27]) || (RCS_ON[28] != bRCS_ON[28]) ||
			(RCS_LK[21] != bRCS_LK[21]) || (RCS_LK[24] != bRCS_LK[24]) || (RCS_LK[27] != bRCS_LK[27]) || (RCS_LK[28] != bRCS_LK[28]) ||
			(RCS_OFF[21] != bRCS_OFF[21]) || (RCS_OFF[24] != bRCS_OFF[24]) || (RCS_OFF[27] != bRCS_OFF[27]) || (RCS_OFF[28] != bRCS_OFF[28]))
		{
			unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
			if (j < 5)
			{
				WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, CRTMSG_L_RCS_DJET, 5, 19 );
				WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 2, 5 );
				WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
			}
		}

		// LxL
		if ((RCS_ON[17] != bRCS_ON[17]) || (RCS_ON[19] != bRCS_ON[19]) || (RCS_ON[23] != bRCS_ON[23]) || (RCS_ON[25] != bRCS_ON[25]) || (RCS_ON[29] != bRCS_ON[29]) ||
			(RCS_LK[17] != bRCS_LK[17]) || (RCS_LK[19] != bRCS_LK[19]) || (RCS_LK[23] != bRCS_LK[23]) || (RCS_LK[25] != bRCS_LK[25]) || (RCS_LK[29] != bRCS_LK[29]) ||
			(RCS_OFF[17] != bRCS_OFF[17]) || (RCS_OFF[19] != bRCS_OFF[19]) || (RCS_OFF[23] != bRCS_OFF[23]) || (RCS_OFF[25] != bRCS_OFF[25]) || (RCS_OFF[29] != bRCS_OFF[29]))
		{
			unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
			if (j < 5)
			{
				WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, CRTMSG_L_RCS_LJET, 5, 19 );
				WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 2, 5 );
				WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
			}
		}

		// LxU
		if ((RCS_ON[18] != bRCS_ON[18]) || (RCS_ON[20] != bRCS_ON[20]) || (RCS_ON[26] != bRCS_ON[26]) ||
			(RCS_LK[18] != bRCS_LK[18]) || (RCS_LK[20] != bRCS_LK[20]) || (RCS_LK[26] != bRCS_LK[26]) ||
			(RCS_OFF[18] != bRCS_OFF[18]) || (RCS_OFF[20] != bRCS_OFF[20]) || (RCS_OFF[26] != bRCS_OFF[26]))
		{
			unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
			if (j < 5)
			{
				WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, CRTMSG_L_RCS_UJET, 5, 19 );
				WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 2, 5 );
				WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
			}
		}

		// LxA
		if ((RCS_ON[16] != bRCS_ON[16]) || (RCS_ON[22] != bRCS_ON[22]) ||
			(RCS_LK[16] != bRCS_LK[16]) || (RCS_LK[22] != bRCS_LK[22]) ||
			(RCS_OFF[16] != bRCS_OFF[16]) || (RCS_OFF[22] != bRCS_OFF[22]))
		{
			unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
			if (j < 5)
			{
				WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, CRTMSG_L_RCS_AJET, 5, 19 );
				WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 2, 5 );
				WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
			}
		}

		// RxD
		if ((RCS_ON[35] != bRCS_ON[35]) || (RCS_ON[38] != bRCS_ON[38]) || (RCS_ON[41] != bRCS_ON[41]) || (RCS_ON[42] != bRCS_ON[42]) ||
			(RCS_LK[35] != bRCS_LK[35]) || (RCS_LK[38] != bRCS_LK[38]) || (RCS_LK[41] != bRCS_LK[41]) || (RCS_LK[42] != bRCS_LK[42]) ||
			(RCS_OFF[35] != bRCS_OFF[35]) || (RCS_OFF[38] != bRCS_OFF[38]) || (RCS_OFF[41] != bRCS_OFF[41]) || (RCS_OFF[42] != bRCS_OFF[42]))
		{
			unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
			if (j < 5)
			{
				WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, CRTMSG_R_RCS_DJET, 5, 19 );
				WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 2, 5 );
				WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
			}
		}

		// RxR
		if ((RCS_ON[31] != bRCS_ON[31]) || (RCS_ON[33] != bRCS_ON[33]) || (RCS_ON[37] != bRCS_ON[37]) || (RCS_ON[39] != bRCS_ON[39]) || (RCS_ON[43] != bRCS_ON[43]) ||
			(RCS_LK[31] != bRCS_LK[31]) || (RCS_LK[33] != bRCS_LK[33]) || (RCS_LK[37] != bRCS_LK[37]) || (RCS_LK[39] != bRCS_LK[39]) || (RCS_LK[43] != bRCS_LK[43]) ||
			(RCS_OFF[31] != bRCS_OFF[31]) || (RCS_OFF[33] != bRCS_OFF[33]) || (RCS_OFF[37] != bRCS_OFF[37]) || (RCS_OFF[39] != bRCS_OFF[39]) || (RCS_OFF[43] != bRCS_OFF[43]))
		{
			unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
			if (j < 5)
			{
				WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, CRTMSG_R_RCS_RJET, 5, 19 );
				WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 2, 5 );
				WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
			}
		}

		// RxU
		if ((RCS_ON[32] != bRCS_ON[32]) || (RCS_ON[34] != bRCS_ON[34]) || (RCS_ON[40] != bRCS_ON[40]) ||
			(RCS_LK[32] != bRCS_LK[32]) || (RCS_LK[34] != bRCS_LK[34]) || (RCS_LK[40] != bRCS_LK[40]) ||
			(RCS_OFF[32] != bRCS_OFF[32]) || (RCS_OFF[34] != bRCS_OFF[34]) || (RCS_OFF[40] != bRCS_OFF[40]))
		{
			unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
			if (j < 5)
			{
				WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, CRTMSG_R_RCS_UJET, 5, 19 );
				WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 2, 5 );
				WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
			}
		}

		// RxA
		if ((RCS_ON[30] != bRCS_ON[30]) || (RCS_ON[36] != bRCS_ON[36]) ||
			(RCS_LK[30] != bRCS_LK[30]) || (RCS_LK[36] != bRCS_LK[36]) ||
			(RCS_OFF[30] != bRCS_OFF[30]) || (RCS_OFF[36] != bRCS_OFF[36]))
		{
			unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
			if (j < 5)
			{
				WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, CRTMSG_R_RCS_AJET, 5, 19 );
				WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 2, 5 );
				WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
			}
		}

		for (int i = 0; i < 44; i++)
		{
			bRCS_ON[i] = RCS_ON[i];
			bRCS_LK[i] = RCS_LK[i];
			bRCS_OFF[i] = RCS_OFF[i];
		}
		return;
	}

	void GAX::RCSJetManifStatus( const unsigned int addr, const unsigned int idx, const bool ona, const bool onb, const bool onc, const bool ond, const bool lka, const bool lkb, const bool lkc, const bool lkd, const bool offa, const bool offb, const bool offc, const bool offd )
	{
		if (ona || onb || onc || ond) WriteCOMPOOL_AC( addr, idx, "ON ", 15, 3 );
		else if (lka || lkb || lkc || lkd) WriteCOMPOOL_AC( addr, idx, "LK ", 15, 3 );
		else if (offa || offb || offc || offd) WriteCOMPOOL_AC( addr, idx, "OFF", 15, 3 );
		else WriteCOMPOOL_AC( addr, idx, "   ", 15, 3 );
		return;
	}

	void GAX::RCSManifOPCLIOStatus( const unsigned int dilemmaaddr, const unsigned int dilemmaidx, const unsigned int outaddr, const unsigned int outidx, const unsigned int outsz )
	{
		// TODO commfaults
		if (0 || 0) WriteCOMPOOL_AC( outaddr, outidx, "M", outsz, 1 );
		else if (ReadCOMPOOL_AIS( dilemmaaddr, dilemmaidx, 15 ) == 1) WriteCOMPOOL_AC( outaddr, outidx, "?", outsz, 1 );
		else WriteCOMPOOL_AC( outaddr, outidx, " ", outsz, 1 );
		return;
	}

	void GAX::GNCSYSSUMM1SupportProcessing( void )
	{
		// RCS Jet Manifold Status-Entry/Ascent/Orbit
		bool RCS_ON[44];
		bool RCS_LK[44];
		bool RCS_OFF[44];
		for (int i = 0; i < 44; i++)
		{
			RCS_ON[i] = ReadCOMPOOL_AIS( SCP_JET_FAILED_ON, i + 1, 44 );
			RCS_LK[i] = ReadCOMPOOL_AIS( SCP_JET_LEAKING, i + 1, 44 );
			RCS_OFF[i] = ReadCOMPOOL_AIS( SCP_JET_FAILED_OFF, i + 1, 44 );
		}

		RCSJetManifStatus( SCP_JET_FAIL_ON_LK_OFF, 1, RCS_ON[0], RCS_ON[1], RCS_ON[2], RCS_ON[3], RCS_LK[0], RCS_LK[1], RCS_LK[2], RCS_LK[3], RCS_OFF[0], RCS_OFF[1], RCS_OFF[2], RCS_OFF[3] );// F1
		RCSJetManifStatus( SCP_JET_FAIL_ON_LK_OFF, 2, RCS_ON[4], RCS_ON[5], RCS_ON[6], RCS_ON[7], RCS_LK[4], RCS_LK[5], RCS_LK[6], RCS_LK[7], RCS_OFF[4], RCS_OFF[5], RCS_OFF[6], RCS_OFF[7] );// F2
		RCSJetManifStatus( SCP_JET_FAIL_ON_LK_OFF, 3, RCS_ON[8], RCS_ON[9], RCS_ON[10], RCS_ON[11], RCS_LK[8], RCS_LK[9], RCS_LK[10], RCS_LK[11], RCS_OFF[8], RCS_OFF[9], RCS_OFF[10], RCS_OFF[11] );// F3
		RCSJetManifStatus( SCP_JET_FAIL_ON_LK_OFF, 4, RCS_ON[12], RCS_ON[13], false, false, RCS_LK[12], RCS_LK[13], false, false, RCS_OFF[12], RCS_OFF[13], false, false );// F4
		RCSJetManifStatus( SCP_JET_FAIL_ON_LK_OFF, 5, RCS_ON[14], RCS_ON[15], false, false, RCS_LK[14], RCS_LK[15], false, false, RCS_OFF[14], RCS_OFF[15], false, false );// F5
		RCSJetManifStatus( SCP_JET_FAIL_ON_LK_OFF, 6, RCS_ON[16], RCS_ON[17], RCS_ON[18], false, RCS_LK[16], RCS_LK[17], RCS_LK[18], false, RCS_OFF[16], RCS_OFF[17], RCS_OFF[18], false );// L1
		RCSJetManifStatus( SCP_JET_FAIL_ON_LK_OFF, 7, RCS_ON[19], RCS_ON[20], RCS_ON[21], false, RCS_LK[19], RCS_LK[20], RCS_LK[21], false, RCS_OFF[19], RCS_OFF[20], RCS_OFF[21], false );// L2
		RCSJetManifStatus( SCP_JET_FAIL_ON_LK_OFF, 8, RCS_ON[22], RCS_ON[23], RCS_ON[24], false, RCS_LK[22], RCS_LK[23], RCS_LK[24], false, RCS_OFF[22], RCS_OFF[23], RCS_OFF[24], false );// L3
		RCSJetManifStatus( SCP_JET_FAIL_ON_LK_OFF, 9, RCS_ON[25], RCS_ON[26], RCS_ON[27], false, RCS_LK[25], RCS_LK[26], RCS_LK[27], false, RCS_OFF[25], RCS_OFF[26], RCS_OFF[27], false );// L4
		RCSJetManifStatus( SCP_JET_FAIL_ON_LK_OFF, 10, RCS_ON[28], RCS_ON[29], false, false, RCS_LK[28], RCS_LK[29], false, false, RCS_OFF[28], RCS_OFF[29], false, false );// L5
		RCSJetManifStatus( SCP_JET_FAIL_ON_LK_OFF, 11, RCS_ON[30], RCS_ON[31], RCS_ON[32], false, RCS_LK[30], RCS_LK[31], RCS_LK[32], false, RCS_OFF[30], RCS_OFF[31], RCS_OFF[32], false );// R1
		RCSJetManifStatus( SCP_JET_FAIL_ON_LK_OFF, 12, RCS_ON[33], RCS_ON[34], RCS_ON[35], false, RCS_LK[33], RCS_LK[34], RCS_LK[35], false, RCS_OFF[33], RCS_OFF[34], RCS_OFF[35], false );// R2
		RCSJetManifStatus( SCP_JET_FAIL_ON_LK_OFF, 13, RCS_ON[36], RCS_ON[37], RCS_ON[38], false, RCS_LK[36], RCS_LK[37], RCS_LK[38], false, RCS_OFF[36], RCS_OFF[37], RCS_OFF[38], false );// R3
		RCSJetManifStatus( SCP_JET_FAIL_ON_LK_OFF, 14, RCS_ON[39], RCS_ON[40], RCS_ON[41], false, RCS_LK[39], RCS_LK[40], RCS_LK[41], false, RCS_OFF[39], RCS_OFF[40], RCS_OFF[41], false );// R4
		RCSJetManifStatus( SCP_JET_FAIL_ON_LK_OFF, 15, RCS_ON[42], RCS_ON[43], false, false, RCS_LK[42], RCS_LK[43], false, false, RCS_OFF[42], RCS_OFF[43], false, false );// R5

		// RCS Isolation OP/CL I/O Status
		for (int i = 1; i <= 15; i++) RCSManifOPCLIOStatus( SCP_RCS_MANF_RM_DILEMMA_FLAG, i, SCP_RCS_MANF_ISLN_VLV_OP_CL_IO_STAT, i, 15 );

		// Hinge Moment Conversion and Status

		// Elevon Position Saturation Status

		// Controller/Sensor Status

		// FCS SRB/MPS/AERO Status
		return;
	}

	void GAX::OnPostStep( double simt, double simdt, double mjd )
	{
		step += simdt;
		if (step < EXEC_DT) return;

		GNCSYSSUMM1SupportProcessing();// TODO find processing rate

		switch (ReadCOMPOOL_IS( SCP_MM ))
		{
			case 101:
				MPS_CMD_X();
				MPS_DATA_X();
				MPS_ELEC_X();
				MPS_HYD_X();
				RCS();
				break;
			case 102:
				MPS_CMD_X();
				MPS_DATA_X();
				MPS_ELEC_X();
				MPS_HYD_X();
				SSME_FAIL_X();
				ET_SEP_INH();
				RCS();
				break;
			case 103:
				MPS_CMD_X();
				MPS_DATA_X();
				MPS_ELEC_X();
				MPS_HYD_X();
				SSME_FAIL_X();
				ET_SEP_INH();
				RCS();
				break;
			case 104:
				MPS_CMD_X();
				MPS_DATA_X();
				ET_SEP_INH();
				L_OMS_GMBL();
				R_OMS_GMBL();
				RCS();
				break;
			case 105:
				L_OMS_GMBL();
				R_OMS_GMBL();
				RCS();
				break;
			case 106:
				L_OMS_GMBL();
				R_OMS_GMBL();
				RCS();
				break;
			case 201:
				TGT_DELTA_T();
				TGT_EL_ANG();
				TGT_ITER();
				RCS();
				break;
			case 202:
				TGT_DELTA_T();
				TGT_EL_ANG();
				TGT_ITER();
				L_OMS_GMBL();
				R_OMS_GMBL();
				RCS();
				break;
			case 301:
				ROLL_REF();
				FCS_SAT_POS();
				L_OMS_GMBL();
				R_OMS_GMBL();
				RCS();
				break;
			case 302:
				ROLL_REF();
				FCS_SAT_POS();
				L_OMS_GMBL();
				R_OMS_GMBL();
				RCS();
				break;
			case 303:
				ROLL_REF();
				FCS_SAT_POS();
				L_OMS_GMBL();
				R_OMS_GMBL();
				RCS();
				break;
			case 304:
				ROLL_REF();
				DAP_DNMODE_RHC();
				FCS_SAT_POS();
				SPD_BRK();
				L_OMS_GMBL();
				R_OMS_GMBL();
				RCS();
				break;
			case 305:
				OTT_ST_IN();
				ROLL_REF();
				SW_TO_MEP();
				DAP_DNMODE_RHC();
				FCS_SAT_POS();
				SPD_BRK();
				RCS();
				break;
			case 601:
				MPS_CMD_X();
				MPS_DATA_X();
				MPS_ELEC_X();
				MPS_HYD_X();
				SSME_FAIL_X();
				RCS();
				break;
			case 602:
				DAP_DNMODE_RHC();
				FCS_SAT_POS();
				SPD_BRK();
				RCS();
				break;
			case 603:
				OTT_ST_IN();
				SW_TO_MEP();
				DAP_DNMODE_RHC();
				FCS_SAT_POS();
				SPD_BRK();
				RCS();
				break;
			case 801:
				RCS();
				break;
			case 901:
				break;
			default:
				break;
		}

		if (bFCS_SAT_POS) WriteCOMPOOL_IS( SCP_FF3_IOM5_CH1_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM5_CH1_DATA ) | 0x0020 );
		if (bL_OMS_GMBL || bR_OMS_GMBL) WriteCOMPOOL_IS( SCP_FF3_IOM5_CH1_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM5_CH1_DATA ) | 0x0002 );
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
		else if (!_strnicmp(keyword, "TGT_DELTA_T", 11))
		{
			sscanf_s(value, "%u", &tmp1);
			bTGT_DELTA_T = (tmp1 == 1);
			return true;
		}
		else if (!_strnicmp(keyword, "TGT_EL_ANG", 10))
		{
			sscanf_s(value, "%u", &tmp1);
			bTGT_EL_ANG = (tmp1 == 1);
			return true;
		}
		else if (!_strnicmp(keyword, "TGT_ITER", 8))
		{
			sscanf_s(value, "%u", &tmp1);
			bTGT_ITER = (tmp1 == 1);
			return true;
		}
		else if (!_strnicmp( keyword, "L_OMS_GMBL", 10 ))
		{
			sscanf_s( value, "%u", &tmp1 );
			bL_OMS_GMBL = (tmp1 == 1);
			return true;
		}
		else if (!_strnicmp( keyword, "R_OMS_GMBL", 10 ))
		{
			sscanf_s( value, "%u", &tmp1 );
			bR_OMS_GMBL = (tmp1 == 1);
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
		oapiWriteScenario_int(scn, "TGT_DELTA_T", bTGT_DELTA_T ? 1 : 0);
		oapiWriteScenario_int(scn, "TGT_EL_ANG", bTGT_EL_ANG ? 1 : 0);
		oapiWriteScenario_int(scn, "TGT_ITER", bTGT_ITER ? 1 : 0);
		oapiWriteScenario_int( scn, "L_OMS_GMBL", bL_OMS_GMBL ? 1 : 0 );
		oapiWriteScenario_int( scn, "R_OMS_GMBL", bR_OMS_GMBL ? 1 : 0 );
		return;
	}
}

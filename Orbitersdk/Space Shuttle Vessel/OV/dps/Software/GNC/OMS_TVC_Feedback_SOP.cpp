/******* SSV File Modification Notice *******
Date         Developer
2020/04/07   GLS
2020/06/20   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/12/28   GLS
********************************************/
#include "OMS_TVC_Feedback_SOP.h"
#include <cassert>


namespace dps
{
	// K-LOADs
	constexpr float COMSLPFB = 1.64f;// COMP SCALE FACTOR – OMS L PITCH FDBK (V97U3972C) [deg/vdc]
	constexpr float COMSLYFB = 1.636f;// COMP SCALE FACTOR – OMS L YAW FDBK (V97U3974C) [deg/vdc]
	constexpr float COMSRPFB = 1.64f;// COMP SCALE FACTOR – OMS R PITCH FDBK (V97U3976C) [deg/vdc]
	constexpr float COMSRYFB = -1.636f;// COMP SCALE FACTOR – OMS R YAW FDBK (V97U3978C) [deg/vdc]
	constexpr float KOMSLPFB = 0.0735f;// COMP BIAS–OMS L PITCH FDBK (V97U4083C) [deg]
	constexpr float KOMSLYFB = 0.4244f;// COMP BIAS–OMS L YAW FDBK (V97U4085C) [deg]
	constexpr float KOMSRPFB = 0.0735f;// COMP BIAS–OMS R PITCH FDBK (V97U4087C) [deg]
	constexpr float KOMSRYFB = -0.4244f;// COMP BIAS–OMS R YAW FDBK (V97U4089C) [deg]


	OMSTVCFDBK_SOP::OMSTVCFDBK_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "OMS_TVC_Feedback_SOP" )
	{
		return;
	}

	OMSTVCFDBK_SOP::~OMSTVCFDBK_SOP( void )
	{
		return;
	}

	void OMSTVCFDBK_SOP::Realize( void )
	{
		return;
	}

	void OMSTVCFDBK_SOP::OnPreStep( double simt, double simdt, double mjd )
	{
		unsigned short Lsel = ReadCOMPOOL_IS( SCP_OMSL_ACT_SEL );
		unsigned short Rsel = ReadCOMPOOL_IS( SCP_OMSR_ACT_SEL );

		// HACK source commfaults from MDM status
		unsigned int COMMFAULT_WORD_1 = ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 );
		bool commfaultFA1 = (COMMFAULT_WORD_1 & 0x00001000) != 0;
		bool commfaultFA2 = (COMMFAULT_WORD_1 & 0x00002000) != 0;
		bool commfaultFA3 = (COMMFAULT_WORD_1 & 0x00004000) != 0;
		bool commfaultFA4 = (COMMFAULT_WORD_1 & 0x00008000) != 0;
		unsigned short LOMSPPCF = commfaultFA1 ? 1 : 0;
		unsigned short LOMSPYCF = commfaultFA1 ? 1 : 0;
		unsigned short LOMSSPCF = commfaultFA2 ? 1 : 0;
		unsigned short LOMSSYCF = commfaultFA2 ? 1 : 0;
		unsigned short ROMSPPCF = commfaultFA4 ? 1 : 0;
		unsigned short ROMSPYCF = commfaultFA4 ? 1 : 0;
		unsigned short ROMSSPCF = commfaultFA3 ? 1 : 0;
		unsigned short ROMSSYCF = commfaultFA3 ? 1 : 0;

		switch (GetMajorMode())
		{
			case 101:
			case 102:
			case 103:
			case 601:
				// output active, standby and selected pos
				// left pitch active
				WriteCOMPOOL_SS( SCP_AOMSLPFDBK, (ReadCOMPOOL_IS( SCP_FA1_IOM14_CH14_DATA ) * COMSLPFB) + KOMSLPFB );
				// left yaw active
				WriteCOMPOOL_SS( SCP_AOMSLYFDBK, (ReadCOMPOOL_IS( SCP_FA1_IOM14_CH15_DATA ) * COMSLYFB) + KOMSLYFB );
				// right pitch active
				WriteCOMPOOL_SS( SCP_AOMSLPFDBK, (ReadCOMPOOL_IS( SCP_FA4_IOM14_CH14_DATA ) * COMSRPFB) + KOMSRPFB );
				// right yaw active
				WriteCOMPOOL_SS( SCP_AOMSLYFDBK, (ReadCOMPOOL_IS( SCP_FA4_IOM14_CH15_DATA ) * COMSRYFB) + KOMSRYFB );

				// left pitch standby
				WriteCOMPOOL_SS( SCP_SOMSLPFDBK, (ReadCOMPOOL_IS( SCP_FA2_IOM14_CH14_DATA ) * COMSLPFB) + KOMSLPFB );
				// left yaw standby
				WriteCOMPOOL_SS( SCP_SOMSLYFDBK, (ReadCOMPOOL_IS( SCP_FA2_IOM14_CH15_DATA ) * COMSLYFB) + KOMSLYFB );
				// right pitch standby
				WriteCOMPOOL_SS( SCP_SOMSLPFDBK, (ReadCOMPOOL_IS( SCP_FA3_IOM14_CH14_DATA ) * COMSRPFB) + KOMSRPFB );
				// right yaw standby
				WriteCOMPOOL_SS( SCP_SOMSLYFDBK, (ReadCOMPOOL_IS( SCP_FA3_IOM14_CH15_DATA ) * COMSRYFB) + KOMSRYFB );
			default:
				// output selected pos
				// left pitch
				if (Lsel != 2)
				{
					if ((Lsel == 0) && (LOMSPPCF == 0))
					{
						WriteCOMPOOL_SS( SCP_SOMSLPFDBK, (ReadCOMPOOL_IS( SCP_FA1_IOM14_CH14_DATA ) * COMSLPFB) + KOMSLPFB );
						WriteCOMPOOL_IS( SCP_LOMSPDG, 1 );
					}
					else if (/*(Lsel == 1) &&*/ (LOMSSPCF == 0))
					{
						WriteCOMPOOL_SS( SCP_SOMSLPFDBK, (ReadCOMPOOL_IS( SCP_FA2_IOM14_CH14_DATA ) * COMSLPFB) + KOMSLPFB );
						WriteCOMPOOL_IS( SCP_LOMSPDG, 1 );
					}
					else WriteCOMPOOL_IS( SCP_LOMSPDG, 0 );
				}
				else
				{
					if ((LOMSPPCF == 0) && (LOMSSPCF == 0)) WriteCOMPOOL_IS( SCP_LOMSPDG, 1 );
				}

				// left yaw
				if (Lsel != 2)
				{
					if ((Lsel == 0) && (LOMSPYCF == 0))
					{
						WriteCOMPOOL_SS( SCP_SOMSLYFDBK, (ReadCOMPOOL_IS( SCP_FA1_IOM14_CH15_DATA ) * COMSLYFB) + KOMSLYFB );
						WriteCOMPOOL_IS( SCP_LOMSYDG, 1 );
					}
					else if (/*(Lsel == 1) &&*/ (LOMSSYCF == 0))
					{
						WriteCOMPOOL_SS( SCP_SOMSLYFDBK, (ReadCOMPOOL_IS( SCP_FA2_IOM14_CH15_DATA ) * COMSLYFB) + KOMSLYFB );
						WriteCOMPOOL_IS( SCP_LOMSYDG, 1 );
					}
					else WriteCOMPOOL_IS( SCP_LOMSYDG, 0 );
				}
				else
				{
					if ((LOMSPYCF == 0) && (LOMSSYCF == 0)) WriteCOMPOOL_IS( SCP_LOMSYDG, 1 );
				}

				// right pitch
				if (Rsel != 2)
				{
					if ((Rsel == 0) && (ROMSPPCF == 0))
					{
						WriteCOMPOOL_SS( SCP_SOMSRPFDBK, (ReadCOMPOOL_IS( SCP_FA4_IOM14_CH14_DATA ) * COMSRPFB) + KOMSRPFB );
						WriteCOMPOOL_IS( SCP_ROMSPDG, 1 );
					}
					else if (/*(Rsel == 1) &&*/ (ROMSSPCF == 0))
					{
						WriteCOMPOOL_SS( SCP_SOMSRPFDBK, (ReadCOMPOOL_IS( SCP_FA3_IOM14_CH14_DATA ) * COMSRPFB) + KOMSRPFB );
						WriteCOMPOOL_IS( SCP_ROMSPDG, 1 );
					}
					else WriteCOMPOOL_IS( SCP_ROMSPDG, 0 );
				}
				else
				{
					if ((ROMSPPCF == 0) && (ROMSSPCF == 0)) WriteCOMPOOL_IS( SCP_ROMSPDG, 1 );
				}

				// right yaw
				if (Rsel != 2)
				{
					if ((Rsel == 0) && (ROMSPYCF == 0))
					{
						WriteCOMPOOL_SS( SCP_SOMSRYFDBK, (ReadCOMPOOL_IS( SCP_FA4_IOM14_CH15_DATA ) * COMSRYFB) + KOMSRYFB );
						WriteCOMPOOL_IS( SCP_ROMSYDG, 1 );
					}
					else if (/*(Rsel == 1) &&*/ (ROMSSYCF == 0))
					{
						WriteCOMPOOL_SS( SCP_SOMSRYFDBK, (ReadCOMPOOL_IS( SCP_FA3_IOM14_CH15_DATA ) * COMSRYFB) + KOMSRYFB );
						WriteCOMPOOL_IS( SCP_ROMSYDG, 1 );
					}
					else WriteCOMPOOL_IS( SCP_ROMSYDG, 0 );
				}
				else
				{
					if ((ROMSPYCF == 0) && (ROMSSYCF == 0)) WriteCOMPOOL_IS( SCP_ROMSYDG, 1 );
				}
				break;
		}
		return;
	}

	bool OMSTVCFDBK_SOP::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void OMSTVCFDBK_SOP::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	bool OMSTVCFDBK_SOP::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 101:
			case 102:
			case 103:
			case 104:
			case 105:
			case 106:
			case 202:
			case 301:
			case 302:
			case 303:
			case 601:
			case 801:
			case 901:
				return true;
			default:
				return false;
		}
	}
}

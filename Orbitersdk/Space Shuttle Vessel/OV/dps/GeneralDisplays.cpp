/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/04/07   GLS
2020/04/28   GLS
2020/05/08   GLS
2020/06/20   GLS
2020/06/28   GLS
2020/08/24   GLS
2021/06/07   GLS
2021/06/18   GLS
2021/06/26   GLS
2021/06/28   GLS
2021/08/14   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/27   GLS
2021/12/28   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/02/14   GLS
2022/03/24   GLS
2022/06/04   GLS
2022/06/06   GLS
2022/08/05   GLS
2022/08/23   GLS
2022/08/27   GLS
********************************************/
#include "GeneralDisplays.h"
#include "..\Atlantis.h"
#include "IDP.h"
#include "..\vc\MDU.h"
#include "AscentDAP.h"
#include "SSME_Operations.h"
#include "SRBSepSequence.h"
//#include "ETSepSequence.h"
#include "..\APU.h"
#include <MathSSV.h>
#include <EngConst.h>


namespace dps
{
	constexpr double DROOP_ALT = 265000;// ft

	constexpr double ENTRYTRAJ12_X = 17000.0;// [fps]
	constexpr double ENTRYTRAJ23_X = 14000.0;// [fps]
	constexpr double ENTRYTRAJ34_X = 10500.0;// [fps]
	constexpr double ENTRYTRAJ45_X = 6500.0;// [fps]


	constexpr double ETX1C = -228.0444444;// [px]
	constexpr double ETX1C1 = 0.388444444;// [px/NM]
	constexpr double ETX1C2 = -5.11111E-05;// [px/NM^2]
	constexpr double ETY1C = 910.9333333;// [px]
	constexpr double ETY1C1 = -0.035466667;// [px/fps]

	constexpr double ETX2C = -402.9387755;// [px]
	constexpr double ETX2C1 = 1.358367347;// [px/NM]
	constexpr double ETX2C2 = -0.000522449;// [px/NM^2]
	constexpr double ETY2C = 1549.333333;// [px]
	constexpr double ETY2C1 = -0.088666667;// [px/fps]

	constexpr double ETX3C = -724.3596556;// [px]
	constexpr double ETX3C1 = 3.060899139;// [px/NM]
	constexpr double ETX3C2 = -0.001913062;// [px/NM^2]
	constexpr double ETY3C = 1106.0;// [px]
	constexpr double ETY3C1 = -0.076;// [px/fps]

	constexpr double ETX4C = -454.3885052;// [px]
	constexpr double ETX4C1 = 3.934952105;// [px/NM]
	constexpr double ETX4C2 = -0.004098908;// [px/NM^2]
	constexpr double ETY4C = 498.0;// [px]
	constexpr double ETY4C1 = -2.53333E-07;// [px/ft^2/s]

	constexpr double ETX5C = -272.2222222;// [px]
	constexpr double ETX5C1 = 7.111111111;// [px/NM]
	constexpr double ETX5C2 = -0.016161616;// [px/NM^2]
	constexpr double ETY5C = 404.7272727;// [px]
	constexpr double ETY5C1 = -4.83636E-07;// [px/ft^2/s]

	constexpr double VSX1C = -43.33333333;// [px]
	constexpr double VSX1C1 = 0.00104233;// [px/ft]
	constexpr double VSY1C = 398.0;// [px]
	constexpr double VSY1C1 = -0.003;// [px/ft]

	constexpr double VSX2C = -27.22222222;// [px]
	constexpr double VSX2C1 = 0.003200136;// [px/ft]
	constexpr double VSY2C = 392.0;// [px]
	constexpr double VSY2C1 = -0.0112;// [px/ft]

	GeneralDisplays::GeneralDisplays( SimpleGPCSystem* _gpc ):SimpleGPCSoftware( _gpc, "GeneralDisplays" )
	{
		He_T = 0;

		for (int i = 0; i < 32; i++)
		{
			ITEM_STATE_SPEC112[i] = false;
		}

		for (int i = 0; i < 44; i++)
		{
			ITEM_STATE_SPEC113[i] = false;
		}

		CurrentET = 1;
		ET_History_updatetime = 0.0;
		memset( ET_History_X, 0, sizeof(int) * 6 );
		memset( ET_History_X_Drag, 0, sizeof(int) * 6 );
		memset( ET_History_Y, 0, sizeof(int) * 6 );

		ROLLREF_status = false;

		engunit_hex = 0;
		for (int i = 0; i < 6; i++)
		{
			addidvalid[i] = false;
		}

		SPEC23_RCSsel = 1;
		return;
	}

	GeneralDisplays::~GeneralDisplays()
	{
	}

	void GeneralDisplays::Realize()
	{
		pAscentDAP = dynamic_cast<AscentDAP*> (FindSoftware( "AscentDAP" ));
		assert( (pAscentDAP != NULL) && "GeneralDisplays::Realize.pAscentDAP" );
		pSSME_Operations = dynamic_cast<SSME_Operations*> (FindSoftware( "SSME_Operations" ));
		assert( (pSSME_Operations != NULL) && "GeneralDisplays::Realize.pSSME_Operations" );
		pSRBSepSequence = dynamic_cast<SRBSepSequence*> (FindSoftware( "SRBSepSequence" ));
		assert( (pSRBSepSequence != NULL) && "GeneralDisplays::Realize.pSRBSepSequence" );
		//pETSepSequence = dynamic_cast<ETSepSequence*> (FindSoftware( "ETSepSequence" ));
		//assert( (pETSepSequence != NULL) && "GeneralDisplays::Realize.pETSepSequence" );

		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "BFCCRT", 3 );
		dipBFCCRTDisplay.Connect( pBundle, 0 );// ON
		dipBFCCRTSelect[0].Connect( pBundle, 1 ); // 3+1
		dipBFCCRTSelect[1].Connect( pBundle, 2 ); // 1+2

		pBundle = BundleManager()->CreateBundle( "ET_LOX_SENSORS", 16 );
		dipLO2UllagePressureSensor[0].Connect( pBundle, 12 );
		dipLO2UllagePressureSensor[1].Connect( pBundle, 13 );
		dipLO2UllagePressureSensor[2].Connect( pBundle, 14 );

		pBundle = BundleManager()->CreateBundle( "ET_LH2_SENSORS", 16 );
		dipLH2UllagePressureSensor[0].Connect( pBundle, 12 );
		dipLH2UllagePressureSensor[1].Connect( pBundle, 13 );
		dipLH2UllagePressureSensor[2].Connect( pBundle, 14 );

		pBundle = BundleManager()->CreateBundle( "MPS_HE_SENSORS", 12 );
		dipHeSysPressureSensor[0].Connect( pBundle, 0 );
		dipHeSysPressureSensor[1].Connect( pBundle, 1 );
		dipHeSysPressureSensor[2].Connect( pBundle, 2 );
		dipHeSysPressureSensor[3].Connect( pBundle, 3 );
		dipHeSysPressureSensor[4].Connect( pBundle, 4 );
		dipHeSysPressureSensor[5].Connect( pBundle, 5 );
		dipHeSysPressureSensor[6].Connect( pBundle, 6 );
		dipHeSysPressureSensor[7].Connect( pBundle, 7 );
		dipHeSysPressureSensor[8].Connect( pBundle, 8 );
		dipHeSysPressureSensor[9].Connect( pBundle, 9 );
		dipHeSysPressureSensor[10].Connect( pBundle, 10 );
		dipHeSysPressureSensor[11].Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle( "MPS_SENSORS", 2 );
		dipMPSManifPressureSensor[0].Connect( pBundle, 0 );
		dipMPSManifPressureSensor[1].Connect( pBundle, 1 );

		pBundle = BundleManager()->CreateBundle( "LeftRHCTHC_A", 16 );
		for (int i = 0; i < 9; i++) LeftRHC[i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "RightRHC_A", 16 );
		for (int i = 0; i < 9; i++) RightRHC[i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "AftRHCTHC_A", 16 );
		for (int i = 0; i < 9; i++) AftRHC[i].Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "RPTA", 16 );
		for (int i = 0; i < 3; i++)
		{
			LeftRPTA[i].Connect( pBundle, i );
			RightRPTA[i].Connect( pBundle, i + 3 );
		}

		pBundle = BundleManager()->CreateBundle( "LeftSBTC", 16 );
		for (int i = 0; i < 3; i++) LeftSBTC[i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "RightSBTC", 16 );
		for (int i = 0; i < 3; i++) RightSBTC[i].Connect( pBundle, i );

		// init He dP/dT calc
		He_P[0] = dipHeSysPressureSensor[0].GetVoltage() * 1000;
		He_P[1] = dipHeSysPressureSensor[1].GetVoltage() * 1000;
		He_P[2] = dipHeSysPressureSensor[2].GetVoltage() * 1000;
		return;
	}

	void GeneralDisplays::OnPreStep( double simt, double simdt, double mjd )
	{
		////////////////////////////////////////////////////////////////////////////
		/*sprintf_s( oapiDebugString(), 255, "FRCS %d%d %d%d %d%d %d%d %d%d %d%d %d%d %d%d %d%d %d%d %d%d %d%d %d%d %d%d %d%d %d%d",
			(ReadCOMPOOL_IS( SCP_FF2_IOM9_CH0_DATA ) >> 0) & 0x0001, (ReadCOMPOOL_IS( SCP_FF2_IOM6_CH0_DATA ) >> 0) & 0x0001,// F2F
			(ReadCOMPOOL_IS( SCP_FF4_IOM9_CH0_DATA ) >> 0) & 0x0001, (ReadCOMPOOL_IS( SCP_FF4_IOM6_CH0_DATA ) >> 0) & 0x0001,// F3F
			(ReadCOMPOOL_IS( SCP_FF1_IOM9_CH0_DATA ) >> 0) & 0x0001, (ReadCOMPOOL_IS( SCP_FF1_IOM6_CH0_DATA ) >> 0) & 0x0001,// F1F
			(ReadCOMPOOL_IS( SCP_FF1_IOM9_CH0_DATA ) >> 1) & 0x0001, (ReadCOMPOOL_IS( SCP_FF1_IOM6_CH0_DATA ) >> 1) & 0x0001,// F1L
			(ReadCOMPOOL_IS( SCP_FF4_IOM9_CH0_DATA ) >> 1) & 0x0001, (ReadCOMPOOL_IS( SCP_FF4_IOM6_CH0_DATA ) >> 1) & 0x0001,// F3L
			(ReadCOMPOOL_IS( SCP_FF2_IOM9_CH0_DATA ) >> 1) & 0x0001, (ReadCOMPOOL_IS( SCP_FF2_IOM6_CH0_DATA ) >> 1) & 0x0001,// F2R
			(ReadCOMPOOL_IS( SCP_FF3_IOM9_CH0_DATA ) >> 0) & 0x0001, (ReadCOMPOOL_IS( SCP_FF3_IOM6_CH0_DATA ) >> 0) & 0x0001,// F4R
			(ReadCOMPOOL_IS( SCP_FF2_IOM9_CH0_DATA ) >> 2) & 0x0001, (ReadCOMPOOL_IS( SCP_FF2_IOM6_CH0_DATA ) >> 2) & 0x0001,// F2U
			(ReadCOMPOOL_IS( SCP_FF4_IOM9_CH0_DATA ) >> 2) & 0x0001, (ReadCOMPOOL_IS( SCP_FF4_IOM6_CH0_DATA ) >> 2) & 0x0001,// F3U
			(ReadCOMPOOL_IS( SCP_FF1_IOM9_CH0_DATA ) >> 2) & 0x0001, (ReadCOMPOOL_IS( SCP_FF1_IOM6_CH0_DATA ) >> 2) & 0x0001,// F1U
			(ReadCOMPOOL_IS( SCP_FF2_IOM9_CH0_DATA ) >> 3) & 0x0001, (ReadCOMPOOL_IS( SCP_FF2_IOM6_CH0_DATA ) >> 3) & 0x0001,// F2D
			(ReadCOMPOOL_IS( SCP_FF1_IOM9_CH0_DATA ) >> 3) & 0x0001, (ReadCOMPOOL_IS( SCP_FF1_IOM6_CH0_DATA ) >> 3) & 0x0001,// F1D
			(ReadCOMPOOL_IS( SCP_FF3_IOM9_CH0_DATA ) >> 1) & 0x0001, (ReadCOMPOOL_IS( SCP_FF3_IOM6_CH0_DATA ) >> 1) & 0x0001,// F4D
			(ReadCOMPOOL_IS( SCP_FF4_IOM9_CH0_DATA ) >> 3) & 0x0001, (ReadCOMPOOL_IS( SCP_FF4_IOM6_CH0_DATA ) >> 3) & 0x0001,// F3D
			(ReadCOMPOOL_IS( SCP_FF3_IOM9_CH0_DATA ) >> 3) & 0x0001, (ReadCOMPOOL_IS( SCP_FF3_IOM6_CH0_DATA ) >> 3) & 0x0001,// F5R
			(ReadCOMPOOL_IS( SCP_FF3_IOM9_CH0_DATA ) >> 2) & 0x0001, (ReadCOMPOOL_IS( SCP_FF3_IOM6_CH0_DATA ) >> 2) & 0x0001// F5L
		);*/

		/*sprintf_s( oapiDebugString(), 255, "LRCS %d%d %d%d %d%d %d%d %d%d %d%d %d%d %d%d %d%d %d%d %d%d %d%d %d%d %d%d",
			(ReadCOMPOOL_IS( SCP_FA2_IOM8_CH0_DATA ) >> 0) & 0x0001, (ReadCOMPOOL_IS( SCP_FA2_IOM5_CH0_DATA ) >> 0) & 0x0001,// L3A
			(ReadCOMPOOL_IS( SCP_FA1_IOM8_CH0_DATA ) >> 1) & 0x0001, (ReadCOMPOOL_IS( SCP_FA1_IOM5_CH0_DATA ) >> 1) & 0x0001,// L1A
			(ReadCOMPOOL_IS( SCP_FA4_IOM8_CH0_DATA ) >> 0) & 0x0001, (ReadCOMPOOL_IS( SCP_FA4_IOM5_CH0_DATA ) >> 0) & 0x0001,// L4L
			(ReadCOMPOOL_IS( SCP_FA3_IOM8_CH0_DATA ) >> 0) & 0x0001, (ReadCOMPOOL_IS( SCP_FA3_IOM5_CH0_DATA ) >> 0) & 0x0001,// L2L
			(ReadCOMPOOL_IS( SCP_FA2_IOM8_CH0_DATA ) >> 1) & 0x0001, (ReadCOMPOOL_IS( SCP_FA2_IOM5_CH0_DATA ) >> 1) & 0x0001,// L3L
			(ReadCOMPOOL_IS( SCP_FA1_IOM8_CH0_DATA ) >> 1) & 0x0001, (ReadCOMPOOL_IS( SCP_FA1_IOM5_CH0_DATA ) >> 1) & 0x0001,// L1L
			(ReadCOMPOOL_IS( SCP_FA4_IOM8_CH0_DATA ) >> 1) & 0x0001, (ReadCOMPOOL_IS( SCP_FA4_IOM5_CH0_DATA ) >> 1) & 0x0001,// L4U
			(ReadCOMPOOL_IS( SCP_FA3_IOM8_CH0_DATA ) >> 1) & 0x0001, (ReadCOMPOOL_IS( SCP_FA3_IOM5_CH0_DATA ) >> 1) & 0x0001,// L2U
			(ReadCOMPOOL_IS( SCP_FA1_IOM8_CH0_DATA ) >> 2) & 0x0001, (ReadCOMPOOL_IS( SCP_FA1_IOM5_CH0_DATA ) >> 2) & 0x0001,// L1U
			(ReadCOMPOOL_IS( SCP_FA4_IOM8_CH0_DATA ) >> 2) & 0x0001, (ReadCOMPOOL_IS( SCP_FA4_IOM5_CH0_DATA ) >> 2) & 0x0001,// L4D
			(ReadCOMPOOL_IS( SCP_FA3_IOM8_CH0_DATA ) >> 2) & 0x0001, (ReadCOMPOOL_IS( SCP_FA3_IOM5_CH0_DATA ) >> 2) & 0x0001,// L2D
			(ReadCOMPOOL_IS( SCP_FA2_IOM8_CH0_DATA ) >> 2) & 0x0001, (ReadCOMPOOL_IS( SCP_FA2_IOM5_CH0_DATA ) >> 2) & 0x0001,// L3D
			(ReadCOMPOOL_IS( SCP_FA1_IOM8_CH0_DATA ) >> 6) & 0x0001, (ReadCOMPOOL_IS( SCP_FA1_IOM5_CH0_DATA ) >> 6) & 0x0001,// L5D
			(ReadCOMPOOL_IS( SCP_FA1_IOM8_CH0_DATA ) >> 7) & 0x0001, (ReadCOMPOOL_IS( SCP_FA1_IOM5_CH0_DATA ) >> 7) & 0x0001// L5L
		);*/

		/*sprintf_s( oapiDebugString(), 255, "RRCS %d%d %d%d %d%d %d%d %d%d %d%d %d%d %d%d %d%d %d%d %d%d %d%d %d%d %d%d",
			(ReadCOMPOOL_IS( SCP_FA2_IOM8_CH0_DATA ) >> 3) & 0x0001, (ReadCOMPOOL_IS( SCP_FA2_IOM5_CH0_DATA ) >> 3) & 0x0001,// R3A
			(ReadCOMPOOL_IS( SCP_FA1_IOM8_CH0_DATA ) >> 3) & 0x0001, (ReadCOMPOOL_IS( SCP_FA1_IOM5_CH0_DATA ) >> 3) & 0x0001,// R1A
			(ReadCOMPOOL_IS( SCP_FA4_IOM8_CH0_DATA ) >> 3) & 0x0001, (ReadCOMPOOL_IS( SCP_FA4_IOM5_CH0_DATA ) >> 3) & 0x0001,// R4R
			(ReadCOMPOOL_IS( SCP_FA3_IOM8_CH0_DATA ) >> 3) & 0x0001, (ReadCOMPOOL_IS( SCP_FA3_IOM5_CH0_DATA ) >> 3) & 0x0001,// R2R
			(ReadCOMPOOL_IS( SCP_FA2_IOM8_CH0_DATA ) >> 4) & 0x0001, (ReadCOMPOOL_IS( SCP_FA2_IOM5_CH0_DATA ) >> 4) & 0x0001,// R3R
			(ReadCOMPOOL_IS( SCP_FA1_IOM8_CH0_DATA ) >> 4) & 0x0001, (ReadCOMPOOL_IS( SCP_FA1_IOM5_CH0_DATA ) >> 4) & 0x0001,// R1R
			(ReadCOMPOOL_IS( SCP_FA4_IOM8_CH0_DATA ) >> 4) & 0x0001, (ReadCOMPOOL_IS( SCP_FA4_IOM5_CH0_DATA ) >> 4) & 0x0001,// R4U
			(ReadCOMPOOL_IS( SCP_FA3_IOM8_CH0_DATA ) >> 4) & 0x0001, (ReadCOMPOOL_IS( SCP_FA3_IOM5_CH0_DATA ) >> 4) & 0x0001,// R2U
			(ReadCOMPOOL_IS( SCP_FA1_IOM8_CH0_DATA ) >> 5) & 0x0001, (ReadCOMPOOL_IS( SCP_FA1_IOM5_CH0_DATA ) >> 5) & 0x0001,// R1U
			(ReadCOMPOOL_IS( SCP_FA4_IOM8_CH0_DATA ) >> 5) & 0x0001, (ReadCOMPOOL_IS( SCP_FA4_IOM5_CH0_DATA ) >> 5) & 0x0001,// R4D
			(ReadCOMPOOL_IS( SCP_FA3_IOM8_CH0_DATA ) >> 5) & 0x0001, (ReadCOMPOOL_IS( SCP_FA3_IOM5_CH0_DATA ) >> 5) & 0x0001,// R2D
			(ReadCOMPOOL_IS( SCP_FA2_IOM8_CH0_DATA ) >> 5) & 0x0001, (ReadCOMPOOL_IS( SCP_FA2_IOM5_CH0_DATA ) >> 5) & 0x0001,// R3D
			(ReadCOMPOOL_IS( SCP_FA2_IOM8_CH0_DATA ) >> 7) & 0x0001, (ReadCOMPOOL_IS( SCP_FA2_IOM5_CH0_DATA ) >> 7) & 0x0001,// R5D
			(ReadCOMPOOL_IS( SCP_FA2_IOM8_CH0_DATA ) >> 6) & 0x0001, (ReadCOMPOOL_IS( SCP_FA2_IOM5_CH0_DATA ) >> 6) & 0x0001// R5R
		);*/
		////////////////////////////////////////////////////////////////////////////

		// calculate He dP/dT (psia/3sec) for BFS DISP 18
		if ((simt - He_T) >= 3)
		{
			double currentP;
			for (int i = 0; i < 3; i++)
			{
				currentP = dipHeSysPressureSensor[i * 3].GetVoltage() * 1000;
				He_dPdT[i] = (3 * (He_P[i] - currentP)) / (simt - He_T);

				He_P[i] = currentP;// save press
			}

			He_T = simt;// save time
		}

		// ENTRY TRAJ displays
		if (GetMajorMode() == 304)
		{
			// calculate positions
			double VE = ReadCOMPOOL_SD( SCP_VE );
			if (VE > ENTRYTRAJ12_X)
			{
				double TRANG = ReadCOMPOOL_SD( SCP_TRANG );
				double DRAG = ReadCOMPOOL_SD( SCP_DRAG );
				double DREFP = ReadCOMPOOL_SD( SCP_DREFP );
				double DRDD = ReadCOMPOOL_SD( SCP_DRDD );
				double RRANG = TRANG - (DRDD * (DRAG - DREFP));

				/*if (CurrentET != 1)
				{
					CurrentET = 1;
					// new display, delete trailers
					memset( ET_History_X + 1, 0, sizeof(int) * 5 );
					memset( ET_History_X_Drag + 1, 0, sizeof(int) * 5 );
					memset( ET_History_Y + 1, 0, sizeof(int) * 5 );
				}*/

				ET_History_X[0] = Round( ETX1C + (TRANG * (ETX1C1 + (TRANG * ETX1C2))) );
				ET_History_Y[0] = Round( ETY1C + (VE * ETY1C1) );
				ET_History_X_Drag[0] = (ReadCOMPOOL_IS( SCP_ISLECT ) == 1) ? 0 : Round( ETX1C + (RRANG * (ETX1C1 + (RRANG * ETX1C2))) );
			}
			else if (VE > ENTRYTRAJ23_X)
			{
				double TRANG = ReadCOMPOOL_SD( SCP_TRANG );
				double DRAG = ReadCOMPOOL_SD( SCP_DRAG );
				double DREFP = ReadCOMPOOL_SD( SCP_DREFP );
				double DRDD = ReadCOMPOOL_SD( SCP_DRDD );
				double RRANG = TRANG - (DRDD * (DRAG - DREFP));

				if (CurrentET != 2)
				{
					CurrentET = 2;
					// new display, delete trailers
					memset( ET_History_X + 1, 0, sizeof(int) * 5 );
					memset( ET_History_X_Drag + 1, 0, sizeof(int) * 5 );
					memset( ET_History_Y + 1, 0, sizeof(int) * 5 );
				}

				ET_History_X[0] = Round( ETX2C + (TRANG * (ETX2C1 + (TRANG * ETX2C2))) );
				ET_History_Y[0] = Round( ETY2C + (VE * ETY2C1) );
				ET_History_X_Drag[0] = Round( ETX2C + (RRANG * (ETX2C1 + (RRANG * ETX2C2))) );
			}
			else if (VE > ENTRYTRAJ34_X)
			{
				double TRANG = ReadCOMPOOL_SD( SCP_TRANG );
				double DRAG = ReadCOMPOOL_SD( SCP_DRAG );
				double DREFP = ReadCOMPOOL_SD( SCP_DREFP );
				double DRDD = ReadCOMPOOL_SD( SCP_DRDD );
				double RRANG = TRANG - (DRDD * (DRAG - DREFP));

				if (CurrentET != 3)
				{
					CurrentET = 3;
					// new display, delete trailers
					memset( ET_History_X + 1, 0, sizeof(int) * 5 );
					memset( ET_History_X_Drag + 1, 0, sizeof(int) * 5 );
					memset( ET_History_Y + 1, 0, sizeof(int) * 5 );
				}

				ET_History_X[0] = Round( ETX3C + (TRANG * (ETX3C1 + (TRANG * ETX3C2))) );
				ET_History_Y[0] = Round( ETY3C + (VE * ETY3C1) );
				ET_History_X_Drag[0] = Round( ETX3C + (RRANG * (ETX3C1 + (RRANG * ETX3C2))) );
			}
			else if (VE > ENTRYTRAJ45_X)
			{
				double TRANG = ReadCOMPOOL_SD( SCP_TRANG );
				double H = ReadCOMPOOL_SD( SCP_H );
				double DRAG = ReadCOMPOOL_SD( SCP_DRAG );
				double DREFP = ReadCOMPOOL_SD( SCP_DREFP );
				double DRDD = ReadCOMPOOL_SD( SCP_DRDD );
				double RRANG = TRANG - (DRDD * (DRAG - DREFP));

				if (CurrentET != 4)
				{
					CurrentET = 4;
					// new display, delete trailers
					memset( ET_History_X + 1, 0, sizeof(int) * 5 );
					memset( ET_History_X_Drag + 1, 0, sizeof(int) * 5 );
					memset( ET_History_Y + 1, 0, sizeof(int) * 5 );
				}

				ET_History_X[0] = Round( ETX4C + (TRANG * (ETX4C1 + (TRANG * ETX4C2))) );
				ET_History_Y[0] = Round( ETY4C + (VE * H * ETY4C1) );
				ET_History_X_Drag[0] = Round( ETX4C + (RRANG * (ETX4C1 + (RRANG * ETX4C2))) );
			}
			else
			{
				double TRANG = ReadCOMPOOL_SD( SCP_TRANG );
				double H = ReadCOMPOOL_SD( SCP_H );
				double DRAG = ReadCOMPOOL_SD( SCP_DRAG );
				double DREFP = ReadCOMPOOL_SD( SCP_DREFP );
				double DRDD = ReadCOMPOOL_SD( SCP_DRDD );
				double RRANG = TRANG - (DRDD * (DRAG - DREFP));

				if (CurrentET != 5)
				{
					CurrentET = 5;
					// new display, delete trailers
					memset( ET_History_X + 1, 0, sizeof(int) * 5 );
					memset( ET_History_X_Drag + 1, 0, sizeof(int) * 5 );
					memset( ET_History_Y + 1, 0, sizeof(int) * 5 );
				}

				ET_History_X[0] = Round( ETX5C + (TRANG * (ETX5C1 + (TRANG * ETX5C2))) );
				ET_History_Y[0] = Round( ETY5C + (VE * H * ETY5C1) );
				ET_History_X_Drag[0] = Round( ETX5C + (RRANG * (ETX5C1 + (RRANG * ETX5C2))) );
			}

			// save data for ENTRY TRAJ displays
			if (simt >= ET_History_updatetime)
			{
				// set new time
				if (VE > ENTRYTRAJ23_X) ET_History_updatetime = simt + 28.8;// ET1, ET2
				else ET_History_updatetime = simt + 15.36;// ET3, ET4, ET5

				// shift history back
				memmove( ET_History_X + 1, ET_History_X, sizeof(int) * 5 );
				memmove( ET_History_X_Drag + 1, ET_History_X_Drag, sizeof(int) * 5 );
				memmove( ET_History_Y + 1, ET_History_Y, sizeof(int) * 5 );
			}

			// ROLL REF status
			double ROLLREF = fabs( ReadCOMPOOL_SD( SCP_ROLLREF ) );
			double ROLLREFLIM = 0.0;
			if (VE >= 9500.0) ROLLREFLIM = 37.0;
			else if (VE >= 4000.0) ROLLREFLIM = 20.0;
			else  ROLLREFLIM = -5.0;

			if (ROLLREF < ROLLREFLIM) ROLLREF_status = true;
			else ROLLREF_status = false;
		}
		return;
	}

	bool GeneralDisplays::OnMajorModeChange( unsigned int newMajorMode )
	{
		// always running
		return true;
	}

	bool GeneralDisplays::ItemInput( int spec, int item, const char* Data, bool &IllegalEntry )
	{
		switch (spec)
		{
			case 0:
				return ItemInput_GPCMEMORY( item, Data, IllegalEntry );
			case 23:
				return ItemInput_SPEC23( item, Data, IllegalEntry );
			case 50:
				return ItemInput_SPEC50( item, Data, IllegalEntry );
			case 51:
				return ItemInput_SPEC51( item, Data, IllegalEntry );
			/*case 53:
				return true;
			case 55:
				return true;
			case 99:
				return true;*/
			case 112:
				ItemInput_SPEC112( item, Data, IllegalEntry );
				return true;
			case 113:
				ItemInput_SPEC113( item, Data, IllegalEntry );
				return true;
			case dps::MODE_UNDEFINED:
				switch (GetMajorMode())
				{
					case 304:
						return ItemInput_ENTRYTRAJ( item, Data, IllegalEntry );
				}
		}
		return false;
	}

	bool GeneralDisplays::ItemInput_GPCMEMORY( int item, const char* Data, bool &IllegalEntry )
	{
		switch (item)
		{
			case 26:
				{
					int nNew;
					if (GetIntegerUnsigned( Data, nNew ))
					{
						if (((nNew >= 100) && (nNew <= 110)) || ((nNew >= 200) && (nNew <= 210)))
						{
							engunit_hex = nNew;
							for (int i = 0; i < 6; i++)
							{
								addidvalid[i] = false;
							}
						}
						else IllegalEntry = true;
					}
					else IllegalEntry = true;
				}
				return true;
			case 27:
				engunit_hex = 0;
				for (int i = 0; i < 6; i++)
				{
					addidvalid[i] = false;
				}
				return true;
			case 28:
			case 30:
			case 32:
			case 34:
			case 36:
			case 38:
				{
					unsigned int nNew;
					if (GetIntegerHex( Data, nNew ))
					{
						if (nNew < (SIMPLECOMPOOL_SIZE - ((engunit_hex >= 200) ? 1 : 0)))// limit to "last - 1" for 32b
						{
							addid[(item - 28) / 2] = nNew;
							addidvalid[(item - 28) / 2] = true;
						}
						else IllegalEntry = true;
					}
					else IllegalEntry = true;
				}
				return true;
		}
		return false;
	}

	bool GeneralDisplays::ItemInput_ENTRYTRAJ( int item, const char* Data, bool &IllegalEntry )
	{
		switch (item)
		{
			/*case 1:
				return true;*/
			case 2:
				WriteCOMPOOL_SD( SCP_DLRDOT, 0.0 );
				return true;
			/*case 3:
				return true;*/
		}
		return false;
	}

	bool GeneralDisplays::ItemInput_SPEC23( int item, const char* Data, bool &IllegalEntry )
	{
		switch (item)
		{
			case 1:
			case 2:
			case 3:
				SPEC23_RCSsel = item;
				return true;
			////////////////////////////////////////////////////////////////////////////
			case 4:// RCS off
				WriteCOMPOOL_IS( SCP_FF1_IOM5_CH0_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FF1_IOM13_CH0_DATA, 0x0000 );

				WriteCOMPOOL_IS( SCP_FF2_IOM5_CH0_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FF2_IOM13_CH0_DATA, 0x0000 );

				WriteCOMPOOL_IS( SCP_FF3_IOM5_CH0_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FF3_IOM13_CH0_DATA, 0x0000 );

				WriteCOMPOOL_IS( SCP_FF4_IOM5_CH0_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FF4_IOM13_CH0_DATA, 0x0000 );


				WriteCOMPOOL_IS( SCP_FA1_IOM2_CH0_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA1_IOM10_CH0_DATA, 0x0000 );

				WriteCOMPOOL_IS( SCP_FA2_IOM2_CH0_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA2_IOM10_CH0_DATA, 0x0000 );

				WriteCOMPOOL_IS( SCP_FA3_IOM2_CH0_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA3_IOM10_CH0_DATA, 0x0000 );

				WriteCOMPOOL_IS( SCP_FA4_IOM2_CH0_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA4_IOM10_CH0_DATA, 0x0000 );
				return true;
			case 5:// RCS on
				WriteCOMPOOL_IS( SCP_FF1_IOM5_CH0_DATA, 0x000F );
				WriteCOMPOOL_IS( SCP_FF1_IOM13_CH0_DATA, 0x000F );

				WriteCOMPOOL_IS( SCP_FF2_IOM5_CH0_DATA, 0x000F );
				WriteCOMPOOL_IS( SCP_FF2_IOM13_CH0_DATA, 0x000F );

				WriteCOMPOOL_IS( SCP_FF3_IOM5_CH0_DATA, 0x000F );
				WriteCOMPOOL_IS( SCP_FF3_IOM13_CH0_DATA, 0x000F );

				WriteCOMPOOL_IS( SCP_FF4_IOM5_CH0_DATA, 0x000F );
				WriteCOMPOOL_IS( SCP_FF4_IOM13_CH0_DATA, 0x000F );


				WriteCOMPOOL_IS( SCP_FA1_IOM2_CH0_DATA, 0x00FF );
				WriteCOMPOOL_IS( SCP_FA1_IOM10_CH0_DATA, 0x00FF );

				WriteCOMPOOL_IS( SCP_FA2_IOM2_CH0_DATA, 0x00FF );
				WriteCOMPOOL_IS( SCP_FA2_IOM10_CH0_DATA, 0x00FF );

				WriteCOMPOOL_IS( SCP_FA3_IOM2_CH0_DATA, 0x003F );
				WriteCOMPOOL_IS( SCP_FA3_IOM10_CH0_DATA, 0x003F );

				WriteCOMPOOL_IS( SCP_FA4_IOM2_CH0_DATA, 0x003F );
				WriteCOMPOOL_IS( SCP_FA4_IOM10_CH0_DATA, 0x003F );
				return true;
			case 6:// RCS on (-Z trans)
				WriteCOMPOOL_IS( SCP_FF1_IOM5_CH0_DATA, 0x0008 );
				WriteCOMPOOL_IS( SCP_FF1_IOM13_CH0_DATA, 0x0008 );

				WriteCOMPOOL_IS( SCP_FF2_IOM5_CH0_DATA, 0x0008 );
				WriteCOMPOOL_IS( SCP_FF2_IOM13_CH0_DATA, 0x0008 );

				WriteCOMPOOL_IS( SCP_FF3_IOM5_CH0_DATA, 0x0002 );
				WriteCOMPOOL_IS( SCP_FF3_IOM13_CH0_DATA, 0x0002 );

				WriteCOMPOOL_IS( SCP_FF4_IOM5_CH0_DATA, 0x0008 );
				WriteCOMPOOL_IS( SCP_FF4_IOM13_CH0_DATA, 0x0008 );


				WriteCOMPOOL_IS( SCP_FA1_IOM2_CH0_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA1_IOM10_CH0_DATA, 0x0000 );

				WriteCOMPOOL_IS( SCP_FA2_IOM2_CH0_DATA, 0x0024 );
				WriteCOMPOOL_IS( SCP_FA2_IOM10_CH0_DATA, 0x0024 );

				WriteCOMPOOL_IS( SCP_FA3_IOM2_CH0_DATA, 0x0024 );
				WriteCOMPOOL_IS( SCP_FA3_IOM10_CH0_DATA, 0x0024 );

				WriteCOMPOOL_IS( SCP_FA4_IOM2_CH0_DATA, 0x0024 );
				WriteCOMPOOL_IS( SCP_FA4_IOM10_CH0_DATA, 0x0024 );
				return true;
			case 7:// RCS on (low +Z trans)
				WriteCOMPOOL_IS( SCP_FF1_IOM5_CH0_DATA, 0x0001 );
				WriteCOMPOOL_IS( SCP_FF1_IOM13_CH0_DATA, 0x0001 );

				WriteCOMPOOL_IS( SCP_FF2_IOM5_CH0_DATA, 0x0001 );
				WriteCOMPOOL_IS( SCP_FF2_IOM13_CH0_DATA, 0x0001 );


				WriteCOMPOOL_IS( SCP_FA1_IOM2_CH0_DATA, 0x0009 );
				WriteCOMPOOL_IS( SCP_FA1_IOM10_CH0_DATA, 0x0009 );
				return true;
			case 20:// FRCS vlv GPC open
				WriteCOMPOOL_IS( SCP_FF1_IOM2_CH0_DATA, 0x1028 );
				WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, 0x2400 );

				WriteCOMPOOL_IS( SCP_FF2_IOM2_CH0_DATA, 0x0008 );
				WriteCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA, 0x1000 );

				WriteCOMPOOL_IS( SCP_FF3_IOM2_CH0_DATA, 0x0028 );
				WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, 0x3400 );

				WriteCOMPOOL_IS( SCP_FF4_IOM2_CH0_DATA, 0x0008 );
				WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, 0x0000 );
				return true;
			case 21:// FRCS vlv GPC close
				WriteCOMPOOL_IS( SCP_FF1_IOM2_CH0_DATA, 0x00D0 );
				WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, 0xD800 );

				WriteCOMPOOL_IS( SCP_FF2_IOM2_CH0_DATA, 0x1010 );
				WriteCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA, 0x8000 );

				WriteCOMPOOL_IS( SCP_FF3_IOM2_CH0_DATA, 0x10D0 );
				WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, 0xC800 );

				WriteCOMPOOL_IS( SCP_FF4_IOM2_CH0_DATA, 0x0010 );
				WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, 0x8000 );
				return true;
			case 22:// FRCS vlv GPC off
				WriteCOMPOOL_IS( SCP_FF1_IOM2_CH0_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, 0x0000 );

				WriteCOMPOOL_IS( SCP_FF2_IOM2_CH0_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA, 0x0000 );

				WriteCOMPOOL_IS( SCP_FF3_IOM2_CH0_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, 0x0000 );

				WriteCOMPOOL_IS( SCP_FF4_IOM2_CH0_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, 0x0000 );
				return true;
			case 23:// LRCS vlv GPC open
				WriteCOMPOOL_IS( SCP_FA1_IOM7_CH0_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA1_IOM7_CH2_DATA, 0x0A6A );
				WriteCOMPOOL_IS( SCP_FA1_IOM15_CH2_DATA, 0x0000 );

				WriteCOMPOOL_IS( SCP_FA2_IOM7_CH0_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA2_IOM7_CH2_DATA, 0x026A );
				WriteCOMPOOL_IS( SCP_FA2_IOM15_CH2_DATA, 0x0000 );

				WriteCOMPOOL_IS( SCP_FA3_IOM7_CH0_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA3_IOM7_CH2_DATA, 0x086A );
				WriteCOMPOOL_IS( SCP_FA3_IOM15_CH2_DATA, 0x0400 );

				WriteCOMPOOL_IS( SCP_FA4_IOM7_CH0_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA4_IOM7_CH2_DATA, 0x026A );
				WriteCOMPOOL_IS( SCP_FA4_IOM15_CH2_DATA, 0x0000 );
				return true;
			case 24:// LRCS vlv GPC close
				WriteCOMPOOL_IS( SCP_FA1_IOM7_CH0_DATA, 0x0001 );
				WriteCOMPOOL_IS( SCP_FA1_IOM7_CH2_DATA, 0x0415 );
				WriteCOMPOOL_IS( SCP_FA1_IOM15_CH2_DATA, 0x0100 );

				WriteCOMPOOL_IS( SCP_FA2_IOM7_CH0_DATA, 0x0001 );
				WriteCOMPOOL_IS( SCP_FA2_IOM7_CH2_DATA, 0x0C15 );
				WriteCOMPOOL_IS( SCP_FA2_IOM15_CH2_DATA, 0x0100 );

				WriteCOMPOOL_IS( SCP_FA3_IOM7_CH0_DATA, 0x0001 );
				WriteCOMPOOL_IS( SCP_FA3_IOM7_CH2_DATA, 0x0015 );
				WriteCOMPOOL_IS( SCP_FA3_IOM15_CH2_DATA, 0x0B00 );

				WriteCOMPOOL_IS( SCP_FA4_IOM7_CH0_DATA, 0x0001 );
				WriteCOMPOOL_IS( SCP_FA4_IOM7_CH2_DATA, 0x0415 );
				WriteCOMPOOL_IS( SCP_FA4_IOM15_CH2_DATA, 0x0100 );
				return true;
			case 25:// LRCS vlv GPC off
				WriteCOMPOOL_IS( SCP_FA1_IOM7_CH0_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA1_IOM7_CH2_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA1_IOM15_CH2_DATA, 0x0000 );

				WriteCOMPOOL_IS( SCP_FA2_IOM7_CH0_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA2_IOM7_CH2_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA2_IOM15_CH2_DATA, 0x0000 );

				WriteCOMPOOL_IS( SCP_FA3_IOM7_CH0_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA3_IOM7_CH2_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA3_IOM15_CH2_DATA, 0x0000 );

				WriteCOMPOOL_IS( SCP_FA4_IOM7_CH0_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA4_IOM7_CH2_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA4_IOM15_CH2_DATA, 0x0000 );
				return true;
			case 26:// RRCS vlv GPC open
				WriteCOMPOOL_IS( SCP_FA1_IOM7_CH2_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA1_IOM15_CH2_DATA, 0x026A );

				WriteCOMPOOL_IS( SCP_FA2_IOM7_CH2_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA2_IOM15_CH2_DATA, 0x0A6A );

				WriteCOMPOOL_IS( SCP_FA3_IOM7_CH2_DATA, 0x0200 );
				WriteCOMPOOL_IS( SCP_FA3_IOM15_CH0_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA3_IOM15_CH2_DATA, 0x006A );

				WriteCOMPOOL_IS( SCP_FA4_IOM7_CH2_DATA, 0x0800 );
				WriteCOMPOOL_IS( SCP_FA4_IOM15_CH0_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA4_IOM15_CH2_DATA, 0x046A );
				return true;
			case 27:// RRCS vlv GPC close
				WriteCOMPOOL_IS( SCP_FA1_IOM7_CH2_DATA, 0x0100 );
				WriteCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA, 0x0002 );
				WriteCOMPOOL_IS( SCP_FA1_IOM15_CH2_DATA, 0x0C15 );

				WriteCOMPOOL_IS( SCP_FA2_IOM7_CH2_DATA, 0x0100 );
				WriteCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA, 0x0002 );
				WriteCOMPOOL_IS( SCP_FA2_IOM15_CH2_DATA, 0x0415 );

				WriteCOMPOOL_IS( SCP_FA3_IOM7_CH2_DATA, 0x0500 );
				WriteCOMPOOL_IS( SCP_FA3_IOM15_CH0_DATA, 0x0002 );
				WriteCOMPOOL_IS( SCP_FA3_IOM15_CH2_DATA, 0x0015 );

				WriteCOMPOOL_IS( SCP_FA4_IOM7_CH2_DATA, 0x0100 );
				WriteCOMPOOL_IS( SCP_FA4_IOM15_CH0_DATA, 0x0002 );
				WriteCOMPOOL_IS( SCP_FA4_IOM15_CH2_DATA, 0x0A15 );
				return true;
			case 28:// RRCS vlv GPC off
				WriteCOMPOOL_IS( SCP_FA1_IOM7_CH2_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA1_IOM15_CH2_DATA, 0x0000 );

				WriteCOMPOOL_IS( SCP_FA2_IOM7_CH2_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA2_IOM15_CH2_DATA, 0x0000 );

				WriteCOMPOOL_IS( SCP_FA3_IOM7_CH2_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA3_IOM15_CH0_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA3_IOM15_CH2_DATA, 0x0000 );

				WriteCOMPOOL_IS( SCP_FA4_IOM7_CH2_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA4_IOM15_CH0_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA4_IOM15_CH2_DATA, 0x0000 );
				return true;
			case 30:// LOMS vlv GPC open
				WriteCOMPOOL_IS( SCP_FA1_IOM7_CH1_DATA, 0x08AC );
				WriteCOMPOOL_IS( SCP_FA1_IOM12_CH1_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA1_IOM15_CH1_DATA, 0x0826 );

				WriteCOMPOOL_IS( SCP_FA2_IOM7_CH1_DATA, 0x0824 );
				WriteCOMPOOL_IS( SCP_FA2_IOM12_CH1_DATA, 0x0010 );
				WriteCOMPOOL_IS( SCP_FA2_IOM15_CH1_DATA, 0x08A6 );

				WriteCOMPOOL_IS( SCP_FA3_IOM15_CH1_DATA, 0x0002 );

				WriteCOMPOOL_IS( SCP_FA4_IOM15_CH1_DATA, 0x0002 );
				return true;
			case 31:// LOMS vlv GPC close
				WriteCOMPOOL_IS( SCP_FA1_IOM7_CH1_DATA, 0x1150 );
				WriteCOMPOOL_IS( SCP_FA1_IOM12_CH1_DATA, 0x0010 );
				WriteCOMPOOL_IS( SCP_FA1_IOM15_CH1_DATA, 0x1040 );

				WriteCOMPOOL_IS( SCP_FA2_IOM7_CH1_DATA, 0x1040 );
				WriteCOMPOOL_IS( SCP_FA2_IOM12_CH1_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA2_IOM15_CH1_DATA, 0x1150 );

				WriteCOMPOOL_IS( SCP_FA3_IOM15_CH1_DATA, 0x0000 );

				WriteCOMPOOL_IS( SCP_FA4_IOM15_CH1_DATA, 0x0000 );
				return true;
			case 32:// LOMS vlv GPC off
				WriteCOMPOOL_IS( SCP_FA1_IOM7_CH1_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA1_IOM12_CH1_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA1_IOM15_CH1_DATA, 0x0000 );

				WriteCOMPOOL_IS( SCP_FA2_IOM7_CH1_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA2_IOM12_CH1_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA2_IOM15_CH1_DATA, 0x0000 );

				WriteCOMPOOL_IS( SCP_FA3_IOM15_CH1_DATA, 0x0000 );

				WriteCOMPOOL_IS( SCP_FA4_IOM15_CH1_DATA, 0x0000 );
				return true;
			case 33:// ROMS vlv GPC open
				WriteCOMPOOL_IS( SCP_FA1_IOM7_CH1_DATA, 0x2202 );
				WriteCOMPOOL_IS( SCP_FA1_IOM15_CH1_DATA, 0x2000 );

				WriteCOMPOOL_IS( SCP_FA2_IOM7_CH1_DATA, 0x2002 );
				WriteCOMPOOL_IS( SCP_FA2_IOM15_CH1_DATA, 0x2200 );

				WriteCOMPOOL_IS( SCP_FA3_IOM7_CH1_DATA, 0x0026 );
				WriteCOMPOOL_IS( SCP_FA3_IOM12_CH1_DATA, 0x0010 );
				WriteCOMPOOL_IS( SCP_FA3_IOM15_CH1_DATA, 0x002C );

				WriteCOMPOOL_IS( SCP_FA4_IOM7_CH1_DATA, 0x002E );
				WriteCOMPOOL_IS( SCP_FA4_IOM12_CH1_DATA, 0x0010 );
				WriteCOMPOOL_IS( SCP_FA4_IOM15_CH1_DATA, 0x0024 );
				return true;
			case 34:// ROMS vlv GPC close
				WriteCOMPOOL_IS( SCP_FA1_IOM7_CH1_DATA, 0x4400 );
				WriteCOMPOOL_IS( SCP_FA1_IOM15_CH1_DATA, 0x4000 );

				WriteCOMPOOL_IS( SCP_FA2_IOM7_CH1_DATA, 0x4000 );
				WriteCOMPOOL_IS( SCP_FA2_IOM15_CH1_DATA, 0x4400 );

				WriteCOMPOOL_IS( SCP_FA3_IOM7_CH1_DATA, 0x0040 );
				WriteCOMPOOL_IS( SCP_FA3_IOM12_CH1_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA3_IOM15_CH1_DATA, 0x0050 );

				WriteCOMPOOL_IS( SCP_FA4_IOM7_CH1_DATA, 0x0050 );
				WriteCOMPOOL_IS( SCP_FA4_IOM12_CH1_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA4_IOM15_CH1_DATA, 0x0040 );
				return true;
			case 35:// ROMS vlv GPC off
				WriteCOMPOOL_IS( SCP_FA1_IOM7_CH1_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA1_IOM15_CH1_DATA, 0x0000 );

				WriteCOMPOOL_IS( SCP_FA2_IOM7_CH1_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA2_IOM15_CH1_DATA, 0x0000 );

				WriteCOMPOOL_IS( SCP_FA3_IOM7_CH1_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA3_IOM12_CH1_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA3_IOM15_CH1_DATA, 0x0000 );

				WriteCOMPOOL_IS( SCP_FA4_IOM7_CH1_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA4_IOM12_CH1_DATA, 0x0000 );
				WriteCOMPOOL_IS( SCP_FA4_IOM15_CH1_DATA, 0x0000 );
				return true;
			////////////////////////////////////////////////////////////////////////////
			case 46:
			case 47:
				IllegalEntry = true;
				return true;
		}
		return false;
	}

	bool GeneralDisplays::ItemInput_SPEC50( int item, const char* Data, bool &IllegalEntry )
	{
		if (item == 3)
		{
			if (strlen( Data ) == 0)
			{
				if (ReadCOMPOOL_IS( SCP_RWID ) == 2)// check so OVHD reset only occurs when actually changing RWID
				{
					WriteCOMPOOL_IS( SCP_RWID, 1 );
					WriteCOMPOOL_IS( SCP_OVHD, 1 );// reset to overhead
				}
			}
			else IllegalEntry = true;
			return true;
		}
		else if (item == 4)
		{
			if (strlen( Data ) == 0)
			{
				if (ReadCOMPOOL_IS( SCP_RWID ) == 1)// check so OVHD reset only occurs when actually changing RWID
				{
					WriteCOMPOOL_IS( SCP_RWID, 2 );
					WriteCOMPOOL_IS( SCP_OVHD, 1 );// reset to overhead
				}
			}
			else IllegalEntry = true;
			return true;
		}
		else if (item == 6)
		{
			if (strlen( Data ) == 0)
			{
				if ((ReadCOMPOOL_IS( SCP_IPHASE ) <= 2) && (ReadCOMPOOL_IS( SCP_TG_END ) == 0))
				{
					WriteCOMPOOL_IS( SCP_OVHD, 0 );
					WriteCOMPOOL_IS( SCP_RWID0, 0 );// to force PSHA to reset in EGRT or TAEM Guidance so PSHA ends up < 180.0º
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
			return true;
		}
		else if (item == 7)
		{
			if (strlen( Data ) == 0)
			{
				if ((ReadCOMPOOL_IS( SCP_IPHASE ) <= 2) && (ReadCOMPOOL_IS( SCP_TG_END ) == 0))
				{
					if (ReadCOMPOOL_IS( SCP_MEP ) == 1) WriteCOMPOOL_IS( SCP_MEP, 0 );
					else WriteCOMPOOL_IS( SCP_MEP, 1 );
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
			return true;
		}
		else if (item == 8)
		{
			if (strlen( Data ) == 0)
			{
				if (ReadCOMPOOL_IS( SCP_TG_END ) == 0)// valid until A/L
				{
					if (ReadCOMPOOL_IS( SCP_IGI ) == 1) WriteCOMPOOL_IS( SCP_IGI, 2 );
					else WriteCOMPOOL_IS( SCP_IGI, 1 );
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
			return true;
		}
		else if (item == 39)
		{
			if (strlen( Data ) == 0)
			{
				if (ReadCOMPOOL_IS( SCP_TG_END ) == 0)// valid until A/L
				{
					unsigned short sbsel = ReadCOMPOOL_IS( SCP_SB_SEL );
					sbsel++;
					if (sbsel > 3) sbsel = 1;
					WriteCOMPOOL_IS( SCP_SB_SEL, sbsel );
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
			return true;
		}
		else if (item == 41)
		{
			int nNew;
			if (GetIntegerUnsigned( Data, nNew ))
			{
				if ((nNew > 0) && (nNew <= 45))
				{
					WriteCOMPOOL_IS( SCP_LSID, nNew );
					WriteCOMPOOL_IS( SCP_RWID, 1 );// reset to PRI
					WriteCOMPOOL_IS( SCP_OVHD, 1 );// reset to overhead
					WriteCOMPOOL_IS( SCP_IGI, 1 );// reset to nom aim
					WriteCOMPOOL_IS( SCP_MEP, 0 );// reset to NEP
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
			return true;
		}
		return false;
	}

	bool GeneralDisplays::ItemInput_SPEC51( int item, const char* Data, bool &IllegalEntry )
	{
		switch (item)
		{
			case 4:
				switch (GetMajorMode())
				{
					case 102:
					case 103:
					case 601:
						WriteCOMPOOL_IS( SCP_KMAX_SEL, 1 );
						break;
					default:
						IllegalEntry = true;
						break;
				}
				return true;
			case 42:
				switch (GetMajorMode())
				{
					case 304:
					case 305:
					case 602:
					case 603:
						WriteCOMPOOL_IS( SCP_ENTRY_SW_OVERRIDE, (ReadCOMPOOL_IS( SCP_ENTRY_SW_OVERRIDE ) == 0) ? 1 : 0 );
						break;
					default:
						IllegalEntry = true;
						break;
				}
				return true;
			case 43:
				switch (GetMajorMode())
				{
					case 301:
					case 302:
					case 303:
					case 304:
					case 305:
					case 602:
					case 603:
						if (ReadCOMPOOL_IS( SCP_VENT_DOOR_SEQ_INIT ) == 0)
						{
							WriteCOMPOOL_IS( SCP_VENT_DOOR_SEQ_INIT, 1 );
							WriteCOMPOOL_IS( SCP_ALL_VENT_CLOSE_CMD, 0 );
						}
						else IllegalEntry = true;
						break;
					default:
						IllegalEntry = true;
						break;
				}
				return true;
			case 44:
				switch (GetMajorMode())
				{
					case 305:
					case 603:
						if (ReadCOMPOOL_IS( SCP_ROLLOUT ) == 0)
						{
							IllegalEntry = true;
							break;
						}
					case 301:
					case 302:
					case 303:
					case 304:
					case 602:
						if (ReadCOMPOOL_IS( SCP_VENT_DOOR_SEQ_INIT ) == 0)
						{
							WriteCOMPOOL_IS( SCP_VENT_DOOR_SEQ_INIT, 1 );
							WriteCOMPOOL_IS( SCP_ALL_VENT_CLOSE_CMD, 1 );
						}
						else IllegalEntry = true;
						break;
					default:
						IllegalEntry = true;
						break;
				}
				return true;
			case 45:
				if (GetMajorMode() / 100 != 3) IllegalEntry = true;
				else
				{
					if (ReadCOMPOOL_IS( SCP_WRAP ) == 0) WriteCOMPOOL_IS( SCP_WRAP, 1 );
					else WriteCOMPOOL_IS( SCP_WRAP, 0 );
				}
				return true;
			case 50:
				switch (GetMajorMode())
				{
					case 102:
					case 103:
					case 601:
						WriteCOMPOOL_IS( SCP_KMAX_SEL, 2 );
						break;
					default:
						IllegalEntry = true;
						break;
				}
				return true;
			case 51:
				switch (GetMajorMode())
				{
					case 102:
					case 103:
					case 601:
						WriteCOMPOOL_IS( SCP_KMAX_SEL, 0 );
						break;
					default:
						IllegalEntry = true;
						break;
				}
				return true;
		}
		return false;
	}

	void GeneralDisplays::ItemInput_SPEC112( int item, const char* Data, bool &IllegalEntry )
	{
		// TODO
		return;
	}

	void GeneralDisplays::ItemInput_SPEC113( int item, const char* Data, bool &IllegalEntry )
	{
		// TODO
		return;
	}

	bool GeneralDisplays::OnPaint( int spec, vc::MDU* pMDU ) const
	{
		// HACK determine which display to use based on the position of the BFC CRT switches (BFS display only available in CRTx)
		bool outputBFSdisplay = false;

		if (pMDU->GetIdentifier() == "CRT1")
		{
			if (dipBFCCRTDisplay.IsSet() && dipBFCCRTSelect[1].IsSet()) outputBFSdisplay = true;
		}
		else if (pMDU->GetIdentifier() == "CRT2")
		{
			if (dipBFCCRTDisplay.IsSet() && !dipBFCCRTSelect[0].IsSet() && !dipBFCCRTSelect[1].IsSet()) outputBFSdisplay = true;
		}
		else if (pMDU->GetIdentifier() == "CRT3")
		{
			if (dipBFCCRTDisplay.IsSet() && dipBFCCRTSelect[0].IsSet()) outputBFSdisplay = true;
		}

		if (outputBFSdisplay == false)
		{
			// PASS
			switch (GetMajorMode() / 100)
			{
				case 0:
					switch (spec)
					{
						case 0:
							OnPaint_GPCMEMORY_PASS( pMDU );// GPC MEMORY
							return true;
						case 99:
							OnPaint_DISP99_PASS( pMDU );// FAULT
							return true;
						case dps::MODE_UNDEFINED:
							OnPaint_GPCMEMORY_PASS( pMDU );// GPC MEMORY
							return true;
						default:
							return false;
					}
				case 1:
					switch (spec)
					{
						case 0:
							OnPaint_GPCMEMORY_PASS( pMDU );// GPC MEMORY
							return true;
						case 18:
							OnPaint_DISP18_PASS( pMDU );// GNC SYS SUMM 1
							return true;
						case 23:
							OnPaint_SPEC23_PASS( pMDU );// RCS
							return true;
						case 50:
							OnPaint_SPEC50_PASS( pMDU );// HORIZ SIT
							return true;
						case 51:
							OnPaint_SPEC51_PASS( pMDU );// OVERRIDE
							return true;
						case 53:
							OnPaint_SPEC53_PASS( pMDU );// CONTROLS
							return true;
						case 55:
							OnPaint_SPEC55_PASS( pMDU );// GPS STATUS
							return true;
						case 99:
							OnPaint_DISP99_PASS( pMDU );// FAULT
							return true;
						case dps::MODE_UNDEFINED:
							switch (GetMajorMode())// only PASS XXXXXX TRAJ displays for now
							{
								case 101:
									OnPaint_LAUNCHTRAJ1_PASS( pMDU );// OI-32 PASS LAUNCH TRAJ 1
									return true;
								case 102:
									OnPaint_ASCENTTRAJ1_PASS( pMDU );// OI-32 PASS ASCENT TRAJ 1
									return true;
								case 103:
									OnPaint_ASCENTTRAJ2_PASS( pMDU );// OI-32 PASS ASCENT TRAJ 2
									return true;
								default:
									return false;
							}
						default:
							return false;
					}
				case 2:
					switch (spec)
					{
						case 0:
							OnPaint_GPCMEMORY_PASS( pMDU );// GPC MEMORY
							return true;
						case 18:
							OnPaint_DISP18_PASS( pMDU );// GNC SYS SUMM 1
							return true;
						case 19:
							OnPaint_DISP19_PASS( pMDU );// GNC SYS SUMM 2
							return true;
						case 23:
							OnPaint_SPEC23_PASS( pMDU );// RCS
							return true;
						case 25:
							OnPaint_SPEC25_PASS( pMDU );// RM ORBIT
							return true;
						case 55:
							OnPaint_SPEC55_PASS( pMDU );// GPS STATUS
							return true;
						case 99:
							OnPaint_DISP99_PASS( pMDU );// FAULT
							return true;
						default:
							return false;
					}
				case 3:
					switch (spec)
					{
						case 0:
							OnPaint_GPCMEMORY_PASS( pMDU );// GPC MEMORY
							return true;
						case 18:
							OnPaint_DISP18_PASS( pMDU );// GNC SYS SUMM 1
							return true;
						case 23:
							OnPaint_SPEC23_PASS( pMDU );// RCS
							return true;
						case 50:
							OnPaint_SPEC50_PASS( pMDU );// HORIZ SIT
							return true;
						case 51:
							OnPaint_SPEC51_PASS( pMDU );// OVERRIDE
							return true;
						case 53:
							OnPaint_SPEC53_PASS( pMDU );// CONTROLS
							return true;
						case 55:
							OnPaint_SPEC55_PASS( pMDU );// GPS STATUS
							return true;
						case 99:
							OnPaint_DISP99_PASS( pMDU );// FAULT
							return true;
						case dps::MODE_UNDEFINED:
							switch (GetMajorMode())
							{
								case 304:
									if (CurrentET == 1)
										OnPaint_ENTRYTRAJ1_PASS( pMDU );// ENTRY TRAJ 1 (24.5kfps-17kfps / 3800nm-800nm)
									else if (CurrentET == 2)
										OnPaint_ENTRYTRAJ2_PASS( pMDU );// ENTRY TRAJ 2 (17kfps-14kfps / 1300nm-425nm)
									else if (CurrentET == 3)
										OnPaint_ENTRYTRAJ3_PASS( pMDU );// ENTRY TRAJ 3 (14kfps-10.5kfps / 800nm-315nm)
									else if (CurrentET == 4)
										OnPaint_ENTRYTRAJ4_PASS( pMDU );// ENTRY TRAJ 4 (1.8Mft-750kft(10kfps-6.5kfps) / 480nm-145nm)
									else// if (CurrentET == 5)
										OnPaint_ENTRYTRAJ5_PASS( pMDU );// ENTRY TRAJ 5 (750kft-200kft(6.5kfps-2.5kfps) / 220nm-55nm)
									return true;
								case 305:
									if (ReadCOMPOOL_SD( SCP_H ) > 30000.0)
										OnPaint_VERTSIT1_PASS( pMDU );// VERT SIT 1 (100kft-30kft / 70nm-10nm)
									else
										OnPaint_VERTSIT2_PASS( pMDU );// VERT SIT 2 (30kft-8kft / 25nm-5nm)
									return true;
								default:
									return false;
							}
						default:
							return false;
					}
				case 6:
					switch (spec)
					{
						case 0:
							OnPaint_GPCMEMORY_PASS( pMDU );// GPC MEMORY
							return true;
						case 18:
							OnPaint_DISP18_PASS( pMDU );// GNC SYS SUMM 1
							return true;
						case 23:
							OnPaint_SPEC23_PASS( pMDU );// RCS
							return true;
						case 50:
							OnPaint_SPEC50_PASS( pMDU );// HORIZ SIT
							return true;
						case 51:
							OnPaint_SPEC51_PASS( pMDU );// OVERRIDE
							return true;
						case 53:
							OnPaint_SPEC53_PASS( pMDU );// CONTROLS
							return true;
						case 55:
							OnPaint_SPEC55_PASS( pMDU );// GPS STATUS
							return true;
						case 99:
							OnPaint_DISP99_PASS( pMDU );// FAULT
							return true;
						default:
							return false;
					}
				case 8:
					switch (spec)
					{
						case 0:
							OnPaint_GPCMEMORY_PASS( pMDU );// GPC MEMORY
							return true;
						case 18:
							OnPaint_DISP18_PASS( pMDU );// GNC SYS SUMM 1
							return true;
						case 19:
							OnPaint_DISP19_PASS( pMDU );// GNC SYS SUMM 2
							return true;
						case 23:
							OnPaint_SPEC23_PASS( pMDU );// RCS
							return true;
						case 43:
							OnPaint_SPEC43_PASS( pMDU );// CONTROLLERS
							return true;
						case 44:
							OnPaint_SPEC44_PASS( pMDU );// SWITCHES
							return true;
						case 55:
							OnPaint_SPEC55_PASS( pMDU );// GPS STATUS
							return true;
						case 99:
							OnPaint_DISP99_PASS( pMDU );// FAULT
							return true;
						default:
							return false;
					}
				case 9:
					switch (spec)
					{
						case 0:
							OnPaint_GPCMEMORY_PASS( pMDU );// GPC MEMORY
							return true;
						case 55:
							OnPaint_SPEC55_PASS( pMDU );// GPS STATUS
							return true;
						case 99:
							OnPaint_DISP99_PASS( pMDU );// FAULT
							return true;
						case 112:
							OnPaint_SPEC112_PASS( pMDU );// GPC/BTU I/F
							return true;
						case 113:
							OnPaint_SPEC113_PASS( pMDU );// ACTUATOR CONTROL
							return true;
						case dps::MODE_UNDEFINED:
							OnPaint_GPCMEMORY_PASS( pMDU );// GPC MEMORY
							return true;
						default:
							return false;
					}
				default:
					return false;
			}
		}
		else
		{
			// BFS
			switch (GetMajorMode() / 100)
			{
				case 0:
					switch (spec)
					{
						case 99:
							OnPaint_DISP99_BFS( pMDU );// FAULT
							return true;
						default:
							return false;
					}
				case 1:
					switch (spec)
					{
						case 18:
							OnPaint_DISP18_BFS( pMDU );// GNC SYS SUMM 1
							return true;
						case 19:
							OnPaint_DISP19_BFS( pMDU );// GNC SYS SUMM 2
							return true;
						case 51:
							OnPaint_SPEC51_BFS( pMDU );// OVERRIDE
							return true;
						case 55:
							OnPaint_SPEC55_BFS( pMDU );// GPS STATUS
							return true;
						case 99:
							OnPaint_DISP99_BFS( pMDU );// FAULT
							return true;
						default:
							return false;
					}
				case 3:
					switch (spec)
					{
						case 18:
							OnPaint_DISP18_BFS( pMDU );// GNC SYS SUMM 1
							return true;
						case 19:
							OnPaint_DISP19_BFS( pMDU );// GNC SYS SUMM 2
							return true;
						case 51:
							OnPaint_SPEC51_BFS( pMDU );// OVERRIDE
							return true;
						case 55:
							OnPaint_SPEC55_BFS( pMDU );// GPS STATUS
							return true;
						case 99:
							OnPaint_DISP99_BFS( pMDU );// FAULT
							return true;
						default:
							return false;
					}
				case 6:
					switch (spec)
					{
						case 18:
							OnPaint_DISP18_BFS( pMDU );// GNC SYS SUMM 1
							return true;
						case 19:
							OnPaint_DISP19_BFS( pMDU );// GNC SYS SUMM 2
							return true;
						case 51:
							OnPaint_SPEC51_BFS( pMDU );// OVERRIDE
							return true;
						case 55:
							OnPaint_SPEC55_BFS( pMDU );// GPS STATUS
							return true;
						case 99:
							OnPaint_DISP99_BFS( pMDU );// FAULT
							return true;
						default:
							return false;
					}
				default:
					return false;
			}
		}
	}

	void GeneralDisplays::OnPaint_GPCMEMORY_PASS( vc::MDU* pMDU ) const
	{
		PrintCommonHeader( "  GPC MEMORY", pMDU );

		// static parts (labels)
		pMDU->mvprint( 0, 2, "MEM/BUS CONFIG" );
		pMDU->mvprint( 0, 3, "1 CONFIG" );
		pMDU->mvprint( 11, 3, "(" );
		pMDU->mvprint( 14, 3, ")" );
		pMDU->mvprint( 0, 4, "2 GPC" );
		pMDU->mvprint( 1, 6, "STRING 1  7" );
		pMDU->mvprint( 8, 7, "2  8" );
		pMDU->mvprint( 8, 8, "3  9" );
		pMDU->mvprint( 8, 9, "4 10" );
		pMDU->mvprint( 3, 10, "PL 1/2 11" );
		pMDU->mvprint( 4, 12, "CRT 1 12" );
		pMDU->mvprint( 8, 13, "2 13" );
		pMDU->mvprint( 8, 14, "3 14" );
		pMDU->mvprint( 8, 15, "4 15" );
		pMDU->mvprint( 1, 17, "LAUNCH 1 16" );
		pMDU->mvprint( 8, 18, "2 17" );
		pMDU->mvprint( 5, 19, "MM 1 18" );
		pMDU->mvprint( 8, 20, "2 19" );
		pMDU->Underline( 9, 3 );
		pMDU->Underline( 10, 3 );
		pMDU->Underline( 6, 4 );
		pMDU->Underline( 8, 4 );
		pMDU->Underline( 10, 4 );
		pMDU->Underline( 12, 4 );
		pMDU->Underline( 14, 4 );
		pMDU->Underline( 13, 6 );
		pMDU->Underline( 13, 7 );
		pMDU->Underline( 13, 8 );
		pMDU->Underline( 13, 9 );
		pMDU->Underline( 13, 10 );
		pMDU->Underline( 13, 12 );
		pMDU->Underline( 13, 13 );
		pMDU->Underline( 13, 14 );
		pMDU->Underline( 13, 15 );
		pMDU->Underline( 13, 17 );
		pMDU->Underline( 13, 18 );
		pMDU->Underline( 13, 19 );
		pMDU->Underline( 13, 20 );

		pMDU->mvprint( 17, 2, "READ/WRITE" );
		pMDU->mvprint( 18, 3, "DATA 20" );
		pMDU->mvprint( 18, 4, "CODE 21" );
		pMDU->mvprint( 28, 3, "BIT SET 22" );
		pMDU->mvprint( 28, 4, "BIT RST 23" );
		pMDU->mvprint( 41, 3, "SEQ ID 24" );
		pMDU->mvprint( 41, 4, "WRITE  25" );
		pMDU->mvprint( 18, 5, "26 ENG UNITS" );
		pMDU->mvprint( 38, 5, "HEX 27" );
		pMDU->mvprint( 18, 6, "ADD ID   DESIRED   ACTUAL" );
		pMDU->mvprint( 17, 7, "28" );
		pMDU->mvprint( 27, 7, "29" );
		pMDU->mvprint( 17, 8, "30" );
		pMDU->mvprint( 27, 8, "31" );
		pMDU->mvprint( 17, 9, "32" );
		pMDU->mvprint( 27, 9, "33" );
		pMDU->mvprint( 17, 10, "34" );
		pMDU->mvprint( 27, 10, "35" );
		pMDU->mvprint( 17, 11, "36" );
		pMDU->mvprint( 27, 11, "37" );
		pMDU->mvprint( 17, 12, "38" );
		pMDU->mvprint( 27, 12, "39" );
		pMDU->Underline( 31, 5 );
		pMDU->Underline( 32, 5 );
		pMDU->Underline( 33, 5 );
		pMDU->Underline( 20, 7 );
		pMDU->Underline( 21, 7 );
		pMDU->Underline( 22, 7 );
		pMDU->Underline( 23, 7 );
		pMDU->Underline( 24, 7 );
		pMDU->Underline( 30, 7 );
		pMDU->Underline( 31, 7 );
		pMDU->Underline( 32, 7 );
		pMDU->Underline( 33, 7 );

		pMDU->mvprint( 17, 14, "MEMORY DUMP" );
		pMDU->mvprint( 38, 14, "STORE   MC=" );
		pMDU->mvprint( 18, 15, "40 START ID" );
		pMDU->mvprint( 18, 16, "41 NO WORDS" );
		pMDU->mvprint( 18, 17, "42 EDS/FRAME" );
		pMDU->mvprint( 18, 18, "DUMP START/STOP 43" );
		pMDU->mvprint( 39, 15, "45 CONFIG" );
		pMDU->mvprint( 39, 16, "46 GPC" );
		pMDU->mvprint( 39, 17, "STORE 47" );
		pMDU->Underline( 31, 15 );
		pMDU->Underline( 32, 15 );
		pMDU->Underline( 33, 15 );
		pMDU->Underline( 34, 15 );
		pMDU->Underline( 35, 15 );
		pMDU->Underline( 49, 15 );
		pMDU->Underline( 50, 15 );
		pMDU->Underline( 31, 16 );
		pMDU->Underline( 32, 16 );
		pMDU->Underline( 33, 16 );
		pMDU->Underline( 34, 16 );
		pMDU->Underline( 35, 16 );
		pMDU->Underline( 36, 16 );
		pMDU->Underline( 46, 16 );
		pMDU->Underline( 31, 17 );
		pMDU->Underline( 32, 17 );
		pMDU->Underline( 33, 17 );

		pMDU->mvprint( 0, 22, "OPS 3 UPLK 50" );
		pMDU->mvprint( 0, 23, "OPS 3 INIT 51" );
		pMDU->mvprint( 18, 20, "44 DOWNLIST GPC" );
		pMDU->mvprint( 20, 21, "OPS 0 ENA 49" );
		pMDU->mvprint( 17, 23, "ERR LOG RESET 48" );
		pMDU->mvprint( 39, 20, "MM AREA" );
		pMDU->mvprint( 40, 21, "PL  52" );
		pMDU->mvprint( 40, 22, "GNC 53" );
		pMDU->mvprint( 40, 23, "SM  54" );
		pMDU->Underline( 34, 20 );
		pMDU->Underline( 47, 21 );
		pMDU->Underline( 47, 22 );
		pMDU->Underline( 47, 23 );

		// static parts (lines)
		pMDU->Line( 90, 84, 90, 294 );
		pMDU->Line( 160, 28, 160, 294 );
		pMDU->Line( 160, 196, 500, 196 );
		pMDU->Line( 160, 280, 500, 280 );
		pMDU->Line( 10, 294, 160, 294 );

		// dynamic parts
		if (engunit_hex == 0) pMDU->mvprint( 44, 5, "*" );
		else
		{
			char cbuf[4];
			sprintf_s( cbuf, 4, "%d", engunit_hex );
			pMDU->mvprint( 31, 5, cbuf );
		}

		for (int i = 0; i < 6; i++)
		{
			if (!addidvalid[i]) continue;

			char cbuf[16];
			sprintf_s( cbuf, 16, "%05X", addid[i] );
			pMDU->mvprint( 20, 7 + i, cbuf );

			if (engunit_hex == 0)
			{
				sprintf_s( cbuf, 16, "%04X", ReadCOMPOOL_IS( addid[i] ) );
				pMDU->mvprint( 38, 7 + i, cbuf );
			}
			else if (engunit_hex < 200)
			{
				// 16b
				short tmp = ReadCOMPOOL_IS( addid[i] );
				double conv = GetConversionParameter( engunit_hex - 100 );
				tmp = static_cast<short>(tmp * conv);
				if (tmp > 0) pMDU->mvprint( 37, 7 + i, "+" );
				else if (tmp < 0) pMDU->mvprint( 37, 7 + i, "-" );
				sprintf_s( cbuf, 16, "%11d", abs( tmp ) );
				pMDU->mvprint( 38, 7 + i, cbuf );
			}
			else
			{
				// 32b float
				float tmp = ReadCOMPOOL_SD( addid[i] );
				double conv = GetConversionParameter( engunit_hex - 200 );
				tmp = static_cast<float>(tmp * conv);
				if (fabs( tmp ) >= 100000.0) tmp = static_cast<float>(tmp - (sign( tmp ) * 100000.0));
				if (tmp > 0.0) pMDU->mvprint( 37, 7 + i, "+" );
				else if (tmp < 0.0) pMDU->mvprint( 37, 7 + i, "-" );
				sprintf_s( cbuf, 16, "%#11.5f", fabs( tmp ) );
				pMDU->mvprint( 38, 7 + i, cbuf );
			}
		}
		return;
	}

	void GeneralDisplays::OnPaint_DISP18_PASS( vc::MDU* pMDU ) const
	{
		PrintCommonHeader( " GNC SYS SUMM 1", pMDU );

		// static parts (labels)
		// RCS
		pMDU->mvprint( 0, 2, "RCS  JETISOL" );
		pMDU->mvprint( 0, 3, "MANFFAILVLV" );
		pMDU->mvprint( 2, 4, "F1" );
		pMDU->mvprint( 3, 5, "2" );
		pMDU->mvprint( 3, 6, "3" );
		pMDU->mvprint( 3, 7, "4" );
		pMDU->mvprint( 3, 8, "5" );
		pMDU->mvprint( 2, 9, "L1" );
		pMDU->mvprint( 3, 10, "2" );
		pMDU->mvprint( 3, 11, "3" );
		pMDU->mvprint( 3, 12, "4" );
		pMDU->mvprint( 3, 13, "5" );
		pMDU->mvprint( 2, 14, "R1" );
		pMDU->mvprint( 3, 15, "2" );
		pMDU->mvprint( 3, 16, "3" );
		pMDU->mvprint( 3, 17, "4" );
		pMDU->mvprint( 3, 18, "5" );

		// SURF
		pMDU->mvprint( 14, 3, "SURF     POS   MOM" );
		pMDU->mvprint( 14, 4, "L OB" );
		pMDU->mvprint( 16, 5, "IB" );
		pMDU->mvprint( 14, 6, "R IB" );
		pMDU->mvprint( 16, 7, "OB" );
		pMDU->mvprint( 14, 8, "AIL" );
		pMDU->mvprint( 14, 9, "RUD" );
		pMDU->mvprint( 14, 10, "SPD BRK" );
		pMDU->mvprint( 14, 11, "BDY FLP" );

		// DPS
		pMDU->mvprint( 34, 3, "DPS    1 2 3 4 5" );
		pMDU->mvprint( 37, 4, "GPC" );
		pMDU->mvprint( 34, 5, "MDM FF" );
		pMDU->mvprint( 38, 6, "FA" );

		// FCS
		pMDU->mvprint( 34, 9, "FCS CH 1 2 3 4" );

		// NAV
		pMDU->mvprint( 34, 13, "NAV    1 2 3 4" );
		pMDU->mvprint( 36, 14, "IMU" );
		pMDU->mvprint( 36, 15, "ACC" );
		pMDU->mvprint( 36, 16, "RGA" );
		pMDU->mvprint( 36, 17, "TAC" );
		pMDU->mvprint( 36, 18, "MLS" );
		pMDU->mvprint( 36, 19, "ADTA" );

		// CNTLR
		pMDU->mvprint( 16, 15, "CNTLR  1 2 3" );
		pMDU->mvprint( 16, 16, "RHC  L" );
		pMDU->mvprint( 21, 17, "R" );
		pMDU->mvprint( 21, 18, "A" );
		pMDU->mvprint( 16, 19, "THC  L" );
		pMDU->mvprint( 21, 20, "A" );
		pMDU->mvprint( 16, 21, "SBTC L" );
		pMDU->mvprint( 21, 22, "R" );


		// static parts (lines)
		// RCS
		pMDU->Line( 40, 14, 40, 266 );
		pMDU->Line( 80, 14, 80, 266 );
		pMDU->Line( 0, 56, 120, 56 );
		pMDU->Line( 0, 126, 120, 126 );
		pMDU->Line( 0, 196, 120, 196 );

		// SURF
		pMDU->Line( 140, 56, 320, 56 );

		// DPS
		pMDU->Line( 340, 56, 500, 56 );

		// FCS
		pMDU->Line( 340, 140, 480, 140 );

		// NAV
		pMDU->Line( 340, 196, 480, 196 );

		// CNTRL
		pMDU->Line( 160, 224, 280, 224 );


		// dynamic parts
		unsigned int MM = ReadCOMPOOL_IS( SCP_MM );
		// TODO finish
		char cbuf[64];
		double tmp = 0;
		char pos;

		// RCS

		// SURF
		if (((MM / 100) == 3) || ((MM / 100) == 6))
		{
			double LOB = ReadCOMPOOL_SD( SCP_LOB_ELVN_POS_FDBK );
			double LIB = ReadCOMPOOL_SD( SCP_LIB_ELVN_POS_FDBK );
			double RIB = ReadCOMPOOL_SD( SCP_RIB_ELVN_POS_FDBK );
			double ROB = ReadCOMPOOL_SD( SCP_ROB_ELVN_POS_FDBK );
			double DAFB = ReadCOMPOOL_SD( SCP_DAFB );
			double DRFB = ReadCOMPOOL_SD( SCP_DRFB );
			double DSBFB = ReadCOMPOOL_SD( SCP_DSBFB_DEG );
			double DBFOFB = ReadCOMPOOL_SD( SCP_DBFOFB );

			if (LOB > 0.0) pos = 'D';
			else if (LOB < 0.0) pos = 'U';
			else pos = ' ';
			sprintf_s( cbuf, 64, "%c%4.1f  %2.0f", pos, fabs( LOB ), tmp );
			pMDU->mvprint( 22, 4, cbuf );

			if (LIB > 0.0) pos = 'D';
			else if (LIB < 0.0) pos = 'U';
			else pos = ' ';
			sprintf_s( cbuf, 64, "%c%4.1f  %2.0f", pos, fabs( LIB ), tmp );
			pMDU->mvprint( 22, 5, cbuf );

			if (RIB > 0.0) pos = 'D';
			else if (RIB < 0.0) pos = 'U';
			else pos = ' ';
			sprintf_s( cbuf, 64, "%c%4.1f  %2.0f", pos, fabs( RIB ), tmp );
			pMDU->mvprint( 22, 6, cbuf );

			if (ROB > 0.0) pos = 'D';
			else if (ROB < 0.0) pos = 'U';
			else pos = ' ';
			sprintf_s( cbuf, 64, "%c%4.1f  %2.0f", pos, fabs( ROB ), tmp );
			pMDU->mvprint( 22, 7, cbuf );

			if (DAFB > 0.0) pos = 'R';
			else if (DAFB < 0.0) pos = 'L';
			else pos = ' ';
			sprintf_s( cbuf, 64, "%c%4.1f", pos, fabs( DAFB ) );
			pMDU->mvprint( 22, 8, cbuf );

			if (DRFB > 0.0) pos = 'L';
			else if (DRFB < 0.0) pos = 'R';
			else pos = ' ';
			sprintf_s( cbuf, 64, "%c%4.1f", pos, fabs( DRFB ) );
			pMDU->mvprint( 22, 9, cbuf );

			sprintf_s( cbuf, 64, "%5.1f", fabs( DSBFB ) );
			pMDU->mvprint( 22, 10, cbuf );

			sprintf_s( cbuf, 64, "%5.1f", range( 0.0, fabs( (DBFOFB + 11.7) * 2.919708 ), 100.0 ) );
			pMDU->mvprint( 22, 11, cbuf );
		}

		// DPS

		// FCS

		// NAV

		// CNTLR
		return;
	}

	void GeneralDisplays::OnPaint_DISP19_PASS( vc::MDU* pMDU ) const
	{
		PrintCommonHeader( " GNC SYS SUMM 2", pMDU );

		// static parts (labels)
		// OMS
		pMDU->mvprint( 0, 2, "OMS AFT QTY    L     R" );
		pMDU->mvprint( 8, 3, "OXID" );
		pMDU->mvprint( 10, 4, "FU" );
		pMDU->mvprint( 29, 2, "OMS" );
		pMDU->mvprint( 42, 2, "L" );
		pMDU->mvprint( 48, 2, "R" );
		pMDU->mvprint( 30, 3, "TK P   HE" );
		pMDU->mvprint( 35, 4, "OXID" );
		pMDU->mvprint( 37, 5, "FU" );
		pMDU->mvprint( 30, 6, "N2 TK   P" );
		pMDU->mvprint( 33, 7, "REG  P" );
		pMDU->mvprint( 33, 8, "P  VLV" );
		pMDU->mvprint( 29, 9, "ENG IN   P" );
		pMDU->mvprint( 35, 10, "OXID" );
		pMDU->mvprint( 37, 11, "FU" );
		pMDU->mvprint( 34, 12, "VLV 1" );
		pMDU->mvprint( 38, 13, "2" );

		// RCS
		pMDU->mvprint( 20, 6, "JETISOL" );
		pMDU->mvprint( 0, 7, "RCS       OXID  FU FAIL VLV" );
		pMDU->mvprint( 0, 8, "FWD  HE P" );
		pMDU->mvprint( 5, 9, "TK P" );
		pMDU->mvprint( 6, 10, "QTY" );
		pMDU->mvprint( 0, 11, "MANF  1 P" );
		pMDU->mvprint( 6, 12, "2 P" );
		pMDU->mvprint( 6, 13, "3 P" );
		pMDU->mvprint( 6, 14, "4 P" );
		pMDU->mvprint( 6, 15, "5" );
		pMDU->mvprint( 0, 16, "AFT  HE P" );
		pMDU->mvprint( 0, 17, "L    TK P" );
		pMDU->mvprint( 6, 18, "QTY" );
		pMDU->mvprint( 0, 19, "MANF  1 P" );
		pMDU->mvprint( 6, 20, "2 P" );
		pMDU->mvprint( 6, 21, "3 P" );
		pMDU->mvprint( 6, 22, "4 P" );
		pMDU->mvprint( 6, 23, "5" );
		pMDU->mvprint( 44, 14, "JETISOL" );
		pMDU->mvprint( 34, 15, "OXID  FU FAIL VLV" );
		pMDU->mvprint( 29, 16, "HE P" );
		pMDU->mvprint( 27, 17, "R TK P" );
		pMDU->mvprint( 30, 18, "QTY" );
		pMDU->mvprint( 30, 19, "1 P" );
		pMDU->mvprint( 30, 20, "2 P" );
		pMDU->mvprint( 30, 21, "3 P" );
		pMDU->mvprint( 30, 22, "4 P" );
		pMDU->mvprint( 30, 23, "5" );


		// static parts (lines)
		pMDU->Line( 90, 84, 90, 336 );
		pMDU->Line( 140, 84, 140, 336 );
		pMDU->Line( 190, 84, 190, 336 );
		pMDU->Line( 230, 84, 230, 336 );
		pMDU->Line( 270, 84, 270, 336 );
		pMDU->Line( 330, 196, 330, 336 );
		pMDU->Line( 380, 196, 380, 336 );
		pMDU->Line( 430, 196, 430, 336 );
		pMDU->Line( 470, 196, 470, 336 );
		pMDU->Line( 0, 84, 270, 84 );
		pMDU->Line( 0, 112, 270, 112 );
		pMDU->Line( 60, 154, 190, 154 );
		pMDU->Line( 270, 196, 510, 196 );
		pMDU->Line( 0, 224, 510, 224 );
		pMDU->Line( 60, 266, 190, 266 );
		pMDU->Line( 300, 266, 430, 266 );


		// TODO dynamic parts
		return;
	}

	void GeneralDisplays::OnPaint_SPEC23_PASS( vc::MDU* pMDU ) const
	{
		PrintCommonHeader( "      RCS", pMDU );

		// static parts (labels)
		pMDU->mvprint( 0, 2, "F 1" );
		pMDU->mvprint( 0, 3, "L 2" );
		pMDU->mvprint( 0, 4, "R 3" );

		pMDU->mvprint( 6, 2, "4 PRI FAIL LIM" );
		pMDU->mvprint( 5, 4, "51 AUT MANF CL" );

		pMDU->mvprint( 24, 2, "L OMS" );
		pMDU->RightArrow( 29, 2 );
		pMDU->mvprint( 24, 3, "AFT  5" );
		pMDU->mvprint( 24, 4, "FWD 46" );
		pMDU->mvprint( 32, 2, "R OMS" );
		pMDU->RightArrow( 37, 2 );
		pMDU->mvprint( 32, 3, "AFT  6" );
		pMDU->mvprint( 32, 4, "FWD 47" );
		pMDU->mvprint( 28, 5, "OFF   7" );
		pMDU->mvprint( 25, 6, "48 PRESS" );

		pMDU->mvprint( 40, 3, "OMS RCS QTY" );
		pMDU->RightArrow( 43, 3 );
		pMDU->mvprint( 40, 4, "49L" );
		pMDU->mvprint( 40, 5, "50R" );

		pMDU->mvprint( 1, 6, "JET FAIL DES JET PTY" );
		pMDU->mvprint( 10, 7, "INH DES" );

		pMDU->mvprint( 0, 10, "Y" );
		pMDU->mvprint( 0, 14, "Z" );
		pMDU->mvprint( 3, 12, "U" );
		pMDU->mvprint( 3, 13, "U" );
		pMDU->mvprint( 3, 14, "U" );
		pMDU->mvprint( 2, 17, "2" );
		pMDU->mvprint( 3, 16, "D" );
		pMDU->mvprint( 3, 17, "D" );
		pMDU->mvprint( 3, 18, "D" );
		pMDU->mvprint( 0, 23, "V" );
		pMDU->mvprint( 2, 22, "5" );
		pMDU->mvprint( 2, 23, "5" );

		pMDU->mvprint( 11, 8, "8" );
		pMDU->mvprint( 15, 8, "9" );
		pMDU->mvprint( 10, 9, "10" );
		pMDU->mvprint( 14, 9, "11" );
		pMDU->mvprint( 10, 10, "12" );
		pMDU->mvprint( 14, 10, "13" );
		pMDU->mvprint( 10, 11, "14" );
		pMDU->mvprint( 14, 11, "15" );
		pMDU->mvprint( 10, 12, "16" );
		pMDU->mvprint( 14, 12, "17" );
		pMDU->mvprint( 10, 13, "18" );
		pMDU->mvprint( 14, 13, "19" );
		pMDU->mvprint( 10, 14, "20" );
		pMDU->mvprint( 14, 14, "21" );
		pMDU->mvprint( 10, 15, "22" );
		pMDU->mvprint( 14, 15, "23" );
		pMDU->mvprint( 10, 16, "24" );
		pMDU->mvprint( 14, 16, "25" );
		pMDU->mvprint( 10, 17, "26" );
		pMDU->mvprint( 14, 17, "27" );
		pMDU->mvprint( 10, 18, "28" );
		pMDU->mvprint( 14, 18, "29" );
		pMDU->mvprint( 10, 19, "30" );
		pMDU->mvprint( 14, 19, "31" );
		pMDU->mvprint( 10, 20, "32" );
		pMDU->mvprint( 14, 20, "33" );
		pMDU->mvprint( 10, 21, "34" );
		pMDU->mvprint( 14, 21, "35" );
		pMDU->mvprint( 10, 22, "36" );
		pMDU->mvprint( 14, 22, "37" );
		pMDU->mvprint( 10, 23, "38" );
		pMDU->mvprint( 14, 23, "39" );

		pMDU->mvprint( 39, 7, "OXID FU" );
		pMDU->mvprint( 27, 8, "HE" );
		pMDU->mvprint( 36, 8, "P" );
		pMDU->mvprint( 27, 9, "PRPLT TK P" );
		pMDU->mvprint( 36, 10, "T" );
		pMDU->mvprint( 34, 11, "QTY" );
		pMDU->mvprint( 27, 12, "MANF P   1" );
		pMDU->mvprint( 36, 13, "2" );
		pMDU->mvprint( 36, 14, "3" );
		pMDU->mvprint( 36, 15, "4" );
		pMDU->mvprint( 27, 16, "MANF VLVS" );
		pMDU->mvprint( 35, 17, "1" );
		pMDU->mvprint( 35, 18, "2" );
		pMDU->mvprint( 35, 19, "3" );
		pMDU->mvprint( 35, 20, "4" );
		pMDU->mvprint( 35, 21, "5" );
		pMDU->mvprint( 27, 22, "XFEED   P" );
		pMDU->mvprint( 27, 23, "JET RESET 45" );

		pMDU->mvprint( 39, 16, "STAT  OVRD" );
		pMDU->mvprint( 46, 17, "40" );
		pMDU->mvprint( 46, 18, "41" );
		pMDU->mvprint( 46, 19, "42" );
		pMDU->mvprint( 46, 20, "43" );
		pMDU->mvprint( 46, 21, "44" );

		// static parts (lines)
		pMDU->Line( 40, 28, 40, 70 );
		pMDU->Line( 230, 28, 230, 98 );
		pMDU->Line( 310, 28, 310, 70 );
		pMDU->Line( 390, 28, 390, 98 );

		pMDU->Line( 50, 84, 50, 336 );
		pMDU->Line( 100, 84, 100, 336 );
		pMDU->Line( 140, 84, 140, 336 );
		pMDU->Line( 180, 84, 180, 336 );

		pMDU->Line( 380, 98, 380, 308 );
		pMDU->Line( 440, 98, 440, 308 );
		
		pMDU->Line( 0, 112, 210, 112 );
		pMDU->Line( 0, 168, 210, 168 );
		pMDU->Line( 20, 210, 210, 210 );
		pMDU->Line( 0, 266, 210, 266 );
		pMDU->Line( 0, 308, 210, 308 );

		pMDU->Line( 260, 112, 490, 112 );
		pMDU->Line( 260, 126, 490, 126 );
		pMDU->Line( 260, 168, 490, 168 );
		pMDU->Line( 260, 224, 490, 224 );
		pMDU->Line( 380, 238, 490, 238 );
		pMDU->Line( 260, 308, 490, 308 );
		pMDU->Line( 260, 322, 490, 322 );

		// dynamic parts
		if (SPEC23_RCSsel == 2)// LRCS
		{
			pMDU->mvprint( 3, 3, "*" );

			pMDU->mvprint( 1, 8, "L4L" );
			pMDU->mvprint( 2, 9, "2L" );
			pMDU->mvprint( 2, 10, "3L" );
			pMDU->mvprint( 2, 11, "1L" );

			pMDU->mvprint( 1, 12, "L4" );
			pMDU->mvprint( 2, 13, "2" );
			pMDU->mvprint( 2, 14, "1" );
			
			pMDU->mvprint( 1, 15, "L" );
			pMDU->mvprint( 2, 16, "4" );
			pMDU->mvprint( 2, 18, "3" );
			
			pMDU->mvprint( 1, 19, "L3A" );
			pMDU->mvprint( 2, 20, "1A" );
			
			pMDU->mvprint( 1, 22, "L" );
			pMDU->mvprint( 3, 22, "L" );
			pMDU->mvprint( 3, 23, "D" );
		}
		else if (SPEC23_RCSsel == 3)// RRCS
		{
			pMDU->mvprint( 3, 4, "*" );

			pMDU->mvprint( 1, 8, "R4R" );
			pMDU->mvprint( 2, 9, "2R" );
			pMDU->mvprint( 2, 10, "3R" );
			pMDU->mvprint( 2, 11, "1R" );

			pMDU->mvprint( 1, 12, "R4" );
			pMDU->mvprint( 2, 13, "2" );
			pMDU->mvprint( 2, 14, "1" );
			
			pMDU->mvprint( 1, 15, "R" );
			pMDU->mvprint( 2, 16, "4" );
			pMDU->mvprint( 2, 18, "3" );
			
			pMDU->mvprint( 1, 19, "R1A" );
			pMDU->mvprint( 2, 20, "3A" );
			
			pMDU->mvprint( 1, 22, "R" );
			pMDU->mvprint( 3, 22, "R" );
			pMDU->mvprint( 3, 23, "D" );
		}
		else //if (SPEC23_RCSsel == 1)// FRCS
		{
			pMDU->mvprint( 3, 2, "*" );

			pMDU->mvprint( 1, 8, "F1L" );
			pMDU->mvprint( 2, 9, "3L" );
			pMDU->mvprint( 2, 10, "2R" );
			pMDU->mvprint( 2, 11, "4R" );

			pMDU->mvprint( 1, 12, "F1" );
			pMDU->mvprint( 2, 13, "3" );
			pMDU->mvprint( 2, 14, "2" );
			
			pMDU->mvprint( 1, 15, "F1D" );
			pMDU->mvprint( 2, 16, "3" );
			pMDU->mvprint( 2, 18, "4" );
			
			pMDU->mvprint( 1, 19, "F1F" );
			pMDU->mvprint( 2, 20, "3F" );
			pMDU->mvprint( 2, 21, "2F" );
			
			pMDU->mvprint( 1, 22, "F" );
			pMDU->mvprint( 3, 22, "L" );
			pMDU->mvprint( 3, 23, "R" );
		}
		
		return;
	}

	void GeneralDisplays::OnPaint_SPEC25_PASS( vc::MDU* pMDU ) const
	{
		PrintCommonHeader( "   RM ORBIT", pMDU );

		// static parts (labels)
		// THC
		pMDU->mvprint( 3, 6, "THC TX TY TZ DES" );
		pMDU->mvprint( 3, 8, "L 1" );
		pMDU->mvprint( 17, 8, "1" );
		pMDU->mvprint( 5, 9, "2" );
		pMDU->mvprint( 17, 9, "2" );
		pMDU->mvprint( 5, 10, "3" );
		pMDU->mvprint( 17, 10, "3" );
		pMDU->mvprint( 3, 12, "A 1" );
		pMDU->mvprint( 17, 12, "4" );
		pMDU->mvprint( 5, 13, "2" );
		pMDU->mvprint( 17, 13, "5" );
		pMDU->mvprint( 5, 14, "3" );
		pMDU->mvprint( 17, 14, "6" );

		// RHC
		pMDU->mvprint( 23, 6, "RHC  R    P    Y   DES" );
		pMDU->mvprint( 23, 8, "L 1" );
		pMDU->mvprint( 43, 8, "7" );
		pMDU->mvprint( 25, 9, "2" );
		pMDU->mvprint( 43, 9, "8" );
		pMDU->mvprint( 25, 10, "3" );
		pMDU->mvprint( 43, 10, "9" );
		pMDU->mvprint( 23, 12, "R 1" );
		pMDU->mvprint( 42, 12, "10" );
		pMDU->mvprint( 25, 13, "2" );
		pMDU->mvprint( 42, 13, "11" );
		pMDU->mvprint( 25, 14, "3" );
		pMDU->mvprint( 42, 14, "12" );
		pMDU->mvprint( 23, 16, "A 1" );
		pMDU->mvprint( 42, 16, "13" );
		pMDU->mvprint( 25, 17, "2" );
		pMDU->mvprint( 42, 17, "14" );
		pMDU->mvprint( 25, 18, "3" );
		pMDU->mvprint( 42, 18, "15" );

		pMDU->mvprint( 23, 23, "SW RM INH 16" );

		// dynamic parts
		unsigned short FF1_IOM6_CH0 = ReadCOMPOOL_IS( SCP_FF1_IOM6_CH0_DATA );
		unsigned short FF1_IOM15_CH0 = ReadCOMPOOL_IS( SCP_FF1_IOM15_CH0_DATA );
		unsigned short FF2_IOM6_CH0 = ReadCOMPOOL_IS( SCP_FF2_IOM6_CH0_DATA );
		unsigned short FF2_IOM15_CH0 = ReadCOMPOOL_IS( SCP_FF2_IOM15_CH0_DATA );
		unsigned short FF3_IOM6_CH0 = ReadCOMPOOL_IS( SCP_FF3_IOM6_CH0_DATA );
		unsigned short FF3_IOM15_CH0 = ReadCOMPOOL_IS( SCP_FF3_IOM15_CH0_DATA );

		bool FWD_THC_POS_X_OUTPUT_A = ((FF1_IOM6_CH0 & 0x0080) != 0);
		bool FWD_THC_NEG_X_OUTPUT_A = ((FF1_IOM6_CH0 & 0x0100) != 0);
		SPEC25_SPEC43_printTHC( pMDU, FWD_THC_POS_X_OUTPUT_A, FWD_THC_NEG_X_OUTPUT_A, 7, 8 );
		bool FWD_THC_POS_X_OUTPUT_B = ((FF2_IOM6_CH0 & 0x0080) != 0);
		bool FWD_THC_NEG_X_OUTPUT_B = ((FF2_IOM6_CH0 & 0x0100) != 0);
		SPEC25_SPEC43_printTHC( pMDU, FWD_THC_POS_X_OUTPUT_B, FWD_THC_NEG_X_OUTPUT_B, 7, 9 );
		bool FWD_THC_POS_X_OUTPUT_C = ((FF3_IOM6_CH0 & 0x0080) != 0);
		bool FWD_THC_NEG_X_OUTPUT_C = ((FF3_IOM6_CH0 & 0x0100) != 0);
		SPEC25_SPEC43_printTHC( pMDU, FWD_THC_POS_X_OUTPUT_C, FWD_THC_NEG_X_OUTPUT_C, 7, 10 );
		bool FWD_THC_POS_Y_OUTPUT_A = ((FF1_IOM6_CH0 & 0x0200) != 0);
		bool FWD_THC_NEG_Y_OUTPUT_A = ((FF1_IOM6_CH0 & 0x0400) != 0);
		SPEC25_SPEC43_printTHC( pMDU, FWD_THC_POS_Y_OUTPUT_A, FWD_THC_NEG_Y_OUTPUT_A, 10, 8 );
		bool FWD_THC_POS_Y_OUTPUT_B = ((FF2_IOM6_CH0 & 0x0200) != 0);
		bool FWD_THC_NEG_Y_OUTPUT_B = ((FF2_IOM6_CH0 & 0x0400) != 0);
		SPEC25_SPEC43_printTHC( pMDU, FWD_THC_POS_Y_OUTPUT_B, FWD_THC_NEG_Y_OUTPUT_B, 10, 9 );
		bool FWD_THC_POS_Y_OUTPUT_C = ((FF3_IOM6_CH0 & 0x0200) != 0);
		bool FWD_THC_NEG_Y_OUTPUT_C = ((FF3_IOM6_CH0 & 0x0400) != 0);
		SPEC25_SPEC43_printTHC( pMDU, FWD_THC_POS_Y_OUTPUT_C, FWD_THC_NEG_Y_OUTPUT_C, 10, 10 );
		bool FWD_THC_POS_Z_OUTPUT_A = ((FF1_IOM6_CH0 & 0x0800) != 0);
		bool FWD_THC_NEG_Z_OUTPUT_A = ((FF1_IOM6_CH0 & 0x1000) != 0);
		SPEC25_SPEC43_printTHC( pMDU, FWD_THC_POS_Z_OUTPUT_A, FWD_THC_NEG_Z_OUTPUT_A, 13, 8 );
		bool FWD_THC_POS_Z_OUTPUT_B = ((FF2_IOM6_CH0 & 0x0800) != 0);
		bool FWD_THC_NEG_Z_OUTPUT_B = ((FF2_IOM6_CH0 & 0x1000) != 0);
		SPEC25_SPEC43_printTHC( pMDU, FWD_THC_POS_Z_OUTPUT_B, FWD_THC_NEG_Z_OUTPUT_B, 13, 9 );
		bool FWD_THC_POS_Z_OUTPUT_C = ((FF3_IOM6_CH0 & 0x0800) != 0);
		bool FWD_THC_NEG_Z_OUTPUT_C = ((FF3_IOM6_CH0 & 0x1000) != 0);
		SPEC25_SPEC43_printTHC( pMDU, FWD_THC_POS_Z_OUTPUT_C, FWD_THC_NEG_Z_OUTPUT_C, 13, 10 );

		bool AFT_THC_POS_X_OUTPUT_A = ((FF1_IOM15_CH0 & 0x0080) != 0);
		bool AFT_THC_NEG_X_OUTPUT_A = ((FF1_IOM15_CH0 & 0x0100) != 0);
		SPEC25_SPEC43_printTHC( pMDU, AFT_THC_POS_X_OUTPUT_A, AFT_THC_NEG_X_OUTPUT_A, 7, 12 );
		bool AFT_THC_POS_X_OUTPUT_B = ((FF2_IOM15_CH0 & 0x0080) != 0);
		bool AFT_THC_NEG_X_OUTPUT_B = ((FF2_IOM15_CH0 & 0x0100) != 0);
		SPEC25_SPEC43_printTHC( pMDU, AFT_THC_POS_X_OUTPUT_B, AFT_THC_NEG_X_OUTPUT_B, 7, 13 );
		bool AFT_THC_POS_X_OUTPUT_C = ((FF3_IOM15_CH0 & 0x0080) != 0);
		bool AFT_THC_NEG_X_OUTPUT_C = ((FF3_IOM15_CH0 & 0x0100) != 0);
		SPEC25_SPEC43_printTHC( pMDU, AFT_THC_POS_X_OUTPUT_C, AFT_THC_NEG_X_OUTPUT_C, 7, 14 );
		bool AFT_THC_POS_Y_OUTPUT_A = ((FF1_IOM15_CH0 & 0x0200) != 0);
		bool AFT_THC_NEG_Y_OUTPUT_A = ((FF1_IOM15_CH0 & 0x0400) != 0);
		SPEC25_SPEC43_printTHC( pMDU, AFT_THC_POS_Y_OUTPUT_A, AFT_THC_NEG_Y_OUTPUT_A, 10, 12 );
		bool AFT_THC_POS_Y_OUTPUT_B = ((FF2_IOM15_CH0 & 0x0200) != 0);
		bool AFT_THC_NEG_Y_OUTPUT_B = ((FF2_IOM15_CH0 & 0x0400) != 0);
		SPEC25_SPEC43_printTHC( pMDU, AFT_THC_POS_Y_OUTPUT_B, AFT_THC_NEG_Y_OUTPUT_B, 10, 13 );
		bool AFT_THC_POS_Y_OUTPUT_C = ((FF3_IOM15_CH0 & 0x0200) != 0);
		bool AFT_THC_NEG_Y_OUTPUT_C = ((FF3_IOM15_CH0 & 0x0400) != 0);
		SPEC25_SPEC43_printTHC( pMDU, AFT_THC_POS_Y_OUTPUT_C, AFT_THC_NEG_Y_OUTPUT_C, 10, 14 );
		bool AFT_THC_POS_Z_OUTPUT_A = ((FF1_IOM15_CH0 & 0x0800) != 0);
		bool AFT_THC_NEG_Z_OUTPUT_A = ((FF1_IOM15_CH0 & 0x1000) != 0);
		SPEC25_SPEC43_printTHC( pMDU, AFT_THC_POS_Z_OUTPUT_A, AFT_THC_NEG_Z_OUTPUT_A, 13, 12 );
		bool AFT_THC_POS_Z_OUTPUT_B = ((FF2_IOM15_CH0 & 0x0800) != 0);
		bool AFT_THC_NEG_Z_OUTPUT_B = ((FF2_IOM15_CH0 & 0x1000) != 0);
		SPEC25_SPEC43_printTHC( pMDU, AFT_THC_POS_Z_OUTPUT_B, AFT_THC_NEG_Z_OUTPUT_B, 13, 13 );
		bool AFT_THC_POS_Z_OUTPUT_C = ((FF3_IOM15_CH0 & 0x0800) != 0);
		bool AFT_THC_NEG_Z_OUTPUT_C = ((FF3_IOM15_CH0 & 0x1000) != 0);
		SPEC25_SPEC43_printTHC( pMDU, AFT_THC_POS_Z_OUTPUT_C, AFT_THC_NEG_Z_OUTPUT_C, 13, 14 );


		SPEC25_SPEC43_printRHC_RY( pMDU, LeftRHC[3].GetVoltage(), 27, 8 );
		SPEC25_SPEC43_printRHC_RY( pMDU, LeftRHC[4].GetVoltage(), 27, 9 );
		SPEC25_SPEC43_printRHC_RY( pMDU, LeftRHC[5].GetVoltage(), 27, 10 );
		SPEC25_SPEC43_printRHC_P( pMDU, LeftRHC[0].GetVoltage(), 32, 8 );
		SPEC25_SPEC43_printRHC_P( pMDU, LeftRHC[1].GetVoltage(), 32, 9 );
		SPEC25_SPEC43_printRHC_P( pMDU, LeftRHC[2].GetVoltage(), 32, 10 );
		SPEC25_SPEC43_printRHC_RY( pMDU, LeftRHC[6].GetVoltage(), 37, 8 );
		SPEC25_SPEC43_printRHC_RY( pMDU, LeftRHC[7].GetVoltage(), 37, 9 );
		SPEC25_SPEC43_printRHC_RY( pMDU, LeftRHC[8].GetVoltage(), 37, 10 );

		SPEC25_SPEC43_printRHC_RY( pMDU, RightRHC[3].GetVoltage(), 27, 12 );
		SPEC25_SPEC43_printRHC_RY( pMDU, RightRHC[4].GetVoltage(), 27, 13 );
		SPEC25_SPEC43_printRHC_RY( pMDU, RightRHC[5].GetVoltage(), 27, 14 );
		SPEC25_SPEC43_printRHC_P( pMDU, RightRHC[0].GetVoltage(), 32, 12 );
		SPEC25_SPEC43_printRHC_P( pMDU, RightRHC[1].GetVoltage(), 32, 13 );
		SPEC25_SPEC43_printRHC_P( pMDU, RightRHC[2].GetVoltage(), 32, 14 );
		SPEC25_SPEC43_printRHC_RY( pMDU, RightRHC[6].GetVoltage(), 37, 12 );
		SPEC25_SPEC43_printRHC_RY( pMDU, RightRHC[7].GetVoltage(), 37, 13 );
		SPEC25_SPEC43_printRHC_RY( pMDU, RightRHC[8].GetVoltage(), 37, 14 );

		SPEC25_SPEC43_printRHC_RY( pMDU, AftRHC[3].GetVoltage(), 27, 16 );
		SPEC25_SPEC43_printRHC_RY( pMDU, AftRHC[4].GetVoltage(), 27, 17 );
		SPEC25_SPEC43_printRHC_RY( pMDU, AftRHC[5].GetVoltage(), 27, 18 );
		SPEC25_SPEC43_printRHC_P( pMDU, AftRHC[0].GetVoltage(), 32, 16 );
		SPEC25_SPEC43_printRHC_P( pMDU, AftRHC[1].GetVoltage(), 32, 17 );
		SPEC25_SPEC43_printRHC_P( pMDU, AftRHC[2].GetVoltage(), 32, 18 );
		SPEC25_SPEC43_printRHC_RY( pMDU, AftRHC[6].GetVoltage(), 37, 16 );
		SPEC25_SPEC43_printRHC_RY( pMDU, AftRHC[7].GetVoltage(), 37, 17 );
		SPEC25_SPEC43_printRHC_RY( pMDU, AftRHC[8].GetVoltage(), 37, 18 );
		return;
	}

	void GeneralDisplays::SPEC25_SPEC43_printTHC( vc::MDU* pMDU, bool axis_plus, bool axis_minus, int x, int y ) const
	{
		char ctmp[2];
		ctmp[0] = ' ';
		ctmp[1] = 0;
		if (axis_plus && !axis_minus) ctmp[0] = '+';
		else if (!axis_plus && axis_minus) ctmp[0] = '-';
		pMDU->mvprint( x, y, ctmp );
		return;
	}

	void GeneralDisplays::SPEC25_SPEC43_printRHC_P( vc::MDU* pMDU, double val, int x, int y ) const
	{
		char cbuf[16];
		int itmp = 0;
		char ctmp = 0;

		itmp = min( (int)fabs( val * 100 ), 99 );
		if (val > 0) ctmp = 'U';
		else if (val < 0) ctmp = 'D';
		else ctmp = ' ';
		sprintf_s( cbuf, 16, "%c%02d", ctmp, itmp );
		pMDU->mvprint( x, y, cbuf );
		return;
	}

	void GeneralDisplays::SPEC25_SPEC43_printRHC_RY( vc::MDU* pMDU, double val, int x, int y ) const
	{
		char cbuf[16];
		int itmp = 0;
		char ctmp = 0;

		itmp = min( (int)fabs( val * 100 ), 99 );
		if (val > 0) ctmp = 'R';
		else if (val < 0) ctmp = 'L';
		else ctmp = ' ';
		sprintf_s( cbuf, 16, "%c%02d", ctmp, itmp );
		pMDU->mvprint( x, y, cbuf );
		return;
	}

	void GeneralDisplays::OnPaint_SPEC43_PASS( vc::MDU* pMDU ) const
	{
		PrintCommonHeader( "  CONTROLLERS", pMDU );

		// static parts (labels)
		pMDU->mvprint( 6, 3, "TXTYTZDES" );
		pMDU->mvprint( 5, 4, "1" );
		pMDU->mvprint( 13, 4, "1" );
		pMDU->mvprint( 4, 5, "L2" );
		pMDU->mvprint( 13, 5, "2" );
		pMDU->mvprint( 0, 6, "THC  3" );
		pMDU->mvprint( 13, 6, "3" );
		pMDU->mvprint( 5, 7, "1" );
		pMDU->mvprint( 13, 7, "4" );
		pMDU->mvprint( 4, 8, "A2" );
		pMDU->mvprint( 13, 8, "5" );
		pMDU->mvprint( 5, 9, "3" );
		pMDU->mvprint( 13, 9, "6" );
		pMDU->mvprint( 5, 10, "1" );
		pMDU->mvprint( 13, 10, "7" );
		pMDU->mvprint( 4, 11, "L2" );
		pMDU->mvprint( 13, 11, "8" );
		pMDU->mvprint( 5, 12, "3" );
		pMDU->mvprint( 13, 12, "9" );
		pMDU->mvprint( 0, 13, "SPD  1" );
		pMDU->mvprint( 12, 13, "10" );
		pMDU->mvprint( 0, 14, "BK  R2" );
		pMDU->mvprint( 12, 14, "11" );
		pMDU->mvprint( 5, 15, "3" );
		pMDU->mvprint( 12, 15, "12" );
		pMDU->mvprint( 5, 16, "1" );
		pMDU->mvprint( 12, 16, "13" );
		pMDU->mvprint( 4, 17, "L2" );
		pMDU->mvprint( 12, 17, "14" );
		pMDU->mvprint( 0, 18, "RUD  3" );
		pMDU->mvprint( 12, 18, "15" );
		pMDU->mvprint( 0, 19, "PED  1" );
		pMDU->mvprint( 12, 19, "16" );
		pMDU->mvprint( 4, 20, "R2" );
		pMDU->mvprint( 12, 20, "17" );
		pMDU->mvprint( 5, 21, "3" );
		pMDU->mvprint( 12, 21, "18" );

		pMDU->mvprint( 19, 6, "BDY FLP" );
		pMDU->mvprint( 21, 7, "UPDNDES" );
		pMDU->mvprint( 19, 8, "L1" );
		pMDU->mvprint( 25, 8, "19" );
		pMDU->mvprint( 16, 9, "SW  2" );
		pMDU->mvprint( 25, 9, "20" );
		pMDU->mvprint( 19, 10, "R1" );
		pMDU->mvprint( 25, 10, "21" );
		pMDU->mvprint( 20, 11, "2" );
		pMDU->mvprint( 25, 11, "22" );

		pMDU->mvprint( 37, 3, "R" );
		pMDU->mvprint( 41, 3, "P" );
		pMDU->mvprint( 45, 3, "Y  DES" );
		pMDU->mvprint( 35, 4, "1" );
		pMDU->mvprint( 48, 4, "23" );
		pMDU->mvprint( 34, 5, "L2" );
		pMDU->mvprint( 48, 5, "24" );
		pMDU->mvprint( 35, 6, "3" );
		pMDU->mvprint( 48, 6, "25" );
		pMDU->mvprint( 35, 7, "1" );
		pMDU->mvprint( 48, 7, "26" );
		pMDU->mvprint( 29, 8, "RHC  R2" );
		pMDU->mvprint( 48, 8, "27" );
		pMDU->mvprint( 35, 9, "3" );
		pMDU->mvprint( 48, 9, "28" );
		pMDU->mvprint( 35, 10, "1" );
		pMDU->mvprint( 48, 10, "29" );
		pMDU->mvprint( 34, 11, "A2" );
		pMDU->mvprint( 48, 11, "30" );
		pMDU->mvprint( 35, 12, "3" );
		pMDU->mvprint( 48, 12, "31" );
		pMDU->mvprint( 34, 13, "L1" );
		pMDU->mvprint( 48, 13, "32" );
		pMDU->mvprint( 29, 14, "RHC   2" );
		pMDU->mvprint( 48, 14, "33" );
		pMDU->mvprint( 29, 15, "TRIM R1" );
		pMDU->mvprint( 48, 15, "34" );
		pMDU->mvprint( 35, 16, "2" );
		pMDU->mvprint( 48, 16, "35" );
		pMDU->mvprint( 34, 17, "L1" );
		pMDU->mvprint( 48, 17, "36" );
		pMDU->mvprint( 29, 18, "PNL   2" );
		pMDU->mvprint( 48, 18, "37" );
		pMDU->mvprint( 29, 19, "TRIM R1" );
		pMDU->mvprint( 48, 19, "38" );
		pMDU->mvprint( 35, 20, "2" );
		pMDU->mvprint( 48, 20, "39" );

		// static parts (lines)
		pMDU->Line( 0, 56, 150, 56 );
		pMDU->Line( 40, 98, 150, 98 );
		pMDU->Line( 0, 140, 150, 140 );
		pMDU->Line( 40, 182, 150, 182 );
		pMDU->Line( 0, 224, 150, 224 );
		pMDU->Line( 40, 266, 150, 266 );
		pMDU->Line( 60, 42, 60, 308 );
		pMDU->Line( 80, 42, 80, 140 );
		pMDU->Line( 100, 42, 100, 140 );
		pMDU->Line( 120, 42, 120, 308 );

		pMDU->Line( 160, 112, 280, 112 );
		pMDU->Line( 190, 140, 280, 140 );
		pMDU->Line( 210, 98, 210, 168 );
		pMDU->Line( 230, 98, 230, 168 );
		pMDU->Line( 250, 98, 250, 168 );

		pMDU->Line( 290, 56, 510, 56 );
		pMDU->Line( 350, 98, 510, 98 );
		pMDU->Line( 340, 140, 510, 140 );
		pMDU->Line( 290, 182, 510, 182 );
		pMDU->Line( 340, 210, 510, 210 );
		pMDU->Line( 290, 238, 510, 238 );
		pMDU->Line( 340, 266, 510, 266 );
		pMDU->Line( 360, 42, 360, 294 );
		pMDU->Line( 400, 42, 400, 294 );
		pMDU->Line( 440, 42, 440, 294 );
		pMDU->Line( 480, 42, 480, 294 );

		// dynamic parts
		unsigned short FF1_IOM6_CH0 = ReadCOMPOOL_IS( SCP_FF1_IOM6_CH0_DATA );
		unsigned short FF1_IOM15_CH0 = ReadCOMPOOL_IS( SCP_FF1_IOM15_CH0_DATA );
		unsigned short FF2_IOM6_CH0 = ReadCOMPOOL_IS( SCP_FF2_IOM6_CH0_DATA );
		unsigned short FF2_IOM15_CH0 = ReadCOMPOOL_IS( SCP_FF2_IOM15_CH0_DATA );
		unsigned short FF3_IOM6_CH0 = ReadCOMPOOL_IS( SCP_FF3_IOM6_CH0_DATA );
		unsigned short FF3_IOM15_CH0 = ReadCOMPOOL_IS( SCP_FF3_IOM15_CH0_DATA );

		bool FWD_THC_POS_X_OUTPUT_A = ((FF1_IOM6_CH0 & 0x0080) != 0);
		bool FWD_THC_NEG_X_OUTPUT_A = ((FF1_IOM6_CH0 & 0x0100) != 0);
		SPEC25_SPEC43_printTHC( pMDU, FWD_THC_POS_X_OUTPUT_A, FWD_THC_NEG_X_OUTPUT_A, 6, 4 );
		bool FWD_THC_POS_X_OUTPUT_B = ((FF2_IOM6_CH0 & 0x0080) != 0);
		bool FWD_THC_NEG_X_OUTPUT_B = ((FF2_IOM6_CH0 & 0x0100) != 0);
		SPEC25_SPEC43_printTHC( pMDU, FWD_THC_POS_X_OUTPUT_B, FWD_THC_NEG_X_OUTPUT_B, 6, 5 );
		bool FWD_THC_POS_X_OUTPUT_C = ((FF3_IOM6_CH0 & 0x0080) != 0);
		bool FWD_THC_NEG_X_OUTPUT_C = ((FF3_IOM6_CH0 & 0x0100) != 0);
		SPEC25_SPEC43_printTHC( pMDU, FWD_THC_POS_X_OUTPUT_C, FWD_THC_NEG_X_OUTPUT_C, 6, 6 );
		bool FWD_THC_POS_Y_OUTPUT_A = ((FF1_IOM6_CH0 & 0x0200) != 0);
		bool FWD_THC_NEG_Y_OUTPUT_A = ((FF1_IOM6_CH0 & 0x0400) != 0);
		SPEC25_SPEC43_printTHC( pMDU, FWD_THC_POS_Y_OUTPUT_A, FWD_THC_NEG_Y_OUTPUT_A, 8, 4 );
		bool FWD_THC_POS_Y_OUTPUT_B = ((FF2_IOM6_CH0 & 0x0200) != 0);
		bool FWD_THC_NEG_Y_OUTPUT_B = ((FF2_IOM6_CH0 & 0x0400) != 0);
		SPEC25_SPEC43_printTHC( pMDU, FWD_THC_POS_Y_OUTPUT_B, FWD_THC_NEG_Y_OUTPUT_B, 8, 5 );
		bool FWD_THC_POS_Y_OUTPUT_C = ((FF3_IOM6_CH0 & 0x0200) != 0);
		bool FWD_THC_NEG_Y_OUTPUT_C = ((FF3_IOM6_CH0 & 0x0400) != 0);
		SPEC25_SPEC43_printTHC( pMDU, FWD_THC_POS_Y_OUTPUT_C, FWD_THC_NEG_Y_OUTPUT_C, 8, 6 );
		bool FWD_THC_POS_Z_OUTPUT_A = ((FF1_IOM6_CH0 & 0x0800) != 0);
		bool FWD_THC_NEG_Z_OUTPUT_A = ((FF1_IOM6_CH0 & 0x1000) != 0);
		SPEC25_SPEC43_printTHC( pMDU, FWD_THC_POS_Z_OUTPUT_A, FWD_THC_NEG_Z_OUTPUT_A, 10, 4 );
		bool FWD_THC_POS_Z_OUTPUT_B = ((FF2_IOM6_CH0 & 0x0800) != 0);
		bool FWD_THC_NEG_Z_OUTPUT_B = ((FF2_IOM6_CH0 & 0x1000) != 0);
		SPEC25_SPEC43_printTHC( pMDU, FWD_THC_POS_Z_OUTPUT_B, FWD_THC_NEG_Z_OUTPUT_B, 10, 5 );
		bool FWD_THC_POS_Z_OUTPUT_C = ((FF3_IOM6_CH0 & 0x0800) != 0);
		bool FWD_THC_NEG_Z_OUTPUT_C = ((FF3_IOM6_CH0 & 0x1000) != 0);
		SPEC25_SPEC43_printTHC( pMDU, FWD_THC_POS_Z_OUTPUT_C, FWD_THC_NEG_Z_OUTPUT_C, 10, 6 );

		bool AFT_THC_POS_X_OUTPUT_A = ((FF1_IOM15_CH0 & 0x0080) != 0);
		bool AFT_THC_NEG_X_OUTPUT_A = ((FF1_IOM15_CH0 & 0x0100) != 0);
		SPEC25_SPEC43_printTHC( pMDU, AFT_THC_POS_X_OUTPUT_A, AFT_THC_NEG_X_OUTPUT_A, 6, 7 );
		bool AFT_THC_POS_X_OUTPUT_B = ((FF2_IOM15_CH0 & 0x0080) != 0);
		bool AFT_THC_NEG_X_OUTPUT_B = ((FF2_IOM15_CH0 & 0x0100) != 0);
		SPEC25_SPEC43_printTHC( pMDU, AFT_THC_POS_X_OUTPUT_B, AFT_THC_NEG_X_OUTPUT_B, 6, 8 );
		bool AFT_THC_POS_X_OUTPUT_C = ((FF3_IOM15_CH0 & 0x0080) != 0);
		bool AFT_THC_NEG_X_OUTPUT_C = ((FF3_IOM15_CH0 & 0x0100) != 0);
		SPEC25_SPEC43_printTHC( pMDU, AFT_THC_POS_X_OUTPUT_C, AFT_THC_NEG_X_OUTPUT_C, 6, 9 );
		bool AFT_THC_POS_Y_OUTPUT_A = ((FF1_IOM15_CH0 & 0x0200) != 0);
		bool AFT_THC_NEG_Y_OUTPUT_A = ((FF1_IOM15_CH0 & 0x0400) != 0);
		SPEC25_SPEC43_printTHC( pMDU, AFT_THC_POS_Y_OUTPUT_A, AFT_THC_NEG_Y_OUTPUT_A, 8, 7 );
		bool AFT_THC_POS_Y_OUTPUT_B = ((FF2_IOM15_CH0 & 0x0200) != 0);
		bool AFT_THC_NEG_Y_OUTPUT_B = ((FF2_IOM15_CH0 & 0x0400) != 0);
		SPEC25_SPEC43_printTHC( pMDU, AFT_THC_POS_Y_OUTPUT_B, AFT_THC_NEG_Y_OUTPUT_B, 8, 8 );
		bool AFT_THC_POS_Y_OUTPUT_C = ((FF3_IOM15_CH0 & 0x0200) != 0);
		bool AFT_THC_NEG_Y_OUTPUT_C = ((FF3_IOM15_CH0 & 0x0400) != 0);
		SPEC25_SPEC43_printTHC( pMDU, AFT_THC_POS_Y_OUTPUT_C, AFT_THC_NEG_Y_OUTPUT_C, 8, 9 );
		bool AFT_THC_POS_Z_OUTPUT_A = ((FF1_IOM15_CH0 & 0x0800) != 0);
		bool AFT_THC_NEG_Z_OUTPUT_A = ((FF1_IOM15_CH0 & 0x1000) != 0);
		SPEC25_SPEC43_printTHC( pMDU, AFT_THC_POS_Z_OUTPUT_A, AFT_THC_NEG_Z_OUTPUT_A, 10, 7 );
		bool AFT_THC_POS_Z_OUTPUT_B = ((FF2_IOM15_CH0 & 0x0800) != 0);
		bool AFT_THC_NEG_Z_OUTPUT_B = ((FF2_IOM15_CH0 & 0x1000) != 0);
		SPEC25_SPEC43_printTHC( pMDU, AFT_THC_POS_Z_OUTPUT_B, AFT_THC_NEG_Z_OUTPUT_B, 10, 8 );
		bool AFT_THC_POS_Z_OUTPUT_C = ((FF3_IOM15_CH0 & 0x0800) != 0);
		bool AFT_THC_NEG_Z_OUTPUT_C = ((FF3_IOM15_CH0 & 0x1000) != 0);
		SPEC25_SPEC43_printTHC( pMDU, AFT_THC_POS_Z_OUTPUT_C, AFT_THC_NEG_Z_OUTPUT_C, 10, 9 );

		SPEC25_SPEC43_printRHC_RY( pMDU, LeftRHC[3].GetVoltage(), 36, 4 );
		SPEC25_SPEC43_printRHC_RY( pMDU, LeftRHC[4].GetVoltage(), 36, 5 );
		SPEC25_SPEC43_printRHC_RY( pMDU, LeftRHC[5].GetVoltage(), 36, 6 );
		SPEC25_SPEC43_printRHC_P( pMDU, LeftRHC[0].GetVoltage(), 40, 4 );
		SPEC25_SPEC43_printRHC_P( pMDU, LeftRHC[1].GetVoltage(), 40, 5 );
		SPEC25_SPEC43_printRHC_P( pMDU, LeftRHC[2].GetVoltage(), 40, 6 );
		SPEC25_SPEC43_printRHC_RY( pMDU, LeftRHC[6].GetVoltage(), 44, 4 );
		SPEC25_SPEC43_printRHC_RY( pMDU, LeftRHC[7].GetVoltage(), 44, 5 );
		SPEC25_SPEC43_printRHC_RY( pMDU, LeftRHC[8].GetVoltage(), 44, 6 );

		SPEC25_SPEC43_printRHC_RY( pMDU, RightRHC[3].GetVoltage(), 36, 7 );
		SPEC25_SPEC43_printRHC_RY( pMDU, RightRHC[4].GetVoltage(), 36, 8 );
		SPEC25_SPEC43_printRHC_RY( pMDU, RightRHC[5].GetVoltage(), 36, 9 );
		SPEC25_SPEC43_printRHC_P( pMDU, RightRHC[0].GetVoltage(), 40, 7 );
		SPEC25_SPEC43_printRHC_P( pMDU, RightRHC[1].GetVoltage(), 40, 8 );
		SPEC25_SPEC43_printRHC_P( pMDU, RightRHC[2].GetVoltage(), 40, 9 );
		SPEC25_SPEC43_printRHC_RY( pMDU, RightRHC[6].GetVoltage(), 44, 7 );
		SPEC25_SPEC43_printRHC_RY( pMDU, RightRHC[7].GetVoltage(), 44, 8 );
		SPEC25_SPEC43_printRHC_RY( pMDU, RightRHC[8].GetVoltage(), 44, 9 );

		SPEC25_SPEC43_printRHC_RY( pMDU, AftRHC[3].GetVoltage(), 36, 10 );
		SPEC25_SPEC43_printRHC_RY( pMDU, AftRHC[4].GetVoltage(), 36, 11 );
		SPEC25_SPEC43_printRHC_RY( pMDU, AftRHC[5].GetVoltage(), 36, 12 );
		SPEC25_SPEC43_printRHC_P( pMDU, AftRHC[0].GetVoltage(), 40, 10 );
		SPEC25_SPEC43_printRHC_P( pMDU, AftRHC[1].GetVoltage(), 40, 11 );
		SPEC25_SPEC43_printRHC_P( pMDU, AftRHC[2].GetVoltage(), 40, 12 );
		SPEC25_SPEC43_printRHC_RY( pMDU, AftRHC[6].GetVoltage(), 44, 10 );
		SPEC25_SPEC43_printRHC_RY( pMDU, AftRHC[7].GetVoltage(), 44, 11 );
		SPEC25_SPEC43_printRHC_RY( pMDU, AftRHC[8].GetVoltage(), 44, 12 );

		char cbuf[8];
		sprintf_s( cbuf, 8, "%03.0f", LeftSBTC[0].GetVoltage() * 100 );
		pMDU->mvprint( 7, 10, cbuf );
		sprintf_s( cbuf, 8, "%03.0f", LeftSBTC[1].GetVoltage() * 100 );
		pMDU->mvprint( 7, 11, cbuf );
		sprintf_s( cbuf, 8, "%03.0f", LeftSBTC[2].GetVoltage() * 100 );
		pMDU->mvprint( 7, 12, cbuf );
		sprintf_s( cbuf, 8, "%03.0f", RightSBTC[0].GetVoltage() * 100 );
		pMDU->mvprint( 7, 13, cbuf );
		sprintf_s( cbuf, 8, "%03.0f", RightSBTC[1].GetVoltage() * 100 );
		pMDU->mvprint( 7, 14, cbuf );
		sprintf_s( cbuf, 8, "%03.0f", RightSBTC[2].GetVoltage() * 100 );
		pMDU->mvprint( 7, 15, cbuf );

		SPEC43_printRPTA( pMDU, LeftRPTA[0].GetVoltage(), 6, 16 );
		SPEC43_printRPTA( pMDU, LeftRPTA[1].GetVoltage(), 6, 17 );
		SPEC43_printRPTA( pMDU, LeftRPTA[2].GetVoltage(), 6, 18 );
		SPEC43_printRPTA( pMDU, RightRPTA[0].GetVoltage(), 6, 19 );
		SPEC43_printRPTA( pMDU, RightRPTA[1].GetVoltage(), 6, 20 );
		SPEC43_printRPTA( pMDU, RightRPTA[2].GetVoltage(), 6, 21 );


		unsigned short FF1_IOM4_CH0 = ReadCOMPOOL_IS( SCP_FF1_IOM4_CH0_DATA );
		unsigned short FF2_IOM4_CH0 = ReadCOMPOOL_IS( SCP_FF2_IOM4_CH0_DATA );
		unsigned short FF3_IOM4_CH0 = ReadCOMPOOL_IS( SCP_FF3_IOM4_CH0_DATA );
		unsigned short FF4_IOM4_CH0 = ReadCOMPOOL_IS( SCP_FF4_IOM4_CH0_DATA );

		bool LH_BODY_FLAP_UP_A = (FF1_IOM4_CH0 & 0x0008) >> 3;
		if (LH_BODY_FLAP_UP_A) pMDU->mvprint( 21, 8, "*" );

		bool LH_BODY_FLAP_UP_B = (FF2_IOM4_CH0 & 0x0008) >> 3;
		if (LH_BODY_FLAP_UP_B) pMDU->mvprint( 21, 9, "*" );

		bool LH_BODY_FLAP_DOWN_A = (FF1_IOM4_CH0 & 0x0010) >> 4;
		if (LH_BODY_FLAP_DOWN_A) pMDU->mvprint( 23, 8, "*" );

		bool LH_BODY_FLAP_DOWN_B = (FF2_IOM4_CH0 & 0x0010) >> 4;
		if (LH_BODY_FLAP_DOWN_B) pMDU->mvprint( 23, 9, "*" );

		bool RH_BODY_FLAP_UP_A = (FF3_IOM4_CH0 & 0x0008) >> 3;
		if (RH_BODY_FLAP_UP_A) pMDU->mvprint( 21, 10, "*" );

		bool RH_BODY_FLAP_UP_B = (FF4_IOM4_CH0 & 0x0008) >> 3;
		if (RH_BODY_FLAP_UP_B) pMDU->mvprint( 21, 11, "*" );

		bool RH_BODY_FLAP_DOWN_A = (FF3_IOM4_CH0 & 0x0010) >> 4;
		if (RH_BODY_FLAP_DOWN_A) pMDU->mvprint( 23, 10, "*" );

		bool RH_BODY_FLAP_DOWN_B = (FF4_IOM4_CH0 & 0x0010) >> 4;
		if (RH_BODY_FLAP_DOWN_B) pMDU->mvprint( 23, 11, "*" );


		unsigned short FF1_IOM6_CH1 = ReadCOMPOOL_IS( SCP_FF1_IOM6_CH1_DATA );
		unsigned short FF2_IOM6_CH1 = ReadCOMPOOL_IS( SCP_FF2_IOM6_CH1_DATA );
		unsigned short FF3_IOM15_CH1 = ReadCOMPOOL_IS( SCP_FF3_IOM15_CH1_DATA );
		unsigned short FF4_IOM15_CH1 = ReadCOMPOOL_IS( SCP_FF4_IOM15_CH1_DATA );
		unsigned short FF1_IOM12_CH0 = ReadCOMPOOL_IS( SCP_FF1_IOM12_CH0_DATA );
		unsigned short FF2_IOM12_CH0 = ReadCOMPOOL_IS( SCP_FF2_IOM12_CH0_DATA );
		unsigned short FF3_IOM12_CH0 = ReadCOMPOOL_IS( SCP_FF3_IOM12_CH0_DATA );
		unsigned short FF4_IOM12_CH0 = ReadCOMPOOL_IS( SCP_FF4_IOM12_CH0_DATA );

		bool LH_RHC_PLUS_PITCH_TRIM_A = (FF1_IOM6_CH1 & 0x0002) >> 1;
		bool LH_RHC_MINUS_PITCH_TRIM_A = (FF1_IOM6_CH1 & 0x0004) >> 2;
		if (LH_RHC_PLUS_PITCH_TRIM_A && !LH_RHC_MINUS_PITCH_TRIM_A) pMDU->mvprint( 42, 13, "U" );
		else if (!LH_RHC_PLUS_PITCH_TRIM_A && LH_RHC_MINUS_PITCH_TRIM_A) pMDU->mvprint( 42, 13, "D" );

		bool LH_RHC_PLUS_PITCH_TRIM_B = (FF2_IOM6_CH1 & 0x0002) >> 1;
		bool LH_RHC_MINUS_PITCH_TRIM_B = (FF2_IOM6_CH1 & 0x0004) >> 2;
		if (LH_RHC_PLUS_PITCH_TRIM_B && !LH_RHC_MINUS_PITCH_TRIM_B) pMDU->mvprint( 42, 14, "U" );
		else if (!LH_RHC_PLUS_PITCH_TRIM_B && LH_RHC_MINUS_PITCH_TRIM_B) pMDU->mvprint( 42, 14, "D" );

		bool LH_RHC_PLUS_ROLL_TRIM_A = (FF1_IOM6_CH1 & 0x0008) >> 3;
		bool LH_RHC_MINUS_ROLL_TRIM_A = (FF1_IOM6_CH1 & 0x0010) >> 4;
		if (LH_RHC_PLUS_ROLL_TRIM_A && !LH_RHC_MINUS_ROLL_TRIM_A) pMDU->mvprint( 38, 13, "R" );
		else if (!LH_RHC_PLUS_ROLL_TRIM_A && LH_RHC_MINUS_ROLL_TRIM_A) pMDU->mvprint( 38, 13, "L" );

		bool LH_RHC_PLUS_ROLL_TRIM_B = (FF2_IOM6_CH1 & 0x0008) >> 3;
		bool LH_RHC_MINUS_ROLL_TRIM_B = (FF2_IOM6_CH1 & 0x0010) >> 4;
		if (LH_RHC_PLUS_ROLL_TRIM_B && !LH_RHC_MINUS_ROLL_TRIM_B) pMDU->mvprint( 38, 14, "R" );
		else if (!LH_RHC_PLUS_ROLL_TRIM_B && LH_RHC_MINUS_ROLL_TRIM_B) pMDU->mvprint( 38, 14, "L" );

		bool RH_RHC_PLUS_PITCH_TRIM_A = (FF3_IOM15_CH1 & 0x0002) >> 1;
		bool RH_RHC_MINUS_PITCH_TRIM_A = (FF3_IOM15_CH1 & 0x0004) >> 2;
		if (RH_RHC_PLUS_PITCH_TRIM_A && !RH_RHC_MINUS_PITCH_TRIM_A) pMDU->mvprint( 42, 15, "U" );
		else if (!RH_RHC_PLUS_PITCH_TRIM_A && RH_RHC_MINUS_PITCH_TRIM_A) pMDU->mvprint( 42, 15, "D" );

		bool RH_RHC_PLUS_PITCH_TRIM_B = (FF4_IOM15_CH1 & 0x0002) >> 1;
		bool RH_RHC_MINUS_PITCH_TRIM_B = (FF4_IOM15_CH1 & 0x0004) >> 2;
		if (RH_RHC_PLUS_PITCH_TRIM_B && !RH_RHC_MINUS_PITCH_TRIM_B) pMDU->mvprint( 42, 16, "U" );
		else if (!RH_RHC_PLUS_PITCH_TRIM_B && RH_RHC_MINUS_PITCH_TRIM_B) pMDU->mvprint( 42, 16, "D" );

		bool RH_RHC_PLUS_ROLL_TRIM_A = (FF3_IOM15_CH1 & 0x0008) >> 3;
		bool RH_RHC_MINUS_ROLL_TRIM_A = (FF3_IOM15_CH1 & 0x0010) >> 4;
		if (RH_RHC_PLUS_ROLL_TRIM_A && !RH_RHC_MINUS_ROLL_TRIM_A) pMDU->mvprint( 38, 15, "R" );
		else if (!RH_RHC_PLUS_ROLL_TRIM_A && RH_RHC_MINUS_ROLL_TRIM_A) pMDU->mvprint( 38, 15, "L" );

		bool RH_RHC_PLUS_ROLL_TRIM_B = (FF4_IOM15_CH1 & 0x0008) >> 3;
		bool RH_RHC_MINUS_ROLL_TRIM_B = (FF4_IOM15_CH1 & 0x0010) >> 4;
		if (RH_RHC_PLUS_ROLL_TRIM_B && !RH_RHC_MINUS_ROLL_TRIM_B) pMDU->mvprint( 38, 16, "R" );
		else if (!RH_RHC_PLUS_ROLL_TRIM_B && RH_RHC_MINUS_ROLL_TRIM_B) pMDU->mvprint( 38, 16, "L" );


		bool LH_PLUS_ROLL_TRIM_A = (FF1_IOM12_CH0 & 0x0008) >> 3;
		bool LH_MINUS_ROLL_TRIM_A = (FF1_IOM12_CH0 & 0x0010) >> 4;
		if (LH_PLUS_ROLL_TRIM_A && !LH_MINUS_ROLL_TRIM_A) pMDU->mvprint( 38, 17, "R" );
		else if (!LH_PLUS_ROLL_TRIM_A && LH_MINUS_ROLL_TRIM_A) pMDU->mvprint( 38, 17, "L" );

		bool LH_PLUS_ROLL_TRIM_B = (FF2_IOM12_CH0 & 0x0008) >> 3;
		bool LH_MINUS_ROLL_TRIM_B = (FF2_IOM12_CH0 & 0x0010) >> 4;
		if (LH_PLUS_ROLL_TRIM_B && !LH_MINUS_ROLL_TRIM_B) pMDU->mvprint( 38, 18, "R" );
		else if (!LH_PLUS_ROLL_TRIM_B && LH_MINUS_ROLL_TRIM_B) pMDU->mvprint( 38, 18, "L" );

		bool LH_PLUS_PITCH_TRIM_A = (FF1_IOM12_CH0 & 0x0002) >> 1;
		bool LH_MINUS_PITCH_TRIM_A = (FF1_IOM12_CH0 & 0x0004) >> 2;
		if (LH_PLUS_PITCH_TRIM_A && !LH_MINUS_PITCH_TRIM_A) pMDU->mvprint( 42, 17, "U" );
		else if (!LH_PLUS_PITCH_TRIM_A && LH_MINUS_PITCH_TRIM_A) pMDU->mvprint( 42, 17, "D" );

		bool LH_PLUS_PITCH_TRIM_B = (FF2_IOM12_CH0 & 0x0002) >> 1;
		bool LH_MINUS_PITCH_TRIM_B = (FF2_IOM12_CH0 & 0x0004) >> 2;
		if (LH_PLUS_PITCH_TRIM_B && !LH_MINUS_PITCH_TRIM_B) pMDU->mvprint( 42, 18, "U" );
		else if (!LH_PLUS_PITCH_TRIM_B && LH_MINUS_PITCH_TRIM_B) pMDU->mvprint( 42, 18, "D" );

		bool LH_PLUS_YAW_TRIM_A = (FF1_IOM12_CH0 & 0x0020) >> 5;
		bool LH_MINUS_YAW_TRIM_A = (FF1_IOM12_CH0 & 0x0040) >> 6;
		if (LH_PLUS_YAW_TRIM_A && !LH_MINUS_YAW_TRIM_A) pMDU->mvprint( 46, 17, "R" );
		else if (!LH_PLUS_YAW_TRIM_A && LH_MINUS_YAW_TRIM_A) pMDU->mvprint( 46, 17, "L" );

		bool LH_PLUS_YAW_TRIM_B = (FF2_IOM12_CH0 & 0x0020) >> 5;
		bool LH_MINUS_YAW_TRIM_B = (FF2_IOM12_CH0 & 0x0040) >> 6;
		if (LH_PLUS_YAW_TRIM_B && !LH_MINUS_YAW_TRIM_B) pMDU->mvprint( 46, 18, "R" );
		else if (!LH_PLUS_YAW_TRIM_B && LH_MINUS_YAW_TRIM_B) pMDU->mvprint( 46, 18, "L" );

		bool RH_PLUS_ROLL_TRIM_A = (FF3_IOM12_CH0 & 0x0008) >> 3;
		bool RH_MINUS_ROLL_TRIM_A = (FF3_IOM12_CH0 & 0x0010) >> 4;
		if (RH_PLUS_ROLL_TRIM_A && !RH_MINUS_ROLL_TRIM_A) pMDU->mvprint( 38, 19, "R" );
		else if (!RH_PLUS_ROLL_TRIM_A && RH_MINUS_ROLL_TRIM_A) pMDU->mvprint( 38, 19, "L" );

		bool RH_PLUS_ROLL_TRIM_B = (FF4_IOM12_CH0 & 0x0008) >> 3;
		bool RH_MINUS_ROLL_TRIM_B = (FF4_IOM12_CH0 & 0x0010) >> 4;
		if (RH_PLUS_ROLL_TRIM_B && !RH_MINUS_ROLL_TRIM_B) pMDU->mvprint( 38, 20, "R" );
		else if (!RH_PLUS_ROLL_TRIM_B && RH_MINUS_ROLL_TRIM_B) pMDU->mvprint( 38, 20, "L" );

		bool RH_PLUS_PITCH_TRIM_A = (FF3_IOM12_CH0 & 0x0002) >> 1;
		bool RH_MINUS_PITCH_TRIM_A = (FF3_IOM12_CH0 & 0x0004) >> 2;
		if (RH_PLUS_PITCH_TRIM_A && !RH_MINUS_PITCH_TRIM_A) pMDU->mvprint( 42, 19, "U" );
		else if (!RH_PLUS_PITCH_TRIM_A && RH_MINUS_PITCH_TRIM_A) pMDU->mvprint( 42, 19, "D" );

		bool RH_PLUS_PITCH_TRIM_B = (FF4_IOM12_CH0 & 0x0002) >> 1;
		bool RH_MINUS_PITCH_TRIM_B = (FF4_IOM12_CH0 & 0x0004) >> 2;
		if (RH_PLUS_PITCH_TRIM_B && !RH_MINUS_PITCH_TRIM_B) pMDU->mvprint( 42, 20, "U" );
		else if (!RH_PLUS_PITCH_TRIM_B && RH_MINUS_PITCH_TRIM_B) pMDU->mvprint( 42, 20, "D" );

		bool RH_PLUS_YAW_TRIM_A = (FF3_IOM12_CH0 & 0x0020) >> 5;
		bool RH_MINUS_YAW_TRIM_A = (FF3_IOM12_CH0 & 0x0040) >> 6;
		if (RH_PLUS_YAW_TRIM_A && !RH_MINUS_YAW_TRIM_A) pMDU->mvprint( 46, 19, "R" );
		else if (!RH_PLUS_YAW_TRIM_A && RH_MINUS_YAW_TRIM_A) pMDU->mvprint( 46, 19, "L" );

		bool RH_PLUS_YAW_TRIM_B = (FF4_IOM12_CH0 & 0x0020) >> 5;
		bool RH_MINUS_YAW_TRIM_B = (FF4_IOM12_CH0 & 0x0040) >> 6;
		if (RH_PLUS_YAW_TRIM_B && !RH_MINUS_YAW_TRIM_B) pMDU->mvprint( 46, 20, "R" );
		else if (!RH_PLUS_YAW_TRIM_B && RH_MINUS_YAW_TRIM_B) pMDU->mvprint( 46, 20, "L" );
		return;
	}

	void GeneralDisplays::SPEC43_printRPTA( vc::MDU* pMDU, double val, int x, int y ) const
	{
		char cbuf[16];
		int itmp = 0;
		char ctmp = 0;

		itmp = (int)fabs( val * 100 );
		if (val > 0) ctmp = 'R';
		else if (val < 0) ctmp = 'L';
		else ctmp = ' ';
		sprintf_s( cbuf, 16, "%c%03d", ctmp, itmp );
		pMDU->mvprint( x, y, cbuf );
		return;
	}

	void GeneralDisplays::OnPaint_SPEC44_PASS( vc::MDU* pMDU ) const
	{
		PrintCommonHeader( "    SWITCHES", pMDU );

		// static parts (labels)
		pMDU->mvprint( 29, 3, "ENTRY ROLL MODE" );
		pMDU->mvprint( 31, 4, "LOW" );
		pMDU->mvprint( 36, 4, "NO" );
		pMDU->mvprint( 31, 5, "GAIN Y/J DES" );
		pMDU->mvprint( 29, 6, "1" );
		pMDU->mvprint( 29, 7, "2" );
		pMDU->mvprint( 29, 8, "3" );
		pMDU->mvprint( 29, 9, "4" );
		pMDU->mvprint( 41, 6, "1" );
		pMDU->mvprint( 41, 7, "2" );
		pMDU->mvprint( 41, 8, "3" );
		pMDU->mvprint( 41, 9, "4" );

		// static parts (lines)
		pMDU->Line( 310, 56, 310, 140 );
		pMDU->Line( 360, 56, 360, 140 );
		pMDU->Line( 400, 56, 400, 140 );
		pMDU->Line( 290, 84, 430, 84 );

		// dynamic parts
		unsigned short FF1_IOM4_CH2 = ReadCOMPOOL_IS( SCP_FF1_IOM4_CH2_DATA );
		unsigned short FF1_IOM9_CH1 = ReadCOMPOOL_IS( SCP_FF1_IOM9_CH1_DATA );
		unsigned short FF2_IOM4_CH0 = ReadCOMPOOL_IS( SCP_FF2_IOM4_CH0_DATA );
		unsigned short FF2_IOM9_CH1 = ReadCOMPOOL_IS( SCP_FF2_IOM9_CH1_DATA );
		unsigned short FF3_IOM9_CH1 = ReadCOMPOOL_IS( SCP_FF3_IOM9_CH1_DATA );
		unsigned short FF3_IOM12_CH1 = ReadCOMPOOL_IS( SCP_FF3_IOM12_CH1_DATA );
		unsigned short FF4_IOM9_CH1 = ReadCOMPOOL_IS( SCP_FF4_IOM9_CH1_DATA );
		unsigned short FF4_IOM12_CH2 = ReadCOMPOOL_IS( SCP_FF4_IOM12_CH2_DATA );

		bool ENTRY_ROLL_MODE_NO_Y_JET_A = ((FF1_IOM4_CH2 & 0x0008) != 0);
		bool ENTRY_ROLL_MODE_NO_Y_JET_B = ((FF2_IOM4_CH0 & 0x0004) != 0);
		bool ENTRY_ROLL_MODE_NO_Y_JET_C = ((FF3_IOM12_CH1 & 0x0004) != 0);
		bool ENTRY_ROLL_MODE_NO_Y_JET_D = ((FF4_IOM12_CH2 & 0x8000) != 0);
		bool ENTRY_ROLL_MODE_L_GAIN_A = ((FF1_IOM9_CH1 & 0x0008) != 0);
		bool ENTRY_ROLL_MODE_L_GAIN_B = ((FF2_IOM9_CH1 & 0x0008) != 0);
		bool ENTRY_ROLL_MODE_L_GAIN_C = ((FF3_IOM9_CH1 & 0x0008) != 0);
		bool ENTRY_ROLL_MODE_L_GAIN_D = ((FF4_IOM9_CH1 & 0x0008) != 0);
		if (ENTRY_ROLL_MODE_L_GAIN_A) pMDU->mvprint( 32, 6, "*" );
		if (ENTRY_ROLL_MODE_L_GAIN_B) pMDU->mvprint( 32, 7, "*" );
		if (ENTRY_ROLL_MODE_L_GAIN_C) pMDU->mvprint( 32, 8, "*" );
		if (ENTRY_ROLL_MODE_L_GAIN_D) pMDU->mvprint( 32, 9, "*" );
		if (ENTRY_ROLL_MODE_NO_Y_JET_A) pMDU->mvprint( 36, 6, "*" );
		if (ENTRY_ROLL_MODE_NO_Y_JET_B) pMDU->mvprint( 36, 7, "*" );
		if (ENTRY_ROLL_MODE_NO_Y_JET_C) pMDU->mvprint( 36, 8, "*" );
		if (ENTRY_ROLL_MODE_NO_Y_JET_D) pMDU->mvprint( 36, 9, "*" );
		return;
	}

	void GeneralDisplays::OnPaint_SPEC50_PASS( vc::MDU* pMDU ) const
	{
		char cbuf[51];
		unsigned short RWID = ReadCOMPOOL_IS( SCP_RWID );
		double YSGN = ReadCOMPOOL_SD( SCP_YSGN );
		PrintCommonHeader("    HORIZ SIT", pMDU);

		pMDU->mvprint( 0, 1, "PTI" );
		pMDU->mvprint( 10, 1, "1" );
		pMDU->mvprint( 1, 2, "INDEX" );
		pMDU->mvprint( 13, 1, "ALTM" );
		pMDU->mvprint( 13, 2, "9" );

		pMDU->mvprint(0, 5, "41 LAND SITE");
		sprintf_s(cbuf, 51, "%02d", ReadCOMPOOL_IS( SCP_LSID ) );
		pMDU->mvprint(13, 5, cbuf);
		pMDU->mvprint(0, 6, "PRI");
		ReadCOMPOOL_C( SCP_PRI_ID, cbuf, 5 );
		cbuf[5] = 0;
		pMDU->mvprint( 4, 6, cbuf );
		pMDU->mvprint(13, 6, "3");
		pMDU->mvprint(0, 7, "SEC");
		ReadCOMPOOL_C( SCP_SEC_ID, cbuf, 5 );
		cbuf[5] = 0;
		pMDU->mvprint( 4, 7, cbuf );
		pMDU->mvprint(13, 7, "4");
		if (RWID == 1) pMDU->mvprint(14, 6, "*");
		else pMDU->mvprint(14, 7, "*");
		pMDU->mvprint( 0, 8, "TAC" );
		pMDU->mvprint( 13, 8, "5" );
		pMDU->mvprint( 0, 9, "GPS FOM" );
		pMDU->mvprint( 13, 9, "RA" );
		pMDU->mvprint( 12, 10, "46" );

		pMDU->mvprint( 0, 11, "TAEM TGT" );
		pMDU->mvprint(0, 12, "G&N");
		if (ReadCOMPOOL_IS( SCP_OVHD ) == 1) pMDU->mvprint(6, 12, "OVHD 6");
		else pMDU->mvprint(6, 12, "STRT 6");
		if(GetMajorMode() >= 304)
		{
			if(YSGN < 0.0) {
				pMDU->mvprint(4, 12, "L");
				pMDU->mvprint(0, 13, "HSI L");
			}
			else {
				pMDU->mvprint(4, 12, "R");
				pMDU->mvprint(0, 13, "HSI R");
			}
		}
		if (ReadCOMPOOL_IS( SCP_MEP ) == 1) pMDU->mvprint( 0, 14, "MEP" );
		else pMDU->mvprint( 0, 14, "NEP" );
		pMDU->mvprint( 11, 14, "7" );
		pMDU->mvprint( 0, 15, "AIM" );
		pMDU->mvprint( 11, 15, "8" );
		if (ReadCOMPOOL_IS( SCP_IGI ) == 1) pMDU->mvprint( 6, 15, "NOM" );
		else pMDU->mvprint( 6, 15, "CLSE" );
		pMDU->mvprint( 0, 16, "S/B" );
		pMDU->mvprint( 11, 16, "39" );
		unsigned short SBControlLogic = ReadCOMPOOL_IS( SCP_SB_SEL );
		if (SBControlLogic == 1) pMDU->mvprint( 7, 16, "NOM" );
		else if (SBControlLogic == 2) pMDU->mvprint( 5, 16, "SHORT", dps::DEUATT_OVERBRIGHT );
		else pMDU->mvprint( 7, 16, "ELS", dps::DEUATT_OVERBRIGHT );

		pMDU->mvprint( 42, 2, "NAV DATA" );
		pMDU->Delta( 44, 3 );
		pMDU->mvprint( 45, 3, "X 10" );
		pMDU->Delta( 44, 5 );
		pMDU->mvprint( 45, 5, "Y 11" );
		pMDU->Delta( 44, 7 );
		pMDU->mvprint( 45, 7, "Z 12" );
		pMDU->Delta( 44, 9 );
		pMDU->mvprint( 45, 9, "X 13" );
		pMDU->DotCharacter( 45, 9 );
		pMDU->Delta( 44, 11 );
		pMDU->mvprint( 45, 11, "Y 14" );
		pMDU->DotCharacter( 45, 11 );
		pMDU->Delta( 44, 13 );
		pMDU->mvprint( 45, 13, "Z 15" );
		pMDU->DotCharacter( 45, 13 );
		pMDU->mvprint( 44, 15, "LOAD 16" );
		pMDU->mvprint( 39, 16, "18  T" );
		pMDU->Delta( 42, 16 );

		pMDU->mvprint( 0, 17, "NAV" );
		pMDU->mvprint( 0, 18, "TAC AZ" );
		pMDU->mvprint( 3, 19, "RNG" );
		pMDU->mvprint( 0, 20, "GPS" );
		pMDU->mvprint( 0, 21, "DRAG H" );
		pMDU->mvprint( 0, 22, "ADTA H" );
		pMDU->mvprint( 6, 17, "RESID" );
		pMDU->mvprint( 12, 17, "RATIO" );
		pMDU->mvprint( 17, 17, "AUT" );
		pMDU->mvprint( 17, 18, "19" );
		pMDU->mvprint( 17, 20, "42" );
		pMDU->mvprint( 17, 21, "22" );
		pMDU->mvprint( 17, 22, "25" );
		pMDU->mvprint( 20, 17, "INH" );
		pMDU->mvprint( 20, 18, "20" );
		pMDU->mvprint( 20, 20, "43" );
		pMDU->mvprint( 20, 21, "23" );
		pMDU->mvprint( 20, 22, "26" );
		pMDU->mvprint( 23, 17, "FOR" );
		pMDU->mvprint( 23, 18, "21" );
		pMDU->mvprint( 23, 20, "44" );
		pMDU->mvprint( 23, 21, "24" );
		pMDU->mvprint( 23, 22, "27" );
		pMDU->mvprint( 0, 23, "ADTA TO G&C" );
		pMDU->mvprint( 17, 23, "28" );
		pMDU->mvprint( 20, 23, "29" );
		pMDU->mvprint( 23, 23, "30" );
		pMDU->mvprint( 27, 17, "TAC 1" );
		pMDU->mvprint( 28, 20, "DES 31" );
		pMDU->mvprint( 35, 17, "TAC 2" );
		pMDU->mvprint( 36, 20, "DES 32" );
		pMDU->mvprint( 43, 17, "TAC 3" );
		pMDU->mvprint( 44, 20, "DES 33" );
		pMDU->mvprint( 28, 21, "ABS 34" );
		pMDU->mvprint( 36, 21, "DELTA 35" );
		pMDU->mvprint( 26, 22, "GPS S" );
		pMDU->mvprint( 32, 22, "RN" );
		pMDU->mvprint( 42, 22, "AZ" );
		pMDU->mvprint( 26, 23, "AIF_G S47" );
		pMDU->mvprint( 37, 23, "48" );
		pMDU->mvprint( 41, 23, "49" );
		if (0) pMDU->mvprint( 29, 15, "MLS", dps::DEUATT_OVERBRIGHT );// TODO

		const int BUG_POINT_X = 264;
		const int BUG_POINT_Y = 210;
		if (ReadCOMPOOL_SD( SCP_H ) < 200000.0)
		{
			double HAC_CENTER_Y = YSGN * ((GetMajorMode() == 304) ? ReadCOMPOOL_SD( SCP_RF0 ) : ReadCOMPOOL_SD( SCP_RF ));// only shrinks in TAEM
			double XHAC = ReadCOMPOOL_SD( SCP_XHAC );
			double RTURN = ReadCOMPOOL_SD( SCP_RTURN );

			VECTOR3 TgtPos;
			TgtPos.x = ReadCOMPOOL_SD( SCP_X );
			TgtPos.y = ReadCOMPOOL_SD( SCP_Y );

			// calculate angle between runway heading and vehicle heading
			double rwHdg;
			if (RWID == 1) rwHdg = ReadCOMPOOL_SD( SCP_PRI_HDG );
			else rwHdg = ReadCOMPOOL_SD( SCP_SEC_HDG );
			double degHeading = ReadCOMPOOL_SD( SCP_HDG );
			double degHeadingError = rwHdg - degHeading;
			while(degHeadingError < 0.0) degHeadingError+=360.0;
			while(degHeadingError > 360.0) degHeadingError-=360.0;

			// rotate runway coordinate to vehicle heading
			VECTOR3 TouchdownPos = RotateVectorZ( _V( TgtPos.x - ReadCOMPOOL_SD( SCP_X_AIM ), TgtPos.y, 0.0 ), degHeadingError );
			VECTOR3 HACExitPos = RotateVectorZ( _V( TgtPos.x - XHAC, TgtPos.y, 0.0 ), degHeadingError );

			// calculate scale factor for display
			double scale_distance;
			if (GetMajorMode() == 304) scale_distance = ReadCOMPOOL_SD( SCP_TRANG ) / FT2NM;
			else if (ReadCOMPOOL_IS( SCP_TG_END ) == 0) scale_distance = ReadCOMPOOL_SD( SCP_RPRED );
			else scale_distance = hypot( TgtPos.x, TgtPos.y );
			scale_distance = range( 30000.0, scale_distance, 360000.0 );// limit distance covered by display to range covered in TAEM
			double scale = 182.0 / scale_distance; // screen area is 512 pixels by 364 pixels (using 364 as limit) [px/ft]

			// draw A/L line
			int touchdown_x = BUG_POINT_X - Round( TouchdownPos.y * scale );
			int touchdown_y = BUG_POINT_Y + Round( TouchdownPos.x * scale );
			int hac_exit_x = BUG_POINT_X - Round( HACExitPos.y * scale );
			int hac_exit_y = BUG_POINT_Y + Round( HACExitPos.x * scale );
			pMDU->Circle( touchdown_x, touchdown_y, 5 );
			pMDU->Line( hac_exit_x, hac_exit_y, touchdown_x, touchdown_y );

			// draw HAC
			if (ReadCOMPOOL_IS( SCP_TG_END ) == 0)
			{
				VECTOR3 HACCenter = RotateVectorZ( _V( TgtPos.x - XHAC, TgtPos.y - HAC_CENTER_Y, 0.0 ), degHeadingError );
				int hac_center_x = BUG_POINT_X - Round( HACCenter.y * scale );
				int hac_center_y = BUG_POINT_Y + Round( HACCenter.x * scale );
				int hac_radius = Round( RTURN * scale );
				pMDU->Circle( hac_center_x, hac_center_y, hac_radius );
			}

			// draw position predictor circles
			// get speed and acceleration in LVLH-like frame
			VECTOR3 localForce;
			STS()->GetForceVector(localForce);
			VECTOR3 localAcceleration = localForce / (ReadCOMPOOL_SD( SCP_WEIGHT ) * LBM2KG / LBS2SL);
			VECTOR3 horizonAcceleration;
			STS()->HorizonRot(localAcceleration, horizonAcceleration);
			VECTOR3 groundAcceleration = RotateVectorZ(_V(-horizonAcceleration.z, -horizonAcceleration.x, 0), -degHeading);

			double HDOT = ReadCOMPOOL_SD( SCP_HDOT );
			double VE = ReadCOMPOOL_SD( SCP_VE );
			VECTOR3 groundVelocity = _V( -sqrt( (VE * VE) - (HDOT * HDOT) ) * FPS2MS, 0.0, 0.0 );// initial velocity is always along display's y axis

			// to calculate position in future, split acceleration into (constant magnitude) radial and tangential components and do numerical integration
			// assumes aerodynamic forces (lift/drag) are constant
			double radial_acc = -groundAcceleration.y;
			double tangential_acc = -groundAcceleration.x;
			VECTOR3 pos = _V(0, 0, 0);
			const double DELTA_T = 0.1;
			for (double time=DELTA_T;time<=60.1;time+=DELTA_T)
			{
				pos += groundVelocity*DELTA_T + groundAcceleration*(0.5*DELTA_T*DELTA_T);
				// calculate acceleration from radial and tangential components
				VECTOR3 norm_vel = groundVelocity/length(groundVelocity);
				groundAcceleration = crossp(norm_vel, _V(0, 0, -1))*radial_acc + norm_vel*tangential_acc;
				groundVelocity = groundVelocity + groundAcceleration*DELTA_T;

				if (Eq(time, 20, 0.01) || Eq(time, 40, 0.01) || Eq(time, 60, 0.01))
				{
					int pos_x = BUG_POINT_X - Round( pos.y * MPS2FPS * scale );
					int pos_y = BUG_POINT_Y + Round( pos.x * MPS2FPS * scale );
					pMDU->Circle(pos_x, pos_y, 5, dps::DEUATT_OVERBRIGHT);
				}
			}
		}

		// draw shuttle bug (this is always at fixed position)
		char att = 0;
		double NZ = (GetMajorMode() == 304) ? (ReadCOMPOOL_SD( SCP_XLFAC ) / (G * MPS2FPS)) : ReadCOMPOOL_SD( SCP_NZ );
		if ((NZ > 2.5) || (NZ < -1.0)) att = dps::DEUATT_FLASHING;// HACK limits are true most of the time, but not 100% accurate

		pMDU->OrbiterSymbolTop( BUG_POINT_X, BUG_POINT_Y, att );

		sprintf_s( cbuf, 51, "%3.1f", NZ );
		pMDU->mvprint( 21, 15, cbuf, att );

		// scales
		if (((GetMajorMode() == 305) || (GetMajorMode() == 603)) && (ReadCOMPOOL_SD( SCP_H ) > 7000.0))// blank under 7kft
		{
			// top scale
			pMDU->Line( 222, 50, 402, 50 );
			// side scale
			pMDU->Line( 418, 73, 418, 195 );
			pMDU->Line( 415, 73, 421, 73 );
			pMDU->Line( 415, 195, 421, 195 );
			pMDU->Line( 415, 104, 421, 104 );
			pMDU->Line( 415, 134, 421, 134 );
			pMDU->Line( 415, 165, 421, 165 );

			if ((ReadCOMPOOL_IS( SCP_IPHASE ) == 0) || (ReadCOMPOOL_IS( SCP_IPHASE ) == 1))
			{
				// ACQ
				// top scale
				att = 0;
				int pos;
				double TimeToHAC = ReadCOMPOOL_SD( SCP_P2TRNT ) * ReadCOMPOOL_SD( SCP_YSGN );
				double t2h = fabs( TimeToHAC );
				pMDU->Line( 222, 47, 222, 53 );
				pMDU->Line( 402, 47, 402, 53 );
				if (TimeToHAC < 0)
				{
					pMDU->mvprint( 21, 4, "0 1 2 3" );
					pMDU->Line( 240, 47, 240, 53 );
					pMDU->Line( 258, 47, 258, 53 );
					pMDU->Line( 276, 47, 276, 53 );
				}
				else
				{
					pMDU->mvprint( 34, 4, "3 2 1 0" );
					pMDU->Line( 348, 47, 348, 53 );
					pMDU->Line( 366, 47, 366, 53 );
					pMDU->Line( 384, 47, 384, 53 );
				}

				if (t2h < 20)
				{
					if (t2h > 10)
					{
						att = dps::DEUATT_FLASHING;
						t2h = 10;
					}
					else t2h = floor( t2h );

					if (t2h == 0) att = dps::DEUATT_FLASHING;

					if (TimeToHAC < 0) pos = 222 + Round( t2h * 18 );
					else pos = 402 - Round( t2h * 18 );
					pMDU->Line( pos, 48, pos - 6, 40, att );
					pMDU->Line( pos - 6, 40, pos + 6, 40, att );
					pMDU->Line( pos + 6, 40, pos, 48, att );
				}

				// side scale
				pMDU->mvprint( 37, 5, "5.0K" );
				pMDU->mvprint( 37, 14, "5.0K" );
				att = 0;
				double err = ReadCOMPOOL_SD( SCP_HERROR );

				if (err > 5000.0)
				{
					att = dps::DEUATT_FLASHING;
					pos = 195;
				}
				else if (err < -5000.0)
				{
					att = dps::DEUATT_FLASHING;
					pos = 73;
				}
				else pos = Round( err * 0.0122 ) + 134;

				pMDU->LeftArrowFilled( 420, pos, att );
			}
			else if (ReadCOMPOOL_IS( SCP_IPHASE ) == 2)
			{
				// HDG
				// top scale
				pMDU->Line( 222, 47, 222, 53 );
				pMDU->Line( 402, 47, 402, 53 );
				pMDU->mvprint( 20, 4, "5.0K" );
				pMDU->mvprint( 38, 4, "5.0K" );
				pMDU->Line( 268, 47, 268, 53 );
				pMDU->Line( 312, 47, 312, 53 );
				pMDU->Line( 358, 47, 358, 53 );
				att = 0;
				int pos;
				double err = -(ReadCOMPOOL_SD( SCP_RCIR ) - ReadCOMPOOL_SD( SCP_RTURN )) * ReadCOMPOOL_SD( SCP_YSGN );

				if (err > 5000.0)
				{
					att = dps::DEUATT_FLASHING;
					pos = 402;
				}
				else if (err < -5000.0)
				{
					att = dps::DEUATT_FLASHING;
					pos = 222;
				}
				else pos = Round( err * 0.018 ) + 312;

				pMDU->OrbiterSymbolTop( pos, 36, att );

				// side scale
				pMDU->mvprint( 37, 5, "5.0K" );
				pMDU->mvprint( 37, 14, "5.0K" );
				att = 0;
				err = ReadCOMPOOL_SD( SCP_HERROR );

				if (err > 5000.0)
				{
					att = dps::DEUATT_FLASHING;
					pos = 195;
				}
				else if (err < -5000.0)
				{
					att = dps::DEUATT_FLASHING;
					pos = 73;
				}
				else pos = Round( err * 0.0122 ) + 134;

				pMDU->LeftArrowFilled( 420, pos, att );
			}
			else
			{
				// PRFNL and A/L
				// top scale
				pMDU->Line( 222, 47, 222, 53 );
				pMDU->Line( 402, 47, 402, 53 );
				pMDU->mvprint( 20, 4, "2.5K" );
				pMDU->mvprint( 38, 4, "2.5K" );
				pMDU->Line( 268, 47, 268, 53 );
				pMDU->Line( 312, 47, 312, 53 );
				pMDU->Line( 358, 47, 358, 53 );
				att = 0;
				int pos;
				double err = ReadCOMPOOL_SD( SCP_Y );

				if (err > 2500.0)
				{
					att = dps::DEUATT_FLASHING;
					pos = 402;
				}
				else if (err < -2500.0)
				{
					att = dps::DEUATT_FLASHING;
					pos = 222;
				}
				else pos = Round( err * 0.036 ) + 312;

				pMDU->OrbiterSymbolTop( pos, 36, att );

				// side scale
				pMDU->mvprint( 37, 5, "1.0K" );
				pMDU->mvprint( 37, 14, "1.0K" );
				att = 0;
				err = (ReadCOMPOOL_IS( SCP_TG_END ) == 1) ? ReadCOMPOOL_SD( SCP_HERR ) : ReadCOMPOOL_SD( SCP_HERROR );

				if (err > 1000.0)
				{
					att = dps::DEUATT_FLASHING;
					pos = 195;
				}
				else if (err < -1000.0)
				{
					att = dps::DEUATT_FLASHING;
					pos = 73;
				}
				else pos = Round( err * 0.061 ) + 134;

				pMDU->LeftArrowFilled( 420, pos, att );
			}
		}

		// lines
		pMDU->Line( 0, 14, 110, 14 );
		pMDU->Line( 110, 14, 110, 56 );
		pMDU->Line( 0, 56, 110, 56 );

		pMDU->Line( 0, 154, 150, 154 );

		pMDU->Line( 0, 238, 512, 238 );
		pMDU->Line( 260, 294, 450, 294 );
		pMDU->Line( 260, 308, 510, 308 );
		pMDU->Line( 0, 322, 260, 322 );

		pMDU->Line( 60, 238, 60, 322 );
		pMDU->Line( 120, 238, 120, 322 );
		pMDU->Line( 170, 238, 170, 336 );
		pMDU->Line( 200, 238, 200, 336 );
		pMDU->Line( 230, 238, 230, 336 );
		pMDU->Line( 260, 238, 260, 336 );
		pMDU->Line( 350, 238, 350, 280 );
		pMDU->Line( 430, 238, 430, 280 );
		pMDU->Line( 450, 294, 450, 308 );
		return;
	}

	void GeneralDisplays::OnPaint_SPEC51_PASS( vc::MDU* pMDU ) const
	{
		PrintCommonHeader( "    OVERRIDE", pMDU );

		// static parts (labels)
		// ABORT MODE
		pMDU->mvprint( 0, 2, "ABORT MODE" );
		pMDU->mvprint( 1, 3, "TAL" );
		pMDU->mvprint( 10, 3, "1" );
		pMDU->mvprint( 1, 4, "ATO" );
		pMDU->mvprint( 10, 4, "2" );
		pMDU->mvprint( 0, 5, "ABORT     3" );
		pMDU->mvprint( 0, 6, "THROT MAX 4" );
		pMDU->mvprint( 6, 7, "ABT 50" );
		pMDU->mvprint( 6, 8, "NOM 51" );

		// ENTRY FCS
		pMDU->mvprint( 29, 2, "ENTRY FCS" );
		pMDU->mvprint( 18, 3, "ELEVON    FILTER    ATMOSPHERE" );
		pMDU->mvprint( 16, 4, "AUTO  17    NOM 20    NOM    22" );
		pMDU->mvprint( 16, 5, "FIXED 18    ALT 21    N POLE 23" );
		pMDU->mvprint( 18, 6, "SSME REPOS 19       S POLE 24" );

		// IMU
		pMDU->mvprint( 18, 7, "IMU STAT ATT DES" );
		pMDU->mvprint( 19, 8, "1" );
		pMDU->mvprint( 31, 8, "25" );
		pMDU->mvprint( 19, 9, "2" );
		pMDU->mvprint( 31, 9, "26" );
		pMDU->mvprint( 19, 10, "3" );
		pMDU->mvprint( 31, 10, "27" );

		// PRL
		pMDU->mvprint( 43, 7, "PRL" );
		pMDU->mvprint( 39, 8, "SYS AUT DES" );
		pMDU->mvprint( 40, 9, "1  28  31" );
		pMDU->mvprint( 40, 10, "2  29  32" );
		pMDU->mvprint( 40, 11, "3  30  33" );

		// PRPLT DUMP
		pMDU->mvprint( 3, 9, "PRPLT DUMP" );
		pMDU->mvprint( 4, 10, "ICNCT 5" );
		pMDU->mvprint( 0, 11, "OMS DUMP" );
		pMDU->mvprint( 3, 12, "ARM    6" );
		pMDU->mvprint( 3, 13, "START  7" );
		pMDU->mvprint( 3, 14, "STOP   8" );
		pMDU->mvprint( 1, 15, "9 QUAN/SIDE" );
		pMDU->mvprint( 0, 16, "OMS DUMP TTG" );

		// ADTA
		pMDU->mvprint( 18, 12, "ADTA" );
		pMDU->mvprint( 28, 12, "H" );
		pMDU->Alpha( 36, 12 );
		pMDU->mvprint( 42, 12, "M    DES" );
		pMDU->mvprint( 20, 13, "L 1" );
		pMDU->mvprint( 47, 13, "34" );
		pMDU->mvprint( 22, 14, "3" );
		pMDU->mvprint( 47, 14, "35" );
		pMDU->mvprint( 20, 15, "R 2" );
		pMDU->mvprint( 47, 15, "36" );
		pMDU->mvprint( 22, 16, "4" );
		pMDU->mvprint( 47, 16, "37" );

		// ET SEP
		pMDU->mvprint( 18, 17, "ET SEP" );
		pMDU->mvprint( 20, 18, "AUTO    38" );
		pMDU->mvprint( 20, 19, "SEP     39" );

		// ROLL MODE
		pMDU->mvprint( 34, 17, "ROLL MODE" );
		pMDU->mvprint( 35, 18, "AUTO SEL    42" );
		pMDU->mvprint( 35, 19, "WRAP MODE 45" );

		// AFT RCS
		pMDU->mvprint( 0, 19, "AFT RCS 13" );
		pMDU->mvprint( 3, 20, "14 TIME" );

		// ET UMB DR
		pMDU->mvprint( 18, 20, "ET UMB DR" );
		pMDU->mvprint( 20, 21, "CLOSE   40" );

		// VENT DOOR CNTL
		pMDU->mvprint( 34, 20, "VENT DOOR CNTL" );
		pMDU->mvprint( 35, 21, "OPEN   43" );
		pMDU->mvprint( 35, 22, "CLOSE  44" );

		// FWD RCS
		pMDU->mvprint( 0, 22, "FWD RCS 15" );
		pMDU->mvprint( 3, 23, "16 TIME" );

		// RCS RM MANIF
		pMDU->mvprint( 18, 22, "RCS RM MANF" );
		pMDU->mvprint( 20, 23, "CL OVRD 41" );


		// static parts (lines)
		pMDU->Line( 170, 98, 170, 336 );
		pMDU->Line( 170, 98, 510, 98 );
		pMDU->Line( 170, 168, 510, 168 );
		pMDU->Line( 170, 238, 510, 238 );


		// dynamic parts
		switch (GetMajorMode())
		{
			case 102:
			case 103:
			case 601:
				{
					unsigned short kmaxsel = ReadCOMPOOL_IS( SCP_KMAX_SEL );
					if (kmaxsel == 1) pMDU->mvprint( 11, 6, "*" );
					else if (kmaxsel == 2) pMDU->mvprint( 12, 7, "*" );
					else if (kmaxsel == 0) pMDU->mvprint( 12, 8, "*" );
				}
				break;
		}

		switch (GetMajorMode())
		{
			case 304:
			case 305:
			case 602:
			case 603:
				{
					unsigned short SelEntryModeLGain = ReadCOMPOOL_IS( SCP_SEL_L_GAIN );
					unsigned short SelEntryModeNoYJet = ReadCOMPOOL_IS( SCP_SEL_NO_Y_JET );
					unsigned short OVRDEntryMode = ReadCOMPOOL_IS( SCP_ENTRY_SW_OVERRIDE );

					if ((SelEntryModeLGain == 1) && (SelEntryModeNoYJet == 0)) pMDU->mvprint( 44, 17, "L GAIN" );
					else if ((SelEntryModeLGain == 0) && (SelEntryModeNoYJet == 1)) pMDU->mvprint( 44, 17, "NO YJET" );
					else pMDU->mvprint( 44, 17, "AUTO" );

					if (OVRDEntryMode == 1) pMDU->mvprint( 49, 18, "*" );
				}
				break;
		}

		if (GetMajorMode() / 100 == 3)
		{
			switch (ReadCOMPOOL_IS( SCP_WRAP ))
			{
				case 0:
					pMDU->mvprint( 48, 19, "INH" );
					break;
				case 1:
					pMDU->mvprint( 48, 19, "ENA" );
					break;
				case 2:
					pMDU->mvprint( 48, 19, "ACT" );
					break;
			}
		}

		if ((ReadCOMPOOL_IS( SCP_VENT_DOOR_SEQ_INIT ) == 1) && (ReadCOMPOOL_IS( SCP_ALL_VENT_CLOSE_CMD ) == 0)) pMDU->mvprint( 44, 21, "*" );
		else if (ReadCOMPOOL_IS( SCP_VENT_DOOR_POS_IND ) == 1) pMDU->mvprint( 44, 21, "* OP" );

		if ((ReadCOMPOOL_IS( SCP_VENT_DOOR_SEQ_INIT ) == 1) && (ReadCOMPOOL_IS( SCP_ALL_VENT_CLOSE_CMD ) == 1)) pMDU->mvprint( 44, 22, "*" );
		else if (ReadCOMPOOL_IS( SCP_VENT_DOOR_POS_IND ) == 2) pMDU->mvprint( 44, 22, "* CL" );
		return;
	}

	void GeneralDisplays::OnPaint_SPEC53_PASS( vc::MDU* pMDU ) const
	{
		PrintCommonHeader( "       CONTROLS", pMDU );

		// static parts (labels)
		// SEC
		pMDU->mvprint( 0, 3, "SEC ACT CK" );
		pMDU->mvprint( 2, 5, "CH1 1" );
		pMDU->mvprint( 4, 6, "2 2" );
		pMDU->mvprint( 4, 7, "3 3" );
		pMDU->mvprint( 4, 8, "4 4" );
		pMDU->mvprint( 0, 9, "START 5" );
		pMDU->mvprint( 1, 10, "STOP 6" );
		pMDU->mvprint( 1, 12, "NEG STIM" );
		pMDU->mvprint( 2, 13, "ENA 7" );

		// AERO
		pMDU->mvprint( 14, 3, "AERO PORT STAT" );
		pMDU->mvprint( 21, 4, "1 2 3 4" );
		pMDU->mvprint( 14, 5, "L OB" );
		pMDU->mvprint( 16, 6, "IB" );
		pMDU->mvprint( 14, 7, "R IB" );
		pMDU->mvprint( 16, 8, "OB" );
		pMDU->mvprint( 15, 9, "RUD" );
		pMDU->mvprint( 11, 10, "SPD BRK" );

		// SSME
		pMDU->mvprint( 33, 3, "SSME PORT STAT" );
		pMDU->mvprint( 38, 4, "1 2 3 4" );
		pMDU->mvprint( 34, 5, "L P" );
		pMDU->mvprint( 36, 6, "Y" );
		pMDU->mvprint( 34, 7, "C P" );
		pMDU->mvprint( 36, 8, "Y" );
		pMDU->mvprint( 34, 9, "R P" );
		pMDU->mvprint( 36, 10, "Y" );

		// ACT
		pMDU->mvprint( 22, 12, "ACT/CH" );
		pMDU->mvprint( 13, 13, "8 BYPASS" );
		pMDU->mvprint( 13, 14, "9  RESET" );

		// LRU
		pMDU->mvprint( 1, 17, "LRU   AA      RGA   SURF FDBK" );
		pMDU->mvprint( 7, 18, "DES     DES" );
		pMDU->mvprint( 23, 18, "DES" );
		pMDU->mvprint( 2, 19, "1" );
		pMDU->mvprint( 6, 19, "10" );
		pMDU->mvprint( 14, 19, "14" );
		pMDU->mvprint( 22, 19, "18" );
		pMDU->mvprint( 2, 20, "2" );
		pMDU->mvprint( 6, 20, "11" );
		pMDU->mvprint( 14, 20, "15" );
		pMDU->mvprint( 22, 20, "19" );
		pMDU->mvprint( 2, 21, "3" );
		pMDU->mvprint( 6, 21, "12" );
		pMDU->mvprint( 14, 21, "16" );
		pMDU->mvprint( 22, 21, "20" );
		pMDU->mvprint( 2, 22, "4" );
		pMDU->mvprint( 6, 22, "13" );
		pMDU->mvprint( 14, 22, "17" );
		pMDU->mvprint( 22, 22, "21" );


		// TODO dynamic parts
		return;
	}

	void GeneralDisplays::OnPaint_SPEC55_PASS( vc::MDU* pMDU ) const
	{
		PrintCommonHeader( "    GPS STATUS", pMDU );

		// static parts (labels)
		pMDU->mvprint( 0, 2, "I/O 10   GPS1  GPS2  GPS3" );
		pMDU->mvprint( 0, 3, "STAT" );
		pMDU->mvprint( 0, 4, "MODE" );
		pMDU->mvprint( 0, 5, "S/TEST    11    12    13" );
		pMDU->mvprint( 0, 6, "INIT" );
		pMDU->mvprint( 10, 6, "14" );
		pMDU->mvprint( 16, 6, "15" );
		pMDU->mvprint( 22, 6, "16" );
		pMDU->mvprint( 0, 7, "NAV" );
		pMDU->mvprint( 10, 7, "17" );
		pMDU->mvprint( 16, 7, "18" );
		pMDU->mvprint( 22, 7, "19" );
		pMDU->mvprint( 0, 8, "RESTART   20    21    22" );
		pMDU->mvprint( 0, 10, "GDOP" );

		pMDU->mvprint( 33, 3, "GPS MINUS NAV" );
		pMDU->Delta( 28, 4 );
		pMDU->mvprint( 29, 4, "H" );
		pMDU->Delta( 40, 4 );
		pMDU->mvprint( 41, 4, "H" );
		pMDU->DotCharacter( 41, 4 );
		pMDU->Delta( 28, 5 );
		pMDU->mvprint( 29, 5, "DR" );
		pMDU->Delta( 40, 5 );
		pMDU->mvprint( 41, 5, "DR" );
		pMDU->DotCharacter( 41, 5 );
		pMDU->Delta( 28, 6 );
		pMDU->mvprint( 29, 6, "CR" );
		pMDU->Delta( 40, 6 );
		pMDU->mvprint( 41, 6, "CR" );
		pMDU->DotCharacter( 41, 6 );
		pMDU->mvprint( 30, 8, "LAT" );
		pMDU->mvprint( 38, 8, "LON" );
		pMDU->mvprint( 46, 8, "ALT" );

		pMDU->mvprint( 0, 11, "DG FAIL" );
		pMDU->mvprint( 0, 12, "DES RCVR  26    27    28" );
		pMDU->mvprint( 0, 13, "QA OVRD   29    30    31" );
		pMDU->mvprint( 0, 14, "SF CAND" );
		pMDU->mvprint( 0, 15, "QA1 P 1" );
		pMDU->Sigma( 7, 15 );
		pMDU->mvprint( 0, 16, "QA2 POS" );
		pMDU->mvprint( 4, 17, "VEL" );
		pMDU->mvprint( 0, 18, "QA3 POS" );
		pMDU->mvprint( 4, 19, "VEL" );

		pMDU->mvprint( 40, 11, "AUT INH FOR" );
		pMDU->mvprint( 28, 12, "GPS TO G&C  32  33  34" );
		pMDU->mvprint( 28, 13, "GPS TO NAV  35  36  37" );
		pMDU->mvprint( 28, 14, "METERING OVERRIDE   38" );
		pMDU->mvprint( 28, 15, "GPS TIME ADJUST ENA 39" );

		pMDU->mvprint( 34, 16, "SATELLITES" );
		pMDU->mvprint( 28, 17, "TRKD  C1 C2 C3 C4 C5 C6" );
		pMDU->mvprint( 29, 18, "GPS1" );
		pMDU->mvprint( 29, 19, "GPS2" );
		pMDU->mvprint( 29, 20, "GPS3" );
		pMDU->mvprint( 28, 22, "DES 43" );

		pMDU->mvprint( 10, 20, "1-2   2-3   3-1" );
		pMDU->mvprint( 0, 21, "QA4 POS" );
		pMDU->mvprint( 4, 22, "VEL" );
		pMDU->mvprint( 7, 23, "LAST SEL FIL UPDATE" );


		// static parts (lines)
		pMDU->Line( 140, 14, 140, 322 );
		pMDU->Line( 200, 14, 200, 322 );
		pMDU->Line( 260, 14, 260, 322 );
		pMDU->Line( 0, 154, 510, 154 );
		pMDU->Line( 260, 224, 510, 224 );
		pMDU->Line( 0, 280, 260, 280 );


		// TODO dynamic parts
		int mm = GetMajorMode();
		if (((mm / 100) != 9) && ((mm / 100) != 1) && (mm != 601))
		{
			char cbuf[16];
			double lon = 0;
			double lat = 0;
			double rad = 0;
			STS()->GetEquPos( lon, lat, rad );

			lon *= DEG;
			lat *= DEG;
			rad -= 6371010;
			if ((mm == 304) || (mm == 305) || (mm == 602) || (mm == 603)) rad *= (MPS2FPS / 1000);// kft
			else rad /= NM2M;// nm

			if (lat >= 0) pMDU->mvprint( 28, 8, "N" );
			else pMDU->mvprint( 28, 8, "S" );

			sprintf_s( cbuf, 16, "%05.2f", fabs( lat ) );
			pMDU->mvprint( 28, 9, cbuf );

			if (lon >= 0) pMDU->mvprint( 36, 8, "E" );
			else pMDU->mvprint( 36, 8, "W" );

			sprintf_s( cbuf, 16, "%06.2f", fabs( lon ) );
			pMDU->mvprint( 35, 9, cbuf );

			sprintf_s( cbuf, 16, "%08.4f", rad );
			pMDU->mvprint( 43, 9, cbuf );
		}
		return;
	}

	void GeneralDisplays::OnPaint_DISP99_PASS( vc::MDU* pMDU ) const
	{
		PrintCommonHeader( "    FAULT", pMDU );

		// static parts (labels)
		pMDU->mvprint( 4, 5, "CRT" );
		pMDU->mvprint( 13, 5, "FAULT      C/W   GPC      TIME" );
		pMDU->mvprint( 4, 6, "ID" );
		return;
	}

	void GeneralDisplays::OnPaint_SPEC112_PASS( vc::MDU* pMDU ) const
	{
		PrintCommonHeader( "  GPC/BTU I/F", pMDU );

		// static parts (labels)
		// BTU SELECTION
		pMDU->mvprint( 3, 2, "BTU SELECTION" );
		pMDU->mvprint( 1, 3, "FF1 1   PCMMU 12" );
		pMDU->mvprint( 3, 4, "2 2   MMU1  13" );
		pMDU->mvprint( 3, 5, "3 3" );
		pMDU->mvprint( 12, 5, "2  14" );
		pMDU->mvprint( 3, 6, "4 4   MEC1  15" );
		pMDU->mvprint( 1, 7, "FA1 5" );
		pMDU->mvprint( 12, 7, "2  16" );
		pMDU->mvprint( 3, 8, "2 6   EIU1  17" );
		pMDU->mvprint( 3, 9, "3 7" );
		pMDU->mvprint( 12, 9, "2  18" );
		pMDU->mvprint( 3, 10, "4 8" );
		pMDU->mvprint( 12, 10, "3  19" );
		pMDU->mvprint( 1, 11, "PF1 9   DDU   20" );
		pMDU->mvprint( 3, 12, "2 10  MCIU  21" );
		pMDU->mvprint( 10, 13, "CMD  22" );
		pMDU->mvprint( 10, 14, "SRB  23" );
		pMDU->mvprint( 1, 15, "ALL" );
		pMDU->mvprint( 1, 16, "MDMS 11" );
		pMDU->mvprint( 11, 15, "DES" );
		pMDU->mvprint( 11, 16, "ALL   24" );

		// TEST STATUS
		pMDU->mvprint( 20, 2, "TEST STATUS" );
		pMDU->mvprint( 20, 4, "BTU ITEM" );
		pMDU->mvprint( 20, 5, "STEP" );
		pMDU->mvprint( 20, 6, "RDW" );
		pMDU->mvprint( 20, 7, "BCE STAT RG" );

		// MDM OUTPUT TEST
		pMDU->mvprint( 33, 3, "MDM OUTPUT TEST" );
		pMDU->mvprint( 37, 4, "MODULE" );

		pMDU->mvprint( 33, 6, "ANALOG OUTPUTS" );
		pMDU->mvprint( 34, 7, "0" );
		pMDU->mvprint( 43, 7, "1" );
		pMDU->mvprint( 34, 8, "2" );
		pMDU->mvprint( 43, 8, "3" );
		pMDU->mvprint( 34, 9, "4" );
		pMDU->mvprint( 43, 9, "5" );
		pMDU->mvprint( 34, 10, "6" );
		pMDU->mvprint( 43, 10, "7" );
		pMDU->mvprint( 34, 11, "8" );
		pMDU->mvprint( 43, 11, "9" );
		pMDU->mvprint( 33, 12, "10" );
		pMDU->mvprint( 42, 12, "11" );
		pMDU->mvprint( 33, 13, "12" );
		pMDU->mvprint( 42, 13, "13" );
		pMDU->mvprint( 33, 14, "14" );
		pMDU->mvprint( 42, 14, "15" );

		pMDU->mvprint( 33, 16, "DISCRETE OUTPUTS" );
		pMDU->mvprint( 33, 17, "CHANNEL 0" );
		pMDU->mvprint( 33, 18, "CHANNEL 1" );
		pMDU->mvprint( 33, 19, "CHANNEL 2" );

		// PORT SEL
		pMDU->mvprint( 19, 10, "PORT SEL 1 31" );
		pMDU->mvprint( 28, 11, "2 32" );

		// TEST
		pMDU->mvprint( 9, 18, "LEVEL 1    25" );
		pMDU->mvprint( 1, 19, "TEST    LEVEL 2    26" );
		pMDU->mvprint( 9, 20, "MDM OUTPUT 27" );
		pMDU->mvprint( 1, 21, "CONTROL TERMINATE  28" );
		pMDU->mvprint( 9, 22, "CONTINUE   29" );

		// BTU
		pMDU->mvprint( 31, 21, "BTU CYCLIC BITE 30" );


		// dynamic parts
		// TODO finish
		// BTU SELECTION
		if (ITEM_STATE_SPEC112[0] == true) pMDU->mvprint( 6, 3, "*" );
		if (ITEM_STATE_SPEC112[1] == true) pMDU->mvprint( 6, 4, "*" );
		if (ITEM_STATE_SPEC112[2] == true) pMDU->mvprint( 6, 5, "*" );
		if (ITEM_STATE_SPEC112[3] == true) pMDU->mvprint( 6, 6, "*" );
		if (ITEM_STATE_SPEC112[4] == true) pMDU->mvprint( 6, 7, "*" );
		if (ITEM_STATE_SPEC112[5] == true) pMDU->mvprint( 6, 8, "*" );
		if (ITEM_STATE_SPEC112[6] == true) pMDU->mvprint( 6, 9, "*" );
		if (ITEM_STATE_SPEC112[7] == true) pMDU->mvprint( 6, 10, "*" );
		if (ITEM_STATE_SPEC112[8] == true) pMDU->mvprint( 6, 11, "*" );
		if (ITEM_STATE_SPEC112[9] == true) pMDU->mvprint( 7, 12, "*" );
		if (ITEM_STATE_SPEC112[10] == true) pMDU->mvprint( 8, 16, "*" );
		if (ITEM_STATE_SPEC112[11] == true) pMDU->mvprint( 17, 3, "*" );
		if (ITEM_STATE_SPEC112[12] == true) pMDU->mvprint( 17, 4, "*" );
		if (ITEM_STATE_SPEC112[13] == true) pMDU->mvprint( 17, 5, "*" );
		if (ITEM_STATE_SPEC112[14] == true) pMDU->mvprint( 17, 6, "*" );
		if (ITEM_STATE_SPEC112[15] == true) pMDU->mvprint( 17, 7, "*" );
		if (ITEM_STATE_SPEC112[16] == true) pMDU->mvprint( 17, 8, "*" );
		if (ITEM_STATE_SPEC112[17] == true) pMDU->mvprint( 17, 9, "*" );
		if (ITEM_STATE_SPEC112[18] == true) pMDU->mvprint( 17, 10, "*" );
		if (ITEM_STATE_SPEC112[19] == true) pMDU->mvprint( 17, 11, "*" );
		if (ITEM_STATE_SPEC112[20] == true) pMDU->mvprint( 17, 12, "*" );
		if (ITEM_STATE_SPEC112[21] == true) pMDU->mvprint( 17, 13, "*" );
		if (ITEM_STATE_SPEC112[22] == true) pMDU->mvprint( 17, 14, "*" );
		if (ITEM_STATE_SPEC112[23] == true) pMDU->mvprint( 19, 16, "*" );



		// PORT SEL
		if (ITEM_STATE_SPEC112[30] == true) pMDU->mvprint( 32, 10, "*" );
		if (ITEM_STATE_SPEC112[31] == true) pMDU->mvprint( 32, 11, "*" );

		// TEST
		if (ITEM_STATE_SPEC112[24] == true) pMDU->mvprint( 22, 18, "*" );
		if (ITEM_STATE_SPEC112[25] == true) pMDU->mvprint( 22, 19, "*" );
		if (ITEM_STATE_SPEC112[26] == true) pMDU->mvprint( 22, 20, "*" );
		//if (ITEM_STATE_SPEC112[27] == true) pMDU->mvprint( 0, 0, "*" );
		//if (ITEM_STATE_SPEC112[28] == true) pMDU->mvprint( 0, 0, "*" );

		// BTU
		if (ITEM_STATE_SPEC112[29] == true) pMDU->mvprint( 49, 21, "*" );
		return;
	}

	void GeneralDisplays::OnPaint_SPEC113_PASS( vc::MDU* pMDU ) const
	{
		PrintCommonHeader( "ACTUATOR CONTROL", pMDU );

		// static parts (labels)
		// MONITOR
		pMDU->mvprint( 3, 1, "MONITOR" );
		pMDU->mvprint( 1, 2, "CMD     POS  ACT" );
		pMDU->mvprint( 15, 3, "SB  1" );
		pMDU->mvprint( 14, 4, "RUD  2" );
		pMDU->mvprint( 14, 5, "LIE  3" );
		pMDU->mvprint( 14, 6, "RIE  4" );
		pMDU->mvprint( 14, 7, "LOE  5" );
		pMDU->mvprint( 14, 8, "ROE  6" );
		pMDU->mvprint( 15, 9, "1P  7" );
		pMDU->mvprint( 15, 10, "1Y  8" );
		pMDU->mvprint( 15, 11, "2P  9" );
		pMDU->mvprint( 15, 12, "2Y 10" );
		pMDU->mvprint( 15, 13, "3P 12" );
		pMDU->mvprint( 15, 14, "3Y 12" );
		pMDU->mvprint( 14, 15, "RPA 13" );
		pMDU->mvprint( 14, 16, "RPS 14" );
		pMDU->mvprint( 14, 17, "RYA 15" );
		pMDU->mvprint( 14, 18, "RYS 16" );
		pMDU->mvprint( 14, 19, "LPA 17" );
		pMDU->mvprint( 14, 20, "LPS 18" );
		pMDU->mvprint( 14, 21, "LYA 19" );
		pMDU->mvprint( 14, 22, "LYS 20" );
		pMDU->mvprint( 15, 23, "BF 21" );

		// FAIL
		pMDU->mvprint( 23, 1, "FAIL" );
		pMDU->mvprint( 22, 2, "A B C D" );

		// ACTUATOR GIMBALING
		pMDU->mvprint( 32, 2, "ACTUATOR GIMBALING" );
		pMDU->mvprint( 30, 3, "RATE 29" );
		pMDU->mvprint( 44, 3, "DEG/SEC" );
		pMDU->mvprint( 30, 4, "FIN POS 30" );
		pMDU->mvprint( 48, 4, "DEG" );
		pMDU->mvprint( 30, 5, "START 31" );
		pMDU->mvprint( 43, 5, "STOP 32" );
		pMDU->mvprint( 40, 6, "STATUS" );
		pMDU->mvprint( 40, 7, "ECP ERR" );
		pMDU->mvprint( 41, 8, "BF MON 33" );

		// HYD PR
		pMDU->mvprint( 32, 7, "HYD PR" );
		pMDU->mvprint( 32, 8, "1" );
		pMDU->mvprint( 32, 9, "2" );
		pMDU->mvprint( 32, 10, "3" );

		// AI SRB/NW
		pMDU->mvprint( 38, 11, "AI SRB/NW 34" );

		// ME ISO V
		pMDU->mvprint( 30, 12, "ME ISO V" );
		pMDU->mvprint( 30, 13, "1  2" );
		pMDU->mvprint( 36, 13, "3" );

		// FC LIM CHNG
		pMDU->mvprint( 40, 13, "FC LIM CHNG" );
		pMDU->mvprint( 39, 14, "R/SB MAT 35" );
		pMDU->mvprint( 35, 15, "R/SB RFG/FRT 36" );
		pMDU->mvprint( 37, 16, "MAT P 40MS 37" );
		pMDU->mvprint( 37, 17, "NOP CA RFG 38" );
		pMDU->mvprint( 37, 18, "NOP CA FRT 39" );
		pMDU->mvprint( 40, 19, "NOP OMS 40" );
		pMDU->mvprint( 36, 20, "SRB S/S LIM 41" );
		pMDU->mvprint( 37, 21, "EL POS LIM 42" );
		pMDU->mvprint( 36, 22, "S/B POS LIM 43" );
		pMDU->mvprint( 34, 23, "R RATE .5 PCM 44" );

		// AI MODES
		pMDU->mvprint( 24, 16, "AI MODES" );
		pMDU->mvprint( 23, 17, "0 SAFE 22" );
		pMDU->mvprint( 23, 18, "1 MDM  23" );
		pMDU->mvprint( 23, 19, "2 FERY 24" );
		pMDU->mvprint( 23, 20, "3 RAIN 25" );
		pMDU->mvprint( 23, 21, "4 GRAV 26" );
		pMDU->mvprint( 23, 22, "5 NULL 27" );
		pMDU->mvprint( 23, 23, "6 TURN 28" );


		// static parts (lines)
		// ACTUATOR GIMBALING
		pMDU->Line( 320, 42, 500, 42 );

		pMDU->Line( 380, 56, 400, 56 );
		pMDU->Line( 410, 56, 430, 56 );

		// HYD PR
		pMDU->Line( 320, 112, 380, 112 );

		// ME ISO V
		pMDU->Line( 300, 182, 380, 182 );

		// FC LIM CHNG
		pMDU->Line( 400, 196, 510, 196 );

		// AI MODES
		pMDU->Line( 240, 238, 320, 238 );


		// dynamic parts
		// TODO finish
		char cbuf[64];

		// MONITOR
		/*sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 0, 3, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 7, 3, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 0, 4, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 7, 4, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 0, 5, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 7, 5, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 0, 6, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 7, 6, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 0, 7, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 7, 7, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 0, 8, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 7, 8, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 0, 9, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 7, 9, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 0, 10, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 7, 10, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 0, 11, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 7, 11, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 0, 12, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 7, 12, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 0, 13, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 7, 13, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 0, 14, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 7, 14, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 0, 15, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 7, 15, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 0, 16, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 7, 16, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 0, 17, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 7, 17, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 0, 18, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 7, 18, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 0, 19, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 7, 19, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 0, 20, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 7, 20, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 0, 21, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 7, 21, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 0, 22, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 7, 22, cbuf );
		sprintf_s( cbuf, 64, "%02.0f", dtmp );
		pMDU->mvprint( 1, 23, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 7, 23, cbuf );*/

		if (ITEM_STATE_SPEC113[0] == true) pMDU->mvprint( 20, 3, "*" );
		if (ITEM_STATE_SPEC113[1] == true) pMDU->mvprint( 20, 4, "*" );
		if (ITEM_STATE_SPEC113[2] == true) pMDU->mvprint( 20, 5, "*" );
		if (ITEM_STATE_SPEC113[3] == true) pMDU->mvprint( 20, 6, "*" );
		if (ITEM_STATE_SPEC113[4] == true) pMDU->mvprint( 20, 7, "*" );
		if (ITEM_STATE_SPEC113[5] == true) pMDU->mvprint( 20, 8, "*" );
		if (ITEM_STATE_SPEC113[6] == true) pMDU->mvprint( 20, 9, "*" );
		if (ITEM_STATE_SPEC113[7] == true) pMDU->mvprint( 20, 10, "*" );
		if (ITEM_STATE_SPEC113[8] == true) pMDU->mvprint( 20, 11, "*" );
		if (ITEM_STATE_SPEC113[9] == true) pMDU->mvprint( 20, 12, "*" );
		if (ITEM_STATE_SPEC113[10] == true) pMDU->mvprint( 20, 13, "*" );
		if (ITEM_STATE_SPEC113[11] == true) pMDU->mvprint( 20, 14, "*" );
		if (ITEM_STATE_SPEC113[12] == true) pMDU->mvprint( 20, 15, "*" );
		if (ITEM_STATE_SPEC113[13] == true) pMDU->mvprint( 20, 16, "*" );
		if (ITEM_STATE_SPEC113[14] == true) pMDU->mvprint( 20, 17, "*" );
		if (ITEM_STATE_SPEC113[15] == true) pMDU->mvprint( 20, 18, "*" );
		if (ITEM_STATE_SPEC113[16] == true) pMDU->mvprint( 20, 19, "*" );
		if (ITEM_STATE_SPEC113[17] == true) pMDU->mvprint( 20, 20, "*" );
		if (ITEM_STATE_SPEC113[18] == true) pMDU->mvprint( 20, 21, "*" );
		if (ITEM_STATE_SPEC113[19] == true) pMDU->mvprint( 20, 22, "*" );
		if (ITEM_STATE_SPEC113[20] == true) pMDU->mvprint( 20, 23, "*" );

		// FAIL
		/*if (abc == true) pMDU->DownArrow( 22, 3, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 22, 3, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 24, 3, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 24, 3, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 26, 3, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 26, 3, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 28, 3, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 28, 3, "M", dps::DEUATT_OVERBRIGHT );

		if (abc == true) pMDU->DownArrow( 22, 4, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 22, 4, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 24, 4, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 24, 4, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 26, 4, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 26, 4, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 28, 4, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 28, 4, "M", dps::DEUATT_OVERBRIGHT );

		if (abc == true) pMDU->DownArrow( 22, 5, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 22, 5, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 24, 5, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 24, 5, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 26, 5, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 26, 5, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 28, 5, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 28, 5, "M", dps::DEUATT_OVERBRIGHT );

		if (abc == true) pMDU->DownArrow( 22, 6, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 22, 6, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 24, 6, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 24, 6, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 26, 6, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 26, 6, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 28, 6, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 28, 6, "M", dps::DEUATT_OVERBRIGHT );

		if (abc == true) pMDU->DownArrow( 22, 7, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 22, 7, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 24, 7, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 24, 7, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 26, 7, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 26, 7, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 28, 7, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 28, 7, "M", dps::DEUATT_OVERBRIGHT );

		if (abc == true) pMDU->DownArrow( 22, 8, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 22, 8, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 24, 8, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 24, 8, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 26, 8, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 26, 8, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 28, 8, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 28, 8, "M", dps::DEUATT_OVERBRIGHT );

		if (abc == true) pMDU->DownArrow( 22, 9, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 22, 9, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 24, 9, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 24, 9, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 26, 9, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 26, 9, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 28, 9, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 28, 9, "M", dps::DEUATT_OVERBRIGHT );

		if (abc == true) pMDU->DownArrow( 22, 10, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 22, 10, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 24, 10, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 24, 10, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 26, 10, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 26, 10, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 28, 10, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 28, 10, "M", dps::DEUATT_OVERBRIGHT );

		if (abc == true) pMDU->DownArrow( 22, 11, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 22, 11, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 24, 11, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 24, 11, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 26, 11, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 26, 11, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 28, 11, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 28, 11, "M", dps::DEUATT_OVERBRIGHT );

		if (abc == true) pMDU->DownArrow( 22, 12, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 22, 12, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 24, 12, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 24, 12, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 26, 12, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 26, 12, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 28, 12, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 28, 12, "M", dps::DEUATT_OVERBRIGHT );

		if (abc == true) pMDU->DownArrow( 22, 13, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 22, 13, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 24, 13, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 24, 13, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 26, 13, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 26, 13, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 28, 13, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 28, 13, "M", dps::DEUATT_OVERBRIGHT );

		if (abc == true) pMDU->DownArrow( 22, 14, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 22, 14, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 24, 14, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 24, 14, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 26, 14, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 26, 14, "M", dps::DEUATT_OVERBRIGHT );
		if (abc == true) pMDU->DownArrow( 28, 14, dps::DEUATT_OVERBRIGHT );
		else if (abc == true) pMDU->mvprint( 28, 14, "M", dps::DEUATT_OVERBRIGHT );*/

		// ACTUATOR GIMBALING
		/*sprintf_s( cbuf, 64, "%05.2f", dtmp );
		pMDU->mvprint( 38, 3, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		pMDU->mvprint( 41, 4, cbuf );*/

		//if (ITEM_STATE_SPEC113[28] == true) pMDU->mvprint( 0, 0, "*" );
		//if (ITEM_STATE_SPEC113[29] == true) pMDU->mvprint( 0, 0, "*" );
		if (ITEM_STATE_SPEC113[30] == true)
		{
			pMDU->mvprint( 38, 5, "*" );

			/*if (abc == true)
			{
				// speedbrake
				if (abc == true)
				{
					pMDU->LeftArrow( 39, 5 );
					pMDU->RightArrow( 40, 5 );
				}
				else
				{
					pMDU->RightArrow( 39, 5 );
					pMDU->LeftArrow( 40, 5 );
				}
			}
			else if (abc == true)
			{
				// other actuators (vertical)
				if (abc == true) pMDU->UpArrow( 39, 5 );
				else pMDU->DownArrow( 39, 5 );
			}
			else
			{
				// other actuators (horizontal)
				if (abc == true) pMDU->LeftArrow( 39, 5 );
				else pMDU->RightArrow( 39, 5 );
			}*/
		}
		if (ITEM_STATE_SPEC113[31] == true) pMDU->mvprint( 50, 5, "*" );
		if (ITEM_STATE_SPEC113[32] == true) pMDU->mvprint( 50, 8, "*" );

		// HYD PR
		sprintf_s( cbuf, 64, "%4.0f", STS()->GetAPU( 1 )->GetHydraulicPressure() );
		pMDU->mvprint( 34, 8, cbuf );
		sprintf_s( cbuf, 64, "%4.0f", STS()->GetAPU( 2 )->GetHydraulicPressure() );
		pMDU->mvprint( 34, 9, cbuf );
		sprintf_s( cbuf, 64, "%4.0f", STS()->GetAPU( 3 )->GetHydraulicPressure() );
		pMDU->mvprint( 34, 10, cbuf );

		// AI SRB/NW
		if (ITEM_STATE_SPEC113[33] == true) pMDU->mvprint( 50, 11, "*" );

		// ME ISO V
		/*if (abc == true) pMDU->mvprint( 31, 13, "C" );
		if (abc == true) pMDU->mvprint( 34, 13, "C" );
		if (abc == true) pMDU->mvprint( 37, 13, "C" );*/

		// FC LIM CHNG
		if (ITEM_STATE_SPEC113[34] == true) pMDU->mvprint( 50, 14, "*" );
		if (ITEM_STATE_SPEC113[35] == true) pMDU->mvprint( 50, 15, "*" );
		if (ITEM_STATE_SPEC113[36] == true) pMDU->mvprint( 50, 16, "*" );
		if (ITEM_STATE_SPEC113[37] == true) pMDU->mvprint( 50, 17, "*" );
		if (ITEM_STATE_SPEC113[38] == true) pMDU->mvprint( 50, 18, "*" );
		if (ITEM_STATE_SPEC113[39] == true) pMDU->mvprint( 50, 19, "*" );
		if (ITEM_STATE_SPEC113[40] == true) pMDU->mvprint( 50, 20, "*" );
		if (ITEM_STATE_SPEC113[41] == true) pMDU->mvprint( 50, 21, "*" );
		if (ITEM_STATE_SPEC113[42] == true) pMDU->mvprint( 50, 22, "*" );
		if (ITEM_STATE_SPEC113[43] == true) pMDU->mvprint( 50, 23, "*" );

		// AI MODES
		if (ITEM_STATE_SPEC113[21] == true) pMDU->mvprint( 32, 17, "*" );
		if (ITEM_STATE_SPEC113[22] == true) pMDU->mvprint( 32, 18, "*" );
		if (ITEM_STATE_SPEC113[23] == true) pMDU->mvprint( 32, 19, "*" );
		if (ITEM_STATE_SPEC113[24] == true) pMDU->mvprint( 32, 20, "*" );
		if (ITEM_STATE_SPEC113[25] == true) pMDU->mvprint( 32, 21, "*" );
		if (ITEM_STATE_SPEC113[26] == true) pMDU->mvprint( 32, 22, "*" );
		if (ITEM_STATE_SPEC113[27] == true) pMDU->mvprint( 32, 23, "*" );
		return;
	}


	void GeneralDisplays::OnPaint_DISP18_BFS( vc::MDU* pMDU ) const
	{
		PrintCommonHeader( " GNC SYS SUMM 1", pMDU );
		pMDU->mvprint( 34, 1, "BFS", dps::DEUATT_OVERBRIGHT );

		// static parts (labels)
		// SURF
		pMDU->mvprint( 5, 3, "SURF     POS   MOM" );
		pMDU->mvprint( 5, 4, "L OB" );
		pMDU->mvprint( 7, 5, "IB" );
		pMDU->mvprint( 5, 6, "R IB" );
		pMDU->mvprint( 7, 7, "OB" );
		pMDU->mvprint( 5, 8, "AIL" );
		pMDU->mvprint( 5, 9, "RUD" );
		pMDU->mvprint( 5, 10, "SPD BRK" );
		pMDU->mvprint( 5, 11, "BDY FLP" );

		// DPS
		pMDU->mvprint( 30, 3, "DPS    1 2 3 4" );
		pMDU->mvprint( 30, 4, "MDM FF" );
		pMDU->mvprint( 30, 5, "FA" );
		pMDU->mvprint( 30, 6, "PL" );

		// FCS
		pMDU->mvprint( 30, 9, "FCS CH 1 2 3 4" );

		// NAV
		pMDU->mvprint( 30, 13, "NAV  1 2 3 4" );
		pMDU->mvprint( 30, 14, "IMU" );
		pMDU->mvprint( 30, 15, "TAC" );
		pMDU->mvprint( 30, 16, "ADTA" );

		// MPS
		pMDU->mvprint( 2, 13, "MPS" );
		pMDU->mvprint( 14, 13, "L" );
		pMDU->mvprint( 20, 13, "C" );
		pMDU->mvprint( 26, 13, "R" );
		pMDU->mvprint( 2, 14, "HE TK P" );
		pMDU->mvprint( 4, 15, "REG P A" );
		pMDU->mvprint( 10, 16, "B" );
		pMDU->mvprint( 4, 17, "dP/dT" );

		pMDU->mvprint( 30, 18, "MPS PNEU HE P" );
		pMDU->mvprint( 35, 19, "TK" );
		pMDU->mvprint( 35, 20, "REG" );
		pMDU->mvprint( 35, 21, "ACUM" );
		pMDU->mvprint( 35, 19, "TK" );

		pMDU->mvprint( 2, 19, "ULL P LH2" );
		pMDU->mvprint( 8, 20, "LO2" );

		pMDU->mvprint( 2, 22, "GH2 OUT P" );
		pMDU->mvprint( 2, 23, "GO2 OUT T" );

		pMDU->mvprint( 30, 22, "MANF P LH2" );
		pMDU->mvprint( 37, 23, "LO2" );


		// static parts (lines)
		pMDU->Line( 50, 56, 230, 56 );

		pMDU->Line( 300, 56, 440, 56 );

		pMDU->Line( 300, 140, 440, 140 );

		pMDU->Line( 300, 196, 420, 196 );

		pMDU->Line( 20, 196, 290, 196 );
		pMDU->Line( 290, 196, 290, 238 );
		pMDU->Line( 290, 238, 450, 238 );


		// dynamic parts
		unsigned int MM = ReadCOMPOOL_IS( SCP_MM );
		// TODO finish
		char cbuf[64];
		double tmp[3] = {0};
		char pos;

		// SURF
		if (((MM / 100) == 3) || (MM == 602) || (MM == 603))
		{
			double LOB = ReadCOMPOOL_SD( SCP_LOB_ELVN_POS_FDBK );
			double LIB = ReadCOMPOOL_SD( SCP_LIB_ELVN_POS_FDBK );
			double RIB = ReadCOMPOOL_SD( SCP_RIB_ELVN_POS_FDBK );
			double ROB = ReadCOMPOOL_SD( SCP_ROB_ELVN_POS_FDBK );
			double DAFB = ReadCOMPOOL_SD( SCP_DAFB );
			double DRFB = ReadCOMPOOL_SD( SCP_DRFB );
			double DSBFB = ReadCOMPOOL_SD( SCP_DSBFB_DEG );
			double DBFOFB = ReadCOMPOOL_SD( SCP_DBFOFB );

			if (LOB > 0.0) pos = 'D';
			else if (LOB < 0.0) pos = 'U';
			else pos = ' ';
			sprintf_s( cbuf, 64, "%c%4.1f  %2.0f", pos, fabs( LOB ), tmp[0] );
			pMDU->mvprint( 13, 4, cbuf );

			if (LIB > 0.0) pos = 'D';
			else if (LIB < 0.0) pos = 'U';
			else pos = ' ';
			sprintf_s( cbuf, 64, "%c%4.1f  %2.0f", pos, fabs( LIB ), tmp[0] );
			pMDU->mvprint( 13, 5, cbuf );

			if (RIB > 0.0) pos = 'D';
			else if (RIB < 0.0) pos = 'U';
			else pos = ' ';
			sprintf_s( cbuf, 64, "%c%4.1f  %2.0f", pos, fabs( RIB ), tmp[0] );
			pMDU->mvprint( 13, 6, cbuf );

			if (ROB > 0.0) pos = 'D';
			else if (ROB < 0.0) pos = 'U';
			else pos = ' ';
			sprintf_s( cbuf, 64, "%c%4.1f  %2.0f", pos, fabs( ROB ), tmp[0] );
			pMDU->mvprint( 13, 7, cbuf );

			if (DAFB > 0.0) pos = 'R';
			else if (DAFB < 0.0) pos = 'L';
			else pos = ' ';
			sprintf_s( cbuf, 64, "%c%4.1f", pos, fabs( DAFB ) );
			pMDU->mvprint( 13, 8, cbuf );

			if (DRFB > 0.0) pos = 'L';
			else if (DRFB < 0.0) pos = 'R';
			else pos = ' ';
			sprintf_s( cbuf, 64, "%c%4.1f", pos, fabs( DRFB ) );
			pMDU->mvprint( 13, 9, cbuf );

			sprintf_s( cbuf, 64, "%5.1f", fabs( DSBFB ) );
			pMDU->mvprint( 13, 10, cbuf );

			sprintf_s( cbuf, 64, "%5.1f", range( 0.0, fabs( (DBFOFB + 11.7) * 2.919708 ), 100.0 ) );
			pMDU->mvprint( 13, 11, cbuf );
		}

		// DPS

		// FCS

		// NAV

		// MPS
		if (((MM / 100) == 1) || ((MM / 100) == 6))
		{
			for (int i = 0; i < 3; i++)
			{
				tmp[i] = dipHeSysPressureSensor[i * 3].GetVoltage() * 1000;
				if (tmp[i] > 5000) tmp[i] = 5000;
				else if (tmp[i] < 0) tmp[i] = 0;
			}
			sprintf_s( cbuf, 64, "%4.0f  %4.0f  %4.0f", tmp[1], tmp[0], tmp[2] );
			pMDU->mvprint( 12, 14, cbuf );
			if (tmp[1] < 1150) pMDU->DownArrow( 16, 14, dps::DEUATT_OVERBRIGHT );
			if (tmp[0] < 1150) pMDU->DownArrow( 22, 14, dps::DEUATT_OVERBRIGHT );
			if (tmp[2] < 1150) pMDU->DownArrow( 28, 14, dps::DEUATT_OVERBRIGHT );

			for (int i = 0; i < 3; i++)
			{
				tmp[i] = dipHeSysPressureSensor[(i * 3) + 1].GetVoltage() * 200;
				if (tmp[i] > 1000) tmp[i] = 1000;
				else if (tmp[i] < 0) tmp[i] = 0;
			}
			sprintf_s( cbuf, 64, "%4.0f  %4.0f  %4.0f", tmp[1], tmp[0], tmp[2] );
			pMDU->mvprint( 12, 15, cbuf );
			if (tmp[1] < 680) pMDU->DownArrow( 16, 15, dps::DEUATT_OVERBRIGHT );
			else if (tmp[1] > 810) pMDU->UpArrow( 16, 15, dps::DEUATT_OVERBRIGHT );
			if (tmp[0] < 680) pMDU->DownArrow( 22, 15, dps::DEUATT_OVERBRIGHT );
			else if (tmp[0] > 810) pMDU->UpArrow( 22, 15, dps::DEUATT_OVERBRIGHT );
			if (tmp[2] < 680) pMDU->DownArrow( 28, 15, dps::DEUATT_OVERBRIGHT );
			else if (tmp[2] > 810) pMDU->UpArrow( 28, 15, dps::DEUATT_OVERBRIGHT );

			for (int i = 0; i < 3; i++)
			{
				tmp[i] = dipHeSysPressureSensor[(i * 3) + 2].GetVoltage() * 200;
				if (tmp[i] > 1000) tmp[i] = 1000;
				else if (tmp[i] < 0) tmp[i] = 0;
			}
			sprintf_s( cbuf, 64, "%4.0f  %4.0f  %4.0f", tmp[1], tmp[0], tmp[2] );
			pMDU->mvprint( 12, 16, cbuf );
			if (tmp[1] < 680) pMDU->DownArrow( 16, 16, dps::DEUATT_OVERBRIGHT );
			else if (tmp[1] > 810) pMDU->UpArrow( 16, 16, dps::DEUATT_OVERBRIGHT );
			if (tmp[0] < 680) pMDU->DownArrow( 22, 16, dps::DEUATT_OVERBRIGHT );
			else if (tmp[0] > 810) pMDU->UpArrow( 22, 16, dps::DEUATT_OVERBRIGHT );
			if (tmp[2] < 680) pMDU->DownArrow( 28, 16, dps::DEUATT_OVERBRIGHT );
			else if (tmp[2] > 810) pMDU->UpArrow( 28, 16, dps::DEUATT_OVERBRIGHT );

			for (int i = 0; i < 3; i++)
			{
				tmp[i] = He_dPdT[i];
				if (tmp[i] > 50) tmp[i] = 50;
				else if (tmp[i] < 0) tmp[i] = 0;
			}
			sprintf_s( cbuf, 64, "%3.0f   %3.0f   %3.0f", tmp[1], tmp[0], tmp[2] );
			pMDU->mvprint( 13, 17, cbuf );
			if (He_dPdT[1] > 20) pMDU->UpArrow( 16, 17, dps::DEUATT_OVERBRIGHT );
			if (He_dPdT[0] > 20) pMDU->UpArrow( 22, 17, dps::DEUATT_OVERBRIGHT );
			if (He_dPdT[2] > 20) pMDU->UpArrow( 28, 17, dps::DEUATT_OVERBRIGHT );

			tmp[0] = dipHeSysPressureSensor[9].GetVoltage() * 1000;
			if (tmp[0] > 5000) tmp[0] = 5000;
			else if (tmp[0] < 0) tmp[0] = 0;
			sprintf_s( cbuf, 64, "%4.0f", tmp[0] );
			pMDU->mvprint( 40, 19, cbuf );
			if (tmp[0] < 3800) pMDU->DownArrow( 44, 19, dps::DEUATT_OVERBRIGHT );

			tmp[0] = dipHeSysPressureSensor[10].GetVoltage() * 200;
			if (tmp[0] > 1000) tmp[0] = 1000;
			else if (tmp[0] < 0) tmp[0] = 0;
			sprintf_s( cbuf, 64, "%4.0f", tmp[0] );
			pMDU->mvprint( 40, 20, cbuf );
			if (tmp[0] < 700) pMDU->DownArrow( 44, 20, dps::DEUATT_OVERBRIGHT );
			else if (tmp[0] > 810) pMDU->UpArrow( 44, 20, dps::DEUATT_OVERBRIGHT );

			tmp[0] = dipHeSysPressureSensor[11].GetVoltage() * 200;
			if (tmp[0] > 1000) tmp[0] = 1000;
			else if (tmp[0] < 0) tmp[0] = 0;
			sprintf_s( cbuf, 64, "%4.0f", tmp[0] );
			pMDU->mvprint( 40, 21, cbuf );
			if (tmp[0] < 700) pMDU->DownArrow( 44, 21, dps::DEUATT_OVERBRIGHT );

			for (int i = 0; i < 3; i++)
			{
				tmp[i] = (dipLH2UllagePressureSensor[i].GetVoltage() * 8) + 12;

				if (tmp[i] > 52) tmp[i] = 52;
				else if (tmp[i] < 12) tmp[i] = 12;
			}
			sprintf_s( cbuf, 64, "%4.1f  %4.1f  %4.1f", tmp[1], tmp[0], tmp[2] );
			pMDU->mvprint( 12, 19, cbuf );
			if (tmp[1] < 28) pMDU->DownArrow( 16, 19, dps::DEUATT_OVERBRIGHT );
			else if (tmp[1] > 48.9) pMDU->UpArrow( 16, 19, dps::DEUATT_OVERBRIGHT );
			if (tmp[0] < 28) pMDU->DownArrow( 22, 19, dps::DEUATT_OVERBRIGHT );
			else if (tmp[0] > 48.9) pMDU->UpArrow( 22, 19, dps::DEUATT_OVERBRIGHT );
			if (tmp[2] < 28) pMDU->DownArrow( 28, 19, dps::DEUATT_OVERBRIGHT );
			else if (tmp[2] > 48.9) pMDU->UpArrow( 28, 19, dps::DEUATT_OVERBRIGHT );

			for (int i = 0; i < 3; i++)
			{
				tmp[i] = dipLO2UllagePressureSensor[i].GetVoltage() * 10;
				// HACK must convert because sensor is not outputting psig but psia
				tmp[i] -= 14.7;
				if (tmp[i] > 30) tmp[i] = 30;
				else if (tmp[i] < 0) tmp[i] = 0;
			}
			sprintf_s( cbuf, 64, "%4.1f  %4.1f  %4.1f", tmp[1], tmp[0], tmp[2] );
			pMDU->mvprint( 12, 20, cbuf );
			if (tmp[1] < 0) pMDU->DownArrow( 16, 20, dps::DEUATT_OVERBRIGHT );
			else if (tmp[1] > 28) pMDU->UpArrow( 16, 20, dps::DEUATT_OVERBRIGHT );
			if (tmp[0] < 0) pMDU->DownArrow( 22, 20, dps::DEUATT_OVERBRIGHT );
			else if (tmp[0] > 28) pMDU->UpArrow( 22, 20, dps::DEUATT_OVERBRIGHT );
			if (tmp[2] < 0) pMDU->DownArrow( 28, 20, dps::DEUATT_OVERBRIGHT );
			else if (tmp[2] > 28) pMDU->UpArrow( 28, 20, dps::DEUATT_OVERBRIGHT );

			/*sprintf_s( cbuf, 64, "%4.0f  %4.0f  %4.0f", abc, abc, abc );
			pMDU->mvprint( 12, 22, cbuf );
			sprintf_s( cbuf, 64, "%4.0f  %4.0f  %4.0f", abc, abc, abc );
			pMDU->mvprint( 12, 23, cbuf );*/

			tmp[0] = dipMPSManifPressureSensor[1].GetVoltage() * 20;
			if (tmp[0] > 100) tmp[0] = 100;
			else if (tmp[0] < 0) tmp[0] = 0;
			sprintf_s( cbuf, 64, "%3.0f", tmp[0] );
			pMDU->mvprint( 41, 22, cbuf );
			if (tmp[0] > 65) pMDU->UpArrow( 44, 22, dps::DEUATT_OVERBRIGHT );

			tmp[0] = dipMPSManifPressureSensor[0].GetVoltage() * 60;
			if (tmp[0] > 300) tmp[0] = 300;
			else if (tmp[0] < 0) tmp[0] = 0;
			sprintf_s( cbuf, 64, "%3.0f", tmp[0] );
			pMDU->mvprint( 41, 23, cbuf );
			if (tmp[0] > 249) pMDU->UpArrow( 44, 23, dps::DEUATT_OVERBRIGHT );
		}
		return;
	}

	void GeneralDisplays::OnPaint_DISP19_BFS( vc::MDU* pMDU ) const
	{
		PrintCommonHeader( " GNC SYS SUMM 2", pMDU );
		pMDU->mvprint( 34, 1, "BFS", dps::DEUATT_OVERBRIGHT );

		// static parts (labels)
		// OMS
		pMDU->mvprint( 0, 2, "OMS AFT QTY    L     R" );
		pMDU->mvprint( 8, 3, "OXID" );
		pMDU->mvprint( 10, 4, "FU" );
		pMDU->mvprint( 4, 5, "FU INJ T" );
		pMDU->mvprint( 29, 2, "OMS" );
		pMDU->mvprint( 42, 2, "L" );
		pMDU->mvprint( 48, 2, "R" );
		pMDU->mvprint( 30, 3, "TK P   HE" );
		pMDU->mvprint( 35, 4, "OXID" );
		pMDU->mvprint( 37, 5, "FU" );
		pMDU->mvprint( 30, 6, "N2 TK   P" );
		pMDU->mvprint( 33, 7, "REG  P" );
		pMDU->mvprint( 33, 8, "P  VLV" );
		pMDU->mvprint( 29, 9, "ENG IN   P" );
		pMDU->mvprint( 35, 10, "OXID" );
		pMDU->mvprint( 37, 11, "FU" );
		pMDU->mvprint( 34, 12, "VLV 1" );
		pMDU->mvprint( 38, 13, "2" );

		// RCS
		pMDU->mvprint( 20, 6, "JETISOL" );
		pMDU->mvprint( 0, 7, "RCS       OXID  FU FAIL VLV" );
		pMDU->mvprint( 0, 8, "FWD  HE P" );
		pMDU->mvprint( 5, 9, "TK P" );
		pMDU->mvprint( 6, 10, "QTY" );
		pMDU->mvprint( 0, 11, "MANF  1 P" );
		pMDU->mvprint( 6, 12, "2 P" );
		pMDU->mvprint( 6, 13, "3 P" );
		pMDU->mvprint( 6, 14, "4 P" );
		pMDU->mvprint( 6, 15, "5" );
		pMDU->mvprint( 0, 16, "AFT  HE P" );
		pMDU->mvprint( 0, 17, "L    TK P" );
		pMDU->mvprint( 6, 18, "QTY" );
		pMDU->mvprint( 0, 19, "MANF  1 P" );
		pMDU->mvprint( 6, 20, "2 P" );
		pMDU->mvprint( 6, 21, "3 P" );
		pMDU->mvprint( 6, 22, "4 P" );
		pMDU->mvprint( 6, 23, "5" );
		pMDU->mvprint( 44, 14, "JETISOL" );
		pMDU->mvprint( 34, 15, "OXID  FU FAIL VLV" );
		pMDU->mvprint( 29, 16, "HE P" );
		pMDU->mvprint( 27, 17, "R TK P" );
		pMDU->mvprint( 30, 18, "QTY" );
		pMDU->mvprint( 30, 19, "1 P" );
		pMDU->mvprint( 30, 20, "2 P" );
		pMDU->mvprint( 30, 21, "3 P" );
		pMDU->mvprint( 30, 22, "4 P" );
		pMDU->mvprint( 30, 23, "5" );


		// static parts (lines)
		pMDU->Line( 90, 84, 90, 336 );
		pMDU->Line( 140, 84, 140, 336 );
		pMDU->Line( 190, 84, 190, 336 );
		pMDU->Line( 230, 84, 230, 336 );
		pMDU->Line( 270, 84, 270, 336 );
		pMDU->Line( 330, 196, 330, 336 );
		pMDU->Line( 380, 196, 380, 336 );
		pMDU->Line( 430, 196, 430, 336 );
		pMDU->Line( 470, 196, 470, 336 );
		pMDU->Line( 0, 84, 270, 84 );
		pMDU->Line( 0, 112, 270, 112 );
		pMDU->Line( 60, 154, 190, 154 );
		pMDU->Line( 270, 196, 510, 196 );
		pMDU->Line( 0, 224, 510, 224 );
		pMDU->Line( 60, 266, 190, 266 );
		pMDU->Line( 300, 266, 430, 266 );


		// TODO dynamic parts
		return;
	}

	void GeneralDisplays::OnPaint_SPEC51_BFS( vc::MDU* pMDU ) const
	{
		PrintCommonHeader( "    OVERRIDE", pMDU );
		pMDU->mvprint( 34, 1, "BFS", dps::DEUATT_OVERBRIGHT );

		// static parts (labels)
		// ABORT MODE
		pMDU->mvprint( 0, 2, "ABORT MODE" );
		pMDU->mvprint( 1, 3, "TAL" );
		pMDU->mvprint( 10, 3, "1" );
		pMDU->mvprint( 1, 4, "ATO" );
		pMDU->mvprint( 10, 4, "2" );
		pMDU->mvprint( 0, 5, "ABORT     3" );
		pMDU->mvprint( 0, 6, "THROT MAX 4" );
		pMDU->mvprint( 6, 7, "ABT 50" );
		pMDU->mvprint( 6, 8, "NOM 51" );

		// ENTRY FCS
		pMDU->mvprint( 29, 2, "ENTRY FCS" );
		pMDU->mvprint( 18, 3, "ELEVON    FILTER    ATMOSPHERE" );
		pMDU->mvprint( 16, 4, "AUTO  17    NOM 20    NOM    22" );
		pMDU->mvprint( 16, 5, "FIXED 18    ALT 21    N POLE 23" );
		pMDU->mvprint( 18, 6, "SSME REPOS 19       S POLE 24" );

		// IMU
		pMDU->mvprint( 17, 8, "IMU DES ATT" );
		pMDU->mvprint( 18, 9, "1  25" );
		pMDU->mvprint( 18, 10, "2  26" );
		pMDU->mvprint( 18, 11, "3  27" );

		// AA RGA SURF
		pMDU->mvprint( 33, 8, "AA    RGA  SURF" );
		pMDU->mvprint( 29, 9, "LRU DES   DES  DES" );
		pMDU->mvprint( 30, 10, "1  31" );
		pMDU->mvprint( 39, 10, "35   39" );
		pMDU->mvprint( 30, 11, "2  32" );
		pMDU->mvprint( 39, 11, "36   40" );
		pMDU->mvprint( 30, 12, "3  33" );
		pMDU->mvprint( 39, 12, "37   41" );
		pMDU->mvprint( 30, 13, "4  34" );
		pMDU->mvprint( 39, 13, "38   42" );

		// PRPLT DUMP
		pMDU->mvprint( 3, 9, "PRPLT DUMP" );
		pMDU->mvprint( 4, 10, "ICNCT 5" );
		pMDU->mvprint( 0, 11, "OMS DUMP" );
		pMDU->mvprint( 3, 12, "ARM    6" );
		pMDU->mvprint( 3, 13, "START  7" );
		pMDU->mvprint( 3, 14, "STOP   8" );
		pMDU->mvprint( 1, 15, "9 QUAN/SIDE" );
		pMDU->mvprint( 0, 16, "OMS DUMP TTG" );

		// ET SEP
		pMDU->mvprint( 18, 13, "ET SEP" );
		pMDU->mvprint( 20, 14, "AUTO  28" );
		pMDU->mvprint( 20, 15, "SEP   29" );

		// ROLL MODE
		pMDU->mvprint( 34, 15, "ROLL MODE" );
		pMDU->mvprint( 35, 16, "WRAP MODE 45" );

		// ET UMB DR
		pMDU->mvprint( 18, 17, "ET UMB  DR" );
		pMDU->mvprint( 20, 18, "CLOSE 30" );

		// AFT RCS
		pMDU->mvprint( 0, 18, "AFT RCS 13" );
		pMDU->mvprint( 3, 19, "14 TIME" );

		// COMM
		pMDU->mvprint( 39, 18, "COMM" );
		pMDU->mvprint( 40, 19, "TDRS    46" );
		pMDU->mvprint( 40, 20, "STDN-HI 47" );
		pMDU->mvprint( 40, 21, "STDN-LO 48" );
		pMDU->mvprint( 40, 22, "SGLS    49" );

		// VENT DOOR CNTL
		pMDU->mvprint( 18, 20, "VENT DOOR CNTL" );
		pMDU->mvprint( 20, 21, "OPEN  43" );
		pMDU->mvprint( 20, 22, "CLOSE 44" );

		// FWD RCS
		pMDU->mvprint( 0, 21, "FWD RCS 15" );
		pMDU->mvprint( 3, 22, "16 TIME" );

		// dynamic parts
		switch (GetMajorMode())
		{
			case 102:
			case 103:
			case 601:
				{
					unsigned short kmaxsel = ReadCOMPOOL_IS( SCP_KMAX_SEL );
					if (kmaxsel == 1) pMDU->mvprint( 11, 6, "*" );
					else if (kmaxsel == 2) pMDU->mvprint( 12, 7, "*" );
					else if (kmaxsel == 0) pMDU->mvprint( 12, 8, "*" );
				}
				break;
		}

		if (GetMajorMode() / 100 == 3)
		{
			switch (ReadCOMPOOL_IS( SCP_WRAP ))
			{
				case 0:
					pMDU->mvprint( 48, 19, "INH" );
					break;
				case 1:
					pMDU->mvprint( 48, 19, "ENA" );
					break;
				case 2:
					pMDU->mvprint( 48, 19, "ACT" );
					break;
			}
		}
		return;
	}

	void GeneralDisplays::OnPaint_SPEC55_BFS( vc::MDU* pMDU ) const
	{
		PrintCommonHeader( "    GPS STATUS", pMDU );
		pMDU->mvprint( 34, 1, "BFS", dps::DEUATT_OVERBRIGHT );

		// static parts (labels)
		pMDU->mvprint( 9, 2, "GPS1  GPS2  GPS3" );
		pMDU->mvprint( 0, 3, "STAT" );
		pMDU->mvprint( 0, 4, "MODE" );
		pMDU->mvprint( 0, 6, "INIT" );
		pMDU->mvprint( 10, 6, "14" );
		pMDU->mvprint( 16, 6, "15" );
		pMDU->mvprint( 22, 6, "16" );
		pMDU->mvprint( 0, 8, "RESTART   20    21    22" );

		pMDU->mvprint( 33, 3, "GPS MINUS NAV" );
		pMDU->Delta( 28, 4 );
		pMDU->mvprint( 29, 4, "H" );
		pMDU->Delta( 40, 4 );
		pMDU->mvprint( 41, 4, "H" );
		pMDU->DotCharacter( 41, 4 );
		pMDU->Delta( 28, 5 );
		pMDU->mvprint( 29, 5, "DR" );
		pMDU->Delta( 40, 5 );
		pMDU->mvprint( 41, 5, "DR" );
		pMDU->DotCharacter( 41, 5 );
		pMDU->Delta( 28, 6 );
		pMDU->mvprint( 29, 6, "CR" );
		pMDU->Delta( 40, 6 );
		pMDU->mvprint( 41, 6, "CR" );
		pMDU->DotCharacter( 41, 6 );
		pMDU->mvprint( 30, 8, "LAT" );
		pMDU->mvprint( 38, 8, "LON" );
		pMDU->mvprint( 46, 8, "ALT" );

		pMDU->mvprint( 0, 11, "DG FAIL" );
		pMDU->mvprint( 0, 12, "DES RCVR  26    27    28" );
		pMDU->mvprint( 0, 13, "QA1 OVRD  29    30    31" );
		pMDU->mvprint( 0, 15, "QA1 P 1" );
		pMDU->Sigma( 7, 15 );

		pMDU->mvprint( 28, 15, "GPS TIME ADJUST ENA 39" );

		pMDU->mvprint( 34, 16, "SATELLITES" );
		pMDU->mvprint( 28, 17, "TRKD  C1 C2 C3 C4 C5 C6" );
		pMDU->mvprint( 29, 18, "GPS1" );
		pMDU->mvprint( 29, 19, "GPS2" );
		pMDU->mvprint( 29, 20, "GPS3" );
		pMDU->mvprint( 28, 22, "DES 43" );


		// static parts (lines)
		pMDU->Line( 140, 28, 140, 336 );
		pMDU->Line( 200, 28, 200, 336 );
		pMDU->Line( 260, 28, 260, 336 );
		pMDU->Line( 0, 154, 510, 154 );
		pMDU->Line( 260, 224, 510, 224 );
		pMDU->Line( 0, 280, 260, 280 );


		// TODO dynamic parts
		return;
	}

	void GeneralDisplays::OnPaint_DISP99_BFS( vc::MDU* pMDU ) const
	{
		PrintCommonHeader( "    FAULT", pMDU );
		pMDU->mvprint( 34, 1, "BFS", dps::DEUATT_OVERBRIGHT );

		// static parts (labels)
		pMDU->mvprint( 4, 5, "CRT" );
		pMDU->mvprint( 13, 5, "FAULT      C/W   GPC      TIME" );
		pMDU->mvprint( 4, 6, "ID" );
		return;
	}

	void GeneralDisplays::OnPaint_LAUNCHTRAJ1_PASS( vc::MDU* pMDU ) const// OI-32 PASS LAUNCH TRAJ 1
	{
		PrintCommonHeader( "  LAUNCH TRAJ 1", pMDU );

		// static parts (labels)
		pMDU->mvprint( 7, 5, "CONT ABORT" );
		pMDU->mvprint( 8, 6, "3EO BLUE" );
		pMDU->mvprint( 1, 7, "2  ARM 2EO BLUE" );
		pMDU->mvprint( 1, 8, "4  ABORT" );
		pMDU->mvprint( 1, 10, "5 INH YAW STEER" );
		pMDU->mvprint( 1, 12, "6  SERC" );
		pMDU->mvprint( 38, 17, "THROT" );
		pMDU->mvprint( 18, 22, "7 INH DRP 1EO" );

		pMDU->mvprint( 31, 15, "40" );
		pMDU->mvprint( 24, 18, "50" );
		pMDU->mvprint( 19, 20, "60" );
		pMDU->mvprint( 11, 23, "70" );

		// static parts (lines)
		pMDU->Line( 78, 324, 116, 317 );
		pMDU->Line( 116, 317, 159, 302 );
		pMDU->Line( 159, 302, 217, 257 );
		pMDU->Line( 217, 257, 355, 174 );
		pMDU->Line( 355, 174, 438, 119 );
		pMDU->Line( 438, 119, 455, 97 );
		pMDU->Line( 455, 97, 471, 58 );

		pMDU->Line( 322, 189, 322, 200 );
		pMDU->Line( 254, 230, 254, 241 );
		pMDU->Line( 196, 267, 196, 278 );
		pMDU->Line( 116, 313, 116, 324 );
		return;
	}

	void GeneralDisplays::OnPaint_ASCENTTRAJ1_PASS( vc::MDU* pMDU ) const// OI-32 PASS ASCENT TRAJ 1
	{
		PrintCommonHeader( "  ASCENT TRAJ 1", pMDU );

		// static parts (labels)
		pMDU->mvprint( 7, 5, "CONT ABORT" );
		pMDU->mvprint( 8, 6, "3EO BLUE" );
		pMDU->mvprint( 1, 7, "2  ARM 2EO BLUE" );
		pMDU->mvprint( 1, 8, "4  ABORT" );
		pMDU->mvprint( 1, 10, "5 INH YAW STEER" );
		pMDU->mvprint( 1, 12, "6  SERC" );
		pMDU->mvprint( 38, 17, "THROT" );
		pMDU->mvprint( 18, 22, "7 INH DRP 1EO" );

		pMDU->mvprint( 31, 15, "40" );
		pMDU->mvprint( 24, 18, "50" );
		pMDU->mvprint( 19, 20, "60" );
		pMDU->mvprint( 11, 23, "70" );

		// static parts (lines)
		pMDU->Line( 78, 324, 116, 317 );
		pMDU->Line( 116, 317, 159, 302 );
		pMDU->Line( 159, 302, 217, 257 );
		pMDU->Line( 217, 257, 355, 174 );
		pMDU->Line( 355, 174, 438, 119 );
		pMDU->Line( 438, 119, 455, 97 );
		pMDU->Line( 455, 97, 471, 58 );

		pMDU->Line( 322, 189, 322, 200 );
		pMDU->Line( 254, 230, 254, 241 );
		pMDU->Line( 196, 267, 196, 278 );
		pMDU->Line( 116, 313, 116, 324 );

		// dynamic parts
		char cbuf[64];

		sprintf_s( cbuf, 64, "%3d", (int)pAscentDAP->GetAutoThrottleCommand() );
		pMDU->mvprint( 44, 17, cbuf );

		if (pSRBSepSequence->GetLHRHSRBPC50PSIFlag() == true) pMDU->mvprint( 22, 9, "PC<50", dps::DEUATT_OVERBRIGHT | dps::DEUATT_FLASHING );

		//if (pSRBSepSequence->GetSRBSEPINHFlag() == true) pMDU->mvprint( 10, 11, "SEP INH" );

		if (pAscentDAP->SERCenabled() == true) pMDU->mvprint( 9, 12, "ON", dps::DEUATT_OVERBRIGHT );

		if (pAscentDAP->GetEOVI( 1 ) != 0)
		{
			sprintf_s( cbuf, 64, "1ST EO VI %5.0f", pAscentDAP->GetEOVI( 1 ) );
			pMDU->mvprint( 34, 22, cbuf );
		}
		if (pAscentDAP->GetEOVI( 2 ) != 0)
		{
			sprintf_s( cbuf, 64, "2ND EO VI %5.0f", pAscentDAP->GetEOVI( 2 ) );
			pMDU->mvprint( 34, 23, cbuf, dps::DEUATT_OVERBRIGHT );
		}

		double VR = STS()->GetAirspeed() * MPS2FPS;
		double Altitude = STS()->GetAltitude() * MPS2FPS;

		//Draw triangle for state vector
		short stY = static_cast<short>(324 - (Altitude * 0.00164198));
		short stX = static_cast<short>(78 + (VR * 0.0930909));
		pMDU->Line( stX, stY - 6, stX - 6, stY + 6, dps::DEUATT_OVERBRIGHT );
		pMDU->Line( stX - 6, stY + 6, stX + 6, stY + 6, dps::DEUATT_OVERBRIGHT );
		pMDU->Line( stX + 6, stY + 6, stX, stY - 6, dps::DEUATT_OVERBRIGHT );

		VECTOR3 thr;
		STS()->GetThrustVector( thr );
		thr /= STS()->GetMass();
		VECTOR3 LVLH_Vel;
		GetGPCLVLHVel( LVLH_Vel );
		double AOA = STS()->GetAOA();
		double Pitch = STS()->GetPitch();
		// 20s predictor
		VR += (length( thr ) * cos( -AOA - atan( thr.y / thr.z ) ) - G * sin( PI - Pitch - AOA )) * 20 * MPS2FPS;
		Altitude += -LVLH_Vel.z * 20 + ((length( thr ) * sin( Pitch + atan( thr.y / thr.z ) ) - G) * 400) * MPS2FPS;
		if (VR < 0) VR = 0;
		if (Altitude < 0) Altitude = 0;
		stY = static_cast<short>(324 - (Altitude * 0.00164198));
		stX = static_cast<short>(78 + (VR * 0.0930909));
		pMDU->Ellipse( stX - 6, stY - 6, stX + 6, stY + 6, dps::DEUATT_OVERBRIGHT );
		return;
	}

	void GeneralDisplays::OnPaint_ASCENTTRAJ2_PASS( vc::MDU* pMDU ) const// OI-32 PASS ASCENT TRAJ 2
	{
		PrintCommonHeader( "  ASCENT TRAJ 2", pMDU );

		// static parts (labels)
		pMDU->mvprint( 9, 4, "25" );
		pMDU->mvprint( 49, 4, "26" );
		pMDU->mvprint( 38, 5, "TGO   :" );
		pMDU->mvprint( 7, 5, "CONT ABORT" );
		pMDU->mvprint( 8, 6, "3EO" );
		pMDU->mvprint( 1, 7, "2  ARM 2EO" );
		pMDU->mvprint( 1, 8, "4  ABORT" );
		pMDU->mvprint( 1, 10, "5 INH YAW STEER" );
		pMDU->mvprint( 1, 12, "6  SERC" );
		pMDU->mvprint( 38, 17, "THROT" );
		pMDU->mvprint( 38, 18, "PRPLT" );
		pMDU->mvprint( 38, 20, "TMECO   :" );
		pMDU->mvprint( 19, 19, "DROOP ALT   8" );
		pMDU->mvprint( 18, 22, "7     DRP 1EO" );


		// static parts (lines)
		//Nominal ascent line
		pMDU->Line( 116, 289, 126, 257 );
		pMDU->Line( 126, 257, 136, 236 );
		pMDU->Line( 136, 236, 146, 218 );
		pMDU->Line( 146, 218, 166, 196 );
		pMDU->Line( 166, 196, 196, 179 );
		pMDU->Line( 196, 179, 212, 173 );
		pMDU->Line( 212, 173, 242, 168 );
		pMDU->Line( 242, 168, 272, 168 );
		pMDU->Line( 272, 168, 376, 177 );
		pMDU->Line( 376, 177, 450, 180 );
		pMDU->Line( 450, 180, 496, 179 );

		pMDU->Line( 270, 151, 322, 159 );
		pMDU->Line( 322, 159, 388, 166 );
		pMDU->Line( 388, 166, 468, 166 );

		// Vr line
		pMDU->Line( 100, 48, 498, 48 );
		// 25K mark
		pMDU->Line( 100, 48, 100, 56 );
		// 26K mark
		pMDU->Line( 498, 48, 498, 56 );

		// dynamic parts
		char cbuf[64];
		int tmp = 0;
		double TgtSpd = pAscentDAP->GetTgtSpd() * MPS2FPS;
		double inertialVelocity = pAscentDAP->GetInertialVelocity() * MPS2FPS;

		// Vr scale
		// HACK retains pre OI-32 BFS display implementation, as no info exists for post OI-32 PASS display
		// CO mark
		pMDU->Line( 379, 48, 379, 56 );
		pMDU->mvprint( 37, 4, "CO" );

		// triangle
		tmp = static_cast<int>(range( 100, Round( (((inertialVelocity - (TgtSpd - 700.0))) * 0.398) ) + 100, 498 ));
		pMDU->Line( tmp, 47, tmp - 6, 39, dps::DEUATT_OVERBRIGHT );
		pMDU->Line( tmp - 6, 39, tmp + 6, 39, dps::DEUATT_OVERBRIGHT );
		pMDU->Line( tmp + 6, 39, tmp, 47, dps::DEUATT_OVERBRIGHT );


		sprintf_s( cbuf, 64, "%3d", (int)pAscentDAP->GetAutoThrottleCommand() );
		pMDU->mvprint( 44, 17, cbuf );

		tmp = STS()->GetETPropellant();
		if (tmp < 0) tmp = 0;
		sprintf_s( cbuf, 64, "%2d", tmp );
		pMDU->mvprint( 44, 18, cbuf );

		// contigency abort boundaries
		// 3EO
		if (inertialVelocity < 18000.0) pMDU->mvprint( 12, 6, "GREEN" );
		// 2EO
		if (inertialVelocity < 12100.0)
		{
			VECTOR3 vr3;
			STS()->GetAirspeedVector( FRAME_HORIZON, vr3 );
			if ((vr3.y * MPS2FPS) < 1850) pMDU->mvprint( 12, 7, "GREEN" );
			else pMDU->mvprint( 13, 7, "BLUE" );
		}

		//if (pETSepSequence->GetETSEPINHFlag() == true) pMDU->mvprint( 10, 11, "SEP INH" );

		if (pAscentDAP->SERCenabled() == true) pMDU->mvprint( 9, 12, "ON", dps::DEUATT_OVERBRIGHT );

		if (pAscentDAP->GetEOVI( 1 ) != 0)
		{
			sprintf_s( cbuf, 64, "1ST EO VI %5.0f", pAscentDAP->GetEOVI( 1 ) );
			pMDU->mvprint( 34, 22, cbuf );
		}
		if (pAscentDAP->GetEOVI( 2 ) != 0)
		{
			sprintf_s( cbuf, 64, "2ND EO VI %5.0f", pAscentDAP->GetEOVI( 2 ) );
			pMDU->mvprint( 34, 23, cbuf, dps::DEUATT_OVERBRIGHT );
		}
		else pMDU->mvprint( 20, 22, "INH" );

		if ((pSSME_Operations->GetMECOConfirmedFlag() == false) && (pSSME_Operations->GetMECOCommandFlag() == false))
		{
			// TGO
			double timeRemaining = pAscentDAP->GetTimeRemaining();
			tmp = Round( timeRemaining );
			sprintf_s( cbuf, 64, "%2d", (tmp - (tmp % 60)) / 60 );
			pMDU->mvprint( 42, 5, cbuf );
			sprintf_s( cbuf, 64, "%02d", (tmp % 60) );
			pMDU->mvprint( 45, 5, cbuf );
			// TMECO
			tmp = Round( STS()->GetMET() + timeRemaining );
			sprintf_s( cbuf, 64, "%2d", (tmp - (tmp % 60)) / 60 );
			pMDU->mvprint( 44, 20, cbuf );
			sprintf_s( cbuf, 64, "%02d", (tmp % 60) );
			pMDU->mvprint( 47, 20, cbuf );

			double droopH = DROOP_ALT;// TODO
			char att = 0;
			if (droopH < DROOP_ALT) att = dps::DEUATT_FLASHING;
			sprintf_s( cbuf, 64, "DROOP ALT %3.0f", droopH * 0.001 );
			pMDU->mvprint( 19, 19, cbuf, att );
		}

		VECTOR3 LVLH_Vel;
		GetGPCLVLHVel( LVLH_Vel );

		//Current vehicle state (57NM insertion altitude):
		double VHI = LVLH_Vel.x;
		double Altitude = STS()->GetAltitude() * MPS2FPS;
		//Draw triangle for state vector
		short stY = static_cast<short>(490.558404 - (Altitude * 0.000997152));
		short stX = static_cast<short>(VHI * 0.0204);
		pMDU->Line( stX, stY - 6, stX - 6, stY + 6, dps::DEUATT_OVERBRIGHT );
		pMDU->Line( stX - 6, stY + 6, stX + 6, stY + 6, dps::DEUATT_OVERBRIGHT );
		pMDU->Line( stX + 6, stY + 6, stX, stY - 6, dps::DEUATT_OVERBRIGHT );

		// HACK using constant 12º for SSME offset
		// 30s predictor
		double earthR = 20902200;//6371010 * MPS2FPS;
		double thrustAcceleration = pAscentDAP->GetThrustAcceleration();
		double dv30 = thrustAcceleration * cos( STS()->GetSlipAngle() ) * 30 * MPS2FPS;
		VHI += dv30;
		Altitude += -LVLH_Vel.z * 30 + (((thrustAcceleration * sin( STS()->GetPitch() - (12 * RAD * sign( cos( STS()->GetBank() ) )) )) - G ) * 450 * MPS2FPS);
		//Draw circle for 30s predictor
		//stY = static_cast<short>(315.358974 - (Altitude * 0.000641026));
		stY = static_cast<short>(490.558404 - ((Altitude + sqrt(earthR * earthR + VHI * VHI * 900) - earthR) * 0.000997152));
		stX = static_cast<short>(VHI * 0.0204);
		pMDU->Ellipse( stX - 6, stY - 6, stX + 6, stY + 6, dps::DEUATT_OVERBRIGHT );

		// 60s predictor
		VHI += dv30;
		Altitude = (STS()->GetAltitude() * MPS2FPS) - (LVLH_Vel.z * 60) + ((thrustAcceleration * sin( STS()->GetPitch() - (12 * RAD * sign( cos( STS()->GetBank() ) )) )) - G ) * 1800 * MPS2FPS;
		//Draw circle for 60s predictor
		//stY = static_cast<short>(315.358974 - (Altitude * 0.000641026));
		stY = static_cast<short>(490.558404 - ((Altitude + sqrt(earthR * earthR + VHI * VHI * 3600) - earthR) * 0.000997152));
		stX = static_cast<short>(VHI * 0.0204);
		pMDU->Ellipse( stX - 6, stY - 6, stX + 6, stY + 6, dps::DEUATT_OVERBRIGHT );
		return;
	}

	void GeneralDisplays::OnPaint_ENTRYTRAJ1_PASS( vc::MDU* pMDU ) const
	{
		char cbuf[8];
		double DELAZ = ReadCOMPOOL_SD( SCP_DELAZ ) * DEG;
		unsigned short ISLECT = ReadCOMPOOL_IS( SCP_ISLECT );
		bool rrflash = ((DELAZ * ReadCOMPOOL_SD( SCP_PHI )) > 0.0) && (fabs( DELAZ ) >= (ReadCOMPOOL_SD( SCP_YL ) * DEG)) && (ISLECT > 1);
		char att = dps::DEUATT_NORMAL;

		PrintCommonHeader( "  ENTRY TRAJ 1", pMDU );

		pMDU->Alpha( 1, 1 );
		pMDU->mvprint( 0, 2, "50" );
		pMDU->mvprint( 0, 6, "45" );
		pMDU->mvprint( 0, 10, "40" );
		pMDU->mvprint( 0, 14, "35" );
		pMDU->mvprint( 0, 18, "30" );
		pMDU->mvprint( 0, 22, "25" );
		pMDU->mvprint( 4, 1, "D" );
		pMDU->mvprint( 4, 2, "50" );
		pMDU->mvprint( 4, 6, "40" );
		pMDU->mvprint( 4, 10, "30" );
		pMDU->mvprint( 4, 14, "20" );
		pMDU->mvprint( 4, 18, "10" );
		pMDU->mvprint( 4, 22, "0" );
		pMDU->mvprint( 7, 4, "1 BIAS" );
		pMDU->mvprint( 7, 5, "D REF" );
		pMDU->mvprint( 7, 6, "q" );
		pMDU->Line( 70, 84, 80, 84 );
		pMDU->Delta( 7, 7 );
		pMDU->mvprint( 9, 7, "AZ" );
		//pMDU->mvprint( 7, 9, "LO ENRGY" );
		//pMDU->mvprint( 7, 10, "3" );
		pMDU->mvprint( 38, 15, "NY" );
		pMDU->mvprint( 38, 16, "NY TRIM" );
		pMDU->mvprint( 38, 17, "AIL" );
		pMDU->mvprint( 38, 18, "RUD" );
		pMDU->mvprint( 37, 19, "ZERO H BIAS 2" );
		pMDU->DotCharacter( 42, 19 );
		pMDU->mvprint( 38, 20, "H BIAS" );
		pMDU->DotCharacter( 38, 20 );
		pMDU->mvprint( 41, 21, "REF" );
		pMDU->mvprint( 36, 22, "ROLL REF" );
		pMDU->mvprint( 41, 23, "CMD" );
		pMDU->mvprint( 34, 2, "10D" );
		pMDU->mvprint( 40, 2, "8D" );
		pMDU->mvprint( 46, 2, "6D" );
		pMDU->mvprint( 23, 6, "15D" );
		pMDU->mvprint( 16, 9, "20D" );
		pMDU->mvprint( 10, 14, "25D" );
		pMDU->mvprint( 41, 13, "-40" );
		pMDU->mvprint( 30, 18, "-70" );
		pMDU->mvprint( 4, 23, "-180" );
		pMDU->mvprint( 19, 23, "-100" );

		// phugoid scale lines
		if (rrflash) att = dps::DEUATT_FLASHING;
		else att = dps::DEUATT_NORMAL;
		pMDU->Line( 70, 30, 250, 30, att );
		pMDU->Line( 70, 30, 70, 36, att );
		pMDU->Line( 160, 30, 160, 36, att );
		pMDU->Line( 250, 30, 250, 36, att );

		// alpha/D scale lines
		pMDU->Line( 34, 34, 34, 314 );
		pMDU->Line( 30, 34, 38, 34 );
		pMDU->Line( 30, 45, 38, 45 );
		pMDU->Line( 30, 56, 38, 56 );
		pMDU->Line( 30, 68, 38, 68 );
		pMDU->Line( 30, 79, 38, 79 );
		pMDU->Line( 30, 90, 38, 90 );
		pMDU->Line( 30, 101, 38, 101 );
		pMDU->Line( 30, 112, 38, 112 );
		pMDU->Line( 30, 124, 38, 124 );
		pMDU->Line( 30, 135, 38, 135 );
		pMDU->Line( 30, 146, 38, 146 );
		pMDU->Line( 30, 157, 38, 157 );
		pMDU->Line( 30, 168, 38, 168 );
		pMDU->Line( 30, 180, 38, 180 );
		pMDU->Line( 30, 191, 38, 191 );
		pMDU->Line( 30, 202, 38, 202 );
		pMDU->Line( 30, 213, 38, 213 );
		pMDU->Line( 30, 224, 38, 224 );
		pMDU->Line( 30, 236, 38, 236 );
		pMDU->Line( 30, 247, 38, 247 );
		pMDU->Line( 30, 258, 38, 258 );
		pMDU->Line( 30, 269, 38, 269 );
		pMDU->Line( 30, 280, 38, 280 );
		pMDU->Line( 30, 292, 38, 292 );
		pMDU->Line( 30, 303, 38, 303 );
		pMDU->Line( 30, 314, 38, 314 );

		// vel/rng lines
		pMDU->Line( 348, 48, 174, 176 );
		pMDU->Line( 174, 176, 50, 308 );

		pMDU->Line( 394, 45, 192, 190 );
		pMDU->Line( 192, 190, 50, 308 );

		pMDU->Line( 444, 50, 204, 202 );
		pMDU->Line( 204, 202, 74, 311 );

		pMDU->Line( 488, 54, 178, 246 );
		pMDU->Line( 178, 246, 110, 308 );

		pMDU->Line( 508, 120, 282, 205 );
		pMDU->Line( 282, 205, 176, 277 );
		pMDU->Line( 176, 277, 150, 308 );

		// drag lines
		pMDU->Line( 110, 210, 70, 313, dps::DEUATT_DASHED );

		pMDU->Line( 170, 142, 118, 269, dps::DEUATT_DASHED );
		pMDU->Line( 118, 269, 90, 305, dps::DEUATT_DASHED );

		pMDU->Line( 244, 100, 182, 314, dps::DEUATT_DASHED );

		pMDU->Line( 350, 40, 298, 142, dps::DEUATT_DASHED );
		pMDU->Line( 298, 142, 298, 238, dps::DEUATT_DASHED );

		pMDU->Line( 412, 45, 406, 75, dps::DEUATT_DASHED );
		pMDU->Line( 406, 75, 372, 143, dps::DEUATT_DASHED );
		pMDU->Line( 372, 143, 374, 199, dps::DEUATT_DASHED );

		pMDU->Line( 476, 39, 424, 140, dps::DEUATT_DASHED );
		pMDU->Line( 424, 140, 424, 176, dps::DEUATT_DASHED );

		// digital data
		sprintf_s( cbuf, 8, "%5.1f", ReadCOMPOOL_SD( SCP_QBAR ) );
		pMDU->mvprint( 12, 6, cbuf );

		sprintf_s( cbuf, 8, "%+5.1f", DELAZ );
		pMDU->mvprint( 12, 7, cbuf );

		ENTRYTRAJ_PrintTrimGuidanceParams( pMDU, ReadCOMPOOL_SD( SCP_NY ), ReadCOMPOOL_SD( SCP_DRTI ), ReadCOMPOOL_SD( SCP_DATRIM ), ReadCOMPOOL_SD( SCP_DRTRIM ), ReadCOMPOOL_SD( SCP_DLRDOT ), ReadCOMPOOL_SD( SCP_RDTREF ), ReadCOMPOOL_SD( SCP_ROLLREF ), ReadCOMPOOL_SD( SCP_ROLLCMD ) );

		// scale data
		att = dps::DEUATT_OVERBRIGHT;
		double ALPHA = ReadCOMPOOL_SD( SCP_ALPHA );
		double ACMD1 = ReadCOMPOOL_SD( SCP_ACMD1 );
		if (fabs( ALPHA - ACMD1 ) > 2.0) att |= dps::DEUATT_FLASHING;
		int pos;
		if (ALPHA > 50.0)
		{
			pos = 34;
			att |= dps::DEUATT_FLASHING;
		}
		else if (ALPHA < 25.0)
		{
			pos = 314;
			att |= dps::DEUATT_FLASHING;
		}
		else pos = 594 - Round( 11.2 * ALPHA );
		pMDU->Line( 33, pos, 25, pos + 6, att );
		pMDU->Line( 25, pos + 6, 25, pos - 6, att );
		pMDU->Line( 25, pos - 6, 33, pos, att );

		att = dps::DEUATT_OVERBRIGHT;
		if (ACMD1 > 50.0)
		{
			pos = 34;
			att |= dps::DEUATT_FLASHING;
		}
		else if (ACMD1 < 25.0)
		{
			pos = 314;
			att |= dps::DEUATT_FLASHING;
		}
		else pos = 594 - Round( 11.2 * ACMD1 );
		pMDU->Line( 33, pos, 27, pos + 6, att );
		pMDU->Line( 27, pos + 6, 27, pos + 2, att );
		pMDU->Line( 27, pos + 2, 15, pos + 2, att );
		pMDU->Line( 15, pos + 2, 15, pos - 2, att );
		pMDU->Line( 15, pos - 2, 27, pos - 2, att );
		pMDU->Line( 27, pos - 2, 27, pos - 6, att );
		pMDU->Line( 27, pos - 6, 33, pos, att );

		att = dps::DEUATT_OVERBRIGHT;
		double DRAG = ReadCOMPOOL_SD( SCP_DRAG );
		if (DRAG > 50.0)
		{
			pos = 34;
			att |= dps::DEUATT_FLASHING;
		}
		else if (DRAG < 0.0)
		{
			pos = 314;
			att |= dps::DEUATT_FLASHING;
		}
		else pos = 314 - Round( 5.6 * DRAG );
		pMDU->Line( 35, pos, 43, pos + 6, att );
		pMDU->Line( 43, pos + 6, 43, pos - 6, att );
		pMDU->Line( 43, pos - 6, 35, pos, att );

		if (ISLECT > 1)
		{
			att = dps::DEUATT_OVERBRIGHT;
			double DREFP = ReadCOMPOOL_SD( SCP_DREFP );
			if (DREFP > 50.0)
			{
				pos = 34;
				att |= dps::DEUATT_FLASHING;
			}
			else if (DREFP < 0.0)
			{
				pos = 314;
				att |= dps::DEUATT_FLASHING;
			}
			else pos = 314 - Round( 5.6 * DREFP );
			pMDU->Line( 35, pos, 41, pos + 6, att );
			pMDU->Line( 41, pos + 6, 41, pos + 2, att );
			pMDU->Line( 41, pos + 2, 53, pos + 2, att );
			pMDU->Line( 53, pos + 2, 53, pos - 2, att );
			pMDU->Line( 53, pos - 2, 41, pos - 2, att );
			pMDU->Line( 41, pos - 2, 41, pos - 6, att );
			pMDU->Line( 41, pos - 6, 35, pos, att );
		}

		// orbiter symbol
		att = dps::DEUATT_OVERBRIGHT;
		if (rrflash) att |= dps::DEUATT_FLASHING;
		pMDU->OrbiterSymbolSide( ET_History_X[0], ET_History_Y[0], 0, att );

		// drag symbol
		if (ISLECT > 1) pMDU->Square( ET_History_X_Drag[0], ET_History_Y[0] );

		// orbiter and drag trailers
		for (int i = 1; i < 6; i++)
		{
			if (ET_History_X[i] != 0)
			{
				pMDU->Line( ET_History_X[i], ET_History_Y[i] + 4, ET_History_X[i] - 6, ET_History_Y[i] - 4, dps::DEUATT_OVERBRIGHT );
				pMDU->Line( ET_History_X[i] - 6, ET_History_Y[i] - 4, ET_History_X[i] + 6, ET_History_Y[i] - 4, dps::DEUATT_OVERBRIGHT );
				pMDU->Line( ET_History_X[i] + 6, ET_History_Y[i] - 4, ET_History_X[i], ET_History_Y[i] + 4, dps::DEUATT_OVERBRIGHT );
			}

			if ((ISLECT > 1) && (ET_History_X_Drag[i] != 0))
			{
				pMDU->ThickDot( ET_History_X_Drag[i], ET_History_Y[i] );
			}
		}
		return;
	}

	void GeneralDisplays::OnPaint_ENTRYTRAJ2_PASS( vc::MDU* pMDU ) const
	{
		char cbuf[8];
		double DELAZ = ReadCOMPOOL_SD( SCP_DELAZ ) * DEG;
		unsigned short ISLECT = ReadCOMPOOL_IS( SCP_ISLECT );
		bool rrflash = ((DELAZ * ReadCOMPOOL_SD( SCP_PHI )) > 0.0) && (fabs( DELAZ ) >= (ReadCOMPOOL_SD( SCP_YL ) * DEG)) && (ISLECT > 1);
		char att = dps::DEUATT_NORMAL;

		PrintCommonHeader( "  ENTRY TRAJ 2", pMDU );

		pMDU->Alpha( 1, 1 );
		pMDU->mvprint( 0, 2, "50" );
		pMDU->mvprint( 0, 6, "45" );
		pMDU->mvprint( 0, 10, "40" );
		pMDU->mvprint( 0, 14, "35" );
		pMDU->mvprint( 0, 18, "30" );
		pMDU->mvprint( 0, 22, "25" );
		pMDU->mvprint( 4, 1, "D" );
		pMDU->mvprint( 4, 2, "50" );
		pMDU->mvprint( 4, 6, "40" );
		pMDU->mvprint( 4, 10, "30" );
		pMDU->mvprint( 4, 14, "20" );
		pMDU->mvprint( 4, 18, "10" );
		pMDU->mvprint( 4, 22, "0" );
		pMDU->mvprint( 7, 4, "1 BIAS" );
		pMDU->mvprint( 7, 5, "D REF" );
		pMDU->mvprint( 7, 6, "q" );
		pMDU->Line( 70, 84, 80, 84 );
		pMDU->Delta( 7, 7 );
		pMDU->mvprint( 9, 7, "AZ" );
		//pMDU->mvprint( 7, 9, "LO ENRGY" );
		//pMDU->mvprint( 7, 10, "3" );
		pMDU->mvprint( 38, 15, "NY" );
		pMDU->mvprint( 38, 16, "NY TRIM" );
		pMDU->mvprint( 38, 17, "AIL" );
		pMDU->mvprint( 38, 18, "RUD" );
		pMDU->mvprint( 37, 19, "ZERO H BIAS 2" );
		pMDU->DotCharacter( 42, 19 );
		pMDU->mvprint( 38, 20, "H BIAS" );
		pMDU->DotCharacter( 38, 20 );
		pMDU->mvprint( 41, 21, "REF" );
		pMDU->mvprint( 36, 22, "ROLL REF" );
		pMDU->mvprint( 41, 23, "CMD" );
		pMDU->mvprint( 31, 2, "35D" );
		pMDU->mvprint( 35, 2, "25D" );
		pMDU->mvprint( 39, 2, "20D" );
		pMDU->mvprint( 15, 13, "45D" );
		pMDU->mvprint( 7, 19, "52D" );
		pMDU->mvprint( 19, 23, "-125" );
		pMDU->mvprint( 31, 23, "-190" );

		// phugoid scale lines
		if (rrflash) att = dps::DEUATT_FLASHING;
		else att = dps::DEUATT_NORMAL;
		pMDU->Line( 70, 30, 250, 30, att );
		pMDU->Line( 70, 30, 70, 36, att );
		pMDU->Line( 160, 30, 160, 36, att );
		pMDU->Line( 250, 30, 250, 36, att );

		// alpha/D scale lines
		pMDU->Line( 34, 34, 34, 314 );
		pMDU->Line( 30, 34, 38, 34 );
		pMDU->Line( 30, 45, 38, 45 );
		pMDU->Line( 30, 56, 38, 56 );
		pMDU->Line( 30, 68, 38, 68 );
		pMDU->Line( 30, 79, 38, 79 );
		pMDU->Line( 30, 90, 38, 90 );
		pMDU->Line( 30, 101, 38, 101 );
		pMDU->Line( 30, 112, 38, 112 );
		pMDU->Line( 30, 124, 38, 124 );
		pMDU->Line( 30, 135, 38, 135 );
		pMDU->Line( 30, 146, 38, 146 );
		pMDU->Line( 30, 157, 38, 157 );
		pMDU->Line( 30, 168, 38, 168 );
		pMDU->Line( 30, 180, 38, 180 );
		pMDU->Line( 30, 191, 38, 191 );
		pMDU->Line( 30, 202, 38, 202 );
		pMDU->Line( 30, 213, 38, 213 );
		pMDU->Line( 30, 224, 38, 224 );
		pMDU->Line( 30, 236, 38, 236 );
		pMDU->Line( 30, 247, 38, 247 );
		pMDU->Line( 30, 258, 38, 258 );
		pMDU->Line( 30, 269, 38, 269 );
		pMDU->Line( 30, 280, 38, 280 );
		pMDU->Line( 30, 292, 38, 292 );
		pMDU->Line( 30, 303, 38, 303 );
		pMDU->Line( 30, 314, 38, 314 );

		// vel/rng lines
		pMDU->Line( 338, 42, 108, 266 );
		pMDU->Line( 108, 266, 82, 308 );

		pMDU->Line( 356, 42, 206, 308 );

		pMDU->Line( 396, 42, 218, 308 );

		pMDU->Line( 478, 53, 368, 229 );
		pMDU->Line( 368, 229, 320, 297 );

		// drag lines
		pMDU->Line( 158, 193, 110, 314, dps::DEUATT_DASHED );

		pMDU->Line( 326, 42, 192, 313, dps::DEUATT_DASHED );

		pMDU->Line( 366, 44, 228, 314, dps::DEUATT_DASHED );

		pMDU->Line( 406, 44, 298, 303, dps::DEUATT_DASHED );

		// digital data
		sprintf_s( cbuf, 8, "%5.1f", ReadCOMPOOL_SD( SCP_QBAR ) );
		pMDU->mvprint( 12, 6, cbuf );

		sprintf_s( cbuf, 8, "%+5.1f", DELAZ );
		pMDU->mvprint( 12, 7, cbuf );

		ENTRYTRAJ_PrintTrimGuidanceParams( pMDU, ReadCOMPOOL_SD( SCP_NY ), ReadCOMPOOL_SD( SCP_DRTI ), ReadCOMPOOL_SD( SCP_DATRIM ), ReadCOMPOOL_SD( SCP_DRTRIM ), ReadCOMPOOL_SD( SCP_DLRDOT ), ReadCOMPOOL_SD( SCP_RDTREF ), ReadCOMPOOL_SD( SCP_ROLLREF ), ReadCOMPOOL_SD( SCP_ROLLCMD ) );

		// scale data
		att = dps::DEUATT_OVERBRIGHT;
		double ALPHA = ReadCOMPOOL_SD( SCP_ALPHA );
		double ACMD1 = ReadCOMPOOL_SD( SCP_ACMD1 );
		if (fabs( ALPHA - ACMD1 ) > 2.0) att |= dps::DEUATT_FLASHING;
		int pos;
		if (ALPHA > 50.0)
		{
			pos = 34;
			att |= dps::DEUATT_FLASHING;
		}
		else if (ALPHA < 25.0)
		{
			pos = 314;
			att |= dps::DEUATT_FLASHING;
		}
		else pos = 594 - Round( 11.2 * ALPHA );
		pMDU->Line( 33, pos, 25, pos + 6, att );
		pMDU->Line( 25, pos + 6, 25, pos - 6, att );
		pMDU->Line( 25, pos - 6, 33, pos, att );

		att = dps::DEUATT_OVERBRIGHT;
		if (ACMD1 > 50.0)
		{
			pos = 34;
			att |= dps::DEUATT_FLASHING;
		}
		else if (ACMD1 < 25.0)
		{
			pos = 314;
			att |= dps::DEUATT_FLASHING;
		}
		else pos = 594 - Round( 11.2 * ACMD1 );
		pMDU->Line( 33, pos, 27, pos + 6, att );
		pMDU->Line( 27, pos + 6, 27, pos + 2, att );
		pMDU->Line( 27, pos + 2, 15, pos + 2, att );
		pMDU->Line( 15, pos + 2, 15, pos - 2, att );
		pMDU->Line( 15, pos - 2, 27, pos - 2, att );
		pMDU->Line( 27, pos - 2, 27, pos - 6, att );
		pMDU->Line( 27, pos - 6, 33, pos, att );

		att = dps::DEUATT_OVERBRIGHT;
		double DRAG = ReadCOMPOOL_SD( SCP_DRAG );
		if (DRAG > 50.0)
		{
			pos = 34;
			att |= dps::DEUATT_FLASHING;
		}
		else if (DRAG < 0.0)
		{
			pos = 314;
			att |= dps::DEUATT_FLASHING;
		}
		else pos = 314 - Round( 5.6 * DRAG );
		pMDU->Line( 35, pos, 43, pos + 6, att );
		pMDU->Line( 43, pos + 6, 43, pos - 6, att );
		pMDU->Line( 43, pos - 6, 35, pos, att );

		if (ISLECT > 1)
		{
			att = dps::DEUATT_OVERBRIGHT;
			double DREFP = ReadCOMPOOL_SD( SCP_DREFP );
			if (DREFP > 50.0)
			{
				pos = 34;
				att |= dps::DEUATT_FLASHING;
			}
			else if (DREFP < 0.0)
			{
				pos = 314;
				att |= dps::DEUATT_FLASHING;
			}
			else pos = 314 - Round( 5.6 * DREFP );
			pMDU->Line( 35, pos, 41, pos + 6, att );
			pMDU->Line( 41, pos + 6, 41, pos + 2, att );
			pMDU->Line( 41, pos + 2, 53, pos + 2, att );
			pMDU->Line( 53, pos + 2, 53, pos - 2, att );
			pMDU->Line( 53, pos - 2, 41, pos - 2, att );
			pMDU->Line( 41, pos - 2, 41, pos - 6, att );
			pMDU->Line( 41, pos - 6, 35, pos, att );
		}

		// orbiter symbol
		att = dps::DEUATT_OVERBRIGHT;
		if (rrflash) att |= dps::DEUATT_FLASHING;
		pMDU->OrbiterSymbolSide( ET_History_X[0], ET_History_Y[0], 0, att );

		// drag symbol
		if (ISLECT > 1) pMDU->Square( ET_History_X_Drag[0], ET_History_Y[0] );

		// orbiter and drag trailers
		for (int i = 1; i < 6; i++)
		{
			if (ET_History_X[i] != 0)
			{
				pMDU->Line( ET_History_X[i], ET_History_Y[i] + 4, ET_History_X[i] - 6, ET_History_Y[i] - 4, dps::DEUATT_OVERBRIGHT );
				pMDU->Line( ET_History_X[i] - 6, ET_History_Y[i] - 4, ET_History_X[i] + 6, ET_History_Y[i] - 4, dps::DEUATT_OVERBRIGHT );
				pMDU->Line( ET_History_X[i] + 6, ET_History_Y[i] - 4, ET_History_X[i], ET_History_Y[i] + 4, dps::DEUATT_OVERBRIGHT );
			}

			if ((ISLECT > 1) && (ET_History_X_Drag[i] != 0))
			{
				pMDU->ThickDot( ET_History_X_Drag[i], ET_History_Y[i] );
			}
		}
		return;
	}

	void GeneralDisplays::OnPaint_ENTRYTRAJ3_PASS( vc::MDU* pMDU ) const
	{
		char cbuf[8];
		double DELAZ = ReadCOMPOOL_SD( SCP_DELAZ ) * DEG;
		unsigned short ISLECT = ReadCOMPOOL_IS( SCP_ISLECT );
		bool rrflash = ((DELAZ * ReadCOMPOOL_SD( SCP_PHI )) > 0.0) && (fabs( DELAZ ) >= (ReadCOMPOOL_SD( SCP_YL ) * DEG)) && (ISLECT > 1);
		char att = dps::DEUATT_NORMAL;

		PrintCommonHeader( "  ENTRY TRAJ 3", pMDU );

		pMDU->Alpha( 1, 1 );
		pMDU->mvprint( 0, 2, "45" );
		pMDU->mvprint( 0, 6, "40" );
		pMDU->mvprint( 0, 10, "35" );
		pMDU->mvprint( 0, 14, "30" );
		pMDU->mvprint( 0, 18, "25" );
		pMDU->mvprint( 0, 22, "20" );
		pMDU->mvprint( 4, 1, "D" );
		pMDU->mvprint( 4, 2, "50" );
		pMDU->mvprint( 4, 6, "40" );
		pMDU->mvprint( 4, 10, "30" );
		pMDU->mvprint( 4, 14, "20" );
		pMDU->mvprint( 4, 18, "10" );
		pMDU->mvprint( 4, 22, "0" );
		pMDU->mvprint( 7, 4, "1 BIAS" );
		pMDU->mvprint( 7, 5, "D REF" );
		pMDU->mvprint( 7, 6, "q" );
		pMDU->Line( 70, 84, 80, 84 );
		pMDU->Delta( 7, 7 );
		pMDU->mvprint( 9, 7, "AZ" );
		//pMDU->mvprint( 7, 9, "LO ENRGY" );
		//pMDU->mvprint( 7, 10, "3" );
		pMDU->mvprint( 38, 15, "NY" );
		pMDU->mvprint( 38, 16, "NY TRIM" );
		pMDU->mvprint( 38, 17, "AIL" );
		pMDU->mvprint( 38, 18, "RUD" );
		pMDU->mvprint( 37, 19, "ZERO H BIAS 2" );
		pMDU->DotCharacter( 42, 19 );
		pMDU->mvprint( 38, 20, "H BIAS" );
		pMDU->DotCharacter( 38, 20 );
		pMDU->mvprint( 41, 21, "REF" );
		pMDU->mvprint( 36, 22, "ROLL REF" );
		pMDU->mvprint( 41, 23, "CMD" );
		pMDU->mvprint( 28, 2, "45D" );
		pMDU->mvprint( 37, 2, "35D" );
		pMDU->mvprint( 42, 2, "25D" );
		pMDU->mvprint( 16, 23, "-210" );
		pMDU->mvprint( 31, 23, "-130" );

		// phugoid scale lines
		if (rrflash) att = dps::DEUATT_FLASHING;
		else att = dps::DEUATT_NORMAL;
		pMDU->Line( 70, 30, 250, 30, att );
		pMDU->Line( 70, 30, 70, 36, att );
		pMDU->Line( 160, 30, 160, 36, att );
		pMDU->Line( 250, 30, 250, 36, att );

		// alpha/D scale lines
		pMDU->Line( 34, 34, 34, 314 );
		pMDU->Line( 30, 34, 38, 34 );
		pMDU->Line( 30, 45, 38, 45 );
		pMDU->Line( 30, 56, 38, 56 );
		pMDU->Line( 30, 68, 38, 68 );
		pMDU->Line( 30, 79, 38, 79 );
		pMDU->Line( 30, 90, 38, 90 );
		pMDU->Line( 30, 101, 38, 101 );
		pMDU->Line( 30, 112, 38, 112 );
		pMDU->Line( 30, 124, 38, 124 );
		pMDU->Line( 30, 135, 38, 135 );
		pMDU->Line( 30, 146, 38, 146 );
		pMDU->Line( 30, 157, 38, 157 );
		pMDU->Line( 30, 168, 38, 168 );
		pMDU->Line( 30, 180, 38, 180 );
		pMDU->Line( 30, 191, 38, 191 );
		pMDU->Line( 30, 202, 38, 202 );
		pMDU->Line( 30, 213, 38, 213 );
		pMDU->Line( 30, 224, 38, 224 );
		pMDU->Line( 30, 236, 38, 236 );
		pMDU->Line( 30, 247, 38, 247 );
		pMDU->Line( 30, 258, 38, 258 );
		pMDU->Line( 30, 269, 38, 269 );
		pMDU->Line( 30, 280, 38, 280 );
		pMDU->Line( 30, 292, 38, 292 );
		pMDU->Line( 30, 303, 38, 303 );
		pMDU->Line( 30, 314, 38, 314 );

		// vel/rng lines
		pMDU->Line( 244, 40, 56, 300 );

		pMDU->Line( 396, 40, 192, 299 );

		pMDU->Line( 498, 44, 388, 190 );
		pMDU->Line( 388, 190, 296, 300 );

		// drag lines
		pMDU->Line( 292, 44, 84, 319, dps::DEUATT_DASHED );

		pMDU->Line( 380, 40, 174, 311, dps::DEUATT_DASHED );

		pMDU->Line( 440, 40, 232, 311, dps::DEUATT_DASHED );

		// digital data
		sprintf_s( cbuf, 8, "%5.1f", ReadCOMPOOL_SD( SCP_QBAR ) );
		pMDU->mvprint( 12, 6, cbuf );

		sprintf_s( cbuf, 8, "%+5.1f", DELAZ );
		pMDU->mvprint( 12, 7, cbuf );

		ENTRYTRAJ_PrintTrimGuidanceParams( pMDU, ReadCOMPOOL_SD( SCP_NY ), ReadCOMPOOL_SD( SCP_DRTI ), ReadCOMPOOL_SD( SCP_DATRIM ), ReadCOMPOOL_SD( SCP_DRTRIM ), ReadCOMPOOL_SD( SCP_DLRDOT ), ReadCOMPOOL_SD( SCP_RDTREF ), ReadCOMPOOL_SD( SCP_ROLLREF ), ReadCOMPOOL_SD( SCP_ROLLCMD ) );

		// scale data
		att = dps::DEUATT_OVERBRIGHT;
		double ALPHA = ReadCOMPOOL_SD( SCP_ALPHA );
		double ACMD1 = ReadCOMPOOL_SD( SCP_ACMD1 );
		if (fabs( ALPHA - ACMD1 ) > 2.0) att |= dps::DEUATT_FLASHING;
		int pos;
		if (ALPHA > 45.0)
		{
			pos = 34;
			att |= dps::DEUATT_FLASHING;
		}
		else if (ALPHA < 20.0)
		{
			pos = 314;
			att |= dps::DEUATT_FLASHING;
		}
		else pos = 538 - Round( 11.2 * ALPHA );
		pMDU->Line( 33, pos, 25, pos + 6, att );
		pMDU->Line( 25, pos + 6, 25, pos - 6, att );
		pMDU->Line( 25, pos - 6, 33, pos, att );

		att = dps::DEUATT_OVERBRIGHT;
		if (ACMD1 > 45.0)
		{
			pos = 34;
			att |= dps::DEUATT_FLASHING;
		}
		else if (ACMD1 < 20.0)
		{
			pos = 314;
			att |= dps::DEUATT_FLASHING;
		}
		else pos = 538 - Round( 11.2 * ACMD1 );
		pMDU->Line( 33, pos, 27, pos + 6, att );
		pMDU->Line( 27, pos + 6, 27, pos + 2, att );
		pMDU->Line( 27, pos + 2, 15, pos + 2, att );
		pMDU->Line( 15, pos + 2, 15, pos - 2, att );
		pMDU->Line( 15, pos - 2, 27, pos - 2, att );
		pMDU->Line( 27, pos - 2, 27, pos - 6, att );
		pMDU->Line( 27, pos - 6, 33, pos, att );

		att = dps::DEUATT_OVERBRIGHT;
		double DRAG = ReadCOMPOOL_SD( SCP_DRAG );
		if (DRAG > 50.0)
		{
			pos = 34;
			att |= dps::DEUATT_FLASHING;
		}
		else if (DRAG < 0.0)
		{
			pos = 314;
			att |= dps::DEUATT_FLASHING;
		}
		else pos = 314 - Round( 5.6 * DRAG );
		pMDU->Line( 35, pos, 43, pos + 6, att );
		pMDU->Line( 43, pos + 6, 43, pos - 6, att );
		pMDU->Line( 43, pos - 6, 35, pos, att );

		if (ISLECT > 1)
		{
			att = dps::DEUATT_OVERBRIGHT;
			double DREFP = ReadCOMPOOL_SD( SCP_DREFP );
			if (DREFP > 50.0)
			{
				pos = 34;
				att |= dps::DEUATT_FLASHING;
			}
			else if (DREFP < 0.0)
			{
				pos = 314;
				att |= dps::DEUATT_FLASHING;
			}
			else pos = 314 - Round( 5.6 * DREFP );
			pMDU->Line( 35, pos, 41, pos + 6, att );
			pMDU->Line( 41, pos + 6, 41, pos + 2, att );
			pMDU->Line( 41, pos + 2, 53, pos + 2, att );
			pMDU->Line( 53, pos + 2, 53, pos - 2, att );
			pMDU->Line( 53, pos - 2, 41, pos - 2, att );
			pMDU->Line( 41, pos - 2, 41, pos - 6, att );
			pMDU->Line( 41, pos - 6, 35, pos, att );
		}

		// orbiter symbol
		att = dps::DEUATT_OVERBRIGHT;
		if (rrflash) att |= dps::DEUATT_FLASHING;
		pMDU->OrbiterSymbolSide( ET_History_X[0], ET_History_Y[0], 0, att );

		// drag symbol
		if (ISLECT > 1) pMDU->Square( ET_History_X_Drag[0], ET_History_Y[0] );

		// orbiter and drag trailers
		for (int i = 1; i < 6; i++)
		{
			if (ET_History_X[i] != 0)
			{
				pMDU->Line( ET_History_X[i], ET_History_Y[i] + 4, ET_History_X[i] - 6, ET_History_Y[i] - 4, dps::DEUATT_OVERBRIGHT );
				pMDU->Line( ET_History_X[i] - 6, ET_History_Y[i] - 4, ET_History_X[i] + 6, ET_History_Y[i] - 4, dps::DEUATT_OVERBRIGHT );
				pMDU->Line( ET_History_X[i] + 6, ET_History_Y[i] - 4, ET_History_X[i], ET_History_Y[i] + 4, dps::DEUATT_OVERBRIGHT );
			}

			if ((ISLECT > 1) && (ET_History_X_Drag[i] != 0))
			{
				pMDU->ThickDot( ET_History_X_Drag[i], ET_History_Y[i] );
			}
		}
		return;
	}

	void GeneralDisplays::OnPaint_ENTRYTRAJ4_PASS( vc::MDU* pMDU ) const
	{
		char cbuf[8];
		double DELAZ = ReadCOMPOOL_SD( SCP_DELAZ ) * DEG;
		unsigned short ISLECT = ReadCOMPOOL_IS( SCP_ISLECT );
		bool rrflash = ((DELAZ * ReadCOMPOOL_SD( SCP_PHI )) > 0.0) && (fabs( DELAZ ) >= (ReadCOMPOOL_SD( SCP_YL ) * DEG)) && (ISLECT > 1);
		char att = dps::DEUATT_NORMAL;

		PrintCommonHeader( "  ENTRY TRAJ 4", pMDU );

		pMDU->Alpha( 1, 1 );
		pMDU->mvprint( 0, 2, "45" );
		pMDU->mvprint( 0, 6, "40" );
		pMDU->mvprint( 0, 10, "35" );
		pMDU->mvprint( 0, 14, "30" );
		pMDU->mvprint( 0, 18, "25" );
		pMDU->mvprint( 0, 22, "20" );
		pMDU->mvprint( 4, 1, "D" );
		pMDU->mvprint( 4, 2, "50" );
		pMDU->mvprint( 4, 6, "40" );
		pMDU->mvprint( 4, 10, "30" );
		pMDU->mvprint( 4, 14, "20" );
		pMDU->mvprint( 4, 18, "10" );
		pMDU->mvprint( 4, 22, "0" );
		pMDU->mvprint( 7, 4, "1 BIAS" );
		pMDU->mvprint( 7, 5, "D REF" );
		pMDU->mvprint( 7, 6, "q" );
		pMDU->Line( 70, 84, 80, 84 );
		pMDU->Delta( 7, 7 );
		pMDU->mvprint( 9, 7, "AZ" );
		//pMDU->mvprint( 7, 9, "LO ENRGY" );
		//pMDU->mvprint( 7, 10, "3" );
		pMDU->mvprint( 38, 15, "NY" );
		pMDU->mvprint( 38, 16, "NY TRIM" );
		pMDU->mvprint( 38, 17, "AIL" );
		pMDU->mvprint( 38, 18, "RUD" );
		pMDU->mvprint( 37, 19, "ZERO H BIAS 2" );
		pMDU->DotCharacter( 42, 19 );
		pMDU->mvprint( 38, 20, "H BIAS" );
		pMDU->DotCharacter( 38, 20 );
		pMDU->mvprint( 41, 21, "REF" );
		pMDU->mvprint( 36, 22, "ROLL REF" );
		pMDU->mvprint( 41, 23, "CMD" );
		pMDU->mvprint( 42, 2, "40D" );
		pMDU->mvprint( 47, 2, "30D" );
		pMDU->mvprint( 48, 11, "20D" );
		pMDU->mvprint( 42, 13, "-210" );
		pMDU->mvprint( 13, 23, "-255" );
		pMDU->mvprint( 30, 23, "-250" );

		// phugoid scale lines
		if (rrflash) att = dps::DEUATT_FLASHING;
		else att = dps::DEUATT_NORMAL;
		pMDU->Line( 70, 30, 250, 30, att );
		pMDU->Line( 70, 30, 70, 36, att );
		pMDU->Line( 160, 30, 160, 36, att );
		pMDU->Line( 250, 30, 250, 36, att );

		// alpha/D scale lines
		pMDU->Line( 34, 34, 34, 314 );
		pMDU->Line( 30, 34, 38, 34 );
		pMDU->Line( 30, 45, 38, 45 );
		pMDU->Line( 30, 56, 38, 56 );
		pMDU->Line( 30, 68, 38, 68 );
		pMDU->Line( 30, 79, 38, 79 );
		pMDU->Line( 30, 90, 38, 90 );
		pMDU->Line( 30, 101, 38, 101 );
		pMDU->Line( 30, 112, 38, 112 );
		pMDU->Line( 30, 124, 38, 124 );
		pMDU->Line( 30, 135, 38, 135 );
		pMDU->Line( 30, 146, 38, 146 );
		pMDU->Line( 30, 157, 38, 157 );
		pMDU->Line( 30, 168, 38, 168 );
		pMDU->Line( 30, 180, 38, 180 );
		pMDU->Line( 30, 191, 38, 191 );
		pMDU->Line( 30, 202, 38, 202 );
		pMDU->Line( 30, 213, 38, 213 );
		pMDU->Line( 30, 224, 38, 224 );
		pMDU->Line( 30, 236, 38, 236 );
		pMDU->Line( 30, 247, 38, 247 );
		pMDU->Line( 30, 258, 38, 258 );
		pMDU->Line( 30, 269, 38, 269 );
		pMDU->Line( 30, 280, 38, 280 );
		pMDU->Line( 30, 292, 38, 292 );
		pMDU->Line( 30, 303, 38, 303 );
		pMDU->Line( 30, 314, 38, 314 );

		// alt*vel/rng lines
		pMDU->Line( 358, 51, 192, 208 );
		pMDU->Line( 192, 208, 36, 319 );

		pMDU->Line( 438, 64, 350, 171 );
		pMDU->Line( 350, 171, 164, 302 );

		pMDU->Line( 486, 64, 452, 128 );
		pMDU->Line( 452, 128, 356, 224 );
		pMDU->Line( 356, 224, 192, 320 );

		// drag lines
		pMDU->Line( 422, 37, 258, 180, dps::DEUATT_DASHED );
		pMDU->Line( 258, 180, 212, 216, dps::DEUATT_DASHED );
		pMDU->Line( 212, 216, 24, 330, dps::DEUATT_DASHED );

		pMDU->Line( 484, 44, 358, 151, dps::DEUATT_DASHED );
		pMDU->Line( 358, 151, 272, 208, dps::DEUATT_DASHED );
		pMDU->Line( 272, 208, 66, 330, dps::DEUATT_DASHED );

		pMDU->Line( 464, 145, 292, 252, dps::DEUATT_DASHED );
		pMDU->Line( 292, 252, 168, 319, dps::DEUATT_DASHED );

		// digital data
		sprintf_s( cbuf, 8, "%5.1f", ReadCOMPOOL_SD( SCP_QBAR ) );
		pMDU->mvprint( 12, 6, cbuf );

		sprintf_s( cbuf, 8, "%+5.1f", DELAZ );
		pMDU->mvprint( 12, 7, cbuf );

		ENTRYTRAJ_PrintTrimGuidanceParams( pMDU, ReadCOMPOOL_SD( SCP_NY ), ReadCOMPOOL_SD( SCP_DRTI ), ReadCOMPOOL_SD( SCP_DATRIM ), ReadCOMPOOL_SD( SCP_DRTRIM ), ReadCOMPOOL_SD( SCP_DLRDOT ), ReadCOMPOOL_SD( SCP_RDTREF ), ReadCOMPOOL_SD( SCP_ROLLREF ), ReadCOMPOOL_SD( SCP_ROLLCMD ) );

		// scale data
		att = dps::DEUATT_OVERBRIGHT;
		double ALPHA = ReadCOMPOOL_SD( SCP_ALPHA );
		double ACMD1 = ReadCOMPOOL_SD( SCP_ACMD1 );
		if (fabs( ALPHA - ACMD1 ) > 2.0) att |= dps::DEUATT_FLASHING;
		int pos;
		if (ALPHA > 45.0)
		{
			pos = 34;
			att |= dps::DEUATT_FLASHING;
		}
		else if (ALPHA < 20.0)
		{
			pos = 314;
			att |= dps::DEUATT_FLASHING;
		}
		else pos = 538 - Round( 11.2 * ALPHA );
		pMDU->Line( 33, pos, 25, pos + 6, att );
		pMDU->Line( 25, pos + 6, 25, pos - 6, att );
		pMDU->Line( 25, pos - 6, 33, pos, att );

		att = dps::DEUATT_OVERBRIGHT;
		if (ACMD1 > 45.0)
		{
			pos = 34;
			att |= dps::DEUATT_FLASHING;
		}
		else if (ACMD1 < 20.0)
		{
			pos = 314;
			att |= dps::DEUATT_FLASHING;
		}
		else pos = 538 - Round( 11.2 * ACMD1 );
		pMDU->Line( 33, pos, 27, pos + 6, att );
		pMDU->Line( 27, pos + 6, 27, pos + 2, att );
		pMDU->Line( 27, pos + 2, 15, pos + 2, att );
		pMDU->Line( 15, pos + 2, 15, pos - 2, att );
		pMDU->Line( 15, pos - 2, 27, pos - 2, att );
		pMDU->Line( 27, pos - 2, 27, pos - 6, att );
		pMDU->Line( 27, pos - 6, 33, pos, att );

		att = dps::DEUATT_OVERBRIGHT;
		double DRAG = ReadCOMPOOL_SD( SCP_DRAG );
		if (DRAG > 50.0)
		{
			pos = 34;
			att |= dps::DEUATT_FLASHING;
		}
		else if (DRAG < 0.0)
		{
			pos = 314;
			att |= dps::DEUATT_FLASHING;
		}
		else pos = 314 - Round( 5.6 * DRAG );
		pMDU->Line( 35, pos, 43, pos + 6, att );
		pMDU->Line( 43, pos + 6, 43, pos - 6, att );
		pMDU->Line( 43, pos - 6, 35, pos, att );

		if (ISLECT > 1)
		{
			att = dps::DEUATT_OVERBRIGHT;
			double DREFP = ReadCOMPOOL_SD( SCP_DREFP );
			if (DREFP > 50.0)
			{
				pos = 34;
				att |= dps::DEUATT_FLASHING;
			}
			else if (DREFP < 0.0)
			{
				pos = 314;
				att |= dps::DEUATT_FLASHING;
			}
			else pos = 314 - Round( 5.6 * DREFP );
			pMDU->Line( 35, pos, 41, pos + 6, att );
			pMDU->Line( 41, pos + 6, 41, pos + 2, att );
			pMDU->Line( 41, pos + 2, 53, pos + 2, att );
			pMDU->Line( 53, pos + 2, 53, pos - 2, att );
			pMDU->Line( 53, pos - 2, 41, pos - 2, att );
			pMDU->Line( 41, pos - 2, 41, pos - 6, att );
			pMDU->Line( 41, pos - 6, 35, pos, att );
		}

		// orbiter symbol
		att = dps::DEUATT_OVERBRIGHT;
		if (rrflash) att |= dps::DEUATT_FLASHING;
		pMDU->OrbiterSymbolSide( ET_History_X[0], ET_History_Y[0], 0, att );

		// drag symbol
		if (ISLECT > 1) pMDU->Square( ET_History_X_Drag[0], ET_History_Y[0] );

		// orbiter and drag trailers
		for (int i = 1; i < 6; i++)
		{
			if (ET_History_X[i] != 0)
			{
				pMDU->Line( ET_History_X[i], ET_History_Y[i] + 4, ET_History_X[i] - 6, ET_History_Y[i] - 4, dps::DEUATT_OVERBRIGHT );
				pMDU->Line( ET_History_X[i] - 6, ET_History_Y[i] - 4, ET_History_X[i] + 6, ET_History_Y[i] - 4, dps::DEUATT_OVERBRIGHT );
				pMDU->Line( ET_History_X[i] + 6, ET_History_Y[i] - 4, ET_History_X[i], ET_History_Y[i] + 4, dps::DEUATT_OVERBRIGHT );
			}

			if ((ISLECT > 1) && (ET_History_X_Drag[i] != 0))
			{
				pMDU->ThickDot( ET_History_X_Drag[i], ET_History_Y[i] );
			}
		}
		return;
	}

	void GeneralDisplays::OnPaint_ENTRYTRAJ5_PASS( vc::MDU* pMDU ) const
	{
		char cbuf[8];
		double DELAZ = ReadCOMPOOL_SD( SCP_DELAZ ) * DEG;
		unsigned short ISLECT = ReadCOMPOOL_IS( SCP_ISLECT );
		bool rrflash = ((DELAZ * ReadCOMPOOL_SD( SCP_PHI )) > 0.0) && (fabs( DELAZ ) >= (ReadCOMPOOL_SD( SCP_YL ) * DEG)) && (ISLECT > 1);
		char att = dps::DEUATT_NORMAL;

		PrintCommonHeader( "  ENTRY TRAJ 5", pMDU );

		pMDU->Alpha( 1, 1 );
		pMDU->mvprint( 0, 2, "30" );
		pMDU->mvprint( 0, 6, "25" );
		pMDU->mvprint( 0, 10, "20" );
		pMDU->mvprint( 0, 14, "15" );
		pMDU->mvprint( 0, 18, "10" );
		pMDU->mvprint( 0, 22, "5" );
		pMDU->mvprint( 4, 1, "D" );
		pMDU->mvprint( 4, 2, "50" );
		pMDU->mvprint( 4, 6, "40" );
		pMDU->mvprint( 4, 10, "30" );
		pMDU->mvprint( 4, 14, "20" );
		pMDU->mvprint( 4, 18, "10" );
		pMDU->mvprint( 4, 22, "0" );
		pMDU->mvprint( 7, 4, "1 BIAS" );
		pMDU->mvprint( 7, 5, "D REF" );
		pMDU->mvprint( 7, 6, "q" );
		pMDU->Line( 70, 84, 80, 84 );
		pMDU->Delta( 7, 7 );
		pMDU->mvprint( 9, 7, "AZ" );
		//pMDU->mvprint( 7, 9, "LO ENRGY" );
		//pMDU->mvprint( 7, 10, "3" );
		pMDU->mvprint( 38, 15, "NY" );
		pMDU->mvprint( 38, 16, "NY TRIM" );
		pMDU->mvprint( 38, 17, "AIL" );
		pMDU->mvprint( 38, 18, "RUD" );
		pMDU->mvprint( 37, 19, "ZERO H BIAS 2" );
		pMDU->DotCharacter( 42, 19 );
		pMDU->mvprint( 38, 20, "H BIAS" );
		pMDU->DotCharacter( 38, 20 );
		pMDU->mvprint( 41, 21, "REF" );
		pMDU->mvprint( 36, 22, "ROLL REF" );
		pMDU->mvprint( 41, 23, "CMD" );
		pMDU->mvprint( 42, 2, "30D" );
		pMDU->mvprint( 47, 2, "20D" );
		pMDU->mvprint( 44, 14, "-275" );
		pMDU->mvprint( 13, 23, "-245" );
		pMDU->mvprint( 30, 23, "-275" );

		// phugoid scale lines
		if (rrflash) att = dps::DEUATT_FLASHING;
		else att = dps::DEUATT_NORMAL;
		pMDU->Line( 70, 30, 250, 30, att );
		pMDU->Line( 70, 30, 70, 36, att );
		pMDU->Line( 160, 30, 160, 36, att );
		pMDU->Line( 250, 30, 250, 36, att );

		// alpha/D scale lines
		pMDU->Line( 34, 34, 34, 314 );
		pMDU->Line( 30, 34, 38, 34 );
		pMDU->Line( 30, 45, 38, 45 );
		pMDU->Line( 30, 56, 38, 56 );
		pMDU->Line( 30, 68, 38, 68 );
		pMDU->Line( 30, 79, 38, 79 );
		pMDU->Line( 30, 90, 38, 90 );
		pMDU->Line( 30, 101, 38, 101 );
		pMDU->Line( 30, 112, 38, 112 );
		pMDU->Line( 30, 124, 38, 124 );
		pMDU->Line( 30, 135, 38, 135 );
		pMDU->Line( 30, 146, 38, 146 );
		pMDU->Line( 30, 157, 38, 157 );
		pMDU->Line( 30, 168, 38, 168 );
		pMDU->Line( 30, 180, 38, 180 );
		pMDU->Line( 30, 191, 38, 191 );
		pMDU->Line( 30, 202, 38, 202 );
		pMDU->Line( 30, 213, 38, 213 );
		pMDU->Line( 30, 224, 38, 224 );
		pMDU->Line( 30, 236, 38, 236 );
		pMDU->Line( 30, 247, 38, 247 );
		pMDU->Line( 30, 258, 38, 258 );
		pMDU->Line( 30, 269, 38, 269 );
		pMDU->Line( 30, 280, 38, 280 );
		pMDU->Line( 30, 292, 38, 292 );
		pMDU->Line( 30, 303, 38, 303 );
		pMDU->Line( 30, 314, 38, 314 );

		// alt*vel/rng lines
		pMDU->Line( 378, 45, 222, 196 );
		pMDU->Line( 222, 196, 72, 308 );

		pMDU->Line( 450, 54, 358, 146 );
		pMDU->Line( 358, 146, 202, 252 );
		pMDU->Line( 202, 252, 92, 308 );

		pMDU->Line( 492, 50, 414, 143 );
		pMDU->Line( 414, 143, 298, 216 );
		pMDU->Line( 298, 216, 116, 308 );

		pMDU->Line( 510, 73, 460, 143 );
		pMDU->Line( 460, 143, 354, 218 );
		pMDU->Line( 354, 218, 160, 308 );

		// drag lines
		pMDU->Line( 420, 37, 260, 184, dps::DEUATT_DASHED );
		pMDU->Line( 260, 184, 170, 252, dps::DEUATT_DASHED );
		pMDU->Line( 170, 252, 26, 328, dps::DEUATT_DASHED );

		pMDU->Line( 484, 42, 358, 154, dps::DEUATT_DASHED );
		pMDU->Line( 358, 154, 274, 210, dps::DEUATT_DASHED );
		pMDU->Line( 274, 210, 68, 328, dps::DEUATT_DASHED );

		// digital data
		sprintf_s( cbuf, 8, "%5.1f", ReadCOMPOOL_SD( SCP_QBAR ) );
		pMDU->mvprint( 12, 6, cbuf );

		sprintf_s( cbuf, 8, "%+5.1f", DELAZ );
		pMDU->mvprint( 12, 7, cbuf );

		ENTRYTRAJ_PrintTrimGuidanceParams( pMDU, ReadCOMPOOL_SD( SCP_NY ), ReadCOMPOOL_SD( SCP_DRTI ), ReadCOMPOOL_SD( SCP_DATRIM ), ReadCOMPOOL_SD( SCP_DRTRIM ), ReadCOMPOOL_SD( SCP_DLRDOT ), ReadCOMPOOL_SD( SCP_RDTREF ), ReadCOMPOOL_SD( SCP_ROLLREF ), ReadCOMPOOL_SD( SCP_ROLLCMD ) );

		// scale data
		att = dps::DEUATT_OVERBRIGHT;
		double ALPHA = ReadCOMPOOL_SD( SCP_ALPHA );
		double ACMD1 = ReadCOMPOOL_SD( SCP_ACMD1 );
		if (fabs( ALPHA - ACMD1 ) > 2.0) att |= dps::DEUATT_FLASHING;
		int pos;
		if (ALPHA > 30.0)
		{
			pos = 34;
			att |= dps::DEUATT_FLASHING;
		}
		else if (ALPHA < 5.0)
		{
			pos = 314;
			att |= dps::DEUATT_FLASHING;
		}
		else pos = 370 - Round( 11.2 * ALPHA );
		pMDU->Line( 33, pos, 25, pos + 6, att );
		pMDU->Line( 25, pos + 6, 25, pos - 6, att );
		pMDU->Line( 25, pos - 6, 33, pos, att );

		att = dps::DEUATT_OVERBRIGHT;
		if (ACMD1 > 30.0)
		{
			pos = 34;
			att |= dps::DEUATT_FLASHING;
		}
		else if (ACMD1 < 5.0)
		{
			pos = 314;
			att |= dps::DEUATT_FLASHING;
		}
		else pos = 370 - Round( 11.2 * ACMD1 );
		pMDU->Line( 33, pos, 27, pos + 6, att );
		pMDU->Line( 27, pos + 6, 27, pos + 2, att );
		pMDU->Line( 27, pos + 2, 15, pos + 2, att );
		pMDU->Line( 15, pos + 2, 15, pos - 2, att );
		pMDU->Line( 15, pos - 2, 27, pos - 2, att );
		pMDU->Line( 27, pos - 2, 27, pos - 6, att );
		pMDU->Line( 27, pos - 6, 33, pos, att );

		att = dps::DEUATT_OVERBRIGHT;
		double DRAG = ReadCOMPOOL_SD( SCP_DRAG );
		if (DRAG > 50.0)
		{
			pos = 34;
			att |= dps::DEUATT_FLASHING;
		}
		else if (DRAG < 0.0)
		{
			pos = 314;
			att |= dps::DEUATT_FLASHING;
		}
		else pos = 314 - Round( 5.6 * DRAG );
		pMDU->Line( 35, pos, 43, pos + 6, att );
		pMDU->Line( 43, pos + 6, 43, pos - 6, att );
		pMDU->Line( 43, pos - 6, 35, pos, att );

		if (ISLECT > 1)
		{
			att = dps::DEUATT_OVERBRIGHT;
			double DREFP = ReadCOMPOOL_SD( SCP_DREFP );
			if (DREFP > 50.0)
			{
				pos = 34;
				att |= dps::DEUATT_FLASHING;
			}
			else if (DREFP < 0.0)
			{
				pos = 314;
				att |= dps::DEUATT_FLASHING;
			}
			else pos = 314 - Round( 5.6 * DREFP );
			pMDU->Line( 35, pos, 41, pos + 6, att );
			pMDU->Line( 41, pos + 6, 41, pos + 2, att );
			pMDU->Line( 41, pos + 2, 53, pos + 2, att );
			pMDU->Line( 53, pos + 2, 53, pos - 2, att );
			pMDU->Line( 53, pos - 2, 41, pos - 2, att );
			pMDU->Line( 41, pos - 2, 41, pos - 6, att );
			pMDU->Line( 41, pos - 6, 35, pos, att );
		}

		// orbiter symbol
		att = dps::DEUATT_OVERBRIGHT;
		if (rrflash) att |= dps::DEUATT_FLASHING;
		pMDU->OrbiterSymbolSide( ET_History_X[0], ET_History_Y[0], 0, att );

		// drag symbol
		if (ISLECT > 1) pMDU->Square( ET_History_X_Drag[0], ET_History_Y[0] );

		// orbiter and drag trailers
		for (int i = 1; i < 6; i++)
		{
			if (ET_History_X[i] != 0)
			{
				pMDU->Line( ET_History_X[i], ET_History_Y[i] + 4, ET_History_X[i] - 6, ET_History_Y[i] - 4, dps::DEUATT_OVERBRIGHT );
				pMDU->Line( ET_History_X[i] - 6, ET_History_Y[i] - 4, ET_History_X[i] + 6, ET_History_Y[i] - 4, dps::DEUATT_OVERBRIGHT );
				pMDU->Line( ET_History_X[i] + 6, ET_History_Y[i] - 4, ET_History_X[i], ET_History_Y[i] + 4, dps::DEUATT_OVERBRIGHT );
			}

			if ((ISLECT > 1) && (ET_History_X_Drag[i] != 0))
			{
				pMDU->ThickDot( ET_History_X_Drag[i], ET_History_Y[i] );
			}
		}
		return;
	}

	void GeneralDisplays::ENTRYTRAJ_PrintTrimGuidanceParams( vc::MDU* pMDU, double NY, double DRTI, double DATRIM, double DRTRIM, double DLRDOT, double RDTREF, double ROLLREF, double ROLLCMD ) const
	{
		char cbuf[8];
		sprintf_s( cbuf, 8, "%.3f", min(fabs( NY ), 0.999) );
		if (NY > 0.0) cbuf[0] = 'R';
		else if (NY < 0.0) cbuf[0] = 'L';
		else cbuf[0] = ' ';
		pMDU->mvprint( 46, 15, cbuf );

		sprintf_s( cbuf, 8, "%.3f", min(fabs( DRTI ), 0.999) );
		if (DRTI > 0.0) cbuf[0] = 'R';
		else if (DRTI < 0.0) cbuf[0] = 'L';
		else cbuf[0] = ' ';
		pMDU->mvprint( 46, 16, cbuf );

		sprintf_s( cbuf, 8, " %.1f", fabs( DATRIM ) );
		if (DATRIM > 0.0) cbuf[0] = 'R';
		else if (DATRIM < 0.0) cbuf[0] = 'L';
		pMDU->mvprint( 46, 17, cbuf );

		sprintf_s( cbuf, 8, " %.1f", fabs( DRTRIM ) );
		if (DRTRIM > 0.0) cbuf[0] = 'L';
		else if (DRTRIM < 0.0) cbuf[0] = 'R';
		pMDU->mvprint( 46, 18, cbuf );

		sprintf_s( cbuf, 8, " %3.0f", fabs( DLRDOT ) );
		if (DLRDOT > 0.0) cbuf[0] = '+';
		else if (DLRDOT < 0.0) cbuf[0] = '-';
		else cbuf[0] = ' ';
		pMDU->mvprint( 46, 20, cbuf );

		sprintf_s( cbuf, 8, " %3.0f", fabs( RDTREF ) );
		if (RDTREF > 0.0) cbuf[0] = '+';
		else if (RDTREF < 0.0) cbuf[0] = '-';
		else cbuf[0] = ' ';
		pMDU->mvprint( 46, 21, cbuf );

		sprintf_s( cbuf, 8, "%4.0f", fabs( ROLLREF ) );
		if (ROLLREF > 0.0) cbuf[0] = 'R';
		else if (ROLLREF < 0.0) cbuf[0] = 'L';
		else cbuf[0] = ' ';
		pMDU->mvprint( 46, 22, cbuf );
		if (ROLLREF_status) pMDU->DownArrow( 50, 22, dps::DEUATT_OVERBRIGHT );

		sprintf_s( cbuf, 8, "%4.0f", fabs( ROLLCMD ) );
		if (ROLLCMD > 0.0) cbuf[0] = 'R';
		else if (ROLLCMD < 0.0) cbuf[0] = 'L';
		else cbuf[0] = ' ';
		pMDU->mvprint( 46, 23, cbuf );
		return;
	}

	double GeneralDisplays::GetConversionParameter( unsigned char engunit ) const
	{
		switch (engunit)
		{
			case 1:// NM from FT
				return FT2NM;
			case 2:// NM from KFT
				return FT2NM * 1000.0;
			case 3:// FT from NM
				return 1.0 / FT2NM;
			case 4:// KFT from NM
				return 1.0 / (FT2NM * 1000.0);
			case 5:// FT/SEC2 from Gs
				return G2FPS2;
			case 6:// DEG/SEC from MR/SEC
				return DEG * 0.001;
			case 7:// DEG from ARC SEC
				return 1.0 / 3600.0;
			case 8:// FT/SEC2 from micro Gs
				return G2FPS2 * 0.000001;
			case 9:// DEG from Radians
				return DEG;
			case 10:// KFT from FT
				return 0.001;
			default:
				return 1.0;
		}
	}

	void GeneralDisplays::OnPaint_VERTSIT1_PASS( vc::MDU* pMDU ) const
	{
		char cbuf[8];
		double RPRED = ReadCOMPOOL_SD( SCP_RPRED );

		PrintCommonHeader( "  VERT SIT 1", pMDU );

		pMDU->mvprint( 39, 5, "272" );
		pMDU->mvprint( 40, 7, "240" );
		pMDU->mvprint( 14, 11, "269" );
		pMDU->mvprint( 23, 14, "214" );
		pMDU->mvprint( 13, 15, "240" );
		pMDU->mvprint( 4, 16, "266" );
		pMDU->mvprint( 9, 18, "227" );

		pMDU->Theta( 42, 8 );
		pMDU->mvprint( 48, 8, "E/W" );
		pMDU->mvprint( 48, 12, "STN" );
		pMDU->mvprint( 48, 15, "NOM" );
		pMDU->mvprint( 48, 20, "MEP" );

		pMDU->mvprint( 38, 12, "NOSE HI" );
		pMDU->mvprint( 29, 14, "SPD BK" );
		pMDU->mvprint( 32, 15, "CMD" );
		pMDU->mvprint( 38, 20, "NOSE LO" );

		pMDU->mvprint( 21, 17, "NY" );
		pMDU->mvprint( 21, 18, "NY TRIM" );
		pMDU->mvprint( 21, 19, "AIL" );
		pMDU->mvprint( 21, 20, "RUD" );
		//pMDU->mvprint( 21, 21, "TGT NZ" );// OPS 6 only

		// alt/rng lines
		pMDU->Line( 404, 90, 180, 160 );
		pMDU->Line( 180, 160, 74, 230 );
		pMDU->Line( 74, 230, 24, 308 );

		pMDU->Line( 400, 112, 216, 162 );
		pMDU->Line( 216, 162, 60, 311 );

		pMDU->Line( 404, 121, 238, 188 );
		pMDU->Line( 238, 188, 104, 300 );

		// RTLS alpha/mach transition
		pMDU->Line( 214, 92, 42, 112 );
		pMDU->Line( 42, 112, 10, 126 );
		pMDU->Line( 210, 62, 10, 98, dps::DEUATT_DASHED );

		// theta / E/W scale
		const int EOWscaleMaxY = 115;
		const int EOWscaleMinY = 339;
		const int EOWscaleSTRNY = 179;
		const int EOWscaleMEPY = 292;

		pMDU->Line( 464, EOWscaleMinY, 464, EOWscaleMaxY );
		pMDU->Line( 460, EOWscaleSTRNY, 470, EOWscaleSTRNY );
		pMDU->Line( 460, EOWscaleMEPY, 470, EOWscaleMEPY );

		// E/W side
		double EOW = ReadCOMPOOL_SD( SCP_EOW );
		double EN = ReadCOMPOOL_SD( SCP_EN );
		double ES = ReadCOMPOOL_SD( SCP_ES );
		double EMEP = ReadCOMPOOL_SD( SCP_EMEP );

		double m = (EOWscaleSTRNY - EOWscaleMEPY) / (ES - EMEP);// [px/ft]
		double b = EOWscaleMEPY - (EMEP * m);// [px]

		int pos = Round( range( EOWscaleMaxY, (m * (EN + 8000)) + b, EOWscaleMinY ) );
		pMDU->Line( 462, pos, 476, pos, dps::DEUATT_OVERBRIGHT );

		pos = Round( range( EOWscaleMaxY, (m * EN) + b, EOWscaleMinY ) );
		pMDU->Line( 460, pos, 470, pos, dps::DEUATT_OVERBRIGHT );

		pos = Round( range( EOWscaleMaxY, (m * (EN - 4000)) + b, EOWscaleMinY ) );
		pMDU->Line( 462, pos, 476, pos, dps::DEUATT_OVERBRIGHT );

		if (RPRED > ReadCOMPOOL_SD( SCP_RMOH ))
		{
			double EMOH = ReadCOMPOOL_SD( SCP_EMOH );
			pos = Round( range( EOWscaleMaxY, (m * EMOH) + b, EOWscaleMinY ) );
			pMDU->LeftArrowHollow( 464, pos );
		}

		pos = Round( range( EOWscaleMaxY, (m * EOW) + b, EOWscaleMinY ) );
		char att = 0;
		if ((EOW > ES) || (EOW < EMEP)) att = dps::DEUATT_FLASHING;
		pMDU->LeftTriangle( 464, pos, att );

		// digital data
		sprintf_s( cbuf, 8, "%3.0f", ReadCOMPOOL_SD( SCP_DSBFB_PCT ) );
		pMDU->mvprint( 38, 14, cbuf );
		sprintf_s( cbuf, 8, "%3.0f", ReadCOMPOOL_SD( SCP_SB_AUTO_CMD ) / 0.986 );
		pMDU->mvprint( 38, 15, cbuf );

		double NY = ReadCOMPOOL_SD( SCP_NY );
		sprintf_s( cbuf, 8, "%.3f", min(fabs( NY ), 0.999) );
		if (NY > 0.0) cbuf[0] = 'R';
		else if (NY < 0.0) cbuf[0] = 'L';
		else cbuf[0] = ' ';
		pMDU->mvprint( 29, 17, cbuf );

		double DRTI = ReadCOMPOOL_SD( SCP_DRTI );
		sprintf_s( cbuf, 8, "%.3f", min(fabs( DRTI ), 0.999) );
		if (DRTI > 0.0) cbuf[0] = 'R';
		else if (DRTI < 0.0) cbuf[0] = 'L';
		else cbuf[0] = ' ';
		pMDU->mvprint( 29, 18, cbuf );

		double DATRIM = ReadCOMPOOL_SD( SCP_DATRIM );
		sprintf_s( cbuf, 8, " %.1f", fabs( DATRIM ) );
		if (DATRIM > 0.0) cbuf[0] = 'R';
		else if (DATRIM < 0.0) cbuf[0] = 'L';
		pMDU->mvprint( 29, 19, cbuf );

		double DRTRIM = ReadCOMPOOL_SD( SCP_DRTRIM );
		sprintf_s( cbuf, 8, " %.1f", fabs( DRTRIM ) );
		if (DRTRIM > 0.0) cbuf[0] = 'L';
		else if (DRTRIM < 0.0) cbuf[0] = 'R';
		pMDU->mvprint( 29, 20, cbuf );

		// orbiter symbol
		int x = Round( VSX1C + (RPRED * VSX1C1) );
		int y = Round( VSY1C + (ReadCOMPOOL_SD( SCP_H ) * VSY1C1) );
		double rot = ReadCOMPOOL_SD( SCP_GAMMA ) * RAD;
		pMDU->OrbiterSymbolSide( x, y, rot, dps::DEUATT_OVERBRIGHT );
		return;
	}

	void GeneralDisplays::OnPaint_VERTSIT2_PASS( vc::MDU* pMDU ) const
	{
		char cbuf[8];
		double H = ReadCOMPOOL_SD( SCP_H );
		double RPRED = ReadCOMPOOL_IS( SCP_TG_END ) == 1 ? hypot( ReadCOMPOOL_SD( SCP_X ), ReadCOMPOOL_SD( SCP_Y ) ) : ReadCOMPOOL_SD( SCP_RPRED );

		PrintCommonHeader( "  VERT SIT 2", pMDU );

		pMDU->mvprint( 17, 2, "317" );
		pMDU->mvprint( 26, 2, "255" );
		pMDU->mvprint( 42, 3, "214" );
		pMDU->mvprint( 15, 11, "270" );
		pMDU->mvprint( 14, 16, "214" );
		pMDU->mvprint( 5, 17, "317" );
		pMDU->mvprint( 4, 20, "285" );

		pMDU->Theta( 43, 6 );
		pMDU->mvprint( 48, 6, "E/W" );
		pMDU->mvprint( 48, 11, "STN" );
		pMDU->mvprint( 48, 15, "NOM" );
		pMDU->mvprint( 48, 20, "MEP" );

		pMDU->mvprint( 38, 11, "NOSE HI" );
		pMDU->mvprint( 29, 14, "SPD BK" );
		pMDU->mvprint( 32, 15, "CMD" );
		pMDU->mvprint( 38, 20, "NOSE LO" );

		pMDU->mvprint( 18, 16, "ACCEL" );
		pMDU->mvprint( 21, 17, "NY" );
		pMDU->mvprint( 21, 18, "NY TRIM" );
		pMDU->mvprint( 21, 19, "AIL" );
		pMDU->mvprint( 21, 20, "RUD" );
		//pMDU->mvprint( 21, 21, "TGT NZ" );// OPS 6 only

		if (ReadCOMPOOL_IS( SCP_TG_END ) == 1) pMDU->mvprint( 38, 17, "A/L", dps::DEUATT_FLASHING );

		// alt/rng lines
		pMDU->Line( 188, 45, 72, 269 );

		pMDU->Line( 266, 42, 72, 277 );

		pMDU->Line( 422, 54, 132, 227 );
		pMDU->Line( 132, 227, 72, 292 );

		pMDU->Line( 72, 269, 72, 292 );

		// theta / E/W scale
		const int EOWscaleMaxY = 115;
		const int EOWscaleMinY = 339;
		const int EOWscaleSTRNY = 179;
		const int EOWscaleMEPY = 292;

		pMDU->Line( 464, EOWscaleMinY, 464, EOWscaleMaxY );
		pMDU->Line( 460, EOWscaleSTRNY, 470, EOWscaleSTRNY );
		pMDU->Line( 460, EOWscaleMEPY, 470, EOWscaleMEPY );

		// E/W side
		if (H > 20000.0)
		{
			double EOW = ReadCOMPOOL_SD( SCP_EOW );
			double EN = ReadCOMPOOL_SD( SCP_EN );
			double ES = ReadCOMPOOL_SD( SCP_ES );
			double EMEP = ReadCOMPOOL_SD( SCP_EMEP );

			double m = (EOWscaleSTRNY - EOWscaleMEPY) / (ES - EMEP);// [px/ft]
			double b = EOWscaleMEPY - (EMEP * m);// [px]

			int pos = Round( range( EOWscaleMaxY, (m * (EN + 8000)) + b, EOWscaleMinY ) );
			pMDU->Line( 462, pos, 476, pos, dps::DEUATT_OVERBRIGHT );

			pos = Round( range( EOWscaleMaxY, (m * EN) + b, EOWscaleMinY ) );
			pMDU->Line( 460, pos, 470, pos, dps::DEUATT_OVERBRIGHT );

			pos = Round( range( EOWscaleMaxY, (m * (EN - 4000)) + b, EOWscaleMinY ) );
			pMDU->Line( 462, pos, 476, pos, dps::DEUATT_OVERBRIGHT );

			if (RPRED > ReadCOMPOOL_SD( SCP_RMOH ))
			{
				double EMOH = ReadCOMPOOL_SD( SCP_EMOH );
				pos = Round( range( EOWscaleMaxY, (m * EMOH) + b, EOWscaleMinY ) );
				pMDU->LeftArrowHollow( 464, pos );
			}

			pos = Round( range( EOWscaleMaxY, (m * EOW) + b, EOWscaleMinY ) );
			char att = 0;
			if ((EOW > ES) || (EOW < EMEP)) att = dps::DEUATT_FLASHING;
			pMDU->LeftTriangle( 464, pos, att );
		}

		// digital data
		sprintf_s( cbuf, 8, "%3.0f", ReadCOMPOOL_SD( SCP_DSBFB_PCT ) );
		pMDU->mvprint( 38, 14, cbuf );
		sprintf_s( cbuf, 8, "%3.0f", ReadCOMPOOL_SD( SCP_SB_AUTO_CMD ) / 0.986 );
		pMDU->mvprint( 38, 15, cbuf );

		double NY = ReadCOMPOOL_SD( SCP_NY );
		sprintf_s( cbuf, 8, "%.3f", range( -0.999, fabs( NY ), 0.999 ) );
		if (NY > 0.0) cbuf[0] = 'R';
		else if (NY < 0.0) cbuf[0] = 'L';
		else cbuf[0] = ' ';
		pMDU->mvprint( 29, 17, cbuf );

		double DRTI = ReadCOMPOOL_SD( SCP_DRTI );
		sprintf_s( cbuf, 8, "%.3f", min(fabs( DRTI ), 0.999) );
		if (DRTI > 0.0) cbuf[0] = 'R';
		else if (DRTI < 0.0) cbuf[0] = 'L';
		else cbuf[0] = ' ';
		pMDU->mvprint( 29, 18, cbuf );

		double DATRIM = ReadCOMPOOL_SD( SCP_DATRIM );
		sprintf_s( cbuf, 8, " %.1f", fabs( DATRIM ) );
		if (DATRIM > 0.0) cbuf[0] = 'R';
		else if (DATRIM < 0.0) cbuf[0] = 'L';
		pMDU->mvprint( 29, 19, cbuf );

		double DRTRIM = ReadCOMPOOL_SD( SCP_DRTRIM );
		sprintf_s( cbuf, 8, " %.1f", fabs( DRTRIM ) );
		if (DRTRIM > 0.0) cbuf[0] = 'L';
		else if (DRTRIM < 0.0) cbuf[0] = 'R';
		pMDU->mvprint( 29, 20, cbuf );

		// orbiter symbol
		int x = Round( VSX2C + (RPRED * VSX2C1) );
		int y = Round( VSY2C + (H * VSY2C1) );
		double rot = ReadCOMPOOL_SD( SCP_GAMMA ) * RAD;
		pMDU->OrbiterSymbolSide( x, y, rot, dps::DEUATT_OVERBRIGHT );
		return;
	}

	// INFO below is the pre OI-32 PASS ASCENT TRAJ display
	//void GeneralDisplays::OnPaint_ASCENTTRAJ_PASS( vc::MDU* pMDU ) const
	//{
	//	// PASS LAUNCH TRJ/PASS ASCENT TRAJ
	//	switch(GetMajorMode())
	//	{
	//		case 101:
	//			PrintCommonHeader( "  LAUNCH TRAJ", pMDU );
	//			break;
	//		case 102:
	//		case 103:
	//			PrintCommonHeader( "  ASCENT TRAJ", pMDU );
	//			break;
	//	}
	//
	//	// static parts (labels)
	//	pMDU->mvprint( 9, 5, "CO" );
	//	pMDU->mvprint( 25, 5, "PD" );
	//	pMDU->mvprint( 32, 5, "PD3" );
	//
	//	pMDU->mvprint( 36, 6, "ABORT    ARM" );
	//	pMDU->mvprint( 33, 7, "3 E/O" );
	//	pMDU->mvprint( 33, 8, "2 E/O" );
	//	pMDU->mvprint( 46, 8, "2" );
	//	pMDU->mvprint( 31, 9, "ABORT      4" );
	//	pMDU->mvprint( 31, 10, "YAW STEER  5" );
	//
	//	pMDU->mvprint( 10, 7, "GUID" );
	//	pMDU->mvprint( 10, 8, "TMECO   :" );
	//	pMDU->mvprint( 10, 9, "PRPLT" );
	//	pMDU->mvprint( 7, 12, "6  SERC" );
	//
	//	pMDU->mvprint( 5, 13, "O" );
	//
	//	pMDU->mvprint( 46, 13, "GO" );
	//	pMDU->mvprint( 39, 15, "RTLS" );
	//
	//
	//	// static parts (lines)
	//
	//	//Nominal ascent line
	//	pMDU->Line( 181, 212, 191, 176 );
	//	pMDU->Line( 191, 176, 233, 128 );
	//	pMDU->Line( 233, 128, 255, 117 );
	//
	//	//EO at Lift-Off line
	//	pMDU->Line( 159, 212, 174, 138 );
	//	pMDU->Line( 174, 138, 78, 195 );
	//	pMDU->Line( 78, 195, 58, 201 );
	//	pMDU->Line( 58, 201, 21, 176 );
	//
	//	pMDU->Line( 183, 119, 176, 122 );
	//	pMDU->Line( 176, 122, 81, 187 );
	//
	//	//Q = 2 line
	//	pMDU->Line( 38, 187, 11, 179 );
	//
	//	//Q = 10 line
	//	pMDU->Line( 38, 171, 11, 157 );
	//
	//	//Hdot indicator
	//	pMDU->Line( 17, 30, 11, 30 );
	//	pMDU->Line( 11, 30, 11, 206 );
	//	pMDU->Line( 11, 206, 17, 206 );
	//	pMDU->Line( 11, 118, 17, 118 );
	//
	//	//DR indicator
	//	pMDU->Line( 26, 27, 247, 27 );
	//
	//	//PD3 Mark
	//	pMDU->Line( 164, 27, 164, 35 );
	//
	//	//PD Mark
	//	pMDU->Line( 128, 27, 128, 35 );
	//
	//	//CO Mark
	//	pMDU->Line( 47, 27, 47, 35 );
	//
	//
	//	// dynamic parts
	//	char cbuf[64];
	//	int tmp = 0;
	//
	//	if ((GetMajorMode() == 103) && (pSSME_Operations->GetMECOConfirmedFlag() == false))
	//	{
	//		tmp = Round( STS()->GetMET() + timeRemaining );
	//		sprintf_s( cbuf, 64, "%02d", (tmp - (tmp % 60)) / 60 );
	//		pMDU->mvprint( 16, 8, cbuf );
	//		sprintf_s( cbuf, 64, "%02d", (tmp % 60) );
	//		pMDU->mvprint( 19, 8, cbuf );
	//	}
	//
	//	tmp = STS()->GetETPropellant();
	//	if (tmp < 0) tmp = 0;
	//	sprintf_s( cbuf, 64, "%2d", tmp );
	//	pMDU->mvprint( 19, 9, cbuf );
	//
	//	if ((pSRBSepSequence->GetPC50Flag() == true) && (GetMajorMode() == 102)) pMDU->mvprint( 10, 10, "PC<50" );
	//
	//	if ((pSRBSepSequence->GetSRBSEPINHFlag() == true) || (pETSepSequence->GetETSEPINHFlag() == true)) pMDU->mvprint( 10, 11, "SEP INH" );
	//
	//	if (enaSERC == true) pMDU->mvprint( 15, 12, "ON", dps::DEUATT_OVERBRIGHT );
	//
	//	if (EOVI[0] != 0)
	//	{
	//		sprintf_s( cbuf, 64, "EO VI %5.0f", EOVI[0] );
	//		pMDU->mvprint( 7, 13, cbuf );
	//	}
	//	if (EOVI[1] != 0)
	//	{
	//		sprintf_s( cbuf, 64, "EO VI %5.0f", EOVI[1] );
	//		pMDU->mvprint( 7, 14, cbuf, dps::DEUATT_OVERBRIGHT );
	//	}
	//
	//	VECTOR3 LVLH_Vel;
	//	STS()->GetGPCLVLHVel(0, LVLH_Vel);
	//
	//	double Ref_hdot = 0.0;
	//	bool bShowHDot = (STS()->GetGPCRefHDot(0, Ref_hdot) == VARSTATE_OK);
	//
	//	//Hdot indicator
	//	if(bShowHDot)
	//	{
	//		double HDot_Error = -LVLH_Vel.z - Ref_hdot;
	//		char att = dps::DEUATT_OVERBRIGHT;
	//
	//		if(HDot_Error > 200.0)
	//		{
	//			HDot_Error = 200.0;
	//			att += dps::DEUATT_FLASHING;
	//		}
	//		else if (HDot_Error < -200.0)
	//		{
	//			HDot_Error = -200.0;
	//			att += dps::DEUATT_FLASHING;
	//		}
	//
	//		short sHDot_pry = -static_cast<short>(HDot_Error/200.0 * 88);
	//
	//		pMDU->Line( 11, 118 + sHDot_pry, 6, 113 + sHDot_pry, att );
	//		pMDU->Line( 6, 113 + sHDot_pry, 6, 123 + sHDot_pry, att );
	//		pMDU->Line( 6, 123 + sHDot_pry, 11, 118 + sHDot_pry, att );
	//	}
	//
	//	if (GetMajorMode() >= 103)// HACK because thrustAcceleration is only calculated in MM103
	//	{
	//		//Current vehicle state:
	//		double VHI = LVLH_Vel.x;
	//		double Altitude = STS()->GetAltitude() * MPS2FPS;
	//
	//		if(Altitude > 155500 && VHI < 10000)
	//		{
	//			//Draw triangle for state vector
	//			short stY = static_cast<short>(255*(1.13256 - (Altitude/513955.985)));
	//			short stX = static_cast<short>(255*(0.36194 + (VHI/15672.3964)));
	//			pMDU->Line( stX, stY - 3, stX - 3, stY + 3 );
	//			pMDU->Line( stX - 3, stY + 3, stX + 3, stY + 3 );
	//			pMDU->Line( stX + 3, stY + 3, stX, stY - 3 );
	//		}
	//
	//		// HACK using constant 12º for SSME offset
	//		// 30s predictor
	//		double dv30 = thrustAcceleration * cos( STS()->GetSlipAngle() ) * 30 * MPS2FPS;
	//		VHI += dv30;
	//		Altitude += -LVLH_Vel.z * 30 + (((thrustAcceleration * sin( STS()->GetPitch() - (12 * RAD * sign( cos( STS()->GetBank() ) )) )) - G ) * 450 * MPS2FPS);
	//
	//		if(Altitude > 155500 && VHI < 10000)
	//		{
	//			//Draw circle for 30s predictor
	//			short stY = static_cast<short>(255*(1.13256 - (Altitude/513955.985)));
	//			short stX = static_cast<short>(255*(0.36194 + (VHI/15672.3964)));
	//			pMDU->Ellipse( stX - 3, stY - 3, stX + 3, stY + 3 );
	//		}
	//
	//		// 60s predictor
	//		VHI += dv30;
	//		Altitude = (STS()->GetAltitude() * MPS2FPS) - (LVLH_Vel.z * 60) + ((thrustAcceleration * sin( STS()->GetPitch() - (12 * RAD * sign( cos( STS()->GetBank() ) )) )) - G ) * 1800 * MPS2FPS;
	//
	//		if(Altitude > 155500 && VHI < 10000)
	//		{
	//			//Draw circle for 60s predictor
	//			short stY = static_cast<short>(255*(1.13256 - (Altitude/513955.985)));
	//			short stX = static_cast<short>(255*(0.36194 + (VHI/15672.3964)));
	//			pMDU->Ellipse( stX - 3, stY - 3, stX + 3, stY + 3 );
	//		}
	//	}
	//	return;
	//}

	//short GeneralDisplays::GetGPCRefHDot(unsigned short usGPCID, double &fRefHDot)
	//{
	//	switch (GetMajorMode())
	//	{
	//		case 102:
	//			if (met < 30.0)
	//			{
	//				fRefHDot = met * 21.33;
	//			}
	//			else if (met < 50.0)
	//			{
	//				fRefHDot = 640 + (met - 30.0) * 16.7;
	//			}
	//			else if (met < 70.0)
	//			{
	//				fRefHDot = 974 + (met - 50.0) * 21.65;
	//			}
	//			else if (met < 90)
	//			{
	//				fRefHDot = 1407 + (met - 70.0) * 23.4;
	//			}
	//			else if (met < 110.0)
	//			{
	//				fRefHDot = 1875 + (met - 90.0) * 15.6;
	//			}
	//			else {
	//				fRefHDot = 2187 + (met - 110.0) * 15.6;
	//			}
	//			//TODO: Generate VSpeed Table.
	//			return VARSTATE_OK;
	//	}
	//	return VARSTATE_MISSING;
	//}

	unsigned short GeneralDisplays::GetGPCLVLHVel( VECTOR3 &vel ) const
	{
		VECTOR3 tmpVel;
		VECTOR3 LVLH_X;
		VECTOR3 LVLH_Y;
		VECTOR3 LVLH_Z;
		STS()->GetRelativeVel(STS()->GetSurfaceRef(), tmpVel);
		STS()->GetRelativePos(STS()->GetSurfaceRef(), LVLH_Z);

		double magVel = length(tmpVel);

		if (magVel != 0.0)
		{
			LVLH_X = tmpVel / length(tmpVel);
			LVLH_Z = -LVLH_Z / length(LVLH_Z);

			LVLH_Y = crossp(LVLH_X, LVLH_Z);

			vel.x = dotp(LVLH_X, tmpVel) * MPS2FPS;
			vel.y = dotp(LVLH_Y, tmpVel)* MPS2FPS;
			vel.z = dotp(LVLH_Z, tmpVel) * MPS2FPS;

			return 0;
		}
		else return 1;
	}
};

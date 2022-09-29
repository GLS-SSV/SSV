/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/05/10   GLS
2020/05/29   GLS
2020/06/01   GLS
2020/06/20   GLS
2020/06/23   GLS
2021/06/30   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/03/29   GLS
2022/04/02   GLS
2022/04/07   GLS
2022/04/17   GLS
2022/04/26   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "SSME_BLOCK_II.h"
#include "../Atlantis.h"
#include "PneumaticControlAssembly.h"
#include "MPS.h"
#include "SolenoidValve.h"
#include "HydraulicActuatedValve.h"
#include "PressureActuatedValve.h"
#include "MPSdefs.h"
#include <EngConst.h>
#include <Orbitersdk.h>


namespace mps
{
	const char* MESHNAME_BLOCK_II = "SSV\\OV\\SSME_FPL";

	// SSME Block II model values
	//inline constexpr double SSME_BLOCK_II_RPL_THRUST = 2090664.159; //100% thrust
	//inline constexpr double SSME_BLOCK_II_NPL_THRUST = 2170732.15; //Nominal "104%" thrust
	constexpr double SSME_BLOCK_II_FPL_THRUST = 2278824.21641;//2275094.273; //109% thrust
	constexpr int SSME_BLOCK_II_FPL = 109;// % RPL
	constexpr double SSME_BLOCK_II_RPL_PC_PRESS = 2746.788990825688073394495412844;// extrapolated from: 109% = 2994psia
	constexpr double SSME_BLOCK_II_ISP0 = 453 * 9.80665;
	constexpr double SSME_BLOCK_II_ISP1 = 363 * 9.80665;
	constexpr double SSME_BLOCK_II_MASS = 7748.0 * LBM2KG;// [kg]
	// BLOCK IIA = 7488;
	constexpr VECTOR3 SSME_BLOCK_II_CG[3] = {// TODO move c.g. aft "a bit" (currently it is engine attachment)
		{0.0, 0.6651, -12.464},// Xo+1445.0 Yo+0.0 Zo+443.0
		{-1.3462, -1.884044, -13.052518},// Xo+1468.17 Yo-53.0 Zo+342.64
		{1.3462, -1.884044, -13.052518}};// Xo+1468.17 Yo+53.0 Zo+342.64

	// pressure
	inline constexpr int SSME_BLOCK_II_FPB_PP = 0;
	inline constexpr int SSME_BLOCK_II_OPB_PP = 1;
	inline constexpr int SSME_BLOCK_II_LPOT_DP_A = 2;
	inline constexpr int SSME_BLOCK_II_LPOT_DP_B = 3;
	inline constexpr int SSME_BLOCK_II_LPFT_DP_A = 4;
	inline constexpr int SSME_BLOCK_II_LPFT_DP_B = 5;
	inline constexpr int SSME_BLOCK_II_HPOTP_DP_A = 6;
	inline constexpr int SSME_BLOCK_II_HPOTP_DP_B = 7;
	inline constexpr int SSME_BLOCK_II_HPFTP_DP_A = 8;
	inline constexpr int SSME_BLOCK_II_HPFTP_DP_B = 9;
	inline constexpr int SSME_BLOCK_II_HPOTPBP_DP_A = 10;
	inline constexpr int SSME_BLOCK_II_HPOTPBP_DP_B = 11;
	inline constexpr int SSME_BLOCK_II_FS_PP_A = 12;
	inline constexpr int SSME_BLOCK_II_FS_PP_B = 13;
	inline constexpr int SSME_BLOCK_II_MCC_P_A1 = 14;
	inline constexpr int SSME_BLOCK_II_MCC_P_B1 = 15;
	inline constexpr int SSME_BLOCK_II_MCC_P_A2 = 16;
	inline constexpr int SSME_BLOCK_II_MCC_P_B2 = 17;
	inline constexpr int SSME_BLOCK_II_HPOTP_IS_A = 18;
	inline constexpr int SSME_BLOCK_II_HPOTP_IS_B = 19;
	inline constexpr int SSME_BLOCK_II_PNEU_SD_P_A = 20;
	inline constexpr int SSME_BLOCK_II_PNEU_SD_P_B = 21;

	// temp
	inline constexpr int SSME_BLOCK_II_HPFT_DT_A2 = 0;
	inline constexpr int SSME_BLOCK_II_HPFT_DT_B2 = 1;
	inline constexpr int SSME_BLOCK_II_HPFT_DT_A3 = 2;
	inline constexpr int SSME_BLOCK_II_HPFT_DT_B3 = 3;
	inline constexpr int SSME_BLOCK_II_HPOT_DT_A2 = 4;
	inline constexpr int SSME_BLOCK_II_HPOT_DT_B2 = 5;
	inline constexpr int SSME_BLOCK_II_HPOT_DT_A3 = 6;
	inline constexpr int SSME_BLOCK_II_HPOT_DT_B3 = 7;
	inline constexpr int SSME_BLOCK_II_PBP_DT_A = 8;
	inline constexpr int SSME_BLOCK_II_PBP_DT_B = 9;
	inline constexpr int SSME_BLOCK_II_LPFP_DT_A = 10;
	inline constexpr int SSME_BLOCK_II_LPFP_DT_B = 11;
	inline constexpr int SSME_BLOCK_II_MOV_HT_A = 12;
	inline constexpr int SSME_BLOCK_II_MOV_HT_B = 13;
	inline constexpr int SSME_BLOCK_II_MFV_HT_A = 14;
	inline constexpr int SSME_BLOCK_II_MFV_HT_B = 15;

	// flow
	inline constexpr int SSME_BLOCK_II_FF_A1 = 0;
	inline constexpr int SSME_BLOCK_II_FF_B1 = 1;
	inline constexpr int SSME_BLOCK_II_FF_A2 = 2;
	inline constexpr int SSME_BLOCK_II_FF_B2 = 3;

	// speed
	inline constexpr int SSME_BLOCK_II_LPFTP_SS_A = 0;
	inline constexpr int SSME_BLOCK_II_LPFTP_SS_B = 1;
	inline constexpr int SSME_BLOCK_II_HPFTP_SS_A = 2;
	inline constexpr int SSME_BLOCK_II_HPFTP_SS_B = 3;



	SSME_BLOCK_II::SSME_BLOCK_II( AtlantisSubsystemDirector* _director, const string& _ident, unsigned short nID, int controllertype, const string& sw, HeSysEng* HeSys ):SSME( _director, _ident, nID, MESHNAME_BLOCK_II, controllertype, sw, HeSys )
	{
#ifdef _MPSDEBUG
		oapiWriteLogV( " SSME_BLOCK_II::SSME_BLOCK_II in || nID:%d|controllertype:%d|sw:%s", nID, controllertype, sw.c_str() );
#endif// _MPSDEBUG

		// set specific SSME BLOCK II parameters
		FPL = SSME_BLOCK_II_FPL;
		FPL_THRUST = SSME_BLOCK_II_FPL_THRUST;
		RPL_PC_PRESS = SSME_BLOCK_II_RPL_PC_PRESS;
		ISP0 = SSME_BLOCK_II_ISP0;
		ISP1 = SSME_BLOCK_II_ISP1;

		posMFV = 0;
		posMOV = 0;

		IMSLHeUsage = 20.8 + (0.5 * oapiRand());// IMSL max 21.31884

		Sensor_Press[SSME_BLOCK_II_FPB_PP] = Sensor( 0, 5000 );
		Sensor_Press[SSME_BLOCK_II_OPB_PP] = Sensor( 0, 5000 );
		Sensor_Press[SSME_BLOCK_II_LPOT_DP_A] = Sensor( 0, 5000 );
		Sensor_Press[SSME_BLOCK_II_LPOT_DP_B] = Sensor( 0, 5000 );
		Sensor_Press[SSME_BLOCK_II_LPFT_DP_A] = Sensor( 0, 5000 );
		Sensor_Press[SSME_BLOCK_II_LPFT_DP_B] = Sensor( 0, 5000 );
		Sensor_Press[SSME_BLOCK_II_HPOTP_DP_A] = Sensor( 0, 8000 );
		Sensor_Press[SSME_BLOCK_II_HPOTP_DP_B] = Sensor( 0, 8000 );
		Sensor_Press[SSME_BLOCK_II_HPFTP_DP_A] = Sensor( 0, 8000 );
		Sensor_Press[SSME_BLOCK_II_HPFTP_DP_B] = Sensor( 0, 8000 );
		Sensor_Press[SSME_BLOCK_II_HPOTPBP_DP_A] = Sensor( 0, 8000 );
		Sensor_Press[SSME_BLOCK_II_HPOTPBP_DP_B] = Sensor( 0, 8000 );
		Sensor_Press[SSME_BLOCK_II_FS_PP_A] = Sensor( 0, 5000 );
		Sensor_Press[SSME_BLOCK_II_FS_PP_B] = Sensor( 0, 5000 );
		Sensor_Press[SSME_BLOCK_II_MCC_P_A1] = Sensor( 0, 5000 );
		Sensor_Press[SSME_BLOCK_II_MCC_P_B1] = Sensor( 0, 5000 );
		Sensor_Press[SSME_BLOCK_II_MCC_P_A2] = Sensor( 0, 5000 );
		Sensor_Press[SSME_BLOCK_II_MCC_P_B2] = Sensor( 0, 5000 );
		Sensor_Press[SSME_BLOCK_II_HPOTP_IS_A] = Sensor( 0, 5000 );
		Sensor_Press[SSME_BLOCK_II_HPOTP_IS_B] = Sensor( 0, 5000 );
		Sensor_Press[SSME_BLOCK_II_PNEU_SD_P_A] = Sensor( 0, 1500 );
		Sensor_Press[SSME_BLOCK_II_PNEU_SD_P_B] = Sensor( 0, 1500 );
		Sensor_Temp[SSME_BLOCK_II_HPFT_DT_A2] = Sensor( 0, 2450 );
		Sensor_Temp[SSME_BLOCK_II_HPFT_DT_B2] = Sensor( 0, 2450 );
		Sensor_Temp[SSME_BLOCK_II_HPFT_DT_A3] = Sensor( 0, 2450 );
		Sensor_Temp[SSME_BLOCK_II_HPFT_DT_B3] = Sensor( 0, 2450 );
		Sensor_Temp[SSME_BLOCK_II_HPOT_DT_A2] = Sensor( 0, 2450 );
		Sensor_Temp[SSME_BLOCK_II_HPOT_DT_B2] = Sensor( 0, 2450 );
		Sensor_Temp[SSME_BLOCK_II_HPOT_DT_A3] = Sensor( 0, 2450 );
		Sensor_Temp[SSME_BLOCK_II_HPOT_DT_B3] = Sensor( 0, 2450 );
		Sensor_Temp[SSME_BLOCK_II_PBP_DT_A] = Sensor( 0, 2450 );
		Sensor_Temp[SSME_BLOCK_II_PBP_DT_B] = Sensor( 0, 2450 );
		Sensor_Temp[SSME_BLOCK_II_LPFP_DT_A] = Sensor( 0, 2450 );
		Sensor_Temp[SSME_BLOCK_II_LPFP_DT_B] = Sensor( 0, 2450 );
		Sensor_Temp[SSME_BLOCK_II_MOV_HT_A] = Sensor( 0, 2450 );
		Sensor_Temp[SSME_BLOCK_II_MOV_HT_B] = Sensor( 0, 2450 );
		Sensor_Temp[SSME_BLOCK_II_MFV_HT_A] = Sensor( 0, 2450 );
		Sensor_Temp[SSME_BLOCK_II_MFV_HT_B] = Sensor( 0, 2450 );
		Sensor_Flow[SSME_BLOCK_II_FF_A1] = Sensor( 0, 5000 );
		Sensor_Flow[SSME_BLOCK_II_FF_B1] = Sensor( 0, 5000 );
		Sensor_Flow[SSME_BLOCK_II_FF_A2] = Sensor( 0, 5000 );
		Sensor_Flow[SSME_BLOCK_II_FF_B2] = Sensor( 0, 5000 );
		Sensor_Speed[SSME_BLOCK_II_LPFTP_SS_A] = Sensor( 0, 40000 );
		Sensor_Speed[SSME_BLOCK_II_LPFTP_SS_B] = Sensor( 0, 40000 );
		Sensor_Speed[SSME_BLOCK_II_HPFTP_SS_A] = Sensor( 0, 40000 );
		Sensor_Speed[SSME_BLOCK_II_HPFTP_SS_B] = Sensor( 0, 40000 );

#ifdef _MPSDEBUG
		oapiWriteLog( " SSME_BLOCK_II::SSME_BLOCK_II out" );
#endif// _MPSDEBUG
		return;
	}

	SSME_BLOCK_II::~SSME_BLOCK_II( void )
	{
		return;
	}

	void SSME_BLOCK_II::OnSaveState( FILEHANDLE scn ) const
	{
		SSME::OnSaveState( scn );
		return;
	}

	bool SSME_BLOCK_II::OnParseLine( const char* line )
	{
		return SSME::OnParseLine( line );
	}

	double SSME_BLOCK_II::GetSubsystemMass( void ) const
	{
		return SSME_BLOCK_II_MASS;
	}

	bool SSME_BLOCK_II::GetSubsystemCoG( VECTOR3& CoG ) const
	{
		CoG = SSME_BLOCK_II_CG[ID - 1];
		return true;
	}

	void SSME_BLOCK_II::ConnectSensors( DiscreteBundle* IEchA_Press, DiscreteBundle* IEchB_Press, DiscreteBundle* IEchA_Temp, DiscreteBundle* IEchB_Temp, DiscreteBundle* IEchA_Flow, DiscreteBundle* IEchB_Flow, DiscreteBundle* IEchA_Speed, DiscreteBundle* IEchB_Speed )
	{
		Sensor_Press[SSME_BLOCK_II_FPB_PP].Connect( IEchA_Press, 0 );// HACK (a big one), just on chA for now
		Sensor_Press[SSME_BLOCK_II_OPB_PP].Connect( IEchA_Press, 1 );// HACK (a big one), just on chA for now
		Sensor_Press[SSME_BLOCK_II_LPOT_DP_A].Connect( IEchA_Press, 2 );
		Sensor_Press[SSME_BLOCK_II_LPOT_DP_B].Connect( IEchB_Press, 2 );
		Sensor_Press[SSME_BLOCK_II_LPFT_DP_A].Connect( IEchA_Press, 3 );
		Sensor_Press[SSME_BLOCK_II_LPFT_DP_B].Connect( IEchB_Press, 3 );
		Sensor_Press[SSME_BLOCK_II_HPOTP_DP_A].Connect( IEchA_Press, 4 );
		Sensor_Press[SSME_BLOCK_II_HPOTP_DP_B].Connect( IEchB_Press, 4 );
		Sensor_Press[SSME_BLOCK_II_HPFTP_DP_A].Connect( IEchA_Press, 5 );
		Sensor_Press[SSME_BLOCK_II_HPFTP_DP_B].Connect( IEchB_Press, 5 );
		Sensor_Press[SSME_BLOCK_II_HPOTPBP_DP_A].Connect( IEchA_Press, 6 );
		Sensor_Press[SSME_BLOCK_II_HPOTPBP_DP_B].Connect( IEchB_Press, 6 );
		Sensor_Press[SSME_BLOCK_II_FS_PP_A].Connect( IEchA_Press, 7 );
		Sensor_Press[SSME_BLOCK_II_FS_PP_B].Connect( IEchB_Press, 7 );
		Sensor_Press[SSME_BLOCK_II_MCC_P_A1].Connect( IEchA_Press, 8 );
		Sensor_Press[SSME_BLOCK_II_MCC_P_B1].Connect( IEchB_Press, 8 );
		Sensor_Press[SSME_BLOCK_II_MCC_P_A2].Connect( IEchA_Press, 9 );
		Sensor_Press[SSME_BLOCK_II_MCC_P_B2].Connect( IEchB_Press, 9 );
		Sensor_Press[SSME_BLOCK_II_HPOTP_IS_A].Connect( IEchA_Press, 10 );
		Sensor_Press[SSME_BLOCK_II_HPOTP_IS_B].Connect( IEchB_Press, 10 );
		Sensor_Press[SSME_BLOCK_II_PNEU_SD_P_A].Connect( IEchA_Press, 11 );
		Sensor_Press[SSME_BLOCK_II_PNEU_SD_P_B].Connect( IEchB_Press, 11 );

		Sensor_Temp[SSME_BLOCK_II_HPFT_DT_A2].Connect( IEchA_Temp, 0 );
		Sensor_Temp[SSME_BLOCK_II_HPFT_DT_B2].Connect( IEchB_Temp, 0 );
		Sensor_Temp[SSME_BLOCK_II_HPFT_DT_A3].Connect( IEchA_Temp, 1 );
		Sensor_Temp[SSME_BLOCK_II_HPFT_DT_B3].Connect( IEchB_Temp, 1 );
		Sensor_Temp[SSME_BLOCK_II_HPOT_DT_A2].Connect( IEchA_Temp, 2 );
		Sensor_Temp[SSME_BLOCK_II_HPOT_DT_B2].Connect( IEchB_Temp, 2 );
		Sensor_Temp[SSME_BLOCK_II_HPOT_DT_A3].Connect( IEchA_Temp, 3 );
		Sensor_Temp[SSME_BLOCK_II_HPOT_DT_B3].Connect( IEchB_Temp, 3 );
		Sensor_Temp[SSME_BLOCK_II_PBP_DT_A].Connect( IEchA_Temp, 4 );
		Sensor_Temp[SSME_BLOCK_II_PBP_DT_B].Connect( IEchB_Temp, 4 );
		Sensor_Temp[SSME_BLOCK_II_LPFP_DT_A].Connect( IEchA_Temp, 5 );
		Sensor_Temp[SSME_BLOCK_II_LPFP_DT_B].Connect( IEchB_Temp, 5 );
		Sensor_Temp[SSME_BLOCK_II_MOV_HT_A].Connect( IEchA_Temp, 6 );
		Sensor_Temp[SSME_BLOCK_II_MOV_HT_B].Connect( IEchB_Temp, 6 );
		Sensor_Temp[SSME_BLOCK_II_MFV_HT_A].Connect( IEchA_Temp, 7 );
		Sensor_Temp[SSME_BLOCK_II_MFV_HT_B].Connect( IEchB_Temp, 7 );

		Sensor_Flow[SSME_BLOCK_II_FF_A1].Connect( IEchA_Flow, 0 );
		Sensor_Flow[SSME_BLOCK_II_FF_B1].Connect( IEchB_Flow, 0 );
		Sensor_Flow[SSME_BLOCK_II_FF_A2].Connect( IEchA_Flow, 1 );
		Sensor_Flow[SSME_BLOCK_II_FF_B2].Connect( IEchB_Flow, 1 );

		Sensor_Speed[SSME_BLOCK_II_LPFTP_SS_A].Connect( IEchA_Speed, 0 );
		Sensor_Speed[SSME_BLOCK_II_LPFTP_SS_B].Connect( IEchB_Speed, 0 );
		Sensor_Speed[SSME_BLOCK_II_HPFTP_SS_A].Connect( IEchA_Speed, 1 );
		Sensor_Speed[SSME_BLOCK_II_HPFTP_SS_B].Connect( IEchB_Speed, 1 );
		return;
	}

	void SSME_BLOCK_II::RUN1( double time, double dt )// pre-start
	{
		// TODO do purges and stuff....
		// TODO "MFV moves" AFTER propellant drop (it moves before in testing)
		double temp = 0;
		if ((ptrMFV->GetPos() != 0) &&// MFV moves -> RUN2
			((Igniter_FPB[0] == true) || (Igniter_FPB[1] == true)) && // at least 1 of the 2 igniters in each chamber must be on
			((Igniter_OPB[0] == true) || (Igniter_OPB[1] == true)) &&
			((Igniter_MCC[0] == true) || (Igniter_MCC[1] == true)))
		{
			modeltime = time;
			modelmode = 2;

			STS()->SetSSMEGH2burn( ID, true );
		}

		// set sensor readings
		// press
		temp = PCA->GetPressFuelPreburnerPurge();
		Sensor_Press[SSME_BLOCK_II_FPB_PP].SetValue( temp );
		temp = PCA->GetPressOxidizerPreburnerPurge();
		Sensor_Press[SSME_BLOCK_II_OPB_PP].SetValue( temp );
		Sensor_Press[SSME_BLOCK_II_LPOT_DP_A].SetValue( 52 );
		Sensor_Press[SSME_BLOCK_II_LPOT_DP_B].SetValue( 53 );
		Sensor_Press[SSME_BLOCK_II_LPFT_DP_A].SetValue( 54 );
		Sensor_Press[SSME_BLOCK_II_LPFT_DP_B].SetValue( 55 );
		Sensor_Press[SSME_BLOCK_II_HPOTP_DP_A].SetValue( 56 );
		Sensor_Press[SSME_BLOCK_II_HPOTP_DP_B].SetValue( 57 );
		Sensor_Press[SSME_BLOCK_II_HPFTP_DP_A].SetValue( 58 );
		Sensor_Press[SSME_BLOCK_II_HPFTP_DP_B].SetValue( 59 );
		Sensor_Press[SSME_BLOCK_II_HPOTPBP_DP_A].SetValue( 60 );
		Sensor_Press[SSME_BLOCK_II_HPOTPBP_DP_B].SetValue( 61 );
		temp = PCA->UseFuelSystemPurge( 3 );
		Sensor_Press[SSME_BLOCK_II_FS_PP_A].SetValue( temp );
		Sensor_Press[SSME_BLOCK_II_FS_PP_B].SetValue( temp );
		Sensor_Press[SSME_BLOCK_II_MCC_P_A1].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_MCC_P_B1].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_MCC_P_A2].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_MCC_P_B2].SetValue( 0 );
		temp = PCA->UseHPOTPISPurge( IMSLHeUsage );
		Sensor_Press[SSME_BLOCK_II_HPOTP_IS_A].SetValue( temp );
		Sensor_Press[SSME_BLOCK_II_HPOTP_IS_B].SetValue( temp );
		temp = PCA->GetPressEmergencyShutdown();
		Sensor_Press[SSME_BLOCK_II_PNEU_SD_P_A].SetValue( temp );
		Sensor_Press[SSME_BLOCK_II_PNEU_SD_P_B].SetValue( temp );

		// temp
		Sensor_Temp[SSME_BLOCK_II_HPFT_DT_A2].SetValue( 512 );
		Sensor_Temp[SSME_BLOCK_II_HPFT_DT_A3].SetValue( 510 );
		Sensor_Temp[SSME_BLOCK_II_HPFT_DT_B2].SetValue( 511 );
		Sensor_Temp[SSME_BLOCK_II_HPFT_DT_B3].SetValue( 509 );
		Sensor_Temp[SSME_BLOCK_II_HPOT_DT_A2].SetValue( 508 );
		Sensor_Temp[SSME_BLOCK_II_HPOT_DT_A3].SetValue( 506 );
		Sensor_Temp[SSME_BLOCK_II_HPOT_DT_B2].SetValue( 507 );
		Sensor_Temp[SSME_BLOCK_II_HPOT_DT_B3].SetValue( 505 );
		Sensor_Temp[SSME_BLOCK_II_PBP_DT_A].SetValue( 504 );
		Sensor_Temp[SSME_BLOCK_II_PBP_DT_B].SetValue( 503 );
		Sensor_Temp[SSME_BLOCK_II_LPFP_DT_A].SetValue( 502 );
		Sensor_Temp[SSME_BLOCK_II_LPFP_DT_B].SetValue( 501 );
		Sensor_Temp[SSME_BLOCK_II_MOV_HT_A].SetValue( 500 );
		Sensor_Temp[SSME_BLOCK_II_MOV_HT_B].SetValue( 499 );
		Sensor_Temp[SSME_BLOCK_II_MFV_HT_A].SetValue( 498 );
		Sensor_Temp[SSME_BLOCK_II_MFV_HT_B].SetValue( 497 );

		// flow
		Sensor_Flow[SSME_BLOCK_II_FF_A1].SetValue( 1 );
		Sensor_Flow[SSME_BLOCK_II_FF_A2].SetValue( 2 );
		Sensor_Flow[SSME_BLOCK_II_FF_B1].SetValue( 3 );
		Sensor_Flow[SSME_BLOCK_II_FF_B2].SetValue( 4 );

		// speed
		Sensor_Speed[SSME_BLOCK_II_LPFTP_SS_A].SetValue( 5 );
		Sensor_Speed[SSME_BLOCK_II_LPFTP_SS_B].SetValue( 6 );
		Sensor_Speed[SSME_BLOCK_II_HPFTP_SS_A].SetValue( 7 );
		Sensor_Speed[SSME_BLOCK_II_HPFTP_SS_B].SetValue( 8 );

		STS()->SetSSMEThrustLevel( ID, 0 );// no thrust allowed
		return;
	}

	void SSME_BLOCK_II::RUN2( double time, double dt )// ignition
	{
		// can go to RUN3 (NOM) or RUN4 (SD, if MOV and/or MFV starts closing)
		// TODO check vlv pos, and improve SD stuff...
		double temp = 0;
		double pc = dcPC_ESC( time - modeltime );
		STS()->SetSSMEThrustLevel( ID, pc );

		// set sensor readings
		// press
		temp = PCA->GetPressFuelPreburnerPurge();
		Sensor_Press[SSME_BLOCK_II_FPB_PP].SetValue( temp );
		temp = PCA->GetPressOxidizerPreburnerPurge();
		Sensor_Press[SSME_BLOCK_II_OPB_PP].SetValue( temp );
		Sensor_Press[SSME_BLOCK_II_LPOT_DP_A].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_LPOT_DP_B].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_LPFT_DP_A].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_LPFT_DP_B].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_HPOTP_DP_A].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_HPOTP_DP_B].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_HPFTP_DP_A].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_HPFTP_DP_B].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_HPOTPBP_DP_A].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_HPOTPBP_DP_B].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_FS_PP_A].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_FS_PP_B].SetValue( 0 );
		temp = /*PCfromPCTtoPSI( pc );*/PCfromPCTtoPSI( STS()->GetSSMEThrustLevel( ID ) );// HACK
		Sensor_Press[SSME_BLOCK_II_MCC_P_A1].SetValue( temp );
		Sensor_Press[SSME_BLOCK_II_MCC_P_A2].SetValue( temp );
		Sensor_Press[SSME_BLOCK_II_MCC_P_B1].SetValue( temp );
		Sensor_Press[SSME_BLOCK_II_MCC_P_B2].SetValue( temp );
		temp = PCA->UseHPOTPISPurge( IMSLHeUsage );
		Sensor_Press[SSME_BLOCK_II_HPOTP_IS_A].SetValue( temp );
		Sensor_Press[SSME_BLOCK_II_HPOTP_IS_B].SetValue( temp );
		temp = PCA->GetPressEmergencyShutdown();
		Sensor_Press[SSME_BLOCK_II_PNEU_SD_P_A].SetValue( temp );
		Sensor_Press[SSME_BLOCK_II_PNEU_SD_P_B].SetValue( temp );

		// temp
		Sensor_Temp[SSME_BLOCK_II_HPFT_DT_A2].SetValue( 1000 );
		Sensor_Temp[SSME_BLOCK_II_HPFT_DT_A3].SetValue( 1000 );
		Sensor_Temp[SSME_BLOCK_II_HPFT_DT_B2].SetValue( 1000 );
		Sensor_Temp[SSME_BLOCK_II_HPFT_DT_B3].SetValue( 1000 );
		Sensor_Temp[SSME_BLOCK_II_HPOT_DT_A2].SetValue( 1000 );
		Sensor_Temp[SSME_BLOCK_II_HPOT_DT_A3].SetValue( 1000 );
		Sensor_Temp[SSME_BLOCK_II_HPOT_DT_B2].SetValue( 1000 );
		Sensor_Temp[SSME_BLOCK_II_HPOT_DT_B3].SetValue( 1000 );
		Sensor_Temp[SSME_BLOCK_II_PBP_DT_A].SetValue( 504 );
		Sensor_Temp[SSME_BLOCK_II_PBP_DT_B].SetValue( 503 );
		Sensor_Temp[SSME_BLOCK_II_LPFP_DT_A].SetValue( 502 );
		Sensor_Temp[SSME_BLOCK_II_LPFP_DT_B].SetValue( 501 );
		Sensor_Temp[SSME_BLOCK_II_MOV_HT_A].SetValue( 500 );
		Sensor_Temp[SSME_BLOCK_II_MOV_HT_B].SetValue( 499 );
		Sensor_Temp[SSME_BLOCK_II_MFV_HT_A].SetValue( 498 );
		Sensor_Temp[SSME_BLOCK_II_MFV_HT_B].SetValue( 497 );

		// flow
		Sensor_Flow[SSME_BLOCK_II_FF_A1].SetValue( 1 );
		Sensor_Flow[SSME_BLOCK_II_FF_A2].SetValue( 2 );
		Sensor_Flow[SSME_BLOCK_II_FF_B1].SetValue( 3 );
		Sensor_Flow[SSME_BLOCK_II_FF_B2].SetValue( 4 );

		// speed
		Sensor_Speed[SSME_BLOCK_II_LPFTP_SS_A].SetValue( 5 );
		Sensor_Speed[SSME_BLOCK_II_LPFTP_SS_B].SetValue( 6 );
		Sensor_Speed[SSME_BLOCK_II_HPFTP_SS_A].SetValue( 7 );
		Sensor_Speed[SSME_BLOCK_II_HPFTP_SS_B].SetValue( 8 );

		// HACK pressurant flow (GOX: 0.8618255kg/s GH2: 0.3311224kg/s @ 104.5%) using VERY simple power level correction
		pMPS->PressurantFlow( ID, 0.8247134 * dt * (pc / 100) * ptrAFV->GetPos(), 0.3168635 * dt * (pc / 100) );

		if (pc > 5) STS()->SetSSMEGH2burn( ID, false );

		// is the controller commanding shutdown?
		if ((ptrMFV->GetPos() < posMFV) || (ptrMOV->GetPos() < posMOV))// MFV/MOV closing?
		{
			// goto shutdown
			modeltime = time - AdjCOTime( STS()->GetSSMEThrustLevel( ID ) );
			modelmode = 4;

			STS()->SetSSMEGH2burn( ID, true );
			return;
		}
		// if not save pos for next time
		posMOV = ptrMOV->GetPos();
		posMFV = ptrMFV->GetPos();

		// are we done here?
		if ((time - modeltime) >= 5)// it's on -> RUN3
		{
			modeltime = time;
			modelmode = 3;
		}
		return;
	}

	void SSME_BLOCK_II::RUN3( double time, double dt )// mainstage
	{
		// MOV moves -> RUN4
		double temp = 0;
		// is the controller commanding shutdown?
		if (ptrMOV->GetPos() < 1)// MOV closing?
		{
			modeltime = time - AdjCOTime( STS()->GetSSMEThrustLevel( ID ) );
			modelmode = 4;

			STS()->SetSSMEGH2burn( ID, true );

			RUN4( time, dt );// go to shutdown
			return;
		}

		// set pc from OPOV pos
		double pc = 125 * (0.3679 + (0.126491 * sqrt( (ptrOPOV->GetPos() * 100) - 52.5646 )));
		STS()->SetSSMEThrustLevel( ID, pc );

		// set sensor readings
		// press
		temp = PCA->GetPressFuelPreburnerPurge();
		Sensor_Press[SSME_BLOCK_II_FPB_PP].SetValue( temp );
		temp = PCA->GetPressOxidizerPreburnerPurge();
		Sensor_Press[SSME_BLOCK_II_OPB_PP].SetValue( temp );
		Sensor_Press[SSME_BLOCK_II_LPOT_DP_A].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_LPOT_DP_B].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_LPFT_DP_A].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_LPFT_DP_B].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_HPOTP_DP_A].SetValue( 3804 );// Block IIA
		Sensor_Press[SSME_BLOCK_II_HPOTP_DP_B].SetValue( 3804 );// Block IIA
		Sensor_Press[SSME_BLOCK_II_HPFTP_DP_A].SetValue( 5666 );// Block IIA
		Sensor_Press[SSME_BLOCK_II_HPFTP_DP_B].SetValue( 5666 );// Block IIA
		Sensor_Press[SSME_BLOCK_II_HPOTPBP_DP_A].SetValue( 6910 );// Block IIA
		Sensor_Press[SSME_BLOCK_II_HPOTPBP_DP_B].SetValue( 6910 );// Block IIA
		Sensor_Press[SSME_BLOCK_II_FS_PP_A].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_FS_PP_B].SetValue( 0 );
		temp = /*PCfromPCTtoPSI( pc );*/PCfromPCTtoPSI( STS()->GetSSMEThrustLevel( ID ) );// HACK
		Sensor_Press[SSME_BLOCK_II_MCC_P_A1].SetValue( temp );
		Sensor_Press[SSME_BLOCK_II_MCC_P_A2].SetValue( temp );
		Sensor_Press[SSME_BLOCK_II_MCC_P_B1].SetValue( temp );
		Sensor_Press[SSME_BLOCK_II_MCC_P_B2].SetValue( temp );
		temp = PCA->UseHPOTPISPurge( IMSLHeUsage );
		Sensor_Press[SSME_BLOCK_II_HPOTP_IS_A].SetValue( temp );
		Sensor_Press[SSME_BLOCK_II_HPOTP_IS_B].SetValue( temp );
		temp = PCA->GetPressEmergencyShutdown();
		Sensor_Press[SSME_BLOCK_II_PNEU_SD_P_A].SetValue( temp );
		Sensor_Press[SSME_BLOCK_II_PNEU_SD_P_B].SetValue( temp );

		// temp
		Sensor_Temp[SSME_BLOCK_II_HPFT_DT_A2].SetValue( 1597 );// Block IIA
		Sensor_Temp[SSME_BLOCK_II_HPFT_DT_A3].SetValue( 1597 );// Block IIA
		Sensor_Temp[SSME_BLOCK_II_HPFT_DT_B2].SetValue( 1604 );// Block IIA
		Sensor_Temp[SSME_BLOCK_II_HPFT_DT_B3].SetValue( 1604 );// Block IIA
		Sensor_Temp[SSME_BLOCK_II_HPOT_DT_A2].SetValue( 1214 );// Block IIA
		Sensor_Temp[SSME_BLOCK_II_HPOT_DT_A3].SetValue( 1214 );// Block IIA
		Sensor_Temp[SSME_BLOCK_II_HPOT_DT_B2].SetValue( 1228 );// Block IIA
		Sensor_Temp[SSME_BLOCK_II_HPOT_DT_B3].SetValue( 1228 );// Block IIA
		Sensor_Temp[SSME_BLOCK_II_PBP_DT_A].SetValue( 504 );
		Sensor_Temp[SSME_BLOCK_II_PBP_DT_B].SetValue( 503 );
		Sensor_Temp[SSME_BLOCK_II_LPFP_DT_A].SetValue( 502 );
		Sensor_Temp[SSME_BLOCK_II_LPFP_DT_B].SetValue( 501 );
		Sensor_Temp[SSME_BLOCK_II_MOV_HT_A].SetValue( 500 );
		Sensor_Temp[SSME_BLOCK_II_MOV_HT_B].SetValue( 499 );
		Sensor_Temp[SSME_BLOCK_II_MFV_HT_A].SetValue( 498 );
		Sensor_Temp[SSME_BLOCK_II_MFV_HT_B].SetValue( 497 );

		// flow
		Sensor_Flow[SSME_BLOCK_II_FF_A1].SetValue( 0 );
		Sensor_Flow[SSME_BLOCK_II_FF_A2].SetValue( 0 );
		Sensor_Flow[SSME_BLOCK_II_FF_B1].SetValue( 0 );
		Sensor_Flow[SSME_BLOCK_II_FF_B2].SetValue( 0 );

		// speed
		Sensor_Speed[SSME_BLOCK_II_LPFTP_SS_A].SetValue( 15680 );// Block IIA
		Sensor_Speed[SSME_BLOCK_II_LPFTP_SS_B].SetValue( 15680 );// Block IIA
		Sensor_Speed[SSME_BLOCK_II_HPFTP_SS_A].SetValue( 34293 );// Block IIA
		Sensor_Speed[SSME_BLOCK_II_HPFTP_SS_B].SetValue( 34293 );// Block IIA

		// HACK pressurant flow (GOX: 0.8618255kg/s GH2: 0.3311224kg/s @ 104.5%) using VERY simple power level correction
		pMPS->PressurantFlow( ID, 0.8247134 * dt * (pc / 100) * ptrAFV->GetPos(), 0.3168635 * dt * (pc / 100) );
		return;
	}

	void SSME_BLOCK_II::RUN4( double time, double dt )// shutdown
	{
		// MFV ?or? CCV = 0 -> RUN 5
		double temp = 0;
		double pc = dcPC_CO( time - modeltime );
		STS()->SetSSMEThrustLevel( ID, pc );

		// set sensor readings
		// press
		temp = PCA->GetPressFuelPreburnerPurge();
		Sensor_Press[SSME_BLOCK_II_FPB_PP].SetValue( temp );
		temp = PCA->GetPressOxidizerPreburnerPurge();
		Sensor_Press[SSME_BLOCK_II_OPB_PP].SetValue( temp );
		Sensor_Press[SSME_BLOCK_II_LPOT_DP_A].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_LPOT_DP_B].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_LPFT_DP_A].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_LPFT_DP_B].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_HPOTP_DP_A].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_HPOTP_DP_B].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_HPFTP_DP_A].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_HPFTP_DP_B].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_HPOTPBP_DP_A].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_HPOTPBP_DP_B].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_FS_PP_A].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_FS_PP_B].SetValue( 0 );
		temp = /*PCfromPCTtoPSI( pc );*/PCfromPCTtoPSI( STS()->GetSSMEThrustLevel( ID ) );// HACK
		Sensor_Press[SSME_BLOCK_II_MCC_P_A1].SetValue( temp );
		Sensor_Press[SSME_BLOCK_II_MCC_P_A2].SetValue( temp );
		Sensor_Press[SSME_BLOCK_II_MCC_P_B1].SetValue( temp );
		Sensor_Press[SSME_BLOCK_II_MCC_P_B2].SetValue( temp );
		temp = PCA->UseHPOTPISPurge( IMSLHeUsage );
		Sensor_Press[SSME_BLOCK_II_HPOTP_IS_A].SetValue( temp );
		Sensor_Press[SSME_BLOCK_II_HPOTP_IS_B].SetValue( temp );
		temp = PCA->GetPressEmergencyShutdown();
		Sensor_Press[SSME_BLOCK_II_PNEU_SD_P_A].SetValue( temp );
		Sensor_Press[SSME_BLOCK_II_PNEU_SD_P_B].SetValue( temp );

		// temp
		Sensor_Temp[SSME_BLOCK_II_HPFT_DT_A2].SetValue( 512 );
		Sensor_Temp[SSME_BLOCK_II_HPFT_DT_A3].SetValue( 510 );
		Sensor_Temp[SSME_BLOCK_II_HPFT_DT_B2].SetValue( 511 );
		Sensor_Temp[SSME_BLOCK_II_HPFT_DT_B3].SetValue( 509 );
		Sensor_Temp[SSME_BLOCK_II_HPOT_DT_A2].SetValue( 508 );
		Sensor_Temp[SSME_BLOCK_II_HPOT_DT_A3].SetValue( 506 );
		Sensor_Temp[SSME_BLOCK_II_HPOT_DT_B2].SetValue( 507 );
		Sensor_Temp[SSME_BLOCK_II_HPOT_DT_B3].SetValue( 505 );
		Sensor_Temp[SSME_BLOCK_II_PBP_DT_A].SetValue( 504 );
		Sensor_Temp[SSME_BLOCK_II_PBP_DT_B].SetValue( 503 );
		Sensor_Temp[SSME_BLOCK_II_LPFP_DT_A].SetValue( 502 );
		Sensor_Temp[SSME_BLOCK_II_LPFP_DT_B].SetValue( 501 );
		Sensor_Temp[SSME_BLOCK_II_MOV_HT_A].SetValue( 500 );
		Sensor_Temp[SSME_BLOCK_II_MOV_HT_B].SetValue( 499 );
		Sensor_Temp[SSME_BLOCK_II_MFV_HT_A].SetValue( 498 );
		Sensor_Temp[SSME_BLOCK_II_MFV_HT_B].SetValue( 497 );

		// flow
		Sensor_Flow[SSME_BLOCK_II_FF_A1].SetValue( 0 );
		Sensor_Flow[SSME_BLOCK_II_FF_A2].SetValue( 0 );
		Sensor_Flow[SSME_BLOCK_II_FF_B1].SetValue( 0 );
		Sensor_Flow[SSME_BLOCK_II_FF_B2].SetValue( 0 );

		// speed
		Sensor_Speed[SSME_BLOCK_II_LPFTP_SS_A].SetValue( 0 );
		Sensor_Speed[SSME_BLOCK_II_LPFTP_SS_B].SetValue( 0 );
		Sensor_Speed[SSME_BLOCK_II_HPFTP_SS_A].SetValue( 0 );
		Sensor_Speed[SSME_BLOCK_II_HPFTP_SS_B].SetValue( 0 );

		// HACK pressurant flow (GOX: 0.8618255kg/s GH2: 0.3311224kg/s @ 104.5%) using VERY simple power level correction
		pMPS->PressurantFlow( ID, 0.8247134 * dt * (pc / 100) * ptrAFV->GetPos(), 0.3168635 * dt * (pc / 100) );

		if (pc < 3) STS()->SetSSMEGH2burn( ID, false );

		// are we done here?
		if ((time - modeltime) >= 6)// it's off -> RUN5
		{
			modeltime = time;
			modelmode = 5;
		}
		return;
	}

	void SSME_BLOCK_II::RUN5( double time, double dt )// post-shutdown
	{
		double temp = 0;

		STS()->SetSSMEThrustLevel( ID, 0 );// no thrust allowed

		// set sensor readings
		// press
		temp = PCA->GetPressFuelPreburnerPurge();
		Sensor_Press[SSME_BLOCK_II_FPB_PP].SetValue( temp );
		temp = PCA->GetPressOxidizerPreburnerPurge();
		Sensor_Press[SSME_BLOCK_II_OPB_PP].SetValue( temp );
		Sensor_Press[SSME_BLOCK_II_LPOT_DP_A].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_LPOT_DP_B].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_LPFT_DP_A].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_LPFT_DP_B].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_HPOTP_DP_A].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_HPOTP_DP_B].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_HPFTP_DP_A].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_HPFTP_DP_B].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_HPOTPBP_DP_A].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_HPOTPBP_DP_B].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_FS_PP_A].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_FS_PP_B].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_MCC_P_A1].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_MCC_P_A2].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_MCC_P_B1].SetValue( 0 );
		Sensor_Press[SSME_BLOCK_II_MCC_P_B2].SetValue( 0 );
		temp = PCA->UseHPOTPISPurge( IMSLHeUsage );
		Sensor_Press[SSME_BLOCK_II_HPOTP_IS_A].SetValue( temp );
		Sensor_Press[SSME_BLOCK_II_HPOTP_IS_B].SetValue( temp );
		temp = PCA->GetPressEmergencyShutdown();
		Sensor_Press[SSME_BLOCK_II_PNEU_SD_P_A].SetValue( temp );
		Sensor_Press[SSME_BLOCK_II_PNEU_SD_P_B].SetValue( temp );

		// temp
		Sensor_Temp[SSME_BLOCK_II_HPFT_DT_A2].SetValue( 512 );
		Sensor_Temp[SSME_BLOCK_II_HPFT_DT_A3].SetValue( 510 );
		Sensor_Temp[SSME_BLOCK_II_HPFT_DT_B2].SetValue( 511 );
		Sensor_Temp[SSME_BLOCK_II_HPFT_DT_B3].SetValue( 509 );
		Sensor_Temp[SSME_BLOCK_II_HPOT_DT_A2].SetValue( 508 );
		Sensor_Temp[SSME_BLOCK_II_HPOT_DT_A3].SetValue( 506 );
		Sensor_Temp[SSME_BLOCK_II_HPOT_DT_B2].SetValue( 507 );
		Sensor_Temp[SSME_BLOCK_II_HPOT_DT_B3].SetValue( 505 );
		Sensor_Temp[SSME_BLOCK_II_PBP_DT_A].SetValue( 504 );
		Sensor_Temp[SSME_BLOCK_II_PBP_DT_B].SetValue( 503 );
		Sensor_Temp[SSME_BLOCK_II_LPFP_DT_A].SetValue( 502 );
		Sensor_Temp[SSME_BLOCK_II_LPFP_DT_B].SetValue( 501 );
		Sensor_Temp[SSME_BLOCK_II_MOV_HT_A].SetValue( 500 );
		Sensor_Temp[SSME_BLOCK_II_MOV_HT_B].SetValue( 499 );
		Sensor_Temp[SSME_BLOCK_II_MFV_HT_A].SetValue( 498 );
		Sensor_Temp[SSME_BLOCK_II_MFV_HT_B].SetValue( 497 );

		// flow
		Sensor_Flow[SSME_BLOCK_II_FF_A1].SetValue( 0 );
		Sensor_Flow[SSME_BLOCK_II_FF_A2].SetValue( 0 );
		Sensor_Flow[SSME_BLOCK_II_FF_B1].SetValue( 0 );
		Sensor_Flow[SSME_BLOCK_II_FF_B2].SetValue( 0 );

		// speed
		Sensor_Speed[SSME_BLOCK_II_LPFTP_SS_A].SetValue( 0 );
		Sensor_Speed[SSME_BLOCK_II_LPFTP_SS_B].SetValue( 0 );
		Sensor_Speed[SSME_BLOCK_II_HPFTP_SS_A].SetValue( 0 );
		Sensor_Speed[SSME_BLOCK_II_HPFTP_SS_B].SetValue( 0 );

		STS()->SetMPSDumpLevel( ID - 1, ptrMOV->GetPos() *  pMPS->GetLOXPVPos( ID ) * min( (pMPS->GetLOXManifPress() / 80) * (pMPS->GetLOXManifPress() / 80), 1 ) );
		return;
	}
}
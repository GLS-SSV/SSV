/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/04/07   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/05/29   GLS
2020/06/20   GLS
2021/06/06   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "SSME.h"
#include "../Atlantis.h"
#include "SSMEController_BLOCK_II.h"
#include "PneumaticControlAssembly.h"
#include "HeliumSystem.h"
#include "SolenoidValve.h"
#include "PressureActuatedValve.h"
#include "HydraulicActuatedValve.h"
#include <discsignals.h>
#include "MPS.h"
#include "MPSdefs.h"
#include <Orbitersdk.h>


namespace mps
{
	SSME::SSME( AtlantisSubsystemDirector* _director, const string& _ident, unsigned short nID, const string& _mesh, int controllertype, const string& sw, HeSysEng* HeSys ):AtlantisSubsystem( _director, _ident )
	{
#ifdef _MPSDEBUG
		oapiWriteLogV( " SSME::SSME in || name:%s|ID:%d|controllertype:%d|sw:%s", _ident.c_str(), nID, controllertype, sw.c_str() );
#endif// _MPSDEBUG

		ID = nID;

		PCA = new PneumaticControlAssembly( this, HeSys );

		// make valves
		ptrOPOV = new HydraulicActuatedValve( 0, MAX_RATE_OPOV, 30, PCA->EmergencyShutdown_PAV, 0.57 );// HACK no clue about correct sequence valve value
		ptrMOV = new HydraulicActuatedValve( 0, MAX_RATE_MOV, 40, ptrOPOV );
		ptrFPOV = new HydraulicActuatedValve( 0, MAX_RATE_FPOV, 30, ptrOPOV, 0.4 );// HACK no clue about correct sequence valve value
		ptrMFV = new HydraulicActuatedValve( 0, MAX_RATE_MFV, 25, ptrFPOV );
		ptrCCV = new HydraulicActuatedValve( 0, MAX_RATE_CCV, 23, ptrFPOV, 0.05 );// HACK no clue about correct sequence valve value
		PCA->PurgeSequenceValve_PAV->SetPressureSources( nullptr, ptrCCV, nullptr, nullptr );

		ptrAFV = new SolenoidValve( 0, RATE_AFV, true, nullptr, nullptr );
		ptrHPV_SV = new SolenoidValve( 0, RATE_HPV_SV, true, HeSys, PCA->PurgeSequenceValve_PAV );
		ptrOBV = new PressureActuatedValve( 1, RATE_OBV, PCA->OxidizerBleedValve_PAV, nullptr, nullptr, nullptr );
		ptrFBV = new PressureActuatedValve( 1, RATE_FBV, PCA->BleedValvesControl_SV, nullptr, nullptr, nullptr );
		ptrHPV = new PressureActuatedValve( 0, RATE_HPV, ptrHPV_SV, nullptr, HeSys, nullptr );
		ptrGCV = new PressureActuatedValve( 1, RATE_GCV, nullptr, ptrHPV_SV, nullptr, nullptr );
		ptrRIV = new PressureActuatedValve( 0, RATE_RIV, nullptr, PCA->OxidizerBleedValve_PAV, nullptr, nullptr );

		// hardware model stuff
		modelmode = 1;
		modeltime = 0;

		// igniters
		Igniter_MCC[0] = false;
		Igniter_MCC[1] = false;
		Igniter_FPB[0] = false;
		Igniter_FPB[1] = false;
		Igniter_OPB[0] = false;
		Igniter_OPB[1] = false;

		// make controller
		/*if (controllertype == 1)// TODO improve/add error checking
		{
			Controller = new SSMEController_BLOCK_I( this, sw );
		}
		else
		{*/
			Controller = new SSMEController_BLOCK_II( this, sw );
		//}

		// load mesh
		MESHHANDLE mesh = oapiLoadMeshGlobal( _mesh.c_str() );
		STS()->SetSSMEMesh( ID - 1, mesh );

#ifdef _MPSDEBUG
		oapiWriteLog( " SSME::SSME out" );
#endif// _MPSDEBUG
		return;
	}

	SSME::~SSME( void )
	{
		delete ptrCCV;
		delete ptrMOV;
		delete ptrMFV;
		delete ptrFPOV;
		delete ptrOPOV;
		delete ptrAFV;
		delete ptrHPV_SV;
		delete ptrOBV;
		delete ptrFBV;
		delete ptrHPV;
		delete ptrGCV;
		delete ptrRIV;

		delete Controller;

		delete PCA;
		return;
	}

	void SSME::Realize()
	{
		pMPS = dynamic_cast<MPS*>(director->GetSubsystemByName( "MPS" ));

		STS()->SetSSMEParams( ID, FPL_THRUST, ISP0, ISP1 );

		// connect AC to PSE
		discsignals::DiscreteBundle* bundle_hyd;
		discsignals::DiscreteBundle* bundle_power;
		discsignals::DiscreteBundle* bundle_OEout;// TODO separate chs?
		discsignals::DiscreteBundle* bundle_OEoutCCV;
		discsignals::DiscreteBundle* bundle_OEoutMFV;
		discsignals::DiscreteBundle* bundle_OEoutMOV;
		discsignals::DiscreteBundle* bundle_OEoutFPOV;
		discsignals::DiscreteBundle* bundle_OEoutOPOV;
		discsignals::DiscreteBundle* bundle_IEchA_Press;
		discsignals::DiscreteBundle* bundle_IEchB_Press;
		discsignals::DiscreteBundle* bundle_IEchA_Temp;
		discsignals::DiscreteBundle* bundle_IEchB_Temp;
		discsignals::DiscreteBundle* bundle_IEchA_Flow;
		discsignals::DiscreteBundle* bundle_IEchB_Flow;
		discsignals::DiscreteBundle* bundle_IEchA_Speed;
		discsignals::DiscreteBundle* bundle_IEchB_Speed;

		switch (ID)
		{
			case 1:
				bundle_hyd = BundleManager()->CreateBundle( "R2_To_APU1", 16 );
				bundle_power = BundleManager()->CreateBundle( "SSMEC_R2_SWITCHES", 8 );
				break;
			case 2:
				bundle_hyd = BundleManager()->CreateBundle( "R2_To_APU2", 16 );
				bundle_power = BundleManager()->CreateBundle( "SSMEL_R2_SWITCHES", 8 );
				break;
			case 3:
				bundle_hyd = BundleManager()->CreateBundle( "R2_To_APU3", 16 );
				bundle_power = BundleManager()->CreateBundle( "SSMER_R2_SWITCHES", 8 );
				break;
		}

		char cbuf[32];
		sprintf_s( cbuf, 32, "OE_SSME_%d", ID );
		bundle_OEout = BundleManager()->CreateBundle( cbuf, 14 );

		sprintf_s( cbuf, 32, "OE_SSME_%d_CCV", ID );
		bundle_OEoutCCV = BundleManager()->CreateBundle( cbuf, 6 );

		sprintf_s( cbuf, 32, "OE_SSME_%d_MFV", ID );
		bundle_OEoutMFV = BundleManager()->CreateBundle( cbuf, 6 );

		sprintf_s( cbuf, 32, "OE_SSME_%d_MOV", ID );
		bundle_OEoutMOV = BundleManager()->CreateBundle( cbuf, 6 );

		sprintf_s( cbuf, 32, "OE_SSME_%d_FPOV", ID );
		bundle_OEoutFPOV = BundleManager()->CreateBundle( cbuf, 6 );

		sprintf_s( cbuf, 32, "OE_SSME_%d_OPOV", ID );
		bundle_OEoutOPOV = BundleManager()->CreateBundle( cbuf, 6 );

		sprintf_s( cbuf, 32, "SSME_%d_IEchA_Press", ID );
		bundle_IEchA_Press = BundleManager()->CreateBundle( cbuf, 15 );

		sprintf_s( cbuf, 32, "SSME_%d_IEchB_Press", ID );
		bundle_IEchB_Press = BundleManager()->CreateBundle( cbuf, 15 );

		sprintf_s( cbuf, 32, "SSME_%d_IEchA_Temp", ID );
		bundle_IEchA_Temp = BundleManager()->CreateBundle( cbuf, 8 );

		sprintf_s( cbuf, 32, "SSME_%d_IEchB_Temp", ID );
		bundle_IEchB_Temp = BundleManager()->CreateBundle( cbuf, 8 );

		sprintf_s( cbuf, 32, "SSME_%d_IEchA_Flow", ID );
		bundle_IEchA_Flow = BundleManager()->CreateBundle( cbuf, 4 );

		sprintf_s( cbuf, 32, "SSME_%d_IEchB_Flow", ID );
		bundle_IEchB_Flow = BundleManager()->CreateBundle( cbuf, 4 );

		sprintf_s( cbuf, 32, "SSME_%d_IEchA_Speed", ID );
		bundle_IEchA_Speed = BundleManager()->CreateBundle( cbuf, 3 );

		sprintf_s( cbuf, 32, "SSME_%d_IEchB_Speed", ID );
		bundle_IEchB_Speed = BundleManager()->CreateBundle( cbuf, 3 );

		Controller->Realize( bundle_power, bundle_OEout, bundle_OEoutCCV, bundle_OEoutMFV, bundle_OEoutMOV, bundle_OEoutFPOV, bundle_OEoutOPOV, bundle_IEchA_Press, bundle_IEchB_Press, bundle_IEchA_Temp, bundle_IEchB_Temp, bundle_IEchA_Flow, bundle_IEchB_Flow, bundle_IEchA_Speed, bundle_IEchB_Speed );

		ConnectSensors( bundle_IEchA_Press, bundle_IEchB_Press, bundle_IEchA_Temp, bundle_IEchB_Temp, bundle_IEchA_Flow, bundle_IEchB_Flow, bundle_IEchA_Speed, bundle_IEchB_Speed );

		PCA->Realize( bundle_OEout );

		ptrAFV->Connect( 0, bundle_OEout, 10 );
		ptrAFV->Connect( 1, bundle_OEout, 11 );
		ptrHPV_SV->Connect( 0, bundle_OEout, 12 );
		ptrHPV_SV->Connect( 1, bundle_OEout, 13 );

		ptrCCV->Connect( bundle_OEoutCCV, bundle_hyd );
		ptrMFV->Connect( bundle_OEoutMFV, bundle_hyd );
		ptrMOV->Connect( bundle_OEoutMOV, bundle_hyd );
		ptrFPOV->Connect( bundle_OEoutFPOV, bundle_hyd );
		ptrOPOV->Connect( bundle_OEoutOPOV, bundle_hyd );
		return;
	}

	double SSME::PCfromPCTtoPSI( double pcPCT ) const
	{
		return ((pcPCT * RPL_PC_PRESS) / 100);
	}

	double SSME::PCfromPSItoPCT( double pcPSI ) const
	{
		return ((pcPSI * 100) / RPL_PC_PRESS);
	}

	void SSME::OnPostStep( double simt, double simdt, double mjd )
	{
		// valves first
		ptrCCV->tmestp( simdt );
		ptrMOV->tmestp( simdt );
		ptrMFV->tmestp( simdt );
		ptrFPOV->tmestp( simdt );
		ptrOPOV->tmestp( simdt );
		ptrAFV->tmestp( simdt );
		ptrHPV_SV->tmestp( simdt );
		ptrOBV->tmestp( simdt );
		ptrFBV->tmestp( simdt );
		ptrHPV->tmestp( simdt );
		ptrGCV->tmestp( simdt );
		ptrRIV->tmestp( simdt );

		// engine model
		SSMERUN( simt, simdt );

		// run controller
		Controller->tmestp( simt, simdt );

		// run PCA
		PCA->tmestp( simdt );

		ptrHPV->Use( 30.0, 0 );// HACK no clue what value should be, probably much less than this
		return;
	}

	void SSME::OnSaveState( FILEHANDLE scn ) const
	{
		char cbuf[16];
		int config = modelmode;

		if ((modelmode == 1) && (ptrCCV->GetPos() > 0)) config = 2;

		sprintf_s( cbuf, 16, "SSME config" );
		oapiWriteScenario_int( scn, cbuf, config );

		Controller->__OnSaveState( scn );// write controller
		return;
	}

	bool SSME::OnParseLine( const char* line )
	{
		int read_i = 0;

		if (!_strnicmp( line, "SSME config", 11 ))
		{
			sscanf_s( line + 11, "%d", &read_i );

			switch (read_i)
			{
				case 1:// pre-launch psn-3
					ptrCCV->_backdoor( 0 );
					ptrMFV->_backdoor( 0 );
					ptrMOV->_backdoor( 0 );
					ptrFPOV->_backdoor( 0 );
					ptrOPOV->_backdoor( 0 );
					ptrFBV->_backdoor( 1 );
					ptrOBV->_backdoor( 1 );
					ptrAFV->_backdoor( 0 );
					ptrHPV->_backdoor( 0 );
					ptrGCV->_backdoor( 1 );
					ptrRIV->_backdoor( 0 );
					PCA->PurgeSequenceValve_PAV->_backdoor( 0 );
					PCA->EmergencyShutdown_PAV->_backdoor( 1 );
					PCA->EmergencyShutdown_SV->_backdoor( 1 );
					PCA->FuelSystemPurge_SV->_backdoor( 1 );
					PCA->FuelSystemPurge_PAV->_backdoor( 1 );
					PCA->HPOTPISPurge_SV->_backdoor( 0 );
					PCA->HPOTPISPurge_PAV->_backdoor( 0 );

					modelmode = 1;
					break;
				case 2:// pre-launch post psn-4
					ptrCCV->_backdoor( 1 );
					ptrMFV->_backdoor( 0 );
					ptrMOV->_backdoor( 0 );
					ptrFPOV->_backdoor( 0 );
					ptrOPOV->_backdoor( 0 );
					ptrFBV->_backdoor( 1 );
					ptrOBV->_backdoor( 1 );
					ptrAFV->_backdoor( 0 );
					ptrHPV->_backdoor( 0 );
					ptrGCV->_backdoor( 1 );
					ptrRIV->_backdoor( 0 );
					PCA->FuelSystemPurge_SV->_backdoor( 1 );
					PCA->FuelSystemPurge_PAV->_backdoor( 1 );

					modelmode = 1;
					break;
				default:// post-shutdown
					ptrCCV->_backdoor( 0 );
					ptrMFV->_backdoor( 0 );
					ptrMOV->_backdoor( 0 );
					ptrFPOV->_backdoor( 0 );
					ptrOPOV->_backdoor( 0 );
					ptrFBV->_backdoor( 0 );
					ptrOBV->_backdoor( 0 );
					ptrAFV->_backdoor( 0 );
					ptrHPV->_backdoor( 0 );
					ptrGCV->_backdoor( 1 );
					ptrRIV->_backdoor( 1 );
					PCA->PurgeSequenceValve_PAV->_backdoor( 0 );

					modelmode = 5;
					break;
			}
#ifdef _MPSDEBUG
			oapiWriteLogV( " SSME::OnParseLine || SSME_config:%d", read_i );
#endif// _MPSDEBUG
			return true;
		}

		return Controller->__OnParseLine( line );// check if controller wants line
	}


	void SSME::SSMERUN( double time, double dt )
	{
		switch (modelmode)
		{
			case 1:// pre-start
				RUN1( time, dt );
				break;
			case 2:// ignition
				RUN2( time, dt );
				break;
			case 3:// mainstage
				RUN3( time, dt );
				break;
			case 4:// cutoff
				RUN4( time, dt );
				break;
			case 5:// post-shutdown
				RUN5( time, dt );
				break;
		}
		return;
	}

	// data cookup
	// ESC
	double SSME::dcPC_ESC( double tme )
	{
		double pc;

		if (tme <= 0.1)
		{
			pc = 0;
		}
		else if (tme <= 0.95)
		{
			pc = 0.1;
		}
		else if (tme <= 1.5)
		{
			pc = abs( (5.09 * tme) - 4.84 );// abs here due to double precision prob
		}
		else if (tme <= 1.62)
		{
			pc = (96.67 * tme) - 142.2;
		}
		else if (tme <= 2.14)
		{
			pc = (22.5 * tme) - 22.05;
		}
		else if (tme <= 2.46)
		{
			pc = 26.1;
		}
		else if (tme <= 3.8)
		{
			pc = (49.78 * tme) - 96.35;
		}
		else if (tme <= 5)
		{
			pc = (6 * tme) + 70;
		}
		else
		{
			pc = 100;
		}
		return pc;
	}


	// CO
	double SSME::dcPC_CO( double tme )
	{
		double pc;

		if (tme <= 0.5)
		{
			pc = 100 - (122 * tme);
		}
		else
		{
			if (tme <= 1.8)
			{
				pc = 50.92 - (23.85 * tme);
			}
			else
			{
				if (tme <= 6)
				{
					pc = 11.43 - (1.9 * tme);
				}
				else
				{
					pc = 0;
				}
			}
		}
		return pc;
	}

	double SSME::AdjCOTime( double pc )
	{
		// pc > 100% -> < 0
		// pc = 100% -> = 0
		// pc < 100% -> > 0
		if (pc >= 39)
		{
			return (100 - pc) / 122;
		}
		else
		{
			if (pc >= 8)
			{
				return ((50.92 - pc) * 2.6) / 62;
			}
			else
			{
				return ((11.43 - pc) * 4.2) / 8;
			}
		}
	}
}
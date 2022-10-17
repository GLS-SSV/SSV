/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "OutputElectronics.h"
#include "SSMEController.h"
#include "PowerSupplyElectronics.h"
#include "SSME.h"
#include <HydraulicActuatedValve.h>
#include "MPSdefs.h"


namespace mps
{
	OutputElectronics::OutputElectronics( int ch, SSME* eng, SSMEController* Controller )
	{
#ifdef _MPSDEBUG
		oapiWriteLogV( " OutputElectronics::OutputElectronics in || ch:%d", ch );
#endif// _MPSDEBUG

		this->eng = eng;
		this->ch = ch;
		this->Controller = Controller;
		time = 0;
		StorageRegister = 0;
		ONOFFCommandRegister[0] = 0;
		ONOFFCommandRegister[1] = 0;
		SH[0] = 0;
		SH[1] = 0;
		SH[2] = 0;
		SH[3] = 0;
		SH[4] = 0;
		triplevel[0] = 0.06;// chA
		triplevel[1] = 0.1;// chB

#ifdef _MPSDEBUG
		oapiWriteLog( " OutputElectronics::OutputElectronics out" );
#endif// _MPSDEBUG
		return;
	}

	OutputElectronics::~OutputElectronics( void )
	{
		return;
	}

	void OutputElectronics::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	bool OutputElectronics::OnParseLine( const char* line )
	{
		return false;
	}

	void OutputElectronics::Realize( discsignals::DiscreteBundle* bundle, discsignals::DiscreteBundle* bundleCCV, discsignals::DiscreteBundle* bundleMFV, discsignals::DiscreteBundle* bundleMOV, discsignals::DiscreteBundle* bundleFPOV, discsignals::DiscreteBundle* bundleOPOV )
	{
		PSE = Controller->PSE[ch];
		CIE[chA] = Controller->CIE[chA];
		CIE[chB] = Controller->CIE[chB];

		FuelSystemPurge_SV.Connect( bundle, 0 + ch );
		BleedValvesControl_SV.Connect( bundle, 2 + ch );
		EmergencyShutdown_SV.Connect( bundle, 4 + ch );
		ShutdownPurge_SV.Connect( bundle, 6 + ch );
		HPOTPISPurge_SV.Connect( bundle, 8 + ch );
		AFV_SV.Connect( bundle, 10 + ch );
		HPV_SV.Connect( bundle, 12 + ch );

		HSV_pos[0].Connect( bundleCCV, 0 + ch );
		FO_SS[0].Connect( bundleCCV, 2 + ch );
		FS_SS[0].Connect( bundleCCV, 4 + ch );

		HSV_pos[1].Connect( bundleMFV, 0 + ch );
		FO_SS[1].Connect( bundleMFV, 2 + ch );
		FS_SS[1].Connect( bundleMFV, 4 + ch );

		HSV_pos[2].Connect( bundleMOV, 0 + ch );
		FO_SS[2].Connect( bundleMOV, 2 + ch );
		FS_SS[2].Connect( bundleMOV, 4 + ch );

		HSV_pos[3].Connect( bundleFPOV, 0 + ch );
		FO_SS[3].Connect( bundleFPOV, 2 + ch );
		FS_SS[3].Connect( bundleFPOV, 4 + ch );

		HSV_pos[4].Connect( bundleOPOV, 0 + ch );
		FO_SS[4].Connect( bundleOPOV, 2 + ch );
		FS_SS[4].Connect( bundleOPOV, 4 + ch );

		////////////////////////////////////////////////////////
		// get initial positions so we're all on the same page
		SVmodel_cur[0] = eng->ptrCCV->GetPos();
		SVmodel_tgt[0] = SVmodel_cur[0];
		SVmodel_cur[1] = eng->ptrMFV->GetPos();
		SVmodel_tgt[1] = SVmodel_cur[1];
		SVmodel_cur[2] = eng->ptrMOV->GetPos();
		SVmodel_tgt[2] = SVmodel_cur[2];
		SVmodel_cur[3] = eng->ptrFPOV->GetPos();
		SVmodel_tgt[3] = SVmodel_cur[3];
		SVmodel_cur[4] = eng->ptrOPOV->GetPos();
		SVmodel_tgt[4] = SVmodel_cur[4];
		return;
	}
}

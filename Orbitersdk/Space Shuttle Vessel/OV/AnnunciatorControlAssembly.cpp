/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
2023/11/12   GLS
********************************************/
#include "AnnunciatorControlAssembly.h"
#include "Atlantis.h"
#include <cassert>


AnnunciatorControlAssembly::AnnunciatorControlAssembly( AtlantisSubsystemDirector* _director, const string& _ident, short nID ):AtlantisSubsystem( _director, _ident )
{
	assert( (nID >= 1) && (nID <= 5) && "AnnunciatorControlAssembly::AnnunciatorControlAssembly.nID" );
	ID = nID;
	return;
}

AnnunciatorControlAssembly::~AnnunciatorControlAssembly( void )
{
}

void AnnunciatorControlAssembly::Realize( void )
{
	char bundlename[8];
	int k = 0;

	sprintf_s( bundlename, 8, "ACA%d_1", ID );
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( bundlename, 16 );
	for (int i = 0; i <= 15; i += 2, k++)
	{
		cmd[k].Connect( pBundle, i );
		output[k].Connect( pBundle, i + 1 );
	}

	sprintf_s( bundlename, 8, "ACA%d_2", ID );
	pBundle = BundleManager()->CreateBundle( bundlename, 16 );
	for (int i = 0; i <= 15; i += 2, k++)
	{
		cmd[k].Connect( pBundle, i );
		output[k].Connect( pBundle, i + 1 );
	}

	sprintf_s( bundlename, 8, "ACA%d_3", ID );
	pBundle = BundleManager()->CreateBundle( bundlename, 16 );
	for (int i = 0; i <= 15; i += 2, k++)
	{
		cmd[k].Connect( pBundle, i );
		output[k].Connect( pBundle, i + 1 );
	}

	sprintf_s( bundlename, 8, "ACA%d_4", ID );
	pBundle = BundleManager()->CreateBundle( bundlename, 16 );
	for (int i = 0; i <= 15; i += 2, k++)
	{
		cmd[k].Connect( pBundle, i );
		output[k].Connect( pBundle, i + 1 );
	}

	sprintf_s( bundlename, 8, "ACA%d_5", ID );
	pBundle = BundleManager()->CreateBundle( bundlename, 16 );
	for (int i = 0; i <= 15; i += 2, k++)
	{
		cmd[k].Connect( pBundle, i );
		output[k].Connect( pBundle, i + 1 );
	}

	pBundle = BundleManager()->CreateBundle( "ACA", 16 );
	switch (ID)
	{
		case 1:
			power[0].Connect( pBundle, 0 );
			power[1].Connect( pBundle, 1 );
			odd[0].Connect( pBundle, 6 );
			even[0].Connect( pBundle, 7 );
			odd[1].Connect( pBundle, 8 );
			even[1].Connect( pBundle, 9 );
			break;
		case 2:
		case 3:
			power[0].Connect( pBundle, 2 );
			power[1].Connect( pBundle, 3 );
			odd[0].Connect( pBundle, 6 );
			even[0].Connect( pBundle, 7 );
			odd[1].Connect( pBundle, 8 );
			even[1].Connect( pBundle, 9 );
			break;
		case 4:
		case 5:
			power[0].Connect( pBundle, 4 );
			power[1].Connect( pBundle, 5 );
			odd[0].Connect( pBundle, 10 );
			even[0].Connect( pBundle, 11 );
			break;
	}

	// HACK "overwrite" previous MDM connections and plug cmd ports to MDM bundles
	switch (ID)
	{
		case 1:
			pBundle = BundleManager()->CreateBundle( "MDM_FF1_IOM2_CH1", 16 );
			cmd[3].Connect( pBundle, 15 );// C3 LIGHT: FWD DAP RCS JETS "NORM"

			pBundle = BundleManager()->CreateBundle( "MDM_FF1_IOM2_CH2", 16 );
			cmd[1].Connect( pBundle, 3 );// C3 LIGHT: FWD DAP CONTROL "MAN"
			cmd[5].Connect( pBundle, 5 );// C3 LIGHT: FWD DAP RCS JETS "VERN"

			pBundle = BundleManager()->CreateBundle( "MDM_FF1_IOM10_CH0", 16 );
			cmd[28].Connect( pBundle, 4 );// F2 LIGHT: LH FCS BODY FLAP "AUTO"
			cmd[24].Connect( pBundle, 5 );// F2 LIGHT: LH FCS SPEED BK "AUTO"
			cmd[12].Connect( pBundle, 6 );// F2 LIGHT: LH FCS PITCH "AUTO"
			cmd[18].Connect( pBundle, 7 );// F2 LIGHT: LH FCS ROLL/YAW "AUTO"

			pBundle = BundleManager()->CreateBundle( "MDM_FF1_IOM10_CH1", 16 );
			cmd[9].Connect( pBundle, 1 );// C3 LIGHT: FWD MAN ROT ROLL "DISC RT"
			cmd[17].Connect( pBundle, 2 );// C3 LIGHT: FWD MAN ROT ROLL "ACCEL"
			cmd[25].Connect( pBundle, 3 );// C3 LIGHT: FWD MAN ROT ROLL "PULSE"
			cmd[11].Connect( pBundle, 4 );// C3 LIGHT: FWD MAN ROT PITCH "DISC RT"
			cmd[19].Connect( pBundle, 5 );// C3 LIGHT: FWD MAN ROT PITCH "ACCEL"
			cmd[27].Connect( pBundle, 6 );// C3 LIGHT: FWD MAN ROT PITCH "PULSE"
			cmd[13].Connect( pBundle, 7 );// C3 LIGHT: FWD MAN ROT YAW "DISC RT"
			cmd[21].Connect( pBundle, 8 );// C3 LIGHT: FWD MAN ROT YAW "ACCEL"
			cmd[29].Connect( pBundle, 9 );// C3 LIGHT: FWD MAN ROT YAW "PULSE"

			pBundle = BundleManager()->CreateBundle( "MDM_FF2_IOM2_CH1", 16 );
			cmd[15].Connect( pBundle, 0 );// F7 LIGHT: L MPS AMBER STATUS

			pBundle = BundleManager()->CreateBundle( "MDM_FF2_IOM10_CH0", 16 );
			cmd[10].Connect( pBundle, 4 );// F2 LIGHT: LH FCS BODY FLAP "MAN"
			cmd[26].Connect( pBundle, 5 );// F2 LIGHT: LH FCS SPEED BK "MAN"
			cmd[14].Connect( pBundle, 6 );// F2 LIGHT: LH FCS PITCH "CSS"
			cmd[20].Connect( pBundle, 7 );// F2 LIGHT: LH FCS ROLL/YAW "CSS"

			pBundle = BundleManager()->CreateBundle( "MDM_FF2_IOM10_CH1", 16 );
			cmd[7].Connect( pBundle, 0 );// F7 LIGHT: L MPS RED STATUS
			break;
		case 2:
			pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM2_CH1", 16 );
			cmd[37].Connect( pBundle, 0 );// F7 LIGHT: R MPS AMBER STATUS
			cmd[16].Connect( pBundle, 7 );// F6 LIGHT B: RCS CMD "ROLL LEFT"
			cmd[18].Connect( pBundle, 8 );// F6 LIGHT B: RCS CMD "ROLL RIGHT"
			cmd[24].Connect( pBundle, 9 );// F6 LIGHT B: RCS CMD "YAW LEFT"
			cmd[26].Connect( pBundle, 10 );// F6 LIGHT B: RCS CMD "YAW RIGHT"
			cmd[20].Connect( pBundle, 11 );// F6 LIGHT B: RCS CMD "PITCH UP"
			cmd[22].Connect( pBundle, 12 );// F6 LIGHT B: RCS CMD "PITCH DOWN"

			pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM10_CH0", 16 );
			cmd[29].Connect( pBundle, 4 );// F4 LIGHT: RH FCS BODY FLAP "AUTO"
			cmd[25].Connect( pBundle, 5 );// F4 LIGHT: RH FCS SPEED BK "AUTO"
			cmd[13].Connect( pBundle, 6 );// F4 LIGHT: RH FCS PITCH "AUTO"
			cmd[19].Connect( pBundle, 7 );// F4 LIGHT: RH FCS ROLL/YAW "AUTO"

			pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM10_CH1", 16 );
			cmd[31].Connect( pBundle, 0 );// F7 LIGHT: R MPS RED STATUS

			pBundle = BundleManager()->CreateBundle( "MDM_FF4_IOM10_CH0", 16 );
			cmd[33].Connect( pBundle, 4 );// F4 LIGHT: RH FCS BODY FLAP "MAN"
			cmd[27].Connect( pBundle, 5 );// F4 LIGHT: RH FCS SPEED BK "MAN"
			cmd[15].Connect( pBundle, 6 );// F4 LIGHT: RH FCS PITCH "CSS"
			cmd[21].Connect( pBundle, 7 );// F4 LIGHT: RH FCS ROLL/YAW "CSS"
			break;
		case 3:
			pBundle = BundleManager()->CreateBundle( "MDM_FF1_IOM2_CH1", 16 );
			cmd[15].Connect( pBundle, 0 );// F7 LIGHT: C MPS AMBER STATUS
			cmd[16].Connect( pBundle, 7 );// F6 LIGHT A: RCS CMD "ROLL LEFT"
			cmd[18].Connect( pBundle, 8 );// F6 LIGHT A: RCS CMD "ROLL RIGHT"
			cmd[24].Connect( pBundle, 9 );// F6 LIGHT A: RCS CMD "YAW LEFT"
			cmd[26].Connect( pBundle, 10 );// F6 LIGHT A: RCS CMD "YAW RIGHT"
			cmd[20].Connect( pBundle, 11 );// F6 LIGHT A: RCS CMD "PITCH UP"
			cmd[22].Connect( pBundle, 12 );// F6 LIGHT A: RCS CMD "PITCH DOWN"
			cmd[5].Connect( pBundle, 13 );// C3 LIGHT: FWD DAP CONTROL "AUTO"
			cmd[1].Connect( pBundle, 14 );// C3 LIGHT: FWD DAP SELECT "A"

			pBundle = BundleManager()->CreateBundle( "MDM_FF1_IOM2_CH2", 16 );
			cmd[3].Connect( pBundle, 4 );// C3 LIGHT: FWD DAP SELECT "B"

			pBundle = BundleManager()->CreateBundle( "MDM_FF1_IOM10_CH1", 16 );
			cmd[7].Connect( pBundle, 0 );// F7 LIGHT: C MPS RED STATUS
			cmd[17].Connect( pBundle, 10 );// C3 LIGHT: FWD MAN TRANS X "NORM"
			cmd[25].Connect( pBundle, 11 );// C3 LIGHT: FWD MAN TRANS X "PULSE"
			cmd[9].Connect( pBundle, 12 );// C3 LIGHT: FWD MAN TRANS X "LVLH"
			cmd[19].Connect( pBundle, 13 );// C3 LIGHT: FWD MAN TRANS Y "NORM"
			cmd[27].Connect( pBundle, 14 );// C3 LIGHT: FWD MAN TRANS Y "PULSE"
			cmd[11].Connect( pBundle, 15 );// C3 LIGHT: FWD MAN TRANS Y "LOW Z"

			pBundle = BundleManager()->CreateBundle( "MDM_FF1_IOM10_CH2", 16 );
			cmd[21].Connect( pBundle, 0 );// C3 LIGHT: FWD MAN TRANS Z "NORM"
			cmd[29].Connect( pBundle, 1 );// C3 LIGHT: FWD MAN TRANS Z "PULSE"
			cmd[13].Connect( pBundle, 2 );// C3 LIGHT: FWD MAN TRANS Z "HIGH"
			break;
		case 4:
			pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM2_CH1", 16 );
			cmd[4].Connect( pBundle, 13 );// A6 LIGHT: AFT DAP CONTROL "AUTO"
			cmd[0].Connect( pBundle, 14 );// A6 LIGHT: AFT DAP SELECT "A"

			pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM2_CH2", 16 );
			cmd[2].Connect( pBundle, 4 );// A6 LIGHT: AFT DAP SELECT "B"

			pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM10_CH1", 16 );
			cmd[16].Connect( pBundle, 10 );// A6 LIGHT: AFT MAN TRANS X "NORM"
			cmd[24].Connect( pBundle, 11 );// A6 LIGHT: AFT MAN TRANS X "PULSE"
			cmd[8].Connect( pBundle, 12 );// A6 LIGHT: AFT MAN TRANS X "LVLH"
			cmd[18].Connect( pBundle, 13 );// A6 LIGHT: AFT MAN TRANS Y "NORM"
			cmd[26].Connect( pBundle, 14 );// A6 LIGHT: AFT MAN TRANS Y "PULSE"
			cmd[10].Connect( pBundle, 15 );// A6 LIGHT: AFT MAN TRANS Y "LOW Z"

			pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM10_CH2", 16 );
			cmd[20].Connect( pBundle, 0 );// A6 LIGHT: AFT MAN TRANS Z "NORM"
			cmd[28].Connect( pBundle, 1 );// A6 LIGHT: AFT MAN TRANS Z "PULSE"
			cmd[12].Connect( pBundle, 2 );// A6 LIGHT: AFT MAN TRANS Z "HIGH"
			break;
		case 5:
			pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM2_CH1", 16 );
			cmd[2].Connect( pBundle, 15 );// A6 LIGHT: AFT DAP RCS JETS "NORM"

			pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM2_CH2", 16 );
			cmd[0].Connect( pBundle, 3 );// A6 LIGHT: AFT DAP CONTROL "MAN"
			cmd[4].Connect( pBundle, 5 );// A6 LIGHT: AFT DAP RCS JETS "VERN"

			pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM10_CH1", 16 );
			cmd[8].Connect( pBundle, 1 );// A6 LIGHT: AFT MAN ROT ROLL "DISC RT"
			cmd[16].Connect( pBundle, 2 );// A6 LIGHT: AFT MAN ROT ROLL "ACCEL"
			cmd[24].Connect( pBundle, 3 );// A6 LIGHT: AFT MAN ROT ROLL "PULSE"
			cmd[10].Connect( pBundle, 4 );// A6 LIGHT: AFT MAN ROT PITCH "DISC RT"
			cmd[18].Connect( pBundle, 5 );// A6 LIGHT: AFT MAN ROT PITCH "ACCEL"
			cmd[26].Connect( pBundle, 6 );// A6 LIGHT: AFT MAN ROT PITCH "PULSE"
			cmd[12].Connect( pBundle, 7 );// A6 LIGHT: AFT MAN ROT YAW "DISC RT"
			cmd[20].Connect( pBundle, 8 );// A6 LIGHT: AFT MAN ROT YAW "ACCEL"
			cmd[28].Connect( pBundle, 9 );// A6 LIGHT: AFT MAN ROT YAW "PULSE"
			break;
	}
	return;
}

void AnnunciatorControlAssembly::OnPreStep( double simt, double simdt, double mjd )
{
	if (!power[0].IsSet() && !power[1].IsSet())
	{
		// all lights off
		for (int i = 0; i < 40; i++) output[i].ResetLine();
		return;
	}

	if (odd[0].IsSet() || odd[1].IsSet())
	{
		// odd lights on
		for (int i = 0; i < 40; i += 2) output[i].SetLine();
	}
	else
	{
		// check cmd for odd lights
		for (int i = 0; i < 40; i += 2) output[i].SetLine( (int)cmd[i].IsSet() * 5.0f );
	}

	if (even[0].IsSet() || even[1].IsSet())
	{
		// even lights on
		for (int i = 1; i < 40; i += 2) output[i].SetLine();
	}
	else
	{
		// check cmd for even lights
		for (int i = 1; i < 40; i += 2) output[i].SetLine( (int)cmd[i].IsSet() * 5.0f );
	}
	return;
}

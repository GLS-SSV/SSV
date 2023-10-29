/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/04/07   GLS
2020/05/10   GLS
2020/06/20   GLS
2020/08/24   GLS
2020/09/21   GLS
2020/10/17   GLS
2021/05/26   GLS
2021/06/18   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/03/28   GLS
2022/06/13   GLS
2022/08/05   GLS
2022/08/27   GLS
2022/09/29   GLS
2022/12/18   GLS
2023/05/07   GLS
2023/05/12   GLS
2023/05/14   GLS
2023/10/29   GLS
********************************************/
#include "HUD.h"
#include "Atlantis.h"
#include "ParameterValues.h"
#include <MathSSV.h>
#include <EngConst.h>


const double SCALE = 25.788502804088015;// (px/º) use with angular distance from boresight (CX,CY) for fixed distances
const VECTOR3 HUD_POS_CDR = _V( 14.6146, -0.6527025, -2.59925 );// CDR HUD plane position (in runway coordinate system)
const VECTOR3 HUD_POS_PLT = _V( 14.6146, 0.6528925, -2.59925 );// PLT HUD plane position (in runway coordinate system)


constexpr unsigned short HUD_FC_ADDR[2] = {
	6,
	9
};


static unsigned int pow10( unsigned int pw )
{
	const unsigned int powa[4] = {1, 10, 100, 1000};
	return powa[pw];
}

HUD::HUD( AtlantisSubsystemDirector* _director, const string& _ident, unsigned short ID, BusManager* pBusManager ):AtlantisSubsystem( _director, _ident ), BusTerminal( pBusManager )
{
	this->ID = ID;

	testactive = false;
	testrot = PI;

	UpperLeftWindow[0] = 0;
	UpperRightWindow1[0] = 0;
	UpperRightWindow2[0] = 0;
	SituationLine[0] = 0;

	UpperLeftWindowFlash = false;

	dclt_sw_on = false;
	declutter_level = 0;

	gearstate = 0;
	tGear = 0.0;
	cssstate = 0;
	tCSS = 0.0;
	mlsnvstate = 0;
	tMLSNV = 0.0;
	bfstate = 0;
	tBF = 0.0;

	HUDFlashTime = 0.0;
	bHUDFlasher = true;

	GSIValid = false;
	IndicatedAltitudeValid = false;
	RadarAltitudeValid = false;
	NZValid = false;
	EquivalentAirspeedValid = false;

	HUD_CNTL1 = 0;
	FlagsWord1 = 0;
	FlagsWord2 = 0;

	Roll = 0.0;
	Pitch = 0.0;
	GSI = 0.0;
	IndicatedAltitude = 0.0;
	RadarAltitude = 0.0;
	AngleOfAttack = 0.0;
	EquivalentAirspeed = 0.0;
	SpeedbrakePosition = 0;
	SpeedbrakeCommand = 0;

	DR = 0;
	CR = 0;
	HR = 0;
	rwXdot = 0.0;
	rwYdot = 0.0;

	VehicleHeading = 0.0;
	RunwayHeading = 0.0;
	FlightPath1 = 0.0;
	FlightPath2 = 0.0;
	X_zero = 0.0;

	NZ = 0.0;
	Beta = 0.0;

	RW_LNGTH = 0;
	RunwayToGo = 0;
	DECEL_CMD_MAX = 0.0;

	RollError = 0.0;
	PitchError = 0.0;

	FDVVoffsetX = 0.0;
	FDVVoffsetY = 5.0;

	GuidanceoffsetX = 0.0;
	GuidanceoffsetY = 0.0;

	hassetmode = false;

	// connect to busses
	busA = (ID == 1) ? BUS_FC1 : BUS_FC3;
	busB = (ID == 1) ? BUS_FC2 : BUS_FC4;
	BusConnect( busA );
	BusConnect( busB );
	return;
}

HUD::~HUD( void )
{
	return;
}

void HUD::Rx( const BUS_ID id, void* data, const unsigned short datalen )
{
	if (HUDPower.IsSet() == false) return;

	// select source
	if (selbusA.IsSet())
	{
		if (id != busA) return;
	}
	else
	{
		if (id != busB) return;
	}

	unsigned int* rcvd = static_cast<unsigned int*>(data);

	//// process command word
	{
		// check address
		int dataaddr = (rcvd[0] >> 20) & 0b11111;
		if (HUD_FC_ADDR[ID - 1] != dataaddr) return;
	}

	// check parity
	if (CalcParity( rcvd[0] ) == 0) return;

	unsigned short wdcount = ((rcvd[0] >> 1) & 0b11111) + 1;// data words (rcvd = 0b00000 => 1 word)

	unsigned short msgid = (rcvd[0] >> 6) & 0b11111111111111;


	//// process command data words
	unsigned short datawords[32];// data field of command data words
	bool datawordsvalid[32];
	for (int i = 1; i <= wdcount; i++)
	{
		// check reception of words
		if (i > (datalen - 1))
		{
			datawordsvalid[i - 1] = false;
			continue;
		}

		// check parity
		if (CalcParity( rcvd[i] ) == 0)
		{
			datawordsvalid[i - 1] = false;
			continue;
		}

		// check address
		int dataaddr = (rcvd[i] >> 20) & 0b11111;
		if (HUD_FC_ADDR[ID - 1] != dataaddr)
		{
			datawordsvalid[i - 1] = false;
			continue;
		}

		// check SEV
		unsigned short SEV = (rcvd[i] >> 1) & 0b111;
		if (SEV != 0b101)
		{
			datawordsvalid[i - 1] = false;
			continue;
		}

		// save data
		datawords[i - 1] = (rcvd[i] >> 4) & 0xFFFF;
		datawordsvalid[i - 1] = true;
	}

	switch (msgid)
	{
		case 0b10000000000001:// ADI L
		case 0b01000000000001:// ADI R
			{
				if (wdcount == 14)// 14 words total
				{
					if (datawordsvalid[2] && datawordsvalid[3]) Roll = atan2( static_cast<short>(datawords[2]), static_cast<short>(datawords[3]) ) * DEG;
					if (datawordsvalid[4] && datawordsvalid[5]) Pitch = atan2( static_cast<short>(datawords[4]), static_cast<short>(datawords[5]) ) * DEG;
				}
			}
			break;
		case 0b10000000000100:// AVVI L
		case 0b01000000000100:// AVVI R
			{
				if (wdcount == 6)// 6 words total
				{
					if (datawordsvalid[0])
					{
						IndicatedAltitudeValid = (datawords[0] & 0x4000) != 0;
						RadarAltitudeValid = (datawords[0] & 0x1000) != 0;
					}
					if (datawordsvalid[2])
					{
						if (datawords[2] < 1600)
						{
							IndicatedAltitude = ((datawords[2] >> 3) - 220) / 0.2;
						}
						else if (datawords[2] < 2240)
						{
							IndicatedAltitude = ((datawords[2] >> 3) - 280) / 0.8;
						}
						else if (datawords[2] < 3840)
						{
							double a = -0.4686e-3;
							double b = 0.6343;
							double c = 280 - (datawords[2] >> 3);
							IndicatedAltitude = (-b + sqrt( (b * b) - (4 * a * c) )) / (2 * a);
						}
						else if (datawords[2] < 19760)
						{
							IndicatedAltitude = ((datawords[2] >> 3) - 470) / 0.02;
						}
						else
						{
							IndicatedAltitude = (((datawords[2] >> 3) - 2470) * 625) + 1e5;
						}
					}
					if (datawordsvalid[4])
					{
						if (datawords[4] < 16000)
						{
							double a = -2.343e-3;
							double b = 3.1715;
							double c = -(datawords[4] / 16.0);
							RadarAltitude = (-b + sqrt( (b * b) - (4 * a * c) )) / (2 * a);
						}
						else RadarAltitude = (((datawords[4] / 16.0) - 1000) * 10) + 500;
					}
				}
			}
			break;
		case 0b10000000001000:// AMI L
		case 0b01000000001000:// AMI R
			{
				if (wdcount == 6)// 6 words total
				{
					if (datawordsvalid[0])
					{
						EquivalentAirspeedValid = (datawords[0] & 0x1000) != 0;
						NZValid = (datawords[0] & 0x0800) != 0;
					}
					if (datawordsvalid[3]) AngleOfAttack = (datawords[3] >> 1) * 0.015;
					if (datawordsvalid[4]) EquivalentAirspeed = (datawords[4] >> 3) * 0.125;
					if (datawordsvalid[5])
					{
						if (datawords[5] & 0x8000) NZ = -((datawords[5] & 0x7FFF) / 8.0) * 0.00125;
						else NZ = ((datawords[5] & 0x7FFF) / 8.0) * 0.00250;
					}
				}
			}
			break;
		case 0b10000000100001:// HUD message 1
			{
				if (wdcount == 31)// 31 words total
				{
					if (datawordsvalid[0]) HUD_CNTL1 = datawords[0];
					if (datawordsvalid[2]) FlagsWord1 = datawords[2];
					if (datawordsvalid[3]) FlagsWord2 = datawords[3];
					if (datawordsvalid[4]) SpeedbrakePosition = datawords[4];
					if (datawordsvalid[5]) SpeedbrakeCommand = datawords[5];
					if (datawordsvalid[6]) DR = static_cast<short>(datawords[6]) * pow10( (HUD_CNTL1 & 0xC000) >> 14 );
					if (datawordsvalid[7]) CR = static_cast<short>(datawords[7]) * pow10( (HUD_CNTL1 & 0x3000) >> 12 );
					if (datawordsvalid[8]) HR = static_cast<short>(datawords[8]) * pow10( (HUD_CNTL1 & 0x0C00) >> 10 );
					if (datawordsvalid[9]) rwXdot = (datawords[9] - 32768.0) * 0.1;
					if (datawordsvalid[10]) rwYdot = (datawords[10] - 32768.0) * 0.1;
					if (datawordsvalid[12]) VehicleHeading = datawords[12] * 0.1;
					if (datawordsvalid[13]) ACC_DRAG = datawords[13] * 0.01;
					if (datawordsvalid[15]) FlightPath2 = -(datawords[15] * 0.1);
					if (datawordsvalid[16]) RollError = static_cast<short>(datawords[16]) * 0.01;
					if (datawordsvalid[17]) PitchError = static_cast<short>(datawords[17]) * 0.01;
					if (datawordsvalid[18]) RunwayHeading = static_cast<short>(datawords[18]) * 0.02;
					if (datawordsvalid[20]) FlightPath1 = -(datawords[20] * 0.1);
					if (datawordsvalid[21]) X_zero = -static_cast<double>(datawords[21]);
				}
			}
			break;
		case 0b10000000100010:// HUD message 2
			{
				if (wdcount == 12)// 12 words total
				{
					if (datawordsvalid[2]) RunwayToGo = datawords[2];
					if (datawordsvalid[3]) DECEL_CMD_MAX = datawords[3] * 0.1;
					if (datawordsvalid[4]) RW_LNGTH = datawords[4];
					/*if (datawordsvalid[9])*/ Beta = 0;//(datawords[9] * 0.01) - 30.0;
				}
			}
			break;
	}
	return;
}

bool HUD::OnParseLine( const char* line )
{
	if (!_strnicmp( line, "DECLUTTER", 9 ))
	{
		sscanf_s( line + 9, "%u", &declutter_level );
		if (declutter_level > 3) declutter_level = 0;
		return true;
	}
	else if (!_strnicmp( line, "GEAR", 4 ))
	{
		sscanf_s( line + 4, "%hu %lf", &gearstate, &tGear );
		if (gearstate > 3) gearstate = 0;
		if ((tGear < 0.0) || (tGear > 5.0)) tGear = 0.0;
		return true;
	}
	else if (!_strnicmp( line, "CSS", 3 ))
	{
		sscanf_s( line + 4, "%hu %lf", &cssstate, &tCSS );
		if (cssstate > 2) cssstate = 0;
		if ((tCSS < 0.0) || (tCSS > 5.0)) tCSS = 0.0;
		return true;
	}
	else if (!_strnicmp( line, "MLSNV", 5 ))
	{
		sscanf_s( line + 4, "%hu %lf", &mlsnvstate, &tMLSNV );
		if (mlsnvstate > 2) mlsnvstate = 0;
		if ((tMLSNV < 0.0) || (tMLSNV > 5.0)) tMLSNV = 0.0;
		return true;
	}
	else if (!_strnicmp( line, "B/F", 3 ))
	{
		sscanf_s( line + 4, "%hu %lf", &bfstate, &tBF );
		if (bfstate > 2) bfstate = 0;
		if ((tBF < 0.0) || (tBF > 5.0)) tBF = 0.0;
		return true;
	}
	return false;
}

void HUD::OnSaveState( FILEHANDLE scn ) const
{
	char cbuf[64];

	oapiWriteScenario_int( scn, "DECLUTTER", declutter_level );

	sprintf_s( cbuf, 64, "%d %f", gearstate, tGear );
	oapiWriteScenario_string( scn, "GEAR", cbuf );

	sprintf_s( cbuf, 64, "%d %f", cssstate, tCSS );
	oapiWriteScenario_string( scn, "CSS", cbuf );

	sprintf_s( cbuf, 64, "%d %f", mlsnvstate, tMLSNV );
	oapiWriteScenario_string( scn, "MLSNV", cbuf );

	sprintf_s( cbuf, 64, "%d %f", bfstate, tBF );
	oapiWriteScenario_string( scn, "B/F", cbuf );
	return;
}

void HUD::Realize( void )
{
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "HUD_SWITCHES", 16 );
	unsigned short tmp = (ID == 1) ? 0 : 8;
	HUDPower.Connect( pBundle, 0 + tmp );
	HUDDCLT.Connect( pBundle, 1 + tmp );
	// TODO mode norm
	HUDTest.Connect( pBundle, 3 + tmp );
	HUDBright.Connect( pBundle, 4 + tmp );
	HUDBrightNight.Connect( pBundle, 5 + tmp );
	// TODO bright auto
	HUDBrightDay.Connect( pBundle, 7 + tmp );

	pBundle = BundleManager()->CreateBundle( "LANDING_GEAR", 16 );
	NLG_Down.Connect( pBundle, 6 );
	LMG_Down.Connect( pBundle, 8 );
	RMG_Down.Connect( pBundle, 10 );
	return;
}

void HUD::OnPostStep( double simt, double simdt, double mjd )
{
	if (!HUDPower.IsSet())
	{
		hassetmode = false;

		testactive = false;
		testrot = PI;
		return;
	}

	if (!hassetmode)
	{
		// turn HUD on, don't care on what mode
		oapiSetHUDMode( HUD_SURFACE );

		// switch to allow other vessels to control HUD
		// if HUD is turned off in another vessel, the HUD power switch must be cycled
		hassetmode = true;
	}

	if (HUDTest.IsSet())// test pattern
	{
		testactive = true;

		// calc current angle
		testrot -= simdt * (PI / 5.0);// 5 seconds
		if (testrot < 0.0) testrot = 0.0;
	}
	else
	{
		testactive = false;
		testrot = PI;
	}

	for (int i = 0; i < 2; i++)
	{
		if (HUDDCLT.IsSet())
		{
			if (!dclt_sw_on)
			{
				dclt_sw_on = true;
				declutter_level++;
				if (declutter_level == 4) declutter_level = 0;
			}
		}
		else dclt_sw_on = false;
	}

	// upper left window
	unsigned short GEAR = (FlagsWord1 & 0x0200) >> 9;
	unsigned short GR_TR = (FlagsWord1 & 0x0004) >> 2;
	switch (gearstate)
	{
		case 0:
			if (GR_TR == 1)
			{
				strcpy_s( UpperLeftWindow, "/GR//" );
				UpperLeftWindowFlash = false;
				gearstate = 1;
			}
			else if (NLG_Down.IsSet() && LMG_Down.IsSet() && RMG_Down.IsSet())
			{
				strcpy_s( UpperLeftWindow, "GR-DN" );
				UpperLeftWindowFlash = false;
				tGear = 0.0;
				gearstate = 2;
			}
			else if (GEAR == 1)
			{
				strcpy_s( UpperLeftWindow, "GEAR" );
				UpperLeftWindowFlash = true;
			}
			break;
		case 1:
			if (NLG_Down.IsSet() && LMG_Down.IsSet() && RMG_Down.IsSet())
			{
				strcpy_s( UpperLeftWindow, "GR-DN" );
				UpperLeftWindowFlash = false;
				tGear = 0.0;
				gearstate = 2;
			}
			break;
		case 2:
			tGear += simdt;
			if (tGear >= 5.0)// clear after 5 sec
			{
				UpperLeftWindow[0] = 0;
				gearstate = 3;
			}
			break;
	}

	// upper right windows and situation line
	unsigned short PITCH_CSS = (FlagsWord2 & 0x0020) >> 5;
	unsigned short ROLL_CSS = (FlagsWord2 & 0x0008) >> 3;
	switch (cssstate)
	{
		case 0:
			if ((PITCH_CSS == 1) && (ROLL_CSS == 1))
			{
				tCSS = 0.0;
				cssstate = 1;
			}
			break;
		case 1:
			if ((PITCH_CSS == 0) || (ROLL_CSS == 0)) cssstate = 0;
			else
			{
				tCSS += simdt;
				if (tCSS >= 5.0) cssstate = 2;// switch to situation line after 5 sec
			}
			break;
		case 2:
			if ((PITCH_CSS == 0) || (ROLL_CSS == 0)) cssstate = 0;
			break;
	}

	unsigned short MLSNAV = (FlagsWord1 & 0x0040) >> 6;
	switch (mlsnvstate)
	{
		case 0:
			if (MLSNAV == 1)
			{
				tMLSNV = 0.0;
				mlsnvstate = 1;
			}
			break;
		case 1:
			if (MLSNAV == 0) mlsnvstate = 0;
			else
			{
				tMLSNV += simdt;
				if (tMLSNV >= 5.0) mlsnvstate = 2;// switch to situation line after 5 sec
			}
			break;
		case 2:
			if (MLSNAV == 0) mlsnvstate = 0;
			break;
	}

	unsigned short BODY_FLAP = (FlagsWord1 & 0x0400) >> 10;
	switch (bfstate)
	{
		case 0:
			if (BODY_FLAP == 1)
			{
				tBF = 0.0;
				bfstate = 1;
			}
			break;
		case 1:
			if (BODY_FLAP == 0) bfstate = 0;
			else
			{
				tBF += simdt;
				if (tBF >= 5.0) bfstate = 2;// switch to situation line after 5 sec
			}
			break;
		case 2:
			if (BODY_FLAP == 0) bfstate = 0;
			break;
	}

	UpperRightWindow1[0] = 0;
	UpperRightWindow2[0] = 0;
	if (cssstate == 1)
	{
		strcpy_s( UpperRightWindow1, "CSS" );
		if (mlsnvstate == 1) strcpy_s( UpperRightWindow2, "MLSNV" );
		else if (bfstate == 1) strcpy_s( UpperRightWindow2, "B/F" );
	}
	else if (mlsnvstate == 1)
	{
		strcpy_s( UpperRightWindow1, "MLSNV" );
		if (bfstate == 1) strcpy_s( UpperRightWindow2, "B/F" );
	}
	else if (bfstate == 1) strcpy_s( UpperRightWindow1, "B/F" );

	SituationLine[0] = 0;
	if (cssstate == 2) strcpy_s( SituationLine, "CSS " );
	if (mlsnvstate == 2) strcat_s( SituationLine, "MLSNV " );
	if (bfstate == 2) strcat_s( SituationLine, "B/F" );


	if (HUDFlashTime <= simt)
	{
		HUDFlashTime = simt + 0.25;
		bHUDFlasher = !bHUDFlasher;
	}

	const double HUDRATE = 2.0;
	unsigned short I_PHASE = (FlagsWord2 & 0x0007) >> 0;
	if (I_PHASE == 3)
	{
		// uncaged velocity vector
		FDVVoffsetX = range( FDVVoffsetX - (simdt * HUDRATE), Beta, FDVVoffsetX + (simdt * HUDRATE) );
		FDVVoffsetY = range( FDVVoffsetY - (simdt * HUDRATE), AngleOfAttack, FDVVoffsetY + (simdt * HUDRATE) );
	}
	else
	{
		// caged flight director
		FDVVoffsetX = range( FDVVoffsetX - (simdt * HUDRATE), 0.0, FDVVoffsetX + (simdt * HUDRATE) );
		FDVVoffsetY = range( FDVVoffsetY - (simdt * HUDRATE), 5.0, FDVVoffsetY + (simdt * HUDRATE) );
	}

	GuidanceoffsetX = range( GuidanceoffsetX - (simdt * HUDRATE), RollError, GuidanceoffsetX + (simdt * HUDRATE) );
	GuidanceoffsetY = range( GuidanceoffsetY - (simdt * HUDRATE), PitchError, GuidanceoffsetY + (simdt * HUDRATE) );
	return;
}

void HUD::SetBrightness( void )
{
	if (HUDBrightNight.IsSet())// night: [10:50]
	{
		oapiSetHUDIntensity( (HUDBright.GetVoltage() / (5.0 / 0.4)) + 0.1 );
	}
	else if (HUDBrightDay.IsSet())// day: [50:100]
	{
		oapiSetHUDIntensity( (HUDBright.GetVoltage() / (5.0 / 0.5)) + 0.5 );
	}
	else oapiSetHUDIntensity( 0.55 );// auto: 55
	return;
}

bool HUD::Draw( const HUDPAINTSPEC* hps, oapi::Sketchpad* skp )
{
	// only have PLT HUD draw when in PLT seat, use CDR HUD for everywhere else
	if ((ID == 1) && (STS()->GetVCMode() == 1))// VC_PLT
		return false;

	if (!HUDPower.IsSet()) return true;

	if (testactive)// test pattern
	{
		// fixed circles
		static const double testcx0 = 0.0;// vertical offset
		static const double testcy0 = 5.0;// horizontal offset
		static const double testcr[4] = {1.0, 0.5, 0.8, 0.3};// circle radius
		static const double testcx[4] = {-3.75, -2.5, 4.0, 2.5};// circle horizontal position (positive right)
		static const double testcy[4] = {2.25, -4.5, -2.5, 4.5};// circle vertical position (positive up)
		for (int i = 0; i < 4; i++)
			skp->Ellipse(
				hps->CX + Round( SCALE * (testcx[i] + testcx0 - testcr[i]) ), hps->CY + Round( SCALE * (-testcy[i] + testcy0 - testcr[i]) ),
				hps->CX + Round( SCALE * (testcx[i] + testcx0 + testcr[i]) ), hps->CY + Round( SCALE * (-testcy[i] + testcy0 + testcr[i]) ) );

		// rotating lines
		static const double testshortdist = sqrt( 2.0 ) / 2.0;
		static const double testlongdist = 3.0 * testshortdist;
		static const double testcxp01[4] = {testlongdist, -testshortdist, testshortdist, -testlongdist};// CCW
		static const double testcyp01[4] = {testshortdist, -testlongdist, -testlongdist, testshortdist};// CCW
		static const double testcxp02[4] = {-testlongdist, testshortdist, -testshortdist, testlongdist};// CW
		static const double testcyp02[4] = {-testshortdist, testlongdist, testlongdist, -testshortdist};// CW

		for (int i = 0; i < 4; i++)// run circles
		{
			double testcxp1[4];// CCW
			double testcyp1[4];// CCW
			double testcxp2[4];// CW
			double testcyp2[4];// CW
			double testoffx = testcx[i];
			double testoffy = testcy[i];
			for (int j = 0; j < 4; j++)// run points
			{
				// CCW
				testcxp1[j] = (((testcr[i] * testcxp01[j]) + testoffx) * cos( -testrot * sign( -testoffx ) )) - (((testcr[i] * testcyp01[j]) + testoffy) * sin( -testrot * sign( -testoffx ) ));
				testcyp1[j] = (((testcr[i] * testcxp01[j]) + testoffx) * sin( -testrot * sign( -testoffx ) )) + (((testcr[i] * testcyp01[j]) + testoffy) * cos( -testrot * sign( -testoffx ) ));
				// CW
				testcxp2[j] = (((testcr[i] * testcxp02[j]) + testoffx) * cos( testrot * sign( -testoffx ) )) - (((testcr[i] * testcyp02[j]) + testoffy) * sin( testrot * sign( -testoffx ) ));
				testcyp2[j] = (((testcr[i] * testcxp02[j]) + testoffx) * sin( testrot * sign( -testoffx ) )) + (((testcr[i] * testcyp02[j]) + testoffy) * cos( testrot * sign( -testoffx ) ));
			}
			// CCW
			skp->Line(
				hps->CX + Round( SCALE * (testcx0 + testcxp1[0]) ), hps->CY + Round( SCALE * (testcy0 - testcyp1[0]) ),
				hps->CX + Round( SCALE * (testcx0 + testcxp1[1]) ), hps->CY + Round( SCALE * (testcy0 - testcyp1[1]) ) );
			skp->Line(
				hps->CX + Round( SCALE * (testcx0 + testcxp1[2]) ), hps->CY + Round( SCALE * (testcy0 - testcyp1[2]) ),
				hps->CX + Round( SCALE * (testcx0 + testcxp1[3]) ), hps->CY + Round( SCALE * (testcy0 - testcyp1[3]) ) );
			// CW
			skp->Line(
				hps->CX + Round( SCALE * (testcx0 + testcxp2[0]) ), hps->CY + Round( SCALE * (testcy0 - testcyp2[0]) ),
				hps->CX + Round( SCALE * (testcx0 + testcxp2[1]) ), hps->CY + Round( SCALE * (testcy0 - testcyp2[1]) ) );
			skp->Line(
				hps->CX + Round( SCALE * (testcx0 + testcxp2[2]) ), hps->CY + Round( SCALE * (testcy0 - testcyp2[2]) ),
				hps->CX + Round( SCALE * (testcx0 + testcxp2[3]) ), hps->CY + Round( SCALE * (testcy0 - testcyp2[3]) ) );
		}
	}
	else if (STS()->GetGPCMajorMode() == 305)
	{
		// boresight
		skp->Line( hps->CX - 8, hps->CY, hps->CX + 8, hps->CY );
		skp->Line( hps->CX, hps->CY - 8, hps->CX, hps->CY + 8 );

		char cbuf[255];
		unsigned short WOWLON = (FlagsWord1 & 0x4000) >> 14;
		unsigned short ROLLOUT = (FlagsWord1 & 0x2000) >> 13;
		unsigned short SB = (FlagsWord1 & 0x0800) >> 11;
		unsigned short P_MODE = (FlagsWord2 & 0x1C00) >> 10;
		unsigned short I_PHASE = (FlagsWord2 & 0x0007) >> 0;

		if (declutter_level != 3)
		{
			// show upper left window (gear deployment status)
			if (UpperLeftWindow[0] && (!UpperLeftWindowFlash || bHUDFlasher))
				skp->Text( hps->CX - Round( SCALE * 4.0 ), hps->CY + Round( SCALE * 0.75 ), UpperLeftWindow, strlen( UpperLeftWindow ) );

			// upper right windows
			if ((WOWLON == 0) && (bHUDFlasher))
			{
				if (UpperRightWindow1[0]) skp->Text( hps->CX + Round( SCALE * 2.0 ), hps->CY + Round( SCALE * 0.75 ), UpperRightWindow1, strlen( UpperRightWindow1 ) );
				if (UpperRightWindow2[0]) skp->Text( hps->CX + Round( SCALE * 2.0 ), hps->CY + Round( SCALE * 1.4 ), UpperRightWindow2, strlen( UpperRightWindow2 ) );
			}

			// situation line
			if (SituationLine[0]) skp->Text( hps->CX - Round( SCALE * 5.0 ), hps->CY + Round( SCALE * 14.0 ), SituationLine, strlen( SituationLine ) );

			// speedbrake
			if ((SB == 0) || (bHUDFlasher)) DrawHUDSBScale( skp, hps );

			// draw flight director/velocity vector
			double FDVV_x;
			double FDVV_y;
			int iFDVV_x;
			int iFDVV_y;
			// TODO cage/uncage via ATT REF PB (JSC-23266, 2-36)
			if (I_PHASE == 3)
			{
				// uncaged velocity vector
				FDVV_x = hps->CX + (FDVVoffsetX * hps->Scale);
				FDVV_y = hps->CY + (FDVVoffsetY * hps->Scale);
				iFDVV_x = Round( FDVV_x );
				iFDVV_y = Round( FDVV_y );
				if (WOWLON == 0) skp->Ellipse( iFDVV_x - 6, iFDVV_y - 6, iFDVV_x + 6, iFDVV_y + 6 );
			}
			else
			{
				// caged flight director
				FDVV_x = hps->CX + (FDVVoffsetX * SCALE);
				FDVV_y = hps->CY + (FDVVoffsetY * SCALE);
				iFDVV_x = Round( FDVV_x );
				iFDVV_y = Round( FDVV_y );
				skp->Rectangle( iFDVV_x - 6, iFDVV_y - 6, iFDVV_x + 6, iFDVV_y + 6 );
			}
			// lines are the same for both FD and VV modes
			if (WOWLON == 0)
			{
				skp->Line( iFDVV_x - 16, iFDVV_y, iFDVV_x - 6, iFDVV_y );
				skp->Line( iFDVV_x + 15, iFDVV_y, iFDVV_x + 5, iFDVV_y );
				skp->Line( iFDVV_x, iFDVV_y - 11, iFDVV_x, iFDVV_y - 6 );
			}

			if ((P_MODE < 4) || ((cssstate != 0) && (WOWLON == 0)))// only removed at FNLFL in CSS
			{
				double Guidance_x = FDVV_x + (GuidanceoffsetX * SCALE * 6.0 / 25.0);
				double Guidance_y = FDVV_y + (GuidanceoffsetY * SCALE * 6.0 / 1.2);

				// if guidance diamond is within HUD area, draw it normally; otherwise, draw flashing diamond at edge of HUD
				bool bValid = true;
				if(Guidance_x < 0.0) {
					bValid = false;
					Guidance_x = 0.0;
				}
				else if(Guidance_x > hps->W) {
					bValid = false;
					Guidance_x = hps->W;
				}
				if(Guidance_y < 0.0) {
					bValid = false;
					Guidance_y = 0.0;
				}
				else if(Guidance_y > hps->H-57) {
					bValid = false;
					Guidance_y = hps->H-57;
				}
				if(bValid || bHUDFlasher) {
					skp->MoveTo(Round(Guidance_x)-5, Round(Guidance_y));
					skp->LineTo(Round(Guidance_x), Round(Guidance_y)+5);
					skp->LineTo(Round(Guidance_x)+5, Round(Guidance_y));
					skp->LineTo(Round(Guidance_x), Round(Guidance_y)-5);
					skp->LineTo(Round(Guidance_x)-5, Round(Guidance_y));
				}
			}

			// nz accel
			if (I_PHASE < 3) DrawHUDNormalAccel( skp, hps );

			// runway overlay
			if ((declutter_level == 0) && (WOWLON == 0)) DrawHUDRunwayOverlay( skp, hps );

			// draw pitch ladder
			int nPitch = static_cast<int>(Pitch);
			int pitchBar = nPitch - (nPitch%5); // display lines at 5-degree increments
			if (((declutter_level == 0) || (declutter_level == 1)) || ((WOWLON == 1) && (ROLLOUT == 0)))
			{
				// create rotated font for HUD pitch markings
				oapi::Font* pFont = oapiCreateFont(20, false, "Fixed", FONT_NORMAL, static_cast<int>(Roll * 10.0));
				oapi::Font* pOldFont = skp->SetFont(pFont);
				// draw pitch lines
				for (int i = 0; i >= -10; i-=5) DrawHUDPitchLine( skp, hps, pitchBar + i, Pitch, Roll );
				// deselect rotated font
				skp->SetFont(pOldFont);
				oapiReleaseFont(pFont);
			}
			else if (ROLLOUT == 0) DrawHUDPitchLine( skp, hps, 0, Pitch, Roll );// horizon line (if not printed before)

			// alt/vel + GSI
			double keas = EquivalentAirspeed;
			if (keas > 500.0) keas = 500.0;
			double alt = IndicatedAltitude;
			if ((declutter_level == 2) || (WOWLON == 1))
			{
				// numeric
				sprintf_s(cbuf, 255, "%3.0f", keas);
				if (WOWLON == 0)
				{
					if (RadarAltitudeValid) alt = RadarAltitude;

					skp->Text( Round( FDVV_x - (SCALE * 2.5) ), Round( FDVV_y - (SCALE * 1) ), cbuf, strlen( cbuf ) );

					int tmpalt;
					if (alt >= 32767.0) tmpalt = 32800;//32767;
					else if (alt > 1000.0) tmpalt = Round( alt * 0.005 ) * 200;
					else if (alt > 400.0) tmpalt = Round( alt * 0.01 ) * 100;
					else if (alt > 50.0) tmpalt = Round( alt * 0.1 ) * 10;
					else tmpalt = Round( alt );
					sprintf_s( cbuf, 255, "%d %c", tmpalt, RadarAltitudeValid ? 'R':' ' );
					skp->Text( Round( FDVV_x + (SCALE * 1.1) ), Round( FDVV_y - (SCALE * 1) ), cbuf, strlen( cbuf ) );
				}
				else if (ROLLOUT == 0) skp->Text( hps->CX - Round( SCALE * 1.5 ), hps->CY - Round( SCALE * 0.75 ), cbuf, strlen( cbuf ) );
				else
				{
					skp->Text( hps->CX - Round( SCALE * 2.1 ), hps->CY - Round( SCALE * 0.75 ), "G", 1 );
					skp->Text( hps->CX - Round( SCALE * 1.5 ), hps->CY - Round( SCALE * 0.75 ), cbuf, strlen( cbuf ) );
				}
			}
			else
			{
				// tape
				int yline = hps->CY + Round( SCALE * 5 );
				int ikeas = Round( keas * 0.2 ) * 5;
				int offset = yline + (int)((ikeas - keas) * Round( SCALE * 0.333333 ));// 15kn / 5º
				int tmp;
				int ytmp;
				for (int i = 0; i < 7; i++)
				{
					tmp = ikeas + ((i - 3) * 5);
					if (tmp < 0) continue;
					else if (tmp > 500) break;
					ytmp = offset + ((i - 3) * Round( SCALE * 1.666666 ));
					if (tmp % 10 == 0)
					{
						// number
						sprintf_s( cbuf, 255, "%d", tmp );
						skp->Text( hps->CX - Round( SCALE * 5.5 ), ytmp - 10, cbuf, strlen( cbuf ) );
					}
					else skp->Line( hps->CX - Round( SCALE * 5.5 ), ytmp, hps->CX - Round( SCALE * 5.2 ), ytmp );// line
				}
				skp->Line( hps->CX - Round( SCALE * 6.1 ), yline - 2, hps->CX - Round( SCALE * 5.5 ), yline - 2 );
				skp->Line( hps->CX - Round( SCALE * 6.1 ), yline - 1, hps->CX - Round( SCALE * 5.5 ), yline - 1 );
				skp->Line( hps->CX - Round( SCALE * 6.1 ), yline, hps->CX - Round( SCALE * 5.5 ), yline );
				skp->Line( hps->CX - Round( SCALE * 6.1 ), yline + 1, hps->CX - Round( SCALE * 5.5 ), yline + 1 );
				skp->Line( hps->CX - Round( SCALE * 6.1 ), yline + 2, hps->CX - Round( SCALE * 5.5 ), yline + 2 );

				DrawHUDAltTape( skp, hps, alt );
				skp->Line( hps->CX + Round( SCALE * 6.1 ), yline - 2, hps->CX + Round( SCALE * 5.5 ), yline - 2 );
				skp->Line( hps->CX + Round( SCALE * 6.1 ), yline - 1, hps->CX + Round( SCALE * 5.5 ), yline - 1 );
				skp->Line( hps->CX + Round( SCALE * 6.1 ), yline, hps->CX + Round( SCALE * 5.5 ), yline );
				skp->Line( hps->CX + Round( SCALE * 6.1 ), yline + 1, hps->CX + Round( SCALE * 5.5 ), yline + 1 );
				skp->Line( hps->CX + Round( SCALE * 6.1 ), yline + 2, hps->CX + Round( SCALE * 5.5 ), yline + 2 );

				// GSI
				DrawGSI( hps, skp );
			}
		}

		if ((P_MODE != 4) && (declutter_level < 3) && (I_PHASE == 3))
		{
			// draw OGS flight path triangles
			if (FlightPath2 < FlightPath1) DrawHUDGuidanceTriangles( skp, hps, FlightPath1, Pitch, Roll, /*FDVV_x*/hps->CX + (FDVVoffsetX * hps->Scale) );

			// draw pullup circle, exponential and shallow glide slope flight path triangles
			DrawHUDGuidanceTriangles( skp, hps, FlightPath2, Pitch, Roll, /*FDVV_x*/hps->CX + (FDVVoffsetX * hps->Scale) );
		}

		if ((WOWLON == 1) && ((WOWLON == 0) || (declutter_level < 3)))
		{
			// deceleration scale
			DrawHUDDecelerationScale( skp, hps );
		}

		if ((WOWLON == 0) && (declutter_level != 3))
		{
			// guidance mode
			DrawLowerLeftWindow( skp, hps );
		}
	}

	SetBrightness();

	return true;
}

bool HUD::DrawHUDPitchLine(oapi::Sketchpad *skp, const HUDPAINTSPEC *hps, int ladderPitch, double orbiterPitch, double orbiterBank)
{
	char pszBuf[8];

	double curPitchDelta = static_cast<double>(ladderPitch) - orbiterPitch;
	int textHeight = skp->GetCharSize() & 65535; // lower 16 bits of GetCharSize

	orbiterBank = -orbiterBank;

	VECTOR3 line_rot_vector;
	VECTOR3 line_dir_vector = RotateVectorZ(_V(1, 0, 0), orbiterBank);
	VECTOR3 line_pos = RotateVectorZ(_V(4*SCALE, curPitchDelta*hps->Scale, 0), orbiterBank) - line_dir_vector * 5 * SCALE * sin( orbiterBank * RAD );
	line_pos.x = hps->CX-line_pos.x;
	line_pos.y = hps->CY-line_pos.y;
	if(line_pos.y < 0 || line_pos.x < 0) return false;
	if(line_pos.y > hps->W || line_pos.x > hps->H) return false;
	VECTOR3 line_end = line_pos + line_dir_vector*8*SCALE;
	if(line_end.y < 0 || line_end.x < 0) return false;
	if(line_end.y > hps->W || line_end.x > hps->H) return false;

	// draw line
	if(ladderPitch < 0) { // 2 dashed lines
		VECTOR3 line_seg1_end = line_pos + line_dir_vector*0.666666*SCALE;
		skp->Line(Round(line_pos.x), Round(line_pos.y), Round(line_seg1_end.x), Round(line_seg1_end.y));
		VECTOR3 line_seg2_start = line_seg1_end + line_dir_vector*0.666666*SCALE;
		VECTOR3 line_seg2_end = line_pos + line_dir_vector*2*SCALE;
		skp->Line(Round(line_seg2_start.x), Round(line_seg2_start.y), Round(line_seg2_end.x), Round(line_seg2_end.y));

		VECTOR3 line_seg3_start = line_end - line_dir_vector*2*SCALE;
		VECTOR3 line_seg3_end = line_seg3_start + line_dir_vector*0.666666*SCALE;
		skp->Line(Round(line_seg3_start.x), Round(line_seg3_start.y), Round(line_seg3_end.x), Round(line_seg3_end.y));
		VECTOR3 line_seg4_start = line_seg3_end + line_dir_vector*0.666666*SCALE;
		skp->Line(Round(line_seg4_start.x), Round(line_seg4_start.y), Round(line_end.x), Round(line_end.y));
	}
	else if(ladderPitch > 0) { //  2 solid lines
		VECTOR3 line_seg1_end = line_pos + line_dir_vector*2*SCALE;
		skp->Line(Round(line_pos.x), Round(line_pos.y), Round(line_seg1_end.x), Round(line_seg1_end.y));
		VECTOR3 line_seg2_start = line_end - line_dir_vector*2*SCALE;
		skp->Line(Round(line_seg2_start.x), Round(line_seg2_start.y), Round(line_end.x), Round(line_end.y));
	}
	else { //  2 solid thick lines
		// draw a line above main line to save a thick line pen
		line_rot_vector = RotateVectorZ(_V(0, 1, 0), orbiterBank);
		VECTOR3 line_seg1_end = line_pos + line_dir_vector*2.2*SCALE;
		skp->Line(Round(line_pos.x), Round(line_pos.y), Round(line_seg1_end.x), Round(line_seg1_end.y));
		skp->Line(Round(line_pos.x + line_rot_vector.x), Round(line_pos.y + line_rot_vector.y), Round(line_seg1_end.x + line_rot_vector.x), Round(line_seg1_end.y + line_rot_vector.y));
		VECTOR3 line_seg2_start = line_end - line_dir_vector*2.2*SCALE;
		skp->Line(Round(line_seg2_start.x), Round(line_seg2_start.y), Round(line_end.x), Round(line_end.y));
		skp->Line(Round(line_seg2_start.x + line_rot_vector.x), Round(line_seg2_start.y + line_rot_vector.y), Round(line_end.x + line_rot_vector.x), Round(line_end.y + line_rot_vector.y));
	}
	// draw lines pointing toward horizon
	if(ladderPitch > 0) {
		line_rot_vector = RotateVectorZ(_V(0, 1, 0), orbiterBank);
		VECTOR3 left_line_end = line_pos + line_rot_vector*0.25*SCALE;
		skp->Line(Round(left_line_end.x), Round(left_line_end.y), Round(line_pos.x), Round(line_pos.y));
		VECTOR3 right_line_end = line_end + line_rot_vector*0.25*SCALE;
		skp->Line(Round(right_line_end.x), Round(right_line_end.y), Round(line_end.x), Round(line_end.y));
	}
	else if(ladderPitch < 0) {
		line_rot_vector = RotateVectorZ(_V(0, -1, 0), orbiterBank);
		VECTOR3 left_line_end = line_pos + line_rot_vector*0.25*SCALE;
		skp->Line(Round(left_line_end.x), Round(left_line_end.y), Round(line_pos.x), Round(line_pos.y));
		VECTOR3 right_line_end = line_end + line_rot_vector*0.25*SCALE;
		skp->Line(Round(right_line_end.x), Round(right_line_end.y), Round(line_end.x), Round(line_end.y));
	}

	// print angle
	if(ladderPitch != 0) {
		sprintf_s(pszBuf, 8, "%d", abs( ladderPitch ));
		int textWidth = skp->GetTextWidth(pszBuf);
		VECTOR3 textPos = line_end - line_dir_vector*(1+textWidth);
		if (ladderPitch < 0) textPos = textPos + line_rot_vector*(2+textHeight);
		else textPos = textPos + line_rot_vector*(12-textHeight);
		skp->Text(Round(textPos.x), Round(textPos.y), pszBuf, strlen(pszBuf));
	}

	return true;
}

void HUD::DrawTriangle(oapi::Sketchpad *skp, const VECTOR3& pt1, const VECTOR3& pt2, const VECTOR3& pt3)
{
	skp->Line(Round(pt1.x), Round(pt1.y), Round(pt2.x), Round(pt2.y));
	skp->Line(Round(pt1.x), Round(pt1.y), Round(pt3.x), Round(pt3.y));
	skp->Line(Round(pt3.x), Round(pt3.y), Round(pt2.x), Round(pt2.y));
}

void HUD::DrawHUDGuidanceTriangles(oapi::Sketchpad *skp, const HUDPAINTSPEC *hps, double degTrianglePitch, double degOrbiterPitch, double degOrbiterBank, double fdvv_x )
{
	double curPitchDelta = degTrianglePitch - degOrbiterPitch;

	degOrbiterBank = -degOrbiterBank;

	VECTOR3 line_dir_vector = RotateVectorZ(_V(1, 0, 0), degOrbiterBank);
	VECTOR3 line_rot_vector = RotateVectorZ(_V(0, 1, 0), degOrbiterBank);
	VECTOR3 line_pos = _V( fdvv_x, hps->CY, 0) - line_rot_vector*(curPitchDelta*hps->Scale); // midpoint between triangles

	VECTOR3 leftTrianglePt1 = line_pos - line_dir_vector*0.7*SCALE;
	VECTOR3 leftTrianglePt2 = line_pos - line_dir_vector*1.1*SCALE - line_rot_vector*0.2*SCALE;
	VECTOR3 leftTrianglePt3 = leftTrianglePt2 + line_rot_vector*0.4*SCALE;
	DrawTriangle(skp, leftTrianglePt1, leftTrianglePt2, leftTrianglePt3);

	VECTOR3 rightTrianglePt1 = line_pos + line_dir_vector*0.7*SCALE;
	VECTOR3 rightTrianglePt2 = line_pos + line_dir_vector*1.1*SCALE - line_rot_vector*0.2*SCALE;
	VECTOR3 rightTrianglePt3 = rightTrianglePt2 + line_rot_vector*0.4*SCALE;
	DrawTriangle(skp, rightTrianglePt1, rightTrianglePt2, rightTrianglePt3);
}

double HUD::HUDScale3Diff( double x1, double x2 ) const
{// y distance between 2 altitudes in scale 3, returns > 0 if x1 > x2
	static double a = 0.00005;
	static double b = -0.065;
	return (((x2 * x2) - (x1 * x1)) * a) + ((x2 - x1) * b);
}

bool HUD::DrawHUDAltTapeScale( oapi::Sketchpad *skp, const HUDPAINTSPEC *hps, int scale, int& pos, int &alt, bool up )
{
	char cbuf[255];
	double display_top = -1;
	double display_bottom = 11;

	// draw tape
	if (scale == 0)
	{
		// 400k-100k
		if (up)
		{
			while (alt <= 400000)
			{
				if (pos < (hps->CY + Round( SCALE * display_top ))) return false;

				if (alt % 10000 == 0)// number w 'K'
				{
					sprintf_s( cbuf, 255, "%dK", (int)(alt * 0.001) );
					skp->Text( hps->CX + Round( SCALE * 3.7 ), pos - 10, cbuf, strlen( cbuf ) );
				}
				else skp->Line( hps->CX + Round( SCALE * 5.2 ), pos, hps->CX + Round( SCALE * 5.5 ), pos );// line

				pos -= Round( SCALE * 2.5 );
				alt += 5000;
			}
		}
		else
		{
			while (alt >= 100000)
			{
				if (pos > (hps->CY + Round( SCALE * display_bottom ))) return false;

				if (alt % 10000 == 0)// number w 'K'
				{
					sprintf_s( cbuf, 255, "%dK", (int)(alt * 0.001) );
					skp->Text( hps->CX + Round( SCALE * 3.7 ), pos - 10, cbuf, strlen( cbuf ) );
				}
				else skp->Line( hps->CX + Round( SCALE * 5.2 ), pos, hps->CX + Round( SCALE * 5.5 ), pos );// line

				pos += Round( SCALE * 2.5 );
				alt -= 5000;
			}
			// correct pos and alt for next scale
			pos -= Round( SCALE * 2.5 ) - Round( SCALE * 1.666667 );// TODO this scale
			alt += 5000 - 500;// correct alt for next scale
		}
	}
	else if (scale == 1)
	{
		// 100k-1500
		if (up)
		{
			while (alt < 100000)
			{
				if (pos < (hps->CY + Round( SCALE * display_top ))) return false;

				if (alt % 5000 == 0)// number w 'K'
				{
					sprintf_s( cbuf, 255, "%2dK", (int)(alt * 0.001) );
					skp->Text( hps->CX + Round( SCALE * 4.2 ), pos - 10, cbuf, strlen( cbuf ) );
				}
				else if (alt % 1000 == 0)// number w/o 'K'
				{
					sprintf_s( cbuf, 255, "%3d", (int)(alt * 0.001) );
					skp->Text( hps->CX + Round( SCALE * 4.2 ), pos - 10, cbuf, strlen( cbuf ) );
				}
				else skp->Line( hps->CX + Round( SCALE * 5.2 ), pos, hps->CX + Round( SCALE * 5.5 ), pos );// line

				pos -= Round( SCALE * 1.666667 );
				alt += 500;
			}
		}
		else
		{
			while (alt >= 1500)
			{
				if (pos > (hps->CY + Round( SCALE * display_bottom ))) return false;

				if (alt % 5000 == 0)// number w 'K'
				{
					sprintf_s( cbuf, 255, "%2dK", (int)(alt * 0.001) );
					skp->Text( hps->CX + Round( SCALE * 4.2 ), pos - 10, cbuf, strlen( cbuf ) );
				}
				else if (alt % 1000 == 0)// number w/o 'K'
				{
					sprintf_s( cbuf, 255, "%3d", (int)(alt * 0.001) );
					skp->Text( hps->CX + Round( SCALE * 4.2 ), pos - 10, cbuf, strlen( cbuf ) );
				}
				else skp->Line( hps->CX + Round( SCALE * 5.2 ), pos, hps->CX + Round( SCALE * 5.5 ), pos );// line

				pos += Round( SCALE * 1.666667 );
				alt -= 500;
			}
		}
	}
	else if (scale == 2)
	{
		// 1500-500
		if (up)
		{
			while (alt < 1500)
			{
				if (pos < (hps->CY + Round( SCALE * display_top ))) return false;

				if (alt % 1000 == 0)// number w 'K'
				{
					sprintf_s( cbuf, 255, "%2dK", (int)(alt * 0.001) );
					skp->Text( hps->CX + Round( SCALE * 4.2 ), pos - 10, cbuf, strlen( cbuf ) );
				}
				else// number w/o 'K'
				{
					sprintf_s( cbuf, 255, "%3d", alt );
					skp->Text( hps->CX + Round( SCALE * 4.2 ), pos - 10, cbuf, strlen( cbuf ) );
				}

				pos -= Round( SCALE * 1.666667 );
				alt += 500;
			}
		}
		else
		{
			while (alt >= 500)
			{
				if (pos > (hps->CY + Round( SCALE * display_bottom ))) return false;

				if (alt % 1000 == 0)// number w 'K'
				{
					sprintf_s( cbuf, 255, "%2dK", (int)(alt * 0.001) );
					skp->Text( hps->CX + Round( SCALE * 4.2 ), pos - 10, cbuf, strlen( cbuf ) );
				}
				else// number w/o 'K'
				{
					sprintf_s( cbuf, 255, "%3d", alt );
					skp->Text( hps->CX + Round( SCALE * 4.2 ), pos - 10, cbuf, strlen( cbuf ) );
				}

				pos += Round( SCALE * 1.666667 );
				alt -= 500;
			}
			// correct pos and alt for next scale
			alt += 500;
			pos -= Round( SCALE * 1.666667 ) - Round( HUDScale3Diff( alt, alt - 50 ) * SCALE );
			alt -= 50;
		}
	}
	else if (scale == 3)
	{
		// 500-100
		if (up)
		{
			while (alt < 500)
			{
				if (pos < (hps->CY + Round( SCALE * display_top ))) return false;

				if (alt % 100 == 0)// number
				{
					sprintf_s( cbuf, 255, "%3d", alt );
					skp->Text( hps->CX + Round( SCALE * 4.2 ), pos - 10, cbuf, strlen( cbuf ) );
				}
				else skp->Line( hps->CX + Round( SCALE * 5.2 ), pos, hps->CX + Round( SCALE * 5.5 ), pos );// line

				pos -= Round( HUDScale3Diff( alt + 50, alt ) * SCALE );
				alt += 50;
			}
		}
		else
		{
			while (alt >= 100)
			{
				if (pos > (hps->CY + Round( SCALE * display_bottom ))) return false;

				if (alt % 100 == 0)// number
				{
					sprintf_s( cbuf, 255, "%3d", alt );
					skp->Text( hps->CX + Round( SCALE * 4.2 ), pos - 10, cbuf, strlen( cbuf ) );
				}
				else skp->Line( hps->CX + Round( SCALE * 5.2 ), pos, hps->CX + Round( SCALE * 5.5 ), pos );// line

				pos += Round( HUDScale3Diff( alt, alt - 50 ) * SCALE );
				alt -= 50;
			}
			// correct pos and alt for next scale
			alt += 50;
			pos -= Round( HUDScale3Diff( alt, alt - 50 ) * SCALE ) - Round( SCALE * 1.25 );
			alt -= 25;
		}
	}
	else if (scale == 4)
	{
		// 100-50
		if (up)
		{
			while (alt < 100)
			{
				if (pos < (hps->CY + Round( SCALE * display_top ))) return false;

				if (alt % 50 == 0)// number
				{
					sprintf_s( cbuf, 255, "%3d", alt );
					skp->Text( hps->CX + Round( SCALE * 4.2 ), pos - 10, cbuf, strlen( cbuf ) );
				}
				else skp->Line( hps->CX + Round( SCALE * 5.2 ), pos, hps->CX + Round( SCALE * 5.5 ), pos );// line

				pos -= Round( SCALE * 1.25 );
				alt += 25;
			}
		}
		else
		{
			while (alt >= 50)
			{
				if (pos > (hps->CY + Round( SCALE * display_bottom ))) return false;

				if (alt % 50 == 0)// number
				{
					sprintf_s( cbuf, 255, "%3d", alt );
					skp->Text( hps->CX + Round( SCALE * 4.2 ), pos - 10, cbuf, strlen( cbuf ) );
				}
				else skp->Line( hps->CX + Round( SCALE * 5.2 ), pos, hps->CX + Round( SCALE * 5.5 ), pos );// line

				pos += Round( SCALE * 1.25 );
				alt -= 25;
			}
			// correct pos and alt for next scale
			pos -= Round( SCALE * 1.25 ) - Round( SCALE * 0.6 );
			alt += 25 - 10;
		}
	}
	else// if (scale == 5)
	{
		// 50-0
		if (up)
		{
			while (alt < 50)
			{
				if (pos < (hps->CY + Round( SCALE * display_top ))) return false;

				if (alt == 0) skp->Text( hps->CX + Round( SCALE * 4.2 ), pos - 10, "  0", 3 );
				else skp->Line( hps->CX + Round( SCALE * 5.2 ), pos, hps->CX + Round( SCALE * 5.5 ), pos );// line

				pos -= Round( SCALE * 0.6 );
				alt += 10;
			}
		}
		else
		{
			while (alt >= 0)
			{
				if (pos > (hps->CY + Round( SCALE * display_bottom ))) return false;

				if (alt == 0) skp->Text( hps->CX + Round( SCALE * 4.2 ), pos - 10, "  0", 3 );
				else skp->Line( hps->CX + Round( SCALE * 5.2 ), pos, hps->CX + Round( SCALE * 5.5 ), pos );// line

				pos += Round( SCALE * 0.6 );
				alt -= 10;
			}
		}
	}
	return true;
}

void HUD::DrawHUDAltTape( oapi::Sketchpad *skp, const HUDPAINTSPEC *hps, double alt )
{
	if (alt >= 400000) alt = 400000;

	int tmpalt = Round( alt );
	int ialt = 0;
	int offset;
	int altscale;

	if (alt >= 100000)
	{
		altscale = 0;// 400k-100k
		ialt = Round( alt * 0.0002 ) * 5000;
		offset = Round( (tmpalt - ialt) * SCALE * 0.0005 );// 10000ft / 5º (?)
	}
	else if (alt >= 1500)
	{
		altscale = 1;// 100k-1500
		ialt = Round( alt * 0.002 ) * 500;
		offset = Round( (tmpalt - ialt) * SCALE * 0.003333 );// 1500ft / 5º
	}
	else if (alt >= 500)
	{
		altscale = 2;// 1500-500
		ialt = Round( alt * 0.002 ) * 500;
		offset = Round( (tmpalt - ialt) * SCALE * 0.003333 );// 1500ft / 5º
	}
	else if (alt >= 100)
	{
		altscale = 3;// 500-100
		ialt = Round( alt * 0.02 ) * 50;
		offset = Round( HUDScale3Diff( tmpalt, ialt ) * SCALE );
	}
	else if (alt >= 50)
	{
		altscale = 4;// 100-50
		ialt = Round( alt * 0.04 ) * 25;
		offset = Round( (tmpalt - ialt) * SCALE * 0.05 );// 100ft / 5º
	}
	else
	{
		altscale = 5;// 50-0
		ialt = Round( alt * 0.1 ) * 10;
		offset = Round( (tmpalt - ialt) * SCALE * 0.06 );// 50ft / 3º
	}

	int tmp = ialt;
	int ytmp = offset + hps->CY + Round( SCALE * 5 );
	int tmp_altscale = altscale;
	// up
	do
	{
		if (DrawHUDAltTapeScale( skp, hps, tmp_altscale, ytmp, tmp, true ) == false) break;
		tmp_altscale--;
	}
	while (tmp_altscale >= 0);

	tmp = ialt;
	ytmp = offset + hps->CY + Round( SCALE * 5 );
	tmp_altscale = altscale;
	// advance so it doesn't print the center-most symbol twice
	if (altscale == 0)
	{
		tmp -= 5000;
		ytmp += Round( SCALE * 2.5 );
	}
	else if (altscale == 1)
	{
		tmp -= 500;
		ytmp += Round( SCALE * 1.666667 );
	}
	else if (altscale == 2)
	{
		tmp -= 500;
		ytmp += Round( SCALE * 1.666667 );
	}
	else if (altscale == 3)
	{
		tmp -= 50;
		ytmp += Round( HUDScale3Diff( tmp + 50, tmp ) * SCALE );
	}
	else if (altscale == 4)
	{
		tmp -= 25;
		ytmp += Round( SCALE * 1.25 );
	}
	else// if (altscale == 5)
	{
		tmp -= 10;
		ytmp += Round( SCALE * 0.6 );
	}
	// down
	do
	{
		if (DrawHUDAltTapeScale( skp, hps, tmp_altscale, ytmp, tmp, false ) == false) break;
		tmp_altscale++;
	}
	while (tmp_altscale <= 5);
	return;
}

void HUD::DrawLowerLeftWindow( oapi::Sketchpad *skp, const HUDPAINTSPEC *hps )
{
	char cbuf[8];
	unsigned short P_MODE = (FlagsWord2 & 0x1C00) >> 10;
	unsigned short I_PHASE = (FlagsWord2 & 0x0007) >> 0;

	if ((I_PHASE == 0) && (P_MODE == 0)) strcpy_s( cbuf, "S-TRN" );
	else if ((I_PHASE == 1) && (P_MODE == 0)) strcpy_s( cbuf, "ACQ" );
	else if ((I_PHASE == 2) && (P_MODE == 0)) strcpy_s( cbuf, "HDG" );
	else if ((I_PHASE == 3) && (P_MODE == 0)) strcpy_s( cbuf, "PRFNL" );
	else if (P_MODE == 1) strcpy_s( cbuf, "CAPT" );
	else if (P_MODE == 2) strcpy_s( cbuf, "OGS" );
	else if (P_MODE == 3) strcpy_s( cbuf, "FLARE" );
	else if (P_MODE == 4) strcpy_s( cbuf, "FNLFL" );
	else return;

	skp->Text( hps->CX - Round( SCALE * 4 ), hps->CY + Round( SCALE * 12.1 ), cbuf, strlen( cbuf ) );
	return;
}

void HUD::DrawHUDSBScale( oapi::Sketchpad *skp, const HUDPAINTSPEC *hps ) const
{
	skp->Line( hps->CX + Round( SCALE * 0.4 ), hps->CY + Round( SCALE * 12.5 ), hps->CX + Round( SCALE * 3.5 ), hps->CY + Round( SCALE * 12.5 ) );

	skp->Line( hps->CX + Round( SCALE * 0.4 ), hps->CY + Round( SCALE * 12.28 ), hps->CX + Round( SCALE * 0.4 ), hps->CY + Round( SCALE * 12.72 ) );
	skp->Line( hps->CX + Round( SCALE * 1.175 ), hps->CY + Round( SCALE * 12.37 ), hps->CX + Round( SCALE * 1.175 ), hps->CY + Round( SCALE * 12.63 ) );
	skp->Line( hps->CX + Round( SCALE * 1.95 ), hps->CY + Round( SCALE * 12.37 ), hps->CX + Round( SCALE * 1.95 ), hps->CY + Round( SCALE * 12.63 ) );
	skp->Line( hps->CX + Round( SCALE * 2.725 ), hps->CY + Round( SCALE * 12.37 ), hps->CX + Round( SCALE * 2.725 ), hps->CY + Round( SCALE * 12.63 ) );
	skp->Line( hps->CX + Round( SCALE * 3.5 ), hps->CY + Round( SCALE * 12.28 ), hps->CX + Round( SCALE * 3.5 ), hps->CY + Round( SCALE * 12.72 ) );

	int commanded = Round( SCALE * (0.4 + (SpeedbrakeCommand * 0.031)) );
	int act = Round( SCALE * (0.4 + (SpeedbrakePosition * 0.031)) );
	//actual
	skp->MoveTo( hps->CX + act, hps->CY + Round( SCALE * 12.49 ) );
	skp->LineTo( hps->CX + act - Round( SCALE * 0.2 ), hps->CY + Round( SCALE * 12.09 ) );
	skp->LineTo( hps->CX + act + Round( SCALE * 0.2 ), hps->CY + Round( SCALE * 12.09 ) );
	skp->LineTo( hps->CX + act, hps->CY + Round( SCALE * 12.49 ) );
	//commanded
	skp->MoveTo( hps->CX + commanded, hps->CY + Round( SCALE * 12.51 ) );
	skp->LineTo( hps->CX + commanded - Round( SCALE * 0.2 ), hps->CY + Round( SCALE * 12.91 ) );
	skp->LineTo( hps->CX + commanded + Round( SCALE * 0.2 ), hps->CY + Round( SCALE * 12.91 ) );
	skp->LineTo( hps->CX + commanded, hps->CY + Round( SCALE * 12.51 ) );
	skp->Line( hps->CX + commanded, hps->CY + Round( SCALE * 12.91 ), hps->CX + commanded, hps->CY + Round( SCALE * 13.2 ) );
	return;
}

void HUD::DrawHUDDecelerationScale( oapi::Sketchpad *skp, const HUDPAINTSPEC *hps ) const
{
	skp->Line( hps->CX + Round( SCALE * 4.98 ), hps->CY - Round( SCALE * 1.0 ), hps->CX + Round( SCALE * 5.42 ), hps->CY - Round( SCALE * 1.0 ) );
	skp->Line( hps->CX + Round( SCALE * 5.07 ), hps->CY + Round( SCALE * 0.25 ), hps->CX + Round( SCALE * 5.33 ), hps->CY + Round( SCALE * 0.25 ) );
	skp->Line( hps->CX + Round( SCALE * 5.07 ), hps->CY + Round( SCALE * 1.5 ), hps->CX + Round( SCALE * 5.33 ), hps->CY + Round( SCALE * 1.5 ) );
	skp->Line( hps->CX + Round( SCALE * 5.07 ), hps->CY + Round( SCALE * 2.75 ), hps->CX + Round( SCALE * 5.33 ), hps->CY + Round( SCALE * 2.75 ) );
	skp->Line( hps->CX + Round( SCALE * 4.98 ), hps->CY + Round( SCALE * 4.0 ), hps->CX + Round( SCALE * 5.42 ), hps->CY + Round( SCALE * 4.0 ) );

	// commanded deceleration
	double RW_TGO = (RW_LNGTH - RunwayToGo) - DR;// [ft]
	if (RW_TGO == 0.0) RW_TGO = 0.001;// prevent division by 0
	double v = rwXdot;// [fps]
	double da = (v * v) / (2.0 * RW_TGO);
	double y = range( 0.0, (da * 5.0) / DECEL_CMD_MAX, 5.0 ) - 1.0;
	skp->Line( hps->CX + Round( SCALE * 5.2 ), hps->CY + Round( SCALE * y ), hps->CX + Round( SCALE * 5.51 ), hps->CY + Round( SCALE * (y - 0.25) ) );
	skp->Line( hps->CX + Round( SCALE * 5.51 ), hps->CY + Round( SCALE * (y - 0.25) ), hps->CX + Round( SCALE * 5.51 ), hps->CY + Round( SCALE * (y + 0.25) ) );
	skp->Line( hps->CX + Round( SCALE * 5.51 ), hps->CY + Round( SCALE * (y + 0.25) ), hps->CX + Round( SCALE * 5.2 ), hps->CY + Round( SCALE * y ) );
	skp->Line( hps->CX + Round( SCALE * 5.51 ), hps->CY + Round( SCALE * y ), hps->CX + Round( SCALE * 5.8 ), hps->CY + Round( SCALE * y ) );

	// current deceleration
	y = range( 0.0, (ACC_DRAG * 5.0) / DECEL_CMD_MAX, 5.0 ) - 1.0;
	skp->Line( hps->CX + Round( SCALE * 5.2 ), hps->CY + Round( SCALE * y ), hps->CX + Round( SCALE * 4.89 ), hps->CY + Round( SCALE * (y + 0.25) ) );
	skp->Line( hps->CX + Round( SCALE * 4.89 ), hps->CY + Round( SCALE * (y + 0.25) ), hps->CX + Round( SCALE * 4.89 ), hps->CY + Round( SCALE * (y - 0.25) ) );
	skp->Line( hps->CX + Round( SCALE * 4.89 ), hps->CY + Round( SCALE * (y - 0.25) ), hps->CX + Round( SCALE * 5.2 ), hps->CY + Round( SCALE * y ) );
	return;
}

void HUD::DrawHUDRunwayOverlay( oapi::Sketchpad *skp, const HUDPAINTSPEC *hps ) const
{
	const unsigned short rwyWidth = 300;// fixed runway width [ft]

	// calculate position of runway corners in an vehicle-centered runway coordinate system
	VECTOR3 rwy1_l = _V( -DR, -CR, -HR ) - _V( 0.0, rwyWidth * 0.5, 0.0 );
	VECTOR3 rwy1_r = rwy1_l + _V( 0.0, rwyWidth, 0.0 );
	VECTOR3 rwy2_l = rwy1_l + _V( RW_LNGTH, 0.0, 0.0 );
	VECTOR3 rwy2_r = rwy1_r + _V( RW_LNGTH, 0.0, 0.0 );

	// draw runway
	int rwy1_l_HUDX = 0;
	int rwy1_l_HUDY = 0;
	int rwy1_r_HUDX = 0;
	int rwy1_r_HUDY = 0;
	int rwy2_l_HUDX = 0;
	int rwy2_l_HUDY = 0;
	int rwy2_r_HUDX = 0;
	int rwy2_r_HUDY = 0;
	if (Runway2HUD_Line( rwy1_l, rwy1_r, rwy1_l_HUDX, rwy1_l_HUDY, rwy1_r_HUDX, rwy1_r_HUDY, Pitch, Roll, RunwayHeading - VehicleHeading, hps ))
		skp->Line( rwy1_l_HUDX, rwy1_l_HUDY, rwy1_r_HUDX, rwy1_r_HUDY );
	if (Runway2HUD_Line( rwy1_r, rwy2_r, rwy1_r_HUDX, rwy1_r_HUDY, rwy2_r_HUDX, rwy2_r_HUDY, Pitch, Roll, RunwayHeading - VehicleHeading, hps ))
		skp->Line( rwy1_r_HUDX, rwy1_r_HUDY, rwy2_r_HUDX, rwy2_r_HUDY );
	if (Runway2HUD_Line( rwy2_r, rwy2_l, rwy2_r_HUDX, rwy2_r_HUDY, rwy2_l_HUDX, rwy2_l_HUDY, Pitch, Roll, RunwayHeading - VehicleHeading, hps ))
		skp->Line( rwy2_r_HUDX, rwy2_r_HUDY, rwy2_l_HUDX, rwy2_l_HUDY );
	if (Runway2HUD_Line( rwy2_l, rwy1_l, rwy2_l_HUDX, rwy2_l_HUDY, rwy1_l_HUDX, rwy1_l_HUDY, Pitch, Roll, RunwayHeading - VehicleHeading, hps ))
		skp->Line( rwy2_l_HUDX, rwy2_l_HUDY, rwy1_l_HUDX, rwy1_l_HUDY );

	// aim points
	const VECTOR3 SteepAimPoint = _V( X_zero, 0.0, 0.0 );// [ft]
	const VECTOR3 ShallowAimPoint = _V( 1000.0, 0.0, 0.0 );// [ft]

	int st_HUDX = 0;
	int st_HUDY = 0;
	int sh_HUDX = 0;
	int sh_HUDY = 0;
	if (Runway2HUD_Point( SteepAimPoint + _V( -DR, -CR, -HR ), st_HUDX, st_HUDY, Pitch, Roll, RunwayHeading - VehicleHeading, hps ))
		skp->Ellipse( st_HUDX - 4, st_HUDY - 4, st_HUDX + 4, st_HUDY + 4 );
	if (Runway2HUD_Point( ShallowAimPoint + _V( -DR, -CR, -HR ), sh_HUDX, sh_HUDY, Pitch, Roll, RunwayHeading - VehicleHeading, hps ))
		skp->Ellipse( sh_HUDX - 4, sh_HUDY - 4, sh_HUDX + 4, sh_HUDY + 4 );

	if (Runway2HUD_Line( SteepAimPoint + _V( -DR, -CR, -HR ), ShallowAimPoint + _V( -DR, -CR, -HR ), st_HUDX, st_HUDY, sh_HUDX, sh_HUDY, Pitch, Roll, RunwayHeading - VehicleHeading, hps ))
		skp->Line( st_HUDX, st_HUDY, sh_HUDX, sh_HUDY );
	return;
}

void HUD::DrawHUDNormalAccel( oapi::Sketchpad *skp, const HUDPAINTSPEC *hps ) const
{
	if (!NZValid) return;

	char cbuf[32];
	sprintf_s( cbuf, 32, "%4.1f G", NZ );
	skp->Text( hps->CX - Round( SCALE * 3.0 ), hps->CY + Round( SCALE * 5.75 ), cbuf, strlen( cbuf ) );
	return;
}

bool HUD::Runway2HUD_Point( const VECTOR3& pt_rwy, int& pt_HUD_X, int& pt_HUD_Y, double pitch, double roll, double hdg_ofs, const HUDPAINTSPEC *hps ) const
{
	// convert to meters
	VECTOR3 pt = pt_rwy * FPS2MS;

	// add heading "offset"
	pt = RotateVectorZ( pt, hdg_ofs );

	// add pitch "offset"
	pt = RotateVectorY( pt, pitch );

	// add roll "offset"
	pt = RotateVectorX( pt, roll );

	// add camera offset (in runway coordinate system)
	VECTOR3 camPos;
	STS()->GetCameraOffset( camPos );
	camPos = _V( camPos.z, camPos.x, -camPos.y );
	pt -= camPos;

	// don't draw if point is behind vehicle
	if (pt.x < 0.0) return false;

	// calculate angle from boresight [deg]
	double ang = angle( _V( 1.0, 0.0, 0.0 ), pt ) * DEG;

	// calculate clock angle around boresight [rad]
	double clk = atan2( pt.z, pt.y );

	// calculate X and Y angles from boresight [deg]
	double angX = ang * cos( clk );
	double angY = ang * sin( clk );

	// calculate points position in HUD coordinates [px]
	pt_HUD_X = hps->CX + Round( hps->Scale * angX );
	pt_HUD_Y = hps->CY + Round( hps->Scale * angY );
	return true;
}

bool HUD::Runway2HUD_Line( const VECTOR3& pt1_rwy, const VECTOR3& pt2_rwy, int& pt1_HUD_X, int& pt1_HUD_Y, int& pt2_HUD_X, int& pt2_HUD_Y, double pitch, double roll, double hdg_ofs, const HUDPAINTSPEC *hps ) const
{
	// convert to meters
	VECTOR3 pt1 = pt1_rwy * FPS2MS;
	VECTOR3 pt2 = pt2_rwy * FPS2MS;

	// add heading "offset"
	pt1 = RotateVectorZ( pt1, hdg_ofs );
	pt2 = RotateVectorZ( pt2, hdg_ofs );

	// add pitch "offset"
	pt1 = RotateVectorY( pt1, pitch );
	pt2 = RotateVectorY( pt2, pitch );

	// add roll "offset"
	pt1 = RotateVectorX( pt1, roll );
	pt2 = RotateVectorX( pt2, roll );

	// add camera offset (in runway coordinate system)
	VECTOR3 camPos;
	STS()->GetCameraOffset( camPos );
	//pt1 -= camPos;
	//pt2 -= camPos;
	VECTOR3 camPos2 = STS()->GetOrbiterCoGOffset() + VC_OFFSET;
	camPos2 = _V( camPos2.z, camPos2.x, -camPos2.y );
	camPos2 += HUD_POS_CDR;
	//camPos2 += HUD_POS_PLT;
	pt1 -= camPos2;
	pt2 -= camPos2;

	///////////////////////////////////////////////
	if (pt1.x <= 0.0)
	{
		if (pt2.x <= 0.0) return false;// both points behind, nothing to draw
		else
		{
			// pt2 in view, pt1 behind
			VECTOR3 pt12 = pt2 - pt1;
			double t = dotp( _V( 1.0, 0.0, 0.0 ), pt1 ) / dotp( -pt12, _V( 1.0, 0.0, 0.0 ) );
			pt1 = pt1 + (pt12 * t);
		}
	}
	else
	{
		if (pt2.x <= 0.0)
		{
			// pt1 in view, pt2 behind
			VECTOR3 pt21 = pt1 - pt2;
			double t = dotp( _V( 1.0, 0.0, 0.0 ), pt2 ) / dotp( -pt21, _V( 1.0, 0.0, 0.0 ) );
			pt2 = pt2 + (pt21 * t);
		}
		//else// both points in view
	}


	///////////////////////////////////////////////

	// calculate angle from boresight [deg]
	double ang1 = angle( _V( 1.0, 0.0, 0.0 ), pt1 ) * DEG;
	double ang2 = angle( _V( 1.0, 0.0, 0.0 ), pt2 ) * DEG;

	// calculate clock angle around boresight [rad]
	double clk1 = atan2( pt1.z, pt1.y );
	double clk2 = atan2( pt2.z, pt2.y );

	// calculate X and Y angles from boresight [deg]
	double angX1 = ang1 * cos( clk1 );
	double angY1 = ang1 * sin( clk1 );
	double angX2 = ang2 * cos( clk2 );
	double angY2 = ang2 * sin( clk2 );

	// calculate points position in HUD coordinates [px]
	pt1_HUD_X = hps->CX + Round( hps->Scale * angX1 );
	pt1_HUD_Y = hps->CY + Round( hps->Scale * angY1 );
	pt2_HUD_X = hps->CX + Round( hps->Scale * angX2 );
	pt2_HUD_Y = hps->CY + Round( hps->Scale * angY2 );
	return true;
}

void HUD::DrawGSI( const HUDPAINTSPEC* hps, oapi::Sketchpad* skp )
{
	if (!GSIValid) return;

	// h > 10000ft: +/-5000ft
	// h < 5000ft: +/-500ft
	// 10000ft > h > 5000ft: linear ramp
	double tmp = 19.0 - range( 5000.0, IndicatedAltitude, 10000.0 ) * 9.0 / 5000.0;
	double pos = range( -6.0, GSI * tmp, 6.0 );
	if ((fabs( pos ) >= 6.0) && (bHUDFlasher)) return;

	// draw triangle
	VECTOR3 pt1 = _V( hps->CX + (SCALE * 6.1), hps->CY + (SCALE * (pos + 5.0)), 0.0 );
	VECTOR3 pt2 = _V( pt1.x + (SCALE * 0.4), pt1.y + (SCALE * 0.25), 0.0 );
	VECTOR3 pt3 = _V( pt2.x, pt2.y - (SCALE * 0.5), 0.0 );
	DrawTriangle( skp, pt1, pt2, pt3 );
	return;
}

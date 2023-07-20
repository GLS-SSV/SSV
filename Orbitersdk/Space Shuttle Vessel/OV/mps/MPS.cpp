/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/05/10   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/01/20   GLS
2021/06/18   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/01/10   GLS
2022/01/15   GLS
2022/06/11   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "MPS.h"
#include <Orbitersdk.h>
#include "../Atlantis.h"
#include "HeliumSystem.h"
#include <MathSSV.h>
#include <PressureActuatedValve.h>
#include <SolenoidValve.h>
#include <cassert>


namespace mps
{
	MPS::MPS( AtlantisSubsystemDirector* _director, HeSysPneu* HeSys ):AtlantisSubsystem( _director, "MPS" )
	{
		this->HeSys = HeSys;

		ptrLV12 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );
		ptrLV13 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );
		ptrLV14 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );
		ptrLV15 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );
		ptrLV16 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );
		ptrLV17 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );
		ptrLV18 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );
		ptrLV19 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );
		ptrLV20 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );
		ptrLV21 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );
		ptrLV22 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );
		ptrLV23 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );
		ptrLV24 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );
		ptrLV25 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );

		ptrLV28 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );
		ptrLV29 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );
		ptrLV30 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );
		ptrLV31 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );
		ptrLV32 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );
		ptrLV33 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );
		ptrLV34 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );
		ptrLV35 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );

		ptrLV39 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );
		ptrLV40 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );
		ptrLV41 = new SolenoidValve( 0, 1000, true, ptrLV40, nullptr );
		ptrLV42 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );
		ptrLV43 = new SolenoidValve( 0, 1000, true, ptrLV42, nullptr );

		ptrLV46 = new SolenoidValve( 1, 1000, true, HeSys, nullptr );
		ptrLV47 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );
		ptrLV48 = new SolenoidValve( 1, 1000, true, HeSys, nullptr );
		ptrLV49 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );
		ptrLV50 = new SolenoidValve( 1, 1000, true, HeSys, nullptr );
		ptrLV51 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );

		ptrLV53 = new SolenoidValve( 1, 500, false, nullptr, nullptr );
		ptrLV54 = new SolenoidValve( 1, 500, false, nullptr, nullptr );
		ptrLV55 = new SolenoidValve( 1, 500, false, nullptr, nullptr );
		ptrLV56 = new SolenoidValve( 1, 500, false, nullptr, nullptr );
		ptrLV57 = new SolenoidValve( 1, 500, false, nullptr, nullptr );
		ptrLV58 = new SolenoidValve( 1, 500, false, nullptr, nullptr );

		ptrLV72 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );
		ptrLV73 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );

		ptrLV76 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );
		ptrLV77 = new SolenoidValve( 1, 1000, true, HeSys, nullptr );
		ptrLV78 = new SolenoidValve( 1, 1000, true, HeSys, nullptr );

		// TODO find a way to make LV80, 81 and 82 connect to PV1, 2 and 3
		ptrLV80 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );
		ptrLV81 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );
		ptrLV82 = new SolenoidValve( 0, 1000, true, HeSys, nullptr );
		ptrLV83 = new SolenoidValve( 0, 1000, true, ptrLV12, nullptr );
		ptrLV84 = new SolenoidValve( 0, 1000, true, ptrLV14, nullptr );
		ptrLV85 = new SolenoidValve( 0, 1000, true, ptrLV16, nullptr );

		ptrPV1 = new PressureActuatedValve( 1, 100, ptrLV83, ptrLV13, nullptr, nullptr );
		ptrPV2 = new PressureActuatedValve( 1, 100, ptrLV84, ptrLV15, nullptr, nullptr );
		ptrPV3 = new PressureActuatedValve( 1, 100, ptrLV85, ptrLV17, nullptr, nullptr );
		ptrPV4 = new PressureActuatedValve( 0, 100, ptrLV18, ptrLV19, nullptr, nullptr );
		ptrPV5 = new PressureActuatedValve( 0, 100, ptrLV20, ptrLV21, nullptr, nullptr );
		ptrPV6 = new PressureActuatedValve( 0, 100, ptrLV22, ptrLV23, nullptr, nullptr );
		ptrPV7 = new PressureActuatedValve( 0, 100, nullptr, ptrLV24, nullptr, nullptr );
		ptrPV8 = new PressureActuatedValve( 0, 100, nullptr, ptrLV25, nullptr, nullptr );
		ptrPV9 = new PressureActuatedValve( 0, 20, ptrLV28, ptrLV29, nullptr, nullptr );
		ptrPV10 = new PressureActuatedValve( 0, 20, ptrLV30, ptrLV31, nullptr, nullptr );
		ptrPV11 = new PressureActuatedValve( 0, 20, ptrLV32, ptrLV33, nullptr, nullptr );
		ptrPV12 = new PressureActuatedValve( 0, 20, ptrLV34, ptrLV35, nullptr, nullptr );
		ptrPV13 = new PressureActuatedValve( 0, 100, ptrLV39, nullptr, nullptr, nullptr );
		ptrPV17 = new PressureActuatedValve( 0, 100, ptrLV72, nullptr, nullptr, nullptr );
		ptrPV18 = new PressureActuatedValve( 0, 100, ptrLV73, nullptr, nullptr, nullptr );
		ptrPV19 = new PressureActuatedValve( 1, 100, nullptr, ptrLV76, nullptr, nullptr );
		ptrPV20 = new PressureActuatedValve( 0, 100, nullptr, ptrLV77, nullptr, nullptr );
		ptrPV21 = new PressureActuatedValve( 0, 100, nullptr, ptrLV78, nullptr, nullptr );
		//ptrPV22 = new ValveTypeBool( false, 50 );// Normal closing response of the valve is less than 2 seconds (signal to switch).

		ptrPD1 = new PressureActuatedValve( 1, 50, ptrLV46, ptrLV47, nullptr, nullptr );
		ptrPD2 = new PressureActuatedValve( 1, 50, ptrLV48, ptrLV49, nullptr, nullptr );
		ptrPD3 = new PressureActuatedValve( 1, 50, ptrLV50, ptrLV51, nullptr, nullptr );

		LOXManifPress = 105;
		LH2ManifPress = 45;

		LOXinitpress = 36;
		LH2initpress = 33;

		LOXrepress = 0;

		GOXmass = 0;
		GH2mass = 0;

		RV5 = false;
		RV6 = false;

		ManifPress[0] = Sensor( 0, 300 );
		ManifPress[1] = Sensor( 0, 100 );
		return;
	}

	MPS::~MPS( void )
	{
		delete ptrLV12;
		delete ptrLV13;
		delete ptrLV14;
		delete ptrLV15;
		delete ptrLV16;
		delete ptrLV17;
		delete ptrLV18;
		delete ptrLV19;
		delete ptrLV20;
		delete ptrLV21;
		delete ptrLV22;
		delete ptrLV23;
		delete ptrLV24;
		delete ptrLV25;

		delete ptrLV28;
		delete ptrLV29;
		delete ptrLV30;
		delete ptrLV31;
		delete ptrLV32;
		delete ptrLV33;
		delete ptrLV34;
		delete ptrLV35;

		delete ptrLV39;
		delete ptrLV40;
		delete ptrLV41;
		delete ptrLV42;
		delete ptrLV43;

		delete ptrLV46;
		delete ptrLV47;
		delete ptrLV48;
		delete ptrLV49;
		delete ptrLV50;
		delete ptrLV51;

		delete ptrLV53;
		delete ptrLV54;
		delete ptrLV55;
		delete ptrLV56;
		delete ptrLV57;
		delete ptrLV58;

		delete ptrLV72;
		delete ptrLV73;

		delete ptrLV76;
		delete ptrLV77;
		delete ptrLV78;

		delete ptrLV80;
		delete ptrLV81;
		delete ptrLV82;
		delete ptrLV83;
		delete ptrLV84;
		delete ptrLV85;

		delete ptrPV1;
		delete ptrPV2;
		delete ptrPV3;
		delete ptrPV4;
		delete ptrPV5;
		delete ptrPV6;
		delete ptrPV7;
		delete ptrPV8;
		delete ptrPV9;
		delete ptrPV10;
		delete ptrPV11;
		delete ptrPV12;
		delete ptrPV13;
		delete ptrPV17;
		delete ptrPV18;
		delete ptrPV19;
		delete ptrPV20;
		delete ptrPV21;
		//delete ptrPV22;

		delete ptrPD1;
		delete ptrPD2;
		delete ptrPD3;
	}

	bool MPS::OnParseLine( const char* line )
	{
		return false;
	}

	void MPS::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	void MPS::Realize( void )
	{
		discsignals::DiscreteBundle* bundle = BundleManager()->CreateBundle( "MPS_LV_A", 16 );// LV1 - LV16
		//ptrLV1->Connect( 0, bundle, 0 );
		//ptrLV2->Connect( 0, bundle, 1 );
		//ptrLV3->Connect( 0, bundle, 2 );
		//ptrLV4->Connect( 0, bundle, 3 );
		//ptrLV5->Connect( 0, bundle, 4 );
		//ptrLV6->Connect( 0, bundle, 5 );
		//ptrLV7->Connect( 0, bundle, 6 );
		//ptrLV8->Connect( 0, bundle, 7 );
		//ptrLV9->Connect( 0, bundle, 8 );
		//ptrLV10->Connect( 0, bundle, 9 );
		//ptrLV11->Connect( 0, bundle, 10 );
		ptrLV12->Connect( 0, bundle, 11 );
		ptrLV13->Connect( 0, bundle, 12 );
		ptrLV14->Connect( 0, bundle, 13 );
		ptrLV15->Connect( 0, bundle, 14 );
		ptrLV16->Connect( 0, bundle, 15 );

		bundle = BundleManager()->CreateBundle( "MPS_LV_B", 16 );// LV17 - LV32
		ptrLV17->Connect( 0, bundle, 0 );
		ptrLV18->Connect( 0, bundle, 1 );
		ptrLV19->Connect( 0, bundle, 2 );
		ptrLV20->Connect( 0, bundle, 3 );
		ptrLV21->Connect( 0, bundle, 4 );
		ptrLV22->Connect( 0, bundle, 5 );
		ptrLV23->Connect( 0, bundle, 6 );
		ptrLV24->Connect( 0, bundle, 7 );
		ptrLV25->Connect( 0, bundle, 8 );
		//ptrLV26->Connect( 0, bundle, 9 );
		//ptrLV27->Connect( 0, bundle, 10 );
		ptrLV28->Connect( 0, bundle, 11 );
		ptrLV29->Connect( 0, bundle, 12 );
		ptrLV30->Connect( 0, bundle, 13 );
		ptrLV31->Connect( 0, bundle, 14 );
		ptrLV32->Connect( 0, bundle, 15 );

		bundle = BundleManager()->CreateBundle( "MPS_LV_C", 16 );// LV33 - LV48
		ptrLV33->Connect( 0, bundle, 0 );
		ptrLV34->Connect( 0, bundle, 1 );
		ptrLV35->Connect( 0, bundle, 2 );
		//ptrLV36->Connect( 0, bundle, 3 );
		//ptrLV37->Connect( 0, bundle, 4 );
		//ptrLV38->Connect( 0, bundle, 5 );
		ptrLV39->Connect( 0, bundle, 6 );
		ptrLV40->Connect( 0, bundle, 7 );
		ptrLV41->Connect( 0, bundle, 8 );
		ptrLV42->Connect( 0, bundle, 9 );
		ptrLV43->Connect( 0, bundle, 10 );
		//ptrLV44->Connect( 0, bundle, 11 );
		//ptrLV45->Connect( 0, bundle, 12 );
		ptrLV46->Connect( 0, bundle, 13 );
		ptrLV47->Connect( 0, bundle, 14 );
		ptrLV48->Connect( 0, bundle, 15 );

		bundle = BundleManager()->CreateBundle( "MPS_LV_D", 16 );// LV49 - LV64
		ptrLV49->Connect( 0, bundle, 0 );
		ptrLV50->Connect( 0, bundle, 1 );
		ptrLV51->Connect( 0, bundle, 2 );
		//ptrLV52->Connect( 0, bundle, 3 );
		ptrLV53->Connect( 0, bundle, 4 );
		ptrLV54->Connect( 0, bundle, 5 );
		ptrLV55->Connect( 0, bundle, 6 );
		ptrLV56->Connect( 0, bundle, 7 );
		ptrLV57->Connect( 0, bundle, 8 );
		ptrLV58->Connect( 0, bundle, 9 );
		//ptrLV59->Connect( 0, bundle, 10 );
		//ptrLV60->Connect( 0, bundle, 11 );
		//ptrLV61->Connect( 0, bundle, 12 );
		//ptrLV62->Connect( 0, bundle, 13 );
		//ptrLV63->Connect( 0, bundle, 14 );
		//ptrLV64->Connect( 0, bundle, 15 );

		bundle = BundleManager()->CreateBundle( "MPS_LV_E", 16 );// LV65 - LV80
		//ptrLV65->Connect( 0, bundle, 0 );
		//ptrLV66->Connect( 0, bundle, 1 );
		//ptrLV67->Connect( 0, bundle, 2 );
		//ptrLV68->Connect( 0, bundle, 3 );
		//ptrLV69->Connect( 0, bundle, 4 );
		//ptrLV70->Connect( 0, bundle, 5 );
		//ptrLV71->Connect( 0, bundle, 6 );
		ptrLV72->Connect( 0, bundle, 7 );
		ptrLV73->Connect( 0, bundle, 8 );
		//ptrLV74->Connect( 0, bundle, 9 );
		//ptrLV75->Connect( 0, bundle, 10 );
		ptrLV76->Connect( 0, bundle, 11 );
		ptrLV77->Connect( 0, bundle, 12 );
		ptrLV78->Connect( 0, bundle, 13 );
		//ptrLV79->Connect( 0, bundle, 14 );
		ptrLV80->Connect( 0, bundle, 15 );

		bundle = BundleManager()->CreateBundle( "MPS_LV_F", 16 );// LV81 - LV85
		ptrLV81->Connect( 0, bundle, 0 );
		ptrLV82->Connect( 0, bundle, 1 );
		ptrLV83->Connect( 0, bundle, 2 );
		ptrLV84->Connect( 0, bundle, 3 );
		ptrLV85->Connect( 0, bundle, 4 );


		// connect indications
		bundle = BundleManager()->CreateBundle( "MPS_CLInd_A", 16 );
		ptrPV19->ConnectIndication( false, 0, bundle, 8 );
		ptrPV19->ConnectIndication( false, 1, bundle, 9 );
		ptrPV20->ConnectIndication( false, 0, bundle, 10 );
		ptrPV21->ConnectIndication( false, 0, bundle, 11 );

		ptrPD1->ConnectIndication( false, 0, bundle, 13 );
		ptrPD1->ConnectIndication( false, 1, bundle, 14 );
		ptrPD2->ConnectIndication( false, 0, bundle, 15 );

		bundle = BundleManager()->CreateBundle( "MPS_CLInd_B", 16 );
		ptrPD2->ConnectIndication( false, 1, bundle, 0 );

		ptrPD3->ConnectIndication( false, 0, bundle, 7 );

		bundle = BundleManager()->CreateBundle( "MPS_OPInd_A", 16 );
		ptrPV4->ConnectIndication( true, 0, bundle, 3 );
		ptrPV4->ConnectIndication( true, 1, bundle, 4 );
		ptrPV5->ConnectIndication( true, 0, bundle, 5 );
		ptrPV5->ConnectIndication( true, 1, bundle, 6 );
		ptrPV6->ConnectIndication( true, 0, bundle, 7 );
		ptrPV6->ConnectIndication( true, 1, bundle, 8 );

		ptrPV20->ConnectIndication( true, 0, bundle, 15 );

		bundle = BundleManager()->CreateBundle( "MPS_OPInd_B", 16 );
		ptrPV21->ConnectIndication( true, 0, bundle, 0 );

		bundle = BundleManager()->CreateBundle( "MPS_SENSORS", 2 );
		ManifPress[0].Connect( bundle, 0 );
		ManifPress[1].Connect( bundle, 1 );

		if (STS()->Get_status() == 3)
		{
			ptrPD1->_backdoor( 0 );
			ptrPD2->_backdoor( 0 );
			ptrPD3->_backdoor( 0 );

			ptrLV46->_backdoor( 0 );
			ptrLV47->_backdoor( 0 );
			ptrLV48->_backdoor( 0 );
			ptrLV49->_backdoor( 0 );
			ptrLV50->_backdoor( 0 );
			ptrLV51->_backdoor( 0 );
		}
		return;
	}

	void MPS::OnPostStep( double simt, double simdt, double mjd )
	{
		ptrLV12->tmestp( simdt );
		ptrLV13->tmestp( simdt );
		ptrLV14->tmestp( simdt );
		ptrLV15->tmestp( simdt );
		ptrLV16->tmestp( simdt );
		ptrLV17->tmestp( simdt );
		ptrLV18->tmestp( simdt );
		ptrLV19->tmestp( simdt );
		ptrLV20->tmestp( simdt );
		ptrLV21->tmestp( simdt );
		ptrLV22->tmestp( simdt );
		ptrLV23->tmestp( simdt );
		ptrLV24->tmestp( simdt );
		ptrLV25->tmestp( simdt );

		ptrLV28->tmestp( simdt );
		ptrLV29->tmestp( simdt );
		ptrLV30->tmestp( simdt );
		ptrLV31->tmestp( simdt );
		ptrLV32->tmestp( simdt );
		ptrLV33->tmestp( simdt );
		ptrLV34->tmestp( simdt );
		ptrLV35->tmestp( simdt );

		ptrLV39->tmestp( simdt );
		ptrLV40->tmestp( simdt );
		ptrLV41->tmestp( simdt );
		ptrLV42->tmestp( simdt );
		ptrLV43->tmestp( simdt );

		ptrLV46->tmestp( simdt );
		ptrLV47->tmestp( simdt );
		ptrLV48->tmestp( simdt );
		ptrLV49->tmestp( simdt );
		ptrLV50->tmestp( simdt );
		ptrLV51->tmestp( simdt );

		ptrLV53->tmestp( simdt );
		ptrLV54->tmestp( simdt );
		ptrLV55->tmestp( simdt );
		ptrLV56->tmestp( simdt );
		ptrLV57->tmestp( simdt );
		ptrLV58->tmestp( simdt );

		ptrLV72->tmestp( simdt );
		ptrLV73->tmestp( simdt );

		ptrLV76->tmestp( simdt );
		ptrLV77->tmestp( simdt );
		ptrLV78->tmestp( simdt );

		ptrLV80->tmestp( simdt );
		ptrLV81->tmestp( simdt );
		ptrLV82->tmestp( simdt );
		ptrLV83->tmestp( simdt );
		ptrLV84->tmestp( simdt );
		ptrLV85->tmestp( simdt );

		ptrPV1->tmestp( simdt );
		ptrPV2->tmestp( simdt );
		ptrPV3->tmestp( simdt );
		ptrPV4->tmestp( simdt );
		ptrPV5->tmestp( simdt );
		ptrPV6->tmestp( simdt );
		ptrPV7->tmestp( simdt );
		ptrPV8->tmestp( simdt );
		ptrPV9->tmestp( simdt );
		ptrPV10->tmestp( simdt );
		ptrPV11->tmestp( simdt );
		ptrPV12->tmestp( simdt );
		ptrPV13->tmestp( simdt );
		ptrPV17->tmestp( simdt );
		ptrPV18->tmestp( simdt );
		ptrPV19->tmestp( simdt );
		ptrPV20->tmestp( simdt );
		ptrPV21->tmestp( simdt );
		//ptrPV22->tmestp( simdt );

		ptrPD1->tmestp( simdt );
		ptrPD2->tmestp( simdt );
		ptrPD3->tmestp( simdt );

		STS()->ETPressurization( GOXmass, GH2mass );
		// reset masses
		GOXmass = 0;
		GH2mass = 0;

		double LOXTankLevel = 0;
		double LH2TankLevel = 0;

		if (ptrPD1->GetPos() > 0)// HACK should be one for each LOX and LH2
		{
			STS()->UpdateMPSManifold();

			// ET
			LOXTankLevel = STS()->GetETPropellant_B() / 100;
			LH2TankLevel = LOXTankLevel;

			constexpr double LOXFeedlineHeight = 31.6742;
			constexpr double LOXFeedlineVol = 3.1415 * LOXFeedlineHeight * (17.0 * 0.5 * IN2M) * (17.0 * 0.5 * IN2M);
			constexpr double LOXCylHeight = 6.8375;
			constexpr double LOXCylVol = 378.9194;
			constexpr double LH2Density = 70.85;// Kg/m^3
			constexpr double LOXDensity = 1141;// Kg/m^3
			double LH2UllagePress = STS()->GetETLH2UllagePressure();//289579.8;// Pa
			double LOXUllagePress = STS()->GetETLOXUllagePressure();//246142.8;// Pa
			double LH2Height = 0 + (((LH2TankLevel * 104463.23) / LH2Density) / 55.4177);// m
			double LOXHeight = 0;// m (42.7m at pre-press)
			double LOXvol = (LOXTankLevel * 624252.0) / LOXDensity;
			if (LOXvol > (LOXFeedlineVol + LOXCylVol))
			{
				// feedline + cyl + cone
				LOXvol -= (LOXFeedlineVol + LOXCylVol);
				LOXHeight = LOXFeedlineHeight + LOXCylHeight + (13.6536 - pow( ((252.217 - LOXvol) * 31.7051) / 3.1416, 1/3. ));
			}
			else if (LOXvol > LOXFeedlineVol)
			{
				// feedline + cyl
				LOXvol -= LOXFeedlineVol;
				LOXHeight = LOXFeedlineHeight + (LOXvol / 55.4177);
			}
			else
			{
				// feedline
				LOXHeight = LOXvol / (3.1415 * (17.0 * 0.5 * IN2M) * (17.0 * 0.5 * IN2M));
			}

			double acc = 9.80665;
			if (STS()->GroundContact() == false)
			{
				VECTOR3 tv;
				if (STS()->GetThrustVector( tv ))
				{
					VECTOR3 forceV3;
					VECTOR3 accV3;
					STS()->GetForceVector( forceV3 );
					accV3 = forceV3 / STS()->GetMass();
					acc = accV3.z;
					acc += 9.80665 * sin( STS()->GetPitch() );
				}
				else acc = 0;
			}

			// ET
			LH2ManifPress = (LH2UllagePress + (LH2Density * acc * LH2Height)) / 6894.757;// psia
			LOXManifPress = (LOXUllagePress + (LOXDensity * acc * LOXHeight)) / 6894.757;// psia

			// use full vent thrust on all
			STS()->SetMPSDumpLevel( 3, ptrPV17->GetPos() * ptrPV18->GetPos() );
			STS()->SetMPSDumpLevel( 4, ptrPV11->GetPos() * (ptrPV12->GetPos() * 0.3 + ptrPV13->GetPos() * 0.7) );
			STS()->SetMPSDumpLevel( 5, ptrPV9->GetPos() * ptrPV10->GetPos() );
			// ********** ad-hoc RV6 **********
			if (RV6 == false)
			{
				// closed, check if press > crack press (55psig -> 69.7psia)
				if (LH2ManifPress > 69.7) RV6 = true;// open
			}
			else
			{
				// open, check press < reseat press (40psig -> 54.7psia)
				if (LH2ManifPress < 54.7) RV6 = false;// close
			}
			// ********************************
			STS()->SetMPSDumpLevel( 6, ptrPV8->GetPos() * (int)RV6 );

			// ********** ad-hoc RV5 **********
			if (RV5 == false)
			{
				// closed, check if press > crack press (220psig -> 234.7psia)
				if (LOXManifPress > 234.7) RV5 = true;// open
			}
			else
			{
				// open, check press < reseat press (190psig -> 204.7psia)
				if (LOXManifPress < 204.7) RV5 = false;// close
			}
			// ********************************
			STS()->SetMPSDumpLevel( 7, ptrPV7->GetPos() * (int)RV5 );
		}
		else
		{
			// manifold
			PROPELLANT_HANDLE ph = STS()->GetLOXTank();
			if (ph == NULL) LOXTankLevel = 0;
			else LOXTankLevel = STS()->GetPropellantLevel( ph ) / 100;

			ph = STS()->GetLH2Tank();
			if (ph == NULL) LH2TankLevel = 0;
			else LH2TankLevel = STS()->GetPropellantLevel( ph ) / 100;

			// TODO use ideal gas here for temp increase?
			LOXinitpress += 0.4 * simdt * LOXTankLevel;// pressure rises due to heat soak back
			LH2initpress += 1 * simdt * LH2TankLevel;// pressure rises due to heat soak back (STS-1 data: ~1 psi/sec)
			LOXManifPress = LOXinitpress * LOXTankLevel;
			LH2ManifPress = LH2initpress * LH2TankLevel;


			//ptrLV43->Use( 1000 * simdt );

			// HACK totally madeup numbers for pressurized LOX dump (not enough info)
			double LOXrepress_temp = ptrLV41->Use( 0.0, 0 );// check press
			if (LOXrepress_temp > 0)
			{
				if (LOXrepress_temp > 37) LOXrepress_temp = 37;// conflicting reports if 20-25psia or psig... using psig
				if (LOXrepress_temp > LOXManifPress)
				{
					LOXrepress_temp = (LOXrepress_temp - LOXManifPress) / 37;
					ptrLV41->Use( 1000 * simdt * LOXrepress_temp, 0 );
					LOXrepress += 10 * simdt * LOXrepress_temp;
				}
			}
			LOXManifPress += LOXTankLevel * LOXrepress;

			// use "normalized" manifold press to control vent thrust
			double LOXventlevel = LOXManifPress / 80;
			LOXventlevel = min( LOXventlevel * LOXventlevel, 1 );
			double LH2ventlevel = LH2ManifPress / 35;
			LH2ventlevel = min( pow( LH2ventlevel, 5 ), 1 );

			// so it doesn't take forever to empty
			if (LOXventlevel < 0.05) LOXventlevel = 0.05;
			if (LH2ventlevel < 0.05) LH2ventlevel = 0.05;

			STS()->SetMPSDumpLevel( 3, ptrPV17->GetPos() * ptrPV18->GetPos() * LH2ventlevel );
			STS()->SetMPSDumpLevel( 4, ptrPV11->GetPos() * (ptrPV12->GetPos() * 0.05 + ptrPV13->GetPos() * 0.95) * LH2ventlevel );
			STS()->SetMPSDumpLevel( 5, ptrPV9->GetPos() * ptrPV10->GetPos() * LOXventlevel );

			// ********** ad-hoc RV6 **********
			if (RV6 == false)
			{
				// closed, check if press > crack press (55psig -> 69.7psia)
				if (LH2ManifPress > 69.7) RV6 = true;// open
			}
			else
			{
				// open, check press < reseat press (40psig -> 54.7psia)
				if (LH2ManifPress < 54.7) RV6 = false;// close
			}
			// ********************************
			STS()->SetMPSDumpLevel( 6, ptrPV8->GetPos() * LH2ventlevel * (int)RV6 );

			// ********** ad-hoc RV5 **********
			if (RV5 == false)
			{
				// closed, check if press > crack press (220psig -> 234.7psia)
				if (LOXManifPress > 234.7) RV5 = true;// open
			}
			else
			{
				// open, check press < reseat press (190psig -> 204.7psia)
				if (LOXManifPress < 204.7) RV5 = false;// close
			}
			// ********************************
			STS()->SetMPSDumpLevel( 7, ptrPV7->GetPos() * LOXventlevel * (int)RV5 );
		}

		ManifPress[0].SetValue( LOXManifPress );
		ManifPress[1].SetValue( LH2ManifPress );

		//char buffer[100];
		//sprintf_s( buffer, 100, "%f,%f,%f,%f,%f", STS()->GetMET(), LH2initpress, LH2ManifPress, LH2ventlevel, STS()->GetPropellantLevel( STS()->GetLH2Tank() ) );
		//sprintf_s( buffer, 100, "%f,%f,%f,%f,%f,%f",  ptrLV53->GetPos(), ptrLV54->GetPos(), ptrLV55->GetPos(), ptrLV56->GetPos(), ptrLV57->GetPos(), ptrLV58->GetPos() );
		//oapiWriteLog( buffer );
		//sprintf_s( oapiDebugString(), 256, buffer );
		//sprintf_s( buffer, 100, "PV4 %f LV18 %f LV19 %f", ptrPV4->GetPos(), ptrLV18->GetPos(), ptrLV19->GetPos() );
		//oapiWriteLog( buffer );
		return;
	}

	double MPS::GetLOXManifPress( void ) const
	{
		return LOXManifPress;
	}

	double MPS::GetLH2ManifPress( void ) const
	{
		return LH2ManifPress;
	}

	double MPS::GetLOXPVPos( int eng ) const
	{
		assert( (eng >= 1) && (eng <= 3) && "MPS::GetLOXPVPos.eng" );
		if (eng == 1) return ptrPV1->GetPos();
		else if (eng == 2) return ptrPV2->GetPos();
		return ptrPV3->GetPos();
	}

	double MPS::GetLH2PVPos( int eng ) const
	{
		assert( (eng >= 1) && (eng <= 3) && "MPS::GetLH2PVPos.eng" );
		if (eng == 1) return ptrPV4->GetPos();
		else if (eng == 2) return ptrPV5->GetPos();
		return ptrPV6->GetPos();
	}

	void MPS::PressurantFlow( int eng, double GOXmass, double GH2mass )
	{
		assert( (eng >= 1) && (eng <= 3) && "MPS::PressurantFlow.eng" );
		// INFO "current" GOX FCVs are fixed at 78% since STS-40 (eventually disconnected/removed?)
		// original: 100%-42%, step I: 93%-55% ?, step II: 85%-66% ?, step III: 78%
		// HACK using step I config as current ullage implementation is not good enough for step III
		// INFO GH2 FCVs are limited from 70% to 31% from the mid-1990s (was 100% to 18%)
		switch (eng)
		{
			case 1:
				this->GOXmass += GOXmass * range( 0.55, ptrLV53->GetPos(), 0.93 );
				this->GH2mass += GH2mass * range( 0.31, ptrLV56->GetPos(), 0.7 );
				break;
			case 2:
				this->GOXmass += GOXmass * range( 0.55, ptrLV54->GetPos(), 0.93 );
				this->GH2mass += GH2mass * range( 0.31, ptrLV57->GetPos(), 0.7 );
				break;
			case 3:
				this->GOXmass += GOXmass * range( 0.55, ptrLV55->GetPos(), 0.93 );
				this->GH2mass += GH2mass * range( 0.31, ptrLV58->GetPos(), 0.7 );
				break;
		}
		return;
	}
}
#include "RJD.h"
#include "..\Atlantis.h"
#include <assert.h>


namespace rcs
{
	RJD::RJD( AtlantisSubsystemDirector* _director, const string& _ident, unsigned short ID ):AtlantisSubsystem( _director, _ident )
	{
		assert( (ID <= 3) && "RJD::RJD:ID" );
		this->ID = ID;

		unsigned short jetsA = 0;
		unsigned short jetsB = 0;
		switch (ID)
		{
			case 0:// RJDF-1
				jetsA = 4;// RJDF-1A
				jetsB = 4;// RJDF-1B
				break;
			case 1:// RJDF-2
				jetsA = 4;// RJDF-2A
				jetsB = 4;// RJDF-2B
				break;
			case 2:// RJDA-1
				jetsA = 6;// RJDA-1A
				jetsB = 8;// RJDA-1B
				break;
			case 3:// RJDA-2
				jetsA = 6;// RJDA-2A
				jetsB = 8;// RJDA-2B
				break;
		}
		sideA = new RJD_side( jetsA );
		sideB = new RJD_side( jetsB );
		return;
	}

	RJD::~RJD( void )
	{
		delete sideA;
		delete sideB;
	}

	void RJD::Realize( void )
	{
		// TODO power

		// from MDM
		DiscreteBundle* CMD_A_bundle_FRCS;
		DiscreteBundle* CMD_A_bundle_LRCS;
		DiscreteBundle* CMD_A_bundle_RRCS;
		DiscreteBundle* CMD_B_bundle_FRCS;
		DiscreteBundle* CMD_B_bundle_LRCS;
		DiscreteBundle* CMD_B_bundle_RRCS;

		// to MDM
		DiscreteBundle* PC_evt_bundle_FRCS;
		DiscreteBundle* PC_evt_bundle_LRCS;
		DiscreteBundle* PC_evt_bundle_RRCS;

		// to RCS/MDM
		DiscreteBundle* Driver_bundle_FRCS;
		DiscreteBundle* Driver_bundle_LRCS;
		DiscreteBundle* Driver_bundle_RRCS;

		// from RCS
		DiscreteBundle* PC_bundle_FRCS;
		DiscreteBundle* PC_bundle_LRCS;
		DiscreteBundle* PC_bundle_RRCS;

		switch (ID)
		{
			case 0:// RJDF-1
				CMD_A_bundle_FRCS = BundleManager()->CreateBundle( "RCS_CMD_A_FRCS", 16 );
				CMD_B_bundle_FRCS = BundleManager()->CreateBundle( "RCS_CMD_B_FRCS", 16 );
				PC_evt_bundle_FRCS = BundleManager()->CreateBundle( "RCS_PC_EVT_FRCS", 16 );
				Driver_bundle_FRCS = BundleManager()->CreateBundle( "RCS_DRIVER_FRCS", 16 );
				PC_bundle_FRCS = BundleManager()->CreateBundle( "RCS_PC_FRCS", 16 );

				// RJDF-1A
				sideA->ConnectJet( 0, CMD_A_bundle_FRCS, 0, CMD_B_bundle_FRCS, 0, PC_evt_bundle_FRCS, 0, PC_bundle_FRCS, 0, Driver_bundle_FRCS, 0 );// F2F
				sideA->ConnectJet( 1, CMD_A_bundle_FRCS, 5, CMD_B_bundle_FRCS, 5, PC_evt_bundle_FRCS, 5, PC_bundle_FRCS, 5, Driver_bundle_FRCS, 5 );// F2R
				sideA->ConnectJet( 2, CMD_A_bundle_FRCS, 7, CMD_B_bundle_FRCS, 7, PC_evt_bundle_FRCS, 7, PC_bundle_FRCS, 7, Driver_bundle_FRCS, 7 );// F2U
				sideA->ConnectJet( 3, CMD_A_bundle_FRCS, 10, CMD_B_bundle_FRCS, 10, PC_evt_bundle_FRCS, 10, PC_bundle_FRCS, 10, Driver_bundle_FRCS, 10 );// F2D
				
				// RJDF-1B
				sideB->ConnectJet( 0, CMD_A_bundle_FRCS, 2, CMD_B_bundle_FRCS, 2, PC_evt_bundle_FRCS, 2, PC_bundle_FRCS, 2, Driver_bundle_FRCS, 2 );// F1F
				sideB->ConnectJet( 1, CMD_A_bundle_FRCS, 3, CMD_B_bundle_FRCS, 3, PC_evt_bundle_FRCS, 3, PC_bundle_FRCS, 3, Driver_bundle_FRCS, 3 );// F1L
				sideB->ConnectJet( 2, CMD_A_bundle_FRCS, 9, CMD_B_bundle_FRCS, 9, PC_evt_bundle_FRCS, 9, PC_bundle_FRCS, 9, Driver_bundle_FRCS, 9 );// F1U
				sideB->ConnectJet( 3, CMD_A_bundle_FRCS, 11, CMD_B_bundle_FRCS, 11, PC_evt_bundle_FRCS, 11, PC_bundle_FRCS, 11, Driver_bundle_FRCS, 11 );// F1D
				break;
			case 1:// RJDF-2
				CMD_A_bundle_FRCS = BundleManager()->CreateBundle( "RCS_CMD_A_FRCS", 16 );
				CMD_B_bundle_FRCS = BundleManager()->CreateBundle( "RCS_CMD_B_FRCS", 16 );
				PC_evt_bundle_FRCS = BundleManager()->CreateBundle( "RCS_PC_EVT_FRCS", 16 );
				Driver_bundle_FRCS = BundleManager()->CreateBundle( "RCS_DRIVER_FRCS", 16 );
				PC_bundle_FRCS = BundleManager()->CreateBundle( "RCS_PC_FRCS", 16 );

				// RJDF-2A
				sideA->ConnectJet( 0, CMD_A_bundle_FRCS, 1, CMD_B_bundle_FRCS, 1, PC_evt_bundle_FRCS, 1, PC_bundle_FRCS, 1, Driver_bundle_FRCS, 1 );// F3F
				sideA->ConnectJet( 1, CMD_A_bundle_FRCS, 4, CMD_B_bundle_FRCS, 4, PC_evt_bundle_FRCS, 4, PC_bundle_FRCS, 4, Driver_bundle_FRCS, 4 );// F3L
				sideA->ConnectJet( 2, CMD_A_bundle_FRCS, 8, CMD_B_bundle_FRCS, 8, PC_evt_bundle_FRCS, 8, PC_bundle_FRCS, 8, Driver_bundle_FRCS, 8 );// F3U
				sideA->ConnectJet( 3, CMD_A_bundle_FRCS, 13, CMD_B_bundle_FRCS, 13, PC_evt_bundle_FRCS, 13, PC_bundle_FRCS, 13, Driver_bundle_FRCS, 13 );// F3D
				
				// RJDF-2B
				sideB->ConnectJet( 0, CMD_A_bundle_FRCS, 6, CMD_B_bundle_FRCS, 6, PC_evt_bundle_FRCS, 6, PC_bundle_FRCS, 6, Driver_bundle_FRCS, 6 );// F4R
				sideB->ConnectJet( 1, CMD_A_bundle_FRCS, 12, CMD_B_bundle_FRCS, 12, PC_evt_bundle_FRCS, 12, PC_bundle_FRCS, 12, Driver_bundle_FRCS, 12 );// F4D
				sideB->ConnectJet( 2, CMD_A_bundle_FRCS, 15, CMD_B_bundle_FRCS, 15, PC_evt_bundle_FRCS, 15, PC_bundle_FRCS, 15, Driver_bundle_FRCS, 15 );// F5L
				sideB->ConnectJet( 3, CMD_A_bundle_FRCS, 14, CMD_B_bundle_FRCS, 14, PC_evt_bundle_FRCS, 14, PC_bundle_FRCS, 14, Driver_bundle_FRCS, 14 );// F5R
				break;
			case 2:// RJDA-1
				CMD_A_bundle_LRCS = BundleManager()->CreateBundle( "RCS_CMD_A_LRCS", 14 );
				CMD_A_bundle_RRCS = BundleManager()->CreateBundle( "RCS_CMD_A_RRCS", 14 );
				CMD_B_bundle_LRCS = BundleManager()->CreateBundle( "RCS_CMD_B_LRCS", 14 );
				CMD_B_bundle_RRCS = BundleManager()->CreateBundle( "RCS_CMD_B_RRCS", 14 );
				PC_evt_bundle_LRCS = BundleManager()->CreateBundle( "RCS_PC_EVT_LRCS", 14 );
				PC_evt_bundle_RRCS = BundleManager()->CreateBundle( "RCS_PC_EVT_RRCS", 14 );
				Driver_bundle_LRCS = BundleManager()->CreateBundle( "RCS_DRIVER_LRCS", 14 );
				Driver_bundle_RRCS = BundleManager()->CreateBundle( "RCS_DRIVER_RRCS", 14 );
				PC_bundle_LRCS = BundleManager()->CreateBundle( "RCS_PC_LRCS", 14 );
				PC_bundle_RRCS = BundleManager()->CreateBundle( "RCS_PC_RRCS", 14 );

				// RJDA-1A
				sideA->ConnectJet( 0, CMD_A_bundle_LRCS, 3, CMD_B_bundle_LRCS, 3, PC_evt_bundle_LRCS, 3, PC_bundle_LRCS, 3, Driver_bundle_LRCS, 3 );// L2L
				sideA->ConnectJet( 1, CMD_A_bundle_LRCS, 7, CMD_B_bundle_LRCS, 7, PC_evt_bundle_LRCS, 7, PC_bundle_LRCS, 7, Driver_bundle_LRCS, 7 );// L2U
				sideA->ConnectJet( 2, CMD_A_bundle_LRCS, 10, CMD_B_bundle_LRCS, 10, PC_evt_bundle_LRCS, 10, PC_bundle_LRCS, 10, Driver_bundle_LRCS, 10 );// L2D
				sideA->ConnectJet( 3, CMD_A_bundle_RRCS, 3, CMD_B_bundle_RRCS, 3, PC_evt_bundle_RRCS, 3, PC_bundle_RRCS, 3, Driver_bundle_RRCS, 3 );// R2R
				sideA->ConnectJet( 4, CMD_A_bundle_RRCS, 7, CMD_B_bundle_RRCS, 7, PC_evt_bundle_RRCS, 7, PC_bundle_RRCS, 7, Driver_bundle_RRCS, 7 );// R2U
				sideA->ConnectJet( 5, CMD_A_bundle_RRCS, 10, CMD_B_bundle_RRCS, 10, PC_evt_bundle_RRCS, 10, PC_bundle_RRCS, 10, Driver_bundle_RRCS, 10 );// R2D
				
				// RJDA-1B
				sideB->ConnectJet( 0, CMD_A_bundle_LRCS, 1, CMD_B_bundle_LRCS, 1, PC_evt_bundle_LRCS, 1, PC_bundle_LRCS, 1, Driver_bundle_LRCS, 1 );// L1A
				sideB->ConnectJet( 1, CMD_A_bundle_LRCS, 5, CMD_B_bundle_LRCS, 5, PC_evt_bundle_LRCS, 5, PC_bundle_LRCS, 5, Driver_bundle_LRCS, 5 );// L1L
				sideB->ConnectJet( 2, CMD_A_bundle_LRCS, 8, CMD_B_bundle_LRCS, 8, PC_evt_bundle_LRCS, 8, PC_bundle_LRCS, 8, Driver_bundle_LRCS, 8 );// L1U
				sideB->ConnectJet( 3, CMD_A_bundle_RRCS, 1, CMD_B_bundle_RRCS, 1, PC_evt_bundle_RRCS, 1, PC_bundle_RRCS, 1, Driver_bundle_RRCS, 1 );// R1A
				sideB->ConnectJet( 4, CMD_A_bundle_RRCS, 5, CMD_B_bundle_RRCS, 5, PC_evt_bundle_RRCS, 5, PC_bundle_RRCS, 5, Driver_bundle_RRCS, 5 );// R1R
				sideB->ConnectJet( 5, CMD_A_bundle_RRCS, 8, CMD_B_bundle_RRCS, 8, PC_evt_bundle_RRCS, 8, PC_bundle_RRCS, 8, Driver_bundle_RRCS, 8 );// R1U
				sideB->ConnectJet( 6, CMD_A_bundle_LRCS, 13, CMD_B_bundle_LRCS, 13, PC_evt_bundle_LRCS, 13, PC_bundle_LRCS, 13, Driver_bundle_LRCS, 13 );// L5L
				sideB->ConnectJet( 7, CMD_A_bundle_LRCS, 12, CMD_B_bundle_LRCS, 12, PC_evt_bundle_LRCS, 12, PC_bundle_LRCS, 12, Driver_bundle_LRCS, 12 );// L5D
				break;
			case 3:// RJDA-2
				CMD_A_bundle_LRCS = BundleManager()->CreateBundle( "RCS_CMD_A_LRCS", 14 );
				CMD_A_bundle_RRCS = BundleManager()->CreateBundle( "RCS_CMD_A_RRCS", 14 );
				CMD_B_bundle_LRCS = BundleManager()->CreateBundle( "RCS_CMD_B_LRCS", 14 );
				CMD_B_bundle_RRCS = BundleManager()->CreateBundle( "RCS_CMD_B_RRCS", 14 );
				PC_evt_bundle_LRCS = BundleManager()->CreateBundle( "RCS_PC_EVT_LRCS", 14 );
				PC_evt_bundle_RRCS = BundleManager()->CreateBundle( "RCS_PC_EVT_RRCS", 14 );
				Driver_bundle_LRCS = BundleManager()->CreateBundle( "RCS_DRIVER_LRCS", 14 );
				Driver_bundle_RRCS = BundleManager()->CreateBundle( "RCS_DRIVER_RRCS", 14 );
				PC_bundle_LRCS = BundleManager()->CreateBundle( "RCS_PC_LRCS", 14 );
				PC_bundle_RRCS = BundleManager()->CreateBundle( "RCS_PC_RRCS", 14 );

				// RJDA-2A
				sideA->ConnectJet( 0, CMD_A_bundle_LRCS, 2, CMD_B_bundle_LRCS, 2, PC_evt_bundle_LRCS, 2, PC_bundle_LRCS, 2, Driver_bundle_LRCS, 2 );// L4L
				sideA->ConnectJet( 1, CMD_A_bundle_LRCS, 6, CMD_B_bundle_LRCS, 6, PC_evt_bundle_LRCS, 6, PC_bundle_LRCS, 6, Driver_bundle_LRCS, 6 );// L4U
				sideA->ConnectJet( 2, CMD_A_bundle_LRCS, 9, CMD_B_bundle_LRCS, 9, PC_evt_bundle_LRCS, 9, PC_bundle_LRCS, 9, Driver_bundle_LRCS, 9 );// L4D
				sideA->ConnectJet( 3, CMD_A_bundle_RRCS, 2, CMD_B_bundle_RRCS, 2, PC_evt_bundle_RRCS, 2, PC_bundle_RRCS, 2, Driver_bundle_RRCS, 2 );// R4R
				sideA->ConnectJet( 4, CMD_A_bundle_RRCS, 6, CMD_B_bundle_RRCS, 6, PC_evt_bundle_RRCS, 6, PC_bundle_RRCS, 6, Driver_bundle_RRCS, 6 );// R4U
				sideA->ConnectJet( 5, CMD_A_bundle_RRCS, 9, CMD_B_bundle_RRCS, 9, PC_evt_bundle_RRCS, 9, PC_bundle_RRCS, 9, Driver_bundle_RRCS, 9 );// R4D
				
				// RJDA-2B
				sideB->ConnectJet( 0, CMD_A_bundle_LRCS, 0, CMD_B_bundle_LRCS, 0, PC_evt_bundle_LRCS, 0, PC_bundle_LRCS, 0, Driver_bundle_LRCS, 0 );// L3A
				sideB->ConnectJet( 1, CMD_A_bundle_LRCS, 4, CMD_B_bundle_LRCS, 4, PC_evt_bundle_LRCS, 4, PC_bundle_LRCS, 4, Driver_bundle_LRCS, 4 );// L3L
				sideB->ConnectJet( 2, CMD_A_bundle_LRCS, 11, CMD_B_bundle_LRCS, 11, PC_evt_bundle_LRCS, 11, PC_bundle_LRCS, 11, Driver_bundle_LRCS, 11 );// L3D
				sideB->ConnectJet( 3, CMD_A_bundle_RRCS, 0, CMD_B_bundle_RRCS, 0, PC_evt_bundle_RRCS, 0, PC_bundle_RRCS, 0, Driver_bundle_RRCS, 0 );// R3A
				sideB->ConnectJet( 4, CMD_A_bundle_RRCS, 4, CMD_B_bundle_RRCS, 4, PC_evt_bundle_RRCS, 4, PC_bundle_RRCS, 4, Driver_bundle_RRCS, 4 );// R3R
				sideB->ConnectJet( 5, CMD_A_bundle_RRCS, 11, CMD_B_bundle_RRCS, 11, PC_evt_bundle_RRCS, 11, PC_bundle_RRCS, 11, Driver_bundle_RRCS, 11 );// R3D
				sideB->ConnectJet( 6, CMD_A_bundle_RRCS, 13, CMD_B_bundle_RRCS, 13, PC_evt_bundle_RRCS, 13, PC_bundle_RRCS, 13, Driver_bundle_RRCS, 13 );// R5R
				sideB->ConnectJet( 7, CMD_A_bundle_RRCS, 12, CMD_B_bundle_RRCS, 12, PC_evt_bundle_RRCS, 12, PC_bundle_RRCS, 12, Driver_bundle_RRCS, 12 );// R5D
				break;
		}
		return;
	}

	void RJD::OnPreStep( double fSimT, double fDeltaT, double fMJD )
	{
		sideA->OnPreStep( fSimT, fDeltaT );
		sideB->OnPreStep( fSimT, fDeltaT );
		return;
	}


	RJD_side::RJD_side( unsigned short jets )
	{
		this->jets = jets;
		
		for (int i = 0; i < jets; i++)
		{
			PC_output.push_back( 0.0 );
			CMD_A.push_back( DiscInPort() );
			CMD_B.push_back( DiscInPort() );
			PC_Ind.push_back( DiscInPort() );
			PC_Evt.push_back( DiscOutPort() );
			Driver.push_back( DiscOutPort() );
		}
		return;
	}

	RJD_side::~RJD_side( void )
	{
		return;
	}

	void RJD_side::ConnectJet( unsigned short jet, DiscreteBundle* CMD_A_bundle, unsigned int CMD_A_line, DiscreteBundle* CMD_B_bundle, unsigned int CMD_B_line, DiscreteBundle* PC_Evt_bundle, unsigned int PC_Evt_line, DiscreteBundle* PC_Ind_bundle, unsigned int PC_Ind_line, DiscreteBundle* Driver_bundle, unsigned int Driver_line )
	{
		CMD_A.at( jet ).Connect( CMD_A_bundle, CMD_A_line );
		CMD_B.at( jet ).Connect( CMD_B_bundle, CMD_B_line );
		PC_Ind.at( jet ).Connect( PC_Ind_bundle, PC_Ind_line );
		PC_Evt.at( jet ).Connect( PC_Evt_bundle, PC_Evt_line );
		Driver.at( jet ).Connect( Driver_bundle, Driver_line );
		return;
	}

	void RJD_side::OnPreStep( double fSimT, double fDeltaT )
	{
		// TODO power

		double PC = 0.0;// [v]

		for (int i = 0; i < jets; i++)
		{
			// jet cmd logic / jet driver
			if (CMD_A.at( i ).IsSet() && CMD_B.at( i ).IsSet()) Driver.at( i ).SetLine();
			else Driver.at( i ).ResetLine();

			// jet receiver level detector
			// TODO pulse stretcher
			PC = PC_Ind.at( i ).GetVoltage();
			
			if (PC >= ((36.0 / 200.0) * 5.11)) PC_output.at( i ) = 15.0;
			else if (PC <= ((26.0 / 200.0) * 5.11)) PC_output.at( i ) = 0.0;
			
			PC_Evt.at( i ).SetLine( static_cast<float>(PC_output.at( i )) );
		}
		return;
	}
}

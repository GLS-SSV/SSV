#include "LPS_Interface.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"


namespace dps
{
	constexpr unsigned short ADDR = 17;


	LPS_Interface::LPS_Interface( AtlantisSubsystemDirector* _director, BusManager* pBusManager ):AtlantisSubsystem( _director, "LPS_Interface" ), BusTerminal( pBusManager ),
		id(0), hasdata(false),
		GMTLO(-1),
		LPSGoForAutoSequenceStart(false),
		LPSGoForEngineStart(false),
		GMTLOSetCommand(false),
		ResumeCountCommand(false),
		LPSCountdownHold(false),
		RecycleCountCmd(false),
		MPS_Slew(false),
		Aero_Slew(false),
		SRB_Slew(false),
		RSCountdownHold(false),
		LaunchSequenceAbort(false),
		HoldFlags(false)
	{
		BusConnect( BUS_LB1 );
		BusConnect( BUS_LB2 );
		return;
	}

	LPS_Interface::~LPS_Interface()
	{
		return;
	}

	void LPS_Interface::Rx( const BUS_ID id, void* data, const unsigned short datalen )
	{
		unsigned int* rcvd = static_cast<unsigned int*>(data);

		//// process command word
		{
			// check address
			int dataaddr = (rcvd[0] >> 20) & 0b11111;
			if (ADDR != dataaddr) return;
		}

		// check parity
		if (CalcParity( rcvd[0] ) == 0) return;

		unsigned char wdcount = (rcvd[0] >> 1) & 0b11111;// data words
		unsigned char modecontrol = (rcvd[0] >> 15) & 0b1111;

		switch (modecontrol)
		{
			case 0b0110:/// Interrogate Without GPC Data/Interrogate With GPC Data/Go Ahead/Transmission Enable
				if (wdcount == 1)
				{
					// check data
					{
						// check parity
						if (CalcParity( rcvd[1] ) == 0) return;

						// check address
						int dataaddr = (rcvd[1] >> 20) & 0b11111;
						if (ADDR != dataaddr) return;

						// check SEV
						unsigned short SEV = (rcvd[1] >> 1) & 0b111;
						if (SEV != 0b101) return;
					}
					unsigned short dwdata = (rcvd[1] >> 4) & 0xFFFF;

					if (dwdata == 0)
					{
						/// Interrogate Without GPC Data
						if (hasdata)
						{
							// Have Data
							unsigned short rsp = (0b0110 << 12) | ldbdatalen;
							unsigned int outdata = 0;

							outdata |= ADDR << 20;
							outdata |= rsp << 4;
							outdata |= 0b101 << 1;// SEV
							outdata |= (~CalcParity( outdata )) & 1;// parity

							Tx( id, &outdata, 1 );
						}
						else
						{
							// No Need For Bus
							unsigned short rsp = 0b0011 << 12;
							unsigned int outdata = 0;

							outdata |= ADDR << 20;
							outdata |= rsp << 4;
							outdata |= 0b101 << 1;// SEV
							outdata |= (~CalcParity( outdata )) & 1;// parity

							Tx( id, &outdata, 1 );
						}
					}
					else
					{
						/// Interrogate With GPC Data
						if (hasdata)
						{
							// Have Data
							unsigned short rsp = (0b0110 << 12) | ldbdatalen;
							unsigned int outdata = 0;

							outdata |= ADDR << 20;
							outdata |= rsp << 4;
							outdata |= 0b101 << 1;// SEV
							outdata |= (~CalcParity( outdata )) & 1;// parity

							Tx( id, &outdata, 1 );
						}
						else
						{
							// Send Data
							unsigned short rsp = 0b1011 << 12;
							unsigned int outdata = 0;

							outdata |= ADDR << 20;
							outdata |= rsp << 4;
							outdata |= 0b101 << 1;// SEV
							outdata |= (~CalcParity( outdata )) & 1;// parity

							Tx( id, &outdata, 1 );
						}
						// TODO No Need For Bus
					}
				}
				else if (wdcount == 0)
				{
					/// Go Ahead
					unsigned int outdata[32];
					memset( outdata, 0, 32 * sizeof(unsigned int) );

					for (int i = 0; i < ldbdatalen; i++)
					{
						outdata[i] |= ADDR << 20;
						outdata[i] |= ldbdata[i] << 4;
						outdata[i] |= 0b101 << 1;// SEV
						outdata[i] |= (~CalcParity( outdata[i] )) & 1;// parity
					}

					Tx( id, &outdata, ldbdatalen );

					hasdata = false;
				}
				else 
				{
					/// Transmission Enable
					// parse data
					RSCountdownHold = (rcvd[1] >> 4) & 0xFFFF;
					LaunchSequenceAbort = (rcvd[2] >> 4) & 0xFFFF;
					HoldFlags = (rcvd[3] >> 4) & 0xFFFF;
					HoldFlags |= (rcvd[4] >> 4) & 0xFFFF;
				}
				// TODO error
				break;
			case 0b0100:/// Status Request/Status
				if (wdcount == 0)
				{
					/// Status Request
					unsigned short rsp = 0;// TODO status
					unsigned int outdata = 0;

					outdata |= ADDR << 20;
					outdata |= rsp << 4;
					outdata |= 0b101 << 1;// SEV
					outdata |= (~CalcParity( outdata )) & 1;// parity

					Tx( id, &outdata, 1 );
				}
				else if (wdcount == 1)
				{
					/// Status
					// TODO save/process status
				}
				else
				{
					// TODO error
				}
				break;
		}
		return;
	}

	void LPS_Interface::AssembleData( void )
	{
		// maintain list of vars, update list when LPS calls, and then send it to LDB

		// increment id counter
		id++;
		if (id > 0x07FF)// 11b
		{
			id = 0;
		}

		// input destination 5b
		// input transaction id 11b
		ldbdata[0] = (1 << 11) | id;

		// mm operation code 4b
		// spare1 1b
		// ldb deu number 3b
		// spare2 2b
		// mm block number 5b
		// spare3 1b
		ldbdata[1] = 0;

		// control headed word 2
		ldbdata[2] = 0;

		// data x131
		uint64_t gmtlo64;
		memcpy( &gmtlo64, &GMTLO, 8 );
		ldbdata[3] = gmtlo64 & 0xFFFF;
		ldbdata[4] = (gmtlo64 >> 16) & 0xFFFF;
		ldbdata[5] = (gmtlo64 >> 32) & 0xFFFF;
		ldbdata[6] = (gmtlo64 >> 48) & 0xFFFF;
		ldbdata[7] = GMTLOSetCommand;
		ldbdata[8] = LPSCountdownHold;
		ldbdata[9] = LPSGoForAutoSequenceStart;
		ldbdata[10] = LPSGoForEngineStart;
		ldbdata[11] = ResumeCountCommand;
		ldbdata[12] = MPS_Slew;
		ldbdata[13] = Aero_Slew;
		ldbdata[14] = SRB_Slew;
		ldbdata[15] = 0;// RECYCLE COUNT CMD FLAG
		ldbdata[16] = 0;// LPS ORBITER VENT DOORS OVRD WORD
		ldbdata[17] = 0;// LPS BYPASS LO2 POGO RECRC
		ldbdata[18] = 0;// LPS BYPASS L02 OVBD B/V A FLAG
		ldbdata[19] = 0;// LPS BYPASS L02 OVBD B/V B FLAG

		ldbdatalen = 19;
		hasdata = true;
		return;
	}

	void LPS_Interface::SetGMTLO( double GMTLO )
	{
		oapiWriteLogV( "SetGMTLO" );
		this->GMTLO = GMTLO;
		//AssembleData();
		return;
	}

	void LPS_Interface::SetGMTLOSetCommandFlag( bool val )
	{
		oapiWriteLogV( "SetGMTLOSetCommandFlag" );
		GMTLOSetCommand = true;
		AssembleData();
		GMTLOSetCommand = false;
		return;
	}

	void LPS_Interface::SetLPSCountdownHoldFlag( bool val )
	{
		oapiWriteLogV( "SetLPSCountdownHoldFlag" );
		LPSCountdownHold = val;
		AssembleData();
		return;
	}

	void LPS_Interface::SetLPSGoForAutoSequenceStartFlag( bool val )
	{
		oapiWriteLogV( "SetLPSGoForAutoSequenceStartFlag" );
		LPSGoForAutoSequenceStart = val;
		AssembleData();
		return;
	}

	void LPS_Interface::SetLPSGoForEngineStartFlag( bool val )
	{
		oapiWriteLogV( "SetLPSGoForEngineStartFlag" );
		LPSGoForEngineStart = val;
		AssembleData();
		return;
	}

	void LPS_Interface::SetResumeCountCommandFlag( bool val )
	{
		oapiWriteLogV( "SetResumeCountCommandFlag" );
		ResumeCountCommand = true;
		AssembleData();
		ResumeCountCommand = false;
		return;
	}

	bool LPS_Interface::GetRSCountdownHoldFlag( void ) const
	{
		return RSCountdownHold;
	}

	bool LPS_Interface::GetLaunchSequenceAbortFlag( void ) const
	{
		return LaunchSequenceAbort;
	}

	unsigned int LPS_Interface::GetHoldFlags( void ) const
	{
		return HoldFlags;
	}

	void LPS_Interface::SetSSMEActPos( int num, double Ppos, double Ypos )
	{
		if (num == 1)// Aero slew
		{
			Aero_Slew = true;
			AssembleData();
			Aero_Slew = false;
		}
		else if (num == 2)// MPS slew
		{
			MPS_Slew = true;
			AssembleData();
			MPS_Slew = false;
		}
		return;
	}
}

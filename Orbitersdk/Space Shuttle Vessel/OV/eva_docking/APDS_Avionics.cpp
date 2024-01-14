#include "APDS_Avionics.h"


namespace eva_docking
{
	static void RelayNetwork( const bool ctrl_gnd_1, const bool ctrl_gnd_2, const bool ctrl_gnd_3, const bool ctrl_pwr_1, const bool ctrl_pwr_2, const bool ctrl_pwr_3, const bool in_1, const bool in_2, bool &out_1, bool &out_2, bool &out_3 )
	{
		bool P1 = !ctrl_gnd_1 && ctrl_pwr_1;
		bool P2 = !ctrl_gnd_1 && ctrl_pwr_1;
		bool P3 = !ctrl_gnd_2 && ctrl_pwr_2;
		bool P4 = !ctrl_gnd_3 && ctrl_pwr_3;

		bool in = in_1 && in_2;

		bool o1 = (P3 && P4) || (P1 && P3) || (P1 && P2 && P4);
		bool o2 = (P3 && P4) || (P1 && P2 && P4) || (P1 && P2 && P3);
		bool o3 = (P3 && P4) || (P1 && P4) || (P1 && P3) || (P1 && P2);

		out_1 = in || !o1;
		out_2 = in || !o2;
		out_3 = in || !o3;
		return;
	}

	static void RelayNetwork_PACU( const bool ctrl_gnd_1, const bool ctrl_gnd_2, const bool ctrl_gnd_3, const bool ctrl_pwr_1, const bool ctrl_pwr_2, const bool ctrl_pwr_3, const bool in_1, const bool in_2, bool &out_1, bool &out_2, bool &out_3 )
	{
		bool P1 = !ctrl_gnd_1 && ctrl_pwr_3;
		bool P2 = !ctrl_gnd_2 && ctrl_pwr_1;
		bool P3 = !ctrl_gnd_1 && ctrl_pwr_2;
		bool P4 = !ctrl_gnd_3 && ctrl_pwr_3;

		bool o1_i1 = P2 && P3;
		bool o1_i2 = P1 && P3 && P4;
		bool o2_i1 = P2 && P3;
		bool o2_i2 = (P1 && P3 && P4) || (P1 && P2 && P4);
		bool o3_i1 = P2 && P3;
		bool o3_i2 = P1 && P4;

		out_1 = (in_1 || !o1_i1) || (in_2 || !o1_i2);
		out_2 = (in_1 || !o2_i1) || (in_2 || !o2_i2);
		out_3 = (in_1 || !o3_i1) || (in_2 || !o3_i2);
		return;
	}

	static void MomentaryRelays( const bool ctrl_gnd_1, const bool ctrl_gnd_2, const bool ctrl_gnd_3, const bool ctrl_pwr_1, const bool ctrl_pwr_2, const bool ctrl_pwr_3, const bool in_1, const bool in_2, const bool in_3, bool &out_on_1, bool &out_on_2, bool &out_on_3, bool &out_off_1, bool &out_off_2, bool &out_off_3 )
	{
		bool k1 = !ctrl_gnd_1 && ctrl_pwr_1;
		bool k2 = !ctrl_gnd_2 && ctrl_pwr_2;
		bool k3 = !ctrl_gnd_3 && ctrl_pwr_3;

		out_on_1 = !k1 || in_1;
		out_off_1 = k1 || in_1;

		out_on_2 = !k2 || in_2;
		out_off_2 = k2 || in_2;

		out_on_3 = !k3 || in_3;
		out_off_3 = k3 || in_3;
		return;
	}

	void _2of3VotingRelay( const bool ctrl_gnd_1, const bool ctrl_gnd_2, const bool ctrl_gnd_3, const bool ctrl_pwr_1, const bool ctrl_pwr_2, const bool ctrl_pwr_3, const bool in_1, const bool in_2, bool &out_1, bool &out_2 )
	{
		bool k1 = !ctrl_gnd_3 && ctrl_pwr_3;
		bool k2 = !ctrl_gnd_1 && ctrl_pwr_1;
		bool k3 = !ctrl_gnd_1 && ctrl_pwr_1;
		bool k4 = !ctrl_gnd_2 && ctrl_pwr_2;

		bool o1 = k2 && k4;
		bool o21 = k1 && !k3 && k4;
		bool o22 = k1 && k3;

		bool out = (in_1 || !o1) && (in_1 || !o21) && (in_2 || !o22);

		out_1 = out;
		out_2 = out;
		return;
	}

	void _2of3VotingRelay_Off( const bool ctrl_gnd_1, const bool ctrl_gnd_2, const bool ctrl_gnd_3, const bool ctrl_pwr_1, const bool ctrl_pwr_2, const bool ctrl_pwr_3, const bool in_1, const bool in_2, bool &out_1, bool &out_2 )
	{
		bool k1 = !ctrl_gnd_3 && ctrl_pwr_3;
		bool k2 = !ctrl_gnd_1 && ctrl_pwr_1;
		bool k3 = !ctrl_gnd_1 && ctrl_pwr_1;
		bool k4 = !ctrl_gnd_2 && ctrl_pwr_2;

		bool o1 = k2 && k4;
		bool o2 = k1 && k3;

		out_1 = in_1 || o1;
		out_2 = in_2 || o2;
		return;
	}

	static void LatchingRelay( const bool pwr, const bool gnd_on, const bool gnd_off, bool& k )
	{
		k = (k && !pwr) || (k && !gnd_on) || (k && gnd_off) || (pwr && !gnd_on && gnd_off);
		return;
	}

	static void TimeDelay( const double td, const bool in, const double dt, double &timer, bool &out )
	{
		// steady-state
		if (in == out)
		{
			timer = -1.0;
			return;
		}

		// change of state
		if (timer < 0.0)
		{
			timer = 0.0;
			return;
		}

		// time delay complete
		timer += dt;
		if (timer >= td)
		{
			timer = -1.0;
			out = in;
		}
		return;
	}



	APDS_Avionics::APDS_Avionics( void )
	{
		return;
	}

	APDS_Avionics::~APDS_Avionics( void )
	{
		return;
	}

	bool APDS_Avionics::ReadState( FILEHANDLE scn )
	{
		char* line;

		while (oapiReadScenario_nextline( scn, line ))
		{
			if (!_strnicmp( line, "@ENDOBJECT", 10 ))
			{
				return true;
			}
			else
			{
				unsigned long i = 0;
				char pszKey[256];
				while ((*line != ' ') && (*line != '\0'))
				{
					pszKey[i++] = *line;
					line++;
				}
				pszKey[i++] = '\0';
				Load( pszKey, line );
			}
		}
		return false;
	}

	void APDS_Avionics::SaveState( FILEHANDLE scn ) const
	{
		Save( scn );
		return;
	}

	void APDS_Avionics::LoadVarsOut( char* line, bool& vala, bool& valb, bool& valc )
	{
		int itmp1;
		int itmp2;
		int itmp3;

		sscanf_s( line, "%d %d %d", &itmp1, &itmp2, &itmp3 );

		vala = (itmp1 == 1);
		valb = (itmp2 == 1);
		valc = (itmp3 == 1);
		return;
	}

	void APDS_Avionics::LoadVarsTD( char* line, bool& vala, bool& valb, bool& valc, double& tda, double& tdb, double& tdc )
	{
		int itmp1;
		int itmp2;
		int itmp3;

		sscanf_s( line, "%d %d %d %lf %lf %lf", &itmp1, &itmp2, &itmp3, &tda, &tdb, &tdc );

		vala = (itmp1 == 1);
		valb = (itmp2 == 1);
		valc = (itmp3 == 1);
		return;
	}

	void APDS_Avionics::SaveVarsOut( FILEHANDLE scn, char* name, const bool vala, const bool valb, const bool valc ) const
	{
		char cbuf[256];
		sprintf_s( cbuf, 256, "%d %d %d", vala, valb, valc );
		oapiWriteScenario_string( scn, name, cbuf );
		return;
	}

	void APDS_Avionics::SaveVarsTD( FILEHANDLE scn, char* name, const bool vala, const bool valb, const bool valc, const double tda, const double tdb, const double tdc ) const
	{
		char cbuf[256];
		sprintf_s( cbuf, 256, "%d %d %d %f %f %f", vala, valb, valc, tda, tdb, tdc );
		oapiWriteScenario_string( scn, name, cbuf );
		return;
	}


	PSU::PSU( void ):
		K1(false), K2(false), K11(false), K12(false),
		K3(false), K4(false), K13(false), K14(false),
		K5(false), K6(false), K15(false), K16(false),
		e10_out_on_1(true), e10_out_on_2(true), e10_out_on_3(true),
		e12_out_1(true), e12_out_2(true), e12_out_3(true),
		e12_ctrl_gnd_1(true), e12_ctrl_gnd_2(true), e12_ctrl_gnd_3(true), e12_ctrl_gnd_1_td(-1.0), e12_ctrl_gnd_2_td(-1.0), e12_ctrl_gnd_3_td(-1.0),
		e23_ctrl_gnd_1(true), e23_ctrl_gnd_2(true), e23_ctrl_gnd_3(true), e23_ctrl_gnd_1_td(-1.0), e23_ctrl_gnd_2_td(-1.0), e23_ctrl_gnd_3_td(-1.0)
	{
		return;
	}

	void PSU::Run( const double dt, PSU_IO& io )
	{
		bool tmp1;
		bool tmp2;
		bool tmp3;

		// E1
		bool e1_out_1;
		bool e1_out_2;
		bool e1_out_3;
		RelayNetwork( io.power_on, io.power_on, io.power_on, io.cntl_pnl_a, io.cntl_pnl_b, io.cntl_pnl_c, io.gnd_c, io.gnd_c, e1_out_1, e1_out_2, e1_out_3 );

		// E2
		bool e2_out_1;
		bool e2_out_2;
		bool e2_out_3;
		RelayNetwork( io.power_off, io.power_off, io.power_off, io.cntl_pnl_a, io.cntl_pnl_b, io.cntl_pnl_c, io.gnd_c, io.gnd_c, e2_out_1, e2_out_2, e2_out_3 );

		// E25, 22
		bool e25_out_1;
		bool e25_out_2;
		bool e25_out_3;
		MomentaryRelays( e2_out_1 && e12_out_1, e2_out_2 && e12_out_2, e2_out_3 && e12_out_3, io.pwr_wa, io.pwr_wb, io.pwr_wc, io.gnd_c, io.gnd_c, io.gnd_c, e25_out_1, e25_out_2, e25_out_3, tmp1, tmp2, tmp3 );

		// E23
		bool e23_out_1;
		bool e23_out_2;
		bool e23_out_3;
		TimeDelay( 0.2, e25_out_1, dt, e23_ctrl_gnd_1_td, e23_ctrl_gnd_1 );
		TimeDelay( 0.2, e25_out_2, dt, e23_ctrl_gnd_2_td, e23_ctrl_gnd_2 );
		TimeDelay( 0.2, e25_out_3, dt, e23_ctrl_gnd_3_td, e23_ctrl_gnd_3 );
		MomentaryRelays( e23_ctrl_gnd_1, e23_ctrl_gnd_2, e23_ctrl_gnd_3, io.pwr_wa, io.pwr_wb, io.pwr_wc, io.gnd_c, io.gnd_c, io.gnd_c, e23_out_1, e23_out_2, e23_out_3, tmp1, tmp2, tmp3 );

		// E12, 13
		TimeDelay( 0.2, e23_out_1, dt, e12_ctrl_gnd_1_td, e12_ctrl_gnd_1 );
		TimeDelay( 0.2, e23_out_2, dt, e12_ctrl_gnd_2_td, e12_ctrl_gnd_2 );
		TimeDelay( 0.2, e23_out_3, dt, e12_ctrl_gnd_3_td, e12_ctrl_gnd_3 );
		MomentaryRelays( e12_ctrl_gnd_1, e12_ctrl_gnd_2, e12_ctrl_gnd_3, io.pwr_wa, io.pwr_wb, io.pwr_wc, e25_out_1, e25_out_2, e25_out_3, tmp1, tmp2, tmp3, e12_out_1, e12_out_2, e12_out_3 );

		// E4
		bool e4_out_1;
		bool e4_out_2;
		bool e4_out_3;
		RelayNetwork( e23_out_1, e23_out_2, e23_out_3, io.pwr_wa, io.pwr_wb, io.pwr_wc, io.gnd_c, io.gnd_c, e4_out_1, e4_out_2, e4_out_3 );

		// E10, 11
		bool e10_out_off_1;
		bool e10_out_off_2;
		bool e10_out_off_3;
		MomentaryRelays( e4_out_1 && e10_out_on_1, e4_out_2 && e10_out_on_2, e4_out_3 && e10_out_on_3, io.pwr_wa, io.pwr_wb, io.pwr_wc, e1_out_1, e1_out_2, e1_out_3, e10_out_on_1, e10_out_on_2, e10_out_on_3, e10_out_off_1, e10_out_off_2, e10_out_off_3 );

		// K
		LatchingRelay( io.pwr_wa, e10_out_off_1, e4_out_1, K1 );
		LatchingRelay( io.pwr_wa, e10_out_off_1, e4_out_1, K2 );
		LatchingRelay( io.pwr_wa, e10_out_off_1, e4_out_1, K11 );
		LatchingRelay( io.pwr_wa, e10_out_off_1, e4_out_1, K12 );

		LatchingRelay( io.pwr_wb, e10_out_off_2, e4_out_2, K3 );
		LatchingRelay( io.pwr_wb, e10_out_off_2, e4_out_2, K4 );
		LatchingRelay( io.pwr_wb, e10_out_off_2, e4_out_2, K13 );
		LatchingRelay( io.pwr_wb, e10_out_off_2, e4_out_2, K14 );
		
		LatchingRelay( io.pwr_wc, e10_out_off_3, e4_out_3, K5 );
		LatchingRelay( io.pwr_wc, e10_out_off_3, e4_out_3, K6 );
		LatchingRelay( io.pwr_wc, e10_out_off_3, e4_out_3, K15 );
		LatchingRelay( io.pwr_wc, e10_out_off_3, e4_out_3, K16 );

		// grounds
		io.gnd_c_1 = !(K1 && K4) || io.gnd_c;
		io.gnd_c_2 = !(K3 && K6) || io.gnd_c;
		io.gnd_c_3 = !(K2 && K5) || io.gnd_c;

		// powers
		io.pwr_wa_1 = K1 && io.pwr_wa;
		io.pwr_wa_2 = K2 && io.pwr_wa;

		io.pwr_wb_1 = K3 && io.pwr_wb;
		io.pwr_wb_2 = K4 && io.pwr_wb;

		io.pwr_wc_1 = K5 && io.pwr_wc;
		io.pwr_wc_2 = K6 && io.pwr_wc;

		// E20
		MomentaryRelays( e1_out_1, e1_out_2, e1_out_3, io.pwr_wa, io.pwr_wb, io.pwr_wc, io.gnd_c_1, io.gnd_c_2, io.gnd_c_3, io.pwr_on_reset_1, io.pwr_on_reset_2, io.pwr_on_reset_3, tmp1, tmp2, tmp3 );

		// E21
		MomentaryRelays( e2_out_1, e2_out_2, e2_out_3, io.pwr_wa, io.pwr_wb, io.pwr_wc, io.gnd_c_1, io.gnd_c_2, io.gnd_c_3, io.pwr_off_reset_1, io.pwr_off_reset_2, io.pwr_off_reset_3, tmp1, tmp2, tmp3 );
		return;
	}

	void PSU::Load( char* keyword, char* line )
	{
		int itmp;

		if (!strcmp( keyword, "K1" ))
		{
			sscanf_s( line, "%d", &itmp );
			K1 = (itmp == 1);
		}
		else if (!strcmp( keyword, "K2" ))
		{
			sscanf_s( line, "%d", &itmp );
			K2 = (itmp == 1);
		}
		else if (!strcmp( keyword, "K3" ))
		{
			sscanf_s( line, "%d", &itmp );
			K3 = (itmp == 1);
		}
		else if (!strcmp( keyword, "K4" ))
		{
			sscanf_s( line, "%d", &itmp );
			K4 = (itmp == 1);
		}
		else if (!strcmp( keyword, "K5" ))
		{
			sscanf_s( line, "%d", &itmp );
			K5 = (itmp == 1);
		}
		else if (!strcmp( keyword, "K6" ))
		{
			sscanf_s( line, "%d", &itmp );
			K6 = (itmp == 1);
		}
		else if (!strcmp( keyword, "K11" ))
		{
			sscanf_s( line, "%d", &itmp );
			K11 = (itmp == 1);
		}
		else if (!strcmp( keyword, "K12" ))
		{
			sscanf_s( line, "%d", &itmp );
			K12 = (itmp == 1);
		}
		else if (!strcmp( keyword, "K13" ))
		{
			sscanf_s( line, "%d", &itmp );
			K13 = (itmp == 1);
		}
		else if (!strcmp( keyword, "K14" ))
		{
			sscanf_s( line, "%d", &itmp );
			K14 = (itmp == 1);
		}
		else if (!strcmp( keyword, "K15" ))
		{
			sscanf_s( line, "%d", &itmp );
			K15 = (itmp == 1);
		}
		else if (!strcmp( keyword, "K16" ))
		{
			sscanf_s( line, "%d", &itmp );
			K16 = (itmp == 1);
		}
		else if (!strcmp( keyword, "E10_OUT_ON" ))
		{
			LoadVarsOut( line, e10_out_on_1, e10_out_on_2, e10_out_on_3 );
		}
		else if (!strcmp( keyword, "E12_OUT" ))
		{
			LoadVarsOut( line, e12_out_1, e12_out_2, e12_out_3 );
		}
		else if (!strcmp( keyword, "E12_CTRL_GND" ))
		{
			LoadVarsTD( line, e12_ctrl_gnd_1, e12_ctrl_gnd_2, e12_ctrl_gnd_3, e12_ctrl_gnd_1_td, e12_ctrl_gnd_2_td, e12_ctrl_gnd_3_td );
		}
		else if (!strcmp( keyword, "E23_CTRL_GND" ))
		{
			LoadVarsTD( line, e23_ctrl_gnd_1, e23_ctrl_gnd_2, e23_ctrl_gnd_3, e23_ctrl_gnd_1_td, e23_ctrl_gnd_2_td, e23_ctrl_gnd_3_td );
		}
		else
		{
			// TODO unknown parameter
		}
		return;
	}

	void PSU::Save( FILEHANDLE scn ) const
	{
		oapiWriteScenario_int( scn, "K1", K1 );
		oapiWriteScenario_int( scn, "K2", K2 );
		oapiWriteScenario_int( scn, "K3", K3 );
		oapiWriteScenario_int( scn, "K4", K4 );
		oapiWriteScenario_int( scn, "K5", K5 );
		oapiWriteScenario_int( scn, "K6", K6 );
		oapiWriteScenario_int( scn, "K11", K11 );
		oapiWriteScenario_int( scn, "K12", K12 );
		oapiWriteScenario_int( scn, "K13", K13 );
		oapiWriteScenario_int( scn, "K14", K14 );
		oapiWriteScenario_int( scn, "K15", K15 );
		oapiWriteScenario_int( scn, "K16", K16 );

		SaveVarsOut( scn, "E10_OUT_ON", e10_out_on_1, e10_out_on_2, e10_out_on_3 );
		SaveVarsOut( scn, "E12_OUT", e12_out_1, e12_out_2, e12_out_3 );
		SaveVarsTD( scn, "E12_CTRL_GND", e12_ctrl_gnd_1, e12_ctrl_gnd_2, e12_ctrl_gnd_3, e12_ctrl_gnd_1_td, e12_ctrl_gnd_2_td, e12_ctrl_gnd_3_td );
		SaveVarsTD( scn, "E23_CTRL_GND", e23_ctrl_gnd_1, e23_ctrl_gnd_2, e23_ctrl_gnd_3, e23_ctrl_gnd_1_td, e23_ctrl_gnd_2_td, e23_ctrl_gnd_3_td );
		return;
	}



	DSCU::DSCU( void ):
		gnd_ct1(true), gnd_ct2(true), gnd_ct3(true),
		kp1(false), kp2(false), kp3(false),
		e102_out_1(true), e102_out_2(true), e102_out_3(true),
		e124_out_1(true), e124_out_2(true), e124_out_3(true),
		e113_out_1(true), e113_out_2(true), e113_out_3(true),
		e114_out_1(true), e114_out_2(true), e114_out_3(true),
		e148_out_1(true), e148_out_2(true), e148_out_3(true),
		e37_out_1(true), e37_out_2(true), e37_out_3(true),
		e103_out_1(true), e103_out_2(true), e103_out_3(true),
		e134_out_1(true), e134_out_2(true), e134_out_3(true),
		e1_out_off_1(true), e1_out_off_2(true), e1_out_off_3(true),
		e128_out_1(true), e128_out_2(true), e128_out_3(true),
		e139_out_1(true), e139_out_2(true), e139_out_3(true),
		e140_out_1(true), e140_out_2(true), e140_out_3(true),
		e15_out_off_1(true), e15_out_off_2(true), e15_out_off_3(true),
		e31_ctrl_gnd_1(true), e31_ctrl_gnd_2(true), e31_ctrl_gnd_3(true), e31_ctrl_gnd_1_td(-1.0), e31_ctrl_gnd_2_td(-1.0), e31_ctrl_gnd_3_td(-1.0),
		e33_ctrl_gnd_1(true), e33_ctrl_gnd_2(true), e33_ctrl_gnd_3(true), e33_ctrl_gnd_1_td(-1.0), e33_ctrl_gnd_2_td(-1.0), e33_ctrl_gnd_3_td(-1.0),
		e35_ctrl_gnd_1(true), e35_ctrl_gnd_2(true), e35_ctrl_gnd_3(true), e35_ctrl_gnd_1_td(-1.0), e35_ctrl_gnd_2_td(-1.0), e35_ctrl_gnd_3_td(-1.0),
		e145_ctrl_gnd_1(true), e145_ctrl_gnd_2(true), e145_ctrl_gnd_3(true), e145_ctrl_gnd_1_td(-1.0), e145_ctrl_gnd_2_td(-1.0), e145_ctrl_gnd_3_td(-1.0),
		e206_ctrl_gnd_1(true), e206_ctrl_gnd_2(true), e206_ctrl_gnd_3(true), e206_ctrl_gnd_1_td(-1.0), e206_ctrl_gnd_2_td(-1.0), e206_ctrl_gnd_3_td(-1.0),
		e204_ctrl_gnd_1(true), e204_ctrl_gnd_2(true), e204_ctrl_gnd_3(true), e204_ctrl_gnd_1_td(-1.0), e204_ctrl_gnd_2_td(-1.0), e204_ctrl_gnd_3_td(-1.0),
		e1_ctrl_gnd_1(true), e1_ctrl_gnd_2(true), e1_ctrl_gnd_3(true), e1_ctrl_gnd_1_td(-1.0), e1_ctrl_gnd_2_td(-1.0), e1_ctrl_gnd_3_td(-1.0),
		e208_ctrl_gnd_1(true), e208_ctrl_gnd_2(true), e208_ctrl_gnd_3(true), e208_ctrl_gnd_1_td(-1.0), e208_ctrl_gnd_2_td(-1.0), e208_ctrl_gnd_3_td(-1.0),
		e28_ctrl_gnd_1(true), e28_ctrl_gnd_2(true), e28_ctrl_gnd_3(true), e28_ctrl_gnd_1_td(-1.0), e28_ctrl_gnd_2_td(-1.0), e28_ctrl_gnd_3_td(-1.0),
		e202_ctrl_gnd_1(true), e202_ctrl_gnd_2(true), e202_ctrl_gnd_3(true), e202_ctrl_gnd_1_td(-1.0), e202_ctrl_gnd_2_td(-1.0), e202_ctrl_gnd_3_td(-1.0),
		e101_ctrl_gnd_1(true), e101_ctrl_gnd_2(true), e101_ctrl_gnd_3(true), e101_ctrl_gnd_1_td(-1.0), e101_ctrl_gnd_2_td(-1.0), e101_ctrl_gnd_3_td(-1.0)
	{
		return;
	}

	void DSCU::Run( const double dt, DSCU_IO& io )
	{
		bool tmp1;
		bool tmp2;
		bool tmp3;

		bool pwr_cntl_pnl_a = true;// TODO
		bool pwr_cntl_pnl_b = true;// TODO
		bool pwr_cntl_pnl_c = true;// TODO

		// E102, 142
		MomentaryRelays( e102_out_1 && io.apds_circ_prot_off, e102_out_2 && io.apds_circ_prot_off, e102_out_3 && io.apds_circ_prot_off, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, e102_out_1, e102_out_2, e102_out_3, tmp1, tmp2, tmp3 );

		// E221
		bool e221_out_1;
		bool e221_out_2;
		_2of3VotingRelay( e102_out_1, e102_out_2, e102_out_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, e221_out_1, e221_out_2 );
		bool gnd_blamb = e221_out_1 && e221_out_2;

		// E163
		bool e163_out_1;
		bool e163_out_2;
		bool e163_out_3;
		MomentaryRelays( io.undocking, io.undocking, io.undocking, pwr_cntl_pnl_a, pwr_cntl_pnl_b, pwr_cntl_pnl_c, gnd_blamb, gnd_blamb, gnd_blamb, e163_out_1, e163_out_2, e163_out_3, tmp1, tmp2, tmp3 );

		// E124
		MomentaryRelays( e163_out_1 && e124_out_1, e163_out_2 && e124_out_2, e163_out_3 && e124_out_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, e124_out_1, e124_out_2, e124_out_3, tmp1, tmp2, tmp3 );

		// E226
		bool e226_out_1;
		bool e226_out_2;
		bool e226_out_3;
		MomentaryRelays( e124_out_1, e124_out_2, e124_out_3, io.pwr_a, io.pwr_b, io.pwr_c, io.undockingcomplete_ind_1, io.undockingcomplete_ind_1 && io.undockingcomplete_ind_2, io.undockingcomplete_ind_2, e226_out_1, e226_out_2, e226_out_3, tmp1, tmp2, tmp3 );

		// E131
		bool e131_out_1;
		bool e131_out_2;
		bool e131_out_3;
		RelayNetwork_PACU( io.readytohook_ind_1, io.readytohook_ind_1 && io.readytohook_ind_2, io.readytohook_ind_2, io.pwr_b, io.pwr_a, io.pwr_c, io.gnd_abc, io.gnd_abc, e131_out_1, e131_out_2, e131_out_3 );

		// E181
		bool e181_out_1;
		bool e181_out_2;
		bool e181_out_3;
		MomentaryRelays( gnd_ct1 && e148_out_1, gnd_ct2 && e148_out_2, gnd_ct3 && e148_out_3, io.pwr_a, io.pwr_b, io.pwr_c, e131_out_1, e131_out_2, e131_out_3, e181_out_1, e181_out_2, e181_out_3, tmp1, tmp2, tmp3 );

		// E33, E34A
		bool e33_out_1;
		bool e33_out_2;
		bool e33_out_3;
		TimeDelay( 0.2, e181_out_1, dt, e33_ctrl_gnd_1_td, e33_ctrl_gnd_1 );
		TimeDelay( 0.2, e181_out_2, dt, e33_ctrl_gnd_2_td, e33_ctrl_gnd_2 );
		TimeDelay( 0.2, e181_out_3, dt, e33_ctrl_gnd_3_td, e33_ctrl_gnd_3 );
		MomentaryRelays( e33_ctrl_gnd_1, e33_ctrl_gnd_2, e33_ctrl_gnd_3, io.pwr_a, io.pwr_b, io.pwr_c, e181_out_1, e181_out_2, e181_out_3, tmp1, tmp2, tmp3, e33_out_1, e33_out_2, e33_out_3 );

		// hooks 1
		bool e182_out_1;
		bool e182_out_2;
		bool e182_out_3;
		bool e173_out_1;
		bool e173_out_2;
		bool e173_out_3;
		{
			// E155
			bool e155_out_1;
			bool e155_out_2;
			bool e155_out_3;
			MomentaryRelays( io.open_hooks, io.open_hooks, io.open_hooks, pwr_cntl_pnl_a, pwr_cntl_pnl_b, pwr_cntl_pnl_c, gnd_blamb, gnd_blamb, gnd_blamb, e155_out_1, e155_out_2, e155_out_3, tmp1, tmp2, tmp3 );

			// E117
			MomentaryRelays( e155_out_1 && e163_out_1, e155_out_2 && e163_out_2, e155_out_3 && e163_out_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, io.hooks_1_op_cmd_1, io.hooks_1_op_cmd_2, io.hooks_1_op_cmd_3, tmp1, tmp2, tmp3 );

			// E153
			bool e153_out_1;
			bool e153_out_2;
			bool e153_out_3;
			MomentaryRelays( io.close_hooks, io.close_hooks, io.close_hooks, pwr_cntl_pnl_a, pwr_cntl_pnl_b, pwr_cntl_pnl_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, e153_out_1, e153_out_2, e153_out_3, tmp1, tmp2, tmp3 );

			// E121
			MomentaryRelays( e153_out_1 && e33_out_1, e153_out_2 && e33_out_2, e153_out_3 && e33_out_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, io.hooks_1_cl_cmd_1, io.hooks_1_cl_cmd_2, io.hooks_1_cl_cmd_3, tmp1, tmp2, tmp3 );

			// E157
			MomentaryRelays( io.hooks_1_op_ind_1, io.hooks_1_op_ind_2, io.hooks_1_op_ind_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_pnl, io.gnd_pnl, io.gnd_pnl, io.hooks_1_op_light_1, io.hooks_1_op_light_2, io.hooks_1_op_light_3, tmp1, tmp2, tmp3 );

			// E119
			MomentaryRelays( io.hooks_1_cl_ind_1, io.hooks_1_cl_ind_2, io.hooks_1_cl_ind_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_pnl, io.gnd_pnl, io.gnd_pnl, io.hooks_1_cl_light_1, io.hooks_1_cl_light_2, io.hooks_1_cl_light_3, tmp1, tmp2, tmp3 );

			// E173
			MomentaryRelays( io.inbetweenhooks_ind_1, io.inbetweenhooks_ind_1 && io.inbetweenhooks_ind_2, io.inbetweenhooks_ind_2, io.pwr_b, io.pwr_a, io.pwr_c, e181_out_1, e181_out_2, e181_out_3, e173_out_1, e173_out_2, e173_out_3, tmp1, tmp2, tmp3 );

			// E113
			MomentaryRelays( e113_out_1 && io.gnd_hooks_1_cl_1, e113_out_2 && io.gnd_hooks_1_cl_2, e113_out_3 && io.gnd_hooks_1_cl_3, io.pwr_a, io.pwr_b, io.pwr_c, gnd_ct1, gnd_ct2, gnd_ct3, e113_out_1, e113_out_2, e113_out_3, tmp1, tmp2, tmp3 );

			// E182
			MomentaryRelays( e113_out_1, e113_out_2, e113_out_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, e182_out_1, e182_out_2, e182_out_3, tmp1, tmp2, tmp3 );
		}

		// hooks 2
		bool e183_out_1;
		bool e183_out_2;
		bool e183_out_3;
		bool e175_out_1;
		bool e175_out_2;
		bool e175_out_3;
		{
			// E156
			bool e156_out_1;
			bool e156_out_2;
			bool e156_out_3;
			MomentaryRelays( io.open_hooks, io.open_hooks, io.open_hooks, pwr_cntl_pnl_a, pwr_cntl_pnl_b, pwr_cntl_pnl_c, gnd_blamb, gnd_blamb, gnd_blamb, e156_out_1, e156_out_2, e156_out_3, tmp1, tmp2, tmp3 );

			// E118
			MomentaryRelays( e156_out_1 && e163_out_1, e156_out_2 && e163_out_2, e156_out_3 && e163_out_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, io.hooks_2_op_cmd_1, io.hooks_2_op_cmd_2, io.hooks_2_op_cmd_3, tmp1, tmp2, tmp3 );

			// E154
			bool e154_out_1;
			bool e154_out_2;
			bool e154_out_3;
			MomentaryRelays( io.close_hooks, io.close_hooks, io.close_hooks, pwr_cntl_pnl_a, pwr_cntl_pnl_b, pwr_cntl_pnl_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, e154_out_1, e154_out_2, e154_out_3, tmp1, tmp2, tmp3 );

			// E122
			MomentaryRelays( e154_out_1 && e33_out_1, e154_out_2 && e33_out_2, e154_out_3 && e33_out_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, io.hooks_2_cl_cmd_1, io.hooks_2_cl_cmd_2, io.hooks_2_cl_cmd_3, tmp1, tmp2, tmp3 );

			// E158
			MomentaryRelays( io.hooks_2_op_ind_1, io.hooks_2_op_ind_2, io.hooks_2_op_ind_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_pnl, io.gnd_pnl, io.gnd_pnl, io.hooks_2_op_light_1, io.hooks_2_op_light_2, io.hooks_2_op_light_3, tmp1, tmp2, tmp3 );

			// E120
			MomentaryRelays( io.hooks_2_cl_ind_1, io.hooks_2_cl_ind_2, io.hooks_2_cl_ind_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_pnl, io.gnd_pnl, io.gnd_pnl, io.hooks_2_cl_light_1, io.hooks_2_cl_light_2, io.hooks_2_cl_light_3, tmp1, tmp2, tmp3 );

			// E175
			MomentaryRelays( io.inbetweenhooks_ind_1, io.inbetweenhooks_ind_1 && io.inbetweenhooks_ind_2, io.inbetweenhooks_ind_2, io.pwr_b, io.pwr_a, io.pwr_c, e181_out_1, e181_out_2, e181_out_3, e175_out_1, e175_out_2, e175_out_3, tmp1, tmp2, tmp3 );

			// E114
			MomentaryRelays( e114_out_1 && io.gnd_hooks_2_cl_1, e114_out_2 && io.gnd_hooks_2_cl_2, e114_out_3 && io.gnd_hooks_2_cl_3, io.pwr_a, io.pwr_b, io.pwr_c, gnd_ct1, gnd_ct2, gnd_ct3, e114_out_1, e114_out_2, e114_out_3, tmp1, tmp2, tmp3 );

			// E183
			MomentaryRelays( e114_out_1, e114_out_2, e114_out_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, e183_out_1, e183_out_2, e183_out_3, tmp1, tmp2, tmp3 );
		}

		// E35, E34-2
		bool e35_out_1;
		bool e35_out_2;
		bool e35_out_3;
		TimeDelay( 0.2, e182_out_1 && e183_out_1, dt, e35_ctrl_gnd_1_td, e35_ctrl_gnd_1 );
		TimeDelay( 0.2, e182_out_2 && e183_out_2, dt, e35_ctrl_gnd_2_td, e35_ctrl_gnd_2 );
		TimeDelay( 0.2, e182_out_3 && e183_out_3, dt, e35_ctrl_gnd_3_td, e35_ctrl_gnd_3 );
		MomentaryRelays( e35_ctrl_gnd_1, e35_ctrl_gnd_2, e35_ctrl_gnd_3, io.pwr_a, io.pwr_b, io.pwr_c, e182_out_1 && e183_out_1, e182_out_2 && e183_out_2, e182_out_3 && e183_out_3, tmp1, tmp2, tmp3, e35_out_1, e35_out_2, e35_out_3 );

		// E145
		bool e145_out_1;
		bool e145_out_2;
		bool e145_out_3;
		TimeDelay( 10.0, e182_out_1 && e183_out_1, dt, e145_ctrl_gnd_1_td, e145_ctrl_gnd_1 );
		TimeDelay( 10.0, e182_out_2 && e183_out_2, dt, e145_ctrl_gnd_2_td, e145_ctrl_gnd_2 );
		TimeDelay( 10.0, e182_out_3 && e183_out_3, dt, e145_ctrl_gnd_3_td, e145_ctrl_gnd_3 );
		RelayNetwork_PACU( e145_ctrl_gnd_1, e145_ctrl_gnd_2, e145_ctrl_gnd_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, e145_out_1, e145_out_2, e145_out_3 );

		// E31, E36
		bool e31_out_1;
		bool e31_out_2;
		bool e31_out_3;
		TimeDelay( 0.2, e145_out_1, dt, e31_ctrl_gnd_1_td, e31_ctrl_gnd_1 );
		TimeDelay( 0.2, e145_out_2, dt, e31_ctrl_gnd_2_td, e31_ctrl_gnd_2 );
		TimeDelay( 0.2, e145_out_3, dt, e31_ctrl_gnd_3_td, e31_ctrl_gnd_3 );
		MomentaryRelays( e31_ctrl_gnd_1, e31_ctrl_gnd_2, e31_ctrl_gnd_3, io.pwr_a, io.pwr_b, io.pwr_c, e145_out_1, e145_out_2, e145_out_3, tmp1, tmp2, tmp3, e31_out_1, e31_out_2, e31_out_3 );

		// E149
		bool e149_out_1;
		bool e149_out_2;
		bool e149_out_3;
		MomentaryRelays( io.open_latches, io.open_latches, io.open_latches, pwr_cntl_pnl_a, pwr_cntl_pnl_b, pwr_cntl_pnl_c, gnd_blamb, gnd_blamb, gnd_blamb, e149_out_1, e149_out_2, e149_out_3, tmp1, tmp2, tmp3 );

		// E112
		MomentaryRelays( e149_out_1 && e31_out_1, e149_out_2 && e31_out_2, e149_out_3 && e31_out_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, io.latches_op_cmd_1, io.latches_op_cmd_2, io.latches_op_cmd_3, tmp1, tmp2, tmp3 );

		// E150
		MomentaryRelays( io.close_latches, io.close_latches, io.close_latches, pwr_cntl_pnl_a, pwr_cntl_pnl_b, pwr_cntl_pnl_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, io.latches_cl_cmd_1, io.latches_cl_cmd_2, io.latches_cl_cmd_3, tmp1, tmp2, tmp3 );

		// E151
		MomentaryRelays( io.latches_op_ind_1 && io.latches_op_ind_2, io.latches_op_ind_1, io.latches_op_ind_2, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_pnl, io.gnd_pnl, io.gnd_pnl, io.latchesopen_light_1, io.latchesopen_light_2, io.latchesopen_light_3, tmp1, tmp2, tmp3 );

		// E115
		bool e115_out_1;
		bool e115_out_2;
		bool e115_out_3;
		MomentaryRelays( io.latches_op_ind_1 && io.latches_op_ind_2, io.latches_op_ind_1, io.latches_op_ind_2, io.pwr_a, io.pwr_b, io.pwr_c, io.lacu_ring_in_cmd_1, io.lacu_ring_in_cmd_2, io.lacu_ring_in_cmd_3, e115_out_1, e115_out_2, e115_out_3, tmp1, tmp2, tmp3 );

		// E111
		bool e111_out_1;
		bool e111_out_2;
		bool e111_out_3;
		MomentaryRelays( e115_out_1, e115_out_2, e115_out_3, io.pwr_a, io.pwr_b, io.pwr_c, gnd_ct1, gnd_ct2, gnd_ct3, e111_out_1, e111_out_2, e111_out_3, tmp1, tmp2, tmp3 );

		// E152
		MomentaryRelays( io.latches_cl_ind_1 && io.latches_cl_ind_2, io.latches_cl_ind_1, io.latches_cl_ind_2, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_pnl, io.gnd_pnl, io.gnd_pnl, io.latchesclosed_light_1, io.latchesclosed_light_2, io.latchesclosed_light_3, tmp1, tmp2, tmp3 );

		// power light
		MomentaryRelays( io.gnd_abc, io.gnd_abc, io.gnd_abc, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_pnl, io.gnd_pnl, io.gnd_pnl, io.power_on_light_1, io.power_on_light_2, io.power_on_light_3, tmp1, tmp2, tmp3 );

		// E177
		MomentaryRelays( io.interfacesealed_ind_1, io.interfacesealed_ind_2, io.interfacesealed_ind_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_pnl, io.gnd_pnl, io.gnd_pnl, io.interfsealed_light_1, io.interfsealed_light_2, io.interfsealed_light_3, tmp1, tmp2, tmp3 );

		// E184
		MomentaryRelays( e131_out_1, e131_out_2, e131_out_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_pnl, io.gnd_pnl, io.gnd_pnl, io.readytohook_light_1, io.readytohook_light_2, io.readytohook_light_3, tmp1, tmp2, tmp3 );

		// E222
		_2of3VotingRelay( gnd_blamb, gnd_blamb, gnd_blamb, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_pnl, io.gnd_pnl, io.apdscirprotoff_light_1, io.apdscirprotoff_light_2 );

		// E224
		_2of3VotingRelay( e226_out_1, e226_out_2, e226_out_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_pnl, io.gnd_pnl, io.undockcomplet_light_1, io.undockcomplet_light_2 );

		// E208
		bool e208_out_1;
		bool e208_out_2;
		bool e208_out_3;
		TimeDelay( 60.0, gnd_ct1, dt, e208_ctrl_gnd_1_td, e208_ctrl_gnd_1 );
		TimeDelay( 60.0, gnd_ct2, dt, e208_ctrl_gnd_2_td, e208_ctrl_gnd_2 );
		TimeDelay( 60.0, gnd_ct3, dt, e208_ctrl_gnd_3_td, e208_ctrl_gnd_3 );
		MomentaryRelays( e208_ctrl_gnd_1, e208_ctrl_gnd_2, e208_ctrl_gnd_3, io.pwr_a, io.pwr_b, io.pwr_c, gnd_ct1, gnd_ct2, gnd_ct3, e208_out_1, e208_out_2, e208_out_3, tmp1, tmp2, tmp3 );

		// E28, 30-1
		bool e28_out_1;
		bool e28_out_2;
		bool e28_out_3;
		TimeDelay( 0.2, e208_out_1, dt, e28_ctrl_gnd_1_td, e28_ctrl_gnd_1 );
		TimeDelay( 0.2, e208_out_2, dt, e28_ctrl_gnd_2_td, e28_ctrl_gnd_2 );
		TimeDelay( 0.2, e208_out_3, dt, e28_ctrl_gnd_3_td, e28_ctrl_gnd_3 );
		MomentaryRelays( e28_ctrl_gnd_1, e28_ctrl_gnd_2, e28_ctrl_gnd_3, io.pwr_a, io.pwr_b, io.pwr_c, e208_out_1, e208_out_2, e208_out_3, tmp1, tmp2, tmp3, e28_out_1, e28_out_2, e28_out_3 );

		// E144
		bool e144_out_1;
		bool e144_out_2;
		bool e144_out_3;
		MomentaryRelays( io.ring_out, io.ring_out, io.ring_out, io.pwr_a, io.pwr_b, io.pwr_c, gnd_blamb, gnd_blamb, gnd_blamb, e144_out_1, e144_out_2, e144_out_3, tmp1, tmp2, tmp3 );

		// E104
		MomentaryRelays( e144_out_1 && e28_out_1 && e35_out_1, e144_out_2 && e28_out_2 && e35_out_2, e144_out_3 && e28_out_3 && e35_out_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, io.ring_out_cmd_1, io.ring_out_cmd_2, io.ring_out_cmd_3, tmp1, tmp2, tmp3 );

		// E148, 106
		MomentaryRelays( io.ring_in && e148_out_1 && e111_out_1, io.ring_in && e148_out_2 && e111_out_2, io.ring_in && e148_out_3 && e111_out_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, e148_out_1, e148_out_2, e148_out_3, tmp1, tmp2, tmp3 );

		// E147, 110
		bool e147_out_1;
		bool e147_out_2;
		bool e147_out_3;
		MomentaryRelays( e148_out_1, e148_out_2, e148_out_3, io.pwr_a, io.pwr_b, io.pwr_c, io.ringfinalposition_ind_1, io.ringfinalposition_ind_1 && io.ringfinalposition_ind_2, io.ringfinalposition_ind_2, e147_out_1, e147_out_2, e147_out_3, tmp1, tmp2, tmp3 );

		// E206
		bool e206_out_1;
		bool e206_out_2;
		bool e206_out_3;
		TimeDelay( 10.0, e147_out_1, dt, e206_ctrl_gnd_1_td, e206_ctrl_gnd_1 );
		TimeDelay( 10.0, e147_out_2, dt, e206_ctrl_gnd_2_td, e206_ctrl_gnd_2 );
		TimeDelay( 10.0, e147_out_3, dt, e206_ctrl_gnd_3_td, e206_ctrl_gnd_3 );
		MomentaryRelays( e206_ctrl_gnd_1, e206_ctrl_gnd_2, e206_ctrl_gnd_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, e206_out_1, e206_out_2, e206_out_3, tmp1, tmp2, tmp3 );

		// E107, 137
		bool e107_out_1;
		bool e107_out_2;
		bool e107_out_3;
		MomentaryRelays( e206_out_1 && e173_out_1 && e175_out_1 && io.pwr_on_reset_1 && io.pwr_off_reset_1, e206_out_2 && e173_out_2 && e175_out_2 && io.pwr_on_reset_2 && io.pwr_off_reset_2, e206_out_3 && e173_out_3 && e175_out_3 && io.pwr_on_reset_3 && io.pwr_off_reset_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, e107_out_1, e107_out_2, e107_out_3, tmp1, tmp2, tmp3 );

		io.ring_in_stop_cmd_1 = e107_out_1;
		io.ring_in_stop_cmd_2 = e107_out_2;
		io.ring_in_stop_cmd_3 = e107_out_3;

		// E109
		MomentaryRelays( io.ringfinalposition_ind_1, io.ringfinalposition_ind_1 && io.ringfinalposition_ind_2, io.ringfinalposition_ind_2, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_pnl, io.gnd_pnl, io.gnd_pnl, io.ringfinalposition_light_1, io.ringfinalposition_light_2, io.ringfinalposition_light_3, tmp1, tmp2, tmp3 );

		// E143
		MomentaryRelays( io.ringforwardposition_ind_1, io.ringforwardposition_ind_1 && io.ringforwardposition_ind_2, io.ringforwardposition_ind_2, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_pnl, io.gnd_pnl, io.gnd_pnl, io.ringforwardposition_light_1, io.ringforwardposition_light_2, io.ringforwardposition_light_3, tmp1, tmp2, tmp3 );

		// E146
		MomentaryRelays( io.ringinitialposition_ind_1, io.ringinitialposition_ind_1 && io.ringinitialposition_ind_2, io.ringinitialposition_ind_2, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_pnl, io.gnd_pnl, io.gnd_pnl, io.ringinitialposition_light_1, io.ringinitialposition_light_2, io.ringinitialposition_light_3, tmp1, tmp2, tmp3 );

		// E178, 179, 133
		MomentaryRelays( e37_out_1 && io.fixeroff, e37_out_2 && io.fixeroff, e37_out_3 && io.fixeroff, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_pnl, io.gnd_pnl, io.gnd_pnl, io.fixersoff_light_1, io.fixersoff_light_2, io.fixersoff_light_3, tmp1, tmp2, tmp3 );

		// E37, 4-2
		MomentaryRelays( e1_out_off_1, e1_out_off_2, e1_out_off_3, io.pwr_a, io.pwr_b, io.pwr_c, io.fixersoff_light_1, io.fixersoff_light_2, io.fixersoff_light_3, tmp1, tmp2, tmp3, e37_out_1, e37_out_2, e37_out_3 );

		// E2-2, 3
		bool e2_2_out_1;
		bool e2_2_out_2;
		bool e2_2_out_3;
		MomentaryRelays( e37_out_1, e37_out_2, e37_out_3, io.pwr_a, io.pwr_b, io.pwr_c, e103_out_1, e103_out_2, e103_out_3, tmp1, tmp2, tmp3, e2_2_out_1, e2_2_out_2, e2_2_out_3 );

		// E223
		bool e223_out_1;
		bool e223_out_2;
		bool e223_out_3;
		MomentaryRelays( e2_2_out_1, e2_2_out_2, e2_2_out_3, io.pwr_a, io.pwr_b, io.pwr_c, io.ringinitialposition_ind_1 && io.ringinitialposition_ind_2, io.ringinitialposition_ind_1, io.ringinitialposition_ind_2, e223_out_1, e223_out_2, e223_out_3, tmp1, tmp2, tmp3 );

		// E204
		bool e204_out_1;
		bool e204_out_2;
		bool e204_out_3;
		TimeDelay( 1.0, e223_out_1, dt, e204_ctrl_gnd_1_td, e204_ctrl_gnd_1 );
		TimeDelay( 1.0, e223_out_2, dt, e204_ctrl_gnd_2_td, e204_ctrl_gnd_2 );
		TimeDelay( 1.0, e223_out_3, dt, e204_ctrl_gnd_3_td, e204_ctrl_gnd_3 );
		MomentaryRelays( e204_ctrl_gnd_1, e204_ctrl_gnd_2, e204_ctrl_gnd_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, e204_out_1, e204_out_2, e204_out_3, tmp1, tmp2, tmp3 );

		// E201
		bool e201_out_1;
		bool e201_out_2;
		bool e201_out_3;
		MomentaryRelays( e103_out_1 && e208_out_1, e103_out_2 && e208_out_2, e103_out_3 && e208_out_3, io.pwr_a, io.pwr_b, io.pwr_c, io.ringforwardposition_ind_1, io.ringforwardposition_ind_1 && io.ringforwardposition_ind_2, io.ringforwardposition_ind_2, e201_out_1, e201_out_2, e201_out_3, tmp1, tmp2, tmp3 );

		// E202
		bool e202_out_1;
		bool e202_out_2;
		bool e202_out_3;
		TimeDelay( 10.0, e201_out_1, dt, e202_ctrl_gnd_1_td, e202_ctrl_gnd_1 );
		TimeDelay( 10.0, e201_out_2, dt, e202_ctrl_gnd_2_td, e202_ctrl_gnd_2 );
		TimeDelay( 10.0, e201_out_3, dt, e202_ctrl_gnd_3_td, e202_ctrl_gnd_3 );
		MomentaryRelays( e202_ctrl_gnd_1, e202_ctrl_gnd_2, e202_ctrl_gnd_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, e202_out_1, e202_out_2, e202_out_3, tmp1, tmp2, tmp3 );

		// INFO moved 200ms delay from E136 to E1, 2 as that is where it makes sense
		// E136
		bool e136_out_1;
		bool e136_out_2;
		bool e136_out_3;
		MomentaryRelays( e145_out_1 && e202_out_1 && e204_out_1, e145_out_2 && e202_out_2 && e204_out_2, e145_out_3 && e202_out_3 && e204_out_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, e136_out_1, e136_out_2, e136_out_3, tmp1, tmp2, tmp3 );

		// E1, 2
		bool e1_out_on_1;
		bool e1_out_on_2;
		bool e1_out_on_3;
		TimeDelay( 0.2, e136_out_1, dt, e1_ctrl_gnd_1_td, e1_ctrl_gnd_1 );
		TimeDelay( 0.2, e136_out_2, dt, e1_ctrl_gnd_2_td, e1_ctrl_gnd_2 );
		TimeDelay( 0.2, e136_out_3, dt, e1_ctrl_gnd_3_td, e1_ctrl_gnd_3 );
		MomentaryRelays( e1_ctrl_gnd_1, e1_ctrl_gnd_2, e1_ctrl_gnd_3, io.pwr_a, io.pwr_b, io.pwr_c, e136_out_1, e136_out_2, e136_out_3, e1_out_on_1, e1_out_on_2, e1_out_on_3, e1_out_off_1, e1_out_off_2, e1_out_off_3 );

		// E105
		MomentaryRelays( e1_out_off_1 && io.pwr_on_reset_1 && io.pwr_off_reset_1, e1_out_off_2 && io.pwr_on_reset_2 && io.pwr_off_reset_2, e1_out_off_3 && io.pwr_on_reset_3 && io.pwr_off_reset_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, io.ring_out_stop_cmd_1, io.ring_out_stop_cmd_2, io.ring_out_stop_cmd_3, tmp1, tmp2, tmp3 );

		// E5, 6
		bool e5_out_on_1;
		bool e5_out_on_2;
		bool e5_out_on_3;
		bool e5_out_off_1;
		bool e5_out_off_2;
		bool e5_out_off_3;
		MomentaryRelays( e1_out_on_1, e1_out_on_2, e1_out_on_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, e5_out_on_1, e5_out_on_2, e5_out_on_3, e5_out_off_1, e5_out_off_2, e5_out_off_3 );

		// E103
		MomentaryRelays( e103_out_1 && e144_out_1, e103_out_2 && e144_out_2, e103_out_3 && e144_out_3, io.pwr_a, io.pwr_b, io.pwr_c, e5_out_off_1, e5_out_off_2, e5_out_off_3, e103_out_1, e103_out_2, e103_out_3, tmp1, tmp2, tmp3 );

		// E170, 17, 16-2
		MomentaryRelays( io.ringaligned_ind_1, io.ringaligned_ind_1 && io.ringaligned_ind_2, io.ringaligned_ind_2, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_pnl, io.gnd_pnl, io.gnd_pnl, tmp1, tmp2, tmp3, io.ringaligned_light_1, io.ringaligned_light_2, io.ringaligned_light_3 );

		// E26, 27-1
		bool e26_out_on_1;
		bool e26_out_on_2;
		bool e26_out_on_3;
		bool e26_out_off_1;
		bool e26_out_off_2;
		bool e26_out_off_3;
		MomentaryRelays( io.ringaligned_ind_1, io.ringaligned_ind_1 && io.ringaligned_ind_2, io.ringaligned_ind_2, io.pwr_a, io.pwr_b, io.pwr_c, e5_out_on_1, e5_out_on_2, e5_out_on_3, e26_out_on_1, e26_out_on_2, e26_out_on_3, e26_out_off_1, e26_out_off_2, e26_out_off_3 );

		// E120, E180, E29, 27-2
		bool e120_out_1;
		bool e120_out_2;
		bool e120_out_3;
		MomentaryRelays( e26_out_off_1, e26_out_off_2, e26_out_off_3, io.pwr_a, io.pwr_b, io.pwr_c, gnd_ct1, gnd_ct2, gnd_ct3, e120_out_1, e120_out_2, e120_out_3, tmp1, tmp2, tmp3 );

		// E108
		MomentaryRelays( io.ring_in && e111_out_1 && e120_out_1, io.ring_in && e111_out_2 && e120_out_2, io.ring_in && e111_out_3 && e120_out_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, io.ring_in_cmd_1, io.ring_in_cmd_2, io.ring_in_cmd_3, tmp1, tmp2, tmp3 );

		// E32, 4
		bool e32_out_1;
		bool e32_out_2;
		bool e32_out_3;
		MomentaryRelays( io.pwr_on_reset_1 && e1_out_off_1 && e107_out_1 && e37_out_1, io.pwr_on_reset_2 && e1_out_off_2 && e107_out_2 && e37_out_2, io.pwr_on_reset_3 && e1_out_off_3 && e107_out_3 && e37_out_3, io.pwr_a, io.pwr_b, io.pwr_c, e111_out_1 && e134_out_1 && e144_out_1 && e120_out_1 && io.ring_in_cmd_1, e111_out_2 && e134_out_2 && e144_out_2 && e120_out_2 && io.ring_in_cmd_2, e111_out_3 && e134_out_3 && e144_out_3 && e120_out_3 && io.ring_in_cmd_3, tmp1, tmp2, tmp3, e32_out_1, e32_out_2, e32_out_3 );

		// E134
		MomentaryRelays( e32_out_1, e32_out_2, e32_out_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, e134_out_1, e134_out_2, e134_out_3, tmp1, tmp2, tmp3 );

		// E168
		bool e168_out_1;
		bool e168_out_2;
		bool e168_out_3;
		MomentaryRelays( e202_out_1, e202_out_2, e202_out_3, io.pwr_a, io.pwr_b, io.pwr_c, e26_out_on_1, e26_out_on_2, e26_out_on_3, e168_out_1, e168_out_2, e168_out_3, tmp1, tmp2, tmp3 );

		// E19, 20-1, 30
		bool e19_out_1;
		bool e19_out_2;
		// TODO capture long indication lost before hooks closed
		_2of3VotingRelay_Off( e168_out_1, e168_out_2, e168_out_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, e19_out_1, e19_out_2 );

		// E21, 20-2
		bool e21_out_on_1;
		bool e21_out_on_2;
		bool e21_out_on_3;
		bool e21_out_off_1;
		bool e21_out_off_2;
		bool e21_out_off_3;
		MomentaryRelays( io.capturelong_ind_1 && io.capturelong_ind_2, io.capturelong_ind_1, io.capturelong_ind_2, io.pwr_a, io.pwr_b, io.pwr_c, e19_out_1 && e19_out_2, e19_out_1 && e19_out_2, e19_out_1 && e19_out_2, e21_out_on_1, e21_out_on_2, e21_out_on_3, e21_out_off_1, e21_out_off_2, e21_out_off_3 );

		// E101
		bool e101_out_1;
		bool e101_out_2;
		bool e101_out_3;
		TimeDelay( 0.05, io.pwr_on_reset_1, dt, e101_ctrl_gnd_1_td, e101_ctrl_gnd_1 );
		TimeDelay( 0.05, io.pwr_on_reset_2, dt, e101_ctrl_gnd_2_td, e101_ctrl_gnd_2 );
		TimeDelay( 0.05, io.pwr_on_reset_3, dt, e101_ctrl_gnd_3_td, e101_ctrl_gnd_3 );
		MomentaryRelays( e101_ctrl_gnd_1, e101_ctrl_gnd_2, e101_ctrl_gnd_3, io.pwr_a, io.pwr_b, io.pwr_c, e21_out_off_1, e21_out_off_2, e21_out_off_3, e101_out_1, e101_out_2, e101_out_3, tmp1, tmp2, tmp3 );

		// KP1, 2, 3
		bool kp1_out;
		bool kp2_out;
		bool kp3_out;
		LatchingRelay( io.pwr_a, e128_out_1, e101_out_1, kp1 );
		LatchingRelay( io.pwr_b, e128_out_2, e101_out_2, kp2 );
		LatchingRelay( io.pwr_c, e128_out_3, e101_out_3, kp3 );
		kp1_out = kp1 || io.gnd_abc;
		kp2_out = kp2 || io.gnd_abc;
		kp3_out = kp3 || io.gnd_abc;

		// E126
		bool e126_out_1;
		bool e126_out_2;
		bool e126_out_3;
		MomentaryRelays( io.captureshort_ind_1, io.captureshort_ind_1 && io.captureshort_ind_2, io.captureshort_ind_2, io.pwr_a, io.pwr_b, io.pwr_c, kp1_out, kp2_out, kp3_out, e126_out_1, e126_out_2, e126_out_3, tmp1, tmp2, tmp3 );

		// E128
		MomentaryRelays( e128_out_1 && e126_out_1, e128_out_2 && e126_out_2, e128_out_3 && e126_out_3, io.pwr_a, io.pwr_b, io.pwr_c, e21_out_on_1, e21_out_on_2, e21_out_on_3, e128_out_1, e128_out_2, e128_out_3, tmp1, tmp2, tmp3 );

		// E172
		MomentaryRelays( e128_out_1, e128_out_2, e128_out_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_pnl, io.gnd_pnl, io.gnd_pnl, io.capturecapture_light_1, io.capturecapture_light_2, io.capturecapture_light_3, tmp1, tmp2, tmp3 );

		// E22, 23-1
		bool e22_out_1;
		bool e22_out_2;
		bool e22_out_3;
		MomentaryRelays( io.ringfinalposition_ind_1, io.ringfinalposition_ind_1 && io.ringfinalposition_ind_2, io.ringfinalposition_ind_2, io.pwr_a, io.pwr_b, io.pwr_c, e128_out_1, e128_out_2, e128_out_3, tmp1, tmp2, tmp3, e22_out_1, e22_out_2, e22_out_3 );

		// K14, 15, 16
		MomentaryRelays( e22_out_1, e22_out_2, e22_out_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, gnd_ct1, gnd_ct2, gnd_ct3, tmp1, tmp2, tmp3 );

		// E139
		MomentaryRelays( e139_out_1 && e15_out_off_1, e139_out_2 && e15_out_off_2, e139_out_3 && e15_out_off_3, io.pwr_a, io.pwr_b, io.pwr_c, kp1_out, kp2_out, kp3_out, e139_out_1, e139_out_2, e139_out_3, tmp1, tmp2, tmp3 );

		// E15, 16-1
		// HACK split box to handle signal flow
		bool e15_out_on_1;
		bool e15_out_on_2;
		bool e15_out_on_3;
		MomentaryRelays( io.initialcontact_ind_1, io.initialcontact_ind_1 && io.initialcontact_ind_2, io.initialcontact_ind_2, io.pwr_a, io.pwr_b, io.pwr_c, e139_out_1, e139_out_2, e139_out_3, e15_out_on_1, e15_out_on_2, e15_out_on_3, tmp1, tmp2, tmp3 );
		MomentaryRelays( io.initialcontact_ind_1, io.initialcontact_ind_1 && io.initialcontact_ind_2, io.initialcontact_ind_2, io.pwr_a, io.pwr_b, io.pwr_c, io.ringinitialposition_ind_1, io.ringinitialposition_ind_1 && io.ringinitialposition_ind_2, io.ringinitialposition_ind_2, tmp1, tmp2, tmp3, e15_out_off_1, e15_out_off_2, e15_out_off_3 );

		// E140
		MomentaryRelays( e140_out_1 && e15_out_on_1, e140_out_2 && e15_out_on_2, e140_out_3 && e15_out_on_3, io.pwr_a, io.pwr_b, io.pwr_c, kp1_out, kp2_out, kp3_out, e140_out_1, e140_out_2, e140_out_3, tmp1, tmp2, tmp3 );

		// E186
		MomentaryRelays( e140_out_1, e140_out_2, e140_out_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_pnl, io.gnd_pnl, io.gnd_pnl, io.initialcontact_light_1, io.initialcontact_light_2, io.initialcontact_light_3, tmp1, tmp2, tmp3 );
		return;
	}

	void DSCU::Load( char* keyword, char* line )
	{
		if (!strcmp( keyword, "GND_CT" ))
		{
			LoadVarsOut( line, gnd_ct1, gnd_ct2, gnd_ct3 );
		}
		else if (!strcmp( keyword, "KP" ))
		{
			LoadVarsOut( line, kp1, kp2, kp3 );
		}
		else if (!strcmp( keyword, "E102_OUT" ))
		{
			LoadVarsOut( line, e102_out_1, e102_out_2, e102_out_3 );
		}
		else if (!strcmp( keyword, "E124_OUT" ))
		{
			LoadVarsOut( line, e124_out_1, e124_out_2, e124_out_3 );
		}
		else if (!strcmp( keyword, "E113_OUT" ))
		{
			LoadVarsOut( line, e113_out_1, e113_out_2, e113_out_3 );
		}
		else if (!strcmp( keyword, "E114_OUT" ))
		{
			LoadVarsOut( line, e114_out_1, e114_out_2, e114_out_3 );
		}
		else if (!strcmp( keyword, "E148_OUT" ))
		{
			LoadVarsOut( line, e148_out_1, e148_out_2, e148_out_3 );
		}
		else if (!strcmp( keyword, "E37_OUT" ))
		{
			LoadVarsOut( line, e37_out_1, e37_out_2, e37_out_3 );
		}
		else if (!strcmp( keyword, "E103_OUT" ))
		{
			LoadVarsOut( line, e103_out_1, e103_out_2, e103_out_3 );
		}
		else if (!strcmp( keyword, "E134_OUT" ))
		{
			LoadVarsOut( line, e134_out_1, e134_out_2, e134_out_3 );
		}
		else if (!strcmp( keyword, "E1_OUT_OFF" ))
		{
			LoadVarsOut( line, e1_out_off_1, e1_out_off_2, e1_out_off_3 );
		}
		else if (!strcmp( keyword, "E128_OUT" ))
		{
			LoadVarsOut( line, e128_out_1, e128_out_2, e128_out_3 );
		}
		else if (!strcmp( keyword, "E139_OUT" ))
		{
			LoadVarsOut( line, e139_out_1, e139_out_2, e139_out_3 );
		}
		else if (!strcmp( keyword, "E140_OUT" ))
		{
			LoadVarsOut( line, e140_out_1, e140_out_2, e140_out_3 );
		}
		else if (!strcmp( keyword, "E15_OUT_OFF" ))
		{
			LoadVarsOut( line, e15_out_off_1, e15_out_off_2, e15_out_off_3 );
		}
		else if (!strcmp( keyword, "E31_CTRL_GND" ))
		{
			LoadVarsTD( line, e31_ctrl_gnd_1, e31_ctrl_gnd_2, e31_ctrl_gnd_3, e31_ctrl_gnd_1_td, e31_ctrl_gnd_2_td, e31_ctrl_gnd_3_td );
		}
		else if (!strcmp( keyword, "E33_CTRL_GND" ))
		{
			LoadVarsTD( line, e33_ctrl_gnd_1, e33_ctrl_gnd_2, e33_ctrl_gnd_3, e33_ctrl_gnd_1_td, e33_ctrl_gnd_2_td, e33_ctrl_gnd_3_td );
		}
		else if (!strcmp( keyword, "E35_CTRL_GND" ))
		{
			LoadVarsTD( line, e35_ctrl_gnd_1, e35_ctrl_gnd_2, e35_ctrl_gnd_3, e35_ctrl_gnd_1_td, e35_ctrl_gnd_2_td, e35_ctrl_gnd_3_td );
		}
		else if (!strcmp( keyword, "E145_CTRL_GND" ))
		{
			LoadVarsTD( line, e145_ctrl_gnd_1, e145_ctrl_gnd_2, e145_ctrl_gnd_3, e145_ctrl_gnd_1_td, e145_ctrl_gnd_2_td, e145_ctrl_gnd_3_td );
		}
		else if (!strcmp( keyword, "E206_CTRL_GND" ))
		{
			LoadVarsTD( line, e206_ctrl_gnd_1, e206_ctrl_gnd_2, e206_ctrl_gnd_3, e206_ctrl_gnd_1_td, e206_ctrl_gnd_2_td, e206_ctrl_gnd_3_td );
		}
		else if (!strcmp( keyword, "E204_CTRL_GND" ))
		{
			LoadVarsTD( line, e204_ctrl_gnd_1, e204_ctrl_gnd_2, e204_ctrl_gnd_3, e204_ctrl_gnd_1_td, e204_ctrl_gnd_2_td, e204_ctrl_gnd_3_td );
		}
		else if (!strcmp( keyword, "E1_CTRL_GND" ))
		{
			LoadVarsTD( line, e1_ctrl_gnd_1, e1_ctrl_gnd_2, e1_ctrl_gnd_3, e1_ctrl_gnd_1_td, e1_ctrl_gnd_2_td, e1_ctrl_gnd_3_td );
		}
		else if (!strcmp( keyword, "E208_CTRL_GND" ))
		{
			LoadVarsTD( line, e208_ctrl_gnd_1, e208_ctrl_gnd_2, e208_ctrl_gnd_3, e208_ctrl_gnd_1_td, e208_ctrl_gnd_2_td, e208_ctrl_gnd_3_td );
		}
		else if (!strcmp( keyword, "E28_CTRL_GND" ))
		{
			LoadVarsTD( line, e28_ctrl_gnd_1, e28_ctrl_gnd_2, e28_ctrl_gnd_3, e28_ctrl_gnd_1_td, e28_ctrl_gnd_2_td, e28_ctrl_gnd_3_td );
		}
		else if (!strcmp( keyword, "E202_CTRL_GND" ))
		{
			LoadVarsTD( line, e202_ctrl_gnd_1, e202_ctrl_gnd_2, e202_ctrl_gnd_3, e202_ctrl_gnd_1_td, e202_ctrl_gnd_2_td, e202_ctrl_gnd_3_td );
		}
		else if (!strcmp( keyword, "E101_CTRL_GND" ))
		{
			LoadVarsTD( line, e101_ctrl_gnd_1, e101_ctrl_gnd_2, e101_ctrl_gnd_3, e101_ctrl_gnd_1_td, e101_ctrl_gnd_2_td, e101_ctrl_gnd_3_td );
		}
		else
		{
			// TODO unknown parameter
		}
		return;
	}

	void DSCU::Save( FILEHANDLE scn ) const
	{
		SaveVarsOut( scn, "GND_CT", gnd_ct1, gnd_ct2, gnd_ct3 );
		SaveVarsOut( scn, "KP", kp1, kp2, kp3 );
		SaveVarsOut( scn, "E102_OUT", e102_out_1, e102_out_2, e102_out_3 );
		SaveVarsOut( scn, "E124_OUT", e124_out_1, e124_out_2, e124_out_3 );
		SaveVarsOut( scn, "E113_OUT", e113_out_1, e113_out_2, e113_out_3 );
		SaveVarsOut( scn, "E114_OUT", e114_out_1, e114_out_2, e114_out_3 );
		SaveVarsOut( scn, "E148_OUT", e148_out_1, e148_out_2, e148_out_3 );
		SaveVarsOut( scn, "E37_OUT", e37_out_1, e37_out_2, e37_out_3 );
		SaveVarsOut( scn, "E103_OUT", e103_out_1, e103_out_2, e103_out_3 );
		SaveVarsOut( scn, "E134_OUT", e134_out_1, e134_out_2, e134_out_3 );
		SaveVarsOut( scn, "E1_OUT_OFF", e1_out_off_1, e1_out_off_2, e1_out_off_3 );
		SaveVarsOut( scn, "E128_OUT", e128_out_1, e128_out_2, e128_out_3 );
		SaveVarsOut( scn, "E139_OUT", e139_out_1, e139_out_2, e139_out_3 );
		SaveVarsOut( scn, "E140_OUT", e140_out_1, e140_out_2, e140_out_3 );
		SaveVarsOut( scn, "E15_OUT_OFF", e15_out_off_1, e15_out_off_2, e15_out_off_3 );
		SaveVarsTD( scn, "E31_CTRL_GND", e31_ctrl_gnd_1, e31_ctrl_gnd_2, e31_ctrl_gnd_3, e31_ctrl_gnd_1_td, e31_ctrl_gnd_2_td, e31_ctrl_gnd_3_td );
		SaveVarsTD( scn, "E33_CTRL_GND", e33_ctrl_gnd_1, e33_ctrl_gnd_2, e33_ctrl_gnd_3, e33_ctrl_gnd_1_td, e33_ctrl_gnd_2_td, e33_ctrl_gnd_3_td );
		SaveVarsTD( scn, "E35_CTRL_GND", e35_ctrl_gnd_1, e35_ctrl_gnd_2, e35_ctrl_gnd_3, e35_ctrl_gnd_1_td, e35_ctrl_gnd_2_td, e35_ctrl_gnd_3_td );
		SaveVarsTD( scn, "E145_CTRL_GND", e145_ctrl_gnd_1, e145_ctrl_gnd_2, e145_ctrl_gnd_3, e145_ctrl_gnd_1_td, e145_ctrl_gnd_2_td, e145_ctrl_gnd_3_td );
		SaveVarsTD( scn, "E206_CTRL_GND", e206_ctrl_gnd_1, e206_ctrl_gnd_2, e206_ctrl_gnd_3, e206_ctrl_gnd_1_td, e206_ctrl_gnd_2_td, e206_ctrl_gnd_3_td );
		SaveVarsTD( scn, "E204_CTRL_GND", e204_ctrl_gnd_1, e204_ctrl_gnd_2, e204_ctrl_gnd_3, e204_ctrl_gnd_1_td, e204_ctrl_gnd_2_td, e204_ctrl_gnd_3_td );
		SaveVarsTD( scn, "E1_CTRL_GND", e1_ctrl_gnd_1, e1_ctrl_gnd_2, e1_ctrl_gnd_3, e1_ctrl_gnd_1_td, e1_ctrl_gnd_2_td, e1_ctrl_gnd_3_td );
		SaveVarsTD( scn, "E208_CTRL_GND", e208_ctrl_gnd_1, e208_ctrl_gnd_2, e208_ctrl_gnd_3, e208_ctrl_gnd_1_td, e208_ctrl_gnd_2_td, e208_ctrl_gnd_3_td );
		SaveVarsTD( scn, "E28_CTRL_GND", e28_ctrl_gnd_1, e28_ctrl_gnd_2, e28_ctrl_gnd_3, e28_ctrl_gnd_1_td, e28_ctrl_gnd_2_td, e28_ctrl_gnd_3_td );
		SaveVarsTD( scn, "E202_CTRL_GND", e202_ctrl_gnd_1, e202_ctrl_gnd_2, e202_ctrl_gnd_3, e202_ctrl_gnd_1_td, e202_ctrl_gnd_2_td, e202_ctrl_gnd_3_td );
		SaveVarsTD( scn, "E101_CTRL_GND", e101_ctrl_gnd_1, e101_ctrl_gnd_2, e101_ctrl_gnd_3, e101_ctrl_gnd_1_td, e101_ctrl_gnd_2_td, e101_ctrl_gnd_3_td );
		return;
	}



	DMCU::DMCU( void ):
		K01(false), K02(false), K03(false), K04(false), K05(false), K06(false), K07(false), K08(false)
	{
		return;
	}

	void DMCU::Run( DMCU_IO& io )
	{
		bool tmp1;
		bool tmp2;
		bool tmp3;

		// E28
		bool e28_out_1;
		bool e28_out_2;
		bool e28_out_3;
		MomentaryRelays( io.ring_out_cmd_1, io.ring_out_cmd_2, io.ring_out_cmd_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, e28_out_1, e28_out_2, e28_out_3, tmp1, tmp2, tmp3 );

		// E29
		bool e29_out_1;
		bool e29_out_2;
		bool e29_out_3;
		MomentaryRelays( io.ring_out_stop_cmd_1, io.ring_out_stop_cmd_2, io.ring_out_stop_cmd_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, e29_out_1, e29_out_2, e29_out_3, tmp1, tmp2, tmp3 );

		// E30
		bool e30_out_1;
		bool e30_out_2;
		bool e30_out_3;
		MomentaryRelays( io.ring_in_cmd_1, io.ring_in_cmd_2, io.ring_in_cmd_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, e30_out_1, e30_out_2, e30_out_3, tmp1, tmp2, tmp3 );

		// E31
		bool e31_out_1;
		bool e31_out_2;
		bool e31_out_3;
		MomentaryRelays( io.ring_out_stop_cmd_1, io.ring_out_stop_cmd_2, io.ring_out_stop_cmd_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, e31_out_1, e31_out_2, e31_out_3, tmp1, tmp2, tmp3 );

		// K6
		bool k6 = io.pwr_a && !(e28_out_1 && e28_out_3 && e29_out_1 && e29_out_3 && e30_out_1 && e30_out_3 && e31_out_1 && e31_out_3);

		// K22
		bool k22 = io.pwr_c && !(e28_out_1 && e28_out_3 && e29_out_1 && e29_out_3 && e30_out_1 && e30_out_3 && e31_out_1 && e31_out_3);

		// K14
		bool k14 = io.pwr_a && !(e28_out_1 && e28_out_3 && e29_out_1 && e29_out_3 && e30_out_1 && e30_out_3 && e31_out_1 && e31_out_3);

		// K24
		bool k24 = io.pwr_c && !(e28_out_1 && e28_out_3 && e29_out_1 && e29_out_3 && e30_out_1 && e30_out_3 && e31_out_1 && e31_out_3);

		// K01
		{
			bool k5 = io.pwr_a && !e29_out_1;
			bool k1 = io.pwr_a && !K05 && !e28_out_1;

			if (io.pwr_a)
			{
				if (k5 && !io.gnd_abc)
				{
					K01 = false;
				}
				else if (!k5 && k1 && !io.gnd_abc)
				{
					K01 = true;
				}
			}
		}

		// K02
		{
			bool k8 = io.pwr_c && !e29_out_3;
			bool k3 = io.pwr_c && !K07 && !e28_out_2;

			if (io.pwr_c)
			{
				if (k8 && !io.gnd_abc)
				{
					K02 = false;
				}
				else if (!k8 && k3 && !io.gnd_abc)
				{
					K02 = true;
				}
			}
		}

		// K03
		{
			bool k7 = io.pwr_b && !e29_out_2;
			bool k2 = io.pwr_b && !K06 && !e28_out_3;

			if (io.pwr_b)
			{
				if (k7 && !io.gnd_abc)
				{
					K03 = false;
				}
				else if (!k7 && k2 && !io.gnd_abc)
				{
					K03 = true;
				}
			}
		}

		// K04
		{
			bool k21 = io.pwr_a && !(e29_out_1 && e29_out_3);
			bool k17 = io.pwr_a && !K08 && !(e28_out_1 && e28_out_3);

			if ((io.pwr_a && k6 && !k22) || (io.pwr_c && k22) || (io.pwr_a && k14 && !k24) || (io.pwr_c && k24))
			{
				if (k21 && !io.gnd_abc)
				{
					K04 = false;
				}
				else if (!k21 && k17 && !io.gnd_abc)
				{
					K04 = true;
				}
			}
		}

		// K05
		{
			bool k13 = io.pwr_a && !e31_out_1;
			bool k9 = io.pwr_a && !K01 && !e30_out_1;

			if (io.pwr_a)
			{
				if (k13 && !io.gnd_abc)
				{
					K05 = false;
				}
				else if (!k13 && k9 && !io.gnd_abc)
				{
					K05 = true;
				}
			}
		}

		// K06
		{
			bool k16 = io.pwr_c && !e31_out_3;
			bool k12 = io.pwr_c && !K03 && !e30_out_2;

			if (io.pwr_c)
			{
				if (k16 && !io.gnd_abc)
				{
					K06 = false;
				}
				else if (!k16 && k12 && !io.gnd_abc)
				{
					K06 = true;
				}
			}
		}

		// K07
		{
			bool k15 = io.pwr_b && !e31_out_2;
			bool k11 = io.pwr_b && !K02 && !e30_out_3;

			if (io.pwr_b)
			{
				if (k15 && !io.gnd_abc)
				{
					K07 = false;
				}
				else if (!k15 && k11 && !io.gnd_abc)
				{
					K07 = true;
				}
			}
		}

		// K08
		{
			bool k23 = io.pwr_a && !(e31_out_1 && e31_out_3);
			bool k19 = io.pwr_a && !K04 && !(e30_out_1 && e30_out_3);

			if ((io.pwr_a && k6 && !k22) || (io.pwr_c && k22) || (io.pwr_a && k14 && !k24) || (io.pwr_c && k24))
			{
				if (k23 && !io.gnd_abc)
				{
					K08 = false;
				}
				else if (!k23 && k19 && !io.gnd_abc)
				{
					K08 = true;
				}
			}
		}

		// motor power/ground
		// output: 0=off; +1=extend; -1=retract
		io.motor_1_pwr_a1 = 0;
		io.motor_1_pwr_a2 = 0;

		if ((K03 && K04) && (!K07 || !K08))
		{
			if (io.pwr_c1) io.motor_1_pwr_a1 = 1;
		}
		else if ((K07 && K08) && (!K03 || !K04))
		{
			if (!io.gnd_c1) io.motor_1_pwr_a1 = -1;
		}

		if ((K01 && K02) && (!K05 || !K06))
		{
			if (io.pwr_c1) io.motor_1_pwr_a2 = 1;
		}
		else if ((K05 && K06) && (!K01 || !K02))
		{
			if (!io.gnd_c1) io.motor_1_pwr_a2 = -1;
		}

		io.motor_1_pwr_b1 = 0;
		io.motor_1_pwr_b2 = 0;

		if ((K05 && K06) && (!K01 || !K02))
		{
			if (io.pwr_c1) io.motor_1_pwr_b1 = 1;
		}
		else if ((K01 && K02) && (!K05 || !K06))
		{
			if (!io.gnd_c1) io.motor_1_pwr_b1 = -1;
		}

		if ((K07 && K08) && (!K03 || !K04))
		{
			if (io.pwr_c1) io.motor_1_pwr_b2 = 1;
		}
		else if ((K03 && K04) && (!K07 || !K08))
		{
			if (!io.gnd_c1) io.motor_1_pwr_b2 = -1;
		}

		io.motor_2_pwr_a1 = 0;
		io.motor_2_pwr_a2 = 0;

		if ((K03 && K04) && (!K07 || !K08))
		{
			if (io.pwr_c2) io.motor_2_pwr_a1 = 1;
		}
		else if ((K07 && K08) && (!K03 || !K04))
		{
			if (!io.gnd_c2) io.motor_2_pwr_a1 = -1;
		}

		if ((K01 && K02) && (!K05 || !K06))
		{
			if (io.pwr_c2) io.motor_2_pwr_a2 = 1;
		}
		else if ((K05 && K06) && (!K01 || !K02))
		{
			if (!io.gnd_c2) io.motor_2_pwr_a2 = -1;
		}

		io.motor_2_pwr_b1 = 0;
		io.motor_2_pwr_b2 = 0;

		if ((K05 && K06) && (!K01 || !K02))
		{
			if (io.pwr_c2) io.motor_2_pwr_b1 = 1;
		}
		else if ((K01 && K02) && (!K05 || !K06))
		{
			if (!io.gnd_c2) io.motor_2_pwr_b1 = -1;
		}

		if ((K07 && K08) && (!K03 || !K04))
		{
			if (io.pwr_c2) io.motor_2_pwr_b2 = 1;
		}
		else if ((K03 && K04) && (!K07 || !K08))
		{
			if (!io.gnd_c2) io.motor_2_pwr_b2 = -1;
		}
		return;
	}

	void DMCU::Load( char* keyword, char* line )
	{
		int itmp;

		if (!strcmp( keyword, "K01" ))
		{
			sscanf_s( line, "%d", &itmp );
			K01 = (itmp == 1);
		}
		else if (!strcmp( keyword, "K02" ))
		{
			sscanf_s( line, "%d", &itmp );
			K02 = (itmp == 1);
		}
		else if (!strcmp( keyword, "K03" ))
		{
			sscanf_s( line, "%d", &itmp );
			K03 = (itmp == 1);
		}
		else if (!strcmp( keyword, "K04" ))
		{
			sscanf_s( line, "%d", &itmp );
			K04 = (itmp == 1);
		}
		else if (!strcmp( keyword, "K05" ))
		{
			sscanf_s( line, "%d", &itmp );
			K05 = (itmp == 1);
		}
		else if (!strcmp( keyword, "K06" ))
		{
			sscanf_s( line, "%d", &itmp );
			K06 = (itmp == 1);
		}
		else if (!strcmp( keyword, "K07" ))
		{
			sscanf_s( line, "%d", &itmp );
			K07 = (itmp == 1);
		}
		else if (!strcmp( keyword, "K08" ))
		{
			sscanf_s( line, "%d", &itmp );
			K08 = (itmp == 1);
		}
		else
		{
			// TODO unknown parameter
		}
		return;
	}

	void DMCU::Save( FILEHANDLE scn ) const
	{
		oapiWriteScenario_int( scn, "K01", K01 );
		oapiWriteScenario_int( scn, "K02", K02 );
		oapiWriteScenario_int( scn, "K03", K03 );
		oapiWriteScenario_int( scn, "K04", K04 );
		oapiWriteScenario_int( scn, "K05", K05 );
		oapiWriteScenario_int( scn, "K06", K06 );
		oapiWriteScenario_int( scn, "K07", K07 );
		oapiWriteScenario_int( scn, "K08", K08 );
		return;
	}



	PACU::PACU( void ):
		e21a_off_out_1_m1(true), e21a_off_out_2_m1(true), e21a_off_out_3_m1(true), e21a_on_out_1_m1(true), e21a_on_out_2_m1(true), e21a_on_out_3_m1(true),
		e21a_off_out_1_m2(true), e21a_off_out_2_m2(true), e21a_off_out_3_m2(true), e21a_on_out_1_m2(true), e21a_on_out_2_m2(true), e21a_on_out_3_m2(true),
		e21b_off_out_1_m1(true), e21b_off_out_2_m1(true), e21b_off_out_3_m1(true), e21b_on_out_1_m1(true), e21b_on_out_2_m1(true), e21b_on_out_3_m1(true),
		e21b_off_out_1_m2(true), e21b_off_out_2_m2(true), e21b_off_out_3_m2(true), e21b_on_out_1_m2(true), e21b_on_out_2_m2(true), e21b_on_out_3_m2(true),
		e30_ctrl_gnd_1_m1(true), e30_ctrl_gnd_2_m1(true), e30_ctrl_gnd_3_m1(true), e30_ctrl_gnd_1_td_m1(-1.0), e30_ctrl_gnd_2_td_m1(-1.0), e30_ctrl_gnd_3_td_m1(-1.0),
		e30_ctrl_gnd_1_m2(true), e30_ctrl_gnd_2_m2(true), e30_ctrl_gnd_3_m2(true), e30_ctrl_gnd_1_td_m2(-1.0), e30_ctrl_gnd_2_td_m2(-1.0), e30_ctrl_gnd_3_td_m2(-1.0),
		e31_ctrl_gnd_1_m1(true), e31_ctrl_gnd_2_m1(true), e31_ctrl_gnd_3_m1(true), e31_ctrl_gnd_1_td_m1(-1.0), e31_ctrl_gnd_2_td_m1(-1.0), e31_ctrl_gnd_3_td_m1(-1.0),
		e31_ctrl_gnd_1_m2(true), e31_ctrl_gnd_2_m2(true), e31_ctrl_gnd_3_m2(true), e31_ctrl_gnd_1_td_m2(-1.0), e31_ctrl_gnd_2_td_m2(-1.0), e31_ctrl_gnd_3_td_m2(-1.0)
	{
		return;
	}

	void PACU::Run( const double dt, PACU_IO& io )
	{
		io.hooks_cl_ind_1 = io.hooks_cl_ind_a;
		io.hooks_cl_ind_2 = io.hooks_cl_ind_a && io.hooks_cl_ind_b;
		io.hooks_cl_ind_3 = io.hooks_cl_ind_b;

		io.hooks_op_ind_1 = io.hooks_op_ind_a;
		io.hooks_op_ind_2 = io.hooks_op_ind_a && io.hooks_op_ind_b;
		io.hooks_op_ind_3 = io.hooks_op_ind_b;

		bool tmp1;
		bool tmp2;
		bool tmp3;

		//// Motor 1
		{
			// E50
			bool e50_out_1;
			bool e50_out_2;
			bool e50_out_3;
			RelayNetwork_PACU( io.hooks_op_cmd_1, io.hooks_op_cmd_2, io.hooks_op_cmd_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, e50_out_1, e50_out_2, e50_out_3 );

			// E51
			bool e51_out_1;
			bool e51_out_2;
			bool e51_out_3;
			RelayNetwork_PACU( io.hooks_cl_cmd_1, io.hooks_cl_cmd_2, io.hooks_cl_cmd_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, e51_out_1, e51_out_2, e51_out_3 );

			// E1A, 2A, 3A
			// HACK split box to handle signal flow
			bool e1a_out_1;
			bool e1a_out_2;
			bool e1a_out_3;
			MomentaryRelays( e50_out_3 && e21b_off_out_1_m1, e50_out_2 && e21b_off_out_2_m1, e50_out_1 && e21b_off_out_3_m1, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, e1a_out_1, e1a_out_2, e1a_out_3, tmp1, tmp2, tmp3 );
			MomentaryRelays( e50_out_3 && e21b_off_out_1_m1, e50_out_2 && e21b_off_out_2_m1, e50_out_1 && e21b_off_out_3_m1, io.pwr_a, io.pwr_b, io.pwr_c, e21b_on_out_1_m1, e21b_on_out_2_m1, e21b_on_out_3_m1, tmp1, tmp2, tmp3, io.gnd_hooks_cl_1, io.gnd_hooks_cl_2, io.gnd_hooks_cl_3 );

			// E4B, 5B, 6B
			bool e4b_out_1;
			bool e4b_out_2;
			bool e4b_out_3;
			MomentaryRelays( e51_out_1 && e21a_off_out_1_m1, e51_out_2 && e21a_off_out_2_m1, e51_out_3 && e21a_off_out_3_m1, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, e4b_out_1, e4b_out_2, e4b_out_3, tmp1, tmp2, tmp3 );

			// E30, 44
			bool e30_out_1;
			bool e30_out_2;
			bool e30_out_3;
			TimeDelay( 0.5, e1a_out_1 && e21b_on_out_1_m1, dt, e30_ctrl_gnd_1_td_m1, e30_ctrl_gnd_1_m1 );
			TimeDelay( 0.5, e1a_out_2 && e21b_on_out_2_m1, dt, e30_ctrl_gnd_2_td_m1, e30_ctrl_gnd_2_m1 );
			TimeDelay( 0.5, e1a_out_3 && e21b_on_out_3_m1, dt, e30_ctrl_gnd_3_td_m1, e30_ctrl_gnd_3_m1 );
			MomentaryRelays( e30_ctrl_gnd_1_m1, e30_ctrl_gnd_2_m1, e30_ctrl_gnd_3_m1, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, e30_out_1, e30_out_2, e30_out_3, tmp1, tmp2, tmp3 );

			// E31, 45
			bool e31_out_1;
			bool e31_out_2;
			TimeDelay( 0.5, e4b_out_1 && e21a_on_out_1_m1, dt, e31_ctrl_gnd_1_td_m1, e31_ctrl_gnd_1_m1 );
			TimeDelay( 0.5, e4b_out_2 && e21a_on_out_2_m1, dt, e31_ctrl_gnd_2_td_m1, e31_ctrl_gnd_2_m1 );
			TimeDelay( 0.5, e4b_out_3 && e21a_on_out_3_m1, dt, e31_ctrl_gnd_3_td_m1, e31_ctrl_gnd_3_m1 );
			{
				// custom circuit
				bool k1 = !e31_ctrl_gnd_1_m1 && io.pwr_a;
				bool k2 = !e31_ctrl_gnd_2_m1 && io.pwr_b;
				bool k3 = !e31_ctrl_gnd_3_m1 && io.pwr_c;

				// HACK info not clear
				bool o1 = k1 && (k2 || k3);
				bool o2 = k1 && (k2 || k3);

				e31_out_1 = io.gnd_abc || !o1;
				e31_out_2 = io.gnd_abc || !o2;
			}

			// E21A, 22A, 23A
			// HACK split box to handle signal flow
			MomentaryRelays( e30_out_1, e30_out_2, e30_out_3, io.pwr_a, io.pwr_b, io.pwr_c, e4b_out_1, e4b_out_2, e4b_out_3, tmp1, tmp2, tmp3, e21a_off_out_1_m1, e21a_off_out_2_m1, e21a_off_out_3_m1 );
			MomentaryRelays( e30_out_1, e30_out_2, e30_out_3, io.pwr_a, io.pwr_b, io.pwr_c, io.hooks_op_ind_1, io.hooks_op_ind_2, io.hooks_op_ind_3, e21a_on_out_1_m1, e21a_on_out_2_m1, e21a_on_out_3_m1, tmp1, tmp2, tmp3 );

			// E21B, 22B, 23B
			// HACK split box to handle signal flow
			MomentaryRelays( e31_out_1 && e31_out_2, e31_out_1 && e31_out_2, e31_out_1 && e31_out_2, io.pwr_a, io.pwr_b, io.pwr_c, e1a_out_1, e1a_out_2, e1a_out_3, tmp1, tmp2, tmp3, e21b_off_out_1_m1, e21b_off_out_2_m1, e21b_off_out_3_m1 );
			MomentaryRelays( e31_out_1 && e31_out_2, e31_out_1 && e31_out_2, e31_out_1 && e31_out_2, io.pwr_a, io.pwr_b, io.pwr_c, io.hooks_cl_ind_1, io.hooks_cl_ind_2, io.hooks_cl_ind_3, e21b_on_out_1_m1, e21b_on_out_2_m1, e21b_on_out_3_m1, tmp1, tmp2, tmp3 );

			// E1B, 2B, 3B
			bool e1b_out_1;
			bool e1b_out_2;
			bool e1b_out_3;
			MomentaryRelays( e50_out_3 && e21b_off_out_1_m1, e50_out_2 && e21b_off_out_2_m1, e50_out_1 && e21b_off_out_3_m1, io.pwr_a, io.pwr_b, io.pwr_c, e21a_off_out_1_m1, e21a_off_out_2_m1, e21a_off_out_3_m1, tmp1, tmp2, tmp3, e1b_out_1, e1b_out_2, e1b_out_3 );

			// E4A, 5A, 6A
			bool e4a_out_1;
			bool e4a_out_2;
			bool e4a_out_3;
			MomentaryRelays( e51_out_1 && e21a_off_out_1_m1, e51_out_2 && e21a_off_out_2_m1, e51_out_3 && e21a_off_out_3_m1, io.pwr_a, io.pwr_b, io.pwr_c, e21b_off_out_1_m1, e21b_off_out_2_m1, e21b_off_out_3_m1, tmp1, tmp2, tmp3, e4a_out_1, e4a_out_2, e4a_out_3 );

			// K
			bool K4 = io.pwr_a && !e1b_out_1;
			bool K7 = io.pwr_a && !e1b_out_1;
			bool K5 = io.pwr_b && !e1b_out_2;
			bool K8 = io.pwr_b && !e1b_out_2;
			bool K6 = io.pwr_c && !e1b_out_3;
			bool K9 = io.pwr_c && !e1b_out_3;

			bool K1 = io.pwr_a && !e4a_out_3;
			bool K10 = io.pwr_a && !e4a_out_3;
			bool K2 = io.pwr_b && !e4a_out_2;
			bool K11 = io.pwr_b && !e4a_out_2;
			bool K3 = io.pwr_c && !e4a_out_1;
			bool K12 = io.pwr_c && !e4a_out_1;

			// motor power/ground
			// output: 0=off; +1=open; -1=close
			io.motor_1_pwr_a1 = 0;
			io.motor_1_pwr_a2 = 0;

			if ((!K1 && !K2 && K4 && K6) || (!K1 && K2 && !K3 && K5 && K6) || (!K1 && K2 && !K3 && K4 && K5))
			{
				if (io.pwr_1) io.motor_1_pwr_a1 = 1;
			}
			else if (K1 && K3)
			{
				if (!io.gnd_1) io.motor_1_pwr_a1 = -1;
			}

			if ((!K2 && !K3 && K5 && K6) || (!K2 && !K3 && K4 && K5))
			{
				if (io.pwr_1) io.motor_1_pwr_a2 = 1;
			}
			else if ((K2 && K3) || (K1 && K2))
			{
				if (!io.gnd_1) io.motor_1_pwr_a2 = -1;
			}

			io.motor_1_pwr_b1 = 0;
			io.motor_1_pwr_b2 = 0;

			if ((!K7 && !K8 && K10 && K12) || (!K7 && K8 && !K9 && K11 && K12) || (!K7 && K8 && !K9 && K10 && K11))
			{
				if (io.pwr_1) io.motor_1_pwr_b1 = 1;
			}
			else if (K7 && K9)
			{
				if (!io.gnd_1) io.motor_1_pwr_b1 = -1;
			}

			if ((!K8 && !K9 && K11 && K12) || (!K8 && !K9 && K10 && K11))
			{
				if (io.pwr_1) io.motor_1_pwr_b2 = 1;
			}
			else if ((K8 && K9) || (K7 && K8))
			{
				if (!io.gnd_1) io.motor_1_pwr_b2 = -1;
			}
		}

		//// Motor 2
		{
			// E52
			bool e52_out_1;
			bool e52_out_2;
			bool e52_out_3;
			RelayNetwork_PACU( io.hooks_op_cmd_1, io.hooks_op_cmd_2, io.hooks_op_cmd_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, e52_out_1, e52_out_2, e52_out_3 );

			// E53
			bool e53_out_1;
			bool e53_out_2;
			bool e53_out_3;
			RelayNetwork_PACU( io.hooks_cl_cmd_1, io.hooks_cl_cmd_2, io.hooks_cl_cmd_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, e53_out_1, e53_out_2, e53_out_3 );

			// E1A, 2A, 3A
			// HACK split box to handle signal flow
			bool e1a_out_1;
			bool e1a_out_2;
			bool e1a_out_3;
			MomentaryRelays( e52_out_3 && e21b_off_out_1_m2, e52_out_2 && e21b_off_out_2_m2, e52_out_1 && e21b_off_out_3_m2, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, e1a_out_1, e1a_out_2, e1a_out_3, tmp1, tmp2, tmp3 );

			// E4B, 5B, 6B
			bool e4b_out_1;
			bool e4b_out_2;
			bool e4b_out_3;
			MomentaryRelays( e53_out_1 && e21a_off_out_1_m1, e53_out_2 && e21a_off_out_2_m1, e53_out_3 && e21a_off_out_3_m1, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, e4b_out_1, e4b_out_2, e4b_out_3, tmp1, tmp2, tmp3 );

			// E30, 44
			bool e30_out_1;
			bool e30_out_2;
			bool e30_out_3;
			TimeDelay( 0.5, e1a_out_1 && e21b_on_out_1_m2, dt, e30_ctrl_gnd_1_td_m2, e30_ctrl_gnd_1_m2 );
			TimeDelay( 0.5, e1a_out_2 && e21b_on_out_2_m2, dt, e30_ctrl_gnd_2_td_m2, e30_ctrl_gnd_2_m2 );
			TimeDelay( 0.5, e1a_out_3 && e21b_on_out_3_m2, dt, e30_ctrl_gnd_3_td_m2, e30_ctrl_gnd_3_m2 );
			MomentaryRelays( e30_ctrl_gnd_1_m2, e30_ctrl_gnd_2_m2, e30_ctrl_gnd_3_m2, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, e30_out_1, e30_out_2, e30_out_3, tmp1, tmp2, tmp3 );

			// E31, 45
			bool e31_out_1;
			bool e31_out_2;
			TimeDelay( 0.5, e4b_out_1 && e21a_on_out_1_m2, dt, e31_ctrl_gnd_1_td_m2, e31_ctrl_gnd_1_m2 );
			TimeDelay( 0.5, e4b_out_2 && e21a_on_out_2_m2, dt, e31_ctrl_gnd_2_td_m2, e31_ctrl_gnd_2_m2 );
			TimeDelay( 0.5, e4b_out_3 && e21a_on_out_3_m2, dt, e31_ctrl_gnd_3_td_m2, e31_ctrl_gnd_3_m2 );
			{
				// custom circuit
				bool k1 = !e31_ctrl_gnd_1_m2 && io.pwr_a;
				bool k2 = !e31_ctrl_gnd_2_m2 && io.pwr_b;
				bool k3 = !e31_ctrl_gnd_3_m2 && io.pwr_c;

				// HACK info not clear
				bool o1 = k1 && (k2 || k3);
				bool o2 = k1 && (k2 || k3);

				e31_out_1 = io.gnd_abc || !o1;
				e31_out_2 = io.gnd_abc || !o2;
			}

			// E21A, 22A, 23A
			// HACK split box to handle signal flow
			MomentaryRelays( e30_out_1, e30_out_2, e30_out_3, io.pwr_a, io.pwr_b, io.pwr_c, e4b_out_1, e4b_out_2, e4b_out_3, tmp1, tmp2, tmp3, e21a_off_out_1_m2, e21a_off_out_2_m2, e21a_off_out_3_m2 );
			MomentaryRelays( e30_out_1, e30_out_2, e30_out_3, io.pwr_a, io.pwr_b, io.pwr_c, io.hooks_op_ind_1, io.hooks_op_ind_2, io.hooks_op_ind_3, e21a_on_out_1_m2, e21a_on_out_2_m2, e21a_on_out_3_m2, tmp1, tmp2, tmp3 );

			// E21B, 22B, 23B
			// HACK split box to handle signal flow
			MomentaryRelays( e31_out_1 && e31_out_2, e31_out_1 && e31_out_2, e31_out_1 && e31_out_2, io.pwr_a, io.pwr_b, io.pwr_c, e1a_out_1, e1a_out_2, e1a_out_3, tmp1, tmp2, tmp3, e21b_off_out_1_m2, e21b_off_out_2_m2, e21b_off_out_3_m2 );
			MomentaryRelays( e31_out_1 && e31_out_2, e31_out_1 && e31_out_2, e31_out_1 && e31_out_2, io.pwr_a, io.pwr_b, io.pwr_c, io.hooks_cl_ind_1, io.hooks_cl_ind_2, io.hooks_cl_ind_3, e21b_on_out_1_m2, e21b_on_out_2_m2, e21b_on_out_3_m2, tmp1, tmp2, tmp3 );

			// E1B, 2B, 3B
			bool e1b_out_1;
			bool e1b_out_2;
			bool e1b_out_3;
			MomentaryRelays( e52_out_3 && e21b_off_out_1_m2, e52_out_2 && e21b_off_out_2_m2, e52_out_1 && e21b_off_out_3_m2, io.pwr_a, io.pwr_b, io.pwr_c, e21a_off_out_1_m2, e21a_off_out_2_m2, e21a_off_out_3_m2, tmp1, tmp2, tmp3, e1b_out_1, e1b_out_2, e1b_out_3 );

			// E4A, 5A, 6A
			bool e4a_out_1;
			bool e4a_out_2;
			bool e4a_out_3;
			MomentaryRelays( e53_out_1 && e21a_off_out_1_m2, e53_out_2 && e21a_off_out_2_m2, e53_out_3 && e21a_off_out_3_m2, io.pwr_a, io.pwr_b, io.pwr_c, e21b_off_out_1_m2, e21b_off_out_2_m2, e21b_off_out_3_m2, tmp1, tmp2, tmp3, e4a_out_1, e4a_out_2, e4a_out_3 );

			// K
			bool K16 = io.pwr_a && !e1b_out_1;
			bool K19 = io.pwr_a && !e1b_out_1;
			bool K17 = io.pwr_b && !e1b_out_2;
			bool K20 = io.pwr_b && !e1b_out_2;
			bool K18 = io.pwr_c && !e1b_out_3;
			bool K21 = io.pwr_c && !e1b_out_3;

			bool K13 = io.pwr_a && !e4a_out_3;
			bool K22 = io.pwr_a && !e4a_out_3;
			bool K14 = io.pwr_b && !e4a_out_2;
			bool K23 = io.pwr_b && !e4a_out_2;
			bool K15 = io.pwr_c && !e4a_out_1;
			bool K24 = io.pwr_c && !e4a_out_1;

			// motor power/ground
			// output: 0=off; +1=open; -1=close
			io.motor_2_pwr_a1 = 0;
			io.motor_2_pwr_a2 = 0;

			if ((!K13 && !K14 && K16 && K18) || (!K13 && K14 && !K15 && K17 && K18) || (!K13 && K14 && !K15 && K16 && K17))
			{
				if (io.pwr_2) io.motor_2_pwr_a1 = 1;
			}
			else if (K13 && K15)
			{
				if (!io.gnd_2) io.motor_2_pwr_a1 = -1;
			}

			if ((!K14 && !K15 && K17 && K18) || (!K14 && !K15 && K16 && K17))
			{
				if (io.pwr_2) io.motor_2_pwr_a2 = 1;
			}
			else if ((K14 && K15) || (K13 && K14))
			{
				if (!io.gnd_2) io.motor_2_pwr_a2 = -1;
			}

			io.motor_2_pwr_b1 = 0;
			io.motor_2_pwr_b2 = 0;

			if ((!K19 && !K20 && K22 && K24) || (!K19 && K20 && !K21 && K23 && K24) || (!K19 && K20 && !K21 && K22 && K23))
			{
				if (io.pwr_2) io.motor_2_pwr_b1 = 1;
			}
			else if (K19 && K21)
			{
				if (!io.gnd_2) io.motor_2_pwr_b1 = -1;
			}

			if ((!K20 && !K21 && K23 && K24) || (!K20 && !K21 && K22 && K23))
			{
				if (io.pwr_2) io.motor_2_pwr_b2 = 1;
			}
			else if ((K20 && K21) || (K19 && K20))
			{
				if (!io.gnd_2) io.motor_2_pwr_b2 = -1;
			}
		}
		return;
	}

	void PACU::Load( char* keyword, char* line )
	{
		if (!strcmp( keyword, "E21A_OFF_OUT_M1" ))
		{
			LoadVarsOut( line, e21a_off_out_1_m1, e21a_off_out_2_m1, e21a_off_out_3_m1 );
		}
		else if (!strcmp( keyword, "E21A_ON_OUT_M1" ))
		{
			LoadVarsOut( line,e21a_on_out_1_m1, e21a_on_out_2_m1, e21a_on_out_3_m1 );
		}
		else if (!strcmp( keyword, "E21A_OFF_OUT_M2" ))
		{
			LoadVarsOut( line, e21a_off_out_1_m2, e21a_off_out_2_m2, e21a_off_out_3_m2 );
		}
		else if (!strcmp( keyword, "E21A_ON_OUT_M2" ))
		{
			LoadVarsOut( line, e21a_on_out_1_m2, e21a_on_out_2_m2, e21a_on_out_3_m2 );
		}
		else if (!strcmp( keyword, "E21B_OFF_OUT_M1" ))
		{
			LoadVarsOut( line, e21b_off_out_1_m1, e21b_off_out_2_m1, e21b_off_out_3_m1 );
		}
		else if (!strcmp( keyword, "E21B_ON_OUT_M1" ))
		{
			LoadVarsOut( line, e21b_on_out_1_m1, e21b_on_out_2_m1, e21b_on_out_3_m1 );
		}
		else if (!strcmp( keyword, "E21B_OFF_OUT_M2" ))
		{
			LoadVarsOut( line, e21b_off_out_1_m2, e21b_off_out_2_m2, e21b_off_out_3_m2 );
		}
		else if (!strcmp( keyword, "E21B_ON_OUT_M2" ))
		{
			LoadVarsOut( line, e21b_on_out_1_m2, e21b_on_out_2_m2, e21b_on_out_3_m2 );
		}
		else  if (!strcmp( keyword, "E30_CTRL_GND_M1" ))
		{
			LoadVarsTD( line, e30_ctrl_gnd_1_m1, e30_ctrl_gnd_2_m1, e30_ctrl_gnd_3_m1, e30_ctrl_gnd_1_td_m1, e30_ctrl_gnd_2_td_m1, e30_ctrl_gnd_3_td_m1 );
		}
		else if (!strcmp( keyword, "E30_CTRL_GND_M2" ))
		{
			LoadVarsTD( line, e30_ctrl_gnd_1_m2, e30_ctrl_gnd_2_m2, e30_ctrl_gnd_3_m2, e30_ctrl_gnd_1_td_m2, e30_ctrl_gnd_2_td_m2, e30_ctrl_gnd_3_td_m2 );
		}
		else if (!strcmp( keyword, "E31_CTRL_GND_M1" ))
		{
			LoadVarsTD( line, e31_ctrl_gnd_1_m1, e31_ctrl_gnd_2_m1, e31_ctrl_gnd_3_m1, e31_ctrl_gnd_1_td_m1, e31_ctrl_gnd_2_td_m1, e31_ctrl_gnd_3_td_m1 );
		}
		else if (!strcmp( keyword, "E31_CTRL_GND_M2" ))
		{
			LoadVarsTD( line, e31_ctrl_gnd_1_m2, e31_ctrl_gnd_2_m2, e31_ctrl_gnd_3_m2, e31_ctrl_gnd_1_td_m2, e31_ctrl_gnd_2_td_m2, e31_ctrl_gnd_3_td_m2 );
		}
		else
		{
			// TODO unknown parameter
		}
		return;
	}

	void PACU::Save( FILEHANDLE scn ) const
	{
		SaveVarsOut( scn, "E21A_OFF_OUT_M1", e21a_off_out_1_m1, e21a_off_out_2_m1, e21a_off_out_3_m1 );
		SaveVarsOut( scn, "E21A_ON_OUT_M1", e21a_on_out_1_m1, e21a_on_out_2_m1, e21a_on_out_3_m1 );
		SaveVarsOut( scn, "E21A_OFF_OUT_M2", e21a_off_out_1_m2, e21a_off_out_2_m2, e21a_off_out_3_m2 );
		SaveVarsOut( scn, "E21A_ON_OUT_M2", e21a_on_out_1_m2, e21a_on_out_2_m2, e21a_on_out_3_m2 );
		SaveVarsOut( scn, "E21B_OFF_OUT_M1", e21b_off_out_1_m1, e21b_off_out_2_m1, e21b_off_out_3_m1 );
		SaveVarsOut( scn, "E21B_ON_OUT_M1", e21b_on_out_1_m1, e21b_on_out_2_m1, e21b_on_out_3_m1 );
		SaveVarsOut( scn, "E21B_OFF_OUT_M2", e21b_off_out_1_m2, e21b_off_out_2_m2, e21b_off_out_3_m2 );
		SaveVarsOut( scn, "E21B_ON_OUT_M2", e21b_on_out_1_m2, e21b_on_out_2_m2, e21b_on_out_3_m2 );
		SaveVarsTD( scn, "E30_CTRL_GND_M1", e30_ctrl_gnd_1_m1, e30_ctrl_gnd_2_m1, e30_ctrl_gnd_3_m1, e30_ctrl_gnd_1_td_m1, e30_ctrl_gnd_2_td_m1, e30_ctrl_gnd_3_td_m1 );
		SaveVarsTD( scn, "E30_CTRL_GND_M2", e30_ctrl_gnd_1_m2, e30_ctrl_gnd_2_m2, e30_ctrl_gnd_3_m2, e30_ctrl_gnd_1_td_m2, e30_ctrl_gnd_2_td_m2, e30_ctrl_gnd_3_td_m2 );
		SaveVarsTD( scn, "E31_CTRL_GND_M1", e31_ctrl_gnd_1_m1, e31_ctrl_gnd_2_m1, e31_ctrl_gnd_3_m1, e31_ctrl_gnd_1_td_m1, e31_ctrl_gnd_2_td_m1, e31_ctrl_gnd_3_td_m1 );
		SaveVarsTD( scn, "E31_CTRL_GND_M2", e31_ctrl_gnd_1_m2, e31_ctrl_gnd_2_m2, e31_ctrl_gnd_3_m2, e31_ctrl_gnd_1_td_m2, e31_ctrl_gnd_2_td_m2, e31_ctrl_gnd_3_td_m2 );
		return;
	}



	LACU::LACU( void ):
		K1(false), K2(false), K3(false), K4(false),
		K5(false), K6(false), K7(false), K8(false),
		e8_2_ctrl_gnd_1(true), e8_2_ctrl_gnd_2(true), e8_2_ctrl_gnd_3(true), e8_2_ctrl_gnd_1_td(-1.0), e8_2_ctrl_gnd_2_td(-1.0), e8_2_ctrl_gnd_3_td(-1.0)
	{
		return;
	}

	void LACU::Run( const double dt, LACU_IO& io )
	{
		bool tmp1;
		bool tmp2;
		bool tmp3;

		bool gnd_nk3 = io.gnd_abc;

		// self-latching logic for K1-4 and K5-8
		bool latch_k1 = !(K1 && !K5) || io.gnd_abc;
		bool latch_k3 = !(K3 && !K7) || io.gnd_abc;
		bool latch_k4 = !(K4 && !K8) || io.gnd_abc;
		bool latch_k5 = !K5 || io.gnd_abc;
		bool latch_k7 = !K7 || io.gnd_abc;
		bool latch_k8 = !K8 || io.gnd_abc;

		// K
		bool K9 = io.pwr_b && !(latch_k3 && latch_k7);
		bool K10 = io.pwr_b && !(latch_k3 && latch_k7);
		bool K13 = io.pwr_b && !(latch_k3 && latch_k7);
		
		bool K11 = io.pwr_c && !(latch_k4 && latch_k8);
		bool K12 = io.pwr_c && !(latch_k4 && latch_k8);
		bool K14 = io.pwr_c && !(latch_k4 && latch_k8);

		// E10
		_2of3VotingRelay( io.latches_cl_ind_a && io.latches_cl_ind_b, io.latches_cl_ind_a, io.latches_cl_ind_b, io.pwr_b, io.pwr_a, io.pwr_c, io.gnd_abc, io.gnd_abc, io.latches_cl_ind_1, io.latches_cl_ind_2 );

		// E11
		_2of3VotingRelay( io.latches_op_ind_a && io.latches_op_ind_b, io.latches_op_ind_a, io.latches_op_ind_b, io.pwr_b, io.pwr_a, io.pwr_c, io.gnd_abc, io.gnd_abc, io.latches_op_ind_1, io.latches_op_ind_2 );

		// E2, 3.2
		bool e2_on_out_1;
		bool e2_on_out_2;
		bool e2_on_out_3;
		bool e2_off_out_1;
		bool e2_off_out_2;
		bool e2_off_out_3;
		MomentaryRelays( io.latches_op_cmd_1, io.latches_op_cmd_2, io.latches_op_cmd_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, e2_on_out_1, e2_on_out_2, e2_on_out_3, e2_off_out_1, e2_off_out_2, e2_off_out_3 );

		// E1, 3.1
		bool e1_on_out_1;
		bool e1_on_out_2;
		bool e1_on_out_3;
		bool e1_off_out_1;
		bool e1_off_out_2;
		bool e1_off_out_3;
		MomentaryRelays( io.latches_cl_cmd_1, io.latches_cl_cmd_2, io.latches_cl_cmd_3, io.pwr_a, io.pwr_b, io.pwr_c, e2_off_out_1, e2_off_out_2, e2_off_out_3, e1_on_out_1, e1_on_out_2, e1_on_out_3, e1_off_out_1, e1_off_out_2, e1_off_out_3 );

		// E14
		bool e14_out_1;
		bool e14_out_2;
		bool e14_out_3;
		MomentaryRelays( latch_k4 && latch_k8, latch_k3 && latch_k7, latch_k1 && latch_k5, io.pwr_a, io.pwr_b, io.pwr_c, e1_off_out_1, e1_off_out_2, e1_off_out_3,e14_out_1, e14_out_2, e14_out_3, tmp1, tmp2, tmp3 );

		// E4, 5, 6, 7, 8.1, 37, 38.1
		bool e4_out_1;
		bool e4_out_2;
		bool e4_out_3;
		MomentaryRelays( (io.latch_1_ret_gnd_1 || !K9) && (io.latch_1_ret_gnd_2 || !K11), (io.latch_2_ret_gnd_1 || !K9) && (io.latch_2_ret_gnd_2 || !K11), (io.latch_3_ret_gnd_1 || !K10) && (io.latch_3_ret_gnd_2 || !K12), io.pwr_n3k1, io.pwr_n3k2, io.pwr_n3k3, e14_out_1, e14_out_2, e14_out_3, tmp1, tmp2, tmp3, e4_out_1, e4_out_2, e4_out_3 );

		// E8.2, 9
		// HACK inputs and outputs inverted as MomentaryRelays() logic is for grounds
		bool e8_2_out_1;
		bool e8_2_out_2;
		bool e8_2_out_3;
		TimeDelay( 0.35, e4_out_1, dt, e8_2_ctrl_gnd_1_td, e8_2_ctrl_gnd_1 );
		TimeDelay( 0.35, e4_out_2, dt, e8_2_ctrl_gnd_2_td, e8_2_ctrl_gnd_2 );
		TimeDelay( 0.35, e4_out_3, dt, e8_2_ctrl_gnd_3_td, e8_2_ctrl_gnd_3 );
		MomentaryRelays( e8_2_ctrl_gnd_1, e8_2_ctrl_gnd_2, e8_2_ctrl_gnd_3, io.pwr_a, io.pwr_b, io.pwr_c, !io.pwr_a, !io.pwr_b, !io.pwr_c, tmp1, tmp2, tmp3, e8_2_out_1, e8_2_out_2, e8_2_out_3 );

		// E12
		bool e12_out_1;
		bool e12_out_2;
		bool e12_out_3;
		MomentaryRelays( e4_out_1, e4_out_2, e4_out_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, e12_out_1, e12_out_2, e12_out_3, tmp1, tmp2, tmp3 );

		// E15
		MomentaryRelays( latch_k5, latch_k7, latch_k8, io.pwr_a, io.pwr_b, io.pwr_c, e12_out_1, e12_out_2, e12_out_3, io.ring_in_cmd_1, io.ring_in_cmd_2, io.ring_in_cmd_3, tmp1, tmp2, tmp3 );

		// K
		K1 = !e8_2_out_1 && !(e1_on_out_1 && latch_k1);
		K2 = !e8_2_out_1 && !(e1_on_out_1 && latch_k1);
		K3 = !e8_2_out_2 && !(e1_on_out_2 && latch_k3);
		K4 = !e8_2_out_3 && !(e1_on_out_3 && latch_k4);

		K5 = !e8_2_out_1 && !(e2_on_out_1 && latch_k5);
		K6 = !e8_2_out_1 && !(e2_on_out_1 && latch_k5);
		K7 = !e8_2_out_2 && !(e2_on_out_2 && latch_k7);
		K8 = !e8_2_out_3 && !(e2_on_out_3 && latch_k8);

		// open latches cmd / mtr ground logic
		// 5/6/7/8
		io.latch_motor_op_gnd_1 = gnd_nk3 || !(K7 && (K5 || (!K6 && K8)));
		io.latch_motor_op_gnd_2 = gnd_nk3 || !(K6 && K8);

		// close latches cmd / mtr ground logic
		// 1/2/3/4
		io.latch_motor_cl_gnd_1 = gnd_nk3 || !(K3 && (K1 || (!K2 && K4)));
		io.latch_motor_cl_gnd_2 = gnd_nk3 || !(K2 && K4);

		// motor power
		io.latch_1_motor_pwr_1 = K10 * io.pwr_n3k1;
		io.latch_1_motor_pwr_2 = K12 * io.pwr_n3k1;
		io.latch_2_motor_pwr_1 = K13 * io.pwr_n3k2;
		io.latch_2_motor_pwr_2 = K14 * io.pwr_n3k2;
		io.latch_3_motor_pwr_1 = K13 * io.pwr_n3k3;
		io.latch_3_motor_pwr_2 = K14 * io.pwr_n3k3;
		return;
	}

	void LACU::Load( char* keyword, char* line )
	{
		int itmp;

		if (!strcmp( keyword, "K1" ))
		{
			sscanf_s( line, "%d", &itmp );
			K1 = (itmp == 1);
		}
		else if (!strcmp( keyword, "K2" ))
		{
			sscanf_s( line, "%d", &itmp );
			K2 = (itmp == 1);
		}
		else if (!strcmp( keyword, "K3" ))
		{
			sscanf_s( line, "%d", &itmp );
			K3 = (itmp == 1);
		}
		else if (!strcmp( keyword, "K4" ))
		{
			sscanf_s( line, "%d", &itmp );
			K4 = (itmp == 1);
		}
		else if (!strcmp( keyword, "K5" ))
		{
			sscanf_s( line, "%d", &itmp );
			K5 = (itmp == 1);
		}
		else if (!strcmp( keyword, "K6" ))
		{
			sscanf_s( line, "%d", &itmp );
			K6 = (itmp == 1);
		}
		else if (!strcmp( keyword, "K7" ))
		{
			sscanf_s( line, "%d", &itmp );
			K7 = (itmp == 1);
		}
		else if (!strcmp( keyword, "K8" ))
		{
			sscanf_s( line, "%d", &itmp );
			K8 = (itmp == 1);
		}
		else if (!strcmp( keyword, "E8_2_CTRL_GND" ))
		{
			LoadVarsTD( line, e8_2_ctrl_gnd_1, e8_2_ctrl_gnd_2, e8_2_ctrl_gnd_3, e8_2_ctrl_gnd_1_td, e8_2_ctrl_gnd_2_td, e8_2_ctrl_gnd_3_td );
		}
		else
		{
			// TODO unknown parameter
		}
		return;
	}

	void LACU::Save( FILEHANDLE scn ) const
	{
		oapiWriteScenario_int( scn, "K1", K1 );
		oapiWriteScenario_int( scn, "K2", K2 );
		oapiWriteScenario_int( scn, "K3", K3 );
		oapiWriteScenario_int( scn, "K4", K4 );
		oapiWriteScenario_int( scn, "K5", K5 );
		oapiWriteScenario_int( scn, "K6", K6 );
		oapiWriteScenario_int( scn, "K7", K7 );
		oapiWriteScenario_int( scn, "K8", K8 );

		SaveVarsTD( scn, "E8_2_CTRL_GND", e8_2_ctrl_gnd_1, e8_2_ctrl_gnd_2, e8_2_ctrl_gnd_3, e8_2_ctrl_gnd_1_td, e8_2_ctrl_gnd_2_td, e8_2_ctrl_gnd_3_td );
		return;
	}
}

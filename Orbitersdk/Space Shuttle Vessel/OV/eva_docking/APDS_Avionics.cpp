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


	PSU::PSU( void ):
		K1(false), K2(false), K11(false), K12(false),
		K3(false), K4(false), K13(false), K14(false),
		K5(false), K6(false), K15(false), K16(false),
		e12_out_1(true), e12_out_2(true), e12_out_3(true),
		e23_ctrl_gnd_1(true), e23_ctrl_gnd_2(true), e23_ctrl_gnd_3(true), e23_ctrl_gnd_1_td(-1.0), e23_ctrl_gnd_2_td(-1.0), e23_ctrl_gnd_3_td(-1.0),
		e12_ctrl_gnd_1(true), e12_ctrl_gnd_2(true), e12_ctrl_gnd_3(true), e12_ctrl_gnd_1_td(-1.0), e12_ctrl_gnd_2_td(-1.0), e12_ctrl_gnd_3_td(-1.0),
		e10_out_on_1(true), e10_out_on_2(true), e10_out_on_3(true)
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
		MomentaryRelays( e2_out_1 && e12_out_1, e2_out_2 && e12_out_2, e2_out_3 && e12_out_3, io.wa, io.wb, io.wc, io.gnd_c, io.gnd_c, io.gnd_c, e25_out_1, e25_out_2, e25_out_3, tmp1, tmp2, tmp3 );

		// E23
		bool e23_out_1;
		bool e23_out_2;
		bool e23_out_3;
		TimeDelay( 0.2, e25_out_1, dt, e23_ctrl_gnd_1_td, e23_ctrl_gnd_1 );
		TimeDelay( 0.2, e25_out_2, dt, e23_ctrl_gnd_2_td, e23_ctrl_gnd_2 );
		TimeDelay( 0.2, e25_out_3, dt, e23_ctrl_gnd_3_td, e23_ctrl_gnd_3 );
		MomentaryRelays( e23_ctrl_gnd_1, e23_ctrl_gnd_2, e23_ctrl_gnd_3, io.wa, io.wb, io.wc, io.gnd_c, io.gnd_c, io.gnd_c, e23_out_1, e23_out_2, e23_out_3, tmp1, tmp2, tmp3 );

		// E12, 13
		TimeDelay( 0.2, e23_out_1, dt, e12_ctrl_gnd_1_td, e12_ctrl_gnd_1 );
		TimeDelay( 0.2, e23_out_2, dt, e12_ctrl_gnd_2_td, e12_ctrl_gnd_2 );
		TimeDelay( 0.2, e23_out_3, dt, e12_ctrl_gnd_3_td, e12_ctrl_gnd_3 );
		MomentaryRelays( e12_ctrl_gnd_1, e12_ctrl_gnd_2, e12_ctrl_gnd_3, io.wa, io.wb, io.wc, e25_out_1, e25_out_2, e25_out_3, tmp1, tmp2, tmp3, e12_out_1, e12_out_2, e12_out_3 );

		// E4
		bool e4_out_1;
		bool e4_out_2;
		bool e4_out_3;
		RelayNetwork( e23_out_1, e23_out_2, e23_out_3, io.wa, io.wb, io.wc, io.gnd_c, io.gnd_c, e4_out_1, e4_out_2, e4_out_3 );

		// E10, 11
		bool e10_out_off_1;
		bool e10_out_off_2;
		bool e10_out_off_3;
		MomentaryRelays( e4_out_1 && e10_out_on_1, e4_out_2 && e10_out_on_2, e4_out_3 && e10_out_on_3, io.wa, io.wb, io.wc, e1_out_1, e1_out_2, e1_out_3, e10_out_on_1, e10_out_on_2, e10_out_on_3, e10_out_off_1, e10_out_off_2, e10_out_off_3 );

		// K
		LatchingRelay( io.wa, e10_out_off_1, e4_out_1, K1 );
		LatchingRelay( io.wa, e10_out_off_1, e4_out_1, K2 );
		LatchingRelay( io.wa, e10_out_off_1, e4_out_1, K11 );
		LatchingRelay( io.wa, e10_out_off_1, e4_out_1, K12 );

		LatchingRelay( io.wb, e10_out_off_2, e4_out_2, K3 );
		LatchingRelay( io.wb, e10_out_off_2, e4_out_2, K4 );
		LatchingRelay( io.wb, e10_out_off_2, e4_out_2, K13 );
		LatchingRelay( io.wb, e10_out_off_2, e4_out_2, K14 );
		
		LatchingRelay( io.wc, e10_out_off_3, e4_out_3, K5 );
		LatchingRelay( io.wc, e10_out_off_3, e4_out_3, K6 );
		LatchingRelay( io.wc, e10_out_off_3, e4_out_3, K15 );
		LatchingRelay( io.wc, e10_out_off_3, e4_out_3, K16 );

		// grounds
		io.gnd_c_1 = !(K1 && K4) || io.gnd_c;
		io.gnd_c_2 = !(K3 && K6) || io.gnd_c;
		io.gnd_c_3 = !(K2 && K5) || io.gnd_c;

		// powers
		io.pwr_wa_1 = K1 && io.wa;
		io.pwr_wa_2 = K2 && io.wa;

		io.pwr_wb_1 = K3 && io.wb;
		io.pwr_wb_2 = K4 && io.wb;

		io.pwr_wc_1 = K5 && io.wc;
		io.pwr_wc_2 = K6 && io.wc;

		// E20
		MomentaryRelays( e1_out_1, e1_out_2, e1_out_3, io.wa, io.wb, io.wc, io.gnd_c_1, io.gnd_c_2, io.gnd_c_3, io.pwr_on_reset_1, io.pwr_on_reset_2, io.pwr_on_reset_3, tmp1, tmp2, tmp3 );

		// E21
		MomentaryRelays( e2_out_1, e2_out_2, e2_out_3, io.wa, io.wb, io.wc, io.gnd_c_1, io.gnd_c_2, io.gnd_c_3, io.pwr_off_reset_1, io.pwr_off_reset_2, io.pwr_off_reset_3, tmp1, tmp2, tmp3 );
		return;
	}

	void PSU::Load( void )
	{
		return;
	}

	void PSU::Save( void ) const
	{
		return;
	}



	DSCU::DSCU( void ):
		e102_out_1(true), e102_out_2(true), e102_out_3(true),
		e124_out_1(true), e124_out_2(true), e124_out_3(true),
		e113_out_1(true), e113_out_2(true), e113_out_3(true),
		e114_out_1(true), e114_out_2(true), e114_out_3(true),
		e31_ctrl_gnd_1(true), e31_ctrl_gnd_2(true), e31_ctrl_gnd_3(true), e31_ctrl_gnd_1_td(-1.0), e31_ctrl_gnd_2_td(-1.0), e31_ctrl_gnd_3_td(-1.0),
		e33_ctrl_gnd_1(true), e33_ctrl_gnd_2(true), e33_ctrl_gnd_3(true), e33_ctrl_gnd_1_td(-1.0), e33_ctrl_gnd_2_td(-1.0), e33_ctrl_gnd_3_td(-1.0),
		e35_ctrl_gnd_1(true), e35_ctrl_gnd_2(true), e35_ctrl_gnd_3(true), e35_ctrl_gnd_1_td(-1.0), e35_ctrl_gnd_2_td(-1.0), e35_ctrl_gnd_3_td(-1.0),
		e145_ctrl_gnd_1(true), e145_ctrl_gnd_2(true), e145_ctrl_gnd_3(true), e145_ctrl_gnd_1_td(-1.0), e145_ctrl_gnd_2_td(-1.0), e145_ctrl_gnd_3_td(-1.0)
	{
		return;
	}

	void DSCU::Run( const double dt, DSCU_IO& io )
	{
		bool tmp1;
		bool tmp2;
		bool tmp3;

		bool gnd_ct1 = true;// TODO
		bool gnd_ct2 = true;// TODO
		bool gnd_ct3 = true;// TODO
		bool pwr_cntl_pnl_a = true;// TODO
		bool pwr_cntl_pnl_b = true;// TODO
		bool pwr_cntl_pnl_c = true;// TODO

		// E102, 142
		MomentaryRelays( e102_out_3 && io.apds_circ_prot_off, e102_out_3 && io.apds_circ_prot_off, e102_out_3 && io.apds_circ_prot_off, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, e102_out_1, e102_out_2, e102_out_3, tmp1, tmp2, tmp3 );

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
		MomentaryRelays( gnd_ct1/* TODO*/, gnd_ct2/*TODO*/, gnd_ct3/*TODO*/, io.pwr_a, io.pwr_b, io.pwr_c, e131_out_1, e131_out_2, e131_out_3, e181_out_1, e181_out_2, e181_out_3, tmp1, tmp2, tmp3 );

		// E33, E34A
		bool e33_out_1;
		bool e33_out_2;
		bool e33_out_3;
		TimeDelay( 0.2, e181_out_1, dt, e33_ctrl_gnd_1_td, e33_ctrl_gnd_1 );
		TimeDelay( 0.2, e181_out_2, dt, e33_ctrl_gnd_2_td, e33_ctrl_gnd_2 );
		TimeDelay( 0.2, e181_out_3, dt, e33_ctrl_gnd_3_td, e33_ctrl_gnd_3 );
		MomentaryRelays( e33_ctrl_gnd_1, e33_ctrl_gnd_2, e33_ctrl_gnd_3, io.pwr_a, io.pwr_b, io.pwr_c, e181_out_1, e181_out_2, e181_out_3, e33_out_1, e33_out_2, e33_out_3, tmp1, tmp2, tmp3 );

		// hooks 1
		bool e182_out_1;
		bool e182_out_2;
		bool e182_out_3;
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
			bool e173_out_1;// TODO
			bool e173_out_2;
			bool e173_out_3;
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
			bool e175_out_1;// TODO
			bool e175_out_2;
			bool e175_out_3;
			MomentaryRelays( io.inbetweenhooks_ind_1, io.inbetweenhooks_ind_1 && io.inbetweenhooks_ind_2, io.inbetweenhooks_ind_2, io.pwr_b, io.pwr_a, io.pwr_c, e181_out_1, e181_out_2, e181_out_3, e175_out_1, e175_out_2, e175_out_3, tmp1, tmp2, tmp3 );

			// E114
			MomentaryRelays( e114_out_1 && io.gnd_hooks_2_cl_1, e114_out_2 && io.gnd_hooks_2_cl_2, e114_out_3 && io.gnd_hooks_2_cl_3, io.pwr_a, io.pwr_b, io.pwr_c, gnd_ct1, gnd_ct2, gnd_ct3, e114_out_1, e114_out_2, e114_out_3, tmp1, tmp2, tmp3 );

			// E183
			MomentaryRelays( e114_out_1, e114_out_2, e114_out_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, io.gnd_abc, e183_out_1, e183_out_2, e183_out_3, tmp1, tmp2, tmp3 );
		}

		// E35, 34-2
		bool e35_out_1;
		bool e35_out_2;
		bool e35_out_3;
		TimeDelay( 10.0, e182_out_1 && e183_out_1, dt, e35_ctrl_gnd_1_td, e35_ctrl_gnd_1 );
		TimeDelay( 10.0, e182_out_2 && e183_out_2, dt, e35_ctrl_gnd_2_td, e35_ctrl_gnd_2 );
		TimeDelay( 10.0, e182_out_3 && e183_out_3, dt, e35_ctrl_gnd_3_td, e35_ctrl_gnd_3 );
		MomentaryRelays( e35_ctrl_gnd_1, e35_ctrl_gnd_2, e35_ctrl_gnd_3, io.pwr_a, io.pwr_b, io.pwr_c, e182_out_1 && e183_out_1, e182_out_2 && e183_out_2, e182_out_3 && e183_out_3, tmp1, tmp2, tmp3, e35_out_1, e35_out_2, e35_out_3 );

		// E145
		bool e145_out_1;
		bool e145_out_2;
		bool e145_out_3;
		TimeDelay( 10.0, e182_out_1 && e183_out_1, dt, e145_ctrl_gnd_1_td, e145_ctrl_gnd_1 );
		TimeDelay( 10.0, e182_out_2 && e183_out_2, dt, e145_ctrl_gnd_2_td, e145_ctrl_gnd_2 );
		TimeDelay( 10.0, e182_out_3 && e183_out_3, dt, e145_ctrl_gnd_3_td, e145_ctrl_gnd_3 );
		RelayNetwork_PACU( e145_ctrl_gnd_1, e145_ctrl_gnd_2, e145_ctrl_gnd_3, io.pwr_a, io.pwr_b, io.pwr_c, io.gnd_abc, io.gnd_abc, e145_out_1, e145_out_2, e145_out_3 );

		// E31, 36
		bool e31_out_1;
		bool e31_out_2;
		bool e31_out_3;
		TimeDelay( 10.0, e145_out_1, dt, e31_ctrl_gnd_1_td, e31_ctrl_gnd_1 );
		TimeDelay( 10.0, e145_out_2, dt, e31_ctrl_gnd_2_td, e31_ctrl_gnd_2 );
		TimeDelay( 10.0, e145_out_3, dt, e31_ctrl_gnd_3_td, e31_ctrl_gnd_3 );
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
		bool e111_out_1;// TODO
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
		return;
	}

	void DSCU::Load( void )
	{
		return;
	}

	void DSCU::Save( void ) const
	{
		return;
	}



	DMCU::DMCU( void )
	{
		return;
	}

	void DMCU::Run( DMCU_IO& io )
	{
		return;
	}

	void DMCU::Load( void )
	{
		return;
	}

	void DMCU::Save( void ) const
	{
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

	void PACU::Load( void )
	{
		return;
	}

	void PACU::Save( void ) const
	{
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

	void LACU::Load( void )
	{
		return;
	}

	void LACU::Save( void ) const
	{
		return;
	}
}

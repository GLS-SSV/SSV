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

	static void _2of3VotingRelay( const bool ctrl_gnd_1, const bool ctrl_gnd_2, const bool ctrl_gnd_3, const bool ctrl_pwr_1, const bool ctrl_pwr_2, const bool ctrl_pwr_3, const bool in_1, const bool in_2, bool &out_1, bool &out_2 )
	{
		bool k1 = !ctrl_gnd_3 && ctrl_pwr_3;
		bool k2 = !ctrl_gnd_1 && ctrl_pwr_1;
		bool k3 = !ctrl_gnd_1 && ctrl_pwr_1;
		bool k4 = !ctrl_gnd_2 && ctrl_pwr_2;

		bool o1 = k2 && k4;
		bool o21 = k1 && !k3 && k4;
		bool o22 = k1 && k3;

		bool out = (in_1 || !o1) || (in_1 || !o21) || (in_2 || !o22);

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

	void PSU::Run( const double dt, const bool cntl_pnl_a, const bool cntl_pnl_b, const bool cntl_pnl_c, const bool power_on, const bool power_off, const bool gnd_c, const bool wa, const bool wb, const bool wc, const bool cw1, const bool cw2,
		bool& pwr_on_reset_1, bool& pwr_on_reset_2, bool& pwr_on_reset_3, bool& pwr_off_reset_1, bool& pwr_off_reset_2, bool& pwr_off_reset_3, bool& gnd_c_1, bool& gnd_c_2, bool& gnd_c_3, bool& pwr_wa_1, bool& pwr_wa_2, bool& pwr_wb_1, bool& pwr_wb_2, bool& pwr_wc_1, bool& pwr_wc_2 )
	{
		bool tmp1;
		bool tmp2;
		bool tmp3;

		// E1
		bool e1_out_1;
		bool e1_out_2;
		bool e1_out_3;
		RelayNetwork( power_on, power_on, power_on, cntl_pnl_a, cntl_pnl_b, cntl_pnl_c, gnd_c, gnd_c, e1_out_1, e1_out_2, e1_out_3 );

		// E2
		bool e2_out_1;
		bool e2_out_2;
		bool e2_out_3;
		RelayNetwork( power_off, power_off, power_off, cntl_pnl_a, cntl_pnl_b, cntl_pnl_c, gnd_c, gnd_c, e2_out_1, e2_out_2, e2_out_3 );

		// E25, 22
		bool e25_out_1;
		bool e25_out_2;
		bool e25_out_3;
		MomentaryRelays( e2_out_1 && e12_out_1, e2_out_2 && e12_out_2, e2_out_3 && e12_out_3, wa, wb, wc, gnd_c, gnd_c, gnd_c, e25_out_1, e25_out_2, e25_out_3, tmp1, tmp2, tmp3 );

		// E23
		bool e23_out_1;
		bool e23_out_2;
		bool e23_out_3;
		TimeDelay( 0.2, e25_out_1, dt, e23_ctrl_gnd_1_td, e23_ctrl_gnd_1 );
		TimeDelay( 0.2, e25_out_2, dt, e23_ctrl_gnd_2_td, e23_ctrl_gnd_2 );
		TimeDelay( 0.2, e25_out_3, dt, e23_ctrl_gnd_3_td, e23_ctrl_gnd_3 );
		MomentaryRelays( e23_ctrl_gnd_1, e23_ctrl_gnd_2, e23_ctrl_gnd_3, wa, wb, wc, gnd_c, gnd_c, gnd_c, e23_out_1, e23_out_2, e23_out_3, tmp1, tmp2, tmp3 );

		// E12, 13
		TimeDelay( 0.2, e23_out_1, dt, e12_ctrl_gnd_1_td, e12_ctrl_gnd_1 );
		TimeDelay( 0.2, e23_out_2, dt, e12_ctrl_gnd_2_td, e12_ctrl_gnd_2 );
		TimeDelay( 0.2, e23_out_3, dt, e12_ctrl_gnd_3_td, e12_ctrl_gnd_3 );
		MomentaryRelays( e12_ctrl_gnd_1, e12_ctrl_gnd_2, e12_ctrl_gnd_3, wa, wb, wc, e25_out_1, e25_out_2, e25_out_3, tmp1, tmp2, tmp3, e12_out_1, e12_out_2, e12_out_3 );

		// E4
		bool e4_out_1;
		bool e4_out_2;
		bool e4_out_3;
		RelayNetwork( e23_out_1, e23_out_2, e23_out_3, wa, wb, wc, gnd_c, gnd_c, e4_out_1, e4_out_2, e4_out_3 );

		// E10, 11
		bool e10_out_off_1;
		bool e10_out_off_2;
		bool e10_out_off_3;
		MomentaryRelays( e4_out_1 && e10_out_on_1, e4_out_2 && e10_out_on_2, e4_out_3 && e10_out_on_3, wa, wb, wc, e1_out_1, e1_out_2, e1_out_3, e10_out_on_1, e10_out_on_2, e10_out_on_3, e10_out_off_1, e10_out_off_2, e10_out_off_3 );

		// K
		LatchingRelay( wa, e10_out_off_1, e4_out_1, K1 );
		LatchingRelay( wa, e10_out_off_1, e4_out_1, K2 );
		LatchingRelay( wa, e10_out_off_1, e4_out_1, K11 );
		LatchingRelay( wa, e10_out_off_1, e4_out_1, K12 );

		LatchingRelay( wb, e10_out_off_2, e4_out_2, K3 );
		LatchingRelay( wb, e10_out_off_2, e4_out_2, K4 );
		LatchingRelay( wb, e10_out_off_2, e4_out_2, K13 );
		LatchingRelay( wb, e10_out_off_2, e4_out_2, K14 );
		
		LatchingRelay( wc, e10_out_off_3, e4_out_3, K5 );
		LatchingRelay( wc, e10_out_off_3, e4_out_3, K6 );
		LatchingRelay( wc, e10_out_off_3, e4_out_3, K15 );
		LatchingRelay( wc, e10_out_off_3, e4_out_3, K16 );

		// grounds
		gnd_c_1 = !(K1 && K4) || gnd_c;
		gnd_c_2 = !(K3 && K6) || gnd_c;
		gnd_c_3 = !(K2 && K5) || gnd_c;

		// powers
		pwr_wa_1 = K1 && wa;
		pwr_wa_2 = K2 && wa;

		pwr_wb_1 = K3 && wb;
		pwr_wb_2 = K4 && wb;

		pwr_wc_1 = K5 && wc;
		pwr_wc_2 = K6 && wc;

		// E20
		MomentaryRelays( e1_out_1, e1_out_2, e1_out_3, wa, wb, wc, gnd_c_1, gnd_c_2, gnd_c_3, pwr_on_reset_1, pwr_on_reset_2, pwr_on_reset_3, tmp1, tmp2, tmp3 );

		// E21
		MomentaryRelays( e2_out_1, e2_out_2, e2_out_3, wa, wb, wc, gnd_c_1, gnd_c_2, gnd_c_3, pwr_off_reset_1, pwr_off_reset_2, pwr_off_reset_3, tmp1, tmp2, tmp3 );
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

	void PACU::Run( const double dt, const bool gnd_1, const bool gnd_2, const bool gnd_abc, const bool pwr_1, const bool pwr_2, const bool pwr_a, const bool pwr_b, const bool pwr_c, const bool hooks_cl_1, const bool hooks_cl_2, const bool hooks_cl_3, const bool hooks_op_1, const bool hooks_op_2, const bool hooks_op_3, const bool hooks_cl_ind_a, const bool hooks_cl_ind_b, const bool hooks_op_ind_a, const bool hooks_op_ind_b,
		short& motor_1_pwr_a1, short& motor_1_pwr_a2, short& motor_1_pwr_b1, short& motor_1_pwr_b2, short& motor_2_pwr_a1, short& motor_2_pwr_a2, short& motor_2_pwr_b1, short& motor_2_pwr_b2, bool& gnd_hooks_cl_1, bool& gnd_hooks_cl_2, bool& gnd_hooks_cl_3 )
	{
		bool hooks_cl_ind_1 = hooks_cl_ind_a;
		bool hooks_cl_ind_2 = hooks_cl_ind_a && hooks_cl_ind_b;
		bool hooks_cl_ind_3 = hooks_cl_ind_b;

		bool hooks_op_ind_1 = hooks_op_ind_a;
		bool hooks_op_ind_2 = hooks_op_ind_a && hooks_op_ind_b;
		bool hooks_op_ind_3 = hooks_op_ind_b;

		bool tmp1;
		bool tmp2;
		bool tmp3;

		//// Motor 1
		{
			// E50
			bool e50_out_1;
			bool e50_out_2;
			bool e50_out_3;
			RelayNetwork_PACU( hooks_op_1, hooks_op_2, hooks_op_3, pwr_a, pwr_b, pwr_c, gnd_abc, gnd_abc, e50_out_1, e50_out_2, e50_out_3 );

			// E51
			bool e51_out_1;
			bool e51_out_2;
			bool e51_out_3;
			RelayNetwork_PACU( hooks_cl_1, hooks_cl_2, hooks_cl_3, pwr_a, pwr_b, pwr_c, gnd_abc, gnd_abc, e51_out_1, e51_out_2, e51_out_3 );

			// E1A, 2A, 3A
			// HACK split box to handle signal flow
			bool e1a_out_1;
			bool e1a_out_2;
			bool e1a_out_3;
			MomentaryRelays( e50_out_3 && e21b_off_out_1_m1, e50_out_2 && e21b_off_out_2_m1, e50_out_1 && e21b_off_out_3_m1, pwr_a, pwr_b, pwr_c, gnd_abc, gnd_abc, gnd_abc, e1a_out_1, e1a_out_2, e1a_out_3, tmp1, tmp2, tmp3 );
			MomentaryRelays( e50_out_3 && e21b_off_out_1_m1, e50_out_2 && e21b_off_out_2_m1, e50_out_1 && e21b_off_out_3_m1, pwr_a, pwr_b, pwr_c, e21b_on_out_1_m1, e21b_on_out_2_m1, e21b_on_out_3_m1, tmp1, tmp2, tmp3, gnd_hooks_cl_1, gnd_hooks_cl_2, gnd_hooks_cl_3 );

			// E4B, 5B, 6B
			bool e4b_out_1;
			bool e4b_out_2;
			bool e4b_out_3;
			MomentaryRelays( e51_out_1, e51_out_2, e51_out_3, pwr_a, pwr_b, pwr_c, gnd_abc, gnd_abc, gnd_abc, e4b_out_1, e4b_out_2, e4b_out_3, tmp1, tmp2, tmp3 );

			// E30, 44
			bool e30_out_1;
			bool e30_out_2;
			bool e30_out_3;
			TimeDelay( 0.5, e1a_out_1 && e21b_on_out_1_m1, dt, e30_ctrl_gnd_1_td_m1, e30_ctrl_gnd_1_m1 );
			TimeDelay( 0.5, e1a_out_2 && e21b_on_out_2_m1, dt, e30_ctrl_gnd_2_td_m1, e30_ctrl_gnd_2_m1 );
			TimeDelay( 0.5, e1a_out_3 && e21b_on_out_3_m1, dt, e30_ctrl_gnd_3_td_m1, e30_ctrl_gnd_3_m1 );
			MomentaryRelays( e30_ctrl_gnd_1_m1, e30_ctrl_gnd_2_m1, e30_ctrl_gnd_3_m1, pwr_a, pwr_b, pwr_c, gnd_abc, gnd_abc, gnd_abc, e30_out_1, e30_out_2, e30_out_3, tmp1, tmp2, tmp3 );

			// E31, 45
			bool e31_out_1;
			bool e31_out_2;
			TimeDelay( 0.5, e4b_out_1 && e21a_on_out_1_m1, dt, e31_ctrl_gnd_1_td_m1, e31_ctrl_gnd_1_m1 );
			TimeDelay( 0.5, e4b_out_2 && e21a_on_out_2_m1, dt, e31_ctrl_gnd_2_td_m1, e31_ctrl_gnd_2_m1 );
			TimeDelay( 0.5, e4b_out_3 && e21a_on_out_3_m1, dt, e31_ctrl_gnd_3_td_m1, e31_ctrl_gnd_3_m1 );
			{
				// custom circuit
				bool k1 = !e31_ctrl_gnd_1_m1 && pwr_a;
				bool k2 = !e31_ctrl_gnd_2_m1 && pwr_b;
				bool k3 = !e31_ctrl_gnd_3_m1 && pwr_c;

				// HACK info not clear
				bool o1 = k1 && (k2 || k3);
				bool o2 = k1 && (k2 || k3);

				e31_out_1 = gnd_abc || !o1;
				e31_out_2 = gnd_abc || !o2;
			}

			// E21A, 22A, 23A
			// HACK split box to handle signal flow
			MomentaryRelays( e30_out_1, e30_out_2, e30_out_3, pwr_a, pwr_b, pwr_c, e4b_out_1, e4b_out_2, e4b_out_3, tmp1, tmp2, tmp3, e21a_off_out_1_m1, e21a_off_out_2_m1, e21a_off_out_3_m1 );
			MomentaryRelays( e30_out_1, e30_out_2, e30_out_3, pwr_a, pwr_b, pwr_c, hooks_op_ind_1, hooks_op_ind_2, hooks_op_ind_3, e21a_on_out_1_m1, e21a_on_out_2_m1, e21a_on_out_3_m1, tmp1, tmp2, tmp3 );

			// E21B, 22B, 23B
			// HACK split box to handle signal flow
			MomentaryRelays( e31_out_1 && e31_out_2, e31_out_1 && e31_out_2, e31_out_1 && e31_out_2, pwr_a, pwr_b, pwr_c, e1a_out_1, e1a_out_2, e1a_out_3, tmp1, tmp2, tmp3, e21b_off_out_1_m1, e21b_off_out_2_m1, e21b_off_out_3_m1 );
			MomentaryRelays( e31_out_1 && e31_out_2, e31_out_1 && e31_out_2, e31_out_1 && e31_out_2, pwr_a, pwr_b, pwr_c, hooks_cl_ind_1, hooks_cl_ind_2, hooks_cl_ind_3, e21b_on_out_1_m1, e21b_on_out_2_m1, e21b_on_out_3_m1, tmp1, tmp2, tmp3 );

			// E1B, 2B, 3B
			bool e1b_out_1;
			bool e1b_out_2;
			bool e1b_out_3;
			MomentaryRelays( e50_out_3 && e21b_off_out_1_m1, e50_out_2 && e21b_off_out_2_m1, e50_out_1 && e21b_off_out_3_m1, pwr_a, pwr_b, pwr_c, e21b_off_out_1_m1, e21b_off_out_2_m1, e21b_off_out_3_m1, tmp1, tmp2, tmp3, e1b_out_1, e1b_out_2, e1b_out_3 );

			// E4A, 5A, 6A
			bool e4a_out_1;
			bool e4a_out_2;
			bool e4a_out_3;
			MomentaryRelays( e51_out_1 && e21a_off_out_1_m1, e51_out_2 && e21a_off_out_2_m1, e51_out_3 && e21a_off_out_3_m1, pwr_a, pwr_b, pwr_c, e21b_off_out_1_m1, e21b_off_out_2_m1, e21b_off_out_3_m1, tmp1, tmp2, tmp3, e4a_out_1, e4a_out_2, e4a_out_3 );

			// K
			bool K4 = pwr_a && !e1b_out_1;
			bool K7 = pwr_a && !e1b_out_1;
			bool K5 = pwr_b && !e1b_out_2;
			bool K8 = pwr_b && !e1b_out_2;
			bool K6 = pwr_c && !e1b_out_3;
			bool K9 = pwr_c && !e1b_out_3;

			bool K1 = pwr_a && !e4a_out_3;
			bool K10 = pwr_a && !e4a_out_3;
			bool K2 = pwr_b && !e4a_out_2;
			bool K11 = pwr_b && !e4a_out_2;
			bool K3 = pwr_c && !e4a_out_1;
			bool K12 = pwr_c && !e4a_out_1;

			// motor power/ground
			// output: 0=off; +1=open; -1=close
			motor_1_pwr_a1 = 0;
			motor_1_pwr_a2 = 0;

			if ((!K1 && !K2 && K4 && K6) || (!K1 && K2 && !K3 && K5 && K6) || (!K1 && K2 && !K3 && K4 && K5))
			{
				if (pwr_1) motor_1_pwr_a1 = 1;
			}
			else if (K1 && K3)
			{
				if (gnd_1) motor_1_pwr_a1 = -1;
			}

			if ((!K2 && !K3 && K5 && K6) || (!K2 && !K3 && K4 && K5))
			{
				if (pwr_1) motor_1_pwr_a2 = 1;
			}
			else if ((K2 && K3) || (K1 && K2))
			{
				if (gnd_1) motor_1_pwr_a2 = -1;
			}

			motor_1_pwr_b1 = 0;
			motor_1_pwr_b2 = 0;

			if ((!K7 && !K8 && K10 && K12) || (!K7 && K8 && !K9 && K11 && K12) || (!K7 && K8 && !K9 && K10 && K11))
			{
				if (pwr_1) motor_1_pwr_b1 = 1;
			}
			else if (K7 && K9)
			{
				if (gnd_1) motor_1_pwr_b1 = -1;
			}

			if ((!K8 && !K9 && K11 && K12) || (!K8 && !K9 && K10 && K11))
			{
				if (pwr_1) motor_1_pwr_b2 = 1;
			}
			else if ((K8 && K9) || (K7 && K8))
			{
				if (gnd_1) motor_1_pwr_b2 = -1;
			}
		}

		//// Motor 2
		{
			// E52
			bool e52_out_1;
			bool e52_out_2;
			bool e52_out_3;
			RelayNetwork_PACU( hooks_op_1, hooks_op_2, hooks_op_3, pwr_a, pwr_b, pwr_c, gnd_abc, gnd_abc, e52_out_1, e52_out_2, e52_out_3 );

			// E53
			bool e53_out_1;
			bool e53_out_2;
			bool e53_out_3;
			RelayNetwork_PACU( hooks_cl_1, hooks_cl_2, hooks_cl_3, pwr_a, pwr_b, pwr_c, gnd_abc, gnd_abc, e53_out_1, e53_out_2, e53_out_3 );

			// E1A, 2A, 3A
			// HACK split box to handle signal flow
			bool e1a_out_1;
			bool e1a_out_2;
			bool e1a_out_3;
			MomentaryRelays( e52_out_3 && e21b_off_out_1_m2, e52_out_2 && e21b_off_out_2_m2, e52_out_1 && e21b_off_out_3_m2, pwr_a, pwr_b, pwr_c, gnd_abc, gnd_abc, gnd_abc, e1a_out_1, e1a_out_2, e1a_out_3, tmp1, tmp2, tmp3 );

			// E4B, 5B, 6B
			bool e4b_out_1;
			bool e4b_out_2;
			bool e4b_out_3;
			MomentaryRelays( e53_out_1, e53_out_2, e53_out_3, pwr_a, pwr_b, pwr_c, gnd_abc, gnd_abc, gnd_abc, e4b_out_1, e4b_out_2, e4b_out_3, tmp1, tmp2, tmp3 );

			// E30, 44
			bool e30_out_1;
			bool e30_out_2;
			bool e30_out_3;
			TimeDelay( 0.5, e1a_out_1 && e21b_on_out_1_m2, dt, e30_ctrl_gnd_1_td_m2, e30_ctrl_gnd_1_m2 );
			TimeDelay( 0.5, e1a_out_2 && e21b_on_out_2_m2, dt, e30_ctrl_gnd_2_td_m2, e30_ctrl_gnd_2_m2 );
			TimeDelay( 0.5, e1a_out_3 && e21b_on_out_3_m2, dt, e30_ctrl_gnd_3_td_m2, e30_ctrl_gnd_3_m2 );
			MomentaryRelays( e30_ctrl_gnd_1_m2, e30_ctrl_gnd_2_m2, e30_ctrl_gnd_3_m2, pwr_a, pwr_b, pwr_c, gnd_abc, gnd_abc, gnd_abc, e30_out_1, e30_out_2, e30_out_3, tmp1, tmp2, tmp3 );

			// E31, 45
			bool e31_out_1;
			bool e31_out_2;
			TimeDelay( 0.5, e4b_out_1 && e21a_on_out_1_m2, dt, e31_ctrl_gnd_1_td_m2, e31_ctrl_gnd_1_m2 );
			TimeDelay( 0.5, e4b_out_2 && e21a_on_out_2_m2, dt, e31_ctrl_gnd_2_td_m2, e31_ctrl_gnd_2_m2 );
			TimeDelay( 0.5, e4b_out_3 && e21a_on_out_3_m2, dt, e31_ctrl_gnd_3_td_m2, e31_ctrl_gnd_3_m2 );
			{
				// custom circuit
				bool k1 = !e31_ctrl_gnd_1_m2 && pwr_a;
				bool k2 = !e31_ctrl_gnd_2_m2 && pwr_b;
				bool k3 = !e31_ctrl_gnd_3_m2 && pwr_c;

				// HACK info not clear
				bool o1 = k1 && (k2 || k3);
				bool o2 = k1 && (k2 || k3);

				e31_out_1 = gnd_abc || !o1;
				e31_out_2 = gnd_abc || !o2;
			}

			// E21A, 22A, 23A
			// HACK split box to handle signal flow
			MomentaryRelays( e30_out_1, e30_out_2, e30_out_3, pwr_a, pwr_b, pwr_c, e4b_out_1, e4b_out_2, e4b_out_3, tmp1, tmp2, tmp3, e21a_off_out_1_m2, e21a_off_out_2_m2, e21a_off_out_3_m2 );
			MomentaryRelays( e30_out_1, e30_out_2, e30_out_3, pwr_a, pwr_b, pwr_c, hooks_op_ind_1, hooks_op_ind_2, hooks_op_ind_3, e21a_on_out_1_m2, e21a_on_out_2_m2, e21a_on_out_3_m2, tmp1, tmp2, tmp3 );

			// E21B, 22B, 23B
			// HACK split box to handle signal flow
			MomentaryRelays( e31_out_1 && e31_out_2, e31_out_1 && e31_out_2, e31_out_1 && e31_out_2, pwr_a, pwr_b, pwr_c, e1a_out_1, e1a_out_2, e1a_out_3, tmp1, tmp2, tmp3, e21b_off_out_1_m2, e21b_off_out_2_m2, e21b_off_out_3_m2 );
			MomentaryRelays( e31_out_1 && e31_out_2, e31_out_1 && e31_out_2, e31_out_1 && e31_out_2, pwr_a, pwr_b, pwr_c, hooks_cl_ind_1, hooks_cl_ind_2, hooks_cl_ind_3, e21b_on_out_1_m2, e21b_on_out_2_m2, e21b_on_out_3_m2, tmp1, tmp2, tmp3 );

			// E1B, 2B, 3B
			bool e1b_out_1;
			bool e1b_out_2;
			bool e1b_out_3;
			MomentaryRelays( e52_out_3 && e21b_off_out_1_m2, e52_out_2 && e21b_off_out_2_m2, e52_out_1 && e21b_off_out_3_m2, pwr_a, pwr_b, pwr_c, e21b_off_out_1_m2, e21b_off_out_2_m2, e21b_off_out_3_m2, tmp1, tmp2, tmp3, e1b_out_1, e1b_out_2, e1b_out_3 );

			// E4A, 5A, 6A
			bool e4a_out_1;
			bool e4a_out_2;
			bool e4a_out_3;
			MomentaryRelays( e53_out_1 && e21a_off_out_1_m2, e53_out_2 && e21a_off_out_2_m2, e53_out_3 && e21a_off_out_3_m2, pwr_a, pwr_b, pwr_c, e21b_off_out_1_m2, e21b_off_out_2_m2, e21b_off_out_3_m2, tmp1, tmp2, tmp3, e4a_out_1, e4a_out_2, e4a_out_3 );

			// K
			bool K16 = pwr_a && !e1b_out_1;
			bool K19 = pwr_a && !e1b_out_1;
			bool K17 = pwr_b && !e1b_out_2;
			bool K20 = pwr_b && !e1b_out_2;
			bool K18 = pwr_c && !e1b_out_3;
			bool K21 = pwr_c && !e1b_out_3;

			bool K13 = pwr_a && !e4a_out_3;
			bool K22 = pwr_a && !e4a_out_3;
			bool K14 = pwr_b && !e4a_out_2;
			bool K23 = pwr_b && !e4a_out_2;
			bool K15 = pwr_c && !e4a_out_1;
			bool K24 = pwr_c && !e4a_out_1;

			// motor power/ground
			// output: 0=off; +1=open; -1=close
			motor_2_pwr_a1 = 0;
			motor_2_pwr_a2 = 0;

			if ((!K13 && !K14 && K16 && K18) || (!K13 && K14 && !K15 && K17 && K18) || (!K13 && K14 && !K15 && K16 && K17))
			{
				if (pwr_2) motor_2_pwr_a1 = 1;
			}
			else if (K13 && K15)
			{
				if (gnd_2) motor_2_pwr_a1 = -1;
			}

			if ((!K14 && !K15 && K17 && K18) || (!K14 && !K15 && K16 && K17))
			{
				if (pwr_2) motor_2_pwr_a2 = 1;
			}
			else if ((K14 && K15) || (K13 && K14))
			{
				if (gnd_2) motor_2_pwr_a2 = -1;
			}

			motor_2_pwr_b1 = 0;
			motor_2_pwr_b2 = 0;

			if ((!K19 && !K20 && K22 && K24) || (!K19 && K20 && !K21 && K23 && K24) || (!K19 && K20 && !K21 && K22 && K23))
			{
				if (pwr_2) motor_2_pwr_b1 = 1;
			}
			else if (K19 && K21)
			{
				if (gnd_2) motor_2_pwr_b1 = -1;
			}

			if ((!K20 && !K21 && K23 && K24) || (!K20 && !K21 && K22 && K23))
			{
				if (pwr_2) motor_2_pwr_b2 = 1;
			}
			else if ((K20 && K21) || (K19 && K20))
			{
				if (gnd_2) motor_2_pwr_b2 = -1;
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
}

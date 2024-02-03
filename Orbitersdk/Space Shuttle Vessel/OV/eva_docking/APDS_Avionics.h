/****************************************************************************
  This file is part of Space Shuttle Vessel

  Androgynous Peripheral Docking System avionics definition


  Space Shuttle Vessel is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Vessel is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Vessel; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file SSV-LICENSE.txt for more details.

  **************************************************************************/
#ifndef _APDS_AVIONICS_H_
#define _APDS_AVIONICS_H_


#include <orbitersdk.h>


namespace eva_docking
{
	void _2of3VotingRelay( const bool ctrl_gnd_1, const bool ctrl_gnd_2, const bool ctrl_gnd_3, const bool ctrl_pwr_1, const bool ctrl_pwr_2, const bool ctrl_pwr_3, const bool in_1, const bool in_2, bool &out_1, bool &out_2 );


	class APDS_Avionics
	{
		protected:
			virtual void Load( char* keyword, char* line ) = 0;
			virtual void Save( FILEHANDLE scn ) const = 0;

			void LoadVarsTD3( char* line, double& tda, double& tdb, double& tdc );
			void LoadVarsOut( char* line, bool& vala, bool& valb, bool& valc );
			void SaveVarsOut( FILEHANDLE scn, char* name, const bool vala, const bool valb, const bool valc ) const;
			void SaveVarsTD3( FILEHANDLE scn, char* name, const double tda, const double tdb, const double tdc ) const;

		public:
			APDS_Avionics( void );
			virtual ~APDS_Avionics( void );

			bool ReadState( FILEHANDLE scn );
			void SaveState( FILEHANDLE scn ) const;
	};


	class PSU : public APDS_Avionics
	{
		private:
			bool K1;
			bool K2;
			bool K11;
			bool K12;
			bool K3;
			bool K4;
			bool K13;
			bool K14;
			bool K5;
			bool K6;
			bool K15;
			bool K16;

			bool e12_out_1;
			bool e12_out_2;
			bool e12_out_3;

			double e23_ctrl_gnd_1_td;
			double e23_ctrl_gnd_2_td;
			double e23_ctrl_gnd_3_td;

			double e12_ctrl_gnd_1_td;
			double e12_ctrl_gnd_2_td;
			double e12_ctrl_gnd_3_td;

			bool e10_out_on_1;
			bool e10_out_on_2;
			bool e10_out_on_3;


			void Load( char* keyword, char* line ) override;
			void Save( FILEHANDLE scn ) const override;

		public:
			struct PSU_IO
			{
				// in
				bool cntl_pnl_a;
				bool cntl_pnl_b;
				bool cntl_pnl_c;
				bool power_on;
				bool power_off;
				bool gnd_c;
				bool pwr_wa;
				bool pwr_wb;
				bool pwr_wc;
				// out
				bool pwr_on_reset_1;
				bool pwr_on_reset_2;
				bool pwr_on_reset_3;
				bool pwr_off_reset_1;
				bool pwr_off_reset_2;
				bool pwr_off_reset_3;
				bool gnd_c_1;
				bool gnd_c_2;
				bool gnd_c_3;
				bool pwr_wa_1;
				bool pwr_wa_2;
				bool pwr_wb_1;
				bool pwr_wb_2;
				bool pwr_wc_1;
				bool pwr_wc_2;
			};

			PSU( void );
			virtual ~PSU( void ) {};

			void Run( const double dt, PSU_IO& io );
	};


	class DSCU : public APDS_Avionics
	{
		private:
			bool gnd_ct1;
			bool gnd_ct2;
			bool gnd_ct3;

			bool kp1;
			bool kp2;
			bool kp3;

			bool kp11;
			bool kp12;
			bool kp13;
			bool kp14;
			bool kp15;
			bool kp16;
			bool kp17;
			bool kp18;
			bool kp19;

			bool e102_out_1;
			bool e102_out_2;
			bool e102_out_3;

			bool e124_out_1;
			bool e124_out_2;
			bool e124_out_3;

			bool e113_out_1;
			bool e113_out_2;
			bool e113_out_3;

			bool e114_out_1;
			bool e114_out_2;
			bool e114_out_3;

			bool e148_out_1;
			bool e148_out_2;
			bool e148_out_3;

			bool e37_out_1;
			bool e37_out_2;
			bool e37_out_3;

			bool e103_out_1;
			bool e103_out_2;
			bool e103_out_3;

			bool e134_out_1;
			bool e134_out_2;
			bool e134_out_3;

			bool e1_out_off_1;
			bool e1_out_off_2;
			bool e1_out_off_3;

			bool e128_out_1;
			bool e128_out_2;
			bool e128_out_3;

			bool e139_out_1;
			bool e139_out_2;
			bool e139_out_3;

			bool e140_out_1;
			bool e140_out_2;
			bool e140_out_3;

			bool e15_out_off_1;
			bool e15_out_off_2;
			bool e15_out_off_3;

			double e31_ctrl_gnd_1_td;
			double e31_ctrl_gnd_2_td;
			double e31_ctrl_gnd_3_td;

			double e33_ctrl_gnd_1_td;
			double e33_ctrl_gnd_2_td;
			double e33_ctrl_gnd_3_td;

			double kt4_td;

			double kt5_td;

			double kt6_td;

			double kt60_td;

			double kt61_td;

			double kt62_td;

			double e206_ctrl_gnd_1_td;
			double e206_ctrl_gnd_2_td;
			double e206_ctrl_gnd_3_td;

			double e204_ctrl_gnd_1_td;
			double e204_ctrl_gnd_2_td;
			double e204_ctrl_gnd_3_td;

			double e1_ctrl_gnd_1_td;
			double e1_ctrl_gnd_2_td;
			double e1_ctrl_gnd_3_td;

			double e208_ctrl_gnd_1_td;
			double e208_ctrl_gnd_2_td;
			double e208_ctrl_gnd_3_td;

			double e28_ctrl_gnd_1_td;
			double e28_ctrl_gnd_2_td;
			double e28_ctrl_gnd_3_td;

			double e202_ctrl_gnd_1_td;
			double e202_ctrl_gnd_2_td;
			double e202_ctrl_gnd_3_td;

			double e101_ctrl_gnd_1_td;
			double e101_ctrl_gnd_2_td;
			double e101_ctrl_gnd_3_td;

			double brake_set_1_td;
			double brake_set_2_td;
			double brake_set_3_td;

			double brake_reset_30_1_td;
			double brake_reset_30_2_td;
			double brake_reset_30_3_td;

			double brake_reset_5_1_td;
			double brake_reset_5_2_td;
			double brake_reset_5_3_td;

			void Load( char* keyword, char* line ) override;
			void Save( FILEHANDLE scn ) const override;

		public:
			struct DSCU_IO
			{
				// in
				bool pwr_a;
				bool pwr_b;
				bool pwr_c;
				bool pwr_cntl_pnl_a;
				bool pwr_cntl_pnl_b;
				bool pwr_cntl_pnl_c;
				bool pwr_tf3m12;
				bool pwr_tf3m345;
				bool gnd_abc;
				bool gnd_pnl;
				bool gnd_tf3m12;
				bool gnd_tf3m345;
				bool pwr_on_reset_1;
				bool pwr_on_reset_2;
				bool pwr_on_reset_3;
				bool pwr_off_reset_1;
				bool pwr_off_reset_2;
				bool pwr_off_reset_3;
				bool gnd_hooks_1_cl_1;
				bool gnd_hooks_1_cl_2;
				bool gnd_hooks_1_cl_3;
				bool gnd_hooks_2_cl_1;
				bool gnd_hooks_2_cl_2;
				bool gnd_hooks_2_cl_3;
				bool open_hooks;
				bool close_hooks;
				bool open_latches;
				bool close_latches;
				bool ring_in;
				bool ring_out;
				bool undocking;
				bool apds_circ_prot_off;
				bool fixeroff;
				bool hooks_1_cl_ind_1;
				bool hooks_1_cl_ind_2;
				bool hooks_1_cl_ind_3;
				bool hooks_1_op_ind_1;
				bool hooks_1_op_ind_2;
				bool hooks_1_op_ind_3;
				bool hooks_2_cl_ind_1;
				bool hooks_2_cl_ind_2;
				bool hooks_2_cl_ind_3;
				bool hooks_2_op_ind_1;
				bool hooks_2_op_ind_2;
				bool hooks_2_op_ind_3;
				bool latches_cl_ind_1;
				bool latches_cl_ind_2;
				bool latches_op_ind_1;
				bool latches_op_ind_2;
				bool ringfinalposition_ind_1;
				bool ringfinalposition_ind_2;
				bool ringforwardposition_ind_1;
				bool ringforwardposition_ind_2;
				bool ringinitialposition_ind_1;
				bool ringinitialposition_ind_2;
				bool interfacesealed_ind_1;
				bool interfacesealed_ind_2;
				bool interfacesealed_ind_3;
				bool undockingcomplete_ind_1;
				bool undockingcomplete_ind_2;
				bool readytohook_ind_1;
				bool readytohook_ind_2;
				bool inbetweenhooks_ind_1;
				bool inbetweenhooks_ind_2;
				bool captureshort_ind_1;
				bool captureshort_ind_2;
				bool capturelong_ind_1;
				bool capturelong_ind_2;
				bool ringaligned_ind_1;
				bool ringaligned_ind_2;
				bool initialcontact_ind_1;
				bool initialcontact_ind_2;
				bool lacu_ring_in_cmd_1;
				bool lacu_ring_in_cmd_2;
				bool lacu_ring_in_cmd_3;
				// out
				bool hooks_1_op_cmd_1;
				bool hooks_1_op_cmd_2;
				bool hooks_1_op_cmd_3;
				bool hooks_1_cl_cmd_1;
				bool hooks_1_cl_cmd_2;
				bool hooks_1_cl_cmd_3;
				bool hooks_2_op_cmd_1;
				bool hooks_2_op_cmd_2;
				bool hooks_2_op_cmd_3;
				bool hooks_2_cl_cmd_1;
				bool hooks_2_cl_cmd_2;
				bool hooks_2_cl_cmd_3;
				bool hooks_1_cl_light_1;
				bool hooks_1_cl_light_2;
				bool hooks_1_cl_light_3;
				bool hooks_1_op_light_1;
				bool hooks_1_op_light_2;
				bool hooks_1_op_light_3;
				bool hooks_2_cl_light_1;
				bool hooks_2_cl_light_2;
				bool hooks_2_cl_light_3;
				bool hooks_2_op_light_1;
				bool hooks_2_op_light_2;
				bool hooks_2_op_light_3;
				bool latches_op_cmd_1;
				bool latches_op_cmd_2;
				bool latches_op_cmd_3;
				bool latches_cl_cmd_1;
				bool latches_cl_cmd_2;
				bool latches_cl_cmd_3;
				bool ring_out_cmd_1;
				bool ring_out_cmd_2;
				bool ring_out_cmd_3;
				bool ring_out_stop_cmd_1;
				bool ring_out_stop_cmd_2;
				bool ring_out_stop_cmd_3;
				bool ring_in_cmd_1;
				bool ring_in_cmd_2;
				bool ring_in_cmd_3;
				bool ring_in_stop_cmd_1;
				bool ring_in_stop_cmd_2;
				bool ring_in_stop_cmd_3;
				bool latchesclosed_light_1;
				bool latchesclosed_light_2;
				bool latchesclosed_light_3;
				bool latchesopen_light_1;
				bool latchesopen_light_2;
				bool latchesopen_light_3;
				bool ringinitialposition_light_1;
				bool ringinitialposition_light_2;
				bool ringinitialposition_light_3;
				bool ringforwardposition_light_1;
				bool ringforwardposition_light_2;
				bool ringforwardposition_light_3;
				bool ringfinalposition_light_1;
				bool ringfinalposition_light_2;
				bool ringfinalposition_light_3;
				bool power_on_light_1;
				bool power_on_light_2;
				bool power_on_light_3;
				bool readytohook_light_1;
				bool readytohook_light_2;
				bool readytohook_light_3;
				bool interfsealed_light_1;
				bool interfsealed_light_2;
				bool interfsealed_light_3;
				bool undockcomplet_light_1;
				bool undockcomplet_light_2;
				bool apdscirprotoff_light_1;
				bool apdscirprotoff_light_2;
				bool fixersoff_light_1;
				bool fixersoff_light_2;
				bool fixersoff_light_3;
				bool initialcontact_light_1;
				bool initialcontact_light_2;
				bool initialcontact_light_3;
				bool capturecapture_light_1;
				bool capturecapture_light_2;
				bool capturecapture_light_3;
				bool ringaligned_light_1;
				bool ringaligned_light_2;
				bool ringaligned_light_3;
				bool fixer_1_pwr;
				bool fixer_1_gnd;
				bool fixer_2_pwr;
				bool fixer_2_gnd;
				bool fixer_3_pwr;
				bool fixer_3_gnd;
				bool fixer_4_pwr;
				bool fixer_4_gnd;
				bool fixer_5_pwr;
				bool fixer_5_gnd;
				bool brake_1_pwr;
				bool brake_1_gnd;
				bool brake_2_pwr;
				bool brake_2_gnd;
				bool brake_3_pwr;
				bool brake_3_gnd;
			};

			DSCU( void );
			virtual ~DSCU( void ) {};

			void Run( const double dt, DSCU_IO& io );
	};


	class DMCU : public APDS_Avionics
	{
		private:
			bool K01;
			bool K02;
			bool K03;
			bool K04;
			bool K05;
			bool K06;
			bool K07;
			bool K08;


			void Load( char* keyword, char* line ) override;
			void Save( FILEHANDLE scn ) const override;

		public:
			struct DMCU_IO
			{
				// in
				bool pwr_a;
				bool pwr_b;
				bool pwr_c;
				bool gnd_abc;
				bool pwr_c1;
				bool pwr_c2;
				bool gnd_c1;
				bool gnd_c2;
				bool ring_out_cmd_1;
				bool ring_out_cmd_2;
				bool ring_out_cmd_3;
				bool ring_out_stop_cmd_1;
				bool ring_out_stop_cmd_2;
				bool ring_out_stop_cmd_3;
				bool ring_in_cmd_1;
				bool ring_in_cmd_2;
				bool ring_in_cmd_3;
				bool ring_in_stop_cmd_1;
				bool ring_in_stop_cmd_2;
				bool ring_in_stop_cmd_3;
				// out
				short motor_1_pwr_a1;
				short motor_1_pwr_a2;
				short motor_1_pwr_b1;
				short motor_1_pwr_b2;
				short motor_2_pwr_a1;
				short motor_2_pwr_a2;
				short motor_2_pwr_b1;
				short motor_2_pwr_b2;
			};

			DMCU( void );
			virtual ~DMCU( void ) {};

			void Run( DMCU_IO& io );
	};


	class PACU : public APDS_Avionics
	{
		private:
			bool e21a_off_out_1_m1;
			bool e21a_off_out_2_m1;
			bool e21a_off_out_3_m1;
			bool e21a_on_out_1_m1;
			bool e21a_on_out_2_m1;
			bool e21a_on_out_3_m1;
			bool e21a_off_out_1_m2;
			bool e21a_off_out_2_m2;
			bool e21a_off_out_3_m2;
			bool e21a_on_out_1_m2;
			bool e21a_on_out_2_m2;
			bool e21a_on_out_3_m2;

			bool e21b_off_out_1_m1;
			bool e21b_off_out_2_m1;
			bool e21b_off_out_3_m1;
			bool e21b_on_out_1_m1;
			bool e21b_on_out_2_m1;
			bool e21b_on_out_3_m1;
			bool e21b_off_out_1_m2;
			bool e21b_off_out_2_m2;
			bool e21b_off_out_3_m2;
			bool e21b_on_out_1_m2;
			bool e21b_on_out_2_m2;
			bool e21b_on_out_3_m2;

			double e30_ctrl_gnd_1_td_m1;
			double e30_ctrl_gnd_2_td_m1;
			double e30_ctrl_gnd_3_td_m1;

			double e30_ctrl_gnd_1_td_m2;
			double e30_ctrl_gnd_2_td_m2;
			double e30_ctrl_gnd_3_td_m2;

			double e31_ctrl_gnd_1_td_m1;
			double e31_ctrl_gnd_2_td_m1;
			double e31_ctrl_gnd_3_td_m1;

			double e31_ctrl_gnd_1_td_m2;
			double e31_ctrl_gnd_2_td_m2;
			double e31_ctrl_gnd_3_td_m2;


			void Load( char* keyword, char* line ) override;
			void Save( FILEHANDLE scn ) const override;

		public:
			struct PACU_IO
			{
				// in
				bool gnd_1;
				bool gnd_2;
				bool gnd_abc;
				bool pwr_1;
				bool pwr_2;
				bool pwr_a;
				bool pwr_b;
				bool pwr_c;
				bool hooks_cl_cmd_1;
				bool hooks_cl_cmd_2;
				bool hooks_cl_cmd_3;
				bool hooks_op_cmd_1;
				bool hooks_op_cmd_2;
				bool hooks_op_cmd_3;
				bool hooks_cl_ind_a;
				bool hooks_cl_ind_b;
				bool hooks_op_ind_a;
				bool hooks_op_ind_b;
				// out
				short motor_1_pwr_a1;
				short motor_1_pwr_a2;
				short motor_1_pwr_b1;
				short motor_1_pwr_b2;
				short motor_2_pwr_a1;
				short motor_2_pwr_a2;
				short motor_2_pwr_b1;
				short motor_2_pwr_b2;
				bool hooks_cl_ind_1;
				bool hooks_cl_ind_2;
				bool hooks_cl_ind_3;
				bool hooks_op_ind_1;
				bool hooks_op_ind_2;
				bool hooks_op_ind_3;
				bool gnd_hooks_cl_1;
				bool gnd_hooks_cl_2;
				bool gnd_hooks_cl_3;
			};

			PACU( void );
			virtual ~PACU( void ) {};

			void Run( const double dt, PACU_IO& io );
	};


	class LACU : public APDS_Avionics
	{
		private:
			bool K1;
			bool K2;
			bool K3;
			bool K4;
			bool K5;
			bool K6;
			bool K7;
			bool K8;

			double kt16_td;

			double kt17_td;

			double kt18_td;


			void Load( char* keyword, char* line ) override;
			void Save( FILEHANDLE scn ) const override;

		public:
			struct LACU_IO
			{
				// in
				bool pwr_a;
				bool pwr_b;
				bool pwr_c;
				bool pwr_n3k1;
				bool pwr_n3k2;
				bool pwr_n3k3;
				bool gnd_abc;
				bool latches_op_cmd_1;
				bool latches_op_cmd_2;
				bool latches_op_cmd_3;
				bool latches_cl_cmd_1;
				bool latches_cl_cmd_2;
				bool latches_cl_cmd_3;
				bool latches_cl_ind_a;
				bool latches_cl_ind_b;
				bool latches_op_ind_a;
				bool latches_op_ind_b;
				bool latch_1_ret_gnd_1;
				bool latch_1_ret_gnd_2;
				bool latch_2_ret_gnd_1;
				bool latch_2_ret_gnd_2;
				bool latch_3_ret_gnd_1;
				bool latch_3_ret_gnd_2;
				// out
				bool latches_cl_ind_1;
				bool latches_cl_ind_2;
				bool latches_op_ind_1;
				bool latches_op_ind_2;
				bool latch_motor_cl_gnd_1;
				bool latch_motor_cl_gnd_2;
				bool latch_motor_op_gnd_1;
				bool latch_motor_op_gnd_2;
				bool latch_1_motor_pwr_1;
				bool latch_1_motor_pwr_2;
				bool latch_2_motor_pwr_1;
				bool latch_2_motor_pwr_2;
				bool latch_3_motor_pwr_1;
				bool latch_3_motor_pwr_2;
				bool ring_in_cmd_1;
				bool ring_in_cmd_2;
				bool ring_in_cmd_3;
			};

			LACU( void );
			virtual ~LACU( void ) {};

			void Run( const double dt, LACU_IO& io );
	};
}

#endif// _APDS_AVIONICS_H_

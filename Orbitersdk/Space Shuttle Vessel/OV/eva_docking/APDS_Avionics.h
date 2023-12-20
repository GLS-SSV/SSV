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


namespace eva_docking
{
	void _2of3VotingRelay( const bool ctrl_gnd_1, const bool ctrl_gnd_2, const bool ctrl_gnd_3, const bool ctrl_pwr_1, const bool ctrl_pwr_2, const bool ctrl_pwr_3, const bool in_1, const bool in_2, bool &out_1, bool &out_2 );


	class PSU
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

			bool e23_ctrl_gnd_1;
			bool e23_ctrl_gnd_2;
			bool e23_ctrl_gnd_3;
			double e23_ctrl_gnd_1_td;
			double e23_ctrl_gnd_2_td;
			double e23_ctrl_gnd_3_td;

			bool e12_ctrl_gnd_1;
			bool e12_ctrl_gnd_2;
			bool e12_ctrl_gnd_3;
			double e12_ctrl_gnd_1_td;
			double e12_ctrl_gnd_2_td;
			double e12_ctrl_gnd_3_td;

			bool e10_out_on_1;
			bool e10_out_on_2;
			bool e10_out_on_3;

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
				bool wa;
				bool wb;
				bool wc;
				bool cw1;
				bool cw2;
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
			void Load( void );
			void Save( void ) const;
	};


	class DSCU
	{
		private:
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

			bool e31_ctrl_gnd_1;
			bool e31_ctrl_gnd_2;
			bool e31_ctrl_gnd_3;
			double e31_ctrl_gnd_1_td;
			double e31_ctrl_gnd_2_td;
			double e31_ctrl_gnd_3_td;

			bool e33_ctrl_gnd_1;
			bool e33_ctrl_gnd_2;
			bool e33_ctrl_gnd_3;
			double e33_ctrl_gnd_1_td;
			double e33_ctrl_gnd_2_td;
			double e33_ctrl_gnd_3_td;

			bool e35_ctrl_gnd_1;
			bool e35_ctrl_gnd_2;
			bool e35_ctrl_gnd_3;
			double e35_ctrl_gnd_1_td;
			double e35_ctrl_gnd_2_td;
			double e35_ctrl_gnd_3_td;

			bool e145_ctrl_gnd_1;
			bool e145_ctrl_gnd_2;
			bool e145_ctrl_gnd_3;
			double e145_ctrl_gnd_1_td;
			double e145_ctrl_gnd_2_td;
			double e145_ctrl_gnd_3_td;

		public:
			struct DSCU_IO
			{
				// in
				bool pwr_a;
				bool pwr_b;
				bool pwr_c;
				bool gnd_abc;
				bool gnd_pnl;
				bool gnd_hooks_1_cl_1;
				bool gnd_hooks_1_cl_2;
				bool gnd_hooks_1_cl_3;
				bool gnd_hooks_2_cl_1;
				bool gnd_hooks_2_cl_2;
				bool gnd_hooks_2_cl_3;
				bool open_hooks;
				bool close_hooks;
				bool undocking;
				bool apds_circ_prot_off;
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
				bool interfacesealed_ind_1;
				bool interfacesealed_ind_2;
				bool interfacesealed_ind_3;
				bool undockingcomplete_ind_1;
				bool undockingcomplete_ind_2;
				bool readytohook_ind_1;
				bool readytohook_ind_2;
				bool inbetweenhooks_ind_1;
				bool inbetweenhooks_ind_2;
				// out
				bool hooks_1_op_1;
				bool hooks_1_op_2;
				bool hooks_1_op_3;
				bool hooks_1_cl_1;
				bool hooks_1_cl_2;
				bool hooks_1_cl_3;
				bool hooks_2_op_1;
				bool hooks_2_op_2;
				bool hooks_2_op_3;
				bool hooks_2_cl_1;
				bool hooks_2_cl_2;
				bool hooks_2_cl_3;
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
			};

			DSCU( void );
			virtual ~DSCU( void ) {};

			void Run( const double dt, DSCU_IO& io );
			void Load( void );
			void Save( void ) const;
	};


	class DMCU
	{
		private:

		public:
			DMCU( void );
			virtual ~DMCU( void ) {};

			void Run( bool a, bool b, bool c );
			void Load( void );
			void Save( void ) const;
	};


	class PACU
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

			bool e30_ctrl_gnd_1_m1;
			bool e30_ctrl_gnd_2_m1;
			bool e30_ctrl_gnd_3_m1;
			double e30_ctrl_gnd_1_td_m1;
			double e30_ctrl_gnd_2_td_m1;
			double e30_ctrl_gnd_3_td_m1;
			bool e30_ctrl_gnd_1_m2;
			bool e30_ctrl_gnd_2_m2;
			bool e30_ctrl_gnd_3_m2;
			double e30_ctrl_gnd_1_td_m2;
			double e30_ctrl_gnd_2_td_m2;
			double e30_ctrl_gnd_3_td_m2;

			bool e31_ctrl_gnd_1_m1;
			bool e31_ctrl_gnd_2_m1;
			bool e31_ctrl_gnd_3_m1;
			double e31_ctrl_gnd_1_td_m1;
			double e31_ctrl_gnd_2_td_m1;
			double e31_ctrl_gnd_3_td_m1;
			bool e31_ctrl_gnd_1_m2;
			bool e31_ctrl_gnd_2_m2;
			bool e31_ctrl_gnd_3_m2;
			double e31_ctrl_gnd_1_td_m2;
			double e31_ctrl_gnd_2_td_m2;
			double e31_ctrl_gnd_3_td_m2;

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
				bool hooks_cl_1;
				bool hooks_cl_2;
				bool hooks_cl_3;
				bool hooks_op_1;
				bool hooks_op_2;
				bool hooks_op_3;
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
			void Load( void );
			void Save( void ) const;
	};


	class LACU
	{
		private:

		public:
			LACU( void );
			virtual ~LACU( void ) {};

			void Run( bool a, bool b, bool c );
			void Load( void );
			void Save( void ) const;
	};
}

#endif// _APDS_AVIONICS_H_

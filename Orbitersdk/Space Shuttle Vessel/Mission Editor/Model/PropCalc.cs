using System;


namespace SSVMissionEditor
{
	class PropCalc
	{
		const double G = 0.0000000000667259;// gravitational constant [m^3 kg^-1 s^-2]
		const double M = 5.973698968E+24;// Earth mass [kg]
		const double mu = G * M;
		const double R = 6371010.0;// Earth radius [m]
		const double g = 9.80665;// Earth gravitational acceleration [m/s^2]

		// IUS params
		const double STAGE1_EMPTYMASS = 1123.276;// kg
		const double STAGE2_EMPTYMASS = 1010.649;// kg
		const double STAGE2_EEC_EMPTYMASS = 1054.19387;// kg

		const double STAGE1_PROPELLANT_MAXMASS = 9708.6;// kg
		const double STAGE2_PROPELLANT_MAXMASS = 2749.133;// kg

		const double STAGE1_ISP_VAC = 295.5;// s
		const double STAGE2_ISP_VAC = 289.1;// s
		const double STAGE2_EEC_ISP_VAC = 303.5;// s
		const double RCS_ISP_VAC = 320.0;// s

		const double RCS_THRUST_VAC = 157.6;// N (or 133N???)

		const double RCS_TANK_PROPELLANT_MASS = 55.56507;// kg

		// RCS Propellant allocation ratio (mass equivalent for 2 tanks)
		const double RCS_PROP_RATIO_ATT_PRE_SRM1 = 0.041;// Attitude Control (10.2 lbm)
		const double RCS_PROP_RATIO_AUG_SRM1 = 0.160;// Augment SRM-1 Burn (39.7 lbm)
		const double RCS_PROP_RATIO_ATT_PRE_SRM2 = 0.137;// Attitude Control (33.9 lbm)
		const double RCS_PROP_RATIO_AUG_SRM2 = 0.382;// Augment SRM-2 Burn (94.5 lbm)
		const double RCS_PROP_RATIO_ATT_POST_SRM2 = 0.028;// Attitude Control & CAM (7.0 lbm)
		const double RCS_PROP_RATIO_RESERVE = 0.252;// Reserves & Trapped (62.5 lbm)

		const double RCS_BURN_TIME = (RCS_TANK_PROPELLANT_MASS * RCS_ISP_VAC) / RCS_THRUST_VAC;// total RCS burn time for 1 tank [s]

		const double IUS_PROP_LOAD_MIN = 0.5;
		const double IUS_PROP_LOAD_MAX = 1.0;


		public PropCalc()
		{
			return;
		}

		/**
		 * Calculate IUS stage propellant load needed to send a payload mass from a initial circular orbit to a final circular orbit, with an inclination change on the apogee.
		 * @arg curAlt		altitude of initial circular orbit [km]
		 * @arg tgtAlt		altitude of target circular orbit [km]
		 * @arg dInc1		inclination change during SRM-1 burn [deg]
		 * @arg dInc2		inclination change during SRM-2 burn [deg]
		 * @arg payloadmass	payload mass [kg]
		 * @arg RCStanks	number of RCS tanks installed [1]
		 * @arg EEC		EEC installed [1]
		 * @arg load1		output stage 1 propellant load [1]
		 * @arg load2		output stage 2 propellant load [1]
		 * @arg strresult	output of result text [1]
		 **/
		public void IUS_Orbital( double curAlt, double tgtAlt, double dInc1, double dInc2, double payloadmass, int RCStanks, bool EEC, ref double load1, ref double load2, ref string strresult )
		{
			double SRM1dV = 0;// [m/s]
			double RCS1dV = 0;// [m/s]
			double SRM1propMass = 0;// [kg]
			double SRM1load = 0;
			double SRM1perfdelta = 0;// [m/s]
			bool SRM1over = false;
			bool SRM1under = false;
			double SRM2dV = 0;// [m/s]
			double RCS2dV = 0;// [m/s]
			double SRM2propMass = 0;// [kg]
			double SRM2load = 0;
			double RCSmass = 0;// [kg]
			double RCStotmass = RCStanks * RCS_TANK_PROPELLANT_MASS;// [kg]
			double SRM2dryMass = (EEC ? STAGE2_EEC_EMPTYMASS : STAGE2_EMPTYMASS) + payloadmass;// [kg]
			double SRM2Isp = EEC ? STAGE2_EEC_ISP_VAC : STAGE2_ISP_VAC;
			double SRM2perfdelta = 0;// [m/s]
			bool SRM2over = false;
			bool SRM2under = false;

			// get SRM-2 prop load
			// get required ap dV
			SRM2dV = GetApBurndV( curAlt, tgtAlt, dInc2 );

			// get RCS 2 burn dV and subtract from total
			RCSmass = RCStotmass * (RCS_PROP_RATIO_RESERVE + RCS_PROP_RATIO_ATT_POST_SRM2);
			RCS2dV = GetdV( SRM2dryMass + RCSmass, RCStotmass * RCS_PROP_RATIO_AUG_SRM2, RCS_ISP_VAC );
			SRM2dV -= RCS2dV;

			// get needed SRM 2 burn prop needed for rest of dV
			RCSmass = RCStotmass * (RCS_PROP_RATIO_RESERVE + RCS_PROP_RATIO_ATT_POST_SRM2 + RCS_PROP_RATIO_AUG_SRM2);
			SRM2propMass = GetBurnPropMass( SRM2dryMass + RCSmass, SRM2Isp, SRM2dV );
			if (SRM2propMass > (STAGE2_PROPELLANT_MAXMASS * IUS_PROP_LOAD_MAX))
			{
				// under-performance
				SRM2under = true;
				double SRM2dVact = GetdV( SRM2dryMass + RCSmass, STAGE2_PROPELLANT_MAXMASS * IUS_PROP_LOAD_MAX, SRM2Isp );// actual stage max performance
				SRM2perfdelta = SRM2dVact - SRM2dV;
				SRM2dV = SRM2dVact;
				SRM2propMass = STAGE2_PROPELLANT_MAXMASS * IUS_PROP_LOAD_MAX;
				SRM2load = IUS_PROP_LOAD_MAX;
			}
			else if (SRM2propMass < (STAGE2_PROPELLANT_MAXMASS * IUS_PROP_LOAD_MIN))
			{
				// over-performance
				SRM2over = true;
				double SRM2dVact = GetdV( SRM2dryMass + RCSmass, STAGE2_PROPELLANT_MAXMASS * IUS_PROP_LOAD_MIN, SRM2Isp );// actual stage min performance
				SRM2perfdelta = SRM2dVact - SRM2dV;
				SRM2dV = SRM2dVact;
				SRM2propMass = STAGE2_PROPELLANT_MAXMASS * IUS_PROP_LOAD_MIN;
				SRM2load = IUS_PROP_LOAD_MIN;
			}
			else
			{
				SRM2load = SRM2propMass / STAGE2_PROPELLANT_MAXMASS;
			}


			// get SRM-1 prop load
			double SRM1dryMass = STAGE1_EMPTYMASS + SRM2dryMass + SRM2propMass;

			// get required pe dV
			SRM1dV = GetPeBurndV( curAlt, tgtAlt, dInc1 );

			// get RCS 1 burn dV and subtract from total
			RCSmass = RCStotmass * (RCS_PROP_RATIO_RESERVE + RCS_PROP_RATIO_ATT_POST_SRM2 + RCS_PROP_RATIO_AUG_SRM2 + RCS_PROP_RATIO_ATT_PRE_SRM2);
			RCS1dV = GetdV( SRM1dryMass + RCSmass, RCStotmass * RCS_PROP_RATIO_AUG_SRM1, RCS_ISP_VAC );
			SRM1dV -= RCS1dV;

			// get needed SRM 1 burn prop needed for rest of dV
			RCSmass = RCStotmass * (RCS_PROP_RATIO_RESERVE + RCS_PROP_RATIO_ATT_POST_SRM2 + RCS_PROP_RATIO_AUG_SRM2 + RCS_PROP_RATIO_ATT_PRE_SRM2 + RCS_PROP_RATIO_AUG_SRM1);
			SRM1propMass = GetBurnPropMass( SRM1dryMass + RCSmass, STAGE1_ISP_VAC, SRM1dV );
			if (SRM1propMass > (STAGE1_PROPELLANT_MAXMASS * IUS_PROP_LOAD_MAX))
			{
				// under-performance
				SRM1under = true;
				double SRM1dVact = GetdV( SRM1dryMass + RCSmass, STAGE1_PROPELLANT_MAXMASS * IUS_PROP_LOAD_MAX, STAGE1_ISP_VAC );// actual stage max performance
				SRM1perfdelta = SRM1dVact - SRM1dV;
				SRM1dV = SRM1dVact;
				SRM1propMass = STAGE1_PROPELLANT_MAXMASS * IUS_PROP_LOAD_MAX;
				SRM1load = IUS_PROP_LOAD_MAX;
			}
			else if (SRM1propMass < (STAGE1_PROPELLANT_MAXMASS * IUS_PROP_LOAD_MIN))
			{
				// over-performance
				SRM1over = true;
				double SRM1dVact = GetdV( SRM1dryMass + RCSmass, STAGE1_PROPELLANT_MAXMASS * IUS_PROP_LOAD_MIN, STAGE1_ISP_VAC );// actual stage min performance
				SRM1perfdelta = SRM1dVact - SRM1dV;
				SRM1dV = SRM1dVact;
				SRM1propMass = STAGE1_PROPELLANT_MAXMASS * IUS_PROP_LOAD_MIN;
				SRM1load = IUS_PROP_LOAD_MIN;
			}
			else
			{
				SRM1load = SRM1propMass / STAGE1_PROPELLANT_MAXMASS;
			}


			// output
			load1 = SRM1load;
			load2 = SRM2load;

			strresult = "SRM-1\n";
			if (SRM1under) strresult += "  Under perf: " + SRM1perfdelta.ToString("0.#") + " m/s\n";
			else if (SRM1over) strresult += "  Over perf: " + SRM1perfdelta.ToString("0.#") + " m/s\n";
			strresult += "  Load: " + SRM1load.ToString("0.##") + "\n";
			strresult += "  deltaV SRM: " + SRM1dV.ToString("0.#") + " m/s\n";
			strresult += "  deltaV RCS: " + RCS1dV.ToString("0.#") + " m/s\n";
			strresult += "  RCS burn time: " + (RCS_PROP_RATIO_AUG_SRM1 * RCS_BURN_TIME * RCStanks).ToString("0.#") + " s\n";

			strresult += "\n";
			strresult += "SRM-2\n";
			if (SRM2under) strresult += "  Under perf: " + SRM2perfdelta.ToString("0.#") + " m/s\n";
			else if (SRM2over) strresult += "  Over perf: " + SRM2perfdelta.ToString("0.#") + " m/s\n";
			strresult += "  Load: " + SRM2load.ToString("0.##") + "\n";
			strresult += "  deltaV SRM: " + SRM2dV.ToString("0.#") + " m/s\n";
			strresult += "  deltaV RCS: " + RCS2dV.ToString("0.#") + " m/s\n";
			strresult += "  RCS burn time: " + (RCS_PROP_RATIO_AUG_SRM2 * RCS_BURN_TIME * RCStanks).ToString("0.#") + " s";
			return;
		}

		/**
		 * Calculate IUS stage propellant load needed to send a payload mass on an escape trajectory, with the specified C3 characteristic energy.
		 * @arg curAlt		altitude of initial circular orbit [km]
		 * @arg C3		target C3 characteristic energy [km^2 / m^2]
		 * @arg payloadmass	payload mass [kg]
		 * @arg RCStanks	number of RCS tanks installed [1]
		 * @arg EEC		EEC installed? [1]
		 * @arg load1		output stage 1 propellant load [1]
		 * @arg load2		output stage 2 propellant load [1]
		 * @arg strresult	output of result text [1]
		 **/
		public void IUS_Escape( double curAlt, double C3, double payloadmass, int RCStanks, bool EEC, ref double load1, ref double load2, ref string strresult )
		{
			double SRM1dV = 0;
			double RCS1dV = 0;
			double SRM2dV = 0;
			double RCS2dV = 0;
			double RCSmass = 0;
			double RCStotmass = RCStanks * RCS_TANK_PROPELLANT_MASS;
			double SRM1dryMass = 0;
			double SRM2dryMass = (EEC ? STAGE2_EEC_EMPTYMASS : STAGE2_EMPTYMASS) + payloadmass;
			double SRM2Isp = EEC ? STAGE2_EEC_ISP_VAC : STAGE2_ISP_VAC;

			// get target dV
			double dVtgt = 0;// [m/s]
			dVtgt = GetC3BurndV( curAlt, C3 );

			// get RCS 2 burn dV
			RCSmass = RCStotmass * (RCS_PROP_RATIO_RESERVE + RCS_PROP_RATIO_ATT_POST_SRM2);
			RCS2dV = GetdV( SRM2dryMass + RCSmass, RCStotmass * RCS_PROP_RATIO_AUG_SRM2, RCS_ISP_VAC );

			int res = 0;
			double ld = IUS_PROP_LOAD_MAX;
			for (; ld >= IUS_PROP_LOAD_MIN; ld -= 0.1)// decrease performance until under req, then fine-tune forward
			{
				// get SRM 2 burn dV
				RCSmass = RCStotmass * (RCS_PROP_RATIO_RESERVE + RCS_PROP_RATIO_ATT_POST_SRM2 + RCS_PROP_RATIO_AUG_SRM2);
				SRM2dV = GetdV( SRM2dryMass + RCSmass, (STAGE2_PROPELLANT_MAXMASS * ld), SRM2Isp );

				// get RCS 1 burn dV
				SRM1dryMass = STAGE1_EMPTYMASS + SRM2dryMass + (STAGE2_PROPELLANT_MAXMASS * ld);
				RCSmass = RCStotmass * (RCS_PROP_RATIO_RESERVE + RCS_PROP_RATIO_ATT_POST_SRM2 + RCS_PROP_RATIO_AUG_SRM2 + RCS_PROP_RATIO_ATT_PRE_SRM2);
				RCS1dV = GetdV( SRM1dryMass + RCSmass, RCStotmass * RCS_PROP_RATIO_AUG_SRM1, RCS_ISP_VAC );

				// get SRM 1 burn dV
				RCSmass = RCStotmass * (RCS_PROP_RATIO_RESERVE + RCS_PROP_RATIO_ATT_POST_SRM2 + RCS_PROP_RATIO_AUG_SRM2 + RCS_PROP_RATIO_ATT_PRE_SRM2 + RCS_PROP_RATIO_AUG_SRM1);
				SRM1dV = GetdV( SRM1dryMass + RCSmass, (STAGE1_PROPELLANT_MAXMASS * ld), STAGE1_ISP_VAC );

				if ((SRM1dV + RCS1dV + SRM2dV + RCS2dV) <= dVtgt)
				{
					for (; ld <= IUS_PROP_LOAD_MAX; ld += 0.01)
					{
						// get SRM 2 burn dV
						RCSmass = RCStotmass * (RCS_PROP_RATIO_RESERVE + RCS_PROP_RATIO_ATT_POST_SRM2 + RCS_PROP_RATIO_AUG_SRM2);
						SRM2dV = GetdV( SRM2dryMass + RCSmass, (STAGE2_PROPELLANT_MAXMASS * ld), SRM2Isp );

						// get RCS 1 burn dV
						SRM1dryMass = STAGE1_EMPTYMASS + SRM2dryMass + (STAGE2_PROPELLANT_MAXMASS * ld);
						RCSmass = RCStotmass * (RCS_PROP_RATIO_RESERVE + RCS_PROP_RATIO_ATT_POST_SRM2 + RCS_PROP_RATIO_AUG_SRM2 + RCS_PROP_RATIO_ATT_PRE_SRM2);
						RCS1dV = GetdV( SRM1dryMass + RCSmass, RCStotmass * RCS_PROP_RATIO_AUG_SRM1, RCS_ISP_VAC );

						// get SRM 1 burn dV
						RCSmass = RCStotmass * (RCS_PROP_RATIO_RESERVE + RCS_PROP_RATIO_ATT_POST_SRM2 + RCS_PROP_RATIO_AUG_SRM2 + RCS_PROP_RATIO_ATT_PRE_SRM2 + RCS_PROP_RATIO_AUG_SRM1);
						SRM1dV = GetdV( SRM1dryMass + RCSmass, (STAGE1_PROPELLANT_MAXMASS * ld), STAGE1_ISP_VAC );

						if ((SRM1dV + RCS1dV + SRM2dV + RCS2dV) >= dVtgt)
						{
							res = 0;// ok
							goto lbl_result;
						}
					}

					res = 1;// under-powered
					goto lbl_result;
				}
			}

			res = 2;// over-powered
			goto lbl_result;

lbl_result:
			// output
			ld = Math.Max( Math.Min( ld, IUS_PROP_LOAD_MAX ), IUS_PROP_LOAD_MIN );

			load1 = ld;
			load2 = ld;

			double verror = (SRM1dV + RCS1dV + SRM2dV + RCS2dV) - dVtgt;
			if (res == 1) strresult += "Under perf: " + verror.ToString("0.#") + " m/s\n";
			else if (res == 2) strresult += "Over perf: " + verror.ToString("0.#") + " m/s\n";

			strresult += "SRM-1\n";
			strresult += "  Load: " + ld.ToString("0.##") + "\n";
			strresult += "  deltaV SRM: " + SRM1dV.ToString("0.#") + " m/s\n";
			strresult += "  deltaV RCS: " + RCS1dV.ToString("0.#") + " m/s\n";
			strresult += "  RCS burn time: " + (RCS_PROP_RATIO_AUG_SRM1 * RCS_BURN_TIME * RCStanks).ToString("0.#") + " s\n";

			strresult += "\n";
			strresult += "SRM-2\n";
			strresult += "  Load: " + ld.ToString("0.##") + "\n";
			strresult += "  deltaV SRM: " + SRM2dV.ToString("0.#") + " m/s\n";
			strresult += "  deltaV RCS: " + RCS2dV.ToString("0.#") + " m/s\n";
			strresult += "  RCS burn time: " + (RCS_PROP_RATIO_AUG_SRM2 * RCS_BURN_TIME * RCStanks).ToString("0.#") + " s";
			return;
		}

		/**
		 * Calculate dV needed for a burn to change from a circular orbit to elliptical transfer orbit (e.g. GTO).
		 * @arg curAlt		altitude of initial circular orbit [km]
		 * @arg tgtAlt		altitude of apogee of target orbit [km]
		 * @return		calculated burn delta-V [m/s]
		 **/
		private double GetPeBurndV( double curAlt, double tgtAlt )
		{
			double r1 = (curAlt * 1000) + R;// [m]
			double r2 = (tgtAlt * 1000) + R;// [m]
			return Math.Sqrt( mu / r1 ) * (Math.Sqrt( (2 * r2) / (r1 + r2) ) - 1);
		}

		/**
		 * Calculate dV needed for a burn to circularize an elliptical transfer orbit, and change inclination (e.g. GTO to GEO).
		 * @arg curPe		altitude of perigee of transfer orbit [km]
		 * @arg tgtAlt		altitude of apogee of transfer orbit [km]
		 * @arg dInc		required inclination change during burn [deg]
		 * @return		calculated burn delta-V [m/s]
		 **/
		private double GetApBurndV( double curPe, double tgtAlt, double dInc )
		{
			double r1 = (curPe * 1000) + R;// [m]
			double r2 = (tgtAlt * 1000) + R;// [m]
			double velAp = Math.Sqrt( mu * ((2 / r2) - (1 / ((r1 + r2) / 2))) );// [m/s]
			double velFinal = Math.Sqrt( mu / r2 );// [m/s]
			return Math.Sqrt( Math.Pow( velAp, 2 ) + Math.Pow( velFinal, 2 ) - 2 * velAp * velFinal * Math.Cos( Defs.RAD * Math.Abs( dInc ) ));
		}

		/**
		 * Calculate dV needed for a burn to change from a circular orbit to elliptical transfer orbit, and change inclination (e.g. GTO).
		 * @arg curPe		altitude of perigee of transfer orbit [km]
		 * @arg tgtAlt		altitude of apogee of transfer orbit [km]
		 * @arg dInc		required inclination change during burn [deg]
		 * @return		calculated burn delta-V [m/s]
		 **/
		private double GetPeBurndV( double curPe, double tgtAlt, double dInc )
		{
			double r1 = (curPe * 1000) + R;// [m]
			double r2 = (tgtAlt * 1000) + R;// [m]
			double velPe = Math.Sqrt( mu * ((2 / r1) - (1 / ((r1 + r2) / 2))) );// [m/s]
			double velFinal = Math.Sqrt( mu / r1 );// [m/s]
			return Math.Sqrt( Math.Pow( velPe, 2 ) + Math.Pow( velFinal, 2 ) - 2 * velPe * velFinal * Math.Cos( Defs.RAD * Math.Abs( dInc ) ));
		}

		/**
		 * Calculate dV needed for a burn to achieve a target C3 characteristic energy from a circular orbit.
		 * @arg curAlt		current altitude of circular orbit [km]
		 * @arg C3		target C3 characteristic energy [km^2 / m^2]
		 * @return		calculated burn delta-V [m/s]
		 **/
		private double GetC3BurndV( double curAlt, double C3 )
		{
			double r = (curAlt * 1000) + R;// [m]
			double v = Math.Sqrt( mu / r );// [m/s]
			double vreq_c3 = Math.Sqrt( (C3 * 1000 * 1000) + (2 * mu / r) );// [m/s]
			return vreq_c3 - v;
		}

		/**
		 * Calculate propellant mass needed for a burn to achieve a target dV.
		 * @arg dryMass		dry mass [kg]
		 * @arg Isp		engine specific impulse [s]
		 * @arg dV		burn delta-V [m/s]
		 * @return		calculated propellant mass [kg]
		 **/
		private double GetBurnPropMass( double dryMass, double Isp, double dV )
		{
			return (dryMass * Math.Exp( dV / (g * Isp) )) - dryMass;
		}

		/**
		 * Calculate dV achieved by burning the propellant.
		 * @arg dryMass		dry mass [kg]
		 * @arg propMass	propellant mass [kg]
		 * @arg Isp		engine specific impulse [s]
		 * @return		burn delta-V [m/s]
		 **/
		private double GetdV( double dryMass, double propMass, double Isp )
		{
			return (g * Isp) * Math.Log( (propMass + dryMass) / dryMass );
		}
	}
}

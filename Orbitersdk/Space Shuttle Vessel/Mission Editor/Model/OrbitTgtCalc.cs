using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SSVMissionEditor
{
    class OMSTargetSet
    {
        public double DTIG = 0.0;
        public double HTGT = 0.0;
        public double THETA = 0.0;
        public double C1 = 0.0;
        public double C2 = 0.0;
    }

    class OrbitTgtCalcOptions
    {
        public double H_Insertion; //Height above equator of insertion, nautical miles
        public double H_OMS1;      //Apogee altitude above equator after OMS-1 or MPS dump, nautical miles
        public double H_OMS2;      //Height above equator of OMS-2 target (can be apogee or perigee after OMS-2 burn), nautical miles
        public double Inclination; //Inclination, radians
        public bool InsertionMode; //true = direct, false = standard insertion
    }

    class OrbitTgtCalcOutput
    {
        //MECO
        public double TGTMECOaltitude; //MECO altitude above Orbiter Earth radius, meters
        public double TGTMECOvel; // Velocity for MECO, m/s
        public double TGTMECOfpa; //Flight path angle for MECO, degrees
        public double TGTMECOinclination; //Inclination at MECO, degrees

        //OMS-1 and 2
        public OMSTargetSet oms1, oms2; //PEG-4

        public double TGTMECOap; //MECO apogee altitude, meters
        public double TGTMECOpe; //MECO perigee altitude, meters

        public double[] TGTOMS1tig;// [s]
        public double TGTOMS1dv;// [m/s]
        public double TGTOMS1ap; //OMS-1 or MPS dump apogee altitude, meters
        public double TGTOMS1pe; //OMS-1 or MPS dump perigee altitude, meters

        public double[] TGTOMS2tig;// [s]
        public double TGTOMS2dv;// [m/s]
        public double TGTOMS2ap; //OMS-2 apogee altitude, meters
        public double TGTOMS2pe; //OMS-2 perigee altitude, meters



        public OrbitTgtCalcOutput()
        {
            oms1 = new OMSTargetSet();
            oms2 = new OMSTargetSet();
        }
    }

    class VECTOR3
    {
        public double x, y, z;

        public VECTOR3(double X, double Y, double Z)
        {
            x = X;
            y = Y;
            z = Z;
        }

        public static VECTOR3 operator *(VECTOR3 a, double b)
        {
            return new VECTOR3(a.x * b, a.y * b, a.z * b);
        }

        public static VECTOR3 operator /(VECTOR3 a, double b)
        {
            return new VECTOR3(a.x / b, a.y / b, a.z / b);
        }

        public static VECTOR3 operator +(VECTOR3 a, VECTOR3 b)
        {
            return new VECTOR3(a.x + b.x, a.y + b.y, a.z + b.z);
        }

        public static VECTOR3 operator -(VECTOR3 a, VECTOR3 b)
        {
            return new VECTOR3(a.x - b.x, a.y - b.y, a.z - b.z);
        }

        public static VECTOR3 operator -(VECTOR3 a)
        {
            return new VECTOR3(-a.x, -a.y, -a.z);
        }
    }

    class MATRIX3
    {
        public double m11, m12, m13, m21, m22, m23, m31, m32, m33;

        public MATRIX3()
        {
            m11 = m12 = m13 = m21 = m22 = m23 = m31 = m32 = m33 = 0.0;
        }

        public MATRIX3(double M11, double M12, double M13, double M21, double M22, double M23, double M31, double M32, double M33)
        {
            m11 = M11;
            m12 = M12;
            m13 = M13;
            m21 = M21;
            m22 = M22;
            m23 = M23;
            m31 = M31;
            m32 = M32;
            m33 = M33;
        }
    }

    class OrbitalElements
    {
        public double h = 0.0;
        public double e = 0.0;
        public double i = 0.0;
        public double w = 0.0;
        public double RA = 0.0;
        public double TA = 0.0;
    }

    class StateVector
    {
        public VECTOR3 R;
        public VECTOR3 V;
        public double T;
        public double Mass;
    }

    class OrbitTgtCalc
    {
        public const double RADIUS_EARTH_ORBITER = 6371010.0; //Radius in Orbiter
        public const double RADIUS_EARTH_EQUATOR = 6378166.0; //Real equatorial radius
        public const double MU_EARTH = 398600439968871.19;
        public const double FT = 2.0 * 26700.0; //Thrust of 2 OMS engines in Newton
        public const double VEX = 316.0 * 9.80665; //Specific impulse of OMS engine in m/s

        public OrbitTgtCalc()
        {
          
        }

        VECTOR3 _V(double X, double Y, double Z)
        {
            VECTOR3 a = new VECTOR3(X, Y, Z);
            return a;
        }

        double length(VECTOR3 a)
        {
            return Math.Sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
        }

        VECTOR3 crossp(VECTOR3 a, VECTOR3 b)
        {
	        return _V(a.y* b.z - b.y* a.z, a.z* b.x - b.z* a.x, a.x* b.y - b.x* a.y);
        }

        VECTOR3 unit(VECTOR3 a)
        {
	        return a / length(a);
        }

        double dotp(VECTOR3 a, VECTOR3 b)
        {
	        return a.x* b.x + a.y* b.y + a.z* b.z;
        }

        MATRIX3 _M(double M11, double M12, double M13, double M21, double M22, double M23, double M31, double M32, double M33)
        {
            MATRIX3 a = new MATRIX3(M11, M12, M13, M21, M22, M23, M31, M32, M33);
            return a;
        }

        VECTOR3 mul(MATRIX3 a, VECTOR3 b)
        {
            return _V(a.m11 * b.x + a.m12 * b.y + a.m13 * b.z, a.m21 * b.x + a.m22 * b.y + a.m23 * b.z, a.m31 * b.x + a.m32 * b.y + a.m33 * b.z);
        }

        MATRIX3 mul(MATRIX3 A, MATRIX3 B)
        {
            return _M(A.m11 * B.m11 + A.m12 * B.m21 + A.m13 * B.m31, A.m11 * B.m12 + A.m12 * B.m22 + A.m13 * B.m32, A.m11 * B.m13 + A.m12 * B.m23 + A.m13 * B.m33,
                      A.m21 * B.m11 + A.m22 * B.m21 + A.m23 * B.m31, A.m21 * B.m12 + A.m22 * B.m22 + A.m23 * B.m32, A.m21 * B.m13 + A.m22 * B.m23 + A.m23 * B.m33,
                      A.m31 * B.m11 + A.m32 * B.m21 + A.m33 * B.m31, A.m31 * B.m12 + A.m32 * B.m22 + A.m33 * B.m32, A.m31 * B.m13 + A.m32 * B.m23 + A.m33 * B.m33);
        }

        MATRIX3 Transpose(MATRIX3 A)
        {
            return _M(A.m11, A.m21, A.m31, A.m12, A.m22, A.m32, A.m13, A.m23, A.m33);
        }

        MATRIX3 LVLH_Matrix(VECTOR3 R, VECTOR3 V)
        {
            MATRIX3 M = new MATRIX3();
            VECTOR3 VecTemp;

            VecTemp = unit(crossp(crossp(R, V), R));
            M.m11 = VecTemp.x; M.m12 = VecTemp.y; M.m13 = VecTemp.z;
            VecTemp = -unit(crossp(R, V));
            M.m21 = VecTemp.x; M.m22 = VecTemp.y; M.m23 = VecTemp.z;
            VecTemp = -unit(R);
            M.m31 = VecTemp.x; M.m32 = VecTemp.y; M.m33 = VecTemp.z;

            return M;
        }

        double [] SS2MMSS(double sec)
        {
            return new double[] { Math.Floor(sec / 60.0), sec - Math.Floor(sec / 60.0) * 60.0 };
        }

        VECTOR3 ACCEL(VECTOR3 R, VECTOR3 V)
        {
            //TBD: Nonspherical gravity
            double R_INV = 1.0 / length(R);
            return -R * MU_EARTH * Math.Pow(R_INV, 3);
        }

        StateVector Predictor(StateVector sv, double T_FINAL)
        {
            StateVector sv2 = new StateVector();
            VECTOR3 R_FINAL, V_FINAL, G_PREVIOUS, G_FINAL;
            double T_INIT;

            const double DT_MAX = 2.0;

            R_FINAL = sv.R;
            V_FINAL = sv.V;
            T_INIT = sv.T;

            int NUMBER_STEPS = Math.Max((int)(Math.Round(Math.Abs(T_FINAL - T_INIT) / DT_MAX)), 1);
            double STEP_SIZE = (T_FINAL - T_INIT) / NUMBER_STEPS;

            G_PREVIOUS = ACCEL(R_FINAL, V_FINAL);

            for (int i = 1; i <= NUMBER_STEPS; i++)
            {
                R_FINAL = R_FINAL + (V_FINAL + G_PREVIOUS * 0.5 * STEP_SIZE) * STEP_SIZE;

                G_FINAL = ACCEL(R_FINAL, V_FINAL);

                V_FINAL = V_FINAL + (G_PREVIOUS + G_FINAL) * 0.5 * STEP_SIZE;
                R_FINAL = R_FINAL + (G_FINAL - G_PREVIOUS) / 6.0 * STEP_SIZE * STEP_SIZE;
                G_PREVIOUS = G_FINAL;
            }

            sv2.R = R_FINAL;
            sv2.V = V_FINAL;
            sv2.T = T_FINAL;
            sv2.Mass = sv.Mass;

            return sv2;
        }

        StateVector BurnoutStateVectorPrediction(StateVector sv1, VECTOR3 VGO)
        {
            StateVector sv_p = new StateVector();

            double VGOMAG = length(VGO);
            double ATR = FT / sv1.Mass;

            //Time-to-go
            double VRATIO = VGOMAG / (6.0 * VEX);
            double TGO = VGOMAG / (ATR * (1.0 + 3.0 * VRATIO + 3.0 * VRATIO * VRATIO));

            //Thrust integral
            double S = 0.5 * VGOMAG * TGO * (1.0 - VRATIO);

            //Reference thrust vector
            VECTOR3 LAM = VGO / VGOMAG;

            //Burnout state prediction
            StateVector sv_c1 = new StateVector();
            VECTOR3 RGO = LAM * S;
            sv_c1.R = sv1.R - RGO / 10.0 - VGO * TGO / 30.0;
            sv_c1.V = sv1.V + RGO * 6.0 / 5.0 / TGO - VGO / 10.0;
            sv_c1.T = sv1.T;

            StateVector sv_c2 = Predictor(sv_c1, sv_c1.T + TGO);

            VECTOR3 VGRAV = sv_c2.V - sv_c1.V;
            VECTOR3 RGRAV = sv_c2.R - sv_c1.R - sv_c1.V * TGO;
            VECTOR3 RP = sv1.R + sv1.V * TGO + RGRAV + RGO;
            VECTOR3 VP = sv1.V + VGRAV + VGO;

            sv_p.R = RP;
            sv_p.V = VP;
            sv_p.T = sv1.T + TGO;
            sv_p.Mass = sv1.Mass - TGO * FT / VEX;

            return sv_p;
        }

        StateVector sv_from_coe(OrbitalElements coe, double mu)
        {
            VECTOR3 rp = _V(Math.Cos(coe.TA), Math.Sin(coe.TA), 0) * coe.h * coe.h / mu * (1.0 / (1.0 + coe.e * Math.Cos(coe.TA)));
            VECTOR3 vp = _V(-Math.Sin(coe.TA), coe.e + Math.Cos(coe.TA), 0) * mu / coe.h;

            MATRIX3 R3_W = _M(Math.Cos(coe.RA), Math.Sin(coe.RA), 0, -Math.Sin(coe.RA), Math.Cos(coe.RA), 0, 0, 0, 1);
            MATRIX3 R1_i = _M(1, 0, 0, 0, Math.Cos(coe.i), Math.Sin(coe.i), 0, -Math.Sin(coe.i), Math.Cos(coe.i));
            MATRIX3 R3_w = _M(Math.Cos(coe.w), Math.Sin(coe.w), 0, -Math.Sin(coe.w), Math.Cos(coe.w), 0, 0, 0, 1);

            MATRIX3 Q_pX = Transpose(mul(R3_w, mul(R1_i, R3_W)));

            VECTOR3 r = mul(Q_pX, rp);
            VECTOR3 v = mul(Q_pX, vp);


            StateVector sv2 = new StateVector();

            sv2.R = r;
            sv2.V = v;
            sv2.T = 0.0;

            return sv2;
        }

        double ecc(double ApR, double PeR)
        {
            return (ApR - PeR) / (ApR + PeR);
        }

        double SMa(double ApR, double PeR)
        {
            return (ApR + PeR) / 2.0;
        }

        double FPA(double e, double Theta)
        {
            return Math.Atan(e * Math.Sin(Theta) / (1.0 + e * Math.Cos(Theta)));
        }

        double OrbitParameter(double e, double a)
        {
            return a * (1.0 - e * e);
        }

        double TrueAnomalyFromOrbit(double p, double r, double e, double mu)
        {
            return Math.Acos((p / r - 1.0) / e);
        }

        private double VisViva(double fRadius, double fApR, double fPeR)
        {
            return Math.Sqrt(MU_EARTH * ((2.0 / fRadius) - (2.0 / (fApR + fPeR))));
        }

        double ArgumentOfLatitude(VECTOR3 R, VECTOR3 V)
        {
            VECTOR3 H = crossp(R, V);
            VECTOR3 K = _V(0, 0, 1);
            VECTOR3 N = crossp(K, H);
            double u = Math.Acos(dotp(unit(N), unit(R)));
            if (R.z < 0)
            {
                u = Math.PI * 2.0 - u;
            }
            return u;
        }

        StateVector FindApogee(StateVector sv1)
        {
            VECTOR3 E, H;
            double n, dt, theta, dtheta;
            int i, imax;

            n = Defs.PI * 2.0 / (90 * 60);
            i = 0;
            imax = 10;

            StateVector sv2 = sv1;

            dt = 1000;

            while (Math.Abs(dt) > 0.1 && i < imax)
            {
                H = crossp(sv2.R, sv2.V);
                E = crossp(sv2.V, H) / MU_EARTH - unit(sv2.R);
                theta = Math.Acos(dotp(unit(E), unit(sv2.R)));
                if (dotp(sv2.R, sv2.V) < 0)
                {
                    theta = Math.PI * 2.0 - theta;
                }
                dtheta = Math.PI - theta;
                dt = dtheta / n;
                sv2 = Predictor(sv2, sv2.T + dt);
                i++;
            }
            return sv2;
        }

        StateVector FindArgumentOfLatitude(StateVector sv0)
        {
            StateVector sv1 = new StateVector();
            double du;

            //Initial argument of latitude
            double u0 = ArgumentOfLatitude(sv0.R, sv0.V);
            //Desired argument of latitude
            double u1 = u0 + Math.PI;
            //Initial guess for dt
            double dt = 45.0 * 60.0;
            //
            double n = 2.0 * Math.PI / (90.0 * 60.0);

            sv1 = sv0;

            do
            {
                sv1 = Predictor(sv1, sv1.T + dt);
                u0 = ArgumentOfLatitude(sv1.R, sv1.V);

                du = u1 - u0;
                if (du > Math.PI)
                {
                    du -= 2.0 * Math.PI;
                }
                else if (du < -Math.PI)
                {
                    du += 2.0 * Math.PI;
                }
                dt = du / n;
            } while (Math.Abs(dt) > 0.1);

            return sv1;
        }

        VECTOR3 GetOptimumBurnVector(VECTOR3 R, VECTOR3 V, double M, double FT, VECTOR3 DV_LV)
        {
            double dv = length(DV_LV);

            if (dv == 0.0)
            {
                return _V(0, 0, 0);
            }

            VECTOR3 X = unit(crossp(crossp(R, V), R));
            VECTOR3 Y = unit(crossp(V, R));
            VECTOR3 Z = -unit(R);

            VECTOR3 DV_P = X * DV_LV.x + Z * DV_LV.z;
            double theta_T = length(crossp(R, V)) * Math.Abs(dv) * M / (Math.Pow(length(R), 2) * FT);
            VECTOR3 DV_C = (unit(DV_P) * Math.Cos(theta_T / 2.0) + unit(crossp(DV_P, Y)) * Math.Sin(theta_T / 2)) * length(DV_P);
            VECTOR3 DV = DV_C + Y*DV_LV.y;

            return DV;
        }

        double[] PIFAAP(double a, double e, double i, double f, double u, double r, double R_E)
        {
            double J, a_ref, e_ref, p_ref, p, K1, K2, df, r_1, r_2, r_A, r_P;

            J = 0;// 1623.45e-6;

            a_ref = r + J * R_E * (1.0 - 3.0 / 2.0 * Math.Pow(Math.Sin(i), 2) + 5.0 / 6.0 * Math.Pow(Math.Sin(i), 2) * Math.Cos(2.0 * u));
            e_ref = 1.0 - r / a_ref;
            p_ref = a_ref * (1.0 - e_ref * e_ref);
            p = a * (1.0 - e * e);
            K1 = e / Math.Sqrt(p);
            K2 = e_ref / Math.Sqrt(p_ref);
            df = Math.Atan2(K1 * Math.Sin(f), K2 - K1 * Math.Cos(f));
            r_1 = p / (1.0 + e * Math.Cos(f + df)) - p_ref / (1.0 + e_ref * Math.Cos(df)) + r;
            r_2 = p / (1.0 - e * Math.Cos(f + df)) - p_ref / (1.0 - e_ref * Math.Cos(df)) + r;
            if (r_1 >= r_2)
            {
                r_A = r_1;
                r_P = r_2;
            }
            else
            {
                r_A = r_2;
                r_P = r_1;
            }

            return new double[2] { r_A, r_P };
        }

        double[] ApsidesMagnitudeDetermination(StateVector sv0)
        {
            VECTOR3 H, E;
            double eps, r, a, u, e, i, TA;

            r = length(sv0.R);
            eps = Math.Pow(length(sv0.V), 2) / 2.0 - MU_EARTH / r;
            a = -MU_EARTH / (2.0 * eps);
            H = crossp(sv0.R, sv0.V);
            E = crossp(sv0.V, H) / MU_EARTH - sv0.R / r;
            e = length(E);
            i = Math.Acos(H.z / length(H));
            TA = Math.Acos(dotp(unit(E), unit(sv0.R)));
            if (dotp(sv0.R,sv0.V)<0)
            {
                TA = Math.PI * 2.0 - TA;
            }

            u = ArgumentOfLatitude(sv0.R, sv0.V);

            return PIFAAP(a, e, i, TA, u, r, RADIUS_EARTH_ORBITER);
        }

        double MECOTargetLineDI285(double v_Ins)
        {
            if (v_Ins < 25970)
            {
                return -73.15 + 0.00285714 * v_Ins;
            }
            else if (v_Ins < 26020)
            {
                return -32.3923 + 0.00128773 * v_Ins;
            }
            else
            {
                return -75.4756 + 0.00294353 * v_Ins;
            }
        }

        double MECOTargetLineDI516(double v_Ins)
        {
            return 0.6;
        }

        double MECOTargetLineDI57(double v_Ins)
        {
            if (v_Ins < 25900)
            {
                return (1.45 - 0.65) / (25880 - 25725) * (v_Ins - 25725) + 0.65;
            }
            return (1.59 - 0.88) / (26160 - 25945) * (v_Ins - 25945) + 0.88;
        }

        public OrbitTgtCalcOutput Calculate(OrbitTgtCalcOptions opt)
        {
            //Input: H insertion, H OMS-1, H OMS-2, insertion mode
            //Output is: Inclination, velocity, PEG-4 for OMS-1 and 2

            OrbitTgtCalcOutput solution = new OrbitTgtCalcOutput();
            OrbitalElements coe = new OrbitalElements();
            StateVector sv_MECO = new StateVector(); //State vector at MECO
            StateVector sv_OMS1 = new StateVector(); //State vector at OMS-1 ignition/MPS dump start
            StateVector sv_OMS1_post = new StateVector(); //State vector at OMS-1 burnout/MPS dump completed
            StateVector sv_apo = new StateVector(); //State vector at apogee following OMS-1/MPS dump
            VECTOR3 DV;
            double fpa = 0.0;
            double Theta = 0.0;
            double e = 0.0;
            double p = 0.0;
            double h = 0.0;
            double V_MECO, dv_OMS1, dr;

            const double PFT = 8.0*60.0 + 39.0; //Powered flight time from launch to MECO
            const double PFA = 14.4 * Defs.RAD; //Powered flight arc from launch to MECO
            const double DT_ET_SEP = 18.0; //MECO to ET sep
            const double DTIG_OMS1 = 120.0; //MECO to OMS-1
            const double M0 = 250000.0 * 0.453; //Orbiter weight before MPS dump
            const double DV_SLOPE = 3413.5; //Rule of thumb, 1 ft/s of DV raises orbit by 1 NM

            double r_Insertion = opt.H_Insertion + RADIUS_EARTH_EQUATOR;
            double r_OMS1_T = opt.H_OMS1 + RADIUS_EARTH_EQUATOR;
            double r_OMS2_T = opt.H_OMS2 + RADIUS_EARTH_EQUATOR;

            //Initial calculations
            if (opt.InsertionMode == true)
            {
                //Initial guess
                V_MECO = 25800.0 / Defs.MPS2FPS;

                //MPS dump
                dv_OMS1 = 1.0;
            }
            else
            {
                //Insertion orbit
                double fApogeeMECOOrbit = ((85 * Defs.NM2KM) * 1000.0) + RADIUS_EARTH_EQUATOR;
                double fPerigeeMECOOrbit = ((3 * Defs.NM2KM) * 1000.0) + RADIUS_EARTH_EQUATOR;

                e = ecc(fApogeeMECOOrbit, fPerigeeMECOOrbit);
                double a = SMa(fApogeeMECOOrbit, fPerigeeMECOOrbit);
                p = OrbitParameter(e, a);
                h = Math.Sqrt(p * MU_EARTH);
                Theta = TrueAnomalyFromOrbit(p, r_Insertion, e, MU_EARTH);
                fpa = FPA(e, Theta);
                V_MECO = VisViva(r_Insertion, fApogeeMECOOrbit, fPerigeeMECOOrbit);

                //Initial guess
                dv_OMS1 = 30.0;
            }

            //Iterate on apogee height

            int i, imax;

            i = 0;
            imax = 10;

            do
            {
                if (opt.InsertionMode == true)
                {
                    if (opt.Inclination < 50.0 * Defs.RAD)
                    {
                        fpa = MECOTargetLineDI285(V_MECO * Defs.MPS2FPS) * Defs.RAD;
                    }
                    else if (opt.Inclination < 54.0 * Defs.RAD)
                    {
                        fpa = MECOTargetLineDI516(V_MECO * Defs.MPS2FPS) * Defs.RAD;
                    }
                    else
                    {
                        fpa = MECOTargetLineDI57(V_MECO * Defs.MPS2FPS) * Defs.RAD;
                    }

                    double V_tangential = V_MECO * Math.Cos(fpa);
                    double V_radial = V_MECO * Math.Sin(fpa);
                    h = V_tangential * r_Insertion;
                    p = h * h / MU_EARTH;
                    double e_cos_theta = p / r_Insertion - 1.0;
                    double e_sin_theta = V_radial * h / MU_EARTH;
                    e = Math.Sqrt(e_cos_theta * e_cos_theta + e_sin_theta * e_sin_theta);
                    Theta = TrueAnomalyFromOrbit(p, r_Insertion, e, MU_EARTH);
                }

                //Build MECO state vector. TBD: Put launch function in here

                coe.h = h;
                coe.e = e;
                coe.i = opt.Inclination;
                coe.w = 0.0; //TBD
                coe.RA = 0.0; //TBD
                coe.TA = Theta;

                sv_MECO = sv_from_coe(coe, MU_EARTH);
                sv_MECO.T = PFT;
                sv_MECO.Mass = M0;

                //Propagate state vector to OMS-1 or MPS dump
                sv_OMS1 = Predictor(sv_MECO, sv_MECO.T + DTIG_OMS1);

                if (opt.InsertionMode == true)
                {
                    //MPS Dump
                    sv_OMS1_post = sv_OMS1;
                    sv_OMS1_post.V = sv_OMS1_post.V + mul(LVLH_Matrix(sv_OMS1_post.R, sv_OMS1_post.V), _V(dv_OMS1, 0, 0));
                }
                else
                {
                    //Target OMS-1
                    DV = GetOptimumBurnVector(sv_OMS1.R, sv_OMS1.V, sv_OMS1.Mass, FT, _V(dv_OMS1, 0, 0));
                    sv_OMS1_post = BurnoutStateVectorPrediction(sv_OMS1, DV);
                }

                //Propagate state vector to apogee
                sv_apo = FindApogee(sv_OMS1_post);

                //Apogee radius error
                dr = r_OMS1_T - length(sv_apo.R);

                //Calculate velocity correction
                if (opt.InsertionMode == true)
                {
                    V_MECO = V_MECO + dr / DV_SLOPE;
                }
                else
                {
                    dv_OMS1 = dv_OMS1 + dr / DV_SLOPE;
                }
                i++;
            } while (Math.Abs(dr) > 1.0 && i < imax);

            //TBD: Error return?

            //OMS-2 iteration
            StateVector sv_OMS2 = new StateVector();
            StateVector sv_OMS2_post = new StateVector();
            StateVector sv_peri = new StateVector();
            double dv_OMS2 = 10.0;
            double dt;

            i = 0;
            do
            {
                //Estimate OMS-2 TIG
                dt = sv_apo.Mass * dv_OMS2 / FT;
                sv_OMS2 = Predictor(sv_apo, sv_apo.T - dt / 2.0);

                //Burn
                DV = GetOptimumBurnVector(sv_OMS2.R, sv_OMS2.V, sv_OMS2.Mass, FT, _V(dv_OMS2, 0, 0));
                sv_OMS2_post = BurnoutStateVectorPrediction(sv_OMS2, DV);

                //Predict state vector at 180° away from current position
                sv_peri = FindArgumentOfLatitude(sv_OMS2_post);

                //Error in radius
                dr = r_OMS2_T - length(sv_peri.R);

                //Correct OMS-2 DV
                dv_OMS2 = dv_OMS2 + dr / DV_SLOPE;

                i++;
            } while (Math.Abs(dr) > 1.0 && i < imax);

            //TBD: Error return?

            //Build OMS-1 target
            double DTHETA_OMS1 = Math.Acos(dotp(unit(sv_MECO.R), unit(sv_apo.R)));
            double THETA_OMS1 = PFA + DTHETA_OMS1;

            solution.oms1.DTIG = DTIG_OMS1 - DT_ET_SEP;
            solution.oms1.C1 = 0.0;
            solution.oms1.C2 = 0.0;
            solution.oms1.THETA = Math.Round(THETA_OMS1 * Defs.DEG) * Defs.RAD; //Round to next degree
            solution.oms1.HTGT = opt.H_OMS1;

            //Build OMS-2 target
            solution.oms2.DTIG = sv_OMS2.T - (sv_MECO.T + DT_ET_SEP);
            solution.oms2.C1 = 0.0;
            solution.oms2.C2 = 0.0;
            solution.oms2.THETA = solution.oms1.THETA + Defs.PI;
            solution.oms2.HTGT = opt.H_OMS2;

            //Additional outputs
            double[] apsides = ApsidesMagnitudeDetermination(sv_MECO);

            solution.TGTMECOaltitude = r_Insertion - RADIUS_EARTH_ORBITER;
            solution.TGTMECOvel = V_MECO;
            solution.TGTMECOfpa = fpa * Defs.DEG;
            solution.TGTMECOinclination = opt.Inclination * Defs.DEG;
            solution.TGTMECOap = apsides[0] - RADIUS_EARTH_EQUATOR;
            solution.TGTMECOpe = apsides[1] - RADIUS_EARTH_EQUATOR;

            solution.TGTOMS1tig = SS2MMSS(sv_OMS1.T);
            solution.TGTOMS1dv = dv_OMS1;
            apsides = ApsidesMagnitudeDetermination(sv_OMS1_post);
            solution.TGTOMS1ap = apsides[0] - RADIUS_EARTH_EQUATOR;
            solution.TGTOMS1pe = apsides[1] - RADIUS_EARTH_EQUATOR;

            solution.TGTOMS2tig = SS2MMSS(sv_OMS2.T);
            solution.TGTOMS2dv = dv_OMS2;
            apsides = ApsidesMagnitudeDetermination(sv_OMS2_post);
            solution.TGTOMS2ap = apsides[0] - RADIUS_EARTH_EQUATOR;
            solution.TGTOMS2pe = apsides[1] - RADIUS_EARTH_EQUATOR;


            return solution;
        }
    }
}

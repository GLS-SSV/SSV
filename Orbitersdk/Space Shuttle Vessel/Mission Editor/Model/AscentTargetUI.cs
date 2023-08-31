/****************************************************************************
  This file is part of Space Shuttle Vessel Mission Editor
  
  Space Shuttle Vessel is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
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

using System.ComponentModel;


namespace SSVMissionEditor.model
{
	public class AscentTargetUI : INotifyPropertyChanged
	{
		public static int[] MECO_ALTITUDE_LIST { get; } = { 60, 57, 52 };

		public AscentTargetUI( Mission mission )
		{
			this.mission = mission;

			orbittgtcalc = new OrbitTgtCalc();

			// lead default ascent target values
			DI = true;
			MECOInclination = 51.6;
			MECOAltitude = 52;
			OMS1MECOTargetAltitude = 160.0;
			OMS2TargetAltitude = 160.0;
			RTHU = true;
			return;
		}

		public void Calc()
		{
			ResultString = "calculating...";

			OrbitTgtCalcOptions opt = new OrbitTgtCalcOptions
			{
				H_Insertion = MECOAltitude * Defs.NM2KM * 1000.0,
				H_OMS1 = OMS1MECOTargetAltitude * Defs.NM2KM * 1000.0,
				H_OMS2 = OMS2TargetAltitude * Defs.NM2KM * 1000.0,
				Inclination = MECOInclination * Defs.RAD,
				InsertionMode = DI
			};

			OrbitTgtCalcOutput res = orbittgtcalc.Calculate( opt );

			MECOAltitude2 = res.TGTMECOaltitude;
			MECOVelocity = res.TGTMECOvel * Defs.MPS2FPS;
			MECOFPA = res.TGTMECOfpa;
			//MECOInclination = res.TGTMECOinclination;

			OMS1DTIG = res.oms1.DTIG;
			OMS1HTGT = res.oms1.HTGT * Defs.MPS2FPS;
			OMS1THETA = res.oms1.THETA;
			OMS1C1 = res.oms1.C1 * Defs.MPS2FPS;
			OMS1C2 = res.oms1.C2;

			OMS2DTIG = res.oms2.DTIG;
			OMS2HTGT = res.oms2.HTGT * Defs.MPS2FPS;
			OMS2THETA = res.oms2.THETA;
			OMS2C1 = res.oms2.C1 * Defs.MPS2FPS;
			OMS2C2 = res.oms2.C2;



			ResultString = string.Format(">> MECO <<\n" +
				"Inclination: {0:f2}º\n" +
				"Altitude: {1:f0}ft ({2:f0}km)\n" +
				"Velocity: {3:f0}fps ({4:f0}m/s)\n" +
				"Flight Path Angle: {5:f4}º\n" +
				"Ap/Pe: {6:f0}x{7:f0}NM ({8:f0}x{9:f0}Km)\n",
				MECOInclination,
				res.TGTMECOaltitude * Defs.MPS2FPS, res.TGTMECOaltitude * 0.001,
				res.TGTMECOvel * Defs.MPS2FPS, res.TGTMECOvel,
				res.TGTMECOfpa,
				res.TGTMECOap / (Defs.NM2KM * 1000.0), res.TGTMECOpe / (Defs.NM2KM * 1000.0), res.TGTMECOap * 0.001, res.TGTMECOpe * 0.001 );

			if (!DI)
			{
				// SI
				ResultString += string.Format("\n>> OMS-1 <<\n" +
					"TIG: {0:D2}:{1:D2}\n" +
					"dV: {2:f1}fps ({3:f1}m/s)\n" +
					"Ap/Pe: {4:f0}x{5:f0}NM ({6:f0}x{7:f0}Km)\n",
					(int)res.TGTOMS1tig[0], (int)res.TGTOMS1tig[1],
					res.TGTOMS1dv * Defs.MPS2FPS, res.TGTOMS1dv,
					res.TGTOMS1ap / (Defs.NM2KM * 1000.0), res.TGTOMS1pe / (Defs.NM2KM * 1000.0), res.TGTOMS1ap * 0.001, res.TGTOMS1pe * 0.001 );
			}
			else
			{
				// DI
				ResultString += string.Format("\n>> OMS-1 <<\n(not performed)\n" +
					"Ap/Pe: {0:f0}x{1:f0}NM ({2:f0}x{3:f0}Km)\n",
					res.TGTOMS1ap / (Defs.NM2KM * 1000.0), res.TGTOMS1pe / (Defs.NM2KM * 1000.0), res.TGTOMS1ap * 0.001, res.TGTOMS1pe * 0.001 );
			}

			ResultString += string.Format("\n>> OMS-2 <<\n" +
				"TIG: {0:D2}:{1:D2}\n" +
				"dV: {2:f1}fps ({3:f1}m/s)\n" +
				"Ap/Pe: {4:f0}x{5:f0}NM ({6:f0}x{7:f0}Km)\n",
				(int)res.TGTOMS2tig[0], (int)res.TGTOMS2tig[1],
				res.TGTOMS2dv * Defs.MPS2FPS, res.TGTOMS2dv,
				res.TGTOMS2ap / (Defs.NM2KM * 1000.0), res.TGTOMS2pe / (Defs.NM2KM * 1000.0), res.TGTOMS2ap * 0.001, res.TGTOMS2pe * 0.001 );
			return;
		}

		public void Save()
		{
			// save legacy MECO target
			mission.SetMECOparams( MECOInclination, MECOAltitude2, MECOVelocity / Defs.MPS2FPS, MECOFPA );

			// set I-LOADs for roll to heads up and OMS-1/2 targets
			for (int i = 0; i < mission.OV.ILOAD_List.Count; i++)
			{
				if (mission.OV.ILOAD_List[i].ID == "PHI_2STG")
				{
					mission.OV.ILOAD_List[i].Val = RTHU ? "0.0" : "3.141593";
				}
				else if (mission.OV.ILOAD_List[i].ID == "TVR_ROLL")
				{
					mission.OV.ILOAD_List[i].Val = RTHU ? "0" : "180";
				}
				else if (mission.OV.ILOAD_List[i].ID == "DTIG_OMS")
				{
					mission.OV.ILOAD_List[i].Val = string.Format("{0:f1} {1:f1}", OMS1DTIG, OMS2DTIG );
				}
				else if (mission.OV.ILOAD_List[i].ID == "HTGT_OMS")
				{
					mission.OV.ILOAD_List[i].Val = string.Format("{0:f1} {1:f1}", OMS1HTGT, OMS2HTGT );
				}
				else if (mission.OV.ILOAD_List[i].ID == "THETA_OMS")
				{
					mission.OV.ILOAD_List[i].Val = string.Format("{0:f6} {1:f6}", OMS1THETA, OMS2THETA );
				}
				else if (mission.OV.ILOAD_List[i].ID == "C1_OMS")
				{
					mission.OV.ILOAD_List[i].Val = string.Format("{0:f0} {1:f0}", OMS1C1, OMS2C1 );
				}
				else if (mission.OV.ILOAD_List[i].ID == "C2_OMS")
				{
					mission.OV.ILOAD_List[i].Val = string.Format("{0:f4} {1:f4}", OMS1C2, OMS2C2 );
				}
			}
			return;
		}


		private OrbitTgtCalc orbittgtcalc;
		private Mission mission;

		/// <summary>
		/// Direct Insertion if true, Standard Insertion if false
		/// </summary>
		private bool di;
		public bool DI
		{
			get { return di; }
			set
			{
				di = value;
				OnPropertyChanged( "DI" );
			}
		}

		/// <summary>
		/// MECO inclination [deg]
		/// </summary>
		private double mecoinclination;
		public double MECOInclination
		{
			get { return mecoinclination; }
			set
			{
				mecoinclination = value;
				OnPropertyChanged( "MECOInclination" );
			}
		}

		/// <summary>
		/// MECO altitude, referenced to STS Earth [NM]
		/// </summary>
		private int mecoaltitude;
		public int MECOAltitude
		{
			get { return mecoaltitude; }
			set
			{
				mecoaltitude = value;
				OnPropertyChanged( "MECOAltitude" );
			}
		}

		/// <summary>
		/// OMS-1 (SI) / MECO (DI) target altitude [NM]
		/// </summary>
		private double oms1mecotargetaltitude;
		public double OMS1MECOTargetAltitude
		{
			get { return oms1mecotargetaltitude; }
			set
			{
				oms1mecotargetaltitude = value;
				OnPropertyChanged( "OMS1MECOTargetAltitude" );
			}
		}

		/// <summary>
		/// OMS-2 target altitude [NM]
		/// </summary>
		private double oms2targetaltitude;
		public double OMS2TargetAltitude
		{
			get { return oms2targetaltitude; }
			set
			{
				oms2targetaltitude = value;
				OnPropertyChanged( "OMS2TargetAltitude" );
			}
		}

		/// <summary>
		/// If true, roll to heads up is performed.
		/// </summary>
		private bool rthu;
		public bool RTHU
		{
			get { return rthu; }
			set
			{
				rthu = value;
				OnPropertyChanged( "RTHU" );
			}
		}



		/// <summary>
		/// Formatted string containg several calculated parameters.
		/// </summary>
		private string resultstring;
		public string ResultString
		{
			get { return resultstring; }
			set
			{
				resultstring = value;
				OnPropertyChanged( "ResultString" );
			}
		}

		/// <summary>
		/// MECO altitude, referenced to Orbiter Earth [m]
		/// </summary>
		private double mecoaltitude2;
		public double MECOAltitude2
		{
			get { return mecoaltitude2; }
			set
			{
				mecoaltitude2 = value;
				OnPropertyChanged( "MECOAltitude2" );
			}
		}

		/// <summary>
		/// MECO velocity [fps]
		/// </summary>
		private double mecovelocity;
		public double MECOVelocity
		{
			get { return mecovelocity; }
			set
			{
				mecovelocity = value;
				OnPropertyChanged( "MECOVelocity" );
			}
		}

		/// <summary>
		/// MECO FPA [deg]
		/// </summary>
		private double mecofpa;
		public double MECOFPA
		{
			get { return mecofpa; }
			set
			{
				mecofpa = value;
				OnPropertyChanged( "MECOFPA" );
			}
		}

		/// <summary>
		/// Time between ET separation and OMS-1 [s]
		/// </summary>
		private double oms1dtig;
		public double OMS1DTIG
		{
			get { return oms1dtig; }
			set
			{
				oms1dtig = value;
				OnPropertyChanged( "OMS1DTIG" );
			}
		}

		/// <summary>
		/// OMS-1 PEG-4 HTGT [ft]
		/// </summary>
		private double oms1htgt;
		public double OMS1HTGT
		{
			get { return oms1htgt; }
			set
			{
				oms1htgt = value;
				OnPropertyChanged( "OMS1HTGT" );
			}
		}

		/// <summary>
		/// OMS-1 PEG-4 Theta [rad]
		/// </summary>
		private double oms1theta;
		public double OMS1THETA
		{
			get { return oms1theta; }
			set
			{
				oms1theta = value;
				OnPropertyChanged( "OMS1THETA" );
			}
		}

		/// <summary>
		/// OMS-1 PEG-4 C1 [fps]
		/// </summary>
		private double oms1c1;
		public double OMS1C1
		{
			get { return oms1c1; }
			set
			{
				oms1c1 = value;
				OnPropertyChanged( "OMS1C1" );
			}
		}

		/// <summary>
		/// OMS-1 PEG-4 C2 [1]
		/// </summary>
		private double oms1c2;
		public double OMS1C2
		{
			get { return oms1c1; }
			set
			{
				oms1c2 = value;
				OnPropertyChanged( "OMS1C2" );
			}
		}

		/// <summary>
		/// Time between ET separation and OMS-2 [s]
		/// </summary>
		private double oms2dtig;
		public double OMS2DTIG
		{
			get { return oms2dtig; }
			set
			{
				oms2dtig = value;
				OnPropertyChanged( "OMS2DTIG" );
			}
		}

		/// <summary>
		/// OMS-2 PEG-4 HTGT [ft]
		/// </summary>
		private double oms2htgt;
		public double OMS2HTGT
		{
			get { return oms2htgt; }
			set
			{
				oms2htgt = value;
				OnPropertyChanged( "OMS2HTGT" );
			}
		}

		/// <summary>
		/// OMS-2 PEG-4 Theta [rad]
		/// </summary>
		private double oms2theta;
		public double OMS2THETA
		{
			get { return oms2theta; }
			set
			{
				oms2theta = value;
				OnPropertyChanged( "OMS2THETA" );
			}
		}

		/// <summary>
		/// OMS-2 PEG-4 C1 [fps]
		/// </summary>
		private double oms2c1;
		public double OMS2C1
		{
			get { return oms2c1; }
			set
			{
				oms2c1 = value;
				OnPropertyChanged( "OMS2C1" );
			}
		}

		/// <summary>
		/// OMS-2 PEG-4 C2 [1]
		/// </summary>
		private double oms2c2;
		public double OMS2C2
		{
			get { return oms2c1; }
			set
			{
				oms2c2 = value;
				OnPropertyChanged( "OMS2C2" );
			}
		}



		public event PropertyChangedEventHandler PropertyChanged;
		private void OnPropertyChanged( string prop )
		{
			PropertyChanged?.Invoke( this, new PropertyChangedEventArgs( prop ) );
		}
	}
}

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
/******* SSV File Modification Notice *******
Date         Developer
2020/05/31   GLS
2020/06/28   GLS
2020/07/01   GLS
2021/12/25   GLS
2022/06/24   GLS
2023/03/30   GLS
2023/04/04   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra Workbench

  Space Shuttle Ultra is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Ultra is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Ultra; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file Doc\Space Shuttle Ultra\GPL.txt for more details.

  **************************************************************************/

using System.Windows.Controls;


namespace SSVMissionEditor
{
	/// <summary>
	/// Interaction logic for Launch.xaml
	/// </summary>
	public partial class Launch : UserControl
	{
		private readonly double[] MECO_ALT = {63, 57, 52};// [NM]

		public Launch()
		{
			InitializeComponent();
		}

		private void LaunchSite_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			if (LaunchSite.SelectedIndex == 0)
			{
				// KSC
				LaunchPad.IsEnabled = true;
				LaunchPad.Items.Clear();
				LaunchPad.Items.Add( "LC-39A" );
				LaunchPad.Items.Add( "LC-39B" );
				LaunchPad.SelectedIndex = 0;

				LaunchPadType.IsEnabled = true;
				LaunchPadType.Items.Clear();
				LaunchPadType.Items.Add( "1981" );
				LaunchPadType.Items.Add( "1982" );
				LaunchPadType.Items.Add( "1983" );
				LaunchPadType.Items.Add( "1985" );
				LaunchPadType.Items.Add( "1986" );
				LaunchPadType.Items.Add( "1988" );
				LaunchPadType.Items.Add( "1995" );
				LaunchPadType.Items.Add( "2007" );
				LaunchPadType.SelectedIndex = 0;

				MLP.IsEnabled = true;
				MLP.Items.Clear();
				MLP.Items.Add( "MLP-1" );
				MLP.Items.Add( "MLP-2" );
				MLP.Items.Add( "MLP-3" );
				MLP.SelectedIndex = 0;
			}
			else
			{
				// VAFB
				LaunchPad.IsEnabled = false;
				LaunchPad.Items.Clear();
				LaunchPad.Items.Add( "SLC-6" );
				LaunchPad.SelectedIndex = 0;

				LaunchPadType.IsEnabled = false;
				LaunchPadType.Items.Clear();

				MLP.IsEnabled = false;
				MLP.Items.Clear();
			}

			cmbTGTMECOAlt.Items.Clear();
			foreach (double x in MECO_ALT) cmbTGTMECOAlt.Items.Add( x );

			// show default ascent target values
			txtTGTAlt.Text = "160.0";
			txtTGTInc.Text = "51.6";
			cmbTGTMECOAlt.SelectedIndex = 2;// 52NM
			cmbTGTInsertionMode.SelectedIndex = 1;// DI
			chkTGTRTHU.IsChecked = true;
			return;
		}

		private void TxtTGTAlt_TextChanged(object sender, TextChangedEventArgs e)
		{
			// display MECO alt in Km
			double.TryParse( txtTGTAlt.Text, out double input );
			txtTGTAltKm.Text = string.Format("{0:f1}", input * Defs.NM2KM );
			return;
		}

		private void BtnCalc_Click(object sender, System.Windows.RoutedEventArgs e)
		{
			double.TryParse( txtTGTAlt.Text, out double TGTORBalt );// [m]
			TGTORBalt *= Defs.NM2KM * 1000.0;

			double.TryParse( txtTGTInc.Text, out double TGTMECOinclination );// [deg]
			
			double MECOalt = MECO_ALT[cmbTGTMECOAlt.SelectedIndex]* Defs.NM2KM * 1000.0;// [m]

			bool DI = cmbTGTInsertionMode.SelectedIndex == 1;

			// TODO run MECO and OMS-1/2 logic

			// TODO get data
			double TGTMECOaltitude = 105000.0;// [m]
			double TGTMECOvel = 7892.4;// [m/s]
			double TGTMECOfpa = 0.8731;// [deg]
			double TGTMECOap = 250000.0;// [m]
			double TGTMECOpe = 49600.0;// [m]

			double TGTOMS1tig = 102.0;// [s]
			double TGTOMS1dv = 37.9;// [m/s]
			double TGTOMS1ap = 255000.0;// [m]
			double TGTOMS1pe = 96100.0;// [m]

			double TGTOMS2tig = 1740.0;// [s]
			double TGTOMS2dv = 89.4;// [m/s]
			double TGTOMS2ap = 255000.0;// [m]
			double TGTOMS2pe = 255000.0;// [m]

			// display results
			string outstr = "";
			outstr = string.Format(">> MECO <<\n" +
				"Inclination: {0:f2}º\n" +
				"Altitude: {1:f0}ft ({2:f0}km)\n" +
				"Velocity: {3:f0}fps ({4:f0}m/s)\n" +
				"Flight Path Angle: {5:f4}º\n" +
				"Ap/Pe: {6:f0}x{7:f0}NM ({8:f0}x{9:f0}Km)\n",
				TGTMECOinclination,
				TGTMECOaltitude * Defs.MPS2FPS, TGTMECOaltitude * 0.001,
				TGTMECOvel * Defs.MPS2FPS, TGTMECOvel,
				TGTMECOfpa,
				TGTMECOap / (Defs.NM2KM * 1000.0), TGTMECOpe / (Defs.NM2KM * 1000.0), TGTMECOap * 0.001, TGTMECOpe * 0.001 );

			if (cmbTGTInsertionMode.SelectedIndex == 0)
			{
				// SI
				outstr += string.Format("\n>> OMS-1 <<\n" +
					"TIG: {0:f0}:{1:f0}\n" +
					"dV: {2:f1}fps ({3:f1}m/s)\n" +
					"Ap/Pe: {4:f0}x{5:f0}NM ({6:f0}x{7:f0}Km)\n",
					TGTOMS1tig, TGTOMS1tig,
					TGTOMS1dv * Defs.MPS2FPS, TGTOMS1dv,
					TGTOMS1ap / (Defs.NM2KM * 1000.0), TGTOMS1pe / (Defs.NM2KM * 1000.0), TGTOMS1ap * 0.001, TGTOMS1pe * 0.001 );
			}
			else
			{
				// DI
				outstr += string.Format("\n>> OMS-1 <<\n(not performed)\n" );
			}

			outstr += string.Format("\n>> OMS-2 <<\n" +
				"TIG: {0:f0}:{1:f0}\n" +
				"dV: {2:f1}fps ({3:f1}m/s)\n" +
				"Ap/Pe: {4:f0}x{5:f0}NM ({6:f0}x{7:f0}Km)\n",
				TGTOMS2tig, TGTOMS2tig,
				TGTOMS2dv * Defs.MPS2FPS, TGTOMS2dv,
				TGTOMS2ap / (Defs.NM2KM * 1000.0), TGTOMS2pe / (Defs.NM2KM * 1000.0), TGTOMS2ap * 0.001, TGTOMS2pe * 0.001 );

			txtTGTresult.Text = outstr;

			// enable Save button
			btnSave.IsEnabled = true;
			return;
		}

		private void BtnSave_Click(object sender, System.Windows.RoutedEventArgs e)
		{
			// TODO get data
			double TGTMECOinclination = 51.6;// [deg]
			double TGTMECOaltitude = 105000.0;// [m]
			double TGTMECOvel = 7892.4;// [m/s]
			double TGTMECOfpa = 0.8731;// [deg]

			double TGTOMS1tig = 102.0;// [s]
			double TGTOMS1ht = 222240.0;// [m]
			double TGTOMS1theta = 2.32129;// [rad]
			double TGTOMS1c1 = 0.0;// [m/s]
			double TGTOMS1c2 = 0.0;// [1]

			double TGTOMS2tig = 1740.0;// [s]
			double TGTOMS2ht = 205572.1;// [m]
			double TGTOMS2theta = 5.49779;// [rad]
			double TGTOMS2c1 = 0.0;// [m/s]
			double TGTOMS2c2 = 0.0;// [1]

			model.Mission msn = (model.Mission)DataContext;

			// save legacy MECO target
			msn.SetMECOparams( TGTMECOinclination, TGTMECOaltitude, TGTMECOvel, TGTMECOfpa );

			// set I-LOADs for roll to heads up and OMS-1/2 targets
			for (int i = 0; i < msn.OV.ILOAD_List.Count; i++)
			{
				if (msn.OV.ILOAD_List[i].ID == "PHI_2STG")
				{
					msn.OV.ILOAD_List[i].Val = (chkTGTRTHU.IsChecked == true) ? "0.0" : "3.141593";
				}
				else if (msn.OV.ILOAD_List[i].ID == "TVR_ROLL")
				{
					msn.OV.ILOAD_List[i].Val = (chkTGTRTHU.IsChecked == true) ? "0" : "180";
				}
				else if (msn.OV.ILOAD_List[i].ID == "DTIG_OMS")
				{
					msn.OV.ILOAD_List[i].Val = string.Format("{0:f1} {1:f1}", TGTOMS1tig, TGTOMS2tig );
				}
				else if (msn.OV.ILOAD_List[i].ID == "HTGT_OMS")
				{
					msn.OV.ILOAD_List[i].Val = string.Format("{0:f3} {1:f3}", TGTOMS1ht * Defs.MPS2FPS, TGTOMS2ht * Defs.MPS2FPS );
				}
				else if (msn.OV.ILOAD_List[i].ID == "THETA_OMS")
				{
					msn.OV.ILOAD_List[i].Val = string.Format("{0:f3} {1:f3}", TGTOMS1theta, TGTOMS2theta );
				}
				else if (msn.OV.ILOAD_List[i].ID == "C1_OMS")
				{
					msn.OV.ILOAD_List[i].Val = string.Format("{0:f0} {1:f0}", TGTOMS1c1 * Defs.MPS2FPS, TGTOMS2c1 * Defs.MPS2FPS );
				}
				else if (msn.OV.ILOAD_List[i].ID == "C2_OMS")
				{
					msn.OV.ILOAD_List[i].Val = string.Format("{0:f4} {1:f4}", TGTOMS1c2, TGTOMS2c2 );
				}
			}
			return;
		}
	}
}

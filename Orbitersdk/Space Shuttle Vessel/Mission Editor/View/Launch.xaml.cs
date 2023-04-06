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
2023/04/06   indy91
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
		private readonly double[] MECO_ALT = {60, 57, 52};// [NM]

        private OrbitTgtCalcOutput OutputData;

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

            double.TryParse(txtTGTInc.Text, out double TGTORBincl);// [m]
            TGTORBincl *= Defs.RAD;

            // Run MECO and OMS-1/2 logic
            OrbitTgtCalcOptions opt = new OrbitTgtCalcOptions();

            OrbitTgtCalc tgt = new OrbitTgtCalc();

            opt.H_Insertion = MECOalt;
            opt.H_OMS1 = TGTORBalt;
            opt.H_OMS2 = TGTORBalt; //TBD: Use separate altitude targeted with OMS-2
            opt.Inclination = TGTORBincl;
            opt.InsertionMode = DI;

            OutputData = tgt.Calculate(opt);

			// display results
			string outstr = "";
			outstr = string.Format(">> MECO <<\n" +
				"Inclination: {0:f2}º\n" +
				"Altitude: {1:f0}ft ({2:f0}km)\n" +
				"Velocity: {3:f0}fps ({4:f0}m/s)\n" +
				"Flight Path Angle: {5:f4}º\n" +
				"Ap/Pe: {6:f0}x{7:f0}NM ({8:f0}x{9:f0}Km)\n",
				TGTMECOinclination,
                OutputData.TGTMECOaltitude * Defs.MPS2FPS, OutputData.TGTMECOaltitude * 0.001,
                OutputData.TGTMECOvel * Defs.MPS2FPS, OutputData.TGTMECOvel,
                OutputData.TGTMECOfpa,
                OutputData.TGTMECOap / (Defs.NM2KM * 1000.0), OutputData.TGTMECOpe / (Defs.NM2KM * 1000.0), OutputData.TGTMECOap * 0.001, OutputData.TGTMECOpe * 0.001 );

			if (cmbTGTInsertionMode.SelectedIndex == 0)
			{
				// SI
				outstr += string.Format("\n>> OMS-1 <<\n" +
					"TIG: {0:f0}:{1:f0}\n" +
					"dV: {2:f1}fps ({3:f1}m/s)\n" +
					"Ap/Pe: {4:f0}x{5:f0}NM ({6:f0}x{7:f0}Km)\n",
                    OutputData.TGTOMS1tig[0], OutputData.TGTOMS1tig[1],
                    OutputData.TGTOMS1dv * Defs.MPS2FPS, OutputData.TGTOMS1dv,
                    OutputData.TGTOMS1ap / (Defs.NM2KM * 1000.0), OutputData.TGTOMS1pe / (Defs.NM2KM * 1000.0), OutputData.TGTOMS1ap * 0.001, OutputData.TGTOMS1pe * 0.001 );
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
                OutputData.TGTOMS2tig[0], OutputData.TGTOMS2tig[1],
                OutputData.TGTOMS2dv * Defs.MPS2FPS, OutputData.TGTOMS2dv,
                OutputData.TGTOMS2ap / (Defs.NM2KM * 1000.0), OutputData.TGTOMS2pe / (Defs.NM2KM * 1000.0), OutputData.TGTOMS2ap * 0.001, OutputData.TGTOMS2pe * 0.001 );

			txtTGTresult.Text = outstr;

			// enable Save button
			btnSave.IsEnabled = true;
			return;
		}

		private void BtnSave_Click(object sender, System.Windows.RoutedEventArgs e)
		{
            //Data to be saved is stored in OutputData

			model.Mission msn = (model.Mission)DataContext;

			// save legacy MECO target
			msn.SetMECOparams( OutputData.TGTMECOinclination, OutputData.TGTMECOaltitude, OutputData.TGTMECOvel, OutputData.TGTMECOfpa );

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
					msn.OV.ILOAD_List[i].Val = string.Format("{0:f1} {1:f1}", OutputData.oms1.DTIG, OutputData.oms2.DTIG );
				}
				else if (msn.OV.ILOAD_List[i].ID == "HTGT_OMS")
				{
					msn.OV.ILOAD_List[i].Val = string.Format("{0:f1} {1:f1}", OutputData.oms1.HTGT * Defs.MPS2FPS, OutputData.oms2.HTGT * Defs.MPS2FPS );
				}
				else if (msn.OV.ILOAD_List[i].ID == "THETA_OMS")
				{
					msn.OV.ILOAD_List[i].Val = string.Format("{0:f6} {1:f6}", OutputData.oms1.THETA, OutputData.oms2.THETA );
				}
				else if (msn.OV.ILOAD_List[i].ID == "C1_OMS")
				{
					msn.OV.ILOAD_List[i].Val = string.Format("{0:f0} {1:f0}", OutputData.oms1.C1 * Defs.MPS2FPS, OutputData.oms2.C1 * Defs.MPS2FPS );
				}
				else if (msn.OV.ILOAD_List[i].ID == "C2_OMS")
				{
					msn.OV.ILOAD_List[i].Val = string.Format("{0:f4} {1:f4}", OutputData.oms1.C2, OutputData.oms2.C2 );
				}
			}
			return;
		}
	}
}

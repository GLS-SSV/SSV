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

			txtTGTAlt.Text = "160.0";
			txtTGTInc.Text = "51.6";
			cmbTGTInsertionMode.SelectedIndex = 1;
			txtTGTRTHU.IsChecked = true;
			return;
		}

		private void TxtTGTAlt_TextChanged(object sender, TextChangedEventArgs e)
		{
			double input = 0.0;
			double.TryParse( txtTGTAlt.Text, out input );
			txtTGTAltKm.Text = string.Format("{0:f2}", input * Defs.NM2KM );
			return;
		}

		private void BtnSave_Click(object sender, System.Windows.RoutedEventArgs e)
		{
			// TODO MECO logic

			// set I-LOADs to handle roll to heads up
			model.Mission msn = (model.Mission)DataContext;
			for (int i = 0; i < msn.OV.ILOAD_List.Count; i++)
			{
				if (msn.OV.ILOAD_List[i].ID == "PHI_2STG")
				{
					msn.OV.ILOAD_List[i] = new Mission_ILOAD( "PHI_2STG", (txtTGTRTHU.IsChecked == true) ? "0.0" : "3.141593" );
					break;
				}
			}
			return;
		}
	}
}

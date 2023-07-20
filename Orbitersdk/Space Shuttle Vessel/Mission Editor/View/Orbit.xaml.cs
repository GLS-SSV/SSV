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

using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;


namespace SSVMissionEditor
{
	public class Convert_ILOAD_TgtSet : IValueConverter
	{
		public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
		{
			// model to viewer
			// retrieve each I-LOAD
			ObservableCollection<Mission_ILOAD> iloads = (ObservableCollection<Mission_ILOAD>)value;
			string T1 = "";
			string DT = "";
			string EL = "";
			string XOFF = "";
			string YOFF = "";
			string ZOFF = "";
			string LAMB = "";
			foreach (Mission_ILOAD iload in iloads)
			{
				switch (iload.ID)
				{
					case "T1_ILOAD_ARRAY":
						T1 = iload.Val;
						break;
					case "DT_ILOAD_ARRAY":
						DT = iload.Val;
						break;
					case "EL_ILOAD_ARRAY":
						EL = iload.Val;
						break;
					case "XOFF_ILOAD_ARRAY":
						XOFF = iload.Val;
						break;
					case "YOFF_ILOAD_ARRAY":
						YOFF = iload.Val;
						break;
					case "ZOFF_ILOAD_ARRAY":
						ZOFF = iload.Val;
						break;
					case "LAMB_ILOAD":
						LAMB = iload.Val;
						break;
				}
			}

			// compare with Defs and if equal return approriate index for cmbTgtSets
			for (int i = 0; i < Defs.TGTSETS_T1.Length; i++)
			{
				if ((Defs.TGTSETS_T1[i] == T1) &&
					(Defs.TGTSETS_DT[i] == DT) &&
					(Defs.TGTSETS_EL[i] == EL) &&
					(Defs.TGTSETS_XOFF[i] == XOFF) &&
					(Defs.TGTSETS_YOFF[i] == YOFF) &&
					(Defs.TGTSETS_ZOFF[i] == ZOFF) &&
					(Defs.TGTSETS_LAMB[i] == LAMB))
				{
					return i;
				}
			}
			return -1;
		}

		public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
		{
			// viewer to model
			throw new NotSupportedException();
		}
	}


	/// <summary>
	/// Interaction logic for Orbit.xaml
	/// </summary>
	public partial class Orbit : UserControl
	{
		public Orbit()
		{
			InitializeComponent();

			// load tgt sets
			foreach (string x in Defs.TGTSETS_NAME)
			{
				cmbTgtSets.Items.Add( x );
			}
			return;
		}

		private void BtnLoadTgtSets_Click(object sender, System.Windows.RoutedEventArgs e)
		{
			if (cmbTgtSets.SelectedIndex == -1) return;

			// set target set in I-Load list
			model.Mission msn = (model.Mission)DataContext;
			foreach (Mission_ILOAD iload in msn.OV.ILOAD_List)
			{
				switch (iload.ID)
				{
					case "T1_ILOAD_ARRAY":
						iload.Val = Defs.TGTSETS_T1[cmbTgtSets.SelectedIndex];
						break;
					case "DT_ILOAD_ARRAY":
						iload.Val = Defs.TGTSETS_DT[cmbTgtSets.SelectedIndex];
						break;
					case "EL_ILOAD_ARRAY":
						iload.Val = Defs.TGTSETS_EL[cmbTgtSets.SelectedIndex];
						break;
					case "XOFF_ILOAD_ARRAY":
						iload.Val = Defs.TGTSETS_XOFF[cmbTgtSets.SelectedIndex];
						break;
					case "YOFF_ILOAD_ARRAY":
						iload.Val = Defs.TGTSETS_YOFF[cmbTgtSets.SelectedIndex];
						break;
					case "ZOFF_ILOAD_ARRAY":
						iload.Val = Defs.TGTSETS_ZOFF[cmbTgtSets.SelectedIndex];
						break;
					case "LAMB_ILOAD":
						iload.Val = Defs.TGTSETS_LAMB[cmbTgtSets.SelectedIndex];
						break;
				}
			}
			return;
		}

		private void CmbTgtSets_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			if (cmbTgtSets.SelectedIndex == -1) txtTgtSetsDesc.Text = "(non-predefined targets currently loaded)";
			else txtTgtSetsDesc.Text = Defs.TGTSETS_DESC[cmbTgtSets.SelectedIndex];
			return;
		}

		private void BtnPickTgtVessel_Click(object sender, System.Windows.RoutedEventArgs e)
		{
			string vsl = GetTgtVesselName();
			if (vsl != "") txtTgtVessel.Text = vsl;
			return;
		}

		private string GetTgtVesselName()
		{
			PickTgtVesselName picktgtvesselname = new PickTgtVesselName( DataContext );
			picktgtvesselname.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
			picktgtvesselname.ShowDialog();
			return picktgtvesselname.tgtvesselname;
		}
	}
}

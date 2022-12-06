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

using System.Windows.Controls;


namespace SSVMissionEditor
{
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
			if (cmbTgtSets.SelectedIndex == -1) txtTgtSetsDesc.Text = "";
			else txtTgtSetsDesc.Text = Defs.TGTSETS_DESC[cmbTgtSets.SelectedIndex];
			return;
		}
	}
}

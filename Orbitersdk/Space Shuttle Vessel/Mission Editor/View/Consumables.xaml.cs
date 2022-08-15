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
2020/08/22   GLS
2020/10/06   GLS
2021/12/26   GLS
2022/01/10   GLS
2022/03/02   GLS
2022/03/04   GLS
2022/06/24   GLS
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

using SSVMissionEditor.model;
using System;
using System.Windows.Controls;
using System.Windows.Data;


namespace SSVMissionEditor
{
	public class Convert_PRSDTanks : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			return (int)value - 2;
		}

		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			return (int)value + 2;
		}
	}

	/// <summary>
	/// Interaction logic for Consumables.xaml
	/// </summary>
	public partial class Consumables : UserControl
	{
		public Consumables()
		{
			InitializeComponent();

			// add tooltip to show max and min allowable prop loads
			txtFRCS.ToolTip = "Max Load: " + Defs.MAXLOAD_FRCS + " lbs\nMin Load: " + Defs.MINLOAD_FRCS + " lbs";
			txtLRCS.ToolTip = "Max Load: " + Defs.MAXLOAD_ARCS + " lbs\nMin Load: " + Defs.MINLOAD_ARCS + " lbs";
			txtRRCS.ToolTip = "Max Load: " + Defs.MAXLOAD_ARCS + " lbs\nMin Load: " + Defs.MINLOAD_ARCS + " lbs";
			txtLOMS.ToolTip = "Max Load: " + Defs.MAXLOAD_OMS + " lbs\nMin Load: " + Defs.MINLOAD_OMS + " lbs";
			txtROMS.ToolTip = "Max Load: " + Defs.MAXLOAD_OMS + " lbs\nMin Load: " + Defs.MINLOAD_OMS + " lbs";
			// OMS kit loads tooltip loaded in cmbOMSKitTankSets_SelectionChanged
		}

		private void cmbEDOPallet_IsEnabledChanged(object sender, System.Windows.DependencyPropertyChangedEventArgs e)
		{
			if (!cmbEDOPallet.IsEnabled) cmbEDOPallet.SelectedIndex = 0;
			return;
		}

		private void cmbEDOPallet_DualPallet_IsEnabledChanged(object sender, System.Windows.DependencyPropertyChangedEventArgs e)
		{
			if (!((ComboBoxItem)sender).IsEnabled && (cmbEDOPallet.SelectedIndex == 2)) cmbEDOPallet.SelectedIndex = 1;
			return;
		}

		private void ckbEDOKit_IsEnabledChanged(object sender, System.Windows.DependencyPropertyChangedEventArgs e)
		{
			if (!ckbEDOKit.IsEnabled) ckbEDOKit.IsChecked = false;
			return;
		}

		private void cmbOMSKitTankSets_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			if (cmbOMSKitTankSets.SelectedIndex > 0)
			{
				txtKOMS.IsEnabled = true;
				// HACK keep one tank above min load
				txtKOMS.ToolTip = "Max Load: " + (Defs.MAXLOAD_OMS * cmbOMSKitTankSets.SelectedIndex) + " lbs\nMin Load: " + (Defs.MINLOAD_OMS + (Defs.MAXLOAD_OMS * (cmbOMSKitTankSets.SelectedIndex - 1))) + " lbs";
			}
			else
			{
				txtKOMS.IsEnabled = false;
				txtKOMS.ToolTip = "";
			}
			return;
		}
	}
}

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
2023/04/09   GLS
2025/06/21   GLS
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

using System;
using System.Windows.Controls;
using System.Windows.Data;


namespace SSVMissionEditor
{
	public class Convert_DI : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// model to viewer
			return (bool)value ? 1 : 0;
		}

		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// viewer to model
			if ((int)value == 1) return true;
			return false;
		}
	}


	/// <summary>
	/// Interaction logic for Launch.xaml
	/// </summary>
	public partial class Launch : UserControl
	{
		public Launch()
		{
			InitializeComponent();
			return;
		}

		private void txtATOMS1MECOTgtAlt_TextChanged(object sender, TextChangedEventArgs e)
		{
			// display alt in Km in tooltip
			double.TryParse( txtATOMS1MECOTgtAlt.Text.Replace(',', '.'), out double input );
			txtATOMS1MECOTgtAlt.ToolTip = string.Format("{0:f1}Km", input * Defs.NM2KM );
			return;
		}

		private void txtATOMS2TgtAlt_TextChanged(object sender, TextChangedEventArgs e)
		{
			// display alt in Km in tooltip
			double.TryParse( txtATOMS2TgtAlt.Text.Replace(',', '.'), out double input );
			txtATOMS2TgtAlt.ToolTip = string.Format("{0:f1}Km", input * Defs.NM2KM );
			return;
		}

		private void cmbATInsertionMode_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			if (cmbATInsertionMode.SelectedIndex == 0) lblMECO_OMS1_Alt.Content = "OMS-1 Target Alt (NM)";
			else lblMECO_OMS1_Alt.Content = "MECO Target Alt (NM)";
		}
	}
}

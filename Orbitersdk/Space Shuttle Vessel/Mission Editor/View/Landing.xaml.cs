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
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;


namespace SSVMissionEditor
{
	public class Convert_LandingSiteTable_String : IValueConverter
	{
		private const string LINE = "+----+------------------+--------+-------+\n";
		private const string HEADER = "| S  |                  |        |       |\n" +
						"| I  |    LOCATION      |  RWY   |  LG   |\n" +
						"| T  |                  |        |       |\n" +
						"| E  |                  |        |       |\n";

		private int FindLandingSite( List<model.Mission.LandingSiteData> lslist, string rw )
		{
			int i = 0;
			foreach (model.Mission.LandingSiteData ls in lslist)
			{
				if (ls.id == rw) return i;
				i++;
			}
			return -1;
		}

		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// model to viewer
			List<Tuple<string,string>> lst = (List<Tuple<string,string>>)value;
			if (lst.Count == 0) return "";// TODO check null?

			model.Mission msn = (model.Mission)parameter;
			List<model.Mission.LandingSiteData> lslist = msn.LandingSiteDB;
			string strls = "";

			strls += LINE + HEADER;
			for (int lsid = 1; lsid <= 45; lsid++)
			{
				string prisite;
				string tmp;
				int idx;
				//// primary rwy ////
				strls += LINE;
				// SITE: len 2
				strls += "| " + lsid.ToString().PadRight( 2 ) + " | ";
				// LOCATION: len 16
				idx = FindLandingSite( lslist, lst[lsid - 1].Item1 );
				prisite = lslist[idx].sitename;
				strls += prisite.PadRight( 16 ) + " | ";
				// RWY: len 6
				strls += lst[lsid - 1].Item1.PadRight( 6 ) + " | ";
				// LG: len 5
				tmp = "15000";
				strls += tmp.PadLeft( 5 ) + " |\n";

				//// secondary rwy ////
				// SITE: len 2
				strls += "|    | ";
				// LOCATION: len 16
				idx = FindLandingSite( lslist, lst[lsid - 1].Item2 );
				tmp = lslist[idx].sitename;
				if (tmp == prisite) tmp = "";
				strls += tmp.PadRight( 16 ) + " | ";
				strls += "                " + " | ";
				// RWY: len 6
				strls += lst[lsid - 1].Item2.PadRight( 6 ) + " | ";
				// LG: len 5
				tmp = "9850";
				strls += tmp.PadLeft( 5 ) + " |\n";
			}
			strls += LINE;
			return strls;
		}

		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// viewer to model
			throw new NotSupportedException();
		}
	}


	/// <summary>
	/// Interaction logic for Landing.xaml
	/// </summary>
	public partial class Landing : UserControl
	{
		public Landing()
		{
			InitializeComponent();

			rbPri.IsChecked = true;

			for (int i = 1; i <= 45; i++) cmbLSID.Items.Add( i );
			cmbLSID.SelectedIndex = 0;

			//txtLandingSiteOut.SetBinding( TextBox.TextProperty, new Binding
			//{
			//	Source = DataContext,
			//	//Mode = BindingMode.OneWay,
			//	Path = new PropertyPath( "OV._LandingSiteTable" )/*,
			//	Converter = new Convert_LandingSiteTable_String(),
			//	ConverterParameter = DataContext*/
			//});
			return;
		}
	}
}

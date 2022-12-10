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
using System.Collections.ObjectModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;


namespace SSVMissionEditor
{
	public class Convert_LandingSiteTable_String : IValueConverter
	{
		public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
		{
			// model to viewer
			return ((Landing)parameter).FormatLandingSiteTable( (List<Tuple<string,string>>)value );
		}

		public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
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
		private const string LINE = "+----+------------------+--------+-------+\n";
		private const string HEADER = "| S  |                  |        |       |\n" +
						"| I  |    LOCATION      |  RWY   |  LG   |\n" +
						"| T  |                  |        |       |\n" +
						"| E  |                  |        |       |\n";

		public Landing()
		{
			InitializeComponent();

			rbPri.IsChecked = true;

			for (int i = 1; i <= 45; i++) cmbLSID.Items.Add( i );
			cmbLSID.SelectedIndex = 0;

			txtLandingSiteOut.SetBinding( TextBox.TextProperty, new Binding
			{
				Mode = BindingMode.OneWay,
				Path = new PropertyPath( "OV.LandingSiteTable" ),
				Converter = new Convert_LandingSiteTable_String(),
				ConverterParameter = this
			});
			return;
		}
		
		public string FormatLandingSiteTable( List<Tuple<string,string>> lstable )
		{
			string strls = "";
			if (lstable.Count == 0) return "";// TODO check null?

			// get landing site database to extract runway info for display
			List<model.Mission_OV.LandingSiteData> lsDB = ((model.Mission)DataContext).OV.LandingSiteDB;

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
				idx = FindLandingSite( lsDB, lstable[lsid - 1].Item1 );
				prisite = lsDB[idx].sitename;
				strls += prisite.PadRight( 16 ) + " | ";
				// RWY: len 6
				strls += lstable[lsid - 1].Item1.PadRight( 6 ) + " | ";
				// LG: len 5
				tmp = lsDB[idx].lgt;
				strls += tmp.PadLeft( 5 ) + " |\n";

				//// secondary rwy ////
				// SITE: len 2
				strls += "|    | ";
				// LOCATION: len 16
				idx = FindLandingSite( lsDB, lstable[lsid - 1].Item2 );
				tmp = lsDB[idx].sitename;
				if (tmp == prisite) tmp = "";
				strls += tmp.PadRight( 16 ) + " | ";
				// RWY: len 6
				strls += lstable[lsid - 1].Item2.PadRight( 6 ) + " | ";
				// LG: len 5
				tmp = lsDB[idx].lgt;
				strls += tmp.PadLeft( 5 ) + " |\n";
			}
			strls += LINE;
			return strls;
		}
		
		public string FormatLandingSiteDB( int idx )
		{
			List<model.Mission_OV.LandingSiteData> lsDB = ((model.Mission)DataContext).OV.LandingSiteDB;

			string strls = "Location: " + lsDB[idx].sitename + "\n" +
				"Runway: " + lsDB[idx].rwname + "\n";

			if (lsDB[idx].lgt != "0")
			{
				double lat = Math.Round( double.Parse( lsDB[idx].lat ) * Defs.DEG, 6 );
				double lon = Math.Round( double.Parse( lsDB[idx].lon ) * Defs.DEG, 6 );
				strls += "Lat: " + lat + "º   Lon: " + lon + "º\n" +
					"AMSL: " + lsDB[idx].amsl + "m\n" +
					"Heading: " + lsDB[idx].hdg + "º\n" +
					"Length: " + lsDB[idx].lgt + "ft";
			}
			else
			{
				strls += "(runway not implemented)";
			}
			return strls;
		}

		private int FindLandingSite( List<model.Mission_OV.LandingSiteData> lsDB, string rw )
		{
			int i = 0;
			foreach (model.Mission_OV.LandingSiteData ls in lsDB)
			{
				if (ls.id == rw) return i;
				i++;
			}
			return -1;
		}

		private void CmbLandingSiteDB_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			if (cmbLandingSiteDB.SelectedIndex < 0) txtRunwayInfo.Text = "";
			else txtRunwayInfo.Text = FormatLandingSiteDB( cmbLandingSiteDB.SelectedIndex );
			return;
		}

		private void BtnSetRunway_Click(object sender, RoutedEventArgs e)
		{
			if (cmbLandingSiteDB.SelectedIndex < 0) return;
			if (cmbLSID.SelectedIndex < 0) return;

			List<model.Mission_OV.LandingSiteData> lsDB = ((model.Mission)DataContext).OV.LandingSiteDB;
			List<Tuple<string,string>> lstable = ((model.Mission)DataContext).OV.LandingSiteTable;
			string priRW;
			string secRW;

			if (rbPri.IsChecked == true)
			{
				priRW = lsDB[cmbLandingSiteDB.SelectedIndex].id;
				secRW = lstable[cmbLSID.SelectedIndex].Item2;
			}
			else
			{
				priRW = lstable[cmbLSID.SelectedIndex].Item1;
				secRW = lsDB[cmbLandingSiteDB.SelectedIndex].id;
			}

			Tuple<string,string> tp = new Tuple<string,string>( priRW, secRW );
			lstable[cmbLSID.SelectedIndex] = tp;
			((model.Mission)DataContext).OV.LandingSiteTable = lstable;
			return;
		}
	}
}

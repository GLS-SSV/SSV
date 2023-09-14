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
			// retrieve each I-LOAD
			ObservableCollection<Mission_ILOAD> iloads = (ObservableCollection<Mission_ILOAD>)value;
			string RUNWAY_NAME = "";
			string RW_LENGTH = "";
			string RW_LAT = "";
			string RW_LON = "";
			foreach (Mission_ILOAD iload in iloads)
			{
				switch (iload.ID)
				{
					case "RUNWAY_NAME":
						RUNWAY_NAME = iload.Val;
						break;
					case "RW_LENGTH":
						RW_LENGTH = iload.Val;
						break;
					case "RW_LAT":
						RW_LAT = iload.Val;
						break;
					case "RW_LON":
						RW_LON = iload.Val;
						break;
				}
			}

			// process I-Loads into table
			return ((Landing)parameter).FormatLandingSiteTable( RUNWAY_NAME, RW_LENGTH, RW_LAT, RW_LON );
		}

		public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
		{
			// viewer to model
			throw new NotSupportedException();
		}
	}
	public class Convert_LandingSiteDB : IValueConverter
	{
		public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
		{
			// model to viewer
			List<model.Mission_OV.LandingSiteData> lsdb = (List<model.Mission_OV.LandingSiteData>)value;

			if (lsdb.Count == 0) return "";

			string[] list = new string[lsdb.Count];

			for (int i = 0; i < lsdb.Count; i++)
				list[i] = lsdb[i].id + " - " + lsdb[i].sitename;
			return list;
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
				Path = new PropertyPath( "OV.ILOAD_List" ),
				Converter = new Convert_LandingSiteTable_String(),
				ConverterParameter = this
				//Binding OV.ILOAD_List, Mode=OneWay, UpdateSourceTrigger=PropertyChanged, Converter={StaticResource Convert_ILOAD_TgtSet}
			});
			return;
		}
		
		public string FormatLandingSiteTable( string RUNWAY_NAME, string RW_LENGTH, string RW_LAT, string RW_LON )
		{
			string strls = "";

			char[] spc = {' '};
			string[] runway_name = RUNWAY_NAME.Split( spc, StringSplitOptions.RemoveEmptyEntries );
			string[] rw_length = RW_LENGTH.Split( spc, StringSplitOptions.RemoveEmptyEntries );
			string[] rw_lat = RW_LAT.Split( spc, StringSplitOptions.RemoveEmptyEntries );
			string[] rw_lon = RW_LON.Split( spc, StringSplitOptions.RemoveEmptyEntries );

			if (runway_name.Length != 90) return "";
			if (rw_length.Length != 90) return "";
			if (rw_lat.Length != 90) return "";
			if (rw_length.Length != 90) return "";

			model.Mission msn = (model.Mission)DataContext;
			List<model.Mission_OV.LandingSiteData> lsDB = msn.OV.LandingSiteDB;
			string[] sitename = new string[90];
			string[] rwy = new string[90];
			for (int i = 0; i < 90; i++)
			{
				// find runway in DB
				int idx = lsDB.FindIndex( item => (item.RUNWAY_NAME == runway_name[i]) && (item.RW_LAT == rw_lat[i]) && (item.RW_LON == rw_lon[i]) );
				if (idx != -1)
				{
					sitename[i] = lsDB[idx].sitename;
					rwy[i] = lsDB[idx].id;
				}
				else
				{
					sitename[i] = "???";
					rwy[i] = runway_name[i];
				}
			}

			strls += LINE + HEADER;
			for (int lsid = 1; lsid <= 45; lsid++)
			{
				string prisite = "";
				string loc = "";
				string lgt = "";

				//// primary rwy ////
				loc = sitename[(lsid - 1) * 2];
				prisite = loc;
				lgt = rw_length[(lsid - 1) * 2];

				strls += LINE;
				// SITE: len 2
				strls += "| " + lsid.ToString().PadRight( 2 ) + " | ";
				// LOCATION: len 16
				strls += loc.PadRight( 16 ) + " | ";
				// RWY: len 6
				strls += rwy[(lsid - 1) * 2].PadRight( 6 ) + " | ";
				// LG: len 5
				strls += lgt.PadLeft( 5 ) + " |\n";

				//// secondary rwy ////
				loc = sitename[((lsid - 1) * 2) + 1];
				lgt = rw_length[((lsid - 1) * 2) + 1];

				// SITE: len 2
				strls += "|    | ";
				// LOCATION: len 16
				if (loc == prisite) loc = "";
				strls += loc.PadRight( 16 ) + " | ";
				// RWY: len 6
				strls += rwy[((lsid - 1) * 2) + 1].PadRight( 6 ) + " | ";
				// LG: len 5
				strls += lgt.PadLeft( 5 ) + " |\n";
			}
			strls += LINE;
			return strls;
		}
		
		public string FormatLandingSiteDB( int idx )
		{
			List<model.Mission_OV.LandingSiteData> lsDB = ((model.Mission)DataContext).OV.LandingSiteDB;

			string strls = "Location: " + lsDB[idx].sitename + "\n" +
				"Runway: " + lsDB[idx].RUNWAY_NAME + "\n";

			if (lsDB[idx].RW_LENGTH != "0")
			{
				double lat = Math.Round( double.Parse( lsDB[idx].RW_LAT ) * Defs.DEG, 6 );
				double lon = Math.Round( double.Parse( lsDB[idx].RW_LON ) * Defs.DEG, 6 );
				double az = Math.Round( double.Parse( lsDB[idx].RW_AZIMUTH ) * Defs.DEG, 2 );
				double alt_m = Math.Round( double.Parse( lsDB[idx].RUNWAY_ALT ) * 0.3048, 1 );
				double delh_m = Math.Round( double.Parse( lsDB[idx].RW_DELH ) * 0.3048, 1 );
				double mvar = Math.Round( double.Parse( lsDB[idx].RW_MAG_VAR ) * Defs.DEG, 2 );
				strls += "Lat: " + lat + "º   Lon: " + lon + "º\n" +
					"Altitude: " + lsDB[idx].RUNWAY_ALT + "ft (" + alt_m + "m)\n" +
					"Azimuth: " + az + "º\n" +
					"Length: " + lsDB[idx].RW_LENGTH + "ft\n" +
					"MSL: " + lsDB[idx].RW_DELH + "ft (" + delh_m + "m)\n" +
					"Mag. Var.: " + mvar + "º";
			}
			else
			{
				strls += "(runway not implemented)";
			}
			return strls;
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

			int idx = cmbLSID.SelectedIndex * 2;
			if (rbPri.IsChecked == false) idx++;

			// get current list
			string RUNWAY_ALT = "";
			string RUNWAY_NAME = "";
			string RW_AZIMUTH = "";
			string RW_DELH = "";
			string RW_LAT = "";
			string RW_LENGTH = "";
			string RW_LON = "";
			string RW_MAG_VAR = "";

			model.Mission msn = (model.Mission)DataContext;
			foreach (Mission_ILOAD iload in msn.OV.ILOAD_List)
			{
				switch (iload.ID)
				{
					case "RUNWAY_ALT":
						RUNWAY_ALT = iload.Val;
						break;
					case "RUNWAY_NAME":
						RUNWAY_NAME = iload.Val;
						break;
					case "RW_AZIMUTH":
						RW_AZIMUTH = iload.Val;
						break;
					case "RW_DELH":
						RW_DELH = iload.Val;
						break;
					case "RW_LAT":
						RW_LAT = iload.Val;
						break;
					case "RW_LENGTH":
						RW_LENGTH = iload.Val;
						break;
					case "RW_LON":
						RW_LON = iload.Val;
						break;
					case "RW_MAG_VAR":
						RW_MAG_VAR = iload.Val;
						break;
				}
			}

			char[] spc = {' '};
			string[] runway_alt = RUNWAY_ALT.Split( spc, StringSplitOptions.RemoveEmptyEntries );
			if (runway_alt.Length != 90)
			{
				// TODO kaput
			}
			string[] runway_name = RUNWAY_NAME.Split( spc, StringSplitOptions.RemoveEmptyEntries );
			if (runway_name.Length != 90)
			{
				// TODO kaput
			}
			string[] rw_azimuth = RW_AZIMUTH.Split( spc, StringSplitOptions.RemoveEmptyEntries );
			if (rw_azimuth.Length != 90)
			{
				// TODO kaput
			}
			string[] rw_delh = RW_DELH.Split( spc, StringSplitOptions.RemoveEmptyEntries );
			if (rw_delh.Length != 90)
			{
				// TODO kaput
			}
			string[] rw_lat = RW_LAT.Split( spc, StringSplitOptions.RemoveEmptyEntries );
			if (rw_lat.Length != 90)
			{
				// TODO kaput
			}
			string[] rw_length = RW_LENGTH.Split( spc, StringSplitOptions.RemoveEmptyEntries );
			if (rw_length.Length != 90)
			{
				// TODO kaput
			}
			string[] rw_lon = RW_LON.Split( spc, StringSplitOptions.RemoveEmptyEntries );
			if (rw_lon.Length != 90)
			{
				// TODO kaput
			}
			string[] rw_mag_var = RW_MAG_VAR.Split( spc, StringSplitOptions.RemoveEmptyEntries );
			if (rw_mag_var.Length != 90)
			{
				// TODO kaput
			}

			// replace entry
			runway_alt[idx] = lsDB[cmbLandingSiteDB.SelectedIndex].RUNWAY_ALT;
			runway_name[idx] = lsDB[cmbLandingSiteDB.SelectedIndex].RUNWAY_NAME;
			rw_azimuth[idx] = lsDB[cmbLandingSiteDB.SelectedIndex].RW_AZIMUTH;
			rw_delh[idx] = lsDB[cmbLandingSiteDB.SelectedIndex].RW_DELH;
			rw_lat[idx] = lsDB[cmbLandingSiteDB.SelectedIndex].RW_LAT;
			rw_length[idx] = lsDB[cmbLandingSiteDB.SelectedIndex].RW_LENGTH;
			rw_lon[idx] = lsDB[cmbLandingSiteDB.SelectedIndex].RW_LON;
			rw_mag_var[idx] = lsDB[cmbLandingSiteDB.SelectedIndex].RW_MAG_VAR;

			// save current list
			RUNWAY_ALT = "";
			RUNWAY_NAME = "";
			RW_AZIMUTH = "";
			RW_DELH = "";
			RW_LAT = "";
			RW_LENGTH = "";
			RW_LON = "";
			RW_MAG_VAR = "";
			for (int i = 0; i < 90; i++)
			{
				RUNWAY_ALT += runway_alt[i] + " ";
				RUNWAY_NAME += runway_name[i] + " ";
				RW_AZIMUTH += rw_azimuth[i] + " ";
				RW_DELH += rw_delh[i] + " ";
				RW_LAT += rw_lat[i] + " ";
				RW_LENGTH += rw_length[i] + " ";
				RW_LON += rw_lon[i] + " ";
				RW_MAG_VAR += rw_mag_var[i] + " ";
			}

			// save landing site table I-Loads
			ObservableCollection<Mission_ILOAD> newiloads = msn.OV.ILOAD_List;
			foreach (Mission_ILOAD iload in newiloads)
			{
				switch (iload.ID)
				{
					case "RUNWAY_ALT":
						iload.Val = RUNWAY_ALT.TrimEnd( ' ' );
						break;
					case "RUNWAY_NAME":
						iload.Val = RUNWAY_NAME.TrimEnd( ' ' );
						break;
					case "RW_AZIMUTH":
						iload.Val = RW_AZIMUTH.TrimEnd( ' ' );
						break;
					case "RW_DELH":
						iload.Val = RW_DELH.TrimEnd( ' ' );
						break;
					case "RW_LAT":
						iload.Val = RW_LAT.TrimEnd( ' ' );
						break;
					case "RW_LENGTH":
						iload.Val = RW_LENGTH.TrimEnd( ' ' );
						break;
					case "RW_LON":
						iload.Val = RW_LON.TrimEnd( ' ' );
						break;
					case "RW_MAG_VAR":
						iload.Val = RW_MAG_VAR.TrimEnd( ' ' );
						break;
				}
			}
			// HACK another duct-tape solution...
			msn.OV.ILOAD_List = newiloads;
			return;
		}
	}
}

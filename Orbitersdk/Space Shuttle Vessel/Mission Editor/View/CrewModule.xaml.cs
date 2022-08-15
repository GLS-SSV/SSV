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
using System.Windows.Controls;
using System.Windows.Data;
using SSVMissionEditor.model;


namespace SSVMissionEditor
{
	public class Convert_Crew : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture ) => (int)value - 2;
		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture ) => (int)value + 2;
	}

	public class Convert_FlightDeck_Type : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture ) => (int)value;
		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture ) => (FlightDeck_Type)value;
	}

	public class Convert_Galley_Type : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture ) => (int)value;
		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture ) => (Galley_Type)value;
	}

	public class Convert_SleepStations_Type : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture ) => (int)value;
		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture ) => (SleepStations_Type)value;
	}

	/// <summary>
	/// Interaction logic for CrewModule.xaml
	/// </summary>
	public partial class CrewModule : UserControl
	{
		public CrewModule()
		{
			InitializeComponent();
		}
	}
}

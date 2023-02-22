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
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using SSVMissionEditor.model;


namespace SSVMissionEditor
{
	public class Convert_RMS_SN : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			switch (value)
			{
				/*case 201:
					return 0;*/
				case 202:
					return 1;
				case 301:
					return 2;
				case 302:
					return 3;
				case 303:
					return 4;
				default:
					return 0;
			}
		}

		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			switch (value)
			{
				/*case 0:
					return 201;*/
				case 1:
					return 202;
				case 2:
					return 301;
				case 3:
					return 302;
				case 4:
					return 303;
				default:
					return 201;
			}
		}
	}


	/// <summary>
	/// Interaction logic for RMS.xaml
	/// </summary>
	public partial class RMS : Window
	{
		public RMS( object datacontext, string bind )
		{
			InitializeComponent();

			DataContext = datacontext;

			cmbSN.SetBinding( ComboBox.SelectedIndexProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bind + ".SN" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
				Converter = new Convert_RMS_SN()
			});

			cmbElbow.SetBinding( ComboBox.SelectedIndexProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bind + ".Elbow" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
				Converter = new Convert_CCTV_Camera_Type()
			});

			cmbWrist.SetBinding( ComboBox.SelectedIndexProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bind + ".Wrist" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
				Converter = new Convert_CCTV_Camera_Type()
			});

			chkElbowIlluminator.SetBinding( CheckBox.IsCheckedProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bind + ".ElbowIlluminator" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});

			chkWristIlluminator.SetBinding( CheckBox.IsCheckedProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bind + ".WristIlluminator" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});

			chkElbowIlluminator.SetBinding( CheckBox.IsEnabledProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bind + ".ElbowIlluminatorEnabled" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});

			chkWristIlluminator.SetBinding( CheckBox.IsEnabledProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bind + ".WristIlluminatorEnabled" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			return;
		}
	}
}

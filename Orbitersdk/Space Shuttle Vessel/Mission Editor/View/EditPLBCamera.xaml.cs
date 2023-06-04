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
using System.Windows.Input;
using SSVMissionEditor.model;


namespace SSVMissionEditor
{
	public class Convert_CCTV_Camera_Type : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			switch (value)
			{
				case CCTV_Camera_Type._506_508:
					return 0;
				case CCTV_Camera_Type.CTVC_ITVC:
				default:
					return 1;
			}
		}

		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			switch (value)
			{
				case 0:
					return CCTV_Camera_Type._506_508;
				case 1:
				default:
					return CCTV_Camera_Type.CTVC_ITVC;
			}
		}
	}


	/// <summary>
	/// Interaction logic for PLBCameras.xaml
	/// </summary>
	public partial class EditPLBCamera : Window
	{
		public EditPLBCamera( object datacontext, string bind )
		{
			InitializeComponent();

			DataContext = datacontext;

			cmbType.SetBinding( ComboBox.SelectedIndexProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( "OV.PLB_Cameras.Type" + bind ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
				Converter = new Convert_CCTV_Camera_Type()
			});

			chkCustom.SetBinding( CheckBox.IsCheckedProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( "OV.PLB_Cameras.Custom" + bind ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});

			chkIlluminator.SetBinding( CheckBox.IsCheckedProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( "OV.PLB_Cameras.Illuminator" + bind ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});

			txtXo.SetBinding( TextBox.TextProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( "OV.PLB_Cameras.Xo" + bind ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});

			txtYo.SetBinding( TextBox.TextProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( "OV.PLB_Cameras.Yo" + bind ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});

			txtZo.SetBinding( TextBox.TextProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( "OV.PLB_Cameras.Zo" + bind ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});

			txtRot.SetBinding( TextBox.TextProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( "OV.PLB_Cameras.Rot" + bind ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			return;
		}

		private void ChkCustom_Checked(object sender, RoutedEventArgs e)
		{
			txtXo.IsEnabled = true;
			txtYo.IsEnabled = true;
			txtZo.IsEnabled = true;
			txtRot.IsEnabled = true;
			return;
		}

		private void ChkCustom_Unchecked(object sender, RoutedEventArgs e)
		{
			txtXo.IsEnabled = false;
			txtYo.IsEnabled = false;
			txtZo.IsEnabled = false;
			txtRot.IsEnabled = false;
			return;
		}

		private void cmbType_SelectionChanged(object sender, RoutedEventArgs e)
		{
			if (cmbType.SelectedIndex == 1) chkIlluminator.IsEnabled = true;
			else
			{
				chkIlluminator.IsEnabled = false;
				chkIlluminator.IsChecked = false;
			}
			return;
		}

		private void CommandBinding_Executed( object sender, ExecutedRoutedEventArgs e )
		{
			Close();
		}
	}
}

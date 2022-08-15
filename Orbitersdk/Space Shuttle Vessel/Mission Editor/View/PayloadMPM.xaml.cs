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
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;


namespace SSVMissionEditor
{
	public class Convert_MRL_Type : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture ) => (int)value;
		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture ) => (MRL_Type)value;
	}

	public class Convert_MPM_Attachment_Type : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture ) => (int)value;
		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture ) => (MPM_Attachment_Type)value;
	}


	/// <summary>
	/// Interaction logic for MPMPayload.xaml
	/// </summary>
	public partial class PayloadMPM : Window
	{
		public PayloadMPM( object datacontext, string bind )
		{
			this.bind = bind;

			InitializeComponent();

			DataContext = datacontext;

			ckbShoulder.SetBinding( CheckBox.IsCheckedProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bind + ".HasShoulder" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			ckbForward.SetBinding( CheckBox.IsCheckedProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bind + ".HasForward" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			ckbMid.SetBinding( CheckBox.IsCheckedProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bind + ".HasMid" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			ckbAft.SetBinding( CheckBox.IsCheckedProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bind + ".HasAft" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});

			txtShoulderMesh.SetBinding( TextBox.TextProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bind + ".ShoulderMesh" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			txtForwardMesh.SetBinding( TextBox.TextProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bind + ".ForwardMesh" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			txtMidMesh.SetBinding( TextBox.TextProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bind + ".MidMesh" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			txtAftMesh.SetBinding( TextBox.TextProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bind + ".AftMesh" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			txtShoulderMesh.SetBinding( TextBox.IsEnabledProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bind + ".HasShoulder" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			txtForwardMesh.SetBinding( TextBox.IsEnabledProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bind + ".HasForward" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			txtMidMesh.SetBinding( TextBox.IsEnabledProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bind + ".HasMid" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			txtAftMesh.SetBinding( TextBox.IsEnabledProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bind + ".HasAft" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});

			cmbShoulder.SetBinding( ComboBox.ItemsSourceProperty, new Binding
			{
				Source = Enum.GetValues( typeof(MRL_Type) )
			});
			cmbForward.SetBinding( ComboBox.ItemsSourceProperty, new Binding
			{
				Source = Enum.GetValues( typeof(MRL_Type) )
			});
			cmbMid.SetBinding( ComboBox.ItemsSourceProperty, new Binding
			{
				Source = Enum.GetValues( typeof(MRL_Type) )
			});
			cmbAft.SetBinding( ComboBox.ItemsSourceProperty, new Binding
			{
				Source = Enum.GetValues( typeof(MRL_Type) )
			});
			cmbShoulder.SetBinding( ComboBox.SelectedIndexProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bind + ".ShoulderPedestalMRL" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
				Converter = new Convert_MRL_Type()
			});
			cmbForward.SetBinding( ComboBox.SelectedIndexProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bind + ".ForwardPedestalMRL" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
				Converter = new Convert_MRL_Type()
			});
			cmbMid.SetBinding( ComboBox.SelectedIndexProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bind + ".MidPedestalMRL" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
				Converter = new Convert_MRL_Type()
			});
			cmbAft.SetBinding( ComboBox.SelectedIndexProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bind + ".AftPedestalMRL" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
				Converter = new Convert_MRL_Type()
			});
			cmbShoulder.SetBinding( ComboBox.IsEnabledProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bind + ".HasShoulder" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			cmbForward.SetBinding( ComboBox.IsEnabledProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bind + ".HasForward" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			cmbMid.SetBinding( ComboBox.IsEnabledProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bind + ".HasMid" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			cmbAft.SetBinding( ComboBox.IsEnabledProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bind + ".HasAft" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});

			cmbAttachment.SetBinding( ComboBox.ItemsSourceProperty, new Binding
			{
				Source = Enum.GetValues( typeof(MPM_Attachment_Type) )
			});
			cmbAttachment.SetBinding( ComboBox.SelectedIndexProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bind + ".Attachment" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
				Converter = new Convert_MPM_Attachment_Type()
			});

			ckbHasPL.SetBinding( CheckBox.IsCheckedProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bind + ".HasPayload" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			btnPayload.SetBinding( Button.IsEnabledProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bind + ".HasPayload" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
		}

		private void btnPayload_Click(object sender, RoutedEventArgs e)
		{
			EditPayload editpayload = new EditPayload( DataContext, bind + ".Payload.VesselClass", bind + ".Payload.Name", bind + ".Payload.AttachmentID", bind + ".Payload.ScnParams" );
			editpayload.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
			editpayload.ShowDialog();
			return;
		}

		string bind;
	}
}

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
using System.Windows.Shapes;
using System.Windows.Media;
using System.Linq;


namespace SSVMissionEditor
{
	public class Convert_PLID_Edit_Button : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// model to viewer
			return ((int)value != 0) ? value.ToString() : "Edit";
		}

		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// viewer to model
			throw new NotSupportedException();
		}
	}

	public class Convert_PLID_LONGERON_ACTIVE_Active : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// model to viewer
			return ((int)value != 0);
		}

		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// viewer to model
			if ((bool)value == true) return Defs.LONGERON_ACTIVE[0];// select first PLID when enabled
			else return 0;
		}
	}
	public class Convert_PLID_LONGERON_PASSIVE_Active : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// model to viewer
			return ((int)value != 0);
		}

		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// viewer to model
			if ((bool)value == true) return Defs.LONGERON_PASSIVE[0];// select first PLID when enabled
			else return 0;
		}
	}
	
	public class Convert_PLID_KEEL_ACTIVE_Active : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// model to viewer
			return ((int)value != 0);
		}

		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// viewer to model
			if ((bool)value == true) return Defs.KEEL_ACTIVE[0];// select first PLID when enabled
			else return 0;
		}
	}
	public class Convert_PLID_KEEL_PASSIVE_Active : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// model to viewer
			return ((int)value != 0);
		}

		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// viewer to model
			if ((bool)value == true) return Defs.KEEL_PASSIVE[0];// select first PLID when enabled
			else return 0;
		}
	}

	/// <summary>
	/// Interaction logic for EditLatches.xaml
	/// </summary>
	public partial class EditLatches : Window
	{
		public EditLatches( object datacontext, bool active, short pl_idx )
		{
			InitializeComponent();

			cmdEditPort1.IsEnabled = false;
			cmdEditPort2.IsEnabled = false;
			cmdEditPort3.IsEnabled = false;
			cmdEditPort4.IsEnabled = false;
			cmdEditStbd1.IsEnabled = false;
			cmdEditStbd2.IsEnabled = false;
			cmdEditStbd3.IsEnabled = false;
			cmdEditStbd4.IsEnabled = false;
			cmdEditKeel1.IsEnabled = false;
			cmdEditKeel2.IsEnabled = false;
			cmdEditKeel3.IsEnabled = false;
			cmdEditKeel4.IsEnabled = false;

			DataContext = datacontext;
			this.active = active;
			this.pl_idx = pl_idx;

			DrawPayloadBay();

			if (active)
			{
				// define bindings
				string pl_bind = "OV.PL_Active[" + pl_idx + "]";

				cmdEditPort1.SetBinding( Button.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( pl_bind + ".Latches[0].PLID" ),
					Converter = new Convert_PLID_Edit_Button()
				});
				cmdEditPort2.SetBinding( Button.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( pl_bind + ".Latches[1].PLID" ),
					Converter = new Convert_PLID_Edit_Button()
				});
				cmdEditPort3.SetBinding( Button.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( pl_bind + ".Latches[2].PLID" ),
					Converter = new Convert_PLID_Edit_Button()
				});
				cmdEditPort4.SetBinding( Button.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( pl_bind + ".Latches[3].PLID" ),
					Converter = new Convert_PLID_Edit_Button()
				});
				cmdEditStbd1.SetBinding( Button.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( pl_bind + ".Latches[4].PLID" ),
					Converter = new Convert_PLID_Edit_Button()
				});
				cmdEditStbd2.SetBinding( Button.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( pl_bind + ".Latches[5].PLID" ),
					Converter = new Convert_PLID_Edit_Button()
				});
				cmdEditStbd3.SetBinding( Button.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( pl_bind + ".Latches[6].PLID" ),
					Converter = new Convert_PLID_Edit_Button()
				});
				cmdEditStbd4.SetBinding( Button.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( pl_bind + ".Latches[7].PLID" ),
					Converter = new Convert_PLID_Edit_Button()
				});
				cmdEditKeel1.SetBinding( Button.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( pl_bind + ".Latches[8].PLID" ),
					Converter = new Convert_PLID_Edit_Button()
				});
				cmdEditKeel2.SetBinding( Button.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( pl_bind + ".Latches[9].PLID" ),
					Converter = new Convert_PLID_Edit_Button()
				});
				cmdEditKeel3.SetBinding( Button.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( pl_bind + ".Latches[10].PLID" ),
					Converter = new Convert_PLID_Edit_Button()
				});
				cmdEditKeel4.SetBinding( Button.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( pl_bind + ".Latches[11].PLID" ),
					Converter = new Convert_PLID_Edit_Button()
				});

				cbEnabledPort1.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.TwoWay,
					Path = new PropertyPath( pl_bind + ".Latches[0].PLID" ),
					Converter = new Convert_PLID_LONGERON_ACTIVE_Active()
				});
				cbEnabledPort2.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.TwoWay,
					Path = new PropertyPath( pl_bind + ".Latches[1].PLID" ),
					Converter = new Convert_PLID_LONGERON_ACTIVE_Active()
				});
				cbEnabledPort3.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.TwoWay,
					Path = new PropertyPath( pl_bind + ".Latches[2].PLID" ),
					Converter = new Convert_PLID_LONGERON_ACTIVE_Active()
				});
				cbEnabledPort4.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.TwoWay,
					Path = new PropertyPath( pl_bind + ".Latches[3].PLID" ),
					Converter = new Convert_PLID_LONGERON_ACTIVE_Active()
				});
				cbEnabledStbd1.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.TwoWay,
					Path = new PropertyPath( pl_bind + ".Latches[4].PLID" ),
					Converter = new Convert_PLID_LONGERON_ACTIVE_Active()
				});
				cbEnabledStbd2.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.TwoWay,
					Path = new PropertyPath( pl_bind + ".Latches[5].PLID" ),
					Converter = new Convert_PLID_LONGERON_ACTIVE_Active()
				});
				cbEnabledStbd3.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.TwoWay,
					Path = new PropertyPath( pl_bind + ".Latches[6].PLID" ),
					Converter = new Convert_PLID_LONGERON_ACTIVE_Active()
				});
				cbEnabledStbd4.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.TwoWay,
					Path = new PropertyPath( pl_bind + ".Latches[7].PLID" ),
					Converter = new Convert_PLID_LONGERON_ACTIVE_Active()
				});
				cbEnabledKeel1.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.TwoWay,
					Path = new PropertyPath( pl_bind + ".Latches[8].PLID" ),
					Converter = new Convert_PLID_KEEL_ACTIVE_Active()
				});
				cbEnabledKeel2.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.TwoWay,
					Path = new PropertyPath( pl_bind + ".Latches[9].PLID" ),
					Converter = new Convert_PLID_KEEL_ACTIVE_Active()
				});
				cbEnabledKeel3.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.TwoWay,
					Path = new PropertyPath( pl_bind + ".Latches[10].PLID" ),
					Converter = new Convert_PLID_KEEL_ACTIVE_Active()
				});
				cbEnabledKeel4.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.TwoWay,
					Path = new PropertyPath( pl_bind + ".Latches[11].PLID" ),
					Converter = new Convert_PLID_KEEL_ACTIVE_Active()
				});
			}
			else
			{
				// define bindings
				string pl_bind = "OV.PL_Passive[" + pl_idx + "]";

				cmdEditPort1.SetBinding( Button.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( pl_bind + ".Latches[0].PLID" ),
					Converter = new Convert_PLID_Edit_Button()
				});
				cmdEditPort2.SetBinding( Button.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( pl_bind + ".Latches[1].PLID" ),
					Converter = new Convert_PLID_Edit_Button()
				});
				cmdEditPort3.SetBinding( Button.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( pl_bind + ".Latches[2].PLID" ),
					Converter = new Convert_PLID_Edit_Button()
				});
				cmdEditPort4.SetBinding( Button.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( pl_bind + ".Latches[3].PLID" ),
					Converter = new Convert_PLID_Edit_Button()
				});
				cmdEditStbd1.SetBinding( Button.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( pl_bind + ".Latches[4].PLID" ),
					Converter = new Convert_PLID_Edit_Button()
				});
				cmdEditStbd2.SetBinding( Button.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( pl_bind + ".Latches[5].PLID" ),
					Converter = new Convert_PLID_Edit_Button()
				});
				cmdEditStbd3.SetBinding( Button.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( pl_bind + ".Latches[6].PLID" ),
					Converter = new Convert_PLID_Edit_Button()
				});
				cmdEditStbd4.SetBinding( Button.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( pl_bind + ".Latches[7].PLID" ),
					Converter = new Convert_PLID_Edit_Button()
				});
				cmdEditKeel1.SetBinding( Button.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( pl_bind + ".Latches[8].PLID" ),
					Converter = new Convert_PLID_Edit_Button()
				});
				cmdEditKeel2.SetBinding( Button.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( pl_bind + ".Latches[9].PLID" ),
					Converter = new Convert_PLID_Edit_Button()
				});
				cmdEditKeel3.SetBinding( Button.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( pl_bind + ".Latches[10].PLID" ),
					Converter = new Convert_PLID_Edit_Button()
				});
				cmdEditKeel4.SetBinding( Button.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( pl_bind + ".Latches[11].PLID" ),
					Converter = new Convert_PLID_Edit_Button()
				});

				cbEnabledPort1.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.TwoWay,
					Path = new PropertyPath( pl_bind + ".Latches[0].PLID" ),
					Converter = new Convert_PLID_LONGERON_PASSIVE_Active()
				});
				cbEnabledPort2.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.TwoWay,
					Path = new PropertyPath( pl_bind + ".Latches[1].PLID" ),
					Converter = new Convert_PLID_LONGERON_PASSIVE_Active()
				});
				cbEnabledPort3.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.TwoWay,
					Path = new PropertyPath( pl_bind + ".Latches[2].PLID" ),
					Converter = new Convert_PLID_LONGERON_PASSIVE_Active()
				});
				cbEnabledPort4.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.TwoWay,
					Path = new PropertyPath( pl_bind + ".Latches[3].PLID" ),
					Converter = new Convert_PLID_LONGERON_PASSIVE_Active()
				});
				cbEnabledStbd1.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.TwoWay,
					Path = new PropertyPath( pl_bind + ".Latches[4].PLID" ),
					Converter = new Convert_PLID_LONGERON_PASSIVE_Active()
				});
				cbEnabledStbd2.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.TwoWay,
					Path = new PropertyPath( pl_bind + ".Latches[5].PLID" ),
					Converter = new Convert_PLID_LONGERON_PASSIVE_Active()
				});
				cbEnabledStbd3.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.TwoWay,
					Path = new PropertyPath( pl_bind + ".Latches[6].PLID" ),
					Converter = new Convert_PLID_LONGERON_PASSIVE_Active()
				});
				cbEnabledStbd4.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.TwoWay,
					Path = new PropertyPath( pl_bind + ".Latches[7].PLID" ),
					Converter = new Convert_PLID_LONGERON_PASSIVE_Active()
				});
				cbEnabledKeel1.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.TwoWay,
					Path = new PropertyPath( pl_bind + ".Latches[8].PLID" ),
					Converter = new Convert_PLID_KEEL_PASSIVE_Active()
				});
				cbEnabledKeel2.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.TwoWay,
					Path = new PropertyPath( pl_bind + ".Latches[9].PLID" ),
					Converter = new Convert_PLID_KEEL_PASSIVE_Active()
				});
				cbEnabledKeel3.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.TwoWay,
					Path = new PropertyPath( pl_bind + ".Latches[10].PLID" ),
					Converter = new Convert_PLID_KEEL_PASSIVE_Active()
				});
				cbEnabledKeel4.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.TwoWay,
					Path = new PropertyPath( pl_bind + ".Latches[11].PLID" ),
					Converter = new Convert_PLID_KEEL_PASSIVE_Active()
				});
			}
			return;
		}

		private void CmdEditPort1_Click(object sender, RoutedEventArgs e)
		{
			ShowEditLatch( 0, false );
			return;
		}

		private void CmdEditPort2_Click(object sender, RoutedEventArgs e)
		{
			ShowEditLatch( 1, false );
			return;
		}

		private void CmdEditPort3_Click(object sender, RoutedEventArgs e)
		{
			ShowEditLatch( 2, false );
			return;
		}

		private void CmdEditPort4_Click(object sender, RoutedEventArgs e)
		{
			ShowEditLatch( 3, false );
			return;
		}

		private void CmdEditStbd1_Click(object sender, RoutedEventArgs e)
		{
			ShowEditLatch( 4, false );
			return;
		}

		private void CmdEditStbd2_Click(object sender, RoutedEventArgs e)
		{
			ShowEditLatch( 5, false );
			return;
		}

		private void CmdEditStbd3_Click(object sender, RoutedEventArgs e)
		{
			ShowEditLatch( 6, false );
			return;
		}

		private void CmdEditStbd4_Click(object sender, RoutedEventArgs e)
		{
			ShowEditLatch( 7, false );
			return;
		}

		private void CmdEditKeel1_Click(object sender, RoutedEventArgs e)
		{
			ShowEditLatch( 8, true );
			return;
		}

		private void CmdEditKeel2_Click(object sender, RoutedEventArgs e)
		{
			ShowEditLatch( 9, true );
			return;
		}

		private void CmdEditKeel3_Click(object sender, RoutedEventArgs e)
		{
			ShowEditLatch( 10, true );
			return;
		}

		private void CmdEditKeel4_Click(object sender, RoutedEventArgs e)
		{
			ShowEditLatch( 11, true );
			return;
		}

		private void CbEnabledPort1_Checked(object sender, RoutedEventArgs e)
		{
			cmdEditPort1.IsEnabled = true;

			// update diagram
			DrawPayloadBay();
			return;
		}

		private void CbEnabledPort1_Unchecked(object sender, RoutedEventArgs e)
		{
			cmdEditPort1.IsEnabled = false;

			// update diagram
			DrawPayloadBay();
			return;
		}

		private void CbEnabledPort2_Checked(object sender, RoutedEventArgs e)
		{
			cmdEditPort2.IsEnabled = true;

			// update diagram
			DrawPayloadBay();
			return;
		}

		private void CbEnabledPort2_Unchecked(object sender, RoutedEventArgs e)
		{
			cmdEditPort2.IsEnabled = false;

			// update diagram
			DrawPayloadBay();
			return;
		}

		private void CbEnabledPort3_Checked(object sender, RoutedEventArgs e)
		{
			cmdEditPort3.IsEnabled = true;

			// update diagram
			DrawPayloadBay();
			return;
		}

		private void CbEnabledPort3_Unchecked(object sender, RoutedEventArgs e)
		{
			cmdEditPort3.IsEnabled = false;

			// update diagram
			DrawPayloadBay();
			return;
		}

		private void CbEnabledPort4_Checked(object sender, RoutedEventArgs e)
		{
			cmdEditPort4.IsEnabled = true;

			// update diagram
			DrawPayloadBay();
			return;
		}

		private void CbEnabledPort4_Unchecked(object sender, RoutedEventArgs e)
		{
			cmdEditPort4.IsEnabled = false;

			// update diagram
			DrawPayloadBay();
			return;
		}

		private void CbEnabledStbd1_Checked(object sender, RoutedEventArgs e)
		{
			cmdEditStbd1.IsEnabled = true;

			// update diagram
			DrawPayloadBay();
			return;
		}

		private void CbEnabledStbd1_Unchecked(object sender, RoutedEventArgs e)
		{
			cmdEditStbd1.IsEnabled = false;

			// update diagram
			DrawPayloadBay();
			return;
		}

		private void CbEnabledStbd2_Checked(object sender, RoutedEventArgs e)
		{
			cmdEditStbd2.IsEnabled = true;

			// update diagram
			DrawPayloadBay();
			return;
		}

		private void CbEnabledStbd2_Unchecked(object sender, RoutedEventArgs e)
		{
			cmdEditStbd2.IsEnabled = false;

			// update diagram
			DrawPayloadBay();
			return;
		}

		private void CbEnabledStbd3_Checked(object sender, RoutedEventArgs e)
		{
			cmdEditStbd3.IsEnabled = true;

			// update diagram
			DrawPayloadBay();
			return;
		}

		private void CbEnabledStbd3_Unchecked(object sender, RoutedEventArgs e)
		{
			cmdEditStbd3.IsEnabled = false;

			// update diagram
			DrawPayloadBay();
			return;
		}

		private void CbEnabledStbd4_Checked(object sender, RoutedEventArgs e)
		{
			cmdEditStbd4.IsEnabled = true;

			// update diagram
			DrawPayloadBay();
			return;
		}

		private void CbEnabledStbd4_Unchecked(object sender, RoutedEventArgs e)
		{
			cmdEditStbd4.IsEnabled = false;

			// update diagram
			DrawPayloadBay();
			return;
		}

		private void CbEnabledKeel1_Checked(object sender, RoutedEventArgs e)
		{
			cmdEditKeel1.IsEnabled = true;

			// update diagram
			DrawPayloadBay();
			return;
		}

		private void CbEnabledKeel1_Unchecked(object sender, RoutedEventArgs e)
		{
			cmdEditKeel1.IsEnabled = false;

			// update diagram
			DrawPayloadBay();
			return;
		}

		private void CbEnabledKeel2_Checked(object sender, RoutedEventArgs e)
		{
			cmdEditKeel2.IsEnabled = true;

			// update diagram
			DrawPayloadBay();
			return;
		}

		private void CbEnabledKeel2_Unchecked(object sender, RoutedEventArgs e)
		{
			cmdEditKeel2.IsEnabled = false;

			// update diagram
			DrawPayloadBay();
			return;
		}

		private void CbEnabledKeel3_Checked(object sender, RoutedEventArgs e)
		{
			cmdEditKeel3.IsEnabled = true;

			// update diagram
			DrawPayloadBay();
			return;
		}

		private void CbEnabledKeel3_Unchecked(object sender, RoutedEventArgs e)
		{
			cmdEditKeel3.IsEnabled = false;

			// update diagram
			DrawPayloadBay();
			return;
		}

		private void CbEnabledKeel4_Checked(object sender, RoutedEventArgs e)
		{
			cmdEditKeel4.IsEnabled = true;

			// update diagram
			DrawPayloadBay();
			return;
		}

		private void CbEnabledKeel4_Unchecked(object sender, RoutedEventArgs e)
		{
			cmdEditKeel4.IsEnabled = false;

			// update diagram
			DrawPayloadBay();
			return;
		}

		private void ShowEditLatch( int latch_idx, bool keel )
		{
			EditLatch editlatch = new EditLatch( DataContext, pl_idx, latch_idx, active, keel );
			editlatch.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
			editlatch.ShowDialog();

			// TODO handle attachment

			// update diagram
			DrawPayloadBay();
			return;
		}

		private void DrawPayloadBay()
		{
			const int gap = 1;
			const int ystbd = 10;
			const int ystbdpl = 5;
			const int ykeel = 135;
			const int ykeelpl = 130;
			const int yport = 260;
			const int yportpl = 255;
			const int height = 5;
			const int heightpl = 15;
			const int width = 5;
			int xpos = 20;// initial position
			int ypos;

			int[] LongeronPLIDs = active ? Defs.LONGERON_ACTIVE : Defs.LONGERON_PASSIVE;
			int[] KeelPLIDs = active ? Defs.KEEL_ACTIVE : Defs.KEEL_PASSIVE;

			// reset
			cnvPLB.Children.Clear();

			model.Mission msn = (model.Mission)DataContext;

			for (int plid = 154; plid <= 330; plid++)
			{
				bool usable = LongeronPLIDs.Contains( plid );
				Brush brsh = usable ? Brushes.DarkGray : Brushes.LightGray;

				// port
				Rectangle r = new Rectangle();
				r.Name = "p" + plid;
				r.ToolTip = plid;
				switch (GetPLIDType( plid, active ? msn.OV.PL_Active[pl_idx].Latches : msn.OV.PL_Passive[pl_idx].Latches, 0 ))
				{
					default:
					case 0:
						r.Stroke = brsh;
						r.Fill = brsh;
						r.Height = height;
						ypos = yport;
						break;
					case 1:
						r.Stroke = Brushes.LimeGreen;
						r.Fill = Brushes.LimeGreen;
						r.Height = heightpl;
						ypos = yportpl;
						break;
					case 2:
						r.Stroke = Brushes.Blue;
						r.Fill = Brushes.Blue;
						r.Height = heightpl;
						ypos = yportpl;
						break;
				}
				r.Width = width;
				cnvPLB.Children.Add( r );
				Canvas.SetTop( r, ypos );
				Canvas.SetLeft( r, xpos );

				// stbd
				r = new Rectangle();
				r.Name = "s" + plid;
				r.ToolTip = plid;
				switch (GetPLIDType( plid, active ? msn.OV.PL_Active[pl_idx].Latches : msn.OV.PL_Passive[pl_idx].Latches, 4 ))
				{
					case 0:
						r.Stroke = brsh;
						r.Fill = brsh;
						r.Height = height;
						ypos = ystbd;
						break;
					case 1:
						r.Stroke = Brushes.LimeGreen;
						r.Fill = Brushes.LimeGreen;
						r.Height = heightpl;
						ypos = ystbdpl;
						break;
					case 2:
						r.Stroke = Brushes.Blue;
						r.Fill = Brushes.Blue;
						r.Height = heightpl;
						ypos = ystbdpl;
						break;
				}
				r.Width = width;
				cnvPLB.Children.Add( r );
				Canvas.SetTop( r, ypos );
				Canvas.SetLeft( r, xpos );

				usable = KeelPLIDs.Contains( plid );
				brsh = usable ? Brushes.DarkGray : Brushes.LightGray;

				// keel
				if (plid <= 316)
				{
					r = new Rectangle();
					r.Name = "s" + plid;
					r.ToolTip = plid;
					switch (GetPLIDType( plid, active ? msn.OV.PL_Active[pl_idx].Latches : msn.OV.PL_Passive[pl_idx].Latches, 8 ))
					{
						case 0:
							r.Stroke = brsh;
							r.Fill = brsh;
							r.Height = height;
							ypos = ykeel;
							break;
						case 1:
							r.Stroke = Brushes.LimeGreen;
							r.Fill = Brushes.LimeGreen;
							r.Height = heightpl;
							ypos = ykeelpl;
							break;
						case 2:
							r.Stroke = Brushes.Blue;
							r.Fill = Brushes.Blue;
							r.Height = heightpl;
							ypos = ykeelpl;
							break;
					}
					r.Width = width;
					cnvPLB.Children.Add( r );
					Canvas.SetTop( r, ypos );
					Canvas.SetLeft( r, xpos );
				}

				xpos += gap + width;
			}

			// draw bay boundaries
			DrawLine( 61, ystbd, ykeel, yport );// bay 1/2
			DrawLine( 151, ystbd, ykeel, yport );// bay 2/3
			DrawLine( 235, ystbd, ykeel, yport );// bay 3/4
			DrawLine( 325, ystbd, ykeel, yport );// bay 4/5
			DrawLine( 409, ystbd, ykeel, yport );// bay 5/6
			DrawLine( 493, ystbd, ykeel, yport );// bay 6/7
			DrawLine( 589, ystbd, ykeel, yport );// bay 7/8
			DrawLine( 679, ystbd, ykeel, yport );// bay 8/9
			DrawLine( 757, ystbd, ykeel, yport );// bay 9/10
			DrawLine( 835, ystbd, ykeel, yport );// bay 10/11
			DrawLine( 919, ystbd, ykeel, yport );// bay 11/12
			DrawLine( 997, ystbd, ykeel, yport );// bay 12/13
			return;
		}

		private void DrawLine( int xpos, int ystbd, int ykeel, int yport )
		{
			Line ln = new Line
			{
				X1 = xpos,
				Y1 = ystbd + 10,
				X2 = xpos,
				Y2 = ykeel - 10,
				Stroke = Brushes.DimGray,
				StrokeThickness = 1,
				SnapsToDevicePixels = true
			};
			cnvPLB.Children.Add( ln );
			ln = new Line
			{
				X1 = xpos,
				Y1 = ykeel + 10,
				X2 = xpos,
				Y2 = yport - 10,
				Stroke = Brushes.Black,
				StrokeThickness = 1,
				SnapsToDevicePixels = true
			};
			cnvPLB.Children.Add( ln );
			return;
		}

		/**
		 * 0 = empty; 1 = PL regular; 2 = PL attachment 
		 **/
		private short GetPLIDType( int plid, model.Mission_PayloadLatch[] latches, short start_idx )
		{
			for (int i = 0; i < 4; i++)
			{
				if (plid == latches[i + start_idx].PLID)
				{
					if (latches[i + start_idx].IsAttachment) return 2;
					else return 1;
				}
			}
			return 0;
		}




		private bool active;
		private int pl_idx;
	}
}

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
		public EditLatches( object datacontext, bool active, string bindplid, string bindisattachment, string bindreversed, string bindlatch, string bindfwdguide, string bindaftguide )
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
			PLIDBindPath = bindplid;
			IsAttachmentBindPath = bindisattachment;
			ReversedBindPath = bindreversed;
			LatchBindPath = bindlatch;
			FwdGuideBindPath = bindfwdguide;
			AftGuideBindPath = bindaftguide;
			this.active = active;

			if (active)
			{
				DrawingTest( Defs.LONGERON_ACTIVE, Defs.KEEL_ACTIVE );

				// define bindings
				cbEnabledPort1.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[0]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_ACTIVE_Active()
				});
				cbEnabledPort2.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[1]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_ACTIVE_Active()
				});
				cbEnabledPort3.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[2]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_ACTIVE_Active()
				});
				cbEnabledPort4.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[3]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_ACTIVE_Active()
				});
				cbEnabledStbd1.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[4]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_ACTIVE_Active()
				});
				cbEnabledStbd2.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[5]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_ACTIVE_Active()
				});
				cbEnabledStbd3.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[6]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_ACTIVE_Active()
				});
				cbEnabledStbd4.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[7]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_ACTIVE_Active()
				});
				cbEnabledKeel1.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[8]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_KEEL_ACTIVE_Active()
				});
				cbEnabledKeel2.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[9]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_KEEL_ACTIVE_Active()
				});
				cbEnabledKeel3.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[10]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_KEEL_ACTIVE_Active()
				});
				cbEnabledKeel4.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[11]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_KEEL_ACTIVE_Active()
				});
			}
			else
			{
				DrawingTest( Defs.LONGERON_PASSIVE, Defs.KEEL_PASSIVE );

				
				// define bindings
				cbEnabledPort1.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[0]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_PASSIVE_Active()
				});
				cbEnabledPort2.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[1]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_PASSIVE_Active()
				});
				cbEnabledPort3.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[2]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_PASSIVE_Active()
				});
				cbEnabledPort4.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[3]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_PASSIVE_Active()
				});
				cbEnabledStbd1.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[4]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_PASSIVE_Active()
				});
				cbEnabledStbd2.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[5]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_PASSIVE_Active()
				});
				cbEnabledStbd3.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[6]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_PASSIVE_Active()
				});
				cbEnabledStbd4.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[7]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_PASSIVE_Active()
				});
				cbEnabledKeel1.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[8]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_KEEL_PASSIVE_Active()
				});
				cbEnabledKeel2.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[9]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_KEEL_PASSIVE_Active()
				});
				cbEnabledKeel3.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[10]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_KEEL_PASSIVE_Active()
				});
				cbEnabledKeel4.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[11]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_KEEL_PASSIVE_Active()
				});
			}
			return;
		}

		private void DrawingTest( int[] longeron, int[] keel )
		{
			const int gap = 1;
			const int yport = 5;
			const int ykeel = 130;
			const int ystbd = 255;
			const int height = 15;
			const int width = 5;
			int xpos = 20;// initial position

			for (int plid = 154; plid <= 330; plid++)
			{
				bool usable = longeron.Contains( plid );
				Brush brsh = usable ? Brushes.DarkGray : Brushes.LightGray;

				// port
				Rectangle r = new Rectangle();
				r.Name = "p" + plid;
				r.ToolTip = plid;
				r.Stroke = brsh;
				r.Fill = brsh;
				r.Height = height;
				r.Width = width;

				cnvPLB.Children.Add( r );
				Canvas.SetTop( r, yport );
				Canvas.SetLeft( r, xpos );

				// stbd
				r = new Rectangle();
				r.Name = "s" + plid;
				r.ToolTip = plid;
				r.Stroke = brsh;
				r.Fill = brsh;
				r.Height = height;
				r.Width = width;

				cnvPLB.Children.Add( r );
				Canvas.SetTop( r, ystbd );
				Canvas.SetLeft( r, xpos );

				usable = keel.Contains( plid );
				brsh = usable ? Brushes.DarkGray : Brushes.LightGray;

				// keel
				r = new Rectangle();
				r.Name = "s" + plid;
				r.ToolTip = plid;
				r.Stroke = brsh;
				r.Fill = brsh;
				r.Height = height;
				r.Width = width;

				cnvPLB.Children.Add( r );
				Canvas.SetTop( r, ykeel );
				Canvas.SetLeft( r, xpos );

				xpos += gap + width;
			}
			return;
		}

		private void CmdEditPort1_Click(object sender, RoutedEventArgs e)
		{
			ShowEditLatch( "[0]", false );
			return;
		}

		private void CmdEditPort2_Click(object sender, RoutedEventArgs e)
		{
			ShowEditLatch( "[1]", false );
			return;
		}

		private void CmdEditPort3_Click(object sender, RoutedEventArgs e)
		{
			ShowEditLatch( "[2]", false );
			return;
		}

		private void CmdEditPort4_Click(object sender, RoutedEventArgs e)
		{
			ShowEditLatch( "[3]", false );
			return;
		}

		private void CmdEditStbd1_Click(object sender, RoutedEventArgs e)
		{
			ShowEditLatch( "[4]", false );
			return;
		}

		private void CmdEditStbd2_Click(object sender, RoutedEventArgs e)
		{
			ShowEditLatch( "[5]", false );
			return;
		}

		private void CmdEditStbd3_Click(object sender, RoutedEventArgs e)
		{
			ShowEditLatch( "[6]", false );
			return;
		}

		private void CmdEditStbd4_Click(object sender, RoutedEventArgs e)
		{
			ShowEditLatch( "[7]", false );
			return;
		}

		private void CmdEditKeel1_Click(object sender, RoutedEventArgs e)
		{
			ShowEditLatch( "[8]", true );
			return;
		}

		private void CmdEditKeel2_Click(object sender, RoutedEventArgs e)
		{
			ShowEditLatch( "[9]", true );
			return;
		}

		private void CmdEditKeel3_Click(object sender, RoutedEventArgs e)
		{
			ShowEditLatch( "[10]", true );
			return;
		}

		private void CmdEditKeel4_Click(object sender, RoutedEventArgs e)
		{
			ShowEditLatch( "[11]", true );
			return;
		}

		private void ShowEditLatch( string LatchBind, bool keel )
		{
			string plid = PLIDBindPath + LatchBind;
			string isattachment = IsAttachmentBindPath + LatchBind;
			string reversed = ReversedBindPath + LatchBind;
			string latch = active ? (LatchBindPath + LatchBind) : "";
			string fwdguide = active ? (FwdGuideBindPath + LatchBind) : "";
			string aftguide = active ? (AftGuideBindPath + LatchBind) : "";

			EditLatch editlatch = new EditLatch( DataContext, active, keel, plid, isattachment, reversed, latch, fwdguide, aftguide );
			editlatch.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
			editlatch.ShowDialog();

			// TODO handle attachment

			// TODO update diagram
			return;
		}



		private string PLIDBindPath;
		private string IsAttachmentBindPath;
		private string ReversedBindPath;
		private string LatchBindPath;
		private string FwdGuideBindPath;
		private string AftGuideBindPath;
		private bool active;

		private void CbEnabledPort1_Checked(object sender, RoutedEventArgs e)
		{
			cmdEditPort1.IsEnabled = true;
			return;
		}

		private void CbEnabledPort1_Unchecked(object sender, RoutedEventArgs e)
		{
			cmdEditPort1.IsEnabled = false;
			return;
		}

		private void CbEnabledPort2_Checked(object sender, RoutedEventArgs e)
		{
			cmdEditPort2.IsEnabled = true;
			return;
		}

		private void CbEnabledPort2_Unchecked(object sender, RoutedEventArgs e)
		{
			cmdEditPort2.IsEnabled = false;
			return;
		}

		private void CbEnabledPort3_Checked(object sender, RoutedEventArgs e)
		{
			cmdEditPort3.IsEnabled = true;
			return;
		}

		private void CbEnabledPort3_Unchecked(object sender, RoutedEventArgs e)
		{
			cmdEditPort3.IsEnabled = false;
			return;
		}

		private void CbEnabledPort4_Checked(object sender, RoutedEventArgs e)
		{
			cmdEditPort4.IsEnabled = true;
			return;
		}

		private void CbEnabledPort4_Unchecked(object sender, RoutedEventArgs e)
		{
			cmdEditPort4.IsEnabled = false;
			return;
		}

		private void CbEnabledStbd1_Checked(object sender, RoutedEventArgs e)
		{
			cmdEditStbd1.IsEnabled = true;
			return;
		}

		private void CbEnabledStbd1_Unchecked(object sender, RoutedEventArgs e)
		{
			cmdEditStbd1.IsEnabled = false;
			return;
		}

		private void CbEnabledStbd2_Checked(object sender, RoutedEventArgs e)
		{
			cmdEditStbd2.IsEnabled = true;
			return;
		}

		private void CbEnabledStbd2_Unchecked(object sender, RoutedEventArgs e)
		{
			cmdEditStbd2.IsEnabled = false;
			return;
		}

		private void CbEnabledStbd3_Checked(object sender, RoutedEventArgs e)
		{
			cmdEditStbd3.IsEnabled = true;
			return;
		}

		private void CbEnabledStbd3_Unchecked(object sender, RoutedEventArgs e)
		{
			cmdEditStbd3.IsEnabled = false;
			return;
		}

		private void CbEnabledStbd4_Checked(object sender, RoutedEventArgs e)
		{
			cmdEditStbd4.IsEnabled = true;
			return;
		}

		private void CbEnabledStbd4_Unchecked(object sender, RoutedEventArgs e)
		{
			cmdEditStbd4.IsEnabled = false;
			return;
		}

		private void CbEnabledKeel1_Checked(object sender, RoutedEventArgs e)
		{
			cmdEditKeel1.IsEnabled = true;
			return;
		}

		private void CbEnabledKeel1_Unchecked(object sender, RoutedEventArgs e)
		{
			cmdEditKeel1.IsEnabled = false;
			return;
		}

		private void CbEnabledKeel2_Checked(object sender, RoutedEventArgs e)
		{
			cmdEditKeel2.IsEnabled = true;
			return;
		}

		private void CbEnabledKeel2_Unchecked(object sender, RoutedEventArgs e)
		{
			cmdEditKeel2.IsEnabled = false;
			return;
		}

		private void CbEnabledKeel3_Checked(object sender, RoutedEventArgs e)
		{
			cmdEditKeel3.IsEnabled = true;
			return;
		}

		private void CbEnabledKeel3_Unchecked(object sender, RoutedEventArgs e)
		{
			cmdEditKeel3.IsEnabled = false;
			return;
		}

		private void CbEnabledKeel4_Checked(object sender, RoutedEventArgs e)
		{
			cmdEditKeel4.IsEnabled = true;
			return;
		}

		private void CbEnabledKeel4_Unchecked(object sender, RoutedEventArgs e)
		{
			cmdEditKeel4.IsEnabled = false;
			return;
		}
	}
}

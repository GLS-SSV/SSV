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


namespace SSVMissionEditor
{
	public class Convert_PLID_LONGERON_ACTIVE : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// model to viewer
			if ((int)value == 0) return 0;
			else
			{
				int i = Array.FindIndex( Defs.LONGERON_ACTIVE, item => item == (int)value );
				return i + 1;
			}
		}

		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// viewer to model
			if ((int)value == 0) return 0;
			else return Defs.LONGERON_ACTIVE[(int)value - 1];
		}
	}

	public class Convert_PLID_LONGERON_PASSIVE : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// model to viewer
			if ((int)value == 0) return 0;
			else
			{
				int i = Array.FindIndex( Defs.LONGERON_PASSIVE, item => item == (int)value );
				return i + 1;
			}
		}

		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// viewer to model
			if ((int)value == 0) return 0;
			else return Defs.LONGERON_PASSIVE[(int)value - 1];
		}
	}

	public class Convert_PLID_KEEL_ACTIVE : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// model to viewer
			if ((int)value == 0) return 0;
			else
			{
				int i = Array.FindIndex( Defs.KEEL_ACTIVE, item => item == (int)value );
				return i + 1;
			}
		}

		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// viewer to model
			if ((int)value == 0) return 0;
			else return Defs.KEEL_ACTIVE[(int)value - 1];
		}
	}

	public class Convert_PLID_KEEL_PASSIVE : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// model to viewer
			if ((int)value == 0) return 0;
			else
			{
				int i = Array.FindIndex( Defs.KEEL_PASSIVE, item => item == (int)value );
				return i + 1;
			}
		}

		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// viewer to model
			if ((int)value == 0) return 0;
			else return Defs.KEEL_PASSIVE[(int)value - 1];
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

			DataContext = datacontext;

			// load "latch not used" into comboboxes
			cmbPLIDPort1.Items.Add( "N/A" );
			cmbPLIDPort2.Items.Add( "N/A" );
			cmbPLIDPort3.Items.Add( "N/A" );
			cmbPLIDPort4.Items.Add( "N/A" );
			cmbPLIDStbd1.Items.Add( "N/A" );
			cmbPLIDStbd2.Items.Add( "N/A" );
			cmbPLIDStbd3.Items.Add( "N/A" );
			cmbPLIDStbd4.Items.Add( "N/A" );
			cmbPLIDKeel1.Items.Add( "N/A" );
			cmbPLIDKeel2.Items.Add( "N/A" );
			cmbPLIDKeel3.Items.Add( "N/A" );
			cmbPLIDKeel4.Items.Add( "N/A" );

			if (active)
			{
				// load PLIDs into comboboxes
				foreach (int x in Defs.LONGERON_ACTIVE)
				{
					cmbPLIDPort1.Items.Add( x + " Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] );
					cmbPLIDPort2.Items.Add( x + " Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] );
					cmbPLIDPort3.Items.Add( x + " Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] );
					cmbPLIDPort4.Items.Add( x + " Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] );
					cmbPLIDStbd1.Items.Add( x + " Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] );
					cmbPLIDStbd2.Items.Add( x + " Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] );
					cmbPLIDStbd3.Items.Add( x + " Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] );
					cmbPLIDStbd4.Items.Add( x + " Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] );
				}

				foreach (int x in Defs.KEEL_ACTIVE)
				{
					cmbPLIDKeel1.Items.Add( x + " Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] );
					cmbPLIDKeel2.Items.Add( x + " Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] );
					cmbPLIDKeel3.Items.Add( x + " Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] );
					cmbPLIDKeel4.Items.Add( x + " Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] );
				}


				// define bindings
				cmbLatchPort1.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindlatch + "[0]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
				});
				cmbLatchPort2.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindlatch + "[1]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
				});
				cmbLatchPort3.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindlatch + "[2]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
				});
				cmbLatchPort4.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindlatch + "[3]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
				});
				cmbLatchStbd1.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindlatch + "[4]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
				});
				cmbLatchStbd2.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindlatch + "[5]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
				});
				cmbLatchStbd3.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindlatch + "[6]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
				});
				cmbLatchStbd4.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindlatch + "[7]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
				});
				cmbLatchKeel1.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindlatch + "[8]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
				});
				cmbLatchKeel2.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindlatch + "[9]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
				});
				cmbLatchKeel3.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindlatch + "[10]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
				});
				cmbLatchKeel4.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindlatch + "[11]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
				});

				cmbFwdGuidesPort1.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindfwdguide + "[0]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
				});
				cmbFwdGuidesPort2.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindfwdguide + "[1]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
				});
				cmbFwdGuidesPort3.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindfwdguide + "[2]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
				});
				cmbFwdGuidesPort4.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindfwdguide + "[3]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
				});
				cmbFwdGuidesStbd1.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindfwdguide + "[4]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
				});
				cmbFwdGuidesStbd2.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindfwdguide + "[5]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
				});
				cmbFwdGuidesStbd3.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindfwdguide + "[6]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
				});
				cmbFwdGuidesStbd4.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindfwdguide + "[7]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
				});

				cmbAftGuidesPort1.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindaftguide + "[0]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
				});
				cmbAftGuidesPort2.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindaftguide + "[1]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
				});
				cmbAftGuidesPort3.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindaftguide + "[2]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
				});
				cmbAftGuidesPort4.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindaftguide + "[3]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
				});
				cmbAftGuidesStbd1.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindaftguide + "[4]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
				});
				cmbAftGuidesStbd2.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindaftguide + "[5]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
				});
				cmbAftGuidesStbd3.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindaftguide + "[6]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
				});
				cmbAftGuidesStbd4.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindaftguide + "[7]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
				});

				cmbPLIDPort1.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[0]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_ACTIVE()
				});
				cmbPLIDPort2.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[1]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_ACTIVE()
				});
				cmbPLIDPort3.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[2]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_ACTIVE()
				});
				cmbPLIDPort4.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[3]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_ACTIVE()
				});
				cmbPLIDStbd1.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[4]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_ACTIVE()
				});
				cmbPLIDStbd2.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[5]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_ACTIVE()
				});
				cmbPLIDStbd3.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[6]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_ACTIVE()
				});
				cmbPLIDStbd4.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[7]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_ACTIVE()
				});
				cmbPLIDKeel1.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[8]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_KEEL_ACTIVE()
				});
				cmbPLIDKeel2.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[9]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_KEEL_ACTIVE()
				});
				cmbPLIDKeel3.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[10]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_KEEL_ACTIVE()
				});
				cmbPLIDKeel4.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[11]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_KEEL_ACTIVE()
				});
			}
			else
			{
				// load PLIDs into comboboxes
				foreach (int x in Defs.LONGERON_PASSIVE)
				{
					cmbPLIDPort1.Items.Add( x + " Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] );
					cmbPLIDPort2.Items.Add( x + " Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] );
					cmbPLIDPort3.Items.Add( x + " Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] );
					cmbPLIDPort4.Items.Add( x + " Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] );
					cmbPLIDStbd1.Items.Add( x + " Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] );
					cmbPLIDStbd2.Items.Add( x + " Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] );
					cmbPLIDStbd3.Items.Add( x + " Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] );
					cmbPLIDStbd4.Items.Add( x + " Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] );
				}

				foreach (int x in Defs.KEEL_PASSIVE)
				{
					cmbPLIDKeel1.Items.Add( x + " Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] );
					cmbPLIDKeel2.Items.Add( x + " Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] );
					cmbPLIDKeel3.Items.Add( x + " Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] );
					cmbPLIDKeel4.Items.Add( x + " Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] );
				}


				// hide uneeded controls
				lblLatchPort.Visibility = Visibility.Hidden;
				lblGuidesPort.Visibility = Visibility.Hidden;
				cmbLatchPort1.Visibility = Visibility.Hidden;
				cmbFwdGuidesPort1.Visibility = Visibility.Hidden;
				cmbAftGuidesPort1.Visibility = Visibility.Hidden;
				cmbLatchPort2.Visibility = Visibility.Hidden;
				cmbFwdGuidesPort2.Visibility = Visibility.Hidden;
				cmbAftGuidesPort2.Visibility = Visibility.Hidden;
				cmbLatchPort3.Visibility = Visibility.Hidden;
				cmbFwdGuidesPort3.Visibility = Visibility.Hidden;
				cmbAftGuidesPort3.Visibility = Visibility.Hidden;
				cmbLatchPort4.Visibility = Visibility.Hidden;
				cmbFwdGuidesPort4.Visibility = Visibility.Hidden;
				cmbAftGuidesPort4.Visibility = Visibility.Hidden;

				lblLatchStbd.Visibility = Visibility.Hidden;
				lblGuidesStbd.Visibility = Visibility.Hidden;
				cmbLatchStbd1.Visibility = Visibility.Hidden;
				cmbFwdGuidesStbd1.Visibility = Visibility.Hidden;
				cmbAftGuidesStbd1.Visibility = Visibility.Hidden;
				cmbLatchStbd2.Visibility = Visibility.Hidden;
				cmbFwdGuidesStbd2.Visibility = Visibility.Hidden;
				cmbAftGuidesStbd2.Visibility = Visibility.Hidden;
				cmbLatchStbd3.Visibility = Visibility.Hidden;
				cmbFwdGuidesStbd3.Visibility = Visibility.Hidden;
				cmbAftGuidesStbd3.Visibility = Visibility.Hidden;
				cmbLatchStbd4.Visibility = Visibility.Hidden;
				cmbFwdGuidesStbd4.Visibility = Visibility.Hidden;
				cmbAftGuidesStbd4.Visibility = Visibility.Hidden;

				lblLatchKeel.Visibility = Visibility.Hidden;
				cmbLatchKeel1.Visibility = Visibility.Hidden;
				cmbLatchKeel2.Visibility = Visibility.Hidden;
				cmbLatchKeel3.Visibility = Visibility.Hidden;
				cmbLatchKeel4.Visibility = Visibility.Hidden;


				// define bindings
				cmbPLIDPort1.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[0]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_PASSIVE()
				});
				cmbPLIDPort2.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[1]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_PASSIVE()
				});
				cmbPLIDPort3.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[2]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_PASSIVE()
				});
				cmbPLIDPort4.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[3]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_PASSIVE()
				});
				cmbPLIDStbd1.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[4]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_PASSIVE()
				});
				cmbPLIDStbd2.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[5]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_PASSIVE()
				});
				cmbPLIDStbd3.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[6]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_PASSIVE()
				});
				cmbPLIDStbd4.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[7]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_LONGERON_PASSIVE()
				});
				cmbPLIDKeel1.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[8]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_KEEL_PASSIVE()
				});
				cmbPLIDKeel2.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[9]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_KEEL_PASSIVE()
				});
				cmbPLIDKeel3.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[10]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_KEEL_PASSIVE()
				});
				cmbPLIDKeel4.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid + "[11]" ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_KEEL_PASSIVE()
				});
			}

			cbAttachmentPort1.SetBinding( CheckBox.IsCheckedProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bindisattachment + "[0]" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			cbAttachmentPort2.SetBinding( CheckBox.IsCheckedProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bindisattachment + "[1]" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			cbAttachmentPort3.SetBinding( CheckBox.IsCheckedProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bindisattachment + "[2]" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			cbAttachmentPort4.SetBinding( CheckBox.IsCheckedProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bindisattachment + "[3]" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			cbAttachmentStbd1.SetBinding( CheckBox.IsCheckedProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bindisattachment + "[4]" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			cbAttachmentStbd2.SetBinding( CheckBox.IsCheckedProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bindisattachment + "[5]" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			cbAttachmentStbd3.SetBinding( CheckBox.IsCheckedProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bindisattachment + "[6]" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			cbAttachmentStbd4.SetBinding( CheckBox.IsCheckedProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bindisattachment + "[7]" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			cbAttachmentKeel1.SetBinding( CheckBox.IsCheckedProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bindisattachment + "[8]" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			cbAttachmentKeel2.SetBinding( CheckBox.IsCheckedProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bindisattachment + "[9]" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			cbAttachmentKeel3.SetBinding( CheckBox.IsCheckedProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bindisattachment + "[10]" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			cbAttachmentKeel4.SetBinding( CheckBox.IsCheckedProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bindisattachment + "[11]" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});

			cbReversedPort1.SetBinding( CheckBox.IsCheckedProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bindreversed + "[0]" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			cbReversedPort2.SetBinding( CheckBox.IsCheckedProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bindreversed + "[1]" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			cbReversedPort3.SetBinding( CheckBox.IsCheckedProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bindreversed + "[2]" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			cbReversedPort4.SetBinding( CheckBox.IsCheckedProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bindreversed + "[3]" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			cbReversedStbd1.SetBinding( CheckBox.IsCheckedProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bindreversed + "[4]" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			cbReversedStbd2.SetBinding( CheckBox.IsCheckedProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bindreversed + "[5]" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			cbReversedStbd3.SetBinding( CheckBox.IsCheckedProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bindreversed + "[6]" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			cbReversedStbd4.SetBinding( CheckBox.IsCheckedProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bindreversed + "[7]" ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
			return;
		}

		private void cbAttachmentPort1_Checked(object sender, RoutedEventArgs e)
		{
			cbAttachmentPort2.IsChecked = false;
			cbAttachmentPort3.IsChecked = false;
			cbAttachmentPort4.IsChecked = false;
			cbAttachmentStbd1.IsChecked = false;
			cbAttachmentStbd2.IsChecked = false;
			cbAttachmentStbd3.IsChecked = false;
			cbAttachmentStbd4.IsChecked = false;
			cbAttachmentKeel1.IsChecked = false;
			cbAttachmentKeel2.IsChecked = false;
			cbAttachmentKeel3.IsChecked = false;
			cbAttachmentKeel4.IsChecked = false;
			return;
		}

		private void cbAttachmentPort2_Checked(object sender, RoutedEventArgs e)
		{
			cbAttachmentPort1.IsChecked = false;
			cbAttachmentPort3.IsChecked = false;
			cbAttachmentPort4.IsChecked = false;
			cbAttachmentStbd1.IsChecked = false;
			cbAttachmentStbd2.IsChecked = false;
			cbAttachmentStbd3.IsChecked = false;
			cbAttachmentStbd4.IsChecked = false;
			cbAttachmentKeel1.IsChecked = false;
			cbAttachmentKeel2.IsChecked = false;
			cbAttachmentKeel3.IsChecked = false;
			cbAttachmentKeel4.IsChecked = false;
			return;
		}

		private void cbAttachmentPort3_Checked(object sender, RoutedEventArgs e)
		{
			cbAttachmentPort1.IsChecked = false;
			cbAttachmentPort2.IsChecked = false;
			cbAttachmentPort4.IsChecked = false;
			cbAttachmentStbd1.IsChecked = false;
			cbAttachmentStbd2.IsChecked = false;
			cbAttachmentStbd3.IsChecked = false;
			cbAttachmentStbd4.IsChecked = false;
			cbAttachmentKeel1.IsChecked = false;
			cbAttachmentKeel2.IsChecked = false;
			cbAttachmentKeel3.IsChecked = false;
			cbAttachmentKeel4.IsChecked = false;
			return;
		}

		private void cbAttachmentPort4_Checked(object sender, RoutedEventArgs e)
		{
			cbAttachmentPort1.IsChecked = false;
			cbAttachmentPort2.IsChecked = false;
			cbAttachmentPort3.IsChecked = false;
			cbAttachmentStbd1.IsChecked = false;
			cbAttachmentStbd2.IsChecked = false;
			cbAttachmentStbd3.IsChecked = false;
			cbAttachmentStbd4.IsChecked = false;
			cbAttachmentKeel1.IsChecked = false;
			cbAttachmentKeel2.IsChecked = false;
			cbAttachmentKeel3.IsChecked = false;
			cbAttachmentKeel4.IsChecked = false;
			return;
		}

		private void cbAttachmentStbd1_Checked(object sender, RoutedEventArgs e)
		{
			cbAttachmentPort1.IsChecked = false;
			cbAttachmentPort2.IsChecked = false;
			cbAttachmentPort3.IsChecked = false;
			cbAttachmentPort4.IsChecked = false;
			cbAttachmentStbd2.IsChecked = false;
			cbAttachmentStbd3.IsChecked = false;
			cbAttachmentStbd4.IsChecked = false;
			cbAttachmentKeel1.IsChecked = false;
			cbAttachmentKeel2.IsChecked = false;
			cbAttachmentKeel3.IsChecked = false;
			cbAttachmentKeel4.IsChecked = false;
			return;
		}

		private void cbAttachmentStbd2_Checked(object sender, RoutedEventArgs e)
		{
			cbAttachmentPort1.IsChecked = false;
			cbAttachmentPort2.IsChecked = false;
			cbAttachmentPort3.IsChecked = false;
			cbAttachmentPort4.IsChecked = false;
			cbAttachmentStbd1.IsChecked = false;
			cbAttachmentStbd3.IsChecked = false;
			cbAttachmentStbd4.IsChecked = false;
			cbAttachmentKeel1.IsChecked = false;
			cbAttachmentKeel2.IsChecked = false;
			cbAttachmentKeel3.IsChecked = false;
			cbAttachmentKeel4.IsChecked = false;
			return;
		}

		private void cbAttachmentStbd3_Checked(object sender, RoutedEventArgs e)
		{
			cbAttachmentPort1.IsChecked = false;
			cbAttachmentPort2.IsChecked = false;
			cbAttachmentPort3.IsChecked = false;
			cbAttachmentPort4.IsChecked = false;
			cbAttachmentStbd1.IsChecked = false;
			cbAttachmentStbd2.IsChecked = false;
			cbAttachmentStbd4.IsChecked = false;
			cbAttachmentKeel1.IsChecked = false;
			cbAttachmentKeel2.IsChecked = false;
			cbAttachmentKeel3.IsChecked = false;
			cbAttachmentKeel4.IsChecked = false;
			return;
		}

		private void cbAttachmentStbd4_Checked(object sender, RoutedEventArgs e)
		{
			cbAttachmentPort1.IsChecked = false;
			cbAttachmentPort2.IsChecked = false;
			cbAttachmentPort3.IsChecked = false;
			cbAttachmentPort4.IsChecked = false;
			cbAttachmentStbd1.IsChecked = false;
			cbAttachmentStbd2.IsChecked = false;
			cbAttachmentStbd3.IsChecked = false;
			cbAttachmentKeel1.IsChecked = false;
			cbAttachmentKeel2.IsChecked = false;
			cbAttachmentKeel3.IsChecked = false;
			cbAttachmentKeel4.IsChecked = false;
			return;
		}

		private void cbAttachmentKeel1_Checked(object sender, RoutedEventArgs e)
		{
			cbAttachmentPort1.IsChecked = false;
			cbAttachmentPort2.IsChecked = false;
			cbAttachmentPort3.IsChecked = false;
			cbAttachmentPort4.IsChecked = false;
			cbAttachmentStbd1.IsChecked = false;
			cbAttachmentStbd2.IsChecked = false;
			cbAttachmentStbd3.IsChecked = false;
			cbAttachmentStbd4.IsChecked = false;
			cbAttachmentKeel2.IsChecked = false;
			cbAttachmentKeel3.IsChecked = false;
			cbAttachmentKeel4.IsChecked = false;
			return;
		}

		private void cbAttachmentKeel2_Checked(object sender, RoutedEventArgs e)
		{
			cbAttachmentPort1.IsChecked = false;
			cbAttachmentPort2.IsChecked = false;
			cbAttachmentPort3.IsChecked = false;
			cbAttachmentPort4.IsChecked = false;
			cbAttachmentStbd1.IsChecked = false;
			cbAttachmentStbd2.IsChecked = false;
			cbAttachmentStbd3.IsChecked = false;
			cbAttachmentStbd4.IsChecked = false;
			cbAttachmentKeel1.IsChecked = false;
			cbAttachmentKeel3.IsChecked = false;
			cbAttachmentKeel4.IsChecked = false;
			return;
		}

		private void cbAttachmentKeel3_Checked(object sender, RoutedEventArgs e)
		{
			cbAttachmentPort1.IsChecked = false;
			cbAttachmentPort2.IsChecked = false;
			cbAttachmentPort3.IsChecked = false;
			cbAttachmentPort4.IsChecked = false;
			cbAttachmentStbd1.IsChecked = false;
			cbAttachmentStbd2.IsChecked = false;
			cbAttachmentStbd3.IsChecked = false;
			cbAttachmentStbd4.IsChecked = false;
			cbAttachmentKeel1.IsChecked = false;
			cbAttachmentKeel2.IsChecked = false;
			cbAttachmentKeel4.IsChecked = false;
			return;
		}

		private void cbAttachmentKeel4_Checked(object sender, RoutedEventArgs e)
		{
			cbAttachmentPort1.IsChecked = false;
			cbAttachmentPort2.IsChecked = false;
			cbAttachmentPort3.IsChecked = false;
			cbAttachmentPort4.IsChecked = false;
			cbAttachmentStbd1.IsChecked = false;
			cbAttachmentStbd2.IsChecked = false;
			cbAttachmentStbd3.IsChecked = false;
			cbAttachmentStbd4.IsChecked = false;
			cbAttachmentKeel1.IsChecked = false;
			cbAttachmentKeel2.IsChecked = false;
			cbAttachmentKeel3.IsChecked = false;
			return;
		}


		private void cbAttachmentPort1_Click(object sender, RoutedEventArgs e)
		{
			if (cbAttachmentPort1.IsChecked == false) cbAttachmentPort1.IsChecked = true;
			return;
		}

		private void cbAttachmentPort2_Click(object sender, RoutedEventArgs e)
		{
			if (cbAttachmentPort2.IsChecked == false) cbAttachmentPort2.IsChecked = true;
			return;
		}

		private void cbAttachmentPort3_Click(object sender, RoutedEventArgs e)
		{
			if (cbAttachmentPort3.IsChecked == false) cbAttachmentPort3.IsChecked = true;
			return;
		}

		private void cbAttachmentPort4_Click(object sender, RoutedEventArgs e)
		{
			if (cbAttachmentPort4.IsChecked == false) cbAttachmentPort4.IsChecked = true;
			return;
		}

		private void cbAttachmentStbd1_Click(object sender, RoutedEventArgs e)
		{
			if (cbAttachmentStbd1.IsChecked == false) cbAttachmentStbd1.IsChecked = true;
			return;
		}

		private void cbAttachmentStbd2_Click(object sender, RoutedEventArgs e)
		{
			if (cbAttachmentStbd2.IsChecked == false) cbAttachmentStbd2.IsChecked = true;
			return;
		}

		private void cbAttachmentStbd3_Click(object sender, RoutedEventArgs e)
		{
			if (cbAttachmentStbd3.IsChecked == false) cbAttachmentStbd3.IsChecked = true;
			return;
		}

		private void cbAttachmentStbd4_Click(object sender, RoutedEventArgs e)
		{
			if (cbAttachmentStbd4.IsChecked == false) cbAttachmentStbd4.IsChecked = true;
			return;
		}

		private void cbAttachmentKeel1_Click(object sender, RoutedEventArgs e)
		{
			if (cbAttachmentKeel1.IsChecked == false) cbAttachmentKeel1.IsChecked = true;
			return;
		}

		private void cbAttachmentKeel2_Click(object sender, RoutedEventArgs e)
		{
			if (cbAttachmentKeel2.IsChecked == false) cbAttachmentKeel2.IsChecked = true;
			return;
		}

		private void cbAttachmentKeel3_Click(object sender, RoutedEventArgs e)
		{
			if (cbAttachmentKeel3.IsChecked == false) cbAttachmentKeel3.IsChecked = true;
			return;
		}

		private void cbAttachmentKeel4_Click(object sender, RoutedEventArgs e)
		{
			if (cbAttachmentKeel4.IsChecked == false) cbAttachmentKeel4.IsChecked = true;
			return;
		}

		private void cmbPLIDPort1_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			if (cmbPLIDPort1.SelectedIndex == 0)
			{
				cbAttachmentPort1.IsEnabled = false;
				cbReversedPort1.IsEnabled = false;
				cmbLatchPort1.IsEnabled = false;
				cmbFwdGuidesPort1.IsEnabled = false;
				cmbAftGuidesPort1.IsEnabled = false;
			}
			else
			{
				cbAttachmentPort1.IsEnabled = true;
				cbReversedPort1.IsEnabled = true;
				cmbLatchPort1.IsEnabled = true;
				cmbFwdGuidesPort1.IsEnabled = true;
				cmbAftGuidesPort1.IsEnabled = true;
			}
			return;
		}

		private void cmbPLIDPort2_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			if (cmbPLIDPort2.SelectedIndex == 0)
			{
				cbAttachmentPort2.IsEnabled = false;
				cbReversedPort2.IsEnabled = false;
				cmbLatchPort2.IsEnabled = false;
				cmbFwdGuidesPort2.IsEnabled = false;
				cmbAftGuidesPort2.IsEnabled = false;
			}
			else
			{
				cbAttachmentPort2.IsEnabled = true;
				cbReversedPort2.IsEnabled = true;
				cmbLatchPort2.IsEnabled = true;
				cmbFwdGuidesPort2.IsEnabled = true;
				cmbAftGuidesPort2.IsEnabled = true;
			}
			return;
		}

		private void cmbPLIDPort3_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			if (cmbPLIDPort3.SelectedIndex == 0)
			{
				cbAttachmentPort3.IsEnabled = false;
				cbReversedPort3.IsEnabled = false;
				cmbLatchPort3.IsEnabled = false;
				cmbFwdGuidesPort3.IsEnabled = false;
				cmbAftGuidesPort3.IsEnabled = false;
			}
			else
			{
				cbAttachmentPort3.IsEnabled = true;
				cbReversedPort3.IsEnabled = true;
				cmbLatchPort3.IsEnabled = true;
				cmbFwdGuidesPort3.IsEnabled = true;
				cmbAftGuidesPort3.IsEnabled = true;
			}
			return;
		}

		private void cmbPLIDPort4_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			if (cmbPLIDPort4.SelectedIndex == 0)
			{
				cbAttachmentPort4.IsEnabled = false;
				cbReversedPort4.IsEnabled = false;
				cmbLatchPort4.IsEnabled = false;
				cmbFwdGuidesPort4.IsEnabled = false;
				cmbAftGuidesPort4.IsEnabled = false;
			}
			else
			{
				cbAttachmentPort4.IsEnabled = true;
				cbReversedPort4.IsEnabled = true;
				cmbLatchPort4.IsEnabled = true;
				cmbFwdGuidesPort4.IsEnabled = true;
				cmbAftGuidesPort4.IsEnabled = true;
			}
			return;
		}

		private void cmbPLIDStbd1_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			if (cmbPLIDStbd1.SelectedIndex == 0)
			{
				cbAttachmentStbd1.IsEnabled = false;
				cbReversedStbd1.IsEnabled = false;
				cmbLatchStbd1.IsEnabled = false;
				cmbFwdGuidesStbd1.IsEnabled = false;
				cmbAftGuidesStbd1.IsEnabled = false;
			}
			else
			{
				cbAttachmentStbd1.IsEnabled = true;
				cbReversedStbd1.IsEnabled = true;
				cmbLatchStbd1.IsEnabled = true;
				cmbFwdGuidesStbd1.IsEnabled = true;
				cmbAftGuidesStbd1.IsEnabled = true;
			}
			return;
		}

		private void cmbPLIDStbd2_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			if (cmbPLIDStbd2.SelectedIndex == 0)
			{
				cbAttachmentStbd2.IsEnabled = false;
				cbReversedStbd2.IsEnabled = false;
				cmbLatchStbd2.IsEnabled = false;
				cmbFwdGuidesStbd2.IsEnabled = false;
				cmbAftGuidesStbd2.IsEnabled = false;
			}
			else
			{
				cbAttachmentStbd2.IsEnabled = true;
				cbReversedStbd2.IsEnabled = true;
				cmbLatchStbd2.IsEnabled = true;
				cmbFwdGuidesStbd2.IsEnabled = true;
				cmbAftGuidesStbd2.IsEnabled = true;
			}
			return;
		}

		private void cmbPLIDStbd3_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			if (cmbPLIDStbd3.SelectedIndex == 0)
			{
				cbAttachmentStbd3.IsEnabled = false;
				cbReversedStbd3.IsEnabled = false;
				cmbLatchStbd3.IsEnabled = false;
				cmbFwdGuidesStbd3.IsEnabled = false;
				cmbAftGuidesStbd3.IsEnabled = false;
			}
			else
			{
				cbAttachmentStbd3.IsEnabled = true;
				cbReversedStbd3.IsEnabled = true;
				cmbLatchStbd3.IsEnabled = true;
				cmbFwdGuidesStbd3.IsEnabled = true;
				cmbAftGuidesStbd3.IsEnabled = true;
			}
			return;
		}

		private void cmbPLIDStbd4_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			if (cmbPLIDStbd4.SelectedIndex == 0)
			{
				cbAttachmentStbd4.IsEnabled = false;
				cbReversedStbd4.IsEnabled = false;
				cmbLatchStbd4.IsEnabled = false;
				cmbFwdGuidesStbd4.IsEnabled = false;
				cmbAftGuidesStbd4.IsEnabled = false;
			}
			else
			{
				cbAttachmentStbd4.IsEnabled = true;
				cbReversedStbd4.IsEnabled = true;
				cmbLatchStbd4.IsEnabled = true;
				cmbFwdGuidesStbd4.IsEnabled = true;
				cmbAftGuidesStbd4.IsEnabled = true;
			}
			return;
		}

		private void cmbPLIDKeel1_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			if (cmbPLIDKeel1.SelectedIndex == 0)
			{
				cbAttachmentKeel1.IsEnabled = false;
				cmbLatchKeel1.IsEnabled = false;
			}
			else
			{
				cbAttachmentKeel1.IsEnabled = true;
				cmbLatchKeel1.IsEnabled = true;
			}
			return;
		}

		private void cmbPLIDKeel2_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			if (cmbPLIDKeel2.SelectedIndex == 0)
			{
				cbAttachmentKeel2.IsEnabled = false;
				cmbLatchKeel2.IsEnabled = false;
			}
			else
			{
				cbAttachmentKeel2.IsEnabled = true;
				cmbLatchKeel2.IsEnabled = true;
			}
			return;
		}

		private void cmbPLIDKeel3_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			if (cmbPLIDKeel3.SelectedIndex == 0)
			{
				cbAttachmentKeel3.IsEnabled = false;
				cmbLatchKeel3.IsEnabled = false;
			}
			else
			{
				cbAttachmentKeel3.IsEnabled = true;
				cmbLatchKeel3.IsEnabled = true;
			}
			return;
		}

		private void cmbPLIDKeel4_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			if (cmbPLIDKeel4.SelectedIndex == 0)
			{
				cbAttachmentKeel4.IsEnabled = false;
				cmbLatchKeel4.IsEnabled = false;
			}
			else
			{
				cbAttachmentKeel4.IsEnabled = true;
				cmbLatchKeel4.IsEnabled = true;
			}
			return;
		}
	}
}

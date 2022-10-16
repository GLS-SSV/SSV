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
				return i;
			}
		}

		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// viewer to model
			if ((int)value == 0) return 0;
			else return Defs.LONGERON_ACTIVE[(int)value];
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
				return i;
			}
		}

		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// viewer to model
			if ((int)value == 0) return 0;
			else return Defs.LONGERON_PASSIVE[(int)value];
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
				return i;
			}
		}

		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// viewer to model
			if ((int)value == 0) return 0;
			else return Defs.KEEL_ACTIVE[(int)value];
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
				return i;
			}
		}

		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// viewer to model
			if ((int)value == 0) return 0;
			else return Defs.KEEL_PASSIVE[(int)value];
		}
	}

	/// <summary>
	/// Interaction logic for EditLatch.xaml
	/// </summary>
	public partial class EditLatch : Window
	{
		public EditLatch( object datacontext, bool active, bool keel, string bindplid, string bindisattachment, string bindreversed, string bindlatch, string bindfwdguide, string bindaftguide )
		{
			InitializeComponent();

			DataContext = datacontext;

			if (active)
			{
				if (keel)
				{
					//// active keel
					// load PLIDs into combobox
					foreach (int x in Defs.KEEL_ACTIVE)
					{
						cmbPLID.Items.Add( x + " (Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] + ")" );
					}

					// hide uneeded controls
					lblReversed.Visibility = Visibility.Hidden;
					cbReversed.Visibility = Visibility.Hidden;
					lblGuides.Visibility = Visibility.Hidden;
					cmbFwdGuides.Visibility = Visibility.Hidden;
					cmbAftGuides.Visibility = Visibility.Hidden;

					// define bindings
					cmbPLID.SetBinding( ComboBox.SelectedIndexProperty, new Binding
					{
						Source = DataContext,
						Mode = BindingMode.TwoWay,
						Path = new PropertyPath( bindplid ),
						Converter = new Convert_PLID_KEEL_ACTIVE()
					});
				}
				else
				{
					//// active longeron
					// load PLIDs into combobox
					foreach (int x in Defs.LONGERON_ACTIVE)
					{
						cmbPLID.Items.Add( x + " (Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] + ")" );
					}

					// define bindings
					cmbPLID.SetBinding( ComboBox.SelectedIndexProperty, new Binding
					{
						Source = DataContext,
						Mode = BindingMode.TwoWay,
						Path = new PropertyPath( bindplid ),
						Converter = new Convert_PLID_LONGERON_ACTIVE()
					});
					cbReversed.SetBinding( CheckBox.IsCheckedProperty, new Binding
					{
						Source = DataContext,
						Mode = BindingMode.TwoWay,
						Path = new PropertyPath( bindreversed )
					});
					cmbFwdGuides.SetBinding( ComboBox.SelectedIndexProperty, new Binding
					{
						Source = DataContext,
						Mode = BindingMode.TwoWay,
						Path = new PropertyPath( bindfwdguide )
					});
					cmbAftGuides.SetBinding( ComboBox.SelectedIndexProperty, new Binding
					{
						Source = DataContext,
						Mode = BindingMode.TwoWay,
						Path = new PropertyPath( bindaftguide )
					});
				}

				// define bindings
				cmbLatch.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.TwoWay,
					Path = new PropertyPath( bindlatch )
				});
			}
			else
			{
				if (keel)
				{
					//// passive keel
					// load PLIDs into combobox
					foreach (int x in Defs.KEEL_PASSIVE)
					{
						cmbPLID.Items.Add( x + " Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] + ")" );
					}

					// hide uneeded controls
					lblReversed.Visibility = Visibility.Hidden;
					cbReversed.Visibility = Visibility.Hidden;

					// define bindings
					cmbPLID.SetBinding( ComboBox.SelectedIndexProperty, new Binding
					{
						Source = DataContext,
						Mode = BindingMode.TwoWay,
						Path = new PropertyPath( bindplid ),
						Converter = new Convert_PLID_KEEL_PASSIVE()
					});
				}
				else
				{
					//// passive longeron
					// load PLIDs into combobox
					foreach (int x in Defs.LONGERON_PASSIVE)
					{
						cmbPLID.Items.Add( x + " Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] + ")" );
					}

					// define bindings
					cmbPLID.SetBinding( ComboBox.SelectedIndexProperty, new Binding
					{
						Source = DataContext,
						Mode = BindingMode.TwoWay,
						Path = new PropertyPath( bindplid ),
						Converter = new Convert_PLID_LONGERON_PASSIVE()
					});
					cbReversed.SetBinding( CheckBox.IsCheckedProperty, new Binding
					{
						Source = DataContext,
						Mode = BindingMode.TwoWay,
						Path = new PropertyPath( bindreversed )
					});
				}

				// hide uneeded controls
				lblLatch.Visibility = Visibility.Hidden;
				cmbLatch.Visibility = Visibility.Hidden;
				lblGuides.Visibility = Visibility.Hidden;
				cmbFwdGuides.Visibility = Visibility.Hidden;
				cmbAftGuides.Visibility = Visibility.Hidden;
			}

			// define bindings
			cbAttachment.SetBinding( CheckBox.IsCheckedProperty, new Binding
			{
				Source = DataContext,
						Mode = BindingMode.TwoWay,
				Path = new PropertyPath( bindisattachment )
			});
			return;
		}
	}
}

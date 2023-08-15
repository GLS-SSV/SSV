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
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Input;


namespace SSVMissionEditor
{
	public class Convert_Attachment_Enabled : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// model to viewer
			return !(bool)value;
		}

		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// viewer to model
			throw new NotSupportedException();
		}
	}

	public class Convert_PLID_idx : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// model to viewer
			if ((int)value == 0) return 0;
			else
			{
				int[] plids = parameter as int[];
				int i = Array.FindIndex( plids, item => item == (int)value );
				return i;
			}
		}

		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// viewer to model
			int[] plids = parameter as int[];
			if (((int)value < 0) || ((int)value >= plids.Length)) return plids[0];
			return plids[(int)value];
		}
	}

	public class Convert_PLID_SPDS: IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// model to viewer
			List<string> lst = new List<string>();

			foreach (int x in ((bool)value ? Defs.LONGERON_SPDS_3 : Defs.LONGERON_SPDS_5))
			{
				lst.Add( x + " (Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] + ")" );
			}

			return lst;
		}

		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// viewer to model
			throw new NotSupportedException();
		}
	}

	/// <summary>
	/// Interaction logic for EditLatch.xaml
	/// </summary>
	public partial class EditLatch : Window
	{
		public EditLatch( object datacontext, string latch_bind, int latch_idx, int type, bool keel )
		{
			InitializeComponent();

			DataContext = datacontext;

			this.latch_bind = latch_bind;
			this.latch_idx = latch_idx;
			this.type = type;
			this.keel = keel;

			if (type == 0)
			{
				latch_bind += "[" + latch_idx + "]";

				if (keel)
				{
					//// active keel
					// load PLIDs into combobox
					foreach (int x in Defs.KEEL_ACTIVE)
					{
						cmbPLID.Items.Add( x + " (Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] + ")" );
					}

					// hide unneeded controls
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
						Path = new PropertyPath( latch_bind + ".PLID" ),
						Converter = new Convert_PLID_idx(),
						ConverterParameter = Defs.KEEL_ACTIVE
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
						Path = new PropertyPath( latch_bind + ".PLID" ),
						Converter = new Convert_PLID_idx(),
						ConverterParameter = Defs.LONGERON_ACTIVE
					});
					cbReversed.SetBinding( CheckBox.IsCheckedProperty, new Binding
					{
						Source = DataContext,
						Mode = BindingMode.TwoWay,
						Path = new PropertyPath( latch_bind + ".Reversed" )
					});
					cmbFwdGuides.SetBinding( ComboBox.SelectedIndexProperty, new Binding
					{
						Source = DataContext,
						Mode = BindingMode.TwoWay,
						Path = new PropertyPath( latch_bind + ".ForwardGuide" )
					});
					cmbAftGuides.SetBinding( ComboBox.SelectedIndexProperty, new Binding
					{
						Source = DataContext,
						Mode = BindingMode.TwoWay,
						Path = new PropertyPath( latch_bind + ".AftGuide" )
					});
				}

				// define bindings
				cmbLatch.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.TwoWay,
					Path = new PropertyPath( latch_bind + ".Latch" )
				});

				IsAttHack( latch_bind, latch_idx );
			}
			else if (type == 1)
			{
				latch_bind += "[" + latch_idx + "]";

				if (keel)
				{
					//// passive keel
					// load PLIDs into combobox
					foreach (int x in Defs.KEEL_PASSIVE)
					{
						cmbPLID.Items.Add( x + " (Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] + ")" );
					}

					// hide unneeded controls
					lblReversed.Visibility = Visibility.Hidden;
					cbReversed.Visibility = Visibility.Hidden;

					// define bindings
					cmbPLID.SetBinding( ComboBox.SelectedIndexProperty, new Binding
					{
						Source = DataContext,
						Mode = BindingMode.TwoWay,
						Path = new PropertyPath( latch_bind + ".PLID" ),
						Converter = new Convert_PLID_idx(),
						ConverterParameter = Defs.KEEL_PASSIVE
					});
				}
				else
				{
					//// passive longeron
					// load PLIDs into combobox
					foreach (int x in Defs.LONGERON_PASSIVE)
					{
						cmbPLID.Items.Add( x + " (Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] + ")" );
					}

					// define bindings
					cmbPLID.SetBinding( ComboBox.SelectedIndexProperty, new Binding
					{
						Source = DataContext,
						Mode = BindingMode.TwoWay,
						Path = new PropertyPath( latch_bind + ".PLID" ),
						Converter = new Convert_PLID_idx(),
						ConverterParameter = Defs.LONGERON_PASSIVE
					});
					cbReversed.SetBinding( CheckBox.IsCheckedProperty, new Binding
					{
						Source = DataContext,
						Mode = BindingMode.TwoWay,
						Path = new PropertyPath( latch_bind + ".Reversed" )
					});
				}

				// hide unneeded controls
				lblLatch.Visibility = Visibility.Hidden;
				cmbLatch.Visibility = Visibility.Hidden;
				lblGuides.Visibility = Visibility.Hidden;
				cmbFwdGuides.Visibility = Visibility.Hidden;
				cmbAftGuides.Visibility = Visibility.Hidden;

				IsAttHack( latch_bind, latch_idx );
			}
			else //if (type == 2)
			{
				if (keel)
				{
					//// keel
					// load PLIDs into combobox
					foreach (int x in Defs.KEEL_SPDS)
					{
						cmbPLID.Items.Add( x + " (Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] + ")" );
					}

					// hide unneeded controls
					lblReversed.Visibility = Visibility.Hidden;
					cbReversed.Visibility = Visibility.Hidden;

					// define bindings
					cmbPLID.SetBinding( ComboBox.SelectedIndexProperty, new Binding
					{
						Source = DataContext,
						Mode = BindingMode.TwoWay,
						Path = new PropertyPath( latch_bind + ".Latches[" + latch_idx + "].PLID" ),
						Converter = new Convert_PLID_idx(),
						ConverterParameter = Defs.KEEL_SPDS
					});
				}
				else
				{
					//// longeron
					// define bindings
					cbReversed.SetBinding( CheckBox.IsCheckedProperty, new Binding
					{
						Source = DataContext,
						Mode = BindingMode.TwoWay,
						Path = new PropertyPath( latch_bind + ".Latches[" + latch_idx + "].Reversed" )
					});
					cmbPLID.SetBinding( ComboBox.ItemsSourceProperty, new Binding
					{
						Source = DataContext,
						Mode = BindingMode.OneWay,
						Path = new PropertyPath( latch_bind + ".Latches[" + latch_idx + "].Reversed" ),
						Converter = new Convert_PLID_SPDS()
					});
					cmbPLID.SetBinding( ComboBox.SelectedIndexProperty, new Binding
					{
						Source = DataContext,
						Mode = BindingMode.TwoWay,
						Path = new PropertyPath( latch_bind + ".Latches[" + latch_idx + "].PLID" ),
						Converter = new Convert_PLID_idx(),
						ConverterParameter = (cbReversed.IsChecked == true) ? Defs.LONGERON_SPDS_3 : Defs.LONGERON_SPDS_5
					});
				}

				// hide unneeded controls
				lblAttachment.Visibility = Visibility.Hidden;
				lblLatch.Visibility = Visibility.Hidden;
				cmbLatch.Visibility = Visibility.Hidden;
				lblGuides.Visibility = Visibility.Hidden;
				cmbFwdGuides.Visibility = Visibility.Hidden;
				cmbAftGuides.Visibility = Visibility.Hidden;
			}
			return;
		}

		private void IsAttHack( string latch_bind, int latch_idx )
		{
			//// handle isattachment
			CheckBox[] cbattacharray = new CheckBox[]
			{
				cbAttachment0,
				cbAttachment1,
				cbAttachment2,
				cbAttachment3,
				cbAttachment4,
				cbAttachment5,
				cbAttachment6,
				cbAttachment7,
				cbAttachment8,
				cbAttachment9,
				cbAttachment10,
				cbAttachment11
			};
			// define bindings
			for (int i = 0; i < 12; i++)
			{
				string isattachment_bind = latch_bind + "[" + i + "]" + ".IsAttachment";
				cbattacharray[i].SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.TwoWay,
					Path = new PropertyPath( isattachment_bind )
				});
			}
			cbattacharray[latch_idx].SetBinding( CheckBox.IsEnabledProperty, new Binding
			{
				Source = DataContext,
				Mode = BindingMode.OneWay,
				Path = new PropertyPath( latch_bind + ".IsAttachment" ),
				Converter = new Convert_Attachment_Enabled()
			});
			// unhide correct checkbox
			cbattacharray[latch_idx].Visibility = Visibility.Visible;
		}

		private void CbAttachment_Click(object sender, RoutedEventArgs e)
		{
			// when one is clicked for checking, uncheck rest
			CheckBox cb = sender as CheckBox;

			if (cb.IsChecked == false) return;
			if (cb != cbAttachment0) cbAttachment0.IsChecked = false;
			if (cb != cbAttachment1) cbAttachment1.IsChecked = false;
			if (cb != cbAttachment2) cbAttachment2.IsChecked = false;
			if (cb != cbAttachment3) cbAttachment3.IsChecked = false;
			if (cb != cbAttachment4) cbAttachment4.IsChecked = false;
			if (cb != cbAttachment5) cbAttachment5.IsChecked = false;
			if (cb != cbAttachment6) cbAttachment6.IsChecked = false;
			if (cb != cbAttachment7) cbAttachment7.IsChecked = false;
			if (cb != cbAttachment8) cbAttachment8.IsChecked = false;
			if (cb != cbAttachment9) cbAttachment9.IsChecked = false;
			if (cb != cbAttachment10) cbAttachment10.IsChecked = false;
			if (cb != cbAttachment11) cbAttachment11.IsChecked = false;
			return;
		}

		private void CbReversed_Click(object sender, RoutedEventArgs e)
		{
			if (keel) return;
			if (type != 2) return;

			BindingOperations.ClearBinding( cmbPLID, ComboBox.SelectedIndexProperty );

			cmbPLID.SetBinding( ComboBox.SelectedIndexProperty, new Binding
			{
				Source = DataContext,
				Mode = BindingMode.TwoWay,
				Path = new PropertyPath( latch_bind + ".Latches[" + latch_idx + "].PLID" ),
				Converter = new Convert_PLID_idx(),
				ConverterParameter = (cbReversed.IsChecked == true) ? Defs.LONGERON_SPDS_3 : Defs.LONGERON_SPDS_5
			});

			cmbPLID.SelectedIndex = 0;
			return;
		}

		private void CommandBinding_Executed( object sender, ExecutedRoutedEventArgs e )
		{
			Close();
			return;
		}

		string latch_bind;
		int latch_idx;
		int type;
		bool keel;
	}
}

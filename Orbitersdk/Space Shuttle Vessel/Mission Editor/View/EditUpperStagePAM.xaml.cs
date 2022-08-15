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
	public class Convert_PLID_KEEL_PAM_D : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// model to viewer
			if ((int)value == 0) return 0;
			else
			{
				int i = Array.FindIndex( Defs.KEEL_PAM_D, item => item == (int)value );
				return i;
			}
		}

		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// viewer to model
			if ((int)value == 0) return 0;
			else return Defs.KEEL_PAM_D[(int)value];
		}
	}

	public class Convert_PLID_KEEL_PAM_A : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// model to viewer
			if ((int)value == 0) return 0;
			else
			{
				int i = Array.FindIndex( Defs.KEEL_PAM_A, item => item == (int)value );
				return i;
			}
		}

		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture )
		{
			// viewer to model
			if ((int)value == 0) return 0;
			else return Defs.KEEL_PAM_A[(int)value];
		}
	}

	/// <summary>
	/// Interaction logic for EditUpperStagePAM.xaml
	/// </summary>
	public partial class EditUpperStagePAM : Window
	{
		public EditUpperStagePAM( object datacontext, bool pamD, string bindname, string bindplid, string bindload, string bindlargesunshield )
		{
			InitializeComponent();

			DataContext = datacontext;

			chkSmallUpperStage_LargeSunshield.IsEnabled = pamD;

			txtSmallUpperStage_Name.SetBinding( TextBox.TextProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bindname ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});

			if (pamD)
			{
				// load PLIDs into combobox
				foreach (int x in Defs.KEEL_PAM_D)
				{
					cmbSmallUpperStage_PLID.Items.Add( x );
				}

				cmbSmallUpperStage_PLID.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_KEEL_PAM_D()
				});

				chkSmallUpperStage_LargeSunshield.SetBinding( CheckBox.IsCheckedProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindlargesunshield ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
				});
			}
			else
			{
				// load PLIDs into combobox
				foreach (int x in Defs.KEEL_PAM_A)
				{
					cmbSmallUpperStage_PLID.Items.Add( x );
				}

				cmbSmallUpperStage_PLID.SetBinding( ComboBox.SelectedIndexProperty, new Binding
				{
					Source = this.DataContext,
					Path = new PropertyPath( bindplid ),
					UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
					Converter = new Convert_PLID_KEEL_PAM_A()
				});
			}

			txtSmallUpperStage_Load.SetBinding( TextBox.TextProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bindload ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
		}

		private void cmbPLIDStbd1_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			return;
		}
	}
}

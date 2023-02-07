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
/******* SSV File Modification Notice *******
Date         Developer
2020/05/31   GLS
2020/06/28   GLS
2020/07/01   GLS
2020/07/02   GLS
2020/07/03   GLS
2020/07/30   GLS
2020/08/22   GLS
2020/09/19   GLS
2020/10/09   GLS
2020/10/10   GLS
2021/12/19   GLS
2021/12/25   GLS
2022/01/10   GLS
2022/02/23   GLS
2022/03/02   GLS
2022/03/04   GLS
2022/03/22   GLS
2022/03/24   GLS
2022/06/24   GLS
2022/08/05   GLS
2022/10/17   GLS
2022/11/13   GLS
2023/02/06   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra Workbench

  Space Shuttle Ultra is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Ultra is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Ultra; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file Doc\Space Shuttle Ultra\GPL.txt for more details.

  **************************************************************************/

using SSVMissionEditor.model;
using System;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;


namespace SSVMissionEditor
{
	public class Convert_PL_Bays : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture ) => (int)value - 1;// model to viewer
		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture ) => (int)value + 1;// viewer to model
	}

	public class Convert_Bridge_Type : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture ) => (int)value;
		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture ) => (Bridge_Type)value;
	}

	public class Convert_LongeronSillHardware_Type : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture ) => (int)value;
		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture ) => (LongeronSillHardware_Type)value;
	}

	/// <summary>
	/// Interaction logic for Payload.xaml
	/// </summary>
	public partial class Payload : UserControl
	{
		public Payload()
		{
			InitializeComponent();

			for (int i = 1; i <= 13; i++)
			{
				string str = "Bay " + i;
				cbBayBridge1Bay.Items.Add( new ComboBoxItem(){Content = str} );
				cbBayBridge2Bay.Items.Add( new ComboBoxItem(){Content = str} );
				cbBayBridge3Bay.Items.Add( new ComboBoxItem(){Content = str} );
				cbBayBridge4Bay.Items.Add( new ComboBoxItem(){Content = str} );
				cbBayBridge5Bay.Items.Add( new ComboBoxItem(){Content = str} );
				cbBayBridge6Bay.Items.Add( new ComboBoxItem(){Content = str} );
				cbBayBridge7Bay.Items.Add( new ComboBoxItem(){Content = str} );
				cbBayBridge8Bay.Items.Add( new ComboBoxItem(){Content = str} );
			}
		}

		private void ckPayload_Checked(object sender, System.Windows.RoutedEventArgs e)
		{
			if (sender == ckActive1)
			{
				ckHasPayload1.IsEnabled = true;
				if (ckHasPayload1.IsChecked == true) btnActive1Payload.IsEnabled = true;
				btnActive1Latch.IsEnabled = true;
				lblActive1PayloadName.SetBinding( Label.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( "OV.PL_Active[0].Payload.Name" )
				});
			}
			else if (sender == ckActive2)
			{
				ckHasPayload2.IsEnabled = true;
				if (ckHasPayload2.IsChecked == true) btnActive2Payload.IsEnabled = true;
				btnActive2Latch.IsEnabled = true;
				lblActive2PayloadName.SetBinding( Label.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( "OV.PL_Active[1].Payload.Name" )
				});
			}
			else if (sender == ckActive3)
			{
				ckHasPayload3.IsEnabled = true;
				if (ckHasPayload3.IsChecked == true) btnActive3Payload.IsEnabled = true;
				btnActive3Latch.IsEnabled = true;
				lblActive3PayloadName.SetBinding( Label.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( "OV.PL_Active[2].Payload.Name" )
				});
			}
			else if (sender == ckActive4)
			{
				ckHasPayload4.IsEnabled = true;
				if (ckHasPayload4.IsChecked == true) btnActive4Payload.IsEnabled = true;
				btnActive4Latch.IsEnabled = true;
				lblActive4PayloadName.SetBinding( Label.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( "OV.PL_Active[3].Payload.Name" )
				});
			}
			else if (sender == ckActive5)
			{
				ckHasPayload5.IsEnabled = true;
				if (ckHasPayload5.IsChecked == true) btnActive5Payload.IsEnabled = true;
				btnActive5Latch.IsEnabled = true;
				lblActive5PayloadName.SetBinding( Label.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( "OV.PL_Active[4].Payload.Name" )
				});
			}
			else if (sender == ckPassive1)
			{
				btnPassive1Payload.IsEnabled = true;
				btnPassive1Latch.IsEnabled = true;
				lblPassive1PayloadName.SetBinding( Label.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( "OV.PL_Passive[0].Payload.Name" )
				});
			}
			else if (sender == ckPassive2)
			{
				btnPassive2Payload.IsEnabled = true;
				btnPassive2Latch.IsEnabled = true;
				lblPassive2PayloadName.SetBinding( Label.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( "OV.PL_Passive[1].Payload.Name" )
				});
			}
			else if (sender == ckPassive3)
			{
				btnPassive3Payload.IsEnabled = true;
				btnPassive3Latch.IsEnabled = true;
				lblPassive3PayloadName.SetBinding( Label.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( "OV.PL_Passive[2].Payload.Name" )
				});
			}
			else if (sender == ckPassive4)
			{
				btnPassive4Payload.IsEnabled = true;
				btnPassive4Latch.IsEnabled = true;
				lblPassive4PayloadName.SetBinding( Label.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( "OV.PL_Passive[3].Payload.Name" )
				});
			}
			else if (sender == ckPassive5)
			{
				btnPassive5Payload.IsEnabled = true;
				btnPassive5Latch.IsEnabled = true;
				lblPassive5PayloadName.SetBinding( Label.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( "OV.PL_Passive[4].Payload.Name" )
				});
			}
			else if (sender == ckBayBridge1)
			{
				btnBayBridge1Payload.IsEnabled = true;
				cbBayBridge1Bay.IsEnabled = true;
				cbBayBridge1Bridge.IsEnabled = true;
				lblBayBridge1PayloadName.SetBinding( Label.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( "OV.PL_BayBridge[0].Payload.Name" )
				});
			}
			else if (sender == ckBayBridge2)
			{
				btnBayBridge2Payload.IsEnabled = true;
				cbBayBridge2Bay.IsEnabled = true;
				cbBayBridge2Bridge.IsEnabled = true;
				lblBayBridge2PayloadName.SetBinding( Label.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( "OV.PL_BayBridge[1].Payload.Name" )
				});
			}
			else if (sender == ckBayBridge3)
			{
				btnBayBridge3Payload.IsEnabled = true;
				cbBayBridge3Bay.IsEnabled = true;
				cbBayBridge3Bridge.IsEnabled = true;
				lblBayBridge3PayloadName.SetBinding( Label.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( "OV.PL_BayBridge[2].Payload.Name" )
				});
			}
			else if (sender == ckBayBridge4)
			{
				btnBayBridge4Payload.IsEnabled = true;
				cbBayBridge4Bay.IsEnabled = true;
				cbBayBridge4Bridge.IsEnabled = true;
				lblBayBridge4PayloadName.SetBinding( Label.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( "OV.PL_BayBridge[3].Payload.Name" )
				});
			}
			else if (sender == ckBayBridge5)
			{
				btnBayBridge5Payload.IsEnabled = true;
				cbBayBridge5Bay.IsEnabled = true;
				cbBayBridge5Bridge.IsEnabled = true;
				lblBayBridge5PayloadName.SetBinding( Label.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( "OV.PL_BayBridge[4].Payload.Name" )
				});
			}
			else if (sender == ckBayBridge6)
			{
				btnBayBridge6Payload.IsEnabled = true;
				cbBayBridge6Bay.IsEnabled = true;
				cbBayBridge6Bridge.IsEnabled = true;
				lblBayBridge6PayloadName.SetBinding( Label.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( "OV.PL_BayBridge[5].Payload.Name" )
				});
			}
			else if (sender == ckBayBridge7)
			{
				btnBayBridge7Payload.IsEnabled = true;
				cbBayBridge7Bay.IsEnabled = true;
				cbBayBridge7Bridge.IsEnabled = true;
				lblBayBridge7PayloadName.SetBinding( Label.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( "OV.PL_BayBridge[6].Payload.Name" )
				});
			}
			else if (sender == ckBayBridge8)
			{
				btnBayBridge8Payload.IsEnabled = true;
				cbBayBridge8Bay.IsEnabled = true;
				cbBayBridge8Bridge.IsEnabled = true;
				lblBayBridge8PayloadName.SetBinding( Label.ContentProperty, new Binding
				{
					Source = DataContext,
					Mode = BindingMode.OneWay,
					Path = new PropertyPath( "OV.PL_BayBridge[7].Payload.Name" )
				});
			}
		}

		private void ckPayload_Unchecked(object sender, System.Windows.RoutedEventArgs e)
		{
			if (sender == ckActive1)
			{
				ckHasPayload1.IsEnabled = false;
				btnActive1Payload.IsEnabled = false;
				btnActive1Latch.IsEnabled = false;
				BindingOperations.ClearBinding( lblActive1PayloadName, Label.ContentProperty );
			}
			else if (sender == ckActive2)
			{
				ckHasPayload2.IsEnabled = false;
				btnActive2Payload.IsEnabled = false;
				btnActive2Latch.IsEnabled = false;
				BindingOperations.ClearBinding( lblActive2PayloadName, Label.ContentProperty );
			}
			else if (sender == ckActive3)
			{
				ckHasPayload3.IsEnabled = false;
				btnActive3Payload.IsEnabled = false;
				btnActive3Latch.IsEnabled = false;
				BindingOperations.ClearBinding( lblActive3PayloadName, Label.ContentProperty );
			}
			else if (sender == ckActive4)
			{
				ckHasPayload4.IsEnabled = false;
				btnActive4Payload.IsEnabled = false;
				btnActive4Latch.IsEnabled = false;
				BindingOperations.ClearBinding( lblActive4PayloadName, Label.ContentProperty );
			}
			else if (sender == ckActive5)
			{
				ckHasPayload5.IsEnabled = false;
				btnActive5Payload.IsEnabled = false;
				btnActive5Latch.IsEnabled = false;
				BindingOperations.ClearBinding( lblActive5PayloadName, Label.ContentProperty );
			}
			else if (sender == ckPassive1)
			{
				btnPassive1Payload.IsEnabled = false;
				btnPassive1Latch.IsEnabled = false;
				BindingOperations.ClearBinding( lblPassive1PayloadName, Label.ContentProperty );
			}
			else if (sender == ckPassive2)
			{
				btnPassive2Payload.IsEnabled = false;
				btnPassive2Latch.IsEnabled = false;
				BindingOperations.ClearBinding( lblPassive2PayloadName, Label.ContentProperty );
			}
			else if (sender == ckPassive3)
			{
				btnPassive3Payload.IsEnabled = false;
				btnPassive3Latch.IsEnabled = false;
				BindingOperations.ClearBinding( lblPassive3PayloadName, Label.ContentProperty );
			}
			else if (sender == ckPassive4)
			{
				btnPassive4Payload.IsEnabled = false;
				btnPassive4Latch.IsEnabled = false;
				BindingOperations.ClearBinding( lblPassive4PayloadName, Label.ContentProperty );
			}
			else if (sender == ckPassive5)
			{
				btnPassive5Payload.IsEnabled = false;
				btnPassive5Latch.IsEnabled = false;
				BindingOperations.ClearBinding( lblPassive5PayloadName, Label.ContentProperty );
			}
			else if (sender == ckBayBridge1)
			{
				btnBayBridge1Payload.IsEnabled = false;
				cbBayBridge1Bay.IsEnabled = false;
				cbBayBridge1Bridge.IsEnabled = false;
				BindingOperations.ClearBinding( lblBayBridge1PayloadName, Label.ContentProperty );
			}
			else if (sender == ckBayBridge2)
			{
				btnBayBridge2Payload.IsEnabled = false;
				cbBayBridge2Bay.IsEnabled = false;
				cbBayBridge2Bridge.IsEnabled = false;
				BindingOperations.ClearBinding( lblBayBridge2PayloadName, Label.ContentProperty );
			}
			else if (sender == ckBayBridge3)
			{
				btnBayBridge3Payload.IsEnabled = false;
				cbBayBridge3Bay.IsEnabled = false;
				cbBayBridge3Bridge.IsEnabled = false;
				BindingOperations.ClearBinding( lblBayBridge3PayloadName, Label.ContentProperty );
			}
			else if (sender == ckBayBridge4)
			{
				btnBayBridge4Payload.IsEnabled = false;
				cbBayBridge4Bay.IsEnabled = false;
				cbBayBridge4Bridge.IsEnabled = false;
				BindingOperations.ClearBinding( lblBayBridge4PayloadName, Label.ContentProperty );
			}
			else if (sender == ckBayBridge5)
			{
				btnBayBridge5Payload.IsEnabled = false;
				cbBayBridge5Bay.IsEnabled = false;
				cbBayBridge5Bridge.IsEnabled = false;
				BindingOperations.ClearBinding( lblBayBridge5PayloadName, Label.ContentProperty );
			}
			else if (sender == ckBayBridge6)
			{
				btnBayBridge6Payload.IsEnabled = false;
				cbBayBridge6Bay.IsEnabled = false;
				cbBayBridge6Bridge.IsEnabled = false;
				BindingOperations.ClearBinding( lblBayBridge6PayloadName, Label.ContentProperty );
			}
			else if (sender == ckBayBridge7)
			{
				btnBayBridge7Payload.IsEnabled = false;
				cbBayBridge7Bay.IsEnabled = false;
				cbBayBridge7Bridge.IsEnabled = false;
				BindingOperations.ClearBinding( lblBayBridge7PayloadName, Label.ContentProperty );
			}
			else if (sender == ckBayBridge8)
			{
				btnBayBridge8Payload.IsEnabled = false;
				cbBayBridge8Bay.IsEnabled = false;
				cbBayBridge8Bridge.IsEnabled = false;
				BindingOperations.ClearBinding( lblBayBridge8PayloadName, Label.ContentProperty );
			}
			return;
		}

		private void ckHasPayload_Checked(object sender, System.Windows.RoutedEventArgs e)
		{
			if (sender == ckHasPayload1)
			{
				btnActive1Payload.IsEnabled = true;
			}
			else if (sender == ckHasPayload2)
			{
				btnActive2Payload.IsEnabled = true;
			}
			else if (sender == ckHasPayload3)
			{
				btnActive3Payload.IsEnabled = true;
			}
			else if (sender == ckHasPayload4)
			{
				btnActive4Payload.IsEnabled = true;
			}
			else if (sender == ckHasPayload5)
			{
				btnActive5Payload.IsEnabled = true;
			}
			return;
		}

		private void ckHasPayload_Unchecked(object sender, System.Windows.RoutedEventArgs e)
		{
			if (sender == ckHasPayload1)
			{
				btnActive1Payload.IsEnabled = false;
			}
			else if (sender == ckHasPayload2)
			{
				btnActive2Payload.IsEnabled = false;
			}
			else if (sender == ckHasPayload3)
			{
				btnActive3Payload.IsEnabled = false;
			}
			else if (sender == ckHasPayload4)
			{
				btnActive4Payload.IsEnabled = false;
			}
			else if (sender == ckHasPayload5)
			{
				btnActive5Payload.IsEnabled = false;
			}
			return;
		}

		private void ShowEditPayload( string PayloadBindPath )
		{
			string vesselclass = PayloadBindPath + ".VesselClass";
			string name = PayloadBindPath + ".Name";
			string attachid = PayloadBindPath + ".AttachmentID";
			string scnparams = PayloadBindPath + ".ScnParams";

			EditPayload editpayload = new EditPayload( DataContext, vesselclass, name, attachid, scnparams );
			editpayload.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
			editpayload.ShowDialog();
			return;
		}

		private void ShowEditLatches( bool active, short pl_idx )
		{
			EditLatches editlatches = new EditLatches( DataContext, active, pl_idx );
			editlatches.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
			editlatches.ShowDialog();
			return;
		}

		private void btnActivePayload_Click(object sender, System.Windows.RoutedEventArgs e)
		{
			if (sender == btnActive1Payload)
			{
				ShowEditPayload( "OV.PL_Active[0].Payload" );
			}
			else if (sender == btnActive2Payload)
			{
				ShowEditPayload( "OV.PL_Active[1].Payload" );
			}
			else if (sender == btnActive3Payload)
			{
				ShowEditPayload( "OV.PL_Active[2].Payload" );
			}
			else if (sender == btnActive4Payload)
			{
				ShowEditPayload( "OV.PL_Active[3].Payload" );
			}
			else if (sender == btnActive5Payload)
			{
				ShowEditPayload( "OV.PL_Active[4].Payload" );
			}
			return;
		}

		private void btnPassivePayload_Click(object sender, System.Windows.RoutedEventArgs e)
		{
			if (sender == btnPassive1Payload)
			{
				ShowEditPayload( "OV.PL_Passive[0].Payload" );
			}
			else if (sender == btnPassive2Payload)
			{
				ShowEditPayload( "OV.PL_Passive[1].Payload" );
			}
			else if (sender == btnPassive3Payload)
			{
				ShowEditPayload( "OV.PL_Passive[2].Payload" );
			}
			else if (sender == btnPassive4Payload)
			{
				ShowEditPayload( "OV.PL_Passive[3].Payload" );
			}
			else if (sender == btnPassive5Payload)
			{
				ShowEditPayload( "OV.PL_Passive[4].Payload" );
			}
			return;
		}

		private void btnBayBridgePayload_Click(object sender, System.Windows.RoutedEventArgs e)
		{
			if (sender == btnBayBridge1Payload)
			{
				ShowEditPayload( "OV.PL_BayBridge[0].Payload" );
			}
			else if (sender == btnBayBridge2Payload)
			{
				ShowEditPayload( "OV.PL_BayBridge[1].Payload" );
			}
			else if (sender == btnBayBridge3Payload)
			{
				ShowEditPayload( "OV.PL_BayBridge[2].Payload" );
			}
			else if (sender == btnBayBridge4Payload)
			{
				ShowEditPayload( "OV.PL_BayBridge[3].Payload" );
			}
			else if (sender == btnBayBridge5Payload)
			{
				ShowEditPayload( "OV.PL_BayBridge[4].Payload" );
			}
			else if (sender == btnBayBridge6Payload)
			{
				ShowEditPayload( "OV.PL_BayBridge[5].Payload" );
			}
			else if (sender == btnBayBridge7Payload)
			{
				ShowEditPayload( "OV.PL_BayBridge[6].Payload" );
			}
			else if (sender == btnBayBridge8Payload)
			{
				ShowEditPayload( "OV.PL_BayBridge[7].Payload" );
			}
			return;
		}


		private void btnActiveLatch_Click(object sender, System.Windows.RoutedEventArgs e)
		{
			if (sender == btnActive1Latch)
			{
				ShowEditLatches( true, 0 );
			}
			else if (sender == btnActive2Latch)
			{
				ShowEditLatches( true, 1 );
			}
			else if (sender == btnActive3Latch)
			{
				ShowEditLatches( true, 2 );
			}
			else if (sender == btnActive4Latch)
			{
				ShowEditLatches( true, 3 );
			}
			else if (sender == btnActive5Latch)
			{
				ShowEditLatches( true, 4 );
			}
			return;
		}

		private void btnPassiveLatch_Click(object sender, System.Windows.RoutedEventArgs e)
		{
			if (sender == btnPassive1Latch)
			{
				ShowEditLatches( false, 0 );
			}
			else if (sender == btnPassive2Latch)
			{
				ShowEditLatches( false, 1 );
			}
			else if (sender == btnPassive3Latch)
			{
				ShowEditLatches( false, 2 );
			}
			else if (sender == btnPassive4Latch)
			{
				ShowEditLatches( false, 3 );
			}
			else if (sender == btnPassive5Latch)
			{
				ShowEditLatches( false, 4 );
			}
			return;
		}

		private void btnPortLSEdit_Click(object sender, RoutedEventArgs e)
		{
			switch (cbPortLS.SelectedIndex)
			{
				case 1:// RMS
					{
						RMS rms = new RMS( DataContext, "OV.Port_RMS_SN" );
						rms.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
						rms.ShowDialog();
					}
					break;
				case 2:// PL MPM
					break;
				case 3:// SPDS
				{
						SPDS spds = new SPDS( DataContext, "OV.Stbd_SPDS" );
						spds.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
						spds.ShowDialog();
					}
					break;
				default:
					break;
			}
			return;
		}

		private void btnStbdLSEdit_Click(object sender, RoutedEventArgs e)
		{
			switch (cbStbdLS.SelectedIndex)
			{
				case 1:// RMS
					break;
				case 2:// PL MPM
					{
						PayloadMPM plmpm = new PayloadMPM( DataContext, "OV.Stbd_PL_MPM" );
						plmpm.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
						plmpm.ShowDialog();
					}
					break;
				case 3:// SPDS
					break;
				default:
					break;
			}
			return;
		}

		private void cbBayBridge1Bridge_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			ComboBoxItem itm = (ComboBoxItem)cbBayBridge1Bay.Items[12];// bay 13
			if (itm != null)
			{
				if (cbBayBridge1Bridge.SelectedIndex == 2/*Keel*/)
				{
					itm.IsEnabled = false;
					if (cbBayBridge1Bay.SelectedIndex == 12) cbBayBridge1Bay.SelectedIndex = 0;
				}
				else itm.IsEnabled = true;
			}
			return;
		}

		private void cbBayBridge2Bridge_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			ComboBoxItem itm = (ComboBoxItem)cbBayBridge2Bay.Items[12];// bay 13
			if (itm != null)
			{
				if (cbBayBridge2Bridge.SelectedIndex == 2/*Keel*/)
				{
					itm.IsEnabled = false;
					if (cbBayBridge2Bay.SelectedIndex == 12) cbBayBridge2Bay.SelectedIndex = 0;
				}
				else itm.IsEnabled = true;
			}
			return;
		}

		private void cbBayBridge3Bridge_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			ComboBoxItem itm = (ComboBoxItem)cbBayBridge3Bay.Items[12];// bay 13
			if (itm != null)
			{
				if (cbBayBridge3Bridge.SelectedIndex == 2/*Keel*/)
				{
					itm.IsEnabled = false;
					if (cbBayBridge3Bay.SelectedIndex == 12) cbBayBridge3Bay.SelectedIndex = 0;
				}
				else itm.IsEnabled = true;
			}
			return;
		}

		private void cbBayBridge4Bridge_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			ComboBoxItem itm = (ComboBoxItem)cbBayBridge4Bay.Items[12];// bay 13
			if (itm != null)
			{
				if (cbBayBridge4Bridge.SelectedIndex == 2/*Keel*/)
				{
					itm.IsEnabled = false;
					if (cbBayBridge4Bay.SelectedIndex == 12) cbBayBridge4Bay.SelectedIndex = 0;
				}
				else itm.IsEnabled = true;
			}
			return;
		}

		private void cbBayBridge5Bridge_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			ComboBoxItem itm = (ComboBoxItem)cbBayBridge5Bay.Items[12];// bay 13
			if (itm != null)
			{
				if (cbBayBridge5Bridge.SelectedIndex == 2/*Keel*/)
				{
					itm.IsEnabled = false;
					if (cbBayBridge5Bay.SelectedIndex == 12) cbBayBridge5Bay.SelectedIndex = 0;
				}
				else itm.IsEnabled = true;
			}
			return;
		}

		private void cbBayBridge6Bridge_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			ComboBoxItem itm = (ComboBoxItem)cbBayBridge6Bay.Items[12];// bay 13
			if (itm != null)
			{
				if (cbBayBridge6Bridge.SelectedIndex == 2/*Keel*/)
				{
					itm.IsEnabled = false;
					if (cbBayBridge6Bay.SelectedIndex == 12) cbBayBridge6Bay.SelectedIndex = 0;
				}
				else itm.IsEnabled = true;
			}
			return;
		}

		private void cbBayBridge7Bridge_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			ComboBoxItem itm = (ComboBoxItem)cbBayBridge7Bay.Items[12];// bay 13
			if (itm != null)
			{
				if (cbBayBridge7Bridge.SelectedIndex == 2/*Keel*/)
				{
					itm.IsEnabled = false;
					if (cbBayBridge7Bay.SelectedIndex == 12) cbBayBridge7Bay.SelectedIndex = 0;
				}
				else itm.IsEnabled = true;
			}
			return;
		}

		private void cbBayBridge8Bridge_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			ComboBoxItem itm = (ComboBoxItem)cbBayBridge8Bay.Items[12];// bay 13
			if (itm != null)
			{
				if (cbBayBridge8Bridge.SelectedIndex == 2/*Keel*/)
				{
					itm.IsEnabled = false;
					if (cbBayBridge8Bay.SelectedIndex == 12) cbBayBridge8Bay.SelectedIndex = 0;
				}
				else itm.IsEnabled = true;
			}
			return;
		}


		private void cbLargeUpperStageType_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			switch (cbLargeUpperStageType.SelectedIndex)
			{
				case 1:// IUS 2-Stage
				case 2:// IUS Twin-Stage
				case 3:// IUS 3-Stage
				case 4:// Centaur G
				case 5:// Centaur G-Prime
					btnLargeUpperStage.IsEnabled = true;
					btnLargeUpperStageAdapter.IsEnabled = true;
					btnLargeUpperStagePayload.IsEnabled = true;
					lblLargeUpperStagePayloadName.SetBinding( Label.ContentProperty, new Binding
					{
						Source = DataContext,
						Mode = BindingMode.OneWay,
						Path = new PropertyPath( "LargeUpperStage_PL.Name" )
					});
					break;
				default:
					btnLargeUpperStage.IsEnabled = false;
					btnLargeUpperStageAdapter.IsEnabled = false;
					btnLargeUpperStagePayload.IsEnabled = false;
					BindingOperations.ClearBinding( lblLargeUpperStagePayloadName, Label.ContentProperty );
					break;
			}
			return;
		}

		private void btnLargeUpperStage_Click(object sender, System.Windows.RoutedEventArgs e)
		{
			switch (cbLargeUpperStageType.SelectedIndex)
			{
				case 1:// IUS 2-Stage
					{
						EditUpperStageIUS editius = new EditUpperStageIUS( DataContext );
						editius.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
						editius.ShowDialog();
					}
					break;
				case 2:// IUS Twin-Stage
					// TODO
					break;
				case 3:// IUS 3-Stage
					// TODO
					break;
				case 4:// Centaur G
				case 5:// Centaur G-Prime
					{
						EditUpperStageCentaur editcentaur = new EditUpperStageCentaur( DataContext );
						editcentaur.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
						editcentaur.ShowDialog();
					}
					break;
				default:
					break;
			}
			return;
		}

		private void btnLargeUpperStageEditPayload_Click(object sender, System.Windows.RoutedEventArgs e)
		{
			EditPayload editpayload = new EditPayload( DataContext, "LargeUpperStage_PL.VesselClass", "LargeUpperStage_PL.Name", "LargeUpperStage_PL.AttachmentID", "LargeUpperStage_PL.ScnParams" );
			editpayload.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
			editpayload.ShowDialog();
			return;
		}

		private void btnLargeUpperStageEditAdapter_Click(object sender, System.Windows.RoutedEventArgs e)
		{
			EditPayloadAdapter editadapter = new EditPayloadAdapter( DataContext, "LargeUpperStage_Adapter_Mesh", "LargeUpperStage_Adapter_Offset", "LargeUpperStage_Adapter_Mass" );
			editadapter.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
			editadapter.ShowDialog();
			return;
		}

		private void cbLargeUpperStageType_Centaur_IsEnabledChanged(object sender, System.Windows.DependencyPropertyChangedEventArgs e)
		{
			if (!((ComboBoxItem)sender).IsEnabled && ((cbLargeUpperStageType.SelectedIndex == 4) || (cbLargeUpperStageType.SelectedIndex == 5))) cbLargeUpperStageType.SelectedIndex = 0;
			return;
		}


		private void cbSmallUpperStage1Type_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			switch (cbSmallUpperStage1Type.SelectedIndex)
			{
				case 1:// PAM-D
				case 2:// PAM-DII
				case 3:// PAM-A
					btnSmallUpperStage1.IsEnabled = true;
					btnSmallUpperStage1Adapter.IsEnabled = true;
					btnSmallUpperStage1Payload.IsEnabled = true;
					lblSmallUpperStage1PayloadName.SetBinding( Label.ContentProperty, new Binding
					{
						Source = DataContext,
						Mode = BindingMode.OneWay,
						Path = new PropertyPath( "SmallUpperStage_PL[0].Name" )
					});
					break;
				default:
					btnSmallUpperStage1.IsEnabled = false;
					btnSmallUpperStage1Adapter.IsEnabled = false;
					btnSmallUpperStage1Payload.IsEnabled = false;
					BindingOperations.ClearBinding( lblSmallUpperStage1PayloadName, Label.ContentProperty );
					break;
			}
			return;
		}

		private void btnSmallUpperStage1_Click(object sender, System.Windows.RoutedEventArgs e)
		{
			switch (cbSmallUpperStage1Type.SelectedIndex)
			{
				case 1:// PAM-D
				case 2:// PAM-DII
					{
						EditUpperStagePAM editius = new EditUpperStagePAM( DataContext, true, "SmallUpperStage_Name[0]", "OV.SmallUpperStage_ASEPLID[0]", "SmallUpperStage_Load[0]", "OV.SmallUpperStage_LargeSunshield[0]" );
						editius.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
						editius.ShowDialog();
					}
					break;
				case 3:// PAM-A
					{
						EditUpperStagePAM editius = new EditUpperStagePAM( DataContext, false, "SmallUpperStage_Name[0]", "OV.SmallUpperStage_ASEPLID[0]", "SmallUpperStage_Load[0]", "OV.SmallUpperStage_LargeSunshield[0]" );
						editius.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
						editius.ShowDialog();
					}
					break;
				default:
					break;
			}
			return;
		}

		private void btnSmallUpperStage1Adapter_Click(object sender, System.Windows.RoutedEventArgs e)
		{
			EditPayloadAdapter editadapter = new EditPayloadAdapter( DataContext, "SmallUpperStage_Adapter_Mesh[0]", "SmallUpperStage_Adapter_Offset[0]", "SmallUpperStage_Adapter_Mass[0]" );
			editadapter.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
			editadapter.ShowDialog();
			return;
		}

		private void btnSmallUpperStage1Payload_Click(object sender, System.Windows.RoutedEventArgs e)
		{
			EditPayload editpayload = new EditPayload( DataContext, "SmallUpperStage_PL[0].VesselClass", "SmallUpperStage_PL[0].Name", "SmallUpperStage_PL[0].AttachmentID", "SmallUpperStage_PL[0].ScnParams" );
			editpayload.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
			editpayload.ShowDialog();
			return;
		}


		private void cbSmallUpperStage2Type_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			switch (cbSmallUpperStage2Type.SelectedIndex)
			{
				case 1:// PAM-D
				case 2:// PAM-DII
				case 3:// PAM-A
					btnSmallUpperStage2.IsEnabled = true;
					btnSmallUpperStage2Adapter.IsEnabled = true;
					btnSmallUpperStage2Payload.IsEnabled = true;
					lblSmallUpperStage2PayloadName.SetBinding( Label.ContentProperty, new Binding
					{
						Source = DataContext,
						Mode = BindingMode.OneWay,
						Path = new PropertyPath( "SmallUpperStage_PL[1].Name" )
					});
					break;
				default:
					btnSmallUpperStage2.IsEnabled = false;
					btnSmallUpperStage2Adapter.IsEnabled = false;
					btnSmallUpperStage2Payload.IsEnabled = false;
					BindingOperations.ClearBinding( lblSmallUpperStage2PayloadName, Label.ContentProperty );
					break;
			}
			return;
		}

		private void btnSmallUpperStage2_Click(object sender, System.Windows.RoutedEventArgs e)
		{
			switch (cbSmallUpperStage2Type.SelectedIndex)
			{
				case 1:// PAM-D
				case 2:// PAM-DII
					{
						EditUpperStagePAM editius = new EditUpperStagePAM( DataContext, true, "SmallUpperStage_Name[1]", "OV.SmallUpperStage_ASEPLID[1]", "SmallUpperStage_Load[1]", "OV.SmallUpperStage_LargeSunshield[1]" );
						editius.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
						editius.ShowDialog();
					}
					break;
				case 3:// PAM-A
					{
						EditUpperStagePAM editius = new EditUpperStagePAM( DataContext, false, "SmallUpperStage_Name[1]", "OV.SmallUpperStage_ASEPLID[1]", "SmallUpperStage_Load[1]", "OV.SmallUpperStage_LargeSunshield[1]" );
						editius.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
						editius.ShowDialog();
					}
					break;
				default:
					break;
			}
			return;
		}

		private void btnSmallUpperStage2Adapter_Click(object sender, System.Windows.RoutedEventArgs e)
		{
			EditPayloadAdapter editadapter = new EditPayloadAdapter( DataContext, "SmallUpperStage_Adapter_Mesh[1]", "SmallUpperStage_Adapter_Offset[1]", "SmallUpperStage_Adapter_Mass[1]" );
			editadapter.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
			editadapter.ShowDialog();
			return;
		}

		private void btnSmallUpperStage2Payload_Click(object sender, System.Windows.RoutedEventArgs e)
		{
			EditPayload editpayload = new EditPayload( DataContext, "SmallUpperStage_PL[1].VesselClass", "SmallUpperStage_PL[1].Name", "SmallUpperStage_PL[1].AttachmentID", "SmallUpperStage_PL[1].ScnParams" );
			editpayload.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
			editpayload.ShowDialog();
			return;
		}


		private void cbSmallUpperStage3Type_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			switch (cbSmallUpperStage3Type.SelectedIndex)
			{
				case 1:// PAM-D
				case 2:// PAM-DII
				case 3:// PAM-A
					btnSmallUpperStage3.IsEnabled = true;
					btnSmallUpperStage3Adapter.IsEnabled = true;
					btnSmallUpperStage3Payload.IsEnabled = true;
					lblSmallUpperStage3PayloadName.SetBinding( Label.ContentProperty, new Binding
					{
						Source = DataContext,
						Mode = BindingMode.OneWay,
						Path = new PropertyPath( "SmallUpperStage_PL[2].Name" )
					});
					break;
				default:
					btnSmallUpperStage3.IsEnabled = false;
					btnSmallUpperStage3Adapter.IsEnabled = false;
					btnSmallUpperStage3Payload.IsEnabled = false;
					BindingOperations.ClearBinding( lblSmallUpperStage3PayloadName, Label.ContentProperty );
					break;
			}
			return;
		}

		private void btnSmallUpperStage3_Click(object sender, System.Windows.RoutedEventArgs e)
		{
			switch (cbSmallUpperStage3Type.SelectedIndex)
			{
				case 1:// PAM-D
				case 2:// PAM-DII
					{
						EditUpperStagePAM editius = new EditUpperStagePAM( DataContext, true, "SmallUpperStage_Name[2]", "OV.SmallUpperStage_ASEPLID[2]", "SmallUpperStage_Load[2]", "OV.SmallUpperStage_LargeSunshield[2]" );
						editius.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
						editius.ShowDialog();
					}
					break;
				case 3:// PAM-A
					{
						EditUpperStagePAM editius = new EditUpperStagePAM( DataContext, false, "SmallUpperStage_Name[2]", "OV.SmallUpperStage_ASEPLID[2]", "SmallUpperStage_Load[2]", "OV.SmallUpperStage_LargeSunshield[2]" );
						editius.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
						editius.ShowDialog();
					}
					break;
				default:
					break;
			}
			return;
		}

		private void btnSmallUpperStage3Adapter_Click(object sender, System.Windows.RoutedEventArgs e)
		{
			EditPayloadAdapter editadapter = new EditPayloadAdapter( DataContext, "SmallUpperStage_Adapter_Mesh[2]", "SmallUpperStage_Adapter_Offset[2]", "SmallUpperStage_Adapter_Mass[2]" );
			editadapter.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
			editadapter.ShowDialog();
			return;
		}

		private void btnSmallUpperStage3Payload_Click(object sender, System.Windows.RoutedEventArgs e)
		{
			EditPayload editpayload = new EditPayload( DataContext, "SmallUpperStage_PL[2].VesselClass", "SmallUpperStage_PL[2].Name", "SmallUpperStage_PL[2].AttachmentID", "SmallUpperStage_PL[2].ScnParams" );
			editpayload.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
			editpayload.ShowDialog();
			return;
		}

		private void cbPortLS_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			switch (cbPortLS.SelectedIndex)
			{
				case 1:// RMS
					BindingOperations.ClearBinding( lblPortLSPayloadName, Label.ContentProperty );
					break;
				case 2:// PL MPM
					/*lblPortLSPayloadName.SetBinding( Label.ContentProperty, new Binding
					{
						Source = DataContext,
						Mode = BindingMode.OneWay,
						Path = new PropertyPath( "OV.Port_PL_MPM.Payload.Name" )
					});*/
					break;
				case 3:// SPDS
					/*lblPortLSPayloadName.SetBinding( Label.ContentProperty, new Binding
					{
						Source = DataContext,
						Mode = BindingMode.OneWay,
						Path = new PropertyPath( "TODO" )
					});*/
					break;
				default:
					break;
			}
			return;
		}

		private void cbStbdLS_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			switch (cbStbdLS.SelectedIndex)
			{
				case 1:// RMS
					BindingOperations.ClearBinding( lblStbdLSPayloadName, Label.ContentProperty );
					break;
				case 2:// PL MPM
					lblStbdLSPayloadName.SetBinding( Label.ContentProperty, new Binding
					{
						Source = DataContext,
						Mode = BindingMode.OneWay,
						Path = new PropertyPath( "OV.Stbd_PL_MPM.Payload.Name" )
					});
					break;
				case 3:// SPDS
					/*lblStbdLSPayloadName.SetBinding( Label.ContentProperty, new Binding
					{
						Source = DataContext,
						Mode = BindingMode.OneWay,
						Path = new PropertyPath( "TODO" )
					});*/
					break;
				default:
					BindingOperations.ClearBinding( lblStbdLSPayloadName, Label.ContentProperty );
					break;
			}
			return;
		}

		private void btnOBSS_Click(object sender, RoutedEventArgs e)
		{
			Mission mission = (Mission)DataContext;
			mission.SetOBSS();
			return;
		}
	}
}

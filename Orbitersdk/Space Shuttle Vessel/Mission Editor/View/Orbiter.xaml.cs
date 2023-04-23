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
2020/06/30   GLS
2020/07/01   GLS
2020/07/02   GLS
2020/07/08   GLS
2020/10/06   GLS
2020/10/09   GLS
2021/11/13   GLS
2021/12/05   GLS
2021/12/19   GLS
2021/12/25   GLS
2022/01/10   GLS
2022/02/05   GLS
2022/02/07   GLS
2022/02/23   GLS
2022/02/28   GLS
2022/03/01   GLS
2022/03/02   GLS
2022/06/16   GLS
2022/06/19   GLS
2022/06/24   GLS
2022/08/05   GLS
2023/02/13   GLS
2023/02/14   GLS
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
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;


namespace SSVMissionEditor
{
	public class Convert_OV_Name : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture ) => (int)value;
		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture ) => (OV_Name)value;
	}

	public class Convert_Airlock_Type : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture ) => (int)value;
		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture ) => (Airlock_Type)value;
	}

	public class Convert_TAA_Type : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture ) => (int)value;
		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture ) => (TAA_Type)value;
	}

	/// <summary>
	/// Interaction logic for Orbiter.xaml
	/// </summary>
	public partial class Orbiter : UserControl
	{
		List<List<Tuple<string,string>>> TEXNAME_OV;
		List<Tuple<string,string>> TEXNAME_LOMS;
		List<Tuple<string,string>> TEXNAME_ROMS;

		public Orbiter()
		{
			// init OV texture list (tag,filename)
			TEXNAME_OV = new List<List<Tuple<string,string>>>
			{
				new List<Tuple<string,string>>// OV-102
				{
					Tuple.Create( "Original", "OV-102_original" ),
					Tuple.Create( "4th mod", "OV-102_4thmod" ),
					Tuple.Create( "6th mod", "OV-102_6thmod" ),
					Tuple.Create( "8th mod", "OV-102_8thmod" )
				},
				new List<Tuple<string,string>>// OV-099
				{
					Tuple.Create( "Original", "OV-099_original" )
				},
				new List<Tuple<string,string>>// OV-103
				{
					Tuple.Create( "Original", "OV-103_original" ),
					Tuple.Create( "6th mod", "OV-103_6thmod" ),
					Tuple.Create( "9th mod", "OV-103_9thmod" )
				},
				new List<Tuple<string,string>>// OV-104
				{
					Tuple.Create( "Original", "OV-104_original" ),
					Tuple.Create( "4th mod", "OV-104_4thmod" ),
					Tuple.Create( "5th mod", "OV-104_5thmod" )
				},
				new List<Tuple<string,string>>// OV-105
				{
					Tuple.Create( "Original", "OV-105_original" ),
					Tuple.Create( "3rd mod", "OV-105_3rdmod" )
				},
			};

			/**
			 * Original	1
			 * 1		2
			 * 2		6
			 * 3		9
			 * 4		41C
			 * 5		41G
			 * 6		51A
			 * 7		51B
			 **/
			// init LH OMS texture list (tag,filename)
			TEXNAME_LOMS = new List<Tuple<string,string>>
			{
				/*Tuple.Create( "Original", "OMSpod_original" ),
				Tuple.Create( "1st mod", "OMSpod_1stmod" ),
				Tuple.Create( "2nd mod", "OMSpod_2ndmod" ),
				Tuple.Create( "3rd mod", "OMSpod_3rdmod" ),
				Tuple.Create( "4th mod", "OMSpod_4thmod" ),
				Tuple.Create( "5th mod", "OMSpod_5thmod" ),
				Tuple.Create( "6th mod", "OMSpod_6thmod" ),*/
				Tuple.Create( "7th mod", "OMSpod_7thmod" )
			};

			// init RH OMS texture list (tag,filename)
			TEXNAME_ROMS = new List<Tuple<string,string>>
			{
				/*Tuple.Create( "Original", "OMSpod_original" ),
				Tuple.Create( "1st mod", "OMSpod_1stmod" ),
				Tuple.Create( "2nd mod", "OMSpod_2ndmod" ),
				Tuple.Create( "3rd mod", "OMSpod_3rdmod" ),
				Tuple.Create( "4th mod", "OMSpod_4thmod" ),
				Tuple.Create( "5th mod", "OMSpod_5thmod" ),
				Tuple.Create( "6th mod", "OMSpod_6thmod" ),*/
				Tuple.Create( "7th mod", "OMSpod_7thmod" )
			};

			InitializeComponent();

			// fill LOMS texture cb
			cbLOMStexture.Items.Clear();
			for (int i = 0; i < TEXNAME_LOMS.Count; i++)
				cbLOMStexture.Items.Add( TEXNAME_LOMS[i].Item1 );
			cbLOMStexture.Items.Add( "Custom..." );
			cbLOMStexture.SelectedIndex = 0;

			// fill ROMS texture cb
			cbROMStexture.Items.Clear();
			for (int i = 0; i < TEXNAME_ROMS.Count; i++)
				cbROMStexture.Items.Add( TEXNAME_ROMS[i].Item1 );
			cbROMStexture.Items.Add( "Custom..." );
			cbROMStexture.SelectedIndex = 0;

			// keel camera
			foreach (int x in Defs.KEEL_CAMERA)
			{
				cmbKeelCamera.Items.Add( x + " (Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] + ")" );
			}
			cmbKeelCamera.SetBinding( ComboBox.SelectedIndexProperty, new Binding
			{
				Mode = BindingMode.TwoWay,
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged,
				Path = new PropertyPath( "OV.PLB_Cameras.Keel_Cameras[0]" ),
				Converter = new Convert_PLID_idx(),
				ConverterParameter = Defs.KEEL_CAMERA
			});
		}

		private void cbOV_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			// update texture list
			cbOVtexture.Items.Clear();
			for (int i = 0; i < TEXNAME_OV[cbOV.SelectedIndex].Count; i++)
				cbOVtexture.Items.Add( TEXNAME_OV[cbOV.SelectedIndex][i].Item1 );
			cbOVtexture.Items.Add( "Custom..." );
			cbOVtexture.SelectedIndex = 0;

			// enable/disable features
			switch (cbOV.SelectedIndex)
			{
				case 0:// OV-102
					ckbSILTS.IsEnabled = true;

					ckbDFIWireTray.IsEnabled = true;

					ckbExtAL_ODS_Kit.IsEnabled = true;

					ckbFwdBulkDockLights.IsEnabled = false;
					ckbFwdBulkDockLights.IsChecked = true;

					ckbDragChute.IsEnabled = true;

					ckbVentDoors4and7.IsEnabled = true;
					break;
				case 1:// OV-099
					ckbSILTS.IsEnabled = false;

					ckbDFIWireTray.IsEnabled = false;
					ckbDFIWireTray.IsChecked = false;

					ckbExtAL_ODS_Kit.IsEnabled = false;
					ckbExtAL_ODS_Kit.IsChecked = false;

					ckbFwdBulkDockLights.IsEnabled = false;
					ckbFwdBulkDockLights.IsChecked = true;

					ckbDragChute.IsEnabled = false;
					ckbDragChute.IsChecked = false;

					ckbVentDoors4and7.IsEnabled = false;
					ckbVentDoors4and7.IsChecked = true;
					break;
				case 2:// OV-103
					ckbSILTS.IsEnabled = false;

					ckbDFIWireTray.IsEnabled = false;
					ckbDFIWireTray.IsChecked = false;

					ckbExtAL_ODS_Kit.IsEnabled = true;

					ckbFwdBulkDockLights.IsEnabled = true;

					ckbDragChute.IsEnabled = true;

					ckbVentDoors4and7.IsEnabled = true;
					break;
				case 3:// OV-104
					ckbSILTS.IsEnabled = false;

					ckbDFIWireTray.IsEnabled = false;
					ckbDFIWireTray.IsChecked = false;

					ckbExtAL_ODS_Kit.IsEnabled = true;

					ckbFwdBulkDockLights.IsEnabled = false;
					ckbFwdBulkDockLights.IsChecked = true;

					ckbDragChute.IsEnabled = true;

					ckbVentDoors4and7.IsEnabled = true;
					break;
				case 4:// OV-105
					ckbSILTS.IsEnabled = false;

					ckbDFIWireTray.IsEnabled = false;
					ckbDFIWireTray.IsChecked = false;

					ckbExtAL_ODS_Kit.IsEnabled = true;

					ckbFwdBulkDockLights.IsEnabled = true;

					ckbDragChute.IsEnabled = false;
					ckbDragChute.IsChecked = true;

					ckbVentDoors4and7.IsEnabled = true;
					break;
			}
			return;
		}

		private void cbOVtexture_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			if ((cbOVtexture.SelectedIndex + 1) == cbOVtexture.Items.Count)// "custom" is selected
			{
				txtOVtexture.IsEnabled = true;
				return;
			}
			else txtOVtexture.IsEnabled = false;

			txtOVtexture.Text = TEXNAME_OV[cbOV.SelectedIndex][cbOVtexture.SelectedIndex].Item2;
			return;
		}

		private void txtOVtexture_TextChanged(object sender, TextChangedEventArgs e)
		{
			// find texture in list and set correct index
			for (int i = 0; i < TEXNAME_OV[cbOV.SelectedIndex].Count; i++)
			{
				if (TEXNAME_OV[cbOV.SelectedIndex][i].Item2 == txtOVtexture.Text)
				{
					cbOVtexture.SelectedIndex = i;
					return;
				}
			}

			// if not found, set "custom"
			cbOVtexture.SelectedIndex = cbOVtexture.Items.Count - 1;
			return;
		}

		private void cbLOMStexture_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			if ((cbLOMStexture.SelectedIndex + 1) == cbLOMStexture.Items.Count)// "custom" is selected
			{
				txtLOMStexture.IsEnabled = true;
				return;
			}
			else txtLOMStexture.IsEnabled = false;

			txtLOMStexture.Text = TEXNAME_LOMS[cbLOMStexture.SelectedIndex].Item2;
			return;
		}

		private void txtLOMStexture_TextChanged(object sender, TextChangedEventArgs e)
		{
			// find texture in list and set correct index
			for (int i = 0; i < TEXNAME_LOMS.Count; i++)
			{
				if (TEXNAME_LOMS[i].Item2 == txtLOMStexture.Text)
				{
					cbLOMStexture.SelectedIndex = i;
					return;
				}
			}

			// if not found, set "custom"
			cbLOMStexture.SelectedIndex = cbLOMStexture.Items.Count - 1;
			return;
		}

		private void cbROMStexture_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			if ((cbROMStexture.SelectedIndex + 1) == cbROMStexture.Items.Count)// "custom" is selected
			{
				txtROMStexture.IsEnabled = true;
				return;
			}
			else txtROMStexture.IsEnabled = false;

			txtROMStexture.Text = TEXNAME_ROMS[cbROMStexture.SelectedIndex].Item2;
			return;
		}

		private void txtROMStexture_TextChanged(object sender, TextChangedEventArgs e)
		{
			// find texture in list and set correct index
			for (int i = 0; i < TEXNAME_ROMS.Count; i++)
			{
				if (TEXNAME_ROMS[i].Item2 == txtROMStexture.Text)
				{
					cbROMStexture.SelectedIndex = i;
					return;
				}
			}

			// if not found, set "custom"
			cbROMStexture.SelectedIndex = cbROMStexture.Items.Count - 1;
			return;
		}

		private void CkbExtAL_ODS_Kit_Unchecked(object sender, RoutedEventArgs e)
		{
			cbAL.IsEnabled = false;
			cbAL.SelectedIndex = 0;

			ckbODS.IsEnabled = false;
			ckbODS.IsChecked = false;
			return;
		}

		private void CkbExtAL_ODS_Kit_Checked(object sender, RoutedEventArgs e)
		{
			cbAL.IsEnabled = true;

			ckbODS.IsEnabled = true;
			return;
		}

		private void CbAL_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			if (cbAL.SelectedIndex == 0)
			{
				// internal
				if (ckbODS.IsChecked == false)
				{
					ComboBoxItem itm = (ComboBoxItem)cbTAA.Items[2];// aft
					if (itm != null) itm.IsEnabled = false;
					if (cbTAA.SelectedIndex == 2) cbTAA.SelectedIndex = 0;
				}
			}
			else
			{
				// external
				ComboBoxItem itm = (ComboBoxItem)cbTAA.Items[2];// aft
				if (itm != null) itm.IsEnabled = true;
			}
			return;
		}

		private void CkbODS_Unchecked(object sender, RoutedEventArgs e)
		{
			if (cbAL.SelectedIndex == 0)
			{
				// internal
				ComboBoxItem itm = (ComboBoxItem)cbTAA.Items[2];// aft
				if (itm != null) itm.IsEnabled = false;
				if (cbTAA.SelectedIndex == 2) cbTAA.SelectedIndex = 0;
			}
			return;
		}

		private void CkbODS_Checked(object sender, RoutedEventArgs e)
		{
			ComboBoxItem itm = (ComboBoxItem)cbTAA.Items[2];// aft
			if (itm != null) itm.IsEnabled = true;
			return;
		}

		private void CmdCCTV_Click(object sender, RoutedEventArgs e)
		{
			string bind = "";
			if (sender == cmdCCTVA)
			{
				bind = "[0]";
			}
			else if (sender == cmdCCTVB)
			{
				bind = "[1]";
			}
			else if (sender == cmdCCTVC)
			{
				bind = "[2]";
			}
			else if (sender == cmdCCTVD)
			{
				bind = "[3]";
			}
			else return;

			EditPLBCamera cctv = new EditPLBCamera( DataContext, bind );
			cctv.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
			cctv.ShowDialog();
			return;
		}

		private void ckbCCTV_Checked(object sender, RoutedEventArgs e)
		{
			if (sender == ckbCCTVA)
			{
				cmdCCTVA.IsEnabled = true;
			}
			else if (sender == ckbCCTVB)
			{
				cmdCCTVB.IsEnabled = true;
			}
			else if (sender == ckbCCTVC)
			{
				cmdCCTVC.IsEnabled = true;
			}
			else if (sender == ckbCCTVD)
			{
				cmdCCTVD.IsEnabled = true;
			}
			return;
		}

		private void ckbCCTV_Unchecked(object sender, RoutedEventArgs e)
		{
			if (sender == ckbCCTVA)
			{
				cmdCCTVA.IsEnabled = false;
			}
			else if (sender == ckbCCTVB)
			{
				cmdCCTVB.IsEnabled = false;
			}
			else if (sender == ckbCCTVC)
			{
				cmdCCTVC.IsEnabled = false;
			}
			else if (sender == ckbCCTVD)
			{
				cmdCCTVD.IsEnabled = false;
			}
			return;
		}

		private void ckbKeelCamera_Checked(object sender, RoutedEventArgs e)
		{
			cmbKeelCamera.IsEnabled = true;
			return;
		}

		private void ckbKeelCamera_Unchecked(object sender, RoutedEventArgs e)
		{
			cmbKeelCamera.IsEnabled = false;
			return;
		}
	}
}

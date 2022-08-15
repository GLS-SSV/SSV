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
2020/06/30   GLS
2020/07/01   GLS
2020/07/08   GLS
2021/08/08   GLS
2021/12/09   GLS
2021/12/10   GLS
2021/12/25   GLS
2022/06/24   GLS
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

using System;
using System.Collections.Generic;
using System.Windows.Controls;
using System.Windows.Data;
using SSVMissionEditor.model;


namespace SSVMissionEditor
{
	public class Convert_ET_Type : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture ) => (int)value;
		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture ) => (ET_Type)value;
	}

	public class Convert_SRM_Type : IValueConverter
	{
		public object Convert( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture ) => (int)value;
		public object ConvertBack( object value, Type targetType, object parameter, System.Globalization.CultureInfo culture ) => (SRM_Type)value;
	}

	/// <summary>
	/// Interaction logic for ETSRB.xaml
	/// </summary>
	public partial class ETSRB : UserControl
	{
		List<List<Tuple<string,string>>> TEXNAME_LH_SRB_FWDASSEMBLY;
		List<List<Tuple<string,string>>> TEXNAME_RH_SRB_FWDASSEMBLY;
		List<List<Tuple<string,string>>> TEXNAME_LH_SRB_CASE;
		List<List<Tuple<string,string>>> TEXNAME_RH_SRB_CASE;

		public ETSRB()
		{
			/**
			 * Original	1
			 * 1		2
			 * 2		41C
			 * 3		41D
			 * 4		61
			 * 5		90
			 **/
			// init LH SRB fwd assembly texture list (tag,filename)
			TEXNAME_LH_SRB_FWDASSEMBLY = new List<List<Tuple<string,string>>>
			{
				new List<Tuple<string,string>>// SPM
				{
					//Tuple.Create( "Original", "fwd_assembly_original" ),
					Tuple.Create( "1st mod", "fwd_assembly_1stmod" )
				},
				new List<Tuple<string,string>>// HPM
				{
					Tuple.Create( "1st mod", "fwd_assembly_1stmod" ),
					//Tuple.Create( "2nd mod", "LH_fwd_assembly_2ndmod" ),
					Tuple.Create( "3rd mod", "LH_fwd_assembly_3rdmod" )
				},
				new List<Tuple<string,string>>// FWC
				{
					Tuple.Create( "3rd mod", "LH_fwd_assembly_3rdmod" )
				},
				new List<Tuple<string,string>>// RSRM
				{
					Tuple.Create( "3rd mod", "LH_fwd_assembly_3rdmod" ),
					Tuple.Create( "4th mod", "LH_fwd_assembly_4thmod" ),
					Tuple.Create( "5th mod", "LH_fwd_assembly_5thmod" )
				}
			};

			// init RH SRB fwd assembly texture list (tag,filename)
			TEXNAME_RH_SRB_FWDASSEMBLY = new List<List<Tuple<string,string>>>
			{
				new List<Tuple<string,string>>// SPM
				{
					//Tuple.Create( "Original", "fwd_assembly_original" ),
					Tuple.Create( "1st mod", "fwd_assembly_1stmod" )
				},
				new List<Tuple<string,string>>// HPM
				{
					Tuple.Create( "1st mod", "fwd_assembly_1stmod" ),
					//Tuple.Create( "2nd mod", "RH_fwd_assembly_2ndmod" ),
					Tuple.Create( "3rd mod", "RH_fwd_assembly_3rdmod" )
				},
				new List<Tuple<string,string>>// FWC
				{
					Tuple.Create( "3rd mod", "RH_fwd_assembly_3rdmod" )
				},
				new List<Tuple<string,string>>// RSRM
				{
					Tuple.Create( "3rd mod", "RH_fwd_assembly_3rdmod" ),
					Tuple.Create( "4th mod", "RH_fwd_assembly_4thmod" ),
					Tuple.Create( "5th mod", "RH_fwd_assembly_5thmod" )
				}
			};

			/**
			 * Original	1
			 * 1		2
			 * 2		6
			 * 3		9
			 * 4		51D
			 * 5		51I
			 * 6		51L
			 * 7		62A
			 * 8		26R
			 * 9		60
			 **/
			// init LH SRB case texture list (tag,filename)
			TEXNAME_LH_SRB_CASE = new List<List<Tuple<string,string>>>
			{
				new List<Tuple<string,string>>// SPM
				{
					//Tuple.Create( "Original", "case_original" ),
					Tuple.Create( "1st mod", "case_1stmod" ),
					Tuple.Create( "2nd mod", "case_2ndmod" )
				},
				new List<Tuple<string,string>>// HPM
				{
					Tuple.Create( "3rd mod", "case_3rdmod" ),
					Tuple.Create( "4th mod", "case_4thmod" ),
					//Tuple.Create( "5th mod", "case_5thmod" ),
					//Tuple.Create( "6th mod", "case_6thmod" )
				},
				new List<Tuple<string,string>>// FWC
				{
					Tuple.Create( "7th mod", "case_7thmod" )
				},
				new List<Tuple<string,string>>// RSRM
				{
					Tuple.Create( "8th mod", "case_8thmod" ),
					Tuple.Create( "9th mod", "case_9thmod" )
				}
			};

			// init RH SRB case texture list (tag,filename)
			TEXNAME_RH_SRB_CASE = new List<List<Tuple<string,string>>>
			{
				new List<Tuple<string,string>>// SPM
				{
					//Tuple.Create( "Original", "case_original" ),
					Tuple.Create( "1st mod", "case_1stmod" ),
					Tuple.Create( "2nd mod", "case_2ndmod" )
				},
				new List<Tuple<string,string>>// HPM
				{
					Tuple.Create( "3rd mod", "case_3rdmod" ),
					Tuple.Create( "4th mod", "case_4thmod" ),
					//Tuple.Create( "5th mod", "case_5thmod" ),
					//Tuple.Create( "6th mod", "case_6thmod" )
				},
				new List<Tuple<string,string>>// FWC
				{
					Tuple.Create( "7th mod", "case_7thmod" )
				},
				new List<Tuple<string,string>>// RSRM
				{
					Tuple.Create( "8th mod", "case_8thmod" ),
					Tuple.Create( "9th mod", "case_9thmod" )
				}
			};

			InitializeComponent();
		}

		//// ET ////
		private void cbET_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			cbETtexture_Update();
			return;
		}

		private void txtETtexture_TextChanged(object sender, TextChangedEventArgs e)
		{
			// find texture in list and set correct index
			string tex;

			switch (cbET.SelectedIndex)
			{
				case (int)ET_Type.SWT:
					if (ckbFRL.IsChecked == false) tex = "SWT";
					else tex = "SWT_FRL";
					break;
				case (int)ET_Type.LWT:
					tex = "LWT";
					break;
				//case (int)ET_Type.SLWT:
				default:
					tex = "SLWT";
					break;
			}

			if (tex == txtETtexture.Text) cbETtexture.SelectedIndex = 0;
			else cbETtexture.SelectedIndex = cbETtexture.Items.Count - 1;// "custom"
			return;
		}

		private void cbETtexture_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			if ((cbETtexture.SelectedIndex + 1) == cbETtexture.Items.Count)// "custom" is selected
			{
				txtETtexture.IsEnabled = true;
				return;
			}
			else txtETtexture.IsEnabled = false;


			// show default texture
			switch (cbET.SelectedIndex)
			{
				case (int)ET_Type.SWT:
					if (ckbFRL.IsChecked == false) txtETtexture.Text = "SWT";
					else txtETtexture.Text = "SWT_FRL";
					break;
				case (int)ET_Type.LWT:
					txtETtexture.Text = "LWT";
					break;
				//case (int)ET_Type.SLWT:
				default:
					txtETtexture.Text = "SLWT";
					break;
			}
			return;
		}

		private void ckbFRL_Checked(object sender, System.Windows.RoutedEventArgs e)
		{
			cbETtexture_Update();
			return;
		}

		private void ckbFRL_Unchecked(object sender, System.Windows.RoutedEventArgs e)
		{
			cbETtexture_Update();
			return;
		}

		private void cbETtexture_Update()
		{
			cbETtexture.Items.Clear();

			switch (cbET.SelectedIndex)
			{
				case (int)ET_Type.SWT:
					ckbFRL.IsEnabled = true;
					ckbBipod.IsEnabled = false;
					ckbPAL.IsEnabled = false;
					if (ckbFRL.IsChecked == false) cbETtexture.Items.Add( "SWT" );
					else cbETtexture.Items.Add( "SWT_FRL" );
					cbETtexture.Items.Add( "Custom..." );
					cbETtexture.SelectedIndex = 0;
					break;
				case (int)ET_Type.LWT:
					ckbFRL.IsEnabled = false;
					ckbFRL.IsChecked = false;
					ckbBipod.IsEnabled = false;
					ckbPAL.IsEnabled = false;
					cbETtexture.Items.Add( "LWT" );
					cbETtexture.Items.Add( "Custom..." );
					cbETtexture.SelectedIndex = 0;
					break;
				case (int)ET_Type.SLWT:
					ckbFRL.IsEnabled = false;
					ckbFRL.IsChecked = false;
					ckbBipod.IsEnabled = true;
					ckbPAL.IsEnabled = true;
					cbETtexture.Items.Add( "SLWT" );
					cbETtexture.Items.Add( "Custom..." );
					cbETtexture.SelectedIndex = 0;
					break;
			}
			return;
		}


		//// SRB ////
		private void cbSRM_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			cbLHSRBtextureFwdAssembly_Update();
			cbRHSRBtextureFwdAssembly_Update();
			cbLHSRBtextureCase_Update();
			cbRHSRBtextureCase_Update();
			return;
		}

		//// SRB Fwd Assembly ////
		private void txtLHSRBtextureFwdAssembly_TextChanged(object sender, TextChangedEventArgs e)
		{
			// find texture in list and set correct index
			for (int i = 0; i < TEXNAME_LH_SRB_FWDASSEMBLY[cbSRM.SelectedIndex].Count; i++)
			{
				if (TEXNAME_LH_SRB_FWDASSEMBLY[cbSRM.SelectedIndex][i].Item2 == txtLHSRBtextureFwdAssembly.Text)
				{
					cbLHSRBtextureFwdAssembly.SelectedIndex = i;
					return;
				}
			}

			// if not found, set "custom"
			cbLHSRBtextureFwdAssembly.SelectedIndex = cbLHSRBtextureFwdAssembly.Items.Count - 1;
			return;
		}

		private void txtRHSRBtextureFwdAssembly_TextChanged(object sender, TextChangedEventArgs e)
		{
			// find texture in list and set correct index
			for (int i = 0; i < TEXNAME_RH_SRB_FWDASSEMBLY[cbSRM.SelectedIndex].Count; i++)
			{
				if (TEXNAME_RH_SRB_FWDASSEMBLY[cbSRM.SelectedIndex][i].Item2 == txtRHSRBtextureFwdAssembly.Text)
				{
					cbRHSRBtextureFwdAssembly.SelectedIndex = i;
					return;
				}
			}

			// if not found, set "custom"
			cbRHSRBtextureFwdAssembly.SelectedIndex = cbRHSRBtextureFwdAssembly.Items.Count - 1;
			return;
		}

		private void cbLHSRBtextureFwdAssembly_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			if ((cbLHSRBtextureFwdAssembly.SelectedIndex + 1) == cbLHSRBtextureFwdAssembly.Items.Count)// "custom" is selected
			{
				txtLHSRBtextureFwdAssembly.IsEnabled = true;
				return;
			}
			else txtLHSRBtextureFwdAssembly.IsEnabled = false;

			txtLHSRBtextureFwdAssembly.Text = TEXNAME_LH_SRB_FWDASSEMBLY[cbSRM.SelectedIndex][cbLHSRBtextureFwdAssembly.SelectedIndex].Item2;
			return;
		}

		private void cbRHSRBtextureFwdAssembly_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			if ((cbRHSRBtextureFwdAssembly.SelectedIndex + 1) == cbRHSRBtextureFwdAssembly.Items.Count)// "custom" is selected
			{
				txtRHSRBtextureFwdAssembly.IsEnabled = true;
				return;
			}
			else txtRHSRBtextureFwdAssembly.IsEnabled = false;

			txtRHSRBtextureFwdAssembly.Text = TEXNAME_RH_SRB_FWDASSEMBLY[cbSRM.SelectedIndex][cbRHSRBtextureFwdAssembly.SelectedIndex].Item2;
			return;
		}

		private void cbLHSRBtextureFwdAssembly_Update()
		{
			// update texture list
			cbLHSRBtextureFwdAssembly.Items.Clear();
			for (int i = 0; i < TEXNAME_LH_SRB_FWDASSEMBLY[cbSRM.SelectedIndex].Count; i++)
				cbLHSRBtextureFwdAssembly.Items.Add( TEXNAME_LH_SRB_FWDASSEMBLY[cbSRM.SelectedIndex][i].Item1 );
			cbLHSRBtextureFwdAssembly.Items.Add( "Custom..." );
			cbLHSRBtextureFwdAssembly.SelectedIndex = 0;
			return;
		}

		private void cbRHSRBtextureFwdAssembly_Update()
		{
			// update texture list
			cbRHSRBtextureFwdAssembly.Items.Clear();
			for (int i = 0; i < TEXNAME_RH_SRB_FWDASSEMBLY[cbSRM.SelectedIndex].Count; i++)
				cbRHSRBtextureFwdAssembly.Items.Add( TEXNAME_RH_SRB_FWDASSEMBLY[cbSRM.SelectedIndex][i].Item1 );
			cbRHSRBtextureFwdAssembly.Items.Add( "Custom..." );
			cbRHSRBtextureFwdAssembly.SelectedIndex = 0;
			return;
		}


		//// SRB Case ////
		private void txtLHSRBtextureCase_TextChanged(object sender, TextChangedEventArgs e)
		{
			// find texture in list and set correct index
			for (int i = 0; i < TEXNAME_LH_SRB_CASE[cbSRM.SelectedIndex].Count; i++)
			{
				if (TEXNAME_LH_SRB_CASE[cbSRM.SelectedIndex][i].Item2 == txtLHSRBtextureCase.Text)
				{
					cbLHSRBtextureCase.SelectedIndex = i;
					return;
				}
			}

			// if not found, set "custom"
			cbLHSRBtextureCase.SelectedIndex = cbLHSRBtextureCase.Items.Count - 1;
			return;
		}

		private void txtRHSRBtextureCase_TextChanged(object sender, TextChangedEventArgs e)
		{
			// find texture in list and set correct index
			for (int i = 0; i < TEXNAME_RH_SRB_CASE[cbSRM.SelectedIndex].Count; i++)
			{
				if (TEXNAME_RH_SRB_CASE[cbSRM.SelectedIndex][i].Item2 == txtRHSRBtextureCase.Text)
				{
					cbRHSRBtextureCase.SelectedIndex = i;
					return;
				}
			}

			// if not found, set "custom"
			cbRHSRBtextureCase.SelectedIndex = cbRHSRBtextureCase.Items.Count - 1;
			return;
		}

		private void cbLHSRBtextureCase_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			if ((cbLHSRBtextureCase.SelectedIndex + 1) == cbLHSRBtextureCase.Items.Count)// "custom" is selected
			{
				txtLHSRBtextureCase.IsEnabled = true;
				return;
			}
			else txtLHSRBtextureCase.IsEnabled = false;

			txtLHSRBtextureCase.Text = TEXNAME_LH_SRB_CASE[cbSRM.SelectedIndex][cbLHSRBtextureCase.SelectedIndex].Item2;
			return;
		}

		private void cbRHSRBtextureCase_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			if ((cbRHSRBtextureCase.SelectedIndex + 1) == cbRHSRBtextureCase.Items.Count)// "custom" is selected
			{
				txtRHSRBtextureCase.IsEnabled = true;
				return;
			}
			else txtRHSRBtextureCase.IsEnabled = false;

			txtRHSRBtextureCase.Text = TEXNAME_RH_SRB_CASE[cbSRM.SelectedIndex][cbRHSRBtextureCase.SelectedIndex].Item2;
			return;
		}

		private void cbLHSRBtextureCase_Update()
		{
			// update texture list
			cbLHSRBtextureCase.Items.Clear();
			for (int i = 0; i < TEXNAME_LH_SRB_CASE[cbSRM.SelectedIndex].Count; i++)
				cbLHSRBtextureCase.Items.Add( TEXNAME_LH_SRB_CASE[cbSRM.SelectedIndex][i].Item1 );
			cbLHSRBtextureCase.Items.Add( "Custom..." );
			cbLHSRBtextureCase.SelectedIndex = 0;
			return;
		}

		private void cbRHSRBtextureCase_Update()
		{
			// update texture list
			cbRHSRBtextureCase.Items.Clear();
			for (int i = 0; i < TEXNAME_RH_SRB_CASE[cbSRM.SelectedIndex].Count; i++)
				cbRHSRBtextureCase.Items.Add( TEXNAME_RH_SRB_CASE[cbSRM.SelectedIndex][i].Item1 );
			cbRHSRBtextureCase.Items.Add( "Custom..." );
			cbRHSRBtextureCase.SelectedIndex = 0;
			return;
		}
	}
}

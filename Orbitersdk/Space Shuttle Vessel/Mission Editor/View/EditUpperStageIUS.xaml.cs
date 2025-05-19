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
using System.Windows.Input;


namespace SSVMissionEditor
{
	/// <summary>
	/// Interaction logic for EditUpperStageIUS.xaml
	/// </summary>
	public partial class EditUpperStageIUS : Window
	{
		double load1 = 1;
		double load2 = 1;

		public EditUpperStageIUS( object datacontext )
		{
			InitializeComponent();

			radOrbital.IsChecked = true;

			DataContext = datacontext;
		}

		private void CommandBinding_Executed( object sender, ExecutedRoutedEventArgs e )
		{
			Close();
			return;
		}

		private void CmdCalc_Click(object sender, RoutedEventArgs e)
		{
			string result = "";
			PropCalc pc = new PropCalc();

			try
			{
				double Altcur = Convert.ToDouble( txtAltcur.Text );
				if (Altcur <= 175)// ~95NM
				{
					txtResult.Text = "invalid current altitude";
					return;
				}
				double PLmass = Convert.ToDouble( txtPLmass.Text );
				if (PLmass <= 0)
				{
					txtResult.Text = "invalid payload mass";
					return;
				}
				int RCSTanks = Convert.ToInt32( txtRCSTanks.Text );
				if ((RCSTanks < 1) || (RCSTanks > 3))
				{
					txtResult.Text = "invalid RCS tanks";
					return;
				}
				if (radOrbital.IsChecked == true)
				{
					double Alttgt = Convert.ToDouble( txtAlttgt.Text );
					if (Alttgt <= Altcur)
					{
						txtResult.Text = "invalid target altitude";
						return;
					}
					double dInc1 = Convert.ToDouble( txtdInc1.Text );
					double dInc2 = Convert.ToDouble( txtdInc2.Text );
					pc.IUS_Orbital( Altcur, Alttgt, dInc1, dInc2, PLmass, RCSTanks, true, ref load1, ref load2, ref result );
				}
				else
				{
					double C3tgt = Convert.ToDouble( txtC3tgt.Text );
					pc.IUS_Escape( Altcur, C3tgt, PLmass, RCSTanks, true, ref load1, ref load2, ref result );
				}

				txtResult.Text = result;
			}
			catch (Exception)
			{
				txtResult.Text = "error";
			}
			return;
		}

		private void CmdSave_Click(object sender, RoutedEventArgs e)
		{
			txtLoad1Stage.Text = Math.Round( load1, 2 ).ToString();
			txtLoad2Stage.Text = Math.Round( load2, 2 ).ToString();
			return;
		}

		private void radOrbital_Checked(object sender, RoutedEventArgs e)
		{
			txtAlttgt.IsEnabled = true;
			txtdInc1.IsEnabled = true;
			txtdInc2.IsEnabled = true;
			txtC3tgt.IsEnabled = false;
			return;
		}

		private void radEscape_Checked(object sender, RoutedEventArgs e)
		{
			txtAlttgt.IsEnabled = false;
			txtdInc1.IsEnabled = false;
			txtdInc2.IsEnabled = false;
			txtC3tgt.IsEnabled = true;
			return;
		}
	}
}

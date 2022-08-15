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
2020/05/25   GLS
2020/05/31   GLS
2020/07/01   GLS
2020/07/03   GLS
2021/12/25   GLS
2022/06/24   GLS
2022/08/05   GLS
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
using System.Windows.Threading;
using System.Windows;
using System.Windows.Controls.Ribbon;
using System.Windows.Input;
using Microsoft.Win32;


namespace SSVMissionEditor
{
	/// <summary>
	/// Interaction logic for ScenarioWindow.xaml
	/// </summary>
	public partial class ScenarioWindow : RibbonWindow
	{
		string orbiterpath;
		internal model.Scenario Scenario { get; private set; }
		private DispatcherTimer tmr;


		public ScenarioWindow( model.Scenario scn, string orbiterpath )
		{
			InitializeComponent();
			this.Owner = App.Current.MainWindow;

			Scenario = scn;
			this.orbiterpath = orbiterpath;

			DataContext = Scenario;// load to screen

			tmr = new DispatcherTimer();

			tmr.Tick += tmrTick;
			tmr.Interval = new TimeSpan( 0, 0, 3 );
		}

		private void ExportScenario()
		{
			// export current mission to scenario
			SaveFileDialog savefiledialog = new SaveFileDialog
			{
				Title = "Export Scenario File...",
				Filter = "Scenario files (*.scn)|*.scn",
				InitialDirectory = orbiterpath + "Scenarios\\Space Shuttle Vessel"
			};

			if (savefiledialog.ShowDialog() == true)
			{
				try
				{
					Scenario.Save( savefiledialog.FileName );
				}
				catch (Exception ex)
				{
					MessageBox.Show( ex.ToString(), "Error saving scenario!!!", MessageBoxButton.OK, MessageBoxImage.Error );
					return;
				}
				SetStatusTextLeft( "File \"" + savefiledialog.FileName + "\" saved successfully!" );
			}
			return;
		}

		private void RibbonExport_Click(object sender, RoutedEventArgs e)
		{
			ExportScenario();
			return;
		}

		private void RibbonClose_Click(object sender, RoutedEventArgs e)
		{
			this.Close();
			return;
		}

		protected override void OnPreviewKeyDown( KeyEventArgs e )
		{
			if ((e.Key == Key.E) && (Keyboard.IsKeyDown( Key.LeftCtrl ) || Keyboard.IsKeyDown( Key.RightCtrl )))
			{
				ExportScenario();
				e.Handled = true;
			}

			base.OnPreviewKeyDown(e);
			return;
		}

		private void SetStatusTextLeft( string text )
		{
			lblStatusLeft.Text = text;
			tmr.Start();
			return;
		}

		private void tmrTick(Object source, EventArgs e)
		{
			tmr.Stop();
			lblStatusLeft.Text = "";
			return;
		}
	}
}

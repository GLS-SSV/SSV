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
2020/06/28   GLS
2020/07/01   GLS
2020/07/03   GLS
2021/12/25   GLS
2021/12/26   GLS
2022/01/10   GLS
2022/03/02   GLS
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
using SSVMissionEditor.model;


namespace SSVMissionEditor
{
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : RibbonWindow
	{
		private const string vesselconfigpath = "Config\\Vessels\\";
		private const string missionpath = "Missions\\SSV\\";

		private string orbiterpath;
		internal Mission mission { get; private set; }
		private DispatcherTimer tmr;


		public MainWindow()
		{
			InitializeComponent();

			// we want the orbiter.exe so we open the missions folder and scenario folder
			if (GetOrbiterPath() == false) Environment.Exit( 0 );

			tmr = new DispatcherTimer();

			tmr.Tick += tmrTick;
			tmr.Interval = new TimeSpan( 0, 0, 3 );

			// display orbiter path in title bar
			Title = "SSV Mission Editor - " + orbiterpath;
		}

		private bool GetOrbiterPath()
		{
			// first check if a path has been saved, and if orbiter.exe still exists in there
			string tmp = Properties.Settings.Default.orbiterexepath;
			if (tmp.Length  > 0)
			{
				if (System.IO.File.Exists( tmp + "orbiter.exe" ))
				{
					orbiterpath = tmp;
					return true;
				}
			}

			// make user find orbiter.exe
			return OrbiterPathDialog();
		}

		private bool OrbiterPathDialog()
		{
			OpenFileDialog openfiledialog = new OpenFileDialog
			{
				Title = "Locate orbiter.exe...",
				Filter = "Orbiter executable (orbiter.exe)|orbiter.exe",
				InitialDirectory = orbiterpath
			};

			if (openfiledialog.ShowDialog() == true)
			{
				orbiterpath = openfiledialog.FileName.Substring( 0, openfiledialog.FileName.LastIndexOf( "\\" ) + 1 );
				// save
				Properties.Settings.Default.orbiterexepath = orbiterpath;
				Properties.Settings.Default.Save();
				return true;
			}
			return false;
		}

		private void NewMission()
		{
			// load STS-101 mission
			try
			{
				mission = new Mission( orbiterpath + vesselconfigpath );
			}
			catch (Exception ex)
			{
				MessageBox.Show( ex.ToString(), "Error creating mission!!!", MessageBoxButton.OK, MessageBoxImage.Error );
				return;
			}
			DataContext = mission;// load to screen
			tcTabs.IsEnabled = true;// enable editing
			return;
		}

		private void OpenMission()
		{
			// open existing mission file
			OpenFileDialog openfiledialog = new OpenFileDialog
			{
				Title = "Open Mission File...",
				Filter = "Mission files (*.json)|*.json|All files (*.*)|*.*",
				InitialDirectory = orbiterpath + missionpath
			};

			if (openfiledialog.ShowDialog() == true)
			{
				// check file inside Missions\SSV
				if (openfiledialog.FileName.Contains( orbiterpath + missionpath ) == false)
				{
					MessageBox.Show( "Mission files must be located inside the " + missionpath + " folder!" );
					return;
				}

				try
				{
					mission = new Mission( orbiterpath + vesselconfigpath );
				}
				catch (Exception ex)
				{
					MessageBox.Show( ex.ToString(), "Error creating mission!!!", MessageBoxButton.OK, MessageBoxImage.Error );
					return;
				}
				try
				{
					mission.Load( openfiledialog.FileName );
				}
				catch (Exception ex)
				{
					MessageBox.Show( ex.ToString(), "Error loading mission!!!", MessageBoxButton.OK, MessageBoxImage.Error );
					return;
				}

				mission.MissionFile = openfiledialog.FileName.Substring( (orbiterpath + missionpath).Length, openfiledialog.FileName.Length - (orbiterpath + missionpath).Length - 5 );// save mission file name (and path from Missions\SSV)
				DataContext = mission;// load to screen
				tcTabs.IsEnabled = true;// enable editing

				SetStatusTextLeft( "File \"" + openfiledialog.FileName + "\" loaded successfully!" );
			}
			return;
		}

		private void SaveMission()
		{
			if (mission == null)
			{
				MessageBox.Show( "no mission!" );
				return;
			}

			// save the loaded mission into file
			SaveFileDialog savefiledialog = new SaveFileDialog
			{
				Title = "Save Mission File...",
				Filter = "Mission files (*.json)|*.json",
				InitialDirectory = orbiterpath + missionpath,
				FileName = mission.Name
			};

			if (savefiledialog.ShowDialog() == true)
			{
				// check file inside Missions\SSV
				if (savefiledialog.FileName.Contains( orbiterpath + missionpath ) == false)
				{
					MessageBox.Show( "Mission files must be located inside the " + missionpath + " folder!" );
					return;
				}

				try
				{
					mission.Save( savefiledialog.FileName );
				}
				catch (Exception ex)
				{
					MessageBox.Show( ex.ToString(), "Error saving mission!!!", MessageBoxButton.OK, MessageBoxImage.Error );
					return;
				}

				mission.MissionFile = savefiledialog.FileName.Substring( (orbiterpath + missionpath).Length, savefiledialog.FileName.Length - (orbiterpath + missionpath).Length - 5 );// save mission file name (and path from Missions\SSV)

				SetStatusTextLeft( "File \"" + savefiledialog.FileName + "\" saved successfully!" );
			}
			return;
		}

		private void TestMission()
		{
			if (mission == null)
			{
				MessageBox.Show( "No mission!", "Mission test", MessageBoxButton.OK, MessageBoxImage.Exclamation );
				return;
			}

			string str = "";
			if (mission.Test( ref str ))
			{
				// ok
				MessageBox.Show( "No issues!", "Mission test", MessageBoxButton.OK, MessageBoxImage.Information );
			}
			else
			{
				// problems
				MessageBox.Show( str, "Mission test found problems!", MessageBoxButton.OK, MessageBoxImage.Error );
			}
			return;
		}

		protected override void OnPreviewKeyDown(KeyEventArgs e)
		{
			if ((e.Key == Key.N) && (Keyboard.IsKeyDown( Key.LeftCtrl ) || Keyboard.IsKeyDown( Key.RightCtrl )))
			{
				NewMission();
				e.Handled = true;
			}
			else if ((e.Key == Key.O) && (Keyboard.IsKeyDown( Key.LeftCtrl ) || Keyboard.IsKeyDown( Key.RightCtrl )))
			{
				OpenMission();
				e.Handled = true;
			}
			else if ((e.Key == Key.S) && (Keyboard.IsKeyDown( Key.LeftCtrl ) || Keyboard.IsKeyDown( Key.RightCtrl )))
			{
				SaveMission();
				e.Handled = true;
			}
			else if ((e.Key == Key.T) && (Keyboard.IsKeyDown( Key.LeftCtrl ) || Keyboard.IsKeyDown( Key.RightCtrl )))
			{
				TestMission();
				e.Handled = true;
			}

			base.OnPreviewKeyDown(e);
			return;
		}

		private void ribbonNew_Click(object sender, RoutedEventArgs e)
		{
			NewMission();
			return;
		}

		private void ribbonOpen_Click(object sender, RoutedEventArgs e)
		{
			OpenMission();
			return;
		}

		private void ribbonSave_Click(object sender, RoutedEventArgs e)
		{
			SaveMission();
			return;
		}

		private void ribbonTest_Click(object sender, RoutedEventArgs e)
		{
			TestMission();
			return;
		}

		private void ribbonChangeOrbiterPath_Click(object sender, RoutedEventArgs e)
		{
			// dialog to change orbiter.exe path
			OrbiterPathDialog();

			// display orbiter path in title bar
			Title = "SSV Mission Editor - " + orbiterpath;
			return;
		}

		private void ribbonAbout_Click(object sender, RoutedEventArgs e)
		{
			AboutBox box = new AboutBox();
			box.ShowDialog();
			return;
		}

		private void ribbonClose_Click(object sender, RoutedEventArgs e)
		{
			Environment.Exit( 0 );//Windows.Forms.Application.Exit();
			return;
		}

		private void rbtnCreate_Click(object sender, RoutedEventArgs e)
		{
			if (mission == null)
			{
				MessageBox.Show( "No mission exists!" );
				return;
			}

			if (mission.MissionFile == null)
			{
				MessageBox.Show( "Mission not saved!" );
				return;
			}

			model.Scenario scn;
			try
			{
				scn = new model.Scenario( mission );
			}
			catch (Exception ex)
			{
				MessageBox.Show( ex.ToString(), "Error creating scenario!!!", MessageBoxButton.OK, MessageBoxImage.Error );
				return;
			}
			ScenarioWindow scnwin = new ScenarioWindow( scn, orbiterpath );
			scnwin.ShowDialog();
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

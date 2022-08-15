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
2020/07/01   GLS
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

using System.Windows.Controls;


namespace SSVMissionEditor
{
	/// <summary>
	/// Interaction logic for Scenario.xaml
	/// </summary>
	public partial class Scenario : UserControl
	{
		public Scenario()
		{
			InitializeComponent();
		}

		private void cbCameraMode_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			if (cbCameraMode.SelectedIndex == 0)// Cockpit
			{
				cbCameraTrackMode.IsEnabled = false;
				cbCameraTrackMode.SelectedIndex = 0;

				txtCameraVesselRadius.IsEnabled = false;
				txtCameraPosY.IsEnabled = false;
				txtCameraPosZ.IsEnabled = false;
			}
			else// Extern
			{
				cbCameraTrackMode.IsEnabled = true;
				cbCameraTrackMode.SelectedIndex = 0;

				txtCameraVesselRadius.IsEnabled = true;
				txtCameraPosY.IsEnabled = true;
				txtCameraPosZ.IsEnabled = true;
			}
			return;
		}

		private void cbCameraTrackMode_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			switch (cbCameraTrackMode.SelectedIndex)
			{
				case 0:// TargetRelative
					txtCameraTrackModeRef.IsEnabled = false;

					ckbTargetLock.IsEnabled = false;
					ckbTargetLock.IsChecked = true;

					txtCameraGrPosLon.IsEnabled = false;
					txtCameraGrPosLat.IsEnabled = false;
					txtCameraGrPosAlt.IsEnabled = false;

					lblCameraPosY.Content = "Vessel Beta";
					lblCameraPosZ.Content = "Vessel Alpha";
					break;
				case 1:// AbsoluteDirection
					txtCameraTrackModeRef.IsEnabled = false;

					ckbTargetLock.IsEnabled = false;
					ckbTargetLock.IsChecked = true;

					txtCameraGrPosLon.IsEnabled = false;
					txtCameraGrPosLat.IsEnabled = false;
					txtCameraGrPosAlt.IsEnabled = false;

					lblCameraPosY.Content = "Vessel Beta";
					lblCameraPosZ.Content = "Vessel Alpha";
					break;
				case 2:// GlobalFrame
					txtCameraTrackModeRef.IsEnabled = false;

					ckbTargetLock.IsEnabled = false;
					ckbTargetLock.IsChecked = true;

					txtCameraGrPosLon.IsEnabled = false;
					txtCameraGrPosLat.IsEnabled = false;
					txtCameraGrPosAlt.IsEnabled = false;

					lblCameraPosY.Content = "Ecliptic Longitude";
					lblCameraPosZ.Content = "Ecliptic Latitude";
					break;
				case 3:// TargetTo
					txtCameraTrackModeRef.IsEnabled = true;

					ckbTargetLock.IsEnabled = false;
					ckbTargetLock.IsChecked = true;

					txtCameraGrPosLon.IsEnabled = false;
					txtCameraGrPosLat.IsEnabled = false;
					txtCameraGrPosAlt.IsEnabled = false;

					lblCameraPosY.Content = "Vessel Beta";
					lblCameraPosZ.Content = "Vessel Alpha";
					break;
				case 4:// TargetFrom
					txtCameraTrackModeRef.IsEnabled = true;

					ckbTargetLock.IsEnabled = false;
					ckbTargetLock.IsChecked = true;

					txtCameraGrPosLon.IsEnabled = false;
					txtCameraGrPosLat.IsEnabled = false;
					txtCameraGrPosAlt.IsEnabled = false;

					lblCameraPosY.Content = "Vessel Beta";
					lblCameraPosZ.Content = "Vessel Alpha";
					break;
				case 5:// Ground
					txtCameraTrackModeRef.IsEnabled = true;

					ckbTargetLock.IsEnabled = true;

					txtCameraGrPosLon.IsEnabled = true;
					txtCameraGrPosLat.IsEnabled = true;
					txtCameraGrPosAlt.IsEnabled = true;

					lblCameraPosY.Content = "Vessel Beta";
					lblCameraPosZ.Content = "Vessel Alpha";
					break;
			}
			return;
		}

		private void ckbTargetLock_Checked(object sender, System.Windows.RoutedEventArgs e)
		{
			txtCameraGrDirH.IsEnabled = false;
			txtCameraGrDirV.IsEnabled = false;
			return;
		}

		private void ckbTargetLock_Unchecked(object sender, System.Windows.RoutedEventArgs e)
		{
			txtCameraGrDirH.IsEnabled = true;
			txtCameraGrDirV.IsEnabled = true;
			return;
		}
	}
}

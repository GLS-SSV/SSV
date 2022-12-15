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

using System.Windows;


namespace SSVMissionEditor
{
	public partial class PickTgtVesselName : Window
	{
		public string tgtvesselname;


		/// <summary>
		/// Shows list of deployable payloads and other vessels for user to pick the target for rendezvous.
		/// </summary>
		/// <param name="datacontext"></param>
		public PickTgtVesselName( object datacontext )
		{
			InitializeComponent();

			tgtvesselname = "";

			model.Mission msn = (model.Mission)datacontext;

			// add active PLs
			foreach (model.Mission_PLActive pl in msn.OV.PL_Active)
			{
				if (pl.HasPayload) cmbTgtVesselName.Items.Add( pl.Payload.Name );
			}

			// add MPM PLs
			if (msn.OV.Port_PL_MPM.HasPayload) cmbTgtVesselName.Items.Add( msn.OV.Port_PL_MPM.Payload.Name );

			// add other vessels
			foreach (model.Mission_Vessel v in msn.OtherVessels)
			{
				cmbTgtVesselName.Items.Add( v.Name );
			}

			cmbTgtVesselName.SelectedIndex = 0;
			return;
		}

		private void btnOK_Click(object sender, RoutedEventArgs e)
		{
			// save selection
			tgtvesselname = (string)cmbTgtVesselName.SelectedValue;

			// exit
			DialogResult = true;
			Close();
			return;
		}

		private void btnCancel_Click(object sender, RoutedEventArgs e)
		{
			// exit
			DialogResult = false;
			Close();
			return;
		}
	}
}

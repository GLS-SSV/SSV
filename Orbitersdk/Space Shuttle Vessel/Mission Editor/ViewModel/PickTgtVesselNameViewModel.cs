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

using SSVMissionEditor.Model;
using System.Collections.Generic;
using System.ComponentModel;


namespace SSVMissionEditor.ViewModel
{
	class PickTgtVesselNameViewModel : INotifyPropertyChanged
	{
		public PickTgtVesselNameViewModel( Mission mission )
		{
			TargetVesselList = new List<string>();

			// add active PLs
			foreach (Mission_PLActive pl in mission.OV.PL_Active)
			{
				if (pl.HasPayload) TargetVesselList.Add( pl.Payload.Name );
			}

			// add MPM PLs
			if (mission.OV.Port_PL_MPM.HasPayload) TargetVesselList.Add( mission.OV.Port_PL_MPM.Payload.Name );

			// add other vessels
			foreach (Mission_Vessel v in mission.OtherVessels)
			{
				TargetVesselList.Add( v.Name );
			}
			return;
		}


		/// <summary>
		/// List of available vessel targets.
		/// </summary>
		private List<string> targetvessellist;
		public List<string> TargetVesselList
		{
			get
			{
				return targetvessellist;
			}
			set
			{
				targetvessellist = value;
				OnPropertyChanged( "TargetVesselList" );
			}
		}

		/// <summary>
		/// Selected vessel target.
		/// </summary>
		private string seltargetvessel;
		public string SelTargetVessel
		{
			get
			{
				return seltargetvessel;
			}
			set
			{
				seltargetvessel = value;
				OnPropertyChanged( "SelTargetVessel" );
			}
		}


		public event PropertyChangedEventHandler PropertyChanged;
		private void OnPropertyChanged( string prop )
		{
			PropertyChanged?.Invoke( this, new PropertyChangedEventArgs( prop ) );
			return;
		}
	}
}

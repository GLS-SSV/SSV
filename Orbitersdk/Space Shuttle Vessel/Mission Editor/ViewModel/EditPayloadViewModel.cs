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
using System.ComponentModel;


namespace SSVMissionEditor.ViewModel
{
	abstract class EditPayloadViewModel : INotifyPropertyChanged
	{
		public const string PL_VM_TYPE_ACTIVE = "Active";
		public const string PL_VM_TYPE_PASSIVE = "Passive";
		public const string PL_VM_TYPE_BAY_BRIDGE = "Bay Bridge";
		public const string PL_VM_TYPE_IUS_2 = "IUS 2-Stage";
		public const string PL_VM_TYPE_IUS_TWIN = "IUS Twin-Stage";
		public const string PL_VM_TYPE_IUS_3 = "IUS 3-Stage";
		public const string PL_VM_TYPE_CG = "Centaur G";
		public const string PL_VM_TYPE_CGP = "Centaur G'";
		public const string PL_VM_TYPE_PAM_D = "PAM-D";
		public const string PL_VM_TYPE_PAM_D2 = "PAM-DII";
		public const string PL_VM_TYPE_PAM_A = "PAM-A";
		public const string PL_VM_TYPE_SPDS_PORT = "SPDS Port";
		public const string PL_VM_TYPE_SPDS_STBD = "SPDS Starboard";
		public const string PL_VM_TYPE_PL_MPM_PORT = "Payload MPM Port";
		public const string PL_VM_TYPE_PL_MPM_STBD = "Payload MPM Starboard";


		public EditPayloadViewModel( string type )
		{
			Type = type;
			return;
		}

		public string Type { get; }

		private Mission_Payload payload;
		public Mission_Payload Payload
		{
			get { return payload; }
			set
			{
				payload = value;
				OnPropertyChanged( "Payload" );
			}
		}

		public event PropertyChangedEventHandler PropertyChanged;
		protected void OnPropertyChanged( string prop )
		{
			PropertyChanged?.Invoke( this, new PropertyChangedEventArgs( prop ) );
			return;
		}
	}
}

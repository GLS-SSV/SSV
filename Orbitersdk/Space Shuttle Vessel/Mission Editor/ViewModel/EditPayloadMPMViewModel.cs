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

using System.Linq;
using System.Windows;
using System.Windows.Input;
using CommunityToolkit.Mvvm.Input;


namespace SSVMissionEditor.ViewModel
{
	class EditPayloadMPMViewModel : EditPayloadViewModel
	{
		public EditPayloadMPMViewModel( string type ) : base( type )
		{
			Command_EditPayloadCommand = new RelayCommand( EditPayloadCommand );
			Command_UseOBSSCommand = new RelayCommand( UseOBSSCommand );
			return;
		}



		/// <summary>
		/// Is payload installed?
		/// </summary>
		public bool haspayload;
		public bool HasPayload
		{
			get { return haspayload; }
			set
			{
				haspayload = value;
				OnPropertyChanged( "HasPayload" );
			}
		}

		/// <summary>
		/// Is the Shoulder Pedestal installed
		/// </summary>
		private bool hasshoulder;
		public bool HasShoulder
		{
			get { return hasshoulder; }
			set
			{
				hasshoulder = value;
				if (value == false) ShoulderMesh = "";
				OnPropertyChanged( "HasShoulder" );
			}
		}

		/// <summary>
		/// Is the Forward Pedestal installed
		/// </summary>
		private bool hasforward;
		public bool HasForward
		{
			get { return hasforward; }
			set
			{
				hasforward = value;
				if (value == false) ForwardMesh = "";
				OnPropertyChanged( "HasForward" );
			}
		}

		/// <summary>
		/// Is the Mid Pedestal installed
		/// </summary>
		private bool hasmid;
		public bool HasMid
		{
			get { return hasmid; }
			set
			{
				hasmid = value;
				if (value == false) MidMesh = "";
				OnPropertyChanged( "HasMid" );
			}
		}

		/// <summary>
		/// Is the Aft Pedestal installed
		/// </summary>
		private bool hasaft;
		public bool HasAft
		{
			get { return hasaft; }
			set
			{
				hasaft = value;
				if (value == false) AftMesh = "";
				OnPropertyChanged( "HasAft" );
			}
		}

		/// <summary>
		/// Mesh file for Shoulder Upper Pedestal
		/// </summary>
		private string shouldermesh;
		public string ShoulderMesh
		{
			get { return shouldermesh; }
			set
			{
				shouldermesh = value;
				OnPropertyChanged( "ShoulderMesh" );
			}
		}

		/// <summary>
		/// Mesh file for Forward Upper Pedestal
		/// </summary>
		private string forwardmesh;
		public string ForwardMesh
		{
			get { return forwardmesh; }
			set
			{
				forwardmesh = value;
				OnPropertyChanged( "ForwardMesh" );
			}
		}

		/// <summary>
		/// Mesh file for Mid Upper Pedestal
		/// </summary>
		private string midmesh;
		public string MidMesh
		{
			get { return midmesh; }
			set
			{
				midmesh = value;
				OnPropertyChanged( "MidMesh" );
			}
		}

		/// <summary>
		/// Mesh file for Aft Upper Pedestal
		/// </summary>
		private string aftmesh;
		public string AftMesh
		{
			get { return aftmesh; }
			set
			{
				aftmesh = value;
				OnPropertyChanged( "AftMesh" );
			}
		}


		/// <summary>
		/// List of Pedestal MRL options.
		/// </summary>
		public static string[] PedestalMRL_src{ get; } = { "None", "Forward", "Mid", "Aft" };
		
		/// <summary>
		/// MRL latch for Shoulder Pedestal
		/// </summary>
		private int shoulderpedestalmrl;
		public int ShoulderPedestalMRL
		{
			get { return shoulderpedestalmrl; }
			set
			{
				shoulderpedestalmrl = value;
				OnPropertyChanged( "ShoulderPedestalMRL" );
			}
		}

		/// <summary>
		/// MRL latch for Forward Pedestal
		/// </summary>
		private int forwardpedestalmrl;
		public int ForwardPedestalMRL
		{
			get { return forwardpedestalmrl; }
			set
			{
				forwardpedestalmrl = value;
				OnPropertyChanged( "ForwardPedestalMRL" );
			}
		}

		/// <summary>
		/// MRL latch for Mid Pedestal
		/// </summary>
		private int midpedestalmrl;
		public int MidPedestalMRL
		{
			get { return midpedestalmrl; }
			set
			{
				midpedestalmrl = value;
				OnPropertyChanged( "MidPedestalMRL" );
			}
		}

		/// <summary>
		/// MRL latch for Aft Pedestal
		/// </summary>
		private int aftpedestalmrl;
		public int AftPedestalMRL
		{
			get { return aftpedestalmrl; }
			set
			{
				aftpedestalmrl = value;
				OnPropertyChanged( "AftPedestalMRL" );
			}
		}

		/// <summary>
		/// List of Attachment options.
		/// </summary>
		public static string[] Attachment_src{ get; } = { "Shoulder", "Forward", "Mid", "Aft" };

		/// <summary>
		/// Attachment Pedestal
		/// </summary>
		private int attachment;
		public int Attachment
		{
			get { return attachment; }
			set
			{
				attachment = value;
				OnPropertyChanged( "Attachment" );
			}
		}


		public ICommand Command_EditPayloadCommand{ get; private set; }
		void EditPayloadCommand()
		{
			EditPayload editpayload = new EditPayload( Payload );
			editpayload.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
			editpayload.ShowDialog();
			return;
		}

		public ICommand Command_UseOBSSCommand{ get; private set; }
		void UseOBSSCommand()
		{
			HasShoulder = true;
			HasForward = true;
			HasMid = false;
			HasAft = true;

			ShoulderMesh = "SSV\\MPMUpperPedestal_Starboard_Shoulder_OBSS";
			ForwardMesh = "SSV\\MPMUpperPedestal_Starboard_OBSS";
			MidMesh = "";
			AftMesh = "SSV\\MPMUpperPedestal_Starboard_OBSS";

			ShoulderPedestalMRL = 1;// MRL_Type.Forward
			ForwardPedestalMRL = 2;// MRL_Type.Mid
			MidPedestalMRL = 0;// MRL_Type.None
			AftPedestalMRL = 3;// MRL_Type.Aft

			Attachment = 1;// MPM_Attachment_Type.Forward

			HasPayload = true;

			Payload.Name = "OBSS";
			Payload.VesselClass = "SSV_OBSS";
			Payload.AttachmentID = 0;
			Payload.ScnParams = "";
			return;
		}
	}
}

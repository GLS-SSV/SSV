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
using SSVMissionEditor.Model;

namespace SSVMissionEditor.ViewModel
{
	class EditActivePayloadViewModel : EditPayloadViewModel
	{
		public EditActivePayloadViewModel() : base( PL_VM_TYPE_ACTIVE )
		{
			Command_EditLatchCommand = new RelayCommand<object>( EditLatchCommand );
			Command_EditPayloadCommand = new RelayCommand( EditPayloadCommand );

			HasInstalledPayloadOption = Visibility.Visible;
			return;
		}

		public Mission_PayloadLatch[] Latches { get; set; }

		public static string WindowTitle{ get; } = "Edit Active Payload";

		public string PLID_P1
		{
			get { return Latches[0].PLID == 0 ? "Edit" : Latches[0].PLID.ToString(); }
		}

		public string PLID_P2
		{
			get { return Latches[1].PLID == 0 ? "Edit" : Latches[1].PLID.ToString(); }
		}

		public string PLID_P3
		{
			get { return Latches[2].PLID == 0 ? "Edit" : Latches[2].PLID.ToString(); }
		}

		public string PLID_P4
		{
			get { return Latches[3].PLID == 0 ? "Edit" : Latches[3].PLID.ToString(); }
		}

		public string PLID_S1
		{
			get { return Latches[4].PLID == 0 ? "Edit" : Latches[4].PLID.ToString(); }
		}

		public string PLID_S2
		{
			get { return Latches[5].PLID == 0 ? "Edit" : Latches[5].PLID.ToString(); }
		}

		public string PLID_S3
		{
			get { return Latches[6].PLID == 0 ? "Edit" : Latches[6].PLID.ToString(); }
		}

		public string PLID_S4
		{
			get { return Latches[7].PLID == 0 ? "Edit" : Latches[7].PLID.ToString(); }
		}

		public string PLID_K1
		{
			get { return Latches[8].PLID == 0 ? "Edit" : Latches[8].PLID.ToString(); }
		}

		public string PLID_K2
		{
			get { return Latches[9].PLID == 0 ? "Edit" : Latches[9].PLID.ToString(); }
		}

		public string PLID_K3
		{
			get { return Latches[10].PLID == 0 ? "Edit" : Latches[10].PLID.ToString(); }
		}

		public string PLID_K4
		{
			get { return Latches[11].PLID == 0 ? "Edit" : Latches[11].PLID.ToString(); }
		}

		public bool PLID_P1_ena
		{
			get { return Latches[0].PLID != 0; }
			set
			{
				if (value) Latches[0].PLID = Defs.LONGERON_ACTIVE[0];
				else Latches[0].PLID = 0;
				OnPropertyChanged( "PLID_P1_ena" );
				OnPropertyChanged( "PLID_P1" );
			}
		}

		public bool PLID_P2_ena
		{
			get { return Latches[1].PLID != 0; }
			set
			{
				if (value) Latches[1].PLID = Defs.LONGERON_ACTIVE[0];
				else Latches[1].PLID = 0;
				OnPropertyChanged( "PLID_P2_ena" );
				OnPropertyChanged( "PLID_P2" );
			}
		}

		public bool PLID_P3_ena
		{
			get { return Latches[2].PLID != 0; }
			set
			{
				if (value) Latches[2].PLID = Defs.LONGERON_ACTIVE[0];
				else Latches[2].PLID = 0;
				OnPropertyChanged( "PLID_P3_ena" );
				OnPropertyChanged( "PLID_P3" );
			}
		}

		public bool PLID_P4_ena
		{
			get { return Latches[3].PLID != 0; }
			set
			{
				if (value) Latches[3].PLID = Defs.LONGERON_ACTIVE[0];
				else Latches[3].PLID = 0;
				OnPropertyChanged( "PLID_P4_ena" );
				OnPropertyChanged( "PLID_P4" );
			}
		}

		public bool PLID_S1_ena
		{
			get { return Latches[4].PLID != 0; }
			set
			{
				if (value) Latches[4].PLID = Defs.LONGERON_ACTIVE[0];
				else Latches[4].PLID = 0;
				OnPropertyChanged( "PLID_S1_ena" );
				OnPropertyChanged( "PLID_S1" );
			}
		}

		public bool PLID_S2_ena
		{
			get { return Latches[5].PLID != 0; }
			set
			{
				if (value) Latches[5].PLID = Defs.LONGERON_ACTIVE[0];
				else Latches[5].PLID = 0;
				OnPropertyChanged( "PLID_S2_ena" );
				OnPropertyChanged( "PLID_S2" );
			}
		}

		public bool PLID_S3_ena
		{
			get { return Latches[6].PLID != 0; }
			set
			{
				if (value) Latches[6].PLID = Defs.LONGERON_ACTIVE[0];
				else Latches[6].PLID = 0;
				OnPropertyChanged( "PLID_S3_ena" );
				OnPropertyChanged( "PLID_S3" );
			}
		}

		public bool PLID_S4_ena
		{
			get { return Latches[7].PLID != 0; }
			set
			{
				if (value) Latches[7].PLID = Defs.LONGERON_ACTIVE[0];
				else Latches[7].PLID = 0;
				OnPropertyChanged( "PLID_S4_ena" );
				OnPropertyChanged( "PLID_S4" );
			}
		}

		public bool PLID_K1_ena
		{
			get { return Latches[8].PLID != 0; }
			set
			{
				if (value) Latches[8].PLID = Defs.KEEL_ACTIVE[0];
				else Latches[8].PLID = 0;
				OnPropertyChanged( "PLID_K1_ena" );
				OnPropertyChanged( "PLID_K1" );
			}
		}

		public bool PLID_K2_ena
		{
			get { return Latches[9].PLID != 0; }
			set
			{
				if (value) Latches[9].PLID = Defs.KEEL_ACTIVE[0];
				else Latches[9].PLID = 0;
				OnPropertyChanged( "PLID_K2_ena" );
				OnPropertyChanged( "PLID_K2" );
			}
		}

		public bool PLID_K3_ena
		{
			get { return Latches[10].PLID != 0; }
			set
			{
				if (value) Latches[10].PLID = Defs.KEEL_ACTIVE[0];
				else Latches[10].PLID = 0;
				OnPropertyChanged( "PLID_K3_ena" );
				OnPropertyChanged( "PLID_K3" );
			}
		}

		public bool PLID_K4_ena
		{
			get { return Latches[11].PLID != 0; }
			set
			{
				if (value) Latches[11].PLID = Defs.KEEL_ACTIVE[0];
				else Latches[11].PLID = 0;
				OnPropertyChanged( "PLID_K4_ena" );
				OnPropertyChanged( "PLID_K4" );
			}
		}

		/// <summary>
		/// Is P1 attachment?
		/// </summary>
		public FontWeight IsAttachment_P1{ get { return Latches[0].IsAttachment ? FontWeights.Bold : FontWeights.Normal; } }

		/// <summary>
		/// Is P2 attachment?
		/// </summary>
		public FontWeight IsAttachment_P2{ get { return Latches[1].IsAttachment ? FontWeights.Bold : FontWeights.Normal; } }

		/// <summary>
		/// Is P3 attachment?
		/// </summary>
		public FontWeight IsAttachment_P3{ get { return Latches[2].IsAttachment ? FontWeights.Bold : FontWeights.Normal; } }

		/// <summary>
		/// Is P4 attachment?
		/// </summary>
		public FontWeight IsAttachment_P4{ get { return Latches[3].IsAttachment ? FontWeights.Bold : FontWeights.Normal; } }

		/// <summary>
		/// Is S1 attachment?
		/// </summary>
		public FontWeight IsAttachment_S1{ get { return Latches[4].IsAttachment ? FontWeights.Bold : FontWeights.Normal; } }

		/// <summary>
		/// Is S2 attachment?
		/// </summary>
		public FontWeight IsAttachment_S2{ get { return Latches[5].IsAttachment ? FontWeights.Bold : FontWeights.Normal; } }

		/// <summary>
		/// Is S3 attachment?
		/// </summary>
		public FontWeight IsAttachment_S3{ get { return Latches[6].IsAttachment ? FontWeights.Bold : FontWeights.Normal; } }

		/// <summary>
		/// Is S4 attachment?
		/// </summary>
		public FontWeight IsAttachment_S4{ get { return Latches[7].IsAttachment ? FontWeights.Bold : FontWeights.Normal; } }

		/// <summary>
		/// Is K1 attachment?
		/// </summary>
		public FontWeight IsAttachment_K1{ get { return Latches[8].IsAttachment ? FontWeights.Bold : FontWeights.Normal; } }

		/// <summary>
		/// Is K2 attachment?
		/// </summary>
		public FontWeight IsAttachment_K2{ get { return Latches[9].IsAttachment ? FontWeights.Bold : FontWeights.Normal; } }

		/// <summary>
		/// Is K3 attachment?
		/// </summary>
		public FontWeight IsAttachment_K3{ get { return Latches[10].IsAttachment ? FontWeights.Bold : FontWeights.Normal; } }

		/// <summary>
		/// Is K4 attachment?
		/// </summary>
		public FontWeight IsAttachment_K4{ get { return Latches[11].IsAttachment ? FontWeights.Bold : FontWeights.Normal; } }

		public ICommand Command_EditLatchCommand{ get; private set; }
		void EditLatchCommand( object parameter )
		{
			switch (parameter)
			{
				case "P1":
					{
						EditLatchViewModel editlatchvm = new EditLatchViewModel( 0, false, Defs.LONGERON_ACTIVE, Defs.LONGERON_ACTIVE );
						editlatchvm.Reversed = Latches[0].Reversed;
						editlatchvm.PLID = Latches[0].PLID;
						editlatchvm.FwdGuide = Latches[0].ForwardGuide;
						editlatchvm.AftGuide = Latches[0].AftGuide;
						editlatchvm.Latch = Latches[0].Latch;
						editlatchvm.Attachment = Latches[0].IsAttachment;
						EditLatch( editlatchvm );
						if (editlatchvm.Attachment) foreach (Mission_PayloadLatch x in Latches) x.IsAttachment = false;
						Latches[0].IsAttachment = editlatchvm.Attachment;
						Latches[0].PLID = editlatchvm.PLID;
						Latches[0].Reversed = editlatchvm.Reversed;
						Latches[0].ForwardGuide = editlatchvm.FwdGuide;
						Latches[0].AftGuide = editlatchvm.AftGuide;
						Latches[0].Latch = editlatchvm.Latch;
					}
					break;
				case "P2":
					{
						EditLatchViewModel editlatchvm = new EditLatchViewModel( 0, false, Defs.LONGERON_ACTIVE, Defs.LONGERON_ACTIVE );
						editlatchvm.Reversed = Latches[1].Reversed;
						editlatchvm.PLID = Latches[1].PLID;
						editlatchvm.FwdGuide = Latches[1].ForwardGuide;
						editlatchvm.AftGuide = Latches[1].AftGuide;
						editlatchvm.Latch = Latches[1].Latch;
						editlatchvm.Attachment = Latches[1].IsAttachment;
						EditLatch( editlatchvm );
						if (editlatchvm.Attachment) foreach (Mission_PayloadLatch x in Latches) x.IsAttachment = false;
						Latches[1].IsAttachment = editlatchvm.Attachment;
						Latches[1].PLID = editlatchvm.PLID;
						Latches[1].Reversed = editlatchvm.Reversed;
						Latches[1].ForwardGuide = editlatchvm.FwdGuide;
						Latches[1].AftGuide = editlatchvm.AftGuide;
						Latches[1].Latch = editlatchvm.Latch;
					}
					break;
				case "P3":
					{
						EditLatchViewModel editlatchvm = new EditLatchViewModel( 0, false, Defs.LONGERON_ACTIVE, Defs.LONGERON_ACTIVE );
						editlatchvm.Reversed = Latches[2].Reversed;
						editlatchvm.PLID = Latches[2].PLID;
						editlatchvm.FwdGuide = Latches[2].ForwardGuide;
						editlatchvm.AftGuide = Latches[2].AftGuide;
						editlatchvm.Latch = Latches[2].Latch;
						editlatchvm.Attachment = Latches[2].IsAttachment;
						EditLatch( editlatchvm );
						if (editlatchvm.Attachment) foreach (Mission_PayloadLatch x in Latches) x.IsAttachment = false;
						Latches[2].IsAttachment = editlatchvm.Attachment;
						Latches[2].PLID = editlatchvm.PLID;
						Latches[2].Reversed = editlatchvm.Reversed;
						Latches[2].ForwardGuide = editlatchvm.FwdGuide;
						Latches[2].AftGuide = editlatchvm.AftGuide;
						Latches[2].Latch = editlatchvm.Latch;
					}
					break;
				case "P4":
					{
						EditLatchViewModel editlatchvm = new EditLatchViewModel( 0, false, Defs.LONGERON_ACTIVE, Defs.LONGERON_ACTIVE );
						editlatchvm.Reversed = Latches[3].Reversed;
						editlatchvm.PLID = Latches[3].PLID;
						editlatchvm.FwdGuide = Latches[3].ForwardGuide;
						editlatchvm.AftGuide = Latches[3].AftGuide;
						editlatchvm.Latch = Latches[3].Latch;
						editlatchvm.Attachment = Latches[3].IsAttachment;
						EditLatch( editlatchvm );
						if (editlatchvm.Attachment) foreach (Mission_PayloadLatch x in Latches) x.IsAttachment = false;
						Latches[3].IsAttachment = editlatchvm.Attachment;
						Latches[3].PLID = editlatchvm.PLID;
						Latches[3].Reversed = editlatchvm.Reversed;
						Latches[3].ForwardGuide = editlatchvm.FwdGuide;
						Latches[3].AftGuide = editlatchvm.AftGuide;
						Latches[3].Latch = editlatchvm.Latch;
					}
					break;
				case "S1":
					{
						EditLatchViewModel editlatchvm = new EditLatchViewModel( 0, false, Defs.LONGERON_ACTIVE, Defs.LONGERON_ACTIVE );
						editlatchvm.Reversed = Latches[4].Reversed;
						editlatchvm.PLID = Latches[4].PLID;
						editlatchvm.FwdGuide = Latches[4].ForwardGuide;
						editlatchvm.AftGuide = Latches[4].AftGuide;
						editlatchvm.Latch = Latches[4].Latch;
						editlatchvm.Attachment = Latches[4].IsAttachment;
						EditLatch( editlatchvm );
						if (editlatchvm.Attachment) foreach (Mission_PayloadLatch x in Latches) x.IsAttachment = false;
						Latches[4].IsAttachment = editlatchvm.Attachment;
						Latches[4].PLID = editlatchvm.PLID;
						Latches[4].Reversed = editlatchvm.Reversed;
						Latches[4].ForwardGuide = editlatchvm.FwdGuide;
						Latches[4].AftGuide = editlatchvm.AftGuide;
						Latches[4].Latch = editlatchvm.Latch;
					}
					break;
				case "S2":
					{
						EditLatchViewModel editlatchvm = new EditLatchViewModel( 0, false, Defs.LONGERON_ACTIVE, Defs.LONGERON_ACTIVE );
						editlatchvm.Reversed = Latches[5].Reversed;
						editlatchvm.PLID = Latches[5].PLID;
						editlatchvm.FwdGuide = Latches[5].ForwardGuide;
						editlatchvm.AftGuide = Latches[5].AftGuide;
						editlatchvm.Latch = Latches[5].Latch;
						editlatchvm.Attachment = Latches[5].IsAttachment;
						EditLatch( editlatchvm );
						if (editlatchvm.Attachment) foreach (Mission_PayloadLatch x in Latches) x.IsAttachment = false;
						Latches[5].IsAttachment = editlatchvm.Attachment;
						Latches[5].PLID = editlatchvm.PLID;
						Latches[5].Reversed = editlatchvm.Reversed;
						Latches[5].ForwardGuide = editlatchvm.FwdGuide;
						Latches[5].AftGuide = editlatchvm.AftGuide;
						Latches[5].Latch = editlatchvm.Latch;
					}
					break;
				case "S3":
					{
						EditLatchViewModel editlatchvm = new EditLatchViewModel( 0, false, Defs.LONGERON_ACTIVE, Defs.LONGERON_ACTIVE );
						editlatchvm.Reversed = Latches[6].Reversed;
						editlatchvm.PLID = Latches[6].PLID;
						editlatchvm.FwdGuide = Latches[6].ForwardGuide;
						editlatchvm.AftGuide = Latches[6].AftGuide;
						editlatchvm.Latch = Latches[6].Latch;
						editlatchvm.Attachment = Latches[6].IsAttachment;
						EditLatch( editlatchvm );
						if (editlatchvm.Attachment) foreach (Mission_PayloadLatch x in Latches) x.IsAttachment = false;
						Latches[6].IsAttachment = editlatchvm.Attachment;
						Latches[6].PLID = editlatchvm.PLID;
						Latches[6].Reversed = editlatchvm.Reversed;
						Latches[6].ForwardGuide = editlatchvm.FwdGuide;
						Latches[6].AftGuide = editlatchvm.AftGuide;
						Latches[6].Latch = editlatchvm.Latch;
					}
					break;
				case "S4":
					{
						EditLatchViewModel editlatchvm = new EditLatchViewModel( 0, false, Defs.LONGERON_ACTIVE, Defs.LONGERON_ACTIVE );
						editlatchvm.Reversed = Latches[7].Reversed;
						editlatchvm.PLID = Latches[7].PLID;
						editlatchvm.FwdGuide = Latches[7].ForwardGuide;
						editlatchvm.AftGuide = Latches[7].AftGuide;
						editlatchvm.Latch = Latches[7].Latch;
						editlatchvm.Attachment = Latches[7].IsAttachment;
						EditLatch( editlatchvm );
						if (editlatchvm.Attachment) foreach (Mission_PayloadLatch x in Latches) x.IsAttachment = false;
						Latches[7].IsAttachment = editlatchvm.Attachment;
						Latches[7].PLID = editlatchvm.PLID;
						Latches[7].Reversed = editlatchvm.Reversed;
						Latches[7].ForwardGuide = editlatchvm.FwdGuide;
						Latches[7].AftGuide = editlatchvm.AftGuide;
						Latches[7].Latch = editlatchvm.Latch;
					}
					break;
				case "K1":
					{
						EditLatchViewModel editlatchvm = new EditLatchViewModel( 0, true, Defs.KEEL_ACTIVE, Defs.KEEL_ACTIVE );
						editlatchvm.PLID = Latches[8].PLID;
						editlatchvm.Latch = Latches[8].Latch;
						editlatchvm.Attachment = Latches[8].IsAttachment;
						EditLatch( editlatchvm );
						if (editlatchvm.Attachment) foreach (Mission_PayloadLatch x in Latches) x.IsAttachment = false;
						Latches[8].IsAttachment = editlatchvm.Attachment;
						Latches[8].PLID = editlatchvm.PLID;
						Latches[8].Latch = editlatchvm.Latch;
					}
					break;
				case "K2":
					{
						EditLatchViewModel editlatchvm = new EditLatchViewModel( 0, true, Defs.KEEL_ACTIVE, Defs.KEEL_ACTIVE );
						editlatchvm.PLID = Latches[9].PLID;
						editlatchvm.Latch = Latches[9].Latch;
						editlatchvm.Attachment = Latches[9].IsAttachment;
						EditLatch( editlatchvm );
						if (editlatchvm.Attachment) foreach (Mission_PayloadLatch x in Latches) x.IsAttachment = false;
						Latches[9].IsAttachment = editlatchvm.Attachment;
						Latches[9].PLID = editlatchvm.PLID;
						Latches[9].Latch = editlatchvm.Latch;
					}
					break;
				case "K3":
					{
						EditLatchViewModel editlatchvm = new EditLatchViewModel( 0, true, Defs.KEEL_ACTIVE, Defs.KEEL_ACTIVE );
						editlatchvm.PLID = Latches[10].PLID;
						editlatchvm.Latch = Latches[10].Latch;
						editlatchvm.Attachment = Latches[10].IsAttachment;
						EditLatch( editlatchvm );
						if (editlatchvm.Attachment) foreach (Mission_PayloadLatch x in Latches) x.IsAttachment = false;
						Latches[10].IsAttachment = editlatchvm.Attachment;
						Latches[10].PLID = editlatchvm.PLID;
						Latches[10].Latch = editlatchvm.Latch;
					}
					break;
				case "K4":
					{
						EditLatchViewModel editlatchvm = new EditLatchViewModel( 0, true, Defs.KEEL_ACTIVE, Defs.KEEL_ACTIVE );
						editlatchvm.PLID = Latches[11].PLID;
						editlatchvm.Latch = Latches[11].Latch;
						editlatchvm.Attachment = Latches[11].IsAttachment;
						EditLatch( editlatchvm );
						if (editlatchvm.Attachment) foreach (Mission_PayloadLatch x in Latches) x.IsAttachment = false;
						Latches[11].IsAttachment = editlatchvm.Attachment;
						Latches[11].PLID = editlatchvm.PLID;
						Latches[11].Latch = editlatchvm.Latch;
					}
					break;
			}

			OnPropertyChanged( "PLID_" + parameter );
			OnPropertyChanged( "IsAttachment_P1" );
			OnPropertyChanged( "IsAttachment_P2" );
			OnPropertyChanged( "IsAttachment_P3" );
			OnPropertyChanged( "IsAttachment_P4" );
			OnPropertyChanged( "IsAttachment_S1" );
			OnPropertyChanged( "IsAttachment_S2" );
			OnPropertyChanged( "IsAttachment_S3" );
			OnPropertyChanged( "IsAttachment_S4" );
			OnPropertyChanged( "IsAttachment_K1" );
			OnPropertyChanged( "IsAttachment_K2" );
			OnPropertyChanged( "IsAttachment_K3" );
			OnPropertyChanged( "IsAttachment_K4" );
			return;
		}

		void EditLatch( EditLatchViewModel editlatchvm )
		{
			EditLatch editlatch = new EditLatch( editlatchvm );
			editlatch.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
			editlatch.ShowDialog();
			return;
		}


		private int idx;
		public int Idx
		{
			get { return idx; }
			set
			{
				idx = value;
				OnPropertyChanged( "Idx" );
			}
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
		/// Has Installed Payload option.
		/// </summary>
		public Visibility HasInstalledPayloadOption { get; }


		public ICommand Command_EditPayloadCommand{ get; private set; }
		void EditPayloadCommand()
		{
			EditPayload editpayload = new EditPayload( Payload );
			editpayload.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
			editpayload.ShowDialog();
			return;
		}
	}
}

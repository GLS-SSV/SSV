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
	class EditSPDSViewModel : EditPayloadViewModel
	{
		public EditSPDSViewModel( string type ) : base( type )
		{
			Command_EditLatchCommand = new RelayCommand<object>( EditLatchCommand );
			Command_EditPayloadCommand = new RelayCommand( EditPayloadCommand );
			return;
		}

		public Mission_PayloadLatch[] Latches { get; set; }

		public string PLID_P1
		{
			get { return Latches[0].PLID.ToString(); }
		}

		public string PLID_P2
		{
			get { return Latches[1].PLID.ToString(); }
		}

		public string PLID_S1
		{
			get { return Latches[2].PLID.ToString(); }
		}

		public string PLID_S2
		{
			get { return Latches[3].PLID.ToString(); }
		}

		public string PLID_K
		{
			get { return Latches[4].PLID.ToString(); }
		}

		public ICommand Command_EditLatchCommand{ get; private set; }
		void EditLatchCommand( object parameter )
		{
			switch (parameter)
			{
				case "P1":
					{
						EditLatchViewModel editlatchvm = new EditLatchViewModel( 2, false, Defs.LONGERON_SPDS_5, Defs.LONGERON_SPDS_3 );
						editlatchvm.Reversed = Latches[0].Reversed;
						editlatchvm.PLID = Latches[0].PLID;
						EditLatch( editlatchvm );
						Latches[0].PLID = editlatchvm.PLID;
						Latches[0].Reversed = editlatchvm.Reversed;
					}
					break;
				case "P2":
					{
						EditLatchViewModel editlatchvm = new EditLatchViewModel( 2, false, Defs.LONGERON_SPDS_5, Defs.LONGERON_SPDS_3 );
						editlatchvm.Reversed = Latches[1].Reversed;
						editlatchvm.PLID = Latches[1].PLID;
						EditLatch( editlatchvm );
						Latches[1].PLID = editlatchvm.PLID;
						Latches[1].Reversed = editlatchvm.Reversed;
					}
					break;
				case "S1":
					{
						EditLatchViewModel editlatchvm = new EditLatchViewModel( 3, false, Defs.LONGERON_ACTIVE, Defs.LONGERON_ACTIVE );
						editlatchvm.Reversed = Latches[2].Reversed;
						editlatchvm.PLID = Latches[2].PLID;
						EditLatch( editlatchvm );
						Latches[2].PLID = editlatchvm.PLID;
						Latches[2].Reversed = editlatchvm.Reversed;
					}
					break;
				case "S2":
					{
						EditLatchViewModel editlatchvm = new EditLatchViewModel( 3, false, Defs.LONGERON_ACTIVE, Defs.LONGERON_ACTIVE );
						editlatchvm.Reversed = Latches[3].Reversed;
						editlatchvm.PLID = Latches[3].PLID;
						EditLatch( editlatchvm );
						Latches[3].PLID = editlatchvm.PLID;
						Latches[3].Reversed = editlatchvm.Reversed;
					}
					break;
				case "K":
					{
						EditLatchViewModel editlatchvm = new EditLatchViewModel( 3, true, Defs.KEEL_SPDS, Defs.KEEL_SPDS );
						editlatchvm.PLID = Latches[4].PLID;
						EditLatch( editlatchvm );
						Latches[4].PLID = editlatchvm.PLID;
					}
					break;
			}

			OnPropertyChanged( "PLID_" + parameter );
			return;
		}

		void EditLatch( EditLatchViewModel editlatchvm )
		{
			EditLatch editlatch = new EditLatch( editlatchvm );
			editlatch.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
			editlatch.ShowDialog();
			return;
		}

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

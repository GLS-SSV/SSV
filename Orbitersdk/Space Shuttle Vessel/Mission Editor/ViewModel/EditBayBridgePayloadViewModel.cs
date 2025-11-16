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
	class EditBayBridgePayloadViewModel : EditPayloadViewModel
	{
		public EditBayBridgePayloadViewModel() : base( PL_VM_TYPE_BAY_BRIDGE )
		{
			Command_EditPayloadCommand = new RelayCommand( EditPayloadCommand );

			Bridge = 0;
			Bay = 1;
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
		/// List of bridge options.
		/// </summary>
		public static string[] Bridge_src{ get; } = { "Port", "Starboard", "Keel" };

		/// <summary>
		/// List of side bay options.
		/// </summary>
		private static int[] Bay_Side_src{ get; } = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };

		/// <summary>
		/// List of keel bay options.
		/// </summary>
		private static int[] Bay_Keel_src{ get; } = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

		/// <summary>
		/// List of bay options.
		/// </summary>
		private int[] bay_src;
		public int[] Bay_src
		{
			get { return bay_src; }
			set
			{
				bay_src = value;
				OnPropertyChanged( "Bay_src" );
			}
		}

		private int bridge;
		public int Bridge
		{
			get { return bridge; }
			set
			{
				bridge = value;
				if (bridge == 2) Bay_src = Bay_Keel_src;
				else Bay_src = Bay_Side_src;
				OnPropertyChanged( "Bridge" );
			}
		}

		private int bay;
		public int Bay
		{
			get { return bay; }
			set
			{
				bay = value;
				OnPropertyChanged( "Bay" );
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
	}
}

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
	class EditUpperStageCentaurViewModel : EditPayloadViewModel
	{
		public EditUpperStageCentaurViewModel( string type ) : base( type )
		{
			Command_EditPayloadCommand = new RelayCommand( EditPayloadCommand );
			Command_EditAdapterCommand = new RelayCommand( EditAdapterCommand );
			return;
		}


		/// <summary>
		/// Centaur vessel name
		/// </summary>
		public string name;
		public string Name
		{
			get { return name; }
			set
			{
				name = value;
				OnPropertyChanged( "Name" );
			}
		}

		public static string[] Latch_src{ get; } = { "P/L 1 Latch 1", "P/L 1 Latch 2", "P/L 1 Latch 3", "P/L 1 Latch 4", "P/L 1 Latch 5", "P/L 2 Latch 1", "P/L 2 Latch 2", "P/L 2 Latch 3", "P/L 2 Latch 4", "P/L 2 Latch 5", "P/L 3 Latch 1", "P/L 3 Latch 2", "P/L 3 Latch 3", "P/L 3 Latch 4", "P/L 3 Latch 5" };

		private int[] latches;
		public int[] Latches
		{
			get { return latches; }
			set
			{
				latches = value;
				OnPropertyChanged( "Latches" );
			}
		}

		/// <summary>
		/// Mesh of payload adapter
		/// </summary>
		private string adapter_mesh;
		public string Adapter_Mesh
		{
			get { return adapter_mesh; }
			set
			{
				adapter_mesh = value;
				OnPropertyChanged( "Adapter_Mesh" );
			}
		}

		/// <summary>
		/// Offset of mesh of payload adapter
		/// </summary>
		private double adapter_offset;
		public double Adapter_Offset
		{
			get { return adapter_offset; }
			set
			{
				adapter_offset = value;
				OnPropertyChanged( "Adapter_Offset" );
			}
		}

		/// <summary>
		/// Mass of payload adapter
		/// </summary>
		private double adapter_mass;
		public double Adapter_Mass
		{
			get { return adapter_mass; }
			set
			{
				adapter_mass = value;
				OnPropertyChanged( "Adapter_Mass" );
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

		public ICommand Command_EditAdapterCommand{ get; private set; }
		void EditAdapterCommand()
		{
			EditPayloadAdapter editadapter = new EditPayloadAdapter( this );
			editadapter.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
			editadapter.ShowDialog();
			return;
		}
	}
}

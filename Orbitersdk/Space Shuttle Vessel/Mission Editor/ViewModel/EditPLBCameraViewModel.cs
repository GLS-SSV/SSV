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

using System;
using System.ComponentModel;


namespace SSVMissionEditor.ViewModel
{
	class EditPLBCameraViewModel : INotifyPropertyChanged
	{
		private Mission_PLB_Camera cameras;
		private int camidx;

		public EditPLBCameraViewModel( Mission_PLB_Camera cameras, string camid )
		{
			if (camid == "A")
			{
				camidx = 0;
			}
			else if (camid == "B")
			{
				camidx = 1;
			}
			else if (camid == "C")
			{
				camidx = 2;
			}
			else if (camid == "D")
			{
				camidx = 3;
			}
			else throw new ArgumentException();

			this.cameras = cameras;

			if (cameras.Type[camidx] == Defs.strCTVC_ITVC)
			{
				Illuminator_ena = true;
			}
			else
			{
				Illuminator_ena = false;
				Illuminator = false;
			}
			return;
		}


		/// <summary>
		/// List of Camera type options.
		/// </summary>
		public static string[] Type_src{ get; } = { Defs.str_506_508, Defs.strCTVC_ITVC };

		/// <summary>
		/// Camera type
		/// </summary>
		public string Type
		{
			get { return cameras.Type[camidx]; }
			set
			{
				cameras.Type[camidx] = value;

				if (value == Defs.strCTVC_ITVC)
				{
					Illuminator_ena = true;
				}
				else
				{
					Illuminator_ena = false;
					Illuminator = false;
				}
				OnPropertyChanged( "Type" );
			}
		}

		/// <summary>
		/// Is Illuminator option enabled?
		/// </summary>
		public bool illuminator_ena;
		public bool Illuminator_ena
		{
			get { return illuminator_ena; }
			set
			{
				illuminator_ena = value;
				OnPropertyChanged( "Illuminator_ena" );
			}
		}

		/// <summary>
		/// Is Illuminator installed in camera?
		/// </summary>
		public bool Illuminator
		{
			get { return cameras.Illuminator[camidx]; }
			set
			{
				cameras.Illuminator[camidx] = value;
				OnPropertyChanged( "Illuminator" );
			}
		}

		/// <summary>
		/// Does camera have custom coordinates?
		/// </summary>
		public bool Custom
		{
			get { return cameras.Custom[camidx]; }
			set
			{
				cameras.Custom[camidx] = value;
				OnPropertyChanged( "Custom" );
			}
		}

		/// <summary>
		/// Custom Xo coordinate
		/// </summary>
		public double Xo
		{
			get { return cameras.Xo[camidx]; }
			set
			{
				cameras.Xo[camidx] = value;
				OnPropertyChanged( "Xo" );
			}
		}

		/// <summary>
		/// Custom Yo coordinate
		/// </summary>
		public double Yo
		{
			get { return cameras.Yo[camidx]; }
			set
			{
				cameras.Yo[camidx] = value;
				OnPropertyChanged( "Yo" );
			}
		}

		/// <summary>
		/// Custom Zo coordinate
		/// </summary>
		public double Zo
		{
			get { return cameras.Zo[camidx]; }
			set
			{
				cameras.Zo[camidx] = value;
				OnPropertyChanged( "Zo" );
			}
		}

		/// <summary>
		/// Custom rotation [deg]
		/// </summary>
		public double Rot
		{
			get { return cameras.Rot[camidx]; }
			set
			{
				cameras.Rot[camidx] = value;
				OnPropertyChanged( "Rot" );
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

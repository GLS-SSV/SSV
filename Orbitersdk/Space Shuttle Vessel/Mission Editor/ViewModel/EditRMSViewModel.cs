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
	class EditRMSViewModel : INotifyPropertyChanged
	{
		public EditRMSViewModel( Mission_RMS rms )
		{
			this.rms = rms;
			return;
		}

		Mission_RMS rms;


		/// <summary>
		/// List of Camera type options.
		/// </summary>
		public static int[] SN_src{ get; } = { 201, 202, 301, 302, 303 };

		/// <summary>
		/// Serial Number
		/// </summary>
		public int SN
		{
			get { return rms.SN; }
			set
			{
				rms.SN = value;
				OnPropertyChanged( "SN" );
			}
		}

		/// <summary>
		/// List of Camera type options.
		/// </summary>
		public static string[] Type_src{ get; } = { Defs.str_506_508, Defs.strCTVC_ITVC };

		/// <summary>
		/// Elbow camera type
		/// </summary>
		public string TypeElbow
		{
			get { return rms.Elbow; }
			set
			{
				rms.Elbow = value;

				if (value != Defs.strCTVC_ITVC)
				{
					IlluminatorElbow = false;
				}
				OnPropertyChanged( "TypeElbow" );
				OnPropertyChanged( "IlluminatorElbow_ena" );
			}
		}

		/// <summary>
		/// Wrist camera type
		/// </summary>
		public string TypeWrist
		{
			get { return rms.Wrist; }
			set
			{
				rms.Wrist = value;

				if (value != Defs.strCTVC_ITVC)
				{
					IlluminatorWrist = false;
				}
				OnPropertyChanged( "TypeWrist" );
				OnPropertyChanged( "IlluminatorWrist_ena" );
			}
		}

		/// <summary>
		/// Is Elbow illuminator option enabled?
		/// </summary>
		public bool IlluminatorElbow_ena
		{
			get { return TypeElbow == Defs.strCTVC_ITVC; }
		}

		/// <summary>
		/// Is Wrist illuminator option enabled?
		/// </summary>
		public bool IlluminatorWrist_ena
		{
			get { return TypeWrist == Defs.strCTVC_ITVC; }
		}

		/// <summary>
		/// Is Elbow illuminator installed in camera?
		/// </summary>
		public bool IlluminatorElbow
		{
			get { return rms.ElbowIlluminator; }
			set
			{
				rms.ElbowIlluminator = value;
				OnPropertyChanged( "IlluminatorElbow" );
			}
		}

		/// <summary>
		/// Is Wrist illuminator installed in camera?
		/// </summary>
		public bool IlluminatorWrist
		{
			get { return rms.WristIlluminator; }
			set
			{
				rms.WristIlluminator = value;
				OnPropertyChanged( "IlluminatorWrist" );
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

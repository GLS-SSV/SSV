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
using System.Linq;
using System.Windows;
using System.Windows.Input;
using CommunityToolkit.Mvvm.Input;


namespace SSVMissionEditor.ViewModel
{
	class EditUpperStageIUSViewModel : EditPayloadViewModel
	{
		public EditUpperStageIUSViewModel() : base( PL_VM_TYPE_IUS_2 )
		{
			Command_CalcCommand = new RelayCommand( CalcCommand, CalcCommandEnabled );
			Command_SaveCommand = new RelayCommand( SaveCommand, SaveCommandEnabled );
			Command_EditPayloadCommand = new RelayCommand( EditPayloadCommand );
			Command_EditAdapterCommand = new RelayCommand( EditAdapterCommand );

			calcload1 = 1;
			calcload2 = 1;

			AltCur = 296;
			AltTgt = 35786;
			DInc1 = 1.45;
			DInc2 = 27;
			C3Tgt = 25;
			PLMass = 2268;
			Result = "";
			CalcTarget = CalcTarget_src[0];
			return;
		}


		/// <summary>
		/// IUS vessel name
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

		/// <summary>
		/// IUS vessel texture name
		/// </summary>
		private string texture;
		public string Texture
		{
			get { return texture; }
			set
			{
				texture = value;
				OnPropertyChanged( "Texture" );
			}
		}

		private bool _4antennas;
		public bool FourAntennas
		{
			get { return _4antennas; }
			set
			{
				_4antennas = value;
				OnPropertyChanged( "FourAntennas" );
			}
		}

		private bool aftposition;
		public bool AftPosition
		{
			get { return aftposition; }
			set
			{
				aftposition = value;
				OnPropertyChanged( "AftPosition" );
			}
		}

		private int rcstanks;
		public int RCSTanks
		{
			get { return rcstanks; }
			set
			{
				rcstanks = value;
				OnPropertyChanged( "RCSTanks" );
			}
		}

		private double firststageload;
		public double FirstStageLoad
		{
			get { return firststageload; }
			set
			{
				firststageload = value;
				OnPropertyChanged( "FirstStageLoad" );
			}
		}

		private double secondstageload;
		public double SecondStageLoad
		{
			get { return secondstageload; }
			set
			{
				secondstageload = value;
				OnPropertyChanged( "SecondStageLoad" );
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



		double calcload1;
		double calcload2;

		/// <summary>
		/// Current Altitude [km]
		/// </summary>
		private double altcur;
		public double AltCur
		{
			get { return altcur; }
			set
			{
				altcur = value;
				OnPropertyChanged( "AltCur" );
			}
		}

		/// <summary>
		/// Target Altitude [km]
		/// </summary>
		private double alttgt;
		public double AltTgt
		{
			get { return alttgt; }
			set
			{
				alttgt = value;
				OnPropertyChanged( "AltTgt" );
			}
		}

		/// <summary>
		/// Delta inclination for SRM-1 burn [deg]
		/// </summary>
		private double dinc1;
		public double DInc1
		{
			get { return dinc1; }
			set
			{
				dinc1 = value;
				OnPropertyChanged( "DInc1" );
			}
		}

		/// <summary>
		/// Delta inclination for SRM-2 burn [deg]
		/// </summary>
		private double dinc2;
		public double DInc2
		{
			get { return dinc2; }
			set
			{
				dinc2 = value;
				OnPropertyChanged( "DInc2" );
			}
		}

		/// <summary>
		/// Target C3 energy [km^2 / m^2]
		/// </summary>
		private double c3tgt;
		public double C3Tgt
		{
			get { return c3tgt; }
			set
			{
				c3tgt = value;
				OnPropertyChanged( "C3Tgt" );
			}
		}

		/// <summary>
		/// Payload mass [kg]
		/// </summary>
		private double plmass;
		public double PLMass
		{
			get { return plmass; }
			set
			{
				plmass = value;
				OnPropertyChanged( "PLMass" );
			}
		}

		/// <summary>
		/// Calculation result string
		/// </summary>
		private string result;
		public string Result
		{
			get { return result; }
			set
			{
				result = value;
				OnPropertyChanged( "Result" );
			}
		}

		/// <summary>
		/// List of calculation target options.
		/// </summary>
		public static string[] CalcTarget_src{ get; } = { "Orbital", "Escape" };

		/// <summary>
		/// Calculation target mode.
		/// </summary>
		private string calctarget;
		public string CalcTarget
		{
			get { return calctarget; }
			set
			{
				calctarget = value;
				OnPropertyChanged( "CalcTarget" );
				OnPropertyChanged( "IsCalcTargetOrbital" );
				OnPropertyChanged( "IsCalcTargetEscape" );
			}
		}

		public bool IsCalcTargetOrbital
		{
			get { return CalcTarget == CalcTarget_src[0]; }
		}

		public bool IsCalcTargetEscape
		{
			get { return CalcTarget == CalcTarget_src[1]; }
		}



		public ICommand Command_CalcCommand{ get; private set; }
		void CalcCommand()
		{
			string res = "";
			PropCalc pc = new PropCalc();

			try
			{
				if (AltCur <= 175)// ~95NM
				{
					Result = "invalid current altitude";
					return;
				}
				if (PLMass <= 0)
				{
					Result = "invalid payload mass";
					return;
				}
				if ((RCSTanks < 1) || (RCSTanks > 3))
				{
					Result = "invalid RCS tanks";
					return;
				}
				if (IsCalcTargetOrbital)
				{
					if (AltTgt <= AltCur)
					{
						Result = "invalid target altitude";
						return;
					}
					pc.IUS_Orbital( AltCur, AltTgt, DInc1, DInc2, PLMass, RCSTanks, true, ref calcload1, ref calcload2, ref res );
				}
				else
				{
					pc.IUS_Escape( AltCur, C3Tgt, PLMass, RCSTanks, true, ref calcload1, ref calcload2, ref res );
				}

				Result = res;
			}
			catch (Exception)
			{
				Result = "error";
			}
			return;
		}
		private bool CalcCommandEnabled()
		{
			return true;
		}

		public ICommand Command_SaveCommand{ get; private set; }
		void SaveCommand()
		{
			FirstStageLoad = Math.Round( calcload1, 2 );
			SecondStageLoad = Math.Round( calcload2, 2 );
			return;
		}
		private bool SaveCommandEnabled()
		{
			return true;
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

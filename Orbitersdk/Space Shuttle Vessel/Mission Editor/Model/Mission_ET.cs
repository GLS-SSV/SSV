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
/******* SSV File Modification Notice *******
Date         Developer
2020/05/31   GLS
2020/06/28   GLS
2020/06/30   GLS
2020/07/01   GLS
2020/07/08   GLS
2021/08/08   GLS
2021/12/11   GLS
2022/06/24   GLS
2022/08/05   GLS
2023/09/14   GLS
********************************************/

using System.ComponentModel;
using Newtonsoft.Json.Linq;


namespace SSVMissionEditor.model
{
	public enum ET_Type
{
		SWT = 0,
		LWT,
		SLWT
	}

	public class Mission_ET : INotifyPropertyChanged
	{
		public Mission_ET()
		{
			LoadDefault();
		}

		public void LoadDefault()
		{
			Type = ET_Type.SLWT;
			Texture = "SLWT";
			FRL = false;
			Bipod_Ramps = true;
			PAL_Ramps = true;
			return;
		}

		public void Load_V1( JToken jtk )
		{
			string strtmp = (string)jtk["Type"];
			int inttmp = Mission.String2EnumIdx( Type, strtmp );
			if (inttmp >= 0) Type = (ET_Type)inttmp;
			else Type = ET_Type.SLWT;

			Texture = (string)jtk["Texture"];

			if (Type == ET_Type.SWT)
			{
				FRL = (bool)jtk["FRL"];
			}
			else if (Type == ET_Type.SLWT)
			{
				Bipod_Ramps = (bool)jtk["Bipod Ramps"];
				PAL_Ramps = (bool)jtk["PAL Ramps"];
			}
			return;
		}

		public void Load_V2( JToken jtk )
		{
			Load_V1( jtk );
			return;
		}

		public JObject Save_V2()
		{
			JObject jobj = new JObject();

			jobj["Type"] = Type.ToString();
			jobj["Texture"] = Texture;
			jobj["FRL"] = FRL;
			jobj["Bipod Ramps"] = Bipod_Ramps;
			jobj["PAL Ramps"] = PAL_Ramps;
			return jobj;
		}


		private ET_Type type;
		public ET_Type Type
		{
			get { return type; }
			set
			{
				type = value;
				OnPropertyChanged( "Type" );
			}
		}

		/// <summary>
		/// The name of the ET texture
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

		/// <summary>
		/// Does the ET have FRL (for SWT ET only)
		/// </summary>
		private bool frl;
		public bool FRL
		{
			get { return frl; }
			set
			{
				frl = value;
				OnPropertyChanged( "FRL" );
			}
		}

		/// <summary>
		/// Does the ET have Bipod Ramps (for SLWT ET only)
		/// </summary>
		private bool bipod_ramps;
		public bool Bipod_Ramps
		{
			get { return bipod_ramps; }
			set
			{
				bipod_ramps = value;
				OnPropertyChanged( "Bipod_Ramps" );
			}
		}

		/// <summary>
		/// Does the ET have PAL Ramps (for SLWT ET only)
		/// </summary>
		private bool pal_ramps;
		public bool PAL_Ramps
		{
			get { return pal_ramps; }
			set
			{
				pal_ramps = value;
				OnPropertyChanged( "PAL_Ramps" );
			}
		}


		public event PropertyChangedEventHandler PropertyChanged;
		private void OnPropertyChanged( string prop )
		{
			PropertyChanged?.Invoke( this, new PropertyChangedEventArgs( prop ) );
		}
	}
}

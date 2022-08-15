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
2021/12/09   GLS
2022/06/24   GLS
2022/08/05   GLS
********************************************/

using System.ComponentModel;
using Newtonsoft.Json.Linq;


namespace SSVMissionEditor.model
{
	public enum SRM_Type
{
		SPM = 0,
		HPM,
		FWC,
		RSRM
	}

	public class Mission_SRB : INotifyPropertyChanged
	{
		public Mission_SRB()
		{
			LoadDefault();
		}

		public void LoadDefault()
		{
			SRM = SRM_Type.RSRM;
			LHFwdAssemblyTexture = "LH_fwd_assembly_5thmod";
			RHFwdAssemblyTexture = "RH_fwd_assembly_5thmod";
			LHCaseTexture = "case_9thmod";
			RHCaseTexture = "case_9thmod";
			return;
		}

		public void Load_V1( JToken jtk )
		{
			string strtmp = (string)jtk["SRM"];
			int inttmp = Mission.String2EnumIdx( SRM, strtmp );
			if (inttmp >= 0) SRM = (SRM_Type)inttmp;
			else SRM = SRM_Type.HPM;

			LHFwdAssemblyTexture = (string)jtk["LH Fwd Assembly Texture"];
			RHFwdAssemblyTexture = (string)jtk["RH Fwd Assembly Texture"];
			LHCaseTexture = (string)jtk["LH Case Texture"];
			RHCaseTexture = (string)jtk["RH Case Texture"];
			return;
		}

		public JObject Save_V1()
		{
			JObject jobj = new JObject();

			jobj["SRM"] = SRM.ToString();

			jobj["LH Fwd Assembly Texture"] = LHFwdAssemblyTexture;
			jobj["RH Fwd Assembly Texture"] = RHFwdAssemblyTexture;
			jobj["LH Case Texture"] = LHCaseTexture;
			jobj["RH Case Texture"] = RHCaseTexture;
			return jobj;
		}


		private SRM_Type srm;
		public SRM_Type SRM
		{
			get { return srm; }
			set
			{
				srm = value;
				OnPropertyChanged( "SRM" );
			}
		}

		/// <summary>
		/// The name of the LH SRB Fwd Assembly texture suffix
		/// </summary>
		private string lhfwdassemblytexture;
		public string LHFwdAssemblyTexture
		{
			get { return lhfwdassemblytexture; }
			set
			{
				lhfwdassemblytexture = value;
				OnPropertyChanged( "LHFwdAssemblyTexture" );
			}
		}

		/// <summary>
		/// The name of the RH SRB Fwd Assembly texture suffix
		/// </summary>
		private string rhfwdassemblytexture;
		public string RHFwdAssemblyTexture
		{
			get { return rhfwdassemblytexture; }
			set
			{
				rhfwdassemblytexture = value;
				OnPropertyChanged( "RHFwdAssemblyTexture" );
			}
		}

		/// <summary>
		/// The name of the LH SRB Case texture suffix
		/// </summary>
		private string lhcasetexture;
		public string LHCaseTexture
		{
			get { return lhcasetexture; }
			set
			{
				lhcasetexture = value;
				OnPropertyChanged( "LHCaseTexture" );
			}
		}

		/// <summary>
		/// The name of the RH SRB Case texture suffix
		/// </summary>
		private string rhcasetexture;
		public string RHCaseTexture
		{
			get { return rhcasetexture; }
			set
			{
				rhcasetexture = value;
				OnPropertyChanged( "RHCaseTexture" );
			}
		}


		public event PropertyChangedEventHandler PropertyChanged;
		private void OnPropertyChanged( string prop )
		{
			PropertyChanged?.Invoke( this, new PropertyChangedEventArgs( prop ) );
		}
	}
}

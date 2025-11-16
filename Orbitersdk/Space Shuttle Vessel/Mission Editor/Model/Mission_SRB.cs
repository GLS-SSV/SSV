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
2025/06/21   GLS
2025/09/26   GLS
********************************************/

using Newtonsoft.Json.Linq;


namespace SSVMissionEditor.Model
{
	public enum SRM_Type
{
		SPM = 0,
		HPM,
		FWC,
		RSRM
	}

	public class Mission_SRB
	{
		public Mission_SRB()
		{
			LoadDefault();
		}

		public void LoadDefault()
		{
			SRM = Defs.strRSRM;
			LHFwdAssemblyTexture = "LH_fwd_assembly_5thmod";
			RHFwdAssemblyTexture = "RH_fwd_assembly_5thmod";
			LHCaseTexture = "case_9thmod";
			RHCaseTexture = "case_9thmod";
			return;
		}

		public void Load_V1( JToken jtk )
		{
			string strtmp = (string)jtk["SRM"];
			if (strtmp == Defs.strSPM) SRM = Defs.strSPM;
			else if (strtmp == Defs.strHPM) SRM = Defs.strHPM;
			else if (strtmp == Defs.strFWC) SRM = Defs.strFWC;
			else if (strtmp == Defs.strRSRM) SRM = Defs.strRSRM;
			else
			{
				// TODO kaput
			}

			LHFwdAssemblyTexture = (string)jtk["LH Fwd Assembly Texture"];
			RHFwdAssemblyTexture = (string)jtk["RH Fwd Assembly Texture"];
			LHCaseTexture = (string)jtk["LH Case Texture"];
			RHCaseTexture = (string)jtk["RH Case Texture"];
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

			jobj["SRM"] = SRM;

			jobj["LH Fwd Assembly Texture"] = LHFwdAssemblyTexture;
			jobj["RH Fwd Assembly Texture"] = RHFwdAssemblyTexture;
			jobj["LH Case Texture"] = LHCaseTexture;
			jobj["RH Case Texture"] = RHCaseTexture;
			return jobj;
		}


		/// <summary>
		/// SRM type
		/// </summary>
		public string SRM { get; set; }

		/// <summary>
		/// The name of the LH SRB Fwd Assembly texture
		/// </summary>
		public string LHFwdAssemblyTexture { get; set; }

		/// <summary>
		/// The name of the RH SRB Fwd Assembly texture
		/// </summary>
		public string RHFwdAssemblyTexture { get; set; }

		/// <summary>
		/// The name of the LH SRB Case texture
		/// </summary>
		public string LHCaseTexture { get; set; }

		/// <summary>
		/// The name of the RH SRB Case texture
		/// </summary>
		public string RHCaseTexture { get; set; }
	}
}

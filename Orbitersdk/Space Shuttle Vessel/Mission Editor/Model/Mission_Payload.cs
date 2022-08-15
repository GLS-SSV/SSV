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

using System.Collections.Generic;
using System.ComponentModel;
using Newtonsoft.Json.Linq;


namespace SSVMissionEditor.model
{
	public class Mission_Payload : Mission_Vessel
	{
		public Mission_Payload()
		{
			VesselClass = "";
			Name = "";
			ScnParams = "";
			AttachmentID = 0;
		}

		public override void LoadDefault()
		{
			VesselClass = "";
			Name = "";
			ScnParams = "";
			AttachmentID = 0;
			return;
		}

		public override void LoadEmpty()
		{
			LoadDefault();
			return;
		}

		public override void Load_V1( JToken jtk )
		{
			VesselClass = (string)jtk["Vessel Class"];
			Name = (string)jtk["Name"];
			AttachmentID = (int)jtk["Attachment ID"];
			JToken jscn = jtk["Scenario Params"];
			if (jscn != null)
			{
				List<string> scnparams = jscn.ToObject<List<string>>();
				foreach (string tmp in scnparams)
				{
					ScnParams += tmp + System.Environment.NewLine;
				}
			}
			return;
		}

		public override JObject Save_V1()
		{
			JObject jobj = new JObject();

			jobj["Vessel Class"] = VesselClass;
			jobj["Name"] = Name;
			jobj["Attachment ID"] = AttachmentID;
			JArray jscnparams = new JArray();
			string[] scnparamlist = ScnParams.Split( new[] { "\r\n", "\r", "\n" }, System.StringSplitOptions.RemoveEmptyEntries );
			foreach (string tmp in scnparamlist) if (tmp.Length != 0) jscnparams.Add( tmp );
			jobj["Scenario Params"] = jscnparams;
			return jobj;
		}


		/// <summary>
		/// Attachment ID
		/// </summary>
		private int attachmentid;
		public int AttachmentID
		{
			get { return attachmentid; }
			set
			{
				attachmentid = value;
				OnPropertyChanged( "AttachmentID" );
			}
		}
	}
}

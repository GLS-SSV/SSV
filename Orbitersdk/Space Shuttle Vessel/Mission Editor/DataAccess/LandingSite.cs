using System.Collections.Generic;
using System.IO;


namespace SSVMissionEditor.DataAccess
{
	/**
	 * Loads landing site database from file, and provides access to it.
	 */
	public class LandingSite
	{
		private const string lsDBfilepath = "Config\\SSV_RunwayDB.csv";

		public class LandingSiteData
		{
			public string id;
			public string sitename;
			public string rwname;
			public string lat;// [rad]
			public string lon;// [rad]
			public string amsl;// [m]
			public string hdg;// [deg]
			public string lgt;// [ft]
		}


		public LandingSite( string orbiterpath )
		{
			LoadDB( orbiterpath );
		}

		public void LoadDB( string orbiterpath )
		{
			landingsitedb = new List<LandingSiteData>();

			string line;
			StreamReader file = new StreamReader( orbiterpath + lsDBfilepath );
			while ((line = file.ReadLine()) != null)
			{
				// format: id,site name,rw name,lat(n)[rad],lon(e)[rad],amsl[m],hdg[deg],lgt[ft]
				string[] items = line.Split( ',' );
				if (items.Length != 8)
				{
					// TODO error msg?
					continue;
				}
				LandingSiteData lsd = new LandingSiteData
				{
					id = items[0],
					sitename = items[1],
					rwname = items[2],
					lat = items[3],
					lon = items[4],
					amsl = items[5],
					hdg = items[6],
					lgt = items[7]
				};

				landingsitedb.Add( lsd );
			}
			file.Close();
			return;
		}

		public List<string> GetLandingSiteNames()
		{
			List<string> lsnames = new List<string>();
			foreach (LandingSiteData ls in landingsitedb)
			{
				lsnames.Add( ls.rwname + " - " + ls.sitename );
			}
			return lsnames;
		}

		public LandingSiteData GetLandingSite( int idx )
		{
			if ((idx < 0) || (idx >= landingsitedb.Count)) return null;
			return landingsitedb[idx];
		}

		public LandingSiteData FindLandingSite( string rw )
		{
			foreach (LandingSiteData ls in landingsitedb)
			{
				if (ls.id == rw) return ls;
			}
			return null;
		}

		private List<LandingSiteData> landingsitedb;
		public List<LandingSiteData> LandingSiteDB { get; }
	}
}

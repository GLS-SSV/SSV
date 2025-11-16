using System;
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
			public string RUNWAY_NAME;
			public string RW_LAT;// [rad]
			public string RW_LON;// [rad]
			public string RUNWAY_ALT;// [ft]
			public string RW_AZIMUTH;// [rad]
			public string RW_LENGTH;// [ft]
			public string RW_DELH;// [ft]
			public string RW_MAG_VAR;// [rad]
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
				// format: id,site name,RUNWAY_NAME,RW_LAT[rad],RW_LON[rad],RUNWAY_ALT[ft],RW_AZIMUTH[rad],RW_LENGTH[ft],RW_DELH[ft],RW_MAG_VAR[rad]
				string[] items = line.Split( ',' );
				if (items.Length != 10)
				{
					// kaput
					throw new Exception( "Landing Site database bad line" );
				}
				LandingSiteData lsd = new LandingSiteData
				{
					id = items[0],
					sitename = items[1],
					RUNWAY_NAME = items[2],
					RW_LAT = items[3],
					RW_LON = items[4],
					RUNWAY_ALT = items[5],
					RW_AZIMUTH = items[6],
					RW_LENGTH = items[7],
					RW_DELH = items[8],
					RW_MAG_VAR = items[9]
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
				lsnames.Add( ls.RUNWAY_NAME + " - " + ls.sitename );
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

		public LandingSiteData FindLandingSite_byRUNWAY_NAME( string rwname )
		{
			foreach (LandingSiteData ls in landingsitedb)
			{
				if (ls.RUNWAY_NAME == rwname) return ls;
			}
			return null;
		}

		private List<LandingSiteData> landingsitedb;
	}
}

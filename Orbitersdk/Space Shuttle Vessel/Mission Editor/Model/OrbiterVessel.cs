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
2020/07/01   GLS
2021/12/25   GLS
2022/06/24   GLS
2022/08/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra Workbench

  Space Shuttle Ultra is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Ultra is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Ultra; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file Doc\Space Shuttle Ultra\GPL.txt for more details.

  **************************************************************************/

using System;
using System.Collections.Generic;


namespace SSVMissionEditor.model
{
	public class OrbiterVessel
	{
		public OrbiterVessel()
		{
			poslat = -1.0;
			poslon = -1.0;
			heading = -1.0;
			rposx = -1.0;
			rposy = -1.0;
			rposz = -1.0;
			rvelx = -1.0;
			rvely = -1.0;
			rvelz = -1.0;
			elements_date = -1.0;
			arotx = -1.0;
			aroty = -1.0;
			arotz = -1.0;
			vrotx = -1.0;
			vroty = -1.0;
			vrotz = -1.0;
			fuel = -1.0;
			alt = -9999.0;
			rcsmode = -1;
			afcmode = -1;
			xpdr = -1;
			prplevel = new List<Tuple<int,double>>();
			thlevel = new List<Tuple<int,double>>();
			dockinfo = new List<Tuple<int,int,string>>();
			attached = new List<Tuple<int,int,string>>();
			otherparams = new List<string>();

			save = true;
		}

		public void Save( System.IO.StreamWriter scn )
		{
			if (save == false) return;
			// header
			scn.WriteLine( name + ":" + _class );

			// standard params
			scn.WriteLine( "  STATUS " + (statuslanded ? "Landed" : "Orbiting") +  " " + statusplanet );

			if ((statuslanded) && (attached.Count == 0))
			{
				if (!String.IsNullOrEmpty( _base )) scn.WriteLine( "  BASE " + _base );
				else if ((poslon != -1.0) && (poslat != -1.0)) scn.WriteLine( "  POS " + string.Format( "{0:f7} {1:f7}", poslon, poslat ).Replace( ',', '.' ) );
				if (heading != -1.0) scn.WriteLine( "  HEADING " + string.Format( "{0:f2}", heading ).Replace( ',', '.' ) );
				if (alt != -9999.0) scn.WriteLine( "  ALT " + string.Format( "{0:f3}", alt ).Replace( ',', '.' ) );
				if ((arotx != -1.0) && (aroty != -1.0) && (arotz != -1.0)) scn.WriteLine( "  AROT " + string.Format( "{0:f3} {1:f3} {2:f3}", arotx, aroty, arotz ).Replace( ',', '.' ) );
			}
			else
			{
				if ((rposx != -1.0) && (rposy != -1.0) && (rposz != -1.0)) scn.WriteLine( "  RPOS " + string.Format( "{0:f3} {1:f3} {2:f3}", rposx, rposy, rposz ).Replace( ',', '.' ) );
				if ((rvelx != -1.0) && (rvely != -1.0) && (rvelz != -1.0)) scn.WriteLine( "  RVEL " + string.Format( "{0:f4} {1:f4} {2:f4}", rvelx, rvely, rvelz ).Replace( ',', '.' ) );
				if (elements_date != -1.0) scn.WriteLine( "  ELEMENTS " + string.Format( "{0:f4} {1:f4} {2:f4} {3:f4} {4:f4} {5:f4} {6:f4}", elements_a, elements_e, elements_i, elements_lan, elements_lp, elements_ml, elements_date ).Replace( ',', '.' ) );
				if ((arotx != -1.0) && (aroty != -1.0) && (arotz != -1.0)) scn.WriteLine( "  AROT " + string.Format( "{0:f3} {1:f3} {2:f3}", arotx, aroty, arotz ).Replace( ',', '.' ) );
				if ((vrotx != -1.0) && (vroty != -1.0) && (vrotz != -1.0)) scn.WriteLine( "  VROT " + string.Format( "{0:f3} {1:f3} {2:f3}", vrotx, vroty, vrotz ).Replace( ',', '.' ) );
			}

			string attch = "";
			for (int j = 0; j < attached.Count; j++)
			{
				attch = attch + " " + attached[j].Item1 + ":" + attached[j].Item2 + "," + attached[j].Item3;
			}
			if (attached.Count > 0) scn.WriteLine( "  ATTACHED" + attch );

			if (rcsmode != -1) scn.WriteLine( "  RCSMODE " + rcsmode );

			if (afcmode != -1) scn.WriteLine( "  AFCMODE " + afcmode );

			if (fuel != -1.0) scn.WriteLine( "  FUEL " + string.Format( "{0:f6}", fuel ).Replace( ',', '.' ) );

			string prplvl = "";
			for (int j = 0; j < prplevel.Count; j++)
			{
				prplvl = prplvl + " " + prplevel[j].Item1 + ":" + string.Format( "{0:f6}", prplevel[j].Item2 ).Replace( ',', '.' );
			}
			if (prplevel.Count > 0) scn.WriteLine( "  PRPLEVEL" + string.Format( "{0:f6}", prplvl ).Replace( ',', '.' ) );

			string thlvl = "";
			for (int j = 0; j < thlevel.Count; j++)
			{
				thlvl = thlvl + " " + thlevel[j].Item1 + ":" + string.Format( "{0:f6}", thlevel[j].Item2 ).Replace( ',', '.' );
			}
			if (thlevel.Count > 0) scn.WriteLine( "  THLEVEL" + string.Format( "{0:f6}", thlvl ).Replace( ',', '.' ) );

			string dcknf = "";
			for (int j = 0; j < dockinfo.Count; j++)
			{
				dcknf = dcknf + " " + dockinfo[j].Item1 + ":" + dockinfo[j].Item2 + "," + dockinfo[j].Item3;
			}
			if (dockinfo.Count > 0) scn.WriteLine( "  DOCKINFO" + dcknf );

			if (!String.IsNullOrEmpty( ids )) scn.WriteLine( "  IDS " + ids );

			if (!String.IsNullOrEmpty( navfreq )) scn.WriteLine( "  NAVFREQ " + navfreq );

			if (xpdr != -1) scn.WriteLine( "  XPDR " + xpdr );

			// other params
			SaveSpecificParams( scn );
			scn.WriteLine( "END" );
			return;
		}

		public virtual void PreSave( MissionPhase missionphase )
		{
			return;
		}

		protected virtual void SaveSpecificParams( System.IO.StreamWriter scn )
		{
			for (int i = 0; i < otherparams.Count; i++)
			{
				scn.WriteLine( "  " + otherparams[i] );
			}
			return;
		}


		protected string name;
		public string Name
		{
			get { return name; }
			set { name = value; }
		}

		protected string _class;
		public string Class
		{
			get { return _class; }
			set { _class = value; }
		}

		protected bool statuslanded;
		public bool StatusLanded
		{
			get { return statuslanded; }
			set { statuslanded = value; }
		}

		protected string statusplanet;
		public string StatusPlanet
		{
			get { return statusplanet; }
			set { statusplanet = value; }
		}

		protected string _base;

		protected double heading;

		protected double rposx;
		protected double rposy;
		protected double rposz;

		protected double rvelx;
		protected double rvely;
		protected double rvelz;

		protected double elements_a;
		protected double elements_e;
		protected double elements_i;
		protected double elements_lan;
		protected double elements_lp;
		protected double elements_ml;
		protected double elements_date;

		protected double arotx;
		protected double aroty;
		protected double arotz;

		protected double vrotx;
		protected double vroty;
		protected double vrotz;

		protected double fuel;

		protected double poslat;

		protected double poslon;

		protected double alt;

		protected int rcsmode;

		protected int afcmode;

		protected string ids;// HACK

		protected string navfreq;// HACK

		protected int xpdr;

		protected List<Tuple<int,double>> prplevel;

		protected List<Tuple<int,double>> thlevel;

		protected List<Tuple<int,int,string>> dockinfo;

		protected List<Tuple<int,int,string>> attached;
		public List<Tuple<int,int,string>> Attached
		{
			get { return attached; }
			set { attached = value; }
		}

		protected List<string> otherparams;
		public List<string> OtherParams
		{
			get { return otherparams; }
			set { otherparams = value; }
		}

		protected bool save;
	}
}

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
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;


namespace SSVMissionEditor
{
	public class Convert_LandingSiteTable_String : IValueConverter
	{
		public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
		{
			// model to viewer
			// retrieve each I-LOAD
			ObservableCollection<Mission_ILOAD> iloads = (ObservableCollection<Mission_ILOAD>)value;
			string RUNWAY_NAME = "";
			string RW_LENGTH = "";
			string RW_LAT = "";
			string RW_LON = "";
			foreach (Mission_ILOAD iload in iloads)
			{
				switch (iload.ID)
				{
					case "RUNWAY_NAME":
						RUNWAY_NAME = iload.Val;
						break;
					case "RW_LENGTH":
						RW_LENGTH = iload.Val;
						break;
					case "RW_LAT":
						RW_LAT = iload.Val;
						break;
					case "RW_LON":
						RW_LON = iload.Val;
						break;
				}
			}

			// process I-Loads into table
			return ((Landing)parameter).FormatLandingSiteTable( RUNWAY_NAME, RW_LENGTH, RW_LAT, RW_LON );
		}

		public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
		{
			// viewer to model
			throw new NotSupportedException();
		}
	}
	public class Convert_LandingSiteDB : IValueConverter
	{
		public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
		{
			// model to viewer
			List<model.Mission_OV.LandingSiteData> lsdb = (List<model.Mission_OV.LandingSiteData>)value;

			if (lsdb.Count == 0) return "";

			string[] list = new string[lsdb.Count];

			for (int i = 0; i < lsdb.Count; i++)
				list[i] = lsdb[i].id + " - " + lsdb[i].sitename;
			return list;
		}

		public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
		{
			// viewer to model
			throw new NotSupportedException();
		}
	}


	/// <summary>
	/// Interaction logic for Landing.xaml
	/// </summary>
	public partial class Landing : UserControl
	{
		private const string LINE = "+----+----------------------+--------+-------+\n";
		private const string HEADER = "| S  |                      |        |       |\n" +
						"| I  |      LOCATION        |  RWY   |  LG   |\n" +
						"| T  |                      |        |       |\n" +
						"| E  |                      |        |       |\n";

		private List<Tuple<string,string>> LowIncEarly()
		{
			List<Tuple<string,string>> lstable = new List<Tuple<string, string>>();
			lstable.Add( new Tuple<string,string>( "KSC15", "KSC33" ) );// 1
			lstable.Add( new Tuple<string,string>( "CBA17", "CBA35" ) );// 2
			lstable.Add( new Tuple<string,string>( "OOY18", "OOY36" ) );// 3
			lstable.Add( new Tuple<string,string>( "AAT02", "AAT20" ) );// 4
			lstable.Add( new Tuple<string,string>( "HNL08R", "HNL26L" ) );// 5
			lstable.Add( new Tuple<string,string>( "DDN11", "DDN29" ) );// 6
			lstable.Add( new Tuple<string,string>( "ROZ28", "ROZ10" ) );// 7
			lstable.Add( new Tuple<string,string>( "KIN06", "KIN24" ) );// 8
			lstable.Add( new Tuple<string,string>( "LRB04", "LRB22" ) );// 9
			lstable.Add( new Tuple<string,string>( "JDG31", "JDG13" ) );// 10
			lstable.Add( new Tuple<string,string>( "DNA05L", "DNA23R" ) );// 11
			lstable.Add( new Tuple<string,string>( "GDV03L", "GDV21R" ) );// 12
			lstable.Add( new Tuple<string,string>( "YNN14", "YNN32" ) );// 13
			lstable.Add( new Tuple<string,string>( "PMR13", "PMR31" ) );// 14
			lstable.Add( new Tuple<string,string>( "AMB15", "AMB33" ) );// 15
			lstable.Add( new Tuple<string,string>( "KKI15R", "KKI33L" ) );// 16
			lstable.Add( new Tuple<string,string>( "MYR36", "MYR18" ) );// 17
			lstable.Add( new Tuple<string,string>( "AHS18", "AHS36" ) );// 18
			lstable.Add( new Tuple<string,string>( "NOR17", "NOR23" ) );// 19
			lstable.Add( new Tuple<string,string>( "NOR05", "NOR35" ) );// 20
			lstable.Add( new Tuple<string,string>( "EDW05R", "EDW23L" ) );// 21
			lstable.Add( new Tuple<string,string>( "EDW15", "EDW33" ) );// 22
			lstable.Add( new Tuple<string,string>( "EDW35", "EDW17" ) );// 23
			lstable.Add( new Tuple<string,string>( "EDW22", "EDW04" ) );// 24
			lstable.Add( new Tuple<string,string>( "KSC15", "KSC33" ) );// 25

			lstable.Add( new Tuple<string,string>( "JTY36", "JTY18" ) );// 26
			lstable.Add( new Tuple<string,string>( "GUA06L", "GUA24R" ) );// 27
			lstable.Add( new Tuple<string,string>( "WAK28", "WAK10" ) );// 28
			lstable.Add( new Tuple<string,string>( "HNL08R", "HNL26L" ) );// 29
			lstable.Add( new Tuple<string,string>( "HAO12", "HAO30" ) );// 30
			lstable.Add( new Tuple<string,string>( "HAW13", "HAW31" ) );// 31
			lstable.Add( new Tuple<string,string>( "KSC15", "KSC33" ) );// 32
			lstable.Add( new Tuple<string,string>( "YNN14", "YNN32" ) );// 33
			lstable.Add( new Tuple<string,string>( "PMR13", "PMR31" ) );// 34
			lstable.Add( new Tuple<string,string>( "MCO36L", "MCO18R" ) );// 35
			lstable.Add( new Tuple<string,string>( "NZC18L", "NZC36R" ) );// 36
			lstable.Add( new Tuple<string,string>( "MCF04", "MCF22" ) );// 37
			lstable.Add( new Tuple<string,string>( "NID03", "NID21" ) );// 38
			lstable.Add( new Tuple<string,string>( "VBG12", "VBG30" ) );// 39
			lstable.Add( new Tuple<string,string>( "LNK18", "LNK36" ) );// 40
			lstable.Add( new Tuple<string,string>( "NOR17", "NOR23" ) );// 41
			lstable.Add( new Tuple<string,string>( "NOR05", "NOR35" ) );// 42
			lstable.Add( new Tuple<string,string>( "EDW15", "EDW33" ) );// 43
			lstable.Add( new Tuple<string,string>( "EDW18L", "EDW18L" ) );// 44
			lstable.Add( new Tuple<string,string>( "EDW22", "EDW04" ) );// 45
			return lstable;
		}

		private List<Tuple<string,string>> LowIncLate()
		{
			List<Tuple<string,string>> lstable = new List<Tuple<string, string>>();
			lstable.Add( new Tuple<string,string>( "KSC15", "KSC33" ) );// 1
			lstable.Add( new Tuple<string,string>( "BEN36", "BEN18" ) );// 2
			lstable.Add( new Tuple<string,string>( "OOY36", "OOY36" ) );// 3
			lstable.Add( new Tuple<string,string>( "MRN20", "MRN02" ) );// 4
			lstable.Add( new Tuple<string,string>( "BYD32", "BYD14" ) );// 5
			lstable.Add( new Tuple<string,string>( "BDA30", "BDA12" ) );// 6
			lstable.Add( new Tuple<string,string>( "AML01", "AML19" ) );// 7
			lstable.Add( new Tuple<string,string>( "GDV03L", "GDV21R" ) );// 8
			lstable.Add( new Tuple<string,string>( "DYS16", "DYS34" ) );// 9
			lstable.Add( new Tuple<string,string>( "MRN20", "MRN02" ) );// 10
			lstable.Add( new Tuple<string,string>( "BEN36", "BEN18" ) );// 11
			lstable.Add( new Tuple<string,string>( "ILM06", "ILM24" ) );// 12
			lstable.Add( new Tuple<string,string>( "BYD32", "BYD14" ) );// 13
			lstable.Add( new Tuple<string,string>( "NKT32L", "NKT23R" ) );// 14
			lstable.Add( new Tuple<string,string>( "EIP10", "EIP28" ) );// 15
			lstable.Add( new Tuple<string,string>( "LRB04", "LRB22" ) );// 16
			lstable.Add( new Tuple<string,string>( "KIN24", "KIN06" ) );// 17
			lstable.Add( new Tuple<string,string>( "AHS18", "AHS36" ) );// 18
			lstable.Add( new Tuple<string,string>( "AAT02", "AAT20" ) );// 19
			lstable.Add( new Tuple<string,string>( "GSA29", "GSA11" ) );// 20
			lstable.Add( new Tuple<string,string>( "KKI15R", "KKI33L" ) );// 21
			lstable.Add( new Tuple<string,string>( "JDG31", "JDG13" ) );// 22
			lstable.Add( new Tuple<string,string>( "PEA18L", "PEA36R" ) );// 23
			lstable.Add( new Tuple<string,string>( "PTN14", "PTN32" ) );// 24
			lstable.Add( new Tuple<string,string>( "AMB15", "AMB33" ) );// 25
			lstable.Add( new Tuple<string,string>( "JTY36", "JTY18" ) );// 26
			lstable.Add( new Tuple<string,string>( "GUA06L", "GUA24R" ) );// 27
			lstable.Add( new Tuple<string,string>( "WAK28", "WAK10" ) );// 28
			lstable.Add( new Tuple<string,string>( "HNL08R", "HNL26L" ) );// 29
			lstable.Add( new Tuple<string,string>( "HAO12", "HAO30" ) );// 30
			lstable.Add( new Tuple<string,string>( "HAW13", "HAW31" ) );// 31
			lstable.Add( new Tuple<string,string>( "KSC15", "KSC33" ) );// 32
			lstable.Add( new Tuple<string,string>( "YNN14", "YNN32" ) );// 33
			lstable.Add( new Tuple<string,string>( "PMR13", "PMR31" ) );// 34
			lstable.Add( new Tuple<string,string>( "MCO36L", "MCO18R" ) );// 35
			lstable.Add( new Tuple<string,string>( "NZC18L", "NZC36R" ) );// 36
			lstable.Add( new Tuple<string,string>( "MCF04", "MCF22" ) );// 37
			lstable.Add( new Tuple<string,string>( "NID03", "NID21" ) );// 38
			lstable.Add( new Tuple<string,string>( "VBG12", "VBG30" ) );// 39
			lstable.Add( new Tuple<string,string>( "EDT22R", "EDT04L" ) );// 40
			lstable.Add( new Tuple<string,string>( "NOR17", "NOR23" ) );// 41
			lstable.Add( new Tuple<string,string>( "NOR05", "NOR35" ) );// 42
			lstable.Add( new Tuple<string,string>( "EDW15", "EDW33" ) );// 43
			lstable.Add( new Tuple<string,string>( "EDW18L", "EDW18L" ) );// 44
			lstable.Add( new Tuple<string,string>( "EDW22", "EDW04" ) );// 45
			return lstable;
		}

		private List<Tuple<string,string>> MidIncEarly()
		{
			List<Tuple<string,string>> lstable = new List<Tuple<string, string>>();
			lstable.Add( new Tuple<string,string>( "KSC15", "KSC33" ) );// 1
			lstable.Add( new Tuple<string,string>( "CBA17", "CBA35" ) );// 2
			lstable.Add( new Tuple<string,string>( "OOY18", "OOY36" ) );// 3
			lstable.Add( new Tuple<string,string>( "AAT02", "AAT20" ) );// 4
			lstable.Add( new Tuple<string,string>( "HNL08R", "HNL26L" ) );// 5
			lstable.Add( new Tuple<string,string>( "DDN11", "DDN29" ) );// 6
			lstable.Add( new Tuple<string,string>( "ROZ28", "ROZ10" ) );// 7
			lstable.Add( new Tuple<string,string>( "KIN06", "KIN24" ) );// 8
			lstable.Add( new Tuple<string,string>( "LAJ15", "LAJ33" ) );// 9
			lstable.Add( new Tuple<string,string>( "JDG31", "JDG13" ) );// 10
			lstable.Add( new Tuple<string,string>( "DNA05L", "DNA23R" ) );// 11
			lstable.Add( new Tuple<string,string>( "GDV03L", "GDV21R" ) );// 12
			lstable.Add( new Tuple<string,string>( "KBO14L", "KBO32R" ) );// 13
			lstable.Add( new Tuple<string,string>( "ESN03R", "ESN21L" ) );// 14
			lstable.Add( new Tuple<string,string>( "AMB15", "AMB33" ) );// 15
			lstable.Add( new Tuple<string,string>( "KKI15R", "KKI33L" ) );// 16
			lstable.Add( new Tuple<string,string>( "MYR36", "MYR18" ) );// 17
			lstable.Add( new Tuple<string,string>( "AHS18", "AHS36" ) );// 18
			lstable.Add( new Tuple<string,string>( "GSA29", "GSA11" ) );// 19
			lstable.Add( new Tuple<string,string>( "NOR17", "NOR23" ) );// 20
			lstable.Add( new Tuple<string,string>( "NOR05", "NOR35" ) );// 21
			lstable.Add( new Tuple<string,string>( "EDW05R", "EDW23L" ) );// 22
			lstable.Add( new Tuple<string,string>( "EDW15", "EDW33" ) );// 23
			lstable.Add( new Tuple<string,string>( "EDW35", "EDW17" ) );// 24
			lstable.Add( new Tuple<string,string>( "EDW22", "EDW04" ) );// 25

			lstable.Add( new Tuple<string,string>( "JTY36", "JTY18" ) );// 26
			lstable.Add( new Tuple<string,string>( "GUA06L", "GUA24R" ) );// 27
			lstable.Add( new Tuple<string,string>( "WAK28", "WAK10" ) );// 28
			lstable.Add( new Tuple<string,string>( "HNL08R", "HNL26L" ) );// 29
			lstable.Add( new Tuple<string,string>( "HAO12", "HAO30" ) );// 30
			lstable.Add( new Tuple<string,string>( "HAW13", "HAW31" ) );// 31
			lstable.Add( new Tuple<string,string>( "ESN03R", "ESN21L" ) );// 32
			lstable.Add( new Tuple<string,string>( "YNN14", "YNN32" ) );// 33
			lstable.Add( new Tuple<string,string>( "PMR13", "PMR31" ) );// 34
			lstable.Add( new Tuple<string,string>( "MCO36L", "MCO18R" ) );// 35
			lstable.Add( new Tuple<string,string>( "NZC18L", "NZC36R" ) );// 36
			lstable.Add( new Tuple<string,string>( "GUS23", "GUS05" ) );// 37
			lstable.Add( new Tuple<string,string>( "MWH14L", "MWH32R" ) );// 38
			lstable.Add( new Tuple<string,string>( "FFO23R", "FFO05L" ) );// 39
			lstable.Add( new Tuple<string,string>( "LNK18", "LNK36" ) );// 40
			lstable.Add( new Tuple<string,string>( "NKT32L", "NKT23R" ) );// 41
			lstable.Add( new Tuple<string,string>( "FMH32", "FMH23" ) );// 42
			lstable.Add( new Tuple<string,string>( "PBG35", "PBG17" ) );// 43
			lstable.Add( new Tuple<string,string>( "RCA13", "RCA31" ) );// 44
			lstable.Add( new Tuple<string,string>( "CEF05", "CEF23" ) );// 45
			return lstable;
		}

		private List<Tuple<string,string>> MidIncLate()
		{
			List<Tuple<string,string>> lstable = new List<Tuple<string, string>>();
			lstable.Add( new Tuple<string,string>( "KSC15", "KSC33" ) );// 1
			lstable.Add( new Tuple<string,string>( "BEN36", "BEN18" ) );// 2
			lstable.Add( new Tuple<string,string>( "MRN20", "MRN02" ) );// 3
			lstable.Add( new Tuple<string,string>( "ZZA30L", "ZZA12R" ) );// 4
			lstable.Add( new Tuple<string,string>( "BYD32", "BYD14" ) );// 5
			lstable.Add( new Tuple<string,string>( "BDA30", "BDA12" ) );// 6
			lstable.Add( new Tuple<string,string>( "AML01", "AML19" ) );// 7
			lstable.Add( new Tuple<string,string>( "GDV03L", "GDV21R" ) );// 8
			lstable.Add( new Tuple<string,string>( "LAJ15", "LAJ33" ) );// 9
			lstable.Add( new Tuple<string,string>( "BEJ01L", "BEJ19R" ) );// 10
			lstable.Add( new Tuple<string,string>( "FMI33", "FMI15" ) );// 11
			lstable.Add( new Tuple<string,string>( "ILM06", "ILM24" ) );// 12
			lstable.Add( new Tuple<string,string>( "MRN20", "MRN02" ) );// 13
			lstable.Add( new Tuple<string,string>( "NKT32L", "NKT23R" ) );// 14
			lstable.Add( new Tuple<string,string>( "EIP10", "EIP28" ) );// 15
			lstable.Add( new Tuple<string,string>( "LRB04", "LRB22" ) );// 16
			lstable.Add( new Tuple<string,string>( "KIN24", "KIN06" ) );// 17
			lstable.Add( new Tuple<string,string>( "AHS18", "AHS36" ) );// 18
			lstable.Add( new Tuple<string,string>( "AAT02", "AAT20" ) );// 19
			lstable.Add( new Tuple<string,string>( "GSA29", "GSA11" ) );// 20
			lstable.Add( new Tuple<string,string>( "KKI15R", "KKI33L" ) );// 21
			lstable.Add( new Tuple<string,string>( "JDG31", "JDG13" ) );// 22
			lstable.Add( new Tuple<string,string>( "PEA18L", "PEA36R" ) );// 23
			lstable.Add( new Tuple<string,string>( "PTN14", "PTN32" ) );// 24
			lstable.Add( new Tuple<string,string>( "AMB15", "AMB33" ) );// 25
			lstable.Add( new Tuple<string,string>( "JTY36", "JTY18" ) );// 26
			lstable.Add( new Tuple<string,string>( "GUA06L", "GUA24R" ) );// 27
			lstable.Add( new Tuple<string,string>( "WAK28", "WAK10" ) );// 28
			lstable.Add( new Tuple<string,string>( "HNL08R", "HNL26L" ) );// 29
			lstable.Add( new Tuple<string,string>( "HAO12", "HAO30" ) );// 30
			lstable.Add( new Tuple<string,string>( "HAW13", "HAW31" ) );// 31
			lstable.Add( new Tuple<string,string>( "ESN03R", "ESN21L" ) );// 32
			lstable.Add( new Tuple<string,string>( "YNN14", "YNN32" ) );// 33
			lstable.Add( new Tuple<string,string>( "PMR13", "PMR31" ) );// 34
			lstable.Add( new Tuple<string,string>( "MCO36L", "MCO18R" ) );// 35
			lstable.Add( new Tuple<string,string>( "NZC18L", "NZC36R" ) );// 36
			lstable.Add( new Tuple<string,string>( "MCF04", "MCF22" ) );// 37
			lstable.Add( new Tuple<string,string>( "NID03", "NID21" ) );// 38
			lstable.Add( new Tuple<string,string>( "VBG12", "VBG30" ) );// 39
			lstable.Add( new Tuple<string,string>( "EDT22R", "EDT04L" ) );// 40
			lstable.Add( new Tuple<string,string>( "NOR17", "NOR23" ) );// 41
			lstable.Add( new Tuple<string,string>( "NOR05", "NOR35" ) );// 42
			lstable.Add( new Tuple<string,string>( "EDW15", "EDW33" ) );// 43
			lstable.Add( new Tuple<string,string>( "EDW18L", "EDW18L" ) );// 44
			lstable.Add( new Tuple<string,string>( "EDW22", "EDW04" ) );// 45
			return lstable;
		}

		private List<Tuple<string,string>> HighIncEarly()
		{
			List<Tuple<string,string>> lstable = new List<Tuple<string, string>>();
			lstable.Add( new Tuple<string,string>( "KSC15", "KSC33" ) );// 1
			lstable.Add( new Tuple<string,string>( "CBA17", "CBA35" ) );// 2
			lstable.Add( new Tuple<string,string>( "OOY18", "OOY36" ) );// 3
			lstable.Add( new Tuple<string,string>( "AAT02", "AAT20" ) );// 4
			lstable.Add( new Tuple<string,string>( "HNL08R", "HNL26L" ) );// 5
			lstable.Add( new Tuple<string,string>( "DDN11", "DDN29" ) );// 6
			lstable.Add( new Tuple<string,string>( "ROZ28", "ROZ10" ) );// 7
			lstable.Add( new Tuple<string,string>( "KIN06", "KIN24" ) );// 8
			lstable.Add( new Tuple<string,string>( "LAJ15", "LAJ33" ) );// 9
			lstable.Add( new Tuple<string,string>( "JDG31", "JDG13" ) );// 10
			lstable.Add( new Tuple<string,string>( "DNA05L", "DNA23R" ) );// 11
			lstable.Add( new Tuple<string,string>( "GDV03L", "GDV21R" ) );// 12
			lstable.Add( new Tuple<string,string>( "KBO14L", "KBO32R" ) );// 13
			lstable.Add( new Tuple<string,string>( "ESN03R", "ESN21L" ) );// 14
			lstable.Add( new Tuple<string,string>( "AMB15", "AMB33" ) );// 15
			lstable.Add( new Tuple<string,string>( "KKI15R", "KKI33L" ) );// 16
			lstable.Add( new Tuple<string,string>( "MYR36", "MYR18" ) );// 17
			lstable.Add( new Tuple<string,string>( "AHS18", "AHS36" ) );// 18
			lstable.Add( new Tuple<string,string>( "ARL01", "ARL19" ) );// 19
			lstable.Add( new Tuple<string,string>( "NOR17", "NOR23" ) );// 20
			lstable.Add( new Tuple<string,string>( "NOR05", "NOR35" ) );// 21
			lstable.Add( new Tuple<string,string>( "EDW05R", "EDW23L" ) );// 22
			lstable.Add( new Tuple<string,string>( "EDW15", "EDW33" ) );// 23
			lstable.Add( new Tuple<string,string>( "EDW35", "EDW17" ) );// 24
			lstable.Add( new Tuple<string,string>( "EDW22", "EDW04" ) );// 25

			lstable.Add( new Tuple<string,string>( "INN06", "INN24" ) );// 26
			lstable.Add( new Tuple<string,string>( "FFA27", "FFA09" ) );// 27
			lstable.Add( new Tuple<string,string>( "KBO14L", "KBO32R" ) );// 28
			lstable.Add( new Tuple<string,string>( "FMI33", "FMI15" ) );// 29
			lstable.Add( new Tuple<string,string>( "ESN03R", "ESN21L" ) );// 30
			lstable.Add( new Tuple<string,string>( "KKI15R", "KKI33L" ) );// 31
			lstable.Add( new Tuple<string,string>( "JDG31", "JDG13" ) );// 32
			lstable.Add( new Tuple<string,string>( "GUS23", "GUS05" ) );// 33
			lstable.Add( new Tuple<string,string>( "MWH14L", "MWH32R" ) );// 34
			lstable.Add( new Tuple<string,string>( "FFO23R", "FFO05L" ) );// 35
			lstable.Add( new Tuple<string,string>( "LNK18", "LNK36" ) );// 36
			lstable.Add( new Tuple<string,string>( "NKT32L", "NKT23R" ) );// 37
			lstable.Add( new Tuple<string,string>( "FMH32", "FMH23" ) );// 38
			lstable.Add( new Tuple<string,string>( "PBG35", "PBG17" ) );// 39
			lstable.Add( new Tuple<string,string>( "RCA13", "RCA31" ) );// 40
			lstable.Add( new Tuple<string,string>( "CEF23", "CEF05" ) );// 41
			lstable.Add( new Tuple<string,string>( "FFA27", "FFA09" ) );// 42
			lstable.Add( new Tuple<string,string>( "INN06", "INN06" ) );// 43
			lstable.Add( new Tuple<string,string>( "IKF11", "IKF29" ) );// 44
			lstable.Add( new Tuple<string,string>( "IKF29", "IKF02" ) );// 45
			return lstable;
		}

		private List<Tuple<string,string>> HighIncLate()
		{
			List<Tuple<string,string>> lstable = new List<Tuple<string, string>>();
			lstable.Add( new Tuple<string,string>( "KSC15", "KSC33" ) );// 1
			lstable.Add( new Tuple<string,string>( "BEN36", "BEN18" ) );// 2
			lstable.Add( new Tuple<string,string>( "MRN20", "MRN02" ) );// 3
			lstable.Add( new Tuple<string,string>( "ZZA30L", "ZZA12R" ) );// 4
			lstable.Add( new Tuple<string,string>( "MYR36", "MYR18" ) );// 5
			lstable.Add( new Tuple<string,string>( "ILM06", "ILM24" ) );// 6
			lstable.Add( new Tuple<string,string>( "NKT32L", "NKT23R" ) );// 7
			lstable.Add( new Tuple<string,string>( "NTU32R", "NTU23L" ) );// 8
			lstable.Add( new Tuple<string,string>( "WAL28", "WAL04" ) );// 9
			lstable.Add( new Tuple<string,string>( "DOV32", "DOV19" ) );// 10
			lstable.Add( new Tuple<string,string>( "ACY31", "ACY13" ) );// 11
			lstable.Add( new Tuple<string,string>( "BEN36", "BEN18" ) );// 12
			lstable.Add( new Tuple<string,string>( "MRN20", "MRN02" ) );// 13
			lstable.Add( new Tuple<string,string>( "ZZA30L", "ZZA12R" ) );// 14
			lstable.Add( new Tuple<string,string>( "FOK06", "FOK24" ) );// 15
			lstable.Add( new Tuple<string,string>( "FMH32", "FMH23" ) );// 16
			lstable.Add( new Tuple<string,string>( "PSM34", "PSM16" ) );// 17
			lstable.Add( new Tuple<string,string>( "YHZ23", "YHZ32" ) );// 18
			lstable.Add( new Tuple<string,string>( "YJT09", "YJT27" ) );// 19
			lstable.Add( new Tuple<string,string>( "YYT29", "YYT11" ) );// 20
			lstable.Add( new Tuple<string,string>( "YQX21", "YQX31" ) );// 21
			lstable.Add( new Tuple<string,string>( "YYR26", "YYR34" ) );// 22
			lstable.Add( new Tuple<string,string>( "LAJ15", "LAJ33" ) );// 23
			lstable.Add( new Tuple<string,string>( "BEJ01L", "BEJ19R" ) );// 24
			lstable.Add( new Tuple<string,string>( "IKF20", "IKF29" ) );// 25
			lstable.Add( new Tuple<string,string>( "INN06", "INN24" ) );// 26
			lstable.Add( new Tuple<string,string>( "FFA27", "FFA09" ) );// 27
			lstable.Add( new Tuple<string,string>( "KBO14L", "KBO32R" ) );// 28
			lstable.Add( new Tuple<string,string>( "FMI33", "FMI15" ) );// 29
			lstable.Add( new Tuple<string,string>( "ESN03R", "ESN21L" ) );// 30
			lstable.Add( new Tuple<string,string>( "KKI15R", "KKI33L" ) );// 31
			lstable.Add( new Tuple<string,string>( "JDG31", "JDG13" ) );// 32
			lstable.Add( new Tuple<string,string>( "AMB15", "PTN14" ) );// 33
			lstable.Add( new Tuple<string,string>( "JTY36", "JTY18" ) );// 34
			lstable.Add( new Tuple<string,string>( "GUA06L", "GUA24R" ) );// 35
			lstable.Add( new Tuple<string,string>( "WAK28", "WAK10" ) );// 36
			lstable.Add( new Tuple<string,string>( "HNL08R", "HNL26L" ) );// 37
			lstable.Add( new Tuple<string,string>( "EDF24", "EDF06" ) );// 38
			lstable.Add( new Tuple<string,string>( "HAO12", "HAO30" ) );// 39
			lstable.Add( new Tuple<string,string>( "EDT22R", "EDT04L" ) );// 40
			lstable.Add( new Tuple<string,string>( "HAW13", "HAW31" ) );// 41
			lstable.Add( new Tuple<string,string>( "NOR17", "NOR23" ) );// 42
			lstable.Add( new Tuple<string,string>( "NOR05", "NOR35" ) );// 43
			lstable.Add( new Tuple<string,string>( "EDW15", "EDW18L" ) );// 44
			lstable.Add( new Tuple<string,string>( "EDW22", "EDW04" ) );// 45
			return lstable;
		}

		private List<Tuple<string,string>> WTR()
		{
			List<Tuple<string,string>> lstable = new List<Tuple<string, string>>();
			lstable.Add( new Tuple<string,string>( "VBG30", "VBG12" ) );// 1
			lstable.Add( new Tuple<string,string>( "NKX24R", "NKX06L" ) );// 2
			lstable.Add( new Tuple<string,string>( "EIP28", "EIP10" ) );// 3
			lstable.Add( new Tuple<string,string>( "HAO12", "HAO30" ) );// 4
			lstable.Add( new Tuple<string,string>( "KSC15", "KSC33" ) );// 5
			lstable.Add( new Tuple<string,string>( "HNL08R", "HNL26L" ) );// 6
			lstable.Add( new Tuple<string,string>( "AAT02", "AAT20" ) );// 7
			lstable.Add( new Tuple<string,string>( "KBO14L", "KBO32R" ) );// 8
			lstable.Add( new Tuple<string,string>( "DNA05L", "DNA23R" ) );// 9
			lstable.Add( new Tuple<string,string>( "CBA17", "CBA35" ) );// 10
			lstable.Add( new Tuple<string,string>( "ARL01", "ARL19" ) );// 11
			lstable.Add( new Tuple<string,string>( "EDF24", "EDF06" ) );// 12
			lstable.Add( new Tuple<string,string>( "AHS18", "AHS36" ) );// 13
			lstable.Add( new Tuple<string,string>( "EST17", "EST35" ) );// 14
			lstable.Add( new Tuple<string,string>( "DDN11", "DDN29" ) );// 15
			lstable.Add( new Tuple<string,string>( "JDG31", "JDG13" ) );// 16
			lstable.Add( new Tuple<string,string>( "PBG35", "PBG17" ) );// 17
			lstable.Add( new Tuple<string,string>( "RCA13", "RCA31" ) );// 18
			lstable.Add( new Tuple<string,string>( "NOR17", "NOR23" ) );// 19
			lstable.Add( new Tuple<string,string>( "NOR05", "NOR35" ) );// 20
			lstable.Add( new Tuple<string,string>( "EDW05R", "EDW23L" ) );// 21
			lstable.Add( new Tuple<string,string>( "EDW15", "EDW33" ) );// 22
			lstable.Add( new Tuple<string,string>( "EDW35", "EDW17" ) );// 23
			lstable.Add( new Tuple<string,string>( "EDW22", "EDW04" ) );// 24
			lstable.Add( new Tuple<string,string>( "KSC15", "KSC33" ) );// 25

			lstable.Add( new Tuple<string,string>( "INN06", "INN24" ) );// 26
			lstable.Add( new Tuple<string,string>( "FFA27", "FFA09" ) );// 27
			lstable.Add( new Tuple<string,string>( "KBO14L", "KBO32R" ) );// 28
			lstable.Add( new Tuple<string,string>( "FMI33", "FMI15" ) );// 29
			lstable.Add( new Tuple<string,string>( "ESN03R", "ESN21L" ) );// 30
			lstable.Add( new Tuple<string,string>( "KKI15R", "KKI33L" ) );// 31
			lstable.Add( new Tuple<string,string>( "JDG31", "JDG13" ) );// 32
			lstable.Add( new Tuple<string,string>( "GUS23", "GUS05" ) );// 33
			lstable.Add( new Tuple<string,string>( "MWH14L", "MWH32R" ) );// 34
			lstable.Add( new Tuple<string,string>( "FFO23R", "FFO05L" ) );// 35
			lstable.Add( new Tuple<string,string>( "LNK18", "LNK36" ) );// 36
			lstable.Add( new Tuple<string,string>( "NKT32L", "NKT23R" ) );// 37
			lstable.Add( new Tuple<string,string>( "FMH32", "FMH23" ) );// 38
			lstable.Add( new Tuple<string,string>( "PBG35", "PBG17" ) );// 39
			lstable.Add( new Tuple<string,string>( "RCA13", "RCA31" ) );// 40
			lstable.Add( new Tuple<string,string>( "CEF23", "CEF05" ) );// 41
			lstable.Add( new Tuple<string,string>( "FFA27", "FFA09" ) );// 42
			lstable.Add( new Tuple<string,string>( "INN06", "INN06" ) );// 43
			lstable.Add( new Tuple<string,string>( "IKF11", "IKF29" ) );// 44
			lstable.Add( new Tuple<string,string>( "IKF29", "IKF02" ) );// 45
			return lstable;
		}


		public Landing()
		{
			InitializeComponent();

			rbPri.IsChecked = true;

			for (int i = 1; i <= 45; i++) cmbLSID.Items.Add( i );
			cmbLSID.SelectedIndex = 0;

			txtLandingSiteOut.SetBinding( TextBox.TextProperty, new Binding
			{
				Mode = BindingMode.OneWay,
				Path = new PropertyPath( "OV.ILOAD_List" ),
				Converter = new Convert_LandingSiteTable_String(),
				ConverterParameter = this
				//Binding OV.ILOAD_List, Mode=OneWay, UpdateSourceTrigger=PropertyChanged, Converter={StaticResource Convert_ILOAD_TgtSet}
			});

			cmbLSListPreset.Items.Add( "Low Inclination: 28.45º - 30.9º (Early)" );
			cmbLSListPreset.Items.Add( "Low Inclination: 28.45º - 30.9º (Late)" );
			cmbLSListPreset.Items.Add( "Mid Inclination: 31.0º - 49.9º (Early)" );
			cmbLSListPreset.Items.Add( "Mid Inclination: 31.0º - 49.9º (Late)" );
			cmbLSListPreset.Items.Add( "High Inclination: 50.0º - 63.5º (Early)" );
			cmbLSListPreset.Items.Add( "High Inclination: 50.0º - 63.5º (Late)" );
			cmbLSListPreset.Items.Add( "Western Test Range" );
			cmbLSListPreset.SelectedIndex = -1;
			return;
		}
		
		public string FormatLandingSiteTable( string RUNWAY_NAME, string RW_LENGTH, string RW_LAT, string RW_LON )
		{
			string strls = "";

			char[] spc = {' '};
			string[] runway_name = RUNWAY_NAME.Split( spc, StringSplitOptions.RemoveEmptyEntries );
			string[] rw_length = RW_LENGTH.Split( spc, StringSplitOptions.RemoveEmptyEntries );
			string[] rw_lat = RW_LAT.Split( spc, StringSplitOptions.RemoveEmptyEntries );
			string[] rw_lon = RW_LON.Split( spc, StringSplitOptions.RemoveEmptyEntries );

			if (runway_name.Length != 90) return "";
			if (rw_length.Length != 90) return "";
			if (rw_lat.Length != 90) return "";
			if (rw_length.Length != 90) return "";

			model.Mission msn = (model.Mission)DataContext;
			List<model.Mission_OV.LandingSiteData> lsDB = msn.OV.LandingSiteDB;
			string[] sitename = new string[90];
			string[] rwy = new string[90];
			for (int i = 0; i < 90; i++)
			{
				// find runway in DB
				int idx = lsDB.FindIndex( item => (item.RUNWAY_NAME == runway_name[i]) && (item.RW_LAT == rw_lat[i]) && (item.RW_LON == rw_lon[i]) );
				if (idx != -1)
				{
					sitename[i] = lsDB[idx].sitename;
					rwy[i] = lsDB[idx].id;
				}
				else
				{
					sitename[i] = "???";
					rwy[i] = runway_name[i];
				}
			}

			strls += LINE + HEADER;
			for (int lsid = 1; lsid <= 45; lsid++)
			{
				string prisite = "";
				string loc = "";
				string lgt = "";

				//// primary rwy ////
				loc = sitename[(lsid - 1) * 2];
				prisite = loc;
				lgt = rw_length[(lsid - 1) * 2];

				strls += LINE;
				// SITE: len 2
				strls += "| " + lsid.ToString().PadRight( 2 ) + " | ";
				// LOCATION: len 20
				strls += loc.PadRight( 20 ) + " | ";
				// RWY: len 6
				strls += rwy[(lsid - 1) * 2].PadRight( 6 ) + " | ";
				// LG: len 5
				strls += lgt.PadLeft( 5 ) + " |\n";

				//// secondary rwy ////
				loc = sitename[((lsid - 1) * 2) + 1];
				lgt = rw_length[((lsid - 1) * 2) + 1];

				// SITE: len 2
				strls += "|    | ";
				// LOCATION: len 20
				if (loc == prisite) loc = "";
				strls += loc.PadRight( 20 ) + " | ";
				// RWY: len 6
				strls += rwy[((lsid - 1) * 2) + 1].PadRight( 6 ) + " | ";
				// LG: len 5
				strls += lgt.PadLeft( 5 ) + " |\n";
			}
			strls += LINE;
			return strls;
		}
		
		public string FormatLandingSiteDB( int idx )
		{
			List<model.Mission_OV.LandingSiteData> lsDB = ((model.Mission)DataContext).OV.LandingSiteDB;

			string strls = "Location: " + lsDB[idx].sitename + "\n" +
				"Runway: " + lsDB[idx].RUNWAY_NAME + "\n";

			if (lsDB[idx].RW_LENGTH != "0")
			{
				double lat = Math.Round( double.Parse( lsDB[idx].RW_LAT ) * Defs.DEG, 6 );
				double lon = Math.Round( double.Parse( lsDB[idx].RW_LON ) * Defs.DEG, 6 );
				double az = Math.Round( double.Parse( lsDB[idx].RW_AZIMUTH ) * Defs.DEG, 2 );
				double alt_m = Math.Round( double.Parse( lsDB[idx].RUNWAY_ALT ) * 0.3048, 1 );
				double delh_m = Math.Round( double.Parse( lsDB[idx].RW_DELH ) * 0.3048, 1 );
				double mvar = Math.Round( double.Parse( lsDB[idx].RW_MAG_VAR ) * Defs.DEG, 2 );
				strls += "Lat: " + lat + "º   Lon: " + lon + "º\n" +
					"Altitude: " + lsDB[idx].RUNWAY_ALT + "ft (" + alt_m + "m)\n" +
					"Azimuth: " + az + "º\n" +
					"Length: " + lsDB[idx].RW_LENGTH + "ft\n" +
					"MSL: " + lsDB[idx].RW_DELH + "ft (" + delh_m + "m)\n" +
					"Mag. Var.: " + mvar + "º";
			}
			else
			{
				strls += "(runway not implemented)";
			}
			return strls;
		}

		private void CmbLandingSiteDB_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			if (cmbLandingSiteDB.SelectedIndex < 0) txtRunwayInfo.Text = "";
			else txtRunwayInfo.Text = FormatLandingSiteDB( cmbLandingSiteDB.SelectedIndex );
			return;
		}

		private void BtnSetRunway_Click(object sender, RoutedEventArgs e)
		{
			if (cmbLandingSiteDB.SelectedIndex < 0) return;
			if (cmbLSID.SelectedIndex < 0) return;

			List<model.Mission_OV.LandingSiteData> lsDB = ((model.Mission)DataContext).OV.LandingSiteDB;

			int idx = cmbLSID.SelectedIndex * 2;
			if (rbPri.IsChecked == false) idx++;

			// get current list
			string RUNWAY_ALT = "";
			string RUNWAY_NAME = "";
			string RW_AZIMUTH = "";
			string RW_DELH = "";
			string RW_LAT = "";
			string RW_LENGTH = "";
			string RW_LON = "";
			string RW_MAG_VAR = "";

			model.Mission msn = (model.Mission)DataContext;
			foreach (Mission_ILOAD iload in msn.OV.ILOAD_List)
			{
				switch (iload.ID)
				{
					case "RUNWAY_ALT":
						RUNWAY_ALT = iload.Val;
						break;
					case "RUNWAY_NAME":
						RUNWAY_NAME = iload.Val;
						break;
					case "RW_AZIMUTH":
						RW_AZIMUTH = iload.Val;
						break;
					case "RW_DELH":
						RW_DELH = iload.Val;
						break;
					case "RW_LAT":
						RW_LAT = iload.Val;
						break;
					case "RW_LENGTH":
						RW_LENGTH = iload.Val;
						break;
					case "RW_LON":
						RW_LON = iload.Val;
						break;
					case "RW_MAG_VAR":
						RW_MAG_VAR = iload.Val;
						break;
				}
			}

			char[] spc = {' '};
			string[] runway_alt = RUNWAY_ALT.Split( spc, StringSplitOptions.RemoveEmptyEntries );
			if (runway_alt.Length != 90)
			{
				// TODO kaput
			}
			string[] runway_name = RUNWAY_NAME.Split( spc, StringSplitOptions.RemoveEmptyEntries );
			if (runway_name.Length != 90)
			{
				// TODO kaput
			}
			string[] rw_azimuth = RW_AZIMUTH.Split( spc, StringSplitOptions.RemoveEmptyEntries );
			if (rw_azimuth.Length != 90)
			{
				// TODO kaput
			}
			string[] rw_delh = RW_DELH.Split( spc, StringSplitOptions.RemoveEmptyEntries );
			if (rw_delh.Length != 90)
			{
				// TODO kaput
			}
			string[] rw_lat = RW_LAT.Split( spc, StringSplitOptions.RemoveEmptyEntries );
			if (rw_lat.Length != 90)
			{
				// TODO kaput
			}
			string[] rw_length = RW_LENGTH.Split( spc, StringSplitOptions.RemoveEmptyEntries );
			if (rw_length.Length != 90)
			{
				// TODO kaput
			}
			string[] rw_lon = RW_LON.Split( spc, StringSplitOptions.RemoveEmptyEntries );
			if (rw_lon.Length != 90)
			{
				// TODO kaput
			}
			string[] rw_mag_var = RW_MAG_VAR.Split( spc, StringSplitOptions.RemoveEmptyEntries );
			if (rw_mag_var.Length != 90)
			{
				// TODO kaput
			}

			// replace entry
			runway_alt[idx] = lsDB[cmbLandingSiteDB.SelectedIndex].RUNWAY_ALT;
			runway_name[idx] = lsDB[cmbLandingSiteDB.SelectedIndex].RUNWAY_NAME;
			rw_azimuth[idx] = lsDB[cmbLandingSiteDB.SelectedIndex].RW_AZIMUTH;
			rw_delh[idx] = lsDB[cmbLandingSiteDB.SelectedIndex].RW_DELH;
			rw_lat[idx] = lsDB[cmbLandingSiteDB.SelectedIndex].RW_LAT;
			rw_length[idx] = lsDB[cmbLandingSiteDB.SelectedIndex].RW_LENGTH;
			rw_lon[idx] = lsDB[cmbLandingSiteDB.SelectedIndex].RW_LON;
			rw_mag_var[idx] = lsDB[cmbLandingSiteDB.SelectedIndex].RW_MAG_VAR;

			// save current list
			RUNWAY_ALT = "";
			RUNWAY_NAME = "";
			RW_AZIMUTH = "";
			RW_DELH = "";
			RW_LAT = "";
			RW_LENGTH = "";
			RW_LON = "";
			RW_MAG_VAR = "";
			for (int i = 0; i < 90; i++)
			{
				RUNWAY_ALT += runway_alt[i] + " ";
				RUNWAY_NAME += runway_name[i] + " ";
				RW_AZIMUTH += rw_azimuth[i] + " ";
				RW_DELH += rw_delh[i] + " ";
				RW_LAT += rw_lat[i] + " ";
				RW_LENGTH += rw_length[i] + " ";
				RW_LON += rw_lon[i] + " ";
				RW_MAG_VAR += rw_mag_var[i] + " ";
			}

			// save landing site table I-Loads
			ObservableCollection<Mission_ILOAD> newiloads = msn.OV.ILOAD_List;
			foreach (Mission_ILOAD iload in newiloads)
			{
				switch (iload.ID)
				{
					case "RUNWAY_ALT":
						iload.Val = RUNWAY_ALT.TrimEnd( ' ' );
						break;
					case "RUNWAY_NAME":
						iload.Val = RUNWAY_NAME.TrimEnd( ' ' );
						break;
					case "RW_AZIMUTH":
						iload.Val = RW_AZIMUTH.TrimEnd( ' ' );
						break;
					case "RW_DELH":
						iload.Val = RW_DELH.TrimEnd( ' ' );
						break;
					case "RW_LAT":
						iload.Val = RW_LAT.TrimEnd( ' ' );
						break;
					case "RW_LENGTH":
						iload.Val = RW_LENGTH.TrimEnd( ' ' );
						break;
					case "RW_LON":
						iload.Val = RW_LON.TrimEnd( ' ' );
						break;
					case "RW_MAG_VAR":
						iload.Val = RW_MAG_VAR.TrimEnd( ' ' );
						break;
				}
			}
			// HACK another duct-tape solution...
			msn.OV.ILOAD_List = newiloads;
			return;
		}

		private void BtnLoadRunwayPreset_Click(object sender, RoutedEventArgs e)
		{
			if (cmbLSListPreset.SelectedIndex < 0) return;

			// get new table
			List<Tuple<string,string>> lst;
			switch (cmbLSListPreset.SelectedIndex)
			{
				default:
				case 0:
					lst = LowIncEarly();
					break;
				case 1:
					lst = LowIncLate();
					break;
				case 2:
					lst = MidIncEarly();
					break;
				case 3:
					lst = MidIncLate();
					break;
				case 4:
					lst = HighIncEarly();
					break;
				case 5:
					lst = HighIncLate();
					break;
				case 6:
					lst = WTR();
					break;
			}

			// get table info from DB
			string[] runway_alt = new string[90];
			string[] runway_name = new string[90];
			string[] rw_azimuth = new string[90];
			string[] rw_delh = new string[90];
			string[] rw_lat = new string[90];
			string[] rw_length = new string[90];
			string[] rw_lon = new string[90];
			string[] rw_mag_var = new string[90];
			List<model.Mission_OV.LandingSiteData> lsDB = ((model.Mission)DataContext).OV.LandingSiteDB;
			int idx = 0;
			for (int i = 0; i < 45; i++)
			{
				int DBidx = lsDB.FindIndex( 0, tmp => tmp.id == lst[i].Item1 );
				if (DBidx < 0)
				{
					// TODO kaput
				}
				else
				{
					runway_alt[idx] = lsDB[DBidx].RUNWAY_ALT;
					runway_name[idx] = lsDB[DBidx].RUNWAY_NAME;
					rw_azimuth[idx] = lsDB[DBidx].RW_AZIMUTH;
					rw_delh[idx] = lsDB[DBidx].RW_DELH;
					rw_lat[idx] = lsDB[DBidx].RW_LAT;
					rw_length[idx] = lsDB[DBidx].RW_LENGTH;
					rw_lon[idx] = lsDB[DBidx].RW_LON;
					rw_mag_var[idx] = lsDB[DBidx].RW_MAG_VAR;
					idx++;
				}

				DBidx = lsDB.FindIndex( 0, tmp => tmp.id == lst[i].Item2 );
				if (DBidx < 0)
				{
					// TODO kaput
				}
				else
				{
					runway_alt[idx] = lsDB[DBidx].RUNWAY_ALT;
					runway_name[idx] = lsDB[DBidx].RUNWAY_NAME;
					rw_azimuth[idx] = lsDB[DBidx].RW_AZIMUTH;
					rw_delh[idx] = lsDB[DBidx].RW_DELH;
					rw_lat[idx] = lsDB[DBidx].RW_LAT;
					rw_length[idx] = lsDB[DBidx].RW_LENGTH;
					rw_lon[idx] = lsDB[DBidx].RW_LON;
					rw_mag_var[idx] = lsDB[DBidx].RW_MAG_VAR;
					idx++;
				}
			}


			// save current list
			string RUNWAY_ALT = "";
			string RUNWAY_NAME = "";
			string RW_AZIMUTH = "";
			string RW_DELH = "";
			string RW_LAT = "";
			string RW_LENGTH = "";
			string RW_LON = "";
			string RW_MAG_VAR = "";
			for (int i = 0; i < 90; i++)
			{
				RUNWAY_ALT += runway_alt[i] + " ";
				RUNWAY_NAME += runway_name[i] + " ";
				RW_AZIMUTH += rw_azimuth[i] + " ";
				RW_DELH += rw_delh[i] + " ";
				RW_LAT += rw_lat[i] + " ";
				RW_LENGTH += rw_length[i] + " ";
				RW_LON += rw_lon[i] + " ";
				RW_MAG_VAR += rw_mag_var[i] + " ";
			}

			// save landing site table I-Loads
			model.Mission msn = (model.Mission)DataContext;
			ObservableCollection<Mission_ILOAD> newiloads = msn.OV.ILOAD_List;
			foreach (Mission_ILOAD iload in newiloads)
			{
				switch (iload.ID)
				{
					case "RUNWAY_ALT":
						iload.Val = RUNWAY_ALT.TrimEnd( ' ' );
						break;
					case "RUNWAY_NAME":
						iload.Val = RUNWAY_NAME.TrimEnd( ' ' );
						break;
					case "RW_AZIMUTH":
						iload.Val = RW_AZIMUTH.TrimEnd( ' ' );
						break;
					case "RW_DELH":
						iload.Val = RW_DELH.TrimEnd( ' ' );
						break;
					case "RW_LAT":
						iload.Val = RW_LAT.TrimEnd( ' ' );
						break;
					case "RW_LENGTH":
						iload.Val = RW_LENGTH.TrimEnd( ' ' );
						break;
					case "RW_LON":
						iload.Val = RW_LON.TrimEnd( ' ' );
						break;
					case "RW_MAG_VAR":
						iload.Val = RW_MAG_VAR.TrimEnd( ' ' );
						break;
				}
			}
			// HACK another duct-tape solution...
			msn.OV.ILOAD_List = newiloads;
			return;
		}
	}
}

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
			return ((Landing)parameter).FormatLandingSiteTable( (List<Tuple<string,string>>)value );
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
				list[i] = lsdb[i].rwname + " - " + lsdb[i].sitename;
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
				Path = new PropertyPath( "OV.LandingSiteTable" ),
				Converter = new Convert_LandingSiteTable_String(),
				ConverterParameter = this
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

		public string FormatLandingSiteTable( List<Tuple<string,string>> lstable )
		{
			string strls = "";
			if (lstable.Count == 0) return "";// TODO check null?

			// get landing site database to extract runway info for display
			model.Mission msn = (model.Mission)DataContext;
			List<model.Mission_OV.LandingSiteData> lsDB = msn.OV.LandingSiteDB;

			strls += LINE + HEADER;
			for (int lsid = 1; lsid <= 45; lsid++)
			{
				string prisite = "";
				string loc = "";
				string lgt = "";
				int idx;
				//// primary rwy ////
				if ((idx = msn.FindLandingSite( lsDB, lstable[lsid - 1].Item1 )) != -1)
				{
					loc = lsDB[idx].sitename;
					prisite = loc;
					lgt = lsDB[idx].lgt;
				}
				else
				{
					loc = "<ERROR>";
					lgt = "";
				}
				strls += LINE;
				// SITE: len 2
				strls += "| " + lsid.ToString().PadRight( 2 ) + " | ";
				// LOCATION: len 20
				strls += loc.PadRight( 20 ) + " | ";
				// RWY: len 6
				strls += lstable[lsid - 1].Item1.PadRight( 6 ) + " | ";
				// LG: len 5
				strls += lgt.PadLeft( 5 ) + " |\n";

				//// secondary rwy ////
				if ((idx = msn.FindLandingSite( lsDB, lstable[lsid - 1].Item2 )) != -1)
				{
					loc = lsDB[idx].sitename;
					lgt = lsDB[idx].lgt;
				}
				else
				{
					loc = "<ERROR>";
					lgt = "";
				}
				// SITE: len 2
				strls += "|    | ";
				// LOCATION: len 20
				if (loc == prisite) loc = "";
				strls += loc.PadRight( 20 ) + " | ";
				// RWY: len 6
				strls += lstable[lsid - 1].Item2.PadRight( 6 ) + " | ";
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
				"Runway: " + lsDB[idx].rwname + "\n";

			if (lsDB[idx].lgt != "0")
			{
				double lat = Math.Round( double.Parse( lsDB[idx].lat ) * Defs.DEG, 6 );
				double lon = Math.Round( double.Parse( lsDB[idx].lon ) * Defs.DEG, 6 );
				strls += "Lat: " + lat + "º   Lon: " + lon + "º\n" +
					"AMSL: " + lsDB[idx].amsl + "m\n" +
					"Heading: " + lsDB[idx].hdg + "º\n" +
					"Length: " + lsDB[idx].lgt + "ft";
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
			List<Tuple<string,string>> lstable = ((model.Mission)DataContext).OV.LandingSiteTable;
			string priRW;
			string secRW;

			if (rbPri.IsChecked == true)
			{
				priRW = lsDB[cmbLandingSiteDB.SelectedIndex].id;
				secRW = lstable[cmbLSID.SelectedIndex].Item2;
			}
			else
			{
				priRW = lstable[cmbLSID.SelectedIndex].Item1;
				secRW = lsDB[cmbLandingSiteDB.SelectedIndex].id;
			}

			Tuple<string,string> tp = new Tuple<string,string>( priRW, secRW );
			lstable[cmbLSID.SelectedIndex] = tp;
			((model.Mission)DataContext).OV.LandingSiteTable = lstable;
			return;
		}

		private void BtnLoadRunwayPreset_Click(object sender, RoutedEventArgs e)
		{
			if (cmbLSListPreset.SelectedIndex < 0) return;


			switch (cmbLSListPreset.SelectedIndex)
			{
				case 0:
					((model.Mission)DataContext).OV.LandingSiteTable = LowIncEarly();
					break;
				case 1:
					((model.Mission)DataContext).OV.LandingSiteTable = LowIncLate();
					break;
				case 2:
					((model.Mission)DataContext).OV.LandingSiteTable = MidIncEarly();
					break;
				case 3:
					((model.Mission)DataContext).OV.LandingSiteTable = MidIncLate();
					break;
				case 4:
					((model.Mission)DataContext).OV.LandingSiteTable = HighIncEarly();
					break;
				case 5:
					((model.Mission)DataContext).OV.LandingSiteTable = HighIncLate();
					break;
				case 6:
					((model.Mission)DataContext).OV.LandingSiteTable = WTR();
					break;
			}
			return;
		}
	}
}

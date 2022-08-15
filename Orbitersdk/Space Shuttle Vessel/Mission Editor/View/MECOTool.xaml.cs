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
2020/07/01   GLS
2020/07/08   GLS
2020/07/09   GLS
2021/12/25   GLS
2022/06/24   GLS
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
using System.Linq;
using System.Windows;
using System.Windows.Controls;


namespace SSVMissionEditor
{
	/// <summary>
	/// Interaction logic for MECOTool.xaml
	/// </summary>
	public partial class MECOTool : UserControl
	{
		const double MU_EARTH = 398600439968871.19;
		const double RADIUS_EARTH = 6371010.0;
		const double NM2KM = 1.852;
		const double FT2M = 0.3048;
		const double M2FT = 1.0 / FT2M;

		internal LaunchTargets target { get; private set; }

		public MECOTool()
		{
			InitializeComponent();
			target = new LaunchTargets();

			target.TargetInc = 28.45;
			target.TargetLAN = 0;
			target.TargetAlt = 250.0;
			target.InsertionMode = InsertionMode.Direct;
			target.MECOPe = 55.56;
			CB_MECO_Alt.SelectedIndex = 2;// 59NM

			target.OMS1TIG = "000:00:10:30";
			target.OMS1VX = 0.0;
			target.OMS1VY = 0.0;
			target.OMS1VZ = 0.0;
			target.OMS2TIG = "000:00:40:00";
			target.OMS2VX = 0.0;
			target.OMS2VY = 0.0;
			target.OMS2VZ = 0.0;
            
			DataContext = target;
		}

		private double TTA(double fRadius, double fApR, double fPeR)
		{
			double fSma = 0.5 * (fApR + fPeR);
			double fEcc = (fApR - fPeR) / (fApR + fPeR);
			double fPhiE = Math.Acos((1 - fRadius / fSma) / fEcc);
			double ft = Math.Sqrt(Math.Pow(fSma, 3) / MU_EARTH) * (Math.PI - (fPhiE - fEcc * Math.Sin(fPhiE)));
			return ft;
		}

		double OrbitPeriod(double fApR, double fPeR)
		{
			double fSma = 0.5 * (fApR + fPeR);

			return Math.Sqrt(Math.Pow(fSma, 3) / MU_EARTH) * 2.0 * Math.PI;
		}

		private double VisViva(double fRadius, double fApR, double fPeR)
		{
			return Math.Sqrt(MU_EARTH * ((2.0 / fRadius) - (2.0 / (fApR + fPeR))));
		}

		double FPA(double fRadius, double fApR, double fPeR)
		{
			double fh = 2 * fPeR - 2 * Math.Pow(fPeR, 2) / (fApR + fPeR);
			double fx = 2 * fRadius - 2 * Math.Pow(fRadius, 2) / (fApR + fPeR);
			return Math.Acos(Math.Sqrt(fh / fx));
		}

		double RadiusAtTime( double R, double ApR, double PeR, double t )
		{
			double e = ecc( ApR, PeR );
			double a = SMa( ApR, PeR );

			double n = Math.Sqrt( MU_EARTH / (a * a * a) );
			double v = Radius2TrueAnomaly( R, e, a );
			double E = TrueAnomaly2EccentricAnomaly( v, e );
			double Mo = EccentricAnomaly2MeanAnomaly( E, e );

			double M = (n * t) + Mo;
			v = M + (2 * e * Math.Sin( M )) + (1.25 * e * e * Math.Sin( 2 * M ));

			return TrueAnomaly2Radius( v, e, a );
		}

		double ecc( double ApR, double PeR )
		{
			return (ApR - PeR) / (ApR + PeR);
		}

		double SMa( double ApR, double PeR )
		{
			return (ApR + PeR) / 2.0;
		}

		double TrueAnomaly2Radius( double v, double e, double a )
		{
			return (a * (1 - (e * e))) / (1 + (e * Math.Cos( v )));
		}

		double Radius2TrueAnomaly( double R, double e, double a )
		{
			return Math.Acos( (((a * (1 - (e * e))) / R) - 1) / e );
		}

		double TrueAnomaly2EccentricAnomaly( double v, double e )
		{
			return Math.Acos( (e + Math.Cos( v )) / (1 + (e * Math.Cos( v ))) );
		}

		double EccentricAnomaly2MeanAnomaly( double E, double e )
		{
			return E - (e * Math.Sin( E ));
		}

		double GetVel( double R, double ApR, double FPA )
		{
			double k = ApR / R;
			double sing = Math.Sin( (Math.PI / 2) - FPA );

			return Math.Sqrt( ((k - (k * k)) * 2 * MU_EARTH) / (((sing * sing) - (k * k)) * R) );
		}

		double GetPeR( double r1, double v1, double FPA )
		{
			double C = (2 * MU_EARTH) / (r1 * v1 * v1);
			double sing = Math.Sin( (Math.PI / 2) - FPA );
			return ((-C + Math.Sqrt( (C * C) + (4 * (1 - C) * sing * sing) )) / (2 * (1 - C))) * r1;
		}

		private void btnCalculateClick(object sender, RoutedEventArgs e)
		{
			const double TMECO = 510.0;

			double fRadiusTargetOrbit = (target.TargetAlt * 1000.0) + RADIUS_EARTH;
			//Apogee target for MECO orbit
			double fApogeeMECOOrbit = ((85 * NM2KM) * 1000.0) + RADIUS_EARTH;
			double fPerigeeMECOOrbit = ((3 * NM2KM) * 1000.0) + RADIUS_EARTH;

			double fOMS1Apogee = fRadiusTargetOrbit;

			if (target.InsertionMode == InsertionMode.Direct)
			{
				fApogeeMECOOrbit = fRadiusTargetOrbit;
				fPerigeeMECOOrbit = (target.MECOPe * 1000.0) + RADIUS_EARTH;
				//Select an as high as possible periapsis for minimum fuel consumption
			}

			target.MECOAlt = 59 * NM2KM;// default index 2
			if (CB_MECO_Alt.SelectedIndex == 0) target.MECOAlt = 63 * NM2KM;
			else if (CB_MECO_Alt.SelectedIndex == 1) target.MECOAlt = 61 * NM2KM;
			else if (CB_MECO_Alt.SelectedIndex == 3) target.MECOAlt = 57 * NM2KM;
			else if (CB_MECO_Alt.SelectedIndex == 4) target.MECOAlt = 52 * NM2KM;

			double fMECORadius = 1000.0 * target.MECOAlt + RADIUS_EARTH;
			double fSmaMECO = 0.5 * (fApogeeMECOOrbit + fPerigeeMECOOrbit);

			target.MECOVel = VisViva(fMECORadius, fApogeeMECOOrbit, fPerigeeMECOOrbit);
			target.MECOFPA = FPA(fMECORadius, fApogeeMECOOrbit, fPerigeeMECOOrbit) * 180.0 / Math.PI;
			double fTIG_OMS1 = 0.0;
			double fTIG_OMS2 = 0.0;
			double fDV_OMS1 = 0.0;
			double fDV_OMS2 = 0.0;
			double fVTargetOrbit = Math.Sqrt(MU_EARTH / fRadiusTargetOrbit);

			if (target.InsertionMode == InsertionMode.Direct)
			{
				//Direct ascent
				fTIG_OMS1 = TMECO + 120.0;
				fTIG_OMS2 = TMECO + TTA( fMECORadius, fApogeeMECOOrbit, fPerigeeMECOOrbit );

				fDV_OMS2 = fVTargetOrbit - VisViva(fRadiusTargetOrbit, fApogeeMECOOrbit, fPerigeeMECOOrbit);
			}
			else
			{
				//Standard ascent
				fTIG_OMS1 = TMECO + 120;
				double MECO120Radius = RadiusAtTime( fMECORadius, fApogeeMECOOrbit, fPerigeeMECOOrbit, 120 );
				double MECO120FPA = FPA( MECO120Radius, fApogeeMECOOrbit, fPerigeeMECOOrbit );
				double MECO120v = VisViva( MECO120Radius, fApogeeMECOOrbit, fPerigeeMECOOrbit );
				double postOMS1v = GetVel( MECO120Radius, fOMS1Apogee, MECO120FPA );
				fDV_OMS1 = postOMS1v - MECO120v;

				target.OMS1VX = (fDV_OMS1 * Math.Cos( MECO120FPA )) * M2FT;
				target.OMS1VZ = (fDV_OMS1 * Math.Sin( MECO120FPA )) * M2FT;

				double postOMS1PeR = GetPeR( MECO120Radius, postOMS1v, MECO120FPA );
				fTIG_OMS2 = fTIG_OMS1 + TTA( MECO120Radius, fOMS1Apogee, postOMS1PeR );
				fDV_OMS2 = fVTargetOrbit - VisViva( fOMS1Apogee, fOMS1Apogee, postOMS1PeR );
			}

			fTIG_OMS2 -= fDV_OMS2 / (3 * FT2M);

			target.OMS2VX = fDV_OMS2 * M2FT;

			int iTIG = (int)(fTIG_OMS1);
			int iDay = iTIG / 86400;
			iTIG -= iDay * 86400;
			int iHour = iTIG / 3600;
			iTIG -= 3600 * iHour;
			int iMin = iTIG / 60;
			int iSec = iTIG - 60 * iMin;

			target.OMS1TIG = string.Format("{0:d3}:{1:d2}:{2:d2}:{3:d2}", iDay, iHour, iMin, iSec);

			iTIG = (int)(fTIG_OMS2);
			iDay = iTIG / 86400;
			iTIG -= iDay * 86400;
			iHour = iTIG / 3600;
			iTIG -= 3600 * iHour;
			iMin = iTIG / 60;
			iSec = iTIG - 60 * iMin;

			target.OMS2TIG = string.Format("{0:d3}:{1:d2}:{2:d2}:{3:d2}", iDay, iHour, iMin, iSec);


			target.FileOutput = string.Format("TargetInc={0:f6}\r\nMECOAlt={1:f6}\r\nMECOVel={2:f6}\r\nMECOFPA={3:f6}",
				target.TargetInc, target.MECOAlt * 1000.0,
				target.MECOVel, target.MECOFPA);
		}

		private void btnTransferClick(object sender, RoutedEventArgs e)
		{
			MainWindow mw = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
			mw.mission.SetMECOparams( target.TargetInc, target.MECOAlt * 1000.0, target.MECOVel, target.MECOFPA );
			return;
		}
	}
}

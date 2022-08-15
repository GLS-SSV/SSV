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
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace SSVMissionEditor
{
    public enum InsertionMode
    {
        Standard,
        Direct
    }

    class LaunchTargets : INotifyPropertyChanged
    {
		double targetInc;
        public double TargetInc
		{
			get { return targetInc; }
			set
			{
				targetInc = value;
				OnPropertyChanged("TargetInc");
			}
		}
		double targetLAN;
        public double TargetLAN
		{
			get { return targetLAN; }
			set
			{
				targetLAN = value;
				OnPropertyChanged("TargetLAN");
			}
		}
		double targetAlt;
        public double TargetAlt
		{
			get { return targetAlt; }
			set
			{
				targetAlt = value;
				OnPropertyChanged("TargetAlt");
			}
		}
		InsertionMode insertionMode;
        public InsertionMode InsertionMode
		{
			get { return insertionMode; }
			set
			{
				insertionMode = value;
				OnPropertyChanged("InsertionMode");
			}
		}

		string fileOutput;
        public string FileOutput
		{
			get { return fileOutput; }
			set
			{
				fileOutput = value;
				OnPropertyChanged("FileOutput");
			}
		}

		double mecoVel;
        public double MECOVel
		{
			get { return mecoVel; }
			set
			{
				mecoVel = value;
				OnPropertyChanged("MECOVel");
			}
		}
		double mecoFPA;
        public double MECOFPA
		{
			get { return mecoFPA; }
			set
			{
				mecoFPA = value;
				OnPropertyChanged("MECOFPA");
			}
		}
		double mecoAlt;
        public double MECOAlt
		{
			get { return mecoAlt; }
			set
			{
				mecoAlt = value;
				OnPropertyChanged("MECOAlt");
			}
		}

        double mecoPe;// for DI only
        public double MECOPe
        {
            get { return mecoPe; }
            set
            {
                mecoPe = value;
                OnPropertyChanged( "MECOPe");
            }
        }

        private string oms1tig;
        public string OMS1TIG
        {
            get { return oms1tig; }
            set
            {
                oms1tig = value;
                OnPropertyChanged("OMS1TIG");
            }
        }
        private double oms1vx, oms1vy, oms1vz;
        public double OMS1VX
        {
            get { return oms1vx; }
            set
            {
                oms1vx = value;
                OnPropertyChanged("OMS1VX");
            }
        }
        public double OMS1VY
        {
            get { return oms1vy; }
            set
            {
                oms1vy = value;
                OnPropertyChanged("OMS1VY");
            }
        }
        public double OMS1VZ
        {
            get { return oms1vz; }
            set
            {
                oms1vz = value;
                OnPropertyChanged("OMS1VZ");
            }
        }

        private string oms2tig;
        public string OMS2TIG
        {
            get { return oms2tig; }
            set
            {
                oms2tig = value;
                OnPropertyChanged("OMS2TIG");
            }
        }
        private double oms2vx, oms2vy, oms2vz;
        public double OMS2VX
        {
            get { return oms2vx; }
            set
            {
                oms2vx = value;
                OnPropertyChanged("OMS2VX");
            }
        }
        public double OMS2VY
        {
            get { return oms2vy; }
            set
            {
                oms2vy = value;
                OnPropertyChanged("OMS2VY");
            }
        }
        public double OMS2VZ
        {
            get { return oms2vz; }
            set
            {
                oms2vz = value;
                OnPropertyChanged("OMS2VZ");
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string prop)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(prop));
            }
        }
    }
}

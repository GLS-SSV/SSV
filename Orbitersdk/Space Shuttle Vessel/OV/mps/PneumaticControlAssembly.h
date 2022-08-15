/****************************************************************************
  This file is part of Space Shuttle Vessel

  Pneumatic Control Assembly definition


  Space Shuttle Vessel is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License as published by
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
2020/04/01   GLS
2020/06/20   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/08/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Pneumatic Control Assembly definition



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
#ifndef _mps_PCA_H_
#define _mps_PCA_H_


#include <discsignals.h>


class SolenoidValve;
class PressureActuatedValve;


namespace mps
{
	class HeSysEng;

	using namespace discsignals;


	class PneumaticControlAssembly
	{
		friend class OutputElectronics_BLOCK_II;
		friend class SSME;

		private:
			// P2.1 (P4 press???)
			// P2.2 (P3 press???)
			// P2.3 (P12 press???)
			// P2.4 (N2.3 press???)
			// P2.5 (N2.4 press???)
			// P1 Eng He
			// P3 (downstream MFV)
			// P4 HPOTP I/S
			// P5 FBV
			// P9 OBV
			// P12 OPOVA (maybe more after???)
			// P34 HPV
			// P35 POGO HPV Solenoid vent port
			// N1 GSE GN2 (600 +/-50)
			// N2.2 HPV
			// N2.3 OPOV/OPB/FPB
			// N2.4 FPOV

			// 5 solenoids //
			// E) hpotp i/s purge
			// C) emergency shutdown
			// A) fuel system purge
			// B) bleed valves control
			// D) shutdown purge
			SolenoidValve* FuelSystemPurge_SV;
			SolenoidValve* BleedValvesControl_SV;
			SolenoidValve* EmergencyShutdown_SV;
			SolenoidValve* ShutdownPurge_SV;
			SolenoidValve* HPOTPISPurge_SV;

			// 8 PAVs //
			// purge sequence valve
			// oxidizer system purge
			// D) fuel preburner purge
			// B) oxidizer bleed valve
			// A) fuel system purge
			// C) emergency shutdown
			// E) hpotp i/s purge
			// D) oxidizer preburner purge
			PressureActuatedValve* FuelSystemPurge_PAV;
			PressureActuatedValve* OxidizerBleedValve_PAV;
			PressureActuatedValve* EmergencyShutdown_PAV;
			PressureActuatedValve* FuelPreburnerPurge_PAV;
			PressureActuatedValve* OxidizerPreburnerPurge_PAV;
			PressureActuatedValve* HPOTPISPurge_PAV;
			PressureActuatedValve* OxidizerSystemPurge_PAV;
			PressureActuatedValve* PurgeSequenceValve_PAV;

			double pressFuelSystemPurge;
			//double pressEmergencyShutdown;
			double pressFuelPreburnerPurge;
			double pressOxidizerPreburnerPurge;
			double pressHPOTPISPurge;

			SSME* eng;
			HeSysEng* HeSys;

		public:
			PneumaticControlAssembly( SSME* eng, HeSysEng* HeSys );
			~PneumaticControlAssembly( void );

			void tmestp( double simdt );
			void Realize( discsignals::DiscreteBundle* bundle );

			double UseHPOTPISPurge( double flow );
			double UseFuelSystemPurge( double flow );

			double GetPressFuelSystemPurge() const;
			double GetPressEmergencyShutdown() const;
			double GetPressFuelPreburnerPurge() const;
			double GetPressOxidizerPreburnerPurge() const;
			double GetPressHPOTPISPurge() const;
	};
}

#endif// _mps_PCA_H_
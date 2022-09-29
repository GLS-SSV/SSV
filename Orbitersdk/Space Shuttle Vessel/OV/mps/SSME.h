/****************************************************************************
  This file is part of Space Shuttle Vessel

  Space Shuttle Main Engine subsystem definition


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
2020/05/10   GLS
2020/05/29   GLS
2020/06/20   GLS
2021/06/06   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/03/29   GLS
2022/04/02   GLS
2022/04/26   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Space Shuttle Main Engine definition



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
#ifndef _mps_SSME_H_
#define _mps_SSME_H_


#include "../AtlantisSubsystem.h"


class HydraulicActuatedValve;
class SolenoidValve;
class PressureActuatedValve;

namespace discsignals
{
	class DiscreteBundle;
}


namespace mps
{
	// HACK very little ideia about the real numbers
	inline constexpr double MAX_RATE_CCV = 120;
	inline constexpr double MAX_RATE_MOV = 120;
	inline constexpr double MAX_RATE_MFV = 150;
	inline constexpr double MAX_RATE_FPOV = 170;
	inline constexpr double MAX_RATE_OPOV = 210;
	inline constexpr double RATE_AFV = 100;
	inline constexpr double RATE_HPV_SV = 1000;
	inline constexpr double RATE_OBV = 100;
	inline constexpr double RATE_FBV = 100;
	inline constexpr double RATE_HPV = 100;
	inline constexpr double RATE_GCV = 100;
	inline constexpr double RATE_RIV = 100;


	class HeSysEng;
	class MPS;

	using namespace discsignals;

	class SSME:public AtlantisSubsystem
	{
		friend class EIU;
		friend class SSMEController;
		friend class OutputElectronics;
		friend class OutputElectronics_BLOCK_II;
		friend class InputElectronics_BLOCK_II;
		friend class PneumaticControlAssembly;

		protected:
			unsigned short ID;// engine ID (1 - C, 2 - L, 3 - R)

			HydraulicActuatedValve* ptrCCV;
			HydraulicActuatedValve* ptrMFV;
			HydraulicActuatedValve* ptrMOV;
			HydraulicActuatedValve* ptrFPOV;
			HydraulicActuatedValve* ptrOPOV;
			SolenoidValve* ptrAFV;
			SolenoidValve* ptrHPV_SV;
			PressureActuatedValve* ptrFBV;
			PressureActuatedValve* ptrOBV;
			PressureActuatedValve* ptrHPV;
			PressureActuatedValve* ptrGCV;
			PressureActuatedValve* ptrRIV;

			SSMEController* Controller;

			PneumaticControlAssembly* PCA;

			MPS* pMPS;

			bool Igniter_MCC[2];
			bool Igniter_FPB[2];
			bool Igniter_OPB[2];

			double ISP0;
			double ISP1;
			double FPL_THRUST;
			double RPL_PC_PRESS;
			int FPL;// % RPL

			/**
			 * Converts engine level from percentage to chamber pressure (psi)
			 * @param pcPCT engine level (percentage)
			 * @return engine level (chamber pressure)
			 */
			double PCfromPCTtoPSI( double pcPCT ) const;

			/**
			 * Converts engine level from chamber pressure (psi) to percentage
			 * @param pcPSI engine level (chamber pressure)
			 * @return engine level (percentage)
			 */
			double PCfromPSItoPCT( double pcPSI ) const;

			// engine model
			// gets inputs from valve positions and internal values and outputs sensor readings and thrust
			void SSMERUN( double time, double dt );
			virtual void RUN1( double time, double dt ) = 0;// pre-start
			virtual void RUN2( double time, double dt ) = 0;// ignition
			virtual void RUN3( double time, double dt ) = 0;// mainstage
			virtual void RUN4( double time, double dt ) = 0;// cutoff
			virtual void RUN5( double time, double dt ) = 0;// post-shutdown

			short modelmode;
			double modeltime;

			// data cookup fncts
			double dcPC_ESC( double );
			double dcPC_CO( double );

			double AdjCOTime( double pc );

			virtual void ConnectSensors( DiscreteBundle* IEchA_Press, DiscreteBundle* IEchB_Press, DiscreteBundle* IEchA_Temp, DiscreteBundle* IEchB_Temp, DiscreteBundle* IEchA_Flow, DiscreteBundle* IEchB_Flow, DiscreteBundle* IEchA_Speed, DiscreteBundle* IEchB_Speed ) = 0;

		public:
			/**
			 * Create a new SSME object.
			 * @param _director reference to the subsystem director
			 * @param _ident identification of the subsystem inside the model
			 * @param nID identification number of the SSME
			 * @param controllertype identification of the SSME controller version
			 * @param sw identification of the software version of the SSME controller
			 * @param HeSys Helium System supplying the engine
			 */
			SSME( AtlantisSubsystemDirector* _director, const string& _ident, unsigned short nID, const string& _mesh, int controllertype, const string& sw, HeSysEng* HeSys );
			virtual ~SSME( void );

			/**
			 * Create the thruster reference of the SSME
			 * and link the cable connections of the SSME.
			 * @sa AtlantisSubsystem::Realize
			 */
			void Realize( void ) override;

			void OnPostStep( double simt, double simdt, double mjd ) override;

			bool SingleParamParseLine() const override {return true;};

			void OnSaveState( FILEHANDLE scn ) const override;
			bool OnParseLine( const char* line ) override;
	};
}


#endif// _mps_SSME_H_

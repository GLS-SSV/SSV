/****************************************************************************
  This file is part of Space Shuttle Vessel

  MPS TVC subsystem definition


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
#ifndef _MPS_TVC_H_
#define _MPS_TVC_H_


#include "AtlantisSubsystem.h"


class APU;


class MPS_TVC:public AtlantisSubsystem
{
	private:
		double Pcurpos[3];
		double Ycurpos[3];
		double Ptgtpos[3];
		double Ytgtpos[3];

		APU* pAPU[3];

		void UpdateActuator( double hydpri, double hydsec, double& cur, double tgt, double dt, double lim );

	public:
		explicit MPS_TVC( AtlantisSubsystemDirector* _director );
		~MPS_TVC( void );

		void Realize( void ) override;
		bool OnParseLine( const char* keyword, const char* value ) override;
		void OnSaveState( FILEHANDLE scn ) const override;

		void OnPostStep( double simt, double simdt, double mjd ) override;

		void Command( unsigned int eng, double pitch, double yaw );
};


#endif// _MPS_TVC_H_

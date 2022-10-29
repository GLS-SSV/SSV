/****************************************************************************
  This file is part of Space Shuttle Vessel

  Engine Interface Unit subsystem definition


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
2020/05/10   GLS
2020/06/20   GLS
2021/06/06   GLS
2021/07/03   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Engine Interface Unit definition



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
#ifndef _mps_EIU_H_
#define _mps_EIU_H_


#include "../AtlantisSubsystem.h"
#include "../dps/SimpleBTU.h"
#include "../dps/dps_defs.h"
#include <DiscInPort.h>


using namespace dps;
using namespace discsignals;


namespace mps
{
	class SSME;

	class EIU:public AtlantisSubsystem, public dps::SimpleBTU
	{
		private:
			int ID;
			SSME* eng;
			DiscInPort power1;
			DiscInPort power2;

			unsigned short StatusRegisterA[32];// holds primary data from CIA 1
			unsigned short StatusRegisterB[32];// holds secondary data from CIA 2

			FILE* fp;

			bool DataRecorderOn;

			void DataRecorder( unsigned short* data, char* type );

			bool Power( void ) const;

		public:
			EIU( AtlantisSubsystemDirector* _director, const string& _ident, int ID, SSME* eng );
			~EIU( void );

			void busCommand( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw ) override;
			void busRead( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw ) override;

			/**
			 * Used to connect DiscInPort
			 * @sa AtlantisSubsystem::Realize
			 */
			void Realize( void );

			bool OnParseLine( const char* line ) override;
			void OnSaveState( FILEHANDLE scn ) const override;
			bool SingleParamParseLine() const override {return true;};

			void OnPostStep( double, double, double ) override;

			void CIA( int num, unsigned short* data );

			// HACK
			void command( unsigned short cmd );
	};
}


#endif// _mps_EIU_H_

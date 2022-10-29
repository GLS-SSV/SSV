/****************************************************************************
  This file is part of Space Shuttle Vessel

  Standard light VC definition


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
2021/01/20   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Standard light VC component



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
#ifndef _VC_STANDARDSWITCH_H_
#define _VC_STANDARDSWITCH_H_


#include "BasicLight.h"
#include <DiscInPort.h>


namespace vc {

	using discsignals::DiscInPort;

	class StandardSingleLight : public BasicLight
	{
		protected:
			UINT panelmesh;
			UINT grpIndex;

			float offsetU[2];
			float offsetV[2];

		public:
			StandardSingleLight( Atlantis* _sts, const string& _ident );
			~StandardSingleLight();

			void SetDefaultState( unsigned int _state ) override;
			void SetStateOffset( unsigned int _state, float _U, float _V ) override;
			bool ConnectLight( unsigned short usPort, DiscreteBundle* pBundle, unsigned short usLine ) override;

			void OnPostStep( double simt, double simdt, double mjd ) override;

			void UpdateUV( void );
			void DefineMeshGroup( UINT _panelmesh, UINT _grpIndex );
			void VisualCreated( void ) override;

			DiscInPort input[2];
	};

	class StandardDoubleLight : public BasicLight
	{
		protected:
			UINT panelmesh;
			UINT grpIndex;

			float offsetU[4];
			float offsetV[4];

		public:
			StandardDoubleLight( Atlantis* _sts, const string& _ident );
			~StandardDoubleLight();

			void SetDefaultState( unsigned int _state ) override;
			void SetStateOffset( unsigned int _state, float _U, float _V ) override;
			bool ConnectLight( unsigned short usPort, DiscreteBundle* pBundle, unsigned short usLine ) override;

			void OnPostStep( double simt, double simdt, double mjd ) override;

			void UpdateUV( void );
			void DefineMeshGroup( UINT _panelmesh, UINT _grpIndex );
			void VisualCreated( void ) override;

			DiscInPort input[4];
	};
}

#endif// _VC_STANDARDSWITCH_H_

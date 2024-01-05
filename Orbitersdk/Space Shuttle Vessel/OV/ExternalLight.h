/****************************************************************************
  This file is part of Space Shuttle Vessel

  External Light definition


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
#ifndef _VC_EXTERNALLIGHT_H_
#define _VC_EXTERNALLIGHT_H_


#include <Orbitersdk.h>
#include <DiscInPort.h>


class Atlantis;


enum EXTERNAL_LIGHT_TYPE {HG_VAPOR, INCANDESCENT, LED};


class ExternalLight
{
	protected:
		Atlantis* sts;

		VECTOR3 position;
		EXTERNAL_LIGHT_TYPE type;
		unsigned short state;// 0 = off, 1 = level 1, 2 = level 2
		unsigned short next_state;// 0 = off, 1 = level 1, 2 = level 2
		UINT mesh;
		UINT grpIndex;

		float offsetU[3];
		float offsetV[3];

		LightEmitter* Light;
		float curlevel;// current light level
		float statelevel[2];// light level for states 1 and 2

		discsignals::DiscInPort input[2];// inputs for states 1 and 2 (tested in that order)

		void UpdateUV( void );

	public:
		ExternalLight( Atlantis* sts, const VECTOR3& pos, const VECTOR3& dir, const float defaultoffsetU, const float defaultoffsetV, const double range, const double att0, const double att1, const double att2, const double umbra, const double penumbra, const EXTERNAL_LIGHT_TYPE type );
		virtual ~ExternalLight();

		void DefineState( const unsigned int state, const float stateoffsetU, const float stateoffsetV, const float level, discsignals::DiscreteBundle* pBundle, const unsigned short usLine );

		void TimeStep( const double dt );

		void DefineMeshGroup( UINT _mesh, UINT _grpIndex );
		void VisualCreated( void );

		void ShiftLightPosition( const VECTOR3& shift );
		void UpdateLightPosition( const VECTOR3& pos );
		void UpdateLightDirection( const VECTOR3& dir );
};

#endif// _VC_EXTERNALLIGHT_H_

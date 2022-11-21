/****************************************************************************
  This file is part of Space Shuttle Vessel

  CCTV monitor definition


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
#ifndef __CTVM_H_
#define __CTVM_H_


#include "AtlantisVCComponent.h"
#include <gcConst.h>


namespace vc
{
	class CTVM:public AtlantisVCComponent
	{
		private:
			unsigned short id;
			unsigned short menuoptions[3];
			unsigned short menuselect;
			bool power;
			bool menu;
			bool selectpressed;
			bool functionleft;
			bool functionright;
			double menutime;

			SURFHANDLE hSurf;

			MGROUP_ROTATE* pPower;
			MGROUP_ROTATE* pFunction;
			MGROUP_TRANSLATE* pSelect;

			UINT anim_power;
			UINT anim_function;
			UINT anim_select;

			VECTOR3 refPower;
			VECTOR3 refFunction;
			VECTOR3 dirPower;
			VECTOR3 dirFunction;
			VECTOR3 dirSelect;

			UINT grpPower;
			UINT grpFunction;
			UINT grpSelect;

			void OnPowerOn( void );
			void OnPowerOff( void );
			void OnPowerChange( void );
			void OnSelectPress( void );
			void OnSelectDepress( void );
			void OnFunctionLeft( void );
			void OnFunctionCenter( void );
			void OnFunctionRight( void );


		public:
			CTVM( unsigned short id, Atlantis* _sts, const string& _ident );
			virtual ~CTVM( void );

			void SetReferences( const VECTOR3& refPower, const VECTOR3& refFunction );
			void SetDirections( const VECTOR3& dirPower, const VECTOR3& dirFunction, const VECTOR3& dirSelect );
			void SetGroups( UINT grpPower, UINT grpFunction, UINT grpSelect );

			virtual void DefineVCAnimations( UINT vc_idx ) override;
			virtual bool OnMouseEvent( int _event, float x, float y ) override;
			virtual bool OnReadState( FILEHANDLE scn ) override;
			virtual void OnSaveState( FILEHANDLE scn ) const override;
			virtual bool IsMultiLineSaveState( void ) const override { return true; };
			void OnPreStep( double simt, double simdt, double mjd ) override;

			SURFHANDLE GetMonitorSurf( void ) const;
	};
};


#endif// __CTVM_H_

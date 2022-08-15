/****************************************************************************
  This file is part of Space Shuttle Vessel

  CrawlerPanelLight definition


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
2020/05/08   GLS
2020/05/10   GLS
2020/06/14   GLS
2020/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/12/25   GLS
2022/08/05   GLS
********************************************/

#ifndef CRAWLERPANELLIGHT_H_7ADEE92B_D3B6_46ab_8DD2_DEB8C804DE96
#define CRAWLERPANELLIGHT_H_7ADEE92B_D3B6_46ab_8DD2_DEB8C804DE96
#pragma once

#include <BasicVCComponent.h>
#include "Crawler_vc_defs.h"
#include <discsignals.h>


namespace vc
{
	using discsignals::DiscInPort;
	using discsignals::DiscreteBundle;

	class CrawlerPanelLight : public BasicVCComponent<Crawler>
	{
		protected:
			int state;
			int next_state;
			int default_state;

			UINT panelmesh;
			UINT grpIndex;

			float offsetU[2];
			float offsetV[2];

		public:
			CrawlerPanelLight( Crawler* _v, const string& _ident );
			~CrawlerPanelLight();

			virtual void SetDefaultState( unsigned int _state );
			virtual void SetStateOffset( unsigned int _state, float _U, float _V );
			virtual bool ConnectLight( unsigned short usPort, DiscreteBundle* pBundle, unsigned short usLine );

			void OnPostStep( double simt, double simdt, double mjd ) override;

			void UpdateUV( void );
			void DefineMeshGroup( UINT _panelmesh, UINT _grpIndex );
			void VisualCreated( void ) override;

			DiscInPort input[2];
	};

	class CrawlerPanelLight2 : public BasicVCComponent<Crawler>
	{
		protected:
			int state;
			int next_state;
			int default_state;

			UINT panelmesh;
			UINT grpIndex;

			float offsetU[4];
			float offsetV[4];

		public:
			CrawlerPanelLight2( Crawler* _v, const string& _ident );
			~CrawlerPanelLight2();

			virtual void SetDefaultState( unsigned int _state );
			virtual void SetStateOffset( unsigned int _state, float _U, float _V );
			virtual bool ConnectLight( unsigned short usPort, DiscreteBundle* pBundle, unsigned short usLine );

			void OnPostStep( double simt, double simdt, double mjd ) override;

			void UpdateUV( void );
			void DefineMeshGroup( UINT _panelmesh, UINT _grpIndex );
			void VisualCreated( void ) override;

			DiscInPort input[4];
	};
};

#endif

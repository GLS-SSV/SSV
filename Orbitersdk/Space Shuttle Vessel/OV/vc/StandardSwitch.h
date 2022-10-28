/****************************************************************************
  This file is part of Space Shuttle Vessel

  Standard Switch VC Component


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
2020/03/20   GLS
2020/04/01   GLS
2020/04/07   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/08/24   GLS
2021/12/26   GLS
2022/05/29   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Standard Switch VC Component



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
#ifndef _STANDARDSWITCH_H_
#define _STANDARDSWITCH_H_


#include "BasicSwitch.h"
#include <DiscreteBundle.h>
#include <DiscOutPort.h>


namespace vc
{
	using ::discsignals::DiscreteBundle;
	using ::discsignals::DiscOutPort;

	class LockableLever: public BasicSwitch
	{
		private:
			MGROUP_ROTATE* pswitchrot;
			MGROUP_TRANSLATE* pswitchpull;
			UINT anim_switch;
			UINT anim_pull;
			VECTOR3 dummy_vec; // needed to create animation

			VECTOR3 pullDir;
			bool bHasPullDir;

			bool bIsPulled;
			double fInitialMousePos;
		public:
			LockableLever(Atlantis* _sts, unsigned short usNumPositions, const string& _ident);
			virtual ~LockableLever();

			/**
			 * @param _pullDir Normalized vector in direction along which lever can be pulled
			 */
			void SetPullDirection( const VECTOR3& _pullDir );

			void Realize() override;
			void DefineVCAnimations(UINT vc_idx) override;
			bool OnMouseEvent(int _event, float x, float y) override;
			virtual void ConnectPort( unsigned short usPort, DiscreteBundle* pBundle, unsigned short usLine ) = 0;
			void OnPositionChange(unsigned short usNewPosition) override;
			virtual void OnPull();
			virtual void OnRelease();
	};

	class LockableLever2 : public LockableLever
	{
		private:
			DiscOutPort output[2];
		public:
			LockableLever2(Atlantis* _sts, const string& _ident);
			virtual ~LockableLever2();

			void OnPositionChange(unsigned short usNewPosition) override;
			void ConnectPort( unsigned short usPort, DiscreteBundle* pBundle, unsigned short usLine ) override;
	};

	class LockableLever3 : public LockableLever
	{
		private:
			DiscOutPort output[3];
		public:
			LockableLever3(Atlantis* _sts, const string& _ident);
			virtual ~LockableLever3();

			void OnPositionChange(unsigned short usNewPosition) override;
			void ConnectPort(unsigned short usPort, DiscreteBundle* pBundle, unsigned short usLine) override;
	};

	class StandardSwitch : public BasicSwitch
	{
		private:
			MGROUP_ROTATE* pswitchrot;

			UINT anim_switch;
		public:
			StandardSwitch(Atlantis* _sts, unsigned short usNumPositions, const string& _ident);
			virtual ~StandardSwitch();

			void DefineVCAnimations(UINT vc_idx) override;
			void OnPositionChange(unsigned short usNewPosition) override;
			void Realize() override;
			virtual void ConnectPort( unsigned short usPort, DiscreteBundle* pBundle, unsigned short usLine ) = 0;
	};

	class StdSwitch2: public StandardSwitch
	{
		private:
			DiscOutPort output[2];
		public:
			StdSwitch2(Atlantis* _sts, const string& _ident);
			virtual ~StdSwitch2();

			void OnPositionChange(unsigned short usNewPosition) override;
			void ConnectPort( unsigned short usPort, DiscreteBundle* pBundle, unsigned short usLine ) override;
	};

	class StdSwitch3: public StandardSwitch
	{
		private:
			DiscOutPort output[3];
		public:
			StdSwitch3(Atlantis* _sts, const string& _ident);
			virtual ~StdSwitch3();

			void OnPositionChange(unsigned short usNewPosition) override;
			void ConnectPort( unsigned short usPort, DiscreteBundle* pBundle, unsigned short usLine ) override;
	};

}

#endif// _STANDARDSWITCH_H_

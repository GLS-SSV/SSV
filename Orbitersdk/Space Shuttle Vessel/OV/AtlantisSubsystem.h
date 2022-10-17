/****************************************************************************
  This file is part of Space Shuttle Vessel

  Basic subsystem definitions


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
2021/06/06   GLS
2021/08/24   GLS
2021/12/26   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Basic subsystem definitions



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

#ifndef _ATLANTISSUBSYSTEM_H_
#define _ATLANTISSUBSYSTEM_H_


#include <Subsystem.h>
#include <string>


using namespace std;

class Atlantis;
class AtlantisSubsystemDirector;

namespace discsignals
{
	class DiscreteBundleManager;
}

/**
 * base class for all subsystem simulations.
 */
class AtlantisSubsystem : public Subsystem<Atlantis>
{
public:
	/**
	 * Create a new Atlantis subsystem object
	 */
	AtlantisSubsystem(AtlantisSubsystemDirector* _director, const string& _ident);
	/**
	 * Destructor
	 */
	virtual ~AtlantisSubsystem();

	/**
	 * Get a reference to the Space Shuttle external physical model.
	 * @return reference to the space shuttle object. If possible.
	 */
	Atlantis* STS() const;

	/**
	 * Return the currently used discrete bundle managing object.
	 * @return pointer to the bundle manager
	 */
	discsignals::DiscreteBundleManager* BundleManager() const;
};


#endif// _ATLANTISSUBSYSTEM_H_

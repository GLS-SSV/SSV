/****************************************************************************
  This file is part of Space Shuttle Vessel

  Discrete line bundle manager definition


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
2020/08/24   GLS
2020/09/04   GLS
2021/08/24   GLS
2022/07/16   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Discrete line bundle manager definition



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
#ifndef __DISCRETEBUNDLEMANAGER_H_
#define __DISCRETEBUNDLEMANAGER_H_


#include <vector>
#include <string>
#include "DiscreteBundle.h"

namespace discsignals {

	using namespace std;

class DiscreteBundleManager
{
	vector <DiscreteBundle*> bundles;
public:
	DiscreteBundleManager(void);
	virtual ~DiscreteBundleManager(void);

	unsigned long CountBundles() const;
	void AddBundle(DiscreteBundle* bBundle);
	DiscreteBundle* FindBundle(const string& _ident) const;

	DiscreteBundle* GetBundleByIndex(unsigned long ulIndex) const;
	DiscreteBundle* CreateBundle(const string& _ident, unsigned short usLines);
	void DumpToLog() const;
};

}

#endif// __DISCRETEBUNDLEMANAGER_H_

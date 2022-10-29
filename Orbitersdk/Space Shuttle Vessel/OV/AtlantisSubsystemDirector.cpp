/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/06/06   GLS
2021/08/24   GLS
2022/09/29   GLS
********************************************/
#include "AtlantisSubsystemDirector.h"
#include "Atlantis.h"
#include "AtlantisSubsystem.h"
#include <DiscreteBundleManager.h>


AtlantisSubsystemDirector::AtlantisSubsystemDirector(Atlantis *_sts)
: SubsystemDirector(_sts)
{
}

AtlantisSubsystemDirector::~AtlantisSubsystemDirector()
{
}

discsignals::DiscreteBundleManager* AtlantisSubsystemDirector::BundleManager() const
{
	return V()->BundleManager();
}

/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/04/07   GLS
2020/06/20   GLS
2021/06/06   GLS
2021/08/24   GLS
********************************************/
// AtlantisSubsystem.cpp: Implementierung der Klasse AtlantisSubsystem.
//
//////////////////////////////////////////////////////////////////////

#include "AtlantisSubsystem.h"
#include "AtlantisSubsystemDirector.h"
#include "Atlantis.h"
#include "DiscreteBundleManager.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

AtlantisSubsystem::AtlantisSubsystem(AtlantisSubsystemDirector* _director, const string& _ident)
: Subsystem(_director, _ident)
{
	oapiWriteLogV( "(AtlantisSubsystem) Create subsystem %s.", ident.c_str() );
}

AtlantisSubsystem::~AtlantisSubsystem()
{

}

Atlantis* AtlantisSubsystem::STS() const
{
	return director->V();
}


discsignals::DiscreteBundleManager* AtlantisSubsystem::BundleManager() const
{
	return dynamic_cast<AtlantisSubsystemDirector*>(director)->BundleManager();
}

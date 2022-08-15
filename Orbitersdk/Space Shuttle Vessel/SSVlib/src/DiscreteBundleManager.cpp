/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/03/29   GLS
2020/08/24   GLS
2020/09/04   GLS
2021/01/20   GLS
2021/08/24   GLS
2022/08/05   GLS
********************************************/
#include "DiscreteBundleManager.h"
#include <OrbiterAPI.h>
#include <cassert>


namespace discsignals {

DiscreteBundleManager::DiscreteBundleManager(void)
: bundles()
{
}

DiscreteBundleManager::~DiscreteBundleManager(void)
{
	for(unsigned int i=0;i<bundles.size();i++) {
		DiscreteBundle* pBundle=bundles[i];
		delete pBundle;
	}
	bundles.clear();
}

void DiscreteBundleManager::DumpToLog() const
{
	oapiWriteLog("(DiscreteBundleManager) Bundle dump:");
	//Dump all registered Bundles to the orbiter log
	for(unsigned int i=0;i<bundles.size();i++) {
		oapiWriteLogV( "%d\t:\t%s\t:\t%d",
			i+1, bundles.at(i)->GetIdentity().c_str(), bundles.at(i)->CountLines() );
	}
}

void DiscreteBundleManager::AddBundle(discsignals::DiscreteBundle *pBundle)
{
	assert( (pBundle != NULL) && "DiscreteBundleManager::AddBundle.pBundle" );

	bundles.push_back(pBundle);
	return;
}

DiscreteBundle* DiscreteBundleManager::CreateBundle(const std::string &_ident, unsigned short usLines)
{
	//char pszBuffer[400];
	//DumpToLog();
	//sprintf_s(pszBuffer, 400, "(DiscreteBundleManager::CreateBundle) Enter \"%s\"", _ident.c_str());
	//oapiWriteLog(pszBuffer);

	DiscreteBundle* pE = FindBundle(_ident);
	if (pE != NULL)
	{
		//oapiWriteLog("(DiscreteBundleManager::CreateBundle) Found Bundle");
		return pE;
	}

	DiscreteBundle* pR = new DiscreteBundle(_ident, usLines);
	AddBundle(pR);
	//oapiWriteLog("(DiscreteBundleManager::CreateBundle) Added new bundle");
	return pR;
}

unsigned long DiscreteBundleManager::CountBundles() const
{
	return bundles.size();
}

DiscreteBundle* DiscreteBundleManager::FindBundle(const std::string &_ident) const
{
	try {
		for(unsigned int i = 0; i<bundles.size(); i++)
		{
			if(bundles.at(i)->GetIdentity() == _ident)
				return bundles.at(i);
		}
	}
	catch(...)
	{
		oapiWriteLog("(DiscreteBundleManager::FindBundle) Uncaught exception.");
		return NULL;
	}
	return NULL;
};

DiscreteBundle* DiscreteBundleManager::GetBundleByIndex(unsigned long ulIndex) const
{
	assert( (ulIndex <= bundles.size()) && "DiscreteBundleManager::GetBundleByIndex.ulIndex" );

	return bundles.at( ulIndex );
}


};
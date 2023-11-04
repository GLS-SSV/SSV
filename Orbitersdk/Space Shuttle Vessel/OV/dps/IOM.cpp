#include "IOM.h"


namespace dps
{
	IOM::IOM( const std::string& mdmname, const unsigned short iomidx ):
	mdmname(mdmname), iomidx(iomidx)
	{
		return;
	}

	IOM::~IOM()
	{
		return;
	}
	
	void IOM::Connect( discsignals::DiscreteBundleManager* bman )
	{
		return;
	}

	bool IOM::LoadState( const char* line )
	{
		return false;
	}

	void IOM::SaveState( FILEHANDLE scn ) const
	{
		return;
	}

	void IOM::PowerLoss( void )
	{
		return;
	}
}

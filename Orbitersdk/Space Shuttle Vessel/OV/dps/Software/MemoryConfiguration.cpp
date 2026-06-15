#include "MemoryConfiguration.h"
#include "../SimpleGPCSystem.h"


namespace dps
{
	MemoryConfiguration::MemoryConfiguration( SimpleGPCSystem* pGPC, const unsigned short ID ):pGPC( pGPC ), ID(ID)
	{
		return;
	}

	unsigned short MemoryConfiguration::GetID( void ) const
	{
		return ID;
	};

	bool MemoryConfiguration::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	};

	void MemoryConfiguration::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	};
}

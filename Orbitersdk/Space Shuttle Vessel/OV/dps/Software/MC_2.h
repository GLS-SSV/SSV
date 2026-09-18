#ifndef _MC_2_H_
#define _MC_2_H_


#include "MemoryConfiguration.h"


namespace dps
{
	class MC_2 : public MemoryConfiguration
	{
		public:
			MC_2( SimpleGPCSystem* pGPC );

			void Init( std::vector<SimpleGPCSoftware*>& vCOMSUB, std::vector<unsigned short>& vDFB ) override;

			bool ScheduleProgram( std::vector<SimpleGPCSoftware*>& vPROGRAM, const std::string& name ) override;

			bool OnParseLine( const char* keyword, const char* value ) override;

			void OnSaveState( FILEHANDLE scn ) const override;
	};
}

#endif// _MC_2_H_

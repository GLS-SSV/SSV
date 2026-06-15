#ifndef _MEMORYCONFIGURATION_H_
#define _MEMORYCONFIGURATION_H_


#include <vector>
#include <OrbiterAPI.h >


namespace dps
{
	class SimpleGPCSystem;
	class SimpleGPCSoftware;


	class MemoryConfiguration
	{
		protected:
			SimpleGPCSystem* pGPC;
			unsigned short ID;

		public:
			MemoryConfiguration( SimpleGPCSystem* pGPC, const unsigned short ID );

			unsigned short GetID( void ) const;

			virtual void Init( std::vector<SimpleGPCSoftware*>& vCOMSUB, std::vector<unsigned short>& vDFB ) = 0;

			virtual bool ScheduleProgram( std::vector<SimpleGPCSoftware*>& vPROGRAM, const std::string& name ) = 0;

			virtual bool OnParseLine( const char* keyword, const char* value );

			virtual void OnSaveState( FILEHANDLE scn ) const;
	};
}

#endif// _MEMORYCONFIGURATION_H_

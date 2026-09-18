#ifndef _GNC8_OPS_H_
#define _GNC8_OPS_H_


#include "../ControlSegment.h"


namespace dps
{
	class GNC8_OPS_Mode_1_Block_1 : public CS_Block
	{
		public:
			GNC8_OPS_Mode_1_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS );

			void Init( void ) override;
			void Input( void ) override;
			void CleanUp( void ) override;
	};

	class GNC8_OPS_Mode_1 : public CS_Mode
	{
		public:
			GNC8_OPS_Mode_1( SimpleGPCSystem* pGPC, ControlSegment* pCS );

			void Init( void ) override;
			void CleanUp( void ) override;
	};


	class GNC8_OPS : public ControlSegmentOPS
	{
		public:
			GNC8_OPS( SimpleGPCSystem* pGPC );

			void Init( void ) override;
			void CleanUp( void ) override;

			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;
	};
}

#endif// _GNC8_OPS_H_

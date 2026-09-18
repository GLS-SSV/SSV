#ifndef _GNC9_OPS_H_
#define _GNC9_OPS_H_


#include "../ControlSegment.h"


namespace dps
{
	class GNC9_OPS_Mode_1_Block_1 : public CS_Block
	{
		public:
			GNC9_OPS_Mode_1_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS );

			void Init( void ) override;
			void Input( void ) override;
			void CleanUp( void ) override;
	};

	class GNC9_OPS_Mode_1 : public CS_Mode
	{
		public:
			GNC9_OPS_Mode_1( SimpleGPCSystem* pGPC, ControlSegment* pCS );

			void Init( void ) override;
			void CleanUp( void ) override;
	};


	class GNC9_OPS : public ControlSegmentOPS
	{
		public:
			GNC9_OPS( SimpleGPCSystem* pGPC );

			void Init( void ) override;
			void CleanUp( void ) override;

			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;
	};
}

#endif// _GNC9_OPS_H_

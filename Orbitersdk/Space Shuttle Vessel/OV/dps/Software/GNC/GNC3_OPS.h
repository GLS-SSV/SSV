#ifndef _GNC3_OPS_H_
#define _GNC3_OPS_H_


#include "../ControlSegment.h"


namespace dps
{
	class GNC3_OPS_Mode_1_Block_1 : public CS_Block
	{
		public:
			GNC3_OPS_Mode_1_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS );

			void Init( void ) override;
			void Input( void ) override;
			void CleanUp( void ) override;
	};

	class GNC3_OPS_Mode_1 : public CS_Mode
	{
		public:
			GNC3_OPS_Mode_1( SimpleGPCSystem* pGPC, ControlSegment* pCS );

			void Init( void ) override;
			void CleanUp( void ) override;
	};


	class GNC3_OPS_Mode_2_Block_1 : public CS_Block
	{
		public:
			GNC3_OPS_Mode_2_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS );

			void Init( void ) override;
			void Input( void ) override;
			void CleanUp( void ) override;
	};

	class GNC3_OPS_Mode_2 : public CS_Mode
	{
		public:
			GNC3_OPS_Mode_2( SimpleGPCSystem* pGPC, ControlSegment* pCS );

			void Init( void ) override;
			void CleanUp( void ) override;
	};


	class GNC3_OPS_Mode_3_Block_1 : public CS_Block
	{
		public:
			GNC3_OPS_Mode_3_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS );

			void Init( void ) override;
			void Input( void ) override;
			void CleanUp( void ) override;
	};

	class GNC3_OPS_Mode_3 : public CS_Mode
	{
		public:
			GNC3_OPS_Mode_3( SimpleGPCSystem* pGPC, ControlSegment* pCS );

			void Init( void ) override;
			void CleanUp( void ) override;
	};


	class GNC3_OPS_Mode_4_Block_1 : public CS_Block
	{
		public:
			GNC3_OPS_Mode_4_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS );

			void Init( void ) override;
			void Input( void ) override;
			void CleanUp( void ) override;
	};

	class GNC3_OPS_Mode_4 : public CS_Mode
	{
		public:
			GNC3_OPS_Mode_4( SimpleGPCSystem* pGPC, ControlSegment* pCS );

			void Init( void ) override;
			void CleanUp( void ) override;
	};


	class GNC3_OPS_Mode_5_Block_1 : public CS_Block
	{
		public:
			GNC3_OPS_Mode_5_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS );

			void Init( void ) override;
			void Input( void ) override;
			void CleanUp( void ) override;
	};

	class GNC3_OPS_Mode_5 : public CS_Mode
	{
		public:
			GNC3_OPS_Mode_5( SimpleGPCSystem* pGPC, ControlSegment* pCS );

			void Init( void ) override;
			void CleanUp( void ) override;
	};


	class GNC3_OPS : public ControlSegmentOPS
	{
		public:
			GNC3_OPS( SimpleGPCSystem* pGPC );

			void Init( void ) override;
			void CleanUp( void ) override;

			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;
	};
}

#endif// _GNC3_OPS_H_

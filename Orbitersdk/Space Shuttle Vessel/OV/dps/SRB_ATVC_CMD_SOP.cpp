/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/04/07   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
********************************************/
#include "SRB_ATVC_CMD_SOP.h"
#include "..\Atlantis.h"
#include <cassert>


namespace dps
{
	SRB_ATVC_CMD_SOP::SRB_ATVC_CMD_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "SRB_ATVC_CMD_SOP" )
	{
		Rpos[0] = 0.0;
		Rpos[1] = 0.0;
		Tpos[0] = 0.0;
		Tpos[1] = 0.0;
		return;
	}

	SRB_ATVC_CMD_SOP::~SRB_ATVC_CMD_SOP( void )
	{
		return;
	}

	void SRB_ATVC_CMD_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		for (int i = 0; i < 2; i++)
		{
			dopRpos[i].SetLine( static_cast<float>(Rpos[i]) );
			dopTpos[i].SetLine( static_cast<float>(Tpos[i]) );
		}
		//sprintf_s( oapiDebugString(), 256, "%.2f %.2f %.2f %.2f", Rpos[0], Rpos[1], Tpos[0], Tpos[1] );
		return;
	}

	void SRB_ATVC_CMD_SOP::Realize( void )
	{
		DiscreteBundle* bundle = BundleManager()->CreateBundle( "ATVC", 10 );
		dopRpos[0].Connect( bundle, 6 );
		dopRpos[1].Connect( bundle, 7 );
		dopTpos[0].Connect( bundle, 8 );
		dopTpos[1].Connect( bundle, 9 );

		for (int i = 0; i < 2; i++)
		{
			dopRpos[i].SetLine( static_cast<float>(Rpos[i]) );
			dopTpos[i].SetLine( static_cast<float>(Tpos[i]) );
		}
		return;
	}

	bool SRB_ATVC_CMD_SOP::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void SRB_ATVC_CMD_SOP::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	bool SRB_ATVC_CMD_SOP::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 101:
			case 102:
				return true;
			default:
				return false;
		}
	}

	void SRB_ATVC_CMD_SOP::SetSRBActPos( unsigned int num, double Rpos, double Tpos )
	{
		assert( (num <= 1) && "SRB_ATVC_CMD_SOP::SetSRBActPos.num" );

		this->Rpos[num] = Rpos;
		this->Tpos[num] = Tpos;
		return;
	}
}
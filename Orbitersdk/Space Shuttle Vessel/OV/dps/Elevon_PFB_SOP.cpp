/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
********************************************/
#include "Elevon_PFB_SOP.h"


namespace dps
{
	Elevon_PFB_SOP::Elevon_PFB_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "Elevon_PFB_SOP" )
	{
		return;
	}

	Elevon_PFB_SOP::~Elevon_PFB_SOP( void )
	{
		return;
	}

	void Elevon_PFB_SOP::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "AEROSURFACE_POS", 16 );
		dipPositionFeedbackLOB.Connect( pBundle, 0 );
		dipPositionFeedbackLIB.Connect( pBundle, 1 );
		dipPositionFeedbackRIB.Connect( pBundle, 2 );
		dipPositionFeedbackROB.Connect( pBundle, 3 );
		return;
	}

	void Elevon_PFB_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		double LOB = ((dipPositionFeedbackLOB.GetVoltage() * (21.1 + 36.5)) / 5.0) - 36.5;// (-36.5,+21.1) [deg]
		double LIB = ((dipPositionFeedbackLIB.GetVoltage() * (21.3 + 36.5)) / 5.0) - 36.5;// (-36.5,+21.3) [deg]
		double RIB = ((dipPositionFeedbackRIB.GetVoltage() * (21.3 + 36.5)) / 5.0) - 36.5;// (-36.5,+21.3) [deg]
		double ROB = ((dipPositionFeedbackROB.GetVoltage() * (21.1 + 36.5)) / 5.0) - 36.5;// (-36.5,+21.1) [deg]

		double DEFB = (LOB + LIB + RIB + ROB) * 0.25;
		double DAFB = (LOB + LIB - RIB - ROB) * 0.25;

		WriteCOMPOOL_SD( SCP_LOB_ELVN_POS_FDBK, static_cast<float>(LOB) );
		WriteCOMPOOL_SD( SCP_LIB_ELVN_POS_FDBK, static_cast<float>(LIB) );
		WriteCOMPOOL_SD( SCP_RIB_ELVN_POS_FDBK, static_cast<float>(RIB) );
		WriteCOMPOOL_SD( SCP_ROB_ELVN_POS_FDBK, static_cast<float>(ROB) );

		WriteCOMPOOL_SD( SCP_DEFB, static_cast<float>(DEFB) );
		WriteCOMPOOL_SD( SCP_DAFB, static_cast<float>(DAFB) );
		return;
	}

	bool Elevon_PFB_SOP::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 101:
			case 102:
			case 301:
			case 302:
			case 303:
			case 304:
			case 305:
			case 602:
			case 603:
			case 801:
				return true;
			default:
				return false;
		}
	}

	void Elevon_PFB_SOP::GetPosition( double& LOB, double& LIB, double& RIB, double& ROB, double& DAFB ) const
	{
		LOB = ReadCOMPOOL_SD( SCP_LOB_ELVN_POS_FDBK );
		LIB = ReadCOMPOOL_SD( SCP_LIB_ELVN_POS_FDBK );
		RIB = ReadCOMPOOL_SD( SCP_RIB_ELVN_POS_FDBK );
		ROB = ReadCOMPOOL_SD( SCP_ROB_ELVN_POS_FDBK );
		DAFB = ReadCOMPOOL_SD( SCP_DAFB );
		return;
	}
}
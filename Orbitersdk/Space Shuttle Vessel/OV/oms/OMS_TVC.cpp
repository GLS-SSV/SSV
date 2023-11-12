/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/09/29   GLS
2022/12/28   GLS
2022/12/29   GLS
2023/01/01   GLS
2023/11/08   GLS
********************************************/
#include "OMS_TVC.h"
#include "../Atlantis.h"
#include <cassert>
#include <MathSSV.h>


namespace oms
{
	OMS_TVC::OMS_TVC( AtlantisSubsystemDirector* _director, const string& _ident, unsigned int ID ):AtlantisSubsystem( _director, _ident ),
		ID(ID), pitch(0.0), yaw(0.0), PRI_P_driving(false), PRI_Y_driving(false), SEC_P_driving(false), SEC_Y_driving(false)
	{
		assert( (ID <= 1) && "OMS_TVC::OMS_TVC.ID" );
		return;
	}

	OMS_TVC::~OMS_TVC( void )
	{
		return;
	}

	void OMS_TVC::Realize( void )
	{
		DiscreteBundle* pBundle;
		if (ID == 0)
		{
			// left
			pBundle = BundleManager()->CreateBundle( "MDM_FF1_IOM2_CH2", 16 );
			OMS_ENG_PRI_ENA_1.Connect( pBundle, 1 );
			OMS_ENG_PRI_ENA_2.Connect( pBundle, 2 );

			pBundle = BundleManager()->CreateBundle( "MDM_FF2_IOM2_CH2", 16 );
			OMS_ENG_SEC_ENA_1.Connect( pBundle, 1 );
			OMS_ENG_SEC_ENA_2.Connect( pBundle, 2 );

			pBundle = BundleManager()->CreateBundle( "MDM_FA1_IOM4_PLUS", 16 );
			OMS_PRI_P_ACTR_CMD.Connect( pBundle, 7 );
			OMS_PRI_Y_ACTR_CMD.Connect( pBundle, 8 );

			pBundle = BundleManager()->CreateBundle( "MDM_FA1_IOM14_CH0_15", 16 );
			OMS_PRI_P_ACTR_POS.Connect( pBundle, 14 );
			OMS_PRI_Y_ACTR_POS.Connect( pBundle, 15 );

			pBundle = BundleManager()->CreateBundle( "MDM_FA2_IOM4_PLUS", 16 );
			OMS_SEC_P_ACTR_CMD.Connect( pBundle, 7 );
			OMS_SEC_Y_ACTR_CMD.Connect( pBundle, 8 );

			pBundle = BundleManager()->CreateBundle( "MDM_FA2_IOM14_CH0_15", 16 );
			OMS_SEC_P_ACTR_POS.Connect( pBundle, 14 );
			OMS_SEC_Y_ACTR_POS.Connect( pBundle, 15 );
		}
		else
		{
			// rights
			pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM2_CH2", 16 );
			OMS_ENG_SEC_ENA_1.Connect( pBundle, 1 );
			OMS_ENG_SEC_ENA_2.Connect( pBundle, 2 );

			pBundle = BundleManager()->CreateBundle( "MDM_FF4_IOM2_CH2", 16 );
			OMS_ENG_PRI_ENA_1.Connect( pBundle, 1 );
			OMS_ENG_PRI_ENA_2.Connect( pBundle, 2 );

			pBundle = BundleManager()->CreateBundle( "MDM_FA3_IOM4_PLUS", 16 );
			OMS_SEC_P_ACTR_CMD.Connect( pBundle, 7 );
			OMS_SEC_Y_ACTR_CMD.Connect( pBundle, 8 );

			pBundle = BundleManager()->CreateBundle( "MDM_FA3_IOM14_CH0_15", 16 );
			OMS_SEC_P_ACTR_POS.Connect( pBundle, 14 );
			OMS_SEC_Y_ACTR_POS.Connect( pBundle, 15 );

			pBundle = BundleManager()->CreateBundle( "MDM_FA4_IOM4_PLUS", 16 );
			OMS_PRI_P_ACTR_CMD.Connect( pBundle, 7 );
			OMS_PRI_Y_ACTR_CMD.Connect( pBundle, 8 );

			pBundle = BundleManager()->CreateBundle( "MDM_FA4_IOM14_CH0_15", 16 );
			OMS_PRI_P_ACTR_POS.Connect( pBundle, 14 );
			OMS_PRI_Y_ACTR_POS.Connect( pBundle, 15 );
		}

		STS()->GimbalOMS( ID, pitch, yaw );// set position at start of sim
		return;
	}

	bool OMS_TVC::OnParseLine( const char* line )
	{
		if (!_strnicmp( line, "PITCH", 5 ))
		{
			sscanf_s( line + 5, "%lf", &pitch );
			if ((pitch > 6.0) || (pitch < -6.0)) pitch = 0.0;
			return true;
		}
		else if (!_strnicmp( line, "YAW", 3 ))
		{
			sscanf_s( line + 3, "%lf", &yaw );
			if ((yaw > 7.0) || (yaw < -7.0)) yaw = 0.0;
			return true;
		}
		return false;
	}

	void OMS_TVC::OnSaveState( FILEHANDLE scn ) const
	{
		oapiWriteScenario_float( scn, "PITCH", pitch );
		oapiWriteScenario_float( scn, "YAW", yaw );
		return;
	}

	void OMS_TVC::OnPreStep( double simt, double simdt, double mjd )
	{
		// command position
		if (OMS_ENG_PRI_ENA_1.IsSet( 26.0f ) && OMS_ENG_PRI_ENA_2.IsSet( 26.0f ))
		{
			// pri
			double r = 3.0 * simdt;// 3º/sec
			double p = (OMS_PRI_P_ACTR_CMD.GetVoltage() + 0.0448) / 0.6097;
			double y;
			if (ID == 0) y = (OMS_PRI_Y_ACTR_CMD.GetVoltage() + 0.2595) / 0.6114;
			else y = (OMS_PRI_Y_ACTR_CMD.GetVoltage() + 0.2595) / -0.6114;

			Actuator( PRI_P_driving, pitch, p, r, 6.0 );
			Actuator( PRI_Y_driving, yaw, y, r, 7.0 );

			STS()->GimbalOMS( ID, pitch, yaw );
		}
		else if (OMS_ENG_SEC_ENA_1.IsSet( 26.0f ) && OMS_ENG_SEC_ENA_2.IsSet( 26.0f ))
		{
			// sec
			double r = 3.0 * simdt;// 3º/sec
			double p = (OMS_SEC_P_ACTR_CMD.GetVoltage() + 0.0448) / 0.6097;
			double y;
			if (ID == 0) y = (OMS_SEC_Y_ACTR_CMD.GetVoltage() + 0.2595) / 0.6114;
			else y = (OMS_SEC_Y_ACTR_CMD.GetVoltage() + 0.2595) / -0.6114;

			Actuator( SEC_P_driving, pitch, p, r, 6.0 );
			Actuator( SEC_Y_driving, yaw, y, r, 7.0 );

			STS()->GimbalOMS( ID, pitch, yaw );
		}


		// output position
		float vp = static_cast<float>((pitch - 0.0735) / 1.64);
		float vy;
		if (ID == 0) vy = static_cast<float>((yaw - 0.4244) / 1.636);
		else vy = static_cast<float>((yaw + 0.4244) / -1.636);
		OMS_PRI_P_ACTR_POS.SetLine( vp );
		OMS_PRI_Y_ACTR_POS.SetLine( vy );

		OMS_SEC_P_ACTR_POS.SetLine( vp );
		OMS_SEC_Y_ACTR_POS.SetLine( vy );
		return;
	}

	void OMS_TVC::Actuator( bool &driving, double &cur, double tgt, double step, double max )
	{
		double error = tgt - cur;

		// actuator hysteresis
		if (fabs( error ) < 0.06) driving = false;
		else if (fabs( error ) > 0.4) driving = true;

		if (driving)
		{
			if (error > 0.0)
			{
				double tmp = cur + step;
				error -= step;
				if (error < 0.06) tmp = tgt - 0.06;
				cur = range( -max, tmp, max );
			}
			else
			{
				double tmp = cur - step;
				error += step;
				if (error > -0.06) tmp = tgt + 0.06;
				cur = range( -max, tmp, max );
			}
		}
		return;
	}
}

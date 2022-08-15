/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
********************************************/
#include "OMS_TVC.h"
#include "..\Atlantis.h"
#include <cassert>
#include <MathSSV.h>


namespace oms
{
	OMS_TVC::OMS_TVC( AtlantisSubsystemDirector* _director, const string& _ident, unsigned int ID ):AtlantisSubsystem( _director, _ident )
	{
		assert( (ID <= 1) && "OMS_TVC::OMS_TVC.ID" );
		this->ID = ID;

		pitch = 0.0;
		yaw = 0.0;

		PRI_P_driving = false;
		PRI_Y_driving = false;
		SEC_P_driving = false;
		SEC_Y_driving = false;
		return;
	}

	OMS_TVC::~OMS_TVC( void )
	{
	}

	void OMS_TVC::Realize( void )
	{
		DiscreteBundle* pBundleC = BundleManager()->CreateBundle( "OMS_TVC_CMD", 16 );
		DiscreteBundle* pBundleF = BundleManager()->CreateBundle( "OMS_TVC_FDBK", 8 );

		if (ID == 0)
		{
			OMS_ENG_PRI_ENA_1.Connect( pBundleC, 0 );
			OMS_ENG_PRI_ENA_2.Connect( pBundleC, 1 );
			OMS_ENG_SEC_ENA_1.Connect( pBundleC, 2 );
			OMS_ENG_SEC_ENA_2.Connect( pBundleC, 3 );
			OMS_PRI_P_ACTR_CMD.Connect( pBundleC, 8 );
			OMS_SEC_P_ACTR_CMD.Connect( pBundleC, 9 );
			OMS_PRI_Y_ACTR_CMD.Connect( pBundleC, 10 );
			OMS_SEC_Y_ACTR_CMD.Connect( pBundleC, 11 );

			OMS_PRI_P_ACTR_POS.Connect( pBundleF, 0 );
			OMS_PRI_Y_ACTR_POS.Connect( pBundleF, 1 );
			OMS_SEC_P_ACTR_POS.Connect( pBundleF, 2 );
			OMS_SEC_Y_ACTR_POS.Connect( pBundleF, 3 );
		}
		else
		{
			OMS_ENG_PRI_ENA_1.Connect( pBundleC, 4 );
			OMS_ENG_PRI_ENA_2.Connect( pBundleC, 5 );
			OMS_ENG_SEC_ENA_1.Connect( pBundleC, 6 );
			OMS_ENG_SEC_ENA_2.Connect( pBundleC, 7 );
			OMS_PRI_P_ACTR_CMD.Connect( pBundleC, 12 );
			OMS_SEC_P_ACTR_CMD.Connect( pBundleC, 13 );
			OMS_PRI_Y_ACTR_CMD.Connect( pBundleC, 14 );
			OMS_SEC_Y_ACTR_CMD.Connect( pBundleC, 15 );

			OMS_PRI_P_ACTR_POS.Connect( pBundleF, 4 );
			OMS_PRI_Y_ACTR_POS.Connect( pBundleF, 5 );
			OMS_SEC_P_ACTR_POS.Connect( pBundleF, 6 );
			OMS_SEC_Y_ACTR_POS.Connect( pBundleF, 7 );
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
		if (OMS_ENG_PRI_ENA_1 && OMS_ENG_PRI_ENA_2)
		{
			// pri
			double r = 3.0 * simdt;// 3º/sec
			Actuator( PRI_P_driving, pitch, OMS_PRI_P_ACTR_CMD.GetVoltage(), r, 6.0 );
			Actuator( PRI_Y_driving, yaw, OMS_PRI_Y_ACTR_CMD.GetVoltage(), r, 7.0 );

			STS()->GimbalOMS( ID, pitch, yaw );
		}
		else if (OMS_ENG_SEC_ENA_1 && OMS_ENG_SEC_ENA_2)
		{
			// sec
			double r = 3.0 * simdt;// 3º/sec
			Actuator( SEC_P_driving, pitch, OMS_SEC_P_ACTR_CMD.GetVoltage(), r, 6.0 );
			Actuator( SEC_Y_driving, yaw, OMS_SEC_Y_ACTR_CMD.GetVoltage(), r, 7.0 );

			STS()->GimbalOMS( ID, pitch, yaw );
		}


		// output position
		OMS_PRI_P_ACTR_POS.SetLine( static_cast<float>(pitch) );
		OMS_PRI_Y_ACTR_POS.SetLine( static_cast<float>(yaw) );

		OMS_SEC_P_ACTR_POS.SetLine( static_cast<float>(pitch) );
		OMS_SEC_Y_ACTR_POS.SetLine( static_cast<float>(yaw) );
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

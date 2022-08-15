/******* SSV File Modification Notice *******
Date         Developer
2020/05/06   GLS
2020/06/20   GLS
2020/09/02   GLS
2021/08/24   GLS
2022/08/08   GLS
********************************************/
#include "7SegDisp_RMS.h"
#include "../RMS.h"
#include "../Atlantis.h"


namespace vc
{
	_7SegDisp_RMS::_7SegDisp_RMS( Atlantis* _sts, const std::string& _ident ):_7SegDisp( _sts, _ident )
	{
	}

	_7SegDisp_RMS::~_7SegDisp_RMS()
	{
	}

	void _7SegDisp_RMS::Realize( void )
	{
		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "A8_LED", 16 );
		for (int i = 0; i < 8; i++) LED_ParameterSelect[i].Connect( pBundle, i );

		pBundle = STS()->BundleManager()->CreateBundle( "RMS_SINGLE_JOINT", 16 );
		for (int i = 0; i < 8; i++) LED_JointSelect[i].Connect( pBundle, i );

		pBundle = STS()->BundleManager()->CreateBundle( "RMS_DATA", 16 );
		for (int i = 0; i < 6; i++) RMSJointAngles[i].Connect( pBundle, i );
		for (int i = 0; i < 3; i++)
		{
			EEPosition[i].Connect( pBundle, i + 6 );
			EEAttitude[i].Connect( pBundle, i + 9 );
		}

		pBundle = STS()->BundleManager()->CreateBundle( "RMS", 16 );
		RMSSelectPort.Connect( pBundle, 6 );
		return;
	}

	void _7SegDisp_RMS::Controller( void )
	{
		if (RMSSelectPort.IsSet())
		{
			if (LED_ParameterSelect[7].IsSet())
			{
				// STBD TEMP LED/ABE/ID
				// TODO
				next_state[14] = _7SD_STATE_SIGNOFF;
				next_state[13] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[12] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[11] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[10] = _7SD_STATE_NUM0_DOTOFF;
				next_state[9] = _7SD_STATE_SIGNOFF;
				next_state[8] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[7] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[6] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[5] = _7SD_STATE_NUM0_DOTOFF;
				next_state[4] = _7SD_STATE_SIGNOFF;
				next_state[3] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[2] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[1] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[0] = _7SD_STATE_NUM0_DOTOFF;
			}
			else if (LED_ParameterSelect[6].IsSet())
			{
				// PORT TEMP LED/ABE/ID
				// TODO
				next_state[14] = _7SD_STATE_SIGNOFF;
				next_state[13] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[12] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[11] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[10] = _7SD_STATE_NUM0_DOTOFF;
				next_state[9] = _7SD_STATE_SIGNOFF;
				next_state[8] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[7] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[6] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[5] = _7SD_STATE_NUM0_DOTOFF;
				next_state[4] = _7SD_STATE_SIGNOFF;
				next_state[3] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[2] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[1] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[0] = _7SD_STATE_NUM0_DOTOFF;
			}
			else if (LED_ParameterSelect[5].IsSet())
			{
				// RATE P/Y/R
				// TODO
				next_state[14] = _7SD_STATE_SIGNOFF;
				next_state[13] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[12] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[11] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[10] = _7SD_STATE_NUM0_DOTOFF;
				next_state[9] = _7SD_STATE_SIGNOFF;
				next_state[8] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[7] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[6] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[5] = _7SD_STATE_NUM0_DOTOFF;
				next_state[4] = _7SD_STATE_SIGNOFF;
				next_state[3] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[2] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[1] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[0] = _7SD_STATE_NUM0_DOTOFF;
			}
			else if (LED_ParameterSelect[4].IsSet())
			{
				// VEL X/Y/Z
				// TODO
				next_state[14] = _7SD_STATE_SIGNOFF;
				next_state[13] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[12] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[11] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[10] = _7SD_STATE_NUM0_DOTOFF;
				next_state[9] = _7SD_STATE_SIGNOFF;
				next_state[8] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[7] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[6] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[5] = _7SD_STATE_NUM0_DOTOFF;
				next_state[4] = _7SD_STATE_SIGNOFF;
				next_state[3] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[2] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[1] = _7SD_STATE_NUMOFF_DOTOFF;
				next_state[0] = _7SD_STATE_NUM0_DOTOFF;
			}
			else if (LED_ParameterSelect[3].IsSet())
			{
				// JOINT ANGLE
				if (LED_JointSelect[7].IsSet())
				{
					// CRIT TEMP
					// TODO
					next_state[14] = _7SD_STATE_SIGNOFF;
					next_state[13] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[12] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[11] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[10] = _7SD_STATE_NUM0_DOTOFF;
					next_state[9] = _7SD_STATE_SIGNOFF;
					next_state[8] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[7] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[6] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[5] = _7SD_STATE_NUM0_DOTOFF;
					next_state[4] = _7SD_STATE_SIGNOFF;
					next_state[3] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[2] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[1] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[0] = _7SD_STATE_NUM0_DOTOFF;
				}
				else if (LED_JointSelect[6].IsSet())
				{
					// END EFF TEMP
					// TODO
					next_state[14] = _7SD_STATE_SIGNOFF;
					next_state[13] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[12] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[11] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[10] = _7SD_STATE_NUM0_DOTOFF;
					next_state[9] = _7SD_STATE_SIGNOFF;
					next_state[8] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[7] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[6] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[5] = _7SD_STATE_NUM0_DOTOFF;
					next_state[4] = _7SD_STATE_SIGNOFF;
					next_state[3] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[2] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[1] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[0] = _7SD_STATE_NUM0_DOTOFF;
				}
				else if (LED_JointSelect[5].IsSet())
				{
					// WRIST ROLL
					char cbuf[8];
					int decimalpoint = 11;

					double roll = RMSJointAngles[RMS::WRIST_ROLL].GetVoltage() * 1999.8;
					if (!isfinite( roll )) roll = 888.8;

					if (fabs( roll ) < 9.999)
					{
						// X.XXX
						sprintf_s( cbuf, 8, "%05.3f", fabs( roll ) );
						decimalpoint = 13;
					}
					else if (fabs( roll ) < 99.99)
					{
						// XX.XX
						sprintf_s( cbuf, 8, "%05.2f", fabs( roll ) );
						decimalpoint = 12;
					}
					else// if (fabs( roll ) < 999.9)
					{
						// XXX.X
						sprintf_s( cbuf, 8, "%05.1f", fabs( roll ) );
						//decimalpoint = 11;
					}

					for (int i = 13, j = 0; i >= 10; i--, j++)
					{
						if (cbuf[j] == '.') j++;

						next_state[i] = cbuf[j] - 48 + _7SD_STATE_NUM0_DOTOFF;
					}

					next_state[decimalpoint] -= _7SD_STATE_NUM0_DOTON;

					if (roll < 0.0) next_state[14] = _7SD_STATE_SIGNMINUS;
					else next_state[14] = _7SD_STATE_SIGNPLUS;

					next_state[9] = _7SD_STATE_SIGNOFF;
					next_state[8] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[7] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[6] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[5] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[4] = _7SD_STATE_SIGNOFF;
					next_state[3] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[2] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[1] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[0] = _7SD_STATE_NUMOFF_DOTOFF;
				}
				else if (LED_JointSelect[4].IsSet())
				{
					// WRIST YAW
					char cbuf[8];
					int decimalpoint = 6;

					double yaw = RMSJointAngles[RMS::WRIST_YAW].GetVoltage() * 1999.8;
					if (!isfinite( yaw )) yaw = 888.8;

					if (fabs( yaw ) < 9.999)
					{
						// X.XXX
						sprintf_s( cbuf, 8, "%05.3f", fabs( yaw ) );
						decimalpoint = 8;
					}
					else if (fabs( yaw ) < 99.99)
					{
						// XX.XX
						sprintf_s( cbuf, 8, "%05.2f", fabs( yaw ) );
						decimalpoint = 7;
					}
					else// if (fabs( yaw ) < 999.9)
					{
						// XXX.X
						sprintf_s( cbuf, 8, "%05.1f", fabs( yaw ) );
						//decimalpoint = 6;
					}

					for (int i = 8, j = 0; i >= 5; i--, j++)
					{
						if (cbuf[j] == '.') j++;

						next_state[i] = cbuf[j] - 48 + _7SD_STATE_NUM0_DOTOFF;
					}

					next_state[decimalpoint] -= _7SD_STATE_NUM0_DOTON;

					if (yaw < 0.0) next_state[9] = _7SD_STATE_SIGNMINUS;
					else next_state[9] = _7SD_STATE_SIGNPLUS;

					next_state[14] = _7SD_STATE_SIGNOFF;
					next_state[13] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[12] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[11] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[10] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[4] = _7SD_STATE_SIGNOFF;
					next_state[3] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[2] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[1] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[0] = _7SD_STATE_NUMOFF_DOTOFF;
				}
				else if (LED_JointSelect[3].IsSet())
				{
					// WRIST PITCH
					char cbuf[8];
					int decimalpoint = 1;

					double pitch = RMSJointAngles[RMS::WRIST_PITCH].GetVoltage() * 1999.8;
					if (!isfinite( pitch )) pitch = 888.8;

					if (fabs( pitch ) < 9.999)
					{
						// X.XXX
						sprintf_s( cbuf, 8, "%05.3f", fabs( pitch ) );
						decimalpoint = 3;
					}
					else if (fabs( pitch ) < 99.99)
					{
						// XX.XX
						sprintf_s( cbuf, 8, "%05.2f", fabs( pitch ) );
						decimalpoint = 2;
					}
					else// if (fabs( pitch ) < 999.9)
					{
						// XXX.X
						sprintf_s( cbuf, 8, "%05.1f", fabs( pitch ) );
						//decimalpoint = 1;
					}

					for (int i = 3, j = 0; i >= 0; i--, j++)
					{
						if (cbuf[j] == '.') j++;

						next_state[i] = cbuf[j] - 48 + _7SD_STATE_NUM0_DOTOFF;
					}

					next_state[decimalpoint] -= _7SD_STATE_NUM0_DOTON;

					if (pitch < 0.0) next_state[4] = _7SD_STATE_SIGNMINUS;
					else next_state[4] = _7SD_STATE_SIGNPLUS;

					next_state[14] = _7SD_STATE_SIGNOFF;
					next_state[13] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[12] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[11] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[10] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[9] = _7SD_STATE_SIGNOFF;
					next_state[8] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[7] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[6] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[5] = _7SD_STATE_NUMOFF_DOTOFF;
				}
				else if (LED_JointSelect[2].IsSet())
				{
					// ELBOW
					char cbuf[8];
					int decimalpoint = 1;

					double pitch = RMSJointAngles[RMS::ELBOW_PITCH].GetVoltage() * 1999.8;
					if (!isfinite( pitch )) pitch = 888.8;

					if (fabs( pitch ) < 9.999)
					{
						// X.XXX
						sprintf_s( cbuf, 8, "%05.3f", fabs( pitch ) );
						decimalpoint = 3;
					}
					else if (fabs( pitch ) < 99.99)
					{
						// XX.XX
						sprintf_s( cbuf, 8, "%05.2f", fabs( pitch ) );
						decimalpoint = 2;
					}
					else// if (fabs( pitch ) < 999.9)
					{
						// XXX.X
						sprintf_s( cbuf, 8, "%05.1f", fabs( pitch ) );
						//decimalpoint = 1;
					}

					for (int i = 3, j = 0; i >= 0; i--, j++)
					{
						if (cbuf[j] == '.') j++;

						next_state[i] = cbuf[j] - 48 + _7SD_STATE_NUM0_DOTOFF;
					}

					next_state[decimalpoint] -= _7SD_STATE_NUM0_DOTON;

					if (pitch < 0.0) next_state[4] = _7SD_STATE_SIGNMINUS;
					else next_state[4] = _7SD_STATE_SIGNPLUS;

					next_state[14] = _7SD_STATE_SIGNOFF;
					next_state[13] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[12] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[11] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[10] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[9] = _7SD_STATE_SIGNOFF;
					next_state[8] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[7] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[6] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[5] = _7SD_STATE_NUMOFF_DOTOFF;
				}
				else if (LED_JointSelect[1].IsSet())
				{
					// SHOULDER PITCH
					char cbuf[8];
					int decimalpoint = 1;

					double pitch = RMSJointAngles[RMS::SHOULDER_PITCH].GetVoltage() * 1999.8;
					if (!isfinite( pitch )) pitch = 888.8;

					if (fabs( pitch ) < 9.999)
					{
						// X.XXX
						sprintf_s( cbuf, 8, "%05.3f", fabs( pitch ) );
						decimalpoint = 3;
					}
					else if (fabs( pitch ) < 99.99)
					{
						// XX.XX
						sprintf_s( cbuf, 8, "%05.2f", fabs( pitch ) );
						decimalpoint = 2;
					}
					else// if (fabs( pitch ) < 999.9)
					{
						// XXX.X
						sprintf_s( cbuf, 8, "%05.1f", fabs( pitch ) );
						//decimalpoint = 1;
					}

					for (int i = 3, j = 0; i >= 0; i--, j++)
					{
						if (cbuf[j] == '.') j++;

						next_state[i] = cbuf[j] - 48 + _7SD_STATE_NUM0_DOTOFF;
					}

					next_state[decimalpoint] -= _7SD_STATE_NUM0_DOTON;

					if (pitch < 0.0) next_state[4] = _7SD_STATE_SIGNMINUS;
					else next_state[4] = _7SD_STATE_SIGNPLUS;

					next_state[14] = _7SD_STATE_SIGNOFF;
					next_state[13] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[12] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[11] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[10] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[9] = _7SD_STATE_SIGNOFF;
					next_state[8] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[7] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[6] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[5] = _7SD_STATE_NUMOFF_DOTOFF;
				}
				else// if (LED_JointSelect[0].IsSet())
				{
					// SHOULDER YAW
					char cbuf[8];
					int decimalpoint = 6;

					double yaw = -RMSJointAngles[RMS::SHOULDER_YAW].GetVoltage() * 1999.8;// HACK minus added to fix wrong sign coming from RMS
					if (!isfinite( yaw )) yaw = 888.8;

					if (fabs( yaw ) < 9.999)
					{
						// X.XXX
						sprintf_s( cbuf, 8, "%05.3f", fabs( yaw ) );
						decimalpoint = 8;
					}
					else if (fabs( yaw ) < 99.99)
					{
						// XX.XX
						sprintf_s( cbuf, 8, "%05.2f", fabs( yaw ) );
						decimalpoint = 7;
					}
					else// if (fabs( yaw ) < 999.9)
					{
						// XXX.X
						sprintf_s( cbuf, 8, "%05.1f", fabs( yaw ) );
						//decimalpoint = 6;
					}

					for (int i = 8, j = 0; i >= 5; i--, j++)
					{
						if (cbuf[j] == '.') j++;

						next_state[i] = cbuf[j] - 48 + _7SD_STATE_NUM0_DOTOFF;
					}

					next_state[decimalpoint] -= _7SD_STATE_NUM0_DOTON;

					if (yaw < 0.0) next_state[9] = _7SD_STATE_SIGNMINUS;
					else next_state[9] = _7SD_STATE_SIGNPLUS;

					next_state[14] = _7SD_STATE_SIGNOFF;
					next_state[13] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[12] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[11] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[10] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[4] = _7SD_STATE_SIGNOFF;
					next_state[3] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[2] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[1] = _7SD_STATE_NUMOFF_DOTOFF;
					next_state[0] = _7SD_STATE_NUMOFF_DOTOFF;
				}
			}
			else if (LED_ParameterSelect[2].IsSet())
			{
				// ATTITUDE P/Y/R
				char cbuf[8];

				// P
				double att = EEAttitude[0].GetVoltage() * 2000.0;
				if (!isfinite( att )) att = 888.8;
				sprintf_s( cbuf, 8, "%5.1f", fabs( att ) );

				for (int i = 3, j = 0; i >= 0; i--, j++)
				{
					if (cbuf[j] == '.') j++;

					if (cbuf[j] == ' ') next_state[i] = _7SD_STATE_NUMOFF_DOTOFF;
					else next_state[i] = cbuf[j] - 48 + _7SD_STATE_NUM0_DOTOFF;
				}

				next_state[1] -= _7SD_STATE_NUM0_DOTON;

				if (att < 0.0) next_state[4] = _7SD_STATE_SIGNMINUS;
				else next_state[4] = _7SD_STATE_SIGNPLUS;

				// Y
				att = EEAttitude[1].GetVoltage() * 2000.0;
				if (!isfinite( att )) att = 888.8;
				sprintf_s( cbuf, 8, "%5.1f", fabs( att ) );

				for (int i = 8, j = 0; i >= 5; i--, j++)
				{
					if (cbuf[j] == '.') j++;

					if (cbuf[j] == ' ') next_state[i] = _7SD_STATE_NUMOFF_DOTOFF;
					else next_state[i] = cbuf[j] - 48 + _7SD_STATE_NUM0_DOTOFF;
				}

				next_state[6] -= _7SD_STATE_NUM0_DOTON;

				if (att < 0.0) next_state[9] = _7SD_STATE_SIGNMINUS;
				else next_state[9] = _7SD_STATE_SIGNPLUS;

				// R
				att = EEAttitude[2].GetVoltage() * 2000.0;
				if (!isfinite( att )) att = 888.8;
				sprintf_s( cbuf, 8, "%5.1f", fabs( att ) );

				for (int i = 13, j = 0; i >= 10; i--, j++)
				{
					if (cbuf[j] == '.') j++;

					if (cbuf[j] == ' ') next_state[i] = _7SD_STATE_NUMOFF_DOTOFF;
					else next_state[i] = cbuf[j] - 48 + _7SD_STATE_NUM0_DOTOFF;
				}

				next_state[11] -= _7SD_STATE_NUM0_DOTON;

				if (att < 0.0) next_state[14] = _7SD_STATE_SIGNMINUS;
				else next_state[14] = _7SD_STATE_SIGNPLUS;
			}
			else if (LED_ParameterSelect[1].IsSet())
			{
				// POSITION X/Y/Z
				char cbuf[8];

				// X
				double pos = EEPosition[0].GetVoltage() * 2000.0;
				if (!isfinite( pos )) pos = 8888.0;
				sprintf_s( cbuf, 8, "%4.0f", fabs( pos ) );

				for (int i = 3, j = 0; i >= 0; i--, j++)
				{
					if (cbuf[j] == ' ') next_state[i] = _7SD_STATE_NUMOFF_DOTOFF;
					else next_state[i] = cbuf[j] - 48 + _7SD_STATE_NUM0_DOTOFF;
				}

				if (pos < 0.0) next_state[4] = _7SD_STATE_SIGNMINUS;
				else next_state[4] = _7SD_STATE_SIGNPLUS;

				// Y
				pos = EEPosition[1].GetVoltage() * 2000.0;
				if (!isfinite( pos )) pos = 8888.0;
				sprintf_s( cbuf, 8, "%4.0f", fabs( pos ) );

				for (int i = 8, j = 0; i >= 5; i--, j++)
				{
					if (cbuf[j] == ' ') next_state[i] = _7SD_STATE_NUMOFF_DOTOFF;
					else next_state[i] = cbuf[j] - 48 + _7SD_STATE_NUM0_DOTOFF;
				}

				if (pos < 0.0) next_state[9] = _7SD_STATE_SIGNMINUS;
				else next_state[9] = _7SD_STATE_SIGNPLUS;

				// Z
				pos = EEPosition[2].GetVoltage() * 2000.0;
				if (!isfinite( pos )) pos = 8888.0;
				sprintf_s( cbuf, 8, "%4.0f", fabs( pos ) );

				for (int i = 13, j = 0; i >= 10; i--, j++)
				{
					if (cbuf[j] == ' ') next_state[i] = _7SD_STATE_NUMOFF_DOTOFF;
					else next_state[i] = cbuf[j] - 48 + _7SD_STATE_NUM0_DOTOFF;
				}

				if (pos < 0.0) next_state[14] = _7SD_STATE_SIGNMINUS;
				else next_state[14] = _7SD_STATE_SIGNPLUS;
			}
			else// if (LED_ParameterSelect[0].IsSet())
			{
				// TEST
				next_state[14] = _7SD_STATE_SIGNPLUS;
				next_state[13] = _7SD_STATE_NUM8_DOTON;
				next_state[12] = _7SD_STATE_NUM8_DOTON;
				next_state[11] = _7SD_STATE_NUM8_DOTON;
				next_state[10] = _7SD_STATE_NUM8_DOTON;
				next_state[9] = _7SD_STATE_SIGNPLUS;
				next_state[8] = _7SD_STATE_NUM8_DOTON;
				next_state[7] = _7SD_STATE_NUM8_DOTON;
				next_state[6] = _7SD_STATE_NUM8_DOTON;
				next_state[5] = _7SD_STATE_NUM8_DOTON;
				next_state[4] = _7SD_STATE_SIGNPLUS;
				next_state[3] = _7SD_STATE_NUM8_DOTON;
				next_state[2] = _7SD_STATE_NUM8_DOTON;
				next_state[1] = _7SD_STATE_NUM8_DOTON;
				next_state[0] = _7SD_STATE_NUM8_DOTON;
			}
		}
		else
		{
			// off
			next_state[14] = _7SD_STATE_SIGNOFF;
			next_state[13] = _7SD_STATE_NUMOFF_DOTOFF;
			next_state[12] = _7SD_STATE_NUMOFF_DOTOFF;
			next_state[11] = _7SD_STATE_NUMOFF_DOTOFF;
			next_state[10] = _7SD_STATE_NUMOFF_DOTOFF;
			next_state[9] = _7SD_STATE_SIGNOFF;
			next_state[8] = _7SD_STATE_NUMOFF_DOTOFF;
			next_state[7] = _7SD_STATE_NUMOFF_DOTOFF;
			next_state[6] = _7SD_STATE_NUMOFF_DOTOFF;
			next_state[5] = _7SD_STATE_NUMOFF_DOTOFF;
			next_state[4] = _7SD_STATE_SIGNOFF;
			next_state[3] = _7SD_STATE_NUMOFF_DOTOFF;
			next_state[2] = _7SD_STATE_NUMOFF_DOTOFF;
			next_state[1] = _7SD_STATE_NUMOFF_DOTOFF;
			next_state[0] = _7SD_STATE_NUMOFF_DOTOFF;
		}
		return;
	}
};
/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/06/03   GLS
2022/07/03   GLS
2022/07/19   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "RCSActivityLights.h"
#include "../Atlantis.h"


constexpr double RCS_LIGHT_MIN_ON_TIME = 0.08 + 0.12;// [s]


namespace dps
{
	RCSActivityLights::RCSActivityLights( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "RCSActivityLights" )
	{
		RollR = 0.0;
		RollL = 0.0;
		PitchU = 0.0;
		PitchD = 0.0;
		YawR = 0.0;
		YawL = 0.0;
		return;
	}

	RCSActivityLights::~RCSActivityLights( void )
	{
		return;
	}

	void RCSActivityLights::OnPostStep( double simt, double simdt, double mjd )
	{
		short UXCMD = ReadCOMPOOL_IS( SCP_UXCMD );
		short UYCMD = ReadCOMPOOL_IS( SCP_UYCMD );
		short UZCMD = ReadCOMPOOL_IS( SCP_UZCMD );

		if (ReadCOMPOOL_SD( SCP_QBAR ) < 50.0)
		{
			// logic for roll and pitch RCS firings
			// roll right
			if (UXCMD > 0)
			{
				if (RCS_CMD_ROLL_RIGHT_LAMP)
				{
					RollR -= simdt;
				}
				else
				{
					RollR = RCS_LIGHT_MIN_ON_TIME;
				}
				RCS_CMD_ROLL_RIGHT_LAMP = true;
			}
			else
			{
				if (RollR > 0.0)
				{
					RollR -= simdt;
					RCS_CMD_ROLL_RIGHT_LAMP = true;
				}
				else
				{
					RCS_CMD_ROLL_RIGHT_LAMP = false;
				}
			}

			// roll left
			if (UXCMD < 0)
			{
				if (RCS_CMD_ROLL_LEFT_LAMP)
				{
					RollL -= simdt;
				}
				else
				{
					RollL = RCS_LIGHT_MIN_ON_TIME;
				}
				RCS_CMD_ROLL_LEFT_LAMP = true;
			}
			else
			{
				if (RollL > 0.0)
				{
					RollL -= simdt;
					RCS_CMD_ROLL_LEFT_LAMP = true;
				}
				else
				{
					RCS_CMD_ROLL_LEFT_LAMP = false;
				}
			}

			// pitch up
			if (UYCMD > 0)
			{
				if (RCS_CMD_PITCH_UP_LAMP)
				{
					PitchU -= simdt;
				}
				else
				{
					PitchU = RCS_LIGHT_MIN_ON_TIME;
				}
				RCS_CMD_PITCH_UP_LAMP = true;
			}
			else
			{
				if (PitchU > 0.0)
				{
					PitchU -= simdt;
					RCS_CMD_PITCH_UP_LAMP = true;
				}
				else
				{
					RCS_CMD_PITCH_UP_LAMP = false;
				}
			}

			// pitch down
			if (UYCMD < 0)
			{
				if (RCS_CMD_PITCH_DOWN_LAMP)
				{
					PitchD -= simdt;
				}
				else
				{
					PitchD = RCS_LIGHT_MIN_ON_TIME;
				}
				RCS_CMD_PITCH_DOWN_LAMP = true;
			}
			else
			{
				if (PitchD > 0.0)
				{
					PitchD -= simdt;
					RCS_CMD_PITCH_DOWN_LAMP = true;
				}
				else
				{
					RCS_CMD_PITCH_DOWN_LAMP = false;
				}
			}
		}
		else
		{
			// logic for yaw RCS firings (roll lights) and for elevon saturation (pitch lights)
			if (abs( UZCMD ) >= 3)
			{
				if (RCS_CMD_ROLL_RIGHT_LAMP)
				{
					RollR -= simdt;
				}
				else
				{
					RollR = RCS_LIGHT_MIN_ON_TIME;
				}
				RCS_CMD_ROLL_LEFT_LAMP = true;
				RCS_CMD_ROLL_RIGHT_LAMP = true;
			}
			else
			{
				if (RollR > 0.0)
				{
					RollR -= simdt;
					RCS_CMD_ROLL_LEFT_LAMP = true;
					RCS_CMD_ROLL_RIGHT_LAMP = true;
				}
				else
				{

					RCS_CMD_ROLL_LEFT_LAMP = false;
					RCS_CMD_ROLL_RIGHT_LAMP = false;
				}
			}

			// TODO elevon saturation logic
			RCS_CMD_PITCH_UP_LAMP = false;
			RCS_CMD_PITCH_DOWN_LAMP = false;
		}

		// yaw right
		if (UZCMD >= 2)
		{
			if (RCS_CMD_YAW_RIGHT_LAMP)
			{
				YawR -= simdt;
			}
			else
			{
				YawR = RCS_LIGHT_MIN_ON_TIME;
			}
			RCS_CMD_YAW_RIGHT_LAMP = true;
		}
		else
		{
			if (YawR > 0.0)
			{
				YawR -= simdt;
				RCS_CMD_YAW_RIGHT_LAMP = true;
			}
			else
			{
				RCS_CMD_YAW_RIGHT_LAMP = false;
			}
		}

		// yaw left
		if (UZCMD <= -2)
		{
			if (RCS_CMD_YAW_LEFT_LAMP)
			{
				YawL -= simdt;
			}
			else
			{
				YawL = RCS_LIGHT_MIN_ON_TIME;
			}
			RCS_CMD_YAW_LEFT_LAMP = true;
		}
		else
		{
			if (YawL > 0.0)
			{
				YawL -= simdt;
				RCS_CMD_YAW_LEFT_LAMP = true;
			}
			else
			{
				RCS_CMD_YAW_LEFT_LAMP = false;
			}
		}

		// output
		if (RCS_CMD_ROLL_RIGHT_LAMP)
		{
			WriteCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA ) | 0x0100 );
			WriteCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA ) | 0x0100 );
		}
		if (RCS_CMD_ROLL_LEFT_LAMP)
		{
			WriteCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA ) | 0x0080 );
			WriteCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA ) | 0x0080 );
		}
		if (RCS_CMD_PITCH_UP_LAMP)
		{
			WriteCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA ) | 0x0800 );
			WriteCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA ) | 0x0800 );
		}
		if (RCS_CMD_PITCH_DOWN_LAMP)
		{
			WriteCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA ) | 0x1000 );
			WriteCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA ) | 0x1000 );
		}
		if (RCS_CMD_YAW_RIGHT_LAMP)
		{
			WriteCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA ) | 0x0400 );
			WriteCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA ) | 0x0400 );
		}
		if (RCS_CMD_YAW_LEFT_LAMP)
		{
			WriteCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA ) | 0x0200 );
			WriteCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA ) | 0x0200 );
		}
		return;
	}

	bool RCSActivityLights::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 304:
			case 305:
			case 602:
			case 603:
				return true;
			default:
				return false;
		}
	}
}
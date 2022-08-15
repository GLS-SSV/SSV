/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2020/08/24   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/08/05   GLS
********************************************/
#include "ElectronicsAssembly1.h"
#include "..\Atlantis.h"
#include "DeployedAssembly.h"
#include <MathSSV.h>


namespace comm
{
	constexpr double SLEW_RATE_SLOW = 0.4;// deg/sec
	constexpr double SLEW_RATE_FAST = 20;// deg/sec

	constexpr double STOW_ALPHA = 124.3;// deg
	constexpr double STOW_BETA = -27.5;// deg

	constexpr double COS_67 = 0.390731128489;
	constexpr double SIN_67 = 0.920504853452;

	constexpr double SCAN_CONE_HALF_ANGLE = 30;// deg


	ElectronicsAssembly1::ElectronicsAssembly1( AtlantisSubsystemDirector* _director, DeployedAssembly* pDeployedAssembly ):AtlantisSubsystem( _director, "ElectronicsAssembly1" )
	{
		this->pDeployedAssembly = pDeployedAssembly;

		ValidDeploy = false;

		timer = -1;
		lastsimt = -1;

		deploy = 1;

		scan = false;
		scan_in = false;
		scan_az = 0;
		scan_el = 90;
		scan_az_delta = 0;
		scan_el_delta = 0;

		target = false;

		AlphaMIPdone = false;
		BetaMIPdone = false;

		tgt_elOLD = 0;
		tgt_azOLD = 0;

		old_alpha = -1;
		old_beta = -1;

		GimbalLockMotorsPower = 0;
		GimbalLockMotorsENA = false;

		omegaalpha = 0;
		omegabeta = 0;

		ZONEI = false;
		ZONEO = false;

		bBOOMST = false;
	}

	ElectronicsAssembly1::~ElectronicsAssembly1()
	{
	}

	void ElectronicsAssembly1::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "A1U_SWITCHES_A", 16 );
		pSlewAzimuth_R.Connect( pBundle, 0 );
		pSlewAzimuth_L.Connect( pBundle, 1 );
		pSlewElevation_Down.Connect( pBundle, 2 );
		pSlewElevation_Up.Connect( pBundle, 3 );
		pSlewRate_Fast.Connect( pBundle, 4 );
		pSearch.Connect( pBundle, 5 );
		pRadarOutput_Low.Connect( pBundle, 6 );
		pRadarOutput_High.Connect( pBundle, 7 );
		//pScanWarnTB->SetInput( pBundle, 8 );
		pTrackTB.Connect( pBundle, 9 );
		pSearchTB.Connect( pBundle, 10 );

		pBundle = BundleManager()->CreateBundle( "A1U_SWITCHES_B", 16 );
		pPower_Off.Connect( pBundle, 5 );
		pPower_On.Connect( pBundle, 6 );

		pBundle = BundleManager()->CreateBundle( "GCIL_EA1", 16 );
		COMON.Connect( pBundle, 0 );
		RADSTB.Connect( pBundle, 1 );
		COMSTB.Connect( pBundle, 2 );
		RADON.Connect( pBundle, 3 );
		GPC.Connect( pBundle, 4 );
		GPCDES.Connect( pBundle, 5 );
		AUTO.Connect( pBundle, 6 );
		MANUAL.Connect( pBundle, 7 );

		pBundle = BundleManager()->CreateBundle( "A2_SWITCHES_DATA", 16 );
		pRange.Connect( pBundle, 3 );
		pRangeRate.Connect( pBundle, 4 );
		pElevation.Connect( pBundle, 5 );
		pAzimuth.Connect( pBundle, 6 );
		pELrate0_20.Connect( pBundle, 7 );
		pELrate0_2.Connect( pBundle, 8 );
		pAZrate0_20.Connect( pBundle, 9 );
		pAZrate0_2.Connect( pBundle, 10 );

		pBundle = BundleManager()->CreateBundle( "KUAntennaControl", 16 );
		BOOM.Connect( pBundle, 1 );// LOCKED
		XMIT.Connect( pBundle, 4 );
		BOOMST.Connect( pBundle, 5 );// Boom Stow Enable I
		AlphaMIP.Connect( pBundle, 7 );
		BetaMIP.Connect( pBundle, 8 );
		GimbalLockMotors.Connect( pBundle, 9 );
		GimbalMotorAlpha.Connect( pBundle, 10 );
		GimbalMotorBeta.Connect( pBundle, 11 );
		AlphaEncoder.Connect( pBundle, 12 );
		BetaEncoder.Connect( pBundle, 13 );

		pBundle = BundleManager()->CreateBundle( "EA1_EA2", 16 );
		KUaz_EA2.Connect( pBundle, 0 );
		KUel_EA2.Connect( pBundle, 1 );
		RADSTB_EA2.Connect( pBundle, 2 );
		RADON_EA2.Connect( pBundle, 3 );
		RADARPOWERLOW_EA2.Connect( pBundle, 4 );
		RADARPOWERMEDIUM_EA2.Connect( pBundle, 5 );
		Range_EA2.Connect( pBundle, 6 );
		RangeRate_EA2.Connect( pBundle, 7 );
		Detect_EA2.Connect( pBundle, 8 );
		TGTaz_EA2.Connect( pBundle, 9 );
		TGTel_EA2.Connect( pBundle, 10 );
		return;
	}

	bool ElectronicsAssembly1::OnParseLine( const char* line )
	{
		if (!_strnicmp( line, "TIMER", 5 ))
		{
			sscanf_s( line + 5, "%lf", &timer );
			return true;
		}
		else if (!_strnicmp( line, "VALIDDEPLOY", 11 ))
		{
			int tmp;
			sscanf_s( line + 11, "%d", &tmp );
			ValidDeploy = (tmp != 0);
			return true;
		}
		else if (!_strnicmp( line, "DEPLOY", 6 ))
		{
			sscanf_s( line + 6, "%d", &deploy );
			return true;
		}
		return false;
	}

	void ElectronicsAssembly1::OnSaveState( FILEHANDLE scn ) const
	{
		if (timer != -1) oapiWriteScenario_float( scn, "TIMER", timer - simt );
		if (ValidDeploy) oapiWriteScenario_int( scn, "VALIDDEPLOY", (int)ValidDeploy );
		if (deploy != 1) oapiWriteScenario_int( scn, "DEPLOY", deploy );
		return;
	}

	void ElectronicsAssembly1::OnPostStep( double simt, double simdt, double mjd )
	{
		if (pPower_Off.IsSet())
		{
			timer = -1;
			ValidDeploy = false;
			AlphaMIPdone = false;
			BetaMIPdone = false;
			omegaalpha = 0;
			omegabeta = 0;
			BOOMST.ResetLine();
			bBOOMST = false;
			GimbalLockMotors.ResetLine();

			KUaz_EA2.ResetLine();
			KUel_EA2.ResetLine();
			RADSTB_EA2.ResetLine();
			RADON_EA2.ResetLine();
			RADARPOWERLOW_EA2.ResetLine();
			RADARPOWERMEDIUM_EA2.ResetLine();

			pTrackTB.ResetLine();
			pSearchTB.ResetLine();
			return;
		}

		double range = 0;
		double range_rate = 0;

		this->simt = simt;
		dt = simdt;

		// read encoders
		cur_alpha = AlphaEncoder.GetVoltage();
		cur_beta = BetaEncoder.GetVoltage();
		GimbalToShuttle( cur_alpha, cur_beta, cur_el, cur_az );

		// "Configure routine"
		if (COMON)
		{
			// comm
			if (BOOM)// check for stow
			{
				Procedure_Deploy();
			}
			else if (XMIT)
			{
				if (!ValidDeploy)// check for deploy
				{
					Procedure_Deploy();
				}
				else
				{
					// TODO comm stuff
					if (GPCDES)
					{
						// gpc desig
						Procedure_Point();
					}
					else if (GPC)
					{
						// gpc
						Procedure_Point();
						Procedure_Scan();
						Procedure_Track();
					}
					else if (AUTO)
					{
						// auto
						Procedure_Slew( pSlewRate_Fast, pSlewAzimuth_R, pSlewAzimuth_L, pSlewElevation_Up, pSlewElevation_Down );
						//Procedure_Scan();
						//Procedure_Track();
					}
					else
					{
						// man slew
						Procedure_Slew( pSlewRate_Fast, pSlewAzimuth_R, pSlewAzimuth_L, pSlewElevation_Up, pSlewElevation_Down );
					}
				}
			}
			else
			{
				if (0)//(STEST)
				{
					Procedure_Self_test();
				}
				else Procedure_Idle();
			}
		}
		else if (RADON)
		{
			// radar
			if (BOOM)// check for stow
			{
				Procedure_Deploy();
			}
			else if (XMIT)
			{
				if (!ValidDeploy)// check for deploy
				{
					Procedure_Deploy();
				}
				else
				{
					if (0)//(STEST)
					{
						Procedure_Self_test();
					}
					else
					{
						// radar stuff
						if (GPCDES)
						{
							// gpc desig
							Procedure_Point();
							target = false;
						}
						else if (GPC)
						{
							// gpc
							Procedure_Point();
							Procedure_Scan();
							Procedure_Track();
						}
						else if (AUTO)
						{
							// auto
							if (!scan && !target && !pSearch) Procedure_Slew( pSlewRate_Fast, pSlewAzimuth_R, pSlewAzimuth_L, pSlewElevation_Up, pSlewElevation_Down );
							else if (!target && (pSearch || scan)) Procedure_Scan();
							else if (target) Procedure_Track();
						}
						else
						{
							// man slew
							Procedure_Slew( pSlewRate_Fast, pSlewAzimuth_R, pSlewAzimuth_L, pSlewElevation_Up, pSlewElevation_Down );
							target = false;
						}

						range = Range_EA2.GetVoltage();
						range_rate = RangeRate_EA2.GetVoltage();
					}
				}
			}
			else
			{
				if (0)//(STEST)
				{
					Procedure_Self_test();
				}
				else Procedure_Idle();
			}
		}
		else if (COMSTB && RADSTB)
		{
			// standby
			if (BOOM)// check for stow
			{
				Procedure_Deploy();
			}
			else Procedure_Idle();
		}
		else Procedure_Idle();

		lastsimt = simt;

		PanelOutput( range, range_rate );

		// output to DA
		GimbalLockMotors.SetLine( (float)GimbalLockMotorsPower * (int)GimbalLockMotorsENA );
		GimbalMotorAlpha.SetLine( (float)omegaalpha );
		GimbalMotorBeta.SetLine( (float)omegabeta );

		// output to EA-2
		KUaz_EA2.SetLine( (float)cur_az );
		KUel_EA2.SetLine( (float)cur_el );
		RADSTB_EA2.SetLine( RADSTB.GetVoltage() );
		RADON_EA2.SetLine( RADON.GetVoltage() );
		RADARPOWERLOW_EA2.SetLine( pRadarOutput_Low.GetVoltage() );
		RADARPOWERMEDIUM_EA2.SetLine( 5.0f * (int)(!pRadarOutput_Low.IsSet() && !pRadarOutput_High.IsSet()) );
		return;
	}

	void ElectronicsAssembly1::PanelOutput( double r, double rr )
	{
		// output to panel A1U
		pTrackTB.SetLine( 5.0f * (int)target );
		pSearchTB.SetLine( 5.0f * (int)scan );

		// output to panel A2
		pElevation.SetLine( (float)(cur_el * 0.01) );
		pAzimuth.SetLine( (float)(cur_az * 0.01) );

		if (target)
		{
			// radar output
			pRange.SetLine( (float)(r * 0.0005) );
			pRangeRate.SetLine( (float)(rr * 0.0005) );
			// M1 output
			double el1 = TGTel_EA2.GetVoltage() * RAD * 1000;
			double az1 = TGTaz_EA2.GetVoltage() * RAD * 1000;
			double el = (el1 - tgt_elOLD) / dt;
			double az = (az1 - tgt_azOLD) / dt;
			tgt_elOLD = el1;
			tgt_azOLD = az1;
			pELrate0_20.SetLine( (float)range( -5, el * 0.25, 5 ) );
			pELrate0_2.SetLine( (float)range( -5, el * 2.5, 5 ) );
			pAZrate0_20.SetLine( (float)range( -5, az * 0.25, 5 ) );
			pAZrate0_2.SetLine( (float)range( -5, az * 2.5, 5 ) );
		}
		else
		{
			pRange.ResetLine();
			pRangeRate.ResetLine();
			pELrate0_20.ResetLine();
			pELrate0_2.ResetLine();
			pAZrate0_20.ResetLine();
			pAZrate0_2.ResetLine();
		}
		return;
	}

	void ElectronicsAssembly1::ShuttleToGimbal( double _EL, double _AZ, double &_alpha, double &_beta )
	{
		AngleTransform( _alpha, _beta, _EL, _AZ, -SIN_67 );
		if (_alpha > 154) _alpha -= 360;
		return;
	}

	void ElectronicsAssembly1::GimbalToShuttle( double _alpha, double _beta, double &_EL, double &_AZ )
	{
		if (_alpha <= -206) _alpha += 360;
		AngleTransform( _AZ, _EL, _beta, _alpha, SIN_67 );
		return;
	}

	void ElectronicsAssembly1::AngleTransform( double &A, double &B, double C, double D, double K )
	{
		double SIN_C = sin( C * RAD );
		double COS_C = cos( C * RAD );
		double SIN_D = sin( D * RAD );
		double COS_D = cos( D * RAD );

		B = asin( -COS_67 * SIN_C - K * SIN_D * COS_C );
		A = asin( (-COS_67 * SIN_D * COS_C + K * SIN_C) / cos( B ) ) * DEG;
		B *= DEG;

		// correction to gimbal equations
		if (sign( COS_C * COS_D ) < 0)
		{
			if (A < 0) A = -180 - A;
			else if (A > 0) A = 180 - A;
		}
		return;
	}

	void ElectronicsAssembly1::PositionLoop( double des_alpha, double des_beta, bool man )
	{
		omegaalpha = des_alpha - cur_alpha;
		omegabeta = des_beta - cur_beta;

		if (man)
		{
			if ((fabs( omegaalpha ) < 3) && (fabs( omegabeta ) < 3))
			{
				ZONEO = true;
				if ((fabs( omegaalpha ) < 0.3) && (fabs( omegabeta ) < 0.3)) ZONEI = true;
				else ZONEI = false;
			}
			else
			{
				ZONEO = false;
				ZONEI = false;
			}

			omegaalpha /= dt;
			omegabeta /= dt;

			// limit output
			if (omegaalpha > 56.25) omegaalpha = 56.25;
			else if (omegaalpha < -56.25) omegaalpha = -56.25;
			if (omegabeta > 56.25) omegabeta = 56.25;
			else if (omegabeta < -56.25) omegabeta = -56.25;
			return;
		}

		if ((fabs( omegaalpha ) < 3) && (fabs( omegabeta ) < 3))
		{
			ZONEO = true;
			if ((fabs( omegaalpha ) < 0.3) && (fabs( omegabeta ) < 0.3))
			{
				ZONEI = true;
				// stop drive?
				omegaalpha = 0;
				omegabeta = 0;
			}
			else ZONEI = false;
		}
		else
		{
			ZONEO = false;
			ZONEI = false;
		}

		// limit output
		if (omegaalpha > 20) omegaalpha = 20;
		else if (omegaalpha < -20) omegaalpha = -20;
		if (omegabeta > 20) omegabeta = 20;
		else if (omegabeta < -20) omegabeta = -20;
		return;
	}


	void ElectronicsAssembly1::Procedure_Initialize( void )
	{
		return;
	}

	void ElectronicsAssembly1::Procedure_Procedure_termination( void )
	{
		return;
	}

	/*void ElectronicsAssembly1::Procedure_Recover( void )
	{
		return;
	}*/

	void ElectronicsAssembly1::Procedure_Idle( void )
	{
		return;
	}

	void ElectronicsAssembly1::Procedure_Deploy( void )
	{
		if ((COMON || RADON) && !BOOM && XMIT && !ValidDeploy)
		{
			// deploy
			if (deploy == 1)
			{
				if (RetractLockingPins()) deploy = 2;
			}
			else if (deploy == 2)
			{
				if (InitializeEncoders()) deploy = 3;
			}
			else if (deploy == 3)
			{
				if (DriveToZenith()) deploy = 1;
			}
		}
		else if ((COMON || RADON || COMSTB || RADSTB) && BOOM)
		{
			// stow
			if ((deploy == 1) && (!bBOOMST))
			{
				if (DriveToStow()) deploy = 2;
			}
			else if (deploy == 2)
			{
				if (InsertLockingPins()) deploy = 3;
			}
			else if (deploy == 3)
			{
				if (WiggleTest())
				{
					if (WiggleTestPass)
					{
						BOOMST.SetLine();
						bBOOMST = true;
						deploy = 1;
					}
					else deploy = 4;
				}
			}
			else if (deploy == 4)
			{
				if (RetractLockingPins()) deploy = 1;
			}
		}
		return;
	}

	void ElectronicsAssembly1::Procedure_Point( void )
	{
		return;
	}

	void ElectronicsAssembly1::Procedure_Slew( bool fast, bool right, bool left, bool up, bool down )
	{
		double dP = ((SLEW_RATE_SLOW * (int)!fast) + (SLEW_RATE_FAST * (int)fast)) * dt;
		double des_az = cur_az;
		double des_el = cur_el;
		double des_alpha;
		double des_beta;

		if (right)
		{
			des_az += dP;
			if (des_az > 180) des_az = 180;
		}
		else if (left)
		{
			des_az -= dP;
			if (des_az < -180) des_az = -180;
		}

		if (up)
		{
			des_el += dP;
			if (des_el > 90) des_el = 90;
		}
		else if (down)
		{
			des_el -= dP;
			if (des_el < -90) des_el = -90;
		}

		ShuttleToGimbal( des_el, des_az, des_alpha, des_beta );
		PositionLoop( des_alpha, des_beta, true );
		return;
	}

	void ElectronicsAssembly1::Procedure_Scan( void )// very, very simplified and radar only
	{
		double des_alpha;
		double des_beta;
		double des_az;
		double des_el;

		if (scan)
		{
			if (Detect_EA2)
			{
				target = true;
				scan = false;
			}
			else
			{
				scan_az += 35 * dt;
				if (scan_az > 180) scan_az -= 360;

				if (!scan_in)
				{
					scan_el -= 1 * dt;
					if (scan_el < (90 - SCAN_CONE_HALF_ANGLE))
					{
						scan_el = (90 - SCAN_CONE_HALF_ANGLE);
						scan_in = true;
					}
				}
				else
				{
					scan_el += 1 * dt;
					if (scan_el > 90)
					{
						scan_el = 90;
						scan = false;
					}
				}
			}
		}
		else
		{
			// setup
			scan = true;
			scan_in = false;
			scan_az = 0;
			scan_el = 90;
			scan_az_delta = cur_az * RAD;
			scan_el_delta = (cur_el - 90) * RAD;
		}

		// convert reference
		VECTOR3 desA = _V( cos( scan_el * RAD ) * sin( -scan_az * RAD ), cos( scan_el * RAD ) * cos( scan_az * RAD ), sin( scan_el * RAD ) );
		VECTOR3 desB;
		VECTOR3 ang = _V( scan_el_delta, 0, scan_az_delta );
		RotateVector( desA, ang, desB );
		des_el = asin( desB.z ) * DEG;
		des_az = atan2( desB.x, desB.y ) * DEG;

		ShuttleToGimbal( des_el, des_az, des_alpha, des_beta );

		omegaalpha = (des_alpha - cur_alpha) / dt;
		omegabeta = (des_beta - cur_beta) / dt;
		// limit output
		if (omegaalpha > 40) omegaalpha = 40;
		else if (omegaalpha < -40) omegaalpha = -40;
		if (omegabeta > 40) omegabeta = 40;
		else if (omegabeta < -40) omegabeta = -40;
		return;
	}

	void ElectronicsAssembly1::Procedure_Track( void )
	{
		if (!Detect_EA2)
		{
			target = false;
		}
		else
		{
			// track
			double des_alpha;
			double des_beta;
			ShuttleToGimbal( TGTel_EA2.GetVoltage(), TGTaz_EA2.GetVoltage(), des_alpha, des_beta );

			omegaalpha = (des_alpha - cur_alpha) / dt;
			omegabeta = (des_beta - cur_beta) / dt;
			// limit output
			if (omegaalpha > 20) omegaalpha = 20;
			else if (omegaalpha < -20) omegaalpha = -20;
			if (omegabeta > 20) omegabeta = 20;
			else if (omegabeta < -20) omegabeta = -20;
		}
		return;
	}

	void ElectronicsAssembly1::Procedure_Self_test( void )
	{
		return;
	}


	bool ElectronicsAssembly1::RetractLockingPins( void )
	{
		/*
		A. Command gimbal motors off
		B. Command the gimbal lock motor, when activated, to retract the locking pins
		C. Set LOCKED (BOOMST) false
		D. After a timeout of 800 ms, command lock motor on
		E. After a further timeout of 30 seconds, command lock motor off
		F. Command gimbal motors on
		*/
		if (timer == -1)
		{
			// A, B, C
			GimbalLockMotorsPower = -28;
			BOOMST.ResetLine();
			bBOOMST = false;
			timer = simt;
			return false;
		}
		else if ((timer + 0.8 <= simt) && (timer + 0.8 > lastsimt))
		{
			// D
			GimbalLockMotorsENA = true;
			return false;
		}
		else if ((timer + 30 <= simt) && (timer + 30 > lastsimt))
		{
			// E, F
			GimbalLockMotorsENA = false;
			timer = -1;// reset timer
			return true;
		}
		return false;
	}

	bool ElectronicsAssembly1::InsertLockingPins( void )
	{
		/*
		A. Command the gimbal lock motor, when activated, to drive the locking pins into the locked position
		B. After a timeout of 4 seconds, command lock motor on
		C. After a timeout of 30 seconds, command lock motor off
		*/
		if (timer == -1)
		{
			// A
			GimbalLockMotorsPower = 28;
			timer = simt;
			return false;
		}
		else if ((timer + 4 <= simt) && (timer + 4 > lastsimt))
		{
			// B
			GimbalLockMotorsENA = true;
			return false;
		}
		else if ((timer + 30 <= simt) && (timer + 30 > lastsimt))
		{
			// C
			GimbalLockMotorsENA = false;
			timer = -1;// reset timer
			return true;
		}
		return false;
	}

	bool ElectronicsAssembly1::InitializeEncoders( void )
	{
		if (!BetaMIPdone)
		{
			if (timer == -1)
			{
				timer = simt;
				omegaalpha = 0;
				omegabeta = 20;
			}
			else if ((timer + 20 <= simt) || BetaMIP)
			{
				BetaMIPdone = true;
				timer = -1;// reset timer
			}
			else if (GimbalStopCheck())
			{
				omegaalpha = 0;
				omegabeta = -20;
			}
			return false;
		}
		else if (!AlphaMIPdone)
		{
			if (timer == -1)
			{
				timer = simt;
				omegaalpha = 20;
				omegabeta = 0;
			}
			else if ((timer + 40 <= simt) || AlphaMIP)
			{
				AlphaMIPdone = true;
				timer = -1;// reset timer
				return true;
			}
			else if (GimbalStopCheck())
			{
				omegaalpha = -20;
				omegabeta = 0;
			}
			return false;
		}
		return true;
	}

	bool ElectronicsAssembly1::DriveToZenith( void )
	{
		if (timer == -1)
		{
			timer = simt;
		}
		else if (ZONEI || (timer + 22 <= simt))
		{
			timer = -1;// reset timer
			ValidDeploy = true;
			return true;
		}

		PositionLoop( 0, 0 );
		return false;
	}

	bool ElectronicsAssembly1::DriveToStow( void )
	{
		if (timer == -1)
		{
			timer = simt;
		}
		else if (ZONEI || (timer + 22 <= simt))
		{
			timer = -1;// reset timer
			ValidDeploy = false;
			return true;
		}

		PositionLoop( STOW_ALPHA, STOW_BETA );
		return false;
	}

	bool ElectronicsAssembly1::WiggleTest( void )
	{
		if (timer == -1)
		{
			timer = simt;
			WiggleTestPass = false;
			WiggleTestAlpha = cur_alpha;
			WiggleTestBeta = cur_beta;
			omegaalpha = 20;
			omegabeta = 20;
			return false;
		}
		else if ((timer + 1 <= simt) && (timer + 1 > lastsimt))
		{
			WiggleTestPass = Eq( WiggleTestAlpha, cur_alpha, 0.704 ) && Eq( WiggleTestBeta, cur_beta, 0.704 );
			omegaalpha = -20;
			omegabeta = -20;
		}
		else if ((timer + 2 <= simt) && (timer + 2 > lastsimt))
		{
			WiggleTestPass = WiggleTestPass && Eq( WiggleTestAlpha, cur_alpha, 0.704 ) && Eq( WiggleTestBeta, cur_beta, 0.704 );
			omegaalpha = 0;
			omegabeta = 0;
			timer = -1;// reset timer
			return true;
		}
		return false;
	}

	bool ElectronicsAssembly1::GimbalStopCheck( void )
	{
		bool res = true;
		if ((old_alpha != cur_alpha) || (old_beta != cur_beta)) res = false;
		old_alpha = cur_alpha;
		old_beta = cur_beta;
		return res;
	}
};
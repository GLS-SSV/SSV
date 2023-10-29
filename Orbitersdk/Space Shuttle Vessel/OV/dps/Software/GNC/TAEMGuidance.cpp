/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/03/24   GLS
2022/03/29   GLS
2022/04/01   GLS
2022/04/20   GLS
2022/04/26   GLS
2022/07/24   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/12/01   indy91
2023/06/14   GLS
2023/10/29   GLS
********************************************/
#include "TAEMGuidance.h"
#include <MathSSV.h>
#include <EngConst.h>


namespace dps
{
	/////// TAEM (from 80-FM-29, JSC-16522) ///////

	// limit on DSBI
	constexpr double DSBIL = 20.0;// [deg]

	// gain on QBERR integral in computing speedbrake command
	constexpr double GSBI = 0.1;// [deg/psf^-1]

	// maximum EOW error for speedbrakes out
	constexpr double DEMXSB = 10000.0;// [ft]


	double RES180( double v )
	{
		while (v > 180.0) v -= 360.0;
		while (v <= -180.0) v += 360.0;
		return v;
	}

	TAEMGuidance::TAEMGuidance( SimpleGPCSystem* _gpc ):SimpleGPCSoftware( _gpc, "TAEMGuidance" )
	{
		IRESET = 1;
		NZC = 0.0;
		PHI0 = 0.0;
		PHILIM = 0.0;
		DNZUL = 0.0;
		DNZLL = 0.0;
		QBARF = 0.0;
		QBD = 0.0;
		DSBI = 0.0;
		DSBC = 0.0;

		step = 0.96;

		ISR = ReadCOMPOOL_SS( SCP_RFTC );

		// I-LOADs init
		PHILMC = 100.0;
		return;
	}

	TAEMGuidance::~TAEMGuidance( void )
	{
		return;
	}

	bool TAEMGuidance::OnParseLine( const char* keyword, const char* value )
	{
		if (!_strnicmp( keyword, "IRESET", 6 ))
		{
			unsigned int tmp = 0;
			sscanf_s( value, "%u", &tmp );
			if (tmp <= 1) IRESET = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "NZC", 3 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			NZC = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "PHILIM", 6 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			PHILIM = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "DNZUL", 5 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			DNZUL = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "DNZLL", 5 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			DNZLL = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "QBARF", 5 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			QBARF = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "QBD", 3 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			QBD = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "DSBI", 4 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			DSBI = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "DSBC", 4 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			DSBC = tmp;
			return true;
		}
		else return false;
	}

	void TAEMGuidance::OnSaveState( FILEHANDLE scn ) const
	{
		oapiWriteScenario_int( scn, "IRESET", IRESET );
		oapiWriteScenario_float( scn, "NZC", NZC );
		oapiWriteScenario_float( scn, "PHI0", PHI0 );
		oapiWriteScenario_float( scn, "PHILIM", PHILIM );
		oapiWriteScenario_float( scn, "DNZUL", DNZUL );
		oapiWriteScenario_float( scn, "DNZLL", DNZLL );
		oapiWriteScenario_float( scn, "QBARF", QBARF );
		oapiWriteScenario_float( scn, "QBD", QBD );
		oapiWriteScenario_float( scn, "DSBI", DSBI );
		oapiWriteScenario_float( scn, "DSBC", DSBC );
		return;
	}

	void TAEMGuidance::ReadILOADs( const std::map<std::string,std::string>& ILOADs )
	{
		GetValILOAD( "PHILMC", ILOADs, PHILMC );
		return;
	}

	void TAEMGuidance::OnPreStep( double simt, double simdt, double mjd )
	{
		if (ReadCOMPOOL_IS( SCP_TG_END ) == 1) return;

		step += simdt;
		if (step < 0.96) return;

		// read inputs
		H = ReadCOMPOOL_SD( SCP_ALT_WHEELS );
		HDOT = ReadCOMPOOL_SS( SCP_H_DOT_ELLIPSOID );
		IGS = ReadCOMPOOL_IS( SCP_IGS );
		RWID = ReadCOMPOOL_IS( SCP_RW_ID );
		RWID0 = ReadCOMPOOL_IS( SCP_RWID0 );
		X = ReadCOMPOOL_VS( SCP_POSN_WRT_RW, 1, 3 );
		Y = ReadCOMPOOL_VS( SCP_POSN_WRT_RW, 2, 3 );
		XDOT = ReadCOMPOOL_VS( SCP_VEL_WRT_RW, 1, 3 );
		YDOT = ReadCOMPOOL_VS( SCP_VEL_WRT_RW, 2, 3 );
		COSPHI = ReadCOMPOOL_SS( SCP_COSPHI );
		PSD = ReadCOMPOOL_SS( SCP_COURSE_WRT_RW );
		GAMMA = ReadCOMPOOL_SS( SCP_FLT_PATH_ANG );
		QBAR = ReadCOMPOOL_SS( SCP_QBAR );
		WEIGHT = ReadCOMPOOL_SS( SCP_WEIGHT );
		MACH = ReadCOMPOOL_SS( SCP_M );
		V = ReadCOMPOOL_SS( SCP_REL_VEL_MAG );
		VH = ReadCOMPOOL_SS( SCP_V_GROUNDSPEED );
		GAMSGS = ReadCOMPOOL_VS( SCP_GAMMA_REF_1, IGS, 2 );

		TGEXEC( step/*simdt*/ );

		// write outputs
		WriteCOMPOOL_IS( SCP_RWID0, RWID0 );
		WriteCOMPOOL_SS( SCP_DSBC_AT, static_cast<float>(DSBC_AT) );
		WriteCOMPOOL_SS( SCP_NZC, static_cast<float>(NZC) );
		WriteCOMPOOL_SS( SCP_PHIC_AT, static_cast<float>(PHIC_AT) );
		WriteCOMPOOL_SS( SCP_DPSAC, static_cast<float>(DPSAC) );
		WriteCOMPOOL_SS( SCP_EOW, static_cast<float>(EOW) );
		WriteCOMPOOL_SS( SCP_EN, static_cast<float>(EN) );
		WriteCOMPOOL_SS( SCP_ES, static_cast<float>(ES) );
		WriteCOMPOOL_SS( SCP_EMEP, static_cast<float>(EMEP) );
		WriteCOMPOOL_SS( SCP_EMOH, static_cast<float>(EMOH) );

		step = 0.0;
		return;
	}

	bool TAEMGuidance::OnMajorModeChange( unsigned int newMajorMode )
	{
		if (newMajorMode == 305) return true;
		else return false;
	}

	void TAEMGuidance::TGEXEC( double dt )
	{
		if ((IRESET == 1) || (RWID != RWID0)) TGINIT();
		TGXHAC();
		GTP();
		TGCOMP( dt );
		TGTRAN();
		TGNZC( dt );
		TGSBC( dt );
		TGPHIC( dt );
		return;
	}

	void TAEMGuidance::TGINIT( void )
	{
		//if (IRESET == 1) RWID0 = RWID;
		ISR = ReadCOMPOOL_SS( SCP_RFTC )/* / DTG*/;// HACK subtract dt in TGPHIC
		WriteCOMPOOL_SS( SCP_RF, ReadCOMPOOL_SS( SCP_RF0 ) );
		DSBI = 0.0;
		//OHALRT = 0;
		PHILIM = ReadCOMPOOL_SS( SCP_PHILM1 );
		DNZUL = ReadCOMPOOL_SS( SCP_DNZUC1 );
		DNZLL = ReadCOMPOOL_SS( SCP_DNZLC1 );
		QBARF = QBAR;
		QBD = 0.0;
		WriteCOMPOOL_IS( SCP_IPHASE, 1 );
		WriteCOMPOOL_SS( SCP_TG_END, 0 );
		IRESET = 0;

		IGS = 1;
		if (WEIGHT > ReadCOMPOOL_SS( SCP_WT_GS1 )) IGS = 2;
		WriteCOMPOOL_IS( SCP_IGS, IGS );

		WriteCOMPOOL_SS( SCP_RTURN, /*ReadCOMPOOL_SS( SCP_RTURN );*/ReadCOMPOOL_SS( SCP_RF0 ) );// TODO get R_NEP from ENT UPP
		return;
	}

	void TAEMGuidance::TGXHAC( void )
	{
		float XFTC = 0.0f;
		float XMEP = 0.0f;

		/*if (V <= VTOGL)
		{
			if (OVHD == 1) OVHD = 0;
			else
			{
				OVHD = 1;
				YSGN = -sign( Y );
			}
			PSHA = ReadCOMPOOL_SS( SCP_PSHARS );
			VTOGL = 0.0;
		}*/

		if (RWID != RWID0)
		{
			WriteCOMPOOL_SS( SCP_PSHA, ReadCOMPOOL_SS( SCP_PSHARS ) );
			if (ReadCOMPOOL_IS( SCP_OVHD ) == 1) WriteCOMPOOL_SS( SCP_YSGNP, static_cast<float>(-sign( Y )) );
		}

		RWID0 = RWID;

		/*if ((OHALRT == 1) && (ORAHAC[RWID - 1] == 0) && (OVHD == 1))
		{
			OVHD = 0;
			PSHA = ReadCOMPOOL_SS( SCP_PSHARS );
		}*/

		if ((ReadCOMPOOL_IS( SCP_OVHD ) == 0) && (ReadCOMPOOL_IS( SCP_IPHASE ) < 2)) WriteCOMPOOL_SS( SCP_YSGNP, static_cast<float>(sign( Y )) );

		unsigned short IGI;
		if (ReadCOMPOOL_IS( SCP_GI_CHANGE ) == 1) IGI = 2;
		else IGI = 1;
		WriteCOMPOOL_IS( SCP_IGI, IGI );

		XFTC = static_cast<float>(ReadCOMPOOL_VS( SCP_XA, IGI, 2 ) + (ReadCOMPOOL_VS( SCP_HFTC, IGS, 2 ) / ReadCOMPOOL_VS( SCP_TGGS, IGS, 2 )) );
		XALI = ReadCOMPOOL_VS( SCP_XA, IGI, 2 ) + (ReadCOMPOOL_VS( SCP_HALI, IGS, 2 ) / ReadCOMPOOL_VS( SCP_TGGS, IGS, 2 ));
		XMEP = static_cast<float>(ReadCOMPOOL_VS( SCP_XA, IGI, 2 ) + (ReadCOMPOOL_VS( SCP_HMEP, IGS, 2 ) / ReadCOMPOOL_VS( SCP_TGGS, IGS, 2 )) );

		WriteCOMPOOL_SS( SCP_XHAC, XFTC );
		if (ReadCOMPOOL_IS( SCP_ENT_PT_SW ) == 1) WriteCOMPOOL_SS( SCP_XHAC, XMEP );

		RPRED3 = -ReadCOMPOOL_SS( SCP_XHAC ) + ReadCOMPOOL_SS( SCP_DR3 );

		WriteCOMPOOL_IS( SCP_NEP_FB, ReadCOMPOOL_IS( SCP_ENT_PT_SW ) );
		return;
	}

	void TAEMGuidance::GTP( void )
	{
		double SIGNY = 0.0;// sign of vehicle Y position in runway coordinates [1]
		double RTAN = 0.0;// straight line distance to WP1 [ft]
		double PST = 0.0;// heading to WP1 [deg]
		double PSHAN = 0.0;// new PSHA [deg]
		double PHAVG = 0.0;// average PHI turning to WP1 [deg]
		double RTAC = 0.0;// acquisition turn radius [ft]
		double ARCAC = 0.0;// acquisition turn arc length [ft]
		double A = 0.0;
		double B = 0.0;
		double RC = 0.0;// range from end of acquisition turn to WP1 [ft]
		double PSC = 0.0;// heading to HAC center [deg]

		XCIR = ReadCOMPOOL_SS( SCP_XHAC ) - X;
		/*if ((ReadCOMPOOL_IS( SCP_IPHASE ) == 3) && (XCIR < DR4))
		{
			RPRED = sqrt( (X * X) + (Y * Y) );
			return;
		}*/

		// eq set 1
		SIGNY = sign( Y );
		YCIR = (ReadCOMPOOL_SS( SCP_YSGNP ) * ReadCOMPOOL_SS( SCP_RF )) - Y;
		RCIR = sqrt( (XCIR * XCIR) + (YCIR * YCIR) );
		if (RCIR > ReadCOMPOOL_SS( SCP_RTURN ))
		{
			RTAN = sqrt( (RCIR * RCIR) - (ReadCOMPOOL_SS( SCP_RTURN ) * ReadCOMPOOL_SS( SCP_RTURN )) );
		}
		else RTAN = 0.0;

		// eq set 2
		PSC = atan2( YCIR, XCIR ) * DEG;
		PST = PSC - (ReadCOMPOOL_SS( SCP_YSGNP ) * atan2( ReadCOMPOOL_SS( SCP_RTURN ), RTAN ) * DEG);
		PST = RES180( PST );
		DPSAC = RES180( PST - PSD );
		WriteCOMPOOL_SS( SCP_MEDS_DPSAC, static_cast<float>(fabs( DPSAC )) );
		PSHAN = -PST * ReadCOMPOOL_SS( SCP_YSGNP );
		if (((ReadCOMPOOL_SS( SCP_PSHA ) > (ReadCOMPOOL_SS( SCP_PSHARS ) + 1.0)) || (PSHAN < -1.0) || (ReadCOMPOOL_SS( SCP_YSGNP ) != SIGNY)) && (ReadCOMPOOL_SS( SCP_PSHA ) > 90.0)) PSHAN += 360.0;
		WriteCOMPOOL_SS( SCP_PSHA, static_cast<float>(PSHAN) );
		WriteCOMPOOL_SS( SCP_RTURN, ReadCOMPOOL_SS( SCP_RF ) + ((ReadCOMPOOL_SS( SCP_R1 ) + (ReadCOMPOOL_SS( SCP_R2 ) * ReadCOMPOOL_SS( SCP_PSHA ))) * ReadCOMPOOL_SS( SCP_PSHA ) ));
		RPRED2 = ((ReadCOMPOOL_SS( SCP_RF ) + ((0.5 * ReadCOMPOOL_SS( SCP_R1 )) + (0.333333 * ReadCOMPOOL_SS( SCP_R2 ) * ReadCOMPOOL_SS( SCP_PSHA ))) * ReadCOMPOOL_SS( SCP_PSHA )) * ReadCOMPOOL_SS( SCP_PSHA ) * RAD/*DTR*/) - ReadCOMPOOL_SS( SCP_XHAC );

		// delayed this check so PSC and DPSAC is calculated in IPHASE = 3
		if ((ReadCOMPOOL_IS( SCP_IPHASE ) == 3) && (XCIR < ReadCOMPOOL_SS( SCP_DR4 )))
		{
			WriteCOMPOOL_SS( SCP_RPRED, static_cast<float>(sqrt( (X * X) + (Y * Y) )) );
			return;
		}

		if (ReadCOMPOOL_IS( SCP_IPHASE ) < 2)
		{
			// eq set 3
			PHAVG = ReadCOMPOOL_SS( SCP_PHAVGC ) - ReadCOMPOOL_SS( SCP_PHAVGS ) * MACH;
			PHAVG = range( ReadCOMPOOL_SS( SCP_PHAVGLL ), PHAVG, ReadCOMPOOL_SS( SCP_PHAVGUL ) );
			RTAC = (V * VH) / (G * MPS2FPS * tan( PHAVG * RAD/*DTR*/ ) );
			ARCAC = RTAC * fabs( DPSAC ) * RAD/*DTR*/;

			// eq set 4
			A = RTAC * (1.0 - cos( DPSAC * RAD ));
			B = RTAN - (RTAC * fabs( sin( DPSAC * RAD ) ));
			RC = sqrt( (A * A) + (B * B) );
			RTAN = ARCAC + RC;
		}

		WriteCOMPOOL_SS( SCP_RPRED, static_cast<float>(RPRED2 + RTAN) );

		WriteCOMPOOL_SS( SCP_RTAN, static_cast<float>(RTAN) );
		return;
	}

	void TAEMGuidance::TGCOMP( double dt )
	{
		// eq set 1
		DRPRED = ReadCOMPOOL_SS( SCP_RPRED ) + XALI;
		EOW = H + ((V * V) / (2.0 * G * MPS2FPS));

		// eq set 2
		if (DRPRED < ReadCOMPOOL_VS( SCP_EOW_SPT, IGS, 2 )) IEL = 2;
		else IEL = 1;

		EN = ReadCOMPOOL_MS( SCP_EN_C1, IGS, IEL, 2, 2 ) + (DRPRED * ReadCOMPOOL_MS( SCP_EN_C2, IGS, IEL, 2, 2 )) - range( 0.0, ReadCOMPOOL_MS( SCP_EN_C2, IGS, 1, 2, 2 ) * (RPRED2 - ReadCOMPOOL_SS( SCP_R2MAX )), ReadCOMPOOL_SS( SCP_ESHFMX ) );

		// eq set 4
		double HREF = 0.0;

		if (DRPRED > ReadCOMPOOL_VS( SCP_PBRC, IGS, 2 )) HREF = ReadCOMPOOL_VS( SCP_PBHC, IGS, 2 ) + (ReadCOMPOOL_VS( SCP_PBGC, IGS, 2 ) * (DRPRED - ReadCOMPOOL_VS( SCP_PBRC, IGS, 2 )));
		else
		{
			HREF = ReadCOMPOOL_VS( SCP_HALI, IGS, 2 ) - (ReadCOMPOOL_VS( SCP_TGGS, IGS, 2 ) * DRPRED);
			if (DRPRED > 0.0) HREF += (DRPRED * DRPRED) * (ReadCOMPOOL_VS( SCP_CUBIC_C3, IGS, 2 ) + (DRPRED * ReadCOMPOOL_VS( SCP_CUBIC_C4, IGS, 2 )));
		}

		// eq set 5
		double HREFOH = 0.0;// altitude below which RF is adjusted if PSHA > PSRF [ft]
		double DRF = 0.0;// RF adjustment

		if (DRPRED > ReadCOMPOOL_VS( SCP_PBRCQ, IGS, 2 )) QBREF = range( ReadCOMPOOL_VS( SCP_QBRLL, IGS, 2 ), ReadCOMPOOL_VS( SCP_QBRLL, IGS, 2 ) + (ReadCOMPOOL_VS( SCP_QBC1, IGS, 2 ) * (DRPRED - ReadCOMPOOL_VS( SCP_PBRCQ, IGS, 2 ))), ReadCOMPOOL_VS( SCP_QBRML, IGS, 2 ) );
		else QBREF = range( ReadCOMPOOL_VS( SCP_QBRLL, IGS, 2 ), ReadCOMPOOL_VS( SCP_QBRUL, IGS, 2 ) + (ReadCOMPOOL_VS( SCP_QBC2, IGS, 2 ) * DRPRED), ReadCOMPOOL_VS( SCP_QBRUL, IGS, 2 ) );
		if ((ReadCOMPOOL_IS( SCP_IPHASE ) == 2) && (ReadCOMPOOL_SS( SCP_PSHA ) > ReadCOMPOOL_SS( SCP_PSRF )))
		{
			HREFOH = HREF - range( 0.0, ReadCOMPOOL_SS( SCP_DHOH1 ) * (DRPRED - ReadCOMPOOL_SS( SCP_DHOH2 )), ReadCOMPOOL_SS( SCP_DHOH3 ) );
			DRF = (ReadCOMPOOL_SS( SCP_DRFK ) * (HREFOH - H)) / (ReadCOMPOOL_SS( SCP_PSHA ) * RAD/*DTR*/);
			WriteCOMPOOL_SS( SCP_RF, static_cast<float>(range( ReadCOMPOOL_SS( SCP_RFMN ), ReadCOMPOOL_SS( SCP_RF ) + DRF, ReadCOMPOOL_SS( SCP_RFMX ) )) );
		}
		WriteCOMPOOL_SS( SCP_HERROR, static_cast<float>(HREF - H) );
		if (DRPRED > ReadCOMPOOL_VS( SCP_PBRC, IGS, 2 )) DHDRRF = -ReadCOMPOOL_VS( SCP_PBGC, IGS, 2 );
		else DHDRRF = -range( ReadCOMPOOL_VS( SCP_PBGC, IGS, 2 ), -ReadCOMPOOL_VS( SCP_TGGS, IGS, 2 ) + (DRPRED * (2 * ReadCOMPOOL_VS( SCP_CUBIC_C3, IGS, 2 ) + (3 * ReadCOMPOOL_VS( SCP_CUBIC_C4, IGS, 2 ) * DRPRED))), -ReadCOMPOOL_VS( SCP_TGGS, IGS, 2 ) );
		DELRNG = ReadCOMPOOL_SS( SCP_HERROR ) / DHDRRF;

		// eq set 6
		double QBARD = 0.0;
		QBARD = range( -ReadCOMPOOL_SS( SCP_QBARDL ), ReadCOMPOOL_SS( SCP_CQG ) * (QBAR - QBARF), ReadCOMPOOL_SS( SCP_QBARDL ) );
		QBARF += QBARD * dt/*DTG*/;// HACK replaced fixed cycle length for dt
		QBD = (ReadCOMPOOL_SS( SCP_CDEQD ) * QBD) + (ReadCOMPOOL_SS( SCP_CQDG ) * QBARD);
		QBERR = QBREF - QBARF;
		//EAS_CMD = 17.1865 * sqrt( QBREF );
		return;
	}

	void TAEMGuidance::TGTRAN( void )
	{
		if (ReadCOMPOOL_IS( SCP_IPHASE ) == 3)
		{
			if (((fabs( ReadCOMPOOL_SS( SCP_HERROR ) ) < ((H * ReadCOMPOOL_SS( SCP_DEL_H1 )) - ReadCOMPOOL_SS( SCP_DEL_H2 ))) && (fabs( Y ) < ((H * ReadCOMPOOL_SS( SCP_Y_RANGE1 )) - ReadCOMPOOL_SS( SCP_Y_RANGE2 ))) &&
				(fabs( GAMMA - GAMSGS ) < ((H * ReadCOMPOOL_SS( SCP_GAMMA_COEF1 )) - ReadCOMPOOL_SS( SCP_GAMMA_COEF2 ))) && (fabs( QBERR ) < ReadCOMPOOL_SS( SCP_QB_ERROR2 )) && (ReadCOMPOOL_SS( SCP_H_REF1 ) > H))
				|| (H < ReadCOMPOOL_SS( SCP_H_REF2 ))) WriteCOMPOOL_IS( SCP_TG_END, 1 );
		}
		else
		{
			if ((ReadCOMPOOL_SS( SCP_RPRED ) < RPRED3) || (H < ReadCOMPOOL_SS( SCP_H_MIN_3 )))
			{
				// eq set 1
				WriteCOMPOOL_IS( SCP_IPHASE, 3 );
				PHI0 = PHIC;
				PHILIM = ReadCOMPOOL_SS( SCP_PHILM3 );
				DNZUL = ReadCOMPOOL_SS( SCP_DNZUC2 );
				DNZLL = ReadCOMPOOL_SS( SCP_DNZLC2 );
			}
			else
			{
				// HACK moved ES and EMEP calc to here so they are available in IPHASE 0 and 2, for display in VERT SITs
				ES = ReadCOMPOOL_VS( SCP_ES1, IGS, 2 ) + (DRPRED * ReadCOMPOOL_VS( SCP_EDRS, IGS, 2 ));
				EMEP = ReadCOMPOOL_MS( SCP_EMEP_C1, IGS, IEL, 2, 2 ) + (DRPRED * ReadCOMPOOL_MS( SCP_EMEP_C2, IGS, IEL, 2, 2 ));
				switch (ReadCOMPOOL_IS( SCP_IPHASE ))
				{
					case 0:
						if (EOW < (EN + ReadCOMPOOL_SS( SCP_ENBIAS )))
						{
							// eq set 2
							WriteCOMPOOL_IS( SCP_IPHASE, 1 );
							PHILIM = ReadCOMPOOL_SS( SCP_PHILM1 );
						}
						break;
					case 1:
						if ((ReadCOMPOOL_SS( SCP_PSHA ) < ReadCOMPOOL_SS( SCP_PSSTRN )) && (DRPRED > ReadCOMPOOL_VS( SCP_RMINST, IGS, 2 )))
						{
							// eq set 3
							double SPSI = 0.0;

							//ES = ReadCOMPOOL_VS( SCP_ES1, IGS, 2 ) + (DRPRED * ReadCOMPOOL_VS( SCP_EDRS, IGS, 2 ));// moved up
							if (EOW > ES)
							{
								WriteCOMPOOL_IS( SCP_IPHASE, 0 );
								PHILIM = ReadCOMPOOL_SS( SCP_PHILM0 );
								S = -ReadCOMPOOL_SS( SCP_YSGNP );
								SPSI = S * PSD;
								if ((SPSI < 0.0) && (ReadCOMPOOL_SS( SCP_PSHA ) < 90.0)) S = -S;
							}
						}
						//EMEP = ReadCOMPOOL_MS( SCP_EMEP_C1, IGS, IEL, 2, 2 ) + (DRPRED * ReadCOMPOOL_MS( SCP_EMEP_C2, IGS, IEL, 2, 2 ));// moved up
						EMOH = ReadCOMPOOL_VS( SCP_EMOHC1, IGS, 2 ) + (ReadCOMPOOL_VS( SCP_EMOHC2, IGS, 2 ) * DRPRED);
						if ((EOW < EMEP) && (ReadCOMPOOL_IS( SCP_NEP_FB ) == 1))
						{
							// SM alert "SW TO MEP"
							WriteCOMPOOL_IS( SCP_MEPALERT, 1 );
							//MEP = 1;// disabled auto switching to MEP
						}
						else
						{
							WriteCOMPOOL_IS( SCP_MEPALERT, 0 );
						}
						if ((EOW < EMOH) && (ReadCOMPOOL_SS( SCP_PSHA ) > ReadCOMPOOL_SS( SCP_PSOHAL )) && (ReadCOMPOOL_SS( SCP_RPRED ) > ReadCOMPOOL_SS( SCP_RMOH )) && (ReadCOMPOOL_IS( SCP_OVHD ) == 1))// added OVHD check
						{
							// SM alert "OTT ST IN"
							WriteCOMPOOL_IS( SCP_OHALERT, 1 );
						}
						else
						{
							WriteCOMPOOL_IS( SCP_OHALERT, 0 );
						}
						if (RCIR < (ReadCOMPOOL_SS( SCP_P2TRNC1 ) * ReadCOMPOOL_SS( SCP_RTURN )))
						{
							WriteCOMPOOL_IS( SCP_IPHASE, 2 );
							PHILIM = ReadCOMPOOL_SS( SCP_PHILM2 );
						}
						break;
					/*case 2:
						break;*/
				}
			}
		}
		return;
	}

	void TAEMGuidance::TGNZC( double dt )
	{
		// eq set 1
		double GDH = 0.0;// [1]
		double HDREF = 0.0;// HDOT reference [fps]
		double HDERR = 0.0;// HDOT error [fps]
		double DNZC = 0.0;// unlimited normal acceleration command [g]
		double MXQBWT = 0.0;// [psf/slug]
		double QBLL = 0.0;// [psf]
		double QBMNNZ = 0.0;// minimum dynamic pressure profile
		double QBMXNZ = 0.0;// maximum dynamic pressure profile

		GDH = midval( ReadCOMPOOL_SS( SCP_GDHC ) - (ReadCOMPOOL_SS( SCP_GDHS ) * H), ReadCOMPOOL_SS( SCP_GDHLL ), ReadCOMPOOL_SS( SCP_GDHUL ) );
		HDREF = VH * DHDRRF;
		HDERR = HDREF - HDOT;
		DNZC = ReadCOMPOOL_SS( SCP_DNZCG ) * GDH * (HDERR + (ReadCOMPOOL_SS( SCP_HDREQG ) * GDH * ReadCOMPOOL_SS( SCP_HERROR )));
		if (MACH < ReadCOMPOOL_SS( SCP_QMACH2 )) MXQBWT = midval( ReadCOMPOOL_SS( SCP_QBWT1 ) + (ReadCOMPOOL_SS( SCP_QBMSL1 ) * (MACH - ReadCOMPOOL_SS( SCP_QMACH1 ))), ReadCOMPOOL_SS( SCP_QBWT2 ), ReadCOMPOOL_SS( SCP_QBWT1 ) );
		else MXQBWT = midval( ReadCOMPOOL_SS( SCP_QBWT2 ) + (ReadCOMPOOL_SS( SCP_QBMSL2 ) * (MACH - ReadCOMPOOL_SS( SCP_QMACH2 ))), ReadCOMPOOL_SS( SCP_QBWT2 ), ReadCOMPOOL_SS( SCP_QBWT3 ) );
		QBLL = MXQBWT * WEIGHT;
		QBMNNZ = QBLL / max(COSPHI, ReadCOMPOOL_SS( SCP_CPMIN ));
		if (MACH > ReadCOMPOOL_SS( SCP_QBM1 )) QBMXNZ = midval( ReadCOMPOOL_SS( SCP_QBMX2 ) + (ReadCOMPOOL_SS( SCP_QBMXS2 ) * (MACH - ReadCOMPOOL_SS( SCP_QBM2 ))), ReadCOMPOOL_SS( SCP_QBMX2 ), ReadCOMPOOL_SS( SCP_QBMX3 ) );
		else QBMXNZ = midval( ReadCOMPOOL_SS( SCP_QBMX2 ) + (ReadCOMPOOL_SS( SCP_QBMXS1 ) * (MACH - ReadCOMPOOL_SS( SCP_QBM1 ))), ReadCOMPOOL_SS( SCP_QBMX2 ), ReadCOMPOOL_SS( SCP_QBMX1 ) );
		if ((ReadCOMPOOL_SS( SCP_EQLOWL ) < EOW) && (EOW < ReadCOMPOOL_SS( SCP_EQLOWU )) && (ReadCOMPOOL_SS( SCP_PSHA ) > ReadCOMPOOL_SS( SCP_PSOHQB )))
			QBMXNZ = midval( ReadCOMPOOL_VS( SCP_QBREF2, IGS, 2 ) - (ReadCOMPOOL_SS( SCP_PQBWRR ) * (RPRED2 - ReadCOMPOOL_SS( SCP_R2MAX ) + ((EOW - EN) / ReadCOMPOOL_SS( SCP_PEWRR )))), QBMNNZ, QBMXNZ );

		// eq set 2
		double QBNZUL = 0.0;// maximum dynamic pressure [psf]
		double QBNZLL = 0.0;// minimum dynamic pressure [psf]

		QBNZUL = -((ReadCOMPOOL_SS( SCP_QBG1 ) * (QBMNNZ - QBARF)) - QBD) * ReadCOMPOOL_SS( SCP_QBG2 );
		QBNZLL = -((ReadCOMPOOL_SS( SCP_QBG1 ) * (QBMXNZ - QBARF)) - QBD) * ReadCOMPOOL_SS( SCP_QBG2 );

		if (ReadCOMPOOL_IS( SCP_IPHASE ) == 3) NZC = midval( DNZC, QBNZLL, QBNZUL );
		else
		{
			// eq set 3
			double EMAX = 0.0;
			double EMIN = 0.0;
			double EOWNZUL = 0.0;
			double EOWNZLL = 0.0;
			double DNZCL = 0.0;
			double DNZCD = 0.0;

			EMAX = EN + (ReadCOMPOOL_VS( SCP_EDELNZ, IGS, 2 ) * midval( DRPRED / ReadCOMPOOL_VS( SCP_DEL_R_EMAX, IGS, 2 ), ReadCOMPOOL_SS( SCP_EDELC1 ), ReadCOMPOOL_SS( SCP_EDELC2 ) ));
			EMIN = EN - ReadCOMPOOL_VS( SCP_EDELNZ, IGS, 2 );
			EOWNZUL = ((ReadCOMPOOL_SS( SCP_GEUL ) * GDH * (EMAX - EOW)) + HDERR) * ReadCOMPOOL_SS( SCP_GEHDUL ) * GDH;
			EOWNZLL = ((ReadCOMPOOL_SS( SCP_GELL ) * GDH * (EMIN - EOW)) + HDERR) * ReadCOMPOOL_SS( SCP_GEHDLL ) * GDH;
			DNZCL = midval( DNZC, EOWNZLL, EOWNZUL );
			DNZCL = midval( DNZCL, QBNZLL, QBNZUL );
			DNZCD = midval( (DNZCL - NZC) * ReadCOMPOOL_SS( SCP_CQG ), -ReadCOMPOOL_SS( SCP_DNZCDL ), ReadCOMPOOL_SS( SCP_DNZCDL ) );
			NZC = NZC + DNZCD * dt/*DTG*/;// HACK replaced fixed cycle length for dt
		}

		NZC = midval( NZC, DNZLL, DNZUL );
		return;
	}

	void TAEMGuidance::TGSBC( double dt )
	{
		if (MACH > ReadCOMPOOL_SS( SCP_DSBCM ))
		{
			DSBC_AT = ReadCOMPOOL_SS( SCP_DSBSUP );
			return;
		}

		// eq set 1
		double DSBCLL = 0.0;// lower command limit
		double DSBCUL = 0.0;// upper command limit

		DSBCLL = range( 0.0, ReadCOMPOOL_SS( SCP_DSBSUP ) + ReadCOMPOOL_SS( SCP_DSBLLS ) * (MACH - ReadCOMPOOL_SS( SCP_DSBCM )), ReadCOMPOOL_SS( SCP_DSBSUP ) );
		DSBCUL = range( ReadCOMPOOL_SS( SCP_DSBSUP ), ReadCOMPOOL_SS( SCP_DSBSUP ) + ReadCOMPOOL_SS( SCP_DSBULS ) * (MACH - ReadCOMPOOL_SS( SCP_DSBCM )), ReadCOMPOOL_SS( SCP_DSBLIM ) );

		// eq set 2
		double DSBE = 0.0;// [deg]

		if (ReadCOMPOOL_IS( SCP_IPHASE ) == 0) DSBC = ReadCOMPOOL_SS( SCP_DSBLIM );
		else
		{
			DSBE = ReadCOMPOOL_SS( SCP_GSBE ) * QBERR;
			if ((DSBC > DSBCLL) && (DSBC < DSBCUL))
			{
				DSBI = range( -DSBIL, DSBI + GSBI * QBERR * dt/*DTG*/, DSBIL );// HACK replaced fixed cycle length for dt
			}
			DSBC = ReadCOMPOOL_SS( SCP_DSBNOM ) - DSBE - DSBI;
			if ((EN - EOW) > DEMXSB) DSBC = 0.0;
		}

		// eq set 3
		DSBC_AT = range( DSBCLL, DSBC, DSBCUL );
		return;
	}

	void TAEMGuidance::TGPHIC( double dt )
	{
		double PHILIMIT = range( ReadCOMPOOL_SS( SCP_PHILMSUP ), ReadCOMPOOL_SS( SCP_PHILMSUP ) + (ReadCOMPOOL_SS( SCP_PHILS ) * (MACH - ReadCOMPOOL_SS( SCP_PHIM ))), PHILIM );

		switch (ReadCOMPOOL_IS( SCP_IPHASE ))
		{
			case 0:
				// eq set 1
				PHIC = S * PHILIMIT;
				break;
			case 1:
				// eq set 2
				PHIC = ReadCOMPOOL_SS( SCP_GPHI ) * DPSAC;
				break;
			case 2:
				{
					// eq set 3
					float RERRC = ReadCOMPOOL_SS( SCP_RERRC );// vehicle radial error in HAC [ft]
					double RDOT = 0.0;// HAC radial rate [fps]
					double PHIP2C = 0.0;
					double RDOTRF = 0.0;// reference HAC radial rate [fps]

					RERRC = static_cast<float>(RCIR - ReadCOMPOOL_SS( SCP_RTURN ));
					if (RERRC > ReadCOMPOOL_SS( SCP_RERRLM ))
					{
						if (PHILIMIT > ReadCOMPOOL_SS( SCP_PHILM1 )) PHILIMIT = ReadCOMPOOL_SS( SCP_PHILM1 );
						PHIC = ReadCOMPOOL_SS( SCP_GPHI ) * DPSAC;
					}
					else
					{
						RDOT = -((XCIR * XDOT) + (YCIR * YDOT)) / RCIR;
						PHIP2C = ((VH * VH) - (RDOT * RDOT)) * DEG/*RTD*/ / (G * MPS2FPS * ReadCOMPOOL_SS( SCP_RTURN ));
						RDOTRF = -VH * (ReadCOMPOOL_SS( SCP_R1 ) + (2 * ReadCOMPOOL_SS( SCP_R2 ) * ReadCOMPOOL_SS( SCP_PSHA ))) * DEG/*RTD*/ / ReadCOMPOOL_SS( SCP_RTURN );
						PHIC = ReadCOMPOOL_SS( SCP_YSGNP ) * max(0.0, PHIP2C + (ReadCOMPOOL_SS( SCP_GR ) * RERRC) + (ReadCOMPOOL_SS( SCP_GRDOT ) * (RDOT - RDOTRF)));
					}

					WriteCOMPOOL_SS( SCP_RERRC, RERRC );
				}
				break;
			case 3:
				{
					// eq set 4
					double YERRC = 0.0;
					double DPHI = 0.0;

					YERRC = range( -ReadCOMPOOL_SS( SCP_YERRLM ), -ReadCOMPOOL_SS( SCP_GY ) * Y, ReadCOMPOOL_SS( SCP_YERRLM ) );
					PHIC = YERRC - (ReadCOMPOOL_SS( SCP_GYDOT ) * YDOT);
					if (fabs( PHIC ) > PHILMC) PHILIMIT = ReadCOMPOOL_SS( SCP_PHILM4 );
					if (ISR > 0.0)
					{
						DPHI = (PHIC - PHI0) / ISR;
						ISR -= dt/*1.0*/;// HACK subtract dt instead
						PHIC = PHI0 + DPHI;
						PHI0 = PHIC;
					}
				}
				break;
		}

		PHIC_AT = range( -PHILIMIT, PHIC, PHILIMIT );
		return;
	}
}

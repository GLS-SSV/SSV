/******* SSV File Modification Notice *******
Date         Developer
2020/04/07   GLS
2020/05/10   GLS
2020/06/20   GLS
2020/08/24   GLS
2020/08/30   GLS
2020/09/07   GLS
2021/06/13   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/03/24   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/10/05   GLS
2022/12/17   GLS
2025/12/27   indy91
2025/12/29   GLS
2023/10/22   GLS
2023/10/29   GLS
2023/11/26   GLS
2025/01/23   GLS
********************************************/
#include "MDU.h"
#include "../Atlantis.h"
#include "../dps/IDP.h"
#include "../mission/Mission.h"
#include <MathSSV.h>
#include <gcCoreAPI.h>


namespace vc
{
	constexpr int AlphaLimNom_count = 16;
	constexpr double AlphaLimNom_Mach[AlphaLimNom_count] = {0.0, 0.2, 0.5, 0.6, 0.8, 1.1, 2.0, 2.5, 3.0, 3.2, 3.5, 5.0, 8.0, 9.6, 11.4, 27.0};// [Mach]
	constexpr double AlphaLimNom_Max[AlphaLimNom_count] = {20.0, 20.0, 20.0, 20.0, 15.0, 15.8, 18.3, 19.6, 21.0, 21.4, 22.0, 28.0, 40.0, 44.0, 44.0, 44.0};// [deg]
	constexpr double AlphaLimNom_Min[AlphaLimNom_count] = {-4.0, -4.0, 0.0, 0.7, 2.0, 4.0, 4.0, 6.0, 7.6, 8.2, 12.0, 16.0, 28.9, 33.0, 36.0, 36.0};// [deg]

	constexpr int AlphaLimRTLS_count = 14;
	constexpr double AlphaLimRTLS_Mach[AlphaLimRTLS_count] = {0.0, 0.2, 0.5, 0.6, 0.8, 1.1, 2.0, 2.5, 3.0, 3.4, 4.0, 5.1, 6.0, 8.0};// [Mach]
	constexpr double AlphaLimRTLS_Max[AlphaLimRTLS_count] = {20.0, 20.0, 20.0, 20.0, 15.0, 15.8, 18.3, 19.6, 21.0, 21.0, 21.0, 50.0, 53.0, 53.0};// [deg]
	constexpr double AlphaLimRTLS_Min[AlphaLimRTLS_count] = {-4.0, -4.0, 0.0, 0.7, 2.0, 4.0, 4.0, 6.0, 8.2, 10.0, 10.0, 10.0, 10.0, 10.0};// [deg]

	constexpr int MaxLD_count = 4;
	constexpr double MaxLD_Mach[MaxLD_count] = {0.95, 1.0, 2.0, 3.0};// [Mach]
	constexpr double MaxLD_Alpha[MaxLD_count] = {10.5, 12.0, 15.0, 17.0};// [deg]

	void MDU::AEPFD( HDC hDC )
	{
		int MM = GetIDP()->GetMM();
		double sinpitch;
		double cospitch;
		double sinroll;
		double cosroll;
		double sinyaw;
		double cosyaw;
		GetIDP()->GetADIAtt( usMDUID, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
		unsigned short pitchrate;
		unsigned short rollrate;
		unsigned short yawrate;
		unsigned short pitchratescale;
		unsigned short rollratescale;
		unsigned short yawratescale;
		unsigned short TGOSEC;
		unsigned short ADIRR_0_ON_R;
		GetIDP()->GetADIRate( usMDUID, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
		unsigned short pitcherror;
		unsigned short rollerror;
		unsigned short yawerror;
		unsigned short pitcherrorscale;
		GetIDP()->GetADIError( usMDUID, pitcherror, rollerror, yawerror, pitcherrorscale );

		SelectObject( hDC, gdiSSVAFont_h22w18 );

		switch (MM)
		{
			case 101:
				//AEPFD_Header_AscentDAP( hDC, 101, adiatt );
				Tapes_Invalid( hDC );
				ADI_STATIC( hDC );
				ADI( hDC, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				ADI_RATE( hDC, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
				ADI_ERROR( hDC, pitcherror, rollerror, yawerror, pitcherrorscale );
				HSI_E( hDC, GetIDP()->GetHeading(), GetIDP()->DrawCourse(), GetIDP()->GetCourse(), GetIDP()->DrawCourseDeviation(), GetIDP()->GetCourseDeviationFlag(), 0.0, 0.0, GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				break;
			case 102:
				AEPFD_Header( hDC, MM, false, false, false, false, false, GetIDP()->GetADIattsw(), GetIDP()->GetAutoDAPPitchState(), GetIDP()->GetAutoThrotRollYawState(), GetIDP()->GetBlankThrotRY(), GetIDP()->GetAutoSBState(), GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_MV()) Tape_MV( hDC, GetIDP()->GetVelRef(), GetIDP()->GetMach() );
				else if (GetIDP()->DrawBox_MVR()) Box_MVR( hDC, GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_EAS()) Tape_EAS( hDC, GetIDP()->GetEAS() );
				else if (GetIDP()->DrawBox_EAS()) Box_EAS( hDC, GetIDP()->GetEAS() );
				Tape_Alpha( hDC, GetIDP()->GetAlpha(), 0 );
				Tape_H_Hdot( hDC, GetIDP()->GetAltitude(), GetIDP()->GetAltitudeRate() );
				if (GetIDP()->DrawBeta()) AEPFD_BETA( hDC, GetIDP()->GetBeta() );
				ADI_STATIC( hDC );
				ADI( hDC, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				ADI_RATE( hDC, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
				ADI_ERROR( hDC, pitcherror, rollerror, yawerror, pitcherrorscale );
				AEPFD_GMETER_STATIC( hDC );
				AEPFD_GMETER( hDC, GetIDP()->GetAccelType(), GetIDP()->GetAccel() );
				HSI_A( hDC, GetIDP()->GetHeading(), GetIDP()->GetRollSW(), GetIDP()->DrawCourse(), GetIDP()->GetCourse(), GetIDP()->DrawCourseDeviation(), GetIDP()->GetCourseDeviationFlag(), GetIDP()->GetCourseDeviationScale(), GetIDP()->GetCourseDeviation(), GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				AEPFD_XTRK( hDC );// TODO only NOM, TAL and ATO
				AEPFD_dINC( hDC, GetIDP()->GetdeltaInc() );
				break;
			case 103:
				AEPFD_Header( hDC, MM, false, false, false, false, false, GetIDP()->GetADIattsw(), GetIDP()->GetAutoDAPPitchState(), GetIDP()->GetAutoThrotRollYawState(), GetIDP()->GetBlankThrotRY(), GetIDP()->GetAutoSBState(), GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_MV()) Tape_MV( hDC, GetIDP()->GetVelRef(), GetIDP()->GetMach() );
				else if (GetIDP()->DrawBox_MVR()) Box_MVR( hDC, GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_EAS()) Tape_EAS( hDC, GetIDP()->GetEAS() );
				else if (GetIDP()->DrawBox_EAS()) Box_EAS( hDC, GetIDP()->GetEAS() );
				Tape_Alpha( hDC, GetIDP()->GetAlpha(), 0 );
				Tape_H_Hdot( hDC, GetIDP()->GetAltitude(), GetIDP()->GetAltitudeRate() );
				if (GetIDP()->DrawBeta()) AEPFD_BETA( hDC, GetIDP()->GetBeta() );
				ADI_STATIC( hDC );
				ADI( hDC, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				ADI_RATE( hDC, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
				ADI_ERROR( hDC, pitcherror, rollerror, yawerror, pitcherrorscale );
				AEPFD_GMETER_STATIC( hDC );
				AEPFD_GMETER( hDC, GetIDP()->GetAccelType(), GetIDP()->GetAccel() );
				HSI_A( hDC, GetIDP()->GetHeading(), GetIDP()->GetRollSW(), GetIDP()->DrawCourse(), GetIDP()->GetCourse(), GetIDP()->DrawCourseDeviation(), GetIDP()->GetCourseDeviationFlag(), GetIDP()->GetCourseDeviationScale(), GetIDP()->GetCourseDeviation(), GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				if (0)// TODO TAL
				{
					AEPFD_dXTRK( hDC );
					AEPFD_RANGERW( hDC );// fix colision between this and dINC
				}
				AEPFD_XTRK( hDC );// TODO only NOM, TAL and ATO
				if (0) AEPFD_RANGERW( hDC );// TODO ECAL/BDA
				AEPFD_dINC( hDC, GetIDP()->GetdeltaInc() );
				if (0) AEPFD_TGTINC( hDC );// TODO ATO
				break;
			case 104:
				AEPFD_Header( hDC, MM, false, false, false, false, false, GetIDP()->GetADIattsw(), GetIDP()->GetAutoDAPPitchState(), GetIDP()->GetAutoThrotRollYawState(), GetIDP()->GetBlankThrotRY(), GetIDP()->GetAutoSBState(), GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_MV()) Tape_MV( hDC, GetIDP()->GetVelRef(), GetIDP()->GetMach() );
				else if (GetIDP()->DrawBox_MVR()) Box_MVR( hDC, GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_EAS()) Tape_EAS( hDC, GetIDP()->GetEAS() );
				else if (GetIDP()->DrawBox_EAS()) Box_EAS( hDC, GetIDP()->GetEAS() );
				Tape_H_Hdot( hDC, GetIDP()->GetAltitude(), GetIDP()->GetAltitudeRate() );
				ADI_STATIC( hDC );
				ADI( hDC, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				ADI_RATE( hDC, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
				ADI_ERROR( hDC, pitcherror, rollerror, yawerror, pitcherrorscale );
				HSI_E( hDC, GetIDP()->GetHeading(), GetIDP()->DrawCourse(), GetIDP()->GetCourse(), GetIDP()->DrawCourseDeviation(), GetIDP()->GetCourseDeviationFlag(), GetIDP()->GetCourseDeviationScale(), GetIDP()->GetCourseDeviation(), GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				AEPFD_XTRK( hDC );// TODO only NOM, TAL and ATO
				AEPFD_dINC( hDC, GetIDP()->GetdeltaInc() );
				break;
			case 105:
				AEPFD_Header( hDC, MM, false, false, false, false, false, GetIDP()->GetADIattsw(), GetIDP()->GetAutoDAPPitchState(), GetIDP()->GetAutoThrotRollYawState(), GetIDP()->GetBlankThrotRY(), GetIDP()->GetAutoSBState(), GetIDP()->GetMach() );
				ADI_STATIC( hDC );
				ADI( hDC, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				ADI_RATE( hDC, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
				ADI_ERROR( hDC, pitcherror, rollerror, yawerror, pitcherrorscale );
				break;
			case 106:
				AEPFD_Header( hDC, MM, false, false, false, false, false, GetIDP()->GetADIattsw(), GetIDP()->GetAutoDAPPitchState(), GetIDP()->GetAutoThrotRollYawState(), GetIDP()->GetBlankThrotRY(), GetIDP()->GetAutoSBState(), GetIDP()->GetMach() );
				ADI_STATIC( hDC );
				ADI( hDC, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				ADI_RATE( hDC, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
				ADI_ERROR( hDC, pitcherror, rollerror, yawerror, pitcherrorscale );
				break;
			case 201:
				ADI_STATIC( hDC );
				ADI( hDC, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				break;
			case 202:
				ADI_STATIC( hDC );
				ADI( hDC, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				break;
			case 301:
				AEPFD_Header( hDC, MM, false, false, false, false, false, GetIDP()->GetADIattsw(), GetIDP()->GetAutoDAPPitchState(), GetIDP()->GetAutoThrotRollYawState(), GetIDP()->GetBlankThrotRY(), GetIDP()->GetAutoSBState(), GetIDP()->GetMach() );
				ADI_STATIC( hDC );
				ADI( hDC, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				ADI_RATE( hDC, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
				ADI_ERROR( hDC, pitcherror, rollerror, yawerror, pitcherrorscale );
				break;
			case 302:
				AEPFD_Header( hDC, MM, false, false, false, false, false, GetIDP()->GetADIattsw(), GetIDP()->GetAutoDAPPitchState(), GetIDP()->GetAutoThrotRollYawState(), GetIDP()->GetBlankThrotRY(), GetIDP()->GetAutoSBState(), GetIDP()->GetMach() );
				ADI_STATIC( hDC );
				ADI( hDC, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				ADI_RATE( hDC, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
				ADI_ERROR( hDC, pitcherror, rollerror, yawerror, pitcherrorscale );
				break;
			case 303:
				AEPFD_Header( hDC, MM, false, false, false, false, false, GetIDP()->GetADIattsw(), GetIDP()->GetAutoDAPPitchState(), GetIDP()->GetAutoThrotRollYawState(), GetIDP()->GetBlankThrotRY(), GetIDP()->GetAutoSBState(), GetIDP()->GetMach() );
				ADI_STATIC( hDC );
				ADI( hDC, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				ADI_RATE( hDC, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
				ADI_ERROR( hDC, pitcherror, rollerror, yawerror, pitcherrorscale );
				break;
			case 304:
				AEPFD_Header( hDC, MM, false, false, false, false, false, GetIDP()->GetADIattsw(), GetIDP()->GetAutoDAPPitchState(), GetIDP()->GetAutoThrotRollYawState(), GetIDP()->GetBlankThrotRY(), GetIDP()->GetAutoSBState(), GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_MV()) Tape_MV( hDC, GetIDP()->GetVelRef(), GetIDP()->GetMach() );
				else if (GetIDP()->DrawBox_MVR()) Box_MVR( hDC, GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_EAS()) Tape_EAS( hDC, GetIDP()->GetEAS() );
				else if (GetIDP()->DrawBox_EAS()) Box_EAS( hDC, GetIDP()->GetEAS() );
				Tape_Alpha( hDC, GetIDP()->GetAlpha(), GetIDP()->GetMach() );
				Tape_H_Hdot( hDC, GetIDP()->GetAltitude(), GetIDP()->GetAltitudeRate() );
				ADI_STATIC( hDC );
				ADI( hDC, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				ADI_RATE( hDC, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
				ADI_ERROR( hDC, pitcherror, rollerror, yawerror, pitcherrorscale );
				AEPFD_GMETER_STATIC( hDC );
				AEPFD_GMETER( hDC, GetIDP()->GetAccelType(), GetIDP()->GetAccel() );
				HSI_E( hDC, GetIDP()->GetHeading(), GetIDP()->DrawCourse(), GetIDP()->GetCourse(), GetIDP()->DrawCourseDeviation(), GetIDP()->GetCourseDeviationFlag(), GetIDP()->GetCourseDeviationScale(), GetIDP()->GetCourseDeviation(), GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				AEPFD_dAZ_HTA( hDC, GetIDP()->FlashdeltaAZ(), GetIDP()->GetdeltaAZ() );
				AEPFD_RANGERW( hDC );
				AEPFD_HACCEL( hDC, GetIDP()->GetVacc() );
				break;
			case 305:
				AEPFD_Header( hDC, MM, false, false, false, false, false, GetIDP()->GetADIattsw(), GetIDP()->GetAutoDAPPitchState(), GetIDP()->GetAutoThrotRollYawState(), GetIDP()->GetBlankThrotRY(), GetIDP()->GetAutoSBState(), GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_MV()) Tape_MV( hDC, GetIDP()->GetVelRef(), GetIDP()->GetMach() );
				else if (GetIDP()->DrawBox_MVR()) Box_MVR( hDC, GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_EAS()) Tape_EAS( hDC, GetIDP()->GetEAS() );
				else if (GetIDP()->DrawBox_EAS()) Box_EAS( hDC, GetIDP()->GetEAS() );
				Tape_Alpha( hDC, GetIDP()->GetAlpha(), GetIDP()->GetMach() );
				Tape_H_Hdot( hDC, GetIDP()->GetAltitude(), GetIDP()->GetAltitudeRate() );
				ADI_STATIC( hDC );
				ADI( hDC, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				ADI_RATE( hDC, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
				ADI_ERROR( hDC, pitcherror, rollerror, yawerror, pitcherrorscale );
				AEPFD_GMETER_STATIC( hDC );
				AEPFD_GMETER( hDC, GetIDP()->GetAccelType(), GetIDP()->GetAccel() );
				HSI_E( hDC, GetIDP()->GetHeading(), GetIDP()->DrawCourse(), GetIDP()->GetCourse(), GetIDP()->DrawCourseDeviation(), GetIDP()->GetCourseDeviationFlag(), GetIDP()->GetCourseDeviationScale(), GetIDP()->GetCourseDeviation(), GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				if (GetIDP()->DrawdAZ()) AEPFD_dAZ_HTA( hDC, GetIDP()->FlashdeltaAZ(), GetIDP()->GetdeltaAZ() );
				if (GetIDP()->DrawHACC()) AEPFD_RANGEHACC( hDC, GetIDP()->GetHACCRange() );
				AEPFD_RANGERW( hDC );
				if (GetIDP()->DrawGlideSlopeDeviation()) AEPFD_GSI( hDC, GetIDP()->GetGlideSlopeDeviationFlag(), GetIDP()->GetGlideSlopeDeviationScale(), GetIDP()->GetGlideSlopeDeviation() );
				break;
			case 601:
				AEPFD_Header( hDC, MM, false, false, false, false, false, GetIDP()->GetADIattsw(), GetIDP()->GetAutoDAPPitchState(), GetIDP()->GetAutoThrotRollYawState(), GetIDP()->GetBlankThrotRY(), GetIDP()->GetAutoSBState(), GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_MV()) Tape_MV( hDC, GetIDP()->GetVelRef(), GetIDP()->GetMach() );
				else if (GetIDP()->DrawBox_MVR()) Box_MVR( hDC, GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_EAS()) Tape_EAS( hDC, GetIDP()->GetEAS() );
				else if (GetIDP()->DrawBox_EAS()) Box_EAS( hDC, GetIDP()->GetEAS() );
				Tape_Alpha( hDC, GetIDP()->GetAlpha(), 0 );
				Tape_H_Hdot( hDC, GetIDP()->GetAltitude(), GetIDP()->GetAltitudeRate() );
				AEPFD_BETA( hDC, GetIDP()->GetBeta() );
				ADI_STATIC( hDC );
				ADI( hDC, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				ADI_RATE( hDC, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
				ADI_ERROR( hDC, pitcherror, rollerror, yawerror, pitcherrorscale );
				AEPFD_GMETER_STATIC( hDC );
				AEPFD_GMETER( hDC, GetIDP()->GetAccelType(), GetIDP()->GetAccel() );
				HSI_E( hDC, GetIDP()->GetHeading(), GetIDP()->DrawCourse(), GetIDP()->GetCourse(), GetIDP()->DrawCourseDeviation(), GetIDP()->GetCourseDeviationFlag(), 0.0, 0.0, GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				AEPFD_dAZ_HTA( hDC, GetIDP()->FlashdeltaAZ(), GetIDP()->GetdeltaAZ() );
				AEPFD_RANGERW( hDC );
				break;
			case 602:
				AEPFD_Header( hDC, MM, false, false, false, false, false, GetIDP()->GetADIattsw(), GetIDP()->GetAutoDAPPitchState(), GetIDP()->GetAutoThrotRollYawState(), GetIDP()->GetBlankThrotRY(), GetIDP()->GetAutoSBState(), GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_MV()) Tape_MV( hDC, GetIDP()->GetVelRef(), GetIDP()->GetMach() );
				else if (GetIDP()->DrawBox_MVR()) Box_MVR( hDC, GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_EAS()) Tape_EAS( hDC, GetIDP()->GetEAS() );
				else if (GetIDP()->DrawBox_EAS()) Box_EAS( hDC, GetIDP()->GetEAS() );
				Tape_Alpha( hDC, GetIDP()->GetAlpha(), GetIDP()->GetMach() );
				Tape_H_Hdot( hDC, GetIDP()->GetAltitude(), GetIDP()->GetAltitudeRate() );
				ADI_STATIC( hDC );
				ADI( hDC, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				ADI_RATE( hDC, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
				ADI_ERROR( hDC, pitcherror, rollerror, yawerror, pitcherrorscale );
				AEPFD_GMETER_STATIC( hDC );
				AEPFD_GMETER( hDC, GetIDP()->GetAccelType(), GetIDP()->GetAccel() );
				HSI_E( hDC, GetIDP()->GetHeading(), GetIDP()->DrawCourse(), GetIDP()->GetCourse(), GetIDP()->DrawCourseDeviation(), GetIDP()->GetCourseDeviationFlag(), GetIDP()->GetCourseDeviationScale(), GetIDP()->GetCourseDeviation(), GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				AEPFD_dAZ_HTA( hDC, GetIDP()->FlashdeltaAZ(), GetIDP()->GetdeltaAZ() );
				AEPFD_RANGERW( hDC );
				AEPFD_HACCEL( hDC, GetIDP()->GetVacc() );
				break;
			case 603:
				AEPFD_Header( hDC, MM, false, false, false, false, false, GetIDP()->GetADIattsw(), GetIDP()->GetAutoDAPPitchState(), GetIDP()->GetAutoThrotRollYawState(), GetIDP()->GetBlankThrotRY(), GetIDP()->GetAutoSBState(), GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_MV()) Tape_MV( hDC, GetIDP()->GetVelRef(), GetIDP()->GetMach() );
				else if (GetIDP()->DrawBox_MVR()) Box_MVR( hDC, GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_EAS()) Tape_EAS( hDC, GetIDP()->GetEAS() );
				else if (GetIDP()->DrawBox_EAS()) Box_EAS( hDC, GetIDP()->GetEAS() );
				Tape_Alpha( hDC, GetIDP()->GetAlpha(), GetIDP()->GetMach() );
				Tape_H_Hdot( hDC, GetIDP()->GetAltitude(), GetIDP()->GetAltitudeRate() );
				ADI_STATIC( hDC );
				ADI( hDC, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				ADI_RATE( hDC, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
				ADI_ERROR( hDC, pitcherror, rollerror, yawerror, pitcherrorscale );
				AEPFD_GMETER_STATIC( hDC );
				AEPFD_GMETER( hDC, GetIDP()->GetAccelType(), GetIDP()->GetAccel() );
				HSI_E( hDC, GetIDP()->GetHeading(), GetIDP()->DrawCourse(), GetIDP()->GetCourse(), GetIDP()->DrawCourseDeviation(), GetIDP()->GetCourseDeviationFlag(), GetIDP()->GetCourseDeviationScale(), GetIDP()->GetCourseDeviation(), GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				if (GetIDP()->DrawdAZ()) AEPFD_dAZ_HTA( hDC, GetIDP()->FlashdeltaAZ(), GetIDP()->GetdeltaAZ() );
				if (GetIDP()->DrawHACC()) AEPFD_RANGEHACC( hDC, GetIDP()->GetHACCRange() );
				AEPFD_RANGERW( hDC );
				if (GetIDP()->DrawGlideSlopeDeviation()) AEPFD_GSI( hDC, GetIDP()->GetGlideSlopeDeviationFlag(), GetIDP()->GetGlideSlopeDeviationScale(), GetIDP()->GetGlideSlopeDeviation() );
				break;
			case 801:
				ADI_STATIC( hDC );
				ADI( hDC, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				break;
			case 901:
				Tapes_Invalid( hDC );
				ADI_STATIC( hDC );// TODO no rate and error scales
				ADI( hDC, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				AEPFD_GMETER_STATIC( hDC );
				HSI_E( hDC, GetIDP()->GetHeading(), GetIDP()->DrawCourse(), GetIDP()->GetCourse(), GetIDP()->DrawCourseDeviation(), GetIDP()->GetCourseDeviationFlag(), 0.0, 0.0, GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				break;
			default:
				break;
		}
		return;
	}

	void MDU::AEPFD( oapi::Sketchpad* skp )
	{
		int MM = GetIDP()->GetMM();
		int adiatt = 1;// TODO
		double sinpitch;
		double cospitch;
		double sinroll;
		double cosroll;
		double sinyaw;
		double cosyaw;
		GetIDP()->GetADIAtt( usMDUID, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
		unsigned short pitchrate;
		unsigned short rollrate;
		unsigned short yawrate;
		unsigned short pitchratescale;
		unsigned short rollratescale;
		unsigned short yawratescale;
		unsigned short TGOSEC;
		unsigned short ADIRR_0_ON_R;
		GetIDP()->GetADIRate( usMDUID, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
		unsigned short pitcherror;
		unsigned short rollerror;
		unsigned short yawerror;
		unsigned short pitcherrorscale;
		GetIDP()->GetADIError( usMDUID, pitcherror, rollerror, yawerror, pitcherrorscale );

		skp->SetFont( skpSSVAFont_h22w18 );

		switch (MM)
		{
			case 101:
				//AEPFD_Header_AscentDAP( skp, 101, adiatt );
				Tapes_Invalid( skp );
				ADI_STATIC( skp );
				ADI( skp, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				ADI_RATE( skp, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
				ADI_ERROR( skp, pitcherror, rollerror, yawerror, pitcherrorscale );
				HSI_E( skp, GetIDP()->GetHeading(), GetIDP()->DrawCourse(), GetIDP()->GetCourse(), GetIDP()->DrawCourseDeviation(), GetIDP()->GetCourseDeviationFlag(), 0.0, 0.0, GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				break;
			case 102:
				AEPFD_Header( skp, MM, false, false, false, false, false, GetIDP()->GetADIattsw(), GetIDP()->GetAutoDAPPitchState(), GetIDP()->GetAutoThrotRollYawState(), GetIDP()->GetBlankThrotRY(), GetIDP()->GetAutoSBState(), GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_MV()) Tape_MV( skp, GetIDP()->GetVelRef(), GetIDP()->GetMach() );
				else if (GetIDP()->DrawBox_MVR()) Box_MVR( skp, GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_EAS()) Tape_EAS( skp, GetIDP()->GetEAS() );
				else if (GetIDP()->DrawBox_EAS()) Box_EAS( skp, GetIDP()->GetEAS() );
				Tape_Alpha( skp, GetIDP()->GetAlpha(), 0 );
				Tape_H_Hdot( skp, GetIDP()->GetAltitude(), GetIDP()->GetAltitudeRate() );
				if (GetIDP()->DrawBeta()) AEPFD_BETA( skp, GetIDP()->GetBeta() );
				ADI_STATIC( skp );
				ADI( skp, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				ADI_RATE( skp, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
				ADI_ERROR( skp, pitcherror, rollerror, yawerror, pitcherrorscale );
				AEPFD_GMETER_STATIC( skp );
				AEPFD_GMETER( skp, GetIDP()->GetAccelType(), GetIDP()->GetAccel() );
				HSI_A( skp, GetIDP()->GetHeading(), GetIDP()->GetRollSW(), GetIDP()->DrawCourse(), GetIDP()->GetCourse(), GetIDP()->DrawCourseDeviation(), GetIDP()->GetCourseDeviationFlag(), GetIDP()->GetCourseDeviationScale(), GetIDP()->GetCourseDeviation(), GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				AEPFD_XTRK( skp );// TODO only NOM, TAL and ATO
				AEPFD_dINC( skp, GetIDP()->GetdeltaInc() );
				break;
			case 103:
				AEPFD_Header( skp, MM, false, false, false, false, false, GetIDP()->GetADIattsw(), GetIDP()->GetAutoDAPPitchState(), GetIDP()->GetAutoThrotRollYawState(), GetIDP()->GetBlankThrotRY(), GetIDP()->GetAutoSBState(), GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_MV()) Tape_MV( skp, GetIDP()->GetVelRef(), GetIDP()->GetMach() );
				else if (GetIDP()->DrawBox_MVR()) Box_MVR( skp, GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_EAS()) Tape_EAS( skp, GetIDP()->GetEAS() );
				else if (GetIDP()->DrawBox_EAS()) Box_EAS( skp, GetIDP()->GetEAS() );
				Tape_Alpha( skp, GetIDP()->GetAlpha(), 0 );
				Tape_H_Hdot( skp, GetIDP()->GetAltitude(), GetIDP()->GetAltitudeRate() );
				if (GetIDP()->DrawBeta()) AEPFD_BETA( skp, GetIDP()->GetBeta() );
				ADI_STATIC( skp );
				ADI( skp, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				ADI_RATE( skp, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
				ADI_ERROR( skp, pitcherror, rollerror, yawerror, pitcherrorscale );
				AEPFD_GMETER_STATIC( skp );
				AEPFD_GMETER( skp, GetIDP()->GetAccelType(), GetIDP()->GetAccel() );
				HSI_A( skp, GetIDP()->GetHeading(), GetIDP()->GetRollSW(), GetIDP()->DrawCourse(), GetIDP()->GetCourse(), GetIDP()->DrawCourseDeviation(), GetIDP()->GetCourseDeviationFlag(), GetIDP()->GetCourseDeviationScale(), GetIDP()->GetCourseDeviation(), GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				if (0)// TODO TAL
				{
					AEPFD_dXTRK( skp );
					AEPFD_RANGERW( skp );// fix colision between this and dINC
				}
				AEPFD_XTRK( skp );// TODO only NOM, TAL and ATO
				if (0) AEPFD_RANGERW( skp );// TODO ECAL/BDA
				AEPFD_dINC( skp, GetIDP()->GetdeltaInc() );
				if (0) AEPFD_TGTINC( skp );// TODO ATO
				break;
			case 104:
				AEPFD_Header( skp, MM, false, false, false, false, false, GetIDP()->GetADIattsw(), GetIDP()->GetAutoDAPPitchState(), GetIDP()->GetAutoThrotRollYawState(), GetIDP()->GetBlankThrotRY(), GetIDP()->GetAutoSBState(), GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_MV()) Tape_MV( skp, GetIDP()->GetVelRef(), GetIDP()->GetMach() );
				else if (GetIDP()->DrawBox_MVR()) Box_MVR( skp, GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_EAS()) Tape_EAS( skp, GetIDP()->GetEAS() );
				else if (GetIDP()->DrawBox_EAS()) Box_EAS( skp, GetIDP()->GetEAS() );
				Tape_H_Hdot( skp, GetIDP()->GetAltitude(), GetIDP()->GetAltitudeRate() );
				ADI_STATIC( skp );
				ADI( skp, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				ADI_RATE( skp, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
				ADI_ERROR( skp, pitcherror, rollerror, yawerror, pitcherrorscale );
				HSI_E( skp, GetIDP()->GetHeading(), GetIDP()->DrawCourse(), GetIDP()->GetCourse(), GetIDP()->DrawCourseDeviation(), GetIDP()->GetCourseDeviationFlag(), GetIDP()->GetCourseDeviationScale(), GetIDP()->GetCourseDeviation(), GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				AEPFD_XTRK( skp );// TODO only NOM, TAL and ATO
				AEPFD_dINC( skp, GetIDP()->GetdeltaInc() );
				break;
			case 105:
				AEPFD_Header( skp, MM, false, false, false, false, false, GetIDP()->GetADIattsw(), GetIDP()->GetAutoDAPPitchState(), GetIDP()->GetAutoThrotRollYawState(), GetIDP()->GetBlankThrotRY(), GetIDP()->GetAutoSBState(), GetIDP()->GetMach() );
				ADI_STATIC( skp );
				ADI( skp, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				ADI_RATE( skp, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
				ADI_ERROR( skp, pitcherror, rollerror, yawerror, pitcherrorscale );
				break;
			case 106:
				AEPFD_Header( skp, MM, false, false, false, false, false, GetIDP()->GetADIattsw(), GetIDP()->GetAutoDAPPitchState(), GetIDP()->GetAutoThrotRollYawState(), GetIDP()->GetBlankThrotRY(), GetIDP()->GetAutoSBState(), GetIDP()->GetMach() );
				ADI_STATIC( skp );
				ADI( skp, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				ADI_RATE( skp, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
				ADI_ERROR( skp, pitcherror, rollerror, yawerror, pitcherrorscale );
				break;
			case 201:
				ADI_STATIC( skp );
				ADI( skp, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				break;
			case 202:
				ADI_STATIC( skp );
				ADI( skp, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				break;
			case 301:
				AEPFD_Header( skp, MM, false, false, false, false, false, GetIDP()->GetADIattsw(), GetIDP()->GetAutoDAPPitchState(), GetIDP()->GetAutoThrotRollYawState(), GetIDP()->GetBlankThrotRY(), GetIDP()->GetAutoSBState(), GetIDP()->GetMach() );
				ADI_STATIC( skp );
				ADI( skp, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				ADI_RATE( skp, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
				ADI_ERROR( skp, pitcherror, rollerror, yawerror, pitcherrorscale );
				break;
			case 302:
				AEPFD_Header( skp, MM, false, false, false, false, false, GetIDP()->GetADIattsw(), GetIDP()->GetAutoDAPPitchState(), GetIDP()->GetAutoThrotRollYawState(), GetIDP()->GetBlankThrotRY(), GetIDP()->GetAutoSBState(), GetIDP()->GetMach() );
				ADI_STATIC( skp );
				ADI( skp, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				ADI_RATE( skp, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
				ADI_ERROR( skp, pitcherror, rollerror, yawerror, pitcherrorscale );
				break;
			case 303:
				AEPFD_Header( skp, MM, false, false, false, false, false, GetIDP()->GetADIattsw(), GetIDP()->GetAutoDAPPitchState(), GetIDP()->GetAutoThrotRollYawState(), GetIDP()->GetBlankThrotRY(), GetIDP()->GetAutoSBState(), GetIDP()->GetMach() );
				ADI_STATIC( skp );
				ADI( skp, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				ADI_RATE( skp, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
				ADI_ERROR( skp, pitcherror, rollerror, yawerror, pitcherrorscale );
				break;
			case 304:
				AEPFD_Header( skp, MM, false, false, false, false, false, GetIDP()->GetADIattsw(), GetIDP()->GetAutoDAPPitchState(), GetIDP()->GetAutoThrotRollYawState(), GetIDP()->GetBlankThrotRY(), GetIDP()->GetAutoSBState(), GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_MV()) Tape_MV( skp, GetIDP()->GetVelRef(), GetIDP()->GetMach() );
				else if (GetIDP()->DrawBox_MVR()) Box_MVR( skp, GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_EAS()) Tape_EAS( skp, GetIDP()->GetEAS() );
				else if (GetIDP()->DrawBox_EAS()) Box_EAS( skp, GetIDP()->GetEAS() );
				Tape_Alpha( skp, GetIDP()->GetAlpha(), GetIDP()->GetMach() );
				Tape_H_Hdot( skp, GetIDP()->GetAltitude(), GetIDP()->GetAltitudeRate() );
				ADI_STATIC( skp );
				ADI( skp, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				ADI_RATE( skp, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
				ADI_ERROR( skp, pitcherror, rollerror, yawerror, pitcherrorscale );
				AEPFD_GMETER_STATIC( skp );
				AEPFD_GMETER( skp, GetIDP()->GetAccelType(), GetIDP()->GetAccel() );
				HSI_E( skp, GetIDP()->GetHeading(), GetIDP()->DrawCourse(), GetIDP()->GetCourse(), GetIDP()->DrawCourseDeviation(), GetIDP()->GetCourseDeviationFlag(), GetIDP()->GetCourseDeviationScale(), GetIDP()->GetCourseDeviation(), GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				AEPFD_dAZ_HTA( skp, GetIDP()->FlashdeltaAZ(), GetIDP()->GetdeltaAZ() );
				AEPFD_RANGERW( skp );
				AEPFD_HACCEL( skp, GetIDP()->GetVacc() );
				break;
			case 305:
				AEPFD_Header( skp, MM, false, false, false, false, false, GetIDP()->GetADIattsw(), GetIDP()->GetAutoDAPPitchState(), GetIDP()->GetAutoThrotRollYawState(), GetIDP()->GetBlankThrotRY(), GetIDP()->GetAutoSBState(), GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_MV()) Tape_MV( skp, GetIDP()->GetVelRef(), GetIDP()->GetMach() );
				else if (GetIDP()->DrawBox_MVR()) Box_MVR( skp, GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_EAS()) Tape_EAS( skp, GetIDP()->GetEAS() );
				else if (GetIDP()->DrawBox_EAS()) Box_EAS( skp, GetIDP()->GetEAS() );
				Tape_Alpha( skp, GetIDP()->GetAlpha(), GetIDP()->GetMach() );
				Tape_H_Hdot( skp, GetIDP()->GetAltitude(), GetIDP()->GetAltitudeRate() );
				ADI_STATIC( skp );
				ADI( skp, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				ADI_RATE( skp, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
				ADI_ERROR( skp, pitcherror, rollerror, yawerror, pitcherrorscale );
				AEPFD_GMETER_STATIC( skp );
				AEPFD_GMETER( skp, GetIDP()->GetAccelType(), GetIDP()->GetAccel() );
				HSI_E( skp, GetIDP()->GetHeading(), GetIDP()->DrawCourse(), GetIDP()->GetCourse(), GetIDP()->DrawCourseDeviation(), GetIDP()->GetCourseDeviationFlag(), GetIDP()->GetCourseDeviationScale(), GetIDP()->GetCourseDeviation(), GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				if (GetIDP()->DrawdAZ()) AEPFD_dAZ_HTA( skp, GetIDP()->FlashdeltaAZ(), GetIDP()->GetdeltaAZ() );
				if (GetIDP()->DrawHACC()) AEPFD_RANGEHACC( skp, GetIDP()->GetHACCRange() );
				AEPFD_RANGERW( skp );
				if (GetIDP()->DrawGlideSlopeDeviation()) AEPFD_GSI( skp, GetIDP()->GetGlideSlopeDeviationFlag(), GetIDP()->GetGlideSlopeDeviationScale(), GetIDP()->GetGlideSlopeDeviation() );
				break;
			case 601:
				AEPFD_Header( skp, MM, false, false, false, false, false, GetIDP()->GetADIattsw(), GetIDP()->GetAutoDAPPitchState(), GetIDP()->GetAutoThrotRollYawState(), GetIDP()->GetBlankThrotRY(), GetIDP()->GetAutoSBState(), GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_MV()) Tape_MV( skp, GetIDP()->GetVelRef(), GetIDP()->GetMach() );
				else if (GetIDP()->DrawBox_MVR()) Box_MVR( skp, GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_EAS()) Tape_EAS( skp, GetIDP()->GetEAS() );
				else if (GetIDP()->DrawBox_EAS()) Box_EAS( skp, GetIDP()->GetEAS() );
				Tape_Alpha( skp, GetIDP()->GetAlpha(), 0 );
				Tape_H_Hdot( skp, GetIDP()->GetAltitude(), GetIDP()->GetAltitudeRate() );
				AEPFD_BETA( skp, GetIDP()->GetBeta() );
				ADI_STATIC( skp );
				ADI( skp, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				ADI_RATE( skp, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
				ADI_ERROR( skp, pitcherror, rollerror, yawerror, pitcherrorscale );
				AEPFD_GMETER_STATIC( skp );
				AEPFD_GMETER( skp, GetIDP()->GetAccelType(), GetIDP()->GetAccel() );
				HSI_E( skp, GetIDP()->GetHeading(), GetIDP()->DrawCourse(), GetIDP()->GetCourse(), GetIDP()->DrawCourseDeviation(), GetIDP()->GetCourseDeviationFlag(), 0.0, 0.0, GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				AEPFD_dAZ_HTA( skp, GetIDP()->FlashdeltaAZ(), GetIDP()->GetdeltaAZ() );
				AEPFD_RANGERW( skp );
				break;
			case 602:
				AEPFD_Header( skp, MM, false, false, false, false, false, GetIDP()->GetADIattsw(), GetIDP()->GetAutoDAPPitchState(), GetIDP()->GetAutoThrotRollYawState(), GetIDP()->GetBlankThrotRY(), GetIDP()->GetAutoSBState(), GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_MV()) Tape_MV( skp, GetIDP()->GetVelRef(), GetIDP()->GetMach() );
				else if (GetIDP()->DrawBox_MVR()) Box_MVR( skp, GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_EAS()) Tape_EAS( skp, GetIDP()->GetEAS() );
				else if (GetIDP()->DrawBox_EAS()) Box_EAS( skp, GetIDP()->GetEAS() );
				Tape_Alpha( skp, GetIDP()->GetAlpha(), GetIDP()->GetMach() );
				Tape_H_Hdot( skp, GetIDP()->GetAltitude(), GetIDP()->GetAltitudeRate() );
				ADI_STATIC( skp );
				ADI( skp, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				ADI_RATE( skp, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
				ADI_ERROR( skp, pitcherror, rollerror, yawerror, pitcherrorscale );
				AEPFD_GMETER_STATIC( skp );
				AEPFD_GMETER( skp, GetIDP()->GetAccelType(), GetIDP()->GetAccel() );
				HSI_E( skp, GetIDP()->GetHeading(), GetIDP()->DrawCourse(), GetIDP()->GetCourse(), GetIDP()->DrawCourseDeviation(), GetIDP()->GetCourseDeviationFlag(), GetIDP()->GetCourseDeviationScale(), GetIDP()->GetCourseDeviation(), GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				AEPFD_dAZ_HTA( skp, GetIDP()->FlashdeltaAZ(), GetIDP()->GetdeltaAZ() );
				AEPFD_RANGERW( skp );
				AEPFD_HACCEL( skp, GetIDP()->GetVacc() );
				break;
			case 603:
				AEPFD_Header( skp, MM, false, false, false, false, false, GetIDP()->GetADIattsw(), GetIDP()->GetAutoDAPPitchState(), GetIDP()->GetAutoThrotRollYawState(), GetIDP()->GetBlankThrotRY(), GetIDP()->GetAutoSBState(), GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_MV()) Tape_MV( skp, GetIDP()->GetVelRef(), GetIDP()->GetMach() );
				else if (GetIDP()->DrawBox_MVR()) Box_MVR( skp, GetIDP()->GetMach() );
				if (GetIDP()->DrawTape_EAS()) Tape_EAS( skp, GetIDP()->GetEAS() );
				else if (GetIDP()->DrawBox_EAS()) Box_EAS( skp, GetIDP()->GetEAS() );
				Tape_Alpha( skp, GetIDP()->GetAlpha(), GetIDP()->GetMach() );
				Tape_H_Hdot( skp, GetIDP()->GetAltitude(), GetIDP()->GetAltitudeRate() );
				ADI_STATIC( skp );
				ADI( skp, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				ADI_RATE( skp, pitchrate, rollrate, yawrate, pitchratescale, rollratescale, yawratescale, TGOSEC, ADIRR_0_ON_R );
				ADI_ERROR( skp, pitcherror, rollerror, yawerror, pitcherrorscale );
				AEPFD_GMETER_STATIC( skp );
				AEPFD_GMETER( skp, GetIDP()->GetAccelType(), GetIDP()->GetAccel() );
				HSI_E( skp, GetIDP()->GetHeading(), GetIDP()->DrawCourse(), GetIDP()->GetCourse(), GetIDP()->DrawCourseDeviation(), GetIDP()->GetCourseDeviationFlag(), GetIDP()->GetCourseDeviationScale(), GetIDP()->GetCourseDeviation(), GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				if (GetIDP()->DrawdAZ()) AEPFD_dAZ_HTA( skp, GetIDP()->FlashdeltaAZ(), GetIDP()->GetdeltaAZ() );
				if (GetIDP()->DrawHACC()) AEPFD_RANGEHACC( skp, GetIDP()->GetHACCRange() );
				AEPFD_RANGERW( skp );
				if (GetIDP()->DrawGlideSlopeDeviation()) AEPFD_GSI( skp, GetIDP()->GetGlideSlopeDeviationFlag(), GetIDP()->GetGlideSlopeDeviationScale(), GetIDP()->GetGlideSlopeDeviation() );
				break;
			case 801:
				ADI_STATIC( skp );
				ADI( skp, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				break;
			case 901:
				Tapes_Invalid( skp );
				ADI_STATIC( skp );// TODO no rate and error scales
				ADI( skp, sinpitch, cospitch, sinroll, cosroll, sinyaw, cosyaw );
				AEPFD_GMETER_STATIC( skp );
				HSI_E( skp, GetIDP()->GetHeading(), GetIDP()->DrawCourse(), GetIDP()->GetCourse(), GetIDP()->DrawCourseDeviation(), GetIDP()->GetCourseDeviationFlag(), 0.0, 0.0, GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				break;
			default:
				break;
		}
		return;
	}

	void MDU::CreateTapes_GDI( void )
	{
		if (hDC_Tape_MACHV) return;// already created

		// draw tapes
		int offset_top = 216;
		int offset_bottom = 220;
		char cbuf[8];
		int y = 0;
		int save;

		// Mach/V
		// 0.75K in window (1fps = 0.5786px) (4-27K)
		// M0.75 in window (M1 = 578.6px) (0-4)
		// 13307.8 + 2314.4 = 15622.2px + offsets
		// (should be +/- 0.7K and M0.7 but it needs a surface too big for D3D9)
		hDC_Tape_MACHV = CreateCompatibleDC( GetDC( NULL ) );
		HBITMAP hBM = CreateCompatibleBitmap( GetDC( NULL ), 86, 15622 + offset_top + offset_bottom );
		hBM_Tape_MACHV_tmp = (HBITMAP)SelectObject( hDC_Tape_MACHV, hBM );
		save = SaveDC( hDC_Tape_MACHV );

		SelectObject( hDC_Tape_MACHV, gdiWhitePen );
		SelectObject( hDC_Tape_MACHV, gdiWhiteBrush );
		Rectangle( hDC_Tape_MACHV, 0, 0, 86, 15622 + offset_top + offset_bottom );

		SetTextColor( hDC_Tape_MACHV, CR_BLACK );
		SetTextAlign( hDC_Tape_MACHV, TA_CENTER );
		SelectObject( hDC_Tape_MACHV, gdiSSVBFont_h36w18 );
		SetBkMode( hDC_Tape_MACHV, TRANSPARENT );
		SelectObject( hDC_Tape_MACHV, gdiBlackPen );

		for (int i = 270; i >= 41; i -= 1)
		{
			y = Round( ((270 - i) * 57.86) + offset_top );

			if ((i % 10) == 0)
			{
				sprintf_s( cbuf, 8, "%.1fK", (double)i / 10 );
				TextOut( hDC_Tape_MACHV, 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else if ((i % 2) == 0)
			{
				sprintf_s( cbuf, 8, "%.1f", (double)i / 10 );
				TextOut( hDC_Tape_MACHV, 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else
			{
				MoveToEx( hDC_Tape_MACHV, 0, y, NULL );
				LineTo( hDC_Tape_MACHV, 28, y );
			}
		}
		for (int i = 40; i >= 0; i--)
		{
			y = Round( ((40 - i) * 57.86) + 13307.8 + offset_top );

			if ((i % 2) == 0)
			{
				if ((i % 10) == 0)
				{
					sprintf_s( cbuf, 8, "%.1fM", (double)i / 10 );
					TextOut( hDC_Tape_MACHV, 44, y - 22, cbuf, strlen( cbuf ) );
				}
				else
				{
					sprintf_s( cbuf, 8, "%.1f", (double)i / 10 );
					TextOut( hDC_Tape_MACHV, 44, y - 22, cbuf, strlen( cbuf ) );
				}
			}
			else
			{
				MoveToEx( hDC_Tape_MACHV, 20, y, NULL );
				LineTo( hDC_Tape_MACHV, 66, y );
			}
		}
		RestoreDC( hDC_Tape_MACHV, save );


		// KEAS
		// 28KEAS in window (1KEAS = 15.5px) (500-0)
		// 7750px + offsets
		hDC_Tape_KEAS = CreateCompatibleDC( GetDC( NULL ) );
		hBM = CreateCompatibleBitmap( GetDC( NULL ), 86, 7750 + offset_top + offset_bottom );
		hBM_Tape_KEAS_tmp = (HBITMAP)SelectObject( hDC_Tape_KEAS, hBM );
		save = SaveDC( hDC_Tape_KEAS );

		SelectObject( hDC_Tape_KEAS, gdiWhitePen );
		SelectObject( hDC_Tape_KEAS, gdiWhiteBrush );
		Rectangle( hDC_Tape_KEAS, 0, 0, 86, 7750 + offset_top + offset_bottom );

		SetTextColor( hDC_Tape_KEAS, CR_BLACK );
		SetTextAlign( hDC_Tape_KEAS, TA_CENTER );
		SelectObject( hDC_Tape_KEAS, gdiSSVBFont_h36w18 );
		SetBkMode( hDC_Tape_KEAS, TRANSPARENT );
		SelectObject( hDC_Tape_KEAS, gdiBlackPen );

		for (int i = 500; i >= 0; i -= 5)
		{
			y = Round( ((500 - i) * 15.5) + offset_top );

			if ((i % 10) == 0)
			{
				sprintf_s( cbuf, 8, "%d", i );
				TextOut( hDC_Tape_KEAS, 42, y - 22, cbuf, strlen( cbuf ) );
			}
			else
			{
				MoveToEx( hDC_Tape_KEAS, 20, y, NULL );
				LineTo( hDC_Tape_KEAS, 66, y );
			}
		}
		RestoreDC( hDC_Tape_KEAS, save );


		// alpha
		// 23º in window (1º = 18.87px)
		// 6792px long + offsets
		// just graphics "base" creation, actual painting is done elsewhere
		hDC_Tape_Alpha = CreateCompatibleDC( GetDC( NULL ) );
		hBM = CreateCompatibleBitmap( GetDC( NULL ), 86, 6792 + offset_top + offset_bottom );
		hBM_Tape_Alpha_tmp = (HBITMAP)SelectObject( hDC_Tape_Alpha, hBM );


		// H
		// NM scale 10NM in window (1NM = 43.4px) (165-65.83137NM)
		// FT scale 70Kft in window (1ft = 0.0062px) (400-100Kft)
		// FT scale 11.5Kft in window (1ft = 0.03774px) (100-30Kft)
		// FT scale 5.5Kft in window (1ft = 0.0789px) n1(n5K)/n1000 m0.5 (30-2Kft)
		// FT scale 1400ft in window (1ft = 0.31px) (2000-200ft)
		// FT scale 200ft in window (1ft = 2.17px) n50m10 (200-0ft)
		// FT scale 450ft in window (1ft = 0.9644px) (0-(-1100)ft)
		// 4303.918 + 1860 + 2641.8 + 2209.2 + 558 + 434 + 1060.84 = 13067.758px long + offsets
		hDC_Tape_H = CreateCompatibleDC( GetDC( NULL ) );
		hBM = CreateCompatibleBitmap( GetDC( NULL ), 86, 13068 + offset_top + offset_bottom );
		hBM_Tape_H_tmp = (HBITMAP)SelectObject( hDC_Tape_H, hBM );
		save = SaveDC( hDC_Tape_H );

		SelectObject( hDC_Tape_H, gdiWhitePen );
		SelectObject( hDC_Tape_H, gdiWhiteBrush );
		Rectangle( hDC_Tape_H, 0, 0, 86, 11014 + offset_top );

		SelectObject( hDC_Tape_H, gdiYellowPen );
		SelectObject( hDC_Tape_H, gdiYellowBrush );
		Rectangle( hDC_Tape_H, 0, 11014 + offset_top, 86, 12006 + offset_top );

		SelectObject( hDC_Tape_H, gdiDarkGrayPen );
		SelectObject( hDC_Tape_H, gdiDarkGrayBrush );
		Rectangle( hDC_Tape_H, 0, 12006 + offset_top, 86, 13068 + offset_top + offset_bottom );

		SetTextColor( hDC_Tape_H, CR_BLACK );
		SetTextAlign( hDC_Tape_H, TA_CENTER );
		SelectObject( hDC_Tape_H, gdiSSVBFont_h36w18 );
		SetBkMode( hDC_Tape_H, TRANSPARENT );
		SelectObject( hDC_Tape_H, gdiBlackPen );

		for (int i = 165; i >= 67; i--)
		{
			y = Round( ((165 - i) * 43.4) + offset_top );

			if ((i % 5) == 0)
			{
				sprintf_s( cbuf, 8, "%dM", i );
				TextOut( hDC_Tape_H, 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else
			{
				MoveToEx( hDC_Tape_H, 58, y, NULL );
				LineTo( hDC_Tape_H, 86, y );
			}
		}
		for (int i = 400; i >= 100; i -= 5)
		{
			y = Round( ((400 - i) * 6.2) + offset_top + 4303.918 );

			if ((i % 50) == 0)
			{
				sprintf_s( cbuf, 8, "%dK", i );
				TextOut( hDC_Tape_H, 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else if ((i % 10) == 0)
			{
				MoveToEx( hDC_Tape_H, 0, y, NULL );
				LineTo( hDC_Tape_H, 30, y );
			}
		}
		for (int i = 99; i >= 30; i--)
		{
			y = Round( ((100 - i) * 37.74) + offset_top + 6163.918 );

			if ((i % 5) == 0)
			{
				sprintf_s( cbuf, 8, "%dK", i );
				TextOut( hDC_Tape_H, 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else
			{
				MoveToEx( hDC_Tape_H, 28, y, NULL );
				LineTo( hDC_Tape_H, 58, y );
			}
		}
		for (int i = 295; i > 20; i -= 5)
		{
			y = Round( ((300 - i) * 7.89) + offset_top + 8805.718 );

			if ((i % 50) == 0)
			{
				sprintf_s( cbuf, 8, "%.0fK", (double)i / 10 );
				TextOut( hDC_Tape_H, 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else if ((i % 10) == 0)
			{
				if (i > 40) sprintf_s( cbuf, 8, "%.0f", (double)i / 10 );
				else sprintf_s( cbuf, 8, "%d", i * 100 );
				TextOut( hDC_Tape_H, 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else
			{
				MoveToEx( hDC_Tape_H, 28, y, NULL );
				LineTo( hDC_Tape_H, 58, y );
			}
		}

		for (int i = 20; i > 2; i -= 1)
		{
			y = Round( ((20 - i) * 31) + offset_top + 11014.918 );

			if ((i % 2) == 0)
			{
				sprintf_s( cbuf, 8, "%d", i * 100 );
				TextOut( hDC_Tape_H, 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else
			{
				MoveToEx( hDC_Tape_H, 28, y, NULL );
				LineTo( hDC_Tape_H, 58, y );
			}
		}
		for (int i = 20; i >= 0; i -= 1)
		{
			y = Round( ((20 - i) * 21.7) + offset_top + 11572.918 );

			if ((i % 5) == 0)
			{
				sprintf_s( cbuf, 8, "%d", i * 10 );
				TextOut( hDC_Tape_H, 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else
			{
				MoveToEx( hDC_Tape_H, 28, y, NULL );
				LineTo( hDC_Tape_H, 58, y );
			}
		}

		SetTextColor( hDC_Tape_H, CR_WHITE );
		SelectObject( hDC_Tape_H, gdiWhitePen );

		for (int i = 0; i >= -110; i -= 5)
		{
			y = Round( (-i * 9.644) + offset_top + 12006.918 );

			if ((i % 10) == 0)
			{
				sprintf_s( cbuf, 8, "%d", i * 10 );
				TextOut( hDC_Tape_H, 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else
			{
				MoveToEx( hDC_Tape_H, 20, y, NULL );
				LineTo( hDC_Tape_H, 66, y );
			}
		}
		RestoreDC( hDC_Tape_H, save );


		// Hdot
		// small (inner) scale 165ft in window (1ft = 2.63px) (800-(-800))
		// large (outer) scale 700ft in window (1ft = 0.62px) (3000-800/(-800)-(-3000))
		// 1364 + 4208 + 1364 = 6936px long + offsets
		hDC_Tape_Hdot = CreateCompatibleDC( GetDC( NULL ) );
		hBM = CreateCompatibleBitmap( GetDC( NULL ), 86, 6936 + offset_top + offset_bottom );
		hBM_Tape_Hdot_tmp = (HBITMAP)SelectObject( hDC_Tape_Hdot, hBM );
		save = SaveDC( hDC_Tape_Hdot );

		SelectObject( hDC_Tape_Hdot, gdiWhitePen );
		SelectObject( hDC_Tape_Hdot, gdiWhiteBrush );
		Rectangle( hDC_Tape_Hdot, 0, 0, 86, 3468 + offset_top );

		SelectObject( hDC_Tape_Hdot, gdiDarkGrayPen );
		SelectObject( hDC_Tape_Hdot, gdiDarkGrayBrush );
		Rectangle( hDC_Tape_Hdot, 0, 3468 + offset_top, 86, 6936 + offset_top + offset_bottom );

		SetTextColor( hDC_Tape_Hdot, CR_BLACK );
		SetTextAlign( hDC_Tape_Hdot, TA_CENTER );
		SelectObject( hDC_Tape_Hdot, gdiSSVBFont_h36w18 );
		SetBkMode( hDC_Tape_Hdot, TRANSPARENT );
		SelectObject( hDC_Tape_Hdot, gdiBlackPen );

		for (int i = 30; i >= 8; i--)
		{
			y = ((30 - i) * 62) + offset_top;//y = Round( ((30 - i) * 62) + offset_top );

			if (i < 10)
			{
				sprintf_s( cbuf, 8, "%d", i * 100 );
				TextOut( hDC_Tape_Hdot, 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else if ((i % 5) == 0)
			{
				sprintf_s( cbuf, 8, "%.1fK", (double)i / 10 );
				TextOut( hDC_Tape_Hdot, 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else
			{
				MoveToEx( hDC_Tape_Hdot, 24, y, NULL );
				LineTo( hDC_Tape_Hdot, 62, y );
			}
		}
		for (int i = 80; i > 0; i--)
		{
			y = Round( ((80 - i) * 26.3) + 1364 + offset_top );

			if ((i % 2) == 0)
			{
				sprintf_s( cbuf, 8, "%d", i * 10 );
				TextOut( hDC_Tape_Hdot, 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else
			{
				MoveToEx( hDC_Tape_Hdot, 24, y, NULL );
				LineTo( hDC_Tape_Hdot, 62, y );
			}
		}

		SetTextColor( hDC_Tape_Hdot, CR_WHITE );
		SelectObject( hDC_Tape_Hdot, gdiWhitePen );

		for (int i = 0; i >= -80; i--)
		{
			y = Round( ((80 - i) * 26.3) + 1364 + offset_top );

			if ((i % 2) == 0)
			{
				sprintf_s( cbuf, 8, "%d", i * 10 );
				TextOut( hDC_Tape_Hdot, 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else
			{
				MoveToEx( hDC_Tape_Hdot, 24, y, NULL );
				LineTo( hDC_Tape_Hdot, 62, y );
			}
		}
		for (int i = -8; i >= -30; i--)
		{
			y = ((-8 - i) * 62) + 5572 + offset_top;//y = Round( ((-8 - i) * 62) + 5572 + offset_top );

			if (i > -10)
			{
				sprintf_s( cbuf, 8, "%d", i * 100 );
				TextOut( hDC_Tape_Hdot, 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else if ((i % 5) == 0)
			{
				sprintf_s( cbuf, 8, "%.1fK", (double)i / 10 );
				TextOut( hDC_Tape_Hdot, 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else
			{
				MoveToEx( hDC_Tape_Hdot, 24, y, NULL );
				LineTo( hDC_Tape_Hdot, 62, y );
			}
		}
		RestoreDC( hDC_Tape_Hdot, save );
		return;
	}

	void MDU::CreateTapes_Sketchpad( void )
	{
		if (sfh_Tape_MACHV) return;// already created

		// draw tapes
		int offset_top = 216;
		int offset_bottom = 220;
		char cbuf[8];
		int y = 0;

		// Mach/V
		// 0.75K in window (1fps = 0.5786px) (4-27K)
		// M0.75 in window (M1 = 578.6px) (0-4)
		// 13307.8 + 2314.4 = 15622.2px + offsets
		// (should be +/- 0.7K and M0.7 but it needs a surface too big for D3D9)
		sfh_Tape_MACHV = oapiCreateSurfaceEx( 86, 15622 + offset_top + offset_bottom, OAPISURFACE_TEXTURE | OAPISURFACE_RENDERTARGET | OAPISURFACE_NOMIPMAPS );
		oapi::Sketchpad* skp_Tape_MACHV = oapiGetSketchpad( sfh_Tape_MACHV );

		skp_Tape_MACHV->SetPen( skpWhitePen );
		skp_Tape_MACHV->SetBrush( skpWhiteBrush );
		skp_Tape_MACHV->Rectangle( 0, 0, 86, 15622 + offset_top + offset_bottom );

		skp_Tape_MACHV->SetTextColor( CR_BLACK );
		skp_Tape_MACHV->SetTextAlign( oapi::Sketchpad::CENTER );
		skp_Tape_MACHV->SetFont( skpSSVBFont_h36w18 );
		skp_Tape_MACHV->SetBackgroundColor( oapi::Sketchpad::BK_TRANSPARENT );
		skp_Tape_MACHV->SetPen( skpBlackPen );

		for (int i = 270; i >= 41; i -= 1)
		{
			y = Round( ((270 - i) * 57.86) + offset_top );

			if ((i % 10) == 0)
			{
				sprintf_s( cbuf, 8, "%.1fK", (double)i / 10 );
				skp_Tape_MACHV->Text( 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else if ((i % 2) == 0)
			{
				sprintf_s( cbuf, 8, "%.1f", (double)i / 10 );
				skp_Tape_MACHV->Text( 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else skp_Tape_MACHV->Line( 0, y, 28, y );
		}
		for (int i = 40; i >= 0; i--)
		{
			y = Round( ((40 - i) * 57.86) + 13307.8 + offset_top );

			if ((i % 2) == 0)
			{
				if ((i % 10) == 0)
				{
					sprintf_s( cbuf, 8, "%.1fM", (double)i / 10 );
					skp_Tape_MACHV->Text( 44, y - 22, cbuf, strlen( cbuf ) );
				}
				else
				{
					sprintf_s( cbuf, 8, "%.1f", (double)i / 10 );
					skp_Tape_MACHV->Text( 44, y - 22, cbuf, strlen( cbuf ) );
				}
			}
			else skp_Tape_MACHV->Line( 20, y, 66, y );
		}
		oapiReleaseSketchpad( skp_Tape_MACHV );

		// KEAS
		// 28KEAS in window (1KEAS = 15.5px) (500-0)
		// 7750px + offsets
		sfh_Tape_KEAS = oapiCreateSurfaceEx( 86, 7750 + offset_top + offset_bottom, OAPISURFACE_TEXTURE | OAPISURFACE_RENDERTARGET | OAPISURFACE_NOMIPMAPS );
		oapi::Sketchpad* skp_Tape_KEAS = oapiGetSketchpad( sfh_Tape_KEAS );

		skp_Tape_KEAS->SetPen( skpWhitePen );
		skp_Tape_KEAS->SetBrush( skpWhiteBrush );
		skp_Tape_KEAS->Rectangle( 0, 0, 86, 7750 + offset_top + offset_bottom );

		skp_Tape_KEAS->SetTextColor( CR_BLACK );
		skp_Tape_KEAS->SetTextAlign( oapi::Sketchpad::CENTER );
		skp_Tape_KEAS->SetFont( skpSSVBFont_h36w18 );
		skp_Tape_KEAS->SetBackgroundColor( oapi::Sketchpad::BK_TRANSPARENT );
		skp_Tape_KEAS->SetPen( skpBlackPen );

		for (int i = 500; i >= 0; i -= 5)
		{
			y = Round( ((500 - i) * 15.5) + offset_top );

			if ((i % 10) == 0)
			{
				sprintf_s( cbuf, 8, "%d", i );
				skp_Tape_KEAS->Text( 42, y - 22, cbuf, strlen( cbuf ) );
			}
			else skp_Tape_KEAS->Line( 20, y, 66, y );
		}
		oapiReleaseSketchpad( skp_Tape_KEAS );

		// alpha
		// 23º in window (1º = 18.87px)
		// 6792px long + offsets
		// just graphics "base" creation, actual painting is done elsewhere
		sfh_Tape_Alpha = oapiCreateSurfaceEx( 86, 6792 + offset_top + offset_bottom, OAPISURFACE_TEXTURE | OAPISURFACE_RENDERTARGET | OAPISURFACE_NOMIPMAPS );


		// H
		// NM scale 10NM in window (1NM = 43.4px) (165-65.83137NM)
		// FT scale 70Kft in window (1ft = 0.0062px) (400-100Kft)
		// FT scale 11.5Kft in window (1ft = 0.03774px) (100-30Kft)
		// FT scale 5.5Kft in window (1ft = 0.0789px) n1(n5K)/n1000 m0.5 (30-2Kft)
		// FT scale 1400ft in window (1ft = 0.31px) (2000-200ft)
		// FT scale 200ft in window (1ft = 2.17px) n50m10 (200-0ft)
		// FT scale 450ft in window (1ft = 0.9644px) (0-(-1100)ft)
		// 4303.918 + 1860 + 2641.8 + 2209.2 + 558 + 434 + 1060.84 = 13067.758px long + offsets
		sfh_Tape_H = oapiCreateSurfaceEx( 86, 13068 + offset_top + offset_bottom, OAPISURFACE_TEXTURE | OAPISURFACE_RENDERTARGET | OAPISURFACE_NOMIPMAPS );
		oapi::Sketchpad* skp_Tape_H = oapiGetSketchpad( sfh_Tape_H );

		skp_Tape_H->SetPen( skpWhitePen );
		skp_Tape_H->SetBrush( skpWhiteBrush );
		skp_Tape_H->Rectangle( 0, 0, 86, 11014 + offset_top );

		skp_Tape_H->SetPen( skpYellowPen );
		skp_Tape_H->SetBrush( skpYellowBrush );
		skp_Tape_H->Rectangle( 0, 11014 + offset_top, 86, 12006 + offset_top );

		skp_Tape_H->SetPen( skpDarkGrayPen );
		skp_Tape_H->SetBrush( skpDarkGrayBrush );
		skp_Tape_H->Rectangle( 0, 12006 + offset_top, 86, 13068 + offset_top + offset_bottom );

		skp_Tape_H->SetTextColor( CR_BLACK );
		skp_Tape_H->SetTextAlign( oapi::Sketchpad::CENTER );
		skp_Tape_H->SetFont( skpSSVBFont_h36w18 );
		skp_Tape_H->SetBackgroundColor( oapi::Sketchpad::BK_TRANSPARENT );
		skp_Tape_H->SetPen( skpBlackPen );

		for (int i = 165; i >= 67; i--)
		{
			y = Round( ((165 - i) * 43.4) + offset_top );

			if ((i % 5) == 0)
			{
				sprintf_s( cbuf, 8, "%dM", i );
				skp_Tape_H->Text( 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else skp_Tape_H->Line( 58, y, 86, y );
		}
		for (int i = 400; i >= 100; i -= 5)
		{
			y = Round( ((400 - i) * 6.2) + offset_top + 4303.918 );

			if ((i % 50) == 0)
			{
				sprintf_s( cbuf, 8, "%dK", i );
				skp_Tape_H->Text( 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else if ((i % 10) == 0) skp_Tape_H->Line( 0, y, 30, y );
		}
		for (int i = 99; i >= 30; i--)
		{
			y = Round( ((100 - i) * 37.74) + offset_top + 6163.918 );

			if ((i % 5) == 0)
			{
				sprintf_s( cbuf, 8, "%dK", i );
				skp_Tape_H->Text( 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else skp_Tape_H->Line( 28, y, 58, y );
		}
		for (int i = 295; i > 20; i -= 5)
		{
			y = Round( ((300 - i) * 7.89) + offset_top + 8805.718 );

			if ((i % 50) == 0)
			{
				sprintf_s( cbuf, 8, "%.0fK", (double)i / 10 );
				skp_Tape_H->Text( 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else if ((i % 10) == 0)
			{
				if (i > 40) sprintf_s( cbuf, 8, "%.0f", (double)i / 10 );
				else sprintf_s( cbuf, 8, "%d", i * 100 );
				skp_Tape_H->Text( 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else skp_Tape_H->Line( 28, y, 58, y );
		}

		for (int i = 20; i > 2; i -= 1)
		{
			y = Round( ((20 - i) * 31) + offset_top + 11014.918 );

			if ((i % 2) == 0)
			{
				sprintf_s( cbuf, 8, "%d", i * 100 );
				skp_Tape_H->Text( 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else skp_Tape_H->Line( 28, y, 58, y );
		}
		for (int i = 20; i >= 0; i -= 1)
		{
			y = Round( ((20 - i) * 21.7) + offset_top + 11572.918 );

			if ((i % 5) == 0)
			{
				sprintf_s( cbuf, 8, "%d", i * 10 );
				skp_Tape_H->Text( 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else skp_Tape_H->Line( 28, y, 58, y );
		}

		skp_Tape_H->SetTextColor( CR_WHITE );
		skp_Tape_H->SetPen( skpWhitePen );

		for (int i = 0; i >= -110; i -= 5)
		{
			y = Round( (-i * 9.644) + offset_top + 12006.918 );

			if ((i % 10) == 0)
			{
				sprintf_s( cbuf, 8, "%d", i * 10 );
				skp_Tape_H->Text( 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else skp_Tape_H->Line( 20, y, 66, y );
		}
		oapiReleaseSketchpad( skp_Tape_H );


		// Hdot
		// small (inner) scale 165ft in window (1ft = 2.63px) (800-(-800))
		// large (outer) scale 700ft in window (1ft = 0.62px) (3000-800/(-800)-(-3000))
		// 1364 + 4208 + 1364 = 6936px long + offsets
		sfh_Tape_Hdot = oapiCreateSurfaceEx( 86, 6936 + offset_top + offset_bottom, OAPISURFACE_TEXTURE | OAPISURFACE_RENDERTARGET | OAPISURFACE_NOMIPMAPS );
		oapi::Sketchpad* skp_Tape_Hdot = oapiGetSketchpad( sfh_Tape_Hdot );

		skp_Tape_Hdot->SetPen( skpWhitePen );
		skp_Tape_Hdot->SetBrush( skpWhiteBrush );
		skp_Tape_Hdot->Rectangle( 0, 0, 86, 3468 + offset_top );

		skp_Tape_Hdot->SetPen( skpDarkGrayPen );
		skp_Tape_Hdot->SetBrush( skpDarkGrayBrush );
		skp_Tape_Hdot->Rectangle( 0, 3468 + offset_top, 86, 6936 + offset_top + offset_bottom );

		skp_Tape_Hdot->SetTextColor( CR_BLACK );
		skp_Tape_Hdot->SetTextAlign( oapi::Sketchpad::CENTER );
		skp_Tape_Hdot->SetFont( skpSSVBFont_h36w18 );
		skp_Tape_Hdot->SetBackgroundColor( oapi::Sketchpad::BK_TRANSPARENT );
		skp_Tape_Hdot->SetPen( skpBlackPen );

		for (int i = 30; i >= 8; i--)
		{
			y = ((30 - i) * 62) + offset_top;//y = Round( ((30 - i) * 62) + offset_top );

			if (i < 10)
			{
				sprintf_s( cbuf, 8, "%d", i * 100 );
				skp_Tape_Hdot->Text( 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else if ((i % 5) == 0)
			{
				sprintf_s( cbuf, 8, "%.1fK", (double)i / 10 );
				skp_Tape_Hdot->Text( 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else skp_Tape_Hdot->Line( 24, y, 62, y );
		}
		for (int i = 80; i > 0; i--)
		{
			y = Round( ((80 - i) * 26.3) + 1364 + offset_top );

			if ((i % 2) == 0)
			{
				sprintf_s( cbuf, 8, "%d", i * 10 );
				skp_Tape_Hdot->Text( 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else skp_Tape_Hdot->Line( 24, y, 62, y );
		}

		skp_Tape_Hdot->SetTextColor( CR_WHITE );
		skp_Tape_Hdot->SetPen( skpWhitePen );

		for (int i = 0; i >= -80; i--)
		{
			y = Round( ((80 - i) * 26.3) + 1364 + offset_top );

			if ((i % 2) == 0)
			{
				sprintf_s( cbuf, 8, "%d", i * 10 );
				skp_Tape_Hdot->Text( 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else skp_Tape_Hdot->Line( 24, y, 62, y );
		}
		for (int i = -8; i >= -30; i--)
		{
			y = ((-8 - i) * 62) + 5572 + offset_top;//y = Round( ((-8 - i) * 62) + 5572 + offset_top );

			if (i > -10)
			{
				sprintf_s( cbuf, 8, "%d", i * 100 );
				skp_Tape_Hdot->Text( 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else if ((i % 5) == 0)
			{
				sprintf_s( cbuf, 8, "%.1fK", (double)i / 10 );
				skp_Tape_Hdot->Text( 44, y - 22, cbuf, strlen( cbuf ) );
			}
			else skp_Tape_Hdot->Line( 24, y, 62, y );
		}
		oapiReleaseSketchpad( skp_Tape_Hdot );
		return;
	}

	void MDU::DrawAlphaTapeBG_GDI( void )
	{
		int offset_top = 216;
		int offset_bottom = 220;
		int save = SaveDC( hDC_Tape_Alpha );

		SelectObject( hDC_Tape_Alpha, gdiWhitePen );
		SelectObject( hDC_Tape_Alpha, gdiWhiteBrush );
		Rectangle( hDC_Tape_Alpha, 0, 0, 86, 3396 + offset_top );

		SelectObject( hDC_Tape_Alpha, gdiDarkGrayPen );
		SelectObject( hDC_Tape_Alpha, gdiDarkGrayBrush );
		Rectangle( hDC_Tape_Alpha, 0, 3396 + 1 + offset_top, 86, 6792 + offset_top + offset_bottom );

		RestoreDC( hDC_Tape_Alpha, save );
		return;
	}

	void MDU::DrawAlphaTapeBG_Sketchpad( void )
	{
		int offset_top = 216;
		int offset_bottom = 220;
		oapi::Sketchpad* skp_Tape_Alpha = oapiGetSketchpad( sfh_Tape_Alpha );

		skp_Tape_Alpha->SetPen( skpWhitePen );
		skp_Tape_Alpha->SetBrush( skpWhiteBrush );
		skp_Tape_Alpha->Rectangle( 0, 0, 86, 3396 + offset_top );

		skp_Tape_Alpha->SetPen( skpDarkGrayPen );
		skp_Tape_Alpha->SetBrush( skpDarkGrayBrush );
		skp_Tape_Alpha->Rectangle( 0, 3396 + 1 + offset_top, 86, 6792 + offset_top + offset_bottom );

		oapiReleaseSketchpad( skp_Tape_Alpha );
		return;
	}

	void MDU::DrawAlphaTapeFG_GDI( int min, int max )
	{
		int offset_top = 216;
		char cbuf[8];
		int y = 0;
		int save = SaveDC( hDC_Tape_Alpha );

		SetTextColor( hDC_Tape_Alpha, CR_BLACK );
		SetTextAlign( hDC_Tape_Alpha, TA_CENTER );
		SelectObject( hDC_Tape_Alpha, gdiSSVBFont_h36w18 );
		SetBkMode( hDC_Tape_Alpha, TRANSPARENT );
		SelectObject( hDC_Tape_Alpha, gdiBlackPen );

		max = (int)range( -180.0, max, 180.0 );
		min = (int)range( -180.0, min, 180.0 );
		if (max < 0)
		{
			SetTextColor( hDC_Tape_Alpha, CR_WHITE );
			SelectObject( hDC_Tape_Alpha, gdiWhitePen );
		}
		for (int i = max; i >= min; i--)
		{
			if (i == 0)
			{
				SetTextColor( hDC_Tape_Alpha, CR_WHITE );
				SelectObject( hDC_Tape_Alpha, gdiWhitePen );
			}

			y = Round( ((180 - i) * 18.87) + offset_top );

			MoveToEx( hDC_Tape_Alpha, 70, y, NULL );
			LineTo( hDC_Tape_Alpha, 86, y );

			if ((i % 5) == 0)
			{
				sprintf_s( cbuf, 8, "%d", i );
				if (i > -100) TextOut( hDC_Tape_Alpha, 38, y - 22, cbuf, strlen( cbuf ) );
				else TextOut( hDC_Tape_Alpha, 32, y - 22, cbuf, strlen( cbuf ) );
			}
		}

		RestoreDC( hDC_Tape_Alpha, save );
		return;
	}

	void MDU::DrawAlphaTapeFG_Sketchpad( int min, int max )
	{
		int offset_top = 216;
		char cbuf[8];
		int y = 0;
		oapi::Sketchpad* skp_Tape_Alpha = oapiGetSketchpad( sfh_Tape_Alpha );

		skp_Tape_Alpha->SetTextColor( CR_BLACK );
		skp_Tape_Alpha->SetTextAlign( oapi::Sketchpad::CENTER );
		skp_Tape_Alpha->SetFont( skpSSVBFont_h36w18 );
		skp_Tape_Alpha->SetBackgroundColor( oapi::Sketchpad::BK_TRANSPARENT );
		skp_Tape_Alpha->SetPen( skpBlackPen );

		max = (int)range( -180.0, max, 180.0 );
		min = (int)range( -180.0, min, 180.0 );
		if (max < 0)
		{
			skp_Tape_Alpha->SetTextColor( CR_WHITE );
			skp_Tape_Alpha->SetPen( skpWhitePen );
		}
		for (int i = max; i >= min; i--)
		{
			if (i == 0)
			{
				skp_Tape_Alpha->SetTextColor( CR_WHITE );
				skp_Tape_Alpha->SetPen( skpWhitePen );
			}

			y = Round( ((180 - i) * 18.87) + offset_top );

			skp_Tape_Alpha->Line( 70, y, 86, y );

			if ((i % 5) == 0)
			{
				sprintf_s( cbuf, 8, "%d", i );
				if (i > -100) skp_Tape_Alpha->Text( 38, y - 22, cbuf, strlen( cbuf ) );
				else skp_Tape_Alpha->Text( 32, y - 22, cbuf, strlen( cbuf ) );
			}
		}
		oapiReleaseSketchpad( skp_Tape_Alpha );
		return;
	}

	void MDU::DrawAlphaTapeLim_GDI( double min, double max )
	{
		int offset_top = 216;
		int save = SaveDC( hDC_Tape_Alpha );

		SelectObject( hDC_Tape_Alpha, gdiLightGreenPen );
		SelectObject( hDC_Tape_Alpha, gdiLightGreenBrush );
		Rectangle( hDC_Tape_Alpha, 70, 3396 + offset_top - Round( max * 18.87 ), 86, 3396 + offset_top - Round( min * 18.87 ) );

		RestoreDC( hDC_Tape_Alpha, save );
		return;
	}

	void MDU::DrawAlphaTapeLim_Sketchpad( double min, double max )
	{
		int offset_top = 216;
		oapi::Sketchpad* skp_Tape_Alpha = oapiGetSketchpad( sfh_Tape_Alpha );

		skp_Tape_Alpha->SetPen( skpLightGreenPen );
		skp_Tape_Alpha->SetBrush( skpLightGreenBrush );
		skp_Tape_Alpha->Rectangle( 70, 3396 + offset_top - Round( max * 18.87 ), 86, 3396 + offset_top - Round( min * 18.87 ) );

		oapiReleaseSketchpad( skp_Tape_Alpha );
		return;
	}

	void MDU::DestroyTapes( void )
	{
		if (hDC_Tape_MACHV)
		{
			DeleteObject( SelectObject( hDC_Tape_MACHV, hBM_Tape_MACHV_tmp ) );
			DeleteObject( hDC_Tape_MACHV );
			DeleteObject( SelectObject( hDC_Tape_KEAS, hBM_Tape_KEAS_tmp ) );
			DeleteObject( hDC_Tape_KEAS );
			DeleteObject( SelectObject( hDC_Tape_Alpha, hBM_Tape_Alpha_tmp ) );
			DeleteObject( hDC_Tape_Alpha );
			DeleteObject( SelectObject( hDC_Tape_H, hBM_Tape_H_tmp ) );
			DeleteObject( hDC_Tape_H );
			DeleteObject( SelectObject( hDC_Tape_Hdot, hBM_Tape_Hdot_tmp ) );
			DeleteObject( hDC_Tape_Hdot );

			hDC_Tape_MACHV = NULL;
		}

		if (sfh_Tape_MACHV)
		{
			oapiDestroySurface( sfh_Tape_MACHV );
			oapiDestroySurface( sfh_Tape_KEAS );
			oapiDestroySurface( sfh_Tape_Alpha );
			oapiDestroySurface( sfh_Tape_H );
			oapiDestroySurface( sfh_Tape_Hdot );

			sfh_Tape_MACHV = NULL;
		}
		return;
	}

	void MDU::CreateADI( void )
	{
		hDC_ADI = CreateCompatibleDC( GetDC( NULL ) );
		HBITMAP hBM = CreateCompatibleBitmap( GetDC( NULL ), 384, 384 );
		hBM_ADI_tmp = (HBITMAP)SelectObject( hDC_ADI, hBM );
		save_ADI = SaveDC( hDC_ADI );
		SelectObject( hDC_ADI, gdiSSVBFont_h24w14 );

		hDC_ADI_ORBIT = CreateCompatibleDC( hDC_ADI );
		hBM = CreateCompatibleBitmap( hDC_ADI, 444, 444 );
		hBM_ADI_ORBIT_tmp = (HBITMAP)SelectObject( hDC_ADI_ORBIT, hBM );
		save_ADI_ORBIT = SaveDC( hDC_ADI_ORBIT );
		SelectObject( hDC_ADI_ORBIT, gdiSSVBFont_h24w14 );

		if (hDC_ADIMASK) return;// already created

		hDC_ADIMASK = CreateCompatibleDC( hDC_ADI );
		hBM = CreateCompatibleBitmap( hDC_ADI, 384, 384 );
		hBM_ADIMASK_tmp = (HBITMAP)SelectObject( hDC_ADIMASK, hBM );
		int save = SaveDC( hDC_ADIMASK );
		SelectObject( hDC_ADIMASK, gdiWhitePen );
		SelectObject( hDC_ADIMASK, gdiWhiteBrush );
		::Ellipse( hDC_ADIMASK, 2, 2, 382, 382 );
		RestoreDC( hDC_ADIMASK, save );

		hDC_ADIMASK_ORBIT = CreateCompatibleDC( hDC_ADI );
		hBM = CreateCompatibleBitmap( hDC_ADI, 444, 444 );
		hBM_ADIMASK_ORBIT_tmp = (HBITMAP)SelectObject( hDC_ADIMASK_ORBIT, hBM );
		save = SaveDC( hDC_ADIMASK_ORBIT );
		SelectObject( hDC_ADIMASK_ORBIT, gdiWhitePen );
		SelectObject( hDC_ADIMASK_ORBIT, gdiWhiteBrush );
		::Ellipse( hDC_ADIMASK_ORBIT, 2, 2, 442, 442 );
		RestoreDC( hDC_ADIMASK_ORBIT, save );
		return;
	}

	void MDU::DestroyADI( void )
	{
		if (!hDC_ADI) return;

		RestoreDC( hDC_ADI, save_ADI );
		DeleteObject( SelectObject( hDC_ADI, hBM_ADI_tmp ) );
		DeleteObject( hDC_ADI );
		RestoreDC( hDC_ADI_ORBIT, save_ADI_ORBIT );
		DeleteObject( SelectObject( hDC_ADI_ORBIT, hBM_ADI_ORBIT_tmp ) );
		DeleteObject( hDC_ADI_ORBIT );

		hDC_ADI = NULL;

		if (!hDC_ADIMASK) return;// already created

		DeleteObject( SelectObject( hDC_ADIMASK, hBM_ADIMASK_tmp ) );
		DeleteObject( hDC_ADIMASK );
		DeleteObject( SelectObject( hDC_ADIMASK_ORBIT, hBM_ADIMASK_ORBIT_tmp ) );
		DeleteObject( hDC_ADIMASK_ORBIT );

		hDC_ADIMASK = NULL;
		return;
	}

	void MDU::Tape_EAS( HDC hDC, double eas )
	{
		char cbuf[8];
		SelectObject( hDC, gdiWhitePen );
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 26, 108, 118, 548 );
		SelectObject( hDC, gdiLightGrayPen );

		SelectObject( hDC, gdiSSVAFont_h22w18 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		TextOut( hDC, 34, 78, "KEAS", 4 );

		BitBlt( hDC, 28, 110, 86, 434, hDC_Tape_KEAS, 0, 7750 - Round( eas * 15.5 ), SRCCOPY );

		Rectangle( hDC, 26, 300, 118, 350 );

		SelectObject( hDC, gdiSSVBFont_h36w18 );
		SetTextColor( hDC, CR_WHITE );
		SetTextAlign( hDC, TA_RIGHT );
		sprintf_s( cbuf, 8, "%.0f", eas );
		TextOut( hDC, 98, 302, cbuf, strlen( cbuf ) );
		SetTextAlign( hDC, TA_LEFT );
		return;
	}

	void MDU::Tape_EAS( oapi::Sketchpad* skp, double eas )
	{
		char cbuf[8];
		skp->SetPen( skpWhitePen );
		skp->SetBrush( skpBlackBrush );
		skp->Rectangle( 26, 108, 118, 548 );
		skp->SetPen( skpLightGrayPen );

		skp->SetFont( skpSSVAFont_h22w18 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Text( 34, 78, "KEAS", 4 );

		RECT src;
		src.left = 0;
		src.top = 7750 - Round( eas * 15.5 );
		src.right = 86;
		src.bottom = src.top + 434;
		skp->CopyRect( sfh_Tape_KEAS, &src, 28, 112 );

		skp->Rectangle( 26, 300, 118, 350 );

		skp->SetFont( skpSSVBFont_h36w18 );
		skp->SetTextColor( CR_WHITE );
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );
		sprintf_s( cbuf, 8, "%.0f", eas );
		skp->Text( 98, 302, cbuf, strlen( cbuf ) );
		skp->SetTextAlign( oapi::Sketchpad::LEFT );
		return;
	}

	void MDU::Tape_MV( HDC hDC, char label, double mach )
	{
		char cbuf[8];
		SelectObject( hDC, gdiWhitePen );
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 26, 108, 118, 548 );
		SelectObject( hDC, gdiLightGrayPen );

		SelectObject( hDC, gdiSSVAFont_h22w18 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		sprintf_s( cbuf, 8, "M/V%c", label );
		TextOut( hDC, 36, 78, cbuf, 4 );

		SelectObject( hDC, gdiSSVBFont_h36w18 );
		SetTextColor( hDC, CR_WHITE );
		SetTextAlign( hDC, TA_RIGHT );
		BitBlt( hDC, 28, 110, 86, 434, hDC_Tape_MACHV, 0, Round( 15622.2 - mach * 578.6 ), SRCCOPY );

		Rectangle( hDC, 26, 300, 118, 350 );
		sprintf_s( cbuf, 8, "%.2f", mach );
		TextOut( hDC, 114, 302, cbuf, strlen( cbuf ) );
		SetTextAlign( hDC, TA_LEFT );
		return;
	}

	void MDU::Tape_MV( oapi::Sketchpad* skp, char label, double mach )
	{
		char cbuf[8];
		skp->SetPen( skpWhitePen );
		skp->SetBrush( skpBlackBrush );
		skp->Rectangle( 26, 108, 118, 548 );
		skp->SetPen( skpLightGrayPen );

		skp->SetFont( skpSSVAFont_h22w18 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		sprintf_s( cbuf, 8, "M/V%c", label );
		skp->Text( 36, 78, cbuf, 4 );

		skp->SetFont( skpSSVBFont_h36w18 );
		skp->SetTextColor( CR_WHITE );
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );

		RECT src;
		src.left = 0;
		src.top = Round( 15622.2 - mach * 578.6 );
		src.right = 86;
		src.bottom = src.top + 434;
		skp->CopyRect( sfh_Tape_MACHV, &src, 28, 112 );

		skp->Rectangle( 26, 300, 118, 350 );
		sprintf_s( cbuf, 8, "%.2f", mach );
		skp->Text( 114, 302, cbuf, strlen( cbuf ) );
		skp->SetTextAlign( oapi::Sketchpad::LEFT );
		return;
	}

	void MDU::Box_EAS( HDC hDC, double eas )
	{
		char cbuf[8];
		SelectObject( hDC, gdiWhitePen );
		SelectObject( hDC, gdiLightGrayPen );
		Rectangle( hDC, 26, 570, 118, 618 );

		SelectObject( hDC, gdiSSVAFont_h22w18 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		TextOut( hDC, 34, 630, "KEAS", 4 );

		SelectObject( hDC, gdiSSVBFont_h36w18 );
		SetTextColor( hDC, CR_WHITE );
		SetTextAlign( hDC, TA_RIGHT );

		sprintf_s( cbuf, 8, "%.0f", eas );
		TextOut( hDC, 98, 570, cbuf, strlen( cbuf ) );
		SetTextAlign( hDC, TA_LEFT );
		return;
	}

	void MDU::Box_EAS( oapi::Sketchpad* skp, double eas )
	{
		char cbuf[8];
		skp->SetPen( skpWhitePen );
		skp->SetPen( skpLightGrayPen );
		skp->Rectangle( 26, 570, 118, 618 );

		skp->SetFont( skpSSVAFont_h22w18 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Text( 34, 630, "KEAS", 4 );

		skp->SetFont( skpSSVBFont_h36w18 );
		skp->SetTextColor( CR_WHITE );
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );

		sprintf_s( cbuf, 8, "%.0f", eas );
		skp->Text( 98, 570, cbuf, strlen( cbuf ) );
		skp->SetTextAlign( oapi::Sketchpad::LEFT );
		return;
	}

	void MDU::Box_MVR( HDC hDC, double mach )
	{
		char cbuf[8];
		SelectObject( hDC, gdiWhitePen );
		SelectObject( hDC, gdiLightGrayPen );
		Rectangle( hDC, 26, 570, 118, 618 );

		SelectObject( hDC, gdiSSVAFont_h22w18 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		TextOut( hDC, 34, 630, "M/VR", 4 );

		SelectObject( hDC, gdiSSVBFont_h36w18 );
		SetTextColor( hDC, CR_WHITE );
		SetTextAlign( hDC, TA_RIGHT );
		sprintf_s( cbuf, 8, "%.2f", mach );
		TextOut( hDC, 114, 570, cbuf, strlen( cbuf ) );
		SetTextAlign( hDC, TA_LEFT );
		return;
	}

	void MDU::Box_MVR( oapi::Sketchpad* skp, double mach )
	{
		char cbuf[8];
		skp->SetPen( skpWhitePen );
		skp->SetPen( skpLightGrayPen );
		skp->Rectangle( 26, 570, 118, 618 );

		skp->SetFont( skpSSVAFont_h22w18 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Text( 34, 630, "M/VR", 4 );

		skp->SetFont( skpSSVBFont_h36w18 );
		skp->SetTextColor( CR_WHITE );
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );
		sprintf_s( cbuf, 8, "%.2f", mach );
		skp->Text( 114, 570, cbuf, strlen( cbuf ) );
		skp->SetTextAlign( oapi::Sketchpad::LEFT );
		return;
	}

	void MDU::Tape_Alpha( HDC hDC, double alpha, double vel )
	{
		SelectObject( hDC, gdiSSVAFont_h22w18 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		TextOut( hDC, 164, 78, "\x10", 1 );

		SelectObject( hDC, gdiWhitePen );
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 136, 108, 228, 548 );

		// draw tape background
		DrawAlphaTapeBG_GDI();

		// paint alpha limits (if any)
		switch (STS()->GetGPCMajorMode())
		{
			case 304:
			case 305:
				DrawAlphaTapeLim_GDI( listerp( AlphaLimNom_Mach, AlphaLimNom_Min, AlphaLimNom_count, vel ),
					listerp( AlphaLimNom_Mach, AlphaLimNom_Max, AlphaLimNom_count, vel ) );
				break;
			case 602:
			case 603:
				DrawAlphaTapeLim_GDI( listerp( AlphaLimRTLS_Mach, AlphaLimRTLS_Min, AlphaLimRTLS_count, vel ),
					listerp( AlphaLimRTLS_Mach, AlphaLimRTLS_Max, AlphaLimRTLS_count, vel ) );
				break;
		}

		// draw tape foreground (only ~13º around current value)
		int amin = (int)alpha - 13;
		int amax = amin + 26;
		DrawAlphaTapeFG_GDI( amin, amax );

		// copy tape
		BitBlt( hDC, 138, 110, 86, 434, hDC_Tape_Alpha, 0, 3396 - Round( alpha * 18.87 ), SRCCOPY );

		// max L/D alpha
		if ((vel > 0.0) && (vel < 3.0))
		{
			double maxLD = 0.0;
			if (vel > MaxLD_Mach[0]) maxLD = listerp( MaxLD_Mach, MaxLD_Alpha, MaxLD_count, vel );
			else maxLD = MaxLD_Alpha[0];// maintain minimum value

			maxLD -= alpha;
			if (fabs( maxLD ) < 11.0)
			{
				int pos = Round( maxLD * 18.87 );
				POINT diamond[4];
				diamond[0].x = 206;// start at top moving cw
				diamond[0].y = 310 - pos;
				diamond[1].x = 222;
				diamond[1].y = 326 - pos;
				diamond[2].x = 206;
				diamond[2].y = 342 - pos;
				diamond[3].x = 190;
				diamond[3].y = 326 - pos;
				SelectObject( hDC, gdiMagentaBrush );
				SelectObject( hDC, gdiBlackPen );
				Polygon( hDC, diamond, 4 );

				diamond[0].y += 12;
				diamond[1].x = 210;
				diamond[2].y -= 12;
				diamond[3].x = 202;
				SelectObject( hDC, gdiBlackBrush );
				Polygon( hDC, diamond, 4 );
			}
		}

		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiBlackBrush );
		static const POINT poly[5] = {{222,326},{208,350},{128,350},{128,300},{208,300}};// start at tip moving cw
		Polygon( hDC, poly, 5 );

		SelectObject( hDC, gdiSSVBFont_h36w18 );
		SetTextColor( hDC, CR_WHITE );
		SetTextAlign( hDC, TA_RIGHT );
		char cbuf[8];
		if (alpha >= -100) sprintf_s( cbuf, 8, "%.1f", alpha );
		else sprintf_s( cbuf, 8, "%.0f", alpha );
		TextOut( hDC, 216, 302, cbuf, strlen( cbuf ) );
		SetTextAlign( hDC, TA_LEFT );
		return;
	}

	void MDU::Tape_Alpha( oapi::Sketchpad* skp, double alpha, double vel )
	{
		skp->SetFont( skpSSVAFont_h22w18 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		char cbuf[8];
		sprintf_s( cbuf, 8, "%c", 254 );
		skp->Text( 164, 78, cbuf, 1 );

		skp->SetPen( skpWhitePen );
		skp->SetBrush( skpBlackBrush );
		skp->Rectangle( 136, 108, 228, 548 );

		// draw tape background
		DrawAlphaTapeBG_Sketchpad();

		// paint alpha limits (if any)
		switch (STS()->GetGPCMajorMode())
		{
			case 304:
			case 305:
				DrawAlphaTapeLim_Sketchpad( listerp( AlphaLimNom_Mach, AlphaLimNom_Min, AlphaLimNom_count, vel ),
					listerp( AlphaLimNom_Mach, AlphaLimNom_Max, AlphaLimNom_count, vel ) );
				break;
			case 602:
			case 603:
				DrawAlphaTapeLim_Sketchpad( listerp( AlphaLimRTLS_Mach, AlphaLimRTLS_Min, AlphaLimRTLS_count, vel ),
					listerp( AlphaLimRTLS_Mach, AlphaLimRTLS_Max, AlphaLimRTLS_count, vel ) );
				break;
		}

		// draw tape foreground (only ~13º around current value)
		int amin = (int)alpha - 13;
		int amax = amin + 26;
		DrawAlphaTapeFG_Sketchpad( amin, amax );

		// copy tape
		RECT src;
		src.left = 0;
		src.top = 3396 - Round( alpha * 18.87 );
		src.right = 86;
		src.bottom = src.top + 434;
		skp->CopyRect( sfh_Tape_Alpha, &src, 138, 112 );

		// max L/D alpha
		if ((vel > 0.0) && (vel < 3.0))
		{
			double maxLD = 0.0;
			if (vel > MaxLD_Mach[0]) maxLD = listerp( MaxLD_Mach, MaxLD_Alpha, MaxLD_count, vel );
			else maxLD = MaxLD_Alpha[0];// maintain minimum value

			maxLD -= alpha;
			if (fabs( maxLD ) < 11.0)
			{
				int pos = Round( maxLD * 18.87 );
				oapi::IVECTOR2 diamond[4];
				diamond[0].x = 206;// start at top moving cw
				diamond[0].y = 310 - pos;
				diamond[1].x = 222;
				diamond[1].y = 326 - pos;
				diamond[2].x = 206;
				diamond[2].y = 342 - pos;
				diamond[3].x = 190;
				diamond[3].y = 326 - pos;
				skp->SetBrush( skpMagentaBrush );
				skp->SetPen( skpBlackPen );
				skp->Polygon( diamond, 4 );

				diamond[0].y += 12;
				diamond[1].x = 210;
				diamond[2].y -= 12;
				diamond[3].x = 202;
				skp->SetBrush( skpBlackBrush );
				skp->Polygon( diamond, 4 );
			}
		}

		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpBlackBrush );
		static const oapi::IVECTOR2 poly[5] = {{222,326},{208,350},{128,350},{128,300},{208,300}};// start at tip moving cw
		skp->Polygon( poly, 5 );

		skp->SetFont( skpSSVBFont_h36w18 );
		skp->SetTextColor( CR_WHITE );
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );
		if (alpha >= -100) sprintf_s( cbuf, 8, "%.1f", alpha );
		else sprintf_s( cbuf, 8, "%.0f", alpha );
		skp->Text( 216, 302, cbuf, strlen( cbuf ) );
		skp->SetTextAlign( oapi::Sketchpad::LEFT );
		return;
	}

	void MDU::Tape_H_Hdot( HDC hDC, double Altitude_ft, double Hdot )
	{
		SelectObject( hDC, gdiSSVAFont_h22w18 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		TextOut( hDC, 822, 78, "H", 1 );
		SelectObject( hDC, gdiWhitePen );
		Rectangle( hDC, 788, 108, 880, 548 );
		int pos;
		double Altitude_NM = 0;
		if (Altitude_ft > 400000)
		{
			Altitude_NM = Altitude_ft * FT2NM;
			if (Altitude_NM > 165) Altitude_NM = 165;
			pos = Round( 7161 - Altitude_NM * 43.4 );
		}
		else if (Altitude_ft > 100000)
		{
			pos = Round( 6783.918542 - Altitude_ft * 0.0062 );
		}
		else if (Altitude_ft > 30000)
		{
			pos = Round( 9937.918542 - Altitude_ft * 0.03774 );
		}
		else if (Altitude_ft > 2000)
		{
			pos = Round( 11172.718542 - Altitude_ft * 0.0789 );
		}
		else if (Altitude_ft > 200)
		{
			pos = Round( 11634.918542 - Altitude_ft * 0.31 );
		}
		else if (Altitude_ft > 0)
		{
			pos = Round( 12006.918 - Altitude_ft * 2.17 );
		}
		else //if (Altitude_ft > -1100)
		{
			if (Altitude_ft < -1100) Altitude_ft = -1100;
			pos = Round( 12006.918 - Altitude_ft * 0.9644 );
		}
		BitBlt( hDC, 790, 110, 86, 434, hDC_Tape_H, 0, pos, SRCCOPY );

		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 788, 300, 880, 350 );
		SelectObject( hDC, gdiSSVBFont_h36w18 );
		SetTextColor( hDC, CR_WHITE );
		SetTextAlign( hDC, TA_RIGHT );
		char cbuf[8];
		if (Altitude_ft < 10000)
		{
			sprintf_s( cbuf, 8, "%d", (int)Altitude_ft );
			TextOut( hDC, 860, 302, cbuf, strlen( cbuf ) );
		}
		else if (Altitude_ft < 400000)
		{
			sprintf_s( cbuf, 8, "%d", (int)Altitude_ft / 1000 );
			TextOut( hDC, 860, 302, cbuf, strlen( cbuf ) );
			SelectObject( hDC, gdiSSVBFont_h24w14 );
			SetTextColor( hDC, CR_LIGHT_GRAY );
			TextOut( hDC, 876, 310, "K", 1 );
		}
		else
		{
			sprintf_s( cbuf, 8, "%.0f", Altitude_NM );
			TextOut( hDC, 860, 302, cbuf, strlen( cbuf ) );
			SelectObject( hDC, gdiSSVBFont_h24w14 );
			SetTextColor( hDC, CR_LIGHT_GRAY );
			TextOut( hDC, 876, 310, "M", 1 );
		}
		SetTextAlign( hDC, TA_LEFT );

		SelectObject( hDC, gdiSSVAFont_h22w18 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		SetPixel( hDC, 962, 74, CR_LIGHT_GRAY );
		TextOut( hDC, 954, 78, "H", 1 );
		SelectObject( hDC, gdiWhitePen );
		Rectangle( hDC, 918, 108, 1010, 548 );
		if (Hdot > 800)
		{
			if (Hdot > 3000) Hdot = 3000;
			pos = Round( (3000 - Hdot) * 0.62 );
		}
		else if (Hdot > -800)
		{
			pos = Round( 3468 - (Hdot * 2.63) );
		}
		else
		{
			if (Hdot < -3000) Hdot = -3000;
			pos = Round( 5076 - (Hdot * 0.62) );
		}
		BitBlt( hDC, 920, 110, 86, 434, hDC_Tape_Hdot, 0, pos, SRCCOPY );

		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 918, 300, 1010, 350 );
		SelectObject( hDC, gdiSSVBFont_h36w18 );
		SetTextColor( hDC, CR_WHITE );
		SetTextAlign( hDC, TA_RIGHT );
		sprintf_s( cbuf, 8, "%.0f", Hdot );
		TextOut( hDC, 1006, 302, cbuf, strlen( cbuf ) );
		SetTextAlign( hDC, TA_LEFT );
		return;
	}

	void MDU::Tape_H_Hdot( oapi::Sketchpad* skp, double Altitude_ft, double Hdot )
	{
		skp->SetFont( skpSSVAFont_h22w18 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Text( 822, 78, "H", 1 );
		skp->SetPen( skpWhitePen );
		skp->Rectangle( 788, 108, 880, 548 );
		int pos;
		double Altitude_NM = 0;
		if (Altitude_ft > 400000)
		{
			Altitude_NM = Altitude_ft * FT2NM;
			if (Altitude_NM > 165) Altitude_NM = 165;
			pos = Round( 7161 - Altitude_NM * 43.4 );
		}
		else if (Altitude_ft > 100000)
		{
			pos = Round( 6783.918542 - Altitude_ft * 0.0062 );
		}
		else if (Altitude_ft > 30000)
		{
			pos = Round( 9937.918542 - Altitude_ft * 0.03774 );
		}
		else if (Altitude_ft > 2000)
		{
			pos = Round( 11172.718542 - Altitude_ft * 0.0789 );
		}
		else if (Altitude_ft > 200)
		{
			pos = Round( 11634.918542 - Altitude_ft * 0.31 );
		}
		else if (Altitude_ft > 0)
		{
			pos = Round( 12006.918 - Altitude_ft * 2.17 );
		}
		else //if (Altitude_ft > -1100)
		{
			if (Altitude_ft < -1100) Altitude_ft = -1100;
			pos = Round( 12006.918 - Altitude_ft * 0.9644 );
		}
		RECT src;
		src.left = 0;
		src.top = pos;
		src.right = 86;
		src.bottom = src.top + 434;
		skp->CopyRect( sfh_Tape_H, &src, 790, 112 );

		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpBlackBrush );
		skp->Rectangle( 788, 300, 880, 350 );
		skp->SetFont( skpSSVBFont_h36w18 );
		skp->SetTextColor( CR_WHITE );
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );
		char cbuf[8];
		if (Altitude_ft < 10000)
		{
			sprintf_s( cbuf, 8, "%d", (int)Altitude_ft );
			skp->Text( 860, 302, cbuf, strlen( cbuf ) );
		}
		else if (Altitude_ft < 400000)
		{
			sprintf_s( cbuf, 8, "%d", (int)Altitude_ft / 1000 );
			skp->Text( 860, 302, cbuf, strlen( cbuf ) );
			skp->SetFont( skpSSVBFont_h24w14 );
			skp->SetTextColor( CR_LIGHT_GRAY );
			skp->Text( 876, 310, "K", 1 );
		}
		else
		{
			sprintf_s( cbuf, 8, "%.0f", Altitude_NM );
			skp->Text( 860, 302, cbuf, strlen( cbuf ) );
			skp->SetFont( skpSSVBFont_h24w14 );
			skp->SetTextColor( CR_LIGHT_GRAY );
			skp->Text( 876, 310, "M", 1 );
		}
		skp->SetTextAlign( oapi::Sketchpad::LEFT );

		skp->SetFont( skpSSVAFont_h22w18 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Pixel( 962, 74, CR_LIGHT_GRAY );
		skp->Text( 954, 78, "H", 1 );
		skp->SetPen( skpWhitePen );
		skp->Rectangle( 918, 108, 1010, 548 );
		if (Hdot > 800)
		{
			if (Hdot > 3000) Hdot = 3000;
			pos = Round( (3000 - Hdot) * 0.62 );
		}
		else if (Hdot > -800)
		{
			pos = Round( 3468 - (Hdot * 2.63) );
		}
		else
		{
			if (Hdot < -3000) Hdot = -3000;
			pos = Round( 5076 - (Hdot * 0.62) );
		}
		src.top = pos;
		src.bottom = src.top + 434;
		skp->CopyRect( sfh_Tape_Hdot, &src, 920, 112 );

		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpBlackBrush );
		skp->Rectangle( 918, 300, 1010, 350 );
		skp->SetFont( skpSSVBFont_h36w18 );
		skp->SetTextColor( CR_WHITE );
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );
		sprintf_s( cbuf, 8, "%.0f", Hdot );
		skp->Text( 1006, 302, cbuf, strlen( cbuf ) );
		skp->SetTextAlign( oapi::Sketchpad::LEFT );
		return;
	}

	void MDU::Tapes_Invalid( HDC hDC )
	{
		SelectObject( hDC, gdiRedPen );
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 26, 108, 118, 548 );
		Rectangle( hDC, 26, 300, 118, 350 );
		Rectangle( hDC, 26, 570, 118, 618 );

		Rectangle( hDC, 136, 108, 228, 548 );
		static const POINT poly[5] = {{222,326},{208,350},{128,350},{128,300},{208,300}};// start at tip moving cw
		Polygon( hDC, poly, 5 );

		Rectangle( hDC, 788, 108, 880, 548 );
		Rectangle( hDC, 788, 300, 880, 350 );

		Rectangle( hDC, 918, 108, 1010, 548 );
		Rectangle( hDC, 918, 300, 1010, 350 );

		SelectObject( hDC, gdiSSVAFont_h22w18 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		TextOut( hDC, 34, 78, "M/V", 3 );
		TextOut( hDC, 34, 630, "KEAS", 4 );

		TextOut( hDC, 164, 78, "\x10", 1 );

		TextOut( hDC, 822, 78, "H", 1 );
		SetPixel( hDC, 962, 74, CR_LIGHT_GRAY );
		TextOut( hDC, 954, 78, "H", 1 );
		return;
	}

	void MDU::Tapes_Invalid( oapi::Sketchpad* skp )
	{
		skp->SetFont( skpSSVAFont_h22w18 );
		skp->SetPen( skpRedPen );
		skp->SetBrush( skpBlackBrush );
		skp->Rectangle( 26, 108, 118, 548 );
		skp->Rectangle( 26, 300, 118, 350 );
		skp->Rectangle( 26, 570, 118, 618 );

		skp->Rectangle( 136, 108, 228, 548 );
		static const oapi::IVECTOR2 poly[5] = {{222,326},{208,350},{128,350},{128,300},{208,300}};// start at tip moving cw
		skp->Polygon( poly, 5 );

		skp->Rectangle( 788, 110, 880, 538 );
		skp->Rectangle( 788, 302, 880, 352 );

		skp->Rectangle( 918, 110, 1010, 538 );
		skp->Rectangle( 918, 302, 1010, 352 );

		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Text( 34, 78, "M/V", 3 );
		skp->Text( 34, 630, "KEAS", 4 );

		skp->Text( 164, 78, "\x10", 1 );

		skp->Text( 822, 78, "H", 1 );
		skp->Pixel( 962, 74, CR_LIGHT_GRAY );
		skp->Text( 954, 78, "H", 1 );
		return;
	}

	void MDU::ADI_STATIC( HDC hDC )
	{
		SelectObject( hDC, gdiSSVBFont_h24w14 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		TextOut( hDC, 698, 28, "R", 1 );
		TextOut( hDC, 698, 58, "P", 1 );
		TextOut( hDC, 698, 88, "Y", 1 );

		SelectObject( hDC, gdiWhitePen );
		::Ellipse( hDC, 244, 86, 712, 564 );

		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiLightGrayBrush );
		POINT diamond[4];
		diamond[0].x = 478;
		diamond[0].y = 106;
		diamond[1].x = 488;
		diamond[1].y = 124;
		diamond[2].x = 478;
		diamond[2].y = 142;
		diamond[3].x = 468;
		diamond[3].y = 122;
		Polygon( hDC, diamond, 4 );// top
		//diamond[0].x = 478;
		diamond[0].y = 518;
		//diamond[1].x = 488;
		diamond[1].y = 536;
		//diamond[2].x = 478;
		diamond[2].y = 554;
		//diamond[3].x = 468;
		diamond[3].y = 536;
		Polygon( hDC, diamond, 4 );// bottom
		diamond[0].x = 684;
		diamond[0].y = 320;
		diamond[1].x = 702;
		diamond[1].y = 330;
		diamond[2].x = 684;
		diamond[2].y = 340;
		diamond[3].x = 666;
		diamond[3].y = 330;
		Polygon( hDC, diamond, 4 );// right
		diamond[0].x = 272;
		//diamond[0].y = 320;
		diamond[1].x = 290;
		//diamond[1].y = 330;
		diamond[2].x = 272;
		//diamond[2].y = 340;
		diamond[3].x = 254;
		//diamond[3].y = 330;
		Polygon( hDC, diamond, 4 );// left

		// rate scales
		// top scale
		MoveToEx( hDC, 308, 68, NULL );
		LineTo( hDC, 648, 68 );
		MoveToEx( hDC, 308, 66, NULL );
		LineTo( hDC, 308, 88 );
		MoveToEx( hDC, 342, 66, NULL );
		LineTo( hDC, 342, 82 );
		MoveToEx( hDC, 376, 66, NULL );
		LineTo( hDC, 376, 82 );
		MoveToEx( hDC, 410, 66, NULL );
		LineTo( hDC, 410, 82 );
		MoveToEx( hDC, 444, 66, NULL );
		LineTo( hDC, 444, 82 );
		MoveToEx( hDC, 478, 66, NULL );
		LineTo( hDC, 478, 88 );
		MoveToEx( hDC, 512, 66, NULL );
		LineTo( hDC, 512, 82 );
		MoveToEx( hDC, 546, 66, NULL );
		LineTo( hDC, 546, 82 );
		MoveToEx( hDC, 580, 66, NULL );
		LineTo( hDC, 580, 82 );
		MoveToEx( hDC, 614, 66, NULL );
		LineTo( hDC, 614, 82 );
		MoveToEx( hDC, 648, 66, NULL );
		LineTo( hDC, 648, 88 );

		// side scale
		MoveToEx( hDC, 740, 160, NULL );
		LineTo( hDC, 740, 500 );
		MoveToEx( hDC, 740, 160, NULL );
		LineTo( hDC, 718, 160 );
		MoveToEx( hDC, 740, 194, NULL );
		LineTo( hDC, 724, 194 );
		MoveToEx( hDC, 740, 228, NULL );
		LineTo( hDC, 724, 228 );
		MoveToEx( hDC, 740, 262, NULL );
		LineTo( hDC, 724, 262 );
		MoveToEx( hDC, 740, 296, NULL );
		LineTo( hDC, 724, 296 );
		MoveToEx( hDC, 740, 330, NULL );
		LineTo( hDC, 718, 330 );
		MoveToEx( hDC, 740, 364, NULL );
		LineTo( hDC, 724, 364 );
		MoveToEx( hDC, 740, 398, NULL );
		LineTo( hDC, 724, 398 );
		MoveToEx( hDC, 740, 432, NULL );
		LineTo( hDC, 724, 432 );
		MoveToEx( hDC, 740, 466, NULL );
		LineTo( hDC, 724, 466 );
		MoveToEx( hDC, 740, 500, NULL );
		LineTo( hDC, 718, 500 );

		// bottom scale
		MoveToEx( hDC, 308, 592, NULL );
		LineTo( hDC, 648, 592 );
		MoveToEx( hDC, 308, 592, NULL );
		LineTo( hDC, 308, 570 );
		MoveToEx( hDC, 342, 592, NULL );
		LineTo( hDC, 342, 576 );
		MoveToEx( hDC, 376, 592, NULL );
		LineTo( hDC, 376, 576 );
		MoveToEx( hDC, 410, 592, NULL );
		LineTo( hDC, 410, 576 );
		MoveToEx( hDC, 444, 592, NULL );
		LineTo( hDC, 444, 576 );
		MoveToEx( hDC, 478, 592, NULL );
		LineTo( hDC, 478, 570 );
		MoveToEx( hDC, 512, 592, NULL );
		LineTo( hDC, 512, 576 );
		MoveToEx( hDC, 546, 592, NULL );
		LineTo( hDC, 546, 576 );
		MoveToEx( hDC, 580, 592, NULL );
		LineTo( hDC, 580, 576 );
		MoveToEx( hDC, 614, 592, NULL );
		LineTo( hDC, 614, 576 );
		MoveToEx( hDC, 648, 592, NULL );
		LineTo( hDC, 648, 570 );

		// roll lines
		MoveToEx( hDC, 460, 130, NULL );// 5º/185º
		LineTo( hDC, 496, 530 );
		MoveToEx( hDC, 444, 134, NULL );// 10º/190º
		LineTo( hDC, 512, 526 );
		MoveToEx( hDC, 426, 136, NULL );// 15º/195º
		LineTo( hDC, 530, 524 );
		MoveToEx( hDC, 410, 142, NULL );// 20º/200º
		LineTo( hDC, 546, 518 );
		MoveToEx( hDC, 394, 148, NULL );// 25º/205º
		LineTo( hDC, 562, 512 );

		MoveToEx( hDC, 364, 166, NULL );// 35º/215º
		LineTo( hDC, 592, 494 );
		MoveToEx( hDC, 350, 176, NULL );// 40º/220º
		LineTo( hDC, 606, 484 );
		MoveToEx( hDC, 336, 188, NULL );// 45º/225º
		LineTo( hDC, 620, 472 );
		MoveToEx( hDC, 324, 202, NULL );// 50º/230º
		LineTo( hDC, 632, 458 );
		MoveToEx( hDC, 314, 216, NULL );// 55º/235º
		LineTo( hDC, 642, 444 );

		MoveToEx( hDC, 296, 246, NULL );// 65º/245º
		LineTo( hDC, 660, 414 );
		MoveToEx( hDC, 290, 262, NULL );// 70º/250º
		LineTo( hDC, 666, 398 );
		MoveToEx( hDC, 284, 278, NULL );// 75º/255º
		LineTo( hDC, 672, 382 );
		MoveToEx( hDC, 282, 296, NULL );// 80º/260º
		LineTo( hDC, 674, 364 );
		MoveToEx( hDC, 278, 312, NULL );// 85º/265º
		LineTo( hDC, 678, 348 );

		MoveToEx( hDC, 278, 348, NULL );// 95º/275º
		LineTo( hDC, 678, 312 );
		MoveToEx( hDC, 282, 364, NULL );// 100º/280º
		LineTo( hDC, 674, 296 );
		MoveToEx( hDC, 284, 382, NULL );// 105º/285º
		LineTo( hDC, 672, 278 );
		MoveToEx( hDC, 290, 398, NULL );// 110º/290º
		LineTo( hDC, 666, 262 );
		MoveToEx( hDC, 296, 414, NULL );// 115º/295º
		LineTo( hDC, 660, 246 );

		MoveToEx( hDC, 314, 444, NULL );// 125º/305º
		LineTo( hDC, 642, 216 );
		MoveToEx( hDC, 324, 458, NULL );// 130º/310º
		LineTo( hDC, 632, 202 );
		MoveToEx( hDC, 336, 472, NULL );// 135º/315º
		LineTo( hDC, 620, 188 );
		MoveToEx( hDC, 350, 484, NULL );// 140º/320º
		LineTo( hDC, 606, 176 );
		MoveToEx( hDC, 364, 494, NULL );// 145º/325º
		LineTo( hDC, 592, 166 );

		MoveToEx( hDC, 394, 512, NULL );// 155º/335º
		LineTo( hDC, 562, 148 );
		MoveToEx( hDC, 410, 518, NULL );// 160º/340º
		LineTo( hDC, 546, 142 );
		MoveToEx( hDC, 426, 524, NULL );// 165º/345º
		LineTo( hDC, 530, 136 );
		MoveToEx( hDC, 444, 526, NULL );// 170º/350º
		LineTo( hDC, 512, 134 );
		MoveToEx( hDC, 460, 530, NULL );// 175º/355º
		LineTo( hDC, 496, 130 );
		SelectObject( hDC, gdiLightGrayThickPen );
		MoveToEx( hDC, 374, 150, NULL );// 30º/210º
		LineTo( hDC, 582, 510 );
		MoveToEx( hDC, 298, 226, NULL );// 60º/240º
		LineTo( hDC, 658, 434 );
		MoveToEx( hDC, 298, 434, NULL );// 120º/300º
		LineTo( hDC, 658, 226 );
		MoveToEx( hDC, 374, 510, NULL );// 150º/330º
		LineTo( hDC, 582, 150 );

		// cover center for ADI SRCPAINT
		SelectObject( hDC, GetStockObject( BLACK_BRUSH ) );
		SelectObject( hDC, GetStockObject( BLACK_PEN ) );
		::Ellipse( hDC, 288, 140, 668, 520 );

		TextOut( hDC, 588, 140, "33", 2 );
		TextOut( hDC, 646, 198, "30", 2 );
		TextOut( hDC, 646, 434, "24", 2 );
		TextOut( hDC, 588, 494, "21", 2 );
		TextOut( hDC, 342, 494, "15", 2 );
		TextOut( hDC, 284, 434, "12", 2 );
		TextOut( hDC, 284, 198, "06", 2 );
		TextOut( hDC, 342, 140, "03", 2 );

		// att needles
		// top scale
		SelectObject( hDC, gdiMagentaPen );
		SelectObject( hDC, gdiMagentaBrush );
		Arc( hDC, 258, 110, 698, 550, 572, 132, 384, 132 );
		MoveToEx( hDC, 384, 132, NULL );
		LineTo( hDC, 384, 144 );
		MoveToEx( hDC, 402, 124, NULL );
		LineTo( hDC, 402, 136 );
		MoveToEx( hDC, 422, 118, NULL );
		LineTo( hDC, 422, 130 );
		MoveToEx( hDC, 440, 114, NULL );
		LineTo( hDC, 440, 126 );
		MoveToEx( hDC, 460, 110, NULL );
		LineTo( hDC, 460, 122 );
		MoveToEx( hDC, 478, 110, NULL );
		LineTo( hDC, 478, 122 );
		MoveToEx( hDC, 496, 110, NULL );
		LineTo( hDC, 496, 122 );
		MoveToEx( hDC, 516, 114, NULL );
		LineTo( hDC, 516, 126 );
		MoveToEx( hDC, 534, 118, NULL );
		LineTo( hDC, 534, 130 );
		MoveToEx( hDC, 554, 124, NULL );
		LineTo( hDC, 554, 136 );
		MoveToEx( hDC, 572, 132, NULL );
		LineTo( hDC, 572, 144 );

		// side scale
		Arc( hDC, 258, 110, 698, 550, 676, 424, 676, 236 );
		MoveToEx( hDC, 676, 236, NULL );
		LineTo( hDC, 664, 236 );
		MoveToEx( hDC, 684, 254, NULL );
		LineTo( hDC, 672, 254 );
		MoveToEx( hDC, 690, 274, NULL );
		LineTo( hDC, 678, 274 );
		MoveToEx( hDC, 694, 292, NULL );
		LineTo( hDC, 682, 292 );
		MoveToEx( hDC, 698, 312, NULL );
		LineTo( hDC, 686, 312 );
		MoveToEx( hDC, 698, 330, NULL );
		LineTo( hDC, 686, 330 );
		MoveToEx( hDC, 698, 348, NULL );
		LineTo( hDC, 686, 348 );
		MoveToEx( hDC, 694, 368, NULL );
		LineTo( hDC, 682, 368 );
		MoveToEx( hDC, 690, 386, NULL );
		LineTo( hDC, 678, 386 );
		MoveToEx( hDC, 684, 406, NULL );
		LineTo( hDC, 672, 406 );
		MoveToEx( hDC, 676, 424, NULL );
		LineTo( hDC, 664, 424 );

		// bottom scale
		Arc( hDC, 258, 110, 698, 550, 384, 528, 572, 528 );
		MoveToEx( hDC, 384, 528, NULL );
		LineTo( hDC, 384, 516 );
		MoveToEx( hDC, 402, 536, NULL );
		LineTo( hDC, 402, 524 );
		MoveToEx( hDC, 422, 542, NULL );
		LineTo( hDC, 422, 530 );
		MoveToEx( hDC, 440, 546, NULL );
		LineTo( hDC, 440, 534 );
		MoveToEx( hDC, 460, 550, NULL );
		LineTo( hDC, 460, 538 );
		MoveToEx( hDC, 478, 550, NULL );
		LineTo( hDC, 478, 538 );
		MoveToEx( hDC, 496, 550, NULL );
		LineTo( hDC, 498, 538 );
		MoveToEx( hDC, 516, 546, NULL );
		LineTo( hDC, 516, 534 );
		MoveToEx( hDC, 534, 542, NULL );
		LineTo( hDC, 534, 530 );
		MoveToEx( hDC, 554, 536, NULL );
		LineTo( hDC, 554, 524 );
		MoveToEx( hDC, 572, 528, NULL );
		LineTo( hDC, 572, 516 );
		return;
	}

	void MDU::ADI_STATIC( oapi::Sketchpad* skp )
	{
		skp->SetFont( skpSSVBFont_h24w14 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Text( 698, 28, "R", 1 );
		skp->Text( 698, 58, "P", 1 );
		skp->Text( 698, 88, "Y", 1 );

		skp->SetPen( skpWhitePen );
		skp->Ellipse( 244, 86, 712, 564 );

		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpLightGrayBrush );
		oapi::IVECTOR2 diamond[4];
		diamond[0].x = 478;
		diamond[0].y = 106;
		diamond[1].x = 488;
		diamond[1].y = 124;
		diamond[2].x = 478;
		diamond[2].y = 142;
		diamond[3].x = 468;
		diamond[3].y = 122;
		skp->Polygon( diamond, 4 );// top
		//diamond[0].x = 478;
		diamond[0].y = 518;
		//diamond[1].x = 488;
		diamond[1].y = 536;
		//diamond[2].x = 478;
		diamond[2].y = 554;
		//diamond[3].x = 468;
		diamond[3].y = 536;
		skp->Polygon( diamond, 4 );// bottom
		diamond[0].x = 684;
		diamond[0].y = 320;
		diamond[1].x = 702;
		diamond[1].y = 330;
		diamond[2].x = 684;
		diamond[2].y = 340;
		diamond[3].x = 666;
		diamond[3].y = 330;
		skp->Polygon( diamond, 4 );// right
		diamond[0].x = 272;
		//diamond[0].y = 320;
		diamond[1].x = 290;
		//diamond[1].y = 330;
		diamond[2].x = 272;
		//diamond[2].y = 340;
		diamond[3].x = 254;
		//diamond[3].y = 330;
		skp->Polygon( diamond, 4 );// left

		// rate scales
		// top scale
		skp->SetPen( skpLightGrayPen );
		skp->Line( 308, 68, 648, 68 );
		skp->Line( 308, 66, 308, 88 );
		skp->Line( 342, 66, 342, 82 );
		skp->Line( 376, 66, 376, 82 );
		skp->Line( 410, 66, 410, 82 );
		skp->Line( 444, 66, 444, 82 );
		skp->Line( 478, 66, 478, 88 );
		skp->Line( 512, 66, 512, 82 );
		skp->Line( 546, 66, 546, 82 );
		skp->Line( 580, 66, 580, 82 );
		skp->Line( 614, 66, 614, 82 );
		skp->Line( 648, 66, 648, 88 );

		// side scale
		skp->Line( 740, 160, 740, 500 );
		skp->Line( 740, 160, 718, 160 );
		skp->Line( 740, 194, 724, 194 );
		skp->Line( 740, 228, 724, 228 );
		skp->Line( 740, 262, 724, 262 );
		skp->Line( 740, 296, 724, 296 );
		skp->Line( 740, 330, 718, 330 );
		skp->Line( 740, 364, 724, 364 );
		skp->Line( 740, 398, 724, 398 );
		skp->Line( 740, 432, 724, 432 );
		skp->Line( 740, 466, 724, 466 );
		skp->Line( 740, 500, 718, 500 );

		// bottom scale
		skp->Line( 308, 592, 648, 592 );
		skp->Line( 308, 592, 308, 570 );
		skp->Line( 342, 592, 342, 576 );
		skp->Line( 376, 592, 376, 576 );
		skp->Line( 410, 592, 410, 576 );
		skp->Line( 444, 592, 444, 576 );
		skp->Line( 478, 592, 478, 570 );
		skp->Line( 512, 592, 512, 576 );
		skp->Line( 546, 592, 546, 576 );
		skp->Line( 580, 592, 580, 576 );
		skp->Line( 614, 592, 614, 576 );
		skp->Line( 648, 592, 648, 570 );

		// roll lines
		skp->Line( 460, 130, 496, 530 );// 5º/185º
		skp->Line( 444, 134, 512, 526 );// 10º/190º
		skp->Line( 426, 136, 530, 524 );// 15º/195º
		skp->Line( 410, 142, 546, 518 );// 20º/200º
		skp->Line( 394, 148, 562, 512 );// 25º/205º

		skp->Line( 364, 166, 592, 494 );// 35º/215º
		skp->Line( 350, 176, 606, 484 );// 40º/220º
		skp->Line( 336, 188, 620, 472 );// 45º/225º
		skp->Line( 324, 202, 632, 458 );// 50º/230º
		skp->Line( 314, 216, 642, 444 );// 55º/235º

		skp->Line( 296, 246, 660, 414 );// 65º/245º
		skp->Line( 290, 262, 666, 398 );// 70º/250º
		skp->Line( 284, 278, 672, 382 );// 75º/255º
		skp->Line( 282, 296, 674, 364 );// 80º/260º
		skp->Line( 278, 312, 678, 348 );// 85º/265º

		skp->Line( 278, 348, 678, 312 );// 95º/275º
		skp->Line( 282, 364, 674, 296 );// 100º/280º
		skp->Line( 284, 382, 672, 278 );// 105º/285º
		skp->Line( 290, 398, 666, 262 );// 110º/290º
		skp->Line( 296, 414, 660, 246 );// 115º/295º

		skp->Line( 314, 444, 642, 216 );// 125º/305º
		skp->Line( 324, 458, 632, 202 );// 130º/310º
		skp->Line( 336, 472, 620, 188 );// 135º/315º
		skp->Line( 350, 484, 606, 176 );// 140º/320º
		skp->Line( 364, 494, 592, 166 );// 145º/325º

		skp->Line( 394, 512, 562, 148 );// 155º/335º
		skp->Line( 410, 518, 546, 142 );// 160º/340º
		skp->Line( 426, 524, 530, 136 );// 165º/345º
		skp->Line( 444, 526, 512, 134 );// 170º/350º
		skp->Line( 460, 530, 496, 130 );// 175º/355º
		skp->SetPen( skpLightGrayThickPen );
		skp->Line( 374, 150, 582, 510 );// 30º/210º
		skp->Line( 298, 226, 658, 434 );// 60º/240º
		skp->Line( 298, 434, 658, 226 );// 120º/300º
		skp->Line( 374, 510, 582, 150 );// 150º/330º

		// cover center for ADI SRCPAINT
		skp->SetBrush( _skpBlackBrush );
		skp->SetPen( _skpBlackPen );
		skp->Ellipse( 288, 140, 668, 520 );

		skp->Text( 588, 140, "33", 2 );
		skp->Text( 646, 198, "30", 2 );
		skp->Text( 646, 434, "24", 2 );
		skp->Text( 588, 494, "21", 2 );
		skp->Text( 342, 494, "15", 2 );
		skp->Text( 284, 434, "12", 2 );
		skp->Text( 284, 198, "06", 2 );
		skp->Text( 342, 140, "03", 2 );

		// att needles
		// top scale
		skp->SetPen( skpMagentaPen );
		skp->SetBrush( skpMagentaBrush );
		//Arc( 258, 110, 698, 550, 572, 132, 384, 132 );
		// HACK makeshift arc
		skp->Line( 384, 132, 402, 124 );
		skp->Line( 402, 124, 422, 118 );
		skp->Line( 422, 118, 440, 114 );
		skp->Line( 440, 114, 460, 110 );
		skp->Line( 460, 110, 478, 110 );
		skp->Line( 478, 110, 496, 110 );
		skp->Line( 496, 110, 516, 114 );
		skp->Line( 516, 114, 534, 118 );
		skp->Line( 534, 118, 554, 124 );
		skp->Line( 554, 124, 572, 132 );

		skp->Line( 384, 132, 384, 144 );
		skp->Line( 402, 124, 402, 136 );
		skp->Line( 422, 118, 422, 130 );
		skp->Line( 440, 114, 440, 126 );
		skp->Line( 460, 110, 460, 122 );
		skp->Line( 478, 110, 478, 122 );
		skp->Line( 496, 110, 496, 122 );
		skp->Line( 516, 114, 516, 126 );
		skp->Line( 534, 118, 534, 130 );
		skp->Line( 554, 124, 554, 136 );
		skp->Line( 572, 132, 572, 144 );

		// side scale
		//Arc( 258, 110, 698, 550, 676, 424, 676, 236 );
		// HACK makeshift arc
		skp->Line( 676, 236, 684, 254 );
		skp->Line( 684, 254, 690, 274 );
		skp->Line( 690, 274, 694, 292 );
		skp->Line( 694, 292, 698, 312 );
		skp->Line( 698, 312, 698, 330 );
		skp->Line( 698, 330, 698, 348 );
		skp->Line( 698, 348, 694, 368 );
		skp->Line( 694, 368, 690, 386 );
		skp->Line( 690, 386, 684, 406 );
		skp->Line( 684, 406, 676, 424 );

		skp->Line( 676, 236, 664, 236 );
		skp->Line( 684, 254, 672, 254 );
		skp->Line( 690, 274, 678, 274 );
		skp->Line( 694, 292, 682, 292 );
		skp->Line( 698, 312, 686, 312 );
		skp->Line( 698, 330, 686, 330 );
		skp->Line( 698, 348, 686, 348 );
		skp->Line( 694, 368, 682, 368 );
		skp->Line( 690, 386, 678, 386 );
		skp->Line( 684, 406, 672, 406 );
		skp->Line( 676, 424, 664, 424 );

		// bottom scale
		//Arc( 258, 110, 698, 550, 384, 528, 572, 528 );
		// HACK makeshift arc
		skp->Line( 384, 528, 402, 536 );
		skp->Line( 402, 536, 422, 542 );
		skp->Line( 422, 542, 440, 546 );
		skp->Line( 440, 546, 460, 550 );
		skp->Line( 460, 550, 478, 550 );
		skp->Line( 478, 550, 496, 550 );
		skp->Line( 496, 550, 516, 546 );
		skp->Line( 516, 546, 534, 542 );
		skp->Line( 534, 542, 554, 536 );
		skp->Line( 554, 536, 572, 528 );

		skp->Line( 384, 528, 384, 516 );
		skp->Line( 402, 536, 402, 524 );
		skp->Line( 422, 542, 422, 530 );
		skp->Line( 440, 546, 440, 534 );
		skp->Line( 460, 550, 460, 538 );
		skp->Line( 478, 550, 478, 538 );
		skp->Line( 496, 550, 498, 538 );
		skp->Line( 516, 546, 516, 534 );
		skp->Line( 534, 542, 534, 530 );
		skp->Line( 554, 536, 554, 524 );
		skp->Line( 572, 528, 572, 516 );
		return;
	}

	void MDU::ADI( HDC hDC, double sinpitch, double cospitch, double sinroll, double cosroll, double sinyaw, double cosyaw )
	{
		// center (478,330) r = 234
		// view r = 190, ball r = 190 * sqrt( 2 )
		// 90º pitch/yaw "FOV"

		double digitalpitch = atan2( sinpitch, cospitch );
		double ballpitch = digitalpitch * DEG;
		if (digitalpitch < 0.0) digitalpitch += PI2;
		double digitalroll = atan2( sinroll, cosroll );
		if (digitalroll < 0.0) digitalroll += PI2;
		double digitalyaw = atan2( sinyaw, cosyaw );
		if (digitalyaw > PI05) digitalyaw = PI - digitalyaw;
		if (digitalyaw < -PI05) digitalyaw = PI - digitalyaw;
		if (digitalyaw < 0.0) digitalyaw += PI2;

		// apply roll
		XFORM WTroll;
		WTroll.eM11 = (FLOAT)cosroll;
		WTroll.eM12 = -(FLOAT)sinroll;
		WTroll.eM21 = -WTroll.eM12;
		WTroll.eM22 = WTroll.eM11;
		WTroll.eDx = (FLOAT)(192 * (1 - WTroll.eM11 - WTroll.eM21));
		WTroll.eDy = (FLOAT)(192 * (1 - WTroll.eM11 + WTroll.eM21));
		SetGraphicsMode( hDC_ADI, GM_ADVANCED );
		SetWorldTransform( hDC_ADI, &WTroll );

		// 0º pitch line/labels
		int hP;
		double hP2;
		SetTextColor( hDC_ADI, CR_BLACK );
		SetBkColor( hDC_ADI, CR_WHITE );
		if (fabs( ballpitch ) <= 45)
		{
			hP = Round( 268.7 * sinpitch );
			if (ballpitch < 0)
			{
				SelectObject( hDC_ADI, gdiWhiteBrush );
				SelectObject( hDC_ADI, gdiWhitePen );
				Rectangle( hDC_ADI, 0, 0, 380, 190 );
				SelectObject( hDC_ADI, gdiDarkGrayBrush );
				SelectObject( hDC_ADI, gdiDarkGrayPen );
				Chord( hDC_ADI, -74, 190 - hP, 462, 190 + hP, 462, 190, -74, 190 );
				Rectangle( hDC_ADI, 0, 190, 380, 380 );
			}
			else
			{
				SelectObject( hDC_ADI, gdiDarkGrayBrush );
				SelectObject( hDC_ADI, gdiDarkGrayPen );
				Rectangle( hDC_ADI, 0, 190, 380, 380 );
				SelectObject( hDC_ADI, gdiWhiteBrush );
				SelectObject( hDC_ADI, gdiWhitePen );
				Chord( hDC_ADI, -74, 190 - hP, 462, 190 + hP, -74, 190, 462, 190 );
				Rectangle( hDC_ADI, 0, 0, 380, 190 );
			}
			hP = 186 + Round( 259.544828 * sinpitch );
			TextOut( hDC_ADI, 120, hP, "0", 1 );
			TextOut( hDC_ADI, 260, hP, "0", 1 );
		}
		else if (ballpitch > 0)
		{
			SelectObject( hDC_ADI, gdiWhiteBrush );
			Rectangle( hDC_ADI, -4, -4, 388, 388 );
		}
		else
		{
			SelectObject( hDC_ADI, gdiDarkGrayBrush );
			Rectangle( hDC_ADI, -4, -4, 388, 388 );
		}

		// pitch lines/labels for +30º/+60º/+90º/+120º/+150º
		SelectObject( hDC_ADI, gdiBlackPen );
		// +30º
		if (fabs( ballpitch - 30 ) <= 45)
		{
			hP2 = sinpitch * 232.701526 - cospitch * 134.350288;//hP = 138.592 * sin( (pitch - 30) * RAD );
			hP = Round( hP2 );
			if (ballpitch < 30) Arc( hDC_ADI, -74, 190 - hP, 462, 190 + hP, 462, 190, -74, 190 );
			else Arc( hDC_ADI, -74, 190 - hP, 462, 190 + hP, -74, 190, 462, 190 );
			hP = 178 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI, 120, hP, "3", 1 );
			TextOut( hDC_ADI, 260, hP, "3", 1 );
		}
		// +60º
		if (fabs( ballpitch - 60 ) <= 45)
		{
			hP2 = sinpitch * 134.350288 - cospitch * 232.701526;
			hP = Round( hP2 );
			if (ballpitch < 60) Arc( hDC_ADI, -74, 190 - hP, 462, 190 + hP, 462, 190, -74, 190 );
			else Arc( hDC_ADI, -74, 190 - hP, 462, 190 + hP, -74, 190, 462, 190 );
			hP = 178 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI, 120, hP, "6", 1 );
			TextOut( hDC_ADI, 260, hP, "6", 1 );
		}
		// +90º
		if (fabs( ballpitch - 90 ) <= 45)
		{
			hP2 = 268.700578 * (-cospitch);
			hP = Round( hP2 );
			if (ballpitch < 90) Arc( hDC_ADI, -74, 190 - hP, 462, 190 + hP, 462, 190, -74, 190 );
			else Arc( hDC_ADI, -74, 190 - hP, 462, 190 + hP, -74, 190, 462, 190 );
			hP = 178 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI, 120, hP, "9", 1 );
			TextOut( hDC_ADI, 260, hP, "9", 1 );
		}
		// +120º
		if (fabs( ballpitch - 120 ) <= 45)
		{
			hP2 = (-sinpitch) * 134.350288 - cospitch * 232.701526;
			hP = Round( hP2 );
			if (ballpitch < 120) Arc( hDC_ADI, -74, 190 - hP, 462, 190 + hP, 462, 190, -74, 190 );
			else Arc( hDC_ADI, -74, 190 - hP, 462, 190 + hP, -74, 190, 462, 190 );
			hP = 178 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI, 116, hP, "12", 2 );
			TextOut( hDC_ADI, 256, hP, "12", 2 );
		}
		// +150º
		if (fabs( ballpitch - 150 ) <= 45)
		{
			hP2 = (-sinpitch) * 232.701526 - cospitch * 134.350288;
			hP = Round( hP2 );
			if (ballpitch < 150) Arc( hDC_ADI, -74, 190 - hP, 462, 190 + hP, 462, 190, -74, 190 );
			else Arc( hDC_ADI, -74, 190 - hP, 462, 190 + hP, -74, 190, 462, 190 );
			hP = 178 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI, 116, hP, "15", 2 );
			TextOut( hDC_ADI, 256, hP, "15", 2 );
		}

		// pitch lines/labels for -30º/-60º/-90º/-120º/-150º
		SelectObject( hDC_ADI, gdiWhitePen );
		SetTextColor( hDC_ADI, CR_WHITE );
		SetBkColor( hDC_ADI, CR_DARK_GRAY );
		// -30º
		if (fabs( ballpitch + 30 ) <= 45)
		{
			hP2 = sinpitch * 232.701526 + cospitch * 134.350288;
			hP = Round( hP2 );
			if (ballpitch < -30) Arc( hDC_ADI, -74, 190 - hP, 462, 190 + hP, 462, 190, -74, 190 );
			else Arc( hDC_ADI, -74, 190 - hP, 462, 190 + hP, -74, 190, 462, 190 );
			hP = 178 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI, 116, hP, "33", 2 );
			TextOut( hDC_ADI, 256, hP, "33", 2 );
		}
		// -60º
		if (fabs( ballpitch + 60 ) <= 45)
		{
			hP2 = sinpitch * 134.350288 + cospitch * 232.701526;
			hP = Round( hP2 );
			if (ballpitch < -60) Arc( hDC_ADI, -74, 190 - hP, 462, 190 + hP, 462, 190, -74, 190 );
			else Arc( hDC_ADI, -74, 190 - hP, 462, 190 + hP, -74, 190, 462, 190 );
			hP = 178 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI, 116, hP, "30", 2 );
			TextOut( hDC_ADI, 256, hP, "30", 2 );
		}
		// -90º
		if (fabs( ballpitch + 90 ) <= 45)
		{
			hP2 = 268.700578 * cospitch;
			hP = Round( hP2 );
			if (ballpitch < -90) Arc( hDC_ADI, -74, 190 - hP, 462, 190 + hP, 462, 190, -74, 190 );
			else Arc( hDC_ADI, -74, 190 - hP, 462, 190 + hP, -74, 190, 462, 190 );
			hP = 178 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI, 118, hP, "27", 2 );
			TextOut( hDC_ADI, 256, hP, "27", 2 );
		}
		// -120º
		if (fabs( ballpitch + 120 ) <= 45)
		{
			hP2 = (-sinpitch) * 134.350288 + cospitch * 232.701526;
			hP = Round( hP2 );
			if (ballpitch < -120) Arc( hDC_ADI, -74, 190 - hP, 462, 190 + hP, 462, 190, -74, 190 );
			else Arc( hDC_ADI, -74, 190 - hP, 462, 190 + hP, -74, 190, 462, 190 );
			hP = 178 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI, 118, hP, "24", 2 );
			TextOut( hDC_ADI, 256, hP, "24", 2 );
		}
		// -150º
		if (fabs( ballpitch + 150 ) <= 45)
		{
			hP2 = (-sinpitch) * 232.701526 + cospitch * 134.350288;
			hP = Round( hP2 );
			if (ballpitch < -150) Arc( hDC_ADI, -74, 190 - hP, 462, 190 + hP, 462, 190, -74, 190 );
			else Arc( hDC_ADI, -74, 190 - hP, 462, 190 + hP, -74, 190, 462, 190 );
			hP = 178 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI, 118, hP, "21", 2 );
			TextOut( hDC_ADI, 256, hP, "21", 2 );
		}

		// TODO yaw
		// HACK
		// "central plane"
		SelectObject( hDC_ADI, gdiWhiteBrush );
		SelectObject( hDC_ADI, gdiBlackPen );
		Rectangle( hDC_ADI, 184, 0, 196, 384 );
		MoveToEx( hDC_ADI, 190, 0, NULL );
		LineTo( hDC_ADI, 190, 380 );

		SelectObject( hDC_ADI, gdiBlackPen );
		// yaw line 30º (above horizon)
		MoveToEx( hDC_ADI, 326, 0, NULL );
		LineTo( hDC_ADI, 326, 194 + Round( 232.699964 * sinpitch ) );
		// yaw line 330º (above horizon)
		MoveToEx( hDC_ADI, 54, 0, NULL );
		LineTo( hDC_ADI, 54, 194 + Round( 232.699964 * sinpitch ) );
		SelectObject( hDC_ADI, gdiWhitePen );
		// yaw line 30º (below horizon)
		MoveToEx( hDC_ADI, 326, 380, NULL );
		LineTo( hDC_ADI, 326, 194 + Round( 232.699964 * sinpitch ) );
		// yaw line 330º (below horizon)
		MoveToEx( hDC_ADI, 54, 380, NULL );
		LineTo( hDC_ADI, 54, 194 + Round( 232.699964 * sinpitch ) );

		// TODO yaw labels

		// roll triangle
		SelectObject( hDC_ADI, gdiLightGreenPen );
		SelectObject( hDC_ADI, gdiLightGreenBrush );
		POINT tri[3];
		tri[0].x = 190;
		tri[0].y = 2;
		tri[1].x = 180;
		tri[1].y = 22;
		tri[2].x = 200;
		tri[2].y = 22;
		Polygon( hDC_ADI, tri, 3 );

		// clean up
		ModifyWorldTransform( hDC_ADI, &WTroll, MWT_IDENTITY );
		SetGraphicsMode( hDC_ADI, GM_COMPATIBLE );

		// digital RPY
		SetTextColor( hDC, CR_WHITE );
		char cbuf[8];
		sprintf_s( cbuf, 8, "%03.0f", digitalroll * DEG );
		TextOut( hDC, 724, 28, cbuf, strlen( cbuf ) );
		sprintf_s( cbuf, 8, "%03.0f", digitalpitch * DEG );
		TextOut( hDC, 724, 58, cbuf, strlen( cbuf ) );
		sprintf_s( cbuf, 8, "%03.0f", digitalyaw * DEG );
		TextOut( hDC, 724, 88, cbuf, strlen( cbuf ) );

		// copy ball
		BitBlt( hDC_ADI, 0, 0, 384, 384, hDC_ADIMASK, 0, 0, SRCAND );
		BitBlt( hDC, 288, 140, 380, 380, hDC_ADI, 1, 1, SRCPAINT );

		// flight director
		SelectObject( hDC, gdiBlackPen );
		SelectObject( hDC, gdiLightGreenBrush );
		static const POINT fd[18] = {{406,326},{406,334},{446,334},{456,350},{472,362},{484,362},{500,350},{510,334},{550,334},{550,326},{502,326},{502,334},{496,346},{484,354},{472,354},{460,346},{454,334},{454,326}};
		Polygon( hDC, fd, 18 );
		// center marker
		SelectObject( hDC, gdiLightGreenPen );
		Rectangle( hDC, 476, 274, 480, 386 );
		Rectangle( hDC, 422, 328, 534, 332 );
		return;
	}

	void MDU::ADI( oapi::Sketchpad* skp, double sinpitch, double cospitch, double sinroll, double cosroll, double sinyaw, double cosyaw )
	{
		// center (478,330) r = 234
		// view r = 190, ball r = 190 * sqrt( 2 )
		// 90º pitch/yaw "FOV"

		double digitalpitch = atan2( sinpitch, cospitch );
		if (digitalpitch < 0.0) digitalpitch += PI2;
		double digitalroll = atan2( sinroll, cosroll );
		if (digitalroll < 0.0) digitalroll += PI2;
		double digitalyaw = atan2( sinyaw, cosyaw );
		if (digitalyaw > PI05) digitalyaw = PI - digitalyaw;
		if (digitalyaw < -PI05) digitalyaw = PI - digitalyaw;
		if (digitalyaw < 0.0) digitalyaw += PI2;

		// draw ball mesh
		oapi::FMATRIX4 mat;
		int H = 660;
		int W = 956;

		VECTOR3 xdir = _V( cosyaw * cosroll, -sinroll, -cosroll * sinyaw );
		VECTOR3 zdir = _V( sinyaw * cospitch - sinroll * cosyaw * sinpitch, -cosroll * sinpitch, cospitch * cosyaw + sinyaw * sinroll * sinpitch );
		STS()->D3D9()->WorldMatrix( &mat, _V( W / 2, H / 2, W + 252 ), xdir, zdir, 2.687 );

		skp->SetWorldTransform( &mat );
		skp->SetPen( skpWhitePen );
		skp->DrawMeshGroup( hADIball, 0, oapi::Sketchpad::MeshFlags::RENDER_ALL );
		skp->SetWorldTransform();

		// roll triangle
		skp->SetPen( skpLightGreenPen );
		skp->SetBrush( skpLightGreenBrush );
		oapi::IVECTOR2 tri[3];
		tri[0].x = (long)(478 - 190 * sinroll);
		tri[0].y = (long)(330 - 190 * cosroll);
		tri[1].x = (long)(478 - 10 * cosroll - 168 * sinroll);
		tri[1].y = (long)(330 + 10 * sinroll - 168 * cosroll);
		tri[2].x = (long)(478 + 10 * cosroll - 168 * sinroll);
		tri[2].y = (long)(330 - 10 * sinroll - 168 * cosroll);
		skp->Polygon( tri, 3 );

		// digital RPY
		skp->SetTextColor( CR_WHITE );
		char cbuf[8];
		sprintf_s( cbuf, 8, "%03.0f", digitalroll * DEG );
		skp->Text( 724, 28, cbuf, strlen( cbuf ) );
		sprintf_s( cbuf, 8, "%03.0f", digitalpitch * DEG );
		skp->Text( 724, 58, cbuf, strlen( cbuf ) );
		sprintf_s( cbuf, 8, "%03.0f", digitalyaw * DEG );
		skp->Text( 724, 88, cbuf, strlen( cbuf ) );

		// flight director
		skp->SetPen( skpBlackPen );
		static const oapi::IVECTOR2 fd[18] = {{406,326},{406,334},{446,334},{456,350},{472,362},{484,362},{500,350},{510,334},{550,334},{550,326},{502,326},{502,334},{496,346},{484,354},{472,354},{460,346},{454,334},{454,326}};
		skp->Polygon( fd, 18 );
		// center marker
		skp->SetPen( skpLightGreenPen );
		skp->Rectangle( 476, 274, 480, 386 );
		skp->Rectangle( 422, 328, 534, 332 );
		return;
	}

	static void GetADIRateLabel( char* txt, unsigned short num )
	{
		double n = num;
		char k = 0;
		if (n >= 1000)
		{
			k = 'K';
			n /= 1000;
		}
		sprintf( txt, "%g%c", n, k );
		return;
	}

	void MDU::ADI_RATE( HDC hDC, unsigned short pitchrate, unsigned short rollrate, unsigned short yawrate, unsigned short pitchratescale, unsigned short rollratescale, unsigned short yawratescale, unsigned short TGOSEC, unsigned short ADIRR_0_ON_R )
	{
		POINT tri[3];
		char txt[8];

		SelectObject( hDC, gdiSSVBFont_h24w14 );
		
		SelectObject( hDC, gdiLightGreenPen );
		SelectObject( hDC, gdiLightGreenBrush );

		if ((rollratescale > 0) || (TGOSEC == 1))
		{
			// labels
			if (TGOSEC == 0)
			{
				SetTextAlign( hDC, TA_CENTER );
				SetTextColor( hDC, CR_LIGHT_GRAY );
				TextOut( hDC, 472, 36, "0", 1 );

				sprintf( txt, "%d", rollratescale );
				SetTextColor( hDC, CR_WHITE );
				SetTextAlign( hDC, TA_RIGHT );
				TextOut( hDC, 302, 62, txt, strlen( txt ) );
				SetTextAlign( hDC, TA_LEFT );
				TextOut( hDC, 654, 62, txt, strlen( txt ) );
			}
			else
			{
				char txtL[8];
				char txtR[8];
				if (ADIRR_0_ON_R == 0)
				{
					strcpy( txtL, "0" );
					strcpy( txtR, "10" );
				}
				else
				{
					strcpy( txtL, "10" );
					strcpy( txtR, "0" );
				}
				SetTextColor( hDC, CR_WHITE );
				SetTextAlign( hDC, TA_RIGHT );
				TextOut( hDC, 302, 62, txtL, strlen( txtL ) );
				SetTextAlign( hDC, TA_LEFT );
				TextOut( hDC, 654, 62, txtR, strlen( txtR ) );
			}

			// triangles
			tri[0].x = 478 + Round( static_cast<short>(rollrate) * (170.0 / (4095 * 8)) );
			tri[0].y = 68;
			tri[1].x = tri[0].x + 20;
			tri[1].y = 36;
			tri[2].x = tri[0].x - 20;
			tri[2].y = 36;
			Polygon( hDC, tri, 3 );
		}

		if (pitchratescale > 0)
		{
			// labels
			SetTextAlign( hDC, TA_CENTER );
			SetTextColor( hDC, CR_LIGHT_GRAY );
			TextOut( hDC, 750, 318, "0", 1 );

			GetADIRateLabel( txt, pitchratescale );
			SetTextColor( hDC, CR_WHITE );
			SetTextAlign( hDC, TA_LEFT );
			TextOut( hDC, 712, 130, txt, strlen( txt ) );
			TextOut( hDC, 712, 502, txt, strlen( txt ) );

			// triangles
			tri[0].x = 740;
			tri[0].y = 330 - Round( static_cast<short>(pitchrate) * (170.0 / (4095 * 8)) );
			tri[1].x = 772;
			tri[1].y = tri[0].y - 20;
			tri[2].x = 772;
			tri[2].y = tri[0].y + 20;
			Polygon( hDC, tri, 3 );
		}

		if (yawratescale > 0)
		{
			// labels
			SetTextAlign( hDC, TA_CENTER );
			SetTextColor( hDC, CR_LIGHT_GRAY );
			TextOut( hDC, 472, 596, "0", 1 );

			GetADIRateLabel( txt, yawratescale );
			SetTextColor( hDC, CR_WHITE );
			SetTextAlign( hDC, TA_RIGHT );
			TextOut( hDC, 302, 566, txt, strlen( txt ) );
			SetTextAlign( hDC, TA_LEFT );
			TextOut( hDC, 654, 566, txt, strlen( txt ) );

			// triangles
			tri[0].x = 478 + Round( static_cast<short>(yawrate) * (170.0 / (4095 * 8)) );
			tri[0].y = 592;
			tri[1].x = tri[0].x - 20;
			tri[1].y = 624;
			tri[2].x = tri[0].x + 20;
			tri[2].y = 624;
			Polygon( hDC, tri, 3 );
		}
		return;
	}

	void MDU::ADI_RATE( oapi::Sketchpad* skp, unsigned short pitchrate, unsigned short rollrate, unsigned short yawrate, unsigned short pitchratescale, unsigned short rollratescale, unsigned short yawratescale, unsigned short TGOSEC, unsigned short ADIRR_0_ON_R )
	{
		oapi::IVECTOR2 tri[3];
		char txt[8];

		skp->SetFont( skpSSVBFont_h24w14 );
		
		skp->SetPen( skpLightGreenPen );
		skp->SetBrush( skpLightGreenBrush );

		if ((rollratescale > 0) || (TGOSEC == 1))
		{
			// labels
			if (TGOSEC == 0)
			{
				skp->SetTextAlign( oapi::Sketchpad::CENTER );
				skp->SetTextColor( CR_LIGHT_GRAY );
				skp->Text( 472, 36, "0", 1 );

				sprintf( txt, "%d", rollratescale );
				skp->SetTextColor( CR_WHITE );
				skp->SetTextAlign( oapi::Sketchpad::RIGHT );
				skp->Text( 302, 62, txt, strlen( txt ) );
				skp->SetTextAlign( oapi::Sketchpad::LEFT );
				skp->Text( 654, 62, txt, strlen( txt ) );
			}
			else
			{
				char txtL[8];
				char txtR[8];
				if (ADIRR_0_ON_R == 0)
				{
					strcpy( txtL, "0" );
					strcpy( txtR, "10" );
				}
				else
				{
					strcpy( txtL, "10" );
					strcpy( txtR, "0" );
				}
				skp->SetTextColor( CR_WHITE );
				skp->SetTextAlign( oapi::Sketchpad::RIGHT );
				skp->Text( 302, 62, txtL, strlen( txtL ) );
				skp->SetTextAlign( oapi::Sketchpad::LEFT );
				skp->Text( 654, 62, txtR, strlen( txtR ) );
			}

			// triangles
			tri[0].x = 478 + Round( static_cast<short>(rollrate) * (170.0 / (4095 * 8)) );
			tri[0].y = 68;
			tri[1].x = tri[0].x + 20;
			tri[1].y = 36;
			tri[2].x = tri[0].x - 20;
			tri[2].y = 36;
			skp->Polygon( tri, 3 );
		}

		if (pitchratescale > 0)
		{
			// labels
			skp->SetTextAlign( oapi::Sketchpad::CENTER );
			skp->SetTextColor( CR_LIGHT_GRAY );
			skp->Text( 750, 318, "0", 1 );

			GetADIRateLabel( txt, pitchratescale );
			skp->SetTextColor( CR_WHITE );
			skp->SetTextAlign( oapi::Sketchpad::LEFT );
			skp->Text( 712, 130, txt, strlen( txt ) );
			skp->Text( 712, 502, txt, strlen( txt ) );

			// triangles
			tri[0].x = 740;
			tri[0].y = 330 - Round( static_cast<short>(pitchrate) * (170.0 / (4095 * 8)) );
			tri[1].x = 772;
			tri[1].y = tri[0].y - 20;
			tri[2].x = 772;
			tri[2].y = tri[0].y + 20;
			skp->Polygon( tri, 3 );
		}

		if (yawratescale > 0)
		{
			// labels
			skp->SetTextAlign( oapi::Sketchpad::CENTER );
			skp->SetTextColor( CR_LIGHT_GRAY );
			skp->Text( 472, 596, "0", 1 );

			GetADIRateLabel( txt, yawratescale );
			skp->SetTextColor( CR_WHITE );
			skp->SetTextAlign( oapi::Sketchpad::RIGHT );
			skp->Text( 302, 566, txt, strlen( txt ) );
			skp->SetTextAlign( oapi::Sketchpad::LEFT );
			skp->Text( 654, 566, txt, strlen( txt ) );

			// triangles
			tri[0].x = 478 + Round( static_cast<short>(yawrate) * (170.0 / (4095 * 8)) );
			tri[0].y = 592;
			tri[1].x = tri[0].x - 20;
			tri[1].y = 624;
			tri[2].x = tri[0].x + 20;
			tri[2].y = 624;
			skp->Polygon( tri, 3 );
		}
		return;
	}

	static void GetADIErrorLabel( char* txt, unsigned short num )
	{
		double n = num * 0.25;
		char g = 0;
		if ((num & 0b10) || (num & 0b01))
		{
			g = 'g';
			if (num & 0b01) n -= 0.05;// no space for the 0.05
		}
		sprintf( txt, "%g%c", n, g );
		return;
	}

	void MDU::ADI_ERROR( HDC hDC, unsigned short pitcherror, unsigned short rollerror, unsigned short yawerror, unsigned short pitcherrorscale )
	{
		double pos;
		char txt[8];

		// labels
		SetTextColor( hDC, CR_MAGENTA );
		SelectObject( hDC, gdiSSVBFont_h24w14 );
		GetADIErrorLabel( txt, pitcherrorscale );
		TextOut( hDC, 674, 210, txt, strlen( txt ) );
		TextOut( hDC, 674, 416, txt, strlen( txt ) );

		// needles
		SelectObject( hDC, gdiMagentaPen );
		SelectObject( hDC, gdiMagentaBrush );

		pos = -(static_cast<short>(rollerror) * (94.0 / (4095 * 8)));
		Rectangle( hDC, 476 + Round( pos ), 330 - Round( sqrt( 48400 - (pos * pos) ) ), 480 + Round( pos ), 268 );

		pos = (static_cast<short>(pitcherror) * (94.0 / (4095 * 8)));
		Rectangle( hDC, 540, 328 + Round( pos ), 478 + Round( sqrt( 48400 - (pos * pos) ) ), 332 + Round( pos ) );

		pos = -(static_cast<short>(yawerror) * (94.0 / (4095 * 8)));
		Rectangle( hDC, 476 + Round( pos ), 392, 480 + Round( pos ), 330 + Round( sqrt( 48400 - (pos * pos) ) ) );
		return;
	}

	void MDU::ADI_ERROR( oapi::Sketchpad* skp, unsigned short pitcherror, unsigned short rollerror, unsigned short yawerror, unsigned short pitcherrorscale )
	{
		double pos;
		char txt[8];

		// labels
		skp->SetTextColor( CR_MAGENTA );
		skp->SetFont( skpSSVBFont_h24w14 );
		GetADIErrorLabel( txt, pitcherrorscale );
		skp->Text( 674, 210, txt, strlen( txt ) );
		skp->Text( 674, 416, txt, strlen( txt ) );

		// needles
		skp->SetPen( skpMagentaPen );
		skp->SetBrush( skpMagentaBrush );

		pos = -(static_cast<short>(rollerror) * (94.0 / (4095 * 8)));
		skp->Rectangle( 476 + Round( pos ), 330 - Round( sqrt( 48400 - (pos * pos) ) ), 480 + Round( pos ), 268 );

		pos = (static_cast<short>(pitcherror) * (94.0 / (4095 * 8)));
		skp->Rectangle( 540, 328 + Round( pos ), 478 + Round( sqrt( 48400 - (pos * pos) ) ), 332 + Round( pos ) );

		pos = -(static_cast<short>(yawerror) * (94.0 / (4095 * 8)));
		skp->Rectangle( 476 + Round( pos ), 392, 480 + Round( pos ), 330 + Round( sqrt( 48400 - (pos * pos) ) ) );
		return;
	}

	void MDU::HSI_A( HDC hDC, double heading, unsigned short roll_sw, bool drawcourse, double course, bool drawCDI, bool CDIflag, double CDIscale, double CDIdeviation, char primarytype, double primarybearing, char secondarytype, double secondarybearing )
	{
		double sgn = (roll_sw == 0) ? 1 : -1;

		// center (478,872) r = 190
		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiBlackBrush );
		::Ellipse( hDC, 268, 662, 688, 1082 );// r = 210

		MoveToEx( hDC, 268, 872, NULL );
		LineTo( hDC, 256, 872 );
		MoveToEx( hDC, 330, 724, NULL );
		LineTo( hDC, 318, 712 );
		MoveToEx( hDC, 476, 682, NULL );
		LineTo( hDC, 476, 650 );
		MoveToEx( hDC, 480, 682, NULL );
		LineTo( hDC, 480, 650 );
		MoveToEx( hDC, 626, 724, NULL );
		LineTo( hDC, 638, 712 );
		MoveToEx( hDC, 688, 872, NULL );
		LineTo( hDC, 700, 872 );

		SelectObject( hDC, gdiWhitePen );
		SelectObject( hDC, gdiDarkGrayBrush );
		::Ellipse( hDC, 288, 682, 668, 1062 );// r = 190

		SelectObject( hDC, gdiBlackBrush );
		::Ellipse( hDC, 354, 748, 602, 996 );// r = 190

		int x1;
		int y1;
		int x2;
		int y2;
		double cosi;
		double sini;
		for (int i = 90; i != 0; i -= 10)// big lines (20px)
		{
			cosi = cos( (i * RAD) + (heading * sgn) );
			sini = sin( (i * RAD) + (heading * sgn) );
			x1 = Round( 190 * cosi );
			y1 = Round( 190 * sini );

			x2 = Round( 170 * cosi );
			y2 = Round( 170 * sini );

			MoveToEx( hDC, 478 + x1, 872 - y1, NULL );
			LineTo( hDC, 478 + x2, 872 - y2 );

			MoveToEx( hDC, 478 + y1, 872 + x1, NULL );
			LineTo( hDC, 478 + y2, 872 + x2 );

			MoveToEx( hDC, 478 - x1, 872 + y1, NULL );
			LineTo( hDC, 478 - x2, 872 + y2 );

			MoveToEx( hDC, 478 - y1, 872 - x1, NULL );
			LineTo( hDC, 478 - y2, 872 - x2 );
		}
		for (int i = 85; i > 0; i -= 10)// small lines (10px)
		{
			cosi = cos( (i * RAD) + (heading * sgn) );
			sini = sin( (i * RAD) + (heading * sgn) );
			x1 = Round( 190 * cosi );
			y1 = Round( 190 * sini );

			x2 = Round( 180 * cosi );
			y2 = Round( 180 * sini );

			MoveToEx( hDC, 478 + x1, 872 - y1, NULL );
			LineTo( hDC, 478 + x2, 872 - y2 );

			MoveToEx( hDC, 478 + y1, 872 + x1, NULL );
			LineTo( hDC, 478 + y2, 872 + x2 );

			MoveToEx( hDC, 478 - x1, 872 + y1, NULL );
			LineTo( hDC, 478 - x2, 872 + y2 );

			MoveToEx( hDC, 478 - y1, 872 - x1, NULL );
			LineTo( hDC, 478 - y2, 872 - x2 );
		}

		SetTextColor( hDC, CR_WHITE );
		SelectObject( hDC, gdiSSVBFont_h24w14 );
		XFORM WTroll;
		char cbuf[4];
		SetGraphicsMode( hDC, GM_ADVANCED );
		for (int i = 0; i <= 33; i += 3)
		{
			// rotate
			WTroll.eM11 = (FLOAT)cos( (heading * sgn) - i * 10 * RAD * sgn );
			WTroll.eM12 = (FLOAT)(-sin( (heading * sgn) - i * 10 * RAD * sgn ));
			WTroll.eM21 = -WTroll.eM12;
			WTroll.eM22 = WTroll.eM11;
			WTroll.eDx = (FLOAT)(478 - (478 * WTroll.eM11) - (872 * WTroll.eM21));
			WTroll.eDy = (FLOAT)(872 - (872 * WTroll.eM11) + (478 * WTroll.eM21));
			SetWorldTransform( hDC, &WTroll );

			// paint
			sprintf_s( cbuf, 4, "%d", i );// number
			TextOut( hDC, 478 - strlen( cbuf ) * 8, 718, cbuf, strlen( cbuf ) );

			// de-rotate
			ModifyWorldTransform( hDC, &WTroll, MWT_IDENTITY );
		}

		// rotate to course arrow and CDI heading
		WTroll.eM11 = (FLOAT)cos( -course );
		WTroll.eM12 = (FLOAT)(-sin( -course ));
		WTroll.eM21 = -WTroll.eM12;
		WTroll.eM22 = WTroll.eM11;
		WTroll.eDx = (FLOAT)(478 - (478 * WTroll.eM11) - (872 * WTroll.eM21));
		WTroll.eDy = (FLOAT)(872 - (872 * WTroll.eM11) + (478 * WTroll.eM21));
		SetWorldTransform( hDC, &WTroll );

		if (drawcourse) HSI_CourseArrow( hDC );
		if (drawCDI) HSI_CDI( hDC, CDIflag, CDIscale, CDIdeviation );

		// de-rotate
		ModifyWorldTransform( hDC, &WTroll, MWT_IDENTITY );
		SetGraphicsMode( hDC, GM_COMPATIBLE );

		HSI_Bearing( hDC, primarytype, primarybearing, secondarytype, secondarybearing );

		static const POINT ov_symbol[6] = {{478,838},{484,874},{492,884},{478,898},{464,884},{472,874}};
		SelectObject( hDC, gdiLightGrayBrush );
		SelectObject( hDC, gdiLightGrayPen );
		Polygon( hDC, ov_symbol, 6 );

		// "delete" bottom area where the menu will be
		SelectObject( hDC, gdiBlackBrush );
		SelectObject( hDC, gdiBlackPen );
		Rectangle( hDC, 234, 912, 722, 1024 );
		return;
	}

	void MDU::HSI_A( oapi::Sketchpad* skp, double heading, unsigned short roll_sw, bool drawcourse, double course, bool drawCDI, bool CDIflag, double CDIscale, double CDIdeviation, char primarytype, double primarybearing, char secondarytype, double secondarybearing )
	{
		double sgn = (roll_sw == 0) ? 1 : -1;

		// center (478,872) r = 190
		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpBlackBrush );
		skp->Ellipse( 268, 662, 688, 1082 );// r = 210

		skp->Line( 268, 872, 256, 872 );
		skp->Line( 330, 724, 318, 712 );
		skp->Line( 476, 682, 476, 650 );
		skp->Line( 480, 682, 480, 650 );
		skp->Line( 626, 724, 638, 712 );
		skp->Line( 688, 872, 700, 872 );

		skp->SetPen( skpWhitePen );
		skp->SetBrush( skpDarkGrayBrush );
		skp->Ellipse( 288, 682, 668, 1062 );// r = 190

		skp->SetBrush( skpBlackBrush );
		skp->Ellipse( 354, 748, 602, 996 );// r = 190

		int x1;
		int y1;
		int x2;
		int y2;
		double cosi;
		double sini;
		for (int i = 90; i != 0; i -= 10)// big lines (20px)
		{
			cosi = cos( (i * RAD) + (heading * sgn) );
			sini = sin( (i * RAD) + (heading * sgn) );
			x1 = Round( 190 * cosi );
			y1 = Round( 190 * sini );

			x2 = Round( 170 * cosi );
			y2 = Round( 170 * sini );

			skp->Line( 478 + x1, 872 - y1, 478 + x2, 872 - y2 );

			skp->Line( 478 + y1, 872 + x1, 478 + y2, 872 + x2 );

			skp->Line( 478 - x1, 872 + y1, 478 - x2, 872 + y2 );

			skp->Line( 478 - y1, 872 - x1, 478 - y2, 872 - x2 );
		}

		for (int i = 85; i > 0; i -= 10)// small lines (10px)
		{
			cosi = cos( (i * RAD) + (heading * sgn) );
			sini = sin( (i * RAD) + (heading * sgn) );
			x1 = Round( 190 * cosi );
			y1 = Round( 190 * sini );

			x2 = Round( 180 * cosi );
			y2 = Round( 180 * sini );

			skp->Line( 478 + x1, 872 - y1, 478 + x2, 872 - y2 );

			skp->Line( 478 + y1, 872 + x1, 478 + y2, 872 + x2 );

			skp->Line( 478 - x1, 872 + y1, 478 - x2, 872 + y2 );

			skp->Line( 478 - y1, 872 - x1, 478 - y2, 872 - x2 );
		}

		skp->SetTextColor( CR_WHITE );
		skp->SetFont( skpSSVBFont_h24w14 );
		char cbuf[4];
		oapi::IVECTOR2 cntr;
		cntr.x = 478;
		cntr.y = 872;
		for (int i = 0; i <= 33; i += 3)
		{
			// rotate
			skp->SetWorldTransform2D( 1.0f, (float)(i * 10 * RAD * sgn - (heading * sgn)), &cntr );

			// paint
			sprintf_s( cbuf, 4, "%d", i );// number
			skp->Text( 478 - strlen( cbuf ) * 8, 718, cbuf, strlen( cbuf ) );

			// de-rotate
			skp->SetWorldTransform();
		}

		// rotate to course arrow and CDI heading
		skp->SetWorldTransform2D( 1.0f, (float)(course), &cntr );

		if (drawcourse) HSI_CourseArrow( skp );
		if (drawCDI) HSI_CDI( skp, CDIflag, CDIscale, CDIdeviation );

		// de-rotate
		skp->SetWorldTransform();

		HSI_Bearing( skp, primarytype, primarybearing, secondarytype, secondarybearing );

		static const oapi::IVECTOR2 ov_symbol[6] = {{478,838},{484,874},{492,884},{478,898},{464,884},{472,874}};
		skp->SetBrush( skpLightGrayBrush );
		skp->SetPen( skpLightGrayPen );
		skp->Polygon( ov_symbol, 6 );

		// "delete" bottom area where the menu will be
		skp->SetBrush( skpBlackBrush );
		skp->SetPen( skpBlackPen );
		skp->Rectangle( 234, 912, 722, 1024 );
		return;
	}

	void MDU::HSI_E( HDC hDC, double heading, bool drawcourse, double course, bool drawCDI, bool CDIflag, double CDIscale, double CDIdeviation, char primarytype, double primarybearing, char secondarytype, double secondarybearing )
	{
		// center (478,872) r = 190
		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiBlackBrush );
		::Ellipse( hDC, 268, 662, 688, 1082 );// r = 210

		MoveToEx( hDC, 268, 872, NULL );
		LineTo( hDC, 256, 872 );
		MoveToEx( hDC, 330, 724, NULL );
		LineTo( hDC, 318, 712 );
		MoveToEx( hDC, 476, 682, NULL );
		LineTo( hDC, 476, 650 );
		MoveToEx( hDC, 480, 682, NULL );
		LineTo( hDC, 480, 650 );
		MoveToEx( hDC, 626, 724, NULL );
		LineTo( hDC, 638, 712 );
		MoveToEx( hDC, 688, 872, NULL );
		LineTo( hDC, 700, 872 );

		SelectObject( hDC, gdiWhitePen );
		SelectObject( hDC, gdiDarkGrayBrush );
		::Ellipse( hDC, 288, 682, 668, 1062 );// r = 190

		SelectObject( hDC, gdiBlackBrush );
		::Ellipse( hDC, 354, 748, 602, 996 );// r = 190

		int x1;
		int y1;
		int x2;
		int y2;
		double cosi;
		double sini;
		for (int i = 90; i != 0; i -= 10)// big lines (20px)
		{
			cosi = cos( (i * RAD) + heading );
			sini = sin( (i * RAD) + heading );
			x1 = Round( 190 * cosi );
			y1 = Round( 190 * sini );

			x2 = Round( 170 * cosi );
			y2 = Round( 170 * sini );

			MoveToEx( hDC, 478 + x1, 872 - y1, NULL );
			LineTo( hDC, 478 + x2, 872 - y2 );

			MoveToEx( hDC, 478 + y1, 872 + x1, NULL );
			LineTo( hDC, 478 + y2, 872 + x2 );

			MoveToEx( hDC, 478 - x1, 872 + y1, NULL );
			LineTo( hDC, 478 - x2, 872 + y2 );

			MoveToEx( hDC, 478 - y1, 872 - x1, NULL );
			LineTo( hDC, 478 - y2, 872 - x2 );
		}
		for (int i = 85; i > 0; i -= 10)// small lines (10px)
		{
			cosi = cos( (i * RAD) + heading );
			sini = sin( (i * RAD) + heading );
			x1 = Round( 190 * cosi );
			y1 = Round( 190 * sini );

			x2 = Round( 180 * cosi );
			y2 = Round( 180 * sini );

			MoveToEx( hDC, 478 + x1, 872 - y1, NULL );
			LineTo( hDC, 478 + x2, 872 - y2 );

			MoveToEx( hDC, 478 + y1, 872 + x1, NULL );
			LineTo( hDC, 478 + y2, 872 + x2 );

			MoveToEx( hDC, 478 - x1, 872 + y1, NULL );
			LineTo( hDC, 478 - x2, 872 + y2 );

			MoveToEx( hDC, 478 - y1, 872 - x1, NULL );
			LineTo( hDC, 478 - y2, 872 - x2 );
		}

		SetTextColor( hDC, CR_WHITE );
		SelectObject( hDC, gdiSSVBFont_h24w14 );
		XFORM WTroll;
		char cbuf[4];
		SetGraphicsMode( hDC, GM_ADVANCED );
		for (int i = 0; i <= 33; i += 3)
		{
			// rotate
			WTroll.eM11 = (FLOAT)cos( heading - i * 10 * RAD );
			WTroll.eM12 = (FLOAT)(-sin( heading - i * 10 * RAD ));
			WTroll.eM21 = -WTroll.eM12;
			WTroll.eM22 = WTroll.eM11;
			WTroll.eDx = (FLOAT)(478 - (478 * WTroll.eM11) - (872 * WTroll.eM21));
			WTroll.eDy = (FLOAT)(872 - (872 * WTroll.eM11) + (478 * WTroll.eM21));
			SetWorldTransform( hDC, &WTroll );

			// paint
			if ((i % 9) != 0)// number
			{
				sprintf_s( cbuf, 4, "%d", i );
				TextOut( hDC, 478 - strlen( cbuf ) * 8, 718, cbuf, strlen( cbuf ) );
			}
			else// letter
			{
				SelectObject( hDC, gdiSSVBFont_h32w18 );
				if (i == 0) TextOut( hDC, 470, 708, "N", 1 );
				else if (i == 9) TextOut( hDC, 470, 708, "E", 1 );
				else if (i == 18) TextOut( hDC, 470, 708, "S", 1 );
				else TextOut( hDC, 470, 708, "W", 1 );
				SelectObject( hDC, gdiSSVBFont_h24w14 );
			}

			// de-rotate
			ModifyWorldTransform( hDC, &WTroll, MWT_IDENTITY );
		}

		// rotate to course arrow and CDI heading
		WTroll.eM11 = (FLOAT)cos( -course );
		WTroll.eM12 = (FLOAT)(-sin( -course ));
		WTroll.eM21 = -WTroll.eM12;
		WTroll.eM22 = WTroll.eM11;
		WTroll.eDx = (FLOAT)(478 - (478 * WTroll.eM11) - (872 * WTroll.eM21));
		WTroll.eDy = (FLOAT)(872 - (872 * WTroll.eM11) + (478 * WTroll.eM21));
		SetWorldTransform( hDC, &WTroll );

		if (drawcourse) HSI_CourseArrow( hDC );
		if (drawCDI) HSI_CDI( hDC, CDIflag, CDIscale, CDIdeviation );

		// de-rotate
		ModifyWorldTransform( hDC, &WTroll, MWT_IDENTITY );
		SetGraphicsMode( hDC, GM_COMPATIBLE );

		HSI_Bearing( hDC, primarytype, primarybearing, secondarytype, secondarybearing );

		// draw ov symbol
		static const POINT ov_symbol[6] = {{478,838},{484,874},{492,884},{478,898},{464,884},{472,874}};
		SelectObject( hDC, gdiLightGrayBrush );
		SelectObject( hDC, gdiLightGrayPen );
		Polygon( hDC, ov_symbol, 6 );

		// "delete" bottom area where the menu will be
		SelectObject( hDC, gdiBlackBrush );
		SelectObject( hDC, gdiBlackPen );
		Rectangle( hDC, 234, 912, 722, 1024 );
		return;
	}

	void MDU::HSI_E( oapi::Sketchpad* skp, double heading, bool drawcourse, double course, bool drawCDI, bool CDIflag, double CDIscale, double CDIdeviation, char primarytype, double primarybearing, char secondarytype, double secondarybearing )
	{
		// center (478,872) r = 190
		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpBlackBrush );
		skp->Ellipse( 268, 662, 688, 1082 );// r = 210

		skp->Line( 268, 872, 256, 872 );
		skp->Line( 330, 724, 318, 712 );
		skp->Line( 476, 682, 476, 650 );
		skp->Line( 480, 682, 480, 650 );
		skp->Line( 626, 724, 638, 712 );
		skp->Line( 688, 872, 700, 872 );

		skp->SetPen( skpWhitePen );
		skp->SetBrush( skpDarkGrayBrush );
		skp->Ellipse( 288, 682, 668, 1062 );// r = 190

		skp->SetBrush( skpBlackBrush );
		skp->Ellipse( 354, 748, 602, 996 );// r = 190

		int x1;
		int y1;
		int x2;
		int y2;
		double cosi;
		double sini;
		for (int i = 90; i != 0; i -= 10)// big lines (20px)
		{
			cosi = cos( (i * RAD) + heading );
			sini = sin( (i * RAD) + heading );
			x1 = Round( 190 * cosi );
			y1 = Round( 190 * sini );

			x2 = Round( 170 * cosi );
			y2 = Round( 170 * sini );

			skp->Line( 478 + x1, 872 - y1, 478 + x2, 872 - y2 );

			skp->Line( 478 + y1, 872 + x1, 478 + y2, 872 + x2 );

			skp->Line( 478 - x1, 872 + y1, 478 - x2, 872 + y2 );

			skp->Line( 478 - y1, 872 - x1, 478 - y2, 872 - x2 );
		}

		for (int i = 85; i > 0; i -= 10)// small lines (10px)
		{
			cosi = cos( (i * RAD) + heading );
			sini = sin( (i * RAD) + heading );
			x1 = Round( 190 * cosi );
			y1 = Round( 190 * sini );

			x2 = Round( 180 * cosi );
			y2 = Round( 180 * sini );

			skp->Line( 478 + x1, 872 - y1, 478 + x2, 872 - y2 );

			skp->Line( 478 + y1, 872 + x1, 478 + y2, 872 + x2 );

			skp->Line( 478 - x1, 872 + y1, 478 - x2, 872 + y2 );

			skp->Line( 478 - y1, 872 - x1, 478 - y2, 872 - x2 );
		}

		skp->SetTextColor( CR_WHITE );
		skp->SetFont( skpSSVBFont_h24w14 );
		char cbuf[4];
		oapi::IVECTOR2 cntr;
		cntr.x = 478;
		cntr.y = 872;
		for (int i = 0; i <= 33; i += 3)
		{
			// rotate
			skp->SetWorldTransform2D( 1.0f, (float)(i * 10 * RAD - heading), &cntr );

			// paint
			if ((i % 9) != 0)// number
			{
				sprintf_s( cbuf, 4, "%d", i );
				skp->Text( 478 - strlen( cbuf ) * 8, 718, cbuf, strlen( cbuf ) );
			}
			else// letter
			{
				skp->SetFont( skpSSVBFont_h32w18 );
				if (i == 0) skp->Text( 470, 708, "N", 1 );
				else if (i == 9) skp->Text( 470, 708, "E", 1 );
				else if (i == 18) skp->Text( 470, 708, "S", 1 );
				else skp->Text( 470, 708, "W", 1 );
				skp->SetFont( skpSSVBFont_h24w14 );
			}

			// de-rotate
			skp->SetWorldTransform();
		}

		// rotate to course arrow and CDI heading
		skp->SetWorldTransform2D( 1.0f, static_cast<float>(course), &cntr );

		if (drawcourse) HSI_CourseArrow( skp );
		if (drawCDI) HSI_CDI( skp, CDIflag, CDIscale, CDIdeviation );

		// de-rotate
		skp->SetWorldTransform();

		HSI_Bearing( skp, primarytype, primarybearing, secondarytype, secondarybearing );

		// draw ov symbol
		static const oapi::IVECTOR2 ov_symbol[6] = {{478,838},{484,874},{492,884},{478,898},{464,884},{472,874}};
		skp->SetBrush( skpLightGrayBrush );
		skp->SetPen( skpLightGrayPen );
		skp->Polygon( ov_symbol, 6 );

		// "delete" bottom area where the menu will be
		skp->SetBrush( skpBlackBrush );
		skp->SetPen( skpBlackPen );
		skp->Rectangle( 234, 912, 722, 1024 );
		return;
	}

	void MDU::HSI_CourseArrow( HDC hDC )
	{
		SelectObject( hDC, gdiMagentaBrush );
		SelectObject( hDC, gdiBlackPen );

		// head
		static const POINT arrow[10] = {{478,698},{468,762},{456,770},{454,780},{466,776},{478,790},{490,776},{502,780},{500,770},{488,762}};
		Polygon( hDC, arrow, 10 );
		MoveToEx( hDC, arrow[0].x, arrow[0].y, NULL );
		LineTo( hDC, arrow[5].x, arrow[5].y );

		// tail
		Rectangle( hDC, 472, 952, 484, 1026 );
		return;
	}

	void MDU::HSI_CourseArrow( oapi::Sketchpad* skp )
	{
		skp->SetBrush( skpMagentaBrush );
		skp->SetPen( skpBlackPen );

		// head
		static const oapi::IVECTOR2 arrow[10] = {{478,698},{468,762},{456,770},{454,780},{466,776},{478,790},{490,776},{502,780},{500,770},{488,762}};
		skp->Polygon( arrow, 10 );
		skp->Line( arrow[0].x, arrow[0].y, arrow[5].x, arrow[5].y );

		// tail
		skp->Rectangle( 472, 952, 484, 1026 );
		return;
	}

	void MDU::HSI_CDI( HDC hDC, bool flag, double scale, double deviation )
	{
		int offset = 0;

		// digital scale
		if (scale > 0.0)
		{
			char cbuf[4];
			sprintf_s( cbuf, 4, "%g", scale );
			TextOut( hDC, 368, 880, cbuf, strlen( cbuf ) );
			SetTextAlign( hDC, TA_RIGHT );
			TextOut( hDC, 588, 880, cbuf, strlen( cbuf ) );
			SetTextAlign( hDC, TA_LEFT );

			offset = Round( (deviation / 512) * 126 );
			if (offset > 126) offset = 126;
			else if (offset < -126) offset = -126;
		}

		// dots (42px)
		SelectObject( hDC, gdiWhiteBrush );
		::Ellipse( hDC, 384, 862, 404, 882 );
		::Ellipse( hDC, 426, 862, 446, 882 );
		::Ellipse( hDC, 510, 862, 530, 882 );
		::Ellipse( hDC, 552, 862, 572, 882 );

		// bar (+/-126px)
		SelectObject( hDC, gdiMagentaBrush );
		SelectObject( hDC, gdiBlackPen );
		Rectangle( hDC, 472 + offset, 790, 484 + offset, 952 );

		// off flag
		if (flag)
		{
			SelectObject( hDC, gdiRedPen );
			SelectObject( hDC, gdiRedBrush );
			Rectangle( hDC, 454, 794, 502, 822 );
			SetTextColor( hDC, CR_BLACK );
			TextOut( hDC, 458, 794, "OFF", 3 );
		}
		return;
	}

	void MDU::HSI_CDI( oapi::Sketchpad* skp, bool flag, double scale, double deviation )
	{
		int offset = 0;

		// scale
		if (scale > 0.0)
		{
			char cbuf[4];
			sprintf_s( cbuf, 4, "%g", scale );
			skp->Text( 368, 880, cbuf, strlen( cbuf ) );
			skp->SetTextAlign( oapi::Sketchpad::RIGHT );
			skp->Text( 588, 880, cbuf, strlen( cbuf ) );
			skp->SetTextAlign( oapi::Sketchpad::LEFT );

			offset = Round( (deviation / 512) * 126 );
			if (offset > 126) offset = 126;
			else if (offset < -126) offset = -126;
		}

		// dots (42px)
		skp->SetBrush( skpWhiteBrush );
		skp->Ellipse( 384, 862, 404, 882 );
		skp->Ellipse( 426, 862, 446, 882 );
		skp->Ellipse( 510, 862, 530, 882 );
		skp->Ellipse( 552, 862, 572, 882 );

		// bar (+/-126px)
		skp->SetBrush( skpMagentaBrush );
		skp->SetPen( skpBlackPen );
		skp->Rectangle( 472 + offset, 790, 484 + offset, 952 );

		// off flag
		if (flag)
		{
			skp->SetPen( skpRedPen );
			skp->SetBrush( skpRedBrush );
			skp->Rectangle( 454, 794, 502, 822 );
			skp->SetTextColor( CR_BLACK );
			skp->Text( 458, 794, "OFF", 3 );
		}
		return;
	}

	void MDU::HSI_Bearing( HDC hDC, char primarytype, double primarybearing, char secondarytype, double secondarybearing )
	{
		SetGraphicsMode( hDC, GM_ADVANCED );

		switch (secondarytype)
		{
			case 0:
				break;
			case 'E':
				HSI_Bearing_E( hDC, secondarybearing, false );
				break;
			case 'I':
				HSI_Bearing_I( hDC, secondarybearing );
				break;
			case 'R':
			case 'H':
				HSI_Bearing_RH( hDC, secondarybearing, secondarytype );
				break;
			case 'C':
				HSI_Bearing_C( hDC, secondarybearing );
				break;
		}

		switch (primarytype)
		{
			case 'E':
				HSI_Bearing_E( hDC, primarybearing, true );
				break;
			case 'I':
				HSI_Bearing_I( hDC, primarybearing );
				break;
			case 'R':
			case 'H':
				HSI_Bearing_RH( hDC, primarybearing, primarytype );
				break;
			case 'C':
				HSI_Bearing_C( hDC, primarybearing );
				break;
		}

		SetGraphicsMode( hDC, GM_COMPATIBLE );
		return;
	}

	void MDU::HSI_Bearing( oapi::Sketchpad* skp, char primarytype, double primarybearing, char secondarytype, double secondarybearing )
	{
		switch (secondarytype)
		{
			case 0:// off
				break;
			case 'E':
				HSI_Bearing_E( skp, secondarybearing, false );
				break;
			case 'I':
				HSI_Bearing_I( skp, secondarybearing );
				break;
			case 'R':
			case 'H':
				HSI_Bearing_RH( skp, secondarybearing, secondarytype );
				break;
			case 'C':
				HSI_Bearing_C( skp, secondarybearing );
				break;
		}

		switch (primarytype)
		{
			case 0:// off
				break;
			case 'E':
				HSI_Bearing_E( skp, primarybearing, true );
				break;
			case 'I':
				HSI_Bearing_I( skp, primarybearing );
				break;
			case 'R':
			case 'H':
				HSI_Bearing_RH( skp, primarybearing, primarytype );
				break;
			case 'C':
				HSI_Bearing_C( skp, primarybearing );
				break;
		}
		return;
	}

	void MDU::HSI_Bearing_E( HDC hDC, double bearing, bool pri )
	{
		SelectObject( hDC, gdiRedBrush );
		SelectObject( hDC, gdiBlackPen );
		SetTextColor( hDC, CR_BLACK );

		XFORM WTroll;
		// rotate
		WTroll.eM11 = (FLOAT)cos( bearing );
		WTroll.eM12 = (FLOAT)sin( bearing );
		WTroll.eM21 = -WTroll.eM12;
		WTroll.eM22 = WTroll.eM11;
		WTroll.eDx = (FLOAT)(478 - (478 * WTroll.eM11) - (872 * WTroll.eM21));
		WTroll.eDy = (FLOAT)(872 - (872 * WTroll.eM11) + (478 * WTroll.eM21));
		SetWorldTransform( hDC, &WTroll );

		if (pri)
		{
			// pointer
			static const POINT pointerPRI[6] = {{478,630},{460,670},{472,670},{478,686},{484,670},{496,670}};
			Polygon( hDC, pointerPRI, 6 );
			TextOut( hDC, 472, 644, "E", 1 );

			// tail
			static const POINT tailPRI[6] = {{478,1018},{460,1058},{472,1058},{478,1074},{484,1058},{496,1058}};
			Polygon( hDC, tailPRI, 6 );
			TextOut( hDC, 472, 1032, "E", 1 );
		}
		else
		{
			// pointer
			static const POINT pointerSEC[6] = {{478,642},{460,682},{472,682},{478,698},{484,682},{496,682}};
			Polygon( hDC, pointerSEC, 6 );
			TextOut( hDC, 472, 656, "E", 1 );

			// tail
			static const POINT tailSEC[6] = {{478,996},{460,1036},{472,1036},{478,1052},{484,1036},{496,1036}};
			Polygon( hDC, tailSEC, 6 );
			TextOut( hDC, 472, 1010, "E", 1 );
		}

		// de-rotate
		ModifyWorldTransform( hDC, &WTroll, MWT_IDENTITY );
		return;
	}

	void MDU::HSI_Bearing_E( oapi::Sketchpad* skp, double bearing, bool pri )
	{
		skp->SetBrush( skpRedBrush );
		skp->SetPen( skpBlackPen );
		skp->SetTextColor( CR_BLACK );

		oapi::IVECTOR2 cntr;
		cntr.x = 478;
		cntr.y = 872;
		// rotate
		skp->SetWorldTransform2D( 1.0f, static_cast<float>(bearing), &cntr );

		if (pri)
		{
			// pointer
			static const oapi::IVECTOR2 pointerPRI[6] = {{478,630},{460,670},{472,670},{478,686},{484,670},{496,670}};
			skp->Polygon( pointerPRI, 6 );
			skp->Text( 472, 644, "E", 1 );

			// tail
			static const oapi::IVECTOR2 tailPRI[6] = {{478,1018},{460,1058},{472,1058},{478,1074},{484,1058},{496,1058}};
			skp->Polygon( tailPRI, 6 );
			skp->Text( 472, 1032, "E", 1 );
		}
		else
		{
			// pointer
			static const oapi::IVECTOR2 pointerSEC[6] = {{478,642},{460,682},{472,682},{478,698},{484,682},{496,682}};
			skp->Polygon( pointerSEC, 6 );
			skp->Text( 472, 656, "E", 1 );

			// tail
			static const oapi::IVECTOR2 tailSEC[6] = {{478,996},{460,1036},{472,1036},{478,1052},{484,1036},{496,1036}};
			skp->Polygon( tailSEC, 6 );
			skp->Text( 472, 1010, "E", 1 );
		}

		// de-rotate
		skp->SetWorldTransform();
		return;
	}

	void MDU::HSI_Bearing_I( HDC hDC, double bearing )
	{
		SelectObject( hDC, gdiWhiteBrush );
		SelectObject( hDC, gdiBlackPen );
		SetTextColor( hDC, CR_BLACK );

		// pointer
		XFORM WTroll;
		// rotate
		WTroll.eM11 = (FLOAT)cos( bearing );
		WTroll.eM12 = (FLOAT)sin( bearing );
		WTroll.eM21 = -WTroll.eM12;
		WTroll.eM22 = WTroll.eM11;
		WTroll.eDx = (FLOAT)(478 - (478 * WTroll.eM11) - (872 * WTroll.eM21));
		WTroll.eDy = (FLOAT)(872 - (872 * WTroll.eM11) + (478 * WTroll.eM21));
		SetWorldTransform( hDC, &WTroll );

		static const POINT marker[6] = {{478,642},{460,682},{472,682},{478,698},{484,682},{496,682}};
		Polygon( hDC, marker, 6 );
		TextOut( hDC, 470, 656, "I", 1 );

		// tail
		static const POINT tail[6] = {{478,996},{460,1036},{472,1036},{478,1052},{484,1036},{496,1036}};
		Polygon( hDC, tail, 6 );
		TextOut( hDC, 470, 1010, "I", 1 );

		// de-rotate
		ModifyWorldTransform( hDC, &WTroll, MWT_IDENTITY );
		return;
	}

	void MDU::HSI_Bearing_I( oapi::Sketchpad* skp, double bearing )
	{
		skp->SetBrush( skpWhiteBrush );
		skp->SetPen( skpBlackPen );
		skp->SetTextColor( CR_BLACK );

		// pointer
		oapi::IVECTOR2 cntr;
		cntr.x = 478;
		cntr.y = 872;
		// rotate
		skp->SetWorldTransform2D( 1.0f, static_cast<float>(bearing), &cntr );

		static const oapi::IVECTOR2 marker[6] = {{478,642},{460,682},{472,682},{478,698},{484,682},{496,682}};
		skp->Polygon( marker, 6 );
		skp->Text( 470, 656, "I", 1 );

		// tail
		static const oapi::IVECTOR2 tail[6] = {{478,996},{460,1036},{472,1036},{478,1052},{484,1036},{496,1036}};
		skp->Polygon( tail, 6 );
		skp->Text( 470, 1010, "I", 1 );

		// de-rotate
		skp->SetWorldTransform();
		return;
	}

	void MDU::HSI_Bearing_RH( HDC hDC, double bearing, char chr )
	{
		SelectObject( hDC, gdiLightGreenBrush );
		SelectObject( hDC, gdiBlackPen );
		SetTextColor( hDC, CR_BLACK );

		// pointer
		XFORM WTroll;
		// rotate
		WTroll.eM11 = (FLOAT)cos( bearing );
		WTroll.eM12 = (FLOAT)sin( bearing );
		WTroll.eM21 = -WTroll.eM12;
		WTroll.eM22 = WTroll.eM11;
		WTroll.eDx = (FLOAT)(478 - (478 * WTroll.eM11) - (872 * WTroll.eM21));
		WTroll.eDy = (FLOAT)(872 - (872 * WTroll.eM11) + (478 * WTroll.eM21));
		SetWorldTransform( hDC, &WTroll );

		static const POINT marker[5] = {{478,632},{460,648},{470,672},{486,672},{496,648}};
		Polygon( hDC, marker, 5 );
		char cbuf[2];
		sprintf_s( cbuf, 2, "%c", chr );
		TextOut( hDC, 472, 642, cbuf, 1 );

		// de-rotate
		ModifyWorldTransform( hDC, &WTroll, MWT_IDENTITY );


		// tail
		// rotate
		WTroll.eM11 = (FLOAT)cos( bearing + PI );
		WTroll.eM12 = (FLOAT)sin( bearing + PI );
		WTroll.eM21 = -WTroll.eM12;
		WTroll.eM22 = WTroll.eM11;
		WTroll.eDx = (FLOAT)(478 - (478 * WTroll.eM11) - (872 * WTroll.eM21));
		WTroll.eDy = (FLOAT)(872 - (872 * WTroll.eM11) + (478 * WTroll.eM21));
		SetWorldTransform( hDC, &WTroll );

		Rectangle( hDC, 468, 700, 488, 732 );
		TextOut( hDC, 472, 704, cbuf, 1 );

		// de-rotate
		ModifyWorldTransform( hDC, &WTroll, MWT_IDENTITY );
		return;
	}

	void MDU::HSI_Bearing_RH( oapi::Sketchpad* skp, double bearing, char chr )
	{
		skp->SetBrush( skpLightGreenBrush );
		skp->SetPen( skpBlackPen );
		skp->SetTextColor( CR_BLACK );

		// pointer
		oapi::IVECTOR2 cntr;
		cntr.x = 478;
		cntr.y = 872;
		// rotate
		skp->SetWorldTransform2D( 1.0f, static_cast<float>(bearing), &cntr );

		static const oapi::IVECTOR2 marker[5] = {{478,632},{460,648},{470,672},{486,672},{496,648}};
		skp->Polygon( marker, 5 );
		char cbuf[2];
		sprintf_s( cbuf, 2, "%c", chr );
		skp->Text( 472, 642, cbuf, 1 );

		// de-rotate
		skp->SetWorldTransform();


		// tail
		// rotate
		skp->SetWorldTransform2D( 1.0f, static_cast<float>(bearing + PI), &cntr );

		skp->Rectangle( 468, 700, 488, 732 );
		skp->Text( 472, 704, cbuf, 1 );

		// de-rotate
		skp->SetWorldTransform();
		return;
	}

	void MDU::HSI_Bearing_C( HDC hDC, double bearing )
	{
		SelectObject( hDC, gdiWhiteBrush );
		SelectObject( hDC, gdiBlackPen );
		SetTextColor( hDC, CR_BLACK );

		// pointer
		XFORM WTroll;
		// rotate
		WTroll.eM11 = (FLOAT)cos( bearing );
		WTroll.eM12 = (FLOAT)sin( bearing );
		WTroll.eM21 = -WTroll.eM12;
		WTroll.eM22 = WTroll.eM11;
		WTroll.eDx = (FLOAT)(478 - (478 * WTroll.eM11) - (872 * WTroll.eM21));
		WTroll.eDy = (FLOAT)(872 - (872 * WTroll.eM11) + (478 * WTroll.eM21));
		SetWorldTransform( hDC, &WTroll );

		static const POINT marker[5] = {{478,662},{460,678},{470,702},{486,702},{496,678}};
		Polygon( hDC, marker, 5 );
		TextOut( hDC, 472, 672, "C", 1 );

		// de-rotate
		ModifyWorldTransform( hDC, &WTroll, MWT_IDENTITY );


		// tail
		// rotate
		WTroll.eM11 = (FLOAT)cos( bearing + PI );
		WTroll.eM12 = (FLOAT)sin( bearing + PI );
		WTroll.eM21 = -WTroll.eM12;
		WTroll.eM22 = WTroll.eM11;
		WTroll.eDx = (FLOAT)(478 - (478 * WTroll.eM11) - (872 * WTroll.eM21));
		WTroll.eDy = (FLOAT)(872 - (872 * WTroll.eM11) + (478 * WTroll.eM21));
		SetWorldTransform( hDC, &WTroll );

		Rectangle( hDC, 468, 718, 488, 750 );
		TextOut( hDC, 472, 722, "C", 1 );

		// de-rotate
		ModifyWorldTransform( hDC, &WTroll, MWT_IDENTITY );
		return;
	}

	void MDU::HSI_Bearing_C( oapi::Sketchpad* skp, double bearing )
	{
		skp->SetBrush( skpWhiteBrush );
		skp->SetPen( skpBlackPen );
		skp->SetTextColor( CR_BLACK );

		// pointer
		oapi::IVECTOR2 cntr;
		cntr.x = 478;
		cntr.y = 872;
		// rotate
		skp->SetWorldTransform2D( 1.0f, static_cast<float>(bearing), &cntr );

		static const oapi::IVECTOR2 marker[5] = {{478,662},{460,678},{470,702},{486,702},{496,678}};
		skp->Polygon( marker, 5 );
		skp->Text( 472, 672, "C", 1 );

		// de-rotate
		skp->SetWorldTransform();


		// tail
		// rotate
		skp->SetWorldTransform2D( 1.0f, static_cast<float>(bearing + PI), &cntr );

		skp->Rectangle( 468, 718, 488, 750 );
		skp->Text( 472, 722, "C", 1 );

		// de-rotate
		skp->SetWorldTransform();
		return;
	}

	void MDU::AEPFD_Header( HDC hDC, unsigned short MM, bool rtls, bool tal, bool ato, bool aoa, bool ca, unsigned short adiatt, bool autodappitch, bool autothrotry, bool blankthrotry, bool autosb, double mach )
	{
		// top left (DAP/P)
		if ((MM != 304) && (MM != 305) && (MM != 602) && (MM != 603))
		{
			SetTextColor( hDC, CR_LIGHT_GRAY );
			TextOut( hDC, 80, 6, "DAP:", 4 );
			SetTextColor( hDC, CR_WHITE );
			if (autodappitch) TextOut( hDC, 170, 6, "Auto", 4 );
			else
			{
				SelectObject( hDC, gdiYellowPen );
				SelectObject( hDC, GetStockObject( HOLLOW_BRUSH ) );
				Rectangle( hDC, 32, 2, 264, 34 );
				if ((MM == 102) || (MM == 103) || (MM == 601)) TextOut( hDC, 170, 6, "CSS", 3 );
				else TextOut( hDC, 170, 6, "Inrtl", 5 );
			}
		}
		else
		{
			SetTextColor( hDC, CR_LIGHT_GRAY );
			TextOut( hDC, 44, 6, "Pitch:", 6 );
			SetTextColor( hDC, CR_WHITE );
			if (autodappitch) TextOut( hDC, 170, 6, "Auto", 4 );
			else
			{
				if (mach > 1)
				{
					SelectObject( hDC, gdiYellowPen );
					SelectObject( hDC, GetStockObject( HOLLOW_BRUSH ) );
					Rectangle( hDC, 32, 2, 264, 34 );
				}
				TextOut( hDC, 170, 6, "CSS", 3 );
			}
		}

		// bottom left (Throt/RY)
		if (!blankthrotry)
		{
			if ((MM == 102) || (MM == 103) || (MM == 601))
			{
				SetTextColor( hDC, CR_LIGHT_GRAY );
				TextOut( hDC, 44, 36, "Throt:", 6 );
				SetTextColor( hDC, CR_WHITE );
				if (autothrotry) TextOut( hDC, 170, 36, "Auto", 4 );
				else
				{
					SelectObject( hDC, gdiYellowPen );
					SelectObject( hDC, GetStockObject( HOLLOW_BRUSH ) );
					Rectangle( hDC, 32, 32, 264, 64 );
					TextOut( hDC, 170, 36, "MAN", 3 );
				}
			}
			else
			{
				SetTextColor( hDC, CR_LIGHT_GRAY );
				TextOut( hDC, 80, 36, "R/Y:", 4 );
				SetTextColor( hDC, CR_WHITE );
				if (autothrotry) TextOut( hDC, 170, 36, "Auto", 4 );
				else
				{
					if (mach > 1)
					{
						SelectObject( hDC, gdiYellowPen );
						SelectObject( hDC, GetStockObject( HOLLOW_BRUSH ) );
						Rectangle( hDC, 32, 32, 264, 64 );
					}
					TextOut( hDC, 170, 36, "CSS", 3 );
				}
			}
		}

		// top right (MM)
		SetTextColor( hDC, CR_LIGHT_GRAY );
		TextOut( hDC, 826, 6, "MM:", 3 );
		SetTextColor( hDC, CR_WHITE );
		char cbuf[8];
		if ((MM == 106) || (MM == 301) || (MM == 302) || (MM == 303))
		{
			if (rtls) sprintf_s( cbuf, 8, "%dR", MM );// RTLS
			else if (tal) sprintf_s( cbuf, 8, "%dT", MM );// TAL
			else if (ato) sprintf_s( cbuf, 8, "%dATO", MM );// ATO
			else if (aoa) sprintf_s( cbuf, 8, "%dAOA", MM );// AOA
			else if (ca) sprintf_s( cbuf, 8, "%dCA", MM );// CA
			else sprintf_s( cbuf, 8, "%d", MM );// NOM
		}
		else sprintf_s( cbuf, 8, "%d", MM );
		TextOut( hDC, 898, 6, cbuf, strlen( cbuf ) );

		// bottom right (ATT/SB)
		if ((MM != 304) && (MM != 305) && (MM != 602) && (MM != 603))
		{
			SetTextColor( hDC, CR_LIGHT_GRAY );
			TextOut( hDC, 808, 36, "ATT:", 4 );
			SetTextColor( hDC, CR_WHITE );
			if (adiatt == 2) TextOut( hDC, 898, 36, "LVLH", 4 );
			else if (adiatt == 1) TextOut( hDC, 898, 36, "Inrtl", 5 );
			else TextOut( hDC, 898, 36, "Ref", 3 );
		}
		else
		{
			SetTextColor( hDC, CR_LIGHT_GRAY );
			TextOut( hDC, 826, 36, "SB:", 3 );
			SetTextColor( hDC, CR_WHITE );
			if (autosb) TextOut( hDC, 898, 36, "Auto", 4 );
			else
			{
				SelectObject( hDC, gdiYellowPen );
				SelectObject( hDC, GetStockObject( HOLLOW_BRUSH ) );
				Rectangle( hDC, 800, 32, 1000, 64 );
				TextOut( hDC, 898, 36, "MAN", 3 );
			}
		}
		return;
	}

	void MDU::AEPFD_Header( oapi::Sketchpad* skp, unsigned short MM, bool rtls, bool tal, bool ato, bool aoa, bool ca, unsigned short adiatt, bool autodappitch, bool autothrotry, bool blankthrotry, bool autosb, double mach )
	{
		// top left (DAP/P)
		if ((MM != 304) && (MM != 305) && (MM != 602) && (MM != 603))
		{
			skp->SetTextColor( CR_LIGHT_GRAY );
			skp->Text( 80, 6, "DAP:", 4 );
			skp->SetTextColor( CR_WHITE );
			if (autodappitch) skp->Text( 170, 6, "Auto", 4 );
			else
			{
				skp->SetPen( skpYellowPen );
				skp->SetBrush( NULL );
				skp->Rectangle( 32, 2, 264, 34 );
				if ((MM == 102) || (MM == 103) || (MM == 601)) skp->Text( 170, 6, "CSS", 3 );
				else skp->Text( 170, 6, "Inrtl", 5 );
			}
		}
		else
		{
			skp->SetTextColor( CR_LIGHT_GRAY );
			skp->Text( 44, 6, "Pitch:", 6 );
			skp->SetTextColor( CR_WHITE );
			if (autodappitch) skp->Text( 170, 6, "Auto", 4 );
			else
			{
				if (mach > 1)
				{
					skp->SetPen( skpYellowPen );
					skp->SetBrush( NULL );
					skp->Rectangle( 32, 2, 264, 34 );
				}
				skp->Text( 170, 6, "CSS", 3 );
			}
		}

		// bottom left (Throt/RY)
		if (!blankthrotry)
		{
			if ((MM == 102) || (MM == 103) || (MM == 601))
			{
				skp->SetTextColor( CR_LIGHT_GRAY );
				skp->Text( 44, 36, "Throt:", 6 );
				skp->SetTextColor( CR_WHITE );
				if (autothrotry) skp->Text( 170, 36, "Auto", 4 );
				else
				{
					skp->SetPen( skpYellowPen );
					skp->SetBrush( NULL );
					skp->Rectangle( 32, 32, 264, 64 );
					skp->Text( 170, 36, "MAN", 3 );
				}
			}
			else
			{
				skp->SetTextColor( CR_LIGHT_GRAY );
				skp->Text( 80, 36, "R/Y:", 4 );
				skp->SetTextColor( CR_WHITE );
				if (autothrotry) skp->Text( 170, 36, "Auto", 4 );
				else
				{
					if (mach > 1)
					{
						skp->SetPen( skpYellowPen );
						skp->SetBrush( NULL );
						skp->Rectangle( 32, 32, 264, 64 );
					}
					skp->Text( 170, 36, "CSS", 3 );
				}
			}
		}

		// top right (MM)
		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Text( 826, 6, "MM:", 3 );
		skp->SetTextColor( CR_WHITE );
		char cbuf[8];
		if ((MM == 106) || (MM == 301) || (MM == 302) || (MM == 303))
		{
			if (rtls) sprintf_s( cbuf, 8, "%dR", MM );// RTLS
			else if (tal) sprintf_s( cbuf, 8, "%dT", MM );// TAL
			else if (ato) sprintf_s( cbuf, 8, "%dATO", MM );// ATO
			else if (aoa) sprintf_s( cbuf, 8, "%dAOA", MM );// AOA
			else if (ca) sprintf_s( cbuf, 8, "%dCA", MM );// CA
			else sprintf_s( cbuf, 8, "%d", MM );// NOM
		}
		else sprintf_s( cbuf, 8, "%d", MM );
		skp->Text( 898, 6, cbuf, strlen( cbuf ) );

		// bottom right (ATT/SB)
		if ((MM != 304) && (MM != 305) && (MM != 602) && (MM != 603))
		{
			skp->SetTextColor( CR_LIGHT_GRAY );
			skp->Text( 808, 36, "ATT:", 4 );
			skp->SetTextColor( CR_WHITE );
			if (adiatt == 2) skp->Text( 898, 36, "LVLH", 4 );
			else if (adiatt == 1) skp->Text( 898, 36, "Inrtl", 5 );
			else skp->Text( 898, 36, "Ref", 3 );
		}
		else
		{
			skp->SetTextColor( CR_LIGHT_GRAY );
			skp->Text( 826, 36, "SB:", 3 );
			skp->SetTextColor( CR_WHITE );
			if (autosb) skp->Text( 898, 36, "Auto", 4 );
			else
			{
				skp->SetPen( skpYellowPen );
				skp->SetBrush( NULL );
				skp->Rectangle( 800, 32, 1000, 64 );
				skp->Text( 898, 36, "MAN", 3 );
			}
		}
		return;
	}

	void MDU::AEPFD_BETA( HDC hDC, double beta )
	{
		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 136, 570, 236, 618 );

		SelectObject( hDC, gdiSSVAFont_h22w18 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		TextOut( hDC, 148, 630, "Beta", 4 );

		SelectObject( hDC, gdiSSVBFont_h24w14 );
		SetTextColor( hDC, CR_WHITE );
		if (beta > 0.0) TextOut( hDC, 140, 580, "L", 1 );
		else TextOut( hDC, 140, 580, "R", 1 );

		SelectObject( hDC, gdiSSVBFont_h36w18 );
		SetTextAlign( hDC, TA_RIGHT );
		char cbuf[8];
		sprintf_s( cbuf, 8, "%4.1f", fabs( beta ) );
		TextOut( hDC, 230, 572, cbuf, strlen( cbuf ) );
		SetTextAlign( hDC, TA_LEFT );
		return;
	}

	void MDU::AEPFD_BETA( oapi::Sketchpad* skp, double beta )
	{
		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpBlackBrush );
		skp->Rectangle( 136, 570, 236, 618 );

		skp->SetFont( skpSSVAFont_h22w18 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Text( 148, 630, "Beta", 4 );

		skp->SetFont( skpSSVBFont_h24w14 );
		skp->SetTextColor( CR_WHITE );
		if (beta > 0.0) skp->Text( 140, 580, "L", 1 );
		else skp->Text( 140, 580, "R", 1 );

		skp->SetFont( skpSSVBFont_h36w18 );
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );
		char cbuf[8];
		sprintf_s( cbuf, 8, "%4.1f", fabs( beta ) );
		skp->Text( 230, 572, cbuf, strlen( cbuf ) );
		skp->SetTextAlign( oapi::Sketchpad::LEFT );
		return;
	}

	void MDU::AEPFD_GMETER_STATIC( HDC hDC )
	{
		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 150, 732, 246, 780 );

		Arc( hDC, 62, 712, 214, 864, 138, 712, 192, 842 );

		MoveToEx( hDC, 138, 712, NULL );
		LineTo( hDC, 138, 702 );
		MoveToEx( hDC, 84, 734, NULL );
		LineTo( hDC, 74, 724 );
		MoveToEx( hDC, 62, 788, NULL );
		LineTo( hDC, 52, 788 );
		MoveToEx( hDC, 84, 840, NULL );
		LineTo( hDC, 74, 850 );
		MoveToEx( hDC, 138, 864, NULL );
		LineTo( hDC, 138, 874 );
		MoveToEx( hDC, 190, 840, NULL );
		LineTo( hDC, 200, 850 );

		SetTextAlign( hDC, TA_LEFT );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		SelectObject( hDC, gdiSSVAFont_h22w18 );
		TextOut( hDC, 224, 746, "g", 1 );

		SelectObject( hDC, gdiSSVBFont_h24w14 );
		TextOut( hDC, 54, 692, "3", 1 );
		TextOut( hDC, 24, 774, "2", 1 );
		TextOut( hDC, 54, 848, "1", 1 );
		TextOut( hDC, 132, 878, "0", 1 );
		TextOut( hDC, 200, 854, "-1", 2 );
		return;
	}

	void MDU::AEPFD_GMETER_STATIC( oapi::Sketchpad* skp )
	{
		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpBlackBrush );
		skp->Ellipse( 62, 712, 214, 864 );
		skp->SetPen( skpBlackPen );
		skp->Rectangle( 138, 712, 216, 842 );// cover part of the circle to get an arc because sketchpad doesn't have Arc()

		skp->SetTextAlign( oapi::Sketchpad::LEFT );
		skp->SetPen( skpLightGrayPen );
		skp->Rectangle( 150, 732, 246, 780 );

		skp->Line( 138, 712, 138, 702 );
		skp->Line( 84, 734, 74, 724 );
		skp->Line( 62, 788, 52, 788 );
		skp->Line( 84, 840, 74, 850 );
		skp->Line( 138, 864, 138, 874 );
		skp->Line( 190, 840, 200, 850 );

		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->SetFont( skpSSVAFont_h22w18 );
		skp->Text( 224, 746, "g", 1 );

		skp->SetFont( skpSSVBFont_h24w14 );
		skp->Text( 54, 692, "3", 1 );
		skp->Text( 24, 774, "2", 1 );
		skp->Text( 54, 848, "1", 1 );
		skp->Text( 132, 878, "0", 1 );
		skp->Text( 200, 854, "-1", 2 );
		return;
	}

	void MDU::AEPFD_GMETER( HDC hDC, short type, double accel )
	{
		SelectObject( hDC, gdiSSVAFont_h22w18 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		if (type == 0) TextOut( hDC, 166, 790, "Accel", 5 );
		else if (type == 1) TextOut( hDC, 182, 790, "Nz", 2 );

		SelectObject( hDC, gdiSSVBFont_h36w18 );
		SetTextColor( hDC, CR_WHITE );
		char cbuf[8];
		SetTextAlign( hDC, TA_RIGHT );
		sprintf_s( cbuf, 8, "%.1f", accel );
		TextOut( hDC, 222, 734, cbuf, strlen( cbuf ) );
		SetTextAlign( hDC, TA_LEFT );

		if (accel > 4) accel = 4;
		else if (accel < -1) accel = -1;
		accel = ((accel * 45) - 90) * RAD;

		double cosdtmp = cos( accel );
		double sindtmp = sin( accel );
		// center (138,788)
		POINT arrow[3];
		arrow[0].x = 138 - Round( 66 * cosdtmp );
		arrow[0].y = 788 - Round( 66 * sindtmp );
		arrow[1].x = 138 - Round( (44 * cosdtmp) + (12 * sindtmp) );
		arrow[1].y = 788 - Round( (44 * sindtmp) - (12 * cosdtmp) );
		arrow[2].x = 138 - Round( (44 * cosdtmp) - (12 * sindtmp) );
		arrow[2].y = 788 - Round( (44 * sindtmp) + (12 * cosdtmp) );

		SelectObject( hDC, gdiLightGreenPen );
		SelectObject( hDC, gdiLightGreenBrush );
		Polygon( hDC, arrow, 3 );

		SelectObject( hDC, gdiLightGreenThickPen );
		MoveToEx( hDC, 138, 788, NULL );
		LineTo( hDC, 138 - Round( 62 * cosdtmp ), 788 - Round( 62 * sindtmp ) );
		return;
	}

	void MDU::AEPFD_GMETER( oapi::Sketchpad* skp, short type, double accel )
	{
		skp->SetFont( skpSSVAFont_h22w18 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		if (type == 0) skp->Text( 166, 790, "Accel", 5 );
		else if (type == 1) skp->Text( 182, 790, "Nz", 2 );

		skp->SetFont( skpSSVBFont_h36w18 );
		skp->SetTextColor( CR_WHITE );
		char cbuf[8];
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );
		sprintf_s( cbuf, 8, "%.1f", accel );
		skp->Text( 222, 734, cbuf, strlen( cbuf ) );
		skp->SetTextAlign( oapi::Sketchpad::LEFT );

		if (accel > 4) accel = 4;
		else if (accel < -1) accel = -1;
		accel = ((accel * 45) - 90) * RAD;

		double cosdtmp = cos( accel );
		double sindtmp = sin( accel );
		// center (138,788)
		oapi::IVECTOR2 arrow[3];
		arrow[0].x = 138 - Round( 66 * cosdtmp );
		arrow[0].y = 788 - Round( 66 * sindtmp );
		arrow[1].x = 138 - Round( (44 * cosdtmp) + (12 * sindtmp) );
		arrow[1].y = 788 - Round( (44 * sindtmp) - (12 * cosdtmp) );
		arrow[2].x = 138 - Round( (44 * cosdtmp) - (12 * sindtmp) );
		arrow[2].y = 788 - Round( (44 * sindtmp) + (12 * cosdtmp) );

		skp->SetPen( skpLightGreenPen );
		skp->SetBrush( skpLightGreenBrush );
		skp->Polygon( arrow, 3 );

		skp->SetPen( skpLightGreenThickPen );
		skp->Line( 138, 788, 138 - Round( 62 * cosdtmp ), 788 - Round( 62 * sindtmp ) );
		return;
	}

	void MDU::AEPFD_HACCEL( HDC hDC, double vacc )
	{
		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiWhiteBrush );
		Rectangle( hDC, 934, 600, 958, 904 );

		MoveToEx( hDC, 958, 612, NULL );
		LineTo( hDC, 970, 612 );
		MoveToEx( hDC, 958, 640, NULL );
		LineTo( hDC, 970, 640 );
		MoveToEx( hDC, 958, 668, NULL );
		LineTo( hDC, 970, 668 );
		MoveToEx( hDC, 958, 696, NULL );
		LineTo( hDC, 970, 696 );
		MoveToEx( hDC, 958, 724, NULL );
		LineTo( hDC, 970, 724 );
		MoveToEx( hDC, 958, 752, NULL );
		LineTo( hDC, 970, 752 );
		MoveToEx( hDC, 958, 780, NULL );
		LineTo( hDC, 970, 780 );
		MoveToEx( hDC, 958, 808, NULL );
		LineTo( hDC, 970, 808 );
		MoveToEx( hDC, 958, 836, NULL );
		LineTo( hDC, 970, 836 );
		MoveToEx( hDC, 958, 864, NULL );
		LineTo( hDC, 970, 864 );
		MoveToEx( hDC, 958, 892, NULL );
		LineTo( hDC, 970, 892 );

		SelectObject( hDC, gdiDarkGrayBrush );
		Rectangle( hDC, 934, 752, 958, 904 );

		SetPixel( hDC, 942, 566, CR_LIGHT_GRAY );
		SetPixel( hDC, 946, 566, CR_LIGHT_GRAY );
		SelectObject( hDC, gdiSSVAFont_h22w18 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		TextOut( hDC, 936, 572, "H", 1 );
		SelectObject( hDC, gdiSSVBFont_h24w14 );
		SetTextColor( hDC, CR_WHITE );
		TextOut( hDC, 978, 598, "10", 2 );
		TextOut( hDC, 978, 738, "0", 1 );
		TextOut( hDC, 978, 878, "-10", 3 );

		double dtmp = vacc;
		if (dtmp > 10) dtmp = 10;
		else if (dtmp < -10) dtmp = -10;

		POINT tri[3];// starts at tip moving cw
		tri[0].x = 950;
		tri[0].y = 752 - Round( dtmp * 14 );
		tri[1].x = 922;
		tri[1].y = tri[0].y + 16;
		tri[2].x = 922;
		tri[2].y = tri[0].y - 16;

		SelectObject( hDC, gdiLightGreenPen );
		SelectObject( hDC, gdiLightGreenBrush );
		Polygon( hDC, tri, 3 );
		return;
	}

	void MDU::AEPFD_HACCEL( oapi::Sketchpad* skp, double vacc )
	{
		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpWhiteBrush );
		skp->Rectangle( 934, 600, 958, 904 );

		skp->Line( 958, 612, 970, 612 );
		skp->Line( 958, 640, 970, 640 );
		skp->Line( 958, 668, 970, 668 );
		skp->Line( 958, 696, 970, 696 );
		skp->Line( 958, 724, 970, 724 );
		skp->Line( 958, 752, 970, 752 );
		skp->Line( 958, 780, 970, 780 );
		skp->Line( 958, 808, 970, 808 );
		skp->Line( 958, 836, 970, 836 );
		skp->Line( 958, 864, 970, 864 );
		skp->Line( 958, 892, 970, 892 );

		skp->SetBrush( skpDarkGrayBrush );
		skp->Rectangle( 934, 752, 958, 904 );

		skp->Pixel( 942, 566, CR_LIGHT_GRAY );
		skp->Pixel( 946, 566, CR_LIGHT_GRAY );
		skp->SetFont( skpSSVAFont_h22w18 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Text( 936, 572, "H", 1 );
		skp->SetFont( skpSSVBFont_h24w14 );
		skp->SetTextColor( CR_WHITE );
		skp->Text( 978, 598, "10", 2 );
		skp->Text( 978, 738, "0", 1 );
		skp->Text( 978, 878, "-10", 3 );

		double dtmp = vacc;
		if (dtmp > 10) dtmp = 10;
		else if (dtmp < -10) dtmp = -10;

		oapi::IVECTOR2 tri[3];// starts at tip moving cw
		tri[0].x = 950;
		tri[0].y = 752 - Round( dtmp * 14 );
		tri[1].x = 922;
		tri[1].y = tri[0].y + 16;
		tri[2].x = 922;
		tri[2].y = tri[0].y - 16;

		skp->SetPen( skpLightGreenPen );
		skp->SetBrush( skpLightGreenBrush );
		skp->Polygon( tri, 3 );
		return;
	}

	void MDU::AEPFD_RANGERW( HDC hDC )
	{
		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 734, 768, 816, 802 );
		SelectObject( hDC, gdiSSVAFont_h22w18 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		char cbuf[8];
		GetIDP()->GetSelectedRunway( cbuf );
		TextOut( hDC, 734, 742, cbuf, 5 );
		SelectObject( hDC, gdiSSVBFont_h24w14 );
		SetTextColor( hDC, CR_WHITE );
		SetTextAlign( hDC, TA_RIGHT );
		GetIDP()->GetSelectedRunwayRange( cbuf );
		TextOut( hDC, 810, 770, cbuf, strlen( cbuf ) );
		SetTextAlign( hDC, TA_LEFT );
		return;
	}

	void MDU::AEPFD_RANGERW( oapi::Sketchpad* skp )
	{
		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpBlackBrush );
		skp->Rectangle( 734, 768, 816, 802 );
		skp->SetFont( skpSSVAFont_h22w18 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		char cbuf[8];
		GetIDP()->GetSelectedRunway( cbuf );
		skp->Text( 734, 742, cbuf, 5 );
		skp->SetFont( skpSSVBFont_h24w14 );
		skp->SetTextColor( CR_WHITE );
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );
		GetIDP()->GetSelectedRunwayRange( cbuf );
		skp->Text( 810, 770, cbuf, strlen( cbuf ) );
		skp->SetTextAlign( oapi::Sketchpad::LEFT );
		return;
	}

	void MDU::AEPFD_RANGEHACC( HDC hDC, double range )
	{
		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 734, 850, 816, 884 );
		SelectObject( hDC, gdiSSVAFont_h22w18 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		TextOut( hDC, 734, 824, "HAC-C", 5 );
		SelectObject( hDC, gdiSSVBFont_h24w14 );
		SetTextColor( hDC, CR_WHITE );
		SetTextAlign( hDC, TA_RIGHT );
		char cbuf[8];
		sprintf_s( cbuf, 8, "%5.1f", range );
		TextOut( hDC, 810, 852, cbuf, strlen( cbuf ) );
		SetTextAlign( hDC, TA_LEFT );
		return;
	}

	void MDU::AEPFD_RANGEHACC( oapi::Sketchpad* skp, double range )
	{
		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpBlackBrush );
		skp->Rectangle( 734, 850, 816, 884 );
		skp->SetFont( skpSSVAFont_h22w18 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Text( 734, 824, "HAC-C", 5 );
		skp->SetFont( skpSSVBFont_h24w14 );
		skp->SetTextColor( CR_WHITE );
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );
		char cbuf[8];
		sprintf_s( cbuf, 8, "%5.1f", range );
		skp->Text( 810, 852, cbuf, strlen( cbuf ) );
		skp->SetTextAlign( oapi::Sketchpad::LEFT );
		return;
	}

	void MDU::AEPFD_dAZ_HTA( HDC hDC, bool flash, unsigned short daz )
	{
		char cbuf[8];
		SelectObject( hDC, gdiBlackBrush );
		SelectObject( hDC, gdiSSVAFont_h22w18 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		//if (GetIDP()->GetOnHACState() == false)
		{
			TextOut( hDC, 630, 654, "\x7F""AZ", 3 );
			if (flash)
			{
				// rectangle flashes red for limits
				if (GetFlash() == false) SelectObject( hDC, gdiBlackPen );
				else SelectObject( hDC, gdiRedPen );
			}
			else SelectObject( hDC, gdiLightGrayPen );
		}
		/*else
		{
			TextOut( hDC, 630, 654, "HTA", 3 );
			dtmp = GetIDP()->GetHTA();
			SelectObject( hDC, gdiLightGrayPen );
		}*/

		Rectangle( hDC, 692, 644, 756, 686 );

		SelectObject( hDC, gdiSSVBFont_h24w14 );
		SetTextColor( hDC, CR_WHITE );
		SetTextAlign( hDC, TA_RIGHT );
		sprintf_s( cbuf, 8, "%3d\xB0", daz );
		TextOut( hDC, 754, 650, cbuf, strlen( cbuf ) );
		SetTextAlign( hDC, TA_LEFT );
		return;
	}

	void MDU::AEPFD_dAZ_HTA( oapi::Sketchpad* skp, bool flash, unsigned short daz )
	{
		char cbuf[8];
		skp->SetBrush( skpBlackBrush );
		skp->SetFont( skpSSVAFont_h22w18 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		//if (GetIDP()->GetOnHACState() == false)
		{
			skp->Text( 630, 654, "\x7F""AZ", 3 );
			if (flash)
			{
				// rectangle flashes red for limits
				if (GetFlash() == false) skp->SetPen( skpBlackPen );
				else skp->SetPen( skpRedPen );
			}
			else skp->SetPen( skpLightGrayPen );
		}
		/*else
		{
			skp->Text( 630, 654, "HTA", 3 );
			dtmp = GetIDP()->GetHTA();
			skp->SetPen( skpLightGrayPen );
		}*/

		skp->Rectangle( 692, 644, 756, 686 );

		skp->SetFont( skpSSVBFont_h24w14 );
		skp->SetTextColor( CR_WHITE );
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );
		sprintf_s( cbuf, 8, "%3d\xB0", daz );
		skp->Text( 754, 650, cbuf, strlen( cbuf ) );
		skp->SetTextAlign( oapi::Sketchpad::LEFT );
		return;
	}

	void MDU::AEPFD_dXTRK( HDC hDC )
	{
		SelectObject( hDC, gdiSSVAFont_h22w18 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		char cbuf[8];
		sprintf_s( cbuf, 8, "%c X-Trk", 255 );
		TextOut( hDC, 758, 588, cbuf, 7 );

		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 892, 578, 992, 626 );

		SelectObject( hDC, gdiSSVBFont_h36w18 );
		SetTextColor( hDC, CR_WHITE );
		SetTextAlign( hDC, TA_RIGHT );
		double dtmp = 0;// TODO
		sprintf_s( cbuf, 8, "%4.1f", dtmp );
		TextOut( hDC, 986, 580, cbuf, strlen( cbuf ) );
		SetTextAlign( hDC, TA_LEFT );
		return;
	}

	void MDU::AEPFD_dXTRK( oapi::Sketchpad* skp )
	{
		skp->SetFont( skpSSVAFont_h22w18 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		char cbuf[8];
		sprintf_s( cbuf, 8, "%c X-Trk", 255 );
		skp->Text( 758, 588, cbuf, 7 );

		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpBlackBrush );
		skp->Rectangle( 892, 578, 992, 626 );

		skp->SetFont( skpSSVBFont_h36w18 );
		skp->SetTextColor( CR_WHITE );
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );
		double dtmp = 0;// TODO
		sprintf_s( cbuf, 8, "%4.1f", dtmp );
		skp->Text( 986, 580, cbuf, strlen( cbuf ) );
		skp->SetTextAlign( oapi::Sketchpad::LEFT );
		return;
	}

	void MDU::AEPFD_XTRK( HDC hDC )
	{
		SelectObject( hDC, gdiSSVAFont_h22w18 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		TextOut( hDC, 794, 674, "X-Trk", 5 );

		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 892, 664, 992, 712 );

		SelectObject( hDC, gdiSSVBFont_h36w18 );
		SetTextColor( hDC, CR_WHITE );
		SetTextAlign( hDC, TA_RIGHT );

		double XTrk = GetIDP()->GetCrossTrack();
		XTrk = midval(-99.9, XTrk, 99.9);
		char cbuf[8];
		sprintf_s( cbuf, 8, "%4.1f", XTrk);
		TextOut( hDC, 986, 666, cbuf, strlen( cbuf ) );
		SetTextAlign( hDC, TA_LEFT );
		return;
	}

	void MDU::AEPFD_XTRK( oapi::Sketchpad* skp )
	{
		skp->SetFont( skpSSVAFont_h22w18 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Text( 794, 674, "X-Trk", 5 );

		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpBlackBrush );
		skp->Rectangle( 892, 664, 992, 712 );

		skp->SetFont( skpSSVBFont_h36w18 );
		skp->SetTextColor( CR_WHITE );
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );

		double XTrk = GetIDP()->GetCrossTrack();
		XTrk = midval(-99.9, XTrk, 99.9);
		char cbuf[8];
		sprintf_s( cbuf, 8, "%4.1f", XTrk);
		skp->Text( 986, 666, cbuf, strlen( cbuf ) );
		skp->SetTextAlign( oapi::Sketchpad::LEFT );
		return;
	}

	void MDU::AEPFD_dINC( HDC hDC, double dinc )
	{
		SelectObject( hDC, gdiSSVAFont_h22w18 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		TextOut( hDC, 776, 760, "\x7F Inc", 5 );

		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 874, 750, 992, 798 );

		SelectObject( hDC, gdiSSVBFont_h36w18 );
		SetTextColor( hDC, CR_WHITE );
		SetTextAlign( hDC, TA_RIGHT );
		char cbuf[8];
		sprintf_s( cbuf, 8, "%6.2f", dinc );
		TextOut( hDC, 986, 752, cbuf, strlen( cbuf ) );
		SetTextAlign( hDC, TA_LEFT );
		return;
	}

	void MDU::AEPFD_dINC( oapi::Sketchpad* skp, double dinc )
	{
		skp->SetFont( skpSSVAFont_h22w18 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		char cbuf[8];
		sprintf_s( cbuf, 8, "%c Inc", 255 );
		skp->Text( 776, 760, cbuf, 5 );

		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpBlackBrush );
		skp->Rectangle( 874, 750, 992, 798 );

		skp->SetFont( skpSSVBFont_h36w18 );
		skp->SetTextColor( CR_WHITE );
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );
		sprintf_s( cbuf, 8, "%6.2f", dinc );
		skp->Text( 986, 752, cbuf, strlen( cbuf ) );
		skp->SetTextAlign( oapi::Sketchpad::LEFT );
		return;
	}

	void MDU::AEPFD_TGTINC( HDC hDC )
	{
		SelectObject( hDC, gdiSSVAFont_h22w18 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		TextOut( hDC, 740, 846, "Tgt Inc", 7 );

		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 874, 836, 992, 884 );

		SelectObject( hDC, gdiSSVBFont_h36w18 );
		SetTextColor( hDC, CR_WHITE );
		SetTextAlign( hDC, TA_RIGHT );
		double dtmp = 0;// TODO
		char cbuf[8];
		sprintf_s( cbuf, 8, "%5.2f", dtmp );
		TextOut( hDC, 978, 838, cbuf, strlen( cbuf ) );
		SetTextAlign( hDC, TA_LEFT );
		return;
	}

	void MDU::AEPFD_TGTINC( oapi::Sketchpad* skp )
	{
		skp->SetFont( skpSSVAFont_h22w18 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Text( 740, 846, "Tgt Inc", 7 );

		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpBlackBrush );
		skp->Rectangle( 874, 836, 992, 884 );

		skp->SetFont( skpSSVBFont_h36w18 );
		skp->SetTextColor( CR_WHITE );
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );
		double dtmp = 0;// TODO
		char cbuf[8];
		sprintf_s( cbuf, 8, "%5.2f", dtmp );
		skp->Text( 978, 838, cbuf, strlen( cbuf ) );
		skp->SetTextAlign( oapi::Sketchpad::LEFT );
		return;
	}

	void MDU::AEPFD_GSI( HDC hDC, bool flag, double scale, short deviation )
	{
		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 868, 580, 896, 884 );
		SelectObject( hDC, gdiLightGrayBrush );
		::Ellipse( hDC, 874, 594, 890, 610 );
		::Ellipse( hDC, 874, 658, 890, 674 );
		::Ellipse( hDC, 874, 790, 890, 806 );
		::Ellipse( hDC, 874, 854, 890, 870 );
		MoveToEx( hDC, 868, 732, NULL );
		LineTo( hDC, 896, 732 );

		SelectObject( hDC, gdiSSVBFont_h24w14 );

		if (scale != 0)
		{
			char cbuf[8];
			sprintf_s( cbuf, 8, "%dK", (int)scale / 1000 );
			TextOut( hDC, 868, 552, cbuf, 2 );
			TextOut( hDC, 868, 884, cbuf, 2 );
		}

		if (flag)
		{
			// no tracking -> print GS label
			SelectObject( hDC, gdiRedPen );
			SelectObject( hDC, gdiRedBrush );
			Rectangle( hDC, 854, 714, 910, 748 );
			SetTextColor( hDC, CR_BLACK );
			TextOut( hDC, 868, 718, "GS", 2 );
		}
		else
		{
			POINT tri[3];
			tri[0].x = 882;// starts at tip moving cw
			tri[1].x = 914;
			tri[2].x = 914;

			// display range is 2/3 of input
			if (deviation <= (-512 * 2.0 / 3))
			{
				if (GetFlash() == false) return;
				tri[0].y = 602;
			}
			else if (deviation >= (511 * 2.0 / 3))
			{
				if (GetFlash() == false) return;
				tri[0].y = 862;
			}
			else tri[0].y = 732 + Round( (deviation / (512 * 2.0 / 3) ) * 130 );

			tri[1].y = tri[0].y - 20;
			tri[2].y = tri[0].y + 20;
			SelectObject( hDC, gdiLightGreenPen );
			SelectObject( hDC, gdiLightGreenBrush );
			Polygon( hDC, tri, 3 );
		}
		return;
	}

	void MDU::AEPFD_GSI( oapi::Sketchpad* skp, bool flag, double scale, short deviation )
	{
		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpBlackBrush );
		skp->Rectangle( 868, 580, 896, 884 );
		skp->SetBrush( skpLightGrayBrush );
		skp->Ellipse( 874, 594, 890, 610 );
		skp->Ellipse( 874, 658, 890, 674 );
		skp->Ellipse( 874, 790, 890, 806 );
		skp->Ellipse( 874, 854, 890, 870 );
		skp->Line( 868, 732, 896, 732 );

		skp->SetFont( skpSSVBFont_h24w14 );

		if (scale != 0)
		{
			char cbuf[8];
			sprintf_s( cbuf, 8, "%dK", (int)scale / 1000 );
			skp->Text( 868, 552, cbuf, 2 );
			skp->Text( 868, 884, cbuf, 2 );
		}

		if (flag)
		{
			// no tracking -> print GS label
			skp->SetPen( skpRedPen );
			skp->SetBrush( skpRedBrush );
			skp->Rectangle( 854, 714, 910, 748 );
			skp->SetTextColor( CR_BLACK );
			skp->Text( 868, 718, "GS", 2 );
		}
		else
		{
			oapi::IVECTOR2 tri[3];
			tri[0].x = 882;// starts at tip moving cw
			tri[1].x = 914;
			tri[2].x = 914;

			// display range is 2/3 of input
			if (deviation <= (-512 * 2.0 / 3))
			{
				if (GetFlash() == false) return;
				tri[0].y = 602;
			}
			else if (deviation >= (511 * 2.0 / 3))
			{
				if (GetFlash() == false) return;
				tri[0].y = 862;
			}
			else tri[0].y = 732 + Round( (deviation / (512 * 2.0 / 3) ) * 130 );

			tri[1].y = tri[0].y - 20;
			tri[2].y = tri[0].y + 20;
			skp->SetPen( skpLightGreenPen );
			skp->SetBrush( skpLightGreenBrush );
			skp->Polygon( tri, 3 );
		}
		return;
	}
}

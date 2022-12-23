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
2022/12/17   GLS
********************************************/
#include "MDU.h"
#include "../Atlantis.h"
#include "../dps/IDP.h"
#include "../mission/Mission.h"
#include <MathSSV.h>


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
		int MM = STS()->GetGPCMajorMode();
		double vr = STS()->GetGroundspeed() * MPS2FPS * 0.001;
		VECTOR3 v3vi;
		STS()->GetRelativeVel( STS()->GetSurfaceRef(), v3vi );
		double vi = length( v3vi ) * MPS2FPS * 0.001;
		double Altitude_ft = STS()->GetAltitude() * MPS2FPS;
		int adiatt = 1;//GetIDP()->GetADIAttitude();
		int adierr = GetIDP()->GetADIError();
		int adirate = GetIDP()->GetADIRate();
		VECTOR3 vel;
		STS()->GetGroundspeedVector( FRAME_HORIZON, vel );
		vel *= MPS2FPS;
		VECTOR3 av;// x = pitch, y = yaw, z = roll
		STS()->GetAngularVel( av );
		av *= DEG;
		av.z = -av.z;
		av.x = -av.x;
		VECTOR3 atterr;
		VECTOR3 rates;
		double attRoll = -STS()->GetBank() * DEG;
		if (attRoll <= 0) attRoll += 360;
		double attPitch = STS()->GetPitch() * DEG;
		if (attPitch <= 0) attPitch += 360;
		double attYaw = 0;//STS()->GetSlipAngle() * DEG;
		//if (attYaw <= 0) attYaw += 360;
		double hsiheading;

		SelectObject( hDC, gdiSSVAFont_h11w9 );

		switch (MM)
		{
			case 101:
				AEPFD_Header_AscentDAP( hDC, 101, adiatt );
				Tapes_Invalid( hDC );
				ADI_STATIC( hDC );
				ADI( hDC, attPitch, attRoll, attYaw );
				ADI_RATE_A( hDC, av.x, av.z, av.y, adirate );
				ADI_ERROR_A( hDC, 0, 0, 0, adierr );
				HSI_E( hDC, 0.0, true, 0, true, true, 0.0, 0.0, GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				break;
			case 102:
				AEPFD_Header_AscentDAP( hDC, 102, adiatt );
				Tape_MV_KEAS( hDC, 'R', vr );
				Tape_Alpha( hDC, 0 );
				Tape_H_Hdot( hDC, Altitude_ft, vel.y );
				if ((Altitude_ft <= 200000) && (STS()->GetMET() <= 150)) AEPFD_BETA( hDC );
				ADI_STATIC( hDC );
				ADI( hDC, attPitch, attRoll, attYaw );
				ADI_RATE_A( hDC, av.x, av.z, av.y, adirate );
				atterr = GetIDP()->GetAttitudeErrors_AscentDAP();
				ADI_ERROR_A( hDC, atterr.x, atterr.z, atterr.y, adierr );
				AEPFD_GMETER_STATIC( hDC );
				AEPFD_GMETER_ACCEL( hDC );
				hsiheading = STS()->GetYaw() - GetIDP()->GetTargetHeading();
				HSI_A( hDC, hsiheading, STS()->GetBank(), true, hsiheading * DEG, false, true, GetIDP()->GetCourseDeviationScale(), GetIDP()->GetCourseDeviation(), GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				AEPFD_XTRK( hDC );// TODO only NOM, TAL and ATO
				AEPFD_dINC( hDC );
				break;
			case 103:
				AEPFD_Header_AscentDAP( hDC, 103, adiatt );
				Tape_MV_KEAS( hDC, 'I', vi );
				Tape_Alpha( hDC, 0 );
				Tape_H_Hdot( hDC, Altitude_ft, vel.y );
				if ((Altitude_ft <= 200000) && (STS()->GetMET() <= 150)) AEPFD_BETA( hDC );
				ADI_STATIC( hDC );
				ADI( hDC, attPitch, attRoll, attYaw );
				ADI_RATE_A( hDC, av.x, av.z, av.y, adirate );
				atterr = GetIDP()->GetAttitudeErrors_AscentDAP();
				ADI_ERROR_A( hDC, atterr.x, atterr.z, atterr.y, adierr );
				AEPFD_GMETER_STATIC( hDC );
				AEPFD_GMETER_ACCEL( hDC );
				hsiheading = STS()->GetYaw() - GetIDP()->GetTargetHeading();
				HSI_A( hDC, hsiheading, STS()->GetBank(), true, hsiheading * DEG, false, true, GetIDP()->GetCourseDeviationScale(), GetIDP()->GetCourseDeviation(), GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				if (0)// TODO TAL
				{
					AEPFD_dXTRK( hDC );
					AEPFD_RANGERW( hDC );// fix colision between this and dINC
				}
				AEPFD_XTRK( hDC );// TODO only NOM, TAL and ATO
				if (0) AEPFD_RANGERW( hDC );// TODO ECAL/BDA
				AEPFD_dINC( hDC );
				if (0) AEPFD_TGTINC( hDC );// TODO ATO
				break;
			case 104:
				AEPFD_Header_TransDAP( hDC, 104, adiatt );
				Tape_MV_KEAS( hDC, 'I', vi );
				Tape_H_Hdot( hDC, Altitude_ft, vel.y );
				ADI_STATIC( hDC );
				ADI( hDC, attPitch, attRoll, attYaw );
				ADI_RATE_A( hDC, av.x, av.z, av.y, adirate );
				ADI_ERROR_A( hDC, 0, 0, 0, adierr );// TODO
				HSI_E( hDC, STS()->GetYaw(), true, 0.0, false, true, GetIDP()->GetCourseDeviationScale(), GetIDP()->GetCourseDeviation(), GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				AEPFD_XTRK( hDC );// TODO only NOM, TAL and ATO
				AEPFD_dINC( hDC );
				break;
			case 105:
				AEPFD_Header_TransDAP( hDC, 105, adiatt );
				ADI_STATIC( hDC );
				ADI( hDC, attPitch, attRoll, attYaw );
				ADI_RATE_A( hDC, av.x, av.z, av.y, adirate );
				ADI_ERROR_A( hDC, 0, 0, 0, adierr );// TODO
				break;
			case 106:
				AEPFD_Header_TransDAP( hDC, 106, adiatt );
				ADI_STATIC( hDC );
				ADI( hDC, attPitch, attRoll, attYaw );
				ADI_RATE_A( hDC, av.x, av.z, av.y, adirate );
				ADI_ERROR_A( hDC, 0, 0, 0, adierr );// TODO
				break;
			case 201:
				ADI_STATIC( hDC );
				ADI( hDC, attPitch, attRoll, attYaw );
				break;
			case 202:
				ADI_STATIC( hDC );
				ADI( hDC, attPitch, attRoll, attYaw );
				break;
			case 301:
				AEPFD_Header_TransDAP( hDC, 301, adiatt );
				ADI_STATIC( hDC );
				ADI( hDC, attPitch, attRoll, attYaw );
				ADI_RATE_A( hDC, av.x, av.z, av.y, adirate );
				atterr = GetIDP()->GetAttitudeErrors_AerojetDAP();
				ADI_ERROR_A( hDC, atterr.x, atterr.z, atterr.y, adierr );
				break;
			case 302:
				AEPFD_Header_TransDAP( hDC, 302, adiatt );
				ADI_STATIC( hDC );
				ADI( hDC, attPitch, attRoll, attYaw );
				ADI_RATE_A( hDC, av.x, av.z, av.y, adirate );
				atterr = GetIDP()->GetAttitudeErrors_AerojetDAP();
				ADI_ERROR_A( hDC, atterr.x, atterr.z, atterr.y, adierr );
				break;
			case 303:
				AEPFD_Header_TransDAP( hDC, 303, adiatt );
				ADI_STATIC( hDC );
				ADI( hDC, attPitch, attRoll, attYaw );
				ADI_RATE_A( hDC, av.x, av.z, av.y, adirate );
				atterr = GetIDP()->GetAttitudeErrors_AerojetDAP();
				ADI_ERROR_A( hDC, atterr.x, atterr.z, atterr.y, adierr );
				break;
			case 304:
				AEPFD_Header_AerojetDAP( hDC, 304, GetIDP()->GetVrel() * 0.001 );
				Tape_MV_KEAS( hDC, 'R', GetIDP()->GetVrel() * 0.001 );
				Tape_Alpha( hDC, GetIDP()->GetVrel() * 0.001 );
				Tape_H_Hdot( hDC, GetIDP()->GetAltitude(), GetIDP()->GetAltitudeRate() );
				ADI_STATIC( hDC );
				ADI( hDC, attPitch, attRoll, attYaw );
				rates = GetIDP()->GetRates();
				ADI_RATE_A( hDC, rates.x, rates.z, rates.y, adirate );
				atterr = GetIDP()->GetAttitudeErrors_AerojetDAP();
				ADI_ERROR_B( hDC, atterr.x, atterr.z, atterr.y, adierr );
				AEPFD_GMETER_STATIC( hDC );
				AEPFD_GMETER_NZ( hDC );
				HSI_E( hDC, atan2( vel.x, vel.z ), true, GetIDP()->GetSelectedRunwayHeading(), false, true, GetIDP()->GetCourseDeviationScale(), GetIDP()->GetCourseDeviation(), GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				AEPFD_dAZ_HTA( hDC );
				AEPFD_RANGERW( hDC );
				AEPFD_HACCEL( hDC );
				break;
			case 305:
				AEPFD_Header_AerojetDAP( hDC, 305, GetIDP()->GetVrel() * 0.001 );
				if (GetIDP()->GetVrel() >= 900.0) Tape_MV_KEAS( hDC, 'R', GetIDP()->GetVrel() * 0.001 );
				else Tape_KEAS_MVR( hDC, GetIDP()->GetVrel() * 0.001 );
				Tape_Alpha( hDC, GetIDP()->GetVrel() * 0.001 );
				Tape_H_Hdot( hDC, GetIDP()->GetAltitude(), GetIDP()->GetAltitudeRate() );
				ADI_STATIC( hDC );
				ADI( hDC, attPitch, attRoll, attYaw );
				rates = GetIDP()->GetRates();
				ADI_RATE_B( hDC, rates.x, rates.z, rates.y, adirate, GetIDP()->GetAltitude() );
				atterr = GetIDP()->GetAttitudeErrors_AerojetDAP();
				if (GetIDP()->GetWOW() == false) ADI_ERROR_C( hDC, GetIDP()->GetNZError(), atterr.z, atterr.y, adierr );
				else ADI_ERROR_D( hDC, atterr.x, atterr.z, atterr.y, adierr );
				AEPFD_GMETER_STATIC( hDC );
				AEPFD_GMETER_NZ( hDC );
				HSI_E( hDC, STS()->GetYaw(), true, GetIDP()->GetSelectedRunwayHeading(), false, true, GetIDP()->GetCourseDeviationScale(), GetIDP()->GetCourseDeviation(), GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				if (GetIDP()->GetPrefinalState() == false)
				{
					AEPFD_dAZ_HTA( hDC );
					AEPFD_RANGEHACC( hDC );
				}
				AEPFD_RANGERW( hDC );
				AEPFD_GSI( hDC, GetIDP()->GetGSFlag(), GetIDP()->GetGlideSlopeDeviationScale(), GetIDP()->GetGlideSlopeDeviation() );
				break;
			case 601:
				AEPFD_Header_AscentDAP( hDC, 601, adiatt );
				if (0) Tape_MV_KEAS( hDC, 'R', vr );// TODO PPA
				else Tape_MV_KEAS( hDC, 'I', vi );
				Tape_Alpha( hDC, 0 );
				Tape_H_Hdot( hDC, Altitude_ft, vel.y );
				AEPFD_BETA( hDC );
				ADI_STATIC( hDC );
				ADI( hDC, attPitch, attRoll, attYaw );
				ADI_RATE_A( hDC, av.x, av.z, av.y, adirate );
				atterr = GetIDP()->GetAttitudeErrors_AscentDAP();
				ADI_ERROR_A( hDC, atterr.x, atterr.z, atterr.y, adierr );
				AEPFD_GMETER_STATIC( hDC );
				AEPFD_GMETER_ACCEL( hDC );
				HSI_E( hDC, STS()->GetYaw(), false, 0.0, false, false, 0.0, 0.0, GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				AEPFD_dAZ_HTA( hDC );
				AEPFD_RANGERW( hDC );
				break;
			case 602:
				AEPFD_Header_AerojetDAP( hDC, 602, GetIDP()->GetVrel() * 0.001 );
				Tape_MV_KEAS( hDC, 'R', GetIDP()->GetVrel() * 0.001 );
				Tape_Alpha( hDC, GetIDP()->GetVrel() * 0.001 );
				Tape_H_Hdot( hDC, GetIDP()->GetAltitude(), GetIDP()->GetAltitudeRate() );
				ADI_STATIC( hDC );
				ADI( hDC, attPitch, attRoll, attYaw );
				rates = GetIDP()->GetRates();
				ADI_RATE_A( hDC, rates.x, rates.z, rates.y, adirate );
				atterr = GetIDP()->GetAttitudeErrors_AerojetDAP();
				if (0) ADI_ERROR_C( hDC, GetIDP()->GetNZError(), atterr.z, atterr.y, adierr );// TODO Nz hold
				else ADI_ERROR_B( hDC, atterr.x, atterr.z, atterr.y, adierr );
				AEPFD_GMETER_STATIC( hDC );
				AEPFD_GMETER_NZ( hDC );
				HSI_E( hDC, atan2( vel.x, vel.z ), true, GetIDP()->GetSelectedRunwayHeading(), false, true, GetIDP()->GetCourseDeviationScale(), GetIDP()->GetCourseDeviation(), GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				AEPFD_dAZ_HTA( hDC );
				AEPFD_RANGERW( hDC );
				AEPFD_HACCEL( hDC );
				break;
			case 603:
				AEPFD_Header_AerojetDAP( hDC, 603, GetIDP()->GetVrel() * 0.001 );
				if (GetIDP()->GetVrel() >= 900.0) Tape_MV_KEAS( hDC, 'R', GetIDP()->GetVrel() * 0.001 );
				else Tape_KEAS_MVR( hDC, GetIDP()->GetVrel() * 0.001 );
				Tape_Alpha( hDC, GetIDP()->GetVrel() * 0.001 );
				Tape_H_Hdot( hDC, GetIDP()->GetAltitude(), GetIDP()->GetAltitudeRate() );
				ADI_STATIC( hDC );
				ADI( hDC, attPitch, attRoll, attYaw );
				rates = GetIDP()->GetRates();
				ADI_RATE_B( hDC, rates.x, rates.z, rates.y, adirate, GetIDP()->GetAltitude() );
				atterr = GetIDP()->GetAttitudeErrors_AerojetDAP();
				if (GetIDP()->GetWOW() == false) ADI_ERROR_C( hDC, GetIDP()->GetNZError(), atterr.z, atterr.y, adierr );
				else ADI_ERROR_D( hDC, atterr.x, atterr.z, atterr.y, adierr );
				AEPFD_GMETER_STATIC( hDC );
				AEPFD_GMETER_NZ( hDC );
				HSI_E( hDC, STS()->GetYaw(), true, GetIDP()->GetSelectedRunwayHeading(), false, true, GetIDP()->GetCourseDeviationScale(), GetIDP()->GetCourseDeviation(), GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				if (GetIDP()->GetPrefinalState() == false)
				{
					AEPFD_dAZ_HTA( hDC );
					AEPFD_RANGEHACC( hDC );
				}
				AEPFD_RANGERW( hDC );
				AEPFD_GSI( hDC, GetIDP()->GetGSFlag(), GetIDP()->GetGlideSlopeDeviationScale(), GetIDP()->GetGlideSlopeDeviation() );
				break;
			case 801:
				ADI_STATIC( hDC );
				ADI( hDC, attPitch, attRoll, attYaw );
				break;
			case 901:
				Tapes_Invalid( hDC );
				ADI_STATIC( hDC );// TODO no rate and error scales
				ADI( hDC, attPitch, attRoll, attYaw );
				AEPFD_GMETER_STATIC( hDC );
				HSI_E( hDC, 0.0, true, 0.0, false, true, 0.0, 0.0, GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				break;
			default:
				break;
		}
		return;
	}

	void MDU::AEPFD( oapi::Sketchpad2* skp )
	{
		int MM = STS()->GetGPCMajorMode();
		double vr = STS()->GetGroundspeed() * MPS2FPS * 0.001;
		VECTOR3 v3vi;
		STS()->GetRelativeVel( STS()->GetSurfaceRef(), v3vi );
		double vi = length( v3vi ) * MPS2FPS * 0.001;
		double Altitude_ft = STS()->GetAltitude() * MPS2FPS;
		int adiatt = 1;//GetIDP()->GetADIAttitude();
		int adierr = GetIDP()->GetADIError();
		int adirate = GetIDP()->GetADIRate();
		VECTOR3 vel;
		STS()->GetGroundspeedVector( FRAME_HORIZON, vel );
		vel *= MPS2FPS;
		VECTOR3 av;// x = pitch, y = yaw, z = roll
		STS()->GetAngularVel( av );
		av *= DEG;
		av.z = -av.z;
		av.x = -av.x;
		VECTOR3 atterr;
		VECTOR3 rates;
		double attRoll = -STS()->GetBank() * DEG;
		if (attRoll <= 0) attRoll += 360;
		double attPitch = STS()->GetPitch() * DEG;
		if (attPitch <= 0) attPitch += 360;
		double attYaw = 0;//STS()->GetSlipAngle() * DEG;
		//if (attYaw <= 0) attYaw += 360;
		double hsiheading;

		skp->SetFont( skpSSVAFont_h11w9 );

		switch (MM)
		{
			case 101:
				AEPFD_Header_AscentDAP( skp, 101, adiatt );
				Tapes_Invalid( skp );
				ADI_STATIC( skp );
				ADI( skp, attPitch, attRoll, attYaw );
				ADI_RATE_A( skp, av.x, av.z, av.y, adirate );
				ADI_ERROR_A( skp, 0, 0, 0, adierr );
				HSI_E( skp, 0.0, true, 0, true, true, 0.0, 0.0, GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				break;
			case 102:
				AEPFD_Header_AscentDAP( skp, 102, adiatt );
				Tape_MV_KEAS( skp, 'R', vr );
				Tape_Alpha( skp, 0 );
				Tape_H_Hdot( skp, Altitude_ft, vel.y );
				if ((Altitude_ft <= 200000) && (STS()->GetMET() <= 150)) AEPFD_BETA( skp );
				ADI_STATIC( skp );
				ADI( skp, attPitch, attRoll, attYaw );
				ADI_RATE_A( skp, av.x, av.z, av.y, adirate );
				atterr = GetIDP()->GetAttitudeErrors_AscentDAP();
				ADI_ERROR_A( skp, atterr.x, atterr.z, atterr.y, adierr );
				AEPFD_GMETER_STATIC( skp );
				AEPFD_GMETER_ACCEL( skp );
				hsiheading = STS()->GetYaw() - GetIDP()->GetTargetHeading();
				HSI_A( skp, hsiheading, STS()->GetBank(), true, hsiheading * DEG, false, true, GetIDP()->GetCourseDeviationScale(), GetIDP()->GetCourseDeviation(), GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				AEPFD_XTRK( skp );// TODO only NOM, TAL and ATO
				AEPFD_dINC( skp );
				break;
			case 103:
				AEPFD_Header_AscentDAP( skp, 103, adiatt );
				Tape_MV_KEAS( skp, 'I', vi );
				Tape_Alpha( skp, 0 );
				Tape_H_Hdot( skp, Altitude_ft, vel.y );
				if ((Altitude_ft <= 200000) && (STS()->GetMET() <= 150)) AEPFD_BETA( skp );
				ADI_STATIC( skp );
				ADI( skp, attPitch, attRoll, attYaw );
				ADI_RATE_A( skp, av.x, av.z, av.y, adirate );
				atterr = GetIDP()->GetAttitudeErrors_AscentDAP();
				ADI_ERROR_A( skp, atterr.x, atterr.z, atterr.y, adierr );
				AEPFD_GMETER_STATIC( skp );
				AEPFD_GMETER_ACCEL( skp );
				hsiheading = STS()->GetYaw() - GetIDP()->GetTargetHeading();
				HSI_A( skp, hsiheading, STS()->GetBank(), true, hsiheading * DEG, false, true, GetIDP()->GetCourseDeviationScale(), GetIDP()->GetCourseDeviation(), GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				if (0)// TODO TAL
				{
					AEPFD_dXTRK( skp );
					AEPFD_RANGERW( skp );// fix colision between this and dINC
				}
				AEPFD_XTRK( skp );// TODO only NOM, TAL and ATO
				if (0) AEPFD_RANGERW( skp );// TODO ECAL/BDA
				AEPFD_dINC( skp );
				if (0) AEPFD_TGTINC( skp );// TODO ATO
				break;
			case 104:
				AEPFD_Header_TransDAP( skp, 104, adiatt );
				Tape_MV_KEAS( skp, 'I', vi );
				Tape_H_Hdot( skp, Altitude_ft, vel.y );
				ADI_STATIC( skp );
				ADI( skp, attPitch, attRoll, attYaw );
				ADI_RATE_A( skp, av.x, av.z, av.y, adirate );
				ADI_ERROR_A( skp, 0, 0, 0, adierr );// TODO
				HSI_E( skp, STS()->GetYaw(), true, 0.0, false, true, GetIDP()->GetCourseDeviationScale(), GetIDP()->GetCourseDeviation(), GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				AEPFD_XTRK( skp );// TODO only NOM, TAL and ATO
				AEPFD_dINC( skp );
				break;
			case 105:
				AEPFD_Header_TransDAP( skp, 105, adiatt );
				ADI_STATIC( skp );
				ADI( skp, attPitch, attRoll, attYaw );
				ADI_RATE_A( skp, av.x, av.z, av.y, adirate );
				ADI_ERROR_A( skp, 0, 0, 0, adierr );// TODO
				break;
			case 106:
				AEPFD_Header_TransDAP( skp, 106, adiatt );
				ADI_STATIC( skp );
				ADI( skp, attPitch, attRoll, attYaw );
				ADI_RATE_A( skp, av.x, av.z, av.y, adirate );
				ADI_ERROR_A( skp, 0, 0, 0, adierr );// TODO
				break;
			case 201:
				ADI_STATIC( skp );
				ADI( skp, attPitch, attRoll, attYaw );
				break;
			case 202:
				ADI_STATIC( skp );
				ADI( skp, attPitch, attRoll, attYaw );
				break;
			case 301:
				AEPFD_Header_TransDAP( skp, 301, adiatt );
				ADI_STATIC( skp );
				ADI( skp, attPitch, attRoll, attYaw );
				ADI_RATE_A( skp, av.x, av.z, av.y, adirate );
				atterr = GetIDP()->GetAttitudeErrors_AerojetDAP();
				ADI_ERROR_A( skp, atterr.x, atterr.z, atterr.y, adierr );
				break;
			case 302:
				AEPFD_Header_TransDAP( skp, 302, adiatt );
				ADI_STATIC( skp );
				ADI( skp, attPitch, attRoll, attYaw );
				ADI_RATE_A( skp, av.x, av.z, av.y, adirate );
				atterr = GetIDP()->GetAttitudeErrors_AerojetDAP();
				ADI_ERROR_A( skp, atterr.x, atterr.z, atterr.y, adierr );
				break;
			case 303:
				AEPFD_Header_TransDAP( skp, 303, adiatt );
				ADI_STATIC( skp );
				ADI( skp, attPitch, attRoll, attYaw );
				ADI_RATE_A( skp, av.x, av.z, av.y, adirate );
				atterr = GetIDP()->GetAttitudeErrors_AerojetDAP();
				ADI_ERROR_A( skp, atterr.x, atterr.z, atterr.y, adierr );
				break;
			case 304:
				AEPFD_Header_AerojetDAP( skp, 304, vr );
				Tape_MV_KEAS( skp, 'R', vr );
				Tape_Alpha( skp, vr );
				Tape_H_Hdot( skp, GetIDP()->GetAltitude(), GetIDP()->GetAltitudeRate() );
				ADI_STATIC( skp );
				ADI( skp, attPitch, attRoll, attYaw );
				rates = GetIDP()->GetRates();
				ADI_RATE_A( skp, rates.x, rates.z, rates.y, adirate );
				atterr = GetIDP()->GetAttitudeErrors_AerojetDAP();
				ADI_ERROR_B( skp, atterr.x, atterr.z, atterr.y, adierr );
				AEPFD_GMETER_STATIC( skp );
				AEPFD_GMETER_NZ( skp );
				HSI_E( skp, atan2( vel.x, vel.z ), true, GetIDP()->GetSelectedRunwayHeading(), false, true, GetIDP()->GetCourseDeviationScale(), GetIDP()->GetCourseDeviation(), GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				AEPFD_dAZ_HTA( skp );
				AEPFD_RANGERW( skp );
				AEPFD_HACCEL( skp );
				break;
			case 305:
				AEPFD_Header_AerojetDAP( skp, 305, vr );
				if (vr >= 0.9) Tape_MV_KEAS( skp, 'R', vr );
				else Tape_KEAS_MVR( skp, vr );
				Tape_Alpha( skp, vr );
				Tape_H_Hdot( skp, GetIDP()->GetAltitude(), GetIDP()->GetAltitudeRate() );
				ADI_STATIC( skp );
				ADI( skp, attPitch, attRoll, attYaw );
				rates = GetIDP()->GetRates();
				ADI_RATE_B( skp, rates.x, rates.z, rates.y, adirate, GetIDP()->GetAltitude() );
				atterr = GetIDP()->GetAttitudeErrors_AerojetDAP();
				if (GetIDP()->GetWOW() == false) ADI_ERROR_C( skp, GetIDP()->GetNZError(), atterr.z, atterr.y, adierr );
				else ADI_ERROR_D( skp, atterr.x, atterr.z, atterr.y, adierr );
				AEPFD_GMETER_STATIC( skp );
				AEPFD_GMETER_NZ( skp );
				HSI_E( skp, STS()->GetYaw(), true, GetIDP()->GetSelectedRunwayHeading(), false, true, GetIDP()->GetCourseDeviationScale(), GetIDP()->GetCourseDeviation(), GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				if (GetIDP()->GetPrefinalState() == false)
				{
					AEPFD_dAZ_HTA( skp );
					AEPFD_RANGEHACC( skp );
				}
				AEPFD_RANGERW( skp );
				AEPFD_GSI( skp, GetIDP()->GetGSFlag(), GetIDP()->GetGlideSlopeDeviationScale(), GetIDP()->GetGlideSlopeDeviation() );
				break;
			case 601:
				AEPFD_Header_AscentDAP( skp, 601, adiatt );
				if (0) Tape_MV_KEAS( skp, 'R', vr );// TODO PPA
				else Tape_MV_KEAS( skp, 'I', vi );
				Tape_Alpha( skp, 0 );
				Tape_H_Hdot( skp, Altitude_ft, vel.y );
				AEPFD_BETA( skp );
				ADI_STATIC( skp );
				ADI( skp, attPitch, attRoll, attYaw );
				ADI_RATE_A( skp, av.x, av.z, av.y, adirate );
				atterr = GetIDP()->GetAttitudeErrors_AscentDAP();
				ADI_ERROR_A( skp, atterr.x, atterr.z, atterr.y, adierr );
				AEPFD_GMETER_STATIC( skp );
				AEPFD_GMETER_ACCEL( skp );
				HSI_E( skp, STS()->GetYaw(), false, 0.0, false, false, 0.0, 0.0, GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				AEPFD_dAZ_HTA( skp );
				AEPFD_RANGERW( skp );
				break;
			case 602:
				AEPFD_Header_AerojetDAP( skp, 602, vr );
				Tape_MV_KEAS( skp, 'R', vr );
				Tape_Alpha( skp, vr );
				Tape_H_Hdot( skp, GetIDP()->GetAltitude(), GetIDP()->GetAltitudeRate() );
				ADI_STATIC( skp );
				ADI( skp, attPitch, attRoll, attYaw );
				rates = GetIDP()->GetRates();
				ADI_RATE_A( skp, rates.x, rates.z, rates.y, adirate );
				atterr = GetIDP()->GetAttitudeErrors_AerojetDAP();
				if (0) ADI_ERROR_C( skp, GetIDP()->GetNZError(), atterr.z, atterr.y, adierr );// TODO Nz hold
				else ADI_ERROR_B( skp, atterr.x, atterr.z, atterr.y, adierr );
				AEPFD_GMETER_STATIC( skp );
				AEPFD_GMETER_NZ( skp );
				HSI_E( skp, atan2( vel.x, vel.z ), true, GetIDP()->GetSelectedRunwayHeading(), false, true, GetIDP()->GetCourseDeviationScale(), GetIDP()->GetCourseDeviation(), GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				AEPFD_dAZ_HTA( skp );
				AEPFD_RANGERW( skp );
				AEPFD_HACCEL( skp );
				break;
			case 603:
				AEPFD_Header_AerojetDAP( skp, 603, vr );
				if (vr >= 0.9) Tape_MV_KEAS( skp, 'R', vr );
				else Tape_KEAS_MVR( skp, vr );
				Tape_Alpha( skp, vr );
				Tape_H_Hdot( skp, GetIDP()->GetAltitude(), GetIDP()->GetAltitudeRate() );
				ADI_STATIC( skp );
				ADI( skp, attPitch, attRoll, attYaw );
				rates = GetIDP()->GetRates();
				ADI_RATE_B( skp, rates.x, rates.z, rates.y, adirate, GetIDP()->GetAltitude() );
				atterr = GetIDP()->GetAttitudeErrors_AerojetDAP();
				if (GetIDP()->GetWOW() == false) ADI_ERROR_C( skp, GetIDP()->GetNZError(), atterr.z, atterr.y, adierr );
				else ADI_ERROR_D( skp, atterr.x, atterr.z, atterr.y, adierr );
				AEPFD_GMETER_STATIC( skp );
				AEPFD_GMETER_NZ( skp );
				HSI_E( skp, STS()->GetYaw(), true, GetIDP()->GetSelectedRunwayHeading(), false, true, GetIDP()->GetCourseDeviationScale(), GetIDP()->GetCourseDeviation(), GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
				if (GetIDP()->GetPrefinalState() == false)
				{
					AEPFD_dAZ_HTA( skp );
					AEPFD_RANGEHACC( skp );
				}
				AEPFD_RANGERW( skp );
				AEPFD_GSI( skp, GetIDP()->GetGSFlag(), GetIDP()->GetGlideSlopeDeviationScale(), GetIDP()->GetGlideSlopeDeviation() );
				break;
			case 801:
				ADI_STATIC( skp );
				ADI( skp, attPitch, attRoll, attYaw );
				break;
			case 901:
				Tapes_Invalid( skp );
				ADI_STATIC( skp );// TODO no rate and error scales
				ADI( skp, attPitch, attRoll, attYaw );
				AEPFD_GMETER_STATIC( skp );
				HSI_E( skp, 0.0, true, 0.0, false, true, 0.0, 0.0, GetIDP()->GetPrimaryBearingType(), GetIDP()->GetPrimaryBearing(), GetIDP()->GetSecondaryBearingType(), GetIDP()->GetSecondaryBearing() );
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
		int offset_top = 108;
		int offset_bottom = 110;
		char cbuf[8];
		int y = 0;
		int save;

		// Mach/V
		// 0.75K in window (1fps = 0.2893px) (4-27K)
		// M0.75 in window (M1 = 289.3px) (0-4)
		// 6653.9 + 1157.2 = 7811.1px + offsets
		// (should be +/- 0.7K and M0.7 but it needs a surface too big for D3D9)
		hDC_Tape_MACHV = CreateCompatibleDC( GetDC( NULL ) );
		HBITMAP hBM = CreateCompatibleBitmap( GetDC( NULL ), 43, 7811 + offset_top + offset_bottom );
		hBM_Tape_MACHV_tmp = (HBITMAP)SelectObject( hDC_Tape_MACHV, hBM );
		save = SaveDC( hDC_Tape_MACHV );

		SelectObject( hDC_Tape_MACHV, gdiWhitePen );
		SelectObject( hDC_Tape_MACHV, gdiWhiteBrush );
		Rectangle( hDC_Tape_MACHV, 0, 0, 43, 7811 + offset_top + offset_bottom );

		SetTextColor( hDC_Tape_MACHV, CR_BLACK );
		SetTextAlign( hDC_Tape_MACHV, TA_CENTER );
		SelectObject( hDC_Tape_MACHV, gdiSSVBFont_h18w9 );
		SetBkMode( hDC_Tape_MACHV, TRANSPARENT );
		SelectObject( hDC_Tape_MACHV, gdiBlackPen );

		for (int i = 270; i >= 41; i -= 1)
		{
			y = Round( ((270 - i) * 28.93) + offset_top );

			if ((i % 10) == 0)
			{
				sprintf_s( cbuf, 8, "%.1fK", (double)i / 10 );
				TextOut( hDC_Tape_MACHV, 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else if ((i % 2) == 0)
			{
				sprintf_s( cbuf, 8, "%.1f", (double)i / 10 );
				TextOut( hDC_Tape_MACHV, 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else
			{
				MoveToEx( hDC_Tape_MACHV, 0, y, NULL );
				LineTo( hDC_Tape_MACHV, 14, y );
			}
		}
		for (int i = 40; i >= 0; i--)
		{
			y = Round( ((40 - i) * 28.93) + 6653.9 + offset_top );

			if ((i % 2) == 0)
			{
				if ((i % 10) == 0)
				{
					sprintf_s( cbuf, 8, "%.1fM", (double)i / 10 );
					TextOut( hDC_Tape_MACHV, 22, y - 11, cbuf, strlen( cbuf ) );
				}
				else
				{
					sprintf_s( cbuf, 8, "%.1f", (double)i / 10 );
					TextOut( hDC_Tape_MACHV, 22, y - 11, cbuf, strlen( cbuf ) );
				}
			}
			else
			{
				MoveToEx( hDC_Tape_MACHV, 10, y, NULL );
				LineTo( hDC_Tape_MACHV, 33, y );
			}
		}
		RestoreDC( hDC_Tape_MACHV, save );


		// KEAS
		// 28KEAS in window (1KEAS = 7.75px) (500-0)
		// 3875px + offsets
		hDC_Tape_KEAS = CreateCompatibleDC( GetDC( NULL ) );
		hBM = CreateCompatibleBitmap( GetDC( NULL ), 43, 3875 + offset_top + offset_bottom );
		hBM_Tape_KEAS_tmp = (HBITMAP)SelectObject( hDC_Tape_KEAS, hBM );
		save = SaveDC( hDC_Tape_KEAS );

		SelectObject( hDC_Tape_KEAS, gdiWhitePen );
		SelectObject( hDC_Tape_KEAS, gdiWhiteBrush );
		Rectangle( hDC_Tape_KEAS, 0, 0, 43, 3875 + offset_top + offset_bottom );

		SetTextColor( hDC_Tape_KEAS, CR_BLACK );
		SetTextAlign( hDC_Tape_KEAS, TA_CENTER );
		SelectObject( hDC_Tape_KEAS, gdiSSVBFont_h18w9 );
		SetBkMode( hDC_Tape_KEAS, TRANSPARENT );
		SelectObject( hDC_Tape_KEAS, gdiBlackPen );

		for (int i = 500; i >= 0; i -= 5)
		{
			y = Round( ((500 - i) * 7.75) + offset_top );

			if ((i % 10) == 0)
			{
				sprintf_s( cbuf, 8, "%d", i );
				TextOut( hDC_Tape_KEAS, 21, y - 11, cbuf, strlen( cbuf ) );
			}
			else
			{
				MoveToEx( hDC_Tape_KEAS, 10, y, NULL );
				LineTo( hDC_Tape_KEAS, 33, y );
			}
		}
		RestoreDC( hDC_Tape_KEAS, save );


		// alpha
		// 23º in window (1º = 9.435px)
		// 3396px long + offsets
		// just graphics "base" creation, actual painting is done elsewhere
		hDC_Tape_Alpha = CreateCompatibleDC( GetDC( NULL ) );
		hBM = CreateCompatibleBitmap( GetDC( NULL ), 43, 3396 + offset_top + offset_bottom );
		hBM_Tape_Alpha_tmp = (HBITMAP)SelectObject( hDC_Tape_Alpha, hBM );


		// H
		// NM scale 10NM in window (1NM = 21.7px) (165-65.83137NM)
		// FT scale 70Kft in window (1ft = 0.0031px) (400-100Kft)
		// FT scale 11.5Kft in window (1ft = 0.01887px) (100-30Kft)
		// FT scale 5.5Kft in window (1ft = 0.03945px) n1(n5K)/n1000 m0.5 (30-2Kft)
		// FT scale 1400ft in window (1ft = 0.155px) (2000-200ft)
		// FT scale 200ft in window (1ft = 1.085px) n50m10 (200-0ft)
		// FT scale 450ft in window (1ft = 0.4822px) (0-(-1100)ft)
		// 2151.959 + 930 + 1320.9 + 1104.6 + 279 + 217 + 530.42 = 6533.879px long + offsets
		hDC_Tape_H = CreateCompatibleDC( GetDC( NULL ) );
		hBM = CreateCompatibleBitmap( GetDC( NULL ), 43, 6534 + offset_top + offset_bottom );
		hBM_Tape_H_tmp = (HBITMAP)SelectObject( hDC_Tape_H, hBM );
		save = SaveDC( hDC_Tape_H );

		SelectObject( hDC_Tape_H, gdiWhitePen );
		SelectObject( hDC_Tape_H, gdiWhiteBrush );
		Rectangle( hDC_Tape_H, 0, 0, 43, 5507 + offset_top );

		SelectObject( hDC_Tape_H, gdiYellowPen );
		SelectObject( hDC_Tape_H, gdiYellowBrush );
		Rectangle( hDC_Tape_H, 0, 5507 + offset_top, 43, 6003 + offset_top );

		SelectObject( hDC_Tape_H, gdiDarkGrayPen );
		SelectObject( hDC_Tape_H, gdiDarkGrayBrush );
		Rectangle( hDC_Tape_H, 0, 6003 + offset_top, 43, 6534 + offset_top + offset_bottom );

		SetTextColor( hDC_Tape_H, CR_BLACK );
		SetTextAlign( hDC_Tape_H, TA_CENTER );
		SelectObject( hDC_Tape_H, gdiSSVBFont_h18w9 );
		SetBkMode( hDC_Tape_H, TRANSPARENT );
		SelectObject( hDC_Tape_H, gdiBlackPen );

		for (int i = 165; i >= 67; i--)
		{
			y = Round( ((165 - i) * 21.7) + offset_top );

			if ((i % 5) == 0)
			{
				sprintf_s( cbuf, 8, "%dM", i );
				TextOut( hDC_Tape_H, 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else
			{
				MoveToEx( hDC_Tape_H, 29, y, NULL );
				LineTo( hDC_Tape_H, 43, y );
			}
		}
		for (int i = 400; i >= 100; i -= 5)
		{
			y = Round( ((400 - i) * 3.1) + offset_top + 2151.959 );

			if ((i % 50) == 0)
			{
				sprintf_s( cbuf, 8, "%dK", i );
				TextOut( hDC_Tape_H, 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else if ((i % 10) == 0)
			{
				MoveToEx( hDC_Tape_H, 0, y, NULL );
				LineTo( hDC_Tape_H, 15, y );
			}
		}
		for (int i = 99; i >= 30; i--)
		{
			y = Round( ((100 - i) * 18.87) + offset_top + 3081.959 );

			if ((i % 5) == 0)
			{
				sprintf_s( cbuf, 8, "%dK", i );
				TextOut( hDC_Tape_H, 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else
			{
				MoveToEx( hDC_Tape_H, 14, y, NULL );
				LineTo( hDC_Tape_H, 29, y );
			}
		}
		for (int i = 295; i > 20; i -= 5)
		{
			y = Round( ((300 - i) * 3.945) + offset_top + 4402.859 );

			if ((i % 50) == 0)
			{
				sprintf_s( cbuf, 8, "%.0fK", (double)i / 10 );
				TextOut( hDC_Tape_H, 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else if ((i % 10) == 0)
			{
				if (i > 40) sprintf_s( cbuf, 8, "%.0f", (double)i / 10 );
				else sprintf_s( cbuf, 8, "%d", i * 100 );
				TextOut( hDC_Tape_H, 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else
			{
				MoveToEx( hDC_Tape_H, 14, y, NULL );
				LineTo( hDC_Tape_H, 29, y );
			}
		}

		for (int i = 20; i > 2; i -= 1)
		{
			y = Round( ((20 - i) * 15.5) + offset_top + 5507.459 );

			if ((i % 2) == 0)
			{
				sprintf_s( cbuf, 8, "%d", i * 100 );
				TextOut( hDC_Tape_H, 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else
			{
				MoveToEx( hDC_Tape_H, 14, y, NULL );
				LineTo( hDC_Tape_H, 29, y );
			}
		}
		for (int i = 20; i >= 0; i -= 1)
		{
			y = Round( ((20 - i) * 10.85) + offset_top + 5786.459 );

			if ((i % 5) == 0)
			{
				sprintf_s( cbuf, 8, "%d", i * 10 );
				TextOut( hDC_Tape_H, 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else
			{
				MoveToEx( hDC_Tape_H, 14, y, NULL );
				LineTo( hDC_Tape_H, 29, y );
			}
		}

		SetTextColor( hDC_Tape_H, CR_WHITE );
		SelectObject( hDC_Tape_H, gdiWhitePen );

		for (int i = 0; i >= -110; i -= 5)
		{
			y = Round( (-i * 4.822) + offset_top + 6003.459 );

			if ((i % 10) == 0)
			{
				sprintf_s( cbuf, 8, "%d", i * 10 );
				TextOut( hDC_Tape_H, 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else
			{
				MoveToEx( hDC_Tape_H, 10, y, NULL );
				LineTo( hDC_Tape_H, 33, y );
			}
		}
		RestoreDC( hDC_Tape_H, save );


		// Hdot
		// small (inner) scale 165ft in window (1ft = 1.315px) (800-(-800))
		// large (outer) scale 700ft in window (1ft = 0.31px) (3000-800/(-800)-(-3000))
		// 682 + 2104 + 682 = 3468px long + offsets
		hDC_Tape_Hdot = CreateCompatibleDC( GetDC( NULL ) );
		hBM = CreateCompatibleBitmap( GetDC( NULL ), 43, 3468 + offset_top + offset_bottom );
		hBM_Tape_Hdot_tmp = (HBITMAP)SelectObject( hDC_Tape_Hdot, hBM );
		save = SaveDC( hDC_Tape_Hdot );

		SelectObject( hDC_Tape_Hdot, gdiWhitePen );
		SelectObject( hDC_Tape_Hdot, gdiWhiteBrush );
		Rectangle( hDC_Tape_Hdot, 0, 0, 43, 1734 + offset_top );

		SelectObject( hDC_Tape_Hdot, gdiDarkGrayPen );
		SelectObject( hDC_Tape_Hdot, gdiDarkGrayBrush );
		Rectangle( hDC_Tape_Hdot, 0, 1734 + offset_top, 43, 3468 + offset_top + offset_bottom );

		SetTextColor( hDC_Tape_Hdot, CR_BLACK );
		SetTextAlign( hDC_Tape_Hdot, TA_CENTER );
		SelectObject( hDC_Tape_Hdot, gdiSSVBFont_h18w9 );
		SetBkMode( hDC_Tape_Hdot, TRANSPARENT );
		SelectObject( hDC_Tape_Hdot, gdiBlackPen );

		for (int i = 30; i >= 8; i--)
		{
			y = ((30 - i) * 31) + offset_top;//y = Round( ((30 - i) * 31) + offset_top );

			if (i < 10)
			{
				sprintf_s( cbuf, 8, "%d", i * 100 );
				TextOut( hDC_Tape_Hdot, 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else if ((i % 5) == 0)
			{
				sprintf_s( cbuf, 8, "%.1fK", (double)i / 10 );
				TextOut( hDC_Tape_Hdot, 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else
			{
				MoveToEx( hDC_Tape_Hdot, 12, y, NULL );
				LineTo( hDC_Tape_Hdot, 31, y );
			}
		}
		for (int i = 80; i > 0; i--)
		{
			y = Round( ((80 - i) * 13.15) + 682 + offset_top );

			if ((i % 2) == 0)
			{
				sprintf_s( cbuf, 8, "%d", i * 10 );
				TextOut( hDC_Tape_Hdot, 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else
			{
				MoveToEx( hDC_Tape_Hdot, 12, y, NULL );
				LineTo( hDC_Tape_Hdot, 31, y );
			}
		}

		SetTextColor( hDC_Tape_Hdot, CR_WHITE );
		SelectObject( hDC_Tape_Hdot, gdiWhitePen );

		for (int i = 0; i >= -80; i--)
		{
			y = Round( ((80 - i) * 13.15) + 682 + offset_top );

			if ((i % 2) == 0)
			{
				sprintf_s( cbuf, 8, "%d", i * 10 );
				TextOut( hDC_Tape_Hdot, 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else
			{
				MoveToEx( hDC_Tape_Hdot, 12, y, NULL );
				LineTo( hDC_Tape_Hdot, 31, y );
			}
		}
		for (int i = -8; i >= -30; i--)
		{
			y = ((-8 - i) * 31) + 2786 + offset_top;//y = Round( ((-8 - i) * 31) + 2786 + offset_top );

			if (i > -10)
			{
				sprintf_s( cbuf, 8, "%d", i * 100 );
				TextOut( hDC_Tape_Hdot, 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else if ((i % 5) == 0)
			{
				sprintf_s( cbuf, 8, "%.1fK", (double)i / 10 );
				TextOut( hDC_Tape_Hdot, 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else
			{
				MoveToEx( hDC_Tape_Hdot, 12, y, NULL );
				LineTo( hDC_Tape_Hdot, 31, y );
			}
		}
		RestoreDC( hDC_Tape_Hdot, save );
		return;
	}

	void MDU::CreateTapes_Sketchpad( void )
	{
		if (sfh_Tape_MACHV) return;// already created

		// draw tapes
		int offset_top = 108;
		int offset_bottom = 110;
		char cbuf[8];
		int y = 0;

		// Mach/V
		// 0.75K in window (1fps = 0.2893px) (4-27K)
		// M0.75 in window (M1 = 289.3px) (0-4)
		// 6653.9 + 1157.2 = 7811.1px + offsets
		// (should be +/- 0.7K and M0.7 but it needs a surface too big for D3D9)
		sfh_Tape_MACHV = oapiCreateSurfaceEx( 43, 7811 + offset_top + offset_bottom, OAPISURFACE_TEXTURE | OAPISURFACE_RENDERTARGET | OAPISURFACE_NOMIPMAPS );
		oapi::Sketchpad* skp_Tape_MACHV = oapiGetSketchpad( sfh_Tape_MACHV );

		skp_Tape_MACHV->SetPen( skpWhitePen );
		skp_Tape_MACHV->SetBrush( skpWhiteBrush );
		skp_Tape_MACHV->Rectangle( 0, 0, 43, 7811 + offset_top + offset_bottom );

		skp_Tape_MACHV->SetTextColor( CR_BLACK );
		skp_Tape_MACHV->SetTextAlign( oapi::Sketchpad::CENTER );
		skp_Tape_MACHV->SetFont( skpSSVBFont_h18w9 );
		skp_Tape_MACHV->SetBackgroundColor( oapi::Sketchpad::BK_TRANSPARENT );
		skp_Tape_MACHV->SetPen( skpBlackPen );

		for (int i = 270; i >= 41; i -= 1)
		{
			y = Round( ((270 - i) * 28.93) + offset_top );

			if ((i % 10) == 0)
			{
				sprintf_s( cbuf, 8, "%.1fK", (double)i / 10 );
				skp_Tape_MACHV->Text( 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else if ((i % 2) == 0)
			{
				sprintf_s( cbuf, 8, "%.1f", (double)i / 10 );
				skp_Tape_MACHV->Text( 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else skp_Tape_MACHV->Line( 0, y, 14, y );
		}
		for (int i = 40; i >= 0; i--)
		{
			y = Round( ((40 - i) * 28.93) + 6653.9 + offset_top );

			if ((i % 2) == 0)
			{
				if ((i % 10) == 0)
				{
					sprintf_s( cbuf, 8, "%.1fM", (double)i / 10 );
					skp_Tape_MACHV->Text( 22, y - 11, cbuf, strlen( cbuf ) );
				}
				else
				{
					sprintf_s( cbuf, 8, "%.1f", (double)i / 10 );
					skp_Tape_MACHV->Text( 22, y - 11, cbuf, strlen( cbuf ) );
				}
			}
			else skp_Tape_MACHV->Line( 10, y, 33, y );
		}
		oapiReleaseSketchpad( skp_Tape_MACHV );

		// KEAS
		// 28KEAS in window (1KEAS = 7.75px) (500-0)
		// 3875px + offsets
		sfh_Tape_KEAS = oapiCreateSurfaceEx( 43, 3875 + offset_top + offset_bottom, OAPISURFACE_TEXTURE | OAPISURFACE_RENDERTARGET | OAPISURFACE_NOMIPMAPS );
		oapi::Sketchpad* skp_Tape_KEAS = oapiGetSketchpad( sfh_Tape_KEAS );

		skp_Tape_KEAS->SetPen( skpWhitePen );
		skp_Tape_KEAS->SetBrush( skpWhiteBrush );
		skp_Tape_KEAS->Rectangle( 0, 0, 43, 3875 + offset_top + offset_bottom );

		skp_Tape_KEAS->SetTextColor( CR_BLACK );
		skp_Tape_KEAS->SetTextAlign( oapi::Sketchpad::CENTER );
		skp_Tape_KEAS->SetFont( skpSSVBFont_h18w9 );
		skp_Tape_KEAS->SetBackgroundColor( oapi::Sketchpad::BK_TRANSPARENT );
		skp_Tape_KEAS->SetPen( skpBlackPen );

		for (int i = 500; i >= 0; i -= 5)
		{
			y = Round( ((500 - i) * 7.75) + offset_top );

			if ((i % 10) == 0)
			{
				sprintf_s( cbuf, 8, "%d", i );
				skp_Tape_KEAS->Text( 21, y - 11, cbuf, strlen( cbuf ) );
			}
			else skp_Tape_KEAS->Line( 10, y, 33, y );
		}
		oapiReleaseSketchpad( skp_Tape_KEAS );

		// alpha
		// 23º in window (1º = 9.435px)
		// 3396px long + offsets
		// just graphics "base" creation, actual painting is done elsewhere
		sfh_Tape_Alpha = oapiCreateSurfaceEx( 43, 3396 + offset_top + offset_bottom, OAPISURFACE_TEXTURE | OAPISURFACE_RENDERTARGET | OAPISURFACE_NOMIPMAPS );


		// H
		// NM scale 10NM in window (1NM = 21.7px) (165-65.83137NM)
		// FT scale 70Kft in window (1ft = 0.0031px) (400-100Kft)
		// FT scale 11.5Kft in window (1ft = 0.01887px) (100-30Kft)
		// FT scale 5.5Kft in window (1ft = 0.03945px) n1(n5K)/n1000 m0.5 (30-2Kft)
		// FT scale 1400ft in window (1ft = 0.155px) (2000-200ft)
		// FT scale 200ft in window (1ft = 1.085px) n50m10 (200-0ft)
		// FT scale 450ft in window (1ft = 0.4822px) (0-(-1100)ft)
		// 2151.959 + 930 + 1320.9 + 1104.6 + 279 + 217 + 530.42 = 6533.879px long + offsets
		sfh_Tape_H = oapiCreateSurfaceEx( 43, 6534 + offset_top + offset_bottom, OAPISURFACE_TEXTURE | OAPISURFACE_RENDERTARGET | OAPISURFACE_NOMIPMAPS );
		oapi::Sketchpad* skp_Tape_H = oapiGetSketchpad( sfh_Tape_H );

		skp_Tape_H->SetPen( skpWhitePen );
		skp_Tape_H->SetBrush( skpWhiteBrush );
		skp_Tape_H->Rectangle( 0, 0, 43, 5507 + offset_top );

		skp_Tape_H->SetPen( skpYellowPen );
		skp_Tape_H->SetBrush( skpYellowBrush );
		skp_Tape_H->Rectangle( 0, 5507 + offset_top, 43, 6003 + offset_top );

		skp_Tape_H->SetPen( skpDarkGrayPen );
		skp_Tape_H->SetBrush( skpDarkGrayBrush );
		skp_Tape_H->Rectangle( 0, 6003 + offset_top, 43, 6534 + offset_top + offset_bottom );

		skp_Tape_H->SetTextColor( CR_BLACK );
		skp_Tape_H->SetTextAlign( oapi::Sketchpad::CENTER );
		skp_Tape_H->SetFont( skpSSVBFont_h18w9 );
		skp_Tape_H->SetBackgroundColor( oapi::Sketchpad::BK_TRANSPARENT );
		skp_Tape_H->SetPen( skpBlackPen );

		for (int i = 165; i >= 67; i--)
		{
			y = Round( ((165 - i) * 21.7) + offset_top );

			if ((i % 5) == 0)
			{
				sprintf_s( cbuf, 8, "%dM", i );
				skp_Tape_H->Text( 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else skp_Tape_H->Line( 29, y, 43, y );
		}
		for (int i = 400; i >= 100; i -= 5)
		{
			y = Round( ((400 - i) * 3.1) + offset_top + 2151.959 );

			if ((i % 50) == 0)
			{
				sprintf_s( cbuf, 8, "%dK", i );
				skp_Tape_H->Text( 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else if ((i % 10) == 0) skp_Tape_H->Line( 0, y, 15, y );
		}
		for (int i = 99; i >= 30; i--)
		{
			y = Round( ((100 - i) * 18.87) + offset_top + 3081.959 );

			if ((i % 5) == 0)
			{
				sprintf_s( cbuf, 8, "%dK", i );
				skp_Tape_H->Text( 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else skp_Tape_H->Line( 14, y, 29, y );
		}
		for (int i = 295; i > 20; i -= 5)
		{
			y = Round( ((300 - i) * 3.945) + offset_top + 4402.859 );

			if ((i % 50) == 0)
			{
				sprintf_s( cbuf, 8, "%.0fK", (double)i / 10 );
				skp_Tape_H->Text( 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else if ((i % 10) == 0)
			{
				if (i > 40) sprintf_s( cbuf, 8, "%.0f", (double)i / 10 );
				else sprintf_s( cbuf, 8, "%d", i * 100 );
				skp_Tape_H->Text( 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else skp_Tape_H->Line( 14, y, 29, y );
		}

		for (int i = 20; i > 2; i -= 1)
		{
			y = Round( ((20 - i) * 15.5) + offset_top + 5507.459 );

			if ((i % 2) == 0)
			{
				sprintf_s( cbuf, 8, "%d", i * 100 );
				skp_Tape_H->Text( 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else skp_Tape_H->Line( 14, y, 29, y );
		}
		for (int i = 20; i >= 0; i -= 1)
		{
			y = Round( ((20 - i) * 10.85) + offset_top + 5786.459 );

			if ((i % 5) == 0)
			{
				sprintf_s( cbuf, 8, "%d", i * 10 );
				skp_Tape_H->Text( 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else skp_Tape_H->Line( 14, y, 29, y );
		}

		skp_Tape_H->SetTextColor( CR_WHITE );
		skp_Tape_H->SetPen( skpWhitePen );

		for (int i = 0; i >= -110; i -= 5)
		{
			y = Round( (-i * 4.822) + offset_top + 6003.459 );

			if ((i % 10) == 0)
			{
				sprintf_s( cbuf, 8, "%d", i * 10 );
				skp_Tape_H->Text( 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else skp_Tape_H->Line( 10, y, 33, y );
		}
		oapiReleaseSketchpad( skp_Tape_H );


		// Hdot
		// small (inner) scale 165ft in window (1ft = 1.315px) (800-(-800))
		// large (outer) scale 700ft in window (1ft = 0.31px) (3000-800/(-800)-(-3000))
		// 682 + 2104 + 682 = 3468px long + offsets
		sfh_Tape_Hdot = oapiCreateSurfaceEx( 43, 3468 + offset_top + offset_bottom, OAPISURFACE_TEXTURE | OAPISURFACE_RENDERTARGET | OAPISURFACE_NOMIPMAPS );
		oapi::Sketchpad* skp_Tape_Hdot = oapiGetSketchpad( sfh_Tape_Hdot );

		skp_Tape_Hdot->SetPen( skpWhitePen );
		skp_Tape_Hdot->SetBrush( skpWhiteBrush );
		skp_Tape_Hdot->Rectangle( 0, 0, 43, 1734 + offset_top );

		skp_Tape_Hdot->SetPen( skpDarkGrayPen );
		skp_Tape_Hdot->SetBrush( skpDarkGrayBrush );
		skp_Tape_Hdot->Rectangle( 0, 1734 + offset_top, 43, 3468 + offset_top + offset_bottom );

		skp_Tape_Hdot->SetTextColor( CR_BLACK );
		skp_Tape_Hdot->SetTextAlign( oapi::Sketchpad::CENTER );
		skp_Tape_Hdot->SetFont( skpSSVBFont_h18w9 );
		skp_Tape_Hdot->SetBackgroundColor( oapi::Sketchpad::BK_TRANSPARENT );
		skp_Tape_Hdot->SetPen( skpBlackPen );

		for (int i = 30; i >= 8; i--)
		{
			y = ((30 - i) * 31) + offset_top;//y = Round( ((30 - i) * 31) + offset_top );

			if (i < 10)
			{
				sprintf_s( cbuf, 8, "%d", i * 100 );
				skp_Tape_Hdot->Text( 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else if ((i % 5) == 0)
			{
				sprintf_s( cbuf, 8, "%.1fK", (double)i / 10 );
				skp_Tape_Hdot->Text( 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else skp_Tape_Hdot->Line( 12, y, 31, y );
		}
		for (int i = 80; i > 0; i--)
		{
			y = Round( ((80 - i) * 13.15) + 682 + offset_top );

			if ((i % 2) == 0)
			{
				sprintf_s( cbuf, 8, "%d", i * 10 );
				skp_Tape_Hdot->Text( 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else skp_Tape_Hdot->Line( 12, y, 31, y );
		}

		skp_Tape_Hdot->SetTextColor( CR_WHITE );
		skp_Tape_Hdot->SetPen( skpWhitePen );

		for (int i = 0; i >= -80; i--)
		{
			y = Round( ((80 - i) * 13.15) + 682 + offset_top );

			if ((i % 2) == 0)
			{
				sprintf_s( cbuf, 8, "%d", i * 10 );
				skp_Tape_Hdot->Text( 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else skp_Tape_Hdot->Line( 12, y, 31, y );
		}
		for (int i = -8; i >= -30; i--)
		{
			y = ((-8 - i) * 31) + 2786 + offset_top;//y = Round( ((-8 - i) * 31) + 2786 + offset_top );

			if (i > -10)
			{
				sprintf_s( cbuf, 8, "%d", i * 100 );
				skp_Tape_Hdot->Text( 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else if ((i % 5) == 0)
			{
				sprintf_s( cbuf, 8, "%.1fK", (double)i / 10 );
				skp_Tape_Hdot->Text( 22, y - 11, cbuf, strlen( cbuf ) );
			}
			else skp_Tape_Hdot->Line( 12, y, 31, y );
		}
		oapiReleaseSketchpad( skp_Tape_Hdot );
		return;
	}

	void MDU::DrawAlphaTapeBG_GDI( void )
	{
		int offset_top = 108;
		int offset_bottom = 110;
		int save = SaveDC( hDC_Tape_Alpha );

		SelectObject( hDC_Tape_Alpha, gdiWhitePen );
		SelectObject( hDC_Tape_Alpha, gdiWhiteBrush );
		Rectangle( hDC_Tape_Alpha, 0, 0, 43, 1698 + offset_top );

		SelectObject( hDC_Tape_Alpha, gdiDarkGrayPen );
		SelectObject( hDC_Tape_Alpha, gdiDarkGrayBrush );
		Rectangle( hDC_Tape_Alpha, 0, 1698 + 1 + offset_top, 43, 3396 + offset_top + offset_bottom );

		RestoreDC( hDC_Tape_Alpha, save );
		return;
	}

	void MDU::DrawAlphaTapeBG_Sketchpad( void )
	{
		int offset_top = 108;
		int offset_bottom = 110;
		oapi::Sketchpad* skp_Tape_Alpha = oapiGetSketchpad( sfh_Tape_Alpha );

		skp_Tape_Alpha->SetPen( skpWhitePen );
		skp_Tape_Alpha->SetBrush( skpWhiteBrush );
		skp_Tape_Alpha->Rectangle( 0, 0, 43, 1698 + offset_top );

		skp_Tape_Alpha->SetPen( skpDarkGrayPen );
		skp_Tape_Alpha->SetBrush( skpDarkGrayBrush );
		skp_Tape_Alpha->Rectangle( 0, 1698 + 1 + offset_top, 43, 3396 + offset_top + offset_bottom );

		oapiReleaseSketchpad( skp_Tape_Alpha );
		return;
	}

	void MDU::DrawAlphaTapeFG_GDI( int min, int max )
	{
		int offset_top = 108;
		char cbuf[8];
		int y = 0;
		int save = SaveDC( hDC_Tape_Alpha );

		SetTextColor( hDC_Tape_Alpha, CR_BLACK );
		SetTextAlign( hDC_Tape_Alpha, TA_CENTER );
		SelectObject( hDC_Tape_Alpha, gdiSSVBFont_h18w9 );
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

			y = Round( ((180 - i) * 9.435) + offset_top );

			MoveToEx( hDC_Tape_Alpha, 35, y, NULL );
			LineTo( hDC_Tape_Alpha, 43, y );

			if ((i % 5) == 0)
			{
				sprintf_s( cbuf, 8, "%d", i );
				if (i > -100) TextOut( hDC_Tape_Alpha, 19, y - 11, cbuf, strlen( cbuf ) );
				else TextOut( hDC_Tape_Alpha, 16, y - 11, cbuf, strlen( cbuf ) );
			}
		}

		RestoreDC( hDC_Tape_Alpha, save );
		return;
	}

	void MDU::DrawAlphaTapeFG_Sketchpad( int min, int max )
	{
		int offset_top = 108;
		char cbuf[8];
		int y = 0;
		oapi::Sketchpad* skp_Tape_Alpha = oapiGetSketchpad( sfh_Tape_Alpha );

		skp_Tape_Alpha->SetTextColor( CR_BLACK );
		skp_Tape_Alpha->SetTextAlign( oapi::Sketchpad::CENTER );
		skp_Tape_Alpha->SetFont( skpSSVBFont_h18w9 );
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

			y = Round( ((180 - i) * 9.435) + offset_top );

			skp_Tape_Alpha->Line( 35, y, 43, y );

			if ((i % 5) == 0)
			{
				sprintf_s( cbuf, 8, "%d", i );
				if (i > -100) skp_Tape_Alpha->Text( 19, y - 11, cbuf, strlen( cbuf ) );
				else skp_Tape_Alpha->Text( 16, y - 11, cbuf, strlen( cbuf ) );
			}
		}
		oapiReleaseSketchpad( skp_Tape_Alpha );
		return;
	}

	void MDU::DrawAlphaTapeLim_GDI( double min, double max )
	{
		int offset_top = 108;
		int save = SaveDC( hDC_Tape_Alpha );

		SelectObject( hDC_Tape_Alpha, gdiLightGreenPen );
		SelectObject( hDC_Tape_Alpha, gdiLightGreenBrush );
		Rectangle( hDC_Tape_Alpha, 35, 1698 + offset_top - Round( max * 9.435 ), 43, 1698 + offset_top - Round( min * 9.435 ) );

		RestoreDC( hDC_Tape_Alpha, save );
		return;
	}

	void MDU::DrawAlphaTapeLim_Sketchpad( double min, double max )
	{
		int offset_top = 108;
		oapi::Sketchpad* skp_Tape_Alpha = oapiGetSketchpad( sfh_Tape_Alpha );

		skp_Tape_Alpha->SetPen( skpLightGreenPen );
		skp_Tape_Alpha->SetBrush( skpLightGreenBrush );
		skp_Tape_Alpha->Rectangle( 35, 1698 + offset_top - Round( max * 9.435 ), 43, 1698 + offset_top - Round( min * 9.435 ) );

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
		HBITMAP hBM = CreateCompatibleBitmap( GetDC( NULL ), 192, 192 );
		hBM_ADI_tmp = (HBITMAP)SelectObject( hDC_ADI, hBM );
		save_ADI = SaveDC( hDC_ADI );
		SelectObject( hDC_ADI, gdiSSVBFont_h12w7 );

		hDC_ADI_ORBIT = CreateCompatibleDC( hDC_ADI );
		hBM = CreateCompatibleBitmap( hDC_ADI, 222, 222 );
		hBM_ADI_ORBIT_tmp = (HBITMAP)SelectObject( hDC_ADI_ORBIT, hBM );
		save_ADI_ORBIT = SaveDC( hDC_ADI_ORBIT );
		SelectObject( hDC_ADI_ORBIT, gdiSSVBFont_h12w7 );

		if (hDC_ADIMASK) return;// already created

		hDC_ADIMASK = CreateCompatibleDC( hDC_ADI );
		hBM = CreateCompatibleBitmap( hDC_ADI, 192, 192 );
		hBM_ADIMASK_tmp = (HBITMAP)SelectObject( hDC_ADIMASK, hBM );
		int save = SaveDC( hDC_ADIMASK );
		SelectObject( hDC_ADIMASK, gdiWhitePen );
		SelectObject( hDC_ADIMASK, gdiWhiteBrush );
		::Ellipse( hDC_ADIMASK, 1, 1, 191, 191 );
		RestoreDC( hDC_ADIMASK, save );

		hDC_ADIMASK_ORBIT = CreateCompatibleDC( hDC_ADI );
		hBM = CreateCompatibleBitmap( hDC_ADI, 222, 222 );
		hBM_ADIMASK_ORBIT_tmp = (HBITMAP)SelectObject( hDC_ADIMASK_ORBIT, hBM );
		save = SaveDC( hDC_ADIMASK_ORBIT );
		SelectObject( hDC_ADIMASK_ORBIT, gdiWhitePen );
		SelectObject( hDC_ADIMASK_ORBIT, gdiWhiteBrush );
		::Ellipse( hDC_ADIMASK_ORBIT, 1, 1, 221, 221 );
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

	void MDU::Tape_KEAS_MVR( HDC hDC, double vel )
	{
		char cbuf[8];
		double keas = sqrt( STS()->GetDynPressure() * PA2PSF ) * 17.18;
		SelectObject( hDC, gdiWhitePen );
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 13, 54, 59, 274 );
		SelectObject( hDC, gdiLightGrayPen );
		Rectangle( hDC, 13, 285, 59, 309 );

		SelectObject( hDC, gdiSSVAFont_h11w9 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		TextOut( hDC, 17, 39, "KEAS", 4 );
		TextOut( hDC, 17, 315, "M/VR", 4 );

		double tapekeas = keas;
		if (tapekeas > 500) tapekeas = 500;
		BitBlt( hDC, 14, 55, 43, 217, hDC_Tape_KEAS, 0, 3875 - Round( tapekeas * 7.75 ), SRCCOPY );

		Rectangle( hDC, 13, 150, 59, 175 );

		SelectObject( hDC, gdiSSVBFont_h18w9 );
		SetTextColor( hDC, CR_WHITE );
		SetTextAlign( hDC, TA_RIGHT );
		sprintf_s( cbuf, 8, "%.0f", keas );
		TextOut( hDC, 49, 151, cbuf, strlen( cbuf ) );
		sprintf_s( cbuf, 8, "%.2f", vel );
		TextOut( hDC, 57, 285, cbuf, strlen( cbuf ) );
		SetTextAlign( hDC, TA_LEFT );
		return;
	}

	void MDU::Tape_KEAS_MVR( oapi::Sketchpad2* skp, double vel )
	{
		char cbuf[8];
		double keas = sqrt( STS()->GetDynPressure() * PA2PSF ) * 17.18;
		skp->SetPen( skpWhitePen );
		skp->SetBrush( skpBlackBrush );
		skp->Rectangle( 13, 54, 59, 274 );
		skp->SetPen( skpLightGrayPen );
		skp->Rectangle( 13, 285, 59, 309 );

		skp->SetFont( skpSSVAFont_h11w9 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Text( 17, 39, "KEAS", 4 );
		skp->Text( 17, 315, "M/VR", 4 );

		double tapekeas = keas;
		if (tapekeas > 500) tapekeas = 500;
		RECT src;
		src.left = 0;
		src.top = 3875 - Round( tapekeas * 7.75 );
		src.right = 43;
		src.bottom = src.top + 217;
		skp->CopyRect( sfh_Tape_KEAS, &src, 14, 56 );

		skp->Rectangle( 13, 150, 59, 175 );

		skp->SetFont( skpSSVBFont_h18w9 );
		skp->SetTextColor( CR_WHITE );
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );
		sprintf_s( cbuf, 8, "%.0f", keas );
		skp->Text( 49, 151, cbuf, strlen( cbuf ) );
		sprintf_s( cbuf, 8, "%.2f", vel );
		skp->Text( 57, 285, cbuf, strlen( cbuf ) );
		skp->SetTextAlign( oapi::Sketchpad::LEFT );
		return;
	}

	void MDU::Tape_MV_KEAS( HDC hDC, char label, double vel )
	{
		char cbuf[8];
		double keas = sqrt( STS()->GetDynPressure() * PA2PSF ) * 17.18;
		SelectObject( hDC, gdiWhitePen );
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 13, 54, 59, 274 );
		SelectObject( hDC, gdiLightGrayPen );
		Rectangle( hDC, 13, 285, 59, 309 );

		SelectObject( hDC, gdiSSVAFont_h11w9 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		sprintf_s( cbuf, 8, "M/V%c", label );
		TextOut( hDC, 17, 39, cbuf, 4 );
		TextOut( hDC, 17, 315, "KEAS", 4 );

		SelectObject( hDC, gdiSSVBFont_h18w9 );
		SetTextColor( hDC, CR_WHITE );
		SetTextAlign( hDC, TA_RIGHT );
		BitBlt( hDC, 14, 55, 43, 217, hDC_Tape_MACHV, 0, Round( 7811.1 - vel * 289.3 ), SRCCOPY );

		Rectangle( hDC, 13, 150, 59, 175 );
		sprintf_s( cbuf, 8, "%.2f", vel );
		TextOut( hDC, 57, 151, cbuf, strlen( cbuf ) );

		sprintf_s( cbuf, 8, "%.0f", keas );
		TextOut( hDC, 49, 285, cbuf, strlen( cbuf ) );
		SetTextAlign( hDC, TA_LEFT );
		return;
	}

	void MDU::Tape_MV_KEAS( oapi::Sketchpad2* skp, char label, double vel )
	{
		char cbuf[8];
		double keas = sqrt( STS()->GetDynPressure() * PA2PSF ) * 17.18;
		skp->SetPen( skpWhitePen );
		skp->SetBrush( skpBlackBrush );
		skp->Rectangle( 13, 54, 59, 274 );
		skp->SetPen( skpLightGrayPen );
		skp->Rectangle( 13, 285, 59, 309 );

		skp->SetFont( skpSSVAFont_h11w9 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		sprintf_s( cbuf, 8, "M/V%c", label );
		skp->Text( 17, 39, cbuf, 4 );
		skp->Text( 17, 315, "KEAS", 4 );

		skp->SetFont( skpSSVBFont_h18w9 );
		skp->SetTextColor( CR_WHITE );
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );

		RECT src;
		src.left = 0;
		src.top = Round( 7811.1 - vel * 289.3 );
		src.right = 43;
		src.bottom = src.top + 217;
		skp->CopyRect( sfh_Tape_MACHV, &src, 14, 56 );

		skp->Rectangle( 13, 150, 59, 175 );
		sprintf_s( cbuf, 8, "%.2f", vel );
		skp->Text( 57, 151, cbuf, strlen( cbuf ) );

		sprintf_s( cbuf, 8, "%.0f", keas );
		skp->Text( 49, 285, cbuf, strlen( cbuf ) );
		skp->SetTextAlign( oapi::Sketchpad::LEFT );
		return;
	}

	void MDU::Tape_Alpha( HDC hDC, double vel )
	{
		SelectObject( hDC, gdiSSVAFont_h11w9 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		char cbuf[8];
		sprintf_s( cbuf, 8, "%c", 254 );
		TextOut( hDC, 82, 39, cbuf, 1 );

		SelectObject( hDC, gdiWhitePen );
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 68, 54, 114, 274 );

		double alpha = STS()->GetAOA() * DEG;

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
		BitBlt( hDC, 69, 55, 43, 217, hDC_Tape_Alpha, 0, 1698 - Round( alpha * 9.435 ), SRCCOPY );

		// max L/D alpha
		if ((vel > 0.0) && (vel < 3.0))
		{
			double maxLD = 0.0;
			if (vel > MaxLD_Mach[0]) maxLD = listerp( MaxLD_Mach, MaxLD_Alpha, MaxLD_count, vel );
			else maxLD = MaxLD_Alpha[0];// maintain minimum value

			maxLD -= alpha;
			if (fabs( maxLD ) < 11.0)
			{
				int pos = Round( maxLD * 9.435 );
				POINT diamond[4];
				diamond[0].x = 103;// start at top moving cw
				diamond[0].y = 155 - pos;
				diamond[1].x = 111;
				diamond[1].y = 163 - pos;
				diamond[2].x = 103;
				diamond[2].y = 171 - pos;
				diamond[3].x = 95;
				diamond[3].y = 163 - pos;
				SelectObject( hDC, gdiMagentaBrush );
				SelectObject( hDC, gdiBlackPen );
				Polygon( hDC, diamond, 4 );

				diamond[0].y += 6;
				diamond[1].x = 105;
				diamond[2].y -= 6;
				diamond[3].x = 101;
				SelectObject( hDC, gdiBlackBrush );
				Polygon( hDC, diamond, 4 );
			}
		}

		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiBlackBrush );
		static const POINT poly[5] = {{111,163},{104,175},{64,175},{64,150},{104,150}};// start at tip moving cw
		Polygon( hDC, poly, 5 );

		SelectObject( hDC, gdiSSVBFont_h18w9 );
		SetTextColor( hDC, CR_WHITE );
		SetTextAlign( hDC, TA_RIGHT );
		if (alpha >= -100) sprintf_s( cbuf, 8, "%.1f", alpha );
		else sprintf_s( cbuf, 8, "%.0f", alpha );
		TextOut( hDC, 108, 151, cbuf, strlen( cbuf ) );
		SetTextAlign( hDC, TA_LEFT );
		return;
	}

	void MDU::Tape_Alpha( oapi::Sketchpad2* skp, double vel )
	{
		skp->SetFont( skpSSVAFont_h11w9 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		char cbuf[8];
		sprintf_s( cbuf, 8, "%c", 254 );
		skp->Text( 82, 39, cbuf, 1 );

		skp->SetPen( skpWhitePen );
		skp->SetBrush( skpBlackBrush );
		skp->Rectangle( 68, 54, 114, 274 );

		double alpha = STS()->GetAOA() * DEG;

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
		src.top = 1698 - Round( alpha * 9.435 );
		src.right = 43;
		src.bottom = src.top + 217;
		skp->CopyRect( sfh_Tape_Alpha, &src, 69, 56 );

		// max L/D alpha
		if ((vel > 0.0) && (vel < 3.0))
		{
			double maxLD = 0.0;
			if (vel > MaxLD_Mach[0]) maxLD = listerp( MaxLD_Mach, MaxLD_Alpha, MaxLD_count, vel );
			else maxLD = MaxLD_Alpha[0];// maintain minimum value

			maxLD -= alpha;
			if (fabs( maxLD ) < 11.0)
			{
				int pos = Round( maxLD * 9.435 );
				oapi::IVECTOR2 diamond[4];
				diamond[0].x = 103;// start at top moving cw
				diamond[0].y = 155 - pos;
				diamond[1].x = 111;
				diamond[1].y = 163 - pos;
				diamond[2].x = 103;
				diamond[2].y = 171 - pos;
				diamond[3].x = 95;
				diamond[3].y = 163 - pos;
				skp->SetBrush( skpMagentaBrush );
				skp->SetPen( skpBlackPen );
				skp->Polygon( diamond, 4 );

				diamond[0].y += 6;
				diamond[1].x = 105;
				diamond[2].y -= 6;
				diamond[3].x = 101;
				skp->SetBrush( skpBlackBrush );
				skp->Polygon( diamond, 4 );
			}
		}

		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpBlackBrush );
		static const oapi::IVECTOR2 poly[5] = {{111,163},{104,175},{64,175},{64,150},{104,150}};// start at tip moving cw
		skp->Polygon( poly, 5 );

		skp->SetFont( skpSSVBFont_h18w9 );
		skp->SetTextColor( CR_WHITE );
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );
		if (alpha >= -100) sprintf_s( cbuf, 8, "%.1f", alpha );
		else sprintf_s( cbuf, 8, "%.0f", alpha );
		skp->Text( 108, 151, cbuf, strlen( cbuf ) );
		skp->SetTextAlign( oapi::Sketchpad::LEFT );
		return;
	}

	void MDU::Tape_H_Hdot( HDC hDC, double Altitude_ft, double Hdot )
	{
		SelectObject( hDC, gdiSSVAFont_h11w9 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		TextOut( hDC, 411, 39, "H", 1 );
		SelectObject( hDC, gdiWhitePen );
		Rectangle( hDC, 394, 54, 440, 274 );
		int pos;
		double Altitude_NM = 0;
		if (Altitude_ft > 400000)
		{
			Altitude_NM = Altitude_ft * FT2NM;
			if (Altitude_NM > 165) Altitude_NM = 165;
			pos = Round( 3580.5 - Altitude_NM * 21.7 );
		}
		else if (Altitude_ft > 100000)
		{
			pos = Round( 3391.959271 - Altitude_ft * 0.0031 );
		}
		else if (Altitude_ft > 30000)
		{
			pos = Round( 4968.959271 - Altitude_ft * 0.01887 );
		}
		else if (Altitude_ft > 2000)
		{
			pos = Round( 5586.359271 - Altitude_ft * 0.03945 );
		}
		else if (Altitude_ft > 200)
		{
			pos = Round( 5817.459271 - Altitude_ft * 0.155 );
		}
		else if (Altitude_ft > 0)
		{
			pos = Round( 6003.459 - Altitude_ft * 1.085 );
		}
		else //if (Altitude_ft > -1100)
		{
			if (Altitude_ft < -1100) Altitude_ft = -1100;
			pos = Round( 6003.459 - Altitude_ft * 0.4822 );
		}
		BitBlt( hDC, 395, 55, 43, 217, hDC_Tape_H, 0, pos, SRCCOPY );

		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 394, 150, 440, 175 );
		SelectObject( hDC, gdiSSVBFont_h18w9 );
		SetTextColor( hDC, CR_WHITE );
		SetTextAlign( hDC, TA_RIGHT );
		char cbuf[8];
		if (Altitude_ft < 10000)
		{
			sprintf_s( cbuf, 8, "%d", (int)Altitude_ft );
			TextOut( hDC, 430, 151, cbuf, strlen( cbuf ) );
		}
		else if (Altitude_ft < 400000)
		{
			sprintf_s( cbuf, 8, "%d", (int)Altitude_ft / 1000 );
			TextOut( hDC, 430, 151, cbuf, strlen( cbuf ) );
			SelectObject( hDC, gdiSSVBFont_h12w7 );
			SetTextColor( hDC, CR_LIGHT_GRAY );
			TextOut( hDC, 438, 155, "K", 1 );
		}
		else
		{
			sprintf_s( cbuf, 8, "%.0f", Altitude_NM );
			TextOut( hDC, 430, 151, cbuf, strlen( cbuf ) );
			SelectObject( hDC, gdiSSVBFont_h12w7 );
			SetTextColor( hDC, CR_LIGHT_GRAY );
			TextOut( hDC, 438, 155, "M", 1 );
		}
		SetTextAlign( hDC, TA_LEFT );

		SelectObject( hDC, gdiSSVAFont_h11w9 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		SetPixel( hDC, 481, 37, CR_LIGHT_GRAY );
		TextOut( hDC, 477, 39, "H", 1 );
		SelectObject( hDC, gdiWhitePen );
		Rectangle( hDC, 459, 54, 505, 274 );
		if (Hdot > 800)
		{
			if (Hdot > 3000) Hdot = 3000;
			pos = Round( (3000 - Hdot) * 0.31 );
		}
		else if (Hdot > -800)
		{
			pos = Round( 1734 - (Hdot * 1.315) );
		}
		else
		{
			if (Hdot < -3000) Hdot = -3000;
			pos = Round( 2538 - (Hdot * 0.31) );
		}
		BitBlt( hDC, 460, 55, 43, 217, hDC_Tape_Hdot, 0, pos, SRCCOPY );

		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 459, 150, 505, 175 );
		SelectObject( hDC, gdiSSVBFont_h18w9 );
		SetTextColor( hDC, CR_WHITE );
		SetTextAlign( hDC, TA_RIGHT );
		sprintf_s( cbuf, 8, "%.0f", Hdot );
		TextOut( hDC, 503, 151, cbuf, strlen( cbuf ) );
		SetTextAlign( hDC, TA_LEFT );
		return;
	}

	void MDU::Tape_H_Hdot( oapi::Sketchpad2* skp, double Altitude_ft, double Hdot )
	{
		skp->SetFont( skpSSVAFont_h11w9 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Text( 411, 39, "H", 1 );
		skp->SetPen( skpWhitePen );
		skp->Rectangle( 394, 54, 440, 274 );
		int pos;
		double Altitude_NM = 0;
		if (Altitude_ft > 400000)
		{
			Altitude_NM = Altitude_ft * FT2NM;
			if (Altitude_NM > 165) Altitude_NM = 165;
			pos = Round( 3580.5 - Altitude_NM * 21.7 );
		}
		else if (Altitude_ft > 100000)
		{
			pos = Round( 3391.959271 - Altitude_ft * 0.0031 );
		}
		else if (Altitude_ft > 30000)
		{
			pos = Round( 4968.959271 - Altitude_ft * 0.01887 );
		}
		else if (Altitude_ft > 2000)
		{
			pos = Round( 5586.359271 - Altitude_ft * 0.03945 );
		}
		else if (Altitude_ft > 200)
		{
			pos = Round( 5817.459271 - Altitude_ft * 0.155 );
		}
		else if (Altitude_ft > 0)
		{
			pos = Round( 6003.459 - Altitude_ft * 1.085 );
		}
		else //if (Altitude_ft > -1100)
		{
			if (Altitude_ft < -1100) Altitude_ft = -1100;
			pos = Round( 6003.459 - Altitude_ft * 0.4822 );
		}
		RECT src;
		src.left = 0;
		src.top = pos;
		src.right = 43;
		src.bottom = src.top + 217;
		skp->CopyRect( sfh_Tape_H, &src, 395, 56 );

		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpBlackBrush );
		skp->Rectangle( 394, 150, 440, 175 );
		skp->SetFont( skpSSVBFont_h18w9 );
		skp->SetTextColor( CR_WHITE );
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );
		char cbuf[8];
		if (Altitude_ft < 10000)
		{
			sprintf_s( cbuf, 8, "%d", (int)Altitude_ft );
			skp->Text( 430, 151, cbuf, strlen( cbuf ) );
		}
		else if (Altitude_ft < 400000)
		{
			sprintf_s( cbuf, 8, "%d", (int)Altitude_ft / 1000 );
			skp->Text( 430, 151, cbuf, strlen( cbuf ) );
			skp->SetFont( skpSSVBFont_h12w7 );
			skp->SetTextColor( CR_LIGHT_GRAY );
			skp->Text( 438, 155, "K", 1 );
		}
		else
		{
			sprintf_s( cbuf, 8, "%.0f", Altitude_NM );
			skp->Text( 430, 151, cbuf, strlen( cbuf ) );
			skp->SetFont( skpSSVBFont_h12w7 );
			skp->SetTextColor( CR_LIGHT_GRAY );
			skp->Text( 438, 155, "M", 1 );
		}
		skp->SetTextAlign( oapi::Sketchpad::LEFT );

		skp->SetFont( skpSSVAFont_h11w9 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Pixel( 481, 37, CR_LIGHT_GRAY );
		skp->Text( 477, 39, "H", 1 );
		skp->SetPen( skpWhitePen );
		skp->Rectangle( 459, 54, 505, 274 );
		if (Hdot > 800)
		{
			if (Hdot > 3000) Hdot = 3000;
			pos = Round( (3000 - Hdot) * 0.31 );
		}
		else if (Hdot > -800)
		{
			pos = Round( 1734 - (Hdot * 1.315) );
		}
		else
		{
			if (Hdot < -3000) Hdot = -3000;
			pos = Round( 2538 - (Hdot * 0.31) );
		}
		src.top = pos;
		src.bottom = src.top + 217;
		skp->CopyRect( sfh_Tape_Hdot, &src, 460, 56 );

		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpBlackBrush );
		skp->Rectangle( 459, 150, 505, 175 );
		skp->SetFont( skpSSVBFont_h18w9 );
		skp->SetTextColor( CR_WHITE );
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );
		sprintf_s( cbuf, 8, "%.0f", Hdot );
		skp->Text( 503, 151, cbuf, strlen( cbuf ) );
		skp->SetTextAlign( oapi::Sketchpad::LEFT );
		return;
	}

	void MDU::Tapes_Invalid( HDC hDC )
	{
		SelectObject( hDC, gdiRedPen );
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 13, 54, 59, 274 );
		Rectangle( hDC, 13, 150, 59, 175 );
		Rectangle( hDC, 13, 285, 59, 309 );

		Rectangle( hDC, 68, 54, 114, 274 );
		static const POINT poly[5] = {{111,163},{104,175},{64,175},{64,150},{104,150}};// start at tip moving cw
		Polygon( hDC, poly, 5 );

		Rectangle( hDC, 394, 54, 440, 274 );
		Rectangle( hDC, 394, 150, 440, 175 );

		Rectangle( hDC, 459, 54, 505, 274 );
		Rectangle( hDC, 459, 150, 505, 175 );

		SelectObject( hDC, gdiSSVAFont_h11w9 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		TextOut( hDC, 17, 39, "M/V", 3 );
		TextOut( hDC, 17, 315, "KEAS", 4 );

		char alpha[4];
		sprintf_s( alpha, 4, "%c", 254 );
		TextOut( hDC, 82, 39, alpha, 1 );

		TextOut( hDC, 411, 39, "H", 1 );
		SetPixel( hDC, 481, 37, CR_LIGHT_GRAY );
		TextOut( hDC, 477, 39, "H", 1 );
		return;
	}

	void MDU::Tapes_Invalid( oapi::Sketchpad2* skp )
	{
		skp->SetFont( skpSSVAFont_h11w9 );
		skp->SetPen( skpRedPen );
		skp->SetBrush( skpBlackBrush );
		skp->Rectangle( 13, 55, 59, 269 );
		skp->Rectangle( 13, 151, 59, 176 );
		skp->Rectangle( 13, 279, 59, 304 );

		skp->Rectangle( 68, 55, 114, 269 );
		static const oapi::IVECTOR2 poly[5] = {{111,163},{104,176},{64,176},{64,151},{104,151}};// start at tip moving cw
		skp->Polygon( poly, 5 );

		skp->Rectangle( 394, 55, 440, 269 );
		skp->Rectangle( 394, 151, 440, 176 );

		skp->Rectangle( 459, 55, 505, 269 );
		skp->Rectangle( 459, 151, 505, 176 );

		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Text( 17, 40, "M/V", 3 );
		skp->Text( 17, 310, "KEAS", 4 );

		char alpha[4];
		sprintf_s( alpha, 4, "%c", 254 );
		skp->Text( 82, 40, alpha, 1 );

		skp->Text( 411, 40, "H", 1 );
		skp->Pixel( 481, 37, CR_LIGHT_GRAY );
		skp->Text( 477, 40, "H", 1 );
		return;
	}

	void MDU::ADI_STATIC( HDC hDC )
	{
		SelectObject( hDC, gdiSSVBFont_h12w7 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		TextOut( hDC, 349, 14, "R", 1 );
		TextOut( hDC, 349, 29, "P", 1 );
		TextOut( hDC, 349, 44, "Y", 1 );

		SelectObject( hDC, gdiWhitePen );
		::Ellipse( hDC, 122, 48, 356, 282 );

		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiLightGrayBrush );
		POINT diamond[4];
		diamond[0].x = 239;
		diamond[0].y = 53;
		diamond[1].x = 244;
		diamond[1].y = 62;
		diamond[2].x = 239;
		diamond[2].y = 71;
		diamond[3].x = 234;
		diamond[3].y = 62;
		Polygon( hDC, diamond, 4 );// top
		//diamond[0].x = 239;
		diamond[0].y = 259;
		//diamond[1].x = 244;
		diamond[1].y = 268;
		//diamond[2].x = 239;
		diamond[2].y = 277;
		//diamond[3].x = 234;
		diamond[3].y = 268;
		Polygon( hDC, diamond, 4 );// bottom
		diamond[0].x = 342;
		diamond[0].y = 160;
		diamond[1].x = 351;
		diamond[1].y = 165;
		diamond[2].x = 342;
		diamond[2].y = 170;
		diamond[3].x = 333;
		diamond[3].y = 165;
		Polygon( hDC, diamond, 4 );// right
		diamond[0].x = 136;
		//diamond[0].y = 160;
		diamond[1].x = 145;
		//diamond[1].y = 165;
		diamond[2].x = 136;
		//diamond[2].y = 170;
		diamond[3].x = 127;
		//diamond[3].y = 165;
		Polygon( hDC, diamond, 4 );// left

		// rate scales
		// top scale
		MoveToEx( hDC, 154, 34, NULL );
		LineTo( hDC, 324, 34 );
		MoveToEx( hDC, 154, 33, NULL );
		LineTo( hDC, 154, 44 );
		MoveToEx( hDC, 171, 33, NULL );
		LineTo( hDC, 171, 41 );
		MoveToEx( hDC, 188, 33, NULL );
		LineTo( hDC, 188, 41 );
		MoveToEx( hDC, 205, 33, NULL );
		LineTo( hDC, 205, 41 );
		MoveToEx( hDC, 222, 33, NULL );
		LineTo( hDC, 222, 41 );
		MoveToEx( hDC, 239, 33, NULL );
		LineTo( hDC, 239, 44 );
		MoveToEx( hDC, 256, 33, NULL );
		LineTo( hDC, 256, 41 );
		MoveToEx( hDC, 273, 33, NULL );
		LineTo( hDC, 273, 41 );
		MoveToEx( hDC, 290, 33, NULL );
		LineTo( hDC, 290, 41 );
		MoveToEx( hDC, 307, 33, NULL );
		LineTo( hDC, 307, 41 );
		MoveToEx( hDC, 324, 33, NULL );
		LineTo( hDC, 324, 44 );

		// side scale
		MoveToEx( hDC, 370, 80, NULL );
		LineTo( hDC, 370, 250 );
		MoveToEx( hDC, 370, 80, NULL );
		LineTo( hDC, 359, 80 );
		MoveToEx( hDC, 370, 97, NULL );
		LineTo( hDC, 362, 97 );
		MoveToEx( hDC, 370, 114, NULL );
		LineTo( hDC, 362, 114 );
		MoveToEx( hDC, 370, 131, NULL );
		LineTo( hDC, 362, 131 );
		MoveToEx( hDC, 370, 148, NULL );
		LineTo( hDC, 362, 148 );
		MoveToEx( hDC, 370, 165, NULL );
		LineTo( hDC, 359, 165 );
		MoveToEx( hDC, 370, 182, NULL );
		LineTo( hDC, 362, 182 );
		MoveToEx( hDC, 370, 199, NULL );
		LineTo( hDC, 362, 199 );
		MoveToEx( hDC, 370, 216, NULL );
		LineTo( hDC, 362, 216 );
		MoveToEx( hDC, 370, 233, NULL );
		LineTo( hDC, 362, 233 );
		MoveToEx( hDC, 370, 250, NULL );
		LineTo( hDC, 359, 250 );

		// bottom scale
		MoveToEx( hDC, 154, 296, NULL );
		LineTo( hDC, 324, 296 );
		MoveToEx( hDC, 154, 296, NULL );
		LineTo( hDC, 154, 285 );
		MoveToEx( hDC, 171, 296, NULL );
		LineTo( hDC, 171, 288 );
		MoveToEx( hDC, 188, 296, NULL );
		LineTo( hDC, 188, 288 );
		MoveToEx( hDC, 205, 296, NULL );
		LineTo( hDC, 205, 288 );
		MoveToEx( hDC, 222, 296, NULL );
		LineTo( hDC, 222, 288 );
		MoveToEx( hDC, 239, 296, NULL );
		LineTo( hDC, 239, 285 );
		MoveToEx( hDC, 256, 296, NULL );
		LineTo( hDC, 256, 288 );
		MoveToEx( hDC, 273, 296, NULL );
		LineTo( hDC, 273, 288 );
		MoveToEx( hDC, 290, 296, NULL );
		LineTo( hDC, 290, 288 );
		MoveToEx( hDC, 307, 296, NULL );
		LineTo( hDC, 307, 288 );
		MoveToEx( hDC, 324, 296, NULL );
		LineTo( hDC, 324, 285 );

		// roll lines
		MoveToEx( hDC, 230, 65, NULL );// 5º/185º
		LineTo( hDC, 248, 265 );
		MoveToEx( hDC, 222, 67, NULL );// 10º/190º
		LineTo( hDC, 256, 263 );
		MoveToEx( hDC, 213, 68, NULL );// 15º/195º
		LineTo( hDC, 265, 262 );
		MoveToEx( hDC, 205, 71, NULL );// 20º/200º
		LineTo( hDC, 273, 259 );
		MoveToEx( hDC, 197, 74, NULL );// 25º/205º
		LineTo( hDC, 281, 256 );

		MoveToEx( hDC, 182, 83, NULL );// 35º/215º
		LineTo( hDC, 296, 247 );
		MoveToEx( hDC, 175, 88, NULL );// 40º/220º
		LineTo( hDC, 303, 242 );
		MoveToEx( hDC, 168, 94, NULL );// 45º/225º
		LineTo( hDC, 310, 236 );
		MoveToEx( hDC, 162, 101, NULL );// 50º/230º
		LineTo( hDC, 316, 229 );
		MoveToEx( hDC, 157, 108, NULL );// 55º/235º
		LineTo( hDC, 321, 222 );

		MoveToEx( hDC, 148, 123, NULL );// 65º/245º
		LineTo( hDC, 330, 207 );
		MoveToEx( hDC, 145, 131, NULL );// 70º/250º
		LineTo( hDC, 333, 199 );
		MoveToEx( hDC, 142, 139, NULL );// 75º/255º
		LineTo( hDC, 336, 191 );
		MoveToEx( hDC, 141, 148, NULL );// 80º/260º
		LineTo( hDC, 337, 182 );
		MoveToEx( hDC, 139, 156, NULL );// 85º/265º
		LineTo( hDC, 339, 174 );

		MoveToEx( hDC, 139, 174, NULL );// 95º/275º
		LineTo( hDC, 339, 156 );
		MoveToEx( hDC, 141, 182, NULL );// 100º/280º
		LineTo( hDC, 337, 148 );
		MoveToEx( hDC, 142, 191, NULL );// 105º/285º
		LineTo( hDC, 336, 139 );
		MoveToEx( hDC, 145, 199, NULL );// 110º/290º
		LineTo( hDC, 333, 131 );
		MoveToEx( hDC, 148, 207, NULL );// 115º/295º
		LineTo( hDC, 330, 123 );

		MoveToEx( hDC, 157, 222, NULL );// 125º/305º
		LineTo( hDC, 321, 108 );
		MoveToEx( hDC, 162, 229, NULL );// 130º/310º
		LineTo( hDC, 316, 101 );
		MoveToEx( hDC, 168, 236, NULL );// 135º/315º
		LineTo( hDC, 310, 94 );
		MoveToEx( hDC, 175, 242, NULL );// 140º/320º
		LineTo( hDC, 303, 88 );
		MoveToEx( hDC, 182, 247, NULL );// 145º/325º
		LineTo( hDC, 296, 83 );

		MoveToEx( hDC, 197, 256, NULL );// 155º/335º
		LineTo( hDC, 281, 74 );
		MoveToEx( hDC, 205, 259, NULL );// 160º/340º
		LineTo( hDC, 273, 71 );
		MoveToEx( hDC, 213, 262, NULL );// 165º/345º
		LineTo( hDC, 265, 68 );
		MoveToEx( hDC, 222, 263, NULL );// 170º/350º
		LineTo( hDC, 256, 67 );
		MoveToEx( hDC, 230, 265, NULL );// 175º/355º
		LineTo( hDC, 248, 65 );
		SelectObject( hDC, gdiLightGrayThickPen );
		MoveToEx( hDC, 187, 75, NULL );// 30º/210º
		LineTo( hDC, 291, 255 );
		MoveToEx( hDC, 149, 113, NULL );// 60º/240º
		LineTo( hDC, 329, 217 );
		MoveToEx( hDC, 149, 217, NULL );// 120º/300º
		LineTo( hDC, 329, 113 );
		MoveToEx( hDC, 187, 255, NULL );// 150º/330º
		LineTo( hDC, 291, 75 );

		// cover center for ADI SRCPAINT
		SelectObject( hDC, GetStockObject( BLACK_BRUSH ) );
		SelectObject( hDC, GetStockObject( BLACK_PEN ) );
		::Ellipse( hDC, 144, 70, 334, 260 );

		TextOut( hDC, 294, 70, "33", 2 );
		TextOut( hDC, 323, 99, "30", 2 );
		TextOut( hDC, 323, 217, "24", 2 );
		TextOut( hDC, 294, 247, "21", 2 );
		TextOut( hDC, 171, 247, "15", 2 );
		TextOut( hDC, 142, 217, "12", 2 );
		TextOut( hDC, 142, 99, "06", 2 );
		TextOut( hDC, 171, 70, "03", 2 );

		// att needles
		// top scale
		SelectObject( hDC, gdiMagentaPen );
		SelectObject( hDC, gdiMagentaBrush );
		Arc( hDC, 129, 55, 349, 275, 286, 66, 192, 66 );
		MoveToEx( hDC, 192, 66, NULL );
		LineTo( hDC, 192, 72 );
		MoveToEx( hDC, 201, 62, NULL );
		LineTo( hDC, 201, 68 );
		MoveToEx( hDC, 211, 59, NULL );
		LineTo( hDC, 211, 65 );
		MoveToEx( hDC, 220, 57, NULL );
		LineTo( hDC, 220, 63 );
		MoveToEx( hDC, 230, 55, NULL );
		LineTo( hDC, 230, 61 );
		MoveToEx( hDC, 239, 55, NULL );
		LineTo( hDC, 239, 61 );
		MoveToEx( hDC, 248, 55, NULL );
		LineTo( hDC, 248, 61 );
		MoveToEx( hDC, 258, 57, NULL );
		LineTo( hDC, 258, 63 );
		MoveToEx( hDC, 267, 59, NULL );
		LineTo( hDC, 267, 65 );
		MoveToEx( hDC, 277, 62, NULL );
		LineTo( hDC, 277, 68 );
		MoveToEx( hDC, 286, 66, NULL );
		LineTo( hDC, 286, 72 );

		// side scale
		Arc( hDC, 129, 55, 349, 275, 338, 212, 338, 118 );
		MoveToEx( hDC, 338, 118, NULL );
		LineTo( hDC, 332, 118 );
		MoveToEx( hDC, 342, 127, NULL );
		LineTo( hDC, 336, 127 );
		MoveToEx( hDC, 345, 137, NULL );
		LineTo( hDC, 339, 137 );
		MoveToEx( hDC, 347, 146, NULL );
		LineTo( hDC, 341, 146 );
		MoveToEx( hDC, 349, 156, NULL );
		LineTo( hDC, 343, 156 );
		MoveToEx( hDC, 349, 165, NULL );
		LineTo( hDC, 343, 165 );
		MoveToEx( hDC, 349, 174, NULL );
		LineTo( hDC, 343, 174 );
		MoveToEx( hDC, 347, 184, NULL );
		LineTo( hDC, 341, 184 );
		MoveToEx( hDC, 345, 193, NULL );
		LineTo( hDC, 339, 193 );
		MoveToEx( hDC, 342, 203, NULL );
		LineTo( hDC, 336, 203 );
		MoveToEx( hDC, 338, 212, NULL );
		LineTo( hDC, 332, 212 );

		// bottom scale
		Arc( hDC, 129, 55, 349, 275, 192, 264, 286, 264 );
		MoveToEx( hDC, 192, 264, NULL );
		LineTo( hDC, 192, 258 );
		MoveToEx( hDC, 201, 268, NULL );
		LineTo( hDC, 201, 262 );
		MoveToEx( hDC, 211, 271, NULL );
		LineTo( hDC, 211, 265 );
		MoveToEx( hDC, 220, 273, NULL );
		LineTo( hDC, 220, 267 );
		MoveToEx( hDC, 230, 275, NULL );
		LineTo( hDC, 230, 269 );
		MoveToEx( hDC, 239, 275, NULL );
		LineTo( hDC, 239, 269 );
		MoveToEx( hDC, 248, 275, NULL );
		LineTo( hDC, 249, 269 );
		MoveToEx( hDC, 258, 273, NULL );
		LineTo( hDC, 258, 267 );
		MoveToEx( hDC, 267, 271, NULL );
		LineTo( hDC, 267, 265 );
		MoveToEx( hDC, 277, 268, NULL );
		LineTo( hDC, 277, 262 );
		MoveToEx( hDC, 286, 264, NULL );
		LineTo( hDC, 286, 258 );
		return;
	}

	void MDU::ADI_STATIC( oapi::Sketchpad2* skp )
	{
		skp->SetFont( skpSSVBFont_h12w7 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Text( 349, 14, "R", 1 );
		skp->Text( 349, 29, "P", 1 );
		skp->Text( 349, 44, "Y", 1 );

		skp->SetPen( skpWhitePen );
		skp->Ellipse( 122, 48, 356, 282 );

		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpLightGrayBrush );
		oapi::IVECTOR2 diamond[4];
		diamond[0].x = 239;
		diamond[0].y = 53;
		diamond[1].x = 244;
		diamond[1].y = 62;
		diamond[2].x = 239;
		diamond[2].y = 71;
		diamond[3].x = 234;
		diamond[3].y = 62;
		skp->Polygon( diamond, 4 );// top
		//diamond[0].x = 239;
		diamond[0].y = 259;
		//diamond[1].x = 244;
		diamond[1].y = 268;
		//diamond[2].x = 239;
		diamond[2].y = 277;
		//diamond[3].x = 234;
		diamond[3].y = 268;
		skp->Polygon( diamond, 4 );// bottom
		diamond[0].x = 342;
		diamond[0].y = 160;
		diamond[1].x = 351;
		diamond[1].y = 165;
		diamond[2].x = 342;
		diamond[2].y = 170;
		diamond[3].x = 333;
		diamond[3].y = 165;
		skp->Polygon( diamond, 4 );// right
		diamond[0].x = 136;
		//diamond[0].y = 160;
		diamond[1].x = 145;
		//diamond[1].y = 165;
		diamond[2].x = 136;
		//diamond[2].y = 170;
		diamond[3].x = 127;
		//diamond[3].y = 165;
		skp->Polygon( diamond, 4 );// left

		// rate scales
		// top scale
		skp->SetPen( skpLightGrayPen );
		skp->Line( 154, 34, 324, 34 );
		skp->Line( 154, 33, 154, 44 );
		skp->Line( 171, 33, 171, 41 );
		skp->Line( 188, 33, 188, 41 );
		skp->Line( 205, 33, 205, 41 );
		skp->Line( 222, 33, 222, 41 );
		skp->Line( 239, 33, 239, 44 );
		skp->Line( 256, 33, 256, 41 );
		skp->Line( 273, 33, 273, 41 );
		skp->Line( 290, 33, 290, 41 );
		skp->Line( 307, 33, 307, 41 );
		skp->Line( 324, 33, 324, 44 );

		// side scale
		skp->Line( 370, 80, 370, 250 );
		skp->Line( 370, 80, 359, 80 );
		skp->Line( 370, 97, 362, 97 );
		skp->Line( 370, 114, 362, 114 );
		skp->Line( 370, 131, 362, 131 );
		skp->Line( 370, 148, 362, 148 );
		skp->Line( 370, 165, 359, 165 );
		skp->Line( 370, 182, 362, 182 );
		skp->Line( 370, 199, 362, 199 );
		skp->Line( 370, 216, 362, 216 );
		skp->Line( 370, 233, 362, 233 );
		skp->Line( 370, 250, 359, 250 );

		// bottom scale
		skp->Line( 154, 296, 324, 296 );
		skp->Line( 154, 296, 154, 285 );
		skp->Line( 171, 296, 171, 288 );
		skp->Line( 188, 296, 188, 288 );
		skp->Line( 205, 296, 205, 288 );
		skp->Line( 222, 296, 222, 288 );
		skp->Line( 239, 296, 239, 285 );
		skp->Line( 256, 296, 256, 288 );
		skp->Line( 273, 296, 273, 288 );
		skp->Line( 290, 296, 290, 288 );
		skp->Line( 307, 296, 307, 288 );
		skp->Line( 324, 296, 324, 285 );

		// roll lines
		skp->Line( 230, 65, 248, 265 );// 5º/185º
		skp->Line( 222, 67, 256, 263 );// 10º/190º
		skp->Line( 213, 68, 265, 262 );// 15º/195º
		skp->Line( 205, 71, 273, 259 );// 20º/200º
		skp->Line( 197, 74, 281, 256 );// 25º/205º

		skp->Line( 182, 83, 296, 247 );// 35º/215º
		skp->Line( 175, 88, 303, 242 );// 40º/220º
		skp->Line( 168, 94, 310, 236 );// 45º/225º
		skp->Line( 162, 101, 316, 229 );// 50º/230º
		skp->Line( 157, 108, 321, 222 );// 55º/235º

		skp->Line( 148, 123, 330, 207 );// 65º/245º
		skp->Line( 145, 131, 333, 199 );// 70º/250º
		skp->Line( 142, 139, 336, 191 );// 75º/255º
		skp->Line( 141, 148, 337, 182 );// 80º/260º
		skp->Line( 139, 156, 339, 174 );// 85º/265º

		skp->Line( 139, 174, 339, 156 );// 95º/275º
		skp->Line( 141, 182, 337, 148 );// 100º/280º
		skp->Line( 142, 191, 336, 139 );// 105º/285º
		skp->Line( 145, 199, 333, 131 );// 110º/290º
		skp->Line( 148, 207, 330, 123 );// 115º/295º

		skp->Line( 157, 222, 321, 108 );// 125º/305º
		skp->Line( 162, 229, 316, 101 );// 130º/310º
		skp->Line( 168, 236, 310, 94 );// 135º/315º
		skp->Line( 175, 242, 303, 88 );// 140º/320º
		skp->Line( 182, 247, 296, 83 );// 145º/325º

		skp->Line( 197, 256, 281, 74 );// 155º/335º
		skp->Line( 205, 259, 273, 71 );// 160º/340º
		skp->Line( 213, 262, 265, 68 );// 165º/345º
		skp->Line( 222, 263, 256, 67 );// 170º/350º
		skp->Line( 230, 265, 248, 65 );// 175º/355º
		skp->SetPen( skpLightGrayThickPen );
		skp->Line( 187, 75, 291, 255 );// 30º/210º
		skp->Line( 149, 113, 329, 217 );// 60º/240º
		skp->Line( 149, 217, 329, 113 );// 120º/300º
		skp->Line( 187, 255, 291, 75 );// 150º/330º

		// cover center for ADI SRCPAINT
		skp->SetBrush( _skpBlackBrush );
		skp->SetPen( _skpBlackPen );
		skp->Ellipse( 144, 70, 334, 260 );

		skp->Text( 294, 70, "33", 2 );
		skp->Text( 323, 99, "30", 2 );
		skp->Text( 323, 217, "24", 2 );
		skp->Text( 294, 247, "21", 2 );
		skp->Text( 171, 247, "15", 2 );
		skp->Text( 142, 217, "12", 2 );
		skp->Text( 142, 99, "06", 2 );
		skp->Text( 171, 70, "03", 2 );

		// att needles
		// top scale
		skp->SetPen( skpMagentaPen );
		skp->SetBrush( skpMagentaBrush );
		//Arc( 129, 55, 349, 275, 286, 66, 192, 66 );
		// HACK makeshift arc
		skp->Line( 192, 66, 201, 62 );
		skp->Line( 201, 62, 211, 59 );
		skp->Line( 211, 59, 220, 57 );
		skp->Line( 220, 57, 230, 55 );
		skp->Line( 230, 55, 239, 55 );
		skp->Line( 239, 55, 248, 55 );
		skp->Line( 248, 55, 258, 57 );
		skp->Line( 258, 57, 267, 59 );
		skp->Line( 267, 59, 277, 62 );
		skp->Line( 277, 62, 286, 66 );

		skp->Line( 192, 66, 192, 72 );
		skp->Line( 201, 62, 201, 68 );
		skp->Line( 211, 59, 211, 65 );
		skp->Line( 220, 57, 220, 63 );
		skp->Line( 230, 55, 230, 61 );
		skp->Line( 239, 55, 239, 61 );
		skp->Line( 248, 55, 248, 61 );
		skp->Line( 258, 57, 258, 63 );
		skp->Line( 267, 59, 267, 65 );
		skp->Line( 277, 62, 277, 68 );
		skp->Line( 286, 66, 286, 72 );

		// side scale
		//Arc( 129, 55, 349, 275, 338, 212, 338, 118 );
		// HACK makeshift arc
		skp->Line( 338, 118, 342, 127 );
		skp->Line( 342, 127, 345, 137 );
		skp->Line( 345, 137, 347, 146 );
		skp->Line( 347, 146, 349, 156 );
		skp->Line( 349, 156, 349, 165 );
		skp->Line( 349, 165, 349, 174 );
		skp->Line( 349, 174, 347, 184 );
		skp->Line( 347, 184, 345, 193 );
		skp->Line( 345, 193, 342, 203 );
		skp->Line( 342, 203, 338, 212 );

		skp->Line( 338, 118, 332, 118 );
		skp->Line( 342, 127, 336, 127 );
		skp->Line( 345, 137, 339, 137 );
		skp->Line( 347, 146, 341, 146 );
		skp->Line( 349, 156, 343, 156 );
		skp->Line( 349, 165, 343, 165 );
		skp->Line( 349, 174, 343, 174 );
		skp->Line( 347, 184, 341, 184 );
		skp->Line( 345, 193, 339, 193 );
		skp->Line( 342, 203, 336, 203 );
		skp->Line( 338, 212, 332, 212 );

		// bottom scale
		//Arc( 129, 55, 349, 275, 192, 264, 286, 264 );
		// HACK makeshift arc
		skp->Line( 192, 264, 201, 268 );
		skp->Line( 201, 268, 211, 271 );
		skp->Line( 211, 271, 220, 273 );
		skp->Line( 220, 273, 230, 275 );
		skp->Line( 230, 275, 239, 275 );
		skp->Line( 239, 275, 248, 275 );
		skp->Line( 248, 275, 258, 273 );
		skp->Line( 258, 273, 267, 271 );
		skp->Line( 267, 271, 277, 268 );
		skp->Line( 277, 268, 286, 264 );

		skp->Line( 192, 264, 192, 258 );
		skp->Line( 201, 268, 201, 262 );
		skp->Line( 211, 271, 211, 265 );
		skp->Line( 220, 273, 220, 267 );
		skp->Line( 230, 275, 230, 269 );
		skp->Line( 239, 275, 239, 269 );
		skp->Line( 248, 275, 249, 269 );
		skp->Line( 258, 273, 258, 267 );
		skp->Line( 267, 271, 267, 265 );
		skp->Line( 277, 268, 277, 262 );
		skp->Line( 286, 264, 286, 258 );
		return;
	}

	void MDU::ADI( HDC hDC, double pitch, double roll, double yaw )
	{
		// center (239,165) r = 117
		// view r = 95, ball r = 95 * sqrt( 2 )
		// 90º pitch/yaw "FOV"

		// apply roll
		XFORM WTroll;
		WTroll.eM11 = (FLOAT)cos( roll * RAD );
		WTroll.eM12 = (FLOAT)(-sin( roll * RAD ));
		WTroll.eM21 = -WTroll.eM12;
		WTroll.eM22 = WTroll.eM11;
		WTroll.eDx = (FLOAT)(96 * (1 - WTroll.eM11 - WTroll.eM21));
		WTroll.eDy = (FLOAT)(96 * (1 - WTroll.eM11 + WTroll.eM21));
		SetGraphicsMode( hDC_ADI, GM_ADVANCED );
		SetWorldTransform( hDC_ADI, &WTroll );

		if (pitch > 180) pitch -= 360;// TODO get rid of this

		// 0º pitch line/labels
		double sinpitch = sin( pitch * RAD );
		double cospitch = cos( pitch * RAD );
		int hP;
		double hP2;
		SetTextColor( hDC_ADI, CR_BLACK );
		SetBkColor( hDC_ADI, CR_WHITE );
		if (fabs( pitch ) <= 45)
		{
			hP = Round( 134.35 * sinpitch );
			if (pitch < 0)
			{
				SelectObject( hDC_ADI, gdiWhiteBrush );
				SelectObject( hDC_ADI, gdiWhitePen );
				Rectangle( hDC_ADI, 0, 0, 190, 95 );
				SelectObject( hDC_ADI, gdiDarkGrayBrush );
				SelectObject( hDC_ADI, gdiDarkGrayPen );
				Chord( hDC_ADI, -37, 95 - hP, 231, 95 + hP, 231, 95, -37, 95 );
				Rectangle( hDC_ADI, 0, 95, 190, 190 );
			}
			else
			{
				SelectObject( hDC_ADI, gdiDarkGrayBrush );
				SelectObject( hDC_ADI, gdiDarkGrayPen );
				Rectangle( hDC_ADI, 0, 95, 190, 190 );
				SelectObject( hDC_ADI, gdiWhiteBrush );
				SelectObject( hDC_ADI, gdiWhitePen );
				Chord( hDC_ADI, -37, 95 - hP, 231, 95 + hP, -37, 95, 231, 95 );
				Rectangle( hDC_ADI, 0, 0, 190, 95 );
			}
			hP = 93 + Round( 129.772414 * sinpitch );
			TextOut( hDC_ADI, 60, hP, "0", 1 );
			TextOut( hDC_ADI, 130, hP, "0", 1 );
		}
		else if (pitch > 0)
		{
			SelectObject( hDC_ADI, gdiWhiteBrush );
			Rectangle( hDC_ADI, -2, -2, 194, 194 );
		}
		else
		{
			SelectObject( hDC_ADI, gdiDarkGrayBrush );
			Rectangle( hDC_ADI, -2, -2, 194, 194 );
		}

		// pitch lines/labels for +30º/+60º/+90º/+120º/+150º
		SelectObject( hDC_ADI, gdiBlackPen );
		// +30º
		if (fabs( pitch - 30 ) <= 45)
		{
			hP2 = sinpitch * 116.350763 - cospitch * 67.175144;//hP = 69.296 * sin( (pitch - 30) * RAD );
			hP = Round( hP2 );
			if (pitch < 30) Arc( hDC_ADI, -37, 95 - hP, 231, 95 + hP, 231, 95, -37, 95 );
			else Arc( hDC_ADI, -37, 95 - hP, 231, 95 + hP, -37, 95, 231, 95 );
			hP = 89 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI, 60, hP, "3", 1 );
			TextOut( hDC_ADI, 130, hP, "3", 1 );
		}
		// +60º
		if (fabs( pitch - 60 ) <= 45)
		{
			hP2 = sinpitch * 67.175144 - cospitch * 116.350763;
			hP = Round( hP2 );
			if (pitch < 60) Arc( hDC_ADI, -37, 95 - hP, 231, 95 + hP, 231, 95, -37, 95 );
			else Arc( hDC_ADI, -37, 95 - hP, 231, 95 + hP, -37, 95, 231, 95 );
			hP = 89 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI, 60, hP, "6", 1 );
			TextOut( hDC_ADI, 130, hP, "6", 1 );
		}
		// +90º
		if (fabs( pitch - 90 ) <= 45)
		{
			hP2 = 134.350289 * (-cospitch);
			hP = Round( hP2 );
			if (pitch < 90) Arc( hDC_ADI, -37, 95 - hP, 231, 95 + hP, 231, 95, -37, 95 );
			else Arc( hDC_ADI, -37, 95 - hP, 231, 95 + hP, -37, 95, 231, 95 );
			hP = 89 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI, 60, hP, "9", 1 );
			TextOut( hDC_ADI, 130, hP, "9", 1 );
		}
		// +120º
		if (fabs( pitch - 120 ) <= 45)
		{
			hP2 = (-sinpitch) * 67.175144 - cospitch * 116.350763;
			hP = Round( hP2 );
			if (pitch < 120) Arc( hDC_ADI, -37, 95 - hP, 231, 95 + hP, 231, 95, -37, 95 );
			else Arc( hDC_ADI, -37, 95 - hP, 231, 95 + hP, -37, 95, 231, 95 );
			hP = 89 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI, 58, hP, "12", 2 );
			TextOut( hDC_ADI, 128, hP, "12", 2 );
		}
		// +150º
		if (fabs( pitch - 150 ) <= 45)
		{
			hP2 = (-sinpitch) * 116.350763 - cospitch * 67.175144;
			hP = Round( hP2 );
			if (pitch < 150) Arc( hDC_ADI, -37, 95 - hP, 231, 95 + hP, 231, 95, -37, 95 );
			else Arc( hDC_ADI, -37, 95 - hP, 231, 95 + hP, -37, 95, 231, 95 );
			hP = 89 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI, 58, hP, "15", 2 );
			TextOut( hDC_ADI, 128, hP, "15", 2 );
		}

		// pitch lines/labels for -30º/-60º/-90º/-120º/-150º
		SelectObject( hDC_ADI, gdiWhitePen );
		SetTextColor( hDC_ADI, CR_WHITE );
		SetBkColor( hDC_ADI, CR_DARK_GRAY );
		// -30º
		if (fabs( pitch + 30 ) <= 45)
		{
			hP2 = sinpitch * 116.350763 + cospitch * 67.175144;
			hP = Round( hP2 );
			if (pitch < -30) Arc( hDC_ADI, -37, 95 - hP, 231, 95 + hP, 231, 95, -37, 95 );
			else Arc( hDC_ADI, -37, 95 - hP, 231, 95 + hP, -37, 95, 231, 95 );
			hP = 89 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI, 58, hP, "33", 2 );
			TextOut( hDC_ADI, 128, hP, "33", 2 );
		}
		// -60º
		if (fabs( pitch + 60 ) <= 45)
		{
			hP2 = sinpitch * 67.175144 + cospitch * 116.350763;
			hP = Round( hP2 );
			if (pitch < -60) Arc( hDC_ADI, -37, 95 - hP, 231, 95 + hP, 231, 95, -37, 95 );
			else Arc( hDC_ADI, -37, 95 - hP, 231, 95 + hP, -37, 95, 231, 95 );
			hP = 89 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI, 58, hP, "30", 2 );
			TextOut( hDC_ADI, 128, hP, "30", 2 );
		}
		// -90º
		if (fabs( pitch + 90 ) <= 45)
		{
			hP2 = 134.350289 * cospitch;
			hP = Round( hP2 );
			if (pitch < -90) Arc( hDC_ADI, -37, 95 - hP, 231, 95 + hP, 231, 95, -37, 95 );
			else Arc( hDC_ADI, -37, 95 - hP, 231, 95 + hP, -37, 95, 231, 95 );
			hP = 89 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI, 58, hP, "27", 2 );
			TextOut( hDC_ADI, 128, hP, "27", 2 );
		}
		// -120º
		if (fabs( pitch + 120 ) <= 45)
		{
			hP2 = (-sinpitch) * 67.175144 + cospitch * 116.350763;
			hP = Round( hP2 );
			if (pitch < -120) Arc( hDC_ADI, -37, 95 - hP, 231, 95 + hP, 231, 95, -37, 95 );
			else Arc( hDC_ADI, -37, 95 - hP, 231, 95 + hP, -37, 95, 231, 95 );
			hP = 89 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI, 58, hP, "24", 2 );
			TextOut( hDC_ADI, 128, hP, "24", 2 );
		}
		// -150º
		if (fabs( pitch + 150 ) <= 45)
		{
			hP2 = (-sinpitch) * 116.350763 + cospitch * 67.175144;
			hP = Round( hP2 );
			if (pitch < -150) Arc( hDC_ADI, -37, 95 - hP, 231, 95 + hP, 231, 95, -37, 95 );
			else Arc( hDC_ADI, -37, 95 - hP, 231, 95 + hP, -37, 95, 231, 95 );
			hP = 89 + Round( hP2 * 0.965926 );
			TextOut( hDC_ADI, 58, hP, "21", 2 );
			TextOut( hDC_ADI, 128, hP, "21", 2 );
		}

		// TODO yaw
		// HACK
		// "central plane"
		SelectObject( hDC_ADI, gdiWhiteBrush );
		SelectObject( hDC_ADI, gdiBlackPen );
		Rectangle( hDC_ADI, 92, 0, 98, 192 );
		MoveToEx( hDC_ADI, 95, 0, NULL );
		LineTo( hDC_ADI, 95, 190 );

		SelectObject( hDC_ADI, gdiBlackPen );
		// yaw line 30º (above horizon)
		MoveToEx( hDC_ADI, 163, 0, NULL );
		LineTo( hDC_ADI, 163, 97 + Round( 116.349982 * sinpitch ) );
		// yaw line 330º (above horizon)
		MoveToEx( hDC_ADI, 27, 0, NULL );
		LineTo( hDC_ADI, 27, 97 + Round( 116.349982 * sinpitch ) );
		SelectObject( hDC_ADI, gdiWhitePen );
		// yaw line 30º (below horizon)
		MoveToEx( hDC_ADI, 163, 190, NULL );
		LineTo( hDC_ADI, 163, 97 + Round( 116.349982 * sinpitch ) );
		// yaw line 330º (below horizon)
		MoveToEx( hDC_ADI, 27, 190, NULL );
		LineTo( hDC_ADI, 27, 97 + Round( 116.349982 * sinpitch ) );

		// TODO yaw labels

		// roll triangle
		SelectObject( hDC_ADI, gdiLightGreenPen );
		SelectObject( hDC_ADI, gdiLightGreenBrush );
		POINT tri[3];
		tri[0].x = 95;
		tri[0].y = 1;
		tri[1].x = 90;
		tri[1].y = 11;
		tri[2].x = 100;
		tri[2].y = 11;
		Polygon( hDC_ADI, tri, 3 );

		// clean up
		ModifyWorldTransform( hDC_ADI, &WTroll, MWT_IDENTITY );
		SetGraphicsMode( hDC_ADI, GM_COMPATIBLE );

		// digital RPY
		if (pitch < 0) pitch += 360;// TODO get rid of this
		SetTextColor( hDC, CR_WHITE );
		char cbuf[8];
		sprintf_s( cbuf, 8, "%03.0f", roll );
		TextOut( hDC, 362, 14, cbuf, strlen( cbuf ) );
		sprintf_s( cbuf, 8, "%03.0f", pitch );
		TextOut( hDC, 362, 29, cbuf, strlen( cbuf ) );
		sprintf_s( cbuf, 8, "%03.0f", yaw );
		TextOut( hDC, 362, 44, cbuf, strlen( cbuf ) );

		// copy ball
		BitBlt( hDC_ADI, 0, 0, 192, 192, hDC_ADIMASK, 0, 0, SRCAND );
		BitBlt( hDC, 144, 70, 190, 190, hDC_ADI, 1, 1, SRCPAINT );

		// flight director
		SelectObject( hDC, gdiBlackPen );
		SelectObject( hDC, gdiLightGreenBrush );
		static const POINT fd[18] = {{203,163},{203,167},{223,167},{228,175},{236,181},{242,181},{250,175},{255,167},{275,167},{275,163},{251,163},{251,167},{248,173},{242,177},{236,177},{230,173},{227,167},{227,163}};
		Polygon( hDC, fd, 18 );
		// center marker
		SelectObject( hDC, gdiLightGreenPen );
		Rectangle( hDC, 238, 137, 240, 193 );
		Rectangle( hDC, 211, 164, 267, 166 );
		return;
	}

	void MDU::ADI( oapi::Sketchpad2* skp, double pitch, double roll, double yaw )
	{
		// center (239,165) r = 117
		// view r = 95, ball r = 95 * sqrt( 2 )
		// 90º pitch/yaw "FOV"

		// draw ball mesh
		FMATRIX4 mat;
		int H = 330;
		int W = 478;

		double croll = cos( roll * RAD );
		double sroll = sin( -roll * RAD );
		double cyaw = cos( yaw * RAD );
		double syaw = sin( yaw * RAD );
		double cpitch = cos( pitch * RAD );
		double spitch = sin( pitch * RAD );

		VECTOR3 xdir = _V( cyaw * croll, sroll, -croll * syaw );
		VECTOR3 zdir = _V( syaw * cpitch + sroll * cyaw * spitch, -croll * spitch, cpitch * cyaw - syaw * sroll * spitch );
		STS()->D3D9()->WorldMatrix( &mat, _V( W / 2, H / 2, W + 126 ), xdir, zdir, 1.3435 );

		skp->SetWorldTransform( &mat );
		skp->SetPen( skpWhitePen );
		skp->DrawSketchMesh( hADIball, 0, 0 );
		skp->SetWorldTransform();

		// roll triangle
		skp->SetPen( skpLightGreenPen );
		skp->SetBrush( skpLightGreenBrush );
		oapi::IVECTOR2 tri[3];
		tri[0].x = (long)(239 + 95 * sroll);
		tri[0].y = (long)(165 - 95 * croll);
		tri[1].x = (long)(239 - 5 * croll + 84 * sroll);
		tri[1].y = (long)(165 - 5 * sroll - 84 * croll);
		tri[2].x = (long)(239 + 5 * croll + 84 * sroll);
		tri[2].y = (long)(165 + 5 * sroll - 84 * croll);
		skp->Polygon( tri, 3 );

		// digital RPY
		if (pitch < 0) pitch += 360;// TODO get rid of this
		skp->SetTextColor( CR_WHITE );
		char cbuf[8];
		sprintf_s( cbuf, 8, "%03.0f", roll );
		skp->Text( 362, 14, cbuf, strlen( cbuf ) );
		sprintf_s( cbuf, 8, "%03.0f", pitch );
		skp->Text( 362, 29, cbuf, strlen( cbuf ) );
		sprintf_s( cbuf, 8, "%03.0f", yaw );
		skp->Text( 362, 44, cbuf, strlen( cbuf ) );

		// flight director
		skp->SetPen( skpBlackPen );
		static const oapi::IVECTOR2 fd[18] = {{203,163},{203,167},{223,167},{228,175},{236,181},{242,181},{250,175},{255,167},{275,167},{275,163},{251,163},{251,167},{248,173},{242,177},{236,177},{230,173},{227,167},{227,163}};
		skp->Polygon( fd, 18 );
		// center marker
		skp->SetPen( skpLightGreenPen );
		skp->Rectangle( 238, 137, 240, 193 );
		skp->Rectangle( 211, 164, 267, 166 );
		return;
	}

	void MDU::ADI_RATE_A( HDC hDC, double pitch, double roll, double yaw, int adirate )
	{
		int pos_roll;
		int pos_pitch;
		int pos_yaw;

		SelectObject( hDC, gdiSSVBFont_h12w7 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		TextOut( hDC, 236, 18, "0", 1 );
		TextOut( hDC, 375, 159, "0", 1 );
		TextOut( hDC, 236, 298, "0", 1 );

		SetTextColor( hDC, CR_WHITE );
		SetTextAlign( hDC, TA_RIGHT );
		if (adirate == 1)
		{
			// ADI RATE MED
			TextOut( hDC, 151, 31, "5", 1 );
			TextOut( hDC, 151, 283, "5", 1 );

			SetTextAlign( hDC, TA_LEFT );
			//TextOut( hDC, 151, 31, "5", 1 );
			TextOut( hDC, 327, 31, "5", 1 );

			TextOut( hDC, 356, 65, "5", 1 );
			TextOut( hDC, 356, 251, "5", 1 );

			//TextOut( hDC, 151, 283, "5", 1 );
			TextOut( hDC, 327, 283, "5", 1 );

			if (roll > 5) pos_roll = 324;
			else if (roll < -5) pos_roll = 154;
			else pos_roll = 239 + Round( roll * 17 );

			if (pitch > 5) pos_pitch = 80;
			else if (pitch < -5) pos_pitch = 250;
			else pos_pitch = 165 - Round( pitch * 17 );

			if (yaw > 5) pos_yaw = 324;
			else if (yaw < -5) pos_yaw = 154;
			else pos_yaw = 239 + Round( yaw * 17 );
		}
		else if (adirate == 2)
		{
			// ADI RATE HIGH
			TextOut( hDC, 151, 31, "10", 2 );
			TextOut( hDC, 151, 283, "10", 2 );

			SetTextAlign( hDC, TA_LEFT );
			//TextOut( hDC, 151, 31, "10", 2 );
			TextOut( hDC, 327, 31, "10", 2 );

			TextOut( hDC, 356, 65, "10", 2 );
			TextOut( hDC, 356, 251, "10", 2 );

			//TextOut( hDC, 151, 283, "10", 2 );
			TextOut( hDC, 327, 283, "10", 2 );

			if (roll > 10) pos_roll = 324;
			else if (roll < -10) pos_roll = 154;
			else pos_roll = 239 + Round( roll * 8.5 );

			if (pitch > 10) pos_pitch = 80;
			else if (pitch < -10) pos_pitch = 250;
			else pos_pitch = 165 - Round( pitch * 8.5 );

			if (yaw > 10) pos_yaw = 324;
			else if (yaw < -10) pos_yaw = 154;
			else pos_yaw = 239 + Round( yaw * 8.5 );
		}
		else
		{
			// ADI RATE LOW
			TextOut( hDC, 151, 31, "1", 1 );
			TextOut( hDC, 151, 283, "1", 1 );

			SetTextAlign( hDC, TA_LEFT );
			//TextOut( hDC, 151, 31, "1", 1 );
			TextOut( hDC, 327, 31, "1", 1 );

			TextOut( hDC, 356, 65, "1", 1 );
			TextOut( hDC, 356, 251, "1", 1 );

			//TextOut( hDC, 151, 283, "1", 1 );
			TextOut( hDC, 327, 283, "1", 1 );

			if (roll > 1) pos_roll = 324;
			else if (roll < -1) pos_roll = 154;
			else pos_roll = 239 + Round( roll * 85 );

			if (pitch > 1) pos_pitch = 80;
			else if (pitch < -1) pos_pitch = 250;
			else pos_pitch = 165 - Round( pitch * 85 );

			if (yaw > 1) pos_yaw = 324;
			else if (yaw < -1) pos_yaw = 154;
			else pos_yaw = 239 + Round( yaw * 85 );
		}

		// draw triangles
		SelectObject( hDC, gdiLightGreenPen );
		SelectObject( hDC, gdiLightGreenBrush );
		POINT tri[3];
		tri[0].x = pos_roll;
		tri[0].y = 34;
		tri[1].x = tri[0].x + 10;
		tri[1].y = 18;
		tri[2].x = tri[0].x - 10;
		tri[2].y = 18;
		Polygon( hDC, tri, 3 );

		tri[0].x = 370;
		tri[0].y = pos_pitch;
		tri[1].x = 386;
		tri[1].y = tri[0].y - 10;
		tri[2].x = 386;
		tri[2].y = tri[0].y + 10;
		Polygon( hDC, tri, 3 );

		tri[0].x = pos_yaw;
		tri[0].y = 296;
		tri[1].x = tri[0].x - 10;
		tri[1].y = 312;
		tri[2].x = tri[0].x + 10;
		tri[2].y = 312;
		Polygon( hDC, tri, 3 );
		return;
	}

	void MDU::ADI_RATE_A( oapi::Sketchpad2* skp, double pitch, double roll, double yaw, int adirate )
	{
		int pos_roll;
		int pos_pitch;
		int pos_yaw;

		skp->SetFont( skpSSVBFont_h12w7 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Text( 236, 18, "0", 1 );
		skp->Text( 375, 159, "0", 1 );
		skp->Text( 236, 298, "0", 1 );

		skp->SetTextColor( CR_WHITE );
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );
		if (adirate == 1)
		{
			// ADI RATE MED
			skp->Text( 151, 31, "5", 1 );
			skp->Text( 151, 283, "5", 1 );

			skp->SetTextAlign( oapi::Sketchpad::LEFT );
			//skp->Text( 151, 31, "5", 1 );
			skp->Text( 327, 31, "5", 1 );

			skp->Text( 356, 65, "5", 1 );
			skp->Text( 356, 251, "5", 1 );

			//skp->Text( 151, 283, "5", 1 );
			skp->Text( 327, 283, "5", 1 );

			if (roll > 5) pos_roll = 324;
			else if (roll < -5) pos_roll = 154;
			else pos_roll = 239 + Round( roll * 17 );

			if (pitch > 5) pos_pitch = 80;
			else if (pitch < -5) pos_pitch = 250;
			else pos_pitch = 165 - Round( pitch * 17 );

			if (yaw > 5) pos_yaw = 324;
			else if (yaw < -5) pos_yaw = 154;
			else pos_yaw = 239 + Round( yaw * 17 );
		}
		else if (adirate == 2)
		{
			// ADI RATE HIGH
			skp->Text( 151, 31, "10", 2 );
			skp->Text( 151, 283, "10", 2 );

			skp->SetTextAlign( oapi::Sketchpad::LEFT );
			//skp->Text( 151, 31, "10", 2 );
			skp->Text( 327, 31, "10", 2 );

			skp->Text( 356, 65, "10", 2 );
			skp->Text( 356, 251, "10", 2 );

			//skp->Text( 151, 283, "10", 2 );
			skp->Text( 327, 283, "10", 2 );

			if (roll > 10) pos_roll = 324;
			else if (roll < -10) pos_roll = 154;
			else pos_roll = 239 + Round( roll * 8.5 );

			if (pitch > 10) pos_pitch = 80;
			else if (pitch < -10) pos_pitch = 250;
			else pos_pitch = 165 - Round( pitch * 8.5 );

			if (yaw > 10) pos_yaw = 324;
			else if (yaw < -10) pos_yaw = 154;
			else pos_yaw = 239 + Round( yaw * 8.5 );
		}
		else
		{
			// ADI RATE LOW
			skp->Text( 151, 31, "1", 1 );
			skp->Text( 151, 283, "1", 1 );

			skp->SetTextAlign( oapi::Sketchpad::LEFT );
			//skp->Text( 151, 31, "1", 1 );
			skp->Text( 327, 31, "1", 1 );

			skp->Text( 356, 65, "1", 1 );
			skp->Text( 356, 251, "1", 1 );

			//skp->Text( 151, 283, "1", 1 );
			skp->Text( 327, 283, "1", 1 );

			if (roll > 1) pos_roll = 324;
			else if (roll < -1) pos_roll = 154;
			else pos_roll = 239 + Round( roll * 85 );

			if (pitch > 1) pos_pitch = 80;
			else if (pitch < -1) pos_pitch = 250;
			else pos_pitch = 165 - Round( pitch * 85 );

			if (yaw > 1) pos_yaw = 324;
			else if (yaw < -1) pos_yaw = 154;
			else pos_yaw = 239 + Round( yaw * 85 );
		}

		// draw triangles
		skp->SetPen( skpLightGreenPen );
		skp->SetBrush( skpLightGreenBrush );
		oapi::IVECTOR2 tri[3];
		tri[0].x = pos_roll;
		tri[0].y = 34;
		tri[1].x = tri[0].x + 10;
		tri[1].y = 18;
		tri[2].x = tri[0].x - 10;
		tri[2].y = 18;
		skp->Polygon( tri, 3 );

		tri[0].x = 370;
		tri[0].y = pos_pitch;
		tri[1].x = 386;
		tri[1].y = tri[0].y - 10;
		tri[2].x = 386;
		tri[2].y = tri[0].y + 10;
		skp->Polygon( tri, 3 );

		tri[0].x = pos_yaw;
		tri[0].y = 296;
		tri[1].x = tri[0].x - 10;
		tri[1].y = 312;
		tri[2].x = tri[0].x + 10;
		tri[2].y = 312;
		skp->Polygon( tri, 3 );
		return;
	}

	void MDU::ADI_RATE_B( HDC hDC, double pitch, double roll, double yaw, int adirate, double Altitude_ft )
	{
		int pos_roll;
		int pos_pitch;
		int pos_yaw;

		SelectObject( hDC, gdiSSVBFont_h12w7 );
		SetTextColor( hDC, CR_WHITE );
		SetTextAlign( hDC, TA_RIGHT );
		if (adirate == 1)
		{
			// ADI RATE MED
			if (Altitude_ft < 6400)// HACK should use a 3sec timer starting at 7Kft, which expires about 6.4Kft
			{
				// <7k + 3s
				TextOut( hDC, 151, 31, "5", 1 );
				TextOut( hDC, 151, 283, "5", 1 );

				SetTextAlign( hDC, TA_LEFT );
				//TextOut( hDC, 151, 31, "5", 1 );
				TextOut( hDC, 327, 31, "5", 1 );

				TextOut( hDC, 356, 65, "5", 1 );
				TextOut( hDC, 356, 251, "5", 1 );

				//TextOut( hDC, 151, 283, "5", 1 );
				TextOut( hDC, 327, 283, "5", 1 );

				SetTextColor( hDC, CR_LIGHT_GRAY );
				TextOut( hDC, 236, 18, "0", 1 );
				TextOut( hDC, 375, 159, "0", 1 );
				TextOut( hDC, 236, 298, "0", 1 );

				if (roll > 5) pos_roll = 324;
				else if (roll < -5) pos_roll = 154;
				else pos_roll = 239 + Round( roll * 17 );

				if (pitch > 5) pos_pitch = 80;
				else if (pitch < -5) pos_pitch = 250;
				else pos_pitch = 165 - Round( pitch * 17 );

				if (yaw > 5) pos_yaw = 324;
				else if (yaw < -5) pos_yaw = 154;
				else pos_yaw = 239 + Round( yaw * 17 );
			}
			else if (Altitude_ft < 7000)
			{
				// <7k
				// blank
				// blank
				// blank
				pos_roll = 0;
				pos_pitch = 0;
				pos_yaw = 0;
			}
			else if (GetIDP()->GetPrefinalState() == true)
			{
				// PRFNL - 7k
				// blank
				// alt err +/-1k
				// y-runway position err +/-1k
				TextOut( hDC, 151, 283, "1K", 2 );

				SetTextAlign( hDC, TA_LEFT );
				TextOut( hDC, 356, 65, "1K", 2 );
				TextOut( hDC, 356, 251, "1K", 2 );

				//TextOut( hDC, 151, 283, "1K", 2 );
				TextOut( hDC, 327, 283, "1K", 2 );

				SetTextColor( hDC, CR_LIGHT_GRAY );
				TextOut( hDC, 375, 159, "0", 1 );
				TextOut( hDC, 236, 298, "0", 1 );

				pos_roll = 0;
				pitch = GetIDP()->GetGlideSlopeDistance();
				yaw = -GetIDP()->GetYRunwayPositionError();

				if (pitch > 1000) pos_pitch = 80;
				else if (pitch < -1000) pos_pitch = 250;
				else pos_pitch = 165 - Round( pitch * 0.085 );

				if (yaw > 1000) pos_yaw = 324;
				else if (yaw < -1000) pos_yaw = 154;
				else pos_yaw = 239 + Round( yaw * 0.085 );
			}
			else if (GetIDP()->GetOnHACState() == true)
			{
				// HAC
				// blank
				// alt err +/-5k
				// HAC x-range err +/-5k
				TextOut( hDC, 151, 283, "5K", 2 );

				SetTextAlign( hDC, TA_LEFT );
				TextOut( hDC, 356, 65, "5K", 2 );
				TextOut( hDC, 356, 251, "5K", 2 );

				//TextOut( hDC, 151, 283, "5K", 2 );
				TextOut( hDC, 327, 283, "5K", 2 );

				SetTextColor( hDC, CR_LIGHT_GRAY );
				TextOut( hDC, 375, 159, "0", 1 );
				TextOut( hDC, 236, 298, "0", 1 );

				pos_roll = 0;
				pitch = GetIDP()->GetGlideSlopeDistance();
				yaw = GetIDP()->GetHACRadialError();

				if (pitch > 5000) pos_pitch = 80;
				else if (pitch < -5000) pos_pitch = 250;
				else pos_pitch = 165 - Round( pitch * 0.017 );

				if (yaw > 5000) pos_yaw = 324;
				else if (yaw < -5000) pos_yaw = 154;
				else pos_yaw = 239 + Round( yaw * 0.017 );
			}
			else
			{
				// ACQ
				// time to HAC 10s
				// alt err +/-5k
				// heading err +/-5º
				// (roll scale output is below)
				TextOut( hDC, 151, 283, "5", 1 );

				SetTextAlign( hDC, TA_LEFT );
				TextOut( hDC, 356, 65, "5K", 2 );
				TextOut( hDC, 356, 251, "5K", 2 );

				//TextOut( hDC, 151, 283, "5", 1 );
				TextOut( hDC, 327, 283, "5", 1 );

				SetTextColor( hDC, CR_LIGHT_GRAY );
				TextOut( hDC, 375, 159, "0", 1 );
				TextOut( hDC, 236, 298, "0", 1 );

				roll = ceil( GetIDP()->GetTimeToHAC() );
				pitch = GetIDP()->GetGlideSlopeDistance();
				yaw = GetIDP()->GetdeltaAZ();

				SetTextColor( hDC, CR_WHITE );
				if (roll > 0)
				{
					SetTextAlign( hDC, TA_RIGHT );
					TextOut( hDC, 151, 31, "10s", 3 );
					SetTextAlign( hDC, TA_LEFT );
					TextOut( hDC, 327, 31, "0", 1 );
					if (roll >= 10) pos_roll = 154;
					else pos_roll = 324 - Round( roll * 17 );
				}
				else if (roll < 0)
				{
					SetTextAlign( hDC, TA_RIGHT );
					TextOut( hDC, 151, 31, "0", 1 );
					SetTextAlign( hDC, TA_LEFT );
					TextOut( hDC, 327, 31, "10s", 3 );
					if (roll <= -10) pos_roll = 324;
					else pos_roll = 154 - Round( roll * 17 );
				}
				else pos_roll = 0;

				if (pitch > 5000) pos_pitch = 80;
				else if (pitch < -5000) pos_pitch = 250;
				else pos_pitch = 165 - Round( pitch * 0.017 );

				if (yaw > 5) pos_yaw = 324;
				else if (yaw < -5) pos_yaw = 154;
				else pos_yaw = 239 + Round( yaw * 17 );
			}
		}
		else
		{
			// ADI RATE HIGH/LOW
			TextOut( hDC, 151, 31, "5", 1 );
			TextOut( hDC, 151, 283, "5", 1 );

			SetTextAlign( hDC, TA_LEFT );
			//TextOut( hDC, 151, 31, "5", 1 );
			TextOut( hDC, 327, 31, "5", 1 );

			TextOut( hDC, 356, 65, "5", 1 );
			TextOut( hDC, 356, 251, "5", 1 );

			//TextOut( hDC, 151, 283, "5", 1 );
			TextOut( hDC, 327, 283, "5", 1 );

			SetTextColor( hDC, CR_LIGHT_GRAY );
			TextOut( hDC, 236, 18, "0", 1 );
			TextOut( hDC, 375, 159, "0", 1 );
			TextOut( hDC, 236, 298, "0", 1 );

			if (roll > 5) pos_roll = 324;
			else if (roll < -5) pos_roll = 154;
			else pos_roll = 239 + Round( roll * 17 );

			if (pitch > 5) pos_pitch = 80;
			else if (pitch < -5) pos_pitch = 250;
			else pos_pitch = 165 - Round( pitch * 17 );

			if (yaw > 5) pos_yaw = 324;
			else if (yaw < -5) pos_yaw = 154;
			else pos_yaw = 239 + Round( yaw * 17 );
		}

		// draw triangles
		SelectObject( hDC, gdiLightGreenPen );
		SelectObject( hDC, gdiLightGreenBrush );
		POINT tri[3];
		if (pos_roll != 0)
		{
			tri[0].x = pos_roll;
			tri[0].y = 34;
			tri[1].x = tri[0].x + 10;
			tri[1].y = 18;
			tri[2].x = tri[0].x - 10;
			tri[2].y = 18;
			Polygon( hDC, tri, 3 );
		}
		if (pos_pitch != 0)
		{
			tri[0].x = 370;
			tri[0].y = pos_pitch;
			tri[1].x = 386;
			tri[1].y = tri[0].y - 10;
			tri[2].x = 386;
			tri[2].y = tri[0].y + 10;
			Polygon( hDC, tri, 3 );
		}
		if (pos_yaw != 0)
		{
			tri[0].x = pos_yaw;
			tri[0].y = 296;
			tri[1].x = tri[0].x - 10;
			tri[1].y = 312;
			tri[2].x = tri[0].x + 10;
			tri[2].y = 312;
			Polygon( hDC, tri, 3 );
		}
		return;
	}

	void MDU::ADI_RATE_B( oapi::Sketchpad2* skp, double pitch, double roll, double yaw, int adirate, double Altitude_ft )
	{
		int pos_roll;
		int pos_pitch;
		int pos_yaw;

		skp->SetFont( skpSSVBFont_h12w7 );
		skp->SetTextColor( CR_WHITE );
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );
		if (adirate == 1)
		{
			// ADI RATE MED
			if (Altitude_ft < 6400)// HACK should use a 3sec timer starting at 7Kft, which expires about 6.4Kft
			{
				// <7k + 3s
				skp->Text( 151, 31, "5", 1 );
				skp->Text( 151, 283, "5", 1 );

				skp->SetTextAlign( oapi::Sketchpad::LEFT );
				//skp->Text( 151, 31, "5", 1 );
				skp->Text( 327, 31, "5", 1 );

				skp->Text( 356, 65, "5", 1 );
				skp->Text( 356, 251, "5", 1 );

				//skp->Text( 151, 283, "5", 1 );
				skp->Text( 327, 283, "5", 1 );

				skp->SetTextColor( CR_LIGHT_GRAY );
				skp->Text( 236, 18, "0", 1 );
				skp->Text( 375, 159, "0", 1 );
				skp->Text( 236, 298, "0", 1 );

				if (roll > 5) pos_roll = 324;
				else if (roll < -5) pos_roll = 154;
				else pos_roll = 239 + Round( roll * 17 );

				if (pitch > 5) pos_pitch = 80;
				else if (pitch < -5) pos_pitch = 250;
				else pos_pitch = 165 - Round( pitch * 17 );

				if (yaw > 5) pos_yaw = 324;
				else if (yaw < -5) pos_yaw = 154;
				else pos_yaw = 239 + Round( yaw * 17 );
			}
			else if (Altitude_ft < 7000)
			{
				// <7k
				// blank
				// blank
				// blank
				pos_roll = 0;
				pos_pitch = 0;
				pos_yaw = 0;
			}
			else if (GetIDP()->GetPrefinalState() == true)
			{
				// PRFNL - 7k
				// blank
				// alt err +/-1k
				// y-runway position err +/-1k
				skp->Text( 151, 283, "1K", 2 );

				skp->SetTextAlign( oapi::Sketchpad::LEFT );
				skp->Text( 356, 65, "1K", 2 );
				skp->Text( 356, 251, "1K", 2 );

				//skp->Text( 151, 283, "1K", 2 );
				skp->Text( 327, 283, "1K", 2 );

				skp->SetTextColor( CR_LIGHT_GRAY );
				skp->Text( 375, 159, "0", 1 );
				skp->Text( 236, 298, "0", 1 );

				pos_roll = 0;
				pitch = GetIDP()->GetGlideSlopeDistance();
				yaw = -GetIDP()->GetYRunwayPositionError();

				if (pitch > 1000) pos_pitch = 80;
				else if (pitch < -1000) pos_pitch = 250;
				else pos_pitch = 165 - Round( pitch * 0.085 );

				if (yaw > 1000) pos_yaw = 324;
				else if (yaw < -1000) pos_yaw = 154;
				else pos_yaw = 239 + Round( yaw * 0.085 );
			}
			else if (GetIDP()->GetOnHACState() == true)
			{
				// HAC
				// blank
				// alt err +/-5k
				// HAC x-range err +/-5k
				skp->Text( 151, 283, "5K", 2 );

				skp->SetTextAlign( oapi::Sketchpad::LEFT );
				skp->Text( 356, 65, "5K", 2 );
				skp->Text( 356, 251, "5K", 2 );

				//skp->Text( 151, 283, "5K", 2 );
				skp->Text( 327, 283, "5K", 2 );

				skp->SetTextColor( CR_LIGHT_GRAY );
				skp->Text( 375, 159, "0", 1 );
				skp->Text( 236, 298, "0", 1 );

				pos_roll = 0;
				pitch = GetIDP()->GetGlideSlopeDistance();
				yaw = GetIDP()->GetHACRadialError();

				if (pitch > 5000) pos_pitch = 80;
				else if (pitch < -5000) pos_pitch = 250;
				else pos_pitch = 165 - Round( pitch * 0.017 );

				if (yaw > 5000) pos_yaw = 324;
				else if (yaw < -5000) pos_yaw = 154;
				else pos_yaw = 239 + Round( yaw * 0.017 );
			}
			else
			{
				// ACQ
				// time to HAC 10s
				// alt err +/-5k
				// heading err +/-5º
				// (roll scale output is below)
				skp->Text( 151, 283, "5", 1 );

				skp->SetTextAlign( oapi::Sketchpad::LEFT );
				skp->Text( 356, 65, "5K", 2 );
				skp->Text( 356, 251, "5K", 2 );

				//skp->Text( 151, 283, "5", 1 );
				skp->Text( 327, 283, "5", 1 );

				skp->SetTextColor( CR_LIGHT_GRAY );
				skp->Text( 375, 159, "0", 1 );
				skp->Text( 236, 298, "0", 1 );

				roll = ceil( GetIDP()->GetTimeToHAC() );
				pitch = GetIDP()->GetGlideSlopeDistance();
				yaw = GetIDP()->GetdeltaAZ();

				skp->SetTextColor( CR_WHITE );
				if (roll > 0)
				{
					skp->SetTextAlign( oapi::Sketchpad::RIGHT );
					skp->Text( 151, 31, "10s", 3 );
					skp->SetTextAlign( oapi::Sketchpad::LEFT );
					skp->Text( 327, 31, "0", 1 );
					if (roll >= 10) pos_roll = 154;
					else pos_roll = 324 - Round( roll * 17 );
				}
				else if (roll < 0)
				{
					skp->SetTextAlign( oapi::Sketchpad::RIGHT );
					skp->Text( 151, 31, "0", 1 );
					skp->SetTextAlign( oapi::Sketchpad::LEFT );
					skp->Text( 327, 31, "10s", 3 );
					if (roll <= -10) pos_roll = 324;
					else pos_roll = 154 - Round( roll * 17 );
				}
				else pos_roll = 0;

				if (pitch > 5000) pos_pitch = 80;
				else if (pitch < -5000) pos_pitch = 250;
				else pos_pitch = 165 - Round( pitch * 0.017 );

				if (yaw > 5) pos_yaw = 324;
				else if (yaw < -5) pos_yaw = 154;
				else pos_yaw = 239 + Round( yaw * 17 );
			}
		}
		else
		{
			// ADI RATE HIGH/LOW
			skp->Text( 151, 31, "5", 1 );
			skp->Text( 151, 283, "5", 1 );

			skp->SetTextAlign( oapi::Sketchpad::LEFT );
			//skp->Text( 151, 31, "5", 1 );
			skp->Text( 327, 31, "5", 1 );

			skp->Text( 356, 65, "5", 1 );
			skp->Text( 356, 251, "5", 1 );

			//skp->Text( 151, 283, "5", 1 );
			skp->Text( 327, 283, "5", 1 );

			skp->SetTextColor( CR_LIGHT_GRAY );
			skp->Text( 236, 18, "0", 1 );
			skp->Text( 375, 159, "0", 1 );
			skp->Text( 236, 298, "0", 1 );

			if (roll > 5) pos_roll = 324;
			else if (roll < -5) pos_roll = 154;
			else pos_roll = 239 + Round( roll * 17 );

			if (pitch > 5) pos_pitch = 80;
			else if (pitch < -5) pos_pitch = 250;
			else pos_pitch = 165 - Round( pitch * 17 );

			if (yaw > 5) pos_yaw = 324;
			else if (yaw < -5) pos_yaw = 154;
			else pos_yaw = 239 + Round( yaw * 17 );
		}

		// draw triangles
		skp->SetPen( skpLightGreenPen );
		skp->SetBrush( skpLightGreenBrush );
		oapi::IVECTOR2 tri[3];
		if (pos_roll != 0)
		{
			tri[0].x = pos_roll;
			tri[0].y = 34;
			tri[1].x = tri[0].x + 10;
			tri[1].y = 18;
			tri[2].x = tri[0].x - 10;
			tri[2].y = 18;
			skp->Polygon( tri, 3 );
		}
		if (pos_pitch != 0)
		{
			tri[0].x = 370;
			tri[0].y = pos_pitch;
			tri[1].x = 386;
			tri[1].y = tri[0].y - 10;
			tri[2].x = 386;
			tri[2].y = tri[0].y + 10;
			skp->Polygon( tri, 3 );
		}
		if (pos_yaw != 0)
		{
			tri[0].x = pos_yaw;
			tri[0].y = 296;
			tri[1].x = tri[0].x - 10;
			tri[1].y = 312;
			tri[2].x = tri[0].x + 10;
			tri[2].y = 312;
			skp->Polygon( tri, 3 );
		}
		return;
	}

	void MDU::ADI_ERROR_A( HDC hDC, double pitch, double roll, double yaw, int adierr )
	{
		double pos_pitch;
		double pos_roll;
		double pos_yaw;

		SetTextColor( hDC, CR_MAGENTA );
		SelectObject( hDC, gdiSSVBFont_h12w7 );
		if (adierr == 1)
		{
			// ADI ERROR MED
			// 5/5/5
			TextOut( hDC, 337, 105, "5", 1 );
			TextOut( hDC, 337, 208, "5", 1 );

			if (roll > 5) pos_roll = -47;
			else if (roll < -5) pos_roll = 47;
			else pos_roll = -roll * 9.4;

			if (pitch > 5) pos_pitch = 47;
			else if (pitch < -5) pos_pitch = -47;
			else pos_pitch = pitch * 9.4;

			if (yaw > 5) pos_yaw = -47;
			else if (yaw < -5) pos_yaw = 47;
			else pos_yaw = -yaw * 9.4;
		}
		else if (adierr == 2)
		{
			// ADI ERROR HIGH
			// 10/10/10
			TextOut( hDC, 337, 105, "10", 2 );
			TextOut( hDC, 337, 208, "10", 2 );

			if (roll > 10) pos_roll = -47;
			else if (roll < -10) pos_roll = 47;
			else pos_roll = -roll * 4.7;

			if (pitch > 10) pos_pitch = 47;
			else if (pitch < -10) pos_pitch = -47;
			else pos_pitch = pitch * 4.7;

			if (yaw > 10) pos_yaw = -47;
			else if (yaw < -10) pos_yaw = 47;
			else pos_yaw = -yaw * 4.7;
		}
		else
		{
			// ADI ERROR LOW
			// 1/1/1
			TextOut( hDC, 337, 105, "1", 1 );
			TextOut( hDC, 337, 208, "1", 1 );

			if (roll > 1) pos_roll = -47;
			else if (roll < -1) pos_roll = 47;
			else pos_roll = -roll * 47;

			if (pitch > 1) pos_pitch = 47;
			else if (pitch < -1) pos_pitch = -47;
			else pos_pitch = pitch * 47;

			if (yaw > 1) pos_yaw = -47;
			else if (yaw < -1) pos_yaw = 47;
			else pos_yaw = -yaw * 47;
		}

		// draw needles
		SelectObject( hDC, gdiMagentaPen );
		SelectObject( hDC, gdiMagentaBrush );
		Rectangle( hDC, 238 + Round( pos_roll ), 165 - Round( sqrt( 12100 - (pos_roll * pos_roll) ) ), 240 + Round( pos_roll ), 134 );// roll
		Rectangle( hDC, 270, 164 + Round( pos_pitch ), 239 + Round( sqrt( 12100 - (pos_pitch * pos_pitch) ) ), 166 + Round( pos_pitch ) );// pitch
		Rectangle( hDC, 238 + Round( pos_yaw ), 196, 240 + Round( pos_yaw ), 165 + Round( sqrt( 12100 - (pos_yaw * pos_yaw) ) ) );// yaw
		return;
	}

	void MDU::ADI_ERROR_A( oapi::Sketchpad2* skp, double pitch, double roll, double yaw, int adierr )
	{
		double pos_pitch;
		double pos_roll;
		double pos_yaw;

		skp->SetTextColor( CR_MAGENTA );
		skp->SetFont( skpSSVBFont_h12w7 );
		if (adierr == 1)
		{
			// ADI ERROR MED
			// 5/5/5
			skp->Text( 337, 105, "5", 1 );
			skp->Text( 337, 208, "5", 1 );

			if (roll > 5) pos_roll = -47;
			else if (roll < -5) pos_roll = 47;
			else pos_roll = -roll * 9.4;

			if (pitch > 5) pos_pitch = 47;
			else if (pitch < -5) pos_pitch = -47;
			else pos_pitch = pitch * 9.4;

			if (yaw > 5) pos_yaw = -47;
			else if (yaw < -5) pos_yaw = 47;
			else pos_yaw = -yaw * 9.4;
		}
		else if (adierr == 2)
		{
			// ADI ERROR HIGH
			// 10/10/10
			skp->Text( 337, 105, "10", 2 );
			skp->Text( 337, 208, "10", 2 );

			if (roll > 10) pos_roll = -47;
			else if (roll < -10) pos_roll = 47;
			else pos_roll = -roll * 4.7;

			if (pitch > 10) pos_pitch = 47;
			else if (pitch < -10) pos_pitch = -47;
			else pos_pitch = pitch * 4.7;

			if (yaw > 10) pos_yaw = -47;
			else if (yaw < -10) pos_yaw = 47;
			else pos_yaw = -yaw * 4.7;
		}
		else
		{
			// ADI ERROR LOW
			// 1/1/1
			skp->Text( 337, 105, "1", 1 );
			skp->Text( 337, 208, "1", 1 );

			if (roll > 1) pos_roll = -47;
			else if (roll < -1) pos_roll = 47;
			else pos_roll = -roll * 47;

			if (pitch > 1) pos_pitch = 47;
			else if (pitch < -1) pos_pitch = -47;
			else pos_pitch = pitch * 47;

			if (yaw > 1) pos_yaw = -47;
			else if (yaw < -1) pos_yaw = 47;
			else pos_yaw = -yaw * 47;
		}

		// draw needles
		skp->SetPen( skpMagentaPen );
		skp->SetBrush( skpMagentaBrush );
		skp->Rectangle( 238 + Round( pos_roll ), 165 - Round( sqrt( 12100 - (pos_roll * pos_roll) ) ), 240 + Round( pos_roll ), 134 );// roll
		skp->Rectangle( 270, 164 + Round( pos_pitch ), 239 + Round( sqrt( 12100 - (pos_pitch * pos_pitch) ) ), 166 + Round( pos_pitch ) );// pitch
		skp->Rectangle( 238 + Round( pos_yaw ), 196, 240 + Round( pos_yaw ), 165 + Round( sqrt( 12100 - (pos_yaw * pos_yaw) ) ) );// yaw
		return;
	}

	void MDU::ADI_ERROR_B( HDC hDC, double pitch, double roll, double yaw, int adierr )
	{
		double pos_pitch;
		double pos_roll;
		double pos_yaw;

		SetTextColor( hDC, CR_MAGENTA );
		SelectObject( hDC, gdiSSVBFont_h12w7 );
		if (adierr == 1)
		{
			// ADI ERROR MED
			// 25/2/2.5
			TextOut( hDC, 337, 105, "2", 1 );
			TextOut( hDC, 337, 208, "2", 1 );

			if (roll > 25) pos_roll = -47;
			else if (roll < -25) pos_roll = 47;
			else pos_roll = -roll * 1.88;

			if (pitch > 2) pos_pitch = 47;
			else if (pitch < -2) pos_pitch = -47;
			else pos_pitch = pitch * 23.5;
		}
		else if (adierr == 2)
		{
			// ADI ERROR HIGH
			// 25/5/2.5
			TextOut( hDC, 337, 105, "5", 1 );
			TextOut( hDC, 337, 208, "5", 1 );

			if (roll > 25) pos_roll = -47;
			else if (roll < -25) pos_roll = 47;
			else pos_roll = -roll * 1.88;

			if (pitch > 5) pos_pitch = 47;
			else if (pitch < -5) pos_pitch = -47;
			else pos_pitch = pitch * 9.4;
		}
		else
		{
			// ADI ERROR LOW
			// 10/1/2.5
			TextOut( hDC, 337, 105, "1", 1 );
			TextOut( hDC, 337, 208, "1", 1 );

			if (roll > 10) pos_roll = -47;
			else if (roll < -10) pos_roll = 47;
			else pos_roll = -roll * 4.7;

			if (pitch > 1) pos_pitch = 47;
			else if (pitch < -1) pos_pitch = -47;
			else pos_pitch = pitch * 47;
		}
		if (yaw > 2.5) pos_yaw = -47;
		else if (yaw < -2.5) pos_yaw = 47;
		else pos_yaw = -yaw * 18.8;

		// draw needles
		SelectObject( hDC, gdiMagentaPen );
		SelectObject( hDC, gdiMagentaBrush );
		Rectangle( hDC, 238 + Round( pos_roll ), 165 - Round( sqrt( 12100 - (pos_roll * pos_roll) ) ), 240 + Round( pos_roll ), 134 );// roll
		Rectangle( hDC, 270, 164 + Round( pos_pitch ), 239 + Round( sqrt( 12100 - (pos_pitch * pos_pitch) ) ), 166 + Round( pos_pitch ) );// pitch
		Rectangle( hDC, 238 + Round( pos_yaw ), 196, 240 + Round( pos_yaw ), 165 + Round( sqrt( 12100 - (pos_yaw * pos_yaw) ) ) );// yaw
		return;// 25/25/10 5/2/1 2.5/2.5/2.5
	}

	void MDU::ADI_ERROR_B( oapi::Sketchpad2* skp, double pitch, double roll, double yaw, int adierr )
	{
		double pos_pitch;
		double pos_roll;
		double pos_yaw;

		skp->SetTextColor( CR_MAGENTA );
		skp->SetFont( skpSSVBFont_h12w7 );
		if (adierr == 1)
		{
			// ADI ERROR MED
			// 25/2/2.5
			skp->Text( 337, 105, "2", 1 );
			skp->Text( 337, 208, "2", 1 );

			if (roll > 25) pos_roll = -47;
			else if (roll < -25) pos_roll = 47;
			else pos_roll = -roll * 1.88;

			if (pitch > 2) pos_pitch = 47;
			else if (pitch < -2) pos_pitch = -47;
			else pos_pitch = pitch * 23.5;
		}
		else if (adierr == 2)
		{
			// ADI ERROR HIGH
			// 25/5/2.5
			skp->Text( 337, 105, "5", 1 );
			skp->Text( 337, 208, "5", 1 );

			if (roll > 25) pos_roll = -47;
			else if (roll < -25) pos_roll = 47;
			else pos_roll = -roll * 1.88;

			if (pitch > 5) pos_pitch = 47;
			else if (pitch < -5) pos_pitch = -47;
			else pos_pitch = pitch * 9.4;
		}
		else
		{
			// ADI ERROR LOW
			// 10/1/2.5
			skp->Text( 337, 105, "1", 1 );
			skp->Text( 337, 208, "1", 1 );

			if (roll > 10) pos_roll = -47;
			else if (roll < -10) pos_roll = 47;
			else pos_roll = -roll * 4.7;

			if (pitch > 1) pos_pitch = 47;
			else if (pitch < -1) pos_pitch = -47;
			else pos_pitch = pitch * 47;
		}
		if (yaw > 2.5) pos_yaw = -47;
		else if (yaw < -2.5) pos_yaw = 47;
		else pos_yaw = -yaw * 18.8;

		// draw needles
		skp->SetPen( skpMagentaPen );
		skp->SetBrush( skpMagentaBrush );
		skp->Rectangle( 238 + Round( pos_roll ), 165 - Round( sqrt( 12100 - (pos_roll * pos_roll) ) ), 240 + Round( pos_roll ), 134 );// roll
		skp->Rectangle( 270, 164 + Round( pos_pitch ), 239 + Round( sqrt( 12100 - (pos_pitch * pos_pitch) ) ), 166 + Round( pos_pitch ) );// pitch
		skp->Rectangle( 238 + Round( pos_yaw ), 196, 240 + Round( pos_yaw ), 165 + Round( sqrt( 12100 - (pos_yaw * pos_yaw) ) ) );// yaw
		return;// 25/25/10 5/2/1 2.5/2.5/2.5
	}

	void MDU::ADI_ERROR_C( HDC hDC, double pitch, double roll, double yaw, int adierr )
	{
		double pos_pitch;
		double pos_roll;
		double pos_yaw;

		SetTextColor( hDC, CR_MAGENTA );
		SelectObject( hDC, gdiSSVBFont_h12w7 );
		SetTextAlign( hDC, TA_LEFT );
		if (adierr == 0)
		{
			// ADI ERROR LOW
			// 10/0.5g/2.5
			TextOut( hDC, 337, 105, "0.5g", 4 );
			TextOut( hDC, 337, 208, "0.5g", 4 );

			if (roll > 10) pos_roll = -47;
			else if (roll < -10) pos_roll = 47;
			else pos_roll = -roll * 4.7;

			if (pitch > 0.5) pos_pitch = 47;
			else if (pitch < -0.5) pos_pitch = -47;
			else pos_pitch = pitch * 94;
		}
		else
		{
			// ADI ERROR MED/HIGH
			// 25/1.25g/2.5
			TextOut( hDC, 337, 105, "1.2g", 4 );
			TextOut( hDC, 337, 208, "1.2g", 4 );

			if (roll > 25) pos_roll = -47;
			else if (roll < -25) pos_roll = 47;
			else pos_roll = -roll * 1.88;

			if (pitch > 1.25) pos_pitch = 47;
			else if (pitch < -1.25) pos_pitch = -47;
			else pos_pitch = pitch * 37.6;
		}
		if (yaw > 2.5) pos_yaw = -47;
		else if (yaw < -2.5) pos_yaw = 47;
		else pos_yaw = -yaw * 18.8;

		// draw needles
		SelectObject( hDC, gdiMagentaPen );
		SelectObject( hDC, gdiMagentaBrush );
		Rectangle( hDC, 238 + Round( pos_roll ), 165 - Round( sqrt( 12100 - (pos_roll * pos_roll) ) ), 240 + Round( pos_roll ), 134 );// roll
		Rectangle( hDC, 270, 164 + Round( pos_pitch ), 239 + Round( sqrt( 12100 - (pos_pitch * pos_pitch) ) ), 166 + Round( pos_pitch ) );// pitch
		Rectangle( hDC, 238 + Round( pos_yaw ), 196, 240 + Round( pos_yaw ), 165 + Round( sqrt( 12100 - (pos_yaw * pos_yaw) ) ) );// yaw
		return;// 25/25/10 1.25/1.25/0.5 2.5/2.5/2.5
	}

	void MDU::ADI_ERROR_C( oapi::Sketchpad2* skp, double pitch, double roll, double yaw, int adierr )
	{
		double pos_pitch;
		double pos_roll;
		double pos_yaw;

		skp->SetTextColor( CR_MAGENTA );
		skp->SetFont( skpSSVBFont_h12w7 );
		skp->SetTextAlign( oapi::Sketchpad::LEFT );
		if (adierr == 0)
		{
			// ADI ERROR LOW
			// 10/0.5g/2.5
			skp->Text( 337, 105, "0.5g", 4 );
			skp->Text( 337, 208, "0.5g", 4 );

			if (roll > 10) pos_roll = -47;
			else if (roll < -10) pos_roll = 47;
			else pos_roll = -roll * 4.7;

			if (pitch > 0.5) pos_pitch = 47;
			else if (pitch < -0.5) pos_pitch = -47;
			else pos_pitch = pitch * 94;
		}
		else
		{
			// ADI ERROR MED/HIGH
			// 25/1.25g/2.5
			skp->Text( 337, 105, "1.2g", 4 );
			skp->Text( 337, 208, "1.2g", 4 );

			if (roll > 25) pos_roll = -47;
			else if (roll < -25) pos_roll = 47;
			else pos_roll = -roll * 1.88;

			if (pitch > 1.25) pos_pitch = 47;
			else if (pitch < -1.25) pos_pitch = -47;
			else pos_pitch = pitch * 37.6;
		}
		if (yaw > 2.5) pos_yaw = -47;
		else if (yaw < -2.5) pos_yaw = 47;
		else pos_yaw = -yaw * 18.8;

		// draw needles
		skp->SetPen( skpMagentaPen );
		skp->SetBrush( skpMagentaBrush );
		skp->Rectangle( 238 + Round( pos_roll ), 165 - Round( sqrt( 12100 - (pos_roll * pos_roll) ) ), 240 + Round( pos_roll ), 134 );// roll
		skp->Rectangle( 270, 164 + Round( pos_pitch ), 239 + Round( sqrt( 12100 - (pos_pitch * pos_pitch) ) ), 166 + Round( pos_pitch ) );// pitch
		skp->Rectangle( 238 + Round( pos_yaw ), 196, 240 + Round( pos_yaw ), 165 + Round( sqrt( 12100 - (pos_yaw * pos_yaw) ) ) );// yaw
		return;// 25/25/10 1.25/1.25/0.5 2.5/2.5/2.5
	}

	void MDU::ADI_ERROR_D( HDC hDC, double pitch, double roll, double yaw, int adierr )
	{
		double pos_pitch;
		double pos_roll;
		double pos_yaw;

		SetTextColor( hDC, CR_MAGENTA );
		SelectObject( hDC, gdiSSVBFont_h12w7 );
		if (adierr == 1)
		{
			// ADI ERROR MED
			// 5/5/2.5
			TextOut( hDC, 337, 105, "5", 1 );
			TextOut( hDC, 337, 208, "5", 1 );

			if (roll > 5) pos_roll = -47;
			else if (roll < -5) pos_roll = 47;
			else pos_roll = -roll * 9.4;

			if (pitch > 5) pos_pitch = 47;
			else if (pitch < -5) pos_pitch = -47;
			else pos_pitch = pitch * 9.4;
		}
		else if (adierr == 2)
		{
			// ADI ERROR HIGH
			// 20/10/2.5
			TextOut( hDC, 337, 105, "10", 2 );
			TextOut( hDC, 337, 208, "10", 2 );

			if (roll > 10) pos_roll = -47;
			else if (roll < -10) pos_roll = 47;
			else pos_roll = -roll * 4.7;

			if (pitch > 10) pos_pitch = 47;
			else if (pitch < -10) pos_pitch = -47;
			else pos_pitch = pitch * 4.7;
		}
		else
		{
			// ADI ERROR LOW
			// 1/1/2.5
			TextOut( hDC, 337, 105, "1", 1 );
			TextOut( hDC, 337, 208, "1", 1 );

			if (roll > 1) pos_roll = -47;
			else if (roll < -1) pos_roll = 47;
			else pos_roll = -roll * 47;

			if (pitch > 1) pos_pitch = 47;
			else if (pitch < -1) pos_pitch = -47;
			else pos_pitch = pitch * 47;
		}
		if (yaw > 2.5) pos_yaw = -47;
		else if (yaw < -2.5) pos_yaw = 47;
		else pos_yaw = -yaw * 18.8;

		// draw needles
		SelectObject( hDC, gdiMagentaPen );
		SelectObject( hDC, gdiMagentaBrush );
		Rectangle( hDC, 238 + Round( pos_roll ), 165 - Round( sqrt( 12100 - (pos_roll * pos_roll) ) ), 240 + Round( pos_roll ), 134 );// roll
		Rectangle( hDC, 270, 164 + Round( pos_pitch ), 239 + Round( sqrt( 12100 - (pos_pitch * pos_pitch) ) ), 166 + Round( pos_pitch ) );// pitch
		Rectangle( hDC, 238 + Round( pos_yaw ), 196, 240 + Round( pos_yaw ), 165 + Round( sqrt( 12100 - (pos_yaw * pos_yaw) ) ) );// yaw
		return;// 20/5/1 10/5/1 2.5/2.5/2.5
	}

	void MDU::ADI_ERROR_D( oapi::Sketchpad2* skp, double pitch, double roll, double yaw, int adierr )
	{
		double pos_pitch;
		double pos_roll;
		double pos_yaw;

		skp->SetTextColor( CR_MAGENTA );
		skp->SetFont( skpSSVBFont_h12w7 );
		if (adierr == 1)
		{
			// ADI ERROR MED
			// 5/5/2.5
			skp->Text( 337, 105, "5", 1 );
			skp->Text( 337, 208, "5", 1 );

			if (roll > 5) pos_roll = -47;
			else if (roll < -5) pos_roll = 47;
			else pos_roll = -roll * 9.4;

			if (pitch > 5) pos_pitch = 47;
			else if (pitch < -5) pos_pitch = -47;
			else pos_pitch = pitch * 9.4;
		}
		else if (adierr == 2)
		{
			// ADI ERROR HIGH
			// 20/10/2.5
			skp->Text( 337, 105, "10", 2 );
			skp->Text( 337, 208, "10", 2 );

			if (roll > 10) pos_roll = -47;
			else if (roll < -10) pos_roll = 47;
			else pos_roll = -roll * 4.7;

			if (pitch > 10) pos_pitch = 47;
			else if (pitch < -10) pos_pitch = -47;
			else pos_pitch = pitch * 4.7;
		}
		else
		{
			// ADI ERROR LOW
			// 1/1/2.5
			skp->Text( 337, 105, "1", 1 );
			skp->Text( 337, 208, "1", 1 );

			if (roll > 1) pos_roll = -47;
			else if (roll < -1) pos_roll = 47;
			else pos_roll = -roll * 47;

			if (pitch > 1) pos_pitch = 47;
			else if (pitch < -1) pos_pitch = -47;
			else pos_pitch = pitch * 47;
		}
		if (yaw > 2.5) pos_yaw = -47;
		else if (yaw < -2.5) pos_yaw = 47;
		else pos_yaw = -yaw * 18.8;

		// draw needles
		skp->SetPen( skpMagentaPen );
		skp->SetBrush( skpMagentaBrush );
		skp->Rectangle( 238 + Round( pos_roll ), 165 - Round( sqrt( 12100 - (pos_roll * pos_roll) ) ), 240 + Round( pos_roll ), 134 );// roll
		skp->Rectangle( 270, 164 + Round( pos_pitch ), 239 + Round( sqrt( 12100 - (pos_pitch * pos_pitch) ) ), 166 + Round( pos_pitch ) );// pitch
		skp->Rectangle( 238 + Round( pos_yaw ), 196, 240 + Round( pos_yaw ), 165 + Round( sqrt( 12100 - (pos_yaw * pos_yaw) ) ) );// yaw
		return;// 20/5/1 10/5/1 2.5/2.5/2.5
	}

	void MDU::HSI_A( HDC hDC, double course, double roll, bool bearingon, double bearing, bool CDIflag, bool CDIbar, double CDIscale, double CDIdeviation, char primarytype, double primarybearing, char secondarytype, double secondarybearing )
	{
		double sgn = sign( (90 * RAD) - fabs( roll ) );
		// center (239,436) r = 95
		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiBlackBrush );
		::Ellipse( hDC, 134, 331, 344, 541 );// r = 105

		MoveToEx( hDC, 134, 436, NULL );
		LineTo( hDC, 128, 436 );
		MoveToEx( hDC, 165, 362, NULL );
		LineTo( hDC, 159, 356 );
		MoveToEx( hDC, 238, 341, NULL );
		LineTo( hDC, 238, 325 );
		MoveToEx( hDC, 240, 341, NULL );
		LineTo( hDC, 240, 325 );
		MoveToEx( hDC, 313, 362, NULL );
		LineTo( hDC, 319, 356 );
		MoveToEx( hDC, 344, 436, NULL );
		LineTo( hDC, 350, 436 );

		SelectObject( hDC, gdiWhitePen );
		SelectObject( hDC, gdiDarkGrayBrush );
		::Ellipse( hDC, 144, 341, 334, 531 );// r = 95

		SelectObject( hDC, gdiBlackBrush );
		::Ellipse( hDC, 177, 374, 301, 498 );// r = 62

		int x1;
		int y1;
		int x2;
		int y2;
		double cosi;
		double sini;
		for (int i = 90; i != 0; i -= 10)// big lines (10px)
		{
			cosi = cos( (i * RAD) + (course * sgn) );
			sini = sin( (i * RAD) + (course * sgn) );
			x1 = Round( 95 * cosi );
			y1 = Round( 95 * sini );

			x2 = Round( 85 * cosi );
			y2 = Round( 85 * sini );

			MoveToEx( hDC, 239 + x1, 436 - y1, NULL );
			LineTo( hDC, 239 + x2, 436 - y2 );

			MoveToEx( hDC, 239 + y1, 436 + x1, NULL );
			LineTo( hDC, 239 + y2, 436 + x2 );

			MoveToEx( hDC, 239 - x1, 436 + y1, NULL );
			LineTo( hDC, 239 - x2, 436 + y2 );

			MoveToEx( hDC, 239 - y1, 436 - x1, NULL );
			LineTo( hDC, 239 - y2, 436 - x2 );
		}

		for (int i = 85; i > 0; i -= 10)// small lines (5px)
		{
			cosi = cos( (i * RAD) + (course * sgn) );
			sini = sin( (i * RAD) + (course * sgn) );
			x1 = Round( 95 * cosi );
			y1 = Round( 95 * sini );

			x2 = Round( 90 * cosi );
			y2 = Round( 90 * sini );

			MoveToEx( hDC, 239 + x1, 436 - y1, NULL );
			LineTo( hDC, 239 + x2, 436 - y2 );

			MoveToEx( hDC, 239 + y1, 436 + x1, NULL );
			LineTo( hDC, 239 + y2, 436 + x2 );

			MoveToEx( hDC, 239 - x1, 436 + y1, NULL );
			LineTo( hDC, 239 - x2, 436 + y2 );

			MoveToEx( hDC, 239 - y1, 436 - x1, NULL );
			LineTo( hDC, 239 - y2, 436 - x2 );
		}

		SetTextColor( hDC, CR_WHITE );
		SelectObject( hDC, gdiSSVBFont_h12w7 );
		XFORM WTroll;
		char cbuf[4];
		SetGraphicsMode( hDC, GM_ADVANCED );
		for (int i = 0; i <= 33; i += 3)
		{
			// rotate
			WTroll.eM11 = (FLOAT)cos( (course * sgn) - i * 10 * RAD * sgn );
			WTroll.eM12 = (FLOAT)(-sin( (course * sgn) - i * 10 * RAD * sgn ));
			WTroll.eM21 = -WTroll.eM12;
			WTroll.eM22 = WTroll.eM11;
			WTroll.eDx = (FLOAT)(239 - (239 * WTroll.eM11) - (436 * WTroll.eM21));
			WTroll.eDy = (FLOAT)(436 - (436 * WTroll.eM11) + (239 * WTroll.eM21));
			SetWorldTransform( hDC, &WTroll );

			// paint
			sprintf_s( cbuf, 4, "%d", i );// number
			TextOut( hDC, 239 - strlen( cbuf ) * 4, 359, cbuf, strlen( cbuf ) );

			// de-rotate
			ModifyWorldTransform( hDC, &WTroll, MWT_IDENTITY );
		}

		// rotate to course arrow and CDI heading
		WTroll.eM11 = (FLOAT)cos( (bearing * sgn) * RAD );
		WTroll.eM12 = (FLOAT)(-sin( (bearing * sgn) * RAD ));
		WTroll.eM21 = -WTroll.eM12;
		WTroll.eM22 = WTroll.eM11;
		WTroll.eDx = (FLOAT)(239 - (239 * WTroll.eM11) - (436 * WTroll.eM21));
		WTroll.eDy = (FLOAT)(436 - (436 * WTroll.eM11) + (239 * WTroll.eM21));
		SetWorldTransform( hDC, &WTroll );

		if (bearingon) HSI_CourseArrow( hDC );
		HSI_CDI( hDC, CDIflag, CDIbar, CDIscale, CDIdeviation );

		// de-rotate
		ModifyWorldTransform( hDC, &WTroll, MWT_IDENTITY );
		SetGraphicsMode( hDC, GM_COMPATIBLE );

		HSI_Bearing( hDC, primarytype, primarybearing, secondarytype, secondarybearing );

		static const POINT ov_symbol[6] = {{239,419},{242,437},{246,442},{239,449},{232,442},{236,437}};
		SelectObject( hDC, gdiLightGrayBrush );
		SelectObject( hDC, gdiLightGrayPen );
		Polygon( hDC, ov_symbol, 6 );

		// "delete" bottom area where the menu will be
		SelectObject( hDC, gdiBlackBrush );
		SelectObject( hDC, gdiBlackPen );
		Rectangle( hDC, 117, 456, 361, 512 );
		return;
	}

	void MDU::HSI_A( oapi::Sketchpad2* skp, double course, double roll, bool bearingon, double bearing, bool CDIflag, bool CDIbar, double CDIscale, double CDIdeviation, char primarytype, double primarybearing, char secondarytype, double secondarybearing )
	{
		double sgn = sign( (90 * RAD) - fabs( roll ) );
		// center (239,436)
		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpBlackBrush );
		skp->Ellipse( 134, 331, 344, 541 );// r = 105

		skp->Line( 134, 436, 128, 436 );
		skp->Line( 165, 362, 159, 356 );
		skp->Line( 238, 341, 238, 325 );
		skp->Line( 240, 341, 240, 325 );
		skp->Line( 313, 362, 319, 356 );
		skp->Line( 344, 436, 350, 436 );

		skp->SetPen( skpWhitePen );
		skp->SetBrush( skpDarkGrayBrush );
		skp->Ellipse( 144, 341, 334, 531 );// r = 95

		skp->SetBrush( skpBlackBrush );
		skp->Ellipse( 177, 374, 301, 498 );// r = 62

		int x1;
		int y1;
		int x2;
		int y2;
		double cosi;
		double sini;
		for (int i = 90; i != 0; i -= 10)// big lines (10px)
		{
			cosi = cos( (i * RAD) + (course * sgn) );
			sini = sin( (i * RAD) + (course * sgn) );
			x1 = Round( 95 * cosi );
			y1 = Round( 95 * sini );

			x2 = Round( 85 * cosi );
			y2 = Round( 85 * sini );

			skp->Line( 239 + x1, 436 - y1, 239 + x2, 436 - y2 );

			skp->Line( 239 + y1, 436 + x1, 239 + y2, 436 + x2 );

			skp->Line( 239 - x1, 436 + y1, 239 - x2, 436 + y2 );

			skp->Line( 239 - y1, 436 - x1, 239 - y2, 436 - x2 );
		}

		for (int i = 85; i > 0; i -= 10)// small lines (5px)
		{
			cosi = cos( (i * RAD) + (course * sgn) );
			sini = sin( (i * RAD) + (course * sgn) );
			x1 = Round( 95 * cosi );
			y1 = Round( 95 * sini );

			x2 = Round( 90 * cosi );
			y2 = Round( 90 * sini );

			skp->Line( 239 + x1, 436 - y1, 239 + x2, 436 - y2 );

			skp->Line( 239 + y1, 436 + x1, 239 + y2, 436 + x2 );

			skp->Line( 239 - x1, 436 + y1, 239 - x2, 436 + y2 );

			skp->Line( 239 - y1, 436 - x1, 239 - y2, 436 - x2 );
		}

		skp->SetTextColor( CR_WHITE );
		skp->SetFont( skpSSVBFont_h12w7 );
		char cbuf[4];
		oapi::IVECTOR2 cntr;
		cntr.x = 239;
		cntr.y = 436;
		for (int i = 0; i <= 33; i += 3)
		{
			// rotate
			skp->SetWorldTransform2D( 1.0f, (float)(i * 10 * RAD * sgn - (course * sgn)), &cntr );

			// paint
			sprintf_s( cbuf, 4, "%d", i );// number
			skp->Text( 239 - strlen( cbuf ) * 4, 359, cbuf, strlen( cbuf ) );

			// de-rotate
			skp->SetWorldTransform();
		}

		// rotate to course arrow and CDI heading
		skp->SetWorldTransform2D( 1.0f, (float)(-(bearing * sgn) * RAD), &cntr );

		if (bearingon) HSI_CourseArrow( skp );
		HSI_CDI( skp, CDIflag, CDIbar, CDIscale, CDIdeviation );

		// de-rotate
		skp->SetWorldTransform();

		HSI_Bearing( skp, primarytype, primarybearing, secondarytype, secondarybearing );

		static const oapi::IVECTOR2 ov_symbol[6] = {{239,419},{242,437},{246,442},{239,449},{232,442},{236,437}};
		skp->SetBrush( skpLightGrayBrush );
		skp->SetPen( skpLightGrayPen );
		skp->Polygon( ov_symbol, 6 );

		// "delete" bottom area where the menu will be
		skp->SetBrush( skpBlackBrush );
		skp->SetPen( skpBlackPen );
		skp->Rectangle( 117, 456, 361, 512 );
		return;
	}

	void MDU::HSI_E( HDC hDC, double course, bool bearingon, double bearing, bool CDIflag, bool CDIbar, double CDIscale, double CDIdeviation, char primarytype, double primarybearing, char secondarytype, double secondarybearing )
	{
		// center (239,436) r = 95
		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiBlackBrush );
		::Ellipse( hDC, 134, 331, 344, 541 );// r = 105

		MoveToEx( hDC, 134, 436, NULL );
		LineTo( hDC, 128, 436 );
		MoveToEx( hDC, 165, 362, NULL );
		LineTo( hDC, 159, 356 );
		MoveToEx( hDC, 238, 341, NULL );
		LineTo( hDC, 238, 325 );
		MoveToEx( hDC, 240, 341, NULL );
		LineTo( hDC, 240, 325 );
		MoveToEx( hDC, 313, 362, NULL );
		LineTo( hDC, 319, 356 );
		MoveToEx( hDC, 344, 436, NULL );
		LineTo( hDC, 350, 436 );

		SelectObject( hDC, gdiWhitePen );
		SelectObject( hDC, gdiDarkGrayBrush );
		::Ellipse( hDC, 144, 341, 334, 531 );// r = 95

		SelectObject( hDC, gdiBlackBrush );
		::Ellipse( hDC, 177, 374, 301, 498 );// r = 62

		int x1;
		int y1;
		int x2;
		int y2;
		double cosi;
		double sini;
		for (int i = 90; i != 0; i -= 10)// big lines (10px)
		{
			cosi = cos( (i * RAD) + course );
			sini = sin( (i * RAD) + course );
			x1 = Round( 95 * cosi );
			y1 = Round( 95 * sini );

			x2 = Round( 85 * cosi );
			y2 = Round( 85 * sini );

			MoveToEx( hDC, 239 + x1, 436 - y1, NULL );
			LineTo( hDC, 239 + x2, 436 - y2 );

			MoveToEx( hDC, 239 + y1, 436 + x1, NULL );
			LineTo( hDC, 239 + y2, 436 + x2 );

			MoveToEx( hDC, 239 - x1, 436 + y1, NULL );
			LineTo( hDC, 239 - x2, 436 + y2 );

			MoveToEx( hDC, 239 - y1, 436 - x1, NULL );
			LineTo( hDC, 239 - y2, 436 - x2 );
		}
		for (int i = 85; i > 0; i -= 10)// small lines (5px)
		{
			cosi = cos( (i * RAD) + course );
			sini = sin( (i * RAD) + course );
			x1 = Round( 95 * cosi );
			y1 = Round( 95 * sini );

			x2 = Round( 90 * cosi );
			y2 = Round( 90 * sini );

			MoveToEx( hDC, 239 + x1, 436 - y1, NULL );
			LineTo( hDC, 239 + x2, 436 - y2 );

			MoveToEx( hDC, 239 + y1, 436 + x1, NULL );
			LineTo( hDC, 239 + y2, 436 + x2 );

			MoveToEx( hDC, 239 - x1, 436 + y1, NULL );
			LineTo( hDC, 239 - x2, 436 + y2 );

			MoveToEx( hDC, 239 - y1, 436 - x1, NULL );
			LineTo( hDC, 239 - y2, 436 - x2 );
		}

		SetTextColor( hDC, CR_WHITE );
		SelectObject( hDC, gdiSSVBFont_h12w7 );
		XFORM WTroll;
		char cbuf[4];
		SetGraphicsMode( hDC, GM_ADVANCED );
		for (int i = 0; i <= 33; i += 3)
		{
			// rotate
			WTroll.eM11 = (FLOAT)cos( course - i * 10 * RAD );
			WTroll.eM12 = (FLOAT)(-sin( course - i * 10 * RAD ));
			WTroll.eM21 = -WTroll.eM12;
			WTroll.eM22 = WTroll.eM11;
			WTroll.eDx = (FLOAT)(239 - (239 * WTroll.eM11) - (436 * WTroll.eM21));
			WTroll.eDy = (FLOAT)(436 - (436 * WTroll.eM11) + (239 * WTroll.eM21));
			SetWorldTransform( hDC, &WTroll );

			// paint
			if ((i % 9) != 0)// number
			{
				sprintf_s( cbuf, 4, "%d", i );
				TextOut( hDC, 239 - strlen( cbuf ) * 4, 359, cbuf, strlen( cbuf ) );
			}
			else// letter
			{
				SelectObject( hDC, gdiSSVBFont_h16w9 );
				if (i == 0) TextOut( hDC, 235, 354, "N", 1 );
				else if (i == 9) TextOut( hDC, 235, 354, "E", 1 );
				else if (i == 18) TextOut( hDC, 235, 354, "S", 1 );
				else TextOut( hDC, 235, 354, "W", 1 );
				SelectObject( hDC, gdiSSVBFont_h12w7 );
			}

			// de-rotate
			ModifyWorldTransform( hDC, &WTroll, MWT_IDENTITY );
		}

		// rotate to course arrow and CDI heading
		WTroll.eM11 = (FLOAT)cos( ((course * DEG) - bearing) * RAD );
		WTroll.eM12 = (FLOAT)(-sin( ((course * DEG) - bearing) * RAD ));
		WTroll.eM21 = -WTroll.eM12;
		WTroll.eM22 = WTroll.eM11;
		WTroll.eDx = (FLOAT)(239 - (239 * WTroll.eM11) - (436 * WTroll.eM21));
		WTroll.eDy = (FLOAT)(436 - (436 * WTroll.eM11) + (239 * WTroll.eM21));
		SetWorldTransform( hDC, &WTroll );

		if (bearingon) HSI_CourseArrow( hDC );
		HSI_CDI( hDC, CDIflag, CDIbar, CDIscale, CDIdeviation );

		// de-rotate
		ModifyWorldTransform( hDC, &WTroll, MWT_IDENTITY );
		SetGraphicsMode( hDC, GM_COMPATIBLE );

		HSI_Bearing( hDC, primarytype, primarybearing, secondarytype, secondarybearing );

		// draw ov symbol
		static const POINT ov_symbol[6] = {{239,419},{242,437},{246,442},{239,449},{232,442},{236,437}};
		SelectObject( hDC, gdiLightGrayBrush );
		SelectObject( hDC, gdiLightGrayPen );
		Polygon( hDC, ov_symbol, 6 );

		// "delete" bottom area where the menu will be
		SelectObject( hDC, gdiBlackBrush );
		SelectObject( hDC, gdiBlackPen );
		Rectangle( hDC, 117, 456, 361, 512 );
		return;
	}

	void MDU::HSI_E( oapi::Sketchpad2* skp, double course, bool bearingon, double bearing, bool CDIflag, bool CDIbar, double CDIscale, double CDIdeviation, char primarytype, double primarybearing, char secondarytype, double secondarybearing )
	{
		// center (239,436)
		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpBlackBrush );
		skp->Ellipse( 134, 331, 344, 541 );// r = 105

		skp->Line( 134, 436, 128, 436 );
		skp->Line( 165, 362, 159, 356 );
		skp->Line( 238, 341, 238, 325 );
		skp->Line( 240, 341, 240, 325 );
		skp->Line( 313, 362, 319, 356 );
		skp->Line( 344, 436, 350, 436 );

		skp->SetPen( skpWhitePen );
		skp->SetBrush( skpDarkGrayBrush );
		skp->Ellipse( 144, 341, 334, 531 );// r = 95

		skp->SetBrush( skpBlackBrush );
		skp->Ellipse( 177, 374, 301, 498 );// r = 62

		int x1;
		int y1;
		int x2;
		int y2;
		double cosi;
		double sini;
		for (int i = 90; i != 0; i -= 10)// big lines (10px)
		{
			cosi = cos( (i * RAD) + course );
			sini = sin( (i * RAD) + course );
			x1 = Round( 95 * cosi );
			y1 = Round( 95 * sini );

			x2 = Round( 85 * cosi );
			y2 = Round( 85 * sini );

			skp->Line( 239 + x1, 436 - y1, 239 + x2, 436 - y2 );

			skp->Line( 239 + y1, 436 + x1, 239 + y2, 436 + x2 );

			skp->Line( 239 - x1, 436 + y1, 239 - x2, 436 + y2 );

			skp->Line( 239 - y1, 436 - x1, 239 - y2, 436 - x2 );
		}

		for (int i = 85; i > 0; i -= 10)// small lines (5px)
		{
			cosi = cos( (i * RAD) + course );
			sini = sin( (i * RAD) + course );
			x1 = Round( 95 * cosi );
			y1 = Round( 95 * sini );

			x2 = Round( 90 * cosi );
			y2 = Round( 90 * sini );

			skp->Line( 239 + x1, 436 - y1, 239 + x2, 436 - y2 );

			skp->Line( 239 + y1, 436 + x1, 239 + y2, 436 + x2 );

			skp->Line( 239 - x1, 436 + y1, 239 - x2, 436 + y2 );

			skp->Line( 239 - y1, 436 - x1, 239 - y2, 436 - x2 );
		}

		skp->SetTextColor( CR_WHITE );
		skp->SetFont( skpSSVBFont_h12w7 );
		char cbuf[4];
		oapi::IVECTOR2 cntr;
		cntr.x = 239;
		cntr.y = 436;
		for (int i = 0; i <= 33; i += 3)
		{
			// rotate
			skp->SetWorldTransform2D( 1.0f, (float)(i * 10 * RAD - course), &cntr );

			// paint
			if ((i % 9) != 0)// number
			{
				sprintf_s( cbuf, 4, "%d", i );
				skp->Text( 239 - strlen( cbuf ) * 4, 359, cbuf, strlen( cbuf ) );
			}
			else// letter
			{
				skp->SetFont( skpSSVBFont_h16w9 );
				if (i == 0) skp->Text( 235, 354, "N", 1 );
				else if (i == 9) skp->Text( 235, 354, "E", 1 );
				else if (i == 18) skp->Text( 235, 354, "S", 1 );
				else skp->Text( 235, 354, "W", 1 );
				skp->SetFont( skpSSVBFont_h12w7 );
			}

			// de-rotate
			skp->SetWorldTransform();
		}

		// rotate to course arrow and CDI heading
		skp->SetWorldTransform2D( 1.0f, (float)((bearing - (course * DEG)) * RAD), &cntr );

		if (bearingon) HSI_CourseArrow( skp );
		HSI_CDI( skp, CDIflag, CDIbar, CDIscale, CDIdeviation );

		// de-rotate
		skp->SetWorldTransform();

		HSI_Bearing( skp, primarytype, primarybearing, secondarytype, secondarybearing );

		// draw ov symbol
		static const oapi::IVECTOR2 ov_symbol[6] = {{239,419},{242,437},{246,442},{239,449},{232,442},{236,437}};
		skp->SetBrush( skpLightGrayBrush );
		skp->SetPen( skpLightGrayPen );
		skp->Polygon( ov_symbol, 6 );

		// "delete" bottom area where the menu will be
		skp->SetBrush( skpBlackBrush );
		skp->SetPen( skpBlackPen );
		skp->Rectangle( 117, 456, 361, 512 );
		return;
	}

	void MDU::HSI_CourseArrow( HDC hDC )
	{
		SelectObject( hDC, gdiMagentaBrush );
		SelectObject( hDC, gdiBlackPen );

		// head
		static const POINT arrow[10] = {{239,349},{234,381},{228,385},{227,390},{233,388},{239,395},{245,388},{251,390},{250,385},{244,381}};
		Polygon( hDC, arrow, 10 );
		MoveToEx( hDC, arrow[0].x, arrow[0].y, NULL );
		LineTo( hDC, arrow[5].x, arrow[5].y );

		// tail
		Rectangle( hDC, 236, 476, 242, 513 );
		return;
	}

	void MDU::HSI_CourseArrow( oapi::Sketchpad2* skp )
	{
		skp->SetBrush( skpMagentaBrush );
		skp->SetPen( skpBlackPen );

		// head
		static const oapi::IVECTOR2 arrow[10] = {{239,349},{234,381},{228,385},{227,390},{233,388},{239,395},{245,388},{251,390},{250,385},{244,381}};
		skp->Polygon( arrow, 10 );
		skp->Line( arrow[0].x, arrow[0].y, arrow[5].x, arrow[5].y );

		// tail
		skp->Rectangle( 236, 476, 242, 513 );
		return;
	}

	void MDU::HSI_CDI( HDC hDC, bool flag, bool bar, double scale, double deviation )
	{
		// HACK (flag == true) assumes (bar == true) && (scale == 0)
		int offset = 0;

		// digital scale
		if (scale > 0.0)
		{
			char cbuf[4];
			sprintf_s( cbuf, 4, "%g", scale );
			TextOut( hDC, 184, 440, cbuf, strlen( cbuf ) );
			SetTextAlign( hDC, TA_RIGHT );
			TextOut( hDC, 294, 440, cbuf, strlen( cbuf ) );
			SetTextAlign( hDC, TA_LEFT );

			double scl = scale * (3.0 / 2.0);
			offset = Round( (range( -scl, deviation, scl ) / scl) * 63.0 );
		}

		if (bar)
		{
			// dots
			SelectObject( hDC, gdiWhiteBrush );
			::Ellipse( hDC, 192, 431, 202, 441 );
			::Ellipse( hDC, 213, 431, 223, 441 );
			::Ellipse( hDC, 255, 431, 265, 441 );
			::Ellipse( hDC, 276, 431, 286, 441 );

			// bar (+/-45px)
			SelectObject( hDC, gdiMagentaBrush );
			SelectObject( hDC, gdiBlackPen );
			Rectangle( hDC, 236 - offset, 395, 242 - offset, 476 );
		}

		// off flag
		if (flag)
		{
			SelectObject( hDC, gdiRedPen );
			SelectObject( hDC, gdiRedBrush );
			Rectangle( hDC, 227, 397, 251, 411 );
			SetTextColor( hDC, CR_BLACK );
			TextOut( hDC, 229, 397, "OFF", 3 );
		}
		return;
	}

	void MDU::HSI_CDI( oapi::Sketchpad2* skp, bool flag, bool bar, double scale, double deviation )
	{
		// HACK (flag == true) assumes (bar == true) && (scale == 0)
		int offset = 0;

		// scale
		if (scale > 0.0)
		{
			char cbuf[4];
			sprintf_s( cbuf, 4, "%g", scale );
			skp->Text( 184, 440, cbuf, strlen( cbuf ) );
			skp->SetTextAlign( oapi::Sketchpad::RIGHT );
			skp->Text( 294, 440, cbuf, strlen( cbuf ) );
			skp->SetTextAlign( oapi::Sketchpad::LEFT );

			double scl = scale * (3.0 / 2.0);
			offset = Round( (range( -scl, deviation, scl ) / scl) * 63.0 );
		}

		if (bar)
		{
			// dots
			skp->SetBrush( skpWhiteBrush );
			skp->Ellipse( 192, 431, 202, 441 );
			skp->Ellipse( 213, 431, 223, 441 );
			skp->Ellipse( 255, 431, 265, 441 );
			skp->Ellipse( 276, 431, 286, 441 );

			// bar (+/-45px)
			skp->SetBrush( skpMagentaBrush );
			skp->SetPen( skpBlackPen );
			skp->Rectangle( 236 - offset, 395, 242 - offset, 476 );
		}

		// off flag
		if (flag)
		{
			skp->SetPen( skpRedPen );
			skp->SetBrush( skpRedBrush );
			skp->Rectangle( 227, 397, 251, 411 );
			skp->SetTextColor( CR_BLACK );
			skp->Text( 228, 397, "OFF", 3 );
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

	void MDU::HSI_Bearing( oapi::Sketchpad2* skp, char primarytype, double primarybearing, char secondarytype, double secondarybearing )
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
		WTroll.eM11 = (FLOAT)cos( bearing * RAD );
		WTroll.eM12 = (FLOAT)sin( bearing * RAD );
		WTroll.eM21 = -WTroll.eM12;
		WTroll.eM22 = WTroll.eM11;
		WTroll.eDx = (FLOAT)(239 - (239 * WTroll.eM11) - (436 * WTroll.eM21));
		WTroll.eDy = (FLOAT)(436 - (436 * WTroll.eM11) + (239 * WTroll.eM21));
		SetWorldTransform( hDC, &WTroll );

		if (pri)
		{
			// pointer
			static const POINT pointerPRI[6] = {{239,315},{230,335},{236,335},{239,343},{242,335},{248,335}};
			Polygon( hDC, pointerPRI, 6 );
			TextOut( hDC, 236, 322, "E", 1 );

			// tail
			static const POINT tailPRI[6] = {{239,509},{230,529},{236,529},{239,537},{242,529},{248,529}};
			Polygon( hDC, tailPRI, 6 );
			TextOut( hDC, 236, 516, "E", 1 );
		}
		else
		{
			// pointer
			static const POINT pointerSEC[6] = {{239,321},{230,341},{236,341},{239,349},{242,341},{248,341}};
			Polygon( hDC, pointerSEC, 6 );
			TextOut( hDC, 236, 328, "E", 1 );

			// tail
			static const POINT tailSEC[6] = {{239,498},{230,518},{236,518},{239,526},{242,518},{248,518}};
			Polygon( hDC, tailSEC, 6 );
			TextOut( hDC, 236, 505, "E", 1 );
		}

		// de-rotate
		ModifyWorldTransform( hDC, &WTroll, MWT_IDENTITY );
		return;
	}

	void MDU::HSI_Bearing_E( oapi::Sketchpad2* skp, double bearing, bool pri )
	{
		skp->SetBrush( skpRedBrush );
		skp->SetPen( skpBlackPen );
		skp->SetTextColor( CR_BLACK );

		oapi::IVECTOR2 cntr;
		cntr.x = 239;
		cntr.y = 436;
		// rotate
		skp->SetWorldTransform2D( 1.0f, (float)(bearing * RAD), &cntr );

		if (pri)
		{
			// pointer
			static const oapi::IVECTOR2 pointerPRI[6] = {{239,315},{230,335},{236,335},{239,343},{242,335},{248,335}};
			skp->Polygon( pointerPRI, 6 );
			skp->Text( 236, 322, "E", 1 );

			// tail
			static const oapi::IVECTOR2 tailPRI[6] = {{239,509},{230,529},{236,529},{239,537},{242,529},{248,529}};
			skp->Polygon( tailPRI, 6 );
			skp->Text( 236, 516, "E", 1 );
		}
		else
		{
			// pointer
			static const oapi::IVECTOR2 pointerSEC[6] = {{239,321},{230,341},{236,341},{239,349},{242,341},{248,341}};
			skp->Polygon( pointerSEC, 6 );
			skp->Text( 236, 328, "E", 1 );

			// tail
			static const oapi::IVECTOR2 tailSEC[6] = {{239,498},{230,518},{236,518},{239,526},{242,518},{248,518}};
			skp->Polygon( tailSEC, 6 );
			skp->Text( 236, 505, "E", 1 );
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
		WTroll.eM11 = (FLOAT)cos( bearing * RAD );
		WTroll.eM12 = (FLOAT)sin( bearing * RAD );
		WTroll.eM21 = -WTroll.eM12;
		WTroll.eM22 = WTroll.eM11;
		WTroll.eDx = (FLOAT)(239 - (239 * WTroll.eM11) - (436 * WTroll.eM21));
		WTroll.eDy = (FLOAT)(436 - (436 * WTroll.eM11) + (239 * WTroll.eM21));
		SetWorldTransform( hDC, &WTroll );

		static const POINT marker[6] = {{239,321},{230,341},{236,341},{239,349},{242,341},{248,341}};
		Polygon( hDC, marker, 6 );
		TextOut( hDC, 235, 328, "I", 1 );

		// tail
		static const POINT tail[6] = {{239,498},{230,518},{236,518},{239,526},{242,518},{248,518}};
		Polygon( hDC, tail, 6 );
		TextOut( hDC, 235, 505, "I", 1 );

		// de-rotate
		ModifyWorldTransform( hDC, &WTroll, MWT_IDENTITY );
		return;
	}

	void MDU::HSI_Bearing_I( oapi::Sketchpad2* skp, double bearing )
	{
		skp->SetBrush( skpWhiteBrush );
		skp->SetPen( skpBlackPen );
		skp->SetTextColor( CR_BLACK );

		// pointer
		oapi::IVECTOR2 cntr;
		cntr.x = 239;
		cntr.y = 436;
		// rotate
		skp->SetWorldTransform2D( 1.0f, (float)(bearing * RAD), &cntr );

		static const oapi::IVECTOR2 marker[6] = {{239,321},{230,341},{236,341},{239,349},{242,341},{248,341}};
		skp->Polygon( marker, 6 );
		skp->Text( 235, 328, "I", 1 );

		// tail
		static const oapi::IVECTOR2 tail[6] = {{239,498},{230,518},{236,518},{239,526},{242,518},{248,518}};
		skp->Polygon( tail, 6 );
		skp->Text( 235, 505, "I", 1 );

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
		WTroll.eM11 = (FLOAT)cos( bearing * RAD );
		WTroll.eM12 = (FLOAT)sin( bearing * RAD );
		WTroll.eM21 = -WTroll.eM12;
		WTroll.eM22 = WTroll.eM11;
		WTroll.eDx = (FLOAT)(239 - (239 * WTroll.eM11) - (436 * WTroll.eM21));
		WTroll.eDy = (FLOAT)(436 - (436 * WTroll.eM11) + (239 * WTroll.eM21));
		SetWorldTransform( hDC, &WTroll );

		static const POINT marker[5] = {{239,316},{230,324},{235,336},{243,336},{248,324}};
		Polygon( hDC, marker, 5 );
		char cbuf[2];
		sprintf_s( cbuf, 2, "%c", chr );
		TextOut( hDC, 236, 321, cbuf, 1 );

		// de-rotate
		ModifyWorldTransform( hDC, &WTroll, MWT_IDENTITY );


		// tail
		// rotate
		WTroll.eM11 = (FLOAT)cos( (bearing + 180.0) * RAD );
		WTroll.eM12 = (FLOAT)sin( (bearing + 180.0) * RAD );
		WTroll.eM21 = -WTroll.eM12;
		WTroll.eM22 = WTroll.eM11;
		WTroll.eDx = (FLOAT)(239 - (239 * WTroll.eM11) - (436 * WTroll.eM21));
		WTroll.eDy = (FLOAT)(436 - (436 * WTroll.eM11) + (239 * WTroll.eM21));
		SetWorldTransform( hDC, &WTroll );

		Rectangle( hDC, 234, 350, 244, 366 );
		TextOut( hDC, 236, 352, cbuf, 1 );

		// de-rotate
		ModifyWorldTransform( hDC, &WTroll, MWT_IDENTITY );
		return;
	}

	void MDU::HSI_Bearing_RH( oapi::Sketchpad2* skp, double bearing, char chr )
	{
		skp->SetBrush( skpLightGreenBrush );
		skp->SetPen( skpBlackPen );
		skp->SetTextColor( CR_BLACK );

		// pointer
		oapi::IVECTOR2 cntr;
		cntr.x = 239;
		cntr.y = 436;
		// rotate
		skp->SetWorldTransform2D( 1.0f, (float)(bearing * RAD), &cntr );

		static const oapi::IVECTOR2 marker[5] = {{239,316},{230,324},{235,336},{243,336},{248,324}};
		skp->Polygon( marker, 5 );
		char cbuf[2];
		sprintf_s( cbuf, 2, "%c", chr );
		skp->Text( 236, 321, cbuf, 1 );

		// de-rotate
		skp->SetWorldTransform();


		// tail
		// rotate
		skp->SetWorldTransform2D( 1.0f, (float)((bearing + 180.0) * RAD), &cntr );

		skp->Rectangle( 234, 350, 244, 366 );
		skp->Text( 236, 352, cbuf, 1 );

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
		WTroll.eM11 = (FLOAT)cos( bearing * RAD );
		WTroll.eM12 = (FLOAT)sin( bearing * RAD );
		WTroll.eM21 = -WTroll.eM12;
		WTroll.eM22 = WTroll.eM11;
		WTroll.eDx = (FLOAT)(239 - (239 * WTroll.eM11) - (436 * WTroll.eM21));
		WTroll.eDy = (FLOAT)(436 - (436 * WTroll.eM11) + (239 * WTroll.eM21));
		SetWorldTransform( hDC, &WTroll );

		static const POINT marker[5] = {{239,331},{230,339},{235,351},{243,351},{248,339}};
		Polygon( hDC, marker, 5 );
		TextOut( hDC, 236, 336, "C", 1 );

		// de-rotate
		ModifyWorldTransform( hDC, &WTroll, MWT_IDENTITY );


		// tail
		// rotate
		WTroll.eM11 = (FLOAT)cos( (bearing + 180.0) * RAD );
		WTroll.eM12 = (FLOAT)sin( (bearing + 180.0) * RAD );
		WTroll.eM21 = -WTroll.eM12;
		WTroll.eM22 = WTroll.eM11;
		WTroll.eDx = (FLOAT)(239 - (239 * WTroll.eM11) - (436 * WTroll.eM21));
		WTroll.eDy = (FLOAT)(436 - (436 * WTroll.eM11) + (239 * WTroll.eM21));
		SetWorldTransform( hDC, &WTroll );

		Rectangle( hDC, 234, 359, 244, 375 );
		TextOut( hDC, 236, 361, "C", 1 );

		// de-rotate
		ModifyWorldTransform( hDC, &WTroll, MWT_IDENTITY );
		return;
	}

	void MDU::HSI_Bearing_C( oapi::Sketchpad2* skp, double bearing )
	{
		skp->SetBrush( skpWhiteBrush );
		skp->SetPen( skpBlackPen );
		skp->SetTextColor( CR_BLACK );

		// pointer
		oapi::IVECTOR2 cntr;
		cntr.x = 239;
		cntr.y = 436;
		// rotate
		skp->SetWorldTransform2D( 1.0f, (float)(bearing * RAD), &cntr );

		static const oapi::IVECTOR2 marker[5] = {{239,331},{230,339},{235,351},{243,351},{248,339}};
		skp->Polygon( marker, 5 );
		skp->Text( 236, 336, "C", 1 );

		// de-rotate
		skp->SetWorldTransform();


		// tail
		// rotate
		skp->SetWorldTransform2D( 1.0f, (float)((bearing + 180.0) * RAD), &cntr );

		skp->Rectangle( 234, 359, 244, 375 );
		skp->Text( 236, 361, "C", 1 );

		// de-rotate
		skp->SetWorldTransform();
		return;
	}

	void MDU::AEPFD_Header_AscentDAP( HDC hDC, int MM, int adiatt )
	{
		char cbuf[8];
		SetTextColor( hDC, CR_LIGHT_GRAY );
		TextOut( hDC, 40, 3, "DAP:", 4 );

		TextOut( hDC, 413, 3, "MM:", 3 );

		if (GetIDP()->GetMECOConfirmedFlag() == false) TextOut( hDC, 22, 18, "Throt:", 6 );

		TextOut( hDC, 404, 18, "ATT:", 4 );

		SetTextColor( hDC, CR_WHITE );
		if (GetIDP()->GetFCSmode() == true) TextOut( hDC, 85, 3, "Auto", 4 );
		else
		{
			SelectObject( hDC, gdiYellowPen );
			SelectObject( hDC, GetStockObject( HOLLOW_BRUSH ) );
			Rectangle( hDC, 16, 1, 132, 17 );
			TextOut( hDC, 85, 3, "CSS", 3 );
		}

		if (0) sprintf_s( cbuf, 8, "%dR", MM );// RTLS
		else if (0) sprintf_s( cbuf, 8, "%dT", MM );// TAL
		else if (0) sprintf_s( cbuf, 8, "%dATO", MM );// ATO
		else if (0) sprintf_s( cbuf, 8, "%dAOA", MM );// AOA
		else if (0) sprintf_s( cbuf, 8, "%dCA", MM );// CA
		else sprintf_s( cbuf, 8, "%d", MM );// NOM
		TextOut( hDC, 449, 3, cbuf, strlen( cbuf ) );

		if (GetIDP()->GetMECOConfirmedFlag() == false)
		{
			if (GetIDP()->GetAutoThrottleState() == true) TextOut( hDC, 85, 18, "Auto", 4 );
			else
			{
				SelectObject( hDC, gdiYellowPen );
				SelectObject( hDC, GetStockObject( HOLLOW_BRUSH ) );
				Rectangle( hDC, 16, 16, 132, 32 );
				TextOut( hDC, 85, 18, "MAN", 3 );
			}
		}

		if (adiatt == 2) TextOut( hDC, 449, 18, "Inrtl", 5 );
		else if (adiatt == 1) TextOut( hDC, 449, 18, "LVLH", 4 );
		else TextOut( hDC, 449, 18, "Ref", 3 );
		return;
	}

	void MDU::AEPFD_Header_AscentDAP( oapi::Sketchpad2* skp, int MM, int adiatt )
	{
		char cbuf[8];
		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Text( 40, 3, "DAP:", 4 );

		skp->Text( 413, 3, "MM:", 3 );

		if (GetIDP()->GetMECOConfirmedFlag() == false) skp->Text( 22, 18, "Throt:", 6 );

		skp->Text( 404, 18, "ATT:", 4 );

		skp->SetTextColor( CR_WHITE );
		if (GetIDP()->GetFCSmode() == true) skp->Text( 85, 3, "Auto", 4 );
		else
		{
			skp->SetPen( skpYellowPen );
			skp->SetBrush( NULL );
			skp->Rectangle( 16, 1, 132, 17 );
			skp->Text( 85, 3, "CSS", 3 );
		}

		if (0) sprintf_s( cbuf, 8, "%dR", MM );// RTLS
		else if (0) sprintf_s( cbuf, 8, "%dT", MM );// TAL
		else if (0) sprintf_s( cbuf, 8, "%dATO", MM );// ATO
		else if (0) sprintf_s( cbuf, 8, "%dAOA", MM );// AOA
		else if (0) sprintf_s( cbuf, 8, "%dCA", MM );// CA
		else sprintf_s( cbuf, 8, "%d", MM );// NOM
		skp->Text( 449, 3, cbuf, strlen( cbuf ) );

		if (GetIDP()->GetMECOConfirmedFlag() == false)
		{
			if (GetIDP()->GetAutoThrottleState() == true) skp->Text( 85, 18, "Auto", 4 );
			else
			{
				skp->SetPen( skpYellowPen );
				skp->SetBrush( NULL );
				skp->Rectangle( 16, 19, 132, 35 );
				skp->Text( 85, 21, "MAN", 3 );
			}
		}

		if (adiatt == 2) skp->Text( 449, 18, "Inrtl", 5 );
		else if (adiatt == 1) skp->Text( 449, 18, "LVLH", 4 );
		else skp->Text( 449, 18, "Ref", 3 );
		return;
	}

	void MDU::AEPFD_Header_TransDAP( HDC hDC, int MM, int adiatt )
	{
		char cbuf[8];
		SetTextColor( hDC, CR_LIGHT_GRAY );
		TextOut( hDC, 40, 3, "DAP:", 4 );

		TextOut( hDC, 413, 3, "MM:", 3 );

		TextOut( hDC, 404, 18, "ATT:", 4 );

		SetTextColor( hDC, CR_WHITE );
		if (1) TextOut( hDC, 85, 3, "Auto", 4 );// TODO get TransDAP state
		else TextOut( hDC, 85, 3, "INRTL", 5 );

		if (0) sprintf_s( cbuf, 8, "%dR", MM );// RTLS
		else if (0) sprintf_s( cbuf, 8, "%dT", MM );// TAL
		else if (0) sprintf_s( cbuf, 8, "%dATO", MM );// ATO
		else if (0) sprintf_s( cbuf, 8, "%dAOA", MM );// AOA
		else if (0) sprintf_s( cbuf, 8, "%dCA", MM );// CA
		else sprintf_s( cbuf, 8, "%d", MM );// NOM
		TextOut( hDC, 449, 3, cbuf, strlen( cbuf ) );

		if (adiatt == 2) TextOut( hDC, 449, 18, "Inrtl", 5 );
		else if (adiatt == 1) TextOut( hDC, 449, 18, "LVLH", 4 );
		else TextOut( hDC, 449, 18, "Ref", 3 );
		return;
	}

	void MDU::AEPFD_Header_TransDAP( oapi::Sketchpad2* skp, int MM, int adiatt )
	{
		char cbuf[8];
		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Text( 40, 3, "DAP:", 4 );

		skp->Text( 413, 3, "MM:", 3 );

		skp->Text( 404, 18, "ATT:", 4 );

		skp->SetTextColor( CR_WHITE );
		if (1) skp->Text( 85, 3, "Auto", 4 );// TODO get TransDAP state
		else skp->Text( 85, 3, "INRTL", 5 );

		if (0) sprintf_s( cbuf, 8, "%dR", MM );// RTLS
		else if (0) sprintf_s( cbuf, 8, "%dT", MM );// TAL
		else if (0) sprintf_s( cbuf, 8, "%dATO", MM );// ATO
		else if (0) sprintf_s( cbuf, 8, "%dAOA", MM );// AOA
		else if (0) sprintf_s( cbuf, 8, "%dCA", MM );// CA
		else sprintf_s( cbuf, 8, "%d", MM );// NOM
		skp->Text( 449, 3, cbuf, strlen( cbuf ) );

		if (adiatt == 2) skp->Text( 449, 18, "Inrtl", 5 );
		else if (adiatt == 1) skp->Text( 449, 18, "LVLH", 4 );
		else skp->Text( 449, 18, "Ref", 3 );
		return;
	}

	void MDU::AEPFD_Header_AerojetDAP( HDC hDC, int MM, double vel )
	{
		char cbuf[8];
		SetTextColor( hDC, CR_LIGHT_GRAY );
		TextOut( hDC, 22, 3, "Pitch:", 6 );

		TextOut( hDC, 40, 18, "R/Y:", 4 );

		TextOut( hDC, 413, 3, "MM:", 3 );

		TextOut( hDC, 413, 18, "SB:", 3 );

		SetTextColor( hDC, CR_WHITE );
		if (GetIDP()->GetAutoPitchState() == true) TextOut( hDC, 85, 3, "Auto", 4 );
		else
		{
			if (vel > 1)
			{
				SelectObject( hDC, gdiYellowPen );
				SelectObject( hDC, GetStockObject( HOLLOW_BRUSH ) );
				Rectangle( hDC, 16, 1, 132, 17 );
			}
			TextOut( hDC, 85, 3, "CSS", 3 );
		}

		if (GetIDP()->GetAutoRollYawState() == true) TextOut( hDC, 85, 18, "Auto", 4 );
		else
		{
			if (vel > 1)
			{
				SelectObject( hDC, gdiYellowPen );
				SelectObject( hDC, GetStockObject( HOLLOW_BRUSH ) );
				Rectangle( hDC, 16, 16, 132, 32 );
			}
			TextOut( hDC, 85, 18, "CSS", 3 );
		}

		if (0) sprintf_s( cbuf, 8, "%dR", MM );// RTLS
		else if (0) sprintf_s( cbuf, 8, "%dT", MM );// TAL
		else if (0) sprintf_s( cbuf, 8, "%dATO", MM );// ATO
		else if (0) sprintf_s( cbuf, 8, "%dAOA", MM );// AOA
		else if (0) sprintf_s( cbuf, 8, "%dCA", MM );// CA
		else sprintf_s( cbuf, 8, "%d", MM );// NOM
		TextOut( hDC, 449, 3, cbuf, strlen( cbuf ) );

		if (GetIDP()->GetAutoSpeedbrakeState() == true) TextOut( hDC, 449, 18, "Auto", 4 );
		else
		{
			SelectObject( hDC, gdiYellowPen );
			SelectObject( hDC, GetStockObject( HOLLOW_BRUSH ) );
			Rectangle( hDC, 400, 16, 500, 32 );
			TextOut( hDC, 449, 18, "MAN", 3 );
		}
		return;
	}

	void MDU::AEPFD_Header_AerojetDAP( oapi::Sketchpad2* skp, int MM, double vel )
	{
		char cbuf[8];
		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Text( 22, 3, "Pitch:", 6 );

		skp->Text( 40, 18, "R/Y:", 4 );

		skp->Text( 413, 3, "MM:", 3 );

		skp->Text( 413, 18, "SB:", 3 );

		skp->SetTextColor( CR_WHITE );
		if (GetIDP()->GetAutoPitchState() == true) skp->Text( 85, 3, "Auto", 4 );
		else
		{
			if (vel > 1)
			{
				skp->SetPen( skpYellowPen );
				skp->SetBrush( NULL );
				skp->Rectangle( 16, 1, 132, 17 );
			}
			skp->Text( 85, 3, "CSS", 3 );
		}

		if (GetIDP()->GetAutoRollYawState() == true) skp->Text( 85, 18, "Auto", 4 );
		else
		{
			if (vel > 1)
			{
				skp->SetPen( skpYellowPen );
				skp->SetBrush( NULL );
				skp->Rectangle( 16, 16, 132, 32 );
			}
			skp->Text( 85, 18, "CSS", 3 );
		}

		if (0) sprintf_s( cbuf, 8, "%dR", MM );// RTLS
		else if (0) sprintf_s( cbuf, 8, "%dT", MM );// TAL
		else if (0) sprintf_s( cbuf, 8, "%dATO", MM );// ATO
		else if (0) sprintf_s( cbuf, 8, "%dAOA", MM );// AOA
		else if (0) sprintf_s( cbuf, 8, "%dCA", MM );// CA
		else sprintf_s( cbuf, 8, "%d", MM );// NOM
		skp->Text( 449, 3, cbuf, strlen( cbuf ) );

		if (GetIDP()->GetAutoSpeedbrakeState() == true) skp->Text( 449, 18, "Auto", 4 );
		else
		{
			skp->SetPen( skpYellowPen );
			skp->SetBrush( NULL );
			skp->Rectangle( 400, 16, 500, 32 );
			skp->Text( 449, 18, "MAN", 3 );
		}
		return;
	}

	void MDU::AEPFD_BETA( HDC hDC )
	{
		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 68, 285, 118, 309 );

		SelectObject( hDC, gdiSSVAFont_h11w9 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		TextOut( hDC, 74, 315, "Beta", 4 );

		SelectObject( hDC, gdiSSVBFont_h12w7 );
		SetTextColor( hDC, CR_WHITE );
		double beta = STS()->GetSlipAngle() * DEG;
		if (beta > 0.0) TextOut( hDC, 70, 290, "L", 1 );
		else TextOut( hDC, 70, 290, "R", 1 );

		SelectObject( hDC, gdiSSVBFont_h18w9 );
		SetTextAlign( hDC, TA_RIGHT );
		char cbuf[8];
		sprintf_s( cbuf, 8, "%4.1f", fabs( beta ) );
		TextOut( hDC, 115, 286, cbuf, strlen( cbuf ) );
		SetTextAlign( hDC, TA_LEFT );
		return;
	}

	void MDU::AEPFD_BETA( oapi::Sketchpad2* skp )
	{
		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpBlackBrush );
		skp->Rectangle( 68, 285, 118, 309 );

		skp->SetFont( skpSSVAFont_h11w9 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Text( 74, 315, "Beta", 4 );

		skp->SetFont( skpSSVBFont_h12w7 );
		skp->SetTextColor( CR_WHITE );
		double beta = STS()->GetSlipAngle() * DEG;
		if (beta > 0.0) skp->Text( 70, 290, "L", 1 );
		else skp->Text( 70, 290, "R", 1 );

		skp->SetFont( skpSSVBFont_h18w9 );
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );
		char cbuf[8];
		sprintf_s( cbuf, 8, "%4.1f", fabs( beta ) );
		skp->Text( 115, 286, cbuf, strlen( cbuf ) );
		skp->SetTextAlign( oapi::Sketchpad::LEFT );
		return;
	}

	void MDU::AEPFD_GMETER_STATIC( HDC hDC )
	{
		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 75, 366, 123, 390 );

		Arc( hDC, 31, 356, 107, 432, 69, 356, 96, 421 );

		MoveToEx( hDC, 69, 356, NULL );
		LineTo( hDC, 69, 351 );
		MoveToEx( hDC, 42, 367, NULL );
		LineTo( hDC, 37, 362 );
		MoveToEx( hDC, 31, 394, NULL );
		LineTo( hDC, 26, 394 );
		MoveToEx( hDC, 42, 420, NULL );
		LineTo( hDC, 37, 425 );
		MoveToEx( hDC, 69, 432, NULL );
		LineTo( hDC, 69, 437 );
		MoveToEx( hDC, 95, 420, NULL );
		LineTo( hDC, 100, 425 );

		SetTextAlign( hDC, TA_LEFT );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		SelectObject( hDC, gdiSSVAFont_h11w9 );
		TextOut( hDC, 112, 373, "g", 1 );

		SelectObject( hDC, gdiSSVBFont_h12w7 );
		TextOut( hDC, 27, 346, "3", 1 );
		TextOut( hDC, 12, 387, "2", 1 );
		TextOut( hDC, 27, 424, "1", 1 );
		TextOut( hDC, 66, 439, "0", 1 );
		TextOut( hDC, 100, 427, "-1", 2 );
		return;
	}

	void MDU::AEPFD_GMETER_STATIC( oapi::Sketchpad2* skp )
	{
		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpBlackBrush );
		skp->Ellipse( 31, 356, 107, 432 );
		skp->SetPen( skpBlackPen );
		skp->Rectangle( 69, 356, 108, 421 );// cover part of the circle to get an arc because sketchpad doesn't have Arc()

		skp->SetTextAlign( oapi::Sketchpad::LEFT );
		skp->SetPen( skpLightGrayPen );
		skp->Rectangle( 75, 366, 123, 390 );

		skp->Line( 69, 356, 69, 351 );
		skp->Line( 42, 367, 37, 362 );
		skp->Line( 31, 394, 26, 394 );
		skp->Line( 42, 420, 37, 425 );
		skp->Line( 69, 432, 69, 437 );
		skp->Line( 95, 420, 100, 425 );

		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->SetFont( skpSSVAFont_h11w9 );
		skp->Text( 112, 373, "g", 1 );

		skp->SetFont( skpSSVBFont_h12w7 );
		skp->Text( 27, 346, "3", 1 );
		skp->Text( 12, 387, "2", 1 );
		skp->Text( 27, 424, "1", 1 );
		skp->Text( 66, 439, "0", 1 );
		skp->Text( 100, 427, "-1", 2 );
		return;
	}

	void MDU::AEPFD_GMETER_ACCEL( HDC hDC )
	{
		SelectObject( hDC, gdiSSVAFont_h11w9 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		TextOut( hDC, 83, 395, "Accel", 5 );
		VECTOR3 f;
		STS()->GetForceVector( f );
		double dtmp = (f.z / (STS()->GetMass() * G)) + sin( STS()->GetPitch() );

		SelectObject( hDC, gdiSSVBFont_h18w9 );
		SetTextColor( hDC, CR_WHITE );
		char cbuf[8];
		SetTextAlign( hDC, TA_RIGHT );
		sprintf_s( cbuf, 8, "%.1f", dtmp );
		TextOut( hDC, 111, 367, cbuf, strlen( cbuf ) );
		SetTextAlign( hDC, TA_LEFT );

		if (dtmp > 4) dtmp = 4;
		else if (dtmp < -1) dtmp = -1;
		dtmp = ((dtmp * 45) - 90) * RAD;

		double cosdtmp = cos( dtmp );
		double sindtmp = sin( dtmp );
		// center (69,394)
		POINT arrow[3];
		arrow[0].x = 69 - Round( 33 * cosdtmp );
		arrow[0].y = 394 - Round( 33 * sindtmp );
		arrow[1].x = 69 - Round( (22 * cosdtmp) + (6 * sindtmp) );
		arrow[1].y = 394 - Round( (22 * sindtmp) - (6 * cosdtmp) );
		arrow[2].x = 69 - Round( (22 * cosdtmp) - (6 * sindtmp) );
		arrow[2].y = 394 - Round( (22 * sindtmp) + (6 * cosdtmp) );

		SelectObject( hDC, gdiLightGreenPen );
		SelectObject( hDC, gdiLightGreenBrush );
		Polygon( hDC, arrow, 3 );

		SelectObject( hDC, gdiLightGreenThickPen );
		MoveToEx( hDC, 69, 394, NULL );
		LineTo( hDC, 69 - Round( 31 * cosdtmp ), 394 - Round( 31 * sindtmp ) );
		return;
	}

	void MDU::AEPFD_GMETER_ACCEL( oapi::Sketchpad2* skp )
	{
		skp->SetFont( skpSSVAFont_h11w9 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Text( 83, 395, "Accel", 5 );
		VECTOR3 f;
		STS()->GetForceVector( f );
		double dtmp = (f.z / (STS()->GetMass() * G)) + sin( STS()->GetPitch() );

		skp->SetFont( skpSSVBFont_h18w9 );
		skp->SetTextColor( CR_WHITE );
		char cbuf[8];
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );
		sprintf_s( cbuf, 8, "%.1f", dtmp );
		skp->Text( 111, 367, cbuf, strlen( cbuf ) );
		skp->SetTextAlign( oapi::Sketchpad::LEFT );

		if (dtmp > 4) dtmp = 4;
		else if (dtmp < -1) dtmp = -1;
		dtmp = ((dtmp * 45) - 90) * RAD;

		double cosdtmp = cos( dtmp );
		double sindtmp = sin( dtmp );
		// center (69,394)
		oapi::IVECTOR2 arrow[3];
		arrow[0].x = 69 - Round( 33 * cosdtmp );
		arrow[0].y = 394 - Round( 33 * sindtmp );
		arrow[1].x = 69 - Round( (22 * cosdtmp) + (6 * sindtmp) );
		arrow[1].y = 394 - Round( (22 * sindtmp) - (6 * cosdtmp) );
		arrow[2].x = 69 - Round( (22 * cosdtmp) - (6 * sindtmp) );
		arrow[2].y = 394 - Round( (22 * sindtmp) + (6 * cosdtmp) );

		skp->SetPen( skpLightGreenPen );
		skp->SetBrush( skpLightGreenBrush );
		skp->Polygon( arrow, 3 );

		skp->SetPen( skpLightGreenThickPen );
		skp->Line( 69, 394, 69 - Round( 31 * cosdtmp ), 394 - Round( 31 * sindtmp ) );
		return;
	}

	void MDU::AEPFD_GMETER_NZ( HDC hDC )
	{
		SelectObject( hDC, gdiSSVAFont_h11w9 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		TextOut( hDC, 91, 395, "Nz", 2 );
		double dtmp = GetIDP()->GetNZ();

		SelectObject( hDC, gdiSSVBFont_h18w9 );
		SetTextColor( hDC, CR_WHITE );
		char cbuf[8];
		SetTextAlign( hDC, TA_RIGHT );
		sprintf_s( cbuf, 8, "%.1f", dtmp );
		TextOut( hDC, 111, 367, cbuf, strlen( cbuf ) );
		SetTextAlign( hDC, TA_LEFT );

		if (dtmp > 4) dtmp = 4;
		else if (dtmp < -1) dtmp = -1;
		dtmp = ((dtmp * 45) - 90) * RAD;

		double cosdtmp = cos( dtmp );
		double sindtmp = sin( dtmp );
		// center (69,394)
		POINT arrow[3];
		arrow[0].x = 69 - Round( 33 * cosdtmp );
		arrow[0].y = 394 - Round( 33 * sindtmp );
		arrow[1].x = 69 - Round( (22 * cosdtmp) + (6 * sindtmp) );
		arrow[1].y = 394 - Round( (22 * sindtmp) - (6 * cosdtmp) );
		arrow[2].x = 69 - Round( (22 * cosdtmp) - (6 * sindtmp) );
		arrow[2].y = 394 - Round( (22 * sindtmp) + (6 * cosdtmp) );

		SelectObject( hDC, gdiLightGreenPen );
		SelectObject( hDC, gdiLightGreenBrush );
		Polygon( hDC, arrow, 3 );

		SelectObject( hDC, gdiLightGreenThickPen );
		MoveToEx( hDC, 69, 394, NULL );
		LineTo( hDC, 69 - Round( 31 * cosdtmp ), 394 - Round( 31 * sindtmp ) );
		return;
	}

	void MDU::AEPFD_GMETER_NZ( oapi::Sketchpad2* skp )
	{
		skp->SetFont( skpSSVAFont_h11w9 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Text( 91, 395, "Nz", 2 );
		double dtmp = GetIDP()->GetNZ();

		skp->SetFont( skpSSVBFont_h18w9 );
		skp->SetTextColor( CR_WHITE );
		char cbuf[8];
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );
		sprintf_s( cbuf, 8, "%.1f", dtmp );
		skp->Text( 111, 367, cbuf, strlen( cbuf ) );
		skp->SetTextAlign( oapi::Sketchpad::LEFT );

		if (dtmp > 4) dtmp = 4;
		else if (dtmp < -1) dtmp = -1;
		dtmp = ((dtmp * 45) - 90) * RAD;

		double cosdtmp = cos( dtmp );
		double sindtmp = sin( dtmp );
		// center (34.217)
		oapi::IVECTOR2 arrow[3];
		arrow[0].x = 69 - Round( 33 * cosdtmp );
		arrow[0].y = 394 - Round( 33 * sindtmp );
		arrow[1].x = 69 - Round( (22 * cosdtmp) + (6 * sindtmp) );
		arrow[1].y = 394 - Round( (22 * sindtmp) - (6 * cosdtmp) );
		arrow[2].x = 69 - Round( (22 * cosdtmp) - (6 * sindtmp) );
		arrow[2].y = 394 - Round( (22 * sindtmp) + (6 * cosdtmp) );

		skp->SetPen( skpLightGreenPen );
		skp->SetBrush( skpLightGreenBrush );
		skp->Polygon( arrow, 3 );

		skp->SetPen( skpLightGreenThickPen );
		skp->Line( 69, 394, 69 - Round( 31 * cosdtmp ), 394 - Round( 31 * sindtmp ) );
		return;
	}

	void MDU::AEPFD_HACCEL( HDC hDC )
	{
		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiWhiteBrush );
		Rectangle( hDC, 467, 300, 479, 452 );

		MoveToEx( hDC, 479, 306, NULL );
		LineTo( hDC, 485, 306 );
		MoveToEx( hDC, 479, 320, NULL );
		LineTo( hDC, 485, 320 );
		MoveToEx( hDC, 479, 334, NULL );
		LineTo( hDC, 485, 334 );
		MoveToEx( hDC, 479, 348, NULL );
		LineTo( hDC, 485, 348 );
		MoveToEx( hDC, 479, 362, NULL );
		LineTo( hDC, 485, 362 );
		MoveToEx( hDC, 479, 376, NULL );
		LineTo( hDC, 485, 376 );
		MoveToEx( hDC, 479, 390, NULL );
		LineTo( hDC, 485, 390 );
		MoveToEx( hDC, 479, 404, NULL );
		LineTo( hDC, 485, 404 );
		MoveToEx( hDC, 479, 418, NULL );
		LineTo( hDC, 485, 418 );
		MoveToEx( hDC, 479, 432, NULL );
		LineTo( hDC, 485, 432 );
		MoveToEx( hDC, 479, 446, NULL );
		LineTo( hDC, 485, 446 );

		SelectObject( hDC, gdiDarkGrayBrush );
		Rectangle( hDC, 467, 376, 479, 452 );

		SetPixel( hDC, 471, 283, CR_LIGHT_GRAY );
		SetPixel( hDC, 473, 283, CR_LIGHT_GRAY );
		SelectObject( hDC, gdiSSVAFont_h11w9 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		TextOut( hDC, 468, 286, "H", 1 );
		SelectObject( hDC, gdiSSVBFont_h12w7 );
		SetTextColor( hDC, CR_WHITE );
		TextOut( hDC, 489, 299, "10", 2 );
		TextOut( hDC, 489, 369, "0", 1 );
		TextOut( hDC, 489, 439, "-10", 3 );

		double dtmp = GetIDP()->GetVacc();
		if (dtmp > 10) dtmp = 10;
		else if (dtmp < -10) dtmp = -10;

		POINT tri[3];// starts at tip moving cw
		tri[0].x = 475;
		tri[0].y = 376 - Round( dtmp * 7 );
		tri[1].x = 461;
		tri[1].y = tri[0].y + 8;
		tri[2].x = 461;
		tri[2].y = tri[0].y - 8;

		SelectObject( hDC, gdiLightGreenPen );
		SelectObject( hDC, gdiLightGreenBrush );
		Polygon( hDC, tri, 3 );
		return;
	}

	void MDU::AEPFD_HACCEL( oapi::Sketchpad2* skp )
	{
		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpWhiteBrush );
		skp->Rectangle( 467, 300, 479, 452 );

		skp->Line( 479, 306, 485, 306 );
		skp->Line( 479, 320, 485, 320 );
		skp->Line( 479, 334, 485, 334 );
		skp->Line( 479, 348, 485, 348 );
		skp->Line( 479, 362, 485, 362 );
		skp->Line( 479, 376, 485, 376 );
		skp->Line( 479, 390, 485, 390 );
		skp->Line( 479, 404, 485, 404 );
		skp->Line( 479, 418, 485, 418 );
		skp->Line( 479, 432, 485, 432 );
		skp->Line( 479, 446, 485, 446 );

		skp->SetBrush( skpDarkGrayBrush );
		skp->Rectangle( 467, 376, 479, 452 );

		skp->Pixel( 471, 284, CR_LIGHT_GRAY );
		skp->Pixel( 473, 284, CR_LIGHT_GRAY );
		skp->SetFont( skpSSVAFont_h11w9 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Text( 468, 286, "H", 1 );
		skp->SetFont( skpSSVBFont_h12w7 );
		skp->SetTextColor( CR_WHITE );
		skp->Text( 489, 299, "10", 2 );
		skp->Text( 489, 369, "0", 1 );
		skp->Text( 489, 439, "-10", 3 );

		double dtmp = GetIDP()->GetVacc();
		if (dtmp > 10) dtmp = 10;
		else if (dtmp < -10) dtmp = -10;

		oapi::IVECTOR2 tri[3];// starts at tip moving cw
		tri[0].x = 475;
		tri[0].y = 376 - Round( dtmp * 7 );
		tri[1].x = 461;
		tri[1].y = tri[0].y + 8;
		tri[2].x = 461;
		tri[2].y = tri[0].y - 8;

		skp->SetPen( skpLightGreenPen );
		skp->SetBrush( skpLightGreenBrush );
		skp->Polygon( tri, 3 );
		return;
	}

	void MDU::AEPFD_RANGERW( HDC hDC )
	{
		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 367, 384, 408, 401 );
		SelectObject( hDC, gdiSSVAFont_h11w9 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		char cbuf[8];
		GetIDP()->GetSelectedRunway( cbuf );
		TextOut( hDC, 367, 371, cbuf, 5 );
		SelectObject( hDC, gdiSSVBFont_h12w7 );
		SetTextColor( hDC, CR_WHITE );
		SetTextAlign( hDC, TA_RIGHT );
		double dtmp = GetIDP()->GetSelectedRunwayRange();
		if (dtmp > 1000) sprintf_s( cbuf, 8, "%4.0f", dtmp );// HACK max indicated as 999.9, but probably wrong
		else sprintf_s( cbuf, 8, "%5.1f", dtmp );
		TextOut( hDC, 405, 385, cbuf, strlen( cbuf ) );
		SetTextAlign( hDC, TA_LEFT );
		return;
	}

	void MDU::AEPFD_RANGERW( oapi::Sketchpad2* skp )
	{
		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpBlackBrush );
		skp->Rectangle( 367, 384, 408, 401 );
		skp->SetFont( skpSSVAFont_h11w9 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		char cbuf[8];
		GetIDP()->GetSelectedRunway( cbuf );
		skp->Text( 367, 371, cbuf, 5 );
		skp->SetFont( skpSSVBFont_h12w7 );
		skp->SetTextColor( CR_WHITE );
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );
		double dtmp = GetIDP()->GetSelectedRunwayRange();
		if (dtmp > 1000) sprintf_s( cbuf, 8, "%4.0f", dtmp );// HACK HACK max indicated as 999.9, but probably wrong
		else sprintf_s( cbuf, 8, "%5.1f", dtmp );
		skp->Text( 405, 385, cbuf, strlen( cbuf ) );
		skp->SetTextAlign( oapi::Sketchpad::LEFT );
		return;
	}

	void MDU::AEPFD_RANGEHACC( HDC hDC )
	{
		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 367, 425, 408, 442 );
		SelectObject( hDC, gdiSSVAFont_h11w9 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		TextOut( hDC, 367, 412, "HAC-C", 5 );
		SelectObject( hDC, gdiSSVBFont_h12w7 );
		SetTextColor( hDC, CR_WHITE );
		SetTextAlign( hDC, TA_RIGHT );
		char cbuf[8];
		sprintf_s( cbuf, 8, "%5.1f", GetIDP()->GetHACCRange() );
		TextOut( hDC, 405, 426, cbuf, strlen( cbuf ) );
		SetTextAlign( hDC, TA_LEFT );
		return;
	}

	void MDU::AEPFD_RANGEHACC( oapi::Sketchpad2* skp )
	{
		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpBlackBrush );
		skp->Rectangle( 367, 425, 408, 442 );
		skp->SetFont( skpSSVAFont_h11w9 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Text( 367, 412, "HAC-C", 5 );
		skp->SetFont( skpSSVBFont_h12w7 );
		skp->SetTextColor( CR_WHITE );
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );
		char cbuf[8];
		sprintf_s( cbuf, 8, "%5.1f", GetIDP()->GetHACCRange() );
		skp->Text( 405, 426, cbuf, strlen( cbuf ) );
		skp->SetTextAlign( oapi::Sketchpad::LEFT );
		return;
	}

	void MDU::AEPFD_dAZ_HTA( HDC hDC )
	{
		double dtmp;
		char cbuf[8];
		SelectObject( hDC, gdiBlackBrush );
		SelectObject( hDC, gdiSSVAFont_h11w9 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		if (GetIDP()->GetOnHACState() == false)
		{
			sprintf_s( cbuf, 8, "%cAZ", 255 );
			TextOut( hDC, 315, 327, cbuf, 3 );
			dtmp = fabs( GetIDP()->GetdeltaAZ() );
			if (dtmp >= GetIDP()->GetdeltaAZLimit())
			{
				// rectangle flashes red for limits
				if (GetFlash() == false) SelectObject( hDC, gdiBlackPen );
				else SelectObject( hDC, gdiRedPen );
			}
			else SelectObject( hDC, gdiLightGrayPen );
		}
		else
		{
			TextOut( hDC, 315, 327, "HTA", 3 );
			dtmp = GetIDP()->GetHTA();
			SelectObject( hDC, gdiLightGrayPen );
		}

		Rectangle( hDC, 346, 322, 378, 343 );

		SelectObject( hDC, gdiSSVBFont_h12w7 );
		SetTextColor( hDC, CR_WHITE );
		SetTextAlign( hDC, TA_RIGHT );
		sprintf_s( cbuf, 8, "%3.0f%c", dtmp, 176 );
		TextOut( hDC, 377, 325, cbuf, strlen( cbuf ) );
		SetTextAlign( hDC, TA_LEFT );
		return;
	}

	void MDU::AEPFD_dAZ_HTA( oapi::Sketchpad2* skp )
	{
		double dtmp;
		char cbuf[8];
		skp->SetBrush( skpBlackBrush );
		skp->SetFont( skpSSVAFont_h11w9 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		if (GetIDP()->GetOnHACState() == false)
		{
			sprintf_s( cbuf, 8, "%cAZ", 255 );
			skp->Text( 315, 327, cbuf, 3 );
			dtmp = fabs( GetIDP()->GetdeltaAZ() );
			if (dtmp >= GetIDP()->GetdeltaAZLimit())
			{
				// rectangle flashes red for limits
				if (GetFlash() == false) skp->SetPen( skpBlackPen );
				else skp->SetPen( skpRedPen );
			}
			else skp->SetPen( skpLightGrayPen );
		}
		else
		{
			skp->Text( 315, 327, "HTA", 3 );
			dtmp = GetIDP()->GetHTA();
			skp->SetPen( skpLightGrayPen );
		}

		skp->Rectangle( 346, 322, 378, 343 );

		skp->SetFont( skpSSVBFont_h12w7 );
		skp->SetTextColor( CR_WHITE );
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );
		sprintf_s( cbuf, 8, "%3.0f%c", dtmp, 176 );
		skp->Text( 377, 325, cbuf, strlen( cbuf ) );
		skp->SetTextAlign( oapi::Sketchpad::LEFT );
		return;
	}

	void MDU::AEPFD_dXTRK( HDC hDC )
	{
		SelectObject( hDC, gdiSSVAFont_h11w9 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		char cbuf[8];
		sprintf_s( cbuf, 8, "%c X-Trk", 255 );
		TextOut( hDC, 379, 294, cbuf, 7 );

		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 446, 289, 496, 313 );

		SelectObject( hDC, gdiSSVBFont_h18w9 );
		SetTextColor( hDC, CR_WHITE );
		SetTextAlign( hDC, TA_RIGHT );
		double dtmp = 0;// TODO
		sprintf_s( cbuf, 8, "%4.1f", dtmp );
		TextOut( hDC, 493, 290, cbuf, strlen( cbuf ) );
		SetTextAlign( hDC, TA_LEFT );
		return;
	}

	void MDU::AEPFD_dXTRK( oapi::Sketchpad2* skp )
	{
		skp->SetFont( skpSSVAFont_h11w9 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		char cbuf[8];
		sprintf_s( cbuf, 8, "%c X-Trk", 255 );
		skp->Text( 379, 294, cbuf, 7 );

		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpBlackBrush );
		skp->Rectangle( 446, 289, 496, 313 );

		skp->SetFont( skpSSVBFont_h18w9 );
		skp->SetTextColor( CR_WHITE );
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );
		double dtmp = 0;// TODO
		sprintf_s( cbuf, 8, "%4.1f", dtmp );
		skp->Text( 493, 290, cbuf, strlen( cbuf ) );
		skp->SetTextAlign( oapi::Sketchpad::LEFT );
		return;
	}

	void MDU::AEPFD_XTRK( HDC hDC )
	{
		SelectObject( hDC, gdiSSVAFont_h11w9 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		TextOut( hDC, 397, 337, "X-Trk", 5 );

		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 446, 332, 496, 356 );

		SelectObject( hDC, gdiSSVBFont_h18w9 );
		SetTextColor( hDC, CR_WHITE );
		SetTextAlign( hDC, TA_RIGHT );
		double dtmp = 0;// TODO
		char cbuf[8];
		sprintf_s( cbuf, 8, "%4.1f", dtmp );
		TextOut( hDC, 493, 333, cbuf, strlen( cbuf ) );
		SetTextAlign( hDC, TA_LEFT );
		return;
	}

	void MDU::AEPFD_XTRK( oapi::Sketchpad2* skp )
	{
		skp->SetFont( skpSSVAFont_h11w9 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Text( 397, 337, "X-Trk", 5 );

		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpBlackBrush );
		skp->Rectangle( 446, 332, 496, 356 );

		skp->SetFont( skpSSVBFont_h18w9 );
		skp->SetTextColor( CR_WHITE );
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );
		double dtmp = 0;// TODO
		char cbuf[8];
		sprintf_s( cbuf, 8, "%4.1f", dtmp );
		skp->Text( 493, 333, cbuf, strlen( cbuf ) );
		skp->SetTextAlign( oapi::Sketchpad::LEFT );
		return;
	}

	void MDU::AEPFD_dINC( HDC hDC )
	{
		SelectObject( hDC, gdiSSVAFont_h11w9 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		char cbuf[8];
		sprintf_s( cbuf, 8, "%c Inc", 255 );
		TextOut( hDC, 388, 380, cbuf, 5 );

		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 437, 375, 496, 399 );

		SelectObject( hDC, gdiSSVBFont_h18w9 );
		SetTextColor( hDC, CR_WHITE );
		SetTextAlign( hDC, TA_RIGHT );
		ELEMENTS el;
		STS()->GetElements( STS()->GetGravityRef(), el, NULL, 0, FRAME_EQU );
		sprintf_s( cbuf, 8, "%6.2f", (STS()->pMission->GetMECOInc() - el.i) * DEG );
		TextOut( hDC, 493, 376, cbuf, strlen( cbuf ) );
		SetTextAlign( hDC, TA_LEFT );
		return;
	}

	void MDU::AEPFD_dINC( oapi::Sketchpad2* skp )
	{
		skp->SetFont( skpSSVAFont_h11w9 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		char cbuf[8];
		sprintf_s( cbuf, 8, "%c Inc", 255 );
		skp->Text( 388, 380, cbuf, 5 );

		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpBlackBrush );
		skp->Rectangle( 437, 375, 496, 399 );

		skp->SetFont( skpSSVBFont_h18w9 );
		skp->SetTextColor( CR_WHITE );
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );
		ELEMENTS el;
		STS()->GetElements( STS()->GetGravityRef(), el, NULL, 0, FRAME_EQU );
		sprintf_s( cbuf, 8, "%6.2f", (STS()->pMission->GetMECOInc() - el.i) * DEG );
		skp->Text( 493, 376, cbuf, strlen( cbuf ) );
		skp->SetTextAlign( oapi::Sketchpad::LEFT );
		return;
	}

	void MDU::AEPFD_TGTINC( HDC hDC )
	{
		SelectObject( hDC, gdiSSVAFont_h11w9 );
		SetTextColor( hDC, CR_LIGHT_GRAY );
		TextOut( hDC, 370, 423, "Tgt Inc", 7 );

		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 437, 418, 496, 442 );

		SelectObject( hDC, gdiSSVBFont_h18w9 );
		SetTextColor( hDC, CR_WHITE );
		SetTextAlign( hDC, TA_RIGHT );
		double dtmp = 0;// TODO
		char cbuf[8];
		sprintf_s( cbuf, 8, "%5.2f", dtmp );
		TextOut( hDC, 489, 419, cbuf, strlen( cbuf ) );
		SetTextAlign( hDC, TA_LEFT );
		return;
	}

	void MDU::AEPFD_TGTINC( oapi::Sketchpad2* skp )
	{
		skp->SetFont( skpSSVAFont_h11w9 );
		skp->SetTextColor( CR_LIGHT_GRAY );
		skp->Text( 370, 423, "Tgt Inc", 7 );

		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpBlackBrush );
		skp->Rectangle( 437, 418, 496, 442 );

		skp->SetFont( skpSSVBFont_h18w9 );
		skp->SetTextColor( CR_WHITE );
		skp->SetTextAlign( oapi::Sketchpad::RIGHT );
		double dtmp = 0;// TODO
		char cbuf[8];
		sprintf_s( cbuf, 8, "%5.2f", dtmp );
		skp->Text( 489, 419, cbuf, strlen( cbuf ) );
		skp->SetTextAlign( oapi::Sketchpad::LEFT );
		return;
	}

	void MDU::AEPFD_GSI( HDC hDC, bool flag, double scale, double deviation )
	{
		SelectObject( hDC, gdiLightGrayPen );
		SelectObject( hDC, gdiBlackBrush );
		Rectangle( hDC, 434, 290, 448, 442 );
		SelectObject( hDC, gdiLightGrayBrush );
		::Ellipse( hDC, 437, 297, 445, 305 );
		::Ellipse( hDC, 437, 329, 445, 337 );
		::Ellipse( hDC, 437, 395, 445, 403 );
		::Ellipse( hDC, 437, 427, 445, 435 );
		MoveToEx( hDC, 434, 366, NULL );
		LineTo( hDC, 448, 366 );

		SelectObject( hDC, gdiSSVBFont_h12w7 );

		char cbuf[8];
		sprintf_s( cbuf, 8, "%dK", (int)scale / 1000 );
		TextOut( hDC, 434, 276, cbuf, 2 );
		TextOut( hDC, 434, 442, cbuf, 2 );

		if (flag)
		{
			// no tracking -> print GS label
			SelectObject( hDC, gdiRedPen );
			SelectObject( hDC, gdiRedBrush );
			Rectangle( hDC, 427, 357, 455, 374 );
			SetTextColor( hDC, CR_BLACK );
			TextOut( hDC, 434, 359, "GS", 2 );
		}
		else
		{
			POINT tri[3];
			tri[0].x = 441;// starts at tip moving cw
			tri[1].x = 457;
			tri[2].x = 457;

			// distance BELOW glide path
			if (deviation < -scale)
			{
				if (GetFlash() == false) return;
				tri[0].y = 431;
			}
			else if (deviation > scale)
			{
				if (GetFlash() == false) return;
				tri[0].y = 301;
			}
			else tri[0].y = 366 - Round( (deviation / scale) * 65.0 );

			tri[1].y = tri[0].y - 10;
			tri[2].y = tri[0].y + 10;
			SelectObject( hDC, gdiLightGreenPen );
			SelectObject( hDC, gdiLightGreenBrush );
			Polygon( hDC, tri, 3 );
		}
		return;
	}

	void MDU::AEPFD_GSI( oapi::Sketchpad2* skp, bool flag, double scale, double deviation )
	{
		skp->SetPen( skpLightGrayPen );
		skp->SetBrush( skpBlackBrush );
		skp->Rectangle( 434, 290, 448, 442 );
		skp->SetBrush( skpLightGrayBrush );
		skp->Ellipse( 437, 297, 445, 305 );
		skp->Ellipse( 437, 329, 445, 337 );
		skp->Ellipse( 437, 395, 445, 403 );
		skp->Ellipse( 437, 427, 445, 435 );
		skp->Line( 434, 366, 448, 366 );

		skp->SetFont( skpSSVBFont_h12w7 );

		char cbuf[8];
		sprintf_s( cbuf, 8, "%dK", (int)scale / 1000 );
		skp->Text( 434, 276, cbuf, 2 );
		skp->Text( 434, 442, cbuf, 2 );

		if (flag)
		{
			// no tracking -> print GS label
			skp->SetPen( skpRedPen );
			skp->SetBrush( skpRedBrush );
			skp->Rectangle( 427, 357, 455, 374 );
			skp->SetTextColor( CR_BLACK );
			skp->Text( 434, 359, "GS", 2 );
		}
		else
		{
			oapi::IVECTOR2 tri[3];
			tri[0].x = 441;// starts at tip moving cw
			tri[1].x = 457;
			tri[2].x = 457;

			// distance BELOW glide path
			if (deviation < -scale)
			{
				if (GetFlash() == false) return;
				tri[0].y = 431;
			}
			else if (deviation > scale)
			{
				if (GetFlash() == false) return;
				tri[0].y = 301;
			}
			else tri[0].y = 366 - Round( (deviation / scale) * 65.0 );

			tri[1].y = tri[0].y - 10;
			tri[2].y = tri[0].y + 10;
			skp->SetPen( skpLightGreenPen );
			skp->SetBrush( skpLightGreenBrush );
			skp->Polygon( tri, 3 );
		}
		return;
	}
}

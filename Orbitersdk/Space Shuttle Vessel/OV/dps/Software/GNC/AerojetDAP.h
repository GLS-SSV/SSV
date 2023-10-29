/****************************************************************************
  This file is part of Space Shuttle Vessel

  Aerojet DAP definition


  Space Shuttle Vessel is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Vessel is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Vessel; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file SSV-LICENSE.txt for more details.

  **************************************************************************/
/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/04/15   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/05/28   GLS
2020/06/20   GLS
2021/06/28   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/12/26   GLS
2021/12/28   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/03/29   GLS
2022/04/02   GLS
2022/04/26   GLS
2022/05/01   GLS
2022/06/06   GLS
2022/06/10   GLS
2022/06/23   GLS
2022/08/05   GLS
2022/09/14   GLS
2022/09/29   GLS
2022/10/21   GLS
2022/12/23   GLS
2023/06/14   GLS
2023/10/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Aerojet DAP definition



  Space Shuttle Ultra is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Ultra is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Ultra; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file Doc\Space Shuttle Ultra\GPL.txt for more details.

  **************************************************************************/
#ifndef _dps_AEROJETDAP_H_
#define _dps_AEROJETDAP_H_


#include "../SimpleGPCSoftware.h"


class FILT1;
class FILT2;
class HYST;
class SignalSampler;
class FADER;


namespace dps
{
class RHC_SOP;
class RPTA_SOP;


/**
 * DAP during entry, TAEM and A/L phases (MM304 and MM305)
 */
class AerojetDAP : public SimpleGPCSoftware
{
private:
	double WGT_SD;// slapdown rate selection weight [slugs]
	double EAS_SD;// slapdown initiation EAS [knots]
	double LD_REL_BIAS;// elevon load relief angle [deg]
	double NWS_LIM;// max NWS deflection [deg]

	double DNWC;// DAP NWS CMD [deg]
	double DBF;// body flap command [deg]

	double ENT_SB_1;
	double ENT_SB_2;
	double ENT_SB_3;
	double ENT_SB_VS;
	double ENT_SB_C1;
	double ENT_SB_C2;
	double ENT_SB_C3;
	double ENT_SB_C4;

	double DSB_MAX;
	double MACH_SBH;
	double DSB_CLOSED;
	double DSB_BIAS_U;
	double DSB_MIN_L;
	double DSB_MIN_U;
	double DSB_MIN_M;

	double ALFERR_LIM;
	double GQALR;
	double DPJET_CUTOFF;
	double PADB;
	double PBDB;
	double VCO;
	double GDQ_MIN;
	double GDQ_MAX;

	double P_STAB;// roll stability rate [deg/s]
	double R_STAB;// yaw stability rate [deg/s]

	double LOWGAIN;

	double MACH_RRXF;

	double QBARLOWQ;
	double QBARLOWMIDQ;
	double QBARHIGHQ;

	double SBDMN;// speedbrake delta minimum velocity [fps]
	double SBDMX;// speedbrake delta maximum velocity [fps]
	double SBDLIM;// speedbrake delta limit [deg]


	bool BodyFlapPBIpressed;// to avoid switch bouncing


	RHC_SOP* pRHC_SOP;
	RPTA_SOP* pRPTA_SOP;


	double DECC;// elevator command [deg]
	double DBFRC;// body flap
	double DAC;// limited aileron command [deg]
	double DRC;// rudder command [deg]
	double DSBC;// speedbrake command [deg]

	short UXCMD;// number of RCS roll jets to fire
	short UYCMD;// number of RCS pitch jets to fire
	short UZCMD;// number of RCS yaw jets to fire


	short DETM_RHC;// pitch RHC trim
	short DATM_RHC;// roll RHC trim
	short DETM_PAN;// pitch panel trim
	short DATM_PAN;// roll panel trim
	short DRT;// NY panel trim


	double VE;// [fps]
	double PHI;// [deg]
	double QBAR;// [psf]
	double Q;// [deg/s]
	double P;// [deg/s]
	double R;// [deg/s]
	double THETA;
	double ALPHA;// [deg]
	double BETA;
	double COSALF;
	double SINALF;
	double COSPHI;
	double SINPHI;
	double COSTH;
	double SINTH;
	double TAS;
	double NY;
	double RC;
	unsigned short TG_END;

	double DEFB;// elevator position [deg]
	double DBFOFB;// body flap position [deg]
	double DSBFB;// speedbrake position [deg]
	double DSBPC;// speedbrake increment [deg]
	double ETRIM;
	double ELFBK;

	// from pitch channel to body flap channel
	double DETRIM;

	// from yaw channel to roll channel
	double DRRCJF;
	double DAY;
	double BETAF;
	double DRPRM;// corrected yaw rate feedback [deg/s]

	// from roll channel to yaw channel
	double PC;// stability axis roll rate command [deg/s]
	double PCOR;// corrected roll rate feedback [deg/s]

	double DRPHI;

	double DATRIM;
	double DRTRIM;
	double DRTI;

	short DBF_MAN;

	unsigned short WRAP;// 0=INH, 1=ENA, 2=ACT
	unsigned short SEL_L_GAIN;
	unsigned short SEL_NO_Y_JET;

	double DEMAN;
	double DAMAN;
	double DRMAN;

	unsigned short WOWLON;
	unsigned short ROLLOUT;
	unsigned short FLATTURN;
	unsigned short FCS_PITCH;// 1=AUTO; 2=CSS
	unsigned short FCS_ROLL;// 1=AUTO; 2=CSS

	FILT1* fltrETRIM;
	FILT1* fltrELFBK;
	FILT1* NZ_FILTER;
	FILT1* PITCH_SHAPING_FILTER;
	FILT1* ALFERR_FILT;
	FILT1* RHC_INT;
	FILT1* BETA_FILTER;
	FILT1* fltrGRH;
	FILT1* fltrDRTRIM;
	FILT1* NY_COMP;
	FILT1* fltrDATRIM;
	FILT1* fltrDRTI;
	FILT1* fltrDETR;// pitch RHC trim integrator
	FILT1* fltrDATR;// roll RHC trim integrator
	FILT1* fltrDBFD;
	FILT2* DNYP_COMP;
	FILT2* fltrNYBF;

	HYST* PITCH_JET_HYSTERESIS;
	HYST* BF_HYSTER;
	HYST* BF_RATE_CMD;
	HYST* ROLL_JET_HYSTERESIS;
	HYST* YAW_JET_HYSTERESIS;

	SignalSampler* BF_DEF_CMD;

	FADER* TRWY_FADE;
	FADER* TNWFADE;

	bool LOWQ;
	bool LOWMIDQ;
	bool HIGHQ;

	double ALFERR_FDC;// alpha error [deg]
	double NZERR;// Nz error [g]
	double QFDC;// rate error for derotation [deg/s]
	double BANKERR;// unlimited bank error [deg]

public:
	explicit AerojetDAP(SimpleGPCSystem* _gpc);
	virtual ~AerojetDAP();

	void Realize() override;

	void ReadILOADs( const std::map<std::string,std::string>& ILOADs ) override;

	void OnPreStep(double simt, double simdt, double mjd) override;

	bool OnMajorModeChange(unsigned int newMajorMode) override;

	bool OnParseLine(const char* keyword, const char* value) override;
	void OnSaveState(FILEHANDLE scn) const override;


private:
	/**
	 * Sets FCS pitch, roll/yaw and speedbrake variables.
	 */
	void SelectFCS( void );

	void SpeedbrakeChannel( void );

	void PitchChannel( double dt );

	void BodyFlapChannel( double dt );

	void RollChannel( double dt );

	void YawChannel( double dt );

	void NosewheelChannel( double dt );


	double ENT_SB_SCHED( void ) const;
	void SB_LIM_BIAS( double &DSB_BIAS, double &DSB_MIN ) const;

	double GQAL_COMP( void ) const;
	double GQAL_COMP_NYJET( void ) const;
	double GDQ_COMP( void ) const;
	double GJET_COMP( void ) const;
	double GTRE_COMP( void ) const;
	double GPRHC_COMP( void ) const;
	double QC_NOM_COMP( void ) const;
	double QC_ALT_COMP( void ) const;
	double GDSB_COMP( void ) const;
	double GD_COMP( double QFDBK ) const;

	double GBFR_SCHED( void ) const;
	double DETD_SCHED_FWD( void ) const;
	double DETD_SCHED_MID( void ) const;
	double DETD_SCHED_AFT( void ) const;
	double GBFMACH_SCHED( void ) const;
	double GBFAUTO_MOD( void ) const;

	double GALRT_COMP( void ) const;
	double GALRD_COMP( void ) const;
	double BANKERR_THRESH( double _BANKERR );
	double BANKERR_THRESH_NYJET( double _BANKERR );
	double GPBANK_COMP( void ) const;
	double PCLIM_COMP( void ) const;
	double GTRA_COMP( void ) const;
	double GDA_COMP( void ) const;
	double KGDA_COMP( void ) const;
	double KDAMLIN_COMP( void ) const;
	double KDAMPAR_COMP( void ) const;
	double DAMAX_COMP( void ) const;
	double GPAY_COMP( void ) const;
	double GBAY_COMP( void ) const;

	double GRH_COMP( void ) const;
	double GDRC_COMP( void ) const;
	double KDRC_COMP( void ) const;
	double GTRR_COMP( void ) const;
	double GRAY_COMP( void ) const;
	double GNYDRM_COMP( void ) const;

	void RECON( void );
};

}

#endif// _dps_AEROJETDAP_H_

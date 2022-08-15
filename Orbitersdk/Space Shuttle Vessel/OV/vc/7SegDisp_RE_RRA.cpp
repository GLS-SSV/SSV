/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/08/24   GLS
2022/08/05   GLS
********************************************/
#include "7SegDisp_RE_RRA.h"
#include "../Atlantis.h"


namespace vc
{
	_7SegDisp_RE_RRA::_7SegDisp_RE_RRA( Atlantis* _sts, const std::string& _ident ):_7SegDisp( _sts, _ident )
	{
	}

	_7SegDisp_RE_RRA::~_7SegDisp_RE_RRA()
	{
	}

	void _7SegDisp_RE_RRA::Realize( void )
	{
		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "A2_SWITCHES_DATA", 16 );
		pDIGI_DIS_SELECT_LAMPTEST.Connect( pBundle, 0 );
		pDIGI_DIS_SELECT_RRbar.Connect( pBundle, 1 );

		pRange.Connect( pBundle, 3 );
		pRangeRate.Connect( pBundle, 4 );
		pElevation.Connect( pBundle, 5 );
		pAzimuth.Connect( pBundle, 6 );

		pBundle = STS()->BundleManager()->CreateBundle( "A1U_SWITCHES_B", 16 );
		pPower_On.Connect( pBundle, 6 );
		return;
	}

	void _7SegDisp_RE_RRA::Controller( void )
	{
		if (!pPower_On.IsSet())
		{
			// off
			next_state[9] = _7SD_STATE_SIGN2OFF;
			next_state[8] = _7SD_STATE_NUMOFF_DOTOFF;
			next_state[7] = _7SD_STATE_NUMOFF_DOTOFF;
			next_state[6] = _7SD_STATE_NUMOFF_DOTOFF;
			next_state[5] = _7SD_STATE_NUMOFF_DOTOFF;
			next_state[4] = _7SD_STATE_SIGN2OFF;
			next_state[3] = _7SD_STATE_NUMOFF_DOTOFF;
			next_state[2] = _7SD_STATE_NUMOFF_DOTOFF;
			next_state[1] = _7SD_STATE_NUMOFF_DOTOFF;
			next_state[0] = _7SD_STATE_NUMOFF_DOTOFF;
		}
		else if (pDIGI_DIS_SELECT_LAMPTEST.IsSet())
		{
			// test
			next_state[9] = _7SD_STATE_SIGN2ON;
			next_state[8] = _7SD_STATE_NUM8_DOTON;
			next_state[7] = _7SD_STATE_NUM8_DOTON;
			next_state[6] = _7SD_STATE_NUM8_DOTON;
			next_state[5] = _7SD_STATE_NUM8_DOTON;
			next_state[4] = _7SD_STATE_SIGN2ON;
			next_state[3] = _7SD_STATE_NUM8_DOTON;
			next_state[2] = _7SD_STATE_NUM8_DOTON;
			next_state[1] = _7SD_STATE_NUM8_DOTON;
			next_state[0] = _7SD_STATE_NUM8_DOTON;
		}
		else if (pDIGI_DIS_SELECT_RRbar.IsSet())
		{
			// range
			double range = pRange.GetVoltage() * 2000;
			char cbuf[8];
			int decimalpoint = 0;
			if (range < 9.99)
			{
				// X.XX0
				sprintf_s( cbuf, 8, "%04.2f0", range );
				decimalpoint = 3;
			}
			else if (range < 99.99)
			{
				// XX.XX
				sprintf_s( cbuf, 8, "%05.2f", range );
				decimalpoint = 2;
			}
			else if (range < 999.9)
			{
				// XXX.X
				sprintf_s( cbuf, 8, "%05.1f", range );
				decimalpoint = 1;
			}
			else if (range < 9999) sprintf_s( cbuf, 8, "%04.0f", range );// XXXX.
			else sprintf_s( cbuf, 8, "9999" );

			for (int i = 3, j = 0; i >= 0; i--, j++)
			{
				if (cbuf[j] == '.') j++;

				next_state[i] = cbuf[j] - 48 + _7SD_STATE_NUM0_DOTOFF;
			}

			next_state[decimalpoint] -= _7SD_STATE_NUM0_DOTON;

			next_state[4] = _7SD_STATE_SIGN2OFF;

			// range rate
			double rangerate = pRangeRate.GetVoltage() * 2000;
			if (fabs( rangerate ) <= 999.9)
			{
				sprintf_s( cbuf, 8, "%05.1f", fabs( rangerate ) );
				decimalpoint = 6;
			}
			else
			{
				sprintf_s( cbuf, 8, "%04.0f", fabs( rangerate ) );
				decimalpoint = 5;
			}

			for (int i = 8, j = 0; i >= 5; i--, j++)
			{
				if (cbuf[j] == '.') j++;

				next_state[i] = cbuf[j] - 48 + _7SD_STATE_NUM0_DOTOFF;
			}

			next_state[decimalpoint] -= _7SD_STATE_NUM0_DOTON;

			if (rangerate > 0) next_state[9] = _7SD_STATE_SIGN2PLUS;
			else if (rangerate < 0) next_state[9] = _7SD_STATE_SIGN2MINUS;
			else next_state[9] = _7SD_STATE_SIGN2OFF;
		}
		else
		{
			// elevation
			double elevation = pElevation.GetVoltage() * 100;
			char cbuf[8];
			sprintf_s( cbuf, 8, "%05.1f", fabs( elevation ) );

			for (int i = 3, j = 0; i >= 0; i--, j++)
			{
				if (cbuf[j] == '.') j++;

				next_state[i] = cbuf[j] - 48 + _7SD_STATE_NUM0_DOTOFF;
			}

			next_state[1] -= _7SD_STATE_NUM0_DOTON;

			if (elevation > 0) next_state[4] = _7SD_STATE_SIGN2PLUS;
			else if (elevation < 0) next_state[4] = _7SD_STATE_SIGN2MINUS;
			else next_state[4] = _7SD_STATE_SIGN2OFF;

			// azimuth
			double azimuth = pAzimuth.GetVoltage() * 100;
			sprintf_s( cbuf, 8, "%05.1f", fabs( azimuth ) );

			for (int i = 8, j = 0; i >= 5; i--, j++)
			{
				if (cbuf[j] == '.') j++;

				next_state[i] = cbuf[j] - 48 + _7SD_STATE_NUM0_DOTOFF;
			}

			next_state[6] -= _7SD_STATE_NUM0_DOTON;

			if (azimuth > 0) next_state[9] = _7SD_STATE_SIGN2PLUS;
			else if (azimuth < 0) next_state[9] = _7SD_STATE_SIGN2MINUS;
			else next_state[9] = _7SD_STATE_SIGN2OFF;
		}
		return;
	}
};
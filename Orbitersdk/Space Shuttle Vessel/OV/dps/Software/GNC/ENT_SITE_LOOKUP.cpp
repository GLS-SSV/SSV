#include "ENT_SITE_LOOKUP.h"
#include "GNCUtilities.h"
#include <MathSSV.h>
#include <EngConst.h>


namespace dps
{
	// K-Loads
	VECTOR3 R_HAC_RW_L = {0.0f/*TODO ?*/, -15500.0f, 0.0f};// (???, V98U9802C, V98U9803C) [ft]
	VECTOR3 R_HAC_RW_R = {0.0f/*TODO ?*/, 15500.0f, 0.0f};// (???, V98U9805C, V98U9806C) [ft]



	constexpr double _EARTH_RADIUS_EQUATOR = 20902263.7794;// Orbiter value [ft]
	constexpr double _ELLIPT = 0.0;// Orbiter value

	static VECTOR3 _GEODETIC_TO_EF( double LAT_GEOD, double LON, double ALT )
	{
		double CLAT, SLAT, DUM, DUM1, R_EF_EQUAT;

		CLAT = cos(LAT_GEOD);
		SLAT = sin(LAT_GEOD);
		DUM = pow(1.0 - _ELLIPT, 2);
		DUM1 = _EARTH_RADIUS_EQUATOR / sqrt(CLAT*CLAT + SLAT * SLAT*DUM);
		R_EF_EQUAT = (DUM1 + ALT)*CLAT;
		return _V(R_EF_EQUAT*cos(LON), R_EF_EQUAT*sin(LON), (DUM*DUM1 + ALT)*SLAT);
	}


	ENT_SITE_LOOKUP::ENT_SITE_LOOKUP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "ENT_SITE_LOOKUP" ),
		FIRST_PASS(1), PRIME_RUNWAY_INDEX(1), ALT_SITES_RESET_INH(0), TAL_ALT_SITE_INIT(0)
	{
		return;
	}

	ENT_SITE_LOOKUP::~ENT_SITE_LOOKUP( void )
	{
		return;
	}

	void ENT_SITE_LOOKUP::OnPreStep( double simt, double simdt, double mjd )
	{
		ENTRY_SITE_LOOKUP_INIT();
		return;
	}

	void ENT_SITE_LOOKUP::ENTRY_SITE_LOOKUP_INIT( void )
	{
		if (FIRST_PASS == 1)
		{
			unsigned short TAL_ABORT_DECLARED = 0;// TODO

			WriteCOMPOOL_IS( SCP_AREA_SEL, 1 );
			PRIME_RUNWAY_INDEX = 1;
			//TAC_SEL = (2 * AREA_SEL) - 1;
			FIRST_PASS = 0;

			/*if (TAL_ABORT_DECLARED)// TODO TAL
			{
				WriteCOMPOOL_IS( SCP_AREA_SEL, AREA_SEL_OPS_1 );
				PRIME_RUNWAY_INDEX = RW_SEL_OPS_1;
				//TAC_SEL = TAC_SEL_OPS_1;
				TAL_ALT_SITE_INIT = 1;
			}*/

			//AUTO_CHANNEL_ID = TACAN_ID_MAXI(TAC_SEL);

			ENTRY_RUNWAY_SITE_LOOKUP();
		}

		if (ReadCOMPOOL_IS( SCP_NEW_AREA ) == 1)
		{
			PRIME_RUNWAY_INDEX = 1;
			WriteCOMPOOL_IS( SCP_RW_ID_UPP, 0 );
			//TAC_SEL = (2 * AREA_SEL) - 1;
			//AUTO_CHANNEL_ID = TACAN_ID_MAXI(TAC_SEL);
			//TAC_CHAN_OLD(1) = 0;
			//TAC_CHAN_OLD(2) = 0;
			//TAC_CHAN_OLD(3) = 0;
			WriteCOMPOOL_IS( SCP_NEW_AREA, 0 );

			ENTRY_RUNWAY_SITE_LOOKUP();
		}

		if (ReadCOMPOOL_IS( SCP_PRI_SEL ) == 1)
		{
			PRIME_RUNWAY_INDEX = 1;
			WriteCOMPOOL_IS( SCP_PRI_SEL, 0 );
			ALT_SITES_RESET_INH = 1;

			ENTRY_RUNWAY_SITE_LOOKUP();
		}

		if (ReadCOMPOOL_IS( SCP_SEC_SEL ) == 1)
		{
			PRIME_RUNWAY_INDEX = 2;
			WriteCOMPOOL_IS( SCP_SEC_SEL, 0 );
			ALT_SITES_RESET_INH = 1;

			ENTRY_RUNWAY_SITE_LOOKUP();
		}

		/*if (TAC_CHANGE == 1)
		{
			// TODO TACAN
		}*/

		/*if (TAC_SEL_LAST == TAC_SEL)
		{
			// TODO TACAN
		}*/
		return;
	}

	void ENT_SITE_LOOKUP::ENTRY_RUNWAY_SITE_LOOKUP( void )
	{
		unsigned short J = ReadCOMPOOL_IS( SCP_AREA_SEL );
		char RUNWAY_NAME_PSL[5];
		char RUNWAY_NAME_SSL[5];

		ReadCOMPOOL_AC( SCP_RUNWAY_NAME, (2 * J) - 1, RUNWAY_NAME_PSL, 90, 5 );
		ReadCOMPOOL_AC( SCP_RUNWAY_NAME, 2 * J, RUNWAY_NAME_SSL, 90, 5 );
		WriteCOMPOOL_C( SCP_RUNWAY_NAME_PSL, RUNWAY_NAME_PSL, 5 );
		WriteCOMPOOL_C( SCP_RUNWAY_NAME_SSL, RUNWAY_NAME_SSL, 5 );

		if (ALT_SITES_RESET_INH == 0)
		{
			if (TAL_ALT_SITE_INIT == 0)
			{
				WriteCOMPOOL_AIS( SCP_ALT_SITE_INDEX, 1, ReadCOMPOOL_AIS( SCP_ALTERNATE_SITE_1, J, 45 ), 2 );
				WriteCOMPOOL_AIS( SCP_ALT_SITE_INDEX, 2, ReadCOMPOOL_AIS( SCP_ALTERNATE_SITE_2, J, 45 ), 2 );
			}
			else
			{
				TAL_ALT_SITE_INIT = 0;
			}
		}
		else
		{
			ALT_SITES_RESET_INH = 0;
		}

		unsigned short L;
		if (PRIME_RUNWAY_INDEX == 1)
		{
			L = (2 * J) - 1;
			WriteCOMPOOL_IS( SCP_RW_SELECT, 1 );
			WriteCOMPOOL_C( SCP_RW_NAME_SEL, RUNWAY_NAME_PSL, 5 );
		}
		else
		{
			L = 2 * J;
			WriteCOMPOOL_IS( SCP_RW_SELECT, 0 );
			WriteCOMPOOL_C( SCP_RW_NAME_SEL, RUNWAY_NAME_SSL, 5 );
		}

		WriteCOMPOOL_IS( SCP_RW_NAME, L );
		
		char ctmp[5];
		ReadCOMPOOL_AC( SCP_RUNWAY_NAME, L, ctmp, 90, 5 );
		WriteCOMPOOL_C( SCP_SEL_SITE_ID, ctmp, 5 );

		float LAT = ReadCOMPOOL_ASS( SCP_RW_LAT, L, 90 );
		float LON = ReadCOMPOOL_ASS( SCP_RW_LON, L, 90 );
		float ALT_RW = ReadCOMPOOL_ASS( SCP_RUNWAY_ALT, L, 90 );
		WriteCOMPOOL_SS( SCP_ALT_RW, ALT_RW );
		float AZIMUTH_RW = ReadCOMPOOL_ASS( SCP_RW_AZIMUTH, L, 90 );
		WriteCOMPOOL_SS( SCP_AZIMUTH_RW, AZIMUTH_RW );
		WriteCOMPOOL_IS( SCP_HUD_RW_LENGTH, static_cast<unsigned short>(ReadCOMPOOL_ASS( SCP_RW_LENGTH, L, 90 )) );
		WriteCOMPOOL_SS( SCP_DELH_MSL_ELLIPSOID_RW, ReadCOMPOOL_ASS( SCP_RW_DELH, L, 90 ) );
		WriteCOMPOOL_SS( SCP_ANGLE_CORR_TNTOMAG_RW, ReadCOMPOOL_ASS( SCP_RW_MAG_VAR, L, 90 ) );
		//unsigned short K = RW_MSBLS_INDEX(L);
		//MLS_AVAIL = 0;

		MATRIX3 M_EFTORW = EF_TO_RUNWAY( LAT, LON, AZIMUTH_RW );
		VECTOR3 R_LS_EF = _GEODETIC_TO_EF( LAT, LON, ALT_RW );
		MATRIX3 M_EFTOTD_RW = EF_TO_TOPDET( LAT, LON );
		WriteCOMPOOL_MS( SCP_M_EFTORW, M_EFTORW );
		WriteCOMPOOL_VD( SCP_R_LS_EF, R_LS_EF );
		WriteCOMPOOL_MS( SCP_M_EFTOTD_RW, M_EFTOTD_RW );

		VECTOR3 R_CC_L_PRI = R_LS_EF + tmul( M_EFTORW, R_HAC_RW_L );
		VECTOR3 R_CC_R_PRI = R_LS_EF + tmul( M_EFTORW, R_HAC_RW_R );
		WriteCOMPOOL_VS( SCP_R_CC_L_PRI, R_CC_L_PRI );
		WriteCOMPOOL_VS( SCP_R_CC_R_PRI, R_CC_R_PRI );

		WriteCOMPOOL_SS( SCP_R_CC_LMAG_PRI, static_cast<float>(length( R_CC_L_PRI )) );
		WriteCOMPOOL_SS( SCP_R_CC_RMAG_PRI, static_cast<float>(length( R_CC_R_PRI )) );

		/*if (K > 0)
		{
			// TODO MSBLS
		}*/
		return;
	}

	void ENT_SITE_LOOKUP::ENTRY_TACAN_SITE_LOOKUP( void )
	{
		// TODO TACAN
		return;
	}

	bool ENT_SITE_LOOKUP::OnParseLine( const char* keyword, const char* value )
	{
		if  (!_strnicmp( keyword, "FIRST_PASS", 10 ))
		{
			unsigned int tmp = 0;
			sscanf_s( value, "%u", &tmp );
			if (tmp <= 1) FIRST_PASS = tmp;
			return true;
		}
		else if  (!_strnicmp( keyword, "PRIME_RUNWAY_INDEX", 18 ))
		{
			unsigned int tmp = 0;
			sscanf_s( value, "%u", &tmp );
			if (tmp <= 1) PRIME_RUNWAY_INDEX = tmp;
			return true;
		}
		/*else if  (!_strnicmp( keyword, "ALT_SITES_RESET_INH", 19 ))
		{
			unsigned int tmp = 0;
			sscanf_s( value, "%u", &tmp );
			if (tmp <= 1) ALT_SITES_RESET_INH = tmp;
			return true;
		}
		else if  (!_strnicmp( keyword, "TAL_ALT_SITE_INIT", 17 ))
		{
			unsigned int tmp = 0;
			sscanf_s( value, "%u", &tmp );
			if (tmp <= 1) TAL_ALT_SITE_INIT = tmp;
			return true;
		}*/
		else return false;
	}

	void ENT_SITE_LOOKUP::OnSaveState( FILEHANDLE scn ) const
	{
		oapiWriteScenario_int( scn, "FIRST_PASS", FIRST_PASS );
		oapiWriteScenario_int( scn, "PRIME_RUNWAY_INDEX", PRIME_RUNWAY_INDEX );
		//oapiWriteItem_int( scn, "ALT_SITES_RESET_INH", ALT_SITES_RESET_INH );
		//oapiWriteItem_int( scn, "TAL_ALT_SITE_INIT", TAL_ALT_SITE_INIT );
		return;
	}
}

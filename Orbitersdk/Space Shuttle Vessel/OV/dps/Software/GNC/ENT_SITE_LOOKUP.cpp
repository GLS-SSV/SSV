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
		for (auto& x : RUNWAY_NAME) x = new char[5];
		return;
	}

	ENT_SITE_LOOKUP::~ENT_SITE_LOOKUP( void )
	{
		for (auto x : RUNWAY_NAME) delete[] x;
		return;
	}

	void ENT_SITE_LOOKUP::ReadILOADs( const std::map<std::string,std::string>& ILOADs )
	{
		GetValILOAD( "ALTERNATE_SITE_1", ILOADs, 45, ALTERNATE_SITE_1 );
		GetValILOAD( "ALTERNATE_SITE_2", ILOADs, 45, ALTERNATE_SITE_2 );
		GetValILOAD( "RUNWAY_ALT", ILOADs, 90, RUNWAY_ALT );
		GetValILOAD( "RUNWAY_NAME", ILOADs, 90, 5, RUNWAY_NAME );
		GetValILOAD( "RW_AZIMUTH", ILOADs, 90, RW_AZIMUTH );
		GetValILOAD( "RW_DELH", ILOADs, 90, RW_DELH );
		GetValILOAD( "RW_LAT", ILOADs, 90, RW_LAT );
		GetValILOAD( "RW_LENGTH", ILOADs, 90, RW_LENGTH );
		GetValILOAD( "RW_LON", ILOADs, 90, RW_LON );
		GetValILOAD( "RW_MAG_VAR", ILOADs, 90, RW_MAG_VAR );
		return;
	}

	void ENT_SITE_LOOKUP::OnPostStep( double simt, double simdt, double mjd )
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
			//TAC_SEL = (2 * AREA_SEL) – 1;
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
		memcpy( RUNWAY_NAME_PSL, RUNWAY_NAME[(2 * J) - 1 - 1], 5 );
		memcpy( RUNWAY_NAME_SSL, RUNWAY_NAME[2 * J - 1], 5 );
		WriteCOMPOOL_C( SCP_RUNWAY_NAME_PSL, RUNWAY_NAME_PSL, 5 );
		WriteCOMPOOL_C( SCP_RUNWAY_NAME_SSL, RUNWAY_NAME_SSL, 5 );

		if (ALT_SITES_RESET_INH == 0)
		{
			if (TAL_ALT_SITE_INIT == 0)
			{
				WriteCOMPOOL_AIS( SCP_ALT_SITE_INDEX, 1, ALTERNATE_SITE_1[J - 1], 2 );
				WriteCOMPOOL_AIS( SCP_ALT_SITE_INDEX, 2, ALTERNATE_SITE_2[J - 1], 2 );
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
		WriteCOMPOOL_C( SCP_SEL_SITE_ID, RUNWAY_NAME[L - 1], 5 );
		float LAT = RW_LAT[L - 1];
		float LON = RW_LON[L - 1];
		float ALT_RW = RUNWAY_ALT[L - 1];
		WriteCOMPOOL_SS( SCP_ALT_RW, ALT_RW );
		float AZIMUTH_RW = RW_AZIMUTH[L - 1];
		WriteCOMPOOL_SS( SCP_AZIMUTH_RW, AZIMUTH_RW );
		WriteCOMPOOL_IS( SCP_HUD_RW_LENGTH, RW_LENGTH[L - 1] );
		WriteCOMPOOL_SS( SCP_DELH_MSL_ELLIPSOID_RW, RW_DELH[L - 1] );
		WriteCOMPOOL_SS( SCP_ANGLE_CORR_TNTOMAG_RW, RW_MAG_VAR[L - 1] );
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

	bool ENT_SITE_LOOKUP::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 301:
			case 302:
			case 303:
			case 304:
			case 305:
				return true;
			default:
				return false;
		}
	}

	bool ENT_SITE_LOOKUP::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void ENT_SITE_LOOKUP::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}
}

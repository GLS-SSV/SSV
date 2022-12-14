/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/04/07   GLS
2020/04/15   GLS
2020/05/01   GLS
2020/06/12   GLS
2020/06/20   GLS
2020/06/21   GLS
2020/08/24   GLS
2021/06/18   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/01/10   GLS
2022/02/15   GLS
2022/06/13   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/12/01   indy91
********************************************/
#include "LandingSite.h"
#include "../Atlantis.h"
#include "../mission/Mission.h"
#include <MathSSV.h>
#include <sstream>
#include <map>


namespace dps
{
	LandingSite::LandingSite( SimpleGPCSystem* _gpc ):SimpleGPCSoftware( _gpc, "LandingSite" )
	{
		LSID = 1;
		return;
	}

	LandingSite::~LandingSite( void )
	{
		return;
	}

	void LandingSite::Realize( void )
	{
		hEarth = STS()->GetGravityRef();

		LoadLandingSiteList( STS()->GetMissionData()->GetLandingSiteTable() );

		CalculateLandingSiteData();
		return;
	}

	bool LandingSite::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void LandingSite::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	void LandingSite::OnPreStep( double simt, double simdt, double mjd )
	{
		// check if landing site changed
		unsigned short _LSID = ReadCOMPOOL_IS( SCP_LSID );
		if (LSID != _LSID)
		{
			LSID = _LSID;
			CalculateLandingSiteData();
		}
		return;
	}

	bool LandingSite::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 101:
			case 102:
			case 103:
			case 104:
			case 105:
			case 106:
			case 301:
			case 302:
			case 303:
			case 304:
			case 305:
			case 601:
			case 602:
			case 603:
				return true;
			default:
				return false;
		}
	}

	void LandingSite::LoadLandingSiteList( const std::string& table )
	{
		// load runway database
		// format: id,site name,rw name,lat(n)[rad],lon(e)[rad],amsl[m],hdg[deg],lgt[ft]
		std::map<std::string,RunwayData> rwDB;
		std::string line;
		char str1[32];
		char str2[32];
		char str3[32];
		int id;
		RunwayData rw1;
		RunwayData rw2;

		ifstream fs;
		fs.open( "Config\\SSV_RunwayDB.csv" );
		if (fs.is_open())
		{
			while (std::getline( fs, line ))
			{
				sscanf_s( line.c_str(), "%[^,],%[^,],%[^,],%lf,%lf,%lf,%lf,%hu", str1, 32, str2, 32, str3, 32, &rw1.Lat, &rw1.Lon, &rw1.AMSL, &rw1.Hdg, &rw1.Lgt );
				rw1.Name = str3;

				rwDB.insert( std::pair<std::string,RunwayData>( std::string( str1 ), rw1 ) );
			}
			fs.close();
		}
		else throw std::exception( "SSV_RunwayDB.csv not found!" );

		// load defined runways to landing site list
		// format: id,rwPri,rwSec
		istringstream ss( table );
		while (std::getline( ss, line ))
		{
			sscanf_s( line.c_str(), "%d,%[^,],%[^,]", &id, str1, 32, str2, 32 );

			// handle \r
			{
				int len = strlen( str2 ) - 1;
				if (str2[len] == '\r') str2[len] = 0;
			}

			rw1 = rwDB[str1];
			rw2 = rwDB[str2];

			// check for missing entry
			if (rw1.Name.empty()) throw std::exception( "Runway not found!" );
			if (rw2.Name.empty()) throw std::exception( "Runway not found!" );

			vLandingSites.push_back( LandingSiteData( rw1, rw2 ) );
		}

		rwDB.clear();
		return;
	}

	void LandingSite::CalculateLandingSiteData( void )
	{
		double radLat, radLong, AMSL, degHdg;
		std::string sName;

		// PRI
		vLandingSites[LSID - 1].GetRwyPosition( true, radLat, radLong, AMSL );
		degHdg = vLandingSites[LSID - 1].GetRwyHeading( true );
		sName = vLandingSites[LSID - 1].GetPriRwyName();

		VECTOR3 RwyStart;
		oapiEquToLocal( hEarth, radLong, radLat, oapiGetSize( hEarth ) + AMSL, &RwyStart );// get position vector
		RwyStart = _V( RwyStart.x, RwyStart.z, RwyStart.y ) * MPS2FPS;// correct axis and convert to feet
		VECTOR3 z = -unit( RwyStart );
		VECTOR3 EastDir = _V( -sin( radLong ), cos( radLong ), 0 );
		VECTOR3 x = RotateVector( z, RAD * (degHdg - 90.0), EastDir );
		VECTOR3 y = crossp( z, x );

		WriteCOMPOOL_C( SCP_PRI_ID, sName.c_str(), 5 );
		WriteCOMPOOL_SS( SCP_PRI_HDG, static_cast<float>(degHdg) );
		WriteCOMPOOL_VS( SCP_PRI_POS, RwyStart );
		MATRIX3 m3tmp = _M( x.x, x.y, x.z, y.x, y.y, y.z, z.x, z.y, z.z );
		WriteCOMPOOL_MS( SCP_PRI_G2R, m3tmp );
		WriteCOMPOOL_IS( SCP_PRI_LEN, vLandingSites[LSID - 1].GetRwyLength( true ) );

		// SEC
		vLandingSites[LSID - 1].GetRwyPosition( false, radLat, radLong, AMSL );
		degHdg = vLandingSites[LSID - 1].GetRwyHeading( false );
		sName = vLandingSites[LSID - 1].GetSecRwyName();

		oapiEquToLocal( hEarth, radLong, radLat, oapiGetSize( hEarth ) + AMSL, &RwyStart );// get position vector
		RwyStart = _V( RwyStart.x, RwyStart.z, RwyStart.y ) * MPS2FPS;// correct axis and convert to feet
		z = -unit( RwyStart );
		EastDir = _V( -sin( radLong ), cos( radLong ), 0 );
		x = RotateVector( z, RAD * (degHdg - 90.0), EastDir );
		y = crossp( z, x );

		WriteCOMPOOL_C( SCP_SEC_ID, sName.c_str(), 5 );
		WriteCOMPOOL_SS( SCP_SEC_HDG, static_cast<float>(degHdg) );
		WriteCOMPOOL_VS( SCP_SEC_POS, RwyStart );
		m3tmp = _M( x.x, x.y, x.z, y.x, y.y, y.z, z.x, z.y, z.z );
		WriteCOMPOOL_MS( SCP_SEC_G2R, m3tmp );
		WriteCOMPOOL_IS( SCP_SEC_LEN, vLandingSites[LSID - 1].GetRwyLength( false ) );
		return;
	}
}

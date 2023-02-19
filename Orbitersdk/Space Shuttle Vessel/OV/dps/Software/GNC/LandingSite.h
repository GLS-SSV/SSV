/****************************************************************************
  This file is part of Space Shuttle Vessel

  Landing Site definition


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
2020/04/07   GLS
2020/05/08   GLS
2020/06/20   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/06/13   GLS
2022/09/29   GLS
2022/12/23   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Landing Site definition



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
#ifndef __LANDINGSITE
#define __LANDINGSITE


#include "../SimpleGPCSoftware.h"
#include <string>
#include <vector>


namespace dps
{
	class LandingSite:public SimpleGPCSoftware
	{
		private:
			struct RunwayData
			{
				std::string Name;
				double Lat;// latitude [rad]
				double Lon;// longitude [rad]
				double Hdg;// heading [deg]
				unsigned short Lgt;// length [ft]
				double AMSL;// altitude above mean sea level [m]
			};

			class LandingSiteData
			{
				private:
					RunwayData Pri;
					RunwayData Sec;
				public:
					LandingSiteData( RunwayData _Pri, RunwayData _Sec ):Pri(_Pri), Sec(_Sec)
					{
					}

					~LandingSiteData()
					{
					}

					void GetRwyPosition( bool pri, double& radLat, double& radLong, double &AMSL ) const
					{
						if (pri)
						{
							radLat = Pri.Lat;
							radLong = Pri.Lon;
							AMSL = Pri.AMSL;
						}
						else
						{
							radLat = Sec.Lat;
							radLong = Sec.Lon;
							AMSL = Sec.AMSL;
						}
					}

					unsigned short GetRwyLength( bool pri ) const
					{
						if(pri) return Pri.Lgt;
						else return Sec.Lgt;
					}

					double GetRwyHeading( bool pri ) const
					{
						if(pri) return Pri.Hdg;
						else return Sec.Hdg;
					}

					const std::string& GetPriRwyName( void ) const
					{
						return Pri.Name;
					}

					const std::string& GetSecRwyName( void ) const
					{
						return Sec.Name;
					}

					double GetRwyAMSL( bool pri ) const
					{
						if(pri) return Pri.AMSL;
						else return Sec.AMSL;
					}
			};

			unsigned short LSID;

			std::vector<LandingSiteData> vLandingSites;

			OBJHANDLE hEarth;

			void LoadLandingSiteList( const std::string& table );

			/**
			 * Calculates and updates runway data in COMPOOL.
			 */
			void CalculateLandingSiteData( void );

		public:
			explicit LandingSite( SimpleGPCSystem* _gpc );
			virtual ~LandingSite( void );

			void Realize( void ) override;

			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;

			void OnPreStep( double simt, double simdt, double mjd ) override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;
	};

}

#endif// __LANDINGSITE

/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2020/08/24   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/09/29   GLS
2023/09/03   GLS
********************************************/
#include "RA.h"
#include "../Atlantis.h"
#include <EngConst.h>
#include <MathSSV.h>


// radar position (assumes both radars are in the same place, centered in the Y axis)
constexpr double RADAR_POS_X = 11.53;
constexpr double RADAR_POS_Z = -3.48;


namespace gnc
{
	RadarAltimeter::RadarAltimeter( AtlantisSubsystemDirector* _director, const string& _ident, int ID ):AtlantisSubsystem( _director, _ident )
	{
		this->ID = ID;
		data = 0;
		return;
	}

	RadarAltimeter::~RadarAltimeter( void )
	{
		return;
	}

	void RadarAltimeter::Realize( void )
	{
		DiscreteBundle* bundle = BundleManager()->CreateBundle( "RDR_ALT", 16 );
		power.Connect( bundle, ID - 1 );
		return;
	}

	void RadarAltimeter::OnPostStep( double simt, double simdt, double mjd )
	{
		if (power == false) return;

		// calc alt (assumes the beam target is at the same elevation as what is directly below the vehicle)
		double tmp_alt = STS()->GetAltitude( ALTMODE_GROUND );
		VECTOR3 ofs = STS()->GetOrbiterCoGOffset();
		double cosp = cos( STS()->GetPitch() );

		tmp_alt += ((RADAR_POS_Z + ofs.y) * cosp) + ((RADAR_POS_X + ofs.z) * sin( STS()->GetPitch() ));// correct for radar position
		tmp_alt /= (cosp * cos( STS()->GetBank() ));// correct for vehicle attitude
		int alt = Round( tmp_alt * MPS2FPS );

		// assemble data
		data = 1;// control

		if ((alt >= 0) && (alt <= 5000))// lock at 5kft
		{
			data |= 2;// validity
			data |= alt << 2;// data
		}

		// odd parity
		unsigned short tmp = data;
		tmp ^= tmp >> 8;
		tmp ^= tmp >> 4;
		tmp ^= tmp >> 2;
		tmp ^= tmp >> 1;
		data |= ((~tmp) & 1) << 15;
		return;
	}

	unsigned short RadarAltimeter::GetData( void ) const
	{
		if (power == false) return 0;
		return data;
	}
}

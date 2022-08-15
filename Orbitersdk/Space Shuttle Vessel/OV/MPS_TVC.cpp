#include "MPS_TVC.h"
#include "Atlantis.h"
#include "APU.h"
#include <MathSSV.h>
#include <cassert>


MPS_TVC::MPS_TVC( AtlantisSubsystemDirector* _director ):AtlantisSubsystem( _director, "MPS_TVC" )
{
	Pcurpos[0] = 0.0;
	Pcurpos[1] = 0.0;
	Pcurpos[2] = 0.0;
	Ycurpos[0] = 0.0;
	Ycurpos[1] = 0.0;
	Ycurpos[2] = 0.0;

	Ptgtpos[0] = 0.0;
	Ptgtpos[1] = 0.0;
	Ptgtpos[2] = 0.0;
	Ytgtpos[0] = 0.0;
	Ytgtpos[1] = 0.0;
	Ytgtpos[2] = 0.0;
	return;
}

MPS_TVC::~MPS_TVC( void )
{
	return;
}


void MPS_TVC::Realize( void )
{
	pAPU[0] = dynamic_cast<APU*>(director->GetSubsystemByName( "APU1" ));
	assert( (pAPU[0] != NULL) && "ATVC::Realize.pAPU[0]" );
	pAPU[1] = dynamic_cast<APU*>(director->GetSubsystemByName( "APU2" ));
	assert( (pAPU[1] != NULL) && "ATVC::Realize.pAPU[1]" );
	pAPU[2] = dynamic_cast<APU*>(director->GetSubsystemByName( "APU3" ));
	assert( (pAPU[2] != NULL) && "ATVC::Realize.pAPU[2]" );

	// set positions for initial step
	STS()->SetSSMEGimbalAngles( 0, Pcurpos[0], Ycurpos[0] );
	STS()->SetSSMEGimbalAngles( 1, Pcurpos[1], Ycurpos[1] );
	STS()->SetSSMEGimbalAngles( 2, Pcurpos[2], Ycurpos[2] );
	return;
}

bool MPS_TVC::OnParseLine( const char* keyword, const char* value )
{
	double tmp = 0;

	if (!_stricmp( keyword, "CenterPitch" ))
	{
		sscanf_s( value, "%lf", &tmp );
		Pcurpos[0] = Ptgtpos[0] = range( -10.5, tmp, 10.5 );
	}
	else if (!_stricmp( keyword, "CenterYaw" ))
	{
		sscanf_s( value, "%lf", &tmp );
		Ycurpos[0] = Ytgtpos[0] = range( -8.5, tmp, 8.5 );
	}
	else if (!_stricmp( keyword, "LeftPitch" ))
	{
		sscanf_s( value, "%lf", &tmp );
		Pcurpos[1] = Ptgtpos[1] = range( -10.5, tmp, 10.5 );
	}
	else if (!_stricmp( keyword, "LeftYaw" ))
	{
		sscanf_s( value, "%lf", &tmp );
		Ycurpos[1] = Ytgtpos[1] = range( -8.5, tmp, 8.5 );
	}
	else if (!_stricmp( keyword, "RightPitch" ))
	{
		sscanf_s( value, "%lf", &tmp );
		Pcurpos[2] = Ptgtpos[2] = range( -10.5, tmp, 10.5 );
	}
	else if (!_stricmp( keyword, "RightYaw" ))
	{
		sscanf_s( value, "%lf", &tmp );
		Ycurpos[2] = Ytgtpos[2] = range( -8.5, tmp, 8.5 );
	}
	else return false;

	return true;
}

void MPS_TVC::OnSaveState( FILEHANDLE scn ) const
{
	oapiWriteScenario_float( scn, "CenterPitch", Pcurpos[0] );
	oapiWriteScenario_float( scn, "CenterYaw", Ycurpos[0] );
	oapiWriteScenario_float( scn, "LeftPitch", Pcurpos[1] );
	oapiWriteScenario_float( scn, "LeftYaw", Ycurpos[1] );
	oapiWriteScenario_float( scn, "RightPitch", Pcurpos[2] );
	oapiWriteScenario_float( scn, "RightYaw", Ycurpos[2] );
	return;
}

void MPS_TVC::OnPostStep( double simt, double simdt, double mjd )
{
	double HydSys1Press = pAPU[0]->GetHydraulicPressure();
	double HydSys2Press = pAPU[1]->GetHydraulicPressure();
	double HydSys3Press = pAPU[2]->GetHydraulicPressure();

	UpdateActuator( HydSys1Press, HydSys3Press, Pcurpos[0], Ptgtpos[0], simdt, 10.5 );
	UpdateActuator( HydSys3Press, HydSys1Press, Ycurpos[0], Ytgtpos[0], simdt, 8.5 );
	STS()->SetSSMEGimbalAngles( 0, Pcurpos[0], Ycurpos[0] );

	UpdateActuator( HydSys2Press, HydSys1Press, Pcurpos[1], Ptgtpos[1], simdt, 10.5 );
	UpdateActuator( HydSys1Press, HydSys2Press, Ycurpos[1], Ytgtpos[1], simdt, 8.5 );
	STS()->SetSSMEGimbalAngles( 1, Pcurpos[1], Ycurpos[1] );

	UpdateActuator( HydSys3Press, HydSys2Press, Pcurpos[2], Ptgtpos[2], simdt, 10.5 );
	UpdateActuator( HydSys2Press, HydSys3Press, Ycurpos[2], Ytgtpos[2], simdt, 8.5 );
	STS()->SetSSMEGimbalAngles( 2, Pcurpos[2], Ycurpos[2] );
	return;
}

void MPS_TVC::Command( unsigned int eng, double pitch, double yaw )
{
	assert( (eng <= 2) && "MPS_TVC::Command.eng" );

	Ptgtpos[eng] = pitch;
	Ytgtpos[eng] = yaw;
	return;
}

void MPS_TVC::UpdateActuator( double hydpri, double hydsec, double& cur, double tgt, double dt, double lim )
{
	if ((hydpri < 1500) && (hydsec < 1500)) return;

	double temp = tgt - cur;
	if (fabs( temp ) < (dt * 15.0))// HACK 10-20º/s limit
	{
		cur = tgt;
	}
	else
	{
		cur += sign( temp ) * dt * 15.0;
	}

	cur = range( -lim, cur, lim );
	return;
}

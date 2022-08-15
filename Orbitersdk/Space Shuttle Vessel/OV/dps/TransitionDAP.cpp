/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/04/07   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/08/05   GLS
********************************************/
#include "TransitionDAP.h"
#include "..\Atlantis.h"
#include "SSME_Operations.h"
#include <MathSSV.h>
#include "..\ParameterValues.h"
#include <cassert>


namespace dps
{

	constexpr double MINUSZ_TARGET_DV_NOM = 1.2192;// m/s (4 fps)
	constexpr double MINUSZ_TARGET_DV_TAL = 3.3528;// m/s (11 fps)
	constexpr double MINUSZ_TARGET_DT_RTLS = 10;// sec


	TransitionDAP::TransitionDAP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "TransitionDAP" )
	{
		MinusZTranslation = false;

		ETSepMinusZDV = 0;
		ETSepMinusZDT = -1;
		return;
	}

	TransitionDAP::~TransitionDAP( void )
	{
		return;
	}

	void TransitionDAP::OnPostStep( double simt, double simdt, double mjd )
	{
		if (pSSME_Operations->GetMECOConfirmedFlag() == true)
		{
			WriteCOMPOOL_IS( SCP_FWD_DAP_AUTO_LT, 1 );
			WriteCOMPOOL_IS( SCP_FWD_ROT_ROLL_DISC_LT, 1 );
			WriteCOMPOOL_IS( SCP_FWD_ROT_PITCH_DISC_LT, 1 );
			WriteCOMPOOL_IS( SCP_FWD_ROT_YAW_DISC_LT, 1 );
		}
		// HACK conflicting info about which flag does what
		if (pSSME_Operations->GetZeroThrustFlag() == true)
		{
			// hold attitude
			NullRates( simdt );

			if (MinusZTranslation == true)
			{
				// fire cmd
				ZTransCommand.SetLine( -1.0f );

				if (GetMajorMode() == 601)
				{
					// RTLS
					if (ETSepMinusZDT == -1) ETSepMinusZDT = simt + MINUSZ_TARGET_DT_RTLS;

					if (ETSepMinusZDT <= simt)
					{
						ZTransCommand.ResetLine();
						MinusZTranslation = false;
						SetMajorMode( 602 );

						oapiWriteLog( "-Z Translation terminated" );
					}
				}
				else if (0)// TODO add TAL abort flag
				{
					// TAL
					VECTOR3 ThrustVector;
					STS()->GetThrustVector( ThrustVector );
					ETSepMinusZDV += (ThrustVector.y / STS()->GetMass()) * simdt;

					if (ETSepMinusZDV >= MINUSZ_TARGET_DV_TAL)
					{
						ZTransCommand.ResetLine();
						MinusZTranslation = false;
						SetMajorMode( 104 );

						oapiWriteLog( "-Z Translation terminated" );
					}
				}
				else
				{
					// NOM
					VECTOR3 ThrustVector;
					STS()->GetThrustVector( ThrustVector );
					ETSepMinusZDV += (ThrustVector.y / STS()->GetMass()) * simdt;

					if (ETSepMinusZDV >= MINUSZ_TARGET_DV_NOM)
					{
						ZTransCommand.ResetLine();
						MinusZTranslation = false;
						SetMajorMode( 104 );

						oapiWriteLog( "-Z Translation terminated" );
					}
				}
			}
			else
			{
				// TODO man control?
			}
		}
		return;
	}

	void TransitionDAP::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "THRUSTER_CMD", 16 );
		RotThrusterCommands[0].Connect( pBundle, 0 );
		RotThrusterCommands[1].Connect( pBundle, 1 );
		RotThrusterCommands[2].Connect( pBundle, 2 );
		ZTransCommand.Connect( pBundle, 5 );

		pSSME_Operations = dynamic_cast<SSME_Operations*> (FindSoftware( "SSME_Operations" ));
		assert( (pSSME_Operations != NULL) && "TransitionDAP::Realize.pSSME_Operations" );
		return;
	}

	bool TransitionDAP::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			//case 102:
			case 103:
			//case 104:// TAL only?
				return true;
			default:
				return false;
		}
	}

	void TransitionDAP::MinusZTranslationCommand()
	{
		MinusZTranslation = true;

		oapiWriteLog( "-Z Translation comanded" );
		return;
	}

	void TransitionDAP::NullRates( double simdt )
	{
		const VECTOR3 PRI_LIMITS = _V(0.005, 0.005, 0.005);

		VECTOR3 Error;
		STS()->GetAngularVel( Error );
		Error = _V( Error.x, -Error.y, Error.z ); // convert from Orbitersim to body axis frame
		Error = -Error * DEG;

		VECTOR3 Limits;
		double timeAcc = max(1.0, oapiGetTimeAcceleration());
		double MaxThrusterLevel = 1.0/timeAcc;

		VECTOR3 Torque;// HACK probably should use other values because of the ET
		Torque.data[PITCH]=ORBITER_PITCH_TORQUE;
		Torque.data[YAW]=ORBITER_YAW_TORQUE;
		Torque.data[ROLL]=ORBITER_ROLL_TORQUE;
		VECTOR3 PMI;
		STS()->GetPMI(PMI);

		for(unsigned int i=0;i<3;i++)
		{
			Limits.data[i] = max(PRI_LIMITS.data[i], 0.5*RotationRateChange(STS()->GetMass(), PMI.data[i], Torque.data[i]/timeAcc, simdt));
		}

		for(unsigned int i=0;i<3;i++)
		{
			if(abs(Error.data[i])>Limits.data[i])
			{
				double thrusterLevel = MaxThrusterLevel;
				double scale = abs(Error.data[i])/Limits.data[i];
				if(scale < 2) thrusterLevel = MaxThrusterLevel/3.0;
				else if(scale < 5) thrusterLevel = MaxThrusterLevel*(0.667);
				RotThrusterCommands[i].SetLine(static_cast<float>(thrusterLevel*sign(Error.data[i])));
			}
			else
			{
				RotThrusterCommands[i].ResetLine();
			}
		}
	}
}
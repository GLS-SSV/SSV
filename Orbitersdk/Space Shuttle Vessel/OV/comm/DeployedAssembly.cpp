/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/02/16   GLS
2021/08/18   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/01/31   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "DeployedAssembly.h"
#include "../Atlantis.h"
#include "../PayloadBay.h"
#include "../../CommonDefs.h"
#include "../meshres_Ku.h"
#include <cassert>


namespace comm
{
	const static char* MESHNAME_KU = "SSV\\Ku_band_DA";

	const VECTOR3 KU_OFFSET = _V( 0.0, 0.0, 0.0 );

	const VECTOR3 KUBANDANTENNA_GIMBAL_REF = _V( 2.17932, 0.687325, 8.276878 );// when stowed [m] (Xo+628.43, Yo+85.8, Zo+443.875)
	const VECTOR3 KUBANDANTENNA_ALPHA_DIR = _V( 0.5, 0.0, 0.866025 );
	const VECTOR3 KUBANDANTENNA_BETA_DIR = _V( -0.488028, 0.826098, 0.281763 );


	DeployedAssembly::DeployedAssembly( AtlantisSubsystemDirector* _director ):AtlantisSubsystem( _director, "DeployedAssembly" )
	{
		alpha = 124.3;
		beta = -27.5;
		LockingPin1 = 1;
		LockingPin2 = 1;

		mesh_idx = MESH_UNDEFINED;

		hMesh = oapiLoadMeshGlobal( MESHNAME_KU );
	}

	DeployedAssembly::~DeployedAssembly()
	{
	}

	void DeployedAssembly::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "KuBandAntennaControl", 16 );
		BoomStowEnableII.Connect( pBundle, 1 );
		AlphaMIP.Connect( pBundle, 2 );
		BetaMIP.Connect( pBundle, 3 );
		GimbalLockMotors.Connect( pBundle, 4 );
		GimbalMotorAlpha.Connect( pBundle, 5 );
		GimbalMotorBeta.Connect( pBundle, 6 );
		AlphaEncoder.Connect( pBundle, 7 );
		BetaEncoder.Connect( pBundle, 8 );

		AddMesh();
		AddAnimation();
		SetKuGimbalAngles();
		return;
	}

	void DeployedAssembly::OnPostStep( double simt, double simdt, double mjd )
	{
		// locking pins
		if (GimbalLockMotors.GetVoltage() > 0)
		{
			// lock
			if (LockingPin1 < 1.0)
			{
				// drive 1
				LockingPin1 += LOCKINGPIN1_SPEED * simdt;
				if (LockingPin1 > 1.0) LockingPin1 = 1.0;
			}
			else
			{
				// drive 2
				LockingPin2 += LOCKINGPIN2_SPEED * simdt;
				if (LockingPin2 > 1.0) LockingPin2 = 1.0;
			}
		}
		else if (GimbalLockMotors.GetVoltage() < 0)
		{
			// unlock
			// drive 1
			LockingPin1 -= LOCKINGPIN1_SPEED * simdt;
			if (LockingPin1 < 0.0) LockingPin1 = 0.0;
			// drive 2
			LockingPin2 -= LOCKINGPIN2_SPEED * simdt;
			if (LockingPin2 < 0.0) LockingPin2 = 0.0;
		}

		// gimbal motors
		double newalpha = alpha;
		double newbeta = beta;
		if ((LockingPin1 < 0.5) || (LockingPin2 < 0.5))
		{
			newalpha += GimbalMotorAlpha.GetVoltage() * simdt;
			newbeta += GimbalMotorBeta.GetVoltage() * simdt;
		}

		// check for stop
		if (newalpha > 206) newalpha = 206;
		else if (newalpha < -154) newalpha = -154;
		if (newbeta > 85) newbeta = 85;
		else if (newbeta < -75) newbeta = -75;

		// MIPs (use "passed by position" logic instead of "is at position")
		if (((newalpha >= ALPHA_MASTER_PULSE_INDEX) && (ALPHA_MASTER_PULSE_INDEX >= alpha)) || ((newalpha <= ALPHA_MASTER_PULSE_INDEX) && (ALPHA_MASTER_PULSE_INDEX <= alpha))) AlphaMIP.SetLine();
		else AlphaMIP.ResetLine();
		if (((newbeta >= BETA_MASTER_PULSE_INDEX) && (BETA_MASTER_PULSE_INDEX >= beta)) || ((newbeta <= BETA_MASTER_PULSE_INDEX) && (BETA_MASTER_PULSE_INDEX <= beta))) BetaMIP.SetLine();
		else BetaMIP.ResetLine();

		// save and output positions
		alpha = newalpha;
		beta = newbeta;
		AlphaEncoder.SetLine( (float)alpha );
		BetaEncoder.SetLine( (float)beta );

		// output boom stow enable II
		BoomStowEnableII.SetLine( 5.0f * (int)(LockingPin2 == 1.0) );

		// animation
		SetKuGimbalAngles();
		return;
	}

	bool DeployedAssembly::OnParseLine( const char* line )
	{
		if (!_strnicmp( line, "ALPHA", 5 ))
		{
			sscanf_s( line + 5, "%lf", &alpha );
			if (alpha > 206) alpha = 206;
			else if (alpha < -154) alpha = -154;
			return true;
		}
		else if (!_strnicmp( line, "BETA", 4 ))
		{
			sscanf_s( line + 4, "%lf", &beta );
			if (beta > 85) beta = 85;
			else if (beta < -75) beta = -75;
			return true;
		}
		else if (!_strnicmp( line, "LOCKINGPIN1", 11 ))
		{
			sscanf_s( line + 11, "%lf", &LockingPin1 );
			return true;
		}
		else if (!_strnicmp( line, "LOCKINGPIN2", 11 ))
		{
			sscanf_s( line + 11, "%lf", &LockingPin2 );
			return true;
		}
		return false;
	}

	void DeployedAssembly::OnSaveState( FILEHANDLE scn ) const
	{
		oapiWriteScenario_float( scn, "ALPHA", alpha );
		oapiWriteScenario_float( scn, "BETA", beta );
		if (LockingPin1 < 1) oapiWriteScenario_float( scn, "LOCKINGPIN1", LockingPin1 );
		if (LockingPin2 < 1) oapiWriteScenario_float( scn, "LOCKINGPIN2", LockingPin2 );
		return;
	}

	void DeployedAssembly::AddAnimation( void )
	{
		PayloadBay* pPayloadBay = dynamic_cast<PayloadBay*>(director->GetSubsystemByName( "PayloadBay" ));
		assert( (pPayloadBay != NULL) && "DeployedAssembly::AddAnimation.pPayloadBay" );

		static UINT KuBandDAGrp[6] = {GRP_DEA_KU,
						GRP_DEA_MOUNT_KU,
						GRP_DEA_EA_CABLES_KU,
						GRP_ALPHA_GIMBAL_BASE_FOIL_KU,
						GRP_DEA_A_KU,
						GRP_DEA_B_KU };
		MGROUP_TRANSFORM* KuBandDA = new MGROUP_TRANSFORM( mesh_idx, KuBandDAGrp, 6 );
		ANIMATIONCOMPONENT_HANDLE parent = STS()->AddAnimationComponent( pPayloadBay->GetDAindex(), 0.0, 1.0, KuBandDA, pPayloadBay->GetDAparent() );
		SaveAnimation( KuBandDA );

		static UINT KuBandAGrp[1] = {GRP_ALPHA_GIMBAL_KU};
		MGROUP_ROTATE* KuBandA = new MGROUP_ROTATE( mesh_idx, KuBandAGrp, 1, KUBANDANTENNA_GIMBAL_REF, KUBANDANTENNA_ALPHA_DIR, (float)(360.0 * RAD) );
		anim_kualpha = STS()->CreateAnimation( 0.773611 );// 124.3º
		parent = STS()->AddAnimationComponent( anim_kualpha, 0.0, 1.0, KuBandA, parent );
		SaveAnimation( KuBandA );

		static UINT KuBandBGrp[9] = {GRP_BETA_GIMBAL_KU,
						GRP_GIMBAL_LOCK_ASSEMBLY_KU,
						GRP_WIDE_BEAM_HORN_KU,
						GRP_RATE_SENSOR_ASSEMBLY_KU,
						GRP_RATE_SENSOR_ASSEMBLY_BRACKET_KU,
						GRP_COMPOSITE_DISH_ASSEMBLY_KU,
						GRP_COMPOSITE_DISH_SUPPORT_SPINES_KU,
						GRP_DISH_ATTACHMENT_BRACKET_KU,
						GRP_ANTENNA_FEED_KU};
		MGROUP_ROTATE* KuBandB = new MGROUP_ROTATE( mesh_idx, KuBandBGrp, 9, KUBANDANTENNA_GIMBAL_REF, KUBANDANTENNA_BETA_DIR, (float)(160.0 * RAD) );
		anim_kubeta = STS()->CreateAnimation( 0.296875 );// -27.5º
		STS()->AddAnimationComponent( anim_kubeta, 0.0, 1.0, KuBandB, parent );
		SaveAnimation( KuBandB );
		return;
	}

	void DeployedAssembly::AddMesh( void )
	{
		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + KU_OFFSET;
		mesh_idx = STS()->AddMesh( hMesh, &ofs );
		STS()->SetMeshVisibilityMode( mesh_idx, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
		return;
	}

	void DeployedAssembly::SetKuGimbalAngles( void )
	{
		STS()->SetAnimation( anim_kualpha, (alpha + 154.0) / 360.0 );
		STS()->SetAnimation( anim_kubeta, (beta + 75.0) / 160.0 );
	}
}

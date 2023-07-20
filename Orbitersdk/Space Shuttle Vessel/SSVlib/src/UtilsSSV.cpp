/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/08/24   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include <UtilsSSV.h>


double CalculateThrustPower( VESSEL* v, const VECTOR3& vtx_lt, const VECTOR3& vtx_rt, const VECTOR3& vtx_lb, const VECTOR3& vtx_rb )
{
	VECTOR3 D, DG, B, BG;
	VECTOR3 E1, E2, VP;
	VECTOR3 T, P, Q;
	VECTOR3 TUV;

	double fTotalPower = 0.0;

	for (DWORD c = 0; c < oapiGetVesselCount(); c++)
	{
		OBJHANDLE hVessel = oapiGetVesselByIndex( c );
		if (hVessel == v->GetHandle()) continue;
		//Ignore all vessels further away as 1500m
		v->GetRelativePos( hVessel, VP );
		if (length( VP ) > 1500.0) continue;

		VESSEL* pV = oapiGetVesselInterface( hVessel );

		for (DWORD t = 0; t < pV->GetThrusterCount(); t++)
		{
			THRUSTER_HANDLE thT = pV->GetThrusterHandleByIndex( t );

			//Only account powerful thrusters
			if (pV->GetThrusterMax( thT ) > 5000.0)
			{
				double Power = pV->GetThrusterMax( thT ) * pV->GetThrusterLevel( thT ) * pV->GetThrusterIsp( thT );
				pV->GetThrusterDir( thT, D );
				pV->GlobalRot( D, DG );
				pV->GetThrusterRef( thT, B );
				pV->Local2Global( B, BG );
				DG = -DG;

				// First triangle
				E1 = vtx_rt - vtx_lt;
				E2 = vtx_lb - vtx_lt;
				T = BG - vtx_lt;
				P = crossp( DG , E2 );
				Q = crossp( T, E1 );
				TUV = _V( dotp( Q, E2 ), dotp( P, T ), dotp( Q, DG ) ) * (1.0 / dotp( P, E1 ));
				if (TUV.x > 0.0 && TUV.y >= 0.0 && TUV.y < 1.0 && TUV.z >= 0.0 && TUV.z < 1.0)
				{
					// add exhaust energy to flame trench
					fTotalPower += Power;
				}

				// Second triangle
				E1 = vtx_lb - vtx_lt;
				E2 = vtx_rb - vtx_lt;
				T = BG - vtx_lt;
				P = crossp( DG , E2 );
				Q = crossp( T, E1 );
				TUV = _V( dotp( Q, E2 ), dotp( P, T ), dotp( Q, DG ) ) * (1.0 / dotp( P, E1 ));
				if (TUV.x > 0.0 && TUV.y >= 0.0 && TUV.y < 1.0 && TUV.z >= 0.0 && TUV.z < 1.0)
				{
					// add exhaust energy to flame trench
					fTotalPower += Power;
				}
			}
		}
	}
	return fTotalPower;
}

double GetMassAndCoGOfAttachedObject( VESSEL* vp, ATTACHMENTHANDLE ah, VECTOR3& CoG )
{
	double mass = 0.0;
	CoG = _V( 0.0, 0.0, 0.0 );

	OBJHANDLE hV = vp->GetAttachmentStatus( ah );
	if (hV)
	{
		VESSEL* v = oapiGetVesselInterface( hV );
		if (v)
		{
			VECTOR3 childCoG;
			mass = GetMassAndCoG( v, childCoG );
			// get CoG of payload in Orbiter frame
			VECTOR3 rpos;
			v->GetRelativePos( vp->GetHandle(), rpos );
			MATRIX3 LocalToGlob, ChildToGlob;
			vp->GetRotationMatrix( LocalToGlob );
			v->GetRotationMatrix( ChildToGlob );
			CoG = tmul( LocalToGlob, mul( ChildToGlob, childCoG ) + rpos );
		}
	}
	return mass;
}

double GetMassAndCoG( VESSEL* v, VECTOR3& CoG )
{
	double mass = v->GetMass();
	CoG = _V( 0.0, 0.0, 0.0 );
	// iterate over attached children
	DWORD ahCount = v->AttachmentCount( false );
	for (DWORD i = 0; i < ahCount; i++)
	{
		ATTACHMENTHANDLE ah = v->GetAttachmentHandle( false, i );
		OBJHANDLE hV = v->GetAttachmentStatus( ah );
		if (hV)
		{
			VESSEL* pV = oapiGetVesselInterface( hV );
			VECTOR3 childCoG;
			double childMass = GetMassAndCoG( pV, childCoG );
			// convert child CoG to CoG in frame of this vessel
			VECTOR3 rpos;
			pV->GetRelativePos( v->GetHandle(), rpos );
			MATRIX3 LocalToGlob, ChildToGlob;
			v->GetRotationMatrix( LocalToGlob );
			pV->GetRotationMatrix( ChildToGlob );
			childCoG = tmul( LocalToGlob, mul( ChildToGlob, childCoG ) + rpos );
			// calculate CoG of payload relative to center of Orbiter mesh
			CoG += childCoG * childMass;
			mass += childMass;

			//oapiWriteLogV( "Parent: %s Child: %s dist: %f", v->GetName(), pV->GetName(), length(childCoG) );
		}
	}
	CoG = CoG / mass;
	return mass;
}

// ======================================================
// Created by ssvmeshc 1.1
// Input file: VC_external.msh
// ======================================================

#ifndef _MESH_VC_EXTERNAL_H_
#define _MESH_VC_EXTERNAL_H_

inline constexpr unsigned int NUMGRP_VCEXT = 6;
inline constexpr unsigned int NUMMAT_VCEXT = 3;
inline constexpr unsigned int NUMTEX_VCEXT = 4;

inline constexpr unsigned int GRP_COCKPIT1_VCEXT	=	0;	//cockpit1
inline constexpr unsigned int GRP_COCKPIT2_VCEXT	=	1;	//cockpit2
inline constexpr unsigned int GRP_COCKPIT3_VCEXT	=	2;	//cockpit3
inline constexpr unsigned int GRP_PURGEBARRIER_VCEXT	=	3;	//PurgeBarrier
inline constexpr unsigned int GRP_HRSI_VCEXT	=	4;	//HRSI
inline constexpr unsigned int GRP_MIDDECK_VCEXT	=	5;	//middeck

inline constexpr unsigned int MAT_MAINMATERIAL_VCEXT	=	0;	//MainMaterial
inline constexpr unsigned int MAT_PURGESEAL_VCEXT	=	1;	//PurgeSeal
inline constexpr unsigned int MAT_MIDDECK_VCEXT	=	2;	//Middeck

inline constexpr unsigned int TEX_SSV_OV_STSVC01_VCEXT	=	1;	//SSV\OV\stsvc01.dds
inline constexpr unsigned int TEX_SSV_OV_STSVC02_VCEXT	=	2;	//SSV\OV\stsvc02.dds
inline constexpr unsigned int TEX_SSV_OV_STSVC03_VCEXT	=	3;	//SSV\OV\stsvc03.dds
inline constexpr unsigned int TEX_SSV_OV_OV104_5THMOD_VCEXT	=	4;	//SSV\OV\OV-104_5thmod.dds

#endif// _MESH_VC_EXTERNAL_H_

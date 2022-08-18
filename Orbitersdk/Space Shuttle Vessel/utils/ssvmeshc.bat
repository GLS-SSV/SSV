@echo off
pause

:set SSVMESHC=..\ssvmeshc\Debug\ssvmeshc.exe
set SSVMESHC=..\ssvmeshc\Release\ssvmeshc.exe

set TGT_OV=..\OV\


:::: misc ::::
set SRC_MISC=..\..\..\Meshes\SSV\

%SSVMESHC% %SRC_MISC%Ku_band_DA.msh -o%TGT_OV%meshres_Ku.h -pGRP_ -s_KU
%SSVMESHC% %SRC_MISC%MPM_Port.msh -o%TGT_OV%meshres_MPM_Port.h -pGRP_ -s_MPM_Port
%SSVMESHC% %SRC_MISC%MPM_Starboard.msh -o%TGT_OV%meshres_MPM_Starboard.h -pGRP_ -s_MPM_Starboard
%SSVMESHC% %SRC_MISC%RMS_Port.msh -o%TGT_OV%meshres_RMS_Port.h -pGRP_ -s_RMS_Port

set TGT_Xenon_Lights=..\Xenon_Lights\
%SSVMESHC% %SRC_MISC%KSC_xenon_lights_trailer.msh -o%TGT_Xenon_Lights%meshres_xenon.h -pGRP_ -s_XENON



:::: Centaur ::::
set SRC_CENTAUR=..\..\..\Meshes\SSV\Centaur\
set TGT_CENTAUR=..\Centaur\

%SSVMESHC% %SRC_CENTAUR%CentaurG.msh -o%TGT_CENTAUR%meshres_Centaur_G.h -pGRP_ -s_G
%SSVMESHC% %SRC_CENTAUR%CentaurG_Prime.msh -o%TGT_CENTAUR%meshres_Centaur_GPrime.h -pGRP_ -s_GPRIME



:::: CT ::::
set SRC_CT=..\..\..\Meshes\SSV\CT\
set TGT_CT=..\CT\

%SSVMESHC% %SRC_CT%mainbody_2004.msh -o%TGT_CT%meshres_crawler.h -pGRP_ -s_CT
%SSVMESHC% %SRC_CT%mainbody_1980.msh -o%TGT_CT%meshres_crawler_1980.h -pGRP_ -s_CT1980
%SSVMESHC% %SRC_CT%panels.msh -o%TGT_CT%meshres_crawler_vc.h -pGRP_ -s_VC
%SSVMESHC% %SRC_CT%drivetrucks.msh -o%TGT_CT%meshres_drivetruck.h -pGRP_ -s_TRUCK



:::: IUS ::::
set SRC_IUS=..\..\..\Meshes\SSV\IUS\
set TGT_IUS=..\IUS_SRM2\

%SSVMESHC% %SRC_IUS%IUS_SRM2.msh -o%TGT_IUS%meshres_IUS_SRM2.h -pGRP_ -s_IUS_SRM2



:::: LC39 ::::
set SRC_LC39=..\..\..\Meshes\SSV\LC39\
set TGT_LC39=..\LC39\

%SSVMESHC% %SRC_LC39%FSS.msh -o%TGT_LC39%meshres_FSS.h -pGRP_ -s_FSS
%SSVMESHC% %SRC_LC39%LC39A_hardstand.msh -o%TGT_LC39%meshres_Hardstand.h -pGRP_ -s_HARDSTAND
%SSVMESHC% %SRC_LC39%RSS.msh -o%TGT_LC39%meshres_RSS.h -pGRP_ -s_RSS



:::: MLP ::::
set SRC_MLP=..\..\..\Meshes\SSV\MLP\
set TGT_MLP=..\MLP\

%SSVMESHC% %SRC_MLP%MLP.msh -o%TGT_MLP%meshres_MLP.h -pGRP_ -s_MLP



:::: OBSS ::::
set SRC_OBSS=..\..\..\Meshes\SSV\OBSS\
set TGT_OBSS=..\OBSS\

%SSVMESHC% %SRC_OBSS%OBSS.msh -o%TGT_OBSS%meshres_OBSS.h -pGRP_ -s_OBSS



:::: OV ::::
set SRC_OV=..\..\..\Meshes\SSV\OV\

%SSVMESHC% %SRC_OV%OV.msh -a

%SSVMESHC% %SRC_OV%OV.msh -o%TGT_OV%meshres.h -pGRP_ -m -bMAT_ -t -eTEX_
%SSVMESHC% %SRC_OV%VC.msh -o%TGT_OV%meshres_vc.h -pGRP_ -s_VC
%SSVMESHC% %SRC_OV%VC_external.msh -o%TGT_OV%meshres_vcext.h -pGRP_ -s_VCEXT -m -bMAT_ -n_VCEXT -t -eTEX_ -r_VCEXT
%SSVMESHC% %SRC_OV%MidDeck.msh -o%TGT_OV%meshres_vc_middeck.h -pGRP_ -s_MD_VC

%SSVMESHC% %SRC_OV%CISS_Common.msh -o%TGT_OV%meshres_CISS_Common.h -pGRP_ -s_CISS
%SSVMESHC% %SRC_OV%ExtAL.msh -o%TGT_OV%meshres_ExtAL.h -pGRP_ -s_ExtAL
%SSVMESHC% %SRC_OV%IUS_ASE.msh -o%TGT_OV%meshres_IUS_ASE.h -pGRP_ -s_IUS_ASE
%SSVMESHC% %SRC_OV%ODS.msh -o%TGT_OV%meshres_ODS.h -pGRP_ -s_ODS
%SSVMESHC% %SRC_OV%TAA.msh -o%TGT_OV%meshres_TAA.h -pGRP_ -s_TAA

%SSVMESHC% %SRC_OV%panelA1L.msh -o%TGT_OV%meshres_vc_a1l.h -pGRP_ -s_A1L_VC
%SSVMESHC% %SRC_OV%panelA1R.msh -o%TGT_OV%meshres_vc_a1r.h -pGRP_ -s_A1R_VC
%SSVMESHC% %SRC_OV%panelA1U.msh -o%TGT_OV%meshres_vc_a1u.h -pGRP_ -s_A1U_VC
%SSVMESHC% %SRC_OV%panelA2.msh -o%TGT_OV%meshres_vc_a2.h -pGRP_ -s_A2_VC
%SSVMESHC% %SRC_OV%panelA3.msh -o%TGT_OV%meshres_vc_a3.h -pGRP_ -s_A3_VC
%SSVMESHC% %SRC_OV%panelA4.msh -o%TGT_OV%meshres_vc_a4.h -pGRP_ -s_A4_VC
%SSVMESHC% %SRC_OV%panelA6U.msh -o%TGT_OV%meshres_vc_a6u.h -pGRP_ -s_A6U_VC -t -eTEX_ -r_A6U_VC
%SSVMESHC% %SRC_OV%panelA7A3.msh -o%TGT_OV%meshres_vc_a7a3.h -pGRP_ -s_A7A3_VC
%SSVMESHC% %SRC_OV%panelA7U.msh -o%TGT_OV%meshres_vc_a7u.h -pGRP_ -s_A7U_VC
%SSVMESHC% %SRC_OV%panelA8A1.msh -o%TGT_OV%meshres_vc_a8a1.h -pGRP_ -s_A8A1_VC
%SSVMESHC% %SRC_OV%panelA8A2.msh -o%TGT_OV%meshres_vc_a8a2.h -pGRP_ -s_A8A2_VC
%SSVMESHC% %SRC_OV%panelA8A3.msh -o%TGT_OV%meshres_vc_a8a3.h -pGRP_ -s_A8A3_VC
%SSVMESHC% %SRC_OV%panelA12A1.msh -o%TGT_OV%meshres_vc_A12A1.h -pGRP_ -s_A12A1_VC -m -bMAT_ -n_A12A1_VC
%SSVMESHC% %SRC_OV%panelA12A2.msh -o%TGT_OV%meshres_vc_A12A2.h -pGRP_ -s_A12A2_VC
%SSVMESHC% %SRC_OV%panelA134.msh -o%TGT_OV%meshres_vc_a134.h -pGRP_ -s_A134_VC -m -bMAT_ -n_A134_VC

%SSVMESHC% %SRC_OV%panelC2.msh -o%TGT_OV%meshres_vc_c2.h -pGRP_ -s_C2_VC -t -eTEX_ -r_C2_VC
%SSVMESHC% %SRC_OV%panelC3.msh -o%TGT_OV%meshres_vc_c3.h -pGRP_ -s_C3_VC -t -eTEX_ -r_C3_VC

%SSVMESHC% %SRC_OV%panelF2.msh -o%TGT_OV%meshres_vc_f2.h -pGRP_ -s_F2_VC
%SSVMESHC% %SRC_OV%panelF3.msh -o%TGT_OV%meshres_vc_f3.h -pGRP_ -s_F3_VC
%SSVMESHC% %SRC_OV%panelF4.msh -o%TGT_OV%meshres_vc_f4.h -pGRP_ -s_F4_VC
%SSVMESHC% %SRC_OV%panelF6.msh -o%TGT_OV%meshres_vc_f6.h -pGRP_ -s_F6_VC -m -bMAT_ -n_F6_VC
%SSVMESHC% %SRC_OV%panelF7.msh -o%TGT_OV%meshres_vc_f7.h -pGRP_ -s_F7_VC -m -bMAT_ -n_F7_VC
%SSVMESHC% %SRC_OV%panelF8.msh -o%TGT_OV%meshres_vc_f8.h -pGRP_ -s_F8_VC -m -bMAT_ -n_F8_VC
%SSVMESHC% %SRC_OV%panelF9.msh -o%TGT_OV%meshres_vc_f9.h -pGRP_ -s_F9_VC

%SSVMESHC% %SRC_OV%panelL1.msh -o%TGT_OV%meshres_vc_l1.h -pGRP_ -s_L1_VC
%SSVMESHC% %SRC_OV%panelL2.msh -o%TGT_OV%meshres_vc_l2.h -pGRP_ -s_L2_VC
%SSVMESHC% %SRC_OV%panelL4.msh -o%TGT_OV%meshres_vc_l4.h -pGRP_ -s_L4_VC
%SSVMESHC% %SRC_OV%panelL9.msh -o%TGT_OV%meshres_vc_l9.h -pGRP_ -s_L9_VC
%SSVMESHC% %SRC_OV%panelL10_IUS.msh -o%TGT_OV%meshres_vc_l10_ius.h -pGRP_ -s_L10_IUS_VC
%SSVMESHC% %SRC_OV%panelL12U_SSP_IUS.msh -o%TGT_OV%meshres_vc_l12u_ius.h -pGRP_ -s_L12U_IUS_VC
%SSVMESHC% %SRC_OV%panelL12U_SSP_Centaur.msh -o%TGT_OV%meshres_vc_l12u_centaur.h -pGRP_ -s_L12U_CENTAUR_VC

%SSVMESHC% %SRC_OV%panelO1.msh -o%TGT_OV%meshres_vc_o1.h -pGRP_ -s_O1_VC
%SSVMESHC% %SRC_OV%panelO2.msh -o%TGT_OV%meshres_vc_o2.h -pGRP_ -s_O2_VC
%SSVMESHC% %SRC_OV%panelO3.msh -o%TGT_OV%meshres_vc_o3.h -pGRP_ -s_O3_VC
%SSVMESHC% %SRC_OV%panelO5.msh -o%TGT_OV%meshres_vc_o5.h -pGRP_ -s_O5_VC
%SSVMESHC% %SRC_OV%panelO6.msh -o%TGT_OV%meshres_vc_o6.h -pGRP_ -s_O6_VC
%SSVMESHC% %SRC_OV%panelO7.msh -o%TGT_OV%meshres_vc_o7.h -pGRP_ -s_O7_VC
%SSVMESHC% %SRC_OV%panelO8.msh -o%TGT_OV%meshres_vc_o8.h -pGRP_ -s_O8_VC
%SSVMESHC% %SRC_OV%panelO9.msh -o%TGT_OV%meshres_vc_o9.h -pGRP_ -s_O9_VC
%SSVMESHC% %SRC_OV%panelO13.msh -o%TGT_OV%meshres_vc_o13.h -pGRP_ -s_O13_VC
%SSVMESHC% %SRC_OV%panelO14.msh -o%TGT_OV%meshres_vc_o14.h -pGRP_ -s_O14_VC
%SSVMESHC% %SRC_OV%panelO15.msh -o%TGT_OV%meshres_vc_o15.h -pGRP_ -s_O15_VC
%SSVMESHC% %SRC_OV%panelO16.msh -o%TGT_OV%meshres_vc_o16.h -pGRP_ -s_O16_VC
%SSVMESHC% %SRC_OV%panelO17.msh -o%TGT_OV%meshres_vc_o17.h -pGRP_ -s_O17_VC

%SSVMESHC% %SRC_OV%panelR1.msh -o%TGT_OV%meshres_vc_r1.h -pGRP_ -s_R1_VC
%SSVMESHC% %SRC_OV%panelR2.msh -o%TGT_OV%meshres_vc_r2.h -pGRP_ -s_R2_VC
%SSVMESHC% %SRC_OV%panelR4.msh -o%TGT_OV%meshres_vc_r4.h -pGRP_ -s_R4_VC
%SSVMESHC% %SRC_OV%panelR10.msh -o%TGT_OV%meshres_vc_r10.h -pGRP_ -s_R10_VC
%SSVMESHC% %SRC_OV%panelR13L.msh -o%TGT_OV%meshres_vc_r13l.h -pGRP_ -s_R13L_VC
%SSVMESHC% %SRC_OV%panelR13U.msh -o%TGT_OV%meshres_vc_r13u.h -pGRP_ -s_R13U_VC

%SSVMESHC% %SRC_OV%PLBLinerBay13.msh -o%TGT_OV%meshres_bay13liner.h -pGRP_ -s_BAY13LINER
%SSVMESHC% %SRC_OV%PLBMLIBay13.msh -o%TGT_OV%meshres_bay13mli.h -pGRP_ -s_BAY13MLI



:::: SLC6 ::::
set SRC_SLC6=..\..\..\Meshes\SSV\SLC6\
set TGT_SLC6=..\SLC6\

%SSVMESHC% %SRC_SLC6%SAB.msh -o%TGT_SLC6%meshres_SAB.h -pGRP_ -s_SAB
%SSVMESHC% %SRC_SLC6%AT.msh -o%TGT_SLC6%meshres_AT.h -pGRP_ -s_AT
%SSVMESHC% %SRC_SLC6%LaunchMount.msh -o%TGT_SLC6%meshres_Pad.h -pGRP_ -s_SLC6_PAD



:::: VAB ::::
set SRC_VAB=..\..\..\Meshes\SSV\VAB\
set TGT_VAB=..\VAB\
%SSVMESHC% %SRC_VAB%exterior_1980.msh -o%TGT_VAB%meshres.h -pGRP_ -s_VAB



pause
@echo on

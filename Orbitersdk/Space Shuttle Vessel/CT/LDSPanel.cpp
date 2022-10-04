/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/06/12   GLS
2020/06/14   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "LDSPanel.h"
#include <MathSSV.h>
#include "Crawler.h"
#include "meshres_crawler_vc.h"
#include "Crawler_defs.h"
#include <list>
#include <EngConst.h>


namespace vc
{

	LDS::LDS(Crawler *_v, const std::string &_ident, vc::CRAWLER_CAB _cab)
		:CrawlerPanel(_v ,_ident, _cab)
	{
		if(_cab == FWD) CabSelectionSwitchPosition = CAB1;
		else CabSelectionSwitchPosition = CAB3;
	}


	LDS::~LDS()
	{
		// clean up animations
		for(unsigned int i=0;i<vpAnimations.size();i++) delete vpAnimations.at(i);
		for(unsigned int i=0;i<LDSAnimation.size();i++) delete LDSAnimation.at(i);
	}

	ATTACHMENTHANDLE LDS::FindNearestAttachment(VESSEL** pV) const
	{

		VECTOR3 gattach;


		std::vector< std::pair<VESSEL*, ATTACHMENTHANDLE> > attachments;
		OBJHANDLE hv = NULL;
		VESSEL *pv = NULL;
		std::string name;
		name.clear();

		V()->Local2Global(MLP_ATTACH_POS, gattach);

		for(DWORD i=0; i<oapiGetVesselCount(); ++i)
		{
			hv = oapiGetVesselByIndex(i);
			pv = oapiGetVesselInterface(hv);

			name = pv->GetClassNameA();
			if ((name.find( "SSV_LC39" ) != std::string::npos) || name == "SSV_VAB")
			{
				for(DWORD j=0; j<pv->AttachmentCount(false); j++)
				{
					ATTACHMENTHANDLE attach = pv->GetAttachmentHandle(false,j);
					if(!_strnicmp(pv->GetAttachmentId(attach),"XMLP",4))
					{
						attachments.push_back(std::make_pair(pv, attach));
					}
				}
			}
		}

		if (attachments.size() == 0) return NULL;// no vessels

		//sprintf(oapiDebugString(),"FOUND %lf ATTACHMENTS",attachments.end());

		//ALL XMLP ATTACHMENTS COMPLETED
		//DETERMINING SHORTEST DISTANCE

		VECTOR3 pos, dir, rot;
		VECTOR3 gpos;
		std::vector< std::pair<VESSEL*, ATTACHMENTHANDLE> >::iterator res;
		double distance = -1;

		for(std::vector< std::pair<VESSEL*, ATTACHMENTHANDLE> >::iterator ai = attachments.begin(); ai != attachments.end(); ++ai)
		{
			VESSEL* v = ai->first;
			ATTACHMENTHANDLE ah = ai->second;
			v->GetAttachmentParams(ah,pos,dir,rot);
			v->Local2Global(pos,gpos);
			double temp = dist(gpos,gattach);

			if(distance == -1 || temp < distance)
			{
				distance = temp;
				res = ai;
			}
		}
		//sprintf(oapiDebugString(),"%lf",distance);
		*pV = res->first;
		return res->second;
	}

	double LDS::CalculateDistanceBetweenAttachments()
	{
		VESSEL* pTgt;
		ATTACHMENTHANDLE ahTgt = FindNearestAttachment(&pTgt);

		if (ahTgt == NULL) return 0;

		VECTOR3 CabPos;
		if(CabSelectionSwitchPosition == CAB3) CabPos = CRAWLER_FWD_VC_OFFSET;
		else CabPos = CRAWLER_REAR_VC_OFFSET;

		VECTOR3 pos, dir, rot;
		VECTOR3 gTgtPos, gCabPos;
		pTgt->GetAttachmentParams(ahTgt, pos, dir, rot);
		double angle = acos(dotp(rot, MLP_ATTACH_ROT));
		MATRIX3 AttachFrame; // rotation matrix to convert cab offset vector to ref frame defined by attachment
		GetRotMatrixY(angle, AttachFrame);
		VECTOR3 TgtPos = pos + mul(AttachFrame, CabPos);
		//VECTOR3 temp = mul(AttachFrame, CabPos);
		//sprintf(oapiDebugString(), "TgtPos offset: %f %f %f", temp.x, temp.y, temp.z);
		//oapiWriteLog(oapiDebugString());
		pTgt->Local2Global(TgtPos, gTgtPos);
		V()->Local2Global(CabPos, gCabPos);

		VECTOR3 gdist = gCabPos - gTgtPos;
		MATRIX3 RotMatrix;
		V()->GetRotationMatrix(RotMatrix);
		VECTOR3 ldist = tmul(RotMatrix,gdist);

		//sprintf(oapiDebugString(),"ldist: %lf %lf %lf",ldist.x, ldist.y, ldist.z);

		return -sign(ldist.z)*ldist.x;





		/*
		for(DWORD i=0; i<oapiGetVesselCount(); i++)
		{
			hv = oapiGetVesselByIndex(i);
			pv = oapiGetVesselInterface(hv);
			name = pv->GetClassNameA();
			//oapiWriteLog("PRZED WEJSCIEM W IFA");
			if(target == "LC39A" || target == "LC39B")
			{
				if(name == "SSV_LC39") //match
				{
					oapiWriteLog("FOUND PAD");
					ATTACHMENTHANDLE attach = pv->GetAttachmentHandle(false,0);

					//TESTING ATTACHMENT
					oapiWriteLog("START ATTACHMENT TEST");
					if(_strnicmp(pv->GetAttachmentId(attach),"XMLP",4)) continue;
					oapiWriteLog("ATTACHMENT TEST COMPLETED");

					pv->GetAttachmentParams(attach,pos,dir,rot);
					pv->Local2Global(pos,gpos);

					VECTOR3 gdist = gpos-gattach;
					MATRIX3 RotMatrix;
					V()->GetRotationMatrix(RotMatrix);

					ldist = tmul(RotMatrix,gdist);
					return -ldist.x;
				}
			}
			else if(target == "VAB_HBAY1")
			{
				if(name == "SSV_VAB") //match
				{
					pv->Local2Global(VAB_HIGHBAY1,gpos);
					VECTOR3 gdist = gpos - gattach;
					MATRIX3 RotMatrix;
					V()->GetRotationMatrix(RotMatrix);
					ldist = tmul(RotMatrix,gdist);
					return -ldist.x;
				}
			}
			else if(target == "VAB_HBAY2")
			{
				if(name == "SSV_VAB")
				{
					pv->Local2Global(VAB_HIGHBAY2,gpos);
					VECTOR3 gdist = gpos - gattach;
					MATRIX3 RotMatrix;
					V()->GetRotationMatrix(RotMatrix);
					ldist = tmul(RotMatrix,gdist);
					return -ldist.x;
				}
			}
		}
		return 0; //NO TARGET OR STH
		*/
	}


	void LDS::OnPostStep(double simt, double simdt, double mjd)
	{
		UpdateLDS(CalculateDistanceBetweenAttachments());
	}

	void LDS::UpdateLDS(double distance)
	{
		double offset;
		// each tick represents 0.01 feet
		// LDS display on actual Crawler has 8 ticks on each side of center
		offset = (distance*MPS2FPS)/0.16 + 0.5;
		//sprintf(oapiDebugString(),"Distance: %f Offset: %lf", distance, offset);

		offset = range(0, offset, 1);
		V()->SetAnimation(LDSBarAnim, offset);
	}

	void LDS::RegisterVC()
	{
		BasicPanel::RegisterVC();

		VECTOR3 ofs;
		int aid_ofs;
		if(cabID==FWD)
		{
			ofs = CRAWLER_FWD_VC_OFFSET;
			aid_ofs = 0;
		}
		else
		{
			ofs = CRAWLER_REAR_VC_OFFSET;
			aid_ofs = AID_REAR_OFFSET;
		}


		oapiVCRegisterArea(AID_LDS_AREA+aid_ofs,PANEL_REDRAW_MOUSE,PANEL_MOUSE_LBDOWN);
		oapiVCSetAreaClickmode_Quadrilateral(AID_LDS_AREA+aid_ofs,
			TransformVector(_V(-0.505, 0.403, -0.003))+ofs,
			TransformVector(_V(-0.517, 0.403, 0.017))+ofs,
			TransformVector(_V(-0.505, 0.383, -0.003))+ofs,
			TransformVector(_V(-0.517, 0.383, 0.017))+ofs);


	}


	void LDS::DefineVC()
	{
		//STH
		int aid_ofs;
		if(cabID==FWD) aid_ofs = 0;
		else  aid_ofs = AID_REAR_OFFSET;

		AddAIDToMouseEventList(AID_LDS_AREA+aid_ofs);
	}




	void LDS::Realize()
	{
		V()->SetAnimation(CabSelectionSwitchAnim, static_cast<double>(CabSelectionSwitchPosition));
	}


	void LDS::DefineVCAnimations(UINT vcidx)
	{


		/*int rot_ofs;
		if(cabID == FWD)
		{
			rot_ofs = 1;
			BasicPanel::DefineVCAnimations(5);//PASS FWD LDS MESH NUMBER
		}

		else if(cabID == REAR)
		{
			rot_ofs = -1;
			BasicPanel::DefineVCAnimations(6); //PASS REAR LDS MESH NUMBER
		}*/
		//BasicPanel::DefineVCAnimations(vcidx);

		//BasicPanel::DefineVCAnimations(mshnbr);


		VECTOR3 LP1,LP2,CP1,CP2,RP1,RP2,AB1,AB2;
		LP1 = TransformVector(_V(-0.448,0.350,-0.073));
		LP2 = TransformVector(_V(-0.404,0.350,-0.047));
		CP1 = TransformVector(_V(-0.463,0.350,-0.047));
		CP2 = TransformVector(_V(-0.421,0.350,-0.022));
		RP1 = TransformVector(_V(-0.478,0.350,-0.021));
		RP2 = TransformVector(_V(-0.434,0.350,0.005));
		AB1 = TransformVector(_V(-0.4746225178,0.4015539587,-0.0527803004));
		AB2 = TransformVector(_V(-0.4253329933,0.4015539587,-0.1361487955));

		//LDS ALIGNMENT BAR ANIMATION
		static UINT LDSBarGrp[1] = {GRP_ALIGNMENT_BAR_VC};
		VECTOR3 BResult = _V(AB2.x-AB1.x,AB2.y-AB1.y,AB2.z-AB1.z);
		//VECTOR3 BNormalised = BResult/dist(AB1,AB2);
		MGROUP_TRANSLATE *pLDSTranslate = new MGROUP_TRANSLATE(vcidx,LDSBarGrp,1,BResult);
		LDSBarAnim = V()->CreateAnimation(0.5);
		V()->AddAnimationComponent(LDSBarAnim,0,1,pLDSTranslate);
		LDSAnimation.push_back(pLDSTranslate);

		static UINT CabSelectionSwitchGrp[1] = {GRP_LDS_CAB_SWITCH_VC};
		MGROUP_ROTATE* pCabSelectionSwitch = new MGROUP_ROTATE(vcidx, CabSelectionSwitchGrp, 1, TransformVector(_V(-0.503, 0.392, 0.013)), _V(0, -1, 0), static_cast<float>(90.0*RAD));
		CabSelectionSwitchAnim = V()->CreateAnimation(0.5);
		V()->AddAnimationComponent(CabSelectionSwitchAnim, 0, 1, pCabSelectionSwitch);
		vpAnimations.push_back(pCabSelectionSwitch);
	}


	bool LDS::OnVCMouseEvent(int id, int _event, VECTOR3 &p)
	{

		if((cabID == FWD && id == AID_LDS_AREA) || (cabID == REAR && id==AID_LDS_AREA+AID_REAR_OFFSET))
		{
			//sprintf(oapiDebugString(),"%f%s%f",p.x," ",p.y);

			if(p.x < 0.5) {
				CabSelectionSwitchPosition = CAB1;
				V()->SetAnimation(CabSelectionSwitchAnim, 0);
			}
			else {
				CabSelectionSwitchPosition = CAB3;
				V()->SetAnimation(CabSelectionSwitchAnim, 1);
			}

			return true;
		}
		else return false;
	}
}

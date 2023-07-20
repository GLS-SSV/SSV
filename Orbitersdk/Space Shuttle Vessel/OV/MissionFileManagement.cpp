/******* SSV File Modification Notice *******
Date         Developer
2020/05/08   GLS
2020/06/12   GLS
2020/06/20   GLS
2021/08/24   GLS
2022/09/29   GLS
********************************************/
#include "MissionFileManagement.h"
#include "mission/Mission.h"
#include <map>


std::map<std::string, mission::Mission*> ssv_mission_hashmap;


DLLCLBK mission::Mission* ssvGetDefaultMission()
{
	return ssvGetMission("");
}

DLLCLBK mission::Mission* ssvGetMission(const std::string& filename)
{
	if(ssv_mission_hashmap.find(filename) != ssv_mission_hashmap.end())
	{
		oapiWriteLog("(Mission File Management) Found loaded mission file.");
		return ssv_mission_hashmap[filename];
	} else {
		oapiWriteLog("(Mission File Management) Load mission file into shared memory.");
		mission::Mission* new_mission = new mission::Mission(filename);
		ssv_mission_hashmap.insert(std::make_pair(filename, new_mission));
		return new_mission;
	}
}

void InitMissionManagementMemory()
{
	ssv_mission_hashmap.clear();
}

void ClearMissionManagementMemory()
{
	std::map<std::string, mission::Mission*>::iterator iter
		= ssv_mission_hashmap.begin();
	while(iter != ssv_mission_hashmap.end())
	{
		if(iter->second)
		{
			delete iter->second;
			iter->second = NULL;
		}
		iter++;
	}
}

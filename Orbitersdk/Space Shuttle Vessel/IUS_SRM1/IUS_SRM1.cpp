/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/03/29   GLS
2020/04/01   GLS
2020/05/08   GLS
2020/05/14   GLS
2020/05/25   GLS
2020/06/20   GLS
2020/06/21   GLS
2020/06/23   GLS
2020/06/28   GLS
2020/08/24   GLS
2021/01/20   GLS
2021/06/16   GLS
2021/06/28   GLS
2021/08/03   GLS
2021/08/06   GLS
2021/08/10   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/09   GLS
2021/12/10   GLS
2021/12/11   GLS
2021/12/23   GLS
2021/12/24   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/03/22   GLS
2022/03/23   GLS
2022/03/24   GLS
2022/05/07   GLS
2023/09/14   GLS
********************************************/
#define ORBITER_MODULE


#include "IUS_SRM1.h"
#include <MathSSV.h>
#include <UtilsSSV.h>


const static char* MESHNAME_STAGE_1 = "SSV\\IUS\\IUS_SRM1";


const VECTOR3 SRM2_ATTACH_OFFSET = _V( 0.0, 0.0, 2.35112 );

constexpr double STAGE1_EMPTYMASS = 1123.276;// kg


DLLCLBK VESSEL *ovcInit( OBJHANDLE hvessel, int flightmodel )
{
	try
	{
		return new IUS_SRM1( hvessel );
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_IUS_SRM1) [FATAL ERROR] Exception in ovcInit: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_IUS_SRM1) [FATAL ERROR] Exception in ovcInit" );
		abort();
	}
}

DLLCLBK void ovcExit( VESSEL *vessel )
{
	try
	{
		if (vessel) delete static_cast<IUS_SRM1*>(vessel);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_IUS_SRM1) [FATAL ERROR] Exception in ovcExit: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_IUS_SRM1) [FATAL ERROR] Exception in ovcExit" );
		abort();
	}
}


IUS_SRM1::IUS_SRM1( OBJHANDLE hObj ):VESSEL4( hObj ), hTexture(NULL)
{
	return;
}

IUS_SRM1::~IUS_SRM1( void )
{
	if (hTexture) oapiReleaseTexture( hTexture );
	return;
}

void IUS_SRM1::clbkSetClassCaps(FILEHANDLE cfg)
{
	try
	{
		SetSize( 5.0 );// TODO
		SetEmptyMass( STAGE1_EMPTYMASS );
		SetCrossSections( _V( 13.73, 17.84, 10.71 ) );// TODO
		SetPMI( _V( 2.29, 2.4, 1.79 ) );// TODO

		mesh_stage = AddMesh( oapiLoadMeshGlobal( MESHNAME_STAGE_1 ) );
		SetMeshVisibilityMode( mesh_stage, MESHVIS_ALWAYS );

		ahSRM2 = CreateAttachment( true, SRM2_ATTACH_OFFSET, _V( 0.0, 0.0, 1.0 ), _V( 0.0, -1.0, 0.0 ), "IUS_SRM" );
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_IUS_SRM1) [FATAL ERROR] Exception in IUS_SRM1::clbkSetClassCaps: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_IUS_SRM1) [FATAL ERROR] Exception in IUS_SRM1::clbkSetClassCaps" );
		abort();
	}
}

void IUS_SRM1::clbkPostCreation( void )
{
	try
	{
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_IUS_SRM1) [FATAL ERROR] Exception in IUS_SRM1::clbkPostCreation: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_IUS_SRM1) [FATAL ERROR] Exception in IUS_SRM1::clbkPostCreation" );
		abort();
	}
}

void IUS_SRM1::clbkPostStep( double simt, double simdt, double mjd )
{
	try
	{
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_IUS_SRM1) [FATAL ERROR] Exception in IUS_SRM1::clbkPostStep: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_IUS_SRM1) [FATAL ERROR] Exception in IUS_SRM1::clbkPostStep" );
		abort();
	}
}

int IUS_SRM1::clbkConsumeBufferedKey( DWORD key, bool down, char* kstate )
{
	try
	{
		return 0;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_IUS_SRM1) [FATAL ERROR] Exception in IUS_SRM1::clbkConsumeBufferedKey: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_IUS_SRM1) [FATAL ERROR] Exception in IUS_SRM1::clbkConsumeBufferedKey" );
		abort();
	}
}

void IUS_SRM1::clbkVisualCreated( VISHANDLE vis, int refcount )
{
	try
	{
		if (!strTextureName.empty()) UpdateTexture( GetDevMesh( vis, mesh_stage ) );
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_IUS_SRM1) [FATAL ERROR] Exception in IUS_SRM1::clbkVisualCreated: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_IUS_SRM1) [FATAL ERROR] Exception in IUS_SRM1::clbkVisualCreated" );
		abort();
	}
}

void IUS_SRM1::clbkSaveState( FILEHANDLE scn )
{
	try
	{
		VESSEL4::clbkSaveState( scn );

		if (strMission.length() > 0) oapiWriteScenario_string( scn, "MISSION", (char*)strMission.c_str() );
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_IUS_SRM1) [FATAL ERROR] Exception in IUS_SRM1::clbkSaveState: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_IUS_SRM1) [FATAL ERROR] Exception in IUS_SRM1::clbkSaveState" );
		abort();
	}
}

void IUS_SRM1::clbkLoadStateEx( FILEHANDLE scn, void* status )
{
	try
	{
		char *line;

		while (oapiReadScenario_nextline( scn, line ))
		{
			if (!_strnicmp( line, "MISSION", 7 ))
			{
				strMission = line + 8;
				LoadMissionFile();
			}
			else ParseScenarioLineEx( line, status );
		}

		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_IUS_SRM1) [FATAL ERROR] Exception in IUS_SRM1::clbkLoadStateEx: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_IUS_SRM1) [FATAL ERROR] Exception in IUS_SRM1::clbkLoadStateEx" );
		abort();
	}
}

void IUS_SRM1::UpdateTexture( DEVMESHHANDLE hDevMesh )
{
	if (!hDevMesh) return;// no mesh handle
	if (hTexture == NULL) hTexture = oapiLoadTexture( strTextureName.c_str() );
	if (hTexture == NULL) throw std::exception( "Could not load texture" );
	else oapiSetTexture( hDevMesh, 1, hTexture );
	return;
}

void IUS_SRM1::LoadMissionFile( void )
{
	std::string filename;
	filename = "Missions\\SSV\\" + strMission + ".json";

	FILE* hF = fopen( filename.c_str(), "r" );
	if (hF == NULL)
	{
		oapiWriteLogV( "(SSV_IUS_SRM1) [ERROR] Can't open mission file %s", strMission.c_str() );
		return;
	}

	oapiWriteLogV( "(SSV_IUS_SRM1) [INFO] Loading mission file %s", strMission.c_str() );

	fseek( hF, 0, SEEK_END );
	long filesize = ftell( hF );
	if (filesize < 0)
	{
		fclose( hF );
		return;
	}

	char* missionfilestr = new char[filesize];
	rewind( hF );
	fread( missionfilestr, sizeof(char), filesize, hF );
	fclose( hF );

	cJSON* root = cJSON_Parse( missionfilestr );
	if (!root)
	{
		oapiWriteLog( "(SSV_IUS_SRM1) [ERROR] Error parsing mission file version" );
		delete[] missionfilestr;
		return;
	}

	cJSON* version = cJSON_GetObjectItemCaseSensitive( root, "Version" );
	switch (version->valueint)
	{
		case 2:// unchanged from V1
			LoadMissionV1( root );
			break;
		default:
			oapiWriteLogV( "(SSV_IUS_SRM1) [ERROR] Unknown mission file version %d", version->valueint );
			break;
	}

	cJSON_Delete( root );
	delete[] missionfilestr;
	return;
}

void IUS_SRM1::LoadMissionV1( cJSON* root )
{
	// read UpperStages
	cJSON* us = cJSON_GetObjectItemCaseSensitive( root, "Upper Stages" );
	for (int i = 0; i < cJSON_GetArraySize( us ); i++)
	{
		// find correct item
		cJSON* usi = cJSON_GetArrayItem( us, i );
		if (usi)
		{
			cJSON* name = cJSON_GetObjectItemCaseSensitive( usi, "Name" );
			cJSON* usown = cJSON_GetObjectItemCaseSensitive( usi, "IUS 2-Stage" );
			if ((name) && (usown))
			{
				std::string strtmp = name->valuestring;
				strtmp += "_SRM-1";// handle SRM-1 vessel name suffix
				if (!strcmp( GetName(), strtmp.c_str() ))
				{
					// read own params
					cJSON* tmp = cJSON_GetObjectItemCaseSensitive( usown, "Texture" );
					strTextureName = "SSV\\IUS\\" + std::string( tmp->valuestring ) + ".dds";
					break;
				}
			}
		}
	}
	return;
}

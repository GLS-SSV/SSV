/****************************************************************************
  This file is part of Space Shuttle Vessel

  Subsystem Director definition


  Space Shuttle Vessel is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Vessel is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Vessel; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file SSV-LICENSE.txt for more details.

  **************************************************************************/
/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/04/01   GLS
2020/05/10   GLS
2020/06/21   GLS
2020/08/24   GLS
2020/08/25   GLS
2020/08/31   GLS
2020/09/04   GLS
2021/06/03   GLS
2021/06/06   GLS
2021/08/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/01/10   GLS
2022/01/15   GLS
2022/02/16   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/07/16   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Subsystem Director



  Space Shuttle Ultra is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Ultra is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Ultra; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file Doc\Space Shuttle Ultra\GPL.txt for more details.

  **************************************************************************/
#ifndef ___SUBSYSTEM_DIRECTOR_H___
#define ___SUBSYSTEM_DIRECTOR_H___

#include <vector>
#include <OrbiterAPI.h>

using namespace std;

template <class TVessel>
class Subsystem;

template <class TVessel>
class SubsystemDirector
{
protected:
	TVessel* pV;
	vector< Subsystem<TVessel>* > subsystems;
public:
	virtual TVessel* V() const;
	explicit SubsystemDirector(TVessel* _v);
	virtual ~SubsystemDirector();
	bool AddSubsystem(Subsystem<TVessel>* pSubsys);
	Subsystem<TVessel>* ReplaceSubsystem(Subsystem<TVessel>* pCurrentSubsys, Subsystem<TVessel>* pBySubsys);
	Subsystem<TVessel>* GetSubsystemByName(const std::string& name) const;

	double GetTotalSubsystemMass() const;
	double GetTotalSubsystemMassCoG( VECTOR3& CoG, const VECTOR3& defaultCoG ) const;

	bool ParseScenarioLine(FILEHANDLE scn, char* line);
	bool PlaybackEvent(double simt, double fEventT, const char* event_t, const char* event);
	bool SaveState(FILEHANDLE scn);
	bool PostStep(double simt, double simdt, double mjd);
	bool PreStep(double simt, double simdt, double mjd);
	bool Report() const;
	bool WriteLog(const Subsystem<TVessel>* src, char* message);
	void Animate( void );
	void VisualCreated( VISHANDLE vis );


	/**
	 *
	 */
	bool RealizeAll();
};

template <class TVessel>
SubsystemDirector<TVessel>::SubsystemDirector(TVessel* _v)
: pV(_v)
{
}

template <class TVessel>
SubsystemDirector<TVessel>::~SubsystemDirector()
{
	unsigned long i;
	for(i = 0; i<subsystems.size(); i++)
	{
		delete subsystems[i];
	}
}

template <class TVessel>
bool SubsystemDirector<TVessel>::AddSubsystem(Subsystem<TVessel>* pSubsys)
{
	subsystems.push_back(pSubsys);
	oapiWriteLogV( "Added subsystem %s.", pSubsys->GetQualifiedIdentifier().c_str() );
	return true;
}

template <class TVessel>
Subsystem<TVessel>* SubsystemDirector<TVessel>::ReplaceSubsystem(Subsystem<TVessel>* pCurrentSubsys, Subsystem<TVessel>* pBySubsys)
{
	typename vector< Subsystem<TVessel>* >::iterator iter = std::find(subsystems.begin(),
		subsystems.end(), pCurrentSubsys);

	if(iter != subsystems.end()) {

		pCurrentSubsys->UnloadSubsystem();
		*iter = pBySubsys;

		oapiWriteLogV( "Replaced subsystem %s by subsystem %s.",
			pCurrentSubsys->GetQualifiedIdentifier().c_str(),
			pBySubsys->GetQualifiedIdentifier().c_str() );

		delete pCurrentSubsys;

		oapiWriteLog( "Finished clean up." );
		return pBySubsys;
	}
	return pCurrentSubsys;
}

template <class TVessel>
Subsystem<TVessel>* SubsystemDirector<TVessel>::GetSubsystemByName(const std::string& name) const
{
	typename std::vector< Subsystem<TVessel>* >::const_iterator iter = subsystems.begin();
	while(iter != subsystems.end())
	{
		if((*iter)->GetIdentifier() == name) {
			return (*iter);
		}
		++iter;
	}
	return NULL;
}

template <class TVessel>
double SubsystemDirector<TVessel>::GetTotalSubsystemMass() const
{
	double mass = 0.0;
	typename std::vector< Subsystem<TVessel>* >::const_iterator iter = subsystems.begin();
	while(iter != subsystems.end())
	{
		mass += (*iter)->GetSubsystemMass();
		++iter;
	}
	return mass;
}

template <class TVessel>
double SubsystemDirector<TVessel>::GetTotalSubsystemMassCoG( VECTOR3& CoG, const VECTOR3& defaultCoG ) const
{
	VECTOR3 cg = _V( 0.0, 0.0, 0.0 );
	double mass = 0.0;
	double totalmass = 0.0;

	typename std::vector<Subsystem<TVessel>*>::const_iterator iter = subsystems.begin();
	while (iter != subsystems.end())
	{
		mass = (*iter)->GetSubsystemMass();
		if ((*iter)->GetSubsystemCoG( cg ) == false) cg = defaultCoG;// if subsystem c.g. not defined use default

		totalmass += mass;
		CoG += cg * mass;
		//if (mass != 0) oapiWriteLogV( "subsys %s %f    %f %f %f", (*iter)->GetIdentifier().c_str(), mass * KG2LBM, (24.239 - cg.z) / IN2M, cg.x / IN2M, (cg.y + 10.5871) / IN2M );
		++iter;
	}

	CoG = CoG / totalmass;
	return totalmass;
}

template <class TVessel>
bool SubsystemDirector<TVessel>::RealizeAll() {
	unsigned long i;
	for(i = 0; i<subsystems.size(); i++)
	{
		//
		subsystems[i]->Realize();
	}
	return true;
}

template <class TVessel>
bool SubsystemDirector<TVessel>::ParseScenarioLine(FILEHANDLE scn, char* line)
{
	char pszBuffer[400];
	if (!_strnicmp( line, "@SUBSYSTEM", 10 ))
	{
#if _DEBUG
		oapiWriteLog(line);
#endif
		line += 11;
		unsigned long i = 0;
		bool bStringFlag = false;
		while((*line != '\0' && *line != ' ') || bStringFlag) {
			if(*line == '\"') {
				bStringFlag = !bStringFlag;
			} else {
				pszBuffer[i] = *line;
				i++;
			}
			line++;
		}

		pszBuffer[i] = '\0';

		Subsystem<TVessel>* pT = GetSubsystemByName( pszBuffer );
		if (pT != NULL) pT->OnReadState( scn );
		else
		{
			// subsystem not found
			oapiWriteLogV( "(SSVlib) [ERROR] Subsystem %s not found during scenario loading", pszBuffer );

			while (oapiReadScenario_nextline( scn, line ))
			{
				if (!_strnicmp( line, "@ENDSUBSYSTEM", 13 ))
					break;
			}
		}
	}
	else
	{
		// legacy
		for (unsigned long i = 0; i < subsystems.size(); i++)
		{
			if (subsystems[i]->OnParseLine( line ))
			{
				return true;
			}
		}
	}
	return false;
}

template <class TVessel>
bool SubsystemDirector<TVessel>::PlaybackEvent(double simt, double fEventT, const char* event_t, const char* event)
{
	return false;
}

template <class TVessel>
bool SubsystemDirector<TVessel>::SaveState(FILEHANDLE scn)
{
	unsigned long i;
	char pszBuffer[400];
	for(i = 0; i<subsystems.size(); i++)
	{
		oapiWriteLogV( "Save Subystem \"%s\" ...", subsystems[i]->GetQualifiedIdentifier().c_str() );

		sprintf_s(pszBuffer,"@SUBSYSTEM %s", subsystems[i]->GetQualifiedIdentifier().c_str());
		oapiWriteLine(scn, pszBuffer);

		subsystems[i]->OnSaveState(scn);

		oapiWriteLine(scn, "@ENDSUBSYSTEM");
	}
	return true;
}

template <class TVessel>
bool SubsystemDirector<TVessel>::PostStep(double simt, double simdt, double mjd)
{
	unsigned long i;
	//const double SUBSAMPLING_DELTAT = 0.0005;	//0.5 ms
	/*const double SUBSAMPLING_DELTAT = 0.04;	//40 ms


	//Subsampling pass
	double t0 = simt;
	long lSubCount = 0;

	while(t0 < simt + simdt) {
		double dt = min(SUBSAMPLING_DELTAT, simt + simdt - t0);
		for(i = 0; i<subsystems.size(); i++)
		{
			subsystems[i]->OnSubPreStep(t0, dt, mjd);
		}
		//if(BusManager() != NULL)
			//BusManager()->clbkPropagate(t0, dt);
		for(i = 0; i<subsystems.size(); i++)
		{
			//
			subsystems[i]->OnSubPropagate(t0, dt, mjd);
		}


		for(i = 0; i<subsystems.size(); i++)
		{
			subsystems[i]->OnSubPostStep(t0, dt, mjd);
		}
		t0 += SUBSAMPLING_DELTAT;
		lSubCount ++;
		//measure average time for the subsampling during this time step
	}*/

	//sprintf_s(oapiDebugString(), 256, "%d SUBSAMPLING STEPS @ %5.2f us", lSubCount, tsf);

	//Propagate subsystem states to the end of the discrete timestep
	for(i = 0; i<subsystems.size(); i++)
	{
		//
		subsystems[i]->OnPropagate(simt, simdt, mjd);
	}
	for(i = 0; i<subsystems.size(); i++)
	{
		//
		subsystems[i]->OnPostStep(simt, simdt, mjd);
	}
	return true;
}

template <class TVessel>
bool SubsystemDirector<TVessel>::PreStep(double simt, double simdt, double mjd)
{
	unsigned long i;
	for(i = 0; i<subsystems.size(); i++)
	{
		//
		subsystems[i]->OnPreStep(simt, simdt, mjd);
	}
	return true;
}

template <class TVessel>
bool SubsystemDirector<TVessel>::Report() const
{
	/*unsigned int i;
	time_t t0;
	static char buffer[512];

	t0 = time(NULL);
	ctime_s(buffer, 511, &t0);
	//Create report file
	std::ofstream report;
	report.open("ssv-subsys-report.html");
	report << "<!doctype html>" << std::endl;
	report << "<html>" << std::endl << "<head>" << std::endl;
	report << "<title>SSV subsystem report " <<
		STS()->GetName() << "</title>" << std::endl;
	report << "</head>" << std::endl;

	report << "<body>" << std::endl;
	report << "<header>" << buffer << "</header>" << std::endl;

	report << "<h1>SSV subsystem report</h1>" << std::endl;
	report << "<h2>List of existing subsystems</h2>" << std::endl;

	report << "<ol>" << std::endl;

	for(i = 0; i<subsystems.size(); i++)
	{
		report << "<li>" << subsystems[i]->GetIdentifier() << "</li>"
			<< std::endl;
	}

	report << "</ol>" << std::endl;

	report << "</body>" << std::endl << "</html>" << std::endl;
	report.close();*/
	return true;
}

template <class TVessel>
bool SubsystemDirector<TVessel>::WriteLog(const Subsystem<TVessel>* src, char* message)
{
	return true;
}

template <class TVessel>
void SubsystemDirector<TVessel>::Animate( void )
{
	for (unsigned int i = 0; i < subsystems.size(); i++) subsystems[i]->Animate();
	return;
}

template <class TVessel>
void SubsystemDirector<TVessel>::VisualCreated( VISHANDLE vis )
{
	for (unsigned int i = 0; i < subsystems.size(); i++) subsystems[i]->VisualCreated( vis );
	return;
}

template <class TVessel>
TVessel* SubsystemDirector<TVessel>::V() const
{
	return pV;
}

#endif// ___SUBSYSTEM_DIRECTOR_H___

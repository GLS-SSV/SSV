/****************************************************************************
  This file is part of Space Shuttle Vessel

  Basic subsystem definitions


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
2020/05/10   GLS
2020/06/21   GLS
2020/08/24   GLS
2020/08/25   GLS
2021/06/06   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/12/26   GLS
2022/01/10   GLS
2022/02/16   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/07/16   GLS
2022/08/05   GLS
2022/08/08   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Basic subsystem definitions



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

#ifndef SUBSYSTEM_H__6A9F0F48_D391_4E11_9536_F359182CA558__INCLUDED_
#define SUBSYSTEM_H__6A9F0F48_D391_4E11_9536_F359182CA558__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "OrbiterAPI.h"
#include "ISubsystem.h"
#include "SubsystemDirector.h"

using namespace std;

/**
 * base class for all subsystem simulations.
 */
template <class TVessel>
class Subsystem: public ISubsystem
{
protected:
	SubsystemDirector<TVessel>* director;
	string ident;
	std::vector<MGROUP_TRANSFORM*> vpAnimations;
public:
	/**
	 * Create a new Atlantis subsystem object
	 */
	Subsystem(SubsystemDirector<TVessel>* _director, const string& _ident);
	/**
	 * Destructor
	 */
	virtual ~Subsystem();
	/**
	 * Get a reference to the Space Shuttle external physical model.
	 * @return reference to the space shuttle object. If possible.
	 */
	TVessel* V() const;

	/**
	 * Create the physical representation of the subsystem. This means:
	 * - creation of thrusters
	 * - discrete line connections to VC components
	 * - discrete line connections to other subsystems
	 * - connection to Shuttle Bus systems
	 * - hydraulic connections
	 * - coolant loop connections
	 * - connections to logical propellant resources
	 * -
	 */
	virtual void Realize();
	/**
	 * Register a subsystem component for use inside this subsystem for automated
	 * handling. Not in use now.
	 * @warning Does not have an effect.
	 */
	virtual bool RegisterComponent(SubsystemComponent* pComponent);
	/**
	 * Delete a subsystem component, if no longer used
	 * @warning Does not have an effect.
	 */
	virtual bool DelComponent(SubsystemComponent* pComponent);
	/**
	 * Count the number of subsystem components.
	 * @return always zero, as subsystem component handling is not active.
	 */
	virtual unsigned long CountComponents() const;
	/**
	 * Prepare and execute calculations before the propagation of the
	 * state vector
	 * @param simt current simulation time
	 * @param simdt Simulation time step length
	 * @param mjd current modified julian date
	 */
	virtual void OnPreStep(double simt, double simdt, double mjd);
	/**
	 * Finish calculations after the propagation of the
	 * state vector
	 * @param simt current simulation time
	 * @param simdt Simulation time step length
	 * @param mjd current modified julian date
	 */
	virtual void OnPostStep(double simt, double simdt, double mjd);
	/**
	 * Propagate the state vector from old state to new state.
	 * @param simt current simulation time
	 * @param simdt Simulation time step length
	 * @param mjd current modified julian date
	 */
	virtual void OnPropagate(double simt, double simdt, double mjd);
	virtual void OnPlaybackEvent(double simt, double fEventT, const char* event_t, const char* event);
	/**
	 * Parse a line of the scenario file.
	 * @warning
	 * Should get replaced by a block oriented scenario file
	 * format, like NASSP, making this function deprecated.
	 */
	virtual bool OnParseLine(const char* line);
	/**
	 *
	 */
	virtual bool OnParseLine(const char* keyword, const char* line);
	/**
	 * Save the state of the subsystem
	 */
	virtual void OnSaveState(FILEHANDLE scn) const;

	//Callbacks used for subsampling
	virtual void OnSubPreStep(double simt, double simdt, double mjd);
	virtual void OnSubPropagate(double simt, double simdt, double mjd);
	virtual void OnSubPostStep(double simt, double simdt, double mjd);
	/**
	 * Dump the current state and error conditions into the Orbiter.log or
	 * a special SSV.log. Don't modificate state.
	 */
	virtual void OnDumpToLog() const;
	/**
	 * get the full identifier of the subsystem, including parent container,
	 * if needed. Usually the same as GetIdentifier.
	 */
	virtual const string& GetQualifiedIdentifier() const;
	/**
	 * get the identifier of the subsystem. This identifier can be used for
	 * locating the subsystem inside the physical model AND the scenario file.
	 * should not contain white spaces.
	 */
	virtual const string& GetIdentifier() const;
	/**
	 * Entry point for triggering timed failures. Will be used for
	 * failure simulation.
	 */
	virtual bool OnFail(const string& strFailureCode);
	/**
	 * Get the dry mass of the subsystem, if this subsystem is optional and
	 * causes changes to the standard orbiter dry mass. For example RMS,
	 * external airlock/ODS, etc.
	 * @return The subsystem dry mass in kg.
	 */
	virtual double GetSubsystemMass() const {return 0.0;};

	/**
	* Get subsystem center-of-gravity.
	* @return	true if subsystem CoG is defined, false otherwise
	*/
	virtual bool GetSubsystemCoG( VECTOR3& CoG ) const {return false;};

	/**
	 * Remove subsystem from Shuttle and visual
	 */
	virtual void UnloadSubsystem();


	virtual bool OnReadState (FILEHANDLE scn);
	virtual bool SingleParamParseLine() const {return false;};

	/**
	 * Saves MGROUP_TRANSFORM allocated with "new" to be deleted at the destruction of the subsystem.
	 */
	virtual void SaveAnimation( MGROUP_TRANSFORM *anim );

	/**
	 * clbkAnimate callback to allow subsystems to implement manual animations.
	 */
	virtual void Animate( void );

	/**
	 * clbkVisualCreated callback.
	 */
	virtual void VisualCreated( VISHANDLE vis );
};

template <class TVessel>
class EmptySubsystem: Subsystem<TVessel> {
public:
	EmptySubsystem(SubsystemDirector<TVessel>* _director);
	virtual ~EmptySubsystem();
};

template <class TVessel>
Subsystem<TVessel>::Subsystem(SubsystemDirector<TVessel>* _director, const string& _ident)
: director(_director), ident(_ident)
{
	/*char pszBuffer[300];
	oapiWriteLog("(AtlantisSubsystem::AtlantisSubsystem)");
	sprintf_s(pszBuffer, 300, "(AtlantisSubsystem) Create subsystem %s.", ident.c_str());
	oapiWriteLog(pszBuffer);*/
}

template <class TVessel>
Subsystem<TVessel>::~Subsystem()
{
	for (unsigned int i = 0; i < vpAnimations.size(); i++) delete vpAnimations.at(i);
}

template <class TVessel>
bool Subsystem<TVessel>::RegisterComponent(SubsystemComponent* pComponent)
{
	return false;
}

template <class TVessel>
bool Subsystem<TVessel>::DelComponent(SubsystemComponent* pComponent)
{
	return false;
}

template <class TVessel>
unsigned long Subsystem<TVessel>::CountComponents() const
{
	return 0;
}

template <class TVessel>
void Subsystem<TVessel>::Realize()
{
}

template <class TVessel>
bool Subsystem<TVessel>::OnParseLine(const char* line)
{
	return false;
}

template <class TVessel>
bool Subsystem<TVessel>::OnParseLine(const char* key, const char* line)
{
	return false;
}

template <class TVessel>
void Subsystem<TVessel>::OnSaveState(FILEHANDLE scn) const
{

}

template <class TVessel>
void Subsystem<TVessel>::OnPostStep(double simt, double simdt, double mjd)
{

}

template <class TVessel>
void Subsystem<TVessel>::OnPreStep(double simt, double simdt, double mjd)
{

}

template <class TVessel>
void Subsystem<TVessel>::OnPropagate(double simt, double simdt, double mjd)
{
}

template <class TVessel>
void Subsystem<TVessel>::OnSubPostStep(double simt, double simdt, double mjd)
{

}

template <class TVessel>
void Subsystem<TVessel>::OnSubPreStep(double simt, double simdt, double mjd)
{

}

template <class TVessel>
void Subsystem<TVessel>::OnSubPropagate(double simt, double simdt, double mjd)
{
}

template <class TVessel>
void Subsystem<TVessel>::OnPlaybackEvent(double simt, double fEventT, const char* event_t, const char* event)
{
}

template <class TVessel>
bool Subsystem<TVessel>::OnFail(const string& strFailCode)
{
	return false;
}

template <class TVessel>
void Subsystem<TVessel>::OnDumpToLog() const
{
}

template <class TVessel>
const string& Subsystem<TVessel>::GetIdentifier() const
{
	return this->ident;
}

template <class TVessel>
const string& Subsystem<TVessel>::GetQualifiedIdentifier() const
{
	return GetIdentifier();
}

template <class TVessel>
TVessel* Subsystem<TVessel>::V() const
{
	return director->V();
}

template <class TVessel>
void Subsystem<TVessel>::UnloadSubsystem() {

}

template <class TVessel>
bool Subsystem<TVessel>::OnReadState (FILEHANDLE scn) {
	char* line;
	char pszKey[256];
	while(oapiReadScenario_nextline(scn, line)) {
		if(!_strnicmp(line, "@ENDSUBSYSTEM", 13)) {
			return true;
		} else {
			if(SingleParamParseLine())
				OnParseLine(line);
			else {
				unsigned long i = 0;
				while(*line != ' ' && *line != '\0') {
					pszKey[i++] = *line;
					line++;
				}
				pszKey[i++] = '\0';
				if(*line != '\0') {
					OnParseLine(pszKey, line);
				} else {
					OnParseLine(pszKey, NULL);
				}
			}
		}
	}
	return false;
}

template <class TVessel>
void Subsystem<TVessel>::SaveAnimation( MGROUP_TRANSFORM *anim )
{
#if _DEBUG
	oapiWriteLogV( "(Subsystem::%s) Saved subsystem animation %p", ident.c_str(), (void*)anim );
#endif// _DEBUG
	vpAnimations.push_back( anim );
	return;
}

template <class TVessel>
void Subsystem<TVessel>::Animate( void )
{
	return;
}

template <class TVessel>
void Subsystem<TVessel>::VisualCreated( VISHANDLE vis )
{
	return;
}

template <class TVessel>
EmptySubsystem<TVessel>::EmptySubsystem(SubsystemDirector<TVessel>* _director)
: Subsystem(_director, "[Empty]") {
}

template <class TVessel>
EmptySubsystem<TVessel>::~EmptySubsystem() {
}

#endif // !defined(SUBSYSTEM_H__6A9F0F48_D391_4E11_9536_F359182CA558__INCLUDED_)

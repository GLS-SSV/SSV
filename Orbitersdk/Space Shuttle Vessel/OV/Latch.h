/****************************************************************************
  This file is part of Space Shuttle Vessel

  Latch subsystem definition


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
2020/04/01   GLS
2020/05/10   GLS
2020/06/20   GLS
2020/06/28   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/10/30   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Latch definition



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
#ifndef __LATCH_H
#define __LATCH_H


#include "AtlantisSubsystem.h"
#include <VesselAPI.h>


inline constexpr double LATCH_OPERATION_SPEED = 0.0166666;// 60 sec (single motor)

/**
 * This class essentially acts as a wrapper for a single ATTACHMENTHANDLE.
 */
class LatchSystem : public AtlantisSubsystem
{
public:
	LatchSystem( AtlantisSubsystemDirector* _director, const string& _ident, const string& _attachID, double latchmaxdistance, double latchmaxangle );
	virtual ~LatchSystem();

	void OnPreStep(double simt, double simdt, double mjd) override;
	bool OnParseLine(const char* line) override;
	void OnSaveState(FILEHANDLE scn) const override;
	bool SingleParamParseLine() const override {return true;};

	/**
	 * Creates ATTACHMENTHANDLE associated with latch(es)
	 * Should be called from Atlantis class at appropriate time.
	 */
	virtual void CreateAttachment() = 0;

	/**
	 * If vessel is NULL or same as attached payload,
	 * attachment between hAttach and hPayloadAttachment is destroyed.
	 * Remains logically 'attached' to payload
	 */
	//void Detach(VESSEL* vessel);
protected:
	void AttachPayload(VESSEL* vessel, ATTACHMENTHANDLE attachment);
	void DetachPayload();

	virtual void OnAttach() = 0;
	virtual void OnDetach() = 0;

	/**
	 * Update vessel and attachment list, filtering vessels out-of-range (local attachment outside target vessel radius) and with different attachment id.
	 */
	void UpdateAttachmentList( void );

	int FindAttachment( void ) const;

	/**
	 * Finds vessel that can be attached to this latch
	 * @param pVessel Optional pointer to vessel pointer which will point to payload vessel returned
	 * @returns ATTACHMENTHANDLE to attachment point on payload which can be attached to latch
	 */
	virtual ATTACHMENTHANDLE FindPayload( VESSEL** pVessel ) const;
	/**
	 * @param hV Handle to vessel
	 * @param glatchpos Position of latch in global coordindates
	 * @param glatchdir Direction of latch attachment point in global coordinates
	 * @returns Handle to attachment point which can be used by latch
	 * @returns NULL if vessel cannot be attached
	 */
	ATTACHMENTHANDLE CanAttach(OBJHANDLE hV, const VECTOR3& glatchpos, const VECTOR3& glatchdir) const;
	bool PayloadIsFree() const;

	inline bool IsLatched() { return attachedPayload != NULL; };

	inline bool IsFirstStep() { return firstStep; };

	VESSEL* attachedPayload;
	ATTACHMENTHANDLE hPayloadAttachment;
	ATTACHMENTHANDLE hAttach;

	string AttachID;

private:
	double latchmaxdistance;
	double latchmaxangle;

	vector<VESSEL*> vctVessels;
	vector<ATTACHMENTHANDLE> vctAttachments;

	/**
	 * Called during first timestep to handle any objects attached when scn starts
	 */
	void CheckForAttachedObjects();

	bool firstStep;

	// used only for loading attachments from scenario
	std::string payloadName;
	int attachmentIndex;
};

#endif //__LATCH_H

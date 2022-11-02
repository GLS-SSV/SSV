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
2022/11/01   GLS
2022/11/02   GLS
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

protected:
	/**
	 * Attaches payload that meets defined attach conditions (attachment id, maximum distance and angle), and signals derived class by calling OnAttach().
	 * @return	true if payload found and attached, false otherwise
	 */
	bool AttachPayload( void );
	/**
	 * Detaches payload, and signals derived class by calling OnDetach().
	 */
	void DetachPayload( void );

	/**
	 * Called to signal payload attachment, both during simulation and at start for already attached payloads.
	 */
	virtual void OnAttach( void ) = 0;
	/**
	 * Called to signal payload detachment.
	 */
	virtual void OnDetach( void ) = 0;

	/**
	 * Updates vessel and attachment list, filtering vessels out-of-range (local attachment outside target vessel radius) and with different attachment id.
	 */
	void UpdateAttachmentList( void );

	/**
	 * Runs thru attachment list and finds first attachment with less than the specified distance and angle error.
	 * @return	index of attachment and vessel in vctVessels and vctAttachments
	 */
	int FindAttachment( void ) const;

	bool PayloadIsFree() const;

	inline bool IsLatched() const { return attachedPayload != NULL; };

	inline bool IsFirstStep() const { return firstStep; };

	void SetSearchForAttachments( bool enabled ) {SearchForAttachments = enabled;}

	/**
	 * Handle to attached vessel.
	 */
	VESSEL* attachedPayload;
	/**
	 * Handle to attached payload attachment.
	 */
	ATTACHMENTHANDLE hPayloadAttachment;
	/**
	 * Handle to local attachment.
	 */
	ATTACHMENTHANDLE hAttach;

	string AttachID;

private:
	double latchmaxdistance;
	double latchmaxangle;

	/**
	 * Lists vessels "in range" for attachment checks.
	 */
	vector<VESSEL*> vctVessels;
	/**
	 * Lists valid attachments of vessels "in range" for attachment checks.
	 */
	vector<ATTACHMENTHANDLE> vctAttachments;

	/**
	 * Enables periodic updating of vessel and attachment list.
	 */
	bool SearchForAttachments;
	/**
	 * Time of last vessel and attachment list update.
	 */
	double lastUpdateTime;

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

/****************************************************************************
  This file is part of Space Shuttle Vessel

  Orbiter Boom Sensor System definition



  Space Shuttle Vessel is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
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
#ifndef __OBSS_H
#define __OBSS_H


#include <Orbitersdk.h>


class OBSS: public VESSEL4
{
	private:
		MESHHANDLE hMesh;
		UINT mesh_idx;

		ATTACHMENTHANDLE ahToMPM;
		ATTACHMENTHANDLE ahToGF_fwd;
		ATTACHMENTHANDLE ahToGF_mid;
		ATTACHMENTHANDLE ahToPWP;

		void DefineAnimations( void );

	public:
		explicit OBSS( OBJHANDLE hVessel );
		~OBSS( void );

		void clbkSetClassCaps( FILEHANDLE cfg ) override;
		void clbkPostCreation( void ) override;
		void clbkVisualCreated( VISHANDLE vis, int refcount ) override;
		void clbkSaveState( FILEHANDLE scn ) override;
		void clbkLoadStateEx( FILEHANDLE scn, void *status ) override;
};

#endif// __OBSS_H

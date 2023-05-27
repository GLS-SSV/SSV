/****************************************************************************
  This file is part of Space Shuttle Vessel

  Simple GPC System definition


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
2020/03/20   GLS
2020/04/01   GLS
2020/05/01   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/06/20   GLS
2020/06/28   GLS
2021/07/03   GLS
2021/07/17   GLS
2021/07/24   GLS
2021/07/31   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/05/19   GLS
2022/08/05   GLS
2022/08/13   GLS
2022/08/17   GLS
2022/08/20   GLS
2022/09/29   GLS
2022/10/25   GLS
2022/12/01   indy91
2022/12/18   indy91
2022/12/23   GLS
2023/04/28   GLS
2023/05/07   GLS
2023/05/14   GLS
2023/05/27   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Simple GPS System definition



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
#ifndef _SIMPLEGPCSYSTEM_H_
#define _SIMPLEGPCSYSTEM_H_


#include "../AtlantisSubsystem.h"
#include "dps_defs.h"
#include <BusTerminal.h>
#include "Software/COMPOOL.h"
#include <vector>
#include <map>
#include <string>


namespace vc
{
	class MDU;
}

namespace dps
{
	class SimpleGPCSoftware;
	class SimpleFCOS_IO;
	class GeneralDisplays;
	class UserInterfaceControl;
	class KeyboardInterface;

/**
 * Simple class to simulate GPC and associated software.
 * Will eventually be replaced by proper GPC simulation
 * Similar to SubsystemDirector/Subsystem structure; GPC calls functions on different software classes.
 */
class SimpleGPCSystem : public AtlantisSubsystem, public BusTerminal
{
	friend class UserInterfaceControl;
	friend class KeyboardInterface;

private:
	std::vector<SimpleGPCSoftware*> vSoftware; // all software
	std::vector<SimpleGPCSoftware*> vActiveSoftware; // software used in current major mode

	SimpleFCOS_IO* pFCOS_IO;
	KeyboardInterface* pKeyboardInterface;
	UserInterfaceControl* pUserInterfaceControl;
	GeneralDisplays* pSystemDisplays;
	GeneralDisplays* pUserDisplays;

	bool GNC;

	void Rx_FC( const BUS_ID id, void* data, const unsigned short datalen );
	void Rx_DK( const BUS_ID id, void* data, const unsigned short datalen );

public:
	SimpleGPCSystem( AtlantisSubsystemDirector* _director, const string& _ident, bool _GNC, BusManager* pBusManager );
	virtual ~SimpleGPCSystem();

	void _Tx( const BUS_ID id, void* data, const unsigned short datalen );
	void Rx( const BUS_ID id, void* data, const unsigned short datalen ) override;

	unsigned short SimpleCOMPOOL[SIMPLECOMPOOL_SIZE];
	unsigned int WriteBufferAddress;
	unsigned int WriteBufferLength;
	unsigned int SubSystemAddress;

	void SetMajorMode( unsigned short newMM );

	unsigned short GetMajorMode() const { return ReadCOMPOOL_IS( SCP_MM ); };
	double ReadClock() const { return ReadCOMPOOL_SD(SCP_CLOCK); };

	void Realize() override;

	void OnPreStep(double simt, double simdt, double mjd) override;
	void OnPostStep(double simt, double simdt, double mjd) override;
	void OnPropagate(double simt, double simdt, double mjd) override;

	bool OnReadState(FILEHANDLE scn) override;
	void OnSaveState(FILEHANDLE scn) const override;

	void GetFaultMsg( char* msg, bool& flash, unsigned short crt ) const;

	/**
	 * Draws display on MDU.
	 * Returns true if data was drawn; false otherwise
	 */
	bool OnPaint( int crt, vc::MDU* pMDU ) const;

	SimpleGPCSoftware* FindSoftware(const std::string& identifier) const;

	unsigned short ReadCOMPOOL_IS( unsigned int addr ) const;
	unsigned int ReadCOMPOOL_ID( unsigned int addr ) const;
	float ReadCOMPOOL_SS( unsigned int addr ) const;
	double ReadCOMPOOL_SD(unsigned int addr) const;
	MATRIX3 ReadCOMPOOL_MS( unsigned int addr ) const;
	MATRIX3 ReadCOMPOOL_MD(unsigned int addr) const;
	float ReadCOMPOOL_MS( unsigned int addr, unsigned int m, unsigned int n, unsigned int msize = 3, unsigned int nsize = 3 ) const;
	VECTOR3 ReadCOMPOOL_VS( unsigned int addr ) const;
	VECTOR3 ReadCOMPOOL_VD(unsigned int addr) const;
	float ReadCOMPOOL_VS( unsigned int addr, unsigned int n, unsigned int nsize = 3 ) const;
	void ReadCOMPOOL_C( unsigned int addr, char* val, unsigned int size ) const;
	unsigned short ReadCOMPOOL_AIS( unsigned int addr, unsigned int idx, unsigned int size ) const;
	void ReadCOMPOOL_AC( unsigned int addr, unsigned int idx, char* val, unsigned int size_a, unsigned int size_c ) const;

	void WriteCOMPOOL_IS( unsigned int addr, unsigned short val );
	void WriteCOMPOOL_ID( unsigned int addr, unsigned int val );
	void WriteCOMPOOL_SS( unsigned int addr, float val );
	void WriteCOMPOOL_SD(unsigned int addr, double val );
	void WriteCOMPOOL_MS( unsigned int addr, MATRIX3& val );
	void WriteCOMPOOL_MD(unsigned int addr, MATRIX3& val);
	void WriteCOMPOOL_MS( unsigned int addr, unsigned int m, unsigned int n, float val, unsigned int msize = 3, unsigned int nsize = 3 );
	void WriteCOMPOOL_VS( unsigned int addr, VECTOR3& val );
	void WriteCOMPOOL_VD(unsigned int addr, VECTOR3& val);
	void WriteCOMPOOL_VS( unsigned int addr, unsigned int n, float val, unsigned int nsize = 3 );
	void WriteCOMPOOL_C( unsigned int addr, const char* val, unsigned int size );
	void WriteCOMPOOL_AIS( unsigned int addr, unsigned int idx, unsigned short val, unsigned int size );
	void WriteCOMPOOL_AC( unsigned int addr, unsigned int idx, const char* val, unsigned int size_a, unsigned int size_c );

	/**
	 * Gets I-LOADs from mission class and uses them to initialize COMPOOL and then passes them to SimpleGPCSoftware classes for their initialization.
	 * @param ILOADlist	I-LOAD list
	 */
	void LoadILOADs( const std::map<std::string,std::string>& ILOADlist );

	void SimpleCOMPOOLReadILOADs( const std::map<std::string,std::string>& ILOADs );

	unsigned short GetPhysicalID( void ) const;
};

}

#endif// _SIMPLEGPCSYSTEM_H_

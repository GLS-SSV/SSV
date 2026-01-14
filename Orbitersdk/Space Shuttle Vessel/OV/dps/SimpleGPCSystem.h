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
2023/11/04   GLS
2024/06/16   GLS
2024/07/06   GLS
2025/01/23   GLS
2025/07/20   GLS
2025/01/14   GLS
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


namespace dps
{
	class SimpleGPCSoftware;
	class SimpleFCOS_IO;
	class UserInterfaceControl;
	class CRT_Interface;
	class ICC_Interface;
	class DPS_Reconfiguration;
	class KeyboardInterface;
	class GeneralDisplays;

/**
 * Simple class to simulate GPC and associated software.
 * Will eventually be replaced by proper GPC simulation
 * Similar to SubsystemDirector/Subsystem structure; GPC calls functions on different software classes.
 */
class SimpleGPCSystem : public AtlantisSubsystem, public BusTerminal
{
	friend class UserInterfaceControl;
	friend class KeyboardInterface;
	friend class CRT_Interface;
	friend class ICC_Interface;

private:
	std::vector<SimpleGPCSoftware*> vSoftware; // all software
	std::vector<SimpleGPCSoftware*> vActiveSoftware; // software used in current major mode

	SimpleFCOS_IO* pFCOS_IO;
	KeyboardInterface* pKeyboardInterface;
	UserInterfaceControl* pUserInterfaceControl;
	CRT_Interface* pCRT_Interface;
	ICC_Interface* pICC_Interface;
	DPS_Reconfiguration* pDPS_Reconfiguration;
	GeneralDisplays* pSystemDisplays;
	GeneralDisplays* pUserDisplays;

	bool rcvr;

	bool GNC;

	void Rx_FC( const BUS_ID id, void* data, const unsigned short datalen );
	void Rx_DK( const BUS_ID id, void* data, const unsigned short datalen );
	void Rx_IC( const BUS_ID id, void* data, const unsigned short datalen );

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
	void UpdateProcessQueue( void );

	unsigned short GetMajorMode() const { return ReadCOMPOOL_IS( SCP_MM ); };
	double ReadClock() const { return ReadCOMPOOL_SD(SCP_CLOCK); };

	void Realize() override;

	void OnPreStep(double simt, double simdt, double mjd) override;
	void OnPostStep(double simt, double simdt, double mjd) override;
	void OnPropagate(double simt, double simdt, double mjd) override;

	bool OnReadState(FILEHANDLE scn) override;
	void OnSaveState(FILEHANDLE scn) const override;

	SimpleGPCSoftware* FindSoftware(const std::string& identifier) const;


	float ReadCOMPOOL_SS( const unsigned int addr ) const;
	double ReadCOMPOOL_SD( const unsigned int addr ) const;
	unsigned short ReadCOMPOOL_IS( const unsigned int addr ) const;
	unsigned int ReadCOMPOOL_ID( const unsigned int addr ) const;
	void ReadCOMPOOL_C( const unsigned int addr, char* val, const unsigned short size ) const;
	float ReadCOMPOOL_VS( const unsigned int addr, const unsigned short n, const unsigned short nsize ) const;
	VECTOR3 ReadCOMPOOL_VS( const unsigned int addr ) const;
	double ReadCOMPOOL_VD( const unsigned int addr, const unsigned short n, const unsigned short nsize ) const;
	VECTOR3 ReadCOMPOOL_VD( const unsigned int addr ) const;
	float ReadCOMPOOL_MS( const unsigned int addr, const unsigned short m, const unsigned short n, const unsigned short msize, const unsigned short nsize ) const;
	MATRIX3 ReadCOMPOOL_MS( const unsigned int addr ) const;
	double ReadCOMPOOL_MD( const unsigned int addr, const unsigned short m, const unsigned short n, const unsigned short msize, const unsigned short nsize ) const;
	MATRIX3 ReadCOMPOOL_MD( const unsigned int addr ) const;
	void ReadCOMPOOL_STRUCT( const unsigned int addr, void* strct, const unsigned int* sizes, const unsigned int* pos, const unsigned short elcnt ) const;

	float ReadCOMPOOL_ASS( const unsigned int addr, const unsigned short idx, const unsigned short size ) const;
	double ReadCOMPOOL_ASD( const unsigned int addr, const unsigned short idx, const unsigned short size ) const;
	unsigned short ReadCOMPOOL_AIS( const unsigned int addr, const unsigned short idx, const unsigned short size ) const;
	unsigned int ReadCOMPOOL_AID( const unsigned int addr, const unsigned short idx, const unsigned short size ) const;
	void ReadCOMPOOL_AC( const unsigned int addr, const unsigned short idx, char* val, const unsigned short size_a, const unsigned short size_c ) const;
	// TODO AVS
	// TODO AVD
	// TODO AMS
	// TODO AMD
	void ReadCOMPOOL_ASTRUCT( const unsigned int addr, const unsigned short idx, void* strct, const unsigned int* sizes, const unsigned int* pos, const unsigned short elcnt, const unsigned short size ) const;

	float ReadCOMPOOL_A2SS( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short size1, const unsigned short size2 ) const;
	double ReadCOMPOOL_A2SD( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short size1, const unsigned short size2 ) const;
	unsigned short ReadCOMPOOL_A2IS( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short size1, const unsigned short size2 ) const;
	unsigned int ReadCOMPOOL_A2ID( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short size1, const unsigned short size2 ) const;
	// TODO AC2
	// TODO AVS2
	// TODO AVD2
	// TODO AMS2
	// TODO AMD2
	// TODO ASTRUCT2

	float ReadCOMPOOL_A3SS( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short idx3, const unsigned short size1, const unsigned short size2, const unsigned short size3 ) const;
	double ReadCOMPOOL_A3SD( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short idx3, const unsigned short size1, const unsigned short size2, const unsigned short size3 ) const;
	unsigned short ReadCOMPOOL_A3IS( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short idx3, const unsigned short size1, const unsigned short size2, const unsigned short size3 ) const;
	unsigned int ReadCOMPOOL_A3ID( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short idx3, const unsigned short size1, const unsigned short size2, const unsigned short size3 ) const;
	// TODO AC3
	// TODO AVS3
	// TODO AVD3
	// TODO AMS3
	// TODO AMD3
	// TODO ASTRUCT3


	void WriteCOMPOOL_SS( const unsigned int addr, const float val );
	void WriteCOMPOOL_SD( const unsigned int addr, const double val );
	void WriteCOMPOOL_IS( const unsigned int addr, const unsigned short val );
	void WriteCOMPOOL_ID( const unsigned int addr, const unsigned int val );
	void WriteCOMPOOL_C( const unsigned int addr, const char* val, const unsigned short size );
	void WriteCOMPOOL_VS( const unsigned int addr, const unsigned short n, const float val, const unsigned short nsize );
	void WriteCOMPOOL_VS( const unsigned int addr, const VECTOR3& val );
	void WriteCOMPOOL_VD( const unsigned int addr, const unsigned short n, const double val, const unsigned short nsize );
	void WriteCOMPOOL_VD( const unsigned int addr, const VECTOR3& val );
	void WriteCOMPOOL_MS( const unsigned int addr, const unsigned short m, const unsigned short n, const float val, const unsigned short msize, const unsigned short nsize );
	void WriteCOMPOOL_MS( const unsigned int addr, const MATRIX3& val );
	void WriteCOMPOOL_MD( const unsigned int addr, const unsigned short m, const unsigned short n, const double val, const unsigned short msize, const unsigned short nsize );
	void WriteCOMPOOL_MD( const unsigned int addr, const MATRIX3& val );
	void WriteCOMPOOL_STRUCT( const unsigned int addr, const void* strct, const unsigned int* sizes, const unsigned int* pos, const unsigned short elcnt );

	void WriteCOMPOOL_ASS( const unsigned int addr, const unsigned short idx, float val, const unsigned short size );
	void WriteCOMPOOL_ASD( const unsigned int addr, const unsigned short idx, const double val, const unsigned short size );
	void WriteCOMPOOL_AIS( const unsigned int addr, const unsigned short idx, const unsigned short val, const unsigned short size );
	void WriteCOMPOOL_AID( const unsigned int addr, const unsigned short idx, const unsigned int val, const unsigned short size );
	void WriteCOMPOOL_AC( const unsigned int addr, const unsigned short idx, const char* val, const unsigned short size_a, const unsigned short size_c );
	// TODO AVS
	// TODO AVD
	// TODO AMS
	// TODO AMD
	void WriteCOMPOOL_ASTRUCT( const unsigned int addr, const unsigned short idx, const void* strct, const unsigned int* sizes, const unsigned int* pos, const unsigned short elcnt, const unsigned short size );

	void WriteCOMPOOL_A2SS( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const float val, const unsigned short size1, const unsigned short size2 );
	void WriteCOMPOOL_A2SD( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const double val, const unsigned short size1, const unsigned short size2 );
	void WriteCOMPOOL_A2IS( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short val, const unsigned short size1, const unsigned short size2 );
	void WriteCOMPOOL_A2ID( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned int val, const unsigned short size1, const unsigned short size2 );
	// TODO AC2
	// TODO AVS2
	// TODO AVD2
	// TODO AMS2
	// TODO AMD2
	// TODO ASTRUCT2

	void WriteCOMPOOL_A3SS( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short idx3, const float val, const unsigned short size1, const unsigned short size2, const unsigned short size3 );
	void WriteCOMPOOL_A3SD( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short idx3, const double val, const unsigned short size1, const unsigned short size2, const unsigned short size3 );
	void WriteCOMPOOL_A3IS( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short idx3, const unsigned short val, const unsigned short size1, const unsigned short size2, const unsigned short size3 );
	void WriteCOMPOOL_A3ID( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short idx3, const unsigned int val, const unsigned short size1, const unsigned short size2, const unsigned short size3 );
	// TODO AC3
	// TODO AVS3
	// TODO AVD3
	// TODO AMS3
	// TODO AMD3
	// TODO ASTRUCT3


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

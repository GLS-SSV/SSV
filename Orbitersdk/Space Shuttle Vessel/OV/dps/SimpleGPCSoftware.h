/****************************************************************************
  This file is part of Space Shuttle Vessel

  Simple GPC Software definition


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
2020/06/20   GLS
2021/06/06   GLS
2021/06/26   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/03/29   GLS
2022/03/31   GLS
2022/04/26   GLS
2022/08/05   GLS
2022/08/20   GLS
********************************************/
#ifndef SIMPLEGPCSOFTWARE_H_C7DDF614_D4FA_4F2E_9CF1_8E21388BC790
#define SIMPLEGPCSOFTWARE_H_C7DDF614_D4FA_4F2E_9CF1_8E21388BC790
#pragma once

#include "SimpleGPCSystem.h"
#include <string>
#include <map>


using namespace discsignals;


namespace dps
{

class SimpleGPCSoftware
{
	SimpleGPCSystem* pGPC;
	std::string ident;
public:
	SimpleGPCSoftware(SimpleGPCSystem* _gpc, const std::string& _ident);
	virtual ~SimpleGPCSoftware();

	const std::string& GetIdentifier() const { return ident; };
	Atlantis* STS() const { return pGPC->STS(); };
	DiscreteBundleManager* BundleManager() const { return pGPC->BundleManager(); };
	unsigned int GetMajorMode() const { return pGPC->GetMajorMode(); };
	void SetMajorMode(unsigned int newMajorMode) const { pGPC->SetMajorMode(newMajorMode); };

	virtual void Realize();

	virtual void OnPreStep(double simt, double simdt, double mjd);
	virtual void OnPostStep(double simt, double simdt, double mjd);
	virtual void OnPropagate(double simt, double simdt, double mjd);

	/**
	 * Returns true if software is active, false if software should not be used in this MM
	 * Called BEFORE MajorMode is changed (GetMajorMode() will return old value)
	 */
	virtual bool OnMajorModeChange(unsigned int newMajorMode);

	/**
	 * Parses single line in scenario
	 * @param keyword string contaning item id
	 * @param value value of parameter(s)
	 */
	virtual bool OnParseLine(const char* keyword, const char* value);
	/**
	 * Save the state of the software
	 */
	virtual void OnSaveState(FILEHANDLE scn) const;

	/**
	 * Handles Item entry on shuttle's keyboard.
	 * Returns true if item/spec are supported, false otherwise.
	 * @param spec spec currently displayed
	 * @param item ITEM number
	 * @param Data string containing data entered
	 * @param IllegalEntry	if an data entry is illegal, this should be set to true
	 */
	virtual bool ItemInput(int spec, int item, const char* Data, bool &IllegalEntry );
	/**
	 * Called when EXEC is pressed and no data has been entered.
	 * Returns true if keypress was handled.
	 */
	virtual bool ExecPressed(int spec);
	/**
	 * Draws display on MDU.
	 * Will only be called for active software
	 * Returns true if data was drawn; false otherwise
	 */
	virtual bool OnPaint(int spec, vc::MDU* pMDU) const;
	SimpleGPCSoftware* FindSoftware(const std::string& identifier) const;

	virtual void ReadILOADs( const std::map<std::string,std::string>& ILOADs );
	static bool GetValILOAD( const std::string& name, const std::map<std::string,std::string>& ILOADs, double& var );
	static bool GetValILOAD( const std::string& name, const std::map<std::string,std::string>& ILOADs, int& var );
	static bool GetValILOAD( const std::string& name, const std::map<std::string,std::string>& ILOADs, unsigned short& var );
	static bool GetValILOAD( const std::string& name, const std::map<std::string,std::string>& ILOADs, unsigned short count, double* var );
	static bool GetValILOAD( const std::string& name, const std::map<std::string,std::string>& ILOADs, unsigned short count, int* var );
	static bool GetValILOAD( const std::string& name, const std::map<std::string,std::string>& ILOADs, unsigned short count, unsigned short* var );

protected:
	/**
	 * Outputs first line of CRT display. Parameter header starts at position 16.
	 */
	void PrintCommonHeader(const char* header, vc::MDU* pMDU) const;

	/**
	 * Converts a string with an decimal number into a signed integer, checking that the string is not empty, the number in the string is an integer and that no further chars exist.
	 * @param data	string to process
	 * @param num	variable where to save the number
	 * @return	true if the string only contains an integer, false otherwise.
	 */
	bool GetIntegerSigned( const char *data, int &num ) const;

	/**
	 * Converts a string with an decimal number into an unsigned integer (by ignoring the sign), checking that the string is not empty, the number in the string is an integer and that no further chars exist.
	 * @param data	string to process
	 * @param num	variable where to save the number
	 * @return	true if the string only contains an integer, false otherwise.
	 */
	bool GetIntegerUnsigned( const char *data, int &num ) const;

	/**
	 * Converts a string with an hexadecimal number into an unsigned integer, checking that the string is not empty, the number in the string is an integer and that no further chars exist.
	 * @param data	string to process
	 * @param num	variable where to save the number
	 * @return	true if the string only contains an integer, false otherwise.
	 */
	bool GetIntegerHex( const char *data, unsigned int &num ) const;

	/**
	 * Converts a string with an decimal number into a signed double, checking that the string is not empty, the number in the string is a double and that no further chars exist.
	 * @param data	string to process
	 * @param num	variable where to save the number
	 * @return	true if the string only contains a double, false otherwise.
	 */
	bool GetDoubleSigned( const char *data, double &num ) const;

	/**
	 * Converts a string with an decimal number into an unsigned double (by ignoring the sign), checking that the string is not empty, the number in the string is a double and that no further chars exist.
	 * @param data	string to process
	 * @param num	variable where to save the number
	 * @return	true if the string only contains a double, false otherwise.
	 */
	bool GetDoubleUnsigned( const char *data, double &num ) const;

	inline unsigned short ReadCOMPOOL_IS( unsigned int addr ) const
	{
		return pGPC->ReadCOMPOOL_IS( addr );
	}

	inline unsigned int ReadCOMPOOL_ID( unsigned int addr ) const
	{
		return pGPC->ReadCOMPOOL_ID( addr );
	}

	inline float ReadCOMPOOL_SD( unsigned int addr ) const
	{
		return pGPC->ReadCOMPOOL_SD( addr );
	}

	inline MATRIX3 ReadCOMPOOL_M( unsigned int addr ) const
	{
		return pGPC->ReadCOMPOOL_M( addr );
	}

	inline float ReadCOMPOOL_M( unsigned int addr, unsigned int m, unsigned int n, unsigned int msize = 3, unsigned int nsize = 3 ) const
	{
		return pGPC->ReadCOMPOOL_M( addr, m, n, msize, nsize );
	}

	inline VECTOR3 ReadCOMPOOL_V( unsigned int addr ) const
	{
		return pGPC->ReadCOMPOOL_V( addr );
	}

	inline float ReadCOMPOOL_V( unsigned int addr, unsigned int n, unsigned int nsize = 3 ) const
	{
		return pGPC->ReadCOMPOOL_V( addr, n, nsize );
	}

	inline void ReadCOMPOOL_C( unsigned int addr, char* val, unsigned int size ) const
	{
		pGPC->ReadCOMPOOL_C( addr, val, size );
		return;
	}

	inline unsigned short ReadCOMPOOL_AIS( unsigned int addr, unsigned int idx, unsigned int size )
	{
		return pGPC->ReadCOMPOOL_AIS( addr, idx, size );
	}

	inline void WriteCOMPOOL_IS( unsigned int addr, unsigned short val )
	{
		pGPC->WriteCOMPOOL_IS( addr, val );
		return;
	}

	inline void WriteCOMPOOL_ID( unsigned int addr, unsigned int val )
	{
		pGPC->WriteCOMPOOL_ID( addr, val );
		return;
	}

	inline void WriteCOMPOOL_SD( unsigned int addr, float val )
	{
		pGPC->WriteCOMPOOL_SD( addr, val );
		return;
	}

	inline void WriteCOMPOOL_M( unsigned int addr, MATRIX3& val )
	{
		pGPC->WriteCOMPOOL_M( addr, val );
		return;
	}
	inline void WriteCOMPOOL_M( unsigned int addr, unsigned int m, unsigned int n, float val, unsigned int msize = 3, unsigned int nsize = 3 )
	{
		pGPC->WriteCOMPOOL_M( addr, m, n, val, msize, nsize );
		return;
	}

	inline void WriteCOMPOOL_V( unsigned int addr, VECTOR3& val )
	{
		pGPC->WriteCOMPOOL_V( addr, val );
		return;
	}

	inline void WriteCOMPOOL_V( unsigned int addr, unsigned int n, float val, unsigned int nsize = 3 )
	{
		pGPC->WriteCOMPOOL_V( addr, n, val, nsize );
		return;
	}

	inline void WriteCOMPOOL_C( unsigned int addr, const char* val, unsigned int size )
	{
		pGPC->WriteCOMPOOL_C( addr, val, size );
		return;
	}

	inline void WriteCOMPOOL_AIS( unsigned int addr, unsigned int idx, unsigned short val, unsigned int size )
	{
		pGPC->WriteCOMPOOL_AIS( addr, idx, val, size );
		return;
	}
};

};

#endif

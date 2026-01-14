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
2020/03/20   GLS
2020/06/20   GLS
2021/06/06   GLS
2021/06/26   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/03/29   GLS
2022/03/31   GLS
2022/04/26   GLS
2022/07/17   GLS
2022/08/05   GLS
2022/08/20   GLS
2022/09/29   GLS
2022/12/01   indy91
2022/12/02   indy91
2022/12/15   indy91
2022/12/18   indy91
2022/12/23   GLS
2023/02/16   indy91
2023/05/27   GLS
2023/10/22   GLS
2024/05/14   GLS
2024/06/16   GLS
2025/07/20   GLS
2025/01/14   GLS
********************************************/
#ifndef _SIMPLEGPCSOFTWARE_H_
#define _SIMPLEGPCSOFTWARE_H_


#include "../SimpleGPCSystem.h"
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

	SimpleGPCSoftware* FindSoftware(const std::string& identifier) const;

	virtual void ReadILOADs( const std::map<std::string,std::string>& ILOADs );
	static bool GetValILOAD( const std::string& name, const std::map<std::string,std::string>& ILOADs, double& var );
	static bool GetValILOAD( const std::string& name, const std::map<std::string,std::string>& ILOADs, int& var );
	static bool GetValILOAD( const std::string& name, const std::map<std::string,std::string>& ILOADs, unsigned short& var );
	static bool GetValILOAD( const std::string& name, const std::map<std::string,std::string>& ILOADs, unsigned short maxlen, char* var );
	static bool GetValILOAD(const std::string& name, const std::map<std::string, std::string>& ILOADs, unsigned short count, float* var);
	static bool GetValILOAD( const std::string& name, const std::map<std::string,std::string>& ILOADs, unsigned short count, double* var );
	static bool GetValILOAD( const std::string& name, const std::map<std::string,std::string>& ILOADs, unsigned short count, int* var );
	static bool GetValILOAD( const std::string& name, const std::map<std::string,std::string>& ILOADs, unsigned short count, unsigned short* var );
	static bool GetValILOAD( const std::string& name, const std::map<std::string,std::string>& ILOADs, unsigned short count, unsigned short maxlen, char** var );
	static bool GetValILOAD( const std::string& name, const std::map<std::string,std::string>& ILOADs, unsigned short count, SCP_DISPCHAR* dc );

protected:
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

	inline float ReadCOMPOOL_SS( const unsigned int addr ) const
	{
		return pGPC->ReadCOMPOOL_SS( addr );
	}

	inline double ReadCOMPOOL_SD( const unsigned int addr ) const
	{
		return pGPC->ReadCOMPOOL_SD( addr );
	}

	inline unsigned short ReadCOMPOOL_IS( const unsigned int addr ) const
	{
		return pGPC->ReadCOMPOOL_IS( addr );
	}

	inline unsigned int ReadCOMPOOL_ID( const unsigned int addr ) const
	{
		return pGPC->ReadCOMPOOL_ID( addr );
	}

	inline void ReadCOMPOOL_C( const unsigned int addr, char* val, const unsigned short size ) const
	{
		pGPC->ReadCOMPOOL_C( addr, val, size );
		return;
	}

	inline float ReadCOMPOOL_VS( const unsigned int addr, const unsigned short n, const unsigned short nsize ) const
	{
		return pGPC->ReadCOMPOOL_VS( addr, n, nsize );
	}

	inline VECTOR3 ReadCOMPOOL_VS( const unsigned int addr ) const
	{
		return pGPC->ReadCOMPOOL_VS( addr );
	}

	inline double ReadCOMPOOL_VD( const unsigned int addr, const unsigned short n, const unsigned short nsize ) const
	{
		return pGPC->ReadCOMPOOL_VD( addr, n, nsize );
	}

	inline VECTOR3 ReadCOMPOOL_VD( const unsigned int addr ) const
	{
		return pGPC->ReadCOMPOOL_VD(addr);
	}

	inline float ReadCOMPOOL_MS( const unsigned int addr, const unsigned short m, const unsigned short n, const unsigned short msize, const unsigned short nsize ) const
	{
		return pGPC->ReadCOMPOOL_MS( addr, m, n, msize, nsize );
	}

	inline MATRIX3 ReadCOMPOOL_MS( const unsigned int addr ) const
	{
		return pGPC->ReadCOMPOOL_MS( addr );
	}

	inline double ReadCOMPOOL_MD( const unsigned int addr, const unsigned short m, const unsigned short n, const unsigned short msize, const unsigned short nsize ) const
	{
		return pGPC->ReadCOMPOOL_MD( addr, m, n, msize, nsize );
	}

	inline MATRIX3 ReadCOMPOOL_MD( const unsigned int addr ) const
	{
		return pGPC->ReadCOMPOOL_MD( addr );
	}

	inline void ReadCOMPOOL_STRUCT( const unsigned int addr, void* strct, const unsigned int* sizes, const unsigned int* pos, const unsigned short elcnt ) const
	{
		pGPC->ReadCOMPOOL_STRUCT( addr, strct, sizes, pos, elcnt );
		return;
	}

	inline float ReadCOMPOOL_ASS( const unsigned int addr, const unsigned short idx, const unsigned short size ) const
	{
		return pGPC->ReadCOMPOOL_ASS( addr, idx, size );
	}

	inline double ReadCOMPOOL_ASD( const unsigned int addr, const unsigned short idx, const unsigned short size ) const
	{
		return pGPC->ReadCOMPOOL_ASD( addr, idx, size );
	}

	inline unsigned short ReadCOMPOOL_AIS( const unsigned int addr, const unsigned short idx, const unsigned short size ) const
	{
		return pGPC->ReadCOMPOOL_AIS( addr, idx, size );
	}

	inline unsigned int ReadCOMPOOL_AID( const unsigned int addr, const unsigned short idx, const unsigned short size ) const
	{
		return pGPC->ReadCOMPOOL_AID( addr, idx, size );
	}

	inline void ReadCOMPOOL_AC( const unsigned int addr, const unsigned short idx, char* val, const unsigned short size_a, const unsigned short size_c ) const
	{
		pGPC->ReadCOMPOOL_AC( addr, idx, val, size_a, size_c );
		return;
	}

	inline void ReadCOMPOOL_ASTRUCT( const unsigned int addr, const unsigned short idx, void* strct, const unsigned int* sizes, const unsigned int* pos, const unsigned short elcnt, const unsigned short size ) const
	{
		pGPC->ReadCOMPOOL_ASTRUCT( addr, idx, strct, sizes, pos, elcnt, size );
		return;
	}

	float ReadCOMPOOL_A2SS( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short size1, const unsigned short size2 ) const
	{
		return pGPC->ReadCOMPOOL_A2SS( addr, idx1, idx2, size1, size2 );
	}

	double ReadCOMPOOL_A2SD( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short size1, const unsigned short size2 ) const
	{
		return pGPC->ReadCOMPOOL_A2SD( addr, idx1, idx2, size1, size2 );
	}

	unsigned short ReadCOMPOOL_A2IS( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short size1, const unsigned short size2 ) const
	{
		return pGPC->ReadCOMPOOL_A2IS( addr, idx1, idx2, size1, size2 );
	}

	unsigned int ReadCOMPOOL_A2ID( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short size1, const unsigned short size2 ) const
	{
		return pGPC->ReadCOMPOOL_A2ID( addr, idx1, idx2, size1, size2 );
	}

	float ReadCOMPOOL_A3SS( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short idx3, const unsigned short size1, const unsigned short size2, const unsigned short size3 ) const
	{
		return pGPC->ReadCOMPOOL_A3SS( addr, idx1, idx2, idx3, size1, size2, size3 );
	}

	double ReadCOMPOOL_A3SD( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short idx3, const unsigned short size1, const unsigned short size2, const unsigned short size3 ) const
	{
		return pGPC->ReadCOMPOOL_A3SD( addr, idx1, idx2, idx3, size1, size2, size3 );
	}

	unsigned short ReadCOMPOOL_A3IS( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short idx3, const unsigned short size1, const unsigned short size2, const unsigned short size3 ) const
	{
		return pGPC->ReadCOMPOOL_A3IS( addr, idx1, idx2, idx3, size1, size2, size3 );
	}

	unsigned int ReadCOMPOOL_A3ID( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short idx3, const unsigned short size1, const unsigned short size2, const unsigned short size3 ) const
	{
		return pGPC->ReadCOMPOOL_A3ID( addr, idx1, idx2, idx3, size1, size2, size3 );
	}


	inline void WriteCOMPOOL_SS( const unsigned int addr, const float val )
	{
		pGPC->WriteCOMPOOL_SS( addr, val );
		return;
	}

	inline void WriteCOMPOOL_SD( const unsigned int addr, const double val )
	{
		pGPC->WriteCOMPOOL_SD( addr, val );
		return;
	}

	inline void WriteCOMPOOL_IS( const unsigned int addr, const unsigned short val )
	{
		pGPC->WriteCOMPOOL_IS( addr, val );
		return;
	}

	inline void WriteCOMPOOL_ID( const unsigned int addr, const unsigned int val )
	{
		pGPC->WriteCOMPOOL_ID( addr, val );
		return;
	}

	inline void WriteCOMPOOL_C( const unsigned int addr, const char* val, const unsigned short size )
	{
		pGPC->WriteCOMPOOL_C( addr, val, size );
		return;
	}

	inline void WriteCOMPOOL_VS( const unsigned int addr, const unsigned short n, const float val, const unsigned short nsize )
	{
		pGPC->WriteCOMPOOL_VS( addr, n, val, nsize );
		return;
	}

	inline void WriteCOMPOOL_VS( const unsigned int addr, const VECTOR3& val )
	{
		pGPC->WriteCOMPOOL_VS( addr, val );
		return;
	}

	inline void WriteCOMPOOL_VD( const unsigned int addr, const unsigned short n, const double val, const unsigned short nsize )
	{
		pGPC->WriteCOMPOOL_VD( addr, n, val, nsize );
		return;
	}

	inline void WriteCOMPOOL_VD( const unsigned int addr, const VECTOR3& val )
	{
		pGPC->WriteCOMPOOL_VD( addr, val );
		return;
	}

	inline void WriteCOMPOOL_MS( const unsigned int addr, const unsigned short m, const unsigned short n, const float val, const unsigned short msize, const unsigned short nsize )
	{
		pGPC->WriteCOMPOOL_MS( addr, m, n, val, msize, nsize );
		return;
	}

	inline void WriteCOMPOOL_MS( const unsigned int addr, const MATRIX3& val )
	{
		pGPC->WriteCOMPOOL_MS( addr, val );
		return;
	}

	inline void WriteCOMPOOL_MD( const unsigned int addr, const unsigned short m, const unsigned short n, const double val, const unsigned short msize, const unsigned short nsize )
	{
		pGPC->WriteCOMPOOL_MD( addr, m, n, val, msize, nsize );
		return;
	}

	inline void WriteCOMPOOL_MD( const unsigned int addr, const MATRIX3& val )
	{
		pGPC->WriteCOMPOOL_MD( addr, val );
		return;
	}

	inline void WriteCOMPOOL_STRUCT( const unsigned int addr, const void* strct, const unsigned int* sizes, const unsigned int* pos, const unsigned short elcnt )
	{
		pGPC->WriteCOMPOOL_STRUCT( addr, strct, sizes, pos, elcnt );
		return;
	}

	inline void WriteCOMPOOL_ASS( const unsigned int addr, const unsigned short idx, float val, const unsigned short size )
	{
		pGPC->WriteCOMPOOL_ASS( addr, idx, val, size );
		return;
	}

	inline void WriteCOMPOOL_ASD( const unsigned int addr, const unsigned short idx, const double val, const unsigned short size )
	{
		pGPC->WriteCOMPOOL_ASD( addr, idx, val, size );
		return;
	}

	inline void WriteCOMPOOL_AIS( const unsigned int addr, const unsigned short idx, const unsigned short val, const unsigned short size )
	{
		pGPC->WriteCOMPOOL_AIS( addr, idx, val, size );
		return;
	}

	inline void WriteCOMPOOL_AID( const unsigned int addr, const unsigned short idx, const unsigned int val, const unsigned short size )
	{
		pGPC->WriteCOMPOOL_AID( addr, idx, val, size );
		return;
	}

	inline void WriteCOMPOOL_AC( const unsigned int addr, const unsigned short idx, const char* val, const unsigned short size_a, const unsigned short size_c )
	{
		pGPC->WriteCOMPOOL_AC( addr, idx, val, size_a, size_c );
		return;
	}

	inline void WriteCOMPOOL_ASTRUCT( const unsigned int addr, const unsigned short idx, const void* strct, const unsigned int* sizes, const unsigned int* pos, const unsigned short elcnt, const unsigned short size )
	{
		pGPC->WriteCOMPOOL_ASTRUCT( addr, idx, strct, sizes, pos, elcnt, size );
		return;
	}

	inline void WriteCOMPOOL_A2SS( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const float val, const unsigned short size1, const unsigned short size2 )
	{
		pGPC->WriteCOMPOOL_A2SS( addr, idx1, idx2, val, size1, size2 );
		return;
	}

	inline void WriteCOMPOOL_A2SD( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const double val, const unsigned short size1, const unsigned short size2 )
	{
		pGPC->WriteCOMPOOL_A2SD( addr, idx1, idx2, val, size1, size2 );
		return;
	}

	inline void WriteCOMPOOL_A2IS( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short val, const unsigned short size1, const unsigned short size2 )
	{
		pGPC->WriteCOMPOOL_A2IS( addr, idx1, idx2, val, size1, size2 );
		return;
	}

	inline void WriteCOMPOOL_A2ID( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned int val, const unsigned short size1, const unsigned short size2 )
	{
		pGPC->WriteCOMPOOL_A2ID( addr, idx1, idx2, val, size1, size2 );
		return;
	}

	inline void WriteCOMPOOL_A3SS( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short idx3, const float val, const unsigned short size1, const unsigned short size2, const unsigned short size3 )
	{
		pGPC->WriteCOMPOOL_A3SS( addr, idx1, idx2, idx3, val, size1, size2, size3 );
		return;
	}

	inline void WriteCOMPOOL_A3SD( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short idx3, const double val, const unsigned short size1, const unsigned short size2, const unsigned short size3 )
	{
		pGPC->WriteCOMPOOL_A3SD( addr, idx1, idx2, idx3, val, size1, size2, size3 );
		return;
	}

	inline void WriteCOMPOOL_A3IS( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short idx3, const unsigned short val, const unsigned short size1, const unsigned short size2, const unsigned short size3 )
	{
		pGPC->WriteCOMPOOL_A3IS( addr, idx1, idx2, idx3, val, size1, size2, size3 );
		return;
	}

	inline void WriteCOMPOOL_A3ID( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short idx3, const unsigned int val, const unsigned short size1, const unsigned short size2, const unsigned short size3 )
	{
		pGPC->WriteCOMPOOL_A3ID( addr, idx1, idx2, idx3, val, size1, size2, size3 );
		return;
	}

	inline double ReadClock()
	{
		return pGPC->ReadClock();
	}
};

}

#endif// _SIMPLEGPCSOFTWARE_H_

/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/06/20   GLS
2021/06/18   GLS
2021/06/26   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/03/29   GLS
2022/03/31   GLS
2022/04/02   GLS
2022/04/26   GLS
2022/05/19   GLS
2022/08/05   GLS
2022/08/21   GLS
2022/09/29   GLS
2022/12/02   indy91
2022/12/23   GLS
2023/02/16   indy91
2023/04/28   GLS
********************************************/
#include "SimpleGPCSoftware.h"
#include "../../Atlantis.h"
#include "../../vc/MDU.h"
#include "../IDP.h"
#include <sstream>


namespace dps
{

SimpleGPCSoftware::SimpleGPCSoftware(SimpleGPCSystem* _gpc, const std::string& _ident)
: pGPC(_gpc), ident(_ident)
{
}

SimpleGPCSoftware::~SimpleGPCSoftware()
{
}

void SimpleGPCSoftware::Realize()
{
}

void SimpleGPCSoftware::OnPreStep(double simt, double simdt, double mjd)
{
}

void SimpleGPCSoftware::OnPostStep(double simt, double simdt, double mjd)
{
}

void SimpleGPCSoftware::OnPropagate(double simt, double simdt, double mjd)
{
}

bool SimpleGPCSoftware::OnMajorModeChange(unsigned int newMajorMode)
{
	return false;
}

bool SimpleGPCSoftware::OnParseLine(const char* keyword, const char* value)
{
	return false;
}

void SimpleGPCSoftware::OnSaveState(FILEHANDLE scn) const
{
}

bool SimpleGPCSoftware::ExecPressed(int spec)
{
	return false;
}

SimpleGPCSoftware* SimpleGPCSoftware::FindSoftware(const std::string& identifier) const
{
	return pGPC->FindSoftware(identifier);
}

void SimpleGPCSoftware::PrintCommonHeader(const char* header, vc::MDU* pMDU) const
{
	pMDU->mvprint( 15, 0, header );
}

bool SimpleGPCSoftware::GetIntegerSigned( const char *data, int &num ) const
{
	char* stmp = NULL;
	int itmp = strtol( data, &stmp, 10 );

	if ((strlen( data ) > 0) && (strlen( stmp ) == 0))
	{
		num = itmp;
		return true;
	}
	else return false;
}

bool SimpleGPCSoftware::GetIntegerUnsigned( const char *data, int &num ) const
{
	bool ret = GetIntegerSigned( data, num );
	num = abs( num );
	return ret;
}

bool SimpleGPCSoftware::GetIntegerHex( const char *data, unsigned int &num ) const
{
	char* stmp = NULL;
	int itmp = strtol( data, &stmp, 16 );

	if ((strlen( data ) > 0) && (strlen( stmp ) == 0))
	{
		num = abs( itmp );
		return true;
	}
	else return false;
}

bool SimpleGPCSoftware::GetDoubleSigned( const char *data, double &num ) const
{
	char* stmp = NULL;
	double dtmp = strtod( data, &stmp );

	if ((strlen( data ) > 0) && (strlen( stmp ) == 0))
	{
		num = dtmp;
		return true;
	}
	else return false;
}

bool SimpleGPCSoftware::GetDoubleUnsigned( const char *data, double &num ) const
{
	bool ret = GetDoubleSigned( data, num );
	num = fabs( num );
	return ret;
}

void SimpleGPCSoftware::ReadILOADs( const std::map<std::string,std::string>& ILOADs )
{
	return;
}

bool SimpleGPCSoftware::GetValILOAD( const std::string& name, const std::map<std::string,std::string>& ILOADs, double& var )
{
	std::map<std::string,std::string>::const_iterator it = ILOADs.find( name );
	if (it != ILOADs.end())
	{
		var = std::stod( it->second );
		return true;
	}
	// log error
	oapiWriteLogV( "(SSV_OV) [ERROR] I-LOAD missing: %s", name.c_str() );
	//throw std::exception( std::string( "I-LOAD missing: " + name ).c_str() );
	return false;
}

bool SimpleGPCSoftware::GetValILOAD( const std::string& name, const std::map<std::string,std::string>& ILOADs, int& var )
{
	std::map<std::string,std::string>::const_iterator it = ILOADs.find( name );
	if (it != ILOADs.end())
	{
		var = std::stoi( it->second );
		return true;
	}
	// log error
	oapiWriteLogV( "(SSV_OV) [ERROR] I-LOAD missing: %s", name.c_str() );
	//throw std::exception( std::string( "I-LOAD missing: " + name ).c_str() );
	return false;
}

bool SimpleGPCSoftware::GetValILOAD( const std::string& name, const std::map<std::string,std::string>& ILOADs, unsigned short& var )
{
	std::map<std::string,std::string>::const_iterator it = ILOADs.find( name );
	if (it != ILOADs.end())
	{
		var = std::stoi( it->second );
		return true;
	}
	// log error
	oapiWriteLogV( "(SSV_OV) [ERROR] I-LOAD missing: %s", name.c_str() );
	//throw std::exception( std::string( "I-LOAD missing: " + name ).c_str() );
	return false;
}

bool SimpleGPCSoftware::GetValILOAD(const std::string& name, const std::map<std::string, std::string>& ILOADs, unsigned short count, float* var)
{
	std::map<std::string, std::string>::const_iterator it = ILOADs.find(name);
	if (it != ILOADs.end())
	{
		unsigned short i = 0;
		float tmp;
		std::stringstream ss(it->second);
		while (ss >> tmp)
		{
			if (i >= count)
			{
				// log error
				oapiWriteLogV("(SSV_OV) [ERROR] I-LOAD with too many elements: %s", name.c_str());
				//throw std::exception( std::string( "I-LOAD with too many elements: " + name ).c_str() );
				return false;
			}
			var[i] = tmp;
			i++;
		}
		if (i != count)
		{
			// log error
			oapiWriteLogV("(SSV_OV) [ERROR] I-LOAD with too few elements: %s", name.c_str());
			//throw std::exception( std::string( "I-LOAD with too few elements: " + name ).c_str() );
			return false;
		}
		return true;
	}
	// log error
	oapiWriteLogV("(SSV_OV) [ERROR] I-LOAD missing: %s", name.c_str());
	//throw std::exception( std::string( "I-LOAD missing: " + name ).c_str() );
	return false;
}

bool SimpleGPCSoftware::GetValILOAD( const std::string& name, const std::map<std::string,std::string>& ILOADs, unsigned short count, double* var )
{
	std::map<std::string,std::string>::const_iterator it = ILOADs.find( name );
	if (it != ILOADs.end())
	{
		unsigned short i = 0;
		double tmp;
		std::stringstream ss( it->second );
		while (ss >> tmp)
		{
			if (i >= count)
			{
				// log error
				oapiWriteLogV( "(SSV_OV) [ERROR] I-LOAD with too many elements: %s", name.c_str() );
				//throw std::exception( std::string( "I-LOAD with too many elements: " + name ).c_str() );
				return false;
			}
			var[i] = tmp;
			i++;
		}
		if (i != count)
		{
			// log error
			oapiWriteLogV( "(SSV_OV) [ERROR] I-LOAD with too few elements: %s", name.c_str() );
			//throw std::exception( std::string( "I-LOAD with too few elements: " + name ).c_str() );
			return false;
		}
		return true;
	}
	// log error
	oapiWriteLogV( "(SSV_OV) [ERROR] I-LOAD missing: %s", name.c_str() );
	//throw std::exception( std::string( "I-LOAD missing: " + name ).c_str() );
	return false;
}

bool SimpleGPCSoftware::GetValILOAD( const std::string& name, const std::map<std::string,std::string>& ILOADs, unsigned short count, int* var )
{
	std::map<std::string,std::string>::const_iterator it = ILOADs.find( name );
	if (it != ILOADs.end())
	{
		unsigned short i = 0;
		int tmp;
		std::stringstream ss( it->second );
		while (ss >> tmp)
		{
			if (i >= count)
			{
				// log error
				oapiWriteLogV( "(SSV_OV) [ERROR] I-LOAD with too many elements: %s", name.c_str() );
				//throw std::exception( std::string( "I-LOAD with too many elements: " + name ).c_str() );
				return false;
			}
			var[i] = tmp;
			i++;
		}
		if (i != count)
		{
			// log error
			oapiWriteLogV( "(SSV_OV) [ERROR] I-LOAD with too few elements: %s", name.c_str() );
			//throw std::exception( std::string( "I-LOAD with too few elements: " + name ).c_str() );
			return false;
		}
		return true;
	}
	// log error
	oapiWriteLogV( "(SSV_OV) [ERROR] I-LOAD missing: %s", name.c_str() );
	//throw std::exception( std::string( "I-LOAD missing: " + name ).c_str() );
	return false;
}

bool SimpleGPCSoftware::GetValILOAD( const std::string& name, const std::map<std::string,std::string>& ILOADs, unsigned short count, unsigned short* var )
{
	std::map<std::string,std::string>::const_iterator it = ILOADs.find( name );
	if (it != ILOADs.end())
	{
		unsigned short i = 0;
		unsigned short tmp;
		std::stringstream ss( it->second );
		while (ss >> tmp)
		{
			if (i >= count)
			{
				// log error
				oapiWriteLogV( "(SSV_OV) [ERROR] I-LOAD with too many elements: %s", name.c_str() );
				//throw std::exception( std::string( "I-LOAD with too many elements: " + name ).c_str() );
				return false;
			}
			var[i] = tmp;
			i++;
		}
		if (i != count)
		{
			// log error
			oapiWriteLogV( "(SSV_OV) [ERROR] I-LOAD with too few elements: %s", name.c_str() );
			//throw std::exception( std::string( "I-LOAD with too few elements: " + name ).c_str() );
			return false;
		}
		return true;
	}
	// log error
	oapiWriteLogV( "(SSV_OV) [ERROR] I-LOAD missing: %s", name.c_str() );
	//throw std::exception( std::string( "I-LOAD missing: " + name ).c_str() );
	return false;
}

}

/****************************************************************************
  This file is part of Space Shuttle Vessel

  HALS-2-cpp


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

#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <map>


using namespace std;

const std::string OTYPE_HALS[9] = {"SCALAR SINGLE", "SCALAR DOUBLE", "INTEGER SINGLE", "INTEGER DOUBLE", "CHARACTER", "SINGLE", "DOUBLE", "VECTOR", "MATRIX"};
const std::string OTYPE_CPP[9] = {"float", "double", "unsigned short", "unsigned int", "char", "float", "double", "", ""};

constexpr unsigned short SCP_TYPE_SS = 1;
constexpr unsigned short SCP_TYPE_SD = 2;
constexpr unsigned short SCP_TYPE_IS = 3;
constexpr unsigned short SCP_TYPE_ID = 4;
constexpr unsigned short SCP_TYPE_C = 5;
constexpr unsigned short SCP_TYPE_VS = 6;
constexpr unsigned short SCP_TYPE_VD = 7;
constexpr unsigned short SCP_TYPE_MS = 8;
constexpr unsigned short SCP_TYPE_MD = 9;
constexpr unsigned short SCP_TYPE_STRUCT = 10;

constexpr unsigned short SCP_TYPE_ASS = 101;
constexpr unsigned short SCP_TYPE_ASD = 102;
constexpr unsigned short SCP_TYPE_AIS = 103;
constexpr unsigned short SCP_TYPE_AID = 104;
constexpr unsigned short SCP_TYPE_AC = 105;
constexpr unsigned short SCP_TYPE_AVS = 106;
constexpr unsigned short SCP_TYPE_AVD = 107;
constexpr unsigned short SCP_TYPE_AMS = 108;
constexpr unsigned short SCP_TYPE_AMD = 109;
constexpr unsigned short SCP_TYPE_ASTRUCT = 110;


std::vector<std::pair<string, unsigned int>> knownSTRUCTURE;


// C hello!
//  DECLARE WOWLON INTEGER SINGLE;
// C stuff
//  DECLARE PHIC_AL SCALAR DOUBLE;
//  DECLARE X0 ARRAY(2) SCALAR DOUBLE;
// C stuff and stuff
//  DECLARE X_EXP MATRIX(2,2) SCALAR DOUBLE;

vector<string> split(const string& str, const string& delim)
{
	vector<string> tokens;
	size_t prev = 0, pos = 0;
	do
	{
		pos = str.find(delim, prev);
		if (pos == string::npos) pos = str.length();
		string token = str.substr(prev, pos-prev);
		if (!token.empty()) tokens.push_back(token);
		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());
	return tokens;
}


int calcpadding( int& pos, const int sz )
{
	int p = pos % sz;
	if (p != 0)
	{
		pos += sz - p;
	}
	return pos;
}

/**
 * Process SCALAR type.
 * @arg v	string array of split line contents
 * @arg vi	current index of v
 * @arg otypei	index for type output string
 * @arg size	type size
 **/
void typeSCALAR( const vector<string>& v, const unsigned int vi, unsigned int& otypei, unsigned int& size )
{
	if (v.size() == (vi + 1))// no precision
	{
		// SCALAR SINGLE
		otypei = 0;
		size = 2;
	}
	else if (v[vi + 1].find("SINGLE") != string::npos)
	{
		// SCALAR SINGLE
		otypei = 0;
		size = 2;
	}
	else if (v[vi + 1].find("DOUBLE") != string::npos)
	{
		// SCALAR DOUBLE
		otypei = 1;
		size = 4;
	}
	else
	{
		throw "illegal SCALAR keyword";
	}
	return;
}

/**
 * Process INTEGER type.
 * @arg v	string array of split line contents
 * @arg vi	current index of v
 * @arg otypei	index for type output string
 * @arg size	type size
 **/
void typeINTEGER( const vector<string>& v, const unsigned int vi, unsigned int& otypei, unsigned int& size )
{
	if (v.size() == (vi + 1))// no precision
	{
		// INTEGER SINGLE
		otypei = 2;
		size = 1;
	}
	else if (v[vi + 1].find("SINGLE") != string::npos)
	{
		// INTEGER SINGLE
		otypei = 2;
		size = 1;
	}
	else if (v[vi + 1].find("DOUBLE") != string::npos)
	{
		// INTEGER DOUBLE
		otypei = 3;
		size = 2;
	}
	else
	{
		throw "illegal INTEGER keyword";
	}
	return;
}

/**
 * Process CHARACTER type.
 * @arg v	string array of split line contents
 * @arg vi	current index of v
 * @arg otypei	index for type output string
 * @arg size	type size
 * @arg len	string length
 **/
void typeCHARACTER( const vector<string>& v, const unsigned int vi, unsigned int& otypei, unsigned int& size, unsigned int& len )
{
	// get char count
	string tmp = v[vi].substr( 10, v[vi].find( ")" ) - 10 );
	int count = stoi( tmp );

	if ((count < 1) || (count > 255)) throw "illegal CHARACTER size";

	len = count;
	size = (count / 2) + (count % 2);// pack 2 chars in 1 short
	otypei = 4;
	return;
}

/**
 * Process VECTOR type.
 * @arg v	string array of split line contents
 * @arg vi	current index of v
 * @arg otypei	index for type output string
 * @arg size	type size
 * @arg len	vector length
 **/
void typeVECTOR( const vector<string>& v, const unsigned int vi, unsigned int& otypei, unsigned int& size, unsigned int& len )
{
	len = 3;// default

	// get array length
	if (v[vi].find( ")" ) != string::npos)
	{
		string tmp = v[vi].substr( 7, v[vi].find( ")" ) - 7 );
		len = stoi( tmp );
	}

	if ((len <= 1) || (len > 64)) throw "illegal VECTOR size";

	if (v.size() == (vi + 1))// no precision
	{
		// SCALAR SINGLE
		otypei = 5;
		size = len * 2;
	}
	else if (v[vi + 1].find( "SINGLE" ) != string::npos)
	{
		// SCALAR SINGLE
		otypei = 5;
		size = len * 2;
	}
	else if (v[vi + 1].find( "DOUBLE" ) != string::npos)
	{
		// SCALAR DOUBLE
		otypei = 6;
		size = len * 4;
	}
	else
	{
		throw "illegal VECTOR keyword";
	}
	return;
}

/**
 * Process MATRIX type.
 * @arg v	string array of split line contents
 * @arg vi	current index of v
 * @arg otypei	index for type output string
 * @arg size	type size
 * @arg len1	matrix length 1
 * @arg len2	matrix length 2
 **/
void typeMATRIX( const vector<string>& v, const unsigned int vi, unsigned int& otypei, unsigned int& size, unsigned int& len1, unsigned int& len2 )
{
	len1 = 3;// default
	len2 = 3;// default

	// get array length
	if ((v[vi].find( ")" ) != string::npos) && (v[vi].find( "," ) != string::npos))
	{
		string tmp = v[vi].substr( 7, v[vi].find( "," ) - 7 );
		len1 = stoi( tmp );
		tmp = v[vi].substr( v[vi].find( "," ) + 1, v[vi].find( ")" ) - v[vi].find( "," ) + 1 );
		len2 = stoi( tmp );
	}

	if ((len1 <= 1) || (len1 > 64)) throw "illegal MATRIX size 1";
	if ((len2 <= 1) || (len2 > 64)) throw "illegal MATRIX size 2";

	if (v.size() == (vi + 1))// no precision
	{
		// SCALAR SINGLE
		otypei = 5;
		size = len1 * len2 * 2;
	}
	else if (v[vi + 1].find( "SINGLE" ) != string::npos)
	{
		// SCALAR SINGLE
		otypei = 5;
		size = len1 * len2 * 2;
	}
	else if (v[vi + 1].find( "DOUBLE" ) != string::npos)
	{
		// SCALAR DOUBLE
		otypei = 6;
		size = len1 * len2 * 4;
	}
	else
	{
		throw "illegal MATRIX keyword";
	}
	return;
}

/**
 * Process STRUCTURE type.
 * @arg v	string array of split line contents
 * @arg vi	current index of v
 * @arg size	type size
 * @arg len	structure count
 **/
void typeSTRUCTURE( const vector<string>& v, const unsigned int vi, unsigned int& size, unsigned int& len )
{
	len = 1;

	// check if multiple copies
	if (v[vi].find( ")" ) != string::npos)
	{
		string tmp = v[vi].substr( v[vi].find( "(" ) + 1, v[vi].find( ")" ) - v[vi].find( "(" ) + 1 );
		len = stoi( tmp );

		if ((len < 2) || (len > 32767)) throw "illegal STRUCTURE size";
	}

	string strname = v[vi].substr( 0, v[vi].find( "-" ) );
	auto it = find_if( knownSTRUCTURE.begin(), knownSTRUCTURE.end(), [&strname](const pair<string, unsigned int>& element){ return element.first == strname;} );
	if (it == knownSTRUCTURE.end())
	{
		// not found
		throw "unknown STRUCTURE";
	}
	
	size = len * it->second;
	return;
}

/**
 * Process ARRAY type.
 * @arg v	string array of split line contents
 * @arg vi	current index of v
 * @arg otypei	index for type output string
 * @arg ostypei	index for sub-type output string
 * @arg size	type size
 * @arg len	array length
 * @arg lent1	sub-type length 1
 * @arg lent2	sub-type length 2
 **/
void typeARRAY( const vector<string>& v, const unsigned int vi, unsigned int& otypei, unsigned int& ostypei, unsigned int& size, unsigned int& len, unsigned int& lent1, unsigned int& lent2 )
{
	// TODO add missing types: BIT, BOOLEAN ?
	lent1 = 0;
	lent2 = 0;

	// get array size
	string tmp = v[vi].substr( 6, v[vi].find( ")" ) - 6 );
	len = stoi( tmp );

	if ((len <= 1) || (len >= 32768)) throw "illegal ARRAY size";

	size = len;

	if (v.size() == (vi + 1))
	{
		// SCALAR SINGLE
		otypei = 0;
		size *= 2;
		// TODO delete <;> in oname
	}
	else if (v[vi + 1] == "SINGLE;")
	{
		// SCALAR SINGLE
		otypei = 0;
		size *= 2;
	}
	else if (v[vi + 1] == "DOUBLE;")
	{
		// SCALAR DOUBLE
		otypei = 1;
		size *= 4;
	}
	else if (v[vi + 1].find( "SCALAR" ) != string::npos)
	{
		//// SCALAR ////
		unsigned int sz = 0;
		typeSCALAR( v, vi + 1, otypei, sz );
		size *= sz;
	}
	else if (v[vi + 1].find( "INTEGER" ) != string::npos)
	{
		//// INTEGER ////
		unsigned int sz = 0;
		typeINTEGER( v, vi + 1, otypei, sz );
		size *= sz;
	}
	else if (v[vi + 1].find( "CHARACTER" ) != string::npos)
	{
		//// CHARACTER ////
		unsigned int sz = 0;
		typeCHARACTER( v, vi + 1, otypei, sz, lent1 );
		size *= sz;
	}
	else if (v[vi + 1].find( "VECTOR" ) != string::npos)
	{
		//// VECTOR ////
		unsigned int sz = 0;
		typeVECTOR( v, vi + 1, ostypei, sz, lent1 );
		otypei = 7;
		size *= sz;
	}
	else if (v[vi + 1].find( "MATRIX" ) != string::npos)
	{
		//// MATRIX ////
		unsigned int sz = 0;
		typeMATRIX( v, vi + 1, ostypei, sz, lent1, lent2 );
		otypei = 8;
		size *= sz;
	}
	else
	{
		// error
		throw "unknown ARRAY type";
	}
	return;
}


int main( int argc, char* argv[] )
{
	if (argc != 3) return 1;

	unsigned int addr = 0;
	int ret = 0;
	ifstream in;
	ofstream out;
	string iline;
	string oline;
	string otype;
	string oname;
	string oaddr;
	in.open( argv[1] );
	out.open( argv[2] );

	// extract COMPOOL name from output filename
	string name = string( argv[2] );
	size_t p = name.find_last_of( '.' );
	if (p != string::npos) name = name.substr( 0, p );

	p = name.find_last_of( '\\' );
	if (p != string::npos) name = name.substr( p + 1, name.length() - p );

	for (auto & x: name) x = (char)toupper( x );

	vector<string> v;
	vector<string> var;
	map<unsigned int/*addr*/, unsigned short/*type*/> typecheck;

	try
	{
		out << "#ifndef _" << name << "_H_" << "\n";
		out << "#define _" << name << "_H_" << "\n" << "\n";

		while (getline( in, iline ))
		{
			//// comments ////
			if (iline[0] == 'C')
			{
				if (iline.length() > 2)// C<space>
					out << "// " + iline.substr( 2 ) + "\n";
				else
					out << "\n";
				continue;
			}

			//// types ////
			v = split( iline, " " );
			// v[0] <tab>DECLARE	| <tab>STRUCTURE
			// v[1] <name><;>
			// v[2] vector/matrix	|	<type>		| char<;>
			// v[3] <type>		|	<precision><;>
			// v[4] <precision><;>

			if (v.size() < 2) throw "bad line: " + iline;
			if (v[0] == "\tDECLARE")
			{
				std::stringstream strm;
				strm << "0x" << std::setfill( '0' ) << std::setw( 5 ) << std::hex << addr;
				oaddr = strm.str();

				oline = "inline constexpr unsigned int SCP_";
				oname = v[1];

				if (v.size() == 2)
				{
					// SCALAR SINGLE
					typecheck.insert( {addr, SCP_TYPE_SS} );
					otype = "SCALAR SINGLE";
					addr += 2;
					// TODO delete <;> in oname
				}
				else if (v[2] == "SINGLE;")
				{
					// SCALAR SINGLE
					typecheck.insert( {addr, SCP_TYPE_SS} );
					otype = "SCALAR SINGLE";
					addr += 2;
				}
				else if (v[2] == "DOUBLE;")
				{
					// SCALAR DOUBLE
					typecheck.insert( {addr, SCP_TYPE_SS} );
					otype = "SCALAR DOUBLE";
					addr += 4;
				}
				else if (v[2].find( "SCALAR" ) != string::npos)
				{
					//// SCALAR ////
					unsigned int oti = 0;
					unsigned int sz = 0;
					typeSCALAR( v, 2, oti, sz );
					typecheck.insert( {addr, (oti == 0) ? SCP_TYPE_SS : SCP_TYPE_SD} );
					otype = OTYPE_HALS[oti];
					addr += sz;
				}
				else if (v[2].find( "INTEGER" ) != string::npos)
				{
					//// INTEGER ////
					unsigned int oti = 0;
					unsigned int sz = 0;
					typeINTEGER( v, 2, oti, sz );
					typecheck.insert( {addr, (oti == 2) ? SCP_TYPE_IS : SCP_TYPE_ID} );
					otype = OTYPE_HALS[oti];
					addr += sz;
				}
				else if (v[2].find( "CHARACTER" ) != string::npos)
				{
					//// CHARACTER ////
					unsigned int oti = 0;
					unsigned int sz = 0;
					unsigned int ln = 0;
					typeCHARACTER( v, 2, oti, sz, ln );
					typecheck.insert( {addr, SCP_TYPE_C} );
					otype = OTYPE_HALS[oti] + "(" + std::to_string( ln ) + ")";
					addr += sz;
				}
				else if (v[2].find( "VECTOR" ) != string::npos)
				{
					//// VECTOR ////
					unsigned int oti = 0;
					unsigned int sz = 0;
					unsigned int ln = 0;
					typeVECTOR( v, 2, oti, sz, ln );
					typecheck.insert( {addr, (oti == 5) ? SCP_TYPE_VS : SCP_TYPE_VD} );
					otype = "VECTOR(" + std::to_string( ln ) + ") " + OTYPE_HALS[oti];
					addr += sz;
				}
				else if (v[2].find( "MATRIX" ) != string::npos)
				{
					//// MATRIX ////
					unsigned int oti = 0;
					unsigned int sz = 0;
					unsigned int ln1 = 0;
					unsigned int ln2 = 0;
					typeMATRIX( v, 2, oti, sz, ln1, ln2 );
					typecheck.insert( {addr, (oti == 5) ? SCP_TYPE_MS : SCP_TYPE_MD} );
					otype = "MATRIX(" + std::to_string( ln1 ) + "," + std::to_string( ln2 ) + ") " + OTYPE_HALS[oti];
					addr += sz;
				}
				else if (v[2].find( "ARRAY" ) != string::npos)
				{
					//// ARRAY ////
					unsigned int oti = 0;
					unsigned int osti = 999;
					unsigned int sz = 0;
					unsigned int ln = 0;
					unsigned int lnt1 = 0;
					unsigned int lnt2 = 0;
					typeARRAY( v, 2, oti, osti, sz, ln, lnt1, lnt2 );
					switch (oti)
					{
						case 0:
							typecheck.insert( {addr, SCP_TYPE_ASS} );
							break;
						case 1:
							typecheck.insert( {addr, SCP_TYPE_ASD} );
							break;
						case 2:
							typecheck.insert( {addr, SCP_TYPE_AIS} );
							break;
						case 3:
							typecheck.insert( {addr, SCP_TYPE_AID} );
							break;
						case 4:
							typecheck.insert( {addr, SCP_TYPE_AC} );
							break;
						case 7:
							typecheck.insert( {addr, (oti == 5) ? SCP_TYPE_AVS : SCP_TYPE_AVD} );
							break;
						case 8:
							typecheck.insert( {addr, (oti == 5) ? SCP_TYPE_AMS : SCP_TYPE_AMD} );
							break;
					}

					otype = "ARRAY(" + std::to_string( ln ) + ") " + OTYPE_HALS[oti];

					if (lnt2 != 0) otype += "(" + std::to_string( lnt1 ) + "," + std::to_string( lnt2 ) + ")";
					else if (lnt1 != 0) otype += "(" + std::to_string( lnt1 ) + ")";

					if (osti != 999) otype += " " + OTYPE_HALS[osti];

					addr += sz;
				}
				else if (v[2].find( "-STRUCTURE" ) != string::npos)
				{
					//// STRUCTURE ////
					unsigned int sz = 0;
					unsigned int ln = 0;
					typeSTRUCTURE( v, 2, sz, ln );
					typecheck.insert( {addr, (ln > 1) ? SCP_TYPE_ASTRUCT : SCP_TYPE_STRUCT} );
					otype = v[2].substr( 0, v[2].length() - 1 );
					addr += sz;
				}
				// TODO BIT, BOOLEAN ?
				else
				{
					// error
					throw "unknown type";
				}

				oline += oname + " = " + oaddr + ";// " + otype;
				out << oline << "\n";


				// check for repeated name
				if (std::find( var.begin(), var.end(), oname ) != var.end())
				{
					cout << "ERROR repeated variable name: " << oname << "\n";
					ret |= 2;
				}
				else var.push_back( oname );
			}
			else if (v[0] == "\tSTRUCTURE")
			{
				// STRUCTURE
				vector<int> sizes;// [2 bytes]
				vector<int> pos;// [byte]
				int curpos = 0;// [byte]
				oline = "struct SCP_";
				string strctname = v[1].substr( 0, v[1].find( ":" ) );
				oline += strctname;
				out << oline << "\n";
				out << "{" << "\n";

				while (getline( in, iline ))
				{
					//// comments ////
					if (iline[0] == 'C')
					{
						if (iline.length() > 2)// C<space>
							out << "\t// " + iline.substr( 2 ) + "\n";
						else
							out << "\n";
						continue;
					}

					v = split( iline, " " );
					// v[0] <level>
					// v[1] <name>
					// v[2] vector/matrix	|	<type>		| char<;>
					// v[3] <type>		|	<precision><;>
					// v[4] <precision><;>

					if (v.size() < 2) throw "bad line: " + iline;
					if (v.size() == 2)
					{
						// SCALAR SINGLE
						otype = OTYPE_CPP[0];
						sizes.push_back( 2 );
						pos.push_back( calcpadding( curpos, 4 ) );
						curpos += 4;
						// TODO delete <,> or <;> in oname
					}
					else if (v[2].find( "SINGLE" ) != string::npos)
					{
						// SCALAR SINGLE
						otype = OTYPE_CPP[0];
						sizes.push_back( 2 );
						pos.push_back( calcpadding( curpos, 4 ) );
						curpos += 4;
					}
					else if (v[2].find( "DOUBLE" ) != string::npos)
					{
						// SCALAR DOUBLE
						otype = OTYPE_CPP[1];
						sizes.push_back( 4 );
						pos.push_back( calcpadding( curpos, 8 ) );
						curpos += 8;
					}
					else if (v[2].find( "INTEGER" ) != string::npos)
					{
						//// INTEGER ////
						unsigned int oti = 0;
						unsigned int sz = 0;
						typeINTEGER( v, 2, oti, sz );
						sizes.push_back( sz );
						pos.push_back( calcpadding( curpos, sz * 2 ) );
						curpos += (sz * 2);

						out << "\t" << OTYPE_CPP[oti] << " " << v[1] << ";\n";
					}
					else if (v[2].find( "SCALAR" ) != string::npos)
					{
						//// SCALAR ////
						unsigned int oti = 0;
						unsigned int sz = 0;
						typeSCALAR( v, 2, oti, sz );
						sizes.push_back( sz );
						pos.push_back( calcpadding( curpos, sz * 2 ) );
						curpos += (sz * 2);

						out << "\t" << OTYPE_CPP[oti] << " " << v[1] << ";\n";
					}
					else if (v[2].find( "CHARACTER" ) != string::npos)
					{
						//// CHARACTER ////
						unsigned int oti = 0;
						unsigned int sz = 0;
						unsigned int ln = 0;
						typeCHARACTER( v, 2, oti, sz, ln );
						sizes.push_back( sz );
						pos.push_back( curpos );
						curpos += ln;

						out << "\t" << OTYPE_CPP[oti] << " " << v[1] << "[" << ln << "]" << ";\n";
					}
					else if (v[2].find( "VECTOR" ) != string::npos)
					{
						//// VECTOR ////
						unsigned int oti = 0;
						unsigned int sz = 0;
						unsigned int ln = 0;
						typeVECTOR( v, 2, oti, sz, ln );
						sizes.push_back( sz );
						pos.push_back( calcpadding( curpos, (sz * 2) / ln ) );
						curpos += (sz * 2);

						out << "\t" << OTYPE_CPP[oti] << " " << v[1] << "[" << ln << "]" << ";\n";
					}
					else if (v[2].find( "MATRIX" ) != string::npos)
					{
						//// MATRIX ////
						unsigned int oti = 0;
						unsigned int sz = 0;
						unsigned int ln1 = 0;
						unsigned int ln2 = 0;
						typeMATRIX( v, 2, oti, sz, ln1, ln2 );
						sizes.push_back( sz );
						pos.push_back( calcpadding( curpos, (sz * 2) / (ln1 * ln2) ) );
						curpos += (sz * 2);

						out << "\t" << OTYPE_CPP[oti] << " " << v[1] << "[" << ln1 << "]" << "[" << ln2 << "]" << ";\n";
					}
					else if (v[2].find( "ARRAY" ) != string::npos)
					{
						//// ARRAY ////
						unsigned int oti = 0;
						unsigned int osti = 0;
						unsigned int sz = 0;
						unsigned int ln = 0;
						unsigned int lnt1 = 0;
						unsigned int lnt2 = 0;
						typeARRAY( v, 2, oti, osti, sz, ln, lnt1, lnt2 );
						sizes.push_back( sz );

						if (lnt2 != 0)
						{
							pos.push_back( calcpadding( curpos, (sz * 2) / (ln * lnt1 * lnt2) ) );
							out << "\t" << OTYPE_CPP[oti] << " " << v[1] << "[" << ln << "]" << "[" << lnt1 << "]" << "[" << lnt2 << "]" << ";\n";
						}
						else if (lnt1 != 0)
						{
							pos.push_back( calcpadding( curpos, (sz * 2) / (ln * lnt1) ) );
							out << "\t" << OTYPE_CPP[oti] << " " << v[1] << "[" << ln << "]" << "[" << lnt1 << "]" << ";\n";
						}
						else
						{
							pos.push_back( calcpadding( curpos, (sz * 2) / ln ) );
							out << "\t" << OTYPE_CPP[oti] << " " << v[1] << "[" << ln << "]" << ";\n";
						}
						curpos += (sz * 2);
					}
					else
					{
						throw "unsupported STRUCTURE type";
					}

					// until line ends with ';'
					if (iline.find( ";" ) != string::npos)
					{
						break;
					}
				}
				out << "};" << "\n";

				// output sizes, converting to bytes
				oline = "";
				for (size_t i = 0; i < sizes.size(); i++) oline += " " + to_string( sizes[i] * 2 ) + ",";
				if (oline.length() > 0) oline.pop_back();
				out << "inline constexpr unsigned int sizes_" << strctname << "[] = {" << oline << " };\n";

				oline = "";
				for (size_t i = 0; i < pos.size(); i++) oline += " " + to_string( pos[i] ) + ",";
				if (oline.length() > 0) oline.pop_back();
				out << "inline constexpr unsigned int pos_" << strctname << "[] = {" << oline << " };\n";

				out << "inline constexpr unsigned short cnt_" << strctname << " = " << pos.size() << ";\n";

				// check for repeated name
				if (std::find( var.begin(), var.end(), strctname ) != var.end())
				{
					cout << "ERROR repeated variable name: " << strctname << "\n";
					ret |= 2;
				}
				else var.push_back( strctname );

				// save strctname and size
				int fullsize = reduce( sizes.begin(), sizes.end() );
				knownSTRUCTURE.push_back( make_pair( strctname, fullsize ) );
			}
		}

		oline = "\ninline constexpr unsigned int SIMPLE" + name + "_SIZE = " + std::to_string( addr ) + ";";
		out << oline << "\n" << "\n";

#if _DEBUG
		// dump type check stuff
		if (typecheck.size() != 0)
		{
			out << "\n";
			out << "#include <map>\n";

			out << "inline constexpr unsigned short SCP_TYPE_SS = 1;\n";
			out << "inline constexpr unsigned short SCP_TYPE_SD = 2;\n";
			out << "inline constexpr unsigned short SCP_TYPE_IS = 3;\n";
			out << "inline constexpr unsigned short SCP_TYPE_ID = 4;\n";
			out << "inline constexpr unsigned short SCP_TYPE_C = 5;\n";
			out << "inline constexpr unsigned short SCP_TYPE_VS = 6;\n";
			out << "inline constexpr unsigned short SCP_TYPE_VD = 7;\n";
			out << "inline constexpr unsigned short SCP_TYPE_MS = 8;\n";
			out << "inline constexpr unsigned short SCP_TYPE_MD = 9;\n";
			out << "inline constexpr unsigned short SCP_TYPE_STRUCT = 10;\n";

			out << "inline constexpr unsigned short SCP_TYPE_ASS = 101;\n";
			out << "inline constexpr unsigned short SCP_TYPE_ASD = 102;\n";
			out << "inline constexpr unsigned short SCP_TYPE_AIS = 103;\n";
			out << "inline constexpr unsigned short SCP_TYPE_AID = 104;\n";
			out << "inline constexpr unsigned short SCP_TYPE_AC = 105;\n";
			out << "inline constexpr unsigned short SCP_TYPE_AVS = 106;\n";
			out << "inline constexpr unsigned short SCP_TYPE_AVD = 107;\n";
			out << "inline constexpr unsigned short SCP_TYPE_AMS = 108;\n";
			out << "inline constexpr unsigned short SCP_TYPE_AMD = 109;\n";
			out << "inline constexpr unsigned short SCP_TYPE_ASTRUCT = 110;\n";

			out << "\n";

			out << "const std::map<unsigned int, unsigned short> SCP_TYPE_CHECK_LIST = {\n";

			for (std::map<unsigned int, unsigned short>::iterator it = typecheck.begin(); it != typecheck.end(); ++it)
			{
				out << "\t{" << it->first << "," << it->second << "}";
				if ((it != typecheck.end()) && (it == --typecheck.end()))
				{
					out << "\n\t};\n\n";
					break;
				}
				else
				{
					out << ",\n";
				}
			}
		}
#endif// _DEBUG

		out << "#endif// _" << name << "_H_" << "\n";
	}
	catch (const std::string err)
	{
		cout << "ERROR (" << err << ") processing line: " << iline;
		ret |= 1;
	}
	catch (const char* err)
	{
		cout << "ERROR (" << err << ") processing line: " << iline;
		ret |= 1;
	}
	catch (...)
	{
		cout << "ERROR processing line: " << iline;
		ret |= 1;
	}

	in.close();
	out.close();
	return ret;
}

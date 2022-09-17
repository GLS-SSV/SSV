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


using namespace std;

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

int main( int argc, char* argv[] )
{
	if (argc != 3) return 1;

	unsigned int addr = 0;
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

			//// vars ////
			v = split( iline, " " );
			// v[0] <tab>DECLARE
			// v[1] name
			// v[2] vector/matrix	|	type		| char<;>
			// v[3] type		|	size<;>
			// v[4] size<;>

			oline = "inline constexpr unsigned int SCP_";
			oname = v[1];
			std::stringstream strm;
			strm << "0x" << std::setfill( '0' ) << std::setw( 5 ) << std::hex << addr;
			oaddr = strm.str();

			if (v[2].find( "INTEGER" ) != string::npos)
			{
				//// INTEGER ////
				if (v[3].find( "SINGLE" ) != string::npos)
				{
					// INTEGER SINGLE
					otype = "INTEGER SINGLE";
					addr++;
				}
				else if (v[3].find( "DOUBLE" ) != string::npos)
				{
					// INTEGER DOUBLE
					otype = "INTEGER DOUBLE";
					addr += 2;
				}
				// TODO if no SINGLE or DOUBLE = SINGLE
			}
			else if (v[2].find( "SCALAR" ) != string::npos)
			{
				//// SCALAR ////
				// INFO assume DOUBLE
				otype = "SCALAR DOUBLE";
				addr += 2;
				// TODO SCALAR is optional
			}
			else if (v[2].find( "CHARACTER" ) != string::npos)
			{
				//// CHARACTER ////
				unsigned int shift = 1;

				// get char count
				string tmp = v[2].substr( 10, v[2].find( ")" ) - 10 );
				int size = stoi( tmp );

				if ((size <= 0) || (size >= 255)) throw "illegal size";

				shift *= size;

				otype = "CHARACTER(" + std::to_string( size ) + ")";
				addr += shift;
			}
			else if (v[2].find( "VECTOR" ) != string::npos)
			{
				//// VECTOR ////
				// INFO assume DOUBLE
				unsigned int shift = 1;

				// get array size
				string tmp = v[2].substr( 7, v[2].find( ")" ) - 7 );
				int size = stoi( tmp );

				if ((size <= 1) || (size > 64)) throw "illegal size";

				shift *= size;

				//if (v[3].find( "SINGLE" ) != string::npos)
				//{
					// SCALAR SINGLE
					//otype = "SINGLE";
					//shift *= 1;
				//}
				//else if (v[3].find( "DOUBLE" ) != string::npos)
				//{
					// SCALAR DOUBLE
					//otype = "";// TODO
					shift *= 2;
				//}

				otype = "VECTOR(" + std::to_string( size ) + ") DOUBLE";
				addr += shift;
				// TODO no size = (3)
			}
			else if (v[2].find( "MATRIX" ) != string::npos)
			{
				//// MATRIX ////
				// INFO assume DOUBLE
				unsigned int shift = 1;

				// get matrix dimensions
				string tmp = v[2].substr( 7, v[2].find( "," ) - 7 );
				int size1 = stoi( tmp );
				tmp = v[2].substr( v[2].find( "," ) + 1, v[2].find( ")" ) - v[2].find( "," ) + 1 );
				int size2 = stoi( tmp );

				if ((size1 <= 1) || (size1 > 64)) throw "illegal size";
				if ((size2 <= 1) || (size2 > 64)) throw "illegal size";

				shift *= size1 * size2;

				//if (v[3].find( "SINGLE" ) != string::npos)
				//{
					// SCALAR SINGLE
					//otype = "";// TODO
					//shift *= 1;
				//}
				//else if (v[3].find( "DOUBLE" ) != string::npos)
				//{
					// SCALAR DOUBLE
					//otype = "";// TODO
					shift *= 2;
				//}

				otype = "MATRIX(" + std::to_string( size1 ) + "," + std::to_string( size2 ) + ") DOUBLE";
				addr += shift;
				// TODO no dimensions = (3,3)
			}
			else if (v[2].find( "ARRAY" ) != string::npos)
			{
				//// ARRAY ////
				unsigned int shift = 1;

				// get array size
				string tmp = v[2].substr( 6, v[2].find( ")" ) - 6 );
				int size = stoi( tmp );

				if ((size <= 1) || (size >= 32768)) throw "illegal size";

				shift *= size;

				if (v[3].find( "INTEGER" ) != string::npos)
				{
					if (v[4].find( "SINGLE" ) != string::npos)
					{
						// INTEGER SINGLE
						otype = "INTEGER SINGLE";
						shift *= 1;
					}
					else if (v[4].find( "DOUBLE" ) != string::npos)
					{
						// INTEGER DOUBLE
						otype = "INTEGER DOUBLE";
						shift *= 2;
					}
				}
				else if (v[3].find( "SCALAR" ) != string::npos)
				{
					//if (v[4].find( "SINGLE" ) != string::npos)
					//{
						// SCALAR SINGLE
						//otype = "";// TODO
						//shift *= 1;
					//}
					//else if (v[4].find( "DOUBLE" ) != string::npos)
					//{
						// SCALAR DOUBLE
						otype = "SCALAR DOUBLE";
						shift *= 2;
					//}
				}

				otype = "ARRAY(" + std::to_string( size ) + ") " + otype;
				addr += shift;
				// TODO if no type = SCALAR SINGLE?
				// TODO add missing types
			}
			// TODO BOOLEAN
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
			}
			else var.push_back( oname );
		}

		oline = "\ninline constexpr unsigned int SIMPLE" + name + "_SIZE = " + std::to_string( addr ) + ";";
		out << oline << "\n" << "\n";

		out << "#endif// _" << name << "_H_" << "\n";
	}
	catch (const char* err)
	{
		cout << "ERROR (" << err << ") processing line: " << iline;
	}
	catch (...)
	{
		cout << "ERROR processing line: " << iline;
	}

	in.close();
	out.close();
	return 0;
}

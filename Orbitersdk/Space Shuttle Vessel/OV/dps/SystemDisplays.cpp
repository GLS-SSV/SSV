/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/04/07   GLS
2020/04/28   GLS
2020/05/08   GLS
2020/06/20   GLS
2020/06/28   GLS
2020/08/24   GLS
2021/06/18   GLS
2021/06/26   GLS
2021/06/28   GLS
2021/07/31   GLS
2021/08/14   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/27   GLS
2021/12/28   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/02/14   GLS
2022/03/24   GLS
2022/06/04   GLS
2022/06/06   GLS
2022/07/24   GLS
2022/08/05   GLS
2022/08/18   GLS
2022/10/28   GLS
2022/12/19   GLS
********************************************/
#include "SystemDisplays.h"
#include "IDP.h"
#include "..\vc\MDU.h"
#include <EngConst.h>


namespace dps
{
	SystemDisplays::SystemDisplays( SimpleGPCSystem* _gpc ):GeneralDisplays( _gpc, "SystemDisplays" )
	{
		engunit_hex = 0;
		for (int i = 0; i < 6; i++)
		{
			addidvalid[i] = false;
		}
		return;
	}

	SystemDisplays::~SystemDisplays()
	{
	}

	bool SystemDisplays::OnMajorModeChange( unsigned int newMajorMode )
	{
		// always running
		return true;
	}

	bool SystemDisplays::ItemInput( int spec, int item, const char* Data )
	{
		switch (spec)
		{
			case 0:
				return ItemInput_GPCMEMORY( item, Data );
			case 2:
				return ItemInput_SPEC2( item, Data );
		}
		return false;
	}

	bool SystemDisplays::ItemInput_GPCMEMORY( int item, const char* Data )
	{
		switch (item)
		{
			case 26:
				{
					int nNew;
					if (GetIntegerUnsigned( Data, nNew ))
					{
						if (((nNew >= 100) && (nNew <= 110)) || ((nNew >= 200) && (nNew <= 210)))
						{
							engunit_hex = nNew;
							for (int i = 0; i < 6; i++)
							{
								addidvalid[i] = false;
							}
						}
						else return false;
					}
					else return false;
				}
				break;
			case 27:
				engunit_hex = 0;
				for (int i = 0; i < 6; i++)
				{
					addidvalid[i] = false;
				}
				break;
			case 28:
			case 30:
			case 32:
			case 34:
			case 36:
			case 38:
				{
					unsigned int nNew;
					if (GetIntegerHex( Data, nNew ))
					{
						if (nNew < (SIMPLECOMPOOL_SIZE - ((engunit_hex >= 200) ? 1 : 0)))// limit to "last - 1" for 32b
						{
							addid[(item - 28) / 2] = nNew;
							addidvalid[(item - 28) / 2] = true;
						}
						else return false;
					}
					else return false;
				}
				break;
			default:
				return false;
		}
		return true;
	}

	bool SystemDisplays::ItemInput_SPEC2( int item, const char* Data )
	{
		switch (item)
		{
			case 23:
				{
					int nNew;
					if (GetIntegerUnsigned( Data, nNew ))
					{
						if (nNew <= 99)
						{
							WriteCOMPOOL_IS( SCP_SM_TONE_DURATION, nNew );
						}
						else return false;
					}
					else return false;
				}
				break;
			default:
				return false;
		}
		return true;
	}

	bool SystemDisplays::OnPaint( int spec, vc::MDU* pMDU ) const
	{
		switch (GetMajorMode() / 100)
		{
			case 0:
				switch (spec)
				{
					case 0:
						OnPaint_GPCMEMORY_PASS( pMDU );// GPC MEMORY
						return true;
					case 2:
						OnPaint_SPEC2_PASS( pMDU );// TIME
						return true;
					case 99:
						OnPaint_DISP99_PASS( pMDU );// FAULT
						return true;
					case dps::MODE_UNDEFINED:
						OnPaint_GPCMEMORY_PASS( pMDU );// GPC MEMORY
						return true;
					default:
						return false;
				}
			case 1:
				switch (spec)
				{
					case 0:
						OnPaint_GPCMEMORY_PASS( pMDU );// GPC MEMORY
						return true;
					case 99:
						OnPaint_DISP99_PASS( pMDU );// FAULT
						return true;
					default:
						return false;
				}
			case 2:
				switch (spec)
				{
					case 0:
						OnPaint_GPCMEMORY_PASS( pMDU );// GPC MEMORY
						return true;
					case 2:
						OnPaint_SPEC2_PASS( pMDU );// TIME
						return true;
					case 99:
						OnPaint_DISP99_PASS( pMDU );// FAULT
						return true;
					default:
						return false;
				}
			case 3:
				switch (spec)
				{
					case 0:
						OnPaint_GPCMEMORY_PASS( pMDU );// GPC MEMORY
						return true;
					case 99:
						OnPaint_DISP99_PASS( pMDU );// FAULT
						return true;
					default:
						return false;
				}
			case 6:
				switch (spec)
				{
					case 0:
						OnPaint_GPCMEMORY_PASS( pMDU );// GPC MEMORY
						return true;
					case 99:
						OnPaint_DISP99_PASS( pMDU );// FAULT
						return true;
					default:
						return false;
				}
			case 8:
				switch (spec)
				{
					case 0:
						OnPaint_GPCMEMORY_PASS( pMDU );// GPC MEMORY
						return true;
					case 2:
						OnPaint_SPEC2_PASS( pMDU );// TIME
						return true;
					case 99:
						OnPaint_DISP99_PASS( pMDU );// FAULT
						return true;
					default:
						return false;
				}
			case 9:
				switch (spec)
				{
					case 0:
						OnPaint_GPCMEMORY_PASS( pMDU );// GPC MEMORY
						return true;
					case 2:
						OnPaint_SPEC2_PASS( pMDU );// TIME
						return true;
					case 99:
						OnPaint_DISP99_PASS( pMDU );// FAULT
						return true;
					case dps::MODE_UNDEFINED:
						OnPaint_GPCMEMORY_PASS( pMDU );// GPC MEMORY
						return true;
					default:
						return false;
				}
			default:
				return false;
		}
		return false;
	}

	void SystemDisplays::OnPaint_GPCMEMORY_PASS( vc::MDU* pMDU ) const
	{
		PrintCommonHeader( "  GPC MEMORY", pMDU );

		// static parts (labels)
		pMDU->mvprint( 0, 2, "MEM/BUS CONFIG" );
		pMDU->mvprint( 0, 3, "1 CONFIG" );
		pMDU->mvprint( 11, 3, "(" );
		pMDU->mvprint( 14, 3, ")" );
		pMDU->mvprint( 0, 4, "2 GPC" );
		pMDU->mvprint( 1, 6, "STRING 1  7" );
		pMDU->mvprint( 8, 7, "2  8" );
		pMDU->mvprint( 8, 8, "3  9" );
		pMDU->mvprint( 8, 9, "4 10" );
		pMDU->mvprint( 3, 10, "PL 1/2 11" );
		pMDU->mvprint( 4, 12, "CRT 1 12" );
		pMDU->mvprint( 8, 13, "2 13" );
		pMDU->mvprint( 8, 14, "3 14" );
		pMDU->mvprint( 8, 15, "4 15" );
		pMDU->mvprint( 1, 17, "LAUNCH 1 16" );
		pMDU->mvprint( 8, 18, "2 17" );
		pMDU->mvprint( 5, 19, "MM 1 18" );
		pMDU->mvprint( 8, 20, "2 19" );
		pMDU->Underline( 9, 3 );
		pMDU->Underline( 10, 3 );
		pMDU->Underline( 6, 4 );
		pMDU->Underline( 8, 4 );
		pMDU->Underline( 10, 4 );
		pMDU->Underline( 12, 4 );
		pMDU->Underline( 14, 4 );
		pMDU->Underline( 13, 6 );
		pMDU->Underline( 13, 7 );
		pMDU->Underline( 13, 8 );
		pMDU->Underline( 13, 9 );
		pMDU->Underline( 13, 10 );
		pMDU->Underline( 13, 12 );
		pMDU->Underline( 13, 13 );
		pMDU->Underline( 13, 14 );
		pMDU->Underline( 13, 15 );
		pMDU->Underline( 13, 17 );
		pMDU->Underline( 13, 18 );
		pMDU->Underline( 13, 19 );
		pMDU->Underline( 13, 20 );

		pMDU->mvprint( 17, 2, "READ/WRITE" );
		pMDU->mvprint( 18, 3, "DATA 20" );
		pMDU->mvprint( 18, 4, "CODE 21" );
		pMDU->mvprint( 28, 3, "BIT SET 22" );
		pMDU->mvprint( 28, 4, "BIT RST 23" );
		pMDU->mvprint( 41, 3, "SEQ ID 24" );
		pMDU->mvprint( 41, 4, "WRITE  25" );
		pMDU->mvprint( 18, 5, "26 ENG UNITS" );
		pMDU->mvprint( 38, 5, "HEX 27" );
		pMDU->mvprint( 18, 6, "ADD ID   DESIRED   ACTUAL" );
		pMDU->mvprint( 17, 7, "28" );
		pMDU->mvprint( 27, 7, "29" );
		pMDU->mvprint( 17, 8, "30" );
		pMDU->mvprint( 27, 8, "31" );
		pMDU->mvprint( 17, 9, "32" );
		pMDU->mvprint( 27, 9, "33" );
		pMDU->mvprint( 17, 10, "34" );
		pMDU->mvprint( 27, 10, "35" );
		pMDU->mvprint( 17, 11, "36" );
		pMDU->mvprint( 27, 11, "37" );
		pMDU->mvprint( 17, 12, "38" );
		pMDU->mvprint( 27, 12, "39" );
		pMDU->Underline( 31, 5 );
		pMDU->Underline( 32, 5 );
		pMDU->Underline( 33, 5 );
		pMDU->Underline( 20, 7 );
		pMDU->Underline( 21, 7 );
		pMDU->Underline( 22, 7 );
		pMDU->Underline( 23, 7 );
		pMDU->Underline( 24, 7 );
		pMDU->Underline( 30, 7 );
		pMDU->Underline( 31, 7 );
		pMDU->Underline( 32, 7 );
		pMDU->Underline( 33, 7 );

		pMDU->mvprint( 17, 14, "MEMORY DUMP" );
		pMDU->mvprint( 38, 14, "STORE   MC=" );
		pMDU->mvprint( 18, 15, "40 START ID" );
		pMDU->mvprint( 18, 16, "41 NO WORDS" );
		pMDU->mvprint( 18, 17, "42 EDS/FRAME" );
		pMDU->mvprint( 18, 18, "DUMP START/STOP 43" );
		pMDU->mvprint( 39, 15, "45 CONFIG" );
		pMDU->mvprint( 39, 16, "46 GPC" );
		pMDU->mvprint( 39, 17, "STORE 47" );
		pMDU->Underline( 31, 15 );
		pMDU->Underline( 32, 15 );
		pMDU->Underline( 33, 15 );
		pMDU->Underline( 34, 15 );
		pMDU->Underline( 35, 15 );
		pMDU->Underline( 49, 15 );
		pMDU->Underline( 50, 15 );
		pMDU->Underline( 31, 16 );
		pMDU->Underline( 32, 16 );
		pMDU->Underline( 33, 16 );
		pMDU->Underline( 34, 16 );
		pMDU->Underline( 35, 16 );
		pMDU->Underline( 36, 16 );
		pMDU->Underline( 46, 16 );
		pMDU->Underline( 31, 17 );
		pMDU->Underline( 32, 17 );
		pMDU->Underline( 33, 17 );

		pMDU->mvprint( 0, 22, "OPS 3 UPLK 50" );
		pMDU->mvprint( 0, 23, "OPS 3 INIT 51" );
		pMDU->mvprint( 18, 20, "44 DOWNLIST GPC" );
		pMDU->mvprint( 20, 21, "OPS 0 ENA 49" );
		pMDU->mvprint( 17, 23, "ERR LOG RESET 48" );
		pMDU->mvprint( 39, 20, "MM AREA" );
		pMDU->mvprint( 40, 21, "PL  52" );
		pMDU->mvprint( 40, 22, "GNC 53" );
		pMDU->mvprint( 40, 23, "SM  54" );
		pMDU->Underline( 34, 20 );
		pMDU->Underline( 47, 21 );
		pMDU->Underline( 47, 22 );
		pMDU->Underline( 47, 23 );

		// static parts (lines)
		pMDU->Line( 90, 84, 90, 294 );
		pMDU->Line( 160, 28, 160, 294 );
		pMDU->Line( 160, 196, 500, 196 );
		pMDU->Line( 160, 280, 500, 280 );
		pMDU->Line( 10, 294, 160, 294 );

		// dynamic parts
		unsigned short mc = ReadCOMPOOL_IS( SCP_MC );
		if (mc == 1) pMDU->mvprint( 29, 2, "GNC" );
		else if (mc == 2) pMDU->mvprint( 29, 2, "SM" );
		else pMDU->mvprint( 29, 2, "000" );

		if (engunit_hex == 0) pMDU->mvprint( 44, 5, "*" );
		else
		{
			char cbuf[4];
			sprintf_s( cbuf, 4, "%d", engunit_hex );
			pMDU->mvprint( 31, 5, cbuf );
		}

		for (int i = 0; i < 6; i++)
		{
			if (!addidvalid[i]) continue;

			char cbuf[16];
			sprintf_s( cbuf, 16, "%05X", addid[i] );
			pMDU->mvprint( 20, 7 + i, cbuf );

			if (engunit_hex == 0)
			{
				sprintf_s( cbuf, 16, "%04X", ReadCOMPOOL_IS( addid[i] ) );
				pMDU->mvprint( 45, 7 + i, cbuf );
			}
			else if (engunit_hex < 200)
			{
				// 16b
				short tmp = ReadCOMPOOL_IS( addid[i] );
				double conv = GetConversionParameter( engunit_hex - 100 );
				tmp = static_cast<short>(tmp * conv);
				if (tmp > 0) pMDU->mvprint( 37, 7 + i, "+" );
				else if (tmp < 0) pMDU->mvprint( 37, 7 + i, "-" );
				sprintf_s( cbuf, 16, "%11d", abs( tmp ) );
				pMDU->mvprint( 38, 7 + i, cbuf );
			}
			else
			{
				// 32b float
				float tmp = ReadCOMPOOL_SS( addid[i] );
				double conv = GetConversionParameter( engunit_hex - 200 );
				tmp = static_cast<float>(tmp * conv);
				if (fabs( tmp ) >= 100000.0) tmp = static_cast<float>(tmp - (sign( tmp ) * 100000.0));
				if (tmp > 0.0) pMDU->mvprint( 37, 7 + i, "+" );
				else if (tmp < 0.0) pMDU->mvprint( 37, 7 + i, "-" );
				sprintf_s( cbuf, 16, "%#11.5f", fabs( tmp ) );
				pMDU->mvprint( 38, 7 + i, cbuf );
			}
		}
		return;
	}
	
	void SystemDisplays::OnPaint_SPEC2_PASS( vc::MDU* pMDU ) const
	{
		PrintCommonHeader( "  TIME", pMDU );

		// static parts (labels)
		pMDU->mvprint( 1, 2, "MISSION TIME" );
		pMDU->mvprint( 3, 3, "MET 1" );
		pMDU->mvprint( 3, 4, "GMT 2" );

		pMDU->mvprint( 1, 5, "CRT TIMER" );
		pMDU->mvprint( 3, 6, "9 SET" );
		pMDU->Underline( 10, 6 );
		pMDU->Underline( 11, 6 );
		pMDU->mvprint( 12, 6, ":" );
		pMDU->Underline( 13, 6 );
		pMDU->Underline( 14, 6 );
		pMDU->mvprint( 15, 6, ":" );
		pMDU->Underline( 16, 6 );
		pMDU->Underline( 17, 6 );
		pMDU->mvprint( 3, 7, "START 12   STOP 13" );
		pMDU->mvprint( 3, 8, "14 START AT" );
		pMDU->Underline( 15, 8 );
		pMDU->Underline( 16, 8 );
		pMDU->mvprint( 17, 8, ":" );
		pMDU->Underline( 18, 8 );
		pMDU->Underline( 19, 8 );
		pMDU->mvprint( 20, 8, ":" );
		pMDU->Underline( 21, 8 );
		pMDU->Underline( 22, 8 );
		pMDU->mvprint( 24, 8, "MSN T" );
		pMDU->mvprint( 3, 9, "17 COUNT TO" );
		pMDU->Underline( 15, 9 );
		pMDU->Underline( 16, 9 );
		pMDU->mvprint( 17, 9, ":" );
		pMDU->Underline( 18, 9 );
		pMDU->Underline( 19, 9 );
		pMDU->mvprint( 20, 9, ":" );
		pMDU->Underline( 21, 9 );
		pMDU->Underline( 22, 9 );
		pMDU->mvprint( 24, 9, "MSN T" );

		pMDU->mvprint( 30, 2, "TONE" );
		pMDU->mvprint( 32, 3, "3" );
		pMDU->Underline( 35, 3 );
		pMDU->Underline( 36, 3 );
		pMDU->mvprint( 37, 3, ":" );
		pMDU->Underline( 38, 3 );
		pMDU->Underline( 39, 3 );
		pMDU->mvprint( 40, 3, ":" );
		pMDU->Underline( 41, 3 );
		pMDU->Underline( 42, 3 );
		pMDU->mvprint( 44, 3, "MSN T" );
		pMDU->mvprint( 32, 4, "6" );
		pMDU->mvprint( 37, 4, ":" );
		pMDU->mvprint( 40, 4, ":" );
		pMDU->mvprint( 31, 6, "20" );
		pMDU->Underline( 35, 6 );
		pMDU->Underline( 36, 6 );
		pMDU->mvprint( 37, 6, ":" );
		pMDU->Underline( 38, 6 );
		pMDU->Underline( 39, 6 );
		pMDU->mvprint( 40, 6, ":" );
		pMDU->Underline( 41, 6 );
		pMDU->Underline( 42, 6 );
		pMDU->mvprint( 44, 6, "CRT T" );
		pMDU->mvprint( 31, 8, "23 DURATION" );
		pMDU->Underline( 44, 8 );
		pMDU->Underline( 45, 8 );

		pMDU->mvprint( 1, 11, "MTU" );
		pMDU->mvprint( 3, 12, "24 GMT" );
		pMDU->Delta( 10, 12 );
		pMDU->Underline( 13, 12 );
		pMDU->Underline( 14, 12 );
		pMDU->Underline( 15, 12 );
		pMDU->mvprint( 16, 12, "/" );
		pMDU->Underline( 17, 12 );
		pMDU->Underline( 18, 12 );
		pMDU->mvprint( 19, 12, ":" );
		pMDU->Underline( 20, 12 );
		pMDU->Underline( 21, 12 );
		pMDU->mvprint( 22, 12, ":" );
		pMDU->Underline( 23, 12 );
		pMDU->Underline( 24, 12 );
		pMDU->Underline( 25, 12 );
		pMDU->Underline( 26, 12 );
		pMDU->Underline( 27, 12 );
		pMDU->mvprint( 3, 13, "28 MET" );
		pMDU->Delta( 10, 13 );
		pMDU->mvprint( 16, 13, "/" );
		pMDU->mvprint( 19, 13, ":" );
		pMDU->mvprint( 22, 13, ":" );
		pMDU->mvprint( 6, 14, "UPDATE 32" );
		pMDU->mvprint( 34, 14, "MET RESET 33" );

		pMDU->mvprint( 1, 16, "GPC TIME" );
		pMDU->mvprint( 3, 18, "MTU ACCUM 1" );
		pMDU->mvprint( 13, 19, "2" );
		pMDU->mvprint( 13, 20, "3" );
		pMDU->mvprint( 11, 21, "GPC" );

		pMDU->mvprint( 22, 17, "GMT" );
		pMDU->mvprint( 18, 18, "/" );
		pMDU->mvprint( 21, 18, ":" );
		pMDU->mvprint( 24, 18, ":" );
		pMDU->mvprint( 18, 19, "/" );
		pMDU->mvprint( 21, 19, ":" );
		pMDU->mvprint( 24, 19, ":" );
		pMDU->mvprint( 18, 20, "/" );
		pMDU->mvprint( 21, 20, ":" );
		pMDU->mvprint( 24, 20, ":" );
		pMDU->mvprint( 18, 21, "/" );
		pMDU->mvprint( 21, 21, ":" );
		pMDU->mvprint( 24, 21, ":" );

		pMDU->mvprint( 37, 17, "TRY" );
		pMDU->mvprint( 37, 18, "34" );
		pMDU->mvprint( 37, 19, "35" );
		pMDU->mvprint( 37, 20, "36" );
		pMDU->mvprint( 37, 21, "37" );

		pMDU->mvprint( 44, 16, "GPC" );
		pMDU->mvprint( 43, 17, "1" );
		pMDU->mvprint( 43, 18, "2" );
		pMDU->mvprint( 43, 19, "3" );
		pMDU->mvprint( 43, 20, "4" );
		pMDU->mvprint( 43, 21, "5" );

		pMDU->mvprint( 3, 23, "TIME SYNC 38" );

		// static parts (lines)
		pMDU->Line( 9, 147, 490, 147 );
		pMDU->Line( 9, 217, 490, 217 );

		pMDU->Line( 145, 252, 145, 315 );
		pMDU->Line( 365, 238, 365, 315 );
		pMDU->Line( 405, 238, 405, 315 );

		// dynamic parts
		char cbuf[64];
		unsigned int duration = ReadCOMPOOL_IS( SCP_SM_TONE_DURATION );
		sprintf_s( cbuf, 64, "%02hu", duration );
		pMDU->mvprint( 44, 8, cbuf );
		return;
	}

	void SystemDisplays::OnPaint_DISP99_PASS( vc::MDU* pMDU ) const
	{
		PrintCommonHeader( "    FAULT", pMDU );

		// static parts (labels)
		pMDU->mvprint( 4, 5, "CRT" );
		pMDU->mvprint( 13, 5, "FAULT      C/W   GPC      TIME" );
		pMDU->mvprint( 4, 6, "ID" );

		char msg[64];
		unsigned short j = ReadCOMPOOL_IS( SCP_FAULT_DISPBUF_CNT );
		for (unsigned int i = 1; i <= j; i++)
		{
			memset( msg, 0, 64 );
			ReadCOMPOOL_AC( SCP_FAULT_DISPBUF, i, msg, 15, 43 );
			pMDU->mvprint( 4, 8 + i, msg );
		}
		return;
	}

	double SystemDisplays::GetConversionParameter( unsigned char engunit ) const
	{
		switch (engunit)
		{
			case 1:// NM from FT
				return FT2NM;
			case 2:// NM from KFT
				return FT2NM * 1000.0;
			case 3:// FT from NM
				return 1.0 / FT2NM;
			case 4:// KFT from NM
				return 1.0 / (FT2NM * 1000.0);
			case 5:// FT/SEC2 from Gs
				return G2FPS2;
			case 6:// DEG/SEC from MR/SEC
				return DEG * 0.001;
			case 7:// DEG from ARC SEC
				return 1.0 / 3600.0;
			case 8:// FT/SEC2 from micro Gs
				return G2FPS2 * 0.000001;
			case 9:// DEG from Radians
				return DEG;
			case 10:// KFT from FT
				return 0.001;
			default:
				return 1.0;
		}
	}
};

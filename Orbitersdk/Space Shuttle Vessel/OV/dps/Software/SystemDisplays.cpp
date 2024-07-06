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
2022/12/23   GLS
2024/07/06   GLS
********************************************/
#include "SystemDisplays.h"
#include "CRT_Interface.h"
#include <MathSSV.h>
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

	void SystemDisplays::Paint( CRT_Interface* crt, unsigned short page ) const
	{
		switch (page)
		{
			case 0:// GPC MEMORY
				OnPaint_GPCMEMORY( crt );
				break;
			case 2:// TIME
				OnPaint_SPEC2( crt );
				break;
			case 6:// GPC/BUS STATUS
				OnPaint_DISP6( crt );
				break;
			case 99:// FAULT
				OnPaint_DISP99( crt );
				break;
		}
		return;
	}

	void SystemDisplays::PaintBackground( CRT_Interface* crt, unsigned short page ) const
	{
		switch (page)
		{
			case 0:// GPC MEMORY
				BackgroundData_GPCMEMORY( crt );
				break;
			case 2:// TIME
				BackgroundData_SPEC2( crt );
				break;
			case 6:// GPC/BUS STATUS
				BackgroundData_DISP6( crt );
				break;
			case 99:// FAULT
				BackgroundData_DISP99( crt );
				break;
		}
		return;
	}

	void SystemDisplays::OnPaint_GPCMEMORY( CRT_Interface* crt ) const
	{
		unsigned short mc = ReadCOMPOOL_IS( SCP_MC );
		if (mc == 1) crt->TextGrid( 30, 3, "GNC" );
		else if (mc == 2) crt->TextGrid( 30, 3, "SM" );
		else crt->TextGrid( 30, 3, "000" );

		if (engunit_hex == 0) crt->TextGrid( 45, 6, "*" );
		else
		{
			char cbuf[4];
			sprintf_s( cbuf, 4, "%d", engunit_hex );
			crt->TextGrid( 32, 6, cbuf );
		}

		for (int i = 0; i < 6; i++)
		{
			if (!addidvalid[i]) continue;

			char cbuf[16];
			sprintf_s( cbuf, 16, "%05X", addid[i] );
			crt->TextGrid( 21, 8 + i, cbuf );

			if (engunit_hex == 0)
			{
				sprintf_s( cbuf, 16, "%04X", ReadCOMPOOL_IS( addid[i] ) );
				crt->TextGrid( 46, 8 + i, cbuf );
			}
			else if (engunit_hex < 200)
			{
				// 16b
				short tmp = ReadCOMPOOL_IS( addid[i] );
				double conv = GetConversionParameter( engunit_hex - 100 );
				tmp = static_cast<short>(tmp * conv);
				if (tmp > 0) crt->TextGrid( 38, 8 + i, "+" );
				else if (tmp < 0) crt->TextGrid( 38, 8 + i, "-" );
				sprintf_s( cbuf, 16, "%11d", abs( tmp ) );
				crt->TextGrid( 39, 8 + i, cbuf );
			}
			else
			{
				// 32b float
				float tmp = ReadCOMPOOL_SS( addid[i] );
				double conv = GetConversionParameter( engunit_hex - 200 );
				tmp = static_cast<float>(tmp * conv);
				if (fabs( tmp ) >= 100000.0) tmp = static_cast<float>(tmp - (sign( tmp ) * 100000.0));
				if (tmp > 0.0) crt->TextGrid( 38, 8 + i, "+" );
				else if (tmp < 0.0) crt->TextGrid( 38, 8 + i, "-" );
				sprintf_s( cbuf, 16, "%#11.5f", fabs( tmp ) );
				crt->TextGrid( 39, 8 + i, cbuf );
			}
		}
		return;
	}
	
	void SystemDisplays::OnPaint_SPEC2( CRT_Interface* crt ) const
	{
		char cbuf[64];
		unsigned int duration = ReadCOMPOOL_IS( SCP_SM_TONE_DURATION );
		sprintf_s( cbuf, 64, "%02hu", duration );
		crt->TextGrid( 45, 9, cbuf );
		return;
	}

	void SystemDisplays::OnPaint_DISP6( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void SystemDisplays::OnPaint_DISP99( CRT_Interface* crt ) const
	{
		char msg[64];
		unsigned short j = ReadCOMPOOL_IS( SCP_FAULT_DISPBUF_CNT );
		for (unsigned int i = 1; i <= j; i++)
		{
			memset( msg, 0, 64 );
			ReadCOMPOOL_AC( SCP_FAULT_DISPBUF, i, msg, 15, 43 );
			crt->TextGrid( 5, 9 + i, msg );
		}
		return;
	}

	void SystemDisplays::BackgroundData_GPCMEMORY( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 18, 1, "GPC MEMORY" );

		// labels
		crt->TextGrid( 1, 3, "MEM/BUS CONFIG" );
		crt->TextGrid( 1, 4, "1 CONFIG \x7D\x7D(" );
		crt->TextGrid( 15, 4, ")" );
		crt->TextGrid( 1, 5, "2 GPC" );
		crt->TextGrid( 7, 5, "\x7D \x7D \x7D \x7D \x7D" );
		crt->TextGrid( 2, 7, "STRING 1" );
		crt->TextGrid( 12, 7, "7 \x7D" );
		crt->TextGrid( 9, 8, "2  8 \x7D" );
		crt->TextGrid( 9, 9, "3  9 \x7D" );
		crt->TextGrid( 9, 10, "4 10 \x7D" );
		crt->TextGrid( 4, 11, "PL 1/2" );
		crt->TextGrid( 11, 11, "11 \x7D" );
		crt->TextGrid( 5, 13, "CRT 1 12 \x7D" );
		crt->TextGrid( 9, 14, "2 13 \x7D" );
		crt->TextGrid( 9, 15, "3 14 \x7D" );
		crt->TextGrid( 9, 16, "4 15 \x7D" );
		crt->TextGrid( 2, 18, "LAUNCH 1" );
		crt->TextGrid( 11, 18, "16 \x7D" );
		crt->TextGrid( 9, 19, "2 17 \x7D" );
		crt->TextGrid( 6, 20, "MM" );
		crt->TextGrid( 9, 20, "1 18 \x7D" );
		crt->TextGrid( 9, 21, "2 19 \x7D" );

		crt->TextGrid( 18, 3, "READ/WRITE" );
		crt->TextGrid( 19, 4, "DATA" );
		crt->TextGrid( 24, 4, "20" );
		crt->TextGrid( 19, 5, "CODE" );
		crt->TextGrid( 24, 5, "21" );
		crt->TextGrid( 29, 4, "BIT SET 22" );
		crt->TextGrid( 29, 5, "BIT RST 23" );
		crt->TextGrid( 42, 4, "SEQ ID" );
		crt->TextGrid( 49, 4, "24" );
		crt->TextGrid( 42, 5, "WRITE" );
		crt->TextGrid( 49, 5, "25" );
		crt->TextGrid( 19, 6, "26 ENG UNITS" );
		crt->TextGrid( 32, 6, "\x7D\x7D\x7D" );
		crt->TextGrid( 39, 6, "HEX 27" );
		crt->TextGrid( 19, 7, "ADD ID" );
		crt->TextGrid( 28, 7, "DESIRED" );
		crt->TextGrid( 38, 7, "ACTUAL" );
		crt->TextGrid( 18, 8, "28" );
		crt->TextGrid( 21, 8, "\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 28, 8, "29" );
		crt->TextGrid( 31, 8, "\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 18, 9, "30" );
		crt->TextGrid( 28, 9, "31" );
		crt->TextGrid( 18, 10, "32" );
		crt->TextGrid( 28, 10, "33" );
		crt->TextGrid( 18, 11, "34" );
		crt->TextGrid( 28, 11, "35" );
		crt->TextGrid( 18, 12, "36" );
		crt->TextGrid( 28, 12, "37" );
		crt->TextGrid( 18, 13, "38" );
		crt->TextGrid( 28, 13, "39" );

		crt->TextGrid( 18, 15, "MEMORY" );
		crt->TextGrid( 25, 15, "DUMP" );
		crt->TextGrid( 19, 16, "40" );
		crt->TextGrid( 22, 16, "START ID" );
		crt->TextGrid( 32, 16, "\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 19, 17, "41" );
		crt->TextGrid( 22, 17, "NO WORDS" );
		crt->TextGrid( 32, 17, "\x7D\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 19, 18, "42 WDS/FRAME" );
		crt->TextGrid( 32, 18, "\x7D\x7D\x7D" );
		crt->TextGrid( 19, 19, "DUMP" );
		crt->TextGrid( 24, 19, "START/STOP" );
		crt->TextGrid( 35, 19, "43" );

		crt->TextGrid( 39, 15, "STORE" );
		crt->TextGrid( 47, 15, "MC=" );
		crt->TextGrid( 40, 16, "45" );
		crt->TextGrid( 43, 16, "CONFIG" );
		crt->TextGrid( 50, 16, "\x7D\x7D" );
		crt->TextGrid( 40, 17, "46 GPC \x7D" );
		crt->TextGrid( 40, 18, "STORE 47" );

		crt->TextGrid( 1, 23, "OPS 3" );
		crt->TextGrid( 7, 23, "UPLK" );
		crt->TextGrid( 12, 23, "50" );
		crt->TextGrid( 1, 24, "OPS 3" );
		crt->TextGrid( 7, 24, "INIT" );
		crt->TextGrid( 12, 24, "51" );

		crt->TextGrid( 19, 21, "44" );
		crt->TextGrid( 22, 21, "DOWNLIST GPC \x7D" );
		crt->TextGrid( 21, 22, "OPS 0 ENA 49" );
		crt->TextGrid( 18, 24, "ERR LOG RESET 48" );

		crt->TextGrid( 39, 21, "MM" );
		crt->TextGrid( 42, 21, "AREA" );
		crt->TextGrid( 40, 22, "PL" );
		crt->TextGrid( 44, 22, "52 \x7D" );
		crt->TextGrid( 40, 23, "GNC 53 \x7D" );
		crt->TextGrid( 40, 24, "SM" );
		crt->TextGrid( 44, 24, "54 \x7D" );

		// lines
		crt->Line( 209, 176, 209, 581 );
		crt->Line( 323, 68, 323, 662 );
		crt->Line( 741, 379, 741, 662 );

		crt->Line( 323, 379, 978, 379 );
		crt->Line( 323, 541, 978, 541 );
		crt->Line( 38, 581, 323, 581 );
		return;
	}
	
	void SystemDisplays::BackgroundData_SPEC2( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 22, 1, "TIME" );

		// labels
		crt->TextGrid( 2, 3, "MISSION TIME" );
		crt->TextGrid( 4, 4, "MET 1" );
		crt->TextGrid( 4, 5, "GMT 2" );

		crt->TextGrid( 2, 6, "CRT TIMER" );
		crt->TextGrid( 4, 7, "9 SET" );
		crt->TextGrid( 10, 7, "\x01" );
		crt->TextGrid( 10, 7, "\x02" );
		crt->TextGrid( 11, 7, "\x7D\x7D:\x7D\x7D:\x7D\x7D" );
		crt->TextGrid( 4, 8, "START 12" );
		crt->TextGrid( 15, 8, "STOP" );
		crt->TextGrid( 20, 8, "13" );
		crt->TextGrid( 4, 9, "14" );
		crt->TextGrid( 7, 9, "START AT" );
		crt->TextGrid( 16, 9, "\x7D\x7D:\x7D\x7D:\x7D\x7D" );
		crt->TextGrid( 25, 9, "MSN T" );
		crt->TextGrid( 4, 10, "17" );
		crt->TextGrid( 7, 10, "COUNT TO" );
		crt->TextGrid( 18, 10, ":" );
		crt->TextGrid( 21, 10, ":" );
		crt->TextGrid( 25, 10, "MSN T" );

		crt->TextGrid( 31, 3, "TONE" );
		crt->TextGrid( 33, 4, "3" );
		crt->TextGrid( 36, 4, "\x7D\x7D:\x7D\x7D:\x7D\x7D MSN T" );
		crt->TextGrid( 33, 5, "6" );
		crt->TextGrid( 38, 5, ":" );
		crt->TextGrid( 41, 5, ":" );
		crt->TextGrid( 32, 7, "20" );
		crt->TextGrid( 35, 7, "\x01" );
		crt->TextGrid( 35, 7, "\x02" );
		crt->TextGrid( 36, 7, "\x7D\x7D:\x7D\x7D:\x7D\x7D" );
		crt->TextGrid( 45, 7, "CRT T" );
		crt->TextGrid( 32, 9, "23" );
		crt->TextGrid( 35, 9, "DURATION" );
		crt->TextGrid( 45, 9, "\x7D\x7D" );

		crt->TextGrid( 2, 12, "MTU" );
		crt->TextGrid( 4, 13, "24 GMT \x7F" );
		crt->TextGrid( 13, 13, "\x01" );
		crt->TextGrid( 13, 13, "\x02" );
		crt->TextGrid( 14, 13, "\x7D\x7D\x7D/\x7D\x7D:\x7D\x7D:\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 26, 13, "." );
		crt->TextGrid( 4, 14, "28 MET \x7F" );
		crt->TextGrid( 13, 14, "\x01" );
		crt->TextGrid( 13, 14, "\x02" );
		crt->TextGrid( 17, 14, "/" );
		crt->TextGrid( 20, 14, ":" );
		crt->TextGrid( 23, 14, ":" );
		crt->TextGrid( 26, 14, "." );
		crt->TextGrid( 7, 15, "UPDATE" );
		crt->TextGrid( 14, 15, "32" );
		crt->TextGrid( 35, 15, "MET RESET 33" );

		crt->TextGrid( 2, 17, "GPC TIME" );
		crt->TextGrid( 4, 19, "MTU ACCUM 1" );
		crt->TextGrid( 14, 20, "2" );
		crt->TextGrid( 14, 21, "3" );
		crt->TextGrid( 12, 22, "GPC" );

		crt->TextGrid( 23, 18, "GMT" );
		crt->TextGrid( 19, 19, "/" );
		crt->TextGrid( 22, 19, ":" );
		crt->TextGrid( 25, 19, ":" );
		crt->TextGrid( 19, 20, "/" );
		crt->TextGrid( 22, 20, ":" );
		crt->TextGrid( 25, 20, ":" );
		crt->TextGrid( 19, 21, "/" );
		crt->TextGrid( 22, 21, ":" );
		crt->TextGrid( 25, 21, ":" );
		crt->TextGrid( 19, 22, "/" );
		crt->TextGrid( 22, 22, ":" );
		crt->TextGrid( 25, 22, ":" );

		crt->TextGrid( 38, 18, "TRY" );
		crt->TextGrid( 38, 19, "34" );
		crt->TextGrid( 38, 20, "35" );
		crt->TextGrid( 38, 21, "36" );
		crt->TextGrid( 38, 22, "37" );

		crt->TextGrid( 45, 17, "GPC" );
		crt->TextGrid( 44, 18, "1" );
		crt->TextGrid( 44, 19, "2" );
		crt->TextGrid( 44, 20, "3" );
		crt->TextGrid( 44, 21, "4" );
		crt->TextGrid( 44, 22, "5" );

		crt->TextGrid( 4, 24, "TIME" );
		crt->TextGrid( 9, 24, "SYNC" );
		crt->TextGrid( 14, 24, "38" );

		// lines
		crt->Line( 38, 298, 969, 298 );
		crt->Line( 38, 433, 969, 433 );

		crt->Line( 304, 500, 304, 608 );
		crt->Line( 722, 473, 722, 608 );
		crt->Line( 798, 473, 798, 608 );
		return;
	}

	void SystemDisplays::BackgroundData_DISP6( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 18, 1, "GPC/BUS STATUS" );

		// labels
		crt->TextGrid( 9, 3, "GPC" );
		crt->TextGrid( 14, 3, "1" );
		crt->TextGrid( 20, 3, "2" );
		crt->TextGrid( 26, 3, "3" );
		crt->TextGrid( 32, 3, "4" );
		crt->TextGrid( 38, 3, "5" );
		crt->TextGrid( 8, 4, "MODE" );
		crt->TextGrid( 9, 5, "OPS" );

		crt->TextGrid( 1, 6, "STRING 1" );
		crt->TextGrid( 10, 6, "FF" );
		crt->TextGrid( 10, 7, "FA" );
		crt->TextGrid( 8, 8, "2 FF" );
		crt->TextGrid( 10, 9, "FA" );
		crt->TextGrid( 8, 10, "3 FF" );
		crt->TextGrid( 10, 11, "FA" );
		crt->TextGrid( 8, 12, "4 FF" );
		crt->TextGrid( 10, 13, "FA" );

		crt->TextGrid( 8, 15, "PL 1" );
		crt->TextGrid( 11, 16, "2" );
		crt->TextGrid( 4, 17, "LAUNCH 1" );
		crt->TextGrid( 11, 18, "2" );
		crt->TextGrid( 7, 19, "CRT 1" );
		crt->TextGrid( 11, 20, "2" );
		crt->TextGrid( 11, 21, "3" );
		crt->TextGrid( 11, 22, "4" );

		// lines
		crt->Line( 38, 95, 817, 95 );
		crt->Line( 38, 149, 817, 149 );

		crt->Line( 247, 68, 247, 608 );
		crt->Line( 361, 68, 361, 608 );
		crt->Line( 475, 68, 475, 608 );
		crt->Line( 589, 68, 589, 608 );
		crt->Line( 703, 68, 703, 608 );
		crt->Line( 817, 68, 817, 608 );
		return;
	}

	void SystemDisplays::BackgroundData_DISP99( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 20, 1, "FAULT" );

		// labels
		crt->TextGrid( 5, 6, "CRT" );
		crt->TextGrid( 5, 7, "ID" );
		crt->TextGrid( 14, 6, "FAULT" );
		crt->TextGrid( 25, 6, "C/W" );
		crt->TextGrid( 31, 6, "GPC" );
		crt->TextGrid( 40, 6, "TIME" );
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

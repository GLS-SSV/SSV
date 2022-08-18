/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2020/08/30   GLS
2020/09/07   GLS
2021/06/06   GLS
2021/08/24   GLS
2022/08/05   GLS
********************************************/
#include "MDU.h"
#include "../Atlantis.h"
#include "../dps/IDP.h"


namespace vc
{
	void MDU::SystemStatusDisplay_CSTMenu( HDC hDC )
	{
		char cbuf[8];

		SelectObject( hDC, gdiSSVAFont_h10w10bold );
		SetTextColor( hDC, CR_WHITE );
		SelectObject( hDC, gdiWhitePen );

		// ADC1A
		if (0)
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 17, 2, 81, 66 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 27, 28, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 18, 49, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 23, 49, "EDUMP", 5 );
			else if (0) TextOut( hDC, 23, 49, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				TextOut( hDC, 18, 49, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 17, 2, 81, 66 );
		}
		MoveToEx( hDC, 17, 23, NULL );
		LineTo( hDC, 80, 23 );
		MoveToEx( hDC, 17, 44, NULL );
		LineTo( hDC, 80, 44 );
		TextOut( hDC, 23, 7, "ADC1A", 5 );

		// ADC1B
		if (0)
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 86, 2, 150, 66 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 96, 28, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 87, 49, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 92, 49, "EDUMP", 5 );
			else if (0) TextOut( hDC, 92, 49, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				TextOut( hDC, 87, 49, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 86, 2, 150, 66 );
		}
		MoveToEx( hDC, 86, 23, NULL );
		LineTo( hDC, 149, 23 );
		MoveToEx( hDC, 86, 44, NULL );
		LineTo( hDC, 149, 44 );
		TextOut( hDC, 92, 7, "ADC1B", 5 );

		// ADC2A
		if (0)
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 362, 2, 426, 66 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 372, 28, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 363, 49, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 368, 49, "EDUMP", 5 );
			else if (0) TextOut( hDC, 368, 49, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				TextOut( hDC, 363, 49, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 362, 2, 426, 66 );
		}
		MoveToEx( hDC, 362, 23, NULL );
		LineTo( hDC, 425, 23 );
		MoveToEx( hDC, 362, 44, NULL );
		LineTo( hDC, 425, 44 );
		TextOut( hDC, 368, 7, "ADC2A", 5 );

		// ADC2B
		if (0)
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 431, 2, 495, 66 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 441, 28, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 432, 49, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 437, 49, "EDUMP", 5 );
			else if (0) TextOut( hDC, 437, 49, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				TextOut( hDC, 432, 49, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 431, 2, 495, 66 );
		}
		MoveToEx( hDC, 431, 23, NULL );
		LineTo( hDC, 494, 23 );
		MoveToEx( hDC, 431, 44, NULL );
		LineTo( hDC, 494, 44 );
		TextOut( hDC, 437, 7, "ADC2B", 5 );

		SelectObject( hDC, gdiBlackBrush );

		// CDR1
		if (0)// IDP is commanding
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 17, 101, 81, 200 );
			if (1 != 0)// FC bus
			{
				sprintf_s( cbuf, 8, "FC%d", 1 );
				TextOut( hDC, 28, 131, cbuf, 3 );
			}
			if (1) TextOut( hDC, 28, 145, "AUTO", 4 );// MDU port reconfiguration mode
			else TextOut( hDC, 28, 145, "MAN", 3 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 28, 159, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 18, 173, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 23, 173, "EDUMP", 5 );
			else if (0) TextOut( hDC, 23, 173, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				TextOut( hDC, 18, 173, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
			sprintf_s( cbuf, 8, "V %02d%02d", 1, 2 );// SW version number
			TextOut( hDC, 18, 187, cbuf, strlen( cbuf ) );
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 17, 101, 81, 200 );
			if (1)// IDP is communicating
			{
				if (1) TextOut( hDC, 28, 145, "AUTO", 4 );// MDU port reconfiguration mode
				else TextOut( hDC, 28, 145, "MAN", 3 );
			}
		}
		MoveToEx( hDC, 17, 115, NULL );
		LineTo( hDC, 80, 115 );
		MoveToEx( hDC, 17, 129, NULL );
		LineTo( hDC, 80, 129 );
		MoveToEx( hDC, 17, 143, NULL );
		LineTo( hDC, 80, 143 );
		MoveToEx( hDC, 17, 157, NULL );
		LineTo( hDC, 80, 157 );
		MoveToEx( hDC, 17, 171, NULL );
		LineTo( hDC, 80, 171 );
		MoveToEx( hDC, 17, 185, NULL );
		LineTo( hDC, 80, 185 );
		MoveToEx( hDC, 49, 115, NULL );
		LineTo( hDC, 49, 129 );
		TextOut( hDC, 28, 103, "CDR1", 4 );
		TextOut( hDC, 28, 117, "3", 1 );
		TextOut( hDC, 58, 117, "1", 1 );

		// CDR2
		if (0)// IDP is commanding
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 86, 101, 150, 200 );
			if (2 != 0)// FC bus
			{
				sprintf_s( cbuf, 8, "FC%d", 2 );
				TextOut( hDC, 97, 131, cbuf, 3 );
			}
			if (1) TextOut( hDC, 97, 145, "AUTO", 4 );// MDU port reconfiguration mode
			else TextOut( hDC, 97, 145, "MAN", 3 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 97, 159, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 87, 173, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 92, 173, "EDUMP", 5 );
			else if (0) TextOut( hDC, 92, 173, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				TextOut( hDC, 87, 173, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
			sprintf_s( cbuf, 8, "V %02d%02d", 1, 2 );// SW version number
			TextOut( hDC, 87, 187, cbuf, strlen( cbuf ) );
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 86, 101, 150, 200 );
			if (1)// IDP is communicating
			{
				if (1) TextOut( hDC, 97, 145, "AUTO", 4 );// MDU port reconfiguration mode
				else TextOut( hDC, 97, 145, "MAN", 3 );
			}
		}
		MoveToEx( hDC, 86, 115, NULL );
		LineTo( hDC, 149, 115 );
		MoveToEx( hDC, 86, 129, NULL );
		LineTo( hDC, 149, 129 );
		MoveToEx( hDC, 86, 143, NULL );
		LineTo( hDC, 149, 143 );
		MoveToEx( hDC, 86, 157, NULL );
		LineTo( hDC, 149, 157 );
		MoveToEx( hDC, 86, 171, NULL );
		LineTo( hDC, 149, 171 );
		MoveToEx( hDC, 86, 185, NULL );
		LineTo( hDC, 149, 185 );
		MoveToEx( hDC, 118, 115, NULL );
		LineTo( hDC, 118, 129 );
		TextOut( hDC, 97, 103, "CDR2", 4 );
		TextOut( hDC, 97, 117, "1", 1 );
		TextOut( hDC, 127, 117, "2", 1 );

		// CRT1
		if (0)// IDP is commanding
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 155, 31, 219, 130 );
			if (3 != 0)// FC bus
			{
				sprintf_s( cbuf, 8, "FC%d", 3 );
				TextOut( hDC, 166, 61, cbuf, 3 );
			}
			if (1) TextOut( hDC, 166, 75, "AUTO", 4 );// MDU port reconfiguration mode
			else TextOut( hDC, 166, 75, "MAN", 3 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 166, 89, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 156, 103, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 161, 103, "EDUMP", 5 );
			else if (0) TextOut( hDC, 161, 103, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				TextOut( hDC, 156, 103, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
			sprintf_s( cbuf, 8, "V %02d%02d", 1, 2 );// SW version number
			TextOut( hDC, 156, 117, cbuf, strlen( cbuf ) );
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 155, 31, 219, 130 );
			if (1)// IDP is communicating
			{
				if (1) TextOut( hDC, 166, 75, "AUTO", 4 );// MDU port reconfiguration mode
				else TextOut( hDC, 166, 75, "MAN", 3 );
			}
		}
		MoveToEx( hDC, 155, 45, NULL );
		LineTo( hDC, 218, 45 );
		MoveToEx( hDC, 155, 59, NULL );
		LineTo( hDC, 218, 59 );
		MoveToEx( hDC, 155, 73, NULL );
		LineTo( hDC, 218, 73 );
		MoveToEx( hDC, 155, 87, NULL );
		LineTo( hDC, 218, 87 );
		MoveToEx( hDC, 155, 101, NULL );
		LineTo( hDC, 218, 101 );
		MoveToEx( hDC, 155, 115, NULL );
		LineTo( hDC, 218, 115 );
		MoveToEx( hDC, 187, 45, NULL );
		LineTo( hDC, 187, 58 );
		TextOut( hDC, 166, 33, "CRT1", 4 );
		TextOut( hDC, 166, 47, "1", 1 );

		// CRT2
		if (0)// IDP is commanding
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 293, 31, 357, 130 );
			if (4 != 0)// FC bus
			{
				sprintf_s( cbuf, 8, "FC%d", 4 );
				TextOut( hDC, 304, 61, cbuf, 3 );
			}
			if (1) TextOut( hDC, 304, 75, "AUTO", 4 );// MDU port reconfiguration mode
			else TextOut( hDC, 304, 75, "MAN", 3 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 304, 89, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 294, 103, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 299, 103, "EDUMP", 5 );
			else if (0) TextOut( hDC, 299, 103, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				TextOut( hDC, 294, 103, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
			sprintf_s( cbuf, 8, "V %02d%02d", 1, 2 );// SW version number
			TextOut( hDC, 294, 117, cbuf, strlen( cbuf ) );
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 293, 31, 357, 130 );
			if (1)// IDP is communicating
			{
				if (1) TextOut( hDC, 304, 75, "AUTO", 4 );// MDU port reconfiguration mode
				else TextOut( hDC, 304, 75, "MAN", 3 );
			}
		}
		MoveToEx( hDC, 293, 45, NULL );
		LineTo( hDC, 356, 45 );
		MoveToEx( hDC, 293, 59, NULL );
		LineTo( hDC, 356, 59 );
		MoveToEx( hDC, 293, 73, NULL );
		LineTo( hDC, 356, 73 );
		MoveToEx( hDC, 293, 87, NULL );
		LineTo( hDC, 356, 87 );
		MoveToEx( hDC, 293, 101, NULL );
		LineTo( hDC, 356, 101 );
		MoveToEx( hDC, 293, 115, NULL );
		LineTo( hDC, 356, 115 );
		MoveToEx( hDC, 325, 45, NULL );
		LineTo( hDC, 325, 58 );
		TextOut( hDC, 304, 33, "CRT2", 4 );
		TextOut( hDC, 304, 47, "2", 1 );

		// CRT3
		if (0)// IDP is commanding
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 224, 101, 288, 200 );
			if (1 != 0)// FC bus
			{
				sprintf_s( cbuf, 8, "FC%d", 1 );
				TextOut( hDC, 235, 131, cbuf, 3 );
			}
			if (1) TextOut( hDC, 235, 145, "AUTO", 4 );// MDU port reconfiguration mode
			else TextOut( hDC, 235, 145, "MAN", 3 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 235, 159, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 225, 173, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 230, 173, "EDUMP", 5 );
			else if (0) TextOut( hDC, 230, 173, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				TextOut( hDC, 225, 173, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
			sprintf_s( cbuf, 8, "V %02d%02d", 1, 2 );// SW version number
			TextOut( hDC, 225, 187, cbuf, strlen( cbuf ) );
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 224, 101, 288, 200 );
			if (1)// IDP is communicating
			{
				if (1) TextOut( hDC, 235, 145, "AUTO", 4 );// MDU port reconfiguration mode
				else TextOut( hDC, 235, 145, "MAN", 3 );
			}
		}
		MoveToEx( hDC, 224, 115, NULL );
		LineTo( hDC, 287, 115 );
		MoveToEx( hDC, 224, 129, NULL );
		LineTo( hDC, 287, 129 );
		MoveToEx( hDC, 224, 143, NULL );
		LineTo( hDC, 287, 143 );
		MoveToEx( hDC, 224, 157, NULL );
		LineTo( hDC, 287, 157 );
		MoveToEx( hDC, 224, 171, NULL );
		LineTo( hDC, 287, 171 );
		MoveToEx( hDC, 224, 185, NULL );
		LineTo( hDC, 287, 185 );
		MoveToEx( hDC, 256, 115, NULL );
		LineTo( hDC, 256, 129 );
		TextOut( hDC, 235, 103, "CRT3", 4 );
		TextOut( hDC, 235, 117, "3", 1 );

		// MFD1
		if (0)// IDP is commanding
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 155, 143, 219, 242 );
			if (2 != 0)// FC bus
			{
				sprintf_s( cbuf, 8, "FC%d", 2 );
				TextOut( hDC, 166, 173, cbuf, 3 );
			}
			if (1) TextOut( hDC, 166, 187, "AUTO", 4 );// MDU port reconfiguration mode
			else TextOut( hDC, 166, 187, "MAN", 3 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 166, 201, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 156, 215, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 161, 215, "EDUMP", 5 );
			else if (0) TextOut( hDC, 161, 215, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				TextOut( hDC, 156, 215, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
			sprintf_s( cbuf, 8, "V %02d%02d", 1, 2 );// SW version number
			TextOut( hDC, 156, 229, cbuf, strlen( cbuf ) );
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 155, 143, 219, 242 );
			if (1)// IDP is communicating
			{
				if (1) TextOut( hDC, 166, 187, "AUTO", 4 );// MDU port reconfiguration mode
				else TextOut( hDC, 166, 187, "MAN", 3 );
			}
		}
		MoveToEx( hDC, 155, 157, NULL );
		LineTo( hDC, 218, 157 );
		MoveToEx( hDC, 155, 171, NULL );
		LineTo( hDC, 218, 171 );
		MoveToEx( hDC, 155, 185, NULL );
		LineTo( hDC, 218, 185 );
		MoveToEx( hDC, 155, 199, NULL );
		LineTo( hDC, 218, 199 );
		MoveToEx( hDC, 155, 213, NULL );
		LineTo( hDC, 218, 213 );
		MoveToEx( hDC, 155, 227, NULL );
		LineTo( hDC, 218, 227 );
		MoveToEx( hDC, 187, 157, NULL );
		LineTo( hDC, 187, 171 );
		TextOut( hDC, 166, 145, "MFD1", 4 );
		TextOut( hDC, 166, 159, "2", 1 );
		TextOut( hDC, 196, 159, "3", 1 );

		// MFD2
		if (0)// IDP is commanding
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 293, 143, 357, 242 );
			if (3 != 0)// FC bus
			{
				sprintf_s( cbuf, 8, "FC%d", 3 );
				TextOut( hDC, 304, 173, cbuf, 3 );
			}
			if (1) TextOut( hDC, 304, 187, "AUTO", 4 );// MDU port reconfiguration mode
			else TextOut( hDC, 304, 187, "MAN", 3 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 304, 201, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 294, 215, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 299, 215, "EDUMP", 5 );
			else if (0) TextOut( hDC, 299, 215, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				TextOut( hDC, 294, 215, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
			sprintf_s( cbuf, 8, "V %02d%02d", 1, 2 );// SW version number
			TextOut( hDC, 294, 229, cbuf, strlen( cbuf ) );
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 293, 143, 357, 242 );
			if (1)// IDP is communicating
			{
				if (1) TextOut( hDC, 304, 187, "AUTO", 4 );// MDU port reconfiguration mode
				else TextOut( hDC, 304, 187, "MAN", 3 );
			}
		}
		MoveToEx( hDC, 293, 157, NULL );
		LineTo( hDC, 356, 157 );
		MoveToEx( hDC, 293, 171, NULL );
		LineTo( hDC, 356, 171 );
		MoveToEx( hDC, 293, 185, NULL );
		LineTo( hDC, 356, 185 );
		MoveToEx( hDC, 293, 199, NULL );
		LineTo( hDC, 356, 199 );
		MoveToEx( hDC, 293, 213, NULL );
		LineTo( hDC, 356, 213 );
		MoveToEx( hDC, 293, 227, NULL );
		LineTo( hDC, 356, 227 );
		MoveToEx( hDC, 325, 157, NULL );
		LineTo( hDC, 325, 171 );
		TextOut( hDC, 304, 145, "MFD2", 4 );
		TextOut( hDC, 304, 159, "1", 1 );
		TextOut( hDC, 334, 159, "3", 1 );

		// PLT1
		if (0)// IDP is commanding
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 362, 101, 426, 200 );
			if (4 != 0)// FC bus
			{
				sprintf_s( cbuf, 8, "FC%d", 4 );
				TextOut( hDC, 373, 131, cbuf, 3 );
			}
			if (1) TextOut( hDC, 373, 145, "AUTO", 4 );// MDU port reconfiguration mode
			else TextOut( hDC, 373, 145, "MAN", 3 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 373, 159, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 363, 173, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 368, 173, "EDUMP", 5 );
			else if (0) TextOut( hDC, 368, 173, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				TextOut( hDC, 363, 173, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
			sprintf_s( cbuf, 8, "V %02d%02d", 1, 2 );// SW version number
			TextOut( hDC, 363, 187, cbuf, strlen( cbuf ) );
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 362, 101, 426, 200 );
			if (1)// IDP is communicating
			{
				if (1) TextOut( hDC, 373, 145, "AUTO", 4 );// MDU port reconfiguration mode
				else TextOut( hDC, 373, 145, "MAN", 3 );
			}
		}
		MoveToEx( hDC, 362, 115, NULL );
		LineTo( hDC, 425, 115 );
		MoveToEx( hDC, 362, 129, NULL );
		LineTo( hDC, 425, 129 );
		MoveToEx( hDC, 362, 143, NULL );
		LineTo( hDC, 425, 143 );
		MoveToEx( hDC, 362, 157, NULL );
		LineTo( hDC, 425, 157 );
		MoveToEx( hDC, 362, 171, NULL );
		LineTo( hDC, 425, 171 );
		MoveToEx( hDC, 362, 185, NULL );
		LineTo( hDC, 425, 185 );
		MoveToEx( hDC, 394, 115, NULL );
		LineTo( hDC, 394, 129 );
		TextOut( hDC, 373, 103, "PLT1", 4 );
		TextOut( hDC, 373, 117, "2", 1 );
		TextOut( hDC, 403, 117, "1", 1 );

		// PLT2
		if (0)// IDP is commanding
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 431, 101, 495, 200 );
			if (1 != 0)// FC bus
			{
				sprintf_s( cbuf, 8, "FC%d", 1 );
				TextOut( hDC, 442, 131, cbuf, 3 );
			}
			if (1) TextOut( hDC, 442, 145, "AUTO", 4 );// MDU port reconfiguration mode
			else TextOut( hDC, 442, 145, "MAN", 3 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 442, 159, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 432, 173, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 437, 173, "EDUMP", 5 );
			else if (0) TextOut( hDC, 437, 173, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				TextOut( hDC, 432, 173, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
			sprintf_s( cbuf, 8, "V %02d%02d", 1, 2 );// SW version number
			TextOut( hDC, 432, 187, cbuf, strlen( cbuf ) );
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 431, 101, 495, 200 );
			if (1)// IDP is communicating
			{
				if (1) TextOut( hDC, 442, 145, "AUTO", 4 );// MDU port reconfiguration mode
				else TextOut( hDC, 442, 145, "MAN", 3 );
			}
		}
		MoveToEx( hDC, 431, 115, NULL );
		LineTo( hDC, 494, 115 );
		MoveToEx( hDC, 431, 129, NULL );
		LineTo( hDC, 494, 129 );
		MoveToEx( hDC, 431, 143, NULL );
		LineTo( hDC, 494, 143 );
		MoveToEx( hDC, 431, 157, NULL );
		LineTo( hDC, 494, 157 );
		MoveToEx( hDC, 431, 171, NULL );
		LineTo( hDC, 494, 171 );
		MoveToEx( hDC, 431, 185, NULL );
		LineTo( hDC, 494, 185 );
		MoveToEx( hDC, 463, 115, NULL );
		LineTo( hDC, 463, 129 );
		TextOut( hDC, 442, 103, "PLT2", 4 );
		TextOut( hDC, 442, 117, "3", 1 );
		TextOut( hDC, 472, 117, "2", 1 );

		// CRT4
		if (0)// IDP is commanding
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 362, 255, 426, 354 );
			if (2 != 0)// FC bus
			{
				sprintf_s( cbuf, 8, "FC%d", 2 );
				TextOut( hDC, 373, 285, cbuf, 3 );
			}
			if (1) TextOut( hDC, 373, 299, "AUTO", 4 );// MDU port reconfiguration mode
			else TextOut( hDC, 373, 299, "MAN", 3 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 373, 313, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 363, 327, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 368, 327, "EDUMP", 5 );
			else if (0) TextOut( hDC, 368, 327, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				TextOut( hDC, 363, 327, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
			sprintf_s( cbuf, 8, "V %02d%02d", 1, 2 );// SW version number
			TextOut( hDC, 363, 341, cbuf, strlen( cbuf ) );
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 362, 255, 426, 354 );
			if (1)// IDP is communicating
			{
				if (1) TextOut( hDC, 373, 299, "AUTO", 4 );// MDU port reconfiguration mode
				else TextOut( hDC, 373, 299, "MAN", 3 );
			}
		}
		MoveToEx( hDC, 362, 269, NULL );
		LineTo( hDC, 425, 269 );
		MoveToEx( hDC, 362, 283, NULL );
		LineTo( hDC, 425, 283 );
		MoveToEx( hDC, 362, 297, NULL );
		LineTo( hDC, 425, 297 );
		MoveToEx( hDC, 362, 311, NULL );
		LineTo( hDC, 425, 311 );
		MoveToEx( hDC, 362, 325, NULL );
		LineTo( hDC, 425, 325 );
		MoveToEx( hDC, 362, 339, NULL );
		LineTo( hDC, 425, 339 );
		MoveToEx( hDC, 394, 269, NULL );
		LineTo( hDC, 394, 283 );
		TextOut( hDC, 373, 257, "CRT4", 4 );
		TextOut( hDC, 373, 271, "4", 1 );

		// AFD1
		if (0)// IDP is commanding
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 431, 255, 495, 354 );
			if (3 != 0)// FC bus
			{
				sprintf_s( cbuf, 8, "FC%d", 3 );
				TextOut( hDC, 442, 285, cbuf, 3 );
			}
			if (1) TextOut( hDC, 442, 299, "AUTO", 4 );// MDU port reconfiguration mode
			else TextOut( hDC, 442, 299, "MAN", 3 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 442, 313, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 432, 327, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 437, 327, "EDUMP", 5 );
			else if (0) TextOut( hDC, 437, 327, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				TextOut( hDC, 432, 327, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
			sprintf_s( cbuf, 8, "V %02d%02d", 1, 2 );// SW version number
			TextOut( hDC, 432, 341, cbuf, strlen( cbuf ) );
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 431, 255, 495, 354 );
			if (1)// IDP is communicating
			{
				if (1) TextOut( hDC, 442, 299, "AUTO", 4 );// MDU port reconfiguration mode
				else TextOut( hDC, 442, 299, "MAN", 3 );
			}
		}
		MoveToEx( hDC, 431, 269, NULL );
		LineTo( hDC, 494, 269 );
		MoveToEx( hDC, 431, 283, NULL );
		LineTo( hDC, 494, 283 );
		MoveToEx( hDC, 431, 297, NULL );
		LineTo( hDC, 494, 297 );
		MoveToEx( hDC, 431, 311, NULL );
		LineTo( hDC, 494, 311 );
		MoveToEx( hDC, 431, 325, NULL );
		LineTo( hDC, 494, 325 );
		MoveToEx( hDC, 431, 339, NULL );
		LineTo( hDC, 494, 339 );
		MoveToEx( hDC, 463, 269, NULL );
		LineTo( hDC, 463, 283 );
		TextOut( hDC, 442, 257, "AFD1", 4 );
		TextOut( hDC, 442, 271, "4", 1 );
		TextOut( hDC, 472, 271, "2", 1 );

		// IDP1
		if (GetDrivingIDP() == 1)// commanding IDP
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 8, 273, 90, 354 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 28, 292, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 18, 308, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 23, 308, "EDUMP", 5 );
			else if (0) TextOut( hDC, 23, 308, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				TextOut( hDC, 18, 308, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
			if (1)// flight-critical buses selected (1)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 8, 321, 29, 337 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 14, 324, "1", 1 );
			if (0)// flight-critical buses selected (2)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 29, 321, 49, 337 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 33, 324, "2", 1 );
			if (1)// flight-critical buses selected (3)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 49, 321, 69, 337 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 53, 324, "3", 1 );
			if (0)// flight-critical buses selected (4)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 69, 321, 90, 337 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 73, 324, "4", 1 );
			SetTextColor( hDC, CR_WHITE );
			sprintf_s( cbuf, 8, "V %02d%02d", 1, 2 );// SW version number
			TextOut( hDC, 18, 340, cbuf, strlen( cbuf ) );
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 8, 273, 90, 354 );
			SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 14, 324, "1", 1 );
			TextOut( hDC, 33, 324, "2", 1 );
			TextOut( hDC, 53, 324, "3", 1 );
			TextOut( hDC, 73, 324, "4", 1 );
		}
		MoveToEx( hDC, 8, 289, NULL );
		LineTo( hDC, 89, 289 );
		MoveToEx( hDC, 8, 305, NULL );
		LineTo( hDC, 89, 305 );
		MoveToEx( hDC, 8, 321, NULL );
		LineTo( hDC, 89, 321 );
		MoveToEx( hDC, 8, 337, NULL );
		LineTo( hDC, 89, 337 );
		TextOut( hDC, 28, 276, "IDP1", 4 );

		// IDP2
		if (GetDrivingIDP() == 2)// commanding IDP
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 94, 273, 176, 354 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 114, 292, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 104, 308, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 109, 308, "EDUMP", 5 );
			else if (0) TextOut( hDC, 109, 308, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				TextOut( hDC, 104, 308, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
			if (0)// flight-critical buses selected (1)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 94, 321, 115, 337 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 100, 324, "1", 1 );
			if (1)// flight-critical buses selected (2)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 115, 321, 135, 337 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 119, 324, "2", 1 );
			if (0)// flight-critical buses selected (3)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 135, 321, 155, 337 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 139, 324, "3", 1 );
			if (0)// flight-critical buses selected (4)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 155, 321, 176, 337 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 159, 324, "4", 1 );
			SetTextColor( hDC, CR_WHITE );
			sprintf_s( cbuf, 8, "V %02d%02d", 1, 2 );// SW version number
			TextOut( hDC, 104, 340, cbuf, strlen( cbuf ) );
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 94, 273, 176, 354 );
			SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 100, 324, "1", 1 );
			TextOut( hDC, 119, 324, "2", 1 );
			TextOut( hDC, 139, 324, "3", 1 );
			TextOut( hDC, 159, 324, "4", 1 );
		}
		MoveToEx( hDC, 94, 289, NULL );
		LineTo( hDC, 175, 289 );
		MoveToEx( hDC, 94, 305, NULL );
		LineTo( hDC, 175, 305 );
		MoveToEx( hDC, 94, 321, NULL );
		LineTo( hDC, 175, 321 );
		MoveToEx( hDC, 94, 337, NULL );
		LineTo( hDC, 175, 337 );
		TextOut( hDC, 114, 276, "IDP2", 4 );

		// IDP3
		if (GetDrivingIDP() == 3)// commanding IDP
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 180, 273, 262, 354 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 200, 292, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 190, 308, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 195, 308, "EDUMP", 5 );
			else if (0) TextOut( hDC, 195, 308, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				TextOut( hDC, 190, 308, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
			if (1)// flight-critical buses selected (1)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 180, 321, 201, 337 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 186, 324, "1", 1 );
			if (1)// flight-critical buses selected (2)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 201, 321, 221, 337 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 205, 324, "2", 1 );
			if (1)// flight-critical buses selected (3)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 221, 321, 241, 337 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 225, 324, "3", 1 );
			if (0)// flight-critical buses selected (4)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 241, 321, 262, 337 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 245, 324, "4", 1 );
			SetTextColor( hDC, CR_WHITE );
			sprintf_s( cbuf, 8, "V %02d%02d", 1, 2 );// SW version number
			TextOut( hDC, 190, 340, cbuf, strlen( cbuf ) );
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 180, 273, 262, 354 );
			SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 186, 324, "1", 1 );
			TextOut( hDC, 205, 324, "2", 1 );
			TextOut( hDC, 225, 324, "3", 1 );
			TextOut( hDC, 245, 324, "4", 1 );
		}
		MoveToEx( hDC, 180, 289, NULL );
		LineTo( hDC, 261, 289 );
		MoveToEx( hDC, 180, 305, NULL );
		LineTo( hDC, 261, 305 );
		MoveToEx( hDC, 180, 321, NULL );
		LineTo( hDC, 261, 321 );
		MoveToEx( hDC, 180, 337, NULL );
		LineTo( hDC, 261, 337 );
		TextOut( hDC, 200, 276, "IDP3", 4 );

		// IDP4
		if (GetDrivingIDP() == 4)// commanding IDP
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 266, 273, 348, 354 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 286, 292, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 276, 308, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 281, 308, "EDUMP", 5 );
			else if (0) TextOut( hDC, 281, 308, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				TextOut( hDC, 276, 308, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
			if (0)// flight-critical buses selected (1)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 266, 321, 287, 337 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 272, 324, "1", 1 );
			if (1)// flight-critical buses selected (2)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 287, 321, 307, 337 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 291, 324, "2", 1 );
			if (0)// flight-critical buses selected (3)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 307, 321, 327, 337 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 311, 324, "3", 1 );
			if (1)// flight-critical buses selected (4)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 327, 321, 348, 337 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 331, 324, "4", 1 );
			SetTextColor( hDC, CR_WHITE );
			sprintf_s( cbuf, 8, "V %02d%02d", 1, 2 );// SW version number
			TextOut( hDC, 276, 340, cbuf, strlen( cbuf ) );
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 266, 273, 348, 354 );
			SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 272, 324, "1", 1 );
			TextOut( hDC, 291, 324, "2", 1 );
			TextOut( hDC, 311, 324, "3", 1 );
			TextOut( hDC, 331, 324, "4", 1 );
		}
		MoveToEx( hDC, 266, 289, NULL );
		LineTo( hDC, 347, 289 );
		MoveToEx( hDC, 266, 305, NULL );
		LineTo( hDC, 347, 305 );
		MoveToEx( hDC, 266, 321, NULL );
		LineTo( hDC, 347, 321 );
		MoveToEx( hDC, 266, 337, NULL );
		LineTo( hDC, 347, 337 );
		TextOut( hDC, 286, 276, "IDP4", 4 );
		return;
	}

	void MDU::SystemStatusDisplay_CSTMenu( oapi::Sketchpad* skp )
	{
		char cbuf[8];

		skp->SetFont( skpSSVAFont_h10w10bold );
		skp->SetTextColor( CR_WHITE );
		skp->SetPen( skpWhitePen );

		// ADC1A
		if (0)
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 17, 2, 81, 66 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			skp->Text( 27, 28, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 18, 49, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 23, 49, "EDUMP", 5 );
			else if (0) skp->Text( 23, 49, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				skp->Text( 18, 49, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 17, 2, 81, 66 );
		}
		skp->Line( 17, 23, 80, 23 );
		skp->Line( 17, 44, 80, 44 );
		skp->Text( 23, 7, "ADC1A", 5 );

		// ADC1B
		if (0)
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 86, 2, 150, 66 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			skp->Text( 96, 28, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 87, 49, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 92, 49, "EDUMP", 5 );
			else if (0) skp->Text( 92, 49, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				skp->Text( 87, 49, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 86, 2, 150, 66 );
		}
		skp->Line( 86, 23, 149, 23 );
		skp->Line( 86, 44, 149, 44 );
		skp->Text( 92, 7, "ADC1B", 5 );

		// ADC2A
		if (0)
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 362, 2, 426, 66 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			skp->Text( 372, 28, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 363, 49, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 368, 49, "EDUMP", 5 );
			else if (0) skp->Text( 368, 49, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				skp->Text( 363, 49, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 362, 2, 426, 66 );
		}
		skp->Line( 362, 23, 425, 23 );
		skp->Line( 362, 44, 425, 44 );
		skp->Text( 368, 7, "ADC2A", 5 );

		// ADC2B
		if (0)
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 431, 2, 495, 66 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			skp->Text( 441, 28, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 432, 49, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 437, 49, "EDUMP", 5 );
			else if (0) skp->Text( 437, 49, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				skp->Text( 432, 49, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 431, 2, 495, 66 );
		}
		skp->Line( 431, 23, 494, 23 );
		skp->Line( 431, 44, 494, 44 );
		skp->Text( 437, 7, "ADC2B", 5 );

		// CDR1
		if (0)// IDP is commanding
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 17, 101, 81, 200 );
			if (1 != 0)// FC bus
			{
				sprintf_s( cbuf, 8, "FC%d", 1 );
				skp->Text( 28, 131, cbuf, 3 );
			}
			if (1) skp->Text( 28, 145, "AUTO", 4 );// MDU port reconfiguration mode
			else skp->Text( 28, 145, "MAN", 3 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			skp->Text( 28, 159, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 18, 173, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 23, 173, "EDUMP", 5 );
			else if (0) skp->Text( 23, 173, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				skp->Text( 18, 173, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
			sprintf_s( cbuf, 8, "V %02d%02d", 1, 2 );// SW version number
			skp->Text( 18, 187, cbuf, strlen( cbuf ) );
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 17, 101, 81, 200 );
			if (1)// IDP is communicating
			{
				if (1) skp->Text( 28, 145, "AUTO", 4 );// MDU port reconfiguration mode
				else skp->Text( 28, 145, "MAN", 3 );
			}
		}
		skp->Line( 17, 115, 80, 115 );
		skp->Line( 17, 129, 80, 129 );
		skp->Line( 17, 143, 80, 143 );
		skp->Line( 17, 157, 80, 157 );
		skp->Line( 17, 171, 80, 171 );
		skp->Line( 17, 185, 80, 185 );
		skp->Line( 49, 115, 49, 129 );
		skp->Text( 28, 103, "CDR1", 4 );
		skp->Text( 28, 117, "3", 1 );
		skp->Text( 58, 117, "1", 1 );

		// CDR2
		if (0)// IDP is commanding
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 86, 101, 150, 200 );
			if (2 != 0)// FC bus
			{
				sprintf_s( cbuf, 8, "FC%d", 2 );
				skp->Text( 97, 131, cbuf, 3 );
			}
			if (1) skp->Text( 97, 145, "AUTO", 4 );// MDU port reconfiguration mode
			else skp->Text( 97, 145, "MAN", 3 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			skp->Text( 97, 159, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 87, 173, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 92, 173, "EDUMP", 5 );
			else if (0) skp->Text( 92, 173, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				skp->Text( 87, 173, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
			sprintf_s( cbuf, 8, "V %02d%02d", 1, 2 );// SW version number
			skp->Text( 87, 187, cbuf, strlen( cbuf ) );
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 86, 101, 150, 200 );
			if (1)// IDP is communicating
			{
				if (1) skp->Text( 97, 145, "AUTO", 4 );// MDU port reconfiguration mode
				else skp->Text( 97, 145, "MAN", 3 );
			}
		}
		skp->Line( 86, 115, 149, 115 );
		skp->Line( 86, 129, 149, 129 );
		skp->Line( 86, 143, 149, 143 );
		skp->Line( 86, 157, 149, 157 );
		skp->Line( 86, 171, 149, 171 );
		skp->Line( 86, 185, 149, 185 );
		skp->Line( 118, 115, 118, 129 );
		skp->Text( 97, 103, "CDR2", 4 );
		skp->Text( 97, 117, "1", 1 );
		skp->Text( 127, 117, "2", 1 );

		// CRT1
		if (0)// IDP is commanding
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 155, 31, 219, 130 );
			if (3 != 0)// FC bus
			{
				sprintf_s( cbuf, 8, "FC%d", 3 );
				skp->Text( 166, 61, cbuf, 3 );
			}
			if (1) skp->Text( 166, 75, "AUTO", 4 );// MDU port reconfiguration mode
			else skp->Text( 166, 75, "MAN", 3 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			skp->Text( 166, 89, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 156, 103, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 161, 103, "EDUMP", 5 );
			else if (0) skp->Text( 161, 103, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				skp->Text( 156, 103, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
			sprintf_s( cbuf, 8, "V %02d%02d", 1, 2 );// SW version number
			skp->Text( 156, 117, cbuf, strlen( cbuf ) );
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 155, 31, 219, 130 );
			if (1)// IDP is communicating
			{
				if (1) skp->Text( 166, 75, "AUTO", 4 );// MDU port reconfiguration mode
				else skp->Text( 166, 75, "MAN", 3 );
			}
		}
		skp->Line( 155, 45, 218, 45 );
		skp->Line( 155, 59, 218, 59 );
		skp->Line( 155, 73, 218, 73 );
		skp->Line( 155, 87, 218, 87 );
		skp->Line( 155, 101, 218, 101 );
		skp->Line( 155, 115, 218, 115 );
		skp->Line( 187, 45, 187, 58 );
		skp->Text( 166, 33, "CRT1", 4 );
		skp->Text( 166, 47, "1", 1 );

		// CRT2
		if (0)// IDP is commanding
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 293, 31, 357, 130 );
			if (4 != 0)// FC bus
			{
				sprintf_s( cbuf, 8, "FC%d", 4 );
				skp->Text( 304, 61, cbuf, 3 );
			}
			if (1) skp->Text( 304, 75, "AUTO", 4 );// MDU port reconfiguration mode
			else skp->Text( 304, 75, "MAN", 3 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			skp->Text( 304, 89, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 294, 103, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 299, 103, "EDUMP", 5 );
			else if (0) skp->Text( 299, 103, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				skp->Text( 294, 103, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
			sprintf_s( cbuf, 8, "V %02d%02d", 1, 2 );// SW version number
			skp->Text( 294, 117, cbuf, strlen( cbuf ) );
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 293, 31, 357, 130 );
			if (1)// IDP is communicating
			{
				if (1) skp->Text( 304, 75, "AUTO", 4 );// MDU port reconfiguration mode
				else skp->Text( 304, 75, "MAN", 3 );
			}
		}
		skp->Line( 293, 45, 356, 45 );
		skp->Line( 293, 59, 356, 59 );
		skp->Line( 293, 73, 356, 73 );
		skp->Line( 293, 87, 356, 87 );
		skp->Line( 293, 101, 356, 101 );
		skp->Line( 293, 115, 356, 115 );
		skp->Line( 325, 45, 325, 58 );
		skp->Text( 304, 33, "CRT2", 4 );
		skp->Text( 304, 47, "2", 1 );

		// CRT3
		if (0)// IDP is commanding
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 224, 101, 288, 200 );
			if (1 != 0)// FC bus
			{
				sprintf_s( cbuf, 8, "FC%d", 1 );
				skp->Text( 235, 131, cbuf, 3 );
			}
			if (1) skp->Text( 235, 145, "AUTO", 4 );// MDU port reconfiguration mode
			else skp->Text( 235, 145, "MAN", 3 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			skp->Text( 235, 159, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 225, 173, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 230, 173, "EDUMP", 5 );
			else if (0) skp->Text( 230, 173, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				skp->Text( 225, 173, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
			sprintf_s( cbuf, 8, "V %02d%02d", 1, 2 );// SW version number
			skp->Text( 225, 187, cbuf, strlen( cbuf ) );
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 224, 101, 288, 200 );
			if (1)// IDP is communicating
			{
				if (1) skp->Text( 235, 145, "AUTO", 4 );// MDU port reconfiguration mode
				else skp->Text( 235, 145, "MAN", 3 );
			}
		}
		skp->Line( 224, 115, 287, 115 );
		skp->Line( 224, 129, 287, 129 );
		skp->Line( 224, 143, 287, 143 );
		skp->Line( 224, 157, 287, 157 );
		skp->Line( 224, 171, 287, 171 );
		skp->Line( 224, 185, 287, 185 );
		skp->Line( 256, 115, 256, 129 );
		skp->Text( 235, 103, "CRT3", 4 );
		skp->Text( 235, 117, "3", 1 );

		// MFD1
		if (0)// IDP is commanding
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 155, 143, 219, 242 );
			if (2 != 0)// FC bus
			{
				sprintf_s( cbuf, 8, "FC%d", 2 );
				skp->Text( 166, 173, cbuf, 3 );
			}
			if (1) skp->Text( 166, 187, "AUTO", 4 );// MDU port reconfiguration mode
			else skp->Text( 166, 187, "MAN", 3 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			skp->Text( 166, 201, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 156, 215, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 161, 215, "EDUMP", 5 );
			else if (0) skp->Text( 161, 215, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				skp->Text( 156, 215, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
			sprintf_s( cbuf, 8, "V %02d%02d", 1, 2 );// SW version number
			skp->Text( 156, 229, cbuf, strlen( cbuf ) );
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 155, 143, 219, 242 );
			if (1)// IDP is communicating
			{
				if (1) skp->Text( 166, 187, "AUTO", 4 );// MDU port reconfiguration mode
				else skp->Text( 166, 187, "MAN", 3 );
			}
		}
		skp->Line( 155, 157, 218, 157 );
		skp->Line( 155, 171, 218, 171 );
		skp->Line( 155, 185, 218, 185 );
		skp->Line( 155, 199, 218, 199 );
		skp->Line( 155, 213, 218, 213 );
		skp->Line( 155, 227, 218, 227 );
		skp->Line( 187, 157, 187, 171 );
		skp->Text( 166, 145, "MFD1", 4 );
		skp->Text( 166, 159, "2", 1 );
		skp->Text( 196, 159, "3", 1 );

		// MFD2
		if (0)// IDP is commanding
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 293, 143, 357, 242 );
			if (3 != 0)// FC bus
			{
				sprintf_s( cbuf, 8, "FC%d", 3 );
				skp->Text( 304, 173, cbuf, 3 );
			}
			if (1) skp->Text( 304, 187, "AUTO", 4 );// MDU port reconfiguration mode
			else skp->Text( 304, 187, "MAN", 3 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			skp->Text( 304, 201, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 294, 215, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 299, 215, "EDUMP", 5 );
			else if (0) skp->Text( 299, 215, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				skp->Text( 294, 215, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
			sprintf_s( cbuf, 8, "V %02d%02d", 1, 2 );// SW version number
			skp->Text( 294, 229, cbuf, strlen( cbuf ) );
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 293, 143, 357, 242 );
			if (1)// IDP is communicating
			{
				if (1) skp->Text( 304, 187, "AUTO", 4 );// MDU port reconfiguration mode
				else skp->Text( 304, 187, "MAN", 3 );
			}
		}
		skp->Line( 293, 157, 356, 157 );
		skp->Line( 293, 171, 356, 171 );
		skp->Line( 293, 185, 356, 185 );
		skp->Line( 293, 199, 356, 199 );
		skp->Line( 293, 213, 356, 213 );
		skp->Line( 293, 227, 356, 227 );
		skp->Line( 325, 157, 325, 171 );
		skp->Text( 304, 145, "MFD2", 4 );
		skp->Text( 304, 159, "1", 1 );
		skp->Text( 334, 159, "3", 1 );

		// PLT1
		if (0)// IDP is commanding
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 362, 101, 426, 200 );
			if (4 != 0)// FC bus
			{
				sprintf_s( cbuf, 8, "FC%d", 4 );
				skp->Text( 373, 131, cbuf, 3 );
			}
			if (1) skp->Text( 373, 145, "AUTO", 4 );// MDU port reconfiguration mode
			else skp->Text( 373, 145, "MAN", 3 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			skp->Text( 373, 159, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 363, 173, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 368, 173, "EDUMP", 5 );
			else if (0) skp->Text( 368, 173, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				skp->Text( 363, 173, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
			sprintf_s( cbuf, 8, "V %02d%02d", 1, 2 );// SW version number
			skp->Text( 363, 187, cbuf, strlen( cbuf ) );
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 362, 101, 426, 200 );
			if (1)// IDP is communicating
			{
				if (1) skp->Text( 373, 145, "AUTO", 4 );// MDU port reconfiguration mode
				else skp->Text( 373, 145, "MAN", 3 );
			}
		}
		skp->Line( 362, 115, 425, 115 );
		skp->Line( 362, 129, 425, 129 );
		skp->Line( 362, 143, 425, 143 );
		skp->Line( 362, 157, 425, 157 );
		skp->Line( 362, 171, 425, 171 );
		skp->Line( 362, 185, 425, 185 );
		skp->Line( 394, 115, 394, 129 );
		skp->Text( 373, 103, "PLT1", 4 );
		skp->Text( 373, 117, "2", 1 );
		skp->Text( 403, 117, "1", 1 );

		// PLT2
		if (0)// IDP is commanding
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 431, 101, 495, 200 );
			if (1 != 0)// FC bus
			{
				sprintf_s( cbuf, 8, "FC%d", 1 );
				skp->Text( 442, 131, cbuf, 3 );
			}
			if (1) skp->Text( 442, 145, "AUTO", 4 );// MDU port reconfiguration mode
			else skp->Text( 442, 145, "MAN", 3 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			skp->Text( 442, 159, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 432, 173, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 437, 173, "EDUMP", 5 );
			else if (0) skp->Text( 437, 173, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				skp->Text( 432, 173, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
			sprintf_s( cbuf, 8, "V %02d%02d", 1, 2 );// SW version number
			skp->Text( 432, 187, cbuf, strlen( cbuf ) );
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 431, 101, 495, 200 );
			if (1)// IDP is communicating
			{
				if (1) skp->Text( 442, 145, "AUTO", 4 );// MDU port reconfiguration mode
				else skp->Text( 442, 145, "MAN", 3 );
			}
		}
		skp->Line( 431, 115, 494, 115 );
		skp->Line( 431, 129, 494, 129 );
		skp->Line( 431, 143, 494, 143 );
		skp->Line( 431, 157, 494, 157 );
		skp->Line( 431, 171, 494, 171 );
		skp->Line( 431, 185, 494, 185 );
		skp->Line( 463, 115, 463, 129 );
		skp->Text( 442, 103, "PLT2", 4 );
		skp->Text( 442, 117, "3", 1 );
		skp->Text( 472, 117, "2", 1 );

		// CRT4
		if (0)// IDP is commanding
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 362, 255, 426, 354 );
			if (2 != 0)// FC bus
			{
				sprintf_s( cbuf, 8, "FC%d", 2 );
				skp->Text( 373, 285, cbuf, 3 );
			}
			if (1) skp->Text( 373, 299, "AUTO", 4 );// MDU port reconfiguration mode
			else skp->Text( 373, 299, "MAN", 3 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			skp->Text( 373, 313, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 363, 327, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 368, 327, "EDUMP", 5 );
			else if (0) skp->Text( 368, 327, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				skp->Text( 363, 327, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
			sprintf_s( cbuf, 8, "V %02d%02d", 1, 2 );// SW version number
			skp->Text( 363, 341, cbuf, strlen( cbuf ) );
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 362, 255, 426, 354 );
			if (1)// IDP is communicating
			{
				if (1) skp->Text( 373, 299, "AUTO", 4 );// MDU port reconfiguration mode
				else skp->Text( 373, 299, "MAN", 3 );
			}
		}
		skp->Line( 362, 269, 425, 269 );
		skp->Line( 362, 283, 425, 283 );
		skp->Line( 362, 297, 425, 297 );
		skp->Line( 362, 311, 425, 311 );
		skp->Line( 362, 325, 425, 325 );
		skp->Line( 362, 339, 425, 339 );
		skp->Line( 394, 269, 394, 283 );
		skp->Text( 373, 257, "CRT4", 4 );
		skp->Text( 373, 271, "4", 1 );

		// AFD1
		if (0)// IDP is commanding
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 431, 255, 495, 354 );
			if (3 != 0)// FC bus
			{
				sprintf_s( cbuf, 8, "FC%d", 3 );
				skp->Text( 442, 285, cbuf, 3 );
			}
			if (1) skp->Text( 442, 299, "AUTO", 4 );// MDU port reconfiguration mode
			else skp->Text( 442, 299, "MAN", 3 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			skp->Text( 442, 313, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 432, 327, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 437, 327, "EDUMP", 5 );
			else if (0) skp->Text( 437, 327, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				skp->Text( 432, 327, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
			sprintf_s( cbuf, 8, "V %02d%02d", 1, 2 );// SW version number
			skp->Text( 432, 341, cbuf, strlen( cbuf ) );
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 431, 255, 495, 354 );
			if (1)// IDP is communicating
			{
				if (1) skp->Text( 442, 299, "AUTO", 4 );// MDU port reconfiguration mode
				else skp->Text( 442, 299, "MAN", 3 );
			}
		}
		skp->Line( 431, 269, 494, 269 );
		skp->Line( 431, 283, 494, 283 );
		skp->Line( 431, 297, 494, 297 );
		skp->Line( 431, 311, 494, 311 );
		skp->Line( 431, 325, 494, 325 );
		skp->Line( 431, 339, 494, 339 );
		skp->Line( 463, 269, 463, 283 );
		skp->Text( 442, 257, "AFD1", 4 );
		skp->Text( 442, 271, "4", 1 );
		skp->Text( 472, 271, "2", 1 );

		// IDP1
		if (GetDrivingIDP() == 1)// commanding IDP
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 8, 273, 90, 354 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			skp->Text( 28, 292, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 18, 308, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 23, 308, "EDUMP", 5 );
			else if (0) skp->Text( 23, 308, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				skp->Text( 18, 308, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
			if (1)// flight-critical buses selected (1)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 8, 321, 29, 337 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 14, 324, "1", 1 );
			if (0)// flight-critical buses selected (2)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 29, 321, 49, 337 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 33, 324, "2", 1 );
			if (1)// flight-critical buses selected (3)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 49, 321, 69, 337 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 53, 324, "3", 1 );
			if (0)// flight-critical buses selected (4)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 69, 321, 90, 337 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 73, 324, "4", 1 );
			skp->SetTextColor( CR_WHITE );
			sprintf_s( cbuf, 8, "V %02d%02d", 1, 2 );// SW version number
			skp->Text( 18, 340, cbuf, strlen( cbuf ) );
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 8, 273, 90, 354 );
			skp->SetTextColor( CR_WHITE );
			skp->Text( 14, 324, "1", 1 );
			skp->Text( 33, 324, "2", 1 );
			skp->Text( 53, 324, "3", 1 );
			skp->Text( 73, 324, "4", 1 );
		}
		skp->Line( 8, 289, 89, 289 );
		skp->Line( 8, 305, 89, 305 );
		skp->Line( 8, 321, 89, 321 );
		skp->Line( 8, 337, 89, 337 );
		skp->Text( 28, 276, "IDP1", 4 );

		// IDP2
		if (GetDrivingIDP() == 2)// commanding IDP
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 94, 273, 176, 354 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			skp->Text( 114, 292, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 104, 308, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 109, 308, "EDUMP", 5 );
			else if (0) skp->Text( 109, 308, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				skp->Text( 104, 308, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
			if (0)// flight-critical buses selected (1)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 94, 321, 115, 337 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 100, 324, "1", 1 );
			if (1)// flight-critical buses selected (2)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 115, 321, 135, 337 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 119, 324, "2", 1 );
			if (0)// flight-critical buses selected (3)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 135, 321, 155, 337 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 139, 324, "3", 1 );
			if (1)// flight-critical buses selected (4)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 155, 321, 176, 337 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 159, 324, "4", 1 );
			skp->SetTextColor( CR_WHITE );
			sprintf_s( cbuf, 8, "V %02d%02d", 1, 2 );// SW version number
			skp->Text( 104, 340, cbuf, strlen( cbuf ) );
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 94, 273, 176, 354 );
			skp->SetTextColor( CR_WHITE );
			skp->Text( 100, 324, "1", 1 );
			skp->Text( 119, 324, "2", 1 );
			skp->Text( 139, 324, "3", 1 );
			skp->Text( 159, 324, "4", 1 );
		}
		skp->Line( 94, 289, 175, 289 );
		skp->Line( 94, 305, 175, 305 );
		skp->Line( 94, 321, 175, 321 );
		skp->Line( 94, 337, 175, 337 );
		skp->Text( 114, 276, "IDP2", 4 );

		// IDP3
		if (GetDrivingIDP() == 3)// commanding IDP
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 180, 273, 262, 354 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			skp->Text( 200, 292, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 190, 308, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 195, 308, "EDUMP", 5 );
			else if (0) skp->Text( 195, 308, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				skp->Text( 190, 308, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
			if (1)// flight-critical buses selected (1)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 180, 321, 201, 337 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 186, 324, "1", 1 );
			if (0)// flight-critical buses selected (2)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 201, 321, 221, 337 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 205, 324, "2", 1 );
			if (1)// flight-critical buses selected (3)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 221, 321, 241, 337 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 225, 324, "3", 1 );
			if (0)// flight-critical buses selected (4)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 241, 321, 262, 337 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 245, 324, "4", 1 );
			skp->SetTextColor( CR_WHITE );
			sprintf_s( cbuf, 8, "V %02d%02d", 1, 2 );// SW version number
			skp->Text( 190, 340, cbuf, strlen( cbuf ) );
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 180, 273, 262, 354 );
			skp->SetTextColor( CR_WHITE );
			skp->Text( 186, 324, "1", 1 );
			skp->Text( 205, 324, "2", 1 );
			skp->Text( 225, 324, "3", 1 );
			skp->Text( 245, 324, "4", 1 );
		}
		skp->Line( 180, 289, 261, 289 );
		skp->Line( 180, 305, 261, 305 );
		skp->Line( 180, 321, 261, 321 );
		skp->Line( 180, 337, 261, 337 );
		skp->Text( 200, 276, "IDP3", 4 );

		// IDP4
		if (GetDrivingIDP() == 4)// commanding IDP
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 266, 273, 348, 354 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 8, "%04X", 0 );// Built In Test Summary
			skp->Text( 286, 292, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 276, 308, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 281, 308, "EDUMP", 5 );
			else if (0) skp->Text( 281, 308, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 8, "%06X", 0 );
				skp->Text( 276, 308, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
			if (0)// flight-critical buses selected (1)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 266, 321, 287, 337 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 272, 324, "1", 1 );
			if (1)// flight-critical buses selected (2)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 287, 321, 307, 337 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 291, 324, "2", 1 );
			if (0)// flight-critical buses selected (3)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 307, 321, 327, 337 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 311, 324, "3", 1 );
			if (1)// flight-critical buses selected (4)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 327, 321, 348, 337 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 331, 324, "4", 1 );
			skp->SetTextColor( CR_WHITE );
			sprintf_s( cbuf, 8, "V %02d%02d", 1, 2 );// SW version number
			skp->Text( 276, 340, cbuf, strlen( cbuf ) );
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 266, 273, 348, 354 );
			skp->SetTextColor( CR_WHITE );
			skp->Text( 272, 324, "1", 1 );
			skp->Text( 291, 324, "2", 1 );
			skp->Text( 311, 324, "3", 1 );
			skp->Text( 331, 324, "4", 1 );
		}
		skp->Line( 266, 289, 347, 289 );
		skp->Line( 266, 305, 347, 305 );
		skp->Line( 266, 321, 347, 321 );
		skp->Line( 266, 337, 347, 337 );
		skp->Text( 286, 276, "IDP4", 4 );

		return;
	}

	void MDU::SystemStatusDisplay_IDPInteractiveCST( HDC hDC )
	{
		char cbuf[16];

		SelectObject( hDC, gdiSSVAFont_h10w10bold );
		SetTextColor( hDC, CR_WHITE );
		SelectObject( hDC, gdiWhitePen );

		// ADC1A
		if (0)
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 17, 293, 81, 357 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 27, 319, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 18, 340, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 23, 340, "EDUMP", 5 );
			else if (0) TextOut( hDC, 23, 340, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				TextOut( hDC, 18, 340, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 17, 293, 81, 357 );
		}
		MoveToEx( hDC, 17, 314, NULL );
		LineTo( hDC, 80, 314 );
		MoveToEx( hDC, 17, 335, NULL );
		LineTo( hDC, 80, 335 );
		TextOut( hDC, 23, 298, "ADC1A", 5 );

		// ADC1B
		if (0)
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 86, 293, 150, 357 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 96, 319, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 87, 340, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 92, 340, "EDUMP", 5 );
			else if (0) TextOut( hDC, 92, 340, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				TextOut( hDC, 87, 340, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 86, 293, 150, 357 );
		}
		MoveToEx( hDC, 86, 314, NULL );
		LineTo( hDC, 149, 314 );
		MoveToEx( hDC, 86, 335, NULL );
		LineTo( hDC, 149, 335 );
		TextOut( hDC, 92, 298, "ADC1B", 5 );

		// ADC2A
		if (0)
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 155, 293, 219, 357 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 165, 319, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 156, 340, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 161, 340, "EDUMP", 5 );
			else if (0) TextOut( hDC, 161, 340, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				TextOut( hDC, 156, 340, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 155, 293, 219, 357 );
		}
		MoveToEx( hDC, 155, 314, NULL );
		LineTo( hDC, 218, 314 );
		MoveToEx( hDC, 155, 335, NULL );
		LineTo( hDC, 218, 335 );
		TextOut( hDC, 161, 298, "ADC2A", 5 );

		// ADC2B
		if (0)
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 224, 293, 288, 357 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 234, 319, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 225, 340, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 230, 340, "EDUMP", 5 );
			else if (0) TextOut( hDC, 230, 340, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				TextOut( hDC, 225, 340, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 224, 293, 288, 357 );
		}
		MoveToEx( hDC, 224, 314, NULL );
		LineTo( hDC, 287, 314 );
		MoveToEx( hDC, 224, 335, NULL );
		LineTo( hDC, 287, 335 );
		TextOut( hDC, 230, 298, "ADC2B", 5 );

		SelectObject( hDC, gdiBlackBrush );

		// CDR1
		if (0)// IDP is commanding
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 17, 81, 81, 166 );
			if (1 != 0)// FC bus
			{
				sprintf_s( cbuf, 16, "FC%d", 1 );
				TextOut( hDC, 28, 111, cbuf, 3 );
			}
			if (1) TextOut( hDC, 28, 125, "AUTO", 4 );// MDU port reconfiguration mode
			else TextOut( hDC, 28, 125, "MAN", 3 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 28, 139, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 18, 153, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 23, 153, "EDUMP", 5 );
			else if (0) TextOut( hDC, 23, 153, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				TextOut( hDC, 18, 153, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 17, 81, 81, 166 );
			if (1)// IDP is communicating
			{
				if (1) TextOut( hDC, 28, 125, "AUTO", 4 );// MDU port reconfiguration mode
				else TextOut( hDC, 28, 125, "MAN", 3 );
			}
		}
		MoveToEx( hDC, 17, 95, NULL );
		LineTo( hDC, 80, 95 );
		MoveToEx( hDC, 17, 109, NULL );
		LineTo( hDC, 80, 109 );
		MoveToEx( hDC, 17, 123, NULL );
		LineTo( hDC, 80, 123 );
		MoveToEx( hDC, 17, 137, NULL );
		LineTo( hDC, 80, 137 );
		MoveToEx( hDC, 17, 151, NULL );
		LineTo( hDC, 80, 151 );
		MoveToEx( hDC, 49, 95, NULL );
		LineTo( hDC, 49, 109 );
		TextOut( hDC, 28, 83, "CDR1", 4 );
		TextOut( hDC, 28, 97, "3", 1 );
		TextOut( hDC, 58, 97, "1", 1 );

		// CDR2
		if (0)// IDP is commanding
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 86, 81, 150, 166 );
			if (2 != 0)// FC bus
			{
				sprintf_s( cbuf, 16, "FC%d", 2 );
				TextOut( hDC, 97, 111, cbuf, 3 );
			}
			if (1) TextOut( hDC, 97, 125, "AUTO", 4 );// MDU port reconfiguration mode
			else TextOut( hDC, 97, 125, "MAN", 3 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 97, 139, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 87, 153, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 92, 153, "EDUMP", 5 );
			else if (0) TextOut( hDC, 92, 153, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				TextOut( hDC, 87, 153, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 86, 81, 150, 166 );
			if (1)// IDP is communicating
			{
				if (1) TextOut( hDC, 97, 125, "AUTO", 4 );// MDU port reconfiguration mode
				else TextOut( hDC, 97, 125, "MAN", 3 );
			}
		}
		MoveToEx( hDC, 86, 95, NULL );
		LineTo( hDC, 149, 95 );
		MoveToEx( hDC, 86, 109, NULL );
		LineTo( hDC, 149, 109 );
		MoveToEx( hDC, 86, 123, NULL );
		LineTo( hDC, 149, 123 );
		MoveToEx( hDC, 86, 137, NULL );
		LineTo( hDC, 149, 137 );
		MoveToEx( hDC, 86, 151, NULL );
		LineTo( hDC, 149, 151 );
		MoveToEx( hDC, 118, 95, NULL );
		LineTo( hDC, 118, 109 );
		TextOut( hDC, 97, 83, "CDR2", 4 );
		TextOut( hDC, 97, 97, "1", 1 );
		TextOut( hDC, 127, 97, "2", 1 );

		// CRT1
		if (0)// IDP is commanding
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 155, 11, 219, 96 );
			if (3 != 0)// FC bus
			{
				sprintf_s( cbuf, 16, "FC%d", 3 );
				TextOut( hDC, 166, 41, cbuf, strlen( cbuf ) );
			}
			if (1) TextOut( hDC, 166, 55, "AUTO", 4 );// MDU port reconfiguration mode
			else TextOut( hDC, 166, 55, "MAN", 3 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 166, 69, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 156, 83, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 161, 83, "EDUMP", 5 );
			else if (0) TextOut( hDC, 161, 83, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				TextOut( hDC, 156, 83, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 155, 11, 219, 96 );
			if (1)// IDP is communicating
			{
				if (1) TextOut( hDC, 166, 55, "AUTO", 4 );// MDU port reconfiguration mode
				else TextOut( hDC, 166, 55, "MAN", 3 );
			}
		}
		MoveToEx( hDC, 155, 25, NULL );
		LineTo( hDC, 218, 25 );
		MoveToEx( hDC, 155, 39, NULL );
		LineTo( hDC, 218, 39 );
		MoveToEx( hDC, 155, 53, NULL );
		LineTo( hDC, 218, 53 );
		MoveToEx( hDC, 155, 67, NULL );
		LineTo( hDC, 218, 67 );
		MoveToEx( hDC, 155, 81, NULL );
		LineTo( hDC, 218, 81 );
		MoveToEx( hDC, 187, 25, NULL );
		LineTo( hDC, 187, 38 );
		TextOut( hDC, 166, 13, "CRT1", 4 );
		TextOut( hDC, 166, 27, "1", 1 );

		// CRT2
		if (0)// IDP is commanding
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 293, 11, 357, 96 );
			if (4 != 0)// FC bus
			{
				sprintf_s( cbuf, 16, "FC%d", 4 );
				TextOut( hDC, 304, 41, cbuf, 3 );
			}
			if (1) TextOut( hDC, 304, 55, "AUTO", 4 );// MDU port reconfiguration mode
			else TextOut( hDC, 304, 55, "MAN", 3 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 304, 69, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 294, 83, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 299, 83, "EDUMP", 5 );
			else if (0) TextOut( hDC, 299, 83, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				TextOut( hDC, 294, 83, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 293, 11, 357, 96 );
			if (1)// IDP is communicating
			{
				if (1) TextOut( hDC, 304, 55, "AUTO", 4 );// MDU port reconfiguration mode
				else TextOut( hDC, 304, 55, "MAN", 3 );
			}
		}
		MoveToEx( hDC, 293, 25, NULL );
		LineTo( hDC, 356, 25 );
		MoveToEx( hDC, 293, 39, NULL );
		LineTo( hDC, 356, 39 );
		MoveToEx( hDC, 293, 53, NULL );
		LineTo( hDC, 356, 53 );
		MoveToEx( hDC, 293, 67, NULL );
		LineTo( hDC, 356, 67 );
		MoveToEx( hDC, 293, 81, NULL );
		LineTo( hDC, 356, 81 );
		MoveToEx( hDC, 325, 25, NULL );
		LineTo( hDC, 325, 38 );
		TextOut( hDC, 304, 13, "CRT2", 4 );
		TextOut( hDC, 304, 27, "2", 1 );

		// CRT3
		if (0)// IDP is commanding
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 224, 81, 288, 166 );
			if (1 != 0)// FC bus
			{
				sprintf_s( cbuf, 16, "FC%d", 1 );
				TextOut( hDC, 235, 111, cbuf, 3 );
			}
			if (1) TextOut( hDC, 235, 125, "AUTO", 4 );// MDU port reconfiguration mode
			else TextOut( hDC, 235, 125, "MAN", 3 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 235, 139, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 225, 153, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 230, 153, "EDUMP", 5 );
			else if (0) TextOut( hDC, 230, 153, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				TextOut( hDC, 225, 153, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 224, 81, 288, 166 );
			if (1)// IDP is communicating
			{
				if (1) TextOut( hDC, 235, 125, "AUTO", 4 );// MDU port reconfiguration mode
				else TextOut( hDC, 235, 125, "MAN", 3 );
			}
		}
		MoveToEx( hDC, 224, 95, NULL );
		LineTo( hDC, 287, 95 );
		MoveToEx( hDC, 224, 109, NULL );
		LineTo( hDC, 287, 109 );
		MoveToEx( hDC, 224, 123, NULL );
		LineTo( hDC, 287, 123 );
		MoveToEx( hDC, 224, 137, NULL );
		LineTo( hDC, 287, 137 );
		MoveToEx( hDC, 224, 151, NULL );
		LineTo( hDC, 287, 151 );
		MoveToEx( hDC, 256, 95, NULL );
		LineTo( hDC, 256, 109 );
		TextOut( hDC, 235, 83, "CRT3", 4 );
		TextOut( hDC, 235, 97, "3", 1 );

		// MFD1
		if (0)// IDP is commanding
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 155, 123, 219, 208 );
			if (2 != 0)// FC bus
			{
				sprintf_s( cbuf, 16, "FC%d", 2 );
				TextOut( hDC, 166, 153, cbuf, 3 );
			}
			if (1) TextOut( hDC, 166, 167, "AUTO", 4 );// MDU port reconfiguration mode
			else TextOut( hDC, 166, 167, "MAN", 3 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 166, 181, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 156, 195, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 161, 195, "EDUMP", 5 );
			else if (0) TextOut( hDC, 161, 195, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				TextOut( hDC, 156, 195, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 155, 123, 219, 208 );
			if (1)// IDP is communicating
			{
				if (1) TextOut( hDC, 166, 167, "AUTO", 4 );// MDU port reconfiguration mode
				else TextOut( hDC, 166, 167, "MAN", 3 );
			}
		}
		MoveToEx( hDC, 155, 137, NULL );
		LineTo( hDC, 218, 137 );
		MoveToEx( hDC, 155, 151, NULL );
		LineTo( hDC, 218, 151 );
		MoveToEx( hDC, 155, 165, NULL );
		LineTo( hDC, 218, 165 );
		MoveToEx( hDC, 155, 179, NULL );
		LineTo( hDC, 218, 179 );
		MoveToEx( hDC, 155, 193, NULL );
		LineTo( hDC, 218, 193 );
		MoveToEx( hDC, 187, 137, NULL );
		LineTo( hDC, 187, 151 );
		TextOut( hDC, 166, 125, "MFD1", 4 );
		TextOut( hDC, 166, 139, "2", 1 );
		TextOut( hDC, 196, 139, "3", 1 );

		// MFD2
		if (0)// IDP is commanding
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 293, 123, 357, 208 );
			if (3 != 0)// FC bus
			{
				sprintf_s( cbuf, 16, "FC%d", 3 );
				TextOut( hDC, 304, 153, cbuf, 3 );
			}
			if (1) TextOut( hDC, 304, 167, "AUTO", 4 );// MDU port reconfiguration mode
			else TextOut( hDC, 304, 167, "MAN", 3 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 304, 181, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 294, 195, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 299, 195, "EDUMP", 5 );
			else if (0) TextOut( hDC, 299, 195, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				TextOut( hDC, 294, 195, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 293, 123, 357, 208 );
			if (1)// IDP is communicating
			{
				if (1) TextOut( hDC, 304, 167, "AUTO", 4 );// MDU port reconfiguration mode
				else TextOut( hDC, 304, 167, "MAN", 3 );
			}
		}
		MoveToEx( hDC, 293, 137, NULL );
		LineTo( hDC, 356, 137 );
		MoveToEx( hDC, 293, 151, NULL );
		LineTo( hDC, 356, 151 );
		MoveToEx( hDC, 293, 165, NULL );
		LineTo( hDC, 356, 165 );
		MoveToEx( hDC, 293, 179, NULL );
		LineTo( hDC, 356, 179 );
		MoveToEx( hDC, 293, 193, NULL );
		LineTo( hDC, 356, 193 );
		MoveToEx( hDC, 325, 137, NULL );
		LineTo( hDC, 325, 151 );
		TextOut( hDC, 304, 125, "MFD2", 4 );
		TextOut( hDC, 304, 139, "1", 1 );
		TextOut( hDC, 334, 139, "3", 1 );

		// PLT1
		if (0)// IDP is commanding
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 362, 81, 426, 166 );
			if (4 != 0)// FC bus
			{
				sprintf_s( cbuf, 16, "FC%d", 4 );
				TextOut( hDC, 373, 111, cbuf, 3 );
			}
			if (1) TextOut( hDC, 373, 125, "AUTO", 4 );// MDU port reconfiguration mode
			else TextOut( hDC, 373, 125, "MAN", 3 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 373, 139, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 363, 153, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 368, 153, "EDUMP", 5 );
			else if (0) TextOut( hDC, 368, 153, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				TextOut( hDC, 363, 153, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 362, 81, 426, 166 );
			if (1)// IDP is communicating
			{
				if (1) TextOut( hDC, 373, 125, "AUTO", 4 );// MDU port reconfiguration mode
				else TextOut( hDC, 373, 125, "MAN", 3 );
			}
		}
		MoveToEx( hDC, 362, 95, NULL );
		LineTo( hDC, 425, 95 );
		MoveToEx( hDC, 362, 109, NULL );
		LineTo( hDC, 425, 109 );
		MoveToEx( hDC, 362, 123, NULL );
		LineTo( hDC, 425, 123 );
		MoveToEx( hDC, 362, 137, NULL );
		LineTo( hDC, 425, 137 );
		MoveToEx( hDC, 362, 151, NULL );
		LineTo( hDC, 425, 151 );
		MoveToEx( hDC, 394, 95, NULL );
		LineTo( hDC, 394, 109 );
		TextOut( hDC, 373, 83, "PLT1", 4 );
		TextOut( hDC, 373, 97, "2", 1 );
		TextOut( hDC, 403, 97, "1", 1 );

		// PLT2
		if (0)// IDP is commanding
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 431, 81, 495, 166 );
			if (1 != 0)// FC bus
			{
				sprintf_s( cbuf, 16, "FC%d", 1 );
				TextOut( hDC, 442, 111, cbuf, 3 );
			}
			if (1) TextOut( hDC, 442, 125, "AUTO", 4 );// MDU port reconfiguration mode
			else TextOut( hDC, 442, 125, "MAN", 3 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 442, 139, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 432, 153, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 437, 153, "EDUMP", 5 );
			else if (0) TextOut( hDC, 437, 153, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				TextOut( hDC, 432, 153, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 431, 81, 495, 166 );
			if (1)// IDP is communicating
			{
				if (1) TextOut( hDC, 442, 125, "AUTO", 4 );// MDU port reconfiguration mode
				else TextOut( hDC, 442, 125, "MAN", 3 );
			}
		}
		MoveToEx( hDC, 431, 95, NULL );
		LineTo( hDC, 494, 95 );
		MoveToEx( hDC, 431, 109, NULL );
		LineTo( hDC, 494, 109 );
		MoveToEx( hDC, 431, 123, NULL );
		LineTo( hDC, 494, 123 );
		MoveToEx( hDC, 431, 137, NULL );
		LineTo( hDC, 494, 137 );
		MoveToEx( hDC, 431, 151, NULL );
		LineTo( hDC, 494, 151 );
		MoveToEx( hDC, 463, 95, NULL );
		LineTo( hDC, 463, 109 );
		TextOut( hDC, 442, 83, "PLT2", 4 );
		TextOut( hDC, 442, 97, "3", 1 );
		TextOut( hDC, 472, 97, "2", 1 );

		// CRT4
		if (0)// IDP is commanding
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 362, 293, 426, 378 );
			if (2 != 0)// FC bus
			{
				sprintf_s( cbuf, 16, "FC%d", 2 );
				TextOut( hDC, 373, 323, cbuf, 3 );
			}
			if (1) TextOut( hDC, 373, 337, "AUTO", 4 );// MDU port reconfiguration mode
			else TextOut( hDC, 373, 337, "MAN", 3 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 373, 351, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 363, 365, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 368, 365, "EDUMP", 5 );
			else if (0) TextOut( hDC, 368, 365, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				TextOut( hDC, 363, 365, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 362, 293, 426, 378 );
			if (1)// IDP is communicating
			{
				if (1) TextOut( hDC, 373, 337, "AUTO", 4 );// MDU port reconfiguration mode
				else TextOut( hDC, 373, 337, "MAN", 3 );
			}
		}
		MoveToEx( hDC, 362, 307, NULL );
		LineTo( hDC, 425, 307 );
		MoveToEx( hDC, 362, 321, NULL );
		LineTo( hDC, 425, 321 );
		MoveToEx( hDC, 362, 335, NULL );
		LineTo( hDC, 425, 335 );
		MoveToEx( hDC, 362, 349, NULL );
		LineTo( hDC, 425, 349 );
		MoveToEx( hDC, 362, 363, NULL );
		LineTo( hDC, 425, 363 );
		MoveToEx( hDC, 394, 307, NULL );
		LineTo( hDC, 394, 321 );
		TextOut( hDC, 373, 295, "CRT4", 4 );
		TextOut( hDC, 373, 309, "4", 1 );

		// AFD1
		if (0)// IDP is commanding
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 431, 293, 495, 378 );
			if (3 != 0)// FC bus
			{
				sprintf_s( cbuf, 16, "FC%d", 3 );
				TextOut( hDC, 442, 323, cbuf, 3 );
			}
			if (1) TextOut( hDC, 442, 337, "AUTO", 4 );// MDU port reconfiguration mode
			else TextOut( hDC, 442, 337, "MAN", 3 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 442, 351, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 432, 365, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 437, 365, "EDUMP", 5 );
			else if (0) TextOut( hDC, 437, 365, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				TextOut( hDC, 432, 365, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 431, 293, 495, 378 );
			if (1)// IDP is communicating
			{
				if (1) TextOut( hDC, 442, 337, "AUTO", 4 );// MDU port reconfiguration mode
				else TextOut( hDC, 442, 337, "MAN", 3 );
			}
		}
		MoveToEx( hDC, 431, 307, NULL );
		LineTo( hDC, 494, 307 );
		MoveToEx( hDC, 431, 321, NULL );
		LineTo( hDC, 494, 321 );
		MoveToEx( hDC, 431, 335, NULL );
		LineTo( hDC, 494, 335 );
		MoveToEx( hDC, 431, 349, NULL );
		LineTo( hDC, 494, 349 );
		MoveToEx( hDC, 431, 363, NULL );
		LineTo( hDC, 494, 363 );
		MoveToEx( hDC, 463, 307, NULL );
		LineTo( hDC, 463, 321 );
		TextOut( hDC, 442, 295, "AFD1", 4 );
		TextOut( hDC, 442, 309, "4", 1 );
		TextOut( hDC, 472, 309, "2", 1 );

		// IDP1
		if (GetDrivingIDP() == 1)// commanding IDP
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 77, 218, 159, 283 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 97, 237, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 87, 253, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 92, 253, "EDUMP", 5 );
			else if (0) TextOut( hDC, 92, 253, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				TextOut( hDC, 87, 253, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
			if (1)// flight-critical buses selected (1)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 77, 266, 98, 282 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 83, 269, "1", 1 );
			if (0)// flight-critical buses selected (2)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 98, 266, 118, 282 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 102, 269, "2", 1 );
			if (1)// flight-critical buses selected (3)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 118, 266, 138, 282 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 122, 269, "3", 1 );
			if (0)// flight-critical buses selected (4)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 138, 266, 159, 282 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 142, 269, "4", 1 );
			SetTextColor( hDC, CR_WHITE );
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 77, 218, 159, 283 );
			SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 83, 269, "1", 1 );
			TextOut( hDC, 102, 269, "2", 1 );
			TextOut( hDC, 122, 269, "3", 1 );
			TextOut( hDC, 142, 269, "4", 1 );
		}
		MoveToEx( hDC, 77, 234, NULL );
		LineTo( hDC, 158, 234 );
		MoveToEx( hDC, 77, 250, NULL );
		LineTo( hDC, 158, 250 );
		MoveToEx( hDC, 77, 266, NULL );
		LineTo( hDC, 158, 266 );
		TextOut( hDC, 97, 221, "IDP1", 4 );

		// IDP2
		if (GetDrivingIDP() == 2)// commanding IDP
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 169, 218, 251, 283 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 189, 237, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 179, 253, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 184, 253, "EDUMP", 5 );
			else if (0) TextOut( hDC, 184, 253, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				TextOut( hDC, 179, 253, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
			if (0)// flight-critical buses selected (1)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 169, 266, 190, 282 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 175, 269, "1", 1 );
			if (1)// flight-critical buses selected (2)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 190, 266, 210, 282 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 194, 269, "2", 1 );
			if (0)// flight-critical buses selected (3)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 210, 266, 230, 282 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 214, 269, "3", 1 );
			if (0)// flight-critical buses selected (4)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 230, 266, 251, 282 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 234, 269, "4", 1 );
			SetTextColor( hDC, CR_WHITE );
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 169, 218, 251, 283 );
			SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 175, 269, "1", 1 );
			TextOut( hDC, 194, 269, "2", 1 );
			TextOut( hDC, 214, 269, "3", 1 );
			TextOut( hDC, 234, 269, "4", 1 );
		}
		MoveToEx( hDC, 169, 234, NULL );
		LineTo( hDC, 250, 234 );
		MoveToEx( hDC, 169, 250, NULL );
		LineTo( hDC, 250, 250 );
		MoveToEx( hDC, 169, 266, NULL );
		LineTo( hDC, 250, 266 );
		TextOut( hDC, 189, 221, "IDP2", 4 );

		// IDP3
		if (GetDrivingIDP() == 3)// commanding IDP
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 261, 218, 343, 283 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 281, 237, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 271, 253, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 276, 253, "EDUMP", 5 );
			else if (0) TextOut( hDC, 276, 253, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				TextOut( hDC, 271, 253, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
			if (1)// flight-critical buses selected (1)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 261, 266, 282, 282 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 267, 269, "1", 1 );
			if (1)// flight-critical buses selected (2)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 282, 266, 302, 282 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 286, 269, "2", 1 );
			if (1)// flight-critical buses selected (3)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 302, 266, 322, 282 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 306, 269, "3", 1 );
			if (0)// flight-critical buses selected (4)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 322, 266, 343, 282 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 326, 269, "4", 1 );
			SetTextColor( hDC, CR_WHITE );
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 261, 218, 343, 283 );
			SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 267, 269, "1", 1 );
			TextOut( hDC, 286, 269, "2", 1 );
			TextOut( hDC, 306, 269, "3", 1 );
			TextOut( hDC, 326, 269, "4", 1 );
		}
		MoveToEx( hDC, 261, 234, NULL );
		LineTo( hDC, 342, 234 );
		MoveToEx( hDC, 261, 250, NULL );
		LineTo( hDC, 342, 250 );
		MoveToEx( hDC, 261, 266, NULL );
		LineTo( hDC, 342, 266 );
		TextOut( hDC, 281, 221, "IDP3", 4 );

		// IDP4
		if (GetDrivingIDP() == 4)// commanding IDP
		{
			SelectObject( hDC, gdiBlueBrush );
			Rectangle( hDC, 353, 218, 435, 283 );
			if (0) SetTextColor( hDC, CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			TextOut( hDC, 373, 237, cbuf, strlen( cbuf ) );
			SetTextColor( hDC, CR_WHITE );
			if (1) TextOut( hDC, 363, 253, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) TextOut( hDC, 368, 253, "EDUMP", 5 );
			else if (0) TextOut( hDC, 368, 253, "RDUMP", 5 );
			else
			{
				if (0) SetTextColor( hDC, CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				TextOut( hDC, 363, 253, cbuf, strlen( cbuf ) );
				SetTextColor( hDC, CR_WHITE );
			}
			if (0)// flight-critical buses selected (1)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 353, 266, 374, 282 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 359, 269, "1", 1 );
			if (1)// flight-critical buses selected (2)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 374, 266, 394, 282 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 378, 269, "2", 1 );
			if (0)// flight-critical buses selected (3)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 394, 266, 414, 282 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 398, 269, "3", 1 );
			if (1)// flight-critical buses selected (4)
			{
				SelectObject( hDC, gdiWhiteBrush );
				Rectangle( hDC, 414, 266, 435, 282 );
				SetTextColor( hDC, CR_BLACK );
			}
			else SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 418, 269, "4", 1 );
			SetTextColor( hDC, CR_WHITE );
		}
		else
		{
			SelectObject( hDC, gdiBlackBrush );
			Rectangle( hDC, 353, 218, 435, 283 );
			SetTextColor( hDC, CR_WHITE );
			TextOut( hDC, 359, 269, "1", 1 );
			TextOut( hDC, 378, 269, "2", 1 );
			TextOut( hDC, 398, 269, "3", 1 );
			TextOut( hDC, 418, 269, "4", 1 );
		}
		MoveToEx( hDC, 353, 234, NULL );
		LineTo( hDC, 434, 234 );
		MoveToEx( hDC, 353, 250, NULL );
		LineTo( hDC, 434, 250 );
		MoveToEx( hDC, 353, 266, NULL );
		LineTo( hDC, 434, 266 );
		TextOut( hDC, 373, 221, "IDP4", 4 );

		// additional output
		TextOut( hDC, 6, 402, "MAJOR FUNC:", 11 );// major function
		if (GetIDP()->GetMajfunc() == dps::GNC) TextOut( hDC, 116, 402, "GNC", 3 );
		else if (GetIDP()->GetMajfunc() == dps::PL) TextOut( hDC, 116, 402, "PL", 2 );
		else TextOut( hDC, 116, 402, "SM", 2 );

		TextOut( hDC, 6, 415, "IDP LOAD  :", 11 );
		if (0) TextOut( hDC, 116, 415, "LOAD", 4 );// IDP loading

		TextOut( hDC, 176, 402, "LEFT IDP SEL :", 14 );
		if (1) TextOut( hDC, 316, 402, "1", 1 );// switch position
		else TextOut( hDC, 316, 402, "3", 1 );

		TextOut( hDC, 176, 415, "RIGHT IDP SEL:", 14 );
		if (0) TextOut( hDC, 316, 415, "2", 1 );// switch position
		else TextOut( hDC, 316, 415, "3", 1 );

		TextOut( hDC, 356, 402, "KYBD SEL A:", 11 );
		if (1) TextOut( hDC, 466, 402, "ON", 2 );// keyboard port? related to switch position above?
		else TextOut( hDC, 466, 402, "OFF", 3 );

		TextOut( hDC, 356, 415, "KYBD SEL B:", 11 );
		if (0) TextOut( hDC, 466, 415, "ON", 2 );// keyboard port? related to switch position above?
		else TextOut( hDC, 466, 415, "OFF", 3 );

		TextOut( hDC, 66, 428, "ACTIVE KYBD:", 12 );
		sprintf_s( cbuf, 16, "%d", 2 );// ????
		TextOut( hDC, 186, 428, cbuf, strlen( cbuf ) );

		TextOut( hDC, 266, 428, "KEYSTROKE:", 10 );
		sprintf_s( cbuf, 16, "%s", "SYS SUMM" );// latest keyboard input
		TextOut( hDC, 366, 428, cbuf, strlen( cbuf ) );
		return;
	}

	void MDU::SystemStatusDisplay_IDPInteractiveCST( oapi::Sketchpad* skp )
	{
		char cbuf[16];

		skp->SetFont( skpSSVAFont_h10w10bold );
		skp->SetTextColor( CR_WHITE );
		skp->SetPen( skpWhitePen );

		// ADC1A
		if (0)
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 17, 293, 81, 357 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			skp->Text( 27, 319, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 18, 340, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 23, 340, "EDUMP", 5 );
			else if (0) skp->Text( 23, 340, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				skp->Text( 18, 340, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 17, 293, 81, 357 );
		}
		skp->Line( 17, 314, 80, 314 );
		skp->Line( 17, 335, 80, 335 );
		skp->Text( 23, 298, "ADC1A", 5 );

		// ADC1B
		if (0)
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 86, 293, 150, 357 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			skp->Text( 96, 319, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 87, 340, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 92, 340, "EDUMP", 5 );
			else if (0) skp->Text( 92, 340, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				skp->Text( 87, 340, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 86, 293, 150, 357 );
		}
		skp->Line( 86, 314, 149, 314 );
		skp->Line( 86, 335, 149, 335 );
		skp->Text( 92, 298, "ADC1B", 5 );

		// ADC2A
		if (0)
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 155, 293, 219, 357 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			skp->Text( 165, 319, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 156, 340, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 161, 340, "EDUMP", 5 );
			else if (0) skp->Text( 161, 340, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				skp->Text( 156, 340, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 155, 293, 219, 357 );
		}
		skp->Line( 155, 314, 218, 314 );
		skp->Line( 155, 335, 218, 335 );
		skp->Text( 161, 298, "ADC2A", 5 );

		// ADC2B
		if (0)
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 224, 293, 288, 357 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			skp->Text( 234, 319, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 225, 340, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 230, 340, "EDUMP", 5 );
			else if (0) skp->Text( 230, 340, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				skp->Text( 225, 340, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 224, 293, 288, 357 );
		}
		skp->Line( 224, 314, 287, 314 );
		skp->Line( 224, 335, 287, 335 );
		skp->Text( 230, 298, "ADC2B", 5 );

		// CDR1
		if (0)// IDP is commanding
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 17, 81, 81, 166 );
			if (1 != 0)// FC bus
			{
				sprintf_s( cbuf, 16, "FC%d", 1 );
				skp->Text( 28, 111, cbuf, strlen( cbuf ) );
			}
			if (1) skp->Text( 28, 125, "AUTO", 4 );// MDU port reconfiguration mode
			else skp->Text( 28, 125, "MAN", 3 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			skp->Text( 28, 139, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 18, 153, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 23, 153, "EDUMP", 5 );
			else if (0) skp->Text( 23, 153, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				skp->Text( 18, 153, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 17, 81, 81, 166 );
			if (1)// IDP is communicating
			{
				if (1) skp->Text( 28, 125, "AUTO", 4 );// MDU port reconfiguration mode
				else skp->Text( 28, 125, "MAN", 3 );
			}
		}
		skp->Line( 17, 95, 80, 95 );
		skp->Line( 17, 109, 80, 109 );
		skp->Line( 17, 123, 80, 123 );
		skp->Line( 17, 137, 80, 137 );
		skp->Line( 17, 151, 80, 151 );
		skp->Line( 49, 95, 49, 109 );
		skp->Text( 28, 83, "CDR1", 4 );
		skp->Text( 28, 97, "3", 1 );
		skp->Text( 58, 97, "1", 1 );

		// CDR2
		if (0)// IDP is commanding
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 86, 81, 150, 166 );
			if (2 != 0)// FC bus
			{
				sprintf_s( cbuf, 16, "FC%d", 2 );
				skp->Text( 97, 111, cbuf, strlen( cbuf ) );
			}
			if (1) skp->Text( 97, 125, "AUTO", 4 );// MDU port reconfiguration mode
			else skp->Text( 97, 125, "MAN", 3 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			skp->Text( 97, 139, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 87, 153, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 92, 153, "EDUMP", 5 );
			else if (0) skp->Text( 92, 153, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				skp->Text( 87, 153, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 86, 81, 150, 166 );
			if (1)// IDP is communicating
			{
				if (1) skp->Text( 97, 125, "AUTO", 4 );// MDU port reconfiguration mode
				else skp->Text( 97, 125, "MAN", 3 );
			}
		}
		skp->Line( 86, 95, 149, 95 );
		skp->Line( 86, 109, 149, 109 );
		skp->Line( 86, 123, 149, 123 );
		skp->Line( 86, 137, 149, 137 );
		skp->Line( 86, 151, 149, 151 );
		skp->Line( 118, 95, 118, 109 );
		skp->Text( 97, 83, "CDR2", 4 );
		skp->Text( 97, 97, "1", 1 );
		skp->Text( 127, 97, "2", 1 );

		// CRT1
		if (0)// IDP is commanding
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 155, 11, 219, 96 );
			if (3 != 0)// FC bus
			{
				sprintf_s( cbuf, 16, "FC%d", 3 );
				skp->Text( 166, 41, cbuf, strlen( cbuf ) );
			}
			if (1) skp->Text( 166, 55, "AUTO", 4 );// MDU port reconfiguration mode
			else skp->Text( 166, 55, "MAN", 3 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			skp->Text( 166, 69, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 156, 83, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 161, 83, "EDUMP", 5 );
			else if (0) skp->Text( 161, 83, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				skp->Text( 156, 83, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 155, 11, 219, 96 );
			if (1)// IDP is communicating
			{
				if (1) skp->Text( 166, 55, "AUTO", 4 );// MDU port reconfiguration mode
				else skp->Text( 166, 55, "MAN", 3 );
			}
		}
		skp->Line( 155, 25, 218, 25 );
		skp->Line( 155, 39, 218, 39 );
		skp->Line( 155, 53, 218, 53 );
		skp->Line( 155, 67, 218, 67 );
		skp->Line( 155, 81, 218, 81 );
		skp->Line( 187, 25, 187, 38 );
		skp->Text( 166, 13, "CRT1", 4 );
		skp->Text( 166, 27, "1", 1 );

		// CRT2
		if (0)// IDP is commanding
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 293, 11, 357, 96 );
			if (4 != 0)// FC bus
			{
				sprintf_s( cbuf, 16, "FC%d", 4 );
				skp->Text( 304, 41, cbuf, strlen( cbuf ) );
			}
			if (1) skp->Text( 304, 55, "AUTO", 4 );// MDU port reconfiguration mode
			else skp->Text( 304, 55, "MAN", 3 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			skp->Text( 304, 69, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 294, 83, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 299, 83, "EDUMP", 5 );
			else if (0) skp->Text( 299, 83, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				skp->Text( 294, 83, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 293, 11, 357, 96 );
			if (1)// IDP is communicating
			{
				if (1) skp->Text( 304, 55, "AUTO", 4 );// MDU port reconfiguration mode
				else skp->Text( 304, 55, "MAN", 3 );
			}
		}
		skp->Line( 293, 25, 356, 25 );
		skp->Line( 293, 39, 356, 39 );
		skp->Line( 293, 53, 356, 53 );
		skp->Line( 293, 67, 356, 67 );
		skp->Line( 293, 81, 356, 81 );
		skp->Line( 325, 25, 325, 38 );
		skp->Text( 304, 13, "CRT2", 4 );
		skp->Text( 304, 27, "2", 1 );

		// CRT3
		if (0)// IDP is commanding
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 224, 81, 288, 166 );
			if (1 != 0)// FC bus
			{
				sprintf_s( cbuf, 16, "FC%d", 1 );
				skp->Text( 235, 111, cbuf, strlen( cbuf ) );
			}
			if (1) skp->Text( 235, 125, "AUTO", 4 );// MDU port reconfiguration mode
			else skp->Text( 235, 125, "MAN", 3 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			skp->Text( 235, 139, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 225, 153, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 230, 153, "EDUMP", 5 );
			else if (0) skp->Text( 230, 153, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				skp->Text( 225, 153, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 224, 81, 288, 166 );
			if (1)// IDP is communicating
			{
				if (1) skp->Text( 235, 125, "AUTO", 4 );// MDU port reconfiguration mode
				else skp->Text( 235, 125, "MAN", 3 );
			}
		}
		skp->Line( 224, 95, 287, 95 );
		skp->Line( 224, 109, 287, 109 );
		skp->Line( 224, 123, 287, 123 );
		skp->Line( 224, 137, 287, 137 );
		skp->Line( 224, 151, 287, 151 );
		skp->Line( 256, 95, 256, 109 );
		skp->Text( 235, 83, "CRT3", 4 );
		skp->Text( 235, 97, "3", 1 );

		// MFD1
		if (0)// IDP is commanding
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 155, 123, 219, 208 );
			if (2 != 0)// FC bus
			{
				sprintf_s( cbuf, 16, "FC%d", 2 );
				skp->Text( 166, 153, cbuf, strlen( cbuf ) );
			}
			if (1) skp->Text( 166, 167, "AUTO", 4 );// MDU port reconfiguration mode
			else skp->Text( 166, 167, "MAN", 3 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			skp->Text( 166, 181, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 156, 195, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 161, 195, "EDUMP", 5 );
			else if (0) skp->Text( 161, 195, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				skp->Text( 156, 195, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 155, 123, 219, 208 );
			if (1)// IDP is communicating
			{
				if (1) skp->Text( 166, 167, "AUTO", 4 );// MDU port reconfiguration mode
				else skp->Text( 166, 167, "MAN", 3 );
			}
		}
		skp->Line( 155, 137, 218, 137 );
		skp->Line( 155, 151, 218, 151 );
		skp->Line( 155, 165, 218, 165 );
		skp->Line( 155, 179, 218, 179 );
		skp->Line( 155, 193, 218, 193 );
		skp->Line( 187, 137, 187, 151 );
		skp->Text( 166, 125, "MFD1", 4 );
		skp->Text( 166, 139, "2", 1 );
		skp->Text( 196, 139, "3", 1 );

		// MFD2
		if (0)// IDP is commanding
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 293, 123, 357, 208 );
			if (3 != 0)// FC bus
			{
				sprintf_s( cbuf, 16, "FC%d", 3 );
				skp->Text( 304, 153, cbuf, strlen( cbuf ) );
			}
			if (1) skp->Text( 304, 167, "AUTO", 4 );// MDU port reconfiguration mode
			else skp->Text( 304, 167, "MAN", 3 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			skp->Text( 304, 181, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 294, 195, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 299, 195, "EDUMP", 5 );
			else if (0) skp->Text( 299, 195, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				skp->Text( 294, 195, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 293, 123, 357, 208 );
			if (1)// IDP is communicating
			{
				if (1) skp->Text( 304, 167, "AUTO", 4 );// MDU port reconfiguration mode
				else skp->Text( 304, 167, "MAN", 3 );
			}
		}
		skp->Line( 293, 137, 356, 137 );
		skp->Line( 293, 151, 356, 151 );
		skp->Line( 293, 165, 356, 165 );
		skp->Line( 293, 179, 356, 179 );
		skp->Line( 293, 193, 356, 193 );
		skp->Line( 325, 137, 325, 151 );
		skp->Text( 304, 125, "MFD2", 4 );
		skp->Text( 304, 139, "1", 1 );
		skp->Text( 334, 139, "3", 1 );

		// PLT1
		if (0)// IDP is commanding
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 362, 81, 426, 166 );
			if (4 != 0)// FC bus
			{
				sprintf_s( cbuf, 16, "FC%d", 4 );
				skp->Text( 373, 111, cbuf, strlen( cbuf ) );
			}
			if (1) skp->Text( 373, 125, "AUTO", 4 );// MDU port reconfiguration mode
			else skp->Text( 373, 125, "MAN", 3 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			skp->Text( 373, 139, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 363, 153, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 368, 153, "EDUMP", 5 );
			else if (0) skp->Text( 368, 153, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				skp->Text( 363, 153, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 362, 81, 426, 166 );
			if (1)// IDP is communicating
			{
				if (1) skp->Text( 373, 125, "AUTO", 4 );// MDU port reconfiguration mode
				else skp->Text( 373, 125, "MAN", 3 );
			}
		}
		skp->Line( 362, 95, 425, 95 );
		skp->Line( 362, 109, 425, 109 );
		skp->Line( 362, 123, 425, 123 );
		skp->Line( 362, 137, 425, 137 );
		skp->Line( 362, 151, 425, 151 );
		skp->Line( 394, 95, 394, 109 );
		skp->Text( 373, 83, "PLT1", 4 );
		skp->Text( 373, 97, "2", 1 );
		skp->Text( 403, 97, "1", 1 );

		// PLT2
		if (0)// IDP is commanding
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 431, 81, 495, 166 );
			if (1 != 0)// FC bus
			{
				sprintf_s( cbuf, 16, "FC%d", 1 );
				skp->Text( 442, 111, cbuf, strlen( cbuf ) );
			}
			if (1) skp->Text( 442, 125, "AUTO", 4 );// MDU port reconfiguration mode
			else skp->Text( 442, 125, "MAN", 3 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			skp->Text( 442, 139, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 432, 153, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 437, 153, "EDUMP", 5 );
			else if (0) skp->Text( 437, 153, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				skp->Text( 432, 153, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 431, 81, 495, 166 );
			if (1)// IDP is communicating
			{
				if (1) skp->Text( 442, 125, "AUTO", 4 );// MDU port reconfiguration mode
				else skp->Text( 442, 125, "MAN", 3 );
			}
		}
		skp->Line( 431, 95, 494, 95 );
		skp->Line( 431, 109, 494, 109 );
		skp->Line( 431, 123, 494, 123 );
		skp->Line( 431, 137, 494, 137 );
		skp->Line( 431, 151, 494, 151 );
		skp->Line( 463, 95, 463, 109 );
		skp->Text( 442, 83, "PLT2", 4 );
		skp->Text( 442, 97, "3", 1 );
		skp->Text( 472, 97, "2", 1 );

		// CRT4
		if (0)// IDP is commanding
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 362, 293, 426, 378 );
			if (2 != 0)// FC bus
			{
				sprintf_s( cbuf, 16, "FC%d", 2 );
				skp->Text( 373, 323, cbuf, strlen( cbuf ) );
			}
			if (1) skp->Text( 373, 337, "AUTO", 4 );// MDU port reconfiguration mode
			else skp->Text( 373, 337, "MAN", 3 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			skp->Text( 373, 351, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 363, 365, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 368, 365, "EDUMP", 5 );
			else if (0) skp->Text( 368, 365, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				skp->Text( 363, 365, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 362, 293, 426, 378 );
			if (1)// IDP is communicating
			{
				if (1) skp->Text( 373, 337, "AUTO", 4 );// MDU port reconfiguration mode
				else skp->Text( 373, 337, "MAN", 3 );
			}
		}
		skp->Line( 362, 307, 425, 307 );
		skp->Line( 362, 321, 425, 321 );
		skp->Line( 362, 335, 425, 335 );
		skp->Line( 362, 349, 425, 349 );
		skp->Line( 362, 363, 425, 363 );
		skp->Line( 394, 307, 394, 321 );
		skp->Text( 373, 295, "CRT4", 4 );
		skp->Text( 373, 309, "4", 1 );

		// AFD1
		if (0)// IDP is commanding
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 431, 293, 495, 378 );
			if (3 != 0)// FC bus
			{
				sprintf_s( cbuf, 16, "FC%d", 3 );
				skp->Text( 442, 323, cbuf, strlen( cbuf ) );
			}
			if (1) skp->Text( 442, 337, "AUTO", 4 );// MDU port reconfiguration mode
			else skp->Text( 442, 337, "MAN", 3 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			skp->Text( 442, 351, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 432, 365, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 437, 365, "EDUMP", 5 );
			else if (0) skp->Text( 437, 365, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				skp->Text( 432, 365, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 431, 293, 495, 378 );
			if (1)// IDP is communicating
			{
				if (1) skp->Text( 442, 337, "AUTO", 4 );// MDU port reconfiguration mode
				else skp->Text( 442, 337, "MAN", 3 );
			}
		}
		skp->Line( 431, 307, 494, 307 );
		skp->Line( 431, 321, 494, 321 );
		skp->Line( 431, 335, 494, 335 );
		skp->Line( 431, 349, 494, 349 );
		skp->Line( 431, 363, 494, 363 );
		skp->Line( 463, 307, 463, 321 );
		skp->Text( 442, 295, "AFD1", 4 );
		skp->Text( 442, 309, "4", 1 );
		skp->Text( 472, 309, "2", 1 );

		// IDP1
		if (GetDrivingIDP() == 1)// commanding IDP
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 77, 218, 159, 283 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			skp->Text( 97, 237, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 87, 253, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 92, 253, "EDUMP", 5 );
			else if (0) skp->Text( 92, 253, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				skp->Text( 87, 253, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
			if (1)// flight-critical buses selected (1)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 77, 266, 98, 282 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 83, 269, "1", 1 );
			if (0)// flight-critical buses selected (2)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 98, 266, 118, 282 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 102, 269, "2", 1 );
			if (1)// flight-critical buses selected (3)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 118, 266, 138, 282 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 122, 269, "3", 1 );
			if (0)// flight-critical buses selected (4)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 138, 266, 159, 282 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 142, 269, "4", 1 );
			skp->SetTextColor( CR_WHITE );
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 77, 218, 159, 283 );
			skp->SetTextColor( CR_WHITE );
			skp->Text( 83, 269, "1", 1 );
			skp->Text( 102, 269, "2", 1 );
			skp->Text( 122, 269, "3", 1 );
			skp->Text( 142, 269, "4", 1 );
		}
		skp->Line( 77, 234, 158, 234 );
		skp->Line( 77, 250, 158, 250 );
		skp->Line( 77, 266, 158, 266 );
		skp->Text( 97, 221, "IDP1", 4 );

		// IDP2
		if (GetDrivingIDP() == 2)// commanding IDP
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 169, 218, 251, 283 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			skp->Text( 189, 237, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 179, 253, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 184, 253, "EDUMP", 5 );
			else if (0) skp->Text( 184, 253, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				skp->Text( 179, 253, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
			if (0)// flight-critical buses selected (1)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 169, 266, 190, 282 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 175, 269, "1", 1 );
			if (1)// flight-critical buses selected (2)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 190, 266, 210, 282 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 194, 269, "2", 1 );
			if (0)// flight-critical buses selected (3)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 210, 266, 230, 282 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 214, 269, "3", 1 );
			if (1)// flight-critical buses selected (4)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 230, 266, 251, 282 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 234, 269, "4", 1 );
			skp->SetTextColor( CR_WHITE );
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 169, 218, 251, 283 );
			skp->SetTextColor( CR_WHITE );
			skp->Text( 175, 269, "1", 1 );
			skp->Text( 194, 269, "2", 1 );
			skp->Text( 214, 269, "3", 1 );
			skp->Text( 234, 269, "4", 1 );
		}
		skp->Line( 169, 234, 250, 234 );
		skp->Line( 169, 250, 250, 250 );
		skp->Line( 169, 266, 250, 266 );
		skp->Text( 189, 221, "IDP2", 4 );

		// IDP3
		if (GetDrivingIDP() == 3)// commanding IDP
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 261, 218, 343, 283 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			skp->Text( 281, 237, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 271, 253, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 276, 253, "EDUMP", 5 );
			else if (0) skp->Text( 276, 253, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				skp->Text( 271, 253, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
			if (1)// flight-critical buses selected (1)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 261, 266, 282, 282 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 267, 269, "1", 1 );
			if (0)// flight-critical buses selected (2)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 282, 266, 302, 282 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 286, 269, "2", 1 );
			if (1)// flight-critical buses selected (3)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 302, 266, 322, 282 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 306, 269, "3", 1 );
			if (0)// flight-critical buses selected (4)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 322, 266, 343, 282 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 326, 269, "4", 1 );
			skp->SetTextColor( CR_WHITE );
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 261, 218, 343, 283 );
			skp->SetTextColor( CR_WHITE );
			skp->Text( 267, 269, "1", 1 );
			skp->Text( 286, 269, "2", 1 );
			skp->Text( 306, 269, "3", 1 );
			skp->Text( 326, 269, "4", 1 );
		}
		skp->Line( 261, 234, 342, 234 );
		skp->Line( 261, 250, 342, 250 );
		skp->Line( 261, 266, 342, 266 );
		skp->Text( 281, 221, "IDP3", 4 );

		// IDP4
		if (GetDrivingIDP() == 4)// commanding IDP
		{
			skp->SetBrush( skpBlueBrush );
			skp->Rectangle( 353, 218, 435, 283 );
			if (0) skp->SetTextColor( CR_RED );
			sprintf_s( cbuf, 16, "%04X", 0 );// Built In Test Summary
			skp->Text( 373, 237, cbuf, strlen( cbuf ) );
			skp->SetTextColor( CR_WHITE );
			if (1) skp->Text( 363, 253, "NO-CST", 6 );// Dump Status or Comprehensive Self Test Results
			else if (0) skp->Text( 368, 253, "EDUMP", 5 );
			else if (0) skp->Text( 368, 253, "RDUMP", 5 );
			else
			{
				if (0) skp->SetTextColor( CR_RED );
				sprintf_s( cbuf, 16, "%06X", 0 );
				skp->Text( 363, 253, cbuf, strlen( cbuf ) );
				skp->SetTextColor( CR_WHITE );
			}
			if (0)// flight-critical buses selected (1)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 353, 266, 374, 282 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 359, 269, "1", 1 );
			if (1)// flight-critical buses selected (2)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 374, 266, 394, 282 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 378, 269, "2", 1 );
			if (0)// flight-critical buses selected (3)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 394, 266, 414, 282 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 398, 269, "3", 1 );
			if (1)// flight-critical buses selected (4)
			{
				skp->SetBrush( skpWhiteBrush );
				skp->Rectangle( 414, 266, 435, 282 );
				skp->SetTextColor( CR_BLACK );
			}
			else skp->SetTextColor( CR_WHITE );
			skp->Text( 418, 269, "4", 1 );
			skp->SetTextColor( CR_WHITE );
		}
		else
		{
			skp->SetBrush( skpBlackBrush );
			skp->Rectangle( 353, 218, 435, 283 );
			skp->SetTextColor( CR_WHITE );
			skp->Text( 359, 269, "1", 1 );
			skp->Text( 378, 269, "2", 1 );
			skp->Text( 398, 269, "3", 1 );
			skp->Text( 418, 269, "4", 1 );
		}
		skp->Line( 353, 234, 434, 234 );
		skp->Line( 353, 250, 434, 250 );
		skp->Line( 353, 266, 434, 266 );
		skp->Text( 373, 221, "IDP4", 4 );

		// additional output
		skp->Text( 6, 402, "MAJOR FUNC:", 11 );// major function
		if (GetIDP()->GetMajfunc() == dps::GNC) skp->Text( 116, 402, "GNC", 3 );
		else if (GetIDP()->GetMajfunc() == dps::PL) skp->Text( 116, 402, "PL", 2 );
		else skp->Text( 116, 402, "SM", 2 );

		skp->Text( 6, 415, "IDP LOAD  :", 11 );
		if (0) skp->Text( 116, 415, "LOAD", 4 );// IDP loading

		skp->Text( 176, 402, "LEFT IDP SEL :", 14 );
		if (1) skp->Text( 316, 402, "1", 1 );// switch position
		else skp->Text( 316, 402, "3", 1 );

		skp->Text( 176, 415, "RIGHT IDP SEL:", 14 );
		if (0) skp->Text( 316, 415, "2", 1 );// switch position
		else skp->Text( 316, 415, "3", 1 );

		skp->Text( 356, 402, "KYBD SEL A:", 11 );
		if (1) skp->Text( 466, 402, "ON", 2 );// keyboard port? related to switch position above?
		else skp->Text( 466, 402, "OFF", 3 );

		skp->Text( 356, 415, "KYBD SEL B:", 11 );
		if (0) skp->Text( 466, 415, "ON", 2 );// keyboard port? related to switch position above?
		else skp->Text( 466, 415, "OFF", 3 );

		skp->Text( 66, 428, "ACTIVE KYBD:", 12 );
		sprintf_s( cbuf, 16, "%d", 2 );// ????
		skp->Text( 186, 428, cbuf, strlen( cbuf ) );

		skp->Text( 266, 428, "KEYSTROKE:", 10 );
		sprintf_s( cbuf, 16, "%s", "SYS SUMM" );// latest keyboard input
		skp->Text( 366, 428, cbuf, strlen( cbuf ) );

		return;
	}
};
